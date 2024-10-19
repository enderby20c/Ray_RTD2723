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
// ID Code      : RL6952_QA_A_BGA2L_LVDS_1H2TC1DP_TCMST_LVDS.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6952_QA_A_BGA2L_LVDS_2H1TC1DP_TCMST_LVDS)


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#define _EXT_XTAL                                   _XTAL14318K


///////////////
// Debug DDC //
///////////////

//--------------------------------------------------
// Debug DDC Channel
//--------------------------------------------------
#define _PCB_DEBUG_DDC                              _VGA_DDC


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                         _D0_DP_PORT
#define _D0_DDC_CHANNEL_SEL                         _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE                _EDID_SIZE_384
#define _D0_EMBEDDED_DDCRAM_LOCATION                _EDID_TABLE_LOCATION_USER
#define _D0_DP_CONNECTOR_TYPE                       _DP_CONNECTOR_TYPE_C
#define _D0_DP_LINK_CLK_RATE                        _DP_ULTRA_SPEED_1350MHZ
#define _D0_DP_MAIN_LINK_LANES                      _DP_FOUR_LANE
#define _D0_USB_UFP_RX_OOBS_VTH                     _USB_UFP_RX_OOBS_VTH_LEVEL_3

// For USB Hub
#define _D0_USB_HUB_TYPE                            _USB_HUB_RTS
#define _D0_USB_U2_HUB_TRACE_TYPE                   _USB_U2_TRACE_GO_THROUGH_SCALER
#define _D0_USB_U3_HUB_TRACE_TYPE                   _USB_U3_TRACE_GO_THROUGH_SCALER
#define _D0_USB_SPEED                               _USB_3_GEN2
#define _D0_USB_LANE                                _USB_3_LANE_X1
#define _D0_USB_HUB_RTS_SLAVE_ADDR                  0x00
#define _D0_USB_RTS_SMBUS_IIC                       _NO_IIC_PIN

// For Type-C Connector
#define _D0_TYPE_C_PORT_CTRL_TYPE                   _PORT_CTRL_EMBEDDED
#define _D0_TYPE_C_BILLBOARD_TYPE                   _BILLBOARD_SCALER

// For RTS Port Controller
#define _D0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR         0x00

// For RTS / User Port Controller
#define _D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP             _SWAP_BY_SCALER
#define _D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION    _SWAP_BY_PORT_CTRL
#define _D0_TYPE_C_EXT_CC_ATTACH_DETECT             _EXT_PORT_CTRL_NOT_EXIST
#define _D0_TYPE_C_EXT_ALT_MODE_READY_DETECT        _EXT_PORT_CTRL_NOT_EXIST
#define _D0_TYPE_C_EXT_PD3_1_EPR_SUPPORT            _OFF

// For Embedded Port Controller
#define _D0_TYPE_C_EMB_PORT_ROLE                    _TYPE_C_PORT_DRP
#define _D0_TYPE_C_EMB_DRP_PREFER                   _TYPE_C_DRP_NO_PREFERENCE
#define _D0_TYPE_C_EMB_SRC_DEF_CUR                  _TYPE_C_SRC_DEF_3P0A
#define _D0_TYPE_C_EMB_USB_ROLE                     _TYPE_C_USB_DEVICE_ONLY
#define _D0_TYPE_C_EMB_CONNECTOR_TYPE               _TYPE_C_PORT_RECEPTACLE
#define _D0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT         _OFF
#define _D0_TYPE_C_EMB_PD3_PPS_SUPPORT              _OFF
#define _D0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF   _ON
#define _D0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT           _OFF
#define _D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT            _OFF
#define _D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT          _ON

// For Type-C Embedded Port Controller PMIC
#define _D0_TYPE_C_PMIC_TYPE                        _PMIC_SY9228
#define _D0_TYPE_C_PMIC_SLAVE_ADDRESS               0xE2
#define _D0_TYPE_C_PMIC_IIC                         _PMIC_HW_IIC_PIN_H12_J8_0_1
#define _D0_TYPE_C_PMIC_VBUS_ADC_CHANNEL            _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0
#define _D0_TYPE_C_PMIC_IOUT_ADC_CHANNEL            _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _D0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE            2400 // unit: 10mV
#define _D0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO     12
#define _D0_TYPE_C_PMIC_IOUT_MAX_CURRENT            1320 // unit: 10mA
#define _D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT          _OFF
#define _D0_TYPE_C_PMIC_FW_OVP_THRESHOLD            130 // Unit: %
#define _D0_TYPE_C_PMIC_FW_UVP_THRESHOLD            66 // Unit: %
#define _D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD       _TYPE_C_PMIC_FW_OCP_NONE
#define _D0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE        100 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _D0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN       0 // unit: ms, Maximum value: 61000
#define _D0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD        _TYPE_C_PMIC_INT_PIN_NONE
#define _D0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT      _OFF
#define _D0_TYPE_C_PMIC_SAFETY_POWER_LIMIT          100 // W
#define _D0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN       1000 // ms

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                         _D1_NO_PORT
#define _D1_DDC_CHANNEL_SEL                         _NO_DDC
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE                _EDID_SIZE_NONE
#define _D1_EMBEDDED_DDCRAM_LOCATION                _EDID_TABLE_LOCATION_CODE
#define _D1_USB_UFP_RX_OOBS_VTH                     _USB_UFP_RX_OOBS_VTH_LEVEL_3

