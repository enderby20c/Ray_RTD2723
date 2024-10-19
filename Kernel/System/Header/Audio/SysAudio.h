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
// ID Code      : SysAudio.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_AUDIO_H__
#define __SYS_AUDIO_H__

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_EMBEDDED_DAC_SUPPORT == _ON)
#define _DAC_VCM_INITIAL_TIME                                           SEC(0.1)
#define _DAC_VCM_CHARGE_TIME                                            SEC(0.5)
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
// H2.1 eARC Tx standard define TeARC_TX_FORMAT_CHG at least 200ms
#define _AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIME                       250

#define GET_AUDIO_ARC_TX_OSD_ARC_MODE()                                 (g_stAudioArcTxOsdInfo.enumArcMode)
#define SET_AUDIO_ARC_TX_OSD_ARC_MODE(x)                                (g_stAudioArcTxOsdInfo.enumArcMode = (x))

#define GET_AUDIO_ARC_TX_OSD_CHANNEL_NUM()                              (g_stAudioArcTxOsdInfo.enumArcAudioChanelStatus)
#define SET_AUDIO_ARC_TX_OSD_CHANNEL_NUM(x)                             (g_stAudioArcTxOsdInfo.enumArcAudioChanelStatus = (x))

#define GET_AUDIO_ARC_TX_OSD_ARC_MUTE_STATUS()                          (g_stAudioArcTxOsdInfo.enumArcMuteStatus)
#define SET_AUDIO_ARC_TX_OSD_ARC_MUTE_STATUS(x)                         (g_stAudioArcTxOsdInfo.enumArcMuteStatus = (x))

#define GET_AUDIO_ARC_TX_HPD_PIN_STATUS()                               (g_stAudioArcTxModeInfo.enumAudioArcTxHpdPinDetectResult)
#define SET_AUDIO_ARC_TX_HPD_PIN_STATUS(x)                              (g_stAudioArcTxModeInfo.enumAudioArcTxHpdPinDetectResult = (x))

#define GET_AUDIO_ARC_TX_MODE_STATE_CHANGE()                            (g_stAudioArcTxModeInfo.b1ArcModeStateChanged)
#define SET_AUDIO_ARC_TX_MODE_STATE_CHANGE()                            (g_stAudioArcTxModeInfo.b1ArcModeStateChanged = _TRUE)
#define CLR_AUDIO_ARC_TX_MODE_STATE_CHANGE()                            (g_stAudioArcTxModeInfo.b1ArcModeStateChanged = _FALSE)

#define GET_AUDIO_ARC_TX_MODE_STATE()                                   (g_stAudioArcTxModeInfo.enumArcModeState)
#define SET_AUDIO_ARC_TX_MODE_STATE(x)                                  (g_stAudioArcTxModeInfo.enumArcModeState = (x))

#define GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE()                          (g_stAudioArcTxModeInfo.b1OsdArcModeChange)
#define SET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE()                          (g_stAudioArcTxModeInfo.b1OsdArcModeChange = _TRUE)
#define CLR_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE()                          (g_stAudioArcTxModeInfo.b1OsdArcModeChange = _FALSE)

#define GET_AUDIO_ARC_TX_OSD_CHANNEL_NUM_CHANGE()                       (g_stAudioArcTxModeInfo.b1OsdArcChNumChange)
#define SET_AUDIO_ARC_TX_OSD_CHANNEL_NUM_CHANGE()                       (g_stAudioArcTxModeInfo.b1OsdArcChNumChange = _TRUE)
#define CLR_AUDIO_ARC_TX_OSD_CHANNEL_NUM_CHANGE()                       (g_stAudioArcTxModeInfo.b1OsdArcChNumChange = _FALSE)

#define GET_AUDIO_ARC_TX_HPD_PIN_STATUS_CHANGE()                        (g_stAudioArcTxModeInfo.b1HpdPinStatusChange)
#define SET_AUDIO_ARC_TX_HPD_PIN_STATUS_CHANGE()                        (g_stAudioArcTxModeInfo.b1HpdPinStatusChange = _TRUE)
#define CLR_AUDIO_ARC_TX_HPD_PIN_STATUS_CHANGE()                        (g_stAudioArcTxModeInfo.b1HpdPinStatusChange = _FALSE)

#define GET_AUDIO_ARC_TX_AUDIO_OUTPUT_READY()                           (g_stAudioArcTxModeInfo.b1ArcAudioOutputReady)
#define SET_AUDIO_ARC_TX_AUDIO_OUTPUT_READY()                           (g_stAudioArcTxModeInfo.b1ArcAudioOutputReady = _TRUE)
#define CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY()                           (g_stAudioArcTxModeInfo.b1ArcAudioOutputReady = _FALSE)

#if(_HDMI_CEC_SUPPORT == _ON)
#define GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START()               (g_stAudioArcTxModeInfo.b1CecRequestArcInitiateStart)
#define SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START()               (g_stAudioArcTxModeInfo.b1CecRequestArcInitiateStart = _TRUE)
#define CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START()               (g_stAudioArcTxModeInfo.b1CecRequestArcInitiateStart = _FALSE)

