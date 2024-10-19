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
// ID Code      : ScalerTconAdvanceInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _TCON4_ALT_WITH_TCON3 = _TCON4,
    _TCON5_ALT_WITH_TCON4 = _TCON5,
    _TCON6_ALT_WITH_TCON5 = _TCON6,
    _TCON7_ALT_WITH_TCON6 = _TCON7,
    _TCON10_ALT_WITH_TCON9 = _TCON10,
    _TCON11_ALT_WITH_TCON10 = _TCON11,
    _TCON12_ALT_WITH_TCON11 = _TCON12,
    _TCON13_ALT_WITH_TCON12 = _TCON13,
} EnumTconAlternateSet;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTconAdvanceAlternateEnable(EnumTconAlternateSet enumTconAltSet, bit bEnable);

