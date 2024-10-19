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
// ID Code      : ScalerDpMacStreamRx1.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_STREAM_RX1_H__
#define __SCALER_DP_MAC_STREAM_RX1_H__

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON))
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

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRx1SetHblankSupportNoSfMode(void);
extern bit ScalerDpMacStreamRx1PixelModeSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);

extern void ScalerDpMacStreamRx1SetSdpBuffRcvInitial(void);
extern void ScalerDpMacStreamRx1SetSdpBuffRcvMode(EnumDpSdpRamIndex enumDpSdpRamIndex, EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx1SetMetaSdpRcvInitial(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx1SetVscSdpRcvInitial(void);
extern bit ScalerDpMacStreamRx1VscCheck(void);
extern void ScalerDpMacStreamRx1SetMsaReset(void);
extern void ScalerDpMacStreamRx1SetSdpReset(void);
extern void ScalerDpMacStreamRx1SetSdpInitStatus(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx1GetPpsSdpInfo(void);
extern void ScalerDpMacStreamRx1SdpRevDetect(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx1SdpChgDetect(EnumDpSdpType enumDpSdpType);

extern void ScalerDpMacStreamRx1ColorimetrySetting(void);
extern void ScalerDpMacStreamRx1ColorimetryExtSetting(void);
extern void ScalerDpMacStreamRx1QuantizationSetting(void);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx1GetColorSpaceChgWDStatus(void);
extern bit ScalerDpMacStreamRx1GetFifoIRQStatus(void);
extern void ScalerDpMacStreamRx1ClrFifoFlag(void);
extern void ScalerDpMacStreamRx1DMColorFormatChgWoResetSetting(void);
#endif

extern void ScalerDpMacStreamRx1VideoSetting(void);
extern bit ScalerDpMacStreamRx1SetPLLInputClockSetting(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1SetPLLFreqNf(DWORD ulPllTargetClockHz, StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern void ScalerDpMacStreamRx1SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern void ScalerDpMacStreamRx1PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx1SetPllTrackingMode(EnumDpTrackingMode enumDpTrackingMode, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx1WaitVBlanking(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
extern bit ScalerDpMacStreamRx1CheckMultipleClkFeatureSupport(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern bit ScalerDpMacStreamRx1PllTargetClockPixelModeJudge(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit, DWORD *pulPllTargetClockHz, EnumDpStreamPixelMode *penumPixelMode);
extern bit ScalerDpMacStreamRx1PllOutputDivSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx1StreamClockSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1FrameSyncBeModeCheck(void);
extern bit ScalerDpMacStreamRx1NoNeedKeepTrackingCheck(void);
extern bit ScalerDpMacStreamRx1KeepMeasureEnableCheck(void);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1HPorchEnlarge(StructTimingInfo *pstDpTimingInfo);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx1GetFreeSyncStatusChange(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx1GetSdpPktData_EXINT0(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx1GetMetaPktData_EXINT0(StructDpSdpMetaInfo structDpSdpMetaInfo, BYTE *pucMetaData, BYTE ucOffset, BYTE ucLength);
#endif


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern bit ScalerDpMacStreamRx1PixelModeSetting_8b10b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx1VideoSetting_8b10b(void);
extern void ScalerDpMacStreamRx1SetBxToVsDelay_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1FifoCheck_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpMacStreamRx1AdjustVsyncDelay_8b10b(StructDpInfo *pstDpInfo);

extern void ScalerDpMacStreamRx1WaitVBlanking_8B10B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx1SdpChgDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx1SdpRevDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx1GetPpsSdpInfo_8b10b(void);
extern void ScalerDpMacStreamRx1SetSdpInitStatus_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern UnionDpRxMsaValue ScalerDpMacStreamRx1GetMsaInfo_8b10b(EnumDpRxMsaType enumDpRxMsaType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetSdpMetaSramRcvMode_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd);
extern void ScalerDpMacStreamRx1SdpMetaSramIrqEnable_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable);
#endif

extern void ScalerDpMacStreamRx1SdpIrqEnable_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx1SetSdpReset_8b10b(void);
extern void ScalerDpMacStreamRx1SdpSramReset_8b10b(void);

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
extern void ScalerDpMacStreamRx1Set1stBeIrqEnable_8b10b(bit bEnable);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx1DualCableJudge_8b10b(void);
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1DscSetStreamWD_8b10b(bit bEnable);
extern void ScalerDpMacStreamRx1DscSetStreamIRQ_8b10b(bit bEnable);
extern bit ScalerDpMacStreamRx1DscChunkLengthCheck_8b10b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx1DscStreamChangeCheck_8b10b(void);
#endif

#if((_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx1DscStatusReset_8b10b(void);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetColorSpaceChangeWD_8b10b(bit bEn);
extern void ScalerDpMacStreamRx1SstSetMsaChangeIRQ_8b10b(bit bEn);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_8b10b(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1DscSetStreamWD_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx1DscSetStreamIRQ_8b10b_EXINT0(bit bEnable);
#endif


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx1PixelModeSetting_128b132b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx1VideoSetting_128b132b(void);
extern void ScalerDpMacStreamRx1SetBxToVsDelay_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1FifoCheck_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpMacStreamRx1AdjustVsyncDelay_128b132b(StructDpInfo *pstDpInfo);

extern void ScalerDpMacStreamRx1WaitVBlanking_128B132B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx1SdpChgDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx1SdpRevDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx1GetPpsSdpInfo_128b132b(void);
extern void ScalerDpMacStreamRx1SetSdpInitStatus_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern UnionDpRxMsaValue ScalerDpMacStreamRx1GetMsaInfo_128b132b(EnumDpRxMsaType enumDpRxMsaType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetSdpMetaSramRcvMode_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd);
extern void ScalerDpMacStreamRx1SdpMetaSramIrqEnable_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable);
#endif

extern void ScalerDpMacStreamRx1SdpIrqEnable_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx1SetSdpReset_128b132b(void);
extern void ScalerDpMacStreamRx1SdpSramReset_128b132b(void);

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
extern void ScalerDpMacStreamRx1Set1stBeIrqEnable_128b132b(bit bEnable);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx1DualCableJudge_128b132b(void);
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1DscSetStreamWD_128b132b(bit bEnable);
extern void ScalerDpMacStreamRx1DscSetStreamIRQ_128b132b(bit bEnable);
extern bit ScalerDpMacStreamRx1DscChunkLengthCheck_128b132b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx1DscStreamChangeCheck_128b132b(void);
#endif

#if((_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx1DscStatusReset_128b132b(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1PRModeSetPrStateChangeIrq_128b132b(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1DscSetStreamWD_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx1DscSetStreamIRQ_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetColorSpaceChangeWD_128b132b(bit bEn);
#endif
#endif // End of #if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif

#endif // End of #ifndef __SCALER_DP_MAC_STREAM_RX1_H__
