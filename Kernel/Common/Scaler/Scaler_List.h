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
// ID Code      : Scaler_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_LIST_H__
#define __SCALER_LIST_H__

//--------------------------------------------------
// Scaler Type List
//--------------------------------------------------
#define _RL6829_SERIES                                    9
#define _RL6952_SERIES                                    10
#define _RL6978_SERIES                                    11

//--------------------------------------------------
//  RLxxxx Gen None Define
//--------------------------------------------------
#define _GEN_NONE                                         0xFF

//--------------------------------------------------
//  RLxxxx Input Port None Define
//--------------------------------------------------
#define _INPUT_NONE                                       0

//--------------------------------------------------
// ADCNR Type
//--------------------------------------------------
#define _ADCNR_GEN_0                                      0
#define _ADCNR_GEN_1                                      1

//--------------------------------------------------
// Digital Filter Type
//--------------------------------------------------
#define _DIGITAL_FILTER_GEN_0                             0

//--------------------------------------------------
// Ringing Filter Type
//--------------------------------------------------
#define _RINGING_FILTER_GEN_0                             0

//--------------------------------------------------
// Define DP Aux Reply Timeout for I2C_over_aux
//--------------------------------------------------
#define _DP_AUX_I2C_REPLY_TIMEOUT_SETTING                 0x0D

//--------------------------------------------------
// Define DP Aux Rx Mac Dpcd Access Type
//--------------------------------------------------
#define _DP_AUX_RX_MAC_DPCD_ACCESS_NORMAL                 0
#define _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY              1

//--------------------------------------------------
// Define DP Aux Single End Gen
//--------------------------------------------------
#define _DP_AUX_SINGLE_END_ONLY                           0
#define _DP_AUX_SINGLE_END_COMBO_RX2                      1
#define _DP_AUX_SINGLE_END_NONE                           2

//--------------------------------------------------
// Define DP Aux Rx3 Gen
//--------------------------------------------------
#define _DP_AUX_RX_ONLY                                   0
#define _DP_AUX_RX_WITH_AUTO_CALIBRATION                  1

//--------------------------------------------------
// Define DP Aux Auto Calibration Gen
//--------------------------------------------------
#define _DP_AUX_AUTO_CALIBRATION_NONE                     0
#define _DP_AUX_AUTO_CALIBRATION_NORMAL                   1
#define _DP_AUX_AUTO_CALIBRATION_PN_INVERSE               2

//--------------------------------------------------
// Define DP Aux Aphy PN Swap Gen
//--------------------------------------------------
#define _DP_AUX_APHY_PN_SWAP_RXTX_COMBO                   0
#define _DP_AUX_APHY_PN_SWAP_RXTX_SEPARATE                1

//--------------------------------------------------
//  DP MST Stream Count
//--------------------------------------------------
#define _DP_MST_STREAM_NONE                               0
#define _DP_MST_3_STREAM                                  3
#define _DP_MST_4_STREAM                                  4
#define _DP_MST_5_STREAM                                  5
#define _DP_MST_6_STREAM                                  6
#define _DP_MST_8_STREAM                                  8

//--------------------------------------------------
//  Dual DP Mac DPHY Use Define
//--------------------------------------------------
#define _DUAL_DP_MAC_DPHY_NONE                            0
#define _DUAL_DP_MAC_DPHY_RX0RX1                          1
#define _DUAL_DP_MAC_DPHY_RX1RX2                          2
#define _DUAL_DP_MAC_DPHY_ALL                             3

//--------------------------------------------------
//  Dual DP Mac Use Define
//--------------------------------------------------
#define _DUAL_DP_MAC_NONE                                 0
#define _DUAL_DP_MAC_RX0RX1                               1
#define _DUAL_DP_MAC_RX1RX2                               2
#define _DUAL_DP_MAC_ALL                                  3

//--------------------------------------------------
//  DP Mac Power Cut Gen Type
//--------------------------------------------------
#define _DP_MAC_POWER_CUT_COMBO                           0
#define _DP_MAC_POWER_CUT_SEPARATE                        1

//--------------------------------------------------
// TMDS PHY Generation
//    - _GEN_1 RL6410 PHY
//    - _GEN_2 RLE1039 PHY
//--------------------------------------------------
#define _HW_PHY_GEN_1                                     0
#define _HW_PHY_GEN_2                                     1

//--------------------------------------------------
//  GDI DFE TYPE Define
//--------------------------------------------------
#define _NONE_DFE                                         0
#define _ADAPTIVE_DFE                                     1
#define _PASSIVE_DFE                                      2

//--------------------------------------------------
// Definitions of DP Rx Decode Check
//--------------------------------------------------
#define _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX               0x00
#define _DP_RX_DECODE_CHECK_AFTER_LANE_MUX                0x01

