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
// ID Code      : RL6952_Pcb_Default.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#ifndef _EXT_XTAL
#define _EXT_XTAL                                       _XTAL14318K
#endif


///////////////
// Debug DDC //
///////////////

//--------------------------------------------------
// Debug DDC Channel
//--------------------------------------------------
#ifndef _PCB_DEBUG_DDC
#define _PCB_DEBUG_DDC                                  _VGA_DDC
#endif

#ifndef _PCB_DEBUG_JTAG
#define _PCB_DEBUG_JTAG                                 _JTAG_SWD_DDC4
#endif


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// A0 Input Port
//--------------------------------------------------
#ifndef _A0_INPUT_PORT_TYPE
#define _A0_INPUT_PORT_TYPE                             _A0_NO_PORT
#endif

#ifndef _A0_EMBEDDED_DDCRAM_MAX_SIZE
#define _A0_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#endif

#ifndef _A0_EMBEDDED_DDCRAM_LOCATION
#define _A0_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#endif

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#ifndef _D0_INPUT_PORT_TYPE
#define _D0_INPUT_PORT_TYPE                             _D0_NO_PORT
#endif

#ifndef _D0_DDC_CHANNEL_SEL
#define _D0_DDC_CHANNEL_SEL                             _NO_DDC
#endif

#ifndef _D0_EMBEDDED_DDCRAM_MAX_SIZE
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#endif

#ifndef _D0_EMBEDDED_DDCRAM_LOCATION
#define _D0_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D0_DP_CONNECTOR_TYPE
#define _D0_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#endif

#ifndef _D0_DP_Z0_IMPEDANCE_OPTION
#define _D0_DP_Z0_IMPEDANCE_OPTION                      _BY_CONNECTOR
#endif

#ifndef _D0_DP_LINK_CLK_RATE
#define _D0_DP_LINK_CLK_RATE                            _DP_HIGH_SPEED3_810MHZ
#endif

#ifndef _D0_DP_MAIN_LINK_LANES
#define _D0_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE
#endif

#ifndef _D0_DP_REDRIVER_TYPE
#define _D0_DP_REDRIVER_TYPE                            _REDRIVER_NONE
#endif

#ifndef _D0_USB_CONNECTOR_TYPE
#define _D0_USB_CONNECTOR_TYPE                          _USB_CONNECTOR_NONE
#endif

#ifndef _D0_USB_HUB_TYPE
#define _D0_USB_HUB_TYPE                                _USB_NONE
#endif

#ifndef _D0_USB_U2_HUB_TRACE_TYPE
#define _D0_USB_U2_HUB_TRACE_TYPE                       _USB_U2_TRACE_DIRECT_TO_HUB
#endif

#ifndef _D0_USB_U3_HUB_TRACE_TYPE
#define _D0_USB_U3_HUB_TRACE_TYPE                       _USB_U3_TRACE_DIRECT_TO_HUB
#endif

#ifndef _D0_USB_SPEED
#define _D0_USB_SPEED                                   _USB_BILLBOARD_ONLY
#endif

#ifndef _D0_USB_LANE
#define _D0_USB_LANE                                    _USB_3_LANE_NONE
#endif

#ifndef _D0_USB_HUB_RTS_SLAVE_ADDR
#define _D0_USB_HUB_RTS_SLAVE_ADDR                      0x00
#endif

#ifndef _D0_USB_RTS_SMBUS_IIC
#define _D0_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN
#endif

#ifndef _D0_USB_UFP_RX_OOBS_VTH
#define _D0_USB_UFP_RX_OOBS_VTH                         _USB_UFP_RX_OOBS_VTH_LEVEL_3
#endif

#ifndef _D0_TYPE_C_PORT_CTRL_TYPE
#define _D0_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE
#endif

#ifndef _D0_TYPE_C_BILLBOARD_TYPE
#define _D0_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_NONE
#endif

#ifndef _D0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR
#define _D0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00
#endif

#ifndef _D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP
#define _D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#endif

#ifndef _D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION
#define _D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#endif

#ifndef _D0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E
#define _D0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#endif

#ifndef _D0_TYPE_C_EXT_CC_ATTACH_DETECT
#define _D0_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#endif

#ifndef _D0_TYPE_C_EXT_ALT_MODE_READY_DETECT
#define _D0_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#endif

#ifndef _D0_TYPE_C_EXT_PD3_1_EPR_SUPPORT
#define _D0_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF
#endif

#ifndef _D0_TYPE_C_EMB_PORT_ROLE
#define _D0_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#endif

#ifndef _D0_TYPE_C_EMB_DRP_PREFER
#define _D0_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#endif

#ifndef _D0_TYPE_C_EMB_SRC_DEF_CUR
#define _D0_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#endif

#ifndef _D0_TYPE_C_EMB_USB_ROLE
#define _D0_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_NOT_SUPPORT
#endif

#ifndef _D0_TYPE_C_EMB_CONNECTOR_TYPE
#define _D0_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#endif

#ifndef _D0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT
#define _D0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#endif

#ifndef _D0_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _D0_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#endif

#ifndef _D0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF
#define _D0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#endif

#ifndef _D0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _D0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#endif

#ifndef _D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#endif

#ifndef _D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _OFF
#endif

#ifndef _D0_TYPE_C_TCPM_TCPC_TYPE
#define _D0_TYPE_C_TCPM_TCPC_TYPE                       _TCPC_NONE
#endif

#ifndef _D0_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR
#define _D0_TYPE_C_TCPM_TCPC_I2C_SLAVE_ADDR             0x00
#endif

#ifndef _D0_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC
#define _D0_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC             _OFF
#endif

#ifndef _D0_TYPE_C_TCPM_OVP_UVP_SUPPORT
#define _D0_TYPE_C_TCPM_OVP_UVP_SUPPORT                 _OFF
#endif

#ifndef _D0_TYPE_C_TCPM_OVP_THRESHOLD
#define _D0_TYPE_C_TCPM_OVP_THRESHOLD                   130
#endif

#ifndef _D0_TYPE_C_TCPM_UVP_THRESHOLD
#define _D0_TYPE_C_TCPM_UVP_THRESHOLD                   66
#endif

#ifndef _D0_TYPE_C_PMIC_TYPE
#define _D0_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#endif

#ifndef _D0_TYPE_C_PMIC_SLAVE_ADDRESS
#define _D0_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#endif

#ifndef _D0_TYPE_C_PMIC_IIC
#define _D0_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#endif

#ifndef _D0_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _D0_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0
#endif

#ifndef _D0_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _D0_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#endif

#ifndef _D0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _D0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#endif

#ifndef _D0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _D0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#endif

#ifndef _D0_TYPE_C_PMIC_IOUT_MAX_CURRENT
#define _D0_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#endif

#ifndef _D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _D0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#endif

#ifndef _D0_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _D0_TYPE_C_PMIC_FW_OVP_THRESHOLD                130 // Unit: %
#endif

#ifndef _D0_TYPE_C_PMIC_FW_UVP_THRESHOLD
#define _D0_TYPE_C_PMIC_FW_UVP_THRESHOLD                66 // Unit: %
#endif

#ifndef _D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#endif

#ifndef _D0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _D0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            0 // unit: %, should multiply with PMIC setting current to get the real OCP value
#endif

#ifndef _D0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN
#define _D0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#endif

#ifndef _D0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _D0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#endif

#ifndef _D0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _D0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#endif

#ifndef _D0_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _D0_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#endif

#ifndef _D0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN
#define _D0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms
#endif

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#ifndef _D1_INPUT_PORT_TYPE
#define _D1_INPUT_PORT_TYPE                             _D1_NO_PORT
#endif

#ifndef _D1_DDC_CHANNEL_SEL
#define _D1_DDC_CHANNEL_SEL                             _NO_DDC
#endif

#ifndef _D1_EMBEDDED_DDCRAM_MAX_SIZE
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#endif

#ifndef _D1_EMBEDDED_DDCRAM_LOCATION
#define _D1_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D1_DP_CONNECTOR_TYPE
#define _D1_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#endif

#ifndef _D1_DP_Z0_IMPEDANCE_OPTION
#define _D1_DP_Z0_IMPEDANCE_OPTION                      _BY_CONNECTOR
#endif

#ifndef _D1_DP_LINK_CLK_RATE
#define _D1_DP_LINK_CLK_RATE                            _DP_HIGH_SPEED3_810MHZ
#endif

#ifndef _D1_DP_MAIN_LINK_LANES
#define _D1_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE
#endif

#ifndef _D1_DP_REDRIVER_TYPE
#define _D1_DP_REDRIVER_TYPE                            _REDRIVER_NONE
#endif

#ifndef _D1_USB_CONNECTOR_TYPE
#define _D1_USB_CONNECTOR_TYPE                          _USB_CONNECTOR_NONE
#endif

#ifndef _D1_USB_HUB_TYPE
#define _D1_USB_HUB_TYPE                                _USB_NONE
#endif

#ifndef _D1_USB_U2_HUB_TRACE_TYPE
#define _D1_USB_U2_HUB_TRACE_TYPE                       _USB_U2_TRACE_DIRECT_TO_HUB
#endif

#ifndef _D1_USB_U3_HUB_TRACE_TYPE
#define _D1_USB_U3_HUB_TRACE_TYPE                       _USB_U3_TRACE_DIRECT_TO_HUB
#endif

#ifndef _D1_USB_SPEED
#define _D1_USB_SPEED                                   _USB_BILLBOARD_ONLY
#endif

#ifndef _D1_USB_LANE
#define _D1_USB_LANE                                    _USB_3_LANE_NONE
#endif

#ifndef _D1_USB_HUB_RTS_SLAVE_ADDR
#define _D1_USB_HUB_RTS_SLAVE_ADDR                      0x00
#endif

#ifndef _D1_USB_RTS_SMBUS_IIC
#define _D1_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN
#endif

#ifndef _D1_USB_UFP_RX_OOBS_VTH
#define _D1_USB_UFP_RX_OOBS_VTH                         _USB_UFP_RX_OOBS_VTH_LEVEL_3
#endif

#ifndef _D1_TYPE_C_PORT_CTRL_TYPE
#define _D1_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE
#endif

#ifndef _D1_TYPE_C_BILLBOARD_TYPE
#define _D1_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_NONE
#endif

#ifndef _D1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR
#define _D1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00
#endif

#ifndef _D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP
#define _D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#endif

#ifndef _D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION
#define _D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#endif

#ifndef _D1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E
#define _D1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#endif

#ifndef _D1_TYPE_C_EXT_CC_ATTACH_DETECT
#define _D1_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#endif

#ifndef _D1_TYPE_C_EXT_ALT_MODE_READY_DETECT
#define _D1_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#endif

#ifndef _D1_TYPE_C_EXT_PD3_1_EPR_SUPPORT
#define _D1_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF
#endif

#ifndef _D1_TYPE_C_EMB_PORT_ROLE
#define _D1_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#endif

#ifndef _D1_TYPE_C_EMB_DRP_PREFER
#define _D1_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#endif

#ifndef _D1_TYPE_C_EMB_SRC_DEF_CUR
#define _D1_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#endif

#ifndef _D1_TYPE_C_EMB_USB_ROLE
#define _D1_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_NOT_SUPPORT
#endif

#ifndef _D1_TYPE_C_EMB_CONNECTOR_TYPE
#define _D1_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#endif

#ifndef _D1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT
#define _D1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#endif

#ifndef _D1_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _D1_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#endif

#ifndef _D1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF
#define _D1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#endif

#ifndef _D1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _D1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#endif

#ifndef _D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#endif

#ifndef _D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _OFF
#endif

#ifndef _D1_TYPE_C_PMIC_TYPE
#define _D1_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#endif

#ifndef _D1_TYPE_C_PMIC_SLAVE_ADDRESS
#define _D1_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#endif

#ifndef _D1_TYPE_C_PMIC_IIC
#define _D1_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#endif

#ifndef _D1_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _D1_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1
#endif

#ifndef _D1_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _D1_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#endif

#ifndef _D1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _D1_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#endif

#ifndef _D1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _D1_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#endif

#ifndef _D1_TYPE_C_PMIC_IOUT_MAX_CURRENT
#define _D1_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#endif

#ifndef _D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _D1_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#endif

#ifndef _D1_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _D1_TYPE_C_PMIC_FW_OVP_THRESHOLD                130 // Unit: %
#endif

#ifndef _D1_TYPE_C_PMIC_FW_UVP_THRESHOLD
#define _D1_TYPE_C_PMIC_FW_UVP_THRESHOLD                66 // Unit: %
#endif

#ifndef _D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#endif

#ifndef _D1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _D1_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            0 // unit: %, should multiply with PMIC setting current to get the real OCP value
#endif

#ifndef _D1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN
#define _D1_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#endif

#ifndef _D1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _D1_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#endif

#ifndef _D1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _D1_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#endif

#ifndef _D1_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _D1_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#endif

#ifndef _D1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN
#define _D1_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms
#endif

#ifndef _D1_MAX_HDMI_EDID_COUNT
#define _D1_MAX_HDMI_EDID_COUNT                         1
#endif

#ifndef _D1_HDMI_ARC_TX_PIN
#define _D1_HDMI_ARC_TX_PIN                             _HDMI_ARC_TX_NONE
#endif

#ifndef _D1_HDMI_MAC_TYPE
#define _D1_HDMI_MAC_TYPE                               _HDMI_MAC_TMDS
#endif

#ifndef _D1_HDMI_LINK_CLK_RATE
#define _D1_HDMI_LINK_CLK_RATE                          _HDMI_LINK_SPEED_600MHZ
#endif

#ifndef _D1_HDMI_MAIN_LINK_LANES
#define _D1_HDMI_MAIN_LINK_LANES                        _HDMI_THREE_LANE
#endif

//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#ifndef _D2_INPUT_PORT_TYPE
#define _D2_INPUT_PORT_TYPE                             _D2_NO_PORT
#endif

#ifndef _D2_DDC_CHANNEL_SEL
#define _D2_DDC_CHANNEL_SEL                             _NO_DDC
#endif

#ifndef _D2_EMBEDDED_DDCRAM_MAX_SIZE
#define _D2_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#endif

#ifndef _D2_EMBEDDED_DDCRAM_LOCATION
#define _D2_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D2_DP_CONNECTOR_TYPE
#define _D2_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#endif

#ifndef _D2_DP_Z0_IMPEDANCE_OPTION
#define _D2_DP_Z0_IMPEDANCE_OPTION                      _BY_CONNECTOR
#endif

#ifndef _D2_DP_LINK_CLK_RATE
#define _D2_DP_LINK_CLK_RATE                            _DP_HIGH_SPEED3_810MHZ
#endif

#ifndef _D2_DP_MAIN_LINK_LANES
#define _D2_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE
#endif

#ifndef _D2_DP_REDRIVER_TYPE
#define _D2_DP_REDRIVER_TYPE                            _REDRIVER_NONE
#endif

#ifndef _D2_USB_CONNECTOR_TYPE
#define _D2_USB_CONNECTOR_TYPE                          _USB_CONNECTOR_NONE
#endif

#ifndef _D2_USB_HUB_TYPE
#define _D2_USB_HUB_TYPE                                _USB_NONE
#endif

#ifndef _D2_USB_U2_HUB_TRACE_TYPE
#define _D2_USB_U2_HUB_TRACE_TYPE                       _USB_U2_TRACE_DIRECT_TO_HUB
#endif

#ifndef _D2_USB_U3_HUB_TRACE_TYPE
#define _D2_USB_U3_HUB_TRACE_TYPE                       _USB_U3_TRACE_DIRECT_TO_HUB
#endif

#ifndef _D2_USB_SPEED
#define _D2_USB_SPEED                                   _USB_BILLBOARD_ONLY
#endif

#ifndef _D2_USB_LANE
#define _D2_USB_LANE                                    _USB_3_LANE_NONE
#endif

#ifndef _D2_USB_HUB_RTS_SLAVE_ADDR
#define _D2_USB_HUB_RTS_SLAVE_ADDR                      0x00
#endif

#ifndef _D2_USB_RTS_SMBUS_IIC
#define _D2_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN
#endif

#ifndef _D2_TYPE_C_PORT_CTRL_TYPE
#define _D2_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE
#endif

#ifndef _D2_TYPE_C_BILLBOARD_TYPE
#define _D2_TYPE_C_BILLBOARD_TYPE                       _BILLBOARD_NONE
#endif

#ifndef _D2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR
#define _D2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00
#endif

#ifndef _D2_TYPE_C_EXT_PIN_E_AUXPN_SWAP
#define _D2_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#endif

#ifndef _D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION
#define _D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#endif

#ifndef _D2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E
#define _D2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#endif

#ifndef _D2_TYPE_C_EXT_CC_ATTACH_DETECT
#define _D2_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#endif

#ifndef _D2_TYPE_C_EXT_ALT_MODE_READY_DETECT
#define _D2_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#endif

#ifndef _D2_TYPE_C_EXT_PD3_1_EPR_SUPPORT
#define _D2_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF
#endif

#ifndef _D2_TYPE_C_EMB_PORT_ROLE
#define _D2_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#endif

