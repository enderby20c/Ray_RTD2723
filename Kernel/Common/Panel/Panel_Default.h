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
// ID Code      : Panel_Default.h No.0000
// Update Note  :
//-----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#ifndef _PANEL_STYLE
#define _PANEL_STYLE                                    _PANEL_NONE
#endif

#ifndef _PANEL_PIXEL_TYPE
#define _PANEL_PIXEL_TYPE                               _PANEL_PIXEL_LCD
#endif

//--------------------------------------------------
// Definitions for Backlight Style
//--------------------------------------------------
#ifndef _PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE
#define _PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE       _PANEL_OLED_AC_DET_CTRL_WITHOUT_SEQ
#endif

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#ifndef _PANEL_LVDS_OUTPUT_PORT
#define _PANEL_LVDS_OUTPUT_PORT                         _LVDS_2_PORT
#endif

#ifndef _PANEL_LVDS_PANEL_SECTION
#define _PANEL_LVDS_PANEL_SECTION                       _LVDS_PANEL_1_SECTION
#endif

#ifndef _PANEL_LVDS_TABLE_TYPE
#define _PANEL_LVDS_TABLE_TYPE                          _LVDS_BIT_MAP_TABLE_1_3
#endif

#ifndef _PANEL_LVDS_CABLE_TYPE
#define _PANEL_LVDS_CABLE_TYPE                          _LVDS_CABLE_TYPE_0
#endif

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#ifndef _PANEL_DPTX_LINK_RATE
#define _PANEL_DPTX_LINK_RATE                           _PANEL_DPTX_LINK_HBR
#endif

#ifndef _PANEL_DPTX_LANE_NUMBER
#define _PANEL_DPTX_LANE_NUMBER                         _PANEL_DPTX_LANE_NUMBER_4
#endif

#ifndef _PANEL_DPTX_PANEL_SECTION
#define _PANEL_DPTX_PANEL_SECTION                       _DPTX_PANEL_1_SECTION
#endif

#ifndef _PANEL_DPTX_PORT_NUMBER_SEL
#define _PANEL_DPTX_PORT_NUMBER_SEL                     _DPTX_TX1_PORT
#endif

#ifndef _PANEL_DPTX_VENDOR_SPECIFIC_TYPE
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE                _PANEL_DPTX_VENDOR_SPECIFIC_NONE
#endif

#ifndef _PANEL_DPTX_LINK_SEQUENCE_SWAP
#define _PANEL_DPTX_LINK_SEQUENCE_SWAP                  _OFF
#endif

#ifndef _PANEL_DPTX_SCRAMBLE_SEED_TYPE
#define _PANEL_DPTX_SCRAMBLE_SEED_TYPE                  _PANEL_DPTX_SCRAMBLE_SEED_AUTO
#endif

#ifndef _PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE
#define _PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE            _PANEL_DPTX_LT_MANUAL_MODE
#endif

#ifndef _PANEL_DPTX_FORCE_OUTPUT_SUPPORT
#define _PANEL_DPTX_FORCE_OUTPUT_SUPPORT                _OFF
#endif

#ifndef _PANEL_DPTX_FORCE_SSCG_SUPPORT
#define _PANEL_DPTX_FORCE_SSCG_SUPPORT                  _OFF
#endif

#ifndef _PANEL_DPTX_LT_TPS3_SUPPORT_BY_USER
#define _PANEL_DPTX_LT_TPS3_SUPPORT_BY_USER             _ON
#endif

#ifndef _PANEL_DPTX_LT_TPS4_SUPPORT_BY_USER
#define _PANEL_DPTX_LT_TPS4_SUPPORT_BY_USER             _ON
#endif

#ifndef _PANEL_DPTX_AUX_SET_TP_END_SEQUENCE
#define _PANEL_DPTX_AUX_SET_TP_END_SEQUENCE             _TRAIN_PATTERN_END_BEFORE_IDEL_PATTERN
#endif

#ifndef _PANEL_DPTX_SET_HPD_DETECT_SEQUENCE
#define _PANEL_DPTX_SET_HPD_DETECT_SEQUENCE             _HPD_DETECT_AFTER_VIDEO_STREAM
#endif

#ifndef _PANEL_DPTX_HPD_DETECT
#define _PANEL_DPTX_HPD_DETECT                          _OFF
#endif

#ifndef _PANEL_DPTX_HPD_UNPLUG_TIME
#define _PANEL_DPTX_HPD_UNPLUG_TIME                     _DPTX_HPD_TIME_30_MS
#endif

#ifndef _PANEL_DPTX_IRQ_HPD_DETECT
#define _PANEL_DPTX_IRQ_HPD_DETECT                      _OFF
#endif

#ifndef _PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN
#define _PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN            _DISABLE
#endif

#ifndef _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
#define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING           _DISABLE
#endif

#ifndef _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
#define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD               _DISABLE
#endif

#ifndef _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
#define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP            _DISABLE
#endif

#ifndef _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP
#define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP              _DISABLE
#endif

//--------------------------------------------------
// Definitions for TTL Panel Configuration
//--------------------------------------------------
#ifndef _PANEL_TTL_OUTPUT_PORT
#define _PANEL_TTL_OUTPUT_PORT                          _TTL_2_PORT
#endif

//--------------------------------------------------
// Definitions for VBO Panel Configuration
//--------------------------------------------------
#ifndef _PANEL_VBO_BYTE_MODE
#define _PANEL_VBO_BYTE_MODE                            _VBO_DISP_4_BYTE_MODE
#endif

#ifndef _PANEL_VBO_OUTPUT_PORT
#define _PANEL_VBO_OUTPUT_PORT                          _VBO_8_DATA_LANE
#endif

#ifndef _PANEL_VBO_BIT_MODE
#define _PANEL_VBO_BIT_MODE                             _VBO_DISP_30_BIT
#endif

#ifndef _PANEL_VBO_PANEL_SECTION
#define _PANEL_VBO_PANEL_SECTION                        _VBO_PANEL_1_SECTION
#endif

#ifndef _PANEL_VBO_HS_CONTROL
#define _PANEL_VBO_HS_CONTROL                           _VBO_HS_NORMAL
#endif

#ifndef _PANEL_VBO_VS_CONTROL
#define _PANEL_VBO_VS_CONTROL                           _VBO_VS_NORMAL
#endif

#ifndef _PANEL_VBO_VIDEO_TRANSFER_TYPE
#define _PANEL_VBO_VIDEO_TRANSFER_TYPE                  _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK
#endif

#ifndef _PANEL_CDR_TRANSFER_ALN_LATENCY
#define _PANEL_CDR_TRANSFER_ALN_LATENCY                 0
#endif

