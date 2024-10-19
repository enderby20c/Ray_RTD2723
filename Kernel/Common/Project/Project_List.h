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
// ID Code      : Project_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_LIST_H__
#define __PROJECT_LIST_H__

//--------------------------------------------------
//  Project Define
//--------------------------------------------------
#define _RL6829_PROJECT                                   8
#define _RL6952_PROJECT                                   9
#define _RL6978_PROJECT                                   10

//---------------------------------------------------------
// OSD Type
//---------------------------------------------------------
#define _NONE_OSD                                         0
#define _REALTEK_2020_OSD                                 1

//--------------------------------------------------
//  User Osd Architecture Define
//--------------------------------------------------
#define _USER_OSD_GEN_1                                   0
#define _USER_OSD_GEN_2                                   1
#define _USER_OSD_GEN_3                                   2 // 3 BYTE command
#define _USER_OSD_GEN_4                                   3 // 3, 4 BYTE command

//--------------------------------------------------
//  Gosd FW CPU Mode Define
//--------------------------------------------------
#define _GOSD_FW_TWO_CPU_MODE_1                           0 // TWO CPU & SCPU COPROCESS MODE
#define _GOSD_FW_TWO_CPU_MODE_2                           1 // TWO CPU & SCPU ACTOR MODE
#define _GOSD_FW_ONE_CPU_MODE                             2 // ONE CPU

//--------------------------------------------------
// Definations of YPBPR Auto Color Method
//--------------------------------------------------
#define _YPBPR_AUTO_BY_SOURCE                             0x00
#define _YPBPR_AUTO_BY_FORMULA                            0x01

//--------------------------------------------------
//  DP Bit Rate
//--------------------------------------------------
#define _DP_LINK_SPEED_NONE                               0x00
#define _DP_LOW_SPEED_162MHZ                              0x06
#define _DP_HIGH_SPEED_270MHZ                             0x0A
#define _DP_HIGH_SPEED2_540MHZ                            0x14
#define _DP_HIGH_SPEED3_810MHZ                            0x1E
#define _DP_HIGH_SPEED3_900MHZ                            0x21
#define _DP_ULTRA_SPEED_1000MHZ                           0x25
#define _DP_ULTRA_SPEED_1350MHZ                           0x32
#define _DP_ULTRA_SPEED_2000MHZ                           0x4A

//--------------------------------------------------
//  DP Lane Count
//--------------------------------------------------
#define _DP_LANE_AUTO_MODE                                0
#define _DP_ONE_LANE                                      1
#define _DP_TWO_LANE                                      2
#define _DP_FOUR_LANE                                     4

//--------------------------------------------------
//  DP MST Pxp Main Port Search Style
//--------------------------------------------------
#define _DP_MST_PXP_MAIN_PORT_FIXED                       0
#define _DP_MST_PXP_MAIN_PORT_AUTO                        1

//--------------------------------------------------
// DP DPCD DFP Present (00005h) Set Reference Option
//--------------------------------------------------
#define _DP_MST_CAPABILITY                                0
#define _DP_TX_EXISTENCE                                  1

//--------------------------------------------------
//  DP Tx Clone Path Type
//--------------------------------------------------
#define _DP_TX_CLONE_VESA_STREAM_ONLY                     0
#define _DP_TX_CLONE_BOTH_VESA_STREAM_DSC_PASSTHROUGH     1

//--------------------------------------------------
// DP Tx LTTPR Mode Select
//--------------------------------------------------
#define _DP_TX_LTTPR_NON_LTTPR_MODE                       0x00
#define _DP_TX_LTTPR_TRANSPARENT_MODE                     0x01
#define _DP_TX_LTTPR_NON_TRANSPARENT_MODE                 0x02

//--------------------------------------------------
// DP DRR Get IVF Type
//--------------------------------------------------
#define _DP_DRR_SPD_INFO                                  0
#define _DP_DRR_TABLE_SEARCH                              1

//--------------------------------------------------
// Dfp Edid Change Check Method Type
//--------------------------------------------------
#define _EDID_SHA_CODE                                    0
#define _EDID_RAW_DATA                                    1

//--------------------------------------------------
// Dfp Edid Report Source Method Type
//--------------------------------------------------
#define _BYPASS_RAW_DATA                                  0
#define _BACKUP_DDCRAM_DATA                               1

//--------------------------------------------------
//  TMDS Z0 Option in PS Define
//--------------------------------------------------
#define _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS                0
#define _ALL_CHANNEL_CONNECTED_FOR_CTS                    1

//--------------------------------------------------
// HDMI Free Sync Capability Switch Method
//--------------------------------------------------
#define _EDID_SWITCH_MODE                                 1
#define _MCCS_SWITCH_MODE                                 0

//--------------------------------------------------
// Type C SAR ADC Register Type
//--------------------------------------------------
#define _TYPE_C_ADC_REG_GEN_NULL                          0
#define _TYPE_C_ADC_REG_GEN_1                             1
#define _TYPE_C_ADC_REG_GEN_2                             2

//--------------------------------------------------
//  Type C Version (HW Gen Constrain)
//--------------------------------------------------
#define _TYPE_C_VERSION_NULL                              0x00
#define _TYPE_C_VERSION_1_1                               0x01
#define _TYPE_C_VERSION_1_2                               0x02 // RL6492 / RL6561
#define _TYPE_C_VERSION_1_3                               0x03 // RL6629
#define _TYPE_C_VERSION_2_0                               0x20 // RLE1039

//--------------------------------------------------
//  Power Delivery Version (HW Gen Constrain)
//--------------------------------------------------
#define _PD_VERSION_NULL                                  0x00
#define _PD_VERSION_2_0                                   0x01
#define _PD_VERSION_3_0                                   0x02
#define _PD_VERSION_3_1                                   0x03

