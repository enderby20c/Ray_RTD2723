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
// ID Code      : RTD2020ResourceInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GOSD_SUPPORT == _ON)
#include <RTD2020GosdImageSource.h>
#include <RTD2020GosdSurfaceList.h>
#endif

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
#if(_GOSD_SUPPORT == _ON)
    _USER_RESOURCE_ID_GOSD_IMAGE_SOURCE,
#endif
    _USER_RESOURCE_ID_NONE,
}
EnumUserResourceId;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif
