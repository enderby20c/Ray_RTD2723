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

#if(_PANEL_TYPE == _INNOLUX_VBO_8K4K)
//----------------------------------------------------------------------------------------------------
// ID Code      : INNOLUX_VBO_8K4K.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_VBO
#define _PANEL_PIXEL_TYPE                       _PANEL_PIXEL_LCD

//--------------------------------------------------
// Definitions for VBO Panel Configuration
//--------------------------------------------------
#define _PANEL_VBO_BYTE_MODE                    _VBO_DISP_4_BYTE_MODE
#define _PANEL_VBO_OUTPUT_PORT                  _VBO_32_DATA_LANE
#define _PANEL_VBO_BIT_MODE                     _VBO_DISP_30_BIT
#define _PANEL_VBO_PANEL_SECTION                _VBO_PANEL_2_SECTION
#define _PANEL_VBO_HS_CONTROL                   _VBO_HS_INVERSE
#define _PANEL_VBO_VS_CONTROL                   _VBO_VS_INVERSE
#define _PANEL_VBO_VIDEO_TRANSFER_TYPE          _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK
#define _PANEL_CDR_TRANSFER_ALN_LATENCY         0

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_INNOLUX

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
#define _PANEL_DH_START                         160
#define _PANEL_DH_WIDTH                         7680
#define _PANEL_DH_END                           7840

#define _PANEL_DH_TOTAL                         8608 // 8704
#define _PANEL_DH_TOTAL_MAX                     8704
#define _PANEL_DH_TOTAL_MIN                     8448

#define _PANEL_DV_START                         10
#define _PANEL_DV_HEIGHT                        4320
#define _PANEL_DV_END                           4330

#define _PANEL_DV_TOTAL                         4380
#define _PANEL_DV_TOTAL_MAX                     4443
#define _PANEL_DV_TOTAL_MIN                     4352

#define _PANEL_DH_SYNC_WIDTH                    96
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      2272
#define _PANEL_PIXEL_CLOCK_MAX                  2360
#define _PANEL_PIXEL_CLOCK_MIN                  1966

#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      50
#define _PANEL_POWER_ON_T3                      500

#define _PANEL_POWER_OFF_T4                     100
#define _PANEL_POWER_OFF_T5                     50
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



/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _INNOLUX_VBO_8K4K)