#ifndef _D2_TYPE_C_EMB_DRP_PREFER
#define _D2_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#endif

#ifndef _D2_TYPE_C_EMB_SRC_DEF_CUR
#define _D2_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#endif

#ifndef _D2_TYPE_C_EMB_USB_ROLE
#define _D2_TYPE_C_EMB_USB_ROLE                         _TYPE_C_USB_NOT_SUPPORT
#endif

#ifndef _D2_TYPE_C_EMB_CONNECTOR_TYPE
#define _D2_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#endif

#ifndef _D2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT
#define _D2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT             _OFF
#endif

#ifndef _D2_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _D2_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#endif

#ifndef _D2_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF
#define _D2_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#endif

#ifndef _D2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#define _D2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT               _OFF
#endif

#ifndef _D2_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _D2_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#endif

#ifndef _D2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _D2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _OFF
#endif

#ifndef _D2_TYPE_C_PMIC_TYPE
#define _D2_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#endif

#ifndef _D2_TYPE_C_PMIC_SLAVE_ADDRESS
#define _D2_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#endif

#ifndef _D2_TYPE_C_PMIC_IIC
#define _D2_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#endif

#ifndef _D2_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _D2_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#endif

#ifndef _D2_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _D2_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#endif

#ifndef _D2_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _D2_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#endif

#ifndef _D2_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _D2_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#endif

#ifndef _D2_TYPE_C_PMIC_IOUT_MAX_CURRENT
#define _D2_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#endif

#ifndef _D2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _D2_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#endif

#ifndef _D2_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _D2_TYPE_C_PMIC_FW_OVP_THRESHOLD                130 // Unit: %
#endif

#ifndef _D2_TYPE_C_PMIC_FW_UVP_THRESHOLD
#define _D2_TYPE_C_PMIC_FW_UVP_THRESHOLD                66 // Unit: %
#endif

#ifndef _D2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _D2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#endif

#ifndef _D2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _D2_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            0 // unit: %, should multiply with PMIC setting current to get the real OCP value
#endif

#ifndef _D2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN
#define _D2_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#endif

#ifndef _D2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _D2_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#endif

#ifndef _D2_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _D2_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#endif

#ifndef _D2_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _D2_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#endif

#ifndef _D2_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN
#define _D2_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms
#endif

#ifndef _D2_MAX_HDMI_EDID_COUNT
#define _D2_MAX_HDMI_EDID_COUNT                         1
#endif

#ifndef _D2_HDMI_ARC_TX_PIN
#define _D2_HDMI_ARC_TX_PIN                             _HDMI_ARC_TX_NONE
#endif

#ifndef _D2_HDMI_MAC_TYPE
#define _D2_HDMI_MAC_TYPE                               _HDMI_MAC_TMDS
#endif

#ifndef _D2_HDMI_LINK_CLK_RATE
#define _D2_HDMI_LINK_CLK_RATE                          _HDMI_LINK_SPEED_600MHZ
#endif

#ifndef _D2_HDMI_MAIN_LINK_LANES
#define _D2_HDMI_MAIN_LINK_LANES                        _HDMI_THREE_LANE
#endif

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#ifndef _D3_INPUT_PORT_TYPE
#define _D3_INPUT_PORT_TYPE                             _D3_NO_PORT
#endif

#ifndef _D3_DDC_CHANNEL_SEL
#define _D3_DDC_CHANNEL_SEL                             _NO_DDC
#endif

#ifndef _D3_EMBEDDED_DDCRAM_MAX_SIZE
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#endif

#ifndef _D3_EMBEDDED_DDCRAM_LOCATION
#define _D3_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D3_EDID_EXTERNAL_EEPROM_MAX_SIZE
#define _D3_EDID_EXTERNAL_EEPROM_MAX_SIZE               _EDID_EEPROM_SIZE_256
#endif

#ifndef _D3_MAX_HDMI_EDID_COUNT
#define _D3_MAX_HDMI_EDID_COUNT                         1
#endif

#ifndef _D3_HDMI_CEC_PIN
#define _D3_HDMI_CEC_PIN                                _HDMI_CEC_NONE
#endif

#ifndef _D3_HDMI_CEC_EDID_PHYSICAL_ADDR
#define _D3_HDMI_CEC_EDID_PHYSICAL_ADDR                 0x0000
#endif

#ifndef _D3_HDMI_ARC_TX_PIN
#define _D3_HDMI_ARC_TX_PIN                             _HDMI_ARC_TX_NONE
#endif

#ifndef _D3_HDMI_MAC_TYPE
#define _D3_HDMI_MAC_TYPE                               _HDMI_MAC_TMDS
#endif

#ifndef _D3_HDMI_LINK_CLK_RATE
#define _D3_HDMI_LINK_CLK_RATE                          _HDMI_LINK_SPEED_600MHZ
#endif

#ifndef _D3_HDMI_MAIN_LINK_LANES
#define _D3_HDMI_MAIN_LINK_LANES                        _HDMI_THREE_LANE
#endif

//--------------------------------------------------
// D4 Input Port
//--------------------------------------------------
#ifndef _D4_INPUT_PORT_TYPE
#define _D4_INPUT_PORT_TYPE                             _D4_NO_PORT
#endif

#ifndef _D4_DDC_CHANNEL_SEL
#define _D4_DDC_CHANNEL_SEL                             _NO_DDC
#endif

#ifndef _D4_EMBEDDED_DDCRAM_MAX_SIZE
#define _D4_EMBEDDED_DDCRAM_MAX_SIZE                    _EDID_SIZE_NONE
#endif

#ifndef _D4_EMBEDDED_DDCRAM_LOCATION
#define _D4_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D4_EDID_EXTERNAL_EEPROM_MAX_SIZE
#define _D4_EDID_EXTERNAL_EEPROM_MAX_SIZE               _EDID_EEPROM_SIZE_256
#endif

#ifndef _D4_MAX_HDMI_EDID_COUNT
#define _D4_MAX_HDMI_EDID_COUNT                         1
#endif

#ifndef _D4_HDMI_CEC_PIN
#define _D4_HDMI_CEC_PIN                                _HDMI_CEC_NONE
#endif

#ifndef _D4_HDMI_ARC_TX_PIN
#define _D4_HDMI_ARC_TX_PIN                             _HDMI_ARC_TX_NONE
#endif

#ifndef _D4_HDMI_CEC_EDID_PHYSICAL_ADDR
#define _D4_HDMI_CEC_EDID_PHYSICAL_ADDR                 0x0000
#endif

#ifndef _D4_HDMI_MAC_TYPE
#define _D4_HDMI_MAC_TYPE                               _HDMI_MAC_TMDS
#endif

#ifndef _D4_HDMI_LINK_CLK_RATE
#define _D4_HDMI_LINK_CLK_RATE                          _HDMI_LINK_SPEED_600MHZ
#endif

#ifndef _D4_HDMI_MAIN_LINK_LANES
#define _D4_HDMI_MAIN_LINK_LANES                        _HDMI_THREE_LANE
#endif

//--------------------------------------------------
// D7 Input Port
//--------------------------------------------------
#ifndef _D7_INPUT_PORT_TYPE
#define _D7_INPUT_PORT_TYPE                             _D7_NO_PORT
#endif

#ifndef _D7_D0_EMBEDDED_DDCRAM_SIZE
#define _D7_D0_EMBEDDED_DDCRAM_SIZE                     _EDID_SIZE_NONE
#endif

#ifndef _D7_D1_EMBEDDED_DDCRAM_SIZE
#define _D7_D1_EMBEDDED_DDCRAM_SIZE                     _EDID_SIZE_NONE
#endif

#ifndef _D7_EMBEDDED_DDCRAM_LOCATION
#define _D7_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D7_DP_CONNECTOR_TYPE
#define _D7_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_DUAL_DP
#endif

#ifndef _D7_SEARCH_MAIN_PORT_ONLY
#define _D7_SEARCH_MAIN_PORT_ONLY                       _OFF
#endif

//--------------------------------------------------
// D8 Input Port
//--------------------------------------------------
#ifndef _D8_INPUT_PORT_TYPE
#define _D8_INPUT_PORT_TYPE                             _D8_NO_PORT
#endif

#ifndef _D8_D1_EMBEDDED_DDCRAM_SIZE
#define _D8_D1_EMBEDDED_DDCRAM_SIZE                     _EDID_SIZE_NONE
#endif

#ifndef _D8_D2_EMBEDDED_DDCRAM_SIZE
#define _D8_D2_EMBEDDED_DDCRAM_SIZE                     _EDID_SIZE_NONE
#endif

#ifndef _D8_EMBEDDED_DDCRAM_LOCATION
#define _D8_EMBEDDED_DDCRAM_LOCATION                    _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D8_DP_CONNECTOR_TYPE
#define _D8_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_DUAL_DP
#endif

#ifndef _D8_SEARCH_MAIN_PORT_ONLY
#define _D8_SEARCH_MAIN_PORT_ONLY                       _OFF
#endif

//--------------------------------------------------
// D9 Input Port
//--------------------------------------------------
#ifndef _D9_INPUT_PORT_TYPE
#define _D9_INPUT_PORT_TYPE                             _D9_NO_PORT
#endif

#ifndef _D9_EMBEDDED_XRAM_MAX_SIZE
#define _D9_EMBEDDED_XRAM_MAX_SIZE                      _EDID_SIZE_NONE
#endif

#ifndef _D9_EMBEDDED_XRAM_LOCATION
#define _D9_EMBEDDED_XRAM_LOCATION                      _EDID_TABLE_LOCATION_CODE
#endif

//--------------------------------------------------
// D12 Input Port
//--------------------------------------------------
#ifndef _D12_INPUT_PORT_TYPE
#define _D12_INPUT_PORT_TYPE                            _D12_NO_PORT
#endif

#ifndef _D12_INPUT_PORT_SWITCH_FROM
#define _D12_INPUT_PORT_SWITCH_FROM                     _SWITCH_NONE
#endif

//--------------------------------------------------
// D13 Input Port
//--------------------------------------------------
#ifndef _D13_INPUT_PORT_TYPE
#define _D13_INPUT_PORT_TYPE                            _D13_NO_PORT
#endif

#ifndef _D13_INPUT_PORT_SWITCH_FROM
#define _D13_INPUT_PORT_SWITCH_FROM                     _SWITCH_NONE
#endif

//--------------------------------------------------
// D14 Input Port
//--------------------------------------------------
#ifndef _D14_INPUT_PORT_TYPE
#define _D14_INPUT_PORT_TYPE                            _D14_NO_PORT
#endif

#ifndef _D14_INPUT_PORT_SWITCH_FROM
#define _D14_INPUT_PORT_SWITCH_FROM                     _SWITCH_NONE
#endif

//--------------------------------------------------
// D15 Input Port
//--------------------------------------------------
#ifndef _D15_INPUT_PORT_TYPE
#define _D15_INPUT_PORT_TYPE                            _D15_NO_PORT
#endif

#ifndef _D15_INPUT_PORT_SWITCH_FROM
#define _D15_INPUT_PORT_SWITCH_FROM                     _SWITCH_NONE
#endif


/////////////////////////
// Repeater DFP Config //
/////////////////////////

//--------------------------------------------------
// Repeater DownStream Port Orientation
//--------------------------------------------------
#ifndef _RETIMER_DFP_ORIENTATION
#define _RETIMER_DFP_ORIENTATION                        _TYPE_C_DFP_ORIENTATION_NONE
#endif


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#ifndef _A0_INPUT_PORT_GROUP
#define _A0_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D0_INPUT_PORT_GROUP
#define _D0_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D1_INPUT_PORT_GROUP
#define _D1_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D2_INPUT_PORT_GROUP
#define _D2_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D3_INPUT_PORT_GROUP
#define _D3_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D4_INPUT_PORT_GROUP
#define _D4_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D7_INPUT_PORT_GROUP
#define _D7_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D8_INPUT_PORT_GROUP
#define _D8_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D9_INPUT_PORT_GROUP
#define _D9_INPUT_PORT_GROUP                            _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D12_INPUT_PORT_GROUP
#define _D12_INPUT_PORT_GROUP                           _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D13_INPUT_PORT_GROUP
#define _D13_INPUT_PORT_GROUP                           _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D14_INPUT_PORT_GROUP
#define _D14_INPUT_PORT_GROUP                           _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D15_INPUT_PORT_GROUP
#define _D15_INPUT_PORT_GROUP                           _INPUT_PORT_GROUP_NONE
#endif

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#ifndef _INPUT_PORT_SEARCH_PRI_0
#define _INPUT_PORT_SEARCH_PRI_0                        _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_1
#define _INPUT_PORT_SEARCH_PRI_1                        _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_2
#define _INPUT_PORT_SEARCH_PRI_2                        _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_3
#define _INPUT_PORT_SEARCH_PRI_3                        _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_4
#define _INPUT_PORT_SEARCH_PRI_4                        _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_5
#define _INPUT_PORT_SEARCH_PRI_5                        _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_6
#define _INPUT_PORT_SEARCH_PRI_6                        _NO_INPUT_PORT
#endif


//////////////
// VGA Port //
//////////////

//--------------------------------------------------
// Analog Signal Swap Options
//--------------------------------------------------
#ifndef _VGA_INPUT_SWAP_RG
#define _VGA_INPUT_SWAP_RG                              _OFF
#endif

#ifndef _VGA_INPUT_SWAP_RB
#define _VGA_INPUT_SWAP_RB                              _OFF
#endif

#ifndef _VGA_INPUT_SWAP_GB
#define _VGA_INPUT_SWAP_GB                              _OFF
#endif

//--------------------------------------------------
// Analog Hsync Schmitt Trigger Control
//--------------------------------------------------
#ifndef _VGA_HS_SCHMITT_TRIGGER_POLARITY_SEL
#define _VGA_HS_SCHMITT_TRIGGER_POLARITY_SEL            _POSITIVE
#endif

#ifndef _VGA_HS_SCHMITT_TRIGGER_VTH_FINE_TUNE
#define _VGA_HS_SCHMITT_TRIGGER_VTH_FINE_TUNE           _DISABLE
#endif

#ifndef _VGA_HS_SCHMITT_TRIGGER_POSITIVE_VTH
#define _VGA_HS_SCHMITT_TRIGGER_POSITIVE_VTH            _HS_SCHMITT_TRIGGER_LEVEL_10
#endif

#ifndef _VGA_HS_SCHMITT_TRIGGER_NEGATIVE_VTH
#define _VGA_HS_SCHMITT_TRIGGER_NEGATIVE_VTH            _HS_SCHMITT_TRIGGER_LEVEL_01
#endif


///////////////
// TMDS Port //
///////////////

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#ifndef _D2_TMDS_PCB_LANE0_MAPPING
#define _D2_TMDS_PCB_LANE0_MAPPING                      _TMDS_SCALER_LANE0
#endif

#ifndef _D2_TMDS_PCB_LANE1_MAPPING
#define _D2_TMDS_PCB_LANE1_MAPPING                      _TMDS_SCALER_LANE1
#endif

#ifndef _D2_TMDS_PCB_LANE2_MAPPING
#define _D2_TMDS_PCB_LANE2_MAPPING                      _TMDS_SCALER_LANE2
#endif

#ifndef _D2_TMDS_PCB_LANE3_MAPPING
#define _D2_TMDS_PCB_LANE3_MAPPING                      _TMDS_SCALER_LANE3
#endif

#ifndef _D1_TMDS_BR_SWAP
#define _D1_TMDS_BR_SWAP                                _OFF
#endif

#ifndef _D1_TMDS_PN_SWAP
#define _D1_TMDS_PN_SWAP                                _OFF
#endif

#ifndef _D2_TMDS_BR_SWAP
#define _D2_TMDS_BR_SWAP                                _OFF
#endif

#ifndef _D2_TMDS_PN_SWAP
#define _D2_TMDS_PN_SWAP                                (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#endif

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#ifndef _D3_TMDS_PCB_LANE0_MAPPING
#define _D3_TMDS_PCB_LANE0_MAPPING                      _TMDS_SCALER_LANE0
#endif

#ifndef _D3_TMDS_PCB_LANE1_MAPPING
#define _D3_TMDS_PCB_LANE1_MAPPING                      _TMDS_SCALER_LANE1
#endif

#ifndef _D3_TMDS_PCB_LANE2_MAPPING
#define _D3_TMDS_PCB_LANE2_MAPPING                      _TMDS_SCALER_LANE2
#endif

#ifndef _D3_TMDS_PCB_LANE3_MAPPING
#define _D3_TMDS_PCB_LANE3_MAPPING                      _TMDS_SCALER_LANE3
#endif

#ifndef _D3_TMDS_BR_SWAP
#define _D3_TMDS_BR_SWAP                                _OFF
#endif
#ifndef _D3_TMDS_PN_SWAP
#define _D3_TMDS_PN_SWAP                                (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#endif

#ifndef _D4_TMDS_PCB_LANE0_MAPPING
#define _D4_TMDS_PCB_LANE0_MAPPING                      _TMDS_SCALER_LANE0
#endif

