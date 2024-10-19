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
// ID Code      : ScalerUsb3RepeaterPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Usb3RepeaterPhy/ScalerUsb3RepeaterPhy.h"

#if(_USB3_REPEATER_PHY_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_RDC_TEST_TYPE == _USB3_REDRIVER_RDC_TEST_TYPE)
//--------------------------------------------------
// Description  : USB3 Repeater Initial
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
bit ScalerUsb3RepeaterPhyCtsModeCheck(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

            if((GET_USB3_REDRIVER_UFP_PHY0_KMODE_FINISH() == _TRUE) && (GET_USB3_REDRIVER_UFP_PHY0_CTS_FLOW() == _TRUE))
            {
                return _TRUE;
            }

#elif(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_UFP_PHY1_SUPPORT == _ON)

            if((GET_USB3_REDRIVER_UFP_PHY1_KMODE_FINISH() == _TRUE) && (GET_USB3_REDRIVER_UFP_PHY1_CTS_FLOW() == _TRUE))
            {
                return _TRUE;
            }

#elif(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : USB3 Repeater Initial
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyCtsFlow(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_UFP_PHY1_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

#endif
            break;

        default:
            break;
    }

    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_DFP_PHY0_SUPPORT == _ON)

#elif(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_DFP_PHY1_SUPPORT == _ON)

#elif(_USB3_RETIMER_DFP_PHY1_SUPPORT == _ON)

