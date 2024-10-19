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
// ID Code      : Project_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_OPTION_H__
#define __PROJECT_OPTION_H__

//--------------------------------------------------
// QC Option
//--------------------------------------------------
#include <QC/QC_Option.h>

//--------------------------------------------------
// AT Option
//--------------------------------------------------
#include <AT/AT_Option.h>

//--------------------------------------------------
// PWM Option
//--------------------------------------------------
#if((_HW_MCU_PWM_BIT_SUPPORT == _PWM_8BIT) || (_HW_MCU_PWM_BIT_SUPPORT == _PWM_12BIT))

#define MCU_ADJUST_8BIT_PWM_DUTY(x, y)                          {\
                                                                    (((x) == _PWM0) ? (MCU_FF4A_PWM0H_DUT = (y)) :\
                                                                     (((x) == _PWM1) ? (MCU_FF4B_PWM1H_DUT = (y)) :\
                                                                      (((x) == _PWM2) ? (MCU_FF4D_PWM2H_DUT = (y)) :\
                                                                       (((x) == _PWM3) ? (MCU_FF4E_PWM3H_DUT = (y)) :\
                                                                        (((x) == _PWM4) ? (MCU_FF50_PWM4H_DUT = (y)) :\
                                                                         (MCU_FF51_PWM5H_DUT = (y)))))));\
                                                                }


#define MCU_GET_8BIT_PWM_DUTY(x)                                (((x) == _PWM0) ? MCU_FF4A_PWM0H_DUT :\
                                                                  (((x) == _PWM1) ? MCU_FF4B_PWM1H_DUT :\
                                                                    (((x) == _PWM2) ? MCU_FF4D_PWM2H_DUT :\
                                                                     (((x) == _PWM3) ? MCU_FF4E_PWM3H_DUT :\
                                                                      (((x) == _PWM4) ? MCU_FF50_PWM4H_DUT :\
                                                                       MCU_FF51_PWM5H_DUT)))))

#endif

#if(_HW_MCU_PWM_BIT_SUPPORT == _PWM_12BIT)

#define MCU_ADJUST_12BIT_PWM_DUTY(x, y)                         {\
                                                                    (((x) == _PWM0) ? (MCU_FF4C_PWM01L_DUT = ((((BYTE)(y)) & 0x0F) | (MCU_FF4C_PWM01L_DUT & 0xF0)), MCU_FF4A_PWM0H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                     (((x) == _PWM1) ? (MCU_FF4C_PWM01L_DUT = ((((BYTE)((y) << 4)) & 0xF0) | (MCU_FF4C_PWM01L_DUT & 0x0F)), MCU_FF4B_PWM1H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                      (((x) == _PWM2) ? (MCU_FF4F_PWM23L_DUT = ((((BYTE)(y)) & 0x0F) | (MCU_FF4F_PWM23L_DUT & 0xF0)), MCU_FF4D_PWM2H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                       (((x) == _PWM3) ? (MCU_FF4F_PWM23L_DUT = ((((BYTE)((y) << 4)) & 0xF0) | (MCU_FF4F_PWM23L_DUT & 0x0F)), MCU_FF4E_PWM3H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                        (((x) == _PWM4) ? (MCU_FF52_PWM45L_DUT = ((((BYTE)(y)) & 0x0F) | (MCU_FF52_PWM45L_DUT & 0xF0)), MCU_FF50_PWM4H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7) :\
                                                                         (MCU_FF52_PWM45L_DUT = ((((BYTE)((y) << 4)) & 0xF0) | (MCU_FF52_PWM45L_DUT & 0x0F)), MCU_FF51_PWM5H_DUT = (BYTE)((y) >> 4), MCU_FF46_PWML |= _BIT7))))));\
                                                                }


#define MCU_GET_12BIT_PWM_DUTY(x)                               (((x) == _PWM0) ? (WORD)((((WORD)(MCU_FF4A_PWM0H_DUT)) << 4) | (((WORD)(MCU_FF4C_PWM01L_DUT)) & 0x000F)) :\
                                                                 (((x) == _PWM1) ? (WORD)((((WORD)(MCU_FF4B_PWM1H_DUT)) << 4) | ((((WORD)(MCU_FF4C_PWM01L_DUT)) & 0x00F0) >> 4)) :\
                                                                  (((x) == _PWM2) ? (WORD)((((WORD)(MCU_FF4D_PWM2H_DUT)) << 4) | (((WORD)(MCU_FF4F_PWM23L_DUT)) & 0x000F)) :\
                                                                   (((x) == _PWM3) ? (WORD)((((WORD)(MCU_FF4E_PWM3H_DUT)) << 4) | ((((WORD)(MCU_FF4F_PWM23L_DUT)) & 0x00F0) >> 4)) :\
                                                                    (((x) == _PWM4) ? (WORD)((((WORD)(MCU_FF50_PWM4H_DUT)) << 4) | (((WORD)(MCU_FF52_PWM45L_DUT)) & 0x000F)) :\
                                                                     (WORD)((((WORD)(MCU_FF51_PWM5H_DUT)) << 4) | ((((WORD)(MCU_FF52_PWM45L_DUT)) & 0x00F0) >> 4)))))))
#endif

//-------------------------------------------------
// Multi-Display Option
//-------------------------------------------------
#define _2P_DISPLAY_SUPPORT                                     ((_2P_PIP_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_2P_PBP_LR_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_2P_PBP_TB_DISPLAY_SUPPORT == _ON))


#define _3P_DISPLAY_SUPPORT                                     ((_3P_FLAG_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_SKEW_LR_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_SKEW_TB_DISPLAY_SUPPORT == _ON))


#define _2P_FRAME_SYNC_SUPPORT                                  ((_PIP_FRAME_SYNC_SUPPORT == _ON) ||\
                                                                 (_PBP_LR_FRAME_SYNC_SUPPORT == _ON) ||\
                                                                 (_EAGLE_SIGHT_SUPPORT == _ON))


#define _TB_DISPLAY_MODE_SUPPORT                                ((_2P_PBP_TB_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_SKEW_TB_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_4P_DISPLAY_SUPPORT == _ON))

#if(_4P_DISPLAY_SUPPORT == _ON)
#define _MULTI_DISPLAY_MAX                                      4
#elif(_3P_DISPLAY_SUPPORT == _ON)
#define _MULTI_DISPLAY_MAX                                      3
#elif(_2P_DISPLAY_SUPPORT == _ON)
#define _MULTI_DISPLAY_MAX                                      2
#else
#define _MULTI_DISPLAY_MAX                                      1
#endif

#define _M_DOMAIN_S1_S2_PATH_SUPPORT                            ((_2P_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_4P_DISPLAY_SUPPORT == _ON) ||\
                                                                 (GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH))

#define _M_DOMAIN_S3_S4_PATH_SUPPORT                            ((_2P_PIP_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_EAGLE_SIGHT_SUPPORT == _ON) ||\
                                                                 (_2P_PBP_LR_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_DISPLAY_SUPPORT == _ON))

#define _D_DOMAIN_S1_S2_PATH_SUPPORT                            ((_2P_PIP_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_EAGLE_SIGHT_SUPPORT == _ON) ||\
                                                                 (_2P_PBP_LR_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_3P_DISPLAY_SUPPORT == _ON) ||\
                                                                 (_4P_DISPLAY_SUPPORT == _ON))

#define _D_DOMAIN_M3_M4_PATH_SUPPORT                            (GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)

//-------------------------------------------------
// Multi-Display DSC Auto Option
//-------------------------------------------------
#define _DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT                  (((_2P_DISPLAY_SUPPORT == _ON) ||\
                                                                  (_3P_DISPLAY_SUPPORT == _ON) ||\
                                                                  (_4P_DISPLAY_SUPPORT == _ON)) &&\
                                                                 (_DSC_MAC_MAX_COUNT >= _MULTI_DISPLAY_MAX))

//--------------------------------------------------
// OverScan Option
//--------------------------------------------------
#define _OVERSCAN_SUPPORT                                       ((_OVERSCAN_VGA_SUPPORT == _ON) ||\
                                                                 (_OVERSCAN_DVI_SUPPORT == _ON) ||\
                                                                 (_OVERSCAN_HDMI_SUPPORT == _ON) ||\
                                                                 (_OVERSCAN_DP_SUPPORT == _ON))

//--------------------------------------------------
// Dos mode FRC Option
//--------------------------------------------------
#define _FRC_DOS_MODE_ONLY_SUPPORT                              ((_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM) &&\
                                                                 (_M_DOMAIN_IMG_CMP_SUPPORT == _OFF) &&\
                                                                 (_FRC_SUPPORT == _ON))


//--------------------------------------------------
// Space check Option
//--------------------------------------------------
#define _CHECK_ENOUGH_SPACE_SUPPORT                             ((_MEMORY_TYPE_CONFIG == _MEMORY_DDR1) ||\
                                                                 (_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM))

