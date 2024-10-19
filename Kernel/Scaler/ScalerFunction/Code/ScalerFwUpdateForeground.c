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
// ID Code      : ScalerFwUpdateForeground.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_FOREGROUND_FW_UPDATE__

#include "ScalerFunctionInclude.h"
#include "FwUpdateForeground/ScalerFwUpdateForeground.h"

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
bit ScalerFwUpdateForegroundGetStatus(void)
{
    if((GET_FW_UPDATE_STATUS() == _TRUE) && (GET_FW_UPDATE_MODE() == _FOREGROUND_MODE))
    {
        return _TRUE;
    }
    return _FALSE;
}


#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)
//--------------------------------------------------
// Description  : Reset Foreground Fw Update
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateForegroundReset(void)
{
    // Reset MCU
    MCU_FFEE_MCU_CLOCK_CONTROL |= _BIT1;
}
#endif

#endif
