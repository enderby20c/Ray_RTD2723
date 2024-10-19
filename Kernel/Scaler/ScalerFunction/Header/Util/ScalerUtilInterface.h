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
// ID Code      : ScalerUtilInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------



//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _ADDRESS_TYPE_XRAM,
    _ADDRESS_TYPE_XDATA_REG,
    _ADDRESS_TYPE_RBUS32,
    _ADDRESS_TYPE_RBUSD32,
    _ADDRESS_TYPE_ROM,
    _ADDRESS_TYPE_IMEM,
    _ADDRESS_TYPE_DMEM,
    _ADDRESS_TYPE_FLASH,
    _ADDRESS_TYPE_DDR,
    _ADDRESS_TYPE_OTHER,
} EnumAddressType;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumAddressType ScalerUtilGetAddressType(DWORD ulAddress);
extern void ScalerUtilReadDWord(DWORD ulAlignedAddr32, WORD usDwordLength, BYTE ucAddrAutoInc, DWORD *pulReadData);
