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
// ID Code      : RL6952_Series_GDIPhyRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_GDIPHYRX1__

#include "ScalerFunctionInclude.h"
#include "GDIPhyRx1/ScalerGDIPhyRx1.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_TMDS_PHY_RX1_SUPPORT == _ON) || (_DP_PHY_RX1_SUPPORT == _ON) || (_USB3_UFP_PHY1_SUPPORT == _ON))
//--------------------------------------------------
// Description  : GDI Rx1 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx1PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx1Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
            if(ScalerTypeCRxGetPinAssignment(ScalerGDIPhyRxRxDxMapping(_RX1)) == _TYPE_C_PIN_ASSIGNMENT_NONE)
            {
                ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE0);
                ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE1);
                ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE2);
                ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE3);
            }
#endif
            ScalerGDIPhyRx1Z0Switch(_ON);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_PS:

            ScalerGDIPhyRx1Z0Switch(_OFF);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D1 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx1Z0Switch(bit bSelect)
{
    if(bSelect == _ON)
    {
#if(_DIGITAL_PORT_SUPPORT == _ON)
        SET_DIGITAL_PORT_SWITCH_TO_D1();
#endif

#if((_D1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C) ||\
    ((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_DIRECT_TO_HUB)))
        // Enable Z0
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);
#endif
    }
    else
    {
#if(_DIGITAL_PORT_SUPPORT == _ON)
        CLR_DIGITAL_PORT_SWITCH_TO_D1();
#endif
    }
}

//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx1Power(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

#if((_D1_DP_Z0_IMPEDANCE_OPTION == _85_OHM) ||\
    ((_D1_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR) && (_D1_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ)) ||\
    ((_D1_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR) && (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))

            // Lane0/2 Z0 Differential Impedance = 0xA
            // Lane1/3 Z0 Differential Impedance = 0xA
            ScalerSetByte(PB2_3C_TERM_00, 0xAA);
            ScalerSetByte(PB2_3D_TERM_01, 0xAA);

            // Target = 90Ohm - 2 --> 85Ohm
            ScalerSetByte(PB2_3E_TERM_02, 0xAA);

#elif((_D1_DP_Z0_IMPEDANCE_OPTION == _100_OHM) ||\
    ((_D1_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR) && (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_NORMAL)) ||\
    ((_D1_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR) && (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI)))

            // Lane0/2 Z0 Differential Impedance = 0x9
            // Lane1/3 Z0 Differential Impedance = 0x9
            ScalerSetByte(PB2_3C_TERM_00, 0x99);
            ScalerSetByte(PB2_3D_TERM_01, 0x99);

            // reg_term_code_lx => 100ohm
            ScalerSetByte(PB2_3E_TERM_02, 0x55);
#else
            // Lane0/2 Z0 Differential Impedance = 0x9
            // Lane1/3 Z0 Differential Impedance = 0x9
            ScalerSetByte(PB2_3C_TERM_00, 0x99);
            ScalerSetByte(PB2_3D_TERM_01, 0x99);

            // reg_term_code_lx => 90ohm
            ScalerSetByte(PB2_3E_TERM_02, 0xAA);
