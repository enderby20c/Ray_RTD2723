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
// ID Code      : Pcb_Config_Pre_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_CONFIG_PRE_CHECK_H__
#define __PCB_CONFIG_PRE_CHECK_H__

///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// DP Macro Pre-Check
//--------------------------------------------------
#ifdef _D0_INPUT_PORT_TYPE
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if((_D0_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ) && ((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_NORMAL) || (_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI)))
#ifndef _D0_DP_Z0_IMPEDANCE_OPTION
#warning "Check PCB Impedance with HW AE !!! (PCB Impedance should be 90 for Enhance DP Connector, 100 for Legacy DP Connector)"
#endif
#endif

#ifndef PCB_D0_HOTPLUG_DETECT
#ifndef _D0_DP_CONNECTOR_TYPE
#warning "PCB_D0_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#else
#if(_D0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C)
#warning "PCB_D0_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#else
#if((_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_EMBEDDED) && (_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_TCPM))
#warning "PCB_D0_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#endif
#endif
#endif
#endif // END of #ifndef _D0_DP_CONNECTOR_TYPE

#if((_D0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_D0_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ))
#ifndef PCB_DP_UHBR_D0_CABLE_ID_DETECT_ADC_PIN
#warning "PCB_DP_UHBR_D0_CABLE_ID_DETECT_ADC_PIN() Should Be Defined as a ADC Pin!!!"
#endif

#ifndef PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1
#warning "PCB_DP_UHBR_D0_CABLE_ID_DETECT_CONFIG1(x) Should Be Defined as a PushPull Pin!!!"
#endif

#ifndef _DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME
#warning "_DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME Should Be Defined by PCB Design(Default 300us)!!!"
#endif

#endif

#if(_DP_MST_SUPPORT == _ON)

#ifndef GET_PCB_D0_DP_SOURCE_POWER
#warning "GET_PCB_D0_DP_SOURCE_POWER() Should Be Defined!!!"
#endif

#ifdef _D0_DP_CONNECTOR_TYPE
#ifdef _D0_TYPE_C_PORT_CTRL_TYPE
#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
#if(_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP
#warning "GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP() Should Be Defined!!!"
#endif
#endif
#endif
#endif
#endif

#endif

#ifdef _D0_DP_CONNECTOR_TYPE
#ifdef _D0_TYPE_C_EXT_CC_ATTACH_DETECT
#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO))
#ifndef PCB_D0_CC_ATTACH
#warning "PCB_D0_CC_ATTACH() Should Be Defined!!!"
#endif
#endif
#endif
#ifdef _D0_TYPE_C_EXT_ALT_MODE_READY_DETECT
#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO))
#ifndef PCB_D0_ALT_MODE_READY
#warning "PCB_D0_ALT_MODE_READY() Should Be Defined!!!"
#endif
#endif
#endif
#endif

#ifdef _D0_DP_CONNECTOR_TYPE
#ifdef _D0_TYPE_C_PORT_CTRL_TYPE
#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
#if(_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef PCB_D0_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_D0_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#ifndef PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#endif
#endif
#endif
#endif

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D0_INPUT_PORT_TYPE == _D0_USB_PORT)
#ifdef _D0_USB_CONNECTOR_TYPE
#if(_D0_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)
#ifndef PCB_D0_TYPE_B_VBUS_POWER_DETECT
#warning "PCB_D0_TYPE_B_VBUS_POWER_DETECT() Should Be Defined as A GPIO Pin!!!"
#endif
#endif
#endif

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_USB_PORT)

#endif // End of #ifdef _D0_INPUT_PORT_TYPE

#ifdef _D1_INPUT_PORT_TYPE
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if((_D1_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ) && ((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_NORMAL) || (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI)))
#ifndef _D1_DP_Z0_IMPEDANCE_OPTION
#warning "Check PCB Impedance with HW AE !!! (PCB Impedance should be 90 for Enhance DP Connector, 100 for Legacy DP Connector)"
#endif
#endif

#ifndef PCB_D1_HOTPLUG_DETECT
#ifndef _D1_DP_CONNECTOR_TYPE
#warning "PCB_D1_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#else
#if(_D1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C)
#warning "PCB_D1_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#else
#if((_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_EMBEDDED) && (_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_TCPM))
#warning "PCB_D1_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#endif
#endif
#endif
#endif // END of #ifndef _D0_DP_CONNECTOR_TYPE

