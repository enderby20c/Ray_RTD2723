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
// ID Code      : ScalerCpuSyncInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)

//--------------------------------------------------
// Definitions of SCPU NOTIFY INT Event Processing Macro
//--------------------------------------------------
#define CHK_SCPU_NOTIFY_INT_HAPPEN()                        ((MCU_FD52_NOTIFY_8051_INT_CTRL & (_BIT7 | _BIT0)) == (_BIT7 | _BIT0))
#define ACK_SCPU_NOTIFY_INT_FLAG()                          (MCU_FD52_NOTIFY_8051_INT_CTRL |= _BIT0)


//--------------------------------------------------
// Definitions of KCPU Receive SCPU Command Buffer Macro
//--------------------------------------------------
#define GET_SCPU_NOTIFY_INT_CMD_TYPE()                      (g_stCpuSyncToKcpuCmd.stCmdHeader.ucCmdType)
#define ACK_SCPU_NOTIFY_INT_CMD()                           (g_stCpuSyncToKcpuCmdReply.ucAckCmdSeqNum = g_stCpuSyncToKcpuCmd.stCmdHeader.ucCmdSeqNum)

//--------------------------------------------------
// Definitions of Send KCPU Request IRQ to Notify SCPU
// Gen a Pluse : 0 -> 1 -> 0
// High pulse must keep 4*(cup1_clk/2)
//--------------------------------------------------
#define SET_KCPU_REQUEST_IRQ_TO_SCPU()                      {\
                                                                MCU_FD51_NOTIFY_CPU32_INT_CTRL = 0x00;\
                                                                MCU_FD51_NOTIFY_CPU32_INT_CTRL |= _BIT0;\
                                                                MCU_FD51_NOTIFY_CPU32_INT_CTRL = 0x00;\
                                                            }
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1CpuIntMoreProcessFlag : 1;
}StructCpuCmdSyncInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern volatile StructCpuSyncRequestCmd *g_pstCpuSyncToScpuCmd;
#endif // End of #if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#if(_LOCAL_DIMMING_FUNCTION == _ON)
extern volatile bit g_bCpuSyncColorLocalDimmingRestoreBacklight;
#if(_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _OFF)
extern volatile bit g_bCpuSyncColorLocalDimmingSendAdimCmd;
#endif
#endif

extern volatile StructCpuSyncRequestCmd g_stCpuSyncToScpuCmd;
extern volatile StructCpuSyncReplyCmd g_stCpuSyncToScpuCmdReply;
extern volatile StructCpuSyncRequestCmd g_stCpuSyncToKcpuCmd;
extern volatile StructCpuSyncReplyCmd g_stCpuSyncToKcpuCmdReply;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern void ScalerCpuSyncHandler(void);
extern bit ScalerCpuSyncNotifyIntHandler(EnumCpuSyncCommand enumCpuSyncCommand);
extern bit ScalerCpuSyncPollingByteProc(DWORD ulTimeout);
extern bit ScalerCpuSyncSendCmd(EnumCpuSyncCommand enumScalerSyncCmdType, EnumCpuSyncCommandTimeOut enumScalerSyncCmdTypeTimeOut, UnionCpuSyncReplyCmdBody *punCpuSyncToScpuCmdReplyBody);
#endif // End of #if(_IS_MAIN_PROCESS_CPU == _TRUE)

#if((_LOCAL_DIMMING_FUNCTION == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON))
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern bit ScalerCpuSyncColorLDWaitScpuAdimIdle(void);
#else
extern void ScalerCpuSyncColorLDSetScpuAdimStatus(bit bScpuAdimStatus);
#endif // End of #if(_IS_MAIN_PROCESS_CPU == _TRUE)
#endif // End of #if((_LOCAL_DIMMING_FUNCTION == _ON) && (_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON))
#endif // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))

#if(_SCPU_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
__attribute__((section(".itcm_section.ScalerCpuSyncDelayForHbrAudioSetting")))
extern void ScalerCpuSyncDelayForHbrAudioSetting(void);
#endif
#endif

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
__attribute__((section(".itcm_section.ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForFrl")))
extern void ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForFrl(void);
#endif

__attribute__((section(".itcm_section.ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForTmds")))
extern void ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForTmds(void);
#endif
#endif // End of #if(_HDMI_AUDIO_RX3_SUPPORT == _ON)

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
__attribute__((section(".itcm_section.ScalerCpuSyncSetHdmiAudioRx4HbrAudioOutputForFrl")))
extern void ScalerCpuSyncSetHdmiAudioRx4HbrAudioOutputForFrl(void);
#endif

__attribute__((section(".itcm_section.ScalerCpuSyncSetHdmiAudioRx4HbrAudioOutputForTmds")))
extern void ScalerCpuSyncSetHdmiAudioRx4HbrAudioOutputForTmds(void);
#endif
#endif // End of #if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
