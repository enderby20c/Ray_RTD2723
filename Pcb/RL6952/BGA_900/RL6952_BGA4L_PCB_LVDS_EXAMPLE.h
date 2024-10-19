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
// ID Code      : RL6952_BGA4L_PCB_LVDS_EXAMPLE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6952_BGA4L_PCB_LVDS_EXAMPLE)


//////////////////////
// Series Pin Share //
//////////////////////
#include <RL6952/BGA_900/RL6952_BGA4L_PCB_LVDS_EXAMPLE_PINSHARE.h>


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#define _EXT_XTAL                                       _XTAL14318K


///////////////
// Debug DDC //
///////////////

//--------------------------------------------------
// Debug DDC Channel
//--------------------------------------------------
#define _PCB_DEBUG_DDC                                  _VGA_DDC

//--------------------------------------------------
// Debug JTAG Channel
//--------------------------------------------------
#define _PCB_DEBUG_JTAG                                 _JTAG_SWD_DDC4


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                             _D0_NO_PORT
#define _D0_DDC_CHANNEL_SEL                             _NO_DDC
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#define _D0_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#define _D0_USB_UFP_RX_OOBS_VTH                         _USB_UFP_RX_OOBS_VTH_LEVEL_3

// For DP
#define _D0_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _D0_DP_LINK_CLK_RATE                            _DP_LINK_SPEED_NONE
#define _D0_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE

// For DP Redriver
#define _D0_DP_REDRIVER_TYPE                            _REDRIVER_NONE

// For USB Port
#define _D0_USB_CONNECTOR_TYPE                          _USB_CONNECTOR_NONE

// For USB Hub
#define _D0_USB_HUB_TYPE                                _USB_HUB_RTS
#define _D0_USB_U2_HUB_TRACE_TYPE                       _USB_U2_TRACE_GO_THROUGH_SCALER
#define _D0_USB_U3_HUB_TRACE_TYPE                       _USB_U3_TRACE_GO_THROUGH_SCALER
#define _D0_USB_SPEED                                   _USB_3_GEN2
#define _D0_USB_LANE                                    _USB_3_LANE_X1
#define _D0_USB_HUB_RTS_SLAVE_ADDR                      0x00
#define _D0_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN

// For Type-C Connector
#define _D0_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_EMBEDDED
#define _D0_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_SCALER

// For RTS Port Controller
#define _D0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0xAC

// For RTS / User Port Controller
#define _D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_PORT_CTRL
#define _D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#define _D0_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#define _D0_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#define _D0_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF

// For Embedded Port Controller
#define _D0_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#define _D0_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#define _D0_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#define _D0_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_DEVICE_ONLY
#define _D0_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#define _D0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#define _D0_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#define _D0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#define _D0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#define _D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#define _D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _ON

// For Type-C Embedded Port Controller PMIC
#define _D0_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#define _D0_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#define _D0_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#define _D0_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _D0_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _D0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#define _D0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#define _D0_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#define _D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#define _D0_TYPE_C_PMIC_FW_OVP_THRESHOLD                130 // Unit: %
#define _D0_TYPE_C_PMIC_FW_UVP_THRESHOLD                66 // Unit: %
#define _D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#define _D0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            0 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _D0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#define _D0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#define _D0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#define _D0_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#define _D0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                             _D1_NO_PORT
#define _D1_DDC_CHANNEL_SEL                             _NO_DDC
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#define _D1_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#define _D1_USB_UFP_RX_OOBS_VTH                         _USB_UFP_RX_OOBS_VTH_LEVEL_3

// For DP
#define _D1_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _D1_DP_LINK_CLK_RATE                            _DP_LINK_SPEED_NONE
#define _D1_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE

// For DP Redriver
#define _D1_DP_REDRIVER_TYPE                            _REDRIVER_NONE

// For USB Port
#define _D1_USB_CONNECTOR_TYPE                          _USB_CONNECTOR_NONE

// For USB Hub
#define _D1_USB_HUB_TYPE                                _USB_HUB_RTS
#define _D1_USB_U2_HUB_TRACE_TYPE                       _USB_U2_TRACE_GO_THROUGH_SCALER
#define _D1_USB_U3_HUB_TRACE_TYPE                       _USB_U3_TRACE_GO_THROUGH_SCALER
#define _D1_USB_SPEED                                   _USB_3_GEN2
#define _D1_USB_LANE                                    _USB_3_LANE_X1
#define _D1_USB_HUB_RTS_SLAVE_ADDR                      0x00
#define _D1_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN

// For Type-C Connector
#define _D1_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_EMBEDDED
#define _D1_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_SCALER

// For RTS Port Controller
#define _D1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0xAC

// For RTS / User Port Controller
#define _D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_PORT_CTRL
#define _D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#define _D1_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#define _D1_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#define _D1_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF

// For Embedded Port Controller
#define _D1_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#define _D1_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#define _D1_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#define _D1_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_DEVICE_ONLY
#define _D1_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#define _D1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#define _D1_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#define _D1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#define _D1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#define _D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#define _D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _ON

// For Type-C Embedded Port Controller PMIC
#define _D1_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#define _D1_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#define _D1_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#define _D1_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _D1_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _D1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#define _D1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#define _D1_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#define _D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#define _D1_TYPE_C_PMIC_FW_OVP_THRESHOLD                130 // Unit: %
#define _D1_TYPE_C_PMIC_FW_UVP_THRESHOLD                66 // Unit: %
#define _D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#define _D1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            0 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _D1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#define _D1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#define _D1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#define _D1_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#define _D1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms

//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#define _D2_INPUT_PORT_TYPE                             _D2_NO_PORT
#define _D2_DDC_CHANNEL_SEL                             _NO_DDC
#define _D2_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#define _D2_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE

// For DP
#define _D2_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _D2_DP_LINK_CLK_RATE                            _DP_LINK_SPEED_NONE
#define _D2_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE

// For HDMI MultiEdid
#define _D2_HDMI_CEC_PIN                                _HDMI_CEC_NONE
#define _D2_HDMI_CEC_EDID_PHYSICAL_ADDR                 0x0000

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                             _D3_NO_PORT
#define _D3_DDC_CHANNEL_SEL                             _NO_DDC
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#define _D3_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#define _D3_EDID_EXTERNAL_EEPROM_MAX_SIZE               _EDID_EEPROM_SIZE_256

// For HDMI MultiEdid
#define _D3_MAX_HDMI_EDID_COUNT                         1
#define _D3_HDMI_CEC_PIN                                _HDMI_CEC_NONE
#define _D3_HDMI_CEC_EDID_PHYSICAL_ADDR                 0x0000

// For HDMI
#define _D3_HDMI_MAC_TYPE                               _HDMI_MAC_TMDS_FRL
#define _D3_HDMI_LINK_CLK_RATE                          _HDMI_LINK_SPEED_600MHZ
#define _D3_HDMI_MAIN_LINK_LANES                        _HDMI_FOUR_LANE

//--------------------------------------------------
// D4 Input Port
//--------------------------------------------------
#define _D4_INPUT_PORT_TYPE                             _D4_NO_PORT
#define _D4_DDC_CHANNEL_SEL                             _NO_DDC
#define _D4_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#define _D4_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#define _D4_EDID_EXTERNAL_EEPROM_MAX_SIZE               _EDID_EEPROM_SIZE_256

// For HDMI MultiEdid
#define _D4_MAX_HDMI_EDID_COUNT                         1
#define _D4_HDMI_CEC_PIN                                _HDMI_CEC_NONE
#define _D4_HDMI_CEC_EDID_PHYSICAL_ADDR                 0x0000

// For HDMI
#define _D4_HDMI_MAC_TYPE                               _HDMI_MAC_TMDS_FRL
#define _D4_HDMI_LINK_CLK_RATE                          _HDMI_LINK_SPEED_600MHZ
#define _D4_HDMI_MAIN_LINK_LANES                        _HDMI_FOUR_LANE

//--------------------------------------------------
// D9 Input Port
//--------------------------------------------------
#define _D9_INPUT_PORT_TYPE                             _D9_NO_PORT
#define _D9_EMBEDDED_XRAM_MAX_SIZE                      _EDID_SIZE_NONE
#define _D9_EMBEDDED_XRAM_LOCATION                      _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// HDMI SRC 5V Detect By User
//--------------------------------------------------
#define _HDMI_5V_DETECT_BY_USER                         _OFF

//--------------------------------------------------
// D12 Input Port
//--------------------------------------------------
#define _D12_INPUT_PORT_TYPE                            _D12_NO_PORT

#define _D12_INPUT_PORT_SWITCH_FROM                     _SWITCH_NONE

//--------------------------------------------------
// D13 Input Port
//--------------------------------------------------
#define _D13_INPUT_PORT_TYPE                            _D13_NO_PORT

#define _D13_INPUT_PORT_SWITCH_FROM                     _SWITCH_NONE

//--------------------------------------------------
// D14 Input Port
//--------------------------------------------------
#define _D14_INPUT_PORT_TYPE                            _D14_NO_PORT

#define _D14_INPUT_PORT_SWITCH_FROM                     _SWITCH_NONE

//--------------------------------------------------
// D15 Input Port
//--------------------------------------------------
#define _D15_INPUT_PORT_TYPE                            _D15_NO_PORT

#define _D15_INPUT_PORT_SWITCH_FROM                     _SWITCH_NONE


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _D0_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#define _D1_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#define _D2_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#define _D3_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#define _D4_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#define _D7_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#define _D12_INPUT_PORT_GROUP                           _INPUT_PORT_GROUP_NONE
#define _D13_INPUT_PORT_GROUP                           _INPUT_PORT_GROUP_NONE
#define _D14_INPUT_PORT_GROUP                           _INPUT_PORT_GROUP_NONE
#define _D15_INPUT_PORT_GROUP                           _INPUT_PORT_GROUP_NONE

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                        _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                        _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                        _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                        _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_4                        _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_5                        _NO_INPUT_PORT


/////////////////////////
// U2HOST Port Support //
/////////////////////////

//--------------------------------------------------
// U2Host Port
//--------------------------------------------------
#define _USB2_HOST_PORT_SUPPORT                         _OFF
#define _USB2_HOST_PORT_HSTX_SWING                      _USB2_HOST_HS_SWING_LEVEL_3


/////////////////////////
// Repeater DFP Config //
/////////////////////////

//--------------------------------------------------
// Repeater DownStream Port Orientation
//--------------------------------------------------
#define _RETIMER_DFP_ORIENTATION                        _TYPE_C_DFP_ORIENTATION_NONE


///////////////
// TMDS Port //
///////////////

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#define _D1_TMDS_BR_SWAP                                _OFF
#define _D1_TMDS_PN_SWAP                                _OFF

#define _D3_TMDS_PCB_LANE0_MAPPING                      _TMDS_SCALER_LANE0
#define _D3_TMDS_PCB_LANE1_MAPPING                      _TMDS_SCALER_LANE1
#define _D3_TMDS_PCB_LANE2_MAPPING                      _TMDS_SCALER_LANE2
#define _D3_TMDS_PCB_LANE3_MAPPING                      _TMDS_SCALER_LANE3

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#define _D3_TMDS_BR_SWAP                                _OFF
#define _D3_TMDS_PN_SWAP                                _ON
#else
#define _D3_TMDS_BR_SWAP                                _OFF
#define _D3_TMDS_PN_SWAP                                _OFF
#endif

#define _D4_TMDS_PCB_LANE0_MAPPING                      _TMDS_SCALER_LANE0
#define _D4_TMDS_PCB_LANE1_MAPPING                      _TMDS_SCALER_LANE1
#define _D4_TMDS_PCB_LANE2_MAPPING                      _TMDS_SCALER_LANE2
#define _D4_TMDS_PCB_LANE3_MAPPING                      _TMDS_SCALER_LANE3

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#define _D4_TMDS_BR_SWAP                                _OFF
#define _D4_TMDS_PN_SWAP                                _ON
#else
#define _D4_TMDS_BR_SWAP                                _OFF
#define _D4_TMDS_PN_SWAP                                _OFF
#endif


/////////////
// DP Port //
/////////////

//--------------------------------------------------
// DP Lane & PN Swap Option
//--------------------------------------------------
#define _D0_DP_PCB_LANE0_MAPPING                        _DP_SCALER_LANE0
#define _D0_DP_PCB_LANE1_MAPPING                        _DP_SCALER_LANE1
#define _D0_DP_PCB_LANE2_MAPPING                        _DP_SCALER_LANE2
#define _D0_DP_PCB_LANE3_MAPPING                        _DP_SCALER_LANE3
#define _D0_DP_PCB_LANE0_PN_SWAP                        _OFF
#define _D0_DP_PCB_LANE1_PN_SWAP                        _OFF
#define _D0_DP_PCB_LANE2_PN_SWAP                        _OFF
#define _D0_DP_PCB_LANE3_PN_SWAP                        _OFF

