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
// ID Code      : RL6952_Series_DpMacDphyRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpMacDphyRx1/ScalerDpMacDphyRx1.h"

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX1_SUPPORT == _ON))
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
// Description  : Check Dp Training Pattern 1 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
bit ScalerDpMacDphyRx1PhyCtsTp1Check(void)
{
    BYTE ucDecodeCheckLane = 0;
    BYTE ucTP1PhyLane = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // [5] Disable De-Scrambling
        ScalerSetBit(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT5, _BIT5);

        // FIFO sync
        ScalerSetBit(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
        ScalerSetBit(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);

        ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
        ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);

        // Wait for 2ms
        ScalerTimerDelayXms(2);

        // DP 20 MAC Enable TP1 Detect
        ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT7, 0x00);
        ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT7, _BIT7);

        // Wait for 10ms
        ScalerTimerDelayXms(10);

        switch(ScalerGetBit(P1F_A8_BIST_PATTERN_SEL_DP20, (_BIT4 | _BIT3)) << 1)
        {
            case 0x00: // Lane0 Test

                // EQ auto K,Check lane0 CRC
                if(((ScalerGetByte(P1F_B4_TP1_DETECT_DP20_1) & 0x11) == 0x10) &&
                   ((ScalerGetByte(P1F_B5_TP1_DETECT_DP20_2) | ScalerGetByte(P1F_B6_TP1_DETECT_DP20_3)) == 0x00) &&
                   ((ScalerGetByte(P1F_F6_FRAME_DETECT_DP20_5) & 0x03) == 0x01))
                {
                    return _TRUE;
                }

                break;

            case 0x10: // Lane1 Test

                // EQ auto K,Check lane1 CRC
                if(((ScalerGetByte(P1F_B4_TP1_DETECT_DP20_1) & 0x22) == 0x20) &&
                   ((ScalerGetByte(P1F_B5_TP1_DETECT_DP20_2) | ScalerGetByte(P1F_B6_TP1_DETECT_DP20_3)) == 0x00) &&
                   ((ScalerGetByte(P1F_F6_FRAME_DETECT_DP20_5) & 0x0C) == 0x04))
                {
                    return _TRUE;
                }

                break;

            case 0x20: // Lane2 Test

                // EQ auto K,Check lane2 CRC
                if(((ScalerGetByte(P1F_B4_TP1_DETECT_DP20_1) & 0x44) == 0x40) &&
                   ((ScalerGetByte(P1F_B5_TP1_DETECT_DP20_2) | ScalerGetByte(P1F_B6_TP1_DETECT_DP20_3)) == 0x00) &&
                   ((ScalerGetByte(P1F_F6_FRAME_DETECT_DP20_5) & 0x30) == 0x10))
                {
                    return _TRUE;
                }

                break;

            case 0x30: // Lane3 Test

                // EQ auto K,Check lane3 CRC
                if(((ScalerGetByte(P1F_B4_TP1_DETECT_DP20_1) & 0x88) == 0x80) &&
                   ((ScalerGetByte(P1F_B5_TP1_DETECT_DP20_2) | ScalerGetByte(P1F_B6_TP1_DETECT_DP20_3)) == 0x00) &&
                   ((ScalerGetByte(P1F_F6_FRAME_DETECT_DP20_5) & 0xC0) == 0x40))
                {
                    return _TRUE;
                }

                break;

            default:

                break;
        }

        return _FALSE;
    }
    else
