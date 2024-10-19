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
// ID Code      : ScalerVga.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_VGA_H__
#define __SCALER_VGA_H__

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions Of VGA noise margin
//--------------------------------------------------
#define _VGA_NOISE_MARGIN                               (0x40)

//--------------------------------------------------
// Noise width definitions
//--------------------------------------------------
#define _NOISE_WIDTH_AFTER_HSYNC                        (0x3C)
#define _NOISE_WIDTH_AFTER_VSYNC                        (0x01)

//--------------------------------------------------
// Noise Delay before hs definitions, Unit: ns
//--------------------------------------------------
#define _NOISE_DELAY_BEFORE_HSYNC_POSITIVE              (80) // Unit: ns
#define _NOISE_DELAY_BEFORE_HSYNC_NEGTIVE               (100) // Unit: ns

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerVgaTopSetCaptureVStartPosition(WORD usIVstart);
extern void ScalerVgaTopSetCaptureVHeight(WORD usIVheight);
extern void ScalerVgaTopSetCaptureHStartPosition(WORD usIHstart);
extern void ScalerVgaTopSetCaptureHWidth(WORD usIHwidth);

extern WORD ScalerVgaTopSearchHsEdge(void);

extern void ScalerVgaTopInitialDdomainSetting(BYTE *pucBackup);
extern void ScalerVgaTopRestoreDdomainSetting(BYTE *pucBackup);

#endif // End of #if(_VGA_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_VGA_H__
