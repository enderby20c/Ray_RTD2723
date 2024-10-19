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
// ID Code      : RL6952_Gen_Option_Typedef.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------



////////
// HW //
////////
//--------------------------------------------------
// Enum of Pins support user to adjust configuration
//--------------------------------------------------
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_J4,
    _CONFIG_PIN_K4,
    _CONFIG_PIN_H4,
    _CONFIG_PIN_G6,
    _CONFIG_PIN_AD4,
    _CONFIG_PIN_W4,
    _CONFIG_PIN_W5,
    _CONFIG_PIN_T4,
    _CONFIG_PIN_AA4,
    _CONFIG_PIN_AA5,
    _CONFIG_PIN_AB4,
    _CONFIG_PIN_AB5,
    _CONFIG_PIN_AE4,
    _CONFIG_PIN_AE5,
    _CONFIG_PIN_AD5,
    _CONFIG_PIN_AF6,
    _CONFIG_PIN_AF7,
    _CONFIG_PIN_AG6,
    _CONFIG_PIN_AG7,
    _CONFIG_PIN_AF12,
    _CONFIG_PIN_AF11,
    _CONFIG_PIN_AF10,
    _CONFIG_PIN_AF9,
    _CONFIG_PIN_AG12,
    _CONFIG_PIN_AG11,
    _CONFIG_PIN_AG10,
    _CONFIG_PIN_AG9,
    _CONFIG_PIN_AG20,
    _CONFIG_PIN_AF20,
    _CONFIG_PIN_AF19,
    _CONFIG_PIN_AG22,
    _CONFIG_PIN_AF22,
    _CONFIG_PIN_AG23,
    _CONFIG_PIN_AE23,
    _CONFIG_PIN_AA22,
    _CONFIG_PIN_W23,
    _CONFIG_PIN_W22,
    _CONFIG_PIN_AE26,
    _CONFIG_PIN_AD26,
    _CONFIG_PIN_AB26,
    _CONFIG_PIN_AC26,
    _CONFIG_PIN_Y26,
    _CONFIG_PIN_AA26,
    _CONFIG_PIN_Y23,
    _CONFIG_PIN_Y22,
    _CONFIG_PIN_AA23,
    _CONFIG_PIN_Y24,
    _CONFIG_PIN_AA24,
    _CONFIG_PIN_Y25,
    _CONFIG_PIN_AA25,
    _CONFIG_PIN_AC25,
    _CONFIG_PIN_AB25,
    _CONFIG_PIN_R28,
    _CONFIG_PIN_R30,
    _CONFIG_PIN_R29,
    _CONFIG_PIN_P28,
    _CONFIG_PIN_P29,
    _CONFIG_PIN_N29,
    _CONFIG_PIN_N30,
    _CONFIG_PIN_N28,
    _CONFIG_PIN_L28,
    _CONFIG_PIN_L30,
    _CONFIG_PIN_L29,
    _CONFIG_PIN_K28,
    _CONFIG_PIN_K29,
    _CONFIG_PIN_J29,
    _CONFIG_PIN_J30,
    _CONFIG_PIN_J28,
    _CONFIG_PIN_G28,
    _CONFIG_PIN_G30,
    _CONFIG_PIN_G29,
    _CONFIG_PIN_F28,
    _CONFIG_PIN_F29,
    _CONFIG_PIN_E29,
    _CONFIG_PIN_E30,
    _CONFIG_PIN_E28,
    _CONFIG_PIN_C28,
    _CONFIG_PIN_A28,
    _CONFIG_PIN_B28,
    _CONFIG_PIN_C27,
    _CONFIG_PIN_B27,
    _CONFIG_PIN_B26,
    _CONFIG_PIN_A26,
    _CONFIG_PIN_C26,
    _CONFIG_PIN_C24,
    _CONFIG_PIN_A24,
    _CONFIG_PIN_B24,
    _CONFIG_PIN_C23,
    _CONFIG_PIN_B23,
    _CONFIG_PIN_B22,
    _CONFIG_PIN_A22,
    _CONFIG_PIN_C22,
    _CONFIG_PIN_B20,
    _CONFIG_PIN_A20,
    _CONFIG_PIN_B19,
    _CONFIG_PIN_A19,
    _CONFIG_PIN_K9,
    _CONFIG_PIN_H13,
    _CONFIG_PIN_H11,
    _CONFIG_PIN_K8,
    _CONFIG_PIN_H12,
    _CONFIG_PIN_J8,
    _CONFIG_PIN_F9,
    _CONFIG_PIN_F11,
    _CONFIG_PIN_F12,
    _CONFIG_PIN_E13,
    _CONFIG_PIN_F13,
    _CONFIG_PIN_E12,
    _CONFIG_PIN_G9,
    _CONFIG_PIN_F8,
    _CONFIG_PIN_E3,
    _CONFIG_PIN_H8,
    _CONFIG_PIN_D5,
    _CONFIG_PIN_D4,
    _CONFIG_PIN_D3,
    _CONFIG_PIN_H7,
    _CONFIG_PIN_C5,
    _CONFIG_PIN_B5,
    _CONFIG_PIN_B4,
    _CONFIG_PIN_C4,
    _CONFIG_PIN_C3,
    _CONFIG_PIN_J9,
    _CONFIG_PIN_E5,
    _CONFIG_PIN_D12,
    _CONFIG_PIN_D13,
    _CONFIG_PIN_H9,
    _CONFIG_PIN_A5,
    _CONFIG_PIN_E11,
    _CONFIG_PIN_V4,
    _CONFIG_PIN_U4,
    _CONFIG_PIN_G8,
    _CONFIG_PIN_E4,
    _CONFIG_PIN_G7,
    _CONFIG_PIN_A2,
    _CONFIG_PIN_B3,
    _CONFIG_PIN_B2,
    _CONFIG_PIN_A4,
    _CONFIG_PIN_A3,
    _CONFIG_PIN_G5,
    _CONFIG_PIN_F4,
    _CONFIG_PIN_H5,
    _CONFIG_PIN_F3,
} EnumConfigPin;