#define _D1_DP_PCB_LANE0_MAPPING                        _DP_SCALER_LANE0
#define _D1_DP_PCB_LANE1_MAPPING                        _DP_SCALER_LANE1
#define _D1_DP_PCB_LANE2_MAPPING                        _DP_SCALER_LANE2
#define _D1_DP_PCB_LANE3_MAPPING                        _DP_SCALER_LANE3
#define _D1_DP_PCB_LANE0_PN_SWAP                        _OFF
#define _D1_DP_PCB_LANE1_PN_SWAP                        _OFF
#define _D1_DP_PCB_LANE2_PN_SWAP                        _OFF
#define _D1_DP_PCB_LANE3_PN_SWAP                        _OFF

#define _D2_DP_PCB_LANE0_MAPPING                        _DP_SCALER_LANE0
#define _D2_DP_PCB_LANE1_MAPPING                        _DP_SCALER_LANE1
#define _D2_DP_PCB_LANE2_MAPPING                        _DP_SCALER_LANE2
#define _D2_DP_PCB_LANE3_MAPPING                        _DP_SCALER_LANE3
#define _D2_DP_PCB_LANE0_PN_SWAP                        _OFF
#define _D2_DP_PCB_LANE1_PN_SWAP                        _OFF
#define _D2_DP_PCB_LANE2_PN_SWAP                        _OFF
#define _D2_DP_PCB_LANE3_PN_SWAP                        _OFF

//--------------------------------------------------
// DP Rx AUX Reply Swing Level
//--------------------------------------------------
#define _DP_RX_AUX_REPLY_SWING_LEVEL                    _DP_AUX_SWING_900_MV

//--------------------------------------------------
// DP Tx AUX Request Swing Level
//--------------------------------------------------
#define _DP_TX_AUX_REQUEST_SWING_LEVEL                  _DP_AUX_SWING_900_MV


////////////////////////
// Output Port Config //
////////////////////////

//--------------------------------------------------
// P0 Output Port
//--------------------------------------------------
#define _P0_OUTPUT_TYPE                                 _P0_NO_PORT

// For DP
#define _P0_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _P0_DP_LINK_CLK_RATE                            _DP_ULTRA_SPEED_1350MHZ
#define _P0_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE
#define _P0_DP_PCB_LOOP_DX_PORT                         _D0_DP_PORT

// For DP Connector Type-C
#define _P0_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE

// For RTS Port Controller / Hub
#define _P0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00
#define _P0_TYPE_C_RTS_HUB_SLAVE_ADDR                   0x00
#define _P0_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN

// For RTS / User Port Controller
#define _P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#define _P0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#define _P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#define _P0_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#define _P0_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#define _P0_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF

// For Embedded Port Controller
#define _P0_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#define _P0_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#define _P0_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#define _P0_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#define _P0_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#define _P0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#define _P0_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#define _P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _ON

// For Type-C Embedded Port Controller PMIC
#define _P0_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#define _P0_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#define _P0_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#define _P0_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P0_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#define _P0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#define _P0_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#define _P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#define _P0_TYPE_C_PMIC_FW_OVP_THRESHOLD                130
#define _P0_TYPE_C_PMIC_FW_UVP_THRESHOLD                66
#define _P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#define _P0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            0 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _P0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#define _P0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#define _P0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#define _P0_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#define _P0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms

//--------------------------------------------------
// P0 Output Port Lane Mapping
//--------------------------------------------------
// For Type-c Embeded Port Lane Mapping
#define _P0_DP_TYPE_C_PCB_LANE0_MAPPING                 _TYPE_C_TX2
#define _P0_DP_TYPE_C_PCB_LANE1_MAPPING                 _TYPE_C_RX2
#define _P0_DP_TYPE_C_PCB_LANE2_MAPPING                 _TYPE_C_TX1
#define _P0_DP_TYPE_C_PCB_LANE3_MAPPING                 _TYPE_C_RX1

// For Normal Dp Tx Port Lane Mapping
#define _P0_DP_PCB_LANE0_MAPPING                        _DP_LANE_0
#define _P0_DP_PCB_LANE1_MAPPING                        _DP_LANE_1
#define _P0_DP_PCB_LANE2_MAPPING                        _DP_LANE_2
#define _P0_DP_PCB_LANE3_MAPPING                        _DP_LANE_3

//--------------------------------------------------
// P0 Output Port Lane PN Swap
//--------------------------------------------------
#define _P0_DP_PCB_LANE0_PN_SWAP                        _OFF
#define _P0_DP_PCB_LANE1_PN_SWAP                        _OFF
#define _P0_DP_PCB_LANE2_PN_SWAP                        _OFF
#define _P0_DP_PCB_LANE3_PN_SWAP                        _OFF

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#define _D3_TMDS_BR_SWAP                                _OFF
#define _D3_TMDS_PN_SWAP                                _ON
#define _D4_TMDS_BR_SWAP                                _OFF
#define _D4_TMDS_PN_SWAP                                _ON


////////////////////
// Adaptor Config //
////////////////////

//--------------------------------------------------
// For Type-C Embedded Port Local Power Detect
//--------------------------------------------------
#define _ADAPTOR_TYPE_C_PMIC_VBUS_ADC_CHANNEL           _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2
#define _ADAPTOR_TYPE_C_PMIC_VBUS_MAX_VOLTAGE           2400 // unit: 10mV
#define _ADAPTOR_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO    12


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#define _LVDS_PORT_SEL                                  _LVDS_2_PORT_AB
#define _LVDS_PORT_MIRROR                               _DISABLE
#define _LVDS_PORT_AB_SWAP                              _DISABLE
#define _LVDS_PORT_CD_SWAP                              _DISABLE
#define _LVDS_PN_SWAP                                   _DISABLE
#define _LVDS_RB_SWAP                                   _DISABLE
#define _LVDS_ML_SWAP                                   _DISABLE
#define _LVDS_DVS_INVERT                                _DISABLE
#define _LVDS_DHS_INVERT                                _DISABLE
#define _LVDS_DEN_INVERT                                _DISABLE
#define _LVDS_PAIR_MIRROR                               _DISABLE

#define _LVDS_CLK_CHANNEL_SEL                           _NORMAL_MODE           /// Display CLK Pair Position Selection: TXK = A / B / C / D / E / F / G / H port
                                                                               /// Normal mode: TXKCK1 as CLK for 8bit / 10bit
                                                                               /// Mode1:       TXK1   as CLK for 8bit / 10bit
                                                                               /// Mode2:       TXK2   as CLK for 8bit / 10bit
                                                                               /// Mode3:       TXKCK1 as CLK for 8bit
                                                                               ///              TXK3   as CLK for        10bit

//--------------------------------------------------
// LVDS Port AB Phase Selection
//--------------------------------------------------
#define _LVDS_A0_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_A1_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_A2_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_AC_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_A3_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_A4_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_B0_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_B1_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_B2_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_BC_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_B3_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_B4_PHASE                                  _LVDS_PI_PHASE_AB0
#define _LVDS_PI_PHASE_AB0_SEL                          _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB1_SEL                          _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB2_SEL                          _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB3_SEL                          _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used

//--------------------------------------------------
// LVDS Port CD Phase Selection
//--------------------------------------------------
#define _LVDS_C0_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_C1_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_C2_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_CC_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_C3_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_C4_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_D0_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_D1_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_D2_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_DC_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_D3_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_D4_PHASE                                  _LVDS_PI_PHASE_CD0
#define _LVDS_PI_PHASE_CD0_SEL                          _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD1_SEL                          _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD2_SEL                          _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD3_SEL                          _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL                              _LVDS_DRIV_CONTROL_3_0
#define _LVDS_VCM_CONTROL                               _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                                _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL                      _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL                       _DISABLE
#define _LVDS_VCM_USER_LEVEL                            0x0C

//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
#define _LVDS_SPREAD_RANGE                              10                     // 0~15, 0 ~ disable, 15 ~ 7.50%
#define _LVDS_SPREAD_SPEED                              _SPEED_33K


/////////////////
// eDPTx Panel //
/////////////////

//--------------------------------------------------
// eDPTx Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_SWING_LEVEL                         _DP_SWING_800_MV       // Swing Level = 400,600,800,1200mV
#define _PANEL_DPTX_PREEMPHASIS_LEVEL                   _DP_PREEMPHASIS_3_5_DB // Preemphasis Level = 0,3.5,6,9.5dB

//--------------------------------------------------
// eDPTx SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_SPREAD_RANGE                        12                     // 0~15, 0 ~ disable, 0.5 ~ 0.03%
#define _PANEL_DPTX_SPREAD_SPEED                        _SPEED_33K             // _SPEED_30~33K

//--------------------------------------------------
// eDPTx FB/Lane Config
//--------------------------------------------------
#define _PANEL_DPTX_PORT_MIRROR                         _DISABLE               // Swap Tx0 Tx1 Tx2 Tx3
#define _PANEL_DPTX_PORT_0_LANE_SWAP                    _DISABLE               // DP Tx Port0 Lane Swap
#define _PANEL_DPTX_PORT_1_LANE_SWAP                    _DISABLE               // DP Tx Port1 Lane Swap
#define _PANEL_DPTX_PORT_2_LANE_SWAP                    _DISABLE               // DP Tx Port2 Lane Swap
#define _PANEL_DPTX_PORT_3_LANE_SWAP                    _DISABLE               // DP Tx Port3 Lane Swap
#define _PANEL_DPTX_PORT_0_LANE_PN_SWAP                 _DISABLE               // DP Tx Port0 Lane PN Swap
#define _PANEL_DPTX_PORT_1_LANE_PN_SWAP                 _DISABLE               // DP Tx Port1 Lane PN Swap
#define _PANEL_DPTX_PORT_2_LANE_PN_SWAP                 _DISABLE               // DP Tx Port2 Lane PN Swap
#define _PANEL_DPTX_PORT_3_LANE_PN_SWAP                 _DISABLE               // DP Tx Port3 Lane PN Swap

//--------------------------------------------------
// eDPTx AUX Swing Level
//--------------------------------------------------
#define _PANEL_DPTX_AUX_SWING_LEVEL                     _DP_AUX_SWING_1100_MV

//--------------------------------------------------
// eDPTx AUX PN SWAP ENABLE
//--------------------------------------------------
#define _PANEL_DPTX_AUX_PN_SWAP_ENABLE                  _DISABLE


//////////////////////////////////////
// eDPTx Panel Power Sequence Macro //
//////////////////////////////////////

//--------------------------------------------------
// eDPTx Panel Power Sequence Macro
//--------------------------------------------------
#define PCB_DPTX0_POWER_SEQUENCE(x)                     {\
                                                        }

#define PCB_DPTX1_POWER_SEQUENCE(x)                     {\
                                                        }

#define PCB_DPTX2_POWER_SEQUENCE(x)                     {\
                                                        }

#define PCB_DPTX3_POWER_SEQUENCE(x)                     {\
                                                        }

//--------------------------------------------------
// Definitions of eDP Panel Power Sequence
//
// Panel On Sequence
//       _________       ________      ________
//       |       |       |      |      |      |
// ______|       |_______|      |______|      |______
//
//   Panel_On  HPD_ON    LT    IDLE   VIDEO  BL_ON
//
// Panel Off Sequence
//
//       _________
//       |       |
// ______|       |_______
//
//    BL_OFF    IDLE
//--------------------------------------------------
#define _DPTX_POWER_SEQUENCE_PANEL_ON                   _HIGH
#define _DPTX_POWER_SEQUENCE_HPD_ON                     _LOW
#define _DPTX_POWER_SEQUENCE_LINK_TRAINING              _HIGH
#define _DPTX_POWER_SEQUENCE_IDLE_PATTERN               _LOW
#define _DPTX_POWER_SEQUENCE_VIDEO_PATTERN              _HIGH
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_ON               _LOW
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_OFF              _HIGH


////////////////////
// V by One Panel //
////////////////////

//--------------------------------------------------
// V by One Main Link Config
//--------------------------------------------------
#define _PANEL_VBO_LANE_SWAP                            _DISABLE               // Display Data Lane Swap
#define _PANEL_VBO_ML_SWAP                              _DISABLE               // Display Data Port MSB/LSB Data Swap
#define _PANEL_VBO_SECTION_0_PN_SWAP                    _DISABLE               // Display Data Section_0: Lane 0~15 PN Swap
#define _PANEL_VBO_LANE_DRIV_CONTROL                    _VBO_DRIV_CONTROL_3_0
#define _PANEL_VBO_PRE_EMPHASIS_CONTROL                 _VBO_PRE_EMPHASIS_0

