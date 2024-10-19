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
// ID Code      : RL6952_Project_Default_Advanced.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////
// General //
/////////////

//--------------------------------------------------
// Panel Option
//--------------------------------------------------
#ifndef _PANEL_POW_SEQ_T6_TIMER_EVENT_MODE
#define _PANEL_POW_SEQ_T6_TIMER_EVENT_MODE                      _OFF
#endif

#ifndef _PANEL_POWER_ON_BEFORE_COLOR_SETTING
#define _PANEL_POWER_ON_BEFORE_COLOR_SETTING                    _OFF
#endif

#ifndef _PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING
#define _PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING                    _OFF
#endif

#ifndef _VBO_BACKLIGHT_BY_USER
#define _VBO_BACKLIGHT_BY_USER                                  _DISABLE
#endif

//-------------------------------------------------
// LVDS High Speed Option
//-------------------------------------------------
#ifndef _LVDS_ULTRA_HIGH_SPEED_SUPPORT
#define _LVDS_ULTRA_HIGH_SPEED_SUPPORT                          _OFF
#endif

//--------------------------------------------------
// PIP Frame Sync Support Option
//--------------------------------------------------
#ifndef _PIP_FRAME_SYNC_SUPPORT
#define _PIP_FRAME_SYNC_SUPPORT                                 _OFF
#endif

//--------------------------------------------------
// PBP LR Frame Sync Support Option
//--------------------------------------------------
#ifndef _PBP_LR_FRAME_SYNC_SUPPORT
#define _PBP_LR_FRAME_SYNC_SUPPORT                              _OFF
#endif

//--------------------------------------------------
// 2P Frame Sync de-bounce setting
//--------------------------------------------------
#ifndef _2P_FRAME_SYNC_DEBOUNCE_TIME
#define _2P_FRAME_SYNC_DEBOUNCE_TIME                            0 // (ms)
#endif

//--------------------------------------------------
// Multi-Display PIP Blending Option
//--------------------------------------------------
#ifndef _PIP_TRANSPARENCY_SUPPORT
#define _PIP_TRANSPARENCY_SUPPORT                               _OFF
#endif

//--------------------------------------------------
// Multi-Display Default Option
//--------------------------------------------------
#ifndef _USER_DEFAULT_DISPLAY_MODE
#define _USER_DEFAULT_DISPLAY_MODE                              ((_EAGLE_SIGHT_SUPPORT == _ON) ? _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT : _DISPLAY_MODE_1P)
#endif

#ifndef _USER_DEFAULT_AUTO_TARGET_INDEX
#define _USER_DEFAULT_AUTO_TARGET_INDEX                         _REGION_INDEX_0
#endif

#ifndef _USER_DEFAULT_SOURCE_SCAN_TYPE
#define _USER_DEFAULT_SOURCE_SCAN_TYPE                          _SOURCE_SWITCH_AUTO_IN_GROUP
#endif

#ifndef _USER_DEFAULT_INPUT_PORT_0
#define _USER_DEFAULT_INPUT_PORT_0                              _INPUT_PORT_SEARCH_PRI_0
#endif

#ifndef _USER_DEFAULT_INPUT_PORT_1
#define _USER_DEFAULT_INPUT_PORT_1                              _INPUT_PORT_SEARCH_PRI_1
#endif

#ifndef _USER_DEFAULT_INPUT_PORT_2
#define _USER_DEFAULT_INPUT_PORT_2                              _INPUT_PORT_SEARCH_PRI_2
#endif

#ifndef _USER_DEFAULT_INPUT_PORT_3
#define _USER_DEFAULT_INPUT_PORT_3                              _INPUT_PORT_SEARCH_PRI_3
#endif


//--------------------------------------------------
// CPU32 Option
//--------------------------------------------------
#ifndef _CPU32_EXECUTE_ON_ROM_ONLY
#define _CPU32_EXECUTE_ON_ROM_ONLY                              _OFF
#endif

#ifndef _CPU32_DDR_MEMORY_SIZE
#define _CPU32_DDR_MEMORY_SIZE                                  (132)   // 4M Byte: (4*1024^2*8) / (1024*8*32) = 128 row
#endif

//--------------------------------------------------
// Minimum Input Timing
//--------------------------------------------------
#ifndef _INPUT_TIMING_MIN_H_WIDTH
#define _INPUT_TIMING_MIN_H_WIDTH                               (640)
#endif

//-------------------------------------------------
// Motion Blur Reduction Option
//-------------------------------------------------
#ifndef _MOTION_BLUR_REDUCTION_SUPPORT
#define _MOTION_BLUR_REDUCTION_SUPPORT                          _OFF
#endif

#ifndef _MOTION_BLUR_PANEL_PIXEL_TYPE
#define _MOTION_BLUR_PANEL_PIXEL_TYPE                           _MOTION_BLUR_PANEL_PIXEL_LCD
#endif

#ifndef _MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT
#define _MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT      _OFF
#endif

#ifndef _DRR_MOTION_BLUR_REDUCTION_SUPPORT
#define _DRR_MOTION_BLUR_REDUCTION_SUPPORT                      _OFF
#endif

#ifndef _RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT
#define _RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT             _OFF
#endif

#ifndef _MOTION_BLUR_REDUCTION_BFI_1_IVF_SUPPORT
#define _MOTION_BLUR_REDUCTION_BFI_1_IVF_SUPPORT                _OFF
#endif

//-------------------------------------------------
// Memory BW Ctrl
//-------------------------------------------------
#ifndef _OD_BW_CTRL_SUPPORT
#define _OD_BW_CTRL_SUPPORT                                     _OFF
#endif

#ifndef _FRC_CAPTURE_BW_CTRL_SUPPORT
#define _FRC_CAPTURE_BW_CTRL_SUPPORT                            _OFF
#endif

#ifndef _FRC_DISPLAY_BW_CTRL_SUPPORT
#define _FRC_DISPLAY_BW_CTRL_SUPPORT                            _OFF
#endif

#ifndef _3DDI_BW_CTRL_SUPPORT
#define _3DDI_BW_CTRL_SUPPORT                                   _OFF
#endif


///////////
// DDCCI //
///////////

//-------------------------------------------------
// DDCCI Auto Switch Option
//-------------------------------------------------
#ifndef _DDCCI_AUTO_SWITCH_SUPPORT
#define _DDCCI_AUTO_SWITCH_SUPPORT                              _ON
#endif

//-------------------------------------------------
// DDCCI On Line Display Calibration OP Code Option
//-------------------------------------------------
#ifndef _DDCCI_OPCODE_VCP_DISP_CALIBRATION
#define _DDCCI_OPCODE_VCP_DISP_CALIBRATION                      0xFC
#endif

//--------------------------------------------------
// Definitions for custom capability support
//--------------------------------------------------
#ifndef _DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT
#define _DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT                    _OFF
#endif

/////////////////////
// Display Setting //
/////////////////////

//-------------------------------------------------
// Display Rotation Option
//-------------------------------------------------
#ifndef _DISPLAY_HOR_MIRROR_SUPPORT
#define _DISPLAY_HOR_MIRROR_SUPPORT                             _OFF
#endif

#ifndef _DISPLAY_VER_MIRROR_SUPPORT
#define _DISPLAY_VER_MIRROR_SUPPORT                             _OFF
#endif

//-------------------------------------------------
// Display Rotation Force 3buffer Option
//-------------------------------------------------
#ifndef _DISPLAY_ROTATION_FORCE_3_BUFFER
#define _DISPLAY_ROTATION_FORCE_3_BUFFER                        _OFF
#endif

//--------------------------------------------------
// Aspect Ratio Option
//--------------------------------------------------
#ifndef _ASPECT_RATIO_WITHOUT_MUTE
#define _ASPECT_RATIO_WITHOUT_MUTE                              _OFF
#endif

//--------------------------------------------------
// Smart Image Measure Option
//--------------------------------------------------
#ifndef _DYNAMIC_DATA_BOUNDARY_AUTO_MEASURE
#define _DYNAMIC_DATA_BOUNDARY_AUTO_MEASURE                     _OFF
#endif

//-------------------------------------------------
// Force Display Free Run Option --> For Last Line Issue Panel
//-------------------------------------------------
#ifndef _FORCE_TO_FREE_RUN_SUPPORT
#define _FORCE_TO_FREE_RUN_SUPPORT                              _OFF
#endif

//--------------------------------------------------
// Display Frame Sync Line Buffer Option
//--------------------------------------------------
#ifndef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT                         _ON
#endif

//-------------------------------------------------
// Disable MN Frame Sync -> Force to Free Run
//-------------------------------------------------
#ifndef _MN_FRAMESYNC_FORCE_TO_FREERUN
#define _MN_FRAMESYNC_FORCE_TO_FREERUN                          _OFF
#endif

//-------------------------------------------------
// VGIP Safe Mode Option
//-------------------------------------------------
#ifndef _FRAME_RATE_SLOW_DOWN_SUPPORT
#define _FRAME_RATE_SLOW_DOWN_SUPPORT                           _OFF
#endif

//-------------------------------------------------
// Freeze Mode Option
//-------------------------------------------------
#ifndef _FREEZE_SUPPORT
#define _FREEZE_SUPPORT                                         _OFF
#endif

#ifndef _ROTATION_FREEZE_FORCE_TO_BACKGROUND
#define _ROTATION_FREEZE_FORCE_TO_BACKGROUND                    _OFF
#endif

//--------------------------------------------------
// Display Frame Sync Frame Buffer Latency Option
//--------------------------------------------------
#ifndef _DISP_LATENCY_ADJUST_SUPPORT
#define _DISP_LATENCY_ADJUST_SUPPORT                            _OFF
#endif

//-------------------------------------------------
// Eagle Sight Support
//-------------------------------------------------
#ifndef _EAGLE_SIGHT_SUPPORT
#define _EAGLE_SIGHT_SUPPORT                                    _OFF
#endif

//-------------------------------------------------
// Eagle Sight Sub Reserve BW Max Hwidth
//-------------------------------------------------
#ifndef _EAGLE_SIGHT_SUB_BW_RESERVE_MAX_HWIDTH
#define _EAGLE_SIGHT_SUB_BW_RESERVE_MAX_HWIDTH                  (_PANEL_DH_WIDTH / 2)
#endif

//-------------------------------------------------
// Eagle Sight Circle Window Support
//-------------------------------------------------
#ifndef _EAGLE_SIGHT_CIRCLE_WIN_SUPPORT
#define _EAGLE_SIGHT_CIRCLE_WIN_SUPPORT                         _OFF
#endif

//-------------------------------------------------
// Eagle Sight Support
//-------------------------------------------------
#ifndef _EAGLE_SIGHT_MN_FRAME_SYNC_SUPPORT
#define _EAGLE_SIGHT_MN_FRAME_SYNC_SUPPORT                      _OFF
#endif

//-------------------------------------------------
// Eagle Sight Window Original Mode Support
//-------------------------------------------------
#ifndef _EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT
#define _EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT                      _OFF
#endif

//-------------------------------------------------
// Eagle Sight Low Latency Support
//-------------------------------------------------
#ifndef _EAGLE_SIGHT_SUPPORT_LOW_LATENCY
#define _EAGLE_SIGHT_SUPPORT_LOW_LATENCY                        _OFF
#endif

//--------------------------------------------------
// MTP PBPLR Performance Option
//--------------------------------------------------
#ifndef _2P_PBP_LR_PERFORMANCE_TYPE
#define _2P_PBP_LR_PERFORMANCE_TYPE                             _MAIN_EQUAL_TO_SUB
#endif

//--------------------------------------------------
// PIP SUB Display Position Adjust Option
//--------------------------------------------------
#ifndef _2P_PIP_SUB_DISP_POSITION_ADJ_FAST_MODE
#define _2P_PIP_SUB_DISP_POSITION_ADJ_FAST_MODE                 _OFF
#endif

//--------------------------------------------------
// Mdomain 12 Bit Option
//--------------------------------------------------
#ifndef _M_DOMAIN_12BIT_SUPPORT
#define _M_DOMAIN_12BIT_SUPPORT                                 _OFF
#endif

//-------------------------------
// Display Bandwidth Option
//-------------------------------
#ifndef _BW_CUSTOME_MODE
#define _BW_CUSTOME_MODE                                        _DISABLE
#endif

//-------------------------------------------------
// Force IMG CMP off
//-------------------------------------------------
#ifndef _M_DOMAIN_FORCE_IMG_CMP
#define _M_DOMAIN_FORCE_IMG_CMP                                 _OFF
#endif

//--------------------------------------------------
// Force IMC compress to 8 bpp
//--------------------------------------------------
#ifndef _M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT
#define _M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT                   _OFF
#endif

//-------------------------------------------------
// Force Memory Data 10-Bit to 8-Bit
//-------------------------------------------------
#ifndef _M_DOMAIN_LSR_LINE_BUFFER_DT_FORCE_10_TO_8_BIT
#define _M_DOMAIN_LSR_LINE_BUFFER_DT_FORCE_10_TO_8_BIT          _OFF
#endif

//-------------------------------------------------
// Search DRR IVF Priority by User
//-------------------------------------------------
#ifndef _SEARCH_DRR_IVF_PRIORITY_BY_USER
#define _SEARCH_DRR_IVF_PRIORITY_BY_USER                        _OFF
#endif

////////////////////
// Color Function //
////////////////////

//--------------------------------------------------
// Digital Functional Option
//--------------------------------------------------
#ifndef _RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER
#define _RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER           _OFF
#endif

#ifndef _YCC_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER
#define _YCC_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER           _OFF
#endif

#ifndef _IP_SRGB_ON
#define _IP_SRGB_ON                                             _OFF
#endif

#ifndef _IP_OUTPUT_GAMMA_ON
#define _IP_OUTPUT_GAMMA_ON                                     _OFF
#endif

#ifndef _IP_INPUT_GAMMA_ON
#define _IP_INPUT_GAMMA_ON                                      _OFF
#endif

#ifndef _IP_COLOR_CONVERT_ON
#define _IP_COLOR_CONVERT_ON                                    _OFF
#endif

#ifndef _IP_LSR_ON
#define _IP_LSR_ON                                              _OFF
#endif

#ifndef _IP_DSHP_ON
#define _IP_DSHP_ON                                             _OFF
#endif

#ifndef _IP_DCR_ON
#define _IP_DCR_ON                                              _OFF
#endif

#ifndef _IP_IDLTI_ON
#define _IP_IDLTI_ON                                            _OFF
#endif

#ifndef _IP_DCC_HISTOGRAM_ON
#define _IP_DCC_HISTOGRAM_ON                                    _OFF
#endif

#ifndef _IP_DCC_ON
#define _IP_DCC_ON                                              _OFF
#endif

#ifndef _IP_BRIGHTNESS_ON
#define _IP_BRIGHTNESS_ON                                       _OFF
#endif

#ifndef _IP_CONTRAST_ON
#define _IP_CONTRAST_ON                                         _OFF
#endif

#ifndef _IP_ICM_ON
#define _IP_ICM_ON                                              _OFF
#endif

#ifndef _IP_UNIFORMITY_ON
#define _IP_UNIFORMITY_ON                                       _OFF
#endif

#ifndef _SIX_COLOR_ICM_TYPE
#define _SIX_COLOR_ICM_TYPE                                     _SIX_COLOR_ICM_NORMAL_MODE
#endif

#ifndef _SIX_COLOR_ICM_GRAY_LEVEL_CONTROL
#define _SIX_COLOR_ICM_GRAY_LEVEL_CONTROL                       _OFF
#endif

#ifndef _ICM_CHAMELEON_FUNCTION
#define _ICM_CHAMELEON_FUNCTION                                 _OFF
#endif

#ifndef _IP_LOCAL_CONTRAST_ON
#define _IP_LOCAL_CONTRAST_ON                                   _OFF
#endif

