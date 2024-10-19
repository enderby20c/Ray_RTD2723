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
// ID Code      : ScalerDpPhyRx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPPHYRX0__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx0/ScalerDpPhyRx0.h"

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX0_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructDpLanesMapping g_stDpPhyRx0LanesMapping;
BYTE g_pucDpPhyRx0LE[4];
WORD g_pusDpPhyRx0ClockTarget[4];
WORD g_usDpPhyRx0VCOBandDiff;
BYTE g_ucDpPhyRx0CtsCtrl;

volatile StructDpPhyRxIcpKp g_stDpPhyRx0IcpKp;
volatile StructDpPhyRxIcp g_stDpPhyRx0Icp;
volatile StructDpPhyRxKvco g_stDpPhyRx0Kvco;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#endif // End of #if(_DP_PHY_RX0_SUPPORT == _ON)