//-------------------------------------------------
// Mdomain Frame Sync Active Info Option
//-------------------------------------------------
#define _M_DOMAIN_FRAMESYNC_ACTIVE_TIMING_INFO_SUPPORT          ((_HDMI21_ALLM_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT_LOW_LATENCY == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))

//-------------------------------------------------
// VRR Option
//-------------------------------------------------
#define _HDMI21_VRR_SUPPORT                                     ((_HDMI21_GAMING_VRR_SUPPORT == _ON) ||\
                                                                 (_HDMI21_QMS_VRR_SUPPORT == _ON))

//-------------------------------------------------
// DRR Option
//-------------------------------------------------
#define _DRR_SUPPORT                                            ((_FREESYNC_SUPPORT == _ON) ||\
                                                                 (_DP_ADAPTIVESYNC_SUPPORT == _ON) ||\
                                                                 (_HDMI21_VRR_SUPPORT == _ON))

//-------------------------------------------------
// FreeSync Option
//-------------------------------------------------
#define _FREESYNC_SUPPORT                                       ((_DP_FREESYNC_SUPPORT == _ON) ||\
                                                                 (_HDMI_FREESYNC_SUPPORT == _ON))

//-------------------------------------------------
// FreeSync II Option
//-------------------------------------------------
#define _FREESYNC_II_SUPPORT                                    ((_DP_FREESYNC_II_SUPPORT == _ON) ||\
                                                                 (_HDMI_FREESYNC_II_SUPPORT == _ON))

//-------------------------------------------------
// AdaptiveSync Option
//-------------------------------------------------
#define _ADAPTIVESYNC_SUPPORT                                   (_DP_ADAPTIVESYNC_SUPPORT == _ON)


//-------------------------------------------------
// Panel Replay Option
//-------------------------------------------------
#define _PR_MODE_SUPPORT                                        (_DP_PR_MODE_SUPPORT == _ON)


//-------------------------------------------------
// HDR10 Option
//-------------------------------------------------
#define _HDR10_SUPPORT                                          ((_DP_HDR10_SUPPORT == _ON) ||\
                                                                 (_HDMI_HDR10_SUPPORT == _ON))

//-------------------------------------------------
// HLG Option
//-------------------------------------------------
#define _HLG_SUPPORT                                            ((_DP_HLG_SUPPORT == _ON) ||\
                                                                 (_HDMI_HLG_SUPPORT == _ON))

//-------------------------------------------------
// Advanced HDR10 Option
//-------------------------------------------------
#define _ADVANCED_HDR10_SUPPORT                                 ((_HDMI_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE) ||\
                                                                 (_DP_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE))

#define _ADVANCED_HDR10_DHDR_SUPPORT                            ((_HDMI_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE) ||\
                                                                 (_DP_ADVANCED_HDR10_SUPPORT_MODE == _ADVANCED_HDR10_VSIF_AND_DHDR_MODE))

// ------------------------------------------------
// Dx DSC Option
// ------------------------------------------------
#define _DSC_DECODER_SUPPORT                                    ((_DP_RX_DSC_DECODER_SUPPORT == _ON) ||\
                                                                 (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON))

//-------------------------------------------------
// BAKCLIGHT DIMMING Option
//-------------------------------------------------
#define _BACKLIGHT_DIMMING_SUPPORT                              ((_LOCAL_DIMMING_FUNCTION == _ON) ||\
                                                                 (_GLOBAL_DIMMING_FUNCTION == _ON))

//-------------------------------------------------
// Local Dimming Global Boost Option
//-------------------------------------------------
#define _LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT                     ((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) ||\
                                                                 (_LOCAL_DIMMING_FREESYNC_II_BOOST_SUPPORT == _ON) ||\
                                                                 (_LOCAL_DIMMING_USER_GLOBAL_BOOST_SUPPORT == _ON))

//-------------------------------------------------
// Local Dimming Adim Modify Option
//-------------------------------------------------
#define _LOCAL_DIMMING_ADIM_MODIFY_SUPPORT                      ((_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON) ||\
                                                                 (_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) ||\
                                                                 (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))

//-------------------------------------------------
// PWM2SPI MANAUL APPLY MODE
//-------------------------------------------------
#define _LOCAL_DIMMING_PWM2SPI_MANUAL_MODE                      (((_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI) && ((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON))) ||\
                                                                 (_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _ON) || (_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX == _ON))

//-------------------------------------------------
// Local Dimming UP Region Support
//-------------------------------------------------
#define _LOCAL_DIMMING_UP_REGION_SUPPORT                        ((_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON) && (_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT))

//-------------------------------------------------
// Local Dimming Extro Info Enable
//-------------------------------------------------
#if(_HW_LOCAL_DIMMING_EXTROINFO_SUPPORT == _ON)
#define _LOCAL_DIMMING_USING_EXTRO_INFO_SUPPORT_ENABLE          (_LOCAL_DIMMING_USING_EXTRO_INFO)
#else
#define _LOCAL_DIMMING_USING_EXTRO_INFO_SUPPORT_ENABLE          (_OFF)
#endif

//-------------------------------------------------
// SPI BAKCLIGHT DIMMING Option
//-------------------------------------------------
#define _SPI_BACKLIGHT_DIMMING_SUPPORT                          ((_BACKLIGHT_DIMMING_SUPPORT == _ON) &&\
                                                                 (((_SPI0_SUPPORT == _ON) && (_SPI0_SETTING_SOURCE == _SPI_SETTING_BY_PANEL)) ||\
                                                                  ((_SPI1_SUPPORT == _ON) && (_SPI1_SETTING_SOURCE == _SPI_SETTING_BY_PANEL)) ||\
                                                                  ((_SPI2_SUPPORT == _ON) && (_SPI2_SETTING_SOURCE == _SPI_SETTING_BY_PANEL))))

//-------------------------------------------------
// Global Dimming OCC Tool
//-------------------------------------------------
#define _GLOBAL_DIMMING_OCC_TOOL_SUPPORT                        ((_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON) ||\
                                                                 (_GLOBAL_DIMMING_DARK_MODE_SUPPORT == _ON) ||\
                                                                 (_GLOBAL_DIMMING_HDR_FINE_TUNE_MODE_SUPPORT == _ON))

//-------------------------------------------------
// SPI BOOST FORMAT Option
//-------------------------------------------------
#define _SPI_BOOST_FORMAT_SUPPORT                               (((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) ||\
                                                                 (_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)) &&\
                                                                 (_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF))

//-------------------------------------------------
// DP ULTRA HDR Option
//-------------------------------------------------
#define _DP_ULTRA_HDR_SUPPORT                                   ((_DP_HDR10_SUPPORT == _ON) ||\
                                                                 (_DP_FREESYNC_II_SUPPORT == _ON) ||\
                                                                 (_DP_HLG_SUPPORT == _ON))

//-------------------------------------------------
// HDMI ULTRA HDR Option
//-------------------------------------------------
#define _HDMI_ULTRA_HDR_SUPPORT                                 ((_HDMI_HDR10_SUPPORT == _ON) ||\
                                                                 (_HDMI_FREESYNC_II_SUPPORT == _ON) ||\
                                                                 (_HDMI_HLG_SUPPORT == _ON))

//-------------------------------------------------
// ULTRA HDR Option
//-------------------------------------------------
#define _ULTRA_HDR_SUPPORT                                      ((_HDR10_SUPPORT == _ON) ||\
                                                                 (_FREESYNC_II_SUPPORT == _ON) ||\
                                                                 (_HLG_SUPPORT == _ON))

//-------------------------------------------------
// Highlight Window for OD Option
//-------------------------------------------------
#define _HIGHLIGHT_WINDOW_SUPPORT_FOR_OD                        ((_OD_FUNCTION == _ON) &&\
                                                                 (_ASPECT_ORIGINAL_MODE_SUPPORT == _ON))

//-------------------------------------------------
// Scale Up
//-------------------------------------------------
#define _VSU_3L_SUPPORT                                         _OFF
#define _VSU_96TAPS_SUPPORT                                     _OFF

//-------------------------------------------------
// Hue and Saturation Option
//-------------------------------------------------
#define _SATURATION_CENTER                                      ((_SATURATION_MAX + _SATURATION_MIN) / 2)
#define _HUE_CENTER                                             ((_HUE_MAX + _HUE_MIN) / 2)

//-------------------------------------------------
// OGC and OCC (On-Line Calibration) Option
//-------------------------------------------------
#if((_HW_OUTPUT_GAMMA_TABLE_TYPE == _OUTPUT_GAMMA_GEN_0) &&\
    (_HW_INPUT_GAMMA_TABLE_TYPE == _INPUT_GAMMA_GEN_0))
