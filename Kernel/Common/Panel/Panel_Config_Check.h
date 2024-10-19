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
// ID Code      : Panel_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PANEL_CONFIG_CHECK_H__
#define __PANEL_CONFIG_CHECK_H__

#if(_PANEL_EXIST_MULTIPANEL == _OFF)

#if((_PANEL_PIXEL_TYPE == _PANEL_PIXEL_OLED) && (_PANEL_OLED_BACKLIGHT_AC_DET_CONTROL_TYPE == _PANEL_OLED_AC_DET_CTRL_WITH_SEQ))
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
#warning "When _PANEL_OLED_AC_DET_CTRL_WITH_SEQ, _DISPLAY_PREVENT_GARBAGE_METHOD Shold Not Be _GARBAGE_PREVENT_BY_BACKLIGHT"
#endif
#endif

#if(_PANEL_DH_TOTAL_MAX > _HW_DIS_TIMING_GEN_HTOTAL_BIT)
#warning "IC HW Not Support, _PANEL_DH_TOTAL_MAX Exceeds the Size of _HW_DIS_TIMING_GEN_HTOTAL_BIT"
#endif

#if(_PANEL_DV_TOTAL_MAX > _HW_DIS_TIMING_GEN_VTOTAL_BIT)
#warning "IC HW Not Support, _PANEL_DV_TOTAL_MAX Exceeds the Size of _HW_DIS_TIMING_GEN_VTOTAL_BIT"
#endif

#if(_SCALER_TYPE == _RL6829_SERIES)

#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH)
#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 1400000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 700M (2 PATH)"
#endif
#elif(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 2800000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 1400M (4 PATH)"
#endif
#endif

#elif(_SCALER_TYPE == _RL6952_SERIES)
#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 1200000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 600M (2 PATH)"
#endif
#elif(_SCALER_TYPE == _RL6978_SERIES)
#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 1200000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 600M (2 PATH)"
#endif
#endif

#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#warning "Rotation/ Mirror not supported under panel of Front_Back mode!!! _DISPLAY_ROTATION_SUPPORT Set _OFF"
#endif

#if((_DISPLAY_VER_MIRROR_SUPPORT == _ON) || (_DISPLAY_HOR_MIRROR_SUPPORT == _ON))
#warning "Mirror not supported under panel of Front_Back mode!!! _DISPLAY_VER_MIRROR_SUPPORT/ _DISPLAY_HOR_MIRROR_SUPPORT Set _OFF"
#endif

#endif

//--------------------------------------------------
// Modification of Panel Parameters
//--------------------------------------------------
#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)

#if((_PANEL_DH_SYNC_WIDTH % 4) != 0)
#warning "_PANEL_DH_SYNC_WIDTH Should Be Multiple of 4 in Front_Back Mode"
#endif

#if(_PANEL_DH_START < 72)
#warning "_PANEL_DH_START Should Be Larger than 72 in Front_Back Mode"
#endif

#if((_PANEL_DH_START % 8) != 0)
#warning "_PANEL_DH_START Should Be Multiple of 8 in Front_Back Mode"
#endif

#if((_PANEL_DH_WIDTH % 4) != 0)
#warning "_PANEL_DH_WIDTH Should Be Multiple of 4 in Front_Back Mode"
#endif

#if((_PANEL_DH_END % 4) != 0)
#warning "_PANEL_DH_END Should Be Multiple of 4 in Front_Back Mode"
#endif

#if((_PANEL_DH_TOTAL % 8) != 0)
#warning "_PANEL_DH_TOTAL Should Be Multiple of 8 in Front_Back Mode"
#endif

#if((_PANEL_DH_TOTAL_MAX % 8) != 0)
#warning "_PANEL_DH_TOTAL_MAX Should Be Multiple of 8 in Front_Back Mode"
#endif

#if((_PANEL_DH_TOTAL_MIN % 8) != 0)
#warning "_PANEL_DH_TOTAL_MIN Should Be Multiple of 8 in Front_Back Mode"
#endif

#elif(GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH)

#if((_PANEL_DH_SYNC_WIDTH % 2) != 0)
#warning "_PANEL_DH_SYNC_WIDTH Should Be Multiple of 2 in Even_Odd Mode"
#endif

#if(_PANEL_DH_START < 36)
#warning "_PANEL_DH_START Should Be Larger than 36 in Even_Odd Mode"
#endif

#if((_PANEL_DH_START % 2) != 0)
#warning "_PANEL_DH_START Should Be Multiple of 2 in Even_Odd Mode"
#endif

#if((_PANEL_DH_WIDTH % 2) != 0)
#warning "_PANEL_DH_WIDTH Should Be Multiple of 2 in Even_Odd Mode"
#endif

#if((_PANEL_DH_END % 2) != 0)
#warning "_PANEL_DH_END Should Be Multiple of 2 in Even_Odd Mode"
#endif

#if((_PANEL_DH_TOTAL % 4) != 0)
#warning "_PANEL_DH_TOTAL Should Be Multiple of 4 in Even_Odd Mode"
#endif

#if((_PANEL_DH_TOTAL_MAX % 4) != 0)
#warning "_PANEL_DH_TOTAL_MAX Should Be Multiple of 4 in Even_Odd Mode"
#endif

#if((_PANEL_DH_TOTAL_MIN % 4) != 0)
#warning "_PANEL_DH_TOTAL_MIN Should Be Multiple of 4 in Even_Odd Mode"
#endif

