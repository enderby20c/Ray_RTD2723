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
// ID Code      : Pcb_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_CONFIG_CHECK_H__
#define __PCB_CONFIG_CHECK_H__

///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// PCB DP Lane Swap Check
//--------------------------------------------------
#if(_HW_DP_LANE_SWAP_SUPPORT == _OFF)
#if((_D0_DP_PCB_LANE0_MAPPING != _DP_SCALER_LANE0) ||\
    (_D0_DP_PCB_LANE1_MAPPING != _DP_SCALER_LANE1) ||\
    (_D0_DP_PCB_LANE2_MAPPING != _DP_SCALER_LANE2) ||\
    (_D0_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3) ||\
    (_D1_DP_PCB_LANE0_MAPPING != _DP_SCALER_LANE0) ||\
    (_D1_DP_PCB_LANE1_MAPPING != _DP_SCALER_LANE1) ||\
    (_D1_DP_PCB_LANE2_MAPPING != _DP_SCALER_LANE2) ||\
    (_D1_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3) ||\
    (_D2_DP_PCB_LANE0_MAPPING != _DP_SCALER_LANE0) ||\
    (_D2_DP_PCB_LANE1_MAPPING != _DP_SCALER_LANE1) ||\
    (_D2_DP_PCB_LANE2_MAPPING != _DP_SCALER_LANE2) ||\
    (_D2_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3))
#warning "DP Lane Swap Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// PCB DP PN Swap Check
//--------------------------------------------------
#if(_HW_DP_PN_SWAP_SUPPORT == _OFF)
#if((_D0_DP_PCB_LANE0_PN_SWAP == _ON) || (_D0_DP_PCB_LANE1_PN_SWAP == _ON) ||\
    (_D0_DP_PCB_LANE2_PN_SWAP == _ON) || (_D0_DP_PCB_LANE3_PN_SWAP == _ON) ||\
    (_D1_DP_PCB_LANE0_PN_SWAP == _ON) || (_D1_DP_PCB_LANE1_PN_SWAP == _ON) ||\
    (_D1_DP_PCB_LANE2_PN_SWAP == _ON) || (_D1_DP_PCB_LANE3_PN_SWAP == _ON) ||\
    (_D2_DP_PCB_LANE0_PN_SWAP == _ON) || (_D2_DP_PCB_LANE1_PN_SWAP == _ON) ||\
    (_D2_DP_PCB_LANE2_PN_SWAP == _ON) || (_D2_DP_PCB_LANE3_PN_SWAP == _ON))
#warning "DP PN Swap Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// DP Margin Link Support Check
//--------------------------------------------------
#if(_DP_MARGIN_LINK_SUPPORT == _ON)
#if((_D0_DP_LINK_CLK_RATE < _DP_HIGH_SPEED2_540MHZ) &&\
    (_D1_DP_LINK_CLK_RATE < _DP_HIGH_SPEED2_540MHZ) &&\
    (_D2_DP_LINK_CLK_RATE < _DP_HIGH_SPEED2_540MHZ) &&\
    (_D6_DP_LINK_CLK_RATE < _DP_HIGH_SPEED2_540MHZ))
#warning "_DP_MARGIN_LINK_SUPPORT Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// DP D7 Port Check
//--------------------------------------------------
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
#if((_D0_INPUT_PORT_TYPE != _D0_DP_PORT) || (_D1_INPUT_PORT_TYPE != _D1_DP_PORT))
#warning "_D0_INPUT_PORT_TYPE & _D1_INPUT_PORT_TYPE Should Be DP Port!!!"
#endif
#endif

//--------------------------------------------------
// DP D8 Port Check
//--------------------------------------------------
#if(_D8_INPUT_PORT_TYPE == _D8_DP_PORT)
#if((_D1_INPUT_PORT_TYPE != _D1_DP_PORT) || (_D2_INPUT_PORT_TYPE != _D2_DP_PORT))
#warning "_D1_INPUT_PORT_TYPE & _D2_INPUT_PORT_TYPE Should Be DP Port!!!"
#endif
#endif

//--------------------------------------------------
// DP Dual Port Check
//--------------------------------------------------
#if((_D7_INPUT_PORT_TYPE == _D7_DP_PORT) && (_D8_INPUT_PORT_TYPE == _D8_DP_PORT))
#warning "_D7_DP_PORT & _D8_DP_PORT Can't Support Concurrently!!!"
#endif

//--------------------------------------------------
// DP Legancy Connector Impedance Check
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_D0_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ) &&\
    ((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_NORMAL) || (_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI)) &&\
    (_D0_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR))
#warning "Impedance Should be 85 or 100 when using Normal/Mini Connector for UHBR)"
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if((_D1_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ) &&\
    ((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_NORMAL) || (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI)) &&\
    (_D1_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR))
#warning "Impedance Should be 85 or 100 when using Normal/Mini Connector for UHBR)"
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if((_D2_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ) &&\
    ((_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_NORMAL) || (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI)) &&\
    (_D2_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR))
#warning "Impedance Should be 85 or 100 when using Normal/Mini Connector for UHBR)"
#endif
#endif

//--------------------------------------------------
// DP TBT Connector Force Fake LT Check
//--------------------------------------------------
#if(_DP_LT_FORCE_FAKE_LT_FOR_TBT == _ON)
#if(((_D0_INPUT_PORT_TYPE != _D0_DP_PORT) || (_D0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TBT)) &&\
    ((_D1_INPUT_PORT_TYPE != _D1_DP_PORT) || (_D1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TBT)) &&\
    ((_D2_INPUT_PORT_TYPE != _D2_DP_PORT) || (_D2_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TBT)))
#warning "_DP_LT_FORCE_FAKE_LT_FOR_TBT Should not be _ON when there is no TBT Port!!!"
#endif
#endif

//--------------------------------------------------
// HDMI D12 Port Check
//--------------------------------------------------
#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
#if(_D3_INPUT_PORT_TYPE != _D3_HDMI_PORT)
#warning "NOTE: _D3_INPUT_PORT_TYPE Should Be _D3_HDMI_PORT!!!"
#endif
#endif

#if(_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT)
#if(_D12_INPUT_PORT_SWITCH_FROM != _SWITCH_FROM_D3)
#warning "NOTE: _D12_INPUT_PORT_SWITCH_FROM Should Be _SWITCH_FROM_D3!!!"
#endif
#endif

//--------------------------------------------------
// HDMI D13 Port Check
//--------------------------------------------------
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
#if(_D3_INPUT_PORT_TYPE != _D3_HDMI_PORT)
#warning "_D3_INPUT_PORT_TYPE Should Be _D3_HDMI_PORT!!!"
#endif
#endif

#if(_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT)
#if(_D13_INPUT_PORT_SWITCH_FROM != _SWITCH_FROM_D3)
#warning "_D13_INPUT_PORT_SWITCH_FROM Should Be _SWITCH_FROM_D3!!!"
#endif
#endif

#if(_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT)
#if(_D12_INPUT_PORT_TYPE != _D12_HDMI_PORT)
#warning "D12 Should Be (_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT)"
#endif
#endif

//--------------------------------------------------
// HDMI D14 Port Check
//--------------------------------------------------
#if((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
#if(_D4_INPUT_PORT_TYPE != _D4_HDMI_PORT)
#warning "NOTE: _D4_INPUT_PORT_TYPE Should Be _D4_HDMI_PORT!!!"
#endif
#endif

#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
#if(_D14_INPUT_PORT_SWITCH_FROM != _SWITCH_FROM_D4)
#warning "NOTE: _D14_INPUT_PORT_SWITCH_FROM Should Be _SWITCH_FROM_D4!!!"
#endif
#endif

//--------------------------------------------------
// HDMI D15 Port Check
//--------------------------------------------------
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
#if(_D4_INPUT_PORT_TYPE != _D4_HDMI_PORT)
#warning "_D4_INPUT_PORT_TYPE Should Be _D4_HDMI_PORT!!!"
#endif
#endif

#if(_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT)
#if(_D15_INPUT_PORT_SWITCH_FROM != _SWITCH_FROM_D4)
#warning "_D15_INPUT_PORT_SWITCH_FROM Should Be _SWITCH_FROM_D4!!!"
#endif
#endif

#if(_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT)
#if(_D14_INPUT_PORT_TYPE != _D14_HDMI_PORT)
#warning "D14 Should Be (_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)"
#endif
#endif

#if((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT))
#warning "D14 Should Be (_D14_INPUT_PORT_TYPE == _D14_NO_PORT)"
#endif

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
//--------------------------------------------------
// HDMI CEC EDID Physical Address Check
//--------------------------------------------------
#if(_D1_HDMI_CEC_PIN != _HDMI_CEC_NONE)
#if(_D1_HDMI_CEC_EDID_PHYSICAL_ADDR == 0x0000)
#warning "Please define _D1_HDMI_CEC_EDID_PHYSICAL_ADDR in PCB.h"
#endif
#endif // End of #if(_D1_HDMI_CEC_SUPPORT == _ON)

#if(_D2_HDMI_CEC_PIN != _HDMI_CEC_NONE)
#if(_D2_HDMI_CEC_EDID_PHYSICAL_ADDR == 0x0000)
#warning "Please define _D2_HDMI_CEC_EDID_PHYSICAL_ADDR in PCB.h"
#endif
#endif // End of #if(_D2_HDMI_CEC_SUPPORT == _ON)

#if(_D3_HDMI_CEC_PIN != _HDMI_CEC_NONE)
#if(_D3_HDMI_CEC_EDID_PHYSICAL_ADDR == 0x0000)
#warning "Please define _D3_HDMI_CEC_EDID_PHYSICAL_ADDR in PCB.h"
#endif
#endif // End of #if(_D3_HDMI_CEC_SUPPORT == _ON)

#if(_D4_HDMI_CEC_PIN != _HDMI_CEC_NONE)
#if(_D4_HDMI_CEC_EDID_PHYSICAL_ADDR == 0x0000)
#warning "Please define _D4_HDMI_CEC_EDID_PHYSICAL_ADDR in PCB.h"
#endif
#endif // End of #if(_D4_HDMI_CEC_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)

