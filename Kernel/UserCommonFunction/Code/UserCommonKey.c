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
// ID Code      : UserCommonKey.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_KEY__

#include "UserCommonInclude.h"
#include "Key/UserCommonKey.h"

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
// Description  : User Key Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonKeyHandler(void)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    if(UserCommonQCGetEnableStatus() == _TRUE)
    {
        // Skip key flow in QC
        return;
    }
#endif

    UserInterfaceKeyHandler();
}
