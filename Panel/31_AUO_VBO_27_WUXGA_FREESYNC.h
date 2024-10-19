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

#if(_PANEL_TYPE == _AUO_VBO_27_WUXGA_FREESYNC)
//----------------------------------------------------------------------------------------------------
// ID Code      : _AUO_VBO_27_WUXGA_FREESYNC.h No.0000
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
#define _PANEL_VBO_BYTE_MODE                    _VBO_DISP_3_BYTE_MODE
#define _PANEL_VBO_OUTPUT_PORT                  _VBO_8_DATA_LANE
#define _PANEL_VBO_BIT_MODE                     _VBO_DISP_24_BIT
#define _PANEL_VBO_PANEL_SECTION                _VBO_PANEL_2_SECTION
#define _PANEL_VBO_HS_CONTROL                   _VBO_HS_NORMAL
#define _PANEL_VBO_VS_CONTROL                   _VBO_VS_NORMAL
#define _PANEL_VBO_VIDEO_TRANSFER_TYPE          _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK
#define _PANEL_CDR_TRANSFER_ALN_LATENCY         0

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
#define _PANEL_TYP_FRAME_RATE                   2000
#define _PANEL_MAX_FRAME_RATE                   2400
#define _PANEL_MIN_FRAME_RATE                   480

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_DP_FREESYNC_MAX_FRAME_RATE       2400
#define _PANEL_DP_FREESYNC_MIN_FRAME_RATE       480

#define _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE     240
#define _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE     480

#define _PANEL_HDMI21_VRR_MAX_FRAME_RATE        1440
#define _PANEL_HDMI21_VRR_MIN_FRAME_RATE        480

///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48
#define _PANEL_DH_WIDTH                         1920
#define _PANEL_DH_END                           1968

#define _PANEL_DH_TOTAL                         2160
#define _PANEL_DH_TOTAL_MAX                     4088
#define _PANEL_DH_TOTAL_MIN                     2152

#define _PANEL_DV_START                         6
#define _PANEL_DV_HEIGHT                        1080
#define _PANEL_DV_END                           1086

#define _PANEL_DV_TOTAL                         1315
#define _PANEL_DV_TOTAL_MAX                     6600
#define _PANEL_DV_TOTAL_MIN                     1100

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      568
#define _PANEL_PIXEL_CLOCK_MAX                  620
#define _PANEL_PIXEL_CLOCK_MIN                  536

#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      40
#define _PANEL_POWER_ON_T3                      610

#define _PANEL_POWER_OFF_T4                     130
#define _PANEL_POWER_OFF_T5                     20
#define _PANEL_POWER_OFF_T6                     1100


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

#endif // End of #if(_PANEL_TYPE == _AUO_VBO_27_WUXGA_FREESYNC)