//--------------------------------------------------
// Definitions of DP Rx Decode Check
//--------------------------------------------------
#define _DP_RX_20_BIT                                     0x00
#define _DP_RX_32_BIT                                     0x01
#define _DP_RX_16_BIT                                     0x02

//--------------------------------------------------
//  HDMI2.0 HW Mode
//--------------------------------------------------
#define _HDMI20_NONE                                      0
#define _HDMI20_D0_D1                                     1
#define _HDMI20_D2_D3_D4_D5                               2
#define _HDMI20_D1_D2_D3                                  3
#define _HDMI20_D2_D3                                     4
#define _HDMI20_D2                                        5
#define _HDMI20_D1_D2                                     6
#define _HDMI20_D3_D4                                     7

//--------------------------------------------------
//  HDMI2.1 HW Mode
//--------------------------------------------------
#define _HDMI_FRL_MAC_NONE                                0
#define _HDMI_FRL_MAC_D3_D4                               1
#define _HDMI_FRL_MAC_D2_D3                               2
#define _HDMI_FRL_MAC_D1_D2_D3                            3

//--------------------------------------------------
// Definitions of HDMI2.1 FRL Rate
//--------------------------------------------------
#define _HDMI_FRL_RATE_NONE                               0
#define _HDMI_FRL_RATE_3G                                 1
#define _HDMI_FRL_RATE_6G_3LANES                          2
#define _HDMI_FRL_RATE_6G_4LANES                          3
#define _HDMI_FRL_RATE_8G                                 4
#define _HDMI_FRL_RATE_10G                                5
#define _HDMI_FRL_RATE_12G                                6

//--------------------------------------------------
//  TMDS Combo MAC Mode
//--------------------------------------------------
#define _TMDS_COMBO_MAC_NONE                              0
#define _TMDS_COMBO_MAC_D1_FROM_D2                        1

//--------------------------------------------------
// TMDS HW Lane Mapping
//--------------------------------------------------
#define _TMDS_LANE_SWAP_NONE                              0
#define _TMDS_LANE0_LANE2_SWAP                            1

//--------------------------------------------------
// Definations of HDMI-CEC HW Type
// NONE: NO CEC HW IP Exist
// Type0: NO "received HB form CEC RX (0x18E3) & "Result of CEC TX sent (0x18B7[7:5])" & "polling msg irq (0x18B2[0])"
// Type1: NO "received HB form CEC RX (0x18E3)..ex. 6561C / 6493F
// Type2: NO "polling msg irq".. ex. 6478/6573 before ECO...
// Type3: Has "received HB form CEC RX (0x18E3) & "Result of CEC TX sent (0x18B7[7:5])" & "polling msg irq (0x18B2[0])"
//--------------------------------------------------
#define _HW_CEC_GEN_NONE                                  0
#define _HW_CEC_GEN_TYPE_0                                1
#define _HW_CEC_GEN_TYPE_1                                2
#define _HW_CEC_GEN_TYPE_2                                3
#define _HW_CEC_GEN_TYPE_3                                4

//--------------------------------------------------
// Definations of HDMI-CEC HW Analog Type
// NONE: NO CEC HW IP Exist
// Type0: reg_cec_cur is 2bit (0x19F2). ex: 6829
// Type1: reg_cec_cur is 3bit (0x19F2). ex: 6952
//--------------------------------------------------
#define _HW_CEC_ANALOG_GEN_NONE                           0
#define _HW_CEC_ANALOG_GEN_TYPE_0                         1
#define _HW_CEC_ANALOG_GEN_TYPE_1                         2

//--------------------------------------------------
// CEC HW IRQ Group Type
//--------------------------------------------------
#define _HW_CEC_IRQ_HDMI                                  0
#define _HW_CEC_IRQ_SCALER_OTHER                          1

//--------------------------------------------------
// HMDI HW IRQ MODE
// Old Mode: HDMI Mac Level-trigger IRQ
// New Mode: ADI Top IRQ collection consists of level-triggered IRQs
//--------------------------------------------------
#define _HDMI_IRQ_OLD_MODE                                0
#define _HDMI_IRQ_NEW_MODE                                1

//--------------------------------------------------
//  HDCP2.2 Gen Define
//--------------------------------------------------
#define _HDCP_2_2_GEN_1                                   1
#define _HDCP_2_2_GEN_2                                   2

//--------------------------------------------------
//  Display DPTX Combo Type
//--------------------------------------------------
#define _DISPLAY_LVDS_COMBO_DPTX                          0
#define _DISPLAY_VBO_COMBO_DPTX                           1

//--------------------------------------------------
//  Display DPTX Max Lane Number
//--------------------------------------------------
#define _DISPLAY_DPTX_16_LANE                             0
#define _DISPLAY_DPTX_8_LANE                              1
#define _DISPLAY_DPTX_4_LANE                              2

