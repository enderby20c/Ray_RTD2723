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
// ID Code      : ScalerDpAuxTx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_AUX_TX_H__
#define __SCALER_DP_AUX_TX_H__

#if(_DP_PHY_TX_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DP_AUX_TX_NATIVE_WRITE                     0x80
#define _DP_AUX_TX_NATIVE_READ                      0x90
#define _DP_AUX_TX_I2C_WRITE                        0x40
#define _DP_AUX_TX_I2C_READ                         0x50


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
extern BYTE g_ucDpAuxTxPVth;
extern BYTE g_ucDpAuxTxNVth;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerDpAuxTxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDpAuxTxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
extern void ScalerDpAuxTxAutoCalibration(void);
#endif

#endif // End of #if(_DP_PHY_TX_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_DP_AUX_TX_H__
