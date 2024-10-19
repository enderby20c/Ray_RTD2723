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
// ID Code      : ScalerDpPhyTx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_DP_PHY_TX_EXINT0__
#include "ScalerFunctionInclude.h"
#include "DpPhyTx/ScalerDpPhyTx.h"
#if(_DP_PHY_TX_SUPPORT == _ON)
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
// Description  : Dp Tx Lane Swap Setting
// Input Value  : Output Port, Pin Assignment, Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(EnumOutputPort enumOutputPort, EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation)
{
    enumOutputPort = enumOutputPort;
    enumTypeCPinCfgType = enumTypeCPinCfgType;
    enumTypeCOrientation = enumTypeCOrientation;

#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if(ScalerTypeCTxGetPortCtrlType_EXINT0(enumOutputPort) == _TYPE_C_PORT_CTRL_EMBEDDED)
    {
        ScalerDpAuxTxPNSwap_EXINT0(enumTypeCOrientation);

        // Main-Link Lane Setting Start
        // BB0E, bit7-6/5-4/3-2/1-0, The Source Selector of Lane0/1/2/3 of Small FIFO.
        // Used for Lane Swap, 00:Lane0, 01:Lane1, 10:Lane2, 11:lane3, Set Lane Swap
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit_EXINT(P2B_06_DPTX_LANE_SWAP, ~(_BIT7 | _BIT6), ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE0_MAPPING) << 6);
        ScalerSetBit_EXINT(P2B_06_DPTX_LANE_SWAP, ~(_BIT5 | _BIT4), ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE1_MAPPING) << 4);
        ScalerSetBit_EXINT(P2B_06_DPTX_LANE_SWAP, ~(_BIT3 | _BIT2), ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE2_MAPPING) << 2);
        ScalerSetBit_EXINT(P2B_06_DPTX_LANE_SWAP, ~(_BIT1 | _BIT0), ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE3_MAPPING));
#endif

        ScalerSetBit_EXINT(PBB_0E_DPTX_LANE_SWAP, ~(_BIT7 | _BIT6), ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE0_MAPPING) << 6);
        ScalerSetBit_EXINT(PBB_0E_DPTX_LANE_SWAP, ~(_BIT5 | _BIT4), ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE1_MAPPING) << 4);
        ScalerSetBit_EXINT(PBB_0E_DPTX_LANE_SWAP, ~(_BIT3 | _BIT2), ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE2_MAPPING) << 2);
        ScalerSetBit_EXINT(PBB_0E_DPTX_LANE_SWAP, ~(_BIT1 | _BIT0), ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE3_MAPPING));
    }
    else
#endif
    {
        ScalerDpAuxTxPNSwap_EXINT0(_TYPE_C_ORIENTATION_UNFLIP);

        // Set Lane Swap
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit_EXINT(P2B_06_DPTX_LANE_SWAP, ~(_BIT7 | _BIT6), _P0_DP_PCB_LANE0_MAPPING << 6);
        ScalerSetBit_EXINT(P2B_06_DPTX_LANE_SWAP, ~(_BIT5 | _BIT4), _P0_DP_PCB_LANE1_MAPPING << 4);
        ScalerSetBit_EXINT(P2B_06_DPTX_LANE_SWAP, ~(_BIT3 | _BIT2), _P0_DP_PCB_LANE2_MAPPING << 2);
        ScalerSetBit_EXINT(P2B_06_DPTX_LANE_SWAP, ~(_BIT1 | _BIT0), _P0_DP_PCB_LANE3_MAPPING);
#endif

        ScalerSetBit_EXINT(PBB_0E_DPTX_LANE_SWAP, ~(_BIT7 | _BIT6), _P0_DP_PCB_LANE0_MAPPING << 6);
        ScalerSetBit_EXINT(PBB_0E_DPTX_LANE_SWAP, ~(_BIT5 | _BIT4), _P0_DP_PCB_LANE1_MAPPING << 4);
        ScalerSetBit_EXINT(PBB_0E_DPTX_LANE_SWAP, ~(_BIT3 | _BIT2), _P0_DP_PCB_LANE2_MAPPING << 2);
        ScalerSetBit_EXINT(PBB_0E_DPTX_LANE_SWAP, ~(_BIT1 | _BIT0), _P0_DP_PCB_LANE3_MAPPING);
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane Mapping
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(EnumTypeCOrientation enumTypecOrientation, BYTE ucDpTypecPcbLaneMapping)
{
    ucDpTypecPcbLaneMapping = ucDpTypecPcbLaneMapping;

    if(enumTypecOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        switch(ucDpTypecPcbLaneMapping)
        {
            case _TYPE_C_RX1:
                return _DP_SCALER_LANE3;

            case _TYPE_C_TX1:
                return _DP_SCALER_LANE2;

            case _TYPE_C_RX2:
                return _DP_SCALER_LANE0;

            default:
            case _TYPE_C_TX2:
                return _DP_SCALER_LANE1;
        }
    }
    else if(enumTypecOrientation == _TYPE_C_ORIENTATION_FLIP)
    {
        switch(ucDpTypecPcbLaneMapping)
        {
            case _TYPE_C_RX1:
                return _DP_SCALER_LANE0;

            case _TYPE_C_TX1:
                return _DP_SCALER_LANE1;

            case _TYPE_C_RX2:
                return _DP_SCALER_LANE3;

            default:
            case _TYPE_C_TX2:
                return _DP_SCALER_LANE2;
        }
    }

    return _DP_SCALER_LANE0;
}
#endif // End for #if(_DP_PHY_TX_SUPPORT == _ON)
