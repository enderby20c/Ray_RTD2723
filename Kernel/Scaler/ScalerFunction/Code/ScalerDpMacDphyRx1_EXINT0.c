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
// ID Code      : ScalerDpMacDphyRx1_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_DPHY_RX1_EXINT0__

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
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
//--------------------------------------------------
// Description  : Hdcp14 Module Power Proc
// Input Value  : EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1PowerProc_EXINT0(EnumPowerAction enumPowerAction)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch(_DP_MAC_DPHY_RX1);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:

            // Set DPRX SRAM CLK Gate Disable
            ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _DISABLE);

            // DP MAC1 Power Cut Enable
            ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX1_DP14_DPHY, _POWER_CUT_ON, _POWER_RESET_DISABLE);

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            // DP MAC1 Power Cut Disable
            ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX1_DP14_DPHY, _POWER_CUT_OFF, _POWER_RESET_ENABLE);

            // Reset Key download port
            ScalerDpMacDphyRxPowerDataRecover_EXINT0(enumInputPort);

            // Set DPRX SRAM CLK Gate Enable
            ScalerDpMacDphyRxHdcpSramClkGate(enumInputPort, _ENABLE);

            break;

        default:
            break;
    }
}
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FEC Support
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1FecDecode_EXINT0(BYTE ucFECDecode)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(ucFECDecode == _ENABLE)
    {
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ////// DP20 Part //////
        // FEC Enable
        ScalerSetBit_EXINT(P1F_80_FEC_DECODE_CTL, ~(_BIT6 | _BIT0), _BIT0);

        // Enable FEC error detect
        ScalerSetBit_EXINT(P1F_82_FEC_ERROR_DETECT, ~_BIT7, _BIT7);
#endif
        ////// DP14 Part //////
        // FEC Enable
        ScalerSetBit_EXINT(PB0_D0_FEC_DECODE_CTL, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Enable FEC error detect
        ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT7, _BIT7);
    }
    else
    {
        // FEC Disable
        ScalerSetBit_EXINT(PB0_D0_FEC_DECODE_CTL, ~(_BIT7 | _BIT0), 0x00);

        // Disable FEC error detect
        ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT7, 0x00);

        // Clear FEC en/dis seq & Running Indicator
        ScalerDpAuxRxSetDpcdBitWrite1ClearValue_EXINT0(enumInputPort, 0x00, 0x02, 0x80, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Clear FEC DPCD Error Count
        ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x81, 0x00);
        ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x82, 0x00);
    }
}

//--------------------------------------------------
// Description  : FEC Decode Check
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx1FecDecodeCheck_EXINT0(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1FecDecodeCheck_128b132b_EXINT0();
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1FecDecodeCheck_8b10b_EXINT0();
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP Mst Mode Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ConfigMstOrSstMode_EXINT0(void)
{
#if(_DP_MST_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if((ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x11) & _BIT0) == _BIT0)
    {
        // MST to SST block Config MST Mode
        SET_DP_MAC_DPHY_RX1_MST2SST_BLOCK_MST_MODE_EXINT();

        // Dp Phy Rx MST mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        // MST to SST block Config SST Mode
        SET_DP_MAC_DPHY_RX1_MST2SST_BLOCK_SST_MODE_EXINT();

        // Dp Phy Rx SST mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : DP Tp1 Decode Check
// Input Value  : Link Rate, DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRx1Tp1DecodeCheck_EXINT0(BYTE ucDpLane)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1Tp1DecodeCheck_128b132b_EXINT0(ucDpLane);
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1Tp1DecodeCheck_8b10b_EXINT0(ucDpLane);
    }
}

//--------------------------------------------------
// Description  : DP TP2 Decode Check
// Input Value  : Link Rate, DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRx1Tp2DecodeCheck_EXINT0(EnumDpLane enumDpLane)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        return ScalerDpMacDphyRx1Tp2DecodeCheck_128b132b_EXINT0(enumDpLane);
    }
    else
#endif
    {
        return ScalerDpMacDphyRx1Tp2DecodeCheck_8b10b_EXINT0(enumDpLane);
    }
}

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRx1LaneSwapSelect_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1LaneSwapSelect_128b132b_EXINT0(enumInputPort, ucClockLaneSelect);
    }
    else
#endif
    {
        ScalerDpMacDphyRx1LaneSwapSelect_8b10b_EXINT0(enumInputPort, ucClockLaneSelect);
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Lane Count
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1LaneCountSet_EXINT0(BYTE ucDpLaneCount)
{
    switch(ucDpLaneCount)
    {
        case _DP_ONE_LANE:

            // [4:3] DP MAC Select One Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), _BIT3);
#endif
            break;

        case _DP_TWO_LANE:

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), _BIT4);
#endif
            break;

        case _DP_FOUR_LANE:

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
#endif
            break;

        default:

            // [4:3] DP MAC Select Default
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), 0x00);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), 0x00);
#endif
            break;
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Comma Detect
// Input Value  : ON or OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1SetCommaDetect_EXINT0(bit bEn)
{
    if(bEn == _ON)
    {
        // [4] Enable Comma Detection
        ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, 0x00);
    }
    else
    {
        // [4] Disable Comma Detection
        ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, _BIT4);
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Clock Selection
// Input Value  : Link Clock or XTAL Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ClkSelect_EXINT0(EnumDpMacClkSelect enumClkSelect)
{
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, enumClkSelect);
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT5, enumClkSelect >> 1);
#endif
}

//--------------------------------------------------
// Description  : DP MAC Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Reset_EXINT0(void)
{
    ScalerDpMacDphyRx1DeSkewReset_EXINT0();

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
        ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);
    }
    else
#endif
    {
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);
    }

    // Delay Time us [150,x] Delay for Lane Alignment after Mac Reset
    DELAY_XUS_EXINT(150);
}

//--------------------------------------------------
// Description  : DP Chnanel FIFO Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ChannelFifoReset_EXINT0(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        // FIFO sync
        ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);
    }
    else
