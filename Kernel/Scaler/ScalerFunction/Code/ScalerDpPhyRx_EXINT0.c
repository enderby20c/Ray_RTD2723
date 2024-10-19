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
// ID Code      : ScalerDpPhyRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPPHY_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx/ScalerDpPhyRx.h"




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
// Description  : DP Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx1 or Rx2 or Rx3
//--------------------------------------------------
EnumRx ScalerDpPhyRxDxRxMapping_EXINT0(EnumInputPort enumInputPort)
{
    EnumRx enumRx = _RX_MAP_NONE;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(enumInputPort == _D9_INPUT_PORT)
    {
        enumInputPort = GET_DP_MST_RX_PXP_INPUT_PORT();
    }
#endif

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            enumRx = _HW_D0_DP_PHY_RX_MAPPING;
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            enumRx = _HW_D1_DP_PHY_RX_MAPPING;
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            enumRx = _HW_D2_DP_PHY_RX_MAPPING;
            break;
#endif

#if(_D7_DP_SUPPORT == _ON)
        case _D7_INPUT_PORT:
            enumRx = _HW_D7_DP_PHY_RX_MAPPING;
            break;
#endif

#if(_D8_DP_SUPPORT == _ON)
        case _D8_INPUT_PORT:
            enumRx = _HW_D8_DP_PHY_RX_MAPPING;
            break;
#endif

        default:

            break;
    }

    return enumRx;
}

