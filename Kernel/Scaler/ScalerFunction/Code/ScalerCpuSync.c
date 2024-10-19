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
// ID Code      : ScalerCpuSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_CPU32_SYNC__

#include "ScalerFunctionInclude.h"
#include "CpuSync/ScalerCpuSync.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
__attribute__((section(".fast_data.g_ulCpuSyncBusyDelayCnt")))
volatile DWORD g_ulCpuSyncBusyDelayCnt;
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
// Define KCPU to SCPU Request Command Buffer
volatile StructCpuSyncRequestCmd g_stCpuSyncToScpuCmd;
// Define KCPU to SCPU Reply Command Buffer
volatile StructCpuSyncReplyCmd g_stCpuSyncToScpuCmdReply;

// Define SCPU to KCPU Request Command Buffer
volatile StructCpuSyncRequestCmd g_stCpuSyncToKcpuCmd;
// Define SCPU to KCPU Reply Command Buffer
volatile StructCpuSyncReplyCmd g_stCpuSyncToKcpuCmdReply;


#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
// Define KCPU Sync Relative Info
volatile StructCpuCmdSyncInfo g_stCpuSyncCmdInfo;

// Define KCPU to SCPU Request Command Temp Buffer for User use Before ResourceLock
volatile StructCpuSyncRequestCmd g_stCpuSyncToScpuCmdTempBuffer;

// Define KCPU to SCPU Request Command Buffer Pointer
volatile StructCpuSyncRequestCmd *g_pstCpuSyncToScpuCmd = (&g_stCpuSyncToScpuCmdTempBuffer);
#endif

// Local Dimming
#if(_LOCAL_DIMMING_FUNCTION == _ON)
volatile bit g_bCpuSyncColorLocalDimmingRestoreBacklight;
#if(_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _OFF)
volatile bit g_bCpuSyncColorLocalDimmingSendAdimCmd;
#else
volatile bit g_bCpuSyncLedDriverBoostLock;
#endif
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : CPU Communication Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncHandler(void)
{
    if(GET_SCPU_NOTIFY_INT_CMD_TYPE() <= _SCALER_CPU_SYNC_COLOR_MAX)
    {
        ScalerCpuSyncColorHandler();
    }
    else
    {
        switch(GET_SCPU_NOTIFY_INT_CMD_TYPE())
        {
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
            case _SCALER_CPU_SYNC_FLASH_WRITE:
                ScalerCpuSyncFlashWriteHandler();
                break;
            case _SCALER_CPU_SYNC_FLASH_PAGE_ERASE:
                ScalerCpuSyncFlashPageEraseHandler();
                break;
#endif
            default:
                break;
        }
    }

    // Reply Ack
    ACK_SCPU_NOTIFY_INT_CMD();
}

