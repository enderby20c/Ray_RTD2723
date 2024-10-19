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
// ID Code      : UserCommonColorSeamlessChg.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_COLOR_SEAMLESS_CHG_H__
#define __USER_COMMON_COLOR_SEAMLESS_CHG_H__


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
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
extern EnumColorimetryChangeStatus UserCommonColorSeamlessChgGetChangeStatus(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern EnumColorFormatChangeStatus UserCommonColorDMFormatChgWoResetGetChangeStatus(EnumDisplayRegion enumDisplayRegion);
#endif

#endif // End of #ifndef __USER_COMMON_COLOR_SEAMLESS_CHG_H__