//--------------------------------------------------
// Description  : Lane Swap
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation)
{
    enumPinAssignment = enumPinAssignment;
    enumTypeCOrientation = enumTypeCOrientation;

    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0SetAltModeLaneMapping_EXINT0(enumPinAssignment, enumTypeCOrientation);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1SetAltModeLaneMapping_EXINT0(enumPinAssignment, enumTypeCOrientation);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Signal Detect Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpPhyRxTp1SignalDetectCheck_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLaneSel)
{
    ucDpLaneSel = ucDpLaneSel;

    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpPhyRx0Tp1SignalDetectCheck_EXINT0(ucDpLaneSel);
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpPhyRx1Tp1SignalDetectCheck_EXINT0(ucDpLaneSel);
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpPhyRx2Tp1SignalDetectCheck_EXINT0(ucDpLaneSel);
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get PHY CTS Test Lane
// Input Value  : SearchPort
// Output Value : PHY CTS Test Lane
//--------------------------------------------------
BYTE ScalerDpPhyRxGetPhyCtsTestLane_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            return (g_ucDpPhyRx0CtsCtrl & (_BIT5 | _BIT4));
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            return (g_ucDpPhyRx1CtsCtrl & (_BIT5 | _BIT4));
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            return (g_ucDpPhyRx2CtsCtrl & (_BIT5 | _BIT4));
#endif
        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get PHY CTS Test Link Rate
// Input Value  : SearchPort
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSetPhyCtsTestLinkRate_EXINT0(EnumInputPort enumInputPort, EnumDpLinkRate enumDpLinkRate)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            switch(enumDpLinkRate)
            {
                case _DP_LINK_HBR3:

                    g_ucDpPhyRx0CtsCtrl = ((g_ucDpPhyRx0CtsCtrl & 0x3F) | (_BIT7 | _BIT6));

                    break;

                case _DP_LINK_HBR2:

                    g_ucDpPhyRx0CtsCtrl = ((g_ucDpPhyRx0CtsCtrl & 0x3F) | _BIT7);

                    break;

                case _DP_LINK_HBR:

                    g_ucDpPhyRx0CtsCtrl = ((g_ucDpPhyRx0CtsCtrl & 0x3F) | _BIT6);

                    break;

                default:
                case _DP_LINK_RBR:

                    g_ucDpPhyRx0CtsCtrl = (g_ucDpPhyRx0CtsCtrl & 0x3F);

                    break;
            }

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            switch(enumDpLinkRate)
            {
                case _DP_LINK_HBR3:

                    g_ucDpPhyRx1CtsCtrl = ((g_ucDpPhyRx1CtsCtrl & 0x3F) | (_BIT7 | _BIT6));

                    break;

                case _DP_LINK_HBR2:

                    g_ucDpPhyRx1CtsCtrl = ((g_ucDpPhyRx1CtsCtrl & 0x3F) | _BIT7);

                    break;

                case _DP_LINK_HBR:

                    g_ucDpPhyRx1CtsCtrl = ((g_ucDpPhyRx1CtsCtrl & 0x3F) | _BIT6);

                    break;

                default:
                case _DP_LINK_RBR:

                    g_ucDpPhyRx1CtsCtrl = (g_ucDpPhyRx1CtsCtrl & 0x3F);

                    break;
            }

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            switch(enumDpLinkRate)
            {
                case _DP_LINK_HBR3:

                    g_ucDpPhyRx2CtsCtrl = ((g_ucDpPhyRx2CtsCtrl & 0x3F) | (_BIT7 | _BIT6));

                    break;

                case _DP_LINK_HBR2:

                    g_ucDpPhyRx2CtsCtrl = ((g_ucDpPhyRx2CtsCtrl & 0x3F) | _BIT7);

                    break;

                case _DP_LINK_HBR:

                    g_ucDpPhyRx2CtsCtrl = ((g_ucDpPhyRx2CtsCtrl & 0x3F) | _BIT6);

                    break;

                default:
                case _DP_LINK_RBR:

                    g_ucDpPhyRx2CtsCtrl = (g_ucDpPhyRx2CtsCtrl & 0x3F);

                    break;
            }

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set PHY CTS Test Lane
// Input Value  : SearchPort, Test Lane
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSetPhyCtsTestLane_EXINT0(EnumInputPort enumInputPort, BYTE ucTestLane)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            switch(ucTestLane)
            {
                default:
                case 0x00: // Source Lane0

                    g_ucDpPhyRx0CtsCtrl = ((g_ucDpPhyRx0CtsCtrl & 0xCF) | (_DP_PHY_RX0_D0_LANE0 << 4));

                    break;

                case 0x10: // Source Lane1

                    g_ucDpPhyRx0CtsCtrl = ((g_ucDpPhyRx0CtsCtrl & 0xCF) | (_DP_PHY_RX0_D0_LANE1 << 4));

                    break;

                case 0x20: // Source Lane2

                    g_ucDpPhyRx0CtsCtrl = ((g_ucDpPhyRx0CtsCtrl & 0xCF) | (_DP_PHY_RX0_D0_LANE2 << 4));

                    break;

                case 0x30: // Source Lane3

                    g_ucDpPhyRx0CtsCtrl = ((g_ucDpPhyRx0CtsCtrl & 0xCF) | (_DP_PHY_RX0_D0_LANE3 << 4));

                    break;
            }

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            switch(ucTestLane)
            {
                default:
                case 0x00: // Source Lane0

                    g_ucDpPhyRx1CtsCtrl = ((g_ucDpPhyRx1CtsCtrl & 0xCF) | (_DP_PHY_RX1_D1_LANE0 << 4));

                    break;

                case 0x10: // Source Lane1

                    g_ucDpPhyRx1CtsCtrl = ((g_ucDpPhyRx1CtsCtrl & 0xCF) | (_DP_PHY_RX1_D1_LANE1 << 4));

                    break;

                case 0x20: // Source Lane2

                    g_ucDpPhyRx1CtsCtrl = ((g_ucDpPhyRx1CtsCtrl & 0xCF) | (_DP_PHY_RX1_D1_LANE2 << 4));

                    break;

                case 0x30: // Source Lane3

                    g_ucDpPhyRx1CtsCtrl = ((g_ucDpPhyRx1CtsCtrl & 0xCF) | (_DP_PHY_RX1_D1_LANE3 << 4));

                    break;
            }

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            switch(ucTestLane)
            {
                default:
                case 0x00: // Source Lane0

                    g_ucDpPhyRx2CtsCtrl = ((g_ucDpPhyRx2CtsCtrl & 0xCF) | (_DP_PHY_RX2_D2_LANE0 << 4));

                    break;

                case 0x10: // Source Lane1

                    g_ucDpPhyRx2CtsCtrl = ((g_ucDpPhyRx2CtsCtrl & 0xCF) | (_DP_PHY_RX2_D2_LANE1 << 4));

                    break;

                case 0x20: // Source Lane2

                    g_ucDpPhyRx2CtsCtrl = ((g_ucDpPhyRx2CtsCtrl & 0xCF) | (_DP_PHY_RX2_D2_LANE2 << 4));

                    break;

                case 0x30: // Source Lane3

                    g_ucDpPhyRx2CtsCtrl = ((g_ucDpPhyRx2CtsCtrl & 0xCF) | (_DP_PHY_RX2_D2_LANE3 << 4));

                    break;
            }

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane Mapping
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyRxGetLaneMapping_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    enumDpLane = enumDpLane;

    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _DP_PHY_RX0_D0_LANE3;

                case _DP_LANE_2:
                    return _DP_PHY_RX0_D0_LANE2;

                case _DP_LANE_1:
                    return _DP_PHY_RX0_D0_LANE1;

                default:
                case _DP_LANE_0:
                    return _DP_PHY_RX0_D0_LANE0;
            }
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _DP_PHY_RX1_D1_LANE3;

                case _DP_LANE_2:
                    return _DP_PHY_RX1_D1_LANE2;

                case _DP_LANE_1:
                    return _DP_PHY_RX1_D1_LANE1;

                default:
                case _DP_LANE_0:
                    return _DP_PHY_RX1_D1_LANE0;
            }
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _DP_PHY_RX2_D2_LANE3;

                case _DP_LANE_2:
                    return _DP_PHY_RX2_D2_LANE2;

                case _DP_LANE_1:
                    return _DP_PHY_RX2_D2_LANE1;

                default:
                case _DP_LANE_0:
                    return _DP_PHY_RX2_D2_LANE0;
            }
