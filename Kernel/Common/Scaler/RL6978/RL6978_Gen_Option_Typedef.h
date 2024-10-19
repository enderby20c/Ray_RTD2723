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
// ID Code      : RL6978_Gen_Option_Typedef.h No.0000
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
    _CONFIG_PIN_56,
    _CONFIG_PIN_57,
    _CONFIG_PIN_58,
    _CONFIG_PIN_59,
    _CONFIG_PIN_60,
    _CONFIG_PIN_61,
    _CONFIG_PIN_62,
    _CONFIG_PIN_63,
    _CONFIG_PIN_64,
    _CONFIG_PIN_65,
    _CONFIG_PIN_66,
    _CONFIG_PIN_67,
    _CONFIG_PIN_68,
    _CONFIG_PIN_69,
    _CONFIG_PIN_71,
    _CONFIG_PIN_72,
    _CONFIG_PIN_73,
    _CONFIG_PIN_74,
    _CONFIG_PIN_75,
    _CONFIG_PIN_78,
    _CONFIG_PIN_79,
    _CONFIG_PIN_80,
    _CONFIG_PIN_81,
    _CONFIG_PIN_82,
    _CONFIG_PIN_83,
    _CONFIG_PIN_100,
    _CONFIG_PIN_101,
    _CONFIG_PIN_102,
    _CONFIG_PIN_103,
    _CONFIG_PIN_104,
    _CONFIG_PIN_105,
    _CONFIG_PIN_106,
    _CONFIG_PIN_107,
    _CONFIG_PIN_109,
    _CONFIG_PIN_110,
    _CONFIG_PIN_111,
    _CONFIG_PIN_112,
    _CONFIG_PIN_113,
    _CONFIG_PIN_138,
    _CONFIG_PIN_139,
    _CONFIG_PIN_140,
    _CONFIG_PIN_141,
    _CONFIG_PIN_142,
    _CONFIG_PIN_143,
    _CONFIG_PIN_144,
    _CONFIG_PIN_148,
    _CONFIG_PIN_149,
    _CONFIG_PIN_150,
    _CONFIG_PIN_151,
    _CONFIG_PIN_152,
    _CONFIG_PIN_153,
    _CONFIG_PIN_155,
    _CONFIG_PIN_156,
    _CONFIG_PIN_157,
    _CONFIG_PIN_158,
    _CONFIG_PIN_159,
    _CONFIG_PIN_160,
    _CONFIG_PIN_161,
    _CONFIG_PIN_162,
    _CONFIG_PIN_204,
    _CONFIG_PIN_205,
    _CONFIG_PIN_206,
    _CONFIG_PIN_207,
    _CONFIG_PIN_208,
    _CONFIG_PIN_209,
    _CONFIG_PIN_210,
    _CONFIG_PIN_211,
    _CONFIG_PIN_213,
    _CONFIG_PIN_214,
    _CONFIG_PIN_215,
    _CONFIG_PIN_216,
    _CONFIG_PIN_217,
    _CONFIG_PIN_218,
    _CONFIG_PIN_221,
    _CONFIG_PIN_224,
    _CONFIG_PIN_225,
    _CONFIG_PIN_226,
    _CONFIG_PIN_227,
    _CONFIG_PIN_228,
    _CONFIG_PIN_229,
    _CONFIG_PIN_230,
    _CONFIG_PIN_233,
    _CONFIG_PIN_234,
    _CONFIG_PIN_235,
    _CONFIG_PIN_236,
    _CONFIG_PIN_237,
    _CONFIG_PIN_238,
    _CONFIG_PIN_241,
    _CONFIG_PIN_246,
    _CONFIG_PIN_247,
    _CONFIG_PIN_248,
    _CONFIG_PIN_249,
    _CONFIG_PIN_250,
    _CONFIG_PIN_251,
    _CONFIG_PIN_252,
    _CONFIG_PIN_253,
    _CONFIG_PIN_254,
    _CONFIG_PIN_255,
    _CONFIG_PIN_256,
    _CONFIG_PIN_257,
    _CONFIG_PIN_258,
    _CONFIG_PIN_259,
    _CONFIG_PIN_260,
    _CONFIG_PIN_261,
    _CONFIG_PIN_262,
    _CONFIG_PIN_263,
    _CONFIG_PIN_266,
    _CONFIG_PIN_267,
    _CONFIG_PIN_268,
    _CONFIG_PIN_269,
    _CONFIG_PIN_270,
    _CONFIG_PIN_271,
    _CONFIG_PIN_272,
    _CONFIG_PIN_273,
    _CONFIG_PIN_274,
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
    _FC_SOURCE_HDMI0 = (_BIT2 | _BIT1 | _BIT0),     // 0111
    _FC_SOURCE_NONE = 0xFF,
} EnumFormatConversionSourceType;

