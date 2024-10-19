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
// ID Code      : ScalerDpMacDphyRx0_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_DPHY_RX0_WDINT__

#include "ScalerFunctionInclude.h"
#include "DpMacDphyRx0/ScalerDpMacDphyRx0.h"

#if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX0_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Lane Valid
// Input Value  : None
// Output Value : True --> ok, False --> Lane Valid Error
//--------------------------------------------------
bit ScalerDpMacDphyRx0LaneValidCheck_WDINT(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

    // Enable Lane Valid Detect
    ScalerSetBit_WDINT(PB_00_HD_DP_SEL, ~(_BIT3 | _BIT0), 0x00);
    ScalerSetBit_WDINT(PB_00_HD_DP_SEL, ~(_BIT3 | _BIT0), _BIT3);

    // Delay Time us [150,x]
    DELAY_XUS_EXINT(150);

    switch(ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_ONE_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

            if(ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT7) == 0x00)
            {
                return _FALSE;
            }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)
            if(((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                return _FALSE;
            }
#endif

            break;

        case _DP_TWO_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

            if(ScalerGetBit_WDINT(PB_00_HD_DP_SEL, (_BIT7 | _BIT6)) == 0x00)
            {
                return _FALSE;
            }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)

            if(((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT7) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT6) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT5) == 0x00)) ||
               ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT4) == 0x00)))
            {
                if(((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE0) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT7) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE1) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT6) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE2) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT5) == 0x00)) ||
                   ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE3) && (ScalerGetBit_WDINT(PB_00_HD_DP_SEL, _BIT4) == 0x00)))
                {
                    return _FALSE;
                }
            }