//--------------------------------------------------
// Format conversion 420 Type
//--------------------------------------------------
#define _FORMAT_CONVERSION_420_BY_PORT                    0
#define _FORMAT_CONVERSION_420_BY_PATH                    1

//--------------------------------------------------
// Format conversion sd Type
//--------------------------------------------------
#define _FORMAT_CONVERSION_SD_NONE                        0
#define _FORMAT_CONVERSION_SD_HALF                        1
#define _FORMAT_CONVERSION_SD_HALF_FOUR                   2

//--------------------------------------------------
// Global DB Type
//--------------------------------------------------
#define _GLOBAL_DB_GEN_I                                  0 // I DB, D DB
#define _GLOBAL_DB_GEN_II                                 1 // IMD DB
#define _GLOBAL_DB_GEN_III                                2 // I DB, D DB, IMD DB
#define _GLOBAL_DB_GEN_IV                                 3 // I DB, D DB, IMD DB (by channel)

//------------------------------------------------
//  DDR2 DPI_DLL Type Options
//------------------------------------------------
#define _MEMORY_DDR2_DPIDLL_GEN_0                         0x0000 // For RL6449,RL6561
#define _MEMORY_DDR2_DPIDLL_GEN_1                         0x0001 // For RL6629
#define _MEMORY_DDR2_DPIDLL_GEN_2                         0x0002 // For RL6978

//------------------------------------------------
//  DDR3 DPI_DLL Type Options
//------------------------------------------------
#define _MEMORY_DDR3_DPIDLL_GEN_0                         0x0000 // For RL6493
#define _MEMORY_DDR3_DPIDLL_GEN_1                         0x0001 // For RLE1039,RL6829
#define _MEMORY_DDR3_DPIDLL_GEN_2                         0x0002 // For RL6952

//------------------------------------------------
//  DDR3 Type Options
//------------------------------------------------
#define _MEMORY_DDR3_GEN_0                                0x0000 // DCPHY & DCSys For RL6193,RL6410
#define _MEMORY_DDR3_GEN_1                                0x0001 // DCPHY & DCSys For RL6493
#define _MEMORY_DDR3_GEN_2                                0x0002 // DCPHY & DCSys For RLE1039,RL6829,RL6952

//------------------------------------------------
//  DDR2 Type Options
//------------------------------------------------
#define _MEMORY_DDR2_GEN_0                                0 // DCPHY & DCSys For RL6978

//--------------------------------------------------
// FIFO Clk Sel Type
//--------------------------------------------------
#define _FIFO_CLK_SEL_GEN_0                               0 // RL6829, RL6952: mpll(default), ddrpll, dclk, m2pll
#define _FIFO_CLK_SEL_GEN_1                               1 // RL6978: ddrpll(default), reserved, reserved, m2pll

//--------------------------------------------------
// HW Shift One line Type
//--------------------------------------------------
#define _VSD_SHIFT_ONE_LINE                               0
#define _ROTATION_SHIFT_ONE_LINE                          1
#define _NO_SHIFT_ONE_LINE                                2

//--------------------------------------------------
// HW IVS Reset Cooperation Mode Gen
//--------------------------------------------------
#define _IVS_RESET_COOPERATION_GEN_0                      0 // RL6449 depend on P5AF[1] setting
#define _IVS_RESET_COOPERATION_GEN_1                      1 // RLE1039 control by P3304[6]
#define _IVS_RESET_COOPERATION_GEN_NONE                   0xFF

//-------------------------------------------------
// FB To EO Type Define
//-------------------------------------------------
#define _FB2EO_HWIDTH_SETTING_GEN_0                       0
#define _FB2EO_HWIDTH_SETTING_GEN_1                       1 // RL6952 need to set Hwidth
#define _FB2EO_HWIDTH_SETTING_GEN_NONE                    0xFF

//--------------------------------------------------
//  M-Domain Image Compression TYPE Define
//--------------------------------------------------
#define _M_DOMAIN_IMG_CMP_GEN_0                           0 // PQC
#define _M_DOMAIN_IMG_CMP_GEN_1                           1

//--------------------------------------------------
// Display Rotation Type
//--------------------------------------------------
#define _DISPLAY_ROTATION_GEN_I                           0 // 90, 180, 270
#define _DISPLAY_ROTATION_GEN_II                          1 // 180 : 1/2/3 buffer For RL6561, RL6229
#define _DISPLAY_ROTATION_GEN_III                         2 // 180 : 1/2/3 buffer For RL6829
#define _DISPLAY_ROTATION_GEN_IV                          3 // new 90, 180, 270   For RL6952

