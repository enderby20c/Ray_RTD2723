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
// ID Code      : ScalerUsb3RedriverMac0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB3_REDRIVER_MAC_0_H__
#define __SCALER_USB3_REDRIVER_MAC_0_H__

#if(_USB3_REDRIVER_MAC0_SUPPORT == _ON)
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
extern void ScalerUsb3RedriverMac0UfpInitial(void);
extern void ScalerUsb3RedriverMac0DfpInitial(void);
extern void ScalerUsb3RedriverMac0MacEnable(bit bEnable);
extern void ScalerUsb3RedriverMac0IrqEnable(bit bEnable);
#endif // End of #if(_USB3_REDRIVER_MAC0_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_USB3_REDRIVER_MAC_0_H__
