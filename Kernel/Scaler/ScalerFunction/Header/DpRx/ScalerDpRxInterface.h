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
// ID Code      : ScalerDpRxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
#if(_DP_PR_MODE_SUPPORT == _ON)
#define GET_DP_PR_MODE_D0_SUPPORT()                         (g_stDpRxPRModeInfo.b1DpD0Support)
#define SET_DP_PR_MODE_D0_SUPPORT(x)                        (g_stDpRxPRModeInfo.b1DpD0Support = (x))

#define GET_DP_PR_MODE_D1_SUPPORT()                         (g_stDpRxPRModeInfo.b1DpD1Support)
#define SET_DP_PR_MODE_D1_SUPPORT(x)                        (g_stDpRxPRModeInfo.b1DpD1Support = (x))

#define GET_DP_PR_MODE_D2_SUPPORT()                         (g_stDpRxPRModeInfo.b1DpD2Support)
#define SET_DP_PR_MODE_D2_SUPPORT(x)                        (g_stDpRxPRModeInfo.b1DpD2Support = (x))
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define GET_DP_AUXLESS_ALPM_D0_SUPPORT()                    (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD0Support)
#define SET_DP_AUXLESS_ALPM_D0_SUPPORT(x)                   (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD0Support = (x))

#define GET_DP_AUXLESS_ALPM_D1_SUPPORT()                    (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD1Support)
#define SET_DP_AUXLESS_ALPM_D1_SUPPORT(x)                   (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD1Support = (x))

#define GET_DP_AUXLESS_ALPM_D2_SUPPORT()                    (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD2Support)
#define SET_DP_AUXLESS_ALPM_D2_SUPPORT(x)                   (g_stDpRxAuxlessAlpmInfo.b1DpAuxlessAlpmD2Support = (x))
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
#define GET_DP_HDR_D0_SUPPORT()                             (g_stDpRxHdrInfo.b1DpD0Support)
#define SET_DP_HDR_D0_SUPPORT(x)                            (g_stDpRxHdrInfo.b1DpD0Support = (x))

#define GET_DP_HDR_D1_SUPPORT()                             (g_stDpRxHdrInfo.b1DpD1Support)
#define SET_DP_HDR_D1_SUPPORT(x)                            (g_stDpRxHdrInfo.b1DpD1Support = (x))

#define GET_DP_HDR_D2_SUPPORT()                             (g_stDpRxHdrInfo.b1DpD2Support)
#define SET_DP_HDR_D2_SUPPORT(x)                            (g_stDpRxHdrInfo.b1DpD2Support = (x))
#endif
#endif

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP DC ON HPD Related
//--------------------------------------------------
#define GET_DP_DC_ON_HPD_TOGGLE_MODE()                      (g_enumDpRxDcOnHpdToggleMode)
#define SET_DP_DC_ON_HPD_TOGGLE_MODE(x)                     (g_enumDpRxDcOnHpdToggleMode = (x))
#endif

#if(_DP_USER_INT0_SUPPORT == _ON)
//--------------------------------------------------
// Macro of DP User Event
//--------------------------------------------------
#define GET_DP_RX_USER_INT_EVENT(enumInputPort, x)          ((g_penumDpRxUserIntEvent[(enumInputPort) - _D0_INPUT_PORT] & (x)) == (x))
#define SET_DP_RX_USER_INT_EVENT(enumInputPort, x)          (g_penumDpRxUserIntEvent[(enumInputPort) - _D0_INPUT_PORT] |= (x))
#define CLR_DP_RX_USER_INT_EVENT(enumInputPort, x)          (g_penumDpRxUserIntEvent[(enumInputPort) - _D0_INPUT_PORT] &= ~(x))
#endif
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DP Hot Plug Assert Type
//--------------------------------------------------
typedef enum
{
    _DP_HPD_LOW_RESET_AUX, // 1st priority
    _DP_HPD_LOW,
    _DP_MST_LONG_HPD_EVENT,
    _DP_HDCP_LONG_HPD_EVENT,
    _DP_LONG_HPD_EVENT,
    _DP_MARGIN_LINK_HPD_EVENT,
    _DP_HPD_ASSERTED,
    _DP_HPD_NONE = 0xFF,
} EnumDpHotPlugAssertType;

