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
// ID Code      : ScalerTmdsMacRx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_TMDS_MAC_RX3_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#define GET_TMDS_MAC_RX3_PS_WAKEUP()                    ((bit)(g_stTmdsMacRxDpHdmiCompatibleHdmiPsWakeup.b1HdmiRx3PSWakeUp))
#define SET_TMDS_MAC_RX3_PS_WAKEUP()                    (g_stTmdsMacRxDpHdmiCompatibleHdmiPsWakeup.b1HdmiRx3PSWakeUp = 1)
#define CLR_TMDS_MAC_RX3_PS_WAKEUP()                    (g_stTmdsMacRxDpHdmiCompatibleHdmiPsWakeup.b1HdmiRx3PSWakeUp = 0)
#endif

//--------------------------------------------------
// Macro of PHY Set Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_PHY_SET()                      (g_stTmdsMacRx3CtrlInfo.b1TMDSPhySet)
#define SET_TMDS_MAC_RX3_PHY_SET()                      (g_stTmdsMacRx3CtrlInfo.b1TMDSPhySet = _TRUE)
#define CLR_TMDS_MAC_RX3_PHY_SET()                      (g_stTmdsMacRx3CtrlInfo.b1TMDSPhySet = _FALSE)

//--------------------------------------------------
// Macro of Retry to Set Phy
//--------------------------------------------------
#if(_TMDS_RETRY_SET_PHY_SUPPORT == _ON)
#define GET_TMDS_MAC_RX3_RETRY_SET_PHY()                (g_stTmdsMacRx3CtrlInfo.b1TmdsRetrySetPhy)
#define SET_TMDS_MAC_RX3_RETRY_SET_PHY()                (g_stTmdsMacRx3CtrlInfo.b1TmdsRetrySetPhy = _TRUE)
#define CLR_TMDS_MAC_RX3_RETRY_SET_PHY()                (g_stTmdsMacRx3CtrlInfo.b1TmdsRetrySetPhy = _FALSE)
#endif

//--------------------------------------------------
// Macro of HPD Proc Happened Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HPD_RESET_TO_SEARCH_EVENT()    (g_stTmdsMacRx3CtrlInfo.b1TMDSHpdResetSearchEvent)
#define SET_TMDS_MAC_RX3_HPD_RESET_TO_SEARCH_EVENT()    (g_stTmdsMacRx3CtrlInfo.b1TMDSHpdResetSearchEvent = _TRUE)
#define CLR_TMDS_MAC_RX3_HPD_RESET_TO_SEARCH_EVENT()    (g_stTmdsMacRx3CtrlInfo.b1TMDSHpdResetSearchEvent = _FALSE)

//--------------------------------------------------
// Macro of TMDS Video Detecting Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_RGBHV_DETECTING()              (g_stTmdsMacRx3CtrlInfo.b1RGBHVDetecting)
#define SET_TMDS_MAC_RX3_RGBHV_DETECTING()              (g_stTmdsMacRx3CtrlInfo.b1RGBHVDetecting = _TRUE)
#define CLR_TMDS_MAC_RX3_RGBHV_DETECTING()              (g_stTmdsMacRx3CtrlInfo.b1RGBHVDetecting = _FALSE)

//--------------------------------------------------
// Macro of Packet Detecting Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HDMI_PACKET_DETECTING()        (g_stTmdsMacRx3CtrlInfo.b1PacketDetecting)
#define SET_TMDS_MAC_RX3_HDMI_PACKET_DETECTING()        (g_stTmdsMacRx3CtrlInfo.b1PacketDetecting = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI_PACKET_DETECTING()        (g_stTmdsMacRx3CtrlInfo.b1PacketDetecting = _FALSE)

//--------------------------------------------------
// Macro of AVI Info Frame Received Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HDMI_AVI_INFO_FRAME_RECEIVED() (g_stTmdsMacRx3CtrlInfo.b1AVIInfoFrameReceived)
#define SET_TMDS_MAC_RX3_HDMI_AVI_INFO_FRAME_RECEIVED() (g_stTmdsMacRx3CtrlInfo.b1AVIInfoFrameReceived = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI_AVI_INFO_FRAME_RECEIVED() (g_stTmdsMacRx3CtrlInfo.b1AVIInfoFrameReceived = _FALSE)