#ifndef _D4_TMDS_PCB_LANE1_MAPPING
#define _D4_TMDS_PCB_LANE1_MAPPING                      _TMDS_SCALER_LANE1
#endif

#ifndef _D4_TMDS_PCB_LANE2_MAPPING
#define _D4_TMDS_PCB_LANE2_MAPPING                      _TMDS_SCALER_LANE2
#endif

#ifndef _D4_TMDS_PCB_LANE3_MAPPING
#define _D4_TMDS_PCB_LANE3_MAPPING                      _TMDS_SCALER_LANE3
#endif


#ifndef _D4_TMDS_BR_SWAP
#define _D4_TMDS_BR_SWAP                                _OFF
#endif
#ifndef _D4_TMDS_PN_SWAP
#define _D4_TMDS_PN_SWAP                                (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#endif

//--------------------------------------------------
// HDMI SRC 5V Detect By User
//--------------------------------------------------
#ifndef _HDMI_5V_DETECT_BY_USER
#define _HDMI_5V_DETECT_BY_USER                         _OFF
#endif


/////////////
// DP Port //
/////////////

//--------------------------------------------------
// DP Lane & PN Swap Option
//--------------------------------------------------
#ifndef _D0_DP_PCB_LANE0_MAPPING
#define _D0_DP_PCB_LANE0_MAPPING                        _DP_SCALER_LANE0
#endif

#ifndef _D0_DP_PCB_LANE1_MAPPING
#define _D0_DP_PCB_LANE1_MAPPING                        _DP_SCALER_LANE1
#endif

#ifndef _D0_DP_PCB_LANE2_MAPPING
#define _D0_DP_PCB_LANE2_MAPPING                        _DP_SCALER_LANE2
#endif

#ifndef _D0_DP_PCB_LANE3_MAPPING
#define _D0_DP_PCB_LANE3_MAPPING                        _DP_SCALER_LANE3
#endif

#ifndef _D0_DP_PCB_LANE0_PN_SWAP
#define _D0_DP_PCB_LANE0_PN_SWAP                        _OFF
#endif

#ifndef _D0_DP_PCB_LANE1_PN_SWAP
#define _D0_DP_PCB_LANE1_PN_SWAP                        _OFF
#endif

#ifndef _D0_DP_PCB_LANE2_PN_SWAP
#define _D0_DP_PCB_LANE2_PN_SWAP                        _OFF
#endif

#ifndef _D0_DP_PCB_LANE3_PN_SWAP
#define _D0_DP_PCB_LANE3_PN_SWAP                        _OFF
#endif

#ifndef _D1_DP_PCB_LANE0_MAPPING
#define _D1_DP_PCB_LANE0_MAPPING                        _DP_SCALER_LANE0
#endif

#ifndef _D1_DP_PCB_LANE1_MAPPING
#define _D1_DP_PCB_LANE1_MAPPING                        _DP_SCALER_LANE1
#endif

#ifndef _D1_DP_PCB_LANE2_MAPPING
#define _D1_DP_PCB_LANE2_MAPPING                        _DP_SCALER_LANE2
#endif

#ifndef _D1_DP_PCB_LANE3_MAPPING
#define _D1_DP_PCB_LANE3_MAPPING                        _DP_SCALER_LANE3
#endif

#ifndef _D1_DP_PCB_LANE0_PN_SWAP
#define _D1_DP_PCB_LANE0_PN_SWAP                        _OFF
#endif

#ifndef _D1_DP_PCB_LANE1_PN_SWAP
#define _D1_DP_PCB_LANE1_PN_SWAP                        _OFF
#endif

#ifndef _D1_DP_PCB_LANE2_PN_SWAP
#define _D1_DP_PCB_LANE2_PN_SWAP                        _OFF
#endif

#ifndef _D1_DP_PCB_LANE3_PN_SWAP
#define _D1_DP_PCB_LANE3_PN_SWAP                        _OFF
#endif

#ifndef _D2_DP_PCB_LANE0_MAPPING
#define _D2_DP_PCB_LANE0_MAPPING                        _DP_SCALER_LANE0
#endif

#ifndef _D2_DP_PCB_LANE1_MAPPING
#define _D2_DP_PCB_LANE1_MAPPING                        _DP_SCALER_LANE1
#endif

#ifndef _D2_DP_PCB_LANE2_MAPPING
#define _D2_DP_PCB_LANE2_MAPPING                        _DP_SCALER_LANE2
#endif

#ifndef _D2_DP_PCB_LANE3_MAPPING
#define _D2_DP_PCB_LANE3_MAPPING                        _DP_SCALER_LANE3
#endif

#ifndef _D2_DP_PCB_LANE0_PN_SWAP
#define _D2_DP_PCB_LANE0_PN_SWAP                        _OFF
#endif

#ifndef _D2_DP_PCB_LANE1_PN_SWAP
#define _D2_DP_PCB_LANE1_PN_SWAP                        _OFF
#endif

#ifndef _D2_DP_PCB_LANE2_PN_SWAP
#define _D2_DP_PCB_LANE2_PN_SWAP                        _OFF
#endif

#ifndef _D2_DP_PCB_LANE3_PN_SWAP
#define _D2_DP_PCB_LANE3_PN_SWAP                        _OFF
#endif

#ifndef _P0_DP_TYPE_C_PCB_LANE0_MAPPING
#define _P0_DP_TYPE_C_PCB_LANE0_MAPPING                 _TYPE_C_TX2
#endif

#ifndef _P0_DP_TYPE_C_PCB_LANE1_MAPPING
#define _P0_DP_TYPE_C_PCB_LANE1_MAPPING                 _TYPE_C_RX2
#endif

#ifndef _P0_DP_TYPE_C_PCB_LANE2_MAPPING
#define _P0_DP_TYPE_C_PCB_LANE2_MAPPING                 _TYPE_C_TX1
#endif

#ifndef _P0_DP_TYPE_C_PCB_LANE3_MAPPING
#define _P0_DP_TYPE_C_PCB_LANE3_MAPPING                 _TYPE_C_RX1
#endif

#ifndef _P0_DP_PCB_LANE0_MAPPING
#define _P0_DP_PCB_LANE0_MAPPING                        _DP_LANE_0
#endif

#ifndef _P0_DP_PCB_LANE1_MAPPING
#define _P0_DP_PCB_LANE1_MAPPING                        _DP_LANE_1
#endif

#ifndef _P0_DP_PCB_LANE2_MAPPING
#define _P0_DP_PCB_LANE2_MAPPING                        _DP_LANE_2
#endif

#ifndef _P0_DP_PCB_LANE3_MAPPING
#define _P0_DP_PCB_LANE3_MAPPING                        _DP_LANE_3
#endif

#ifndef _P0_DP_PCB_LANE0_PN_SWAP
#define _P0_DP_PCB_LANE0_PN_SWAP                        _OFF
#endif

#ifndef _P0_DP_PCB_LANE1_PN_SWAP
#define _P0_DP_PCB_LANE1_PN_SWAP                        _OFF
#endif

#ifndef _P0_DP_PCB_LANE2_PN_SWAP
#define _P0_DP_PCB_LANE2_PN_SWAP                        _OFF
#endif

#ifndef _P0_DP_PCB_LANE3_PN_SWAP
#define _P0_DP_PCB_LANE3_PN_SWAP                        _OFF
#endif

//--------------------------------------------------
// DP Rx AUX Reply Swing Level
//--------------------------------------------------
#ifndef _DP_RX_AUX_REPLY_SWING_LEVEL
#define _DP_RX_AUX_REPLY_SWING_LEVEL                    _DP_AUX_SWING_900_MV
#endif

//--------------------------------------------------
// DP Tx AUX Request Swing Level
//--------------------------------------------------
#ifndef _DP_TX_AUX_REQUEST_SWING_LEVEL
#define _DP_TX_AUX_REQUEST_SWING_LEVEL                  _DP_AUX_SWING_900_MV
#endif


/////////////////////////
// U2HOST Port Support //
/////////////////////////

//--------------------------------------------------
// U2Host Port
//--------------------------------------------------
#ifndef _USB2_HOST_PORT_SUPPORT
#define _USB2_HOST_PORT_SUPPORT                         _OFF
#endif

#ifndef _USB2_HOST_PORT_HSTX_SWING
#define _USB2_HOST_PORT_HSTX_SWING                      _USB2_HOST_HS_SWING_LEVEL_3
#endif


////////////////////////
// Output Port Config //
////////////////////////

//--------------------------------------------------
// P0 Output Port
//--------------------------------------------------
#ifndef _P0_OUTPUT_TYPE
#define _P0_OUTPUT_TYPE                                 _P0_NO_PORT
#endif

#ifndef _P0_DP_CONNECTOR_TYPE
#define _P0_DP_CONNECTOR_TYPE                           _DP_CONNECTOR_NORMAL
#endif

#ifndef _P0_DP_LINK_CLK_RATE
#define _P0_DP_LINK_CLK_RATE                            _DP_ULTRA_SPEED_1350MHZ
#endif

#ifndef _P0_DP_MAIN_LINK_LANES
#define _P0_DP_MAIN_LINK_LANES                          _DP_FOUR_LANE
#endif

#ifndef _P0_DP_PCB_LOOP_DX_PORT
#define _P0_DP_PCB_LOOP_DX_PORT                         _D0_DP_PORT
#endif

#ifndef _P0_TYPE_C_PORT_CTRL_TYPE
#define _P0_TYPE_C_PORT_CTRL_TYPE                       _PORT_CTRL_NONE
#endif

#ifndef _P0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR
#define _P0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR             0x00
#endif

#ifndef _P0_TYPE_C_RTS_HUB_SLAVE_ADDR
#define _P0_TYPE_C_RTS_HUB_SLAVE_ADDR                   0x00
#endif

#ifndef _P0_USB_RTS_SMBUS_IIC
#define _P0_USB_RTS_SMBUS_IIC                           _NO_IIC_PIN
#endif

#ifndef _P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP
#define _P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP                 _SWAP_BY_SCALER
#endif

#ifndef _P0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E
#define _P0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E              _SWAP_BY_SCALER
#endif

#ifndef _P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION
#define _P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION        _SWAP_BY_PORT_CTRL
#endif

#ifndef _P0_TYPE_C_EXT_CC_ATTACH_DETECT
#define _P0_TYPE_C_EXT_CC_ATTACH_DETECT                 _EXT_PORT_CTRL_NOT_EXIST
#endif

#ifndef _P0_TYPE_C_EXT_ALT_MODE_READY_DETECT
#define _P0_TYPE_C_EXT_ALT_MODE_READY_DETECT            _EXT_PORT_CTRL_NOT_EXIST
#endif

#ifndef _P0_TYPE_C_EXT_PD3_1_EPR_SUPPORT
#define _P0_TYPE_C_EXT_PD3_1_EPR_SUPPORT                _OFF
#endif

#ifndef _P0_TYPE_C_EMB_PORT_ROLE
#define _P0_TYPE_C_EMB_PORT_ROLE                        _TYPE_C_PORT_DRP
#endif

#ifndef _P0_TYPE_C_EMB_DRP_PREFER
#define _P0_TYPE_C_EMB_DRP_PREFER                       _TYPE_C_DRP_NO_PREFERENCE
#endif

#ifndef _P0_TYPE_C_EMB_SRC_DEF_CUR
#define _P0_TYPE_C_EMB_SRC_DEF_CUR                      _TYPE_C_SRC_DEF_3P0A
#endif

#ifndef _P0_TYPE_C_EMB_CONNECTOR_TYPE
#define _P0_TYPE_C_EMB_CONNECTOR_TYPE                   _TYPE_C_PORT_RECEPTACLE
#endif

#ifndef _P0_TYPE_C_EMB_PD3_PPS_SUPPORT
#define _P0_TYPE_C_EMB_PD3_PPS_SUPPORT                  _OFF
#endif

#ifndef _P0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF
#define _P0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF       _OFF
#endif

#ifndef _P0_TYPE_C_EMB_PD3_1_EPR_SUPPORT
#define _P0_TYPE_C_EMB_PD3_1_EPR_SUPPORT                _OFF
#endif

#ifndef _P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT
#define _P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT              _OFF
#endif

#ifndef _P0_TYPE_C_PMIC_TYPE
#define _P0_TYPE_C_PMIC_TYPE                            _PMIC_NONE
#endif

#ifndef _P0_TYPE_C_PMIC_SLAVE_ADDRESS
#define _P0_TYPE_C_PMIC_SLAVE_ADDRESS                   0x00
#endif

#ifndef _P0_TYPE_C_PMIC_IIC
#define _P0_TYPE_C_PMIC_IIC                             _PMIC_NO_IIC_PIN
#endif

#ifndef _P0_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _P0_TYPE_C_PMIC_VBUS_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#endif

#ifndef _P0_TYPE_C_PMIC_IOUT_ADC_CHANNEL
#define _P0_TYPE_C_PMIC_IOUT_ADC_CHANNEL                _TYPE_C_PMIC_ADC_MAPPING_NONE
#endif

#ifndef _P0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _P0_TYPE_C_PMIC_VBUS_MAX_VOLTAGE                2400 // unit: 10mV
#endif

#ifndef _P0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _P0_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO         12
#endif

#ifndef _P0_TYPE_C_PMIC_IOUT_MAX_CURRENT
#define _P0_TYPE_C_PMIC_IOUT_MAX_CURRENT                1320 // unit: 10mA
#endif

#ifndef _P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT
#define _P0_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT              _OFF
#endif

#ifndef _P0_TYPE_C_PMIC_FW_OVP_THRESHOLD
#define _P0_TYPE_C_PMIC_FW_OVP_THRESHOLD                130 // Unit: %
#endif

#ifndef _P0_TYPE_C_PMIC_FW_UVP_THRESHOLD
#define _P0_TYPE_C_PMIC_FW_UVP_THRESHOLD                66 // Unit: %
#endif

#ifndef _P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD
#define _P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD           _TYPE_C_PMIC_FW_OCP_NONE
#endif

#ifndef _P0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE
#define _P0_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE            0 // unit: %, should multiply with PMIC setting current to get the real OCP value
#endif

#ifndef _P0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN
#define _P0_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN           0 // unit: ms, Maximum value: 61000
#endif

#ifndef _P0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD
#define _P0_TYPE_C_PMIC_INT_PIN_CHECK_METHOD            _TYPE_C_PMIC_INT_PIN_NONE
#endif

#ifndef _P0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT
#define _P0_TYPE_C_PMIC_SAFETY_PROTECT_SUPPORT          _OFF
#endif

#ifndef _P0_TYPE_C_PMIC_SAFETY_POWER_LIMIT
#define _P0_TYPE_C_PMIC_SAFETY_POWER_LIMIT              100 // W
#endif

#ifndef _P0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN
#define _P0_TYPE_C_PMIC_SAFETY_DELAY_SHUTDOWN           1000 // ms
#endif


////////////////////
// Adaptor Config //
////////////////////

//--------------------------------------------------
// For Type-C Embedded Port Local Power Detect
//--------------------------------------------------
#ifndef _ADAPTOR_TYPE_C_PMIC_VBUS_ADC_CHANNEL
#define _ADAPTOR_TYPE_C_PMIC_VBUS_ADC_CHANNEL           _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2
#endif

#ifndef _ADAPTOR_TYPE_C_PMIC_VBUS_MAX_VOLTAGE
#define _ADAPTOR_TYPE_C_PMIC_VBUS_MAX_VOLTAGE           2400 // unit: 10mV
#endif

#ifndef _ADAPTOR_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO
#define _ADAPTOR_TYPE_C_PMIC_VBUS_TO_ADC_INPUT_RATIO    12
#endif


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#ifndef _LVDS_PORT_SEL
#define _LVDS_PORT_SEL                                  _LVDS_2_PORT_AB
#endif

#ifndef _LVDS_PORT_MIRROR
#define _LVDS_PORT_MIRROR                               _DISABLE
#endif

#ifndef _LVDS_PORT_AB_SWAP
#define _LVDS_PORT_AB_SWAP                              _DISABLE
#endif

#ifndef _LVDS_PORT_CD_SWAP
#define _LVDS_PORT_CD_SWAP                              _DISABLE
#endif

#ifndef _LVDS_PN_SWAP
#define _LVDS_PN_SWAP                                   _DISABLE
#endif

#ifndef _LVDS_RB_SWAP
#define _LVDS_RB_SWAP                                   _DISABLE
#endif

#ifndef _LVDS_ML_SWAP
#define _LVDS_ML_SWAP                                   _DISABLE
#endif

#ifndef _LVDS_DVS_INVERT
#define _LVDS_DVS_INVERT                                _DISABLE
#endif

#ifndef _LVDS_DHS_INVERT
#define _LVDS_DHS_INVERT                                _DISABLE
#endif

#ifndef _LVDS_DEN_INVERT
#define _LVDS_DEN_INVERT                                _DISABLE
#endif

#ifndef _LVDS_PAIR_MIRROR
#define _LVDS_PAIR_MIRROR                               _DISABLE
#endif

#ifndef _LVDS_CLK_CHANNEL_SEL
#define _LVDS_CLK_CHANNEL_SEL                           _NORMAL_MODE
#endif