#else

#if(_PANEL_DH_START < 18)
#warning "_PANEL_DH_START Should Be Larger than 18 in Single Mode"
#endif

#if((_PANEL_DH_TOTAL % 2) != 0)
#warning "_PANEL_DH_TOTAL Should Be Multiple of 2 in Single Mode"
#endif

#if((_PANEL_DH_TOTAL_MAX % 2) != 0)
#warning "_PANEL_DH_TOTAL_MAX Should Be Multiple of 2 in Single Mode"
#endif

#if((_PANEL_DH_TOTAL_MIN % 2) != 0)
#warning "_PANEL_DH_TOTAL_MIN Should Be Multiple of 2 in Single Mode"
#endif

#endif // End of #if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)


#if(_PANEL_DV_SYNC_HEIGHT < 2)
#warning "_PANEL_DV_SYNC_HEIGHT Should Be Larger than 2"
#endif

#if(_PANEL_DV_START < 2)
#warning "_PANEL_DV_START Should Be Larger than 2"
#endif

#if((GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH) && ((_3P_FLAG_DISPLAY_SUPPORT == _ON) || (_2P_PIP_DISPLAY_SUPPORT == _ON)))
#if(_PANEL_DV_START < 10)
#warning "_PANEL_DV_START Should be larger than 10 in order to tune preread when GET_DISPLAY_MODE() == _DISPLAY_MODE_3P_FLAG or _2P_PIP_DISPLAY_SUPPORT"
#endif
#endif

#if(_PANEL_DH_TOTAL_MIN <= (_PANEL_DH_START + _PANEL_DH_WIDTH))
#warning "_PANEL_DH_TOTAL_MIN Should Be Large Than (_PANEL_DH_START + _PANEL_DH_WIDTH) + H front porch, Check Panel H front porch limit !!"
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_PANEL_DH_TOTAL_MIN <= (_PANEL_DH_START + _PANEL_DH_WIDTH + _PANEL_OUTPUT_NUM))
#warning "_PANEL_DH_TOTAL_MIN Should Be Large Than (_PANEL_DH_START + _PANEL_DH_WIDTH  + _PANEL_OUTPUT_NUM) + H front porch, when _EAGLE_SIGHT_SUPPORT _ON, Check Panel H front porch limit !!"
#endif

#if(_PANEL_DV_TOTAL_MIN <= (_PANEL_DV_START + _PANEL_DV_HEIGHT + _PANEL_FRONT_PORCH_LIMIT + 2))
#warning "_PANEL_DV_TOTAL_MIN Should Be Large Than (_PANEL_DV_START + _PANEL_DV_HEIGHT + _PANEL_FRONT_PORCH_LIMIT), when _EAGLE_SIGHT_SUPPORT _ON, Check Panel V front porch limit !!"
#endif
#endif

#if(_PANEL_DH_SYNC_WIDTH >= _PANEL_DH_START)
#warning "_PANEL_DH_SYNC_WIDTH Should Be Less Than _PANEL_DH_START"
#endif

#if(_PANEL_DV_TOTAL_MIN <= (_PANEL_DV_START + _PANEL_DV_HEIGHT + _PANEL_FRONT_PORCH_LIMIT))
#warning "_PANEL_DV_TOTAL_MIN Should Be Large Than (_PANEL_DV_START + _PANEL_DV_HEIGHT + _PANEL_FRONT_PORCH_LIMIT), Check Panel V front porch limit !!"
#endif

#if(_PANEL_DV_SYNC_HEIGHT >= _PANEL_DV_START)
#warning "_PANEL_DV_SYNC_HEIGHT Should Be Less Than _PANEL_DV_START"
#endif

#if(_PANEL_DV_TOTAL_MAX > _HW_DIS_TIMING_GEN_VTOTAL_BIT)
#warning "_PANEL_DV_TOTAL_MAX Should Be Less Than DVtotal max count"
#endif

#if((_PANEL_DH_TOTAL % _PANEL_OUTPUT_NUM) != 0)
#warning "DHTotal Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_TOTAL_MAX % _PANEL_OUTPUT_NUM) != 0)
#warning "DHTotal Max Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_TOTAL_MIN % _PANEL_OUTPUT_NUM) != 0)
#warning "DHTotal Min Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_START % _PANEL_OUTPUT_NUM) != 0)
#warning "DHStart Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_WIDTH % _PANEL_OUTPUT_NUM) != 0)
#warning "DHWidth Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_END % _PANEL_OUTPUT_NUM) != 0)
#warning "DHWidth End Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_SYNC_WIDTH % _PANEL_OUTPUT_NUM) != 0)
#warning "DHSync Width Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DV_TOTAL > _PANEL_DV_TOTAL_MAX) || (_PANEL_DV_TOTAL < _PANEL_DV_TOTAL_MIN))
#warning "_PANEL_DV_TOTAL should be in the range from _PANEL_DV_TOTAL_MIN to _PANEL_DV_TOTAL_MAX"
#endif

#if((_PANEL_DH_TOTAL > _PANEL_DH_TOTAL_MAX) || (_PANEL_DH_TOTAL < _PANEL_DH_TOTAL_MIN))
#warning "_PANEL_DH_TOTAL should be in the range from _PANEL_DH_TOTAL_MIN to _PANEL_DH_TOTAL_MAX"
#endif

