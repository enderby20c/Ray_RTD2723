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
// ID Code      : ScalerRBusToDdr.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "RBusToDdr/ScalerRBusToDdr.h"

#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile bit g_pbRBusToDdrAddrAutoInc[3];
volatile BYTE g_pucRBusToDdrRemainRegNum[3];
volatile DWORD g_pulRBusToDdrRemainRegSrcAddr[3];
volatile DWORD g_pulRBusToDdrRemainDdrDestAddr[3];

EnumRBusToDdrCallbackFuncId g_enumRBusToDdrCallbackFuncId = _RBUS_TO_DDR_CALLBACK_NULL;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRBusToDdrCallbackFunction(void)
{
    EnumRBusToDdrCallbackFuncId enumRBusToDdrCallbackFuncId = g_enumRBusToDdrCallbackFuncId;
    g_enumRBusToDdrCallbackFuncId = _RBUS_TO_DDR_CALLBACK_NULL;
    switch(enumRBusToDdrCallbackFuncId)
    {
        case _RBUS_TO_DDR_CALLBACK_NULL:
        default:
            break;
    }
}


//--------------------------------------------------
// Description  : RBUS2DDR Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRBusToDdr_IRQHandler(void)
{
    if(ScalerRBusToDdrGetFinishINTFlag() != 0)
    {
        // Ack Flag
        ScalerRBusToDdrAckFinishINTFlag();

        if(ScalerRBusToDdrChkAllDone() == 0)
        {
            ScalerRBusToDdrPostProcess();

            // Release RBUS2DDR resource lock
            RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);

            if(g_enumRBusToDdrCallbackFuncId != _RBUS_TO_DDR_CALLBACK_NULL)
            {
                ScalerRBusToDdrCallbackFunction();
            }
        }
    }
    else
    {
        // Error Source Address Check
        ScalerRBusToDdrError_Handler();

        // Force Release RBUS2DDR resource lock when RBUS2DDR Failed
        RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
    }
}

