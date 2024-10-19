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
// ID Code      : RL6829_Gen_Option_DP.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

////////
// HW //
////////

//--------------------------------------------------
// HW Input Port DP MAPPING TO RX PORT AUX
//--------------------------------------------------
#define _HW_D0_DP_AUX_RX_MAPPING                                _MAPPING_RX0
#define _HW_D1_DP_AUX_RX_MAPPING                                _MAPPING_RX1
#define _HW_D2_DP_AUX_RX_MAPPING                                _MAPPING_RX2
#define _HW_D3_DP_AUX_RX_MAPPING                                _MAPPING_RX_MAP_NONE
#define _HW_D4_DP_AUX_RX_MAPPING                                _MAPPING_RX_MAP_NONE
#define _HW_D5_DP_AUX_RX_MAPPING                                _MAPPING_RX_MAP_NONE
#define _HW_D7_DP_AUX_RX_MAPPING                                _MAPPING_RX7
#define _HW_D8_DP_AUX_RX_MAPPING                                _MAPPING_RX8

//--------------------------------------------------
// HW Input Port DP MAPPING TO RX PORT HDCP
//--------------------------------------------------
#define _HW_D0_DP_HDCP_RX_MAPPING                               _MAPPING_RX0
#define _HW_D1_DP_HDCP_RX_MAPPING                               _MAPPING_RX1
#define _HW_D2_DP_HDCP_RX_MAPPING                               _MAPPING_RX2

//--------------------------------------------------
// DP High Resolution Support
//--------------------------------------------------
#define _HW_DP_HIGH_RESOL_SUPPORT                               _ON

//--------------------------------------------------
// HW DP Video Fifo Size
//--------------------------------------------------
#define _HW_DP_RX_VIDEO_FIFO_SIZE_8B10B                         (256 * 96)
#define _HW_DP_RX_VIDEO_FIFO_SIZE_128B132B                      (256 * 256)

//--------------------------------------------------
// HW DP PLL Input Clock DIV
//--------------------------------------------------
#define _HW_DP_RX_PLL_INPUT_CLK_DIV_128B132B                    _DP_RX_PLL_INPUT_CLK_DIV_40

//--------------------------------------------------
// DP InfoFrame Length
//--------------------------------------------------
#define _HW_DP_SDP_PAYLOAD_LENGTH                               32

//--------------------------------------------------
// DP SDP META SRAM DATA BYTE Length
//--------------------------------------------------
#define _HW_DP_SDP_META_SRAM_DB_DEPTH                           32
#define _HW_DP_SDP_META_SRAM_DB_WIDTH                           16
#define _HW_DP_SDP_META_SRAM_DB_LENGTH                          (_HW_DP_SDP_META_SRAM_DB_DEPTH * _HW_DP_SDP_META_SRAM_DB_WIDTH)

//--------------------------------------------------
// HW DP D0 MAX LINK RATE
//--------------------------------------------------
#define _HW_DP_D0_MAX_LINK_RATE_SUPPORT                         _DP_ULTRA_SPEED_2000MHZ

//--------------------------------------------------
// HW DP D1 MAX LINK RATE
//--------------------------------------------------
#define _HW_DP_D1_MAX_LINK_RATE_SUPPORT                         _DP_ULTRA_SPEED_2000MHZ

//--------------------------------------------------
// HW DP D1 MAX LINK RATE
//--------------------------------------------------
#define _HW_DP_D2_MAX_LINK_RATE_SUPPORT                         _DP_ULTRA_SPEED_2000MHZ

//--------------------------------------------------
// HW DP Tx MAX DPCD VERSION
//--------------------------------------------------
#define _HW_DP_TX_MAX_LINK_RATE_SUPPORT                         _DP_ULTRA_SPEED_2000MHZ

//--------------------------------------------------
// HW Input Port DP MAPPING TO RX PORT MAC DPHY
//--------------------------------------------------
#define _HW_D0_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX0
#define _HW_D1_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX1
#define _HW_D2_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX2
#define _HW_D3_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX_MAP_NONE
#define _HW_D4_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX_MAP_NONE
#define _HW_D5_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX_MAP_NONE
#define _HW_D7_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX7
#define _HW_D8_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX8
#define _HW_D9_DP_MAC_DPHY_RX_MAPPING                           _MAPPING_RX0_OR_RX1_OR_RX2
#define _HW_MST2SST_DP_MAC_DPHY_RX_MAPPING                      _MAPPING_RX0_OR_RX1_OR_RX2

