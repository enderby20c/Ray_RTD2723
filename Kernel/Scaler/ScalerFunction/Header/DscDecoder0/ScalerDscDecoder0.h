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
// ID Code      : ScalerDscDecoder0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DSC_DECODER_0_H__
#define __SCALER_DSC_DECODER_0_H__

#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)

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
extern bit ScalerDscDecoder0DecInfoCheck(void);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoder0GetDpTimingInfo(StructDscTimingInfo *pstDscTimingInfo);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDscDecoder0SetAlpmT1Vstart(WORD usAlpmT1Vstart);
#endif
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoder0GetHdmiTimingInfo(StructDscTimingInfo *pstDscTimingInfo);
#endif

extern bit ScalerDscDecoder0PpsTimingCheck(StructDscTimingInfo *pstDscTimingInfo);
extern void ScalerDscDecoder0RxTimingInfoAdjust(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder0StreamSetting(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder0StreamInfo(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder0DisplayFormatSetting(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder0GetDrrEnable(void);
extern void ScalerDscDecoder0SetColorInfo(void);
extern void ScalerDscDecoder0SetBsToVsDelay(StructDscTimingInfo *pstDscTimingInfo);
extern void ScalerDscDecoder0SetInitialDecDelay(void);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoder0DpInterlaceCheck(StructDscTimingInfo *pstDscTimingInfo);
#endif

extern bit ScalerDscDecoder0StreamClkRegenerate(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder0SetPLLFreqNf(DWORD ulPllTargetClockHz, DWORD ulPllInputClockHz);
extern void ScalerDscDecoder0SetPLLNfOffProc(DWORD ulvcoFreq, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs);
extern bit ScalerDscDecoder0SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b);
extern void ScalerDscDecoder0SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern void ScalerDscDecoder0PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl);
extern void ScalerDscDecoder0HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType, EnumDpHSTrackingSelect enumDpHSTrackingSelect);
extern bit ScalerDscDecoder0SetPLLTrackingNf(StructDscTimingInfo *pstDscTimingInfo);

#endif // End of #if(_DSC_MAC_DECODER_0_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_DSC_DECODER_0_H__
