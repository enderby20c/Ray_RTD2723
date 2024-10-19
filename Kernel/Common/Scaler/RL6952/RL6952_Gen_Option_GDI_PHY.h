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
// ID Code      : RL6952_Gen_Option_GDI_PHY.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//-------------------------------------------------
// DPTX digital phy setting
//-------------------------------------------------
#define _HW_DPTX_DIGITAL_PHY_0                                  0x00
#define _HW_DPTX_DIGITAL_PHY_1                                  0x01
#define _HW_DPTX_DIGITAL_PHY_2                                  0x02
#define _HW_DPTX_DIGITAL_PHY_3                                  0x03
#define _HW_DPTX_DIGITAL_PHY_4                                  0x04
#define _HW_DPTX_DIGITAL_PHY_5                                  0x05
#define _HW_DPTX_DIGITAL_PHY_6                                  0x06
#define _HW_DPTX_DIGITAL_PHY_7                                  0x07
#define _HW_DPTX_DIGITAL_PHY_8                                  0x08
#define _HW_DPTX_DIGITAL_PHY_9                                  0x09
#define _HW_DPTX_DIGITAL_PHY_10                                 0x0A
#define _HW_DPTX_DIGITAL_PHY_11                                 0x0B
#define _HW_DPTX_DIGITAL_PHY_12                                 0x0C
#define _HW_DPTX_DIGITAL_PHY_13                                 0x0D
#define _HW_DPTX_DIGITAL_PHY_14                                 0x0E
#define _HW_DPTX_DIGITAL_PHY_15                                 0x0F

//--------------------------------------------------
// HW Input Port TMDS MAPPING TO RX PORT PHY
//--------------------------------------------------
#define _HW_D0_TMDS_PHY_RX_MAPPING                              _MAPPING_RX_MAP_NONE
#define _HW_D1_TMDS_PHY_RX_MAPPING                              _MAPPING_RX_MAP_NONE
#define _HW_D2_TMDS_PHY_RX_MAPPING                              _MAPPING_RX_MAP_NONE
#define _HW_D3_TMDS_PHY_RX_MAPPING                              _MAPPING_RX3
#define _HW_D4_TMDS_PHY_RX_MAPPING                              _MAPPING_RX4
#define _HW_D5_TMDS_PHY_RX_MAPPING                              _MAPPING_RX_MAP_NONE

//--------------------------------------------------
// HW Limit of TMDS 2X CLK for 420
//--------------------------------------------------
#define _HW_TMDS_PHY_2XCLK_LIMIT                                6000 // unit: 0.1 MHz

//--------------------------------------------------
// HW Input Port HDMI21 MAPPING TO RX PORT PHY
//--------------------------------------------------
#define _HW_D0_HDMI21_PHY_RX_MAPPING                            _MAPPING_RX_MAP_NONE
#define _HW_D1_HDMI21_PHY_RX_MAPPING                            _MAPPING_RX_MAP_NONE
#define _HW_D2_HDMI21_PHY_RX_MAPPING                            _MAPPING_RX_MAP_NONE
#define _HW_D3_HDMI21_PHY_RX_MAPPING                            _MAPPING_RX3
#define _HW_D4_HDMI21_PHY_RX_MAPPING                            _MAPPING_RX4
#define _HW_D5_HDMI21_PHY_RX_MAPPING                            _MAPPING_RX_MAP_NONE

//--------------------------------------------------
// HW Input Port DP MAPPING TO RX PORT PHY
//--------------------------------------------------
#define _HW_D0_DP_PHY_RX_MAPPING                                _MAPPING_RX0
#define _HW_D1_DP_PHY_RX_MAPPING                                _MAPPING_RX1
#define _HW_D2_DP_PHY_RX_MAPPING                                _MAPPING_RX2
#define _HW_D3_DP_PHY_RX_MAPPING                                _MAPPING_RX_MAP_NONE
#define _HW_D4_DP_PHY_RX_MAPPING                                _MAPPING_RX_MAP_NONE
#define _HW_D5_DP_PHY_RX_MAPPING                                _MAPPING_RX_MAP_NONE
#define _HW_D7_DP_PHY_RX_MAPPING                                _MAPPING_RX7
#define _HW_D8_DP_PHY_RX_MAPPING                                _MAPPING_RX8

//--------------------------------------------------
// Package Ball to TMDS PHY's PAD Lane Mapping
//--------------------------------------------------
#define _HW_TMDS_LANE_MAPPING                                   _TMDS_LANE_SWAP_NONE

//--------------------------------------------------
// DPTX PHY Define
//--------------------------------------------------
#define _HW_DP_TX_Z0_TERM_LANE3                                 8
#define _HW_DP_TX_Z0_TERM_LANE2                                 8
#define _HW_DP_TX_Z0_TERM_LANE1                                 8
#define _HW_DP_TX_Z0_TERM_LANE0                                 8

//--------------------------------------------------
// USB3 Repeater UFP PHY Mapping Select
//--------------------------------------------------
#define _HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING                 _USB3_REPEATER_UFP_PHY_0
#define _HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING                 _USB3_REPEATER_UFP_PHY_1
#define _HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING                 _USB3_REPEATER_UFP_PHY_NONE

//--------------------------------------------------
// USB3 Repeater DFP PHY Mapping Select
//--------------------------------------------------
#define _HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING               _USB3_REPEATER_DFP_PHY_0
#define _HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING               _USB3_REPEATER_DFP_PHY_NONE
#define _HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING               _USB3_REPEATER_DFP_PHY_NONE

//--------------------------------------------------
// USB3 Repeater DFP Mux Embedded
//--------------------------------------------------
#define _HW_USB3_REPEATER_PHY_DFP_MUX_TYPE                      _USB3_REPEATER_PHY_DFP_MUX_NONE

//--------------------------------------------------
// HW DP Rx Decode Check
//--------------------------------------------------
#define _HW_DP_RX_DECODE_CHECK_POSITION                         _DP_RX_DECODE_CHECK_AFTER_LANE_MUX

//--------------------------------------------------
// HW DP Rx PHY to MAC Interface
//--------------------------------------------------
#define _HW_DP_RX_PHY_TO_MAC_INTERFACE                          _DP_RX_32_BIT

//--------------------------------------------------
// HW DP Lane Swap Support
//--------------------------------------------------
#define _HW_DP_LANE_SWAP_SUPPORT                                _ON

//--------------------------------------------------
// HW DP PN Swap Support
//--------------------------------------------------
#define _HW_DP_PN_SWAP_SUPPORT                                  _ON
