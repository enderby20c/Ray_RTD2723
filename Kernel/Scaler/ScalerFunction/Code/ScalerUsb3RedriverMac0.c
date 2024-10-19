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
// ID Code      : ScalerUsb3RedriverMac0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Usb3RedriverMac0/ScalerUsb3RedriverMac0.h"

#if(_USB3_REDRIVER_MAC0_SUPPORT == _ON)

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
// Description  : USB3 Rx0 Redriver Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac0Initial(void)
{
    // Redriver Mac0 Initial
    ScalerUsb3RedriverMac0UfpInitial();
    ScalerUsb3RedriverMac0DfpInitial();
}

//--------------------------------------------------
// Description  : USB3 Rx0 Redriver UFP Mac Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac0UfpInitial(void)
{
    // Rx detection priority high in Rx.detect
    ScalerSetBit(P86_27_RTSSM_CONTROL_U_01, ~_BIT2, _BIT2);

    // Adjust EQ Training time to Max.
    ScalerSetByte(P86_3B_TIMER_VALUE_U_05, 0xFF);

    // Adjust Polling.waitEQ --> U2_U3 timer to 3ms
    ScalerSetBit(P86_35_TIMER_UNIT_U_01, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte(P86_3C_TIMER_VALUE_U_06, 0x03);

    // Turn on Compliance mode both side
    ScalerSetBit(P86_20_GLOBAL_SETTING, ~_BIT3, _BIT3);

    // Avoid Enter Compliance mode in normal case
    ScalerSetByte(P86_68_POLLING_LFPS_U_08, 0x04);
    ScalerSetBit(P86_20_GLOBAL_SETTING, ~_BIT2, _BIT2);

    // Adjust tu0u1 EI Timer to 10ms
    ScalerSetByte(P86_A2_TIMER_D_03, 0x0A);
}

//--------------------------------------------------
// Description  : USB3 Rx0 Redriver DFP Mac Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac0DfpInitial(void)
{
    // Rx detection priority high in Rx.detect
    ScalerSetBit(P86_93_RTSSM_CONTROL_D, ~_BIT3, _BIT3);

    ScalerSetBit(P86_35_TIMER_UNIT_U_01, ~(_BIT5 | _BIT4), _BIT4);
}

//--------------------------------------------------
// Description  : USB3 Rx0 Redriver Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac0Enable(bit bEnable)
{
    ScalerUsb3RedriverMac0IrqEnable(bEnable);
    ScalerUsb3RedriverMac0MacEnable(bEnable);
}

//--------------------------------------------------
// Description  : USB3 Rx0 Redriver Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac0MacEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable UFP/DFP Timer Block
        ScalerSetBit(P86_30_TIMER_U, ~(_BIT7 | _BIT4 | _BIT2), (_BIT4 | _BIT2));
        ScalerSetBit(P86_A0_TIMER_D_01, ~_BIT7, 0x00);

        // Enable UFP/DFP LFPS Block
        ScalerSetBit(P86_60_LFPS_GLOBAL_SETTING_U, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));
        ScalerSetBit(P86_C0_LFPS_GLOBAL_SETTING_D, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));

        // Enable UFP/DFP Polling.LFPS Detect
        ScalerSetBit(P86_61_POLLING_LFPS_U_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P86_C1_POLLING_LFPS_D_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable UFP/DFP LBPM Detect
        ScalerSetBit(P86_70_LBPM_U_01, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
        ScalerSetBit(P86_D0_LBPM_D_01, ~(_BIT7 | _BIT3 | _BIT1), (_BIT7 | _BIT3 | _BIT1));

        // Enable UFP Warm Reset Detect
        ScalerSetBit(P86_6C_WARM_RESET_U_01, ~_BIT7, _BIT7);

        // Enable DFP Ping.LFPS Detect
        ScalerSetBit(P86_E0_PING_LFPS_DET_D_01, ~_BIT7, _BIT7);

        // Enable UFP/DFP RTSSM
        ScalerSetBit(P86_20_GLOBAL_SETTING, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Enable Redriver Mac
        ScalerSetBit(P86_20_GLOBAL_SETTING, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Redriver Mac
        ScalerSetBit(P86_20_GLOBAL_SETTING, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : USB3 Rx0 Redriver Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac0IrqEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_HW_USB3_REPEATER_PHY_DFP_MUX_TYPE == _USB3_REPEATER_PHY_DFP_MUX_EMBEDDED)
        // Enable Wait EQ INT and Rx.detect state INT
        ScalerSetBit(P86_2A_RTSSM_IRQ_U_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1));
#else
        // Turn on Compliance mode state INT
        ScalerSetBit(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT5 | _BIT3 | _BIT2));
#endif
    }
    else
    {
#if(_HW_USB3_REPEATER_PHY_DFP_MUX_TYPE == _USB3_REPEATER_PHY_DFP_MUX_EMBEDDED)
        // Disable Wait EQ INT and Rx.detect state INT
        ScalerSetBit(P86_2A_RTSSM_IRQ_U_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

        // Disable U0_U1 INT
        ScalerSetBit(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), (_BIT7 | _BIT5 | _BIT3));
#else
        // Disable RTSSM Polling.RxEQ INT
        ScalerSetBit(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT5 | _BIT3));
#endif
    }
}

