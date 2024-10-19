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
// ID Code      : User_Panel_include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Panel Include Path
//--------------------------------------------------
#if(_PANEL_TYPE == _PANEL_LVDS_EXAMPLE)
#include <EXAMPLE/PANEL_LVDS_EXAMPLE.h>
#elif(_PANEL_TYPE == _PANEL_DPTX_EXAMPLE)
#include <EXAMPLE/PANEL_DPTX_EXAMPLE.h>
#elif(_PANEL_TYPE == _PANEL_VBO_EXAMPLE)
#include <EXAMPLE/PANEL_VBO_EXAMPLE.h>
#elif(_PANEL_TYPE == _PANEL_TTL_EXAMPLE)
#include <EXAMPLE/PANEL_TTL_EXAMPLE.h>


#elif(_PANEL_TYPE == _MULTIPANEL_LVDS_21_5_WUXGA)
#include <04_MULTIPANEL_LVDS_21_5_WUXGA.h>
#elif(_PANEL_TYPE == _CMO_LVDS_17)
#include <00_CMO_LVDS_17.h>
#elif(_PANEL_TYPE == _CMO_LVDS_19_WXGA)
#include <01_CMO_LVDS_19_WXGA.h>
#elif(_PANEL_TYPE == _AU_LVDS_22_WSXGA)
#include <05_AU_LVDS_22_WSXGA.h>
#elif(_PANEL_TYPE == _AU_LVDS_22_WSXGA_QC)
#include <06_AU_LVDS_22_WSXGA_QC.h>
#elif(_PANEL_TYPE == _AU_LVDS_21_5_WUXGA)
#include <02_AU_LVDS_21_5_WUXGA.h>
#elif(_PANEL_TYPE == _AU_LVDS_21_5_WUXGA_FREESYNC)
#include <21_AU_LVDS_21_5_WUXGA_FREESYNC.h>
#elif(_PANEL_TYPE == _AU_DP_HBR2_21_5_WUXGA)
#include <32_AU_DP_HBR2_21_5_WUXGA.h>
#elif(_PANEL_TYPE == _AU_LVDS_23_WUXGA)
#include <07_AU_LVDS_23_WUXGA.h>
#elif(_PANEL_TYPE == _AU_LVDS_24_WUXGA)
#include <08_AU_LVDS_24_WUXGA.h>
#elif(_PANEL_TYPE == _AU_LVDS_27_WUXGA_FREESYNC)
#include <03_AU_LVDS_27_WUXGA_FREESYNC.h>
#elif(_PANEL_TYPE == _LG_LED_LVDS_27_WUXGA)
#include <14_LG_LED_LVDS_27_WUXGA.h>
#elif(_PANEL_TYPE == _LG_LED_LVDS_23_UHD)
#include <19_LG_LED_LVDS_23_UHD.h>
#elif(_PANEL_TYPE == _AUO_EDP_QHD_16ZONE)
#include <36_AU_DP_HBR2_QHD_1x16.h>
#elif(_PANEL_TYPE == _AU_LVDS_UHD_DOLBY_DUMP)
#include <77_AU_LVDS_UHD_DOLBY_DUMP.h>
#elif(_PANEL_TYPE == _RTK_EDP_9G_8K4K_2CHIP_FRONT)
#include <88_RTK_EDP_9G_8K4K_2CHIP_FRONT.h>
#elif(_PANEL_TYPE == _BOE_VBO_4K480)
#include <97_BOE_VBO_4K480.h>
#elif(_PANEL_TYPE == _BOE_VBO_4K240)
#include <98_BOE_VBO_4K240.h>
#elif(_PANEL_TYPE == _INNOLUX_VBO_8K4K)
#include <99_INNOLUX_VBO_8K4K.h>