//--------------------------------------------------
//  Type C Function Gen (HW Gen Constrain)
//--------------------------------------------------
#define _TYPE_C_FUNCTION_GEN_NULL                         0x00
#define _TYPE_C_FUNCTION_GEN_1                            0x01 // RL6492 / RL6478
#define _TYPE_C_FUNCTION_GEN_2                            0x02 // RL6561 / RL6573
#define _TYPE_C_FUNCTION_GEN_3                            0x03 // RL6629
#define _TYPE_C_FUNCTION_GEN_4                            0x04 // RL6828 / RL6829
#define _TYPE_C_FUNCTION_GEN_5                            0x05 // RLE1108 / RLE1109
#define _TYPE_C_FUNCTION_GEN_6                            0x06 // RL6952

//--------------------------------------------------
//  PD Function Gen (HW Gen Constrain)
//--------------------------------------------------
#define _PD_FUNCTION_GEN_NULL                             0x00
#define _PD_FUNCTION_GEN_1                                0x01 // RL6829 and Old IC
#define _PD_FUNCTION_GEN_2                                0x02 // RLE1108/RL6952 and New IC

//--------------------------------------------------
//  Type C 10-BIT SARADC Version (HW Gen Constrain)
//--------------------------------------------------
#define _TYPE_C_10_BIT_SARADC_GEN_0                       0x00
#define _TYPE_C_10_BIT_SARADC_GEN_1                       0x01
#define _TYPE_C_10_BIT_SARADC_NONE                        0xFF

//--------------------------------------------------
//  Type C LS_ADC Version (HW Gen Constrain)
//--------------------------------------------------
#define _TYPE_C_5B_LS_ADC_NONE                            0x00
#define _TYPE_C_5B_LS_ADC_GEN_1                           0x01 // [5Bit LS_ADC Vbus Signal Bug]: CC FSM Will Detect Vbus Off Unexpectedly and Transit to Unattached.SNK from Attached.SNK under RL6828 Ver.A 56pin Sink Only 5V Application.

//--------------------------------------------------
//  Type C Port SRC Default Current Provide
//--------------------------------------------------
#define _TYPE_C_SELF_POWER_ONLY                           0x00     // System Need Adaptor
#define _TYPE_C_VBUS_POWER_ONLY                           0x01     // System Has No Adaptor, Power From Vbus Only
#define _TYPE_C_SELF_AND_VBUS_POWER                       0x02     // System Works From Both Adaptor and Vbus Power

//--------------------------------------------------
//  Type C RTS Port Controller FW Spec Version
//--------------------------------------------------
#define _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D4               4 // Mapping to spec version v0.4
#define _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D5               5 // Mapping to spec version v0.5
#define _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D6               6 // Mapping to spec version v0.6
#define _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D7               7 // Mapping to spec version v0.7
#define _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D8               8 // Mapping to spec version v0.8
#define _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D9               9 // Mapping to spec version v0.9

//--------------------------------------------------
//  Type C RTS Port Controller Status Polling Time
//--------------------------------------------------
#define _PORT_CTRL_RTS_STATUS_POLLING_TIME_500MS          500 // (ms)
#define _PORT_CTRL_RTS_STATUS_POLLING_TIME_1000MS         1000 // (ms)
#define _PORT_CTRL_RTS_STATUS_POLLING_TIME_1500MS         1500 // (ms)
#define _PORT_CTRL_RTS_STATUS_POLLING_TIME_2000MS         2000 // (ms)

//--------------------------------------------------
//  Type C RTS Port Controller SMBus Mode
//--------------------------------------------------
#define _PORT_CTRL_RTS_POLLING_MODE                       0x00
#define _PORT_CTRL_RTS_INT_MODE                           0x01

//--------------------------------------------------
//  Type C DRP Port Power Role Preference
//--------------------------------------------------
#define _TYPE_C_DRP_NO_PREFERENCE                         0x00
#define _TYPE_C_DRP_TRY_SNK                               0x01
#define _TYPE_C_DRP_TRY_SRC                               0x02

//--------------------------------------------------
//  Type C Port SRC Default Current Provide
//--------------------------------------------------
#define _TYPE_C_SRC_DEF_USB                               0x00
#define _TYPE_C_SRC_DEF_1P5A                              0x01
#define _TYPE_C_SRC_DEF_3P0A                              0x02

//--------------------------------------------------
//  Type C Port Accessry Support
//--------------------------------------------------
#define _TYPE_C_ACC_NO_SUPPORT                            0x00
#define _TYPE_C_ACC_POWER                                 0x01
#define _TYPE_C_ACC_AUDIO                                 0x02
#define _TYPE_C_ACC_AUDIO_POWER                           0x03
#define _TYPE_C_ACC_DEBUG                                 0x04
#define _TYPE_C_ACC_DEBUG_POWER                           0x05
#define _TYPE_C_ACC_DEBUG_AUDIO                           0x06
#define _TYPE_C_ACC_ALL                                   0x07

//--------------------------------------------------
//  Type C Vendor Defined Alt Mode List
//--------------------------------------------------
#define _TYPE_C_VENDOR_ALT_MODE_NONE                      0x00
#define _TYPE_C_LENOVO_ALT_MODE                           0x01
#define _TYPE_C_ACER_ALT_MODE                             0x02
#define _TYPE_C_HP_ALT_MODE                               0x03
#define _TYPE_C_DELL_ALT_MODE                             0x04

//--------------------------------------------------
//  Type C Billboard URL INDEX (INDEX Limit at 0x01 - 0x0F)
//--------------------------------------------------
#define _TYPE_C_BILLBOARD_URL_INDEX_DP                    0x01
#define _TYPE_C_BILLBOARD_URL_INDEX_LENOVO                0x02

//--------------------------------------------------
//  Value for Type-C UFP Product Type
//--------------------------------------------------
#define _VALUE_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED          0x00
#define _VALUE_TYPE_C_UFP_PRODUCT_TYPE_HUB                0x01
#define _VALUE_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL         0x02
#define _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT            0xFF

