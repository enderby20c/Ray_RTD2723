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
// ID Code      : RL6952_Project_Default.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include <Project/RL6952_Project_Default_Advanced.h>


/////////////
// General //
/////////////

//--------------------------------------------------
// Pcb Option
//--------------------------------------------------
#ifndef _PCB_TYPE
#define _PCB_TYPE                                               _RL6952_PCB_EXAMPLE
#endif

//--------------------------------------------------
// Panel Option
//--------------------------------------------------
#ifndef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_NONE
#endif

#ifndef _PANEL_POW_SEQ_FAST_MODE
#define _PANEL_POW_SEQ_FAST_MODE                                _ON
#endif

//-------------------------------------------------
// Multi-Display Option
//-------------------------------------------------
#ifndef _2P_PIP_DISPLAY_SUPPORT
#define _2P_PIP_DISPLAY_SUPPORT                                 _OFF
#endif

#ifndef _2P_PBP_LR_DISPLAY_SUPPORT
#define _2P_PBP_LR_DISPLAY_SUPPORT                              _OFF
#endif

//--------------------------------------------------
// MTP BW Calculation Option
//--------------------------------------------------
#ifndef _MTP_MAIN_PREFER_TIMING_FRAME_RATE
#define _MTP_MAIN_PREFER_TIMING_FRAME_RATE                      _PANEL_TYP_FRAME_RATE
#endif

#ifndef _MTP_MAIN_ACCEPT_MIN_COLOR_DEPTH
#define _MTP_MAIN_ACCEPT_MIN_COLOR_DEPTH                        _COLOR_DEPTH_8_BITS
#endif

#ifndef _MTP_SUB_PREFER_TIMING_FRAME_RATE
#define _MTP_SUB_PREFER_TIMING_FRAME_RATE                       _PANEL_TYP_FRAME_RATE
#endif

#ifndef _MTP_SUB_ACCEPT_MIN_COLOR_DEPTH
#define _MTP_SUB_ACCEPT_MIN_COLOR_DEPTH                         _COLOR_DEPTH_8_BITS
#endif

#ifndef _MTP_OD_ACCEPT_MIN_PARAM
#define _MTP_OD_ACCEPT_MIN_PARAM                                _OD_PARAM_4_5_BPP
#endif

#ifndef _MTP_OD_ACCEPT_MAX_PARAM
#define _MTP_OD_ACCEPT_MAX_PARAM                                _OD_PARAM_7_5_BPP
#endif

//--------------------------------------------------
// Osd Option
//--------------------------------------------------
#ifndef _OSD_TYPE
#define _OSD_TYPE                                               _NONE_OSD
#endif

#ifndef _FOSD_SU_H_FACTOR_MIN
#define _FOSD_SU_H_FACTOR_MIN                                   _HW_FOSD_SU_H_FACTOR_MIN // x4. HFactor = H input/ H output * 2^6 = 64 ~ 16
#endif


///////////
// DDCCI //
///////////

//-------------------------------------------------
// DDCCI Option
//-------------------------------------------------
#ifndef _DDCCI0_RXBUF_LENGTH
#define _DDCCI0_RXBUF_LENGTH                                    16 // Only DDC-CI 0 can support OGC/OCC communication, Config length equal to 128 in OGC mode and 16 in other case
#endif

#ifndef _DDCCI_RXBUF_LENGTH
#define _DDCCI_RXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TXBUF_LENGTH
#define _DDCCI_TXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TIMEOUT_LIMIT
#define _DDCCI_TIMEOUT_LIMIT                                    50 // 0~65535ms
#endif

#ifndef _CAPABILITIES_STRING_VGA
#define _CAPABILITIES_STRING_VGA                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_HDMI
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_DP
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif


/////////////////////
// Display Setting //
/////////////////////

//--------------------------------------------------
// Definitions of DDR3 Memory Size
//--------------------------------------------------
#ifndef _EMBEDDED_MEMORY_SIZE_CONFIG
#define _EMBEDDED_MEMORY_SIZE_CONFIG                            _EMBEDDED_MEMORY_SIZE_NONE
#endif

//-------------------------------------------------
// FW DDR3 PLL Freq
//-------------------------------------------------
#ifndef _FW_DDR_PLL_CLOCK
#define _FW_DDR_PLL_CLOCK                                       _FW_DDR_PLL_CLOCK_DEFAULT
#endif

//-------------------------------------------------
// OD Option
//-------------------------------------------------
#ifndef _OD_FUNCTION
#define _OD_FUNCTION                                            _OFF
#endif

#ifndef _OD_BY_POSITION_SUPPORT
#define _OD_BY_POSITION_SUPPORT                                 _OFF
#endif

//-------------------------------------------------
// FRC Option
//-------------------------------------------------
#ifndef _FRC_SUPPORT
#define _FRC_SUPPORT                                            _OFF
#endif

//-------------------------------------------------
// M-Domain Image Compression
//-------------------------------------------------
#ifndef _M_DOMAIN_IMG_CMP_SUPPORT
#define _M_DOMAIN_IMG_CMP_SUPPORT                               _OFF
#endif

//--------------------------------------------------
// Use 10-Bit Color Depth Through M-domain Compression
//--------------------------------------------------
#ifndef _M_DOMAIN_IMG_CMP_10_BIT_SUPPORT
#define _M_DOMAIN_IMG_CMP_10_BIT_SUPPORT                        _OFF
#endif

//-------------------------------------------------
// Display Rotation Option
//-------------------------------------------------
#ifndef _DISPLAY_ROTATION_SUPPORT
#define _DISPLAY_ROTATION_SUPPORT                               _OFF
#endif

