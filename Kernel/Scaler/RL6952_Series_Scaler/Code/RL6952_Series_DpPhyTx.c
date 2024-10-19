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
// ID Code      : RL6952_Series_DpPhyTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DP_PHY_TX__
#include "ScalerFunctionInclude.h"
#include "DpPhyTx/ScalerDpPhyTx.h"

#if(_DP_PHY_TX_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tDPTX_RBR_TABLE[48] =
{
    // Pre-emphasis->      0                   1                   2                   3
    /*    0    */   0x0B, 0x81, 0x13,   0x0B, 0x83, 0x8F,   0x0B, 0x85, 0x8B,   0x0B, 0x88, 0x85,
    /*    4    */   0x0B, 0x83, 0x13,   0x0B, 0x85, 0x8F,   0x0B, 0x88, 0x89,   0x0B, 0x88, 0x89,
    /*    8    */   0x0B, 0x85, 0x13,   0x0B, 0x88, 0x8D,   0x0B, 0x88, 0x8D,   0x0B, 0x88, 0x8D,
    /*   12    */   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,
};

BYTE code tDPTX_HBR_TABLE[48] =
{
    // Pre-emphasis->      0                   1                   2                   3
    /*    0    */   0x0B, 0x81, 0x13,   0x0B, 0x83, 0x8F,   0x0B, 0x85, 0x8B,   0x0B, 0x88, 0x85,
    /*    4    */   0x0B, 0x83, 0x13,   0x0B, 0x85, 0x8F,   0x0B, 0x88, 0x89,   0x0B, 0x88, 0x89,
    /*    8    */   0x0B, 0x85, 0x13,   0x0B, 0x88, 0x8D,   0x0B, 0x88, 0x8D,   0x0B, 0x88, 0x8D,
    /*   12    */   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,
};

BYTE code tDPTX_HBR2_TABLE[48] =
{
    // Pre-emphasis->      0                   1                   2                   3
    /*    0    */   0x0B, 0x81, 0x13,   0x0B, 0x83, 0x8F,   0x0B, 0x85, 0x8B,   0x0B, 0x88, 0x85,
    /*    4    */   0x0B, 0x83, 0x13,   0x0B, 0x85, 0x8F,   0x0B, 0x88, 0x89,   0x0B, 0x88, 0x89,
    /*    8    */   0x0B, 0x85, 0x13,   0x0B, 0x88, 0x8D,   0x0B, 0x88, 0x8D,   0x0B, 0x88, 0x8D,
    /*   12    */   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,
};

BYTE code tDPTX_HBR3_TABLE[48] =
{
    // Pre-emphasis->      0                   1                   2                   3
    /*    0    */   0x0B, 0x81, 0x13,   0x0B, 0x83, 0x8F,   0x0B, 0x85, 0x8B,   0x0B, 0x88, 0x85,
    /*    4    */   0x0B, 0x83, 0x13,   0x0B, 0x85, 0x8F,   0x0B, 0x88, 0x89,   0x0B, 0x88, 0x89,
    /*    8    */   0x0B, 0x85, 0x13,   0x0B, 0x88, 0x8D,   0x0B, 0x88, 0x8D,   0x0B, 0x88, 0x8D,
    /*   12    */   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,   0x0B, 0x88, 0x13,
};

BYTE code tDPTX_UHBR10_TABLE[48] =
{
    // Preset  ->          0                   1                   2                   3
    /*    0    */   0x0B, 0x89, 0x13,   0x0B, 0x89, 0x8D,   0x0B, 0x89, 0x8A,   0x0B, 0x89, 0x87,
    /*    4    */   0x0B, 0x89, 0x83,   0x88, 0x89, 0x13,   0x88, 0x89, 0x8E,   0x89, 0x89, 0x8A,
    /*    8    */   0x88, 0x89, 0x88,   0x89, 0x89, 0x85,   0x86, 0x89, 0x13,   0x86, 0x89, 0x8E,
    /*   12    */   0x86, 0x89, 0x8C,   0x87, 0x89, 0x88,   0x82, 0x89, 0x13,   0x89, 0x84, 0x91,
};

BYTE code tDPTX_UHBR135_TABLE[48] =
{
    // Preset  ->          0                   1                   2                   3
    /*    0    */   0x0B, 0x89, 0x13,   0x0B, 0x89, 0x8D,   0x0B, 0x89, 0x8A,   0x0B, 0x89, 0x87,
    /*    4    */   0x0B, 0x89, 0x83,   0x88, 0x89, 0x13,   0x88, 0x89, 0x8E,   0x89, 0x89, 0x8A,
    /*    8    */   0x88, 0x89, 0x88,   0x89, 0x89, 0x85,   0x86, 0x89, 0x13,   0x86, 0x89, 0x8E,
    /*   12    */   0x86, 0x89, 0x8C,   0x87, 0x89, 0x88,   0x82, 0x89, 0x13,   0x89, 0x84, 0x91,
};

BYTE code tDPTX_UHBR20_TABLE[48] =
{
    // Preset  ->          0                   1                   2                   3
    /*    0    */   0x0B, 0x89, 0x13,   0x0B, 0x89, 0x8D,   0x0B, 0x89, 0x8A,   0x0B, 0x89, 0x87,
    /*    4    */   0x0B, 0x89, 0x83,   0x88, 0x89, 0x13,   0x88, 0x89, 0x8E,   0x89, 0x89, 0x8A,
    /*    8    */   0x88, 0x89, 0x88,   0x89, 0x89, 0x85,   0x86, 0x89, 0x13,   0x86, 0x89, 0x8E,
    /*   12    */   0x86, 0x89, 0x8C,   0x87, 0x89, 0x88,   0x82, 0x89, 0x13,   0x89, 0x84, 0x91,
};
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
// ibhn_trim_l0/1/2/3, cmu_lcvco_ib, calibrate_r_sel_l0/1/2/3
BYTE g_ucDpPhyTxOTPTrimIb;
BYTE g_ucDpPhyTxCtsRequestType;
BYTE g_ucDpPhyTxLinkRate;
StructDPTxLTInfo g_stDpPhyTxLTInfo;
#if(_DP_TX_UHBR_PHY_CTS_ONLY == _ON)
#warning "NOTE: _DP_TX_PHY_CTS_TEST_ONLY can only be used for CTS, and cannot be used for MP !!!"
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Dp Tx Power Control
// Input Value  : enumSwitch    --> Power action description.
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxPowerControl(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            ScalerDpPhyTxPowerCutControl(_POWER_ON);
            ScalerDpPhyTxPowerOnInitial();
            ScalerDpPhyTxPowerProcess(_POWER_ON);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:

            ScalerDpPhyTxPowerProcess(_POWER_OFF);
            ScalerDpPhyTxPowerCutControl(_POWER_OFF);

            break;

        default:
            break;
    }
}
//--------------------------------------------------
// Description  : Dp Phy Tx0 Power Cut Control
// Input Value  : enumSwitch    --> Power action description.
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxPowerCutControl(EnumPowerTarget enumPowerTarget)
{
    if(enumPowerTarget == _POWER_ON)
    {
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_PX0_DP20_APHY, _POWER_CUT_OFF, _POWER_ON_DELAY_NONE);
        PCB_P0_PORT_CTRL_POWER(_P0_PORT_CTRL_POWER_ON);
    }
    else
    {
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_PX0_DP20_APHY, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
        PCB_P0_PORT_CTRL_POWER(_P0_PORT_CTRL_POWER_OFF);
    }
}
//--------------------------------------------------
// Description  : DP Phy Tx Link Training
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxLinkTraining(void)
{
    if(GET_DP_TX_LT_PROCESSING() == _FALSE)
    {
        ScalerDpPhyTxLTInitialSet();
    }

    ScalerDpPhyTxLTStatusJudge();

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        while((GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS) && (GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_FAIL) && (GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_LTTPR_EQ_PASS) && (GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_LTTPR_EQ_FAIL) && (GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_CDS_FAIL_POLLING))
        {
            switch(GET_DP_TX_LT_STATE())
            {
                case _DP_TX_TRAINING_EQ_PHASE:

                    // EQ Not Done --> _DP_TX_TRAINING_LTTPR_EQ_FAIL
                    // EQ Done & Rx Align Not Done --> _DP_TX_TRAINING_LTTPR_EQ_PASS
                    // EQ Done & Rx Align Done --> _DP_TX_TRAINING_EQ_PASS
                    // DPF Share fail | Timeout | Cnt Max --> _DP_TX_TRAINING_EQ_FAIL
                    SET_DP_TX_LT_RESULT(ScalerDpPhyTxTrainEQPhase_128b132b());

                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_EQ_PASS)
                    {
                        DebugMessageDpTx("Dp Tx Link Training EQ PASS", 0);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_CDS_PHASE);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_LTTPR_EQ_PASS)
                    {
                        DebugMessageDpTx("Dp Tx Link Training LTTPR EQ PASS", 1);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_EQ_PHASE_POLLING);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_LTTPR_EQ_FAIL)
                    {
                        DebugMessageDpTx("Dp Tx Link Training LTTPR EQ FAIL", 2);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_EQ_PHASE);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_EQ_FAIL)
                    {
                        DebugMessageDpTx("Dp Tx Link Training EQ FAIL", 3);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DP_TX_TRAINING_EQ_PHASE_POLLING:

                    SET_DP_TX_LT_RESULT(ScalerDpPhyTxTrainEQPhasePolling_128b132b());

                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_EQ_PASS)
                    {
                        DebugMessageDpTx("Dp Tx Link Training Polling EQ PASS", 0);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_CDS_PHASE);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_LTTPR_EQ_PASS)
                    {
                        DebugMessageDpTx("Dp Tx Link Training Polling LTTPR EQ PASS", 1);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_EQ_PHASE_POLLING);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_EQ_FAIL)
                    {
                        DebugMessageDpTx("Dp Tx Link Training Polling EQ FAIL", 2);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DP_TX_TRAINING_CDS_PHASE:

                    // CDS Not Done & Not T.O. --> _DP_TX_TRAINING_CDS_FAIL_POLLING
                    // CDS Done  --> _DP_TX_TRAINING_CDS_PASS
                    // DPF Share fail | Timeout --> _DP_TX_TRAINING_CDS_FAIL
                    SET_DP_TX_LT_RESULT(ScalerDpPhyTxTrainCDSPhase_128b132b());

                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_CDS_PASS)
                    {
                        DebugMessageDpTx("Dp Tx Link Training CDS PASS", 0);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_CDS_FAIL_POLLING)
                    {
                        DebugMessageDpTx("Dp Tx Link Training CDS Polling", 1);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_CDS_PHASE_POLLING);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_CDS_FAIL)
                    {
                        DebugMessageDpTx("Dp Tx Link Training CDS FAIL", 2);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DP_TX_TRAINING_CDS_PHASE_POLLING:

                    SET_DP_TX_LT_RESULT(ScalerDpPhyTxTrainCDSPhasePolling_128b132b());

                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_CDS_PASS)
                    {
                        DebugMessageDpTx("Dp Tx Link Training CDS Polling PASS", 0);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_CDS_FAIL_POLLING)
                    {
                        DebugMessageDpTx("Dp Tx Link Training CDS Polling FAIL", 1);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_CDS_PHASE_POLLING);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_CDS_FAIL)
                    {
                        DebugMessageDpTx("Dp Tx Link Training CDS FAIL", 2);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DP_TX_TRAINING_PATTERN_END:

                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_CDS_PASS)
                    {
                        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_PASS);
                    }
                    else
                    {
                        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_FAIL);
                    }

                    ScalerDpPhyTxTrainPatternEnd();

                    break;

                default:

                    break;
            }

            if(GET_DP_TX_HPD_STATUS_CHANGE() == _TRUE)
            {
                SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_FAIL);

                SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
            }
        }
    }
    else
#endif
    {
        while((GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS) && (GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_FAIL) && (GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_LTTPR_PASS))
        {
            switch(GET_DP_TX_LT_STATE())
            {
                case _DP_TX_TRAINING_PATTERN1:

                    SET_DP_TX_LT_RESULT(ScalerDpPhyTxTrainPattern1());

                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_PASS)
                    {
                        DebugMessageDpTx("Dp Tx Link Training TP1 PASS", 0);

                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN2);
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL)
                    {
                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DP_TX_TRAINING_PATTERN2:

                    SET_DP_TX_LT_RESULT(ScalerDpPhyTxTrainPattern2());

                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN2_PASS)
                    {
                        DebugMessageDpTx("Dp Tx Link Training TP2 PASS", 0);

                        if(GET_DP_TX_LT_DFP_REMAIN_NUM() > 1)
                        {
                            // Write TRAINING_PATTERN_SET = 00
                            pData[0] = _DP_TP_NONE;
                            ScalerDpPhyTxWriteDfpDpcd(_DP_TX_TRAINING_PATTERN_SET, 1, pData);

                            SET_DP_TX_LT_DFP_REMAIN_NUM(GET_DP_TX_LT_DFP_REMAIN_NUM() - 1);
                        }
                        else if(GET_DP_TX_LT_DFP_REMAIN_NUM() == 1)

                        {
                            SET_DP_TX_LT_DFP_REMAIN_NUM(GET_DP_TX_LT_DFP_REMAIN_NUM() - 1);
                        }
                        else
                        {
                            DebugMessageDpTx("Dp Tx Link Training TP2 Error Case", 0);
                        }

                        if(GET_DP_TX_LT_DFP_REMAIN_NUM() == 0)
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                        }
                        else
                        {
                            // Add Already LT pass LTTPR Num
                            ADD_DP_TX_LT_SEGMENT_COMPLETE_NUM();

#if(_DP_TX_TRAINING_SEGMENT_COMPLETE_SUPPORT == _OFF)
                            // LT Result LTTPR Pass & Next Main Loop Handler
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_LTTPR_PASS);
#else
                            // Check Already LT pass LTTPR Num Reach 3
                            if(GET_DP_TX_LT_SEGMENT_COMPLETE_NUM() % _DP_TX_LTTPR_SEGMENT_COMPLETE_NUM == 0)
                            {
                                // Reach 3 Times -> LT Result LTTPR Pass & Next Main Loop Handler
                                SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                                SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_LTTPR_PASS);
                            }
                            else
                            {
                                // Not Reach 3 Times -> LT Result No Result & While in Loop Handler
                                SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                                SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                            }
#endif
                        }
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL)
                    {
                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                    }
                    break;

                case _DP_TX_TRAINING_PATTERN_END:

                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN2_PASS)
                    {
                        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_PASS);
                    }
                    else
                    {
                        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_FAIL);
                    }

                    ScalerDpPhyTxTrainPatternEnd();

                    break;

                default:

                    break;
            }

            if(GET_DP_TX_HPD_STATUS_CHANGE() == _TRUE)
            {
                SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_FAIL);

                SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx BandWidth Config
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxBandWidthConfig(void)
{
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
    {
        SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(ScalerDpMacTxGetMaxLinkRate());
        SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(GET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM());
    }
    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_FAIL)
    {
        if(ScalerDpPhyTxBandWidthReduce() == _FALSE)
        {
            SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(GET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE());
            SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(GET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM());
        }
    }
    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_NO_RESULT)
    {
        SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(GET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE());
        SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(GET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM());
    }
    else
    {
        // Keep & Do nothing
        DebugMessageDpTx("DP Tx BandWidth Config Keep", 0);
    }

    DebugMessageDpTx("DP Tx Link Rate", GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE());
    DebugMessageDpTx("DP Tx Lane Count", GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());
}