//--------------------------------------------------
// DDC Mapping Check
//--------------------------------------------------
#if(_HW_DDC_CHANNEL_SWITCH_SUPPORT == _OFF)
#if(((_D0_DDC_CHANNEL_SEL != _NO_DDC) && (_D0_DDC_CHANNEL_SEL != _DDC0)) ||\
    ((_D1_DDC_CHANNEL_SEL != _NO_DDC) && (_D1_DDC_CHANNEL_SEL != _DDC1)) ||\
    ((_D2_DDC_CHANNEL_SEL != _NO_DDC) && (_D2_DDC_CHANNEL_SEL != _DDC2)) ||\
    ((_D3_DDC_CHANNEL_SEL != _NO_DDC) && (_D3_DDC_CHANNEL_SEL != _DDC3)) ||\
    ((_D4_DDC_CHANNEL_SEL != _NO_DDC) && (_D4_DDC_CHANNEL_SEL != _DDC4)) ||\
    ((_D5_DDC_CHANNEL_SEL != _NO_DDC) && (_D5_DDC_CHANNEL_SEL != _DDC5)))
#warning "D0 or D1 or D2 or D3 or D4 or D5 Select Wrong DDC Channel!!!"
#endif
#endif

//--------------------------------------------------
// Input Port Type & DDC Channel Status Check
//--------------------------------------------------
#if(((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _NO_DDC)))
#warning "When D0 or D1 or D2 or D3 or D4 or D5 Input Port Type Select not _NO_PORT, DDC Channel Can't be _NO_DDC!!!"
#endif

//--------------------------------------------------
// HDMI2.1 Max Link Rate Setting Check
//--------------------------------------------------
#if(_D1_HDMI_FRL_SUPPORT == _ON)
#if(_D1_HDMI_FRL_MAX_LINK_RATE > _HW_HDMI21_MAX_LINK_RATE_SUPPORT)
#warning "_D1_HDMI_LINK_CLK_RATE and _D1_HDMI_MAIN_LINK_LANES Over HW Support!!"
#endif
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
#if(_D2_HDMI_FRL_MAX_LINK_RATE > _HW_HDMI21_MAX_LINK_RATE_SUPPORT)
#warning "_D2_HDMI_LINK_CLK_RATE and _D2_HDMI_MAIN_LINK_LANES Over HW Support!!"
#endif
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
#if(_D3_HDMI_FRL_MAX_LINK_RATE > _HW_HDMI21_MAX_LINK_RATE_SUPPORT)
#warning "_D3_HDMI_LINK_CLK_RATE and _D3_HDMI_MAIN_LINK_LANES Over HW Support!!"
#endif
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
#if(_D4_HDMI_FRL_MAX_LINK_RATE > _HW_HDMI21_MAX_LINK_RATE_SUPPORT)
#warning "_D4_HDMI_LINK_CLK_RATE and _D4_HDMI_MAIN_LINK_LANES Over HW Support!!"
#endif
#endif

//--------------------------------------------------
// HDMI2.1/HDMI2.0 Support Check
//--------------------------------------------------
#if(_D1_HDMI_FRL_SUPPORT == _ON)
#if(_D1_HDMI20_SUPPORT == _OFF)
#warning "_D1_HDMI20_SUPPORT shall be supported when _D1_HDMI_FRL_SUPPORT is supported!!!"
#endif
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
#if(_D2_HDMI20_SUPPORT == _OFF)
#warning "_D2_HDMI20_SUPPORT shall be supported when _D2_HDMI_FRL_SUPPORT is supported!!!"
#endif
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
#if(_D3_HDMI20_SUPPORT == _OFF)
#warning "_D3_HDMI20_SUPPORT shall be supported when _D3_HDMI_FRL_SUPPORT is supported!!!"
#endif
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
#if(_D4_HDMI20_SUPPORT == _OFF)
#warning "_D4_HDMI20_SUPPORT shall be supported when _D4_HDMI_FRL_SUPPORT is supported!!!"
#endif
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
#if(_HDMI20_MAC_RX3_SUPPORT == _OFF)
#warning "_HDMI20_MAC_RX3_SUPPORT shall be supported when _HDMI_FRL_MAC_RX3_SUPPORT is supported!!!"
#endif
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
#if(_HDMI20_MAC_RX4_SUPPORT == _OFF)
#warning "_HDMI20_MAC_RX4_SUPPORT shall be supported when _HDMI_FRL_MAC_RX4_SUPPORT is supported!!!"
#endif
#endif

//--------------------------------------------------
// HDMI EXT EDID SIZE CHECK
//--------------------------------------------------
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE))
#if(_D1_EDID_EXTERNAL_EEPROM_MAX_SIZE == _EDID_EEPROM_SIZE_NONE)
#warning "_D1_EDID_EXTERNAL_EEPROM_MAX_SIZE shall > 0 When D1 is HDMI PORT"
#endif
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE))
#if(_D2_EDID_EXTERNAL_EEPROM_MAX_SIZE == _EDID_EEPROM_SIZE_NONE)
#warning "_D2_EDID_EXTERNAL_EEPROM_MAX_SIZE shall > 0 When D2 is HDMI PORT"
#endif
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE))
#if(_D3_EDID_EXTERNAL_EEPROM_MAX_SIZE == _EDID_EEPROM_SIZE_NONE)
#warning "_D3_EDID_EXTERNAL_EEPROM_MAX_SIZE shall > 0 When D3 is HDMI PORT"
#endif
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE))
#if(_D4_EDID_EXTERNAL_EEPROM_MAX_SIZE == _EDID_EEPROM_SIZE_NONE)
#warning "_D4_EDID_EXTERNAL_EEPROM_MAX_SIZE shall > 0 When D4 is HDMI PORT"
#endif
#endif

//--------------------------------------------------
// ARC Tx D23 Dual Port Check
//--------------------------------------------------
#if((_D2_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE) && (_D3_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE))
#warning "_D2_HDMI_ARC_TX_PIN & _D3_HDMI_ARC_TX_PIN Can't Support Concurrently!!!"
#endif

//--------------------------------------------------
// ARC Tx D34 Dual Port Check
//--------------------------------------------------
#if((_D3_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE) && (_D4_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE))
#warning "_D3_HDMI_ARC_TX_PIN & _D4_HDMI_ARC_TX_PIN Can't Support Concurrently!!!"
#endif

//--------------------------------------------------
// ARC Tx D24 Dual Port Check
//--------------------------------------------------
#if((_D2_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE) && (_D4_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE))
#warning "_D2_HDMI_ARC_TX_PIN & _D4_HDMI_ARC_TX_PIN Can't Support Concurrently!!!"
#endif

//--------------------------------------------------
// ARC Tx D1 CEC Check
//--------------------------------------------------
#if(_D1_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE)
#if(_D1_HDMI_CEC_PIN == _HDMI_CEC_NONE)
#warning "_D1_HDMI_CEC_PIN Should Be Supported, when _D1_HDMI_ARC_TX_PIN is Supported!!!"
#endif
#endif

//--------------------------------------------------
// ARC Tx D2 CEC Check
//--------------------------------------------------
#if(_D2_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE)
#if(_D2_HDMI_CEC_PIN == _HDMI_CEC_NONE)
#warning "_D2_HDMI_CEC_PIN Should Be Supported, when _D2_HDMI_ARC_TX_PIN is Supported!!!"
#endif
#endif

//--------------------------------------------------
// ARC Tx D3 CEC Check
//--------------------------------------------------
#if(_D3_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE)
#if(_D3_HDMI_CEC_PIN == _HDMI_CEC_NONE)
#warning "_D3_HDMI_CEC_PIN Should Be Supported, when _D3_HDMI_ARC_TX_PIN is Supported!!!"
#endif
#endif

//--------------------------------------------------
// ARC Tx D4 CEC Check
//--------------------------------------------------
#if(_D4_HDMI_ARC_TX_PIN != _HDMI_ARC_TX_NONE)
#if(_D4_HDMI_CEC_PIN == _HDMI_CEC_NONE)
#warning "_D4_HDMI_CEC_PIN Should Be Supported, when _D4_HDMI_ARC_TX_PIN is Supported!!!"
#endif
#endif

//--------------------------------------------------
// DP Max Link Rate Setting Check
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if(_HW_DP_D0_MAX_LINK_RATE_SUPPORT < _D0_DP_LINK_CLK_RATE)
#warning "NOTE: Please Confirm D0 Port Max Link Rate Over HW Support~!!"
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_HW_DP_D1_MAX_LINK_RATE_SUPPORT < _D1_DP_LINK_CLK_RATE)
#warning "NOTE: Please Confirm D1 Port Max Link Rate Over HW Support~!!"
#endif
#endif

//--------------------------------------------------
// DP Auxless ALPM Setting Check
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_DP_AUXLESS_ALPM_SUPPORT == _ON) && (_HW_DP_D0_AUXLESS_ALPM_SUPPORT != _ON))
#warning "NOTE: D0 DP Can't Suppport Auxless ALPM!!!"
#endif

#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if((_DP_AUXLESS_ALPM_SUPPORT == _ON) && (_HW_DP_D1_AUXLESS_ALPM_SUPPORT != _ON))
#warning "NOTE: D1 DP Can't Suppport Auxless ALPM!!!"
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if((_DP_AUXLESS_ALPM_SUPPORT == _ON) && (_HW_DP_D2_AUXLESS_ALPM_SUPPORT != _ON))
#warning "NOTE: D2 DP Can't Suppport Auxless ALPM!!!"
#endif
#endif

//--------------------------------------------------
// DP UHBR Link Rate Check
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_D0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_D0_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ))
#if(_LOW_SPEED_ADC_SUPPORT == _OFF)
#warning "_LOW_SPEED_ADC_SUPPORT Should Be _ON for D0 Port Cable_ID detection!!!"
#endif
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if((_D1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_D1_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ))
#if(_LOW_SPEED_ADC_SUPPORT == _OFF)
#warning "_LOW_SPEED_ADC_SUPPORT Should Be _ON for D1 Port Cable_ID detection!!!"
#endif
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if((_D2_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_D2_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ))
#if(_LOW_SPEED_ADC_SUPPORT == _OFF)
#warning "_LOW_SPEED_ADC_SUPPORT Should Be _ON for D2 Port Cable_ID detection!!!"
#endif
#endif
#endif


//////////////////////
// USB Type-C & HUB //
//////////////////////

