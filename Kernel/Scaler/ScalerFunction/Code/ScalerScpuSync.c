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
// ID Code      : ScalerScpuSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "ScpuSync/ScalerScpuSync.h"

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
// Define SCPU Sync Relative Info
volatile StructCpuCmdSyncInfo g_stScpuSyncCmdInfo;

// Define SCPU to KCPU Request Command Temp Buffer
volatile StructCpuSyncRequestCmd g_stScpuSyncToKcpuCmdTempBuffer;

volatile StructCpuSyncRequestCmd *const g_pstScpuSyncToKcpuCmd = ((StructCpuSyncRequestCmd *)(&g_stScpuSyncToKcpuCmdTempBuffer)); // TR9 => 3081


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : CPU Communication Handler Process in mainloop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerScpuSyncHandler(void)
{
    do
    {
        if(GET_KCPU_NOTIFY_INT_MORE_PROCESS_FLAG() == _TRUE)
        {
            if((GET_KCPU_NOTIFY_INT_CMD_TYPE() > _SCALER_CPU_SYNC_COLOR_START) &&
               (GET_KCPU_NOTIFY_INT_CMD_TYPE() < _SCALER_CPU_SYNC_COLOR_MAX))
            {
                ScalerColorScpuSyncHandler();
            }

            CLR_KCPU_NOTIFY_INT_MORE_PROCESS_FLAG();
            ACK_KCPU_NOTIFY_INT_CMD();
        }
    } while(g_bDebugHalt != _FALSE);
}