//--------------------------------------------------
// HW Input Port DP MAPPING TO RX PORT MAC
//--------------------------------------------------
#define _HW_D0_DP_MAC_STREAM_RX_MAPPING                         _MAPPING_RX0
#define _HW_D1_DP_MAC_STREAM_RX_MAPPING                         _MAPPING_RX1
#define _HW_D2_DP_MAC_STREAM_RX_MAPPING                         _MAPPING_RX2
#define _HW_D3_DP_MAC_STREAM_RX_MAPPING                         _MAPPING_RX_MAP_NONE
#define _HW_D4_DP_MAC_STREAM_RX_MAPPING                         _MAPPING_RX_MAP_NONE
#define _HW_D5_DP_MAC_STREAM_RX_MAPPING                         _MAPPING_RX_MAP_NONE
#define _HW_D9_DP_MAC_STREAM_RX_MAPPING                         _MAPPING_RX3
#define _HW_MST2SST_DP_MAC_STREAM_RX_MAPPING                    _MAPPING_RX4

//--------------------------------------------------
// HW DP MAC Dphy And Stream Support Switching Input Port
//--------------------------------------------------
#define _HW_DP_MAC_DPHY_SWITCH_SUPPORT                          _OFF
#define _HW_DP_MAC_STREAM_SWITCH_SUPPORT                        _OFF

//--------------------------------------------------
// HW DP MAC Dphy CTS FIFO Support
//--------------------------------------------------
#define _HW_DP_MAC_DPHY_CTS_FIFO_SUPPORT                        _ON

//--------------------------------------------------
// HW DP MAC MAX Pixel Mode
//--------------------------------------------------
#define _HW_DP_MAC_MAX_PIXEL_MODE_8B10B                         _DP_MAC_STREAM_RX_TWO_PIXEL_MODE
#define _HW_DP_MAC_MAX_PIXEL_MODE_128B132B                      _DP_MAC_STREAM_RX_FOUR_PIXEL_MODE

//--------------------------------------------------
// HW DP MAC MAX Color Depth
//--------------------------------------------------
#define _HW_DP_MAC_MAX_COLOR_DEPTH_8B10B                        _COLOR_DEPTH_16_BITS
#define _HW_DP_MAC_MAX_COLOR_DEPTH_128B132B                     _COLOR_DEPTH_12_BITS

//--------------------------------------------------
// HW DP Max Pixel Clock (MPixel/s)
//--------------------------------------------------
#define _HW_DP_MAX_PIXEL_CLOCK                                  700

//--------------------------------------------------
// HW DP MST Stream Source Count
//--------------------------------------------------
#define _HW_DP_MST_ST_SOURCE_COUNT                              _DP_MST_6_STREAM

//--------------------------------------------------
// HW DP MST Daisy Chain Stream Number Maximum
//--------------------------------------------------
#define _HW_DP_MST_DAISY_ST_NUM_MAX                             _DP_MST_6_STREAM

//--------------------------------------------------
// HW DP MST RX Mac to Source Num
//--------------------------------------------------
#define _HW_DP_MST_RX_MAC0_SOURCEX_MAPPING                      _DP_ST_SOURCE1
#define _HW_DP_MST_RX_MAC1_SOURCEX_MAPPING                      _DP_ST_SOURCE1
#define _HW_DP_MST_RX_MAC2_SOURCEX_MAPPING                      _DP_ST_SOURCE1
#define _HW_DP_MST_RX_MAC3_SOURCEX_MAPPING                      _DP_ST_SOURCE2

//--------------------------------------------------
// HW GDI DFE TYPE
//--------------------------------------------------
#define _HW_DP_GDI_RX0_DFE_TYPE                                 _ADAPTIVE_DFE
#define _HW_DP_GDI_RX1_DFE_TYPE                                 _ADAPTIVE_DFE
#define _HW_DP_GDI_RX2_DFE_TYPE                                 _ADAPTIVE_DFE

//--------------------------------------------------
// DP HDCP2.2 Support
//--------------------------------------------------
#define _HW_DP_HDCP_2_2_FUNCTION_SUPPORT                        _ON

//--------------------------------------------------
// HW HDCP2 TX KEY IROM SUPPORT
//--------------------------------------------------
#define _HW_TX_HDCP_2_2_KEY_LOCATION_IROM_SUPPORT               _OFF

//--------------------------------------------------
// HW DP HDCP circuit count
//--------------------------------------------------
#define _HW_DP_HDCP_CIRCUIT_COUNT                               3

//--------------------------------------------------
// HW DP Aux Rx MacII Support
//--------------------------------------------------
#define _HW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT                     _OFF

