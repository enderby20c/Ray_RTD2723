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
// ID Code      : ScalerDualBank.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DUALBANK__

#include "ScalerFunctionInclude.h"
#include "DualBank/ScalerDualBank.h"

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON)
code StructDigitalSignatureRsaKeyInfo g_stDualBankDigitalSignatureRsaKeyInfo =
{
    _DIGITAL_SIGNATURE_HW_RSA_TYPE,
    _DUAL_BANK_USER_SIGNATURE_LENGTH,

    _RSA_RESULT_SIZE,

    _DIGITAL_SIGNATURE_RSA_KEY_NKEY_OFFSET,
    _DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE,

    _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_OFFSET,
    _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE,

    _DIGITAL_SIGNATURE_RSA_KEY_NPINV_OFFSET,
    _DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE,

    _DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_OFFSET,
    _DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_SIZE,
};
#endif
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************


//--------------------------------------------------
// Description  : Get KCPU Flash Bank Offset
// Input Value  : None
// Output Value : BankIndex
//--------------------------------------------------
WORD ScalerDualBankUserGetKCPUBankOffset(void)
{
    return (WORD)(GET_KCPU_FLASH_BANK_OFFSET() >> 16);
}

#endif // End of #if(_DUAL_BANK_SUPPORT == _ON)