//--------------------------------------------------
// Description  : CPU Communication interrupt Handler
// Input Value  : enumCpuSyncCommand
// Output Value : _TRUE=need execute ACK_SCPU_NOTIFY_INT_CMD()
//--------------------------------------------------
bit ScalerCpuSyncNotifyIntHandler(EnumCpuSyncCommand enumCpuSyncCommand)
{
    switch(enumCpuSyncCommand)
    {
        case _SCALER_CPU_SYNC_READ_DWORD:
            // Reply CPU32 Read Request Data
            SCPU_CMD_READ_DWORD_DATA();
            break;

        case _SCALER_CPU_SYNC_WRITE_DWORD:
            SCPU_CMD_WRITE_DWORD_DATA();
            break;
        case _SYSTEM_CPU_SYNC_WD_EVENT:
            switch(g_stCpuSyncToKcpuCmd.unCmdBody.stCpuSyncWDTimerEventCmd.enumWDTimerEventAction)
            {
                case _WD_TIMER_EVENT_ACTIVATE:
                    ScalerTimerWDActivateTimerEvent(g_stCpuSyncToKcpuCmd.unCmdBody.stCpuSyncWDTimerEventCmd.usTimeMS, (EnumScalerWDTimerEventID)g_stCpuSyncToKcpuCmd.unCmdBody.stCpuSyncWDTimerEventCmd.usEventID);
                    break;
                case _WD_TIMER_EVENT_CANCEL:
                    ScalerTimerWDCancelTimerEvent((EnumScalerWDTimerEventID)g_stCpuSyncToKcpuCmd.unCmdBody.stCpuSyncWDTimerEventCmd.usEventID);
                    break;
                default:
                    break;
            }
            break;

#if(_FW_CPU32_MAIN_PROCESS_CPU == _CPU_ID_KCPU)
#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _SCALER_CPU_SYNC_COLOR_ADVANCED_HDR10:
            if(GET_ADVANCED_HDR10_METADATA_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON)
            {
                if(g_stCpuSyncToKcpuCmd.unCmdBody.stColorAdvancedHDR10Cmd.ucSubCmdType == _ADVANCED_HDR10_APPLY)
                {
                    ACK_SCPU_NOTIFY_INT_CMD();
#if(_FRC_SUPPORT == _ON)
                    if(GET_ADVANCED_HDR10_FRC_STATUS() == _ADVANCED_HDR10_IN_SLOW)
                    {
                        EnumAdvancedHDR10PCMHLWDBStatus enumAdvancedHDR10PCMHLWDBStatus = _ADVANCED_HDR10_PCM_HLW_DB_UNKNOWN;
                        SET_ADVANCED_HDR10_NOTIFY_INT();
                        enumAdvancedHDR10PCMHLWDBStatus = ScalerColorAdvancedHDR10GetPCMHLWDBStatus(_ADVANCED_HDR10_PCM_HLW_DB_PROC_NORAML);
                        ScalerColorAdvancedHDR10PCMHLWDBProc(enumAdvancedHDR10PCMHLWDBStatus);
                        CLR_ADVANCED_HDR10_NOTIFY_INT();
                    }
                    else
#endif
                    {
                        BYTE ucAdvancedHDR10IGNorm = ScalerColorGetAdvancedHDR10InputGammaNorm();
                        EnumSelRegion enumSelRegion = _1P_NORMAL_REGION;
                        EnumHLWSetSel enumHLWSetSel = _HLW_INSIDEB_OUTSIDEA;
                        if(ScalerColorPCMInputGammaGetEffectiveRegion() == _HLW_INSIDEB_OUTSIDEA)
                        {
                            enumSelRegion = _DEMO_INSIDE;
                            enumHLWSetSel = _HLW_INSIDEA_OUTSIDEB;
                        }

                        ScalerColorPCMInputGammaAdjust(enumSelRegion, (BYTE *)(_OGC_ADVANCED_HDR10_IG_NOTM_DARK_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * ucAdvancedHDR10IGNorm), _OGC_FLASH_BANK, _IG_DB_DISABLE);
                        ScalerColorYMappingEnable(enumSelRegion, _FUNCTION_OFF);
                        if(ScalerColorYMappingLoadGainTable(enumSelRegion, g_pucSyncAdvancedHDR10YmTable, _YMAPPING_GAIN_TABLE_SIZE, 0x00, _BURSTWRITE_FROM_XRAM) == _SUCCESS)
                        {
                            ScalerColorYMappingEnable(enumSelRegion, _FUNCTION_ON);
                        }
                        ScalerColorPCMAdvancedHDR10SetEffectiveRegion(enumHLWSetSel, _DB_APPLY_NO_POLLING, _PCM_HLW_DB_A_OR_B);
                    }
                    return _FALSE;
                }
            }
            break;
#endif
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
        case _SCALER_CPU_SYNC_COLOR_LOCAL_DIMMING:
            switch(g_stCpuSyncToKcpuCmd.unCmdBody.stColorLocalDimmingCmd.ucSubCmdType)
            {
                case _LOCAL_DIMMING_BACKLIGHT_RESTORE:
                    g_bCpuSyncColorLocalDimmingRestoreBacklight = _TRUE;
                    ScalerCpuHalSetMainCpuSw0IRQ();
                    break;
#if(_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _OFF)
                case _LOCAL_DIMMING_BACKLIGHT_SEND_ADIM:
                    g_bCpuSyncColorLocalDimmingSendAdimCmd = _TRUE;
                    ScalerCpuHalSetMainCpuSw0IRQ();
                    break;
#endif
                default:
                    break;
            }
            break;
#endif

        default:
            // Command need to be advance processed
            SET_SCPU_NOTIFY_INT_MORE_PROCESS_FLAG();
            return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Color CPU Communication Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncColorHandler(void)
{
    switch(GET_SCPU_NOTIFY_INT_CMD_TYPE())
    {
        default:
            break;
    }
}

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Flash Write CPU Communication Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncFlashWriteHandler(void)
{
    // Execute Flash Write and Set Result status
    g_stCpuSyncToKcpuCmdReply.unCmdBody.stFlashWriteReplyCmd.ucWriteStatus = ScalerFlashWriteByKernel(GET_SCPU_NOTIFY_INT_FLASH_WRITE_BANK(), GET_SCPU_NOTIFY_INT_FLASH_WRITE_ADDR(), GET_SCPU_NOTIFY_INT_FLASH_WRITE_LENGTH(), (BYTE *)GET_SCPU_NOTIFY_INT_FLASH_WRITE_DATA_ADDR(), GET_SCPU_NOTIFY_INT_FLASH_WRITE_EN_FLASH_SR(), GET_SCPU_NOTIFY_INT_FLASH_WRITE_DIS_FLASH_SR());
}

//--------------------------------------------------
// Description  : Flash Write CPU Communication Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncFlashPageEraseHandler(void)
{
    g_stCpuSyncToKcpuCmdReply.unCmdBody.stFlashWriteReplyCmd.ucWriteStatus =
        ScalerFlashErasePage(g_stCpuSyncToKcpuCmd.unCmdBody.stFlashErasePageCmd.usBank,
                             g_stCpuSyncToKcpuCmd.unCmdBody.stFlashErasePageCmd.ucPage,
                             _TRUE, _TRUE);
}
#endif

//----------------------------------------------------------------------
// Description  : Polling Scaler Reg Process
// Input Value  : ulTimeout   --> Timeout number
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerCpuSyncPollingByteProc(DWORD ulTimeout)
{
    if(ulTimeout == _SCALER_CPU_SYNC_TIMEOUT_NO_WAIT)
    {
        return _FALSE;
    }
    else if(ulTimeout == _SCALER_CPU_SYNC_TIMEOUT_INFINITY)
    {
        while(g_stCpuSyncToScpuCmd.stCmdHeader.ucCmdSeqNum != g_stCpuSyncToScpuCmdReply.ucAckCmdSeqNum)
        {
#if(_CPU_NOTIFY_INT_DEBUG_SUPPORT == _ON)
            // for avoiding recursive call to ScalerDebug()
            if(g_bDebugRunCommand == _FALSE)
            {
                ScalerDebug();
            }
#endif
            DELAY_10US();
        }

        return _TRUE;
    }
    else
    {
        WORD usPreviousTime = g_usTimerCounter;

        do
        {
            if(g_stCpuSyncToScpuCmd.stCmdHeader.ucCmdSeqNum == g_stCpuSyncToScpuCmdReply.ucAckCmdSeqNum)
            {
                return _TRUE;
            }

            if(usPreviousTime != g_usTimerCounter)
            {
                ulTimeout--;
                usPreviousTime = g_usTimerCounter;
            }
        }
        while(ulTimeout != 0);

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DW8051 Read 32bits Address Space
// Input Value  : 32bits address
// Output Value : 32bits data
//--------------------------------------------------
DWORD ScalerCpuSyncGetDWord(DWORD ulAddress)
{
    g_pstCpuSyncToScpuCmd->unCmdBody.stReadCmd.pucAddr[0] = ((ulAddress) >> 24);
    g_pstCpuSyncToScpuCmd->unCmdBody.stReadCmd.pucAddr[1] = ((ulAddress) >> 16);
    g_pstCpuSyncToScpuCmd->unCmdBody.stReadCmd.pucAddr[2] = ((ulAddress) >> 8);
    g_pstCpuSyncToScpuCmd->unCmdBody.stReadCmd.pucAddr[3] = (ulAddress);

    UnionCpuSyncReplyCmdBody unCpuSyncToScpuCmdReplyBody = {0};

    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_READ_DWORD, _SCALER_CPU_SYNC_TIMEOUT_READ_DWORD, &unCpuSyncToScpuCmdReplyBody);

    return TO_DWORD(unCpuSyncToScpuCmdReplyBody.stReadReplyCmd.pucReadData[0],
                    unCpuSyncToScpuCmdReplyBody.stReadReplyCmd.pucReadData[1],
                    unCpuSyncToScpuCmdReplyBody.stReadReplyCmd.pucReadData[2],
                    unCpuSyncToScpuCmdReplyBody.stReadReplyCmd.pucReadData[3]);
}

//--------------------------------------------------
// Description  : DW8051 Write 32bits Address Space
// Input Value  : 32bits address
// Output Value : 32bits data
//--------------------------------------------------
void ScalerCpuSyncSetDWord(DWORD ulAddress, DWORD ulData)
{
    g_pstCpuSyncToScpuCmd->unCmdBody.stWriteCmd.pucAddr[0] = ((ulAddress) >> 24);
    g_pstCpuSyncToScpuCmd->unCmdBody.stWriteCmd.pucAddr[1] = ((ulAddress) >> 16);
    g_pstCpuSyncToScpuCmd->unCmdBody.stWriteCmd.pucAddr[2] = ((ulAddress) >> 8);
    g_pstCpuSyncToScpuCmd->unCmdBody.stWriteCmd.pucAddr[3] = (ulAddress);

    g_pstCpuSyncToScpuCmd->unCmdBody.stWriteCmd.pucWriteData[0] = ((ulData) >> 24);
    g_pstCpuSyncToScpuCmd->unCmdBody.stWriteCmd.pucWriteData[1] = ((ulData) >> 16);
    g_pstCpuSyncToScpuCmd->unCmdBody.stWriteCmd.pucWriteData[2] = ((ulData) >> 8);
    g_pstCpuSyncToScpuCmd->unCmdBody.stWriteCmd.pucWriteData[3] = (ulData);

    ScalerCpuSyncSendCmd(_SCALER_CPU_SYNC_WRITE_DWORD, _SCALER_CPU_SYNC_TIMEOUT_WRITE_DWORD, _NULL_POINTER);
}

//--------------------------------------------------
// Description  : 8051 Send ShutDown Cmd
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncShutDownCmd(void)
{
    ScalerCpuSyncSendCmd(_SYSTEM_CPU_SYNC_SHUTDOWN, _SYSTEM_CPU_SYNC_TIMEOUT_SHUT_DOWN, _NULL_POINTER);
}


//--------------------------------------------------
// Description  : KCPU Send Notify Cmd To SCPU
// Input Value  : EnumCpuSyncCommand --> Cmd Type
//                enumScalerLayerSyncCommandTypeTimeOut --> Cmd Timeout
//                punCpuSyncToScpuCmdReplyBody --> ToScpuCmdReplyBody Buffer
// Output Value : execute status
//--------------------------------------------------
bit ScalerCpuSyncSendCmd(EnumCpuSyncCommand enumScalerSyncCmdType, EnumCpuSyncCommandTimeOut enumScalerSyncCmdTypeTimeOut, UnionCpuSyncReplyCmdBody *punCpuSyncToScpuCmdReplyBody)
{
    WORD usTempTime = g_usTimerCounter;
    StructCpuSyncRequestCmd stTmpCpuSyncRequestCmd;

    memcpy(&stTmpCpuSyncRequestCmd, g_pstCpuSyncToScpuCmd, sizeof(StructCpuSyncRequestCmd));

    // Acquire CPU Notify resource lock
    if(RESOURCE_ACQUIRE(_RESOURCE_ID_TO_SCPU_NOTIFY, ((DWORD)enumScalerSyncCmdTypeTimeOut * 100)) == _FALSE)
    {
        return _FALSE;
    }
    // Assign Cmd Type
    stTmpCpuSyncRequestCmd.stCmdHeader.ucCmdType = enumScalerSyncCmdType;

    // Increase CMD ack number for New CMD
    stTmpCpuSyncRequestCmd.stCmdHeader.ucCmdSeqNum = g_stCpuSyncToScpuCmdReply.ucAckCmdSeqNum + 1;

    memcpy(&g_stCpuSyncToScpuCmd, &stTmpCpuSyncRequestCmd, sizeof(StructCpuSyncRequestCmd));

    SET_KCPU_REQUEST_IRQ_TO_SCPU();

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
    // Wait SCPU Side Ack
    bit bstatus = ScalerCpuSyncPollingByteProc(usTempTime);
    if((bstatus == _TRUE) && (punCpuSyncToScpuCmdReplyBody != _NULL_POINTER))
    {
        memcpy(punCpuSyncToScpuCmdReplyBody, &g_stCpuSyncToScpuCmdReply.unCmdBody, sizeof(UnionCpuSyncReplyCmdBody));
    }
    RESOURCE_RELEASE(_RESOURCE_ID_TO_SCPU_NOTIFY);
    return bstatus;
}
#endif // End of #if(_HW_CPU32_IS_BOOT_CPU == _TRUE)



#if((_LOCAL_DIMMING_FUNCTION == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON))
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Description  : Wait for SCPU Adim Send SPI Idle for avoiding conflit of SPI
// Input Value  : None
// Output Value : Polling _TRUE or _FALSE
//--------------------------------------------------
bit ScalerCpuSyncColorLDWaitScpuAdimIdle(void)
{
    if(g_bCpuSyncLedDriverBoostLock == _TRUE)
    {
        return ScalerTimerPollingXRAMFlagProc(_LOCAL_DIMMING_SPI_FW_WAIT_TIMEOUT, (DWORD)(&g_bCpuSyncLedDriverBoostLock), _BIT0, 0);
    }
    return _TRUE;
}
#else
//--------------------------------------------------
// Description  : Set SCPU Adim Send SPI status Flag
// Input Value  : bScpuAdimStatus
// Output Value : PNone
//--------------------------------------------------
void ScalerCpuSyncColorLDSetScpuAdimStatus(bit bScpuAdimStatus)
{
    g_bCpuSyncLedDriverBoostLock = bScpuAdimStatus;
}
#endif // End of #if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#endif // End of #if((_LOCAL_DIMMING_FUNCTION == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON))
#endif // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))

#if(_SCPU_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize("Os")
#endif
//--------------------------------------------------
// Description  : Check PR mode status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncDelayForHbrAudioSetting(void)
{
    BYTE ucDelayForHbrAudioSettingType = Scaler32GetByte(PA30000_08_GLOBAL_CTRL_DUMMY1, 0x01);
    if((ucDelayForHbrAudioSettingType & 0x0F) == 0x01)
    {
        BYTE ucIntStatus = GET_INTERRUPT_GLOBAL_ENABLE_STATUS();
        SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

#if(_HW_CPU32_BW32_SUPPORT == _ON)
        // Wait BW32 idle (5us*4000=20ms)
        WORD usBW32CheckTime = 4000;
        while(usBW32CheckTime != 0)
        {
            if(ScalerBW32ChkAllDone() == 0)
            {
                break;
            }
            ScalerMcuDelayXus(5);
            usBW32CheckTime--;
        }
#endif
        // notify KCPU start to execute ScalerSyncSetHdmiAudioRx3HbrAudioOutputForTmds
        Scaler32SetByte(PA30000_08_GLOBAL_CTRL_DUMMY1, 0x01, _PARALLELMODE_HBR_SECOND_STATE);

        WORD usHbrResetCheckTime = 12800;
        // wait max 210us(5us*12800) for SCPU executing ScalerSyncSetHdmiAudioRx3HbrAudioOutputForTmds
        while(usHbrResetCheckTime != 0)
        {
            if(Scaler32GetByte(PA30000_08_GLOBAL_CTRL_DUMMY1, 0x01) == _PARALLELMODE_HBR_THIRD_STATE)
            {
                break;
            }

            ScalerMcuDelayXus(5);

            usHbrResetCheckTime--;
        }

        switch(ucDelayForHbrAudioSettingType)
        {
#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            case _PARALLELMODE_HBR_FIRST_STATE_FOR_RX3_FRL:
                ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForFrl();
                break;
#endif
            case _PARALLELMODE_HBR_FIRST_STATE_FOR_RX3_TMDS:
                ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForTmds();
                break;
#endif

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
            case _PARALLELMODE_HBR_FIRST_STATE_FOR_RX4_FRL:
                ScalerCpuSyncSetHdmiAudioRx4HbrAudioOutputForFrl();
                break;
#endif
            case _PARALLELMODE_HBR_FIRST_STATE_FOR_RX4_TMDS:
                ScalerCpuSyncSetHdmiAudioRx4HbrAudioOutputForTmds();
                break;
#endif
            default:
                break;
        }

        // notify KCPU execute done
        Scaler32SetByte(PA30000_08_GLOBAL_CTRL_DUMMY1, 0x01, _PARALLELMODE_HBR_FOURTH_STATE);

        SET_INTERRUPT_GLOBAL_ENABLE_STATUS(ucIntStatus);
    }
}
#ifdef __GNUC__
#pragma GCC pop_options
#endif
#endif
#endif


#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize("Os")
#endif
#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HBR Audio Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForFrl(void)
{
    BYTE ucTimeout = 20;

    // w1c over/under flow flag
    ScalerSetBit(P77_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // afifo w en
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT2, _BIT2);

// delay 40us
    while(--ucTimeout)
    {
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        g_ulCpuSyncBusyDelayCnt = 45;
#else
        g_ulCpuSyncBusyDelayCnt = 336;
#endif
        while(--g_ulCpuSyncBusyDelayCnt){};
        ScalerSetByte(P77_C9_HDMI_AP, _P77_CA_PT_62_PORT_PAGE77_HDMI_AOCR);
        ScalerSetByte(P77_CA_HDMI_DP, 0x00);
    }

    // --------------------------------------------------------------------------------------------------------------------------
    // Enable step: Mac I2S output -> Afifo Read enable -> delay for 1 60958frame --> Parallel mode active -> tracking enable
    // --------------------------------------------------------------------------------------------------------------------------
    // Mac I2S output en
    ScalerSetByte(P77_C9_HDMI_AP, _P77_CA_PT_62_PORT_PAGE77_HDMI_AOCR);
    ScalerSetByte(P77_CA_HDMI_DP, 0xFF);

    // w1c over/under flow flag
    ScalerSetByte(P77_CB_HDMI_SR, 0x06);

    // afifo R en
    ScalerSetByte(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR);
    ScalerSetByte(P77_CA_HDMI_DP, 0x26);

    // delay 3us
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ulCpuSyncBusyDelayCnt = 70;
#else
    g_ulCpuSyncBusyDelayCnt = 647;
#endif
    while(--g_ulCpuSyncBusyDelayCnt){};


    // parallel mode normal
    SET_IIS_PARALLEL_MODE_NORMAL();

    // tracking en
    ScalerSetByte(P77_C9_HDMI_AP, _P77_CA_PT_15_PORT_PAGE77_HDMI_PSCR);
    ScalerSetByte(P77_CA_HDMI_DP, 0xEE);

    // double buf
    ScalerSetByte(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR);
    ScalerSetByte(P77_CA_HDMI_DP, 0xC0);

    // trk_mod_en = 0
    ScalerSetByte(P77_C9_HDMI_AP, _P77_CA_PT_9F_PORT_PAGE77_PRESET_AFSM_MOD);
    ScalerSetByte(P77_CA_HDMI_DP, 0xD4);

    if(ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_18_PORT_PAGE77_HDMI_MFDDR) == 0x00)
    {
        SET_HDMI_RX3_HBR_AUDIO_FIFO_ERROR();
    }

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ulCpuSyncBusyDelayCnt = 8;
#else
    g_ulCpuSyncBusyDelayCnt = 202;
#endif
    while(--g_ulCpuSyncBusyDelayCnt){};

    // audio i/p code work
    ScalerSetByte(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0);
    ScalerSetByte(P77_CA_HDMI_DP, 0xA0);
}
#endif

//--------------------------------------------------
// Description  : HBR Audio Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForTmds(void)
{
    BYTE ucTimeout = 20;

    // w1c over/under flow flag
    ScalerSetBit(P72_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // afifo w en
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT2, _BIT2);

    // delay begin
    // delay 40us
    while(--ucTimeout)
    {
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        g_ulCpuSyncBusyDelayCnt = 45;
#else
        g_ulCpuSyncBusyDelayCnt = 336;
#endif
        while(--g_ulCpuSyncBusyDelayCnt){};
        ScalerSetByte(P72_C9_HDMI_AP, _P72_CA_PT_62_PORT_PAGE72_HDMI_AOCR);
        ScalerSetByte(P72_CA_HDMI_DP, 0x00);
    }

    // delay stop

    // --------------------------------------------------------------------------------------------------------------------------
    // Enable step: Mac I2S output -> Afifo Read enable -> delay for 1 60958frame --> Parallel mode active -> tracking enable
    // --------------------------------------------------------------------------------------------------------------------------
    // Mac I2S output en
    ScalerSetByte(P72_C9_HDMI_AP, _P72_CA_PT_62_PORT_PAGE72_HDMI_AOCR);
    ScalerSetByte(P72_CA_HDMI_DP, 0xFF);

    // w1c over/under flow flag
    ScalerSetByte(P72_CB_HDMI_SR, 0x06);

    // afifo R en
    ScalerSetByte(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR);
    ScalerSetByte(P72_CA_HDMI_DP, 0x26);

    // delay 1.6us
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ulCpuSyncBusyDelayCnt = 39;
#else
    g_ulCpuSyncBusyDelayCnt = 423;
#endif
    while(--g_ulCpuSyncBusyDelayCnt){};

    // parallel mode normal
    SET_IIS_PARALLEL_MODE_NORMAL();

    // tracking en
    ScalerSetByte(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR);
    ScalerSetByte(P72_CA_HDMI_DP, 0xEE);

    // double buf
    ScalerSetByte(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR);
    ScalerSetByte(P72_CA_HDMI_DP, 0xC0);

    // trk_mod_en = 0
    ScalerSetByte(P72_C9_HDMI_AP, _P72_CA_PT_9F_PORT_PAGE72_PRESET_AFSM_MOD);
    ScalerSetByte(P72_CA_HDMI_DP, 0xD4);

    if(ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_18_PORT_PAGE72_HDMI_MFDDR) == 0x00)
    {
        SET_HDMI_RX3_HBR_AUDIO_FIFO_ERROR();
    }

    // delay 200ns
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ulCpuSyncBusyDelayCnt = 8;
#else
    g_ulCpuSyncBusyDelayCnt = 202;
#endif
    while(--g_ulCpuSyncBusyDelayCnt){};

    // audio i/p code work
    ScalerSetByte(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0);
    ScalerSetByte(P72_CA_HDMI_DP, 0xA0);
}
#endif
#endif

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HBR Audio Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncSetHdmiAudioRx4HbrAudioOutputForFrl(void)
{
    BYTE ucTimeout = 20;

    // w1c over/under flow flag
    ScalerSetBit(P78_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // afifo w en
    ScalerSetDataPortBit(P78_C9_HDMI_AP, _P78_CA_PT_03_PORT_PAGE78_HDMI_AFCR, ~_BIT2, _BIT2);

    // delay 40us
    while(--ucTimeout)
    {
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        g_ulCpuSyncBusyDelayCnt = 45;
#else
        g_ulCpuSyncBusyDelayCnt = 336;
#endif
        while(--g_ulCpuSyncBusyDelayCnt){};
        ScalerSetByte(P78_C9_HDMI_AP, _P78_CA_PT_62_PORT_PAGE78_HDMI_AOCR);
        ScalerSetByte(P78_CA_HDMI_DP, 0x00);
    }

    // --------------------------------------------------------------------------------------------------------------------------
    // Enable step: Mac I2S output -> Afifo Read enable -> delay for 1 60958frame --> Parallel mode active -> tracking enable
    // --------------------------------------------------------------------------------------------------------------------------
    // Mac I2S output en
    ScalerSetByte(P78_C9_HDMI_AP, _P78_CA_PT_62_PORT_PAGE78_HDMI_AOCR);
    ScalerSetByte(P78_CA_HDMI_DP, 0xFF);

    // w1c over/under flow flag
    ScalerSetByte(P78_CB_HDMI_SR, 0x06);

    // afifo R en
    ScalerSetByte(P78_C9_HDMI_AP, _P78_CA_PT_03_PORT_PAGE78_HDMI_AFCR);
    ScalerSetByte(P78_CA_HDMI_DP, 0x26);

    // delay 3us
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ulCpuSyncBusyDelayCnt = 70;
#else
    g_ulCpuSyncBusyDelayCnt = 647;
#endif
    while(--g_ulCpuSyncBusyDelayCnt){};

    // parallel mode normal
    SET_IIS_PARALLEL_MODE_NORMAL();

    // tracking en
    ScalerSetByte(P78_C9_HDMI_AP, _P78_CA_PT_15_PORT_PAGE78_HDMI_PSCR);
    ScalerSetByte(P78_CA_HDMI_DP, 0xEE);

    // double buf
    ScalerSetByte(P78_C9_HDMI_AP, _P78_CA_PT_D0_PORT_PAGE78_HDMI_CMCR);
    ScalerSetByte(P78_CA_HDMI_DP, 0xC0);

    // trk_mod_en = 0
    ScalerSetByte(P78_C9_HDMI_AP, _P78_CA_PT_9F_PORT_PAGE78_PRESET_AFSM_MOD);
    ScalerSetByte(P78_CA_HDMI_DP, 0xD4);

    if(ScalerGetDataPortSingleByte(P78_C9_HDMI_AP, _P78_CA_PT_18_PORT_PAGE78_HDMI_MFDDR) == 0x00)
    {
        SET_HDMI_RX4_HBR_AUDIO_FIFO_ERROR();
    }

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ulCpuSyncBusyDelayCnt = 8;
#else
    g_ulCpuSyncBusyDelayCnt = 202;
#endif
    while(--g_ulCpuSyncBusyDelayCnt){};

    // audio i/p code work
    ScalerSetByte(P78_C9_HDMI_AP, _P78_CA_PT_31_PORT_PAGE78_HDMI_WDCR0);
    ScalerSetByte(P78_CA_HDMI_DP, 0xA0);
}
#endif

//--------------------------------------------------
// Description  : HBR Audio Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCpuSyncSetHdmiAudioRx4HbrAudioOutputForTmds(void)
{
    BYTE ucTimeout = 20;

    // audio manual mode
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, ~_BIT6, 0x00);

    // manual gain enable
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, ~_BIT3, 0x00);

    // w1c over/under flow flag
    ScalerSetBit(P73_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // afifo w en
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR, ~_BIT2, _BIT2);

// delay 40us
    while(--ucTimeout)
    {
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        g_ulCpuSyncBusyDelayCnt = 45;
#else
        g_ulCpuSyncBusyDelayCnt = 336;
#endif
        while(--g_ulCpuSyncBusyDelayCnt){};
        ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_62_PORT_PAGE73_HDMI_AOCR);
        ScalerSetByte(P73_CA_HDMI_DP, 0x00);
    }

    // --------------------------------------------------------------------------------------------------------------------------
    // Enable step: Mac I2S output -> Afifo Read enable -> delay for 1 60958frame --> Parallel mode active -> tracking enable
    // --------------------------------------------------------------------------------------------------------------------------
    // Mac I2S output en
    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_62_PORT_PAGE73_HDMI_AOCR);
    ScalerSetByte(P73_CA_HDMI_DP, 0xFF);

    // w1c over/under flow flag
    ScalerSetByte(P73_CB_HDMI_SR, 0x06);

    // afifo R en
    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_03_PORT_PAGE73_HDMI_AFCR);
    ScalerSetByte(P73_CA_HDMI_DP, 0x26);

    // delay begin
    // delay 1.6us
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ulCpuSyncBusyDelayCnt = 39;
#else
    g_ulCpuSyncBusyDelayCnt = 423;
