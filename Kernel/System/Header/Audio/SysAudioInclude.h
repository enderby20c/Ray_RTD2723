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
// ID Code      : SysAudioInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_AUDIO_PLAYBACK_SEARCH_INDEX()       (g_stAudioInfo.enumAudioPlaybackSearchPort)
#define SET_AUDIO_PLAYBACK_SEARCH_INDEX(x)      (g_stAudioInfo.enumAudioPlaybackSearchPort = (x))

#if(_LINE_IN_SUPPORT == _ON)
#define GET_AUDIO_POWER_CUT_TO_LINE_IN_STATUS() (bit)(g_stAudioInfo.b1AudioPowerCutToLineInStatus)
#define SET_AUDIO_POWER_CUT_TO_LINE_IN_STATUS() (g_stAudioInfo.b1AudioPowerCutToLineInStatus = _TRUE)
#define CLR_AUDIO_POWER_CUT_TO_LINE_IN_STATUS() (g_stAudioInfo.b1AudioPowerCutToLineInStatus = _FALSE)
#endif

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
#define GET_AUDIO_SPDIF_PARALLEL_MODE()         (g_stAudioParallelInfo.enumSpdifParallelInfo)
#define SET_AUDIO_SPDIF_PARALLEL_MODE(x)        (g_stAudioParallelInfo.enumSpdifParallelInfo = (x))
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
#define GET_AUDIO_I2S_PARALLEL_MODE()           (g_stAudioParallelInfo.enumI2sParallelModeInfo)
#define SET_AUDIO_I2S_PARALLEL_MODE(x)          (g_stAudioParallelInfo.enumI2sParallelModeInfo = (x))

#define GET_AUDIO_I2S_PARALLEL_TYPE()           (g_stAudioParallelInfo.enumI2sParallelTypeInfo)
#define SET_AUDIO_I2S_PARALLEL_TYPE(x)          (g_stAudioParallelInfo.enumI2sParallelTypeInfo = (x))
#endif
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#define GET_TTS_PLAYBACK_CHANGE()               (bit)(g_stAudioInfo.b1TtsPlaybackStateChange)
#define SET_TTS_PLAYBACK_CHANGE()               (g_stAudioInfo.b1TtsPlaybackStateChange = _TRUE)
#define CLR_TTS_PLAYBACK_CHANGE()               (g_stAudioInfo.b1TtsPlaybackStateChange = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumInputPort enumAudioPlaybackSearchPort;

#if(_LINE_IN_SUPPORT == _ON)
    BYTE b1AudioPowerCutToLineInStatus : 1;
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    BYTE b1TtsPlaybackStateChange : 1;
#endif
} StructAudioInfoType;

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Audio ParallelmodeInfo Type
//--------------------------------------------------
typedef struct
{
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
    EnumAudioSpdifParallelMode enumSpdifParallelInfo;
#endif
#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
    EnumAudioI2sParallelMode enumI2sParallelModeInfo;
    EnumAudioI2sParallelType enumI2sParallelTypeInfo;
#endif
} StructAudioParalleInfo;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructAudioInfoType g_stAudioInfo;

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
extern StructAudioParalleInfo g_stAudioParallelInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysAudioHandler(void);
extern void SysAudioInitialSetting(void);
#if(_SLEEP_AUDIO_SUPPORT == _ON)
extern bit SysAudioPlayingAloneStatus(void);
#endif
extern void SysAudioPowerProc(EnumPowerAction enumSwitch);
extern void SysAudioPowerCutProc(EnumInputPort enumPowerCutOnPort, EnumPortType enumPowerCutOnPortType, EnumInputPort enumPowerCutOffPort, EnumPortType enumPowerCutOffPortType);

#if(_DP_SUPPORT == _ON)
extern void SysAudioDpAudioSecDataResetProc(EnumInputPort enumInputPort);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
#if(_HDMI_CEC_SUPPORT == _ON)
extern void SysAudioArcTxCecSetRequestArcInitiateRetryTimeout(void);
extern void SysAudioArcTxCecSetRequestArcTerminateRetryTimeout(void);
#endif
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)