////////
// FW //
////////
//--------------------------------------------------
// Format conversion source setting
//--------------------------------------------------
typedef enum
{
    _FC_SOURCE_DPMAC0 = (_BIT1 | _BIT0),            // 0011
    _FC_SOURCE_DPMAC1 = _BIT2,                      // 0100
    _FC_SOURCE_DPMAC2 = (_BIT2 | _BIT0),            // 0101
    _FC_SOURCE_HDMI0 = (_BIT2 | _BIT1 | _BIT0),     // 0111
    _FC_SOURCE_HDMI1 = _BIT3,                       // 1000
    _FC_SOURCE_DSC0 = (_BIT3 | _BIT1 | _BIT0),      // 1011
    _FC_SOURCE_DSC1 = (_BIT3 | _BIT2),              // 1100
    _FC_SOURCE_NONE = 0xFF,
} EnumFormatConversionSourceType;

typedef enum
{
    _DPTX_OUTPUT_MAC_D0 = (_BIT1 | _BIT0),          // 0011
    _DPTX_OUTPUT_MAC_D1 = _BIT2,                    // 0100
    _DPTX_OUTPUT_MAC_D2 = (_BIT2 | _BIT0),          // 0101
    _DPTX_OUTPUT_MAC_D3 = (_BIT2 | _BIT1 | _BIT0),  // 0111
    _DPTX_OUTPUT_MAC_D4 = _BIT3,                    // 1000
    _DPTX_OUTPUT_DSC0 = (_BIT3 | _BIT1 | _BIT0),    // 1011
    _DPTX_OUTPUT_DSC1 = (_BIT3 | _BIT2),            // 1100
    _DPTX_OUTPUT_NONE = 0xFF,
} EnumDPTxOutputSelMacFrom;
//--------------------------------------------------
// Power Cut Region
//--------------------------------------------------
typedef enum
{
    /* 001 */ _POWER_CUT_GROUP_RX0_DP20_U32_APHY = 0x00,
    /* 002 */ _POWER_CUT_GROUP_RX0_DP_DPHY,
    /* 003 */ _POWER_CUT_GROUP_RX0_DP_AUX,
    /* 004 */ // No Power Domain
    /* 005 */ // No Power Domain
    /* 006 */ _POWER_CUT_GROUP_RX1_DP20_U32_APHY,
    /* 007 */ _POWER_CUT_GROUP_RX1_DP_DPHY,
    /* 008 */ _POWER_CUT_GROUP_RX1_DP_AUX,
    /* 009 */ // No Power Domain
    /* 010 */ // No Power Domain
    /* 011 */ _POWER_CUT_GROUP_RX2_DP20_APHY,
    /* 012 */ _POWER_CUT_GROUP_RX2_DP_DPHY,
    /* 013 */ _POWER_CUT_GROUP_RX2_DP_AUX,
    /* 014 */ // No Power Domain
    /* 015 */ // No Power Domain
    /* 016 */ _POWER_CUT_GROUP_RX3_HDMI21_APHY,
    /* 017 */ _POWER_CUT_GROUP_RX3_HDMI_DPHY,
    /* 018 */ _POWER_CUT_GROUP_RX3_HDMI20_MAC,
    /* 019 */ _POWER_CUT_GROUP_RX3_HDMI21_MAC,
    /* 020 */ _POWER_CUT_GROUP_RX4_HDMI21_APHY,
    /* 021 */ _POWER_CUT_GROUP_RX4_HDMI_DPHY,
    /* 022 */ _POWER_CUT_GROUP_RX4_HDMI20_MAC,
    /* 023 */ _POWER_CUT_GROUP_RX4_HDMI21_MAC,
    /* 024 */ _POWER_CUT_GROUP_DSC_0,
    /* 025 */ _POWER_CUT_GROUP_FORMAT_CONVERSION,
    /* 026 */ // No Power Domain
    /* 027 */ // No Power Domain
    /* 028 */ // No Power Domain
    /* 029 */ _POWER_CUT_GROUP_TYPE_C_0_PD_MAC,
    /* 030 */ _POWER_CUT_GROUP_USB_UFP,
    /* 031 */ _POWER_CUT_GROUP_JFM,
    /* 032 */ _POWER_CUT_GROUP_USB_DFP_DPHY,
    /* 033 */ _POWER_CUT_GROUP_DPTX_DP20_MAC,
    /* 034 */ _POWER_CUT_GROUP_DPTX_DP14_MAC,
    /* 035 */ _POWER_CUT_GROUP_PX0_DP20_APHY,
    /* 036 */ _POWER_CUT_GROUP_PX0_AUX,
    /* 037 */ // No Power Domain
    /* 038 */ // No Power Domain
    /* 039 */ _POWER_CUT_GROUP_TOPOFF,
    /* 040 */ // No Power Domain
    /* 041 */ // No Power Domain
    /* 042 */ _POWER_CUT_GROUP_IMC_ENC_M1,
    /* 043 */ _POWER_CUT_GROUP_IMC_DEC_M1,
    /* 044 */ _POWER_CUT_GROUP_IMC_ENC_M2,
    /* 045 */ _POWER_CUT_GROUP_IMC_DEC_M2,
    /* 046 */ // No Power Domain
    /* 047 */ // No Power Domain
    /* 048 */ // No Power Domain
    /* 049 */ // No Power Domain
    /* 050 */ // No Power Domain
    /* 051 */ // No Power Domain
    /* 052 */ // No Power Domain
    /* 053 */ _POWER_CUT_GROUP_IMC_ENC_S1,
    /* 054 */ _POWER_CUT_GROUP_IMC_DEC_S1,
    /* 055 */ // No Power Domain
    /* 056 */ // No Power Domain
    /* 057 */ // No Power Domain
    /* 058 */ // No Power Domain
    /* 059 */ // No Power Domain
    /* 060 */ // No Power Domain
    /* 061 */ // No Power Domain
    /* 062 */ // No Power Domain
    /* 063 */ // No Power Domain
    /* 064 */ // No Power Domain
    /* 065 */ // No Power Domain
    /* 066 */ // No Power Domain
    /* 067 */ // No Power Domain
    /* 068 */ // No Power Domain
    /* 069 */ // No Power Domain
    /* 070 */ // No Power Domain
    /* 071 */ // No Power Domain
    /* 072 */ // No Power Domain
    /* 073 */ // No Power Domain
    /* 074 */ // No Power Domain
    /* 075 */ // No Power Domain
    /* 076 */ // No Power Domain
    /* 077 */ // No Power Domain
    /* 078 */ // No Power Domain
    /* 079 */ // No Power Domain
    /* 080 */ // No Power Domain
    /* 081 */ // No Power Domain
    /* 082 */ // No Power Domain
    /* 083 */ // No Power Domain
    /* 084 */ // No Power Domain
    /* 085 */ // No Power Domain
    /* 086 */ // No Power Domain
    /* 087 */ // No Power Domain
    /* 088 */ // No Power Domain
    /* 089 */ // No Power Domain
    /* 090 */ // No Power Domain
    /* 091 */ // No Power Domain
    /* 092 */ // No Power Domain
    /* 093 */ _POWER_CUT_GROUP_USB32_DFP_APHY,
    /* 094 */ // No Power Domain
    /* 095 */ // No Power Domain
    /* 096 */ _POWER_CUT_GROUP_THERMAL_SENSOR,
    /* 097 */ _POWER_CUT_GROUP_TYPE_C_0_BMC,
    /* 098 */ _POWER_CUT_GROUP_TYPE_C_1_BMC,
    /* 099 */ _POWER_CUT_GROUP_VBO_EDP_8_LANE,
    /* 100 */ // No Power Domain
    /* 101 */ // No Power Domain
    /* 102 */ _POWER_CUT_GROUP_DSC_1,
    /* 103 */ _POWER_CUT_GROUP_TYPE_C_0_CC_MAC,
    /* 104 */ _POWER_CUT_GROUP_TYPE_C_1_CC_MAC,
    /* 105 */ _POWER_CUT_GROUP_TYPE_C_1_PD_MAC,
    /* 106 */ _POWER_CUT_GROUP_10_BIT_SARADC,
    /* 107 */ _POWER_CUT_GROUP_HDCP_ECDSA,
    /* 108 */ _POWER_CUT_GROUP_RX0_DP14_DPHY,
    /* 109 */ _POWER_CUT_GROUP_RX0_DP14_MAC,
    /* 110 */ _POWER_CUT_GROUP_RX0_DP20_DPHY,
    /* 111 */ _POWER_CUT_GROUP_RX0_DP20_MAC,
    /* 112 */ _POWER_CUT_GROUP_RX1_DP14_DPHY,
    /* 113 */ _POWER_CUT_GROUP_RX1_DP14_MAC,
    /* 114 */ _POWER_CUT_GROUP_RX1_DP20_DPHY,
    /* 115 */ _POWER_CUT_GROUP_RX1_DP20_MAC,
    /* 116 */ _POWER_CUT_GROUP_RX2_DP14_DPHY,
    /* 117 */ _POWER_CUT_GROUP_RX2_DP14_MAC,
    /* 118 */ _POWER_CUT_GROUP_RX2_DP20_DPHY,
    /* 119 */ _POWER_CUT_GROUP_RX2_DP20_MAC,
    /* 120 */ // No Power Domain
    /* 121 */ _POWER_CUT_GROUP_USB_UFP_RETIMER_MAC,
    /* 122 */ _POWER_CUT_GROUP_USB_DFP_RETIMER_MAC,
    /* 123 */ _POWER_CUT_GROUP_ANTI_ALIASING_M1M2,
}EnumPowerGroup;