//--------------------------------------------------
// Macro of GCP Received Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HDMI_GCP_RECEIVED()            (g_stTmdsMacRx3CtrlInfo.b1GCPReceived)
#define SET_TMDS_MAC_RX3_HDMI_GCP_RECEIVED()            (g_stTmdsMacRx3CtrlInfo.b1GCPReceived = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI_GCP_RECEIVED()            (g_stTmdsMacRx3CtrlInfo.b1GCPReceived = _FALSE)

//--------------------------------------------------
// Macro of Input Off Line Measure Get Pixel Clk (Unit in 0.1MHz)
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_OFFLINE_MEASURE_CLK()          (g_usTmdsMacRx3OffLineMeasureClk)
#define SET_TMDS_MAC_RX3_OFFLINE_MEASURE_CLK(x)         (g_usTmdsMacRx3OffLineMeasureClk = (x))
#define CLR_TMDS_MAC_RX3_OFFLINE_MEASURE_CLK()          (g_usTmdsMacRx3OffLineMeasureClk = 0)

//--------------------------------------------------
// Macro of Backup HDCP type
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_BACKUP_HDCP_TYPE()             (g_ucTmdsMacRx3HdcpType)
#define SET_TMDS_MAC_RX3_BACKUP_HDCP_TYPE(x)            (g_ucTmdsMacRx3HdcpType = (x))

//--------------------------------------------------
// Macro of HDR Received Flag
//--------------------------------------------------
#if((_HDMI_HDR10_SUPPORT == _ON) || (_DM_FUNCTION == _ON))
#define GET_TMDS_MAC_RX3_HDMI_HDR10_INFO_FRAME_RECEIVED()\
                                                        (g_stTmdsMacRx3CtrlInfo.b1HDRInfoFrameReceived)
#define SET_TMDS_MAC_RX3_HDMI_HDR10_INFO_FRAME_RECEIVED()\
                                                        (g_stTmdsMacRx3CtrlInfo.b1HDRInfoFrameReceived = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI_HDR10_INFO_FRAME_RECEIVED()\
                                                        (g_stTmdsMacRx3CtrlInfo.b1HDRInfoFrameReceived = _FALSE)
#endif

//--------------------------------------------------
// Macro of EMP Related
//--------------------------------------------------
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))

#define GET_TMDS_MAC_RX3_EMP_DETECTING()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1EmpDetecting)
#define SET_TMDS_MAC_RX3_EMP_DETECTING()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1EmpDetecting = _TRUE)
#define CLR_TMDS_MAC_RX3_EMP_DETECTING()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1EmpDetecting = _FALSE)

#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
//--------------------------------------------------
// Define for VRR Packet Type
//--------------------------------------------------
#if(_HDMI_FORCE_VRR_SUPPORT == _ON)
#define GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED()         (_TRUE)
#else
#define GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED()         (g_stTmdsMacRx3Hdmi21EmpInfo.b1VtemReceived)
#endif

#define SET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED()         (g_stTmdsMacRx3Hdmi21EmpInfo.b1VtemReceived = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVED()         (g_stTmdsMacRx3Hdmi21EmpInfo.b1VtemReceived = _FALSE)

#define GET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVE_CHG()      (g_stTmdsMacRx3Hdmi21EmpInfo.b1VtemReceiveChanged)
#define SET_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVE_CHG()      (g_stTmdsMacRx3Hdmi21EmpInfo.b1VtemReceiveChanged = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI21_VTEM_RECEIVE_CHG()      (g_stTmdsMacRx3Hdmi21EmpInfo.b1VtemReceiveChanged = _FALSE)

#if(_HDMI21_VRR_SUPPORT == _ON)
#define GET_TMDS_MAC_RX3_HDMI21_VRR_RECEIVE_CHG()       (g_stTmdsMacRx3Hdmi21EmpInfo.b1VrrReceiveChanged)
#define SET_TMDS_MAC_RX3_HDMI21_VRR_RECEIVE_CHG()       (g_stTmdsMacRx3Hdmi21EmpInfo.b1VrrReceiveChanged = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI21_VRR_RECEIVE_CHG()       (g_stTmdsMacRx3Hdmi21EmpInfo.b1VrrReceiveChanged = _FALSE)

