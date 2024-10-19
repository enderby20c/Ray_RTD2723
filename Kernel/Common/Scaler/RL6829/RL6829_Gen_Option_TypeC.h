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
// ID Code      : RL6829_Gen_Option_TypeC.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// HW PD/CC Support Status
//--------------------------------------------------
#define _HW_EMB_TYPE_C_0_SUPPORT                                _ON
#define _HW_EMB_TYPE_C_1_SUPPORT                                _ON
#define _HW_EMB_TYPE_C_2_SUPPORT                                _OFF
#define _HW_EMB_TYPE_C_3_SUPPORT                                _OFF

//--------------------------------------------------
// HW TCPM Support Status
//--------------------------------------------------
#define _HW_TCPM_0_0_SUPPORT                                    _OFF
#define _HW_TCPM_0_1_SUPPORT                                    _OFF
#define _HW_TCPM_1_0_SUPPORT                                    _OFF
#define _HW_TCPM_1_1_SUPPORT                                    _OFF

//--------------------------------------------------
// HW TCPM Register Start Address
//--------------------------------------------------
#define _HW_TCPM_IIC_0_REG_ST_ADDR                              0x0000
#define _HW_TCPM_IIC_1_REG_ST_ADDR                              0x0000

#define _HW_TCPM_0_0_REG_ST_ADDR                                0x0000
#define _HW_TCPM_0_1_REG_ST_ADDR                                0x0000
#define _HW_TCPM_1_0_REG_ST_ADDR                                0x0000
#define _HW_TCPM_1_1_REG_ST_ADDR                                0x0000

//--------------------------------------------------
// _TYPE_C_SUPPORT_VERSION SELECT
//--------------------------------------------------
#define _HW_TYPE_C_SUPPORT_VERSION                              _TYPE_C_VERSION_2_0

//--------------------------------------------------
// _PD_SUPPORT_VERSION SELSCT
//--------------------------------------------------
#define _HW_PD_SUPPORT_VERSION                                  _PD_VERSION_3_0

//--------------------------------------------------
// _TYPE_C_FUNCTION_GEN SELSCT
//--------------------------------------------------
#define _HW_TYPE_C_FUNCTION_GEN                                 _TYPE_C_FUNCTION_GEN_4

//--------------------------------------------------
// _PD_FUNCTION_GEN SELECT
//--------------------------------------------------
#define _HW_PD_FUNCTION_GEN                                     _PD_FUNCTION_GEN_1

//--------------------------------------------------
// HW TYPE C 10-BIT SARADC GEN TYPE
//--------------------------------------------------
#define _HW_TYPE_C_10_BIT_SARADC_GEN_TYPE                       _TYPE_C_10_BIT_SARADC_GEN_0

//--------------------------------------------------
// _TYPE_C_LS_ADC_SUPPORT_VERSION SELECT
//--------------------------------------------------
#define _HW_TYPE_C_LS_ADC_HW_VERSION                            _TYPE_C_5B_LS_ADC_NONE

//--------------------------------------------------
// FW TYPE_C Accessory Support Type Selection
//--------------------------------------------------
#define _FW_TYPE_C_ACC_SUPPORT_TYPE                             _TYPE_C_ACC_NO_SUPPORT

//--------------------------------------------------
// HW TYPE C Power Domain Gen Type
//--------------------------------------------------
#define _HW_TYPE_C_POWER_DOMAIN_GEN_TYPE                        _TYPE_C_POWER_DOMAIN_GEN_1