#ifndef _PANEL_VBO_CHANGE_CLK_RESET_TYPE
#define _PANEL_VBO_CHANGE_CLK_RESET_TYPE                _VBO_CHANGE_CLK_RESET_BY_PANEL_OFF
#endif

#ifndef _PANEL_VBO_LANE_SKEW_RESET_TYPE
#define _PANEL_VBO_LANE_SKEW_RESET_TYPE                 _VBO_LANE_SKEW_RESET_BY_CK_USABLE
#endif

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#ifndef _PANEL_EXIST_MULTIPANEL
#define _PANEL_EXIST_MULTIPANEL                         _OFF
#endif

#ifndef _PANEL_MULTIPANEL_VARIABLE
#define _PANEL_MULTIPANEL_VARIABLE                      _OFF
#endif

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#ifndef _PANEL_MANUFACTURER
#define _PANEL_MANUFACTURER                             _PANEL_NONE_BRAND
#endif

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#ifndef _PANEL_DISP_BIT_MODE
#define _PANEL_DISP_BIT_MODE                            _PANEL_DISP_24_BIT
#endif

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0    .1 Hz)
//--------------------------------------------------
#ifndef _PANEL_TYP_FRAME_RATE
#define _PANEL_TYP_FRAME_RATE                           600
#endif

#ifndef _PANEL_MAX_FRAME_RATE
#define _PANEL_MAX_FRAME_RATE                           860
#endif

#ifndef _PANEL_MIN_FRAME_RATE
#define _PANEL_MIN_FRAME_RATE                           460
#endif

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate     (Unit: 0.1 Hz)
//--------------------------------------------------
#ifndef _PANEL_DP_FREESYNC_MAX_FRAME_RATE
#define _PANEL_DP_FREESYNC_MAX_FRAME_RATE               1440
#endif

#ifndef _PANEL_DP_FREESYNC_MIN_FRAME_RATE
#define _PANEL_DP_FREESYNC_MIN_FRAME_RATE               300
#endif

#ifndef _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE
#define _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE             1440
#endif

#ifndef _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE
#define _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE             300
#endif

#ifndef _PANEL_HDMI21_VRR_MAX_FRAME_RATE
#define _PANEL_HDMI21_VRR_MAX_FRAME_RATE                1440
#endif

#ifndef _PANEL_HDMI21_VRR_MIN_FRAME_RATE
#define _PANEL_HDMI21_VRR_MIN_FRAME_RATE                300
#endif



///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#ifndef _PANEL_DH_START
#define _PANEL_DH_START                                 48                  // Display Horizontal Start Position
#endif

#ifndef _PANEL_DH_WIDTH
#define _PANEL_DH_WIDTH                                 1920                // Display Horizontal Width
#endif

#ifndef _PANEL_DH_END
#define _PANEL_DH_END                                   1968                // Display Horizontal End Position
#endif

#ifndef _PANEL_DH_TOTAL
#define _PANEL_DH_TOTAL                                 2100                // Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_TOTAL_MAX
#define _PANEL_DH_TOTAL_MAX                             2200                // Maxinum Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_TOTAL_MIN
#define _PANEL_DH_TOTAL_MIN                             2048                // Mininum Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_START
#define _PANEL_DV_START                                 6                   // Display Vertical Start Position
#endif

#ifndef _PANEL_DV_HEIGHT
#define _PANEL_DV_HEIGHT                                1080                // Display Vertical Width
#endif

#ifndef _PANEL_DV_END
#define _PANEL_DV_END                                   1086                // Display Vertical End Position
#endif

#ifndef _PANEL_DV_TOTAL
#define _PANEL_DV_TOTAL                                 1150                // Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_TOTAL_MAX
#define _PANEL_DV_TOTAL_MAX                             1600                // Maxinum Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_TOTAL_MIN
#define _PANEL_DV_TOTAL_MIN                             1100                // Mininum Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_SYNC_WIDTH
#define _PANEL_DH_SYNC_WIDTH                            8                   // Display Horizontal Sync Width
#endif

#ifndef _PANEL_DV_SYNC_HEIGHT
#define _PANEL_DV_SYNC_HEIGHT                           2                   // Display Vertical Sync Height
#endif

#ifndef _PANEL_PIXEL_CLOCK
#define _PANEL_PIXEL_CLOCK                              144                 // Typical Pixel Clock in MHz
#endif

#ifndef _PANEL_PIXEL_CLOCK_MAX
#define _PANEL_PIXEL_CLOCK_MAX                          230                 // Maxinum Pixel Clock in MHz
#endif

#ifndef _PANEL_PIXEL_CLOCK_MIN
#define _PANEL_PIXEL_CLOCK_MIN                          110                 // Mininum Pixel Clock in MHz
#endif

#ifndef _PANEL_POWER_ON_T1
#define _PANEL_POWER_ON_T1                              100                 // Panel Power On T1 (ms)
#endif

#ifndef _PANEL_POWER_ON_T2
#define _PANEL_POWER_ON_T2                              40                  // Panel Power On T2 (ms)
#endif

#ifndef _PANEL_POWER_ON_T3
#define _PANEL_POWER_ON_T3                              300                 // Panel Power On T3 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T4
#define _PANEL_POWER_OFF_T4                             20                  // Panel Power Off T4 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T5
#define _PANEL_POWER_OFF_T5                             40                  // Panel Power Off T5 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T6
#define _PANEL_POWER_OFF_T6                             600                 // Panel Power Off T6 (ms)
#endif


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Enable
//--------------------------------------------------
#ifndef _PANEL_LAST_LINE_FINETUNE_ENABLE
#define _PANEL_LAST_LINE_FINETUNE_ENABLE                _ENABLE
#endif

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#ifndef _PANEL_LAST_LINE_MAX
#define _PANEL_LAST_LINE_MAX                            (_PANEL_DH_TOTAL - 100)
#endif

#ifndef _PANEL_LAST_LINE_MIN
#define _PANEL_LAST_LINE_MIN                            (_PANEL_DH_TOTAL - 200)
#endif

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#ifndef _PANEL_FRAME_SYNC_MARGIN
#define _PANEL_FRAME_SYNC_MARGIN                        0
#endif

//-------------------------------------------------
// Display PLL Jitter Margin
//-------------------------------------------------
#ifndef _DPLL_JITTER_MARGIN
#define _DPLL_JITTER_MARGIN                             _DPLL_NO_JITTER_MARGIN
#endif

