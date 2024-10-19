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
// ID Code      : RTD2020OsdGosd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDGOSD__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

#if(_GOSD_SUPPORT == _ON)


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************

DWORD code tGOSD_DISP_SHARPNESS_PARAM_0[] =
{
#include "../Header/RTD2020GosdSharpnessTable_0.h"
};

DWORD code tGOSD_DISP_SHARPNESS_PARAM_1[] =
{
#include "../Header/RTD2020GosdSharpnessTable_1.h"
};


DWORD *code tGOSD_DISP_SHARPNESS_TABLE[] =
{
    tGOSD_DISP_SHARPNESS_PARAM_0, // off
    tGOSD_DISP_SHARPNESS_PARAM_1 // max
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
extern void GosdFuncDisplaySharpnessSetting(EnumGosdDisplayOSD enumOsd, BYTE ucEnhanceLevel, EnumDBApply enumDBApply);

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Gosd sharpness table
// Input Value  : ucLevel : enhance level: 0=off
// Output Value : DWORD table
//--------------------------------------------------
DWORD *GosdFuncGetDisplaySharpnessTable(BYTE ucLevel)
{
    return tGOSD_DISP_SHARPNESS_TABLE[ucLevel];
}

//--------------------------------------------------
// Description  : Set Gosd sharpness params, sharpness only enable at Gosd display ScaleUp
// Input Value  : enumOsd : Osd plane
//                ucEnhanceLevel : enhance level: 0=off
// Output Value : None
//--------------------------------------------------
void GosdFuncDisplaySharpnessSetting(EnumGosdDisplayOSD enumOsd, BYTE ucEnhanceLevel, EnumDBApply enumDBApply)
{
    DWORD *pulSharpnessTable = GosdFuncGetDisplaySharpnessTable(ucEnhanceLevel);
    UserCommonGosdDisplayOsdSharpnessSetting(enumOsd, pulSharpnessTable, enumDBApply);
}

#endif // #if(_GOSD_SUPPPRT == _ON)
#endif// #if(_OSD_TYPE == _REALTEK_2020_OSD)