#endif
    {
        // FIFO sync
        ScalerSetBit(PB0_10_PHY_CH_FIFO_SYNC0, ~_BIT0, 0x00);
        ScalerSetBit(PB0_10_PHY_CH_FIFO_SYNC0, ~_BIT0, _BIT0);

        // Wait for 10ms
        ScalerTimerDelayXms(10);

        // Clear 8B/10B Decode Error Flags
        ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Wait for 2ms
        ScalerTimerDelayXms(2);

        switch(ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30)
        {
            case 0x00: // Lane0 Test

                // EQ auto K,Check lane0 CRC
                ucTP1PhyLane = 0x10;

                break;

            case 0x10: // Lane1 Test

                // EQ auto K,Check lane1 CRC
                ucTP1PhyLane = 0x20;

                break;

            case 0x20: // Lane2 Test

                // EQ auto K,Check lane2 CRC
                ucTP1PhyLane = 0x40;

                break;

            case 0x30: // Lane3 Test

                // EQ auto K,Check lane3 CRC
                ucTP1PhyLane = 0x80;

                break;

            default:

                ucTP1PhyLane = 0x00;

                break;
        }

        ucDecodeCheckLane = ScalerDpMacDphyRx1PhyCtsTp1DecodeLane(ucTP1PhyLane);

        DebugMessageRx1("ucDecodeCheckLane", ucDecodeCheckLane);

        if(((ScalerGetByte(PB0_06_DECODE_10B8B_ERROR) & ucDecodeCheckLane) == 0x00) &&
           ((ScalerGetByte(PB0_13_EQ_CRC_2) & (ucDecodeCheckLane << 4)) != 0x00))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//----------------------------------------------------------------
// Description  : Check Dp Lane in Training Pattern 1 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//----------------------------------------------------------------
BYTE ScalerDpMacDphyRx1PhyCtsTp1DecodeLane(BYTE ucTP1PhyLane)
{
#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    ucTP1PhyLane = ucTP1PhyLane;
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if(ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT1 | _BIT0)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) >> 4))
        {
            return 0x01;
        }
        else if(ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT3 | _BIT2)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) >> 2))
        {
            return 0x02;
        }
        else if(ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT5 | _BIT4)) == (ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30))
        {
            return 0x04;
        }
        else if(ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT7 | _BIT6)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) << 2))
        {
            return 0x08;
        }
    }
    else
#endif
    {
        if(ScalerGetBit(PB0_03_LANE_MUX, (_BIT1 | _BIT0)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) >> 4))
        {
            return 0x01;
        }
        else if(ScalerGetBit(PB0_03_LANE_MUX, (_BIT3 | _BIT2)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) >> 2))
        {
            return 0x02;
        }
        else if(ScalerGetBit(PB0_03_LANE_MUX, (_BIT5 | _BIT4)) == (ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30))
        {
            return 0x04;
        }
        else if(ScalerGetBit(PB0_03_LANE_MUX, (_BIT7 | _BIT6)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) << 2))
        {
            return 0x08;
        }
    }
    return 0;
#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)
    return (ucTP1PhyLane >> 4);
#else
    return 0;