#ifndef _IP_LOCAL_CONTRAST_HISTOGRAM_ON
#define _IP_LOCAL_CONTRAST_HISTOGRAM_ON                         _OFF
#endif

#ifndef _CONTRAST_6BIT_PANEL_COMPENSATE
#define _CONTRAST_6BIT_PANEL_COMPENSATE                         _OFF
#endif

#ifndef _ULTRA_VIVID_FUNCTION_WITH_IDLTI
#define _ULTRA_VIVID_FUNCTION_WITH_IDLTI                        _OFF
#endif

#ifndef _ULTRA_VIVID_FUNCTION_WITH_DSHP
#define _ULTRA_VIVID_FUNCTION_WITH_DSHP                         _OFF
#endif

//-------------------------------------------------
// Input Gamma Option
//-------------------------------------------------
#ifndef _INPUT_GAMMA_NODE_1025_SUPPORT
#define _INPUT_GAMMA_NODE_1025_SUPPORT                          _OFF
#endif

//--------------------------------------------------
// Force YUV format conversion Option
//--------------------------------------------------
#ifndef _M_DOMAIN_FORCE_YUV_FORMAT
#define _M_DOMAIN_FORCE_YUV_FORMAT                              _OFF
#endif

//--------------------------------------------------
// OD Performance Option
//--------------------------------------------------
#ifndef _OD_6_0_AND_4_5_BIT_MODE_IMPROVE_OPTION
#define _OD_6_0_AND_4_5_BIT_MODE_IMPROVE_OPTION                 _OFF
#endif

//-------------------------------
// Color Process Control Backlight By User
//-------------------------------
#ifndef _FIRST_CHECK_CONTROL_BACKLIGHT_BY_USER
#define _FIRST_CHECK_CONTROL_BACKLIGHT_BY_USER                  _OFF
#endif

//-------------------------------------------------
// Hue and Saturation Option
//-------------------------------------------------
#ifndef _GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION
#define _GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION           _OFF
#endif

////////////////////////////////////////
// On-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// FreesyncII Option
//-------------------------------------------------
#ifndef _COLORIMETRY_SEAMLESS_CHANGE_SUPPORT
#define _COLORIMETRY_SEAMLESS_CHANGE_SUPPORT                    _OFF
#endif

#ifndef _FREESYNC_II_FORCE_HDR10_BT2020_SUPPORT
#define _FREESYNC_II_FORCE_HDR10_BT2020_SUPPORT                 _OFF
#endif

//-------------------------------------------------
// DM colorformat change wo reset Option
//-------------------------------------------------
#ifndef _DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT
#define _DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT                 _OFF
#endif

//-------------------------------------------------
// Uniformity (On-Line Calibration) Option
//-------------------------------------------------

#ifndef _UNIFORMITY_LEVEL0_SUPPORT
#define _UNIFORMITY_LEVEL0_SUPPORT                              _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE0
#define _UNIFORMITY_OFFSET_TYPE0                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE1
#define _UNIFORMITY_OFFSET_TYPE1                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE2
#define _UNIFORMITY_OFFSET_TYPE2                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE3
#define _UNIFORMITY_OFFSET_TYPE3                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE4
#define _UNIFORMITY_OFFSET_TYPE4                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE5
#define _UNIFORMITY_OFFSET_TYPE5                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE6
#define _UNIFORMITY_OFFSET_TYPE6                                _OFF
#endif

#ifndef _UNIFORMITY_PLUS_FUNCTION
#define _UNIFORMITY_PLUS_FUNCTION                               _OFF
#endif

#ifndef _UNIFORMITY_CUSTOM_ENABLE_CONDITION_SUPPORT
#define _UNIFORMITY_CUSTOM_ENABLE_CONDITION_SUPPORT             _OFF
#endif

//-------------------------------------------------
// Local Dimmming Option
//-------------------------------------------------
#ifndef _LOCAL_DIMMING_HDR10_BOOST_SUPPORT
#define _LOCAL_DIMMING_HDR10_BOOST_SUPPORT                      _OFF
#endif

#ifndef _LOCAL_DIMMING_DRR_MODE_SUPPORT
#define _LOCAL_DIMMING_DRR_MODE_SUPPORT                         _OFF
#endif

#ifndef _LOCAL_DIMMING_USING_YAVG_INFO
#define _LOCAL_DIMMING_USING_YAVG_INFO                          _OFF
#endif

#ifndef _LOCAL_DIMMING_MBR_MODE_SUPPORT
#define _LOCAL_DIMMING_MBR_MODE_SUPPORT                         _OFF
#endif

#ifndef _LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT
#define _LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT                _OFF
#endif

#ifndef _LOCAL_DIMMING_USER_GLOBAL_BOOST_SUPPORT
#define _LOCAL_DIMMING_USER_GLOBAL_BOOST_SUPPORT                _OFF
#endif

#ifndef _LOCAL_DIMMING_BLACK_SMOOTH_MODE
#define _LOCAL_DIMMING_BLACK_SMOOTH_MODE                        _OFF
#endif

#ifndef _LOCAL_DIMMING_BLACK_COLOR_CODE
#define _LOCAL_DIMMING_BLACK_COLOR_CODE                         1
#endif

#ifndef _LOCAL_DIMMING_LINEAR_BLACK_COLOR_CODE
#define _LOCAL_DIMMING_LINEAR_BLACK_COLOR_CODE                  0
#endif

#ifndef _LOCAL_DIMMING_LINEAR_WHITE_COLOR_CODE
#define _LOCAL_DIMMING_LINEAR_WHITE_COLOR_CODE                  1023
#endif

#ifndef _LOCAL_DIMMING_WHITE_LUT_VALUE_SDR
#define _LOCAL_DIMMING_WHITE_LUT_VALUE_SDR                      0X7F
#endif

#ifndef _LOCAL_DIMMING_BLACK_LUT_VALUE_SDR
#define _LOCAL_DIMMING_BLACK_LUT_VALUE_SDR                      0x2F
#endif

#ifndef _LOCAL_DIMMING_WHITE_LUT_VALUE_HDR
#define _LOCAL_DIMMING_WHITE_LUT_VALUE_HDR                      0X7F
#endif

#ifndef _LOCAL_DIMMING_BLACK_LUT_VALUE_HDR
#define _LOCAL_DIMMING_BLACK_LUT_VALUE_HDR                      0x05
#endif

#ifndef _LOCAL_DIMMING_SCENE_CHANGE_SUPPORT
#define _LOCAL_DIMMING_SCENE_CHANGE_SUPPORT                     _OFF
#endif

#ifndef _LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT
#define _LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT                 _OFF
#endif

#ifndef _LOCAL_DIMMING_REGION_BOOST_SUPPORT
#define _LOCAL_DIMMING_REGION_BOOST_SUPPORT                     _OFF
#endif

#ifndef _LOCAL_DIMMING_ADAPTIVE_SMOOTH_SUPPORT
#define _LOCAL_DIMMING_ADAPTIVE_SMOOTH_SUPPORT                  _OFF
#endif

#ifndef _LOCAL_DIMMING_BLMODEL_MAX_GAIN
#define _LOCAL_DIMMING_BLMODEL_MAX_GAIN                         8
#endif

#ifndef _LOCAL_DIMMING_FULL_PATTERN_ONESTEP_SUPPORT
#define _LOCAL_DIMMING_FULL_PATTERN_ONESTEP_SUPPORT             _OFF
#endif

#ifndef _LOCAL_DIMMING_MULTI_TABLE_SUPPORT
#define _LOCAL_DIMMING_MULTI_TABLE_SUPPORT                      _OFF
#endif

#ifndef _LOCAL_DIMMING_COMPENSATE_MODE
#define _LOCAL_DIMMING_COMPENSATE_MODE                          _LD_COMPENSATE_NONE
#endif

#ifndef _LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT
#define _LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT                 _OFF
#endif

//-------------------------------------------------
// Global Dimmming Option
//-------------------------------------------------
#ifndef _GLOBAL_DIMMING_DARK_SENSITIVITY_SUPPORT
#define _GLOBAL_DIMMING_DARK_SENSITIVITY_SUPPORT                _OFF
#endif

#ifndef _GLOBAL_DIMMING_BLACK_THD
#define _GLOBAL_DIMMING_BLACK_THD                               1
#endif

#ifndef _GLOBAL_DIMMING_PATTERN_ESTIMATE
#define _GLOBAL_DIMMING_PATTERN_ESTIMATE                        _OFF
#endif

#ifndef _GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT
#define _GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT              _OFF
#endif

#ifndef _GLOBAL_DIMMING_DARK_MODE_SUPPORT
#define _GLOBAL_DIMMING_DARK_MODE_SUPPORT                       _OFF
#endif

#ifndef _GLOBAL_DIMMING_DARK_MODE_MAX_GAIN
#define _GLOBAL_DIMMING_DARK_MODE_MAX_GAIN                      5
#endif

#ifndef _GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT
#define _GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT              _OFF
#endif

//-------------------------------------------------
// Dynamic color Auto measure
//-------------------------------------------------
#ifndef _DYNAMIC_COLOR_AUTO_MEASURE
#define _DYNAMIC_COLOR_AUTO_MEASURE                             _OFF
#endif

//-------------------------------------------------
// SDR to HDR Option
//-------------------------------------------------
#ifndef _SDR_TO_HDR_FUNCTION
#define _SDR_TO_HDR_FUNCTION                                    _OFF
#endif

#ifndef _SDR_TO_HDR_ADOBE_RGB_SUPPORT
#define _SDR_TO_HDR_ADOBE_RGB_SUPPORT                           _OFF
#endif

//-------------------------------------------------
// LocalContrast Option
//-------------------------------------------------
#ifndef _ADVANCED_LOCAL_CONTRAST_SUPPORT
#define _ADVANCED_LOCAL_CONTRAST_SUPPORT                        _OFF
#endif

#ifndef _LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL
#define _LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL                    _OFF
#endif

#ifndef _LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION
#define _LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION                  _OFF
#endif
//-------------------------------------------------
// SDR+ Option
//-------------------------------------------------
#ifndef _SDR_PLUS_FUNCTION
#define _SDR_PLUS_FUNCTION                                      _OFF
#endif

//-------------------------------------------------
// NIGHT SNIPER Option
//-------------------------------------------------
#ifndef _IMMERSIVE_NIGHT_SNIPER_FUNCTION
#define _IMMERSIVE_NIGHT_SNIPER_FUNCTION                        _OFF
#endif

//-------------------------------------------------
// HDR10 Color Enhance & Light Enhance Option
//-------------------------------------------------
#ifndef _HDR10_COLOR_ENHANCE_FUNCTION
#define _HDR10_COLOR_ENHANCE_FUNCTION                           _OFF
#endif
#ifndef _HDR10_LIGHT_ENHANCE_FUNCTION
#define _HDR10_LIGHT_ENHANCE_FUNCTION                           _OFF
#endif

//-------------------------------------------------
// HDR10 FIXED POINT TONEMAPPING
//-------------------------------------------------
#ifndef _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT
#define _HDR10_FIXED_POINT_TONEMAPPING_SUPPORT                  _OFF
#endif

//-------------------------------------------------
// HDR10 USER DEFINE FIXED POINT TONEMAPPING
//-------------------------------------------------
#ifndef _HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT
#define _HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT      _OFF
#endif

//-------------------------------------------------
// HDR10 EETF TONEMAPPING
//-------------------------------------------------
#ifndef _HDR10_EETF_TONEMAPPING_SUPPORT
#define _HDR10_EETF_TONEMAPPING_SUPPORT                         _OFF
#endif

//-------------------------------------------------
// HDR10 EETF TONEMAPPING
//-------------------------------------------------
#ifndef _HDR10_TONEMAPPING_BY_MAXCLL_SUPPORT
#define _HDR10_TONEMAPPING_BY_MAXCLL_SUPPORT                    _OFF
#endif

//-------------------------------------------------
// HDR10 User Define Panel Max Lv
//-------------------------------------------------
#ifndef _HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT
#define _HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT                 _OFF
#endif

//-------------------------------------------------
// HDR10 BackLight Adaptive TM Option
//-------------------------------------------------
#ifndef _HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT
#define _HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT                    _OFF
#endif

//-------------------------------------------------
// HDR10 Mastering Lv StepeLess TM Option
//-------------------------------------------------
#ifndef _HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT
#define _HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT                 _OFF
#endif

//-------------------------------------------------
// 3D Gamma Gamut compression Option
//-------------------------------------------------
#ifndef _RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT
#define _RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT                   _OFF
#endif

//-------------------------------------------------
// 3D Gamma HDR10 Remap Option
//-------------------------------------------------
#ifndef _RGB_3D_GAMMA_HDR10_REMAP_SUPPORT
#define _RGB_3D_GAMMA_HDR10_REMAP_SUPPORT                       _OFF
#endif

//-------------------------------------------------
// 3D Gamma OCC Normal Option
//-------------------------------------------------
#ifndef _RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT
#define _RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT                      _OFF
#endif

//-------------------------------------------------
// HDR10 Get Status Beforehand Option
//-------------------------------------------------
#ifndef _HDR10_GET_STATUS_BEFOREHAND_SUPPORT
#define _HDR10_GET_STATUS_BEFOREHAND_SUPPORT                    _OFF
#endif

//-------------------------------------------------
// HLG Support
//-------------------------------------------------
#ifndef _HDMI_HLG_SUPPORT
#define _HDMI_HLG_SUPPORT                                       _OFF
#endif

#ifndef _DP_HLG_SUPPORT
#define _DP_HLG_SUPPORT                                         _OFF
#endif

//-------------------------------------------------
// HDR10 User Mastering Lv Change Support
//-------------------------------------------------
#ifndef _HDR10_USER_MASTERING_LV_CHANGE_SUPPORT
#define _HDR10_USER_MASTERING_LV_CHANGE_SUPPORT                 _OFF
#endif

//-------------------------------------------------
// OCC Advance Option
//-------------------------------------------------
#ifndef _DCIP3_NO_COMPRESSION_SUPPORT
#define _DCIP3_NO_COMPRESSION_SUPPORT                           _OFF
#endif

#ifndef _OCC_BOX_PATTERN_GENERATOR_SUPPORT
#define _OCC_BOX_PATTERN_GENERATOR_SUPPORT                      _OFF
#endif

#ifndef _OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT
#define _OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT                    _OFF
#endif

#ifndef _OCC_DISPLAY_P3_GAMMA_22_SUPPORT
#define _OCC_DISPLAY_P3_GAMMA_22_SUPPORT                        _OFF
#endif

#ifndef _OCC_PCM_GAMMA_SUPPORT
#define _OCC_PCM_GAMMA_SUPPORT                                  _OFF
#endif

#ifndef _MULTI_BRI_CALIBRATION_TYPE
#define _MULTI_BRI_CALIBRATION_TYPE                             _MULTI_BRI_CALIBRATION_NONE
#endif

#ifndef _OCC_GAMUT_NO_COMPRESSION_SUPPORT
#define _OCC_GAMUT_NO_COMPRESSION_SUPPORT                       _OFF
#endif

#ifndef _OGC_NO_INTERPOLATION_SUPPORT
#define _OGC_NO_INTERPOLATION_SUPPORT                           _OFF
#endif

#ifndef _SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT
#define _SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT                     _OFF
#endif

#ifndef _OGC_OCC_VERIFY_REPORT_BANK
#define _OGC_OCC_VERIFY_REPORT_BANK                             32
#endif

#ifndef _OCC_RGB_3D_GAMMA_SUPPORT
#define _OCC_RGB_3D_GAMMA_SUPPORT                               _OFF
#endif

#ifndef _OCC_RGB_3D_GAMMA_TOTAL_SET
#define _OCC_RGB_3D_GAMMA_TOTAL_SET                             1
#endif

#ifndef _OCC_RGB_3D_GAMMA_FLASH_BANK0
#define _OCC_RGB_3D_GAMMA_FLASH_BANK0                           33
#endif