//--------------------------------------------------
//  Type-C Brand Option
//--------------------------------------------------
#define _TYPE_C_EMB_BRAND_NONE                            0x00
#define _TYPE_C_EMB_BRAND_DELL                            0x01

//--------------------------------------------------
//  Type C PMIC OCP/OVP Process Option
//--------------------------------------------------
#define _TYPE_C_PMIC_PROCESS_OPTION_ERROR_RECOVERY        0
#define _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET            1
#define _TYPE_C_PMIC_PROCESS_OPTION_BY_USER               2

//--------------------------------------------------
//  Type C Power Domain Gen Option
//--------------------------------------------------
#define _TYPE_C_POWER_DOMAIN_GEN_1                        0
#define _TYPE_C_POWER_DOMAIN_GEN_2                        1

//--------------------------------------------------
// Arbitration Type Between Hub (54xx) And Scaler Chip List
//--------------------------------------------------
#define _SMBUS_ARBITRATION_NONE                           0
#define _SMBUS_ARBITRATION_DELAY_MODE                     1
#define _SMBUS_ARBITRATION_HANDSHAKE_MODE                 2


//--------------------------------------------------
// USB3 Repeater TYPE Define
//--------------------------------------------------
#define _USB3_REPEATER_NONE                               1
#define _USB3_RETIMER                                     2
#define _USB3_REDRIVER                                    3

//--------------------------------------------------
// USB3 Repeater UFP PHY Mapping Define
//--------------------------------------------------
#define _USB3_REPEATER_UFP_PHY_0                          0x00
#define _USB3_REPEATER_UFP_PHY_1                          0x01
#define _USB3_REPEATER_UFP_PHY_2                          0x02
#define _USB3_REPEATER_UFP_PHY_NONE                       0xFF

//--------------------------------------------------
// HW USB3 Repeater UFP AD Interface Bit Width
//--------------------------------------------------
#define _UFP_8_BIT                                        0x00
#define _UFP_16_BIT                                       0x01
#define _UFP_32_BIT                                       0x02

//--------------------------------------------------
// USB3 Repeater UFP JFM Clock Define
//--------------------------------------------------
#define _UFP_JFM_CMU                                      0x00
#define _DFP_RX_CMU                                       0x01

//--------------------------------------------------
// USB3 Repeater DFP PHY Mapping Define
//--------------------------------------------------
#define _USB3_REPEATER_DFP_PHY_0                          0x00
#define _USB3_REPEATER_DFP_PHY_1                          0x01
#define _USB3_REPEATER_DFP_PHY_2                          0x02
#define _USB3_REPEATER_DFP_PHY_NONE                       0xFF

//--------------------------------------------------
// USB3 Repeater UFP JFM Clock Define
//--------------------------------------------------
#define _UFP_JFM_CMU                                      0x00
#define _DFP_RX_CMU                                       0x01

//--------------------------------------------------
// USB3 Repeater MAC Mapping Define
//--------------------------------------------------
#define _USB3_REPEATER_MAC_0                              0x00
#define _USB3_REPEATER_MAC_1                              0x01
#define _USB3_REPEATER_MAC_2                              0x02
#define _USB3_REPEATER_MAC_NONE                           0xFF

//--------------------------------------------------
// USB3 Repeater DFP Mux Embedded Define
//--------------------------------------------------
#define _USB3_REPEATER_PHY_DFP_MUX_EMBEDDED               0x00
#define _USB3_REPEATER_PHY_DFP_MUX_NONE                   0xFF

//--------------------------------------------------
// USB3 Repeater DFP Phy Lane Number Define
//--------------------------------------------------
#define _DFP_NONE                                         0x00
#define _DFP_TWO_LANE                                     0x01
#define _DFP_FOUR_LANE                                    0x02

//--------------------------------------------------
// USB2 Host HW SRAM Size Support Define
//--------------------------------------------------
#define _HW_USB2_HOST_SRAM_SIZE_NULL                      0x00
#define _HW_USB2_HOST_SRAM_SIZE_2K                        0x01 // RL6829 and Old IC
#define _HW_USB2_HOST_SRAM_SIZE_3K                        0x02 // RL6952

//--------------------------------------------------
// USB2 Analog Core Power Define
//--------------------------------------------------
#define _USB2_CORE_POWER_FROM_PIN                         0x00 // RL6829 / RL6952 and Old IC
#define _USB2_CORE_POWER_FROM_LDO                         0x01 // RL6978 / RL7017

//--------------------------------------------------
// Definitions of USB Speed
//--------------------------------------------------
#define _USB_SPEED_NOT_SUPPORT                            0x00
#define _USB_SPEED_5G                                     0x01
#define _USB_SPEED_10G                                    0x02

//--------------------------------------------------
// Definitions of USB Lane
//--------------------------------------------------
#define _USB_LANE_NOT_SUPPORT                             0x00
#define _USB_LANE_X1                                      0x01
#define _USB_LANE_X2                                      0x02

//--------------------------------------------------
//  Interface RDC Test Type
//--------------------------------------------------
#define _USB3_REDRIVER_RDC_TEST_TYPE                      0x0A
#define _HDMI_RDC_TEST_TYPE_1_4                           0x14
#define _HDMI_RDC_TEST_TYPE_2_0                           0x20
#define _HDMI_RDC_TEST_TYPE_2_1                           0x21
#define _HDMI_RDC_TEST_TYPE_NONE                          0xFF

//--------------------------------------------------
//  HDMI Link Rate
//--------------------------------------------------
#define _HDMI_LINK_SPEED_NONE                             0
#define _HDMI_LINK_SPEED_225MHZ                           1
#define _HDMI_LINK_SPEED_300MHZ                           2
#define _HDMI_LINK_SPEED_340MHZ                           3
#define _HDMI_LINK_SPEED_600MHZ                           4
#define _HDMI_LINK_SPEED_800MHZ                           5
#define _HDMI_LINK_SPEED_1000MHZ                          6
#define _HDMI_LINK_SPEED_1200MHZ                          7

