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
// ID Code      : RL6952_Project.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PROJECT == _RL6952_PROJECT)


/////////////
// General //
/////////////

//--------------------------------------------------
// Pcb Option
//--------------------------------------------------
#define _PCB_TYPE                                               _RL6952_QA_A_BGA4L_LVDS_2H2TC1DP_TCMST_LVDS

//--------------------------------------------------
// Panel Option
//--------------------------------------------------
#define _PANEL_TYPE                                             _AU_LVDS_21_5_WUXGA
#define _PANEL_POW_SEQ_FAST_MODE                                _ON

//-------------------------------------------------
// Multi-Display Option
//-------------------------------------------------
#define _2P_PIP_DISPLAY_SUPPORT                                 _ON
#define _2P_PBP_LR_DISPLAY_SUPPORT                              _ON

//--------------------------------------------------
// MTP BW Calculation Option (For PIP/3P)
//--------------------------------------------------
#define _MTP_MAIN_PREFER_TIMING_FRAME_RATE                      _PANEL_TYP_FRAME_RATE
#define _MTP_MAIN_ACCEPT_MIN_COLOR_DEPTH                        _COLOR_DEPTH_10_BITS
#define _MTP_SUB_PREFER_TIMING_FRAME_RATE                       _PANEL_TYP_FRAME_RATE
#define _MTP_SUB_ACCEPT_MIN_COLOR_DEPTH                         _COLOR_DEPTH_8_BITS
#define _MTP_OD_ACCEPT_MIN_PARAM                                _OD_PARAM_4_5_BPP
#define _MTP_OD_ACCEPT_MAX_PARAM                                _OD_PARAM_7_5_BPP

//--------------------------------------------------
// Osd Option
//--------------------------------------------------
#define _OSD_TYPE                                               _REALTEK_2020_OSD
#define _FOSD_SU_H_FACTOR_MIN                                   16 // HFactor = H input/ H output * 2^6 = 64 ~ 16 (x1 ~ x4)

#define _OSD_INCLUDE                                            "RTD2020Include.h"
#define _USER_FUNCTION_INCLUDE                                  "RTD2020UserInclude.h"
#define _USER_TIMER_INCLUDE                                     "RTD2020TimerInclude.h"
#define _FACTORY_INCLUDE                                        "RTDFactoryInclude.h"
#define _USER_HWIIC_INCLUDE                                     "RTD2020HWIICInclude.h"
#define _USER_FLASH_INCLUDE                                     "RTD2020FlashInclude.h"

#define _USER_VGA_MODE_TABLE_INCLUDE                            "RTD2020UserModeTable.h"
#define _DIGITAL_FILTER_ENHANCE_PHASE_TABLE                     "DigFilterEnhancePhaseTable.h"
#define _RINGING_FILTER_TABLE                                   "RingingFilterTable.h"


///////////
// DDCCI //
///////////

//-------------------------------------------------
// DDCCI Option
//-------------------------------------------------
#define _DDCCI0_RXBUF_LENGTH                                    16 // Only DDC-CI 0 can support OGC/OCC communication, Config length equal to 128 in OGC mode and 16 in other case
#define _DDCCI_RXBUF_LENGTH                                     16
#define _DDCCI_TXBUF_LENGTH                                     16
#define _DDCCI_TIMEOUT_LIMIT                                    50 // 0~65535ms

#define _CAPABILITIES_STRING_VGA                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 0E 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 1E 1F 20 30 3E 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"


/////////////////////
// Display Setting //
/////////////////////

//--------------------------------------------------
// Definitions of DDR3 Memory Size
//--------------------------------------------------
#define _EMBEDDED_MEMORY_SIZE_CONFIG                            _1G_16BIT_DDR3_1PC_NORMAL

//-------------------------------------------------
// FW DDR3 PLL Freq
//-------------------------------------------------
#define _FW_DDR_PLL_CLOCK                                       _MEMORY_SPEED_1066MHZ // DDR3 Support Speed : 933MHz/1066MHz

//-------------------------------------------------
// OD Option
//-------------------------------------------------
#define _OD_FUNCTION                                            _ON
#define _OD_BY_POSITION_SUPPORT                                 _OFF

