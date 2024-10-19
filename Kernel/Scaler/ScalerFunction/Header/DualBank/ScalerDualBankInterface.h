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
// ID Code      : ScalerDualBankInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _RSA_SIGNATURE_SIZE                                     (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)
#define _RSA_RESULT_SIZE                                        (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)

#define _DUAL_BANK_USER_SIGNATURE_LENGTH                        (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)

//------------------------------------------------------
// Key address setting
// Public Key Content Offset Address from @0x_000(Nkey + RRmodN + Npinv + EKey)
//------------------------------------------------------
#define _DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE                    (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)
#define _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE                  (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)
#define _DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE                   4
#define _DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_SIZE                 (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)

#define _DIGITAL_SIGNATURE_RSA_KEY_NKEY_OFFSET                  0
#define _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_OFFSET                (_DIGITAL_SIGNATURE_RSA_KEY_NKEY_OFFSET + _DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE)
#define _DIGITAL_SIGNATURE_RSA_KEY_NPINV_OFFSET                 (_DIGITAL_SIGNATURE_RSA_KEY_RRMODN_OFFSET + _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE)
#define _DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_OFFSET               (_DIGITAL_SIGNATURE_RSA_KEY_NPINV_OFFSET + _DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE)

#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON)
//------------------------------------------------------
// Signature address setting
//------------------------------------------------------
#define _SHA256_RESULT_SIZE                                     32
#define _SHA256_ARRAY_SIZE                                      64

//------------------------------------------------------
// Max Signature address setting
//------------------------------------------------------
#define _MAX_RSA_SIGNATURE_SIZE                                 (_FW_MAX_DIGITAL_SIGNATURE_RSA / 8)
#define _MAX_RSA_RESULT_SIZE                                    (_FW_MAX_DIGITAL_SIGNATURE_RSA / 8)
#define _MAX_DUAL_BANK_USER_SIGNATURE_LENGTH                    (_FW_MAX_DIGITAL_SIGNATURE_RSA / 8)
#define _MAX_DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE                (_FW_MAX_DIGITAL_SIGNATURE_RSA / 8)
#define _MAX_DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE              (_FW_MAX_DIGITAL_SIGNATURE_RSA / 8)
#define _MAX_DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE               4
#define _MAX_DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_SIZE             (_FW_MAX_DIGITAL_SIGNATURE_RSA / 8)

#define _MAX_DIGITAL_SIGNATURE_RSA_KEY_NKEY_OFFSET              0
#define _MAX_DIGITAL_SIGNATURE_RSA_KEY_RRMODN_OFFSET            (_MAX_DIGITAL_SIGNATURE_RSA_KEY_NKEY_OFFSET + _MAX_DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE)
#define _MAX_DIGITAL_SIGNATURE_RSA_KEY_NPINV_OFFSET             (_MAX_DIGITAL_SIGNATURE_RSA_KEY_RRMODN_OFFSET + _MAX_DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE)
#define _MAX_DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_OFFSET           (_MAX_DIGITAL_SIGNATURE_RSA_KEY_NPINV_OFFSET + _MAX_DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON)
typedef struct
{
    WORD usHwRsaType;
    WORD usSignatureLength;
    WORD usRsaResultSize;

    WORD usNkeyOffset;
    WORD usNkeySize;

    WORD usRrmodNOffset;
    WORD usRrmodNSize;

    WORD usNpinvOffset;
    WORD usNpinvSize;

    WORD usExorkeyOffset;
    WORD usExorkeySize;
} StructDigitalSignatureRsaKeyInfo;

typedef struct
{
    WORD usUserDataBank;
    BYTE ucUserDataSectorStart;
    BYTE ucUserDataSectorEnd;
}StructUserDataGlobalInfo;

typedef struct
{
    WORD usKeyBank;
    WORD usNKeyAddr;
    WORD usNKeyLength;
    WORD usRrmodnAddr;
    WORD usRrmodnLength;
    WORD usNpinvAddr;
    WORD usNpinvLength;
    WORD usEKeyAddr;
    WORD usEKeyLength;
}StructUserDataKeyInfo;

typedef struct
{
    WORD usSignatureBank;
    WORD usSignatureAddr;
    WORD usSignatureLength;
}StructUserDataSignatureInfo;

typedef struct
{
    WORD usFwBankStart;
    WORD usFwBankEnd;
}StructUserFwInfo;
typedef struct
{
    StructUserDataGlobalInfo stUserDataGlobalInfo;
    StructUserDataKeyInfo stKeyInfo;
    StructUserDataSignatureInfo stSignatureInfo;
    StructUserFwInfo stUserFwInfo;
}StructUserDigitalVerifyInfo;

typedef struct
{
    WORD usFlagBank;
    WORD usFlagAddr;
    WORD usFlagLength;

    WORD usBankStart;
    WORD usBankEnd;
    WORD usSectorStart;
    WORD usSectorEnd;

    WORD usKeyStart;
    WORD usSignatureStart;
}StructUserDataFlagInfo;

typedef struct
{
    StructUserDataGlobalInfo stUserDataGlobalInfo;
    StructUserDataKeyInfo stKeyInfo;
    StructUserDataSignatureInfo stSignatureInfo;
    StructUserFwInfo stUserFwInfo;
    StructUserDataFlagInfo stUserFlagInfo;
}StructUserCopyInfo;

typedef struct
{
    BYTE pucSignature[_MAX_RSA_SIGNATURE_SIZE];
    BYTE pucNKey[_MAX_DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE];
    BYTE pucRrmodn[_MAX_DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE];
    BYTE pucNpinv[_MAX_DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE];
    BYTE pucEKey[_MAX_DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_SIZE];
}StructRsaDataInfo;

#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON)
extern code StructDigitalSignatureRsaKeyInfo g_stDualBankDigitalSignatureRsaKeyInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern WORD ScalerDualBankUserGetKCPUBankOffset(void);

#endif // End of #if(_DUAL_BANK_SUPPORT == _ON)
