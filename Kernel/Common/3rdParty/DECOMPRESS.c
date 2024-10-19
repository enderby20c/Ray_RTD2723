/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   Commercial License Usage                                                   */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

/*
   DECOMPRESS - Fast LZ compression algorithm
   Copyright (C) 2011-2012, Yann Collet.
   BSD 2-Clause License (http://www.opensource.org/licenses/bsd-license.php)

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

       * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
       * Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following disclaimer
   in the documentation and/or other materials provided with the
   distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary AND BSD 2-Clause   */

 //----------------------------------------------------------------------------------------------------
// ID Code      : DECOMPRESS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __DECOMPRESS__

#include "ScalerFunctionInclude.h"
#include "stddef.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
 #define ARCHIVE_MAGICNUMBER 0x184C2102

#define likely(x)                                   __builtin_expect(!!(x), 1)
#define unlikely(x)                                 __builtin_expect(!!(x), 0)

#define DECOMPRESS_SUCCESS                          (0)
#define DECOMPRESS_ERROR_INVALID_MAGIC_NUMBER       (-1)
#define DECOMPRESS_ERROR_REF_OFFSET_UNDERFLOW       (-2)
#define DECOMPRESS_ERROR_INTPUT_DATA_ERROR          (-3)

/* 32-bit */
#define STEPSIZE                                    4

#define ML_BITS                                     4
#define COPYLENGTH                                  8
#define ML_MASK                                     ((1U << ML_BITS) - 1)
#define RUN_BITS                                    (8 - ML_BITS)
#define RUN_MASK                                    ((1U << RUN_BITS) - 1)

#define DECOMPRESS_WILDCOPY(s, d, e)                \
                                                    do {\
                                                        UNALIGNED_DWORD_COPY(d, s);\
                                                        d += 4;\
                                                        s += 4;\
                                                    } while (d < e)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
const size_t dec32table[] = {0, 3, 2, 3, 0, 0, 0, 0};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : The DECOMPRESS_DECOMPRESS function
// Input Value  :
//                inp:Location Pointer to Src Compressed Kernel
//                outp:Location Pointer to Dst Extracted Kernel
//                ulContentSize:Compressed Kernel Size
// Output Value :
//                ErrorCode:error number,0=success
//--------------------------------------------------
int _DECOMPRESS(const BYTE *inp,//    Source , compressed kernel location
                         BYTE *outp,//    Dest ,extracted kernel location
                         DWORD ulContentSize // Source , compressed kernel size
                  )
{
    const BYTE *ref;
    BYTE token;

    const BYTE *CpySrcPtr;
    size_t CpyLength;
    size_t length;
    BYTE *cpy;

    // dst begin pointer
    BYTE *op = (BYTE *) outp;
    // src begin pointer
    const BYTE *ip = (const BYTE *) inp;
    // src end pointer
    const BYTE *const iend = ip + ulContentSize;
    // src_block end pointer
    const BYTE *iblockend;

    // byte 0~3,read first 4bytes to check magic number
    length = TO_DWORD(ip[3], ip[2], ip[1], ip[0]);
    if (length != ARCHIVE_MAGICNUMBER)
    {
        return DECOMPRESS_ERROR_INVALID_MAGIC_NUMBER;
    }
    ip += 4;

    /* Main Loop */
    while (ip < iend)
    {
        // length of next block
        length = TO_DWORD(ip[3], ip[2], ip[1], ip[0]);
        ip += 4;
        iblockend = &ip[length];

        // block main loop
        while(ip < iblockend)
        {
            /* get runlength */
            token = *ip++;
            length = (token >> ML_BITS);
            if (length == RUN_MASK)
            {
                int s = 255;
                while ((ip < iblockend) && (s == 255))
                {
                    s = *ip++;
                    length += s;
                }
            }
            /* copy literals */
            cpy = op + length;
            if(ip + length > iblockend - COPYLENGTH)
            {
                if (ip + length != iblockend)
                {
                    // Error: DECOMPRESS format requires to consume all input at this stage
                    return DECOMPRESS_ERROR_INTPUT_DATA_ERROR;
                }

                CpySrcPtr = ip;
                CpyLength = length;
                while (CpyLength--)
                {
                    *op++ = *CpySrcPtr++;
                }

                ip += length;

                break;/* Necessarily EOF, due to parsing restrictions */
            }
            DECOMPRESS_WILDCOPY(ip, op, cpy);
            ip -= (op - cpy);
            op = cpy;

            /* get offset */
            ref = cpy - ((StructUnAlignedWord *)ip)->usUnalignedWORD;

            ip += 2;
            if (ref < (BYTE * const) outp)
            {
                // Error : offset creates reference outside of destination buffer
                return DECOMPRESS_ERROR_REF_OFFSET_UNDERFLOW;
            }

            /* get matchlength */
            length = (token & ML_MASK);

            if (length == ML_MASK)
            {
                while (ip < iend)
                {
                    int s = *ip++;
                    length += s;
                    if (s == 255)
                    {
                        continue;
                    }
                    break;
                }
            }

            /* copy repeated sequence */
            if (unlikely((op - ref) < STEPSIZE))
            {
                const int dec64 = 0;

                op[0] = ref[0];
                op[1] = ref[1];
                op[2] = ref[2];
                op[3] = ref[3];
                op += 4;
                ref += 4;
                ref -= dec32table[op - ref];
                UNALIGNED_DWORD_COPY(op, ref);
                op += STEPSIZE - 4;
                ref -= dec64;
            }
            else
            {
                UNALIGNED_DWORD_COPY(op, ref);
                op += 4;
                ref += 4;
            }

            cpy = op + length - (STEPSIZE-4);

            DECOMPRESS_WILDCOPY(ref, op, cpy);
            op = cpy; /* correction */
        }
    }

    /* end of decoding */
    return DECOMPRESS_SUCCESS;
}

//--------------------------------------------------
// Description  : The DECOMPRESS_DECOMPRESS function
// Input Value  :
//                pucInput:Location Pointer to Src Compressed Kernel
//                pucOutput:Location Pointer to Dst Extracted Kernel
//                ulContentSize:Compressed Kernel Size
// Output Value :
//                ErrorCode:error number,0=success
//--------------------------------------------------
EnumDecompressStatus DECOMPRESS(const BYTE *pucInput, BYTE *pucOutput, DWORD ulContentSize)
{
    switch(_DECOMPRESS(pucInput, pucOutput, ulContentSize))
    {
        default:
        case DECOMPRESS_SUCCESS:
            return _DECOMPRESS_SUCCESS;

        case DECOMPRESS_ERROR_INVALID_MAGIC_NUMBER:
            return _DECOMPRESS_ERROR_INVALID_MAGIC_NUMBER;

        case DECOMPRESS_ERROR_REF_OFFSET_UNDERFLOW:
            return _DECOMPRESS_ERROR_REF_OFFSET_UNDERFLOW;

        case DECOMPRESS_ERROR_INTPUT_DATA_ERROR:
            return _DECOMPRESS_ERROR_INTPUT_DATA_ERROR;
    }
}

