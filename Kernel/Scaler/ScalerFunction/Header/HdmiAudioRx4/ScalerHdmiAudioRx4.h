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
// ID Code      : ScalerHdmiAudioRx4.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_HDMI_AUDIO_RX4_H__
#define __SCALER_HDMI_AUDIO_RX4_H__


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
extern void ScalerHdmiAudioRx4InitialForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx4LoadInitialICode(void);
extern void ScalerHdmiAudioRx4SetAudioPLL(void);
extern void ScalerHdmiAudioRx4FifoTrackingProc(bit bEnable);
extern void ScalerHdmiAudioRx4AudioFrequencyModeForHdmiTmdsMac(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerHdmiAudioRx4FwTrackingInitialForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx4FwTrackingResetForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx4FwPreparingTrackingForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx4FwBoundaryTrackingForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx4FwLoadNfPll(void);
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
extern void ScalerHdmiAudioRx4InitialForHdmiFrlMac(void);
extern void ScalerHdmiAudioRx4AudioFrequencyModeForHdmiFrlMac(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerHdmiAudioRx4FwTrackingInitialForHdmiFrlMac(void);
extern void ScalerHdmiAudioRx4FwTrackingResetForHdmiFrlMac(void);
extern void ScalerHdmiAudioRx4FwPreparingTrackingForHdmiFrlMac(void);
extern void ScalerHdmiAudioRx4FwBoundaryTrackingForHdmiFrlMac(void);
#endif
#endif

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
__attribute__((section(".itcm_section.ScalerHdmiAudioRx4HbrAudioOutputForFrl")))
extern void ScalerHdmiAudioRx4HbrAudioOutputForFrl(void);
#endif

__attribute__((section(".itcm_section.ScalerHdmiAudioRx4HbrAudioOutputForTmds")))
extern void ScalerHdmiAudioRx4HbrAudioOutputForTmds(void);
#endif
#endif // End of #if(_HDMI_AUDIO_RX4_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_HDMI_AUDIO_RX4_H__
