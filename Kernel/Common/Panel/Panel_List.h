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
// ID Code      : Panel_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PANEL_LIST_H__
#define __PANEL_LIST_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_NONE_BRAND                       0
#define _PANEL_AUO                              1
#define _PANEL_CMO                              2
#define _PANEL_CPT                              3
#define _PANEL_HSD                              4
#define _PANEL_SAMSUNG                          5
#define _PANEL_LGD                              6
#define _PANEL_SVA                              7
#define _PANEL_BOE                              8
#define _PANEL_INNOLUX                          9
#define _PANEL_QISDA                            10

//--------------------------------------------------
// Definitions for Panel Settings
//--------------------------------------------------
#define _PANEL_NONE                             0
#define _PANEL_TTL                              1
#define _PANEL_LVDS                             2
#define _PANEL_RSDS                             3
#define _PANEL_VBO                              4
#define _PANEL_DPTX                             5

//--------------------------------------------------
// Definitions for Panel Pixel Settings
//--------------------------------------------------
#define _PANEL_PIXEL_LCD                        0
#define _PANEL_PIXEL_OLED                       1
#define _PANEL_PIXEL_MICRO_LED                  2

//--------------------------------------------------
// Definitions for Panel Bit Length
//--------------------------------------------------
#define _PANEL_DISP_18_BIT                      0
#define _PANEL_DISP_24_BIT                      1
#define _PANEL_DISP_30_BIT                      2
#define _PANEL_DISP_36_BIT                      3
#define _PANEL_DISP_48_BIT                      4

//--------------------------------------------------
// Definitions for LVDS Port Counts
//--------------------------------------------------
#define _LVDS_1_PORT                            0
#define _LVDS_2_PORT                            1
#define _LVDS_4_PORT                            2
#define _LVDS_8_PORT                            3

//--------------------------------------------------
// Definitions for LVDS Bit Map Table
//--------------------------------------------------
#define _LVDS_BIT_MAP_TABLE_1_3                 0
#define _LVDS_BIT_MAP_TABLE_2_4                 1

//--------------------------------------------------
// Definitions for LVDS Panel Type
//--------------------------------------------------
#define _LVDS_PANEL_1_SECTION                   0
#define _LVDS_PANEL_2_SECTION                   1
#define _LVDS_PANEL_4_SECTION                   2
#define _LVDS_PANEL_8_SECTION                   3

//--------------------------------------------------
// Definitions for TTL Port Counts
//--------------------------------------------------
#define _TTL_1_PORT                             0
#define _TTL_2_PORT                             1

//--------------------------------------------------
// Definitions for DPTX Panel Phy Rate
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RBR                    0x06
#define _PANEL_DPTX_LINK_HBR                    0x0A
#define _PANEL_DPTX_LINK_HBR2                   0x14
#define _PANEL_DPTX_LINK_HBR3                   0x1E
#define _PANEL_DPTX_LINK_HBR3_9G                0x21

//--------------------------------------------------
// Definitions for DPTX Panel Phy Rate
//--------------------------------------------------
#define _PANEL_DPTX_LANE_NUMBER_1               0
#define _PANEL_DPTX_LANE_NUMBER_2               1
#define _PANEL_DPTX_LANE_NUMBER_4               2
#define _PANEL_DPTX_LANE_NUMBER_8               3
#define _PANEL_DPTX_LANE_NUMBER_16              4

//--------------------------------------------------
// Definitions for DPTX Panel Phy Rate
//--------------------------------------------------
#define _DPTX_PANEL_1_SECTION                   0
#define _DPTX_PANEL_2_SECTION                   1
#define _DPTX_PANEL_4_SECTION                   2
#define _DPTX_PANEL_8_SECTION                   3

//--------------------------------------------------
// Definitions for DPTX Panel Vendor Specific Type List
//--------------------------------------------------
#define _PANEL_DPTX_VENDOR_SPECIFIC_NONE        0
#define _PANEL_DPTX_VENDOR_SPECIFIC_004F1H      1

//--------------------------------------------------
// Definitions for DPTX Scramble Seed
//--------------------------------------------------
#define _PANEL_DPTX_SCRAMBLE_SEED_AUTO          0
#define _PANEL_DPTX_SCRAMBLE_SEED_0XFFFE        1
#define _PANEL_DPTX_SCRAMBLE_SEED_0XFFFF        2

//--------------------------------------------------
// Definitions for DPTX LT Singal Level Mode
//--------------------------------------------------
#define _PANEL_DPTX_LT_MANUAL_MODE              0
#define _PANEL_DPTX_LT_NORMAL_MODE              1