#define _OGC_GEN_TYPE                                           _OGC_GEN_0
#elif((_HW_OUTPUT_GAMMA_TABLE_TYPE == _OUTPUT_GAMMA_GEN_1) &&\
      ((_HW_INPUT_GAMMA_TABLE_TYPE == _INPUT_GAMMA_GEN_1) ||\
       (_HW_INPUT_GAMMA_TABLE_TYPE == _INPUT_GAMMA_GEN_2)))
#define _OGC_GEN_TYPE                                           _OGC_GEN_1
#else
#define _OGC_GEN_TYPE                                           _GEN_NONE
#endif

#if(_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE)
#define _OCC_GAMMA_GEN_TYPE                                     _OCC_GAMMA_GEN_1
#else
#define _OCC_GAMMA_GEN_TYPE                                     _OCC_GAMMA_GEN_0
#endif

#define _UNIFORMITY_TOTAL_SET                                   ((_UNIFORMITY_1ST_TABLE_LEVEL != _UNIFORMITY_NONE) +\
                                                                 (_UNIFORMITY_2ND_TABLE_LEVEL != _UNIFORMITY_NONE) +\
                                                                 (_UNIFORMITY_3RD_TABLE_LEVEL != _UNIFORMITY_NONE) +\
                                                                 (_UNIFORMITY_4TH_TABLE_LEVEL != _UNIFORMITY_NONE) +\
                                                                 (_UNIFORMITY_5TH_TABLE_LEVEL != _UNIFORMITY_NONE) +\
                                                                 (_UNIFORMITY_6TH_TABLE_LEVEL != _UNIFORMITY_NONE) +\
                                                                 (_UNIFORMITY_7TH_TABLE_LEVEL != _UNIFORMITY_NONE) +\
                                                                 (_UNIFORMITY_8TH_TABLE_LEVEL != _UNIFORMITY_NONE) +\
                                                                 (_UNIFORMITY_9TH_TABLE_LEVEL != _UNIFORMITY_NONE))

//--------------------------------------------------
// Color IP Option
//--------------------------------------------------
#define _COLOR_IP_3DDI                                          (_3DDI_FUNCTION == _ON)

#define _COLOR_IP_420_SUPPORT                                   ((_HDMI20_SUPPORT == _ON) || (_DP_SUPPORT == _ON))

#define _COLOR_IP_FC_EAGLESIGHT_SUPPORT                         ((_EAGLE_SIGHT_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_EAGLE_SIGHT_SUPPORT == _ON))

#define _COLOR_IP_COLOR_CONVERT                                 ((_ULTRA_VIVID_FUNCTION == _ON) ||\
                                                                 (_COLOR_FORMAT_CONVERT_FUNCTION == _ON) ||\
                                                                 (_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) ||\
                                                                 (_YCC_QUANTIZATION_RANGE_FUNCTION == _ON) ||\
                                                                 (_M_DOMAIN_FORCE_YUV_FORMAT == _ON) ||\
                                                                 (_LOCAL_CONTRAST_FUNCTION == _ON) ||\
                                                                 (_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON) ||\
                                                                 (_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON) ||\
                                                                 (_M_DOMAIN_IMG_CMP_SUPPORT == _ON) ||\
                                                                 (_3DDI_FUNCTION == _ON) ||\
                                                                 (_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON) ||\
                                                                 (_DM_FUNCTION == _ON))

#define _COLOR_IP_I_DITHER                                      (_I_DITHER_FUNCTION == _ON)

#define _COLOR_IP_HL_WIN                                        _ON

#define _COLOR_IP_BORDER_WIN                                    ((_BORDER_WINDOW_FUNCTION == _ON) ||\
                                                                 (_EAGLE_SIGHT_SUPPORT == _ON))

#define _COLOR_IP_LSR                                           ((_ULTRA_VIVID_FUNCTION == _ON) ||\
                                                                 (_IP_LSR_ON == _ON))

#define _COLOR_IP_DSHP                                          (((_ULTRA_VIVID_FUNCTION_WITH_DSHP == _ON) &&\
                                                                  (_ULTRA_VIVID_FUNCTION == _ON)) ||\
                                                                 (_IP_DSHP_ON == _ON))

#define _COLOR_IP_IDLTI                                         (((_ULTRA_VIVID_FUNCTION_WITH_IDLTI == _ON) &&\
                                                                  (_ULTRA_VIVID_FUNCTION == _ON)) ||\
                                                                 (_IP_IDLTI_ON == _ON))

#define _COLOR_IP_SHARPNESS                                     (_SHARPNESS_FUNCTION == _ON)

#define _COLOR_IP_LOCAL_CONTRAST_HISTOGRAM                      ((_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _ON) ||\
                                                                 (_IP_LOCAL_CONTRAST_HISTOGRAM_ON == _ON))

#define _COLOR_IP_LOCAL_CONTRAST                                ((_LOCAL_CONTRAST_FUNCTION == _ON) ||\
                                                                 (_IP_LOCAL_CONTRAST_ON == _ON) ||\
                                                                 (_SDR_PLUS_FUNCTION == _ON) ||\
                                                                 (_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON) ||\
                                                                 (_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION) ||\
                                                                 ((_LOCAL_DIMMING_FUNCTION == _ON) &&\
                                                                  (_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)))

#define _COLOR_IP_DCR                                           ((_DCR_FUNCTION == _ON) ||\
                                                                 (_GLOBAL_DIMMING_FUNCTION == _ON) ||\
                                                                 (_LOCAL_DIMMING_FUNCTION == _ON))

#define _COLOR_IP_DCC_HISTOGRAM                                 ((_DCC_HISTOGRM_INFO_FUNCTION == _ON) ||\
                                                                 (_ULTRA_HDR_SUPPORT == _ON) ||\
                                                                 (_IP_DCC_HISTOGRAM_ON == _ON))

#define _COLOR_IP_DCC                                           ((_DCC_FUNCTION == _ON) ||\
                                                                 ((_HDR10_LIGHT_ENHANCE_FUNCTION == _ON) &&\
                                                                  (_HW_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)) ||\
                                                                 (_SDR_TO_HDR_FUNCTION == _ON) ||\
                                                                 (_IP_DCC_ON == _ON))

#define _COLOR_IP_ICM                                           ((_ICM_FUNCTION == _ON) ||\
                                                                 (_SCM_SUPPORT == _ON) ||\
                                                                 (_SIX_COLOR_SUPPORT == _ON) ||\
                                                                 (_HDR10_COLOR_ENHANCE_FUNCTION == _ON) ||\
                                                                 (_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON) ||\
                                                                 (_SDR_TO_HDR_FUNCTION == _ON) ||\
                                                                 (_IP_ICM_ON == _ON))

#define _COLOR_IP_CONTRAST                                      ((_CONTRAST_FUNCTION == _ON) ||\
                                                                 (_IP_CONTRAST_ON == _ON))

#define _COLOR_IP_BRIGHTNESS                                    ((_BRIGHTNESS_FUNCTION == _ON) ||\
                                                                 (_IP_BRIGHTNESS_ON == _ON))

#define _COLOR_IP_IAPS                                          (_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)

#define _COLOR_IP_RGB_3D_GAMMA                                  ((_RGB_3D_GAMMA_FUNCTION == _ON) ||\
                                                                 (_ADVANCED_HDR10_SUPPORT == _ON))

#define _COLOR_IP_I_GAMMA                                       ((_PCM_FUNCTION == _ON) ||\
                                                                 (_BACKLIGHT_DIMMING_SUPPORT == _ON) ||\
                                                                 (_HDR10_SUPPORT == _ON) ||\
                                                                 (_HLG_SUPPORT == _ON) ||\
                                                                 (_FREESYNC_II_SUPPORT == _ON) ||\
                                                                 (_SDR_TO_HDR_FUNCTION == _ON) ||\
                                                                 (_IP_INPUT_GAMMA_ON == _ON))


#define _COLOR_IP_YMAPPING                                      ((_HLG_SUPPORT == _ON) ||\
                                                                 (_ADVANCED_HDR10_SUPPORT == _ON) ||\
                                                                 (_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON))

#define _COLOR_IP_SRGB                                          ((_GLOBAL_HUE_SATURATION_FUNCTION == _ON) ||\
                                                                 (_PCM_FUNCTION == _ON) ||\
                                                                 (_BACKLIGHT_DIMMING_SUPPORT == _ON) ||\
                                                                 (_HDR10_SUPPORT == _ON) ||\
                                                                 (_HLG_SUPPORT == _ON) ||\
                                                                 (_FREESYNC_II_SUPPORT == _ON) ||\
                                                                 (_SDR_TO_HDR_FUNCTION == _ON) ||\
                                                                 (_IP_SRGB_ON == _ON))

#define _COLOR_IP_LOCAL_DIMMING                                 (_LOCAL_DIMMING_FUNCTION == _ON)