//--------------------------------------------------
// Description  : DP Tx BandWidth Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxBandWidthReduce(void)
{
    // [7][3] : Reserved
    // [6:4] data rate;  0:RBR, 1:HBR, 2:HBR2, 3:HBR3, 4:UHBR10, 5:UHBR13.5, 6:UHBR20
    // [2:0] lane number; 1:1 lane, 2:2 lane, 4:4 lane
    // 0x14:4lane HBR
    // 0x22:2lane HBR2
    // 0x12:2lane HBR
    // 0x21:1lane HBR2
    BYTE pucBandWidthTable[21] =
    {0x64,0x54,0x62,0x44,0x52,0x34,0x61,0x42,0x24,0x51,0x32,0x41,0x22,0x14,0x31,0x04,0x21,0x12,0x02,0x11,0x01};
    BYTE ucCurrentBandWidth = 0;
    BYTE ucNextBandWidth = 0;
    BYTE ucBandId = 0;
    BYTE ucBandIdTemp = 0;
    BYTE ucChangeCodeTypeFlag = _TRUE;

    ucCurrentBandWidth = ScalerDpPhyTxLinkRateSort(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE()) | GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM();

    if(ucCurrentBandWidth == 0x01) // 1 lane RBR
    {
        return _FALSE;
    }

    if(ucCurrentBandWidth == 0x41) // 1 lane UHBR10
    {
        if(GET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE() == _CODING_TYPE_128B132B)
        {
            return _FALSE;
        }
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE() != _CODING_TYPE_NONE)
    {
        ucChangeCodeTypeFlag = _FALSE;
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE() <= _DP_LINK_HBR3)
    {
        ucChangeCodeTypeFlag = _FALSE;
    }

    // Find current Bandwidth
    for(ucBandId = 0; ucBandId < 20; ucBandId ++)
    {
        if(pucBandWidthTable[ucBandId] == ucCurrentBandWidth)
        {
            break;
        }
    }

    ucBandIdTemp = ucBandId;

    for(ucBandId = ucBandIdTemp; ucBandId < 20; ucBandId ++)
    {
        ucNextBandWidth = pucBandWidthTable[ucBandId + 1];
        if(ucChangeCodeTypeFlag == _FALSE)
        {
            if(GET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE() == _CODING_TYPE_8B10B)
            {
                if(((ucNextBandWidth & 0xF0) >> 4) >= 4) // UHBR10
                {
                    continue;
                }
            }

            if(GET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE() == _CODING_TYPE_128B132B)
            {
                if(((ucNextBandWidth & 0xF0) >> 4) < 4) // HBR3
                {
                    continue;
                }
            }
        }
        if(ScalerDpPhyTxLinkRateCheck(ucNextBandWidth) == _TRUE)
        {
            break;
        }
    }

    // Set DPTX link rane
    // Set DPTX link number
    SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(ScalerDpPhyTxLinkRateAna(ucNextBandWidth & 0xF0));
    SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(ucNextBandWidth & 0x07);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Band sort
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpPhyTxLinkRateSort(EnumDpLinkRate enumLinkRate)
{
    switch(enumLinkRate)
    {
        case _DP_LINK_UHBR20:
            return 0x60;
            break;
        case _DP_LINK_UHBR13_5:
            return 0x50;
            break;
        case _DP_LINK_UHBR10:
            return 0x40;
            break;
        case _DP_LINK_HBR3:
            return 0x30;
            break;
        case _DP_LINK_HBR2:
            return 0x20;
            break;
        case _DP_LINK_HBR:
            return 0x10;
            break;
        case _DP_LINK_RBR:
            return 0x00;
            break;
        default:
            break;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : DP Tx Band sort
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpPhyTxLinkRateCheck(BYTE ucBand)
{
    BYTE ucLinkRate = 0;
    BYTE ucLaneNum = 0;

    ucLinkRate = ScalerDpPhyTxLinkRateAna(ucBand & 0xF0);
    ucLaneNum = ucBand & 0x0F;

    if(ucLaneNum > GET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM())
    {
        return _FALSE;
    }

    if((ucLinkRate == _DP_LINK_UHBR20) && (GET_DP_MAC_TX_DOWNSTREAM_UHBR20_SUPPORT() == _FALSE))
    {
        return _FALSE;
    }

    if((ucLinkRate == _DP_LINK_UHBR13_5) && (GET_DP_MAC_TX_DOWNSTREAM_UHBR13_5_SUPPORT() == _FALSE))
    {
        return _FALSE;
    }

    if((ucLinkRate == _DP_LINK_UHBR10) && (GET_DP_MAC_TX_DOWNSTREAM_UHBR10_SUPPORT() == _FALSE))
    {
        return _FALSE;
    }


    if(ucLinkRate > GET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE())
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Band sort
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDpLinkRate ScalerDpPhyTxLinkRateAna(BYTE ucBand)
{
    switch(ucBand)
    {
        case 0x60:
            return _DP_LINK_UHBR20;
            break;
        case 0x50:
            return _DP_LINK_UHBR13_5;
            break;
        case 0x40:
            return _DP_LINK_UHBR10;
            break;
        case 0x30:
            return _DP_LINK_HBR3;
            break;
        case 0x20:
            return _DP_LINK_HBR2;
            break;
        case 0x10:
            return _DP_LINK_HBR;
            break;
        case 0x00:
            return _DP_LINK_RBR;
            break;
        default:
            break;
    }

    return _DP_LINK_RBR;
}

//--------------------------------------------------
// Description  : Dp Tx pre coding Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxPreCodingSet(bit bPreCodingEn)
{
    // Set Pre coding
    if(bPreCodingEn == _ENABLE)
    {
        // Enable pre coding
        ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);
    }
    else
    {
        // Disable pre coding
        ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, _BIT1);
    }
}

//--------------------------------------------------
// Description  : DP Phy Tx Read Dfp Dpcd
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxReadDfpDpcd(EnumDpTxLTReadWriteType enumDpTxLTRWType, BYTE ucLength, BYTE *pucReadArray)
{
    BYTE ucAddrH = 0x00;
    BYTE ucAddrM = 0x00;
    BYTE ucAddrL = 0x00;

    ScalerDpPhyTxGetDfpDpcdAddress(enumDpTxLTRWType, &ucAddrH, &ucAddrM, &ucAddrL);

    return ScalerDpAuxTxNativeRead(ucAddrH, ucAddrM, ucAddrL, ucLength, pucReadArray);
}

//--------------------------------------------------
// Description  : DP Phy Tx Write Dfp Dpcd
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxWriteDfpDpcd(EnumDpTxLTReadWriteType enumDpTxLTRWType, BYTE ucLength, BYTE *pucWriteArray)
{
    BYTE ucAddrH = 0x00;
    BYTE ucAddrM = 0x00;
    BYTE ucAddrL = 0x00;

    ScalerDpPhyTxGetDfpDpcdAddress(enumDpTxLTRWType, &ucAddrH, &ucAddrM, &ucAddrL);

    return ScalerDpAuxTxNativeWrite(ucAddrH, ucAddrM, ucAddrL, ucLength, pucWriteArray);
}

//--------------------------------------------------
// Description  : DP Phy Tx Get Dfp Dpcd Address
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxGetDfpDpcdAddress(EnumDpTxLTReadWriteType enumDpTxLTRWType, BYTE *pucCommandAddrH, BYTE *pucAddrM, BYTE *pucAddrL)
{
    DWORD ulDpcdAddress = 0xF0010;

    switch(enumDpTxLTRWType)
    {
        case _DP_TX_TRAINING_PATTERN_SET:
            if(GET_DP_TX_LT_DFP_REMAIN_NUM() <= 1)
            {
                ulDpcdAddress = 0x102;
            }
            else
            {
                ulDpcdAddress = ulDpcdAddress + (GET_DP_TX_LT_DFP_REMAIN_NUM() - 2)* 0x50;
            }
            break;

        case _DP_TX_TRAINING_LANEX_SET:
            if(GET_DP_TX_LT_DFP_REMAIN_NUM() <= 1)
            {
                ulDpcdAddress = 0x103;
            }
            else
            {
                ulDpcdAddress = ulDpcdAddress + (GET_DP_TX_LT_DFP_REMAIN_NUM() - 2) * 0x50 + 0x01;
            }
            break;

        case _DP_TX_TRAINING_LANEX_STATUS:
            if(GET_DP_TX_LT_DFP_REMAIN_NUM() <= 1)
            {
                ulDpcdAddress = 0x202;
            }
            else
            {
                ulDpcdAddress = ulDpcdAddress + (GET_DP_TX_LT_DFP_REMAIN_NUM() - 2) * 0x50 + 0x20;
            }
            break;

        case _DP_TX_TRAINING_AUX_RD_INTERVAL:
            if(GET_DP_TX_LT_DFP_REMAIN_NUM() <= 1)
            {
                ulDpcdAddress = 0x0E;
            }
            else
            {
                ulDpcdAddress = ulDpcdAddress + (GET_DP_TX_LT_DFP_REMAIN_NUM() - 2) * 0x50 + 0x10;
            }
            break;

        default:
            break;
    }

    *pucCommandAddrH = (BYTE)(ulDpcdAddress >> 16);
    *pucAddrM = (BYTE)(ulDpcdAddress >> 8);
    *pucAddrL = (BYTE)(ulDpcdAddress >> 0);
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Inital Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxLTInitialSet(void)
{
    BYTE pucDPCD_108[1] = {0};
    BYTE pucDPCD_100[1] = {0};

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    BYTE pucTemp[5] = {0};
    BYTE ucIndex = 0;
#endif

    // 1. CTS flow
    if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
    {
        // Read TEST_LINK_RATE
        ScalerDpAuxTxNativeRead(0x00, 0x02, 0x19, 1, pData);

        SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(pData[0]);

        // Read TEST_LANE_COUNT
        ScalerDpAuxTxNativeRead(0x00, 0x02, 0x20, 1, pData);

        SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM((pData[0] & 0x1F));

        CLR_DP_TX_CTS_TEST_REQUEST_TARGET_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING);
    }

    // 1. Set Tx Power On
    pData[0] = 0x01;
    ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, pData);

    // 1. Set Down Spread
    ScalerDpAuxTxNativeRead(0x00, 0x01, 0x07, 1, pData);
    pData[0] = ((pData[0] & ~_BIT4) | ((BYTE)GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() << 4));
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x07, 1, pData);

    // 1. Set DFP LTTPR Mode
    if(GET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM() > 0)
    {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        // 128b/132b Coding Type Only Support Non-Transparent Mode
        if(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() >= _DP_LINK_UHBR10)
        {
            pData[0] = 0xAA;
            ScalerDpAuxTxNativeWrite(0x0F, 0x00, 0x03, 1, pData);

            // Initial Link Training Remain Dfp Number = Max DFP LTTPR Number + Dp Rx Sink
            SET_DP_TX_LT_DFP_REMAIN_NUM(GET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM() + 1);
        }
        else
#endif
        {
            if(GET_DP_MAC_TX_LTTPR_MODE_8B10B() == _DP_TX_LTTPR_NON_TRANSPARENT_MODE)
            {
                pData[0] = 0xAA;
                ScalerDpAuxTxNativeWrite(0x0F, 0x00, 0x03, 1, pData);

                // Initial Link Training Remain Dfp Number = Max DFP LTTPR Number + Dp Rx Sink
                SET_DP_TX_LT_DFP_REMAIN_NUM(GET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM() + 1);
            }
            else if(GET_DP_MAC_TX_LTTPR_MODE_8B10B() == _DP_TX_LTTPR_TRANSPARENT_MODE)
            {
                pData[0] = 0x55;
                ScalerDpAuxTxNativeWrite(0x0F, 0x00, 0x03, 1, pData);

                SET_DP_TX_LT_DFP_REMAIN_NUM(1);
            }
        }
    }
    else
    {
        SET_DP_TX_LT_DFP_REMAIN_NUM(1);
    }

    // 2. Phy Input Data from Tx Mac SST
    CLR_DP_MST_TX_ENABLE();

    ScalerDpMacTxMstEnableSetting();

    // 3. Get Link Rate
    switch(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE())
    {
        case _DP_LINK_UHBR20:
            pucDPCD_108[0] = _CODING_TYPE_128B132B;
            pucDPCD_100[0] = _DP_DPCD_02215_LINK_UHBR20;
            break;

        case _DP_LINK_UHBR13_5:
            pucDPCD_108[0] = _CODING_TYPE_128B132B;
            pucDPCD_100[0] = _DP_DPCD_02215_LINK_UHBR13_5;
            break;

        case _DP_LINK_UHBR10:
            pucDPCD_108[0] = _CODING_TYPE_128B132B;
            pucDPCD_100[0] = _DP_DPCD_02215_LINK_UHBR10;
            break;

        case _DP_LINK_HBR3:
            pucDPCD_108[0] = _CODING_TYPE_8B10B;
            pucDPCD_100[0] = _DP_DPCD_02201_LINK_HBR3;
            break;

        case _DP_LINK_HBR2:
            pucDPCD_108[0] = _CODING_TYPE_8B10B;
            pucDPCD_100[0] = _DP_DPCD_02201_LINK_HBR2;
            break;

        case _DP_LINK_HBR:
            pucDPCD_108[0] = _CODING_TYPE_8B10B;
            pucDPCD_100[0] = _DP_DPCD_02201_LINK_HBR;
            break;

        case _DP_LINK_RBR:
            pucDPCD_108[0] = _CODING_TYPE_8B10B;
            pucDPCD_100[0] = _DP_DPCD_02201_LINK_RBR;
            break;

        default:
            pucDPCD_108[0] = _CODING_TYPE_8B10B;
            pucDPCD_100[0] = _DP_DPCD_02201_LINK_RBR;
            break;
    }

    SET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE((EnumDpLinkChannelCodingType)pucDPCD_108[0]);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Switch channel coding between 128b/132b channel coding and 8b/10b channel coding
    if(GET_DP_MAC_TX_DOWNSTREAM_PRE_CODING_TYPE() != GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE())
    {
        SET_DP_MAC_TX_DOWNSTREAM_PRE_CODING_TYPE(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE());

        if((GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_NO_RESULT) || (GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS))
        {
            // Switch channel coding during normal operation
            // Write 02h to the SET_POWER
            pucTemp[0] = 0x02;
            ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, pucTemp);

            // Disable Main Link Transmit
            ScalerDpPhyTxMLPowerOff();

            // Write 01h to the SET_POWER
            pucTemp[0] = 0x01;
            ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, pucTemp);

            // Write Default Values to TRAINING_LANEx_SET
            pucTemp[0] = 0x00;
            pucTemp[1] = 0x00;
            pucTemp[2] = 0x00;
            pucTemp[3] = 0x00;
            SET_DP_TX_LANE0_CURRENT_FFE_PRESET(pucTemp[0]);
            SET_DP_TX_LANE1_CURRENT_FFE_PRESET(pucTemp[1]);
            SET_DP_TX_LANE2_CURRENT_FFE_PRESET(pucTemp[2]);
            SET_DP_TX_LANE3_CURRENT_FFE_PRESET(pucTemp[3]);
            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x03, 4, pucTemp);
        }
        else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_FAIL)
        {
            // Switch channel coding during Link Training
            // Disable Main Link Transmit
            ScalerDpPhyTxMLPowerOff();

            // Clear Training Pattern to 00h & Write Default Values to TRAINING_LANEx_SET
            pucTemp[0] = 0x00;
            pucTemp[1] = 0x00;
            pucTemp[2] = 0x00;
            pucTemp[3] = 0x00;
            pucTemp[4] = 0x00;
            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 5, pucTemp);
            ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_IDLE_PATTERN);
        }
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        // Clear Training Pattern to 00h
        pucTemp[0] = 0x00;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucTemp);

        // Verify Intra_Hop Aux Mode Set to 0
        for(ucIndex = 0; ucIndex < 10; ucIndex++)
        {
            ScalerDpAuxTxNativeRead(0x00, 0x02, 0x05, 1, pucTemp);

            if((pucTemp[0] & _BIT3) == 0x00)
            {
                break;
            }
            else
            {
                ScalerTimerDelayXms(1);
            }
        }
    }
#endif

    // 3. Set Chanel Coding / Link Rate
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x08, 1, pucDPCD_108);
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x00, 1, pucDPCD_100);

    // 3. Set Link Count and Enhance Framing
    pData[0] = ((BYTE)GET_DP_MAC_TX_DOWNSTREAM_ENHANCE_FRAMING() << 7) | GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM();
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x01, 1, pData);

#if(_DP_TX_FEC_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_FEC_DECODE_DIS_FAIL_RETRAIN);

    // 4. FEC Setting add V2.0
    ScalerDpMacTxFecInitialSetting();
#endif

    // 4. Reset LTTPR Already Pass Num
    CLR_DP_TX_LT_SEGMENT_COMPLETE_NUM();

    // 4. Reset Link Training Flag
    CLR_DP_TX_LT_SHARE_DFP_FAIL();
    CLR_DP_TX_LT_LOOP_CNT();
    CLR_DP_TX_LT_TIMEOUT();

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_LT_TIMEOUT);

#if(_DP_MAC_TX_SUPPORT == _ON)
    CLR_DP_MAC_TX_LINK_ESTABLISH_STATUS();
#endif
#endif

    // 4. Set Analog PHY CMU to gen Link Rate
    ScalerDpPhyTxCMUPowerOn();

    // 4. Initialize Main Link Signal
    ScalerDpPhyTxSignalInitialSetting();
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Inital Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxLTStatusJudge(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        // Set LT State
        if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_LTTPR_EQ_FAIL)
        {
            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_EQ_PHASE);
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
        }
        else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_LTTPR_EQ_PASS)
        {
            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_EQ_PHASE_POLLING);
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
        }
        else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_CDS_FAIL_POLLING)
        {
            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_CDS_PHASE_POLLING);
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
        }
        else
        {
            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_EQ_PHASE);
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
        }

        if(GET_DP_TX_LT_TIMEOUT() == _TRUE)
        {
            CLR_DP_TX_LT_SHARE_DFP_FAIL();
            CLR_DP_TX_LT_TIMEOUT();
            CLR_DP_TX_LT_LOOP_CNT();
            SET_DP_TX_LT_PROCESSING(_FALSE);

            // Set LT State
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_CDS_FAIL);
            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
        }
    }
    else
