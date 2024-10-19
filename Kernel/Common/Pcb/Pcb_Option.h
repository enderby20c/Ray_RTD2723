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
// ID Code      : Pcb_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_OPTION_H__
#define __PCB_OPTION_H__

//----------------------------------------------------------------------------------------------------
// ID Code      : PCB_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Include Pinshare mapping
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6829_SERIES)
#include <RL6829_Series_PinshareMapping.h>
#elif(_SCALER_TYPE == _RL6952_SERIES)
#include <RL6952_Series_PinshareMapping.h>
#elif(_SCALER_TYPE == _RL6978_SERIES)
#include <RL6978_Series_PinshareMapping.h>
#endif

//--------------------------------------------------
// Input Valid Port Option
//--------------------------------------------------
#define _INPUT_PORT_VALID                           ((GET_PORT_TYPE_VALUE(_A0_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D0_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D1_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D2_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D3_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D4_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D5_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D6_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D7_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D8_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D9_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D12_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D13_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D14_INPUT_PORT_TYPE) != _VALUE_PORT_NONE) +\
                                                     (GET_PORT_TYPE_VALUE(_D15_INPUT_PORT_TYPE) != _VALUE_PORT_NONE))

//--------------------------------------------------
// Dp Valid Port Option
//--------------------------------------------------
#define _DP_PORT_VALID                              ((GET_PORT_TYPE_VALUE(_D0_INPUT_PORT_TYPE) == _VALUE_PORT_DP) +\
                                                     (GET_PORT_TYPE_VALUE(_D1_INPUT_PORT_TYPE) == _VALUE_PORT_DP) +\
                                                     (GET_PORT_TYPE_VALUE(_D2_INPUT_PORT_TYPE) == _VALUE_PORT_DP) +\
                                                     (GET_PORT_TYPE_VALUE(_D7_INPUT_PORT_TYPE) == _VALUE_PORT_DP) +\
                                                     (GET_PORT_TYPE_VALUE(_D8_INPUT_PORT_TYPE) == _VALUE_PORT_DP))

//--------------------------------------------------
// Dp Physical Valid Port Option
//--------------------------------------------------
#define _DP_PHYSICAL_PORT_VALID                     ((GET_PORT_TYPE_VALUE(_D0_INPUT_PORT_TYPE) == _VALUE_PORT_DP) +\
                                                     (GET_PORT_TYPE_VALUE(_D1_INPUT_PORT_TYPE) == _VALUE_PORT_DP) +\
                                                     (GET_PORT_TYPE_VALUE(_D2_INPUT_PORT_TYPE) == _VALUE_PORT_DP))

//--------------------------------------------------
// Type C Valid Port Option
//--------------------------------------------------
#define _TYPE_C_PORT_VALID                          ((_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     (_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     (_D2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     (_P0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     (_P1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     (_P2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     (_P3_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     (_P4_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE) +\
                                                     1)

//--------------------------------------------------
// USB Hub Valid Port Option
//--------------------------------------------------
#define _USB_PORT_VALID                             ((_D0_USB_HUB_TYPE != _USB_NONE) +\
                                                     (_D1_USB_HUB_TYPE != _USB_NONE) +\
                                                     (_D2_USB_HUB_TYPE != _USB_NONE) +\
                                                     1)

//--------------------------------------------------
// HDR Metadata Port Option
//--------------------------------------------------
#define _HDR_METADATA_PORT_VALID                    (1 +\
                                                     (_D0_INPUT_PORT_TYPE != _D0_NO_PORT) +\
                                                     (_D1_INPUT_PORT_TYPE != _D1_NO_PORT) +\
                                                     (_D2_INPUT_PORT_TYPE != _D2_NO_PORT) +\
                                                     (_D3_INPUT_PORT_TYPE != _D3_NO_PORT) +\
                                                     (_D4_INPUT_PORT_TYPE != _D4_NO_PORT) +\
                                                     (_D5_INPUT_PORT_TYPE != _D5_NO_PORT))


//--------------------------------------------------
// Interface Support Option
//--------------------------------------------------
#define _VGA_SUPPORT                                (_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)

#if(_VGA_SUPPORT != _ON)
#undef _YPBPR_SUPPORT
#define _YPBPR_SUPPORT                              _OFF
#endif

#define _D0_HDMI_SUPPORT                            (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)


#define _D1_HDMI_SUPPORT                            (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)

#define _D2_HDMI_SUPPORT                            (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)

#define _D3_HDMI_SUPPORT                            (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)

#define _D4_HDMI_SUPPORT                            (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)

#define _D5_HDMI_SUPPORT                            (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)


#define _D1_HDMI_CEC_SUPPORT                        ((_D1_HDMI_SUPPORT == _ON) && (_D1_HDMI_CEC_PIN != _HDMI_CEC_NONE))

#define _D2_HDMI_CEC_SUPPORT                        ((_D2_HDMI_SUPPORT == _ON) && (_D2_HDMI_CEC_PIN != _HDMI_CEC_NONE))

#define _D3_HDMI_CEC_SUPPORT                        ((_D3_HDMI_SUPPORT == _ON) && (_D3_HDMI_CEC_PIN != _HDMI_CEC_NONE))

#define _D4_HDMI_CEC_SUPPORT                        ((_D4_HDMI_SUPPORT == _ON) && (_D4_HDMI_CEC_PIN != _HDMI_CEC_NONE))

#define _HDMI_CEC_PORT_AMOUNT                       (_D1_HDMI_CEC_SUPPORT + _D2_HDMI_CEC_SUPPORT + _D3_HDMI_CEC_SUPPORT + _D4_HDMI_CEC_SUPPORT)

#define _D0_DP_SUPPORT                              (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#define _D1_DP_SUPPORT                              (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#define _D2_DP_SUPPORT                              (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#define _D3_DP_SUPPORT                              (_OFF)

#define _D4_DP_SUPPORT                              (_OFF)

#define _D5_DP_SUPPORT                              (_OFF)

#define _D7_DP_SUPPORT                              (_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

#define _D8_DP_SUPPORT                              (_D8_INPUT_PORT_TYPE == _D8_DP_PORT)

#define _D9_DP_SUPPORT                              (_D9_INPUT_PORT_TYPE == _D9_DP_PORT)

#define _HDMI_SUPPORT                               ((_D0_HDMI_SUPPORT == _ON) ||\
                                                     (_D1_HDMI_SUPPORT == _ON) ||\
                                                     (_D2_HDMI_SUPPORT == _ON) ||\
                                                     (_D3_HDMI_SUPPORT == _ON) ||\
                                                     (_D4_HDMI_SUPPORT == _ON) ||\
                                                     (_D5_HDMI_SUPPORT == _ON))

#define _DP_SUPPORT                                 ((_D0_DP_SUPPORT == _ON) ||\
                                                     (_D1_DP_SUPPORT == _ON) ||\
                                                     (_D2_DP_SUPPORT == _ON) ||\
                                                     (_D3_DP_SUPPORT == _ON) ||\
                                                     (_D4_DP_SUPPORT == _ON) ||\
                                                     (_D5_DP_SUPPORT == _ON) ||\
                                                     (_D7_DP_SUPPORT == _ON) ||\
                                                     (_D8_DP_SUPPORT == _ON))

#define _DUAL_DP_SUPPORT                            ((_D7_DP_SUPPORT == _ON) ||\
                                                     (_D8_DP_SUPPORT == _ON))


#define _DP_TBT_SUPPORT                             (((_D0_DP_SUPPORT == _ON) && (_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)) ||\
                                                     ((_D1_DP_SUPPORT == _ON) && (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)) ||\
                                                     ((_D2_DP_SUPPORT == _ON) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))

#if((_D7_SEARCH_MAIN_PORT_ONLY == _ON) || (_D8_SEARCH_MAIN_PORT_ONLY == _ON))
#define _DUAL_DP_SEARCH_MAIN_PORT_ONLY              _ON
#else
#define _DUAL_DP_SEARCH_MAIN_PORT_ONLY              _OFF
#endif

