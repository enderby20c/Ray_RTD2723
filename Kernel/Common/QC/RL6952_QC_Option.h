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
// ID Code      : RL6952_QC_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// Notify QC fail ID
#define PCB_QC_NOTIFY(id)                                       {\
                                                                    ScalerQCExtBoard7SegmentDisplay(id, _QC_EXT_LED_MODE_HEX);\
                                                                }

// External debug board GPIO initial process
#define EXT_DEBUG_BOARD_GPIO_INITIAL()                          {\
                                                                    ScalerQCExtBoardInitialProc();\
                                                                }

// For testing with RLE0638
#undef _INPUTCLOCK_RANG_DVI
#define _INPUTCLOCK_RANG_DVI                                    6000

// Force #define settings for QC flow
#undef _2P_PIP_DISPLAY_SUPPORT
#define _2P_PIP_DISPLAY_SUPPORT                                 _ON

#undef _2P_PBP_LR_DISPLAY_SUPPORT
#define _2P_PBP_LR_DISPLAY_SUPPORT                              _ON

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

#undef _SCM_SUPPORT
#define _SCM_SUPPORT                                            _OFF

#undef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _OFF

#undef _HIGHLIGHT_WINDOW_SUPPORT
#define _HIGHLIGHT_WINDOW_SUPPORT                               _OFF

#undef _SHARPNESS_FUNCTION
#define _SHARPNESS_FUNCTION                                     _OFF

#undef _CONTRAST_FUNCTION
#define _CONTRAST_FUNCTION                                      _OFF

#undef _BRIGHTNESS_FUNCTION
#define _BRIGHTNESS_FUNCTION                                    _OFF

#undef _LOCAL_CONTRAST_FUNCTION
#define _LOCAL_CONTRAST_FUNCTION                                _OFF

#undef _GLOBAL_HUE_SATURATION_FUNCTION
#define _GLOBAL_HUE_SATURATION_FUNCTION                         _OFF

#undef _YPEAKING_FUNCTION
#define _YPEAKING_FUNCTION                                      _OFF

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

#undef _COLOR_DEMO_SUPPORT
#define _COLOR_DEMO_SUPPORT                                     _OFF

#undef _BORDER_WINDOW_SUPPORT
#define _BORDER_WINDOW_SUPPORT                                  _OFF


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