#endif
    {
        // FIFO sync
        ScalerSetBit_EXINT(PB0_10_PHY_CH_FIFO_SYNC0, ~_BIT0, 0x00);
        ScalerSetBit_EXINT(PB0_10_PHY_CH_FIFO_SYNC0, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : DP De-Skew Circuit Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1DeSkewReset_EXINT0(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit_EXINT(P1F_F7_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit_EXINT(P1F_F7_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT6);
    }
    else
#endif
    {
        ScalerSetBit_EXINT(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit_EXINT(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT6);
    }
}

//--------------------------------------------------
// Description  : DP De-Skew Circuit Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1EnhancementControlMode_EXINT0(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : DP De-Skew Circuit Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Scramble_EXINT0(bit bEn)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        if(bEn == _ENABLE)
        {
            // Enable Scrambling
            ScalerSetBit_EXINT(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT5, 0x00);
        }
        else
        {
            // Disable Scrambling
            ScalerSetBit_EXINT(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT5, _BIT5);
        }
    }
    else
#endif
    {
        if(bEn == _ENABLE)
        {
            // Enable Scrambling
            ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
        }
        else
        {
            // Disable Scrambling
            ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
        }
    }
}

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
DWORD ScalerDpMacDphyRx1SignalDetectMeasureCount_EXINT0(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    DWORD ulDpMeasureCount = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(enumDpMeasureTarget == _DP_MEASURE_TARGET_RAW_DATA)
    {
        ScalerDpPhyRxSignalDetection_EXINT0(enumInputPort, _ENABLE);
    }

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ulDpMeasureCount = (DWORD)ScalerDpMacDphyRx1SignalDetectMeasureCount128b132b_EXINT0(ucDpLaneSel, enumDpMeasureTarget, enumDpMeasurePeriod);
    }
    else
#endif
    {
        // [1:0] freqdet_lane_sel
        ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

        // [5] ln_ck_sel
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT5, enumDpMeasureTarget);

        switch(enumDpMeasurePeriod)
        {
            case _DP_MEASURE_PERIOD_125_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00000
                ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                break;

            case _DP_MEASURE_PERIOD_250_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00001
                ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                break;

            case _DP_MEASURE_PERIOD_1000_CYCLE:

                // [4:0] DP_XTAL_CYCLE = 5'b00011
                ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                break;

            case _DP_MEASURE_PERIOD_2000_CYCLE:
            default:

                // [4:0] DP_XTAL_CYCLE = 5'b00100
                ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
                break;
        }

        // [7] DP_SIG_DET_EN = 1'b1 -> Disable Signal Detection
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        // [6] LANE_COUNT_CLEAR = 1 -> Reset the LANE_COUNT value
        ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Delay Time us [5,150] Polling for Measure Done
        for(BYTE ucLoopIndex = 0; ucLoopIndex <= 30; ucLoopIndex++)
        {
            DELAY_5US_EXINT();

            if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
            {
                DELAY_5US_EXINT();

                ulDpMeasureCount = (DWORD)((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

                break;
            }
        }

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    }

    ScalerDpPhyRxSignalDetection_EXINT0(enumInputPort, _DISABLE);

#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_32_BIT)
    if(enumDpMeasureTarget == _DP_MEASURE_TARGET_RAW_DATA)
    {
        return ulDpMeasureCount;
    }
    else
    {
        return ((ulDpMeasureCount << 3) / 5);
    }
#elif(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_16_BIT)
    if(enumDpMeasureTarget == _DP_MEASURE_TARGET_RAW_DATA)
    {
        return ulDpMeasureCount;
    }
    else
    {
        return ((ulDpMeasureCount << 2) / 5);
    }
#else

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        return ulDpMeasureCount << 1;
    }
    else
#endif
    {
        return ulDpMeasureCount;
    }

#endif
}

//--------------------------------------------------
// Description  : DP High Priority Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1DigitalPhyHighPriorityIntHandler_EXINT0(void)
{
    if(GET_DP_MAC_DPHY_RX1_DPHY_GLOBAL_HIGH_PRIORITY_IRQ_FLAG() == _TRUE)
    {
        return;
    }
}

//--------------------------------------------------
// Description  : DP High Priority Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1DigitalPhyLowPriorityIntHandler_EXINT0(void)
{
    if(GET_DP_MAC_DPHY_RX1_DPHY_GLOBAL_LOW_PRIORITY_IRQ_FLAG() == _TRUE)
    {
#if(_DP_RX_FEC_SUPPORT == _ON)
        ScalerDpMacDphyRx1FecHanlder_EXINT0();
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
        ScalerDpMacDphyRx1AuxlessAlpmHanlder_8b10b_EXINT0();

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpMacDphyRx1AuxlessAlpmHanlder_128b132b_EXINT0();
#endif
#endif
    }
}

//--------------------------------------------------
// Description  : DP Mac Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1MacResetProc_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping_EXINT0(_RX1);

    enumInputPort = enumInputPort;

    SET_DP_RX1_NORMAL_LINK_TRAINING_SETPHY_FINISH();

    // Mac Reset After Link Clock Stable
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // Delay Time us [150,x] Delay for Lane Alignment after Mac Reset
    DELAY_XUS_EXINT(150);

#if(_DP_MST_SUPPORT == _ON)
    SET_DP_MAC_DPHY_RX1_LOAD_NEW_STREAM_PAYLOAD_EXINT();

#if(_DP_TX_SUPPORT == _ON)
    if(enumInputPort == GET_DP_RX_MAIN_PORT())
    {
        // Reset Daisy Chain Async-fifo
        ScalerSetBit_EXINT(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
    }
#endif
#endif

    ScalerDpMacDphyRx1DecodeErrorCountReset_EXINT0(_DP_MAC_DECODE_METHOD_8B10B);
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mac Rx1 Load New Stream PayLoad
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1LoadNewStreamPayload_EXINT0(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit_EXINT(P9F_01_STHD_CTRL_1, ~_BIT7, 0x00);

        // Delay Up to 65537 Timeslots
        // 3.2ns per Timeslot for UHBR10
        // Delay Time  >=  65537 * 3.2ns = 210ns, as 500ns for Insurance Purposes
        DELAY_XUS_EXINT(500);
        ScalerSetBit_EXINT(P9F_01_STHD_CTRL_1, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        ScalerSetBit_EXINT(PB8_01_STHD_CTRL_1, ~_BIT7, 0x00);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(PB8_01_STHD_CTRL_1, ~_BIT7, _BIT7);
    }
}
#endif // #if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : DP Stream Handler Config SST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1SetHdcpMode_EXINT0(EnumHDCPType enumHDCPType)
{
    enumHDCPType = enumHDCPType;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_8B10B)
#endif
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if(enumHDCPType == _HDCP_22)
        {
            ScalerSetBit_EXINT(PB0_1A_HDCP_IRQ, ~_BIT1, _BIT1);
        }
        else
#endif
        {
            ScalerSetBit_EXINT(PB0_1A_HDCP_IRQ, ~_BIT1, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set HDCP An, Aksv, Repeater by FW
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1SetHdcp14Info_EXINT0(void)
{
    BYTE ucTemp = 0x00;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    // Set Hdcp14 FW Mode
    ScalerSetBit_EXINT(PB0_17_DP_HDCP_CONTROL, ~_BIT4, _BIT4);

    for(ucTemp = 0; ucTemp < 5; ucTemp++)
    {
        // DPCD [0x68007 ~ 0x6800B]
        ScalerSetByte_EXINT((PB0_70_HDCP_AKSV_4 + ucTemp), ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x06, 0x80, (0x0B - ucTemp)));
    }

    for(ucTemp = 0; ucTemp < 8; ucTemp++)
    {
        // DPCD [0x6800C ~ 0x68013]
        ScalerSetByte_EXINT((PB0_75_HDCP_AN_7 + ucTemp), ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x06, 0x80, (0x13 - ucTemp)));
    }

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
    ScalerSetBit_EXINT(PB0_7D_HDCP_REPEATER, ~_BIT0, ScalerDpHdcp14RxGetRepeaterCaps_EXINT0(enumInputPort));
#endif
}

//--------------------------------------------------
// Description  : Get Hdcp14 R0 to DPCD Table
// Input Value  : Hdcp14 R0 Type
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMacDphyRx1GetHdcp14R0_EXINT0(EnumDpHdcp14R0Type enumDpHdcp14R0Type)
{
    if(enumDpHdcp14R0Type == _HDCP_14_R0_LSB)
    {
        return ScalerGetByte_EXINT(PB0_7F_HDCP_R0_0);
    }
    else
    {
        return ScalerGetByte_EXINT(PB0_7E_HDCP_R0_1);
    }
}

//--------------------------------------------------
// Description  : Recover Data from Power Cut State
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerDpMacDphyRx1PowerDataRecover_EXINT0(void)
{
    // Reset Key download port and Enable HDCP FW Mode
    ScalerSetBit_EXINT(PB0_17_DP_HDCP_CONTROL, ~(_BIT4 | _BIT0), _BIT4);

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1DecodeErrorCountReset_EXINT0(EnumDpMacDecodeMethod enumDpMacDecodeMethod)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1)) == _CODING_TYPE_128B132B)
    {
        // Reset PRBS Error Check
        ScalerSetBit_EXINT(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT4, 0x00);

        switch(enumDpMacDecodeMethod)
        {
            case _DP_MAC_DECODE_METHOD_PRBS31:

                // Select PRBS31
                ScalerSetBit_EXINT(P1F_A8_BIST_PATTERN_SEL_DP20, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT5));

                // Disable PRBS New Mode, de-scramble
                ScalerSetBit_EXINT(P1F_A7_SCRAMBLE_CTRL_DP20, ~(_BIT7 | _BIT5), _BIT5);

                // Start Record PRBS7 Error Count Value
                ScalerSetBit_EXINT(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT4, _BIT4);

                break;

            default:
                break;
        }
    }
    else
