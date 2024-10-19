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
// ID Code      : RL6829_Gen_Option_Typedef.h No.0000
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
    _CONFIG_PIN_A3,
    _CONFIG_PIN_C5,
    _CONFIG_PIN_B3,
    _CONFIG_PIN_B4,
    _CONFIG_PIN_B2,
    _CONFIG_PIN_C4,
    _CONFIG_PIN_B1,
    _CONFIG_PIN_C1,
    _CONFIG_PIN_E4,
    _CONFIG_PIN_E3,
    _CONFIG_PIN_E2,
    _CONFIG_PIN_C2,
    _CONFIG_PIN_F3,
    _CONFIG_PIN_F2,
    _CONFIG_PIN_C3,
    _CONFIG_PIN_D4,
    _CONFIG_PIN_D2,
    _CONFIG_PIN_D3,
    _CONFIG_PIN_D1,
    _CONFIG_PIN_E1,
    _CONFIG_PIN_J1,
    _CONFIG_PIN_F4,
    _CONFIG_PIN_G1,
    _CONFIG_PIN_H4,
    _CONFIG_PIN_Y5,
    _CONFIG_PIN_Y4,
    _CONFIG_PIN_AB5,
    _CONFIG_PIN_AB6,
    _CONFIG_PIN_AC6,
    _CONFIG_PIN_AA8,
    _CONFIG_PIN_AH1,
    _CONFIG_PIN_AJ1,
    _CONFIG_PIN_AD6,
    _CONFIG_PIN_AD5,
    _CONFIG_PIN_AF7,
    _CONFIG_PIN_AG7,
    _CONFIG_PIN_Y8,
    _CONFIG_PIN_AG6,
    _CONFIG_PIN_Y6,
    _CONFIG_PIN_AC5,
    _CONFIG_PIN_AE5,
    _CONFIG_PIN_AE6,
    _CONFIG_PIN_AE7,
    _CONFIG_PIN_AH3,
    _CONFIG_PIN_AJ3,
    _CONFIG_PIN_AG5,
    _CONFIG_PIN_AM21,
    _CONFIG_PIN_AL21,
    _CONFIG_PIN_AG12,
    _CONFIG_PIN_AE14,
    _CONFIG_PIN_AG14,
    _CONFIG_PIN_AF15,
    _CONFIG_PIN_AH22,
    _CONFIG_PIN_AJ22,
    _CONFIG_PIN_AF20,
    _CONFIG_PIN_AH23,
    _CONFIG_PIN_AJ23,
    _CONFIG_PIN_AH24,
    _CONFIG_PIN_AJ24,
    _CONFIG_PIN_AD27,
    _CONFIG_PIN_AC27,
    _CONFIG_PIN_AD28,
    _CONFIG_PIN_AC28,
    _CONFIG_PIN_AD29,
    _CONFIG_PIN_AC29,
    _CONFIG_PIN_AD30,
    _CONFIG_PIN_AC30,
    _CONFIG_PIN_AE32,
    _CONFIG_PIN_AE31,
    _CONFIG_PIN_AD32,
    _CONFIG_PIN_AD31,
    _CONFIG_PIN_AC32,
    _CONFIG_PIN_AC31,
    _CONFIG_PIN_AB32,
    _CONFIG_PIN_AB31,
    _CONFIG_PIN_AA32,
    _CONFIG_PIN_AA31,
    _CONFIG_PIN_Y32,
    _CONFIG_PIN_Y31,
    _CONFIG_PIN_W32,
    _CONFIG_PIN_W31,
    _CONFIG_PIN_H31,
    _CONFIG_PIN_H32,
    _CONFIG_PIN_G31,
    _CONFIG_PIN_G32,
    _CONFIG_PIN_F31,
    _CONFIG_PIN_F32,
    _CONFIG_PIN_E31,
    _CONFIG_PIN_E32,
    _CONFIG_PIN_D31,
    _CONFIG_PIN_D32,
    _CONFIG_PIN_C31,
    _CONFIG_PIN_C32,
    _CONFIG_PIN_B31,
    _CONFIG_PIN_B32,
    _CONFIG_PIN_C29,
    _CONFIG_PIN_B29,
    _CONFIG_PIN_C28,
    _CONFIG_PIN_B28,
    _CONFIG_PIN_C27,
    _CONFIG_PIN_B27,
    _CONFIG_PIN_C26,
    _CONFIG_PIN_B26,
    _CONFIG_PIN_G21,
    _CONFIG_PIN_E21,
    _CONFIG_PIN_E19,
    _CONFIG_PIN_E20,
    _CONFIG_PIN_F21,
    _CONFIG_PIN_F20,
    _CONFIG_PIN_F19,
    _CONFIG_PIN_E18,
    _CONFIG_PIN_AL27,
    _CONFIG_PIN_AL26,
    _CONFIG_PIN_AL29,
    _CONFIG_PIN_AL28,
    _CONFIG_PIN_AM28,
    _CONFIG_PIN_AM29,
    _CONFIG_PIN_AM30,
    _CONFIG_PIN_AJ18,
    _CONFIG_PIN_AK20,
    _CONFIG_PIN_AK25,
    _CONFIG_PIN_AM26,
    _CONFIG_PIN_AM27,
    _CONFIG_PIN_AJ25,
    _CONFIG_PIN_AK21,
    _CONFIG_PIN_AM25,
    _CONFIG_PIN_AL25,
    _CONFIG_PIN_AK17,
    _CONFIG_PIN_AK18,
    _CONFIG_PIN_J4,
    _CONFIG_PIN_H11,
    _CONFIG_PIN_G11,
    _CONFIG_PIN_E7,
    _CONFIG_PIN_G7,
    _CONFIG_PIN_G10,
    _CONFIG_PIN_F10,
    _CONFIG_PIN_G9,
    _CONFIG_PIN_E8,
    _CONFIG_PIN_E10,
    _CONFIG_PIN_D9,
    _CONFIG_PIN_D10,
    _CONFIG_PIN_G8,
    _CONFIG_PIN_H9,
    _CONFIG_PIN_E9,
    _CONFIG_PIN_F9,
    _CONFIG_PIN_J3,
    _CONFIG_PIN_J2,
    _CONFIG_PIN_H3,
    _CONFIG_PIN_H2,
    _CONFIG_PIN_E11,
    _CONFIG_PIN_F8,
    _CONFIG_PIN_F1,
    _CONFIG_PIN_G4,
    _CONFIG_PIN_H1,
    _CONFIG_PIN_F7,
    _CONFIG_PIN_H7,
    _CONFIG_PIN_G2,
    _CONFIG_PIN_G3,
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
    _FC_SOURCE_PXP = (_BIT3 | _BIT2 | _BIT0),       // 1101
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
    _DPTX_OUTPUT_SST = (_BIT3 | _BIT2 | _BIT0),     // 1101
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
    /* 004 */ _POWER_CUT_GROUP_RX0_DP14_MAC,
    /* 005 */ _POWER_CUT_GROUP_RX0_DP20_MAC,
    /* 006 */ _POWER_CUT_GROUP_RX1_DP20_U32_APHY,
    /* 007 */ _POWER_CUT_GROUP_RX1_DP_DPHY,
    /* 008 */ _POWER_CUT_GROUP_RX1_DP_AUX,
    /* 009 */ _POWER_CUT_GROUP_RX1_DP14_MAC,
    /* 010 */ _POWER_CUT_GROUP_RX1_DP20_MAC,
    /* 011 */ _POWER_CUT_GROUP_RX2_DP20_APHY,
    /* 012 */ _POWER_CUT_GROUP_RX2_DP_DPHY,
    /* 013 */ _POWER_CUT_GROUP_RX2_DP_AUX,
    /* 014 */ _POWER_CUT_GROUP_RX2_DP14_MAC,
    /* 015 */ _POWER_CUT_GROUP_RX2_DP20_MAC,
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
    /* 026 */ _POWER_CUT_GROUP_3DDI_PATH_0,
    /* 027 */ _POWER_CUT_GROUP_3DDI_PATH_1,
    /* 028 */ _POWER_CUT_GROUP_TR9,
    /* 029 */ _POWER_CUT_GROUP_TYPE_C_TOTAL,
    /* 030 */ _POWER_CUT_GROUP_USB_UFP,
    /* 031 */ _POWER_CUT_GROUP_JFM,
    /* 032 */ _POWER_CUT_GROUP_USB_DFP_DPHY,
    /* 033 */ _POWER_CUT_GROUP_DPTX_DP20_MAC,
    /* 034 */ _POWER_CUT_GROUP_DPTX_DP14_MAC,
    /* 035 */ _POWER_CUT_GROUP_PX0_DP20_APHY,
    /* 036 */ _POWER_CUT_GROUP_PX0_AUX,
    /* 037 */ _POWER_CUT_GROUP_MST2SST_DP14_MAC,
    /* 038 */ _POWER_CUT_GROUP_MST2SST_DP20_MAC,
    /* 039 */ _POWER_CUT_GROUP_TOPOFF,
    /* 040 */ _POWER_CUT_GROUP_DOLBY_M1M2,
    /* 041 */ _POWER_CUT_GROUP_EO_TO_FB_M1M2,
    /* 042 */ _POWER_CUT_GROUP_IMC_ENC_M1,
    /* 043 */ _POWER_CUT_GROUP_IMC_DEC_M1,
    /* 044 */ _POWER_CUT_GROUP_IMC_ENC_M2,
    /* 045 */ _POWER_CUT_GROUP_IMC_DEC_M2,
    /* 046 */ _POWER_CUT_GROUP_FB_TO_EO_M1M2,
    /* 047 */ _POWER_CUT_GROUP_LOCAL_CONTRAST_M1M2,
    /* 048 */ _POWER_CUT_GROUP_DOLBY_S1,
    /* 049 */ _POWER_CUT_GROUP_I_DOMAIN_S1S2,
    /* 050 */ _POWER_CUT_GROUP_DOLBY_S2,
    /* 051 */ // No Power Domain
    /* 052 */ _POWER_CUT_GROUP_EO_TO_FB_S1S2,
    /* 053 */ _POWER_CUT_GROUP_IMC_ENC_S1,
    /* 054 */ _POWER_CUT_GROUP_IMC_DEC_S1,
    /* 055 */ _POWER_CUT_GROUP_IMC_ENC_S2,
    /* 056 */ _POWER_CUT_GROUP_IMC_DEC_S2,
    /* 057 */ _POWER_CUT_GROUP_FB_TO_EO_S1S2,
    /* 058 */ _POWER_CUT_GROUP_M_DOMAIN_S1S2,
    /* 059 */ _POWER_CUT_GROUP_D_DOMAIN_M3M4,
    /* 060 */ _POWER_CUT_GROUP_LOCAL_CONTRAST_M3M4,
    /* 061 */ _POWER_CUT_GROUP_I_DOMAIN_S3S4,
    /* 062 */ _POWER_CUT_GROUP_EO_TO_FB_S3S4,
    /* 063 */ _POWER_CUT_GROUP_IMC_ENC_S3,
    /* 064 */ _POWER_CUT_GROUP_IMC_DEC_S3,
    /* 065 */ _POWER_CUT_GROUP_IMC_ENC_S4,
    /* 066 */ _POWER_CUT_GROUP_IMC_DEC_S4,
    /* 067 */ _POWER_CUT_GROUP_FB_TO_EO_S3S4,
    /* 068 */ _POWER_CUT_GROUP_M_DOMAIN_S3S4,
    /* 069 */ _POWER_CUT_GROUP_D_DOMAIN_S1S2,
    /* 070 */ _POWER_CUT_GROUP_LOCAL_CONTRAST_S1S2,
    /* 071 */ _POWER_CUT_GROUP_3D_GAMMA_M1M2,
    /* 072 */ _POWER_CUT_GROUP_INPUT_GAMMA_M1M2,
    /* 073 */ _POWER_CUT_GROUP_LOCAL_DIMMING_M1M2,
    /* 074 */ _POWER_CUT_GROUP_UNIFORMITY_M1M2,
    /* 075 */ _POWER_CUT_GROUP_UNIFORMITY_SRAM_M1M2M3M4,
    /* 076 */ _POWER_CUT_GROUP_D_DOMAIN_BLENDING_M3M4,
    /* 077 */ _POWER_CUT_GROUP_3D_GAMMA_M3M4,
    /* 078 */ _POWER_CUT_GROUP_INPUT_GAMMA_M3M4,
    /* 079 */ _POWER_CUT_GROUP_LOCAL_DIMMING_M3M4,
    /* 080 */ _POWER_CUT_GROUP_UNIFORMITY_M3M4,
    /* 081 */ // No Power Domain
    /* 082 */ _POWER_CUT_GROUP_2D_GRAPHIC_OSD_FRONT,
    /* 083 */ _POWER_CUT_GROUP_2D_GRAPHIC_OSD_BACK,
    /* 084 */ _POWER_CUT_GROUP_VBO_MAC_16_LANE_1,
    /* 085 */ _POWER_CUT_GROUP_VBO_MAC_16_LANE_2,
    /* 086 */ _POWER_CUT_GROUP_EDPTX_MAC_4_LANE_1,
    /* 087 */ _POWER_CUT_GROUP_EDPTX_MAC_4_LANE_2,
    /* 088 */ _POWER_CUT_GROUP_EDPTX_MAC_4_LANE_3,
    /* 089 */ _POWER_CUT_GROUP_EDPTX_MAC_4_LANE_4,
    /* 090 */ _POWER_CUT_GROUP_DISPLAY_CONVERSION,
    /* 091 */ _POWER_CUT_GROUP_PXP_DP14_MAC,
    /* 092 */ _POWER_CUT_GROUP_PXP_DP20_MAC,
    /* 093 */ _POWER_CUT_GROUP_USB32_DFP_APHY,
    /* 094 */ // No Power Domain
    /* 095 */ // No Power Domain
    /* 096 */ _POWER_CUT_GROUP_THERMAL_SENSOR,
    /* 097 */ _POWER_CUT_GROUP_TYPE_C_0_BMC,
    /* 098 */ _POWER_CUT_GROUP_TYPE_C_1_BMC,
    /* 099 */ _POWER_CUT_GROUP_VBO_EDP_16_LANE_0,
    /* 100 */ _POWER_CUT_GROUP_CMU,
    /* 101 */ _POWER_CUT_GROUP_VBO_EDP_16_LANE_1,
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
    _OTPMEMORY_TYPE_C_SARADC_TRIMDATA,
    _OTPMEMORY_LVDS_IBHN_TRIMDATA,
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
    _OTPMEMORY_LVDS_VCM_AB_TRIMDATA,
    _OTPMEMORY_LVDS_VCM_CD_TRIMDATA,
    _OTPMEMORY_MST_DPTX_TRIMDATA,
    _OTPMEMORY_CTRL1_CONFIG,
    _OTPMEMORY_CTRL_FEATURE,
    _OTPMEMORY_DPTX_BANDGAP_TRIMDATA,
} EnumOTPMemoryData;

