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
// ID Code      : RL6952_Gen_Option_USB.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// _HW_USB_SUPPORT_ROLE SELSCT
//--------------------------------------------------
#define _HW_USB_SUPPORT_ROLE                                    _TYPE_C_USB_DEVICE_ONLY // Confirm

//--------------------------------------------------
// _HW_USB_SUPPORT_CAPABILITY SELSCT
//--------------------------------------------------
#define _HW_USB_MAX_LINK_RATE_SUPPORT                           _USB_SPEED_10G // Confirm
#define _HW_USB_MAX_LINK_LANE_SUPPORT                           _USB_LANE_X1

//--------------------------------------------------
// USB3 Repeater TYPE
//--------------------------------------------------
#define _HW_MAC0_USB3_REPEATER_TYPE                             _USB3_RETIMER
#define _HW_MAC1_USB3_REPEATER_TYPE                             _USB3_REPEATER_NONE
#define _HW_MAC2_USB3_REPEATER_TYPE                             _USB3_REPEATER_NONE // Confirm

//--------------------------------------------------
// HW USB3 Repeater Mac Mux Support
//--------------------------------------------------
#define _HW_USB3_REPEATER_MAC_MUX_TYPE                          _ON

//--------------------------------------------------
// HW USB2 Mux Support
//--------------------------------------------------
#define _HW_USB2_EMB_MUX_SUPPORT                                _ON

//--------------------------------------------------
// HW USB2 Host SRAM Size Support
//--------------------------------------------------
#define _HW_USB2_HOST_SRAM_SIZE_SUPPORT                         _HW_USB2_HOST_SRAM_SIZE_3K

//--------------------------------------------------
// HW USB2 Host/BB Shared Phy Support
//--------------------------------------------------
#define _HW_USB2_SHARED_PHY_SUPPORT                             _OFF

//--------------------------------------------------
// HW USB2 Analog Core Power Type
//--------------------------------------------------
#define _HW_USB2_ANALOG_CORE_POWER_TYPE                         _USB2_CORE_POWER_FROM_PIN

//--------------------------------------------------
// USB3 Repeater MAC Mapping Select
//--------------------------------------------------
#define _HW_USB3_REPEATER_UFP_PHY0_TO_MAC_MAPPING               _USB3_REPEATER_MAC_0
#define _HW_USB3_REPEATER_UFP_PHY1_TO_MAC_MAPPING               _USB3_REPEATER_MAC_0
#define _HW_USB3_REPEATER_UFP_PHY2_TO_MAC_MAPPING               _USB3_REPEATER_MAC_NONE // Confirm

//--------------------------------------------------
// HW USB3 Repeater Mac Gen1x1 Parallel Data Path Support
//--------------------------------------------------
#define _HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT        _OFF

//--------------------------------------------------
// HW USB3 Repeater Mac Power Saving Support
//--------------------------------------------------
#define _HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT              _ON

//--------------------------------------------------------
// HW USB3 Repeater Mac Power Saving Support Level
//--------------------------------------------------------
#define _HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL        _USB3_PS_SUPPORT_LEVEL_2

//--------------------------------------------------
// HW USB3 Repeater UFP AD Interface Bit Width
//--------------------------------------------------
#define _HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH            _UFP_32_BIT

//--------------------------------------------------
// HW USB3 Repeater UFP P3 DPHY Power Cut Support
//--------------------------------------------------
#define _HW_USB3_REPEATER_UFP_P3_DPHY_PWRCUT_SUPPORT            _OFF

//--------------------------------------------------
// HW USB3 Repeater UFP0 APHY Power Cut GROUP
//--------------------------------------------------
#define _HW_USB3_REPEATER_UFP0_APHY_POWER_CUT_GROUP             _POWER_CUT_GROUP_RX0_DP20_U32_APHY

//--------------------------------------------------
// HW USB3 Repeater UFP JFM Clock Select
//--------------------------------------------------
#define _HW_USB3_REPEATER_UFP_JFM_CLK_SEL                       _DFP_RX_CMU

//--------------------------------------------------
// HW USB3 Repeater DFP Phy Lane Number Support
//--------------------------------------------------
#define _HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT              _DFP_TWO_LANE