#endif
    {
        // Reset 8b10b Error Count Value
        ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        switch(enumDpMacDecodeMethod)
        {
            case _DP_MAC_DECODE_METHOD_PRBS7:

                // Reverse PRBS7 Pattern Gen
                ScalerDpMacDphyRx1PrbsReverse_EXINT0(_ENABLE);

                // Start Record PRBS7 Error Count Value
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                break;

            case _DP_MAC_DECODE_METHOD_PRBS31:

                // Select PRBS31
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

                // Start Record PRBS7 Error Count Value
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                break;

            case _DP_MAC_DECODE_METHOD_8B10B_DISPARITY:

                // Start Record 8b10b or Disparity Error Count Value
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

                break;

            default:
            case _DP_MAC_DECODE_METHOD_8B10B:

                // Start Record 8b10b Error Count Value
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1DecodeErrorCountOff_EXINT0(void)
{
    // Disable 8b10b Error Count Value
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DP Error Counter Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1ErrorCounterUpdate_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Store Lane0 Error
        ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x10, 0x00);
        ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Store Lane1 Error
        ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x12, 0x00);
        ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Store Lane2 Error
        ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x14, 0x00);
        ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Store Lane3 Error
        ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x16, 0x00);
        ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
#endif
    {
        switch(ScalerDpAuxRxGetLaneCount_EXINT0(enumInputPort))
        {
            case _DP_ONE_LANE:

                // Store Lane0 Error
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_DP_LANE_0 << 3));
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x10, ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) & 0x7F);

                break;

            case _DP_TWO_LANE:

                // Store Lane0 Error
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_DP_LANE_0 << 3));
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x10, ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) & 0x7F);

                // Store Lane1 Error
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_DP_LANE_1 << 3));
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x12, ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) & 0x7F);

                break;

            default:
            case _DP_FOUR_LANE:

                // Store Lane0 Error
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_DP_LANE_0 << 3));
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x10, ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) & 0x7F);

                // Store Lane1 Error
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_DP_LANE_1 << 3));
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x12, ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) & 0x7F);

                // Store Lane2 Error
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_DP_LANE_2 << 3));
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x14, ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) & 0x7F);

                // Store Lane3 Error
                ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_DP_LANE_3 << 3));
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x16, ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) & 0x7F);

                break;
        }
    }

    // Reset 8B/10B Error Counter
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : DP Error Counter Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1PhyCtsErrorCounterUpdate_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);
    BYTE ucErrorCountLaneSelect = 0;
    WORD usErrorCount = 0;

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // PRBS Pattern Follow MAC Lane
        ucErrorCountLaneSelect = ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x70, (_BIT5 | _BIT4));

        // Lane Select
        ScalerSetBit_EXINT(P1F_A8_BIST_PATTERN_SEL_DP20, ~(_BIT4 | _BIT3 | _BIT2), ucErrorCountLaneSelect >> 1);

        // Error Count Readout
        usErrorCount = ((((WORD)ScalerGetByte_EXINT(P1F_AB_BIST_PATTERN_DP_20_3)) << 8) | ScalerGetByte_EXINT(P1F_AC_BIST_PATTERN_DP_20_4));

        switch(ucErrorCountLaneSelect)
        {
            case (_BIT5 | _BIT4):

                // Store Lane3 Error
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x16, LOBYTE(usErrorCount));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                break;

            case (_BIT5):

                // Store Lane2 Error
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x14, LOBYTE(usErrorCount));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                break;

            case (_BIT4):

                // Store Lane1 Error
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x12, LOBYTE(usErrorCount));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                break;

            default:
            case 0x00:

                // Store Lane0 Error
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x10, LOBYTE(usErrorCount));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                break;
        }

        // Reset PRBS7 Error Counter
        ScalerDpMacDphyRx1DecodeErrorCountReset_EXINT0(_DP_MAC_DECODE_METHOD_PRBS31);
    }
    else
#endif
    {
#if(_HW_DP_RX_PHY_TO_MAC_INTERFACE == _DP_RX_20_BIT)
        if((ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x00) == 0x06) ||
           (ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x00) == 0x0A))
        {
            // PRBS Pattern Follow PHY Lane
            ucErrorCountLaneSelect = ScalerDpPhyRxGetPhyCtsTestLane_EXINT0(enumInputPort);
        }
        else
