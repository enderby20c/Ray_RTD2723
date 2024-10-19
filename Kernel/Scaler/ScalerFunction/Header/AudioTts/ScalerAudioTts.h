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
// ID Code      : ScalerAudioTts.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_AUDIO_TTS_H__
#define __SCALER_AUDIO_TTS_H__

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
extern void ScalerAudioTtsSpicReset_EXINT0(void);
extern void ScalerAudioTtsSpicReset_WDINT(void);
extern void ScalerAudioTtsSpicBlk0_EXINT0(void);
extern void ScalerAudioTtsSpicBlk1_EXINT0(void);
extern void ScalerAudioTtsBlk0BurstReadConfig_EXINT0(DWORD ulAddress, WORD usLength);
extern void ScalerAudioTtsBlk1BurstReadConfig_EXINT0(DWORD ulAddress, WORD usLength);
extern void ScalerAudioTtsUpsamplingControl_EXINT0(bit bEn);
extern void ScalerAudioTtsUpsamplingControl_WDINT(bit bEn);
extern void ScalerAudioTtsUpsamplingSetFrequency(void);
extern void ScalerAudioTtsPlayDone_EXINT0(void);
extern void ScalerAudioTtsSpicPingPong_EXINT0(void);
extern void ScalerAudioTtsPlayDoneDetect_EXINT0(bit bEn);
extern void ScalerAudioTtsStartCommandData_WDINT(void);
extern void ScalerAudioTtsBurstReadStart_WDINT(void);
extern EnumAudioSpicStatus ScalerAudioTtsGetBurstStatus(void);
extern void ScalerAudioTtsBlk0BurstReadConfig_WDINT(DWORD ulAddress, WORD usLength);
extern void ScalerAudioTtsBlk1BurstReadConfig_WDINT(DWORD ulAddress, WORD usLength);
extern EnumAudioTtsDataWidth ScalerAudioTtsGetDataWidth(void);

#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_AUDIO_TTS_H__
