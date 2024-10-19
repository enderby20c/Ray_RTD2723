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
// ID Code      : UserCommonDualBankUserInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)

//------------------------------------------------------
// Flag setting
//------------------------------------------------------
#define _USER_FLAG_ISP_TAG                                          0
#define _USER_FLAG_VERIFY_TAG                                       1
#define _USER_FLAG_SWITCH_TAG                                       2
#define _USER_FLAG_RUN_TAG                                          3
#define _USER_FLAG_COPY_TAG                                         4

//------------------------------------------------------
// ISP Tag
//------------------------------------------------------
#define _TAG_UPDATE_FW_PASS                                         0xAA
#define _TAG_UPDATE_FW_FAIL                                         0xFF


//------------------------------------------------------
// Verify Tag
//------------------------------------------------------
#define _TAG_VERIFY_FW_PASS                                         0xAA
#define _TAG_VERIFY_FW_FAIL                                         0x55
#define _TAG_VERIFY_FW_NONE                                         0xFF


//------------------------------------------------------
// Switch Tag
//------------------------------------------------------
#define _TAG_SWITCH_CODE_NONE                                       0xFF
#define _TAG_SWITCH_CODE_INCOMPLETE                                 0xAF
#define _TAG_SWITCH_CODE_COMPLETE                                   0xAA


//------------------------------------------------------
// Run Tag
//------------------------------------------------------
#define _TAG_CAN_BE_EXECUTED                                        0xFF
#define _TAG_CAN_NOT_BE_EXECUTED                                    0x55


//------------------------------------------------------
// Copy Tag
//------------------------------------------------------
#define _TAG_COPY_FW_PASS                                           0xAA
#define _TAG_COPY_FW_NONE                                           0xFF

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DUAL_BANK_STATE_NONE = 0,
    _DUAL_BANK_STATE_RUN,
    _DUAL_BANK_STATE_VERIFY,
    _DUAL_BANK_STATE_WAIT_SWITCH,
    _DUAL_BANK_STATE_SWITCH,
    _DUAL_BANK_STATE_COPY,
}EnumDualBankState;


typedef enum
{
    _USER_ILLEGAL = 0,
    _USER_VALID,
    _USER_INVALID,
    _USER_VERIFY,
    _USER_WAIT_SWITCH,
    _USER_SWITCH,
    _USER_COPY,
}EnumDualBankUserStatus;

typedef enum
{
    _VERIFY_RESULT_PASS = 0,
    _VERIFY_RESULT_FAIL,
}EnumDualBankVerifyResult;

typedef enum
{
    _COPY_RESULT_PASS = 0,
    _COPY_RESULT_FAIL,
}EnumDualBankCopyResult;

typedef enum
{
    _REGION_NONE = 0,
    _REGION_BOOT,
    _REGION_USER_I,
    _REGION_USER_II,
}EnumDualBankCodeRegion;

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonDualBankUserHandler(void);
extern void UserCommonDualBankUserGetFwInfo(BYTE *pucArry);
#endif