#endif
        {
            // TPS Pattern Follow MAC Lane
            ucErrorCountLaneSelect = (ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x70, (_BIT5 | _BIT4)));
        }

        // Lane Select
        ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), ucErrorCountLaneSelect >> 1);

        // Error Count Readout
        usErrorCount = ((((WORD)ScalerGetByte_EXINT(PB0_0B_BIST_PATTERN3) & 0x7F) << 8) | ScalerGetByte_EXINT(PB0_0C_BIST_PATTERN4));

        switch(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x70, (_BIT5 | _BIT4)))
        {
            case (_BIT5 | _BIT4):

                // Store Lane3 Error
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x16, LOBYTE(usErrorCount));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                break;

            case (_BIT5):

                // Store Lane2 Error
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x14, LOBYTE(usErrorCount));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                break;

            case (_BIT4):

                // Store Lane1 Error
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x12, LOBYTE(usErrorCount));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x13, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                break;

            default:
            case 0x00:

                // Store Lane0 Error
                ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x00, 0x02, 0x10, LOBYTE(usErrorCount));
                ScalerDpAuxRxSetDpcdBitValue_EXINT0(enumInputPort, 0x00, 0x02, 0x11, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usErrorCount));

                break;
        }

        // Reset 8B/10B Error Counter
        if((ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x00) == 0x06) ||
           (ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x00) == 0x0A))
        {
            // Reset PRBS7 Error Counter
            ScalerDpMacDphyRx1DecodeErrorCountReset_EXINT0(_DP_MAC_DECODE_METHOD_PRBS7);
        }
        else
        {
            // Reset 8B/10B Error Counter
            ScalerDpMacDphyRx1DecodeErrorCountReset_EXINT0(_DP_MAC_DECODE_METHOD_8B10B_DISPARITY);
        }
    }
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2ResetProc_EXINT0(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpMacDphyRx1Hdcp2ResetProc_128b132b_EXINT0();
#endif
    ScalerDpMacDphyRx1Hdcp2ResetProc_8b10b_EXINT0();
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Link Integrity Check
// Input Value  : _Enable/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_EXINT0(bit bEnable)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_128b132b_EXINT0(bEnable);
    }
    else
#endif
    {
        ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_8b10b_EXINT0(bEnable);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableDecryption_EXINT0(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1Hdcp2EnableDecryption_128b132b_EXINT0();
    }
    else
#endif
    {
        ScalerDpMacDphyRx1Hdcp2EnableDecryption_8b10b_EXINT0();
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_EXINT0(bit bEnable)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1Hdcp2EnableAuthDone_128b132b_EXINT0(bEnable);
    }
    else
#endif
    {
        ScalerDpMacDphyRx1Hdcp2EnableAuthDone_8b10b_EXINT0(bEnable);
    }
}

//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2SetAESType_EXINT0(void)
{
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx1Hdcp2SetAESType_128b132b_EXINT0();
    }
    else
#endif
    {
        ScalerDpMacDphyRx1Hdcp2SetAESType_8b10b_EXINT0();
    }
}
#endif

//--------------------------------------------------
// Description  : PRBS Decode Reverse Bit Sequence
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1PrbsReverse_EXINT0(BYTE ucEnable)
{
    ScalerSetBit_EXINT(PB0_08_BIST_PATTERN_SEL, ~_BIT7, ucEnable << 7);
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2ResetProc_8b10b_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    enumInputPort = enumInputPort;

    // Disable HDCP2.2 Auth. Done
    ScalerSetBit_EXINT(PB0_20_HDCP_DEBUG, ~_BIT4, 0x00);

    // Clear Type Value
    ScalerSetByte_EXINT(PB0_93_HDCP_TYPE_AES_0, 0x00);

    // Clear Type Value
    ScalerSetByte_EXINT(PB0_94_HDCP_TYPE_AES_1, 0x01);

#if(_DP_MST_SUPPORT == _ON)
    // For MST mode
    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
    {
        // Clear AES STx Type
        ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    }
    else
#endif
    {
        // Clear AES STx Type
        ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Link Integrity Check
// Input Value  : _Enable/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_8b10b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable DP Link Integrity Check
        ScalerSetBit_EXINT(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable DP Link Integrity Check
        ScalerSetBit_EXINT(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableDecryption_8b10b_EXINT0(void)
{
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};

    ScalerHdcp2Proc1_EXINT0(pucTemp1, g_stHdcp2RxDownLoadKeyType.pucHdcp2Lc);
    ScalerHdcp2Proc2_EXINT0(pucTemp2, g_pucHdcp2Ks);

    // Enable Decryption
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        g_pucHdcp2InputCipher[ucLoopIndex] = pucTemp2[ucLoopIndex] ^ pucTemp1[ucLoopIndex];

        ScalerSetByte_EXINT(PB0_81_HDCP_AES_CIPHER_KEY_15 + ucLoopIndex, g_pucHdcp2InputCipher[ucLoopIndex]);
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ucLoopIndex++)
    {
        ScalerSetByte_EXINT(PB0_55_RIV0 + ucLoopIndex, g_pucHdcp2Riv[ucLoopIndex]);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_8b10b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable HDCP2.2 Auth. Done
        ScalerSetBit_EXINT(PB0_20_HDCP_DEBUG, ~_BIT4, _BIT4);
    }
    else
    {
        // Disable HDCP2.2 Auth. Done
        ScalerSetBit_EXINT(PB0_20_HDCP_DEBUG, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2SetAESType_8b10b_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    // For MST mode
    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
    {
        EnumDpStreamNum enumDpStreamNum = _DP_ST_NONE;

        ScalerDpRxSetBaseInputPort(enumInputPort);

        for(EnumDpMstPort enumDpMstPort = _DP_PORT8; enumDpMstPort <= _DP_PORT9; enumDpMstPort++)
        {
            enumDpStreamNum = ScalerDpMacDphyRxGetStreamAllocateInfo_EXINT0(enumInputPort, enumDpMstPort);

            if(enumDpStreamNum != _DP_ST_NONE)
            {
                // Set AES Type
                if(ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x06, 0x94, 0x94) == 0x00)
                {
                    // Type = 0x00
                    ScalerDpMacDphyRx1Hdcp2SetStxType_8b10b_EXINT0(enumDpStreamNum, 0x00);
                }
                else
                {
                    // Type = 0x01 or Type = 0x02 - 0xFF
                    ScalerDpMacDphyRx1Hdcp2SetStxType_8b10b_EXINT0(enumDpStreamNum, 0x01);
                }
            }
        }
    }
    else
#endif
    {
        // Set AES Type
        if(ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x06, 0x94, 0x94) == 0x00)
        {
            // Type = 0x00
            ScalerDpMacDphyRx1Hdcp2SetStxType_8b10b_EXINT0(_DP_ST_1, 0x00);
        }
        else
        {
            // Type = 0x01 or Type = 0x02 - 0xFF
            ScalerDpMacDphyRx1Hdcp2SetStxType_8b10b_EXINT0(_DP_ST_1, 0x01);
        }
    }
}

//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2SetStxType_8b10b_EXINT0(EnumDpStreamNum enumDpStreamNum, BYTE ucType)
{
    switch(enumDpStreamNum)
    {
#if(_DP_MST_SUPPORT == _ON)
        case _DP_ST_2:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT6, 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT6);
            }
            else
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT6, _BIT6);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT6;
            }

            break;

        case _DP_ST_3:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT5, 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT5);
            }
            else
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT5, _BIT5);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT5;
            }

            break;

        case _DP_ST_4:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT4, 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT4);
            }
            else
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT4, _BIT4);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT4;
            }

            break;

        case _DP_ST_5:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT3, 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT3);
            }
            else
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT3, _BIT3);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT3;
            }

            break;

        case _DP_ST_6:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(PB0_96_DUMMY3, ~_BIT7, 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT7);
            }
            else
            {
                ScalerSetBit_EXINT(PB0_96_DUMMY3, ~_BIT7, _BIT7);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT7;
            }

            break;