//--------------------------------------------------
// Display Rotation Control Type
//--------------------------------------------------
#define _DISPLAY_ROTATION_CTRL_GEN_0                      0 // Rotation cap enable only: RL6829, RL6952
#define _DISPLAY_ROTATION_CTRL_GEN_1                      1 // Rotation cap/disp enable: RL6978

//--------------------------------------------------
// PR Mode Type
//--------------------------------------------------
#define _M_DOMAIN_PR_MODE_GEN_0                           0 // For RL6829, RL6952
#define _M_DOMAIN_PR_MODE_GEN_1                           1 // For RL6978

//--------------------------------------------------
// PIPPBP Blending Generation
//--------------------------------------------------
#define _PIPPBP_BLENDING_GEN_0                            0
#define _PIPPBP_BLENDING_GEN_1                            1

//--------------------------------------------------
// Drop Extension Generation
//--------------------------------------------------
#define _DROP_EXTENSION_GEN_0                             0
#define _DROP_EXTENSION_GEN_1                             1

//--------------------------------------------------
// Definitions of pixel shift mode
//--------------------------------------------------
#define _PIXEL_SHIFT_IN_IDOMAIN                           0
#define _PIXEL_SHIFT_IN_DDOMAIN                           1

//--------------------------------------------------
// M2PLL Struct Generation
//--------------------------------------------------
#define _M2PLL_STRUCT_M_N                                 0
#define _M2PLL_STRUCT_N_F                                 1

//--------------------------------------------------
// MPLL Struct Generation
//--------------------------------------------------
#define _MPLL_STRUCT_M_N                                  0
#define _MPLL_STRUCT_COMBO_M2PLL                          1
#define _MPLL_STRUCT_N_F                                  2

//--------------------------------------------------
// DPLL Struct Generation
//--------------------------------------------------
#define _DPLL_STRUCT_M_N                                  0
#define _DPLL_STRUCT_M_N_CASCADE_N_F                      1
#define _DPLL_STRUCT_N_F_COMBO_LVDSPLL                    2
#define _DPLL_STRUCT_N_F                                  3

//--------------------------------------------------
// DPLL Min Pixel Clk Divider
//--------------------------------------------------
#define _DPLL_DIV1                                        0
#define _DPLL_DIV2                                        1

//--------------------------------------------------
// DP PLL Input Clk Divider
//--------------------------------------------------
#define _DP_RX_PLL_INPUT_CLK_DIV_NONE                     1
#define _DP_RX_PLL_INPUT_CLK_DIV_32                       32
#define _DP_RX_PLL_INPUT_CLK_DIV_40                       40

//--------------------------------------------------
// NF PLL Struct Generation
//--------------------------------------------------
#define _NF_PLL_GEN_0                                     0 // for RL6829: u28
#define _NF_PLL_GEN_1                                     1 // for RL6952: t22

//--------------------------------------------------
// DPLL Generation Define
//--------------------------------------------------
#define _MN_DPLL_PATH1                                    1
#define _MN_DPLL_PATH2                                    0 // reg spec: path0

//--------------------------------------------------
// MPLL Generation Define
//--------------------------------------------------
#define _MN_MPLL_PATH1                                    1
#define _MN_MPLL_PATH2                                    0 // reg spec: path0

//--------------------------------------------------
// M2PLL Freq
//--------------------------------------------------
#define _M2PLL_FREQ_243M                                  0
#define _M2PLL_FREQ_351M                                  1
#define _M2PLL_FREQ_372M                                  2

//--------------------------------------------------
// M2PLL VCO Freq
//--------------------------------------------------
#define _M2PLL_FVCO_351M                                  0
#define _M2PLL_FVCO_702M                                  1

//--------------------------------------------------
// Memory Device PLL Struct Generation
//--------------------------------------------------
#define _MEMORY_DEVICE_PLL_GEN_0                          0 // for RL6978: DDR2
#define _MEMORY_DEVICE_PLL_GEN_1                          1 // for RL6561: DDR2
#define _MEMORY_DEVICE_PLL_GEN_2                          2 // for RL6629
#define _MEMORY_DEVICE_PLL_GEN_3                          3 // for RLE1039,RL6829
#define _MEMORY_DEVICE_PLL_GEN_4                          4 // for RL6952 DDR3 combo DDR2

//--------------------------------------------------
// FRC Length Value
//--------------------------------------------------
#define _FRC_LENGTH_7BIT                                  0x7C // for RL6829
#define _FRC_LENGTH_8BIT                                  0xFC // for RL6952

//--------------------------------------------------
// OD Generation
//--------------------------------------------------
#define _OD_GEN_0                                         0 // for OD table format before RL6229
#define _OD_GEN_1                                         1 // for OD table format since RL6229
#define _OD_GEN_2                                         2

#define _OD_8BIT_LUT                                      0
#define _OD_10BIT_LUT                                     1 // for RL6193, RL6410, RL6449, RL6493: 10-bit ODLUT mode