#if((_D1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_D1_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ))
#ifndef PCB_DP_UHBR_D1_CABLE_ID_DETECT_ADC_PIN
#warning "PCB_DP_UHBR_D1_CABLE_ID_DETECT_ADC_PIN() Should Be Defined as a ADC Pin!!!"
#endif

#ifndef PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1
#warning "PCB_DP_UHBR_D1_CABLE_ID_DETECT_CONFIG1(x) Should Be Defined as a PushPull Pin!!!"
#endif

#ifndef _DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME
#warning "_DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME Should Be Defined by PCB Design(Default 300us)!!!"
#endif

#endif

#if(_DP_MST_SUPPORT == _ON)

#ifndef GET_PCB_D1_DP_SOURCE_POWER
#warning "GET_PCB_D1_DP_SOURCE_POWER() Should Be Defined!!!"
#endif

#ifdef _D1_DP_CONNECTOR_TYPE
#ifdef _D1_TYPE_C_PORT_CTRL_TYPE
#if((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
#if(_D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP
#warning "GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP() Should Be Defined!!!"
#endif
#endif
#endif
#endif
#endif

#endif

#ifdef _D1_DP_CONNECTOR_TYPE
#ifdef _D1_TYPE_C_EXT_CC_ATTACH_DETECT
#if((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO))
#ifndef PCB_D1_CC_ATTACH
#warning "PCB_D1_CC_ATTACH() Should Be Defined!!!"
#endif
#endif
#endif
#ifdef _D1_TYPE_C_EXT_ALT_MODE_READY_DETECT
#if((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO))
#ifndef PCB_D1_ALT_MODE_READY
#warning "PCB_D1_ALT_MODE_READY() Should Be Defined!!!"
#endif
#endif
#endif
#endif

#ifdef _D1_DP_CONNECTOR_TYPE
#ifdef _D1_TYPE_C_PORT_CTRL_TYPE
#if((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)))
#if(_D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef PCB_D1_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_D1_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#ifndef PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#endif
#endif
#endif
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_USB_PORT)
#ifdef _D1_USB_CONNECTOR_TYPE
#if(_D1_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)
#ifndef PCB_D1_TYPE_B_VBUS_POWER_DETECT
#warning "PCB_D1_TYPE_B_VBUS_POWER_DETECT() Should Be Defined as A GPIO Pin!!!"
#endif
#endif
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_USB_PORT)

#endif // End of #ifdef _D1_INPUT_PORT_TYPE

#ifdef _D2_INPUT_PORT_TYPE
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#if((_D2_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ) && ((_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_NORMAL) || (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI)))
#ifndef _D2_DP_Z0_IMPEDANCE_OPTION
#warning "Check PCB Impedance with HW AE !!! (PCB Impedance should be 90 for Enhance DP Connector, 100 for Legacy DP Connector)"
#endif
#endif

#if((_D2_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_D2_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ))
#ifndef PCB_DP_UHBR_D2_CABLE_ID_DETECT_ADC_PIN
#warning "PCB_DP_UHBR_D2_CABLE_ID_DETECT_ADC_PIN() Should Be Defined as a ADC Pin!!!"
#endif

#ifndef PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1
#warning "PCB_DP_UHBR_D2_CABLE_ID_DETECT_CONFIG1(x) Should Be Defined as a PushPull Pin!!!"
#endif

#ifndef _DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME
#warning "_DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME Should Be Defined by PCB Design(Default 300us)!!!"
#endif

#endif

#ifdef _D2_DP_CONNECTOR_TYPE
#ifdef _D2_TYPE_C_EXT_CC_ATTACH_DETECT
#if((_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO))
#ifndef PCB_D2_CC_ATTACH
#warning "PCB_D2_CC_ATTACH() Should Be Defined!!!"
#endif
#endif
#endif
#ifdef _D2_TYPE_C_EXT_ALT_MODE_READY_DETECT
#if((_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO))
#ifndef PCB_D2_ALT_MODE_READY
#warning "PCB_D2_ALT_MODE_READY() Should Be Defined!!!"
#endif
#endif
#endif
#endif

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_USB_PORT)
#ifdef _D2_USB_CONNECTOR_TYPE
#if(_D2_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)
#ifndef PCB_D2_TYPE_B_VBUS_POWER_DETECT
#warning "PCB_D2_TYPE_B_VBUS_POWER_DETECT() Should Be Defined as A GPIO Pin!!!"
#endif
#endif
#endif

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_USB_PORT)

