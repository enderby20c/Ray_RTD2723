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
// ID Code      : Pcb_Deprecated_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_MAX_HDMI_EDID_COUNT                         1
#define _D0_HDMI_VERSION                                _HDMI_VERSION_2_0
#define _D0_HDMI_LINK_CLK_RATE                          _HDMI_LINK_SPEED_600MHZ
#define _D0_HDMI_MAIN_LINK_LANES                        _HDMI_THREE_LANE

#define _D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF

// For TCPM Port Controller
#define _D1_TYPE_C_TCPM_TCPC_TYPE                       _TCPC_NONE
#define _D1_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR             0x00
#define _D1_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC             _OFF
#define _D1_TYPE_C_TCPM_OVP_UVP_SUPPORT                 _OFF
#define _D1_TYPE_C_TCPM_OVP_THRESHOLD                   130
#define _D1_TYPE_C_TCPM_UVP_THRESHOLD                   66

//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#define _D2_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF

// For TCPM Port Controller
#define _D2_TYPE_C_TCPM_TCPC_TYPE                       _TCPC_NONE
#define _D2_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR             0x00
#define _D2_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC             _OFF
#define _D2_TYPE_C_TCPM_OVP_UVP_SUPPORT                 _OFF
#define _D2_TYPE_C_TCPM_OVP_THRESHOLD                   130
#define _D2_TYPE_C_TCPM_UVP_THRESHOLD                   66

//--------------------------------------------------
// D5 Input Port
//--------------------------------------------------
#define _D5_INPUT_PORT_TYPE                             _D5_NO_PORT
#define _D5_DDC_CHANNEL_SEL                             _NO_DDC
#define _D5_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#define _D5_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#define _D5_MAX_HDMI_EDID_COUNT                         1

#define _D5_HDMI_VERSION                                _HDMI_VERSION_2_0
#define _D5_HDMI_LINK_CLK_RATE                          _HDMI_LINK_SPEED_340MHZ
#define _D5_HDMI_MAIN_LINK_LANES                        _HDMI_THREE_LANE

#define _D5_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF

//--------------------------------------------------
// D6 Input Port
//--------------------------------------------------
#define _D6_INPUT_PORT_TYPE                             _D6_NO_PORT
#define _D6_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#define _D6_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#define _D6_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _D6_DP_LINK_CLK_RATE                            _DP_HIGH_SPEED2_540MHZ
#define _D6_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE
#define _D6_INPUT_PORT_SWITCH_FROM                      _SWITCH_NONE

#define _D6_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _D5_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#define _D6_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_7                        _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_8                        _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_9                        _NO_INPUT_PORT


///////////////////////
// Output Port Config //
///////////////////////

//--------------------------------------------------
// P0 Output Port
//--------------------------------------------------
#define _P0_EDID_SIZE                                   _EDID_SIZE_NONE
#define _P0_PCB_IIC                                     _NO_IIC_PIN

// For DP Repeater
#define _P0_DP_REPEATER_TYPE                            _DP_REPEATER_NONE
#define _P0_DP_REPEATER_SLAVE_ADDR                      0x00
#define _P0_DP_REPEATER_IIC                             _NO_IIC_PIN

// For USB
#define _P0_USB_HUB_TYPE                                _USB_NONE
#define _P0_USB_SPEED                                   _USB_BILLBOARD_ONLY
#define _P0_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_NONE

// For Embedded Port Controller
#define _P0_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_NOT_SUPPORT
#define _P0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#define _P0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF

// For Type-C Embedded Port Controller PMIC
#define _P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF

// For TCPM Port Controller
#define _P0_TYPE_C_TCPM_TCPC_TYPE                       _TCPC_NONE
#define _P0_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR             0x00
#define _P0_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC             _OFF
#define _P0_TYPE_C_TCPM_OVP_UVP_SUPPORT                 _OFF
#define _P0_TYPE_C_TCPM_OVP_THRESHOLD                   130
#define _P0_TYPE_C_TCPM_UVP_THRESHOLD                   66