#define _OD_BY_POSITION_GEN_0                             0

#define _OD_COMP_GEN_0                                    0 // for Scaler before RL6952
#define _OD_COMP_GEN_1                                    1 // for RL6952: Compression Method Pixel_Filter_1X4

//--------------------------------------------------
// 3DDI Generation
//--------------------------------------------------
#define _HW_3DDI_PATH_0                                   0x01
#define _HW_3DDI_PATH_1                                   0x02
#define _HW_3DDI_PATH_2                                   0x04
#define _HW_3DDI_PATH_3                                   0x08
#define _HW_3DDI_PATH_NONE                                0

//--------------------------------------------------
// Scaling Up Generation
//--------------------------------------------------
#define _SU_GEN_0                                         0
#define _SU_GEN_1                                         1
#define _SU_GEN_2                                         2

//--------------------------------------------------
// Scaling Up Video Compensation Generation
//--------------------------------------------------
#define _SU_VIDEO_COMPENSATION_GEN_0                      0
#define _SU_VIDEO_COMPENSATION_GEN_1                      1

//--------------------------------------------------
// Scaling Up HSUI Generation
//--------------------------------------------------
#define _SU_HSUI_GEN_0                                    0
#define _SU_HSUI_GEN_1                                    1

//--------------------------------------------------
// Scaling Down Generation
//--------------------------------------------------
#define _SD_GEN_0                                         0 // for RL6829 : SD After IDither & H/VSD Output Window Select Combined
#define _SD_GEN_1                                         1 // for RL6952 : SD Before IDither & H/VSD Output Window Select Seperated

//--------------------------------------------------
// OSD Blending BG color insert Generation
//--------------------------------------------------
#define _OSD_BLENDING_BG_COLOR_INSERT_GEN_0               0 // for RL6829: only enable bit, need CRC fine tune
#define _OSD_BLENDING_BG_COLOR_INSERT_GEN_1               1 // for RL6952: create bg_color_insert_flag to determine insert specific frame (2 frame cycle)
#define _OSD_BLENDING_BG_COLOR_INSERT_GEN_2               2 // for RL6978: extend determining insert specific frame function (max 8 frame cycle)

//--------------------------------------------------
// DCR Generation
//--------------------------------------------------
#define _DCR_GEN_0                                        0
#define _DCR_GEN_1                                        1
#define _DCR_GEN_2                                        2
#define _DCR_GEN_3                                        3
#define _DCR_GEN_4                                        4
#define _DCR_GEN_5                                        5

#define _DCR_8BIT                                         0
#define _DCR_10BIT                                        1

//--------------------------------------------------
// IAPS Generation
//--------------------------------------------------
#define _IAPS_GAIN_COMPENSATION_GEN_0                     0
#define _IAPS_GAIN_COMPENSATION_GEN_1                     1

//--------------------------------------------------
// DCC Generation
//--------------------------------------------------
#define _DCC_GEN_0                                        0
#define _DCC_GEN_1                                        1

#define _DCC_DB_GEN_0                                     0
#define _DCC_DB_GEN_1                                     1

//--------------------------------------------------
// DCC Y Bit Mode
//--------------------------------------------------
#define _DCC_Y_8BIT                                       0
#define _DCC_Y_10BIT                                      1

//--------------------------------------------------
// ICM Generation
//--------------------------------------------------
#define _ICM_GEN_0                                        0
#define _ICM_GEN_1                                        1
#define _ICM_GEN_2                                        2
#define _ICM_GEN_3                                        3

#define _ICM_DB_GEN_0                                     0    // No local DB, 6952, 6829
#define _ICM_DB_GEN_1                                     1    // with local DB, 6978

//-------------------------------------------------
// Color Conversion Generation
//-------------------------------------------------
#define _COLOR_CONVERSION_GEN_0                           0
#define _COLOR_CONVERSION_GEN_1                           1
#define _COLOR_CONVERSION_GEN_2                           2
#define _COLOR_CONVERSION_GEN_3                           3
#define _COLOR_CONVERSION_GEN_4                           4

#define _COLOR_CONVERSION_DB_GEN_0                        0
#define _COLOR_CONVERSION_DB_GEN_1                        1

//--------------------------------------------------
// Input Gamma Generation
//--------------------------------------------------
#define _INPUT_GAMMA_GEN_0                                0
#define _INPUT_GAMMA_GEN_1                                1
#define _INPUT_GAMMA_GEN_2                                2

#define _INPUT_GAMMA_DB_GEN_0                             0
#define _INPUT_GAMMA_DB_GEN_1                             1

//--------------------------------------------------
// Input Gamma Table Node Type
//--------------------------------------------------
#define _INPUT_GAMMA_NODE_129                             0
#define _INPUT_GAMMA_NODE_1025                            1