//--------------------------------------------------
// Definitions for panel DVtotal adjust limit
//--------------------------------------------------
#ifndef _PANEL_DV_LINE_CHG_LIMIT
#define _PANEL_DV_LINE_CHG_LIMIT                        (_PANEL_DV_TOTAL)
#endif

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#ifndef _PANEL_PIXEL_CLOCK_UNIT
#define _PANEL_PIXEL_CLOCK_UNIT                         _PANEL_CLOCK_MHZ
#endif

//--------------------------------------------------
// Definitions for fine tune margin Frame Sync line     buffer dvtotal
//--------------------------------------------------
#ifndef _PANEL_DV_TOTAL_FINE_TUNE_MARGIN
#define _PANEL_DV_TOTAL_FINE_TUNE_MARGIN                0
#endif

#ifndef _PANEL_FRONT_PORCH_LIMIT
#define _PANEL_FRONT_PORCH_LIMIT                        4
#endif

//-------------------------------------------------
// Free Run Dclk Setting
//-------------------------------------------------
#ifndef _PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE
#define _PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE\
                                                        (_OFF)
#endif

//-------------------------------------------------
// Frame Sync DVtotal Consider Vfreq Margin
//-------------------------------------------------
#ifndef _PANEL_FRAME_SYNC_DVTOTAL_WITH_MARGIN
#define _PANEL_FRAME_SYNC_DVTOTAL_WITH_MARGIN           (_OFF)
#endif

//-------------------------------------------------
// DRR Frame Sync DVtotal Consider Vfreq Margin
//-------------------------------------------------
#ifndef _PANEL_DRR_FRAME_SYNC_DVTOTAL_WITH_MARGIN
#define _PANEL_DRR_FRAME_SYNC_DVTOTAL_WITH_MARGIN       (_OFF)
#endif

//--------------------------------------------------
// Definitions for video compensation
//-------------------------------------------------
#ifndef GET_PANEL_BYPASS_INTERLACE_COMPENSATION
#define GET_PANEL_BYPASS_INTERLACE_COMPENSATION(Vin, Vout)\
                                                        (_FALSE)
#endif

//-------------------------------------------------
// Definitions for dhfreq fine tune
//-------------------------------------------------
#ifndef _PANEL_HFREQ_FINE_TUNE
#define _PANEL_HFREQ_FINE_TUNE                          _OFF
#endif

#ifndef _PANEL_DH_FREQ_MAX
#define _PANEL_DH_FREQ_MAX                              989        // (Unit: 0.1 kHz)
#endif

#ifndef _PANEL_DH_FREQ_MIN
#define _PANEL_DH_FREQ_MIN                              529         // (Unit: 0.1 kHz)
#endif

//--------------------------------------------------
// Definitions for Asymmetric Panel
//-------------------------------------------------
#ifndef _PANEL_ASYMMETRIC
#define _PANEL_ASYMMETRIC                               _OFF
#endif

#ifndef _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT
#define _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT                0
#endif

#ifndef _PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT
#define _PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT               0
#endif

#ifndef _PANEL_ASYMMETRIC_DUMMY_NUM_TOP
#define _PANEL_ASYMMETRIC_DUMMY_NUM_TOP                 0
#endif

#ifndef _PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM
#define _PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM              0
#endif

//--------------------------------------------------
// Definitions for Panel Frame Rate Variation Check
//-------------------------------------------------
#ifndef _PANEL_DRR_FRAME_RATE_VARIATION_CHECK
#define _PANEL_DRR_FRAME_RATE_VARIATION_CHECK           _ON
#endif

#ifndef _PANEL_FRAME_RATE_VARIATION_CHECK
#define _PANEL_FRAME_RATE_VARIATION_CHECK               _ON
#endif

////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#ifndef _PANEL_ADC_OFFSET_BIAS
#define _PANEL_ADC_OFFSET_BIAS                          (0) // 0~5
#endif

#ifndef _PANEL_ADC_GAIN_BIAS
#define _PANEL_ADC_GAIN_BIAS                            (0) // -5~0
#endif


///////////////////////////
// Color Characteristics //
///////////////////////////
//--------------------------------------------------
// HDR10 Option
//--------------------------------------------------
#ifndef _PANEL_MAX_LUMINANCE
#define _PANEL_MAX_LUMINANCE                            0x62 // from OGC Tool
#endif

#ifndef _PANEL_MAX_FRAME_AVERAGE_LUMINANCE
#define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE              0x62 // from OGC Tool
#endif

#ifndef _PANEL_MAX_USER_DEFINE_LUMINANCE
#define _PANEL_MAX_USER_DEFINE_LUMINANCE                0x62
#endif

#ifndef _PANEL_MIN_LUMINANCE
#define _PANEL_MIN_LUMINANCE                            0x27 // from OGC Tool
#endif

//--------------------------------------------------
// FreeSync II Global Backlight Control Option
//--------------------------------------------------
#ifndef _PANEL_FREESYNC_II_MIN_BACKLIGHT
#define _PANEL_FREESYNC_II_MIN_BACKLIGHT                0x00 // 0x00~0xFF
#endif

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#ifndef _I_DITHER_TEMP
#define _I_DITHER_TEMP                                  _ENABLE
#endif

#ifndef _I_DITHER_VALUE_SIGN
#define _I_DITHER_VALUE_SIGN                            _DISABLE
#endif

#ifndef _I_DITHER_V_FRAME_MOD
#define _I_DITHER_V_FRAME_MOD                           _DISABLE
#endif

#ifndef _I_DITHER_H_FRAME_MOD
#define _I_DITHER_H_FRAME_MOD                           _DISABLE
#endif

#ifndef _I_DITHER_MULTI_SEQ_ENABLE
#define _I_DITHER_MULTI_SEQ_ENABLE                      _DISABLE
#endif

#ifndef _I_DITHER_SHARE_SEQ_ENABLE
#define _I_DITHER_SHARE_SEQ_ENABLE                      _DISABLE
#endif

#ifndef _I_DITHER_SERIES_SEQ_ENABLE
#define _I_DITHER_SERIES_SEQ_ENABLE                     _DISABLE
#endif

#ifndef _I_DITHER_SEQ_INV_ENABLE
#define _I_DITHER_SEQ_INV_ENABLE                        _DISABLE
#endif

#ifndef _I_DITHER_SEQ_INV_MODE
#define _I_DITHER_SEQ_INV_MODE                          0
#endif

#ifndef _I_DITHER_SUPER_PIXEL_SIZE
#define _I_DITHER_SUPER_PIXEL_SIZE                      _IDITHER_SUPER_PIXEL_2X2
#endif

#ifndef _I_DITHER_12_TO_10_TEMP
#define _I_DITHER_12_TO_10_TEMP                         _I_DITHER_TEMP
#endif