//--------------------------------------------------
//  HDMI Lane Count
//--------------------------------------------------
#define _HDMI_LANE_AUTO_MODE                              0
#define _HDMI_ONE_LANE                                    1
#define _HDMI_TWO_LANE                                    2
#define _HDMI_THREE_LANE                                  3
#define _HDMI_FOUR_LANE                                   4

//--------------------------------------------------
//  HDMI Version Define
//--------------------------------------------------
#define _HDMI_VERSION_NULL                                0x00
#define _HDMI_VERSION_1_4                                 0x14
#define _HDMI_VERSION_2_0                                 0x20
#define _HDMI_VERSION_2_1                                 0x21

//--------------------------------------------------
//  HDMI MAC Type
//--------------------------------------------------
#define _HDMI_MAC_NONE                                    0
#define _HDMI_MAC_TMDS                                    1
#define _HDMI_MAC_TMDS_FRL                                2

//--------------------------------------------------
// Definitions of eCBUS-S Sync Lost Solution
//--------------------------------------------------
#define _ECBUS_SYNC_LOST_REINIT                           0
#define _ECBUS_SYNC_LOST_RETRY                            1

//--------------------------------------------------
//  HDCP Feature Define
//--------------------------------------------------
#define _HDCP_FEATURE_1_0                                 0
#define _HDCP_FEATURE_1_1                                 1
#define _HDCP_FEATURE_2_2                                 2
#define _HDCP_FEATURE_BY_INPUT                            3

//--------------------------------------------------
//  Audio TTS Support Type Options
//--------------------------------------------------
#define _AUDIO_TTS_NOT_SUPPORT                            0
#define _AUDIO_TTS_EXTERNAL_DEVICE                        1
#define _AUDIO_TTS_EMBEDDED_TYPE                          2

//--------------------------------------------------
//  Audio TTS Content Bit Format Options
//--------------------------------------------------
#define _AUDIO_TTS_CONTENT_8_BIT                          0
#define _AUDIO_TTS_CONTENT_16_BIT                         1

//--------------------------------------------------
//  Audio TTS Content Frequency Options
//--------------------------------------------------
#define _AUDIO_TTS_CONTENT_8_KHZ                          8
#define _AUDIO_TTS_CONTENT_16_KHZ                         16

//--------------------------------------------------
//  Audio ARC Tx Support Type Options
//--------------------------------------------------
#define _AUDIO_ARC_TX_NOT_SUPPORT                         0
#define _AUDIO_ARC_TX_EXTERNAL_DEVICE                     1
#define _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP                2
#define _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD   3

//--------------------------------------------------
//  Audio ARC Tx High Level Behavior FW Type Options
//--------------------------------------------------
#define _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST                0
#define _ARC_TX_HIGH_LEVEL_FW_TYPE_USER                   1

//--------------------------------------------------
//  Audio Options
//--------------------------------------------------
#define _PS_AUDIO_DP                                      0
#define _PS_AUDIO_LINE_IN                                 1
#define _PS_AUDIO_BOTH                                    2

//--------------------------------------------------
// Audio DAC Dither Level
//--------------------------------------------------
#define _AUDIO_DAC_DITHER_LEVEL_OFF                       0
#define _AUDIO_DAC_DITHER_LEVEL_1                         1
#define _AUDIO_DAC_DITHER_LEVEL_2                         2
#define _AUDIO_DAC_DITHER_LEVEL_3                         3
#define _AUDIO_DAC_DITHER_LEVEL_4                         4
#define _AUDIO_DAC_DITHER_LEVEL_5                         5
#define _AUDIO_DAC_DITHER_LEVEL_6                         6

//--------------------------------------------------
//  Audio DVC Mode Options
//--------------------------------------------------
#define _DB_GAIN                                          0
#define _VOLUME_STEP_SIZE                                 1

//--------------------------------------------------
//  Audio DVC DB Mode Options
//--------------------------------------------------
#define _DB_GAIN_1_DB                                     0
#define _DB_GAIN_1_2_DB                                   1
#define _DB_GAIN_1_4_DB                                   2
#define _DB_GAIN_1_8_DB                                   3

//--------------------------------------------------
//  Audio Manual Sampling Frequency Options
//--------------------------------------------------
#define _FIX_FREQ_32KHZ                                   0
#define _FIX_FREQ_44_1KHZ                                 1
#define _FIX_FREQ_48KHZ                                   2

//--------------------------------------------------
//  Audio Hard Gain Options
//--------------------------------------------------
#define _HARD_GAIN_0_DB                                   0
#define _HARD_GAIN_ADD_6_DB                               1
#define _HARD_GAIN_ADD_12_DB                              2
#define _HARD_GAIN_ADD_18_DB                              3
#define _HARD_GAIN_ADD_24_DB                              4
#define _HARD_GAIN_MINUS_6_DB                             5
#define _HARD_GAIN_MINUS_12_DB                            6
#define _HARD_GAIN_MINUS_18_DB                            7
#define _HARD_GAIN_MINUS_24_DB                            8

//--------------------------------------------------
// Definitions of Momory Type
//--------------------------------------------------
#define _EXTERNAL_MEMORY                                  0
#define _EMBEDDED_MEMORY                                  1

//------------------------------------------------
//  Memory Density Options
//------------------------------------------------
#define _MEMORY_DENSITY_MASK                              0x0F00
#define _MEMORY_DENSITY_1M_16                             0x0000 // 16 Mb
#define _MEMORY_DENSITY_4M_16                             0x0200 // 64 Mb
#define _MEMORY_DENSITY_16M_16                            0x0400 // 256 Mb
#define _MEMORY_DENSITY_64M_16                            0x0600 // 1 Gb
#define _MEMORY_DENSITY_128M_16                           0x0700 // 2 Gb
#define _MEMORY_DENSITY_256M_16                           0x0800 // 4 Gb

