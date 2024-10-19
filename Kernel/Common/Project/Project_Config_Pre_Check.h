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
// ID Code      : Project_Config_Pre_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_CONFIG_PRE_CHECK_H__
#define __PROJECT_CONFIG_PRE_CHECK_H__

#ifndef _SHARPNESS_FUNCTION
#warning "_COLOR_SHARPNESS_FUNCTION Should Be Defined!!!"
#endif

#ifndef _CONTRAST_FUNCTION
#warning "_COLOR_CONTRAST_FUNCTION Should Be Defined!!!"
#endif

#ifndef _BRIGHTNESS_FUNCTION
#warning "_COLOR_BRIGHTNESS_FUNCTION Should Be Defined!!!"
#endif

#ifdef _FLASH_ACCESS_FUNCTION_SUPPORT
#warning "_FLASH_ACCESS_FUNCTION_SUPPORT Should Be Replace by _FLASH_WRITE_FUNCTION_SUPPORT & _FLASH_READ_FUNCTION_SUPPORT!!!"
#endif // End of #ifdef _FLASH_ACCESS_FUNCTION_SUPPORT

//--------------------------------------------------
// DP Check
//--------------------------------------------------
#ifdef _DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT
#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
#ifndef _DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT
#warning "_DP_EDID_COLOR_DEPTH_BITS_PER_COMPONENT Should Be Defined!!!"
#endif
#endif
#endif

//--------------------------------------------------
// HDMI Check
//--------------------------------------------------
#ifdef _HDMI_SINK_RTK_ID_STRING_H
#if((_HDMI_SINK_RTK_ID_STRING_H & 0xF0) != 0x20)
#warning "_HDMI_SINK_RTK_ID_STRING_H != 0x20, MM1 RTD Number Should start from 0x2xxx When VID = Realtek"
#endif
#endif

//--------------------------------------------------
// OGC and OCC (On-Line Calibration) Check
//--------------------------------------------------
#ifdef _SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT
#if(_SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON)
#ifndef _OGC_OCC_VERIFY_REPORT_BANK
#warning "_OGC_OCC_VERIFY_REPORT_BANK shoulde be defined when _SAVE_OGC_OCC_VERIFY_REPORT_SUPPORT == _ON!!!"
#endif
#endif
#endif

#ifdef _OCC_RGB_3D_GAMMA_SUPPORT
#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
#ifndef _OCC_RGB_3D_GAMMA_FLASH_BANK0
#warning "_OCC_RGB_3D_GAMMA_FLASH_BANK0 shoulde be defined when _OCC_RGB_3D_GAMMA_SUPPORT == _ON!!!"
#endif
#endif
#endif

#endif // End of #ifndef __PROJECT_CONFIG_PRE_CHECK_H__