//--------------------------------------------------
// V by One SSC Config
//--------------------------------------------------
#define _PANEL_VBO_SPREAD_RANGE                         15                     // 0~15, 0 ~ disable, 15 ~ 0.98%
#define _PANEL_VBO_SPREAD_SPEED                         _SPEED_30K


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                             _PWM_8BIT

#define _BACKLIGHT_PWM                                  _NO_PWM
#define _BACKLIGHT_PWM_INVERSE                          _OFF

#define _PWM0_EN                                        _OFF
#define _PWM1_EN                                        _OFF
#define _PWM2_EN                                        _OFF
#define _PWM3_EN                                        _OFF
#define _PWM4_EN                                        _OFF
#define _PWM5_EN                                        _OFF

#define _PWM0_PSAV_EN                                   _OFF
#define _PWM1_PSAV_EN                                   _OFF
#define _PWM2_PSAV_EN                                   _OFF
#define _PWM3_PSAV_EN                                   _OFF
#define _PWM4_PSAV_EN                                   _OFF
#define _PWM5_PSAV_EN                                   _OFF

#define _PWM0_PDOW_EN                                   _OFF
#define _PWM1_PDOW_EN                                   _OFF
#define _PWM2_PDOW_EN                                   _OFF
#define _PWM3_PDOW_EN                                   _OFF
#define _PWM4_PDOW_EN                                   _OFF
#define _PWM5_PDOW_EN                                   _OFF

#define _PWM0_BYPASS_MODE_EN                            _OFF
#define _PWM1_BYPASS_MODE_EN                            _OFF
#define _PWM2_BYPASS_MODE_EN                            _OFF
#define _PWM3_BYPASS_MODE_EN                            _OFF
#define _PWM4_BYPASS_MODE_EN                            _OFF
#define _PWM5_BYPASS_MODE_EN                            _OFF

#define _PWM0_RST_EN                                    _OFF
#define _PWM1_RST_EN                                    _OFF
#define _PWM2_RST_EN                                    _OFF
#define _PWM3_RST_EN                                    _OFF
#define _PWM4_RST_EN                                    _OFF
#define _PWM5_RST_EN                                    _OFF
#define _PWM_RST_SIGNAL_SEL                             _DVS
#define _PWM_FREQ_DVSRST_CHECK                          _OFF


//--------------------------------------------------
// Definitions of External PWM Setting for LED Driver
//--------------------------------------------------
#define _DEVICE_LED_DRIVER_EXTERNAL_PWM                 _NO_PWM


//////////
// TCON //
//////////

//--------------------------------------------------
// MBR TCON Pin Setting
//--------------------------------------------------
#define _PCB_MBR_TCON_PIN                               _TCON_NONE

//--------------------------------------------------
// MBR Driver IC Max Frequency (unit: kHz)
//--------------------------------------------------
#define _PCB_MBR_DRIVER_IC_MAX_FREQ                     20


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                                 _OFF
#define _SW_IIC_CLK_DIV                                 _DIV_1
#define _SW_IIC_HOLD_TIME_LIMIT_SUPPORT                 _OFF

#define _HW_IIC_SUPPORT                                 _OFF
#define _HW_IIC_SPEED                                   _HW_IIC_LOW_SPEED_100K
#define _HW_IIC_PAR_BY_USER_SUPPORT                     _OFF

#define _TYPEC_IIC_SUPPORT                              _OFF
#define _TYPEC_IIC_SPEED                                _HW_IIC_LOW_SPEED_100K

//--------------------------------------------------
// IIC 1 Slave Support Option
//--------------------------------------------------
#define _HW_IIC_1_SLAVE_SUPPORT_OPTION                  _IIC_SLAVE_DEFAULT_OFF

//--------------------------------------------------
// IIC 1 Slave Address Config
//--------------------------------------------------
#define _HW_IIC_1_SLAVE_ADDRESS_CONFIG_00               0xB6
#define _HW_IIC_1_SLAVE_ADDRESS_CONFIG_01               0xB8
#define _HW_IIC_1_SLAVE_ADDRESS_CONFIG_10               0xBA
#define _HW_IIC_1_SLAVE_ADDRESS_CONFIG_11               0xBC


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                                    _EEPROM_24LC16
#define _EEPROM_SLAVE_ADDRESS                           0xA0
#define _PCB_SYS_EEPROM_IIC                             _NO_IIC_PIN


////////////////////////////
// Second External Eeprom //
////////////////////////////

//--------------------------------------------------
// Second External Eeprom Data Storage Option
//--------------------------------------------------
#define _SEC_EEPROM_TYPE                                _EEPROM_CAT24M01
#define _SEC_EEPROM_SLAVE_ADDRESS                       0xA0
#define _PCB_SEC_EEPROM_IIC                             _NO_IIC_PIN


//////////
// UART //
//////////

//--------------------------------------------------
// UART Support Option
//--------------------------------------------------
#define _EXT_UART0_EN                                   _OFF
#define _EXT_UART1_EN                                   _OFF
#define _EXT_UART2_EN                                   _OFF


///////////////////
// Flash Control //
///////////////////

//--------------------------------------------------
// FLASH SPI Control Option
//--------------------------------------------------
#define _FLASH_CLK_DRIVE_CURRENT                        _SPI_DRIVE_4_0MA
#define _FLASH_SI_SO_CEB_DRIVE_CURRENT                  _SPI_DRIVE_4_0MA
#define _FLASH_CLK_SLEW_RATE_CONTROL                    _SPI_FAST_SLEW_RATE
#define _FLASH_SI_SO_CEB_SLEW_RATE_CONTROL              _SPI_FAST_SLEW_RATE


/////////////////
// SPI Setting //
/////////////////

//--------------------------------------------------
// Definitions of SPI Setting for Panel
//--------------------------------------------------
#define _PCB_SPI0_CLK_PRE_DIV                           0                   // SPI CLK PreDivider
#define _PCB_SPI0_CLK_DIV                               _DIV_4              // SPI CLK Divider
#define _PCB_SPI0_ENUM_PROTOCOL_SEL                     _SPI_NORMAL_MODE    // SPI Protocol Select
#define _PCB_SPI0_ENUM_CLK_SRC_SEL                      _SPI_EXT_XTAL_CLK   // SPI CLK Source
#define _PCB_SPI0_MOSI_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#define _PCB_SPI0_SCLK_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#define _PCB_SPI0_CS_SEL                                0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _PCB_SPI0_CS_POLARITY                           0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active

#define _PCB_SPI1_CLK_PRE_DIV                           0                   // SPI CLK PreDivider
#define _PCB_SPI1_CLK_DIV                               _DIV_4              // SPI CLK Divider
#define _PCB_SPI1_ENUM_PROTOCOL_SEL                     _SPI_NORMAL_MODE    // SPI Protocol Select
#define _PCB_SPI1_ENUM_CLK_SRC_SEL                      _SPI_EXT_XTAL_CLK   // SPI CLK Source
#define _PCB_SPI1_MOSI_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#define _PCB_SPI1_SCLK_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#define _PCB_SPI1_CS_SEL                                0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _PCB_SPI1_CS_POLARITY                           0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active

#define _PCB_SPI2_CLK_PRE_DIV                           0                   // SPI CLK PreDivider
#define _PCB_SPI2_CLK_DIV                               _DIV_4              // SPI CLK Divider
#define _PCB_SPI2_ENUM_PROTOCOL_SEL                     _SPI_NORMAL_MODE    // SPI Protocol Select
#define _PCB_SPI2_ENUM_CLK_SRC_SEL                      _SPI_EXT_XTAL_CLK   // SPI CLK Source
#define _PCB_SPI2_MOSI_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#define _PCB_SPI2_SCLK_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#define _PCB_SPI2_CS_SEL                                0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#define _PCB_SPI2_CS_POLARITY                           0


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#define _AD_KEY_SUPPORT                                 _OFF

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#define _LOW_SPEED_ADC_SUPPORT                          _OFF
#define _LOW_SPEED_ADC_POWER_REDUCE_SUPPORT             _OFF

//--------------------------------------------------
// Type-C 10-Bit ADC Option
//--------------------------------------------------
#define _10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT             _OFF

//--------------------------------------------------
// Type-C CC Pin GPIO Mode Option
//--------------------------------------------------
#define _TYPE_C_GPIO_MODE_SUPPORT                       _OFF


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON()        {\
                                                        }

#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                        {\
                                                        }

#define PCB_GPIO_SETTING_POWER_NORMAL()                 {\
                                                        }

#define PCB_GPIO_SETTING_POWER_SAVING()                 {\
                                                        }

#define PCB_GPIO_SETTING_POWER_DOWN()                   {\
                                                        }


/////////////////////
// SWR Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of Pcb SWR Power Control
//-----------------------------------------------
#define SET_SWR_CORE_POWER_SWITCH_1(x)                  {SET_GPIO_PIN_EMPTY(x);}
#define SET_SWR_CORE_POWER_SWITCH_2(x)                  {SET_GPIO_PIN_EMPTY(x);}

#define _SWR_CORE_POWER_SWITCH_1_SWITCH_ON              1
#define _SWR_CORE_POWER_SWITCH_1_SWITCH_OFF             0

#define _SWR_CORE_POWER_SWITCH_2_SWITCH_ON              1
#define _SWR_CORE_POWER_SWITCH_2_SWITCH_OFF             0

#define PCB_SWR_CORE_POWER_SWITCH_1(x)                  {\
                                                            SET_SWR_CORE_POWER_SWITCH_1(x);\
                                                        }

#define PCB_SWR_CORE_POWER_SWITCH_2(x)                  {\
                                                            SET_SWR_CORE_POWER_SWITCH_2(x);\
                                                        }

#define PCB_SWR_CORE_POWER_SETTING_AC_ON()              {\
                                                        }

#define PCB_SWR_CORE_POWER_SETTING_POWER_NORMAL()       {\
                                                        }

#define PCB_SWR_CORE_POWER_SETTING_POWER_SAVING()       {\
                                                        }

#define PCB_SWR_CORE_POWER_SETTING_POWER_DOWN()         {\
                                                        }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#define SET_VCCKOFFPOWER(x)                             {SET_GPIO_PIN_EMPTY(x);}

#define _VCCK_OFF_POWER_ON                              1
#define _VCCK_OFF_POWER_OFF                             0
#define _VCCK_OFF_TIME_POLLING_POWER_ON                 20 // ms

#define PCB_VCCK_OFF_POWER(x)                           {\
                                                            SET_VCCKOFFPOWER(x);\
                                                        }

//-----------------------------------------------
// Macro of DDR Poewr Control
//-----------------------------------------------
#define SET_DDRPOWER(x)                                 {SET_GPIO_PIN_EMPTY(x);}

#define _DDR_POWER_ON                                   1
#define _DDR_POWER_OFF                                  0

#define PCB_DDR_POWER(x)                                {\
                                                            SET_DDRPOWER(x);\
                                                        }

//-----------------------------------------------
// Macro of DDR Poewr Release Time Control
//-----------------------------------------------
#define _DDR_POWER_OFF_TIME                             200

//-----------------------------------------------
// Macro of Power Board Low Power Pin High/Low
//-----------------------------------------------
#define SET_POWERBOARDPOWER(x)                          {SET_GPIO_PIN_EMPTY(x);}

#define _LOW_POWER_ON                                   1
#define _LOW_POWER_OFF                                  0

#define PCB_POWERBOARD_LOWPOWER(x)                      {\
                                                            SET_POWERBOARDPOWER(x);\
                                                        }

//-----------------------------------------------
// Macro of 12V to 5V Regulator for MyDP or MHL
//-----------------------------------------------
#define SET_REGULATOR_5V(x)                             {SET_GPIO_PIN_EMPTY(x);}

#define _REGULATOR_5V_ON                                0
#define _REGULATOR_5V_OFF                               1

#define PCB_REGULATOR_5V_OUT(x)                         {\
                                                            SET_REGULATOR_5V(x);\
                                                        }

//-----------------------------------------------
// Macro of RX_LV Power Control
//-----------------------------------------------
#define SET_RX_LV_POWER(x)                              {SET_GPIO_PIN_EMPTY(x);}

#define _RX_LV_POWER_ON                                 1
#define _RX_LV_POWER_OFF                                0

#define PCB_SET_RX_LV_POWER(x)                          {\
                                                            SET_RX_LV_POWER(x);\
                                                        }


