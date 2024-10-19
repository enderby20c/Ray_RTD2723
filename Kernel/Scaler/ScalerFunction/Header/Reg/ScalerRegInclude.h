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
// ID Code      : ScalerRegInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _REG8TO32_BYTE_0                                0   // REG32[7:0]
#define _REG8TO32_BYTE_1                                1   // REG32[15:8]
#define _REG8TO32_BYTE_2                                2   // REG32[24:16]
#define _REG8TO32_BYTE_3                                3   // REG32[31:24]


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerBurstWrite(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, WORD usHostAddr, BYTE ucTableType, bit bTableLocation);

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
extern void ScalerBurstWrite4ByteMode(BYTE *pucAddress, WORD usWriteLength, WORD usHostAddr, BYTE ucTableType, bit bTableLocation);
#endif

extern void ScalerSetDataPortByte(WORD usAddr, BYTE ucValue1, BYTE ucValue2);
extern void ScalerGetDataPortByte(WORD usAddr, BYTE ucValue, WORD usLength, BYTE *pucArray, bit bAutoInc);

extern void ScalerSetDataPortBit(WORD usAddr, BYTE ucValue, DWORD ulAnd, BYTE ucOr);
extern BYTE ScalerGetDataPortBit(WORD usAddr, BYTE ucValue, BYTE ucAnd);

extern void ScalerSetDataPortByte_EXINT0(WORD usAddr, BYTE ucValue1, BYTE ucValue2);
extern void ScalerGetDataPortByte_EXINT0(WORD usAddr, BYTE ucValue, WORD usLength, BYTE *pucArray, bit bAutoInc);
extern void ScalerSetDataPortBit_EXINT0(WORD usAddr, BYTE ucValue, DWORD ulAnd, BYTE ucOr);
extern BYTE ScalerGetDataPortBit_EXINT0(WORD usAddr, BYTE ucValue, BYTE ucAnd);
extern BYTE ScalerGetDataPortSingleByte_EXINT0(WORD usAddr, BYTE ucValue);
extern WORD ScalerGetDataPortWord_EXINT0(WORD usAddr, BYTE ucValue, bit bAutoInc);

extern DWORD ScalerGetDataPortDword(WORD usAddr, BYTE ucValue, bit bAutoInc);
extern BYTE ScalerGetDataPortSingleByte(WORD usAddr, BYTE ucValue);
extern WORD ScalerGetDataPortWord(WORD usAddr, BYTE ucValue, bit bAutoInc);
extern void ScalerSetDataPortDword(WORD usAddr, BYTE ucValue1, DWORD ulValue2);
extern void ScalerSetDataPortWord(WORD usAddr, BYTE ucValue1, WORD usValue2);

extern void ScalerRead(WORD usAddr, WORD usLength, BYTE *pucArray, bit bAutoInc);
extern void ScalerWrite(WORD usAddr, WORD usLength, BYTE *pucArray, bit bAutoInc);

