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
// ID Code      : ScalerDscDecoder1.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DSC_DECODER_1_H__
#define __SCALER_DSC_DECODER_1_H__

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)

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
extern bit ScalerDscDecoder1DecInfoCheck(void);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoder1GetDpTimingInfo(StructDscTimingInfo *pstDscTimingInfo);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDscDecoder1SetAlpmT1Vstart(WORD usAlpmT1Vstart);
#endif
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoder1GetHdmiTimingInfo(StructDscTimingInfo *pstDscTimingInfo);
#endif

extern bit ScalerDscDecoder1PpsTimingCheck(StructDscTimingInfo *pstDscTimingInfo);
extern void ScalerDscDecoder1RxTimingInfoAdjust(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder1StreamSetting(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder1StreamInfo(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder1GetDrrEnable(void);
extern bit ScalerDscDecoder1DisplayFormatSetting(StructDscTimingInfo *pstDscTimingInfo);
extern void ScalerDscDecoder1SetColorInfo(void);
extern void ScalerDscDecoder1SetBsToVsDelay(StructDscTimingInfo *pstDscTimingInfo);
extern void ScalerDscDecoder1SetInitialDecDelay(void);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoder1DpInterlaceCheck(StructDscTimingInfo *pstDscTimingInfo);
#endif

extern bit ScalerDscDecoder1StreamClkRegenerate(StructDscTimingInfo *pstDscTimingInfo);
extern bit ScalerDscDecoder1SetPLLFreqNf(DWORD ulPllTargetClockHz, DWORD ulPllInputClockHz);
extern void ScalerDscDecoder1SetPLLNfOffProc(DWORD ulvcoFreq, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs);
extern bit ScalerDscDecoder1SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b);
extern void ScalerDscDecoder1SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern void ScalerDscDecoder1PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl);
extern void ScalerDscDecoder1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType, EnumDpHSTrackingSelect enumDpHSTrackingSelect);
extern bit ScalerDscDecoder1SetPLLTrackingNf(StructDscTimingInfo *pstDscTimingInfo);

#endif // End of #if(_DSC_MAC_DECODER_1_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_DSC_DECODER_1_H__