//--------------------------------------------------
// P1 Output Port
//--------------------------------------------------
#define _P1_OUTPUT_TYPE                                 _P1_NO_PORT
#define _P1_EDID_SIZE                                   _EDID_SIZE_NONE
#define _P1_PCB_IIC                                     _NO_IIC_PIN

// For DP
#define _P1_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _P1_DP_LINK_CLK_RATE                            _DP_HIGH_SPEED2_540MHZ
#define _P1_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE

// For DP Repeater
#define _P1_DP_REPEATER_TYPE                            _DP_REPEATER_NONE
#define _P1_DP_REPEATER_SLAVE_ADDR                      0x00
#define _P1_DP_REPEATER_IIC                             _NO_IIC_PIN

// For Connector Type-C
#define _P1_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE

// For USB
#define _P1_USB_HUB_TYPE                                _USB_NONE
#define _P1_USB_SPEED                                   _USB_BILLBOARD_ONLY
#define _P1_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_NONE
#define _P1_USB_HUB_RTS_SLAVE_ADDR                      0x00
#define _P1_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN

// For RTS Port Controller / Hub
#define _P1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00

// For RTS / User Port Controller
#define _P1_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#define _P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#define _P1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#define _P1_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#define _P1_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#define _P1_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF

// For Embedded Port Controller
#define _P1_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#define _P1_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#define _P1_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#define _P1_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_NOT_SUPPORT
#define _P1_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#define _P1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#define _P1_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#define _P1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#define _P1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#define _P1_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#define _P1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _OFF

// For Type-C Embedded Port Controller PMIC
#define _P1_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#define _P1_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#define _P1_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#define _P1_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P1_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#define _P1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#define _P1_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#define _P1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#define _P1_TYPE_C_PMIC_FW_OVP_THRESHOLD                130
#define _P1_TYPE_C_PMIC_FW_UVP_THRESHOLD                66
#define _P1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#define _P1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            100 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _P1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#define _P1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#define _P1_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF
#define _P1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#define _P1_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#define _P1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms

// For TCPM Port Controller
#define _P1_TYPE_C_TCPM_TCPC_TYPE                       _TCPC_NONE
#define _P1_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR             0x00
#define _P1_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC             _OFF
#define _P1_TYPE_C_TCPM_OVP_UVP_SUPPORT                 _OFF
#define _P1_TYPE_C_TCPM_OVP_THRESHOLD                   130
#define _P1_TYPE_C_TCPM_UVP_THRESHOLD                   66

//--------------------------------------------------
// P2 Output Port
//--------------------------------------------------
#define _P2_OUTPUT_TYPE                                 _P2_NO_PORT
#define _P2_EDID_SIZE                                   _EDID_SIZE_NONE
#define _P2_PCB_IIC                                     _NO_IIC_PIN

// For DP
#define _P2_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _P2_DP_LINK_CLK_RATE                            _DP_HIGH_SPEED2_540MHZ
#define _P2_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE

// For DP Repeater
#define _P2_DP_REPEATER_TYPE                            _DP_REPEATER_NONE
#define _P2_DP_REPEATER_SLAVE_ADDR                      0x00
#define _P2_DP_REPEATER_IIC                             _NO_IIC_PIN

// For DP Connector Type-C
#define _P2_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE

// For USB
#define _P2_USB_HUB_TYPE                                _USB_NONE
#define _P2_USB_SPEED                                   _USB_BILLBOARD_ONLY
#define _P2_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_NONE
#define _P2_USB_HUB_RTS_SLAVE_ADDR                      0x00
#define _P2_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN

// For RTS Port Controller / Hub
#define _P2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00

// For RTS / User Port Controller
#define _P2_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#define _P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#define _P2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#define _P2_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#define _P2_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#define _P2_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF

// For Embedded Port Controller
#define _P2_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#define _P2_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#define _P2_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#define _P2_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_NOT_SUPPORT
#define _P2_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#define _P2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#define _P2_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#define _P2_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#define _P2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#define _P2_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#define _P2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _OFF

