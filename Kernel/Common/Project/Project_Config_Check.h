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
// ID Code      : Project_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_CONFIG_CHECK_H__
#define __PROJECT_CONFIG_CHECK_H__

//--------------------------------------------------
// Interface DSC Config Check
//--------------------------------------------------
#if(_DSC_DECODER_SUPPORT == _ON)
#if(GET_DSC_MAC_SUPPORT(_HW_D_MAC_RX_DSC_MAPPING) == _OFF)
#warning "Interface DSC Can Not Be Supported With This Project !!!"
#endif
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
#if(_HDMI_FRL_SUPPORT == _OFF)
#warning "_HDMI21_RX_DSC_DECODER_SUPPORT Should Be Off When _HDMI_FRL_SUPPORT Off !!!"
#endif
#endif

#if(_DP_TX_SST_CLONE_PATH_TYPE == _DP_TX_CLONE_BOTH_VESA_STREAM_DSC_PASSTHROUGH)
#if(!((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)))
#warning "_DP_RX_DSC_DECODER_SUPPORT And _DP_TX_DSC_PASSTHROUGH_SUPPORT Should Be ON When Select _DP_TX_CLONE_BOTH_VESA_STREAM_DSC_PASSTHROUGH !!!"
#endif
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
#if(_DSC_MAC_MAX_COUNT < 2)
#warning "_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT Should be Off When DSC Decoder Mac Count < 2 !!!"
#endif
#if(!((_DP_MST2SST_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON)))
#warning "_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT Should be Off When _DP_MST2SST_SUPPORT or _DP_RX_DSC_DECODER_SUPPORT Not Support !!!"
#endif
#endif

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
#if(!((_DSC_MAC_MAX_COUNT >= 2) && (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _OFF)))
#warning "_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT Should be Off When DSC Decoder Mac Count < 2 or _DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT ON!!!"
#endif
#if(!((_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON)))
#warning "_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT Should be Off When _SOURCE_BACKGROUND_DETECT_SUPPORT Not Support or _DP_RX_DSC_DECODER_SUPPORT Not Support!!!"
#endif
#endif

#if((_PIXEL_SHIFT_SUPPORT == _ON) &&\
    (_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN))
#if(_HDMI_FRL_SUPPORT == _ON)
#warning "_PIXEL_SHIFT_SUPPORT Should Be Off When _HDMI_FRL_SUPPORT On !!!"
#endif
#endif
//--------------------------------------------------
// Memory Config Check
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6829_SERIES) ||\
    (_SCALER_TYPE == _RL6952_SERIES))
#if((_FW_DDR_PLL_CLOCK != _MEMORY_SPEED_1066MHZ) &&\
    (_FW_DDR_PLL_CLOCK != _MEMORY_SPEED_933MHZ) &&\
    (_FW_DDR_PLL_CLOCK != _MEMORY_SPEED_800MHZ))
#warning "_FW_DDR_PLL_CLOCK Can Not Be The Unspecified Frequnecy!!!"
#endif
#endif

#if(_SCALER_TYPE == _RL6829_SERIES)
#if(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_1066MHZ)
#warning "_MEMORY_SPEED_1066MHZ Can Not be Used Temporally, Plz Contact SDs !!!"
#endif
#if((_DDR3PLL_SSC_SUPPORT == _ON) && (_DDR3PLL_SSC_AMPLITUDE >= _2_PERCENT))
#warning "RL6829 DDR3PLL Can Not support >= 2%, Plz Contact SDs !!!"
#endif
#endif

#if(_SCALER_TYPE == _RL6952_SERIES)
#if((_DDR3PLL_SSC_SUPPORT == _ON) && (_DDR3PLL_SSC_AMPLITUDE == _0_5_PERCENT))
#warning "RL6952 DDR3PLL Can Not support 0.5%, Plz Contact SDs !!!"
#endif
#if((_DDR3PLL_SSC_SUPPORT == _ON) && (_DDR3PLL_SSC_AMPLITUDE > _2_PERCENT))
#warning "RL6952 DDR3PLL Can Not support > 2%, Plz Contact SDs !!!"
#endif
#endif

#if(_SCALER_TYPE == _RL6978_SERIES)
#if((_FW_DDR_PLL_CLOCK != _MEMORY_SPEED_667MHZ) &&\
    (_FW_DDR_PLL_CLOCK != _MEMORY_SPEED_600MHZ) &&\
    (_FW_DDR_PLL_CLOCK != _MEMORY_SPEED_533MHZ))
#warning "_FW_DDR_PLL_CLOCK Can Not Be The Unspecified Frequnecy!!!"
#endif
#if(_DDR3_KGD_DCC_SUPPORT == _ON)
#warning "_DDR3_KGD_DCC_SUPPORT Can Not Be Supported With DDR2!!!"
#endif
#endif

#if(_OD_FUNCTION == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_COLOR_OD_FUNCTION Can Not Be Supported With No Memory!!!"
#endif

#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if((_PANEL_PIXEL_TYPE == _PANEL_PIXEL_OLED) || (_PANEL_PIXEL_TYPE == _PANEL_PIXEL_MICRO_LED))
#warning "_OD_FUNCTION Should Be Off On OLED or Micro LED Panel!!!"
#endif
#endif
#endif

#if(_FRC_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_FRC_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_ROTATION_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_HOR_MIRROR_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_VER_MIRROR_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISP_LATENCY_ADJUST_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_PIP_FRAME_SYNC_SUPPORT == _ON)
#if(_2P_PIP_DISPLAY_SUPPORT == _OFF)
#warning "_PIP_FRAME_SYNC_SUPPORT Can Not Be Supported When _2P_PIP_DISPLAY_SUPPORT _OFF!!!"
#endif
#endif

#if(_PBP_LR_FRAME_SYNC_SUPPORT == _ON)
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _OFF)
#warning "_PBP_LR_FRAME_SYNC_SUPPORT Can Not Be Supported When _2P_PBP_LR_DISPLAY_SUPPORT _OFF!!!"
#endif
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_EAGLE_SIGHT_SUPPORT Can Not Be Supported When _FRC_SUPPORT _OFF!!!"
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _OFF)
#warning "_EAGLE_SIGHT_SUPPORT Can Not Be Supported When _2P_PIP_DISPLAY_SUPPORT _OFF!!!"
#endif

#if(_BORDER_WINDOW_FUNCTION == _OFF)
#warning "_EAGLE_SIGHT_SUPPORT Can Not Be Supported When _BORDER_WINDOW_FUNCTION is _OFF!!!"
#endif
#else
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
#warning "_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT Can Not Be Supported When _EAGLE_SIGHT_SUPPORT is _OFF!!!"
#endif
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_2P_FRAME_SYNC_SUPPORT Can Not Be Supported When _FRC_SUPPORT _OFF!!!"
#endif

#if(_FIRST_CHECK_CONTROL_BACKLIGHT_BY_USER == _OFF)
#warning "_2P_FRAME_SYNC_SUPPORT Can Not Be Supported When _FIRST_CHECK_CONTROL_BACKLIGHT_BY_USER _OFF!!!"
#endif
#endif

#if(_DRR_FREE_RUN_DISPLAY_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_DRR_FREE_RUN_DISPLAY_SUPPORT Can Not Be Supported When _FRC_SUPPORT _OFF!!!"
#endif
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _OFF)
#warning "_2P_PBP_LR_DISPLAY_SUPPORT Can Not Be Supported When _HW_D_DOMAIN_R2_BACKGROUND_SUPPORT _OFF!!!"
#endif
#endif

//--------------------------------------------------
// Display Setting Check
//--------------------------------------------------
#if(_MULTI_DISPLAY_MAX > 0x01)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FORCE_TO_FREE_RUN_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FREEZE_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _OFF) && (_FRC_SUPPORT == _OFF))
#if(_PANEL_STYLE != _PANEL_NONE)
#warning "_FRAME_SYNC_LINE_BUFFER_SUPPORT or _FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#if(_ASPECT_RATIO_SUPPORT == _OFF)
#warning "_ASPECT_RATIO_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_DISPLAY_HOR_MIRROR_SUPPORT == _ON) || (_DISPLAY_VER_MIRROR_SUPPORT == _ON))
#if(_DISPLAY_ROTATION_SUPPORT == _OFF)
#warning "_DISPLAY_ROTATION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_FORCE_TO_FREE_RUN_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
#warning "_FRAME_SYNC_LINE_BUFFER_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if((_FREEZE_SUPPORT == _ON) && (_DISPLAY_ROTATION_SUPPORT == _ON))
#if(_ROTATION_FREEZE_FORCE_TO_BACKGROUND == _OFF)
#warning "_ROTATION_FREEZE_FORCE_TO_BACKGROUND Should Be _ON!!!"
#endif
#endif

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
#warning "_ASPECT_RATIO_WITHOUT_MUTE Do Not Support VBO/eDP Panel!!!"
#endif
#endif

#if((_FREEZE_SUPPORT == _ON) && (_DM_FUNCTION == _ON))
#warning "_FREEZE_SUPPORT Can Not Be Supported When _DM_FUNCTION _ON!!!"
#endif

#if((_HDMI_SBTM_SUPPORT == _ON) && (_DM_FUNCTION == _ON))
#warning "_HDMI_SBTM_SUPPORT Can Not Be Supported When _DM_FUNCTION _ON!!!"
#endif

#if((_HDMI_SBTM_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _OFF))
#warning "_HDMI_HDR10_SUPPORT should be _ON When _HDMI_SBTM_SUPPORT _ON!!!"
#endif

//--------------------------------------------------
// M-Domain Image Compression Check
//--------------------------------------------------
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_M_DOMAIN_IMG_CMP_SUPPORT Should Be _OFF!!!"
#endif
#endif

//--------------------------------------------------
// M-Domain Line Buffer Force Memory 8bit Check
//--------------------------------------------------
#if(_M_DOMAIN_LSR_LINE_BUFFER_DT_FORCE_10_TO_8_BIT == _ON)
#if(_COLOR_IP_LSR == _OFF)
#warning "_M_DOMAIN_LSR_LINE_BUFFER_DT_FORCE_10_TO_8_BIT Should Be _OFF!!!"
#endif
#endif

//--------------------------------------------------
// Framesync Fixed Lastline Check
//--------------------------------------------------
#if(_FRAMESYNC_MODE_FIX_LASTLINE == _ON)
#if(_DRR_SUPPORT == _OFF)
#warning "Only _DRR_SUPPORT = ON need Framesyne Fixed Lastline.If _DRR_SUPPORT = OFF, please set _FRAMESYNC_MODE_FIX_LASTLINE == _OFF!!!"
#endif
#endif

//--------------------------------------------------
// Motion Blur Reduction Check
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(((_PANEL_PIXEL_TYPE == _PANEL_PIXEL_LCD) && (_MOTION_BLUR_PANEL_PIXEL_TYPE != _MOTION_BLUR_PANEL_PIXEL_LCD)) ||\
    ((_PANEL_PIXEL_TYPE == _PANEL_PIXEL_OLED) && (_MOTION_BLUR_PANEL_PIXEL_TYPE != _MOTION_BLUR_PANEL_PIXEL_OLED)))