//--------------------------------------------------
// Aspect Ratio Option
//--------------------------------------------------
#ifndef _ASPECT_RATIO_SUPPORT
#define _ASPECT_RATIO_SUPPORT                                   _OFF
#endif

#ifndef _ASPECT_ORIGINAL_MODE_SUPPORT
#define _ASPECT_ORIGINAL_MODE_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// Overscan Option
//--------------------------------------------------
#ifndef _OVERSCAN_DVI_SUPPORT
#define _OVERSCAN_DVI_SUPPORT                                   _OFF
#endif

#ifndef _OVERSCAN_HDMI_SUPPORT
#define _OVERSCAN_HDMI_SUPPORT                                  _OFF
#endif

#ifndef _OVERSCAN_DP_SUPPORT
#define _OVERSCAN_DP_SUPPORT                                    _OFF
#endif

#ifndef _OVERSCAN_H_RATIO
#define _OVERSCAN_H_RATIO                                       30
#endif

#ifndef _OVERSCAN_V_RATIO
#define _OVERSCAN_V_RATIO                                       30
#endif

//-------------------------------------------------
// Adjust H & V Position Max Range Option
//-------------------------------------------------
#ifndef _MAX_H_POSITION_RANGE
#define _MAX_H_POSITION_RANGE                                   100 // Pixel
#endif

#ifndef _MAX_V_POSITION_RANGE
#define _MAX_V_POSITION_RANGE                                   100 // Line
#endif


////////////////////
// Color Function //
////////////////////

//--------------------------------------------------
// Digital Functional Option
//--------------------------------------------------
#ifndef _I_DITHER_FUNCTION
#define _I_DITHER_FUNCTION                                      _OFF
#endif

#ifndef _D_DITHER_FUNCTION
#define _D_DITHER_FUNCTION                                      _OFF
#endif

#ifndef _GAMMA_FUNCTION
#define _GAMMA_FUNCTION                                         _OFF
#endif

#ifndef _COLOR_FORMAT_CONVERT_FUNCTION
#define _COLOR_FORMAT_CONVERT_FUNCTION                          _OFF
#endif

#ifndef _RGB_QUANTIZATION_RANGE_FUNCTION
#define _RGB_QUANTIZATION_RANGE_FUNCTION                        _OFF
#endif

#ifndef _YCC_QUANTIZATION_RANGE_FUNCTION
#define _YCC_QUANTIZATION_RANGE_FUNCTION                        _OFF
#endif

#ifndef _ULTRA_VIVID_FUNCTION
#define _ULTRA_VIVID_FUNCTION                                   _OFF
#endif

#ifndef _DCR_FUNCTION
#define _DCR_FUNCTION                                           _OFF
#endif

#ifndef _DCC_FUNCTION
#define _DCC_FUNCTION                                           _OFF
#endif

#ifndef _DCC_HISTOGRM_INFO_FUNCTION
#define _DCC_HISTOGRM_INFO_FUNCTION                             _OFF
#endif

#ifndef _ICM_FUNCTION
#define _ICM_FUNCTION                                           _OFF
#endif

#ifndef _SCM_SUPPORT
#define _SCM_SUPPORT                                            _OFF
#endif

#ifndef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _OFF
#endif

#ifndef _COLOR_DEMO_FUNCTION
#define _COLOR_DEMO_FUNCTION                                    _OFF
#endif

#ifndef _BORDER_WINDOW_FUNCTION
#define _BORDER_WINDOW_FUNCTION                                 _OFF
#endif

#ifndef _SHARPNESS_FUNCTION
#define _SHARPNESS_FUNCTION                                     _OFF
#endif

#ifndef _CONTRAST_FUNCTION
#define _CONTRAST_FUNCTION                                      _OFF
#endif

#ifndef _BRIGHTNESS_FUNCTION
#define _BRIGHTNESS_FUNCTION                                    _OFF
#endif

#ifndef _LOCAL_CONTRAST_FUNCTION
#define _LOCAL_CONTRAST_FUNCTION                                _OFF
#endif

#ifndef _ANTI_ALIASING_FUNCTION
#define _ANTI_ALIASING_FUNCTION                                 _OFF
#endif

//-------------------------------------------------
// Hue and Saturation Option
//-------------------------------------------------
#ifndef _GLOBAL_HUE_SATURATION_FUNCTION
#define _GLOBAL_HUE_SATURATION_FUNCTION                         _OFF
#endif

#ifndef _HUE_MAX
#define _HUE_MAX                                                230
#endif

#ifndef _HUE_MIN
#define _HUE_MIN                                                30
#endif

#ifndef _SATURATION_MAX
#define _SATURATION_MAX                                         200
#endif

#ifndef _SATURATION_MIN
#define _SATURATION_MIN                                         0
#endif


////////////////////////////////////////
// Off-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// PCM (Load Code Table) Option
//-------------------------------------------------
#ifndef _PCM_FUNCTION
#define _PCM_FUNCTION                                           _OFF
#endif

//-------------------------------------------------
// 3D Gamma (Load Code Table) Option
//-------------------------------------------------
#ifndef _RGB_3D_GAMMA_FUNCTION
#define _RGB_3D_GAMMA_FUNCTION                                  _OFF
#endif


////////////////////////////////////////
// On-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// OGC and OCC (On-Line Calibration) Option
//-------------------------------------------------
#ifndef _OCC_FUNCTION
#define _OCC_FUNCTION                                           _OFF
#endif

#ifndef _OGC_FUNCTION
#define _OGC_FUNCTION                                           _OFF
#endif

#ifndef _OGC_DICOM_FUNCTION
#define _OGC_DICOM_FUNCTION                                     _OFF
#endif

