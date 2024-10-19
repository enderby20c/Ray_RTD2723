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
// ID Code      : RL6978_Gen_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// HW Input Port TMDS MAPPING TO RX PORT MAC
//--------------------------------------------------
#define _HW_D0_TMDS_MAC_RX_MAPPING                              _MAPPING_RX_MAP_NONE
#define _HW_D1_TMDS_MAC_RX_MAPPING                              _MAPPING_RX3
#define _HW_D2_TMDS_MAC_RX_MAPPING                              _MAPPING_RX3
#define _HW_D3_TMDS_MAC_RX_MAPPING                              _MAPPING_RX3
#define _HW_D4_TMDS_MAC_RX_MAPPING                              _MAPPING_RX_MAP_NONE
#define _HW_D5_TMDS_MAC_RX_MAPPING                              _MAPPING_RX_MAP_NONE // Confirm

//--------------------------------------------------
// HW Input Port TMDS MAPPING TO RX PORT MAC
//--------------------------------------------------
#define _HW_D0_FRL_MAC_RX_MAPPING                               _MAPPING_RX_MAP_NONE
#define _HW_D1_FRL_MAC_RX_MAPPING                               _MAPPING_RX3
#define _HW_D2_FRL_MAC_RX_MAPPING                               _MAPPING_RX3
#define _HW_D3_FRL_MAC_RX_MAPPING                               _MAPPING_RX3
#define _HW_D4_FRL_MAC_RX_MAPPING                               _MAPPING_RX_MAP_NONE
#define _HW_D5_FRL_MAC_RX_MAPPING                               _MAPPING_RX_MAP_NONE // Modify Define Name

//--------------------------------------------------
// TMDS Input Clock Online Measure Divider
//--------------------------------------------------
#define _HW_TMDS_MEASURE_CLOCK_DIVIDER                          2 // Confirm

//--------------------------------------------------
// TMDS Input Clock Online Measure Counter
//--------------------------------------------------
#define _HW_TMDS_MEASURE_CLOCK_COUNTER                          2000 // Confirm

//--------------------------------------------------
// HDMI Video PLL VCO Clk Limit (_HW_HDMI_VIDEO_PLL_CLK_LIMIT shall <= _HW_FORMAT_CONVERSION_SINGLE_PATH_CLOCK_LIMIT)
//--------------------------------------------------
#define _HW_HDMI_VIDEO_PLL_CLK_LIMIT                            6126 // unit: 0.1MHz

//--------------------------------------------------
// HW HDMI 2.0 Support
//--------------------------------------------------
#define _HW_HDMI20_SUPPORT_PORT                                 _HDMI20_D1_D2_D3 // Confirm

//--------------------------------------------------
// HW HDMI 2.1 Support
//--------------------------------------------------
#define _HW_HDMI_FRL_SUPPORT_PORT                               _HDMI_FRL_MAC_D1_D2_D3 // Modify by HDMI21->HDMI FRL git align

//--------------------------------------------------
// HW HDMI 2.1 Max Link Rate
//--------------------------------------------------
#define _HW_HDMI21_MAX_LINK_RATE_SUPPORT                        _HDMI_FRL_RATE_6G_4LANES // Modify by HDMI21->HDMI FRL git align

//--------------------------------------------------
// HW HDMI CEC Function Support
//--------------------------------------------------
#define _HW_HDMI_CEC_GEN                                        _HW_CEC_GEN_TYPE_3
#define _HW_HDMI_CEC_ANALOG_GEN                                 _HW_CEC_ANALOG_GEN_TYPE_1

//--------------------------------------------------
// HW CEC IRQ Group
//--------------------------------------------------
#define _HW_CEC_IRQ_GROUP                                       _HW_CEC_IRQ_SCALER_OTHER

//--------------------------------------------------
// HW IRQ Priority
//--------------------------------------------------
#define _HW_HDMI_IRQ_PRIORITY_MODE                              _HDMI_IRQ_NEW_MODE

//--------------------------------------------------
// HW SCDC reset
//--------------------------------------------------
#define _HW_HDMI_SCDC_RESET                                     _ON

//--------------------------------------------------
// HW SCDC reset
//--------------------------------------------------
#define _HW_HDMI_ON_POWER_CONTROL                               _ON

//--------------------------------------------------
// HW HDMI EMP SRAM Support
//--------------------------------------------------
#define _HW_HDMI_EMP_SRAM_SUPPORT                               _OFF

//--------------------------------------------------
// HW HDMI ARC Tx Function Support
//--------------------------------------------------
#define _HW_HDMI_ARC_TX_EMBEDDED_EARC_IP_SUPPORT                _OFF

//--------------------------------------------------
// HW HDMI ARC Tx SPDIF Strong Driving Pad Support
//--------------------------------------------------
#define _HW_HDMI_ARC_TX_SPDIF_STRONG_DRIVING_PAD_SUPPORT        _ON

//--------------------------------------------------
// HW HDMI AVI ACE Field WD Support
//--------------------------------------------------
#define _HW_HDMI_AVI_ACE_WD_SUPPORT                             _ON

//-------------------------------------------------
// I2s/Spdif Channel Output Select
//-------------------------------------------------
#define _HW_HDMI_AUDIO_8CH_LAYOUT_NORMAL_OUTPUT                 _OFF

//--------------------------------------------------
// HDMI 2.1 DPF 4P/2P/1P Mode Frequency (Unit: 0.1MHz)
//--------------------------------------------------
#define _HW_HDMI_FRL_DPF_4P_MODE_FREQ                           12196
#define _HW_HDMI_FRL_DPF_2P_MODE_FREQ                           6126

