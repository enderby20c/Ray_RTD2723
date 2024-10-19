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
// ID Code      : UserCommonDualBankInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulSize;
    WORD usAddress;
    BYTE *pucTable;
}StructDualBankUserFlagInfo;

typedef void (*FUNC_PTR_AUX_INIT)(void);
typedef struct
{
    BYTE ucDigitalSignatureType;
    BYTE ucDualBankType;
    BYTE ucFlashPartitionSupport;
    BYTE ucRollBackSupport;
    FUNC_PTR_AUX_INIT pfnAuxInit;
}
StructDualBankProjectInfo;
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

//----------------------------------------------------------------------------------------
// Dual Bank Flash Partition
//----------------------------------------------------------------------------------------
extern void UserCommonDualBankUserFlagBootHandler(void);
extern void UserCommonDualBankNormalBootHandler(void);
#if((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON) &&\
    ((_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOOT) ||\
    (_DUAL_BANK_FLASH_PARTITION_BOOT_USER_SEL == _DUAL_BANK_FLASH_PARTITION_BOTH)))
extern void UserCommonDualBankProcess(void);
#endif

#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON)
extern EnumDualBankCopyResult UserCommonDualBankProcessFlashPartitionCopy(EnumDualBankCodeRegion enumSrcRegion, EnumDualBankCodeRegion enumDstRegion);
#endif