#ifndef _TWO_BRI_CALIBRATION_TYPE
#define _TWO_BRI_CALIBRATION_TYPE                               _TWO_BRI_CALIBRATION_NONE
#endif

#ifndef _OCC_IG_NODE_1025_SUPPORT
#define _OCC_IG_NODE_1025_SUPPORT                               _OFF
#endif

#ifndef _OGC_TOTAL_GAMMA
#define _OGC_TOTAL_GAMMA                                        1 // 1/2/3/4/5/6
#endif

#ifndef _OGC_TOTAL_CT
#define _OGC_TOTAL_CT                                           1
#endif

#ifndef _OGC_TOTAL_DICOM
#define _OGC_TOTAL_DICOM                                        1 // 1/2/3/4
#endif

#ifndef _OGC_FLASH_BANK
#define _OGC_FLASH_BANK                                         0
#endif

//-------------------------------------------------
// FreesyncII Option
//-------------------------------------------------
#ifndef _FREESYNC_II_FLASH_BANK
#define _FREESYNC_II_FLASH_BANK                                 0
#endif

#ifndef _FREESYNC_II_FLASH_PAGE
#define _FREESYNC_II_FLASH_PAGE                                 0
#endif

//-------------------------------------------------
// Uniformity (On-Line Calibration) Option
//-------------------------------------------------
#ifndef _UNIFORMITY_FUNCTION
#define _UNIFORMITY_FUNCTION                                    _OFF
#endif

#ifndef _UNIFORMITY_1ST_TABLE_LEVEL
#define _UNIFORMITY_1ST_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_2ND_TABLE_LEVEL
#define _UNIFORMITY_2ND_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_3RD_TABLE_LEVEL
#define _UNIFORMITY_3RD_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_4TH_TABLE_LEVEL
#define _UNIFORMITY_4TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_5TH_TABLE_LEVEL
#define _UNIFORMITY_5TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_6TH_TABLE_LEVEL
#define _UNIFORMITY_6TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_7TH_TABLE_LEVEL
#define _UNIFORMITY_7TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_8TH_TABLE_LEVEL
#define _UNIFORMITY_8TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_9TH_TABLE_LEVEL
#define _UNIFORMITY_9TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#endif

#ifndef _UNIFORMITY_FLASH_BANK0
#define _UNIFORMITY_FLASH_BANK0                                 0
#endif

#ifndef _LOCAL_DIMMING_FUNCTION
#define _LOCAL_DIMMING_FUNCTION                                 _OFF
#endif

#ifndef _GLOBAL_DIMMING_FUNCTION
#define _GLOBAL_DIMMING_FUNCTION                                _OFF
#endif

//-------------------------------------------------
// Display HDR Version
//-------------------------------------------------
#ifndef _DISPLAY_HDR_VERSION
#define _DISPLAY_HDR_VERSION                                    _DISPLAY_HDR_VERSION_1_1
#endif

//-------------------------------------------------
// MRCM Option
//-------------------------------------------------
#ifndef _MRCM_SUPPORT
#define _MRCM_SUPPORT                                           _OFF
#endif


////////////
// Eeprom //
////////////

//-------------------------------------------------
// Eeprom Access Function Option
//-------------------------------------------------
#ifndef _EEPROM_ACCESS_FUNCTION_SUPPORT
#define _EEPROM_ACCESS_FUNCTION_SUPPORT                         _OFF
#endif

#ifndef _EEPROM_KERNEL_START_ADDRESS
#define _EEPROM_KERNEL_START_ADDRESS                            (_EEPROM_PAGE0_BANK0)
#endif


///////////
// Flash //
///////////

//-------------------------------------------------
// Flash Clock Option
//-------------------------------------------------
#ifndef _FLASH_CLK_SPEED
#define _FLASH_CLK_SPEED                                        _FLASH_FAST_SPEED
#endif

//-------------------------------------------------
// Flash Access Function Option
//-------------------------------------------------
#ifndef _FLASH_WRITE_FUNCTION_SUPPORT
#define _FLASH_WRITE_FUNCTION_SUPPORT                           _OFF
#endif

#ifndef _FLASH_READ_FUNCTION_SUPPORT
#define _FLASH_READ_FUNCTION_SUPPORT                            _OFF
#endif

#ifndef _FLASH_TYPE_W25X20A_OR_W25X21CL
#define _FLASH_TYPE_W25X20A_OR_W25X21CL                         _FLASH_W25X20A
#endif

#ifndef _FLASH_TYPE_W25X40CL_OR_W25X41CL
#define _FLASH_TYPE_W25X40CL_OR_W25X41CL                        _FLASH_W25X40CL
#endif

#ifndef _FLASH_TYPE_GD25Q16C_OR_GD25Q16
#define _FLASH_TYPE_GD25Q16C_OR_GD25Q16                         _FLASH_GD25Q16C
#endif

#ifndef _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F
#define _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F      _FLASH_MX25L3233F
#endif

#ifndef _FLASH_TYPE_GD25Q40B_OR_GD25Q41B
#define _FLASH_TYPE_GD25Q40B_OR_GD25Q41B                        _FLASH_GD25Q41B
#endif

#ifndef _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ
#define _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ                     _FLASH_W25Q16JVSIQ
#endif

#ifndef _FLASH_TYPE_FM25Q08_OR_FM25Q08A_OR_FM25Q08B
#define _FLASH_TYPE_FM25Q08_OR_FM25Q08A_OR_FM25Q08B             _FLASH_FM25Q08A
#endif

#ifndef _FLASH_TYPE_BY25D40C_OR_BY25D40ASTIG
#define _FLASH_TYPE_BY25D40C_OR_BY25D40ASTIG                    _FLASH_BY25D40C
#endif