///////////////////////////
// Port Controller Macro //
///////////////////////////

//-----------------------------------------------
// Macro of External Port Controller Power Control
//-----------------------------------------------
#define GET_D0_PORT_CTRL_POWER()                        (GET_GPIO_PIN_EMPTY())
#define SET_D0_PORT_CTRL_POWER(x)                       {SET_GPIO_PIN_EMPTY(x);}
#define GET_D1_PORT_CTRL_POWER()                        (GET_GPIO_PIN_EMPTY())
#define SET_D1_PORT_CTRL_POWER(x)                       {SET_GPIO_PIN_EMPTY(x);}
#define GET_D2_PORT_CTRL_POWER()                        (GET_GPIO_PIN_EMPTY())
#define SET_D2_PORT_CTRL_POWER(x)                       {SET_GPIO_PIN_EMPTY(x);}
#define GET_P0_PORT_CTRL_POWER()                        (GET_GPIO_PIN_EMPTY())
#define SET_P0_PORT_CTRL_POWER(x)                       {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PORT_CTRL_POWER_ON                          1
#define _D0_PORT_CTRL_POWER_OFF                         0

#define _D1_PORT_CTRL_POWER_ON                          1
#define _D1_PORT_CTRL_POWER_OFF                         0

#define _D2_PORT_CTRL_POWER_ON                          1
#define _D2_PORT_CTRL_POWER_OFF                         0

#define _P0_PORT_CTRL_POWER_ON                          1
#define _P0_PORT_CTRL_POWER_OFF                         0

#define PCB_D0_PORT_CTRL_POWER(x)                       {\
                                                            SET_D0_PORT_CTRL_POWER(x);\
                                                        }

#define PCB_D1_PORT_CTRL_POWER(x)                       {\
                                                            SET_D1_PORT_CTRL_POWER(x);\
                                                        }

#define PCB_D2_PORT_CTRL_POWER(x)                       {\
                                                            SET_D2_PORT_CTRL_POWER(x);\
                                                        }

#define PCB_P0_PORT_CTRL_POWER(x)                       {\
                                                            SET_P0_PORT_CTRL_POWER(x);\
                                                        }

#define PCB_D0_PORT_CTRL_POWER_STATUS()                 (GET_D0_PORT_CTRL_POWER())
#define PCB_D1_PORT_CTRL_POWER_STATUS()                 (GET_D1_PORT_CTRL_POWER())
#define PCB_D2_PORT_CTRL_POWER_STATUS()                 (GET_D2_PORT_CTRL_POWER())
#define PCB_P0_PORT_CTRL_POWER_STATUS()                 (GET_P0_PORT_CTRL_POWER())


/////////////////////
// HUB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of TYPE_B VBUS POWER Detec
//-----------------------------------------------
#define GET_TYPE_B_VPWR_POWER()                         (GET_GPIO_PIN_EMPTY())

#define PCB_TYPE_B_VBUS_POWER_DETECT()                  (GET_TYPE_B_VPWR_POWER())

#define GET_D0_TYPE_B_VPWR_POWER()                      (GET_GPIO_PIN_EMPTY())
#define PCB_D0_TYPE_B_VBUS_POWER_DETECT()               (GET_D0_TYPE_B_VPWR_POWER())

#define GET_D1_TYPE_B_VPWR_POWER()                      (GET_GPIO_PIN_EMPTY())
#define PCB_D1_TYPE_B_VBUS_POWER_DETECT()               (GET_D1_TYPE_B_VPWR_POWER())

#define GET_D2_TYPE_B_VPWR_POWER()                      (GET_GPIO_PIN_EMPTY())
#define PCB_D2_TYPE_B_VBUS_POWER_DETECT()               (GET_D2_TYPE_B_VPWR_POWER())

//-----------------------------------------------
// Macro of HUB VBus Power Control
//-----------------------------------------------
#define GET_HUB_BPWR_0_POWER(x)                         (GET_GPIO_PIN_EMPTY())
#define SET_HUB_BPWR_0_POWER(x)                         {SET_GPIO_PIN_EMPTY(x);}
#define GET_HUB_BPWR_1_POWER(x)                         (GET_GPIO_PIN_EMPTY())
#define SET_HUB_BPWR_1_POWER(x)                         {SET_GPIO_PIN_EMPTY(x);}

#define _VBUS_0_POWER_ON                                0
#define _VBUS_0_POWER_OFF                               1
#define _VBUS_1_POWER_ON                                0
#define _VBUS_1_POWER_OFF                               1

#define PCB_HUB_0_BPWR_POWER(x)                         {\
                                                            SET_HUB_BPWR_0_POWER(x);\
                                                        }

#define PCB_HUB_1_BPWR_POWER(x)                         {\
                                                            SET_HUB_BPWR_1_POWER(x);\
                                                        }

#define PCB_HUB_BPWR_0_POWER_DETECT()                   (GET_HUB_BPWR_0_POWER())

#define PCB_HUB_BPWR_1_POWER_DETECT()                   (GET_HUB_BPWR_1_POWER())


/////////////////////////
// U2 MUX Switch Macro //
/////////////////////////

//-----------------------------------------------
// Macro of U2 MUX VBus Power Control
//-----------------------------------------------
#define SET_U2_MUX_EN(x)                                {SET_GPIO_PIN_EMPTY(x);}
#define SET_U2_MUX_SEL_S0(x)                            {SET_GPIO_PIN_EMPTY(x);}
#define SET_U2_MUX_SEL_S1(x)                            {SET_GPIO_PIN_EMPTY(x);}

#define _U2_MUX_ENABLE                                  0
#define _U2_MUX_DISABLE                                 1

#define _U2_MUX_SEL_LOW                                 0
#define _U2_MUX_SEL_HIGH                                1

#define PCB_U2_MUX_SWITCH_CONTROL(UsbHubUfP)            {\
                                                            if((UsbHubUfP) == _HUB_NONE_PORT)\
                                                            {\
                                                                SET_U2_MUX_EN(_U2_MUX_DISABLE);\
                                                            }\
                                                            else if((UsbHubUfP) == _HUB_D0_TYPE_C_PORT)\
                                                            {\
                                                                SET_U2_MUX_EN(_U2_MUX_ENABLE);\
                                                                SET_U2_MUX_SEL_S0(_U2_MUX_SEL_LOW);\
                                                                SET_U2_MUX_SEL_S1(_U2_MUX_SEL_LOW);\
                                                            }\
                                                            else if((UsbHubUfP) == _HUB_D1_TYPE_C_PORT)\
                                                            {\
                                                                SET_U2_MUX_EN(_U2_MUX_ENABLE);\
                                                                SET_U2_MUX_SEL_S0(_U2_MUX_SEL_HIGH);\
                                                                SET_U2_MUX_SEL_S1(_U2_MUX_SEL_LOW);\
                                                            }\
                                                            else if((UsbHubUfP) == _HUB_TYPE_B_PORT)\
                                                            {\
                                                                SET_U2_MUX_EN(_U2_MUX_ENABLE);\
                                                                SET_U2_MUX_SEL_S0(_U2_MUX_SEL_LOW);\
                                                                SET_U2_MUX_SEL_S1(_U3_MUX_SEL_HIGH);\
                                                            }\
                                                            else\
                                                            {\
                                                                SET_U2_MUX_EN(_U2_MUX_DISABLE);\
                                                            }\
                                                        }


/////////////////////////
// U3 MUX Switch Macro //
/////////////////////////

//-----------------------------------------------
// Macro of MUX VBus Power Control
//-----------------------------------------------
#define SET_U3_MUX_SEL_1(x)                             {SET_GPIO_PIN_EMPTY(x);}
#define SET_U3_MUX_SEL_2(x)                             {SET_GPIO_PIN_EMPTY(x);}

#define _U3_MUX_SEL_LOW                                 0
#define _U3_MUX_SEL_HIGH                                1


#define PCB_U3_MUX_SWITCH_CONTROL(UsbHubUfP)            {\
                                                            if((UsbHubUfP) == _HUB_NONE_PORT)\
                                                            {\
                                                                SET_U3_MUX_SEL_1(_U3_MUX_SEL_LOW);\
                                                                SET_U3_MUX_SEL_2(_U3_MUX_SEL_LOW);\
                                                            }\
                                                            else if((UsbHubUfP) == _HUB_D0_TYPE_C_PORT)\
                                                            {\
                                                                SET_U3_MUX_SEL_1(_U3_MUX_SEL_HIGH);\
                                                                SET_U3_MUX_SEL_2(_U3_MUX_SEL_LOW);\
                                                            }\
                                                            else if((UsbHubUfP) == _HUB_D1_TYPE_C_PORT)\
                                                            {\
                                                                SET_U3_MUX_SEL_1(_U3_MUX_SEL_LOW);\
                                                                SET_U3_MUX_SEL_2(_U3_MUX_SEL_HIGH);\
                                                            }\
                                                            else if((UsbHubUfP) == _HUB_TYPE_B_PORT)\
                                                            {\
                                                                SET_U3_MUX_SEL_1(_U3_MUX_SEL_HIGH);\
                                                                SET_U3_MUX_SEL_2(_U3_MUX_SEL_HIGH);\
                                                            }\
                                                            else\
                                                            {\
                                                                SET_U3_MUX_SEL_1(_U3_MUX_SEL_LOW);\
                                                                SET_U3_MUX_SEL_2(_U3_MUX_SEL_LOW);\
                                                            }\
                                                        }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define GET_PANELPOWER()                                (GET_GPIO_PIN_EMPTY())
#define SET_PANELPOWER(x)                               {SET_GPIO_PIN_EMPTY(x);}

#define _PANEL_CONTROL_ON                               0
#define _PANEL_CONTROL_OFF                              1

#define PCB_PANEL_POWER(x)                              {\
                                                        SET_PANELPOWER(x);\
                                                        }

#define PCB_PANEL_POWER_DETECT()                        (GET_PANELPOWER())

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define SET_BACKLIGHTPOWER(x)                           {SET_GPIO_PIN_EMPTY(x);}

#define _LIGHT_CONTROL_ON                               0
#define _LIGHT_CONTROL_OFF                              1

#define PCB_BACKLIGHT_POWER_PIN(x)                      {\
                                                            SET_BACKLIGHTPOWER(x);\
                                                        }

#define PCB_BACKLIGHT_POWER_PIN_EXINT(x)                {PCB_BACKLIGHT_POWER_PIN(x)}

#define PCB_BACKLIGHT_POWER(x)                          {\
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
#define SET_FLASH_WRITE_PROTECT(x)                      {SET_GPIO_PIN_EMPTY(x);}

#define _FLASH_WRITE_PROTECT_ENABLE                     0
#define _FLASH_WRITE_PROTECT_DISABLE                    1

#define PCB_FLASH_WRITE_PROTECT(x)                      {\
                                                            SET_FLASH_WRITE_PROTECT(x);\
                                                        }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define GET_EEPROM_WRITE_PROTECT()                      (GET_GPIO_PIN_EMPTY())
#define SET_EEPROM_WRITE_PROTECT(x)                     {SET_GPIO_PIN_EMPTY(x);}

#define _EEPROM_WP_ENABLE                               1
#define _EEPROM_WP_DISABLE                              0

#define PCB_EEPROM_WRITE_PROTECT(x)                     {\
                                                            SET_EEPROM_WRITE_PROTECT(x);\
                                                        }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()               (GET_EEPROM_WRITE_PROTECT())

//-----------------------------------------------
// Macro of TTS Flash write protect pin
//-----------------------------------------------
#define SET_TTS_FLASH_WRITE_PROTECT(x)                  {SET_GPIO_PIN_EMPTY(x);}

#define _TTS_FLASH_WRITE_PROTECT_ENABLE                 0
#define _TTS_FLASH_WRITE_PROTECT_DISABLE                1

#define PCB_TTS_FLASH_WRITE_PROTECT(x)                  {\
                                                            SET_TTS_FLASH_WRITE_PROTECT(x);\
                                                        }

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define SET_EDID_WRITE_PROTECT(x)                       {SET_GPIO_PIN_EMPTY(x);}

#define _EDID_EEPROM_WP_ENABLE                          1
#define _EDID_EEPROM_WP_DISABLE                         0

#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                            SET_EDID_WRITE_PROTECT(x);\
                                                        }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                            SET_EDID_WRITE_PROTECT(x);\
                                                        }

#define PCB_D4_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                            SET_EDID_WRITE_PROTECT(x);\
                                                        }


//////////////////////
// PCB Define Macro //
//////////////////////

