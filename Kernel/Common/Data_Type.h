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
// ID Code      : Data_Type.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#include <CompilerSpecific.h>
#include <stdio.h>

//****************************************************************************
// Data Type Redefine
//****************************************************************************
typedef BYTE                REG_TYPE;

//--------------------------------------------------
// Debug message function
//--------------------------------------------------
#define DEBUG_MESSAGE_FUNCTION(x, y)                        CPU32_DBG_MSG((x), (y))

//--------------------------------------------------
// Register address mapping
//--------------------------------------------------
#define REG_MAPPING(x)                                      (GET_XDATA_REG_32BIT_ADDR(x))


//--------------------------------------------------
// Macros of controlling the 16-bits scaler registers
//--------------------------------------------------
#define memcpy                                              ScalerUtilMEMCPY
#define memset                                              ScalerUtilMEMSET
#define memcmp                                              ScalerUtilMEMCMP

#define ScalerGetByte(usAddr)                               (SCALER32_GET_XDATA_REG((usAddr)))
#define ScalerSetByte(usAddr, ucValue)                      {SCALER32_SET_XDATA_REG((usAddr), (ucValue));}
#define ScalerGetBit(usAddr, ucAnd)                         ((ScalerGetByte((usAddr))) & (ucAnd))
#define ScalerSetBit(usAddr, ucAnd, ucOr)                   {ScalerSetByte((usAddr), (((ScalerGetByte((usAddr))) & (ucAnd)) | (ucOr)));}

#define ScalerGetWord(usAddr)                               TO_WORD(\
                                                                ScalerGetByte((usAddr)),\
                                                                ScalerGetByte((usAddr) + 1)\
                                                            )

#define ScalerSetWord(usAddr, usValue)                      {\
                                                                ScalerSetByte((usAddr), ((BYTE)((WORD)(usValue) >> 8)));\
                                                                ScalerSetByte((usAddr) + 1, ((BYTE)(usValue)));\
                                                            }

#define ScalerGetDWord(usAddr)                              TO_DWORD(\
                                                                ScalerGetByte((usAddr)),\
                                                                ScalerGetByte((usAddr) + 1),\
                                                                ScalerGetByte((usAddr) + 2),\
                                                                ScalerGetByte((usAddr) + 3)\
                                                            )


#define ScalerSetDWord(usAddr, ulValue)                     {\
                                                                ScalerSetByte((usAddr), ((BYTE)((DWORD)(ulValue) >> 24)));\
                                                                ScalerSetByte((usAddr) + 1, ((BYTE)((DWORD)(ulValue) >> 16)));\
                                                                ScalerSetByte((usAddr) + 2, ((BYTE)((DWORD)(ulValue) >> 8)));\
                                                                ScalerSetByte((usAddr) + 3, ((BYTE)(ulValue)));\
                                                            }

#define ScalerMaskSetDWord(usAddr, ulMask, ulValue)         {\
                                                                DWORD ulTmpValue = (\
                                                                    (ScalerGetDWord(usAddr) & (ulMask)) | (~(ulMask) & (ulValue))\
                                                                );\
                                                                ScalerSetDWord((usAddr), ulTmpValue);\
                                                            }

//--------------------------------------------------
// Macros of controlling the scaler registers for EXINT
//--------------------------------------------------
#define ScalerGetByte_EXINT(usAddr)                         ScalerGetByte((usAddr))
#define ScalerSetByte_EXINT(usAddr, ucValue)                {ScalerSetByte((usAddr), (ucValue));}
#define ScalerGetBit_EXINT(usAddr, ucAnd)                   ScalerGetBit((usAddr), (ucAnd))
#define ScalerSetBit_EXINT(usAddr, ucAnd, ucOr)             {ScalerSetBit((usAddr), (ucAnd), (ucOr));}

#define ScalerGetWord_EXINT(usAddr)                         ScalerGetWord((usAddr))
#define ScalerSetWord_EXINT(usAddr, usValue)                {ScalerSetWord((usAddr), (usValue));}
#define ScalerGetDWord_EXINT(usAddr)                        ScalerGetDWord((usAddr))
#define ScalerSetDWord_EXINT(usAddr, ulValue)               {ScalerSetDWord((usAddr), (ulValue));}

#define ScalerGetByte_EXINT3(usAddr)                        ScalerGetByte((usAddr))
#define ScalerSetByte_EXINT3(usAddr, ucValue)               {ScalerSetByte((usAddr), (ucValue));}
#define ScalerGetBit_EXINT3(usAddr, ucAnd)                  ScalerGetBit((usAddr), (ucAnd))
#define ScalerSetBit_EXINT3(usAddr, ucAnd, ucOr)            {ScalerSetBit((usAddr), (ucAnd), (ucOr));}