#ifndef _OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT
#define _OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT                   _OFF
#endif
//-------------------------------------------------
// PCM Advance Option
//-------------------------------------------------
#ifndef _PCM_FULL_TIME_FUNCTION
#define _PCM_FULL_TIME_FUNCTION                                 (_PCM_FUNCTION == _ON)
#endif

//-------------------------------------------------
// DYNAMIC_LOWBLUE Option
//-------------------------------------------------
#ifndef _DYNAMIC_LOWBLUE_FUNCTION
#define _DYNAMIC_LOWBLUE_FUNCTION                               _OFF
#endif

//-------------------------------------------------
// Scaling Down Coef Sel Function
//-------------------------------------------------
#ifndef _SD_TABLE_SEL_FUNCTION
#define _SD_TABLE_SEL_FUNCTION                                  _OFF
#endif

///////////
// Flash //
///////////

//--------------------------------------------------
// Definitions of Flash Item Length For Each Page
//--------------------------------------------------
#ifndef _DATA_ITEM_LENGTH
#define _DATA_ITEM_LENGTH                                       16
#endif

#ifndef _PAGE_INFO_LENGTH
#define _PAGE_INFO_LENGTH                                       16
#endif

//--------------------------------------------------
// Definitions of Flash Read Mode
//--------------------------------------------------
#ifndef _FLASH_READ_MODE
#define _FLASH_READ_MODE                                        (_GOSD_SUPPORT == _ON ? _FLASH_DUAL_READ : _FLASH_FAST_READ)
#endif

//--------------------------------------------------
// FLASH Top Bottom Protect Select, TOP:0, Bottom:1
//--------------------------------------------------
#ifndef _FLASH_TOP_BOTTOM_PROTECT_SELECT
#define _FLASH_TOP_BOTTOM_PROTECT_SELECT                        _FLASH_TOP_PROTECT
#endif


//////////
// EDID //
//////////

//-------------------------------------------------
// HDR10 EDID Auto Switch Option
//-------------------------------------------------

#ifndef _WRITE_EDID_TO_SYSTEM_EEPROM
#define _WRITE_EDID_TO_SYSTEM_EEPROM                            _OFF
#endif


//////////////
// HDCP Key //
//////////////

//-------------------------------------------------
// HDCP Key Location Option
//-------------------------------------------------
#ifndef _WRITE_HDCP_TO_SYSTEM_EEPROM
#define _WRITE_HDCP_TO_SYSTEM_EEPROM                            _OFF
#endif


///////////////////
// System Source //
///////////////////

//-------------------------------------------------
// System Default Search Time for all Port --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT
#define _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT                    SEC(2)
#endif

//-------------------------------------------------
// System Default Search Time When No Cable Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE               SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE                 SEC(3)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C_NO_CABLE             SEC(4.5)
#endif

//-------------------------------------------------
// System Required Time for External or Embedded DP Switch
//-------------------------------------------------
#ifndef _SOURCE_DP_SWITCH_TIMEOUT_TIME
#define _SOURCE_DP_SWITCH_TIMEOUT_TIME                          SEC(4)
#endif

//-------------------------------------------------
// System Required Time for for DP Dual EDID
//-------------------------------------------------
#ifndef _SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME
#define _SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME                     SEC(4)
#endif

//--------------------------------------------------
// Double Check NVRAM Port When Searching In Polling Mode Option
//--------------------------------------------------
#ifndef _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT
#define _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT                 _OFF
#endif

#ifndef _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT
#define _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT             SEC(0.5)
#endif

//-------------------------------------------------
// System Source Background Detect Support
//-------------------------------------------------
#ifndef _SOURCE_BACKGROUND_DETECT_SUPPORT
#define _SOURCE_BACKGROUND_DETECT_SUPPORT                       _OFF
#endif

//-------------------------------------------------
// System Source Background Detection Enable Control
//-------------------------------------------------
#ifndef _SOURCE_BACKGROUND_DETECT_ENABLE_CONTROL_BY_USER
#define _SOURCE_BACKGROUND_DETECT_ENABLE_CONTROL_BY_USER        _OFF
#endif

//--------------------------------------------------
// System Source Background Detection DSC Decoder Support
//--------------------------------------------------
#ifndef _BACKGROUND_DETECTION_DSC_DECODER_SUPPORT
#define _BACKGROUND_DETECTION_DSC_DECODER_SUPPORT               _OFF
#endif


//////////////////
// System Power //
//////////////////

//--------------------------------------------------
// Power Fake Off to Off Timeout
//--------------------------------------------------
#ifndef _POWER_FAKE_OFF_TO_OFF_TIMEOUT
#define _POWER_FAKE_OFF_TO_OFF_TIMEOUT                          SEC(8)
#endif

//--------------------------------------------------
// Power Off HDCP2 HandShake Timeout
//--------------------------------------------------
#ifndef _POWER_OFF_HDCP_HANDSHAKE_TIMEOUT
#define _POWER_OFF_HDCP_HANDSHAKE_TIMEOUT                       SEC(8)
#endif

//--------------------------------------------------
// Fake Saving Control when support U3
//--------------------------------------------------
#ifndef _FAKE_POWER_SAVING_CONTROL_U3_SUPPORT
#define _FAKE_POWER_SAVING_CONTROL_U3_SUPPORT                   _OFF
#endif


////////////////
//    HDMI    //
////////////////

//--------------------------------------------------
// HDMI Option
//--------------------------------------------------
#ifndef _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD
#define _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD                 _MCCS_SWITCH_MODE
#endif

#ifndef _TMDS_EDID_SWITCH_HPD_TIME
#define _TMDS_EDID_SWITCH_HPD_TIME                              600
#endif

//-------------------------------------------------
// HDMI HDCP Re-auth Option
//-------------------------------------------------
#ifndef _HDMI_HDCP22_REAUTH_IN_RESET_PROC
#define _HDMI_HDCP22_REAUTH_IN_RESET_PROC                       _OFF
#endif

//--------------------------------------------------
// TMDS Z0's HPD DDC Check Optional
//--------------------------------------------------
#ifndef _TMDS_DDC_CHECK_BUSY_BEFORE_HPD
#define _TMDS_DDC_CHECK_BUSY_BEFORE_HPD                         _OFF
#endif

#ifndef _HDMI_FREESYNC_MCCS_VCP
#define _HDMI_FREESYNC_MCCS_VCP                                 0xE6
#endif

#ifndef _TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT
#define _TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT                   _OFF
#endif

#ifndef _TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT
#define _TMDS_HPD_TIMER_EVENT_ACTIVE_TYPE_SUPPORT               _OFF
#endif

//--------------------------------------------------
// HDMI DDCRAM/DDCCI force Nack when HPD low toggle by Kernel
// HPD High Ctrl by User In AC ON
// Swich off HDCP/SCDC Slave when AC ON
//--------------------------------------------------
#ifndef _DELL_HDMI_HPD_DDC_STYLE_SUPPORT
#define _DELL_HDMI_HPD_DDC_STYLE_SUPPORT                        _OFF
#endif

//--------------------------------------------------
// HPD Toggle if DDC toggle during Z0 off
//--------------------------------------------------
#ifndef _HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE
#define _HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE                   _OFF
#endif

//--------------------------------------------------
// HDMI Z0 toggle in power saving
//--------------------------------------------------
#ifndef _TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT
#define _TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT                    _OFF
#endif

#ifndef _HDMI_UNSTABLE_BED_CHECK_SUPPORT
#define _HDMI_UNSTABLE_BED_CHECK_SUPPORT                        _OFF
#endif

//--------------------------------------------------
// HDMI CTS Option
//--------------------------------------------------
#ifndef _TMDS_HDMI20_SCDC_RR_CTS_SUPPORT
#define _TMDS_HDMI20_SCDC_RR_CTS_SUPPORT                        _OFF
#endif

#ifndef _D3_TMDS_Z0_IMPEDANCE_OPTION
#define _D3_TMDS_Z0_IMPEDANCE_OPTION                            _BY_CONNECTOR
#endif

#ifndef _D4_TMDS_Z0_IMPEDANCE_OPTION
#define _D4_TMDS_Z0_IMPEDANCE_OPTION                            _BY_CONNECTOR
#endif

//--------------------------------------------------
// HDMI Feature Option
//--------------------------------------------------
#ifndef _HDMI_FRL_REBUILD_PHY_SUPPORT
#define _HDMI_FRL_REBUILD_PHY_SUPPORT                           _ON
#endif

//--------------------------------------------------
// HDMI 3D Video format Option
//--------------------------------------------------
#ifndef _HDMI_3D_VIDEO_IDENTIFY_SUPPORT
#define _HDMI_3D_VIDEO_IDENTIFY_SUPPORT                         _OFF
#endif

//-------------------------------------------------
// HDMI FRL Signal Detection Period (Unit:ms)
//-------------------------------------------------
#ifndef _HDMI_FRL_SIGNAL_DETECT_PERIOD
#define _HDMI_FRL_SIGNAL_DETECT_PERIOD                          500
#endif

//----------------------------------------------------------
// HDMI Clock Lane enable 200ohm impedence when power saving for low power consumption
//----------------------------------------------------------
#ifndef _TDMS_Z0_PS_CLOCK_LANE_200OHM_SUPPORT
#define _TDMS_Z0_PS_CLOCK_LANE_200OHM_SUPPORT                   _OFF
#endif

//--------------------------------------------------
// HDMI FW DSC FRL Force to DRR mode
//--------------------------------------------------
#ifndef _FW_DSC_FRL_IVS_PRODUCE_BE
#define _FW_DSC_FRL_IVS_PRODUCE_BE                              _OFF
#endif

//-------------------------------------------------
// HDMI ADVANCED HDR10 Option
//-------------------------------------------------
#ifndef _HDMI_ADVANCED_HDR10_SUPPORT_MODE
#define _HDMI_ADVANCED_HDR10_SUPPORT_MODE                       _ADVANCED_HDR10_NONE
#endif

//--------------------------------------------------
// TMDS CLK INTERRUPTION CHECK
//--------------------------------------------------
#ifndef _TMDS_NO_CLK_TRIGGER_AV_WATCHDOG
#define _TMDS_NO_CLK_TRIGGER_AV_WATCHDOG                        _OFF
#endif

//--------------------------------------------------
// TMDS FS ON ONLY TOGGLE TARGET PORT HOTPLUG
//--------------------------------------------------
#ifndef _TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT
#define _TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT                 _OFF
#endif

//--------------------------------------------------
// HDMI CLK INTERRUPTION CHECK
//--------------------------------------------------
#ifndef _HDMI_IDENTIFY_GAME_SRC_SUPPORT
#define _HDMI_IDENTIFY_GAME_SRC_SUPPORT                         _OFF
#endif

//--------------------------------------------------
// HDMI CEC Kernel Hardware Abstraction Layer(HAL) Support
//--------------------------------------------------
#ifndef _HDMI_CEC_KERNEL_HAL_SUPPORT
#define _HDMI_CEC_KERNEL_HAL_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// HDMI CEC Option (ECO Function option)
//--------------------------------------------------
#ifndef _HDMI_CEC_ARBITRATION_MODE_FIXED_VERSION
#define _HDMI_CEC_ARBITRATION_MODE_FIXED_VERSION                _ON
#endif

#ifndef _HDMI_CEC_RX_LOWIMPEDANCE_FIXED_VERSION
#define _HDMI_CEC_RX_LOWIMPEDANCE_FIXED_VERSION                 _ON
#endif

#ifndef _HDMI_CEC_MULTI_LA_FREETIME_FIXED_VERSION
#define _HDMI_CEC_MULTI_LA_FREETIME_FIXED_VERSION               _ON
#endif

#ifndef _HDMI_CEC_MATCH_ADDR_CLEAR_FIXED_VERSION
#define _HDMI_CEC_MATCH_ADDR_CLEAR_FIXED_VERSION                _ON
#endif

//--------------------------------------------------
// HDMI SQE Test
//--------------------------------------------------
#ifndef _HDMI_SQE_TEST_SUPPORT
#define _HDMI_SQE_TEST_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// HDMI ON POWER CONTROL BY CABLE DETECT
//--------------------------------------------------
#ifndef _HDMI_ON_POWER_CONTROL_BY_CABLE_DETECT
#define _HDMI_ON_POWER_CONTROL_BY_CABLE_DETECT                  _OFF
#endif

////////
// DP //
////////

//--------------------------------------------------
// DP Rx Audio DPCD Config by User Option
//--------------------------------------------------
#ifndef _DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT
#define _DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT          _OFF
#endif

//--------------------------------------------------
// DP Rx MST2SST Audio Support Option
//--------------------------------------------------
#ifndef _DP_RX_MST2SST_AUDIO_SUPPORT
#define _DP_RX_MST2SST_AUDIO_SUPPORT                            (_AUDIO_SUPPORT == _ON)
#endif

//--------------------------------------------------
// DP Rx Audio HBR Packet Receive Option
//--------------------------------------------------
#ifndef _DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL
#define _DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL                   _OFF
#endif

//--------------------------------------------------
// DP Rx MST2SST DSC Decoder Support Option
//--------------------------------------------------
#ifndef _DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT
#define _DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// DP Aux Reply Timeout by User Option
//--------------------------------------------------
#ifndef _DP_AUX_REPLY_TIMEOUT_USER_SETTING
#define _DP_AUX_REPLY_TIMEOUT_USER_SETTING                      0x0A
#endif

//--------------------------------------------------
// DP DPCD DFP Present (00005h) Set Option
//--------------------------------------------------
#ifndef _DP_DPCD_DFP_PRESENT_REF_TO
#define _DP_DPCD_DFP_PRESENT_REF_TO                             _DP_MST_CAPABILITY
#endif

#ifndef _DP_TX_SSC_SUPPORT
#define _DP_TX_SSC_SUPPORT                                      _OFF
#endif

//--------------------------------------------------
// DP Link Training Force N+1 for Marginal Link
//--------------------------------------------------
#ifndef _DP_LT_TP1_FORCE_MARGINAL_LINK
#define _DP_LT_TP1_FORCE_MARGINAL_LINK                          _ON
#endif

#ifndef _DP_LT_TP2_FORCE_MARGINAL_LINK
#define _DP_LT_TP2_FORCE_MARGINAL_LINK                          _OFF
#endif

//--------------------------------------------------
// DP Input(Rx) Port Link Training Permit Swing Level 0 for Specific Source
//--------------------------------------------------
#ifndef _DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI
#define _DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI _OFF
#endif

//--------------------------------------------------
// DP Input(Rx) Port Link Training Force Fake LT for On-Board TBT Case
//--------------------------------------------------
#ifndef _DP_LT_FORCE_FAKE_LT_FOR_TBT
#define _DP_LT_FORCE_FAKE_LT_FOR_TBT                            _OFF
#endif

//--------------------------------------------------
// DP Input(Rx) Port Link Training Permit Swing Level 0 for On-Board TBT Case
//--------------------------------------------------
#ifndef _DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT
#define _DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT                 _OFF
#endif

//--------------------------------------------------
// DP Input(Rx) Port Link Training Switch between S2P1/S3P0
//--------------------------------------------------
#ifndef _DP_LT_TP2_RETRY_FOR_S2P1_S3P0
#define _DP_LT_TP2_RETRY_FOR_S2P1_S3P0                          _OFF
#endif

//--------------------------------------------------
// DP Input(Rx) Port Link Training Request the Same Level among All Valid Lane
//--------------------------------------------------
#ifndef _DP_LT_VALID_LANE_REQUEST_THE_SAME_LEVEL
#define _DP_LT_VALID_LANE_REQUEST_THE_SAME_LEVEL                _OFF
#endif

//--------------------------------------------------
// DP Marginal Link Reduce Link Rate
//--------------------------------------------------
#ifndef _DP_MARGIN_LINK_SUPPORT
#define _DP_MARGIN_LINK_SUPPORT                                 _ON
#endif