#define GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT()       (g_stAudioArcTxModeInfo.b1CecRequestArcInitiateTimeout)
#define SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT()       (g_stAudioArcTxModeInfo.b1CecRequestArcInitiateTimeout = _TRUE)
#define CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT()       (g_stAudioArcTxModeInfo.b1CecRequestArcInitiateTimeout = _FALSE)

#define GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT()         (g_stAudioArcTxModeInfo.ucCecRequestArcInitiateRetryCount)
#define SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT(x)        (g_stAudioArcTxModeInfo.ucCecRequestArcInitiateRetryCount = (x))
#define CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT()         (g_stAudioArcTxModeInfo.ucCecRequestArcInitiateRetryCount = 0)

#define GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START()              (g_stAudioArcTxModeInfo.b1CecRequestArcTerminateStart)
#define SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START()              (g_stAudioArcTxModeInfo.b1CecRequestArcTerminateStart = _TRUE)
#define CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START()              (g_stAudioArcTxModeInfo.b1CecRequestArcTerminateStart = _FALSE)

#define GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT()      (g_stAudioArcTxModeInfo.b1CecRequestArcTerminateTimeout)
#define SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT()      (g_stAudioArcTxModeInfo.b1CecRequestArcTerminateTimeout = _TRUE)
#define CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT()      (g_stAudioArcTxModeInfo.b1CecRequestArcTerminateTimeout = _FALSE)

#define GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT()        (g_stAudioArcTxModeInfo.ucCecRequestArcTerminateRetryCount)
#define SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT(x)       (g_stAudioArcTxModeInfo.ucCecRequestArcTerminateRetryCount = (x))
#define CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT()        (g_stAudioArcTxModeInfo.ucCecRequestArcTerminateRetryCount = 0)

//-------------------------------------------------
// Audio ARC Tx CEC Request ARC_Initiate Retry Setting
//-------------------------------------------------
#define _AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_MAX_COUNT          5
#define _AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_DURATION           500

//-------------------------------------------------
// Audio ARC Tx CEC Request ARC_Terminate Retry Setting
//-------------------------------------------------
#define _AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_MAX_COUNT         5
#define _AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_DURATION          500
#endif

#if(_AUDIO_EARC_SUPPORT == _ON)
//-------------------------------------------------
// Audio eARC Tx Pass to DISC Timeout Retry Discovery Support
//-------------------------------------------------
#define _AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY                   _OFF

//-------------------------------------------------
// Audio eARC Tx Pass to DISC Timeout Retry Discovery Max Times
//-------------------------------------------------
#define _AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_MAX_COUNT         5

//-------------------------------------------------
// Audio eARC Tx Wait Discovery Finish Time
//-------------------------------------------------
#define _AUDIO_ARC_TX_WAIT_EARC_DISCOVERY_FINISH_TIME                   1000

#define GET_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH()                        (g_stAudioArcTxModeInfo.b1EarcDiscoveryFinish)
#define SET_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH()                        (g_stAudioArcTxModeInfo.b1EarcDiscoveryFinish = _TRUE)
#define CLR_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH()                        (g_stAudioArcTxModeInfo.b1EarcDiscoveryFinish = _FALSE)

#if(_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY == _ON)
#define GET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED()           (g_stAudioArcTxModeInfo.b1EarcPassToTimeoutHappened)
#define SET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED()           (g_stAudioArcTxModeInfo.b1EarcPassToTimeoutHappened = _TRUE)
#define CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED()           (g_stAudioArcTxModeInfo.b1EarcPassToTimeoutHappened = _FALSE)

#define GET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT()        (g_stAudioArcTxModeInfo.b4EarcPassToTimeoutRetryCount)
#define SET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT(x)       (g_stAudioArcTxModeInfo.b4EarcPassToTimeoutRetryCount = (x))
#define CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT()        (g_stAudioArcTxModeInfo.b4EarcPassToTimeoutRetryCount = 0)
#endif
#endif
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysAudioJudgeHandler(void);
extern void SysAudioModeHandler(void);
extern void SysAudioPathSettingCheck(BYTE ucPathIndex);
extern void SysAudioInputSourceChangeCheck(BYTE ucPathIndex);
extern void SysAudioOutputPortChangeCheck(BYTE ucPathIndex);
extern EnumAudioStatus SysAudioInputGetReadyToPlay(BYTE ucPathIndex);
extern EnumAudioStatus SysAudioOutputGetReadyToPlay(EnumAudioOutputType enumAudioOutput);
extern EnumAudioStatus SysAudioStableCheck(BYTE ucPathIndex);
extern bit SysAudioFormatChangeCheck(BYTE ucPathIndex);
extern bit SysAudioTtsGetPlaybackEvent(EnumAudioOutputType enumAudioOutput);
extern bit SysAudioSourceAudioReceived(BYTE ucPathIndex);
extern bit SysAudioCheckSameInputAtNextPathNeedToReset(BYTE ucPathIndex);
extern bit SysAudioCheckSameInputAtPreviousPath(BYTE ucPathIndex);
extern bit SysAudioCheckSameInputAtPreviousPathReady(BYTE ucPathIndex);
extern bit SysAudioCheckOtherPathHasSameInput(BYTE ucPathIndex);

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
extern void SysAudioFastOutputProc(EnumAudioOutputType enumAudioOutput, bit bEnable);
extern void SysAudioFastMuteProc(EnumAudioOutputType enumAudioOutput, bit bEnable);
extern void SysAudioDacFastMuteProc(bit bMute);
#if(_AUDIO_ARC_SUPPORT == _ON)
extern void SysAudioArcFastMuteProc(bit bMute);
#endif
#endif

