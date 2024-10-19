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
// ID Code      : RL6952_Series_GDIPhyRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_GDIPHY__

#include "ScalerFunctionInclude.h"
#include "GDIPhyRx/ScalerGDIPhyRx.h"


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
// Description  : GDI Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx0~5
//--------------------------------------------------
EnumRx ScalerGDIPhyRxDxRxMapping(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

    enumInputPort = enumInputPort;

#if(_DP_SUPPORT == _ON)
    if((enumRx = ScalerDpPhyRxDxRxMapping(enumInputPort)) != _RX_MAP_NONE)
    {
        return enumRx;
    }
#endif

#if(_HDMI_SUPPORT == _ON)
    if((enumRx = ScalerTmdsPhyRxDxRxMapping(enumInputPort)) != _RX_MAP_NONE)
    {
        return enumRx;
    }
#endif

    return enumRx;
}

//--------------------------------------------------
// Description  : GDI Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx0~5
//--------------------------------------------------
EnumInputPort ScalerGDIPhyRxRxDxMapping(EnumRx enumRx)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    enumRx = enumRx;

#if(_DP_SUPPORT == _ON)
    if((enumInputPort = ScalerDpPhyRxRxDxMapping(enumRx)) != _NO_INPUT_PORT)
    {
        return enumInputPort;
    }
#endif

#if(_HDMI_SUPPORT == _ON)
    if((enumInputPort = ScalerTmdsPhyRxRxDxMapping(enumRx)) != _NO_INPUT_PORT)
    {
        return enumInputPort;
    }
#endif

    return enumInputPort;
}

//--------------------------------------------------
// Description  : GDI Bandgap
// Input Value  : ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRxBandgap(bit bSelect)
{
    // AV1833 = 3.3V
    ScalerSetByte(P29_16_LDO_00, 0xFF);
    ScalerSetByte(P29_17_LDO_01, 0xAA);
    ScalerSetByte(P29_18_LDO_02, 0xAA);
    ScalerSetByte(PB2_16_LDO_00, 0xFF);
    ScalerSetByte(PB2_17_LDO_01, 0xAA);
    ScalerSetByte(PB2_18_LDO_02, 0xAA);
    ScalerSetBit(PE8_01_LDO_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));
    ScalerSetBit(PE8_00_LDO_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // reg_vcm_tune = 0.55V
    ScalerSetByte(P29_05_RX_TOP_05, 0xAA);
    ScalerSetByte(PB2_05_RX_TOP_05, 0xAA);

    if(bSelect == _ON)
    {
        // [5] reg_en_ldo_dprx == 1'b1 --> Enable Bandgap
        ScalerSetBit(PE8_01_LDO_2, ~_BIT0, _BIT0);

        // [4] reg_bg_en == 1'b1 --> Enable Bandgap
        ScalerSetBit(P7C_02_GDI_TERM_2, ~_BIT4, _BIT4);

        // [4] reg_bg_en == 1'b1 --> Enable Bandgap
        ScalerSetBit(P7D_02_GDI_TERM_2, ~_BIT4, _BIT4);

        // HDMI Clock Gating to Measure Block
#if(_D3_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxFreqDetectClkGating(_D3_INPUT_PORT);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        ScalerTmdsMacRxFreqDetectClkGating(_D4_INPUT_PORT);
#endif

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_RETIMER_MAC0_SUPPORT == _ON))
        if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() != _USB3_RETIMER_EXIT_P3_PS) || (GET_USB_HUB_SWITCH_PORT_RESULT() != _HUB_D0_TYPE_C_PORT))
#endif
#if(_DP_PHY_RX0_SUPPORT == _ON)
        {
#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
            // D0 [7:4] rx_en, [3:0] CDR_en always on
            ScalerGDIPhyRx0LanePower(_ENABLE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx0LanePower(_ENABLE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx0LanePower(_ENABLE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx0LanePower(_ENABLE, _GDI_PHY_LANE3);
#endif
        }

#if((_D0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) ||\
    ((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D0_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_DIRECT_TO_HUB)))
        // Enable Z0
        ScalerGDIPhyRx0LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
        ScalerGDIPhyRx0LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
        ScalerGDIPhyRx0LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
        ScalerGDIPhyRx0LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);
#endif
#endif

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_RETIMER_MAC0_SUPPORT == _ON))
        if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() != _USB3_RETIMER_EXIT_P3_PS) || (GET_USB_HUB_SWITCH_PORT_RESULT() != _HUB_D1_TYPE_C_PORT))
#endif
#if(_DP_PHY_RX1_SUPPORT == _ON)
        {
#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
            // D1 [7:4] rx_en, [3:0] CDR_en always on
            ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE3);
#endif
        }