#define ScalerGetByte_EXINT5(usAddr)                        ScalerGetByte((usAddr))
#define ScalerSetByte_EXINT5(usAddr, ucValue)               {ScalerSetByte((usAddr), (ucValue));}
#define ScalerGetBit_EXINT5(usAddr, ucAnd)                  ScalerGetBit((usAddr), (ucAnd))
#define ScalerSetBit_EXINT5(usAddr, ucAnd, ucOr)            {ScalerSetBit((usAddr), (ucAnd), (ucOr));}
//--------------------------------------------------
// Macros of controlling the scaler registers for EXINT3
//--------------------------------------------------
#define ScalerGetByte_EXINT3(usAddr)                        ScalerGetByte((usAddr))
#define ScalerSetByte_EXINT3(usAddr, ucValue)               {ScalerSetByte((usAddr), (ucValue));}
#define ScalerGetBit_EXINT3(usAddr, ucAnd)                  ScalerGetBit((usAddr), (ucAnd))
#define ScalerSetBit_EXINT3(usAddr, ucAnd, ucOr)            {ScalerSetBit((usAddr), (ucAnd), (ucOr));}

//--------------------------------------------------
// Macros of controlling the scaler registers for EXIN5
//--------------------------------------------------
#define ScalerGetByte_EXINT5(usAddr)                        ScalerGetByte((usAddr))
#define ScalerSetByte_EXINT5(usAddr, ucValue)               {ScalerSetByte((usAddr), (ucValue));}
#define ScalerGetBit_EXINT5(usAddr, ucAnd)                  ScalerGetBit((usAddr), (ucAnd))
#define ScalerSetBit_EXINT5(usAddr, ucAnd, ucOr)            {ScalerSetBit((usAddr), (ucAnd), (ucOr));}

//--------------------------------------------------
// Macros of controlling the scaler registers for WDINT
//--------------------------------------------------
#define ScalerGetByte_WDINT(usAddr)                         ScalerGetByte((usAddr))
#define ScalerSetByte_WDINT(usAddr, ucValue)                {ScalerSetByte((usAddr), (ucValue));}
#define ScalerGetBit_WDINT(usAddr, ucAnd)                   ScalerGetBit((usAddr), (ucAnd))
#define ScalerSetBit_WDINT(usAddr, ucAnd, ucOr)             {ScalerSetBit((usAddr), (ucAnd), (ucOr));}

//--------------------------------------------------
// Macros of controlling the scaler registers for T2INT
//--------------------------------------------------
#define ScalerGetByte_T2INT(usAddr)                         ScalerGetByte((usAddr))
#define ScalerSetByte_T2INT(usAddr, ucValue)                {ScalerSetByte((usAddr), (ucValue));}
#define ScalerGetBit_T2INT(usAddr, ucAnd)                   ScalerGetBit((usAddr), (ucAnd))
#define ScalerSetBit_T2INT(usAddr, ucAnd, ucOr)             {ScalerSetBit((usAddr), (ucAnd), (ucOr));}

//--------------------------------------------------
// Macros of controlling the 32bits scaler registers
//--------------------------------------------------
#define Scaler32GetDWord(ulAddr)                            (*((volatile DWORD *)(ulAddr)))
#define Scaler32SetDWord(ulAddr, ulValue)                   {*((volatile DWORD *)(ulAddr)) = ((DWORD)(ulValue));}
#define Scaler32GetBit(ulAddr, ulAnd)                       (*((volatile DWORD *)(ulAddr)) & ((DWORD)(ulAnd)))
#define Scaler32SetBit(ulAddr, ulAnd, ulOr)                 {*((volatile DWORD *)(ulAddr)) = (*((volatile DWORD *)(ulAddr)) & ((DWORD)(ulAnd))) | ((DWORD)(ulOr));}

#define Scaler32GetByte(ulAddr, ucIndex)                    (*((volatile BYTE *)((ulAddr) + (ucIndex))))
#define Scaler32SetByte(ulAddr, ucByteIndex, ucValue)       {Scaler32SetBit((ulAddr), ~((DWORD)0xFF << ((ucByteIndex) << 3)), ((DWORD)(ucValue) << ((ucByteIndex) << 3)));}

#define Scaler32GetWord(ulAddr, ucIndex)                    (*((volatile WORD *)((ulAddr) + (ucIndex) * 2)))
#define Scaler32SetWord(ulAddr, ucWordIndex, usValue)       {Scaler32SetBit((ulAddr), ~((DWORD)0xFFFF << ((ucWordIndex) << 4)), ((DWORD)(usValue) << ((ucWordIndex) << 4)));}