//-----------------------------------------------
// Macro of HDMI External EDID Switch : #if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//-----------------------------------------------
#define SET_D3_EXT_SWITCH_EDID_0(x)                     {SET_GPIO_PIN_EMPTY(x);}
#define SET_D3_EXT_SWITCH_EDID_1(x)                     {SET_GPIO_PIN_EMPTY(x);}
#define SET_D3_EXT_SWITCH_EDID_2(x)                     {SET_GPIO_PIN_EMPTY(x);}
#define SET_D4_EXT_SWITCH_EDID_0(x)                     {SET_GPIO_PIN_EMPTY(x);}
#define SET_D4_EXT_SWITCH_EDID_1(x)                     {SET_GPIO_PIN_EMPTY(x);}
#define SET_D4_EXT_SWITCH_EDID_2(x)                     {SET_GPIO_PIN_EMPTY(x);}

#define _EEPROM_EDID_ENABLE                             1
#define _EEPROM_EDID_DISABLE                            0

#define PCB_MULTI_EDID_ALL_SWITCH_OFF(port)             {\
                                                        }

#define PCB_MULTI_EDID_SWITCH(port, index)              {\
                                                        }

#define PCB_MULTI_EDID_SWITCH_POWER_AC_ON()             {\
                                                        }

#define _HDMI_MULTI_EDID_TABLE                          "./RL6952/HDMI_MultiEdid/RL6952_Example_HDMI_MultiEdid.h"

//--------------------------------------------------
// Macro of Panel Display Switch Control
//--------------------------------------------------
#define SET_GPU_SW_0(x)                                 {SET_GPIO_PIN_EMPTY(x);}
#define SET_GPU_SW_1(x)                                 {SET_GPIO_PIN_EMPTY(x);}

#define _LVDS_PANEL_OUTPUT                              0
#define _EDPTX_PANEL_OUTPUT                             1

#define PCB_SET_LVDS_DPTX_SWITCH(x)                     {\
                                                            if((x) == _LVDS_PANEL_OUTPUT)\
                                                            {\
                                                                SET_GPU_SW_0(_LVDS_PANEL_OUTPUT);\
                                                                SET_GPU_SW_1(_LVDS_PANEL_OUTPUT);\
                                                            }\
                                                            else if((x) == _EDPTX_PANEL_OUTPUT)\
                                                            {\
                                                                SET_GPU_SW_0(_EDPTX_PANEL_OUTPUT);\
                                                                SET_GPU_SW_1(_EDPTX_PANEL_OUTPUT);\
                                                            }\
                                                        }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define GET_D0_DP_PIN15_CONNECT()                       (GET_GPIO_PIN_EMPTY())
#define GET_D0_DP_PIN16_CONNECT()                       (GET_GPIO_PIN_EMPTY())
#define GET_D0_DP_PIN17_CONNECT()                       (GET_GPIO_PIN_EMPTY())

#define GET_D1_DP_PIN15_CONNECT()                       (GET_GPIO_PIN_EMPTY())
#define GET_D1_DP_PIN16_CONNECT()                       (GET_GPIO_PIN_EMPTY())
#define GET_D1_DP_PIN17_CONNECT()                       (GET_GPIO_PIN_EMPTY())

#define GET_D2_DP_PIN15_CONNECT()                       (GET_GPIO_PIN_EMPTY())
#define GET_D2_DP_PIN16_CONNECT()                       (GET_GPIO_PIN_EMPTY())
#define GET_D2_DP_PIN17_CONNECT()                       (GET_GPIO_PIN_EMPTY())

// For Normal DP
#define GET_D0_CONNECT()                                (((bit)GET_D0_DP_PIN15_CONNECT() == _TRUE) && ((bit)GET_D0_DP_PIN16_CONNECT() == _TRUE) && ((bit)GET_D0_DP_PIN17_CONNECT() == _FALSE))
#define GET_D1_CONNECT()                                (((bit)GET_D1_DP_PIN15_CONNECT() == _TRUE) && ((bit)GET_D1_DP_PIN16_CONNECT() == _TRUE) && ((bit)GET_D1_DP_PIN17_CONNECT() == _FALSE))
#define GET_D2_CONNECT()                                (((bit)GET_D1_DP_PIN15_CONNECT() == _TRUE) && ((bit)GET_D1_DP_PIN16_CONNECT() == _TRUE) && ((bit)GET_D1_DP_PIN17_CONNECT() == _FALSE))

// For DP Type-C
#define GET_D0_CONNECT()                                (GET_GPIO_PIN_EMPTY())
#define GET_D1_CONNECT()                                (GET_GPIO_PIN_EMPTY())

// For HDMI
#define GET_D3_CONNECT()                                (GET_GPIO_PIN_EMPTY())
#define GET_D4_CONNECT()                                (GET_GPIO_PIN_EMPTY())
#define GET_D12_CONNECT()                               (GET_GPIO_PIN_EMPTY())
#define GET_D13_CONNECT()                               (GET_GPIO_PIN_EMPTY())
#define GET_D14_CONNECT()                               (GET_GPIO_PIN_EMPTY())
#define GET_D15_CONNECT()                               (GET_GPIO_PIN_EMPTY())

#define PCB_D0_PIN()                                    (GET_D0_CONNECT())
#define PCB_D1_PIN()                                    (GET_D1_CONNECT())
#define PCB_D2_PIN()                                    (GET_D2_CONNECT())
#define PCB_D3_PIN()                                    (GET_D3_CONNECT())
#define PCB_D4_PIN()                                    (GET_D4_CONNECT())
#define PCB_D12_PIN()                                   (GET_D12_CONNECT())
#define PCB_D13_PIN()                                   (GET_D13_CONNECT())
#define PCB_D14_PIN()                                   (GET_D14_CONNECT())
#define PCB_D15_PIN()                                   (GET_D15_CONNECT())

//-----------------------------------------------
// Macro of HDMI External Switch
//-----------------------------------------------
#define bHDMI_SW_SEL                                    (0) // (MCU_EMPTY_PIN_ASSIGN_ADDRESS) GPIO by user -> GPU_SEL or DDC_HPD_SEL
#define _SW_SEL_HDMI_D3                                 (0)
#define _SW_SEL_HDMI_D4                                 (0)
#define _SW_SEL_HDMI_D12                                (1)
#define _SW_SEL_HDMI_D13                                (2)
#define _SW_SEL_HDMI_D14                                (1)
#define _SW_SEL_HDMI_D15                                (2)
#define PCB_HDMI_SW_SELECT(x)                           {} // OE=L; GPU_SEL=x; DDC_HPD_SEL=x; OE=H
#define PCB_GET_HDMI_SW_SELECT()                        (bHDMI_SW_SEL)

//-----------------------------------------------
// Macro of Type-C Cable Connect
//-----------------------------------------------
// For DP Type-C
#define GET_D0_USB_TYPEC_AUXP_CONNECT()                 (GET_GPIO_PIN_EMPTY())
#define GET_D0_USB_TYPEC_AUXN_CONNECT()                 (GET_GPIO_PIN_EMPTY())

#define GET_D1_USB_TYPEC_AUXP_CONNECT()                 (GET_GPIO_PIN_EMPTY())
#define GET_D1_USB_TYPEC_AUXN_CONNECT()                 (GET_GPIO_PIN_EMPTY())

#define GET_D2_USB_TYPEC_AUXP_CONNECT()                 (GET_GPIO_PIN_EMPTY())
#define GET_D2_USB_TYPEC_AUXN_CONNECT()                 (GET_GPIO_PIN_EMPTY())

// For DP Type-C _D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#define GET_D0_CC_ATTACH()                              (GET_GPIO_PIN_EMPTY()) // _PCB_DP_TYPE_C_CC_ATTACH_LEVEL / _PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL
#define GET_D1_CC_ATTACH()                              (GET_GPIO_PIN_EMPTY()) // _PCB_DP_TYPE_C_CC_ATTACH_LEVEL / _PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL
#define GET_D2_CC_ATTACH()                              (GET_GPIO_PIN_EMPTY()) // _PCB_DP_TYPE_C_CC_ATTACH_LEVEL / _PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL

#define PCB_D0_CC_ATTACH()                              (GET_D0_CC_ATTACH())
#define PCB_D1_CC_ATTACH()                              (GET_D1_CC_ATTACH())
#define PCB_D2_CC_ATTACH()                              (GET_D2_CC_ATTACH())

// For DP Type-C _P0_DP_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#define GET_P0_CC_ATTACH()                              (GET_GPIO_PIN_EMPTY()) // _PCB_DP_TYPE_C_CC_ATTACH_LEVEL / _PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL

#define PCB_P0_CC_ATTACH()                              (GET_P0_CC_ATTACH())

// For DP Type-C _D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#define GET_D0_ALT_MODE_READY()                         (GET_GPIO_PIN_EMPTY()) // _PCB_DP_TYPE_C_ALTMODE_LEVEL / _PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL
#define GET_D1_ALT_MODE_READY()                         (GET_GPIO_PIN_EMPTY()) // _PCB_DP_TYPE_C_ALTMODE_LEVEL / _PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL
#define GET_D2_ALT_MODE_READY()                         (GET_GPIO_PIN_EMPTY()) // _PCB_DP_TYPE_C_ALTMODE_LEVEL / _PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL

#define PCB_D0_ALT_MODE_READY()                         (GET_D0_ALT_MODE_READY())
#define PCB_D1_ALT_MODE_READY()                         (GET_D1_ALT_MODE_READY())
#define PCB_D2_ALT_MODE_READY()                         (GET_D2_ALT_MODE_READY())

// For DP Type-C _P0_DP_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#define GET_P0_ALT_MODE_READY()                         (GET_GPIO_PIN_EMPTY()) // _PCB_DP_TYPE_C_ALTMODE_LEVEL / _PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL

#define PCB_P0_ALT_MODE_READY()                         (GET_P0_ALT_MODE_READY())

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()                    (GET_D0_DP_PIN17_CONNECT())
#define GET_PCB_D1_DP_SOURCE_POWER()                    (GET_D1_DP_PIN17_CONNECT())
#define GET_PCB_D2_DP_SOURCE_POWER()                    (GET_D2_DP_PIN17_CONNECT())

// For DP Type-C
#define GET_PCB_D0_DP_SOURCE_POWER()                    (GET_D0_USB_TYPEC_AUXN_CONNECT())
#define GET_PCB_D1_DP_SOURCE_POWER()                    (GET_D1_USB_TYPEC_AUXN_CONNECT())
#define GET_PCB_D2_DP_SOURCE_POWER()                    (GET_D2_USB_TYPEC_AUXN_CONNECT())

/////////////////////////////
// DP CableID Config1 Ctrl //
/////////////////////////////

//-----------------------------------------------
// Macro of Dp CableID Detection Config1 Pin High/Low
//-----------------------------------------------
#define SET_D0_CABLEID_DET_CONFIG1(x)                   {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_CABLEID_DET_CONFIG1(x)                   {SET_GPIO_PIN_EMPTY(x);}
#define SET_D2_CABLEID_DET_CONFIG1(x)                   {SET_GPIO_PIN_EMPTY(x);}

#define _D0_CABLEID_DET_CONFIG1_HIGH                    1
#define _D0_CABLEID_DET_CONFIG1_LOW                     0
#define _D1_CABLEID_DET_CONFIG1_HIGH                    1
#define _D1_CABLEID_DET_CONFIG1_LOW                     0
#define _D2_CABLEID_DET_CONFIG1_HIGH                    1
#define _D2_CABLEID_DET_CONFIG1_LOW                     0

#define PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1(x)       {\
                                                            SET_D0_CABLEID_DET_CONFIG1(x);\
                                                        }

#define PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1(x)       {\
                                                            SET_D1_CABLEID_DET_CONFIG1(x);\
                                                        }

#define PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1(x)       {\
                                                            SET_D2_CABLEID_DET_CONFIG1(x);\
                                                        }


// For DP Source Power When under Pin E Type and Aux PN Swap
#define GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP()            (GET_D0_USB_TYPEC_AUXP_CONNECT())
#define GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP()            (GET_D1_USB_TYPEC_AUXP_CONNECT())
#define GET_PCB_D2_DP_SOURCE_POWER_PN_SWAP()            (GET_D2_USB_TYPEC_AUXP_CONNECT())

//-----------------------------------------------
// Aux PN 1M Pull High / low Swap Control
//-----------------------------------------------
#define GET_D0_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN()         (GET_GPIO_PIN_EMPTY())
#define SET_D0_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN(x)        {SET_GPIO_PIN_EMPTY(x);}
#define GET_D1_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN()         (GET_GPIO_PIN_EMPTY())
#define SET_D1_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN(x)        {SET_GPIO_PIN_EMPTY(x);}
#define GET_D2_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN()         (GET_GPIO_PIN_EMPTY())
#define SET_D2_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN(x)        {SET_GPIO_PIN_EMPTY(x);}

