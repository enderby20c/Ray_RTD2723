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
// ID Code      : UserCommonAudioInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

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
extern EnumAudioStatus UserCommonAudioGetPathReadyToPlayStatus(EnumAudioOutputType enumAudioOutput);
extern bit UserCommonAudioGetAdjustVolumeThroughDVC(void);
extern void UserCommonAudioMuteCurrentDigitalPortProc(EnumInputPort enumInputPort);
extern EnumAudioSamplingFreqType UserCommonAudioUpdateUserSamplingFreq(void);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
extern EnumAudioSamplingFreqType UserCommonAudioGetSamplingFreqLimit(void);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

extern EnumAudioMuteStatus UserCommonAudioGetPathOutputMuteStatus(EnumAudioOutputType enumAudioOutput);
extern EnumAudioCodingType UserCommonAudioGetPathNonLPCMStatus(EnumAudioOutputType enumAudioOutput);
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern EnumAudioSamplingFreqType UserCommonAudioUpdateUserDefineAudioGenFreq(void);
extern EnumAudioLeftRightChannelSelect UserCommonAudioGetUserLeftRightChanelSelect(void);
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
extern EnumAudioInputSource UserCommonAudioGetArcSource(void);
extern EnumInputPort UserCommonAudioGetArcInputport(void);
extern EnumAudioArcMode UserCommonAudioGetArcMode(void);
extern EnumAudioMuteStatus UserCommonAudioGetArcMuteStatus(void);
extern EnumArcAudioChanelStatus UserCommonAudioGetArcChannel(void);
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)