#ifndef _FLASH_TYPE_W25Q32F_OR_W25Q32JVSSIQ
#define _FLASH_TYPE_W25Q32F_OR_W25Q32JVSSIQ                     _FLASH_W25Q32F
#endif

#ifndef _FLASH_TYPE_BY25D80ASTIG_OR_BY25Q80BSTIG
#define _FLASH_TYPE_BY25D80ASTIG_OR_BY25Q80BSTIG                _FLASH_BY25D80ASTIG
#endif

#ifndef _FLASH_TYPE_AT25SF041_OR_AT25SF041B
#define _FLASH_TYPE_AT25SF041_OR_AT25SF041B                     _FLASH_AT25SF041
#endif

#ifndef _FLASH_TYPE_AT25SF321_OR_AT25SF321B
#define _FLASH_TYPE_AT25SF321_OR_AT25SF321B                     _FLASH_AT25SF321
#endif

#ifndef _FLASH_TYPE_EN25QH32A_OR_EN25QH32B
#define _FLASH_TYPE_EN25QH32A_OR_EN25QH32B                      _FLASH_EN25QH32A
#endif

#ifndef _FLASH_TYPE_IS25LQ040B_OR_IS25LP040E
#define _FLASH_TYPE_IS25LQ040B_OR_IS25LP040E                    _FLASH_IS25LQ040B
#endif

#ifndef _FLASH_TYPE_P25Q16H_OR_P25Q16SH
#define _FLASH_TYPE_P25Q16H_OR_P25Q16SH                         _FLASH_P25Q16H
#endif

#ifndef _FLASH_TYPE_EN25Q80_OR_EN25Q80C
#define _FLASH_TYPE_EN25Q80_OR_EN25Q80C                         _FLASH_EN25Q80
#endif

#ifndef _FLASH_TYPE_EN25Q40A_OR_EN25Q40B
#define _FLASH_TYPE_EN25Q40A_OR_EN25Q40B                        _FLASH_EN25Q40A
#endif

#ifndef _FLASH_TYPE_W25Q80BV_OR_W25Q80RVSNIQ
#define _FLASH_TYPE_W25Q80BV_OR_W25Q80RVSNIQ                    _FLASH_W25Q80BV
#endif

//-------------------------------------------------
// EEPROM Emulation Option
//-------------------------------------------------
#ifndef _SYSTEM_EEPROM_EMULATION_SUPPORT
#define _SYSTEM_EEPROM_EMULATION_SUPPORT                        _OFF
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_FLASH_BANK
#define _SYSTEM_EEPROM_EMULATION_FLASH_BANK                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_START_PAGE
#define _SYSTEM_EEPROM_EMULATION_START_PAGE                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_END_PAGE
#define _SYSTEM_EEPROM_EMULATION_END_PAGE                       0
#endif

#ifndef _START_OF_PAGEID
#define _START_OF_PAGEID                                        _PAGEID_0
#endif

#ifndef _END_OF_PAGEID
#define _END_OF_PAGEID                                          _PAGEID_0
#endif

#ifndef _CHECKSUM_VERSIONCODE_ID
#define _CHECKSUM_VERSIONCODE_ID                                _PAGEID_0
#endif

//--------------------------------------------------
// SPI Option
//--------------------------------------------------
#ifndef _SPI0_SUPPORT
#define _SPI0_SUPPORT                                           _OFF
#endif

#ifndef _SPI0_SETTING_SOURCE
#define _SPI0_SETTING_SOURCE                                    _SPI_SETTING_BY_PROJECT
#endif

#ifndef _SPI1_SUPPORT
#define _SPI1_SUPPORT                                           _OFF
#endif

#ifndef _SPI1_SETTING_SOURCE
#define _SPI1_SETTING_SOURCE                                    _SPI_SETTING_BY_PROJECT
#endif

#ifndef _SPI2_SUPPORT
#define _SPI2_SUPPORT                                           _OFF
#endif

#ifndef _SPI2_SETTING_SOURCE
#define _SPI2_SETTING_SOURCE                                    _SPI_SETTING_BY_PROJECT
#endif


//////////
// EDID //
//////////

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#ifndef _EDID_ADDRESS_EEPROM
#define _EDID_ADDRESS_EEPROM                                    (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _EDID_ADDRESS_FLASH
#define _EDID_ADDRESS_FLASH                                     (0)
#endif

#ifndef _EDID_FLASH_BANK
#define _EDID_FLASH_BANK                                        (0)
#endif

//-------------------------------------------------
// HDR10 EDID Auto Switch Option
//-------------------------------------------------
#ifndef _EDID_HDR10_AUTO_SWITCH
#define _EDID_HDR10_AUTO_SWITCH                                 _ON
#endif


//////////////
// HDCP Key //
//////////////

//-------------------------------------------------
// HDCP Key Location Option
//-------------------------------------------------
#ifndef _HDCP_1_4_KEY_LOCATION
#define _HDCP_1_4_KEY_LOCATION                                  _TABLE_LOCATION_SYSTEM_EEPROM
#endif

#ifndef _RX_HDCP_2_2_KEY_LOCATION
#define _RX_HDCP_2_2_KEY_LOCATION                               _TABLE_LOCATION_CODE
#endif

#ifndef _TX_HDCP_2_2_KEY_LOCATION
#define _TX_HDCP_2_2_KEY_LOCATION                               _TABLE_LOCATION_CODE
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_EEPROM
#define _RX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_FLASH
#define _RX_HDCP_1_4_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_1_4_KEY_FLASH_BANK
#define _RX_HDCP_1_4_KEY_FLASH_BANK                             (0)
#endif

