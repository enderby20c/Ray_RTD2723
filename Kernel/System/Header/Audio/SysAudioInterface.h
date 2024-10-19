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
// ID Code      : SysAudioInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_AUDIO_PATH_INPUT_PORT(x)                            (g_pstAudioPathInfo[x].enumInputport)
#define SET_AUDIO_PATH_INPUT_PORT(x, y)                         (g_pstAudioPathInfo[x].enumInputport = (y))

#define GET_AUDIO_PATH_OUTPUT_PORT(x)                           (g_pstAudioPathInfo[x].enumOutputport)
#define SET_AUDIO_PATH_OUTPUT_PORT(x, y)                        (g_pstAudioPathInfo[x].enumOutputport = (y))

#define GET_AUDIO_PATH_AUDIO_STATE(x)                           (g_pstAudioPathInfo[x].enumAudioState)
#define SET_AUDIO_PATH_AUDIO_STATE(x, y)                        (g_pstAudioPathInfo[x].enumAudioState = (y))

#define GET_AUDIO_PATH_AUDIO_PRE_STATE(x)                       (g_pstAudioPathInfo[x].enumPreviousAudioState)
#define SET_AUDIO_PATH_AUDIO_PRE_STATE(x, y)                    (g_pstAudioPathInfo[x].enumPreviousAudioState = (y))

#define GET_AUDIO_PATH_AUDIO_INPUT_READY(x)                     (g_pstAudioPathInfo[x].enumInputReadyStatus)
#define SET_AUDIO_PATH_AUDIO_INPUT_READY(x, y)                  (g_pstAudioPathInfo[x].enumInputReadyStatus = (y))

#define GET_AUDIO_PATH_AUDIO_FORMAT(x)                          (g_pstAudioPathInfo[x].enumAudioPathLpcmInfoBackup)
#define SET_AUDIO_PATH_AUDIO_FORMAT(x, y)                       (g_pstAudioPathInfo[x].enumAudioPathLpcmInfoBackup = (y))

#define GET_AUDIO_PATH_AUDIO_FS(x)                              (g_pstAudioPathInfo[x].enumAudioSamplingFreqPacket)
#define SET_AUDIO_PATH_AUDIO_FS(x, y)                           (g_pstAudioPathInfo[x].enumAudioSamplingFreqPacket = (y))

#define GET_AUDIO_PATH_AUDIO_CHANNEL_COUNT(x)                   (g_pstAudioPathInfo[x].enumAudioChannelCount)
#define SET_AUDIO_PATH_AUDIO_CHANNEL_COUNT(x, y)                (g_pstAudioPathInfo[x].enumAudioChannelCount = (y))

#define GET_AUDIO_PATH_AUDIO_STATE_CHANGE(x)                    (bit)(g_pstAudioPathInfo[x].b1AudioStateChange)
#define SET_AUDIO_PATH_AUDIO_STATE_CHANGE(x)                    (g_pstAudioPathInfo[x].b1AudioStateChange = _TRUE)
#define CLR_AUDIO_PATH_AUDIO_STATE_CHANGE(x)                    (g_pstAudioPathInfo[x].b1AudioStateChange = _FALSE)

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#define GET_AUDIO_PATH_AUDIO_PLAY_ALONE(x)                      (bit)(g_pstAudioPathInfo[x].b1AudioPlayingAlone)
#define SET_AUDIO_PATH_AUDIO_PLAY_ALONE(x)                      (g_pstAudioPathInfo[x].b1AudioPlayingAlone = _TRUE)
#define CLR_AUDIO_PATH_AUDIO_PLAY_ALONE(x)                      (g_pstAudioPathInfo[x].b1AudioPlayingAlone = _FALSE)
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#define GET_AUDIO_INTERNAL_GEN_INPUT_PORT(x)                    (g_pstAudioPathInfo[x].enumAudioGenInputPort)
#define SET_AUDIO_INTERNAL_GEN_INPUT_PORT(x, y)                 (g_pstAudioPathInfo[x].enumAudioGenInputPort = (y))
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
#define GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE()         (g_stAudioArcTxModeInfo.b1RetryArcEarcByHpdToggle)
#define SET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE()         (g_stAudioArcTxModeInfo.b1RetryArcEarcByHpdToggle = _TRUE)
#define CLR_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE()         (g_stAudioArcTxModeInfo.b1RetryArcEarcByHpdToggle = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of ARC Tx Mode State
//--------------------------------------------------
typedef enum
{
    _ARC_MODE_STATUS_POWER_OFF = 0x00,
    _ARC_MODE_STATUS_IDLE,
    _ARC_MODE_STATUS_OSD_CHANGE,
    _ARC_MODE_STATUS_ARC_DISCONNECT,
    _ARC_MODE_STATUS_ARC_CONNECT,
    _ARC_MODE_STATUS_ARC_WAIT_INPUT_READY,
    _ARC_MODE_STATUS_ARC_AUDIO_OUTPUT,
    _ARC_MODE_STATUS_ARC_STABLE_DETECT,
    _ARC_MODE_STATUS_EARC_DISCOVERY,
    _ARC_MODE_STATUS_EARC_WAIT_INPUT_READY,
    _ARC_MODE_STATUS_EARC_AUDIO_OUTPUT,
    _ARC_MODE_STATUS_EARC_STABLE_DETECT,
} EnumArcTxModeStatus;

//--------------------------------------------------
// Structure of ARC Tx Mode Info
//--------------------------------------------------
typedef struct
{
    BYTE b1ArcModeStateChanged : 1;
    BYTE b1ArcAudioOutputReady : 1;
    BYTE b1OsdArcModeChange : 1;
    BYTE b1OsdArcChNumChange : 1;
    BYTE b1HpdPinStatusChange : 1;
    BYTE b1RetryArcEarcByHpdToggle : 1;
#if(_HDMI_CEC_SUPPORT == _ON)
    BYTE b1CecRequestArcInitiateStart : 1;
    BYTE b1CecRequestArcInitiateTimeout : 1;
    BYTE b1CecRequestArcTerminateStart : 1;
    BYTE b1CecRequestArcTerminateTimeout : 1;
    BYTE ucCecRequestArcInitiateRetryCount;
    BYTE ucCecRequestArcTerminateRetryCount;
#endif
#if(_AUDIO_EARC_SUPPORT == _ON)
    BYTE b1EarcDiscoveryFinish : 1;
    BYTE b1EarcPassToTimeoutHappened : 1;
    BYTE b4EarcPassToTimeoutRetryCount : 4;
#endif
    EnumArcTxModeStatus enumArcModeState;
    EnumUserHdmi5vStatus enumAudioArcTxHpdPinDetectResult;
} StructArcTxModeInfoType;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_AUDIO_ARC_SUPPORT == _ON)
extern StructArcTxModeInfoType g_stAudioArcTxModeInfo;
#if(_AUDIO_EARC_SUPPORT == _ON)
extern StructArcTxEarcCdsInfo g_stAudioEarcRxCdsInfo;
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysAudioChangeAudioState(BYTE ucPathIndex, EnumAudioState enumAudioState);
extern void SysAudioChangeAllPathAudioState(EnumAudioState enumAudioState);
extern void SysAudioDisable(EnumAudioOutputType enumAudioOutput);
extern EnumAudioState SysAudioGetPathAudioState(EnumAudioOutputType enumAudioOutput);
#if(_DP_SUPPORT == _ON)
extern bit SysAudioCheckDpPortExist(void);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
extern void SysAudioArcTxCableUnplugResetProc(EnumInputPort enumInputPort);
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)


