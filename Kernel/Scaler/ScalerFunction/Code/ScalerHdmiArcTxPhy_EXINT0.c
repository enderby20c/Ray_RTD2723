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
// ID Code      : ScalerHdmiArcTxPhy_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIARCTXPHY_EXINT0__

#include "ScalerFunctionInclude.h"
#include "HdmiArcTxPhy/ScalerHdmiArcTxPhy.h"

#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Phy Common Mode Driving Power (EXINT0 Only)
// Input Value  : bOnOff
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyEarcCmDrivingPower_EXINT0(bit bOnOff)
{
    if(bOnOff == _ON)
    {
        // enable cm driver
        ScalerSetBit_EXINT(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT5, _BIT5);
    }
    else
    {
        // disable cm driver
        ScalerSetBit_EXINT(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : bOnOff HDMI eARC Tx Phy Differential Mode Driving Power (EXINT0 Only)
// Input Value  : bOnOff
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyEarcDiffDrivingPower_EXINT0(bit bOnOff)
{
    if(bOnOff == _ON)
    {
        // enable df driver
        ScalerSetBit_EXINT(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT4, _BIT4);
    }
    else
    {
        // set Tx phy to eARC Mode(Disable ARC output)
        ScalerSetBit_EXINT(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT7, _BIT7);

        // disable df driver
        ScalerSetBit_EXINT(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT4, 0x00);
    }
}
#endif // End of #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
#endif // End of #if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