#endif

        case _DP_ST_1:
        default:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT7, 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT7);
            }
            else
            {
                ScalerSetBit_EXINT(PB0_95_HDCP_ST_TYPE, ~_BIT7, _BIT7);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT7;
            }

            break;
    }
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Auxless ALPM Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1AuxlessAlpmHanlder_8b10b_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    // Check Sleep Pattern Detected
    if((ScalerGetBit_EXINT(PB0_4C_ALPM_SLEEP_0, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(PB0_4C_ALPM_SLEEP_0, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5)))
    {
        // Flag Clear
        ScalerSetBit_EXINT(PB0_4C_ALPM_SLEEP_0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Set AUX_LESS_ALPM_ML_PHY_SLEEP_DETECTED
        ScalerDpAuxRxSetDpcdBitWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x0B, ~_BIT3, _BIT3);
    }
}
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FEC Support
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1FecHanlder_EXINT0(void)
{
    ScalerDpMacDphyRx1FecHanlder_8b10b_EXINT0();
}
#endif

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRx1LaneSwapSelect_8b10b_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_RTD_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_RTD)
#elif(_PORT_CTRL_TCPM_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
#else
    if(ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED)
#endif
    {
        // Main-Link Lane Setting Start
        if(ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) != _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Pin Assignment C/D PN Swap
            ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3) << 7);
            ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2) << 6);
            ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1) << 5);
            ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0) << 4);
        }
        else
        {
            // Pin Assignment E PN Swap
            ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3)) << 7);
            ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2)) << 6);
            ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1)) << 5);
            ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0)) << 4);
        }

        switch(ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort))
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:

                if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_D:

                if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_E:

                if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 6);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 4);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 2);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 6);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 4);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 2);
                    ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1));
                }

                break;

            default:
            case _TYPE_C_PIN_ASSIGNMENT_NONE:

                // DP Lane Swap Setting
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));

                break;
        }
    }
    else if((ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_RTS) || (ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_USER))
    {
        if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            if((ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler_EXINT0(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 6);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 4);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 2);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));
            }
        }
        else
        {
            if((ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler_EXINT0(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 4);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 2);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 6);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 4);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 2);
                ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3));
            }
        }
    }
    else
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    {
        // DP PN Swap Setting
        ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3) << 7);
        ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2) << 6);
        ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1) << 5);
        ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0) << 4);

        // DP Lane Swap Setting
        ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
        ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 4);
        ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
        ScalerSetBit_EXINT(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));
    }

    ScalerDpPhyRxSetLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3, ScalerGetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, _BIT7) >> 7);
    ScalerDpPhyRxSetLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2, ScalerGetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, _BIT6) >> 6);
    ScalerDpPhyRxSetLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1, ScalerGetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, _BIT5) >> 5);
    ScalerDpPhyRxSetLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0, ScalerGetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, _BIT4) >> 4);

    ScalerDpPhyRxSetLaneMux_EXINT0(enumInputPort, _DP_LANE_3, (ScalerGetBit_EXINT(PB0_03_LANE_MUX, (_BIT7 | _BIT6)) >> 6));
    ScalerDpPhyRxSetLaneMux_EXINT0(enumInputPort, _DP_LANE_2, (ScalerGetBit_EXINT(PB0_03_LANE_MUX, (_BIT5 | _BIT4)) >> 4));
    ScalerDpPhyRxSetLaneMux_EXINT0(enumInputPort, _DP_LANE_1, (ScalerGetBit_EXINT(PB0_03_LANE_MUX, (_BIT3 | _BIT2)) >> 2));
    ScalerDpPhyRxSetLaneMux_EXINT0(enumInputPort, _DP_LANE_0, (ScalerGetBit_EXINT(PB0_03_LANE_MUX, (_BIT1 | _BIT0))));

    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x70, _BIT7) != _BIT7)
    {
        ucClockLaneSelect = (ScalerGetBit_EXINT(PB0_03_LANE_MUX, (_BIT1 | _BIT0)) << 6);
    }

    // [7:6] DP Mac Clock Selection
    ScalerSetBit_EXINT(PB0_02_PHY_DIG_RESET2_CTRL, ~(_BIT7 | _BIT6), ucClockLaneSelect);
}

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FEC Support
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1FecHanlder_8b10b_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    // FEC Decode en Sequence Detect IRQ
    if((ScalerGetBit_EXINT(PB0_D2_FEC_SEQUENCE_DET_CTL, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(PB0_D2_FEC_SEQUENCE_DET_CTL, _BIT6) == _BIT6))
    {
        // Flag Clear
        ScalerSetBit_EXINT(PB0_D2_FEC_SEQUENCE_DET_CTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT6);

        // Set DPCD 00280h FEC_DECODE_EN_DETECTED and FEC_RUNNUING_INDICATOR
        ScalerDpAuxRxSetDpcdBitWrite1ClearValue_EXINT0(enumInputPort, 0x00, 0x02, 0x80, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        if(ScalerGetBit_EXINT(PB0_05_SAMPLE_EDGE, _BIT4) == 0x00)
        {
            // Delay Time us [300,0] for Comma Detect Worse Case 8192 x 10 x 9 / 1.62G = 455us, TP_END Already Delay 150us
            DELAY_XUS_EXINT(300);

            // [4] Disable Comma Detection
            ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, _BIT4);
        }

        ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT1, _BIT1);
        ScalerSetBit_EXINT(PB0_D3_FEC_ERROR_DETECT, ~_BIT1, 0x00);
    }

    // FEC Decode dis Sequence Detect IRQ
    if((ScalerGetBit_EXINT(PB0_D2_FEC_SEQUENCE_DET_CTL, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(PB0_D2_FEC_SEQUENCE_DET_CTL, _BIT5) == _BIT5))
    {
        // Flag Clear
        ScalerSetBit_EXINT(PB0_D2_FEC_SEQUENCE_DET_CTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);

        // Set DPCD 00280h FEC_DECODE_DIS_DETECTED and Clr FEC_RUNNUING_INDICATOR
        ScalerDpAuxRxSetDpcdBitWrite1ClearValue_EXINT0(enumInputPort, 0x00, 0x02, 0x80, ~(_BIT2 | _BIT1), _BIT1);

        if(ScalerDpAuxRxGetFecStatusW1cProtectEnable_EXINT0(enumInputPort) == _ENABLE)
        {
            ScalerDpAuxRxSetDpcdBitWrite1ClearValue_EXINT0(enumInputPort, 0x00, 0x02, 0x80, ~_BIT0, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : DP14 Rx FEC Decode Check
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx1FecDecodeCheck_8b10b_EXINT0(void)
{
    if(((ScalerGetBit_EXINT(PB0_D0_FEC_DECODE_CTL, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(PB0_D2_FEC_SEQUENCE_DET_CTL, _BIT7) == _BIT7)))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP TP2 Decode Check
// Input Value  : Link Rate, DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRx1Tp3DecodeCheck_EXINT0(EnumDpLane enumDpLane)
{
    BYTE uctemp1 = 0;
    BYTE uctemp2 = 0;
    BYTE uctemp3 = 0;

    switch(enumDpLane)
    {
        case _DP_LANE_3:
            // MAC Lane3
            ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
            uctemp1 = 0x80;
            uctemp2 = 0xC0;
            uctemp3 = 6;
            break;

        case _DP_LANE_2:
            // MAC Lane2
            ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), _BIT5);
            uctemp1 = 0x40;
            uctemp2 = 0x30;
            uctemp3 = 4;

            break;

        case _DP_LANE_1:
            // MAC Lane1
            ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), _BIT4);
            uctemp1 = 0x20;
            uctemp2 = 0x0C;
            uctemp3 = 2;

            break;

        case _DP_LANE_0:
        default:

            // MAC Lane0
            ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), 0x00);
            uctemp1 = 0x10;
            uctemp2 = 0x03;
            uctemp3 = 0;
            break;
    }

    // dig_phy_reset
    ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);

    // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
    for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
    {
        DELAY_5US_EXINT();
    }

    // FIFO sync
    ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);

    // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
    for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
    {
        DELAY_5US_EXINT();
    }

    // Enable TPS2 Decode Check
    ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT7 | _BIT6 | _BIT3), _BIT3);
    ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT3, 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT6, _BIT6);

    // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
    for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
    {
        DELAY_5US_EXINT();
    }

    if(((ScalerGetByte_EXINT(P1F_D2_FRAME_DETECT_DP20_3) & uctemp1) != 0x00) &&
       (((ScalerGetByte_EXINT(P1F_F6_FRAME_DETECT_DP20_5) & uctemp2) >> uctemp3) == 0x02))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc for MAC RX1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2ResetProc_128b132b_EXINT0(void)
{
    // Disable HDCP2.2 Auth. Done
    ScalerSetBit_EXINT(P1F_07_HDCP_DEBUG, ~_BIT0, 0x00);

    // Clear Type Value
    ScalerSetByte_EXINT(P1F_28_HDCP_TYPE_AES_0, 0x00);

    // Clear Type Value
    ScalerSetByte_EXINT(P1F_29_HDCP_TYPE_AES_1, 0x01);

    // Clear AES STx Type
    ScalerSetByte_EXINT(P1F_2B_HDCP_ST_TYPE_0, 0x00);
    ScalerSetBit_EXINT(P1F_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Link Integrity Check
// Input Value  : _Enable/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableLinkIntegrityCheck_128b132b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable DP Link Integrity Check
        ScalerSetBit_EXINT(P1F_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable DP Link Integrity Check
        ScalerSetBit_EXINT(P1F_02_HDCP_INTGT_VRF, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableDecryption_128b132b_EXINT0(void)
{
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};

    ScalerHdcp2Proc1_EXINT0(pucTemp1, g_stHdcp2RxDownLoadKeyType.pucHdcp2Lc);
    ScalerHdcp2Proc2_EXINT0(pucTemp2, g_pucHdcp2Ks);

    // Enable Decryption
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        g_pucHdcp2InputCipher[ucLoopIndex] = pucTemp2[ucLoopIndex] ^ pucTemp1[ucLoopIndex];

        ScalerSetByte_EXINT(P1F_18_HDCP_AES_CIPHER_KEY_15 + ucLoopIndex, g_pucHdcp2InputCipher[ucLoopIndex]);
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ucLoopIndex++)
    {
        ScalerSetByte_EXINT(P1F_08_RIV0 + ucLoopIndex, g_pucHdcp2Riv[ucLoopIndex]);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2EnableAuthDone_128b132b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable HDCP2.2 Auth. Done
        ScalerSetBit_EXINT(P1F_07_HDCP_DEBUG, ~_BIT0, _BIT0);
    }
    else
    {
        // Disable HDCP2.2 Auth. Done
        ScalerSetBit_EXINT(P1F_07_HDCP_DEBUG, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2SetAESType_128b132b_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    // For MST mode
    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
    {
        EnumDpStreamNum enumDpStreamNum = _DP_ST_NONE;

        ScalerDpRxSetBaseInputPort(enumInputPort);

        for(EnumDpMstPort enumDpMstPort = _DP_PORT8; enumDpMstPort <= _DP_PORT9; enumDpMstPort++)
        {
            enumDpStreamNum = ScalerDpMacDphyRxGetStreamAllocateInfo_EXINT0(enumInputPort, enumDpMstPort);

            if(enumDpStreamNum != _DP_ST_NONE)
            {
                // Set AES Type
                if(ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x06, 0x94, 0x94) == 0x00)
                {
                    // Type = 0x00
                    ScalerDpMacDphyRx1Hdcp2SetStxType_128b132b_EXINT0(enumDpStreamNum, 0x00);
                }
                else
                {
                    // Type = 0x01 or Type = 0x02 - 0xFF
                    ScalerDpMacDphyRx1Hdcp2SetStxType_128b132b_EXINT0(enumDpStreamNum, 0x01);
                }
            }
        }
    }
    else
#endif
    {
        // Set AES Type
        if(ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x06, 0x94, 0x94) == 0x00)
        {
            // Type = 0x00
            ScalerDpMacDphyRx1Hdcp2SetStxType_128b132b_EXINT0(_DP_ST_1, 0x00);
        }
        else
        {
            // Type = 0x01 or Type = 0x02 - 0xFF
            ScalerDpMacDphyRx1Hdcp2SetStxType_128b132b_EXINT0(_DP_ST_1, 0x01);
        }
    }
}

//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx1Hdcp2SetStxType_128b132b_EXINT0(EnumDpStreamNum enumDpStreamNum, BYTE ucType)
{
    switch(enumDpStreamNum)
    {
        case _DP_ST_2:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(P1F_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6), 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT6);
            }
            else
            {
                ScalerSetBit_EXINT(P1F_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6), _BIT6);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT6;
            }

            break;

        case _DP_ST_3:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(P1F_2B_HDCP_ST_TYPE_0, ~(_BIT1 | _BIT0), 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT0);
            }
            else
            {
                ScalerSetBit_EXINT(P1F_2B_HDCP_ST_TYPE_0, ~(_BIT1 | _BIT0), _BIT0);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT0;
            }

            break;

        case _DP_ST_4:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(P1F_2B_HDCP_ST_TYPE_0, ~(_BIT3 | _BIT2), 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT2);
            }
            else
            {
                ScalerSetBit_EXINT(P1F_2B_HDCP_ST_TYPE_0, ~(_BIT3 | _BIT2), _BIT2);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT2;
            }

            break;

        case _DP_ST_5:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(P1F_2B_HDCP_ST_TYPE_0, ~(_BIT5 | _BIT4), 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT4);
            }
            else
            {
                ScalerSetBit_EXINT(P1F_2B_HDCP_ST_TYPE_0, ~(_BIT5 | _BIT4), _BIT4);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT4;
            }

            break;

        case _DP_ST_6:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(P1F_2B_HDCP_ST_TYPE_0, ~(_BIT7 | _BIT6), 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT6);
            }
            else
            {
                ScalerSetBit_EXINT(P1F_2B_HDCP_ST_TYPE_0, ~(_BIT7 | _BIT6), _BIT6);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT6;
            }

            break;

        case _DP_ST_1:
        default:

            if(ucType == 0x00)
            {
                ScalerSetBit_EXINT(P1F_2C_HDCP_ST_TYPE_1, ~(_BIT5 | _BIT4), 0x00);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT4);
            }
            else
            {
                ScalerSetBit_EXINT(P1F_2C_HDCP_ST_TYPE_1, ~(_BIT5 | _BIT4), _BIT4);

                g_stDpMacDphyRx1HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT4;
            }

            break;
    }
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Auxless ALPM Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx1AuxlessAlpmHanlder_128b132b_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    // Check Sleep Pattern Detected
    if((ScalerGetBit_EXINT(P1F_DC_ALPM_DETECT_DP20, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P1F_DC_ALPM_DETECT_DP20, _BIT4) == _BIT4))
    {
        // Flag Clear
        ScalerSetBit_EXINT(P1F_DC_ALPM_DETECT_DP20, ~_BIT4, _BIT4);

        // Set AUX_LESS_ALPM_ML_PHY_SLEEP_DETECTED
        ScalerDpAuxRxSetDpcdBitWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x0B, ~_BIT3, _BIT3);
    }
}
#endif

