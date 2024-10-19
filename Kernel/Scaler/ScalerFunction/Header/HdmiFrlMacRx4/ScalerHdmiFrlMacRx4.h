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
// ID Code      : ScalerHdmiFrlMacRx4.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_HDMI_FRL_MAC_RX4_H__
#define __SCALER_HDMI_FRL_MAC_RX4_H__


#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of SCDC FRL_Rate Event
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT()                  (g_stHdmiFrlMacRx4CtrlInfo.b1FrlRateEvent)
#define SET_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT()                  (g_stHdmiFrlMacRx4CtrlInfo.b1FrlRateEvent = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_FRL_RATE_EVENT()                  (g_stHdmiFrlMacRx4CtrlInfo.b1FrlRateEvent = _FALSE)

//--------------------------------------------------
// Macro of SCDC FRL_Start
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_FRL_START_EVENT()                 (g_stHdmiFrlMacRx4CtrlInfo.b1FrlStartEvent)
#define SET_HDMI_FRL_MAC_RX4_FRL_START_EVENT()                 (g_stHdmiFrlMacRx4CtrlInfo.b1FrlStartEvent = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_FRL_START_EVENT()                 (g_stHdmiFrlMacRx4CtrlInfo.b1FrlStartEvent = _FALSE)

//--------------------------------------------------
// Macro of FRL Lane Lock
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_LANE0_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane0Lock)
#define SET_HDMI_FRL_MAC_RX4_LANE0_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane0Lock = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_LANE0_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane0Lock = _FALSE)

#define GET_HDMI_FRL_MAC_RX4_LANE1_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane1Lock)
#define SET_HDMI_FRL_MAC_RX4_LANE1_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane1Lock = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_LANE1_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane1Lock = _FALSE)

#define GET_HDMI_FRL_MAC_RX4_LANE2_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane2Lock)
#define SET_HDMI_FRL_MAC_RX4_LANE2_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane2Lock = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_LANE2_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane2Lock = _FALSE)

#define GET_HDMI_FRL_MAC_RX4_LANE3_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane3Lock)
#define SET_HDMI_FRL_MAC_RX4_LANE3_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane3Lock = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_LANE3_LOCK()                      (g_stHdmiFrlMacRx4CtrlInfo.b1Lane3Lock = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_PACKET_DETECTING()                (g_stHdmiFrlMacRx4CtrlInfo.b1PacketDetecting)
#define SET_HDMI_FRL_MAC_RX4_PACKET_DETECTING()                (g_stHdmiFrlMacRx4CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_PACKET_DETECTING()                (g_stHdmiFrlMacRx4CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of HDMI2.1 Rebuild PHY
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT()               (g_stHdmiFrlMacRx4CtrlInfo.b1RebuildPhyEvent)
#define SET_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT()               (g_stHdmiFrlMacRx4CtrlInfo.b1RebuildPhyEvent = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_REBUILD_PHY_EVENT()               (g_stHdmiFrlMacRx4CtrlInfo.b1RebuildPhyEvent = _FALSE)

//--------------------------------------------------
// Macro of HDMI2.1 Rebuild PHY
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_DPF_PIXEL_MODE_MISMATCH()         (g_stHdmiFrlMacRx4CtrlInfo.b1DpfPixelModeMismatch)
#define SET_HDMI_FRL_MAC_RX4_DPF_PIXEL_MODE_MISMATCH()         (g_stHdmiFrlMacRx4CtrlInfo.b1DpfPixelModeMismatch = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_DPF_PIXEL_MODE_MISMATCH()         (g_stHdmiFrlMacRx4CtrlInfo.b1DpfPixelModeMismatch = _FALSE)

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
//--------------------------------------------------
// Macro of HDR10+ VSIF/EMP Detecting Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_DETECTING()        (g_stHdmiFrlMacRx4CtrlInfo.b1FrlAdvancedHdr10Detecting)
#define SET_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_DETECTING()        (g_stHdmiFrlMacRx4CtrlInfo.b1FrlAdvancedHdr10Detecting = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_DETECTING()        (g_stHdmiFrlMacRx4CtrlInfo.b1FrlAdvancedHdr10Detecting = _FALSE)

//--------------------------------------------------
// Macro of HDR10+ VSIF Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED()    (g_stHdmiFrlMacRx4CtrlInfo.b1FrlAdvancedHdr10VsifReceived)
#define SET_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED()    (g_stHdmiFrlMacRx4CtrlInfo.b1FrlAdvancedHdr10VsifReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED()    (g_stHdmiFrlMacRx4CtrlInfo.b1FrlAdvancedHdr10VsifReceived = _FALSE)

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
//--------------------------------------------------
// Macro of HDR10+ (D-HDR EMP) Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED()        (g_stHdmiFrlMacRx4CtrlInfo.b1FrlDhdrEmpType40Received)
#define SET_HDMI_FRL_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED()        (g_stHdmiFrlMacRx4CtrlInfo.b1FrlDhdrEmpType40Received = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED()        (g_stHdmiFrlMacRx4CtrlInfo.b1FrlDhdrEmpType40Received = _FALSE)
#endif
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Macro of DM VSIF/EMP Detecting Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_DM_INFO_DETECTING()               (g_stHdmiFrlMacRx4CtrlInfo.b1DmInfoDetecting)
#define SET_HDMI_FRL_MAC_RX4_DM_INFO_DETECTING()               (g_stHdmiFrlMacRx4CtrlInfo.b1DmInfoDetecting = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_DM_INFO_DETECTING()               (g_stHdmiFrlMacRx4CtrlInfo.b1DmInfoDetecting = _FALSE)

