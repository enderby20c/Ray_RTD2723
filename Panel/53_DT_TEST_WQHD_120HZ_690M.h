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

#if(_PANEL_TYPE == _DT_TEST_WQHD_120HZ_690M)
//----------------------------------------------------------------------------------------------------
// ID Code      : 53_DT_TEST_WQHD.h No.0000
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
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR2
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_4
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_004F1H
#define _PANEL_DPTX_PANEL_SECTION               _DPTX_PANEL_1_SECTION

#if(_DRR_SUPPORT == _ON)
#define _PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN    _ENABLE
#endif

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
#define _PANEL_MANUFACTURER                     _PANEL_BOE

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   1200
#define _PANEL_MIN_FRAME_RATE                   400

#define _PANEL_DP_FREESYNC_MAX_FRAME_RATE       1200
#define _PANEL_DP_FREESYNC_MIN_FRAME_RATE       400

#define _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE     1200
#define _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE     400

#define _PANEL_HDMI21_VRR_MAX_FRAME_RATE        1200
#define _PANEL_HDMI21_VRR_MIN_FRAME_RATE        400

///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48                  // Display Horizontal Start Position
#define _PANEL_DH_WIDTH                         3440                // Display Horizontal Width
#define _PANEL_DH_END                           3488                // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         3800                // Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     4912                // Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     3620                // Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        1440                // Display Vertical Width
#define _PANEL_DV_END                           1446                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         1468                // Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     4500
#define _PANEL_DV_TOTAL_MIN                     1466                // Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   3                   // Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      430                 // Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  690 // 436          // Maxinum Pixel Clock in MHz500//
#define _PANEL_PIXEL_CLOCK_MIN                  100 // 424          // Mininum Pixel Clock in MHz300//


#define _PANEL_POWER_ON_T1                      10                  // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      200                 // Panel Power On T2 (ms)
#define _PANEL_POWER_ON_T3                      300                 // Panel Power On T3 (ms)

#define _PANEL_POWER_OFF_T4                     250                 // Panel Power Off T4 (ms)
#define _PANEL_POWER_OFF_T5                     20                  // Panel Power Off T5 (ms)
#define _PANEL_POWER_OFF_T6                     1000                // Panel Power Off T6 (ms)

/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _PANEL_LAST_LINE_MAX                    150
#define _PANEL_LAST_LINE_MIN                    50

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _PANEL_FRAME_SYNC_MARGIN                10

//--------------------------------------------------
// Definitions for panel DVtotal adjust limit
//--------------------------------------------------
#define _PANEL_DV_LINE_CHG_LIMIT                (_PANEL_DV_TOTAL)

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
#define _PANEL_ADC_OFFSET_BIAS                  (3) // 0~5
#define _PANEL_ADC_GAIN_BIAS                    (0) // -5~0


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

#endif // End of #if(_PANEL_TYPE == _DT_TEST_WQHD_120HZ_690M)

