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
// ID Code      : UserCommonFwUpdateCodeTable.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_FW_UPDATE__

#include "UserCommonInclude.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
__attribute__((section(".used_table.tFwCrc")))
BYTE code tFwCrc[] =
{
    0xFF, 0xFF, 0xFF, 0xFF,
};
#endif

#if((_FW_UPDATE_PROCESS_SUPPORT == _ON) && ((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072)))
__attribute__((section(".used_table.tFW_UPDATE_SIGNATURE_TABLE")))
BYTE code tFW_UPDATE_SIGNATURE_TABLE[4 * 1024] =
{
    [0 ... 4 * 1024 - 1] = 0xFF
};

#endif  // End of #if((_FW_UPDATE_FOREGROUND_SUPPORT == _ON) || (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON))

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************


