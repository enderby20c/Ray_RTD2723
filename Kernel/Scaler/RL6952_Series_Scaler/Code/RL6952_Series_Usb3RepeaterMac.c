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
// ID Code      : RL6952_Series_Usb3RepeaterMac.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_USB3_REPEATER_MAC__

#include "ScalerFunctionInclude.h"
#include "Usb3RepeaterMac/ScalerUsb3RepeaterMac.h"

#if(_USB3_REPEATER_MAC_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_USB3_RETIMER_MAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : USB3 BLR Path Support based on ID code (RL6952 Shall Be _ON)
// Input Value  : NA
// Output Value : _ON, _OFF
//--------------------------------------------------
bit ScalerUsb3RepeaterMacBlrPathSupport(void)
{
    return _ON;
}
#endif // end of #if(_USB3_RETIMER_MAC_SUPPORT == _ON)

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
//--------------------------------------------------
// Description  : USB3 Repeater MAC Mux Switch Control
// Input Value  : enumTypeCPcbPort , enumUSBHubPathEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterMacMuxSwitchControl(EnumInputPort enumInputPort, EnumUSBHubPathEnable enumUSBHubPathEnable)
{
    switch(enumInputPort)
    {
#if((_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))
        case _D0_INPUT_PORT:

            if(enumUSBHubPathEnable == _USB_PATH_ENABLE)
            {
                // Retimer Select UFP PIPE From D0
                // 0x3B07[7] = 1'b0
                ScalerSetBit(P3B_07_RTSSM_GLOBAL_07, ~(_BIT7), 0x00);

                DebugMessageTypeC("9. [USB] MAC Switch to D0 Input Port", enumInputPort);
            }

            break;
#endif // End of #if((_D0_USB_HUB_TYPE != _USB_NONE) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))

#if((_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))
        case _D1_INPUT_PORT:

            if(enumUSBHubPathEnable == _USB_PATH_ENABLE)
            {
                // Retimer Select UFP PIPE From D1
                // 0x3B07[7] = 1'b1
                ScalerSetBit(P3B_07_RTSSM_GLOBAL_07, ~(_BIT7), _BIT7);

                DebugMessageTypeC("9. [USB] MAC Switch to D1 Input Port", enumInputPort);
            }

            break;
#endif // End of #if((_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : USB3 Repeater UfpPhyx mapping to Macx
// Input Value  : UfpPhyx
// Output Value : Macx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterMacUfpPhyx2MacxMapping(EnumRx enumUfpPhyxIndex)
{
    EnumRx enumMacxIndex = _RX_MAP_NONE;

    switch(enumUfpPhyxIndex)
    {
        case _RX0:

            if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
                enumMacxIndex = _RX0;
            }

            break;

        case _RX1:

            if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == _BIT7)
            {
                enumMacxIndex = _RX0;
            }

            break;

        case _RX2:

            break;

        default:

            break;
    }

    return enumMacxIndex;
}