//--------------------------------------------------
// Definitions for DPTX LT Training Pattern End Sequence
//--------------------------------------------------
#define _TRAIN_PATTERN_END_BEFORE_IDEL_PATTERN  0
#define _TRAIN_PATTERN_END_AFTER_IDEL_PATTERN   1

//--------------------------------------------------
// Definitions for DPTX Set HPD Detect Sequence
//--------------------------------------------------
#define _HPD_DETECT_AFTER_PANEL_HPD_T2_TIME     0
#define _HPD_DETECT_AFTER_VIDEO_STREAM          1

//--------------------------------------------------
// Definitions for DPTX HPD Time
//--------------------------------------------------
#define _DPTX_HPD_TIME_2_MS                     0
#define _DPTX_HPD_TIME_30_MS                    1

//--------------------------------------------------
// Definitions for Vby1 Bit Length
//--------------------------------------------------
#define _VBO_DISP_30_BIT                        1
#define _VBO_DISP_24_BIT                        2
#define _VBO_DISP_18_BIT                        3

//--------------------------------------------------
// Definitions for Vby1 Lane Count
//--------------------------------------------------
#define _VBO_1_DATA_LANE                        1
#define _VBO_2_DATA_LANE                        2
#define _VBO_4_DATA_LANE                        4
#define _VBO_8_DATA_LANE                        8
#define _VBO_16_DATA_LANE                       16
#define _VBO_32_DATA_LANE                       32

//--------------------------------------------------
// Definitions for Vby1 Panel Section
//--------------------------------------------------
#define _VBO_PANEL_1_SECTION                    1
#define _VBO_PANEL_2_SECTION                    2
#define _VBO_PANEL_4_SECTION                    4
#define _VBO_PANEL_8_SECTION                    8
#define _VBO_PANEL_16_SECTION                   16
#define _VBO_PANEL_32_SECTION                   32

//--------------------------------------------------
// Definitions for Vby1 Panel HS Control
//--------------------------------------------------
#define _VBO_HS_NORMAL                          0
#define _VBO_HS_ALWAYS_OFF                      1
#define _VBO_HS_ALWAYS_ON                       2
#define _VBO_HS_INVERSE                         3

//--------------------------------------------------
// Definitions for Vby1 Panel VS Control
//--------------------------------------------------
#define _VBO_VS_NORMAL                          0
#define _VBO_VS_ALWAYS_OFF                      1
#define _VBO_VS_ALWAYS_ON                       2
#define _VBO_VS_INVERSE                         3

//--------------------------------------------------
// Definitions for Vby1 Panel Video Pattern Transfer Type
//--------------------------------------------------
#define _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK 0
#define _VBO_VIDEO_TRANSFER_IN_VERTICAL_BLANK   1

//--------------------------------------------------
// Definitions for Vby1 Panel Change Clk Reset Type
//--------------------------------------------------
#define _VBO_CHANGE_CLK_RESET_BY_PANEL_OFF      0
#define _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN  1
#define _VBO_CHANGE_CLK_BY_M_DOMAIN_FREE_RUN    2

//--------------------------------------------------
// Definitions for Vby1 Panel Change Clk Reset Type
//--------------------------------------------------
#define _VBO_LANE_SKEW_RESET_BY_CK_USABLE       0
#define _VBO_LANE_SKEW_RESET_BY_CMU_POWER       1

//--------------------------------------------------
// Definitions for Vby1 Pixel Mode
//--------------------------------------------------
#define _VBO_2_PIXEL_MODE                       2
#define _VBO_4_PIXEL_MODE                       4

//--------------------------------------------------
// Definitions for Vby1 Byte Mode
//--------------------------------------------------
#define _VBO_DISP_3_BYTE_MODE                   3
#define _VBO_DISP_4_BYTE_MODE                   4
#define _VBO_DISP_5_BYTE_MODE                   5

//--------------------------------------------------
// Definitions for 2D / 3D panel type
//--------------------------------------------------
#define _PANEL_DISPLAY_NORMAL                   0
#define _PANEL_DISPLAY_SHUTTER_GLASSES          1
#define _PANEL_DISPLAY_PATTERN_RETARDER         2

//--------------------------------------------------
// Definitions for PR Panel Display Type
//--------------------------------------------------
#define _PANEL_PR_LR_DISPLAY                    0
#define _PANEL_PR_RL_DISPLAY                    1

