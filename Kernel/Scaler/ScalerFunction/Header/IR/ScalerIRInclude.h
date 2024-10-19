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
// ID Code      : ScalerIRInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_IR_SUPPORT == _IR_HW_SUPPORT)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_IR_HW_RECEIVED()                                (g_bIRReceived)
#define SET_IR_HW_RECEIVED()                                (g_bIRReceived = _TRUE)
#define CLR_IR_HW_RECEIVED()                                (g_bIRReceived = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#endif