#endif
    {
        // Set LT State
        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpPhyTxTrainPattern1(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpPhyTxTrainPattern1_128b132b();
    }
    else
#endif
    {
        return ScalerDpPhyTxTrainPattern1_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpPhyTxTrainPattern1_8b10b(void)
{
    BYTE pucTemp[6] = {0};
    BYTE ucRdIntervalTime = 0;

    // Read Training Aux Read Interval
    if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() == _DP_VERSION_1_2)
    {
        ScalerDpPhyTxReadDfpDpcd(_DP_TX_TRAINING_AUX_RD_INTERVAL, 1, &ucRdIntervalTime);

        ucRdIntervalTime &= 0x7F;

        if(ucRdIntervalTime > 0x04)
        {
            ucRdIntervalTime = 0;
        }
    }
    else
    {
        ucRdIntervalTime = 0;
    }

    // Start TP1 Process or Start Link Rate Reduce or Lane Count Reduce
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_NO_RESULT)
    {
        if(GET_DP_TX_LT_PROCESSING() == _FALSE)
        {
            // Recorder Tx Link Traning Start
            SET_DP_TX_LT_PROCESSING(_TRUE);
        }

        // For LTTPR Case Need Reset Cnt & Swing flag
        ScalerDpPhyTxSignalReset();

        ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_TPS1);

        pucTemp[0] = _DP_TP_1 | _DP_SCRAMBLING_DISABLE;
        pucTemp[1] = g_stDpPhyTxLTInfo.ucLane0Adjust;
        pucTemp[2] = g_stDpPhyTxLTInfo.ucLane1Adjust;
        pucTemp[3] = g_stDpPhyTxLTInfo.ucLane2Adjust;
        pucTemp[4] = g_stDpPhyTxLTInfo.ucLane3Adjust;

        // Write DPCD 102h to Start TP1
        ScalerDpPhyTxWriteDfpDpcd(_DP_TX_TRAINING_PATTERN_SET, 5, pucTemp);
    }
    else
    {
        // For LTTPR Case -> Only Closest Tx's Dfp need Change Swing & Pre-emphasis
        if(GET_DP_TX_LT_SEGMENT_COMPLETE_NUM() == 0)
        {
            // Set Output Signal According to Request
            ScalerDpPhyTxMLPHYSet();
        }

        pucTemp[0] = g_stDpPhyTxLTInfo.ucLane0Adjust;
        pucTemp[1] = g_stDpPhyTxLTInfo.ucLane1Adjust;
        pucTemp[2] = g_stDpPhyTxLTInfo.ucLane2Adjust;
        pucTemp[3] = g_stDpPhyTxLTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDpPhyTxWriteDfpDpcd(_DP_TX_TRAINING_LANEX_SET, 4, pucTemp);
    }

    if(ucRdIntervalTime != 0x00)
    {
        // Delay 4 * ucRdIntervalTime ms
        ScalerTimerDelayXms((ucRdIntervalTime << 2) + 1);
    }
    else
    {
        // Delay Time us [100,x]
        DELAY_XUS(100);
    }

    if(GET_DP_TX_LT_DFP_REMAIN_NUM() > 1)
    {
        // Read Lane Status and Request Adjust Level
        ScalerDpPhyTxReadDfpDpcd(_DP_TX_TRAINING_LANEX_STATUS, 5, pucTemp);

        g_stDpPhyTxLTInfo.ucLane01LTStatus = pucTemp[0];
        g_stDpPhyTxLTInfo.ucLane23LTStatus = pucTemp[1];
        g_stDpPhyTxLTInfo.ucAdjustReqLane01 = pucTemp[3];
        g_stDpPhyTxLTInfo.ucAdjustReqLane23 = pucTemp[4];
    }
    else
    {
        // Read Lane Status and Request Adjust Level
        ScalerDpPhyTxReadDfpDpcd(_DP_TX_TRAINING_LANEX_STATUS, 6, pucTemp);

        g_stDpPhyTxLTInfo.ucLane01LTStatus = pucTemp[0];
        g_stDpPhyTxLTInfo.ucLane23LTStatus = pucTemp[1];
        g_stDpPhyTxLTInfo.ucAdjustReqLane01 = pucTemp[4];
        g_stDpPhyTxLTInfo.ucAdjustReqLane23 = pucTemp[5];
    }

    switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            if((GET_DP_TX_LANE3_CR_DONE() == _TRUE) &&
               (GET_DP_TX_LANE2_CR_DONE() == _TRUE) &&
               (GET_DP_TX_LANE1_CR_DONE() == _TRUE) &&
               (GET_DP_TX_LANE0_CR_DONE() == _TRUE))
            {
                return _DP_TX_TRAINING_PATTERN1_PASS;
            }

            if(ScalerDpPhyTxTP1Lane3Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpPhyTxTP1Lane2Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpPhyTxTP1Lane1Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpPhyTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_TWO_LANE:

            if((GET_DP_TX_LANE1_CR_DONE() == _TRUE) &&
               (GET_DP_TX_LANE0_CR_DONE() == _TRUE))
            {
                return _DP_TX_TRAINING_PATTERN1_PASS;
            }

            if(ScalerDpPhyTxTP1Lane1Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpPhyTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_ONE_LANE:
        default:

            if(GET_DP_TX_LANE0_CR_DONE() == _TRUE)
            {
                return _DP_TX_TRAINING_PATTERN1_PASS;
            }

            if(ScalerDpPhyTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;
    }

    return _DP_TX_TRAINING_PATTERN1_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane0Adjust(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpPhyTxTP1Lane0Adjust_128b132b();
    }
    else
#endif
    {
        return ScalerDpPhyTxTP1Lane0Adjust_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane0Adjust_8b10b(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE0_ADJUST_VOL_SWING() + GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == GET_DP_TX_LANE0_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE0_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE0_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE0_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE0_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE0_CURRENT_VOL_SWING(GET_DP_TX_LANE0_ADJUST_VOL_SWING());
    SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane1Adjust(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpPhyTxTP1Lane1Adjust_128b132b();
    }
    else
#endif
    {
        return ScalerDpPhyTxTP1Lane1Adjust_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane1Adjust_8b10b(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE1_ADJUST_VOL_SWING() + GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == GET_DP_TX_LANE1_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE1_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE1_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE1_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE1_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE1_CURRENT_VOL_SWING(GET_DP_TX_LANE1_ADJUST_VOL_SWING());
    SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane2Adjust(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpPhyTxTP1Lane2Adjust_128b132b();
    }
    else
#endif
    {
        return ScalerDpPhyTxTP1Lane2Adjust_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane2Adjust_8b10b(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE2_ADJUST_VOL_SWING() + GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == GET_DP_TX_LANE2_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE2_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE2_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE2_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE2_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE2_CURRENT_VOL_SWING(GET_DP_TX_LANE2_ADJUST_VOL_SWING());
    SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane3Adjust(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpPhyTxTP1Lane3Adjust_128b132b();
    }
    else
#endif
    {
        return ScalerDpPhyTxTP1Lane3Adjust_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane3Adjust_8b10b(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE3_ADJUST_VOL_SWING() + GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == GET_DP_TX_LANE3_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE3_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE3_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE3_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE3_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE3_CURRENT_VOL_SWING(GET_DP_TX_LANE3_ADJUST_VOL_SWING());
    SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpPhyTxTrainPattern2(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        return ScalerDpPhyTxTrainPattern2_128b132b();
    }
    else
#endif
    {
        return ScalerDpPhyTxTrainPattern2_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpPhyTxTrainPattern2_8b10b(void)
{
    BYTE pucTemp[6] = {0};
    BYTE ucRdIntervalTime = 0;

    // Read Training Aux Read Interval
    if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
    {
        ScalerDpPhyTxReadDfpDpcd(_DP_TX_TRAINING_AUX_RD_INTERVAL, 1, &ucRdIntervalTime);

        ucRdIntervalTime &= 0x7F;

        if(ucRdIntervalTime > 0x04)
        {
            ucRdIntervalTime = 0;
        }
    }
    else
    {
        ucRdIntervalTime = 0;
    }

    // Start TP2 Process
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_PASS)
    {
        // Check Dfp LTTPR(TPS4) or Rx Sink
        if(GET_DP_TX_LT_DFP_REMAIN_NUM() == 1)
        {
            // Check TPS Supported
            if(GET_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT() == _TRUE)
            {
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_EYE_PATTERN);

                pucTemp[0] = _DP_TP_4;
            }
            else if(GET_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT() == _TRUE)
            {
                // Disable Scrambling Besides Sending TPS4 Pattern
                // DPCD 00102h BIT5 = 0: Enable Scramble; BIT5 = 1: Disable Scramble;
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_TPS3);

                pucTemp[0] = _DP_TP_3 | _DP_SCRAMBLING_DISABLE;
            }
            else
            {
                // Disable Scrambling Besides Sending TPS4 Pattern
                // DPCD 00102h BIT5 = 0: Enable Scramble; BIT5 = 1: Disable Scramble;
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_TPS2);

                pucTemp[0] = _DP_TP_2 | _DP_SCRAMBLING_DISABLE;
            }
        }
        else
        {
            ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_EYE_PATTERN);

            pucTemp[0] = _DP_TP_4;
        }

        pucTemp[1] = g_stDpPhyTxLTInfo.ucLane0Adjust;
        pucTemp[2] = g_stDpPhyTxLTInfo.ucLane1Adjust;
        pucTemp[3] = g_stDpPhyTxLTInfo.ucLane2Adjust;
        pucTemp[4] = g_stDpPhyTxLTInfo.ucLane3Adjust;

        // Write DPCD 102h-106h to Start TP2
        ScalerDpPhyTxWriteDfpDpcd(_DP_TX_TRAINING_PATTERN_SET, 5, pucTemp);
    }
    else
    {
        // For LTTPR Case -> Only Closest Dfp need Change Swing & Pre
        if(GET_DP_TX_LT_SEGMENT_COMPLETE_NUM() == 0)
        {
            // Set Output Signal According to Request
            ScalerDpPhyTxMLPHYSet();
        }

        pucTemp[0] = g_stDpPhyTxLTInfo.ucLane0Adjust;
        pucTemp[1] = g_stDpPhyTxLTInfo.ucLane1Adjust;
        pucTemp[2] = g_stDpPhyTxLTInfo.ucLane2Adjust;
        pucTemp[3] = g_stDpPhyTxLTInfo.ucLane3Adjust;

        // Write DPCD 103h-106h (Voltage Swing and Pre-emphasis)
        ScalerDpPhyTxWriteDfpDpcd(_DP_TX_TRAINING_LANEX_SET, 4, pucTemp);
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() == _DP_VERSION_1_2)
    {
        pucTemp[0] = (_DP_LANE0_MAX_POST_CURSOR2_REACHED | _DP_LANE1_MAX_POST_CURSOR2_REACHED);
        pucTemp[1] = (_DP_LANE2_MAX_POST_CURSOR2_REACHED | _DP_LANE3_MAX_POST_CURSOR2_REACHED);
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0F, 2, pucTemp);
    }

    if(ucRdIntervalTime != 0x00)
    {
        // Delay 4 * ucRdIntervalTime ms
        ScalerTimerDelayXms((ucRdIntervalTime << 2) + 1);
    }
    else
    {
        // Delay Time us [400,x] Delay 400us
        DELAY_XUS(400);
    }

    if(GET_DP_TX_LT_DFP_REMAIN_NUM() > 1)
    {
        // Read Lane Status and Request Adjust Level
        ScalerDpPhyTxReadDfpDpcd(_DP_TX_TRAINING_LANEX_STATUS, 5, pucTemp);

        g_stDpPhyTxLTInfo.ucLane01LTStatus = pucTemp[0];
        g_stDpPhyTxLTInfo.ucLane23LTStatus = pucTemp[1];
        g_stDpPhyTxLTInfo.ucLaneAlignStatus = pucTemp[2];
        g_stDpPhyTxLTInfo.ucAdjustReqLane01 = pucTemp[3];
        g_stDpPhyTxLTInfo.ucAdjustReqLane23 = pucTemp[4];
    }
    else
    {
        // Read Lane Status and Request Adjust Level
        ScalerDpPhyTxReadDfpDpcd(_DP_TX_TRAINING_LANEX_STATUS, 6, pucTemp);

        g_stDpPhyTxLTInfo.ucLane01LTStatus = pucTemp[0];
        g_stDpPhyTxLTInfo.ucLane23LTStatus = pucTemp[1];
        g_stDpPhyTxLTInfo.ucLaneAlignStatus = pucTemp[2];
        g_stDpPhyTxLTInfo.ucAdjustReqLane01 = pucTemp[4];
        g_stDpPhyTxLTInfo.ucAdjustReqLane23 = pucTemp[5];
    }

    // CDR unlock => Reduce Link Rate or Lane Count and then return to TP1
    // EQ unlock => Adjust Swing and Pre-emphasis until retry more than 5 times
    switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            if((GET_DP_TX_LANE0_CR_DONE() == _TRUE) && (GET_DP_TX_LANE1_CR_DONE() == _TRUE) && (GET_DP_TX_LANE2_CR_DONE() == _TRUE) && (GET_DP_TX_LANE3_CR_DONE() == _TRUE))
            {
                if((GET_DP_TX_LANE0_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE1_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE2_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE3_EQ_DONE() == _TRUE) &&
                   (GET_DP_TX_LANE0_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE1_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE2_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE3_SYMBOL_LOCKED() == _TRUE) &&
                   (GET_DP_TX_LANE_ALIGN_DONE() == _TRUE))
                {
                    CLR_DP_TX_TP2_CNT();

                    return _DP_TX_TRAINING_PATTERN2_PASS;
                }
            }
            else
            {
                CLR_DP_TX_TP2_CNT();

                // CR unlock case return to do Band Width Config
                return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
            }

            break;

        case _DP_TWO_LANE:

            if((GET_DP_TX_LANE0_CR_DONE() == _TRUE) && (GET_DP_TX_LANE1_CR_DONE() == _TRUE))
            {
                if((GET_DP_TX_LANE0_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE1_EQ_DONE() == _TRUE) &&
                   (GET_DP_TX_LANE0_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE1_SYMBOL_LOCKED() == _TRUE) &&
                   (GET_DP_TX_LANE_ALIGN_DONE() == _TRUE))
                {
                    CLR_DP_TX_TP2_CNT();

                    return _DP_TX_TRAINING_PATTERN2_PASS;
                }
            }
            else
            {
                CLR_DP_TX_TP2_CNT();

                // CR unlock case return to do Band Width Config
                return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
            }

            break;

        case _DP_ONE_LANE:
        default:

            if(GET_DP_TX_LANE0_CR_DONE() == _TRUE)
            {
                if((GET_DP_TX_LANE0_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE0_SYMBOL_LOCKED() == _TRUE) &&
                   (GET_DP_TX_LANE_ALIGN_DONE() == _TRUE))
                {
                    CLR_DP_TX_TP2_CNT();

                    return _DP_TX_TRAINING_PATTERN2_PASS;
                }
            }
            else
            {
                CLR_DP_TX_TP2_CNT();

                // CR unlock case return to do Band Width Config
                return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
            }

            break;
    }

    // EQ unlock => Reduce Lane Count
    if(GET_DP_TX_TP2_CNT() >= 5)
    {
        CLR_DP_TX_TP2_CNT();

        // Lane Count Reduce
        return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }
    else
    {
        ADD_DP_TX_TP2_CNT();
    }

    switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            ScalerDpPhyTxTP2Lane3Adjust();
            ScalerDpPhyTxTP2Lane2Adjust();
            ScalerDpPhyTxTP2Lane1Adjust();
            ScalerDpPhyTxTP2Lane0Adjust();

            break;

        case _DP_TWO_LANE:

            ScalerDpPhyTxTP2Lane1Adjust();
            ScalerDpPhyTxTP2Lane0Adjust();

            break;

        case _DP_ONE_LANE:
        default:

            ScalerDpPhyTxTP2Lane0Adjust();

            break;
    }

    return _DP_TX_TRAINING_PATTERN2_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane0Adjust(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpPhyTxTP2Lane0Adjust_128b132b();
    }
    else
#endif
    {
        ScalerDpPhyTxTP2Lane0Adjust_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane0Adjust_8b10b(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE0_CURRENT_VOL_SWING() + GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE0_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE0_CURRENT_VOL_SWING(GET_DP_TX_LANE0_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane1Adjust(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpPhyTxTP2Lane1Adjust_128b132b();
    }
    else
#endif
    {
        ScalerDpPhyTxTP2Lane1Adjust_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane1Adjust_8b10b(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE1_CURRENT_VOL_SWING() + GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE1_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE1_CURRENT_VOL_SWING(GET_DP_TX_LANE1_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane2Adjust(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpPhyTxTP2Lane2Adjust_128b132b();
    }
    else
#endif
    {
        ScalerDpPhyTxTP2Lane2Adjust_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane2Adjust_8b10b(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE2_CURRENT_VOL_SWING() + GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE2_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE2_CURRENT_VOL_SWING(GET_DP_TX_LANE2_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane3Adjust(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpPhyTxTP2Lane3Adjust_128b132b();
    }
    else
#endif
    {
        ScalerDpPhyTxTP2Lane3Adjust_8b10b();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane3Adjust_8b10b(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE3_CURRENT_VOL_SWING() + GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE3_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE3_CURRENT_VOL_SWING(GET_DP_TX_LANE3_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training Pattern End
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTrainPatternEnd(void)
{
    // Recorder Tx Link Traning End
    SET_DP_TX_LT_PROCESSING(_FALSE);
    CLR_DP_TX_LT_SEGMENT_COMPLETE_NUM();

#if(_DP_TX_FEC_SUPPORT == _ON)
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
    {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
        {
            ScalerDpMacTxPreCodingSet(_ENABLE);

            SET_DP_TX_FEC_ENCODE_128B132B(_ENABLE);

            DebugMessageDpTx("DP2.0TX Link Training End FEC Enable", 0);
        }
#endif
    }
#endif

    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
    {
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
        {
            // Phy Input Data from Tx Mac MST
            SET_DP_MST_TX_ENABLE();
        }
        else
        {
            // Phy Input Data from Tx Mac SST
            CLR_DP_MST_TX_ENABLE();
        }

        ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_IDLE_PATTERN);

        if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
        {
            ScalerDpMacTxSetStreamSource(GET_DP_TX_STREAM_SOURCE());
        }
    }
    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_FAIL)
    {
        // Power Down ML PHY
        ScalerDpPhyTxMLPowerOff();

        ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_IDLE_PATTERN);
    }

    // Write TRAINING_PATTERN_SET = 00
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        pData[0] = _DP_TP_NONE;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pData);
    }
    else
#endif
    {
        pData[0] = _DP_TP_NONE;
        ScalerDpPhyTxWriteDfpDpcd(_DP_TX_TRAINING_PATTERN_SET, 1, pData);
    }
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxMLPHYSet(void)
{
    switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
            {
                // set Lane3~0 PHY voltage swing level
                ScalerDpPhyTxSetSignalLevel_128b132b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_3, GET_DP_TX_LANE3_CURRENT_FFE_PRESET());
                ScalerDpPhyTxSetSignalLevel_128b132b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_2, GET_DP_TX_LANE2_CURRENT_FFE_PRESET());
                ScalerDpPhyTxSetSignalLevel_128b132b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_1, GET_DP_TX_LANE1_CURRENT_FFE_PRESET());
                ScalerDpPhyTxSetSignalLevel_128b132b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_FFE_PRESET());
            }
            else
#endif
            {
                // set Lane3~0 PHY voltage swing level
                ScalerDpPhyTxSetSignalLevel_8b10b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_3, GET_DP_TX_LANE3_CURRENT_VOL_SWING(), GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS());
                ScalerDpPhyTxSetSignalLevel_8b10b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_2, GET_DP_TX_LANE2_CURRENT_VOL_SWING(), GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS());
                ScalerDpPhyTxSetSignalLevel_8b10b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_1, GET_DP_TX_LANE1_CURRENT_VOL_SWING(), GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS());
                ScalerDpPhyTxSetSignalLevel_8b10b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());
            }

            break;

        case _DP_TWO_LANE:

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
            {
                // set Lane1~0 PHY voltage swing level
                ScalerDpPhyTxSetSignalLevel_128b132b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_1, GET_DP_TX_LANE1_CURRENT_FFE_PRESET());
                ScalerDpPhyTxSetSignalLevel_128b132b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_FFE_PRESET());
            }
            else
#endif
            {
                // set Lane1~0 PHY voltage swing level
                ScalerDpPhyTxSetSignalLevel_8b10b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_1, GET_DP_TX_LANE1_CURRENT_VOL_SWING(), GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS());
                ScalerDpPhyTxSetSignalLevel_8b10b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());
            }

            break;

        case _DP_ONE_LANE:
        default:

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
            {
                // set Lane0 PHY voltage swing level
                ScalerDpPhyTxSetSignalLevel_128b132b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_FFE_PRESET());
            }
            else
#endif
            {
                // set Lane0 PHY voltage swing level
                ScalerDpPhyTxSetSignalLevel_8b10b(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());
            }

            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxSignalReset(void)
{
    // Set Voltage Swing and pre-emphasis Variable to level 0
    CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();

    SET_DP_TX_LANE0_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE1_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE2_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE3_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE0_CURRENT_FFE_PRESET(0);
    SET_DP_TX_LANE1_CURRENT_FFE_PRESET(0);
    SET_DP_TX_LANE2_CURRENT_FFE_PRESET(0);
    SET_DP_TX_LANE3_CURRENT_FFE_PRESET(0);

    // Clear TP2 Count
    CLR_DP_TX_TP2_CNT();

    // For LTTPR Case -> Only Closest Tx's Dfp need Change Swing & Pre-emphasis
    if(GET_DP_TX_LT_SEGMENT_COMPLETE_NUM() == 0)
    {
        // Set Output Signal According to Request
        ScalerDpPhyTxMLPHYSet();
    }
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxSignalInitialSetting(void)
{
    BYTE ucPNSwap = 0;

    // Set Voltage Swing and pre-emphasis level 0
    ScalerDpPhyTxSignalReset();

    // Enable BS Symbol Replaced by SR Symbol, only Active in SST Mode
    // Disable DP Tx Scramble
    ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT0), 0x00);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerSetBit(P2B_01_DPTX_ML_PAT_SEL, ~_BIT0, _BIT0);
#endif

    ScalerDpPhyTxSetAltModeLaneMapping(_P0_OUTPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE, _TYPE_C_ORIENTATION_UNFLIP);

    // Set PN Swap
    ucPNSwap = ((_P0_DP_PCB_LANE3_PN_SWAP << 7) | (_P0_DP_PCB_LANE2_PN_SWAP << 6) | (_P0_DP_PCB_LANE1_PN_SWAP << 5) | (_P0_DP_PCB_LANE0_PN_SWAP << 4));

    // PN SWAP
    ScalerSetBit(PEB_14_DPTX_SFIFO_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucPNSwap);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() != _CODING_TYPE_128B132B)
#endif
    {
        ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, ((BYTE)GET_DP_MAC_TX_DOWNSTREAM_ENHANCE_FRAMING() << 2));
    }

    // DPTX power on TX driver and Enable output
    ScalerDpPhyTxSignalLaneSetting();

    // Enable TXFIFO
    ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
    ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : DP Tx0 Bit Change
// Input Value  : Bit
// Output Value : Change Value
//--------------------------------------------------
BYTE ScalerDpPhyTxBitChange(BYTE ucBitChange)
{
    return ((ucBitChange & _BIT0) << 7) | ((ucBitChange & _BIT1) << 5) | ((ucBitChange & _BIT2) << 3) | ((ucBitChange & _BIT3) << 1) | ((ucBitChange & _BIT4) >> 1) | ((ucBitChange & _BIT5) >> 3) | ((ucBitChange & _BIT6) >> 5) | ((ucBitChange & _BIT7) >> 7);
}