// For Type-C Embedded Port Controller PMIC
#define _P2_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#define _P2_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#define _P2_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#define _P2_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P2_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P2_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#define _P2_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#define _P2_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#define _P2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#define _P2_TYPE_C_PMIC_FW_OVP_THRESHOLD                130
#define _P2_TYPE_C_PMIC_FW_UVP_THRESHOLD                66
#define _P2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#define _P2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            100 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _P2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#define _P2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#define _P2_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF
#define _P2_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#define _P2_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#define _P2_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms

// For TCPM Port Controller
#define _P2_TYPE_C_TCPM_TCPC_TYPE                       _TCPC_NONE
#define _P2_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR             0x00
#define _P2_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC             _OFF
#define _P2_TYPE_C_TCPM_OVP_UVP_SUPPORT                 _OFF
#define _P2_TYPE_C_TCPM_OVP_THRESHOLD                   130
#define _P2_TYPE_C_TCPM_UVP_THRESHOLD                   66

//--------------------------------------------------
// P3 Output Port
//--------------------------------------------------
#define _P3_OUTPUT_TYPE                                 _P3_NO_PORT
#define _P3_EDID_SIZE                                   _EDID_SIZE_NONE
#define _P3_PCB_IIC                                     _NO_IIC_PIN

// For DP
#define _P3_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _P3_DP_LINK_CLK_RATE                            _DP_HIGH_SPEED2_540MHZ
#define _P3_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE

// For DP Repeater
#define _P3_DP_REPEATER_TYPE                            _DP_REPEATER_NONE
#define _P3_DP_REPEATER_SLAVE_ADDR                      0x00
#define _P3_DP_REPEATER_IIC                             _NO_IIC_PIN

// For Connector Type-C
#define _P3_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE

// For USB
#define _P3_USB_HUB_TYPE                                _USB_NONE
#define _P3_USB_SPEED                                   _USB_BILLBOARD_ONLY
#define _P3_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_NONE
#define _P3_USB_HUB_RTS_SLAVE_ADDR                      0x00
#define _P3_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN

// For RTS Port Controller / Hub
#define _P3_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00

// For RTS / User Port Controller
#define _P3_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#define _P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#define _P3_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#define _P3_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#define _P3_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#define _P3_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF

// For Embedded Port Controller
#define _P3_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#define _P3_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#define _P3_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#define _P3_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_NOT_SUPPORT
#define _P3_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#define _P3_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#define _P3_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#define _P3_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#define _P3_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#define _P3_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#define _P3_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _OFF

// For Type-C Embedded Port Controller PMIC
#define _P3_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#define _P3_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#define _P3_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#define _P3_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P3_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P3_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#define _P3_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#define _P3_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#define _P3_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#define _P3_TYPE_C_PMIC_FW_OVP_THRESHOLD                130
#define _P3_TYPE_C_PMIC_FW_UVP_THRESHOLD                66
#define _P3_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#define _P3_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            100 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _P3_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#define _P3_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#define _P3_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF
#define _P3_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#define _P3_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#define _P3_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms

// For TCPM Port Controller
#define _P3_TYPE_C_TCPM_TCPC_TYPE                       _TCPC_NONE
#define _P3_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR             0x00
#define _P3_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC             _OFF
#define _P3_TYPE_C_TCPM_OVP_UVP_SUPPORT                 _OFF
#define _P3_TYPE_C_TCPM_OVP_THRESHOLD                   130
#define _P3_TYPE_C_TCPM_UVP_THRESHOLD                   66

//--------------------------------------------------
// P4 Output Port
//--------------------------------------------------
#define _P4_OUTPUT_TYPE                                 _P4_NO_PORT
#define _P4_EDID_SIZE                                   _EDID_SIZE_NONE
#define _P4_PCB_IIC                                     _NO_IIC_PIN