#endif

            break;

        case _DP_FOUR_LANE:

            if(ScalerGetBit_WDINT(PB_00_HD_DP_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpMacDphyRx0DecodeCheck_WDINT(void)
{
    BYTE ucTemp = 3;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    if((GET_DP_ILLEGAL_IDLE_PATTERN_CHECK() == _TRUE) ||
       (ScalerDpMacStreamRxGetSourceTypeJudgeStatus_WDINT(enumInputPort) == _FALSE) ||
       (ScalerDpMacDphyRx0LaneValidCheck_WDINT() == _FALSE))
    {
        return _TRUE;
    }
#endif

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_WDINT(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Check FEC Decode Status
        if(ScalerGetBit_WDINT(PC_80_FEC_DECODE_CTL, _BIT7) != _BIT7)
        {
            return _FALSE;
        }

        while(ucTemp > 0)
        {
            // Disable FEC Accumulated Err Counter
            ScalerSetBit_WDINT(PC_96_FEC_ACCUM_ERR_CTRL_7, ~_BIT0, 0x00);

            // Clear 128b/132b FEC Error Flag
            ScalerSetBit_WDINT(PC_8F_FEC_ACCUM_ERR_CTRL_0, ~_BIT6, _BIT6);

            // Set FEC Accumulated Error Threshold
            ScalerSetBit_WDINT(PC_8F_FEC_ACCUM_ERR_CTRL_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Enable FEC Accumulated Err Counter
            ScalerSetBit_WDINT(PC_96_FEC_ACCUM_ERR_CTRL_7, ~_BIT0, _BIT0);

            // Delay Time us [150,x]
            DELAY_XUS_EXINT(150);

            // DP20 Decode Check
            if(ScalerGetBit_WDINT(PC_8F_FEC_ACCUM_ERR_CTRL_0, _BIT6) == 0x00)
            {
                return _TRUE;
            }

            ucTemp--;
        }

        return _FALSE;
    }
    else
#endif
    // dp14 decode check : 8b10b decode check
    {
        while(ucTemp > 0)
        {
            // Clear 8b/10b Decode Error Flag
            ScalerSetBit_WDINT(PB_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // Delay Time us [150,x]
            DELAY_XUS_EXINT(150);

            switch(ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x00, 0x01, 0x01) & 0x1F)
            {
                case _DP_ONE_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)
                    if(ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)
#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)
                    if(((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
#endif
                    {
                        return _TRUE;
                    }

                    break;

                case _DP_TWO_LANE:

#if(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_AFTER_LANE_MUX)

                    if(ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)
                    {
                        return _TRUE;
                    }

#elif(_HW_DP_RX_DECODE_CHECK_POSITION == _DP_RX_DECODE_CHECK_BEFORE_LANE_MUX)

                    if(((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE0) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE1) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE2) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                       ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_0) == _DP_SCALER_LANE3) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                    {
                        if(((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE0) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE1) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE2) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                           ((ScalerDpPhyRxGetLaneMapping_EXINT0(enumInputPort, _DP_LANE_1) == _DP_SCALER_LANE3) && (ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                        {
                            return _TRUE;
                        }
                    }
#endif

                    break;

                case _DP_FOUR_LANE:

                    if(ScalerGetBit_WDINT(PB_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
                    {
                        return _TRUE;
                    }

                    break;

                default:

                    return _FALSE;

                    break;
            }

            ucTemp--;
        }

        return _FALSE;
    }
}

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mac Rx0 Auxless ALPM Initial
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0AuxlessAlpmEnable_WDINT(EnumInputPort enumInputPort, bit bEn)
{
    WORD usTdrlTime = 0;

    if(bEn == _ENABLE)
    {
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType_WDINT(enumInputPort) == _CODING_TYPE_128B132B)
        {
            ScalerSetBit_WDINT(PB_B0_ALPM_UFP_00, ~_BIT7, _BIT7);

            // Enable ALPM mode
            ScalerSetBit_WDINT(PC_D7_FRAME_DETECT_ALPM_DP20_2, ~_BIT0, _BIT0);

            // Clear Sleep Pattern INT Flag
            ScalerSetBit_WDINT(PC_DC_ALPM_DETECT_DP20, ~_BIT4, _BIT4);

            // Enable Sleep Pattern INT
            ScalerSetBit_WDINT(PC_DC_ALPM_DETECT_DP20, ~(_BIT4 | _BIT3), _BIT3);
        }
        else
#endif
        {
            ScalerSetBit_WDINT(PB_B0_ALPM_UFP_00, ~_BIT7, 0x00);

            // Clear Sleep Pattern INT Flag
            ScalerSetBit_WDINT(PB_4C_ALPM_SLEEP_0, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Enable Sleep Pattern Detect and INT
            ScalerSetBit_WDINT(PB_4C_ALPM_SLEEP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));
        }

        // Mac LFPS Wake Use DPHY lfps_cnt_vld
        ScalerSetBit_WDINT(PB_B0_ALPM_UFP_00, ~_BIT5, 0x00);

        if((ScalerGetBit_WDINT(PB_03_LANE_MUX, (_BIT1 | _BIT0)) == _DP_LANE_0) ||
           (ScalerGetBit_WDINT(PB_03_LANE_MUX, (_BIT1 | _BIT0)) == _DP_LANE_1))
        {
            // ALPM LFPS Detection Select Lane0
            ScalerSetBit_WDINT(PB_BE_ALPM_UFP_14, ~(_BIT7 | _BIT6), 0x00);
        }
        else
        {
            // ALPM LFPS Detection Select Lane2
            ScalerSetBit_WDINT(PB_BE_ALPM_UFP_14, ~(_BIT7 | _BIT6), _BIT7);
        }

        // Toggle Reset UFP ALPM FSM
        ScalerSetBit_WDINT(PB_B0_ALPM_UFP_00, ~_BIT6, _BIT6);
        ScalerSetBit_WDINT(PB_B0_ALPM_UFP_00, ~_BIT6, 0x00);

        // 00116h[3] = 1 => There are no LTTPRs Between DPTx and DPRx
        if(ScalerDpAuxRxGetDpcdBitInfo_WDINT(enumInputPort, 0x00, 0x01, 0x16, _BIT3) == _BIT3)
        {
            // lfps_cnt_vld = 0 => tsilence(80~180ns) + t1(50us) => Normal Data
            // eq_start_time = 0xFF => 255/108Mhz = 2.36us
            ScalerSetByte_WDINT(PB_B3_ALPM_UFP_03, 0xFF);

            // noisy_area_start_time = tsilence(80~180ns) + 40us = ~40.13us => 40.13us * 108Mhz = 4334 = 0x10EE
            ScalerSetBit_WDINT(PB_B4_ALPM_UFP_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x10);
            ScalerSetByte_WDINT(PB_B8_ALPM_UFP_08, 0xEE);

            // cds_start_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit_WDINT(PB_B7_ALPM_UFP_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte_WDINT(PB_BB_ALPM_UFP_11, 0x1C);

            // normal_start_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit_WDINT(PB_C0_ALPM_UFP_15, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte_WDINT(PB_C1_ALPM_UFP_16, 0x1C);

            // start_tps2_err_time = 15us => 15us * 108Mhz = 1620 = 0x654
            ScalerSetBit_WDINT(PB_B5_ALPM_UFP_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
            ScalerSetByte_WDINT(PB_B9_ALPM_UFP_09, 0x54);

            // retrain_sleep_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit_WDINT(PB_B6_ALPM_UFP_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte_WDINT(PB_BA_ALPM_UFP_10, 0x1C);
        }
        else
        {
            // lfps_cnt_vld = 0 => tsilence(80~180ns) + t1(50us) + tDRL => Normal Data
            // eq_start_time = 0xFF => 255/108Mhz = 2.36us
            ScalerSetByte_WDINT(PB_B3_ALPM_UFP_03, 0xFF);

            // noisy_area_start_time = tsilence(80~180ns) + 40us = ~40.13us => 40.13us * 108Mhz = 4334 = 0x10EE
            ScalerSetBit_WDINT(PB_B4_ALPM_UFP_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x10);
            ScalerSetByte_WDINT(PB_B8_ALPM_UFP_08, 0xEE);

            // cds_start_time = 10us => 10us * 108Mhz = 1080 = 0x438
            ScalerSetBit_WDINT(PB_B7_ALPM_UFP_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
            ScalerSetByte_WDINT(PB_BB_ALPM_UFP_11, 0x38);

            usTdrlTime = ScalerDpMacDphyRxAuxlessAlpmTdrlTime_WDINT(enumInputPort);

            // normal_start_time = tDRL =>  tDRL * 108Mhz
            ScalerSetBit_WDINT(PB_C0_ALPM_UFP_15, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usTdrlTime >> 8));
            ScalerSetByte_WDINT(PB_C1_ALPM_UFP_16, usTdrlTime);

            // start_tps2_err_time = 15us => 15us * 108Mhz = 1620 = 0x654
            ScalerSetBit_WDINT(PB_B5_ALPM_UFP_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
            ScalerSetByte_WDINT(PB_B9_ALPM_UFP_09, 0x54);

            // retrain_sleep_time = 5us => 5us * 108Mhz = 540 = 0x21C
            ScalerSetBit_WDINT(PB_B6_ALPM_UFP_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
            ScalerSetByte_WDINT(PB_BA_ALPM_UFP_10, 0x1C);
        }
    }
    else
    {
        // alpm_wake_reset = 1'b1
        ScalerSetBit_WDINT(PB_B0_ALPM_UFP_00, ~_BIT6, _BIT6);

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        // Disable ALPM mode
        ScalerSetBit_WDINT(PC_D7_FRAME_DETECT_ALPM_DP20_2, ~_BIT0, 0x00);

        // Disable Sleep Pattern INT
        ScalerSetBit_WDINT(PC_DC_ALPM_DETECT_DP20, ~(_BIT4 | _BIT3), 0x00);
#endif
        // Disable Sleep Pattern Detect and IRQ
        ScalerSetBit_WDINT(PB_4C_ALPM_SLEEP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Handle DP Related WD Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0WDTimerEventRebuildPhyProc_WDINT(void)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = _DP_RX_AUX_AUTO_MODE;
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

    if(ScalerDpAuxRxGetLTStatus_WDINT(enumInputPort) == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY)
    {
        enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus_WDINT(enumInputPort);

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            ScalerDpAuxRxSetManualMode_WDINT(enumInputPort);
        }

        ScalerDpPhyRxRebuildPhy_WDINT(enumInputPort, ScalerDpAuxRxGetDpcdLinkRate_WDINT(enumInputPort));

        ScalerDpAuxRxSetLTStatus_WDINT(enumInputPort, _DP_NORMAL_LINK_TRAINING_PASS);

        ScalerDpAuxRxSetLinkTrainingSetPhyFinishFlag_WDINT(enumInputPort, _TRUE);

        // De-Skew Circuit Reset
        ScalerSetBit_EXINT(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), 0x00);
        ScalerSetBit_EXINT(PB_0E_DESKEW_PHY, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT6);

        // Mac Reset After Link Clock Stable
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

        // Delay Time us [150,x] Delay for Lane Alignment after Mac Reset
        DELAY_XUS_EXINT(150);

#if(_DP_MST_SUPPORT == _ON)
        SET_DP_MAC_DPHY_RX0_LOAD_NEW_STREAM_PAYLOAD_WDINT();

#if(_DP_TX_SUPPORT == _ON)
        if(enumInputPort == GET_DP_RX_MAIN_PORT())
        {
            // Reset Daisy Chain Async-fifo
            ScalerSetBit_EXINT(PA_00_MST2SST_RESET, ~_BIT6, _BIT6);
            ScalerSetBit_EXINT(PA_00_MST2SST_RESET, ~_BIT6, 0x00);
        }
#endif
#endif

        ScalerDpMacDphyRx0DecodeErrorCountReset_WDINT();

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            ScalerDpAuxRxSetAutoMode_WDINT(enumInputPort);
        }
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Comma Detect
// Input Value  : ON or OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0SetCommaDetect_WDINT(bit bEn)
{
    if(bEn == _ON)
    {
        // [4] Enable Comma Detection
        ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, 0x00);
    }
    else
    {
        // [4] Disable Comma Detection
        ScalerSetBit_EXINT(PB_05_SAMPLE_EDGE, ~_BIT4, _BIT4);
    }
}

//--------------------------------------------------
// Description  : Set DP MAC Clock Selection
// Input Value  : Link Clock or XTAL Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0ClkSelect_WDINT(EnumDpMacClkSelect enumClkSelect)
{
    ScalerSetBit_EXINT(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, enumClkSelect);
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mac Rx0 Load New Stream PayLoad
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0LoadNewStreamPayload_WDINT(void)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType_WDINT(ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0)) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit_WDINT(P9D_01_STHD_CTRL_1, ~_BIT7, 0x00);

        // Delay Up to 65537 Timeslots
        // 3.2ns per Timeslot for UHBR10
        // Delay Time  >=  65537 * 3.2ns = 210ns, as 500ns for Insurance Purposes
        DELAY_XUS_EXINT(500);
        ScalerSetBit_WDINT(P9D_01_STHD_CTRL_1, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        ScalerSetBit_WDINT(PB5_01_STHD_CTRL_1, ~_BIT7, 0x00);
        DELAY_5US_EXINT();
        ScalerSetBit_WDINT(PB5_01_STHD_CTRL_1, ~_BIT7, _BIT7);
    }
}
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDCP 2.2 Link Integrity Check
// Input Value  : _Enable/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_WDINT(bit bEnable)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

    if(ScalerDpAuxRxGetCodingType_WDINT(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_128b132b_WDINT(bEnable);
    }
    else
#endif
    {
        ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_8b10b_WDINT(bEnable);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableDecryption_WDINT(void)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

    if(ScalerDpAuxRxGetCodingType_WDINT(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx0Hdcp2EnableDecryption_128b132b_WDINT();
    }
    else
#endif
    {
        ScalerDpMacDphyRx0Hdcp2EnableDecryption_8b10b_WDINT();
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_WDINT(bit bEnable)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

    if(ScalerDpAuxRxGetCodingType_WDINT(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx0Hdcp2EnableAuthDone_128b132b_WDINT(bEnable);
    }
    else
#endif
    {
        ScalerDpMacDphyRx0Hdcp2EnableAuthDone_8b10b_WDINT(bEnable);
    }
}

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_WDINT(void)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)

    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

    if(ScalerDpAuxRxGetCodingType_WDINT(enumInputPort) == _CODING_TYPE_128B132B)
    {
        ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_128b132b_WDINT();
    }
    else
#endif
    {
        ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_8b10b_WDINT();
    }
}
#endif
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDCP 2.2 Link Integrity Check
// Input Value  : _Enable/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_8b10b_WDINT(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable DP Link Integrity Check
        ScalerSetBit_WDINT(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable DP Link Integrity Check
        ScalerSetBit_WDINT(PB_1B_HDCP_INTGT_VRF, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableDecryption_8b10b_WDINT(void)
{
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    BYTE ucData = 0;

    ScalerHdcp2Proc1_WDINT(pucTemp1, g_stHdcp2RxDownLoadKeyType.pucHdcp2Lc);
    ScalerHdcp2Proc2_WDINT(pucTemp2, g_pucHdcp2Ks);

    // Enable Decryption
    for(ucData = 0; ucData < 16; ucData++)
    {
        g_pucHdcp2InputCipher[ucData] = pucTemp2[ucData] ^ pucTemp1[ucData];

        ScalerSetByte_WDINT(PB_81_HDCP_AES_CIPHER_KEY_15 + ucData, g_pucHdcp2InputCipher[ucData]);
    }

    for(ucData = 0; ucData < 8; ucData++)
    {
        ScalerSetByte_WDINT(PB_55_RIV0 + ucData, g_pucHdcp2Riv[ucData]);
    }

    __real_memcpy(g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxAESCipher, g_pucHdcp2InputCipher, 16);
    __real_memcpy(g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxRiv, g_pucHdcp2Riv, 8);
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_8b10b_WDINT(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable HDCP2.2 Auth. Done
        ScalerSetBit_WDINT(PB_20_HDCP_DEBUG, ~_BIT4, _BIT4);
    }
    else
    {
        // Disable HDCP2.2 Auth. Done
        ScalerSetBit_WDINT(PB_20_HDCP_DEBUG, ~_BIT4, 0x00);
    }
}

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_8b10b_WDINT(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

    // StreamID = 0 for SST Case
    if(ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF5) == 0x00)
    {
        // Set AES Type
        if(ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF6) == 0x00)
        {
            // Type = 0x00
            ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT7, 0x00);

            g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] = 0x00;
        }
        else
        {
            // Type = 0x01 or Type = 0x02 - 0xFF
            ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT7, _BIT7);

            g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] = _BIT7;
        }
    }
#if(_DP_MST_SUPPORT == _ON)
    else
    {
        BYTE pucData[4] = {0};

        // Get # of Stream
        pucData[3] = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF4);

        // Set STx AES Type
        for(pucData[0] = 0; pucData[0] < pucData[3]; pucData[0]++)
        {
            for(pucData[1] = _DP_ST_1; pucData[1] <= _DP_ST_END; pucData[1]++)
            {
                if(GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, pucData[1]) == ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF5 + (2 * pucData[0])))
                {
                    pucData[2] = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF5 + (2 * pucData[0]) + 1);

                    ScalerDpMacDphyRx0Hdcp2SetStxType_8b10b_WDINT(pucData[1], pucData[2]);
                }
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2SetStxType_8b10b_WDINT(EnumDpStreamNum enumDpStreamNum, BYTE ucType)
{
    switch(enumDpStreamNum)
    {
        case _DP_ST_1:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT7, 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT7);
            }
            else
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT7, _BIT7);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT7;
            }

            break;

        case _DP_ST_2:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT6, 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT6);
            }
            else
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT6, _BIT6);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT6;
            }

            break;

        case _DP_ST_3:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT5, 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT5);
            }
            else
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT5, _BIT5);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT5;
            }

            break;

        case _DP_ST_4:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT4, 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT4);
            }
            else
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT4, _BIT4);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT4;
            }

            break;

        case _DP_ST_5:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT3, 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT3);
            }
            else
            {
                ScalerSetBit_WDINT(PB_95_HDCP_ST_TYPE, ~_BIT3, _BIT3);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT3;
            }

            break;

        case _DP_ST_6:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PB_96_DUMMY3, ~_BIT7, 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT7);
            }
            else
            {
                ScalerSetBit_WDINT(PB_96_DUMMY3, ~_BIT7, _BIT7);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT7;
            }

            break;

        default:

            break;
    }
}
#endif
#endif