//-----------------------------------------------------------------------
// Description  : Set DP PHY to MAC Lane Swap / PN Swap / Clock Selection
// Input Value  : None
// Output Value : None
//-----------------------------------------------------------------------
void ScalerDpMacDphyRx1LaneSwapSelect_128b132b_EXINT0(EnumInputPort enumInputPort, BYTE ucClockLaneSelect)
{
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_RTD_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_RTD)
#elif(_PORT_CTRL_TCPM_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
#else
    if(ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED)
#endif
    {
        // Main-Link Lane Setting Start
        if(ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) != _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Pin Assignment C/D PN Swap
            ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3) << 7);
            ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2) << 6);
            ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1) << 5);
            ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0) << 4);
        }
        else
        {
            // Pin Assignment E PN Swap
            ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3)) << 7);
            ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2)) << 6);
            ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1)) << 5);
            ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0)) << 4);
        }

        switch(ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort))
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:

                if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_D:

                if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 4);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 4);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 2);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2));
                }

                break;

            case _TYPE_C_PIN_ASSIGNMENT_E:

                if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 6);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 4);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 2);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));
                }
                else
                {
                    // DP Lane Swap Setting
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 6);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 4);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 2);
                    ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1));
                }

                break;

            default:
            case _TYPE_C_PIN_ASSIGNMENT_NONE:

                // DP Lane Swap Setting
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));

                break;
        }
    }
    else if((ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_RTS) || (ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_USER))
    {
        if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            if((ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler_EXINT0(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 6);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 4);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 2);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 4);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));
            }
        }
        else
        {
            if((ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_E) && (ScalerTypeCRxGetExtPinELaneSwapByScaler_EXINT0(enumInputPort) == _TRUE))
            {
                // Pin Assignment E DP Lane PN Swap Setting
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3)) << 7);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2)) << 6);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1)) << 5);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, (!ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0)) << 4);

                // Pin Assignment E DP Lane Swap Setting
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 4);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 2);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1));
            }
            else
            {
                // Pin Assignment C/D/None DP Lane PN Swap Setting
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3) << 7);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2) << 6);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1) << 5);
                ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0) << 4);

                // Pin Assignment C/D/None DP Lane Swap Setting
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) << 6);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 4);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 2);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3));
            }
        }
    }
    else
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    {
        // DP PN Swap Setting
        ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT7, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3) << 7);
        ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT6, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2) << 6);
        ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT5, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1) << 5);
        ScalerSetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, ~_BIT4, ScalerDpPhyRxGetPCBLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0) << 4);

        // DP Lane Swap Setting
        ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT7 | _BIT6), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_3) << 6);
        ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT5 | _BIT4), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_2) << 4);
        ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT3 | _BIT2), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) << 2);
        ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));
    }

    ScalerDpPhyRxSetLanePNSwap_EXINT0(enumInputPort, _DP_LANE_3, ScalerGetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, _BIT7) >> 7);
    ScalerDpPhyRxSetLanePNSwap_EXINT0(enumInputPort, _DP_LANE_2, ScalerGetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, _BIT6) >> 6);
    ScalerDpPhyRxSetLanePNSwap_EXINT0(enumInputPort, _DP_LANE_1, ScalerGetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, _BIT5) >> 5);
    ScalerDpPhyRxSetLanePNSwap_EXINT0(enumInputPort, _DP_LANE_0, ScalerGetBit_EXINT(P1F_A6_DECODE_10B8B_ERROR_DP20, _BIT4) >> 4);

    ScalerDpPhyRxSetLaneMux_EXINT0(enumInputPort, _DP_LANE_3, (ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT7 | _BIT6)) >> 6));
    ScalerDpPhyRxSetLaneMux_EXINT0(enumInputPort, _DP_LANE_2, (ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT5 | _BIT4)) >> 4));
    ScalerDpPhyRxSetLaneMux_EXINT0(enumInputPort, _DP_LANE_1, (ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT3 | _BIT2)) >> 2));
    ScalerDpPhyRxSetLaneMux_EXINT0(enumInputPort, _DP_LANE_0, (ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT1 | _BIT0))));

    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x02, 0x70, _BIT7) != _BIT7)
    {
        ucClockLaneSelect = (ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT1 | _BIT0)) << 6);
    }

    // [7:6] DP Mac Clock Selection
    ScalerSetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), ucClockLaneSelect);
}

