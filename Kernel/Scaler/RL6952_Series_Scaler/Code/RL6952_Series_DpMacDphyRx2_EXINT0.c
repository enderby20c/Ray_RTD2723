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
// ID Code      : RL6952_Series_DpMacDphyRx2_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPRX2_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpMacDphyRx2/ScalerDpMacDphyRx2.h"

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX2_SUPPORT == _ON))
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
// Description  : DP Tp1 Decode Check
// Input Value  : Link Rate, DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRx2Tp1DecodeCheck_8b10b_EXINT0(BYTE ucDpLane)
{
    // Disable scramble
    ScalerSetBit_EXINT(PC5_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    // Enable TP1 Error Detect
    ScalerSetBit_EXINT(PC5_0B_BIST_PATTERN3, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PC5_0B_BIST_PATTERN3, ~_BIT7, _BIT7);

    // Lane Select
    ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (ucDpLane << 3));

    // Bist Method = Detect Non-control Data != 4A/B5
    ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    DELAY_5US_EXINT();

    if((((ScalerGetByte_EXINT(PC5_09_BIST_PATTERN1) & 0x7F) | ScalerGetByte_EXINT(PC5_0A_BIST_PATTERN2)) != 0x00) &&
       (((ScalerGetByte_EXINT(PC5_0B_BIST_PATTERN3) & 0x7F) | ScalerGetByte_EXINT(PC5_0C_BIST_PATTERN4)) == 0x00))
    {
        // Disable TP1 Error Detect
        ScalerSetBit_EXINT(PC5_0B_BIST_PATTERN3, ~_BIT7, 0x00);

        return _TRUE;
    }

    // Disable TP1 Error Detect
    ScalerSetBit_EXINT(PC5_0B_BIST_PATTERN3, ~_BIT7, 0x00);

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP TP2 Decode Check
// Input Value  : Link Rate, DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRx2Tp2DecodeCheck_8b10b_EXINT0(EnumDpLane enumDpLane)
{
    BYTE ucEQCRCStatus1 = 0;
    BYTE ucEQCRCStatus2 = 0;
    BYTE ucTp2Result = 0;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX2);

    enumDpLane = enumDpLane;

    if(ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_2)
    {
        // eq_crc_ans = 0x22C
        ScalerSetByte_EXINT(PC5_15_EQ_CRC_4, 0x2C);

        // eq_crc_sel = 1 -> 0 --> Reload tps2_crc_ans
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~_BIT4, _BIT4);
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~_BIT4, 0x00);
    }
    else if(ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_3)
    {
        // eq_crc_ans = 0x2E8
        ScalerSetByte_EXINT(PC5_15_EQ_CRC_4, 0xE8);

        // eq_crc_sel = 0 -> 1 --> Reload tps3_crc_ans
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~_BIT4, 0x00);
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~_BIT4, _BIT4);
    }

    if((ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_2) ||
       (ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_3))
    {
        // Enable EQ-CRC and Clear EQ-CRC Status(- K28.5)
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~_BIT7, _BIT7);

        // Delay Time [25,x]
        DELAY_25US_EXINT();

        ucEQCRCStatus1 = ScalerGetByte_EXINT(PC5_12_EQ_CRC_1);

        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) == _DP_LINK_HBR2)
        {
            for(g_ucDpMacDphyRx2Temp = 0; g_ucDpMacDphyRx2Temp <= 30; g_ucDpMacDphyRx2Temp++)
            {
                ucEQCRCStatus1 = ucEQCRCStatus1 & ScalerGetByte_EXINT(PC5_12_EQ_CRC_1);
            }
        }
        else
        {
            for(g_ucDpMacDphyRx2Temp = 0; g_ucDpMacDphyRx2Temp <= 5; g_ucDpMacDphyRx2Temp++)
            {
                ucEQCRCStatus1 = ucEQCRCStatus1 & ScalerGetByte_EXINT(PC5_12_EQ_CRC_1);
            }
        }

        // Enable EQ-CRC and Clear EQ-CRC Status(+ K28.5)
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~_BIT7, _BIT7);

        // Delay Time [25,x]
        DELAY_25US_EXINT();

        ucEQCRCStatus2 = ScalerGetByte_EXINT(PC5_12_EQ_CRC_1);

        for(g_ucDpMacDphyRx2Temp = 0; g_ucDpMacDphyRx2Temp <= 5; g_ucDpMacDphyRx2Temp++)
        {
            ucEQCRCStatus2 = ucEQCRCStatus2 & ScalerGetByte_EXINT(PC5_12_EQ_CRC_1);
        }

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PC5_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        g_ucDpMacDphyRx2EQCRC = (ucEQCRCStatus1 | ucEQCRCStatus2);

        ucTp2Result = g_ucDpMacDphyRx2EQCRC;
    }
    else
    {
        // Reset Error Count
        ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // TPS4 Should Disable MST mode
        ScalerSetBit_EXINT(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);

        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);

        // Enable Scrambling
        ScalerSetBit_EXINT(PC5_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);

