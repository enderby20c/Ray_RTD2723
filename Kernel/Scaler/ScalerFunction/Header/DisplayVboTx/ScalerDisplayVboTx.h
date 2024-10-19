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
// ID Code      : ScalerDisplayVboTx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DISPLAY_VBO_TX_H__
#define __SCALER_DISPLAY_VBO_TX_H__

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
extern void ScalerDisplayVboTxSetLocknInterrupt(bit bEnable);
extern void ScalerDisplayVboTxSetUnLocknInterrupt(bit bEnable);
extern bit ScalerDisplayVboTxHpdnStatus(void);
extern bit ScalerDisplayVboTxLocknStatus(void);
extern bit ScalerDisplayVboTxGetLocknVoltageLevel(void);
extern bit ScalerDisplayVboTxAlnPatternStatus(void);

extern bit ScalerDisplayVboTxLockDetect_EXINT0(void);
extern bit ScalerDisplayVboTxLockStatus_EXINT0(void);
extern bit ScalerDisplayVboTxUnLockDetect_EXINT0(void);
extern void ScalerDisplayVboTxPhyPowerDomainEnable(EnumPowerCut enumPowerCut);
#endif


#endif // End of #ifndef __SCALER_DISPLAY_VBO_TX_H__