#define _COLOR_IP_UNIFORMITY                                    ((_UNIFORMITY_FUNCTION == _ON) ||\
                                                                 (_DYNAMIC_LOWBLUE_FUNCTION == _ON) ||\
                                                                 (_IP_UNIFORMITY_ON == _ON))

#define _COLOR_IP_P_GAMMA                                       (_UNIFORMITY_PLUS_FUNCTION == _ON)

#define _COLOR_IP_O_GAMMA                                       ((_GAMMA_FUNCTION == _ON) ||\
                                                                 (_PCM_FUNCTION == _ON) ||\
                                                                 (_BACKLIGHT_DIMMING_SUPPORT == _ON) ||\
                                                                 (_HDR10_SUPPORT == _ON) ||\
                                                                 (_HLG_SUPPORT == _ON) ||\
                                                                 (_FREESYNC_II_SUPPORT == _ON) ||\
                                                                 (_SDR_TO_HDR_FUNCTION == _ON) ||\
                                                                 (_IP_OUTPUT_GAMMA_ON == _ON))

#define _COLOR_IP_D_DITHER                                      (_D_DITHER_FUNCTION == _ON)

#define _COLOR_IP_OD                                            (_OD_FUNCTION == _ON)

#define _COLOR_IP_DM                                            (_DM_FUNCTION == _ON)

#define _COLOR_IP_MRCM                                          ((_MRCM_SUPPORT == _ON) ||\
                                                                 (_DYNAMIC_LOWBLUE_FUNCTION == _ON))

#define _COLOR_IP_ANTI_ALIASING                                 (_ANTI_ALIASING_FUNCTION == _ON)

//--------------------------------------------------
// Color Option
//--------------------------------------------------
#define _COLOR_OUTPUT_POST_GAMMA_BYPASS_SUPPORT                 (_UNIFORMITY_PLUS_FUNCTION == _ON)

//--------------------------------------------------
// Motion Blur Reduction Option
//--------------------------------------------------
#define _MOTION_BLUR_REDUCTION_LCD_SUPPORT                      ((_MOTION_BLUR_REDUCTION_SUPPORT == _ON) &&\
                                                                 (_MOTION_BLUR_PANEL_PIXEL_TYPE == _MOTION_BLUR_PANEL_PIXEL_LCD))
#define _MOTION_BLUR_REDUCTION_OLED_SUPPORT                     ((_MOTION_BLUR_REDUCTION_SUPPORT == _ON) &&\
                                                                 (_MOTION_BLUR_PANEL_PIXEL_TYPE == _MOTION_BLUR_PANEL_PIXEL_OLED))

//--------------------------------------------------
// LocalContrast Option
//--------------------------------------------------
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
#if(_LOCAL_DIMMING_FUNCTION == _ON)
#define _LOCAL_CONTRAST_READYAVG_HBLKNUM                        _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL
#define _LOCAL_CONTRAST_READYAVG_VBLKNUM                        _LOCAL_DIMMING_PANEL_REGION_VERTICAL
#else
#define _LOCAL_CONTRAST_READYAVG_HBLKNUM                        (24)
#define _LOCAL_CONTRAST_READYAVG_VBLKNUM                        (20)
#endif
#define _LOCAL_CONTRAST_MAX_REGION_COUT                         (2)
#define _LOCAL_CONTRAST_READYAVG_TOTAL_BLKNUM                   (_LOCAL_CONTRAST_READYAVG_HBLKNUM * _LOCAL_CONTRAST_READYAVG_VBLKNUM)
#define _LOCAL_CONTRAST_READYAVG_KCPU_BLKNUM_LIMIT              (576)
#endif

//-------------------------------------------------
// EDID Address Option
//-------------------------------------------------
#define _EDID_A0_ADDRESS_EEPROM                                 (_EDID_ADDRESS_EEPROM)
#define _EDID_D0_ADDRESS_EEPROM                                 (_EDID_A0_ADDRESS_EEPROM + ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _A0_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D1_ADDRESS_EEPROM                                 (_EDID_D0_ADDRESS_EEPROM + ((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D0_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D2_ADDRESS_EEPROM                                 (_EDID_D1_ADDRESS_EEPROM + ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D1_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D3_ADDRESS_EEPROM                                 (_EDID_D2_ADDRESS_EEPROM + ((_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D2_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D4_ADDRESS_EEPROM                                 (_EDID_D3_ADDRESS_EEPROM + ((_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D3_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D5_ADDRESS_EEPROM                                 (_EDID_D4_ADDRESS_EEPROM + ((_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D4_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D6_ADDRESS_EEPROM                                 (_EDID_D5_ADDRESS_EEPROM + ((_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D5_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D7_D0_ADDRESS_EEPROM                              (_EDID_D6_ADDRESS_EEPROM + ((_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D6_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D7_D1_ADDRESS_EEPROM                              (_EDID_D7_D0_ADDRESS_EEPROM + ((_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D7_D0_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D8_D1_ADDRESS_EEPROM                              (_EDID_D7_D1_ADDRESS_EEPROM + ((_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D7_D1_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D8_D2_ADDRESS_EEPROM                              (_EDID_D8_D1_ADDRESS_EEPROM + ((_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D8_D1_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D9_ADDRESS_EEPROM                                 (_EDID_D8_D2_ADDRESS_EEPROM + ((_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D8_D2_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_END_ADDRESS_EEPROM                                (_EDID_D9_ADDRESS_EEPROM + ((_D9_EMBEDDED_XRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ? _D9_EMBEDDED_XRAM_MAX_SIZE : 0))

#define _EDID_A0_ADDRESS_FLASH                                  (_EDID_ADDRESS_FLASH)
#define _EDID_D0_ADDRESS_FLASH                                  (_EDID_A0_ADDRESS_FLASH + ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _A0_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D1_ADDRESS_FLASH                                  (_EDID_D0_ADDRESS_FLASH + ((_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D0_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D2_ADDRESS_FLASH                                  (_EDID_D1_ADDRESS_FLASH + ((_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D1_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D3_ADDRESS_FLASH                                  (_EDID_D2_ADDRESS_FLASH + ((_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D2_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D4_ADDRESS_FLASH                                  (_EDID_D3_ADDRESS_FLASH + ((_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D3_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D5_ADDRESS_FLASH                                  (_EDID_D4_ADDRESS_FLASH + ((_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D4_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D6_ADDRESS_FLASH                                  (_EDID_D5_ADDRESS_FLASH + ((_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D5_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D7_D0_ADDRESS_FLASH                               (_EDID_D6_ADDRESS_FLASH + ((_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D6_EMBEDDED_DDCRAM_MAX_SIZE : 0))
#define _EDID_D7_D1_ADDRESS_FLASH                               (_EDID_D7_D0_ADDRESS_FLASH + ((_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D7_D0_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D8_D1_ADDRESS_FLASH                               (_EDID_D7_D1_ADDRESS_FLASH + ((_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D7_D1_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D8_D2_ADDRESS_FLASH                               (_EDID_D8_D1_ADDRESS_FLASH + ((_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D8_D1_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_D9_ADDRESS_FLASH                                  (_EDID_D8_D2_ADDRESS_FLASH + ((_D8_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D8_D2_EMBEDDED_DDCRAM_SIZE : 0))
#define _EDID_END_ADDRESS_FLASH                                 (_EDID_D9_ADDRESS_EEPROM + ((_D9_EMBEDDED_XRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ? _D9_EMBEDDED_XRAM_MAX_SIZE : 0))

//-------------------------------------------------
// VGA Digital Filter Option
//-------------------------------------------------
#define _DIGITAL_FILTER_SUPPORT                                 ((_DIG_FILTER_PHASE_SUPPORT == _ON) ||\
                                                                 (_DIG_FILTER_NSMEAR_SUPPORT == _ON) ||\
                                                                 (_DIG_FILTER_PSMEAR_SUPPORT == _ON) ||\
                                                                 (_DIG_FILTER_NRING_SUPPORT == _ON) ||\
                                                                 (_DIG_FILTER_PRING_SUPPORT == _ON) ||\
                                                                 (_DIG_FILTER_ENHANCE_PHASE_SUPPORT == _ON))

//-------------------------------------------------
// TMDS Clock On Line Measure Lower Boundary Set
//-------------------------------------------------
#ifndef _TMDS_CLOCK_MEASURE_LOWER_BOUNDARY
#define _TMDS_CLOCK_MEASURE_LOWER_BOUNDARY                      25
#endif

//-------------------------------------------------
// DP Link Rate Adjust Set
//-------------------------------------------------
#define DP_LINK_RATE_ADJUST(x, y)                               (((x) == _DP_FOUR_LANE) ? (((y) > 172800) ? _DP_LINK_HBR3 : (((y) > 86400) ? _DP_LINK_HBR2 : _DP_LINK_HBR)) :\
                                                                (((x) == _DP_TWO_LANE) ? (((y) > 86400) ? _DP_LINK_HBR3 : (((y) > 43200) ? _DP_LINK_HBR2 : _DP_LINK_HBR)) :\
                                                                (((y) > 43200) ? _DP_LINK_HBR3 : (((y) > 21600) ? _DP_LINK_HBR2 : _DP_LINK_HBR))))

