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

#if(_PANEL_TYPE == _LG_LED_LVDS_27_WUXGA)
//----------------------------------------------------------------------------------------------------
// ID Code      : _LG_LED_LVDS_27_WUXGA.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_LVDS
#define _PANEL_PIXEL_TYPE                       _PANEL_PIXEL_LCD

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#define _PANEL_LVDS_OUTPUT_PORT                 _LVDS_4_PORT
#define _PANEL_LVDS_PANEL_SECTION               _LVDS_PANEL_1_SECTION
#define _PANEL_LVDS_TABLE_TYPE                  _LVDS_BIT_MAP_TABLE_1_3

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
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_30_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   610
#define _PANEL_MIN_FRAME_RATE                   590


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
#define _PANEL_DH_TOTAL_MAX                     2736
#define _PANEL_DH_TOTAL_MIN                     2704

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        1440
#define _PANEL_DV_END                           1446

#define _PANEL_DV_TOTAL                         1481
#define _PANEL_DV_TOTAL_MAX                     1483
#define _PANEL_DV_TOTAL_MIN                     1479

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      242
#define _PANEL_PIXEL_CLOCK_MAX                  280
#define _PANEL_PIXEL_CLOCK_MIN                  210


#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      50
#define _PANEL_POWER_ON_T3                      500

#define _PANEL_POWER_OFF_T4                     200
#define _PANEL_POWER_OFF_T5                     50
#define _PANEL_POWER_OFF_T6                     1000


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _PANEL_LAST_LINE_MAX                    (_PANEL_DH_TOTAL - 150)
#define _PANEL_LAST_LINE_MIN                    (_PANEL_DH_TOTAL - 250)

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



/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif// End of #if(_PANEL_TYPE == _LG_LED_LVDS_27_WUXGA)
