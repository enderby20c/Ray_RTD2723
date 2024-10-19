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
// ID Code      : ScalerDpPhyRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPPHYRX1__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx1/ScalerDpPhyRx1.h"

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX1_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructDpLanesMapping g_stDpPhyRx1LanesMapping;
BYTE g_pucDpPhyRx1LE[4];
WORD g_pusDpPhyRx1ClockTarget[4];
WORD g_pusDpPhyRx1ClockCDR[4];
WORD g_usDpPhyRx1VCOBandDiff;
BYTE g_ucDpPhyRx1CtsCtrl;

volatile StructDpPhyRxIcpKp g_stDpPhyRx1IcpKp;
volatile StructDpPhyRxIcp g_stDpPhyRx1Icp;
volatile StructDpPhyRxKvco g_stDpPhyRx1Kvco;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#endif // End of #if(_DP_PHY_RX1_SUPPORT == _ON)