//--------------------------------------------------
// Description  : Dp Tx Lane Swap Setting
// Input Value  : Output Port, Pin Assignment, Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxSetAltModeLaneMapping(EnumOutputPort enumOutputPort, EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation)
{
    enumOutputPort = enumOutputPort;
    enumTypeCPinCfgType = enumTypeCPinCfgType;
    enumTypeCOrientation = enumTypeCOrientation;

#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if(ScalerTypeCTxGetPortCtrlType(enumOutputPort) == _TYPE_C_PORT_CTRL_EMBEDDED)
    {
        ScalerDpAuxTxPNSwap(enumTypeCOrientation);

        // Main-Link Lane Setting Start
        // BB0E, bit7-6/5-4/3-2/1-0, The Source Selector of Lane0/1/2/3 of Small FIFO.
        // Used for Lane Swap, 00:Lane0, 01:Lane1, 10:Lane2, 11:lane3, Set Lane Swap
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit(P2B_06_DPTX_LANE_SWAP, ~(_BIT7 | _BIT6), ScalerDpPhyTxGetPcbTypeCLaneMapping(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE0_MAPPING) << 6);
        ScalerSetBit(P2B_06_DPTX_LANE_SWAP, ~(_BIT5 | _BIT4), ScalerDpPhyTxGetPcbTypeCLaneMapping(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE1_MAPPING) << 4);
        ScalerSetBit(P2B_06_DPTX_LANE_SWAP, ~(_BIT3 | _BIT2), ScalerDpPhyTxGetPcbTypeCLaneMapping(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE2_MAPPING) << 2);
        ScalerSetBit(P2B_06_DPTX_LANE_SWAP, ~(_BIT1 | _BIT0), ScalerDpPhyTxGetPcbTypeCLaneMapping(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE3_MAPPING));
#endif

        ScalerSetBit(PBB_0E_DPTX_LANE_SWAP, ~(_BIT7 | _BIT6), ScalerDpPhyTxGetPcbTypeCLaneMapping(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE0_MAPPING) << 6);
        ScalerSetBit(PBB_0E_DPTX_LANE_SWAP, ~(_BIT5 | _BIT4), ScalerDpPhyTxGetPcbTypeCLaneMapping(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE1_MAPPING) << 4);
        ScalerSetBit(PBB_0E_DPTX_LANE_SWAP, ~(_BIT3 | _BIT2), ScalerDpPhyTxGetPcbTypeCLaneMapping(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE2_MAPPING) << 2);
        ScalerSetBit(PBB_0E_DPTX_LANE_SWAP, ~(_BIT1 | _BIT0), ScalerDpPhyTxGetPcbTypeCLaneMapping(enumTypeCOrientation, _P0_DP_TYPE_C_PCB_LANE3_MAPPING));
    }
    else
#endif
    {
        ScalerDpAuxTxPNSwap(_TYPE_C_ORIENTATION_UNFLIP);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit(P2B_06_DPTX_LANE_SWAP, ~(_BIT7 | _BIT6), _P0_DP_PCB_LANE0_MAPPING << 6);
        ScalerSetBit(P2B_06_DPTX_LANE_SWAP, ~(_BIT5 | _BIT4), _P0_DP_PCB_LANE1_MAPPING << 4);
        ScalerSetBit(P2B_06_DPTX_LANE_SWAP, ~(_BIT3 | _BIT2), _P0_DP_PCB_LANE2_MAPPING << 2);
        ScalerSetBit(P2B_06_DPTX_LANE_SWAP, ~(_BIT1 | _BIT0), _P0_DP_PCB_LANE3_MAPPING);
#endif

        ScalerSetBit(PBB_0E_DPTX_LANE_SWAP, ~(_BIT7 | _BIT6), _P0_DP_PCB_LANE0_MAPPING << 6);
        ScalerSetBit(PBB_0E_DPTX_LANE_SWAP, ~(_BIT5 | _BIT4), _P0_DP_PCB_LANE1_MAPPING << 4);
        ScalerSetBit(PBB_0E_DPTX_LANE_SWAP, ~(_BIT3 | _BIT2), _P0_DP_PCB_LANE2_MAPPING << 2);
        ScalerSetBit(PBB_0E_DPTX_LANE_SWAP, ~(_BIT1 | _BIT0), _P0_DP_PCB_LANE3_MAPPING);
    }
}

//--------------------------------------------------
// Description  : Get DP PHY Lane Mapping
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpPhyTxGetPcbTypeCLaneMapping(EnumTypeCOrientation enumTypecOrientation, BYTE ucDpTypecPcbLaneMapping)
{
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

//--------------------------------------------------
// Description  : Dp Tx Signal Lane Setting
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxSignalLaneSetting(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
    {
        ScalerDpPhyTxSignalLaneSetting_128b132b();
    }
    else
#endif
    {
        ScalerDpPhyTxSignalLaneSetting_8b10b();
    }
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxSetSignalLevel_8b10b(EnumDpLinkRate enumDpLinkRate, EnumDpTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis)
{
    BYTE ucIndex = 0;
    BYTE *pucTable;

    // Protect Wrong
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

    ucIndex = (ucVoltageSwing * 4 + ucPreEmphasis) * 3;

    if(enumDpLinkRate == _DP_LINK_HBR3)
    {
        pucTable = tDPTX_HBR3_TABLE;
        DebugMessageDpTx("DP Tx tDPTX_HBR3_TABLE", 0x00);
    }
    else if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        pucTable = tDPTX_HBR2_TABLE;
        DebugMessageDpTx("DP Tx tDPTX_HBR2_TABLE", 0x00);
    }
    else if(enumDpLinkRate == _DP_LINK_HBR)
    {
        pucTable = tDPTX_HBR_TABLE;
        DebugMessageDpTx("DP Tx tDPTX_HBR_TABLE", 0x00);
    }
    else
    {
        pucTable = tDPTX_RBR_TABLE;
        DebugMessageDpTx("DP Tx tDPTX_RBR_TABLE", 0x00);
    }

    switch(enumLaneX)
    {
        case _DP_TX_LANE_3:
            ScalerSetByte(PEB_45_PRE_L3, (pucTable[ucIndex + 0] & 0xFF));// PRE
            ScalerSetByte(PEB_25_MAIN_L3, (pucTable[ucIndex + 1] & 0xFF));// MAIN
            ScalerSetByte(PEB_35_POST_L3, (pucTable[ucIndex + 2] & 0xFF));// POST
            DebugMessageDpTx("DP1.4 VS+PE L3", (ucVoltageSwing * 16 + ucPreEmphasis));
            break;

        case _DP_TX_LANE_2:
            ScalerSetByte(PEB_46_PRE_L2, (pucTable[ucIndex + 0] & 0xFF));
            ScalerSetByte(PEB_26_MAIN_L2, (pucTable[ucIndex + 1] & 0xFF));
            ScalerSetByte(PEB_36_POST_L2, (pucTable[ucIndex + 2] & 0xFF));
            DebugMessageDpTx("DP1.4 VS+PE L2", (ucVoltageSwing * 16 + ucPreEmphasis));
            break;

        case _DP_TX_LANE_1:
            ScalerSetByte(PEB_47_PRE_L1, (pucTable[ucIndex + 0] & 0xFF));
            ScalerSetByte(PEB_27_MAIN_L1, (pucTable[ucIndex + 1] & 0xFF));
            ScalerSetByte(PEB_37_POST_L1, (pucTable[ucIndex + 2] & 0xFF));
            DebugMessageDpTx("DP1.4 VS+PE L1", (ucVoltageSwing * 16 + ucPreEmphasis));
            break;

        case _DP_TX_LANE_0:
            ScalerSetByte(PEB_48_PRE_L0, (pucTable[ucIndex + 0] & 0xFF));
            ScalerSetByte(PEB_28_MAIN_L0, (pucTable[ucIndex + 1] & 0xFF));
            ScalerSetByte(PEB_38_POST_L0, (pucTable[ucIndex + 2] & 0xFF));
            DebugMessageDpTx("DP1.4 VS+PE L0", (ucVoltageSwing * 16 + ucPreEmphasis));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Tx Initial Power Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxPowerOnInitial(void)
{
    ScalerDpPhyTxLoadTrimmingData();
}

//--------------------------------------------------
// Description  : Dp Tx Load Trimming Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxLoadTrimmingData(void)
{
#if(_HW_FUSE_TYPE != _TYPE_NONE)

    BYTE pucEfuseArray[_HW_OTPFUSE_MST_DPTX_IB_TRIMDATA_LEN] = {0};

    DebugMessageDpTx("DPTX IB BEFORE", ScalerGetByte(PEB_08_IB));
    DebugMessageDpTx("DPTX L3 CALIRATE BEFORE", ScalerGetByte(PEB_3A_CALIBRATE_L3));
    DebugMessageDpTx("DPTX L2 CALIBRATE BEFORE", ScalerGetByte(PEB_3B_CALIBRATE_L2));
    DebugMessageDpTx("DPTX L1 CALIBRATE BEFORE", ScalerGetByte(PEB_3C_CALIBRATE_L1));
    DebugMessageDpTx("DPTX L0 CALIBRATE BEFORE", ScalerGetByte(PEB_3D_CALIBRATE_L0));

    if(ScalerOTPMemoryCheckDoneBit() == _TRUE)
    {
        ScalerOTPMemoryReadData(_OTPMEMORY_MST_DPTX_IB_TRIMDATA, &pucEfuseArray[0]);

        DebugMessageDpTx("DPTX OTP0 IB", pucEfuseArray[0]);
        DebugMessageDpTx("DPTX OTP1 CALIBRATE", pucEfuseArray[1]);
        DebugMessageDpTx("DPTX OTP2 CALIBRATE", pucEfuseArray[2]);
        DebugMessageDpTx("DPTX OTP3 CALIBRATE", pucEfuseArray[3]);
        DebugMessageDpTx("DPTX OTP4 CALIBRATE", pucEfuseArray[4]);

        if((pucEfuseArray[0] & 0x07) <= 2)
        {
            g_ucDpPhyTxOTPTrimIb = 0x20;
            DebugMessageDpTx("DPTX IB PASS", g_ucDpPhyTxOTPTrimIb);
        }
        else
        {
            g_ucDpPhyTxOTPTrimIb = (((pucEfuseArray[0] & 0x07) << 4) | ((pucEfuseArray[0] & 0x07) - 3));
            DebugMessageDpTx("DPTX IB FAIL", g_ucDpPhyTxOTPTrimIb);
        }

        ScalerSetBit(PEB_3D_CALIBRATE_L0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucEfuseArray[1] & 0x1F));
        DebugMessageDpTx("DPTX L0 CALIBRATE PASS", ScalerGetByte(PEB_3D_CALIBRATE_L0));

        ScalerSetBit(PEB_3C_CALIBRATE_L1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucEfuseArray[2] & 0x1F));
        DebugMessageDpTx("DPTX L1 CALIBRATE PASS", ScalerGetByte(PEB_3C_CALIBRATE_L1));

        ScalerSetBit(PEB_3B_CALIBRATE_L2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucEfuseArray[3] & 0x1F));
        DebugMessageDpTx("DPTX L2 CALIBRATE PASS", ScalerGetByte(PEB_3B_CALIBRATE_L2));

        ScalerSetBit(PEB_3A_CALIBRATE_L3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucEfuseArray[4] & 0x1F));
        DebugMessageDpTx("DPTX L3 CALIBRATE PASS", ScalerGetByte(PEB_3A_CALIBRATE_L3));
    }
    else
#endif
    {
        g_ucDpPhyTxOTPTrimIb = 0x30;
        ScalerSetBit(PEB_3A_CALIBRATE_L3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));
        ScalerSetBit(PEB_3B_CALIBRATE_L2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));
        ScalerSetBit(PEB_3C_CALIBRATE_L1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));
        ScalerSetBit(PEB_3D_CALIBRATE_L0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));
        DebugMessageDpTx("DPTX IB DEFAULT", g_ucDpPhyTxOTPTrimIb);
        DebugMessageDpTx("DPTX ALL CALIBRATE DEFAULT", ScalerGetByte(PEB_3A_CALIBRATE_L3));
    }
}

