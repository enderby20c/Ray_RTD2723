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
// ID Code      : ScalerTmdsPhyRx4.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TMDS_PHY_RX4_H__
#define __SCALER_TMDS_PHY_RX4_H__


#if(_TMDS_PHY_RX4_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucTmdsPhyRx4Tap0Init;
extern WORD g_usTmdsPhyRx4ExDataRate;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTmdsPhyRx4SetDFEInitial_EXINT0(void);
extern void ScalerTmdsPhyRx4FrlSetDFEInitial_EXINT0(void);
extern void ScalerTmdsPhyRx4SetDFEInitial(void);
extern void ScalerTmdsPhyRx4FrlSetDFEInitial(void);
#endif // End of #if(_TMDS_PHY_RX4_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_TMDS_PHY_RX4_H__