//--------------------------------------------------
// Connector & Port Controller Type Check
//--------------------------------------------------
#if((_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D0_INPUT_PORT_TYPE != _D0_DP_PORT) && (_D0_INPUT_PORT_TYPE != _D0_USB_PORT)))
#warning "'_D0_INPUT_PORT_TYPE' Should be '_D0_DP_PORT' or '_D0_USB_PORT' if '_D0_TYPE_C_PORT_CTRL_SUPPORT' = '_ON'"
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C)) && (_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_D0_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C' if '_D0_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_USB_PORT) && (_D0_USB_CONNECTOR_TYPE != _USB_CONNECTOR_TYPE_C)) && (_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_D0_USB_CONNECTOR_TYPE' Shall be '_USB_CONNECTOR_TYPE_C' if '_D0_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D0_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_D0_DP_CONNECTOR_TYPE' = '_DP_CONNECTOR_TYPE_C'"
#endif

#if((_D0_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_C) && (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D0_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_D0_USB_CONNECTOR_TYPE' = '_USB_CONNECTOR_TYPE_C'"
#endif

#if((_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D1_INPUT_PORT_TYPE != _D1_DP_PORT) && (_D1_INPUT_PORT_TYPE != _D1_USB_PORT)))
#warning "'_D1_INPUT_PORT_TYPE' Should be '_D1_DP_PORT' or '_D1_USB_PORT' if '_D1_TYPE_C_PORT_CTRL_SUPPORT' = '_ON'"
#endif

#if(((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C)) && (_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_D1_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C' if '_D1_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if(((_D1_INPUT_PORT_TYPE == _D1_USB_PORT) && (_D1_USB_CONNECTOR_TYPE != _USB_CONNECTOR_TYPE_C)) && (_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_D1_USB_CONNECTOR_TYPE' Shall be '_USB_CONNECTOR_TYPE_C' if '_D1_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D1_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_D1_DP_CONNECTOR_TYPE' = '_DP_CONNECTOR_TYPE_C'"
#endif

#if((_D1_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_C) && (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D1_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_D1_USB_CONNECTOR_TYPE' = '_USB_CONNECTOR_TYPE_C'"
#endif

#if((_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D2_INPUT_PORT_TYPE != _D2_DP_PORT) && (_D2_INPUT_PORT_TYPE != _D2_USB_PORT)))
#warning "'_D2_INPUT_PORT_TYPE' Should be '_D2_DP_PORT' or '_D2_USB_PORT' if '_D2_TYPE_C_PORT_CTRL_SUPPORT' = '_ON'"
#endif

#if(((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C)) && (_D2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_D2_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C' if '_D2_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if(((_D2_INPUT_PORT_TYPE == _D2_USB_PORT) && (_D2_USB_CONNECTOR_TYPE != _USB_CONNECTOR_TYPE_C)) && (_D2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_D2_USB_CONNECTOR_TYPE' Shall be '_USB_CONNECTOR_TYPE_C' if '_D2_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D2_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_D2_DP_CONNECTOR_TYPE' = '_DP_CONNECTOR_TYPE_C'"
#endif

#if((_D2_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_C) && (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D2_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_D2_USB_CONNECTOR_TYPE' = '_USB_CONNECTOR_TYPE_C'"
#endif

#if((_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_P0_OUTPUT_TYPE != _P0_DP_PORT))
#warning "'_P0_OUTPUT_TYPE' Should be '_P0_DP_PORT' if '_P0_TYPE_C_PORT_CTRL_SUPPORT' = '_ON'"
#endif

#if((_P0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_P0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_P0_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C' if '_P0_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_P0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P0_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_P0_DP_CONNECTOR_TYPE' = '_DP_CONNECTOR_TYPE_C'"
#endif

#if((_P1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_P1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_P1_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C' if '_P1_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_P1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P1_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_P1_DP_CONNECTOR_TYPE' = '_DP_CONNECTOR_TYPE_C'"
#endif

#if((_P2_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_P2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_P2_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C' if '_P2_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_P2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P2_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_P2_DP_CONNECTOR_TYPE' = '_DP_CONNECTOR_TYPE_C'"
#endif

#if((_P3_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_P3_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_P3_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C' if '_P3_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_P3_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P3_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_P3_DP_CONNECTOR_TYPE' = '_DP_CONNECTOR_TYPE_C'"
#endif

#if((_P4_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) && (_P4_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_P4_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C' if '_P4_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_P4_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P4_TYPE_C_PORT_CTRL_TYPE' Should be defined (Not NONE) if '_P4_DP_CONNECTOR_TYPE' = '_DP_CONNECTOR_TYPE_C'"
#endif

#if((_ADAPTOR_CONNECTOR_TYPE != _ADAPTOR_CONNECTOR_TYPE_C) && (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#warning "'_ADAPTOR_CONNECTOR_TYPE' Shall be '_ADAPTOR_CONNECTOR_TYPE_C' if '_ADAPTOR_TYPE_C_PORT_CTRL_TYPE' != _PORT_CTRL_NONE' !!!"
#endif

#if((_ADAPTOR_CONNECTOR_TYPE == _ADAPTOR_CONNECTOR_TYPE_C) && ((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_EMBEDDED) && (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_RTD)))
#warning "'_ADAPTOR_TYPE_C_PORT_CTRL_TYPE' Should be '_PORT_CTRL_EMBEDDED' or '_PORT_CTRL_RTD' if '_ADAPTOR_CONNECTOR_TYPE' = '_ADAPTOR_CONNECTOR_TYPE_C'"
#endif

//--------------------------------------------------
// Port Controller = RTS Related Check
//--------------------------------------------------
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
#if(_D0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR == 0x00)
#warning "'_D0_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR' Should be Defined (Not 0x00)"
#endif

#if(_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D0_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D0_TYPE_C_EXT_CC_ATTACH_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D0_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#warning "NOTE: Please Confirm D0 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_D0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _OFF))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' should be selected '_ON' if '_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS' and '_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY'"
#endif
#endif // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
#if(_D1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR == 0x00)
#warning "'_D1_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR' Should be Defined (Not 0x00)"
#endif

#if(_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D1_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D1_TYPE_C_EXT_CC_ATTACH_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D1_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#warning "NOTE: Please Confirm D1 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_D1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _OFF))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' should be selected '_ON' if '_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS' and '_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY'"
#endif
#endif // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
#if(_D2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR == 0x00)
#warning "'_D2_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR' Should be Defined (Not 0x00)"
#endif

#if(_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D2_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D2_TYPE_C_EXT_CC_ATTACH_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D2_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_D2_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#warning "NOTE: Please Confirm D2 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D2_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D2_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_D2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _OFF))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' should be selected '_ON' if '_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS' and '_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY'"
#endif
#endif // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
#if(_P0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR == 0x00)
#warning "'_P0_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR 'Should be Defined (Not 0x00)"
#endif

#if(_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P0_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P0_TYPE_C_EXT_CC_ATTACH_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P0_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#warning "NOTE: Please Confirm P0 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _OFF))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' should be selected '_ON' if '_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS' and '_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY'"
#endif
#endif // End of #if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
#if(_P1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR == 0x00)
#warning "'_P1_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR 'Should be Defined (Not 0x00)"
#endif

#if(_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P1_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P1_TYPE_C_EXT_CC_ATTACH_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P1_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P1_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#warning "NOTE: Please Confirm P1 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P1_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P1_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _OFF))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' should be selected '_ON' if '_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS' and '_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY'"
#endif
#endif // End of #if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
#if(_P2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR == 0x00)
#warning "'_P2_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR 'Should be Defined (Not 0x00)"
#endif

#if(_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P2_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P2_TYPE_C_EXT_CC_ATTACH_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P2_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P2_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#warning "NOTE: Please Confirm P2 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P2_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P2_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _OFF))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' should be selected '_ON' if '_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS' and '_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY'"
#endif
#endif // End of #if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
#if(_P3_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR == 0x00)
#warning "'_P3_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P3_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR 'Should be Defined (Not 0x00)"
#endif

#if(_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P3_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P3_TYPE_C_EXT_CC_ATTACH_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P3_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P3_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#warning "NOTE: Please Confirm P3 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P3_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P3_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P3_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P3_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _OFF))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' should be selected '_ON' if '_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS' and '_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY'"
#endif
#endif // End of #if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)
#if(_P4_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR == 0x00)
#warning "'_P4_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P4_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR 'Should be Defined (Not 0x00)"
#endif

#if(_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P4_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P4_TYPE_C_EXT_CC_ATTACH_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P4_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_RTS', '_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT' Should Not be '_EXT_PORT_CTRL_NOT_EXIST'"
#endif

#if(_P4_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#warning "NOTE: Please Confirm P4 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P4_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P4_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P4_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P4_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _OFF))
#warning "'_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT' should be selected '_ON' if '_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS' and '_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY'"
#endif
#endif // End of #if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS)

//--------------------------------------------------
// Port Controller = User Related Check
//--------------------------------------------------
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#if((_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_D0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif
#endif // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#if((_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_D1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif
#endif // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#if((_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D2_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D2_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_D2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_D2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif
#endif // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#if((_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P0_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif
#endif // End of #if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#if((_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P1_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P1_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P1_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif
#endif // End of #if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#if((_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P2_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P2_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P2_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif
#endif // End of #if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#if((_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P3_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P3_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P3_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P3_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif
#endif // End of #if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)
#if((_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P4_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_P4_TYPE_C_EXT_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif

#if((_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) && (_P4_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E != _SWAP_BY_SCALER))
#warning "'_P4_TYPE_C_EXT_LANE_SWAP_FOR_PIN_E' should be selected '_SWAP_BY_SCALER' if '_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER'"
#endif
#endif // End of #if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER)

//--------------------------------------------------
// Port Controller = Embedded Related Check
//--------------------------------------------------
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_D0_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_D0_TYPE_C_EMB_DRP_PREFER == _TYPE_C_DRP_TRY_SRC)
#warning "'_D0_TYPE_C_EMB_DRP_PREFER' Should Use '_TYPE_C_DRP_NO_PREFERENCE' or '_TYPE_C_DRP_TRY_SNK' for DP Rx Port (D0)"
#endif

#if(_D0_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D0_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER)
#warning "'_PORT_CTRL_EMBEDDED' PN Swap Should Use '_SWAP_BY_SCALER'"
#endif

#if((_D0_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_D0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "'_D0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_OFF' if '_D0_TYPE_C_EMB_PORT_ROLE' = '_TYPE_C_PORT_SRC_ONLY'"
#endif