//--------------------------------------------------
// Description  : Dp Phy Tx0 Power Process
// Input Value  : enumSwitch    --> Power action description.
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxPowerProcess(EnumPowerTarget enumPowerTarget)
{
    if(enumPowerTarget == _POWER_OFF)
    {
        ScalerDpPhyTxMLPowerOff();
        ScalerDpPhyTxCMUPowerOff();
    }
    else
    {
        ScalerDpPhyTxIbias(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : Dp Tx IBIAS Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxIbias(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(PEB_11_TX_POWER1, ~_BIT6, _BIT6); // DPTX IBHN
    }
    else
    {
        ScalerSetBit(PEB_11_TX_POWER1, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : Dp Tx Band gap Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxBandgap(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Bandgap
    }
}

//--------------------------------------------------
// Description  : Dp Tx CMU Power On
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxCMUPowerOn(void)
{
    WORD usTemp = 0x00;
    g_ucDpPhyTxLinkRate = GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE();

    // Disable Ckusable, FLD, CMU, Power Serializer, TX driver, SSC
    ScalerSetBit(PEB_EE_CMTX_SSCG14, ~_BIT6, 0x00);
    ScalerSetBit(PEB_09_FLD, ~_BIT7, 0x00);
    ScalerSetBit(PEB_11_TX_POWER1, ~_BIT7, 0x00);
    ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PEB_E0_CMTX_SSCG0, ~(_BIT7 | _BIT6), 0x00);

    // Enable LDO, POST DIV=1, PRE DIV=1, Half Rate
    ScalerSetBit(PEB_05_LDO, ~_BIT7, _BIT7);
    ScalerSetBit(PEB_01_DIV, ~_BIT7, 0x00);
    ScalerSetBit(PEB_01_DIV, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~(_BIT1 | _BIT0), 0x00);

    // DIV5, LC DIV, DIV1, MAC, Data, DCC
    switch(g_ucDpPhyTxLinkRate)
    {
        case _DP_LINK_UHBR20:
            ScalerSetBit(PEB_01_DIV, ~_BIT6, 0x00);
            ScalerSetBit(PEB_01_DIV, ~(_BIT5 | _BIT4), 0x00);
            ScalerSetBit(PEB_01_DIV, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(PEB_02_MAC, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT6, _BIT6);
            ScalerSetBit(PEB_53_DCC, ~_BIT1, _BIT1);
            break;

        case _DP_LINK_UHBR13_5:
            ScalerSetBit(PEB_01_DIV, ~_BIT6, 0x00);
            ScalerSetBit(PEB_01_DIV, ~(_BIT5 | _BIT4), _BIT5);
            ScalerSetBit(PEB_01_DIV, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(PEB_02_MAC, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT6, _BIT6);
            ScalerSetBit(PEB_53_DCC, ~_BIT1, _BIT1);
            break;

        case _DP_LINK_UHBR10:
            ScalerSetBit(PEB_01_DIV, ~_BIT6, 0x00);
            ScalerSetBit(PEB_01_DIV, ~(_BIT5 | _BIT4), _BIT5);
            ScalerSetBit(PEB_01_DIV, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(PEB_02_MAC, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT6, _BIT6);
            ScalerSetBit(PEB_53_DCC, ~_BIT1, _BIT1);
            break;

        case _DP_LINK_HBR3:
            ScalerSetBit(PEB_01_DIV, ~_BIT6, 0x00);
            ScalerSetBit(PEB_01_DIV, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
            ScalerSetBit(PEB_01_DIV, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(PEB_02_MAC, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT6, 0x00);
            ScalerSetBit(PEB_53_DCC, ~_BIT1, _BIT1);
            break;

        case _DP_LINK_HBR2:
            ScalerSetBit(PEB_01_DIV, ~_BIT6, 0x00);
            ScalerSetBit(PEB_01_DIV, ~(_BIT5 | _BIT4), _BIT5);
            ScalerSetBit(PEB_01_DIV, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PEB_02_MAC, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT6, 0x00);
            ScalerSetBit(PEB_53_DCC, ~_BIT1, 0x00);
            break;

        case _DP_LINK_HBR:
            ScalerSetBit(PEB_01_DIV, ~_BIT6, 0x00);
            ScalerSetBit(PEB_01_DIV, ~(_BIT5 | _BIT4), _BIT5);
            ScalerSetBit(PEB_01_DIV, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(PEB_02_MAC, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT6, 0x00);
            ScalerSetBit(PEB_53_DCC, ~_BIT1, 0x00);
            break;

        case _DP_LINK_RBR:
            ScalerSetBit(PEB_01_DIV, ~_BIT6, _BIT6);
            ScalerSetBit(PEB_01_DIV, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
            ScalerSetBit(PEB_01_DIV, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(PEB_02_MAC, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT6, 0x00);
            ScalerSetBit(PEB_53_DCC, ~_BIT1, 0x00);
            break;

        default:
            break;
    }

    DebugMessageDpTx("DPTx LinkRate", g_ucDpPhyTxLinkRate);

    // FW Mode
    ScalerSetBit(PEB_EE_CMTX_SSCG14, ~_BIT7, _BIT7);

    ScalerDpPhyTxLCCMUPara();
    ScalerDpPhyTxNFCode();

    if(GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _TRUE)
    {
        ScalerDpPhyTxSSCSet(_ENABLE);
    }
    else
    {
        ScalerDpPhyTxSSCSet(_DISABLE);
    }

    ScalerDpPhyTxFLD();

    // Enable CMU
    ScalerSetBit(PEB_11_TX_POWER1, ~_BIT7, _BIT7);
    ScalerTimerDelayXms(3);

    // Enable FLD
    ScalerSetBit(PEB_09_FLD, ~_BIT7, _BIT7);

    usTemp = 600;
    while((ScalerGetBit(PEB_95_U3_FLD_34, _BIT0) != _BIT0) && (--usTemp != 0))
    {
        DELAY_5US();// FLD Flag
    }

    if(usTemp == 0)
    {
        DebugMessageDpTx("DPTx FLD not locked", 0);
    }

    // Enable Power Serializer
    DELAY_XUS(1000);
    ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    DELAY_5US();

    // Enable Ckusable
    ScalerSetBit(PEB_EE_CMTX_SSCG14, ~_BIT6, _BIT6);

    ScalerDpPhyTxTerm();

    usTemp = 600;
    while((ScalerGetBit(PEB_EE_CMTX_SSCG14, _BIT0) != _BIT0) && (--usTemp != 0))
    {
        DELAY_5US();// Ckusable Flag
    }

    if(usTemp == 0)
    {
        DebugMessageDpTx("DPTX Ckusable not ready", 0);
    }

    // Enable FIFO
    ScalerSetBit(PEB_12_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);
    DebugMessageDpTx("DPTX CMU POWER ON", g_ucDpPhyTxLinkRate);
}

//--------------------------------------------------
// Description  : Dp Tx LC CMU Parameter Set(based on VCO Frequency)
// Input Value  : ulVCOFreq(MHz), ulCMUFreq(MHz)
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxLCCMUPara(void)
{
    // PI_I, Icp, Rs, IB, LS Mode, Reserved
    switch(g_ucDpPhyTxLinkRate)
    {
        case _DP_LINK_UHBR20:
            ScalerSetBit(PEB_00_CMU, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(PEB_06_CP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));
            ScalerSetBit(PEB_07_RS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
            ScalerSetBit(PEB_08_IB, ~(_BIT2 | _BIT1 | _BIT0), ((g_ucDpPhyTxOTPTrimIb & 0x70) >> 4));
            ScalerSetBit(PEB_0B_CMU_LC1, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            ScalerSetByte(PEB_0C_CMU_LC2, 0xD0);
            break;

        case _DP_LINK_UHBR13_5:
            ScalerSetBit(PEB_00_CMU, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
            ScalerSetBit(PEB_06_CP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
            ScalerSetBit(PEB_07_RS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(PEB_08_IB, ~(_BIT2 | _BIT1 | _BIT0), (g_ucDpPhyTxOTPTrimIb & 0x07));
            ScalerSetBit(PEB_0B_CMU_LC1, ~(_BIT2 | _BIT1), 0x00);
            ScalerSetByte(PEB_0C_CMU_LC2, 0xA0);
            break;

        case _DP_LINK_UHBR10:
            ScalerSetBit(PEB_00_CMU, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(PEB_06_CP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));
            ScalerSetBit(PEB_07_RS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
            ScalerSetBit(PEB_08_IB, ~(_BIT2 | _BIT1 | _BIT0), ((g_ucDpPhyTxOTPTrimIb & 0x70) >> 4));
            ScalerSetBit(PEB_0B_CMU_LC1, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            ScalerSetByte(PEB_0C_CMU_LC2, 0xD0);
            break;

        case _DP_LINK_HBR3:
            ScalerSetBit(PEB_00_CMU, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(PEB_06_CP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT1));
            ScalerSetBit(PEB_07_RS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(PEB_08_IB, ~(_BIT2 | _BIT1 | _BIT0), (g_ucDpPhyTxOTPTrimIb & 0x07));
            ScalerSetBit(PEB_0B_CMU_LC1, ~(_BIT2 | _BIT1), 0x00);
            ScalerSetByte(PEB_0C_CMU_LC2, 0xF0);
            break;

        case _DP_LINK_HBR2:
            ScalerSetBit(PEB_00_CMU, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(PEB_06_CP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
            ScalerSetBit(PEB_07_RS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
            ScalerSetBit(PEB_08_IB, ~(_BIT2 | _BIT1 | _BIT0), ((g_ucDpPhyTxOTPTrimIb & 0x70) >> 4));
            ScalerSetBit(PEB_0B_CMU_LC1, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            ScalerSetByte(PEB_0C_CMU_LC2, 0xC0);
            break;

        case _DP_LINK_HBR:
            ScalerSetBit(PEB_00_CMU, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(PEB_06_CP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT1));
            ScalerSetBit(PEB_07_RS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(PEB_08_IB, ~(_BIT2 | _BIT1 | _BIT0), ((g_ucDpPhyTxOTPTrimIb & 0x70) >> 4));
            ScalerSetBit(PEB_0B_CMU_LC1, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            ScalerSetByte(PEB_0C_CMU_LC2, 0xC0);
            break;

        case _DP_LINK_RBR:
            ScalerSetBit(PEB_00_CMU, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
            ScalerSetBit(PEB_06_CP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(PEB_07_RS, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(PEB_08_IB, ~(_BIT2 | _BIT1 | _BIT0), (g_ucDpPhyTxOTPTrimIb & 0x07));
            ScalerSetBit(PEB_0B_CMU_LC1, ~(_BIT2 | _BIT1), 0x00);
            ScalerSetByte(PEB_0C_CMU_LC2, 0xF0);
            break;

        default:
            break;
    }

    // LDOA
    ScalerSetBit(PEB_05_LDO, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // LDO voltage, AV11 orAV33, FLD_CALIBOK
    ScalerSetBit(PEB_0A_CMU_LC, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // IPTAT ratio, IPTAT or IBHN
    ScalerSetBit(PEB_0B_CMU_LC1, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);

    // DCC op isel
    ScalerSetBit(PEB_53_DCC, ~(_BIT3 | _BIT2), _BIT2);

    DebugMessageDpTx("DPTX CMU PARA DONE", g_ucDpPhyTxLinkRate);
}

//--------------------------------------------------
// Description  : Dp Tx Set N.F Code
// Input Value  : ucNcode, ulFcode
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxNFCode(void)
{
    switch(g_ucDpPhyTxLinkRate)
    {
        case _DP_LINK_UHBR20:
            ScalerSetByte(PEB_E8_CMTX_SSCG8, 0x0A);
            ScalerSetByte(PEB_E9_CMTX_SSCG9, 0xA0);
            ScalerSetByte(PEB_EA_CMTX_SSCG10, 0x13);
            ScalerSetByte(PEB_EB_CMTX_SSCG11, 0x5F);
            break;

        case _DP_LINK_UHBR13_5:
            ScalerSetByte(PEB_E8_CMTX_SSCG8, 0x0E);
            ScalerSetByte(PEB_E9_CMTX_SSCG9, 0x70);
            ScalerSetByte(PEB_EA_CMTX_SSCG10, 0x16);
            ScalerSetByte(PEB_EB_CMTX_SSCG11, 0xF3);
            break;

        case _DP_LINK_UHBR10:
            ScalerSetByte(PEB_E8_CMTX_SSCG8, 0x0A);
            ScalerSetByte(PEB_E9_CMTX_SSCG9, 0xA0);
            ScalerSetByte(PEB_EA_CMTX_SSCG10, 0x13);
            ScalerSetByte(PEB_EB_CMTX_SSCG11, 0x5F);
            break;

        case _DP_LINK_HBR3:
            ScalerSetByte(PEB_E8_CMTX_SSCG8, 0x0D);
            ScalerSetByte(PEB_E9_CMTX_SSCG9, 0x00);
            ScalerSetByte(PEB_EA_CMTX_SSCG10, 0x04);
            ScalerSetByte(PEB_EB_CMTX_SSCG11, 0xA8);
            break;

        case _DP_LINK_HBR2:
            ScalerSetByte(PEB_E8_CMTX_SSCG8, 0x0B);
            ScalerSetByte(PEB_E9_CMTX_SSCG9, 0x80);
            ScalerSetByte(PEB_EA_CMTX_SSCG10, 0x12);
            ScalerSetByte(PEB_EB_CMTX_SSCG11, 0x5C);
            break;

        case _DP_LINK_HBR:
            ScalerSetByte(PEB_E8_CMTX_SSCG8, 0x0B);
            ScalerSetByte(PEB_E9_CMTX_SSCG9, 0x80);
            ScalerSetByte(PEB_EA_CMTX_SSCG10, 0x12);
            ScalerSetByte(PEB_EB_CMTX_SSCG11, 0x5C);
            break;

        case _DP_LINK_RBR:
            ScalerSetByte(PEB_E8_CMTX_SSCG8, 0x0D);
            ScalerSetByte(PEB_E9_CMTX_SSCG9, 0x00);
            ScalerSetByte(PEB_EA_CMTX_SSCG10, 0x04);
            ScalerSetByte(PEB_EB_CMTX_SSCG11, 0xA8);
            break;

        default:
            break;
    }
    ScalerSetBit(PEB_E0_CMTX_SSCG0, ~_BIT6, _BIT6);
    ScalerSetBit(PEB_E0_CMTX_SSCG0, ~_BIT6, 0x00);
    DebugMessageDpTx("DPTX NFcode", g_ucDpPhyTxLinkRate);
}

//--------------------------------------------------
// Description  : Dp Tx0 SSC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxSSCSet(BYTE ucSSCEn)
{
    if(ucSSCEn == _ENABLE)
    {
        switch(g_ucDpPhyTxLinkRate) // SSC = -2500PPM
        {
            case _DP_LINK_UHBR20:
                ScalerSetByte(PEB_E4_CMTX_SSCG4, 0x01);
                ScalerSetByte(PEB_E5_CMTX_SSCG5, 0xC7);
                ScalerSetByte(PEB_E6_CMTX_SSCG6, 0x03);
                ScalerSetByte(PEB_E7_CMTX_SSCG7, 0xEE);
                break;

            case _DP_LINK_UHBR13_5:
                ScalerSetByte(PEB_E4_CMTX_SSCG4, 0x01);
                ScalerSetByte(PEB_E5_CMTX_SSCG5, 0xC7);
                ScalerSetByte(PEB_E6_CMTX_SSCG6, 0x05);
                ScalerSetByte(PEB_E7_CMTX_SSCG7, 0x4E);
                break;

            case _DP_LINK_UHBR10:
                ScalerSetByte(PEB_E4_CMTX_SSCG4, 0x01);
                ScalerSetByte(PEB_E5_CMTX_SSCG5, 0xC7);
                ScalerSetByte(PEB_E6_CMTX_SSCG6, 0x03);
                ScalerSetByte(PEB_E7_CMTX_SSCG7, 0xEE);
                break;

            case _DP_LINK_HBR3:
                ScalerSetByte(PEB_E4_CMTX_SSCG4, 0x01);
                ScalerSetByte(PEB_E5_CMTX_SSCG5, 0xC7);
                ScalerSetByte(PEB_E6_CMTX_SSCG6, 0x04);
                ScalerSetByte(PEB_E7_CMTX_SSCG7, 0xC6);
                break;

            case _DP_LINK_HBR2:
                ScalerSetByte(PEB_E4_CMTX_SSCG4, 0x01);
                ScalerSetByte(PEB_E5_CMTX_SSCG5, 0xC7);
                ScalerSetByte(PEB_E6_CMTX_SSCG6, 0x04);
                ScalerSetByte(PEB_E7_CMTX_SSCG7, 0x3E);
                break;

            case _DP_LINK_HBR:
                ScalerSetByte(PEB_E4_CMTX_SSCG4, 0x01);
                ScalerSetByte(PEB_E5_CMTX_SSCG5, 0xC7);
                ScalerSetByte(PEB_E6_CMTX_SSCG6, 0x04);
                ScalerSetByte(PEB_E7_CMTX_SSCG7, 0x3E);
                break;

            case _DP_LINK_RBR:
                ScalerSetByte(PEB_E4_CMTX_SSCG4, 0x01);
                ScalerSetByte(PEB_E5_CMTX_SSCG5, 0xC7);
                ScalerSetByte(PEB_E6_CMTX_SSCG6, 0x04);
                ScalerSetByte(PEB_E7_CMTX_SSCG7, 0xC6);
                break;

            default:
                break;
        }
        ScalerSetBit(PEB_E0_CMTX_SSCG0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(PEB_E0_CMTX_SSCG0, ~(_BIT7 | _BIT6), _BIT7);
        DebugMessageDpTx("DPTX SSC ON", g_ucDpPhyTxLinkRate);
    }
    else
    {
        ScalerSetBit(PEB_E0_CMTX_SSCG0, ~(_BIT7 | _BIT6), 0x00);
        DebugMessageDpTx("DPTX SSC OFF", 0);
    }
}

//--------------------------------------------------
// Description  : Dp Tx FLD Set
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyTxFLD(void)
{
    ScalerSetBit(PEB_09_FLD, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));    // Vc
    ScalerSetBit(PEB_7A_U3_FLD_10, ~(_BIT7 | _BIT2), _BIT7);// Manaul

    switch(g_ucDpPhyTxLinkRate)
    {
        case _DP_LINK_UHBR20:
            ScalerSetByte(PEB_83_U3_FLD_16, 0x00);
            ScalerSetByte(PEB_82_U3_FLD_15, 0x8A);// Dn
            ScalerSetByte(PEB_81_U3_FLD_14, 0x00);
            ScalerSetByte(PEB_80_U3_FLD_13, 0x8D);// Up
            ScalerSetByte(PEB_7B_U3_FLD_11, 0x13);// BAND
            break;

        case _DP_LINK_UHBR13_5:
            ScalerSetByte(PEB_83_U3_FLD_16, 0x00);
            ScalerSetByte(PEB_82_U3_FLD_15, 0xBA);
            ScalerSetByte(PEB_81_U3_FLD_14, 0x00);
            ScalerSetByte(PEB_80_U3_FLD_13, 0xBE);
            ScalerSetByte(PEB_7B_U3_FLD_11, 0x35);
            break;

        case _DP_LINK_UHBR10:
            ScalerSetByte(PEB_83_U3_FLD_16, 0x00);
            ScalerSetByte(PEB_82_U3_FLD_15, 0x8A);
            ScalerSetByte(PEB_81_U3_FLD_14, 0x00);
            ScalerSetByte(PEB_80_U3_FLD_13, 0x8D);
            ScalerSetByte(PEB_7B_U3_FLD_11, 0x13);
            break;

        case _DP_LINK_HBR3:
            ScalerSetByte(PEB_83_U3_FLD_16, 0x00);
            ScalerSetByte(PEB_82_U3_FLD_15, 0xA8);
            ScalerSetByte(PEB_81_U3_FLD_14, 0x00);
            ScalerSetByte(PEB_80_U3_FLD_13, 0xAB);
            ScalerSetByte(PEB_7B_U3_FLD_11, 0x31);
            break;

        case _DP_LINK_HBR2:
            ScalerSetByte(PEB_83_U3_FLD_16, 0x00);
            ScalerSetByte(PEB_82_U3_FLD_15, 0x95);
            ScalerSetByte(PEB_81_U3_FLD_14, 0x00);
            ScalerSetByte(PEB_80_U3_FLD_13, 0x98);
            ScalerSetByte(PEB_7B_U3_FLD_11, 0x22);
            break;

        case _DP_LINK_HBR:
            ScalerSetByte(PEB_83_U3_FLD_16, 0x00);
            ScalerSetByte(PEB_82_U3_FLD_15, 0x95);
            ScalerSetByte(PEB_81_U3_FLD_14, 0x00);
            ScalerSetByte(PEB_80_U3_FLD_13, 0x98);
            ScalerSetByte(PEB_7B_U3_FLD_11, 0x22);
            break;

        case _DP_LINK_RBR:
            ScalerSetByte(PEB_83_U3_FLD_16, 0x00);
            ScalerSetByte(PEB_82_U3_FLD_15, 0xA8);
            ScalerSetByte(PEB_81_U3_FLD_14, 0x00);
            ScalerSetByte(PEB_80_U3_FLD_13, 0xAB);
            ScalerSetByte(PEB_7B_U3_FLD_11, 0x31);
            break;

        default:
            break;
    }
    ScalerSetByte(PEB_85_U3_FLD_18, 0x00);
    ScalerSetByte(PEB_84_U3_FLD_17, 0x04);
    ScalerSetBit(PEB_7A_U3_FLD_10, ~(_BIT7 | _BIT2), (_BIT7 | _BIT2));// Auto
    DebugMessageDpTx("DPTx FLD", g_ucDpPhyTxLinkRate);
}

//--------------------------------------------------
// Description  : DP Tx Tx Term
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTerm(void)
{
    // TERM

    // Calibrate R
    // L3
    ScalerSetBit(PEB_3A_CALIBRATE_L3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));
    ScalerSetBit(PEB_3A_CALIBRATE_L3, ~_BIT7, _BIT7);
    // L2
    ScalerSetBit(PEB_3B_CALIBRATE_L2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));
    ScalerSetBit(PEB_3B_CALIBRATE_L2, ~_BIT7, _BIT7);
    // L1
    ScalerSetBit(PEB_3C_CALIBRATE_L1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));
    ScalerSetBit(PEB_3C_CALIBRATE_L1, ~_BIT7, _BIT7);
    // L0
    ScalerSetBit(PEB_3D_CALIBRATE_L0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));
    ScalerSetBit(PEB_3D_CALIBRATE_L0, ~_BIT7, _BIT7);

    // Tx drv ldo sel
    // L3
    ScalerSetBit(PEB_30_TX_DRV_LDO_L3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit(PEB_30_TX_DRV_LDO_L3, ~_BIT7, 0x00);
    // L2
    ScalerSetBit(PEB_31_TX_DRV_LDO_L2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit(PEB_31_TX_DRV_LDO_L2, ~_BIT7, 0x00);
    // L1
    ScalerSetBit(PEB_32_TX_DRV_LDO_L1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit(PEB_32_TX_DRV_LDO_L1, ~_BIT7, 0x00);
    // L0
    ScalerSetBit(PEB_33_TX_DRV_LDO_L0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit(PEB_33_TX_DRV_LDO_L0, ~_BIT7, 0x00);

    // Slice
    // L3
    ScalerSetBit(PEB_20_SLICE_L3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    // L2
    ScalerSetBit(PEB_21_SLICE_L2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    // L1
    ScalerSetBit(PEB_22_SLICE_L1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    // L0
    ScalerSetBit(PEB_23_SLICE_L0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Dp Tx Signal Lane Setting 8b10b
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxSignalLaneSetting_8b10b(void)
{
    switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_ONE_LANE:

            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, 0x00);

            SET_DP_MAC_TX_REG_DAISY_CHAIN_LANE_NUM(1);
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            break;

        case _DP_TWO_LANE:

            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3));
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, 0x00);

            SET_DP_MAC_TX_REG_DAISY_CHAIN_LANE_NUM(2);
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _DP_FOUR_LANE:

            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, 0x00);

            SET_DP_MAC_TX_REG_DAISY_CHAIN_LANE_NUM(3);
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power off
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxMLPowerOff(void)
{
    // Disable Power Serializer, TX driver
    ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    DebugMessageDpTx("DPTX ML POWER OFF", 0);
}

//--------------------------------------------------
// Description  : Dp Tx CMU Power Off
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxCMUPowerOff(void)
{
    // Disable DCC
    ScalerSetBit(PEB_53_DCC, ~_BIT1, 0x00);
    // Disable Watch Dog
    ScalerSetBit(PEB_A4_CMTX_CMU_WD1, ~_BIT7, 0x00);
    // Disable SSC
    ScalerSetBit(PEB_E0_CMTX_SSCG0, ~(_BIT7 | _BIT6), 0x00);
    // Disable CKUSABLE
    ScalerSetBit(PEB_EE_CMTX_SSCG14, ~_BIT6, 0x00);
    // Disable Power Serializer, TX driver
    ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    DELAY_XUS(10);
    // Disable FLD
    ScalerSetBit(PEB_09_FLD, ~_BIT7, 0x00);
    // Disable CMU, LDO, IBHN
    ScalerSetBit(PEB_11_TX_POWER1, ~_BIT7, 0x00);
    ScalerSetBit(PEB_05_LDO, ~_BIT7, 0x00);
    ScalerSetBit(PEB_11_TX_POWER1, ~_BIT6, 0x00);
    DebugMessageDpTx("DPTX POWER OFF", 0);
}

//--------------------------------------------------
// Description  : Dp Tx PHY Auto Test Config
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxAutoTest(void)
{
    BYTE ucTestPattern = 0;

    // Read CTS Test Request Type
    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x18, 1, &ucTestPattern) == _TRUE)
    {
        SET_DP_TX_CTS_TEST_REQUEST_TYPE(ucTestPattern);
    }
    else
    {
        return _FALSE;
    }

    if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_PHY_TEST_PATTERN) != _DP_TX_CTS_PHY_TEST_PATTERN)
    {
        return _FALSE;
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_PHY_DP20) == _DP_TX_CTS_PHY_DP20)
    {
        SET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE(_CODING_TYPE_128B132B);
        DebugMessageDpTx("DP Tx DP20", 0x01);
        return ScalerDpPhyTxAutoTest_128b132b();
    }
    else
#endif
    {
        SET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE(_CODING_TYPE_8B10B);
        DebugMessageDpTx("DP Tx DP14", 0x00);
        return ScalerDpPhyTxAutoTest_8b10b();
    }
}

//--------------------------------------------------
// Description  : Dp Tx PHY Auto Test Config
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxAutoTest_8b10b(void)
{
    BYTE pucData[16] = {0};
    BYTE ucDpVersion = 0x00;
    BYTE ucNO_TEST_PATTERN = 0;
    BYTE ucSCRAMBLING_DISABLE = 0;
    BYTE ucRECOVERED_CLOCK_OUT_EN = 0x10;
    BYTE ucLINK_QUAL_PATTERN_SET = 0x00;
    BYTE ucLINK_QUAL_PATTERN_SET_TEMP = 0x00;
    BYTE uclane0 = 0;
    BYTE uclane1 = 0;
    BYTE uclane2 = 0;
    BYTE uclane3 = 0;
    BYTE ucDpLinkRate = 0;

    DebugMessageDpTx("MST DPTx AutoTest Start", 0x00);

    if(ScalerDpAuxTxNativeRead(0x00, 0x00, 0x00, 16, pucData) == _FALSE)
    {
        return _FALSE;
    }

    if((pucData[14] & _BIT7) == _BIT7)
    {
        DebugMessageDpTx("MST DP Tx Donwstream Caps. Extended Field Support", pucData[14]);

        if(ScalerDpAuxTxNativeRead(0x00, 0x22, 0x00, 16, pucData) == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerDpAuxTxNativeRead(0x00, 0x22, 0x10, 1, pData) == _FALSE)
        {
            return _FALSE;
        }

        DebugMessageDpTx("MST DP Tx 02210h", (pData[0] & _BIT3));

        // VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
        if((pData[0] & _BIT3) == _BIT3)
        {
            SET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT();
        }
    }

    SET_DP_MAC_TX_DOWNSTREAM_ENHANCE_FRAMING((bit)(pucData[2] & _BIT7));

    // Down-Spread
    if((pucData[3] & _BIT0) == _BIT0)
    {
        SET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD((bit)(pucData[3] & _BIT0));

        // Set Down Spread
        pData[0] = (BYTE)GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() << 4;

        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x07, 1, pData);
        DebugMessageDpTx("DP Tx SSC ON", 0x01);
    }
    else
    {
        SET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD(0);
        DebugMessageDpTx("DP Tx SSC OFF", 0x00);
    }

    // Read Data Rate
    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x19, 1, pucData) == _FALSE)
    {
        return _FALSE;
    }

    switch(pucData[0])
    {
        default:
        case 0x06:
            SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_RBR);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_RBR);
            DebugMessageDpTx("Auto DPTx _DP_LINK_RBR", 0x00);
            break;

        case 0x0A:
            SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_HBR);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR);
            DebugMessageDpTx("Auto DPTx _DP_LINK_HBR", 0x00);
            break;

        case 0x14:
            SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_HBR2);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR2);
            DebugMessageDpTx("Auto DPTx _DP_LINK_HBR2", 0x00);
            break;

        case 0x1E:
            SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_HBR3);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_HBR3);
            DebugMessageDpTx("Auto DPTx _DP_LINK_HBR3", 0x00);
            break;
    }

    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x20, 1, pucData) == _FALSE)
    {
        return _FALSE;
    }

    switch(pucData[0] & 0x1F)
    {
        case 0x01:
            SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(_DP_LINK_1_LANE);
            DebugMessageDpTx("Auto DPTx _DP_LINK_1_LANE", 0x00);
            break;

        case 0x02:
            SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(_DP_LINK_2_LANE);
            DebugMessageDpTx("Auto DPTx _DP_LINK_2_LANE", 0x00);
            break;

        case 0x04:
            SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(_DP_LINK_4_LANE);
            DebugMessageDpTx("Auto DPTx _DP_LINK_4_LANE", 0x00);
            break;

        default:
            break;
    }

    // Initialize Main Link Signal
    ScalerDpPhyTxSignalInitialSetting();

    ScalerDpAuxTxNativeRead(0x00, 0x02, 0x48, 1, pucData);

    switch(pucData[0] & 0x07)
    {
        // No test pattern selected
        case 0x00:

            // Disable ENHANCE
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);

            // Enable skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);
            ucNO_TEST_PATTERN = 1;
            ucLINK_QUAL_PATTERN_SET = 0;

            DebugMessageDpTx("Auto DPTx No test pattern", 0x00);
            break;

        // D10.2 without scrambling
        case 0x01:

            // Disable ENHANCE
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);

            // Disable Scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, 0x00);

            // Enable skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, 0x00);

            // D10.2 Pattern
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x11);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x11);

            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 1;

            DebugMessageDpTx("Auto DPTx D10_2", 0x00);
            break;

        // Symbol_Error_Measurement_Count
        case 0x02:

            // Disable ENHANCE
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);
            ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6 | _BIT0), 0x00);
            ScalerSetByte(PBB_A9_MN_M_VID_H, 0x00);
            ScalerSetByte(PBB_AA_MN_M_VID_M, 0x00);
            ScalerSetByte(PBB_AB_MN_M_VID_L, 0x00);
            ScalerSetByte(PBB_AC_MN_N_VID_H, 0x00);
            ScalerSetByte(PBB_AD_MN_N_VID_M, 0x00);
            ScalerSetByte(PBB_AE_MN_N_VID_L, 0x00);
            ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT6 | _BIT0), _BIT6);
            ScalerSetByte(PBC_20_AUD_TS_MAUD_H, 0x00);
            ScalerSetByte(PBC_21_AUD_TS_MAUD_M, 0x00);
            ScalerSetByte(PBC_22_AUD_TS_MAUD_L, 0x00);
            ScalerSetByte(PBC_23_AUD_TS_NAUD_H, 0x00);
            ScalerSetByte(PBC_24_AUD_TS_NAUD_M, 0x00);
            ScalerSetByte(PBC_25_AUD_TS_NAUD_L, 0x00);
            ScalerSetBit(PBB_C8_VBID_FW_CTL, ~_BIT0, _BIT0);
            ScalerSetByte(PBB_C7_VBID, 0x00);

            // Enable Scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, _BIT0);

            // Enable skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, _BIT4);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0xB1);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0xB1);

            ucSCRAMBLING_DISABLE = 0;
            ucLINK_QUAL_PATTERN_SET = 2;

            DebugMessageDpTx("Auto DPTx SYMBOL_ERROR", 0x00);
            break;

        // PRBS7
        case 0x03:

            // Disable ENHANCE
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);

            // Disable Scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, 0x00);

            // Enable skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, 0x00);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x55);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x55);

            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 3;

            DebugMessageDpTx("Auto DPTx PRBS7", 0x00);
            break;

        // 80-bit custom pattern transmitted
        case 0x04:

            // Disable ENHANCE
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);

            // Disable Scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, 0x00);

            // Enable skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, 0x00);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x61);
            ScalerDpAuxTxNativeRead(0x00, 0x02, 0x50, 10, pucData);
            ScalerSetByte(PBB_02_CUSTOM_PATTERN_0, ScalerDpPhyTxBitChange(pucData[0]));
            ScalerSetByte(PBB_03_CUSTOM_PATTERN_1, ScalerDpPhyTxBitChange(pucData[1]));
            ScalerSetByte(PBB_04_CUSTOM_PATTERN_2, ScalerDpPhyTxBitChange(pucData[2]));
            ScalerSetByte(PBB_05_CUSTOM_PATTERN_3, ScalerDpPhyTxBitChange(pucData[3]));
            ScalerSetByte(PBB_06_CUSTOM_PATTERN_4, ScalerDpPhyTxBitChange(pucData[4]));
            ScalerSetByte(PBB_07_CUSTOM_PATTERN_5, ScalerDpPhyTxBitChange(pucData[5]));
            ScalerSetByte(PBB_08_CUSTOM_PATTERN_6, ScalerDpPhyTxBitChange(pucData[6]));
            ScalerSetByte(PBB_09_CUSTOM_PATTERN_7, ScalerDpPhyTxBitChange(pucData[7]));
            ScalerSetByte(PBB_0A_CUSTOM_PATTERN_8, ScalerDpPhyTxBitChange(pucData[8]));
            ScalerSetByte(PBB_0B_CUSTOM_PATTERN_9, ScalerDpPhyTxBitChange(pucData[9]));

            ucLINK_QUAL_PATTERN_SET = 4;
            ucSCRAMBLING_DISABLE = 1;

            DebugMessageDpTx("Auto DPTx 80BITS", 0x00);
            break;

        // CP2520 Pattern 1
        case 0x05:

            // Disable ENHANCE
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);

            // Enable skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);

            // Enable Scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, _BIT0);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, 0x00);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x71);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x71);

            // Select CP2520 pattern 1
            ScalerSetByte(PBB_0C_COMPLIANCE_EYE_PATTERN, 0x00);

            ucSCRAMBLING_DISABLE = 0;
            ucLINK_QUAL_PATTERN_SET = 5;

            DebugMessageDpTx("Auto DPTx CP2520_1", 0x00);
            break;

        // CP2520 Pattern 2
        case 0x06:

            // Disable ENHANCE
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);

            // Enable skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);

            // Enable Scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, _BIT0);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, 0x00);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x71);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x71);

            // Select CP2520 pattern 2
            ScalerSetByte(PBB_0C_COMPLIANCE_EYE_PATTERN, 0x01);

            ucSCRAMBLING_DISABLE = 0;
            ucLINK_QUAL_PATTERN_SET = 6;

            DebugMessageDpTx("Auto DPTx CP2520_2", 0x00);
            break;

        // TPS4
        case 0x07:

            // Disable ENHANCE
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, 0x00);

            // Enable skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);

            // Enable Scramble
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, _BIT0);
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT4, 0x00);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x71);
            ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x71);

            // Select CP2520 pattern 3
            ScalerSetByte(PBB_0C_COMPLIANCE_EYE_PATTERN, 0x02);

            ucSCRAMBLING_DISABLE = 0;
            ucLINK_QUAL_PATTERN_SET = 7;

            DebugMessageDpTx("Auto DPTx TPS4", 0x00);
            break;

        default:
            break;
    }

    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x06, 2, pucData) == _FALSE)
    {
        return _FALSE;
    }

    SET_DP_TX_LANE0_CURRENT_VOL_SWING(pucData[0] & 0x03);
    SET_DP_TX_LANE1_CURRENT_VOL_SWING((pucData[0] & 0x30) >> 4);
    SET_DP_TX_LANE2_CURRENT_VOL_SWING(pucData[1] & 0x03);
    SET_DP_TX_LANE3_CURRENT_VOL_SWING((pucData[1] & 0x30) >> 4);

    SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS((pucData[0] & 0x0C) >> 2);
    SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS((pucData[0] & 0xC0) >> 6);
    SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS((pucData[1] & 0x0C) >> 2);
    SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS((pucData[1] & 0xC0) >> 6);

    DebugMessageDpTx("DP Tx VSPE", pucData[0]);
    DebugMessageDpTx("DP Tx VSPE", pucData[1]);

    uclane0 = (pucData[0] & 0x03) | ((pucData[0] & 0x0C) << 1);
    if((pucData[0] & 0x03) == 0x03)
    {
        uclane0 = uclane0 | _BIT2;
    }

    if((pucData[0] & 0x0C) == 0x0C)
    {
        uclane0 = uclane0 | _BIT5;
    }

    uclane1 = ((pucData[0] & 0x30) >> 4) | ((pucData[0] & 0xC0) >> 3);
    if((pucData[0] & 0x30) == 0x30)
    {
        uclane1 = uclane1 | _BIT2;
    }
    if((pucData[0] & 0xC0) == 0xC0)
    {
        uclane1 = uclane1 | _BIT5;
    }

    uclane2 = (pucData[1] & 0x03) | ((pucData[1] & 0x0C) << 1);
    if((pucData[1] & 0x03) == 0x03)
    {
        uclane2 = uclane2 | _BIT2;
    }
    if((pucData[1] & 0x0C) == 0x0C)
    {
        uclane2 = uclane2 | _BIT5;
    }

    uclane3 = ((pucData[1] & 0x30) >> 4) | ((pucData[1] & 0xC0) >> 3);
    if((pucData[1] & 0x30) == 0x30)
    {
        uclane3 = uclane3 | _BIT2;
    }
    if((pucData[1] & 0xC0) == 0xC0)
    {
        uclane3 = uclane3 | _BIT5;
    }

    if(ucDpVersion == _DP_VERSION_1_1)
    {
        ucLINK_QUAL_PATTERN_SET_TEMP = (ucLINK_QUAL_PATTERN_SET & 0x03) << 2;
    }
    else
    {
        ucLINK_QUAL_PATTERN_SET_TEMP = 0x00;
    }

    if(ucSCRAMBLING_DISABLE == 0x01)
    {
        pucData[0] = 0x20 | ucRECOVERED_CLOCK_OUT_EN | ucLINK_QUAL_PATTERN_SET_TEMP;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucData);
    }
    else
    {
        pucData[0] = 0x00 | ucRECOVERED_CLOCK_OUT_EN | ucLINK_QUAL_PATTERN_SET_TEMP;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucData);
    }

    pucData[0] = uclane0;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x03, 1, pucData);
    pucData[0] = uclane1;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x04, 1, pucData);
    pucData[0] = uclane2;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x05, 1, pucData);
    pucData[0] = uclane3;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x06, 1, pucData);

    if(ucSCRAMBLING_DISABLE == 0x01)
    {
        pucData[0] = 0x20 | ucRECOVERED_CLOCK_OUT_EN | ucLINK_QUAL_PATTERN_SET_TEMP;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucData);
    }
    else
    {
        pucData[0] = 0x00 | ucRECOVERED_CLOCK_OUT_EN | ucLINK_QUAL_PATTERN_SET_TEMP;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucData);
    }

    pucData[0] = uclane0;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x03, 1, pucData);
    pucData[0] = uclane1;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x04, 1, pucData);
    pucData[0] = uclane2;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x05, 1, pucData);
    pucData[0] = uclane3;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x06, 1, pucData);

    if(ucNO_TEST_PATTERN == 1)
    {
        ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        DebugMessageDpTx("Auto DP Tx Power OFF", 0x00);
    }
    else
    {
        ScalerDpPhyTxCMUPowerOn();

        ScalerDpPhyTxMLPHYSet();

        ScalerDpPhyTxSignalLaneSetting_8b10b();
        DebugMessageDpTx("Auto DP Tx Power ON", 0x01);
    }

    if(ucDpVersion >= _DP_VERSION_1_2)
    {
        pucData[0] = ucLINK_QUAL_PATTERN_SET;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0B, 1, pucData);
        pucData[0] = ucLINK_QUAL_PATTERN_SET;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0C, 1, pucData);
        pucData[0] = ucLINK_QUAL_PATTERN_SET;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0D, 1, pucData);
        pucData[0] = ucLINK_QUAL_PATTERN_SET;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0E, 1, pucData);
    }

    ucDpLinkRate = GET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE();

    // Set Link Rate
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x00, 1, &ucDpLinkRate);

    // Set Link Count Number
    pData[0] = GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM();
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x01, 1, pData);

    pData[0] = 0xF7;
    ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x18, 1, pData);

    pData[0] = 0x01;
    ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x60, 1, pData);

    DebugMessageDpTx("MST DP Tx Auto Test End", 0x01);

    return _TRUE;
}

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx Auto Test
// Input Value  :
// Output Value : _FALSE or _TURE
//--------------------------------------------------
bit ScalerDpPhyTxAutoTest_128b132b(void)
{
    BYTE pucData[16];
    BYTE ucNO_TEST_PATTERN = 0;
    BYTE ucSCRAMBLING_DISABLE = 0;
    BYTE ucLINK_QUAL_PATTERN_SET = 0x00;
    BYTE ucSquarePatternNum = 0x00;
    BYTE uclane0 = 0;
    BYTE uclane1 = 0;
    BYTE uclane2 = 0;
    BYTE uclane3 = 0;
    BYTE uc264TestPattern = 0;
    BYTE pucDPCD_108[1] = {0};
    BYTE pucDPCD_100[1] = {0};
    BYTE ucPreCursorFlag = 1;
    BYTE ucPostCursorFlag = 1;
    BYTE ucLttprClockSwitch = 0;

    memset(pucData, 0, sizeof(pucData));

    DebugMessageDpTx("Auto DPTx Start", 0x00);

    if(ScalerDpAuxTxNativeRead(0x00, 0x00, 0x00, 16, pucData) == _FALSE)
    {
        return _FALSE;
    }

    if((pucData[14] & _BIT7) == _BIT7)
    {
        DebugMessageDpTx("Auto DPTx Donwstream Caps. Extended Field Support", pucData[14]);

        if(ScalerDpAuxTxNativeRead(0x00, 0x22, 0x00, 16, pucData) == _FALSE)
        {
            return _FALSE;
        }

        if(ScalerDpAuxTxNativeRead(0x00, 0x22, 0x10, 1, pData) == _FALSE)
        {
            return _FALSE;
        }

        DebugMessageDpTx("Auto DPTx 02210h", (pData[0] & _BIT3));

        // VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
        if((pData[0] & _BIT3) == _BIT3)
        {
            SET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT();
        }
    }

    SET_DP_MAC_TX_DOWNSTREAM_ENHANCE_FRAMING((bit)(pucData[2] & _BIT7));

    // Down-Spread
    if((pucData[3] & _BIT0) == _BIT0)
    {
        SET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD((bit)(pucData[3] & _BIT0));

        // Set Down Spread
        pData[0] = (BYTE)GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() << 4;

        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x07, 1, pData);
        DebugMessageDpTx("DP Tx SSC ON", 0x01);
    }
    else
    {
        SET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD(0);
        DebugMessageDpTx("DP Tx SSC OFF", 0x00);
    }

    // Read Data Rate
    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x19, 1, pucData) == _FALSE)
    {
        return _FALSE;
    }

    switch(pucData[0])
    {
        default:
        case 0x01:
            SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_UHBR10);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_UHBR10);
            DebugMessageDpTx("Auto DPTx _DP_LINK_UHBR10", 0x00);
            break;

        case 0x04:
            SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_UHBR13_5);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_UHBR13_5);
            DebugMessageDpTx("Auto DPTx _DP_LINK_UHBR13_5", 0x00);
            break;

        case 0x02:
            SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_UHBR20);
            SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(_DP_LINK_UHBR20);
            DebugMessageDpTx("Auto DPTx _DP_LINK_UHBR20", 0x00);
            break;
    }

    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x20, 1, pucData) == _FALSE)
    {
        return _FALSE;
    }

    switch(pucData[0] & 0x1F)
    {
        case 0x01:
            SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(_DP_LINK_1_LANE);
            DebugMessageDpTx("Auto DPTx _DP_LINK_1_LANE", 0x00);
            break;

        case 0x02:
            SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(_DP_LINK_2_LANE);
            DebugMessageDpTx("Auto DPTx _DP_LINK_2_LANE", 0x00);
            break;

        case 0x04:
            SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(_DP_LINK_4_LANE);
            DebugMessageDpTx("Auto DPTx _DP_LINK_4_LANE", 0x00);
            break;

        default:
            break;
    }

    // Initialize Main Link Signal
    ScalerDpPhyTxSignalInitialSetting();

    ScalerDpAuxTxNativeRead(0x00, 0x02, 0x48, 1, pucData);

    ucLttprClockSwitch = pucData[0] & _BIT7;

    switch(pucData[0] & 0x7F)
    {
        // No test pattern selected
        case 0x00:
            ucNO_TEST_PATTERN = 1;
            ucLINK_QUAL_PATTERN_SET = 0;
            DebugMessageDpTx("Auto DPTx No test pattern", 0x00);
            break;

        // PRBS7
        case 0x03:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x31);
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x03;
            DebugMessageDpTx("Auto DPTx PRBS7", 0x00);
            break;

        // 128b/132b_TPS1
        case 0x08:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P2B_01_DPTX_ML_PAT_SEL, ~_BIT0, _BIT0);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), _BIT7);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x08;
            DebugMessageDpTx("Auto DPTx TPS1", 0x00);
            break;

        // 128b/132b_TPS2
        case 0x10:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P2B_01_DPTX_ML_PAT_SEL, ~_BIT0, 0x00);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P2B_07_DPTX_FUNC_MODE, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT1));
            ucSCRAMBLING_DISABLE = 0;
            ucLINK_QUAL_PATTERN_SET = 0x10;
            DebugMessageDpTx("Auto DPTx TPS2", 0x00);
            break;

        // PRBS9
        case 0x18:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x41);
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x18;
            DebugMessageDpTx("Auto DPTx PRBS9", 0x00);
            break;

        // PRBS11
        case 0x20:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x51);
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x20;
            DebugMessageDpTx("Auto DPTx PRBS11", 0x00);
            break;

        // PRBS15
        case 0x28:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x61);
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x28;
            DebugMessageDpTx("Auto DPTx PRBS15", 0x00);
            break;

        // PRBS23
        case 0x30:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x71);
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x30;
            DebugMessageDpTx("Auto DPTx PRBS23", 0x00);
            break;

        // PRBS31
        case 0x38:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x80);
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x38;
            DebugMessageDpTx("Auto DPTx PRBS31", 0x00);
            break;

        // 264
        case 0x40:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);

            ScalerDpAuxTxNativeRead(0x00, 0x22, 0x30, 16, pucData);
            ScalerSetByte(P2B_04_CUSTOM_PATTERN_0, 0x00);
            ScalerSetByte(P2B_05_CUSTOM_PATTERN_1, pucData[0]);
            for(uc264TestPattern = 1; uc264TestPattern < 16; uc264TestPattern ++)
            {
                ScalerSetByte(P2B_05_CUSTOM_PATTERN_1, pucData[uc264TestPattern]);
            }

            ScalerDpAuxTxNativeRead(0x00, 0x22, 0x40, 16, pucData);
            for(uc264TestPattern = 0; uc264TestPattern < 16; uc264TestPattern ++)
            {
                ScalerSetByte(P2B_05_CUSTOM_PATTERN_1, pucData[uc264TestPattern]);
            }

            ScalerDpAuxTxNativeRead(0x00, 0x22, 0x50, 1, pucData);
            ScalerSetByte(P2B_05_CUSTOM_PATTERN_1, pucData[0]);
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x01);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x40;
            DebugMessageDpTx("Auto DPTx 264", 0x00);
            break;

        // SQnum
        case 0x48:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);

            ScalerDpAuxTxNativeRead(0x00, 0x02, 0x49, 1, pucData);
            ucSquarePatternNum = pucData[0];
            ScalerSetByte(P2B_02_LINK_SQUARE_PATTERN, pucData[0]);
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x21);

            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0F, 1, pucData);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x48;
            ucPreCursorFlag = 1;
            ucPostCursorFlag = 1;
            DebugMessageDpTx("Auto DPTx SQnum", 0x00);
            break;

        // SQnum
        case 0x49:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);

            ScalerDpAuxTxNativeRead(0x00, 0x02, 0x49, 1, pucData);
            ucSquarePatternNum = pucData[0];
            ScalerSetByte(P2B_02_LINK_SQUARE_PATTERN, pucData[0]);
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x21);

            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0F, 1, pucData);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x49;
            ucPreCursorFlag = 0;
            ucPostCursorFlag = 1;
            DebugMessageDpTx("Auto DPTx SQnum", 0x00);
            break;

        // SQnum
        case 0x4A:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);

            ScalerDpAuxTxNativeRead(0x00, 0x02, 0x49, 1, pucData);
            ucSquarePatternNum = pucData[0];
            ScalerSetByte(P2B_02_LINK_SQUARE_PATTERN, pucData[0]);
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x21);

            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0F, 1, pucData);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x4A;
            ucPreCursorFlag = 1;
            ucPostCursorFlag = 0;
            DebugMessageDpTx("Auto DPTx SQnum", 0x00);
            break;

        // SQnum
        case 0x4B:
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetByte(P2B_F4_DPTX_CLK_GEN, 0x01);

            ScalerDpAuxTxNativeRead(0x00, 0x02, 0x49, 1, pucData);
            ucSquarePatternNum = pucData[0];
            ScalerSetByte(P2B_02_LINK_SQUARE_PATTERN, pucData[0]);
            ScalerSetByte(P2B_01_DPTX_ML_PAT_SEL, 0x21);

            ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0F, 1, pucData);
            ucSCRAMBLING_DISABLE = 1;
            ucLINK_QUAL_PATTERN_SET = 0x4B;
            ucPreCursorFlag = 0;
            ucPostCursorFlag = 0;
            DebugMessageDpTx("Auto DPTx SQnum", 0x00);
            break;

        default:
            break;
    }

    if(ucLttprClockSwitch == _BIT7)
    {
        pucData[0] = 0x55; // Transparent mode
        ScalerDpAuxTxNativeWrite(0x0F, 0x00, 0x03, 1, pucData);
    }

    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0x06, 2, pucData) == _FALSE)
    {
        return _FALSE;
    }

    SET_DP_TX_LANE0_CURRENT_FFE_PRESET(pucData[0] & 0x0F);
    uclane0 = pucData[0] & 0x0F;

    SET_DP_TX_LANE1_CURRENT_FFE_PRESET((pucData[0] & 0xF0) >> 4);
    uclane1 = (pucData[0] & 0xF0) >> 4;

    SET_DP_TX_LANE2_CURRENT_FFE_PRESET(pucData[1] & 0x0F);
    uclane2 = pucData[1] & 0x0F;

    SET_DP_TX_LANE3_CURRENT_FFE_PRESET((pucData[1] & 0xF0) >> 4);
    uclane3 = (pucData[1] & 0xF0) >> 4;

    DebugMessageDpTx("DP Tx FFE PRESET", pucData[0]);
    DebugMessageDpTx("DP Tx FFE PRESET", pucData[1]);

    if(ucSCRAMBLING_DISABLE == 0x01)
    {
        pucData[0] = 0x20;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucData);
    }
    else
    {
        pucData[0] = 0x00;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucData);
    }

    pucData[0] = uclane0;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x03, 1, pucData);

    pucData[0] = uclane1;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x04, 1, pucData);

    pucData[0] = uclane2;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x05, 1, pucData);

    pucData[0] = uclane3;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x06, 1, pucData);

    if(ucSCRAMBLING_DISABLE == 0x01)
    {
        pucData[0] = 0x20;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucData);
    }
    else
    {
        pucData[0] = 0x00;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucData);
    }

    pucData[0] = uclane0;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x03, 1, pucData);

    pucData[0] = uclane1;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x04, 1, pucData);

    pucData[0] = uclane2;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x05, 1, pucData);

    pucData[0] = uclane3;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x06, 1, pucData);

    if(ucNO_TEST_PATTERN == 1)
    {
        ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        DebugMessageDpTx("Auto DP Tx Power OFF", 0x00);
    }
    else
    {
        ScalerDpPhyTxCMUPowerOn();

        ScalerDpPhyTxMLPHYSet();

        ScalerDpPhyTxSignalLaneSetting_128b132b();
        DebugMessageDpTx("Auto DP Tx Power ON", 0x01);
    }

    if((ucPreCursorFlag == 1) && (ucPostCursorFlag == 1))
    {
        if((ScalerGetByte(PEB_45_PRE_L3) & 0x3F) != 0x00)
        {
            ScalerSetBit(PEB_45_PRE_L3, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_46_PRE_L2, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_47_PRE_L1, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_48_PRE_L0, ~_BIT7, _BIT7);
        }

        if((ScalerGetByte(PEB_35_POST_L3) & 0x3F) != 0x00)
        {
            ScalerSetBit(PEB_35_POST_L3, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_36_POST_L2, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_37_POST_L1, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_38_POST_L0, ~_BIT7, _BIT7);
        }
    }
    if((ucPreCursorFlag == 0) && (ucPostCursorFlag == 1))
    {
        if((ScalerGetByte(PEB_45_PRE_L3) & 0x3F) != 0x00)
        {
            ScalerSetByte(PEB_45_PRE_L3, 0x0B);
            ScalerSetByte(PEB_46_PRE_L2, 0x0B);
            ScalerSetByte(PEB_47_PRE_L1, 0x0B);
            ScalerSetByte(PEB_48_PRE_L0, 0x0B);
        }

        if((ScalerGetByte(PEB_35_POST_L3) & 0x3F) != 0x00)
        {
            ScalerSetBit(PEB_35_POST_L3, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_36_POST_L2, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_37_POST_L1, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_38_POST_L0, ~_BIT7, _BIT7);
        }
    }
    if((ucPreCursorFlag == 1) && (ucPostCursorFlag == 0))
    {
        if((ScalerGetByte(PEB_45_PRE_L3) & 0x3F) != 0x00)
        {
            ScalerSetBit(PEB_45_PRE_L3, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_46_PRE_L2, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_47_PRE_L1, ~_BIT7, _BIT7);
            ScalerSetBit(PEB_48_PRE_L0, ~_BIT7, _BIT7);
        }

        if((ScalerGetByte(PEB_35_POST_L3) & 0x3F) != 0x00)
        {
            ScalerSetByte(PEB_35_POST_L3, 0x13);
            ScalerSetByte(PEB_36_POST_L2, 0x13);
            ScalerSetByte(PEB_37_POST_L1, 0x13);
            ScalerSetByte(PEB_38_POST_L0, 0x13);
        }
    }
    if((ucPreCursorFlag == 0) && (ucPostCursorFlag == 0))
    {
        if((ScalerGetByte(PEB_45_PRE_L3) & 0x3F) != 0x00)
        {
            ScalerSetByte(PEB_45_PRE_L3, 0x0B);
            ScalerSetByte(PEB_46_PRE_L2, 0x0B);
            ScalerSetByte(PEB_47_PRE_L1, 0x0B);
            ScalerSetByte(PEB_48_PRE_L0, 0x0B);
        }

        if((ScalerGetByte(PEB_35_POST_L3) & 0x3F) != 0x00)
        {
            ScalerSetByte(PEB_35_POST_L3, 0x13);
            ScalerSetByte(PEB_36_POST_L2, 0x13);
            ScalerSetByte(PEB_37_POST_L1, 0x13);
            ScalerSetByte(PEB_38_POST_L0, 0x13);
        }
    }
    DebugMessageDpTx("Auto DP Tx Pre Cursor", ucPreCursorFlag);
    DebugMessageDpTx("Auto DP Tx Post Cursor", ucPostCursorFlag);

    if((ucLINK_QUAL_PATTERN_SET == 0x48) || (ucLINK_QUAL_PATTERN_SET == 0x49) || (ucLINK_QUAL_PATTERN_SET == 0x4A) || (ucLINK_QUAL_PATTERN_SET == 0x4B))
    {
        pucData[0] = ucSquarePatternNum;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0F, 1, pucData);
    }

    pucData[0] = ucLINK_QUAL_PATTERN_SET | ucLttprClockSwitch;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0B, 1, pucData);

    pucData[0] = ucLINK_QUAL_PATTERN_SET | ucLttprClockSwitch;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0C, 1, pucData);

    pucData[0] = ucLINK_QUAL_PATTERN_SET | ucLttprClockSwitch;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0D, 1, pucData);

    pucData[0] = ucLINK_QUAL_PATTERN_SET | ucLttprClockSwitch;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x0E, 1, pucData);

    // Set Link Rate
    switch(GET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE())
    {
        case _DP_LINK_UHBR20:
            pucDPCD_108[0] = _CODING_TYPE_128B132B;
            pucDPCD_100[0] = _DP_DPCD_02215_LINK_UHBR20;
            DebugMessageDpTx("DP Tx _DP_LINK_UHBR20", 0x00);
            break;

        case _DP_LINK_UHBR13_5:
            pucDPCD_108[0] = _CODING_TYPE_128B132B;
            pucDPCD_100[0] = _DP_DPCD_02215_LINK_UHBR13_5;
            DebugMessageDpTx("DP Tx _DP_LINK_UHBR13_5", 0x00);
            break;

        case _DP_LINK_UHBR10:
            pucDPCD_108[0] = _CODING_TYPE_128B132B;
            pucDPCD_100[0] = _DP_DPCD_02215_LINK_UHBR10;
            DebugMessageDpTx("DP Tx _DP_LINK_UHBR10", 0x00);
            break;

        default:
            break;
    }

    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x08, 1, pucDPCD_108);
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x00, 1, pucDPCD_100);

    // Set Link Count Number
    pData[0] = GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM();
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x01, 1, pData);

    pData[0] = 0x01;
    ScalerDpAuxTxNativeWrite(0x00, 0x02, 0x60, 1, pData);
    DebugMessageDpTx("MST DP Tx Auto Test End", 0x01);
    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx ML set FFE Preset