#ifndef _I_DITHER_12_TO_10_VALUE_SIGN
#define _I_DITHER_12_TO_10_VALUE_SIGN                   _I_DITHER_VALUE_SIGN
#endif

#ifndef _I_DITHER_12_TO_10_V_FRAME_MOD
#define _I_DITHER_12_TO_10_V_FRAME_MOD                  _I_DITHER_V_FRAME_MOD
#endif

#ifndef _I_DITHER_12_TO_10_H_FRAME_MOD
#define _I_DITHER_12_TO_10_H_FRAME_MOD                  _I_DITHER_H_FRAME_MOD
#endif

#ifndef _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE
#define _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE             _I_DITHER_MULTI_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE             _I_DITHER_SHARE_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE            _I_DITHER_SERIES_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SEQ_INV_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_ENABLE               _I_DITHER_SEQ_INV_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SEQ_INV_MODE
#define _I_DITHER_12_TO_10_SEQ_INV_MODE                 _I_DITHER_SEQ_INV_MODE  // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b
#endif

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#ifndef _D_DITHER_TEMP
#define _D_DITHER_TEMP                                  _ENABLE
#endif

#ifndef _D_DITHER_V_FRAME_MOD
#define _D_DITHER_V_FRAME_MOD                           _DISABLE
#endif

#ifndef _D_DITHER_H_FRAME_MOD
#define _D_DITHER_H_FRAME_MOD                           _DISABLE
#endif

#ifndef _D_DITHER_MULTI_SEQ_ENABLE
#define _D_DITHER_MULTI_SEQ_ENABLE                      _DISABLE
#endif

#ifndef _D_DITHER_SHARE_SEQ_ENABLE
#define _D_DITHER_SHARE_SEQ_ENABLE                      _DISABLE
#endif

#ifndef _D_DITHER_SEQ_INV_ENABLE
#define _D_DITHER_SEQ_INV_ENABLE                        _DISABLE
#endif

#ifndef _D_DITHER_SEQ_INV_MODE
#define _D_DITHER_SEQ_INV_MODE                          0  // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b
#endif

#ifndef _D_DITHER_SERIES_SEQ_ENABLE
#define _D_DITHER_SERIES_SEQ_ENABLE                     _DISABLE
#endif

#ifndef _D_DITHER_ADVANCE_SETTING_ENABLE
#define _D_DITHER_ADVANCE_SETTING_ENABLE                _DISABLE
#endif

#ifndef _D_DITHER_FREERUN_EN_SUPPORT
#define _D_DITHER_FREERUN_EN_SUPPORT                    _DISABLE
#endif

#if((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#ifndef _D_DITHER_SUPER_PIXEL_SIZE
#define _D_DITHER_SUPER_PIXEL_SIZE                      ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? _DDITHER_SUPER_PIXEL_4X4 : _DDITHER_SUPER_PIXEL_4X8)
#endif

#elif(_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL)

#ifndef _D_DITHER_SUPER_PIXEL_SIZE
#define _D_DITHER_SUPER_PIXEL_SIZE                      (((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) || (_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)) ? _DDITHER_SUPER_PIXEL_4X4 : _DDITHER_SUPER_PIXEL_4X8)
#endif

#endif

#ifndef _D_DITHER_6BIT_PANEL_FUNC_ENABLE
#if((_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) || (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#define _D_DITHER_6BIT_PANEL_FUNC_ENABLE                ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) ? _ENABLE : _DISABLE)
#else
#define _D_DITHER_6BIT_PANEL_FUNC_ENABLE                _DISABLE
#endif
#endif

//--------------------------------------------------
// Definitions for Global dimming table
//--------------------------------------------------
#ifndef _GLOBAL_DIMMING_STEP_R_TABLE
#define _GLOBAL_DIMMING_STEP_R_TABLE                    "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_PWM_LUT_TABLE
#define _GLOBAL_DIMMING_PWM_LUT_TABLE                   "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_PWM_LUT_TABLE
#define _GLOBAL_DIMMING_PWM_LUT_TABLE                   "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_HDR_TONE_MAPPING_LV540
#define _GLOBAL_DIMMING_HDR_TONE_MAPPING_LV540          "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_HDR_2084_LV
#define _GLOBAL_DIMMING_HDR_2084_LV                     "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_GAMMA_22_LV
#define _GLOBAL_DIMMING_SDR_GAMMA_22_LV                 "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_GAMMA_24_LV
#define _GLOBAL_DIMMING_SDR_GAMMA_24_LV                 "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_GAMMA_26_LV
#define _GLOBAL_DIMMING_SDR_GAMMA_26_LV                 "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_OGC_CASE_1_LV
#define _GLOBAL_DIMMING_SDR_OGC_CASE_1_LV               "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_OGC_CASE_2_LV
#define _GLOBAL_DIMMING_SDR_OGC_CASE_2_LV               "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_OGC_CASE_3_LV
#define _GLOBAL_DIMMING_SDR_OGC_CASE_3_LV               "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_OGC_CASE_4_LV
#define _GLOBAL_DIMMING_SDR_OGC_CASE_4_LV               "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_OGC_CASE_5_LV
#define _GLOBAL_DIMMING_SDR_OGC_CASE_5_LV               "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_SDR_OGC_CASE_6_LV
#define _GLOBAL_DIMMING_SDR_OGC_CASE_6_LV               "Panel/ZeroTable.h"
#endif

#ifndef _GLOBAL_DIMMING_DARK_MODE_THD
#define _GLOBAL_DIMMING_DARK_MODE_THD                   80
#endif

#ifndef _GLOBAL_DIMMING_DARK_MODE_MIN
#define _GLOBAL_DIMMING_DARK_MODE_MIN                   (_GLOBAL_DIMMING_DARK_MODE_THD - 1)
#endif

#ifndef _GD_PANEL_LV_MAX
#define _GD_PANEL_LV_MAX                                400
#endif

#ifndef _GD_PANEL_LV_MIN
#define _GD_PANEL_LV_MIN                                80
#endif

#if(_GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT == _ON)
#ifndef _GLOBAL_DIMMING_HDR_2084_LV_PWM
#define _GLOBAL_DIMMING_HDR_2084_LV_PWM                 _GLOBAL_DIMMING_HDR_2084_LV
#endif

#ifndef _GLOBAL_DIMMING_HDR_TM_LV540_PWM
#define _GLOBAL_DIMMING_HDR_TM_LV540_PWM                _GLOBAL_DIMMING_HDR_TONE_MAPPING_LV540
#endif
#endif

//--------------------------------------------------
// Definitions for Local Dimming PWM
//--------------------------------------------------
#ifndef _DEVICE_LED_DRIVER_TYPE
#define _DEVICE_LED_DRIVER_TYPE                         _DEVICE_LED_DRIVER_NONE
#endif