// For USB Hub
#define _D1_USB_HUB_TYPE                            _USB_HUB_RTS
#define _D1_USB_U2_HUB_TRACE_TYPE                   _USB_U2_TRACE_GO_THROUGH_SCALER
#define _D1_USB_U3_HUB_TRACE_TYPE                   _USB_U3_TRACE_GO_THROUGH_SCALER
#define _D1_USB_SPEED                               _USB_3_GEN2
#define _D1_USB_LANE                                _USB_3_LANE_X1
#define _D1_USB_HUB_RTS_SLAVE_ADDR                  0x00
#define _D1_USB_RTS_SMBUS_IIC                       _NO_IIC_PIN

// For Type-C Connector
#define _D1_TYPE_C_PORT_CTRL_TYPE                   _PORT_CTRL_NONE
#define _D1_TYPE_C_BILLBOARD_TYPE                   _BILLBOARD_NONE

// For RTS Port Controller
#define _D1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR         0x00

// For RTS / User Port Controller
#define _D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP             _SWAP_BY_SCALER
#define _D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION    _SWAP_BY_PORT_CTRL
#define _D1_TYPE_C_EXT_CC_ATTACH_DETECT             _EXT_PORT_CTRL_NOT_EXIST
#define _D1_TYPE_C_EXT_ALT_MODE_READY_DETECT        _EXT_PORT_CTRL_NOT_EXIST
#define _D1_TYPE_C_EXT_PD3_1_EPR_SUPPORT            _OFF

// For Embedded Port Controller
#define _D1_TYPE_C_EMB_PORT_ROLE                    _TYPE_C_PORT_DRP
#define _D1_TYPE_C_EMB_DRP_PREFER                   _TYPE_C_DRP_NO_PREFERENCE
#define _D1_TYPE_C_EMB_SRC_DEF_CUR                  _TYPE_C_SRC_DEF_3P0A
#define _D1_TYPE_C_EMB_USB_ROLE                     _TYPE_C_USB_DEVICE_ONLY
#define _D1_TYPE_C_EMB_CONNECTOR_TYPE               _TYPE_C_PORT_RECEPTACLE
#define _D1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT         _OFF
#define _D1_TYPE_C_EMB_PD3_PPS_SUPPORT              _OFF
#define _D1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF   _OFF
#define _D1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT           _OFF
#define _D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT            _OFF
#define _D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT          _OFF

// For Type-C Embedded Port Controller PMIC
#define _D1_TYPE_C_PMIC_TYPE                        _PMIC_NONE
#define _D1_TYPE_C_PMIC_SLAVE_ADDRESS               0x00
#define _D1_TYPE_C_PMIC_IIC                         _PMIC_NO_IIC_PIN
#define _D1_TYPE_C_PMIC_VBUS_ADC_CHANNEL            _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _D1_TYPE_C_PMIC_IOUT_ADC_CHANNEL            _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _D1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE            2400 // unit: 10mV
#define _D1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO     12
#define _D1_TYPE_C_PMIC_IOUT_MAX_CURRENT            1320 // unit: 10mA
#define _D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT          _OFF
#define _D1_TYPE_C_PMIC_FW_OVP_THRESHOLD            130 // Unit: %
#define _D1_TYPE_C_PMIC_FW_UVP_THRESHOLD            66 // Unit: %
#define _D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD       _TYPE_C_PMIC_FW_OCP_NONE
#define _D1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE        100 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _D1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN       0 // unit: ms, Maximum value: 61000
#define _D1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD        _TYPE_C_PMIC_INT_PIN_NONE
#define _D1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT      _OFF
#define _D1_TYPE_C_PMIC_SAFETY_POWER_LIMIT          100 // W
#define _D1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN       1000 // ms

//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#define _D2_INPUT_PORT_TYPE                         _D2_DP_PORT
#define _D2_DDC_CHANNEL_SEL                         _DDC2
#define _D2_EMBEDDED_DDCRAM_MAX_SIZE                _EDID_SIZE_384
#define _D2_EMBEDDED_DDCRAM_LOCATION                _EDID_TABLE_LOCATION_USER
#define _D2_DP_CONNECTOR_TYPE                       _DP_CONNECTOR_MINI
#define _D2_DP_Z0_IMPEDANCE_OPTION                  _85_OHM
#define _D2_DP_LINK_CLK_RATE                        _DP_ULTRA_SPEED_1350MHZ
#define _D2_DP_MAIN_LINK_LANES                      _DP_FOUR_LANE

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                         _D3_HDMI_PORT
#define _D3_DDC_CHANNEL_SEL                         _DDC3
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE                _EDID_SIZE_384
#define _D3_EMBEDDED_DDCRAM_LOCATION                _EDID_TABLE_LOCATION_CODE
#define _D3_EDID_EXTERNAL_EEPROM_MAX_SIZE           _EDID_EEPROM_SIZE_256

#define _D3_HDMI_MAC_TYPE                           _HDMI_MAC_TMDS_FRL
#define _D3_HDMI_LINK_CLK_RATE                      _HDMI_LINK_SPEED_1200MHZ
#define _D3_HDMI_MAIN_LINK_LANES                    _HDMI_FOUR_LANE

//--------------------------------------------------
// D4 Input Port
//--------------------------------------------------
#define _D4_INPUT_PORT_TYPE                         _D4_HDMI_PORT
#define _D4_DDC_CHANNEL_SEL                         _DDC4
#define _D4_EMBEDDED_DDCRAM_MAX_SIZE                _EDID_SIZE_384
#define _D4_EMBEDDED_DDCRAM_LOCATION                _EDID_TABLE_LOCATION_USER
#define _D4_EDID_EXTERNAL_EEPROM_MAX_SIZE           _EDID_EEPROM_SIZE_256
#define _D4_MAX_HDMI_EDID_COUNT                     12