#define _DIGITAL_PORT_SUPPORT                       ((_HDMI_SUPPORT == _ON) ||\
                                                     (_DP_SUPPORT == _ON))

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
#define _DUAL_DP_INPUT_PORT                         _D7_INPUT_PORT

#if(_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#define _DUAL_DP_MAIN_PORT                          _D0_INPUT_PORT
#define _DUAL_DP_SUB_PORT                           _D1_INPUT_PORT
#elif(_D7_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#define _DUAL_DP_MAIN_PORT                          _D1_INPUT_PORT
#define _DUAL_DP_SUB_PORT                           _D0_INPUT_PORT
#else
#define _DUAL_DP_MAIN_PORT                          _NO_INPUT_PORT
#define _DUAL_DP_SUB_PORT                           _NO_INPUT_PORT
#endif

#elif(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
#define _DUAL_DP_INPUT_PORT                         _D8_INPUT_PORT

#if(_D8_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#define _DUAL_DP_MAIN_PORT                          _D1_INPUT_PORT
#define _DUAL_DP_SUB_PORT                           _D2_INPUT_PORT
#elif(_D8_D2_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#define _DUAL_DP_MAIN_PORT                          _D2_INPUT_PORT
#define _DUAL_DP_SUB_PORT                           _D1_INPUT_PORT
#else
#define _DUAL_DP_MAIN_PORT                          _NO_INPUT_PORT
#define _DUAL_DP_SUB_PORT                           _NO_INPUT_PORT
#endif
#endif

//--------------------------------------------------
// HDMI External Edid Size
//--------------------------------------------------
#define _EDID_EXTERNAL_EEPROM_MAX_SIZE              MAXOF(MAXOF(((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) ? _D1_EDID_EXTERNAL_EEPROM_MAX_SIZE : _EDID_EEPROM_SIZE_NONE),\
                                                                ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) ? _D2_EDID_EXTERNAL_EEPROM_MAX_SIZE : _EDID_EEPROM_SIZE_NONE)),\
                                                          MAXOF(((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) ? _D3_EDID_EXTERNAL_EEPROM_MAX_SIZE : _EDID_EEPROM_SIZE_NONE),\
                                                                ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) ? _D4_EDID_EXTERNAL_EEPROM_MAX_SIZE : _EDID_EEPROM_SIZE_NONE)))

//--------------------------------------------------
// HDMI External Switch Option
//--------------------------------------------------
#define _HDMI_EXTERNAL_SWITCH_SUPPORT               (((_D12_INPUT_PORT_TYPE == _D12_HDMI_PORT) && (_D12_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3)) ||\
                                                     ((_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT) && (_D14_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4)))

//--------------------------------------------------
// HDMI 2.0 Option
//--------------------------------------------------
#define _D0_HDMI20_SUPPORT                          ((_HW_HDMI20_SUPPORT_PORT == _HDMI20_D0_D1) &&\
                                                     (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT))

#define _D1_HDMI20_SUPPORT                          (((_HW_HDMI20_SUPPORT_PORT == _HDMI20_D0_D1) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D1_D2) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D1_D2_D3)) &&\
                                                     (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))

#define _D2_HDMI20_SUPPORT                          (((_HW_HDMI20_SUPPORT_PORT == _HDMI20_D2_D3_D4_D5) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D2_D3) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D1_D2_D3) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D2) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D1_D2)) &&\
                                                     (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT))

#define _D3_HDMI20_SUPPORT                          (((_HW_HDMI20_SUPPORT_PORT == _HDMI20_D2_D3_D4_D5) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D3_D4) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D2_D3) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D1_D2_D3)) &&\
                                                     (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT))

#define _D4_HDMI20_SUPPORT                          (((_HW_HDMI20_SUPPORT_PORT == _HDMI20_D2_D3_D4_D5) || (_HW_HDMI20_SUPPORT_PORT == _HDMI20_D3_D4)) &&\
                                                     (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT))

#define _D5_HDMI20_SUPPORT                          ((_HW_HDMI20_SUPPORT_PORT == _HDMI20_D2_D3_D4_D5) &&\
                                                     (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT))

#define _HDMI20_SUPPORT                             ((_D0_HDMI20_SUPPORT == _ON) ||\
                                                     (_D1_HDMI20_SUPPORT == _ON) ||\
                                                     (_D2_HDMI20_SUPPORT == _ON) ||\
                                                     (_D3_HDMI20_SUPPORT == _ON) ||\
                                                     (_D4_HDMI20_SUPPORT == _ON) ||\
                                                     (_D5_HDMI20_SUPPORT == _ON))

//--------------------------------------------------
// HDMI 2.1 Option
//--------------------------------------------------
#define _D1_HDMI_FRL_SUPPORT                        ((_HW_HDMI_FRL_SUPPORT_PORT == _HDMI_FRL_MAC_D1_D2_D3) &&\
                                                     (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) &&\
                                                     (_D1_HDMI_MAC_TYPE == _HDMI_MAC_TMDS_FRL))

#define _D2_HDMI_FRL_SUPPORT                        (((_HW_HDMI_FRL_SUPPORT_PORT == _HDMI_FRL_MAC_D2_D3) || (_HW_HDMI_FRL_SUPPORT_PORT == _HDMI_FRL_MAC_D1_D2_D3)) &&\
                                                     (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) &&\
                                                     (_D2_HDMI_MAC_TYPE == _HDMI_MAC_TMDS_FRL))

#define _D3_HDMI_FRL_SUPPORT                        (((_HW_HDMI_FRL_SUPPORT_PORT == _HDMI_FRL_MAC_D3_D4) || (_HW_HDMI_FRL_SUPPORT_PORT == _HDMI_FRL_MAC_D1_D2_D3)) &&\
                                                     (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) &&\
                                                     (_D3_HDMI_MAC_TYPE == _HDMI_MAC_TMDS_FRL))

#define _D4_HDMI_FRL_SUPPORT                        ((_HW_HDMI_FRL_SUPPORT_PORT == _HDMI_FRL_MAC_D3_D4) &&\
                                                     (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) &&\
                                                     (_D4_HDMI_MAC_TYPE == _HDMI_MAC_TMDS_FRL))

#define _HDMI_FRL_SUPPORT                           ((_D1_HDMI_FRL_SUPPORT == _ON) ||\
                                                     (_D2_HDMI_FRL_SUPPORT == _ON) ||\
                                                     (_D3_HDMI_FRL_SUPPORT == _ON) ||\
                                                     (_D4_HDMI_FRL_SUPPORT == _ON))

#if(_D1_HDMI_FRL_SUPPORT == _ON)
#if(_D1_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_300MHZ)
#define _D1_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_3G
#elif((_D1_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_600MHZ) && (_D1_HDMI_MAIN_LINK_LANES == _HDMI_THREE_LANE))
#define _D1_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_6G_3LANES
#elif((_D1_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_600MHZ) && (_D1_HDMI_MAIN_LINK_LANES == _HDMI_FOUR_LANE))
#define _D1_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_6G_4LANES
#elif(_D1_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_800MHZ)
#define _D1_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_8G
#elif(_D1_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_1000MHZ)
#define _D1_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_10G
#elif(_D1_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_1200MHZ)
#define _D1_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_12G
#endif
#else
#define _D1_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_NONE
#endif

#if(_D2_HDMI_FRL_SUPPORT == _ON)
#if(_D2_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_300MHZ)
#define _D2_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_3G
#elif((_D2_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_600MHZ) && (_D2_HDMI_MAIN_LINK_LANES == _HDMI_THREE_LANE))
#define _D2_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_6G_3LANES
#elif((_D2_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_600MHZ) && (_D2_HDMI_MAIN_LINK_LANES == _HDMI_FOUR_LANE))
#define _D2_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_6G_4LANES
#elif(_D2_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_800MHZ)
#define _D2_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_8G
#elif(_D2_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_1000MHZ)
#define _D2_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_10G
#elif(_D2_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_1200MHZ)
#define _D2_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_12G
#endif
#else
#define _D2_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_NONE
#endif