//--------------------------------------------------
// HDCP 2.2 Option
//--------------------------------------------------
#define _HDCP_2_2_SUPPORT                                       ((_TMDS_HDCP_2_2_SUPPORT == _ON) ||\
                                                                 (_DP_HDCP_2_2_SUPPORT == _ON))

//--------------------------------------------------
// Interface RDC TEST MODE
//--------------------------------------------------
#ifndef _RDC_TEST_TYPE
#define _RDC_TEST_TYPE                                          _HDMI_RDC_TEST_TYPE_NONE
#endif

//--------------------------------------------------
// Apple Source IEEE_OUI Check, BYTE Length Limit 9 BYTE
//--------------------------------------------------
#ifndef _SRC_IEEE_OUI_APPLE_2017_PRO_15INCH_IDENTIFY_STRING
#define _SRC_IEEE_OUI_APPLE_2017_PRO_15INCH_IDENTIFY_STRING     {0x00, 0x00, 0x1A, 0xEF, 0x67, 0x00, 0x00, 0x00, 0x00}
#endif

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#if(_AUDIO_SUPPORT == _OFF)
#undef _DAC_HP_OUTPUT_SUPPORT
#undef _DAC_SPEAKER_OUTPUT_SUPPORT
#undef _LINE_IN_SUPPORT
#undef _SLEEP_AUDIO_SUPPORT
#define _DAC_HP_OUTPUT_SUPPORT                                  _OFF
#define _DAC_SPEAKER_OUTPUT_SUPPORT                             _OFF
#define _LINE_IN_SUPPORT                                        _OFF
#define _SLEEP_AUDIO_SUPPORT                                    _OFF
#endif

//-------------------------------------------------
// Audio DAC Support Definition
//-------------------------------------------------
#define _EMBEDDED_DAC_SUPPORT                                   ((_DAC_HP_OUTPUT_SUPPORT == _ON) ||\
                                                                 (_DAC_SPEAKER_OUTPUT_SUPPORT == _ON))

//-------------------------------------------------
// Audio PARALLEL MODE Support Definition
//-------------------------------------------------
#define _AUDIO_PARALLEL_MODE_SUPPORT                            ((_SPDIF_PARALLEL_MODE_SUPPORT == _ON) ||\
                                                                  (_I2S_PARALLEL_MODE_SUPPORT == _ON))

//--------------------------------------------------
// Audio ARC Tx Support Definition
//--------------------------------------------------
#define _AUDIO_ARC_SUPPORT                                      ((_AUDIO_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE != _AUDIO_ARC_TX_NOT_SUPPORT))
#define _AUDIO_EARC_SUPPORT                                     ((_AUDIO_ARC_SUPPORT == _ON) &&\
                                                                 (((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) && (_D1_HDMI_ARC_TX_PIN == _HDMI_EARC_TX)) ||\
                                                                  ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) && (_D2_HDMI_ARC_TX_PIN == _HDMI_EARC_TX)) ||\
                                                                  ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) && (_D3_HDMI_ARC_TX_PIN == _HDMI_EARC_TX)) ||\
                                                                  ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) && (_D4_HDMI_ARC_TX_PIN == _HDMI_EARC_TX))))

//-------------------------------------------------
// Audio Line In Option
//-------------------------------------------------
#define _LINE_IN_VOLUME_CENTER                                  ((_LINE_IN_VOLUME_MAX + _LINE_IN_VOLUME_MIN) / 2)

//-------------------------------------------------
// Audio Digital Option
//-------------------------------------------------
#define _DIGITAL_VOLUME_CENTER                                  ((_DIGITAL_VOLUME_MAX + _DIGITAL_VOLUME_MIN) / 2)


//--------------------------------------------------
// MAIN CPU Option
//--------------------------------------------------
#define _IS_MAIN_PROCESS_CPU                                    (((_HW_CPU32_IS_BOOT_CPU == _TRUE) && (_FW_CPU32_MAIN_PROCESS_CPU == _CPU_ID_KCPU)) ||\
                                                                 ((_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_FW_CPU32_MAIN_PROCESS_CPU == _CPU_ID_SCPU)))

//--------------------------------------------------
// SCPU Option
//--------------------------------------------------
#define _SCPU_IMAGE_LOAD_TIMEOUT                                ((_DM_FUNCTION == _ON) ? 1000 : 500) // ms

#define _SCPU_BUILD_KCPU_FILES                                  (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)

//-------------------------------------------------
// System Power Saving Ref Clock Option
//-------------------------------------------------
#define _SYS_PS_CLOCK_SOURCE                                    ((_SYS_PS_TIMER_PRECISION_SUPPPORT == _ON) ? (_EXT_XTAL_CLK) : (_IOSC_CLK))

//-------------------------------------------------
// Eeprom address
//-------------------------------------------------
#define _EEPROM_CHECKSUM_ADDRESS                                (_EEPROM_KERNEL_START_ADDRESS)
#define _EEPROM_VERSION_CODE_ADDRESS                            (_EEPROM_CHECKSUM_ADDRESS + 1)
#define _ADC_SETTING_ADDRESS                                    (_EEPROM_VERSION_CODE_ADDRESS + 1)
#define _SYSTEM_DATA_ADDRESS                                    (_ADC_SETTING_ADDRESS + sizeof(StructAdcDataType) * (_VGA_SUPPORT + _YPBPR_SUPPORT))
#define _SYSTEM_DATA_ADDRESS_END                                (_SYSTEM_DATA_ADDRESS + sizeof(StructSystemDataType))

#define _MODE_USER_DATA_ADDRESS                                 (_SYSTEM_DATA_ADDRESS_END)
#define _VGA_MODE_DATA_ADDRESS_END                              (_MODE_USER_DATA_ADDRESS + sizeof(StructVgaModeUserDataType) * _MODE_SLOT_AMOUNT * _VGA_SUPPORT)

//-------------------------------------------------
// FW DDR3/DDR2/DDR1/SDRAM PLL Freq
//-------------------------------------------------
#if(_SCALER_TYPE == _RL6829_SERIES)
#define _FW_DDR_PLL_CLOCK_DEFAULT                               _MEMORY_SPEED_933MHZ // DDR3 Support Speed : 800MHz/933MHz/1066MHz
#elif(_SCALER_TYPE == _RL6952_SERIES)
#define _FW_DDR_PLL_CLOCK_DEFAULT                               _MEMORY_SPEED_1066MHZ // DDR3 Support Speed : 800MHz/933MHz/1066MHz
#elif(_SCALER_TYPE == _RL6978_SERIES)
#define _FW_DDR_PLL_CLOCK_DEFAULT                               _MEMORY_SPEED_667MHZ // DDR2 Support Speed : 533/600/667MHz
#else
#define _FW_DDR_PLL_CLOCK_DEFAULT                               _MEMORY_SPEED_198MHZ
#endif

//--------------------------------------------------
// Total num of DPI_CRT(DDR PLL) theoretical PI
// (combination of PI & WRLVL)
//--------------------------------------------------
#define _TOTAL_THEO_DPI_PI_NUM                                  128

//--------------------------------------------------
// SPI Option
//--------------------------------------------------
#define _SPI_SUPPORT                                            ((_SPI0_SUPPORT == _ON) || (_SPI1_SUPPORT == _ON) || (_SPI2_SUPPORT == _ON))