#define _AUX_PN_1M_PULL_HI_LOW_SWAP_ON                  1
#define _AUX_PN_1M_PULL_HI_LOW_SWAP_OFF                 0

#define PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(x)               {\
                                                            SET_D0_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN(x);\
                                                        }

#define PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(x)               {\
                                                            SET_D1_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN(x);\
                                                        }

#define PCB_D2_AUX_PN_1M_PULL_H_L_SWAP(x)               {\
                                                            SET_D2_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN(x);\
                                                        }

#define PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP()            (GET_D0_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN())
#define PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP()            (GET_D1_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN())
#define PCB_GET_D2_AUX_PN_1M_PULL_H_L_SWAP()            (GET_D2_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN())


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define GET_D0_HPD()                                    (GET_GPIO_PIN_EMPTY())
#define SET_D0_HPD(x)                                   {SET_GPIO_PIN_EMPTY(x);}
#define GET_D1_HPD()                                    (GET_GPIO_PIN_EMPTY())
#define SET_D1_HPD(x)                                   {SET_GPIO_PIN_EMPTY(x);}
#define GET_D2_HPD()                                    (GET_GPIO_PIN_EMPTY())
#define SET_D2_HPD(x)                                   {SET_GPIO_PIN_EMPTY(x);}
#define GET_D3_HPD()                                    (GET_GPIO_PIN_EMPTY())
#define SET_D3_HPD(x)                                   {SET_GPIO_PIN_EMPTY(x);}
#define GET_D4_HPD()                                    (GET_GPIO_PIN_EMPTY())
#define SET_D4_HPD(x)                                   {SET_GPIO_PIN_EMPTY(x);}

#define _D0_HOT_PLUG_HIGH                               1
#define _D0_HOT_PLUG_LOW                                0

#define _D1_HOT_PLUG_HIGH                               1
#define _D1_HOT_PLUG_LOW                                0

#define _D2_HOT_PLUG_HIGH                               1
#define _D2_HOT_PLUG_LOW                                0

#define _D3_HOT_PLUG_HIGH                               1
#define _D3_HOT_PLUG_LOW                                0

#define _D4_HOT_PLUG_HIGH                               1
#define _D4_HOT_PLUG_LOW                                0

#define PCB_D0_HOTPLUG(x)                               {\
                                                            SET_D0_HPD(x);\
                                                        }

#define PCB_D1_HOTPLUG(x)                               {\
                                                            SET_D1_HPD(x);\
                                                        }

#define PCB_D2_HOTPLUG(x)                               {\
                                                            SET_D2_HPD(x);\
                                                        }

#define PCB_D3_HOTPLUG(x)                               {\
                                                            SET_D3_HPD(x);\
                                                        }

#define PCB_D4_HOTPLUG(x)                               {\
                                                            SET_D4_HPD(x);\
                                                        }

#define PCB_D0_HOTPLUG_DETECT()                         (GET_D0_HPD())
#define PCB_D1_HOTPLUG_DETECT()                         (GET_D1_HPD())
#define PCB_D2_HOTPLUG_DETECT()                         (GET_D2_HPD())
#define PCB_D3_HOTPLUG_DETECT()                         (GET_D3_HPD())
#define PCB_D4_HOTPLUG_DETECT()                         (GET_D4_HPD())


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#define PCB_PWM_SETTING()                               {\
                                                            UserCommonMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 240);\
                                                        }

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)

#define PCB_BACKLIGHT_PWM(x)                            {\
                                                            MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                        }

#define PCB_GET_BACKLIGHT_PWM()                         (MCU_GET_8BIT_PWM_DUTY(_BACKLIGHT_PWM))

#elif(_PWM_DUT_RESOLUTION == _PWM_12BIT)

#define PCB_BACKLIGHT_PWM(x)                            {\
                                                            MCU_ADJUST_12BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                        }

#define PCB_GET_BACKLIGHT_PWM()                         (MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))

#endif


//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#define GET_SWIIC_SYS_EEPROM_SCL()                      (GET_GPIO_PIN_EMPTY())
#define SET_SWIIC_SYS_EEPROM_SCL(x)                     {SET_GPIO_PIN_EMPTY(x);}

#define GET_SWIIC_SYS_EEPROM_SDA()                      (GET_GPIO_PIN_EMPTY())
#define SET_SWIIC_SYS_EEPROM_SDA(x)                     {SET_GPIO_PIN_EMPTY(x);}

#define PCB_SW_IIC_SDA_SET()                            {\
                                                            if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                            {\
                                                                SET_SWIIC_SYS_EEPROM_SDA(_TRUE);\
                                                            }\
                                                        }
#define PCB_SW_IIC_SDA_CLR()                            {\
                                                            if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                            {\
                                                                SET_SWIIC_SYS_EEPROM_SDA(_FALSE);\
                                                            }\
                                                        }
#define PCB_SW_IIC_SDA_CHK(x)                           {\
                                                            if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                            {\
                                                                (x) = GET_SWIIC_SYS_EEPROM_SDA;\
                                                            }\
                                                        }

#define PCB_SW_IIC_SCL_SET()                            {\
                                                            if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                            {\
                                                                SET_SWIIC_SYS_EEPROM_SCL(_TRUE);\
                                                            }\
                                                        }
#define PCB_SW_IIC_SCL_CLR()                            {\
                                                            if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                            {\
                                                                SET_SWIIC_SYS_EEPROM_SCL(_FALSE);\
                                                            }\
                                                        }
#define PCB_SW_IIC_SCL_CHK(x)                           {\
                                                            if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                            {\
                                                                (x) = GET_SWIIC_SYS_EEPROM_SCL;\
                                                            }\
                                                        }


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#define SET_LED1(x)                                     {SET_GPIO_PIN_EMPTY(x);}
#define SET_LED2(x)                                     {SET_GPIO_PIN_EMPTY(x);}

#define _LED_ON                                         1
#define _LED_OFF                                        0

#define PCB_LED_AC_ON_INITIAL()                         {\
                                                        }

#define PCB_LED_ACTIVE()                                {\
                                                        }

#define PCB_LED_IDLE()                                  {\
                                                        }

#define PCB_LED_POWER_SAVING()                          {\
                                                        }

#define PCB_LED_ON()                                    {\
                                                        }

#define PCB_LED_OFF()                                   {\
                                                        }

#define PCB_LED_TYPE1()                                 {\
                                                        }

#define PCB_LED_TYPE_FLASH()                            {\
                                                        }


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define AD_KEY0                                         (GET_SARADC_EMPTY_VALUE())
#define AD_KEY1                                         (GET_SARADC_EMPTY_VALUE())

#define PCB_ADKEY0()                                    (_FALSE)
#define PCB_ADKEY1()                                    (_FALSE)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)           {\
                                                        }


////////////////////
// GPIO Key Macro //
////////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define GET_POWER_KEY()                                 (GET_GPIO_PIN_EMPTY())
#define GET_MENU_KEY()                                  (GET_GPIO_PIN_EMPTY())
#define GET_EXIT_KEY()                                  (GET_GPIO_PIN_EMPTY())
#define GET_LEFT_KEY()                                  (GET_GPIO_PIN_EMPTY())
#define GET_RIGHT_KEY()                                 (GET_GPIO_PIN_EMPTY())

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)           {\
                                                        }


//////////////////////
// I2C Slave Macro //
//////////////////////

//-----------------------------------------------
// Macro of IIC 1 Slave Enable Pin
//-----------------------------------------------
#define _HW_IIC_1_SLAVE_SUPPORT_ENABLE                  0
#define _HW_IIC_1_SLAVE_SUPPORT_DISABLE                 1

#define PCB_GPIO_GET_IIC_1_SLAVE_SUPPORT_CONFIG()       (GET_GPIO_PIN_EMPTY())

//-----------------------------------------------
// Macro of IIC 1 Slave Address Config Pin
//-----------------------------------------------
#define PCB_GPIO_GET_IIC_1_SLAVE_ADDR_CONFIG_0()        (GET_GPIO_PIN_EMPTY())
#define PCB_GPIO_GET_IIC_1_SLAVE_ADDR_CONFIG_1()        (GET_GPIO_PIN_EMPTY())


//////////////////////
// PMIC Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of PMIC Power Control
//-----------------------------------------------
#define SET_D0_PMIC_POWER(x)                            {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_PMIC_POWER(x)                            {SET_GPIO_PIN_EMPTY(x);}
#define SET_P0_PMIC_POWER(x)                            {SET_GPIO_PIN_EMPTY(x);}
#define SET_ADAPTOR_PMIC_POWER(x)                       {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PMIC_POWER_ON                               1
#define _D0_PMIC_POWER_OFF                              0

#define _D1_PMIC_POWER_ON                               1
#define _D1_PMIC_POWER_OFF                              0

#define _P0_PMIC_POWER_ON                               1
#define _P0_PMIC_POWER_OFF                              0

#define _ADAPTOR_PMIC_POWER_ON                          1
#define _ADAPTOR_PMIC_POWER_OFF                         0


#define PCB_D0_PMIC_POWER(x)                            {\
                                                             SET_D0_PMIC_POWER(x);\
                                                        }

#define PCB_D1_PMIC_POWER(x)                            {\
                                                             SET_D1_PMIC_POWER(x);\
                                                        }

#define PCB_P0_PMIC_POWER(x)                            {\
                                                            SET_P0_PMIC_POWER(x);\
                                                        }

#define PCB_ADAPTOR_PMIC_POWER(x)                       {\
                                                            SET_ADAPTOR_PMIC_POWER(x);\
                                                        }

//-----------------------------------------------
// Macro of Pmic FRWEN Enable Control
//-----------------------------------------------
#define SET_D0_PMIC_FRWEN_CONTROL(x)                    {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_PMIC_FRWEN_CONTROL(x)                    {SET_GPIO_PIN_EMPTY(x);}
#define SET_P0_PMIC_FRWEN_CONTROL(x)                    {SET_GPIO_PIN_EMPTY(x);}
#define SET_ADAPTOR_PMIC_FRWEN_CONTROL(x)               {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PMIC_FOWARD_CONTROL_ON                      1
#define _D0_PMIC_FOWARD_CONTROL_OFF                     0

#define _D1_PMIC_FOWARD_CONTROL_ON                      1
#define _D1_PMIC_FOWARD_CONTROL_OFF                     0

#define _P0_PMIC_FOWARD_CONTROL_ON                      1
#define _P0_PMIC_FOWARD_CONTROL_OFF                     0

#define _ADAPTOR_PMIC_FOWARD_CONTROL_ON                 1
#define _ADAPTOR_PMIC_FOWARD_CONTROL_OFF                0

#define PCB_D0_PMIC_FOWARD_CONTROL(x)                   {\
                                                            SET_D0_PMIC_FRWEN_CONTROL(x);\
                                                        }

#define PCB_D1_PMIC_FOWARD_CONTROL(x)                   {\
                                                            SET_D1_PMIC_FRWEN_CONTROL(x);\
                                                        }

#define PCB_P0_PMIC_FOWARD_CONTROL(x)                   {\
                                                            SET_P0_PMIC_FRWEN_CONTROL(x);\
                                                        }

#define PCB_ADAPTOR_PMIC_FOWARD_CONTROL(x)              {\
                                                            SET_ADAPTOR_PMIC_FRWEN_CONTROL(x);\
                                                        }

//-----------------------------------------------
// Macro of Pmic FRW Power Good
//-----------------------------------------------
#define GET_D0_PMIC_FRWPG()                             (GET_GPIO_PIN_EMPTY())
#define GET_D1_PMIC_FRWPG()                             (GET_GPIO_PIN_EMPTY())
#define GET_P0_PMIC_FRWPG()                             (GET_GPIO_PIN_EMPTY())
#define GET_ADAPTOR_PMIC_FRWPG()                        (GET_GPIO_PIN_EMPTY())

#define _D0_PMIC_FRWPG_ON                               1
#define _D0_PMIC_FRWPG_OFF                              0

#define _D1_PMIC_FRWPG_ON                               1
#define _D1_PMIC_FRWPG_OFF                              0

#define _P0_PMIC_FRWPG_ON                               1
#define _P0_PMIC_FRWPG_OFF                              0

#define _ADAPTOR_PMIC_FRWPG_ON                          1
#define _ADAPTOR_PMIC_FRWPG_OFF                         0