#endif

        default:
            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane PN Swap
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyRxGetLanePNSwap_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    enumDpLane = enumDpLane;

    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return GET_DP_PHY_RX0_PCB_LANE3_PN_SWAP();

                case _DP_LANE_2:
                    return GET_DP_PHY_RX0_PCB_LANE2_PN_SWAP();

                case _DP_LANE_1:
                    return GET_DP_PHY_RX0_PCB_LANE1_PN_SWAP();

                default:
                case _DP_LANE_0:
                    return GET_DP_PHY_RX0_PCB_LANE0_PN_SWAP();
            }
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return GET_DP_PHY_RX1_PCB_LANE3_PN_SWAP();

                case _DP_LANE_2:
                    return GET_DP_PHY_RX1_PCB_LANE2_PN_SWAP();

                case _DP_LANE_1:
                    return GET_DP_PHY_RX1_PCB_LANE1_PN_SWAP();

                default:
                case _DP_LANE_0:
                    return GET_DP_PHY_RX1_PCB_LANE0_PN_SWAP();
            }
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return GET_DP_PHY_RX2_PCB_LANE3_PN_SWAP();

                case _DP_LANE_2:
                    return GET_DP_PHY_RX2_PCB_LANE2_PN_SWAP();

                case _DP_LANE_1:
                    return GET_DP_PHY_RX2_PCB_LANE1_PN_SWAP();

                default:
                case _DP_LANE_0:
                    return GET_DP_PHY_RX2_PCB_LANE0_PN_SWAP();
            }
#endif

        default:
            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane Mapping
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyRxGetPCBLaneMapping_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    enumDpLane = enumDpLane;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _D0_DP_PCB_LANE3_MAPPING;

                case _DP_LANE_2:
                    return _D0_DP_PCB_LANE2_MAPPING;

                case _DP_LANE_1:
                    return _D0_DP_PCB_LANE1_MAPPING;

                default:
                case _DP_LANE_0:
                    return _D0_DP_PCB_LANE0_MAPPING;
            }
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _D1_DP_PCB_LANE3_MAPPING;

                case _DP_LANE_2:
                    return _D1_DP_PCB_LANE2_MAPPING;

                case _DP_LANE_1:
                    return _D1_DP_PCB_LANE1_MAPPING;

                default:
                case _DP_LANE_0:
                    return _D1_DP_PCB_LANE0_MAPPING;
            }
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _D2_DP_PCB_LANE3_MAPPING;

                case _DP_LANE_2:
                    return _D2_DP_PCB_LANE2_MAPPING;

                case _DP_LANE_1:
                    return _D2_DP_PCB_LANE1_MAPPING;

                default:
                case _DP_LANE_0:
                    return _D2_DP_PCB_LANE0_MAPPING;
            }