#define GET_TMDS_MAC_RX3_HDMI21_QMS_RECEIVE_CHG()       (g_stTmdsMacRx3Hdmi21EmpInfo.b1QmsReceiveChanged)
#define SET_TMDS_MAC_RX3_HDMI21_QMS_RECEIVE_CHG()       (g_stTmdsMacRx3Hdmi21EmpInfo.b1QmsReceiveChanged = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI21_QMS_RECEIVE_CHG()       (g_stTmdsMacRx3Hdmi21EmpInfo.b1QmsReceiveChanged = _FALSE)

#define GET_TMDS_MAC_RX3_HDMI21_VRR_EN()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1VrrEnable)
#define SET_TMDS_MAC_RX3_HDMI21_VRR_EN()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1VrrEnable = _ENABLE)
#define CLR_TMDS_MAC_RX3_HDMI21_VRR_EN()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1VrrEnable = _DISABLE)

#define GET_TMDS_MAC_RX3_HDMI21_QMS_EN()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1QmsEnable)
#define SET_TMDS_MAC_RX3_HDMI21_QMS_EN()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1QmsEnable = _ENABLE)
#define CLR_TMDS_MAC_RX3_HDMI21_QMS_EN()                (g_stTmdsMacRx3Hdmi21EmpInfo.b1QmsEnable = _DISABLE)
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
#define GET_TMDS_MAC_RX3_HDMI21_FVA_FACTOR()            (g_stTmdsMacRx3Hdmi21EmpInfo.b5FvaFactor)
#define SET_TMDS_MAC_RX3_HDMI21_FVA_FACTOR(x)           (g_stTmdsMacRx3Hdmi21EmpInfo.b5FvaFactor = (x))
#endif

#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
#define GET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED()        (g_stTmdsMacRx3Hdmi21EmpInfo.b1CvtemReceived)
#define SET_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED()        (g_stTmdsMacRx3Hdmi21EmpInfo.b1CvtemReceived = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI21_CVTEM_RECEIVED()        (g_stTmdsMacRx3Hdmi21EmpInfo.b1CvtemReceived = _FALSE)
#endif

#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Macro of ALLM Enable
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED()          (g_stTmdsMacRx3CtrlInfo.b1Hdmi21AllmEnable)
#define SET_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED()          (g_stTmdsMacRx3CtrlInfo.b1Hdmi21AllmEnable = _ENABLE)
#define CLR_TMDS_MAC_RX3_HDMI21_ALLM_ENABLED()          (g_stTmdsMacRx3CtrlInfo.b1Hdmi21AllmEnable = _DISABLE)
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
//--------------------------------------------------
// Macro of 3D Video format
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID()          (g_stTmdsMacRx3CtrlInfo.b13dVideoValid)
#define SET_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID()          (g_stTmdsMacRx3CtrlInfo.b13dVideoValid = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI_3D_VIDEO_VALID()          (g_stTmdsMacRx3CtrlInfo.b13dVideoValid = _FALSE)
#endif

//--------------------------------------------------
// Macro of the Fiset Time of Z0 Asserted
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_Z0_ASSERTED()                  (g_stTmdsMacRx3CtrlInfo.b1Z0Asserted)
#define SET_TMDS_MAC_RX3_Z0_ASSERTED()                  (g_stTmdsMacRx3CtrlInfo.b1Z0Asserted = _TRUE)
#define CLR_TMDS_MAC_RX3_Z0_ASSERTED()                  (g_stTmdsMacRx3CtrlInfo.b1Z0Asserted = _FALSE)

//--------------------------------------------------
// Macro of the Bed error
//--------------------------------------------------
#if(_HDMI_UNSTABLE_BED_CHECK_SUPPORT == _ON)
#define GET_TMDS_MAC_RX3_BED_ERROR()                    (g_stTmdsMacRx3CtrlInfo.b1BedError)
#define SET_TMDS_MAC_RX3_BED_ERROR()                    (g_stTmdsMacRx3CtrlInfo.b1BedError = _TRUE)
#define CLR_TMDS_MAC_RX3_BED_ERROR()                    (g_stTmdsMacRx3CtrlInfo.b1BedError = _FALSE)
#endif

