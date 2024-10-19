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
// ID Code      : ScalerSyncInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Macros of HDMI HotPlug Toggle Support
//--------------------------------------------------
#define GET_DP_DC_OFF_HPD_HIGH()                            (g_bSyncDpDCOffHPDHigh)
#define SET_DP_DC_OFF_HPD_HIGH()                            (g_bSyncDpDCOffHPDHigh = _TRUE)
#define CLR_DP_DC_OFF_HPD_HIGH()                            (g_bSyncDpDCOffHPDHigh = _FALSE)

#define GET_HDMI_HOTPLUG_TOGGLE()                           ((g_ucSyncHdmiHotPlug & _BIT7) >> 7)
#define SET_HDMI_HOTPLUG_TOGGLE()                           (g_ucSyncHdmiHotPlug |= _BIT7)
#define CLR_HDMI_HOTPLUG_TOGGLE()                           (g_ucSyncHdmiHotPlug &= ~_BIT7)

#define GET_HDMI_HOTPLUG_TIME()                             ((WORD)(g_ucSyncHdmiHotPlug & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) * 100)
#define SET_HDMI_HOTPLUG_TIME(x)                            (g_ucSyncHdmiHotPlug = (g_ucSyncHdmiHotPlug & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | (x))

#define GET_DP_AUX_DIFF_MODE()                              (g_stSyncDpAuxSetting.b1DpAuxMode)
#define SET_DP_AUX_DIFF_MODE()                              (g_stSyncDpAuxSetting.b1DpAuxMode = _TRUE)
#define CLR_DP_AUX_DIFF_MODE()                              (g_stSyncDpAuxSetting.b1DpAuxMode = _FALSE)

#define GET_DP_AUX_ADJR_SETTING()                           (g_stSyncDpAuxSetting.b5DpAuxAdjrSet)
#define SET_DP_AUX_ADJR_SETTING(x)                          (g_stSyncDpAuxSetting.b5DpAuxAdjrSet = (x))
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP Illegal Idle Pattern Check
//--------------------------------------------------
#define GET_DP_ILLEGAL_IDLE_PATTERN_CHECK()                 (g_bSyncDpIllegalIdlePatternCheck)
#define SET_DP_ILLEGAL_IDLE_PATTERN_CHECK()                 (g_bSyncDpIllegalIdlePatternCheck = _TRUE)
#define CLR_DP_ILLEGAL_IDLE_PATTERN_CHECK()                 (g_bSyncDpIllegalIdlePatternCheck = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Source State
//--------------------------------------------------
typedef enum
{
    _SOURCE_VGA,
    _SOURCE_VIDEO,
    _SOURCE_DVI,
    _SOURCE_HDMI,
    _SOURCE_DP,
    _SOURCE_NONE,
    _SOURCE_AMOUNT = _SOURCE_NONE,
} EnumSourceType;

//--------------------------------------------------
// Enumerations of HDCP Type
//--------------------------------------------------
typedef enum
{
    _HDCP_NONE = 0x00,
    _HDCP_14 = 0x14,
    _HDCP_22 = 0x22,
    _HDCP_14_REPEATER = 0x94,
    _HDCP_22_REPEATER = 0xA2,
} EnumHDCPType;

//--------------------------------------------------
// Enumerations of Dp Edid Port
//--------------------------------------------------
typedef enum
{
    _D0_DP_EDID,
    _D1_DP_EDID,
    _D2_DP_EDID,
    _DP_TX_EDID,
    _NO_PORT_EDID,
} EnumDpEdidPort;