//--------------------------------------------------
// HW DP Aux Rx WildCard Support
//--------------------------------------------------
#define _HW_DP_AUX_RX_WILDCARD_SUPPORT                          5

//--------------------------------------------------
// HW DP Aux Rx Remap Support (Use For _FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == ON)
//--------------------------------------------------
#define _HW_DP_AUX_RX_REMAP_SUPPORT                             0

//--------------------------------------------------
// HW DP Aux Rx Remap 32B Support (Use For _FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == OFF)
//--------------------------------------------------
#define _HW_DP_AUX_RX_REMAP_32B_SUPPORT                         4

//--------------------------------------------------
// HW DP Aux Rx Remap 16B Support (Use For _FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == OFF)
//--------------------------------------------------
#define _HW_DP_AUX_RX_REMAP_16B_SUPPORT                         1

//--------------------------------------------------
// HW DP Aux Rx Remap 8B Support (Use For _FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == OFF)
//--------------------------------------------------
#define _HW_DP_AUX_RX_REMAP_8B_SUPPORT                          4

//--------------------------------------------------
// HW DP Aux Single Ended Mode Support
//--------------------------------------------------
#define _HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT                    _ON

//--------------------------------------------------
// HW DP Aux Rx Mac Dpcd Access Type
//--------------------------------------------------
#define _HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE                      _DP_AUX_RX_MAC_DPCD_ACCESS_NORMAL

//--------------------------------------------------
// HW DP Aux Single End Gen
//--------------------------------------------------
#define _HW_DP_AUX_SINGLE_END_GEN                               _DP_AUX_SINGLE_END_ONLY

//--------------------------------------------------
// HW DP Aux Rx3 Gen
//--------------------------------------------------
#define _HW_DP_AUX_RX_GEN                                       _DP_AUX_RX_ONLY

//--------------------------------------------------
// HW DP Aux Auto Calibration Support
//--------------------------------------------------
#define _HW_DP_AUX_AUTO_CALIBRATION_SUPPORT                     _OFF
#define _HW_DP_AUX_AUTO_CALIBRATION_RANGE                       0
#define _HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION                 _DP_AUX_AUTO_CALIBRATION_NONE

//--------------------------------------------------
// HW DP Aux Aphy PN Swap
//--------------------------------------------------
#define _HW_DP_AUX_APHY_PN_SWAP_CTRL                            _DP_AUX_APHY_PN_SWAP_RXTX_COMBO

//--------------------------------------------------
// HW DP Auxless ALPM Support
//--------------------------------------------------
#define _HW_DP_D0_AUXLESS_ALPM_SUPPORT                          _ON
#define _HW_DP_D1_AUXLESS_ALPM_SUPPORT                          _ON
#define _HW_DP_D2_AUXLESS_ALPM_SUPPORT                          _OFF

//--------------------------------------------------
// HW DP Rx Fec Weak Mode Gated Support
//--------------------------------------------------
#define _HW_DP_RX_FEC_WEAK_MODE_GATED_SUPPORT                   _OFF

//--------------------------------------------------
// HW DP Rx BS Miss Detect Period Enable Support
//--------------------------------------------------
#define _HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT          _OFF

//--------------------------------------------------
// HW DP Rx FEC Error Count DB Support
//--------------------------------------------------
#define _HW_DP_RX_FEC_ERROR_COUNT_SEL_DB_SUPPORT                _OFF

//--------------------------------------------------
// HW DP Audio Channel Status Receive with 1s1d/2s Support
//--------------------------------------------------
#define _HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT      _OFF


////////
// FW //
////////

//--------------------------------------------------
// FW Support DP HDCP2 Handshake Support Under DC OFF State
//--------------------------------------------------
#define _FW_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT                 _ON

//--------------------------------------------------
// DP Rx DSC Support Option
//--------------------------------------------------
#define _FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT                 _OFF

//--------------------------------------------------
// FW DP HBE/HBR Buffer Size
//--------------------------------------------------
#define _FW_DP_RX_HBLANKING_MODIFY_BUFFER_SIZE                  0x40

//--------------------------------------------------
// FW DP Aux Rx MacII Support
//--------------------------------------------------
#define _FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT                     _OFF

//--------------------------------------------------
// FW DP Rx Display Format Regen Mode For Freesync
//--------------------------------------------------
#define _FW_DP_RX_FREESYNC_DPF_MODE_FRAME_SYNC_BE_DRR           _OFF

//--------------------------------------------------
// FW DP Aux Rx Dynamic Power Cut
//--------------------------------------------------
#define _FW_DP_AUX_RX_DYNAMIC_POWER_CUT                         _OFF