//--------------------------------------------------
// Description  : USB3 Rx0 Redriver INT Handler
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RedriverMac0IntHandler_EXINT3(void)
{
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(_RX0);
#endif
    // Compliance mode state INT
    if(ScalerGetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
#if(_USB3_REPEATER_PHY_SUPPORT == _ON)
        ScalerUsb3RepeaterPhyEnterComplianceMode_EXINT3(enumTypeCPcbPort);
#endif
        // Turn off Compliance mode state INT
        ScalerSetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2), _BIT3);

        // Turn on Rx.detect state INT
        ScalerSetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), (_BIT7 | _BIT6));
    }

#if(_HW_USB3_REPEATER_PHY_DFP_MUX_TYPE == _USB3_REPEATER_PHY_DFP_MUX_EMBEDDED)
    // Phy Ready Received INT
    if(ScalerGetBit_EXINT3(P86_70_LBPM_U_01, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Check Phy Rate 10G case
        if(ScalerGetBit_EXINT3(P86_53_PIPE_CONTROL_U_04, _BIT7) == _BIT7)
        {
        }

        // Turn off Phy Ready Received INT
        ScalerSetBit_EXINT3(P86_70_LBPM_U_01, ~(_BIT1 | _BIT0), _BIT1);

        // Turn on Rx.detect state INT
        ScalerSetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), (_BIT7 | _BIT6));
    }
#endif

    // Rx.detect INT
    if(ScalerGetBit_EXINT3(P86_2A_RTSSM_IRQ_U_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
#if(_USB3_REPEATER_PHY_SUPPORT == _ON)
        ScalerUsb3RepeaterPhyExitComplianceMode_EXINT3(enumTypeCPcbPort);
#endif
        // Turn off Rx.detect state INT
        ScalerSetBit_EXINT3(P86_2A_RTSSM_IRQ_U_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT7);

        // Turn on Compliance mode state INT
        ScalerSetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_HW_USB3_REPEATER_PHY_DFP_MUX_TYPE == _USB3_REPEATER_PHY_DFP_MUX_EMBEDDED)

        // Turn on Phy Ready Received INT
        ScalerSetBit_EXINT3(P86_70_LBPM_U_01, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
#endif
    }

#if(_HW_USB3_REPEATER_PHY_DFP_MUX_TYPE == _USB3_REPEATER_PHY_DFP_MUX_EMBEDDED)
    // Wait EQ INT
    if(ScalerGetBit_EXINT3(P86_2A_RTSSM_IRQ_U_02, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        // Disable Wait EQ INT
        ScalerSetBit_EXINT3(P86_2A_RTSSM_IRQ_U_02, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        // Enable U0_U1 INT
        ScalerSetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), _BIT6);

        // Clear U0_U1 INT Flag
        ScalerSetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT5 | _BIT3), _BIT7);
    }

    // U0_U1 INT
    if(ScalerGetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // Disable U0_U1 INT
        ScalerSetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), 0x00);

        // Clear IRQ Flag
        ScalerSetBit_EXINT3(P86_2B_RTSSM_IRQ_U_03, ~(_BIT7 | _BIT5 | _BIT3), _BIT7);

        // Enable Wait EQ INT
        ScalerSetBit_EXINT3(P86_2A_RTSSM_IRQ_U_02, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        // Clear Wait EQ INT Flag
        ScalerSetBit_EXINT3(P86_2A_RTSSM_IRQ_U_02, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT3);
    }
#endif
}
#endif // End of #if(_USB3_REDRIVER_MAC0_SUPPORT == _ON)
