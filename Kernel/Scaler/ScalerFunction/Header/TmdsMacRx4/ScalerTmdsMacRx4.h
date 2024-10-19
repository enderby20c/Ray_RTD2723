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
// ID Code      : ScalerTmdsMacRx4.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TMDS_MAC_RX4_H__
#define __SCALER_TMDS_MAC_RX4_H__


#if(_TMDS_MAC_RX4_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _TMDS_MAC_RX4_CED_DEBUG                         _OFF

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
//--------------------------------------------------
// Macro of AVI Pixel Repetiton
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION()         (g_ucTmdsMacRx4AviInfo)
#define SET_TMDS_MAC_RX4_AVI_PIXEL_REPETITION(x)        (g_ucTmdsMacRx4AviInfo = (x))
#define CLR_TMDS_MAC_RX4_AVI_PIXEL_REPETITION()         (g_ucTmdsMacRx4AviInfo = 0)
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
//--------------------------------------------------
// Macro of HDR10+ VSIF/EMP Detecting Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_ADVANCED_HDR10_DETECTING()     (g_stTmdsMacRx4CtrlInfo.b1AdvancedHdr10Detecting)
#define SET_TMDS_MAC_RX4_ADVANCED_HDR10_DETECTING()     (g_stTmdsMacRx4CtrlInfo.b1AdvancedHdr10Detecting = _TRUE)
#define CLR_TMDS_MAC_RX4_ADVANCED_HDR10_DETECTING()     (g_stTmdsMacRx4CtrlInfo.b1AdvancedHdr10Detecting = _FALSE)

//--------------------------------------------------
// Macro of HDR10+ VSIF Received Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED() (g_stTmdsMacRx4CtrlInfo.b1AdvancedHdr10VsifReceived)
#define SET_TMDS_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED() (g_stTmdsMacRx4CtrlInfo.b1AdvancedHdr10VsifReceived = _TRUE)
#define CLR_TMDS_MAC_RX4_ADVANCED_HDR10_VSIF_RECEIVED() (g_stTmdsMacRx4CtrlInfo.b1AdvancedHdr10VsifReceived = _FALSE)

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
//--------------------------------------------------
// Macro of HDR10+ (D-HDR EMP) Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED()     (g_stTmdsMacRx4CtrlInfo.b1DhdrEmpType40Received)
#define SET_TMDS_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED()     (g_stTmdsMacRx4CtrlInfo.b1DhdrEmpType40Received = _TRUE)
#define CLR_TMDS_MAC_RX4_DHDR_EMP_TYPE40_RECEIVED()     (g_stTmdsMacRx4CtrlInfo.b1DhdrEmpType40Received = _FALSE)
#endif
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Macro of DM VSIF/EMP Detecting Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_DM_INFO_DETECTING()            (g_stTmdsMacRx4CtrlInfo.b1DmInfoDetecting)
#define SET_TMDS_MAC_RX4_DM_INFO_DETECTING()            (g_stTmdsMacRx4CtrlInfo.b1DmInfoDetecting = _TRUE)
#define CLR_TMDS_MAC_RX4_DM_INFO_DETECTING()            (g_stTmdsMacRx4CtrlInfo.b1DmInfoDetecting = _FALSE)

//--------------------------------------------------
// Macro of DM VSIF Received Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_DM_VSIF_RECEIVED()             (g_stTmdsMacRx4CtrlInfo.b1DmVsifReceived)
#define SET_TMDS_MAC_RX4_DM_VSIF_RECEIVED()             (g_stTmdsMacRx4CtrlInfo.b1DmVsifReceived = _TRUE)
#define CLR_TMDS_MAC_RX4_DM_VSIF_RECEIVED()             (g_stTmdsMacRx4CtrlInfo.b1DmVsifReceived = _FALSE)

//--------------------------------------------------
// Macro of DM EMP Received Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_DM_EMP_RECEIVED()              (g_stTmdsMacRx4CtrlInfo.b1DmEmpReceived)
#define SET_TMDS_MAC_RX4_DM_EMP_RECEIVED()              (g_stTmdsMacRx4CtrlInfo.b1DmEmpReceived = _TRUE)
#define CLR_TMDS_MAC_RX4_DM_EMP_RECEIVED()              (g_stTmdsMacRx4CtrlInfo.b1DmEmpReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of HF VSIF Received Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_HF_VSIF_RECEIVED()             (g_stTmdsMacRx4CtrlInfo.b1HFVsifReceived)
#define SET_TMDS_MAC_RX4_HF_VSIF_RECEIVED()             (g_stTmdsMacRx4CtrlInfo.b1HFVsifReceived = _TRUE)
#define CLR_TMDS_MAC_RX4_HF_VSIF_RECEIVED()             (g_stTmdsMacRx4CtrlInfo.b1HFVsifReceived = _FALSE)

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HF VSIF Received Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX4_HDMI_VSIF_RECEIVED()           (g_stTmdsMacRx4CtrlInfo.b1HdmiVsifReceived)
#define SET_TMDS_MAC_RX4_HDMI_VSIF_RECEIVED()           (g_stTmdsMacRx4CtrlInfo.b1HdmiVsifReceived = _TRUE)
#define CLR_TMDS_MAC_RX4_HDMI_VSIF_RECEIVED()           (g_stTmdsMacRx4CtrlInfo.b1HdmiVsifReceived = _FALSE)
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
#if(_HDMI_SUPPORT == _ON)
#if(_TMDS_MAC_RX4_CED_DEBUG == _ON)
extern void ScalerTmdsMacRx4CEDCheck(void);
#endif
#endif
#if(_3DDI_FUNCTION == _ON)
extern bit ScalerTmdsMacRx4GetInterlace3ddiAvailable(void);
#endif
#if(_HDMI_MAC_RX4_SUPPORT == _ON)
extern void ScalerTmdsMacRx4HdmiColorimetrySetting(void);
extern void ScalerTmdsMacRx4HdmiColorimetryExtSetting(void);
extern void ScalerTmdsMacRx4HdmiColorimetryAddExtSetting(void);

