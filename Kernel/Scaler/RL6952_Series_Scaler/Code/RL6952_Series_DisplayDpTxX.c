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
// ID Code      : RL6952_Series_DisplayDpTxX.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DisplayDpTx/ScalerDisplayDpTx.h"

#if(_DISPLAY_DP_TXX_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tDISPLAY_DPTXX_DRV_RBR_HBR_TABLE[48] =
{
    // Pre-emphasis->     0                  1                    2                    3
    // VoltageSwing
    /*    0    */        0x1A, 0x00,     0x14, 0x03,     0x0C, 0x07,     0x03, 0x0C,
    /*    1    */        0x14, 0x00,     0x0C, 0x04,     0x03, 0x09,     0x03, 0x09,
    /*    2    */        0x0C, 0x00,     0x03, 0x05,     0x03, 0x05,     0x03, 0x05,
    /*    3    */        0x03, 0x00,     0x03, 0x00,     0x03, 0x00,     0x03, 0x00,
};

BYTE code tDISPLAY_DPTXX_DRV_HBR2_TABLE[48] =
{
    // Pre-emphasis->        0                    1                    2                    3
    // VoltageSwing
    /*    0    */        0x1A, 0x00,     0x14, 0x03,     0x0C, 0x07,     0x03, 0x0C,
    /*    1    */        0x14, 0x00,     0x0C, 0x04,     0x03, 0x09,     0x03, 0x09,
    /*    2    */        0x0C, 0x00,     0x03, 0x05,     0x03, 0x05,     0x03, 0x05,
    /*    3    */        0x03, 0x00,     0x03, 0x00,     0x02, 0x00,     0x02, 0x00,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxXSetSignalLevel(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis)
{
    BYTE ucIndex = 0x00;
    BYTE *pucTable = 0x00;

#if(_PANEL_DPTX_SET_LT_SIGNAL_LEVEL_MODE == _PANEL_DPTX_LT_MANUAL_MODE)
    ucVoltageSwing = GET_PANEL_DPTX_SWING_LEVEL();
    ucPreEmphasis = GET_PANEL_DPTX_PREEMPHASIS_LEVEL();
#endif

    // Protect Wrong table
    if(ucVoltageSwing + ucPreEmphasis > 3)
    {
        if(ucVoltageSwing < 4)
        {
            ucPreEmphasis = 3 - ucVoltageSwing;
        }
        else
        {
            ucVoltageSwing = 3;
            ucPreEmphasis = 0;
        }
    }

    // ucIndex = (ucVoltageSwing * 4 + ucPreEmphasis) * 3;
    ucIndex = (ucVoltageSwing * 4 + ucPreEmphasis) * 2;

    if(ucPreEmphasis > 0)
    {
        if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
        {
            // Port 1
            Scaler32SetBit(PB58060_04_DP14_TX_EM_EN0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
        {
            // Port 2
            Scaler32SetBit(PB58060_04_DP14_TX_EM_EN0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        }
    }
    else
    {
        if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
        {
            // Port 1
            Scaler32SetBit(PB58060_04_DP14_TX_EM_EN0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
        else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
        {
            // Port 2
            Scaler32SetBit(PB58060_04_DP14_TX_EM_EN0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        }
    }

    if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
    {
        pucTable = tDISPLAY_DPTXX_DRV_HBR2_TABLE;
    }
    else
    {
        pucTable = tDISPLAY_DPTXX_DRV_RBR_HBR_TABLE;
    }

    switch(enumLaneX)
    {
        case _DISPLAY_DP_TX_LANE_0: // VTX_lane0

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                // Port1  Swing / Preemphasis
                Scaler32SetByte(PB58060_10_DP14_TX_IB_DRV_CH0, 0x00, (pucTable[ucIndex + 0]));
                Scaler32SetByte(PB58060_20_DP14_TX_EM_DRV_CH0, 0x00, (pucTable[ucIndex + 1]));
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                // Port2  Swing / Preemphasis
                Scaler32SetByte(PB58060_14_DP14_TX_IB_DRV_CH4, 0x00, (pucTable[ucIndex + 0]));
                Scaler32SetByte(PB58060_24_DP14_TX_EM_DRV_CH4, 0x00, (pucTable[ucIndex + 1]));
            }

            break;

        case _DISPLAY_DP_TX_LANE_1: // VTX_lane1

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                // Port1  Swing / Preemphasis
                Scaler32SetByte(PB58060_10_DP14_TX_IB_DRV_CH0, 0x01, (pucTable[ucIndex + 0]));
                Scaler32SetByte(PB58060_20_DP14_TX_EM_DRV_CH0, 0x01, (pucTable[ucIndex + 1]));
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                // Port2  Swing / Preemphasis
                Scaler32SetByte(PB58060_14_DP14_TX_IB_DRV_CH4, 0x01, (pucTable[ucIndex + 0]));
                Scaler32SetByte(PB58060_24_DP14_TX_EM_DRV_CH4, 0x01, (pucTable[ucIndex + 1]));
            }

            break;

        case _DISPLAY_DP_TX_LANE_2: // VTX_lane2

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                // Port1  Swing / Preemphasis
                Scaler32SetByte(PB58060_10_DP14_TX_IB_DRV_CH0, 0x02, (pucTable[ucIndex + 0]));
                Scaler32SetByte(PB58060_20_DP14_TX_EM_DRV_CH0, 0x02, (pucTable[ucIndex + 1]));
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                // Port2  Swing / Preemphasis
                Scaler32SetByte(PB58060_14_DP14_TX_IB_DRV_CH4, 0x02, (pucTable[ucIndex + 0]));
                Scaler32SetByte(PB58060_24_DP14_TX_EM_DRV_CH4, 0x02, (pucTable[ucIndex + 1]));
            }

            break;

        case _DISPLAY_DP_TX_LANE_3: // VTX_lane3

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                // Port1  Swing / Preemphasis
                Scaler32SetByte(PB58060_10_DP14_TX_IB_DRV_CH0, 0x03, (pucTable[ucIndex + 0]));
                Scaler32SetByte(PB58060_20_DP14_TX_EM_DRV_CH0, 0x03, (pucTable[ucIndex + 1]));
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                // Port2  Swing / Preemphasis
                Scaler32SetByte(PB58060_14_DP14_TX_IB_DRV_CH4, 0x03, (pucTable[ucIndex + 0]));
                Scaler32SetByte(PB58060_24_DP14_TX_EM_DRV_CH4, 0x03, (pucTable[ucIndex + 1]));
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Display Dp Tx APHY Output Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXSetAphyOutputEnable(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    switch(GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort))
    {
        case _DP_ONE_LANE: // VTX Lane0

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT19 | _BIT18 | _BIT17 | _BIT16), _BIT16);
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT23 | _BIT22 | _BIT21 | _BIT20), _BIT20);
            }

            break;

        case _DP_TWO_LANE: // VTX Lane0~1

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT19 | _BIT18 | _BIT17 | _BIT16), (_BIT17 | _BIT16));
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT23 | _BIT22 | _BIT21 | _BIT20), (_BIT21 | _BIT20));
            }

            break;

        case _DP_FOUR_LANE: // VTX Lane0~3

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                // Power Serializer power control
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                // Power Tx drv
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT19 | _BIT18 | _BIT17 | _BIT16), (_BIT19 | _BIT18 | _BIT17 | _BIT16));
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                // Power Serializer power control
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                // Power Tx drv
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT23 | _BIT22 | _BIT21 | _BIT20), (_BIT23 | _BIT22 | _BIT21 | _BIT20));
            }
            break;

        default:
            break;
    }
}
#endif // End of #if(_DISPLAY_DP_TXX_SUPPORT == _ON)