#endif
            // [7:4] p_channel_en = 1 --> Switch p Channel 50ohm Z0
            // [3:0] n_channel_en = 1 --> Switch n Channel 50ohm Z0
            ScalerSetByte(PB2_11_RX_TOP_17, 0xFF);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(((_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)) || (_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON))
            if(ScalerGetBit(PB2_01_RX_TOP_01, _BIT0) == 0x00)
            {
                // [0] RX_EN = 1'b0 --> Lane0 Disable RX_EN
                // [4] CDR_EN = 1'b0 --> Lnae0 Disable CDR_EN
                ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE0);
            }

            if(ScalerGetBit(PB2_01_RX_TOP_01, _BIT1) == 0x00)
            {
                // [1] RX_EN = 1'b0 --> Lane1 Disable RX_EN
                // [5] CDR_EN = 1'b0 --> Lnae1 Disable CDR_EN
                ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE1);
            }

            if(ScalerGetBit(PB2_01_RX_TOP_01, _BIT2) == 0x00)
            {
                // [2] RX_EN = 1'b0 --> Lane2 Disable RX_EN
                // [6] CDR_EN = 1'b0 --> Lnae2 Disable CDR_EN
                ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE2);
            }

            if(ScalerGetBit(PB2_01_RX_TOP_01, _BIT3) == 0x00)
            {
                // [3] RX_EN = 1'b0 --> Lane3 Disable RX_EN
                // [7] CDR_EN = 1'b0 --> Lnae3 Disable CDR_EN
                ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE3);
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Config Lane Mode of Combo PHY
// Input Value  : Lane Mode, Lane
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx1LaneMode(EnumLaneConfig enumLaneMode, BYTE ucLane)
{
    switch(ucLane)
    {
        case _GDI_PHY_LANE0:

            if(enumLaneMode == _LANE_DP_MODE)
            {
                ScalerSetBit(PB2_01_RX_TOP_01, ~_BIT0, 0x00);
                ScalerSetBit(PB2_02_RX_TOP_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
                ScalerSetBit(P7A_91_DPHY_01, ~_BIT0, 0x00);
            }
            else
            {
                ScalerSetBit(PB2_01_RX_TOP_01, ~_BIT0, _BIT0);
                ScalerSetBit(PB2_02_RX_TOP_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
                ScalerSetBit(P7A_91_DPHY_01, ~_BIT0, _BIT0);
            }

            break;

        case _GDI_PHY_LANE1:

            if(enumLaneMode == _LANE_DP_MODE)
            {
                ScalerSetBit(PB2_01_RX_TOP_01, ~(_BIT6 | _BIT1), 0x00);
                ScalerSetBit(PB2_02_RX_TOP_02, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
            }
            else
            {
                ScalerSetBit(PB2_01_RX_TOP_01, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));
                ScalerSetBit(PB2_02_RX_TOP_02, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
            }

            break;

        case _GDI_PHY_LANE2:

            if(enumLaneMode == _LANE_DP_MODE)
            {
                ScalerSetBit(PB2_01_RX_TOP_01, ~_BIT2, 0x00);
                ScalerSetBit(PB2_02_RX_TOP_02, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
                ScalerSetBit(P7A_91_DPHY_01, ~_BIT1, 0x00);
            }
            else
            {
                ScalerSetBit(PB2_01_RX_TOP_01, ~_BIT2, _BIT2);
                ScalerSetBit(PB2_02_RX_TOP_02, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
                ScalerSetBit(P7A_91_DPHY_01, ~_BIT1, _BIT1);
            }

            break;

        case _GDI_PHY_LANE3:

            if(enumLaneMode == _LANE_DP_MODE)
            {
                ScalerSetBit(PB2_01_RX_TOP_01, ~(_BIT7 | _BIT3), 0x00);
                ScalerSetBit(PB2_02_RX_TOP_02, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
            }
            else
            {
                ScalerSetBit(PB2_01_RX_TOP_01, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
                ScalerSetBit(PB2_02_RX_TOP_02, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Config Lane Power of Combo PHY
// Input Value  : Enable/Disable, Lane
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx1LanePower(bit bEnable, BYTE ucLane)
{
    switch(ucLane)
    {
        case _GDI_PHY_LANE0:

            if(bEnable == _ENABLE)
            {
                ScalerSetBit(PB2_19_LDO_03, ~_BIT4, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT4, _BIT4);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT0, _BIT0);
                DELAY_5US();
                ScalerSetBit(PB2_19_LDO_03, ~_BIT4, _BIT4);
                DELAY_5US();
            }
            else
            {
                ScalerSetBit(PB2_19_LDO_03, ~_BIT4, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT0, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT4, 0x00);
                DELAY_5US();
            }

            break;

        case _GDI_PHY_LANE1:

            if(bEnable == _ENABLE)
            {
                ScalerSetBit(PB2_19_LDO_03, ~_BIT5, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT5, _BIT5);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT1, _BIT1);
                DELAY_5US();
                ScalerSetBit(PB2_19_LDO_03, ~_BIT5, _BIT5);
                DELAY_5US();
            }
            else
            {
                ScalerSetBit(PB2_19_LDO_03, ~_BIT5, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT1, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT5, 0x00);
                DELAY_5US();
            }

            break;

        case _GDI_PHY_LANE2:

            if(bEnable == _ENABLE)
            {
                ScalerSetBit(PB2_19_LDO_03, ~_BIT6, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT6, _BIT6);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT2, _BIT2);
                DELAY_5US();
                ScalerSetBit(PB2_19_LDO_03, ~_BIT6, _BIT6);
                DELAY_5US();
            }
            else
            {
                ScalerSetBit(PB2_19_LDO_03, ~_BIT6, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT2, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT6, 0x00);
                DELAY_5US();
            }

            break;

        case _GDI_PHY_LANE3:

            if(bEnable == _ENABLE)
            {
                ScalerSetBit(PB2_19_LDO_03, ~_BIT7, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT7, _BIT7);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT3, _BIT3);
                DELAY_5US();
                ScalerSetBit(PB2_19_LDO_03, ~_BIT7, _BIT7);
                DELAY_5US();
            }
            else
            {
                ScalerSetBit(PB2_19_LDO_03, ~_BIT7, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT3, 0x00);
                DELAY_5US();
                ScalerSetBit(PB2_00_RX_TOP_00, ~_BIT7, 0x00);
                DELAY_5US();
            }

            break;

        default:
            break;
    }
}
#endif