//--------------------------------------------------
// LVDS Port AB Phase Selection
//--------------------------------------------------
#ifndef _LVDS_A0_PHASE
#define _LVDS_A0_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_A1_PHASE
#define _LVDS_A1_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_A2_PHASE
#define _LVDS_A2_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_AC_PHASE
#define _LVDS_AC_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_A3_PHASE
#define _LVDS_A3_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_A4_PHASE
#define _LVDS_A4_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_B0_PHASE
#define _LVDS_B0_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_B1_PHASE
#define _LVDS_B1_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_B2_PHASE
#define _LVDS_B2_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_BC_PHASE
#define _LVDS_BC_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_B3_PHASE
#define _LVDS_B3_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_B4_PHASE
#define _LVDS_B4_PHASE                                  _LVDS_PI_PHASE_AB0
#endif

#ifndef _LVDS_PI_PHASE_AB0_SEL
#define _LVDS_PI_PHASE_AB0_SEL                          _LVDS_PHASE0
#endif

#ifndef _LVDS_PI_PHASE_AB1_SEL
#define _LVDS_PI_PHASE_AB1_SEL                          _LVDS_PHASE0
#endif

#ifndef _LVDS_PI_PHASE_AB2_SEL
#define _LVDS_PI_PHASE_AB2_SEL                          _LVDS_PHASE0
#endif

#ifndef _LVDS_PI_PHASE_AB3_SEL
#define _LVDS_PI_PHASE_AB3_SEL                          _LVDS_PHASE0
#endif

//--------------------------------------------------
// LVDS Port CD Phase Selection
//--------------------------------------------------
#ifndef _LVDS_C0_PHASE
#define _LVDS_C0_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_C1_PHASE
#define _LVDS_C1_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_C2_PHASE
#define _LVDS_C2_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_CC_PHASE
#define _LVDS_CC_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_C3_PHASE
#define _LVDS_C3_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_C4_PHASE
#define _LVDS_C4_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_D0_PHASE
#define _LVDS_D0_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_D1_PHASE
#define _LVDS_D1_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_D2_PHASE
#define _LVDS_D2_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_DC_PHASE
#define _LVDS_DC_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_D3_PHASE
#define _LVDS_D3_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_D4_PHASE
#define _LVDS_D4_PHASE                                  _LVDS_PI_PHASE_CD0
#endif

#ifndef _LVDS_PI_PHASE_CD0_SEL
#define _LVDS_PI_PHASE_CD0_SEL                          _LVDS_PHASE0
#endif

#ifndef _LVDS_PI_PHASE_CD1_SEL
#define _LVDS_PI_PHASE_CD1_SEL                          _LVDS_PHASE0
#endif

#ifndef _LVDS_PI_PHASE_CD2_SEL
#define _LVDS_PI_PHASE_CD2_SEL                          _LVDS_PHASE0
#endif

#ifndef _LVDS_PI_PHASE_CD3_SEL
#define _LVDS_PI_PHASE_CD3_SEL                          _LVDS_PHASE0
#endif

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#ifndef _LVDS_DRIV_CONTROL
#define _LVDS_DRIV_CONTROL                              _LVDS_DRIV_CONTROL_3_0
#endif

#ifndef _LVDS_VCM_CONTROL
#define _LVDS_VCM_CONTROL                               _LVDS_VCM_NORMAL
#endif

#ifndef _LVDS_SR_CONTROL
#define _LVDS_SR_CONTROL                                _LVDS_SR_CONTROL_0
#endif

#ifndef _LVDS_PRE_EMPHASIS_CONTROL
#define _LVDS_PRE_EMPHASIS_CONTROL                      _LVDS_PRE_EMPHASIS_0
#endif

#ifndef _LVDS_TERMINATION_CONTROL
#define _LVDS_TERMINATION_CONTROL                       _DISABLE
#endif

#ifndef _LVDS_VCM_USER_LEVEL
#define _LVDS_VCM_USER_LEVEL                            0x0C
#endif

//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
#ifndef _LVDS_SPREAD_RANGE
#define _LVDS_SPREAD_RANGE                              10
#endif

#ifndef _LVDS_SPREAD_SPEED
#define _LVDS_SPREAD_SPEED                              _SPEED_33K
#endif


//////////////////////////
// eDPTx 1.2 HBR2 Panel //
//////////////////////////

//--------------------------------------------------
// eDPTx 1.2 HBR2 Main Link Config
//--------------------------------------------------
#ifndef _PANEL_DPTX_SWING_LEVEL
#define _PANEL_DPTX_SWING_LEVEL                         _DP_SWING_800_MV
#endif

#ifndef _PANEL_DPTX_PREEMPHASIS_LEVEL
#define _PANEL_DPTX_PREEMPHASIS_LEVEL                   _DP_PREEMPHASIS_3_5_DB
#endif

//--------------------------------------------------
// eDPTx 1.2 HBR2 SSC Config
//--------------------------------------------------
#ifndef _PANEL_DPTX_SPREAD_RANGE
#define _PANEL_DPTX_SPREAD_RANGE                        12
#endif

#ifndef _PANEL_DPTX_SPREAD_SPEED
#define _PANEL_DPTX_SPREAD_SPEED                        _SPEED_33K
#endif

//--------------------------------------------------
// eDPTx 1.2 HBR2 FB/Lane Config
//--------------------------------------------------
#ifndef _PANEL_DPTX_PORT_MIRROR
#define _PANEL_DPTX_PORT_MIRROR                         _DISABLE
#endif
#ifndef _PANEL_DPTX_PORT_0_LANE_SWAP
#define _PANEL_DPTX_PORT_0_LANE_SWAP                    _DISABLE
#endif
#ifndef _PANEL_DPTX_PORT_1_LANE_SWAP
#define _PANEL_DPTX_PORT_1_LANE_SWAP                    _DISABLE
#endif
#ifndef _PANEL_DPTX_PORT_2_LANE_SWAP
#define _PANEL_DPTX_PORT_2_LANE_SWAP                    _DISABLE
#endif
#ifndef _PANEL_DPTX_PORT_3_LANE_SWAP
#define _PANEL_DPTX_PORT_3_LANE_SWAP                    _DISABLE
#endif
#ifndef _PANEL_DPTX_PORT_0_LANE_PN_SWAP
#define _PANEL_DPTX_PORT_0_LANE_PN_SWAP                 _DISABLE
#endif
#ifndef _PANEL_DPTX_PORT_1_LANE_PN_SWAP
#define _PANEL_DPTX_PORT_1_LANE_PN_SWAP                 _DISABLE
#endif
#ifndef _PANEL_DPTX_PORT_2_LANE_PN_SWAP
#define _PANEL_DPTX_PORT_2_LANE_PN_SWAP                 _DISABLE
#endif
#ifndef _PANEL_DPTX_PORT_3_LANE_PN_SWAP
#define _PANEL_DPTX_PORT_3_LANE_PN_SWAP                 _DISABLE
#endif


/////////////////////////////
//  eDPTx Panel AUX Config //
/////////////////////////////

//--------------------------------------------------
// eDPTx AUX Swing Level
//--------------------------------------------------
#ifndef _PANEL_DPTX_AUX_SWING_LEVEL
#define _PANEL_DPTX_AUX_SWING_LEVEL                     _DP_AUX_SWING_1100_MV
#endif

//--------------------------------------------------
// eDPTx AUX PN SWAP ENABLE
//--------------------------------------------------
#ifndef _PANEL_DPTX_AUX_PN_SWAP_ENABLE
#define _PANEL_DPTX_AUX_PN_SWAP_ENABLE                  _DISABLE
#endif


////////////////////
// V by One Panel //
////////////////////

//--------------------------------------------------
// V by One Main Link Config
//--------------------------------------------------
#ifndef _PANEL_VBO_LANE_SWAP
#define _PANEL_VBO_LANE_SWAP                            _DISABLE
#endif

#ifndef _PANEL_VBO_ML_SWAP
#define _PANEL_VBO_ML_SWAP                              _DISABLE
#endif

#ifndef _PANEL_VBO_SECTION_0_PN_SWAP
#define _PANEL_VBO_SECTION_0_PN_SWAP                    _DISABLE
#endif

#ifndef _PANEL_VBO_LANE_DRIV_CONTROL
#define _PANEL_VBO_LANE_DRIV_CONTROL                    _VBO_DRIV_CONTROL_3_0
#endif

#ifndef _PANEL_VBO_PRE_EMPHASIS_CONTROL
#define _PANEL_VBO_PRE_EMPHASIS_CONTROL                 _VBO_PRE_EMPHASIS_0
#endif

//--------------------------------------------------
// V by One SSC Config
//--------------------------------------------------
#ifndef _PANEL_VBO_SPREAD_RANGE
#define _PANEL_VBO_SPREAD_RANGE                         15
#endif

#ifndef _PANEL_VBO_SPREAD_SPEED
#define _PANEL_VBO_SPREAD_SPEED                         _SPEED_30K
#endif


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#ifndef _PWM_DUT_RESOLUTION
#define _PWM_DUT_RESOLUTION                             _PWM_8BIT
#endif

#ifndef _BACKLIGHT_PWM
#define _BACKLIGHT_PWM                                  _NO_PWM
#endif

#ifndef _BACKLIGHT_PWM_INVERSE
#define _BACKLIGHT_PWM_INVERSE                          _OFF
#endif

#ifndef _PWM0_EN
#define _PWM0_EN                                        _OFF
#endif

#ifndef _PWM1_EN
#define _PWM1_EN                                        _OFF
#endif

#ifndef _PWM2_EN
#define _PWM2_EN                                        _OFF
#endif

#ifndef _PWM3_EN
#define _PWM3_EN                                        _OFF
#endif

#ifndef _PWM4_EN
#define _PWM4_EN                                        _OFF
#endif

#ifndef _PWM5_EN
#define _PWM5_EN                                        _OFF
#endif

#ifndef _PWM0_PSAV_EN
#define _PWM0_PSAV_EN                                   _OFF
#endif

#ifndef _PWM1_PSAV_EN
#define _PWM1_PSAV_EN                                   _OFF
#endif

#ifndef _PWM2_PSAV_EN
#define _PWM2_PSAV_EN                                   _OFF
#endif

#ifndef _PWM3_PSAV_EN
#define _PWM3_PSAV_EN                                   _OFF
#endif

#ifndef _PWM4_PSAV_EN
#define _PWM4_PSAV_EN                                   _OFF
#endif

#ifndef _PWM5_PSAV_EN
#define _PWM5_PSAV_EN                                   _OFF
#endif

#ifndef _PWM0_PDOW_EN
#define _PWM0_PDOW_EN                                   _OFF
#endif

#ifndef _PWM1_PDOW_EN
#define _PWM1_PDOW_EN                                   _OFF
#endif

#ifndef _PWM2_PDOW_EN
#define _PWM2_PDOW_EN                                   _OFF
#endif

#ifndef _PWM3_PDOW_EN
#define _PWM3_PDOW_EN                                   _OFF
#endif

#ifndef _PWM4_PDOW_EN
#define _PWM4_PDOW_EN                                   _OFF
#endif

#ifndef _PWM5_PDOW_EN
#define _PWM5_PDOW_EN                                   _OFF
#endif

#ifndef _PWM0_BYPASS_MODE_EN
#define _PWM0_BYPASS_MODE_EN                            _OFF
#endif

#ifndef _PWM1_BYPASS_MODE_EN
#define _PWM1_BYPASS_MODE_EN                            _OFF
#endif

#ifndef _PWM2_BYPASS_MODE_EN
#define _PWM2_BYPASS_MODE_EN                            _OFF
#endif

#ifndef _PWM3_BYPASS_MODE_EN
#define _PWM3_BYPASS_MODE_EN                            _OFF
#endif

#ifndef _PWM4_BYPASS_MODE_EN
#define _PWM4_BYPASS_MODE_EN                            _OFF
#endif

#ifndef _PWM5_BYPASS_MODE_EN
#define _PWM5_BYPASS_MODE_EN                            _OFF
#endif

#ifndef _PWM0_RST_EN
#define _PWM0_RST_EN                                    _OFF
#endif

#ifndef _PWM1_RST_EN
#define _PWM1_RST_EN                                    _OFF
#endif

#ifndef _PWM2_RST_EN
#define _PWM2_RST_EN                                    _OFF
#endif

#ifndef _PWM3_RST_EN
#define _PWM3_RST_EN                                    _OFF
#endif

#ifndef _PWM4_RST_EN
#define _PWM4_RST_EN                                    _OFF
#endif

#ifndef _PWM5_RST_EN
#define _PWM5_RST_EN                                    _OFF
#endif

#ifndef _PWM_RST_SIGNAL_SEL
#define _PWM_RST_SIGNAL_SEL                             _DVS
#endif

#ifndef _PWM_FREQ_DVSRST_CHECK
#define _PWM_FREQ_DVSRST_CHECK                          _ON
#endif


//////////
// TCON //
//////////

//--------------------------------------------------
// MBR TCON Pin Setting
//--------------------------------------------------
#ifndef _PCB_MBR_TCON_PIN
#define _PCB_MBR_TCON_PIN                               _TCON_NONE
#endif

//--------------------------------------------------
// MBR Driver IC Max Frequency (unit: kHz)
//--------------------------------------------------
#ifndef _PCB_MBR_DRIVER_IC_MAX_FREQ
#define _PCB_MBR_DRIVER_IC_MAX_FREQ                     (0)
#endif


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#ifndef _SW_IIC_SUPPORT
#define _SW_IIC_SUPPORT                                 _OFF
#endif

#ifndef _SW_IIC_CLK_DIV
#define _SW_IIC_CLK_DIV                                 _DIV_1
#endif

#ifndef _SW_IIC_HOLD_TIME_LIMIT_SUPPORT
#define _SW_IIC_HOLD_TIME_LIMIT_SUPPORT                 _OFF
#endif

#ifndef _HW_IIC_SUPPORT
#define _HW_IIC_SUPPORT                                 _OFF
#endif

#ifndef _HW_IIC_SPEED
#define _HW_IIC_SPEED                                   _HW_IIC_LOW_SPEED_100K
#endif

#ifndef _TYPEC_IIC_SUPPORT
#define _TYPEC_IIC_SUPPORT                              _OFF
#endif

#ifndef _TYPEC_IIC_SPEED
#define _TYPEC_IIC_SPEED                                _HW_IIC_LOW_SPEED_100K
#endif

#ifndef _HW_IIC_PAR_BY_USER_SUPPORT
#define _HW_IIC_PAR_BY_USER_SUPPORT                     _OFF
#endif

//--------------------------------------------------
// IIC 1 Slave Support Option
//--------------------------------------------------
#ifndef _HW_IIC_1_SLAVE_SUPPORT_OPTION
#define _HW_IIC_1_SLAVE_SUPPORT_OPTION                  _IIC_SLAVE_DEFAULT_OFF
#endif

//--------------------------------------------------
// IIC 1 Slave Address Config
//--------------------------------------------------
#ifndef _HW_IIC_1_SLAVE_ADDRESS_CONFIG_00
#define _HW_IIC_1_SLAVE_ADDRESS_CONFIG_00               0xB6
#endif

#ifndef _HW_IIC_1_SLAVE_ADDRESS_CONFIG_01
#define _HW_IIC_1_SLAVE_ADDRESS_CONFIG_01               0xB8
#endif

#ifndef _HW_IIC_1_SLAVE_ADDRESS_CONFIG_10
#define _HW_IIC_1_SLAVE_ADDRESS_CONFIG_10               0xBA
#endif

#ifndef _HW_IIC_1_SLAVE_ADDRESS_CONFIG_11
#define _HW_IIC_1_SLAVE_ADDRESS_CONFIG_11               0xBC
#endif

//-----------------------------------------------
// Macro of IIC 1 Slave Enable Pin
//-----------------------------------------------
#ifndef _HW_IIC_1_SLAVE_SUPPORT_ENABLE
#define _HW_IIC_1_SLAVE_SUPPORT_ENABLE                  0
#endif

#ifndef _HW_IIC_1_SLAVE_SUPPORT_DISABLE
#define _HW_IIC_1_SLAVE_SUPPORT_DISABLE                 1
#endif

#ifndef PCB_GPIO_GET_IIC_1_SLAVE_SUPPORT_CONFIG
#define PCB_GPIO_GET_IIC_1_SLAVE_SUPPORT_CONFIG()       _HW_IIC_1_SLAVE_SUPPORT_DISABLE
#endif

//-----------------------------------------------
// Macro of IIC 1 Slave Address Config Pin
//-----------------------------------------------
#ifndef PCB_GPIO_GET_IIC_1_SLAVE_ADDR_CONFIG_0
#define PCB_GPIO_GET_IIC_1_SLAVE_ADDR_CONFIG_0()        0
#endif

#ifndef PCB_GPIO_GET_IIC_1_SLAVE_ADDR_CONFIG_1
#define PCB_GPIO_GET_IIC_1_SLAVE_ADDR_CONFIG_1()        0
#endif


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#ifndef _EEPROM_TYPE
#define _EEPROM_TYPE                                    _EEPROM_24LC16
#endif