#if(_D3_HDMI_FRL_SUPPORT == _ON)
#if(_D3_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_300MHZ)
#define _D3_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_3G
#elif((_D3_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_600MHZ) && (_D3_HDMI_MAIN_LINK_LANES == _HDMI_THREE_LANE))
#define _D3_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_6G_3LANES
#elif((_D3_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_600MHZ) && (_D3_HDMI_MAIN_LINK_LANES == _HDMI_FOUR_LANE))
#define _D3_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_6G_4LANES
#elif(_D3_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_800MHZ)
#define _D3_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_8G
#elif(_D3_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_1000MHZ)
#define _D3_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_10G
#elif(_D3_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_1200MHZ)
#define _D3_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_12G
#endif
#else
#define _D3_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_NONE
#endif

#if(_D4_HDMI_FRL_SUPPORT == _ON)
#if(_D4_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_300MHZ)
#define _D4_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_3G
#elif((_D4_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_600MHZ) && (_D4_HDMI_MAIN_LINK_LANES == _HDMI_THREE_LANE))
#define _D4_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_6G_3LANES
#elif((_D4_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_600MHZ) && (_D4_HDMI_MAIN_LINK_LANES == _HDMI_FOUR_LANE))
#define _D4_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_6G_4LANES
#elif(_D4_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_800MHZ)
#define _D4_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_8G
#elif(_D4_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_1000MHZ)
#define _D4_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_10G
#elif(_D4_HDMI_LINK_CLK_RATE == _HDMI_LINK_SPEED_1200MHZ)
#define _D4_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_12G
#endif
#else
#define _D4_HDMI_FRL_MAX_LINK_RATE                  _HDMI_FRL_RATE_NONE
#endif

//--------------------------------------------------
// Select DP Aux Channel DDC
//--------------------------------------------------
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC0))
#define _D0_AUX_DDC_CHANNEL                         _D0_AUX_MAP_DDC0_PIN
#else
#define _D0_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC1))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC1_PIN
#else
#define _D1_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC2))
#define _D2_AUX_DDC_CHANNEL                         _D2_AUX_MAP_DDC2_PIN
#else
#define _D2_AUX_DDC_CHANNEL                         _NO_AUX
#endif

//--------------------------------------------------
// Definition of HDCP circuit shared between ports
//--------------------------------------------------
#define _DP_HDCP_ARBITER_SUPPORT                    (((_D0_AUX_DDC_CHANNEL != _NO_AUX) +\
                                                      (_D1_AUX_DDC_CHANNEL != _NO_AUX) +\
                                                      (_D2_AUX_DDC_CHANNEL != _NO_AUX)) > _HW_DP_HDCP_CIRCUIT_COUNT)

//--------------------------------------------------
// Embedded EDID Option
//--------------------------------------------------
#define _EMBEDDED_EDID_SUPPORT                      ((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))

#define _EMBEDDED_HDMI_EDID_SUPPORT                 (((_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D0_HDMI_SUPPORT == _ON)) ||\
                                                     ((_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D1_HDMI_SUPPORT == _ON)) ||\
                                                     ((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D2_HDMI_SUPPORT == _ON)) ||\
                                                     ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D3_HDMI_SUPPORT == _ON)) ||\
                                                     ((_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D4_HDMI_SUPPORT == _ON)) ||\
                                                     ((_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D5_HDMI_SUPPORT == _ON)))

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#define _EDID_TABLE_LOCATED_IN_FLASH                (((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))

#define _WRITE_EDID_LOCATION_BY_USER_SUPPORT        (((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)))

#define _D0_HDMI_MULTI_EDID_SUPPORT                 ((_D0_HDMI_SUPPORT == _ON) &&\
                                                     (_D0_MAX_HDMI_EDID_COUNT > 1))

#define _D1_HDMI_MULTI_EDID_SUPPORT                 ((_D1_HDMI_SUPPORT == _ON) &&\
                                                     (_D1_MAX_HDMI_EDID_COUNT > 1))

#define _D2_HDMI_MULTI_EDID_SUPPORT                 ((_D2_HDMI_SUPPORT == _ON) &&\
                                                     (_D2_MAX_HDMI_EDID_COUNT > 1))

#define _D3_HDMI_MULTI_EDID_SUPPORT                 ((_D3_HDMI_SUPPORT == _ON) &&\
                                                     (_D3_MAX_HDMI_EDID_COUNT > 1))

#define _D4_HDMI_MULTI_EDID_SUPPORT                 ((_D4_HDMI_SUPPORT == _ON) &&\
                                                     (_D4_MAX_HDMI_EDID_COUNT > 1))

#define _D5_HDMI_MULTI_EDID_SUPPORT                 ((_D5_HDMI_SUPPORT == _ON) &&\
                                                     (_D5_MAX_HDMI_EDID_COUNT > 1))

#define _HDMI_MULTI_EDID_SUPPORT                    ((_D0_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D1_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D2_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D3_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D4_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D5_HDMI_MULTI_EDID_SUPPORT == _ON))

//--------------------------------------------------
// Display Spread Spectrum Option
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_LVDS)
#define _DCLK_SPREAD_RANGE                          _LVDS_SPREAD_RANGE
#define _DCLK_SPREAD_SPEED                          _LVDS_SPREAD_SPEED
#elif(_PANEL_STYLE == _PANEL_DPTX)
#define _DCLK_SPREAD_RANGE                          0
#define _DCLK_SPREAD_SPEED                          _SPEED_33K
#elif(_PANEL_STYLE == _PANEL_VBO)
#define _DCLK_SPREAD_RANGE                          _PANEL_VBO_SPREAD_RANGE
#define _DCLK_SPREAD_SPEED                          _PANEL_VBO_SPREAD_SPEED
#elif(_PANEL_STYLE == _PANEL_NONE)
#define _DCLK_SPREAD_RANGE                          0
#define _DCLK_SPREAD_SPEED                          _SPEED_33K
#endif

#ifndef _DCLK_SPREAD_RANGE_MAX
#define _DCLK_SPREAD_RANGE_MAX                      _DCLK_SPREAD_RANGE
#endif

//--------------------------------------------------
// PCB power Option
//--------------------------------------------------
#define PCB_POWER_5V_DETECT()                       (_TRUE)

//--------------------------------------------------
// PWM Function Support Option
//--------------------------------------------------
#define _PWM_FUNCTION_SUPPORT                       ((_PWM0_EN == _ON) ||\
                                                     (_PWM1_EN == _ON) ||\
                                                     (_PWM2_EN == _ON) ||\
                                                     (_PWM3_EN == _ON) ||\
                                                     (_PWM4_EN == _ON) ||\
                                                     (_PWM5_EN == _ON) ||\
                                                     (_PWM0_PSAV_EN == _ON) ||\
                                                     (_PWM1_PSAV_EN == _ON) ||\
                                                     (_PWM2_PSAV_EN == _ON) ||\
                                                     (_PWM3_PSAV_EN == _ON) ||\
                                                     (_PWM4_PSAV_EN == _ON) ||\
                                                     (_PWM5_PSAV_EN == _ON) ||\
                                                     (_PWM0_PDOW_EN == _ON) ||\
                                                     (_PWM1_PDOW_EN == _ON) ||\
                                                     (_PWM2_PDOW_EN == _ON) ||\
                                                     (_PWM3_PDOW_EN == _ON) ||\
                                                     (_PWM4_PDOW_EN == _ON) ||\
                                                     (_PWM5_PDOW_EN == _ON))

#define _PWM_BYPASS_MODE_SUPPORT                    ((_PWM0_BYPASS_MODE_EN == _ON) ||\
                                                     (_PWM1_BYPASS_MODE_EN == _ON) ||\
                                                     (_PWM2_BYPASS_MODE_EN == _ON) ||\
                                                     (_PWM3_BYPASS_MODE_EN == _ON) ||\
                                                     (_PWM4_BYPASS_MODE_EN == _ON) ||\
                                                     (_PWM5_BYPASS_MODE_EN == _ON))

//--------------------------------------------------
// UART Function Support Option
//--------------------------------------------------
#define _UART_SUPPORT                               (((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON)) ||\
                                                     ((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON)) ||\
                                                     ((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON)))