//--------------------------------------------------
// Enumerations of MST Info Backup
//--------------------------------------------------
typedef enum
{
    _DP_MST_BACKUP_INFO,
    _DP_MST_BACKUP_INFO_RESET,
    _DP_MST_BACKUP_INFO_RESTORE,
} EnumDpMstBackup;

//--------------------------------------------------
// Enumerations of DP MacX Select
//--------------------------------------------------
typedef enum
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    _DP_MAC_0 = 0x00,
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    _DP_MAC_1,
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    _DP_MAC_2,
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    _DP_MAC_3,
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    _DP_MAC_4,
#endif

    _DP_MAC_ENTITY_MAX,
    _DP_MAC_DUAL,
    _DP_MAC_NONE = 0xFF,
} EnumDpMacSel;

//--------------------------------------------------
// Enumerations of DP Mac DphyX Select
//--------------------------------------------------
typedef enum
{
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    _DP_MAC_DPHY_RX0 = 0x00,
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
    _DP_MAC_DPHY_RX1,
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
    _DP_MAC_DPHY_RX2,
#endif

    _DP_MAC_DPHY_ENTITY_MAX,
    _DP_MAC_DPHY_DUAL,
    _DP_MAC_DPHY_NONE = 0xFF,
} EnumDpMacDphySel;

//--------------------------------------------------
// Definitions of DP Mac Source Type
//--------------------------------------------------
typedef enum
{
    _STREAM_SOURCE_D0_DP = 0x00,
    _STREAM_SOURCE_D1_DP,
    _STREAM_SOURCE_D2_DP,
    _STREAM_SOURCE_PXP,
    _STREAM_SOURCE_MST2SST,
    _STREAM_SOURCE_NONE = 0xFF,
} EnumDpMacStreamSourceType;

//--------------------------------------------------
// Definitions of DP Mac Apply Type
//--------------------------------------------------
typedef enum
{
    _DP_MAC_APPLY_NONE,
    _DP_MAC_APPLY_DX_PORT,
    _DP_MAC_APPLY_MST2SST,
}EnumDpMacApplyType;

//--------------------------------------------------
// Enumerations of DP Input Port List
//--------------------------------------------------
#if(_DP_SUPPORT == _ON)
typedef enum
{
    _DP_D0_PORT,
    _DP_D1_PORT,
    _DP_D2_PORT,
    _DP_D7_PORT,
    _DP_D8_PORT,
}EnumDpInputPort;

//--------------------------------------------------
// Enumerations of DP Reset Status
//--------------------------------------------------
typedef enum
{
    _DP_DPCD_LINK_STATUS_INITIAL = 0x00,
    _DP_DPCD_LINK_STATUS_IRQ = 0x01,
} EnumDpResetStatus;

#endif

#if(_DP_SUPPORT == _ON)
#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DP PR Mode Support
//--------------------------------------------------
typedef struct
{
    BYTE b1DpD0Support : 1;
    BYTE b1DpD1Support : 1;
    BYTE b1DpD2Support : 1;

    BYTE b1DpD0Enable : 1;
    BYTE b1DpD1Enable : 1;
    BYTE b1DpD2Enable : 1;
    BYTE b1DpD9Enable : 1;

    BYTE b1DpD0CapabilitySwitch : 1;
    BYTE b1DpD1CapabilitySwitch : 1;
    BYTE b1DpD2CapabilitySwitch : 1;

} StructDpPRModeSupportInfo;
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DP AUXLESS ALPM Support
//--------------------------------------------------
typedef struct
{
    BYTE b1DpAuxlessAlpmD0Support : 1;
    BYTE b1DpAuxlessAlpmD1Support : 1;
    BYTE b1DpAuxlessAlpmD2Support : 1;

    BYTE b1DpAuxlessAlpmD0CapabilitySwitch : 1;
    BYTE b1DpAuxlessAlpmD1CapabilitySwitch : 1;
    BYTE b1DpAuxlessAlpmD2CapabilitySwitch : 1;

    BYTE b1DpAuxlessAlpmD0Enable : 1;
    BYTE b1DpAuxlessAlpmD1Enable : 1;
    BYTE b1DpAuxlessAlpmD2Enable : 1;
    BYTE b1DpAuxlessAlpmD9Enable : 1;

} StructDpAuxlessAlpmSupportInfo;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
//--------------------------------------------------
// Struct for DP Hdr Support
//--------------------------------------------------
typedef struct
{
    BYTE b1DpD0Support : 1;
    BYTE b1DpD1Support : 1;
    BYTE b1DpD2Support : 1;

    BYTE b1DpD0CapabilitySwitch : 1;
    BYTE b1DpD1CapabilitySwitch : 1;
    BYTE b1DpD2CapabilitySwitch : 1;

} StructDpHdrSupportInfo;
#endif
#endif