#warning "_MOTION_BLUR_PANEL_PIXEL_TYPE and _PANEL_PIXEL_TYPE Mismatch!!!"
#endif
#endif
#endif

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT != _ON)
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
#warning "_DRR_MOTION_BLUR_REDUCTION_SUPPORT / _RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT Is Only Supported By LCD Panel!!!"
#endif
#endif

#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#warning "_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_DRR_SUPPORT == _OFF)
#warning "_DRR_SUPPORT Should Be _ON!!!"
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _OFF)
#warning "_MOTION_BLUR_REDUCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _OFF)
#warning "_MOTION_BLUR_REDUCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_FORCE_TO_FREE_RUN_SUPPORT == _ON)
#warning "_FORCE_TO_FREE_RUN_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
#if(_OD_FUNCTION == _ON)
#warning "_OD_FUNCTION Should Be _OFF!!!"
#endif
#if(_MN_FRAMESYNC_FORCE_TO_FREERUN == _ON)
#warning "_MN_FRAMESYNC_FORCE_TO_FREERUN Should Be _OFF!!!"
#endif
#endif

//--------------------------------------------------
// SCM Config Check
//--------------------------------------------------
#if(_SCM_SUPPORT == _ON)
#if(_ICM_FUNCTION == _OFF)
#warning "_COLOR_ICM_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
#if(_ICM_FUNCTION == _OFF)
#warning "_COLOR_ICM_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_SIX_COLOR_ICM_GRAY_LEVEL_CONTROL == _ON)
#if(_SIX_COLOR_SUPPORT == _OFF)
#warning "_SIX_COLOR_SUPPORT Should Be _ON!!!"
#endif

#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_NORMAL_MODE)
#warning "_SIX_COLOR_ICM_TYPE Should Be _SIX_COLOR_ICM_BRI_COMPENSATE_MODE!!!"
#endif
#endif

//--------------------------------------------------
// DCR Setting Check
//--------------------------------------------------
#if((_HW_DCR_TYPE != _DCR_GEN_1) && (_HW_DCR_TYPE != _DCR_GEN_3) && (_HW_DCR_TYPE != _DCR_GEN_4) && (_HW_DCR_TYPE != _DCR_GEN_5))
#if(_LOCAL_DIMMING_FUNCTION == _ON)
#warning "_LOCAL_DIMMING_FUNCTION Should be _OFF!!!"
#endif
#endif

//-------------------------------------------------
// Backlight dimming
//-------------------------------------------------
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)

#if(_OCC_FUNCTION == _OFF)
#warning "_COLOR_OCC_FUNCTION Should Be _ON!!!"
#endif

#if((_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE) && (_DEVICE_LED_DRIVER_COMMUNICATE_TYPE == _INTERFACE_SPI) && (_SPI_SUPPORT == _OFF))
#warning "_SPI_SUPPORT Should Be _ON!!!"
#endif

#if((_SPI_SUPPORT != _ON) && (_LOCAL_DIMMING_FUNCTION == _ON))
#warning "_SPI_SUPPORT should be _ON!!!(for PwmToSpi SPI Control)"
#endif

#if(_PCM_FUNCTION == _OFF)
#warning "_COLOR_PCM_FUNCTION Should be _ON!!!"
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT)
#if((_LOCAL_DIMMING_BLACK_COLOR_CODE > 3) || (_LOCAL_DIMMING_BLACK_COLOR_CODE == 0))
#warning "_LOCAL_DIMMING_BLACK_COLOR_CODE should be less than 3 or greater than 0!!!"
#endif
#else
#if(_LOCAL_DIMMING_BLACK_COLOR_CODE < 10)
#warning "_LOCAL_DIMMING_BLACK_COLOR_CODE should be 10!!!"
#endif
#endif
#endif

#if(_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_DIRECT_BACKLIGHT)
#if((_HW_CPU32_SCPU_SUPPORT == _ON) && (_SCPU_SUPPORT == _OFF))
#warning "_SCPU_SUPPORT Should be _ON!!!"
#endif


#if((_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION) && (_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON))
#warning "_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT Should be _OFF!!!"
#endif
#if((_LOCAL_DIMMING_USING_YAVG_INFO == _OFF) && (_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION) && (_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON))
#warning "_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON, _LOCAL_DIMMING_USING_YAVG_INFO shlould be ON !!!"
#endif
#endif

#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
#if((_LOCAL_DIMMING_FUNCTION == _OFF) || (_HDR10_SUPPORT == _OFF))
#warning " _LOCAL_DIMMING_HDR10_BOOST_SUPPORT Should be _OFF!!!"
#endif
#endif

#if((_HW_CPU32_SCPU_SUPPORT == _OFF) || (_SCPU_SUPPORT == _OFF))
#if(_LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU == _ON)
#warning " _LOCAL_DIMMING_BOOST_CMD_SEND_BY_SCPU Should be _OFF!!!"
#endif
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE != _LOCAL_DIMMING_EDGE_BACKLIGHT)
#warning "_LOCAL_DIMMING_REGION_BOOST_SUPPORT Only Supports _LOCAL_DIMMING_EDGE_BACKLIGHT!!!"
#endif
#endif

#if((_LOCAL_DIMMING_FUNCTION == _OFF) || (_SPI_BACKLIGHT_DIMMING_SUPPORT == _OFF))
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
#warning "_LOCAL_DIMMING_REGION_BOOST_SUPPORT Should Be _OFF!!!";
#endif
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _OFF)
#warning " _SPI_BACKLIGHT_DIMMING_SUPPORT Should be _ON!!!"
#endif
#if(_HW_DCR_BIT != _DCR_10BIT)
#warning "_LOCAL_DIMMING_FUNCTION Only Supports _DCR_10BIT!!!"
#endif
#endif


#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
#if((_LOCAL_DIMMING_FUNCTION == _OFF) || (_DRR_SUPPORT == _OFF))
#warning " _LOCAL_DIMMING_DRR_MODE_SUPPORT Should be _OFF!!!"
#endif
#endif

#if(_LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT == _ON)
#if((_LOCAL_DIMMING_FUNCTION == _OFF) || (_FREESYNC_II_SUPPORT == _OFF))
#warning " _LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT Should be _OFF!!!"
#endif

#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _OFF)
#warning " _LOCAL_DIMMING_HDR10_BOOST_SUPPORT Should be _ON!!!"
#endif

#endif

#if(_LOCAL_DIMMING_USER_GLOBAL_BOOST_SUPPORT == _ON)
#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _OFF)
#warning " _LOCAL_DIMMING_HDR10_BOOST_SUPPORT Should be _ON!!!"
#endif
#endif

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
#if(_LOCAL_DIMMING_FUNCTION == _OFF)
#warning " _LOCAL_DIMMING_SCENE_CHANGE_SUPPORT Should be _OFF!!!"
#endif
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_LOCAL_DIMMING_BLMODEL_MAX_GAIN > 32)
#warning "_LOCAL_DIMMING_BLMODEL_MAX_GAIN Should be <= 32!!!"
#endif
#endif

#if(_LOCAL_DIMMING_ADAPTIVE_SMOOTH_SUPPORT == _ON)
#if(_LOCAL_DIMMING_BACKLIGHT_TYPE != _LOCAL_DIMMING_EDGE_BACKLIGHT)
#warning " _LOCAL_DIMMING_ADAPTIVE_SMOOTH_SUPPORT Only Supports _LOCAL_DIMMING_EDGE_BACKLIGHT!!!"
#endif
#if(_LOCAL_DIMMING_BLACK_SMOOTH_MODE == _OFF)
#warning " _LOCAL_DIMMING_ADAPTIVE_SMOOTH_SUPPORT Is Effective When _LOCAL_DIMMING_BLACK_SMOOTH_MODE Is _ON!!!"
#endif
#endif

#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
#if(_LOCAL_DIMMING_TOTAL_REGION < _LOCAL_DIMMING_TRUE_DIRECT_REGION)
#warning " _LOCAL_DIMMING_USING_YAVG_INFO Should be _OFF!!! when _LOCAL_DIMMING_TOTAL_REGION < _LOCAL_DIMMING_TRUE_DIRECT_REGION"
#endif
#if(_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _OFF)
#warning " _LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION Should be _ON!!! when _LOCAL_DIMMING_USING_YAVG_INFO is ON"
#endif
#endif

#if((_SCALER_TYPE == _RL6829_SERIES) || (_SCALER_TYPE == _RL6952_SERIES))
#if(_LOCAL_DIMMING_USING_EXTRO_INFO == _ON)
#warning " _LOCAL_DIMMING_USING_EXTRO_INFO Should be _OFF !!!"
#endif
#endif



#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
#if(_LOCAL_DIMMING_FUNCTION == _OFF)
#warning " _LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT Should be _OFF!!!"
#endif
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
#if((_HW_DCR_BIT == _DCR_8BIT) && (_HW_DCR_BIT == _DCR_10BIT))
#warning "_HW_DCR_BIT Not Support!!! _GLOBAL_DIMMING_FUNCTION should be _OFF!!!"
#endif

#if(_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_0)
#if(_HW_DCR_YMAXMIN_OPTION_SUPPORT == _OFF)
#warning "_DCR_Y_MAX_VAL Not Support!!! _GLOBAL_DIMMING_FUNCTION should be _OFF!!!"
#endif
#endif
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _OFF)
#if(_GLOBAL_DIMMING_DARK_SENSITIVITY_SUPPORT == _ON)
#warning " _GLOBAL_DIMMING_DARK_SENSITIVITY_SUPPORT Should be _OFF!!!"
#endif
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
#if((_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON) && (_HDR10_SUPPORT == _OFF))
#warning " _GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT Can Not Be Supported When _HDR10_SUPPORT is _OFF!!!"
#endif
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
#if(_GLOBAL_DIMMING_DARK_MODE_MAX_GAIN < 5)
#warning " _GLOBAL_DIMMING_DARK_MODE_MAX_GAIN Can Not Be less than 5!!!"
#endif
#endif


//-------------------------------------------------
// Device
//-------------------------------------------------

#if((_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE) &&\
    (_DEVICE_LED_DRIVER_COMMUNICATE_TYPE == _INTERFACE_SPI) &&\
    (_SPI_SUPPORT == _OFF))
#warning "_SPI_SUPPORT Should Be _ON!!!"
#endif

//-------------------------------------------------
// SDRtoHDR
//-------------------------------------------------
#if(_SDR_TO_HDR_FUNCTION == _ON)

#if(_PCM_FUNCTION == _OFF)
#warning "_COLOR_PCM_FUNCTION Should Be _ON!!!"
#endif

#if(_OCC_FUNCTION == _OFF)
#warning "_COLOR_OCC_FUNCTION Should Be _ON!!!"
#endif

#if(_ICM_FUNCTION == _OFF)
#warning "_COLOR_ICM_FUNCTION Should Be _ON!!!"
#endif

#if(_DCC_FUNCTION == _OFF)
#warning "_COLOR_DCC_FUNCTION Should Be _ON!!!"
#endif

#endif