//--------------------------------------------------
// HW IIC Function Support Option
//--------------------------------------------------
#define _HW_IIC_0_SUPPORT                           ((_HW_HW_IIC_0_EXIST == _ON) && (_HW_IIC_SUPPORT == _ON))
#define _HW_IIC_1_SUPPORT                           ((_HW_HW_IIC_1_EXIST == _ON) && (_HW_IIC_SUPPORT == _ON))
#define _HW_IIC_0_SPEED                             _HW_IIC_SPEED
#define _HW_IIC_1_SPEED                             _HW_IIC_SPEED
#define _TYPEC_IIC_0_SUPPORT                        ((_HW_TYPEC_IIC_0_EXIST == _ON) && (_TYPEC_IIC_SUPPORT == _ON) && (_EMB_TYPE_C_0_PMIC_IIC == _PMIC_NO_IIC_PIN))
#define _TYPEC_IIC_0_SPEED                          _TYPEC_IIC_SPEED

//--------------------------------------------------
// Eeprom Size Range Option
//--------------------------------------------------
#if(_EEPROM_TYPE == _EEPROM_24LC16)
#define _EEPROM_SIZE_RANGE                          _EEPROM_SIZE_RANGE_WORD
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
#define _EEPROM_SIZE_RANGE                          _EEPROM_SIZE_RANGE_WORD
#elif(_EEPROM_TYPE == _EEPROM_CAT24M01)
#define _EEPROM_SIZE_RANGE                          _EEPROM_SIZE_RANGE_DWORD
#elif(_EEPROM_TYPE == _EEPROM_24256)
#define _EEPROM_SIZE_RANGE                          _EEPROM_SIZE_RANGE_WORD
#endif

//--------------------------------------------------
// Type C Connector Support Definition
//--------------------------------------------------
#define _D0_TYPE_C_CONNECTOR_SUPPORT                ((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D0_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_C))
#define _D1_TYPE_C_CONNECTOR_SUPPORT                ((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D1_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_C))
#define _D2_TYPE_C_CONNECTOR_SUPPORT                ((_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) || (_D2_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_C))
#define _P0_TYPE_C_CONNECTOR_SUPPORT                (_P0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C)
#define _P1_TYPE_C_CONNECTOR_SUPPORT                (_P1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C)
#define _P2_TYPE_C_CONNECTOR_SUPPORT                (_P2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C)
#define _P3_TYPE_C_CONNECTOR_SUPPORT                (_P3_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C)
#define _P4_TYPE_C_CONNECTOR_SUPPORT                (_P4_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C)
#define _ADAPTOR_TYPE_C_CONNECTOR_SUPPORT           (_ADAPTOR_CONNECTOR_TYPE == _ADAPTOR_CONNECTOR_TYPE_C)

#define _TYPE_C_CONNECTOR_SUPPORT                   ((_D0_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_CONNECTOR_SUPPORT == _ON))

//--------------------------------------------------
// Type C Port Controller Support Definition
//--------------------------------------------------
#define _D0_TYPE_C_PORT_CTRL_SUPPORT                (_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
#define _D1_TYPE_C_PORT_CTRL_SUPPORT                (_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
#define _D2_TYPE_C_PORT_CTRL_SUPPORT                (_D2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
#define _P0_TYPE_C_PORT_CTRL_SUPPORT                (_P0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
#define _P1_TYPE_C_PORT_CTRL_SUPPORT                (_P1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
#define _P2_TYPE_C_PORT_CTRL_SUPPORT                (_P2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
#define _P3_TYPE_C_PORT_CTRL_SUPPORT                (_P3_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
#define _P4_TYPE_C_PORT_CTRL_SUPPORT                (_P4_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
#define _ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT           (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)

#define _TYPE_C_DX_PORT_CTRL_SUPPORT                ((_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON))

#define _TYPE_C_PX_PORT_CTRL_SUPPORT                ((_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON))

#define _TYPE_C_PORT_CTRL_SUPPORT                   ((_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON))

#define _PORT_CTRL_RTS_SUPPORT                      ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) ||\
                                                     (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) ||\
                                                     (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) ||\
                                                     (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) ||\
                                                     (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) ||\
                                                     (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) ||\
                                                     (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) ||\
                                                     (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) ||\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS))

#define _PORT_CTRL_RTD_SUPPORT                      ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) ||\
                                                     (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) ||\
                                                     (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) ||\
                                                     (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) ||\
                                                     (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) ||\
                                                     (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) ||\
                                                     (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) ||\
                                                     (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) ||\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD))

#define _DX_PORT_CTRL_EMBEDDED_SUPPORT              ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
                                                     (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
                                                     (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))

#define _PX_PORT_CTRL_EMBEDDED_SUPPORT              ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
                                                     (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
                                                     (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
                                                     (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) ||\
                                                     (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))

#define _PORT_CTRL_EMBEDDED_SUPPORT                 ((_DX_PORT_CTRL_EMBEDDED_SUPPORT == _ON) ||\
                                                     (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED))

#define _EMB_TYPE_C_PORT_VALID                      ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) +\
                                                     1)

#define _PORT_CTRL_USER_SERIES_SUPPORT              ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) ||\
                                                     (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) ||\
                                                     (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) ||\
                                                     (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) ||\
                                                     (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) ||\
                                                     (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) ||\
                                                     (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) ||\
                                                     (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) ||\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#define _PORT_CTRL_TCPM_SUPPORT                     ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) ||\
                                                     (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) ||\
                                                     (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) ||\
                                                     (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) ||\
                                                     (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) ||\
                                                     (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) ||\
                                                     (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) ||\
                                                     (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) ||\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM))

#define _TCPM_PORT_VALID                            ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) +\
                                                     (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) +\
                                                     (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) +\
                                                     (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) +\
                                                     (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) +\
                                                     (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) +\
                                                     (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) +\
                                                     (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM) +\
                                                     (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM))

#define _PORT_CTRL_PD3_1_EPR_SUPPORT                ((_PORT_CTRL_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_PORT_CTRL_EXT_PD3_1_EPR_SUPPORT == _ON))

//--------------------------------------------------
// Type C Embedded Port Ctrl Definitions
//--------------------------------------------------
#define _PORT_CTRL_EMB_DEAD_BATTERY_SUPPORT         ((_D0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))

#define _PORT_CTRL_EMB_PD3_PPS_SUPPORT              ((_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON))

#define _PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF   ((_D0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON) ||\
                                                     (_D1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON) ||\
                                                     (_D2_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON) ||\
                                                     (_P0_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON) ||\
                                                     (_P1_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON) ||\
                                                     (_P2_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON) ||\
                                                     (_P3_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON) ||\
                                                     (_P4_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON))

#define _PORT_CTRL_EMB_PD3_1_EPR_SUPPORT            ((_D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON))

#define _DX_TYPE_C_EMB_DP_ALT_MODE_SUPPORT          ((_D0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))

#define _PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT          ((_DX_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON))

#if((_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _D0_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_RX
#else
#define _D0_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_NONE
#endif

#if((_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _D1_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_RX
#else
#define _D1_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_NONE
#endif

#if((_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _D2_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_RX
#else
#define _D2_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_NONE
#endif

#if((_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _P0_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_TX
#else
#define _P0_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_NONE
#endif

#if((_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _P1_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_TX
#else
#define _P1_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_NONE
#endif

#if((_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _P2_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_TX
#else
#define _P2_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_NONE
#endif

#if((_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _P3_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_TX
#else
#define _P3_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_NONE
#endif

#if((_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _P4_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_TX
#else
#define _P4_TYPE_C_EMB_PD_BEHAVIOR_TYPE             _TYPE_C_DP_NONE
#endif

#if((_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED) || (_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)))
#define _ADAPTOR_TYPE_C_EMB_PD_BEHAVIOR_TYPE        _TYPE_C_DP_NONE
#else
#define _ADAPTOR_TYPE_C_EMB_PD_BEHAVIOR_TYPE        _TYPE_C_DP_NONE
#endif

#define _PORT_CTRL_EMB_DP_RX_SUPPORT                ((_D0_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX) ||\
                                                     (_D1_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX) ||\
                                                     (_D2_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX) ||\
                                                     (_P0_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX) ||\
                                                     (_P1_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX) ||\
                                                     (_P2_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX) ||\
                                                     (_P3_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX) ||\
                                                     (_P4_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX) ||\
                                                     (_ADAPTOR_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX))

