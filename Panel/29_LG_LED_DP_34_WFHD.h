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

#if(_PANEL_TYPE == _LG_LED_DP_34_WFHD)
//----------------------------------------------------------------------------------------------------
// ID Code      : _LG_LED_DP_34_WFHD.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX
#define _PANEL_PIXEL_TYPE                       _PANEL_PIXEL_LCD

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_4
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE
#define _PANEL_DPTX_PANEL_SECTION               _DPTX_PANEL_1_SECTION

//--------------------------------------------------
// Definitions for DPTx Panel Force Output Parameters
//--------------------------------------------------
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT        _OFF
#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING   _DISABLE
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD       _DISABLE
#define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP    _DISABLE
#define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP      _DISABLE

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_AUO

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   650
#define _PANEL_MIN_FRAME_RATE                   550


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48
#define _PANEL_DH_WIDTH                         2560
#define _PANEL_DH_END                           2608

#define _PANEL_DH_TOTAL                         2720
#define _PANEL_DH_TOTAL_MAX                     2880
#define _PANEL_DH_TOTAL_MIN                     2720

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        1080
#define _PANEL_DV_END                           1086

#define _PANEL_DV_TOTAL                         1130
#define _PANEL_DV_TOTAL_MAX                     1140
#define _PANEL_DV_TOTAL_MIN                     1120

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      184
#define _PANEL_PIXEL_CLOCK_MAX                  199
#define _PANEL_PIXEL_CLOCK_MIN                  169

#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      150
#define _PANEL_POWER_ON_T3                      250

#define _PANEL_POWER_OFF_T4                     200
#define _PANEL_POWER_OFF_T5                     40
#define _PANEL_POWER_OFF_T6                     1000


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _PANEL_LAST_LINE_MAX                    (_PANEL_DH_TOTAL - 200)
#define _PANEL_LAST_LINE_MIN                    (_PANEL_DH_TOTAL - 400)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _PANEL_FRAME_SYNC_MARGIN                20

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                  (0)
#define _PANEL_ADC_GAIN_BIAS                    (0)


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// Definitions for Local Dimming
//--------------------------------------------------

//--------------------------------------------------
// Definitions for Global Dimming
//--------------------------------------------------
#include <RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/GDPanelPara.h>
#define _GLOBAL_DIMMING_STEP_R_TABLE            "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tStepRTable.h"
#define _GLOBAL_DIMMING_PWM_LUT_TABLE           "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tPWMLUT.h"

#define _GLOBAL_DIMMING_HDR_TONE_MAPPING_LV540  "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tHDRToneMappingLv540.h"
#define _GLOBAL_DIMMING_HDR_2084_LV             "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tHDR2084Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_22_LV         "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tSDRGamma22Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_24_LV         "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tSDRGamma24Lv.h"
#define _GLOBAL_DIMMING_SDR_GAMMA_26_LV         "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tSDRGamma26Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_1_LV       "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tSDROGCCase1Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_2_LV       "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tSDROGCCase2Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_3_LV       "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tSDROGCCase3Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_4_LV       "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tSDROGCCase4Lv.h"
#define _GLOBAL_DIMMING_SDR_OGC_CASE_5_LV       "./RTDGlobalDimmingTable/29_LG_LED_DP_34_WFHD/tSDROGCCase5Lv.h"
//--------------------------------------------------
// Definitions for Driver IC
//--------------------------------------------------

#define _DEVICE_LED_DRIVER_TYPE                 _DEVICE_LED_DRIVER_01_O2_OZ9913
#include <User_LedDriver_Include.h>


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// Definitions for Display HDR
//--------------------------------------------------
#define _PANEL_MAX_LUMINANCE                    0x62 // from OGC Tool
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE      0x62 // from OGC Tool
#define _PANEL_MAX_USER_DEFINE_LUMINANCE        0x62 // from OGC Tool
#define _PANEL_MIN_LUMINANCE                    0x27 // from OGC Tool

/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _AU_LVDS_21_5_WUXGA)