#if(_DP_USER_INT0_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP User Event
//--------------------------------------------------
typedef enum
{
    _DP_USER_INT_EVENT_NONE = 0x00,
    _DP_USER_INT_EVENT_SOURCE_WRITE_OUI = _BIT0,
    _DP_USER_INT_EVENT_ALL = 0xFF,
} EnumDpUserIntEvent;
#endif
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_SUPPORT == _ON)
#if(_DP_PR_MODE_SUPPORT == _ON)
extern volatile StructDpPRModeSupportInfo g_stDpRxPRModeInfo;
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern volatile StructDpAuxlessAlpmSupportInfo g_stDpRxAuxlessAlpmInfo;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
extern volatile StructDpHdrSupportInfo g_stDpRxHdrInfo;
#endif
#endif

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
extern EnumDpHpdToggleMode g_enumDpRxDcOnHpdToggleMode;
#endif

#if(_DP_USER_INT0_SUPPORT == _ON)
extern volatile EnumDpUserIntEvent g_penumDpRxUserIntEvent[];
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_SUPPORT == _ON)
extern void ScalerDpRxInitial(EnumInputPort enumInputPort);
extern EnumDpInputPort ScalerDpRxGetDpPort(BYTE ucIndex);
extern WORD ScalerDpRxGetInputPixelClock(EnumInputPort enumInputPort);

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void ScalerDpRxEdidSwitch(EnumInputPort enumInputPort);
#endif