#define _D4_HDMI_MAC_TYPE                           _HDMI_MAC_TMDS_FRL
#define _D4_HDMI_LINK_CLK_RATE                      _HDMI_LINK_SPEED_1200MHZ
#define _D4_HDMI_MAIN_LINK_LANES                    _HDMI_FOUR_LANE

//--------------------------------------------------
// D7 Input Port
//--------------------------------------------------
//#define _D7_INPUT_PORT_TYPE                         _D7_DP_PORT
//#define _D7_D0_EMBEDDED_DDCRAM_SIZE                 _EDID_SIZE_384
//#define _D7_D1_EMBEDDED_DDCRAM_SIZE                 _EDID_SIZE_256
//#define _D7_EMBEDDED_DDCRAM_LOCATION                _EDID_TABLE_LOCATION_USER
//#define _D7_DP_CONNECTOR_TYPE                       _DP_CONNECTOR_DUAL_DP
//#define _D7_SEARCH_MAIN_PORT_ONLY                   _ON

//--------------------------------------------------
// D8 Input Port
//--------------------------------------------------
//#define _D8_INPUT_PORT_TYPE                         _D8_DP_PORT
//#define _D8_D1_EMBEDDED_DDCRAM_SIZE                 _EDID_SIZE_384
//#define _D8_D2_EMBEDDED_DDCRAM_SIZE                 _EDID_SIZE_256
//#define _D8_EMBEDDED_DDCRAM_LOCATION                _EDID_TABLE_LOCATION_USER
//#define _D8_DP_CONNECTOR_TYPE                       _DP_CONNECTOR_DUAL_DP
//#define _D8_SEARCH_MAIN_PORT_ONLY                   _ON

//--------------------------------------------------
// HDMI SRC 5V Detect By User
//--------------------------------------------------
#define _HDMI_5V_DETECT_BY_USER                     _OFF


/////////////////////////
// Repeater DFP Config //
/////////////////////////

//--------------------------------------------------
// Repeater DownStream Port Orientation
//--------------------------------------------------
#define _RETIMER_DFP_ORIENTATION                    _TYPE_C_DFP_ORIENTATION_UNFLIP


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _D0_INPUT_PORT_GROUP                        _INPUT_PORT_GROUP_0
// #define _D1_INPUT_PORT_GROUP                        _INPUT_PORT_GROUP_0
#define _D2_INPUT_PORT_GROUP                        _INPUT_PORT_GROUP_0
#define _D3_INPUT_PORT_GROUP                        _INPUT_PORT_GROUP_0
#define _D4_INPUT_PORT_GROUP                        _INPUT_PORT_GROUP_0
//#define _D7_INPUT_PORT_GROUP                        _INPUT_PORT_GROUP_0
//#define _D8_INPUT_PORT_GROUP                        _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                    _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                    _D2_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                    _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                    _D4_INPUT_PORT
//#define _INPUT_PORT_SEARCH_PRI_4                    _D4_INPUT_PORT
//#define _INPUT_PORT_SEARCH_PRI_5                    _D7_INPUT_PORT
//#define _INPUT_PORT_SEARCH_PRI_5                    _D8_INPUT_PORT


/////////////
// DP Port //
/////////////

//--------------------------------------------------
// DP Lane & PN Swap Option
//--------------------------------------------------
#define _D0_DP_PCB_LANE0_MAPPING                    _DP_SCALER_LANE0
#define _D0_DP_PCB_LANE1_MAPPING                    _DP_SCALER_LANE2
#define _D0_DP_PCB_LANE2_MAPPING                    _DP_SCALER_LANE1
#define _D0_DP_PCB_LANE3_MAPPING                    _DP_SCALER_LANE3
#define _D0_DP_PCB_LANE0_PN_SWAP                    _ON
#define _D0_DP_PCB_LANE1_PN_SWAP                    _OFF
#define _D0_DP_PCB_LANE2_PN_SWAP                    _ON
#define _D0_DP_PCB_LANE3_PN_SWAP                    _OFF

#define _D1_DP_PCB_LANE0_MAPPING                    _DP_SCALER_LANE0
#define _D1_DP_PCB_LANE1_MAPPING                    _DP_SCALER_LANE2
#define _D1_DP_PCB_LANE2_MAPPING                    _DP_SCALER_LANE1
#define _D1_DP_PCB_LANE3_MAPPING                    _DP_SCALER_LANE3
#define _D1_DP_PCB_LANE0_PN_SWAP                    _OFF
#define _D1_DP_PCB_LANE1_PN_SWAP                    _OFF
#define _D1_DP_PCB_LANE2_PN_SWAP                    _OFF
#define _D1_DP_PCB_LANE3_PN_SWAP                    _OFF

#define _D2_DP_PCB_LANE0_MAPPING                    _DP_SCALER_LANE0
#define _D2_DP_PCB_LANE1_MAPPING                    _DP_SCALER_LANE1
#define _D2_DP_PCB_LANE2_MAPPING                    _DP_SCALER_LANE2
#define _D2_DP_PCB_LANE3_MAPPING                    _DP_SCALER_LANE3
#define _D2_DP_PCB_LANE0_PN_SWAP                    _OFF
#define _D2_DP_PCB_LANE1_PN_SWAP                    _OFF
#define _D2_DP_PCB_LANE2_PN_SWAP                    _OFF
#define _D2_DP_PCB_LANE3_PN_SWAP                    _OFF


////////////////////////
// Output Port Config //
////////////////////////

//--------------------------------------------------
// P0 Output Port
//--------------------------------------------------
#define _P0_OUTPUT_TYPE                             _P0_DP_PORT

