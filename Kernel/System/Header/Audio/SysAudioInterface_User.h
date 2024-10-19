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
// ID Code      : SysAudioInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Audio State
//--------------------------------------------------
typedef enum
{
    _AUDIO_STATUS_POWER_OFF,
    _AUDIO_STATUS_MODE_SWITCH,
    _AUDIO_STATUS_RESET_TO_PREPARING,
    _AUDIO_STATUS_PREPARING,
    _AUDIO_STATUS_SETTING,
#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
    _AUDIO_STATUS_PLAYBACKCHECK,
#endif
    _AUDIO_STATUS_PLAYBACK,
    _AUDIO_STATUS_TTS_PLAYBACK,
} EnumAudioState;

typedef enum
{
    _AUDIO_DVC_NORMAL_MODE,
    _AUDIO_DVC_FAST_MODE,
} EnumAudioDVCControlType;

//--------------------------------------------------
// Structure of Region Info
//--------------------------------------------------
typedef struct
{
    bit b1AudioStateChange;
#if(_SLEEP_AUDIO_SUPPORT == _ON)
    BYTE b1AudioPlayingAlone : 1;
#endif
    EnumAudioStatus enumInputReadyStatus;
    EnumInputPort enumInputport;
    EnumAudioOutputType enumOutputport;
    EnumAudioState enumAudioState;
    EnumAudioState enumPreviousAudioState;
    EnumAudioCodingType enumAudioPathLpcmInfoBackup;
    EnumAudioSamplingFreqPacket enumAudioSamplingFreqPacket;
    EnumAudioChannelCount enumAudioChannelCount;

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    EnumInputPort enumAudioGenInputPort;
#endif
} StructAudioInfo;

extern StructAudioInfo g_pstAudioPathInfo[_AUDIO_PATH_VALID];

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysAudioOutputProc(EnumAudioOutputType enumAudioOutput, bit bEnable);
extern EnumAudioState SysAudioGetAudioState(void);
extern BYTE SysAudioGetAudioPath(EnumAudioOutputType enumAudioOutput);
extern EnumAudioInputSource SysAudioGetInputSourceType(EnumAudioOutputType enumAudioOutput);
extern void SysAudioMuteProc(bit bMute);
extern void SysAudioDacOutputProc(bit bEnable);
extern bit SysAudioLpcmStatusChange(BYTE ucPathIndex);
extern bit SysAudioSamplingFreqChange(EnumAudioOutputType enumAudioOutput);

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
extern void SysAudioParallelModeOutput(EnumAudioOutputType enumAudioOutput, bit bEnable);
extern void SysAudioParallelModeSetting(bit bEnable);
extern bit SysAudioParallelModeTypeChange(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern void SysAudioInternalGenTestProc(bit bOn);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
#if(_HDMI_CEC_SUPPORT == _ON)
extern void SysAudioArcTxCecActiveRequestArcInitiateRetryTimer(void);
extern void SysAudioArcTxCecActiveRequestArcTerminateRetryTimer(void);
#endif
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

