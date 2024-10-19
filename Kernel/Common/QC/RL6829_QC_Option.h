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
// ID Code      : RL6829_QC_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// Notify QC fail ID
#define PCB_QC_NOTIFY(id)                                       {\
                                                                    ScalerQC7SegmentDisplay(id);\
                                                                }

// For testing with RLE0638
#undef _INPUTCLOCK_RANG_DVI
#define _INPUTCLOCK_RANG_DVI                                    6000

// Force #define settings for QC flow
#undef _2P_PIP_DISPLAY_SUPPORT
#define _2P_PIP_DISPLAY_SUPPORT                                 _ON

#undef _2P_PBP_LR_DISPLAY_SUPPORT
#define _2P_PBP_LR_DISPLAY_SUPPORT                              _ON

#undef _2P_PBP_TB_DISPLAY_SUPPORT
#define _2P_PBP_TB_DISPLAY_SUPPORT                              _ON

#undef _4P_DISPLAY_SUPPORT
#define _4P_DISPLAY_SUPPORT                                     _ON

#undef _3P_FLAG_DISPLAY_SUPPORT
#define _3P_FLAG_DISPLAY_SUPPORT                                _ON

#undef _3P_SKEW_LR_DISPLAY_SUPPORT
#define _3P_SKEW_LR_DISPLAY_SUPPORT                             _ON

#undef _OD_FUNCTION
#define _OD_FUNCTION                                            _OFF

#undef _DISPLAY_ROTATION_SUPPORT
#define _DISPLAY_ROTATION_SUPPORT                               _OFF

#undef _DISPLAY_HOR_MIRROR_SUPPORT
#define _DISPLAY_HOR_MIRROR_SUPPORT                             _OFF

#undef _DISPLAY_VER_MIRROR_SUPPORT
#define _DISPLAY_VER_MIRROR_SUPPORT                             _OFF

#undef _COLOR_FORMAT_CONVERT_FUNCTION
#define _COLOR_FORMAT_CONVERT_FUNCTION                          _OFF

#undef _RGB_QUANTIZATION_RANGE_FUNCTION
#define _RGB_QUANTIZATION_RANGE_FUNCTION                        _OFF

#undef _YCC_QUANTIZATION_RANGE_FUNCTION
#define _YCC_QUANTIZATION_RANGE_FUNCTION                        _OFF

#undef _M_DOMAIN_FORCE_YUV_FORMAT
#define _M_DOMAIN_FORCE_YUV_FORMAT                              _OFF

#undef _LOCAL_CONTRAST_FUNCTION
#define _LOCAL_CONTRAST_FUNCTION                                _OFF

#undef _I_DITHER_FUNCTION
#define _I_DITHER_FUNCTION                                      _OFF

#undef _D_DITHER_FUNCTION
#define _D_DITHER_FUNCTION                                      _OFF

#undef _GAMMA_FUNCTION
#define _GAMMA_FUNCTION                                         _OFF

#undef _PCM_FUNCTION
#define _PCM_FUNCTION                                           _OFF

#undef _ULTRA_VIVID_FUNCTION
#define _ULTRA_VIVID_FUNCTION                                   _OFF

#undef _DCR_FUNCTION
#define _DCR_FUNCTION                                           _OFF

#undef _DCC_FUNCTION
#define _DCC_FUNCTION                                           _OFF

#undef _DCC_HISTOGRM_INFO_FUNCTION
#define _DCC_HISTOGRM_INFO_FUNCTION                             _OFF

#undef _ICM_FUNCTION
#define _ICM_FUNCTION                                           _OFF

#undef _HIGHLIGHT_WINDOW_SUPPORT
#define _HIGHLIGHT_WINDOW_SUPPORT                               _OFF

#undef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _OFF

#undef _RINGING_FILTER_FUNCTION
#define _RINGING_FILTER_FUNCTION                                _OFF

#undef _SHARPNESS_FUNCTION
#define _SHARPNESS_FUNCTION                                     _OFF

#undef _CONTRAST_FUNCTION
#define _CONTRAST_FUNCTION                                      _OFF

#undef _BRIGHTNESS_FUNCTION
#define _BRIGHTNESS_FUNCTION                                    _OFF

#undef _GLOBAL_HUE_SATURATION_FUNCTION
#define _GLOBAL_HUE_SATURATION_FUNCTION                         _OFF

#undef _OGC_FUNCTION
#define _OGC_FUNCTION                                           _OFF

#undef _OCC_FUNCTION
#define _OCC_FUNCTION                                           _OFF