//-------------------------------------------------
// Night Sniper Function
//-------------------------------------------------
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
#if(_LOCAL_CONTRAST_FUNCTION == _OFF)
#warning "_LOCAL_CONTRAST_FUNCTION Should Be _ON!!!"
#endif

#if(_ICM_CHAMELEON_FUNCTION == _OFF)
#warning "_ICM_CHAMELEON_FUNCTION Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// _ICM_CHAMELEON_FUNCTION
//-------------------------------------------------
#if(_ICM_CHAMELEON_FUNCTION == _ON)
#if(_ICM_FUNCTION == _OFF)
#warning "_COLOR_ICM_FUNCTION Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// LocalContrast
//-------------------------------------------------
#if((_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON) || (_SDR_PLUS_FUNCTION == _ON))
#if(_LOCAL_CONTRAST_FUNCTION == _OFF)
#warning "_LOCAL_CONTRAST_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_LOCAL_CONTRAST_MARGIN_BLOCK_CONTORL == _ON)
#if(_LOCAL_CONTRAST_FUNCTION == _OFF)
#warning "_LOCAL_CONTRAST_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _ON)
#if((_LOCAL_CONTRAST_READYAVG_TOTAL_BLKNUM > _LOCAL_CONTRAST_READYAVG_KCPU_BLKNUM_LIMIT) && (_SCPU_SUPPORT == _OFF))
#warning "_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION Should Be _OFF!!!"
#endif
#endif
//-------------------------------------------------
// 3DDI
//-------------------------------------------------
#if(_3DDI_FUNCTION == _ON)
#if((_FW_3DDI_FUNCTION_SUPPORT == _OFF) ||\
    ((_HW_3DDI_1ST_PATH == _HW_3DDI_PATH_NONE) && (_HW_3DDI_2ND_PATH == _HW_3DDI_PATH_NONE)))
#warning "_3DDI_FUNCTION Should Be _OFF!!!"
#endif
#if(_3DDI_BW_CTRL_SUPPORT == _ON)
#warning "_3DDI_BW_CTRL_SUPPORT Should Be _OFF!!!"
#endif
#endif

//-------------------------------------------------
// HDR10 Color Enhance & Light Enhance
//-------------------------------------------------
#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif
#if(_ICM_FUNCTION == _OFF)
#warning "_COLOR_ICM_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif

#if(_DCC_FUNCTION == _OFF)
#warning "_COLOR_DCC_FUNCTION Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// FreeSync2
//-------------------------------------------------
#if(_FREESYNC_II_SUPPORT == _ON)
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _OFF)
#warning "_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _OFF)
#warning "_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DP_FREESYNC_II_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _OFF)
#warning "_DP_FREESYNC_SUPPORT Should Be _ON!!!"
#endif
#if(_DP_HDR10_SUPPORT == _OFF)
#warning "_DP_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _OFF)
#warning "_HDMI_FREESYNC_SUPPORT Should Be _ON!!!"
#endif
#if(_HDMI_HDR10_SUPPORT == _OFF)
#warning "_HDMI_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FREESYNC_II_FORCE_HDR10_BT2020_SUPPORT == _ON)
#if(_FREESYNC_II_SUPPORT == _OFF)
#warning "_FREESYNC_II_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// Gamut compression
//-------------------------------------------------
#if(_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON)
#if(_RGB_3D_GAMMA_FUNCTION == _OFF)
#warning "_RGB_3D_GAMMA_FUNCTION Should Be _ON when _RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON!!!"
#endif
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON when _RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON!!!"
#endif
#endif

//-------------------------------------------------
// 3D gamma HDR remap
//-------------------------------------------------
#if(_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
#if(_RGB_3D_GAMMA_FUNCTION == _OFF)
#warning "_RGB_3D_GAMMA_FUNCTION Should Be _ON when _RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON!!!"
#endif
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON when _RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON!!!"
#endif
#if(_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON)
#warning "_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT Should Be _OFF when _RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON!!!"
#endif
#endif

//-------------------------------------------------
// HLG
//-------------------------------------------------
#if(_HDMI_HLG_SUPPORT == _ON)
#if(_HDMI_HDR10_SUPPORT == _OFF)
#warning "_HDMI_HDR10_SUPPORT Should be _ON when _HDMI_HLG_SUPPORT == _ON!!!"
#endif
#endif

#if(_DP_HLG_SUPPORT == _ON)
#if(_DP_HDR10_SUPPORT == _OFF)
#warning "_DP_HDR10_SUPPORT Should be _ON when _DP_HLG_SUPPORT == _ON!!!"
#endif
#endif

#if(_PCM_FULL_TIME_FUNCTION == _ON)
#if(_PCM_FUNCTION == _OFF)
#warning "_PCM_FUNCTION Should be _ON when _PCM_FULL_TIME_FUNCTION == _ON!!!"
#endif
#endif

//-------------------------------------------------
// Color Cailibration
//-------------------------------------------------
#if(_OGC_FUNCTION == _ON)
#if(_OGC_TOTAL_GAMMA > 6)
#warning "_OGC_TOTAL_GAMMA Should Be <= 6!!!"
#endif
#endif

#if(_OGC_FUNCTION == _ON)
#if(_OGC_TOTAL_CT > 12)
#warning "_OGC_TOTAL_CT Should Be <= 12!!!"
#endif
#endif

#if(_OGC_FUNCTION == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_COLOR_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OGC_FUNCTION == _ON)
#if(_CONTRAST_FUNCTION == _OFF)
#warning "_COLOR_CONTRAST_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OCC_FUNCTION == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_COLOR_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OGC_DICOM_FUNCTION == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_COLOR_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OCC_FUNCTION == _ON)
#if(_PCM_FUNCTION == _OFF)
#warning "_COLOR_PCM_FUNCTION Should Be _ON!!!"
#endif
#endif

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
#if(_DDCCI0_RXBUF_LENGTH < 128)
#warning "_DDCCI0_RXBUF_LENGTH Should Be >= 128!!!"
#endif

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
#if(_DDCCI_CODE_REDUCTION == _ON)
#warning "_DDCCI_CODE_REDUCTION Should Be _OFF!!!"
#endif
#endif

#if((_DDCCI_OPCODE_VCP_DISP_CALIBRATION < 0xF0) || (_DDCCI_OPCODE_VCP_DISP_CALIBRATION > 0xFF))
#warning "Unreasonable OPCODE for Color Calibration!!!"
#endif

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
#if(_OCC_FUNCTION == _OFF)
#warning "_OCC_FUNCTION Should BE _ON when _OCC_COLORTEMP_TRANSFER_FUNCTION = _ON !!!"
#endif
#if(_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _OFF)
#warning "_OCC_GAMUT_NO_COMPRESSION_SUPPORT Should BE _ON when _OCC_COLORTEMP_TRANSFER_FUNCTION = _ON !!!"
#endif
#if(_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _OFF)
#warning "_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT Should BE _ON when _OCC_COLORTEMP_TRANSFER_FUNCTION = _ON !!!"
#endif
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
#if((_OGC_FUNCTION == _OFF) && (_OCC_FUNCTION == _OFF))
#warning "_COLOR_OGC_FUNCTION or _COLOR_OCC_FUNCTION Should Be _ON!!!"
#endif
#if((_UNIFORMITY_LEVEL0_SUPPORT == _ON) && (_PCM_FULL_TIME_FUNCTION == _ON))
#if(_OCC_PCM_GAMMA_SUPPORT == _OFF)
#warning "_OCC_PCM_GAMMA_SUPPORT Should BE _ON!!!"
#endif
#endif
#endif

#if(_UNIFORMITY_FUNCTION == _OFF)
#if((_UNIFORMITY_1ST_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_2ND_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_3RD_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_4TH_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_5TH_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_6TH_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_7TH_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_8TH_TABLE_LEVEL != _UNIFORMITY_NONE) ||\
    (_UNIFORMITY_9TH_TABLE_LEVEL != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_FUNCTION  Should Be  _ON!!!"
#endif
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#warning "_COLOR_UNIFORMITY_FUNCTION Should BE _ON!!!"
#endif
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
#if((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_NONE))
#warning "_UNIFORMITY_1ST_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_3RD_TABLE_LEVEL + _UNIFORMITY_4TH_TABLE_LEVEL + _UNIFORMITY_5TH_TABLE_LEVEL + _UNIFORMITY_6TH_TABLE_LEVEL + _UNIFORMITY_7TH_TABLE_LEVEL + _UNIFORMITY_8TH_TABLE_LEVEL + _UNIFORMITY_9TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_2ND_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_4TH_TABLE_LEVEL + _UNIFORMITY_5TH_TABLE_LEVEL + _UNIFORMITY_6TH_TABLE_LEVEL + _UNIFORMITY_7TH_TABLE_LEVEL + _UNIFORMITY_8TH_TABLE_LEVEL + _UNIFORMITY_9TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_3RD_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_5TH_TABLE_LEVEL + _UNIFORMITY_6TH_TABLE_LEVEL + _UNIFORMITY_7TH_TABLE_LEVEL + _UNIFORMITY_8TH_TABLE_LEVEL + _UNIFORMITY_9TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_4TH_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_6TH_TABLE_LEVEL + _UNIFORMITY_7TH_TABLE_LEVEL + _UNIFORMITY_8TH_TABLE_LEVEL + _UNIFORMITY_9TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_5TH_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_6TH_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_7TH_TABLE_LEVEL + _UNIFORMITY_8TH_TABLE_LEVEL + _UNIFORMITY_9TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_6TH_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_7TH_TABLE_LEVEL == _UNIFORMITY_NONE) && ((_UNIFORMITY_8TH_TABLE_LEVEL + _UNIFORMITY_9TH_TABLE_LEVEL) != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_7TH_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#if((_UNIFORMITY_8TH_TABLE_LEVEL == _UNIFORMITY_NONE) && (_UNIFORMITY_9TH_TABLE_LEVEL != _UNIFORMITY_NONE))
#warning "_UNIFORMITY_8TH_TABLE_LEVEL  Can't Be  _UNIFORMITY_NONE!!!"
#endif
#endif

#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
#if(_UNIFORMITY_FUNCTION == _OFF)
#warning "_UNIFORMITY_FUNCTION Should Be _ON!!!"
#endif
#if(_OCC_FUNCTION == _OFF)
#warning "_OCC_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
#if(_CONTRAST_FUNCTION == _OFF)
#warning "_COLOR_CONTRAST_FUNCTION Should Be _ON!!!"
#endif
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_OCC_FUNCTION == _OFF)
#warning "_COLOR_OCC_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_COLOR_PROCESS_CONTROL_BY_USER == _ON)
#warning "_COLOR_PROCESS_CONTROL_BY_USER Should Be _OFF!!!"
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
#if(_CONTRAST_FUNCTION == _OFF)
#warning "_COLOR_CONTRAST_FUNCTION Should Be _ON!!!"
#endif
#endif

#if((_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON) || (_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON))
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif
#if(_OCC_IG_NODE_1025_SUPPORT == _ON)
#warning "_OCC_IG_NODE_1025_SUPPORT Should Be _OFF!!!"
#endif

#endif

