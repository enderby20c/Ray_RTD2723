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
// ID Code      : ScalerUsb3RedriverMac1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Usb3RedriverMac1/ScalerUsb3RedriverMac1.h"

#if(_USB3_REDRIVER_MAC1_SUPPORT == _ON)

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
// Description  : USB3 Rx1 Redriver Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac1Initial(void)
{
    // Redriver Mac1 Initial
    ScalerUsb3RedriverMac1UfpInitial();
    ScalerUsb3RedriverMac1DfpInitial();
}

//--------------------------------------------------
// Description  : USB3 Rx1 Redriver UFP Mac Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac1UfpInitial(void)
{
    // Rx detection priority high in Rx.detect
    ScalerSetBit(P98_27_RTSSM_CONTROL_U_01, ~_BIT2, _BIT2);

    // Adjust EQ Training time to Max.
    ScalerSetByte(P98_3B_TIMER_VALUE_U_05, 0xFF);

    // Adjust Polling.waitEQ --> U2_U3 timer to 3ms
    ScalerSetBit(P98_35_TIMER_UNIT_U_01, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte(P98_3C_TIMER_VALUE_U_06, 0x03);

    // Turn on Compliance mode both side
    ScalerSetBit(P98_20_GLOBAL_SETTING, ~_BIT3, _BIT3);

    // Avoid Enter Compliance mode in normal case
    ScalerSetByte(P98_68_POLLING_LFPS_U_08, 0x04);
    ScalerSetBit(P98_20_GLOBAL_SETTING, ~_BIT2, _BIT2);

    // Adjust tu0u1 EI Timer to 10ms
    ScalerSetByte(P98_A2_TIMER_D_03, 0x0A);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Redriver DFP Mac Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac1DfpInitial(void)
{
    // Rx detection priority high in Rx.detect
    ScalerSetBit(P98_93_RTSSM_CONTROL_D, ~_BIT3, _BIT3);

    ScalerSetBit(P98_35_TIMER_UNIT_U_01, ~(_BIT5 | _BIT4), _BIT4);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Redriver Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac1Enable(bit bEnable)
{
    ScalerUsb3RedriverMac1IrqEnable(bEnable);
    ScalerUsb3RedriverMac1MacEnable(bEnable);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Redriver Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac1MacEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable UFP/DFP Timer Block
        ScalerSetBit(P98_30_TIMER_U, ~(_BIT7 | _BIT4 | _BIT2), (_BIT4 | _BIT2));
        ScalerSetBit(P98_A0_TIMER_D_01, ~_BIT7, 0x00);

        // Enable UFP/DFP LFPS Block
        ScalerSetBit(P98_60_LFPS_GLOBAL_SETTING_U, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));
        ScalerSetBit(P98_C0_LFPS_GLOBAL_SETTING_D, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));

        // Enable UFP/DFP Polling.LFPS Detect
        ScalerSetBit(P98_61_POLLING_LFPS_U_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P98_C1_POLLING_LFPS_D_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable UFP/DFP LBPM Detect
        ScalerSetBit(P98_70_LBPM_U_01, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
        ScalerSetBit(P98_D0_LBPM_D_01, ~(_BIT7 | _BIT3 | _BIT1), (_BIT7 | _BIT3 | _BIT1));

        // Enable UFP Warm Reset Detect
        ScalerSetBit(P98_6C_WARM_RESET_U_01, ~_BIT7, _BIT7);

        // Enable DFP Ping.LFPS Detect
        ScalerSetBit(P98_E0_PING_LFPS_DET_D_01, ~_BIT7, _BIT7);

        // Enable UFP/DFP RTSSM
        ScalerSetBit(P98_20_GLOBAL_SETTING, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Enable Redriver Mac
        ScalerSetBit(P98_20_GLOBAL_SETTING, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Redriver Mac
        ScalerSetBit(P98_20_GLOBAL_SETTING, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : USB3 Rx1 Redriver Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac1IrqEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Turn on Compliance mode state INT
        ScalerSetBit(P98_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT5 | _BIT3 | _BIT2));
    }
    else
    {
        // Disable RTSSM Polling.RxEQ INT
        ScalerSetBit(P98_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT5 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : USB3 Rx1 Redriver INT Handler
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac1IntHandler_EXINT3(void)
{
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(_RX1);
#endif
    // Compliance mode state INT
    if(ScalerGetBit_EXINT3(P98_2B_RTSSM_IRQ_U_03, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
#if(_USB3_REPEATER_PHY_SUPPORT == _ON)
        ScalerUsb3RepeaterPhyEnterComplianceMode_EXINT3(enumTypeCPcbPort);
#endif
        // Turn off Compliance mode state INT
        ScalerSetBit_EXINT3(P98_2B_RTSSM_IRQ_U_03, ~(_BIT3 | _BIT2), _BIT3);

        // Turn on Rx.detect state INT
        ScalerSetBit_EXINT3(P98_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }

    // Rx.detect INT
    if(ScalerGetBit_EXINT3(P98_2A_RTSSM_IRQ_U_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
#if(_USB3_REPEATER_PHY_SUPPORT == _ON)
        ScalerUsb3RepeaterPhyExitComplianceMode_EXINT3(enumTypeCPcbPort);
#endif
        // Turn off Rx.detect state INT
        ScalerSetBit_EXINT3(P98_2A_RTSSM_IRQ_U_02, ~(_BIT7 | _BIT6), _BIT7);

        // Turn on Compliance mode state INT
        ScalerSetBit_EXINT3(P98_2B_RTSSM_IRQ_U_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }
}

#endif // End of #if(_USB3_REDRIVER_MAC1_SUPPORT == _ON)