// For DP
#define _P0_DP_CONNECTOR_TYPE                       _DP_CONNECTOR_NORMAL
#define _P0_DP_LINK_CLK_RATE                        _DP_ULTRA_SPEED_1350MHZ
#define _P0_DP_MAIN_LINK_LANES                      _DP_FOUR_LANE


/////////////////////////
// U2HOST Port Support //
/////////////////////////

//--------------------------------------------------
// U2Host Port
//--------------------------------------------------
#define _USB2_HOST_PORT_SUPPORT                     _ON


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#if(_PANEL_LVDS_OUTPUT_PORT == _LVDS_2_PORT)
#define _LVDS_PORT_SEL                              _LVDS_2_PORT_CD
#define _LVDS_PORT_MIRROR                           _DISABLE
#define _LVDS_PORT_AB_SWAP                          _DISABLE
#define _LVDS_PORT_CD_SWAP                          _DISABLE
#define _LVDS_PN_SWAP                               _ENABLE

#elif(_PANEL_LVDS_OUTPUT_PORT == _LVDS_4_PORT)
#define _LVDS_PORT_SEL                              _LVDS_4_PORT_ABCD
#define _LVDS_PORT_MIRROR                           _DISABLE
#define _LVDS_PORT_AB_SWAP                          _ENABLE
#define _LVDS_PORT_CD_SWAP                          _DISABLE
#define _LVDS_PN_SWAP                               _DISABLE
#endif

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL                          _LVDS_DRIV_CONTROL_3_0
#define _LVDS_VCM_CONTROL                           _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                            _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                  _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                   _DISABLE

//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
#define _LVDS_SPREAD_RANGE                          10
#define _LVDS_SPREAD_SPEED                          _SPEED_33K


/////////////////////
// For eDPTx Panel //
/////////////////////

//--------------------------------------------------
// eDPTx Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_SWING_LEVEL                     _DP_SWING_800_MV
#define _PANEL_DPTX_PREEMPHASIS_LEVEL               _DP_PREEMPHASIS_3_5_DB

//--------------------------------------------------
// eDPTx SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_SPREAD_RANGE                    12
#define _PANEL_DPTX_SPREAD_SPEED                    _SPEED_33K

//--------------------------------------------------
// eDPTx 1.2 HBR2 FB/Lane Config
//--------------------------------------------------
#define _PANEL_DPTX_PORT_MIRROR                     _DISABLE
#define _PANEL_DPTX_PORT_1_LANE_SWAP                _DISABLE
#define _PANEL_DPTX_PORT_2_LANE_SWAP                _DISABLE
#define _PANEL_DPTX_PORT_1_LANE_PN_SWAP             _DISABLE
#define _PANEL_DPTX_PORT_2_LANE_PN_SWAP             _DISABLE


////////////////////
// V by One Panel //
////////////////////

//--------------------------------------------------
// V by One Main Link Config
//--------------------------------------------------
#define _PANEL_VBO_LANE_SWAP                        _DISABLE
#define _PANEL_VBO_ML_SWAP                          _DISABLE
#define _PANEL_VBO_SECTION_0_PN_SWAP                _ENABLE
#define _PANEL_VBO_LANE_DRIV_CONTROL                _VBO_DRIV_CONTROL_3_5
#define _PANEL_VBO_PRE_EMPHASIS_CONTROL             _VBO_PRE_EMPHASIS_0

//--------------------------------------------------
// V by One SSC Config
//--------------------------------------------------
#define _PANEL_VBO_SPREAD_RANGE                     0
#define _PANEL_VBO_SPREAD_SPEED                     _SPEED_30K


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                         _PWM_8BIT

#define _BACKLIGHT_PWM                              _PWM0
#define _BACKLIGHT_PWM_INVERSE                      _ON

#define _PWM0_EN                                    _ON
#define _PWM1_EN                                    _OFF
#define _PWM2_EN                                    _OFF
#define _PWM3_EN                                    _OFF
#define _PWM4_EN                                    _OFF
#define _PWM5_EN                                    _OFF

#define _PWM0_PSAV_EN                               _OFF
#define _PWM1_PSAV_EN                               _OFF
#define _PWM2_PSAV_EN                               _OFF
#define _PWM3_PSAV_EN                               _OFF
#define _PWM4_PSAV_EN                               _OFF
#define _PWM5_PSAV_EN                               _OFF

#define _PWM0_PDOW_EN                               _OFF
#define _PWM1_PDOW_EN                               _OFF
#define _PWM2_PDOW_EN                               _OFF
#define _PWM3_PDOW_EN                               _OFF
#define _PWM4_PDOW_EN                               _OFF
#define _PWM5_PDOW_EN                               _OFF

#define _PWM0_BYPASS_MODE_EN                        _OFF
#define _PWM1_BYPASS_MODE_EN                        _OFF
#define _PWM2_BYPASS_MODE_EN                        _OFF
#define _PWM3_BYPASS_MODE_EN                        _OFF
#define _PWM4_BYPASS_MODE_EN                        _OFF
#define _PWM5_BYPASS_MODE_EN                        _OFF

#define _PWM0_RST_EN                                _ON
#define _PWM1_RST_EN                                _OFF
#define _PWM2_RST_EN                                _OFF
#define _PWM3_RST_EN                                _OFF
#define _PWM4_RST_EN                                _OFF
#define _PWM5_RST_EN                                _OFF
#define _PWM_RST_SIGNAL_SEL                         _DVS

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#define _D3_TMDS_BR_SWAP                            _OFF
#define _D3_TMDS_PN_SWAP                            _ON
#define _D4_TMDS_BR_SWAP                            _OFF
#define _D4_TMDS_PN_SWAP                            _ON


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                             _OFF
#define _SW_IIC_CLK_DIV                             _DIV_1

