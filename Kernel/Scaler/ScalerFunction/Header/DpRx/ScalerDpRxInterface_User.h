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
// ID Code      : ScalerDpRxInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DP Link Rate
//--------------------------------------------------
typedef enum
{
    _DP_LINK_NONE = _DP_LINK_SPEED_NONE,
    _DP_LINK_RBR = _DP_LOW_SPEED_162MHZ,
    _DP_LINK_HBR = _DP_HIGH_SPEED_270MHZ,
    _DP_LINK_HBR2 = _DP_HIGH_SPEED2_540MHZ,
    _DP_LINK_HBR3 = _DP_HIGH_SPEED3_810MHZ,
    _DP_LINK_HBR3_9G = _DP_HIGH_SPEED3_900MHZ,
    _DP_LINK_UHBR10 = _DP_ULTRA_SPEED_1000MHZ,
    _DP_LINK_UHBR13_5 = _DP_ULTRA_SPEED_1350MHZ,
    _DP_LINK_UHBR20 = _DP_ULTRA_SPEED_2000MHZ,
} EnumDpLinkRate;

//--------------------------------------------------
// Definitions of DP Link Rate
//--------------------------------------------------
typedef enum
{
    _DP_DPCD_00001_LINK_NONE = 0x00,
    _DP_DPCD_00001_LINK_RBR = 0x06,
    _DP_DPCD_00001_LINK_HBR = 0x0A,
    _DP_DPCD_00001_LINK_HBR2 = 0x14,
    _DP_DPCD_00001_LINK_HBR3 = 0x1E,
    _DP_DPCD_02201_LINK_NONE = 0x00,
    _DP_DPCD_02201_LINK_RBR = 0x06,
    _DP_DPCD_02201_LINK_HBR = 0x0A,
    _DP_DPCD_02201_LINK_HBR2 = 0x14,
    _DP_DPCD_02201_LINK_HBR3 = 0x1E,
    _DP_DPCD_02215_LINK_NONE = 0x00,
    _DP_DPCD_02215_LINK_UHBR10 = _BIT0,
    _DP_DPCD_02215_LINK_UHBR13_5 = _BIT2,
    _DP_DPCD_02215_LINK_UHBR20 = _BIT1,
} EnumDpDpcdLinkRate;

//--------------------------------------------------
// Definitions of DP Maink Link Channel Coding
//--------------------------------------------------
typedef enum
{
    _CODING_TYPE_NONE = 0x00,
    _CODING_TYPE_8B10B = 0x01,
    _CODING_TYPE_128B132B = 0x02,
}EnumDpLinkChannelCodingType;

//--------------------------------------------------
// Enumerations of DP Version Type
//--------------------------------------------------
typedef enum
{
    _DP_VERSION_1_0 = 0x10,
    _DP_VERSION_1_1 = 0x11,
    _DP_VERSION_1_2 = 0x12,
    _DP_VERSION_1_3 = 0x13,
    _DP_VERSION_1_4 = 0x14,
    _DP_VERSION_2_0 = 0x20,
} EnumDpVersionType;

//--------------------------------------------------
// Enumerations of DP Lane Count
//--------------------------------------------------
typedef enum
{
    _DP_LINK_NO_LANE = 0x00,
    _DP_LINK_1_LANE = 0x01,
    _DP_LINK_2_LANE = 0x02,
    _DP_LINK_4_LANE = 0x04,
} EnumDpLaneCount;

//--------------------------------------------------
// Enumerations of MST Rx Port
//--------------------------------------------------
typedef enum
{
    _DP_MST_NO_PORT,
    _DP_MST_RX0_PORT,
    _DP_MST_RX1_PORT,
    _DP_MST_RX2_PORT,
    _DP_MST_AUTO_PORT,
} EnumDPMSTPort;

//--------------------------------------------------
// Define DP MST PxP Mode
//--------------------------------------------------
typedef enum
{
    _DP_MST_PXP_OFF = 0,
    _DP_MST_PXP_ON_FIXED_MODE = 1, // _DP_MST_PXP_FIXED_MODE
    _DP_MST_PXP_ON_SELECT_MODE = 2, // _DP_MST_PXP_SELECT_MODE
} EnumDpMstPxpMode;

//--------------------------------------------------
// Define DP MST PXP Port Num Swap Status
//--------------------------------------------------
typedef enum
{
    _DP_PXP_PORT_NUM_SWAP_FALSE,
    _DP_PXP_PORT_NUM_SWAP_TRUE,
} EnumDpPxpPortNumSwapStatus;

//--------------------------------------------------
// Enumerations of User DP Clone Output Status
//--------------------------------------------------
typedef enum
{
    _DP_CLONE_OUTPUT_FALSE,
    _DP_CLONE_OUTPUT_TRUE,
} EnumDPCloneOutputStatus;

//--------------------------------------------------
// Definitions of DP Lane
//--------------------------------------------------
typedef enum
{
    _DP_LANE_0,
    _DP_LANE_1,
    _DP_LANE_2,
    _DP_LANE_3,
} EnumDpLane;

