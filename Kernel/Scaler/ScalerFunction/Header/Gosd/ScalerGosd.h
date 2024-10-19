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
// ID Code      : ScalerGosd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_GOSD_H__
#define __SCALER_GOSD_H__

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GOSD_IMAGE_SOURCE_MAGICNUMBER                  0x44534f47

#if(_HW_CPU32_KCPU_MEMORYMAP_ACCESS_DDR == _TRUE)
#define _GOSD_SURFACE_ALIGN_UNIT                        (MAXOF(_HW_CPU32_KCPU_DCACHE_LINE_SIZE_IN_BYTE, 16))
#elif(_HW_CPU32_SCPU_MEMORYMAP_ACCESS_DDR == _TRUE)
#define _GOSD_SURFACE_ALIGN_UNIT                        (MAXOF(_HW_CPU32_SCPU_DCACHE_LINE_SIZE_IN_BYTE, 16))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulSignature;
    DWORD ulHeaderSize;
    DWORD ulInfoSize;
    DWORD ulImageNumber;
} StructGosdImageSourceFileHeader;

typedef struct
{
    DWORD ulOffset;
    DWORD ulFlashSize;
    DWORD ulDdrSize;
} StructGosdImageSourceInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // #if(_GOSD_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_GOSD_H__