//--------------------------------------------------
// Description  : Reset 8b10b Error Count value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0DecodeErrorCountReset_WDINT(void)
{
    // Reset 8b10b Error Count Value
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Start Record 8b10b Error Count Value
    ScalerSetBit_EXINT(PB_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
}

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDCP 2.2 Link Integrity Check
// Input Value  : _Enable/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableLinkIntegrityCheck_128b132b_WDINT(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable DP Link Integrity Check
        ScalerSetBit_WDINT(PC_02_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable DP Link Integrity Check
        ScalerSetBit_WDINT(PC_02_HDCP_INTGT_VRF, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableDecryption_128b132b_WDINT(void)
{
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    BYTE ucData = 0;

    ScalerHdcp2Proc1_WDINT(pucTemp1, g_stHdcp2RxDownLoadKeyType.pucHdcp2Lc);
    ScalerHdcp2Proc2_WDINT(pucTemp2, g_pucHdcp2Ks);

    // Enable Decryption
    for(ucData = 0; ucData < 16; ucData++)
    {
        g_pucHdcp2InputCipher[ucData] = pucTemp2[ucData] ^ pucTemp1[ucData];

        ScalerSetByte_WDINT(PC_18_HDCP_AES_CIPHER_KEY_15 + ucData, g_pucHdcp2InputCipher[ucData]);
    }

    for(ucData = 0; ucData < 8; ucData++)
    {
        ScalerSetByte_WDINT(PC_08_RIV0 + ucData, g_pucHdcp2Riv[ucData]);
    }

    __real_memcpy(g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxAESCipher, g_pucHdcp2InputCipher, 16);
    __real_memcpy(g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxRiv, g_pucHdcp2Riv, 8);
}

//--------------------------------------------------
// Description  : Enable HDCP 2.2 Auth Done
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2EnableAuthDone_128b132b_WDINT(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable HDCP2.2 Auth. Done
        ScalerSetBit_WDINT(PC_07_HDCP_DEBUG, ~_BIT0, _BIT0);
    }
    else
    {
        // Disable HDCP2.2 Auth. Done
        ScalerSetBit_WDINT(PC_07_HDCP_DEBUG, ~_BIT0, 0x00);
    }
}

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2SetRepeaterAESType_128b132b_WDINT(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacDphyGetInputPortSwitch_WDINT(_DP_MAC_DPHY_RX0);

    // StreamID = 0 for SST Case
    if(ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF5) == 0x00)
    {
        // Set AES Type
        if(ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF6) == 0x00)
        {
            // Type = 0x00
            ScalerSetBit_WDINT(PC_2C_HDCP_ST_TYPE_1, ~(_BIT5 | _BIT4), 0x00);

            g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] = 0x00;
        }
        else
        {
            // Type = 0x01 or Type = 0x02 - 0xFF
            ScalerSetBit_WDINT(PC_2C_HDCP_ST_TYPE_1, ~(_BIT5 | _BIT4), _BIT4);

            g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] = _BIT4;
        }
    }
