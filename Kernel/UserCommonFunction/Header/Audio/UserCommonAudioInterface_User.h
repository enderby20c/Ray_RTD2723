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
// ID Code      : UserCommonAudioInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
extern bit UserCommonAudioGetAudioDetected(EnumInputPort enumInputPort);
extern void UserCommonAudioDigitalAdjustVolume(WORD usVolume);
extern EnumInputPort UserCommonAudioGetDigitalAudioPortMapping(void);
extern EnumAudioSamplingFreqPacket UserCommonAudioSamplingFreqDetect(EnumInputPort enumInputPort);
extern EnumAudioCodingType UserCommonAudioGetNonLPCMStatus(void);
extern BYTE UserCommonAudioGetDigitalAudioSource(EnumInputPort enumInputPort);

#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
extern EnumAudioSpdifParallelMode UserCommonAudioSpdifParallelMode(void);
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
extern EnumAudioI2sParallelMode UserCommonAudioI2sParallelMode(void);
extern EnumAudioI2sParallelType UserCommonAudioI2sParallelType(void);
#endif

#if(_DP_SUPPORT == _ON)
extern EnumAudioDpDpcdSupport UserCommonAudioDpGetCapabilityInitialState(EnumInputPort enumInputPort);

#if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
extern void UserCommonAudioDpSetCapabilityState(EnumInputPort enumInputPort, EnumAudioDpDpcdSupport enumDpcdSupport);
#endif // End of #if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_LINE_IN_SUPPORT == _ON)
extern EnumAudioInputSource UserCommonAudioGetInputSource(void);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern EnumAudioDACState UserCommonAudioDACGetState(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit UserCommonAudioGetInternalAudioGenEnable(EnumInputPort enumInputPort);
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
extern void UserCommonAudioTtsSetPlaybackActiveEvent(StructAudioTtsSegment *pstAudioTtsSegment, BYTE ucSegmentSize, BYTE ucTtsVolume, BYTE ucAudioVolume);
extern EnumAudioTtsPlayStatus UserCommonAudioTtsGetPlaybackStatus(void);
extern BYTE UserCommonAudioTtsGetErrorSegment(void);
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_AUDIO_ARC_SUPPORT == _ON)
extern EnumAudioCodingType UserCommonAudioGetArcNonLPCMStatus(void);
#endif

extern BYTE UserCommonAudioGetInputChannelAllocation(EnumInputPort enumInputPort);
extern EnumAudioChannelCount UserCommonAudioGetInputChannelCount(EnumInputPort enumInputPort);
extern StructAudioChannelInfo UserCommonAudioGetInputChannelStatus(EnumInputPort enumInputPort);
#endif