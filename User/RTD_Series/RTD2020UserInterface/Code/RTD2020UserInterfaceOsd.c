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
// ID Code      : RTD2020UserInterfaceOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_OSD__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceOsd.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

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
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceOsdHandler(void)
{
    RTDOsdSystemFlowProc();
    RTDOsdEventMsgProc();
}

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : OSD Setting For Eagle Sight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceOsdForEagleSightModify(EnumDBApply enumDBApply)
{
    enumDBApply = enumDBApply;
}
#endif // End of #if(_EAGLE_SIGHT_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