//--------------------------------------------------
// DP Link Training Directly Request Swing Level 2 at TP1 (Skip Swing Level 1)
//--------------------------------------------------
#ifndef _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2
#define _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2                     _ON
#endif

//--------------------------------------------------
// DP Rx PHY Power Management
//--------------------------------------------------
#ifndef _DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT
#define _DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT                    _ON
#endif

//--------------------------------------------------
// DP ASSR Option
//--------------------------------------------------
#ifndef _D0_DP_ASSR_MODE_SUPPORT
#define _D0_DP_ASSR_MODE_SUPPORT                                _OFF
#endif

#ifndef _D1_DP_ASSR_MODE_SUPPORT
#define _D1_DP_ASSR_MODE_SUPPORT                                _OFF
#endif

#ifndef _D2_DP_ASSR_MODE_SUPPORT
#define _D2_DP_ASSR_MODE_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// DP pull-up Long HPD or not (after CPIRQ) by User Option
//--------------------------------------------------
#ifndef _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT
#define _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT                        _ON
#endif

//--------------------------------------------------
// DP MST Option
//--------------------------------------------------
#ifndef _D0_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                                 (_DP_MST_SUPPORT == _ON)
#endif

#ifndef _D1_DP_MST_PORT_SUPPORT
#define _D1_DP_MST_PORT_SUPPORT                                 (_DP_MST_SUPPORT == _ON)
#endif

#ifndef _D2_DP_MST_PORT_SUPPORT
#define _D2_DP_MST_PORT_SUPPORT                                 (_DP_MST_SUPPORT == _ON)
#endif

#ifndef _SOURCE_PXP_MAIN_PORT_SEARCH_STYLE
#define _SOURCE_PXP_MAIN_PORT_SEARCH_STYLE                      _DP_MST_PXP_MAIN_PORT_AUTO
#endif

#ifndef _DP_MST_PXP_FIXED_MODE_SUPPORT
#define _DP_MST_PXP_FIXED_MODE_SUPPORT                          (_DP_MST_PXP_MODE_SUPPORT == _ON)
#endif

#ifndef _DP_MST_PXP_SELECT_MODE_SUPPORT
#define _DP_MST_PXP_SELECT_MODE_SUPPORT                         (_DP_MST_PXP_MODE_SUPPORT == _ON)
#endif

#ifndef _DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT
#define _DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT                  _OFF
#endif

#ifndef _DP_TX_LOOP_BACK_DPRX_SUPPORT
#define _DP_TX_LOOP_BACK_DPRX_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// DP MAC PLL DE Only Mode with Full Last Line
//--------------------------------------------------
#ifndef _DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT
#define _DP_DE_ONLY_MODE_WITH_FULL_LAST_LINE_SUPPORT            _ON
#endif

//--------------------------------------------------
// DC On DP Long HPD Toggled Control By User
//--------------------------------------------------
#ifndef _DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT
#define _DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT                   _OFF
#endif

//--------------------------------------------------
// SST Split SDP Support
//--------------------------------------------------
#ifndef _DP_RX_SST_SPLIT_SDP_SUPPORT
#define _DP_RX_SST_SPLIT_SDP_SUPPORT                            _ON
#endif

//--------------------------------------------------
// DP IRQ HPD Implementation Mode
//--------------------------------------------------
#ifndef _DP_IRQ_HPD_MODE
#define _DP_IRQ_HPD_MODE                                        _DP_IRQ_HPD_T2_MODE
#endif

//--------------------------------------------------
// DP Rx Interlace New mode for VG877 and QD980 Certain Interlace Timing
//--------------------------------------------------
#ifndef _DP_RX_INTERLACE_NEW_MODE_SUPPORT
#define _DP_RX_INTERLACE_NEW_MODE_SUPPORT                       _ON
#endif

//--------------------------------------------------
// DP Rx TPS4 Pattern Check Type
//--------------------------------------------------
#ifndef _DP_RX_TPS4_CHECK_TYPE
#define _DP_RX_TPS4_CHECK_TYPE                                  _DP_RX_ERROR_CHECK_BY_BIST_SEED
#endif

//--------------------------------------------------
// DP Rx Msa Change IRQ Support
//--------------------------------------------------
#ifndef _DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT
#define _DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT                      _ON
#endif

//-------------------------------------------------
// DP MST Down Reply IRQ Retry
//-------------------------------------------------
#ifndef _DP_MST_DOWN_REPLY_MSG_TIME_OUT_RETRY_MAX
#define _DP_MST_DOWN_REPLY_MSG_TIME_OUT_RETRY_MAX               4
#endif

//-------------------------------------------------
// DP Tx HDCP2 Device Count Maximum
//-------------------------------------------------
#ifndef _DP_TX_HDCP2_DEVICE_COUNT_MAX
#define _DP_TX_HDCP2_DEVICE_COUNT_MAX                           31
#endif

//-------------------------------------------------
// DP Tx HDCP14 Device Count Maximum
//-------------------------------------------------
#ifndef _DP_TX_HDCP14_DEVICE_COUNT_MAX
#define _DP_TX_HDCP14_DEVICE_COUNT_MAX                          127
#endif

//-------------------------------------------------
// DP Tx Link Training Config by User (For EIZO USE)
//-------------------------------------------------
#ifndef _DP_TX_CONFIG_BY_USER_SUPPORT
#define _DP_TX_CONFIG_BY_USER_SUPPORT                           _OFF
#endif

#ifndef _DP_TX_TRAINING_SEGMENT_COMPLETE_SUPPORT
#define _DP_TX_TRAINING_SEGMENT_COMPLETE_SUPPORT                _ON
#endif

//--------------------------------------------------
// DP MST Cap On Inactive Port HPD Low (For EIZO USE)
//--------------------------------------------------
#ifndef _DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW
#define _DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW                    _OFF
#endif

//--------------------------------------------------
// DP Rx Illegal Idle Pattern Check (For EIZO USE)
//--------------------------------------------------
#ifndef _DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT
#define _DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// DP Aux Reply Ref. Clk Select From
//--------------------------------------------------
#ifndef _DP_AUX_REPLY_CLK_SEL_FROM
#define _DP_AUX_REPLY_CLK_SEL_FROM                              _DP_AUX_REPLY_SEL_IOSC
#endif

//--------------------------------------------------
// DP DRR Get IVF Type
//--------------------------------------------------
#ifndef _DP_DRR_GET_IVF_TYPE
#define _DP_DRR_GET_IVF_TYPE                                    _DP_DRR_SPD_INFO
#endif

//-------------------------------------------------
// DRR Support Freerun Display
//-------------------------------------------------
#ifndef _DRR_FREE_RUN_DISPLAY_SUPPORT
#define _DRR_FREE_RUN_DISPLAY_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// DP Long HPD Allowed By User
//--------------------------------------------------
#ifndef _DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT
#define _DP_LONG_HPD_ALLOWED_BY_USER_SUPPORT                    _OFF
#endif

//-------------------------------------------------
// DP Tx HPD High Debounce
//-------------------------------------------------
#ifndef _DP_TX_HPD_HIGH_DEBOUNCE_SUPPORT
#define _DP_TX_HPD_HIGH_DEBOUNCE_SUPPORT                        _OFF
#endif

//-------------------------------------------------
// DP ADVANCED HDR10 Option
//-------------------------------------------------
#ifndef _DP_ADVANCED_HDR10_SUPPORT_MODE
#define _DP_ADVANCED_HDR10_SUPPORT_MODE                         _ADVANCED_HDR10_NONE
#endif

//-------------------------------------------------
// DP HDCP Support CTS
//-------------------------------------------------
#ifndef _DP_HDCP14_REPEATER_CTS_SUPPORT
#define _DP_HDCP14_REPEATER_CTS_SUPPORT                         _OFF
#endif

//-------------------------------------------------
// DP MST Tx Plug CSN Debounce Support
//-------------------------------------------------
#ifndef _DP_MST_TX_PLUG_CSN_DEBOUNCE_SUPPORT
#define _DP_MST_TX_PLUG_CSN_DEBOUNCE_SUPPORT                    _OFF
#endif

//-------------------------------------------------
// DP MST Tx Plug CSN Debounce Time in ms
//-------------------------------------------------
#ifndef _DP_MST_TX_PLUG_CSN_DEBOUNCE_TIME
#define _DP_MST_TX_PLUG_CSN_DEBOUNCE_TIME                       100
#endif

//--------------------------------------------------
// DP MST Tx ENUM message reply PBN wait time
//--------------------------------------------------
#ifndef _DP_MST_ENUM_REPLY_PBN_WAIT_TIME
#define _DP_MST_ENUM_REPLY_PBN_WAIT_TIME                        SEC(0.5)
#endif

//-------------------------------------------------
// DP Rx TRAINING_AUX_RD_INTERVAL Setting at HBR2
//-------------------------------------------------
#ifndef _D0_DP_HBR2_TRAINING_AUX_RD_INTERVAL_EQ
#define _D0_DP_HBR2_TRAINING_AUX_RD_INTERVAL_EQ                 _DP_LT_AUX_RD_INTVL_EQ_400US
#endif

#ifndef _D1_DP_HBR2_TRAINING_AUX_RD_INTERVAL_EQ
#define _D1_DP_HBR2_TRAINING_AUX_RD_INTERVAL_EQ                 _DP_LT_AUX_RD_INTVL_EQ_400US
#endif

#ifndef _D2_DP_HBR2_TRAINING_AUX_RD_INTERVAL_EQ
#define _D2_DP_HBR2_TRAINING_AUX_RD_INTERVAL_EQ                 _DP_LT_AUX_RD_INTVL_EQ_400US
#endif

//-------------------------------------------------
// DP Tx Source Switch Mode in 1P Mode
//-------------------------------------------------
#ifndef _DP_TX_SOURCE_SWITCH_MODE_1P
#define _DP_TX_SOURCE_SWITCH_MODE_1P                            _DP_TX_SOURCE_AUTO
#endif

//-------------------------------------------------
// DP Tx Source Switch Mode in MtP Mode
//-------------------------------------------------
#ifndef _DP_TX_SOURCE_SWITCH_MODE_MTP
#define _DP_TX_SOURCE_SWITCH_MODE_MTP                           _DP_TX_SOURCE_FIXED_PORT
#endif

//-------------------------------------------------
// DP Tx Cloned from HDMI Support
//-------------------------------------------------
#ifndef _DP_TX_CLONE_FROM_HDMI_SUPPORT
#define _DP_TX_CLONE_FROM_HDMI_SUPPORT                          _OFF
#endif

//-------------------------------------------------
// DP Rx Dpcd Hdr for Vendor Support
//-------------------------------------------------
#ifndef _DP_HDR_VENDOR_SUPPORT
#define _DP_HDR_VENDOR_SUPPORT                                  _DP_HDR_VENDOR_SUPPORT_NONE
#endif

//--------------------------------------------------
// DP Source OUI Write Interrupt for User
//--------------------------------------------------
#ifndef _DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT
#define _DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT               _OFF
#endif

//--------------------------------------------------
// DP Ver1.1 DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_L
#define _DP_1_1_SINK_RTK_IEEE_OUI_L                             0x00
#endif

#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_M
#define _DP_1_1_SINK_RTK_IEEE_OUI_M                             0xE0
#endif

#ifndef _DP_1_1_SINK_RTK_IEEE_OUI_H
#define _DP_1_1_SINK_RTK_IEEE_OUI_H                             0x4C
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_0
#define _DP_1_1_SINK_RTK_ID_STRING_0                            0x44
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_1
#define _DP_1_1_SINK_RTK_ID_STRING_1                            0x70
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_2
#define _DP_1_1_SINK_RTK_ID_STRING_2                            0x31
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_3
#define _DP_1_1_SINK_RTK_ID_STRING_3                            0x2E
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_4
#define _DP_1_1_SINK_RTK_ID_STRING_4                            0x31
#endif

#ifndef _DP_1_1_SINK_RTK_ID_STRING_5
#define _DP_1_1_SINK_RTK_ID_STRING_5                            0x00
#endif

//--------------------------------------------------
// DP Ver1.1 DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_1_SINK_RTK_HW_VERSION
#define _DP_1_1_SINK_RTK_HW_VERSION                             0x10
#endif

#ifndef _DP_1_1_SINK_RTK_FW_VERSION_H
#define _DP_1_1_SINK_RTK_FW_VERSION_H                           0x04
#endif

#ifndef _DP_1_1_SINK_RTK_FW_VERSION_L
#define _DP_1_1_SINK_RTK_FW_VERSION_L                           0x00
#endif

//--------------------------------------------------
// DP Ver1.2 DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_L
#define _DP_1_2_SINK_RTK_IEEE_OUI_L                             0x00
#endif

#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_M
#define _DP_1_2_SINK_RTK_IEEE_OUI_M                             0xE0
#endif

#ifndef _DP_1_2_SINK_RTK_IEEE_OUI_H
#define _DP_1_2_SINK_RTK_IEEE_OUI_H                             0x4C
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_0
#define _DP_1_2_SINK_RTK_ID_STRING_0                            0x44
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_1
#define _DP_1_2_SINK_RTK_ID_STRING_1                            0x70
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_2
#define _DP_1_2_SINK_RTK_ID_STRING_2                            0x31
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_3
#define _DP_1_2_SINK_RTK_ID_STRING_3                            0x2E
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_4
#define _DP_1_2_SINK_RTK_ID_STRING_4                            0x32
#endif

#ifndef _DP_1_2_SINK_RTK_ID_STRING_5
#define _DP_1_2_SINK_RTK_ID_STRING_5                            0x00
#endif

//--------------------------------------------------
// DP Ver1.2 DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_2_SINK_RTK_HW_VERSION
#define _DP_1_2_SINK_RTK_HW_VERSION                             0x10
#endif

#ifndef _DP_1_2_SINK_RTK_FW_VERSION_H
#define _DP_1_2_SINK_RTK_FW_VERSION_H                           0x04
#endif

#ifndef _DP_1_2_SINK_RTK_FW_VERSION_L
#define _DP_1_2_SINK_RTK_FW_VERSION_L                           0x00
#endif

//--------------------------------------------------
// DP Ver1.4 DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_4_SINK_RTK_IEEE_OUI_L
#define _DP_1_4_SINK_RTK_IEEE_OUI_L                             0x00
#endif

#ifndef _DP_1_4_SINK_RTK_IEEE_OUI_M
#define _DP_1_4_SINK_RTK_IEEE_OUI_M                             0xE0
#endif

#ifndef _DP_1_4_SINK_RTK_IEEE_OUI_H
#define _DP_1_4_SINK_RTK_IEEE_OUI_H                             0x4C
#endif

#ifndef _DP_1_4_SINK_RTK_ID_STRING_0
#define _DP_1_4_SINK_RTK_ID_STRING_0                            0x44
#endif

#ifndef _DP_1_4_SINK_RTK_ID_STRING_1
#define _DP_1_4_SINK_RTK_ID_STRING_1                            0x70
#endif

#ifndef _DP_1_4_SINK_RTK_ID_STRING_2
#define _DP_1_4_SINK_RTK_ID_STRING_2                            0x31
#endif

#ifndef _DP_1_4_SINK_RTK_ID_STRING_3
#define _DP_1_4_SINK_RTK_ID_STRING_3                            0x2E
#endif

#ifndef _DP_1_4_SINK_RTK_ID_STRING_4
#define _DP_1_4_SINK_RTK_ID_STRING_4                            0x34
#endif

#ifndef _DP_1_4_SINK_RTK_ID_STRING_5
#define _DP_1_4_SINK_RTK_ID_STRING_5                            0x00
#endif

//--------------------------------------------------
// DP Ver1.4 DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_4_SINK_RTK_HW_VERSION
#define _DP_1_4_SINK_RTK_HW_VERSION                             0x10
#endif