#endif

        default:
            return 0x01;
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane PN Swap
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    enumDpLane = enumDpLane;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _D0_DP_PCB_LANE3_PN_SWAP;

                case _DP_LANE_2:
                    return _D0_DP_PCB_LANE2_PN_SWAP;

                case _DP_LANE_1:
                    return _D0_DP_PCB_LANE1_PN_SWAP;

                default:
                case _DP_LANE_0:
                    return _D0_DP_PCB_LANE0_PN_SWAP;
            }
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _D1_DP_PCB_LANE3_PN_SWAP;

                case _DP_LANE_2:
                    return _D1_DP_PCB_LANE2_PN_SWAP;

                case _DP_LANE_1:
                    return _D1_DP_PCB_LANE1_PN_SWAP;

                default:
                case _DP_LANE_0:
                    return _D1_DP_PCB_LANE0_PN_SWAP;
            }
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    return _D2_DP_PCB_LANE3_PN_SWAP;

                case _DP_LANE_2:
                    return _D2_DP_PCB_LANE2_PN_SWAP;

                case _DP_LANE_1:
                    return _D2_DP_PCB_LANE1_PN_SWAP;

                default:
                case _DP_LANE_0:
                    return _D2_DP_PCB_LANE0_PN_SWAP;
            }
#endif

        default:
            return 0x00;
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane Mapping
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSetLaneMux_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane, BYTE ucLaneMapping)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    SET_DP_PHY_RX0_PCB_LANE3_MAPPING(ucLaneMapping);
                    break;

                case _DP_LANE_2:
                    SET_DP_PHY_RX0_PCB_LANE2_MAPPING(ucLaneMapping);
                    break;

                case _DP_LANE_1:
                    SET_DP_PHY_RX0_PCB_LANE1_MAPPING(ucLaneMapping);
                    break;

                default:
                case _DP_LANE_0:
                    SET_DP_PHY_RX0_PCB_LANE0_MAPPING(ucLaneMapping);
                    break;
            }

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    SET_DP_PHY_RX1_PCB_LANE3_MAPPING(ucLaneMapping);
                    break;

                case _DP_LANE_2:
                    SET_DP_PHY_RX1_PCB_LANE2_MAPPING(ucLaneMapping);
                    break;

                case _DP_LANE_1:
                    SET_DP_PHY_RX1_PCB_LANE1_MAPPING(ucLaneMapping);
                    break;

                default:
                case _DP_LANE_0:
                    SET_DP_PHY_RX1_PCB_LANE0_MAPPING(ucLaneMapping);
                    break;
            }

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    SET_DP_PHY_RX2_PCB_LANE3_MAPPING(ucLaneMapping);
                    break;

                case _DP_LANE_2:
                    SET_DP_PHY_RX2_PCB_LANE2_MAPPING(ucLaneMapping);
                    break;

                case _DP_LANE_1:
                    SET_DP_PHY_RX2_PCB_LANE1_MAPPING(ucLaneMapping);
                    break;

                default:
                case _DP_LANE_0:
                    SET_DP_PHY_RX2_PCB_LANE0_MAPPING(ucLaneMapping);
                    break;
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane PN Swap
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSetLanePNSwap_EXINT0(EnumInputPort enumInputPort, EnumDpLane enumDpLane, BYTE ucPNSwap)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    SET_DP_PHY_RX0_PCB_LANE3_PN_SWAP(ucPNSwap);
                    break;

                case _DP_LANE_2:
                    SET_DP_PHY_RX0_PCB_LANE2_PN_SWAP(ucPNSwap);
                    break;

                case _DP_LANE_1:
                    SET_DP_PHY_RX0_PCB_LANE1_PN_SWAP(ucPNSwap);
                    break;

                default:
                case _DP_LANE_0:
                    SET_DP_PHY_RX0_PCB_LANE0_PN_SWAP(ucPNSwap);
                    break;
            }

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    SET_DP_PHY_RX1_PCB_LANE3_PN_SWAP(ucPNSwap);
                    break;

                case _DP_LANE_2:
                    SET_DP_PHY_RX1_PCB_LANE2_PN_SWAP(ucPNSwap);
                    break;

                case _DP_LANE_1:
                    SET_DP_PHY_RX1_PCB_LANE1_PN_SWAP(ucPNSwap);
                    break;

                default:
                case _DP_LANE_0:
                    SET_DP_PHY_RX1_PCB_LANE0_PN_SWAP(ucPNSwap);
                    break;
            }

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            switch(enumDpLane)
            {
                case _DP_LANE_3:
                    SET_DP_PHY_RX2_PCB_LANE3_PN_SWAP(ucPNSwap);
                    break;

                case _DP_LANE_2:
                    SET_DP_PHY_RX2_PCB_LANE2_PN_SWAP(ucPNSwap);
                    break;

                case _DP_LANE_1:
                    SET_DP_PHY_RX2_PCB_LANE1_PN_SWAP(ucPNSwap);
                    break;

                default:
                case _DP_LANE_0:
                    SET_DP_PHY_RX2_PCB_LANE0_PN_SWAP(ucPNSwap);
                    break;
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxTp1SetPhy_EXINT0(EnumInputPort enumInputPort, EnumDpNFCodeRef enumDpNFCodeRef)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0Tp1SetPhy_EXINT0(enumDpNFCodeRef);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1Tp1SetPhy_EXINT0(enumDpNFCodeRef);

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2Tp1SetPhy_EXINT0(enumDpNFCodeRef);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxTp2SetPhy_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0Tp2SetPhy_EXINT0();

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1Tp2SetPhy_EXINT0();

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2Tp2SetPhy_EXINT0();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxTp3SetPhy_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0Tp3SetPhy_EXINT0();

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1Tp3SetPhy_EXINT0();

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2Tp3SetPhy_EXINT0();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Reset in TP2
// Input Value  : Input Port, TP2 Result
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxResetCDR_EXINT0(EnumInputPort enumInputPort, BYTE ucTp2Result)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0ResetCDR_EXINT0(ucTp2Result);
            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1ResetCDR_EXINT0(ucTp2Result);
            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2ResetCDR_EXINT0(ucTp2Result);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxPhyCtsTp1SetPhy_EXINT0(EnumInputPort enumInputPort, EnumDpNFCodeRef enumDpNFCodeRef)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0PhyCtsTp1SetPhy_EXINT0(enumDpNFCodeRef);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1PhyCtsTp1SetPhy_EXINT0(enumDpNFCodeRef);

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2PhyCtsTp1SetPhy_EXINT0(enumDpNFCodeRef);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxPhyCtsTp2SetPhy_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0PhyCtsTp2SetPhy_EXINT0();

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1PhyCtsTp2SetPhy_EXINT0();

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2PhyCtsTp2SetPhy_EXINT0();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description : check DFE Coef in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpPhyRxDFECheck_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpPhyRx0DFECheck_EXINT0();
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpPhyRx1DFECheck_EXINT0();
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpPhyRx2DFECheck_EXINT0();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description : check DFE Coef in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpPhyRxGetTp2LE_EXINT0(EnumInputPort enumInputPort, BYTE ucDpLaneSel)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            return g_pucDpPhyRx0LE[ucDpLaneSel];
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            return g_pucDpPhyRx1LE[ucDpLaneSel];
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            return g_pucDpPhyRx2LE[ucDpLaneSel];
#endif

        default:

            return 0x00;
    }
}

//--------------------------------------------------
// Description : Enable Signal Detection
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSignalDetection_EXINT0(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpPhyRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0SignalDetection_EXINT0(bEnable);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1SignalDetection_EXINT0(bEnable);

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2SignalDetection_EXINT0(bEnable);

            break;
#endif

        default:

            break;
    }
}


#endif
