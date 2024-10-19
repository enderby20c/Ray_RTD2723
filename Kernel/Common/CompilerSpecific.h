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
// ID Code      : CompilerSpecific.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __COMPLIER_SPECIFIC__
#define __COMPLIER_SPECIFIC__

//****************************************************************************
// Data Type Redefine
//****************************************************************************
//--------------------------------------------------
// Custom int type setting
//--------------------------------------------------

#ifdef __SDCC
#include <stdint.h>
#endif

#ifdef __GNUC__
#include <stdint.h>
#endif

// generic int types
typedef uint8_t         BYTE;
typedef uint16_t        WORD;
typedef uint32_t        DWORD;
typedef uint64_t        QWORD;

typedef int8_t          SBYTE;
typedef int16_t         SWORD;
typedef int32_t         SDWORD;
typedef int64_t         SQWORD;

//--------------------------------------------------
// Custom data type setting
//--------------------------------------------------
#ifdef __SDCC
#include <stdbool.h>
#define data            __data
#define idata           __idata
#define xdata           __xdata
#define bit             __bit
#define code            __code
#endif

#ifdef __GNUC__
#include <stdbool.h>
#define data
#define idata
#define xdata
#define bit             bool
#define code            const
#endif

//--------------------------------------------------
// Interrupt & register bank setting
//--------------------------------------------------
#ifdef __SDCC
#define NOP()           __asm nop __endasm
#endif

#ifdef __GNUC__
#define NOP()           __NOP()
#endif

#endif // End of __COMPLIER_SPECIFIC__

