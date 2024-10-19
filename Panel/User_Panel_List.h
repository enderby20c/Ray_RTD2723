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
// ID Code      : User_Panel_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Panel Type List
//--------------------------------------------------
#define _PANEL_LVDS_EXAMPLE                     0x01
#define _PANEL_DPTX_EXAMPLE                     0x02
#define _PANEL_VBO_EXAMPLE                      0x03
#define _PANEL_TTL_EXAMPLE                      0x04

#define _INNOLUX_TTL_7                          0x10    // 800 x  480
#define _CMO_LVDS_17                            0x11    // 1280 x 1024
#define _CMO_LVDS_19_WXGA                       0x12    // 1440 x  900
#define _AU_LVDS_22_WSXGA                       0x13    // 1680 x 1050
#define _AU_LVDS_22_WSXGA_QC                    0x14    // 1680 x 1050
#define _AU_LVDS_21_5_WUXGA                     0x15    // 1920 x 1080
#define _AU_LVDS_21_5_WUXGA_FREESYNC            0x16    // 1920 x 1080
#define _AU_LVDS_23_WUXGA                       0x17    // 1920 x 1200
#define _AU_LVDS_24_WUXGA                       0x18    // 1920 x 1080
#define _AU_LVDS_27_WUXGA_FREESYNC              0x19    // 1920 x 1080
#define _AU_DP_21_5_WUXGA                       0x1A    // 1920 x 1080
#define _AU_DP_21_5_WUXGA_FREESYNC              0x1B    // 1920 x 1080
#define _AU_DP_HBR2_21_5_WUXGA                  0x1C    // 1920 x 1080
#define _AUO_VBO_27_WUXGA_FREESYNC              0x1E    // 1920 x 1080
#define _AUO_VBO_M250HTN01_0                    0x1F    // 1920 x 1080 240Hz

#define _LG_LED_DP_34_WFHD                      0x20    // 2560 x 1080
#define _LG_LED_DP_17_QHD                       0x21    // 2560 x 1440
#define _LG_LED_DP_27_QHD                       0x22    // 2560 x 1440
#define _LG_LED_DP_27_QHD_QC                    0x23    // 2560 x 1440
#define _LG_LED_LVDS_27_WUXGA                   0x24    // 2560 x 1440
#define _AUO_EDP_QHD_16ZONE                     0x25    // 2560 x 1440

#define _BOE_EDP_34_WQHD_EO                     0x30    // 3440 x 1440 120Hz(tcon 3456 x 1440)
#define _BOE_VBO_4K480                          0x31    // 3840 x 1080 480Hz
#define _LG_LED_LVDS_23_UHD                     0x32    // 3840 x 2160
#define _AU_LVDS_UHD_DOLBY_DUMP                 0x33    // 3840 x 2160
#define _SAMSUNG_LED_DP_15_6_UHD                0x34    // 3840 x 2160
#define _SAMSUNG_LED_DP_23_6_UHD                0x35    // 3840 x 2160
#define _LG_LED_DP_27_UHD                       0x36    // 3840 x 2160
#define _AUO_EDP_27_UHD_512ZONE                 0x37    // 3840 x 2160
#define _AUO_LED_DP_32_UHD                      0x38    // 3840 x 2160
#define _INNOLUX_LED_VBO_28_UHD                 0x39    // 3840 x 2160
#define _INNOLUX_LED_VBO_40_UHD                 0x3A    // 3840 x 2160
#define _INNOLUX_LED_VBO_28_UHD_FREESYNC        0x3B    // 3840 x 2160
#define _INNOLUX_LED_VBO_16X9_144ZONE           0x3C    // 3840 x 2160
#define _AUO_EDP_27_UHD_16X2_ZONE               0x3D    // 3840 x 2160
#define _AUO_LED_EDP_43_UHD_8X2_ZONE            0x3E    // 3840 x 2160
#define _BOE_LED_DPTX_27_1152_ZONE              0x3F    // 3840 x 2160
#define _BOE_VBO_4K240                          0x40    // 3840 x 2160 240Hz

#define _LG_LED_DP_27_QQHD                      0x60    // 5120 x 2880
#define _RTK_EDP_9G_8K4K_2CHIP_FRONT            0x61    // 7680 x 4320
#define _INNOLUX_VBO_8K4K                       0x62    // 7680 x 4320

#define _MULTIPANEL_LVDS_21_5_WUXGA             0x80    // Mutlti-Panel
#define _MULTIPANEL_DP_QC                       0x81    // Mutlti-Panel
#define _MULTIPANEL_DP_21_5_WUXGA               0x82    // Mutlti-Panel

#define _DT_TEST_FHD_144HZ_350M                 0x90    // Dt-Test Panel 1920 x 1080 144Hz
#define _DT_TEST_WFHD_200HZ_653M                0x91    // Dt-Test Panel 2560 x 1080 200Hz
#define _DT_TEST_QHD_144HZ_650M                 0x92    // Dt-Test Panel 2560 x 1440 144Hz
#define _DT_TEST_WQHD_120HZ_690M                0x93    // Dt-Test Panel 3440 x 1440 120Hz
#define _DT_TEST_UHD_144HZ_1380M                0x94    // Dt-Test Panel 3840 x 2160 144Hz
#define _DT_TEST_QQHD_76HZ_1400M                0x95    // Dt-Test Panel 5120 x 2880 76Hz
#define _DT_TEST_8K4K_60HZ_2700M                0x96    // Dt-Test Panel 7680 x 4320 60Hz
#define _DT_TEST_QHD_240HZ_1100M                0x97    // Dt-Test Panel 2560 x 1440 240Hz
#define _DT_TEST_WQHD_180HZ_1020M               0x98    // Dt-Test Panel 3440 x 1440 180Hz
#define _DT_TEST_UHD_75HZ_750M                  0x99    // Dt-Test Panel 3840 x 2160 75Hz
#define _DT_TEST_QHD_360HZ_1760M                0x9A    // Dt-Test Panel 2560 x 1440 360Hz
#define _DT_TEST_UHD_160HZ_1530M                0x9B    // Dt-Test Panel 3840 x 2160 160Hz
#define _DT_TEST_UHD_240HZ_2380M                0x9C    // Dt-Test Panel 3840 x 2160 240Hz
#define _DT_TEST_5120X2160_120HZ_1427M          0x9D    // Dt-Test Panel 5120 x 2160 120Hz
#define _DT_TEST_QHD_60HZ_1066M                 0x9E    // Dt-Test Panel 2560 x 1440 60Hz DHtotal = 4 DHwidth
#define _DT_TEST_FHD_180HZ_436M                 0x9F    // Dt-Test Panel 1920 x 1080 180Hz
#define _DT_TEST_QHD_100HZ_415M                 0xA0    // Dt-Test Panel 2560 x 1440 100Hz
#define _DT_TEST_WQHD_75HZ_540M                 0xA1    // Dt-Test Panel 3440 x 1440 75Hz
#define _DT_TEST_UHD_60HZ_610M                  0xA2    // Dt-Test Panel 4096 x 2160 60Hz
#define _DT_TEST_QHD_180HZ_742M                 0xA3    // Dt-Test Panel 2560 x 1440 180Hz

//--------------------------------------------------
// Panel Led Driver List (Can Not Be 0xFF)
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_01_O2_OZ9913         0x01
#define _DEVICE_LED_DRIVER_02_AUSTRIA_AS3820    0x02
#define _DEVICE_LED_DRIVER_03_AUSTRIA_AS3812    0x03
#define _DEVICE_LED_DRIVER_04_AUSTRIA_AS3824    0x04
#define _DEVICE_LED_DRIVER_05_MBLOCK_MBI6353    0x05
#define _DEVICE_LED_DRIVER_06_MCU_1152_BOE      0x06

