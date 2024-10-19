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
// ID Code      : ScalerBusSb2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_BUS_SB_2_H__
#define __SCALER_BUS_SB_2_H__


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
#if(_SCPU_SUPPORT == _ON)
// Page A2001A
// RBUS Blocking
extern void ScalerBusSb2RbusWrtProtectSectionEnable(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx);
extern void ScalerBusSb2RbusWrtProtectSectionDisable(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx);
extern void ScalerBusSb2RbusWrtProtectSectionSetRange(EnumCpuRbusWrtProtectSectionIdx enumSectionIdx, DWORD ulProtAddrStart, DWORD ulProtAddrEnd);
#endif

#endif // End of #ifndef __SCALER_BUS_SB_2_H__