//--------------------------------------------------
// Description : DP Signal Detection Measure
// Input Value  : DP Lane Select, Measure target, Measure Period
// Output Value : Measure Counter
//--------------------------------------------------
WORD ScalerDpMacDphyRx1SignalDetectMeasureCount128b132b_EXINT0(BYTE ucDpLaneSel, EnumDpMeasureTarget enumDpMeasureTarget, EnumDpMeasurePeriod enumDpMeasurePeriod)
{
    WORD usDpMeasureCount = 0;

    // [1:0] freqdet_lane_sel
    ScalerSetBit_EXINT(P1F_F1_DP_SIG_DET_DP20_1, ~(_BIT1 | _BIT0), (ucDpLaneSel & (_BIT1 | _BIT0)));

    // [5] ln_ck_sel
    ScalerSetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, ~_BIT5, enumDpMeasureTarget);

    switch(enumDpMeasurePeriod)
    {
        case _DP_MEASURE_PERIOD_125_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00000
            ScalerSetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            break;

        case _DP_MEASURE_PERIOD_250_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00001
            ScalerSetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            break;

        case _DP_MEASURE_PERIOD_1000_CYCLE:

            // [4:0] DP_XTAL_CYCLE = 5'b00011
            ScalerSetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _DP_MEASURE_PERIOD_2000_CYCLE:
        default:

            // [4:0] DP_XTAL_CYCLE = 5'b00100
            ScalerSetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            break;
    }

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(P1F_F2_DP_SIG_DET_DP20_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, ~_BIT7, _BIT7);

    // Delay Time us [5,150] Polling for Measure Done
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 30; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(ScalerGetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, _BIT6) == _BIT6)
        {
            usDpMeasureCount = ((((WORD)ScalerGetByte_EXINT(P1F_F3_DP_SIG_DET_DP20_3)) << 8) | ScalerGetByte_EXINT(P1F_F4_DP_SIG_DET_DP20_4));

            break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(P1F_F0_DP_SIG_DET_DP20_0, ~_BIT7, 0x00);

    return usDpMeasureCount;
}