#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDR10_USER_MASTERING_LV_CHANGE_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
#if(_HDMI_HDR10_SUPPORT == _OFF)
#warning "_HDMI_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)
#warning "_HDMI_ADVANCED_HDR10_SUPPORT_MODE Should Not Be _ADVANCED_HDR10_VSIF_AND_DHDR_MODE"
#endif

#if(_DP_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
#warning "_DP_ADVANCED_HDR10_SUPPORT_MODE Should Be _ADVANCED_HDR10_NONE"

#if(_DP_HDR10_SUPPORT == _OFF)
#warning "_DP_HDR10_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
#if(_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_NONE)
#warning "_HDMI_ADVANCED_HDR10_SUPPORT_MODE Should Not Be _ADVANCED_HDR10_NONE"
#endif

#if(_SCPU_SUPPORT == _OFF)
#warning "_SCPU_SUPPORT Should Be _ON!!!"
#endif

#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _OFF)
#warning "_HW_CPU32_NOTIFY_INT_SUPPORT Should Be _ON!!!"
#endif

#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
#warning "_ADVANCED_HDR10_SUPPORT should be _OFF when _GLOBAL_DIMMING_FUNCTION is ON!!!"
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#warning "_ADVANCED_HDR10_SUPPORT should be _OFF when _LOCAL_DIMMING_FUNCTION is ON!!!"
#endif
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif

#if(_OCC_IG_NODE_1025_SUPPORT == _ON)
#warning "_OCC_IG_NODE_1025_SUPPORT Should Be _OFF when _HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT is ON!!!"
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
#warning "_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT should be _OFF when _GLOBAL_DIMMING_FUNCTION is ON!!!"
#endif

#endif

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDR10_SUPPORT Should Be _ON!!!"
#endif

#if(_OCC_IG_NODE_1025_SUPPORT == _ON)
#warning "_OCC_IG_NODE_1025_SUPPORT Should Be _OFF when _HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT is ON!!!"
#endif

#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
#warning "_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT should be _OFF!!!"
#endif

#if(_HDR10_EETF_TONEMAPPING_SUPPORT == _ON)
#warning "_HDR10_EETF_TONEMAPPING_SUPPORT Should Be _OFF when _HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT is ON!!!"
#endif

#if(_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
#warning "_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT should be _OFF!!!"
#endif
#endif

#if(_SCPU_RTOS == _ON)
#if(_HW_CPU32_SCPU_SUPPORT == _OFF)
#warning "_HW_CPU32_SCPU_SUPPORT is _OFF on this Scaler IC!!!"
#endif
#if(_SCPU_SUPPORT == _OFF)
#warning "_SCPU_SUPPORT should be _ON when _SCPU_RTOS is _ON!!!"
#endif
#endif

#if(_HW_D_DOMAIN_RGN_COUNT_MAX <= 1)
#if(_ADVANCED_HDR10_SUPPORT == _ON)
#warning "_ADVANCED_HDR10_SUPPORT should be _OFF when _HW_D_DOMAIN_RGN_COUNT_MAX <= 1 !!!"
#endif
#endif

#if(_DM_FUNCTION == _ON)
#if(_HDR10_SUPPORT == _OFF)
#warning "_HDMI or DP_HDR10_SUPPORT should be _ON!!!"
#endif

#if((_DM_CONFIG_DARK_MODE_INDEX == _DM_PICTURE_MODE_NONE) || (_DM_CONFIG_BRIGHT_MODE_INDEX == _DM_PICTURE_MODE_NONE))
#warning "DM Dark/Bright Mode Must Exist!!!"
#endif

#if(_DM_CONFIG_DARK_MODE_INDEX == _DM_CONFIG_BRIGHT_MODE_INDEX)
#warning "DM Dark/Bright Mode Cannot Be The Same!!!"
#endif

#if((_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE) && (_HDMI21_ALLM_SUPPORT == _OFF))
#warning "DM Game Mode Cannot Be Supported Without HDMI ALLM!!!"
#endif

#endif

#if(_DCIP3_NO_COMPRESSION_SUPPORT == _ON)
#if(_OCC_FUNCTION == _OFF)
#warning "_OCC_FUNCTION Should be _ON when _DCIP3_NO_COMPRESSION_SUPPORT == _ON!!!"
#endif
#endif

#if(_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _ON)
#if(_OCC_FUNCTION == _OFF)
#warning "_OCC_FUNCTION Should be _ON when _OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _ON!!!"
#endif
#endif

#if((_OGC_TOTAL_DICOM < 1) || (_OGC_TOTAL_DICOM > 4))
#warning "_OGC_TOTAL_DICOM Should Be < 4!!!"
#endif

#if(_OCC_DISPLAY_P3_GAMMA_22_SUPPORT == _ON)
#if(_OCC_FUNCTION == _OFF)
#warning "_OCC_FUNCTION Should be _ON when _OCC_DISPLAY_P3_GAMMA_22_SUPPORT == _ON!!!"
#endif
#endif

#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should be _ON when _OCC_PCM_GAMMA_SUPPORT == _ON!"
#endif
#if(_OCC_FUNCTION == _OFF)
#warning "_OCC_FUNCTION Should be _ON when _OCC_PCM_GAMMA_SUPPORT == _ON!"
#endif
#if(_PCM_FUNCTION == _OFF)
#warning "_PCM_FUNCTION Should Be _ON!!!"
#endif
#if(_OGC_FUNCTION == _ON)
#warning "_OGC_FUNCTION Should be _OFF when _OCC_PCM_GAMMA_SUPPORT == _ON!"
#endif
#if(_OGC_TOTAL_CT > 6)
#warning "_OGC_TOTAL_CT Should be <= 6 when _OCC_PCM_GAMMA_SUPPORT == _ON!"
#endif
#if(_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _OFF)
#warning "_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT Should be _ON when _OCC_PCM_GAMMA_SUPPORT == _ON!"
#endif
#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _OFF)
#warning "_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION should be _ON!"
#endif
#endif
#endif

#if(_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE)
#if(_FREESYNC_II_FLASH_PAGE != 0)
#warning "_FREESYNC_II_FLASH_PAGE should be 0 when _MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE"
#endif
#if(_TWO_BRI_CALIBRATION_TYPE < _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR)
#warning "_TWO_BRI_CALIBRATION_TYPE should be _TWO_BRI_CALIBRATION_OGC_OCC_DICOM_HDR or _MULTI_BRI_CALIBRATION_OGC_OCC"
#endif
#endif

#if(_TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC)
#if(_MULTI_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_NONE)
#warning "_MULTI_BRI_CALIBRATION_TYPE should not be _MULTI_BRI_CALIBRATION_NONE when _TWO_BRI_CALIBRATION_TYPE == _MULTI_BRI_CALIBRATION_OGC_OCC"
#endif
#endif


#if(_OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON)
#if(_OCC_FUNCTION == _OFF)
#warning "_OCC_FUNCTION Should be _ON when _OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON!!!"
#endif
#if(_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT == _OFF)
#warning "_OCC_USER_DEFINE_SHIFT_1_BIT_SUPPORT Should be _ON when _OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON!!!"
#endif
#if(_DCIP3_NO_COMPRESSION_SUPPORT == _ON)
#warning "_DCIP3_NO_COMPRESSION_SUPPORT Should be _OFF when _OCC_GAMUT_NO_COMPRESSION_SUPPORT == _ON!!!"
#endif
#endif

#if(_SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON)
#if((_OCC_FUNCTION == _OFF) && (_OGC_FUNCTION == _OFF))
#warning "_OCC_FUNCTION or _OGC_FUNCTION should be _ON when _SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON!!!"
#endif
#endif

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#if(_OCC_FUNCTION == _OFF)
#warning "_OCC_FUNCTION Should Be _ON when _OCC_RGB_3D_GAMMA_SUPPORT == _ON!!!"
#endif
#if(_RGB_3D_GAMMA_FUNCTION == _OFF)
#warning "_RGB_3D_GAMMA_FUNCTION Should Be _ON when _OCC_RGB_3D_GAMMA_SUPPORT == _ON!!!"
#endif
#if(_OCC_RGB_3D_GAMMA_TOTAL_SET <= 0)
#warning "_OCC_RGB_3D_GAMMA_TOTAL_SET Should Bigger Than 0!!!"
#endif
#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#else
#if(_OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
#warning "_OCC_RGB_3D_GAMMA_SUPPORT Should Be _ON when _OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON!!!"
#endif
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
#warning "_OCC_RGB_3D_GAMMA_SUPPORT should be _ON when _RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON!!!"
#endif
#endif

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
#if(_RGB_3D_GAMMA_FUNCTION == _OFF)
#warning "_RGB_3D_GAMMA_FUNCTION Should Be _ON when _RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON!!!"
#endif
#endif

#if(_OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
#if(_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _OFF)
#warning "_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT Should Be _ON when _OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON!!!"
#endif
#if(_TWO_BRI_CALIBRATION_TYPE == _TWO_BRI_CALIBRATION_NONE)
#warning "_TWO_BRI_CALIBRATION_TYPE Should not Be _TWO_BRI_CALIBRATION_NONE when _OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON!!!"
#endif
#endif

//-------------------------------------------------
// Input Gamma Check
//-------------------------------------------------
#if((_OCC_IG_NODE_1025_SUPPORT == _ON) || (_INPUT_GAMMA_NODE_1025_SUPPORT == _ON))
#if(_HW_INPUT_GAMMA_TABLE_NODE_TYPE != _INPUT_GAMMA_NODE_1025)
#warning "_INPUT_GAMMA_NODE_1025_SUPPORT Should Be _OFF!!!"
#endif
#endif

//-------------------------------------------------
// Color Conversion Check
//-------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _OFF) ||\
    (_YCC_QUANTIZATION_RANGE_FUNCTION == _OFF))
#warning "_COLOR_RGB_QUANTIZATION_RANGE_FUNCTION and _COLOR_YCC_QUANTIZATION_RANGE_FUNCTION Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// UltraVivid Check
//-------------------------------------------------
#if(_ULTRA_VIVID_FUNCTION_WITH_DSHP == _ON)
#if(_ULTRA_VIVID_FUNCTION == _OFF)
#warning "_ULTRA_VIVID_FUNCTION Should be _ON when _ULTRA_VIVID_FUNCTION_WITH_DSHP == _ON!!!"
#endif
#endif

#if(_ULTRA_VIVID_FUNCTION_WITH_IDLTI == _ON)
#if(_ULTRA_VIVID_FUNCTION == _OFF)
#warning "_ULTRA_VIVID_FUNCTION Should be _ON when _ULTRA_VIVID_FUNCTION_WITH_IDLTI == _ON!!!"
#endif
#endif

//-------------------------------------------------
// Global Hue & Sat
//-------------------------------------------------
#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
#if(_GLOBAL_HUE_SATURATION_FUNCTION == _OFF)
#warning " _GLOBAL_HUE_SATURATION_FUNCTION Should be _ON!!!"
#endif
#endif