//--------------------------------------------------
// Macro of HPD Evnet Trigger
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT()            (g_stTmdsMacRx3CtrlInfo.enumHpdEvent)
#define SET_TMDS_MAC_RX3_HPD_TRIGGER_EVENT(x)           (g_stTmdsMacRx3CtrlInfo.enumHpdEvent = (x))
#define CLR_TMDS_MAC_RX3_HPD_TRIGGER_EVENT()            (g_stTmdsMacRx3CtrlInfo.enumHpdEvent = _TMDS_MAC_RX_HPD_NONE)

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#define GET_TMDS_MAC_RX3_TOGGLE_Z0()                    (g_bSyncTmdsRx3Z0Toggle)
#define SET_TMDS_MAC_RX3_TOGGLE_Z0()                    (g_bSyncTmdsRx3Z0Toggle = _TRUE)
#define CLR_TMDS_MAC_RX3_TOGGLE_Z0()                    (g_bSyncTmdsRx3Z0Toggle = _FALSE)

#define GET_TMDS_MAC_RX3_TOGGLE_Z0_EVENT()              (g_bSyncTmdsRx3GlobalZ0Toggle)
#define SET_TMDS_MAC_RX3_TOGGLE_Z0_EVENT()              (g_bSyncTmdsRx3GlobalZ0Toggle = _TRUE)
#define CLR_TMDS_MAC_RX3_TOGGLE_Z0_EVENT()              (g_bSyncTmdsRx3GlobalZ0Toggle = _FALSE)
#endif

#define GET_TMDS_MAC_RX3_FORCE_BCKGRD_PATH()            (g_enumTmdsMacRx3IrqForceBackgrd & _DDOMAIN_RGN_ALL)
#define SET_TMDS_MAC_RX3_FORCE_BCKGRD_PATH(x)           (g_enumTmdsMacRx3IrqForceBackgrd |= (x))
#define CLR_TMDS_MAC_RX3_FORCE_BCKGRD_PATH(x)           (g_enumTmdsMacRx3IrqForceBackgrd &= (EnumDDomainRegion)~(x))

#if(_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON)
#define GET_HDMI_MAC_RX3_INTERFACE_SWITCHING()          (g_stTmdsMacRx3CtrlInfo.b1HdmiInterfaceSwitching)
#define SET_HDMI_MAC_RX3_INTERFACE_SWITCHING()          (g_stTmdsMacRx3CtrlInfo.b1HdmiInterfaceSwitching = _TRUE)
#define CLR_HDMI_MAC_RX3_INTERFACE_SWITCHING()          (g_stTmdsMacRx3CtrlInfo.b1HdmiInterfaceSwitching = _FALSE)
#endif

#if(_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON)
#define GET_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING()     (g_stTmdsMacRx3CtrlInfo.b1HdmiHpdToggling)
#define SET_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING()     (g_stTmdsMacRx3CtrlInfo.b1HdmiHpdToggling = _TRUE)
#define CLR_TMDS_MAC_RX3_ACTIVE_TYPE_HPD_TOGGLING()     (g_stTmdsMacRx3CtrlInfo.b1HdmiHpdToggling = _FALSE)
#endif

#if((_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON) || (_TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT == _ON))
#define GET_TMDS_MAC_RX3_HPD_TIMER_EVENT_TOGGLING_CABLE_ON()\
                                                        (g_stTmdsMacRx3CtrlInfo.b1HdmiHpdTogglingCableOn)
#define SET_TMDS_MAC_RX3_HPD_TIMER_EVENT_TOGGLING_CABLE_ON()\
                                                        (g_stTmdsMacRx3CtrlInfo.b1HdmiHpdTogglingCableOn = _TRUE)
#define CLR_TMDS_MAC_RX3_HPD_TIMER_EVENT_TOGGLING_CABLE_ON()\
                                                        (g_stTmdsMacRx3CtrlInfo.b1HdmiHpdTogglingCableOn = _FALSE)
#endif

#if(_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON)
#define GET_HDMI_MAC_RX3_AC_ON_HPD_TOGGLE_EVENT()       (g_stTmdsMacRx3CtrlInfo.b1HdmiAcOnHpdToggleEvent)
#define SET_HDMI_MAC_RX3_AC_ON_HPD_TOGGLE_EVENT()       (g_stTmdsMacRx3CtrlInfo.b1HdmiAcOnHpdToggleEvent = _TRUE)
#define CLR_HDMI_MAC_RX3_AC_ON_HPD_TOGGLE_EVENT()       (g_stTmdsMacRx3CtrlInfo.b1HdmiAcOnHpdToggleEvent = _FALSE)
#endif