extern void SysAudioDacHandler(void);
extern void SysAudioInputHandler(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort);
extern void SysAudioOutputHandler(EnumAudioOutputType enumAudioOutput);
extern void SysAudioInitial(void);
extern void SysAudioSetUserDefineAudioFrequency(void);

#if(_SLEEP_AUDIO_SUPPORT == _ON)
extern void SysAudioPlayingAloneProc(BYTE ucPathIndex, EnumAudioState enumAudioState);
#endif

#if(_LINE_IN_SUPPORT == _ON)
extern bit SysAudioCheckSourceJudge(void);
#endif

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void SysAudioFwTrackingHandler(void);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
extern void SysAudioArcTxOutputProc(bit bEnable);
extern void SysAudioArcTxMuteProc(bit bMute);
extern void SysAudioArcTxGetOsdInfo(StructArcTxOsdInfo *pstArcOsdInfo);
extern void SysAudioArcTxHandler(void);
extern void SysAudioArcTxJudgeHandler(void);
extern void SysAudioArcTxModeHandler(void);
extern void SysAudioArcTxStateChangeEvent(EnumArcTxModeStatus enumModeState);
extern void SysAudioArcTxHpdPinDetectProc(void);
extern void SysAudioArcTxArcModeInitial(void);
extern void SysAudioArcTxArcModeOutputReset(void);
extern void SysAudioArcTxAudioOutputFormatSetting(EnumArcAudioChanelStatus enumArcOsdChannelNum, StructAudioInterfaceInfoForArc stArcAudioSourceInfo);
extern bit SysAudioArcTxStreamHandler(void);
extern bit SysAudioArcTxStableDetect(void);
extern void SysAudioArcTxInitial(void);
extern void SysAudioArcTxDisable(void);
extern bit SysAudioArcTxOutputChange(void);
extern BYTE SysAudioArcTxGetHpdToggleResetArcTxEvent(void);
extern void SysAudioArcTxClrHpdToggleResetArcTxEvent(void);
extern bit SysAudioArcTxCheckInputAudioInfoChange(void);
extern void SysAudioArcTxOsdChangeProc(EnumAudioArcMode enumArcMode);

#if(_HDMI_CEC_SUPPORT == _ON)
extern bit SysAudioArcTxCecRequestArcInitiateProc(void);
extern bit SysAudioArcTxCecRequestArcTerminateProc(void);
#endif

#if(_AUDIO_EARC_SUPPORT == _ON)
extern void SysAudioArcTxEarcModeOutputReset(void);
extern void SysAudioArcTxEarcDiscoveryProc(void);
extern bit SysAudioArcTxEarcCheckDiscoveryPass(void);
extern bit SysAudioArcTxEarcCheckDiscoveryTimeout(void);
extern bit SysAudioArcTxEarcStreamHandler(void);
extern void SysAudioArcTxEarcHeartbeatStatusCheckProc(void);
extern bit SysAudioArcTxEarcCheckAudioLatencyUpdate(BYTE *pucAudioLatency);
extern bit SysAudioArcTxEarcSetRequestAudioLatency(BYTE ucAudioLatency);
extern bit SysAudioArcTxEarcCheckCdsUpdate(void);
extern bit SysAudioArcTxEarcCdsReload(BYTE *pucEarcRxCdsTable);
extern bit SysAudioArcTxEarcCdsParser(BYTE *pucEarcRxCdsTable, StructArcTxEarcCdsInfo *pstEarcRxCdsInfo);
extern void SysAudioArcTxEarcCdsAudioDataBlockParser(BYTE *pucCtaSad);
extern void SysAudioArcTxEarcCheckChStatusMuteFlagChangeProc(void);
extern void SysAudioArcTxEarcSetChStatusMuteFlag(EnumAudioMuteStatus enumArcMute);
extern EnumAudioMuteStatus SysAudioArcTxEarcGetChStatusMuteFlag(void);
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)

#if((_HDMI_SUPPORT == _ON) && (_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
extern bit SysAudioHbrAudioSettingForParallelMode(BYTE ucPathIndex);
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)


#endif // End of #ifndef __SYS_AUDIO_H__
