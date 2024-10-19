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
// ID Code      : UserCommonDrr.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DRR__

#include "UserCommonInclude.h"
#include "Drr/UserCommonDrr.h"

#if(_DRR_SUPPORT == _ON)

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
// Description  : Get Drr Type
// Input Value  : None
// Output Value : Drr type
//--------------------------------------------------
EnumDrrType UserCommonDrrGetType(void)
{
    EnumDisplayMode enumDisplayModeTrans = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayModeTrans = ScalerRegionEagleSightTransDisplayMode(enumDisplayModeTrans);
#endif

    if(enumDisplayModeTrans == _DISPLAY_MODE_1P)
    {
        return ScalerDrrGetType(SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0)));
    }

    return _DRR_NONE_TYPE;
}

#endif