#endif
    while(--g_ulCpuSyncBusyDelayCnt){};

    // parallel mode normal
    SET_IIS_PARALLEL_MODE_NORMAL();

    // tracking en
    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_15_PORT_PAGE73_HDMI_PSCR);
    ScalerSetByte(P73_CA_HDMI_DP, 0xEE);

    // double buf
    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_D0_PORT_PAGE73_HDMI_CMCR);
    ScalerSetByte(P73_CA_HDMI_DP, 0xC0);

    // trk_mod_en = 0
    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_9F_PORT_PAGE73_PRESET_AFSM_MOD);
    ScalerSetByte(P73_CA_HDMI_DP, 0xD4);

    if(ScalerGetDataPortSingleByte(P73_C9_HDMI_AP, _P73_CA_PT_18_PORT_PAGE73_HDMI_MFDDR) == 0x00)
    {
        SET_HDMI_RX4_HBR_AUDIO_FIFO_ERROR();
    }

    // delay 200ns
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ulCpuSyncBusyDelayCnt = 8;
#else
    g_ulCpuSyncBusyDelayCnt = 202;
#endif
    while(--g_ulCpuSyncBusyDelayCnt){};

    // audio i/p code work
    ScalerSetByte(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0);
    ScalerSetByte(P73_CA_HDMI_DP, 0xA0);
}
#endif
#endif
#ifdef __GNUC__
#pragma GCC pop_options
#endif
