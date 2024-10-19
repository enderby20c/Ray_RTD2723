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
// ID Code      : ScalerGlobalCtrl.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_GLOBAL_CTRL_H__
#define __SCALER_GLOBAL_CTRL_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _HW_CPU32_CLK_SRC_INVALID                               9999999UL  // 9999MHz


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern void ScalerGlobalCtrlSetKcpuClkSrc(EnumClkSel enumClkSel);
#endif

#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
extern void ScalerGlobalCtrlSetScpuClkSrc(EnumClkSel enumClkSel);
#endif

#endif // End of #ifndef __SCALER_GLOBAL_CTRL_H__