#if((_PANEL_PIXEL_CLOCK > _PANEL_PIXEL_CLOCK_MAX) || (_PANEL_PIXEL_CLOCK < _PANEL_PIXEL_CLOCK_MIN))
#warning "_PANEL_PIXEL_CLOCK should be in the range from _PANEL_PIXEL_CLOCK_MIN to _PANEL_PIXEL_CLOCK_MAX"
#endif

#if(_PANEL_STYLE == _PANEL_LVDS)

#if(_PANEL_LVDS_PANEL_SECTION > _PANEL_LVDS_OUTPUT_PORT)
#warning "_PANEL_LVDS_PANEL_SECTION Should Be Less than or Equal to _PANEL_LVDS_OUTPUT_PORT"
#endif

#if(_PANEL_LVDS_OUTPUT_PORT > _LVDS_4_PORT)
#warning "LVDS Output Port Shold Be Less Than or Equal to 4-Port"
#endif

#elif(_PANEL_STYLE == _PANEL_VBO)

#if(_SCALER_TYPE == _RL6829_SERIES)

#if(_PANEL_VBO_OUTPUT_PORT == _VBO_1_DATA_LANE)
#warning "VBO Output Port can not support 1-Port"
#endif
#endif

#if(_PANEL_VBO_PANEL_SECTION > _PANEL_VBO_OUTPUT_PORT)
#warning "_PANEL_VBO_PANEL_SECTION Should Be Less than or Equal to _PANEL_VBO_OUTPUT_PORT"
#endif

#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_PANEL_OFF)
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
#warning "_PANEL_POW_SEQ_FAST_MODE Should Be Off When _PANEL_VBO_CHANGE_CLK_RESET_TYPE reset by Panel Off"
#endif
#endif

#if((_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_BY_M_DOMAIN_FREE_RUN) && (_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE != _ON))
#warning "_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE Should Be On When _VBO_CHANGE_CLK_BY_M_DOMAIN_FREE_RUN"
#endif

#if(_PANEL_VBO_OUTPUT_PORT <= _VBO_2_DATA_LANE)
#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
#warning "VBO can not support 1/2 port in frontback mode"
#endif
#endif

#elif(_PANEL_STYLE == _PANEL_DPTX)

//--------------------------------------------------
// Definitions for Panel Configuration
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6952_SERIES) || (_SCALER_TYPE == _RL6978_SERIES))
#if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16)
#warning "Display Output Tx Can't Support 16 lane"
#endif

#if((_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX0_PORT) || (_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX3_PORT))
#warning "Display Output Tx Can't Support Tx0 or Tx3, only support Tx1 or Tx2"
#endif
#endif

#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
#if(_PANEL_DPTX_HPD_DETECT == _OFF)
#warning "_PANEL_DPTX_HPD_DETECT Should Be On When _PANEL_DPTX_IRQ_HPD_DETECT Define ON"
#endif
#endif

#if((_SCALER_TYPE == _RL6952_SERIES) || (_SCALER_TYPE == _RL6978_SERIES))
#if(((_PANEL_DPTX_LANE_NUMBER <= _PANEL_DPTX_LANE_NUMBER_4) && (_PANEL_DPTX_PANEL_SECTION != _DPTX_PANEL_1_SECTION)) ||\
    ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) && ((_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_1_SECTION) || (_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_8_SECTION))))
#warning "Panel Lane Number <= 4 lane, Section define 1 Section ; Panel Lane Number = 8 lane, Section define 2 Section or 4 section"
#endif
#else
#if(((_PANEL_DPTX_LANE_NUMBER <= _PANEL_DPTX_LANE_NUMBER_4) && (_PANEL_DPTX_PANEL_SECTION != _DPTX_PANEL_1_SECTION)) ||\
    ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8) && (_PANEL_DPTX_PANEL_SECTION != _DPTX_PANEL_2_SECTION)) ||\
    ((_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_16) && ((_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_1_SECTION) || (_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_2_SECTION))))
#warning "Panel Lane Number <= 4 lane, Section define 1 Section ; Panel Lane Number = 8 lane, Section define 2 Section ; Panel Lane Number = 16 lane, Section define 8 Section or 4 section"
#endif
#endif

#if(_DRR_SUPPORT == _ON)
#if(_PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN == _DISABLE)
#warning "_PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN Should Be Enable When _DRR_SUPPORT Define ON"
#endif
#else
#if(_PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN == _ENABLE)
#warning "_PANEL_DPTX_MSA_TIMING_PAR_IGNORE_EN Should Be Disable When _DRR_SUPPORT Define OFF"
#endif
#endif

#if((_PANEL_DH_SYNC_WIDTH) <= ((4UL * _PANEL_PIXEL_CLOCK_MAX_KHZ) / (27UL * 1000UL * _PANEL_DPTX_LINK_RATE)))
#warning "_PANEL_DH_SYNC_WIDTH should be more than (4 * _PANEL_PIXEL_CLOCK_MAX_KHZ / (_PANEL_DPTX_LINK_RATE * 27000))"
#endif

#endif

#if(_PANEL_LAST_LINE_MAX >= _PANEL_DH_TOTAL_MIN)
#warning "_PANEL_LAST_LINE_MAX should be less than _PANEL_DH_TOTAL_MIN"
#endif