#undef _OGC_DICOM_FUNCTION
#define _OGC_DICOM_FUNCTION                                     _OFF

#undef _UNIFORMITY_FUNCTION
#define _UNIFORMITY_FUNCTION                                    _OFF

#undef _FLASH_WRITE_FUNCTION_SUPPORT
#define _FLASH_WRITE_FUNCTION_SUPPORT                           _OFF

#undef _FLASH_READ_FUNCTION_SUPPORT
#define _FLASH_READ_FUNCTION_SUPPORT                            _OFF

#undef _ASPECT_ORIGINAL_MODE_SUPPORT
#define _ASPECT_ORIGINAL_MODE_SUPPORT                           _OFF

#undef _INSTANT_TIMER_EVENT_0
#define _INSTANT_TIMER_EVENT_0                                  _OFF

#undef _INSTANT_TIMER_EVENT_1
#define _INSTANT_TIMER_EVENT_1                                  _OFF

#undef _LOCAL_DIMMING_FUNCTION
#define _LOCAL_DIMMING_FUNCTION                                 _OFF

#undef _GLOBAL_DIMMING_FUNCTION
#define _GLOBAL_DIMMING_FUNCTION                                _OFF

#undef _ADCNR_SUPPORT
#define _ADCNR_SUPPORT                                          _OFF

#undef _DIG_FILTER_PHASE_SUPPORT
#define _DIG_FILTER_PHASE_SUPPORT                               _OFF

#undef _DIG_FILTER_NSMEAR_SUPPORT
#define _DIG_FILTER_NSMEAR_SUPPORT                              _OFF

#undef _DIG_FILTER_PSMEAR_SUPPORT
#define _DIG_FILTER_PSMEAR_SUPPORT                              _OFF

#undef _DIG_FILTER_NRING_SUPPORT
#define _DIG_FILTER_NRING_SUPPORT                               _OFF

#undef _DIG_FILTER_PRING_SUPPORT
#define _DIG_FILTER_PRING_SUPPORT                               _OFF

#undef _DIG_FILTER_ENHANCE_PHASE_SUPPORT
#define _DIG_FILTER_ENHANCE_PHASE_SUPPORT                       _OFF

#undef _COLOR_DEMO_SUPPORT
#define _COLOR_DEMO_SUPPORT                                     _OFF

#undef _BORDER_WINDOW_SUPPORT
#define _BORDER_WINDOW_SUPPORT                                  _OFF

#undef _DM_FUNCTION
#define _DM_FUNCTION                                            _OFF

//--------------------------------------------------
// Macro of Seven-segment display
//--------------------------------------------------
#define SET_LED1_a(x)                                           {SET_GPIO_PIN_F9(x);}
#define SET_LED1_b(x)                                           {SET_GPIO_PIN_AL13(x);}
#define SET_LED1_c(x)                                           {SET_GPIO_PIN_AM14(x);}
#define SET_LED1_d(x)                                           {SET_GPIO_PIN_E9(x);}
#define SET_LED1_e(x)                                           {SET_GPIO_PIN_D9(x);}
#define SET_LED1_f(x)                                           {SET_GPIO_PIN_A8(x);}
#define SET_LED1_g(x)                                           {SET_GPIO_PIN_C8(x);}

#define SET_LED2_a(x)                                           {SET_GPIO_PIN_AJ14(x);}
#define SET_LED2_b(x)                                           {SET_GPIO_PIN_AK14(x);}
#define SET_LED2_c(x)                                           {SET_GPIO_PIN_C7(x);}
#define SET_LED2_d(x)                                           {SET_GPIO_PIN_AM15(x);}
#define SET_LED2_e(x)                                           {SET_GPIO_PIN_AM13(x);}
#define SET_LED2_f(x)                                           {SET_GPIO_PIN_AG18(x);}
#define SET_LED2_g(x)                                           {SET_GPIO_PIN_AJ13(x);}

#define GET_LED1_DP(x)                                          (GET_GPIO_PIN_AL14())
#define SET_LED1_DP(x)                                          {SET_GPIO_PIN_AL14(x);}

#define GET_LED2_DP(x)                                          (GET_GPIO_PIN_A7())
#define SET_LED2_DP(x)                                          {SET_GPIO_PIN_A7(x);}

#define _LED1                                                   0
#define _LED2                                                   1

#define SET_BUZZER(x)                                           {SET_GPIO_PIN_B8(x);} // Pin_B8

