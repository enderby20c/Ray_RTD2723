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
// ID Code      : ScalerDpMacStreamRx2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_STREAM_RX2_H__
#define __SCALER_DP_MAC_STREAM_RX2_H__

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX2_SUPPORT == _ON))
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
extern void ScalerDpMacStreamRx2SetHblankSupportNoSfMode(void);
extern bit ScalerDpMacStreamRx2PixelModeSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);

extern void ScalerDpMacStreamRx2SetSdpBuffRcvInitial(void);
extern void ScalerDpMacStreamRx2SetSdpBuffRcvMode(EnumDpSdpRamIndex enumDpSdpRamIndex, EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx2SetMetaSdpRcvInitial(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx2SetVscSdpRcvInitial(void);
extern bit ScalerDpMacStreamRx2VscCheck(void);
extern void ScalerDpMacStreamRx2SetMsaReset(void);
extern void ScalerDpMacStreamRx2SetSdpReset(void);
extern void ScalerDpMacStreamRx2SetSdpInitStatus(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx2GetPpsSdpInfo(void);
extern void ScalerDpMacStreamRx2SdpRevDetect(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx2SdpChgDetect(EnumDpSdpType enumDpSdpType);

extern void ScalerDpMacStreamRx2ColorimetrySetting(void);
extern void ScalerDpMacStreamRx2ColorimetryExtSetting(void);
extern void ScalerDpMacStreamRx2QuantizationSetting(void);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx2GetColorSpaceChgWDStatus(void);
extern bit ScalerDpMacStreamRx2GetFifoIRQStatus(void);
extern void ScalerDpMacStreamRx2ClrFifoFlag(void);
extern void ScalerDpMacStreamRx2DMColorFormatChgWoResetSetting(void);
#endif

extern void ScalerDpMacStreamRx2VideoSetting(void);
extern bit ScalerDpMacStreamRx2SetPLLInputClockSetting(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2SetPLLFreqNf(DWORD ulPllTargetClockHz, StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern void ScalerDpMacStreamRx2SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern void ScalerDpMacStreamRx2PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx2SetPllTrackingMode(EnumDpTrackingMode enumDpTrackingMode, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx2WaitVBlanking(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx2HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
extern bit ScalerDpMacStreamRx2CheckMultipleClkFeatureSupport(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern bit ScalerDpMacStreamRx2PllTargetClockPixelModeJudge(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit, DWORD *pulPllTargetClockHz, EnumDpStreamPixelMode *penumPixelMode);
extern bit ScalerDpMacStreamRx2PllOutputDivSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx2StreamClockSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2FrameSyncBeModeCheck(void);
extern bit ScalerDpMacStreamRx2NoNeedKeepTrackingCheck(void);
extern bit ScalerDpMacStreamRx2KeepMeasureEnableCheck(void);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2HPorchEnlarge(StructTimingInfo *pstDpTimingInfo);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx2GetFreeSyncStatusChange(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2PRModeSetPrStateChangeIrq(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx2GetSdpPktData_EXINT0(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx2GetMetaPktData_EXINT0(StructDpSdpMetaInfo structDpSdpMetaInfo, BYTE *pucMetaData, BYTE ucOffset, BYTE ucLength);
#endif

///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern bit ScalerDpMacStreamRx2PixelModeSetting_8b10b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx2VideoSetting_8b10b(void);
extern void ScalerDpMacStreamRx2SetBxToVsDelay_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2FifoCheck_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpMacStreamRx2AdjustVsyncDelay_8b10b(StructDpInfo *pstDpInfo);

extern void ScalerDpMacStreamRx2WaitVBlanking_8B10B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx2SdpChgDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx2SdpRevDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx2GetPpsSdpInfo_8b10b(void);
extern void ScalerDpMacStreamRx2SetSdpInitStatus_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern UnionDpRxMsaValue ScalerDpMacStreamRx2GetMsaInfo_8b10b(EnumDpRxMsaType enumDpRxMsaType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetSdpMetaSramRcvMode_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd);
extern void ScalerDpMacStreamRx2SdpMetaSramIrqEnable_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable);
#endif

extern void ScalerDpMacStreamRx2SdpIrqEnable_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx2SetSdpReset_8b10b(void);
extern void ScalerDpMacStreamRx2SdpSramReset_8b10b(void);

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
extern void ScalerDpMacStreamRx2Set1stBeIrqEnable_8b10b(bit bEnable);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx2DualCableJudge_8b10b(void);
#endif

#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2DscSetStreamWD_8b10b(bit bEnable);
extern void ScalerDpMacStreamRx2DscSetStreamIRQ_8b10b(bit bEnable);
extern bit ScalerDpMacStreamRx2DscChunkLengthCheck_8b10b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

#if((_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx2DscStatusReset_8b10b(void);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx2DscStreamChangeCheck_8b10b(void);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetColorSpaceChangeWD_8b10b(bit bEn);
extern void ScalerDpMacStreamRx2SstSetMsaChangeIRQ_8b10b(bit bEn);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2PRModeSetPrStateChangeIrq_8b10b(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2DscSetStreamWD_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx2DscSetStreamIRQ_8b10b_EXINT0(bit bEnable);
#endif


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx2PixelModeSetting_128b132b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx2VideoSetting_128b132b(void);
extern void ScalerDpMacStreamRx2SetBxToVsDelay_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2FifoCheck_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpMacStreamRx2AdjustVsyncDelay_128b132b(StructDpInfo *pstDpInfo);

extern void ScalerDpMacStreamRx2WaitVBlanking_128B132B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx2SdpChgDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx2SdpRevDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx2GetPpsSdpInfo_128b132b(void);
extern void ScalerDpMacStreamRx2SetSdpInitStatus_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern UnionDpRxMsaValue ScalerDpMacStreamRx2GetMsaInfo_128b132b(EnumDpRxMsaType enumDpRxMsaType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetSdpMetaSramRcvMode_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd);
extern void ScalerDpMacStreamRx2SdpMetaSramIrqEnable_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable);
#endif

extern void ScalerDpMacStreamRx2SdpIrqEnable_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx2SetSdpReset_128b132b(void);
extern void ScalerDpMacStreamRx2SdpSramReset_128b132b(void);

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
extern void ScalerDpMacStreamRx2Set1stBeIrqEnable_128b132b(bit bEnable);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx2DualCableJudge_128b132b(void);
#endif

#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2DscSetStreamWD_128b132b(bit bEnable);
extern void ScalerDpMacStreamRx2DscSetStreamIRQ_128b132b(bit bEnable);
extern bit ScalerDpMacStreamRx2DscChunkLengthCheck_128b132b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx2DscStreamChangeCheck_128b132b(void);
#endif

#if((_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx2DscStatusReset_128b132b(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2PRModeSetPrStateChangeIrq_128b132b(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2DscSetStreamWD_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx2DscSetStreamIRQ_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetColorSpaceChangeWD_128b132b(bit bEn);
#endif
#endif // End of #if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif

#endif // End of #ifndef __SCALER_DP_MAC_STREAM_RX2_H__
