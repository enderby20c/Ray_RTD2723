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
// ID Code      : ScalerHdmiFrlMacRx3.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_HDMI_FRL_MAC_RX3_H__
#define __SCALER_HDMI_FRL_MAC_RX3_H__

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of SCDC FRL_Rate Event
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT()                  (g_stHdmiFrlMacRx3CtrlInfo.b1FrlRateEvent)
#define SET_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT()                  (g_stHdmiFrlMacRx3CtrlInfo.b1FrlRateEvent = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_FRL_RATE_EVENT()                  (g_stHdmiFrlMacRx3CtrlInfo.b1FrlRateEvent = _FALSE)

//--------------------------------------------------
// Macro of SCDC FRL_Start
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_FRL_START_EVENT()                 (g_stHdmiFrlMacRx3CtrlInfo.b1FrlStartEvent)
#define SET_HDMI_FRL_MAC_RX3_FRL_START_EVENT()                 (g_stHdmiFrlMacRx3CtrlInfo.b1FrlStartEvent = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_FRL_START_EVENT()                 (g_stHdmiFrlMacRx3CtrlInfo.b1FrlStartEvent = _FALSE)

//--------------------------------------------------
// Macro of FRL Lane Lock
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_LANE0_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane0Lock)
#define SET_HDMI_FRL_MAC_RX3_LANE0_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane0Lock = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_LANE0_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane0Lock = _FALSE)

#define GET_HDMI_FRL_MAC_RX3_LANE1_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane1Lock)
#define SET_HDMI_FRL_MAC_RX3_LANE1_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane1Lock = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_LANE1_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane1Lock = _FALSE)

#define GET_HDMI_FRL_MAC_RX3_LANE2_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane2Lock)
#define SET_HDMI_FRL_MAC_RX3_LANE2_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane2Lock = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_LANE2_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane2Lock = _FALSE)

#define GET_HDMI_FRL_MAC_RX3_LANE3_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane3Lock)
#define SET_HDMI_FRL_MAC_RX3_LANE3_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane3Lock = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_LANE3_LOCK()                      (g_stHdmiFrlMacRx3CtrlInfo.b1Lane3Lock = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_PACKET_DETECTING()                (g_stHdmiFrlMacRx3CtrlInfo.b1PacketDetecting)
#define SET_HDMI_FRL_MAC_RX3_PACKET_DETECTING()                (g_stHdmiFrlMacRx3CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_PACKET_DETECTING()                (g_stHdmiFrlMacRx3CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of HDMI2.1 Rebuild PHY
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT()               (g_stHdmiFrlMacRx3CtrlInfo.b1RebuildPhyEvent)
#define SET_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT()               (g_stHdmiFrlMacRx3CtrlInfo.b1RebuildPhyEvent = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_REBUILD_PHY_EVENT()               (g_stHdmiFrlMacRx3CtrlInfo.b1RebuildPhyEvent = _FALSE)

//--------------------------------------------------
// Macro of HDMI2.1 Rebuild PHY
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_DPF_PIXEL_MODE_MISMATCH()         (g_stHdmiFrlMacRx3CtrlInfo.b1DpfPixelModeMismatch)
#define SET_HDMI_FRL_MAC_RX3_DPF_PIXEL_MODE_MISMATCH()         (g_stHdmiFrlMacRx3CtrlInfo.b1DpfPixelModeMismatch = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_DPF_PIXEL_MODE_MISMATCH()         (g_stHdmiFrlMacRx3CtrlInfo.b1DpfPixelModeMismatch = _FALSE)

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
//--------------------------------------------------
// Macro of HSR10+ VSIF/EMP Detecting Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_DETECTING()        (g_stHdmiFrlMacRx3CtrlInfo.b1FrlAdvancedHdr10Detecting)
#define SET_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_DETECTING()        (g_stHdmiFrlMacRx3CtrlInfo.b1FrlAdvancedHdr10Detecting = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_DETECTING()        (g_stHdmiFrlMacRx3CtrlInfo.b1FrlAdvancedHdr10Detecting = _FALSE)

//--------------------------------------------------
// Macro of HDR10+ VSIF Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_VSIF_RECEIVED()    (g_stHdmiFrlMacRx3CtrlInfo.b1FrlAdvancedHdr10VsifReceived)
#define SET_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_VSIF_RECEIVED()    (g_stHdmiFrlMacRx3CtrlInfo.b1FrlAdvancedHdr10VsifReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_ADVANCED_HDR10_VSIF_RECEIVED()    (g_stHdmiFrlMacRx3CtrlInfo.b1FrlAdvancedHdr10VsifReceived = _FALSE)

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
//--------------------------------------------------
// Macro of HDR10+ (D-HDR EMP) Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_DHDR_EMP_TYPE40_RECEIVED()        (g_stHdmiFrlMacRx3CtrlInfo.b1FrlDhdrEmpType40Received)
#define SET_HDMI_FRL_MAC_RX3_DHDR_EMP_TYPE40_RECEIVED()        (g_stHdmiFrlMacRx3CtrlInfo.b1FrlDhdrEmpType40Received = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_DHDR_EMP_TYPE40_RECEIVED()        (g_stHdmiFrlMacRx3CtrlInfo.b1FrlDhdrEmpType40Received = _FALSE)
#endif
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Macro of DM VSIF/EMP Detecting Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_DM_INFO_DETECTING()               (g_stHdmiFrlMacRx3CtrlInfo.b1DmInfoDetecting)
#define SET_HDMI_FRL_MAC_RX3_DM_INFO_DETECTING()               (g_stHdmiFrlMacRx3CtrlInfo.b1DmInfoDetecting = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_DM_INFO_DETECTING()               (g_stHdmiFrlMacRx3CtrlInfo.b1DmInfoDetecting = _FALSE)