// For DP
#define _P4_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#define _P4_DP_LINK_CLK_RATE                            _DP_HIGH_SPEED2_540MHZ
#define _P4_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE

// For DP Repeater
#define _P4_DP_REPEATER_TYPE                            _DP_REPEATER_NONE
#define _P4_DP_REPEATER_SLAVE_ADDR                      0x00
#define _P4_DP_REPEATER_IIC                             _NO_IIC_PIN

// For DP Connector Type-C
#define _P4_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE

// For USB
#define _P4_USB_HUB_TYPE                                _USB_NONE
#define _P4_USB_SPEED                                   _USB_BILLBOARD_ONLY
#define _P4_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_NONE
#define _P4_USB_HUB_RTS_SLAVE_ADDR                      0x00
#define _P4_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN

// For RTS Port Controller / Hub
#define _P4_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00

// For RTS / User Port Controller
#define _P4_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#define _P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#define _P4_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#define _P4_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#define _P4_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#define _P4_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF

// For Embedded Port Controller
#define _P4_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#define _P4_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#define _P4_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#define _P4_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_NOT_SUPPORT
#define _P4_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#define _P4_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#define _P4_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#define _P4_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#define _P4_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#define _P4_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#define _P4_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _OFF

// For Type-C Embedded Port Controller PMIC
#define _P4_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#define _P4_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#define _P4_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#define _P4_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P4_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _P4_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#define _P4_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#define _P4_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#define _P4_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#define _P4_TYPE_C_PMIC_FW_OVP_THRESHOLD                130
#define _P4_TYPE_C_PMIC_FW_UVP_THRESHOLD                66
#define _P4_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#define _P4_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            100 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _P4_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#define _P4_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#define _P4_TYPE_C_PMIC_VOLTAGE_COMPENSATION            _OFF
#define _P4_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#define _P4_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#define _P4_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms

// For TCPM Port Controller
#define _P4_TYPE_C_TCPM_TCPC_TYPE                       _TCPC_NONE
#define _P4_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR             0x00
#define _P4_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC             _OFF
#define _P4_TYPE_C_TCPM_OVP_UVP_SUPPORT                 _OFF
#define _P4_TYPE_C_TCPM_OVP_THRESHOLD                   130
#define _P4_TYPE_C_TCPM_UVP_THRESHOLD                   66


/////////////////////////
// Adaptor Port Config //
/////////////////////////

//--------------------------------------------------
// Adaptor Port
//--------------------------------------------------
#define _ADAPTOR_CONNECTOR_TYPE                         _ADAPTOR_CONNECTOR_NORMAL

// For DP Connector Type-C
#define _ADAPTOR_TYPE_C_PORT_CTRL_TYPE                  _PORT_CTRL_NONE

// For USB
#define _ADAPTOR_TYPE_C_USB_TYPE                        _USB_NONE
#define _ADAPTOR_TYPE_C_BILLBOARD_TYPE                  _BILLBOARD_NONE

// For Port Controller RTS
#define _ADAPTOR_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR        0x00
#define _ADAPTOR_TYPE_C_RTS_SMBUS_IIC                   _NO_IIC_PIN

// For RTS / User Port Controller
#define _ADAPTOR_TYPE_C_EXT_PIN_E_AUXPN_SWAP            _SWAP_BY_SCALER
#define _ADAPTOR_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION   _SWAP_BY_PORT_CTRL
#define _ADAPTOR_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E         _SWAP_BY_SCALER
#define _ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#define _ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT       _EXT_PORT_CTRL_NOT_EXIST
#define _ADAPTOR_TYPE_C_EXT_PD3_1_EPR_SUPPORT           _OFF

