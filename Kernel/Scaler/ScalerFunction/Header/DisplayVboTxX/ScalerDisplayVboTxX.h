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
// ID Code      : ScalerDisplayVboTxX.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DISPLAY_VBO_TXX_H__
#define __SCALER_DISPLAY_VBO_TXX_H__

#if(_PANEL_STYLE == _PANEL_VBO)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayVboTxXMac(bit bOn);
extern void ScalerDisplayVboTxXDphy(bit bOn);
extern void ScalerDisplayVboTxXCdr2AlnLatency(void);
extern void ScalerDisplayVboTxXCtsFifoHandler(void);
extern void ScalerDisplayVboTxXDrivingControl(BYTE ucDrvLane, BYTE ucEmpLane);
extern void ScalerDisplayVboTxXDataSel(void);
extern void ScalerDisplayVboTxXPLL(bit bOn);
extern void ScalerDisplayVboTxXPower(bit bOn);
extern void ScalerDisplayVboTxXSetZ0(void);
#endif


#endif // End of #ifndef __SCALER_DISPLAY_VBO_TXX_H__