typedef enum
{
    _DPTX_OUTPUT_NONE = 0xFF,
} EnumDPTxOutputSelMacFrom;
//--------------------------------------------------
// Power Cut Region
//--------------------------------------------------
typedef enum
{
    /* 001 */ // No Power Domain,
    /* 002 */ _POWER_CUT_GROUP_RX0_DP_DPHY = 0x00,
    /* 003 */ _POWER_CUT_GROUP_RX0_DP_AUX,
    /* 004 */ // No Power Domain
    /* 005 */ // No Power Domain
    /* 006 */ // No Power Domain
    /* 007 */ // No Power Domain
    /* 008 */ _POWER_CUT_GROUP_RX1_DP_AUX,
    /* 009 */ // No Power Domain
    /* 010 */ // No Power Domain
    /* 011 */ // No Power Domain
    /* 012 */ // No Power Domain
    /* 013 */ _POWER_CUT_GROUP_RX2_DP_AUX,
    /* 014 */ // No Power Domain
    /* 015 */ // No Power Domain
    /* 016 */ // No Power Domain,
    /* 017 */ _POWER_CUT_GROUP_RX3_HDMI_DPHY,
    /* 018 */ _POWER_CUT_GROUP_RX3_HDMI20_MAC,
    /* 019 */ _POWER_CUT_GROUP_RX3_HDMI21_MAC,
    /* 020 */ // No Power Domain
    /* 021 */ // No Power Domain
    /* 022 */ // No Power Domain
    /* 023 */ // No Power Domain
    /* 024 */ // No Power Domain
    /* 025 */ _POWER_CUT_GROUP_FORMAT_CONVERSION,
    /* 026 */ // No Power Domain
    /* 027 */ // No Power Domain
    /* 028 */ // No Power Domain
    /* 029 */ // No Power Domain
    /* 030 */ _POWER_CUT_GROUP_USB_UFP,
    /* 031 */ _POWER_CUT_GROUP_JFM,
    /* 032 */ _POWER_CUT_GROUP_USB_DFP_DPHY,
    /* 033 */ // No Power Domain
    /* 034 */ // No Power Domain
    /* 035 */ // No Power Domain
    /* 036 */ // No Power Domain
    /* 037 */ // No Power Domain
    /* 038 */ // No Power Domain
    /* 039 */ _POWER_CUT_GROUP_TOPOFF,
    /* 040 */ // No Power Domain
    /* 041 */ // No Power Domain
    /* 042 */ _POWER_CUT_GROUP_IMC_ENC_M1,
    /* 043 */ _POWER_CUT_GROUP_IMC_DEC_M1,
    /* 044 */ // No Power Domain
    /* 045 */ // No Power Domain
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
    /* 096 */ // No Power Domain
    /* 097 */ // No Power Domain
    /* 098 */ // No Power Domain
    /* 099 */ // No Power Domain
    /* 100 */ // No Power Domain
    /* 101 */ // No Power Domain
    /* 102 */ // No Power Domain
    /* 103 */ // No Power Domain
    /* 104 */ // No Power Domain
    /* 105 */ // No Power Domain
    /* 106 */ // No Power Domain
    /* 107 */ _POWER_CUT_GROUP_HDCP_ECDSA,
    /* 108 */ _POWER_CUT_GROUP_RX0_DP14_DPHY,
    /* 109 */ _POWER_CUT_GROUP_RX0_DP14_MAC,
    /* 110 */ // No Power Domain
    /* 111 */ // No Power Domain
    /* 112 */ // No Power Domain
    /* 113 */ // No Power Domain
    /* 114 */ // No Power Domain
    /* 115 */ // No Power Domain
    /* 116 */ // No Power Domain
    /* 117 */ // No Power Domain
    /* 118 */ // No Power Domain
    /* 119 */ // No Power Domain
    /* 120 */ // No Power Domain
    /* 121 */ _POWER_CUT_GROUP_USB_UFP_RETIMER_MAC,
    /* 122 */ _POWER_CUT_GROUP_USB_DFP_RETIMER_MAC,
    /* 123 */ // No Power Domain
    /* 124 */ _POWER_CUT_GROUP_I_DOMAIN_S1,
    /* 125 */ _POWER_CUT_GROUP_2D_GRAPHIC_OSD,
    /* 126 */ _POWER_CUT_GROUP_LVDS_VBO_EDP_8_LANE,
    /* 127 */ _POWER_CUT_GROUP_TOP_ON_CUT,
    /* 128 */ _POWER_CUT_GROUP_EMCU_OFF,
    /* 129 */ _POWER_CUT_GROUP_DP_ON_CUT,
    /* 130 */ _POWER_CUT_GROUP_RX0_DP14_U3_APHY,
    /* 131 */ _POWER_CUT_GROUP_HDMI_ON_CUT,
    /* 132 */ _POWER_CUT_GROUP_RX1_TO_RX3_HDMI21_APHY,
    /* 133 */ _POWER_CUT_GROUP_BB_U2_HOST_MAC,
}EnumPowerGroup;

