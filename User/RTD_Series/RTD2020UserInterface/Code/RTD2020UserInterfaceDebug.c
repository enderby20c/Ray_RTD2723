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
// ID Code      : RTD2020UserInterfaceDebug.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_DEBUG__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceDebug.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
//--------------------------------------------------
// Description  : User Debug Tool Page IIC
// Input Value  : Event ID
// Output Value : _DBG_OFF/_DBG_ON
//--------------------------------------------------
EnumDebugMode UserInterfaceDebugIIC(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue)
{
    EnumDebugMode enumDebugMode = _DBG_OFF;

    ucType = ucType;
    pucDdcciArray = pucDdcciArray;
    pucReturnValue = pucReturnValue;

    return enumDebugMode;
}
#endif // End of #if(_DEBUG_IIC_BY_USERINTERFACE == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