//------------------------------------------------
//  Memory Number Options
//------------------------------------------------
#define _MEMORY_NUM_MASK                                  0x00F0
#define _MEMORY_1PC                                       0x0000
#define _MEMORY_2PCS                                      0x0010

//------------------------------------------------
//  Memory Type Options
//------------------------------------------------
#define _MEMORY_TYPE_CONFIG_MASK                          0x000F
#define _NO_MEMORY                                        0x0000
#define _MEMORY_SDRAM                                     0x0001
#define _MEMORY_DDR1                                      0x0002
#define _MEMORY_DDR2                                      0x0003
#define _MEMORY_DDR3                                      0x0004

//------------------------------------------------
//  DDR3 Power Type Options
//------------------------------------------------
#define _MEMORY_TYPE_POWWER_CONFIG_MASK                   0xF000
#define _MEMORY_POWER_NORMAL                              0x0000  // DDR3 = 1.5V
#define _MEMORY_POWER_HIGH                                0x1000
#define _MEMORY_POWER_LOW                                 0x2000  // LPDDR3 = 1.35V

//------------------------------------------------
// Embedded Memory Size Options
//------------------------------------------------
#define _EMBEDDED_MEMORY_SIZE_NONE                        _NO_MEMORY
#define _1M_16BIT_SDRAM                                   (_MEMORY_DENSITY_1M_16 | _MEMORY_1PC | _MEMORY_SDRAM)
#define _4M_16BIT_DDR1_1PC                                (_MEMORY_DENSITY_4M_16 | _MEMORY_1PC | _MEMORY_DDR1)
#define _4M_16BIT_DDR1_2PCS                               (_MEMORY_DENSITY_4M_16 | _MEMORY_2PCS | _MEMORY_DDR1)
#define _16M_16BIT_DDR2_1PC                               (_MEMORY_DENSITY_16M_16 | _MEMORY_1PC | _MEMORY_DDR2)
#define _16M_16BIT_DDR2_2PCS                              (_MEMORY_DENSITY_16M_16 | _MEMORY_2PCS | _MEMORY_DDR2)
#define _1G_16BIT_DDR3_1PC_NORMAL                         (_MEMORY_DENSITY_64M_16 | _MEMORY_1PC | _MEMORY_DDR3 | _MEMORY_POWER_NORMAL)
#define _1G_16BIT_DDR3_2PCS_NORMAL                        (_MEMORY_DENSITY_64M_16 | _MEMORY_2PCS | _MEMORY_DDR3 | _MEMORY_POWER_NORMAL)

//------------------------------------------------
// Memory Speed
//------------------------------------------------
#define _MEMORY_SPEED_100MHZ                              100U
#define _MEMORY_SPEED_120MHZ                              120U
#define _MEMORY_SPEED_166MHZ                              166U
#define _MEMORY_SPEED_195MHZ                              195U
#define _MEMORY_SPEED_198MHZ                              198U
#define _MEMORY_SPEED_200MHZ                              200U
#define _MEMORY_SPEED_215MHZ                              215U
#define _MEMORY_SPEED_220MHZ                              220U
#define _MEMORY_SPEED_222MHZ                              222U
#define _MEMORY_SPEED_250MHZ                              250U
#define _MEMORY_SPEED_333MHZ                              333U
#define _MEMORY_SPEED_400MHZ                              400U
#define _MEMORY_SPEED_533MHZ                              533U
#define _MEMORY_SPEED_600MHZ                              600U
#define _MEMORY_SPEED_667MHZ                              667U
#define _MEMORY_SPEED_720MHZ                              720U
#define _MEMORY_SPEED_800MHZ                              800U
#define _MEMORY_SPEED_933MHZ                              933U
#define _MEMORY_SPEED_1066MHZ                             1066U

//--------------------------------------------------
// DDR3 PLL SSC Amplitude
//--------------------------------------------------
#define _0_5_PERCENT                                      0 // RL6829
#define _1_PERCENT                                        1 // RL6829, RL6952, RL6978
#define _2_PERCENT                                        2 // RL6952, RL6978

//--------------------------------------------------
// Memory Size
//--------------------------------------------------
#define _MEMORY_16MB                                      16U
#define _MEMORY_32MB                                      32U
#define _MEMORY_64MB                                      64U
#define _MEMORY_128MB                                     128U
#define _MEMORY_256MB                                     256U
#define _MEMORY_512MB                                     512U
#define _MEMORY_1GB                                       1024U
#define _MEMORY_2GB                                       2048U
#define _MEMORY_4GB                                       4096U

//--------------------------------------------------
// Option for Memory Allocation
//--------------------------------------------------
#define _DOMINATED_BY_BW                                  0
#define _DOMINATED_BY_SPACE                               1

//--------------------------------------------------
// Definitions of D Domain Data Path
//--------------------------------------------------
#define _D_DOMAIN_1_PATH                                  0
#define _D_DOMAIN_2_PATH                                  1
#define _D_DOMAIN_4_PATH                                  2

//--------------------------------------------------
// DPLL Jitter Margin
//--------------------------------------------------
#define _DPLL_NO_JITTER_MARGIN                            0
#define _DPLL_1_PERCENT_JITTER_MARGIN                     1

//--------------------------------------------------
// CLUT Location Option List
//--------------------------------------------------
#define _GAMMA_LUT_LOCATION_CODE                          0
#define _GAMMA_LUT_LOCATION_FLASH                         1

//--------------------------------------------------
// Calibration Type
//--------------------------------------------------
#define _TWO_BRI_CALIBRATION_NONE                         0
#define _TWO_BRI_CALIBRATION_DICOM_HDR                    1
#define _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR            2
#define _MULTI_BRI_CALIBRATION_OGC_OCC                    3