#define _HW_IIC_SUPPORT                             _ON
#define _HW_IIC_SPEED                               _HW_IIC_LOW_SPEED_100K


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                                _EEPROM_24LC16
#define _EEPROM_SLAVE_ADDRESS                       0xA0
#define _PCB_SYS_EEPROM_IIC                         _HW_IIC_BGA_2L_PIN_AG16_AG17


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#define _AD_KEY_SUPPORT                             _ON

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#define _LOW_SPEED_ADC_SUPPORT                      _ON


/////////////////
// DP Cable ID //
/////////////////

//-----------------------------------------------
// Macro of DP Cable ID Detect Setting
//-----------------------------------------------
#define PCB_DP_UHBR_D2_CABLE_ID_DETECT_ADC_PIN()    (GET_SARADC_0_3_VALUE())

//-----------------------------------------------
// Macro of DP Cable ID Detect Setting
//-----------------------------------------------
#define SET_D2_CABLEID_DET_CONFIG1(x)               {SET_GPIO_2L_900PIN_PIN_E5(x);}

#define _D2_CABLEID_DET_CONFIG1_HIGH                1
#define _D2_CABLEID_DET_CONFIG1_LOW                 0

#define PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1(x)   {\
                                                        SET_D2_CABLEID_DET_CONFIG1(x);\
                                                    }

//--------------------------------------------------
// Macro of DP Cable ID ADC Capacitor Time
//--------------------------------------------------
#define _DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME 300 // Unit: us(50 ~ 1000), 6* tau = 141.2us for Rp = 680kOhm, Rd = 100kOhm, C = 270pF


//////////////////////
// Series Pin Share //
//////////////////////
#include <RL6952/BGA_900/RL6952_QA_A_BGA2L_LVDS_2H1TC1DP_TCMST_LVDS_PINSHARE.h>


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                    {\
                                                        PCB_D0_TYPE_C_ADC_SWITCH(_D0_TYPE_C_ADC_SWITCH_ON);\
                                                        PCB_D1_TYPE_C_ADC_SWITCH(_D1_TYPE_C_ADC_SWITCH_ON);\
                                                        PCB_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF);\
                                                        PCB_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH(_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF);\
                                                    }

#define PCB_GPIO_SETTING_POWER_NORMAL()             {\
                                                    }

#define PCB_GPIO_SETTING_POWER_SAVING()             {\
                                                    }

#define PCB_GPIO_SETTING_POWER_DOWN()               {\
                                                    }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#define SET_VCCKOFFPOWER(x)                         {SET_GPIO_2L_900PIN_PIN_G7(x);}

#define _VCCK_OFF_POWER_ON                          1
#define _VCCK_OFF_POWER_OFF                         0

#define PCB_VCCK_OFF_POWER(x)                       {\
                                                        SET_VCCKOFFPOWER(x);\
                                                    }

//-----------------------------------------------
// Macro of DDR Poewr Control
//-----------------------------------------------
#define SET_DDRPOWER(x)                             {SET_GPIO_2L_900PIN_PIN_F6(x);}

#define _DDR_POWER_ON                               1
#define _DDR_POWER_OFF                              0

#define PCB_DDR_POWER(x)                            {\
                                                        SET_DDRPOWER(x);\
                                                    }

//-----------------------------------------------
// Macro of USB_LV Power Control
//-----------------------------------------------
#define SET_USBLVPOWER(x)                           {SET_GPIO_2L_900PIN_PIN_G5(x);}

#define _USB_LV_POWER_ON                            1
#define _USB_LV_POWER_OFF                           0

#define PCB_USB_LV_POWER(x)                         {\
                                                        SET_USBLVPOWER(x);\
                                                    }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define GET_PANELPOWER()                            (GET_GPIO_2L_900PIN_PIN_B5())
#define SET_PANELPOWER(x)                           {SET_GPIO_2L_900PIN_PIN_B5(x);}

#define _PANEL_CONTROL_ON                           0
#define _PANEL_CONTROL_OFF                          1

#define PCB_PANEL_POWER(x)                          {\
                                                        SET_PANELPOWER(x);\
                                                    }

#define PCB_PANEL_POWER_DETECT()                    (GET_PANELPOWER())

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define SET_BACKLIGHTPOWER(x)                       {SET_GPIO_2L_900PIN_PIN_F7(x);}

#define _LIGHT_CONTROL_ON                           0
#define _LIGHT_CONTROL_OFF                          1

#define PCB_BACKLIGHT_POWER_PIN(x)                  {\
                                                        SET_BACKLIGHTPOWER(x);\
                                                    }

#define PCB_BACKLIGHT_POWER_PIN_EXINT(x)            {PCB_BACKLIGHT_POWER_PIN(x)}

#define PCB_BACKLIGHT_POWER(x)                      {\
                                                        if((x) == _LIGHT_CONTROL_ON)\
                                                        {\
                                                            ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                            ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, (((DWORD)_PANEL_TYP_FRAME_RATE * 60) / 100));\
                                                        }\
                                                        else\
                                                        {\
                                                            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        }\
                                                        PCB_BACKLIGHT_POWER_PIN(x)\
                                                    }


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define SET_FLASH_WRITE_PROTECT(x)                  {SET_GPIO_2L_900PIN_PIN_AF16(x);}

