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
// ID Code      : ScalerHdmiAudioRx3.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_HDMI_AUDIO_RX3_H__
#define __SCALER_HDMI_AUDIO_RX3_H__


#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
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
extern void ScalerHdmiAudioRx3InitialForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx3LoadInitialICode(void);
extern void ScalerHdmiAudioRx3SetAudioPLL(void);
extern void ScalerHdmiAudioRx3FifoTrackingProc(bit bEnable);
#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerHdmiAudioRx3FwTrackingInitialForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx3FwTrackingResetForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx3FwPreparingTrackingForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx3FwBoundaryTrackingForHdmiTmdsMac(void);
extern void ScalerHdmiAudioRx3FwLoadNfPll(void);
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
extern void ScalerHdmiAudioRx3InitialForHdmiFrlMac(void);
extern void ScalerHdmiAudioRx3AudioFrequencyModeForHdmiFrlMac(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerHdmiAudioRx3FwTrackingInitialForHdmiFrlMac(void);
extern void ScalerHdmiAudioRx3FwTrackingResetForHdmiFrlMac(void);
extern void ScalerHdmiAudioRx3FwPreparingTrackingForHdmiFrlMac(void);
extern void ScalerHdmiAudioRx3FwBoundaryTrackingForHdmiFrlMac(void);
#endif
#endif
extern void ScalerHdmiAudioRx3AudioFrequencyModeForHdmiTmdsMac(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
__attribute__((section(".itcm_section.ScalerHdmiAudioRx3HbrAudioOutputForFrl")))
extern void ScalerHdmiAudioRx3HbrAudioOutputForFrl(void);
#endif

__attribute__((section(".itcm_section.ScalerHdmiAudioRx3HbrAudioOutputForTmds")))
extern void ScalerHdmiAudioRx3HbrAudioOutputForTmds(void);
#endif
#endif // End of #if(_HDMI_AUDIO_RX3_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_HDMI_AUDIO_RX3_H__