#if((_D1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) ||\
    ((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_DIRECT_TO_HUB)))
        // Enable Z0
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);
#endif
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
        // D2 [7:4] rx_en, [3:0] CDR_en always on
        ScalerGDIPhyRx2LanePower(_ENABLE, _GDI_PHY_LANE0);
        ScalerGDIPhyRx2LanePower(_ENABLE, _GDI_PHY_LANE1);
        ScalerGDIPhyRx2LanePower(_ENABLE, _GDI_PHY_LANE2);
        ScalerGDIPhyRx2LanePower(_ENABLE, _GDI_PHY_LANE3);
#endif
        // Enable Z0
        ScalerSetByte(PE8_08_Z0_3, 0xFF);
#endif
    }
    else
    {
#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
        if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_NO_ACTION) || (GET_USB_HUB_SWITCH_PORT_RESULT() != _HUB_D0_TYPE_C_PORT))
#endif
        {
#if(_DP_PHY_RX0_SUPPORT == _ON)
            // D0 [7:4] rx_en, [3:0] CDR_en always off
            ScalerGDIPhyRx0LanePower(_DISABLE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx0LanePower(_DISABLE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx0LanePower(_DISABLE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx0LanePower(_DISABLE, _GDI_PHY_LANE3);
#endif
        }

#if((_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
        if((ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_NO_ACTION) || (GET_USB_HUB_SWITCH_PORT_RESULT() != _HUB_D1_TYPE_C_PORT))
#endif
        {
#if(_DP_PHY_RX1_SUPPORT == _ON)
            // D1 [7:4] rx_en, [3:0] CDR_en always off
            ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE3);
#endif
        }

#if(_DP_PHY_RX2_SUPPORT == _ON)
        // D2 [7:4] rx_en, [3:0] CDR_en always off
        ScalerGDIPhyRx2LanePower(_DISABLE, _GDI_PHY_LANE0);
        ScalerGDIPhyRx2LanePower(_DISABLE, _GDI_PHY_LANE1);
        ScalerGDIPhyRx2LanePower(_DISABLE, _GDI_PHY_LANE2);
        ScalerGDIPhyRx2LanePower(_DISABLE, _GDI_PHY_LANE3);
#endif
        // [5] reg_en_bandgap_dprx == 1'b0 --> Disable Bandgap
        ScalerSetBit(PE8_01_LDO_2, ~_BIT0, 0x00);

#if(_HDMI_CEC_SUPPORT == _OFF)
        // [4] reg_bg_en == 1'b1 --> Disable Bandgap
        ScalerSetBit(P7C_02_GDI_TERM_2, ~_BIT4, 0x00);

        // [4] reg_bg_en == 1'b1 --> Disable Bandgap
        ScalerSetBit(P7D_02_GDI_TERM_2, ~_BIT4, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : GDI Rx1 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRxPowerProc(EnumInputPort enumInputPort, EnumPowerAction enumPowerAction)
{
    switch(ScalerGDIPhyRxDxRxMapping(enumInputPort))
    {
#if((_TMDS_PHY_RX0_SUPPORT == _ON) || (_DP_PHY_RX0_SUPPORT == _ON) || (_USB3_UFP_PHY0_SUPPORT == _ON))
        case _RX0:
            ScalerGDIPhyRx0PowerProc(enumPowerAction);
            break;
#endif

#if((_TMDS_PHY_RX1_SUPPORT == _ON) || (_DP_PHY_RX1_SUPPORT == _ON) || (_USB3_UFP_PHY1_SUPPORT == _ON))
        case _RX1:
            ScalerGDIPhyRx1PowerProc(enumPowerAction);
            break;
#endif

#if((_TMDS_PHY_RX2_SUPPORT == _ON) || (_DP_PHY_RX2_SUPPORT == _ON))
        case _RX2:
            ScalerGDIPhyRx2PowerProc(enumPowerAction);
            break;
#endif

#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
        case _RX3:
            ScalerGDIPhyRx3PowerProc(enumPowerAction);
            break;
#endif

#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
        case _RX4:
            ScalerGDIPhyRx4PowerProc(enumPowerAction);
            break;
#endif

#if((_TMDS_PHY_RX5_SUPPORT == _ON) || (_DP_PHY_RX5_SUPPORT == _ON))
        case _RX5:
            ScalerGDIPhyRx5PowerProc(enumPowerAction);
            break;
#endif

        default:
            break;
    }
}
//--------------------------------------------------
// Description  : Disable PHY of All Other Port
// Input Value  : Present Port in Search State
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRxDisableOtherPort(EnumInputPort enumInputPort)
{
#if((_HP_SOURCE_SCAN_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
    BYTE ucFakeLT = ScalerDpAuxRxGetAllPortFakeLT();
#endif
    switch(ScalerGDIPhyRxDxRxMapping(enumInputPort))
    {
        ////////////////////////
        // Rx0, Disable Rx1-4 //
        ////////////////////////

        case _RX0:

#if((_TMDS_PHY_RX1_SUPPORT == _ON) || (_DP_PHY_RX1_SUPPORT == _ON))
#if((_DP_PHY_RX1_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT1) == _BIT1)
#endif
            {
                ScalerGDIPhyRx1PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX2_SUPPORT == _ON) || (_DP_PHY_RX2_SUPPORT == _ON))
#if((_DP_PHY_RX2_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT2) == _BIT2)
#endif
            {
                ScalerGDIPhyRx2PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
            ScalerGDIPhyRx3PowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif

#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
            ScalerGDIPhyRx4PowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif
            break;

        //////////////////////////
        // Rx1, Disable Rx0/2-4 //
        //////////////////////////

        case _RX1:

#if((_TMDS_PHY_RX0_SUPPORT == _ON) || (_DP_PHY_RX0_SUPPORT == _ON))
#if((_DP_PHY_RX0_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT0) == _BIT0)
#endif
            {
                ScalerGDIPhyRx0PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX2_SUPPORT == _ON) || (_DP_PHY_RX2_SUPPORT == _ON))
#if((_DP_PHY_RX2_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT2) == _BIT2)
#endif
            {
                ScalerGDIPhyRx2PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
            ScalerGDIPhyRx3PowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif

#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
            ScalerGDIPhyRx4PowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif
            break;

        ////////////////////////////
        // Rx2, Disable Rx0-1/3-4 //
        ////////////////////////////

        case _RX2:

#if((_TMDS_PHY_RX0_SUPPORT == _ON) || (_DP_PHY_RX0_SUPPORT == _ON))
#if((_DP_PHY_RX0_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT0) == _BIT0)
#endif
            {
                ScalerGDIPhyRx0PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX1_SUPPORT == _ON) || (_DP_PHY_RX1_SUPPORT == _ON))
#if((_DP_PHY_RX1_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT1) == _BIT1)
#endif
            {
                ScalerGDIPhyRx1PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
            ScalerGDIPhyRx3PowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif

#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
            ScalerGDIPhyRx4PowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif
            break;

        //////////////////////////
        // Rx3, Disable Rx0-2/4 //
        //////////////////////////

        case _RX3:

#if((_TMDS_PHY_RX0_SUPPORT == _ON) || (_DP_PHY_RX0_SUPPORT == _ON))
#if((_DP_PHY_RX0_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT0) == _BIT0)
#endif
            {
                ScalerGDIPhyRx0PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX1_SUPPORT == _ON) || (_DP_PHY_RX1_SUPPORT == _ON))
#if((_DP_PHY_RX1_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT1) == _BIT1)
#endif
            {
                ScalerGDIPhyRx1PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX2_SUPPORT == _ON) || (_DP_PHY_RX2_SUPPORT == _ON))
#if((_DP_PHY_RX2_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT2) == _BIT2)
#endif
            {
                ScalerGDIPhyRx2PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
            ScalerGDIPhyRx4PowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif
            break;

        ////////////////////////
        // Rx4, Disable Rx0-3 //
        ////////////////////////

        case _RX4:

#if((_TMDS_PHY_RX0_SUPPORT == _ON) || (_DP_PHY_RX0_SUPPORT == _ON))
#if((_DP_PHY_RX0_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT0) == _BIT0)
#endif
            {
                ScalerGDIPhyRx0PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX1_SUPPORT == _ON) || (_DP_PHY_RX1_SUPPORT == _ON))
#if((_DP_PHY_RX1_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT1) == _BIT1)
#endif
            {
                ScalerGDIPhyRx1PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX2_SUPPORT == _ON) || (_DP_PHY_RX2_SUPPORT == _ON))
#if((_DP_PHY_RX2_SUPPORT == _ON) && (_HP_SOURCE_SCAN_SUPPORT == _ON))
            if((ucFakeLT & _BIT2) == _BIT2)
#endif
            {
                ScalerGDIPhyRx2PowerProc(_POWER_ACTION_NORMAL_TO_PS);
            }
#endif

#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
            ScalerGDIPhyRx3PowerProc(_POWER_ACTION_NORMAL_TO_PS);
#endif
            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Config Lane Power of Combo PHY
// Input Value  : Input Port, Enable/Disable, Lane
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRxLanePower(EnumInputPort enumInputPort, bit bEnable, BYTE ucLane)
{
    bEnable = bEnable;
    ucLane = ucLane;

    switch(ScalerGDIPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
        case _RX0:

#if(_USB3_UFP_PHY0_SUPPORT == _ON)
            ScalerGDIPhyRx0LanePower(bEnable, ucLane);
#endif
            break;

        case _RX1:

#if(_USB3_UFP_PHY1_SUPPORT == _ON)
            ScalerGDIPhyRx1LanePower(bEnable, ucLane);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Combo PHY Switch
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRxComboPhySwitch(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;
}