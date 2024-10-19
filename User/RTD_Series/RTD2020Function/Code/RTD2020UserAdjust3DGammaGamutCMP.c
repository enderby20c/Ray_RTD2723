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
// ID Code      : RTD2020UserAdjust3DGammaGamutCMP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_3D_GAMMA_GAMUTCMP__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)
#if((_RGB_3D_GAMMA_FUNCTION == _ON) && (_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get 3D Gamma HDR10 Gamut compression Table Address
// Input Value  : None
// Output Value : 3D Gamma HDR10 Gamut compression table address
//--------------------------------------------------
BYTE *UserAdjustGet3DGammaGamutCMPTableAddress(void)
{
    return tRGB3DGAMMA_GAMUTCMP_TABLE[0];
}

//--------------------------------------------------
// Description  : Get 3D Gamma HDR10 Gamut compression Table Bank
// Input Value  : None
// Output Value : 3D Gamma HDR10 Gamut compression table bank
//--------------------------------------------------
BYTE UserAdjustGet3DGammaGamutCMPTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

#endif // End of #if(_RGB_3D_GAMMA == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