#ifndef _EEPROM_SLAVE_ADDRESS
#define _EEPROM_SLAVE_ADDRESS                           0xA0
#endif

#ifndef _PCB_SYS_EEPROM_IIC
#define _PCB_SYS_EEPROM_IIC                             _NO_IIC_PIN
#endif


////////////////////////////
// Second External Eeprom //
////////////////////////////

//--------------------------------------------------
// Second External Eeprom Data Storage Option
//--------------------------------------------------
#ifndef _SEC_EEPROM_TYPE
#define _SEC_EEPROM_TYPE                                _EEPROM_CAT24M01
#endif

#ifndef _SEC_EEPROM_SLAVE_ADDRESS
#define _SEC_EEPROM_SLAVE_ADDRESS                       0xA0
#endif

#ifndef _PCB_SEC_EEPROM_IIC
#define _PCB_SEC_EEPROM_IIC                             _NO_IIC_PIN
#endif


//////////
// UART //
//////////

//--------------------------------------------------
// UART Support Option
//--------------------------------------------------
#ifndef _EXT_UART0_EN
#define _EXT_UART0_EN                                   _OFF
#endif

#ifndef _EXT_UART1_EN
#define _EXT_UART1_EN                                   _OFF
#endif

#ifndef _EXT_UART2_EN
#define _EXT_UART2_EN                                   _OFF
#endif


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#ifndef _AD_KEY_SUPPORT
#define _AD_KEY_SUPPORT                                 _OFF
#endif

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#ifndef _LOW_SPEED_ADC_SUPPORT
#define _LOW_SPEED_ADC_SUPPORT                          _OFF
#endif

#ifndef _LOW_SPEED_ADC_POWER_REDUCE_SUPPORT
#define _LOW_SPEED_ADC_POWER_REDUCE_SUPPORT             _OFF
#endif

//--------------------------------------------------
// Type-C 10-Bit ADC Option
//--------------------------------------------------
#ifndef _10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT
#define _10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT             _OFF
#endif

//--------------------------------------------------
// Type-C CC Pin GPIO Mode Option
//--------------------------------------------------
#ifndef _TYPE_C_GPIO_MODE_SUPPORT
#define _TYPE_C_GPIO_MODE_SUPPORT                       _OFF
#endif

//-----------------------------------------------
// Macro of DP Cable ID Detect Setting
//-----------------------------------------------
#ifndef PCB_DP_UHBR_D0_CABLE_ID_DETECT_ADC_PIN
#define PCB_DP_UHBR_D0_CABLE_ID_DETECT_ADC_PIN()        (0)
#endif

#ifndef PCB_DP_UHBR_D1_CABLE_ID_DETECT_ADC_PIN
#define PCB_DP_UHBR_D1_CABLE_ID_DETECT_ADC_PIN()        (0)
#endif

#ifndef PCB_DP_UHBR_D2_CABLE_ID_DETECT_ADC_PIN
#define PCB_DP_UHBR_D2_CABLE_ID_DETECT_ADC_PIN()        (0)
#endif

//--------------------------------------------------
// Macro of DP Cable ID Switch Port Control
//--------------------------------------------------
#ifndef _DP_UHBR_CABLE_ID_SWITCH_PORT_DELAY_TIME
#define _DP_UHBR_CABLE_ID_SWITCH_PORT_DELAY_TIME        0 // Unit: ms
#endif

#ifndef PCB_DP_UHBR_CABLE_ID_SWITCH_PORT_CONTROL
#define PCB_DP_UHBR_CABLE_ID_SWITCH_PORT_CONTROL(DpInputPort)\
                                                        {\
                                                        }
#endif

//--------------------------------------------------
// Macro of DP Cable ID ADC Capacitor Time
//--------------------------------------------------
#ifndef _DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME
#define _DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME     300 // Unit: us(50 ~ 1000), 6* tau = 141.2us for Rp = 680kOhm, Rd = 100kOhm, C = 270pF
#endif

//--------------------------------------------------
// FLASH SPI Control Option
//--------------------------------------------------
#ifndef _FLASH_CLK_DRIVE_CURRENT
#define _FLASH_CLK_DRIVE_CURRENT                        _SPI_DRIVE_4_0MA
#endif

#ifndef _FLASH_SI_SO_CEB_DRIVE_CURRENT
#define _FLASH_SI_SO_CEB_DRIVE_CURRENT                  _SPI_DRIVE_4_0MA
#endif

#ifndef _FLASH_CLK_SLEW_RATE_CONTROL
#define _FLASH_CLK_SLEW_RATE_CONTROL                    _SPI_FAST_SLEW_RATE
#endif

#ifndef _FLASH_SI_SO_CEB_SLEW_RATE_CONTROL
#define _FLASH_SI_SO_CEB_SLEW_RATE_CONTROL              _SPI_FAST_SLEW_RATE
#endif


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#ifndef PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON()        {\
                                                        }
#endif

#ifndef PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON
#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                        {\
                                                        }
#endif

#ifndef PCB_GPIO_SETTING_POWER_NORMAL
#define PCB_GPIO_SETTING_POWER_NORMAL()                 {\
                                                        }
#endif

#ifndef PCB_GPIO_SETTING_POWER_SAVING
#define PCB_GPIO_SETTING_POWER_SAVING()                 {\
                                                        }
#endif

#ifndef PCB_GPIO_SETTING_POWER_DOWN
#define PCB_GPIO_SETTING_POWER_DOWN()                   {\
                                                        }
#endif


/////////////////////
// SWR Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of Pcb SWR Power Control
//-----------------------------------------------
#ifndef PCB_SWR_CORE_POWER_SETTING_AC_ON
#define PCB_SWR_CORE_POWER_SETTING_AC_ON()              {\
                                                        }
#endif

#ifndef PCB_SWR_CORE_POWER_SETTING_POWER_NORMAL
#define PCB_SWR_CORE_POWER_SETTING_POWER_NORMAL()       {\
                                                        }
#endif

#ifndef PCB_SWR_CORE_POWER_SETTING_POWER_SAVING
#define PCB_SWR_CORE_POWER_SETTING_POWER_SAVING()       {\
                                                        }
#endif

#ifndef PCB_SWR_CORE_POWER_SETTING_POWER_DOWN
#define PCB_SWR_CORE_POWER_SETTING_POWER_DOWN()         {\
                                                        }
#endif


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#ifndef _VCCK_OFF_POWER_ON
#define _VCCK_OFF_POWER_ON                              1
#endif

#ifndef _VCCK_OFF_POWER_OFF
#define _VCCK_OFF_POWER_OFF                             0
#endif

#ifndef _VCCK_OFF_TIME_POLLING_POWER_ON
#define _VCCK_OFF_TIME_POLLING_POWER_ON                 20
#endif

#ifndef PCB_VCCK_OFF_POWER
#define PCB_VCCK_OFF_POWER(x)                           {\
                                                        }
#endif

//-----------------------------------------------
// Macro of DDR Poewr Control
//-----------------------------------------------
#ifndef _DDR_POWER_ON
#define _DDR_POWER_ON                                   1
#endif

#ifndef _DDR_POWER_OFF
#define _DDR_POWER_OFF                                  0
#endif

#ifndef PCB_DDR_POWER
#define PCB_DDR_POWER(x)                                {\
                                                        }
#endif

//-----------------------------------------------
// Macro of DDR Poewr Release Time Control
//-----------------------------------------------
#ifndef _DDR_POWER_OFF_TIME
#define _DDR_POWER_OFF_TIME                             200
#endif

//-----------------------------------------------
// Macro of RX_LV Power Control
//-----------------------------------------------
#ifndef _RX_LV_POWER_ON
#define _RX_LV_POWER_ON                                 1
#endif

#ifndef _RX_LV_POWER_OFF
#define _RX_LV_POWER_OFF                                0
#endif

#ifndef PCB_SET_RX_LV_POWER
#define PCB_SET_RX_LV_POWER(x)                          {\
                                                        }
#endif

//-----------------------------------------------
// Macro of Power Board Low Power Pin High/Low
//-----------------------------------------------
#ifndef _LOW_POWER_ON
#define _LOW_POWER_ON                                   1
#endif

#ifndef _LOW_POWER_OFF
#define _LOW_POWER_OFF                                  0
#endif

#ifndef PCB_POWERBOARD_LOWPOWER
#define PCB_POWERBOARD_LOWPOWER(x)                      {\
                                                        }
#endif

//-----------------------------------------------
// Macro of 12V to 5V Regulator for MyDP or MHL
//-----------------------------------------------
#ifndef _REGULATOR_5V_ON
#define _REGULATOR_5V_ON                                0
#endif

#ifndef _REGULATOR_5V_OFF
#define _REGULATOR_5V_OFF                               1
#endif

#ifndef PCB_REGULATOR_5V_OUT
#define PCB_REGULATOR_5V_OUT(x)                         {\
                                                        }
#endif

//-----------------------------------------------
// Macro of External Port Controller Power Control
//-----------------------------------------------
#ifndef _D0_PORT_CTRL_POWER_ON
#define _D0_PORT_CTRL_POWER_ON                          1
#endif

#ifndef _D0_PORT_CTRL_POWER_OFF
#define _D0_PORT_CTRL_POWER_OFF                         0
#endif

#ifndef _D1_PORT_CTRL_POWER_ON
#define _D1_PORT_CTRL_POWER_ON                          1
#endif

#ifndef _D1_PORT_CTRL_POWER_OFF
#define _D1_PORT_CTRL_POWER_OFF                         0
#endif

#ifndef _D2_PORT_CTRL_POWER_ON
#define _D2_PORT_CTRL_POWER_ON                          1
#endif

#ifndef _D2_PORT_CTRL_POWER_OFF
#define _D2_PORT_CTRL_POWER_OFF                         0
#endif

#ifndef _P0_PORT_CTRL_POWER_ON
#define _P0_PORT_CTRL_POWER_ON                          1
#endif

#ifndef _P0_PORT_CTRL_POWER_OFF
#define _P0_PORT_CTRL_POWER_OFF                         0
#endif

#ifndef PCB_D0_PORT_CTRL_POWER
#define PCB_D0_PORT_CTRL_POWER(x)                       {\
                                                        }
#endif

#ifndef PCB_D1_PORT_CTRL_POWER
#define PCB_D1_PORT_CTRL_POWER(x)                       {\
                                                        }
#endif

#ifndef PCB_D2_PORT_CTRL_POWER
#define PCB_D2_PORT_CTRL_POWER(x)                       {\
                                                        }
#endif

#ifndef PCB_P0_PORT_CTRL_POWER
#define PCB_P0_PORT_CTRL_POWER(x)                       {\
                                                        }
#endif

#ifndef PCB_D0_PORT_CTRL_POWER_STATUS
#define PCB_D0_PORT_CTRL_POWER_STATUS()                 (_D0_PORT_CTRL_POWER_OFF)
#endif

#ifndef PCB_D1_PORT_CTRL_POWER_STATUS
#define PCB_D1_PORT_CTRL_POWER_STATUS()                 (_D1_PORT_CTRL_POWER_OFF)
#endif

#ifndef PCB_D2_PORT_CTRL_POWER_STATUS
#define PCB_D2_PORT_CTRL_POWER_STATUS()                 (_D2_PORT_CTRL_POWER_OFF)
#endif

#ifndef PCB_P0_PORT_CTRL_POWER_STATUS
#define PCB_P0_PORT_CTRL_POWER_STATUS()                 (_P0_PORT_CTRL_POWER_OFF)
#endif


//////////////////////
// HUB Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of TYPE_B VBUS POWER Detec
//-----------------------------------------------
#ifndef PCB_TYPE_B_VBUS_POWER_DETECT
#define PCB_TYPE_B_VBUS_POWER_DETECT()                  (_FALSE)
#endif

#ifndef PCB_D0_TYPE_B_VBUS_POWER_DETECT
#define PCB_D0_TYPE_B_VBUS_POWER_DETECT()               (_FALSE)
#endif

#ifndef PCB_D1_TYPE_B_VBUS_POWER_DETECT
#define PCB_D1_TYPE_B_VBUS_POWER_DETECT()               (_FALSE)
#endif

#ifndef PCB_D2_TYPE_B_VBUS_POWER_DETECT
#define PCB_D2_TYPE_B_VBUS_POWER_DETECT()               (_FALSE)
#endif

//-----------------------------------------------
// Macro of HUB VBus Power Control
//-----------------------------------------------
#ifndef _VBUS_0_POWER_ON
#define _VBUS_0_POWER_ON                                0
#endif

#ifndef _VBUS_0_POWER_OFF
#define _VBUS_0_POWER_OFF                               1
#endif

#ifndef _VBUS_1_POWER_ON
#define _VBUS_1_POWER_ON                                0
#endif

#ifndef _VBUS_1_POWER_OFF
#define _VBUS_1_POWER_OFF                               1
#endif

#ifndef PCB_HUB_0_BPWR_POWER
#define PCB_HUB_0_BPWR_POWER(x)                         {\
                                                        }
#endif

#ifndef PCB_HUB_1_BPWR_POWER
#define PCB_HUB_1_BPWR_POWER(x)                         {\
                                                        }
#endif

#ifndef PCB_HUB_BPWR_0_POWER_DETECT
#define PCB_HUB_BPWR_0_POWER_DETECT()                   (_VBUS_0_POWER_OFF)
#endif

#ifndef PCB_HUB_BPWR_1_POWER_DETECT
#define PCB_HUB_BPWR_1_POWER_DETECT()                   (_VBUS_1_POWER_OFF)
#endif


/////////////////////////
// U2 MUX Switch Macro //
/////////////////////////

//-----------------------------------------------
// Macro of U2 MUX VBus Power Control
//-----------------------------------------------
#ifndef _U2_MUX_ENABLE
#define _U2_MUX_ENABLE                                  0
#endif

#ifndef _U2_MUX_DISABLE
#define _U2_MUX_DISABLE                                 1
#endif

#ifndef _U2_MUX_SEL_LOW
#define _U2_MUX_SEL_LOW                                 0
#endif

#ifndef _U2_MUX_SEL_HIGH
#define _U2_MUX_SEL_HIGH                                1
#endif

#ifndef PCB_U2_MUX_SWITCH_CONTROL
#define PCB_U2_MUX_SWITCH_CONTROL(USBHubUfp)            {\
                                                        }
#endif


/////////////////////////
// U3 MUX Switch Macro //
/////////////////////////

//-----------------------------------------------
// Macro of MUX VBus Power Control
//-----------------------------------------------
#ifndef _U3_MUX_SEL_LOW
#define _U3_MUX_SEL_LOW                                 0
#endif

#ifndef _U3_MUX_SEL_HIGH
#define _U3_MUX_SEL_HIGH                                1
#endif

#ifndef PCB_U3_MUX_SWITCH_CONTROL
#define PCB_U3_MUX_SWITCH_CONTROL(USBHubUfp)            {\
                                                        }
#endif


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#ifndef _PANEL_CONTROL_ON
#define _PANEL_CONTROL_ON                               0
#endif

#ifndef _PANEL_CONTROL_OFF
#define _PANEL_CONTROL_OFF                              1
#endif

#ifndef PCB_PANEL_POWER
#define PCB_PANEL_POWER(x)                              {\
                                                        }
#endif

#ifndef PCB_PANEL_POWER_DETECT
#define PCB_PANEL_POWER_DETECT()                        (_PANEL_CONTROL_OFF)
#endif

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#ifndef _LIGHT_CONTROL_ON
#define _LIGHT_CONTROL_ON                               0
#endif

#ifndef _LIGHT_CONTROL_OFF
#define _LIGHT_CONTROL_OFF                              1
#endif

#ifndef PCB_BACKLIGHT_POWER_PIN
#define PCB_BACKLIGHT_POWER_PIN(x)                      {\
                                                        }
#endif

#ifndef PCB_BACKLIGHT_POWER_PIN_EXINT
#define PCB_BACKLIGHT_POWER_PIN_EXINT(x)                {\
                                                        }
#endif

#ifndef PCB_BACKLIGHT_POWER
#define PCB_BACKLIGHT_POWER(x)                          {\
                                                        }
#endif


//////////////////////////////////////
// eDPTx Panel Power Sequence Macro //
//////////////////////////////////////

//--------------------------------------------------
// eDPTx Panel Power Sequence Macro
//--------------------------------------------------
#ifndef PCB_DPTX0_POWER_SEQUENCE
#define PCB_DPTX0_POWER_SEQUENCE(x)                     {\
                                                        }
#endif

#ifndef PCB_DPTX1_POWER_SEQUENCE
#define PCB_DPTX1_POWER_SEQUENCE(x)                     {\
                                                        }
#endif

#ifndef PCB_DPTX2_POWER_SEQUENCE
#define PCB_DPTX2_POWER_SEQUENCE(x)                     {\
                                                        }
#endif

#ifndef PCB_DPTX3_POWER_SEQUENCE
#define PCB_DPTX3_POWER_SEQUENCE(x)                     {\
                                                        }
#endif


