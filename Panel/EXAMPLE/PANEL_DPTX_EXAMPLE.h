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

#if(_PANEL_TYPE == _PANEL_DPTX_EXAMPLE)
//----------------------------------------------------------------------------------------------------
// ID Code      : _PANEL_DPTX_EXAMPLE.h No.0000
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
#define _PANEL_DPTX_PORT_NUMBER_SEL             _DPTX_TX1_PORT
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE
#define _PANEL_DPTX_PANEL_SECTION               _DPTX_PANEL_1_SECTION
#define _PANEL_DPTX_LINK_SEQUENCE_SWAP          _OFF
#define _PANEL_DPTX_AUX_SET_TP_END_SEQUENCE     _TRAIN_PATTERN_END_BEFORE_IDEL_PATTERN
#define _PANEL_DPTX_HPD_DETECT                  _OFF
#define _PANEL_DPTX_HPD_UNPLUG_TIME             _DPTX_HPD_TIME_30_MS
#define _PANEL_DPTX_IRQ_HPD_DETECT              _OFF
#define _PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN    _DISABLE

//--------------------------------------------------
// Definitions for DPTx Panel Force Output Parameters
//--------------------------------------------------
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT        _OFF
#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING   _DISABLE
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD       _DISABLE
#define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP    _DISABLE
#define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP      _DISABLE
#define _PANEL_DPTX_FORCE_SSCG_SUPPORT          _DISABLE

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_NONE_BRAND

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   860
#define _PANEL_MIN_FRAME_RATE                   460

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_DP_FREESYNC_MAX_FRAME_RATE       1440
#define _PANEL_DP_FREESYNC_MIN_FRAME_RATE       300

#define _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE     1440
#define _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE     300

#define _PANEL_HDMI21_VRR_MAX_FRAME_RATE        1440
#define _PANEL_HDMI21_VRR_MIN_FRAME_RATE        300

///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48                  // Display Horizontal Start Position
#define _PANEL_DH_WIDTH                         1920                // Display Horizontal Width
#define _PANEL_DH_END                           1968                // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         2100                // Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     2200                // Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     2048                // Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        1080                // Display Vertical Width
#define _PANEL_DV_END                           1086                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         1150                // Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     1600                // Maxinum Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MIN                     1100                // Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   2                   // Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      144                 // Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  230                 // Maxinum Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MIN                  110                 // Mininum Pixel Clock in MHz

#define _PANEL_POWER_ON_T1                      100                 // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      40                  // Panel Power On T2 (ms)
#define _PANEL_POWER_ON_T3                      300                 // Panel Power On T3 (ms)

#define _PANEL_POWER_OFF_T4                     20                  // Panel Power Off T4 (ms)
#define _PANEL_POWER_OFF_T5                     40                  // Panel Power Off T5 (ms)
#define _PANEL_POWER_OFF_T6                     600                 // Panel Power Off T6 (ms)


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _PANEL_LAST_LINE_MAX                    (_PANEL_DH_TOTAL - 100)
#define _PANEL_LAST_LINE_MIN                    (_PANEL_DH_TOTAL - 200)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _PANEL_FRAME_SYNC_MARGIN                0

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
#define _PANEL_ADC_OFFSET_BIAS                  (0) // 0~5
#define _PANEL_ADC_GAIN_BIAS                    (0) // -5~0


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#define _I_DITHER_TEMP                          _ENABLE

#if((_HW_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
#define _I_DITHER_VALUE_SIGN                    _DISABLE
#define _I_DITHER_V_FRAME_MOD                   _DISABLE
#define _I_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#if((_HW_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) ||\
    (_HW_IDITHER_TYPE == _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
#define _I_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _I_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#define _I_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _I_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _I_DITHER_SEQ_INV_MODE                  0
#endif

#if(_HW_IDITHER_SUPER_PIXEL_SUPPORT == _ON)
#define _I_DITHER_SUPER_PIXEL_SIZE              _IDITHER_SUPER_PIXEL_2X2
#endif

#define _I_DITHER_12_TO_10_TEMP                 _I_DITHER_TEMP
#define _I_DITHER_12_TO_10_VALUE_SIGN           _I_DITHER_VALUE_SIGN
#define _I_DITHER_12_TO_10_V_FRAME_MOD          _I_DITHER_V_FRAME_MOD
#define _I_DITHER_12_TO_10_H_FRAME_MOD          _I_DITHER_H_FRAME_MOD
#define _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE     _I_DITHER_MULTI_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE     _I_DITHER_SHARE_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE    _I_DITHER_SERIES_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_ENABLE       _I_DITHER_SEQ_INV_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_MODE         _I_DITHER_SEQ_INV_MODE // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#define _D_DITHER_TEMP                          _ENABLE

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#define _D_DITHER_V_FRAME_MOD                   _DISABLE
#define _D_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#define _D_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _D_DITHER_SEQ_INV_MODE                  0 // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#define _D_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _D_DITHER_ADVANCE_SETTING_ENABLE        _DISABLE
#endif

#endif // End of #if(_PANEL_TYPE == _PANEL_DPTX_EXAMPLE)