extern void ScalerDpRxLaneCountSwitch(EnumInputPort enumInputPort, EnumDpLaneCount enumDpLaneCount);
extern void ScalerDpRxHotPlugHandler(void);
extern void ScalerDpRxReactiveTimerEventHotPlugAsserted(EnumInputPort enumInputPort, WORD usTime);
extern EnumDpMacStreamSourceType ScalerDpRxGetMacStreamSourceType(EnumDpMacSel enumMacSel);
extern EnumDpMacSel ScalerDpRxGetMacSwitchMappingSourceType(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern EnumInputPort ScalerDpRxGetInputPortMappingSourceType(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern void ScalerDpRxSetMacSwitchToInputPort(EnumDpMacSel enumDpMacSel, EnumInputPort enumInputPort);
extern EnumDpMacSel ScalerDpRxGetMacSwitch(EnumInputPort enumInputPort);
extern EnumInputPort ScalerDpRxMacGetInputPortSwitch(EnumDpMacSel enumDpMacSel);
extern EnumDpMacDphySel ScalerDpRxGetMacDphySwitch(EnumInputPort enumInputPort);
extern EnumInputPort ScalerDpRxMacDphyGetInputPortSwitch(EnumDpMacDphySel enumDpMacDphySel);
extern EnumDpMacStreamSourceType ScalerDpRxDxMacSourceMapping(EnumInputPort enumInputPort);
extern bit ScalerDpRxSetMacSwitch(EnumDpMacSel enumDpMacSel, EnumDpMacStreamSourceType enumMacSource);
extern bit ScalerDpRxCableStatus(EnumInputPort enumInputPort);
extern void ScalerDpRxSetCableStatus(EnumInputPort enumInputPort, bit bStatus);

#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
extern bit ScalerDpRxSetMacDphySwitch(EnumDpMacDphySel enumDpMacDphySel, EnumInputPort enumInputPort);
extern void ScalerDpRxSetMacDphySwitchToInputPort(EnumDpMacDphySel enumDpMacDphySel, EnumInputPort enumInputPort);
#endif

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
extern void ScalerDpRxClearMarginLink(EnumInputPort enumInputPort);
#endif

extern void ScalerDpRxVersionSwitch(EnumInputPort enumInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern bit ScalerDpRxGetVideoStream(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetDscStream(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetAudioStream(EnumInputPort enumInputPort);
extern StructDpRxErrorCount ScalerDpRxGetErrorCount(EnumInputPort enumInputPort);
extern EnumDpLinkRate ScalerDpRxRGetPcbMaxLinkRate(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetSrcMstEnable(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetSrcMstUpRequestEnable(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetMstCapability(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetTxCloneEnable(EnumInputPort enumInputPort);
extern bit ScalerDpRxGetHotPlugStatus(EnumInputPort enumInputPort);
extern void ScalerDpRxSetHotPlugEvent(EnumInputPort enumInputPort, EnumDpHotPlugAssertType enumHpdType);
extern EnumDpPowerState ScalerDpRxGetPowerStatus(EnumInputPort enumInputPort);
extern void ScalerDpRxMainPortInitial(EnumInputPort enumInputPort);
extern void ScalerDpRxMainPortSwitch(EnumInputPort enumInputPort);
extern EnumInputPort ScalerDpRxGetMainPort(void);
extern EnumDpLinkRate ScalerDpRxGetTargetMaxLinkRate(EnumInputPort enumInputPort);
extern BYTE ScalerDpRxGetConnectorType(EnumInputPort enumInputPort);

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
extern void ScalerDpRxSetMacDphyToStreamMux(EnumDpMacSel enumDpMacSel, EnumInputPort enumInputPort);
extern void ScalerDpRxMacDphyToStreamMuxReset(EnumDpMacSel enumDpMacSel);
#endif

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern void ScalerDpRxHpdIrqAssertTimer2EventProc_T2INT(void);
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
extern EnumInputPort ScalerDpRxGetPxpInputPortMux(void);
extern void ScalerDpRxSetPxpInputPortMux(EnumInputPort enumInputPort);
extern void ScalerDpRxResetPxpInputPortMux(EnumInputPort enumInputPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRxSinkCountUpdateProc(void);
extern void ScalerDpRxHdcpHandler(void);
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpRxMstToSstDscCapSwitchProc(void);
#endif

extern void ScalerDpRxIntHandler_EXINT0(void);
extern EnumInputPort ScalerDpRxGetInputPortMappingSourceType_EXINT0(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern EnumDpMacSel ScalerDpRxGetMacSwitch_EXINT0(EnumInputPort enumInputPort);
extern EnumDpMacSel ScalerDpRxGetMacSwitchMappingSourceType_EXINT0(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern EnumDpMacStreamSourceType ScalerDpRxDxMacSourceMapping_EXINT0(EnumInputPort enumInputPort);
extern EnumInputPort ScalerDpRxMacGetInputPortSwitch_EXINT0(EnumDpMacSel enumDpMacSel);
extern EnumInputPort ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(EnumDpMacDphySel enumDpMacDphySel);
extern EnumDpMacDphySel ScalerDpRxGetMacDphySwitch_EXINT0(EnumInputPort enumInputPort);
extern EnumInputPort ScalerDpRxMacGetInputPortSwitch_WDINT(EnumDpMacSel enumDpMacSel);
extern EnumInputPort ScalerDpRxGetInputPortMappingSourceType_WDINT(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern EnumDpMacSel ScalerDpRxGetMacSwitch_WDINT(EnumInputPort enumInputPort);
extern EnumDpMacDphySel ScalerDpRxGetMacDphySwitch_WDINT(EnumInputPort enumInputPort);
extern EnumInputPort ScalerDpRxMacDphyGetInputPortSwitch_WDINT(EnumDpMacDphySel enumDpMacDphySel);
extern EnumDpMacStreamSourceType ScalerDpRxDxMacSourceMapping_WDINT(EnumInputPort enumInputPort);

#if(_DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT == _ON)
extern void ScalerDpRxLongHpdSetAllowed(EnumInputPort enumInputPort, bit bAllowed);
extern bit ScalerDpRxLongHpdGetAllowed(EnumInputPort enumInputPort);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpRxPRModeSupportSwitch(EnumInputPort enumInputPort, EnumDpPRModeSupport enumSupport);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern void ScalerDpRxAuxlessAlpmSupportSwitch(EnumInputPort enumInputPort, EnumDpAuxlessAlpmSupport enumSupport);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
extern void ScalerDpRxHdrSupportSwitch(EnumInputPort enumInputPort, EnumDpHdrSupport enumDpHdrSupport);
extern EnumDpHdrSupport ScalerDpRxHdrGetSupport(EnumInputPort enumInputPort);
extern bit ScalerDpRxHdrCapabilitySwitchProc(EnumInputPort enumInputPort);
#endif
#endif
#endif