//--------------------------------------------------
// Local Dimming Compensate Type
//--------------------------------------------------
#define _LD_COMPENSATE_NONE                               0
#define _LD_COMPENSATE_ADIM                               1
#define _LD_COMPENSATE_DDIM                               2

//--------------------------------------------------
// Multi Brightness Calibration Options
//--------------------------------------------------
#define _MULTI_BRI_CALIBRATION_NONE                       0
#define _MULTI_BRI_THREE_CALIBRATION                      1
#define _MULTI_BRI_FOUR_CALIBRATION                       2

//--------------------------------------------------
// Six Color ICM TYPE
//--------------------------------------------------
#define _SIX_COLOR_ICM_NORMAL_MODE                        0
#define _SIX_COLOR_ICM_BRI_COMPENSATE_MODE                1

//--------------------------------------------------
// Definations of Clock Save Value
//--------------------------------------------------
#define _CLOCK_SAVE_PERCENT_VALUE                         0
#define _CLOCK_SAVE_REAL_VALUE                            1

//--------------------------------------------------
// Definitions of Auto Search Style
//--------------------------------------------------
#define _SOURCE_POLLING_IN_SEARCH_STATE                   0
#define _SOURCE_POLLING_AFTER_NOSIGNAL_STATE              1
#define _SOURCE_POLLING_ACER_STYLE                        2
#define _SOURCE_POLLING_ASUS_STYLE                        3
#define _SOURCE_POLLING_DELL_STYLE                        4
#define _SOURCE_POLLING_EIZO_STYLE                        5
#define _SOURCE_POLLING_FUJITSU_STYLE                     6

//--------------------------------------------------
// Option for Display Garbage Prevent
//--------------------------------------------------
#define _GARBAGE_PREVENT_BY_WATCH_DOG                     0
#define _GARBAGE_PREVENT_BY_BACKLIGHT                     1
#define _GARBAGE_PREVENT_BY_IRQ_BACKGROUND                2

//--------------------------------------------------
// Option for SPD Info FreeSync Enable Reference
//--------------------------------------------------
#define _REF_DRR_GET_TYPE                                 0
#define _REF_SPD_INFO_ENABLE                              1

//--------------------------------------------------
// IRDA receiver type
//--------------------------------------------------
#define _IR_OFF                                           0
#define _IR_HW_SUPPORT                                    1
#define _IR_SW_SUPPORT                                    2

//--------------------------------------------------
// Table Location Option List
//--------------------------------------------------
#define _TABLE_LOCATION_CODE                              0
#define _TABLE_LOCATION_SYSTEM_EEPROM                     1
#define _TABLE_LOCATION_FLASH                             2
#define _TABLE_LOCATION_OTPMEMORY                         3
#define _TABLE_LOCATION_USER                              4
#define _TABLE_LOCATION_IROM                              5

//-------------------------------------------------
// Definitions of Flash Partition
//-------------------------------------------------
#define _FLASH_PARTITION_NONE                             0
#define _FLASH_PARTITION_BOOT                             1
#define _FLASH_PARTITION_USER                             2
#define _FLASH_PARTITION_BOTH                             3

//-------------------------------------------------
// Definitions of Flash Read Mode
//-------------------------------------------------
#define _FLASH_FAST_READ                                  0
#define _FLASH_DUAL_READ                                  1

//--------------------------------------------------
//  Flash Clock Speed Option List
//--------------------------------------------------
#define _FLASH_LOW_SPEED                                  0
#define _FLASH_FAST_SPEED                                 1

//--------------------------------------------------
//  Flash Complement Protect Area
//--------------------------------------------------
#define _FLASH_TOP_PROTECT                                0
#define _FLASH_BOTTOM_PROTECT                             1

//--------------------------------------------------
// Definitions of System Eeprom Emulation Page ID
//--------------------------------------------------
#define _PAGEID_0                                         0
#define _PAGEID_1                                         1
#define _PAGEID_2                                         2
#define _PAGEID_3                                         3
#define _PAGEID_4                                         4

//--------------------------------------------------
// Eeprom address Range
//--------------------------------------------------
#define _EEPROM_SIZE_RANGE_BYTE                           0xFF
#define _EEPROM_SIZE_RANGE_WORD                           0xFFFF
#define _EEPROM_SIZE_RANGE_DWORD                          0xFFFFFFFF