#if(_GLOBAL_HUE_SATURATION_HDR_SUPPORT == _ON)
#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _OFF)
#warning " _GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION Should be _ON!!!"
#endif
#endif
//-------------------------------------------------
// MRCM Check
//-------------------------------------------------
#if(_MRCM_SUPPORT == _ON)
#if(_PCM_FUNCTION == _OFF)
#warning "_PCM_FUNCTION Should be _ON"
#endif
#endif

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
#if(_GAMMA_FUNCTION == _ON)
#if(_OCC_PCM_GAMMA_SUPPORT == _OFF)
#warning "If _DYNAMIC_LOWBLUE_FUNCTION == _ON, _OCC_PCM_GAMMA_SUPPORT Should be _ON"
#endif
#endif
#if(_HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT == _OFF)
#warning "If _HW_PANEL_UNIFORMITY_DB_SRAM_MODE_SUPPORT == _OFF, _DYNAMIC_LOWBLUE_FUNCTION Should be _OFF"
#endif
#endif
//-------------------------------------------------
// System Eeprom Check
//-------------------------------------------------
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _OFF)
#warning "_EEPROM_ACCESS_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// System Eeprom Emulation
//-------------------------------------------------
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_SYSTEM_EEPROM_EMULATION_END_PAGE > 14)
#warning "System Eeprom Emulation End Page Error!!!"
#endif

#if((_SYSTEM_EEPROM_EMULATION_END_PAGE - _SYSTEM_EEPROM_EMULATION_START_PAGE) < (_END_OF_PAGEID - _START_OF_PAGEID + 1))
#warning "Flash Page Number and Page ID Number Warning!!!"
#endif
#endif

//-------------------------------------------------
// EDID Check
//-------------------------------------------------
#if(_EDID_TABLE_LOCATED_IN_FLASH == _ON)
#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// HDCP 2.2 Check
//-------------------------------------------------
#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_HW_DP_HDCP_2_2_FUNCTION_SUPPORT == _OFF)
#warning "_DP_HDCP_2_2_SUPPORT Can Not Be Supported!!!"
#endif
#endif

#if(_HDMI_FRL_SUPPORT == _ON)
#if(_TMDS_HDCP_2_2_SUPPORT == _OFF)
#warning "_TMDS_HDCP_2_2_SUPPORT shall be supported when _HDMI_FRL_SUPPORT is supported!!!"
#endif
#endif

//-------------------------------------------------
// HDCP14 Ksv FIFO Size Check
//-------------------------------------------------
#if(_DP_TX_HDCP14_DEVICE_COUNT_MAX < (_HW_DP_MST_DAISY_ST_NUM_MAX * 3 + 2))
#warning "_DP_TX_HDCP14_DEVICE_COUNT_MAX Should Be >= (_HW_DP_MST_DAISY_ST_NUM_MAX * 3 + 2)!!!"
#endif

//-------------------------------------------------
// HDCP2 Receiver_ID_List FIFO Size Check
//-------------------------------------------------
#if(_DP_TX_HDCP2_DEVICE_COUNT_MAX < (_HW_DP_MST_DAISY_ST_NUM_MAX * 3 + 2))
#warning "_DP_TX_HDCP2_DEVICE_COUNT_MAX Should Be >= (_HW_DP_MST_DAISY_ST_NUM_MAX * 3 + 2)!!!"
#endif

//-------------------------------------------------
// HDCP Key Check
//-------------------------------------------------
#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || ((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)))
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY)
#if((_HW_FUSE_HDCP_1_4_RXKEY == _OFF) || (_HW_FUSE_HDCP_1_4_TXKEY == _OFF))
#warning "_HDCP_1_4_KEY_LOCATION OTP Can Not Be Supported!!! "
#endif
#endif

#if((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY) && (_HW_FUSE_HDCP_2_2_RXKEY == _OFF))
#warning "_RX_HDCP_2_2_KEY_LOCATION OTP Can Not Be Supported!!! "
#endif

#if((_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_OTPMEMORY))
#warning "_TX_HDCP_2_2_KEY_LOCATION OTP Can Not Be Supported!!! "
#endif


#if((_HW_TX_HDCP_2_2_KEY_LOCATION_IROM_SUPPORT == _OFF) && (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_IROM))
#warning "HDCP 2 TX Key Location From IROM Can Not Be Support!"
#endif

#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_IROM) || (_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_IROM))
#warning "HDCP1.4 KEY/HDCP2 RX KEY Can Not Be From Irom!"
#endif

//--------------------------------------------------
// HDMI CEC Config Check
//--------------------------------------------------
#if(_HDMI_CEC_SUPPORT == _ON)
#if(_SCALER_TYPE == _RL6829_SERIES)
#if((_HDMI_CEC_ARBITRATION_MODE_FIXED_VERSION == _ON) ||\
    (_HDMI_CEC_RX_LOWIMPEDANCE_FIXED_VERSION == _ON) ||\
    (_HDMI_CEC_MULTI_LA_FREETIME_FIXED_VERSION == _ON) ||\
    (_HDMI_CEC_MATCH_ADDR_CLEAR_FIXED_VERSION == _ON))
#warning "CEC ECO Function Only Support IC Version after RL6952!!!"
#endif
#endif
#endif

//--------------------------------------------------
// DP Dual Port Config Check
//--------------------------------------------------
#if(_DUAL_DP_SUPPORT == _ON)
#if((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE) ||\
    (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE))
#warning "_SOURCE_AUTO_SEARCH_STYLE you choose can't be supported when using DP Dual Port!!!"
#endif
#endif

//--------------------------------------------------
// VGA Check
//--------------------------------------------------
#if((_YPBPR_SUPPORT == _ON) && (_SOG_SUPPORT == _OFF))
#if(_SOG_SUPPORT == _OFF)
#warning "_SOG_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// Free Sync Check
//--------------------------------------------------
#if((_FORCE_TO_FREE_RUN_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
#if(_FREESYNC_SUPPORT == _ON)
#warning "_FREESYNC_SUPPORT Should Be _OFF!!!"
#endif
#if(_HDMI21_GAMING_VRR_SUPPORT == _ON)
#warning "_HDMI21_GAMING_VRR_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _OFF)
#warning "_DDCCI_AUTO_SWITCH_SUPPORT Should Be _ON!!!"
#endif

#if((_HDMI_FREESYNC_MCCS_VCP < 0xE0) || (_HDMI_FREESYNC_MCCS_VCP > 0xFF))
#warning "_HDMI_FREESYNC_MCCS_VCP Should Be in [0xE0:0xFF]!!!"
#endif

#endif
#endif

//--------------------------------------------------
// FreeSync Replay Check
//--------------------------------------------------
#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _OFF)
#warning "_HDMI_FREESYNC_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// Source Switch Check
//--------------------------------------------------
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
#warning "_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT Should Be _OFF!!!"
#endif
#endif

//-------------------------------------------------
// HDMI Check
//-------------------------------------------------
#if(_HDMI_SUPPORT == _OFF)
#if(_DVI_DE_ONLY_SUPPORT == _ON)
#warning "_DVI_DE_ONLY_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#warning "_HDMI_FREESYNC_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#warning "_HDMI_FREESYNC_II_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)
#warning "_HDMI_FREESYNC_REPLAY_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI21_QMS_VRR_SUPPORT == _ON)
#warning "_HDMI21_QMS_VRR_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI21_GAMING_VRR_SUPPORT == _ON)
#warning "_HDMI21_GAMING_VRR_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
#warning "_HDMI21_FVA_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
#warning "_HDMI21_ALLM_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI21_CCBPC_SUPPORT == _ON)
#warning "_HDMI21_CCBPC_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#warning "_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
#warning "_HDMI_HDR10_SUPPORT Should Be _OFF!!!"
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#warning "_TMDS_HDCP_2_2_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
#warning "_HDMI21_ALLM_SUPPORT Should Be _OFF!!!"
#endif

#if(_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON)
#warning "_HDMI_3D_VIDEO_IDENTIFY_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if((_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON))
#warning "ACER's HPD Toggle can't use timer event!!!"
#endif

#if((_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON) && (_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON))
#warning "ACER's HPD Toggle can't support HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE!!!"
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON))
#warning "DP/HDMI compatible mode can't use timer event!!!"
#endif

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON))
#warning "DP/HDMI compatible mode can't support HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE!!!"
#endif

#if((_TMDS_HPD_WAITING_TIMER_EVENT_SUPPORT == _ON) && (_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON))
#warning "HPD Timer event can't support HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE!!!"
#endif

#if((_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON) && (_HDMI_FRL_SUPPORT == _ON))
#warning "FRL can't support _HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE!!!"
#endif

#if(_HDMI20_SUPPORT == _ON)
#if((_HDMI_SUPPORT == _ON) && ((_USB_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON)))
#if((_HDMI_SINK_RTK_ID_STRING_H != _USB_PRODUCT_ID_H) || (_HDMI_SINK_RTK_ID_STRING_L != _USB_PRODUCT_ID_L))
#warning "_HDMI_SINK_RTK_ID_STRING_H/L Should be same as _USB_PRODUCT_ID_H/L!!!"
#endif
#endif
#endif

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if((_SOURCE_AUTO_SEARCH_STYLE != _SOURCE_POLLING_IN_SEARCH_STATE) && (_SOURCE_AUTO_SEARCH_STYLE != _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) && (_SOURCE_AUTO_SEARCH_STYLE != _SOURCE_POLLING_ACER_STYLE))
#warning "_SOURCE_AUTO_SEARCH_STYLE Should Be _SOURCE_POLLING_IN_SEARCH_STATE or _SOURCE_POLLING_AFTER_NOSIGNAL_STATE or _SOURCE_POLLING_ACER_STYLE!"
#endif

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
#warning "_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT Should Be OFF when _HDMI_EXTERNAL_SWITCH_SUPPORT = _ON!!!"
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
#warning "_SOURCE_BACKGROUND_DETECT_SUPPORT Should Be OFF when _HDMI_EXTERNAL_SWITCH_SUPPORT = _ON!!!"
#endif
#endif

#if((_HDMI_3D_VIDEO_IDENTIFY_SUPPORT == _ON) && ((_DM_FUNCTION == _ON) || (_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)))
#warning "_HDMI_3D_VIDEO_IDENTIFY_SUPPORT Can be ON when HDR10+ or DM Not Support!!!"
#endif

#if((_HW_HDMI_EMP_SRAM_SUPPORT == _OFF) && ((_DM_FUNCTION == _ON) || (_HDMI_SBTM_SUPPORT == _ON) || (_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE)))
#warning "_DM_FUNCTION or _HDMI_SBTM_SUPPORT Should Be OFF or _HDMI_ADVANCED_HDR10_SUPPORT_MODE Should Not Be _ADVANCED_HDR10_VSIF_AND_DHDR_MODE when _HW_HDMI_EMP_SRAM_SUPPORT = _OFF!!!"
#endif

//-------------------------------------------------
// DP Check
//-------------------------------------------------
#if(_DP_SUPPORT == _ON)

#if(_DP_MST_SUPPORT == _ON)
#if(!(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON)) ||\
      ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON)) ||\
      ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_MST_PORT_SUPPORT == _ON))))
