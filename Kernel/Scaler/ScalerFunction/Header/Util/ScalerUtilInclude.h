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
// ID Code      : ScalerUtilInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_ALIGNED_ADDRESS(x)                          ((x) & 0xFFFFFFFC)
#define IS_REG_ADDR(enumAddrType)                       (((enumAddrType) == _ADDRESS_TYPE_XDATA_REG) ||\
                                                         ((enumAddrType) == _ADDRESS_TYPE_RBUSD32) ||\
                                                         ((enumAddrType) == _ADDRESS_TYPE_RBUS32))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _ENDIAN_TYPE_BIG,
    _ENDIAN_TYPE_LITTLE,
} EnumEndianType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUtilReadWord(DWORD ulAlignedAddr32, WORD usWordLength, BYTE ucAddrAutoInc, WORD *pusReadData);
extern void ScalerUtilBurstWrite32(const BYTE *pucAddress32, WORD usWriteLength32, BYTE ucBankNum32, DWORD ulHostAddr32, BYTE ucTableType32, BYTE ucTableLocation32, EnumEndianType enumEndianType);