#define _FLASH_WRITE_PROTECT_ENABLE                 0
#define _FLASH_WRITE_PROTECT_DISABLE                1

#define PCB_FLASH_WRITE_PROTECT(x)                  {\
                                                        SET_FLASH_WRITE_PROTECT(x);\
                                                    }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define GET_EEPROM_WRITE_PROTECT()                  (GET_GPIO_2L_900PIN_PIN_AF17())
#define SET_EEPROM_WRITE_PROTECT(x)                 {SET_GPIO_2L_900PIN_PIN_AF17(x);}

#define _EEPROM_WP_ENABLE                           1
#define _EEPROM_WP_DISABLE                          0

#define PCB_EEPROM_WRITE_PROTECT(x)                 {\
                                                        SET_EEPROM_WRITE_PROTECT(x);\
                                                    }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()           (GET_EEPROM_WRITE_PROTECT())

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define SET_EDID_WRITE_PROTECT(x)                   {SET_GPIO_2L_900PIN_PIN_G6(x);}

#define _EDID_EEPROM_WP_ENABLE                      1
#define _EDID_EEPROM_WP_DISABLE                     0

#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)         {\
                                                        SET_EDID_WRITE_PROTECT(x);\
                                                    }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)         {\
                                                        SET_EDID_WRITE_PROTECT(x);\
                                                    }

#define PCB_D4_EDID_EEPROM_WRITE_PROTECT(x)         {\
                                                        SET_EDID_WRITE_PROTECT(x);\
                                                    }

//-----------------------------------------------
// Macro of HDMI External EDID Switch : #if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//-----------------------------------------------
#define SET_D3_EXT_SWITCH_EDID_0(x)                 {SET_GPIO_2L_900PIN_PIN_F9(x);}
#define SET_D4_EXT_SWITCH_EDID_0(x)                 {SET_GPIO_2L_900PIN_PIN_E8(x);}

#define _EEPROM_EDID_ENABLE                         1
#define _EEPROM_EDID_DISABLE                        0

#define PCB_MULTI_EDID_ALL_SWITCH_OFF(port)         {\
                                                        switch((port))\
                                                        {\
                                                            case _D3_INPUT_PORT:\
                                                                    SET_D3_EXT_SWITCH_EDID_0(_EEPROM_EDID_DISABLE);\
                                                                break;\
                                                            case _D4_INPUT_PORT:\
                                                                    SET_D4_EXT_SWITCH_EDID_0(_EEPROM_EDID_DISABLE);\
                                                                break;\
                                                            default:\
                                                                break;\
                                                        }\
                                                    }

#define PCB_MULTI_EDID_SWITCH(port, index)\
                                                    {\
                                                        switch((port))\
                                                        {\
                                                            case _D3_INPUT_PORT:\
                                                                if((index) == _EDID_INDEX_0)\
                                                                {\
                                                                    SET_D3_EXT_SWITCH_EDID_0(_EEPROM_EDID_ENABLE);\
                                                                }\
                                                                else\
                                                                {\
                                                                    SET_D3_EXT_SWITCH_EDID_0(_EEPROM_EDID_DISABLE);\
                                                                }\
                                                                break;\
                                                            case _D4_INPUT_PORT:\
                                                                if((index) == _EDID_INDEX_0)\
                                                                {\
                                                                    SET_D4_EXT_SWITCH_EDID_0(_EEPROM_EDID_ENABLE);\
                                                                }\
                                                                else\
                                                                {\
                                                                    SET_D4_EXT_SWITCH_EDID_0(_EEPROM_EDID_DISABLE);\
                                                                }\
                                                                break;\
                                                            default:\
                                                                break;\
                                                        }\
                                                    }

#define PCB_MULTI_EDID_SWITCH_POWER_AC_ON()         {\
                                                        SET_D3_EXT_SWITCH_EDID_0(_EEPROM_EDID_ENABLE);\
                                                        SET_D4_EXT_SWITCH_EDID_0(_EEPROM_EDID_ENABLE);\
                                                    }


#define _HDMI_MULTI_EDID_TABLE                      "./RL6952/HDMI_MultiEdid/RL6952_QA_A_MultiEdid.h"


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define GET_D0_DP_PIN15_CONNECT()                   (GET_GPIO_2L_900PIN_PIN_C2())
#define GET_D0_DP_PIN17_CONNECT()                   (GET_GPIO_2L_900PIN_PIN_C1())
#define GET_D0_CONNECT()                            (GET_GPIO_2L_900PIN_PIN_D3())

#define GET_D1_DP_PIN15_CONNECT()                   (GET_GPIO_PIN_EMPTY())
#define GET_D1_DP_PIN17_CONNECT()                   (GET_GPIO_PIN_EMPTY())
#define GET_D1_CONNECT()                            (GET_GPIO_PIN_EMPTY())

#define GET_D2_DP_PIN15_CONNECT()                   (GET_GPIO_2L_900PIN_PIN_H5())
#define GET_D2_DP_PIN16_CONNECT()                   (GET_GPIO_2L_900PIN_PIN_H4())
#define GET_D2_DP_PIN17_CONNECT()                   (GET_GPIO_2L_900PIN_PIN_J4())
#define GET_D2_CONNECT()                            (((bit)GET_D2_DP_PIN15_CONNECT() == _TRUE) && ((bit)GET_D2_DP_PIN16_CONNECT() == _TRUE) && ((bit)GET_D2_DP_PIN17_CONNECT() == _FALSE))

#define GET_D3_CONNECT()                            (GET_GPIO_2L_900PIN_PIN_K11())
#define GET_D4_CONNECT()                            (GET_GPIO_2L_900PIN_PIN_H10())

