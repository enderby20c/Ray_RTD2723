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
// ID Code      : ScalerUsb3RetimerMac1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Usb3RetimerMac1/ScalerUsb3RetimerMac1.h"

#if(_USB3_RETIMER_MAC1_SUPPORT == _ON)

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
// Description  : USB3 Rx1 Retimer Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac1Initial(void)
{
    // Retimer Mac1 Initial
    ScalerUsb3RetimerMac1UfpMacInitial();
    ScalerUsb3RetimerMac1DfpMacInitial();
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP Mac Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac1UfpMacInitial(void)
{
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer DFP Mac Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac1DfpMacInitial(void)
{
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac1Enable(bit bEnable)
{
    ScalerUsb3RetimerMac1IrqEnable(bEnable);
    ScalerUsb3RetimerMac1MacEnable(bEnable);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac1MacEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
    }
    else
    {
    }
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac1IrqEnable(bit bEnable)
{
    bEnable = bEnable;
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer INT Handler
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac1IntHandler_EXINT3(void)
{
}

#endif // End of #if(_USB3_RETIMER_MAC1_SUPPORT == _ON)