#ifndef _DEVICE_LED_DRIVER_COMMUNICATE_TYPE
#define _DEVICE_LED_DRIVER_COMMUNICATE_TYPE             _INTERFACE_SPI
#endif

#ifndef _DEVICE_LED_DRIVER_PWM_MAX
#define _DEVICE_LED_DRIVER_PWM_MAX                      4095
#endif

#ifndef _DEVICE_LED_DRIVER_PWM_MIN
#define _DEVICE_LED_DRIVER_PWM_MIN                      0x00
#endif

#ifndef _DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS
#define _DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS            _OFF
#endif

#ifndef _DEVICE_LED_DRIVER_SUPPORT_BROADCAST
#define _DEVICE_LED_DRIVER_SUPPORT_BROADCAST            _OFF
#endif

#ifndef _DEVICE_LED_DRIVER_BROADCAST_ID
#define _DEVICE_LED_DRIVER_BROADCAST_ID                 0x00
#endif

#ifndef _DEVICE_LED_DRIVER_VALID_ADDR
#define _DEVICE_LED_DRIVER_VALID_ADDR                   0x13
#endif

#ifndef _DEVICE_LED_DRIVER_VALID_BY_CE_NO_PWM
#define _DEVICE_LED_DRIVER_VALID_BY_CE_NO_PWM           0x00
#endif
#ifndef _DEVICE_LED_DRIVER_VALID_BY_VSYNC_NO_PWM
#define _DEVICE_LED_DRIVER_VALID_BY_VSYNC_NO_PWM        0x02
#endif
#ifndef _DEVICE_LED_DRIVER_VALID_BY_CE_EXT_PWM
#define _DEVICE_LED_DRIVER_VALID_BY_CE_EXT_PWM          0x01
#endif
#ifndef _DEVICE_LED_DRIVER_VALID_BY_VSYNC_EXT_PWM
#define _DEVICE_LED_DRIVER_VALID_BY_VSYNC_EXT_PWM       0x03
#endif

#ifndef _PANEL_LV_MAX
#define _PANEL_LV_MAX                                   0x01EC
#endif

#ifndef _PANEL_LV_MIN
#define _PANEL_LV_MIN                                   0x007B
#endif

#ifndef _PANEL_PWM_MAX
#define _PANEL_PWM_MAX                                  0x800
#endif

#ifndef _PANEL_PWM_MIN
#define _PANEL_PWM_MIN                                  0x56
#endif

#ifndef _REGION0_PWM_TO_LV_OWN
#define _REGION0_PWM_TO_LV_OWN                          4
#endif

#ifndef _REGION0_PWM_TO_LV_REGION1
#define _REGION0_PWM_TO_LV_REGION1                      19
#endif

#ifndef _REGION1_PWM_TO_LV_OWN
#define _REGION1_PWM_TO_LV_OWN                          5
#endif

#ifndef _REGION1_PWM_TO_LV_REGION0
#define _REGION1_PWM_TO_LV_REGION0                      21
#endif

#ifndef _REGION1_PWM_TO_LV_REGION2
#define _REGION1_PWM_TO_LV_REGION2                      20
#endif

#ifndef _REGION2_PWM_TO_LV_OWN
#define _REGION2_PWM_TO_LV_OWN                          5
#endif

#ifndef _REGION2_PWM_TO_LV_REGION1
#define _REGION2_PWM_TO_LV_REGION1                      21
#endif

#ifndef _REGION2_PWM_TO_LV_REGION3
#define _REGION2_PWM_TO_LV_REGION3                      20
#endif

#ifndef _REGION3_PWM_TO_LV_OWN
#define _REGION3_PWM_TO_LV_OWN                          5
#endif

#ifndef _REGION3_PWM_TO_LV_REGION2
#define _REGION3_PWM_TO_LV_REGION2                      20
#endif

#ifndef _REGION3_PWM_TO_LV_REGION4
#define _REGION3_PWM_TO_LV_REGION4                      21
#endif

#ifndef _REGION4_PWM_TO_LV_OWN
#define _REGION4_PWM_TO_LV_OWN                          5
#endif

#ifndef _REGION4_PWM_TO_LV_REGION3
#define _REGION4_PWM_TO_LV_REGION3                      21
#endif

#ifndef _REGION4_PWM_TO_LV_REGION5
#define _REGION4_PWM_TO_LV_REGION5                      21
#endif

#ifndef _REGION5_PWM_TO_LV_OWN
#define _REGION5_PWM_TO_LV_OWN                          5
#endif

#ifndef _REGION5_PWM_TO_LV_REGION4
#define _REGION5_PWM_TO_LV_REGION4                      20
#endif

#ifndef _REGION5_PWM_TO_LV_REGION6
#define _REGION5_PWM_TO_LV_REGION6                      21
#endif

#ifndef _REGION6_PWM_TO_LV_OWN
#define _REGION6_PWM_TO_LV_OWN                          5
#endif

#ifndef _REGION6_PWM_TO_LV_REGION5
#define _REGION6_PWM_TO_LV_REGION5                      19
#endif

#ifndef _REGION6_PWM_TO_LV_REGION7
#define _REGION6_PWM_TO_LV_REGION7                      20
#endif

#ifndef _REGION7_PWM_TO_LV_OWN
#define _REGION7_PWM_TO_LV_OWN                          4
#endif

#ifndef _REGION7_PWM_TO_LV_REGION6
#define _REGION7_PWM_TO_LV_REGION6                      18
#endif

#ifndef _GLOBAL_DIMMING_PANEL_PWM_MAX
#define _GLOBAL_DIMMING_PANEL_PWM_MAX                   0x800
#endif

#ifndef _GLOBAL_DIMMING_PANEL_PWM_MIN
#define _GLOBAL_DIMMING_PANEL_PWM_MIN                   0x0FF
#endif

#ifndef _GLOBAL_DIMMING_PANEL_PWM_DELTA_MAX
#define _GLOBAL_DIMMING_PANEL_PWM_DELTA_MAX             (_GLOBAL_DIMMING_PANEL_PWM_MAX - _GLOBAL_DIMMING_PANEL_PWM_MIN)
#endif

#ifndef _GLOBAL_DIMMING_PANEL_LV_MAX
#define _GLOBAL_DIMMING_PANEL_LV_MAX                    0x140
#endif

#ifndef _GLOBAL_DIMMING_PANEL_LV_MIN
#define _GLOBAL_DIMMING_PANEL_LV_MIN                    0x046
#endif

#ifndef _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL
#define _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL          1
#endif