//--------------------------------------------------
// Description  : Fast Communication Handler in ITCM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerScpuSyncIntFastCommHandler(void)
{
    bit bProcessDone = _TRUE;

    switch(GET_KCPU_NOTIFY_INT_CMD_TYPE())
    {
        case _SYSTEM_CPU_SYNC_SHUTDOWN:
            // SEND:(KCPU -> SCPU)
            // MCU_SIDE_BUF_0:_SYSTEM_CPU_SYNC_SHUTDOWN
            // MCU_SIDE_BUF_1:McuExecCmdSeqNum
            // Disable CPU32 side WDT
            DISABLE_CPU32_WDT();

            // Disable All interrupt
            SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

#if(_HW_CPU32_BW32_SUPPORT == _ON)
            // Wait for BW32 become idle
            WAIT_BW32_IDLE();
#endif
            // ACK:(SCPU -> KCPU)
            // CPU32_SIDE_BUF_15:McuExecCmdSeqNum
            ACK_KCPU_NOTIFY_INT_CMD();

            // loop here waiting for shut done
            while(_TRUE)
            {
                CPU32_WAIT_FOR_INTERRUPT();
            }
            break;

        case _SCALER_CPU_SYNC_READ_DWORD:
            // SEND:(KCPU -> SCPU)
            // MCU_SIDE_BUF_0:_SCALER_CPU_SYNC_READ_DWORD
            // MCU_SIDE_BUF_1:McuExecCmdSeqNum
            // MCU_SIDE_BUF_2:ADDR[31:24]
            // MCU_SIDE_BUF_3:ADDR[23:16]
            // MCU_SIDE_BUF_4:ADDR[15:8]
            // MCU_SIDE_BUF_5:ADDR[7:0]
            // ACK:(SCPU -> KCPU)
            // CPU32_SIDE_BUF_0:R_DATA[31:24]
            // CPU32_SIDE_BUF_1:R_DATA[23:16]
            // CPU32_SIDE_BUF_2:R_DATA[15:8]
            // CPU32_SIDE_BUF_3:R_DATA[7:0]
            // CPU32_SIDE_BUF_15:McuExecCmdSeqNum
        {
            // SCPU Cache flush
            ScalerCpuHalCleanDataCache();
            ScalerCpuHalResetDataCache();

            DWORD ulTmpDWORD = Scaler32GetDWord(TO_DWORD(g_stCpuSyncToScpuCmd.unCmdBody.stReadCmd.pucAddr[0],
                                                         g_stCpuSyncToScpuCmd.unCmdBody.stReadCmd.pucAddr[1],
                                                         g_stCpuSyncToScpuCmd.unCmdBody.stReadCmd.pucAddr[2],
                                                         g_stCpuSyncToScpuCmd.unCmdBody.stReadCmd.pucAddr[3]));

            g_stCpuSyncToScpuCmdReply.unCmdBody.stReadReplyCmd.pucReadData[0] = ((ulTmpDWORD >> 24) & 0xFF);
            g_stCpuSyncToScpuCmdReply.unCmdBody.stReadReplyCmd.pucReadData[1] = ((ulTmpDWORD >> 16) & 0xFF);
            g_stCpuSyncToScpuCmdReply.unCmdBody.stReadReplyCmd.pucReadData[2] = ((ulTmpDWORD >> 8) & 0xFF);
            g_stCpuSyncToScpuCmdReply.unCmdBody.stReadReplyCmd.pucReadData[3] = ((ulTmpDWORD) & 0xFF);
            ACK_KCPU_NOTIFY_INT_CMD();
            break;
        }

        case _SCALER_CPU_SYNC_WRITE_DWORD:
            // SEND:(KCPU -> SCPU)
            // MCU_SIDE_BUF_0:_SCALER_CPU_SYNC_WRITE_DWORD
            // MCU_SIDE_BUF_1:McuExecCmdSeqNum
            // MCU_SIDE_BUF_2:ADDR[31:24]
            // MCU_SIDE_BUF_3:ADDR[23:16]
            // MCU_SIDE_BUF_4:ADDR[15:8]
            // MCU_SIDE_BUF_5:ADDR[7:0]
            // MCU_SIDE_BUF_6:W_DATA[31:24]
            // MCU_SIDE_BUF_7:W_DATA[23:16]
            // MCU_SIDE_BUF_8:W_DATA[15:8]
            // MCU_SIDE_BUF_9:W_DATA[7:0]
            // ACK:(SCPU -> KCPU)
            // CPU32_SIDE_BUF_15:McuExecCmdSeqNum
            Scaler32SetDWord(TO_DWORD(g_stCpuSyncToScpuCmd.unCmdBody.stWriteCmd.pucAddr[0],
                                      g_stCpuSyncToScpuCmd.unCmdBody.stWriteCmd.pucAddr[1],
                                      g_stCpuSyncToScpuCmd.unCmdBody.stWriteCmd.pucAddr[2],
                                      g_stCpuSyncToScpuCmd.unCmdBody.stWriteCmd.pucAddr[3]),
                             TO_DWORD(g_stCpuSyncToScpuCmd.unCmdBody.stWriteCmd.pucWriteData[0],
                                      g_stCpuSyncToScpuCmd.unCmdBody.stWriteCmd.pucWriteData[1],
                                      g_stCpuSyncToScpuCmd.unCmdBody.stWriteCmd.pucWriteData[2],
                                      g_stCpuSyncToScpuCmd.unCmdBody.stWriteCmd.pucWriteData[3]));

            // SCPU Cache flush
            ScalerCpuHalCleanDataCache();

            ACK_KCPU_NOTIFY_INT_CMD();
            break;

        default:
            bProcessDone = _FALSE;
            break;
    }

    return bProcessDone;
}