//-------------------------------------------------
// FRC Option
//-------------------------------------------------
#define _FRC_SUPPORT                                            _ON
#define _M_DOMAIN_IMG_CMP_SUPPORT                               _ON
#define _M_DOMAIN_IMG_CMP_10_BIT_SUPPORT                        _ON

//-------------------------------------------------
// Display Rotation Option
//-------------------------------------------------
#define _DISPLAY_ROTATION_SUPPORT                               _OFF

//--------------------------------------------------
// Aspect Ratio Option
//--------------------------------------------------
#define _ASPECT_RATIO_SUPPORT                                   _ON
#define _ASPECT_ORIGINAL_MODE_SUPPORT                           _ON

//--------------------------------------------------
// Overscan Option
//--------------------------------------------------
#define _OVERSCAN_DVI_SUPPORT                                   _ON
#define _OVERSCAN_HDMI_SUPPORT                                  _ON
#define _OVERSCAN_DP_SUPPORT                                    _ON

#define _OVERSCAN_H_RATIO                                       30
#define _OVERSCAN_V_RATIO                                       30

//-------------------------------------------------
// Adjust H & V Position Max Range Option
//-------------------------------------------------
#define _MAX_H_POSITION_RANGE                                   100 // Pixel
#define _MAX_V_POSITION_RANGE                                   100 // Line


////////////////////
// Color Function //
////////////////////

//--------------------------------------------------
// Digital Functional Option
//--------------------------------------------------
#define _I_DITHER_FUNCTION                                      _ON
#define _D_DITHER_FUNCTION                                      _ON
#define _GAMMA_FUNCTION                                         _ON
#define _COLOR_FORMAT_CONVERT_FUNCTION                          _ON
#define _RGB_QUANTIZATION_RANGE_FUNCTION                        _ON
#define _YCC_QUANTIZATION_RANGE_FUNCTION                        _ON
#define _ULTRA_VIVID_FUNCTION                                   _ON
#define _DCR_FUNCTION                                           _OFF
#define _DCC_FUNCTION                                           _ON
#define _DCC_HISTOGRM_INFO_FUNCTION                             _ON
#define _ICM_FUNCTION                                           _ON
#define _SCM_SUPPORT                                            _OFF
#define _SIX_COLOR_SUPPORT                                      _ON
#define _COLOR_DEMO_FUNCTION                                    _ON
#define _BORDER_WINDOW_FUNCTION                                 _ON
#define _SHARPNESS_FUNCTION                                     _ON
#define _CONTRAST_FUNCTION                                      _ON
#define _BRIGHTNESS_FUNCTION                                    _ON
#define _LOCAL_CONTRAST_FUNCTION                                _OFF

//-------------------------------------------------
// Hue and Saturation Option
//-------------------------------------------------
#define _GLOBAL_HUE_SATURATION_FUNCTION                         _ON

#define _HUE_MAX                                                230
#define _HUE_MIN                                                30
#define _SATURATION_MAX                                         200
#define _SATURATION_MIN                                         0


////////////////////////////////////////
// Off-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// PCM (Load Code Table) Option
//-------------------------------------------------
#define _PCM_FUNCTION                                           _OFF

//-------------------------------------------------
// 3D Gamma (Load Code Table) Option
//-------------------------------------------------
#define _RGB_3D_GAMMA_FUNCTION                                  _OFF


////////////////////////////////////////
// On-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// OGC and OCC (On-Line Calibration) Option
//-------------------------------------------------
#define _OCC_FUNCTION                                           _OFF
#define _OGC_FUNCTION                                           _OFF
#define _OGC_DICOM_FUNCTION                                     _OFF
#define _TWO_BRI_CALIBRATION_TYPE                               _TWO_BRI_CALIBRATION_NONE
#define _OCC_IG_NODE_1025_SUPPORT                               _OFF

#define _OGC_TOTAL_GAMMA                                        5 // 1/2/3/4/5
#define _OGC_TOTAL_CT                                           6
#define _OGC_TOTAL_DICOM                                        1 // 1/2
#define _OGC_FLASH_BANK                                         28

//-------------------------------------------------
// FreesyncII Option
//-------------------------------------------------
#define _FREESYNC_II_FLASH_BANK                                 30
#define _FREESYNC_II_FLASH_PAGE                                 0