//--------------------------------------------------
// YMapping DB Type
//--------------------------------------------------
#define _YMAPPING_DB_GEN_0                                0
#define _YMAPPING_DB_GEN_1                                1

//--------------------------------------------------
// Output Gamma Generation
//--------------------------------------------------
#define _OUTPUT_GAMMA_GEN_0                               0
#define _OUTPUT_GAMMA_GEN_1                               1

//--------------------------------------------------
// sRGB Generation
//--------------------------------------------------
#define _SRGB_GEN_0                                       0
#define _SRGB_GEN_1                                       1

//--------------------------------------------------
// 3D Gamma Calibration Generation
//--------------------------------------------------
#define _3D_GAMMA_GEN_0                                   0
#define _3D_GAMMA_GEN_1                                   1
#define _3D_GAMMA_GEN_2                                   2 // For RL6978 3D Gamma Tetrahedral

//--------------------------------------------------
// PCM Generation
//--------------------------------------------------
#define _PCM_GEN_0                                        0
#define _PCM_GEN_1                                        1
#define _PCM_GEN_2                                        2 // For RLE1039 Input_Gamma M2 R/G/B Mode

//--------------------------------------------------
// Output Gamma Calibration Generation
//--------------------------------------------------
#define _OGC_GEN_0                                        0
#define _OGC_GEN_1                                        1

//--------------------------------------------------
// OCC Gamma Calibration Generation
//--------------------------------------------------
#define _OCC_GAMMA_GEN_0                                  0
#define _OCC_GAMMA_GEN_1                                  1

//--------------------------------------------------
// IDither Generation
//--------------------------------------------------
#define _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT             0
#define _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT             1
#define _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT    2
#define _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT           3
#define _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD    4

//--------------------------------------------------
// DDither Generation
//--------------------------------------------------
#define _DDITHER_GEN_0_4BIT_DITHERTBL                     0
#define _DDITHER_GEN_1_6BIT_DITHERTBL                     1
#define _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL      2
#define _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL          3
#define _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2       4

//--------------------------------------------------
// Local Dimming HW Generation
//--------------------------------------------------
#define _HW_LOCAL_DIMMING_OFF                             0
#define _HW_LOCAL_DIMMING_GEN1                            1
#define _HW_LOCAL_DIMMING_GEN2                            2

#define _HW_LOCAL_DIMMING_PWM_TABLE_FORM0                 0
#define _HW_LOCAL_DIMMING_PWM_TABLE_FORM1                 1

//--------------------------------------------------
// Local Contrast Generation
//--------------------------------------------------
#define _LOCAL_CONTRAST_GEN_0                             0     // for RL6493
#define _LOCAL_CONTRAST_GEN_1                             1     // for RL6561 : temporal step improve to 6
#define _LOCAL_CONTRAST_GEN_2                             2     // for RL6629 : temporal filter, CDM
#define _LOCAL_CONTRAST_GEN_3                             3     // for RL6829 : sfilter pre-do, Seamless, support FB & PIP PBPLR
#define _LOCAL_CONTRAST_GEN_4                             4     // for RL6952 : sfilter / tfilter with DB

//--------------------------------------------------
// Ultra Vivid Generation
//--------------------------------------------------
#define _ULTRA_VIVID_GEN_0                                0
#define _ULTRA_VIVID_GEN_1                                1
#define _ULTRA_VIVID_GEN_2                                2
#define _ULTRA_VIVID_GEN_3                                3
#define _ULTRA_VIVID_GEN_4                                4
#define _ULTRA_VIVID_GEN_5                                5
#define _ULTRA_VIVID_GEN_6                                6

//--------------------------------------------------
// CtsBri Generation
//--------------------------------------------------
#define _CTS_GEN_0_8BIT                                   0
#define _CTS_GEN_1_12BIT                                  1

#define _BRI_GEN_0_8BIT                                   0
#define _BRI_GEN_1_10BIT                                  1

//--------------------------------------------------
// CtsBri Enable Bit Addr Type
//--------------------------------------------------
#define _CTS_EN_ADDR_P0_62                                0
#define _CTS_EN_ADDR_P0_65                                1

#define _BRI_EN_ADDR_P0_62                                0
#define _BRI_EN_ADDR_P0_65                                1

//--------------------------------------------------
// Multi Region Color Calibration List
//--------------------------------------------------
#define _COLOR_NONE                                       0
#define _COLOR_1_REGION                                   1
#define _COLOR_2_REGION                                   2
#define _COLOR_3_REGION                                   3

//--------------------------------------------------
// Signal Detection Measure GEN Define
//--------------------------------------------------
#define _SIGNAL_MEASURE_GEN_1                             1 // dp_xtal_cycle[4:0]
#define _SIGNAL_MEASURE_GEN_2                             2 // dp_xtal_cycle[0]