//--------------------------------------------------
// Clock Gating Group
//--------------------------------------------------
typedef enum
{
    _CLOCK_GATING_GROUP_IR,
    _CLOCK_GATING_GROUP_SPI_0_MASTER,
    _CLOCK_GATING_GROUP_SPI_1_MASTER,
    _CLOCK_GATING_GROUP_SPI_2_MASTER,
}EnumPowerClockGatingGroup;

//--------------------------------------------------
// Data Recover from Power Cut State
//--------------------------------------------------
typedef enum
{
    _POWER_DATA_RECOVER_TOP = 0x00,
    _POWER_DATA_RECOVER_GDITX,
    _POWER_DATA_RECOVER_DPMAC,
} EnumPowerRecoverGroup;

//--------------------------------------------------
// OTPMemory type
//--------------------------------------------------
typedef enum
{
    _OTPMEMORY_CHECK_EMPTY = 0x00,
    _OTPMEMORY_HDCP14_RXKEY,
    _OTPMEMORY_HDCP14_RXKEYBKSV,
    _OTPMEMORY_HDCP14_TXKEY,
    _OTPMEMORY_HDCP14_TXKEYBKSV,
    _OTPMEMORY_HDCP22_RXKEY,
    _OTPMEMORY_HDCP22_RXKEY_CERTRX,
    _OTPMEMORY_HDCP22_RXKEY_KPRIV,
    _OTPMEMORY_HDCP22_RXKEY_RRMODN,
    _OTPMEMORY_HDCP22_RXKEY_NPINV,
    _OTPMEMORY_HDCP22_RXKEY_DKEY,
    _OTPMEMORY_HDCP22_RXKEY_LCKEY,
    _OTPMEMORY_TYPE_C_0_TRIMDATA,
    _OTPMEMORY_TYPE_C_0_1M_TRIMDATA,
    _OTPMEMORY_TYPE_C_1_TRIMDATA,
    _OTPMEMORY_TYPE_C_1_1M_TRIMDATA,
    _OTPMEMORY_LVDS_AB_IBHN_TRIMDATA,
    _OTPMEMORY_DDC_CONFIG,
    _OTPMEMORY_IOSC_TRIMDATA,
    _OTPMEMORY_HDMI_RETIMER,
    _OTPMEMORY_M2PLL_CONFIG,
    _OTPMEMORY_HDMI_TRIMDATA,
    _OTPMEMORY_CEC1_CONFIG,
    _OTPMEMORY_EMCU_CONFIG,
    _OTPMEMORY_THERMAL_SENSOR,
    _OTPMEMORY_SLP_MODE,
    _OTPMEMORY_HDCP_LOCATION,
    _OTPMEMORY_LVDS_CD_IBHN_TRIMDATA,
    _OTPMEMORY_LVDS_VCM_AB_TRIMDATA,
    _OTPMEMORY_LVDS_VCM_CD_TRIMDATA,
    _OTPMEMORY_AUDIO_CORNER_CONFIG,
    _OTPMEMORY_EARC_TRIMDATA,
    _OTPMEMORY_TYPE_C_SARADC_TRIMDATA,
    _OTPMEMORY_MST_DPTX_IB_TRIMDATA,
    _OTPMEMORY_SINK_ASS_1M_TRIMDATA,
    _OTPMEMORY_FEATURE_CTRL_BYTE,
} EnumOTPMemoryData;

