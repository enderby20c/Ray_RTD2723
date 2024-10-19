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
// ID Code      : ScalerGosdSeInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_GOSD_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//***************************************************************
// Function
//***************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_NONE = 0,
    _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_X = 1,
    _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_Y = 2,
    _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_XY = 3,
} EnumGosdSeLinearGradientMode;

typedef enum
{
    _GOSD_SEINFO_MIRROR_NONE = 0,
    _GOSD_SEINFO_MIRROR_X = 1,
    _GOSD_SEINFO_MIRROR_Y = 2,
    _GOSD_SEINFO_MIRROR_XY = 3
} EnumGosdSeMirrorMode;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif
