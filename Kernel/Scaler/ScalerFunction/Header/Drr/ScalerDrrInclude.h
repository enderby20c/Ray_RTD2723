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
// ID Code      : ScalerDrrInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Define for SPD Packet Type
//--------------------------------------------------
#if((_FREESYNC_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON) || (_HDMI_SPD_IF_RCV_BY_RR == _ON))
#define _SPD_INFO_TYPE                                      0x83
#endif


//--------------------------------------------------
// Definitions of FreeSync enable status
//--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
#define GET_FREESYNC_DP_TX_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpTxEnable)
#define SET_FREESYNC_DP_TX_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpTxEnable = _ENABLE)
#define CLR_FREESYNC_DP_TX_ENABLED()                        (g_stDrrFreeSyncDpInfo.b1DpTxEnable = _DISABLE)
#endif // End of #if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#endif

//--------------------------------------------------
// Definitions of FreeSync info frame received status
//--------------------------------------------------
#if(_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_SPD_INFO_FRAME_RECEIVED()              (g_bDrrFreeSyncSpdInfoReceive)
#define SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(x)             (g_bDrrFreeSyncSpdInfoReceive = (x))
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
#define GET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx0SpdInfoFrameReceived)
#define SET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx0SpdInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx0SpdInfoFrameReceived = _FALSE)

#define GET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx1SpdInfoFrameReceived)
#define SET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx1SpdInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx1SpdInfoFrameReceived = _FALSE)

#define GET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx2SpdInfoFrameReceived)
#define SET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx2SpdInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx2SpdInfoFrameReceived = _FALSE)

#define GET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx3SpdInfoFrameReceived)
#define SET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx3SpdInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx3SpdInfoFrameReceived = _FALSE)

#define GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx4SpdInfoFrameReceived)
#define SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx4SpdInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx4SpdInfoFrameReceived = _FALSE)

#define GET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx5SpdInfoFrameReceived)
#define SET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx5SpdInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stDrrFreeSyncHdmiInfo.b1HdmiRx5SpdInfoFrameReceived = _FALSE)
#endif // End of #if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
#define GET_TMDS_RX3_FREESYNC_REPLAY_RECEIVED()             (g_stDrrFreeSyncHdmiInfo.b1HdmiRx3FreesyncReplayReceived)
#define SET_TMDS_RX3_FREESYNC_REPLAY_RECEIVED()             (g_stDrrFreeSyncHdmiInfo.b1HdmiRx3FreesyncReplayReceived = _TRUE)
#define CLR_TMDS_RX3_FREESYNC_REPLAY_RECEIVED()             (g_stDrrFreeSyncHdmiInfo.b1HdmiRx3FreesyncReplayReceived = _FALSE)

#define GET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED()             (g_stDrrFreeSyncHdmiInfo.b1HdmiRx4FreesyncReplayReceived)
#define SET_TMDS_RX4_FREESYNC_REPLAY_RECEIVED()             (g_stDrrFreeSyncHdmiInfo.b1HdmiRx4FreesyncReplayReceived = _TRUE)
#define CLR_TMDS_RX4_FREESYNC_REPLAY_RECEIVED()             (g_stDrrFreeSyncHdmiInfo.b1HdmiRx4FreesyncReplayReceived = _FALSE)
#endif

//--------------------------------------------------
// Definitions of AdaptiveSync DP info
//--------------------------------------------------
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#define GET_ADAPTIVESYNC_DP_D0_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD0CapabilitySwitch)
#define SET_ADAPTIVESYNC_DP_D0_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD0CapabilitySwitch = _TRUE)
#define CLR_ADAPTIVESYNC_DP_D0_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD0CapabilitySwitch = _FALSE)

#define GET_ADAPTIVESYNC_DP_D1_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD1CapabilitySwitch)
#define SET_ADAPTIVESYNC_DP_D1_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD1CapabilitySwitch = _TRUE)
#define CLR_ADAPTIVESYNC_DP_D1_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD1CapabilitySwitch = _FALSE)

#define GET_ADAPTIVESYNC_DP_D2_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD2CapabilitySwitch)
#define SET_ADAPTIVESYNC_DP_D2_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD2CapabilitySwitch = _TRUE)
#define CLR_ADAPTIVESYNC_DP_D2_CAPABILITY_SWITCH()          (g_stDrrDpAdaptiveSyncInfo.b1DpD2CapabilitySwitch = _FALSE)
#endif