//--------------------------------------------------
// Eeprom Page address
//--------------------------------------------------
#define _EEPROM_PAGE0_BANK0                               0
#define _EEPROM_PAGE0_BANK1                               128
#define _EEPROM_PAGE1_BANK0                               256
#define _EEPROM_PAGE1_BANK1                               384
#define _EEPROM_PAGE2_BANK0                               512
#define _EEPROM_PAGE2_BANK1                               640
#define _EEPROM_PAGE3_BANK0                               768
#define _EEPROM_PAGE3_BANK1                               896
#define _EEPROM_PAGE4_BANK0                               1024
#define _EEPROM_PAGE4_BANK1                               1152
#define _EEPROM_PAGE5_BANK0                               1280
#define _EEPROM_PAGE5_BANK1                               1408
#define _EEPROM_PAGE6_BANK0                               1536
#define _EEPROM_PAGE6_BANK1                               1664
#define _EEPROM_PAGE7_BANK0                               1792
#define _EEPROM_PAGE7_BANK1                               1920
#define _EEPROM_PAGE8_BANK0                               2048
#define _EEPROM_PAGE8_BANK1                               2176
#define _EEPROM_PAGE9_BANK0                               2304
#define _EEPROM_PAGE9_BANK1                               2432
#define _EEPROM_PAGEA_BANK0                               2560
#define _EEPROM_PAGEA_BANK1                               2688
#define _EEPROM_PAGEB_BANK0                               2816
#define _EEPROM_PAGEB_BANK1                               2944
#define _EEPROM_PAGEC_BANK0                               3072
#define _EEPROM_PAGEC_BANK1                               3200
#define _EEPROM_PAGED_BANK0                               3328
#define _EEPROM_PAGED_BANK1                               3456
#define _EEPROM_PAGEE_BANK0                               3584
#define _EEPROM_PAGEE_BANK1                               3712
#define _EEPROM_PAGEF_BANK0                               3840
#define _EEPROM_PAGEF_BANK1                               3968
#define _EEPROM_PAGE10_BANK0                              4096
#define _EEPROM_PAGE10_BANK1                              4224
#define _EEPROM_PAGE11_BANK0                              4352
#define _EEPROM_PAGE11_BANK1                              4480
#define _EEPROM_PAGE12_BANK0                              4608
#define _EEPROM_PAGE12_BANK1                              4736
#define _EEPROM_PAGE13_BANK0                              4864
#define _EEPROM_PAGE13_BANK1                              4992
#define _EEPROM_PAGE14_BANK0                              5120
#define _EEPROM_PAGE14_BANK1                              5248
#define _EEPROM_PAGE15_BANK0                              5376
#define _EEPROM_PAGE15_BANK1                              5504
#define _EEPROM_PAGE16_BANK0                              5632
#define _EEPROM_PAGE16_BANK1                              5760
#define _EEPROM_PAGE17_BANK0                              5888
#define _EEPROM_PAGE17_BANK1                              6016
#define _EEPROM_PAGE18_BANK0                              6144
#define _EEPROM_PAGE18_BANK1                              6272
#define _EEPROM_PAGE19_BANK0                              6400
#define _EEPROM_PAGE19_BANK1                              6528
#define _EEPROM_PAGE1A_BANK0                              6656
#define _EEPROM_PAGE1A_BANK1                              6784
#define _EEPROM_PAGE1B_BANK0                              6912
#define _EEPROM_PAGE1B_BANK1                              7040
#define _EEPROM_PAGE1C_BANK0                              7168
#define _EEPROM_PAGE1C_BANK1                              7296
#define _EEPROM_PAGE1D_BANK0                              7424
#define _EEPROM_PAGE1D_BANK1                              7552
#define _EEPROM_PAGE1E_BANK0                              7680
#define _EEPROM_PAGE1E_BANK1                              7808
#define _EEPROM_PAGE1F_BANK0                              7936
#define _EEPROM_PAGE1F_BANK1                              8064

//--------------------------------------------------
// Panel Uniformity Level Correction Selection
//--------------------------------------------------
#define _UNIFORMITY_NONE                                  0
#define _UNIFORMITY_1LEVEL                                1
#define _UNIFORMITY_4LEVEL                                4
#define _UNIFORMITY_5LEVEL                                5

//--------------------------------------------------
// Definitions of Color Depth
//--------------------------------------------------
#define _COLOR_DEPTH_NONE                                 0
#define _COLOR_DEPTH_6_BITS                               6
#define _COLOR_DEPTH_7_BITS                               7
#define _COLOR_DEPTH_8_BITS                               8
#define _COLOR_DEPTH_10_BITS                              10
#define _COLOR_DEPTH_12_BITS                              12
#define _COLOR_DEPTH_14_BITS                              14
#define _COLOR_DEPTH_16_BITS                              16

//--------------------------------------------------
// Source of SPI Setting
//--------------------------------------------------
#define _SPI_SETTING_BY_PROJECT                           0
#define _SPI_SETTING_BY_PANEL                             1
#define _SPI_SETTING_BY_PCB                               2


//--------------------------------------------------
// MTP PBPLR Performance Type
//--------------------------------------------------
#define _MAIN_EQUAL_TO_SUB                                0
#define _MAIN_BETTER_THAN_SUB                             1


//--------------------------------------------------
// DP IRQ HPD Implementation Mode
//--------------------------------------------------
#define _DP_IRQ_HPD_DELAY_MODE                            0
#define _DP_IRQ_HPD_T2_MODE                               1

//--------------------------------------------------
// DP HDR VENDOR SUPPORT
//--------------------------------------------------
#define _DP_HDR_VENDOR_SUPPORT_NONE                       0
#define _DP_HDR_VENDOR_SUPPORT_INTEL                      1

//--------------------------------------------------
// PIP Sub Reserve BW option
//--------------------------------------------------
#define _SUB_SINGLE_PATH_HW_LIMIT_SPEED                   0
#define _SUB_FHD_60                                       1
#define _SUB_QUARTER_RESOLUTION                           2

//--------------------------------------------------
// Display HDR Version
//--------------------------------------------------
#define _DISPLAY_HDR_VERSION_1_0                          0
#define _DISPLAY_HDR_VERSION_1_1                          1
#define _DISPLAY_HDR_VERSION_1_2                          2

//--------------------------------------------------
// DP Rx Error Check Type
//--------------------------------------------------
#define _DP_RX_ERROR_CHECK_BY_8B10B                       0
#define _DP_RX_ERROR_CHECK_BY_BIST_SEED                   1

//--------------------------------------------------
// DP Long HPD Implementation Mode
//--------------------------------------------------
#define _DP_LONG_HPD_DELAY_MODE                           0
#define _DP_LONG_HPD_TIMEREVENT_MODE                      1
#define _DP_LONG_HPD_DEFAULT_MODE                         2

//--------------------------------------------------
// DP Mac Stream Rx Pixel Mode
//--------------------------------------------------
#define _DP_MAC_STREAM_RX_PIXEL_MODE_NONE                 0
#define _DP_MAC_STREAM_RX_ONE_PIXEL_MODE                  1
#define _DP_MAC_STREAM_RX_TWO_PIXEL_MODE                  2
#define _DP_MAC_STREAM_RX_FOUR_PIXEL_MODE                 4

//--------------------------------------------------
// DP Aux Ref. Clk Select From
//--------------------------------------------------
#define _DP_AUX_REPLY_SEL_IOSC                            0
#define _DP_AUX_REPLY_SEL_SOURCE                          1

//--------------------------------------------------
// DP Aux Aphy Adjr
//--------------------------------------------------
#define _DP_AUX_Z0_94_OHM                                 8

