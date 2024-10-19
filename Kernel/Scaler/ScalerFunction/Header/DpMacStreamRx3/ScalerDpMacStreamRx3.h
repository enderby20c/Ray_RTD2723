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
// ID Code      : ScalerDpMacStreamRx3.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_STREAM_RX3_H__
#define __SCALER_DP_MAC_STREAM_RX3_H__

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX3_SUPPORT == _ON))
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
extern bit ScalerDpMacStreamRx3GetVideoStream(void);
extern bit ScalerDpMacStreamRx3MSACheck(void);
extern void ScalerDpMacStreamRx3SdpSetting(void);
extern void ScalerDpMacStreamRx3ColorimetrySetting(void);
extern void ScalerDpMacStreamRx3ColorimetryExtSetting(void);
extern void ScalerDpMacStreamRx3QuantizationSetting(void);
extern bit ScalerDpMacStreamRx3VscCheck(void);

extern void ScalerDpMacStreamRx3SetHblankSupportNoSfMode(void);

extern bit ScalerDpMacStreamRx3MeasureInput(void);
extern bit ScalerDpMacStreamRx3GetInputTimingInfo(void);
extern bit ScalerDpMacStreamRx3SetPLLInputClockSetting(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3CheckMultipleClkFeatureSupport(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern bit ScalerDpMacStreamRx3PllTargetClockPixelModeJudge(StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit, DWORD *pulPllTargetClockHz, EnumDpStreamPixelMode *penumPixelMode);
extern bit ScalerDpMacStreamRx3PixelModeSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);
extern bit ScalerDpMacStreamRx3PllOutputDivSetting(EnumInputPort enumInputPort, EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx3StreamClockSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3FrameSyncBeModeCheck(void);
extern bit ScalerDpMacStreamRx3NoNeedKeepTrackingCheck(void);
extern bit ScalerDpMacStreamRx3KeepMeasureEnableCheck(void);

extern void ScalerDpMacStreamRx3SetMsaReset(void);
extern void ScalerDpMacStreamRx3SetSdpReset(void);
extern void ScalerDpMacStreamRx3SetSdpBuffRcvInitial(void);
extern void ScalerDpMacStreamRx3SetSdpBuffRcvMode(EnumDpSdpRamIndex enumDpSdpRamIndex, EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx3SetMetaSdpRcvInitial(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx3SetVscSdpRcvInitial(void);
extern void ScalerDpMacStreamRx3SetSdpInitStatus(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx3GetPpsSdpInfo(void);
extern void ScalerDpMacStreamRx3SdpRevDetect(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx3SdpChgDetect(EnumDpSdpType enumDpSdpType);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3GetFreeSyncStatusChange(void);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3HPorchEnlarge(StructTimingInfo *pstDpTimingInfo);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeInitial(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeSetPrStateChangeIrq(bit bEnable);
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3GetColorSpaceChgWDStatus(void);
extern bit ScalerDpMacStreamRx3GetFifoIRQStatus(void);
extern void ScalerDpMacStreamRx3ClrFifoFlag(void);
extern void ScalerDpMacStreamRx3DMColorFormatChgWoResetSetting(void);
#endif

extern void ScalerDpMacStreamRx3VideoSetting(void);

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx3GetSdpPktData_EXINT0(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3GetMetaPktData_EXINT0(StructDpSdpMetaInfo structDpSdpMetaInfo, BYTE *pucMetaData, BYTE ucOffset, BYTE ucLength);
#endif

///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRx3AdjustVsyncDelay_8b10b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3SetBxToVsDelay_8b10b(StructDpInfo *pstDpInfo);

extern bit ScalerDpMacStreamRx3MSAActiveChange_8b10b(void);
extern void ScalerDpMacStreamRx3CrcCalculate_8b10b(void);
extern bit ScalerDpMacStreamRx3GetMsaTimingInfo_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3GetVbidInfo_8b10b(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx3GetMsaInfo_8b10b(EnumDpRxMsaType enumDpRxMsaType);
extern bit ScalerDpMacStreamRx3FifoCheckProc_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3StableDetect_8b10b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx3InterlaceCheck_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3InterlaceVtotalGetMSACheck_8b10b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3InterlaceReset_8b10b(void);
extern void ScalerDpMacStreamRx3SetBsToHsDelay_8b10b(StructTimingInfo *pstDpTimingInfo);
extern void ScalerDpMacStreamRx3VideoSetting_8b10b(void);
extern bit ScalerDpMacStreamRx3MiscCheck_8b10b(void);
extern bit ScalerDpMacStreamRx3GetVideoInfo_8b10b(void);
extern bit ScalerDpMacStreamRx3GetMeasureLinkInfo_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3DisplayFormatSetting_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3PixelModeSetting_8b10b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx3SetSdpInitStatus_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx3GetPpsSdpInfo_8b10b(void);
extern void ScalerDpMacStreamRx3SdpRevDetect_8b10b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx3WaitVBlanking_8B10B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx3SdpChgDetect_8b10b(EnumDpSdpType enumDpSdpType);

extern void ScalerDpMacStreamRx3AVMute_8b10b(void);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetSdpMetaSramRcvMode_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd);
extern void ScalerDpMacStreamRx3SdpMetaSramIrqEnable_8b10b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable);
#endif

extern void ScalerDpMacStreamRx3SdpIrqEnable_8b10b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx3SetSdpReset_8b10b(void);
extern void ScalerDpMacStreamRx3SdpSramReset_8b10b(void);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3DualCableJudge_8b10b(void);
#endif

#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3DscChunkLengthCheck_8b10b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
extern void ScalerDpMacStreamRx3DscSetStreamIRQ_8b10b(bit bEnable);
extern void ScalerDpMacStreamRx3DscSetStreamWD_8b10b(bit bEnable);
extern void ScalerDpMacStreamRx3DscSetStreamIRQ_8b10b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx3DscSetStreamWD_8b10b_EXINT0(bit bEnable);
#endif

#if((_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx3DscStatusReset_8b10b(void);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3DscStreamChangeCheck_8b10b(void);
#endif

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
extern void ScalerDpMacStreamRx3Set1stBeIrqEnable_8b10b(bit bEnable);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeCheckProc_8b10b(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetColorSpaceChangeWD_8b10b(bit bEn);
extern void ScalerDpMacStreamRx3SstSetMsaChangeIRQ_8b10b(bit bEn);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeSetPrStateChangeIrq_8b10b(bit bEnable);
#endif

///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3PixelModeSetting_128b132b(EnumDpStreamPixelMode enumPixelMode);
extern void ScalerDpMacStreamRx3AdjustVsyncDelay_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3SetBxToVsDelay_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3MSAActiveChange_128b132b(void);
extern void ScalerDpMacStreamRx3CrcCalculate_128b132b(void);
extern bit ScalerDpMacStreamRx3GetMsaTimingInfo_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3FifoCheckProc_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3StableDetect_128b132b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx3GetVbidInfo_128b132b(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx3GetMsaInfo_128b132b(EnumDpRxMsaType enumDpRxMsaType);
extern bit ScalerDpMacStreamRx3InterlaceCheck_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3InterlaceVtotalGetMSACheck_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3InterlaceReset_128b132b(void);
extern void ScalerDpMacStreamRx3SetBsToHsDelay_128b132b(StructTimingInfo *pstDpTimingInfo);
extern void ScalerDpMacStreamRx3VideoSetting_128b132b(void);
extern bit ScalerDpMacStreamRx3MiscCheck_128b132b(void);
extern bit ScalerDpMacStreamRx3GetVideoInfo_128b132b(void);
extern bit ScalerDpMacStreamRx3GetMeasureLinkInfo_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3DisplayFormatSetting_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3SetSdpInitStatus_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex);
extern void ScalerDpMacStreamRx3SdpRevDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx3WaitVBlanking_128B132B(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx3SdpChgDetect_128b132b(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx3AVMute_128b132b(void);
extern void ScalerDpMacStreamRx3GetPpsSdpInfo_128b132b(void);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetSdpMetaSramRcvMode_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, EnumDpSdpType enumDpSdpType, EnumDpSdpMetaRcvMd enumDpSdpMetaRcvMd);
extern void ScalerDpMacStreamRx3SdpMetaSramIrqEnable_128b132b(EnumDpSdpMetaIndex enumDpSdpMetaIndex, bit bEnable);
#endif

extern void ScalerDpMacStreamRx3SdpIrqEnable_128b132b(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRx3SetSdpReset_128b132b(void);
extern void ScalerDpMacStreamRx3SdpSramReset_128b132b(void);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3DualCableJudge_128b132b(void);
#endif

#if((_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx3DscStatusReset_128b132b(void);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeCheckProc_128b132b(EnumInputPort enumInputPort);
#endif

#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3DscChunkLengthCheck_128b132b(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
extern void ScalerDpMacStreamRx3DscSetStreamIRQ_128b132b(bit bEnable);
extern void ScalerDpMacStreamRx3DscSetStreamWD_128b132b(bit bEnable);
extern void ScalerDpMacStreamRx3DscSetStreamIRQ_128b132b_EXINT0(bit bEnable);
extern void ScalerDpMacStreamRx3DscSetStreamWD_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3DscStreamChangeCheck_128b132b(void);
#endif

#if(_DP_RX_SDP_META_SRAM_RESET_FW_MODE == _ON)
extern void ScalerDpMacStreamRx3Set1stBeIrqEnable_128b132b(bit bEnable);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetColorSpaceChangeWD_128b132b(bit bEn);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeSetPrStateChangeIrq_128b132b(bit bEnable);
#endif
#endif // End Of (_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End Of (_DP_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_DP_MAC_STREAM_RX3_H__
