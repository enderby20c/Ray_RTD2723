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
// ID Code      : ScalerTcon.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TCON_H__
#define __SCALER_TCON_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _TCON_DOUBLE_BUFFER_WAIT_TIME             168
#define GET_TCON_GLOBAL_ENABLE()                  (g_stTconStatus.b1TconGlobalEnable)
#define SET_TCON_GLOBAL_ENABLE(x)                 (g_stTconStatus.b1TconGlobalEnable = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1TconGlobalEnable : 1;
} StructTconStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTconGlobalEnable(bit bEnable);
extern void ScalerTconFBmodeAdjust(WORD *pusHstart, WORD *pusHend);

#endif // End of #ifndef __SCALER_TCON_H__