//--------------------------------------------------
// Description  : Wait command be executed by CPU32 CPU
// Input Value  : ulWaitTimeout --> wait timeout (unit: ms)
// Output Value : None
//--------------------------------------------------
bit ScalerScpuSyncPollingByteProc(DWORD ulWaitTimeout)
{
    if(ulWaitTimeout == _SCALER_CPU_SYNC_TIMEOUT_NO_WAIT)
    {
        return _FALSE;
    }
    else
    {
        DWORD ulTimeElapsed = 0;
        WORD usPreviousTime = g_usTimerCounter;

        do
        {
            if(g_stCpuSyncToKcpuCmd.stCmdHeader.ucCmdSeqNum == g_stCpuSyncToKcpuCmdReply.ucAckCmdSeqNum)
            {
                return _TRUE;
            }

            if(usPreviousTime != g_usTimerCounter)
            {
                ulTimeElapsed++;
                usPreviousTime = g_usTimerCounter;
            }
        }
        while(ulTimeElapsed <= ulWaitTimeout);

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : CPU Communication Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerScpuSyncInitial(void)
{
    // Enable and Clear interrupt flag
    // Enable CPU_Notify INT
    ScalerCpuHalEnableIRQ(_IRQN_CPU_NOTIFY);
    // Ack INT
    ScalerMiscCtrlAckNotifyFromKCPU();
}

//--------------------------------------------------
// Description  : SCPU Send Notify Cmd To KCPU
// Input Value  : enumScalerSyncCmdType --> Cmd Type
//                enumScalerLayerSyncCommandTypeTimeOut --> Cmd Timeout
//                punScpuSyncToKcpuCmdReplyBody --> ToKcpuCmdReplyBody Buffer
// Output Value : execute status
//--------------------------------------------------
bit ScalerScpuSyncSendCmd(EnumCpuSyncCommand enumScalerSyncCmdType, EnumCpuSyncCommandTimeOut enumScalerSyncCmdTypeTimeOut, UnionCpuSyncReplyCmdBody *punScpuSyncToKcpuCmdReplyBody)
{
    WORD usTempTime = g_usTimerCounter;

    StructCpuSyncRequestCmd stTmpCpuSyncRequestCmd;

    memcpy(&stTmpCpuSyncRequestCmd, g_pstScpuSyncToKcpuCmd, sizeof(StructCpuSyncRequestCmd));

    // Acquire CPU Notify resource lock
    if(RESOURCE_ACQUIRE(_RESOURCE_ID_TO_KCPU_NOTIFY, ((DWORD)enumScalerSyncCmdTypeTimeOut * 100)) == _FALSE)
    {
        return _FALSE;
    }

    // Assign Cmd Type
    stTmpCpuSyncRequestCmd.stCmdHeader.ucCmdType = enumScalerSyncCmdType;

    // Assign Mew CMD Request Number for New CMD
    stTmpCpuSyncRequestCmd.stCmdHeader.ucCmdSeqNum = g_stCpuSyncToKcpuCmdReply.ucAckCmdSeqNum + 1;


    memcpy(&g_stCpuSyncToKcpuCmd, &stTmpCpuSyncRequestCmd, sizeof(StructCpuSyncRequestCmd));

    SET_SCPU_REQUEST_IRQ_TO_KCPU();


    if(enumScalerSyncCmdTypeTimeOut == _SCALER_CPU_SYNC_TIMEOUT_NO_WAIT)
    {
        // no wait
        usTempTime = _SCALER_CPU_SYNC_TIMEOUT_NO_WAIT;
    }
    else
    {
        WORD usDuration = abs(g_usTimerCounter - usTempTime);

        if((WORD)enumScalerSyncCmdTypeTimeOut > usDuration)
        {
            usTempTime = (WORD)enumScalerSyncCmdTypeTimeOut - usDuration;
        }
        else
        {
            // time out flow
            usTempTime = 1;
        }
    }

    // Wait KCPU Side Ack
    bit bstatus = ScalerScpuSyncPollingByteProc(usTempTime);
    if((bstatus == _TRUE) && (punScpuSyncToKcpuCmdReplyBody != _NULL_POINTER))
    {
        memcpy(punScpuSyncToKcpuCmdReplyBody, &g_stCpuSyncToKcpuCmdReply.unCmdBody, sizeof(UnionCpuSyncReplyCmdBody));
    }

    RESOURCE_RELEASE(_RESOURCE_ID_TO_KCPU_NOTIFY);
    return bstatus;
}

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : CPU32 Send Flash Write Cmd
// Input Value  : ulFlash24BitAddr --> Flash 24bits address
//                ucLength --> Flash Data Byte Length(1~9)
//                pucFlashData --> FlashData Byte Array
// Output Value : none
//--------------------------------------------------
BYTE ScalerScpuSyncIntFlashWriteCmd(DWORD ulFlash24BitAddr, BYTE ucLength, BYTE *pucFlashData, bit bEnFlashSR, bit bDisFlashSR)
{
    // SEND:(SCPU -> KCPU)
    // CPU32_SIDE_BUF_0:_CPU_CMD_CPU32_FLASH_WRITE
    // CPU32_SIDE_BUF_1:Cpu32ExecCmdSeqNum
    // CPU32_SIDE_BUF_2:FlashBank
    // CPU32_SIDE_BUF_3:FlashADDR[15:8]
    // CPU32_SIDE_BUF_4:FlashADDR[7:0]
    // CPU32_SIDE_BUF_5:Length(1~9)
    // CPU32_SIDE_BUF_6:Data0
    // CPU32_SIDE_BUF_7:Data1
    // CPU32_SIDE_BUF_8:Data2
    // CPU32_SIDE_BUF_9:Data3
    // CPU32_SIDE_BUF_10:Data4
    // CPU32_SIDE_BUF_11:Data5
    // CPU32_SIDE_BUF_12:Data6
    // CPU32_SIDE_BUF_13:Data7
    // CPU32_SIDE_BUF_14:Data8
    // ACK:(KCPU -> SCPU)
    // MCU_SIDE_BUF_0:ExecStatus(_TRUE/_FALSE)
    // MCU_SIDE_BUF_15:Cpu32ExecCmdSeqNum

    g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashWriteCmd.pucAddr[0] = ((ulFlash24BitAddr >> 16) & 0xFF);
    g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashWriteCmd.pucAddr[1] = ((ulFlash24BitAddr >> 8) & 0xFF);
    g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashWriteCmd.pucAddr[2] = ((ulFlash24BitAddr) & 0xFF);
    g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashWriteCmd.ucLength = ucLength;
    g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashWriteCmd.bEnFlashSR = bEnFlashSR;
    g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashWriteCmd.bDisFlashSR = bDisFlashSR;

    for(BYTE ucIdx = 0; ucIdx < ucLength; ucIdx++)
    {
        g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashWriteCmd.pucWriteData[ucIdx] = pucFlashData[ucIdx];
    }
    UnionCpuSyncReplyCmdBody unScpuSyncToKcpuCmdReplyBody = {0};
    ScalerScpuSyncSendCmd(_SCALER_CPU_SYNC_FLASH_WRITE, _SCALER_CPU_SYNC_TIMEOUT_FLASH_WRITE, &unScpuSyncToKcpuCmdReplyBody);

    return unScpuSyncToKcpuCmdReplyBody.stFlashWriteReplyCmd.ucWriteStatus;
}

//--------------------------------------------------
// Description  : CPU32 Send Flash erase page Cmd
// Input Value  : usBank --> Flash bank
//                ucPage --> Flash page
// Output Value : none
//--------------------------------------------------
BYTE ScalerScpuSyncIntErasePageCmd(WORD usBank, BYTE ucPage)
{
    g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashErasePageCmd.usBank = usBank;
    g_pstScpuSyncToKcpuCmd->unCmdBody.stFlashErasePageCmd.ucPage = ucPage;

    UnionCpuSyncReplyCmdBody unScpuSyncToKcpuCmdReplyBody = {0};
    ScalerScpuSyncSendCmd(_SCALER_CPU_SYNC_FLASH_PAGE_ERASE, _SCALER_CPU_SYNC_TIMEOUT_FLASH_WRITE, &unScpuSyncToKcpuCmdReplyBody);

    return unScpuSyncToKcpuCmdReplyBody.stFlashWriteReplyCmd.ucWriteStatus;
}
#endif

#endif  // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