#if((_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) && ((_D0_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_D0_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON', '_D0_TYPE_C_EMB_PORT_ROLE' Should Not be '_TYPE_C_PORT_SNK_ONLY' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_D0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) && ((_D0_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_D0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON', '_D0_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_DRP' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) && (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_1))
#warning "If '_D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT' = '_ON', '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_1'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_D0_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "'_D0_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_SNK_ONLY' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_D0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "'_D0_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_NOT_SUPPORT'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && ((_D0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_D0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY)))
#warning "'_D0_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_HOST_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_HOST_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && ((_D0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_D0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY)))
#warning "'_D0_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_DEVICE_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_DEVICE_ONLY'"
#endif
#endif  // End of #if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_D1_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_D1_TYPE_C_EMB_DRP_PREFER == _TYPE_C_DRP_TRY_SRC)
#warning "'_D1_TYPE_C_EMB_DRP_PREFER' Should Use '_TYPE_C_DRP_NO_PREFERENCE' or '_TYPE_C_DRP_TRY_SNK' for DP Rx Port (D1)"
#endif

#if(_D1_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D1_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_D1_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER)
#warning "'_PORT_CTRL_EMBEDDED' PN Swap Should Use '_SWAP_BY_SCALER'"
#endif

#if((_D1_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_D1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "'_D1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_OFF' if '_D1_TYPE_C_EMB_PORT_ROLE' = '_TYPE_C_PORT_SRC_ONLY'"
#endif

#if((_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) && ((_D1_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_D1_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON', '_D1_TYPE_C_EMB_PORT_ROLE' Should Not be '_TYPE_C_PORT_SNK_ONLY' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_D1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) && ((_D1_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_D1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON', '_D1_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_DRP' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) && (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_1))
#warning "If '_D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT' = '_ON', '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_1'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_D1_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "'_D1_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_SNK_ONLY' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_D1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "'_D1_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_NOT_SUPPORT'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && ((_D1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_D1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY)))
#warning "'_D1_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_HOST_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_HOST_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && ((_D1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_D1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY)))
#warning "'_D1_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_DEVICE_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_DEVICE_ONLY'"
#endif
#endif  // End of #if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_D2_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_D2_TYPE_C_EMB_DRP_PREFER == _TYPE_C_DRP_TRY_SRC)
#warning "'_D2_TYPE_C_EMB_DRP_PREFER' Should Use '_TYPE_C_DRP_NO_PREFERENCE' or '_TYPE_C_DRP_TRY_SNK' for DP Rx Port (D2)"
#endif

#if(_D2_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D2_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_D2_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER)
#warning "'_PORT_CTRL_EMBEDDED' PN Swap Should Use '_SWAP_BY_SCALER'"
#endif

#if((_D2_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_D2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "'_D2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_OFF' if '_D2_TYPE_C_EMB_PORT_ROLE' = '_TYPE_C_PORT_SRC_ONLY'"
#endif

#if((_D2_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) && ((_D2_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_D2_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON', '_D2_TYPE_C_EMB_PORT_ROLE' Should Not be '_TYPE_C_PORT_SNK_ONLY' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_D2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) && ((_D2_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_D2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON', '_D2_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_DRP' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_D2_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) && (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_1))
#warning "If '_D2_TYPE_C_EMB_PD3_1_EPR_SUPPORT' = '_ON', '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_1'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_D2_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "'_D2_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_SNK_ONLY' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_D2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "'_D2_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_NOT_SUPPORT'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && ((_D2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_D2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY)))
#warning "'_D2_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_HOST_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_HOST_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && ((_D2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_D2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY)))
#warning "'_D2_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_DEVICE_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_DEVICE_ONLY'"
#endif
#endif  // End of #if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_P0_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_P0_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P0_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P0_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER)
#warning "'_PORT_CTRL_EMBEDDED' PN Swap Should Use '_SWAP_BY_SCALER'"
#endif

#if((_P0_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_P0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "'_P0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_OFF' if '_P0_TYPE_C_EMB_PORT_ROLE' = '_TYPE_C_PORT_SRC_ONLY'"
#endif

#if((_P0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) && ((_P0_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P0_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON', '_P0_TYPE_C_EMB_PORT_ROLE' Should Not be '_TYPE_C_PORT_SNK_ONLY' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) && ((_P0_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P0_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON', '_P0_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_DRP' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P0_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) && (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_1))
#warning "If '_P0_TYPE_C_EMB_PD3_1_EPR_SUPPORT' = '_ON', '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_1'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_P0_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "'_P0_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_SNK_ONLY' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_P0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "'_P0_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_NOT_SUPPORT'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && ((_P0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY)))
#warning "'_P0_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_HOST_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_HOST_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && ((_P0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P0_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY)))
#warning "'_P0_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_DEVICE_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_DEVICE_ONLY'"
#endif
#endif  // End of #if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_P1_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_P1_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P1_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P1_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER)
#warning "'_PORT_CTRL_EMBEDDED' PN Swap Should Use '_SWAP_BY_SCALER'"
#endif

#if((_P1_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_P1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "'_P1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_OFF' if '_P1_TYPE_C_EMB_PORT_ROLE' = '_TYPE_C_PORT_SRC_ONLY'"
#endif

#if((_P1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) && ((_P1_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P1_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON', '_P1_TYPE_C_EMB_PORT_ROLE' Should Not be '_TYPE_C_PORT_SNK_ONLY' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) && ((_P1_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P1_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON', '_P1_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_DRP' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P1_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) && (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_1))
#warning "If '_P1_TYPE_C_EMB_PD3_1_EPR_SUPPORT' = '_ON', '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_1'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_P1_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "'_P1_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_SNK_ONLY' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_P1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "'_P1_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_NOT_SUPPORT'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && ((_P1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY)))
#warning "'_P1_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_HOST_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_HOST_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && ((_P1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P1_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY)))
#warning "'_P1_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_DEVICE_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_DEVICE_ONLY'"
#endif
#endif  // End of #if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_P2_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_P2_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P2_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P2_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER)
#warning "'_PORT_CTRL_EMBEDDED' PN Swap Should Use '_SWAP_BY_SCALER'"
#endif

#if((_P2_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_P2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "'_P2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_OFF' if '_P2_TYPE_C_EMB_PORT_ROLE' = '_TYPE_C_PORT_SRC_ONLY'"
#endif

#if((_P2_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) && ((_P2_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P2_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON', '_P2_TYPE_C_EMB_PORT_ROLE' Should Not be '_TYPE_C_PORT_SNK_ONLY' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) && ((_P2_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P2_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON', '_P2_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_DRP' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P2_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) && (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_1))
#warning "If '_P2_TYPE_C_EMB_PD3_1_EPR_SUPPORT' = '_ON', '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_1'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_P2_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "'_P2_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_SNK_ONLY' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_P2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "'_P2_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_NOT_SUPPORT'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && ((_P2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY)))
#warning "'_P2_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_HOST_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_HOST_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && ((_P2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P2_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY)))
#warning "'_P2_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_DEVICE_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_DEVICE_ONLY'"
#endif
#endif  // End of #if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_P3_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_P3_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P3_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P3_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER)
#warning "'_PORT_CTRL_EMBEDDED' PN Swap Should Use '_SWAP_BY_SCALER'"
#endif

#if((_P3_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_P3_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "'_P3_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_OFF' if '_P3_TYPE_C_EMB_PORT_ROLE' = '_TYPE_C_PORT_SRC_ONLY'"
#endif

#if((_P3_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) && ((_P3_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P3_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON', '_P3_TYPE_C_EMB_PORT_ROLE' Should Not be '_TYPE_C_PORT_SNK_ONLY' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P3_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) && ((_P3_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P3_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON', '_P3_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_DRP' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P3_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) && (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_1))
#warning "If '_P3_TYPE_C_EMB_PD3_1_EPR_SUPPORT' = '_ON', '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_1'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_P3_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "'_P3_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_SNK_ONLY' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_P3_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "'_P3_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_NOT_SUPPORT'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && ((_P3_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P3_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY)))
#warning "'_P3_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_HOST_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_HOST_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && ((_P3_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P3_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY)))
#warning "'_P3_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_DEVICE_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_DEVICE_ONLY'"
#endif
#endif  // End of #if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_P4_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_P4_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P4_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_P4_TYPE_C_EXT_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER)
#warning "'_PORT_CTRL_EMBEDDED' PN Swap Should Use '_SWAP_BY_SCALER'"
#endif

#if((_P4_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_P4_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "'_P4_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_OFF' if '_P4_TYPE_C_EMB_PORT_ROLE' = '_TYPE_C_PORT_SRC_ONLY'"
#endif

#if((_P4_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) && ((_P4_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P4_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON', '_P4_TYPE_C_EMB_PORT_ROLE' Should Not be '_TYPE_C_PORT_SNK_ONLY' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P4_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) && ((_P4_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_DRP) || (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_0)))
#warning "If '_P4_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON', '_P4_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_DRP' and '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_0'"
#endif

#if((_P4_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) && (_TYPE_C_EMB_PD_VERSION < _PD_VERSION_3_1))
#warning "If '_P4_TYPE_C_EMB_PD3_1_EPR_SUPPORT' = '_ON', '_TYPE_C_EMB_PD_VERSION' Should >= '_PD_VERSION_3_1'"
#endif

#if((_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY) && (_P4_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY))
#warning "'_P4_TYPE_C_EMB_PORT_ROLE' Should be '_TYPE_C_PORT_SNK_ONLY' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_NOT_SUPPORT) && (_P4_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT))
#warning "'_P4_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_NOT_SUPPORT'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_HOST_ONLY) && ((_P4_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P4_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_HOST_ONLY)))
#warning "'_P4_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_HOST_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_HOST_ONLY'"
#endif

#if((_HW_USB_SUPPORT_ROLE == _TYPE_C_USB_DEVICE_ONLY) && ((_P4_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) && (_P4_TYPE_C_EMB_USB_ROLE != _TYPE_C_USB_DEVICE_ONLY)))
#warning "'_P4_TYPE_C_EMB_USB_ROLE' Should be '_TYPE_C_USB_NOT_SUPPORT' or '_TYPE_C_USB_DEVICE_ONLY' if '_HW_USB_SUPPORT_ROLE' = '_TYPE_C_USB_DEVICE_ONLY'"
#endif
#endif  // End of #if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
#warning "'_TYPE_C_GPIO_MODE_SUPPORT' Should be '_OFF' if '_ADAPTOR_TYPE_C_PORT_CTRL_TYPE' = '_PORT_CTRL_EMBEDDED'"
#endif

#if(_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)
#warning "'_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT' For '_PORT_CTRL_EMBEDDED' Should be _EXT_PORT_CTRL_NOT_EXIST"
#endif

