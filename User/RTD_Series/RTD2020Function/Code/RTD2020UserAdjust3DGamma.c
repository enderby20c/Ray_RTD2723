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
// ID Code      : RTD2020UserAdjust3DGamma.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_3D_GAMMA__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)
#if(_RGB_3D_GAMMA_FUNCTION == _ON)
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
// Description  : Get PCM USer Mode Table Address
// Input Value  : None
// Output Value : PCM User Modee table address
//--------------------------------------------------
BYTE *UserAdjustGet3DGammaTableAddress(void)
{
    return tRGB3DGAMMA_TABLE[0];
}

//--------------------------------------------------
// Description  : Get 3D Gamma User Mode Table Bank
// Input Value  : None
// Output Value : 3D Gamma User Mode table bank
//--------------------------------------------------
BYTE UserAdjustGet3DGammaTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function to Set Type of Output Gamma and 3D Gamma
// Input Value  : Select Region
// Output Value : enum type of 3D Gamma (and Output Gamma)
//--------------------------------------------------
Enum3DGammaTypeSelect UserAdjustGet3DGammaType(EnumSelRegion enumSelRegion)
{
    Enum3DGammaTypeSelect enum3DGammaTypeSelect = _OCC_RGB_3D_GAMMA_TYPE1;
#if(_OCC_FUNCTION == _ON)
    BYTE ucOSDSelectRegion = UserAdjustGetOSDSelectRegion(enumSelRegion);
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) != _PCM_OSD_NATIVE)
    {
        switch(GET_OSD_PCM_STATUS(ucOSDSelectRegion))
        {
            case _PCM_OSD_SRGB:
                enum3DGammaTypeSelect = _OCC_RGB_3D_GAMMA_TYPE1;
                break;
            case _PCM_OSD_ADOBE_RGB:
                enum3DGammaTypeSelect = _OCC_RGB_3D_GAMMA_TYPE2;
                break;
            default:
                break;
        }
    }
#endif
    return enum3DGammaTypeSelect;
}
#endif

#endif // End of #if(_RGB_3D_GAMMA == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