#ifndef _DPTX_POWER_SEQUENCE_PANEL_ON
#define _DPTX_POWER_SEQUENCE_PANEL_ON                   _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_HPD_ON
#define _DPTX_POWER_SEQUENCE_HPD_ON                     _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_LINK_TRAINING
#define _DPTX_POWER_SEQUENCE_LINK_TRAINING              _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_IDLE_PATTERN
#define _DPTX_POWER_SEQUENCE_IDLE_PATTERN               _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_VIDEO_PATTERN
#define _DPTX_POWER_SEQUENCE_VIDEO_PATTERN              _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_BACKLIGHT_ON
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_ON               _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_BACKLIGHT_OFF
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_OFF              _LOW
#endif

//--------------------------------------------------
// Definitions of Two Chip Data Exchange Option Setting
//--------------------------------------------------
#ifndef _TWO_CHIP_DATA_EXCHANGE_RX_SLAVE_ADDR
#define _TWO_CHIP_DATA_EXCHANGE_RX_SLAVE_ADDR           0x00
#endif

#ifndef _TWO_CHIP_DATA_EXCHANGE_TX_IIC_PIN
#define _TWO_CHIP_DATA_EXCHANGE_TX_IIC_PIN              _NO_IIC_PIN
#endif


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#ifndef _FLASH_WRITE_PROTECT_ENABLE
#define _FLASH_WRITE_PROTECT_ENABLE                     0
#endif

#ifndef _FLASH_WRITE_PROTECT_DISABLE
#define _FLASH_WRITE_PROTECT_DISABLE                    1
#endif

#ifndef PCB_FLASH_WRITE_PROTECT
#define PCB_FLASH_WRITE_PROTECT(x)                      {\
                                                        }
#endif

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#ifndef _EEPROM_WP_ENABLE
#define _EEPROM_WP_ENABLE                               1
#endif

#ifndef _EEPROM_WP_DISABLE
#define _EEPROM_WP_DISABLE                              0
#endif

#ifndef PCB_EEPROM_WRITE_PROTECT
#define PCB_EEPROM_WRITE_PROTECT(x)                     {\
                                                        }
#endif

#ifndef PCB_EEPROM_WRITE_PROTECT_DETECT
#define PCB_EEPROM_WRITE_PROTECT_DETECT()               (_EEPROM_WP_DISABLE)
#endif

//-----------------------------------------------
// Macro of TTS Flash write protect pin
//-----------------------------------------------
#ifndef _TTS_FLASH_WRITE_PROTECT_ENABLE
#define _TTS_FLASH_WRITE_PROTECT_ENABLE                 0
#endif

#ifndef _TTS_FLASH_WRITE_PROTECT_DISABLE
#define _TTS_FLASH_WRITE_PROTECT_DISABLE                1
#endif

#ifndef PCB_TTS_FLASH_WRITE_PROTECT
#define PCB_TTS_FLASH_WRITE_PROTECT(x)                  {\
                                                        }
#endif

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#ifndef _EDID_EEPROM_WP_ENABLE
#define _EDID_EEPROM_WP_ENABLE                          1
#endif

#ifndef _EDID_EEPROM_WP_DISABLE
#define _EDID_EEPROM_WP_DISABLE                         0
#endif

#ifndef PCB_A0_EDID_EEPROM_WRITE_PROTECT
#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                        }
#endif

#ifndef PCB_D2_EDID_EEPROM_WRITE_PROTECT
#define PCB_D2_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                        }
#endif

#ifndef PCB_D3_EDID_EEPROM_WRITE_PROTECT
#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                        }
#endif

#ifndef PCB_D4_EDID_EEPROM_WRITE_PROTECT
#define PCB_D4_EDID_EEPROM_WRITE_PROTECT(x)             {\
                                                        }
#endif

//-----------------------------------------------
// Macro of HDMI External EDID Switch : #if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//-----------------------------------------------
#ifndef _EEPROM_EDID_ENABLE
#define _EEPROM_EDID_ENABLE                             1
#endif

#ifndef _EEPROM_EDID_DISABLE
#define _EEPROM_EDID_DISABLE                            0
#endif

#ifndef PCB_MULTI_EDID_ALL_SWITCH_OFF
#define PCB_MULTI_EDID_ALL_SWITCH_OFF(port)             {\
                                                        }
#endif

#ifndef PCB_MULTI_EDID_SWITCH
#define PCB_MULTI_EDID_SWITCH(port, index)              {\
                                                        }
#endif

#ifndef PCB_MULTI_EDID_SWITCH_POWER_AC_ON
#define PCB_MULTI_EDID_SWITCH_POWER_AC_ON()             {\
                                                        }
#endif

#ifndef _HDMI_MULTI_EDID_TABLE
#define _HDMI_MULTI_EDID_TABLE                          ""
#endif


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#ifndef PCB_A0_PIN
#define PCB_A0_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D0_PIN
#define PCB_D0_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D1_PIN
#define PCB_D1_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D2_PIN
#define PCB_D2_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D3_PIN
#define PCB_D3_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D4_PIN
#define PCB_D4_PIN()                                    (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D12_PIN
#define PCB_D12_PIN()                                   (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D13_PIN
#define PCB_D13_PIN()                                   (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D14_PIN
#define PCB_D14_PIN()                                   (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D15_PIN
#define PCB_D15_PIN()                                   (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

//-----------------------------------------------
// Macro of HDMI External Switch
//-----------------------------------------------
#ifndef _SW_SEL_HDMI_D3
#define _SW_SEL_HDMI_D3                                 (0)
#endif

#ifndef _SW_SEL_HDMI_D12
#define _SW_SEL_HDMI_D12                                (1)
#endif

#ifndef _SW_SEL_HDMI_D13
#define _SW_SEL_HDMI_D13                                (2)
#endif

#ifndef _SW_SEL_HDMI_D4
#define _SW_SEL_HDMI_D4                                 (0)
#endif

#ifndef _SW_SEL_HDMI_D14
#define _SW_SEL_HDMI_D14                                (1)
#endif

#ifndef _SW_SEL_HDMI_D15
#define _SW_SEL_HDMI_D15                                (2)
#endif

#ifndef PCB_HDMI_SW_SELECT
#define PCB_HDMI_SW_SELECT(x)                           {SET_GPIO_PIN_EMPTY();}
#endif

#ifndef PCB_GET_HDMI_SW_SELECT
#define PCB_GET_HDMI_SW_SELECT()                        (GET_GPIO_PIN_EMPTY())
#endif

//-----------------------------------------------
// Macro of Type-C Cable Connect
//-----------------------------------------------
// For DP Type-C _D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#ifndef PCB_D0_CC_ATTACH
#define PCB_D0_CC_ATTACH()                              (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)
#endif

// For DP Type-C _D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#ifndef PCB_D1_CC_ATTACH
#define PCB_D1_CC_ATTACH()                              (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)
#endif

// For DP Type-C _D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#ifndef PCB_D2_CC_ATTACH
#define PCB_D2_CC_ATTACH()                              (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)
#endif

// For DP Type-C _P0_DP_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#ifndef PCB_P0_CC_ATTACH
#define PCB_P0_CC_ATTACH()                              (_PCB_DP_TYPE_C_CC_NOT_ATTACH_LEVEL)
#endif

// For DP Type-C _D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#ifndef PCB_D0_ALT_MODE_READY
#define PCB_D0_ALT_MODE_READY()                         (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#endif

// For DP Type-C _D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#ifndef PCB_D1_ALT_MODE_READY
#define PCB_D1_ALT_MODE_READY()                         (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#endif

// For DP Type-C _D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#ifndef PCB_D2_ALT_MODE_READY
#define PCB_D2_ALT_MODE_READY()                         (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#endif

// For DP Type-C _P0_DP_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO
#ifndef PCB_P0_ALT_MODE_READY
#define PCB_P0_ALT_MODE_READY()                         (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#endif

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#ifndef GET_PCB_D0_DP_SOURCE_POWER
#define GET_PCB_D0_DP_SOURCE_POWER()                    (_LOW)
#endif

#ifndef GET_PCB_D1_DP_SOURCE_POWER
#define GET_PCB_D1_DP_SOURCE_POWER()                    (_LOW)
#endif

#ifndef GET_PCB_D2_DP_SOURCE_POWER
#define GET_PCB_D2_DP_SOURCE_POWER()                    (_LOW)
#endif

//-----------------------------------------------
// Macro of DP Source Power When under Pin E Type and Aux PN Swap
//-----------------------------------------------
#ifndef GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP
#define GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP()            (_LOW)
#endif

#ifndef GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP
#define GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP()            (_LOW)
#endif

#ifndef GET_PCB_D2_DP_SOURCE_POWER_PN_SWAP
#define GET_PCB_D2_DP_SOURCE_POWER_PN_SWAP()            (_LOW)
#endif

//-----------------------------------------------
// Aux PN 1M Pull High / low Swap Control
//-----------------------------------------------
#ifndef _AUX_PN_1M_PULL_HI_LOW_SWAP_ON
#define _AUX_PN_1M_PULL_HI_LOW_SWAP_ON                  (1)
#endif

#ifndef _AUX_PN_1M_PULL_HI_LOW_SWAP_OFF
#define _AUX_PN_1M_PULL_HI_LOW_SWAP_OFF                 (0)
#endif

#ifndef PCB_D0_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(x)               {\
                                                        }
#endif

#ifndef PCB_D1_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(x)               {\
                                                        }
#endif

#ifndef PCB_D2_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_D2_AUX_PN_1M_PULL_H_L_SWAP(x)               {\
                                                        }
#endif

#ifndef PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP()            (_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF)
#endif

#ifndef PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP()            (_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF)
#endif

#ifndef PCB_GET_D2_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_GET_D2_AUX_PN_1M_PULL_H_L_SWAP()            (_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF)
#endif


/////////////////////////////
// DP CableID Config1 Ctrl //
/////////////////////////////

//-----------------------------------------------
// Macro of Dp CableID Detection Config1 Pin High/Low
//-----------------------------------------------
#ifndef _D0_CABLEID_DET_CONFIG1_HIGH
#define _D0_CABLEID_DET_CONFIG1_HIGH                    1
#endif

#ifndef _D0_CABLEID_DET_CONFIG1_LOW
#define _D0_CABLEID_DET_CONFIG1_LOW                     0
#endif

#ifndef _D1_CABLEID_DET_CONFIG1_HIGH
#define _D1_CABLEID_DET_CONFIG1_HIGH                    1
#endif

#ifndef _D1_CABLEID_DET_CONFIG1_LOW
#define _D1_CABLEID_DET_CONFIG1_LOW                     0
#endif

#ifndef _D2_CABLEID_DET_CONFIG1_HIGH
#define _D2_CABLEID_DET_CONFIG1_HIGH                    1
#endif

#ifndef _D2_CABLEID_DET_CONFIG1_LOW
#define _D2_CABLEID_DET_CONFIG1_LOW                     0
#endif

#ifndef PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1
#define PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1(x)       {\
                                                        }
#endif

#ifndef PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1
#define PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1(x)       {\
                                                        }
#endif

#ifndef PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1
#define PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1(x)       {\
                                                        }
#endif


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#ifndef _D0_HOT_PLUG_HIGH
#define _D0_HOT_PLUG_HIGH                               1
#endif

#ifndef _D0_HOT_PLUG_LOW
#define _D0_HOT_PLUG_LOW                                0
#endif

#ifndef _D1_HOT_PLUG_HIGH
#define _D1_HOT_PLUG_HIGH                               1
#endif

#ifndef _D1_HOT_PLUG_LOW
#define _D1_HOT_PLUG_LOW                                0
#endif

#ifndef _D2_HOT_PLUG_HIGH
#define _D2_HOT_PLUG_HIGH                               1
#endif

#ifndef _D2_HOT_PLUG_LOW
#define _D2_HOT_PLUG_LOW                                0
#endif

#ifndef _D3_HOT_PLUG_HIGH
#define _D3_HOT_PLUG_HIGH                               1
#endif

#ifndef _D3_HOT_PLUG_LOW
#define _D3_HOT_PLUG_LOW                                0
#endif

#ifndef _D4_HOT_PLUG_HIGH
#define _D4_HOT_PLUG_HIGH                               1
#endif

#ifndef _D4_HOT_PLUG_LOW
#define _D4_HOT_PLUG_LOW                                0
#endif

#ifndef PCB_D0_HOTPLUG
#define PCB_D0_HOTPLUG(x)                               {\
                                                        }
#endif

#ifndef PCB_D1_HOTPLUG
#define PCB_D1_HOTPLUG(x)                               {\
                                                        }
#endif

#ifndef PCB_D2_HOTPLUG
#define PCB_D2_HOTPLUG(x)                               {\
                                                        }
#endif

#ifndef PCB_D3_HOTPLUG
#define PCB_D3_HOTPLUG(x)                               {\
                                                        }
#endif

#ifndef PCB_D4_HOTPLUG
#define PCB_D4_HOTPLUG(x)                               {\
                                                        }
#endif

#ifndef PCB_D0_HOTPLUG_DETECT
#define PCB_D0_HOTPLUG_DETECT()                         (_D0_HOT_PLUG_LOW)
#endif

#ifndef PCB_D1_HOTPLUG_DETECT
#define PCB_D1_HOTPLUG_DETECT()                         (_D1_HOT_PLUG_LOW)
#endif

#ifndef PCB_D2_HOTPLUG_DETECT
#define PCB_D2_HOTPLUG_DETECT()                         (_D2_HOT_PLUG_LOW)
#endif

#ifndef PCB_D3_HOTPLUG_DETECT
#define PCB_D3_HOTPLUG_DETECT()                         (_D3_HOT_PLUG_LOW)
#endif

#ifndef PCB_D4_HOTPLUG_DETECT
#define PCB_D4_HOTPLUG_DETECT()                         (_D4_HOT_PLUG_LOW)
#endif


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#ifndef PCB_PWM_SETTING
#define PCB_PWM_SETTING()                               {\
                                                        }
#endif

#ifndef PCB_BACKLIGHT_PWM
#define PCB_BACKLIGHT_PWM(x)                            {\
                                                        }
#endif

#ifndef PCB_GET_BACKLIGHT_PWM
#define PCB_GET_BACKLIGHT_PWM()                         (0xFF)
#endif


//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#ifndef PCB_SW_IIC_SDA_SET
#define PCB_SW_IIC_SDA_SET()                            {\
                                                        }
#endif

#ifndef PCB_SW_IIC_SDA_CLR
#define PCB_SW_IIC_SDA_CLR()                            {\
                                                        }
#endif

#ifndef PCB_SW_IIC_SDA_CHK
#define PCB_SW_IIC_SDA_CHK(x)                           {\
                                                        }
#endif

#ifndef PCB_SW_IIC_SCL_SET
#define PCB_SW_IIC_SCL_SET()                            {\
                                                        }
#endif

#ifndef PCB_SW_IIC_SCL_CLR
#define PCB_SW_IIC_SCL_CLR()                            {\
                                                        }
#endif

#ifndef PCB_SW_IIC_SCL_CHK
#define PCB_SW_IIC_SCL_CHK(x)                           {\
                                                        }
#endif


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#ifndef _LED_ON
#define _LED_ON                                         1
#endif

#ifndef _LED_OFF
#define _LED_OFF                                        0
#endif

#ifndef PCB_LED_AC_ON_INITIAL
#define PCB_LED_AC_ON_INITIAL()                         {\
                                                        }
#endif

#ifndef PCB_LED_ACTIVE
#define PCB_LED_ACTIVE()                                {\
                                                        }
#endif

#ifndef PCB_LED_IDLE
#define PCB_LED_IDLE()                                  {\
                                                        }
#endif

#ifndef PCB_LED_POWER_SAVING
#define PCB_LED_POWER_SAVING()                          {\
                                                        }
#endif

#ifndef PCB_LED_ON
#define PCB_LED_ON()                                    {\
                                                        }
#endif

#ifndef PCB_LED_OFF
#define PCB_LED_OFF()                                   {\
                                                        }
#endif

#ifndef PCB_LED_TYPE1
#define PCB_LED_TYPE1()                                 {\
                                                        }
#endif

#ifndef PCB_LED_TYPE2
#define PCB_LED_TYPE2()                                 {\
                                                        }
#endif

#ifndef PCB_LED_TYPE3
#define PCB_LED_TYPE3()                                 {\
                                                        }
#endif

#ifndef PCB_LED_TYPE4
#define PCB_LED_TYPE4()                                 {\
                                                        }
#endif

#ifndef PCB_LED_TYPE5
#define PCB_LED_TYPE5()                                 {\
                                                        }
#endif

#ifndef PCB_LED_TYPE_FLASH
#define PCB_LED_TYPE_FLASH()                            {\
                                                        }
#endif


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#ifndef PCB_ADKEY0
#define PCB_ADKEY0()                                    (_FALSE)
#endif

#ifndef PCB_ADKEY1
#define PCB_ADKEY1()                                    (_FALSE)
#endif

#ifndef PCB_ADKEY2
#define PCB_ADKEY2()                                    (_FALSE)
#endif

#ifndef PCB_ADKEY3
#define PCB_ADKEY3()                                    (_FALSE)
#endif

#ifndef PCB_KEY_STATE
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)           {\
                                                        }