#if(_ADAPTOR_TYPE_C_EMB_PORT_ROLE != _TYPE_C_PORT_SNK_ONLY)
#warning "'_ADAPTOR_TYPE_C_EMB_PORT_ROLE' Can Only be '_TYPE_C_PORT_SNK_ONLY'"
#endif

#if(_ADAPTOR_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _OFF)
#warning "'_ADAPTOR_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' Should Use '_ON'"
#endif

#if((_ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) || (_ADAPTOR_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON) || (_ADAPTOR_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON))
#warning "Adaptor Does Not Support PPS / Fast Role Swap / EPR Mode"
#endif
#endif  // End of #if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)

//--------------------------------------------------
// USB SMBUS IIC Check
//--------------------------------------------------
#if((_D0_USB_RTS_SMBUS_IIC == _NO_IIC_PIN) && ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || ((_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_HUB_RTS_SLAVE_ADDR != 0x00))))
#warning "'_D0_USB_RTS_SMBUS_IIC' Cannot be '_NO_IIC_PIN' if SMBus is Needed ('Port Ctrl = RTS' or 'Hub != None & Slave Addr != 0x00')"
#endif

#if((_D0_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "'_SW_IIC_SUPPORT' Cannot be '_OFF' if '_D0_USB_RTS_SMBUS_IIC' is '_SW_IIC_PIN_GPIO'"
#endif

#if(((_D0_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_D0_USB_RTS_SMBUS_IIC != _SW_IIC_PIN_GPIO)) && (_HW_IIC_SUPPORT == _OFF))
#warning "'_HW_IIC_SUPPORT' Cannot be '_OFF' if '_D0_USB_RTS_SMBUS_IIC' is '_HW_IIC_PIN_XX_YY'"
#endif

#if((_D1_USB_RTS_SMBUS_IIC == _NO_IIC_PIN) && ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || ((_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_HUB_RTS_SLAVE_ADDR != 0x00))))
#warning "'_D1_USB_RTS_SMBUS_IIC' Cannot be '_NO_IIC_PIN' if SMBus is Needed ('Port Ctrl = RTS' or 'Hub != None & Slave Addr != 0x00')"
#endif

#if((_D1_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "'_SW_IIC_SUPPORT' Cannot be '_OFF' if '_D1_USB_RTS_SMBUS_IIC' is '_SW_IIC_PIN_GPIO'"
#endif

#if(((_D1_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_D1_USB_RTS_SMBUS_IIC != _SW_IIC_PIN_GPIO)) && (_HW_IIC_SUPPORT == _OFF))
#warning "'_HW_IIC_SUPPORT' Cannot be '_OFF' if '_D1_USB_RTS_SMBUS_IIC' is '_HW_IIC_PIN_XX_YY'"
#endif

#if((_D2_USB_RTS_SMBUS_IIC == _NO_IIC_PIN) && ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || ((_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_HUB_RTS_SLAVE_ADDR != 0x00))))
#warning "'_D2_USB_RTS_SMBUS_IIC' Cannot be '_NO_IIC_PIN' if SMBus is Needed ('Port Ctrl = RTS' or 'Hub != None & Slave Addr != 0x00')"
#endif

#if((_D2_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "'_SW_IIC_SUPPORT' Cannot be '_OFF' if '_D2_USB_RTS_SMBUS_IIC' is '_SW_IIC_PIN_GPIO'"
#endif

#if(((_D2_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_D2_USB_RTS_SMBUS_IIC != _SW_IIC_PIN_GPIO)) && (_HW_IIC_SUPPORT == _OFF))
#warning "'_HW_IIC_SUPPORT' Cannot be '_OFF' if '_D2_USB_RTS_SMBUS_IIC' is '_HW_IIC_PIN_XX_YY'"
#endif

#if((_P0_USB_RTS_SMBUS_IIC == _NO_IIC_PIN) && ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || ((_P0_USB_HUB_TYPE != _USB_NONE) && (_P0_USB_HUB_RTS_SLAVE_ADDR != 0x00))))
#warning "'_P0_USB_RTS_SMBUS_IIC' Cannot be '_NO_IIC_PIN' if SMBus is Needed ('Port Ctrl = RTS' or 'Hub != None & Slave Addr != 0x00')"
#endif

#if((_P0_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "'_SW_IIC_SUPPORT' Cannot be '_OFF' if '_P0_USB_RTS_SMBUS_IIC' is '_SW_IIC_PIN_GPIO'"
#endif

#if(((_P0_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P0_USB_RTS_SMBUS_IIC != _SW_IIC_PIN_GPIO)) && (_HW_IIC_SUPPORT == _OFF))
#warning "'_HW_IIC_SUPPORT' Cannot be '_OFF' if '_P0_USB_RTS_SMBUS_IIC' is '_HW_IIC_PIN_XX_YY'"
#endif

#if((_P1_USB_RTS_SMBUS_IIC == _NO_IIC_PIN) && ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || ((_P1_USB_HUB_TYPE != _USB_NONE) && (_P1_USB_HUB_RTS_SLAVE_ADDR != 0x00))))
#warning "'_P1_USB_RTS_SMBUS_IIC' Cannot be '_NO_IIC_PIN' if SMBus is Needed ('Port Ctrl = RTS' or 'Hub != None & Slave Addr != 0x00')"
#endif

#if((_P1_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "'_SW_IIC_SUPPORT' Cannot be '_OFF' if '_P1_USB_RTS_SMBUS_IIC' is '_SW_IIC_PIN_GPIO'"
#endif

#if(((_P1_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P1_USB_RTS_SMBUS_IIC != _SW_IIC_PIN_GPIO)) && (_HW_IIC_SUPPORT == _OFF))
#warning "'_HW_IIC_SUPPORT' Cannot be '_OFF' if '_P1_USB_RTS_SMBUS_IIC' is '_HW_IIC_PIN_XX_YY'"
#endif

#if((_P2_USB_RTS_SMBUS_IIC == _NO_IIC_PIN) && ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || ((_P2_USB_HUB_TYPE != _USB_NONE) && (_P2_USB_HUB_RTS_SLAVE_ADDR != 0x00))))
#warning "'_P2_USB_RTS_SMBUS_IIC' Cannot be '_NO_IIC_PIN' if SMBus is Needed ('Port Ctrl = RTS' or 'Hub != None & Slave Addr != 0x00')"
#endif

#if((_P2_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "'_SW_IIC_SUPPORT' Cannot be '_OFF' if '_P2_USB_RTS_SMBUS_IIC' is '_SW_IIC_PIN_GPIO'"
#endif

#if(((_P2_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P2_USB_RTS_SMBUS_IIC != _SW_IIC_PIN_GPIO)) && (_HW_IIC_SUPPORT == _OFF))
#warning "'_HW_IIC_SUPPORT' Cannot be '_OFF' if '_P2_USB_RTS_SMBUS_IIC' is '_HW_IIC_PIN_XX_YY'"
#endif

#if((_P3_USB_RTS_SMBUS_IIC == _NO_IIC_PIN) && ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || ((_P3_USB_HUB_TYPE != _USB_NONE) && (_P3_USB_HUB_RTS_SLAVE_ADDR != 0x00))))
#warning "'_P3_USB_RTS_SMBUS_IIC' Cannot be '_NO_IIC_PIN' if SMBus is Needed ('Port Ctrl = RTS' or 'Hub != None & Slave Addr != 0x00')"
#endif

#if((_P3_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "'_SW_IIC_SUPPORT' Cannot be '_OFF' if '_P3_USB_RTS_SMBUS_IIC' is '_SW_IIC_PIN_GPIO'"
#endif

#if(((_P3_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P3_USB_RTS_SMBUS_IIC != _SW_IIC_PIN_GPIO)) && (_HW_IIC_SUPPORT == _OFF))
#warning "'_HW_IIC_SUPPORT' Cannot be '_OFF' if '_P3_USB_RTS_SMBUS_IIC' is '_HW_IIC_PIN_XX_YY'"
#endif

#if((_P4_USB_RTS_SMBUS_IIC == _NO_IIC_PIN) && ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || ((_P4_USB_HUB_TYPE != _USB_NONE) && (_P4_USB_HUB_RTS_SLAVE_ADDR != 0x00))))
#warning "'_P4_USB_RTS_SMBUS_IIC' Cannot be '_NO_IIC_PIN' if SMBus is Needed ('Port Ctrl = RTS' or 'Hub != None & Slave Addr != 0x00')"
#endif

#if((_P4_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "'_SW_IIC_SUPPORT' Cannot be '_OFF' if '_P4_USB_RTS_SMBUS_IIC' is '_SW_IIC_PIN_GPIO'"
#endif

#if(((_P4_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P4_USB_RTS_SMBUS_IIC != _SW_IIC_PIN_GPIO)) && (_HW_IIC_SUPPORT == _OFF))
#warning "'_HW_IIC_SUPPORT' Cannot be '_OFF' if '_P4_USB_RTS_SMBUS_IIC' is '_HW_IIC_PIN_XX_YY'"
#endif

//--------------------------------------------------
// USB Hub / Speed Related Check
//--------------------------------------------------
#if(((_D0_INPUT_PORT_TYPE == _D0_USB_PORT) && (_D0_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)) && (_D0_USB_SPEED == _USB_3_GEN2))
#warning "'_D0_USB_SPEED' should Not be '_USB_3_GEN2' if '_D0_USB_CONNECTOR_TYPE' == '_USB_CONNECTOR_TYPE_B'"
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_USB_PORT) && (_D0_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)) && (_D0_USB_LANE == _USB_3_LANE_X2))
#warning "'_D0_USB_LANE' should Not be '_USB_3_LANE_X2' if '_D0_USB_CONNECTOR_TYPE' == '_USB_CONNECTOR_TYPE_B'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT) && (_D0_USB_SPEED == _USB_2))
#warning "'_D0_USB_SPEED' should be '_USB_BILLBOARD_ONLY' if '_HW_USB_MAX_LINK_RATE_SUPPORT' == '_USB_SPEED_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_NOT_SUPPORT) && (_D0_USB_LANE > _USB_3_LANE_NONE))
#warning "'_D0_USB_LANE' should be '_USB_3_LANE_NONE' if '_HW_USB_MAX_LINK_LANE_SUPPORT' == '_USB_LANE_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G) && (_D0_USB_SPEED == _USB_3_GEN1))
#warning "'_D0_USB_SPEED' should Not be '_USB_3_GEN1' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_5G'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT < _USB_LANE_X1) && (_D0_USB_LANE == _USB_3_LANE_X1))
#warning "'_D0_USB_LANE' should Not be '_USB_3_LANE_X1' if '_HW_USB_MAX_LINK_LANE_SUPPORT' < '_USB_LANE_x1'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G) && (_D0_USB_SPEED == _USB_3_GEN2))
#warning "'_D0_USB_SPEED' should Not be '_USB_3_GEN2' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_10G'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT < _USB_LANE_X2) && (_D0_USB_LANE == _USB_3_LANE_X2))
#warning "'_D0_USB_LANE' should Not be '_USB_3_LANE_X2' if '_HW_USB_MAX_LINK_LANE_SUPPORT' < '_USB_LANE_x2'"
#endif