#if(_PANEL_PIXEL_CLOCK_MAX_SPREAD <= _PANEL_PIXEL_CLOCK_MIN_SPREAD)
#warning "Enlarge _PANEL_PIXEL_CLOCK_MAX_KHZ/ _PANEL_PIXEL_CLOCK_MIN_KHZ Range, or _DPLL_JITTER_MARGIN Select _DPLL_NO_JITTER_MARGIN"
#endif

#if((_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000) > _PANEL_PIXEL_CLOCK_MAX_SPREAD)
#warning "(_PANEL_DH_TOTAL * _PANEL_DV_TOTAL * _PANEL_TYP_FRAME_RATE) should be less than Pixel clk max with SSCG"
#endif

#if((_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000) < _PANEL_PIXEL_CLOCK_MIN_SPREAD)
#warning "(_PANEL_DH_TOTAL * _PANEL_DV_TOTAL * _PANEL_TYP_FRAME_RATE) should be larger than Pixel clk min with SSCG"
#endif

// margin suggest larger than 20 for narrow range frequency
#if(((_PANEL_MAX_FRAME_RATE - _PANEL_MIN_FRAME_RATE) < (_PANEL_TYP_FRAME_RATE >> 4)) && (_PANEL_FRAME_SYNC_MARGIN < 20))
#warning "_PANEL_FRAME_SYNC_MARGIN Suggest Larger than 20"
#endif

#if(_PANEL_FRAME_RATE_VARIATION_CHECK == _ON)
#if(((_PANEL_DH_TOTAL_MIN * _PANEL_DV_TOTAL_MIN / 100) * _PANEL_MAX_FRAME_RATE * 1005 / 100000) > _PANEL_PIXEL_CLOCK_MAX_SPREAD)
#warning "(_PANEL_DH_TOTAL_MIN * _PANEL_DV_TOTAL_MIN * _PANEL_MAX_FRAME_RATE) should be less than Pixel clk max with SSCG, Enlarge _PANEL_PIXEL_CLOCK_MAX or _DPLL_JITTER_MARGIN Select _DPLL_NO_JITTER_MARGIN"
#endif

#if(((_PANEL_DH_TOTAL_MAX * _PANEL_DV_TOTAL_MAX / 100) * _PANEL_MIN_FRAME_RATE * 995 / 100000) < _PANEL_PIXEL_CLOCK_MIN_SPREAD)
#warning "(_PANEL_DH_TOTAL_MAX * _PANEL_DV_TOTAL_MAX * _PANEL_MIN_FRAME_RATE) should be less than Pixel clk min with SSCG, Reduce _PANEL_PIXEL_CLOCK_MIN or _DPLL_JITTER_MARGIN Select _DPLL_NO_JITTER_MARGIN"
#endif

#else
#if(((_PANEL_DH_TOTAL_MIN * _PANEL_DV_TOTAL_MIN / 100) * _PANEL_MAX_FRAME_RATE / 100) > _PANEL_PIXEL_CLOCK_MAX_SPREAD)
#warning "(_PANEL_DH_TOTAL_MIN * _PANEL_DV_TOTAL_MIN * _PANEL_MAX_FRAME_RATE) should be less than Pixel clk max with SSCG, Enlarge _PANEL_PIXEL_CLOCK_MAX or _DPLL_JITTER_MARGIN Select _DPLL_NO_JITTER_MARGIN"
#endif

#if(((_PANEL_DH_TOTAL_MAX * _PANEL_DV_TOTAL_MAX / 100) * _PANEL_MIN_FRAME_RATE / 100) < _PANEL_PIXEL_CLOCK_MIN_SPREAD)
#warning "(_PANEL_DH_TOTAL_MAX * _PANEL_DV_TOTAL_MAX * _PANEL_MIN_FRAME_RATE) should be less than Pixel clk min with SSCG, Reduce _PANEL_PIXEL_CLOCK_MIN or _DPLL_JITTER_MARGIN Select _DPLL_NO_JITTER_MARGIN"
#endif
#endif

//--------------------------------------------------
// Definitions for FREESYNC Panel Parameters
//--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_PANEL_DRR_FRAME_RATE_VARIATION_CHECK == _ON)
#if(_PANEL_DV_TOTAL_MAX < ((_PANEL_DV_TOTAL * (_PANEL_DP_FREESYNC_MAX_FRAME_RATE * 1005 / 100)) / (_PANEL_DP_FREESYNC_MIN_FRAME_RATE * 995 / 100)))
#warning "_PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * DP FreeSync Vfreq Ratio +/- 0.5%)!"
#endif
#else
#if(_PANEL_DV_TOTAL_MAX < ((_PANEL_DV_TOTAL * _PANEL_DP_FREESYNC_MAX_FRAME_RATE) / _PANEL_DP_FREESYNC_MIN_FRAME_RATE))
#warning "_PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * DP FreeSync Vfreq Ratio)!"
#endif
#endif
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_PANEL_DRR_FRAME_RATE_VARIATION_CHECK == _ON)
#if(_PANEL_DV_TOTAL_MAX < ((_PANEL_DV_TOTAL * (_PANEL_HDMI_FREESYNC_MAX_FRAME_RATE * 1005 / 100)) / (_PANEL_HDMI_FREESYNC_MIN_FRAME_RATE * 995 / 100)))
#warning "_PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * HDMI FreeSync Vfreq Ratio +/- 0.5%)!"
#endif
#else
#if(_PANEL_DV_TOTAL_MAX < ((_PANEL_DV_TOTAL * _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE) / _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE))
#warning "_PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * HDMI FreeSync Vfreq Ratio)!"
#endif
#endif
#endif