//-------------------------------------------------
// Uniformity (On-Line Calibration) Option
//-------------------------------------------------
#define _UNIFORMITY_FUNCTION                                    _OFF

#define _UNIFORMITY_FLASH_BANK0                                 31

#define _UNIFORMITY_1ST_TABLE_LEVEL                             _UNIFORMITY_NONE
#define _UNIFORMITY_2ND_TABLE_LEVEL                             _UNIFORMITY_NONE
#define _UNIFORMITY_3RD_TABLE_LEVEL                             _UNIFORMITY_NONE
#define _UNIFORMITY_4TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#define _UNIFORMITY_5TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#define _UNIFORMITY_6TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#define _UNIFORMITY_7TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#define _UNIFORMITY_8TH_TABLE_LEVEL                             _UNIFORMITY_NONE
#define _UNIFORMITY_9TH_TABLE_LEVEL                             _UNIFORMITY_NONE

//-------------------------------------------------
// Local Dimming Option
//-------------------------------------------------
#define _LOCAL_DIMMING_FUNCTION                                 _OFF

//-------------------------------------------------
// Global Dimming Option
//-------------------------------------------------
#define _GLOBAL_DIMMING_FUNCTION                                _OFF

#define _DISPLAY_HDR_VERSION                                    _DISPLAY_HDR_VERSION_1_1

//-------------------------------------------------
// MRCM Option
//-------------------------------------------------
#define _MRCM_SUPPORT                                           _OFF

//-------------------------------------------------
// Anti-Aliasing Option
//-------------------------------------------------
#define _ANTI_ALIASING_FUNCTION                                 _OFF


////////////
// Eeprom //
////////////

//-------------------------------------------------
// Eeprom Access Function Option
//-------------------------------------------------
#define _EEPROM_ACCESS_FUNCTION_SUPPORT                         _ON

//-------------------------------------------------
// System Eeprom Start Address for Kernel Data Option
//-------------------------------------------------
#define _EEPROM_KERNEL_START_ADDRESS                            (_EEPROM_PAGE0_BANK0)


///////////
// Flash //
///////////

//-------------------------------------------------
// Flash Clock Option
//-------------------------------------------------
#define _FLASH_CLK_SPEED                                        _FLASH_FAST_SPEED

//-------------------------------------------------
// Flash Access Function Option
//-------------------------------------------------
#define _FLASH_WRITE_FUNCTION_SUPPORT                           _OFF
#define _FLASH_READ_FUNCTION_SUPPORT                            _OFF

#define _FLASH_TYPE_W25X20A_OR_W25X21CL                         _FLASH_W25X20A
#define _FLASH_TYPE_W25X40CL_OR_W25X41CL                        _FLASH_W25X40CL
#define _FLASH_TYPE_GD25Q16C_OR_GD25Q16                         _FLASH_GD25Q16C
#define _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F      _FLASH_MX25L3233F
#define _FLASH_TYPE_GD25Q40B_OR_GD25Q41B                        _FLASH_GD25Q41B
#define _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ                     _FLASH_W25Q16JVSIQ
#define _FLASH_TYPE_FM25Q08_OR_FM25Q08A_OR_FM25Q08B             _FLASH_FM25Q08A
#define _FLASH_TYPE_BY25D40C_OR_BY25D40ASTIG                    _FLASH_BY25D40C
#define _FLASH_TYPE_W25Q32F_OR_W25Q32JVSSIQ                     _FLASH_W25Q32F
#define _FLASH_TYPE_BY25D80ASTIG_OR_BY25Q80BSTIG                _FLASH_BY25D80ASTIG
#define _FLASH_TYPE_AT25SF041_OR_AT25SF041B                     _FLASH_AT25SF041
#define _FLASH_TYPE_AT25SF321_OR_AT25SF321B                     _FLASH_AT25SF321
#define _FLASH_TYPE_EN25QH32A_OR_EN25QH32B                      _FLASH_EN25QH32A
#define _FLASH_TYPE_IS25LQ040B_OR_IS25LP040E                    _FLASH_IS25LQ040B
#define _FLASH_TYPE_P25Q16H_OR_P25Q16SH                         _FLASH_P25Q16H
#define _FLASH_TYPE_EN25Q80_OR_EN25Q80C                         _FLASH_EN25Q80
#define _FLASH_TYPE_EN25Q40A_OR_EN25Q40B                        _FLASH_EN25Q40A
#define _FLASH_TYPE_W25Q80BV_OR_W25Q80RVSNIQ                    _FLASH_W25Q80BV

