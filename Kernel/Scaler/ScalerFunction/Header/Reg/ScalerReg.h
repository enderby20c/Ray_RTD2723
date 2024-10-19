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
// ID Code      : ScalerReg.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_REG_H__
#define __SCALER_REG_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _NUM_FONT_WIDTH_4_SERIAL                3


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerBurstWriteTimeoutCal(void);

extern BYTE ScalerEnableAccessPort(WORD usAddr, BYTE ucValue);
extern void ScalerDisableAccessPort(WORD usAddr);

extern BYTE ScalerEnableAccessPort_EXINT0(WORD usAddr, BYTE ucValue);
extern void ScalerDisableAccessPort_EXINT0(WORD usAddr);



#endif // End of #ifndef __SCALER_REG_H__
