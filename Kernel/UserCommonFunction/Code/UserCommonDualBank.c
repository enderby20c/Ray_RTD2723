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
// ID Code      : UserCommonDualBank.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "UserCommonInclude.h"
#include "dualbank/UserCommonDualBankUser.h"

#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)
BYTE code tUSERFLAGTABLE[] =
{
    _DUAL_BANK_FLASH_PARTITION_USER_FLAG_DATA
};

code StructDualBankUserFlagInfo g_stDualBankUserFlagInfo =
{
    sizeof(tUSERFLAGTABLE),
    _DUAL_BANK_FLASH_PARTITION_USER_FLAG_ADDRESS,
    tUSERFLAGTABLE,
};
#endif

code StructUserDataFlagInfo g_stDualBankBootUserIFlag =
{
    _DUAL_BANK_USER_I_USER_DATA_BANK_ADDR,
    _DUAL_BANK_USER_I_FLAG_START_ADDR,
    _DUAL_BANK_USER_FLAG_LENGTH,

    _DUAL_BANK_USER_I_FW_BANK_START,
    _DUAL_BANK_USER_I_FW_BANK_END,

    _DUAL_BANK_USER_I_DATA_SECTOR_START,
    _DUAL_BANK_USER_I_DATA_SECTOR_END,

    _DUAL_BANK_USER_I_KEY_START_ADDR,
    _DUAL_BANK_USER_I_SIGNATURE_START_ADDR,
};

code StructUserDataFlagInfo g_stDualBankBootUserIIFlag =
{
    _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR,
    _DUAL_BANK_USER_II_FLAG_START_ADDR,
    _DUAL_BANK_USER_FLAG_LENGTH,

    _DUAL_BANK_USER_II_FW_BANK_START,
    _DUAL_BANK_USER_II_FW_BANK_END,

    _DUAL_BANK_USER_II_DATA_SECTOR_START,
    _DUAL_BANK_USER_II_DATA_SECTOR_END,

    _DUAL_BANK_USER_II_KEY_START_ADDR,
    _DUAL_BANK_USER_II_SIGNATURE_START_ADDR,
};

code StructDualBankProjectInfo g_stDualBankProjectInfo =
{
    _DIGITAL_SIGNATURE_TYPE,
    _DUAL_BANK_TYPE,
    _DUAL_BANK_FLASH_PARTITION_SUPPORT,
    _DUAL_BANK_ROLLBACK_SUPPORT,
    _NULL_POINTER,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Handle dual bank process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDualBankBootHandler(void)
{
#if(_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)
    UserCommonDualBankUserFlagBootHandler();
#else
    UserCommonDualBankNormalBootHandler();
#endif
}

//--------------------------------------------------
// Description  : digital signature verify
// Input Value  : None
// Output Value : _TRUE
//--------------------------------------------------
EnumDualBankVerifyResult UserCommonDualBankDigitalSignatureVerify(void)
{
#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
    return UserCommonDigitalSignatureHwVerify();
#else
    DebugMessageSignature("sw/none signature", 0);
    return _VERIFY_RESULT_PASS;
#endif
}

#if(_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION)
//--------------------------------------------------
// Description  : Copy Bank Flash Clone Process
// Input Value  : enumSrcRegion
//                enumDstRegion
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDualBankCopyResult UserCommonDualBankProcessCopy(EnumDualBankCodeRegion enumSrcRegion, EnumDualBankCodeRegion enumDstRegion)
{
    return UserCommonDualBankProcessFlashPartitionCopy(enumSrcRegion, enumDstRegion);
}
#endif

#endif