#define PCB_D0_PMIC_FRWPG_DETECT()                      (GET_D0_PMIC_FRWPG())
#define PCB_D1_PMIC_FRWPG_DETECT()                      (GET_D1_PMIC_FRWPG())
#define PCB_P0_PMIC_FRWPG_DETECT()                      (GET_P0_PMIC_FRWPG())
#define PCB_ADAPTOR_PMIC_FRWPG_DETECT()                 (GET_ADAPTOR_PMIC_FRWPG())

//-----------------------------------------------
// Macro of Pmic RVSEN Enable Control
//-----------------------------------------------
#define SET_D0_PMIC_RVSEN_CONTROL(x)                    {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_PMIC_RVSEN_CONTROL(x)                    {SET_GPIO_PIN_EMPTY(x);}
#define SET_P0_PMIC_RVSEN_CONTROL(x)                    {SET_GPIO_PIN_EMPTY(x);}
#define SET_ADAPTOR_PMIC_RVSEN_CONTROL(x)               {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PMIC_REVERSE_CONTROL_ON                     1
#define _D0_PMIC_REVERSE_CONTROL_OFF                    0

#define _D1_PMIC_REVERSE_CONTROL_ON                     1
#define _D1_PMIC_REVERSE_CONTROL_OFF                    0

#define _P0_PMIC_REVERSE_CONTROL_ON                     1
#define _P0_PMIC_REVERSE_CONTROL_OFF                    0

#define _ADAPTOR_PMIC_REVERSE_CONTROL_ON                1
#define _ADAPTOR_PMIC_REVERSE_CONTROL_OFF               0

#define PCB_D0_PMIC_REVERSE_CONTROL(x)                  {\
                                                            SET_D0_PMIC_RVSEN_CONTROL(x);\
                                                        }

#define PCB_D1_PMIC_REVERSE_CONTROL(x)                  {\
                                                            SET_D1_PMIC_RVSEN_CONTROL(x);\
                                                        }

#define PCB_P0_PMIC_REVERSE_CONTROL(x)                  {\
                                                            SET_P0_PMIC_RVSEN_CONTROL(x);\
                                                        }

#define PCB_ADAPTOR_PMIC_REVERSE_CONTROL(x)             {\
                                                            SET_ADAPTOR_PMIC_RVSEN_CONTROL(x);\
                                                        }

//-----------------------------------------------
// Macro of Pmic RVS Power Good
//-----------------------------------------------
#define GET_D0_PMIC_RVSPG()                             (GET_GPIO_PIN_EMPTY())
#define GET_D1_PMIC_RVSPG()                             (GET_GPIO_PIN_EMPTY())
#define GET_P0_PMIC_RVSPG()                             (GET_GPIO_PIN_EMPTY())
#define GET_ADAPTOR_PMIC_RVSPG()                        (GET_GPIO_PIN_EMPTY())

#define _D0_PMIC_RVSPG_ON                               1
#define _D0_PMIC_RVSPG_OFF                              0

#define _D1_PMIC_RVSPG_ON                               1
#define _D1_PMIC_RVSPG_OFF                              0

#define _P0_PMIC_RVSPG_ON                               1
#define _P0_PMIC_RVSPG_OFF                              0

#define _ADAPTOR_PMIC_RVSPG_ON                          1
#define _ADAPTOR_PMIC_RVSPG_OFF                         0

#define PCB_D0_PMIC_RVSPG_DETECT()                      (GET_D0_PMIC_RVSPG())
#define PCB_D1_PMIC_RVSPG_DETECT()                      (GET_D1_PMIC_RVSPG())
#define PCB_P0_PMIC_RVSPG_DETECT()                      (GET_P0_PMIC_RVSPG())
#define PCB_ADAPTOR_PMIC_RVSPG_DETECT()                 (GET_ADAPTOR_PMIC_RVSPG())

//-----------------------------------------------
// Macro of Pmic ALERT Detect
//-----------------------------------------------
#define GET_D0_PMIC_ALERT()                             (GET_GPIO_PIN_EMPTY())
#define GET_D1_PMIC_ALERT()                             (GET_GPIO_PIN_EMPTY())
#define GET_P0_PMIC_ALERT()                             (GET_GPIO_PIN_EMPTY())
#define GET_ADAPTOR_PMIC_ALERT()                        (GET_GPIO_PIN_EMPTY())

#define _D0_PMIC_ALERT_ON                               1
#define _D0_PMIC_ALERT_OFF                              0

#define _D1_PMIC_ALERT_ON                               1
#define _D1_PMIC_ALERT_OFF                              0

#define _P0_PMIC_ALERT_ON                               1
#define _P0_PMIC_ALERT_OFF                              0

#define _ADAPTOR_PMIC_ALERT_ON                          1
#define _ADAPTOR_PMIC_ALERT_OFF                         0


#define PCB_D0_PMIC_ALERT_DETECT()                      (GET_D0_PMIC_ALERT())
#define PCB_D1_PMIC_ALERT_DETECT()                      (GET_D1_PMIC_ALERT())
#define PCB_P0_PMIC_ALERT_DETECT()                      (GET_P0_PMIC_ALERT())
#define PCB_ADAPTOR_PMIC_ALERT_DETECT()                 (GET_ADAPTOR_PMIC_ALERT())

//-----------------------------------------------
// Macro of PMIC Power Detect
//-----------------------------------------------
#define GET_D0_PMIC_POWER_DETECT()                      (GET_GPIO_PIN_EMPTY())
#define GET_D1_PMIC_POWER_DETECT()                      (GET_GPIO_PIN_EMPTY())
#define GET_P0_PMIC_POWER_DETECT()                      (GET_GPIO_PIN_EMPTY())
#define GET_ADAPTOR_PMIC_POWER_DETECT()                 (GET_GPIO_PIN_EMPTY())

#define _D0_PMIC_POWER_TURN_ON                          1
#define _D0_PMIC_POWER_TURN_OFF                         0

#define _D1_PMIC_POWER_TURN_ON                          1
#define _D1_PMIC_POWER_TURN_OFF                         0

#define _P0_PMIC_POWER_TURN_ON                          1
#define _P0_PMIC_POWER_TURN_OFF                         0

#define _ADAPTOR_PMIC_POWER_TURN_ON                     1
#define _ADAPTOR_PMIC_POWER_TURN_OFF                    0

#define PCB_D0_PMIC_POWER_DETECT()                      (GET_D0_PMIC_POWER_DETECT())
#define PCB_D1_PMIC_POWER_DETECT()                      (GET_D1_PMIC_POWER_DETECT())
#define PCB_P0_PMIC_POWER_DETECT()                      (GET_P0_PMIC_POWER_DETECT())
#define PCB_ADAPTOR_PMIC_POWER_DETECT()                 (GET_ADAPTOR_PMIC_POWER_DETECT())

//-----------------------------------------------
// Macro of PMIC VBUS Power SOURCE Control
//-----------------------------------------------
#define SET_D0_PMIC_VBUS_SOURCE_CONTROL(x)              {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_PMIC_VBUS_SOURCE_CONTROL(x)              {SET_GPIO_PIN_EMPTY(x);}
#define SET_P0_PMIC_VBUS_SOURCE_CONTROL(x)              {SET_GPIO_PIN_EMPTY(x);}
#define SET_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(x)         {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PMIC_VBUS_SOURCE_SWITCH_ON                  0
#define _D0_PMIC_VBUS_SOURCE_SWITCH_OFF                 1

#define _D1_PMIC_VBUS_SOURCE_SWITCH_ON                  0
#define _D1_PMIC_VBUS_SOURCE_SWITCH_OFF                 1

#define _P0_PMIC_VBUS_SOURCE_SWITCH_ON                  0
#define _P0_PMIC_VBUS_SOURCE_SWITCH_OFF                 1

#define _ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON             0
#define _ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF            1


#define PCB_D0_PMIC_VBUS_SOURCE_CONTROL(x)              {\
                                                            SET_D0_PMIC_VBUS_SOURCE_CONTROL(x);\
                                                        }

#define PCB_D1_PMIC_VBUS_SOURCE_CONTROL(x)              {\
                                                            SET_D1_PMIC_VBUS_SOURCE_CONTROL(x);\
                                                        }

#define PCB_P0_PMIC_VBUS_SOURCE_CONTROL(x)              {\
                                                            SET_P0_PMIC_VBUS_SOURCE_CONTROL(x);\
                                                        }

#define PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(x)         {\
                                                            SET_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(x);\
                                                        }

//-----------------------------------------------
// Macro of PMIC VBUS Power SINK Control
//-----------------------------------------------
#define SET_D0_PMIC_VBUS_SINK_CONTROL(x)                {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_PMIC_VBUS_SINK_CONTROL(x)                {SET_GPIO_PIN_EMPTY(x);}
#define SET_P0_PMIC_VBUS_SINK_CONTROL(x)                {SET_GPIO_PIN_EMPTY(x);}
#define SET_ADAPTOR_PMIC_VBUS_SINK_CONTROL(x)           {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PMIC_VBUS_SINK_SWITCH_ON                    1
#define _D0_PMIC_VBUS_SINK_SWITCH_OFF                   0

#define _D1_PMIC_VBUS_SINK_SWITCH_ON                    1
#define _D1_PMIC_VBUS_SINK_SWITCH_OFF                   0

#define _P0_PMIC_VBUS_SINK_SWITCH_ON                    1
#define _P0_PMIC_VBUS_SINK_SWITCH_OFF                   0

#define _ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON               1
#define _ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF              0

#define PCB_D0_PMIC_VBUS_SINK_CONTROL(x)                {\
                                                            SET_D0_PMIC_VBUS_SINK_CONTROL(x);\
                                                        }

#define PCB_D1_PMIC_VBUS_SINK_CONTROL(x)                {\
                                                            SET_D1_PMIC_VBUS_SINK_CONTROL(x);\
                                                        }

#define PCB_P0_PMIC_VBUS_SINK_CONTROL(x)                {\
                                                            SET_P0_PMIC_VBUS_SINK_CONTROL(x);\
                                                        }

#define PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(x)           {\
                                                            SET_ADAPTOR_PMIC_VBUS_SINK_CONTROL(x);\
                                                        }

//-----------------------------------------------
// Macro of PMIC Interrupt Detect
//-----------------------------------------------
#define GET_D0_PMIC_INTERRUPT()                         (GET_GPIO_PIN_EMPTY())
#define GET_D1_PMIC_INTERRUPT()                         (GET_GPIO_PIN_EMPTY())
#define GET_P0_PMIC_INTERRUPT()                         (GET_GPIO_PIN_EMPTY())
#define GET_ADAPTOR_PMIC_INTERRUPT()                    (GET_GPIO_PIN_EMPTY())

#define _D0_PMIC_INTERRUPT_ON                           0
#define _D0_PMIC_INTERRUPT_OFF                          1

#define _D1_PMIC_INTERRUPT_ON                           0
#define _D1_PMIC_INTERRUPT_OFF                          1

#define _P0_PMIC_INTERRUPT_ON                           0
#define _P0_PMIC_INTERRUPT_OFF                          1

#define _ADAPTOR_PMIC_INTERRUPT_ON                      0
#define _ADAPTOR_PMIC_INTERRUPT_OFF                     1

#define PCB_D0_PMIC_INTERRUPT_DETECT()                  (GET_D0_PMIC_INTERRUPT())
#define PCB_D1_PMIC_INTERRUPT_DETECT()                  (GET_D1_PMIC_INTERRUPT())
#define PCB_P0_PMIC_INTERRUPT_DETECT()                  (GET_P0_PMIC_INTERRUPT())
#define PCB_ADAPTOR_PMIC_INTERRUPT_DETECT()             (GET_ADAPTOR_PMIC_INTERRUPT())


/////////////////////////////
// Type-C ADC Switch Macro //
/////////////////////////////

//-----------------------------------------------
// Macro of Type-C ADC Switch Control
//-----------------------------------------------
#define SET_D0_TYPE_C_ADC_SWITCH(x)                     {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_TYPE_C_ADC_SWITCH(x)                     {SET_GPIO_PIN_EMPTY(x);}

#define _D0_TYPE_C_ADC_SWITCH_ON                        0
#define _D0_TYPE_C_ADC_SWITCH_OFF                       1

#define _D1_TYPE_C_ADC_SWITCH_ON                        0
#define _D1_TYPE_C_ADC_SWITCH_OFF                       1

#define PCB_D0_TYPE_C_ADC_SWITCH(x)                     {\
                                                            SET_D0_TYPE_C_ADC_SWITCH(x);\
                                                        }