#define _PORT_CTRL_EMB_DP_TX_SUPPORT                ((_D0_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX) ||\
                                                     (_D1_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX) ||\
                                                     (_D2_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX) ||\
                                                     (_P0_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX) ||\
                                                     (_P1_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX) ||\
                                                     (_P2_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX) ||\
                                                     (_P3_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX) ||\
                                                     (_P4_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX) ||\
                                                     (_ADAPTOR_TYPE_C_EMB_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX))

//--------------------------------------------------
// Type C RTS / User Port Ctrl Definitions
//--------------------------------------------------
#define _PORT_CTRL_EXT_PD3_1_EPR_SUPPORT            ((_D0_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON))

//--------------------------------------------------
// Type C PCB Port PMIC Support Definitions
//--------------------------------------------------
#define _TYPE_C_PMIC_SUPPORT                        ((_D0_TYPE_C_PMIC_TYPE != _PMIC_NONE) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE != _PMIC_NONE) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE != _PMIC_NONE) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE != _PMIC_NONE) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE != _PMIC_NONE) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE != _PMIC_NONE) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE != _PMIC_NONE) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE != _PMIC_NONE) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE != _PMIC_NONE))

#define _TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT         ((_D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) ||\
                                                     (_D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) ||\
                                                     (_D2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) ||\
                                                     (_P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) ||\
                                                     (_P1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) ||\
                                                     (_P2_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) ||\
                                                     (_P3_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) ||\
                                                     (_P4_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC))

//--------------------------------------------------
// Type C TCPM Port Ctrl Definitions
//--------------------------------------------------
#define _PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC         ((_D0_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON) ||\
                                                     (_D1_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON) ||\
                                                     (_D2_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON) ||\
                                                     (_P0_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON) ||\
                                                     (_P1_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON) ||\
                                                     (_P2_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON) ||\
                                                     (_P3_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON) ||\
                                                     (_P4_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_TCPM_OCP_PROTECT_BY_TCPC == _ON))

#define _PORT_CTRL_TCPM_OVP_UVP_SUPPORT             ((_D0_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_D1_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_D2_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P0_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P1_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P2_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P3_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_P4_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON) ||\
                                                     (_ADAPTOR_TYPE_C_TCPM_OVP_UVP_SUPPORT == _ON))

#define _PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT          ((_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                     (_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON))

//--------------------------------------------------
// Usb Hub Support Definition
//--------------------------------------------------
#define _D0_USB_HUB_SUPPORT                         (_D0_USB_HUB_TYPE != _USB_NONE)
#define _D1_USB_HUB_SUPPORT                         (_D1_USB_HUB_TYPE != _USB_NONE)
#define _D2_USB_HUB_SUPPORT                         (_D2_USB_HUB_TYPE != _USB_NONE)
#define _P0_USB_HUB_SUPPORT                         (_P0_USB_HUB_TYPE != _USB_NONE)
#define _P1_USB_HUB_SUPPORT                         (_P1_USB_HUB_TYPE != _USB_NONE)
#define _P2_USB_HUB_SUPPORT                         (_P2_USB_HUB_TYPE != _USB_NONE)
#define _P3_USB_HUB_SUPPORT                         (_P3_USB_HUB_TYPE != _USB_NONE)
#define _P4_USB_HUB_SUPPORT                         (_P4_USB_HUB_TYPE != _USB_NONE)

#define _USB_HUB_SUPPORT                            ((_D0_USB_HUB_SUPPORT == _ON) ||\
                                                     (_D1_USB_HUB_SUPPORT == _ON) ||\
                                                     (_D2_USB_HUB_SUPPORT == _ON) ||\
                                                     (_P0_USB_HUB_SUPPORT == _ON) ||\
                                                     (_P1_USB_HUB_SUPPORT == _ON) ||\
                                                     (_P2_USB_HUB_SUPPORT == _ON) ||\
                                                     (_P3_USB_HUB_SUPPORT == _ON) ||\
                                                     (_P4_USB_HUB_SUPPORT == _ON))

#define _D0_USB_HUB_RTS_SUPPORT                     (_D0_USB_HUB_TYPE == _USB_HUB_RTS)
#define _D1_USB_HUB_RTS_SUPPORT                     (_D1_USB_HUB_TYPE == _USB_HUB_RTS)
#define _D2_USB_HUB_RTS_SUPPORT                     (_D2_USB_HUB_TYPE == _USB_HUB_RTS)
#define _P0_USB_HUB_RTS_SUPPORT                     (_P0_USB_HUB_TYPE == _USB_HUB_RTS)
#define _P1_USB_HUB_RTS_SUPPORT                     (_P1_USB_HUB_TYPE == _USB_HUB_RTS)
#define _P2_USB_HUB_RTS_SUPPORT                     (_P2_USB_HUB_TYPE == _USB_HUB_RTS)
#define _P3_USB_HUB_RTS_SUPPORT                     (_P3_USB_HUB_TYPE == _USB_HUB_RTS)
#define _P4_USB_HUB_RTS_SUPPORT                     (_P4_USB_HUB_TYPE == _USB_HUB_RTS)

#define _USB_HUB_RTS_SUPPORT                        ((_D0_USB_HUB_RTS_SUPPORT == _ON) ||\
                                                     (_D1_USB_HUB_RTS_SUPPORT == _ON) ||\
                                                     (_D2_USB_HUB_RTS_SUPPORT == _ON) ||\
                                                     (_P0_USB_HUB_RTS_SUPPORT == _ON) ||\
                                                     (_P1_USB_HUB_RTS_SUPPORT == _ON) ||\
                                                     (_P2_USB_HUB_RTS_SUPPORT == _ON) ||\
                                                     (_P3_USB_HUB_RTS_SUPPORT == _ON) ||\
                                                     (_P4_USB_HUB_RTS_SUPPORT == _ON))

#define _D0_USB_HUB_USER_SERIES_SUPPORT             (_D0_USB_HUB_TYPE == _USB_HUB_USER)
#define _D1_USB_HUB_USER_SERIES_SUPPORT             (_D1_USB_HUB_TYPE == _USB_HUB_USER)
#define _D2_USB_HUB_USER_SERIES_SUPPORT             (_D2_USB_HUB_TYPE == _USB_HUB_USER)
#define _P0_USB_HUB_USER_SERIES_SUPPORT             (_P0_USB_HUB_TYPE == _USB_HUB_USER)
#define _P1_USB_HUB_USER_SERIES_SUPPORT             (_P1_USB_HUB_TYPE == _USB_HUB_USER)
#define _P2_USB_HUB_USER_SERIES_SUPPORT             (_P2_USB_HUB_TYPE == _USB_HUB_USER)
#define _P3_USB_HUB_USER_SERIES_SUPPORT             (_P3_USB_HUB_TYPE == _USB_HUB_USER)
#define _P4_USB_HUB_USER_SERIES_SUPPORT             (_P4_USB_HUB_TYPE == _USB_HUB_USER)

#define _USB_HUB_USER_SERIES_SUPPORT                ((_D0_USB_HUB_USER_SERIES_SUPPORT == _ON) ||\
                                                     (_D1_USB_HUB_USER_SERIES_SUPPORT == _ON) ||\
                                                     (_D2_USB_HUB_USER_SERIES_SUPPORT == _ON) ||\
                                                     (_P0_USB_HUB_USER_SERIES_SUPPORT == _ON) ||\
                                                     (_P1_USB_HUB_USER_SERIES_SUPPORT == _ON) ||\
                                                     (_P2_USB_HUB_USER_SERIES_SUPPORT == _ON) ||\
                                                     (_P3_USB_HUB_USER_SERIES_SUPPORT == _ON) ||\
                                                     (_P4_USB_HUB_USER_SERIES_SUPPORT == _ON))

#define _DX_TYPE_C_EXT_DP_ALT_MODE_SUPPORT          ((((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)) ||\
                                                     (((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)) ||\
                                                     (((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_TCPM)) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT != _EXT_PORT_CTRL_NOT_EXIST)))

