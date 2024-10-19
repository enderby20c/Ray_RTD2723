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
// ID Code      : SysBoot.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
// SCPU firmware image info
extern const DWORD __scpu_firmware_image_load_address_start;
extern const DWORD __scpu_firmware_image_load_address_end;
extern const DWORD __scpu_firmware_image_virtual_address_start;

// SCPU firmware stack info
extern const DWORD __scpu_firmware_kernel_estack;

// SCPU firmware reset handler
extern const DWORD __scpu_firmware_reset_handler;

// SCPU firmware itcm section info
extern const DWORD __scpu_firmware_itcm_load_address_start;
extern const DWORD __scpu_firmware_itcm_length;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_CPU32_COMPRESSED_IMAGE_SUPPORT == _ON)
extern void SysBootLoadCompressedFirmwareImage(void);
#endif

extern void SysBootLoadFirmwareImage(DWORD *pulDest);

extern void SysBootInitItcm(void);
extern void SysBootNotifyBootStatus(bit bStatus);
extern void SysBootMain(void);