#if(((_D1_INPUT_PORT_TYPE == _D1_USB_PORT) && (_D1_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)) && (_D1_USB_SPEED == _USB_3_GEN2))
#warning "'_D1_USB_SPEED' should Not be '_USB_3_GEN2' if '_D1_USB_CONNECTOR_TYPE' == '_USB_CONNECTOR_TYPE_B'"
#endif

#if(((_D1_INPUT_PORT_TYPE == _D1_USB_PORT) && (_D1_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)) && (_D1_USB_LANE == _USB_3_LANE_X2))
#warning "'_D1_USB_LANE' should Not be '_USB_3_LANE_X2' if '_D1_USB_CONNECTOR_TYPE' == '_USB_CONNECTOR_TYPE_B'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT) && (_D1_USB_SPEED == _USB_2))
#warning "'_D1_USB_SPEED' should be '_USB_BILLBOARD_ONLY' if '_HW_USB_MAX_LINK_RATE_SUPPORT' == '_USB_SPEED_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_NOT_SUPPORT) && (_D1_USB_LANE > _USB_3_LANE_NONE))
#warning "'_D1_USB_LANE' should be '_USB_3_LANE_NONE' if '_HW_USB_MAX_LINK_LANE_SUPPORT' == '_USB_LANE_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G) && (_D1_USB_SPEED == _USB_3_GEN1))
#warning "'_D1_USB_SPEED' should Not be '_USB_3_GEN1' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_5G'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT < _USB_LANE_X1) && (_D1_USB_LANE == _USB_3_LANE_X1))
#warning "'_D1_USB_LANE' should Not be '_USB_3_LANE_X1' if '_HW_USB_MAX_LINK_LANE_SUPPORT' < '_USB_LANE_x1'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G) && (_D1_USB_SPEED == _USB_3_GEN2))
#warning "'_D1_USB_SPEED' should Not be '_USB_3_GEN2' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_10G'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT < _USB_LANE_X2) && (_D1_USB_LANE == _USB_3_LANE_X2))
#warning "'_D1_USB_LANE' should Not be '_USB_3_LANE_X2' if '_HW_USB_MAX_LINK_LANE_SUPPORT' < '_USB_LANE_x2'"
#endif

#if(((_D2_INPUT_PORT_TYPE == _D2_USB_PORT) && (_D2_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)) && (_D2_USB_SPEED == _USB_3_GEN2))
#warning "'_D2_USB_SPEED' should Not be '_USB_3_GEN2' if '_D2_USB_CONNECTOR_TYPE' == '_USB_CONNECTOR_TYPE_B'"
#endif

#if(((_D2_INPUT_PORT_TYPE == _D2_USB_PORT) && (_D2_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B)) && (_D2_USB_LANE == _USB_3_LANE_X2))
#warning "'_D2_USB_LANE' should Not be '_USB_3_LANE_X2' if '_D2_USB_CONNECTOR_TYPE' == '_USB_CONNECTOR_TYPE_B'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT) && (_D2_USB_SPEED == _USB_2))
#warning "'_D2_USB_SPEED' should be '_USB_BILLBOARD_ONLY' if '_HW_USB_MAX_LINK_RATE_SUPPORT' == '_USB_SPEED_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_NOT_SUPPORT) && (_D2_USB_LANE > _USB_3_LANE_NONE))
#warning "'_D2_USB_LANE' should be '_USB_3_LANE_NONE' if '_HW_USB_MAX_LINK_LANE_SUPPORT' == '_USB_LANE_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G) && (_D2_USB_SPEED == _USB_3_GEN1))
#warning "'_D2_USB_SPEED' should Not be '_USB_3_GEN1' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_5G'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT < _USB_LANE_X1) && (_D2_USB_LANE == _USB_3_LANE_X1))
#warning "'_D2_USB_LANE' should Not be '_USB_3_LANE_X1' if '_HW_USB_MAX_LINK_LANE_SUPPORT' < '_USB_LANE_x1'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G) && (_D2_USB_SPEED == _USB_3_GEN2))
#warning "'_D2_USB_SPEED' should Not be '_USB_3_GEN2' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_10G'"
#endif

#if((_HW_USB_MAX_LINK_LANE_SUPPORT < _USB_LANE_X2) && (_D2_USB_LANE == _USB_3_LANE_X2))
#warning "'_D2_USB_LANE' should Not be '_USB_3_LANE_X2' if '_HW_USB_MAX_LINK_LANE_SUPPORT' < '_USB_LANE_x2'"
#endif

#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE) && (_P0_USB_HUB_TYPE != _USB_NONE))
#warning "'_P0_USB_HUB_TYPE' should be '_USB_NONE' if '_P0_TYPE_C_PORT_CTRL_SUPPORT' == '_PORT_CTRL_NONE' (Please Select _USB_NONE when using USB Type-B Connector on Hub)"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT) && (_P0_USB_SPEED == _USB_2))
#warning "'_P0_USB_SPEED' should be '_USB_BILLBOARD_ONLY' if '_HW_USB_MAX_LINK_RATE_SUPPORT' == '_USB_SPEED_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G) && (_P0_USB_SPEED == _USB_3_GEN1))
#warning "'_P0_USB_SPEED' should Not be '_USB_3_GEN1' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_5G'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G) && (_P0_USB_SPEED == _USB_3_GEN2))
#warning "'_P0_USB_SPEED' should Not be '_USB_3_GEN2' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_10G'"
#endif

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE) && (_P1_USB_HUB_TYPE != _USB_NONE))
#warning "'_P1_USB_HUB_TYPE' should be '_USB_NONE' if '_P1_TYPE_C_PORT_CTRL_TYPE' == '_PORT_CTRL_NONE' (Please Select _USB_NONE when using USB Type-B Connector on Hub)"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT) && (_P1_USB_SPEED == _USB_2))
#warning "'_P1_USB_SPEED' should be '_USB_BILLBOARD_ONLY' if '_HW_USB_MAX_LINK_RATE_SUPPORT' == '_USB_SPEED_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G) && (_P1_USB_SPEED == _USB_3_GEN1))
#warning "'_P1_USB_SPEED' should Not be '_USB_3_GEN1' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_5G'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G) && (_P1_USB_SPEED == _USB_3_GEN2))
#warning "'_P1_USB_SPEED' should Not be '_USB_3_GEN2' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_10G'"
#endif

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE) && (_P2_USB_HUB_TYPE != _USB_NONE))
#warning "'_P2_USB_HUB_TYPE' should be '_USB_NONE' if '_P2_TYPE_C_PORT_CTRL_TYPE' == '_PORT_CTRL_NONE' (Please Select _USB_NONE when using USB Type-B Connector on Hub)"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT) && (_P2_USB_SPEED == _USB_2))
#warning "'_P2_USB_SPEED' should be '_USB_BILLBOARD_ONLY' if '_HW_USB_MAX_LINK_RATE_SUPPORT' == '_USB_SPEED_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G) && (_P2_USB_SPEED == _USB_3_GEN1))
#warning "'_P2_USB_SPEED' should Not be '_USB_3_GEN1' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_5G'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G) && (_P2_USB_SPEED == _USB_3_GEN2))
#warning "'_P2_USB_SPEED' should Not be '_USB_3_GEN2' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_10G'"
#endif

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE) && (_P3_USB_HUB_TYPE != _USB_NONE))
#warning "'_P3_USB_HUB_TYPE' should be '_USB_NONE' if '_P3_TYPE_C_PORT_CTRL_SUPPORT' == '_PORT_CTRL_NONE' (Please Select _USB_NONE when using USB Type-B Connector on Hub)"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT) && (_P3_USB_SPEED == _USB_2))
#warning "'_P3_USB_SPEED' should be '_USB_BILLBOARD_ONLY' if '_HW_USB_MAX_LINK_RATE_SUPPORT' == '_USB_SPEED_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G) && (_P3_USB_SPEED == _USB_3_GEN1))
#warning "'_P3_USB_SPEED' should Not be '_USB_3_GEN1' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_5G'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G) && (_P3_USB_SPEED == _USB_3_GEN2))
#warning "'_P3_USB_SPEED' should Not be '_USB_3_GEN2' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_10G'"
#endif

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE) && (_P4_USB_HUB_TYPE != _USB_NONE))
#warning "'_P4_USB_HUB_TYPE' should be '_USB_NONE' if '_P4_TYPE_C_PORT_CTRL_SUPPORT' == '_PORT_CTRL_NONE' (Please Select _USB_NONE when using USB Type-B Connector on Hub)"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_NOT_SUPPORT) && (_P4_USB_SPEED == _USB_2))
#warning "'_P4_USB_SPEED' should be '_USB_BILLBOARD_ONLY' if '_HW_USB_MAX_LINK_RATE_SUPPORT' == '_USB_SPEED_NOT_SUPPORT'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_5G) && (_P4_USB_SPEED == _USB_3_GEN1))
#warning "'_P4_USB_SPEED' should Not be '_USB_3_GEN1' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_5G'"
#endif

#if((_HW_USB_MAX_LINK_RATE_SUPPORT < _USB_SPEED_10G) && (_P4_USB_SPEED == _USB_3_GEN2))
#warning "'_P4_USB_SPEED' should Not be '_USB_3_GEN2' if '_HW_USB_MAX_LINK_RATE_SUPPORT' < '_USB_SPEED_10G'"
#endif

//--------------------------------------------------
// Billboard Support Setting Check
//--------------------------------------------------
#if((_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_SCALER' if '_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL) && (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
#warning "'_D0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_EXT_PORT_CTRL' if '_D0_TYPE_C_PORT_CTRL_TYPE = _PORT_CTRL_EMBEDDED'"
#endif

#if((_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D0_USB_HUB_TYPE == _USB_NONE))
#warning "'_D0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_D0_USB_HUB_TYPE == _USB_NONE'"
#endif

