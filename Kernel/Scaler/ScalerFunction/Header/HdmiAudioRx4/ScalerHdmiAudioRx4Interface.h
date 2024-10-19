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
// ID Code      : ScalerHdmiAudioRx4Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)

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
extern void ScalerHdmiAudioRx4SetUserDefineAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
extern void ScalerHdmiAudioRx4SetUserDefineSamplingFreqLimit(EnumAudioSamplingFreqType enumAudioFreq);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

extern void ScalerHdmiAudioRx4SyncUserDefineFrequencyPllSetting(void);
#endif // End of #if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