#if(_SPI0_SETTING_SOURCE == _SPI_SETTING_BY_PROJECT)
#define _SPI0_CLK_PRE_DIV                                       _PROJECT_SPI0_CLK_PRE_DIV       // SPI CLK PreDivider
#define _SPI0_CLK_DIV                                           _PROJECT_SPI0_CLK_DIV           // SPI CLK Divider
#define _SPI0_ENUM_PROTOCOL_SEL                                 _PROJECT_SPI0_ENUM_PROTOCOL_SEL // SPI Protocol Select
#define _SPI0_ENUM_CLK_SRC_SEL                                  _PROJECT_SPI0_ENUM_CLK_SRC_SEL  // SPI CLK Source
#define _SPI0_MOSI_IDLE_STATE                                   _PROJECT_SPI0_MOSI_IDLE_STATE   // 0:low ; 1:high
#define _SPI0_SCLK_IDLE_STATE                                   _PROJECT_SPI0_SCLK_IDLE_STATE   // 0:low ; 1:high
#define _SPI0_CS_SEL                                            _PROJECT_SPI0_CS_SEL            // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI0_CS_POLARITY                                       _PROJECT_SPI0_CS_POLARITY       // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI0_CS_SETUP                                          _PROJECT_SPI0_CS_SETUP          // SPI CS Pin Setup Number(base on sclk)
#define _SPI0_CS_HOLD                                           _PROJECT_SPI0_CS_HOLD           // SPI CS Pin Hold Number(base on sclk)
#define _SPI0_SUPPRESS_BITS                                     _PROJECT_SPI0_SUPPRESS_BITS     // SPI Suppress Bits(value = 0~7)
#endif
#if(_SPI1_SETTING_SOURCE == _SPI_SETTING_BY_PROJECT)
#define _SPI1_CLK_PRE_DIV                                       _PROJECT_SPI1_CLK_PRE_DIV       // SPI CLK PreDivider
#define _SPI1_CLK_DIV                                           _PROJECT_SPI1_CLK_DIV           // SPI CLK Divider
#define _SPI1_ENUM_PROTOCOL_SEL                                 _PROJECT_SPI1_ENUM_PROTOCOL_SEL // SPI Protocol Select
#define _SPI1_ENUM_CLK_SRC_SEL                                  _PROJECT_SPI1_ENUM_CLK_SRC_SEL  // SPI CLK Source
#define _SPI1_MOSI_IDLE_STATE                                   _PROJECT_SPI1_MOSI_IDLE_STATE   // 0:low ; 1:high
#define _SPI1_SCLK_IDLE_STATE                                   _PROJECT_SPI1_SCLK_IDLE_STATE   // 0:low ; 1:high
#define _SPI1_CS_SEL                                            _PROJECT_SPI1_CS_SEL            // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI1_CS_POLARITY                                       _PROJECT_SPI1_CS_POLARITY       // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI1_CS_SETUP                                          _PROJECT_SPI1_CS_SETUP          // SPI CS Pin Setup Number(base on sclk)
#define _SPI1_CS_HOLD                                           _PROJECT_SPI1_CS_HOLD           // SPI CS Pin Hold Number(base on sclk)
#define _SPI1_SUPPRESS_BITS                                     _PROJECT_SPI1_SUPPRESS_BITS     // SPI Suppress Bits(value = 0~7)
#endif
#if(_SPI2_SETTING_SOURCE == _SPI_SETTING_BY_PROJECT)
#define _SPI2_CLK_PRE_DIV                                       _PROJECT_SPI2_CLK_PRE_DIV       // SPI CLK PreDivider
#define _SPI2_CLK_DIV                                           _PROJECT_SPI2_CLK_DIV           // SPI CLK Divider
#define _SPI2_ENUM_PROTOCOL_SEL                                 _PROJECT_SPI2_ENUM_PROTOCOL_SEL // SPI Protocol Select
#define _SPI2_ENUM_CLK_SRC_SEL                                  _PROJECT_SPI2_ENUM_CLK_SRC_SEL  // SPI CLK Source
#define _SPI2_MOSI_IDLE_STATE                                   _PROJECT_SPI2_MOSI_IDLE_STATE   // 0:low ; 1:high
#define _SPI2_SCLK_IDLE_STATE                                   _PROJECT_SPI2_SCLK_IDLE_STATE   // 0:low ; 1:high
#define _SPI2_CS_SEL                                            _PROJECT_SPI2_CS_SEL            // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI2_CS_POLARITY                                       _PROJECT_SPI2_CS_POLARITY       // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI2_CS_SETUP                                          _PROJECT_SPI2_CS_SETUP          // SPI CS Pin Setup Number(base on sclk)
#define _SPI2_CS_HOLD                                           _PROJECT_SPI2_CS_HOLD           // SPI CS Pin Hold Number(base on sclk)
#define _SPI2_SUPPRESS_BITS                                     _PROJECT_SPI2_SUPPRESS_BITS     // SPI Suppress Bits(value = 0~7)
#endif

#if(_SPI0_SETTING_SOURCE == _SPI_SETTING_BY_PANEL)
#define _SPI0_CLK_PRE_DIV                                       _PANEL_SPI0_CLK_PRE_DIV         // SPI CLK PreDivider
#define _SPI0_CLK_DIV                                           _PANEL_SPI0_CLK_DIV             // SPI CLK Divider
#define _SPI0_ENUM_PROTOCOL_SEL                                 _PANEL_SPI0_ENUM_PROTOCOL_SEL   // SPI Protocol Select
#define _SPI0_ENUM_CLK_SRC_SEL                                  _PANEL_SPI0_ENUM_CLK_SRC_SEL    // SPI CLK Source
#define _SPI0_MOSI_IDLE_STATE                                   _PANEL_SPI0_MOSI_IDLE_STATE     // 0:low ; 1:high
#define _SPI0_SCLK_IDLE_STATE                                   _PANEL_SPI0_SCLK_IDLE_STATE     // 0:low ; 1:high
#define _SPI0_CS_SEL                                            _PANEL_SPI0_CS_SEL              // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI0_CS_POLARITY                                       _PANEL_SPI0_CS_POLARITY         // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI0_CS_SETUP                                          _PANEL_SPI0_CS_SETUP            // SPI CS Pin Setup Number(base on sclk)
#define _SPI0_CS_HOLD                                           _PANEL_SPI0_CS_HOLD             // SPI CS Pin Hold Number(base on sclk)
#define _SPI0_SUPPRESS_BITS                                     _PANEL_SPI0_SUPPRESS_BITS       // SPI Suppress Bits(value = 0~7)
#endif
#if(_SPI1_SETTING_SOURCE == _SPI_SETTING_BY_PANEL)
#define _SPI1_CLK_PRE_DIV                                       _PANEL_SPI1_CLK_PRE_DIV         // SPI CLK PreDivider
#define _SPI1_CLK_DIV                                           _PANEL_SPI1_CLK_DIV             // SPI CLK Divider
#define _SPI1_ENUM_PROTOCOL_SEL                                 _PANEL_SPI1_ENUM_PROTOCOL_SEL   // SPI Protocol Select
#define _SPI1_ENUM_CLK_SRC_SEL                                  _PANEL_SPI1_ENUM_CLK_SRC_SEL    // SPI CLK Source
#define _SPI1_MOSI_IDLE_STATE                                   _PANEL_SPI1_MOSI_IDLE_STATE     // 0:low ; 1:high
#define _SPI1_SCLK_IDLE_STATE                                   _PANEL_SPI1_SCLK_IDLE_STATE     // 0:low ; 1:high
#define _SPI1_CS_SEL                                            _PANEL_SPI1_CS_SEL              // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI1_CS_POLARITY                                       _PANEL_SPI1_CS_POLARITY         // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI1_CS_SETUP                                          _PANEL_SPI1_CS_SETUP            // SPI CS Pin Setup Number(base on sclk)
#define _SPI1_CS_HOLD                                           _PANEL_SPI1_CS_HOLD             // SPI CS Pin Hold Number(base on sclk)
#define _SPI1_SUPPRESS_BITS                                     _PANEL_SPI1_SUPPRESS_BITS       // SPI Suppress Bits(value = 0~7)
#endif
#if(_SPI2_SETTING_SOURCE == _SPI_SETTING_BY_PANEL)
#define _SPI2_CLK_PRE_DIV                                       _PANEL_SPI2_CLK_PRE_DIV         // SPI CLK PreDivider
#define _SPI2_CLK_DIV                                           _PANEL_SPI2_CLK_DIV             // SPI CLK Divider
#define _SPI2_ENUM_PROTOCOL_SEL                                 _PANEL_SPI2_ENUM_PROTOCOL_SEL   // SPI Protocol Select
#define _SPI2_ENUM_CLK_SRC_SEL                                  _PANEL_SPI2_ENUM_CLK_SRC_SEL    // SPI CLK Source
#define _SPI2_MOSI_IDLE_STATE                                   _PANEL_SPI2_MOSI_IDLE_STATE     // 0:low ; 1:high
#define _SPI2_SCLK_IDLE_STATE                                   _PANEL_SPI2_SCLK_IDLE_STATE     // 0:low ; 1:high
#define _SPI2_CS_SEL                                            _PANEL_SPI2_CS_SEL              // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI2_CS_POLARITY                                       _PANEL_SPI2_CS_POLARITY         // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI2_CS_SETUP                                          _PANEL_SPI2_CS_SETUP            // SPI CS Pin Setup Number(base on sclk)
#define _SPI2_CS_HOLD                                           _PANEL_SPI2_CS_HOLD             // SPI CS Pin Hold Number(base on sclk)
#define _SPI2_SUPPRESS_BITS                                     _PANEL_SPI2_SUPPRESS_BITS       // SPI Suppress Bits(value = 0~7)
#endif