//--------------------------------------------------
// HW SARADC Support and Bit Num
//--------------------------------------------------
#define _SARADC_NONE                                      0
#define _SARADC_5BIT_MSB                                  1 // from bit7~bit3
#define _SARADC_5BIT_LSB                                  2 // from bit4~bit0
#define _SARADC_8BIT                                      3

//--------------------------------------------------
// HW SARADC Type
//--------------------------------------------------
#define _HW_SARADC_GEN_0                                  0 // For RL6829, and Old IC
#define _HW_SARADC_GEN_1                                  1 // For RL6952
#define _HW_SARADC_GEN_2                                  2 // For RL6983
#define _HW_SARADC_GEN_3                                  3 // For RL6978

//--------------------------------------------------
//  Flash Clock Source Option List
//--------------------------------------------------
#define _FLASH_EXT_XTAL_CLK                               0
#define _FLASH_IOSC_CLK                                   1

//--------------------------------------------------
//  Power Flow Gen Define
//--------------------------------------------------
#define _POWER_FLOW_GEN_1                                 1
#define _POWER_FLOW_GEN_2                                 2

//--------------------------------------------------
//  Power Region
//--------------------------------------------------
#define _POWER_REGION_TYPE_A                              0
#define _POWER_REGION_TYPE_B                              1

//--------------------------------------------------
//  Thermal Sensor Define
//--------------------------------------------------
#define _THERMAL_SENSOR_NONE                              0
#define _THERMAL_SENSOR_GEN_1                             1
#define _THERMAL_SENSOR_GEN_2                             2

//--------------------------------------------------
//  OTP Define
//--------------------------------------------------
#define _TYPE_NONE                                        0
#define _EFUSE_TYPE                                       1
#define _OTPFUSE_TYPE                                     2

//--------------------------------------------------
// IOSC Frequency
//--------------------------------------------------
#define _IOSC27000K                                       27000UL
#define _IOSC28000K                                       28000UL

//--------------------------------------------------
// DDR Phase Calibration
//--------------------------------------------------
#define _MEMORY_PHASE_CALIBRATION_MCU_MODE                0
#define _MEMORY_PHASE_CALIBRATION_FRC_MODE                1
#define _MEMORY_PHASE_CALIBRATION_MODE_NONE               2

//--------------------------------------------------
// FW Write Flash Method
//--------------------------------------------------
#define _FLASH_WRITE_PORT_ACCESS                          0
#define _ISP_PROG_ACCESS                                  1

//--------------------------------------------------
// FW Read Flash Method
//--------------------------------------------------
#define _FLASH_READ_PORT_ACCESS                           0
#define _MEMORY_MAP_ACCESS                                1

//--------------------------------------------------
// Tcon Gen
//--------------------------------------------------
#define _TCON_GEN_0                                       0
#define _TCON_GEN_1                                       1

//--------------------------------------------------
// Tcon
//--------------------------------------------------
#define _TCON_NONE                                        0xFF
#define _TCON0                                            0
#define _TCON1                                            1
#define _TCON2                                            2
#define _TCON3                                            3
#define _TCON4                                            4
#define _TCON5                                            5
#define _TCON6                                            6
#define _TCON7                                            7
#define _TCON8                                            8
#define _TCON9                                            9
#define _TCON10                                           10
#define _TCON11                                           11
#define _TCON12                                           12
#define _TCON13                                           13

//--------------------------------------------------
// SEC Data Proc Gen
//--------------------------------------------------
#define _SEC_DATA_PROC_GEN_1                              1
#define _SEC_DATA_PROC_GEN_2                              2

//--------------------------------------------------
// Definitions of Page
//--------------------------------------------------
#define _PAGE0                                            0x00
#define _PAGE1                                            0x01
#define _PAGE2                                            0x02
#define _PAGE3                                            0x03
#define _PAGE4                                            0x04
#define _PAGE5                                            0x05
#define _PAGE6                                            0x06
#define _PAGE7                                            0x07
#define _PAGE8                                            0x08
#define _PAGE9                                            0x09
#define _PAGEA                                            0x0A
#define _PAGEB                                            0x0B
#define _PAGEC                                            0x0C
#define _PAGED                                            0x0D
#define _PAGEE                                            0x0E
#define _PAGEF                                            0x0F
#define _PAGE10                                           0x10

#define _PAGE2D                                           0x2D
#define _PAGE2E                                           0x2E
#define _PAGE6D                                           0x6D
#define _PAGE6E                                           0x6E

#define _PAGE70                                           0x70
#define _PAGE71                                           0x71
#define _PAGE72                                           0x72
#define _PAGE74                                           0x74