#if(_DP_MST_SUPPORT == _ON)
    else
    {
        BYTE pucData[4] = {0};

        // Get # of Stream
        pucData[3] = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF4);

        // Set STx AES Type
        for(pucData[0] = 0; pucData[0] < pucData[3]; pucData[0]++)
        {
            for(pucData[1] = _DP_ST_1; pucData[1] <= _DP_ST_END; pucData[1]++)
            {
                if(GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, pucData[1]) == ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF5 + (2 * pucData[0])))
                {
                    pucData[2] = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF5 + (2 * pucData[0]) + 1);

                    ScalerDpMacDphyRx0Hdcp2SetStxType_128b132b_WDINT(pucData[1], pucData[2]);
                }
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Set AES Type
// Input Value  : None
// Output Value : Message ID Code
//--------------------------------------------------
void ScalerDpMacDphyRx0Hdcp2SetStxType_128b132b_WDINT(EnumDpStreamNum enumDpStreamNum, BYTE ucType)
{
    switch(enumDpStreamNum)
    {
        case _DP_ST_1:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PC_2C_HDCP_ST_TYPE_1, ~(_BIT5 | _BIT4), 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT4);
            }
            else
            {
                ScalerSetBit_WDINT(PC_2C_HDCP_ST_TYPE_1, ~(_BIT5 | _BIT4), _BIT4);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT4;
            }

            break;

        case _DP_ST_2:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PC_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6), 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] &= ~(_BIT6);
            }
            else
            {
                ScalerSetBit_WDINT(PC_2C_HDCP_ST_TYPE_1, ~(_BIT7 | _BIT6), _BIT6);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[0] |= _BIT6;
            }

            break;

        case _DP_ST_3:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PC_2B_HDCP_ST_TYPE_0, ~(_BIT1 | _BIT0), 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT0);
            }
            else
            {
                ScalerSetBit_WDINT(PC_2B_HDCP_ST_TYPE_0, ~(_BIT1 | _BIT0), _BIT0);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT0;
            }

            break;

        case _DP_ST_4:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PC_2B_HDCP_ST_TYPE_0, ~(_BIT3 | _BIT2), 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT2);
            }
            else
            {
                ScalerSetBit_WDINT(PC_2B_HDCP_ST_TYPE_0, ~(_BIT3 | _BIT2), _BIT2);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT2;
            }

            break;

        case _DP_ST_5:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PC_2B_HDCP_ST_TYPE_0, ~(_BIT5 | _BIT4), 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT4);
            }
            else
            {
                ScalerSetBit_WDINT(PC_2B_HDCP_ST_TYPE_0, ~(_BIT5 | _BIT4), _BIT4);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT4;
            }

            break;

        case _DP_ST_6:

            if(ucType == 0x00)
            {
                ScalerSetBit_WDINT(PC_2B_HDCP_ST_TYPE_0, ~(_BIT7 | _BIT6), 0x00);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] &= ~(_BIT6);
            }
            else
            {
                ScalerSetBit_WDINT(PC_2B_HDCP_ST_TYPE_0, ~(_BIT7 | _BIT6), _BIT6);

                g_stDpMacDphyRx0HdcpCipherBackupInfo.pucDpMacRxSTType[1] |= _BIT6;
            }

            break;

        default:

            break;
    }
}
#endif
#endif
#endif // End of #if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MAC_DPHY_RX0_SUPPORT == _ON))
