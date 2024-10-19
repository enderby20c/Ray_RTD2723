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

#if(_PANEL_TYPE == _DT_TEST_8K4K_60HZ_2700M)
//----------------------------------------------------------------------------------------------------
// ID Code      : 56_DT_TEST_8K4K.h No.0000
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
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_16
#define _PANEL_DPTX_PORT_NUMBER_SEL             _DPTX_TX1_PORT
#define _PANEL_DPTX_PANEL_SECTION               _DPTX_PANEL_4_SECTION

#if(_DRR_SUPPORT == _ON)
#define _PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN    _ENABLE
#endif

//--------------------------------------------------
// Definitions for DPTx Panel Force Output Parameters
//--------------------------------------------------
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT        _ON
#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING   _ENABLE
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD       _ENABLE
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
#define _PANEL_MAX_FRAME_RATE                   600
#define _PANEL_MIN_FRAME_RATE                   400

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_DP_FREESYNC_MAX_FRAME_RATE       600
#define _PANEL_DP_FREESYNC_MIN_FRAME_RATE       400

#define _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE     600
#define _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE     400

#define _PANEL_HDMI21_VRR_MAX_FRAME_RATE        600
#define _PANEL_HDMI21_VRR_MIN_FRAME_RATE        400



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
#define _PANEL_DH_TOTAL_MAX                     8608 // 8704
#define _PANEL_DH_TOTAL_MIN                     8448

#define _PANEL_DV_START                         10
#define _PANEL_DV_HEIGHT                        4320
#define _PANEL_DV_END                           4330

#define _PANEL_DV_TOTAL                         4380
#define _PANEL_DV_TOTAL_MAX                     6700 // 4443
#define _PANEL_DV_TOTAL_MIN                     4352

#define _PANEL_DH_SYNC_WIDTH                    96
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      2272
#define _PANEL_PIXEL_CLOCK_MAX                  2700 // 2360
#define _PANEL_PIXEL_CLOCK_MIN                  1000 // 1966

#define _PANEL_POWER_ON_T1                      10
#define _PANEL_POWER_ON_T2                      50
#define _PANEL_POWER_ON_T3                      500

#define _PANEL_POWER_OFF_T4                     100
#define _PANEL_POWER_OFF_T5                     50
#define _PANEL_POWER_OFF_T6                     500


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

#endif // End of #if(_PANEL_TYPE == _DT_TEST_8K4K_60HZ_2700M)