//--------------------------------------------------
// Macro of DDCCI PS to Normal HPD Toggle
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_PS_WAKEUP_HPD_TOGGLE()         (g_stSyncHdmiPsWakeupHPD.b1Rx3PsWakeupHpd)
#define SET_TMDS_MAC_RX3_PS_WAKEUP_HPD_TOGGLE()         (g_stSyncHdmiPsWakeupHPD.b1Rx3PsWakeupHpd = _TRUE)
#define CLR_TMDS_MAC_RX3_PS_WAKEUP_HPD_TOGGLE()         (g_stSyncHdmiPsWakeupHPD.b1Rx3PsWakeupHpd = _FALSE)

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI 2.0 Format Reset Check Wait
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HDMI20_FORMAT_RESET_WAITING()  (g_stTmdsMacRx3CtrlInfo.b1HDMI2FormatResetWaiting)
#define SET_TMDS_MAC_RX3_HDMI20_FORMAT_RESET_WAITING()  (g_stTmdsMacRx3CtrlInfo.b1HDMI2FormatResetWaiting = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI20_FORMAT_RESET_WAITING()  (g_stTmdsMacRx3CtrlInfo.b1HDMI2FormatResetWaiting = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 Read Request Enable Flag
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HDMI20_RR_ENABLE()             (g_stTmdsMacRx3CtrlInfo.b1HDMI2RREnable)
#define SET_TMDS_MAC_RX3_HDMI20_RR_ENABLE()             (g_stTmdsMacRx3CtrlInfo.b1HDMI2RREnable = _TRUE)
#define CLR_TMDS_MAC_RX3_HDMI20_RR_ENABLE()             (g_stTmdsMacRx3CtrlInfo.b1HDMI2RREnable = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 High Speed Mode
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_HIGH_SPEED_MODE()              (g_stTmdsMacRx3CtrlInfo.b1HDMI2HighSpeedMode)
#define SET_TMDS_MAC_RX3_HIGH_SPEED_MODE()              (g_stTmdsMacRx3CtrlInfo.b1HDMI2HighSpeedMode = _TRUE)
#define CLR_TMDS_MAC_RX3_HIGH_SPEED_MODE()              (g_stTmdsMacRx3CtrlInfo.b1HDMI2HighSpeedMode = _FALSE)
#endif

#if(((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON)) && (_HDMI_SPD_IF_RCV_BY_RR == _ON))
//--------------------------------------------------
// Macro of HDMI FREESYNC VALUABLE
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_FS_VALUABLE()                  (g_stTmdsMacRx3SpdFsInfo.b1FreesyncValuable)
#define SET_TMDS_MAC_RX3_FS_VALUABLE()                  (g_stTmdsMacRx3SpdFsInfo.b1FreesyncValuable = _TRUE)
#define CLR_TMDS_MAC_RX3_FS_VALUABLE()                  (g_stTmdsMacRx3SpdFsInfo.b1FreesyncValuable = _FALSE)
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI FREESYNC VALUABLE
//--------------------------------------------------
#define GET_TMDS_MAC_RX3_SBTM_RECEIVE()                 (g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmInfoReceive)
#define SET_TMDS_MAC_RX3_SBTM_RECEIVE()                 (g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmInfoReceive = _TRUE)
#define CLR_TMDS_MAC_RX3_SBTM_RECEIVE()                 (g_stTmdsMacRx3HdmiSbtmInfo.b1SbtmInfoReceive = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructTMDSCtrlInfo g_stTmdsMacRx3CtrlInfo;
#if(_HDMI_SPD_IF_RCV_BY_RR == _ON)
extern volatile StructHdmiSpdInfo g_stTmdsMacRx3SpdInfo;
#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
extern volatile StructHdmiSpdFsInfo g_stTmdsMacRx3SpdFsInfo;
#endif
#endif
extern volatile WORD g_usTmdsMacRx3ClkCount;
extern WORD g_usTmdsMacRx3OffLineMeasureClk;

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
extern BYTE g_ucTmdsMacRx3AviInfo;
#if((_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
extern volatile StructHdmi21EmpInfo g_stTmdsMacRx3Hdmi21EmpInfo;
#if(_HDMI21_VRR_SUPPORT == _ON)
extern StructHdmi21EdidVrrCap g_stTmdsMacRx3Hdmi21EdidVrrCap;
#endif
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
extern StructHdmiSbtmInfo g_stTmdsMacRx3HdmiSbtmInfo;
#endif
#endif