#endif
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2 for PHY CTS
// Input Value  : Link Rate / Lane Select
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
bit ScalerDpMacDphyRx1PhyCtsTp2Check(void)
{
    BYTE ucDecodeCheckLane = 0;
    BYTE ucTP2PhyLane = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // MAC one lane
        // ScalerSetBit(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), _BIT3);

        // FEC FIFO enable
        ScalerSetBit(P1F_80_FEC_DECODE_CTL, ~(_BIT6 | _BIT0), _BIT0);

        // CDI removal enable
        ScalerSetBit(P1F_CE_CDI_REMOVAL_DP20_1, ~_BIT7, _BIT7);

        // Enable De-Scramble
        ScalerSetBit(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT5, 0x00);

        // FIFO sync
        ScalerSetBit(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
        ScalerSetBit(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);

        ScalerTimerDelayXms(2);
/*
        switch(ScalerGetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, (_BIT5 | _BIT4)))
        {
            case 0x00: // Lane0 Test

                ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), 0x00);
                ScalerSetBit(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), 0x00);
                ScalerSetByte(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBC);

                break;

            case 0x10: // Lane1 Test

                ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), 0x00);
                ScalerSetBit(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), _BIT6);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), _BIT0);
                ScalerSetByte(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBD);

                break;

            case 0x20: // Lane2 Test

                ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), 0x00);
                ScalerSetBit(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), _BIT7);
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), _BIT1);
                ScalerSetByte(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBE);

                break;

            case 0x30: // Lane3 Test

                ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), 0x00);
                ScalerSetBit(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                ScalerSetBit(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetByte(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBF);

                break;

            default:

                break;
        }
*/
        if(ScalerGetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, _BIT6) != _BIT6)
        {
            // Enable EQ-CRC and Clear EQ-CRC Status(- K28.5)
            ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT6, _BIT6);

            ScalerTimerDelayXms(2);

            ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT3, _BIT3);
            ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT3, 0x00);

            ScalerTimerDelayXms(2);
        }
        else
        {
            ScalerTimerDelayXms(2);
            ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT3, _BIT3);
            ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT3, 0x00);
            ScalerTimerDelayXms(2);
        }

        switch(ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30)
        {
            case 0x00: // Lane0 Test

                if(((ScalerGetByte(P1F_B7_TP2_DETECT_DP20_1) | ScalerGetByte(P1F_B8_TP2_DETECT_DP20_2)) == 0x00) &&
                   ((ScalerGetByte(P1F_F6_FRAME_DETECT_DP20_5) & 0x03) == 0x02) &&
                   ((ScalerGetByte(P1F_D2_FRAME_DETECT_DP20_3) & _BIT4) == _BIT4))
                {
                    return _TRUE;
                }

                break;

            case 0x10: // Lane1 Test

                if(((ScalerGetByte(P1F_B7_TP2_DETECT_DP20_1) | ScalerGetByte(P1F_B8_TP2_DETECT_DP20_2)) == 0x00) &&
                   ((ScalerGetByte(P1F_F6_FRAME_DETECT_DP20_5) & 0x0C) == 0x08) &&
                   ((ScalerGetByte(P1F_D2_FRAME_DETECT_DP20_3) & _BIT5) == _BIT5))
                {
                    return _TRUE;
                }

                break;

            case 0x20: // Lane2 Test

                if(((ScalerGetByte(P1F_B7_TP2_DETECT_DP20_1) | ScalerGetByte(P1F_B8_TP2_DETECT_DP20_2)) == 0x00) &&
                   ((ScalerGetByte(P1F_F6_FRAME_DETECT_DP20_5) & 0x30) == 0x20) &&
                   ((ScalerGetByte(P1F_D2_FRAME_DETECT_DP20_3) & _BIT6) == _BIT6))
                {
                    return _TRUE;
                }

                break;

            case 0x30: // Lane3 Test

                if(((ScalerGetByte(P1F_B7_TP2_DETECT_DP20_1) | ScalerGetByte(P1F_B8_TP2_DETECT_DP20_2)) == 0x00) &&
                   ((ScalerGetByte(P1F_F6_FRAME_DETECT_DP20_5) & 0xC0) == 0x80) &&
                   ((ScalerGetByte(P1F_D2_FRAME_DETECT_DP20_3) & _BIT7) == _BIT7))
                {
                    return _TRUE;
                }

                break;

            default:

                break;
        }

        return _FALSE;
    }
    else