#if((_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
#warning "'_D0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_NONE' if '_D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON'"
#endif

#if((_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_SCALER' if '_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL) && (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
#warning "'_D1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_EXT_PORT_CTRL' if '_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED'"
#endif

#if((_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D1_USB_HUB_TYPE == _USB_NONE))
#warning "'_D1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_D1_USB_HUB_TYPE == _USB_NONE'"
#endif

#if((_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
#warning "'_D1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_NONE' if '_D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON'"
#endif

#if((_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_SCALER' if '_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_D2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL) && (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
#warning "'_D2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_EXT_PORT_CTRL' if '_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED'"
#endif

#if((_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D2_USB_HUB_TYPE == _USB_NONE))
#warning "'_D2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_D2_USB_HUB_TYPE == _USB_NONE'"
#endif

#if((_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_D2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
#warning "'_D2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_NONE' if '_D2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON'"
#endif

#if((_P0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_SCALER' if '_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL) && (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
#warning "'_P0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_EXT_PORT_CTRL' if '_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED'"
#endif

#if((_P0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P0_USB_HUB_TYPE == _USB_NONE))
#warning "'_P0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P0_USB_HUB_TYPE == _USB_NONE'"
#endif

#if((_P0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
#warning "'_P0_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_NONE' if '_P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON'"
#endif

#if((_P1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_SCALER' if '_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL) && (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
#warning "'_P1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_EXT_PORT_CTRL' if '_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED'"
#endif

#if((_P1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P1_USB_HUB_TYPE == _USB_NONE))
#warning "'_P1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P1_USB_HUB_TYPE == _USB_NONE'"
#endif

#if((_P1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_P1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
#warning "'_P1_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_NONE' if '_P1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON'"
#endif

#if((_P2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_SCALER' if '_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL) && (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
#warning "'_P2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_EXT_PORT_CTRL' if '_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED'"
#endif

#if((_P2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P2_USB_HUB_TYPE == _USB_NONE))
#warning "'_P2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P2_USB_HUB_TYPE == _USB_NONE'"
#endif

#if((_P2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_P2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
#warning "'_P2_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_NONE' if '_P2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON'"
#endif

#if((_P3_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P3_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_SCALER' if '_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P3_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P3_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P3_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL) && (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
#warning "'_P3_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_EXT_PORT_CTRL' if '_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED'"
#endif

#if((_P3_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P3_USB_HUB_TYPE == _USB_NONE))
#warning "'_P3_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P3_USB_HUB_TYPE == _USB_NONE'"
#endif

#if((_P3_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_P3_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
#warning "'_P3_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_NONE' if '_P3_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON'"
#endif

#if((_P4_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P4_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_SCALER' if '_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P4_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE))
#warning "'_P4_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_NONE'"
#endif

#if((_P4_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL) && (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))
#warning "'_P4_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_EXT_PORT_CTRL' if '_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED'"
#endif

#if((_P4_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_P4_USB_HUB_TYPE == _USB_NONE))
#warning "'_P4_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_HUB' if '_P4_USB_HUB_TYPE == _USB_NONE'"
#endif

#if((_P4_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_P4_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))
#warning "'_P4_TYPE_C_BILLBOARD_TYPE' should not be '_BILLBOARD_NONE' if '_P4_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON'"
#endif

#if(_ADAPTOR_TYPE_C_BILLBOARD_TYPE != _BILLBOARD_NONE)
#warning "'_ADAPTOR_TYPE_C_BILLBOARD_TYPE' should be '_BILLBOARD_NONE'"
#endif

#if((_D0_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE) && (_D1_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE) && (_D2_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE))
#if((_D0_TYPE_C_BILLBOARD_TYPE != _D1_TYPE_C_BILLBOARD_TYPE) || (_D0_TYPE_C_BILLBOARD_TYPE != _D2_TYPE_C_BILLBOARD_TYPE))
#warning "There should be only one type of '_Dx_TYPE_C_BILLBOARD_TYPE', check if '_D0_TYPE_C_BILLBOARD_TYPE' == '_D1_TYPE_C_BILLBOARD_TYPE == '_D2_TYPE_C_BILLBOARD_TYPE'"
#endif

#elif((_D0_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE) && (_D1_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE) && (_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE))
#if(_D0_TYPE_C_BILLBOARD_TYPE != _D1_TYPE_C_BILLBOARD_TYPE)
#warning "There should be only one type of '_Dx_TYPE_C_BILLBOARD_TYPE', check if '_D0_TYPE_C_BILLBOARD_TYPE' == '_D1_TYPE_C_BILLBOARD_TYPE'"
#endif

#elif((_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_D1_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE) && (_D2_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE))
#if(_D1_TYPE_C_BILLBOARD_TYPE != _D2_TYPE_C_BILLBOARD_TYPE)
#warning "There should be only one type of '_Dx_TYPE_C_BILLBOARD_TYPE', check if '_D1_TYPE_C_BILLBOARD_TYPE' == '_D2_TYPE_C_BILLBOARD_TYPE'"
#endif

#elif((_D0_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE) && (_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_NONE) && (_D2_TYPE_C_BILLBOARD_TYPE > _BILLBOARD_NONE))
#if(_D0_TYPE_C_BILLBOARD_TYPE != _D2_TYPE_C_BILLBOARD_TYPE)
#warning "There should be only one type of '_Dx_TYPE_C_BILLBOARD_TYPE', check if '_D0_TYPE_C_BILLBOARD_TYPE' == '_D2_TYPE_C_BILLBOARD_TYPE'"
#endif
#endif

// #if(_HW_USB2_SHARED_PHY_SUPPORT == _ON)
#if((_BILLBOARD_SCALER_SUPPORT == _ON) && (_USB2_HOST_SUPPORT == _ON) && (_SCALER_TYPE == _RL6978_SERIES))
#warning "The USB2 Host / BB Run-Time switching function is currently unavailable.  Presently, only BillBoard_Scaler is supported."
#endif
// #endif
//--------------------------------------------------
// TYPE-C 10-Bit ADC Support Check
//--------------------------------------------------
#if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)
#if(((_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) && (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)) ||\
    ((_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) && (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)) ||\
    ((_D2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) && (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)) ||\
    ((_P0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) && (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)) ||\
    ((_P1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) && (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)) ||\
    ((_P2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) && (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)) ||\
    ((_P3_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) && (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)) ||\
    ((_P4_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) && (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)))
#warning "Embedded Type-C and 10-Bit ADC Can NOT Be Supported At The Same Time."
#endif

#if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_NONE)
#warning "Can Not Support _10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT When No 10-Bit ADC Exist."
#endif
#endif


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Panel
//--------------------------------------------------
#if(_LVDS_VCM_USER_LEVEL > 0x1F)
#warning "LVDS VCM Selection Exceed The Maximum Value"
#endif

//////////////////////////
// eDPTx 1.2 HBR2 Panel //
//////////////////////////

//--------------------------------------------------
// eDPTx 1.2 HBR2 Panel Config Check
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_DPTX)

#if((_PANEL_DPTX_SWING_LEVEL + _PANEL_DPTX_PREEMPHASIS_LEVEL) > 3)
#warning "Panel DPTX Swing and Pre-emphasis over Spec!!!"
#endif

#if((_PANEL_DPTX_SPREAD_SPEED != _SPEED_30K) && (_PANEL_DPTX_SPREAD_SPEED != _SPEED_33K))
#warning "Panel DPTx Spread Spectrum Speed Should Be 30kHz~33kHz"
#endif

#endif


////////////////////
// V by One Panel //
////////////////////

//--------------------------------------------------
// V by One Panel Config Check
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_VBO)

#if((_PANEL_VBO_SPREAD_SPEED != _SPEED_27K) && (_PANEL_VBO_SPREAD_SPEED != _SPEED_30K))
#warning "Vbyone Spread Spectrum Speed Should Be 27kHz ~ 30kHz"
#endif

#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(_PANEL_VBO_OUTPUT_PORT < _VBO_16_DATA_LANE)
#if(_PANEL_VBO_FB_SWAP == _ENABLE)
#warning "Vbyone Does Not Support _PANEL_VBO_FB_SWAP As _PANEL_VBO_OUTPUT_PORT < _VBO_16_DATA_LANE"
#endif
#endif
#endif

#endif

/////////////////
// Memory DDR3 //
/////////////////

//-----------------------------------------------
// Macro of DDR Poewr Release Time Control
//-----------------------------------------------
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#if(_DDR_POWER_OFF_TIME > 1000)
#warning "DDR Power Off Time Delay Should Be Less 1S"
#endif
#endif


////////////////
// MBR + TCON //
////////////////
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_PCB_MBR_TCON_PIN == _TCON_NONE)
#warning "_PCB_MBR_TCON_PIN Should Be Specified When _MOTION_BLUR_REDUCTION_SUPPORT == _ON"
#endif

#if((_PWM_RST_SIGNAL_SEL == _TCON) && (_PCB_MBR_TCON_PIN == _TCON8)) // _HW_PWM_RST_BY_TCON_SELECT == _TCON8
#warning "_PCB_MBR_TCON_PIN Cannot Be _TCON8 When _PWM_RST_SIGNAL_SEL == _TCON"
#endif

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_PWM_RST_SIGNAL_SEL == _TCON) // _HW_PWM_RST_BY_TCON_SELECT == _TCON8
#warning "_PWM_RST_SIGNAL_SEL Cannot Be _TCON When _DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON"
#endif

#if(_PCB_MBR_TCON_PIN < _TCON9)
#warning "_PCB_MBR_TCON_PIN Must >= _TCON9 When _DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON"
#endif
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if((_PCB_MBR_TCON_PIN <= _TCON3) || (_PCB_MBR_TCON_PIN == _TCON8) || (_PCB_MBR_TCON_PIN == _TCON9)) // Valid TCON for RTK_ADV_MBR: 4, 5, 6, 7, 10, 11, 12, 13
#warning "_PCB_MBR_TCON_PIN Should Be TCON 4/5/6/7/10/11/12/13 When _RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON"
#endif
#endif
#endif


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// SW & HW IIC
//--------------------------------------------------
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)
#if(_SW_IIC_SUPPORT == _OFF)
#warning "If using SW IIC _SW_IIC_SUPPORT Should Be ON"
#endif
#endif

#if(_PCB_SEC_EEPROM_IIC == _SW_IIC_PIN_GPIO)
#if(_SW_IIC_SUPPORT == _OFF)
#warning "If using SW IIC _SW_IIC_SUPPORT Should Be ON"
#endif
#endif

