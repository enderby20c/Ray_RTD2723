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
// ID Code      : ScalerGDIPhyRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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



#if((_TMDS_PHY_RX1_SUPPORT == _ON) || (_DP_PHY_RX1_SUPPORT == _ON) || (_USB3_UFP_PHY1_SUPPORT == _ON))
extern void ScalerGDIPhyRx1PowerProc(EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRx1Power(EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRx1LaneMode(EnumLaneConfig enumLaneMode, BYTE ucLane);
extern void ScalerGDIPhyRx1LanePower(bit bEnable, BYTE ucLane);
#endif