//-------------------------------------------------
// Memory BW Ctrl
//-------------------------------------------------
typedef enum
{
    _DBUS_CLIENT_BEGIN,
    //----------DCU DBUS Clients----------
    _DBUS_C00_RBUSD = _DBUS_CLIENT_BEGIN,
    _DBUS_C01_U2R,
    _DBUS_C02_BW32,
    _DBUS_C03_TV_SB2, // System Bridge TV_SB2
    _DBUS_C04_TV_SB4, // System Bridge TV_SB4
    _DBUS_C05_SE,
    _DBUS_C06_RESERVED,
    _DBUS_C08_RESERVED,
    _DBUS_C11_MCU,
    //----------DCU DBUS Clients----------
    _DBUS_CLIENT_END,

    _DBUS_SB_CLIENT_BEGIN = _DBUS_CLIENT_END,
    //----------System Bridge Clients----------
    _DBUS_TV_SB2_C00_FRC_DISP_S3 = _DBUS_SB_CLIENT_BEGIN,
    _DBUS_TV_SB2_C01_FRC_CAP_M1,
    _DBUS_TV_SB2_C02_FRC_CAP_M2,
    _DBUS_TV_SB2_C03_FRC_CAP_S3,
    _DBUS_TV_SB2_C04_FRC_DISP_M1,
    _DBUS_TV_SB2_C05_FRC_DISP_M2,
    _DBUS_TV_SB2_C06_FRC_DISP_S4,
    _DBUS_TV_SB2_C07_FRC_DISP_S1,
    _DBUS_TV_SB2_C08_FRC_DISP_S2,
    _DBUS_TV_SB2_C09_FRC_CAP_S1,
    _DBUS_TV_SB2_C10_FRC_CAP_S4,
    _DBUS_TV_SB2_C11_3DDI_PATH0_W,
    _DBUS_TV_SB2_C12_FRC_CAP_S2,
    _DBUS_TV_SB2_C13_3DDI_PATH0_R,
    _DBUS_TV_SB2_C14_3DDI_PATH1_R,
    _DBUS_TV_SB2_C15_3DDI_PATH1_W,

    _DBUS_TV_SB4_C00_GOSD_F1_R,
    _DBUS_TV_SB4_C01_OD_M1_W,
    _DBUS_TV_SB4_C02_GOSD_F2_R,
    _DBUS_TV_SB4_C03_GOSD_F3_R,
    _DBUS_TV_SB4_C04_GOSD_B1_R,
    _DBUS_TV_SB4_C05_GOSD_B2_R,
    _DBUS_TV_SB4_C06_GOSD_B3_R,
    _DBUS_TV_SB4_C07_OD_M2_W,
    _DBUS_TV_SB4_C08_OD_M1_R,
    _DBUS_TV_SB4_C09_OD_M2_R,
    _DBUS_TV_SB4_C10_OD_M3_W,
    _DBUS_TV_SB4_C11_OD_M3_R,
    _DBUS_TV_SB4_C12_OD_M4_W,
    _DBUS_TV_SB4_C13_OD_M4_R,
    //----------System Bridge Clients----------
    _DBUS_SB_CLIENT_END,
} EnumMemoryClient;

typedef enum
{
    _MEM_CLIENT_FRC_CAP,
    _MEM_CLIENT_FRC_DISP,
    _MEM_CLIENT_OD_W,
    _MEM_CLIENT_OD_R,
    _MEM_CLIENT_3DDI_W,
    _MEM_CLIENT_3DDI_R,
    _MEM_CLIENT_GOSD_F,
    _MEM_CLIENT_GOSD_B,
    _MEM_CLIENT_GOSE_SE,
} EnumMemoryClientType;
