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
// ID Code      : ScalerDpMacStreamRx0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_STREAM_RX0_H__
#define __SCALER_DP_MAC_STREAM_RX0_H__

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX0_SUPPORT == _ON))
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
extern void ScalerDpMacStreamRx0SetHblankSupportNoSfMode(void);
extern bit ScalerDpMacStreamRx0PixelModeSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);

extern void ScalerDpMacStreamRx0SetSdpBuffRcvInitial(void);
extern void ScalerDpMacStreamRx0SetSdpBuffRcvMode(EnumDpSdpRamIndex enumDpSdpRamIndex, EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx0SetMetaSdpRcvInitial(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx0SetVscSdpRcvInitial(void);
extern bit ScalerDpMacStreamRx0VscCheck(void);
extern void ScalerDpMacStreamRx0SetMsaReset(void);
extern void ScalerDpMacStreamRx0SetSdpReset(void);
extern void ScalerDpMacStreamRx0SetSdpInitStatus(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx0GetPpsSdpInfo(void);
extern void ScalerDpMacStreamRx0SdpRevDetect(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx0SdpChgDetect(EnumDpSdpType enumDpSdpType);

extern void ScalerDpMacStreamRx0ColorimetrySetting(void);
extern void ScalerDpMacStreamRx0ColorimetryExtSetting(void);
extern void ScalerDpMacStreamRx0QuantizationSetting(void);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx0GetColorSpaceChgWDStatus(void);
extern bit ScalerDpMacStreamRx0GetFifoIRQStatus(void);
extern void ScalerDpMacStreamRx0ClrFifoFlag(void);
extern void ScalerDpMacStreamRx0DMColorFormatChgWoResetSetting(void);
#endif

extern void ScalerDpMacStreamRx0VideoSetting(void);
extern bit ScalerDpMacStreamRx0SetPLLInputClockSetting(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0SetPLLFreqNf(DWORD ulPllTargetClockHz, StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern void ScalerDpMacStreamRx0SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern void ScalerDpMacStreamRx0PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx0SetPllTrackingMode(EnumDpTrackingMode enumDpTrackingMode, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx0WaitVBlanking(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx0HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
extern bit ScalerDpMacStreamRx0CheckMultipleClkFeatureSupport(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern bit ScalerDpMacStreamRx0PllTargetClockPixelModeJudge(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit, DWORD *pulPllTargetClockHz, EnumDpStreamPixelMode *penumPixelMode);
extern bit ScalerDpMacStreamRx0PllOutputDivSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx0StreamClockSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0FrameSyncBeModeCheck(void);
extern bit ScalerDpMacStreamRx0NoNeedKeepTrackingCheck(void);
extern bit ScalerDpMacStreamRx0KeepMeasureEnableCheck(void);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0HPorchEnlarge(StructTimingInfo *pstDpTimingInfo);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx0GetFreeSyncStatusChange(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0PRModeSetPrStateChangeIrq(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx0GetSdpPktData_EXINT0(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx0GetMetaPktData_EXINT0(StructDpSdpMetaInfo structDpSdpMetaInfo, BYTE *pucMetaData, BYTE ucOffset, BYTE ucLength);
#endif

///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern bit ScalerDpMacStreamRx0PixelModeSetting_8b10b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx0VideoSetting_8b10b(void);
extern void ScalerDpMacStreamRx0SetBxToVsDelay_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0FifoCheck_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpMacStreamRx0AdjustVsyncDelay_8b10b(StructDpInfo *pstDpInfo);

extern void ScalerDpMacStreamRx0WaitVBlanking_8B10B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx0SdpChgDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx0SdpRevDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx0GetPpsSdpInfo_8b10b(void);
extern void ScalerDpMacStreamRx0SetSdpInitStatus_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern UnionDpRxMsaValue ScalerDpMacStreamRx0GetMsaInfo_8b10b(EnumDpRxMsaType enumDpRxMsaType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetSdpMetaSramRcvMode_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd);
extern void ScalerDpMacStreamRx0SdpMetaSramIrqEnable_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable);
#endif

extern void ScalerDpMacStreamRx0SdpIrqEnable_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx0SetSdpReset_8b10b(void);
extern void ScalerDpMacStreamRx0SdpSramReset_8b10b(void);

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
extern void ScalerDpMacStreamRx0Set1stBeIrqEnable_8b10b(bit bEnable);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx0DualCableJudge_8b10b(void);
#endif

#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0DscSetStreamWD_8b10b(bit bEnable);
extern void ScalerDpMacStreamRx0DscSetStreamIRQ_8b10b(bit bEnable);
extern bit ScalerDpMacStreamRx0DscChunkLengthCheck_8b10b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx0DscStreamChangeCheck_8b10b(void);
#endif

#if((_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx0DscStatusReset_8b10b(void);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetColorSpaceChangeWD_8b10b(bit bEn);
extern void ScalerDpMacStreamRx0SstSetMsaChangeIRQ_8b10b(bit bEn);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0PRModeSetPrStateChangeIrq_8b10b(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0DscSetStreamWD_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx0DscSetStreamIRQ_8b10b_EXINT0(bit bEnable);
#endif


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx0PixelModeSetting_128b132b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx0VideoSetting_128b132b(void);
extern void ScalerDpMacStreamRx0SetBxToVsDelay_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0FifoCheck_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpMacStreamRx0AdjustVsyncDelay_128b132b(StructDpInfo *pstDpInfo);

extern void ScalerDpMacStreamRx0WaitVBlanking_128B132B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx0SdpChgDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx0SdpRevDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx0GetPpsSdpInfo_128b132b(void);
extern void ScalerDpMacStreamRx0SetSdpInitStatus_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern UnionDpRxMsaValue ScalerDpMacStreamRx0GetMsaInfo_128b132b(EnumDpRxMsaType enumDpRxMsaType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetSdpMetaSramRcvMode_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd);
extern void ScalerDpMacStreamRx0SdpMetaSramIrqEnable_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable);
#endif

extern void ScalerDpMacStreamRx0SdpIrqEnable_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx0SetSdpReset_128b132b(void);
extern void ScalerDpMacStreamRx0SdpSramReset_128b132b(void);

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
extern void ScalerDpMacStreamRx0Set1stBeIrqEnable_128b132b(bit bEnable);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx0DualCableJudge_128b132b(void);
#endif

#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0DscSetStreamWD_128b132b(bit bEnable);
extern void ScalerDpMacStreamRx0DscSetStreamIRQ_128b132b(bit bEnable);
extern bit ScalerDpMacStreamRx0DscChunkLengthCheck_128b132b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx0DscStreamChangeCheck_128b132b(void);
#endif

#if((_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx0DscStatusReset_128b132b(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0PRModeSetPrStateChangeIrq_128b132b(bit bEnable);
#endif

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0DscSetStreamWD_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx0DscSetStreamIRQ_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetColorSpaceChangeWD_128b132b(bit bEn);
#endif
#endif // End of #if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif

#endif // End of #ifndef __SCALER_DP_MAC_STREAM_RX0_H__
