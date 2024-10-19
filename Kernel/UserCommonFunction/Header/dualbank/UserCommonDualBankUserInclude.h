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
// ID Code      : UserCommonDualBankUserInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
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

// 4 Byte MagicWord + 4 Byte Version + 4BYte Type + 4 Byte Key Len + 4 Byte Signature len
#define _DIGITAL_SIGNATURE_INFO_HEADER_SIZE                     20

//------------------------------------------------------
// User Flag length setting
//------------------------------------------------------
#define _DUAL_BANK_USER_KEY_LENGTH                              (_DIGITAL_SIGNATURE_RSA_KEY_NKEY_SIZE + _DIGITAL_SIGNATURE_RSA_KEY_RRMODN_SIZE + _DIGITAL_SIGNATURE_RSA_KEY_NPINV_SIZE + _DIGITAL_SIGNATURE_RSA_KEY_EXORKEY_SIZE)
#define _DUAL_BANK_USER_FLAG_LENGTH                             5
#define _DUAL_BANK_USER_SIGNATURE_LENGTH                        (_DIGITAL_SIGNATURE_HW_RSA_TYPE / 8)

//------------------------------------------------------
// User I/II setting
//------------------------------------------------------
#define _DUAL_BANK_USER_I_FW_BANK_START                         _DUAL_BANK_USER_FW_START_BANK
#define _DUAL_BANK_USER_I_FW_BANK_END                           (_DUAL_BANK_USER_I_FW_BANK_START + _DUAL_BANK_USER_FW_CODE_SIZE - 1)

#define _DUAL_BANK_USER_II_FW_BANK_START                        (_DUAL_BANK_USER_FW_START_BANK + _DUAL_BANK_USER_FW_CODE_SIZE)
#define _DUAL_BANK_USER_II_FW_BANK_END                          (_DUAL_BANK_USER_II_FW_BANK_START + _DUAL_BANK_USER_FW_CODE_SIZE - 1)


#if(_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_USER)
#define _DUAL_BANK_USER_I_USER_DATA_BANK_ADDR                   (_DUAL_BANK_USER_I_FW_BANK_START + _DUAL_BANK_USER_I_FLAG_LOCATE_BANK)
#else
#define _DUAL_BANK_USER_I_USER_DATA_BANK_ADDR                   _DUAL_BANK_USER_I_FLAG_LOCATE_BANK
#endif

#if(_DUAL_BANK_USER_FLAG_LOCATION_AREA == _DUAL_BANK_FLAG_LOCATION_IN_USER)
#define _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR                  (_DUAL_BANK_USER_II_FW_BANK_START + _DUAL_BANK_USER_II_FLAG_LOCATE_BANK)
#else
#define _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR                  _DUAL_BANK_USER_II_FLAG_LOCATE_BANK
#endif

#if(_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR == _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR)
#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                     0x0A
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                    0x0D
#else
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                     0x0E
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                    0x0F
#endif
#else
#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                     0x0D
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                    0x0D
#else
#define _DUAL_BANK_USER_I_DATA_SECTOR_START                     0x0F
#define _DUAL_BANK_USER_II_DATA_SECTOR_START                    0x0F
#endif
#endif

#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_I_KEY_START_ADDR                        ((WORD)_DUAL_BANK_USER_I_DATA_SECTOR_START << 12)
#define _DUAL_BANK_USER_I_FLAG_START_ADDR                       ((WORD)(_DUAL_BANK_USER_I_DATA_SECTOR_START + 1) << 12)
#define _DUAL_BANK_USER_I_SIGNATURE_START_ADDR                  (((WORD)_DUAL_BANK_USER_I_DATA_SECTOR_START + 2) << 12)
#define _DUAL_BANK_USER_I_DATA_SECTOR_END                       (_DUAL_BANK_USER_I_DATA_SECTOR_START + 2)
#else
#define _DUAL_BANK_USER_I_KEY_START_ADDR                        ((WORD)_DUAL_BANK_USER_I_DATA_SECTOR_START << 12)
#define _DUAL_BANK_USER_I_FLAG_START_ADDR                       ((WORD)(_DUAL_BANK_USER_I_DATA_SECTOR_START << 12) + _DUAL_BANK_USER_KEY_LENGTH)
#define _DUAL_BANK_USER_I_SIGNATURE_START_ADDR                  ((WORD)(_DUAL_BANK_USER_I_DATA_SECTOR_START << 12) + _DUAL_BANK_USER_KEY_LENGTH + _DUAL_BANK_USER_FLAG_LENGTH)
#define _DUAL_BANK_USER_I_DATA_SECTOR_END                       _DUAL_BANK_USER_I_DATA_SECTOR_START
#endif

#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_DIFFER_SECTOR)
#define _DUAL_BANK_USER_II_KEY_START_ADDR                       ((WORD)_DUAL_BANK_USER_II_DATA_SECTOR_START << 12)
#define _DUAL_BANK_USER_II_FLAG_START_ADDR                      ((WORD)(_DUAL_BANK_USER_II_DATA_SECTOR_START + 1) << 12)
#define _DUAL_BANK_USER_II_SIGNATURE_START_ADDR                 ((WORD)(_DUAL_BANK_USER_II_DATA_SECTOR_START + 2) << 12)
#define _DUAL_BANK_USER_II_DATA_SECTOR_END                      (_DUAL_BANK_USER_II_DATA_SECTOR_START + 2)
#else
#define _DUAL_BANK_USER_II_KEY_START_ADDR                       ((WORD)_DUAL_BANK_USER_II_DATA_SECTOR_START << 12)
#define _DUAL_BANK_USER_II_FLAG_START_ADDR                      ((WORD)(_DUAL_BANK_USER_II_DATA_SECTOR_START << 12) + _DUAL_BANK_USER_KEY_LENGTH)
#define _DUAL_BANK_USER_II_SIGNATURE_START_ADDR                 ((WORD)(_DUAL_BANK_USER_II_DATA_SECTOR_START << 12) + _DUAL_BANK_USER_KEY_LENGTH + _DUAL_BANK_USER_FLAG_LENGTH)
#define _DUAL_BANK_USER_II_DATA_SECTOR_END                      _DUAL_BANK_USER_II_DATA_SECTOR_START
#endif

//------------------------------------------------------
// Flag Data in User FW
//------------------------------------------------------
#if(_DUAL_BANK_USER_FLAG_LAYOUT == _DUAL_BANK_ONE_SECTOR)
#define _DUALBANK_FILL_LENGTH                                   4 // 1 Secter 4K (Unit: K bytes)
#else
#define _DUALBANK_FILL_LENGTH                                   12 // 3 Secter 12K (Unit: K bytes)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonDualBankUserEnableISPChannel(void);
#if(_DUAL_BANK_TYPE != _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)
extern WORD UserCommonDualBankUserGetIspStartBank(void);
extern DWORD UserCommonDualBankUserGetIspKeyAddr(void);
extern DWORD UserCommonDualBankUserGetIspFlagAddr(void);
extern DWORD UserCommonDualBankUserGetIspSignatureAddr(void);
extern DWORD UserCommonDualBankUserGetCurrentKeyAddr(void);
extern BYTE UserCommonDualBankUserGetVerifyCopyResult(void);
#endif

#endif