// For Embedded Port Controller
#define _ADAPTOR_TYPE_C_EMB_PORT_ROLE                   _TYPE_C_PORT_SNK_ONLY
#define _ADAPTOR_TYPE_C_EMB_DRP_PREFER                  _TYPE_C_DRP_NO_PREFERENCE
#define _ADAPTOR_TYPE_C_EMB_SRC_DEF_CUR                 _TYPE_C_SRC_DEF_3P0A
#define _ADAPTOR_TYPE_C_EMB_CONNECTOR_TYPE              _TYPE_C_PORT_RECEPTACLE
#define _ADAPTOR_TYPE_C_EMB_DEAD_BATTERY_SUPPORT        _OFF
#define _ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT             _OFF
#define _ADAPTOR_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF  _OFF
#define _ADAPTOR_TYPE_C_EMB_PD3_FRSWAP_SUPPORT          _OFF
#define _ADAPTOR_TYPE_C_EMB_PD3_1_EPR_SUPPORT           _OFF
#define _ADAPTOR_TYPE_C_EMB_DP_ALT_MODE_SUPPORT         _OFF

// For Type-C Embedded Port Controller PMIC
#define _ADAPTOR_TYPE_C_PMIC_TYPE                       _PMIC_NONE
#define _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS              0x00
#define _ADAPTOR_TYPE_C_PMIC_IIC                        _PMIC_NO_IIC_PIN
#define _ADAPTOR_TYPE_C_PMIC_IOUT_ADC_CHANNEL           _TYPE_C_PMIC_ADC_MAPPING_NONE
#define _ADAPTOR_TYPE_C_PMIC_IOUT_MAX_CURRENT           1320 // unit: 10mA
#define _ADAPTOR_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT         _OFF
#define _ADAPTOR_TYPE_C_PMIC_FW_OVP_THRESHOLD           130
#define _ADAPTOR_TYPE_C_PMIC_FW_UVP_THRESHOLD           66
#define _ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD      _TYPE_C_PMIC_FW_OCP_NONE
#define _ADAPTOR_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE       100 // unit: %, should multiply with PMIC setting current to get the real OCP value
#define _ADAPTOR_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN      0 // unit: ms, Maximum value: 61000
#define _ADAPTOR_TYPE_C_PMIC_INT_PIN_CHECK_METHOD       _TYPE_C_PMIC_INT_PIN_NONE
#define _ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION       _OFF
#define _ADAPTOR_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT     _OFF
#define _ADAPTOR_TYPE_C_PMIC_SAFETY_POWER_LIMIT         100 // W
#define _ADAPTOR_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN      1000 // ms

// For TCPM Port Controller
#define _ADAPTOR_TYPE_C_TCPM_TCPC_TYPE                  _TCPC_NONE
#define _ADAPTOR_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR        0x00
#define _ADAPTOR_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC        _OFF
#define _ADAPTOR_TYPE_C_TCPM_OVP_UVP_SUPPORT            _OFF
#define _ADAPTOR_TYPE_C_TCPM_OVP_THRESHOLD              130
#define _ADAPTOR_TYPE_C_TCPM_UVP_THRESHOLD              66


///////////////
// TMDS Port //
///////////////

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#define _D0_TMDS_BR_SWAP                                _OFF
#define _D0_TMDS_PN_SWAP                                _OFF

#define _D5_TMDS_BR_SWAP                                _OFF
#define _D5_TMDS_PN_SWAP                                _ON

#define _D1_EDID_EXTERNAL_EEPROM_MAX_SIZE               _EDID_EEPROM_SIZE_NONE
#define _D2_EDID_EXTERNAL_EEPROM_MAX_SIZE               _EDID_EEPROM_SIZE_NONE

////////////////////
// DP Power Macro //
////////////////////

//-----------------------------------------------
// Macro of MyDP Power Control
//-----------------------------------------------
#define _MYDP_5V_POWER_ON                               1
#define _MYDP_5V_POWER_OFF                              0

#define PCB_D0_MYDP_POWER(x)                            {\
                                                        }

#define PCB_D1_MYDP_POWER(x)                            {\
                                                        }

#define PCB_D6_MYDP_POWER(x)                            {\
                                                        }

//-----------------------------------------------
// Macro of DP1.2 Power Control
//-----------------------------------------------
#define _DP12_33V_POWER_ON                              1
#define _DP12_33V_POWER_OFF                             0