//-------------------------------------------------
// Memory BW Ctrl
//-------------------------------------------------
typedef enum
{
    _DBUS_SB_CLIENT_BEGIN,
    //----------System Bridge Clients----------
    _DBUS_TV_SB2_C00_EARC_TX_R = _DBUS_SB_CLIENT_BEGIN,
    _DBUS_TV_SB2_C01_FRC_CAP_M1,
    _DBUS_TV_SB2_C02_FRC_CAP_M2,
    _DBUS_TV_SB2_C03_EARC_TX_W,
    _DBUS_TV_SB2_C04_FRC_DISP_M1,
    _DBUS_TV_SB2_C05_FRC_DISP_M2,
    _DBUS_TV_SB2_C07_FRC_DISP_S1,
    _DBUS_TV_SB2_C09_FRC_CAP_S1,
    _DBUS_TV_SB2_C11_OD_M1_W,
    _DBUS_TV_SB2_C13_OD_M1_R,
    _DBUS_TV_SB2_C14_OD_M2_R,
    _DBUS_TV_SB2_C15_OD_M2_W,
    //----------System Bridge Clients----------
    _DBUS_SB_CLIENT_END,
} EnumMemoryClient;

typedef enum
{
    _MEM_CLIENT_FRC_CAP,
    _MEM_CLIENT_FRC_DISP,
    _MEM_CLIENT_OD_W,
    _MEM_CLIENT_OD_R,
    _MEM_CLIENT_EARC_TX_W,
    _MEM_CLIENT_EARC_TX_R,
} EnumMemoryClientType;
