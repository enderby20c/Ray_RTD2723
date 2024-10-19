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
// ID Code      : ScalerDpMacStreamRx4.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_STREAM_RX4_H__
#define __SCALER_DP_MAC_STREAM_RX4_H__

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX4_SUPPORT == _ON))
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
extern bit ScalerDpMacStreamRx4GetVideoStream(void);
extern bit ScalerDpMacStreamRx4MSACheck(void);
extern void ScalerDpMacStreamRx4SdpSetting(void);
extern void ScalerDpMacStreamRx4ColorimetrySetting(void);
extern void ScalerDpMacStreamRx4ColorimetryExtSetting(void);
extern void ScalerDpMacStreamRx4QuantizationSetting(void);
extern bit ScalerDpMacStreamRx4VscCheck(void);

extern void ScalerDpMacStreamRx4SetHblankSupportNoSfMode(void);

extern bit ScalerDpMacStreamRx4MeasureInput(void);
extern bit ScalerDpMacStreamRx4GetInputTimingInfo(void);
extern bit ScalerDpMacStreamRx4SetPLLInputClockSetting(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4CheckMultipleClkFeatureSupport(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern bit ScalerDpMacStreamRx4PllTargetClockPixelModeJudge(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit, DWORD *pulPllTargetClockHz, EnumDpStreamPixelMode *penumPixelMode);
extern bit ScalerDpMacStreamRx4PixelModeSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);
extern bit ScalerDpMacStreamRx4PllOutputDivSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx4StreamClockSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4FrameSyncBeModeCheck(void);
extern bit ScalerDpMacStreamRx4NoNeedKeepTrackingCheck(void);
extern bit ScalerDpMacStreamRx4KeepMeasureEnableCheck(void);

extern void ScalerDpMacStreamRx4SetMsaReset(void);
extern void ScalerDpMacStreamRx4SetSdpReset(void);
extern void ScalerDpMacStreamRx4SetSdpBuffRcvInitial(void);
extern void ScalerDpMacStreamRx4SetSdpBuffRcvMode(EnumDpSdpRamIndex enumDpSdpRamIndex, EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4SetMetaSdpRcvInitial(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4SetVscSdpRcvInitial(void);
extern void ScalerDpMacStreamRx4SetSdpInitStatus(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx4GetPpsSdpInfo(void);
extern void ScalerDpMacStreamRx4SdpRevDetect(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4SdpChgDetect(EnumDpSdpType enumDpSdpType);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4GetFreeSyncStatusChange(void);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4HPorchEnlarge(StructTimingInfo *pstDpTimingInfo);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeInitial(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeSetPrStateChangeIrq(bit bEnable);
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4GetColorSpaceChgWDStatus(void);
extern bit ScalerDpMacStreamRx4GetFifoIRQStatus(void);
extern void ScalerDpMacStreamRx4ClrFifoFlag(void);
extern void ScalerDpMacStreamRx4DMColorFormatChgWoResetSetting(void);
#endif

extern void ScalerDpMacStreamRx4VideoSetting(void);


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRx4AdjustVsyncDelay_8b10b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx4SetBxToVsDelay_8b10b(StructDpInfo *pstDpInfo);

extern bit ScalerDpMacStreamRx4MSAActiveChange_8b10b(void);
extern bit ScalerDpMacStreamRx4GetMsaTimingInfo_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4GetVbidInfo_8b10b(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx4GetMsaInfo_8b10b(EnumDpRxMsaType enumDpRxMsaType);
extern bit ScalerDpMacStreamRx4FifoCheckProc_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);

extern bit ScalerDpMacStreamRx4StableDetect_8b10b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx4InterlaceCheck_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4InterlaceVtotalGetMSACheck_8b10b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx4InterlaceReset_8b10b(void);
extern void ScalerDpMacStreamRx4SetBsToHsDelay_8b10b(StructTimingInfo *pstDpTimingInfo);

extern void ScalerDpMacStreamRx4VideoSetting_8b10b(void);
extern bit ScalerDpMacStreamRx4MiscCheck_8b10b(void);
extern bit ScalerDpMacStreamRx4GetVideoInfo_8b10b(void);
extern bit ScalerDpMacStreamRx4GetMeasureLinkInfo_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4DisplayFormatSetting_8b10b(StructDpInfo *pstDpInfo);

extern bit ScalerDpMacStreamRx4PixelModeSetting_8b10b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx4SetSdpInitStatus_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx4GetPpsSdpInfo_8b10b(void);
extern void ScalerDpMacStreamRx4SdpRevDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4WaitVBlanking_8B10B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx4SdpChgDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4SdpIrqEnable_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx4SetSdpReset_8b10b(void);
extern void ScalerDpMacStreamRx4SdpSramReset_8b10b(void);

extern void ScalerDpMacStreamRx4AVMute_8b10b(void);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4DualCableJudge_8b10b(void);
#endif

#if((_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx4DscStatusReset_8b10b(void);
#endif

#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4DscChunkLengthCheck_8b10b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
extern void ScalerDpMacStreamRx4DscSetStreamIRQ_8b10b(bit bEnable);
extern void ScalerDpMacStreamRx4DscSetStreamWD_8b10b(bit bEnable);
extern void ScalerDpMacStreamRx4DscSetStreamIRQ_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx4DscSetStreamWD_8b10b_EXINT0(bit bEnable);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4DscStreamChangeCheck_8b10b(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeCheckProc_8b10b(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetColorSpaceChangeWD_8b10b(bit bEn);
extern void ScalerDpMacStreamRx4SstSetMsaChangeIRQ_8b10b(bit bEn);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeSetPrStateChangeIrq_8b10b(bit bEnable);
#endif

///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4PixelModeSetting_128b132b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx4AdjustVsyncDelay_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx4SetBxToVsDelay_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4MSAActiveChange_128b132b(void);
extern void ScalerDpMacStreamRx4CrcCalculate_128b132b(void);
extern bit ScalerDpMacStreamRx4GetMsaTimingInfo_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4FifoCheckProc_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4StableDetect_128b132b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx4GetVbidInfo_128b132b(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx4GetMsaInfo_128b132b(EnumDpRxMsaType enumDpRxMsaType);
extern bit ScalerDpMacStreamRx4InterlaceCheck_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4InterlaceVtotalGetMSACheck_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx4InterlaceReset_128b132b(void);
extern void ScalerDpMacStreamRx4SetBsToHsDelay_128b132b(StructTimingInfo *pstDpTimingInfo);
extern void ScalerDpMacStreamRx4VideoSetting_128b132b(void);
extern bit ScalerDpMacStreamRx4MiscCheck_128b132b(void);
extern bit ScalerDpMacStreamRx4GetVideoInfo_128b132b(void);
extern bit ScalerDpMacStreamRx4GetMeasureLinkInfo_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4DisplayFormatSetting_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx4SetSdpInitStatus_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx4SdpRevDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4WaitVBlanking_128B132B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx4SdpChgDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4SdpIrqEnable_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx4SetSdpReset_128b132b(void);
extern void ScalerDpMacStreamRx4SdpSramReset_128b132b(void);
extern void ScalerDpMacStreamRx4AVMute_128b132b(void);
extern void ScalerDpMacStreamRx4GetPpsSdpInfo_128b132b(void);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4DualCableJudge_128b132b(void);
#endif

#if((_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx4DscStatusReset_128b132b(void);
#endif

#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4DscChunkLengthCheck_128b132b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
extern void ScalerDpMacStreamRx4DscSetStreamIRQ_128b132b(bit bEnable);
extern void ScalerDpMacStreamRx4DscSetStreamWD_128b132b(bit bEnable);
extern void ScalerDpMacStreamRx4DscSetStreamIRQ_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx4DscSetStreamWD_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4DscStreamChangeCheck_128b132b(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeCheckProc_128b132b(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetColorSpaceChangeWD_128b132b(bit bEn);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeSetPrStateChangeIrq_128b132b(bit bEnable);
#endif
#endif // End of #if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_DP_MAC_STREAM_RX4_H__