#define PCB_D0_PIN()                                (GET_D0_CONNECT())
#define PCB_D1_PIN()                                (GET_D1_CONNECT())
#define PCB_D2_PIN()                                (GET_D2_CONNECT())
#define PCB_D3_PIN()                                (GET_D3_CONNECT())
#define PCB_D4_PIN()                                (GET_D4_CONNECT())

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()                (GET_D0_DP_PIN17_CONNECT())
#define GET_PCB_D1_DP_SOURCE_POWER()                (GET_GPIO_PIN_EMPTY())
#define GET_PCB_D2_DP_SOURCE_POWER()                (GET_D2_DP_PIN17_CONNECT())


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define GET_D2_HPD()                                (GET_GPIO_2L_900PIN_PIN_J5())
#define SET_D2_HPD(x)                               {SET_GPIO_2L_900PIN_PIN_J5(x);}
#define GET_D3_HPD()                                (GET_GPIO_2L_900PIN_PIN_H11())
#define SET_D3_HPD(x)                               {SET_GPIO_2L_900PIN_PIN_H11(x);}
#define GET_D4_HPD()                                (GET_GPIO_2L_900PIN_PIN_J11())
#define SET_D4_HPD(x)                               {SET_GPIO_2L_900PIN_PIN_J11(x);}

#define _D2_HOT_PLUG_HIGH                           1
#define _D2_HOT_PLUG_LOW                            0

#define _D3_HOT_PLUG_HIGH                           1
#define _D3_HOT_PLUG_LOW                            0

#define _D4_HOT_PLUG_HIGH                           1
#define _D4_HOT_PLUG_LOW                            0

#define PCB_D2_HOTPLUG(x)                           {\
                                                        SET_D2_HPD(x);\
                                                    }

#define PCB_D3_HOTPLUG(x)                           {\
                                                        SET_D3_HPD(x);\
                                                    }

#define PCB_D4_HOTPLUG(x)                           {\
                                                        SET_D4_HPD(x);\
                                                    }

#define PCB_D2_HOTPLUG_DETECT()                     (GET_D2_HPD())
#define PCB_D3_HOTPLUG_DETECT()                     (GET_D3_HPD())
#define PCB_D4_HOTPLUG_DETECT()                     (GET_D4_HPD())


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#define PCB_PWM_SETTING()                           {\
                                                        UserCommonMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 240);\
                                                    }

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)

#define PCB_BACKLIGHT_PWM(x)                        {\
                                                        MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                    }

#define PCB_GET_BACKLIGHT_PWM()                     (MCU_GET_8BIT_PWM_DUTY(_BACKLIGHT_PWM))

#elif(_PWM_DUT_RESOLUTION == _PWM_12BIT)

#define PCB_BACKLIGHT_PWM(x)                        {\
                                                        MCU_ADJUST_12BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                    }

#define PCB_GET_BACKLIGHT_PWM()                     (MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))

#endif


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#define SET_LED1(x)                                 {SET_GPIO_2L_900PIN_PIN_AK18(x);}
#define SET_LED2(x)                                 {SET_GPIO_2L_900PIN_PIN_AK17(x);}
#define SET_LED3_1(x)                               {SET_GPIO_2L_900PIN_PIN_C4(x);}
#define SET_LED4_1(x)                               {SET_GPIO_2L_900PIN_PIN_AA25(x);}

#define _LED_ON                                     1
#define _LED_OFF                                    0

#define PCB_LED_AC_ON_INITIAL()                     {\
                                                        SET_LED1(_LED_OFF);\
                                                        SET_LED2(_LED_OFF);\
                                                        SET_LED3_1(_LED_OFF);\
                                                        SET_LED4_1(_LED_OFF);\
                                                    }

#define PCB_LED_ACTIVE()                            {\
                                                        SET_LED1(_LED_ON);\
                                                        SET_LED2(_LED_OFF);\
                                                        SET_LED3_1(_LED_ON);\
                                                        SET_LED4_1(_LED_OFF);\
                                                    }

#define PCB_LED_IDLE()                              {\
                                                        SET_LED1(_LED_OFF);\
                                                        SET_LED2(_LED_ON);\
                                                        SET_LED3_1(_LED_OFF);\
                                                        SET_LED4_1(_LED_ON);\
                                                    }

#define PCB_LED_POWER_SAVING()                      {\
                                                        SET_LED1(_LED_OFF);\
                                                        SET_LED2(_LED_ON);\
                                                        SET_LED3_1(_LED_OFF);\
                                                        SET_LED4_1(_LED_OFF);\
                                                    }

#define PCB_LED_ON()                                {\
                                                        SET_LED1(_LED_ON);\
                                                        SET_LED2(_LED_ON);\
                                                        SET_LED3_1(_LED_ON);\
                                                        SET_LED4_1(_LED_ON);\
                                                    }

#define PCB_LED_OFF()                               {\
                                                        SET_LED1(_LED_OFF);\
                                                        SET_LED2(_LED_OFF);\
                                                        SET_LED3_1(_LED_OFF);\
                                                        SET_LED4_1(_LED_OFF);\
                                                    }

#define PCB_LED_TYPE1()                             {\
                                                        SET_LED1(_LED_ON);\
                                                        SET_LED2(_LED_OFF);\
                                                        SET_LED3_1(_LED_OFF);\
                                                        SET_LED4_1(_LED_OFF);\
                                                    }

#define PCB_LED_TYPE_FLASH()                        {\
                                                    }


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define AD_KEY1                                     (GET_SARADC_1_2_VALUE())
#define AD_KEY2                                     (GET_SARADC_1_3_VALUE())

