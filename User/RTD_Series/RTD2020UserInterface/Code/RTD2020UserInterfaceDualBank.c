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
// ID Code      : RTD2020UserInterfaceDualBank.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_DUALBANK__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceDualBank.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)
#if(_DUAL_BANK_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

#if(_DUAL_BANK_USER_FLAG_CUSTOMER_TYPE == _DUAL_BANK_USER_TYPE)
//--------------------------------------------------
// Description  : Fw Update Write Done Flag
// Input Value  : usFlagBankIndex, Flag Bank Index
//                  usFlagAddr,FLag Adddress
// Output Value : _WRITE_FAIL/WRITE_PASS
//--------------------------------------------------
EnumFwUpdateWriteFlagResult UserInterfaceDualBankFwUpdateWriteDoneFlag(WORD usFlagBank, WORD usFlagAddr)
{
    usFlagBank = usFlagBank;
    usFlagAddr = usFlagAddr;
    return _FWUPDATE_WRITE_FLAG_FAIL;
}
#endif
#endif

#endif // End of #if(_DUAL_BANK_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