//--------------------------------------------------
// Clock Gating Group
//--------------------------------------------------
typedef enum
{
    _CLOCK_GATING_GROUP_IR,
    _CLOCK_GATING_GROUP_UART,
    _CLOCK_GATING_GROUP_SPI_0_MASTER,
    _CLOCK_GATING_GROUP_SPI_1_MASTER,
    _CLOCK_GATING_GROUP_SPI_2_MASTER,
    _CLOCK_GATING_GROUP_TYPE_C_TCPM,
    _CLOCK_GATING_GROUP_TRNG,
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
    _OTPMEMORY_AUDIO_CORNER_CONFIG,
    _OTPMEMORY_PIN60_PIN61_1M_TRIMDATA,
    _OTPMEMORY_PACKAGE_TYPE,
    _OTPMEMORY_DDCCI_I_SLAVE_ADDR,
    _OTPMEMORY_DDCCI_II_SLAVE_ADDR,
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
    _DBUS_TV_SB2_C01_FRC_CAP_M1 = _DBUS_SB_CLIENT_BEGIN,
    _DBUS_TV_SB2_C04_FRC_DISP_M1,
    _DBUS_TV_SB2_C05_GOSD_1_R,
    _DBUS_TV_SB2_C06_GOSD_2_R,
    _DBUS_TV_SB2_C07_FRC_DISP_S1,
    _DBUS_TV_SB2_C08_GOSD_3_R,
    _DBUS_TV_SB2_C09_FRC_CAP_S1,
    _DBUS_TV_SB2_C11_OD_M1_W,
    _DBUS_TV_SB2_C13_OD_M1_R,
    //----------System Bridge Clients----------
    _DBUS_SB_CLIENT_END,
} EnumMemoryClient;

typedef enum
{
    _MEM_CLIENT_FRC_CAP,
    _MEM_CLIENT_FRC_DISP,
    _MEM_CLIENT_OD_W,
    _MEM_CLIENT_OD_R,
    _MEM_CLIENT_GOSD_F,
    _MEM_CLIENT_GOSE_SE,
} EnumMemoryClientType;