#define PCB_D0_DP12_POWER(x)                            {\
                                                        }

#define PCB_D1_DP12_POWER(x)                            {\
                                                        }

#define PCB_D6_DP12_POWER(x)                            {\
                                                        }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of External Port Controller Power Control
//-----------------------------------------------
#define _P1_PORT_CTRL_POWER_ON                          1
#define _P1_PORT_CTRL_POWER_OFF                         0

#define _P2_PORT_CTRL_POWER_ON                          1
#define _P2_PORT_CTRL_POWER_OFF                         0

#define _P3_PORT_CTRL_POWER_ON                          1
#define _P3_PORT_CTRL_POWER_OFF                         0

#define _P4_PORT_CTRL_POWER_ON                          1
#define _P4_PORT_CTRL_POWER_OFF                         0

#define PCB_P1_PORT_CTRL_POWER(x)                       {\
                                                        }

#define PCB_P2_PORT_CTRL_POWER(x)                       {\
                                                        }

#define PCB_P3_PORT_CTRL_POWER(x)                       {\
                                                        }

#define PCB_P4_PORT_CTRL_POWER(x)                       {\
                                                        }

#define PCB_P1_PORT_CTRL_POWER_STATUS()                 (_P1_PORT_CTRL_POWER_OFF)
#define PCB_P2_PORT_CTRL_POWER_STATUS()                 (_P2_PORT_CTRL_POWER_OFF)
#define PCB_P3_PORT_CTRL_POWER_STATUS()                 (_P3_PORT_CTRL_POWER_OFF)
#define PCB_P4_PORT_CTRL_POWER_STATUS()                 (_P4_PORT_CTRL_POWER_OFF)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define PCB_D0_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                        }

#define PCB_D5_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                        }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define PCB_A1_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#define PCB_A2_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#define PCB_D5_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#define PCB_D6_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D6_DP_SOURCE_POWER()                    (_LOW)

//-----------------------------------------------
// Macro of Type-C Cable Connect
//-----------------------------------------------
// For DP Type-C _Px_DP_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#define PCB_P1_CC_ATTACH()                              (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)
#define PCB_P2_CC_ATTACH()                              (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)
#define PCB_P3_CC_ATTACH()                              (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)
#define PCB_P4_CC_ATTACH()                              (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)
#define PCB_ADAPTOR_CC_ATTACH()                         (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)

// For DP Type-C _Px_DP_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#define PCB_P1_ALT_MODE_READY()                         (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#define PCB_P2_ALT_MODE_READY()                         (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#define PCB_P3_ALT_MODE_READY()                         (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#define PCB_P4_ALT_MODE_READY()                         (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#define PCB_ADAPTOR_ALT_MODE_READY()                    (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define _D5_HOT_PLUG_HIGH                               1
#define _D5_HOT_PLUG_LOW                                0

#define PCB_D5_HOTPLUG(x)                               {\
                                                        }

#define PCB_D5_HOTPLUG_DETECT()                         (_D5_HOT_PLUG_LOW)


//////////////////////////////////////
// DP D0 & D6 External Switch Macro //
//////////////////////////////////////

//-----------------------------------------------
// Macro of Input Port D6 Digital Switch
//-----------------------------------------------
#define _DIGITAL_D6_SWITCH_POWER_ON                     1
#define _DIGITAL_D6_SWITCH_POWER_DOWN                   0

#define PCB_DIGITAL_D6_SWITCH_POWER(x)                  {\
                                                        }

//-----------------------------------------------
// Macro of D6 Switch Lane & Aux_HPD Macro
//-----------------------------------------------
#define _DP_D0_D6_SWITCH_D0                             1
#define _DP_D0_D6_SWITCH_D6                             0

#define PCB_DIGITAL_D0_D6_SWITCH_LANE(x)                {\
                                                        }

#define PCB_DIGITAL_D0_D6_SWITCH_AUX_HPD(x)             {\
                                                        }