//--------------------------------------------------
// Description  : RBUS2DDR Error Handler
// Input Value  : None
// Output Value : 0:No Error Happened , 1: Invalid Address Happened
//--------------------------------------------------
bit ScalerRBusToDdrError_Handler(void)
{
    if(Scaler32GetBit(PA20003_50_RBUS2DDR_ERR_SRC_CTRL, (_BIT16 | _BIT8 | _BIT0)) != 0)
    {
        ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_RBUS2DDR_SRC_ADDR);
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Launch RBUS2DDR Command
// Input Value  :
//    ucTotalCmdXcnt --> RBUS2DDR CmdX use Number
//    pstRbus2DdrCmdInfo :
//              ->stRBus2DdrBaseInfo:
//                  ->ulDdrDestAddr --> DDR Address of RBUS2DDR Destination Address
//                  ->ulRBusSrcStartAddress --> RBUS2DDR RBUSD Sourec Reg Start Address
//                  ->ulTotalRegNum --> Total 32bits Reg Number want to read out
//                  ->bAddrAutoInc --> is Address Auto Increase
//              ->enumRBus2DdrTriggerSource --> RBUS2DDR trigger source(manual/dvs...)
//    usWaitResourceLockTimeoutMS --> Wait Timeout MS Counter for Waiting RBusToDdr Resource Lock
//    bWaitExecuteDone --> Sync Wait RBUS2DDR Execute done
//    usWaitExeTimeoutMS --> Wait Timeout MS Counter for Sync Waiting RBUS2DDR Execute done
//    pCallBackFuncPtr --> if Use NoWait, RBUS2DDR will execute call back function in RBUS2DDR finish INT
// Output Value : _TRUE:Success ; _FALSE:Failed
//--------------------------------------------------
bit ScalerRBusToDdrLaunchCmdX(BYTE ucTotalCmdXcnt, StructRBus2DdrCmdInfo *pstRbus2DdrCmdInfo, WORD usWaitResourceLockTimeoutMS, bit bWaitExecuteDone, WORD usWaitExeTimeoutMS, EnumRBusToDdrCallbackFuncId enumCallbackFuncId)
{
    if(ScalerRBusToDdrPrepareCmdX(ucTotalCmdXcnt, pstRbus2DdrCmdInfo, usWaitResourceLockTimeoutMS) == _TRUE)
    {
        return ScalerRBusToDdrExecuteCmdX(ucTotalCmdXcnt, pstRbus2DdrCmdInfo, bWaitExecuteDone, usWaitExeTimeoutMS, enumCallbackFuncId);
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Launch RBUS2DDR Command After IDomain Event
// Input Value  :
//    pstBW32IDomainCmdInfo :
//              ->stRBus2DdrBaseInfo:
//                  ->ulDdrDestAddr --> DDR Address of RBUS2DDR Destination Address
//                  ->ulRBusSrcStartAddress --> RBUS2DDR RBUSD Sourec Reg Start Address
//                  ->ulTotalRegNum --> Total 32bits Reg Number want to read out
//                  ->bAddrAutoInc --> is Address Auto Increase
//              ->enumWaitIDomainEvent --> I-Domain Specified event
//              ->enumInputDataPath --> I-Domain Data Path
//    usWaitResourceLockTimeoutMS --> Wait Timeout MS Counter for Waiting RBusToDdr Resource Lock
//    usWaitExeTimeoutMS --> Wait Timeout MS Counter for Sync Waiting RBUS2DDR Execute done
// Output Value : _TRUE:Success ; _FALSE:Failed
//--------------------------------------------------
bit ScalerRBusToDdrLaunchCmdXAfterIDomainEvent(StructRBus2DdrIDomainCmdInfo *pstRBus2DdrIDomainCmdInfo, WORD usWaitResourceLockTimeoutMS, WORD usWaitExeTimeoutMS)
{
    StructRBus2DdrCmdInfo stRBus2DdrCmdInfo;
    memcpy(&stRBus2DdrCmdInfo.stRBus2DdrBaseInfo, &pstRBus2DdrIDomainCmdInfo->stRBus2DdrBaseInfo, sizeof(StructRBus2DdrBaseInfo));
    stRBus2DdrCmdInfo.enumRBus2DdrTriggerSource = _RBUS2DDR_TRIGGER_MANUAL;

    if(ScalerRBusToDdrPrepareCmdX(1, &stRBus2DdrCmdInfo, usWaitResourceLockTimeoutMS) == _TRUE)
    {
        if(ScalerTimerWaitForIDomainEvent(pstRBus2DdrIDomainCmdInfo->enumWaitIDomainEvent, pstRBus2DdrIDomainCmdInfo->enumInputDataPath) == _TRUE)
        {
            return ScalerRBusToDdrExecuteCmdX(1, &stRBus2DdrCmdInfo, _TRUE, usWaitExeTimeoutMS, _RBUS_TO_DDR_CALLBACK_NULL);
        }
        RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Prepare RBUS2DDR Command
// Input Value  :
//    ucTotalCmdXcnt --> RBUS2DDR CmdX use Number
//    pstRbus2DdrCmdInfo :
//              ->stRBus2DdrBaseInfo:
//                  ->ulDdrDestAddr --> DDR Address of RBUS2DDR Destination Address
//                  ->ulRBusSrcStartAddress --> RBUS2DDR RBUSD Sourec Reg Start Address
//                  ->ulTotalRegNum --> Total 32bits Reg Number want to read out
//                  ->bAddrAutoInc --> is Address Auto Increase
//              ->enumRBus2DdrTriggerSource --> RBUS2DDR trigger source(manual/dvs...)
//    usWaitResourceLockTimeoutMS --> Wait Timeout MS Counter for Waiting RBusToDdr Resource Lock
// Output Value : _TRUE:Success ; _FALSE:Failed
//--------------------------------------------------
bit ScalerRBusToDdrPrepareCmdX(BYTE ucTotalCmdXcnt, StructRBus2DdrCmdInfo *pstRbus2DdrCmdInfo, WORD usWaitResourceLockTimeoutMS)
{
    DWORD ulRBUS2DDR_LEN = 4;

    // Acquire RBUS2DDR resource lock
    if(RESOURCE_ACQUIRE(_RESOURCE_ID_RBUS2DDR, (((DWORD)usWaitResourceLockTimeoutMS) * 100)) == _FALSE)
    {
        return _FALSE;
    }

    if(ucTotalCmdXcnt > 3)
    {
        DebugMessageCpu32("ERROR:RBUS2DDR TotalCmdXcnt >3", ucTotalCmdXcnt);
        RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
        return _FALSE;
    }

    // calculate proper RBUS2DDR_LEN
    while(ulRBUS2DDR_LEN <= 124)
    {
        bit bDivPass = _TRUE;

        for(BYTE ucCmdIdx = 0; ucCmdIdx < ucTotalCmdXcnt; ucCmdIdx++)
        {
            if((((RBUS2DDR_DDR_ARRAY_SIZE(pstRbus2DdrCmdInfo[ucCmdIdx].stRBus2DdrBaseInfo.ulTotalRegNum) * 8) / 2) % ulRBUS2DDR_LEN) != 0)
            {
                bDivPass = _FALSE;
                ulRBUS2DDR_LEN -= 4;
                break;
            }
        }

        if(bDivPass == _FALSE)
        {
            break;
        }
        else
        {
            ulRBUS2DDR_LEN += 4;
        }
    }


    for(BYTE ucCmdIdx = 0; ucCmdIdx < ucTotalCmdXcnt; ucCmdIdx++)
    {
        DWORD ulRBUS2DDR_BLOCK_NUM = 0;
        DWORD ulRemainRegNum = 0;
        StructRBus2DdrBaseInfo *pstBaseInfo = (StructRBus2DdrBaseInfo *)&pstRbus2DdrCmdInfo[ucCmdIdx].stRBus2DdrBaseInfo;
        DWORD ulDdrDestAddr = (DWORD)pstBaseInfo->pstRbus2DdrDestAddr;

        if(((ulDdrDestAddr & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0) ||
           (ulDdrDestAddr < _CPU32_DDR_PHYSICS_OFFSET))
        {
            // Start Address of RBUS2DDR Command table mus be align to 32 (StartAddress[4:0] must be 0)
            DebugMessageCpu32("ERROR:Start Address of RBUS2DDR Command table mus be align to 32 (StartAddress[4:0] must be 0)", ulDdrDestAddr);
            RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
            return _FALSE;
        }

        if(pstBaseInfo->ulTotalRegNum < 8)
        {
            // total Reg Num must larger than 8
            DebugMessageCpu32("ERROR:RBUS2DDR total Reg Num must larger than 8", pstBaseInfo->ulTotalRegNum);
            RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
            return _FALSE;
        }

        if(pstBaseInfo->ulTotalRegNum > ((_MAX_RBUS2DDR_LEN * 2) * _MAX_RBUS2DDR_NUM_CMD))
        {
            // total Num must be even and can be divided by 4 for use
            DebugMessageCpu32("ERROR:RBUS2DDR total Reg Num too large!!", pstBaseInfo->ulTotalRegNum);
            RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
            return _FALSE;
        }

        if(ulRBUS2DDR_LEN != 0)
        {
            ulRBUS2DDR_BLOCK_NUM = (pstBaseInfo->ulTotalRegNum / (ulRBUS2DDR_LEN * 2));
        }
        else
        {
            // ulRBUS2DDR_LEN is zero
            DebugMessageCpu32("ERROR:ulRBUS2DDR_LEN is 0!!", ulRBUS2DDR_LEN);
            RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
            return _FALSE;
        }
        ulRemainRegNum = (pstBaseInfo->ulTotalRegNum % (ulRBUS2DDR_LEN * 2));

        if(ulRemainRegNum != 0)
        {
            DWORD ulAddrOffset = (ulRBUS2DDR_LEN * 2) * ulRBUS2DDR_BLOCK_NUM;

            g_pucRBusToDdrRemainRegNum[ucCmdIdx] = ulRemainRegNum;
            g_pbRBusToDdrAddrAutoInc[ucCmdIdx] = pstBaseInfo->bAddrAutoInc;
            if(pstBaseInfo->bAddrAutoInc == _TRUE)
            {
                g_pulRBusToDdrRemainRegSrcAddr[ucCmdIdx] = pstBaseInfo->ulRBusSrcStartAddress + ulAddrOffset;
            }
            else
            {
                g_pulRBusToDdrRemainRegSrcAddr[ucCmdIdx] = pstBaseInfo->ulRBusSrcStartAddress;
            }
            g_pulRBusToDdrRemainDdrDestAddr[ucCmdIdx] = ulDdrDestAddr + ulAddrOffset;
        }
        else
        {
            g_pucRBusToDdrRemainRegNum[ucCmdIdx] = 0;
        }

        // Address Auto Increase
        Scaler32SetBit(PA20003_30_RBUS2DDR_MODE_CTRL, ~((_BIT7) << (ucCmdIdx * 8)), ((((DWORD)(pstBaseInfo->bAddrAutoInc)) << 7) << (ucCmdIdx * 8)));

        // RBUS Source Address
        Scaler32SetDWord((PA20003_40_RBUS2DDR_DATA_SRC_ADDR0 + (ucCmdIdx * 4)), pstBaseInfo->ulRBusSrcStartAddress);

        // DDR Dest Address
        Scaler32SetDWord((PA20003_20_RBUS2DDR_ADDR0 + (ucCmdIdx * 4)), (ulDdrDestAddr - _CPU32_DDR_PHYSICS_OFFSET));

        switch(ucCmdIdx)
        {
            case _RBUS2DDR_CMD0:
                Scaler32SetBit(PA20003_10_RBUS2DDR_NUM0, ~(0x00000FFF), ulRBUS2DDR_BLOCK_NUM);
                break;

            case _RBUS2DDR_CMD1:
                Scaler32SetBit(PA20003_10_RBUS2DDR_NUM0, ~(0x0FFF0000), (ulRBUS2DDR_BLOCK_NUM << 16));
                break;

            case _RBUS2DDR_CMD2:
                Scaler32SetBit(PA20003_14_RBUS2DDR_NUM1, ~(0x00000FFF), ulRBUS2DDR_BLOCK_NUM);
                break;

            default:
                RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
                return _FALSE;
        }
    }

    Scaler32SetDWord(PA20003_08_RBUS2DDR_CTRL, ((DWORD)ulRBUS2DDR_LEN));

    return _TRUE;
}


//--------------------------------------------------
// Description  : Execute RBUS2DDR Command
// Input Value  :
//    ucTotalCmdXcnt --> RBUS2DDR CmdX use Number
//    pstRbus2DdrCmdInfo :
//              ->stRBus2DdrBaseInfo:
//                  ->ulDdrDestAddr --> DDR Address of RBUS2DDR Destination Address
//                  ->ulRBusSrcStartAddress --> RBUS2DDR RBUSD Sourec Reg Start Address
//                  ->ulTotalRegNum --> Total 32bits Reg Number want to read out
//                  ->bAddrAutoInc --> is Address Auto Increase
//              ->enumRBus2DdrTriggerSource --> RBUS2DDR trigger source(manual/dvs...)
//    bWaitExecuteDone --> Sync Wait RBUS2DDR Execute done
//    usWaitExeTimeoutMS --> Wait Timeout MS Counter for Sync Waiting RBUS2DDR Execute done
//    pCallBackFuncPtr --> if Use NoWait, RBUS2DDR will execute call back function in RBUS2DDR finish INT
// Output Value : _TRUE:Success ; _FALSE:Failed
//--------------------------------------------------
bit ScalerRBusToDdrExecuteCmdX(BYTE ucTotalCmdXcnt, StructRBus2DdrCmdInfo *pstRbus2DdrCmdInfo, bit bWaitExecuteDone, WORD usWaitExeTimeoutMS, EnumRBusToDdrCallbackFuncId enumCallbackFuncId)
{
    DWORD ulRBUS2DDR_ManulTrigger = 0;
    bit bAllManualTrigger = _TRUE;

    enumCallbackFuncId = enumCallbackFuncId;

    for(BYTE ucCmdIdx = 0; ucCmdIdx < ucTotalCmdXcnt; ucCmdIdx++)
    {
        if(pstRbus2DdrCmdInfo[ucCmdIdx].enumRBus2DdrTriggerSource == _RBUS2DDR_TRIGGER_MANUAL)
        {
            ulRBUS2DDR_ManulTrigger |= (_BIT0 << ucCmdIdx);
        }
        else
        {
            bAllManualTrigger = _FALSE;
        }
    }

    if(bWaitExecuteDone == _FALSE)
    {
        // RBUS2DDR use Finish INT(ACK && Enable BW32 INT)
        Scaler32SetDWord(PA20003_00_RBUS2DDR_TOP_CTRL, (_BIT12 | _BIT8));
        g_enumRBusToDdrCallbackFuncId = enumCallbackFuncId;
    }
    else
    {
        // Busy Wait RBUS2DDR execute done(ACK RBUS2DDR INT FLAG)
        Scaler32SetDWord(PA20003_00_RBUS2DDR_TOP_CTRL, _BIT8);
        g_enumRBusToDdrCallbackFuncId = _RBUS_TO_DDR_CALLBACK_NULL;
    }

    // force d-cache sync to DDR
    ScalerCpuHalCleanDataCache();

    // Launch RbusToDdr cmdX
    if(bAllManualTrigger == _TRUE)
    {
        // all cmd are manual triggered
        Scaler32SetBit(PA20003_00_RBUS2DDR_TOP_CTRL, ~(_BIT8 | _BIT2 | _BIT1 | _BIT0), ulRBUS2DDR_ManulTrigger);
    }
    else
    {
        for(BYTE ucCmdIdx = 0; ucCmdIdx < ucTotalCmdXcnt; ucCmdIdx++)
        {
            ScalerRBusToDdrSetCmdTriggerSource(ucCmdIdx, pstRbus2DdrCmdInfo[ucCmdIdx].enumRBus2DdrTriggerSource);
        }
    }

    if(bWaitExecuteDone == _TRUE)
    {
        WORD usPreviousTime = g_usTimerCounter;

        while(usWaitExeTimeoutMS != 0)
        {
            if(ScalerRBusToDdrChkAllDone() == 0)
            {
                ScalerRBusToDdrPostProcess();

                RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
                return _TRUE;
            }
            // _MAX_RBUS2DDR_LEN * 103.2ns(read DWORD share ram) = 12.8us
            ScalerMcuDelayXus(13);

            if(usPreviousTime != g_usTimerCounter)
            {
                usWaitExeTimeoutMS--;
                usPreviousTime = g_usTimerCounter;
            }
        }

        RESOURCE_RELEASE(_RESOURCE_ID_RBUS2DDR);
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : RBusToDdr Post Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRBusToDdrPostProcess(void)
{
    // process remain regs
    for(DWORD ulIdx = 0; ulIdx < 3; ulIdx++)
    {
        if(g_pucRBusToDdrRemainRegNum[ulIdx] != 0)
        {
            DWORD ulRegIdx = 0;
            DWORD *pulDdrDestAddrPtr = (DWORD *)g_pulRBusToDdrRemainDdrDestAddr[ulIdx];
            if(g_pbRBusToDdrAddrAutoInc[ulIdx] == _TRUE)
            {
                while(ulRegIdx < g_pucRBusToDdrRemainRegNum[ulIdx])
                {
                    pulDdrDestAddrPtr[ulRegIdx] = Scaler32GetDWord((g_pulRBusToDdrRemainRegSrcAddr[ulIdx] + (ulRegIdx << 2)));
                    ulRegIdx++;
                }
            }
            else
            {
                while(ulRegIdx < g_pucRBusToDdrRemainRegNum[ulIdx])
                {
                    pulDdrDestAddrPtr[ulRegIdx] = Scaler32GetDWord(g_pulRBusToDdrRemainRegSrcAddr[ulIdx]);
                    ulRegIdx++;
                }
            }

            g_pucRBusToDdrRemainRegNum[ulIdx] = 0;
        }
    }

    // force d-cache sync to DDR
    ScalerCpuHalCleanDataCache();

    // Reset Data Cache
    ScalerCpuHalResetDataCache();
}

//--------------------------------------------------
// Description  : Enable RBUS2DDR Finish Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRBusToDdrEnableFinishINT(void)
{
    Scaler32SetBit(PA20003_00_RBUS2DDR_TOP_CTRL, ~(_BIT12 | _BIT8 | _BIT2 | _BIT1 | _BIT0), _BIT12);
}

//--------------------------------------------------
// Description  : Disable RBUS2DDR Finish Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRBusToDdrDisableFinishINT(void)
{
    Scaler32SetBit(PA20003_00_RBUS2DDR_TOP_CTRL, ~(_BIT12 | _BIT8 | _BIT2 | _BIT1 | _BIT0), 0);
}

//--------------------------------------------------
// Description  : Get RBUS2DDR Finish Interrupt Flag
// Input Value  : None
// Output Value : 0:not happened ; other:happened
//--------------------------------------------------
DWORD ScalerRBusToDdrGetFinishINTFlag(void)
{
    return Scaler32GetBit(PA20003_00_RBUS2DDR_TOP_CTRL, _BIT8);
}

//--------------------------------------------------
// Description  : Ack RBUS2DDR Finish Interrupt Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerRBusToDdrAckFinishINTFlag(void)
{
    Scaler32SetBit(PA20003_00_RBUS2DDR_TOP_CTRL, ~(_BIT8 | _BIT2 | _BIT1 | _BIT0), _BIT8);

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}


//--------------------------------------------------
// Description  : Check if Cmd0 Block's RBUS2DDR operation finished?
// Input Value  : None
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
void ScalerRBusToDdrSetCmdTriggerSource(EnumRBus2DdrCmdX enumRBus2DdrCmdX, EnumRBus2DdrTriggerSource enumRBus2DdrTriggerSource)
{
    if(enumRBus2DdrTriggerSource == _RBUS2DDR_TRIGGER_MANUAL)
    {
        Scaler32SetBit(PA20003_00_RBUS2DDR_TOP_CTRL, ~(_BIT8 | _BIT2 | _BIT1 | _BIT0), (_BIT12 | (_BIT0 << enumRBus2DdrCmdX)));
    }
    else
    {
        // DVS/DEB_START/DEN_STOP
        Scaler32SetBit(PA20003_70_RBUS2DDR_DOMAIN_EVENT_TRIGGER0 + (enumRBus2DdrCmdX * 4), ~(_BIT2 | _BIT1 | _BIT0), enumRBus2DdrTriggerSource);
    }
}

//--------------------------------------------------
// Description  : Check if Cmdx Block's RBUS2DDR operation finished?
// Input Value  : enumBW32CmdX --> BW32 cmdX
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
DWORD ScalerRBusToDdrChkCmdXManualDone(EnumRBus2DdrCmdX enumRBus2DdrCmdX)
{
    return Scaler32GetBit(PA20003_00_RBUS2DDR_TOP_CTRL, (_BIT0 << enumRBus2DdrCmdX));
}

//--------------------------------------------------
// Description  : Check if Cmd0 Block's RBUS2DDR operation finished?
// Input Value  : enumRbus2DdrCmdX --> RBUS2DDR cmdX
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
DWORD ScalerRBusToDdrChkCmdXDomainEventDone(EnumRBus2DdrCmdX enumRbus2DdrCmdX)
{
    return Scaler32GetDWord(PA20003_70_RBUS2DDR_DOMAIN_EVENT_TRIGGER0 + (enumRbus2DdrCmdX << 2));
}

//--------------------------------------------------
// Description  : Check if all RBUS2DDR operation finished?
// Input Value  : None
// Output Value : 0:done ; other:not yet
//--------------------------------------------------
DWORD ScalerRBusToDdrChkAllDone(void)
{
    return (Scaler32GetBit(PA20003_00_RBUS2DDR_TOP_CTRL, (_BIT2 | _BIT1 | _BIT0)) | Scaler32GetDWord(PA20003_70_RBUS2DDR_DOMAIN_EVENT_TRIGGER0) | Scaler32GetDWord(PA20003_74_RBUS2DDR_DOMAIN_EVENT_TRIGGER1) | Scaler32GetDWord(PA20003_78_RBUS2DDR_DOMAIN_EVENT_TRIGGER2));
}

//--------------------------------------------------
// Description  : Get RBUS2DDR Write Once Num setting
// Input Value  : None
// Output Value : 8bits write Once Num
//--------------------------------------------------
DWORD ScalerRBusToDdrGetDdrWriteOnceNumSetting(void)
{
    return (Scaler32GetDWord(PA20003_08_RBUS2DDR_CTRL) & 0x000000FF);
}

//--------------------------------------------------
// Description  : Set RBUS2DDR MBIST Test Setting
// Input Value  : ulRegValue --> MBIST Test Setting
// Output Value : None
//--------------------------------------------------
void ScalerRBusToDdrSetMBistMode(DWORD ulRegValue)
{
    Scaler32SetDWord(PA20003_B0_RBUS2DDR_MBIST_CTRL, ulRegValue);
}

//--------------------------------------------------
// Description  : Get RBUS2DDR MBIST Test Setting
// Input Value  : None
// Output Value : MBIST Test Setting
//--------------------------------------------------
DWORD ScalerRBusToDdrGetMBistMode(void)
{
    return Scaler32GetDWord(PA20003_B0_RBUS2DDR_MBIST_CTRL);
}


#endif  // End of #if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