//--------------------------------------------------
// Definitions for dhfreq fine tune Panel Parameters
//--------------------------------------------------
#if(_PANEL_HFREQ_FINE_TUNE == _ON)
#if(_PANEL_DH_FREQ_MAX * 1000 < (_PANEL_DV_TOTAL_MIN * _PANEL_MAX_FRAME_RATE))
#warning "_PANEL_DH_FREQ_MAX Should Be Larger than (DVTotal Min * Vfreq Max)!"
#endif

#if(_PANEL_DH_FREQ_MAX > (_PANEL_PIXEL_CLOCK_MAX * 1000 / _PANEL_DH_TOTAL_MIN) * 10)
#warning "_PANEL_DH_FREQ_MAX Should Be Less than (Dclk Max / Htotal Min)!"
#endif

#if(_PANEL_DH_FREQ_MIN * 1000 > (_PANEL_DV_TOTAL_MAX * _PANEL_MIN_FRAME_RATE))
#warning "_PANEL_DH_FREQ_Min Should Be Less than (DVTotal Max * Vfreq Min)!"
#endif

#if(_PANEL_DH_FREQ_MIN < (_PANEL_PIXEL_CLOCK_MIN * 1000 / _PANEL_DH_TOTAL_MAX) * 10)
#warning "_PANEL_DH_FREQ_Min Should Be Larger than (Dclk Min / Htotal Max)!"
#endif
#endif

//--------------------------------------------------
// Definitions for VRR Panel Parameters
//--------------------------------------------------
#if(_HDMI21_GAMING_VRR_SUPPORT == _ON)
#if(_PANEL_DRR_FRAME_RATE_VARIATION_CHECK == _ON)
#if(_PANEL_DV_TOTAL_MAX < ((_PANEL_DV_TOTAL * (_PANEL_HDMI21_VRR_MAX_FRAME_RATE * 1005 / 100)) / (_PANEL_HDMI21_VRR_MIN_FRAME_RATE * 987 / 100)))
#warning "_PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * VRR Vfreq Ratio +0.5 ~ -1.3%)!"
#endif
#else
#if(_PANEL_DV_TOTAL_MAX < ((_PANEL_DV_TOTAL * _PANEL_HDMI21_VRR_MAX_FRAME_RATE) / _PANEL_HDMI21_VRR_MIN_FRAME_RATE))
#warning "_PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * VRR Vfreq Ratio)!"
#endif
#endif
#endif

//--------------------------------------------------
// Definitions for Image Compreesion HW Constraints
//--------------------------------------------------
#if((_M_DOMAIN_IMG_CMP_SUPPORT == _ON) && (_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1))
#if(_PANEL_DH_START <= _HW_M_DOMAIN_IMG_DECMP_HPORCH_LIMIT)
#warning "_PANEL_DH_START should be larger than _HW_M_DOMAIN_IMG_DECMP_HPORCH_LIMIT when _M_DOMAIN_IMG_CMP_SUPPORT is _ON!"
#endif

#if(_M_DOMAIN_IMG_CMP_10_BIT_SUPPORT == _ON)
#if((_M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT == _OFF) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < (((_PANEL_DH_WIDTH >> GET_D_DOMAIN_PATH()) * 12) / 128 / 3)))
#warning "_M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT should be _ON when DH Proch is less than (chunk_size / 16 / 3) = ((slice_hwidth * imc_10b_max_bbp) / 128 / 3)!"
#elif((_M_DOMAIN_IMG_CMP_FORCE_8_BPP_SUPPORT == _ON) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < (((_PANEL_DH_WIDTH >> GET_D_DOMAIN_PATH()) * 8) / 128 / 3)))
#warning "Please contact SDs, DH Proch must be larger than (chunk_size / 16 / 3) = ((slice_hwidth * imc_10b_min_bbp) / 128 / 3) to avoid DEC stuck!"
#endif
#else
#if((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < (((_PANEL_DH_WIDTH >> GET_D_DOMAIN_PATH()) * 8) / 128 / 3))
#warning "Please contact SDs, DH Proch must be larger than (chunk_size / 16 / 3) = ((slice_hwidth * imc_8b_typ_bbp) / 128 / 3) to avoid DEC stuck!"
#endif
#endif
#endif

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#if(_I_DITHER_FUNCTION == _ON)
#if((_HW_IDITHER_TYPE != _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) &&\
    (_HW_IDITHER_TYPE != _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT) &&\
    (_HW_IDITHER_TYPE != _IDITHER_GEN_4_4_SEQ_TRUNCATE_6_4_2_BIT_S3LOAD))
#if((_I_DITHER_MULTI_SEQ_ENABLE == _ENABLE) ||\
    (_I_DITHER_SHARE_SEQ_ENABLE == _ENABLE) ||\
    (_I_DITHER_SERIES_SEQ_ENABLE == _ENABLE) ||\
    (_I_DITHER_SEQ_INV_ENABLE == _ENABLE))
#warning "IDither Multi, Share, Series, Inv Function can't be used by this Gen!"
#endif
#endif