#if((_HDMI_SPD_IF_RCV_BY_RR == _ON) || (_HDMI_VSIF_RCV_BY_RR == _ON))
extern void ScalerTmdsMacRx4RoundRobinDetect(bit bWait);

#if((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE) && (_DM_FUNCTION == _OFF))
#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
extern void ScalerTmdsMacRx4RsvSpdHandler(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
extern void ScalerTmdsMacRx4RsvVsifHandler(EnumHdmiRsvNumber enumRsvNumber);
#endif
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
extern void ScalerTmdsMacRx4HdmiVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber);
extern void ScalerTmdsMacRx4HfVsif3dVideoProc(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern void ScalerTmdsMacRx4AllmProc(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
extern void ScalerTmdsMacRx4CcbpcProc(EnumHdmiRsvNumber enumRsvNumber);
#endif
#endif

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) || (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON))
extern void ScalerTmdsMacRx4HdmiQuantizationSetting(void);
#endif
#endif

#if((_HDMI_MAC_RX4_SUPPORT == _ON) || (_3DDI_FUNCTION == _ON))
extern bit ScalerTmdsMacRx4HdmiWaitDeepColorPllLock(void);
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)

#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
extern void ScalerTmdsMacRx4EmpPacketDetect(bit bWait);
#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON))
#if(_HDMI21_VRR_SUPPORT == _ON)
extern void ScalerTmdsMacRx4SetVrrVfmaxFromTable(WORD usSourceBrr);
#endif
extern WORD ScalerTmdsMacRx4HdmiGetVtemInfo(EnumHdmi21VtemInfoContent enumContent);
#endif
#endif

extern bit ScalerTmdsMacRx4HdmiAviPixelRepInfoChanged(void);
#endif

#if(_HDMI_DPC_FIFO_ERR_CHECK_SUPPORT == _ON)
extern bit ScalerTmdsMacRx4HdmiCheckDeepColorFifo(void);
#endif

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
extern void ScalerTmdsMacRx4EmpSramSetting(bit bEnable);
#endif

extern void ScalerTmdsMacRx4RoundRobinIrqEnable(bit bEnable);

extern void ScalerTmdsMacRx4RsvIrqEnable(EnumHdmiRsvNumber enumRsvNumber, bit bEnable);

extern void ScalerTmdsMacRx4RsvInitial(void);

extern BYTE ScalerTmdsMacRx4CheckCDRStable_EXINT0(WORD usClkCount);

#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_OLD_MODE)
extern void ScalerTmdsMacRx4ClearHighPriorityIrqFlag_EXINT0(void);
extern void ScalerTmdsMacRx4ClearLowPriorityIrqFlag_EXINT0(void);
extern void ScalerTmdsMacRx4PsClearHighPriorityIrqFlag_EXINT0(void);
extern void ScalerTmdsMacRx4PsClearLowPriorityIrqFlag_EXINT0(void);
#endif
extern WORD ScalerTmdsMacRx4MeasureClk(BYTE ucMeasureClk);

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
extern void ScalerTmdsMacRx4GetAdvancedHdr10Vsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata);
#endif

#if(_DM_FUNCTION == _ON)
extern void ScalerTmdsMacRx4GetDmVsif_EXINT0(EnumHdmiRsvNumber enumRsvNumber, BYTE *pucDmMetaData);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern void ScalerTmdsMacRx4AllmProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
extern void ScalerTmdsMacRx4CcbpcProc_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

extern WORD ScalerTmdsMacRx4MeasureClk_EXINT0(BYTE ucMeasureClk);

#if(_HDMI_VSIF_RCV_BY_RR == _ON)
extern void ScalerTmdsMacRx4RsvVsifHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
extern void ScalerTmdsMacRx4RsvSpdHandler_EXINT0(EnumHdmiRsvNumber enumRsvNumber);
#endif

#if(_HW_HDMI_EMP_SRAM_SUPPORT == _ON)
extern bit ScalerTmdsMacRx4GetEmpSramData_EXINT0(BYTE ucReadAddress, BYTE *pucEmpData);
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
extern void ScalerTmdsMacRx4SbtmSetting_EXINT0(void);
#endif

#if((_DM_FUNCTION == _ON) && (_HW_CPU32_IS_BOOT_CPU == _TRUE))
extern void ScalerTmdsMacRx4DMSetting_EXINT0(EnumInputPort enumMappingPort);
#endif

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
#if(_HDMI20_MAC_RX4_SUPPORT == _ON)
extern void ScalerTmdsMacRx4ReadRequestProc_EXINT0(BYTE ucRROutCome);
#endif
#endif

#if((_HDMI_MAC_RX4_SUPPORT == _ON) || (_3DDI_FUNCTION == _ON))
extern bit ScalerTmdsMacRx4HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
extern void ScalerTmdsMacRx4DPLLOnProc(BYTE ucNcode);
#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit ScalerTmdsMacRx4CheckSeamlessCondition(void);
extern EnumSourceType ScalerTmdsMacRx4SeamlessReset(void);
#endif
#endif

#endif // End of #if(_TMDS_MAC_RX4_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_TMDS_MAC_RX4_H__