#ifndef _RX_HDCP_2_2_KEY_ADDRESS_EEPROM
#define _RX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_2_2_KEY_ADDRESS_FLASH
#define _RX_HDCP_2_2_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_2_2_KEY_FLASH_BANK
#define _RX_HDCP_2_2_KEY_FLASH_BANK                             (0)
#endif

#ifndef _TX_HDCP_1_4_KEY_ADDRESS_EEPROM
#define _TX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _TX_HDCP_1_4_KEY_ADDRESS_FLASH
#define _TX_HDCP_1_4_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _TX_HDCP_1_4_KEY_FLASH_BANK
#define _TX_HDCP_1_4_KEY_FLASH_BANK                             (0)
#endif

#ifndef _TX_HDCP_2_2_KEY_ADDRESS_EEPROM
#define _TX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _TX_HDCP_2_2_KEY_ADDRESS_FLASH
#define _TX_HDCP_2_2_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _TX_HDCP_2_2_KEY_FLASH_BANK
#define _TX_HDCP_2_2_KEY_FLASH_BANK                             (0)
#endif


///////////////////
// System Source //
///////////////////

//-------------------------------------------------
// System Auto Search Style Option
//-------------------------------------------------
#ifndef _SOURCE_AUTO_SEARCH_STYLE
#define _SOURCE_AUTO_SEARCH_STYLE                               _SOURCE_POLLING_IN_SEARCH_STATE
#endif

//-------------------------------------------------
// System Source Search Time Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI                        SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI_FRL
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI_FRL                    SEC(8)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP
#define _SOURCE_DEFAULT_SEARCH_TIME_DP                          SEC(3)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C
#define _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C                      SEC(4.5)
#endif

//-------------------------------------------------
// System Required Time for External HDMI Switch
//-------------------------------------------------
#ifndef _SOURCE_HDMI_SWITCH_TIMEOUT_TIME
#define _SOURCE_HDMI_SWITCH_TIMEOUT_TIME                        SEC(4)
#endif


//////////////////
// System Judge //
//////////////////

//-------------------------------------------------
// System Display Setting Check Time Option
//-------------------------------------------------
#ifndef _WAIT_TIME_TO_ACTIVE_DVI
#define _WAIT_TIME_TO_ACTIVE_DVI                                SEC(0.1)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_HDMI
#define _WAIT_TIME_TO_ACTIVE_HDMI                               SEC(0.1)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_DP
#define _WAIT_TIME_TO_ACTIVE_DP                                 SEC(0.1)
#endif

//--------------------------------------------------
// System Support Timing Option
//--------------------------------------------------
#ifndef _OOR_H_FREQ_UPPER_BOUND
#define _OOR_H_FREQ_UPPER_BOUND                                 4000 // Unit in 0.1 kHZ
#endif

#ifndef _OOR_H_FREQ_LOWER_BOUND
#define _OOR_H_FREQ_LOWER_BOUND                                 100  // Unit in 0.1 kHZ
#endif

#ifndef _OOR_V_FREQ_UPPER_BOUND
#define _OOR_V_FREQ_UPPER_BOUND                                 2500 // Unit in 0.1 HZ
#endif

#ifndef _OOR_V_FREQ_LOWER_BOUND
#define _OOR_V_FREQ_LOWER_BOUND                                 230  // Unit in 0.1 HZ
#endif

#ifndef _OOR_H_WIDTH_UPPER_BOUND
#define _OOR_H_WIDTH_UPPER_BOUND                                8192 // Unit in pixel
#endif

#ifndef _OOR_V_HEIGHT_LOWER_BOUND
#define _OOR_V_HEIGHT_LOWER_BOUND                               240  // Unit in line
#endif

#ifndef _FAIL_SAVE_H_FREQ_UPPER_BOUND
#define _FAIL_SAVE_H_FREQ_UPPER_BOUND                           4000 // Unit in 0.1 kHZ
#endif

#ifndef _FAIL_SAVE_H_FREQ_LOWER_BOUND
#define _FAIL_SAVE_H_FREQ_LOWER_BOUND                           110  // Unit in 0.1 kHZ
#endif

#ifndef _FAIL_SAVE_V_FREQ_UPPER_BOUND
#define _FAIL_SAVE_V_FREQ_UPPER_BOUND                           1500 // Unit in 0.1 HZ
#endif

#ifndef _FAIL_SAVE_V_FREQ_LOWER_BOUND
#define _FAIL_SAVE_V_FREQ_LOWER_BOUND                           230  // Unit in 0.1 HZ
#endif

#ifndef _INPUTCLOCK_RANG_DVI
#define _INPUTCLOCK_RANG_DVI                                    3400 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_HDMI
#define _INPUTCLOCK_RANG_HDMI                                   6000 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_HDMI21
#define _INPUTCLOCK_RANG_HDMI21                                 14000 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_DP
#define _INPUTCLOCK_RANG_DP                                     12000 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_USBC
#define _INPUTCLOCK_RANG_USBC                                   12000 // Unit in 0.1 MHz
#endif


////////////////
//    HDMI    //
////////////////

//--------------------------------------------------
// HDMI Option
//--------------------------------------------------
#ifndef _DVI_DE_ONLY_SUPPORT
#define _DVI_DE_ONLY_SUPPORT                                    _OFF
#endif

#ifndef _HDMI_FREESYNC_SUPPORT
#define _HDMI_FREESYNC_SUPPORT                                  _OFF
#endif

#ifndef _HDMI_FREESYNC_II_SUPPORT
#define _HDMI_FREESYNC_II_SUPPORT                               _OFF
#endif

#ifndef _HDMI_HDR10_SUPPORT
#define _HDMI_HDR10_SUPPORT                                     _OFF
#endif

#ifndef _HDMI_FREESYNC_REPLAY_SUPPORT
#define _HDMI_FREESYNC_REPLAY_SUPPORT                           _OFF
#endif