#warning "At Least One Of _Dx_DP_MST_PORT_SUPPORT Should Be _ON!!!"
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_INPUT_PORT_TYPE != _D9_DP_PORT)
#warning "_D9_INPUT_PORT_TYPE Should Be _D9_DP_PORT when _DP_MST_PXP_MODE_SUPPORT == _ON!!!"
#endif
#if((_DP_MST_PXP_FIXED_MODE_SUPPORT == _OFF) && (_DP_MST_PXP_SELECT_MODE_SUPPORT == _OFF))
#warning "At Least One Of PXP Mode Should Be _ON!!!"
#endif
#else
#if(_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT == _ON)
#warning "_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT Should Be _OFF when _DP_MST_PXP_MODE_SUPPORT == _OFF !!!"
#endif
#endif // End of #if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#if((_DP_LT_TP1_FORCE_MARGINAL_LINK == _OFF) && (_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON))
#warning "_DP_LT_TP1_FORCE_MARGINAL_LINK Should Be _ON when _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _ON !!!"
#endif

#if((_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON) && ((_DP_LT_TP1_FORCE_MARGINAL_LINK == _OFF) || (_DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 == _OFF)))
#warning "_DP_LT_TP1_FORCE_MARGINAL_LINK and _DP_LT_DIRECT_REQUEST_SWING_LEVEL_2 Should Be _ON when _DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON !!!"
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_LOW_SPEED_162MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_LOW_SPEED_162MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_LOW_SPEED_162MHZ)))
#if(((_DP_RX_DSC_DECODER_SUPPORT == _OFF) && (_INPUTCLOCK_RANG_DP > 2160)) ||\
    ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_INPUTCLOCK_RANG_DP > 6480)))
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED_270MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED_270MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED_270MHZ)))
#if(((_DP_RX_DSC_DECODER_SUPPORT == _OFF) && (_INPUTCLOCK_RANG_DP > 3600)) ||\
    ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_INPUTCLOCK_RANG_DP > 10800)))
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)))
#if(((_DP_RX_DSC_DECODER_SUPPORT == _OFF) && (_INPUTCLOCK_RANG_DP > 7200)) ||\
    ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_INPUTCLOCK_RANG_DP > 21600)))
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)))
#if(((_DP_RX_DSC_DECODER_SUPPORT == _OFF) && (_INPUTCLOCK_RANG_DP > 10800)) ||\
    ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_INPUTCLOCK_RANG_DP > 27200)))
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_1000MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_1000MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_1000MHZ)))
#if(((_DP_RX_DSC_DECODER_SUPPORT == _OFF) && (_INPUTCLOCK_RANG_DP > 16118)) ||\
    ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_INPUTCLOCK_RANG_DP > 27200)))
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_1350MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_1350MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_1350MHZ)))
#if(((_DP_RX_DSC_DECODER_SUPPORT == _OFF) && (_INPUTCLOCK_RANG_DP > 21760)) ||\
    ((_DP_RX_DSC_DECODER_SUPPORT == _ON) && (_INPUTCLOCK_RANG_DP > 27200)))
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_2000MHZ)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_2000MHZ)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_LINK_CLK_RATE == _DP_ULTRA_SPEED_2000MHZ)))
#if(_INPUTCLOCK_RANG_DP > 28000)
#warning "_INPUTCLOCK_RANG_DP must less than Link CLK Rate!!!"
#endif
#endif

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
#if((_DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT == 0) || (_DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT % 2 == 1))
#warning "_DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT shall not be 0 or Odd number!!!"
#endif
#endif

#if(_INPUTCLOCK_RANG_USBC > _INPUTCLOCK_RANG_DP)
#warning "_INPUTCLOCK_RANG_USBC must less than _INPUTCLOCK_RANG_DP!!!"
#endif

#if(_FW_DP_HDMI_COMPATIBLE_MODE_SUPPORT == _OFF)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#warning "_DP_HDMI_COMPATIBLE_MODE Should Be _OFF!!!"
#endif
#endif

#if(_DP_HDMI_COMPATIBLE_MODE_ENHANCED == _ON)
#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)
#warning "_DP_HDMI_COMPATIBLE_MODE_ENHANCED Should Be _OFF!!!"
#endif
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDCP_2_2_SUPPORT == _OFF)
#warning "_DP_HDCP_2_2_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _OFF)
#warning "_DP_FREESYNC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DP_AUX_REPLY_TIMEOUT_USER_SETTING > _DP_AUX_I2C_REPLY_TIMEOUT_SETTING)
#warning "_DP_AUX_REPLY_TIMEOUT_USER_SETTING Should be <= _DP_AUX_I2C_REPLY_TIMEOUT_SETTING!!!"
#endif

#if((_DP_SDP_META_0_PAYLOAD_LENGTH +\
    _DP_SDP_META_1_PAYLOAD_LENGTH +\
    _DP_SDP_META_2_PAYLOAD_LENGTH +\
    _DP_SDP_META_3_PAYLOAD_LENGTH +\
    _DP_SDP_META_4_PAYLOAD_LENGTH) > _HW_DP_SDP_META_SRAM_DB_LENGTH)
#warning "SUM(_DP_SDP_META_0/1/2/3/4_PAYLOAD_LENGTH) should < _HW_DP_SDP_META_SRAM_DB_LENGTH !!!"
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#if(_LOW_SPEED_ADC_SUPPORT == _OFF)
#warning "_LOW_SPEED_ADC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#if(_DP_HBLANKING_REDUCTION_SUPPORT == _OFF)
#warning "_DP_HBLANKING_REDUCTION_SUPPORT Should Be _ON, when _DP_RX_128B132B_CODING_TYPE_SUPPORT Be _ON!!!"
#endif
#endif

#else // #if(_DP_SUPPORT == _OFF)

#if(_DP_MST_SUPPORT == _ON)
#warning "_DP_MST_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
#warning "_DP_FREESYNC_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_FREESYNC_II_SUPPORT == _ON)
#warning "_DP_FREESYNC_II_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#warning "_DP_ADAPTIVESYNC_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#warning "_DP_HDR10_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
#warning "_DP_RX_DSC_DECODER_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
#warning "_DP_TX_DSC_PASSTHROUGH_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
#warning"_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#warning "_DP_HDCP_2_2_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_HBE_SUPPORT == _ON)
#warning "_DP_HBE_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_HBLANKING_REDUCTION_SUPPORT == _ON)
#warning "_DP_HBLANKING_REDUCTION_SUPPORT Should Be _OFF!!!"
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
#warning "_DP_PR_MODE_SUPPORT Should Be _OFF!!!"
#endif

#endif

#if(_DP_TX_SUPPORT == _OFF)
#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
#warning "_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT Should Be _OFF!!!"
#endif
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
#if(_DP_TX_LTTPR_MODE_8B10B == _DP_TX_LTTPR_NON_LTTPR_MODE)
#warning "_DP_TX_LTTPR_MODE_8B10B Should Not Be _DP_TX_LTTPR_NON_LTTPR_MODE when _DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON!!!"
#endif
#endif
//--------------------------------------------------
// TMDS HDMI 2.0 SCDC CTS Check
//--------------------------------------------------
#if(_HDMI20_SUPPORT == _OFF)
#if(_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON)
#warning "_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT Should Be _OFF!!!"
#endif
#endif

//--------------------------------------------------
// Eizo Clock Lane Z0 Toggle in Power Saving Check
//--------------------------------------------------
#if(_HDMI_SUPPORT != _ON)
#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT Should Be _OFF!!!!"
#endif
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
#if(_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY < 50)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY Should Bigger Than 50!!!!"
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY > 1000)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY Should Smaller Than 1000!!!!"
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY < 50)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY Should Bigger Than 50!!!!"
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY > 1000)
#warning "_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY Should Smaller Than 1000!!!!"
#endif
#endif

//--------------------------------------------------
// Type-C Check
//--------------------------------------------------
#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
#if((_USB_VENDOR_ID_H == 0x0B) && (_USB_VENDOR_ID_L == 0xDA))
#if((_USB_PRODUCT_ID_H == 0x00) && (_USB_PRODUCT_ID_L == 0x00))
#warning "_USB_PRODUCT_ID_H/_USB_PRODUCT_ID_L Should Be Defined as RTD Number When VID = Realtek"
#endif

#if((_USB_PRODUCT_ID_H & 0xF0) != 0x20)
#warning "_USB_PRODUCT_ID_H != 0x20, MM1 RTD Number Should start from 0x2xxx When VID = Realtek"
#endif
#endif  // End of #if((_USB_VENDOR_ID_H == 0x0B) && (_USB_VENDOR_ID_L == 0xDA))

#if(_TYPE_C_EMB_PD_VERSION > _HW_PD_SUPPORT_VERSION)
#warning "'_TYPE_C_EMB_PD_VERSION' Cannot more than '_HW_PD_SUPPORT_VERSION'"
#endif
#endif  // End of #if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_SUPPORT == _ON) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON) && (_TYPE_C_PORT_CTRL_RTS_FW_SPEC_VER < _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D9))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' Need _PORT_CTRL_RTS_FW_SPEC_VERSION_V0D9 or uper version~ !!"
#endif

#if((_BILLBOARD_SCALER_SUPPORT == _ON) && ((_DX_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _OFF) && (_DX_TYPE_C_EXT_DP_ALT_MODE_SUPPORT == _OFF)))
#if(_USER_TYPE_C_BB_STRING_DP_SUPPORT == _ON)
#warning "_USER_TYPE_C_BB_STRING_DP_SUPPORT Can Not Be Supported With No DP AltMode Supported!!!"
#endif
#endif

#if((_BILLBOARD_SCALER_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_LENOVO_ALT_MODE))
#if(_USER_TYPE_C_BB_STRING_LENOVO_SUPPORT == _ON)
#warning "_USER_TYPE_C_BB_STRING_LENOVO_SUPPORT Can Not Be Supported With No LENOVO AltMode Supported!!!"
#endif
#endif

#if(((_BILLBOARD_SCALER_SUPPORT == _OFF) || (_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
#warning "_USB_TYPE_C_BB_PROGRAM_SUPPORT Can Not Be ON With _BILLBOARD_SCALER_SUPPORT OFF Or _FLASH_WRITE_FUNCTION_SUPPORT OFF!!!"
#endif

#if((_USB_BB_HID_TYPE_SUPPORT == _ON) && ((_BILLBOARD_SCALER_SUPPORT == _OFF) || (_FLASH_WRITE_FUNCTION_SUPPORT == _OFF) || (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _OFF)))
#warning "_USB_BB_HID_TYPE_SUPPORT Can Not Be ON With _BILLBOARD_SCALER_SUPPORT OFF Or _FLASH_WRITE_FUNCTION_SUPPORT OFF or _USB_TYPE_C_BB_PROGRAM_SUPPORT OFF!!!"
#endif
//--------------------------------------------------
// U2Host Check
//--------------------------------------------------
#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#if((_HW_USB2_HOST_SUPPORT == _OFF) || (_USB2_HOST_PORT_SUPPORT == _OFF) || (_HW_DM_CLIENT_SUPPORT == _OFF) || (_FRC_SUPPORT == _OFF) || (_M_DOMAIN_12BIT_SUPPORT == _OFF))
#warning "_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT ON Must With _HW_USB2_HOST_SUPPORT and _USB2_HOST_PORT_SUPPORT and _HW_DM_CLIENT_SUPPORT and _FRC_SUPPORT and _M_DOMAIN_12BIT_SUPPORT all ON"
#endif
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
// #if((_HW_USB2_HOST_SUPPORT == _OFF) || (_USB2_HOST_PORT_SUPPORT == _OFF) || (_DUAL_BANK_SUPPORT == _OFF))
#if((_HW_USB2_HOST_SUPPORT == _OFF) || (_USB2_HOST_PORT_SUPPORT == _OFF)) // TO be Modified When Dual Bank Related function Added
#warning "_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT ON Must With _HW_USB2_HOST_SUPPORT and _USB2_HOST_PORT_SUPPORT and _DUAL_BANK_SUPPORT all ON"
#endif
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#warning "_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT and _USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT Can Not Be ON At The Same Time"
#endif
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _OFF)
#if(_USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK == _ON)
#warning "(_USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK == _ON) can only be set when (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)"
#endif