//--------------------------------------------------
// Definitions for Panel Backlight
//--------------------------------------------------
#define _PANEL_BACKLIGHT_CCFL                   0
#define _PANEL_BACKLIGHT_LED                    1

//--------------------------------------------------
// Definitions for Panel OLED AC DET with Power Sequnce
//--------------------------------------------------
#define _PANEL_OLED_AC_DET_CTRL_WITHOUT_SEQ     0
#define _PANEL_OLED_AC_DET_CTRL_WITH_SEQ        1

//--------------------------------------------------
// Definitions for Panel Clk Unit
//--------------------------------------------------
#define _PANEL_CLOCK_MHZ                        0
#define _PANEL_CLOCK_KHZ                        1

//--------------------------------------------------
// Definitions for Panel Cable Type
//--------------------------------------------------
#define _LVDS_CABLE_TYPE_0                      0
#define _LVDS_CABLE_TYPE_1                      1

//--------------------------------------------------
// Panel Led Driver List
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_NONE                 0xFF

//--------------------------------------------------
// Definitions for Local dimming Panel Communication Type
//--------------------------------------------------
#define _INTERFACE_SPI                          0
#define _INTERFACE_IIC                          1

//--------------------------------------------------
// Definitions for Local dimming Panel type
//--------------------------------------------------
#define _LOCAL_DIMMING_1X8_MODE                 0
#define _LOCAL_DIMMING_2X8_MODE                 1

//--------------------------------------------------
// Definitions for Local dimming Panel Backlight type
//--------------------------------------------------
#define _LOCAL_DIMMING_DIRECT_BACKLIGHT         0
#define _LOCAL_DIMMING_EDGE_BACKLIGHT           1

//--------------------------------------------------
// Definitions for Local dimming PWM2SPI SRAM Mode UpdSync Trigger Source
//--------------------------------------------------
#define _SMODE_UPDSYNC_BY_MANUAL                0
#define _SMODE_UPDSYNC_BY_LD_GAIN_SYNC          1

//--------------------------------------------------
// Definitions for Local dimming PWM2SPI SRAM Mode UpdSync Method
//--------------------------------------------------
#define _SMODE_UPDSYNC_USE_VSYNC                0
#define _SMODE_UPDSYNC_USE_SPI                  1

//--------------------------------------------------
// Definitions of IDither Options
//--------------------------------------------------
#define _IDITHER_SUPER_PIXEL_2X2                0
#define _IDITHER_SUPER_PIXEL_2X4                1
#define _IDITHER_SUPER_PIXEL_4X2                2
#define _IDITHER_SUPER_PIXEL_4X4                3

//--------------------------------------------------
// Definitions of DDither Options
//--------------------------------------------------
#define _DDITHER_SUPER_PIXEL_2X2                0
#define _DDITHER_SUPER_PIXEL_2X4                1
#define _DDITHER_SUPER_PIXEL_4X2                2
#define _DDITHER_SUPER_PIXEL_4X4                3
#define _DDITHER_SUPER_PIXEL_4X8                4
#define _DDITHER_SUPER_PIXEL_8X4                5
#define _DDITHER_SUPER_PIXEL_8X8                6

//--------------------------------------------------
// Definations of Scaler Write/Read Type
//--------------------------------------------------
#define _NON_AUTOINC                            1
#define _AUTOINC                                0
#define _BURST                                  2
#define _END                                    0

//--------------------------------------------------
// Definitions for Asymmetric Panel
//--------------------------------------------------
#define _DUMMY_BEFORE_ACTIVE                    0
#define _DUMMY_AFTER_ACTIVE                     1

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#ifndef __ASSEMBLER__

//--------------------------------------------------
// Enumerations of DCC Table Index
//--------------------------------------------------
typedef enum
{
    _DCC_CONTROL,
    _DCC_TABLE,
    _DCC_END,
} EnumDCCTableIndex;

//--------------------------------------------------
// Enumerations of ICM Table Index
//--------------------------------------------------
typedef enum
{
    _ICM_CONTROL,
    _ICM_0,
    _ICM_1,
    _ICM_2,
    _ICM_3,
    _ICM_4,
    _ICM_5,
    _ICM_END = 0xff,
} EnumICMTableIndex;

typedef enum
{
    _SCM_CONTROL,
    _SCM_0,
    _SCM_1,
    _SCM_2,
    _SCM_3,
    _SCM_4,
    _SCM_5,
    _SCM_6,
    _SCM_7,
    _SCM_END = 0xff,
} EnumSCMTableIndex;
#endif

#endif // End of #ifndef __PANEL_LIST_H__