//--------------------------------------------------
// Definitions of FreeSync DP info
//--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_DP_D0_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD0CapabilitySwitch)
#define SET_FREESYNC_DP_D0_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD0CapabilitySwitch = _TRUE)
#define CLR_FREESYNC_DP_D0_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD0CapabilitySwitch = _FALSE)

#define GET_FREESYNC_DP_D1_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD1CapabilitySwitch)
#define SET_FREESYNC_DP_D1_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD1CapabilitySwitch = _TRUE)
#define CLR_FREESYNC_DP_D1_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD1CapabilitySwitch = _FALSE)

#define GET_FREESYNC_DP_D2_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD2CapabilitySwitch)
#define SET_FREESYNC_DP_D2_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD2CapabilitySwitch = _TRUE)
#define CLR_FREESYNC_DP_D2_CAPABILITY_SWITCH()              (g_stDrrFreeSyncDpInfo.b1DpD2CapabilitySwitch = _FALSE)
#endif

//--------------------------------------------------
// Definitions of FreeSync HDMI info
//--------------------------------------------------
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
#define GET_FREESYNC_HDMI_VCP()                             (g_ucDrrFreeSyncHdmiVcpReceive)
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON))
#define GET_HDMI_RX3_AMD_SPD_INFO(x)                        (ScalerTmdsMacRx3FreeSyncHDMIGetAmdSpdInfo(x))
#define GET_HDMI_RX4_AMD_SPD_INFO(x)                        (ScalerTmdsMacRx4FreeSyncHDMIGetAmdSpdInfo(x))
#endif

//--------------------------------------------------
// Definitions of Get FreeSyncII Data
//--------------------------------------------------
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#define GET_FREESYNC_II_TMDS_RX3_DATA(x)                    (ScalerTmdsMacRx3GetFreeSyncIIData(x))
#define GET_FREESYNC_II_TMDS_RX4_DATA(x)                    (ScalerTmdsMacRx4GetFreeSyncIIData(x))
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DSC_DECODER_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
#define _IVSTART_PRODUCE_BY_BE                              0
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Enum for Freesync II
//--------------------------------------------------
typedef enum
{
    _TMDS_INFO_RSV2_DB0 = 0x22,
    _TMDS_INFO_RSV2_DB1 = 0x23,
}EnumHdrMasteringInfoFrameTMDSRSV2;
#endif // End of (_HDMI_FREESYNC_II_SUPPORT == _ON)


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern volatile BYTE g_ucDrrFreeSyncHdmiVcpReceive;
#endif

#if(_FREESYNC_SUPPORT == _ON)
extern bit g_bDrrFreeSyncSpdInfoReceive;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DRR_SUPPORT == _ON)

extern void ScalerDrrTestPinEnable(void);

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern bit ScalerDrrDpAdaptiveSyncCapabilitySwitchProc(EnumInputPort enumInputPort);
extern void ScalerDrrDpAdaptiveSyncSetEnable(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerDrrDpAdaptiveSyncGetEnable(EnumInputPort enumInputPort);
#endif

#if(_FREESYNC_SUPPORT == _ON)

extern EnumAmdVsdbVer ScalerDrrGetAmdVsdbVer(EnumInputPort enumInputPort);
#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDrrFreeSyncDpCapabilitySwitchProc(EnumInputPort enumInputPort);
extern EnumFreeSyncSupport ScalerDrrFreeSyncDpGetSupport(EnumInputPort enumInputPort);
extern bit ScalerDrrFreeSyncDpGetStreamConfig(EnumInputPort enumInputPort);
extern void ScalerDrrFreeSyncDpSetEnable(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerDrrFreeSyncDpGetEnable(EnumInputPort enumInputPort);
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern bit ScalerDrrFreeSyncHdmiGetEnable(EnumInputPort enumInputPort);
#endif
#endif // End of #if(_HDMI_SUPPORT == _ON)

#endif
#endif

#if((_DRR_SUPPORT == _ON) || ((_FW_DSC_FRL_IVS_PRODUCE_BE == _ON) && (_DSC_MAC_DECODER_SUPPORT == _ON)) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
extern void ScalerDrrUpdateVsyncSetting(void);
extern void ScalerDrrSetVsyncBypassWhenIVSProduceByBE(void);
#endif