//--------------------------------------------------
// Description  : USB3 Repeater UfpPhyx mapping to Macx
// Input Value  : UfpPhyx
// Output Value : Macx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterMacUfpPhyx2MacxMapping_EXINT3(EnumRx enumUfpPhyxIndex)
{
    EnumRx enumMacxIndex = _RX_MAP_NONE;

    switch(enumUfpPhyxIndex)
    {
        case _RX0:

            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
                enumMacxIndex = _RX0;
            }

            break;

        case _RX1:

            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == _BIT7)
            {
                enumMacxIndex = _RX0;
            }

            break;

        case _RX2:

            break;

        default:

            break;
    }

    return enumMacxIndex;
}

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Description  : USB3 Repeater Power Cut ON FW Mode Setting Process
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RepeaterMacPowerCutOnProcess_EXINT3(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(_RX0);

    //=================================
    // P3 Power Cut ON Register Setting
    //=================================
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
        // case _POWER_CUT_GROUP_RX0_DP20_U32_APHY :
        // Analog isolation on
        ScalerSetBit_EXINT3(P40_41_VCCKOFF_CONTROL41, ~_BIT0, 0x00);

        // Digital power off
        ScalerSetBit_EXINT3(P6F_60_PD1_POWER_CTRL, ~_BIT7, _BIT7);

        DELAY_10US_EXINT();
#endif
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
#if(_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
        // case _POWER_CUT_GROUP_RX1_DP20_U32_APHY :
        // Analog isolation on
        ScalerSetBit_EXINT3(P40_42_VCCKOFF_CONTROL42, ~_BIT0, 0x00);

        // Digital power off
        ScalerSetBit_EXINT3(P6F_65_PD6_POWER_CTRL, ~_BIT7, _BIT7);

        DELAY_10US_EXINT();
#endif
    }

    // case _POWER_CUT_GROUP_USB_UFP_RETIMER_MAC:
    // Digital isolation on
    ScalerSetBit_EXINT3(P6F_8C_PD121_POWER_CTRL, ~_BIT1, _BIT1);

    // Digital power off
    ScalerSetBit_EXINT3(P6F_8C_PD121_POWER_CTRL, ~_BIT5, _BIT5);

    DELAY_10US_EXINT();

    // case _POWER_CUT_GROUP_USB_DFP_RETIMER_MAC:
    // Digital isolation on
    ScalerSetBit_EXINT3(P6F_8D_PD122_POWER_CTRL, ~_BIT1, _BIT1);

    // Digital power off
    ScalerSetBit_EXINT3(P6F_8D_PD122_POWER_CTRL, ~_BIT5, _BIT5);

    DELAY_10US_EXINT();

    // case _POWER_CUT_GROUP_USB_DFP_DPHY:
    // Digital isolation on
    ScalerSetBit_EXINT3(P6F_27_PD32_POWER_CTRL, ~_BIT1, _BIT1);

    // Digital power off
    ScalerSetBit_EXINT3(P6F_27_PD32_POWER_CTRL, ~_BIT5, _BIT5);

    DELAY_10US_EXINT();

    // case _POWER_CUT_GROUP_USB32_DFP_APHY:
    // Analog isolation on
    ScalerSetBit_EXINT3(P40_4C_VCCKOFF_CONTROL4C, ~_BIT0, 0x00);

    // Digital to analog isolation on
    ScalerSetBit_EXINT3(P6F_72_PD93_POWER_CTRL, ~_BIT1, _BIT1);

    // High voltage power off
    ScalerSetBit_EXINT3(P6F_72_PD93_POWER_CTRL, ~_BIT7, _BIT7);

    // Low voltage analog power off
    ScalerSetBit_EXINT3(P6F_72_PD93_POWER_CTRL, ~_BIT6, _BIT6);

    // Low voltage digital power off
    ScalerSetBit_EXINT3(P6F_72_PD93_POWER_CTRL, ~_BIT5, _BIT5);

    DELAY_10US_EXINT();
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Repeater Power Cut OFF FW Mode Setting Process
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RepeaterMacPowerCutOffProcess_EXINT3(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(_RX0);

    //=================================
    // P3 Power Cut OFF Register Setting
    //=================================
    // case _POWER_CUT_GROUP_USB32_DFP_APHY:
    // Low voltage digital power on
    ScalerSetBit_EXINT3(P6F_72_PD93_POWER_CTRL, ~_BIT5, 0x00);

    // Low voltage analog power on
    ScalerSetBit_EXINT3(P6F_72_PD93_POWER_CTRL, ~_BIT6, 0x00);

    // High voltage power on
    ScalerSetBit_EXINT3(P6F_72_PD93_POWER_CTRL, ~_BIT7, 0x00);

    // Digital to analog isolation off
    ScalerSetBit_EXINT3(P6F_72_PD93_POWER_CTRL, ~_BIT1, 0x00);

    // Analog isolation off
    ScalerSetBit_EXINT3(P40_4C_VCCKOFF_CONTROL4C, ~_BIT0, _BIT0);

    DELAY_10US_EXINT();

    // case _POWER_CUT_GROUP_USB_DFP_DPHY:
    // Digital power on
    ScalerSetBit_EXINT3(P6F_27_PD32_POWER_CTRL, ~_BIT5, 0x00);

    // Digital isolation off
    ScalerSetBit_EXINT3(P6F_27_PD32_POWER_CTRL, ~_BIT1, 0x00);

    // Power Cut block Release
    ScalerSetBit_EXINT3(P6F_27_PD32_POWER_CTRL, ~_BIT0, 0x00);

    DELAY_10US_EXINT();

    // case _POWER_CUT_GROUP_USB_UFP_RETIMER_MAC:
    // Digital power on
    ScalerSetBit_EXINT3(P6F_8C_PD121_POWER_CTRL, ~_BIT5, 0x00);

    // Digital isolation off
    ScalerSetBit_EXINT3(P6F_8C_PD121_POWER_CTRL, ~_BIT1, 0x00);

    // Power Cut block Release
    ScalerSetBit_EXINT3(P6F_8C_PD121_POWER_CTRL, ~_BIT0, 0x00);

    DELAY_10US_EXINT();

    // case _POWER_CUT_GROUP_USB_UFP_RETIMER_MAC:
    // Digital power on
    ScalerSetBit_EXINT3(P6F_8D_PD122_POWER_CTRL, ~_BIT5, 0x00);

    // Digital isolation off
    ScalerSetBit_EXINT3(P6F_8D_PD122_POWER_CTRL, ~_BIT1, 0x00);

    // Power Cut block Release
    ScalerSetBit_EXINT3(P6F_8D_PD122_POWER_CTRL, ~_BIT0, 0x00);

    DELAY_10US_EXINT();

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
        // case _POWER_CUT_GROUP_RX0_DP20_U32_APHY:
        // Digital power on
        ScalerSetBit_EXINT3(P6F_60_PD1_POWER_CTRL, ~_BIT7, 0x00);

        // Power on bandgap
        ScalerSetBit_EXINT3(P6F_60_PD1_POWER_CTRL, ~_BIT0, _BIT0);

        // Analog isolation off
        ScalerSetBit_EXINT3(P40_41_VCCKOFF_CONTROL41, ~_BIT0, _BIT0);

        DELAY_10US_EXINT();
#endif
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
#if(_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
        // case _POWER_CUT_GROUP_RX1_DP20_U32_APHY:
        // Digital power on
        ScalerSetBit_EXINT3(P6F_65_PD6_POWER_CTRL, ~_BIT7, 0x00);

        // Power on bandgap
        ScalerSetBit_EXINT3(P6F_65_PD6_POWER_CTRL, ~_BIT0, _BIT0);

        // Analog isolation off
        ScalerSetBit_EXINT3(P40_42_VCCKOFF_CONTROL42, ~_BIT0, _BIT0);

        DELAY_10US_EXINT();
#endif
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Check if power cut off
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
bit ScalerUsb3RepeaterMacCheckP3PowerCutOFF_EXINT3(void)
{
    // Check the MAC UFP Power Cut status
    if(ScalerGetBit_EXINT3(P6F_8C_PD121_POWER_CTRL, _BIT4) == _BIT4)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

#if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Description  : USB3 Repeater Power Cut OFF Power Interfere FW Solution Process
// Input Value  : EnumTypeCPcbPort, EnumP3PowerSolutionStep
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RepeaterMacP3PowerInterfereSolution_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort, EnumP3PowerSolutionStep enumP3PowerSolutionStep)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    switch(enumP3PowerSolutionStep)
    {
        case _P3_POWER_SOLUTION_HIGH_PIRORITY:

#if(_DP_PHY_TX_SUPPORT == _ON)
            // Pre-processing to activate DPTx Aphy : DDR Power On
            PCB_DDR_POWER(_DDR_POWER_ON);
#endif
            //============================================================
            // Adjusting MCU/Flash Clock Divider to Enhance LFPS forwarding speed.
            //============================================================
            // Set Mcu/Flash Clock to M2PLL
            ScalerMcuFlashClockGroupSetting(_M2PLL_CLK);

            break;

        case _P3_POWER_SOLUTION_MEDIUM_PIRORITY:

            // Activate the adjacent Dx Port Phy in advance to avoid power interference and prevent BitError.
            if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
            {
#if(_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
                // PowerOn D1 Aphy to Aviod BitError
                ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX1_DP20_U32_APHY, _POWER_CUT_OFF, _POWER_RESET_ENABLE);

                // PowerOn D1 Dphy to Aviod BitError
                ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX1_DP_DPHY, _POWER_CUT_OFF, _POWER_RESET_ENABLE);
#endif
            }
            else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
            {
#if(_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
                // PowerOn D0 Aphy to Aviod BitError
                ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX0_DP20_U32_APHY, _POWER_CUT_OFF, _POWER_RESET_ENABLE);

                // PowerOn D0 Dphy to Aviod BitError
                ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX0_DP_DPHY, _POWER_CUT_OFF, _POWER_RESET_ENABLE);
#endif
            }

            break;

        case _P3_POWER_SOLUTION_LOW_PIRORITY:

#if(_DP_PHY_TX_SUPPORT == _ON)
            // Pre-processing to activate DPTx Aphy : Delay For DDR_1V5
            ScalerTimerDelayXms(2);

            // Pre-processing to activate DPTx Aphy : VCCK_OFF Power On
            PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_ON);

            // PowerOn DPTx Aphy to Aviod BitError
            ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_PX0_DP20_APHY, _POWER_CUT_OFF, _POWER_RESET_ENABLE);
#endif
            //============================================================
            // Adjusting MCU/Flash Clock Divider Back to PowerSaving Setting
            //============================================================
            // Set Mcu/Flash Clock to IOSC
            ScalerMcuFlashClockGroupSetting(_IOSC_CLK);

            break;

        default:

            break;
    }
}
#endif // End of #if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#endif

