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
// ID Code      : ScalerDpPhyRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPPHY__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx/ScalerDpPhyRx.h"




#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
BYTE code tDpPhyRxDP2PresetSelTable[16] =
{
    0, 5, 10, 1, 6, 15, 11, 2, 7, 12, 14, 3, 8, 13, 9, 4
};
#endif


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundRBR;
WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR;
WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR2;
WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR3;
WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR3_9G;

WORD g_usDpPhyRxVCOCountCriteriaUpperBoundRBR;
WORD g_usDpPhyRxVCOCountCriteriaUpperBoundHBR;
WORD g_usDpPhyRxVCOCountCriteriaUpperBoundHBR2;
WORD g_usDpPhyRxVCOCountCriteriaUpperBoundHBR3;
WORD g_usDpPhyRxVCOCountCriteriaUpperBoundHBR3_9G;

WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundRBR;
WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR;
WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR2;
WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR3;
WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR3_9G;

WORD g_usDpPhyRxVCOCountCriteriaLowerBoundRBR;
WORD g_usDpPhyRxVCOCountCriteriaLowerBoundHBR;
WORD g_usDpPhyRxVCOCountCriteriaLowerBoundHBR2;
WORD g_usDpPhyRxVCOCountCriteriaLowerBoundHBR3;
WORD g_usDpPhyRxVCOCountCriteriaLowerBoundHBR3_9G;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR10;
WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR13_5;
WORD g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR20;

WORD g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR10;
WORD g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR13_5;
WORD g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR20;

WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR10;
WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR13_5;
WORD g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR20;

WORD g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR10;
WORD g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR13_5;
WORD g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR20;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Port Dx mapping to Rx
// Input Value  : Input Port
// Output Value : Rx0 or Rx1 or Rx2
//--------------------------------------------------
EnumRx ScalerDpPhyRxDxRxMapping(EnumInputPort enumInputPort)
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
// Description  : Get PHY CDR Clock
// Input Value  : ucNumber
//                SearchPort
// Output Value : PHY CDR Target Clock
//--------------------------------------------------
WORD ScalerDpPhyRxTargetClock(EnumInputPort enumInputPort, BYTE ucNumber)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            return g_pusDpPhyRx0ClockTarget[ucNumber];
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            return g_pusDpPhyRx1ClockTarget[ucNumber];
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            return g_pusDpPhyRx2ClockTarget[ucNumber];
#endif
        default:

            return 0x0000;
    }
}