//--------------------------------------------------
// Macro of DM VSIF Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_DM_VSIF_RECEIVED()                (g_stHdmiFrlMacRx4CtrlInfo.b1DmVsifReceived)
#define SET_HDMI_FRL_MAC_RX4_DM_VSIF_RECEIVED()                (g_stHdmiFrlMacRx4CtrlInfo.b1DmVsifReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_DM_VSIF_RECEIVED()                (g_stHdmiFrlMacRx4CtrlInfo.b1DmVsifReceived = _FALSE)

//--------------------------------------------------
// Macro of DM EMP Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_DM_EMP_RECEIVED()                 (g_stHdmiFrlMacRx4CtrlInfo.b1DmEmpReceived)
#define SET_HDMI_FRL_MAC_RX4_DM_EMP_RECEIVED()                 (g_stHdmiFrlMacRx4CtrlInfo.b1DmEmpReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_DM_EMP_RECEIVED()                 (g_stHdmiFrlMacRx4CtrlInfo.b1DmEmpReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of HF VSIF Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_HF_VSIF_RECEIVED()                (g_stHdmiFrlMacRx4CtrlInfo.b1HFVsifReceived)
#define SET_HDMI_FRL_MAC_RX4_HF_VSIF_RECEIVED()                (g_stHdmiFrlMacRx4CtrlInfo.b1HFVsifReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_HF_VSIF_RECEIVED()                (g_stHdmiFrlMacRx4CtrlInfo.b1HFVsifReceived = _FALSE)

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HF VSIF Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_HDMI_VSIF_RECEIVED()              (g_stHdmiFrlMacRx4CtrlInfo.b1HdmiVsifReceived)
#define SET_HDMI_FRL_MAC_RX4_HDMI_VSIF_RECEIVED()              (g_stHdmiFrlMacRx4CtrlInfo.b1HdmiVsifReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_HDMI_VSIF_RECEIVED()              (g_stHdmiFrlMacRx4CtrlInfo.b1HdmiVsifReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED()         (g_stHdmiFrlMacRx4CtrlInfo.b1AVIInfoFrameReceived)
#define SET_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED()         (g_stHdmiFrlMacRx4CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_AVI_INFO_FRAME_RECEIVED()         (g_stHdmiFrlMacRx4CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_GCP_RECEIVED()                    (g_stHdmiFrlMacRx4CtrlInfo.b1GCPReceived)
#define SET_HDMI_FRL_MAC_RX4_GCP_RECEIVED()                    (g_stHdmiFrlMacRx4CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_GCP_RECEIVED()                    (g_stHdmiFrlMacRx4CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define SET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION(x)           (g_ucHdmiFrlMacRx4AviInfo = (x))
#define GET_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION()            (g_ucHdmiFrlMacRx4AviInfo)
#define CLR_HDMI_FRL_MAC_RX4_AVI_PIXEL_REPETITION()            (g_ucHdmiFrlMacRx4AviInfo = 0)

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_HDMI_FRL_MAC_RX4_SIGNAL_DETECTING()                (g_stHdmiFrlMacRx4CtrlInfo.b1SignalDetecting)
#define SET_HDMI_FRL_MAC_RX4_SIGNAL_DETECTING()                (g_stHdmiFrlMacRx4CtrlInfo.b1SignalDetecting = _TRUE)
#define CLR_HDMI_FRL_MAC_RX4_SIGNAL_DETECTING()                (g_stHdmiFrlMacRx4CtrlInfo.b1SignalDetecting = _FALSE)
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
extern void ScalerHdmiFrlMacRx4EmpSramSetting(bit bEnable);
#endif
extern void ScalerHdmiFrlMacRx4RsvIrqEnable(EnumHdmiRsvNumber enumRsvNumber, bit bEnable);
extern void ScalerHdmiFrlMacRx4RsvInitial(void);
extern void ScalerHdmiFrlMacRx4Initial(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRx4InterruptInitial(void);
#if(_3DDI_FUNCTION == _ON)
extern bit ScalerHdmiFrlMacRx4GetInterlace3ddiAvaible(void);
#endif
extern bit ScalerHdmiFrlMacRx4CedCheck(void);
extern bit ScalerHdmiFrlMacRx4RsedCheck(void);
extern bit ScalerHdmiFrlMacRx4FrlVideoCheck(void);
#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern EnumSourceType ScalerHdmiFrlMacRx4SeamlessReset(void);
extern bit ScalerHdmiFrlMacRx4CheckSeamlessCondition(void);
#endif
extern bit ScalerHdmiFrlMacRx4MeasureCheck(void);
extern bit ScalerHdmiFrlMacRx4DisplayFormatSetting(void);
extern bit ScalerHdmiFrlMacRx4DPFHsyncHstartAdjust(WORD *pusDPFHsync, WORD *pusDPFHstart, WORD usDPFHblank);
extern bit ScalerHdmiFrlMacRx4StreamClkRegenerate(void);
extern void ScalerHdmiFrlMacRx4DPLLOnProc(WORD usVCOFreq, WORD usPLLinClkFreq);
extern void ScalerHdmiFrlMacRx4SetPGainClampValue (BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern bit ScalerHdmiFrlMacRx4DpfFifoCheck(bit bWait);
extern bit ScalerHdmiFrlMacRx4CheckCdrStable(WORD usClkCount);
extern void ScalerHdmiFrlMacRx4ResetAllPacketReceiveStatus(void);
extern void ScalerHdmiFrlMacRx4PacketDetect(bit bWait);
extern void ScalerHdmiFrlMacRx4WatchDog(BYTE ucWDType, bit bEnable);
extern void ScalerHdmiFrlMacRx4VideoSetting(void);
extern void ScalerHdmiFrlMacRx4ColorimetrySetting(void);
extern void ScalerHdmiFrlMacRx4ColorimetryExtSetting(void);
extern void ScalerHdmiFrlMacRx4ColorimetryAddExtSetting(void);

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
extern void ScalerHdmiFrlMacRx4RoundRobinDetect(bit bWait);

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
extern void ScalerHdmiFrlMacRx4RsvSpdHandler(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
extern void ScalerHdmiFrlMacRx4RsvVsifHandler(EnumHdmiRsvNumber enumRsvNumber);
#endif
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4HdmiVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber);
extern void ScalerHdmiFrlMacRx4HfVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4AllmProc(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4CcbpcProc(EnumHdmiRsvNumber enumRsvNumber);
#endif
#endif

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) || (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON))
extern void ScalerHdmiFrlMacRx4QuantizationSetting(void);
#endif

extern BYTE ScalerHdmiFrlMacRx4GetColorDepth(void);
extern bit ScalerHdmiFrlMacRx4ColorInfoChanged(void);
extern bit ScalerHdmiFrlMacRx4AviPixelRepInfoChanged(void);
extern void ScalerHdmiFrlMacRx4SetPorchColor(EnumColorSpace enumColorFormat);
extern void ScalerHdmiFrlMacRx4SetScdcUpdateFlag(DWORD ulAnd, BYTE ucOr);

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
extern void ScalerHdmiFrlMacRx4EmpPacketDetect(bit bWait);

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
extern WORD ScalerHdmiFrlMacRx4GetVtemInfo(EnumHdmi21VtemInfoContent enumContent);
#if(_HDMI21_VRR_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4SetVrrVfmaxFromTable(WORD usSourceBrr);
#endif
#endif
#endif

#if((_HDMI_FRL_MAC_RX4_LFSR_TEST_MODE == _ON) || (_RDC_TEST_TYPE == _HDMI_RDC_TEST_TYPE_2_1))
extern void ScalerHdmiFrlMacRx4LtpCheck(void);
#endif

#if(_HDMI_FRL_MAC_RX4_LFSR_TEST_MODE == _ON)
extern void ScalerHdmiFrlMacRx4GapCheck(void);
extern void ScalerHdmiFrlMacRx4LfsrCheck(void);
#endif

extern bit ScalerHdmiFrlMacRx4DisplayFormatCheck(EnumInputPort enumInputPort);
extern void ScalerHdmiFrlMacRx4PnSwapConfig(EnumInputPort enumInputPort);

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
extern bit ScalerHdmiFrlMacRx4RebuildPhy(void);
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
extern void ScalerHdmiFrlMacRx4GetAdvancedHdr10Vsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata);
#endif