//--------------------------------------------------
// Macro of DM VSIF Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_DM_VSIF_RECEIVED()                (g_stHdmiFrlMacRx3CtrlInfo.b1DmVsifReceived)
#define SET_HDMI_FRL_MAC_RX3_DM_VSIF_RECEIVED()                (g_stHdmiFrlMacRx3CtrlInfo.b1DmVsifReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_DM_VSIF_RECEIVED()                (g_stHdmiFrlMacRx3CtrlInfo.b1DmVsifReceived = _FALSE)

//--------------------------------------------------
// Macro of DM EMP Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_DM_EMP_RECEIVED()                 (g_stHdmiFrlMacRx3CtrlInfo.b1DmEmpReceived)
#define SET_HDMI_FRL_MAC_RX3_DM_EMP_RECEIVED()                 (g_stHdmiFrlMacRx3CtrlInfo.b1DmEmpReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_DM_EMP_RECEIVED()                 (g_stHdmiFrlMacRx3CtrlInfo.b1DmEmpReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of HF VSIF Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_HF_VSIF_RECEIVED()                (g_stHdmiFrlMacRx3CtrlInfo.b1HFVsifReceived)
#define SET_HDMI_FRL_MAC_RX3_HF_VSIF_RECEIVED()                (g_stHdmiFrlMacRx3CtrlInfo.b1HFVsifReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_HF_VSIF_RECEIVED()                (g_stHdmiFrlMacRx3CtrlInfo.b1HFVsifReceived = _FALSE)

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HF VSIF Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_HDMI_VSIF_RECEIVED()              (g_stHdmiFrlMacRx3CtrlInfo.b1HdmiVsifReceived)
#define SET_HDMI_FRL_MAC_RX3_HDMI_VSIF_RECEIVED()              (g_stHdmiFrlMacRx3CtrlInfo.b1HdmiVsifReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_HDMI_VSIF_RECEIVED()              (g_stHdmiFrlMacRx3CtrlInfo.b1HdmiVsifReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED()         (g_stHdmiFrlMacRx3CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED()         (g_stHdmiFrlMacRx3CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_AVI_INFO_FRAME_RECEIVED()         (g_stHdmiFrlMacRx3CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_GCP_RECEIVED()                    (g_stHdmiFrlMacRx3CtrlInfo.b1GCPReceived)
#define SET_HDMI_FRL_MAC_RX3_GCP_RECEIVED()                    (g_stHdmiFrlMacRx3CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_GCP_RECEIVED()                    (g_stHdmiFrlMacRx3CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define SET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION(x)           (g_ucHdmiFrlMacRx3AviInfo = (x))
#define GET_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION()            (g_ucHdmiFrlMacRx3AviInfo)
#define CLR_HDMI_FRL_MAC_RX3_AVI_PIXEL_REPETITION()            (g_ucHdmiFrlMacRx3AviInfo = 0)

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX3_SIGNAL_DETECTING()                (g_stHdmiFrlMacRx3CtrlInfo.b1SignalDetecting)
#define SET_HDMI_FRL_MAC_RX3_SIGNAL_DETECTING()                (g_stHdmiFrlMacRx3CtrlInfo.b1SignalDetecting = _TRUE)
#define CLR_HDMI_FRL_MAC_RX3_SIGNAL_DETECTING()                (g_stHdmiFrlMacRx3CtrlInfo.b1SignalDetecting = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3EmpSramSetting(bit bEnable);
#endif
extern void ScalerHdmiFrlMacRx3RsvIrqEnable(EnumHdmiRsvNumber enumRsvNumber, bit bEnable);
extern void ScalerHdmiFrlMacRx3RsvInitial(void);
extern void ScalerHdmiFrlMacRx3Initial(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRx3InterruptInitial(void);
#if(_3DDI_FUNCTION == _ON)
extern bit ScalerHdmiFrlMacRx3GetInterlace3ddiAvaible(void);
#endif
extern bit ScalerHdmiFrlMacRx3CedCheck(void);
extern bit ScalerHdmiFrlMacRx3RsedCheck(void);
extern bit ScalerHdmiFrlMacRx3FrlVideoCheck(void);

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern EnumSourceType ScalerHdmiFrlMacRx3SeamlessReset(void);
extern bit ScalerHdmiFrlMacRx3CheckSeamlessCondition(void);
#endif

extern bit ScalerHdmiFrlMacRx3MeasureCheck(void);
extern bit ScalerHdmiFrlMacRx3DisplayFormatSetting(void);
extern bit ScalerHdmiFrlMacRx3DPFHsyncHstartAdjust(WORD *pusDPFHsync, WORD *pusDPFHstart, WORD usDPFHblank);
extern bit ScalerHdmiFrlMacRx3StreamClkRegenerate(void);
extern void ScalerHdmiFrlMacRx3DPLLOnProc(WORD usVCOFreq, WORD usPLLinClkFreq);
extern void ScalerHdmiFrlMacRx3SetPGainClampValue (BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern bit ScalerHdmiFrlMacRx3DpfFifoCheck(bit bWait);
extern bit ScalerHdmiFrlMacRx3CheckCdrStable(WORD usClkCount);
extern void ScalerHdmiFrlMacRx3ResetAllPacketReceiveStatus(void);
extern void ScalerHdmiFrlMacRx3PacketDetect(bit bWait);
extern void ScalerHdmiFrlMacRx3WatchDog(BYTE ucWDType, bit bEnable);
extern void ScalerHdmiFrlMacRx3VideoSetting(void);
extern void ScalerHdmiFrlMacRx3ColorimetrySetting(void);
extern void ScalerHdmiFrlMacRx3ColorimetryExtSetting(void);
extern void ScalerHdmiFrlMacRx3ColorimetryAddExtSetting(void);

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
extern void ScalerHdmiFrlMacRx3RoundRobinDetect(bit bWait);

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
extern void ScalerHdmiFrlMacRx3RsvSpdHandler(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
extern void ScalerHdmiFrlMacRx3RsvVsifHandler(EnumHdmiRsvNumber enumRsvNumber);
#endif
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3HdmiVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber);
extern void ScalerHdmiFrlMacRx3HfVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3AllmProc(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3CcbpcProc(EnumHdmiRsvNumber enumRsvNumber);
#endif
#endif

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) || (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON))
extern void ScalerHdmiFrlMacRx3QuantizationSetting(void);
#endif

extern BYTE ScalerHdmiFrlMacRx3GetColorDepth(void);
extern bit ScalerHdmiFrlMacRx3ColorInfoChanged(void);
extern bit ScalerHdmiFrlMacRx3AviPixelRepInfoChanged(void);
extern void ScalerHdmiFrlMacRx3SetPorchColor(EnumColorSpace enumColorFormat);
extern void ScalerHdmiFrlMacRx3SetScdcUpdateFlag(DWORD ulAnd, BYTE ucOr);

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
extern void ScalerHdmiFrlMacRx3EmpPacketDetect(bit bWait);

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
extern WORD ScalerHdmiFrlMacRx3GetVtemInfo(EnumHdmi21VtemInfoContent enumContent);
#if(_HDMI21_VRR_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3SetVrrVfmaxFromTable(WORD usSourceBrr);
#endif
#endif
#endif

#if((_HDMI_FRL_MAC_RX3_LFSR_TEST_MODE == _ON) || (_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1))
extern void ScalerHdmiFrlMacRx3LtpCheck(void);
#endif

#if(_HDMI_FRL_MAC_RX3_LFSR_TEST_MODE == _ON)
extern void ScalerHdmiFrlMacRx3GapCheck(void);
extern void ScalerHdmiFrlMacRx3LfsrCheck(void);
#endif

extern bit ScalerHdmiFrlMacRx3DisplayFormatCheck(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRx3PnSwapConfig(EnumInputPort enumInputPort);

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
extern bit ScalerHdmiFrlMacRx3RebuildPhy(void);
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
extern void ScalerHdmiFrlMacRx3GetAdvancedHdr10Vsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata);
#endif

#if(_DM_FUNCTION == _ON)
extern void ScalerHdmiFrlMacRx3GetDmVsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, BYTE *pucDmMetaData);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3AllmProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3CcbpcProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
extern bit ScalerHdmiFrlMacRx3GetEmpSramData_EXINT0(BYTE ucReadAddress, BYTE *pucEmpData);
#endif

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
extern void ScalerHdmiFrlMacRx3ClearHighPriorityIrqFlag_EXINT0(void);
extern void ScalerHdmiFrlMacRx3ClearLowPriorityIrqFlag_EXINT0(void);
#endif

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
extern void ScalerHdmiFrlMacRx3RsvVsifHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
extern void ScalerHdmiFrlMacRx3RsvSpdHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

extern BYTE ScalerHdmiFrlMacRx3CheckFrlRate_EXINT0(void);
extern void ScalerHdmiFrlMacRx3SetScdcUpdateFlag_EXINT0(DWORD ulAnd, BYTE ucOr);

#if(_HDMI_SBTM_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3SbtmSetting_EXINT0(void);
#endif

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
extern void ScalerHdmiFrlMacRx3DMSetting_EXINT0(EnumInputPort enumMappingPort);
#endif

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx3SetAudioNfCode_EXINT0(void);
#endif
#endif // End of #if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_HDMI_FRL_MAC_RX3_H__
