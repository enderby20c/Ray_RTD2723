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
// ID Code      : ScalerDpMacRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpMacRx/ScalerDpMacRx.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MAC High Priority Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacRxHighPriorityIntHandler_EXINT0(void)
{
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    ScalerDpMacDphyRx0DigitalPhyHighPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX0_SUPPORT == _ON)
    ScalerDpMacStreamRx0MacHighPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
    ScalerDpMacDphyRx1DigitalPhyHighPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    ScalerDpMacStreamRx1MacHighPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
    ScalerDpMacDphyRx2DigitalPhyHighPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    ScalerDpMacStreamRx2MacHighPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    ScalerDpMacStreamRx3MacHighPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    // ScalerDpMacRx4DigitalPhyHighPriorityIntHandler_EXINT0();
    // ScalerDpMacRx4MacHighPriorityIntHandler_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : DP MAC Low Priority Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacRxLowPriorityIntHandler_EXINT0(void)
{
#if(_DP_MAC_DPHY_RX0_SUPPORT == _ON)
    ScalerDpMacDphyRx0DigitalPhyLowPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX0_SUPPORT == _ON)
    ScalerDpMacStreamRx0MacLowPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)
    ScalerDpMacDphyRx1DigitalPhyLowPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    ScalerDpMacStreamRx1MacLowPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_DPHY_RX2_SUPPORT == _ON)
    ScalerDpMacDphyRx2DigitalPhyLowPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    ScalerDpMacStreamRx2MacLowPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    ScalerDpMacStreamRx3MacLowPriorityIntHandler_EXINT0();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    // ScalerDpMacRx4DigitalPhyLowPriorityIntHandler_EXINT0();
    ScalerDpMacStreamRx4MacLowPriorityIntHandler_EXINT0();
#endif
}

//--------------------------------------------------
// Description  : Get DP Mac RX Power Cut Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacRxGetPowerCutFlagStatus_EXINT0(EnumInputPort enumInputPort)
{
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)

    return ScalerDpMacRxGetComboPowerCutFlagStatus(enumInputPort);

#else

    return ScalerDpMacDphyRxGetPowerCutFlagStatus(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : DP MAC power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacRxPowerProc_EXINT0(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
    // DP MAC DPHY and MAC Stream Combo Power Domain
    ScalerDpMacRxPowerCutComboPowerProc_EXINT0(enumInputPort, enumPowerAction);
#else

    ScalerDpMacDphyRxPowerProc_EXINT0(enumInputPort, enumPowerAction);
#endif
}

//--------------------------------------------------
// Description  : Get DP Mac RX Power Cut Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumPowerCut ScalerDpMacRxGetPowerCutCurrentStatus_EXINT0(EnumInputPort enumInputPort)
{
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
    // DP MAC DPHY and MAC Stream Combo Power Domain
    return ScalerDpMacRxGetComboPowerCutCurrentStatus_EXINT0(enumInputPort);
#else

    return ScalerDpMacDphyRxGetPowerCutCurrentStatus_EXINT0(enumInputPort);
#endif
}

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
//--------------------------------------------------
// Description  : DP MAC power process
// Input Value  : EnumInputPort, EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacRxPowerCutComboPowerProc_EXINT0(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch_EXINT0(enumInputPort);

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            switch(enumPowerAction)
            {
                case _POWER_ACTION_NORMAL_TO_OFF:

                    // Set DPRX SRAM CLK Gate Disable
                    ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

                    // DP MAC0 Power Cut Enable
                    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX0_DP14_MAC, _POWER_CUT_ON, _POWER_RESET_DISABLE);

                    break;

                case _POWER_ACTION_OFF_TO_NORMAL:

                    // DP MAC0 Power Cut Disable
                    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX0_DP14_MAC, _POWER_CUT_OFF, _POWER_RESET_ENABLE);

                    // Reset Key download port
                    ScalerDpMacDphyRxPowerDataRecover_EXINT0(enumInputPort);

                    // Set DPRX SRAM CLK Gate Enable
                    ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _ENABLE);

                    break;

                default:
                    break;
            }

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            switch(enumPowerAction)
            {
                case _POWER_ACTION_NORMAL_TO_OFF:

                    // Set DPRX SRAM CLK Gate Disable
                    ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

                    // DP MAC1 Power Cut Enable
                    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX1_DP14_MAC, _POWER_CUT_ON, _POWER_RESET_DISABLE);

                    break;

                case _POWER_ACTION_OFF_TO_NORMAL:

                    // DP MAC1 Power Cut Disable
                    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX1_DP14_MAC, _POWER_CUT_OFF, _POWER_RESET_ENABLE);

                    // Reset Key download port
                    ScalerDpMacDphyRxPowerDataRecover_EXINT0(enumInputPort);

                    // Set DPRX SRAM CLK Gate Enable
                    ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _ENABLE);

                    break;

                default:
                    break;
            }

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            switch(enumPowerAction)
            {
                case _POWER_ACTION_NORMAL_TO_OFF:

                    // Set DPRX SRAM CLK Gate Disable
                    ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

                    // DP MAC2 Power Cut Enable
                    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX2_DP14_MAC, _POWER_CUT_ON, _POWER_RESET_DISABLE);

                    break;

                case _POWER_ACTION_OFF_TO_NORMAL:

                    // DP MAC2 Power Cut Disable
                    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX2_DP14_MAC, _POWER_CUT_OFF, _POWER_RESET_ENABLE);

                    // Reset Key download port
                    ScalerDpMacDphyRxPowerDataRecover_EXINT0(enumInputPort);

                    // Set DPRX SRAM CLK Gate Enable
                    ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _ENABLE);

                    break;

                default:
                    break;
            }

            break;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP MAC Power Cut Status
// Input Value  : EnumInputPort
// Output Value : EnumPowerCut
//--------------------------------------------------
EnumPowerCut ScalerDpMacRxGetComboPowerCutCurrentStatus_EXINT0(EnumInputPort enumInputPort)
{
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch_EXINT0(enumInputPort);

    switch(enumDpMacSel)
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX0_DP14_MAC);

            break;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX1_DP14_MAC);

            break;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return ScalerPowerGroupGetPowerCutStatus(_POWER_CUT_GROUP_RX2_DP14_MAC);

            break;
#endif

        default:

            return _POWER_CUT_ON;

            break;
    }
}
#endif
#endif