#endif // End of #ifdef _D2_INPUT_PORT_TYPE

#ifdef _P0_OUTPUT_TYPE
#if(_P0_OUTPUT_TYPE == _P0_DP_PORT)

#ifdef _P0_DP_CONNECTOR_TYPE
#ifdef _P0_TYPE_C_EXT_CC_ATTACH_DETECT
#if((_P0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO))
#ifndef PCB_P0_CC_ATTACH
#warning "PCB_P0_CC_ATTACH() Should Be Defined!!!"
#endif
#endif
#endif
#ifdef _P0_TYPE_C_EXT_ALT_MODE_READY_DETECT
#if((_P0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_PCB_MACRO))
#ifndef PCB_P0_ALT_MODE_READY
#warning "PCB_P0_ALT_MODE_READY() Should Be Defined!!!"
#endif
#endif
#endif
#endif

#endif // End of #if(_P0_OUTPUT_TYPE == _P0_DP_PORT)
#endif // End of #ifdef _P0_OUTPUT_TYPE

//--------------------------------------------------
// HDMI EXT EDID SIZE CHECK
//--------------------------------------------------
#ifdef _D1_INPUT_PORT_TYPE
#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#ifndef _D1_EDID_EXTERNAL_EEPROM_MAX_SIZE
#warning "_D1_EDID_EXTERNAL_EEPROM_MAX_SIZE Should Be Defined When HDMI Port"
#endif
#endif
#endif

#ifdef _D2_INPUT_PORT_TYPE
#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#ifndef _D2_EDID_EXTERNAL_EEPROM_MAX_SIZE
#warning "_D2_EDID_EXTERNAL_EEPROM_MAX_SIZE Should Be Defined When HDMI Port"
#endif
#endif
#endif

#ifdef _D3_INPUT_PORT_TYPE
#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#ifndef _D3_EDID_EXTERNAL_EEPROM_MAX_SIZE
#warning "_D3_EDID_EXTERNAL_EEPROM_MAX_SIZE Should Be Defined When HDMI Port"
#endif
#endif
#endif

#ifdef _D4_INPUT_PORT_TYPE
#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#ifndef _D4_EDID_EXTERNAL_EEPROM_MAX_SIZE
#warning "_D4_EDID_EXTERNAL_EEPROM_MAX_SIZE Should Be Defined When HDMI Port"
#endif
#endif
#endif

//--------------------------------------------------
// HDMI Macro Pre-Check
//--------------------------------------------------
#ifdef _D0_MAX_HDMI_EDID_COUNT
#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D1_MAX_HDMI_EDID_COUNT
#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D2_MAX_HDMI_EDID_COUNT
#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D3_MAX_HDMI_EDID_COUNT
#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D4_MAX_HDMI_EDID_COUNT
#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D5_MAX_HDMI_EDID_COUNT
#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef PCB_MULTI_EDID_SWITCH
#ifndef _D0_MAX_HDMI_EDID_COUNT
#ifndef _D1_MAX_HDMI_EDID_COUNT
#ifndef _D2_MAX_HDMI_EDID_COUNT
#ifndef _D3_MAX_HDMI_EDID_COUNT
#ifndef _D4_MAX_HDMI_EDID_COUNT
#ifndef _D5_MAX_HDMI_EDID_COUNT
#warning "_DX_MAX_HDMI_EDID_COUNT Should Be Defined!!!"
#endif
#endif
#endif
#endif
#endif
#endif
#endif


////////////////
// MBR + TCON //
////////////////
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#ifndef _PCB_MBR_DRIVER_IC_MAX_FREQ
#warning "_PCB_MBR_DRIVER_IC_MAX_FREQ Should Be Defined!!!"
#endif
#endif

#endif // End of #ifndef __PCB_CONFIG_PRE_CHECK_H__