#if(_HW_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT)
#if((_I_DITHER_VALUE_SIGN == _ENABLE) ||\
    (_I_DITHER_V_FRAME_MOD == _ENABLE) ||\
    (_I_DITHER_H_FRAME_MOD == _ENABLE))
#warning "IDither Sign, VModu, HModu Function can't be used by this Gen!"
#endif
#endif

#endif

#if(_UNIFORMITY_FUNCTION == _ON)
#if(((_PANEL_DH_WIDTH / _PANEL_UNIFORMITY_HOR_INTERVAL + 2) * (_PANEL_DV_HEIGHT / _PANEL_UNIFORMITY_VER_INTERVAL + 2) * _PANEL_UNIFORMITY_LEVEL_MAX * 5) > _HW_PANEL_UNIFORMITY_MAX_GAIN_LUT_SIZE)
#if(_PANEL_UNIFORMITY_LEVEL_MAX == _UNIFORMITY_5LEVEL)
#warning "_UNIFORMITY_TABLE_LEVEL Can't Be _UNIFORMITY_5LEVEL!!!"
#elif(_PANEL_UNIFORMITY_LEVEL_MAX == _UNIFORMITY_4LEVEL)
#warning "_UNIFORMITY_TABLE_LEVEL Can't Be _UNIFORMITY_4LEVEL!!!"
#else
#warning "_UNIFORMITY Cant't support this panel!!!"
#endif
#endif
#endif
//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#if(_D_DITHER_FUNCTION == _ON)
#if((_HW_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL) &&\
    (_HW_DDITHER_TYPE != _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) &&\
    (_HW_DDITHER_TYPE != _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#if((_D_DITHER_SERIES_SEQ_ENABLE == _ENABLE) || (_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE))
#warning "DDither Series,Advance Function can't be used by this Gen!"
#endif
#endif

#if(_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
#warning "_DDITHER_GEN_1_6BIT_DITHERTBL don't support 6bit panel!"
#endif
#endif

#if(_HW_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL)
#if((_D_DITHER_V_FRAME_MOD == _ENABLE) || (_D_DITHER_H_FRAME_MOD == _ENABLE))
#warning "DDither H/V Modulation Function can't be used by this Gen!"
#endif
#endif

#if(_D_DITHER_FREERUN_EN_SUPPORT == _ENABLE)
#if((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_PANEL_DISP_BIT_MODE != _PANEL_DISP_18_BIT))
#warning "DDither _D_DITHER_FREERUN_EN_SUPPORT can't be used by this Gen or when Panel is not 18 bit!"
#endif
#endif

#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
#if((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < 120)
#warning "DH Proch must be at least 120!"
#endif
#elif(GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH)
#if((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < 60)
#warning "DH Proch must be at least 60!"
#endif
#else
#if((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < 40)
#warning "DH Proch must be at least 40!"
#endif
#endif
#endif

#if(_OSD_H_DELAY_LIMIT_BYPASS == _ON)
#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
#if(_PANEL_DH_WIDTH > (_HW_FOSD_H_DELAY_MAX * 2)) // 8K (8192)
#if(_PANEL_DH_TOTAL_MAX > 12280)
#warning "Decrease _PANEL_DH_TOTAL_MAX for _OSD_H_DELAY_LIMIT_BYPASS"
#endif
#endif // #if(_PANEL_DH_WIDTH > (_HW_FOSD_H_DELAY_MAX * 2)) // 8K (8192)
#elif(GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH)
#if(_PANEL_DH_WIDTH > _HW_FOSD_H_DELAY_MAX + 5) // EO mode, 4K panel width = 4096
#define _MAX_HCNT_DEN           (2 * _PANEL_DH_TOTAL_MAX + 11)
#define _MAX_HCNT_RTL           (12292)
#define _INIT_HCNT1             (16384 - (_PANEL_DH_WIDTH - 1))
#if(_INIT_HCNT1 < ((_MAX_HCNT_DEN > _MAX_HCNT_RTL) ? (_MAX_HCNT_RTL) : (_MAX_HCNT_DEN)))
#warning "Decrease _PANEL_DH_TOTAL_MAX for _OSD_H_DELAY_LIMIT_BYPASS"
#endif
#endif // #if(_PANEL_DH_WIDTH > _HW_FOSD_H_DELAY_MAX + 5) // EO mode, 4K panel width = 4096
#endif // #elif(GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH)
#endif // #if(_OSD_H_DELAY_LIMIT_BYPASS == _ON)

#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
#if((_FOSD_SU_H_FACTOR_MIN < _HW_FOSD_SU_H_FACTOR_MIN) || (_FOSD_SU_H_FACTOR_MIN > _HW_FOSD_SU_H_FACTOR_MAX))
#warning "_FOSD_SU_H_FACTOR_MIN range 16 ~ 64"
#else
// hporch_min = (16 + SU_ratio * 18) * 2) multiple of 8. SU_ratio = in / out * 64.
#if(((_FOSD_SU_H_FACTOR_MIN <= 64) && (_FOSD_SU_H_FACTOR_MIN >= 47) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 88)) ||\
    ((_FOSD_SU_H_FACTOR_MIN <= 46) && (_FOSD_SU_H_FACTOR_MIN >= 40) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 96)) ||\
    ((_FOSD_SU_H_FACTOR_MIN <= 39) && (_FOSD_SU_H_FACTOR_MIN >= 35) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 104)) ||\
    ((_FOSD_SU_H_FACTOR_MIN <= 34) && (_FOSD_SU_H_FACTOR_MIN >= 32) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 112)) ||\
    ((_FOSD_SU_H_FACTOR_MIN <= 31) && (_FOSD_SU_H_FACTOR_MIN >= 29) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 120)) ||\
    ((_FOSD_SU_H_FACTOR_MIN <= 28) && (_FOSD_SU_H_FACTOR_MIN >= 26) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 128)) ||\
    (((_FOSD_SU_H_FACTOR_MIN == 25) || (_FOSD_SU_H_FACTOR_MIN == 24)) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 136)) ||\
    (((_FOSD_SU_H_FACTOR_MIN == 23) || (_FOSD_SU_H_FACTOR_MIN == 22)) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 144)) ||\
    ((_FOSD_SU_H_FACTOR_MIN == 21) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 152)) ||\
    (((_FOSD_SU_H_FACTOR_MIN == 20) || (_FOSD_SU_H_FACTOR_MIN == 19)) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 160)) ||\
    ((_FOSD_SU_H_FACTOR_MIN == 18) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 168)) ||\
    ((_FOSD_SU_H_FACTOR_MIN == 17) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < _HW_FOSD_FB_H_PRE_OPERATION_MAX_H_PORCH)) ||\
    ((_FOSD_SU_H_FACTOR_MIN == 16) && ((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH - _DDOMAIN_MAX_EXTENSION - 8) < 184)))
