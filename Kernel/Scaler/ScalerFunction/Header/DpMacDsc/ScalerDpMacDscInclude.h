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
// ID Code      : ScalerDpMacDscInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && ((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)))
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
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacDscStreamRxSinkStatusSetting(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscFifoStatusIrqProc(EnumDpMacSel enumDpMacSel, BYTE ucFifoCondition);
extern bit ScalerDpMacDscChunkCheckProc(EnumDpMacSel enumDpMacSel);
extern bit ScalerDpMacDscChunkLengthCheck(EnumDpMacSel enumDpMacSel, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
extern bit ScalerDpMacDscStreamRxGetMsaTimingInfo(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);
extern WORD ScalerDpMacDscStreamRxGetMsaVstart(EnumDpMacSel enumDpMacSel);
extern bit ScalerDpMacDscStreamRxGetVideoInfo(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscStreamRxSetColorInfo(EnumDpMacSel enumDpMacSel);
extern bit ScalerDpMacDscStreamRxGetMeasureLinkInfo(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacDscStreamRxStreamInfoSetting(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);
extern void ScalerDpMacDscStreamRxTimingInfoAdjust(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacDscStreamRxStreamClkRegenerate(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacDscStreamRxTrackingSetting(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);
extern void ScalerDpMacDscStreamRxSetVheight(EnumDpMacSel enumDpMacSel, WORD usVheight);
extern void ScalerDpMacDscStreamRxSetVfrontPorch(EnumDpMacSel enumDpMacSel, BYTE ucVfrontporch);
extern bit ScalerDpMacDscStreamRxInterlaceCheck(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacDscGetDscFlagStatus(EnumDpMacSel enumDpMacSel);

#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacDscAudioRxDisableSetting_EXINT0(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscAudioEnable_EXINT0(EnumDpMacSel enumDpMacSel, bit bEnable);
#endif
extern EnumDDomainRegion ScalerDpMacDscStreamRxGetForceBackgroundPath_EXINT0(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscStreamRxSetNoVideoStreamIRQ_EXINT0(EnumDpMacSel enumDpMacSel, bit bEnable);
extern void ScalerDpMacDscSyncDscColorInfo(EnumDpMacSel enumDpMacSel, EnumColorSpace enumColorSpace, BYTE ucColorDepth);
extern BYTE ScalerDpMacDscStreamRxGetQuantizationPreValue(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscSetInputPixelClk(EnumDpMacSel enumDpMacSel, DWORD ulStreamClk);
extern bit ScalerDpMacDscSetNativeInputPixelClkCheck(EnumDpMacSel enumDpMacSel);
extern bit ScalerDpMacDscRxDscStreamGetChange(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscRxDscStreamSetChange(EnumDpMacSel enumDpMacSel, bit bEnable);
extern void ScalerDpMacDscRxDscStreamClearChange(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscRxDscStreamSetChange_EXINT0(EnumDpMacSel enumDpMacSel, bit bEnable);
extern void ScalerDpMacDscStreamAfterJudgeSetting(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscStreamRxBsMissFlagClear(EnumDpMacSel enumDpMacSel);
#endif

extern bit ScalerDpMacDscRxDscStreamCheck(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacDscPpsTimeOutProc(EnumDpMacSel enumDpMacSel, bit bEn);
extern void ScalerDpMacDscPpsTimeOutEventProc(EnumDpMacSel enumDpMacSel);
#endif // #if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON)