extern EnumDDomainRegion g_enumTmdsMacRx3IrqForceBackgrd;
extern BYTE g_ucTmdsMacRx3Z0Status;
extern BYTE g_ucTmdsMacRx3HdcpType;

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
extern BYTE g_pucTmdsMacRx3Caps[3];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HDMI_MAC_RX3_SUPPORT == _ON)
extern BYTE ScalerTmdsMacRx3HdmiGetAVIInfo(EnumAviInfoContent enumContent);
extern BYTE ScalerTmdsMacRx3HdmiRsv6GetAviInfo(EnumAviInfoContent enumContent);
extern EnumContentType ScalerTmdsMacRx3HdmiGetAviContentType(void);
#endif

extern void ScalerTmdsMacRx3FreqDetectDisable(void);
extern void ScalerTmdsMacRx3HotPlugEvent(void);
extern bit ScalerTmdsMacRx3TMDSStableDetect(EnumSourceType enumSourceType);

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
#if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
extern void ScalerTmdsMacRx3HDMI2HPDRRIRQEnable(bit bEnable);
#endif
extern void ScalerTmdsMacRx3ScrambleStatusReset(void);
extern void ScalerTmdsMacRx3ScrambleDetectTimeoutTimerEvent(void);
extern void ScalerTmdsMacRx3ScrambleDetectDisable(void);
extern void ScalerTmdsMacRx3SetScdcInfo(void);
extern void ScalerTmdsMacRx3SetCedLockTransition(bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern void ScalerTmdsMacRx3SetAmdAupiScdcInfo(bit bEnable);
#endif
#endif
#endif

#if(_HDMI_SUPPORT == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
extern void ScalerTmdsMacRx3GetFreeSyncIIData(BYTE *pucFreeSyncIIData);
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
extern void ScalerTmdsMacRx3GetSBTMData(BYTE *pucSBTMData);
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
extern void ScalerTmdsMacRx3GetHDR10Data(BYTE *pucHDRData);
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
extern DWORD ScalerTmdsMacRx3FreeSyncHDMIGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif

extern void ScalerTmdsMacRx3TimerEventReset(void);
extern void ScalerTmdsMacRx3ForceMDomainMuteBeforeHpdToggle(void);
extern void ScalerTmdsMacRx3DviVideoSetting(void);
extern void ScalerTmdsMacRx3SetPorchColor(EnumColorSpace enumColorFormat);

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
extern void ScalerTmdsMacRx3HdmiVideoSetting(void);
extern bit ScalerTmdsMacRx3HdmiColorInfoChanged(void);
#endif


extern void ScalerTmdsMacRx3TMDSScanInitial(EnumInputPort enumInputPort);
extern bit ScalerTmdsMacRx3TMDSPSPreDetect(void);
extern bit ScalerTmdsMacRx3TMDSNormalPreDetect(void);
extern EnumSourceType ScalerTmdsMacRx3TMDSScanInputPort(EnumPortType enumPortType);
extern void ScalerTmdsMacRx3HighPriorityIntHandler_EXINT0(void);
extern void ScalerTmdsMacRx3LowPriorityIntHandler_EXINT0(void);
extern void ScalerTmdsMacRx3PSHighPriorityIntHandler_EXINT0(void);
extern void ScalerTmdsMacRx3PSLowPriorityIntHandler_EXINT0(void);

#if((_HDMI_MAC_RX3_SUPPORT == _ON) || (_3DDI_FUNCTION == _ON))
extern bit ScalerTmdsMacRx3HdmiDeepColorProc(WORD usTmdsClkCnt);
#endif

#if(_HDMI_MAC_RX3_SUPPORT == _ON)

extern void ScalerTmdsMacRx3HdmiPacketDetect(bit bWait);
extern void ScalerTmdsMacRx3HdmiPacketDetectEvent(void);

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
extern void ScalerTmdsMacRx3HdmiAdvancedHdr10DetectEvent(void);
#endif

#if(_DM_FUNCTION == _ON)
extern void ScalerTmdsMacRx3HdmiDmDetectEvent(void);
#endif

#if((_HDMI21_FVA_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON) || (_HDMI21_DHDR_SUPPORT == _ON) || (_HDMI_SBTM_SUPPORT == _ON))
extern void ScalerTmdsMacRx3EmpDetectEvent(void);
#endif

extern BYTE ScalerTmdsMacRx3HdmiGetColorDepth(void);
extern void ScalerTmdsMacRx3HdmiWatchDog(BYTE ucWDType, bit bEnable);
extern bit ScalerTmdsMacRx3BchErrorCheck(EnumInputPort enumInputPort);
#endif

extern void ScalerTmdsMacRx3PowerOffProc(void);
extern void ScalerTmdsMacRx3FirstActiveProc(EnumSourceType enumSourceType);
extern void ScalerTmdsMacRx3SetDeOnlyModeConfig(EnumDeOnlyConfig enumDeonlyConfig);
extern EnumDeOnlyConfig ScalerTmdsMacRx3GetDeOnlyModeConfig(void);
extern bit ScalerTmdsMacRx3HdcpEnabled(void);
extern void ScalerTmdsMacRx3ResetAllPacketReceiveStatus(void);
extern BYTE ScalerTmdsMacRx3TMDSVideoDetect(bit bWait);
extern void ScalerTmdsMacRx3TMDSVideoDetectEvent(void);

extern bit ScalerTmdsMacRx3CheckCDRStable(WORD usClkCount);

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
extern void ScalerTmdsMacRx3HdmiAVMuteProc(void);
#endif

#if(_TMDS_NO_CLK_TRIGGER_AV_WATCHDOG == _ON)
extern void ScalerTmdsMacRx3NoClkWatchDogProc(void);
#endif

extern EnumSourceType ScalerTmdsMacRx3FormatDetect(void);

extern void ScalerTmdsMacRx3AfterHotPlugEventProc(bit bRestoreZ0);
extern void ScalerTmdsMacRx3HotPlugHighProc(WORD usHpdTime);
extern void ScalerTmdsMacRx3HotPlugLowProc(void);
extern void ScalerTmdsMacRx3BeforeHotPlugEventProc(bit bDisableZ0);
extern void ScalerTmdsMacRx3BackupHdcpType(void);
extern void ScalerTmdsMacRx3Hdcp1p4AksvClear(void);
extern void ScalerTmdsMacRx3HdcpFlagClear(void);
// extern void ScalerTmdsMacRx3HdmiIrqEnable(bit bEnable, StructHdmiIrqStatus *pstTmdsMacIrqStatus);
extern void ScalerTmdsMacRx3Initial(EnumInputPort enumInputPort);
extern void ScalerTmdsMacRx3InterruptInitial(void);
extern WORD ScalerTmdsMacRx3OnMeasureClk_EXINT0(BYTE ucLane);
extern BYTE ScalerTmdsMacRx3SaveOnMeasureSettings_EXINT0(void);
extern void ScalerTmdsMacRx3RestoreOnMeasureSettings_EXINT0(BYTE ucStableTimes);

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
extern void ScalerTmdsMacRx3SetScdcInfo_EXINT0(void);
extern void ScalerTmdsMacRx3SetCedLockTransition_EXINT0(bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern void ScalerTmdsMacRx3SetAmdAupiScdcInfo_EXINT0(bit bEnable);
#endif
#endif
#endif


extern void ScalerTmdsMacRx3ResetMacInput_EXINT0(void);

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
#if(_DM_FUNCTION == _ON)
extern bit ScalerTmdsMacRx3GetDMDramReceived_EXINT0(void);
extern void ScalerTmdsMacRx3DMPacketReCheck_EXINT0(void);
#endif

#endif
extern void ScalerTmdsMacRx3PowerSavingProc(void);
extern void ScalerTmdsMacRx3SwitchHdcpSlaveAddr(void);
extern void ScalerTmdsMacRx3FreqDetectClkGating(void);
extern void ScalerTmdsMacRx3DPLLOffProc(WORD usVCOFreq, BYTE ucPreDiv, BYTE ucOutputDiv, BYTE ucNcode);

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
extern void ScalerTmdsMacRx3SetAudioPLLOffProc(void);
extern void ScalerTmdsMacRx3SetAudioNCode(BYTE ucNcode);
extern void ScalerTmdsMacRx3SetAudioFCode(WORD usFcode);
extern void ScalerTmdsMacRx3SetAudioClampNCode(void);
#endif
#endif // End of #if(_TMDS_MAC_RX3_SUPPORT == _ON)