#elif(_PANEL_TYPE == _MULTIPANEL_DP_QC)
#include <40_MULTIPANEL_DP_QC.h>
#elif(_PANEL_TYPE == _MULTIPANEL_DP_21_5_WUXGA)
#include <27_MULTIPANEL_DP_21_5_WUXGA.h>
#elif(_PANEL_TYPE == _AU_DP_21_5_WUXGA)
#include <09_AU_DP_21_5_WUXGA.h>
#elif(_PANEL_TYPE == _AU_DP_21_5_WUXGA_FREESYNC)
#include <25_AU_DP_21_5_WUXGA_FREESYNC.h>
#elif(_PANEL_TYPE == _LG_LED_DP_34_WFHD)
#include <29_LG_LED_DP_34_WFHD.h>
#elif(_PANEL_TYPE == _LG_LED_DP_17_QHD)
#include <28_LG_LED_DP_17_QHD.h>
#elif(_PANEL_TYPE == _LG_LED_DP_27_QHD)
#include <23_LG_LED_DP_27_QHD.h>
#elif(_PANEL_TYPE == _LG_LED_DP_27_QHD_QC)
#include <24_LG_LED_DP_27_QHD_QC.h>
#elif(_PANEL_TYPE == _SAMSUNG_LED_DP_15_6_UHD)
#include <15_SAMSUNG_LED_DP_15_6_UHD.h>
#elif(_PANEL_TYPE == _SAMSUNG_LED_DP_23_6_UHD)
#include <17_SAMSUNG_LED_DP_23_6_UHD.h>
#elif(_PANEL_TYPE == _LG_LED_DP_27_UHD)
#include <10_LG_LED_DP_27_UHD.h>
#elif(_PANEL_TYPE == _AUO_LED_DP_32_UHD)
#include <16_AUO_LED_DP_32_UHD.h>
#elif(_PANEL_TYPE == _LG_LED_DP_27_QQHD)
#include <22_LG_LED_DP_27_QQHD.h>
#elif(_PANEL_TYPE == _AUO_EDP_27_UHD_512ZONE)
#include <30_AUO_eDP_27_UHD_512ZONE.h>
#elif(_PANEL_TYPE == _AUO_VBO_27_WUXGA_FREESYNC)
#include <31_AUO_VBO_27_WUXGA_FREESYNC.h>
#elif(_PANEL_TYPE == _AUO_VBO_M250HTN01_0)
#include <66_AUO_VBO_M250HTN01_0.h>
#elif(_PANEL_TYPE == _INNOLUX_LED_VBO_28_UHD)
#include <18_INNOLUX_LED_VBO_28_UHD.h>
#elif(_PANEL_TYPE == _INNOLUX_LED_VBO_40_UHD)
#include <20_INNOLUX_LED_VBO_40_UHD.h>
#elif(_PANEL_TYPE == _INNOLUX_LED_VBO_28_UHD_FREESYNC)
#include <33_INNOLUX_LED_VBO_28_UHD_FREESYNC.h>
#elif(_PANEL_TYPE == _INNOLUX_LED_VBO_16X9_144ZONE)
#include <34_INNOLUX_LED_VBO_16x9_144ZONE.h>
#elif(_PANEL_TYPE == _AUO_EDP_27_UHD_16X2_ZONE)
#include <35_AUO_eDP_27_UHD_16x2_ZONE.h>
#elif(_PANEL_TYPE == _AUO_LED_EDP_43_UHD_8X2_ZONE)
#include <37_AUO_LED_eDP_43_UHD_8x2_ZONE.h>
#elif(_PANEL_TYPE == _BOE_LED_DPTX_27_1152_ZONE)
#include <38_BOE_LED_DPTX_27_1152_ZONE.h>
#elif(_PANEL_TYPE == _BOE_EDP_34_WQHD_EO)
#include <42_BOE_eDP_34_WQHD_EO.h>
#elif(_PANEL_TYPE == _INNOLUX_TTL_7)
#include <26_INNOLUX_TTL_7.h>
#elif(_PANEL_TYPE == _DT_TEST_FHD_144HZ_350M)
#include <50_DT_TEST_FHD_144HZ_350M.h>
#elif(_PANEL_TYPE == _DT_TEST_WFHD_200HZ_653M)
#include <51_DT_TEST_WFHD_200HZ_653M.h>
#elif(_PANEL_TYPE == _DT_TEST_QHD_144HZ_650M)
#include <52_DT_TEST_QHD_144HZ_650M.h>
#elif(_PANEL_TYPE == _DT_TEST_WQHD_120HZ_690M)
#include <53_DT_TEST_WQHD_120HZ_690M.h>
#elif(_PANEL_TYPE == _DT_TEST_UHD_144HZ_1380M)
#include <54_DT_TEST_UHD_144HZ_1380M.h>
#elif(_PANEL_TYPE == _DT_TEST_QQHD_76HZ_1400M)
#include <55_DT_TEST_QQHD_76HZ_1400M.h>
#elif(_PANEL_TYPE == _DT_TEST_8K4K_60HZ_2700M)
#include <56_DT_TEST_8K4K_60HZ_2700M.h>
#elif(_PANEL_TYPE == _DT_TEST_QHD_240HZ_1100M)
#include <57_DT_TEST_QHD_240HZ_1100M.h>
#elif(_PANEL_TYPE == _DT_TEST_WQHD_180HZ_1020M)
#include <58_DT_TEST_WQHD_180HZ_1020M.h>
#elif(_PANEL_TYPE == _DT_TEST_UHD_75HZ_750M)
#include <59_DT_TEST_UHD_75HZ_750M.h>
#elif(_PANEL_TYPE == _DT_TEST_QHD_360HZ_1760M)
#include <60_DT_TEST_QHD_360HZ_1760M.h>
#elif(_PANEL_TYPE == _DT_TEST_UHD_160HZ_1530M)
#include <61_DT_TEST_UHD_160HZ_1530M.h>
#elif(_PANEL_TYPE == _DT_TEST_UHD_240HZ_2380M)
#include <62_DT_TEST_UHD_240HZ_2380M.h>
#elif(_PANEL_TYPE == _DT_TEST_5120X2160_120HZ_1427M)
#include <63_DT_TEST_5120X2160_120HZ_1427M.h>
#elif(_PANEL_TYPE == _DT_TEST_QHD_60HZ_1066M)
#include <70_DT_TEST_QHD_60HZ_1066M.h>
#elif(_PANEL_TYPE == _DT_TEST_FHD_180HZ_436M)
#include <71_DT_TEST_FHD_180HZ_436M.h>
#elif(_PANEL_TYPE == _DT_TEST_QHD_100HZ_415M)
#include <72_DT_TEST_QHD_100HZ_415M.h>
#elif(_PANEL_TYPE == _DT_TEST_WQHD_75HZ_540M)
#include <73_DT_TEST_WQHD_75HZ_540M.h>
#elif(_PANEL_TYPE == _DT_TEST_UHD_60HZ_610M)
#include <74_DT_TEST_UHD_60HZ_610M.h>
#elif(_PANEL_TYPE == _DT_TEST_QHD_180HZ_742M)
#include <75_DT_TEST_QHD_180HZ_742M.h>

#else
#include <EXAMPLE/PANEL_NONE.h>
#endif