#ifndef _LOCAL_DIMMING_PANEL_REGION_VERTICAL
#define _LOCAL_DIMMING_PANEL_REGION_VERTICAL            1
#endif

#ifndef _LOCAL_DIMMING_TOTAL_REGION
#define _LOCAL_DIMMING_TOTAL_REGION                     (_LOCAL_DIMMING_PANEL_REGION_VERTICAL * _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL)
#endif

#ifndef _LOCAL_DIMMING_HISTO_COVERRATE
#define _LOCAL_DIMMING_HISTO_COVERRATE                  995
#endif

#ifndef _LOCAL_DIMMING_TM_HISTO_COVERRATE
#define _LOCAL_DIMMING_TM_HISTO_COVERRATE               995
#endif

#ifndef _LOCAL_DIMMING_SOFTCLAMP_SLOP
#define _LOCAL_DIMMING_SOFTCLAMP_SLOP                   5
#endif

#ifndef _LOCAL_DIMMING_SOFTCLAMP_SLOP_POWER_SAVER
#define _LOCAL_DIMMING_SOFTCLAMP_SLOP_POWER_SAVER       29
#endif

#ifndef _LOCAL_DIMMING_BACKLIGHT_TYPE
#define _LOCAL_DIMMING_BACKLIGHT_TYPE                   _LOCAL_DIMMING_EDGE_BACKLIGHT
#endif

#ifndef _LOCAL_DIMMING_DEEP_BLACK_TH1
#define _LOCAL_DIMMING_DEEP_BLACK_TH1                   3500
#endif

#ifndef _LOCAL_DIMMING_DEEP_BLACK_DELTA
#define _LOCAL_DIMMING_DEEP_BLACK_DELTA                 3
#endif

#ifndef _DEVICE_LED_DRIVER_MCU_TYPE
#define _DEVICE_LED_DRIVER_MCU_TYPE                     _OFF
#endif

#ifndef _DEVICE_LED_DRIVER_SCPU_MEM_CHG_BUF
#define _DEVICE_LED_DRIVER_SCPU_MEM_CHG_BUF             512
#endif

#ifndef _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES
#define _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES         (2 + _LOCAL_DIMMING_PWM2SPI_APPEND_NUM_OF_BYTES)
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
#define _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME      1
#else
#define _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME      2
#endif
#endif


#ifndef _DEVICE_LED_DRIVER_UPDSYNC_DEFER_DCLK_CNT
#define _DEVICE_LED_DRIVER_UPDSYNC_DEFER_DCLK_CNT       0
#endif
#ifndef _DEVICE_LED_DRIVER_SPI0_VALID_CMD_ENTRY_SEL
#define _DEVICE_LED_DRIVER_SPI0_VALID_CMD_ENTRY_SEL     _SMODE_VALID_CMD_ENTRY_SEL_01
#endif
#ifndef _DEVICE_LED_DRIVER_SPI1_VALID_CMD_ENTRY_SEL
#define _DEVICE_LED_DRIVER_SPI1_VALID_CMD_ENTRY_SEL     _SMODE_VALID_CMD_ENTRY_SEL_23
#endif
#ifndef _DEVICE_LED_DRIVER_SPI2_VALID_CMD_ENTRY_SEL
#define _DEVICE_LED_DRIVER_SPI2_VALID_CMD_ENTRY_SEL     _SMODE_VALID_CMD_ENTRY_SEL_01
#endif

#ifndef _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE
#define _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE            1
#endif

#ifndef _DEVICE_LED_DRIVER_REG_BYTE_SWAP
#define _DEVICE_LED_DRIVER_REG_BYTE_SWAP                _OFF
#endif

#ifndef _DEVICE_LED_DRIVER_READ_DUMMY_BYTE_NUM
#define _DEVICE_LED_DRIVER_READ_DUMMY_BYTE_NUM          0
#endif

#ifndef _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE
#define _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE            2
#endif
#ifndef _DEVICE_LED_DRIVER_ADIM_ADDR
#define _DEVICE_LED_DRIVER_ADIM_ADDR                    0x70
#endif
#ifndef _DEVICE_LED_DRIVER_ADIM_WIDTH_BY_BYTE
#define _DEVICE_LED_DRIVER_ADIM_WIDTH_BY_BYTE           1
#endif
#ifndef _DEVICE_LED_DRIVER_ADIM_BYTE_SWAP
#define _DEVICE_LED_DRIVER_ADIM_BYTE_SWAP               _OFF
#endif
#ifndef _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM
#define _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM            0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME
#define _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME      1
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PIN_INVERT
#define _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PIN_INVERT      0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX
#define _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX       _OFF
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_ALIGN_DVS
#define _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_ALIGN_DVS       _OFF
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_DELAY_AFTER_UPD_SYNC_XUS
#define _LOCAL_DIMMING_PWM2SPI_DELAY_AFTER_UPD_SYNC_XUS 0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_INTERFACE_BITMAP
#define _LOCAL_DIMMING_PWM2SPI_INTERFACE_BITMAP         0x00000000
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_APPEND_NUM_OF_BYTES
#define _LOCAL_DIMMING_PWM2SPI_APPEND_NUM_OF_BYTES      0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_PATTERN_OF_DUMMY_BYTE
#define _LOCAL_DIMMING_PWM2SPI_PATTERN_OF_DUMMY_BYTE    0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM
#define _LOCAL_DIMMING_PWM2SPI_SPI0_DEV_NUM             1
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM
#define _LOCAL_DIMMING_PWM2SPI_SPI1_DEV_NUM             0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM
#define _LOCAL_DIMMING_PWM2SPI_SPI2_DEV_NUM             0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM
#define _LOCAL_DIMMING_PWM2SPI_MAX_DATA_BYTE_NUM        2
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM
#define _LOCAL_DIMMING_PWM2SPI_MAX_DUMMY_BYTE_NUM       0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_DUMMY_WIDTH_BY_BYTE
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_WIDTH_BY_BYTE      1
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP
#define _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP           _OFF
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_PWM_MIN
#define _LOCAL_DIMMING_PWM2SPI_PWM_MIN                  0
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_DEV_ADDR
#define _LOCAL_DIMMING_PWM2SPI_DEV_ADDR                 "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_NUM
#define _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_NUM            "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_PWM_START_ADDR
#define _LOCAL_DIMMING_PWM2SPI_PWM_START_ADDR           "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_NUM
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_BYTE_NUM           "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE0
#define _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE0             "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE1
#define _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE1             "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE2
#define _LOCAL_DIMMING_PWM2SPI_REMAP_TABLE2             "Panel/ZeroTable.h"
#endif