#ifndef _DP_1_4_SINK_RTK_FW_VERSION_H
#define _DP_1_4_SINK_RTK_FW_VERSION_H                           0x04
#endif

#ifndef _DP_1_4_SINK_RTK_FW_VERSION_L
#define _DP_1_4_SINK_RTK_FW_VERSION_L                           0x00
#endif

//--------------------------------------------------
// DP Ver2.0 DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_2_0_SINK_RTK_IEEE_OUI_L
#define _DP_2_0_SINK_RTK_IEEE_OUI_L                             0x00
#endif

#ifndef _DP_2_0_SINK_RTK_IEEE_OUI_M
#define _DP_2_0_SINK_RTK_IEEE_OUI_M                             0xE0
#endif

#ifndef _DP_2_0_SINK_RTK_IEEE_OUI_H
#define _DP_2_0_SINK_RTK_IEEE_OUI_H                             0x4C
#endif

#ifndef _DP_2_0_SINK_RTK_ID_STRING_0
#define _DP_2_0_SINK_RTK_ID_STRING_0                            0x44
#endif

#ifndef _DP_2_0_SINK_RTK_ID_STRING_1
#define _DP_2_0_SINK_RTK_ID_STRING_1                            0x70
#endif

#ifndef _DP_2_0_SINK_RTK_ID_STRING_2
#define _DP_2_0_SINK_RTK_ID_STRING_2                            0x32
#endif

#ifndef _DP_2_0_SINK_RTK_ID_STRING_3
#define _DP_2_0_SINK_RTK_ID_STRING_3                            0x2E
#endif

#ifndef _DP_2_0_SINK_RTK_ID_STRING_4
#define _DP_2_0_SINK_RTK_ID_STRING_4                            0x30
#endif

#ifndef _DP_2_0_SINK_RTK_ID_STRING_5
#define _DP_2_0_SINK_RTK_ID_STRING_5                            0x00
#endif

//--------------------------------------------------
// DP Ver2.0 DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_2_0_SINK_RTK_HW_VERSION
#define _DP_2_0_SINK_RTK_HW_VERSION                             0x10
#endif

#ifndef _DP_2_0_SINK_RTK_FW_VERSION_H
#define _DP_2_0_SINK_RTK_FW_VERSION_H                           0x04
#endif

#ifndef _DP_2_0_SINK_RTK_FW_VERSION_L
#define _DP_2_0_SINK_RTK_FW_VERSION_L                           0x00
#endif

//--------------------------------------------------
// DP Ver1.1 DPCD Table Value of BRANCH IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_1_BRANCH_RTK_IEEE_OUI_L
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_L                           0x00
#endif

#ifndef _DP_1_1_BRANCH_RTK_IEEE_OUI_M
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_M                           0xE0
#endif

#ifndef _DP_1_1_BRANCH_RTK_IEEE_OUI_H
#define _DP_1_1_BRANCH_RTK_IEEE_OUI_H                           0x4C
#endif

#ifndef _DP_1_1_BRANCH_RTK_ID_STRING_0
#define _DP_1_1_BRANCH_RTK_ID_STRING_0                          0x44
#endif

#ifndef _DP_1_1_BRANCH_RTK_ID_STRING_1
#define _DP_1_1_BRANCH_RTK_ID_STRING_1                          0x70
#endif

#ifndef _DP_1_1_BRANCH_RTK_ID_STRING_2
#define _DP_1_1_BRANCH_RTK_ID_STRING_2                          0x31
#endif

#ifndef _DP_1_1_BRANCH_RTK_ID_STRING_3
#define _DP_1_1_BRANCH_RTK_ID_STRING_3                          0x2E
#endif

#ifndef _DP_1_1_BRANCH_RTK_ID_STRING_4
#define _DP_1_1_BRANCH_RTK_ID_STRING_4                          0x31
#endif

#ifndef _DP_1_1_BRANCH_RTK_ID_STRING_5
#define _DP_1_1_BRANCH_RTK_ID_STRING_5                          0x00
#endif

//--------------------------------------------------
// DP Ver1.1 DPCD Table Value Of BRANCH HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_1_BRANCH_RTK_HW_VERSION
#define _DP_1_1_BRANCH_RTK_HW_VERSION                           0x10
#endif

#ifndef _DP_1_1_BRANCH_RTK_FW_VERSION_H
#define _DP_1_1_BRANCH_RTK_FW_VERSION_H                         0x04
#endif

#ifndef _DP_1_1_BRANCH_RTK_FW_VERSION_L
#define _DP_1_1_BRANCH_RTK_FW_VERSION_L                         0x01
#endif

//--------------------------------------------------
// DP Ver1.2 DPCD Table Value of BRANCH IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_2_BRANCH_RTK_IEEE_OUI_L
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_L                           0x00
#endif

#ifndef _DP_1_2_BRANCH_RTK_IEEE_OUI_M
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_M                           0xE0
#endif

#ifndef _DP_1_2_BRANCH_RTK_IEEE_OUI_H
#define _DP_1_2_BRANCH_RTK_IEEE_OUI_H                           0x4C
#endif

#ifndef _DP_1_2_BRANCH_RTK_ID_STRING_0
#define _DP_1_2_BRANCH_RTK_ID_STRING_0                          0x44
#endif

#ifndef _DP_1_2_BRANCH_RTK_ID_STRING_1
#define _DP_1_2_BRANCH_RTK_ID_STRING_1                          0x70
#endif

#ifndef _DP_1_2_BRANCH_RTK_ID_STRING_2
#define _DP_1_2_BRANCH_RTK_ID_STRING_2                          0x31
#endif

#ifndef _DP_1_2_BRANCH_RTK_ID_STRING_3
#define _DP_1_2_BRANCH_RTK_ID_STRING_3                          0x2E
#endif

#ifndef _DP_1_2_BRANCH_RTK_ID_STRING_4
#define _DP_1_2_BRANCH_RTK_ID_STRING_4                          0x32
#endif

#ifndef _DP_1_2_BRANCH_RTK_ID_STRING_5
#define _DP_1_2_BRANCH_RTK_ID_STRING_5                          0x00
#endif

//--------------------------------------------------
// DP Ver1.2 DPCD Table Value Of BRANCH HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_2_BRANCH_RTK_HW_VERSION
#define _DP_1_2_BRANCH_RTK_HW_VERSION                           0x10
#endif

#ifndef _DP_1_2_BRANCH_RTK_FW_VERSION_H
#define _DP_1_2_BRANCH_RTK_FW_VERSION_H                         0x04
#endif

#ifndef _DP_1_2_BRANCH_RTK_FW_VERSION_L
#define _DP_1_2_BRANCH_RTK_FW_VERSION_L                         0x01
#endif

//--------------------------------------------------
// DP Ver1.4 DPCD Table Value of BRANCH IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_1_4_BRANCH_RTK_IEEE_OUI_L
#define _DP_1_4_BRANCH_RTK_IEEE_OUI_L                           0x00
#endif

#ifndef _DP_1_4_BRANCH_RTK_IEEE_OUI_M
#define _DP_1_4_BRANCH_RTK_IEEE_OUI_M                           0xE0
#endif

#ifndef _DP_1_4_BRANCH_RTK_IEEE_OUI_H
#define _DP_1_4_BRANCH_RTK_IEEE_OUI_H                           0x4C
#endif

#ifndef _DP_1_4_BRANCH_RTK_ID_STRING_0
#define _DP_1_4_BRANCH_RTK_ID_STRING_0                          0x44
#endif

#ifndef _DP_1_4_BRANCH_RTK_ID_STRING_1
#define _DP_1_4_BRANCH_RTK_ID_STRING_1                          0x70
#endif

#ifndef _DP_1_4_BRANCH_RTK_ID_STRING_2
#define _DP_1_4_BRANCH_RTK_ID_STRING_2                          0x31
#endif

#ifndef _DP_1_4_BRANCH_RTK_ID_STRING_3
#define _DP_1_4_BRANCH_RTK_ID_STRING_3                          0x2E
#endif

#ifndef _DP_1_4_BRANCH_RTK_ID_STRING_4
#define _DP_1_4_BRANCH_RTK_ID_STRING_4                          0x34
#endif

#ifndef _DP_1_4_BRANCH_RTK_ID_STRING_5
#define _DP_1_4_BRANCH_RTK_ID_STRING_5                          0x00
#endif

//--------------------------------------------------
// DP Ver1.4 DPCD Table Value Of BRANCH HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_1_4_BRANCH_RTK_HW_VERSION
#define _DP_1_4_BRANCH_RTK_HW_VERSION                           0x10
#endif

#ifndef _DP_1_4_BRANCH_RTK_FW_VERSION_H
#define _DP_1_4_BRANCH_RTK_FW_VERSION_H                         0x04
#endif

#ifndef _DP_1_4_BRANCH_RTK_FW_VERSION_L
#define _DP_1_4_BRANCH_RTK_FW_VERSION_L                         0x01
#endif

//--------------------------------------------------
// DP Ver2.0 DPCD Table Value of BRANCH IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_2_0_BRANCH_RTK_IEEE_OUI_L
#define _DP_2_0_BRANCH_RTK_IEEE_OUI_L                           0x00
#endif

#ifndef _DP_2_0_BRANCH_RTK_IEEE_OUI_M
#define _DP_2_0_BRANCH_RTK_IEEE_OUI_M                           0xE0
#endif

#ifndef _DP_2_0_BRANCH_RTK_IEEE_OUI_H
#define _DP_2_0_BRANCH_RTK_IEEE_OUI_H                           0x4C
#endif

#ifndef _DP_2_0_BRANCH_RTK_ID_STRING_0
#define _DP_2_0_BRANCH_RTK_ID_STRING_0                          0x44
#endif

#ifndef _DP_2_0_BRANCH_RTK_ID_STRING_1
#define _DP_2_0_BRANCH_RTK_ID_STRING_1                          0x70
#endif

#ifndef _DP_2_0_BRANCH_RTK_ID_STRING_2
#define _DP_2_0_BRANCH_RTK_ID_STRING_2                          0x32
#endif

#ifndef _DP_2_0_BRANCH_RTK_ID_STRING_3
#define _DP_2_0_BRANCH_RTK_ID_STRING_3                          0x2E
#endif

#ifndef _DP_2_0_BRANCH_RTK_ID_STRING_4
#define _DP_2_0_BRANCH_RTK_ID_STRING_4                          0x30
#endif

#ifndef _DP_2_0_BRANCH_RTK_ID_STRING_5
#define _DP_2_0_BRANCH_RTK_ID_STRING_5                          0x00
#endif

//--------------------------------------------------
// DP Ver2.0 DPCD Table Value Of BRANCH HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_2_0_BRANCH_RTK_HW_VERSION
#define _DP_2_0_BRANCH_RTK_HW_VERSION                           0x10
#endif

#ifndef _DP_2_0_BRANCH_RTK_FW_VERSION_H
#define _DP_2_0_BRANCH_RTK_FW_VERSION_H                         0x04
#endif

#ifndef _DP_2_0_BRANCH_RTK_FW_VERSION_L
#define _DP_2_0_BRANCH_RTK_FW_VERSION_L                         0x01
#endif

//--------------------------------------------------
// Dp ALPM Support
//--------------------------------------------------
#ifndef _DP_AUXLESS_ALPM_SUPPORT
#define _DP_AUXLESS_ALPM_SUPPORT                                _OFF
#endif


////////////
// TYPE C //
////////////

//-------------------------------------------------
// USB Type C Port Controller Pin Assignment E Support Switch Option
//-------------------------------------------------
#ifndef _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT
#define _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT         _OFF
#endif

//--------------------------------------------------
// USB Type C Adapter Voltage Setting (Unit = 0.1v)
//--------------------------------------------------
#ifndef _TYPE_C_ADAPTOR_VOLTAGE
#define _TYPE_C_ADAPTOR_VOLTAGE                                 120UL
#endif

//--------------------------------------------------
// USB Type C Port Controller Alt Mode Option
//--------------------------------------------------
#ifndef _TYPE_C_VENDOR_ALT_MODE
#define _TYPE_C_VENDOR_ALT_MODE                                 _TYPE_C_VENDOR_ALT_MODE_NONE
#endif

#ifndef _TYPE_C_EMB_DP_ALT_MODE_URL_INDEX
#define _TYPE_C_EMB_DP_ALT_MODE_URL_INDEX                       _TYPE_C_BILLBOARD_URL_INDEX_DP
#endif

#ifndef _TYPE_C_EMB_LENOVO_ALT_MODE_URL_INDEX
#define _TYPE_C_EMB_LENOVO_ALT_MODE_URL_INDEX                   _TYPE_C_BILLBOARD_URL_INDEX_LENOVO
#endif

#ifndef _TYPE_C_RTS_DP_ALT_MODE_URL_INDEX
#define _TYPE_C_RTS_DP_ALT_MODE_URL_INDEX                       _TYPE_C_BILLBOARD_URL_INDEX_DP
#endif

#ifndef _TYPE_C_USER_DP_ALT_MODE_URL_INDEX
#define _TYPE_C_USER_DP_ALT_MODE_URL_INDEX                      _TYPE_C_BILLBOARD_URL_INDEX_DP
#endif
//--------------------------------------------------
// USB Type C Embedded Port Controller Option
//--------------------------------------------------
#ifndef _TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA
#define _TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA                 _FALSE
#endif

#ifndef _TYPE_C_EMB_UFP_PRODUCT_TYPE
#define _TYPE_C_EMB_UFP_PRODUCT_TYPE                            _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT
#endif

#ifndef _TYPE_C_EMB_BRAND_OPTION
#define _TYPE_C_EMB_BRAND_OPTION                                _TYPE_C_EMB_BRAND_NONE
#endif

//--------------------------------------------------
// USB Type C RTS Port Controller Option
//--------------------------------------------------
#ifndef _TYPE_C_PORT_CTRL_RTS_FW_SPEC_VER
#define _TYPE_C_PORT_CTRL_RTS_FW_SPEC_VER                       _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D9
#endif

#ifndef _TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME
#define _TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME               _PORT_CTRL_RTS_STATUS_POLLING_TIME_500MS
#endif

#ifndef _TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT
#define _TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT                  _OFF
#endif

#ifndef _TYPE_C_PORT_CTRL_RTS_SMBUS_MODE
#define _TYPE_C_PORT_CTRL_RTS_SMBUS_MODE                        _PORT_CTRL_RTS_POLLING_MODE
#endif

//--------------------------------------------------
// Arbitration Type Select Between RTS Hub And Scaler Chip
//--------------------------------------------------
#ifndef _SMBUS_ARBITRATION_MODE_SEL
#define _SMBUS_ARBITRATION_MODE_SEL                             _SMBUS_ARBITRATION_NONE
#endif

//--------------------------------------------------
// TYPEC Customized Value of BB PID/VID Option (For EIZO USE)
//--------------------------------------------------
#ifndef _EIZO_CUSTOMIZED_BB_SUPPORT
#define _EIZO_CUSTOMIZED_BB_SUPPORT                             _OFF
#endif

//--------------------------------------------------
// USB Type C & Billboard Option
//--------------------------------------------------
#ifndef _USB_EIZO_PRODUCT_ID_H
#define _USB_EIZO_PRODUCT_ID_H                                  0x00
#endif

#ifndef _USB_EIZO_PRODUCT_ID_L
#define _USB_EIZO_PRODUCT_ID_L                                  0x00
#endif

#ifndef _USB_EIZO_VENDOR_ID_H
#define _USB_EIZO_VENDOR_ID_H                                   0x0B
#endif

#ifndef _USB_EIZO_VENDOR_ID_L
#define _USB_EIZO_VENDOR_ID_L                                   0xDA
#endif

#ifndef _USB_VENDOR_ID_H
#define _USB_VENDOR_ID_H                                        0x0B
#endif

#ifndef _USB_VENDOR_ID_L
#define _USB_VENDOR_ID_L                                        0xDA
#endif