//--------------------------------------------------
// Description  : DP TP2 Decode Check
// Input Value  : Link Rate, DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRx1Tp2DecodeCheck_128b132b_EXINT0(EnumDpLane enumDpLane)
{
    BYTE ucLanenumbak = 0;
    BYTE ucLinkclkselbak = 0;
    BYTE ucLane0muxbak = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX1);

    if((ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_2) ||
       (ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_3))
    {
        ucLanenumbak = ScalerGetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, (_BIT4 | _BIT3));
        ucLinkclkselbak = ScalerGetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, (_BIT7 | _BIT6));
        ucLane0muxbak = ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT1 | _BIT0));

        // set one lane for detection
        ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), _BIT3);
        // check lane0
        ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), 0x00);

        switch(enumDpLane)
        {
            case _DP_LANE_3:
                // MAC Lane3
                g_ucDpMacDphyRx1Temp = ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT7 | _BIT6)) >> 6;
                ScalerSetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), g_ucDpMacDphyRx1Temp << 6);
                ScalerSetByte_EXINT(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBF);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), g_ucDpMacDphyRx1Temp);
                break;

            case _DP_LANE_2:
                // MAC Lane2
                g_ucDpMacDphyRx1Temp = ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT5 | _BIT4)) >> 4;
                ScalerSetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), g_ucDpMacDphyRx1Temp << 6);
                ScalerSetByte_EXINT(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBE);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), g_ucDpMacDphyRx1Temp);
                break;

            case _DP_LANE_1:
                // MAC Lane1
                g_ucDpMacDphyRx1Temp = ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT3 | _BIT2)) >> 2;
                ScalerSetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), g_ucDpMacDphyRx1Temp << 6);
                ScalerSetByte_EXINT(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBD);
                ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), g_ucDpMacDphyRx1Temp);
                break;

            case _DP_LANE_0:
            default:
                // MAC Lane0
                g_ucDpMacDphyRx1Temp = ScalerGetBit_EXINT(P1F_A3_LANE_MUX_DP20, (_BIT1 | _BIT0));
                ScalerSetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), g_ucDpMacDphyRx1Temp << 6);
                ScalerSetByte_EXINT(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBC);
                // ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), pData_EXINT[0]);
                break;
        }

        // dig_phy_reset
        ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
        ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);

        // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
        for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
        {
            DELAY_5US_EXINT();
        }

        // FIFO sync
        ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);

        // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
        for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
        {
            DELAY_5US_EXINT();
        }

        // Enable TPS2 Decode Check
        ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT7 | _BIT6 | _BIT3), _BIT3);
        ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT3, 0x00);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT6, _BIT6);

        // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
        for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
        {
            DELAY_5US_EXINT();
        }

        if(((ScalerGetByte_EXINT(P1F_D2_FRAME_DETECT_DP20_3) & _BIT4) != 0x00) &&
           ((ScalerGetByte_EXINT(P1F_F6_FRAME_DETECT_DP20_5) & (_BIT1 | _BIT0)) == 0x02))
        {
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), ucLanenumbak);
            ScalerSetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), ucLinkclkselbak);
            ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ucLane0muxbak);
            ScalerSetByte_EXINT(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBC);

            // dig_phy_reset
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), ucLanenumbak);
            ScalerSetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), ucLinkclkselbak);
            ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ucLane0muxbak);
            ScalerSetByte_EXINT(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBC);

            // dig_phy_reset
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);

            // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
            for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
            {
                DELAY_5US_EXINT();
            }

            // FIFO sync
            ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);

            // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
            for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
            {
                DELAY_5US_EXINT();
            }

            return _TRUE;
        }
        else
        {
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~(_BIT4 | _BIT3), ucLanenumbak);
            ScalerSetBit_EXINT(P1F_A2_PHY_DIG_RESET_CTRL2_DP20, ~(_BIT7 | _BIT6), ucLinkclkselbak);
            ScalerSetBit_EXINT(P1F_A3_LANE_MUX_DP20, ~(_BIT1 | _BIT0), ucLane0muxbak);
            ScalerSetByte_EXINT(P1F_CB_SCRAMBLE_SEED_DP20_12, 0xBC);

            // dig_phy_reset
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, _BIT2);
            ScalerSetBit_EXINT(P1F_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT2, 0x00);

            // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
            for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
            {
                DELAY_5US_EXINT();
            }

            // FIFO sync
            ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P1F_B0_PHY_CH_FIFO_SYNC_DP20_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), _BIT0);

            // delay at least two TPS2 frame 20us @10G ~40us FW use 50us
            for(g_ucDpMacDphyRx1Temp = 0; g_ucDpMacDphyRx1Temp <= 10; g_ucDpMacDphyRx1Temp++)
            {
                DELAY_5US_EXINT();
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tp1 Decode Check
// Input Value  : Link Rate, DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRx1Tp1DecodeCheck_128b132b_EXINT0(BYTE ucDpLane)
{
    ScalerSetBit_EXINT(P1F_A8_BIST_PATTERN_SEL_DP20, ~(_BIT4 | _BIT3 | _BIT2), ucDpLane);

    // Reset TP1 Error Detect
    ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT7, 0x00);

    if(ScalerGetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, _BIT7) != _BIT7)
    {
        ScalerSetBit_EXINT(P1F_B3_ERROR_COUNT_CTRL_DP20, ~_BIT7, _BIT7);
        DELAY_20US_EXINT();
    }

    if((ScalerGetByte_EXINT(P1F_B5_TP1_DETECT_DP20_2) | ScalerGetByte_EXINT(P1F_B5_TP1_DETECT_DP20_2)) == 0x00)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP20 Rx FEC Decode Check
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
bit ScalerDpMacDphyRx1FecDecodeCheck_128b132b_EXINT0(void)
{
    if(ScalerGetBit_EXINT(P1F_80_FEC_DECODE_CTL, _BIT7) == _BIT7)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif
#endif // End of #if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif
