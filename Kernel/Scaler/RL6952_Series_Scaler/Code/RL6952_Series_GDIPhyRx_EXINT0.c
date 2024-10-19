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
// ID Code      : RL6952_Series_GDIPhyRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_GDIPHY_EXINT0__

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
EnumRx ScalerGDIPhyRxDxRxMapping_EXINT0(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

    enumInputPort = enumInputPort;

#if(_DP_SUPPORT == _ON)
    if((enumRx = ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort)) != _RX_MAP_NONE)
    {
        return enumRx;
    }
#endif

#if(_HDMI_SUPPORT == _ON)
    if((enumRx = ScalerTmdsPhyRxDxRxMapping_EXINT0(enumInputPort)) != _RX_MAP_NONE)
    {
        return enumRx;
    }
#endif

    return enumRx;
}

//--------------------------------------------------
// Description  : Input Port, Config Lane Mode of Combo PHY
// Input Value  : Lane Mode, Lane
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRxLaneMode_EXINT0(EnumInputPort enumInputPort, EnumLaneConfig enumLaneMode, BYTE ucLane)
{
    enumLaneMode = enumLaneMode;
    ucLane = ucLane;

    switch(ScalerGDIPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if((_TMDS_PHY_RX0_SUPPORT == _ON) || (_DP_PHY_RX0_SUPPORT == _ON))
        case _RX0:

            switch(ucLane)
            {
                case _GDI_PHY_LANE0:

                    if(enumLaneMode == _LANE_DP_MODE)
                    {
                        ScalerSetBit_EXINT(P29_01_RX_TOP_01, ~_BIT0, 0x00);
                        ScalerSetBit_EXINT(P29_02_RX_TOP_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
                        ScalerSetBit_EXINT(P1C_91_DPHY_01, ~_BIT0, 0x00);
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P29_01_RX_TOP_01, ~_BIT0, _BIT0);
                        ScalerSetBit_EXINT(P29_02_RX_TOP_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
                        ScalerSetBit_EXINT(P1C_91_DPHY_01, ~_BIT0, _BIT0);
                    }

                    break;

                case _GDI_PHY_LANE1:

                    if(enumLaneMode == _LANE_DP_MODE)
                    {
                        ScalerSetBit_EXINT(P29_01_RX_TOP_01, ~(_BIT6 | _BIT1), 0x00);
                        ScalerSetBit_EXINT(P29_02_RX_TOP_02, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P29_01_RX_TOP_01, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));
                        ScalerSetBit_EXINT(P29_02_RX_TOP_02, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
                    }

                    break;

                case _GDI_PHY_LANE2:

                    if(enumLaneMode == _LANE_DP_MODE)
                    {
                        ScalerSetBit_EXINT(P29_01_RX_TOP_01, ~_BIT2, 0x00);
                        ScalerSetBit_EXINT(P29_02_RX_TOP_02, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
                        ScalerSetBit_EXINT(P1C_91_DPHY_01, ~_BIT1, 0x00);
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P29_01_RX_TOP_01, ~_BIT2, _BIT2);
                        ScalerSetBit_EXINT(P29_02_RX_TOP_02, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
                        ScalerSetBit_EXINT(P1C_91_DPHY_01, ~_BIT1, _BIT1);
                    }

                    break;

                case _GDI_PHY_LANE3:

                    if(enumLaneMode == _LANE_DP_MODE)
                    {
                        ScalerSetBit_EXINT(P29_01_RX_TOP_01, ~(_BIT7 | _BIT3), 0x00);
                        ScalerSetBit_EXINT(P29_02_RX_TOP_02, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P29_01_RX_TOP_01, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
                        ScalerSetBit_EXINT(P29_02_RX_TOP_02, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
                    }

                    break;
                default:
                    break;
            }

            break;
#endif
#if((_TMDS_PHY_RX1_SUPPORT == _ON) || (_DP_PHY_RX1_SUPPORT == _ON))
        case _RX1:

            switch(ucLane)
            {
                case _GDI_PHY_LANE0:

                    if(enumLaneMode == _LANE_DP_MODE)
                    {
                        ScalerSetBit_EXINT(PB2_01_RX_TOP_01, ~_BIT0, 0x00);
                        ScalerSetBit_EXINT(PB2_02_RX_TOP_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
                        ScalerSetBit_EXINT(P7A_91_DPHY_01, ~_BIT0, 0x00);
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PB2_01_RX_TOP_01, ~_BIT0, _BIT0);
                        ScalerSetBit_EXINT(PB2_02_RX_TOP_02, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
                        ScalerSetBit_EXINT(P7A_91_DPHY_01, ~_BIT0, _BIT0);
                    }

                    break;

                case _GDI_PHY_LANE1:

                    if(enumLaneMode == _LANE_DP_MODE)
                    {
                        ScalerSetBit_EXINT(PB2_01_RX_TOP_01, ~(_BIT6 | _BIT1), 0x00);
                        ScalerSetBit_EXINT(PB2_02_RX_TOP_02, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PB2_01_RX_TOP_01, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));
                        ScalerSetBit_EXINT(PB2_02_RX_TOP_02, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
                    }

                    break;

                case _GDI_PHY_LANE2:

                    if(enumLaneMode == _LANE_DP_MODE)
                    {
                        ScalerSetBit_EXINT(PB2_01_RX_TOP_01, ~_BIT2, 0x00);
                        ScalerSetBit_EXINT(PB2_02_RX_TOP_02, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
                        ScalerSetBit_EXINT(P7A_91_DPHY_01, ~_BIT1, 0x00);
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PB2_01_RX_TOP_01, ~_BIT2, _BIT2);
                        ScalerSetBit_EXINT(PB2_02_RX_TOP_02, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
                        ScalerSetBit_EXINT(P7A_91_DPHY_01, ~_BIT1, _BIT1);
                    }

                    break;

                case _GDI_PHY_LANE3:

                    if(enumLaneMode == _LANE_DP_MODE)
                    {
                        ScalerSetBit_EXINT(PB2_01_RX_TOP_01, ~(_BIT7 | _BIT3), 0x00);
                        ScalerSetBit_EXINT(PB2_02_RX_TOP_02, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PB2_01_RX_TOP_01, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
                        ScalerSetBit_EXINT(PB2_02_RX_TOP_02, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
                    }

                    break;
                default:
                    break;
            }

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Config Lane Power of Combo PHY
// Input Value  : Enable/Disable, Lane
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRxLanePower_EXINT0(EnumInputPort enumInputPort, bit bEnable, BYTE ucLane)
{
    switch(ScalerGDIPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
        case _RX0:

            switch(ucLane)
            {
                case _GDI_PHY_LANE0:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT4, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT4, _BIT4);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT0, _BIT0);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT4, _BIT4);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT4, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT0, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT4, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE1:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT5, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT5, _BIT5);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT1, _BIT1);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT5, _BIT5);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT5, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT1, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT5, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE2:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT6, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT6, _BIT6);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT2, _BIT2);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT6, _BIT6);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT6, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT2, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT6, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE3:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT7, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT7, _BIT7);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT3, _BIT3);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT7, _BIT7);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P29_19_LDO_03, ~_BIT7, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT3, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(P29_00_RX_TOP_00, ~_BIT7, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                default:
                    break;
            }

            break;

        case _RX1:

            switch(ucLane)
            {
                case _GDI_PHY_LANE0:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT4, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT4, _BIT4);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT0, _BIT0);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT4, _BIT4);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT4, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT0, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT4, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE1:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT5, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT5, _BIT5);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT1, _BIT1);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT5, _BIT5);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT5, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT1, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT5, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE2:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT6, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT6, _BIT6);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT2, _BIT2);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT6, _BIT6);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT6, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT2, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT6, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE3:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT7, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT7, _BIT7);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT3, _BIT3);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT7, _BIT7);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PB2_19_LDO_03, ~_BIT7, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT3, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PB2_00_RX_TOP_00, ~_BIT7, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                default:
                    break;
            }

            break;

        case _RX2:

            switch(ucLane)
            {
                case _GDI_PHY_LANE0:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT0, _BIT0);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT4, _BIT4);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT4, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT0, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE1:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT1, _BIT1);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT5, _BIT5);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT5, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT1, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE2:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT2, _BIT2);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT6, _BIT6);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT6, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT2, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                case _GDI_PHY_LANE3:

                    if(bEnable == _ENABLE)
                    {
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT3, _BIT3);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT7, _BIT7);
                        DELAY_5US_EXINT();
                    }
                    else
                    {
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT7, 0x00);
                        DELAY_5US_EXINT();
                        ScalerSetBit_EXINT(PE8_0B_RX_ENABLE, ~_BIT3, 0x00);
                        DELAY_5US_EXINT();
                    }

                    break;

                default:
                    break;
            }

            break;

        default:

            break;
    }
}