#endif
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : USB3 Repeater Power On Initial
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyPowerSwitchInitial(EnumPowerAction enumSwitch, EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCPinCfgType enumPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;
    enumPinAssignment = enumPinAssignment;

    switch(enumSwitch)
    {
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            if(ScalerUsb3RepeaterPhyGetKModeFinish(enumTypeCPcbPort) == _FALSE)
            {
                ScalerUsb3RetimerPhyPowerSwitchInitial(enumTypeCPcbPort);
            }

            ScalerUsb3RetimerPhySetKModeFinish(enumTypeCPcbPort);

#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
            if(ScalerTypeCRxGetPortCtrlType(ScalerTypeCPcbPortConvertToDx(enumTypeCPcbPort)) == _TYPE_C_PORT_CTRL_EMBEDDED)
            {
                ScalerTypeCGetPinAssignment(enumTypeCPcbPort, &enumPinAssignment);

                ScalerDpPhyRxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToDx(enumTypeCPcbPort), enumPinAssignment, ScalerTypeCGetOrientation(enumTypeCPcbPort));
            }
#endif

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_AC_ON_INITIAL:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
            if(enumTypeCPcbPort == (EnumTypeCPcbPort) GET_USB_HUB_SWITCH_PORT_RESULT())
            {
                if(ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_NO_ACTION)
                {
                    ScalerUsb3RetimerPhyClearKModeFinish(enumTypeCPcbPort);
                }
            }
            else
#endif
            {
                ScalerUsb3RetimerPhyClearKModeFinish(enumTypeCPcbPort);
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Repeater Initial
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyInitial(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumOrientation, EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPinCfgType = enumTypeCPinCfgType;
    enumOrientation = enumOrientation;

#if(_HW_USB3_REPEATER_UFP_P3_DPHY_PWRCUT_SUPPORT == _ON)
    if(enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_D)
    {
        SET_USB3_RETIMER_PHY_PINASSIGNMENT_D();
    }
    else
    {
        CLR_USB3_RETIMER_PHY_PINASSIGNMENT_D();
    }

    if(enumOrientation == _TYPE_C_ORIENTATION_FLIP)
    {
        CLR_USB3_RETIMER_PHY_UNFLIP();
    }
    else
    {
        SET_USB3_RETIMER_PHY_UNFLIP();
    }
#endif

    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

            // Release D0 Power Cut
            ScalerPowerDomainEnableControl(_HW_USB3_REPEATER_UFP0_APHY_POWER_CUT_GROUP, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

            if(ScalerUsb3RepeaterPhyGetKModeFinish(enumTypeCPcbPort) == _FALSE)
            {
                ScalerUsb3RepeaterPhyPowerSwitchInitial(_POWER_ACTION_OFF_TO_NORMAL, enumTypeCPcbPort);
            }

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RepeaterPhyJfmInitialSetting(enumTypeCPcbPort);

            ScalerUsb3RetimerUfpPhy0Initial(enumTypeCPinCfgType, enumOrientation);
#endif

            break;

        case _RX1:
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            // Release D1 Power Cut
            ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX1_DP20_U32_APHY, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerUsb3RepeaterPhyGetKModeFinish(enumTypeCPcbPort) == _FALSE)
            {
                ScalerUsb3RepeaterPhyPowerSwitchInitial(_POWER_ACTION_OFF_TO_NORMAL, enumTypeCPcbPort);
            }

#if(_USB3_REDRIVER_UFP_PHY1_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            ScalerUsb3RepeaterPhyJfmInitialSetting(enumTypeCPcbPort);

            ScalerUsb3RetimerUfpPhy1Initial(enumTypeCPinCfgType, enumOrientation);
#endif

            break;

        default:
            break;
    }

    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_DFP_PHY0_SUPPORT == _ON)

#elif(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerDfpPhy0Initial(enumTypeCPcbPort);
#endif
            switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
            {
                case _RX0:
#if((_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON) && (_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT))

                    // Toggle Tx fld_rst to re-lock ref clk
                    ScalerSetBit(P1C_D0_FLD_TX_0, ~_BIT7, 0x00);
                    ScalerSetBit(P1C_D0_FLD_TX_0, ~_BIT7, _BIT7);

                    // Delay Time us [0,400] Waiting for Polling FLD FSM
                    for(pData[0] = 0; pData[0] <= 40; pData[0]++)
                    {
                        DELAY_10US();

                        if((ScalerGetBit(P1C_E8_FLD_TX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
                           (ScalerGetBit(P1C_E8_FLD_TX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
                        {
                            break;
                        }
                    }
#endif

                    break;

                case _RX1:

#if((_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON) && (_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT))

                    // Toggle Tx fld_rst to re-lock ref clk
                    ScalerSetBit(P7A_D0_FLD_TX_0, ~_BIT7, 0x00);
                    ScalerSetBit(P7A_D0_FLD_TX_0, ~_BIT7, _BIT7);

                    // Delay Time us [0,400] Waiting for Polling FLD FSM
                    for(pData[0] = 0; pData[0] <= 40; pData[0]++)
                    {
                        DELAY_10US();

                        if((ScalerGetBit(P7A_E8_FLD_TX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
                           (ScalerGetBit(P7A_E8_FLD_TX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
                        {
                            break;
                        }
                    }
#endif

                    break;

                default:
                    break;
            }

            break;

        case _RX1:

#if(_USB3_REDRIVER_DFP_PHY1_SUPPORT == _ON)

#elif(_USB3_RETIMER_DFP_PHY1_SUPPORT == _ON)

            ScalerUsb3RetimerDfpPhy1Initial(enumTypeCPcbPort);
#endif

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Get KMode Finish
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
bit ScalerUsb3RepeaterPhyGetKModeFinish(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_USB3_REDRIVER_UFP_PHY_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY_SUPPORT == _ON)

    return ScalerUsb3RetimerPhyGetKModeFinish(enumTypeCPcbPort);

#endif
}

//--------------------------------------------------
// Description  : USB3 Repeater Jfm Eable Port Select
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyJfmInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_USB3_RETIMER_UFP_PHY_SUPPORT == _ON)

    ScalerUsb3RetimerPhyUfpJfmInitialSetting(enumTypeCPcbPort);

#endif
}

//--------------------------------------------------
// Description  : USB3 Repeater Enable
// Input Value  : enumInputPort , bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyDisable(EnumTypeCPcbPort enumTypeCPcbPort, bit bAttach, EnumTypeCOrientation enumTypeCOrientation, EnumTypeCPinCfgType enumTypeCPinCfgType)
{
    bAttach = bAttach;
    enumTypeCOrientation = enumTypeCOrientation;
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumTypeCPinCfgType = enumTypeCPinCfgType;

#if(_U3_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON)
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy0Disable(bAttach, enumTypeCOrientation, enumTypeCPinCfgType);

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_UFP_PHY1_SUPPORT == _ON)

#elif(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy1Disable(bAttach, enumTypeCOrientation, enumTypeCPinCfgType);

#endif
            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }

    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_DFP_PHY0_SUPPORT == _ON)

#elif(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerPhyUfpJfmDisable();
            ScalerUsb3RetimerDfpPhy0Disable();

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_DFP_PHY1_SUPPORT == _ON)

#elif(_USB3_RETIMER_DFP_PHY1_SUPPORT == _ON)

            ScalerUsb3RetimerDfpPhy1Disable();

#endif
            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
#endif // if(_U3_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON)
}

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
//--------------------------------------------------
// Description  : USB3 Repeater Enable
// Input Value  : enumInputPort , bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyMuxSwitchControl(EnumInputPort enumInputPort, EnumUSBHubPathEnable enumUSBHubPathEnable)
{
    enumInputPort = enumInputPort;
    enumUSBHubPathEnable = enumUSBHubPathEnable;
}
#endif

//--------------------------------------------------
// Description  : USB3 Repeater Dx to UFP Phy Mapping
// Input Value  : EnumTypeCPcbPort
// Output Value : UfpPhyx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumRx enumUfpPhyxIndex = _RX_MAP_NONE;

    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)

        case _D0_TYPE_C_PORT:

#if(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)

            enumUfpPhyxIndex = _RX0;

#elif(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)

            enumUfpPhyxIndex = _RX1;

#elif(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)

            enumUfpPhyxIndex = _RX2;
#endif
            break;

#endif // End of #if(_D0_USB_HUB_SUPPORT == _ON)

#if(_D1_USB_HUB_SUPPORT == _ON)

        case _D1_TYPE_C_PORT:

#if(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)

            enumUfpPhyxIndex = _RX0;

#elif(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)

            enumUfpPhyxIndex = _RX1;

#elif(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)

            enumUfpPhyxIndex = _RX2;
#endif
            break;

#endif // End of #if(_D1_USB_HUB_SUPPORT == _ON)

#if(_D2_USB_HUB_SUPPORT == _ON)

        case _D2_TYPE_C_PORT:

#if(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)

            enumUfpPhyxIndex = _RX0;

#elif(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)

            enumUfpPhyxIndex = _RX1;

#elif(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)

            enumUfpPhyxIndex = _RX2;
#endif
            break;

#endif // End of #if(_D2_USB_HUB_SUPPORT == _ON)

        default:

            break;
    }

    return enumUfpPhyxIndex;
}

//--------------------------------------------------
// Description  : USB3 Repeater Dx to UFP Phy Mapping
// Input Value  : EnumTypeCPcbPort
// Output Value : UfpPhyx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterPhyDx2UfpPhyxMapping_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumRx enumUfpPhyxIndex = _RX_MAP_NONE;

    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)

        case _D0_TYPE_C_PORT:

#if(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)

            enumUfpPhyxIndex = _RX0;

#elif(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)

            enumUfpPhyxIndex = _RX1;

#elif(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)

            enumUfpPhyxIndex = _RX2;
#endif
            break;

#endif // End of #if(_D0_USB_HUB_SUPPORT == _ON)

#if(_D1_USB_HUB_SUPPORT == _ON)

        case _D1_TYPE_C_PORT:

#if(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)

            enumUfpPhyxIndex = _RX0;

#elif(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)

            enumUfpPhyxIndex = _RX1;

#elif(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)

            enumUfpPhyxIndex = _RX2;
#endif
            break;

#endif // End of #if(_D1_USB_HUB_SUPPORT == _ON)

#if(_D2_USB_HUB_SUPPORT == _ON)

        case _D2_TYPE_C_PORT:

#if(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)

            enumUfpPhyxIndex = _RX0;

#elif(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)

            enumUfpPhyxIndex = _RX1;

#elif(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)

            enumUfpPhyxIndex = _RX2;
#endif
            break;

#endif // End of #if(_D2_USB_HUB_SUPPORT == _ON)

        default:
            break;
    }

    return enumUfpPhyxIndex;
}

//--------------------------------------------------
// Description  : USB3 Repeater Macx mapping to UfpPhyx
// Input Value  : Macx
// Output Value : UfpPhyx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterPhyMacx2UfpPhyxMapping_EXINT3(EnumRx enumMacxIndex)
{
    EnumRx enumUfpPhyIndex = _RX_MAP_NONE;

    switch(enumMacxIndex)
    {
        case _RX0:
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
                enumUfpPhyIndex = _RX0;
            }
            else if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == _BIT7)
            {
                enumUfpPhyIndex = _RX1;
            }
