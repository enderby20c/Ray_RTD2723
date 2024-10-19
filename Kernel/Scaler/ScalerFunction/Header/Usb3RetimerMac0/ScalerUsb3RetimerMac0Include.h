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
// ID Code      : ScalerUsb3RetimerMac0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsb3RetimerMac0Initial(EnumTypeCOrientation enumOrientation);
extern void ScalerUsb3RetimerMac0Enable(bit bEnable);
#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
extern void ScalerUsb3RetimerMac0DfpU1U2U3JfmEnableTimeOut_WDINT(void);
#endif // end if #if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
#endif // end if #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
extern void ScalerUsb3RetimerMac0ClearLowPowerStateStatus(void);
extern EnumUsb3RetimerP3State ScalerUsb3RetimerMac0GetLowPowerStateStatus(void);
extern void ScalerUsb3RetimerMac0SetAtLowPowerStateStatus(void);
extern bit ScalerUsb3RetimerMac0GetDetectNSQFlag(void);
extern void ScalerUsb3RetimerMac0DisableU3IRQ(void);
extern void ScalerUsb3RetimerMac0U3DFPRxDetectTimeOut_WDINT(void);
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#endif // End of #if(_USB3_RETIMER_MAC0_SUPPORT == _ON)