//-------------------------------------------------
// EEPROM Emulation Option
//-------------------------------------------------
#define _SYSTEM_EEPROM_EMULATION_SUPPORT                        _OFF

#define _SYSTEM_EEPROM_EMULATION_FLASH_BANK                     11
#define _SYSTEM_EEPROM_EMULATION_START_PAGE                     11
#define _SYSTEM_EEPROM_EMULATION_END_PAGE                       12
#define _START_OF_PAGEID                                        _PAGEID_0
#define _END_OF_PAGEID                                          _PAGEID_0
#define _CHECKSUM_VERSIONCODE_ID                                _PAGEID_0


//////////
// EDID //
//////////

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#define _EDID_ADDRESS_EEPROM                                    (_EEPROM_PAGE7_BANK0)
#define _EDID_ADDRESS_FLASH                                     0
#define _EDID_FLASH_BANK                                        9
#define _EDID_HDR10_AUTO_SWITCH                                 _ON


//////////////
// HDCP Key //
//////////////

//-------------------------------------------------
// HDCP Key Location Option
//-------------------------------------------------
#define _HDCP_1_4_KEY_LOCATION                                  _TABLE_LOCATION_CODE
#define _RX_HDCP_2_2_KEY_LOCATION                               _TABLE_LOCATION_CODE
#define _TX_HDCP_2_2_KEY_LOCATION                               _TABLE_LOCATION_CODE

//-------------------------------------------------
// For HDCP 1.4 Rx Key (FW Size : 325 Bytes ; Tool Size : 376 Bytes)
//-------------------------------------------------
#define _RX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE2_BANK1)
#define _RX_HDCP_1_4_KEY_ADDRESS_FLASH                          0
#define _RX_HDCP_1_4_KEY_FLASH_BANK                             8

//-------------------------------------------------
// For HDCP 2.2 Rx Key (FW Size : 1118 Bytes ; Tool Size : 1120 Bytes)
//-------------------------------------------------
#define _RX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE6_BANK0)
#define _RX_HDCP_2_2_KEY_ADDRESS_FLASH                          0
#define _RX_HDCP_2_2_KEY_FLASH_BANK                             15

//-------------------------------------------------
// For HDCP 1.4 Tx Key (FW Size : 325 Bytes ; Tool Size : 376 Bytes)
//-------------------------------------------------
#define _TX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE4_BANK0)
#define _TX_HDCP_1_4_KEY_ADDRESS_FLASH                          0x180
#define _TX_HDCP_1_4_KEY_FLASH_BANK                             8

//-------------------------------------------------
// For HDCP 2.2 Tx Key (FW Size : 900 Bytes ; Tool Size : 935 Bytes)
//-------------------------------------------------
#define _TX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE8_BANK0)
#define _TX_HDCP_2_2_KEY_ADDRESS_FLASH                          0x180
#define _TX_HDCP_2_2_KEY_FLASH_BANK                             15


///////////////////
// System Source //
///////////////////

//-------------------------------------------------
// System Auto Search Style Option
//-------------------------------------------------
#define _SOURCE_AUTO_SEARCH_STYLE                               _SOURCE_POLLING_IN_SEARCH_STATE

//-------------------------------------------------
// System Source Search Time Option
//-------------------------------------------------
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI                        SEC(2)
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI_FRL                    SEC(8)
#define _SOURCE_DEFAULT_SEARCH_TIME_DP                          SEC(3)
#define _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C                      SEC(4.5)
#define _SOURCE_HDMI_SWITCH_TIMEOUT_TIME                        SEC(4)


//////////////////
// System Judge //
//////////////////

//-------------------------------------------------
// System Display Setting Check Time Option
//-------------------------------------------------
#define _WAIT_TIME_TO_ACTIVE_DVI                                SEC(0.1)
#define _WAIT_TIME_TO_ACTIVE_HDMI                               SEC(0.1)
#define _WAIT_TIME_TO_ACTIVE_DP                                 SEC(0.1)