#else
            enumUfpPhyIndex = _RX0;
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

            break;

        case _RX1:

            break;

        case _RX2:

            break;

        default:

            break;
    }

    return enumUfpPhyIndex;
}

//--------------------------------------------------
// Description  : USB3 Repeater Macx mapping to DfpPhyx
// Input Value  : Macx
// Output Value : DfpPhyx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterPhyMacx2DfpPhyxMapping(EnumRx enumMacxIndex)
{
    EnumRx enumDfpPhyIndex = _RX_MAP_NONE;

    switch(enumMacxIndex)
    {
        case _RX0:
#if(_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0)
            enumDfpPhyIndex = _RX0;
#elif(_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1)
            enumDfpPhyIndex = _RX1;
#elif(_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2)
            enumDfpPhyIndex = _RX2;
#endif
            break;

        case _RX1:
#if(_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0)
            enumDfpPhyIndex = _RX0;
#elif(_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1)
            enumDfpPhyIndex = _RX1;
#elif(_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2)
            enumDfpPhyIndex = _RX2;
#endif
            break;

        case _RX2:
#if(_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0)
            enumDfpPhyIndex = _RX0;
#elif(_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1)
            enumDfpPhyIndex = _RX1;
#elif(_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2)
            enumDfpPhyIndex = _RX2;
#endif
            break;

        default:

            break;
    }

    return enumDfpPhyIndex;
}

//--------------------------------------------------
// Description  : USB3 Repeater Macx mapping to DfpPhyx
// Input Value  : Macx
// Output Value : DfpPhyx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterPhyMacx2DfpPhyxMapping_EXINT3(EnumRx enumMacxIndex)
{
    EnumRx enumDfpPhyIndex = _RX_MAP_NONE;

    switch(enumMacxIndex)
    {
        case _RX0:
#if(_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0)
            enumDfpPhyIndex = _RX0;
#elif(_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1)
            enumDfpPhyIndex = _RX1;
#elif(_HW_USB3_REPEATER_MAC0_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2)
            enumDfpPhyIndex = _RX2;
#endif
            break;

        case _RX1:
#if(_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0)
            enumDfpPhyIndex = _RX0;
#elif(_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1)
            enumDfpPhyIndex = _RX1;
#elif(_HW_USB3_REPEATER_MAC1_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2)
            enumDfpPhyIndex = _RX2;
#endif
            break;

        case _RX2:
#if(_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_0)
            enumDfpPhyIndex = _RX0;
#elif(_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_1)
            enumDfpPhyIndex = _RX1;
#elif(_HW_USB3_REPEATER_MAC2_TO_DFP_PHY_MAPPING == _USB3_REPEATER_DFP_PHY_2)
            enumDfpPhyIndex = _RX2;
#endif
            break;

        default:

            break;
    }

    return enumDfpPhyIndex;
}

//--------------------------------------------------
// Description  : USB3 Repeater Dx to DFP Phy Mapping
// Input Value  : EnumTypeCPcbPort
// Output Value : DfpPhyx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_USB3_REPEATER_SUPPORT == _ON)
    return ScalerUsb3RepeaterPhyMacx2DfpPhyxMapping(ScalerUsb3RepeaterMacDx2MacxMapping(enumTypeCPcbPort));
