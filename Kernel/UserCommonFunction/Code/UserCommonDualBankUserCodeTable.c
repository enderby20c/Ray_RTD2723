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
// ID Code      : UserCommonDualBankUserCodeTable.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "UserCommonInclude.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if((_DUAL_BANK_FP_USER_FLAG_TABLE_SUPPORT == _ON) && (_DUAL_BANK_USER_I_TABLE_SUPPORT == _ON))
__attribute__((section(".used_table.tDUALBANKUSERFLAGTABLE")))
BYTE code tDUALBANKUSERFLAGTABLE[] =
{
    _DUAL_BANK_FLASH_PARTITION_DEFAULT_CODE_TABLE
};
#endif

#if(_DUAL_BANK_USER_DATA_TABLE_SUPPORT == _ON)
#if(_DUAL_BANK_USER_I_TABLE_SUPPORT == _ON)
__attribute__((section(".used_table.tDUALBANK_FILLHEX")))
BYTE code tDUALBANK_FILLHEX[_DUALBANK_FILL_LENGTH * 1024] =
{
    [0 ... _DUALBANK_FILL_LENGTH * 1024 - 1] = 0xFF
};
#endif
#if((_DUAL_BANK_USER_I_FLAG_LOCATE_BANK != _DUAL_BANK_USER_II_FLAG_LOCATE_BANK) && (_DUAL_BANK_USER_II_TABLE_SUPPORT == _ON))
__attribute__((section(".used_table.tDUALBANK_FILLHEXII")))
BYTE code tDUALBANK_FILLHEXII[_DUALBANK_FILL_LENGTH * 1024] =
{
    [0 ... _DUALBANK_FILL_LENGTH * 1024 - 1] = 0xFF
};
#endif

#endif // End of #if(_DUAL_BANK_USER_DATA_TABLE_SUPPORT == _ON)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