//--------------------------------------------------
// System Support Timing Option
//--------------------------------------------------
#define _OOR_H_FREQ_UPPER_BOUND                                 4000 // Unit in 0.1 kHZ
#define _OOR_H_FREQ_LOWER_BOUND                                 100  // Unit in 0.1 kHZ
#define _OOR_V_FREQ_UPPER_BOUND                                 2500 // Unit in 0.1 HZ
#define _OOR_V_FREQ_LOWER_BOUND                                 230  // Unit in 0.1 HZ
#define _OOR_H_WIDTH_UPPER_BOUND                                8192 // Unit in pixel
#define _OOR_V_HEIGHT_LOWER_BOUND                               240  // Unit in line

#define _FAIL_SAVE_H_FREQ_UPPER_BOUND                           4000 // Unit in 0.1 kHZ
#define _FAIL_SAVE_H_FREQ_LOWER_BOUND                           110  // Unit in 0.1 kHZ
#define _FAIL_SAVE_V_FREQ_UPPER_BOUND                           2500 // Unit in 0.1 HZ
#define _FAIL_SAVE_V_FREQ_LOWER_BOUND                           230  // Unit in 0.1 HZ

#define _INPUTCLOCK_RANG_DVI                                    3400 // Unit in 0.1 MHz
#define _INPUTCLOCK_RANG_HDMI                                   12000 // Unit in 0.1 MHz
#define _INPUTCLOCK_RANG_HDMI21                                 24000 // Unit in 0.1 MHz
#define _INPUTCLOCK_RANG_DP                                     12000 // Unit in 0.1 MHz
#define _INPUTCLOCK_RANG_USBC                                   12000 // Unit in 0.1 MHz


////////////////
//    HDMI    //
////////////////

//--------------------------------------------------
// HDMI Option
//--------------------------------------------------
#define _DVI_DE_ONLY_SUPPORT                                    _ON
#define _HDMI_FREESYNC_SUPPORT                                  _OFF
#define _HDMI_FREESYNC_II_SUPPORT                               _OFF
#define _HDMI_HDR10_SUPPORT                                     _OFF
#define _TMDS_HDCP_2_2_SUPPORT                                  _ON
#define _HDMI21_GAMING_VRR_SUPPORT                              _OFF
#define _HDMI21_QMS_VRR_SUPPORT                                 _OFF
#define _HDMI21_FVA_SUPPORT                                     _OFF
#define _HDMI21_RX_DSC_DECODER_SUPPORT                          _OFF
#define _HDMI21_ALLM_SUPPORT                                    _OFF
#define _HDMI21_CCBPC_SUPPORT                                   _OFF
#define _HDMI_FREESYNC_REPLAY_SUPPORT                           _OFF
#define _HDMI_SBTM_SUPPORT                                      _OFF

//--------------------------------------------------
// HDMI CTS Option
//--------------------------------------------------
#define _TMDS_HDCP_FEATURE                                      _HDCP_FEATURE_BY_INPUT
#define _TMDS_Z0_POWER_SAVING_OPTION                            _ALL_CHANNEL_CONNECTED_FOR_CTS
#define _HDMI_CEC_CTS_SELF_TEST_MODE                            _OFF

//--------------------------------------------------
// HDMI2.0 CTS Option (For SCDC Test)
//--------------------------------------------------
#define _HDMI_SINK_MANUFACTURE_OUI_H                            0x00 // SCDC 0xD2
#define _HDMI_SINK_MANUFACTURE_OUI_M                            0xE0 // SCDC 0xD1
#define _HDMI_SINK_MANUFACTURE_OUI_L                            0x4C // SCDC 0xD0
#define _HDMI_SINK_RTK_ID_STRING_H                              0x20
#define _HDMI_SINK_RTK_ID_STRING_L                              0x00

//--------------------------------------------------
// HDMI2.1 Option
//--------------------------------------------------
#define _HDMI_FRL_MAX_FFE_LEVEL                                 _HDMI_FRL_FFE0
#define _HDMI_FRL_LT_MAX_TIME                                   200
#define _HDMI21_FRL_CTS_FAKE_POWER_SAVING_SUPPORT               _OFF


////////
// DP //
////////

