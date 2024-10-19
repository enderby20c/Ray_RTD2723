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
// ID Code      : ScalerMbr.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_MBR_H__
#define __SCALER_MBR_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _RTK_ADV_MBR_NON_FLICKER_MIN_FRAME_RATE                 720

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern BYTE g_ucMbrDrrVFreqIndex;
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************




#endif // End of #ifndef __SCALER_MBR_H__
