/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary                    */
/*                                                                              */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerBW32.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "BW32/ScalerBW32.h"

#if(_HW_CPU32_BW32_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
const BYTE tBW32CmdModeLastValidNum[4] = {6, 0, 2, 4};
const BYTE tBW32DataModeLastValidNum[8] = {7, 0, 1, 2, 3, 4, 5, 6};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
EnumBW32CallBackFuncId g_enumBW32CallbackFunctionId = _BW32_CALLBACK_NULL;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBW32RunCallbackFunction(void)
{
    EnumBW32CallBackFuncId enumBW32CallbackFunctionId = g_enumBW32CallbackFunctionId;
    g_enumBW32CallbackFunctionId = _BW32_CALLBACK_NULL;

    switch(enumBW32CallbackFunctionId)
    {
        case _BW32_CALLBACK_SPI_DIMMING_LD_SRAM:
#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON) &&\
    (_LOCAL_DIMMING_FUNCTION == _ON) && (_SCPU_SUPPORT == _ON) &&\
    (_HW_CPU32_MEMORYMAP_ACCESS_DDR == _TRUE))
            ScalerSpiDimmingLDSramModeBW32DoneCallBack();
#endif
            break;

        case _BW32_CALLBACK_NULL:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : BurstWrite32 Finish Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBW32_IRQHandler(void)
{
    if(ScalerBW32GetFinishINTFlag() != 0)
    {
        // BW32 write finish

        // Ack Flag
        ScalerBW32AckFinishINTFlag();

        if(ScalerBW32ChkAllDone() == 0)
        {
            // Release BW32 resource lock
            RESOURCE_RELEASE(_RESOURCE_ID_BW32);

            if(g_enumBW32CallbackFunctionId != _BW32_CALLBACK_NULL)
            {
                ScalerBW32RunCallbackFunction();
            }
        }
    }
    else
    {
        // Error Dsetination Address Check
        ScalerBW32Error_Handler();

        // Force Release BW32 resource lock when BW32 Failed
        RESOURCE_RELEASE(_RESOURCE_ID_BW32);
    }
}

//--------------------------------------------------
// Description  : BurstWrite32 Error Handler
// Input Value  : None
// Output Value : 0:No Error Happened , 1: Invalid Address Happened
//--------------------------------------------------
bit ScalerBW32Error_Handler(void)
{
    if(Scaler32GetBit(PA20002_50_BW32_ERR_DEST_CTRL, (_BIT16 | _BIT8 | _BIT0)) != 0)
    {
        ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_BW32_DEST_ADDR);
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Launch BW32 Command
// Input Value  :
//    ucTotalCmdXcnt --> BW32 CmdX use Number
//    pstBW32CmdInfo :
//              ->stBW32BaseInfo:
//                  ->enumBW32CmdFormat --> BW32 Cmd Format(Cmd/Data)
//                  ->ulDdrSrcAddr --> DDR Address of BW32 Source Command Table
//                  ->ulDestRBusdRegAddr --> Data Mode RBUSD Destination Start Reg Address
//                  ->ulTotalCmdNum --> Total Command Set(32bAddr+32bData) or Data Set(32bData) Number of BW32 Command Table
//                  ->bAddrAutoInc --> is Address Auto Increase in Data Mode
//              ->enumBW32TriggerSource --> BW32 trigger source
//    usWaitResourceLockTimeoutMS --> Wait Timeout MS Counter for Waiting BW32 Resource Lock
//    bWaitExecuteDone --> Sync Wait BW32 Execute done
//    usWaitExeTimeoutMS --> Wait Timeout MS Counter for Sync Waiting BW32 Execute done
//    pCallBackFuncPtr --> if Use NoWait, BW32 will execute call back function in BW32 finish INT
// Output Value : _TRUE:Success ; _FALSE:Failed
//--------------------------------------------------
bit ScalerBW32LaunchCmdX(BYTE ucTotalCmdXcnt, StructBW32CmdInfo *pstBW32CmdInfo, WORD usWaitResourceLockTimeoutMS, bit bWaitExecuteDone, WORD usWaitExeTimeoutMS, EnumBW32CallBackFuncId enumCallBackFuncId)
{
    if(ScalerMcuCheckHwBW32Avaiable() == _TRUE)
    {
        if(ScalerBW32PrepareCmdX(ucTotalCmdXcnt, pstBW32CmdInfo, usWaitResourceLockTimeoutMS) == _TRUE)
        {
            return ScalerBW32ExecuteCmdX(ucTotalCmdXcnt, pstBW32CmdInfo, bWaitExecuteDone, usWaitExeTimeoutMS, enumCallBackFuncId);
        }
        return _FALSE;
    }
    else
    {
        usWaitResourceLockTimeoutMS = usWaitResourceLockTimeoutMS;
        usWaitExeTimeoutMS = usWaitExeTimeoutMS;

        if(bWaitExecuteDone == _TRUE)
        {
            enumCallBackFuncId = _BW32_CALLBACK_NULL;
        }
        enumCallBackFuncId = enumCallBackFuncId;

        // BW32 FW Mode
        for(DWORD ulCmdIdx = 0; ulCmdIdx < ucTotalCmdXcnt; ulCmdIdx++)
        {
            StructBW32BaseInfo * pstBW32BaseInfo = &pstBW32CmdInfo[ulCmdIdx].stBW32BaseInfo;

            DWORD ulTotalCmdNum = pstBW32BaseInfo->ulTotalCmdNum;

            if(pstBW32BaseInfo->enumBW32CmdFormat == _BW32_DATA_FORMAT)
            {
                DWORD ulDestRBusdRegAddr = pstBW32BaseInfo->ulDestRBusdRegAddr;
                DWORD *pulDdrSrcDataArray = (DWORD *)pstBW32BaseInfo->ulDdrSrcAddr;
                DWORD ulAddrIncOffset = (pstBW32BaseInfo->bAddrAutoInc ? 4 : 0);

                // BW32 DATA Format
                for(DWORD ulCmdNumIdx = 0; ulCmdNumIdx < ulTotalCmdNum; ulCmdNumIdx++)
                {
                    Scaler32SetDWord(ulDestRBusdRegAddr, pulDdrSrcDataArray[ulCmdNumIdx]);
                    ulDestRBusdRegAddr += ulAddrIncOffset;
                }
            }
            else
            {
                StructBW32CmdPair *pstDdrSrcCmdArray = (StructBW32CmdPair *)pstBW32BaseInfo->ulDdrSrcAddr;

                // BW32 CMD Format
                for(DWORD ulCmdNumIdx = 0; ulCmdNumIdx < ulTotalCmdNum; ulCmdNumIdx++)
                {
                    Scaler32SetDWord(pstDdrSrcCmdArray[ulCmdNumIdx].ulBW32_ADDRESS, pstDdrSrcCmdArray[ulCmdNumIdx].ulBW32_DATA);
                }
            }
        }

        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Launch BW32 Command After IDomain Event
// Input Value  :
//    pstBW32IDomainCmdInfo :
//              ->stBW32BaseInfo:
//                  ->enumBW32CmdFormat --> BW32 Cmd Format(Cmd/Data)
//                  ->ulDdrSrcAddr --> DDR Address of BW32 Source Command Table
//                  ->ulDestRBusdRegAddr --> Data Mode RBUSD Destination Start Reg Address
//                  ->ulTotalCmdNum --> Total Command Set(32bAddr+32bData) or Data Set(32bData) Number of BW32 Command Table
//                  ->bAddrAutoInc --> is Address Auto Increase in Data Mode
//              ->enumWaitIDomainEvent --> I-Domain Specified event
//              ->enumInputDataPath --> I-Domain Data Path
//    usWaitResourceLockTimeoutMS --> Wait Timeout MS Counter for Waiting BW32 Resource Lock
//    usWaitExeTimeoutMS --> Wait Timeout MS Counter for Sync Waiting BW32 Execute done
// Output Value : _TRUE:Success ; _FALSE:Failed
//--------------------------------------------------
bit ScalerBW32LaunchCmdXAfterIDomainEvent(StructBW32IDomainCmdInfo *pstBW32IDomainCmdInfo, WORD usWaitResourceLockTimeoutMS, WORD usWaitExeTimeoutMS)
{
    if(ScalerMcuCheckHwBW32Avaiable() == _FALSE)
    {
        DebugMessageCpu32("warning!!! NOTE: HW BW32 is not avaiable!!!", 0);
        return _FALSE;
    }
    StructBW32CmdInfo stBW32CmdInfo;
    memcpy(&stBW32CmdInfo.stBW32BaseInfo, &pstBW32IDomainCmdInfo->stBW32BaseInfo, sizeof(StructBW32BaseInfo));
    stBW32CmdInfo.enumBW32TriggerSource = _BW32_TRIGGER_MANUAL;

    if(ScalerBW32PrepareCmdX(1, &stBW32CmdInfo, usWaitResourceLockTimeoutMS) == _TRUE)
    {
        if(ScalerTimerWaitForIDomainEvent(pstBW32IDomainCmdInfo->enumWaitIDomainEvent, pstBW32IDomainCmdInfo->enumInputDataPath) == _TRUE)
        {
            return ScalerBW32ExecuteCmdX(1, &stBW32CmdInfo, _TRUE, usWaitExeTimeoutMS, _BW32_CALLBACK_NULL);
        }
        RESOURCE_RELEASE(_RESOURCE_ID_BW32);
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Prepare BW32 Command
// Input Value  :
//    ucTotalCmdXcnt --> BW32 CmdX use Number
//    pstBW32CmdInfo :
//              ->enumBW32CmdFormat --> BW32 Cmd Format(Cmd/Data)
//              ->enumBW32TriggerSource --> BW32 trigger source
//              ->ulDdrSrcAddr --> DDR Address of BW32 Source Command Table
//              ->ulDestRBusdRegAddr --> Data Mode RBUSD Destination Start Reg Address
//              ->ulTotalCmdNum --> Total Command Set(32bAddr+32bData) or Data Set(32bData) Number of BW32 Command Table
//              ->bAddrAutoInc --> is Address Auto Increase in Data Mode
//    usWaitResourceLockTimeoutMS --> Wait Timeout MS Counter for Waiting BW32 Resource Lock
// Output Value : _TRUE:Success ; _FALSE:Failed
//--------------------------------------------------
bit ScalerBW32PrepareCmdX(BYTE ucTotalCmdXcnt, StructBW32CmdInfo *pstBW32CmdInfo, WORD usWaitResourceLockTimeoutMS)
{
    // CmdX Total Write Reg Number:
    // CMD MODE = (bw32_len * bw32_num_cmdX) ??(4 ??cmdX_last_valid_cmd_num)
    // DATA MODE = ((bw32_len * bw32_num_cmdX) * 2) ??(8 ??cmdX_last_valid_cmd_num)
    DWORD ulBW32_LEN = _MAX_BW32_LEN;   // Cmd per fetch from DDR
    DWORD pulTmpLen[3] = {_MAX_BW32_LEN, _MAX_BW32_LEN, _MAX_BW32_LEN};

    if(ucTotalCmdXcnt == 0)
    {
        DebugMessageCpu32("ERROR:BW32 TotalCmdXcnt == 0", 0);
        return _FALSE;
    }
    if(ucTotalCmdXcnt > 3)
    {
        DebugMessageCpu32("ERROR:BW32 TotalCmdXcnt >3", ucTotalCmdXcnt);
        return _FALSE;
    }

    // Acquire BW32 resource lock
    if(RESOURCE_ACQUIRE(_RESOURCE_ID_BW32, (((DWORD)usWaitResourceLockTimeoutMS) * 100)) == _FALSE)
    {
        return _FALSE;
    }

    // check &&confirm min BW32_LEN
    for(BYTE ucCmdIdx = 0; ucCmdIdx < ucTotalCmdXcnt; ucCmdIdx++)
    {
        DWORD ulLastBlockValidCmdNum = 0;

        StructBW32BaseInfo *pstBaseInfo = &pstBW32CmdInfo[ucCmdIdx].stBW32BaseInfo;

        if(((pstBaseInfo->ulDdrSrcAddr & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0) ||
           (pstBaseInfo->ulDdrSrcAddr < _CPU32_DDR_PHYSICS_OFFSET))
        {
            // Start Address of BW32 Command table mus be align to 32 (StartAddress[4:0] must be 0)
            DebugMessageCpu32("ERROR:Start Address of BW32 Command table mus be align to 32", pstBaseInfo->ulDdrSrcAddr);
            RESOURCE_RELEASE(_RESOURCE_ID_BW32);
            return _FALSE;
        }

        if((pstBaseInfo->ulTotalCmdNum > (_MAX_BW32_LEN * _MAX_BW32_NUM_CMD)) ||
           (pstBaseInfo->ulTotalCmdNum == 0))
        {
            // total Num must be even and can be divided by 4 for use
            DebugMessageCpu32("ERROR:total Num must be even and can be divided by 4 for use", pstBaseInfo->ulTotalCmdNum);
            RESOURCE_RELEASE(_RESOURCE_ID_BW32);
            return _FALSE;
        }

        if(pstBaseInfo->enumBW32CmdFormat == _BW32_CMD_FORMAT)
        {
            // max 4 cmd set(32bAddr,32bData) in one CMD Block
            ulLastBlockValidCmdNum = (pstBaseInfo->ulTotalCmdNum & 3UL);
            pstBaseInfo->ulTotalCmdNum = (((pstBaseInfo->ulTotalCmdNum + 3) / 4) * 4);
        }
        else
        {
            // max 8 data set(32bData) in one CMD Block
            ulLastBlockValidCmdNum = (pstBaseInfo->ulTotalCmdNum & 7UL);
            pstBaseInfo->ulTotalCmdNum = (((pstBaseInfo->ulTotalCmdNum + 7) / 8) * 8) / 2;
        }

        while((pstBaseInfo->ulTotalCmdNum % pulTmpLen[ucCmdIdx]) != 0)
        {
            pulTmpLen[ucCmdIdx] -= 4;
        }

        if(ulBW32_LEN > pulTmpLen[ucCmdIdx])
        {
            ulBW32_LEN = pulTmpLen[ucCmdIdx];
        }

        ScalerBW32SetLastBlockValidCmdNum(ucCmdIdx, pstBaseInfo->enumBW32CmdFormat, ulLastBlockValidCmdNum);
    }

    // find greatest common divisor
    if(ucTotalCmdXcnt != 1)
    {
        while(ulBW32_LEN >= 8)
        {
            if(ucTotalCmdXcnt == 2)
            {
                if(((pulTmpLen[0] % ulBW32_LEN) == 0) && ((pulTmpLen[1] % ulBW32_LEN) == 0))
                {
                    break;
                }
            }
            if(ucTotalCmdXcnt == 3)
            {
                if(((pulTmpLen[0] % ulBW32_LEN) == 0) && ((pulTmpLen[1] % ulBW32_LEN) == 0) && ((pulTmpLen[2] % ulBW32_LEN) == 0))
                {
                    break;
                }
            }
            ulBW32_LEN -= 4;
        }
    }

    for(BYTE ucCmdIdx = 0; ucCmdIdx < ucTotalCmdXcnt; ucCmdIdx++)
    {
        StructBW32BaseInfo *pstBaseInfo = &pstBW32CmdInfo[ucCmdIdx].stBW32BaseInfo;
        DWORD ulBW32_DDR_SRC_ADDR = pstBaseInfo->ulDdrSrcAddr - _CPU32_DDR_PHYSICS_OFFSET;   // DDR source Address of CMD Block
        DWORD ulBW32_BLOCK_NUM = (pstBaseInfo->ulTotalCmdNum / ulBW32_LEN);  // Total fetch times from DDR

        if(ulBW32_BLOCK_NUM > _MAX_BW32_NUM_CMD)
        {
            DebugMessageCpu32("ERROR:BW32 Block Number Over _MAX_BW32_NUM_CMD", ulBW32_BLOCK_NUM);
            RESOURCE_RELEASE(_RESOURCE_ID_BW32);
            return _FALSE;
        }

        // Cmd Format
        // Address Auto Increase
        Scaler32SetBit(PA20002_30_BW32_MODE_CTRL, ~((_BIT7 | _BIT6) << (ucCmdIdx * 8)), (((((DWORD)pstBaseInfo->bAddrAutoInc) << 7) | (((DWORD)pstBaseInfo->enumBW32CmdFormat) << 6)) << (ucCmdIdx * 8)));

        if(pstBaseInfo->enumBW32CmdFormat == _BW32_DATA_FORMAT)
        {
            // Data Mode Dest Start Address
            Scaler32SetDWord((PA20002_40_BW32_DATA_DEST_ADDR0 + (ucCmdIdx * 4)), pstBaseInfo->ulDestRBusdRegAddr);
        }

        Scaler32SetDWord((PA20002_20_BW32_ADDR0 + (ucCmdIdx << 2)), ulBW32_DDR_SRC_ADDR);

        switch(ucCmdIdx)
        {
            case 0:
                Scaler32SetBit(PA20002_10_BW32_NUM0, ~(0x00000FFF), ulBW32_BLOCK_NUM);
                break;

            case 1:
                Scaler32SetBit(PA20002_10_BW32_NUM0, ~(0x0FFF0000), (ulBW32_BLOCK_NUM << 16));
                break;

            case 2:
                Scaler32SetBit(PA20002_14_BW32_NUM1, ~(0x00000FFF), ulBW32_BLOCK_NUM);
                break;

            default:
                DebugMessageCpu32("ERROR:Invalid enumBW32CmdX", ucCmdIdx);
                RESOURCE_RELEASE(_RESOURCE_ID_BW32);
                return _FALSE;
        }
    }
    DWORD ulBW32_WATER_LEVEL = (BYTE)(256 - (ulBW32_LEN * 2));  // water level for triggering DDR Fetch
    Scaler32SetDWord(PA20002_08_BW32_CTRL, ((DWORD)ulBW32_WATER_LEVEL) << 16 | ((DWORD)ulBW32_LEN));

    // force d-cache sync to DDR
    ScalerCpuHalCleanDataCache();

    return _TRUE;
}


//--------------------------------------------------
// Description  : Execute BW32 Command
// Input Value  :
//    bWaitExecuteDone --> Sync Wait BW32 Execute done
//    usWaitExeTimeoutMS --> Wait Timeout MS Counter for Sync Waiting BW32 Execute done
//    pCallBackFuncPtr --> if Use NoWait, BW32 will execute call back function in BW32 finish INT
// Output Value : _TRUE:Success ; _FALSE:Failed
//--------------------------------------------------
bit ScalerBW32ExecuteCmdX(BYTE ucTotalCmdXcnt, StructBW32CmdInfo *pstBW32CmdInfo, bit bWaitExecuteDone, WORD usWaitExeTimeoutMS, EnumBW32CallBackFuncId enumCallBackFuncId)
{
    DWORD ulBW32_ManulTrigger = 0;

    enumCallBackFuncId = enumCallBackFuncId;

    if(bWaitExecuteDone == _FALSE)
    {
        // BW32 use Finish INT(ACK && Enable BW32 INT)
        Scaler32SetDWord(PA20002_00_BW32_TOP_CTRL, (_BIT12 | _BIT8));
        g_enumBW32CallbackFunctionId = enumCallBackFuncId;
    }
    else
    {
        // Busy Wait BW32 execute done(ACK  && disable BW32 INT)
        Scaler32SetDWord(PA20002_00_BW32_TOP_CTRL, _BIT8);
        g_enumBW32CallbackFunctionId = _BW32_CALLBACK_NULL;
    }

    for(BYTE ucCmdIdx = 0; ucCmdIdx < ucTotalCmdXcnt; ucCmdIdx++)
    {
        if(pstBW32CmdInfo[ucCmdIdx].enumBW32TriggerSource == _BW32_TRIGGER_MANUAL)
        {
            ulBW32_ManulTrigger |= (_BIT0 << ucCmdIdx);
        }
    }
    // Launch BW cmdX
    if(ulBW32_ManulTrigger == (_BIT2 | _BIT1 | _BIT0))
    {
        // all cmd are manual triggered
        Scaler32SetBit(PA20002_00_BW32_TOP_CTRL, ~(_BIT8 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        for(BYTE ucCmdIdx = 0; ucCmdIdx < ucTotalCmdXcnt; ucCmdIdx++)
        {
            ScalerBW32SetCmdTriggerSource(ucCmdIdx, pstBW32CmdInfo[ucCmdIdx].enumBW32TriggerSource);
        }
    }

    if(bWaitExecuteDone == _TRUE)
    {
        DWORD ulStatus = 0;
        WORD usPreviousTime = g_usTimerCounter;

        while(((ulStatus = ScalerBW32ChkAllDone()) != 0) &&
              (usWaitExeTimeoutMS != 0))
        {
            // _MAX_BW32_LEN * 124.4ns(write DWORD share ram) = 15.425us
            ScalerMcuDelayXus(16);

            if(usPreviousTime != g_usTimerCounter)
            {
                usWaitExeTimeoutMS--;
                usPreviousTime = g_usTimerCounter;
            }
        }

        RESOURCE_RELEASE(_RESOURCE_ID_BW32);
        return (ulStatus == 0);
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : Enable RBUS BurstWrite Finish Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBW32EnableFinishINT(void)
{
    Scaler32SetBit(PA20002_00_BW32_TOP_CTRL, ~(_BIT12 | _BIT8 | _BIT2 | _BIT1 | _BIT0), _BIT12);
}

//--------------------------------------------------
// Description  : Disable RBUS BurstWrite Finish Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBW32DisableFinishINT(void)
{
    Scaler32SetBit(PA20002_00_BW32_TOP_CTRL, ~(_BIT12 | _BIT8 | _BIT2 | _BIT1 | _BIT0), 0);
}

//--------------------------------------------------
// Description  : Get RBUS BurstWrite Finish Interrupt Flag
// Input Value  : None
// Output Value : 0:not happened ; other:happened
//--------------------------------------------------
DWORD ScalerBW32GetFinishINTFlag(void)
{
    return Scaler32GetBit(PA20002_00_BW32_TOP_CTRL, _BIT8);
}

//--------------------------------------------------
// Description  : Ack RBUS BurstWrite Finish Interrupt Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBW32AckFinishINTFlag(void)
{
    Scaler32SetBit(PA20002_00_BW32_TOP_CTRL, ~(_BIT8 | _BIT2 | _BIT1 | _BIT0), _BIT8);

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}

//--------------------------------------------------
// Description  : Check if Cmd0 Block's Burst Write operation finished?
// Input Value  : None
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
void ScalerBW32SetCmdTriggerSource(EnumBW32CmdX enumBW32CmdX, EnumBW32TriggerSource enumBW32TriggerSource)
{
    if(enumBW32TriggerSource == _BW32_TRIGGER_MANUAL)
    {
        Scaler32SetBit(PA20002_00_BW32_TOP_CTRL, ~(_BIT8 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumBW32CmdX));
    }
    else
    {
        // DVS/DEB_START/DEN_STOP
        Scaler32SetBit(PA20002_70_BW32_DOMAIN_EVENT_TRIGGER0 + (enumBW32CmdX * 4), ~(_BIT2 | _BIT1 | _BIT0), enumBW32TriggerSource);
    }
}


//--------------------------------------------------
// Description  : Check if Cmd0 Block's Burst Write operation finished?
// Input Value  : None
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
void ScalerBW32SetLastBlockValidCmdNum(EnumBW32CmdX enumBW32CmdX, EnumBW32CmdFormat enumBW32CmdFormat, DWORD ulLastBlockValidCmdNum)
{
    if(enumBW32CmdFormat == _BW32_CMD_FORMAT)
    {
        // In CMD Mode:
        // 'b000: the last data is 1st 64Bits
        // 'b010: the last data is 2nd 64Bits
        // 'b100: the last data is 3rd 64Bits
        // 'b110: the last data is 4th 64Bits (size aligned)
        if(ulLastBlockValidCmdNum > 3)
        {
            return;
        }
        Scaler32SetBit(PA20002_30_BW32_MODE_CTRL, ~((_BIT2 | _BIT1 | _BIT0) << (enumBW32CmdX * 8)), (((DWORD)tBW32CmdModeLastValidNum[ulLastBlockValidCmdNum]) << (enumBW32CmdX * 8)));
    }
    else
    {
        // In DATA Mode:
        // 'b000: the last data is 1st 32Bits
        // 'b001: the last data is 2nd 32Bits
        // 'b010: the last data is 3rd 32Bits
        // 'b011: the last data is 4th 32Bits
        // 'b100: the last data is 5th 32Bits
        // 'b101: the last data is 6th 32Bits
        // 'b110: the last data is 7th 32Bits
        // 'b111: the last data is 8th 32Bits (size aligned)
        if(ulLastBlockValidCmdNum > 7)
        {
            return;
        }
        Scaler32SetBit(PA20002_30_BW32_MODE_CTRL, ~((_BIT2 | _BIT1 | _BIT0) << (enumBW32CmdX * 8)), (((DWORD)tBW32DataModeLastValidNum[ulLastBlockValidCmdNum]) << (enumBW32CmdX * 8)));
    }
}

//--------------------------------------------------
// Description  : Check if Cmd0 Block's Burst Write operation finished?
// Input Value  : enumBW32CmdX --> BW32 cmdX
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
DWORD ScalerBW32ChkCmdXManualDone(EnumBW32CmdX enumBW32CmdX)
{
    return Scaler32GetBit(PA20002_00_BW32_TOP_CTRL, (_BIT0 << enumBW32CmdX));
}

//--------------------------------------------------
// Description  : Check if Cmd0 Block's Burst Write operation finished?
// Input Value  : enumBW32CmdX --> BW32 cmdX
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
DWORD ScalerBW32ChkCmdXDomainEventDone(EnumBW32CmdX enumBW32CmdX)
{
    return Scaler32GetDWord(PA20002_70_BW32_DOMAIN_EVENT_TRIGGER0 + (enumBW32CmdX << 2));
}

//--------------------------------------------------
// Description  : Check if all Burst Write operation finished?
// Input Value  : None
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
DWORD ScalerBW32ChkAllDone(void)
{
    return (Scaler32GetBit(PA20002_00_BW32_TOP_CTRL, (_BIT2 | _BIT1 | _BIT0)) | Scaler32GetDWord(PA20002_70_BW32_DOMAIN_EVENT_TRIGGER0) | Scaler32GetDWord(PA20002_74_BW32_DOMAIN_EVENT_TRIGGER1) | Scaler32GetDWord(PA20002_78_BW32_DOMAIN_EVENT_TRIGGER2));
}

//--------------------------------------------------
// Description  : Get Burst Write FIFO Water Level setting
// Input Value  : None
// Output Value : 9bits Water Level setting
//--------------------------------------------------
DWORD ScalerBW32GetFifoWaterLevelSetting(void)
{
    return ((Scaler32GetDWord(PA20002_08_BW32_CTRL) >> 16) & 0x000001FF);
}

//--------------------------------------------------
// Description  : Get Burst Write Reas Once Num setting
// Input Value  : None
// Output Value : 8bits Reas Once Num
//--------------------------------------------------
DWORD ScalerBW32GetDdrReadOnceNumSetting(void)
{
    return (Scaler32GetDWord(PA20002_08_BW32_CTRL) & 0x000000FF);
}

//--------------------------------------------------
// Description  : Set Burst Write MBIST Test Setting
// Input Value  : ulRegValue --> MBIST Test Setting
// Output Value : None
//--------------------------------------------------
void ScalerBW32SetMBistMode(DWORD ulRegValue)
{
    Scaler32SetDWord(PA20002_B0_BW32_MBIST_MODE, ulRegValue);
}

//--------------------------------------------------
// Description  : Get Burst Write MBIST Test Setting
// Input Value  : None
// Output Value : MBIST Test Setting
//--------------------------------------------------
DWORD ScalerBW32GetMBistMode(void)
{
    return Scaler32GetDWord(PA20002_B0_BW32_MBIST_MODE);
}

#endif  // End of #if(_HW_CPU32_BW32_SUPPORT == _ON)
