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
// ID Code      : ScalerTimer.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TIMER_H__
#define __SCALER_TIMER_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern WORD g_usTimer0MS;   // Timer0 Setting (T0 target ms value)
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern WORD g_usTimer1MS;   // Timer1 Setting (T1 target ms value)
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif // End of #ifndef __SCALER_TIMER_H__