#if(_USB2_HOST_1ST_SUB_FOLDER_SUPPORT == _ON)
#warning "(_USB2_HOST_1ST_SUB_FOLDER_SUPPORT == _ON) can only be set when (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)"
#endif

#if(_USB2_HOST_FILE_NAME_JUDGE_VERSION == _ON)
#warning "(_USB2_HOST_FILE_NAME_JUDGE_VERSION == _ON) can only be set when (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)"
#endif

#if(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON)
#warning "(_USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT == _ON) can only be set when (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)"
#endif

#if(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON)
#warning "(_USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT == _ON) can only be set when (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)"
#endif
#endif

#if(_USB2_HOST_FILE_NAME_JUDGE_VERSION == _ON)
#if((_USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN == 0) || (_USB2_HOST_FILE_NAME_VERSION_CHAR_LEN == 0))
#warning "_USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN and _USB2_HOST_FILE_NAME_VERSION_CHAR_LEN should be set to non-zero value when (_USB2_HOST_FILE_NAME_JUDGE_VERSION == _ON)"
#endif
#endif

//--------------------------------------------------
// USB3 Check
//--------------------------------------------------
#if((_USB3_REPEATER_SUPPORT == _ON) && (_USB3_LOW_POWER_CONSUME_IN_POWER_SAVING == _ON))
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT == _OFF)
#warning "This Porject Do Not Support this Feature. _USB3_LOW_POWER_CONSUME_IN_POWER_SAVING Must Be OFF"
#endif
#endif

//--------------------------------------------------
// Audio Check
//--------------------------------------------------
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#if(_HW_AUDIO_TTS_EMBEDDED_SUPPORT == _OFF)
#warning "_AUDIO_TTS_SUPPORT_TYPE Should NOT Be _AUDIO_TTS_EMBEDDED_TYPE!!!"
#endif

#if(_AUDIO_TTS_DATA_SEGMENT_SIZE > 255)
#warning "_AUDIO_TTS_DATA_SEGMENT_SIZE Should Be less than 255!!!"
#endif

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)
#warning "_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT Should Be OFF, When _AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE"
#endif

#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_PS_AUDIO_INPUT != _PS_AUDIO_DP))
#if(_LINE_IN_SUPPORT == _OFF)
#warning "_LINE_IN_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_PS_AUDIO_INPUT != _PS_AUDIO_LINE_IN))
#if(_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON)
#warning "_PS_AUDIO_INPUT Should Be _PS_AUDIO_LINE_IN!!!"
#endif
#endif

#if((_EMBEDDED_DAC_SUPPORT == _OFF) || (_LINE_IN_SUPPORT == _OFF))
#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
#warning "_LINE_IN_AA_PATH_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#if((_DAC_SPEAKER_OUTPUT_SUPPORT == _OFF) && (_DAC_HP_OUTPUT_SUPPORT == _OFF))
#warning "_DAC_SPEAKER_OUTPUT_SUPPORT or _DAC_HP_OUTPUT_SUPPORT Should Be _ON!!!"
#endif
#endif // End of #if(_DAC_SPEAKER_OUTPUT_SUPPORT == _OFF) || (_DAC_HP_OUTPUT_SUPPORT == _OFF))

#if((_INTERNAL_AUDIO_TEST_SUPPORT != _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
#warning "_INTERNAL_AUDIO_TEST_SUPPORT must be '_ON' when use _FIX_AUDIO_OUTPUT!!!"
#endif // End of #if((_INTERNAL_AUDIO_TEST_SUPPORT != _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HW_HDMI_ARC_TX_EMBEDDED_EARC_IP_SUPPORT == _OFF)
#warning "_AUDIO_ARC_TX_SUPPORT_TYPE Should NOT Be _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP when _HW_HDMI_ARC_TX_EMBEDDED_EARC_IP_SUPPORT == _OFF!!!"
#endif

#if((_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT == _ON) && (_AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP == _ON))
#warning "_TMDS_HDMI20_SCDC_RR_CTS_SUPPORT Should Be _OFF when _AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP!!!"
#endif

#if((_HDMI20_SUPPORT == _OFF) && (_AUDIO_ARC_SUPPORT == _ON))
#warning "_HDMI20_SUPPORT Should Be _ON when _AUDIO_ARC_SUPPORT == _ON!!!"
#endif
#endif

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD)
#if(_HW_HDMI_ARC_TX_SPDIF_STRONG_DRIVING_PAD_SUPPORT == _OFF)
#warning "_AUDIO_ARC_TX_SUPPORT_TYPE Should NOT Be _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD when _HW_HDMI_ARC_TX_SPDIF_STRONG_DRIVING_PAD_SUPPORT == _OFF!!!"
#endif
#endif

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_IDENTIFY_GAME_SRC_SUPPORT == _OFF)
#warning "_HDMI_IDENTIFY_GAME_SRC_SUPPORT must be '_ON' when use _AUDIO_PARALLEL_MODE_SUPPORT!!!"
#endif

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _OFF)
#warning "_HDMI_AUDIO_SPREAD_PCODE_SUPPORT must be '_ON' when use _AUDIO_PARALLEL_MODE_SUPPORT!!!"
#endif
#endif

#if((_AUDIO_ARC_SUPPORT == _ON) && (_HDMI_CEC_SUPPORT == _OFF))
#warning "_HDMI_CEC_SUPPORT Should Be _ON when _AUDIO_ARC_SUPPORT == _ON!!!"
#endif

#if((_AUDIO_ARC_SUPPORT == _ON) && (_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST))
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _OFF)
#warning "_HDMI_CEC_KERNEL_HAL_SUPPORT Should Be _ON when _AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST!!!"
#endif
#endif

#if(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_0)
#if(!(_DAC_DITHER_FUNCTION_LEVEL <= _AUDIO_DAC_DITHER_LEVEL_3))
#warning "Audio DAC Gen0 No Support _AUDIO_DAC_DITHER_LEVEL_4 or above"
#endif
#endif

//--------------------------------------------------
// SPI Check
//--------------------------------------------------
#if(_SPI0_SUPPORT == _ON)
#if(_HW_SPI0_EXIST == _OFF)
#warning "_SPI0_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_SPI1_SUPPORT == _ON)
#if(_HW_SPI1_EXIST == _OFF)
#warning "_SPI1_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_SPI2_SUPPORT == _ON)
#if(_HW_SPI2_EXIST == _OFF)
#warning "_SPI2_SUPPORT Should Be _OFF!!!"
#endif
#endif

//--------------------------------------------------
// CPU32 IP Check
//--------------------------------------------------
#if(_HW_CPU32_KCPU_MEMORYMAP_ACCESS_DDR == _TRUE)
#if((_CPU32_KCPU_DDR_TEXT_BANKS != 32) &&\
    (_CPU32_KCPU_DDR_TEXT_BANKS != 64) &&\
    (_CPU32_KCPU_DDR_TEXT_BANKS != 128) &&\
    (_CPU32_KCPU_DDR_TEXT_BANKS != 256))
#warning "_CPU32_KCPU_DDR_TEXT_BANKS should be in 32, 64, 128 or 256 banks"
#endif
#endif

#if(_SCPU_SUPPORT == _ON)
#if(_HW_CPU32_SCPU_SUPPORT == _OFF)
#warning "_SCPU_SUPPORT Should be _OFF while _HW_CPU32_SCPU_SUPPORT is _OFF!!!"
#endif

#if((_CPU32_SCPU_DDR_TEXT_BANKS != 32) &&\
    (_CPU32_SCPU_DDR_TEXT_BANKS != 64) &&\
    (_CPU32_SCPU_DDR_TEXT_BANKS != 128) &&\
    (_CPU32_SCPU_DDR_TEXT_BANKS != 256))
#warning "_CPU32_SCPU_DDR_TEXT_BANKS should be in 32, 64, 128 or 256 banks"
#endif

#if((_DM_FUNCTION == _ON) && (_CPU32_SCPU_DDR_TEXT_BANKS != 32))
#warning "_CPU32_SCPU_DDR_TEXT_BANKS should be 32"
#endif

#endif


//-------------------------------------------------
// USB Redriver Define check
//-------------------------------------------------
#if(((_USB3_REDRIVER_UFP_PHY_SUPPORT == _ON) && (_USB3_REDRIVER_DFP_PHY_SUPPORT == _OFF)) ||\
    ((_USB3_REDRIVER_UFP_PHY_SUPPORT == _OFF) && (_USB3_REDRIVER_DFP_PHY_SUPPORT == _ON)))
#warning "_USB3_REDRIVER_UFP_PHY_SUPPORT and _USB3_REDRIVER_DFP_PHY_SUPPORT Must All Support ON!!!"
#endif

//-------------------------------------------------
// WildCard Excess check
//-------------------------------------------------
#if(_DP_AUX_RX_DPCD_WILDCARD_USED_COUNT > _HW_DP_AUX_RX_WILDCARD_SUPPORT)
#warning "AUX RX DPCD WILDCARD Usage Illegal, total requested wildcard number > hw wildcard number"
#endif

//-------------------------------------------------
// Remap Excess check for _FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT
//-------------------------------------------------
#if(_DP_AUX_RX_DPCD_REMAP_USED_COUNT > _HW_DP_AUX_RX_REMAP_SUPPORT)
#warning "AUX RX DPCD REMAP Usage Illegal, total requested remap number > hw remap number"
#endif

//-------------------------------------------------
// 32B Remap Excess check
//-------------------------------------------------
#if(_DP_AUX_RX_DPCD_REMAP_32B_USED_COUNT > _HW_DP_AUX_RX_REMAP_32B_SUPPORT)
#warning "AUX RX DPCD 32B REMAP Usage Illegal, total requested remap number > hw remap number"
#endif

//-------------------------------------------------
// 16B Remap Excess check
//-------------------------------------------------
#if(_DP_AUX_RX_DPCD_REMAP_16B_USED_COUNT > _HW_DP_AUX_RX_REMAP_16B_SUPPORT)
#warning "AUX RX DPCD 16B REMAP Usage Illegal, total requested remap number > hw remap number"
#endif