#endif


////////////////////
// GPIO Key Macro //
////////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#ifndef PCB_KEY_STATE
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)           {\
                                                        }
#endif


//////////////////////
// PMIC Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of PMIC Power Control
//-----------------------------------------------
#ifndef _D0_PMIC_POWER_ON
#define _D0_PMIC_POWER_ON                               1
#endif

#ifndef _D0_PMIC_POWER_OFF
#define _D0_PMIC_POWER_OFF                              0
#endif

#ifndef _D1_PMIC_POWER_ON
#define _D1_PMIC_POWER_ON                               1
#endif

#ifndef _D1_PMIC_POWER_OFF
#define _D1_PMIC_POWER_OFF                              0
#endif

#ifndef _P0_PMIC_POWER_ON
#define _P0_PMIC_POWER_ON                               1
#endif

#ifndef _P0_PMIC_POWER_OFF
#define _P0_PMIC_POWER_OFF                              0
#endif

#ifndef _ADAPTOR_PMIC_POWER_ON
#define _ADAPTOR_PMIC_POWER_ON                          1
#endif

#ifndef _ADAPTOR_PMIC_POWER_OFF
#define _ADAPTOR_PMIC_POWER_OFF                         0
#endif


#ifndef PCB_D0_PMIC_POWER
#define PCB_D0_PMIC_POWER(x)                            {\
                                                        }
#endif

#ifndef PCB_D1_PMIC_POWER
#define PCB_D1_PMIC_POWER(x)                            {\
                                                        }
#endif

#ifndef PCB_P0_PMIC_POWER
#define PCB_P0_PMIC_POWER(x)                            {\
                                                        }
#endif

#ifndef PCB_ADAPTOR_PMIC_POWER
#define PCB_ADAPTOR_PMIC_POWER(x)                       {\
                                                        }
#endif

//-----------------------------------------------
// Macro of Pmic FRWEN Enable Control
//-----------------------------------------------
#ifndef _D0_PMIC_FOWARD_CONTROL_ON
#define _D0_PMIC_FOWARD_CONTROL_ON                      1
#endif

#ifndef _D0_PMIC_FOWARD_CONTROL_OFF
#define _D0_PMIC_FOWARD_CONTROL_OFF                     0
#endif

#ifndef _D1_PMIC_FOWARD_CONTROL_ON
#define _D1_PMIC_FOWARD_CONTROL_ON                      1
#endif

#ifndef _D1_PMIC_FOWARD_CONTROL_OFF
#define _D1_PMIC_FOWARD_CONTROL_OFF                     0
#endif

#ifndef _P0_PMIC_FOWARD_CONTROL_ON
#define _P0_PMIC_FOWARD_CONTROL_ON                      1
#endif

#ifndef _P0_PMIC_FOWARD_CONTROL_OFF
#define _P0_PMIC_FOWARD_CONTROL_OFF                     0
#endif

#ifndef _ADAPTOR_PMIC_FOWARD_CONTROL_ON
#define _ADAPTOR_PMIC_FOWARD_CONTROL_ON                 1
#endif

#ifndef _ADAPTOR_PMIC_FOWARD_CONTROL_OFF
#define _ADAPTOR_PMIC_FOWARD_CONTROL_OFF                0
#endif

#ifndef PCB_D0_PMIC_FOWARD_CONTROL
#define PCB_D0_PMIC_FOWARD_CONTROL(x)                   {\
                                                        }
#endif

#ifndef PCB_D1_PMIC_FOWARD_CONTROL
#define PCB_D1_PMIC_FOWARD_CONTROL(x)                   {\
                                                        }
#endif

#ifndef PCB_P0_PMIC_FOWARD_CONTROL
#define PCB_P0_PMIC_FOWARD_CONTROL(x)                   {\
                                                        }
#endif

#ifndef PCB_ADAPTOR_PMIC_FOWARD_CONTROL
#define PCB_ADAPTOR_PMIC_FOWARD_CONTROL(x)              {\
                                                        }
#endif

//-----------------------------------------------
// Macro of Pmic FRW Power Good
//-----------------------------------------------
#ifndef _D0_PMIC_FRWPG_ON
#define _D0_PMIC_FRWPG_ON                               1
#endif

#ifndef _D0_PMIC_FRWPG_OFF
#define _D0_PMIC_FRWPG_OFF                              0
#endif

#ifndef _D1_PMIC_FRWPG_ON
#define _D1_PMIC_FRWPG_ON                               1
#endif

#ifndef _D1_PMIC_FRWPG_OFF
#define _D1_PMIC_FRWPG_OFF                              0
#endif

#ifndef _P0_PMIC_FRWPG_ON
#define _P0_PMIC_FRWPG_ON                               1
#endif

#ifndef _P0_PMIC_FRWPG_OFF
#define _P0_PMIC_FRWPG_OFF                              0
#endif

#ifndef _ADAPTOR_PMIC_FRWPG_ON
#define _ADAPTOR_PMIC_FRWPG_ON                          1
#endif

#ifndef _ADAPTOR_PMIC_FRWPG_OFF
#define _ADAPTOR_PMIC_FRWPG_OFF                         0
#endif

#ifndef PCB_D0_PMIC_FRWPG_DETECT
#define PCB_D0_PMIC_FRWPG_DETECT()                      (_D0_PMIC_FRWPG_OFF)
#endif

#ifndef PCB_D0_PMIC_FRWPG_DETECT
#define PCB_D0_PMIC_FRWPG_DETECT()                      (_D0_PMIC_FRWPG_OFF)
#endif

#ifndef PCB_D1_PMIC_FRWPG_DETECT
#define PCB_D1_PMIC_FRWPG_DETECT()                      (_D1_PMIC_FRWPG_OFF)
#endif

#ifndef PCB_D1_PMIC_FRWPG_DETECT
#define PCB_D1_PMIC_FRWPG_DETECT()                      (_D1_PMIC_FRWPG_OFF)
#endif

#ifndef PCB_P0_PMIC_FRWPG_DETECT
#define PCB_P0_PMIC_FRWPG_DETECT()                      (_P0_PMIC_FRWPG_OFF)
#endif

#ifndef PCB_P0_PMIC_FRWPG_DETECT
#define PCB_P0_PMIC_FRWPG_DETECT()                      (_P0_PMIC_FRWPG_OFF)
#endif

#ifndef PCB_ADAPTOR_PMIC_FRWPG_DETECT
#define PCB_ADAPTOR_PMIC_FRWPG_DETECT()                 (_ADAPTOR_PMIC_FRWPG_OFF)
#endif

#ifndef PCB_ADAPTOR_PMIC_FRWPG_DETECT
#define PCB_ADAPTOR_PMIC_FRWPG_DETECT()                 (_ADAPTOR_PMIC_FRWPG_OFF)
#endif

//-----------------------------------------------
// Macro of Pmic RVSEN Enable Control
//-----------------------------------------------
#ifndef _D0_PMIC_REVERSE_CONTROL_ON
#define _D0_PMIC_REVERSE_CONTROL_ON                     1
#endif

#ifndef _D0_PMIC_REVERSE_CONTROL_OFF
#define _D0_PMIC_REVERSE_CONTROL_OFF                    0
#endif

#ifndef _D1_PMIC_REVERSE_CONTROL_ON
#define _D1_PMIC_REVERSE_CONTROL_ON                     1
#endif

#ifndef _D1_PMIC_REVERSE_CONTROL_OFF
#define _D1_PMIC_REVERSE_CONTROL_OFF                    0
#endif

#ifndef _P0_PMIC_REVERSE_CONTROL_ON
#define _P0_PMIC_REVERSE_CONTROL_ON                     1
#endif

#ifndef _P0_PMIC_REVERSE_CONTROL_OFF
#define _P0_PMIC_REVERSE_CONTROL_OFF                    0
#endif

#ifndef _ADAPTOR_PMIC_REVERSE_CONTROL_ON
#define _ADAPTOR_PMIC_REVERSE_CONTROL_ON                1
#endif

#ifndef _ADAPTOR_PMIC_REVERSE_CONTROL_OFF
#define _ADAPTOR_PMIC_REVERSE_CONTROL_OFF               0
#endif

#ifndef PCB_D0_PMIC_REVERSE_CONTROL
#define PCB_D0_PMIC_REVERSE_CONTROL(x)                  {\
                                                        }
#endif

#ifndef PCB_D1_PMIC_REVERSE_CONTROL
#define PCB_D1_PMIC_REVERSE_CONTROL(x)                  {\
                                                        }
#endif

#ifndef PCB_P0_PMIC_REVERSE_CONTROL
#define PCB_P0_PMIC_REVERSE_CONTROL(x)                  {\
                                                        }
#endif

#ifndef PCB_ADAPTOR_PMIC_REVERSE_CONTROL
#define PCB_ADAPTOR_PMIC_REVERSE_CONTROL(x)             {\
                                                        }
#endif

//-----------------------------------------------
// Macro of Pmic RVS Power Good
//-----------------------------------------------
#ifndef _D0_PMIC_RVSPG_ON
#define _D0_PMIC_RVSPG_ON                               1
#endif

#ifndef _D0_PMIC_RVSPG_OFF
#define _D0_PMIC_RVSPG_OFF                              0
#endif

#ifndef _D1_PMIC_RVSPG_ON
#define _D1_PMIC_RVSPG_ON                               1
#endif

#ifndef _D1_PMIC_RVSPG_OFF
#define _D1_PMIC_RVSPG_OFF                              0
#endif

#ifndef _P0_PMIC_RVSPG_ON
#define _P0_PMIC_RVSPG_ON                               1
#endif

#ifndef _P0_PMIC_RVSPG_OFF
#define _P0_PMIC_RVSPG_OFF                              0
#endif

#ifndef _ADAPTOR_PMIC_RVSPG_ON
#define _ADAPTOR_PMIC_RVSPG_ON                          1
#endif

#ifndef _ADAPTOR_PMIC_RVSPG_OFF
#define _ADAPTOR_PMIC_RVSPG_OFF                         0
#endif

#ifndef PCB_D0_PMIC_RVSPG_DETECT
#define PCB_D0_PMIC_RVSPG_DETECT()                      (_D0_PMIC_RVSPG_OFF)
#endif

#ifndef PCB_D1_PMIC_RVSPG_DETECT
#define PCB_D1_PMIC_RVSPG_DETECT()                      (_D1_PMIC_RVSPG_OFF)
#endif

#ifndef PCB_P0_PMIC_RVSPG_DETECT
#define PCB_P0_PMIC_RVSPG_DETECT()                      (_P0_PMIC_RVSPG_OFF)
#endif

#ifndef PCB_ADAPTOR_PMIC_RVSPG_DETECT
#define PCB_ADAPTOR_PMIC_RVSPG_DETECT()                 (_ADAPTOR_PMIC_RVSPG_OFF)
#endif

//-----------------------------------------------
// Macro of PMIC Interrupt Detect
//-----------------------------------------------
#ifndef _D0_PMIC_INTERRUPT_ON
#define _D0_PMIC_INTERRUPT_ON                           1
#endif

#ifndef _D0_PMIC_INTERRUPT_OFF
#define _D0_PMIC_INTERRUPT_OFF                          0
#endif

#ifndef _D1_PMIC_INTERRUPT_ON
#define _D1_PMIC_INTERRUPT_ON                           1
#endif

#ifndef _D1_PMIC_INTERRUPT_OFF
#define _D1_PMIC_INTERRUPT_OFF                          0
#endif

#ifndef _P0_PMIC_INTERRUPT_ON
#define _P0_PMIC_INTERRUPT_ON                           1
#endif

#ifndef _P0_PMIC_INTERRUPT_OFF
#define _P0_PMIC_INTERRUPT_OFF                          0
#endif

#ifndef _ADAPTOR_PMIC_INTERRUPT_ON
#define _ADAPTOR_PMIC_INTERRUPT_ON                      1
#endif

#ifndef _ADAPTOR_PMIC_INTERRUPT_OFF
#define _ADAPTOR_PMIC_INTERRUPT_OFF                     0
#endif

#ifndef PCB_D0_PMIC_INTERRUPT_DETECT
#define PCB_D0_PMIC_INTERRUPT_DETECT()                  (_D0_PMIC_INTERRUPT_OFF)
#endif

#ifndef PCB_D1_PMIC_INTERRUPT_DETECT
#define PCB_D1_PMIC_INTERRUPT_DETECT()                  (_D1_PMIC_INTERRUPT_OFF)
#endif

#ifndef PCB_P0_PMIC_INTERRUPT_DETECT
#define PCB_P0_PMIC_INTERRUPT_DETECT()                  (_P0_PMIC_INTERRUPT_OFF)
#endif

#ifndef PCB_ADAPTOR_PMIC_INTERRUPT_DETECT
#define PCB_ADAPTOR_PMIC_INTERRUPT_DETECT()             (_ADAPTOR_PMIC_INTERRUPT_OFF)
#endif

//-----------------------------------------------
// Macro of Pmic ALERT Detect
//-----------------------------------------------
#ifndef _D0_PMIC_ALERT_ON
#define _D0_PMIC_ALERT_ON                               1
#endif

#ifndef _D0_PMIC_ALERT_OFF
#define _D0_PMIC_ALERT_OFF                              0
#endif

#ifndef _D1_PMIC_ALERT_ON
#define _D1_PMIC_ALERT_ON                               1
#endif

#ifndef _D1_PMIC_ALERT_OFF
#define _D1_PMIC_ALERT_OFF                              0
#endif

#ifndef _P0_PMIC_ALERT_ON
#define _P0_PMIC_ALERT_ON                               1
#endif

#ifndef _P0_PMIC_ALERT_OFF
#define _P0_PMIC_ALERT_OFF                              0
#endif

#ifndef _ADAPTOR_PMIC_ALERT_ON
#define _ADAPTOR_PMIC_ALERT_ON                          1
#endif

#ifndef _ADAPTOR_PMIC_ALERT_OFF
#define _ADAPTOR_PMIC_ALERT_OFF                         0
#endif

#ifndef PCB_D0_PMIC_ALERT_DETECT
#define PCB_D0_PMIC_ALERT_DETECT()                      (_D0_PMIC_ALERT_OFF)
#endif

#ifndef PCB_D1_PMIC_ALERT_DETECT
#define PCB_D1_PMIC_ALERT_DETECT()                      (_D1_PMIC_ALERT_OFF)
#endif

#ifndef PCB_P0_PMIC_ALERT_DETECT
#define PCB_P0_PMIC_ALERT_DETECT()                      (_P0_PMIC_ALERT_OFF)
#endif

#ifndef PCB_ADAPTOR_PMIC_ALERT_DETECT
#define PCB_ADAPTOR_PMIC_ALERT_DETECT()                 (_ADAPTOR_PMIC_ALERT_OFF)
#endif

//-----------------------------------------------
// Macro of Pmic Power Detect
//-----------------------------------------------
#ifndef _D0_PMIC_POWER_TURN_ON
#define _D0_PMIC_POWER_TURN_ON                          1
#endif

#ifndef _D0_PMIC_POWER_TURN_OFF
#define _D0_PMIC_POWER_TURN_OFF                         0
#endif

#ifndef _D1_PMIC_POWER_TURN_ON
#define _D1_PMIC_POWER_TURN_ON                          1
#endif

#ifndef _D1_PMIC_POWER_TURN_OFF
#define _D1_PMIC_POWER_TURN_OFF                         0
#endif

#ifndef _P0_PMIC_POWER_TURN_ON
#define _P0_PMIC_POWER_TURN_ON                          1
#endif

#ifndef _P0_PMIC_POWER_TURN_OFF
#define _P0_PMIC_POWER_TURN_OFF                         0
#endif

#ifndef _ADAPTOR_PMIC_POWER_TURN_ON
#define _ADAPTOR_PMIC_POWER_TURN_ON                     1
#endif

#ifndef _ADAPTOR_PMIC_POWER_TURN_OFF
#define _ADAPTOR_PMIC_POWER_TURN_OFF                    0
#endif

#ifndef PCB_D0_PMIC_POWER_DETECT
#define PCB_D0_PMIC_POWER_DETECT()                      (_D0_PMIC_POWER_TURN_OFF)
#endif

#ifndef PCB_D1_PMIC_POWER_DETECT
#define PCB_D1_PMIC_POWER_DETECT()                      (_D1_PMIC_POWER_TURN_OFF)
#endif

#ifndef PCB_P0_PMIC_POWER_DETECT
#define PCB_P0_PMIC_POWER_DETECT()                      (_P0_PMIC_POWER_TURN_OFF)
#endif

#ifndef PCB_ADAPTOR_PMIC_POWER_DETECT
#define PCB_ADAPTOR_PMIC_POWER_DETECT()                 (_ADAPTOR_PMIC_POWER_TURN_OFF)
#endif

//-----------------------------------------------
// Macro of PMIC VBUS Power SOURCE Control
//-----------------------------------------------
#ifndef _D0_PMIC_VBUS_SOURCE_SWITCH_ON
#define _D0_PMIC_VBUS_SOURCE_SWITCH_ON                  0
#endif