#if(_SPI0_SETTING_SOURCE == _SPI_SETTING_BY_PCB)
#define _SPI0_CLK_PRE_DIV                                       _PCB_SPI0_CLK_PRE_DIV           // SPI CLK PreDivider
#define _SPI0_CLK_DIV                                           _PCB_SPI0_CLK_DIV               // SPI CLK Divider
#define _SPI0_ENUM_PROTOCOL_SEL                                 _PCB_SPI0_ENUM_PROTOCOL_SEL     // SPI Protocol Select
#define _SPI0_ENUM_CLK_SRC_SEL                                  _PCB_SPI0_ENUM_CLK_SRC_SEL      // SPI CLK Source
#define _SPI0_MOSI_IDLE_STATE                                   _PCB_SPI0_MOSI_IDLE_STATE       // 0:low ; 1:high
#define _SPI0_SCLK_IDLE_STATE                                   _PCB_SPI0_SCLK_IDLE_STATE       // 0:low ; 1:high
#define _SPI0_CS_SEL                                            _PCB_SPI0_CS_SEL                // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI0_CS_POLARITY                                       _PCB_SPI0_CS_POLARITY           // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI0_CS_SETUP                                          _PCB_SPI0_CS_SETUP              // SPI CS Pin Setup Number(base on sclk)
#define _SPI0_CS_HOLD                                           _PCB_SPI0_CS_HOLD               // SPI CS Pin Hold Number(base on sclk)
#define _SPI0_SUPPRESS_BITS                                     _PCB_SPI0_SUPPRESS_BITS         // SPI Suppress Bits(value = 0~7)
#endif
#if(_SPI1_SETTING_SOURCE == _SPI_SETTING_BY_PCB)
#define _SPI1_CLK_PRE_DIV                                       _PCB_SPI1_CLK_PRE_DIV           // SPI CLK PreDivider
#define _SPI1_CLK_DIV                                           _PCB_SPI1_CLK_DIV               // SPI CLK Divider
#define _SPI1_ENUM_PROTOCOL_SEL                                 _PCB_SPI1_ENUM_PROTOCOL_SEL     // SPI Protocol Select
#define _SPI1_ENUM_CLK_SRC_SEL                                  _PCB_SPI1_ENUM_CLK_SRC_SEL      // SPI CLK Source
#define _SPI1_MOSI_IDLE_STATE                                   _PCB_SPI1_MOSI_IDLE_STATE       // 0:low ; 1:high
#define _SPI1_SCLK_IDLE_STATE                                   _PCB_SPI1_SCLK_IDLE_STATE       // 0:low ; 1:high
#define _SPI1_CS_SEL                                            _PCB_SPI1_CS_SEL                // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI1_CS_POLARITY                                       _PCB_SPI1_CS_POLARITY           // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI1_CS_SETUP                                          _PCB_SPI1_CS_SETUP              // SPI CS Pin Setup Number(base on sclk)
#define _SPI1_CS_HOLD                                           _PCB_SPI1_CS_HOLD               // SPI CS Pin Hold Number(base on sclk)
#define _SPI1_SUPPRESS_BITS                                     _PCB_SPI1_SUPPRESS_BITS         // SPI Suppress Bits(value = 0~7)
#endif
#if(_SPI2_SETTING_SOURCE == _SPI_SETTING_BY_PCB)
#define _SPI2_CLK_PRE_DIV                                       _PCB_SPI2_CLK_PRE_DIV           // SPI CLK PreDivider
#define _SPI2_CLK_DIV                                           _PCB_SPI2_CLK_DIV               // SPI CLK Divider
#define _SPI2_ENUM_PROTOCOL_SEL                                 _PCB_SPI2_ENUM_PROTOCOL_SEL     // SPI Protocol Select
#define _SPI2_ENUM_CLK_SRC_SEL                                  _PCB_SPI2_ENUM_CLK_SRC_SEL      // SPI CLK Source
#define _SPI2_MOSI_IDLE_STATE                                   _PCB_SPI2_MOSI_IDLE_STATE       // 0:low ; 1:high
#define _SPI2_SCLK_IDLE_STATE                                   _PCB_SPI2_SCLK_IDLE_STATE       // 0:low ; 1:high
#define _SPI2_CS_SEL                                            _PCB_SPI2_CS_SEL                // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _SPI2_CS_POLARITY                                       _PCB_SPI2_CS_POLARITY           // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#define _SPI2_CS_SETUP                                          _PCB_SPI2_CS_SETUP              // SPI CS Pin Setup Number(base on sclk)
#define _SPI2_CS_HOLD                                           _PCB_SPI2_CS_HOLD               // SPI CS Pin Hold Number(base on sclk)
#define _SPI2_SUPPRESS_BITS                                     _PCB_SPI2_SUPPRESS_BITS         // SPI Suppress Bits(value = 0~7)
#endif

//--------------------------------------------------
// Global Interrrupt Option
//--------------------------------------------------
#define _GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN                  (_DM_FUNCTION == _ON)

#define _GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN                  (((_OD_FUNCTION == _ON) && (_FRC_SUPPORT == _ON)) ||\
                                                                 (_LOCAL_DIMMING_FUNCTION == _ON) || (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_GOSD_SUPPORT == _ON) || (_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _ON))

#define _GLOBAL_INTERRUPT_FUNCTION                              ((_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON) ||\
                                                                 (_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON))


//-------------------------------------------------
// GOSD Option
//-------------------------------------------------
#define _GOSD_MEMORY_BW                                         ((_GOSD_MEMORY_BW_DISPLAY) + (_GOSD_MEMORY_BW_DRAW)) // unit: percent

#if(_HW_CPU32_KCPU_MEMORYMAP_ACCESS_DDR == _TRUE)
#define _GOSD_FW_MODE                                           (_GOSD_FW_ONE_CPU_MODE)
#elif(_HW_CPU32_SCPU_MEMORYMAP_ACCESS_DDR == _TRUE)
#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_COPROCESSOR)
#define _GOSD_FW_MODE                                           (_GOSD_FW_TWO_CPU_MODE_1)
#elif(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
#define _GOSD_FW_MODE                                           (_GOSD_FW_TWO_CPU_MODE_2)
#endif
#else
#define _GOSD_FW_MODE                                           (_GOSD_FW_TWO_CPU_MODE_1)
#endif

#if(_GOSD_FW_MODE == _GOSD_FW_TWO_CPU_MODE_1)
#define _GOSD_FW_COMPILE_REQUEST_FLOW                           (_IS_MAIN_PROCESS_CPU == _TRUE)
#define _GOSD_FW_COMPILE_RESPONSE_FLOW                          (_IS_MAIN_PROCESS_CPU == _FALSE)
#define _GOSD_SYNC_BY_GLOBAL_VARIABLE                           (_FALSE)
#define _GOSD_SYNC_BY_INT_NOTIFY                                ((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) &&\
                                                                 (_SCPU_SUPPORT == _ON))
#elif(_GOSD_FW_MODE == _GOSD_FW_TWO_CPU_MODE_2)
#define _GOSD_FW_COMPILE_REQUEST_FLOW                           (_TRUE)
#define _GOSD_FW_COMPILE_RESPONSE_FLOW                          (_IS_MAIN_PROCESS_CPU == _FALSE)
#define _GOSD_SYNC_BY_GLOBAL_VARIABLE                           (_TRUE)
#define _GOSD_SYNC_BY_INT_NOTIFY                                ((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) &&\
                                                                 (_SCPU_SUPPORT == _ON) &&\
                                                                 (_IS_MAIN_PROCESS_CPU == _TRUE))
#elif(_GOSD_FW_MODE == _GOSD_FW_ONE_CPU_MODE)
#define _GOSD_FW_COMPILE_REQUEST_FLOW                           (_TRUE)
#define _GOSD_FW_COMPILE_RESPONSE_FLOW                          (_TRUE)
#define _GOSD_SYNC_BY_GLOBAL_VARIABLE                           (_TRUE)
#define _GOSD_SYNC_BY_INT_NOTIFY                                (_FALSE)
#endif


//-------------------------------------------------
// Flash Partition Process Support
//-------------------------------------------------
#define _DUAL_BANK_DIFF_COPY_SUPPORT                            ((_DUAL_BANK_SUPPORT == _ON) &&\
                                                                 ((_DUAL_BANK_TYPE == _DUAL_BANK_DIFF_BANK) ||\
                                                                 (_DUAL_BANK_TYPE == _DUAL_BANK_COPY_BANK)))


//-------------------------------------------------
// Flash Partition Process Support
//-------------------------------------------------
#define _DUAL_BANK_FLASH_PARTITION_SUPPORT                      ((_DUAL_BANK_SUPPORT == _ON) &&\
                                                                 ((_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION) ||\
                                                                 (_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)))


//-------------------------------------------------
// Dual bank Common Debug Supprot
//-------------------------------------------------
#define _DUAL_BANK_DEBUG_SUPPORT                                ((_DUAL_BANK_SUPPORT == _ON) ||\
                                                                 (_DIGITAL_SIGNATURE_SUPPORT == _ON) || (_ISP_CHANNEL_PROTECT_SUPPORT == _ON))