#ifndef _LED_SPI_DEV_ADDR
#define _LED_SPI_DEV_ADDR                               "Panel/ZeroTable.h"
#endif

#ifndef _LED_SPI_PWM_START_ADDR
#define _LED_SPI_PWM_START_ADDR                         "Panel/ZeroTable.h"
#endif

#ifndef _LED_SPI_DATA_BYTE_NUM
#define _LED_SPI_DATA_BYTE_NUM                          "Panel/ZeroTable.h"
#endif

#ifndef _LED_SPI_DUMMY_BYTE_NUM
#define _LED_SPI_DUMMY_BYTE_NUM                         "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_LVMAX_ADDR
#define _LOCAL_DIMMING_LVMAX_ADDR                       "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_PWMGAIN_ADDR
#define _LOCAL_DIMMING_PWMGAIN_ADDR                     "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_LVGAIN_ADDR
#define _LOCAL_DIMMING_LVGAIN_ADDR                      "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_LVLUT_ADDR
#define _LOCAL_DIMMING_LVLUT_ADDR                       "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_SCURVETHLUT_ADDR
#define _LOCAL_DIMMING_SCURVETHLUT_ADDR                 "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_HISTO_DEFAULTLUT_ADDR
#define _LOCAL_DIMMING_HISTO_DEFAULTLUT_ADDR            "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_LEDSETTING_ADDR
#define _LOCAL_DIMMING_LEDSETTING_ADDR                  "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_HISTO_SDRLUT_ADDR
#define _LOCAL_DIMMING_HISTO_SDRLUT_ADDR                "Panel/LocalDimmingDefaultTable/tHistoSDRLUT.h"
#endif

#ifndef _LOCAL_DIMMING_HISTO_HDRLUT_ADDR
#define _LOCAL_DIMMING_HISTO_HDRLUT_ADDR                "Panel/LocalDimmingDefaultTable/tHistoHDRLUT.h"
#endif

#ifndef _LOCAL_DIMMING_HISTO_SDRLUT_256_BIN_ADDR
#define _LOCAL_DIMMING_HISTO_SDRLUT_256_BIN_ADDR        "Panel/LocalDimmingDefaultTable/tHistoSDRLUT.h"
#endif

#ifndef _LOCAL_DIMMING_HISTO_HDRLUT_256_BIN_ADDR
#define _LOCAL_DIMMING_HISTO_HDRLUT_256_BIN_ADDR        "Panel/LocalDimmingDefaultTable/tHistoHDRLUT.h"
#endif

#ifndef _LOCAL_DIMMING_HISTO_HDRDECISION_THD_ADDR
#define _LOCAL_DIMMING_HISTO_HDRDECISION_THD_ADDR       "Panel/LocalDimmingDefaultTable/tHistoHDRDecisionTHD.h"
#endif

#ifndef _LOCAL_DIMMING_HISTO_SDRDECISION_THD_ADDR
#define _LOCAL_DIMMING_HISTO_SDRDECISION_THD_ADDR       "Panel/LocalDimmingDefaultTable/tHistoSDRDecisionTHD.h"
#endif

#ifndef _LOCAL_DIMMING_S1LUT_ADDR
#define _LOCAL_DIMMING_S1LUT_ADDR                       "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_S2LUT_ADDR
#define _LOCAL_DIMMING_S2LUT_ADDR                       "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_MAXCLL
#define _LOCAL_DIMMING_MAXCLL                           600
#endif

#ifndef _LOCAL_DIMMING_MAXFALL
#define _LOCAL_DIMMING_MAXFALL                          400
#endif

#ifndef _LOCAL_DIMMING_BOOST_ADMING
#define _LOCAL_DIMMING_BOOST_ADMING                     ((DWORD)_LOCAL_DIMMING_MAXCLL * 100 / _LOCAL_DIMMING_MAXFALL)
#endif

#ifndef _LOCAL_DIMMING_MAX_COMPENSATE_GAIN
#define _LOCAL_DIMMING_MAX_COMPENSATE_GAIN              100
#endif

#ifndef _LOCAL_DIMMING_HDR_2084_LV
#define _LOCAL_DIMMING_HDR_2084_LV                      "Panel/ZeroTable.h"
#endif

#ifndef _LOCAL_DIMMING_FREESYNC_II_LV
#define _LOCAL_DIMMING_FREESYNC_II_LV                   "Panel/ZeroTable.h"
#endif


#ifndef _LOCAL_DIMMING_SDR_LV
#define _LOCAL_DIMMING_SDR_LV                           _LOCAL_DIMMING_FREESYNC_II_LV
#endif

#ifndef _LOCAL_DIMMING_BOOST_ACTIVE_TIME
#define _LOCAL_DIMMING_BOOST_ACTIVE_TIME                10
#endif

#ifndef _LOCAL_DIMMING_BOOST_COOLING_TIME
#define _LOCAL_DIMMING_BOOST_COOLING_TIME               30
#endif

#ifndef _LOCAL_DIMMING_BOOST_COOLING_PWM_RATIO
#define _LOCAL_DIMMING_BOOST_COOLING_PWM_RATIO          50
#endif

#ifndef _LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS
#define _LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS           _OFF
#endif

#ifndef _DEVICE_LED_DRIVER_PWM_ADDRESS_STEP
#define _DEVICE_LED_DRIVER_PWM_ADDRESS_STEP             (_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE / _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE)
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS
#if(_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _OFF)
#define _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS    5
#else
#define _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS    1500
#endif
#endif

#ifndef _LOCAL_DIMMING_PWM_DECREASE_STEP_TABLE
#define _LOCAL_DIMMING_PWM_DECREASE_STEP_TABLE          "Panel/LocalDimmingDefaultTable/tPWMDecreaseTable.h"
#endif

#ifndef _LOCAL_DIMMING_PWM_INCREASE_STEP_TABLE
#define _LOCAL_DIMMING_PWM_INCREASE_STEP_TABLE          "Panel/LocalDimmingDefaultTable/tPWMIncreaseTable.h"
#endif

#ifndef _LOCAL_DIMMING_SMOOTH_PARA
#define _LOCAL_DIMMING_SMOOTH_PARA                      "Panel/LocalDimmingDefaultTable/tLDSmoothPara.h"
#endif

#ifndef _LOCAL_DIMMING_REGION_BOOST_ADIM_STAGE
#define _LOCAL_DIMMING_REGION_BOOST_ADIM_STAGE          1
#endif

#ifndef _LOCAL_DIMMING_REGION_BOOST_SUM_THD
#define _LOCAL_DIMMING_REGION_BOOST_SUM_THD             0
#endif

