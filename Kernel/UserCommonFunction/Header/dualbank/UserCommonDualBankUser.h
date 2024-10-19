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
// ID Code      : UserCommonDualBankUser.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_DUAL_BANK_USER_H__
#define __USER_COMMON_DUAL_BANK_USER_H__

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DUAL_BANK_OUT_DATA_MAX_LEN        16

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)
extern void UserCommonDualBankUserGetBundleVersion(BYTE *pucArry);
extern EnumISPBundleVerResult UserCommonDualBankUserUpdateBundleVersion(void);
#endif

#endif


#endif // End of #ifndef __USER_COMMON_DUAL_BANK_USER_H__
