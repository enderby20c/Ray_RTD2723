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
// ID Code      : ScalerRotation.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_ROTATION_H__
#define __SCALER_ROTATION_H__


#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
#define PICT_SET_WIDTH_SCALE(x)         ((((x) % 3) == 2) ? 16 : 32) // Max: 32, 512Byte*16 = 256Byte*32, unit: 256Byte
#define PICT_SET_INIT_PAGE_WIDTH(x)     ((((x) % 3) == 2) ? (240 * 2) : (480 * 2)) // General picture = 480 (8 bank), Remain picture = 240 (8 bank), unit: (4 bank)
#define _TOTOAL_PICT_SET_NUM            (18)        // Max input timing use pict num*buffer* = 3*3*2 = 18
#define _PICT_SET_MAX_WIDTH             (1024)      // 64Byte*8Bank*16Scale = 1024, unit: 8Byte
#define _ROTATION_DISP_BLK_W            (2)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
extern void ScalerRotationSetPictSet(void);
extern void ScalerRotationSetInfo(WORD usCaphwidth, WORD usCapvheight);
extern BYTE ScalerRotationGetVerticalFactor(WORD usCaphwidth);
#endif

#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_ROTATION_H__