#if(_DM_FUNCTION == _ON)
extern void ScalerHdmiFrlMacRx4GetDmVsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, BYTE *pucDmMetaData);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4AllmProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4CcbpcProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
extern bit ScalerHdmiFrlMacRx4GetEmpSramData_EXINT0(BYTE ucReadAddress, BYTE *pucEmpData);
#endif

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
extern void ScalerHdmiFrlMacRx4ClearHighPriorityIrqFlag_EXINT0(void);
extern void ScalerHdmiFrlMacRx4ClearLowPriorityIrqFlag_EXINT0(void);
#endif

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
extern void ScalerHdmiFrlMacRx4RsvVsifHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
extern void ScalerHdmiFrlMacRx4RsvSpdHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

extern BYTE ScalerHdmiFrlMacRx4CheckFrlRate_EXINT0(void);
extern void ScalerHdmiFrlMacRx4SetScdcUpdateFlag_EXINT0(DWORD ulAnd, BYTE ucOr);

#if(_HDMI_SBTM_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4SbtmSetting_EXINT0(void);
#endif

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
extern void ScalerHdmiFrlMacRx4DMSetting_EXINT0(EnumInputPort enumMappingPort);
#endif

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
extern void ScalerHdmiFrlMacRx4SetAudioNfCode_EXINT0(void);
#endif
#endif // End of #if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_HDMI_FRL_MAC_RX4_H__