#define PCB_ADKEY1()                                (AD_KEY1)
#define PCB_ADKEY2()                                (AD_KEY2)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)       {\
                                                        if((ucV2) < 0x20)\
                                                        {\
                                                            (ucKeyState) |= _LEFT_KEY_MASK;\
                                                        }\
                                                        if((0x40 <= (ucV2)) && ((ucV2) < 0x80))\
                                                        {\
                                                            (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                        }\
                                                        if((0x90 <= (ucV2)) && ((ucV2) < 0xE0))\
                                                        {\
                                                            (ucKeyState) |= _EXIT_KEY_MASK;\
                                                        }\
                                                        if((ucV1) < 0x20)\
                                                        {\
                                                            (ucKeyState) |= _POWER_KEY_MASK;\
                                                        }\
                                                        if((0x40 <= (ucV1)) && ((ucV1) < 0x80))\
                                                        {\
                                                            (ucKeyState) |= _MENU_KEY_MASK;\
                                                        }\
                                                        if((0x90 <= (ucV1)) && ((ucV1) < 0xE0))\
                                                        {\
                                                            (ucKeyState) |= _EXIT_KEY_MASK;\
                                                        }\
                                                    }


//////////////////////
// PMIC Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of PMIC Power Control
//-----------------------------------------------
#define SET_D0_PMIC_POWER(x)                        {SET_GPIO_2L_900PIN_PIN_F5(x);}
#define SET_D1_PMIC_POWER(x)                        {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PMIC_POWER_ON                           1
#define _D0_PMIC_POWER_OFF                          0

#define _D1_PMIC_POWER_ON                           1
#define _D1_PMIC_POWER_OFF                          0

#define PCB_D0_PMIC_POWER(x)                        {\
                                                         SET_D0_PMIC_POWER(x);\
                                                    }

#define PCB_D1_PMIC_POWER(x)                        {\
                                                         SET_D1_PMIC_POWER(x);\
                                                    }

//-----------------------------------------------
// Macro of PMIC VBUS SINK Control
//-----------------------------------------------
#define SET_D0_PMIC_VBUS_SINK_CONTROL(x)            {SET_GPIO_2L_900PIN_PIN_V5(x);}
#define SET_D1_PMIC_VBUS_SINK_CONTROL(x)            {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PMIC_VBUS_SINK_SWITCH_ON                1
#define _D0_PMIC_VBUS_SINK_SWITCH_OFF               0
#define _D1_PMIC_VBUS_SINK_SWITCH_ON                1
#define _D1_PMIC_VBUS_SINK_SWITCH_OFF               0

#define PCB_D0_PMIC_VBUS_SINK_CONTROL(x)            {\
                                                        SET_D0_PMIC_VBUS_SINK_CONTROL(x);\
                                                    }
#define PCB_D1_PMIC_VBUS_SINK_CONTROL(x)            {\
                                                        SET_D1_PMIC_VBUS_SINK_CONTROL(x);\
                                                    }

//-----------------------------------------------
// Macro of PMIC Interrupt Detect
//-----------------------------------------------
#define GET_D0_PMIC_INTERRUPT()                     (GET_GPIO_2L_900PIN_PIN_E4())
#define GET_D1_PMIC_INTERRUPT()                     (GET_GPIO_PIN_EMPTY())

#define _D0_PMIC_INTERRUPT_ON                       0
#define _D0_PMIC_INTERRUPT_OFF                      1

#define _D1_PMIC_INTERRUPT_ON                       0
#define _D1_PMIC_INTERRUPT_OFF                      1

#define PCB_D0_PMIC_INTERRUPT_DETECT()              (GET_D0_PMIC_INTERRUPT())
#define PCB_D1_PMIC_INTERRUPT_DETECT()              (GET_D1_PMIC_INTERRUPT())


/////////////////////////////
// Type-C ADC Switch Macro //
/////////////////////////////

//-----------------------------------------------
// Macro of Type-C ADC Switch Control
//-----------------------------------------------
#define SET_D0_TYPE_C_ADC_SWITCH(x)                 {SET_GPIO_2L_900PIN_PIN_F4(x);}
#define SET_D1_TYPE_C_ADC_SWITCH(x)                 {SET_GPIO_PIN_EMPTY(x);}

#define _D0_TYPE_C_ADC_SWITCH_ON                    0
#define _D0_TYPE_C_ADC_SWITCH_OFF                   1

#define _D1_TYPE_C_ADC_SWITCH_ON                    0
#define _D1_TYPE_C_ADC_SWITCH_OFF                   1

#define PCB_D0_TYPE_C_ADC_SWITCH(x)                 {\
                                                        SET_D0_TYPE_C_ADC_SWITCH(x);\
                                                    }

#define PCB_D1_TYPE_C_ADC_SWITCH(x)                 {\
                                                        SET_D1_TYPE_C_ADC_SWITCH(x);\
                                                    }

//-----------------------------------------------
// Macro of Type-C ADC High VBUS Detect Control
//-----------------------------------------------
#define SET_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)    {SET_GPIO_2L_900PIN_PIN_E7(x);}
#define SET_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)    {SET_GPIO_PIN_EMPTY(x);}

#define _D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON       1
#define _D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF      0

#define _D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON       1
#define _D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF      0

#define PCB_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)    {\
                                                        SET_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x);\
                                                    }

#define PCB_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)    {\
                                                        SET_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x);\
                                                    }

#endif // End of #if(_PCB_TYPE == _RL6952_QA_A_BGA2L_LVDS_2H1TC1DP_TCMST_LVDS)