//--------------------------------------------------
// Macros of controlling the 32bits scaler registers for EXINT0
//--------------------------------------------------
#define Scaler32GetDWord_EXINT0(ulAddr)                     (Scaler32GetDWord(ulAddr))
#define Scaler32SetDWord_EXINT0(ulAddr, ulValue)            {Scaler32SetDWord((ulAddr), (ulValue));}
#define Scaler32GetWord_EXINT0(ulAddr, ucIndex)             (Scaler32GetWord((ulAddr), (ucIndex)))
#define Scaler32SetWord_EXINT0(ulAddr, ucWordIndex, usValue)\
                                                            {Scaler32SetWord((ulAddr), (ucWordIndex), (usValue));}
#define Scaler32GetBit_EXINT0(ulAddr, ulAnd)                (Scaler32GetBit((ulAddr), (ulAnd)))
#define Scaler32SetBit_EXINT0(ulAddr, ulAnd, ulOr)          {Scaler32SetBit((ulAddr), (ulAnd), (ulOr));}
#define Scaler32GetByte_EXINT0(ulAddr, ucIndex)             (Scaler32GetByte((ulAddr), (ucIndex)))
#define Scaler32SetByte_EXINT0(ulAddr, ucByteIndex, ucValue)\
                                                            {Scaler32SetByte((ulAddr), (ucByteIndex), (ucValue));}

//--------------------------------------------------
// Macros of controlling the 32bits scaler registers for EXINT0
//--------------------------------------------------
#define Scaler32GetDWord_WDINT(ulAddr)                      (Scaler32GetDWord(ulAddr))
#define Scaler32SetDWord_WDINT(ulAddr, ulValue)             {Scaler32SetDWord((ulAddr), (ulValue));}
#define Scaler32GetWord_WDINT(ulAddr, ucIndex)              (Scaler32GetWord((ulAddr), (ucIndex)))
#define Scaler32SetWord_WDINT(ulAddr, ucWordIndex, usValue) {Scaler32SetWord((ulAddr), (ucWordIndex), (usValue));}
#define Scaler32SetBit_WDINT(ulAddr, ulAnd, ulOr)           {Scaler32SetBit((ulAddr), (ulAnd), (ulOr));}
#define Scaler32GetBit_WDINT(ulAddr, ulAnd)                 (Scaler32GetBit((ulAddr), (ulAnd)))
#define Scaler32GetByte_WDINT(ulAddr, ucIndex)              (Scaler32GetByte((ulAddr), (ucIndex)))
#define Scaler32SetByte_WDINT(ulAddr, ucByteIndex, ucValue)\
                                                            {Scaler32SetByte((ulAddr), (ucByteIndex), (ucValue));}

//--------------------------------------------------
// Macros of controlling the 32bits scaler registers for T2INT
//--------------------------------------------------
#define Scaler32GetDWord_T2INT(ulAddr)                      (Scaler32GetDWord(ulAddr))
#define Scaler32SetDWord_T2INT(ulAddr, ulValue)             {Scaler32SetDWord((ulAddr), (ulValue));}
#define Scaler32GetByte_T2INT(ulAddr, ucIndex)              Scaler32GetByte((ulAddr), (ucIndex))
#define Scaler32SetByte_T2INT(ulAddr, ucByteIndex, ucValue) {Scaler32SetByte((ulAddr), (ucByteIndex), (ucValue));}
#define Scaler32GetBit_T2INT(ulAddr, ulAnd)                 Scaler32GetBit((ulAddr), (ulAnd))
#define Scaler32SetBit_T2INT(ulAddr, ulAnd, ulOr)           {Scaler32SetBit((ulAddr), (ulAnd), (ulOr));}


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void *ScalerUtilMEMCPY(void *pulDestAddr32, const void *pulSrcAddr32, size_t  usLength);
extern void *ScalerUtilMEMSET(void *pulDestAddr32, int chValue, size_t usLength);
extern int ScalerUtilMEMCMP(const void *pulSrc1Addr32, const void *pulSrc2Addr32, size_t usLength);

extern void *__real_memcpy(void *pulDestAddr32, const void *pulSrcAddr32, size_t  usLength);
extern void *__real_memset(void *pulDestAddr32, int chValue, size_t usLength);
extern int __real_memcmp(const void *pulSrc1Addr32, const void *pulSrc2Addr32, size_t usLength);

#endif // End of #ifndef __DATA_TYPE_H__