// Input Value  : LaneX - 0~3 FFE Preset - 0~15
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxSetSignalLevel_128b132b(EnumDpLinkRate enumDpLinkRate, EnumDpTxLane enumLaneX, BYTE ucPreSet)
{
    BYTE ucIndex = 0;
    BYTE *pucTable = 0;
    ucIndex = ucPreSet * 3;

    if(enumDpLinkRate == _DP_LINK_UHBR20)
    {
        pucTable = tDPTX_UHBR20_TABLE;
        DebugMessageDpTx("DP Tx tDPTX_UHBR20_TABLE", 0x00);
    }
    else if(enumDpLinkRate == _DP_LINK_UHBR13_5)
    {
        pucTable = tDPTX_UHBR135_TABLE;
        DebugMessageDpTx("DP Tx tDPTX_UHBR135_TABLE", 0x00);
    }
    else
    {
        pucTable = tDPTX_UHBR10_TABLE;
        DebugMessageDpTx("DP Tx tDPTX_UHBR10_TABLE", 0x00);
    }

    switch(enumLaneX)
    {
        case _DP_TX_LANE_3:
            ScalerSetByte(PEB_45_PRE_L3, (pucTable[ucIndex + 0] & 0xFF));
            ScalerSetByte(PEB_25_MAIN_L3, (pucTable[ucIndex + 1] & 0xFF));
            ScalerSetByte(PEB_35_POST_L3, (pucTable[ucIndex + 2] & 0xFF));
            DebugMessageDpTx("DP2.0 Preset L3", ucPreSet);
            break;

        case _DP_TX_LANE_2:
            ScalerSetByte(PEB_46_PRE_L2, (pucTable[ucIndex + 0] & 0xFF));
            ScalerSetByte(PEB_26_MAIN_L2, (pucTable[ucIndex + 1] & 0xFF));
            ScalerSetByte(PEB_36_POST_L2, (pucTable[ucIndex + 2] & 0xFF));
            DebugMessageDpTx("DP2.0 Preset L2", ucPreSet);
            break;

        case _DP_TX_LANE_1:
            ScalerSetByte(PEB_47_PRE_L1, (pucTable[ucIndex + 0] & 0xFF));
            ScalerSetByte(PEB_27_MAIN_L1, (pucTable[ucIndex + 1] & 0xFF));
            ScalerSetByte(PEB_37_POST_L1, (pucTable[ucIndex + 2] & 0xFF));
            DebugMessageDpTx("DP2.0 Preset L1", ucPreSet);
            break;

        case _DP_TX_LANE_0:
            ScalerSetByte(PEB_48_PRE_L0, (pucTable[ucIndex + 0] & 0xFF));
            ScalerSetByte(PEB_28_MAIN_L0, (pucTable[ucIndex + 1] & 0xFF));
            ScalerSetByte(PEB_38_POST_L0, (pucTable[ucIndex + 2] & 0xFF));
            DebugMessageDpTx("DP2.0 Preset L0", ucPreSet);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainPattern1_128b132b(void)
{
    BYTE pucTemp[1] = {0};

    ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_TPS1);

    // Set Default Lane Ajust
    g_stDpPhyTxLTInfo.ucAdjustReqLane01 = 0x00;
    g_stDpPhyTxLTInfo.ucAdjustReqLane23 = 0x00;

    ScalerDpPhyTxTP1Lane0Adjust_128b132b();
    ScalerDpPhyTxTP1Lane1Adjust_128b132b();
    ScalerDpPhyTxTP1Lane2Adjust_128b132b();
    ScalerDpPhyTxTP1Lane3Adjust_128b132b();

    // Set Output Signal According to Request
    ScalerDpPhyTxMLPHYSet();
    // Write DPCD 102h to Start TP1
    pucTemp[0] = _DP_TP_1;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucTemp);

    // Set Link Training Overall Timeout Start
    ScalerTimerActiveTimerEvent(_DP_TX_EQ_MAX_TIME_OUT, _SCALER_TIMER_EVENT_DP_TX_LT_TIMEOUT);
    CLR_DP_TX_LT_TIMEOUT();

    return _DP_TX_TRAINING_NO_RESULT;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainPattern2_128b132b(void)
{
    BYTE pucTemp[5] = {0};
    WORD usRdIntervalTime = 0;

    // Read DFP Aux Rd Interval
    ScalerDpAuxTxNativeRead(0x00, 0x22, 0x16, 1, pucTemp);

    if((pucTemp[0] & _BIT7) == 0x00)
    {
        usRdIntervalTime = ((pucTemp[0] & 0x7F) + 1) * 2 + 1;
    }
    else
    {
        usRdIntervalTime = (pucTemp[0] & 0x7F) + 2;
    }

    // Prevent 3081 CPU Crash
    if(usRdIntervalTime != 0)
    {
        SET_DP_TX_LT_AUX_RD_INTERVAL(usRdIntervalTime);
    }
    else
    {
        SET_DP_TX_LT_AUX_RD_INTERVAL(4);
    }

    // Read Lane Status and Request Adjust Level
    ScalerDpAuxTxNativeRead(0x00, 0x02, 0x06, 2, pucTemp);
    g_stDpPhyTxLTInfo.ucAdjustReqLane01 = pucTemp[0];
    g_stDpPhyTxLTInfo.ucAdjustReqLane23 = pucTemp[1];

    // Set Lane Ajust
    ScalerDpPhyTxTP1Lane0Adjust_128b132b();
    ScalerDpPhyTxTP1Lane1Adjust_128b132b();
    ScalerDpPhyTxTP1Lane2Adjust_128b132b();
    ScalerDpPhyTxTP1Lane3Adjust_128b132b();

    // Set Output Signal According to Request
    ScalerDpPhyTxMLPHYSet();

    ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_TPS2);

    // Write DPCD 102h-106h to Start TP2
    pucTemp[0] = _DP_TP_2;
    pucTemp[1] = g_stDpPhyTxLTInfo.ucLane0Adjust;
    pucTemp[2] = g_stDpPhyTxLTInfo.ucLane1Adjust;
    pucTemp[3] = g_stDpPhyTxLTInfo.ucLane2Adjust;
    pucTemp[4] = g_stDpPhyTxLTInfo.ucLane3Adjust;
    ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 5, pucTemp);
    return _DP_TX_TRAINING_NO_RESULT;
}