#if(_SW_IIC_SUPPORT == _ON)
#if(_SW_IIC_CLK_DIV > _DIV_7)
#warning "_SW_IIC_CLK_DIV should be less than or equal to _DIV_7"
#endif
#endif

#if((_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) &&\
    (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO))
#if(_HW_IIC_SUPPORT == _OFF)
#warning "_HW_IIC_SUPPORT should be _ON"
#endif
#endif

#if(((_PCB_DEBUG_DDC == _VGA_DDC) && (_HW_ISP_DDC_EXIST != _ON)) ||\
    ((_PCB_DEBUG_DDC == _DDC0) && (_HW_DDC0_EXIST != _ON)) ||\
    ((_PCB_DEBUG_DDC == _DDC1) && (_HW_DDC1_EXIST != _ON)) ||\
    ((_PCB_DEBUG_DDC == _DDC2) && (_HW_DDC2_EXIST != _ON)) ||\
    ((_PCB_DEBUG_DDC == _DDC3) && (_HW_DDC3_EXIST != _ON)) ||\
    ((_PCB_DEBUG_DDC == _DDC4) && (_HW_DDC4_EXIST != _ON)) ||\
    ((_PCB_DEBUG_DDC == _DDC5) && (_HW_DDC5_EXIST != _ON)))
#warning "Debug DDC channel Selected Should be Exist"
#endif


////////////////
// TypeC Pmic //
////////////////
//--------------------------------------------------
// All PMIC Config Check
//--------------------------------------------------
#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)

#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) && (_EMB_TYPE_C_0_PMIC_FW_OCP_CURRENT_VALUE < 100))
#warning "Type-C 0 PMIC OCP ratio should not less than 100%!!!"
#endif

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
#if(((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) && ((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3))) ||\
    (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))
#if(_LOW_SPEED_ADC_SUPPORT != _ON)
#warning "Type-C 0 PMIC OCP should open _LOW_SPEED_ADC_SUPPORT!!!"
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
#warning "Type-C 0 PMIC Current is still not mapping to _LSADC_ADC_Pin!!!"
#endif // End of #if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)

#endif // End of #if((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) && ((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3))) ||\
    (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))
#if(_LOW_SPEED_ADC_SUPPORT != _ON)
#warning "Type-C 0 PMIC OCP should open _LOW_SPEED_ADC_SUPPORT!!!"
#endif

#if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
#warning "Type-C 0 PMIC Current is still not mapping to _LSADC_ADC_Pin!!!"
#endif // End of #if(_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)

#endif // End of #if((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

#if((_EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) && (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
#warning "Type-C 0 PMIC safety protect should open _FW_OCP_BY_LOW_SPEED_ADC or _OCP_BY_10_BIT_ADC!!!"
#endif // End of #if((_EMB_TYPE_C_0_PMIC_SAFETY_PROTECT_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) && (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
#warning "Type-C 0 PMIC can NOT use 10-Bit_ADC_OCP when Type-C 1 port exist!!!"
#endif

#endif // End of #if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) && (_EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE < 100))
#warning "Type-C 1 PMIC OCP ratio should not less than 100%!!!"
#endif

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
#if(((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) && ((_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3))) ||\
    (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))
#if(_LOW_SPEED_ADC_SUPPORT != _ON)
#warning "Type-C 1 PMIC OCP should open _LOW_SPEED_ADC_SUPPORT!!!"
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
#warning "Type-C 1 PMIC Current is still not mapping to _LSADC_ADC_Pin!!!"
#endif // End of #if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)

#endif // End of #if((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) && ((_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3))) ||\
    (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))
#if(_LOW_SPEED_ADC_SUPPORT != _ON)
#warning "Type-C 1 PMIC OCP should open _LOW_SPEED_ADC_SUPPORT!!!"
#endif

#if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
#warning "Type-C 1 PMIC Current is still not mapping to _LSADC_ADC_Pin!!!"
#endif // End of #if(_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)

#endif // End of #if((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC))
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

#if((_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON) && ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) && (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
#warning "Type-C 1 PMIC safety protect should open _FW_OCP_BY_LOW_SPEED_ADC or _OCP_BY_10_BIT_ADC!!!"
#endif // End of #if((_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON) && ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) && (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))
#warning "Type-C 1 PMIC can NOT use 10-Bit_ADC_OCP when Type-C 0 port exist!!!"
#endif

#endif // End of #if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)

#elif(_PORT_CTRL_TCPM_SUPPORT != _ON)

#if(_TYPE_C_PMIC_SUPPORT != _PMIC_NONE)
#warning "PMIC type should be _PMIC_NONE!!!"
#endif

#endif // End of #if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)

//--------------------------------------------------
// ADC Channel Mapping Check
//--------------------------------------------------
#if((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))

#if(_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)
#warning "Type-C 0/1 Vbus mapping conflict, should use another ADC channel!!!"
#endif

#if(((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE) && (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)) &&\
    (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL))
#warning "Type-C 0/1 Iout mapping conflict, should use another ADC channel!!!"
#endif

#endif // End of #if((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)
#if((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0))
#warning "Type-C 0 Vbus must mapping to 10-bit ADC channel 0 or LSADC channel 0!!!"
#endif

#elif(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
#if((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) &&\
    (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1) &&\
    (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2) &&\
    (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3) &&\
    (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) &&\
    (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1) &&\
    (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2) &&\
    (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3))
#warning "Type-C 0 Vbus must mapping to 10-bit ADC or LSADC channel _0_#!!!"
#endif
#endif // End of #if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_NONE) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0))
#warning "Type-C 0 Vbus Should Not be '_TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0' if '_HW_TYPE_C_LS_ADC_HW_VERSION' = '_TYPE_C_5B_LS_ADC_NONE'!!!"
#endif

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) &&\
    ((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
#warning "Type-C 0 Iout must mapping to LS_ADC channel!!!"
#endif

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) &&\
    ((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2) &&\
     (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)))
#warning "Type-C 0 Iout must mapping to LS_ADC channel!!!"
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

#if((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) && (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE))
#warning "Type-C 0 Iout must mapping to LS_ADC/10-bit_ADC channel!!!"
#endif

#endif // End of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)
#if((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1))
#warning "Type-C 1 Vbus must mapping to 10-bit ADC channel 1 or LSADC channel 1!!!"
#endif

#elif(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
#if((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) &&\
    (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1) &&\
    (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2) &&\
    (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3) &&\
    (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) &&\
    (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1) &&\
    (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2) &&\
    (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3))
#warning "Type-C 1 Vbus must mapping to 10-bit ADC or LSADC channel _0_#!!!"
#endif

#endif // End of #if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_NONE) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1))
#warning "Type-C 1 Vbus Should Not be '_TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1' if '_HW_TYPE_C_LS_ADC_HW_VERSION' = '_TYPE_C_5B_LS_ADC_NONE'!!!"
#endif

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) &&\
    ((_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
#warning "Type-C 1 Iout must mapping to LS_ADC channel!!!"
#endif

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) &&\
    ((_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2) &&\
     (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)))
#warning "Type-C 1 Iout must mapping to LS_ADC channel!!!"
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

#if((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) && (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE))
#warning "Type-C 1 Iout must mapping to LS_ADC/10-bit_ADC channel!!!"
#endif

#endif // End of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)

#if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)
#if((_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#if(((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)) &&\
    ((_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)))
#warning "Local Power Vbus must mapping to 10-bit ADC channel or NONE!!!"
#endif
#endif // End of #if((_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))

#elif(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
#if((_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#if(((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)) &&\
    ((_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3) &&\
     (_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)))
#warning "Local Power Vbus must mapping to 10-bit ADC or LS_ADC channel or NONE!!!"
#endif
#endif // End of #if((_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
#endif // End of #if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT)
#if((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) && (_LOCAL_POWER_VBUS_ADC_CHANNEL == _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL))
#warning "Local Power Vbus mapping conflict to Type-C 0, should use another ADC channel!!!"
#endif

#if(((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||\
     (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) ||\
     (_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON)) &&\
     (_LOCAL_POWER_IOUT_ADC_CHANNEL == _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL))
#warning "Local Power Iout mapping conflict to Type-C 0, should use another ADC channel!!!"
#endif
#endif // End of #if(_EMB_TYPE_C_0_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT)
#if((_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT) && (_LOCAL_POWER_VBUS_ADC_CHANNEL == _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL))
#warning "Local Power Vbus mapping conflict to Type-C 1, should use another ADC channel!!!"
#endif

#if(((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||\
     (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) ||\
     (_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON)) &&\
     (_LOCAL_POWER_IOUT_ADC_CHANNEL == _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL))
#warning "Local Power Iout mapping conflict to Type-C 1, should use another ADC channel!!!"
#endif
#endif // End of #if(_EMB_TYPE_C_1_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)


//--------------------------------------------------
// PMIC_NONE Config Check
//--------------------------------------------------
#if(_TYPE_C_PMIC_SUPPORT == _PMIC_NONE)

#if((_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN) || (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
#warning "PMIC HW IIC is NOT support!!!"
#endif

#if((_EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING) ||\
    (_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
#warning "Polling is not support when _TYPE_C_PMIC_TYPE is _PMIC_NONE!!!"
#endif

#endif // End of #if(_TYPE_C_PMIC_SUPPORT == _OFF)

//////////
// Misc //
//////////
#if((_EXT_XTAL != _XTAL14318K) && (_EXT_XTAL != _XTAL27000K))
#warning "_EXT_XTAL should be _XTAL14318K or _XTAL27000K Based On Pcb Design"
#endif

//--------------------------------------------------
// Int Detect By LSADC Channel Mapping Check
//--------------------------------------------------
#if((_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE) && (_LOW_SPEED_ADC_SUPPORT != _ON))
#warning "_LOW_SPEED_ADC_SUPPORT Should Be ON When using LSADC Detect INT"
#endif

//--------------------------------------------------
// LSADC Reduce Power Support Check
//--------------------------------------------------
#if(_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT == _ON)
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
#if(((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
#warning "_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT Should Be OFF When Supporting Embedded Type-C OCP."
#endif

#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
#warning "_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT Should Be OFF When ADC Detecting INT."
#endif

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if((_DX_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
#warning "_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT Should Be OFF When Supporting Embedded Type-C."
#endif
#endif
#endif

#endif // End of #ifndef __PCB_CONFIG_CHECK_H__