//-------------------------------------------------
// DP Capability Option
//-------------------------------------------------
#define _DP_MST_SUPPORT                                         _ON
#define _DP_MST_PXP_MODE_SUPPORT                                _OFF
#define _DP_FREESYNC_SUPPORT                                    _OFF
#define _DP_FREESYNC_II_SUPPORT                                 _OFF
#define _DP_ADAPTIVESYNC_SUPPORT                                _OFF
#define _DP_HDR10_SUPPORT                                       _OFF
#define _DP_RX_COLOR_FORMAT_420_SUPPORT                         _ON
#define _DP_RX_DSC_DECODER_SUPPORT                              _ON
#define _DP_TX_DSC_PASSTHROUGH_SUPPORT                          _ON
#define _DP_TX_SST_CLONE_PATH_TYPE                              _DP_TX_CLONE_VESA_STREAM_ONLY
#define _DP_HDCP_2_2_SUPPORT                                    _ON
#define _DP_HBE_SUPPORT                                         _OFF
#define _DP_HBLANKING_REDUCTION_SUPPORT                         _ON
#define _DP_PR_MODE_SUPPORT                                     _OFF
#define _DP_TX_LTTPR_MODE_8B10B                                 _DP_TX_LTTPR_NON_TRANSPARENT_MODE
#define _DP_TX_UHBR_PHY_CTS_ONLY                                _OFF

//-------------------------------------------------
// DP INT/WD Option
//-------------------------------------------------
#define _DP_8B10B_DEC_ERROR_WD_SUPPORT                          _ON


////////////
// TYPE C //
////////////

//--------------------------------------------------
// USB Type C & Billboard Option
//--------------------------------------------------
#define _USB_PRODUCT_ID_H                                       0x20
#define _USB_PRODUCT_ID_L                                       0x00

#define _USB_XID_BYTE3                                          0x00
#define _USB_XID_BYTE2                                          0x00
#define _USB_XID_BYTE1                                          0x00
#define _USB_XID_BYTE0                                          0x00

//--------------------------------------------------
// USB Type C Port Controller Option
//--------------------------------------------------
#define _TYPE_C_POWER_SOURCE                                    _TYPE_C_SELF_POWER_ONLY

//--------------------------------------------------
// USB Type C Embedded Port Controller Option
//--------------------------------------------------
#define _TYPE_C_EMB_PD_VERSION                                  _PD_VERSION_3_0
#define _TYPE_C_EMB_CTS_FLOW                                    _OFF
#define _TYPE_C_EMB_CTS_FORCE_POWER_NORMAL                      _OFF


/////////
// Usb //
/////////

//--------------------------------------------------
// Billboard String Dp Option (if Support ON, Users Have To Provide DP String Table)
//--------------------------------------------------
#define _USER_TYPE_C_BB_STRING_DP_SUPPORT                       _ON
#define _USER_TYPE_C_BB_STRING_DP                               "RTD2020UserDPAltModeStringTable.h"

//--------------------------------------------------
// Billboard String Brand Option (if Support ON, Users Have To Provide Brand String Table)
//--------------------------------------------------
#define _USER_TYPE_C_BB_STRING_LENOVO_SUPPORT                   _OFF
#define _USER_TYPE_C_BB_STRING_LENOVO                           "RTD2020UserLenovoAltModeStringTable.h"

//--------------------------------------------------
// Billboard String iAddtionalInfoURL Option (if Support ON, Users Have To Provide iAddtionalInfoURL String Table)
//--------------------------------------------------
#define _USER_TYPE_C_BB_STRING_IADDTIONALINFO_SUPPORT           _OFF
#define _USER_TYPE_C_BB_STRING_IADDTIONALINFO                   "RTD2020UseriAddtionalInfoURLStringTable.h"

//--------------------------------------------------
// U2Host(EHCI) Mass Storge Program Support Option
//--------------------------------------------------
#define _USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT             _OFF
#define _USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK             _OFF
#define _USER_USB2_FILE_NAME_STRING                             "RTD2020UserFwFileNameStringTable.h"
#define _USER_USB2_FOLDER_NAME_STRING                           "RTD2020UserFwFolderNameStringTable.h"
#define _USB2_HOST_1ST_SUB_FOLDER_SUPPORT                       _OFF
#define _USB2_HOST_FILE_NAME_JUDGE_VERSION                      _OFF
#define _USB2_HOST_FILE_NAME_PROJECT_CHAR_LEN                   18
#define _USB2_HOST_FILE_NAME_VERSION_CHAR_LEN                   6
#define _USB2_HOST_FILE_SYSTEM_NTFS_SUPPORT                     _OFF
#define _USB2_HOST_FILE_SYSTEM_EXFAT_SUPPORT                    _OFF