//--------------------------------------------------
// Usb Type-B Conn. Definition
//--------------------------------------------------
#define _D0_USB_TYPE_B_SUPPORT                      ((_D0_INPUT_PORT_TYPE == _D0_USB_PORT) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B))
#define _D1_USB_TYPE_B_SUPPORT                      ((_D1_INPUT_PORT_TYPE == _D1_USB_PORT) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B))
#define _D2_USB_TYPE_B_SUPPORT                      ((_D2_INPUT_PORT_TYPE == _D2_USB_PORT) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_CONNECTOR_TYPE == _USB_CONNECTOR_TYPE_B))

//--------------------------------------------------
// Usb3 Supported Speed Definition
//--------------------------------------------------
#define _D0_USB_3_SPEED_GEN2_SUPPORT                (((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D0_INPUT_PORT_TYPE == _D0_USB_PORT)) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_SPEED == _USB_3_GEN2))
#define _D1_USB_3_SPEED_GEN2_SUPPORT                (((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_USB_PORT)) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_SPEED == _USB_3_GEN2))
#define _D2_USB_3_SPEED_GEN2_SUPPORT                (((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_USB_PORT)) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_SPEED == _USB_3_GEN2))

//--------------------------------------------------
// Usb3 Supported Lane Definition
//--------------------------------------------------
#define _D0_USB_3_LANE_X2_SUPPORT                   (((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D0_INPUT_PORT_TYPE == _D0_USB_PORT)) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_LANE == _USB_3_LANE_X2))
#define _D1_USB_3_LANE_X2_SUPPORT                   (((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_USB_PORT)) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_LANE == _USB_3_LANE_X2))
#define _D2_USB_3_LANE_X2_SUPPORT                   (((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_USB_PORT)) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_LANE == _USB_3_LANE_X2))

//--------------------------------------------------
// Usb2 Path Definition
//--------------------------------------------------
#define _D0_USB2_GO_THROUGH_SCALER                  (((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D0_INPUT_PORT_TYPE == _D0_USB_PORT)) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U2_HUB_TRACE_TYPE == _USB_U2_TRACE_GO_THROUGH_SCALER))
#define _D1_USB2_GO_THROUGH_SCALER                  (((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_USB_PORT)) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U2_HUB_TRACE_TYPE == _USB_U2_TRACE_GO_THROUGH_SCALER))
#define _D2_USB2_GO_THROUGH_SCALER                  (((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_USB_PORT)) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U2_HUB_TRACE_TYPE == _USB_U2_TRACE_GO_THROUGH_SCALER))

//--------------------------------------------------
// Usb3 Path Definition
//--------------------------------------------------
#define _D0_USB3_GO_THROUGH_SCALER                  (((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D0_INPUT_PORT_TYPE == _D0_USB_PORT)) && (_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))
#define _D1_USB3_GO_THROUGH_SCALER                  (((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_USB_PORT)) && (_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))
#define _D2_USB3_GO_THROUGH_SCALER                  (((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_USB_PORT)) && (_D2_USB_HUB_TYPE != _USB_NONE) && (_D2_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))

//--------------------------------------------------
// Usb Hub Communication Definition
//--------------------------------------------------
#define _D0_USB_HUB_COMMUNICATION_SUPPORT           (((_D0_USB_HUB_TYPE == _USB_HUB_RTS) && (_D0_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_D0_USB_HUB_RTS_SLAVE_ADDR != 0x00)) || (_D0_USB_HUB_TYPE == _USB_HUB_USER))
#define _D1_USB_HUB_COMMUNICATION_SUPPORT           (((_D1_USB_HUB_TYPE == _USB_HUB_RTS) && (_D1_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_D1_USB_HUB_RTS_SLAVE_ADDR != 0x00)) || (_D1_USB_HUB_TYPE == _USB_HUB_USER))
#define _D2_USB_HUB_COMMUNICATION_SUPPORT           (((_D2_USB_HUB_TYPE == _USB_HUB_RTS) && (_D2_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_D2_USB_HUB_RTS_SLAVE_ADDR != 0x00)) || (_D2_USB_HUB_TYPE == _USB_HUB_USER))
#define _P0_USB_HUB_COMMUNICATION_SUPPORT           (((_P0_USB_HUB_TYPE == _USB_HUB_RTS) && (_P0_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P0_USB_HUB_RTS_SLAVE_ADDR != 0x00)) || (_P0_USB_HUB_TYPE == _USB_HUB_USER))
#define _P1_USB_HUB_COMMUNICATION_SUPPORT           (((_P1_USB_HUB_TYPE == _USB_HUB_RTS) && (_P1_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P1_USB_HUB_RTS_SLAVE_ADDR != 0x00)) || (_P1_USB_HUB_TYPE == _USB_HUB_USER))
#define _P2_USB_HUB_COMMUNICATION_SUPPORT           (((_P2_USB_HUB_TYPE == _USB_HUB_RTS) && (_P2_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P2_USB_HUB_RTS_SLAVE_ADDR != 0x00)) || (_P2_USB_HUB_TYPE == _USB_HUB_USER))
#define _P3_USB_HUB_COMMUNICATION_SUPPORT           (((_P3_USB_HUB_TYPE == _USB_HUB_RTS) && (_P3_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P3_USB_HUB_RTS_SLAVE_ADDR != 0x00)) || (_P3_USB_HUB_TYPE == _USB_HUB_USER))
#define _P4_USB_HUB_COMMUNICATION_SUPPORT           (((_P4_USB_HUB_TYPE == _USB_HUB_RTS) && (_P4_USB_RTS_SMBUS_IIC != _NO_IIC_PIN) && (_P4_USB_HUB_RTS_SLAVE_ADDR != 0x00)) || (_P4_USB_HUB_TYPE == _USB_HUB_USER))

#define _USB_HUB_COMMUNICATION_SUPPORT              ((_D0_USB_HUB_COMMUNICATION_SUPPORT == _ON) ||\
                                                     (_D1_USB_HUB_COMMUNICATION_SUPPORT == _ON) ||\
                                                     (_D2_USB_HUB_COMMUNICATION_SUPPORT == _ON) ||\
                                                     (_P0_USB_HUB_COMMUNICATION_SUPPORT == _ON) ||\
                                                     (_P1_USB_HUB_COMMUNICATION_SUPPORT == _ON) ||\
                                                     (_P2_USB_HUB_COMMUNICATION_SUPPORT == _ON) ||\
                                                     (_P3_USB_HUB_COMMUNICATION_SUPPORT == _ON) ||\
                                                     (_P4_USB_HUB_COMMUNICATION_SUPPORT == _ON))

//--------------------------------------------------
// Type-C SMBus Communication Support Definition
//--------------------------------------------------
#define _D0_USB_HUB_RTS_SMBUS_SUPPORT               ((_D0_USB_HUB_TYPE == _USB_HUB_RTS) && (_D0_USB_HUB_COMMUNICATION_SUPPORT == _ON))
#define _D1_USB_HUB_RTS_SMBUS_SUPPORT               ((_D1_USB_HUB_TYPE == _USB_HUB_RTS) && (_D1_USB_HUB_COMMUNICATION_SUPPORT == _ON))
#define _D2_USB_HUB_RTS_SMBUS_SUPPORT               ((_D2_USB_HUB_TYPE == _USB_HUB_RTS) && (_D2_USB_HUB_COMMUNICATION_SUPPORT == _ON))
#define _P0_USB_HUB_RTS_SMBUS_SUPPORT               ((_P0_USB_HUB_TYPE == _USB_HUB_RTS) && (_P0_USB_HUB_COMMUNICATION_SUPPORT == _ON))
#define _P1_USB_HUB_RTS_SMBUS_SUPPORT               ((_P1_USB_HUB_TYPE == _USB_HUB_RTS) && (_P1_USB_HUB_COMMUNICATION_SUPPORT == _ON))
#define _P2_USB_HUB_RTS_SMBUS_SUPPORT               ((_P2_USB_HUB_TYPE == _USB_HUB_RTS) && (_P2_USB_HUB_COMMUNICATION_SUPPORT == _ON))
#define _P3_USB_HUB_RTS_SMBUS_SUPPORT               ((_P3_USB_HUB_TYPE == _USB_HUB_RTS) && (_P3_USB_HUB_COMMUNICATION_SUPPORT == _ON))
#define _P4_USB_HUB_RTS_SMBUS_SUPPORT               ((_P4_USB_HUB_TYPE == _USB_HUB_RTS) && (_P4_USB_HUB_COMMUNICATION_SUPPORT == _ON))

