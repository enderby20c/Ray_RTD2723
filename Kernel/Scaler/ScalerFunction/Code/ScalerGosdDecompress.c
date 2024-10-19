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
// ID Code      : ScalerGosdDecompress.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GOSD__

#include "ScalerFunctionInclude.h"
#include "Gosd/ScalerGosdDecompress.h"

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Check Compressed File magic number
// Input Value  : ulVirtualFileAddress : File Address
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdDecompressCheckMagicNumber(DWORD ulVirtualFileAddress)
{
    if(Scaler32GetDWord(ulVirtualFileAddress) != _GOSD_DECOMPRESS_ARCHIVE_MAGICNUMBER)
    {
        // first 4bytes to check compress magic number
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : GOSD DECOMPRESS data action, follow Kernel/Common/DECOMPRESS.c
// Input Value  : pstDecompressInfo
//                pulDecompressedTime : total time of compressed pass
//                ulDecompressTimeOut : timeout
// Output Value : Error code
//--------------------------------------------------
EnumGosdLoadImageResult ScalerGosdDecompressAction(StructGosdDecompressInfo *pstDecompressInfo, DWORD *pulDecompressedTime, DWORD ulDecompressTimeOut)
{
    BYTE *pucIp = pstDecompressInfo->pucInPtr; // src_b pointer
    BYTE *pucIend = pstDecompressInfo->pucInendPtr; // src_e pointer
    BYTE *pucIblockend = pstDecompressInfo->pucInblockendPtr;
    BYTE *pucRef;

    BYTE ucToken = 0;

    BYTE *pucCpySrcPtr;
    DWORD ulCpyLength = 0;

    BYTE *pucOp = pstDecompressInfo->pucOutPtr; // dst_b pointer
    BYTE *pucCpy;

    DWORD ulTmp = 0;

    DWORD pulDec32table[] = {0, 3, 2, 3, 0, 0, 0, 0};

    WORD usDiffCnt = 0;
    WORD usPreviousTime = g_usTimerCounter;

    // Main Loop
    while(pucIp < pucIend)
    {
        // block main loop
        while (pucIp < pucIblockend)
        {
            usDiffCnt = g_usTimerCounter;

            if(usDiffCnt > usPreviousTime)
            {
                usDiffCnt -= usPreviousTime;
            }
            else
            {
                usDiffCnt += (0xFFFF - usPreviousTime + 1);
            }

            // Record in/out pointer and return PAUSE when decompressed size is more than _GOSD_MAX_COMPRESSED_DATA
            if(((*pulDecompressedTime) + usDiffCnt) > ulDecompressTimeOut)
            {
                StructGosdDecompressInfo *pstCompressInfo = g_stGosdLoadImageIndexCircularQueue.pstQueueBuffer + g_stGosdLoadImageIndexCircularQueue.usQueueFront;
                pstCompressInfo->pucInPtr = pucIp;
                pstCompressInfo->pucOutPtr = pucOp;
                pstCompressInfo->pucInblockendPtr = pucIblockend;

                return _GOSD_LOADIMAGE_PAUSE;
            }
            // get runlength
            ucToken = *pucIp++;
            ulTmp = (ucToken >> _GOSD_DECOMPRESS_ML_BITS);
            if (ulTmp == _GOSD_DECOMPRESS_RUN_MASK)
            {
                DWORD ulS = 255;
                while ((pucIp < pucIblockend) && (ulS == 255))
                {
                    ulS = *pucIp++;
                    ulTmp += ulS;
                }
            }
            // copy literals
            pucCpy = pucOp + ulTmp;

            if (pucIp + ulTmp > pucIblockend - _GOSD_DECOMPRESS_COPYLENGTH)
            {
                if (pucIp + ulTmp != pucIblockend)
                {
                    // Error: DECOPRESS address must not more than pucIend
                    DebugMessageGOSD("_GOSD_LOADIMAGE_ERROR_INTPUT_DATA_ERROR", 0);

                    usDiffCnt = g_usTimerCounter;

                    if(usDiffCnt > usPreviousTime)
                    {
                        usDiffCnt -= usPreviousTime;
                    }
                    else
                    {
                        usDiffCnt += (0xFFFF - usPreviousTime + 1);
                    }

                    (*pulDecompressedTime) += usDiffCnt;

                    return _GOSD_LOADIMAGE_ERROR;
                }

                pucCpySrcPtr = pucIp;
                ulCpyLength = ulTmp;
                while (ulCpyLength--)
                {
                    *pucOp++ = *pucCpySrcPtr++;
                }

                // skip 5byte EndMark
                pucIp += ulTmp;

                // Next compressed block
                if(pucIp < pucIend)
                {
                    // full length of a compressed block
                    DWORD ulLength = TO_DWORD(pucIp[3], pucIp[2], pucIp[1], pucIp[0]);

                    pucIblockend = &pucIp[4 + ulLength];
                    pucIp += 4;
                }

                break;// Necessarily EOF, due to parsing restrictions
            }

            GOSD_DECOMPRESS_WILDCOPY(pucIp, pucOp, pucCpy);
            pucIp -= (pucOp - pucCpy);
            pucOp = pucCpy;

            // get offset
            pucRef = pucCpy - ((StructUnAlignedWord *)pucIp)->usUnalignedWORD;
            pucIp += 2;

            if (pucRef < (BYTE * const) pstDecompressInfo->pucOp)
            {
                // Error : offset creates reference outside of destination buffer
                DebugMessageGOSD("_GOSD_LOADIMAGE_ERROR_REF_OFFSET_UNDERFLOW", 0);

                usDiffCnt = g_usTimerCounter;

                if(usDiffCnt > usPreviousTime)
                {
                    usDiffCnt -= usPreviousTime;
                }
                else
                {
                    usDiffCnt += (0xFFFF - usPreviousTime + 1);
                }

                (*pulDecompressedTime) += usDiffCnt;

                return _GOSD_LOADIMAGE_ERROR;
            }

            // get matchlength
            ulTmp = (ucToken & _GOSD_DECOMPRESS_ML_MASK);

            if (ulTmp == _GOSD_DECOMPRESS_ML_MASK)
            {
                while (pucIp < pucIblockend)
                {
                    DWORD ulS = *pucIp++;
                    ulTmp += ulS;
                    if (ulS == 255)
                    {
                        continue;
                    }
                    break;
                }
            }

            // copy repeated sequence
            if ((pucOp - pucRef) < _GOSD_DECOMPRESS_STEPSIZE)
            {
                const BYTE ucDec64 = 0;

                pucOp[0] = pucRef[0];
                pucOp[1] = pucRef[1];
                pucOp[2] = pucRef[2];
                pucOp[3] = pucRef[3];
                pucOp += 4;
                pucRef += 4;
                pucRef -= pulDec32table[pucOp - pucRef];
                UNALIGNED_DWORD_COPY(pucOp, pucRef);
                pucOp += _GOSD_DECOMPRESS_STEPSIZE - 4;
                pucRef -= ucDec64;
            }
            else
            {
                UNALIGNED_DWORD_COPY(pucOp, pucRef);
                pucOp += 4;
                pucRef += 4;
            }
            pucCpy = pucOp + ulTmp - (_GOSD_DECOMPRESS_STEPSIZE - 4);

            GOSD_DECOMPRESS_WILDCOPY(pucRef, pucOp, pucCpy);
            pucOp = pucCpy; // correction
        }
    }
    // end of decoding

    usDiffCnt = g_usTimerCounter;

    if(usDiffCnt > usPreviousTime)
    {
        usDiffCnt -= usPreviousTime;
    }
    else
    {
        usDiffCnt += (0xFFFF - usPreviousTime + 1);
    }

    (*pulDecompressedTime) += usDiffCnt;
    return _GOSD_LOADIMAGE_OK;
}

#endif // #if(_GOSD_SUPPORT == _ON)