//--------------------------------------------------
// Definitions of DP Voltage Swing Level
//--------------------------------------------------
typedef enum
{
    _DP_LINK_VOLTAGE_SWING_LEVEL_0,
    _DP_LINK_VOLTAGE_SWING_LEVEL_1,
    _DP_LINK_VOLTAGE_SWING_LEVEL_2,
    _DP_LINK_VOLTAGE_SWING_LEVEL_3,
} EnumDpVoltageSwingLevel;

//--------------------------------------------------
// Definitions of DP Pre-emphasis Level
//--------------------------------------------------
typedef enum
{
    _DP_LINK_PREEMPHASIS_LEVEL_0,
    _DP_LINK_PREEMPHASIS_LEVEL_1,
    _DP_LINK_PREEMPHASIS_LEVEL_2,
    _DP_LINK_PREEMPHASIS_LEVEL_3,
} EnumDpPreEmphasisLevel;

typedef struct
{
    WORD usDpRxLane0ErrorCount;
    WORD usDpRxLane1ErrorCount;
    WORD usDpRxLane2ErrorCount;
    WORD usDpRxLane3ErrorCount;
} StructDpRxErrorCount;

//--------------------------------------------------
// Enumerations of DP Rx MSA Value
//--------------------------------------------------
typedef union
{
    WORD usDpRxMsaHtotal;
    WORD usDpRxMsaHstart;
    WORD usDpRxMsaHwidth;
    WORD usDpRxMsaHsw;
    WORD usDpRxMsaVtotal;
    WORD usDpRxMsaVstart;
    WORD usDpRxMsaVheight;
    WORD usDpRxMsaVsw;
    DWORD ulDpRxMsaMvid;
    DWORD ulDpRxMsaNvid;
    DWORD ulDpRxMsaMaud;
    DWORD ulDpRxMsaNaud;
    QWORD uqDpRxMsaVfreq;
    QWORD uqDpRxMsaAfreq;
    bit bDpRxMsaHsp;
    bit bDpRxMsaVsp;
    QWORD uqDpRxMsaError;
} UnionDpRxMsaValue;

//--------------------------------------------------
// Enumerations of DP Rx MSA Type
//--------------------------------------------------
typedef enum
{
    _DP_RX_MSA_HTOTAL,
    _DP_RX_MSA_HSTART,
    _DP_RX_MSA_HWIDTH,
    _DP_RX_MSA_HSW,
    _DP_RX_MSA_VTOTAL,
    _DP_RX_MSA_VSTART,
    _DP_RX_MSA_VHEIGHT,
    _DP_RX_MSA_VSW,
    _DP_RX_MSA_MVID,
    _DP_RX_MSA_NVID,
    _DP_RX_MSA_MAUD,
    _DP_RX_MSA_NAUD,
    _DP_RX_MSA_VFREQ,
    _DP_RX_MSA_AFREQ,
    _DP_RX_MSA_HSP,
    _DP_RX_MSA_VSP,
} EnumDpRxMsaType;

//--------------------------------------------------
// Definitions of DP Power State
//--------------------------------------------------
typedef enum
{
    _DP_POWER_NORMAL = 0x00,
    _DP_POWER_DOWN,
    _DP_POWER_DOWN_WITH_AUX,
} EnumDpPowerState;

//--------------------------------------------------
// Enumerations of DP PR Mode Support
//--------------------------------------------------
typedef enum
{
    _DP_PR_MODE_SUPPORT_OFF = 0x00,
    _DP_PR_MODE_SUPPORT_ON,
} EnumDpPRModeSupport;

//--------------------------------------------------
// Enumerations of DP Auxless ALPM Support
//--------------------------------------------------
typedef enum
{
    _DP_AUXLESS_ALPM_SUPPORT_OFF = 0x00,
    _DP_AUXLESS_ALPM_SUPPORT_ON,
} EnumDpAuxlessAlpmSupport;

#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
//--------------------------------------------------
// Enumerations of DP Hdr Support
//--------------------------------------------------
typedef enum
{
    _DP_HDR_SUPPORT_OFF = 0x00,
    _DP_HDR_SUPPORT_ON,
} EnumDpHdrSupport;
#endif

//--------------------------------------------------
// Enumerations of DP Hot Plug Assert Type
//--------------------------------------------------
typedef enum
{
    _DP_HPD_USER_NONE,
    _DP_HPD_USER_LOW,
    _DP_HPD_USER_HIGH,
} EnumDpHotPlugType_User;

//--------------------------------------------------
// Definitions of DP HPD Toggle Mode Control By User
//--------------------------------------------------
typedef enum
{
    _DP_HPD_TOGGLE_NORMAL = 0x00,
    _DP_HPD_TOGGLE_NONE = 0x01,
} EnumDpHpdToggleMode;

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_D9_EMBEDDED_XRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
extern BYTE g_pucDpRx0PxpEdid[_D9_EMBEDDED_XRAM_MAX_SIZE];
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
extern BYTE g_pucDpRx1PxpEdid[_D9_EMBEDDED_XRAM_MAX_SIZE];
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
extern BYTE g_pucDpRx2PxpEdid[_D9_EMBEDDED_XRAM_MAX_SIZE];
#endif
#else
extern BYTE g_pucDpRxPxpEdid[_D9_EMBEDDED_XRAM_MAX_SIZE];
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif
