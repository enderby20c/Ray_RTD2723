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
// ID Code      : RL6952_Series_GDIPhyRx2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_GDIPHYRX2__

#include "ScalerFunctionInclude.h"
#include "GDIPhyRx2/ScalerGDIPhyRx2.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_TMDS_PHY_RX2_SUPPORT == _ON) || (_DP_PHY_RX2_SUPPORT == _ON))
//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx2Power(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX2_DP_DPHY, _POWER_CUT_OFF, _POWER_RESET_DISABLE);
            ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX2_DP20_APHY, _POWER_CUT_OFF, _POWER_RESET_DISABLE);

#if((_D2_DP_Z0_IMPEDANCE_OPTION == _85_OHM) ||\
    ((_D2_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR) && (_D2_DP_LINK_CLK_RATE >= _DP_ULTRA_SPEED_1000MHZ)) ||\
    ((_D2_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))

            // Lane0/2 Z0 Differential Impedance = 0x7
            // Lane1/3 Z0 Differential Impedance = 0x7
            ScalerSetByte(PE8_06_Z0_1, 0x77);
            ScalerSetByte(PE8_07_Z0_2, 0x77);

            // Target = 90Ohm - 1 --> 85Ohm
            ScalerSetBit(PE8_09_Z0_4, ~(_BIT1 | _BIT0), _BIT0);

#elif((_D2_DP_Z0_IMPEDANCE_OPTION == _100_OHM) ||\
    ((_D2_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_NORMAL)) ||\
    ((_D2_DP_Z0_IMPEDANCE_OPTION == _BY_CONNECTOR) && (_D2_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI)))

            // Lane0/2 Z0 Differential Impedance = 0x8
            // Lane1/3 Z0 Differential Impedance = 0x8
            ScalerSetByte(PE8_06_Z0_1, 0x88);
            ScalerSetByte(PE8_07_Z0_2, 0x88);

            // Target = 100Ohm
            ScalerSetBit(PE8_09_Z0_4, ~(_BIT1 | _BIT0), 0x00);
#else
            // Lane0/2 Z0 Differential Impedance = 0x8
            // Lane1/3 Z0 Differential Impedance = 0x8
            ScalerSetByte(PE8_06_Z0_1, 0x88);
            ScalerSetByte(PE8_07_Z0_2, 0x88);

            // Target = 90Ohm
            ScalerSetBit(PE8_09_Z0_4, ~(_BIT1 | _BIT0), _BIT0);
#endif
            // [7:4] pn_channel_en = 4'b1111 --> Switch PN Channel On
            ScalerSetByte(PE8_08_Z0_3, 0xFF);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(((_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)) || (_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON))
            // Disable RX_EN, Disable CDR_EN
            ScalerGDIPhyRx2LanePower(_DISABLE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx2LanePower(_DISABLE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx2LanePower(_DISABLE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx2LanePower(_DISABLE, _GDI_PHY_LANE3);

            ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX2_DP20_APHY, _POWER_CUT_ON, _POWER_RESET_ENABLE);
            ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX2_DP_DPHY, _POWER_CUT_ON, _POWER_RESET_ENABLE);
#endif
            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : GDI Rx2 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx2PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx2Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:

            ScalerGDIPhyRx2Z0Switch(_ON);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_PS:

            ScalerGDIPhyRx2Z0Switch(_OFF);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D2 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx2Z0Switch(bit bSelect)
{
    if(bSelect == _ON)
    {
        // Enable Z0
        ScalerSetByte(PE8_08_Z0_3, 0xFF);

        SET_DIGITAL_PORT_SWITCH_TO_D2();
    }
    else
    {
#if(_TMDS_PHY_RX2_SUPPORT == _ON)
        // Disable Z0
        ScalerSetByte(PE8_08_Z0_3, 0x00);
#endif

        CLR_DIGITAL_PORT_SWITCH_TO_D2();
    }
}

//--------------------------------------------------
// Description  : Config Lane Power of Combo PHY
// Input Value  : Enable/Disable, Lane
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx2LanePower(bit bEnable, BYTE ucLane)
{
    switch(ucLane)
    {
        case _GDI_PHY_LANE0:

            if(bEnable == _ENABLE)
            {
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT0, _BIT0);
                DELAY_5US();
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT4, _BIT4);
                DELAY_5US();
            }
            else
            {
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT4, 0x00);
                DELAY_5US();
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT0, 0x00);
                DELAY_5US();
            }

            break;

        case _GDI_PHY_LANE1:

            if(bEnable == _ENABLE)
            {
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT1, _BIT1);
                DELAY_5US();
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT5, _BIT5);
                DELAY_5US();
            }
            else
            {
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT5, 0x00);
                DELAY_5US();
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT1, 0x00);
                DELAY_5US();
            }

            break;

        case _GDI_PHY_LANE2:

            if(bEnable == _ENABLE)
            {
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT2, _BIT2);
                DELAY_5US();
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT6, _BIT6);
                DELAY_5US();
            }
            else
            {
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT6, 0x00);
                DELAY_5US();
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT2, 0x00);
                DELAY_5US();
            }

            break;

        case _GDI_PHY_LANE3:

            if(bEnable == _ENABLE)
            {
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT3, _BIT3);
                DELAY_5US();
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT7, _BIT7);
                DELAY_5US();
            }
            else
            {
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT7, 0x00);
                DELAY_5US();
                ScalerSetBit(PE8_0B_RX_ENABLE, ~_BIT3, 0x00);
                DELAY_5US();
            }

            break;

        default:
            break;
    }
}
#endif