//--------------------------------------------------
// Structure for DP Margin Link
//--------------------------------------------------
typedef struct
{
    BYTE b1D0MarginLink : 1;
    BYTE b1D0Lane0MarginLinkTP1 : 1;
    BYTE b1D0Lane1MarginLinkTP1 : 1;
    BYTE b1D0Lane2MarginLinkTP1 : 1;
    BYTE b1D0Lane3MarginLinkTP1 : 1;
    BYTE b1D0Lane0MarginLinkTP2 : 1;
    BYTE b1D0Lane1MarginLinkTP2 : 1;
    BYTE b1D0Lane2MarginLinkTP2 : 1;
    BYTE b1D0Lane3MarginLinkTP2 : 1;
    BYTE b1D1MarginLink : 1;
    BYTE b1D1Lane0MarginLinkTP1 : 1;
    BYTE b1D1Lane1MarginLinkTP1 : 1;
    BYTE b1D1Lane2MarginLinkTP1 : 1;
    BYTE b1D1Lane3MarginLinkTP1 : 1;
    BYTE b1D1Lane0MarginLinkTP2 : 1;
    BYTE b1D1Lane1MarginLinkTP2 : 1;
    BYTE b1D1Lane2MarginLinkTP2 : 1;
    BYTE b1D1Lane3MarginLinkTP2 : 1;
    BYTE b1D2MarginLink : 1;
    BYTE b1D2Lane0MarginLinkTP1 : 1;
    BYTE b1D2Lane1MarginLinkTP1 : 1;
    BYTE b1D2Lane2MarginLinkTP1 : 1;
    BYTE b1D2Lane3MarginLinkTP1 : 1;
    BYTE b1D2Lane0MarginLinkTP2 : 1;
    BYTE b1D2Lane1MarginLinkTP2 : 1;
    BYTE b1D2Lane2MarginLinkTP2 : 1;
    BYTE b1D2Lane3MarginLinkTP2 : 1;
    BYTE b1D6MarginLink : 1;
} StructDPMarginLinkInfo;

//--------------------------------------------------
// Structure for DP Aux
//--------------------------------------------------
typedef struct
{
    BYTE b1DpAuxMode : 1;
    BYTE b5DpAuxAdjrSet : 5;
} StructDpAuxSetting;

//--------------------------------------------------
// Structure of HDR Static Metadata
//--------------------------------------------------
typedef struct
{
    BYTE ucVersion;
    BYTE ucLength;

    BYTE ucEOTF;
    BYTE ucStaticMetadataID;

    WORD usDisplayPrimariesX0;
    WORD usDisplayPrimariesY0;

    WORD usDisplayPrimariesX1;
    WORD usDisplayPrimariesY1;

    WORD usDisplayPrimariesX2;
    WORD usDisplayPrimariesY2;

    WORD usWhitePointX;
    WORD usWhitePointY;

    WORD usMaxDisplayMasteringLv;
    WORD usMinDisplayMasteringLv;
    WORD usMaxCLL;
    WORD usMaxFALL;
} StructHDR10StaticMetaData;

//--------------------------------------------------
// Structure of HDR SBTM Info
//--------------------------------------------------
typedef struct
{
    WORD usFrmPbLimitInt;
    EnumHDR10SBTMType enumHDR10SBTMType;
    EnumHDR10SBTMMode enumHDR10SBTMMode;
    EnumHDR10SBTMGRDMLumMaxType enumHDR10SBTMGRDMLumMaxType;
    EnumHDR10SBTMGRDMMinType enumHDR10SBTMGRDMMinType;
    BYTE ucSBTMVer;
} StructHDR10SBTMInfo;

//--------------------------------------------------
// Structure of Freesync II
//--------------------------------------------------
typedef struct
{
    BYTE b1NativeColorSpaceEnable : 1;
    BYTE b1BacklightControlEnable : 1;
    BYTE b1LocalDimmingDisable : 1;
    BYTE b5EOTFType : 5;
    BYTE ucBacklightControlRatio;
} StructFreeSyncIIInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DIGITAL_PORT_SUPPORT == _ON)
extern bit g_bSyncDpDCOffHPDHigh;
extern BYTE g_ucSyncHdmiHotPlug;
#endif

#if(_DP_SUPPORT == _ON)
extern StructDpAuxSetting g_stSyncDpAuxSetting;
extern bit g_bSyncDpIllegalIdlePatternCheck;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