//--------------------------------------------------
// USB Type C & PMIC OCP/OVP Process Option
//--------------------------------------------------
#ifndef _TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION
#define _TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION                     _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET
#endif

//--------------------------------------------------
// USB Type C Eizo Customized DP Lane Cnt Option
//--------------------------------------------------
#ifndef _TYPE_C_EIZO_CUSTOMIZED_DP_LANE_CNT_SUPPORT
#define _TYPE_C_EIZO_CUSTOMIZED_DP_LANE_CNT_SUPPORT             _OFF
#endif

//--------------------------------------------------
// USB Type C Eizo Customized OCP Threshold Option
//--------------------------------------------------
#ifndef _TYPE_C_EIZO_CUSTOMIZED_OCP_THRESHOLD_SUPPORT
#define _TYPE_C_EIZO_CUSTOMIZED_OCP_THRESHOLD_SUPPORT           _OFF
#endif

//--------------------------------------------------
// USB Type C Eizo Customized PMIC Flow
//--------------------------------------------------
#ifndef _TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT
#define _TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT            _OFF
#endif

//--------------------------------------------------
// USB Type C Eizo Customized Vbus Check Timer Option
//--------------------------------------------------
#ifndef _TYPE_C_EIZO_CUSTOMIZED_VBUS_CHECK_TIMER_SUPPORT
#define _TYPE_C_EIZO_CUSTOMIZED_VBUS_CHECK_TIMER_SUPPORT        _OFF
#endif

//--------------------------------------------------
// USB Type C Send GET_SNK_CAP PD Message TImer
//--------------------------------------------------
#ifndef _TYPE_C_SRC_GET_SNK_CAP_WAIT_TIMER
#define _TYPE_C_SRC_GET_SNK_CAP_WAIT_TIMER                      50
#endif

#ifndef _TYPE_C_SNK_GET_SNK_CAP_WAIT_TIMER
#define _TYPE_C_SNK_GET_SNK_CAP_WAIT_TIMER                      40
#endif

//--------------------------------------------------
// USB Type C Cable Status Change by ALT Mode Option
//--------------------------------------------------
#ifndef _TYPE_C_CABLE_STATUS_CHANGE_BY_ALT_MODE_SUPPORT
#define _TYPE_C_CABLE_STATUS_CHANGE_BY_ALT_MODE_SUPPORT         _OFF
#endif

//--------------------------------------------------
// Billboard String iManufacture String Option (for EIZO USE)
//--------------------------------------------------
#define _USER_TYPE_C_BB_STRING_MANFAC_SUPPORT                   _OFF
#define _USER_TYPE_C_BB_STRING_MANFAC                           "RTD2020UseriManufacturerStringTable.h"


//////////////////
// Usb Function //
//////////////////

//--------------------------------------------------
// User code Billboard Program support
//--------------------------------------------------
#ifndef _USB_TYPE_C_BB_PROGRAM_SUPPORT
#define _USB_TYPE_C_BB_PROGRAM_SUPPORT                          _OFF
#endif

//--------------------------------------------------
// BB HID Type Support
//--------------------------------------------------
#ifndef _USB_BB_HID_TYPE_SUPPORT
#define _USB_BB_HID_TYPE_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// U2Host Dump Dolby Related Data Support
//--------------------------------------------------
#ifndef _USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT
#define _USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT                    _OFF
#endif

//--------------------------------------------------
// U2Host CDC Device Support
//--------------------------------------------------
#ifndef _USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT
#define _USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// USB3 FW Disable Unused Lane Support
//--------------------------------------------------
#ifndef _U3_DYNAMIC_POWER_MANAGEMENT_SUPPORT
#define _U3_DYNAMIC_POWER_MANAGEMENT_SUPPORT                    _ON
#endif

//////////
// Dfp //
//////////

//-------------------------------------------------
// DFP Sink EDID Change Check Method Select
//-------------------------------------------------
#ifndef _DFP_SINK_EDID_CHANGE_CHECK_METHOD
#define _DFP_SINK_EDID_CHANGE_CHECK_METHOD                      _EDID_SHA_CODE
#endif

//-------------------------------------------------
// DFP Sink EDID Report Source Method Select
//-------------------------------------------------
#ifndef _MST_DFP_SINK_EDID_REPORT_SOURCE_METHOD
#define _MST_DFP_SINK_EDID_REPORT_SOURCE_METHOD                 _BYPASS_RAW_DATA
#endif


///////////
// Audio //
///////////

//-------------------------------------------------
// Audio FW tracking Option (Support <= 48kHz)
//-------------------------------------------------
#ifndef _HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT
#define _HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT                    _OFF
#endif

//-------------------------------------------------
// Audio Spread P Code Option
//-------------------------------------------------
#ifndef _HDMI_AUDIO_SPREAD_PCODE_SUPPORT
#define _HDMI_AUDIO_SPREAD_PCODE_SUPPORT                        _ON
#endif

//-------------------------------------------------
// Audio Compress Audio Support On
//-------------------------------------------------
#ifndef _AUDIO_COMPRESS_SUPPORT
#define _AUDIO_COMPRESS_SUPPORT                                 _OFF
#endif

//-------------------------------------------------
// Audio Parallel Mode Support On
//-------------------------------------------------
#ifndef _SPDIF_PARALLEL_MODE_SUPPORT
#define _SPDIF_PARALLEL_MODE_SUPPORT                            _OFF
#endif

#ifndef _I2S_PARALLEL_MODE_SUPPORT
#define _I2S_PARALLEL_MODE_SUPPORT                              _OFF
#endif

//-------------------------------------------------
// Audio DAC Option
//-------------------------------------------------
#ifndef _DAC_SPEAKER_OUTPUT_SWAP
#define _DAC_SPEAKER_OUTPUT_SWAP                                _OFF
#endif

#ifndef _DAC_HP_OUTPUT_SWAP
#define _DAC_HP_OUTPUT_SWAP                                     _OFF
#endif

#ifndef _DAC_DEPOP_TO_NORMAL_WAIT_TIME
#define _DAC_DEPOP_TO_NORMAL_WAIT_TIME                          SEC(0.1)
#endif

#ifndef _DAC_DITHER_FUNCTION_LEVEL
#define _DAC_DITHER_FUNCTION_LEVEL                              _AUDIO_DAC_DITHER_LEVEL_OFF
#endif

//--------------------------------------------------
// Audio Line In AA DAC Bypass Option
//--------------------------------------------------
#ifndef _LINE_IN_AA_PATH_SUPPORT
#define _LINE_IN_AA_PATH_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// Audio Line In Support For DP TX Clone Option
//--------------------------------------------------
#ifndef _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT
#define _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT                      _ON
#endif

//--------------------------------------------------
// Digital Volume Control Option --> For Audio Mute
//--------------------------------------------------
#ifndef _DVC_ADJUST_TYPE
#define _DVC_ADJUST_TYPE                                        _DB_GAIN
#endif

#ifndef _DB_GAIN_DOWN_VALUE
#define _DB_GAIN_DOWN_VALUE                                     _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _DB_GAIN_UP_VALUE
#define _DB_GAIN_UP_VALUE                                       _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _DB_GAIN_FAST_DOWN_VALUE
#define _DB_GAIN_FAST_DOWN_VALUE                                _DB_GAIN_1_8_DB   // For _DB_GAIN at Playbackcheck status
#endif

#ifndef _DB_GAIN_FAST_UP_VALUE
#define _DB_GAIN_FAST_UP_VALUE                                  _DB_GAIN_1_8_DB   // For _DB_GAIN at Playbackcheck status
#endif

#ifndef _VOLUME_STEP_SIZE_VALUE
#define _VOLUME_STEP_SIZE_VALUE                                 (0x0040 & 0x3FFF) // For _VOLUME_STEP_SIZE
#endif

#ifndef _DVC_VOLUME_MUTE_TIMER
#define _DVC_VOLUME_MUTE_TIMER                                  400 // ms
#endif

#ifndef _DVC_FAST_VOLUME_MUTE_TIMER
#define _DVC_FAST_VOLUME_MUTE_TIMER                             10 // ms
#endif

#ifndef _DVC_FAST_VOLUME_UNMUTE_TIMER
#define _DVC_FAST_VOLUME_UNMUTE_TIMER                           75 // ms
#endif

//--------------------------------------------------
// DP Volume Control Option --> For Audio Mute / Unmute
//--------------------------------------------------
#ifndef _DP_DVC_ADJUST_TYPE
#define _DP_DVC_ADJUST_TYPE                                     _DB_GAIN
#endif

#ifndef _DP_DB_GAIN_DOWN_VALUE
#define _DP_DB_GAIN_DOWN_VALUE                                  _DB_GAIN_1_8_DB   // For _DB_GAIN Mode
#endif

#ifndef _DP_DB_GAIN_UP_VALUE
#define _DP_DB_GAIN_UP_VALUE                                    _DB_GAIN_1_8_DB   // For _DB_GAIN Mode
#endif

#ifndef _DP_VOLUME_STEP_SIZE_VALUE
#define _DP_VOLUME_STEP_SIZE_VALUE                              (0x40 & 0xFF) // For _VOLUME_STEP Mode
#endif

#ifndef _DP_DVC_VOLUME_MUTE_TIMER
#define _DP_DVC_VOLUME_MUTE_TIMER                               400 // ms
#endif

//--------------------------------------------------
// Audio Manual Sampling Frequency Option
//--------------------------------------------------
#ifndef _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT
#define _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT                     _OFF
#endif

#ifndef _FIX_SAMPLING_FREQ_TYPE
#define _FIX_SAMPLING_FREQ_TYPE                                 _FIX_FREQ_48KHZ
#endif

//--------------------------------------------------
// Switch Audio Source to Line In When Entering Power Saving Mode Option
//--------------------------------------------------
#ifndef _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE
#define _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE           _OFF
#endif

//-------------------------------------------------
// Audio Hard Gain Option
//-------------------------------------------------
#ifndef _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT
#define _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT                     _OFF
#endif

#ifndef _LINE_IN_HARD_GAIN_VALUE
#define _LINE_IN_HARD_GAIN_VALUE                                _HARD_GAIN_0_DB
#endif

#ifndef _DIGITAL_HARD_GAIN_VALUE
#define _DIGITAL_HARD_GAIN_VALUE                                _HARD_GAIN_0_DB
#endif

//-------------------------------------------------
// Audio Digital Output(I2S/SPDIF) Adjust Volume Option
//-------------------------------------------------
#ifndef _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT
#define _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT             _OFF
#endif

//-------------------------------------------------
// Audio Digital Output(I2S/SPDIF) Force Channel 0/1 Option
//-------------------------------------------------
#ifndef _DIGITAL_AUDIO_OUTPUT_FORCE_CHANNEL_0_1_SUPPORT
#define _DIGITAL_AUDIO_OUTPUT_FORCE_CHANNEL_0_1_SUPPORT         _OFF
#endif

//-------------------------------------------------
// Audio OSD Mute Disable External Dsp Power Down Option
//-------------------------------------------------
#ifndef _AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT
#define _AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT                _OFF
#endif

//-------------------------------------------------
// PIP Sub Reserve BW type
//-------------------------------------------------
#ifndef _PIP_SUB_BW_RESERVE_TYPE
#define _PIP_SUB_BW_RESERVE_TYPE                                _SUB_QUARTER_RESOLUTION
#endif

//-------------------------------------------------
// PIP Sub Reserve BW Max Hwidth
//-------------------------------------------------
#ifndef _PIP_SUB_BW_RESERVE_MAX_HWIDTH
#define _PIP_SUB_BW_RESERVE_MAX_HWIDTH                          (_PANEL_DH_WIDTH / 2)
#endif

//-------------------------------------------------
// Mtp Vporch Min us for Main and Sub (sub: _SUB_QUARTER_RESOLUTION or _EAGLE_SIGHT_)
//-------------------------------------------------
#ifndef _PIP_SUB_BW_RESERVE_INPUT_CVT_TIMING_VPORCH_MIN_US
#define _PIP_SUB_BW_RESERVE_INPUT_CVT_TIMING_VPORCH_MIN_US      (460) // unit: us
#endif

//--------------------------------------------------
// Audio Output Sampling Limit Option
//--------------------------------------------------
#ifndef _AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT
#define _AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT               _OFF
#endif

//--------------------------------------------------
// Audio Output Sampling Limit Option
//--------------------------------------------------
#ifndef _HDMI_AUDIO_FREQ_LIMIT_FORCE_DEFINE_CLK_SUPPORT
#define _HDMI_AUDIO_FREQ_LIMIT_FORCE_DEFINE_CLK_SUPPORT         _OFF
#endif

//--------------------------------------------------
// Audio Test by Internal Audio Generator
//--------------------------------------------------
#ifndef _INTERNAL_AUDIO_TEST_SUPPORT
#define _INTERNAL_AUDIO_TEST_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// Audio Test by Internal Audio Generator Channel Select
//--------------------------------------------------
#ifndef _INTERNAL_AUDIO_CHANNEL_CONFIG_BY_USER_SUPPORT
#define _INTERNAL_AUDIO_CHANNEL_CONFIG_BY_USER_SUPPORT          _OFF
#endif

//--------------------------------------------------
// Audio Test Option for Keeping Enable With Fix Port
//--------------------------------------------------
#ifndef _INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT
#define _INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT                   _OFF
#endif

//-------------------------------------------------
// Audio Ignort Flat flag
//-------------------------------------------------
#ifndef _HDMI_AUDIO_IGNORE_FLAT_FLAG_SUPPORT
#define _HDMI_AUDIO_IGNORE_FLAT_FLAG_SUPPORT                    _OFF
#endif

//-------------------------------------------------
// Audio Initiate ARC/eARC HPD Time
//-------------------------------------------------
#ifndef _HDMI_ARC_EARC_PORT_HPD_LOW_DURATION
#define _HDMI_ARC_EARC_PORT_HPD_LOW_DURATION                    800
#endif

//--------------------------------------------------
//  Audio ARC Tx High Level Behavior FW Type
//--------------------------------------------------
#ifndef _AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE
#define _AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE                        _ARC_TX_HIGH_LEVEL_FW_TYPE_USER
#endif

////////////////////
// Thermal Sensor //
////////////////////

//--------------------------------------------------
// Thermal Sensor Option
//--------------------------------------------------
#ifndef _THERMAL_SENSOR_SUPPORT
#define _THERMAL_SENSOR_SUPPORT                                 _OFF
#endif

////////////////////
// DDR3 PLL SSC   //
////////////////////

//--------------------------------------------------
// DDR3 PLL SSC Support
//--------------------------------------------------
#ifndef _DDR3PLL_SSC_SUPPORT
#define _DDR3PLL_SSC_SUPPORT                                    _OFF
#endif

//--------------------------------------------------
// DDR3 PLL SSC Amplitude
//--------------------------------------------------
#ifndef _DDR3PLL_SSC_AMPLITUDE
#define _DDR3PLL_SSC_AMPLITUDE                                  _1_PERCENT // Support 1% & 2%
#endif

//--------------------------------------------------
// DDR3 KGD DDC Support
//--------------------------------------------------
#ifndef _DDR3_KGD_DCC_SUPPORT
#define _DDR3_KGD_DCC_SUPPORT                                   _ON
#endif

///////////////////
// Misc Function //
///////////////////

//--------------------------------------------------
// UART Option
//--------------------------------------------------
#ifndef _UART_BAUD_RATE_POWER_NORMAL
#define _UART_BAUD_RATE_POWER_NORMAL                            9600 // 9600/19200/14400/28800/38400/56000 Baud (Unit in Baud)
#endif

#ifndef _UART_BAUD_RATE_POWER_SAVING
#define _UART_BAUD_RATE_POWER_SAVING                            9600 // 9600/19200/14400/28800/38400/56000 Baud (Unit in Baud)
#endif