#define _PAGE7B                                           0x7B
#define _PAGE7C                                           0x7C
#define _PAGE7D                                           0x7D
#define _PAGE7E                                           0x7E

#define _PAGEB0                                           0xB0
#define _PAGEB5                                           0xB5
#define _PAGEB6                                           0xB6
#define _PAGEB8                                           0xB8
#define _PAGEB9                                           0xB9

#define _PAGE9D                                           0x9D
#define _PAGE9F                                           0x9F

#define _PAGEB5                                           0xB5
#define _PAGEB8                                           0xB8

#define _PAGEC5                                           0xC5
#define _PAGEC6                                           0xC6

#define _PAGEE4                                           0xE4

#define _PAGE_COMMON                                      0xFF
#define _PAGE_NONE                                        0x100

//--------------------------------------------------
// Definitions of Rx Index for HDMI/DP Mac & HDCP2.2
//--------------------------------------------------
#define _MAPPING_RX0                                      0x00
#define _MAPPING_RX1                                      0x01
#define _MAPPING_RX2                                      0x02
#define _MAPPING_RX3                                      0x03
#define _MAPPING_RX4                                      0x04
#define _MAPPING_RX5                                      0x05
#define _MAPPING_RX7                                      0x07
#define _MAPPING_RX8                                      0x08
#define _MAPPING_RX0_OR_RX1                               0x10
#define _MAPPING_RX0_OR_RX1_OR_RX2                        0x20
#define _MAPPING_RX_MAP_NONE                              0xFF

//--------------------------------------------------
// OSD Write Protection Generation
//--------------------------------------------------
#define _OSD_WRITE_PROTECT_GEN_0                          0
#define _OSD_WRITE_PROTECT_GEN_1                          1

//--------------------------------------------------
// OSD HW Put String Generation
//--------------------------------------------------
#define _OSD_HW_PUT_STRING_GEN_0                          0
#define _OSD_HW_PUT_STRING_GEN_1                          1

//--------------------------------------------------
// OSD Timing Gen. Double Buffer Generation
//--------------------------------------------------
#define _OSD_TIMING_GEN_DB_GEN_NONE                       0
#define _OSD_TIMING_GEN_DB_GEN_1                          1

//--------------------------------------------------
// Definitions of EMCU PLL SPEED
//--------------------------------------------------
#define _EMCU_PLL_SPEED_354M                              353894UL   // 353.894MHz,+-1%
#define _EMCU_PLL_SPEED_480M                              480000UL   // 480.000MHz,+-1%

//--------------------------------------------------
// TTS Burst Read Count Register
//    - _GEN_0 P8_66_BLK0_BWR_COUNT_H
//    - _GEN_1 P8_66_BLK0_BWR_COUNT_M
//--------------------------------------------------
#define _AUDIO_TTS_BWR_COUNT_GEN_0                        0
#define _AUDIO_TTS_BWR_COUNT_GEN_1                        1

//--------------------------------------------------
// AUDIO DAC Generation
//    - _GEN_0 Analog: Class B (First) Version ; Digital: (First) Version
//    - _GEN_1 Analog: Class A (First) Version ; Digital: (Second) Version
//    - _GEN_2 Analog: Class B (Second) Version ; Digital: (Second) Version
//--------------------------------------------------
#define _AUDIO_DAC_GEN_0                                  0
#define _AUDIO_DAC_GEN_1                                  1
#define _AUDIO_DAC_GEN_2                                  2

//--------------------------------------------------
// Internal OSC Generation
//    - _GEN_0 Trimming VC / MOS Result 5bit Architecture
//    - _GEN_1 Trimming VC / MOS Result 6bit Architecture
//--------------------------------------------------
#define _IOSC_GEN_0                                       0
#define _IOSC_GEN_1                                       1

//--------------------------------------------------
// USB3 Power Saving Support Level
//    - RL6829 : MAC, DFP Power off --> Level 1
//    - RL6952 : MAC, DFP, UFP Aphy Power off --> Level 2
//    - RL6978 : MAC, DFP, UFP, JFM Power off --> Level 3
//--------------------------------------------------
#define _USB3_PS_SUPPORT_LEVEL_1                          0
#define _USB3_PS_SUPPORT_LEVEL_2                          1
#define _USB3_PS_SUPPORT_LEVEL_3                          2

//--------------------------------------------------
// TOP_ON Power Domain Generation
//--------------------------------------------------
#define _TOP_ON_POWER_DOMAIN_GEN_0                        0 // for RL6829, RL6952
#define _TOP_ON_POWER_DOMAIN_GEN_1                        1 // for RL6978

//--------------------------------------------------
// RXI300 HW Generation
//--------------------------------------------------
#define _RXI300_HW_GEN_0                                  0
#define _RXI300_HW_GEN_1                                  1

#endif // End of #ifndef __SCALER_LIST_H__