#endif
}

//--------------------------------------------------
// Description  : USB3 Repeater Dx to DFP Phy Mapping
// Input Value  : EnumTypeCPcbPort
// Output Value : DfpPhyx
//--------------------------------------------------
EnumRx ScalerUsb3RepeaterPhyDx2DfpPhyxMapping_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_USB3_REPEATER_SUPPORT == _ON)
    return ScalerUsb3RepeaterPhyMacx2DfpPhyxMapping_EXINT3(ScalerUsb3RepeaterMacDx2MacxMapping_EXINT3(enumTypeCPcbPort));
#endif
}

//--------------------------------------------------
// Description  : USB3 Repeater UfpPhyx mapping to Dx
// Input Value  : UfpPhyx
// Output Value : EnumTypeCPcbPort(Dx)
//--------------------------------------------------
EnumTypeCPcbPort ScalerUsb3RepeaterPhyUfpPhyx2DxMapping_EXINT3(EnumRx enumUfpPhyxIndex)
{
    EnumTypeCPcbPort enumTypeCPcbPort = _NO_TYPE_C_PORT;

    switch(enumUfpPhyxIndex)
    {
        case _RX0:
#if(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)
            enumTypeCPcbPort = _D0_TYPE_C_PORT;
#elif(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)
            enumTypeCPcbPort = _D1_TYPE_C_PORT;
#elif(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_0)
            enumTypeCPcbPort = _D2_TYPE_C_PORT;
#endif
            break;

        case _RX1:
#if(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)
            enumTypeCPcbPort = _D0_TYPE_C_PORT;
#elif(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)
            enumTypeCPcbPort = _D1_TYPE_C_PORT;
#elif(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_1)
            enumTypeCPcbPort = _D2_TYPE_C_PORT;
            break;
#endif

        case _RX2:
#if(_HW_USB3_REPEATER_D0_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)
            enumTypeCPcbPort = _D0_TYPE_C_PORT;
#elif(_HW_USB3_REPEATER_D1_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)
            enumTypeCPcbPort = _D1_TYPE_C_PORT;
#elif(_HW_USB3_REPEATER_D2_TO_UFP_PHY_MAPPING == _USB3_REPEATER_UFP_PHY_2)
            enumTypeCPcbPort = _D2_TYPE_C_PORT;
#endif
            break;

        default:
            break;
    }

    return enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : Fw Control EQ Training
// Input Value  : EnumTypeCPcbPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyFwAdaptionControl_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping_EXINT3(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

            ScalerSetByte_EXINT3(P86_2F_RTSSM_U_DUMMY_04, ScalerGetByte_EXINT3(P86_2F_RTSSM_U_DUMMY_04) + 1);
#endif
            break;

        default:
            break;
    }

    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping_EXINT3(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_DFP_PHY0_SUPPORT == _ON)
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Phy Enter Compliance Mode
// Input Value  : EnumTypeCPcbPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyEnterComplianceMode_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping_EXINT3(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_UFP_PHY1_SUPPORT == _ON)

#endif
            break;

        default:
            break;
    }

    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping_EXINT3(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_DFP_PHY0_SUPPORT == _ON)

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_DFP_PHY1_SUPPORT == _ON)

#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Phy Exit Compliance Mode
// Input Value  : EnumTypeCPcbPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RepeaterPhyExitComplianceMode_EXINT3(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping_EXINT3(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_UFP_PHY0_SUPPORT == _ON)

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_UFP_PHY1_SUPPORT == _ON)

#endif
            break;

        default:
            break;
    }

    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping_EXINT3(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_REDRIVER_DFP_PHY0_SUPPORT == _ON)

#endif
            break;

        case _RX1:

#if(_USB3_REDRIVER_DFP_PHY1_SUPPORT == _ON)

#endif
            break;

        default:
            break;
    }
}

#endif

