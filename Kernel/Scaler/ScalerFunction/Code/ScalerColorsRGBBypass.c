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
// ID Code      : ScalerColorsRGBBypass.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_PCM_FUNCTION == _ON)
BYTE code tSRGB_BYPASS[] =
{
    0,0,0,0,0,0,
    0,0,0,0,0,0,
    0,0,0,0,0,0
};

BYTE code tSRGB_HALF[] =
{
    0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
};

BYTE * code tSRGB_BYPASS_LUT[] =
{
    tSRGB_BYPASS,
    tSRGB_HALF,
};
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get sRGB Bypass Table
// Input Value  : EnumSrgbBypassLut
// Output Value : sRGB table address
//--------------------------------------------------
BYTE *ScalerColorsRGBBypassGetTableAddress(EnumSrgbBypassLut enumSrgbBypassLut)
{
    return tSRGB_BYPASS_LUT[enumSrgbBypassLut];
}

//--------------------------------------------------
// Description  : Get sRGB Bypass Table Bank
// Input Value  : None
// Output Value : sRGB table bank
//--------------------------------------------------
BYTE ScalerColorsRGBBypassGetTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}
#endif