#ifndef _HDMI_SBTM_SUPPORT
#define _HDMI_SBTM_SUPPORT                                      _OFF
#endif

//--------------------------------------------------
// TMDS Z0's HPD DDC Check Optional
//--------------------------------------------------
#ifndef _TMDS_HDCP_2_2_SUPPORT
#define _TMDS_HDCP_2_2_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// HDMI CTS Option
//--------------------------------------------------
#ifndef _TMDS_HDCP_FEATURE
#define _TMDS_HDCP_FEATURE                                      _HDCP_FEATURE_BY_INPUT
#endif

#ifndef _TMDS_Z0_POWER_SAVING_OPTION
#define _TMDS_Z0_POWER_SAVING_OPTION                            _ALL_CHANNEL_CONNECTED_FOR_CTS
#endif

#ifndef _HDMI_CEC_CTS_SELF_TEST_MODE
#define _HDMI_CEC_CTS_SELF_TEST_MODE                            _OFF
#endif

//--------------------------------------------------
// HDMI2.0 CTS Option (For SCDC Test)
//--------------------------------------------------
#ifndef _HDMI_SINK_MANUFACTURE_OUI_H
#define _HDMI_SINK_MANUFACTURE_OUI_H                            0x00 // SCDC 0xD2
#endif

#ifndef _HDMI_SINK_MANUFACTURE_OUI_M
#define _HDMI_SINK_MANUFACTURE_OUI_M                            0x00 // SCDC 0xD1
#endif

#ifndef _HDMI_SINK_MANUFACTURE_OUI_L
#define _HDMI_SINK_MANUFACTURE_OUI_L                            0x00 // SCDC 0xD0
#endif

#ifndef _HDMI_SINK_RTK_ID_STRING_H
#define _HDMI_SINK_RTK_ID_STRING_H                              0x00
#endif

#ifndef _HDMI_SINK_RTK_ID_STRING_L
#define _HDMI_SINK_RTK_ID_STRING_L                              0x00
#endif

//--------------------------------------------------
// HDMI2.1 Option
//--------------------------------------------------
#ifndef _HDMI_FRL_MAX_FFE_LEVEL
#define _HDMI_FRL_MAX_FFE_LEVEL                                 _HDMI_FRL_FFE0
#endif

#ifndef _HDMI_FRL_LT_MAX_TIME
#define _HDMI_FRL_LT_MAX_TIME                                   200
#endif

#ifndef _HDMI21_GAMING_VRR_SUPPORT
#define _HDMI21_GAMING_VRR_SUPPORT                              _OFF
#endif

#ifndef _HDMI21_QMS_VRR_SUPPORT
#define _HDMI21_QMS_VRR_SUPPORT                                 _OFF
#endif

#ifndef _HDMI21_FVA_SUPPORT
#define _HDMI21_FVA_SUPPORT                                     _OFF
#endif

#ifndef _HDMI21_RX_DSC_DECODER_SUPPORT
#define _HDMI21_RX_DSC_DECODER_SUPPORT                          _OFF
#endif

#ifndef _HDMI21_ALLM_SUPPORT
#define _HDMI21_ALLM_SUPPORT                                    _OFF
#endif

#ifndef _HDMI21_CCBPC_SUPPORT
#define _HDMI21_CCBPC_SUPPORT                                   _OFF
#endif

#ifndef _HDMI21_FRL_CTS_FAKE_POWER_SAVING_SUPPORT
#define _HDMI21_FRL_CTS_FAKE_POWER_SAVING_SUPPORT               _OFF
#endif


////////
// DP //
////////

//-------------------------------------------------
// DP Capability Option
//-------------------------------------------------
#ifndef _DP_MST_SUPPORT
#define _DP_MST_SUPPORT                                         _OFF
#endif

#ifndef _DP_MST_PXP_MODE_SUPPORT
#define _DP_MST_PXP_MODE_SUPPORT                                _OFF
#endif

#ifndef _DP_FREESYNC_SUPPORT
#define _DP_FREESYNC_SUPPORT                                    _OFF
#endif

#ifndef _DP_FREESYNC_II_SUPPORT
#define _DP_FREESYNC_II_SUPPORT                                 _OFF
#endif

#ifndef _DP_ADAPTIVESYNC_SUPPORT
#define _DP_ADAPTIVESYNC_SUPPORT                                _OFF
#endif

#ifndef _DP_HDR10_SUPPORT
#define _DP_HDR10_SUPPORT                                       _OFF
#endif

#ifndef _DP_RX_COLOR_FORMAT_420_SUPPORT
#define _DP_RX_COLOR_FORMAT_420_SUPPORT                         _OFF
#endif

#ifndef _DP_RX_DSC_DECODER_SUPPORT
#define _DP_RX_DSC_DECODER_SUPPORT                              _OFF
#endif

#ifndef _DP_TX_DSC_PASSTHROUGH_SUPPORT
#define _DP_TX_DSC_PASSTHROUGH_SUPPORT                          ((_DP_MST_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
#endif

#ifndef _DP_TX_SST_CLONE_PATH_TYPE
#define _DP_TX_SST_CLONE_PATH_TYPE                              _DP_TX_CLONE_VESA_STREAM_ONLY // _DP_TX_CLONE_BOTH_VESA_STREAM_DSC_PASSTHROUGH Need (_DP_RX_DSC_DECODER_SUPPORT = _ON) And (_DP_TX_DSC_PASSTHROUGH_SUPPORT = _ON)
#endif

#ifndef _DP_HDCP_2_2_SUPPORT
#define _DP_HDCP_2_2_SUPPORT                                    _OFF
#endif

