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
// ID Code      : ScalerUsb3RetimerMac1.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB3_RETIMER_MAC_1_H__
#define __SCALER_USB3_RETIMER_MAC_1_H__

#if(_USB3_RETIMER_MAC1_SUPPORT == _ON)
//****************************************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************************************

//****************************************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************************************


//****************************************************************************************************
// VARIABLE EXTERN
//****************************************************************************************************


//****************************************************************************************************
// FUNCTION EXTERN
//****************************************************************************************************
extern void ScalerUsb3RetimerMac1UfpMacInitial(void);
extern void ScalerUsb3RetimerMac1DfpMacInitial(void);
extern void ScalerUsb3RetimerMac1MacEnable(bit bEnable);
extern void ScalerUsb3RetimerMac1IrqEnable(bit bEnable);
#endif // End of #if(_USB3_RETIMER_MAC1_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_USB3_RETIMER_MAC_1_H__