//-------------------------------------------------
// System Timer 250us Option --> SW IR Application
//-------------------------------------------------
#ifndef _SYSTEM_TIMER_QUARTER_RESOLUTION
#define _SYSTEM_TIMER_QUARTER_RESOLUTION                        _OFF
#endif

//--------------------------------------------------
//  Factory Debug Option --> Extern ScalerSetByte, ScalerGetByte, ScalerSetBit, ScalerGetBit to User
//--------------------------------------------------
#ifndef _FACTORY_DEBUG_SUPPORT
#define _FACTORY_DEBUG_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// Display Garbage Prevent Method Option
//--------------------------------------------------
#ifndef _DISPLAY_PREVENT_GARBAGE_METHOD
#define _DISPLAY_PREVENT_GARBAGE_METHOD                         _GARBAGE_PREVENT_BY_WATCH_DOG
#endif

//--------------------------------------------------
// SPD Info FreeSync Enable Reference
//--------------------------------------------------
#ifndef _SPD_INFO_FREESYNC_ENABLE_REF
#define _SPD_INFO_FREESYNC_ENABLE_REF                           _REF_DRR_GET_TYPE
#endif

//-------------------------------------------------
// Panel Power Sequence Control by User Option
//-------------------------------------------------
#ifndef _PANEL_POWER_SEQUENCE_CONTROL_BY_USER
#define _PANEL_POWER_SEQUENCE_CONTROL_BY_USER                   _OFF
#endif

//-------------------------------------------------
// Color Process Control by User Option
//-------------------------------------------------
#ifndef _COLOR_PROCESS_CONTROL_BY_USER
#define _COLOR_PROCESS_CONTROL_BY_USER                          _OFF
#endif

//-------------------------------------------------
// Flash Enable Write protect Option
//-------------------------------------------------
#ifndef _FLASH_WR_PROTECT
#define _FLASH_WR_PROTECT                                       _OFF
#endif

//-------------------------------------------------
// FLASH Write SR Mode Select Eable Write SR CMD
//--------------------------------------------------
#ifndef _FLASH_EWSR_FUNCTION_SUPPORT
#define _FLASH_EWSR_FUNCTION_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// SPI Option
//--------------------------------------------------
#ifndef _PROJECT_SPI0_CLK_PRE_DIV
#define _PROJECT_SPI0_CLK_PRE_DIV                               0                   // SPI CLK PreDivider
#endif
#ifndef _PROJECT_SPI0_CLK_DIV
#define _PROJECT_SPI0_CLK_DIV                                   _DIV_4              // SPI CLK Divider
#endif
#ifndef _PROJECT_SPI0_ENUM_PROTOCOL_SEL
#define _PROJECT_SPI0_ENUM_PROTOCOL_SEL                         _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PROJECT_SPI0_ENUM_CLK_SRC_SEL
#define _PROJECT_SPI0_ENUM_CLK_SRC_SEL                          _SPI_EXT_XTAL_CLK   // SPI CLK Source
#endif
#ifndef _PROJECT_SPI0_MOSI_IDLE_STATE
#define _PROJECT_SPI0_MOSI_IDLE_STATE                           _HIGH               // 0:low ; 1:high
#endif
#ifndef _PROJECT_SPI0_SCLK_IDLE_STATE
#define _PROJECT_SPI0_SCLK_IDLE_STATE                           _HIGH               // 0:low ; 1:high
#endif
#ifndef _PROJECT_SPI0_CS_SEL
#define _PROJECT_SPI0_CS_SEL                                    0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PROJECT_SPI0_CS_POLARITY
#define _PROJECT_SPI0_CS_POLARITY                               0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PROJECT_SPI0_CS_SETUP
#define _PROJECT_SPI0_CS_SETUP                                  0                   // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PROJECT_SPI0_CS_HOLD
#define _PROJECT_SPI0_CS_HOLD                                   0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PROJECT_SPI0_SUPPRESS_BITS
#define _PROJECT_SPI0_SUPPRESS_BITS                             0                   // SPI Suppress Bits(value = 0~7)
#endif

#ifndef _PROJECT_SPI1_CLK_PRE_DIV
#define _PROJECT_SPI1_CLK_PRE_DIV                               0                   // SPI CLK PreDivider
#endif
#ifndef _PROJECT_SPI1_CLK_DIV
#define _PROJECT_SPI1_CLK_DIV                                   _DIV_4              // SPI CLK Divider
#endif
#ifndef _PROJECT_SPI1_ENUM_PROTOCOL_SEL
#define _PROJECT_SPI1_ENUM_PROTOCOL_SEL                         _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PROJECT_SPI1_ENUM_CLK_SRC_SEL
#define _PROJECT_SPI1_ENUM_CLK_SRC_SEL                          _SPI_EXT_XTAL_CLK   // SPI CLK Source
#endif
#ifndef _PROJECT_SPI1_MOSI_IDLE_STATE
#define _PROJECT_SPI1_MOSI_IDLE_STATE                           _HIGH               // 0:low ; 1:high
#endif
#ifndef _PROJECT_SPI1_SCLK_IDLE_STATE
#define _PROJECT_SPI1_SCLK_IDLE_STATE                           _HIGH               // 0:low ; 1:high
#endif
#ifndef _PROJECT_SPI1_CS_SEL
#define _PROJECT_SPI1_CS_SEL                                    0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PROJECT_SPI1_CS_POLARITY
#define _PROJECT_SPI1_CS_POLARITY                               0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PROJECT_SPI1_CS_SETUP
#define _PROJECT_SPI1_CS_SETUP                                  0                   // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PROJECT_SPI1_CS_HOLD
#define _PROJECT_SPI1_CS_HOLD                                   0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PROJECT_SPI1_SUPPRESS_BITS
#define _PROJECT_SPI1_SUPPRESS_BITS                             0                   // SPI Suppress Bits(value = 0~7)
#endif

#ifndef _PROJECT_SPI2_CLK_PRE_DIV
#define _PROJECT_SPI2_CLK_PRE_DIV                               0                   // SPI CLK PreDivider
#endif
#ifndef _PROJECT_SPI2_CLK_DIV
#define _PROJECT_SPI2_CLK_DIV                                   _DIV_4              // SPI CLK Divider
#endif
#ifndef _PROJECT_SPI2_ENUM_PROTOCOL_SEL
#define _PROJECT_SPI2_ENUM_PROTOCOL_SEL                         _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PROJECT_SPI2_ENUM_CLK_SRC_SEL
#define _PROJECT_SPI2_ENUM_CLK_SRC_SEL                          _SPI_EXT_XTAL_CLK   // SPI CLK Source
#endif
#ifndef _PROJECT_SPI2_MOSI_IDLE_STATE
#define _PROJECT_SPI2_MOSI_IDLE_STATE                           _HIGH               // 0:low ; 1:high
#endif
#ifndef _PROJECT_SPI2_SCLK_IDLE_STATE
#define _PROJECT_SPI2_SCLK_IDLE_STATE                           _HIGH               // 0:low ; 1:high
#endif
#ifndef _PROJECT_SPI2_CS_SEL
#define _PROJECT_SPI2_CS_SEL                                    0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PROJECT_SPI2_CS_POLARITY
#define _PROJECT_SPI2_CS_POLARITY                               0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PROJECT_SPI2_CS_SETUP
#define _PROJECT_SPI2_CS_SETUP                                  0                   // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PROJECT_SPI2_CS_HOLD
#define _PROJECT_SPI2_CS_HOLD                                   0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PROJECT_SPI2_SUPPRESS_BITS
#define _PROJECT_SPI2_SUPPRESS_BITS                             0                   // SPI Suppress Bits(value = 0~7)
#endif

//-------------------------------------------------
// Eizo DDCCI Code Reduction Option
//-------------------------------------------------
#ifndef _DDCCI_CODE_REDUCTION
#define _DDCCI_CODE_REDUCTION                                   _OFF
#endif

//--------------------------------------------------
// System Eeprom Customization
//--------------------------------------------------
#ifndef _USER_SYSTEM_EEPROM_CUSTOMIZATION
#define _USER_SYSTEM_EEPROM_CUSTOMIZATION                       _OFF
#endif

//--------------------------------------------------
// Eizo GDI Power Cut Option
//--------------------------------------------------
#ifndef _DP_HDMI_COMPATIBLE_MODE
#define _DP_HDMI_COMPATIBLE_MODE                                _OFF
#endif

//--------------------------------------------------
// Eizo GDI Power Cut Option
//--------------------------------------------------
#ifndef _DP_HDMI_COMPATIBLE_MODE_ENHANCED
#define _DP_HDMI_COMPATIBLE_MODE_ENHANCED                       _OFF
#endif

//--------------------------------------------------
// Power Saving Precision Clock Option
//--------------------------------------------------
#ifndef _SYS_PS_TIMER_PRECISION_SUPPPORT
#define _SYS_PS_TIMER_PRECISION_SUPPPORT                        _OFF
#endif


//////////
// Acer //
//////////

//-------------------------------------------------
// Acer TMDS Toggle HPD & Z0 Option
//-------------------------------------------------
#ifndef _TMDS_TOGGLE_HPD_Z0_FOR_ACER
#define _TMDS_TOGGLE_HPD_Z0_FOR_ACER                            _OFF
#endif


//////////
// Asus //
//////////

//-------------------------------------------------
// Asus Auto Search Time Option --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)
//-------------------------------------------------
#ifndef _SOURCE_ASUS_START_AUTO_TIME
#define _SOURCE_ASUS_START_AUTO_TIME                            SEC(2)
#endif


//////////
// DELL //
//////////

//--------------------------------------------------
// DELL DP D3 Options --> for DELL
//--------------------------------------------------
#ifndef _DP_DELL_D3_TEST_SUPPORT
#define _DP_DELL_D3_TEST_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// DELL DP Dynamic Adjust Link Rate --> for DELL
//--------------------------------------------------
#ifndef _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT
#define _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT                    _OFF // when _ON:_DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT shall be checked
#endif

//--------------------------------------------------
// DELL EDID INPUT BITS PER COMPONENT --> for DELL
//--------------------------------------------------
#ifndef _DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT
#define _DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT                 _COLOR_DEPTH_8_BITS // Shall be Checked When _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON
#endif

//--------------------------------------------------
// DELL AUX not reply when DP HPD low
//--------------------------------------------------
#ifndef _DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT
#define _DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// DELL delay mode input port count
//--------------------------------------------------
#ifndef _DELL_DELAY_MODE_INPUT_PORT
#define _DELL_DELAY_MODE_INPUT_PORT                             ((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) ? 1 : _INPUT_PORT_VALID)
#endif

//--------------------------------------------------
// DELL Gating Dp Tx DDCCI MSG
//--------------------------------------------------
#ifndef _DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT
#define _DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT                  _OFF
#endif

#ifndef _DP_MST_RX_INTERCEPT_PORT9_DDCCI_MSG_SUPPORT
#define _DP_MST_RX_INTERCEPT_PORT9_DDCCI_MSG_SUPPORT            _OFF
#endif


/////////////
// PHILIPS //
/////////////

//--------------------------------------------------
// PHILIPS Pixel-shift Support Option
//--------------------------------------------------
#ifndef _PIXEL_SHIFT_SUPPORT
#define _PIXEL_SHIFT_SUPPORT                                    _OFF
#endif

//--------------------------------------------------
// FW Pixel Shift Mode
//--------------------------------------------------
#ifndef _FW_PIXEL_SHIFT_MODE
#define _FW_PIXEL_SHIFT_MODE                                    ((_DRR_SUPPORT == _ON) ? _PIXEL_SHIFT_IN_DDOMAIN : _PIXEL_SHIFT_IN_IDOMAIN)
#endif

////////
// HP //
////////

//--------------------------------------------------
// HP Source Scan Define Option
//--------------------------------------------------
#ifndef _HP_SOURCE_SCAN_SUPPORT
#define _HP_SOURCE_SCAN_SUPPORT                                 _OFF
#endif

//--------------------------------------------------
// DP MST DC Off HPD High Tx Active (for HP Use)
//--------------------------------------------------
#ifndef _DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT
#define _DP_MST_DC_OFF_HPD_HIGH_TX_ACTIVE_SUPPORT               _OFF
#endif


//////////
// Eizo //
//////////

//--------------------------------------------------
// DP Sink Support OUI Under Ver1.1 Option
//--------------------------------------------------
#ifndef _DP_SINK_VER11_OUI_SUPPORT
#define _DP_SINK_VER11_OUI_SUPPORT                              _ON
#endif

//--------------------------------------------------
// DP Tx Aux Communication Option
//--------------------------------------------------
#ifndef _DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT
#define _DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT               _OFF
#endif

//--------------------------------------------------
// DP DPCD Down Stream Port Count
//--------------------------------------------------
#ifndef _DP_1_1_DOWN_STREAM_PORT_COUNT
#define _DP_1_1_DOWN_STREAM_PORT_COUNT                          0x01
#endif

#ifndef _DP_1_2_DOWN_STREAM_PORT_COUNT
#define _DP_1_2_DOWN_STREAM_PORT_COUNT                          0x01
#endif

//-------------------------------------------------
// Eizo LVDS Setting Control
//-------------------------------------------------
#ifndef _LVDS_SETTING_CONTROL_BY_USER
#define _LVDS_SETTING_CONTROL_BY_USER                           _DISABLE
#endif

//--------------------------------------------------
// DP Customized Value of DPCD Option (For EIZO USE)
//--------------------------------------------------
#ifndef _EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT
#define _EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// DP HPD Implementation Mode
//--------------------------------------------------
#ifndef _DP_LONG_HPD_USER_MODE
#define _DP_LONG_HPD_USER_MODE                                  _DP_LONG_HPD_DEFAULT_MODE
#endif


////////
// LG //
////////

//--------------------------------------------------
//  LG DP Power Management
//--------------------------------------------------
#ifndef _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER
#define _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER           _OFF
#endif

//-----------------------------------------------------
// Hw DDCCI Buffer None Reply Null Msg Support
// For HP case, return Null Msg if Command isn't finish
//-----------------------------------------------------
#ifndef _HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT
#define _HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT           _OFF
#endif

///////////////
// Dual Bank //
///////////////

//--------------------------------------------------
// Dual Bank Type Selection
//--------------------------------------------------
#ifndef _DUAL_BANK_SUPPORT
#define _DUAL_BANK_SUPPORT                                      _OFF
#endif

#ifndef _DUAL_BANK_TYPE
#define _DUAL_BANK_TYPE                                         _DUAL_BANK_DIFF_BANK
#endif

#ifndef _DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL
#define _DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL                _DUAL_BANK_FLASH_PARTITION_USER
#endif

//--------------------------------------------------
// User FW Information
//--------------------------------------------------
#ifndef _DUAL_BANK_USER_FW_CODE_SIZE
#define _DUAL_BANK_USER_FW_CODE_SIZE                            9
#endif

#ifndef _DUAL_BANK_USER_FW_START_BANK
#define _DUAL_BANK_USER_FW_START_BANK                           1
#endif

//--------------------------------------------------
// User Flag Location
//--------------------------------------------------
#ifndef _DUAL_BANK_USER_FLAG_LOCATION_AREA
#define _DUAL_BANK_USER_FLAG_LOCATION_AREA                      _DUAL_BANK_FLAG_LOCATION_IN_USER
#endif

#ifndef _DUAL_BANK_USER_FLAG_LAYOUT
#define _DUAL_BANK_USER_FLAG_LAYOUT                             _DUAL_BANK_DIFFER_SECTOR
#endif

#ifndef _DUAL_BANK_USER_I_FLAG_LOCATE_BANK
#define _DUAL_BANK_USER_I_FLAG_LOCATE_BANK                      8
#endif

#ifndef _DUAL_BANK_USER_II_FLAG_LOCATE_BANK
#define _DUAL_BANK_USER_II_FLAG_LOCATE_BANK                     8
#endif