#ifndef _LOCAL_DIMMING_REGION_BOOST_TABLE
#define _LOCAL_DIMMING_REGION_BOOST_TABLE               "Panel/LocalDimmingDefaultTable/tRegionBoost.h"
#endif

#ifndef _LOCAL_DIMMING_PWM2SPI_ADIM_DATA_NUM
#define _LOCAL_DIMMING_PWM2SPI_ADIM_DATA_NUM            "Panel/ZeroTable.h"
#endif

//--------------------------------------------------
// Definitions of SPI Setting for Panel
//--------------------------------------------------
#ifndef _PANEL_SPI0_CLK_PRE_DIV
#define _PANEL_SPI0_CLK_PRE_DIV                         _DIV_9                   // SPI CLK PreDivider
#endif
#ifndef _PANEL_SPI0_CLK_DIV
#define _PANEL_SPI0_CLK_DIV                             _DIV_4              // SPI CLK Divider
#endif
#ifndef _PANEL_SPI0_ENUM_PROTOCOL_SEL
#define _PANEL_SPI0_ENUM_PROTOCOL_SEL                   _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PANEL_SPI0_ENUM_CLK_SRC_SEL
#define _PANEL_SPI0_ENUM_CLK_SRC_SEL                    _SPI_M2PLL_CLK      // SPI CLK Source
#endif
#ifndef _PANEL_SPI0_MOSI_IDLE_STATE
#define _PANEL_SPI0_MOSI_IDLE_STATE                     _LOW                // 0:low ; 1:high
#endif
#ifndef _PANEL_SPI0_SCLK_IDLE_STATE
#define _PANEL_SPI0_SCLK_IDLE_STATE                     _LOW                // 0:low ; 1:high
#endif
#ifndef _PANEL_SPI0_CS_SEL
#define _PANEL_SPI0_CS_SEL                              0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PANEL_SPI0_CS_POLARITY
#define _PANEL_SPI0_CS_POLARITY                         0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PANEL_SPI0_CS_SETUP
#define _PANEL_SPI0_CS_SETUP                            0                   // SPI CS Pin Setup  Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PANEL_SPI0_CS_HOLD
#define _PANEL_SPI0_CS_HOLD                             0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PANEL_SPI0_SUPPRESS_BITS
#define _PANEL_SPI0_SUPPRESS_BITS                       0                   // SPI Suppress Bits(value = 0~7)
#endif

#ifndef _PANEL_SPI1_CLK_PRE_DIV
#define _PANEL_SPI1_CLK_PRE_DIV                         _DIV_9                   // SPI CLK PreDivider
#endif
#ifndef _PANEL_SPI1_CLK_DIV
#define _PANEL_SPI1_CLK_DIV                             _DIV_4              // SPI CLK Divider
#endif
#ifndef _PANEL_SPI1_ENUM_PROTOCOL_SEL
#define _PANEL_SPI1_ENUM_PROTOCOL_SEL                   _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PANEL_SPI1_ENUM_CLK_SRC_SEL
#define _PANEL_SPI1_ENUM_CLK_SRC_SEL                    _SPI_M2PLL_CLK      // SPI CLK Source
#endif
#ifndef _PANEL_SPI1_MOSI_IDLE_STATE
#define _PANEL_SPI1_MOSI_IDLE_STATE                     _LOW                // 0:low ; 1:high
#endif
#ifndef _PANEL_SPI1_SCLK_IDLE_STATE
#define _PANEL_SPI1_SCLK_IDLE_STATE                     _LOW                // 0:low ; 1:high
#endif
#ifndef _PANEL_SPI1_CS_SEL
#define _PANEL_SPI1_CS_SEL                              0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PANEL_SPI1_CS_POLARITY
#define _PANEL_SPI1_CS_POLARITY                         0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PANEL_SPI1_CS_SETUP
#define _PANEL_SPI1_CS_SETUP                            0                   // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PANEL_SPI1_CS_HOLD
#define _PANEL_SPI1_CS_HOLD                             0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PANEL_SPI1_SUPPRESS_BITS
#define _PANEL_SPI1_SUPPRESS_BITS                       0                   // SPI Suppress Bits(value = 0~7)
#endif

#ifndef _PANEL_SPI2_CLK_PRE_DIV
#define _PANEL_SPI2_CLK_PRE_DIV                         _DIV_9                   // SPI CLK PreDivider
#endif
#ifndef _PANEL_SPI2_CLK_DIV
#define _PANEL_SPI2_CLK_DIV                             _DIV_4              // SPI CLK Divider
#endif
#ifndef _PANEL_SPI2_ENUM_PROTOCOL_SEL
#define _PANEL_SPI2_ENUM_PROTOCOL_SEL                   _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PANEL_SPI2_ENUM_CLK_SRC_SEL
#define _PANEL_SPI2_ENUM_CLK_SRC_SEL                    _SPI_M2PLL_CLK      // SPI CLK Source
#endif
#ifndef _PANEL_SPI2_MOSI_IDLE_STATE
#define _PANEL_SPI2_MOSI_IDLE_STATE                     _LOW                // 0:low ; 1:high
#endif
#ifndef _PANEL_SPI2_SCLK_IDLE_STATE
#define _PANEL_SPI2_SCLK_IDLE_STATE                     _LOW                // 0:low ; 1:high
#endif
#ifndef _PANEL_SPI2_CS_SEL
#define _PANEL_SPI2_CS_SEL                              0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PANEL_SPI2_CS_POLARITY
#define _PANEL_SPI2_CS_POLARITY                         0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PANEL_SPI2_CS_SETUP
#define _PANEL_SPI2_CS_SETUP                            0                   // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PANEL_SPI2_CS_HOLD
#define _PANEL_SPI2_CS_HOLD                             0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PANEL_SPI2_SUPPRESS_BITS
#define _PANEL_SPI2_SUPPRESS_BITS                       0                   // SPI Suppress Bits(value = 0~7)
#endif

//--------------------------------------------------
// Definitions of Motion Blur Reduction Fine-Tune Parameter
//--------------------------------------------------
#ifndef _DRR_MOTION_BLUR_REDUCTION_COMP_DUTY_OFFSET
#define _DRR_MOTION_BLUR_REDUCTION_COMP_DUTY_OFFSET     (0)                 // 0.1% of duty ratio
#endif

#ifndef _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO
#define _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO       (750)               // unit: 0.1 Hz
#endif

#ifndef _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_HI
#define _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_HI       (800)               // unit: 0.1 Hz
#endif

#ifndef _MOTION_BLUR_REDUCTION_FLICKER_IVF
#define _MOTION_BLUR_REDUCTION_FLICKER_IVF              (750)               // unit: 0.1 Hz
#endif