#warning "Increase DH Porch or _FOSD_SU_H_FACTOR_MIN for OSD pre-calcuated"
#endif
#endif

#if(_PANEL_DH_START >= _HW_FOSD_FB_D_H_START_MAX)
#warning "DH start should be less than _HW_FOSD_FB_D_H_START_MAX! (for OSD re-gen. timing)"
#endif

#elif(GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH)

#if((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < 52)
// 52 : real total = register + 4 (EO mode) = 48 + 4. 48 : registe h porch
#warning "DH Proch must be at least 52! (for OSD pre-calculated)"
#endif

#if(_PANEL_DH_START >= _HW_FOSD_EO_D_H_START_MAX)
#warning "DH start should be less than _HW_FOSD_EO_D_H_START_MAX! (for OSD re-gen. timing)"
#endif

#else

#if((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < 44)
// 44 : real total = register + 4 (EO mode) = 40 + 4. 40 : registe h porch
#warning "DH Proch must be at least 44! (for OSD pre-calculated)"
#endif

#if(_PANEL_DH_START >= _HW_FOSD_SINGLE_D_H_START_MAX)
#warning "DH start should be less than _HW_FOSD_SINGLE_D_H_START_MAX! (for OSD re-gen. timing)"
#endif

#endif // end of #if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)

//--------------------------------------------------
// Local Contrast
//--------------------------------------------------
#if((_LOCAL_CONTRAST_FUNCTION == _ON) || ((_LOCAL_DIMMING_FUNCTION == _ON) && (_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)))
#if((_PANEL_DH_TOTAL_MIN - _PANEL_DH_WIDTH) < _HW_LOCAL_CONTRAST_DH_PORCH_MIN)
#warning "DH Proch must be >= _HW_LOCAL_CONTRAST_DH_PORCH_MIN! (For LocalContrast)"
#endif
#endif

//--------------------------------------------------
// Asymmetric Panel
//--------------------------------------------------
#if(_PANEL_ASYMMETRIC == _ON)
#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
#warning "Asymmetric Panel support EO mode Only."
#else
#if((_2P_PBP_TB_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
#warning "Asymmetric Panel in EO mode support 1P/PIP/PBPLR mode Only."
#endif
#endif
#if(_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION == _ON)
#warning "_LOCAL_CONTRAST_HISTOGRM_INFO_FUNCTION should be _OFF when _PANEL_ASYMMETRIC = _ON"
#endif
#endif

#if(_PANEL_ASYMMETRIC == _OFF)
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_LEFT != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_TOP != 0) || (_PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM != 0))
#warning "_PANEL_ASYMMETRIC_DUMMY_NUM should be zero when  _PANEL_ASYMMETRIC is _OFF."
#endif
#else
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_LEFT % 2) != 0)
#warning "_PANEL_ASYMMETRIC_DUMMY_NUM_LEFT should be Even Number."
#endif
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT % 2) != 0)
#warning "_PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT should be Even Number."
#endif
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_TOP % 2) != 0)
#warning "_PANEL_ASYMMETRIC_DUMMY_NUM_TOP should be Even Number."
#endif
#if((_PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM % 2) != 0)
#warning "_PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM should be Even Number."
#endif
#endif

//--------------------------------------------------
// Pixel Shift Mode
//--------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if((GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH) && (_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN))
#warning "Pixel Shift can not support _PIXEL_SHIFT_IN_IDOMAIN in frontback mode!!!"
#endif
#endif

#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

//--------------------------------------------------
// Global Dimming
//--------------------------------------------------
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
#if(_GLOBAL_DIMMING_DARK_MODE_THD <= _GLOBAL_DIMMING_DARK_MODE_MIN)
#warning "_GLOBAL_DIMMING_DARK_MODE_MIN Should be less than _GLOBAL_DIMMING_DARK_MODE_THD!!!"
#endif
#endif

