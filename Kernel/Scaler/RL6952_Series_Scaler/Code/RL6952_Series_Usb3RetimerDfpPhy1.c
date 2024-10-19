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
// ID Code      : RL6952_Series_Usb3RetimerDfpPhy1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_USB3RETIMERDFPPHY1__

#include "ScalerFunctionInclude.h"
#include "Usb3RetimerMac1/ScalerUsb3RetimerMac1.h"

#if(_USB3_RETIMER_DFP_PHY1_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : USB3 Rx1 Retimer DFP PHY Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy1Initial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer DFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy1Disable(void)
{
    ScalerUsb3RetimerDfpPhy1PhyDisable();
    ScalerUsb3RetimerDfpPhy1IrqDisable();
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer DFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy1PhyDisable(void)
{
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer DFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy1IrqDisable(void)
{
}

#endif // End of #if(_USB3_RETIMER_DFP_PHY1_SUPPORT == _ON)