#ifndef _D0_PMIC_VBUS_SOURCE_SWITCH_OFF
#define _D0_PMIC_VBUS_SOURCE_SWITCH_OFF                 1
#endif

#ifndef _D1_PMIC_VBUS_SOURCE_SWITCH_ON
#define _D1_PMIC_VBUS_SOURCE_SWITCH_ON                  0
#endif

#ifndef _D1_PMIC_VBUS_SOURCE_SWITCH_OFF
#define _D1_PMIC_VBUS_SOURCE_SWITCH_OFF                 1
#endif

#ifndef _P0_PMIC_VBUS_SOURCE_SWITCH_ON
#define _P0_PMIC_VBUS_SOURCE_SWITCH_ON                  0
#endif

#ifndef _P0_PMIC_VBUS_SOURCE_SWITCH_OFF
#define _P0_PMIC_VBUS_SOURCE_SWITCH_OFF                 1
#endif

#ifndef _ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON
#define _ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON             0
#endif

#ifndef _ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF
#define _ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF            1
#endif

#ifndef PCB_D0_PMIC_VBUS_SOURCE_CONTROL
#define PCB_D0_PMIC_VBUS_SOURCE_CONTROL(x)              {\
                                                        }
#endif

#ifndef PCB_D1_PMIC_VBUS_SOURCE_CONTROL
#define PCB_D1_PMIC_VBUS_SOURCE_CONTROL(x)              {\
                                                        }
#endif

#ifndef PCB_P0_PMIC_VBUS_SOURCE_CONTROL
#define PCB_P0_PMIC_VBUS_SOURCE_CONTROL(x)              {\
                                                        }
#endif

#ifndef PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL
#define PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(x)         {\
                                                        }
#endif

//-----------------------------------------------
// Macro of PMIC VBUS Power SINK Control
//-----------------------------------------------
#ifndef _D0_PMIC_VBUS_SINK_SWITCH_ON
#define _D0_PMIC_VBUS_SINK_SWITCH_ON                    1
#endif

#ifndef _D0_PMIC_VBUS_SINK_SWITCH_OFF
#define _D0_PMIC_VBUS_SINK_SWITCH_OFF                   0
#endif

#ifndef _D1_PMIC_VBUS_SINK_SWITCH_ON
#define _D1_PMIC_VBUS_SINK_SWITCH_ON                    1
#endif

#ifndef _D1_PMIC_VBUS_SINK_SWITCH_OFF
#define _D1_PMIC_VBUS_SINK_SWITCH_OFF                   0
#endif

#ifndef _P0_PMIC_VBUS_SINK_SWITCH_ON
#define _P0_PMIC_VBUS_SINK_SWITCH_ON                    1
#endif

#ifndef _P0_PMIC_VBUS_SINK_SWITCH_OFF
#define _P0_PMIC_VBUS_SINK_SWITCH_OFF                   0
#endif

#ifndef _ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON
#define _ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON               1
#endif

#ifndef _ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF
#define _ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF              0
#endif

#ifndef PCB_D0_PMIC_VBUS_SINK_CONTROL
#define PCB_D0_PMIC_VBUS_SINK_CONTROL(x)                {\
                                                        }
#endif

#ifndef PCB_D1_PMIC_VBUS_SINK_CONTROL
#define PCB_D1_PMIC_VBUS_SINK_CONTROL(x)                {\
                                                        }
#endif

#ifndef PCB_P0_PMIC_VBUS_SINK_CONTROL
#define PCB_P0_PMIC_VBUS_SINK_CONTROL(x)                {\
                                                        }
#endif

#ifndef PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL
#define PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(x)           {\
                                                        }
#endif

//-----------------------------------------------
// Macro of PMIC Discharge Control
//-----------------------------------------------
#ifndef _D0_PMIC_VBUS_DISCHARGE_ON
#define _D0_PMIC_VBUS_DISCHARGE_ON                      1
#endif

#ifndef _D0_PMIC_VBUS_DISCHARGE_OFF
#define _D0_PMIC_VBUS_DISCHARGE_OFF                     0
#endif

#ifndef _D1_PMIC_VBUS_DISCHARGE_ON
#define _D1_PMIC_VBUS_DISCHARGE_ON                      1
#endif

#ifndef _D1_PMIC_VBUS_DISCHARGE_OFF
#define _D1_PMIC_VBUS_DISCHARGE_OFF                     0
#endif

#ifndef _P0_PMIC_VBUS_DISCHARGE_ON
#define _P0_PMIC_VBUS_DISCHARGE_ON                      1
#endif

#ifndef _P0_PMIC_VBUS_DISCHARGE_OFF
#define _P0_PMIC_VBUS_DISCHARGE_OFF                     0
#endif

#ifndef _ADAPTOR_PMIC_VBUS_DISCHARGE_ON
#define _ADAPTOR_PMIC_VBUS_DISCHARGE_ON                 1
#endif

#ifndef _ADAPTOR_PMIC_VBUS_DISCHARGE_OFF
#define _ADAPTOR_PMIC_VBUS_DISCHARGE_OFF                0
#endif

#ifndef PCB_D0_VBUS_DISCHARGE_CONTROL
#define PCB_D0_VBUS_DISCHARGE_CONTROL(x)                {\
                                                        }
#endif

#ifndef PCB_D1_VBUS_DISCHARGE_CONTROL
#define PCB_D1_VBUS_DISCHARGE_CONTROL(x)                {\
                                                        }
#endif

#ifndef PCB_P0_VBUS_DISCHARGE_CONTROL
#define PCB_P0_VBUS_DISCHARGE_CONTROL(x)                {\
                                                        }
#endif

#ifndef PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL
#define PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(x)           {\
                                                        }
#endif


/////////////////////////////
// Type-C ADC Switch Macro //
/////////////////////////////

//-----------------------------------------------
// Macro of Type-C ADC Switch Control
//-----------------------------------------------
#ifndef _D0_TYPE_C_ADC_SWITCH_ON
#define _D0_TYPE_C_ADC_SWITCH_ON                        0
#endif

#ifndef _D0_TYPE_C_ADC_SWITCH_OFF
#define _D0_TYPE_C_ADC_SWITCH_OFF                       1
#endif

#ifndef _D1_TYPE_C_ADC_SWITCH_ON
#define _D1_TYPE_C_ADC_SWITCH_ON                        0
#endif

#ifndef _D1_TYPE_C_ADC_SWITCH_OFF
#define _D1_TYPE_C_ADC_SWITCH_OFF                       1
#endif

#ifndef _P0_TYPE_C_ADC_SWITCH_ON
#define _P0_TYPE_C_ADC_SWITCH_ON                        0
#endif

#ifndef _P0_TYPE_C_ADC_SWITCH_OFF
#define _P0_TYPE_C_ADC_SWITCH_OFF                       1
#endif

#ifndef _ADAPTOR_TYPE_C_ADC_SWITCH_ON
#define _ADAPTOR_TYPE_C_ADC_SWITCH_ON                   0
#endif

#ifndef _ADAPTOR_TYPE_C_ADC_SWITCH_OFF
#define _ADAPTOR_TYPE_C_ADC_SWITCH_OFF                  1
#endif

#ifndef PCB_D0_TYPE_C_ADC_SWITCH
#define PCB_D0_TYPE_C_ADC_SWITCH(x)                     {\
                                                        }
#endif

#ifndef PCB_D1_TYPE_C_ADC_SWITCH
#define PCB_D1_TYPE_C_ADC_SWITCH(x)                     {\
                                                        }
#endif

#ifndef PCB_P0_TYPE_C_ADC_SWITCH
#define PCB_P0_TYPE_C_ADC_SWITCH(x)                     {\
                                                        }
#endif

#ifndef PCB_ADAPTOR_TYPE_C_ADC_SWITCH
#define PCB_ADAPTOR_TYPE_C_ADC_SWITCH(x)                {\
                                                        }
#endif

//-----------------------------------------------
// Macro of Type-C ADC High VBUS Detect Control
//-----------------------------------------------
#ifndef _D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON
#define _D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON           1
#endif

#ifndef _D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF
#define _D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF          0
#endif

#ifndef _D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON
#define _D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON           1
#endif

#ifndef _D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF
#define _D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF          0
#endif

#ifndef _P0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON
#define _P0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON           1
#endif

#ifndef _P0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF
#define _P0_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF          0
#endif

#ifndef _ADAPTOR_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON
#define _ADAPTOR_TYPE_C_HIGH_VBUS_DETECT_SWITCH_ON      1
#endif

#ifndef _ADAPTOR_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF
#define _ADAPTOR_TYPE_C_HIGH_VBUS_DETECT_SWITCH_OFF     0
#endif

#ifndef PCB_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH
#define PCB_D0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)        {\
                                                        }
#endif

#ifndef PCB_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH
#define PCB_D1_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)        {\
                                                        }
#endif

#ifndef PCB_P0_TYPE_C_HIGH_VBUS_DETECT_SWITCH
#define PCB_P0_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)        {\
                                                        }
#endif

#ifndef PCB_ADAPTOR_TYPE_C_HIGH_VBUS_DETECT_SWITCH
#define PCB_ADAPTOR_TYPE_C_HIGH_VBUS_DETECT_SWITCH(x)   {\
                                                        }
#endif


/////////////////
// Audio Macro //
/////////////////

//-----------------------------------------------
// Macro of PCB Audio Headphone Connect
//-----------------------------------------------
#ifndef _AUDIO_CONNECT
#define _AUDIO_CONNECT                                  0                   // Audio Headphone Connect
#endif

#ifndef _AUDIO_DISCONNECT
#define _AUDIO_DISCONNECT                               1                   // Audio Headphone Dis-Connect
#endif

#ifndef PCB_AUDIO_DETECT
#define PCB_AUDIO_DETECT()                              (_AUDIO_DISCONNECT)    // Audio Headphone Detect
#endif

//-----------------------------------------------
// Macro of PCB Audio AMP Control
//-----------------------------------------------
#ifndef _AMP_MUTE_ON
#define _AMP_MUTE_ON                                    0
#endif

#ifndef _AMP_MUTE_OFF
#define _AMP_MUTE_OFF                                   1
#endif

#ifndef PCB_AMP_MUTE
#define PCB_AMP_MUTE(x)                                 {\
                                                        }
#endif

//--------------------------------------------------
// Definitions of SPI Setting for Panel
//--------------------------------------------------
#ifndef _PCB_SPI0_CLK_PRE_DIV
#define _PCB_SPI0_CLK_PRE_DIV                           0                   // SPI CLK PreDivider
#endif
#ifndef _PCB_SPI0_CLK_DIV
#define _PCB_SPI0_CLK_DIV                               _DIV_4              // SPI CLK Divider
#endif
#ifndef _PCB_SPI0_ENUM_PROTOCOL_SEL
#define _PCB_SPI0_ENUM_PROTOCOL_SEL                     _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PCB_SPI0_ENUM_CLK_SRC_SEL
#define _PCB_SPI0_ENUM_CLK_SRC_SEL                      _SPI_EXT_XTAL_CLK   // SPI CLK Source
#endif
#ifndef _PCB_SPI0_MOSI_IDLE_STATE
#define _PCB_SPI0_MOSI_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#endif
#ifndef _PCB_SPI0_SCLK_IDLE_STATE
#define _PCB_SPI0_SCLK_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#endif
#ifndef _PCB_SPI0_CS_SEL
#define _PCB_SPI0_CS_SEL                                0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PCB_SPI0_CS_POLARITY
#define _PCB_SPI0_CS_POLARITY                           0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PCB_SPI0_CS_SETUP
#define _PCB_SPI0_CS_SETUP                              0                   // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PCB_SPI0_CS_HOLD
#define _PCB_SPI0_CS_HOLD                               0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PCB_SPI0_SUPPRESS_BITS
#define _PCB_SPI0_SUPPRESS_BITS                         0                   // SPI Suppress Bits(value = 0~7)
#endif

#ifndef _PCB_SPI1_CLK_PRE_DIV
#define _PCB_SPI1_CLK_PRE_DIV                           0                   // SPI CLK PreDivider
#endif
#ifndef _PCB_SPI1_CLK_DIV
#define _PCB_SPI1_CLK_DIV                               _DIV_4              // SPI CLK Divider
#endif
#ifndef _PCB_SPI1_ENUM_PROTOCOL_SEL
#define _PCB_SPI1_ENUM_PROTOCOL_SEL                     _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PCB_SPI1_ENUM_CLK_SRC_SEL
#define _PCB_SPI1_ENUM_CLK_SRC_SEL                      _SPI_EXT_XTAL_CLK   // SPI CLK Source
#endif
#ifndef _PCB_SPI1_MOSI_IDLE_STATE
#define _PCB_SPI1_MOSI_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#endif
#ifndef _PCB_SPI1_SCLK_IDLE_STATE
#define _PCB_SPI1_SCLK_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#endif
#ifndef _PCB_SPI1_CS_SEL
#define _PCB_SPI1_CS_SEL                                0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PCB_SPI1_CS_POLARITY
#define _PCB_SPI1_CS_POLARITY                           0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PCB_SPI1_CS_SETUP
#define _PCB_SPI1_CS_SETUP                              0                   // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PCB_SPI1_CS_HOLD
#define _PCB_SPI1_CS_HOLD                               0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PCB_SPI1_SUPPRESS_BITS
#define _PCB_SPI1_SUPPRESS_BITS                         0                   // SPI Suppress Bits(value = 0~7)
#endif

#ifndef _PCB_SPI2_CLK_PRE_DIV
#define _PCB_SPI2_CLK_PRE_DIV                           0                   // SPI CLK PreDivider
#endif
#ifndef _PCB_SPI2_CLK_DIV
#define _PCB_SPI2_CLK_DIV                               _DIV_4              // SPI CLK Divider
#endif
#ifndef _PCB_SPI2_ENUM_PROTOCOL_SEL
#define _PCB_SPI2_ENUM_PROTOCOL_SEL                     _SPI_NORMAL_MODE    // SPI Protocol Select
#endif
#ifndef _PCB_SPI2_ENUM_CLK_SRC_SEL
#define _PCB_SPI2_ENUM_CLK_SRC_SEL                      _SPI_EXT_XTAL_CLK   // SPI CLK Source
#endif
#ifndef _PCB_SPI2_MOSI_IDLE_STATE
#define _PCB_SPI2_MOSI_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#endif
#ifndef _PCB_SPI2_SCLK_IDLE_STATE
#define _PCB_SPI2_SCLK_IDLE_STATE                       _HIGH               // 0:low ; 1:high
#endif
#ifndef _PCB_SPI2_CS_SEL
#define _PCB_SPI2_CS_SEL                                0                   // SPI CS Pin Select, 0:CS0 ; 1:CS1
#endif
#ifndef _PCB_SPI2_CS_POLARITY
#define _PCB_SPI2_CS_POLARITY                           0                   // SPI CS Pin Polarity Select, 0:low active ; 1:high active
#endif
#ifndef _PCB_SPI2_CS_SETUP
#define _PCB_SPI2_CS_SETUP                              0                   // SPI CS Pin Setup Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PCB_SPI2_CS_HOLD
#define _PCB_SPI2_CS_HOLD                               0                   // SPI CS Pin Hold Number, 0 ~ 3(unit: sclk)
#endif
#ifndef _PCB_SPI2_SUPPRESS_BITS
#define _PCB_SPI2_SUPPRESS_BITS                         0                   // SPI Suppress Bits(value = 0~7)
#endif

//--------------------------------------------------
// Definitions of External PWM Setting for LED Driver
//--------------------------------------------------
#ifndef _DEVICE_LED_DRIVER_EXTERNAL_PWM
#define _DEVICE_LED_DRIVER_EXTERNAL_PWM                 _NO_PWM
#endif


////////////////////
// ADC Detect Int //
////////////////////

//-----------------------------------------------
// Macro of Int Detected By ADC Support
//-----------------------------------------------
#ifndef _ADC_DETECT_INT_BY_ADC_CHANNEL
#define _ADC_DETECT_INT_BY_ADC_CHANNEL                  _ADC_DET_INT_ADC_MAPPING_NONE
#endif

#ifndef _ADC_DETECT_INT_BY_ADC_THRESHOLD
#define _ADC_DETECT_INT_BY_ADC_THRESHOLD                25 // Unit: %
#endif

//-----------------------------------------------
// Macro of ADC Int Trigger GPIO Control
//-----------------------------------------------
#ifndef SET_ADC_INTERRUPT_CONTROL_PIN
#define SET_ADC_INTERRUPT_CONTROL_PIN(x)                {SET_GPIO_PIN_EMPTY(x);}
#endif

#ifndef _ADC_INTERRUPT_CONTROL_PIN_ON
#define _ADC_INTERRUPT_CONTROL_PIN_ON                   1
#endif

#ifndef _ADC_INTERRUPT_CONTROL_PIN_OFF
#define _ADC_INTERRUPT_CONTROL_PIN_OFF                  0
#endif

#ifndef PCB_ADC_INTERRUPT_CONTROL
#define PCB_ADC_INTERRUPT_CONTROL(x)                    {\
                                                            SET_ADC_INTERRUPT_CONTROL_PIN(x);\
                                                        }
#endif