//--------------------------------------------------
// U2Host(OHCI) Mouse Support Option
//--------------------------------------------------
#define _USB2_HOST_OHCI_MOUSE_SUPPORT                           _OFF


////////////
// USB3   //
////////////

//--------------------------------------------------
// USB3 Power Saving Option
//--------------------------------------------------
#define _USB3_LOW_POWER_CONSUME_IN_POWER_SAVING                 _ON


///////////
// Audio //
///////////

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#define _AUDIO_SUPPORT                                          _ON
#define _AUDIO_ARC_TX_SUPPORT_TYPE                              _AUDIO_ARC_TX_NOT_SUPPORT

#define _AUDIO_DVC_FAST_CONTROL_SUPPORT                         _ON // To Resolve Short Audio Issue

//-------------------------------------------------
// Audio DAC Option
//-------------------------------------------------
#define _DAC_HP_OUTPUT_SUPPORT                                  _ON // Should be _OFF if the related pinout is used as GPIO funtion
#define _DAC_SPEAKER_OUTPUT_SUPPORT                             _ON // Should be _OFF if the related pinout is used as GPIO funtion

//-------------------------------------------------
// Audio Line In Option
//-------------------------------------------------
#define _LINE_IN_SUPPORT                                        _ON

#define _LINE_IN_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 0.5dB for each step, Max Gain: 'b111(3.0dB)
#define _LINE_IN_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 0.5dB for each step, Max Gain: 'b111(3.0dB)
#define _LINE_IN_BOOST_GAIN_DB                                  0x17                        // 0dB, 0.75dB for each step, Max Gain: 0x3F(30dB)
#define _LINE_IN_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#define _LINE_IN_VOLUME_MIN                                     0x0000

//-------------------------------------------------
// Audio Digital Option
//-------------------------------------------------
#define _DIGITAL_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 0.5dB for each step, Max Gain: 'b111(3.0dB)
#define _DIGITAL_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 0.5dB for each step, Max Gain: 'b111(3.0dB)
#define _DIGITAL_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#define _DIGITAL_VOLUME_MIN                                     0x0000

//-------------------------------------------------
// Audio PS Option
//-------------------------------------------------
#define _SLEEP_AUDIO_SUPPORT                                    _ON

#define _PS_AUDIO_INPUT                                         _PS_AUDIO_DP

//--------------------------------------------------
// Audio TTS Option
//--------------------------------------------------
#define _AUDIO_TTS_SUPPORT_TYPE                                 _AUDIO_TTS_NOT_SUPPORT
#define _AUDIO_TTS_CONTENT_BIT_FORMAT                           _AUDIO_TTS_CONTENT_16_BIT
#define _AUDIO_TTS_CONTENT_FREQUENCY                            _AUDIO_TTS_CONTENT_16_KHZ
#define _AUDIO_TTS_DATA_SEGMENT_SIZE                            10


///////////////////
// Misc Function //
///////////////////

//-------------------------------------------------
// Instant Timer Events Option
//-------------------------------------------------
#define _INSTANT_TIMER_EVENT_0                                  _ON
#define _INSTANT_TIMER_EVENT_1                                  _OFF

//--------------------------------------------------
// IRDA Option
//--------------------------------------------------
#define _IR_SUPPORT                                             _IR_OFF

//--------------------------------------------------
// SPI Option
//--------------------------------------------------
#define _SPI0_SUPPORT                                           _OFF
#define _SPI0_SETTING_SOURCE                                    _SPI_SETTING_BY_PROJECT

#define _SPI1_SUPPORT                                           _OFF
#define _SPI1_SETTING_SOURCE                                    _SPI_SETTING_BY_PROJECT

#define _SPI2_SUPPORT                                           _OFF
#define _SPI2_SETTING_SOURCE                                    _SPI_SETTING_BY_PROJECT

#endif // End of #if(_PROJECT == _RL6952_PROJECT)