#if(_DP_RX_TPS4_CHECK_TYPE == _DP_RX_ERROR_CHECK_BY_8B10B)
        // Check Error Count by 8b10b
        ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
#else
        // bist_seed = 0x00
        ScalerSetByte_EXINT(PC5_0D_BIST_SEED_0, 0x00);

        // Check Error Count by BIST-SEED = 0
        ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#endif

        // Delay Time us [100,x]
        DELAY_XUS_EXINT(100);

        // Lane3
        ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        if(((ScalerGetByte_EXINT(PC5_0B_BIST_PATTERN3) & 0x7F) | ScalerGetByte_EXINT(PC5_0C_BIST_PATTERN4)) == 0x00)
        {
            ucTp2Result = ucTp2Result | _BIT3;
        }

        // Lane2
        ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT4);
        if(((ScalerGetByte_EXINT(PC5_0B_BIST_PATTERN3) & 0x7F) | ScalerGetByte_EXINT(PC5_0C_BIST_PATTERN4)) == 0x00)
        {
            ucTp2Result = ucTp2Result | _BIT2;
        }

        // Lane1
        ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), _BIT3);
        if(((ScalerGetByte_EXINT(PC5_0B_BIST_PATTERN3) & 0x7F) | ScalerGetByte_EXINT(PC5_0C_BIST_PATTERN4)) == 0x00)
        {
            ucTp2Result = ucTp2Result | _BIT1;
        }

        // Lane0
        ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT4 | _BIT3), 0x00);
        if(((ScalerGetByte_EXINT(PC5_0B_BIST_PATTERN3) & 0x7F) | ScalerGetByte_EXINT(PC5_0C_BIST_PATTERN4)) == 0x00)
        {
            ucTp2Result = ucTp2Result | _BIT0;
        }

        // Reset Error Count
        ScalerSetBit_EXINT(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        if(ScalerDpMacDphyRxGetMstProtocolEnable_EXINT0(enumInputPort) == _ENABLE)
        {
            // Check Enable or Disable MST mode
            ScalerSetBit_EXINT(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);
        }
    }

    return ucTp2Result;
}

//--------------------------------------------------
// Description  : DP TP1 Decode Check
// Input Value  : DP Lane
// Output Value : TRUE/FALSE
//--------------------------------------------------
BYTE ScalerDpMacDphyRx2Tp1Detect_EXINT0(EnumDpLane enumDpLane)
{
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_EXINT0(_DP_MAC_DPHY_RX2);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit_EXINT(PD2_B3_ERROR_COUNT_CTRL_DP20, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PD2_B3_ERROR_COUNT_CTRL_DP20, ~_BIT7, _BIT7);
        DELAY_20US_EXINT();
    }
#endif

    switch(enumDpLane)
    {
        case _DP_SCALER_LANE0:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit_EXINT(PD2_B4_TP1_DETECT_DP20_1, (_BIT4 | _BIT0)) == _BIT4)
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if(ScalerGetBit_EXINT(PC5_13_EQ_CRC_2, _BIT4) == _BIT4)
                {
                    return _TRUE;
                }
            }

            break;

        case _DP_SCALER_LANE1:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit_EXINT(PD2_B4_TP1_DETECT_DP20_1, (_BIT5 | _BIT1)) == _BIT5)
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if(ScalerGetBit_EXINT(PC5_13_EQ_CRC_2, _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }

            break;

        case _DP_SCALER_LANE2:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit_EXINT(PD2_B4_TP1_DETECT_DP20_1, (_BIT6 | _BIT2)) == _BIT6)
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if(ScalerGetBit_EXINT(PC5_13_EQ_CRC_2, _BIT6) == _BIT6)
                {
                    return _TRUE;
                }
            }

            break;

        case _DP_SCALER_LANE3:
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
            {
                if(ScalerGetBit_EXINT(PD2_B4_TP1_DETECT_DP20_1, (_BIT7 | _BIT3)) == _BIT7)
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if(ScalerGetBit_EXINT(PC5_13_EQ_CRC_2, _BIT7) == _BIT7)
                {
                    return _TRUE;
                }
            }

            break;

        default:

            break;
    }

    return _FALSE;
}

#endif