#define _USB_HUB_RTS_SMBUS_SUPPORT                  ((_D0_USB_HUB_RTS_SMBUS_SUPPORT == _ON) ||\
                                                     (_D1_USB_HUB_RTS_SMBUS_SUPPORT == _ON) ||\
                                                     (_D2_USB_HUB_RTS_SMBUS_SUPPORT == _ON) ||\
                                                     (_P0_USB_HUB_RTS_SMBUS_SUPPORT == _ON) ||\
                                                     (_P1_USB_HUB_RTS_SMBUS_SUPPORT == _ON) ||\
                                                     (_P2_USB_HUB_RTS_SMBUS_SUPPORT == _ON) ||\
                                                     (_P3_USB_HUB_RTS_SMBUS_SUPPORT == _ON) ||\
                                                     (_P4_USB_HUB_RTS_SMBUS_SUPPORT == _ON))

#define _USB_RTS_SMBUS_SUPPORT                      ((_PORT_CTRL_RTS_SUPPORT == _ON) || (_USB_HUB_RTS_SMBUS_SUPPORT == _ON))

//--------------------------------------------------
// Usb Type-C / Hub SMBus Communication SW_IIC Support Definition
//--------------------------------------------------
#define _D0_USB_COMMUNICATION_SW_IIC                (((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D0_INPUT_PORT_TYPE == _D0_USB_PORT)) && (_D0_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO))
#define _D1_USB_COMMUNICATION_SW_IIC                (((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_USB_PORT)) && (_D1_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO))
#define _D2_USB_COMMUNICATION_SW_IIC                (((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_USB_PORT)) && (_D2_USB_RTS_SMBUS_IIC == _SW_IIC_PIN_GPIO))

//--------------------------------------------------
// Type-C RTS / User Port Controller Definition
//--------------------------------------------------
#define _PORT_CTRL_RTS_DET_CC_ATTACH_BY_SMBUS       (((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)))

#define _PORT_CTRL_RTS_DET_ALT_MODE_READY_BY_SMBUS  (((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) && (_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)))

#define _PORT_CTRL_USER_DET_CC_ATTACH_BY_SMBUS      (((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)))

#define _PORT_CTRL_USER_DET_ALT_MODE_READY_BY_SMBUS (((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER) && (_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)))

#define _PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT      ((_D0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) ||\
                                                     (_D1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) ||\
                                                     (_D2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) ||\
                                                     (_P0_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) ||\
                                                     (_P1_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) ||\
                                                     (_P2_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) ||\
                                                     (_P3_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) ||\
                                                     (_P4_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER) ||\
                                                     (_ADAPTOR_TYPE_C_EXT_LANE_SWAP_FOR_ORIENTATION == _SWAP_BY_SCALER))

//--------------------------------------------------
// Type-C RTD / User Port Controller Detect CC Attach / Alt Mode Ready By SMBUS
//--------------------------------------------------
#define _PORT_CTRL_RTD_DET_CC_ATTACH_BY_SMBUS       (((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_D0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_D1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_D2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P0_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P1_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P2_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P3_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P4_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_ADAPTOR_TYPE_C_EXT_CC_ATTACH_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)))

#define _PORT_CTRL_RTD_DET_ALT_MODE_READY_BY_SMBUS  (((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_D0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_D1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_D2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P0_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P1_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P2_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P3_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_P4_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)) ||\
                                                     ((_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) && (_ADAPTOR_TYPE_C_EXT_ALT_MODE_READY_DETECT == _EXT_PORT_CTRL_DETECT_BY_SMBUS)))

//--------------------------------------------------
// Billboard Support Definition
//--------------------------------------------------
#define _D0_BILLBOARD_SCALER_SUPPORT                ((_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _D1_BILLBOARD_SCALER_SUPPORT                ((_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _D2_BILLBOARD_SCALER_SUPPORT                ((_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_D2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P0_BILLBOARD_SCALER_SUPPORT                ((_P0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P1_BILLBOARD_SCALER_SUPPORT                ((_P1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P2_BILLBOARD_SCALER_SUPPORT                ((_P2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P3_BILLBOARD_SCALER_SUPPORT                ((_P3_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P3_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P4_BILLBOARD_SCALER_SUPPORT                ((_P4_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) && (_P4_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))

#define _BILLBOARD_SCALER_SUPPORT                   ((_D0_BILLBOARD_SCALER_SUPPORT == _ON) ||\
                                                     (_D1_BILLBOARD_SCALER_SUPPORT == _ON) ||\
                                                     (_D2_BILLBOARD_SCALER_SUPPORT == _ON) ||\
                                                     (_P0_BILLBOARD_SCALER_SUPPORT == _ON) ||\
                                                     (_P1_BILLBOARD_SCALER_SUPPORT == _ON) ||\
                                                     (_P2_BILLBOARD_SCALER_SUPPORT == _ON) ||\
                                                     (_P3_BILLBOARD_SCALER_SUPPORT == _ON) ||\
                                                     (_P4_BILLBOARD_SCALER_SUPPORT == _ON))

#define _D0_BILLBOARD_EXT_PORT_CTRL_SUPPORT         (_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL)
#define _D1_BILLBOARD_EXT_PORT_CTRL_SUPPORT         (_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL)
#define _D2_BILLBOARD_EXT_PORT_CTRL_SUPPORT         (_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL)
#define _P0_BILLBOARD_EXT_PORT_CTRL_SUPPORT         (_P0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL)
#define _P1_BILLBOARD_EXT_PORT_CTRL_SUPPORT         (_P1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL)
#define _P2_BILLBOARD_EXT_PORT_CTRL_SUPPORT         (_P2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL)
#define _P3_BILLBOARD_EXT_PORT_CTRL_SUPPORT         (_P3_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL)
#define _P4_BILLBOARD_EXT_PORT_CTRL_SUPPORT         (_P4_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_EXT_PORT_CTRL)

#define _BILLBOARD_EXT_PORT_CTRL_SUPPORT            ((_D0_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_D1_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_D2_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P0_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P1_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P2_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P3_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_P4_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON))

#define _D0_BILLBOARD_HUB_SUPPORT                   (_D0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB)
#define _D1_BILLBOARD_HUB_SUPPORT                   (_D1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB)
#define _D2_BILLBOARD_HUB_SUPPORT                   (_D2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB)
#define _P0_BILLBOARD_HUB_SUPPORT                   (_P0_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB)
#define _P1_BILLBOARD_HUB_SUPPORT                   (_P1_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB)
#define _P2_BILLBOARD_HUB_SUPPORT                   (_P2_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB)
#define _P3_BILLBOARD_HUB_SUPPORT                   (_P3_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB)
#define _P4_BILLBOARD_HUB_SUPPORT                   (_P4_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB)

#define _BILLBOARD_HUB_SUPPORT                      ((_D0_BILLBOARD_HUB_SUPPORT == _ON) ||\
                                                     (_D1_BILLBOARD_HUB_SUPPORT == _ON) ||\
                                                     (_D2_BILLBOARD_HUB_SUPPORT == _ON) ||\
                                                     (_P0_BILLBOARD_HUB_SUPPORT == _ON) ||\
                                                     (_P1_BILLBOARD_HUB_SUPPORT == _ON) ||\
                                                     (_P2_BILLBOARD_HUB_SUPPORT == _ON) ||\
                                                     (_P3_BILLBOARD_HUB_SUPPORT == _ON) ||\
                                                     (_P4_BILLBOARD_HUB_SUPPORT == _ON))

