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
// ID Code      : ScalerAudioTtsInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

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
extern void ScalerAudioTtsResetProc(void);
extern void ScalerAudioTtsRecoverProc(void);
extern bit ScalerAudioTtsPlaybackStableCheck(void);
extern bit ScalerAudioTtsGetPlayDoneStatus(void);
extern void ScalerAudioTtsPlayConfig(void);
extern void ScalerAudioTtsDvcGainControl(WORD usTtsVolume, WORD usAudioVolume);
extern void ScalerAudioTtsSpicReset(void);
extern bit ScalerAudioTtsGetCommandData(StructAudioTtsSegment *pstAudioTtsSegment, BYTE ucSegmentSize);
extern void ScalerAudioTtsUpsamplingControl(bit bEn);
extern void ScalerAudioTtsSetUserDefineAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq);
extern void ScalerAudioTtsPlayDoneDetect(bit bEn);
extern void ScalerAudioTtsIntHandler_EXINT0(void);
extern bit ScalerAudioTtsGetPlaybackEvent(void);
extern void ScalerAudioTtsSetPlaybackEvent(bit bEn);
extern void ScalerAudioTtsSetTimerEvent(bit bEn);
extern void ScalerAudioTtsClearFlag(void);

#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

