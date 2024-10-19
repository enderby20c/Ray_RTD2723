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
// ID Code      : ScalerDpAuxRx_T2INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpAuxRx/ScalerDpAuxRx.h"




#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Backup Aux Request in Timer2 Interupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRxDpcdIrqProtect_T2INT(void)
{
#if(_DP_AUX_RX0_SUPPORT == _ON)
    ScalerDpAuxRx0DpcdIrqProtect_T2INT();
#endif
#if(_DP_AUX_RX1_SUPPORT == _ON)
    ScalerDpAuxRx1DpcdIrqProtect_T2INT();
#endif
#if(_DP_AUX_RX2_SUPPORT == _ON)
    ScalerDpAuxRx2DpcdIrqProtect_T2INT();
#endif
}
#endif
#endif