#endif
    {
        // FIFO sync
        ScalerSetBit(PB0_10_PHY_CH_FIFO_SYNC0, ~_BIT0, 0x00);
        ScalerSetBit(PB0_10_PHY_CH_FIFO_SYNC0, ~_BIT0, _BIT0);

        ScalerTimerDelayXms(10);

        // Mac Use Xtal Clk
        ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);

        switch(ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30)
        {
            case 0x00: // Lane0 Test

                ucTP2PhyLane = 0x01;

                break;

            case 0x10: // Lane1 Test

                ucTP2PhyLane = 0x02;

                break;

            case 0x20: // Lane2 Test

                ucTP2PhyLane = 0x04;

                break;

            case 0x30: // Lane3 Test

                ucTP2PhyLane = 0x08;

                break;

            default:

                break;
        }

        ucDecodeCheckLane = ScalerDpMacDphyRx1PhyCtsTp2DecodeLane(ucTP2PhyLane);

        if((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0xC0) == 0xC0) // HBR3
        {
            // Enable Scramble
            ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);

            // Clear 8B/10B Decode Error Flags
            ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            ScalerTimerDelayXms(2);

            if(((ScalerGetByte(PB0_06_DECODE_10B8B_ERROR) & ucDecodeCheckLane) == 0x00))
            {
                return _TRUE;
            }
        }
        else
        {
            // Disable Scramble
            ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

            // eq_crc_ans = 0x22C
            ScalerSetByte(PB0_15_EQ_CRC_4, 0x2C);

            // eq_crc_sel = 1 -> 0 --> Reload tps2_crc_ans
            ScalerSetBit(PB0_12_EQ_CRC_1, ~_BIT4, _BIT4);
            ScalerSetBit(PB0_12_EQ_CRC_1, ~_BIT4, 0x00);

            // Clear EQ-CRC
            ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

            // Start Calculate EQ-CRC
            ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            ScalerTimerDelayXms(2);

            if((ScalerGetByte(PB0_12_EQ_CRC_1) & ucDecodeCheckLane) != 0x00)
            {
                // Stop Calculate EQ-CRC
                ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

                return _TRUE;
            }
            else
            {
                // eq_crc_ans = 0x2E8
                ScalerSetByte_EXINT(PB0_15_EQ_CRC_4, 0xE8);

                // eq_crc_sel = 0 -> 1 --> Reload tps3_crc_ans
                ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~_BIT4, 0x00);
                ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~_BIT4, _BIT4);

                // Clear EQ-CRC
                ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

                // Start Calculate EQ-CRC
                ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                ScalerTimerDelayXms(2);

                if((ScalerGetByte(PB0_12_EQ_CRC_1) & ucDecodeCheckLane) != 0x00)
                {
                    // Stop Calculate EQ-CRC
                    ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);

                    return _TRUE;
                }
            }

            // Stop Calculate EQ-CRC
            ScalerSetBit(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);
        }
    }
    return _FALSE;
}

//----------------------------------------------------------------
// Description  : Check Dp Lane in Training Pattern 1 for PHY CTS
// Input Value  : None
// Output Value : TRUE --> TP1 Pass
//----------------------------------------------------------------
BYTE ScalerDpMacDphyRx1PhyCtsTp2DecodeLane(BYTE ucTP2PhyLane)
{
#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    ucTP2PhyLane = ucTP2PhyLane;
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if(ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT1 | _BIT0)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) >> 4))
        {
            return 0x01;
        }
        else if(ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT3 | _BIT2)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) >> 2))
        {
            return 0x02;
        }
        else if(ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT5 | _BIT4)) == (ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30))
        {
            return 0x04;
        }
        else if(ScalerGetBit(P1F_A3_LANE_MUX_DP20, (_BIT7 | _BIT6)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) << 2))
        {
            return 0x08;
        }
    }
    else
#endif
    {
        if(ScalerGetBit(PB0_03_LANE_MUX, (_BIT1 | _BIT0)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) >> 4))
        {
            return 0x01;
        }
        else if(ScalerGetBit(PB0_03_LANE_MUX, (_BIT3 | _BIT2)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) >> 2))
        {
            return 0x02;
        }
        else if(ScalerGetBit(PB0_03_LANE_MUX, (_BIT5 | _BIT4)) == (ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30))
        {
            return 0x04;
        }
        else if(ScalerGetBit(PB0_03_LANE_MUX, (_BIT7 | _BIT6)) == ((ScalerDpPhyRxCtsCtrl(enumInputPort) & 0x30) << 2))
        {
            return 0x08;
        }
    }
    return 0;

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)
    return ucTP2PhyLane;
#else
    return 0;
#endif
}

#endif // End of #if(_DP_MAC_DPHY_RX1_SUPPORT == _ON)