//--------------------------------------------------
// Description  : DP PHY CTS Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyRxGetPhyCtsFlag(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpPhyRx0GetPhyCtsFlag();
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpPhyRx1GetPhyCtsFlag();
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpPhyRx2GetPhyCtsFlag();
#endif

        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane Mapping
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyRxGetLaneMapping(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    enumDpLane = enumDpLane;

    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
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
BYTE ScalerDpPhyRxGetLanePNSwap(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
{
    enumDpLane = enumDpLane;

    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
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
BYTE ScalerDpPhyRxGetPCBLaneMapping(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
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
BYTE ScalerDpPhyRxGetPCBLanePNSwap(EnumInputPort enumInputPort, EnumDpLane enumDpLane)
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
void ScalerDpPhyRxSetLaneMux(EnumInputPort enumInputPort, EnumDpLane enumDpLane, BYTE ucLaneMapping)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
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
void ScalerDpPhyRxSetLanePNSwap(EnumInputPort enumInputPort, EnumDpLane enumDpLane, BYTE ucPNSwap)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
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
// Description  : DP Phy CTS Control Register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyRxCtsCtrl(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:
            return g_ucDpPhyRx0CtsCtrl;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:
            return g_ucDpPhyRx1CtsCtrl;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:
            return g_ucDpPhyRx2CtsCtrl;
#endif
        default:
            return 0x00;
    }
}

//--------------------------------------------------
// Description  : DP PHY CTS Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxPhyCts(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0PhyCts();

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1PhyCts();

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2PhyCts();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP PHY CTS Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxPhyCtsAutoMode(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0PhyCtsAutoMode();

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1PhyCtsAutoMode();

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2PhyCtsAutoMode();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxPhyInitial(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0PhyInitial();

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1PhyInitial();

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2PhyInitial();

            break;
#endif

#if((_DP_PHY_RX0_SUPPORT == _ON) && (_DP_PHY_RX1_SUPPORT == _ON))
        case _RX7:

            ScalerDpPhyRx0PhyInitial();
            ScalerDpPhyRx1PhyInitial();

            break;
#endif

#if((_DP_PHY_RX1_SUPPORT == _ON) && (_DP_PHY_RX2_SUPPORT == _ON))
        case _RX8:

            ScalerDpPhyRx1PhyInitial();
            ScalerDpPhyRx2PhyInitial();

            break;
#endif

        default:

            break;
    }

    g_usDpPhyRxD10p2CountCriteriaUpperBoundRBR = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_RBR;
    g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR;
    g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR2 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR2;
    g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR3 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3;
    g_usDpPhyRxD10p2CountCriteriaUpperBoundHBR3_9G = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_HBR3_9G;

    g_usDpPhyRxVCOCountCriteriaUpperBoundRBR = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_RBR;
    g_usDpPhyRxVCOCountCriteriaUpperBoundHBR = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR;
    g_usDpPhyRxVCOCountCriteriaUpperBoundHBR2 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR2;
    g_usDpPhyRxVCOCountCriteriaUpperBoundHBR3 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3;
    g_usDpPhyRxVCOCountCriteriaUpperBoundHBR3_9G = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_HBR3_9G;

    g_usDpPhyRxD10p2CountCriteriaLowerBoundRBR = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_RBR;
    g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR;
    g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR2 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR2;
    g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR3 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3;
    g_usDpPhyRxD10p2CountCriteriaLowerBoundHBR3_9G = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_HBR3_9G;

    g_usDpPhyRxVCOCountCriteriaLowerBoundRBR = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_RBR;
    g_usDpPhyRxVCOCountCriteriaLowerBoundHBR = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR;
    g_usDpPhyRxVCOCountCriteriaLowerBoundHBR2 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR2;
    g_usDpPhyRxVCOCountCriteriaLowerBoundHBR3 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3;
    g_usDpPhyRxVCOCountCriteriaLowerBoundHBR3_9G = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_HBR3_9G;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR10 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR10;
    g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR13_5 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR13_5;
    g_usDpPhyRxD10p2CountCriteriaUpperBoundUHBR20 = _DP_RX_RAWDATA_COUNT_D10P2_UPPER_BOUND_1000_UHBR20;

    g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR10 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR10;
    g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR13_5 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR13_5;
    g_usDpPhyRxVCOCountCriteriaUpperBoundUHBR20 = _DP_RX_VCO_COUNT_UPPER_BOUND_1000_UHBR20;

    g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR10 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR10;
    g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR13_5 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR13_5;
    g_usDpPhyRxD10p2CountCriteriaLowerBoundUHBR20 = _DP_RX_RAWDATA_COUNT_D10P2_LOWER_BOUND_1000_UHBR20;

    g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR10 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR10;
    g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR13_5 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR13_5;
    g_usDpPhyRxVCOCountCriteriaLowerBoundUHBR20 = _DP_RX_VCO_COUNT_LOWER_BOUND_1000_UHBR20;
#endif
}

//--------------------------------------------------
// Description  : Lane Swap
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSetAltModeLaneMapping(EnumInputPort enumInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation)
{
    enumPinAssignment = enumPinAssignment;
    enumTypeCOrientation = enumTypeCOrientation;

    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0SetAltModeLaneMapping(enumPinAssignment, enumTypeCOrientation);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1SetAltModeLaneMapping(enumPinAssignment, enumTypeCOrientation);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxRebuildPhy(EnumInputPort enumInputPort, EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0RebuildPhy(enumDpLinkRate, ucDpcdLane);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1RebuildPhy(enumDpLinkRate, ucDpcdLane);

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2RebuildPhy(enumDpLinkRate, ucDpcdLane);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description : Initial Signal check
// Input Value  : DP Link Rate
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSignalDetectInitial(EnumInputPort enumInputPort, BYTE ucDpLinkRate, BYTE ucDpLEQScanValue)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0SignalDetectInitial(ucDpLinkRate, ucDpLEQScanValue);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1SignalDetectInitial(ucDpLinkRate, ucDpLEQScanValue);

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2SignalDetectInitial(ucDpLinkRate, ucDpLEQScanValue);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description : Enable Signal Detection
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRxSignalDetection(EnumInputPort enumInputPort, bit bEnable)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0SignalDetection(bEnable);

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1SignalDetection(bEnable);

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2SignalDetection(bEnable);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpPhyRxDFECheck(EnumInputPort enumInputPort)
{
    bit bReturn = _FALSE;

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpMacDphyRxAuxlessAlpmClrOccurred(enumInputPort);
#endif

    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            bReturn = ScalerDpPhyRx0DFECheck();

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            bReturn = ScalerDpPhyRx1DFECheck();

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            bReturn = ScalerDpPhyRx2DFECheck();

            break;
#endif

        default:
            break;
    }

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpMacDphyRxAuxlessAlpmGetOccurred(enumInputPort) == _TRUE)
    {
        return _TRUE;
    }
    else
#endif
    {
        return bReturn;
    }
}

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpPhyRxEnableEyeMonitor(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            return ScalerDpPhyRx0GetEyeMonitorEnableFlag();
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            return ScalerDpPhyRx1GetEyeMonitorEnableFlag();
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            return ScalerDpPhyRx2GetEyeMonitorEnableFlag();
#endif

        default:

            return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
void ScalerDpPhyRxEyeMonitor(EnumInputPort enumInputPort)
{
    switch(ScalerDpPhyRxDxRxMapping(enumInputPort))
    {
#if(_DP_PHY_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpPhyRx0EyeMonitor();

            break;
#endif

#if(_DP_PHY_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpPhyRx1EyeMonitor();

            break;
#endif

#if(_DP_PHY_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpPhyRx2EyeMonitor();

            break;
#endif

        default:

            break;
    }
}
#endif