#define _D0_BILLBOARD_RTS_HUB_SUPPORT               ((_D0_USB_HUB_TYPE == _USB_HUB_RTS) && (_D0_BILLBOARD_HUB_SUPPORT == _ON))
#define _D1_BILLBOARD_RTS_HUB_SUPPORT               ((_D1_USB_HUB_TYPE == _USB_HUB_RTS) && (_D1_BILLBOARD_HUB_SUPPORT == _ON))
#define _D2_BILLBOARD_RTS_HUB_SUPPORT               ((_D2_USB_HUB_TYPE == _USB_HUB_RTS) && (_D2_BILLBOARD_HUB_SUPPORT == _ON))
#define _P0_BILLBOARD_RTS_HUB_SUPPORT               ((_P0_USB_HUB_TYPE == _USB_HUB_RTS) && (_P0_BILLBOARD_HUB_SUPPORT == _ON))
#define _P1_BILLBOARD_RTS_HUB_SUPPORT               ((_P1_USB_HUB_TYPE == _USB_HUB_RTS) && (_P1_BILLBOARD_HUB_SUPPORT == _ON))
#define _P2_BILLBOARD_RTS_HUB_SUPPORT               ((_P2_USB_HUB_TYPE == _USB_HUB_RTS) && (_P2_BILLBOARD_HUB_SUPPORT == _ON))
#define _P3_BILLBOARD_RTS_HUB_SUPPORT               ((_P3_USB_HUB_TYPE == _USB_HUB_RTS) && (_P3_BILLBOARD_HUB_SUPPORT == _ON))
#define _P4_BILLBOARD_RTS_HUB_SUPPORT               ((_P4_USB_HUB_TYPE == _USB_HUB_RTS) && (_P4_BILLBOARD_HUB_SUPPORT == _ON))

#define _BILLBOARD_RTS_HUB_SUPPORT                  ((_D0_BILLBOARD_RTS_HUB_SUPPORT == _ON) ||\
                                                     (_D1_BILLBOARD_RTS_HUB_SUPPORT == _ON) ||\
                                                     (_D2_BILLBOARD_RTS_HUB_SUPPORT == _ON) ||\
                                                     (_P0_BILLBOARD_RTS_HUB_SUPPORT == _ON) ||\
                                                     (_P1_BILLBOARD_RTS_HUB_SUPPORT == _ON) ||\
                                                     (_P2_BILLBOARD_RTS_HUB_SUPPORT == _ON) ||\
                                                     (_P3_BILLBOARD_RTS_HUB_SUPPORT == _ON) ||\
                                                     (_P4_BILLBOARD_RTS_HUB_SUPPORT == _ON))


#define _D0_BILLBOARD_USER_HUB_SUPPORT              ((_D0_USB_HUB_TYPE == _USB_HUB_USER) && (_D0_BILLBOARD_HUB_SUPPORT == _ON))
#define _D1_BILLBOARD_USER_HUB_SUPPORT              ((_D1_USB_HUB_TYPE == _USB_HUB_USER) && (_D1_BILLBOARD_HUB_SUPPORT == _ON))
#define _D2_BILLBOARD_USER_HUB_SUPPORT              ((_D2_USB_HUB_TYPE == _USB_HUB_USER) && (_D2_BILLBOARD_HUB_SUPPORT == _ON))
#define _P0_BILLBOARD_USER_HUB_SUPPORT              ((_P0_USB_HUB_TYPE == _USB_HUB_USER) && (_P0_BILLBOARD_HUB_SUPPORT == _ON))
#define _P1_BILLBOARD_USER_HUB_SUPPORT              ((_P1_USB_HUB_TYPE == _USB_HUB_USER) && (_P1_BILLBOARD_HUB_SUPPORT == _ON))
#define _P2_BILLBOARD_USER_HUB_SUPPORT              ((_P2_USB_HUB_TYPE == _USB_HUB_USER) && (_P2_BILLBOARD_HUB_SUPPORT == _ON))
#define _P3_BILLBOARD_USER_HUB_SUPPORT              ((_P3_USB_HUB_TYPE == _USB_HUB_USER) && (_P3_BILLBOARD_HUB_SUPPORT == _ON))
#define _P4_BILLBOARD_USER_HUB_SUPPORT              ((_P4_USB_HUB_TYPE == _USB_HUB_USER) && (_P4_BILLBOARD_HUB_SUPPORT == _ON))

#define _BILLBOARD_USER_HUB_SUPPORT                 ((_D0_BILLBOARD_USER_HUB_SUPPORT == _ON) ||\
                                                     (_D1_BILLBOARD_USER_HUB_SUPPORT == _ON) ||\
                                                     (_D2_BILLBOARD_USER_HUB_SUPPORT == _ON) ||\
                                                     (_P0_BILLBOARD_USER_HUB_SUPPORT == _ON) ||\
                                                     (_P1_BILLBOARD_USER_HUB_SUPPORT == _ON) ||\
                                                     (_P2_BILLBOARD_USER_HUB_SUPPORT == _ON) ||\
                                                     (_P3_BILLBOARD_USER_HUB_SUPPORT == _ON) ||\
                                                     (_P4_BILLBOARD_USER_HUB_SUPPORT == _ON))

#define _BILLBOARD_SUPPORT                          ((_BILLBOARD_SCALER_SUPPORT == _ON) || (_BILLBOARD_HUB_SUPPORT == _ON) || (_BILLBOARD_EXT_PORT_CTRL_SUPPORT == _ON))

#define _D0_TYPE_C_BILLBOARD_SUPPORT                (((_D0_BILLBOARD_HUB_SUPPORT == _ON) || (_D0_BILLBOARD_SCALER_SUPPORT == _ON)) && (_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _D1_TYPE_C_BILLBOARD_SUPPORT                (((_D1_BILLBOARD_HUB_SUPPORT == _ON) || (_D1_BILLBOARD_SCALER_SUPPORT == _ON)) && (_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _D2_TYPE_C_BILLBOARD_SUPPORT                (((_D2_BILLBOARD_HUB_SUPPORT == _ON) || (_D2_BILLBOARD_SCALER_SUPPORT == _ON)) && (_D2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P0_TYPE_C_BILLBOARD_SUPPORT                (((_P0_BILLBOARD_HUB_SUPPORT == _ON) || (_P0_BILLBOARD_SCALER_SUPPORT == _ON)) && (_P0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P1_TYPE_C_BILLBOARD_SUPPORT                (((_P1_BILLBOARD_HUB_SUPPORT == _ON) || (_P1_BILLBOARD_SCALER_SUPPORT == _ON)) && (_P1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P2_TYPE_C_BILLBOARD_SUPPORT                (((_P2_BILLBOARD_HUB_SUPPORT == _ON) || (_P2_BILLBOARD_SCALER_SUPPORT == _ON)) && (_P2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P3_TYPE_C_BILLBOARD_SUPPORT                (((_P3_BILLBOARD_HUB_SUPPORT == _ON) || (_P3_BILLBOARD_SCALER_SUPPORT == _ON)) && (_P3_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))
#define _P4_TYPE_C_BILLBOARD_SUPPORT                (((_P4_BILLBOARD_HUB_SUPPORT == _ON) || (_P4_BILLBOARD_SCALER_SUPPORT == _ON)) && (_P4_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE))

//--------------------------------------------------
// Macro of Two Chip Support
//--------------------------------------------------
#define _TWO_CHIP_DATA_EXCHANGE_SUPPORT             (_TWO_CHIP_DATA_EXCHANGE_TX_IIC_PIN != _NO_IIC_PIN)

//--------------------------------------------------
// Macro of DDR Poewr Release Time Control
//--------------------------------------------------
#define PCB_DDR_POWER_RELEASE_TIME(x)               {\
                                                        ScalerTimerDelayXms(x);\
                                                    }

//--------------------------------------------------
// Reserved for pin define
//--------------------------------------------------
#define GET_GPIO_PIN_EMPTY()                        (_FALSE)
#define SET_GPIO_PIN_EMPTY(x)                       {}
#define GET_SARADC_EMPTY_VALUE()                    (0)

//--------------------------------------------------
// PWM Reset by TCON or DVS SEL
//--------------------------------------------------
#define _DVS                                        0
#define _TCON                                       1

#endif // End of #ifndef __PCB_OPTION_H__
