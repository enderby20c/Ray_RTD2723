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
// ID Code      : ScalerGDIPhyRx2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_GDIPHY_RX2_H__
#define __SCALER_GDIPHY_RX2_H__

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
#if((_TMDS_PHY_RX2_SUPPORT == _ON) || (_DP_PHY_RX2_SUPPORT == _ON))
extern void ScalerGDIPhyRx2Z0Switch(bit bSelect);
extern void ScalerGDIPhyRx2DigitalPhySwitch(void);
#endif // End of #if((_TMDS_PHY_RX2_SUPPORT == _ON) || (_DP_PHY_RX2_SUPPORT == _ON))


#endif // End of #ifndef __SCALER_GDIPHY_RX2_H__