/////////////////////////
// D2 PMIC Power Macro //
/////////////////////////

//-----------------------------------------------
// Macro of D2 Pmic Interrupt Detect
//-----------------------------------------------
#define _D2_PMIC_INTERRUPT_ON                           1
#define _D2_PMIC_INTERRUPT_OFF                          0

#define PCB_D2_PMIC_INTERRUPT_DETECT()                  (_D2_PMIC_INTERRUPT_OFF)

//-----------------------------------------------
// Macro of D2 Pmic ALERT Detect
//-----------------------------------------------
#define _D2_PMIC_ALERT_ON                               1
#define _D2_PMIC_ALERT_OFF                              0

#define PCB_D2_PMIC_ALERT_DETECT()                      (_D2_PMIC_ALERT_OFF)


/////////////////////////
// P1 PMIC Power Macro //
/////////////////////////

//-----------------------------------------------
// Macro of P4 Pmic Interrupt Detect
//-----------------------------------------------
#define _P1_PMIC_INTERRUPT_ON                           1
#define _P1_PMIC_INTERRUPT_OFF                          0

#define PCB_P1_PMIC_INTERRUPT_DETECT()                  (_P1_PMIC_INTERRUPT_OFF)

//-----------------------------------------------
// Macro of P1 Pmic ALERT Detect
//-----------------------------------------------
#define _P1_PMIC_ALERT_ON                               1
#define _P1_PMIC_ALERT_OFF                              0

#define PCB_P1_PMIC_ALERT_DETECT()                      (_P1_PMIC_ALERT_OFF)


/////////////////////////
// P2 PMIC Power Macro //
/////////////////////////

//-----------------------------------------------
// Macro of P2 Pmic Interrupt Detect
//-----------------------------------------------
#define _P2_PMIC_INTERRUPT_ON                           1
#define _P2_PMIC_INTERRUPT_OFF                          0

#define PCB_P2_PMIC_INTERRUPT_DETECT()                  (_P2_PMIC_INTERRUPT_OFF)

//-----------------------------------------------
// Macro of P2 Pmic ALERT Detect
//-----------------------------------------------
#define _P2_PMIC_ALERT_ON                               1
#define _P2_PMIC_ALERT_OFF                              0

#define PCB_P2_PMIC_ALERT_DETECT()                      (_P2_PMIC_ALERT_OFF)


/////////////////////////
// P3 PMIC Power Macro //
/////////////////////////

//-----------------------------------------------
// Macro of P3 Pmic Interrupt Detect
//-----------------------------------------------
#define _P3_PMIC_INTERRUPT_ON                           1
#define _P3_PMIC_INTERRUPT_OFF                          0

#define PCB_P3_PMIC_INTERRUPT_DETECT()                  (_P3_PMIC_INTERRUPT_OFF)

//-----------------------------------------------
// Macro of P3 Pmic ALERT Detect
//-----------------------------------------------
#define _P3_PMIC_ALERT_ON                               1
#define _P3_PMIC_ALERT_OFF                              0

#define PCB_P3_PMIC_ALERT_DETECT()                      (_P3_PMIC_ALERT_OFF)


/////////////////////////
// P4 PMIC Power Macro //
/////////////////////////

//-----------------------------------------------
// Macro of P4 Pmic Interrupt Detect
//-----------------------------------------------
#define _P4_PMIC_INTERRUPT_ON                           1
#define _P4_PMIC_INTERRUPT_OFF                          0

#define PCB_P4_PMIC_INTERRUPT_DETECT()                  (_P4_PMIC_INTERRUPT_OFF)

//-----------------------------------------------
// Macro of P4 Pmic ALERT Detect
//-----------------------------------------------
#define _P4_PMIC_ALERT_ON                               1
#define _P4_PMIC_ALERT_OFF                              0

#define PCB_P4_PMIC_ALERT_DETECT()                      (_P4_PMIC_ALERT_OFF)