//--------------------------------------------------
// Description  : DP Tx Link Training EQ Phase
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainEQPhase_128b132b(void)
{
    EnumDPTxLTResult enumDpTxLTResult = _DP_TX_TRAINING_NO_RESULT;
    BYTE pucTemp[4] = {0};
    WORD usRdIntervalTime = 0;
    WORD usDelayTime = 0;
    WORD usDpRdIntervalThreshold = _DP_TX_AUX_RD_INTERVAL_THRESHOLD;

    if(GET_DP_TX_LT_PROCESSING() == _FALSE)
    {
        // Recorder Tx Link Traning Start
        SET_DP_TX_LT_PROCESSING(_TRUE);

        // Transmit TPS1, Wr 102 0x01 --> TP1
        ScalerDpPhyTxTrainPattern1();

        // Transmit TPS2
        ScalerDpPhyTxTrainPattern2();

        // Reset Link Training Loop Cnt
        CLR_DP_TX_LT_LOOP_CNT();

        CLR_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE();
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_AUX_RD_INTERVAL);
    }

    usRdIntervalTime = GET_DP_TX_LT_AUX_RD_INTERVAL();

    // Delay Aux Rd Interval Time
    while(usDelayTime <= usDpRdIntervalThreshold)
    {
        if(ScalerTimerSearchActiveTimerEvent(_SCALER_TIMER_EVENT_DP_TX_AUX_RD_INTERVAL) == _TRUE)
        {
            return _DP_TX_TRAINING_LTTPR_EQ_FAIL;
        }

        usRdIntervalTime = GET_DP_TX_LT_AUX_RD_INTERVAL();

        if(GET_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE() == _FALSE)
        {
            // Total delay time compare with threshold (if > threshold, break while loop)
            if(usDelayTime + usRdIntervalTime > usDpRdIntervalThreshold)
            {
                ScalerTimerActiveTimerEvent(usRdIntervalTime, _SCALER_TIMER_EVENT_DP_TX_AUX_RD_INTERVAL);
                return _DP_TX_TRAINING_LTTPR_EQ_FAIL;
            }

            ScalerTimerDelayXms(usRdIntervalTime);
            SET_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE();
            usDelayTime += usRdIntervalTime;
        }

        if(GET_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE() == _TRUE)
        {
            enumDpTxLTResult = ScalerDpPhyTxTrainLTTPREQDoneCheck_128b132b();

            if((enumDpTxLTResult == _DP_TX_TRAINING_EQ_PASS) || (enumDpTxLTResult == _DP_TX_TRAINING_EQ_FAIL))
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_LT_TIMEOUT);
                CLR_DP_TX_LT_TIMEOUT();
                return enumDpTxLTResult;
            }
            else if(enumDpTxLTResult == _DP_TX_TRAINING_LTTPR_EQ_PASS)
            {
                return enumDpTxLTResult;
            }
            else if(enumDpTxLTResult == _DP_TX_TRAINING_LTTPR_EQ_FAIL)
            {
                if((GET_DP_TX_LANE0_CURRENT_FFE_PRESET() != GET_DP_TX_LANE0_ADJUST_FFE_PRESET()) ||
                   (GET_DP_TX_LANE1_CURRENT_FFE_PRESET() != GET_DP_TX_LANE1_ADJUST_FFE_PRESET()) ||
                   (GET_DP_TX_LANE2_CURRENT_FFE_PRESET() != GET_DP_TX_LANE2_ADJUST_FFE_PRESET()) ||
                   (GET_DP_TX_LANE3_CURRENT_FFE_PRESET() != GET_DP_TX_LANE3_ADJUST_FFE_PRESET()))
                {
                    // Set Lane Ajust
                    ScalerDpPhyTxTP2Lane0Adjust_128b132b();
                    ScalerDpPhyTxTP2Lane1Adjust_128b132b();
                    ScalerDpPhyTxTP2Lane2Adjust_128b132b();
                    ScalerDpPhyTxTP2Lane3Adjust_128b132b();

                    // Set Output Signal According to Request
                    ScalerDpPhyTxMLPHYSet();
                }

                pucTemp[0] = g_stDpPhyTxLTInfo.ucLane0Adjust;
                pucTemp[1] = g_stDpPhyTxLTInfo.ucLane1Adjust;
                pucTemp[2] = g_stDpPhyTxLTInfo.ucLane2Adjust;
                pucTemp[3] = g_stDpPhyTxLTInfo.ucLane3Adjust;

                // Write DPCD 103h-106h Lane Adjust
                ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x03, 4, pucTemp);
            }
            else
            {
                // Error case
                DebugMessageDpTx("DP20 Tx EQ Phase error", 0);
                return _DP_TX_TRAINING_EQ_FAIL;
            }
        }
    }
    return _DP_TX_TRAINING_EQ_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training EQ Phase Polling
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainEQPhasePolling_128b132b(void)
{
    EnumDPTxLTResult enumDpTxLTResult = GET_DP_TX_LT_RESULT();
    BYTE ucDpRdIntervalThreshold = _DP_TX_AUX_RD_POLLING_THRESHOLD;
    BYTE ucDpRdInterval = 4;
    BYTE ucDpRdIndex = 0;

    for(ucDpRdIndex = 0; ucDpRdIndex < (ucDpRdIntervalThreshold / ucDpRdInterval); ucDpRdIndex++)
    {
        ScalerTimerDelayXms(ucDpRdInterval);

        enumDpTxLTResult = ScalerDpPhyTxTrainRxAlignDoneCheck_128b132b();

        if(enumDpTxLTResult == _DP_TX_TRAINING_EQ_PASS)
        {
            return enumDpTxLTResult;
        }
    }
    return enumDpTxLTResult;
}