#ifndef _DUAL_BANK_FLASH_PARTITION_USER_FLAG_ADDRESS
#define _DUAL_BANK_FLASH_PARTITION_USER_FLAG_ADDRESS            0xF8FC
#endif

#ifndef _DUAL_BANK_FLASH_PARTITION_USER_FLAG_DATA
#define _DUAL_BANK_FLASH_PARTITION_USER_FLAG_DATA               0xFF, 0xFF, 0xAA, 0x55
#endif

#ifndef _DUAL_BANK_FLASH_PARTITION_DEFAULT_CODE_TABLE
#define _DUAL_BANK_FLASH_PARTITION_DEFAULT_CODE_TABLE           0xFF, 0xFF, 0xFF, 0xFF
#endif

//--------------------------------------------------
// User Flag Type Option
//--------------------------------------------------
#ifndef _DUAL_BANK_USER_FLAG_CUSTOMER_TYPE
#define _DUAL_BANK_USER_FLAG_CUSTOMER_TYPE                      _DUAL_BANK_KERNEL_TYPE
#endif

///////////////////////////////
// Digital Signature Support //
///////////////////////////////
#ifndef _DIGITAL_SIGNATURE_SUPPORT
#define _DIGITAL_SIGNATURE_SUPPORT                              _OFF
#endif

#ifndef _DIGITAL_SIGNATURE_TYPE
#define _DIGITAL_SIGNATURE_TYPE                                 _DIGITAL_SIGNATURE_NONE
#endif

#ifndef _DIGITAL_SIGNATURE_HW_RSA_TYPE
#define _DIGITAL_SIGNATURE_HW_RSA_TYPE                          _DIGITAL_SIGNATURE_RSA_2048
#endif

//////////////////////////
// ISP Channel Protect //
/////////////////////////

#ifndef _ISP_CHANNEL_PROTECT_SUPPORT
#define _ISP_CHANNEL_PROTECT_SUPPORT                            _OFF
#endif

#ifndef _ISP_CHANNEL_EN_FW_RUN
#define _ISP_CHANNEL_EN_FW_RUN                                  ((WORD)(1 << _VGA_DDC))
#endif

#ifndef _ISP_CHANNEL_EN_FW_UPDATE
#define _ISP_CHANNEL_EN_FW_UPDATE                               ((WORD)((1 << _VGA_DDC) |\
                                                                        (1 << _DDC0) |\
                                                                        (1 << _DDC1) |\
                                                                        (1 << _DDC2) |\
                                                                        (1 << _DDC3) |\
                                                                        (1 << _DDC4) |\
                                                                        (1 << _DDC5) |\
                                                                        (1 << _VGA_DDC2)))
#endif

//--------------------------------------------------
// FW Version Support
//--------------------------------------------------
#ifndef _CUSTOMER_FW_VERSION_SUPPORT
#define _CUSTOMER_FW_VERSION_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// FW Version (8-Bit Width)
//--------------------------------------------------
#ifndef _CUSTOMER_FW_VERSION
#define _CUSTOMER_FW_VERSION                                    0x01
#endif

//--------------------------------------------------
// FW Sub Version (8-Bit Width)
//--------------------------------------------------
#ifndef _CUSTOMER_FW_SUB_VERSION
#define _CUSTOMER_FW_SUB_VERSION                                0x00
#endif

//----------------------------------------------------
// FW Version Locate BankIndex:offset with start bank
//----------------------------------------------------
#ifndef _CUSTOMER_FW_VERSION_LOCATE_BANK
#define _CUSTOMER_FW_VERSION_LOCATE_BANK                        0x00
#endif

//--------------------------------------------------
// FW Version Locate address
// Default 0x7005 Alain with tranasltor
//--------------------------------------------------
#ifndef _CUSTOMER_FW_VERSION_LOCATE_ADDRESS
#define _CUSTOMER_FW_VERSION_LOCATE_ADDRESS                     0x8000
#endif

//--------------------------------------------------
// Customer Debug Support
//--------------------------------------------------
#ifndef _CUSTOMER_DEBUG_COMMAND_SUPPORT
#define _CUSTOMER_DEBUG_COMMAND_SUPPORT                         _OFF
#endif

//--------------------------------------------------
// Dual Bank Bundle Version
// May Be USB Hub Version + Scaler Version
//--------------------------------------------------
#ifndef _DUAL_BANK_BUNDLE_VERSION_SUPPORT
#define _DUAL_BANK_BUNDLE_VERSION_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// Dual Bank Bundle Version Lacate bank
// Should not in FW Code Area
//--------------------------------------------------
#ifndef _DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK
#define _DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK                   8
#endif

#ifndef _DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR
#define _DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR                 8
#endif

//--------------------------------------------------
// Dual Bank Bundle Version Byte Count less then 12
//--------------------------------------------------
#ifndef _DUAL_BANK_BUNDLE_VERSION_COUNT
#define _DUAL_BANK_BUNDLE_VERSION_COUNT                         4
#endif

//-----------------------------------------------------
// FW Check Option
//-----------------------------------------------------
#ifndef _ISP_FW_CHECK_PROJECT_ID_SUPPORT
#define _ISP_FW_CHECK_PROJECT_ID_SUPPORT                        _OFF
#endif

#ifndef _ISP_FW_CHECK_PROJECT_ID_LOCATION_BANK
#define _ISP_FW_CHECK_PROJECT_ID_LOCATION_BANK                  1
#endif

#ifndef _ISP_FW_CHECK_PROJECT_ID_LOCATION_ADDRESS
#define _ISP_FW_CHECK_PROJECT_ID_LOCATION_ADDRESS               0x7100
#endif

#ifndef _ISP_FW_CHECK_PROJECT_ID_DATA
#define _ISP_FW_CHECK_PROJECT_ID_DATA                           _PROJECT, _SCALER_TYPE, _OSD_TYPE, _PCB_TYPE, _PANEL_TYPE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF // Example: First 5 bytes are RTDxxxxx and then followed by 7 Bytes dependent on project name.
#endif

#ifndef CHECK_FW_PROJECT_ID
#define CHECK_FW_PROJECT_ID(pucInput, pucTarget, ucLen)         (memcmp(pucInput, pucTarget, ucLen) == 0)
#endif

//-------------------------------------------------
// Background  Fw Update  Option
//-------------------------------------------------
#ifndef _FW_UPDATE_BACKGROUND_SUPPORT
#define _FW_UPDATE_BACKGROUND_SUPPORT                           _OFF
#endif

//-------------------------------------------------
// Fw Update FW Option
//-------------------------------------------------
#ifndef _FW_UPDATE_FOREGROUND_SUPPORT
#define _FW_UPDATE_FOREGROUND_SUPPORT                           _OFF
#endif

//-------------------------------------------------
// Fw Update FW Option
//-------------------------------------------------
#ifndef _FW_UPDATE_CHECK_TYPE
#define _FW_UPDATE_CHECK_TYPE                                   _FW_UPDATE_CHECK_NONE
#endif

//-------------------------------------------------
// Fw Update Forground FW Option
//-------------------------------------------------
#ifndef _FW_UPDATE_FOREGROUND_EXIT_TYPE
#define _FW_UPDATE_FOREGROUND_EXIT_TYPE                         _FW_UPDATE_FOREGROUND_RESET
#endif

//-------------------------------------------------
// Fw Update Forground Disable Int0 while fw update
//-------------------------------------------------
#ifndef _FW_UPDATE_FOREGROUND_DISABLE_INT0
#define _FW_UPDATE_FOREGROUND_DISABLE_INT0                      _ON
#endif

//-------------------------------------------------
// FW Update Password
//-------------------------------------------------
#ifndef _FW_UPDATE_PASSWORD_DATA
#define _FW_UPDATE_PASSWORD_DATA                                0xFF, 0xFF
#endif

#ifndef _FW_UPDATE_PASSWORD_BANK
#define _FW_UPDATE_PASSWORD_BANK                                0
#endif

#ifndef _FW_UPDATE_PASSWORD_ADDRESS
#define _FW_UPDATE_PASSWORD_ADDRESS                             0x8000
#endif

//-------------------------------------------------
// Fw Update Forground FW Option
//-------------------------------------------------
#ifndef _FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS
#define _FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS                     0x9000
#endif

//-------------------------------------------------
// Fw Update Forground DDCCI Channel Sel
//-------------------------------------------------
#ifndef _FW_UPDATE_DDCCI_SEL
#define _FW_UPDATE_DDCCI_SEL                                    _FW_UPDATE_SEL_DDCCI0
#endif

//-------------------------------------------------
// Fw Update Clac CRC Type
//-------------------------------------------------
#ifndef _FW_UPDATE_CLAC_CRC_TYPE
#define _FW_UPDATE_CLAC_CRC_TYPE                                _FW_UPDATE_FW_CLAC_CRC
#endif

//-------------------------------------------------
// Fw Update Speed up
//-------------------------------------------------
#ifndef _FW_UPDATE_FW_SPEED_UP_SUPPORT
#define _FW_UPDATE_FW_SPEED_UP_SUPPORT                          _ON
#endif

#define _LOCAL_DIMMING_DEEP_BLACK_MIN_PWM                       200

//-------------------------------------------------
// Eizo LVDS Pull Down Control (Active when _LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//-------------------------------------------------
#ifndef _LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTA_WEAKLY_PULL_DOWN_USER_CONTROL               _DISABLE
#endif

#ifndef _LVDS_PORTA_STRONGLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTA_STRONGLY_PULL_DOWN_USER_CONTROL             _DISABLE
#endif

#ifndef _LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTB_WEAKLY_PULL_DOWN_USER_CONTROL               _DISABLE
#endif

#ifndef _LVDS_PORTB_STRONGLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTB_STRONGLY_PULL_DOWN_USER_CONTROL             _DISABLE
#endif

#ifndef _LVDS_PORTC_WEAKLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTC_WEAKLY_PULL_DOWN_USER_CONTROL               _DISABLE
#endif

#ifndef _LVDS_PORTC_STRONGLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTC_STRONGLY_PULL_DOWN_USER_CONTROL             _DISABLE
#endif

#ifndef _LVDS_PORTD_WEAKLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTD_WEAKLY_PULL_DOWN_USER_CONTROL               _DISABLE
#endif

#ifndef _LVDS_PORTD_STRONGLY_PULL_DOWN_USER_CONTROL
#define _LVDS_PORTD_STRONGLY_PULL_DOWN_USER_CONTROL             _DISABLE
#endif

//-------------------------------------------------
// Eizo LVDS Driving Current Control (Active when _LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//-------------------------------------------------
#ifndef _LVDS_DRIV_CURRENT_USER_ADUST
#define _LVDS_DRIV_CURRENT_USER_ADUST                           0xA0
#endif

//-------------------------------------------------
// Eizo LVDS Driving Double Current Control (Active when _LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//-------------------------------------------------
#ifndef _LVDS_PORTA_DATA0_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA0_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTA_DATA1_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA1_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTA_DATA2_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA2_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTA_CLK_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_CLK_DRIV_2X_USER_CTRL                       _DISABLE
#endif

#ifndef _LVDS_PORTA_DATA3_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA3_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTA_DATA4_DRIV_2X_USER_CTRL
#define _LVDS_PORTA_DATA4_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA0_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA0_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA1_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA1_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA2_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA2_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA3_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA3_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTB_DATA4_DRIV_2X_USER_CTRL
#define _LVDS_PORTB_DATA4_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTC_DATA0_DRIV_2X_USER_CTRL
#define _LVDS_PORTC_DATA0_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTC_DATA1_DRIV_2X_USER_CTRL
#define _LVDS_PORTC_DATA1_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTC_DATA2_DRIV_2X_USER_CTRL
#define _LVDS_PORTC_DATA2_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTC_CLK_DRIV_2X_USER_CTRL
#define _LVDS_PORTC_CLK_DRIV_2X_USER_CTRL                       _DISABLE
#endif

#ifndef _LVDS_PORTC_DATA3_DRIV_2X_USER_CTRL
#define _LVDS_PORTC_DATA3_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTC_DATA4_DRIV_2X_USER_CTRL
#define _LVDS_PORTC_DATA4_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTD_DATA0_DRIV_2X_USER_CTRL
#define _LVDS_PORTD_DATA0_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTD_DATA1_DRIV_2X_USER_CTRL
#define _LVDS_PORTD_DATA1_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTD_DATA2_DRIV_2X_USER_CTRL
#define _LVDS_PORTD_DATA2_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTD_DATA3_DRIV_2X_USER_CTRL
#define _LVDS_PORTD_DATA3_DRIV_2X_USER_CTRL                     _DISABLE
#endif

#ifndef _LVDS_PORTD_DATA4_DRIV_2X_USER_CTRL
#define _LVDS_PORTD_DATA4_DRIV_2X_USER_CTRL                     _DISABLE
#endif

//-------------------------------------------------
// Eizo LVDS Output Termination Control (Active when _LVDS_SETTING_CONTROL_BY_USER == _ENABLE)
//-------------------------------------------------
#ifndef _LVDS_PORTA_DATA0_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA0_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTA_DATA1_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA1_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTA_DATA2_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA2_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTA_DATA3_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA3_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTA_DATA4_TERMINATION_USER_ADJUST
#define _LVDS_PORTA_DATA4_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_DATA0_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA0_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_DATA1_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA1_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_DATA2_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA2_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_CLK_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_CLK_TERMINATION_USER_ADJUST                 0x03
#endif

#ifndef _LVDS_PORTB_DATA3_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA3_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTB_DATA4_TERMINATION_USER_ADJUST
#define _LVDS_PORTB_DATA4_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTC_DATA0_TERMINATION_USER_ADJUST
#define _LVDS_PORTC_DATA0_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTC_DATA1_TERMINATION_USER_ADJUST
#define _LVDS_PORTC_DATA1_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTC_DATA2_TERMINATION_USER_ADJUST
#define _LVDS_PORTC_DATA2_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTC_DATA3_TERMINATION_USER_ADJUST
#define _LVDS_PORTC_DATA3_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTC_DATA4_TERMINATION_USER_ADJUST
#define _LVDS_PORTC_DATA4_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTD_DATA0_TERMINATION_USER_ADJUST
#define _LVDS_PORTD_DATA0_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTD_DATA1_TERMINATION_USER_ADJUST
#define _LVDS_PORTD_DATA1_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTD_DATA2_TERMINATION_USER_ADJUST
#define _LVDS_PORTD_DATA2_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTD_CLK_TERMINATION_USER_ADJUST
#define _LVDS_PORTD_CLK_TERMINATION_USER_ADJUST                 0x03
#endif

#ifndef _LVDS_PORTD_DATA3_TERMINATION_USER_ADJUST
#define _LVDS_PORTD_DATA3_TERMINATION_USER_ADJUST               0x03
#endif

#ifndef _LVDS_PORTD_DATA4_TERMINATION_USER_ADJUST
#define _LVDS_PORTD_DATA4_TERMINATION_USER_ADJUST               0x03
#endif

//--------------------------------------------------
// USER DP Long HPD Time Value
//--------------------------------------------------
#ifndef _USER_DP_LONG_HPD_TIME_VALUE
#define _USER_DP_LONG_HPD_TIME_VALUE                            800
#endif

#ifndef _USER_DP_HDCP_LONG_HPD_TIME_VALUE
#define _USER_DP_HDCP_LONG_HPD_TIME_VALUE                       800
#endif

//-------------------------------------------------
// OSD disable option
//-------------------------------------------------
#ifndef _OSD_WD_RESET_OVERLAY_DISABLE
#define _OSD_WD_RESET_OVERLAY_DISABLE                           _OFF
#endif

//-------------------------------------------------
// DP Digital Color Info Change Check
//-------------------------------------------------
#ifndef _DP_COLORIMTRY_SEAMLESS_COLOR_INFO_CHECK_BYPASS
#define _DP_COLORIMTRY_SEAMLESS_COLOR_INFO_CHECK_BYPASS         _OFF
#endif
