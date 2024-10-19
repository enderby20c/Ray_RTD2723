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
// ID Code      : ScalerUsb3RetimerMac0Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _USB32_TX_COMPLIANCE_MODE_FW_MODE           _ON

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#define _USB32_GEN1_BLR_PATH_SUPPORT                _ON
#define _USB32_GEN1_BLR_FW_SOLUTION_SUPPORT         _OFF
#define _USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT  _ON
#else
#define _USB32_GEN1_BLR_PATH_SUPPORT                _OFF
#define _USB32_GEN1_BLR_FW_SOLUTION_SUPPORT         _OFF
#define _USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT  _OFF
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#define _USB32_RL6952_FW_SOLUTION_SUPPORT           _OFF

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_TYPE_C_EMB_CTS_FLOW == _ON))
#define _USB32_GEN2_P3_CV_FW_SOLUTION_SUPPORT       _ON
#else
#define _USB32_GEN2_P3_CV_FW_SOLUTION_SUPPORT       _OFF
#endif // End of #if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_TYPE_C_EMB_CTS_FLOW == _ON))
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsb3RetimerMac0IntHandler_EXINT3(EnumPowerStatus enumPowerStatus);
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
extern void ScalerUsb3RetimerMac0PowerCutOnSleep(void);
extern void ScalerUsb3RetimerMac0PowerCutOffAwake(void);
#endif
#endif // End of #if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