//--------------------------------------------------
// Local Dimming
//--------------------------------------------------
#if(_LOCAL_DIMMING_FUNCTION == _ON)

#if(_HW_LOCAL_DIMMING_MAX_REGION < _LOCAL_DIMMING_TOTAL_REGION)
#warning "_LOCAL_DIMMING_TOTAL_REGION can't larger than _HW_LOCAL_DIMMING_MAX_REGION"
#endif

#if((_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL > _HW_LOCAL_DIMMING_EDGE_H_REGION_MAX) && (_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_EDGE_BACKLIGHT))
#warning "_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL can't larger than _HW_LOCAL_DIMMING_EDGE_H_REGION_MAX"
#endif

#if((_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL > _HW_LOCAL_DIMMING_DIRECT_H_REGION_MAX) && (_LOCAL_DIMMING_BACKLIGHT_TYPE == _LOCAL_DIMMING_DIRECT_BACKLIGHT))
#warning "_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL can't larger than _HW_LOCAL_DIMMING_DIRECT_H_REGION_MAX"
#endif

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
#warning "_DEVICE_LED_DRIVER_TYPE should not be _DEVICE_LED_DRIVER_NONE when local dimming is supported"
#endif

#if(_SCALER_TYPE == _RL6829_SERIES)
#if(_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP == _ON)
#warning "_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP must be _OFF on this Scaler IC"
#endif
#endif

#if(_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _ON)
#if((_DEVICE_LED_DRIVER_SUPPORT_BROADCAST == _OFF) ||\
    (_DEVICE_LED_DRIVER_USE_UPDSYNC_AS_CS == _ON))
#warning "_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS must be _OFF"
#endif
#endif

#if((((_DEVICE_LED_DRIVER_PWM_MIN * 128 / _DEVICE_LED_DRIVER_PWM_MAX) - 1) > _LOCAL_DIMMING_BLACK_LUT_VALUE_HDR) ||\
    (((_DEVICE_LED_DRIVER_PWM_MIN * 128 / _DEVICE_LED_DRIVER_PWM_MAX) - 1) > _LOCAL_DIMMING_BLACK_LUT_VALUE_SDR))
#warning "_LOCAL_DIMMING_BLACK_LUT_VALUE_HDR and _LOCAL_DIMMING_BLACK_LUT_VALUE_SDR can't smaller than ((_DEVICE_LED_DRIVER_PWM_MIN * 128 / _DEVICE_LED_DRIVER_PWM_MAX) - 1) !!!"
#endif

#if((_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _ON) && (_SCPU_SUPPORT == _ON))
#warning "_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS Can Not Be Supported In Dual CPU Case!!!"
#endif

#if(_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE)
#if(_LOCAL_DIMMING_MAX_COMPENSATE_GAIN > 255)
#warning "_LOCAL_DIMMING_MAX_COMPENSATE_GAIN can't larger than 255!!!"
#endif
#endif

#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX == _ON)
#if(_DEVICE_LED_DRIVER_UPDSYNC_METHOD == _SMODE_UPDSYNC_USE_SPI)
#warning "_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX must be _OFF when UPDSYNC_USE_SPI!!!"
#endif
#if(_LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME > 1)
#warning "_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX must be _OFF when _LOCAL_DIMMING_PWM2SPI_UPD_TIMES_PER_FRAME > 1!!!"
#endif
#else
#if(_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_ALIGN_DVS == _ON)
#warning "_LOCAL_DIMMING_PWM2SPI_UPD_SYNC_ALIGN_DVS must be _OFF when _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX is _OFF!!!"
#endif
#if(_LOCAL_DIMMING_PWM2SPI_DELAY_AFTER_UPD_SYNC_XUS != 0)
#warning "_LOCAL_DIMMING_PWM2SPI_DELAY_AFTER_UPD_SYNC_XUS must be 0 when _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_BEFORE_TX is _OFF!!!"
#endif
#endif
#endif

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
#if(_DEVICE_LED_DRIVER_PWM_ADDRESS_STEP == 0)
#warning "_DEVICE_LED_DRIVER_PWM_ADDRESS_STEP should not be 0!!!"
#endif
#endif

//--------------------------------------------------
// Local Dimming MBR Mode
//--------------------------------------------------
#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
#if(_LOCAL_DIMMING_FUNCTION == _OFF)
#warning "_LOCAL_DIMMING_FUNCTION Should be _ON!!!"
#endif

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _OFF)
#warning "_MOTION_BLUR_REDUCTION_SUPPORT should be _ON"
#endif
#endif

//--------------------------------------------------
// MBR Check
//--------------------------------------------------
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO < 750)
#warning "_DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO should be >= 750!!!"
#endif

#if(_DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_HI < _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO + 50)
#warning "_DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_HI and _DRR_MOTION_BLUR_REDUCTION_FLICKER_IVF_LO should have margin >= 50!!!"
#endif
#endif

//--------------------------------------------------
// DRR Check
//--------------------------------------------------
#if(_PANEL_DRR_FRAME_SYNC_DVTOTAL_WITH_MARGIN == _ON)
#if(_DRR_SUPPORT == _OFF)
#warning "_DRR_SUPPORT should be _ON when _PANEL_DRR_FRAME_SYNC_DVTOTAL_WITH_MARGIN is _ON"
#endif
#endif
#endif // End of #ifndef __PANEL_CONFIG_CHECK_H__