#define PCB_LED_DISPLAY_0(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_OFF);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_OFF);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_1(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_OFF);\
                                                                        SET_LED1_b(_LED_OFF);\
                                                                        SET_LED1_c(_LED_OFF);\
                                                                        SET_LED1_d(_LED_OFF);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_OFF);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_OFF);\
                                                                        SET_LED2_b(_LED_OFF);\
                                                                        SET_LED2_c(_LED_OFF);\
                                                                        SET_LED2_d(_LED_OFF);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_OFF);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_2(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_OFF);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_OFF);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_OFF);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_OFF);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_3(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_OFF);\
                                                                        SET_LED1_c(_LED_OFF);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_OFF);\
                                                                        SET_LED2_c(_LED_OFF);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_4(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_OFF);\
                                                                        SET_LED1_b(_LED_OFF);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_OFF);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_OFF);\
                                                                        SET_LED2_b(_LED_OFF);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_OFF);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_5(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_OFF);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_OFF);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_OFF);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_OFF);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_6(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_OFF);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_OFF);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_7(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_OFF);\
                                                                        SET_LED1_b(_LED_OFF);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_OFF);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_OFF);\
                                                                        SET_LED2_b(_LED_OFF);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_OFF);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_8(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_9(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_OFF);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_OFF);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_A(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_OFF);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_OFF);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_B(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_OFF);\
                                                                        SET_LED1_e(_LED_OFF);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_OFF);\
                                                                        SET_LED2_e(_LED_OFF);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_C(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_OFF);\
                                                                        SET_LED1_f(_LED_OFF);\
                                                                        SET_LED1_g(_LED_OFF);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_OFF);\
                                                                        SET_LED2_f(_LED_OFF);\
                                                                        SET_LED2_g(_LED_OFF);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_D(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_OFF);\
                                                                        SET_LED1_d(_LED_OFF);\
                                                                        SET_LED1_e(_LED_ON);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_ON);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_OFF);\
                                                                        SET_LED2_d(_LED_OFF);\
                                                                        SET_LED2_e(_LED_ON);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_ON);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_E(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_ON);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_OFF);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_OFF);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_ON);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_OFF);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_OFF);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_F(x)                                    {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_OFF);\
                                                                        SET_LED1_b(_LED_ON);\
                                                                        SET_LED1_c(_LED_ON);\
                                                                        SET_LED1_d(_LED_ON);\
                                                                        SET_LED1_e(_LED_OFF);\
                                                                        SET_LED1_f(_LED_ON);\
                                                                        SET_LED1_g(_LED_OFF);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_OFF);\
                                                                        SET_LED2_b(_LED_ON);\
                                                                        SET_LED2_c(_LED_ON);\
                                                                        SET_LED2_d(_LED_ON);\
                                                                        SET_LED2_e(_LED_OFF);\
                                                                        SET_LED2_f(_LED_ON);\
                                                                        SET_LED2_g(_LED_OFF);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define PCB_LED_DISPLAY_NONE(x)                                 {\
                                                                    if((x) == _LED1)\
                                                                    {\
                                                                        SET_LED1_a(_LED_OFF);\
                                                                        SET_LED1_b(_LED_OFF);\
                                                                        SET_LED1_c(_LED_OFF);\
                                                                        SET_LED1_d(_LED_OFF);\
                                                                        SET_LED1_e(_LED_OFF);\
                                                                        SET_LED1_f(_LED_OFF);\
                                                                        SET_LED1_g(_LED_OFF);\
                                                                        SET_LED1_DP(_LED_OFF);\
                                                                    }\
                                                                    else\
                                                                    {\
                                                                        SET_LED2_a(_LED_OFF);\
                                                                        SET_LED2_b(_LED_OFF);\
                                                                        SET_LED2_c(_LED_OFF);\
                                                                        SET_LED2_d(_LED_OFF);\
                                                                        SET_LED2_e(_LED_OFF);\
                                                                        SET_LED2_f(_LED_OFF);\
                                                                        SET_LED2_g(_LED_OFF);\
                                                                        SET_LED2_DP(_LED_OFF);\
                                                                    }\
                                                                }

#define BUZZER_BEEP(x)                                          {\
                                                                    BYTE ucBeepIndex = 0;\
                                                                    for(; ucBeepIndex < (x); ucBeepIndex++)\
                                                                    {\
                                                                        ScalerTimerDelayXms(50);\
                                                                        SET_BUZZER(_ON);\
                                                                        ScalerTimerDelayXms(50);\
                                                                        SET_BUZZER(_OFF);\
                                                                    }\
                                                                }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerQC7SegmentDisplay(BYTE ucNum);