#ifndef _DP_HBE_SUPPORT
#define _DP_HBE_SUPPORT                                         _OFF
#endif

#ifndef _DP_HBLANKING_REDUCTION_SUPPORT
#define _DP_HBLANKING_REDUCTION_SUPPORT                         _OFF
#endif

#ifndef _DP_PR_MODE_SUPPORT
#define _DP_PR_MODE_SUPPORT                                     _OFF
#endif

#ifndef _DP_TX_UHBR_PHY_CTS_ONLY
#define _DP_TX_UHBR_PHY_CTS_ONLY                                _OFF
#endif

//-------------------------------------------------
// DP INT/WD Option
//-------------------------------------------------
#ifndef _DP_8B10B_DEC_ERROR_WD_SUPPORT
#define _DP_8B10B_DEC_ERROR_WD_SUPPORT                          _OFF
#endif

//-------------------------------------------------
// DP Tx Lttpr Mode Option For 8b/10b
//-------------------------------------------------
#ifndef _DP_TX_LTTPR_MODE_8B10B
#define _DP_TX_LTTPR_MODE_8B10B                                 _DP_TX_LTTPR_NON_LTTPR_MODE
#endif


////////////
// TYPE C //
////////////

//--------------------------------------------------
// USB Type C & Billboard Option
//--------------------------------------------------
#ifndef _USB_PRODUCT_ID_H
#define _USB_PRODUCT_ID_H                                       0x00
#endif

#ifndef _USB_PRODUCT_ID_L
#define _USB_PRODUCT_ID_L                                       0x00
#endif

#ifndef _USB_XID_BYTE3
#define _USB_XID_BYTE3                                          0x00
#endif

#ifndef _USB_XID_BYTE2
#define _USB_XID_BYTE2                                          0x00
#endif

#ifndef _USB_XID_BYTE1
#define _USB_XID_BYTE1                                          0x00
#endif

#ifndef _USB_XID_BYTE0
#define _USB_XID_BYTE0                                          0x00
#endif

//--------------------------------------------------
// USB Type C Port Controller Option
//--------------------------------------------------
#ifndef _TYPE_C_POWER_SOURCE
#define _TYPE_C_POWER_SOURCE                                    _TYPE_C_SELF_POWER_ONLY
#endif

//--------------------------------------------------
// USB Type C Embedded Port Controller Option
//--------------------------------------------------
#ifndef _TYPE_C_EMB_PD_VERSION
#define _TYPE_C_EMB_PD_VERSION                                  _PD_VERSION_3_0
#endif

#ifndef _TYPE_C_EMB_CTS_FLOW
#define _TYPE_C_EMB_CTS_FLOW                                    _OFF
#endif

#ifndef _TYPE_C_EMB_CTS_FORCE_POWER_NORMAL
#define _TYPE_C_EMB_CTS_FORCE_POWER_NORMAL                      _OFF
#endif


////////////
// USB3   //
////////////

//--------------------------------------------------
// USB3 Power Saving Option
//--------------------------------------------------
#ifndef _USB3_LOW_POWER_CONSUME_IN_POWER_SAVING
#define _USB3_LOW_POWER_CONSUME_IN_POWER_SAVING                 _OFF
#endif


/////////
// USB //
/////////

//--------------------------------------------------
// Billboard String Dp Option (if Support ON, Users Have To Provide DP String Table)
//--------------------------------------------------
#ifndef _USER_TYPE_C_BB_STRING_DP_SUPPORT
#define _USER_TYPE_C_BB_STRING_DP_SUPPORT                       _OFF
#endif

#ifndef _USER_TYPE_C_BB_STRING_DP
#define _USER_TYPE_C_BB_STRING_DP                               0
#endif

//--------------------------------------------------
// Billboard String Brand Option (if Support ON, Users Have To Provide Brand String Table)
//--------------------------------------------------
#ifndef _USER_TYPE_C_BB_STRING_LENOVO_SUPPORT
#define _USER_TYPE_C_BB_STRING_LENOVO_SUPPORT                   _OFF
#endif

#ifndef _USER_TYPE_C_BB_STRING_LENOVO
#define _USER_TYPE_C_BB_STRING_LENOVO                           0
#endif

//--------------------------------------------------
// U2Host(EHCI) Mass Storge Program Support Option
//--------------------------------------------------
#ifndef _USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT
#define _USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT             _OFF
#endif

#ifndef _USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK
#define _USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK             _OFF
#endif

#ifndef _USER_USB2_FILE_NAME_STRING
#define _USER_USB2_FILE_NAME_STRING                             0
#endif

#ifndef _USER_USB2_FOLDER_NAME_STRING
#define _USER_USB2_FOLDER_NAME_STRING                           0
#endif

#ifndef _USB2_HOST_1ST_SUB_FOLDER_SUPPORT
#define _USB2_HOST_1ST_SUB_FOLDER_SUPPORT                       _OFF
#endif

#ifndef _USB2_HOST_FILE_NAME_JUDGE_VERSION
#define _USB2_HOST_FILE_NAME_JUDGE_VERSION                      _OFF
#endif

#ifndef _USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN
#define _USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN                   0
#endif

#ifndef _USB2_HOST_FILE_NAME_VERSION_CHAR_LEN
#define _USB2_HOST_FILE_NAME_VERSION_CHAR_LEN                   0
#endif

#ifndef _USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT
#define _USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT                     _OFF
#endif

#ifndef _USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT
#define _USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT                    _OFF
#endif

