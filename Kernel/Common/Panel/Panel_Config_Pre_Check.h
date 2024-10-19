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
// ID Code      : Panel_Config_Pre_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PANEL_CONFIG_PRE_CHECK_H__
#define __PANEL_CONFIG_PRE_CHECK_H__

//--------------------------------------------------
// Definitions for eDP Panel Configuration
//--------------------------------------------------
#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(_PANEL_PIXEL_TYPE == _PANEL_PIXEL_OLED)
#ifndef _PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE
#warning "User Should Check OLED AC_DET Control Type, It Would Affect PCB_BACKLIGHT_POWER_PIN Behavior"
#endif
#endif
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)

#ifndef _PANEL_DPTX_LINK_RATE
#warning "Link Rate for eDP Panel isn't define by User"
#endif

#ifndef _PANEL_DPTX_LANE_NUMBER
#warning "Lane Number for eDP Panel isn't define by User"
#endif

#ifndef _PANEL_DPTX_PANEL_SECTION
#warning "Panel Section for eDP Panel isn't define by User"
#endif

#ifdef _PANEL_DPTX_FORCE_OUTPUT_SUPPORT
#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)

#ifndef _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING
#warning "Please Define _PANEL_DPTX_FORCE_MSA_ENHANCE_FRAMING at Panel.h for DPTX Force Output. Refer to the output of debug message _DEBUG_MESSAGE_CHECK_DISP_SETTING in ScalerDisplayDpTxXLinkConfig."
#endif

#ifndef _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD
#warning "Please Define _PANEL_DPTX_FORCE_MSA_DOWN_SPREAD at Panel.h for DPTX Force Output. Refer to the output of debug message _DEBUG_MESSAGE_CHECK_DISP_SETTING in ScalerDisplayDpTxXLinkConfig."
#endif

#ifndef _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP
#warning "Please Define _PANEL_DPTX_FORCE_FRAMING_CHANGE_CAP at Panel.h for DPTX Force Output. Refer to the output of debug message _DEBUG_MESSAGE_CHECK_DISP_SETTING in ScalerDisplayDpTxXLinkConfig."
#endif

#ifndef _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP
#warning "Please Define _PANEL_DPTX_FORCE_ALTERNATE_SR_CAP at Panel.h for DPTX Force Output. Refer to the output of debug message _DEBUG_MESSAGE_CHECK_DISP_SETTING in ScalerDisplayDpTxXLinkConfig."
#endif

#endif
#endif

#endif

///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// Display HDR Option
//--------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#ifndef _PANEL_MAX_LUMINANCE
#warning "_PANEL_MAX_LUMINANCE should be defined at Panel.h for HDR10"
#endif

#ifndef _PANEL_MAX_FRAME_AVERAGE_LUMINANCE
#warning "_PANEL_MAX_FRAME_AVERAGE_LUMINANCE should be defined at Panel.h for HDR10"
#endif
#endif

//--------------------------------------------------
// HDR User Define Panel Max Lv
//--------------------------------------------------
#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
#ifndef _PANEL_MAX_USER_DEFINE_LUMINANCE
#warning "_PANEL_MAX_USER_DEFINE_LUMINANCE should be defined at Panel.h when _HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT is _ON"
#endif
#endif

//--------------------------------------------------
// Definitions for FREESYNC Panel Parameters
//--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
#ifndef _PANEL_DP_FREESYNC_MAX_FRAME_RATE
#warning "_PANEL_DP_FREESYNC_MAX_FRAME_RATE should be defined at Panel.h for Freesync"
#endif

#ifndef _PANEL_DP_FREESYNC_MIN_FRAME_RATE
#warning "_PANEL_DP_FREESYNC_MIN_FRAME_RATE should be defined at Panel.h for Freesync"
#endif
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#ifndef _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE
#warning "_PANEL_HDMI_FREESYNC_MAX_FRAME_RATE should be defined at Panel.h for Freesync"
#endif

#ifndef _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE
#warning "_PANEL_HDMI_FREESYNC_MIN_FRAME_RATE should be defined at Panel.h for Freesync"
#endif
#endif

//--------------------------------------------------
// Definitions for VRR Panel Parameters
//--------------------------------------------------

#if(_HDMI21_GAMING_VRR_SUPPORT == _ON)
#ifndef _PANEL_HDMI21_VRR_MAX_FRAME_RATE
#warning "_PANEL_HDMI21_VRR_MAX_FRAME_RATE should be defined at Panel.h for Freesync"
#endif

#ifndef _PANEL_HDMI21_VRR_MIN_FRAME_RATE
#warning "_PANEL_HDMI21_VRR_MIN_FRAME_RATE should be defined at Panel.h for Freesync"
#endif
#endif

//-------------------------------------------------
// Definitions for dhfreq fine tune
//-------------------------------------------------
#ifdef _PANEL_HFREQ_FINE_TUNE
#if(_PANEL_HFREQ_FINE_TUNE == _ON)

#ifndef _PANEL_DH_FREQ_MAX
#warning "_PANEL_DH_FREQ_MAX should be defined at Panel.h when _PANEL_HFREQ_FINE_TUNE is _ON"
#endif

#ifndef _PANEL_DH_FREQ_MIN
#warning "_PANEL_DH_FREQ_MIN should be defined at Panel.h when _PANEL_HFREQ_FINE_TUNE is _ON"
#endif

#endif
#endif

//-------------------------------------------------
// Definitions for Panel Pixel Type
//-------------------------------------------------
#ifndef _PANEL_PIXEL_TYPE
#warning "_PANEL_PIXEL_TYPE should be defined at Panel.h"
#endif

#endif // End of #ifndef __PANEL_CONFIG_PRE_CHECK_H__