//--------------------------------------------------
// Description  : DP Tx Link Training LTTPR EQ Done Check
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainLTTPREQDoneCheck_128b132b(void)
{
    BYTE pucTemp[6] = {0};
    WORD usRdIntervalTime = 0;

    if(GET_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE() == _TRUE)
    {
        CLR_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE();

        // Read Lane Status and Request Adjust Level
        ScalerDpAuxTxNativeRead(0x00, 0x02, 0x02, 6, pucTemp);

#if(_DP_TX_UHBR_PHY_CTS_ONLY == _ON)

        pucTemp[0] = 0x77;
        pucTemp[1] = 0x77;
        pucTemp[2] = 0x8D;

#endif

        g_stDpPhyTxLTInfo.ucLane01LTStatus = pucTemp[0];
        g_stDpPhyTxLTInfo.ucLane23LTStatus = pucTemp[1];
        g_stDpPhyTxLTInfo.ucLaneAlignStatus = pucTemp[2];
        g_stDpPhyTxLTInfo.ucAdjustReqLane01 = pucTemp[4];
        g_stDpPhyTxLTInfo.ucAdjustReqLane23 = pucTemp[5];

        SET_DP_TX_LANE0_ADJUST_FFE_PRESET(pucTemp[4]);
        SET_DP_TX_LANE1_ADJUST_FFE_PRESET(pucTemp[4]);
        SET_DP_TX_LANE2_ADJUST_FFE_PRESET(pucTemp[5]);
        SET_DP_TX_LANE3_ADJUST_FFE_PRESET(pucTemp[5]);

        // Set Share Dfp Fail Flag
        if((pucTemp[2] & _BIT4) == _BIT4)
        {
            SET_DP_TX_LT_SHARE_DFP_FAIL();
        }

        // Read DFP Aux Rd Interval
        ScalerDpAuxTxNativeRead(0x00, 0x22, 0x16, 1, pucTemp);

        if((pucTemp[0] & _BIT7) == 0x00)
        {
            usRdIntervalTime = ((pucTemp[0] & 0x7F) + 1) * 2 + 1;
        }
        else
        {
            usRdIntervalTime = (pucTemp[0] & 0x7F) + 2;
        }

        // Prevent 3081 CPU Crash
        if(usRdIntervalTime != 0)
        {
            SET_DP_TX_LT_AUX_RD_INTERVAL(usRdIntervalTime);
        }
        else
        {
            SET_DP_TX_LT_AUX_RD_INTERVAL(4);
        }

        // Add Link Training Loop Cnt
        ADD_DP_TX_LT_LOOP_CNT();

        // Check if Share Dfp Fail or Linktraing Overall Timeout or Loop Cnt Reach Max -> Return Fail
        if((GET_DP_TX_LT_SHARE_DFP_FAIL() == _TRUE) || (GET_DP_TX_LT_TIMEOUT() == _TRUE) || (GET_DP_TX_LT_LOOP_CNT() > _DP_TX_EQ_MAX_LOOP_CNT))
        {
            CLR_DP_TX_LT_SHARE_DFP_FAIL();
            CLR_DP_TX_LT_TIMEOUT();
            CLR_DP_TX_LT_LOOP_CNT();
            return _DP_TX_TRAINING_EQ_FAIL;
        }
        else
        {
            // Check EQ & Rx Align Done
            switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
            {
                case _DP_FOUR_LANE:

                    if((GET_DP_TX_LANE0_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE1_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE2_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE3_EQ_DONE() == _TRUE))
                    {
                        if(GET_DP_TX_DP_RX_LANE_ALIGN_DONE() == _TRUE)
                        {
                            return _DP_TX_TRAINING_EQ_PASS;
                        }
                        else
                        {
                            return _DP_TX_TRAINING_LTTPR_EQ_PASS;
                        }
                    }
                    else
                    {
                        return _DP_TX_TRAINING_LTTPR_EQ_FAIL;
                    }

                    break;

                case _DP_TWO_LANE:

                    if((GET_DP_TX_LANE0_EQ_DONE() == _TRUE) && (GET_DP_TX_LANE1_EQ_DONE() == _TRUE))
                    {
                        if(GET_DP_TX_DP_RX_LANE_ALIGN_DONE() == _TRUE)
                        {
                            return _DP_TX_TRAINING_EQ_PASS;
                        }
                        else
                        {
                            return _DP_TX_TRAINING_LTTPR_EQ_PASS;
                        }
                    }
                    else
                    {
                        return _DP_TX_TRAINING_LTTPR_EQ_FAIL;
                    }

                    break;

                case _DP_ONE_LANE:
                default:
                    if(GET_DP_TX_LANE0_EQ_DONE() == _TRUE)
                    {
                        if(GET_DP_TX_DP_RX_LANE_ALIGN_DONE() == _TRUE)
                        {
                            return _DP_TX_TRAINING_EQ_PASS;
                        }
                        else
                        {
                            return _DP_TX_TRAINING_LTTPR_EQ_PASS;
                        }
                    }
                    else
                    {
                        return _DP_TX_TRAINING_LTTPR_EQ_FAIL;
                    }
                    break;
            }
        }
    }

    return _DP_TX_TRAINING_NO_RESULT;
}

//--------------------------------------------------
// Description  : DP Tx Link Training Rx Align Done Check
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainRxAlignDoneCheck_128b132b(void)
{
    BYTE pucTemp[2] = {0};

    // Read Lane Status and Request Adjust Level
    ScalerDpAuxTxNativeRead(0x00, 0x02, 0x04, 1, pucTemp);
    g_stDpPhyTxLTInfo.ucLaneAlignStatus = pucTemp[0];

    // Set Share Dfp Fail Flag
    if((pucTemp[0] & _BIT4) == _BIT4)
    {
        SET_DP_TX_LT_SHARE_DFP_FAIL();
    }

    // Check if Share Dfp Fail or Linktraing Overall Timeout
    if((GET_DP_TX_LT_SHARE_DFP_FAIL() == _TRUE) || (GET_DP_TX_LT_TIMEOUT() == _TRUE))
    {
        CLR_DP_TX_LT_SHARE_DFP_FAIL();
        CLR_DP_TX_LT_TIMEOUT();
        return _DP_TX_TRAINING_EQ_FAIL;
    }
    else
    {
        // Check Dp Rx Interlane Align Done
        if(GET_DP_TX_DP_RX_LANE_ALIGN_DONE() == _TRUE)
        {
            return _DP_TX_TRAINING_EQ_PASS;
        }
        else
        {
            return _DP_TX_TRAINING_LTTPR_EQ_PASS;
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training CDS Done Check
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainRxCDSDoneCheck_128b132b(void)
{
    BYTE pucTemp[3] = {0};

    // Read Lane Status and Request Adjust Level
    ScalerDpAuxTxNativeRead(0x00, 0x02, 0x02, 3, pucTemp);

#if(_DP_TX_UHBR_PHY_CTS_ONLY == _ON)

    pucTemp[2] = 0x8D;

#endif

    g_stDpPhyTxLTInfo.ucLane01LTStatus = pucTemp[0];
    g_stDpPhyTxLTInfo.ucLane23LTStatus = pucTemp[1];
    g_stDpPhyTxLTInfo.ucLaneAlignStatus = pucTemp[2];

    // Set Share Dfp Fail Flag
    if((pucTemp[2] & _BIT4) == _BIT4)
    {
        SET_DP_TX_LT_SHARE_DFP_FAIL();
    }

    // Check if Share Dfp Fail or Linktraing Overall Timeout
    if((GET_DP_TX_LT_SHARE_DFP_FAIL() == _TRUE) || (GET_DP_TX_LT_TIMEOUT() == _TRUE))
    {
        CLR_DP_TX_LT_SHARE_DFP_FAIL();
        CLR_DP_TX_LT_TIMEOUT();
        return _DP_TX_TRAINING_CDS_FAIL;
    }
    else
    {
        // Check Dp Rx Interlane Align Done
        switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
        {
            case _DP_FOUR_LANE:

                if((GET_DP_TX_LANE0_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE1_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE2_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE3_SYMBOL_LOCKED() == _TRUE) &&
                   (GET_DP_TX_LANE_CDS_ALIGN_DONE() == _TRUE))
                {
                    return _DP_TX_TRAINING_CDS_PASS;
                }
                else
                {
                    return _DP_TX_TRAINING_CDS_FAIL_POLLING;
                }

            case _DP_TWO_LANE:

                if((GET_DP_TX_LANE0_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE1_SYMBOL_LOCKED() == _TRUE) &&
                   (GET_DP_TX_LANE_CDS_ALIGN_DONE() == _TRUE))
                {
                    return _DP_TX_TRAINING_CDS_PASS;
                }
                else
                {
                    return _DP_TX_TRAINING_CDS_FAIL_POLLING;
                }

            case _DP_ONE_LANE:
            default:
                if((GET_DP_TX_LANE0_SYMBOL_LOCKED() == _TRUE) && (GET_DP_TX_LANE_CDS_ALIGN_DONE() == _TRUE))
                {
                    return _DP_TX_TRAINING_CDS_PASS;
                }
                else
                {
                    return _DP_TX_TRAINING_CDS_FAIL_POLLING;
                }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Link CDS Phase
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainCDSPhase_128b132b(void)
{
    EnumDPTxLTResult enumDpTxLTResult = GET_DP_TX_LT_RESULT();
    WORD usDpTxLTTimeout = 0;
    BYTE ucDpRdIntervalThreshold = _DP_TX_AUX_RD_POLLING_THRESHOLD;
    BYTE ucDpRdInterval = 4;
    BYTE ucDpRdIndex = 0;
    BYTE pucTemp[1] = {0};

    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_EQ_PASS)
    {
        // Transmit TPS2_CDS
        // Write DPCD 102h 0x03 to Start CDS
        pucTemp[0] = 0x03;
        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x02, 1, pucTemp);

        // Set Link Training Overall Timeout Start
        usDpTxLTTimeout = 20 * (GET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM() + 1);
        ScalerTimerActiveTimerEvent(usDpTxLTTimeout, _SCALER_TIMER_EVENT_DP_TX_LT_TIMEOUT);
        CLR_DP_TX_LT_TIMEOUT();
    }

    ucDpRdIndex = ucDpRdIntervalThreshold / ucDpRdInterval;

    for(pucTemp[0] = 0; pucTemp[0] < ucDpRdIndex; pucTemp[0]++)
    {
        ScalerTimerDelayXms(ucDpRdInterval);

        enumDpTxLTResult = ScalerDpPhyTxTrainRxCDSDoneCheck_128b132b();

        if((enumDpTxLTResult == _DP_TX_TRAINING_CDS_PASS) || (enumDpTxLTResult == _DP_TX_TRAINING_CDS_FAIL))
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_LT_TIMEOUT);
            CLR_DP_TX_LT_TIMEOUT();
            return enumDpTxLTResult;
        }
    }
    // Can't Get CDS Done During Aux Read Threshold & Retrun & Next Main Loop Check Again
    return _DP_TX_TRAINING_CDS_FAIL_POLLING;
}

//--------------------------------------------------
// Description  : DP Tx Link Training CDS Phase Polling
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxLTResult ScalerDpPhyTxTrainCDSPhasePolling_128b132b(void)
{
    EnumDPTxLTResult enumDpTxLTResult = GET_DP_TX_LT_RESULT();
    BYTE ucDpRdIntervalThreshold = _DP_TX_AUX_RD_POLLING_THRESHOLD;
    BYTE ucDpRdInterval = 3;
    BYTE ucDpRdIndex = 0;

    for(ucDpRdIndex = 0; ucDpRdIndex < (ucDpRdIntervalThreshold / ucDpRdInterval); ucDpRdIndex++)
    {
        ScalerTimerDelayXms(ucDpRdInterval);
        enumDpTxLTResult = ScalerDpPhyTxTrainRxCDSDoneCheck_128b132b();
        if((enumDpTxLTResult == _DP_TX_TRAINING_CDS_PASS) || (enumDpTxLTResult == _DP_TX_TRAINING_CDS_FAIL))
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_LT_TIMEOUT);
            CLR_DP_TX_LT_TIMEOUT();
            return enumDpTxLTResult;
        }
    }
    // Can't Get CDS Done During Aux Read Threshold & Retrun & Next Main Loop Check Again
    return _DP_TX_TRAINING_CDS_FAIL_POLLING;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane0Adjust_128b132b(void)
{
    SET_DP_TX_LANE0_CURRENT_FFE_PRESET(GET_DP_TX_LANE0_ADJUST_FFE_PRESET());
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane1Adjust_128b132b(void)
{
    SET_DP_TX_LANE1_CURRENT_FFE_PRESET(GET_DP_TX_LANE1_ADJUST_FFE_PRESET());
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane2Adjust_128b132b(void)
{
    SET_DP_TX_LANE2_CURRENT_FFE_PRESET(GET_DP_TX_LANE2_ADJUST_FFE_PRESET());
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpPhyTxTP1Lane3Adjust_128b132b(void)
{
    SET_DP_TX_LANE3_CURRENT_FFE_PRESET(GET_DP_TX_LANE3_ADJUST_FFE_PRESET());
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane0Adjust_128b132b(void)
{
    SET_DP_TX_LANE0_CURRENT_FFE_PRESET(GET_DP_TX_LANE0_ADJUST_FFE_PRESET());
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane1Adjust_128b132b(void)
{
    SET_DP_TX_LANE1_CURRENT_FFE_PRESET(GET_DP_TX_LANE1_ADJUST_FFE_PRESET());
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane2Adjust_128b132b(void)
{
    SET_DP_TX_LANE2_CURRENT_FFE_PRESET(GET_DP_TX_LANE2_ADJUST_FFE_PRESET());
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxTP2Lane3Adjust_128b132b(void)
{
    SET_DP_TX_LANE3_CURRENT_FFE_PRESET(GET_DP_TX_LANE3_ADJUST_FFE_PRESET());
}

//--------------------------------------------------
// Description  : Dp Tx Signal Lane Setting 128b132b
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpPhyTxSignalLaneSetting_128b132b(void)
{
    switch(GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_ONE_LANE:
            ScalerSetBit(P2B_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT3 | _BIT2), _BIT2);
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            break;

        case _DP_TWO_LANE:
            ScalerSetBit(P2B_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT3 | _BIT2), _BIT3);
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _DP_FOUR_LANE:
            ScalerSetBit(P2B_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P2B_00_DP_PHY_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            ScalerSetBit(PEB_10_TX_POWER, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            break;

        default:
            break;
    }
}
#endif
#endif // End for #if(_DP_PHY_TX_SUPPORT == _ON)

