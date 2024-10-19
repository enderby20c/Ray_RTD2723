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
// ID Code      : ScalerColor3DGammaAdvancedHDR10.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
#if(_ADVANCED_HDR10_SUPPORT == _ON)
BYTE code tPCM_3DGAMMA_ADVANCED_HDR10[] =
{
#include <Color/3DGamma/3DGamma_AdvancdHDR10_Table.h>
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get 3D Gamma Advanced HDR10 Table Address
// Input Value  : None
// Output Value : table address
//--------------------------------------------------
BYTE *ScalerColorRGB3DGammaGetAdvancedHDR10TableAddress(void)
{
    return tPCM_3DGAMMA_ADVANCED_HDR10;
}

//--------------------------------------------------
// Description  : Get 3D Gamma Advanced HDR10 Table Bank
// Input Value  : None
// Output Value : table bank
//--------------------------------------------------
BYTE ScalerColorRGB3DGammaGetAdvancedHDR10TableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}
#endif
#endif
