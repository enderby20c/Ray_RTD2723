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
// ID Code      : ScalerHdmiArcTx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIARCTX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "HdmiArcTx/ScalerHdmiArcTx.h"

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
//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx High Priority Interrupt Handler (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxHighIntHandler_EXINT0(EnumPowerStatus enumPowerStatus)
{
    if((enumPowerStatus != _POWER_STATUS_SAVING) && (enumPowerStatus != _POWER_STATUS_OFF))
    {
        // cs_in_atype_chg_flag irq
        if((ScalerGetByte_EXINT(PE5_13_SPDIF_IN_CH_STATUS_CTRL_1) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // clear cs_in_atype_chg_flag
            ScalerSetBit_EXINT(PE5_13_SPDIF_IN_CH_STATUS_CTRL_1, ~(_BIT1 | _BIT0), _BIT1);

            // pop out channel status
            ScalerSetBit_EXINT(PE5_10_SPDIF_IN_CH_STATUS_CTRL_0, ~(_BIT3 | _BIT2), _BIT2);

            SET_HDMI_ARC_TX_SOURCE_CH_STATUS_CHANGE_EVENT();
        }

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
        // eARC discovery success
        if((ScalerGetByte_EXINT(PE5_B6_EARC_TX_CMDC_DISC_CTRL_2) & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear eARC discovery flag and protect BIT5,3,1
            ScalerSetBit_EXINT(PE5_B6_EARC_TX_CMDC_DISC_CTRL_2, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

            SET_HDMI_ARC_TX_EARC_DISCOVERY_EVENT();
        }

        // eARC lost heartbeat
        if((ScalerGetByte_EXINT(PE5_B6_EARC_TX_CMDC_DISC_CTRL_2) & (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
        {
            // Clear eARC host heartbeat flag and protect BIT7,3,1
            ScalerSetBit_EXINT(PE5_B6_EARC_TX_CMDC_DISC_CTRL_2, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT5);

            SET_HDMI_ARC_TX_EARC_LOST_HEARTBEAT_EVENT();
        }

        // eARC dicovery timeout
        if((ScalerGetByte_EXINT(PE5_B7_EARC_TX_CMDC_DISC_CTRL_3) & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear eARC discovery timeout flag and protect BIT7
            ScalerSetBit_EXINT(PE5_B7_EARC_TX_CMDC_DISC_CTRL_3, ~_BIT7, _BIT7);

            ScalerHdmiArcTxPhyEarcDiffDrivingPower_EXINT0(_OFF);
            ScalerHdmiArcTxPhyEarcCmDrivingPower_EXINT0(_OFF);

            // Enable eARC Discovery Related IRQ
            ScalerSetBit_EXINT(PE5_B6_EARC_TX_CMDC_DISC_CTRL_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1));
            ScalerSetBit_EXINT(PE5_B7_EARC_TX_CMDC_DISC_CTRL_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Disable eARC Rx Heartbeat Status Change IRQ
            ScalerSetBit_EXINT(PE5_C6_EARC_TX_HEARTBEAT_CTRL_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

            // disable CMDC
            ScalerSetBit_EXINT(PE5_B4_EARC_TX_CMDC_DISC_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

            SET_HDMI_ARC_TX_EARC_DISC_TIMEOUT_EVENT();
        }

        // eARC Heartbeat Rx audio latency status change
        if((ScalerGetByte_EXINT(PE5_C6_EARC_TX_HEARTBEAT_CTRL_1) & (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // Clear audio latency status change flag and protect BIT7,5,1
            ScalerSetBit_EXINT(PE5_C6_EARC_TX_HEARTBEAT_CTRL_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT3);

            SET_HDMI_ARC_TX_EARC_AUDIO_LATENCY_CHANGE_EVENT();
        }

        // eARC Heartbeat Rx capability data structure change
        if((ScalerGetByte_EXINT(PE5_C6_EARC_TX_HEARTBEAT_CTRL_1) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // Clear capability data structure change flag and protect BIT7,3,1
            ScalerSetBit_EXINT(PE5_C6_EARC_TX_HEARTBEAT_CTRL_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT1);

            SET_HDMI_ARC_TX_EARC_CDS_CHANGE_EVENT();
        }
#endif // End of #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Low Priority Interrupt Handler (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxLowIntHandler_EXINT0(EnumPowerStatus enumPowerStatus)
{
    if((enumPowerStatus != _POWER_STATUS_SAVING) && (enumPowerStatus != _POWER_STATUS_OFF))
    {
        return;
    }
}

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Start Discovery (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxEarcStartDiscovery_EXINT0(void)
{
    CLR_HDMI_ARC_TX_EARC_AUDIO_LATENCY_CHANGE_EVENT();
    CLR_HDMI_ARC_TX_EARC_CDS_CHANGE_EVENT();
    CLR_HDMI_ARC_TX_EARC_LOST_HEARTBEAT_EVENT();
    CLR_HDMI_ARC_TX_EARC_DISC_TIMEOUT_EVENT();
    CLR_HDMI_ARC_TX_EARC_DISCOVERY_EVENT();

    ScalerHdmiArcTxPhyEarcCmDrivingPower_EXINT0(_ON);

    // Enable CM Tx module
    ScalerSetBit_EXINT(PE5_B4_EARC_TX_CMDC_DISC_CTRL_0, ~_BIT7, _BIT7);

    // Enable eARC Discovery Related IRQ
    ScalerSetBit_EXINT(PE5_B6_EARC_TX_CMDC_DISC_CTRL_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1));
    ScalerSetBit_EXINT(PE5_B7_EARC_TX_CMDC_DISC_CTRL_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Enable eARC Rx Heartbeat Status Change IRQ
    ScalerSetBit_EXINT(PE5_C6_EARC_TX_HEARTBEAT_CTRL_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Start eARC Discovery
    ScalerSetBit_EXINT(PE5_B4_EARC_TX_CMDC_DISC_CTRL_0, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Reset Discovery (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxEarcResetDiscovery_EXINT0(void)
{
    ScalerHdmiArcTxPhyEarcDiffDrivingPower_EXINT0(_OFF);
    ScalerHdmiArcTxPhyEarcCmDrivingPower_EXINT0(_OFF);

    // disable CMDC
    ScalerSetBit_EXINT(PE5_B4_EARC_TX_CMDC_DISC_CTRL_0, ~(_BIT7 | _BIT6), 0x00);

    // Disable eARC Discovery Related IRQ
    ScalerSetBit_EXINT(PE5_B6_EARC_TX_CMDC_DISC_CTRL_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PE5_B7_EARC_TX_CMDC_DISC_CTRL_3, ~(_BIT7 | _BIT6), _BIT7);

    // Disable eARC Rx Heartbeat Status Change IRQ
    ScalerSetBit_EXINT(PE5_C6_EARC_TX_HEARTBEAT_CTRL_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
}
#endif // End of #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
#endif // End of #if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