#define PCB_D1_TYPE_C_ADC_SWITCH(x)                     {\
                                                            SET_D1_TYPE_C_ADC_SWITCH(x);\
                                                        }

//-----------------------------------------------
// Macro of Type-C ADC High VBUS Detect Control
//-----------------------------------------------
#define SET_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)        {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)        {SET_GPIO_PIN_EMPTY(x);}

#define _D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON           1
#define _D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF          0

#define _D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON           1
#define _D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF          0

#define PCB_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)        {\
                                                            SET_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x);\
                                                        }

#define PCB_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)        {\
                                                            SET_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x);\
                                                        }


/////////////////////
// Type-C CC Macro //
/////////////////////

//-----------------------------------------------
// Macro of PMIC Discharge Control
//-----------------------------------------------
#define SET_D0_VBUS_DISCHARGE_CONTROL(x)                {SET_GPIO_PIN_EMPTY(x);}
#define SET_D1_VBUS_DISCHARGE_CONTROL(x)                {SET_GPIO_PIN_EMPTY(x);}
#define SET_P0_VBUS_DISCHARGE_CONTROL(x)                {SET_GPIO_PIN_EMPTY(x);}
#define SET_ADAPTOR_VBUS_DISCHARGE_CONTROL(x)           {SET_GPIO_PIN_EMPTY(x);}

#define _D0_PMIC_VBUS_DISCHARGE_ON                      1
#define _D0_PMIC_VBUS_DISCHARGE_OFF                     0

#define _D1_PMIC_VBUS_DISCHARGE_ON                      1
#define _D1_PMIC_VBUS_DISCHARGE_OFF                     0

#define _P0_PMIC_VBUS_DISCHARGE_ON                      1
#define _P0_PMIC_VBUS_DISCHARGE_OFF                     0

#define _ADAPTOR_PMIC_VBUS_DISCHARGE_ON                 1
#define _ADAPTOR_PMIC_VBUS_DISCHARGE_OFF                0

#define PCB_D0_VBUS_DISCHARGE_CONTROL(x)                {\
                                                            SET_D0_VBUS_DISCHARGE_CONTROL(x);\
                                                        }

#define PCB_D1_VBUS_DISCHARGE_CONTROL(x)                {\
                                                            SET_D1_VBUS_DISCHARGE_CONTROL(x);\
                                                        }

#define PCB_P0_VBUS_DISCHARGE_CONTROL(x)                {\
                                                            SET_P0_VBUS_DISCHARGE_CONTROL(x);\
                                                        }

#define PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(x)           {\
                                                            SET_ADAPTOR_VBUS_DISCHARGE_CONTROL(x);\
                                                        }

//-----------------------------------------------
// Macro of Type-C CC Control
//-----------------------------------------------
#define SET_TC0_CC_SWITCH_CONTROL_0(x)                  {SET_GPIO_PIN_EMPTY(x);}
#define SET_TC0_CC_SWITCH_CONTROL_1(x)                  {SET_GPIO_PIN_EMPTY(x);}
#define SET_TC0_CC_SWITCH_CONTROL_2(x)                  {SET_GPIO_PIN_EMPTY(x);}
#define SET_TC1_CC_SWITCH_CONTROL_0(x)                  {SET_GPIO_PIN_EMPTY(x);}
#define SET_TC1_CC_SWITCH_CONTROL_1(x)                  {SET_GPIO_PIN_EMPTY(x);}
#define SET_TC1_CC_SWITCH_CONTROL_2(x)                  {SET_GPIO_PIN_EMPTY(x);}

#define _CC_CONTROL_ON                                  0
#define _CC_CONTROL_OFF                                 1

#define _PCB_D0_TYPE_C_PORT                             0
#define _PCB_D1_TYPE_C_PORT                             1
#define _PCB_P0_TYPE_C_PORT                             2
#define _EMBEDDED_TYPE_C_0                              3
#define _EMBEDDED_TYPE_C_1                              4

#define PCB_TC0_CC_VBUS_SWITCH_CONTROL(TypeCPcbPort)\
                                                        {\
                                                            if((TypeCPcbPort) == _PCB_D0_TYPE_C_PORT)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_0(_CC_CONTROL_ON);\
                                                                SET_TC0_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                            }\
                                                            else if((TypeCPcbPort) == _PCB_D1_TYPE_C_PORT)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                                SET_TC0_CC_SWITCH_CONTROL_1(_CC_CONTROL_ON);\
                                                            }\
                                                            else if((TypeCPcbPort) == _PCB_P0_TYPE_C_PORT)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                                SET_TC0_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                            }\
                                                            else\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                                SET_TC0_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                            }\
                                                        }

#define PCB_TC1_CC_VBUS_SWITCH_CONTROL(TypeCPcbPort)\
                                                        {\
                                                            if((TypeCPcbPort) == _PCB_D0_TYPE_C_PORT)\
                                                            {\
                                                                SET_TC1_CC_SWITCH_CONTROL_0(_CC_CONTROL_ON);\
                                                                SET_TC1_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                            }\
                                                            else if((TypeCPcbPort) == _PCB_D1_TYPE_C_PORT)\
                                                            {\
                                                                SET_TC1_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_1(_CC_CONTROL_ON);\
                                                            }\
                                                            else if((TypeCPcbPort) == _PCB_P0_TYPE_C_PORT)\
                                                            {\
                                                                SET_TC1_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                            }\
                                                            else\
                                                            {\
                                                                SET_TC1_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                            }\
                                                        }

#define PCB_D0_CC_VBUS_SWITCH_CONTROL(TypeCEmbeddedPort)\
                                                        {\
                                                            if((TypeCEmbeddedPort) == _EMBEDDED_TYPE_C_0)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_0(_CC_CONTROL_ON);\
                                                                SET_TC1_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                            }\
                                                            else if((TypeCEmbeddedPort) == _EMBEDDED_TYPE_C_1)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_0(_CC_CONTROL_ON);\
                                                            }\
                                                            else\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_0(_CC_CONTROL_OFF);\
                                                            }\
                                                        }

#define PCB_D1_CC_VBUS_SWITCH_CONTROL(TypeCEmbeddedPort)\
                                                        {\
                                                            if((TypeCEmbeddedPort) == _EMBEDDED_TYPE_C_0)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_1(_CC_CONTROL_ON);\
                                                                SET_TC1_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                            }\
                                                            else if((TypeCEmbeddedPort) == _EMBEDDED_TYPE_C_1)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_1(_CC_CONTROL_ON);\
                                                            }\
                                                            else\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_1(_CC_CONTROL_OFF);\
                                                            }\
                                                        }

#define PCB_DPTX_CC_VBUS_SWITCH_CONTROL(TypeCEmbeddedPort)\
                                                        {\
                                                            if((TypeCEmbeddedPort) == _EMBEDDED_TYPE_C_0)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_2(_CC_CONTROL_ON);\
                                                                SET_TC1_CC_SWITCH_CONTROL_2(_CC_CONTROL_OFF);\
                                                            }\
                                                            else if((TypeCEmbeddedPort) == _EMBEDDED_TYPE_C_1)\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_2(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_2(_CC_CONTROL_ON);\
                                                            }\
                                                            else\
                                                            {\
                                                                SET_TC0_CC_SWITCH_CONTROL_2(_CC_CONTROL_OFF);\
                                                                SET_TC1_CC_SWITCH_CONTROL_2(_CC_CONTROL_OFF);\
                                                            }\
                                                        }


//////////////////////
// DPTX Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of DPTX Power Control
//-----------------------------------------------
#define SET_P0_DPTX_POWER(x)                            {SET_GPIO_PIN_EMPTY(x);}

#define _P0_DPTX_POWER_ON                               1
#define _P0_DPTX_POWER_OFF                              0

#define PCB_P0_DPTX_POWER(x)                            {\
                                                             SET_P0_DPTX_POWER(x);\
                                                        }


/////////////////
// Audio Macro //
/////////////////

//-----------------------------------------------
// Macro of PCB Audio Headphone Connect
//-----------------------------------------------
#define GET_AUDIO_DETECT()                              (GET_GPIO_PIN_EMPTY()) // Audio Headphone GPI Detec PIN

#define _AUDIO_CONNECT                                  1                      // Audio Headphone Connect
#define _AUDIO_DISCONNECT                               0                      // Audio Headphone Dis-Connect

#define PCB_AUDIO_DETECT()                              (GET_AUDIO_DETECT())   // Audio Headphone Detect


//-----------------------------------------------
// Macro of PCB Audio AMP Control
//-----------------------------------------------
#define SET_PCBAMPMUTECONTROL(x)                        {SET_GPIO_PIN_EMPTY(x);}

#define _AMP_MUTE_ON                                    0
#define _AMP_MUTE_OFF                                   1

#define PCB_AMP_MUTE(x)                                 {\
                                                            SET_PCBAMPMUTECONTROL(x);\
                                                        }


/////////////////
// DP Cable ID //
/////////////////

//--------------------------------------------------
// Macro of DP Cable ID Detect Setting
//--------------------------------------------------
#define PCB_DP_UHBR_D0_CABLE_ID_DETECT_ADC_PIN()        (GET_SARADC_EMPTY_VALUE())

#define PCB_DP_UHBR_D1_CABLE_ID_DETECT_ADC_PIN()        (GET_SARADC_EMPTY_VALUE())

#define PCB_DP_UHBR_D2_CABLE_ID_DETECT_ADC_PIN()        (GET_SARADC_EMPTY_VALUE())

//--------------------------------------------------
// Macro of DP Cable ID Switch Port Control
//--------------------------------------------------
#define SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_0(x)        {SET_GPIO_PIN_EMPTY(x);}
#define SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_1(x)        {SET_GPIO_PIN_EMPTY(x);}

#define _DP_UHBR_CABLE_ID_CONTROL_ON                    1
#define _DP_UHBR_CABLE_ID_CONTROL_OFF                   0

#define _DP_UHBR_CABLE_ID_SWITCH_PORT_DELAY_TIME        2 // Unit: ms

#define PCB_DP_UHBR_CABLE_ID_SWITCH_PORT_CONTROL(DpInputPort)\
                                                        {\
                                                            if((DpInputPort) == _D0_INPUT_PORT)\
                                                            {\
                                                                SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_0(_DP_UHBR_CABLE_ID_CONTROL_ON);\
                                                                SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_1(_DP_UHBR_CABLE_ID_CONTROL_OFF);\
                                                            }\
                                                            else if((DpInputPort) == _D1_INPUT_PORT)\
                                                            {\
                                                                SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_0(_DP_UHBR_CABLE_ID_CONTROL_OFF);\
                                                                SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_1(_DP_UHBR_CABLE_ID_CONTROL_ON);\
                                                            }\
                                                            else if((DpInputPort) == _D2_INPUT_PORT)\
                                                            {\
                                                                SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_0(_DP_UHBR_CABLE_ID_CONTROL_ON);\
                                                                SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_1(_DP_UHBR_CABLE_ID_CONTROL_ON);\
                                                            }\
                                                            else\
                                                            {\
                                                                SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_0(_DP_UHBR_CABLE_ID_CONTROL_OFF);\
                                                                SET_DP_UHBR_CABLE_ID_SWITCH_CONTROL_1(_DP_UHBR_CABLE_ID_CONTROL_OFF);\
                                                            }\
                                                        }

//--------------------------------------------------
// Macro of DP Cable ID ADC Capacitor Time
//--------------------------------------------------
#define _DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME     300 // Unit: us(50 ~ 1000), 6* tau = 141.2us for Rp = 680kOhm, Rd = 100kOhm, C = 270pF


////////////////////
// ADC Detect Int //
////////////////////

//-----------------------------------------------
// Macro of Int Detected By ADC Support
//-----------------------------------------------
#define _ADC_DETECT_INT_BY_ADC_CHANNEL                  _ADC_DET_INT_ADC_MAPPING_NONE
#define _ADC_DETECT_INT_BY_ADC_THRESHOLD                25 // Unit: %

//-----------------------------------------------
// Macro of ADC Int Trigger GPIO Control
//-----------------------------------------------
#define SET_ADC_INTERRUPT_CONTROL_PIN(x)                {SET_GPIO_PIN_EMPTY(x);}

#define _ADC_INTERRUPT_CONTROL_PIN_ON                   1
#define _ADC_INTERRUPT_CONTROL_PIN_OFF                  0

#define PCB_ADC_INTERRUPT_CONTROL(x)                    {\
                                                            SET_ADC_INTERRUPT_CONTROL_PIN(x);\
                                                        }

#endif // End of #if(_PCB_TYPE == _RL6952_BGA4L_PCB_LVDS_EXAMPLE)