//--------------------------------------------------
// FW build type
//--------------------------------------------------
#define _FW_BUILD_PROJECT                                 0
#define _FW_BUILD_BOOT                                    1
#define _FW_BUILD_DEFAULT                                 2

//--------------------------------------------------
// Dual Bank Type
// _DUAL_BANK_FLASH_PARTITION : Use 5 Byte Check Flag
// _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE : Use 0x55, 0xAA Check Flag
//--------------------------------------------------
#define _DUAL_BANK_FLASH_PARTITION                        0
#define _DUAL_BANK_DIFF_BANK                              1
#define _DUAL_BANK_COPY_BANK                              2
#define _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE         3

//-------------------------------------------------
// Definitions of Flash Partition
// _DUAL_BANK_FLASH_PARTITION_BOOT : Included Bank Switch Check Flow
// _DUAL_BANK_FLASH_PARTITION_USER : Excluded Bank Switch Check Flow
// _DUAL_BANK_FLASH_PARTITION_BOTH : Integrate Bank Switch Check Flow Into User
//-------------------------------------------------
#define _DUAL_BANK_FLASH_PARTITION_BOOT                   1
#define _DUAL_BANK_FLASH_PARTITION_USER                   2
#define _DUAL_BANK_FLASH_PARTITION_BOTH                   3

//--------------------------------------------------
// User Flag Location
//--------------------------------------------------
#define _DUAL_BANK_FLAG_LOCATION_IN_BOOT                  0
#define _DUAL_BANK_FLAG_LOCATION_IN_USER                  1
#define _DUAL_BANK_FLAG_LOCATION_IN_NONE_FW               2

//--------------------------------------------------
// User Flag Layout
//--------------------------------------------------
#define _DUAL_BANK_ONE_SECTOR                             0
#define _DUAL_BANK_DIFFER_SECTOR                          1

//--------------------------------------------------
// User Flag Customer Type
//--------------------------------------------------
#define _DUAL_BANK_KERNEL_TYPE                            0
#define _DUAL_BANK_USER_TYPE                              1

//--------------------------------------------------
// Digital Signature Type
//--------------------------------------------------
#define _DIGITAL_SIGNATURE_NONE                           0
#define _DIGITAL_SIGNATURE_HW                             1
#define _DIGITAL_SIGNATURE_SW                             2

//--------------------------------------------------
// Digital Signature RSA Support Mode
//--------------------------------------------------
#define _DIGITAL_SIGNATURE_RSA_512                        512
#define _DIGITAL_SIGNATURE_RSA_1024                       1024
#define _DIGITAL_SIGNATURE_RSA_2048                       2048
#define _DIGITAL_SIGNATURE_RSA_3072                       3072

//--------------------------------------------------
// Advanced HDR10 HDMI Support Type
//--------------------------------------------------
#define _ADVANCED_HDR10_NONE                              0
#define _ADVANCED_HDR10_VSIF_MODE                         1
#define _ADVANCED_HDR10_VSIF_AND_DHDR_MODE                2

//--------------------------------------------------
// Fw Update Check Mode
//--------------------------------------------------
#define _FW_UPDATE_CHECK_NONE                             0
#define _FW_UPDATE_CHECK_RTK_RSA2048                      1
#define _FW_UPDATE_CHECK_PASSWORD                         2
#define _FW_UPDATE_CHECK_RTK_RSA3072                      3

//--------------------------------------------------
// Foreground Fw Update Exit Mode
//--------------------------------------------------
#define _FW_UPDATE_FOREGROUND_RESET                       0
#define _FW_UPDATE_FOREGROUND_RESTORE_SCENE               1

//--------------------------------------------------
// Fw Update calculate CRC Type
//--------------------------------------------------
#define _FW_UPDATE_FW_CLAC_CRC                            0
#define _FW_UPDATE_HW_CLAC_CRC                            1

//--------------------------------------------------
// Fw Update DDCCI Select
//--------------------------------------------------
#define _FW_UPDATE_SEL_DDCCI0                             0
#define _FW_UPDATE_SEL_DDCCI1                             1
#define _FW_UPDATE_SEL_DDCCI2                             2
#define _FW_UPDATE_SEL_DDCCI3                             3
#define _FW_UPDATE_SEL_DDCCI4                             4

//-------------------------------------------------
// DP Tx Source Switch Mode
//-------------------------------------------------
#define _DP_TX_SOURCE_FIXED_PORT                          0
#define _DP_TX_SOURCE_AUTO                                1

//--------------------------------------------------
// HW MCU IIC Type
//--------------------------------------------------
#define _HW_IIC_GEN_0                                     0 // For Old IC
#define _HW_IIC_GEN_1                                     1 // For RL6829
#define _HW_IIC_GEN_2                                     2 // For RL6952, RL6978

//--------------------------------------------------
// Motion Blur Reduction Method
//--------------------------------------------------
#define _MOTION_BLUR_PANEL_PIXEL_LCD                      0
#define _MOTION_BLUR_PANEL_PIXEL_OLED                     1

//--------------------------------------------------
//  SCPU Firmware Mode
//--------------------------------------------------
#define _SCPU_FW_MODE_COPROCESSOR                         0
#define _SCPU_FW_MODE_ACTOR                               1

//--------------------------------------------------
//  DM Picture Mode
//--------------------------------------------------
#define _DM_PICTURE_MODE_0                                0
#define _DM_PICTURE_MODE_1                                1
#define _DM_PICTURE_MODE_2                                2
#define _DM_PICTURE_MODE_3                                3
#define _DM_PICTURE_MODE_NONE                             0xFF

//--------------------------------------------------
//  DM Mute Mode
//--------------------------------------------------
#define _DM_MUTE_D_DEN_STOP                               0
#define _DM_MUTE_I_DEN_START                              1


#endif // End of #ifndef __PROJECT_LIST_H__