//-------------------------------------------------
// 8B Remap Excess check
//-------------------------------------------------
#if(_DP_AUX_RX_DPCD_REMAP_8B_USED_COUNT > _HW_DP_AUX_RX_REMAP_8B_SUPPORT)
#warning "AUX RX DPCD 8B REMAP Usage Illegal, total requested remap number > hw remap number"
#endif

//-------------------------------------------------
// OSD Define check
//-------------------------------------------------
#if(_HW_GOSD_SUPPORT == _OFF)
#if(_GOSD_SUPPORT == _ON)
#warning "_GOSD_SUPPORT Should Be _OFF"
#endif
#endif

#if(_GOSD_SUPPORT == _ON)
#if((_HW_CPU32_KCPU_MEMORYMAP_ACCESS_DDR == _FALSE) && ((_SCPU_SUPPORT == _OFF) || (_HW_CPU32_SCPU_MEMORYMAP_ACCESS_DDR == _FALSE)))
#warning "_SCPU_SUPPORT Support Be _ON while _GOSD_SUPPORT is _ON!!!"
#endif
#if(_GOSD_CONTINUOUS_STEP_MAX > 256)
#warning "_GOSD_CONTINUOUS_STEP_MAX Should Be less than 256!!!"
#endif
#if(_GOSD_DRAW_BW_CTRL_SUPPORT == _OFF)
#warning "_GOSD_DRAW_BW_CTRL_SUPPORT Should Be _ON while _GOSD_SUPPORT is _ON!!!"
#if(_GOSD_MEMORY_BW_DRAW != 0)
#warning "_GOSD_MEMORY_BW_DRAW Should Be 0 while _GOSD_DRAW_BW_CTRL_SUPPORT is _OFF!!!"
#endif
#else
#if((_GOSD_MEMORY_BW_DRAW < 1) || (_GOSD_MEMORY_BW_DRAW > 20))
#warning "_GOSD_MEMORY_BW_DRAW Should between 1 and 20!!!"
#endif
#endif
#endif

//-------------------------------------------------
// Dual Bank Support
//-------------------------------------------------
#if(_DUAL_BANK_SUPPORT == _ON)

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON while _DUAL_BANK_SUPPORT ON!!!"
#endif

#if(_DUAL_BANK_TYPE != _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)

#if(_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_BOOT)
#if(_DUAL_BANK_USER_I_FLAG_LOCATE_BANK > _DUAL_BANK_USER_FW_START_BANK)
#warning "_DUAL_BANK_USER_I_FLAG_LOCATE_BANK Should Be less than _DUAL_BANK_USER_FW_START_BANK while _DUAL_BANK_USER_FLAG_LOCATION_AREA is _DUAL_BANK_FLAG_LOCATION_IN_BOOT!!!"
#endif
#if(_DUAL_BANK_USER_II_FLAG_LOCATE_BANK > _DUAL_BANK_USER_FW_START_BANK)
#warning "_DUAL_BANK_USER_II_FLAG_LOCATE_BANK Should Be less than _DUAL_BANK_USER_FW_START_BANK while _DUAL_BANK_USER_FLAG_LOCATION_AREA is _DUAL_BANK_FLAG_LOCATION_IN_BOOT!!!"
#endif
#elif(_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_USER)
#if(_DUAL_BANK_USER_I_FLAG_LOCATE_BANK > _DUAL_BANK_USER_FW_CODE_SIZE)
#warning "_DUAL_BANK_USER_I_FLAG_LOCATE_BANK Should Be less than _DUAL_BANK_USER_FW_CODE_SIZE while _DUAL_BANK_USER_FLAG_LOCATION_AREA is _DUAL_BANK_FLAG_LOCATION_IN_USER!!!"
#endif
#if(_DUAL_BANK_USER_II_FLAG_LOCATE_BANK > _DUAL_BANK_USER_FW_CODE_SIZE)
#warning "_DUAL_BANK_USER_II_FLAG_LOCATE_BANK Should Be less than _DUAL_BANK_USER_FW_CODE_SIZE while _DUAL_BANK_USER_FLAG_LOCATION_AREA is _DUAL_BANK_FLAG_LOCATION_IN_USER!!!"
#endif
#endif // End of #if(_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_BOOT)

#else

#if(_DIGITAL_SIGNATURE_SUPPORT == _ON)
#warning "_DIGITAL_SIGNATURE_SUPPORT Should Be _OFF while _DUAL_BANK_TYPE is _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE!!!"
#endif

#if((_DUAL_BANK_FLASH_PARTITION_USER_FLAG_ADDRESS % 4) != 0)
#warning "_DUAL_BANK_FLASH_PARTITION_USER_FLAG_ADDRESS Should Be Multiple of 4!!!"
#endif

#endif // End of #if(_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)

#endif // End of #if(_DUAL_BANK_SUPPORT == _ON)


//-------------------------------------------------
// Dual Bank bundle version
//-------------------------------------------------
#if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)
#if(_DUAL_BANK_SUPPORT == _OFF)
#warning "_DUAL_BANK_BUNDLE_VERSION_SUPPORT Should Be uesed when  _DUAL_BANK_SUPPORT is _ON!!!"
#endif

#if(_DUAL_BANK_BUNDLE_VERSION_COUNT > 12)
#warning "_DUAL_BANK_BUNDLE_VERSION_COUNT Should Be less than 12!!!"
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_READ_FUNCTION_SUPPORT Should Be _ON while _DUAL_BANK_SUPPORT ON!!!"
#endif

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON while _DUAL_BANK_SUPPORT ON!!!"
#endif
#endif

//-------------------------------------------------
// ISP FW Project ID Check
//-------------------------------------------------
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
#if(_DDCCI0_RXBUF_LENGTH < 18)
#warning "_DDCCI0_RXBUF_LENGTH Should Be >= 18 while _ISP_FW_CHECK_PROJECT_ID_SUPPORT ON!!!!!!"
#endif

#if(_DDCCI_RXBUF_LENGTH < 18)
#warning "_DDCCI_RXBUF_LENGTH Should Be >= 18 while _ISP_FW_CHECK_PROJECT_ID_SUPPORT ON!!!!!!"
#endif

#if(_DDCCI_TXBUF_LENGTH < 18)
#warning "_DDCCI_TXBUF_LENGTH Should Be >= 18 while _ISP_FW_CHECK_PROJECT_ID_SUPPORT ON!!!"
#endif
#endif

//--------------------------------------------------
// Fw  Update FW Check
//--------------------------------------------------
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

#if(_FLASH_WRITE_FUNCTION_SUPPORT == _OFF)
#warning "FW Update FW _FLASH_WRITE_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_FLASH_READ_FUNCTION_SUPPORT == _OFF)
#warning "FW Update FW _FLASH_READ_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if(_DUAL_BANK_SUPPORT == _OFF)
#warning "Fw Update FW _DUAL_BANK_SUPPORT Should Be _ON!!!"
#endif

#if((_DUAL_BANK_TYPE != _DUAL_BANK_DIFF_BANK) && (_DUAL_BANK_TYPE != _DUAL_BANK_COPY_BANK))
#warning "FW Update FW _DUAL_BANK_TYPE Should Be _DUAL_BANK_DIFF_BANK or _DUAL_BANK_COPY_BANK!!!"
#endif

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _OFF)
#warning "_DDCCI_AUTO_SWITCH_SUPPORT Should Be _ON!!!"
#endif

#if((_HW_DDCCI1_EXIST == _OFF) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
#warning "_FW_UPDATE_DDCCI_SEL Should Not Be _FW_UPDATE_SEL_DDCCI1 When _HW_DDCCI1_EXIST is _OFF!!!"
#endif

#if((_HW_DDCCI2_EXIST == _OFF) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
#warning "_FW_UPDATE_DDCCI_SEL Should Not Be _FW_UPDATE_SEL_DDCCI2 When _HW_DDCCI2_EXIST is _OFF!!!"
#endif

#if((_HW_DDCCI3_EXIST == _OFF) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
#warning "_FW_UPDATE_DDCCI_SEL Should Not Be _FW_UPDATE_SEL_DDCCI3 When _HW_DDCCI3_EXIST is _OFF!!!"
#endif

#if((_HW_DDCCI4_EXIST == _OFF) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4))
#warning "_FW_UPDATE_DDCCI_SEL Should Not Be _FW_UPDATE_SEL_DDCCI4 When _HW_DDCCI4_EXIST is _OFF!!!"
#endif

#if((_FW_UPDATE_FOREGROUND_SUPPORT == _ON) && (_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _OFF))
#warning "_ISP_FW_CHECK_PROJECT_ID_SUPPORT Should Be _ON When _FW_UPDATE_FOREGROUND_SUPPORT is _ON!!!"
#endif

#if((_FW_UPDATE_CLAC_CRC_TYPE == _FW_UPDATE_HW_CLAC_CRC) && (_DIGITAL_SIGNATURE_SUPPORT == _ON))
#warning "_FW_UPDATE_CLAC_CRC_TYPE Should Be _FW_UPDATE_FW_CLAC_CRC When _DIGITAL_SIGNATURE_SUPPORT is _ON!!!"
#endif

#if((_HW_ISP_SPEED_UP_SUPPORT == _OFF) && (_FW_UPDATE_FW_SPEED_UP_SUPPORT == _ON))
#warning "_FW_UPDATE_FW_SPEED_UP_SUPPORT Should Be _OFF When _HW_ISP_SPEED_UP_SUPPORT is _ON!!!"
#endif

#if((_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_SUPPORT == _ON))
#warning "_FW_ISP_SPEED_UP_PROCESS_SUPPORT Should Be _OFF When _DIGITAL_SIGNATURE_SUPPORT is _ON!!!"
#endif

#endif

//--------------------------------------------------
// System Source Background Detection Define Check
//--------------------------------------------------
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)

#if(_VGA_SUPPORT == _ON)
#warning "_SOURCE_BACKGROUND_DETECT_SUPPORT Should Not Be _ON while VGA Support!!!"
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
#warning "_SOURCE_BACKGROUND_DETECT_SUPPORT Should Not Be _ON while _SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE !!!"
#endif

#endif

//-------------------------------------------------
// Flash Clock Check
//-------------------------------------------------
#if((_FLASH_CLK_SPEED == _FLASH_LOW_SPEED) && (_DP_SUPPORT == _ON))
#warning "_FLASH_LOW_SPEED Is Unsafe for DP Application!!!"
#endif

//--------------------------------------------------
// Flash 4byte Check
//--------------------------------------------------
#if((_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON) && (_HW_FLASH_4BYTE_MODE_SUPPORT == _OFF))
#warning "_FLASH_4BYTE_MODE_FUNCTION_SUPPORT Should Not Be _ON when _HW_FLASH_4BYTE_MODE_SUPPORT == OFF !!!"
#endif

//--------------------------------------------------
// DP HPD Implementation Mode Check
//--------------------------------------------------
#if(((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_DP_MST_SUPPORT == _ON)) && (_DP_LONG_HPD_USER_MODE == _DP_LONG_HPD_DELAY_MODE))
#warning "_DP_LONG_HPD_USER_MODE Should be _DP_LONG_HPD_TIMEREVENT_MODE!!!!!"
#endif

#endif // End of #ifndef __PROJECT_CONFIG_CHECK_H__
