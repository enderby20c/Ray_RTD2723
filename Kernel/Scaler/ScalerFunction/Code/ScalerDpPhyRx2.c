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
// ID Code      : ScalerDpPhyRx2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPPHYRX2__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx2/ScalerDpPhyRx2.h"

#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX2_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructDpLanesMapping g_stDpPhyRx2LanesMapping;
BYTE g_pucDpPhyRx2LE[4];
WORD g_pusDpPhyRx2ClockTarget[4];
WORD g_usDpPhyRx2VCOBandDiff;
BYTE g_ucDpPhyRx2CtsCtrl;

volatile StructDpPhyRxIcpKp g_stDpPhyRx2IcpKp;
volatile StructDpPhyRxIcp g_stDpPhyRx2Icp;
volatile StructDpPhyRxKvco g_stDpPhyRx2Kvco;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#endif // End of #if(_DP_PHY_RX2_SUPPORT == _ON)