//--------------------------------------------------
// U2Host(EHCI) Mass Storge Program Support Option
//--------------------------------------------------
#ifndef _USB2_HOST_OHCI_MOUSE_SUPPORT
#define _USB2_HOST_OHCI_MOUSE_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// Billboard String iAddtionalInfo Option (if Support ON, Users Have To Provide iAddtionalInfo String Table)
//--------------------------------------------------
#ifndef _USER_TYPE_C_BB_STRING_IADDTIONALINFO_SUPPORT
#define _USER_TYPE_C_BB_STRING_IADDTIONALINFO_SUPPORT           _OFF
#endif

#ifndef _USER_TYPE_C_BB_STRING_IADDTIONALINFO
#define _USER_TYPE_C_BB_STRING_IADDTIONALINFO                   0
#endif


///////////
// Audio //
///////////

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#ifndef _AUDIO_SUPPORT
#define _AUDIO_SUPPORT                                          _OFF
#endif

#ifndef _AUDIO_ARC_TX_SUPPORT_TYPE
#define _AUDIO_ARC_TX_SUPPORT_TYPE                              _AUDIO_ARC_TX_NOT_SUPPORT
#endif

#ifndef _AUDIO_DVC_FAST_CONTROL_SUPPORT
#define _AUDIO_DVC_FAST_CONTROL_SUPPORT                         _OFF  // To Resolve Short Audio Issue
#endif

//-------------------------------------------------
// Audio TTS Support Type Option
//-------------------------------------------------
#ifndef _AUDIO_TTS_SUPPORT_TYPE
#define _AUDIO_TTS_SUPPORT_TYPE                                 _AUDIO_TTS_NOT_SUPPORT
#endif

//--------------------------------------------------
//  Audio TTS Content Bit Format Options
//--------------------------------------------------
#ifndef _AUDIO_TTS_CONTENT_BIT_FORMAT
#define _AUDIO_TTS_CONTENT_BIT_FORMAT                           _AUDIO_TTS_CONTENT_16_BIT
#endif

//--------------------------------------------------
//  Audio TTS Content Frequency Options
//--------------------------------------------------
#ifndef _AUDIO_TTS_CONTENT_FREQUENCY
#define _AUDIO_TTS_CONTENT_FREQUENCY                            _AUDIO_TTS_CONTENT_16_KHZ
#endif

//--------------------------------------------------
//  Audio TTS Data Segment Size
//--------------------------------------------------
#ifndef _AUDIO_TTS_DATA_SEGMENT_SIZE
#define _AUDIO_TTS_DATA_SEGMENT_SIZE                            10
#endif

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#ifndef _AUDIO_ARC_TX_SUPPORT_TYPE
#define _AUDIO_ARC_TX_SUPPORT_TYPE                              _AUDIO_ARC_TX_NOT_SUPPORT
#endif

//-------------------------------------------------
// Audio DAC Option
//-------------------------------------------------
#ifndef _DAC_HP_OUTPUT_SUPPORT
#define _DAC_HP_OUTPUT_SUPPORT                                  _OFF  // Should be _OFF if the related pinout is used as GPIO funtion
#endif

#ifndef _DAC_SPEAKER_OUTPUT_SUPPORT
#define _DAC_SPEAKER_OUTPUT_SUPPORT                             _OFF // Should be _OFF if the related pinout is used as GPIO funtion
#endif

//-------------------------------------------------
// Audio Line In Option
//-------------------------------------------------
#ifndef _LINE_IN_SUPPORT
#define _LINE_IN_SUPPORT                                        _OFF
#endif

#ifndef _LINE_IN_DAC_AOUT_GAIN_DB
#define _LINE_IN_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 0.5dB for each step, Max Gain: 'b111(3.0dB)
#endif

#ifndef _LINE_IN_DAC_HPOUT_GAIN_DB
#define _LINE_IN_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 0.5dB for each step, Max Gain: 'b111(3.0dB)
#endif

#ifndef _LINE_IN_BOOST_GAIN_DB
#define _LINE_IN_BOOST_GAIN_DB                                  0x17                        // 0dB, 0.75dB for each step, Max Gain: 0x3F(30dB)
#endif

#ifndef _LINE_IN_VOLUME_MAX
#define _LINE_IN_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _LINE_IN_VOLUME_MIN
#define _LINE_IN_VOLUME_MIN                                     0x0000
#endif

//-------------------------------------------------
// Audio Digital Option
//-------------------------------------------------
#ifndef _DIGITAL_DAC_AOUT_GAIN_DB
#define _DIGITAL_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 0.5dB for each step, Max Gain: 'b111(3.0dB)
#endif

#ifndef _DIGITAL_DAC_HPOUT_GAIN_DB
#define _DIGITAL_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 0.5dB for each step, Max Gain: 'b111(3.0dB)
#endif

#ifndef _DIGITAL_VOLUME_MAX
#define _DIGITAL_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _DIGITAL_VOLUME_MIN
#define _DIGITAL_VOLUME_MIN                                     0x0000
#endif

//-------------------------------------------------
// Audio PS Option
//-------------------------------------------------
#ifndef _SLEEP_AUDIO_SUPPORT
#define _SLEEP_AUDIO_SUPPORT                                    _OFF
#endif

#ifndef _PS_AUDIO_INPUT
#define _PS_AUDIO_INPUT                                         _PS_AUDIO_LINE_IN
#endif


///////////////////
// Misc Function //
///////////////////

//-------------------------------------------------
// Instant Timer Events Option
//-------------------------------------------------
#ifndef _INSTANT_TIMER_EVENT_0
#define _INSTANT_TIMER_EVENT_0                                  _OFF
#endif

#ifndef _INSTANT_TIMER_EVENT_1
#define _INSTANT_TIMER_EVENT_1                                  _OFF
#endif

//--------------------------------------------------
// IRDA Option
//--------------------------------------------------
#ifndef _IR_SUPPORT
#define _IR_SUPPORT                                             _IR_OFF
#endif