//-------------------------------------------------
// For  dual bank ld link
//-------------------------------------------------
#define _DUAL_BANK_FLASH_PARIRION_TABLE_SUPPORT                 (((_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_BOOT) &&\
                                                                 (_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL != _DUAL_BANK_FLASH_PARTITION_USER)) ||\
                                                                 ((_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_USER) &&\
                                                                  (_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL != _DUAL_BANK_FLASH_PARTITION_BOOT)))

// For diff/copy / flash Partition
#define _DUAL_BANK_USER_DATA_TABLE_SUPPORT                      ((_DUAL_BANK_SUPPORT == _ON) &&\
                                                                 (((_DUAL_BANK_DIFF_COPY_SUPPORT == _ON) &&\
                                                                  (_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_USER)) ||\
                                                                  ((_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION) &&\
                                                                   (_DUAL_BANK_FLASH_PARIRION_TABLE_SUPPORT == _ON))))

// Flash Partition User Flag Mode: Boot & Both:occupy Code Table if flag in Boot FW;User & Both:occupy Code Table if flag in User FW
#define _DUAL_BANK_FP_USER_FLAG_TABLE_SUPPORT                   ((_DUAL_BANK_SUPPORT == _ON) &&\
                                                                  (_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE) &&\
                                                                  (_DUAL_BANK_FLASH_PARIRION_TABLE_SUPPORT == _ON))


#if(_SCPU_SUPPORT == _ON)

#if(defined(CPU32_BOOTLOADER) == _TRUE)
#define _DUAL_BANK_USER_I_TABLE_SUPPORT                         (_DUAL_BANK_USER_I_FLAG_LOCATE_BANK == (_DUAL_BANK_USER_FW_CODE_SIZE - 1))
#define _DUAL_BANK_USER_II_TABLE_SUPPORT                        (_DUAL_BANK_USER_II_FLAG_LOCATE_BANK == (_DUAL_BANK_USER_FW_CODE_SIZE - 1))

#else
#define _DUAL_BANK_USER_I_TABLE_SUPPORT                         ((_HW_CPU32_IS_BOOT_CPU == _TRUE) &&\
                                                                 (_DUAL_BANK_USER_I_FLAG_LOCATE_BANK != (_DUAL_BANK_USER_FW_CODE_SIZE - 1)))
#define _DUAL_BANK_USER_II_TABLE_SUPPORT                        ((_HW_CPU32_IS_BOOT_CPU == _TRUE) &&\
                                                                 (_DUAL_BANK_USER_II_FLAG_LOCATE_BANK != (_DUAL_BANK_USER_FW_CODE_SIZE - 1)))
#endif

#else
#define _DUAL_BANK_USER_I_TABLE_SUPPORT                         _ON
#define _DUAL_BANK_USER_II_TABLE_SUPPORT                        _ON
#endif

#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_DATA_SECTOR_ADDRESS                     0xD000
#else
#define _DUAL_BANK_USER_DATA_SECTOR_ADDRESS                     0xF000
#endif

//-------------------------------------------------
// Fw Update Process Support
//-------------------------------------------------
#define _FW_UPDATE_PROCESS_SUPPORT                              ((_FW_UPDATE_BACKGROUND_SUPPORT == _ON) ||\
                                                                 (_FW_UPDATE_FOREGROUND_SUPPORT == _ON) ||\
                                                                 (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON))


//-------------------------------------------------
// Fw Update Speed Up Support
//-------------------------------------------------
#define _FW_ISP_SPEED_UP_PROCESS_SUPPORT                        (((_FW_UPDATE_BACKGROUND_SUPPORT == _ON) ||\
                                                                  (_FW_UPDATE_FOREGROUND_SUPPORT == _ON)) &&\
                                                                 ((_FW_UPDATE_FW_SPEED_UP_SUPPORT == _ON) &&\
                                                                  (_HW_ISP_SPEED_UP_SUPPORT == _ON)))

//--------------------------------------------------
// embedded resource file support
//--------------------------------------------------
#ifndef _EMBEDDED_RESOURCE_FILE_SUPPORT
#define _EMBEDDED_RESOURCE_FILE_SUPPORT                         _OFF
#endif

//--------------------------------------------------
// Memory BW Ctrl Option
//--------------------------------------------------
#define _FRC_MEMORY_BW_CTRL_SUPPORT                             ((_HW_MEMORY_BW_CTRL_FRC_SUPPORT == _ON) &&\
                                                                 (_MEMORY_TYPE_CONFIG != _NO_MEMORY) &&\
                                                                 (_FRC_SUPPORT == _ON) &&\
                                                                 ((_FRC_CAPTURE_BW_CTRL_SUPPORT == _ON) || (_FRC_DISPLAY_BW_CTRL_SUPPORT == _ON)))

#define _OD_MEMORY_BW_CTRL_SUPPORT                              ((_HW_MEMORY_BW_CTRL_OD_SUPPORT == _ON) &&\
                                                                 (_MEMORY_TYPE_CONFIG != _NO_MEMORY) &&\
                                                                 (_OD_FUNCTION == _ON) &&\
                                                                 (_OD_BW_CTRL_SUPPORT == _ON))

#define _3DDI_MEMORY_BW_CTRL_SUPPORT                            ((_HW_MEMORY_BW_CTRL_3DDI_SUPPORT == _ON) &&\
                                                                 (_MEMORY_TYPE_CONFIG != _NO_MEMORY) &&\
                                                                 (_COLOR_IP_3DDI == _ON) &&\
                                                                 (_3DDI_BW_CTRL_SUPPORT == _ON))

#define _GOSD_MEMORY_BW_CTRL_SUPPORT                            ((_HW_MEMORY_BW_CTRL_GOSD_SUPPORT == _ON) &&\
                                                                 (_MEMORY_TYPE_CONFIG != _NO_MEMORY) &&\
                                                                 (_GOSD_SUPPORT == _ON) &&\
                                                                 ((_GOSD_DRAW_BW_CTRL_SUPPORT == _ON) || (_GOSD_DISPLAY_BW_CTRL_SUPPORT == _ON)))

#define _MEMORY_BW_CTRL_SUPPORT                                 ((_FRC_MEMORY_BW_CTRL_SUPPORT == _ON) ||\
                                                                 (_OD_MEMORY_BW_CTRL_SUPPORT == _ON) ||\
                                                                 (_3DDI_MEMORY_BW_CTRL_SUPPORT == _ON) ||\
                                                                 (_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON))

//--------------------------------------------------
// KCPU Scaler Other Interrupt INT12 Option
//--------------------------------------------------
#define _ENABLE_KCPU_SCALER_OTHER_INT                           (((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)) ||\
                                                                 ((_COLOR_IP_LOCAL_DIMMING == _ON) && (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)) ||\
                                                                 ((_GOSD_SUPPORT == _ON) && (_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE) && ((_GOSD_FW_MODE == _GOSD_FW_ONE_CPU_MODE) || (_GOSD_FW_MODE == _GOSD_FW_TWO_CPU_MODE_2))) ||\
                                                                 (_IR_SUPPORT == _IR_HW_SUPPORT))

//-------------------------------------------------
// DP DPCD 300h Write Intterupt Support
//-------------------------------------------------
#define _DP_AUX_RX_DPCD_300_SOURCE_OUI_INT_SUPPORT              (_DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT == _ON)

//-------------------------------------------------
// DP User INT0 Support
//-------------------------------------------------
#define _DP_USER_INT0_SUPPORT                                   (_DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT == _ON)

//--------------------------------------------------
// DP Aux Listen Mode z0
//--------------------------------------------------
#define _DP_AUX_LISTEN_MODE_Z0                                  _DP_AUX_Z0_94_OHM

//--------------------------------------------------
// FRC Length Option
//--------------------------------------------------
#if(_HW_FRC_LENGTH_TYPE == _FRC_LENGTH_7BIT)
#define _FRC_LENGTH_ENLRGE_M1_M2_ONLY                           (_BW_80_PERCENT_1P_SUPPORT == _ON)
#define _FRC_ACCESS_WRITE_LENGTH                                (_FRC_LENGTH_7BIT)
#define _FRC_ACCESS_READ_LENGTH                                 (_FRC_LENGTH_7BIT)
#elif(_HW_FRC_LENGTH_TYPE == _FRC_LENGTH_8BIT)
#define _FRC_LENGTH_ENLRGE_M1_M2_ONLY                           _OFF
#define _FRC_ACCESS_WRITE_LENGTH                                (_FRC_LENGTH_8BIT)
#define _FRC_ACCESS_READ_LENGTH                                 (_FRC_LENGTH_8BIT)
#endif

#endif // End of #ifndef __PROJECT_OPTION_H__
