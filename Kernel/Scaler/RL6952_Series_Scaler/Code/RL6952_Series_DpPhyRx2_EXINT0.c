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
// ID Code      : RL6952_Series_DpPhyRx2_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPPHYRX2_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx2/ScalerDpPhyRx2.h"


#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX2_SUPPORT == _ON))
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
// Description  : DP APhy CDR & FLD Initial Setting
// Input Value  : Link Rate & Ref Method
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2CDRFLDSetting4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);

    enumDpNFCodeRef = enumDpNFCodeRef;

    // using xtal
    ScalerSetBit_EXINT(PE7_1D_ANA_CDR_04, ~_BIT7, 0x00);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // bbpd_pulse_sel = 01 --> Half Rate /3
        ScalerSetBit_EXINT(PE8_19_BBPD_SEL_1, ~(_BIT1 | _BIT0), _BIT0);

        // reg_sel_icp_kp_ratio = 3'b010 --> 8/10
        ScalerSetBit_EXINT(PE8_26_KP_PATH_2, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // bbpd_pulse_sel = 11 --> Full Rate /3
        ScalerSetBit_EXINT(PE8_19_BBPD_SEL_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // reg_sel_icp_kp_ratio = 3'b001 --> 8/8 (Default)
        ScalerSetBit_EXINT(PE8_26_KP_PATH_2, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR3)
    {
        // Disable DFE Delay Increase
        ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~_BIT3, 0x00);
    }
    else
    {
        // Enable DFE Delay Increase
        ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~_BIT3, _BIT3);
    }

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_UHBR10)
    {
        // Disable VCO Low Power Mode
        ScalerSetBit_EXINT(PE8_5D_LOW_POWER_MODE_1, ~(_BIT1 | _BIT0), 0x00);

        // reg_v2i_isel = 2'b10
        ScalerSetBit_EXINT(PE8_2F_DUAL_LOOP_2, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Enable VCO Low Power Mode
        ScalerSetBit_EXINT(PE8_5D_LOW_POWER_MODE_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // reg_v2i_isel = 2'b00
        ScalerSetBit_EXINT(PE8_2F_DUAL_LOOP_2, ~(_BIT1 | _BIT0), 0x00);
    }

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_UHBR13_5)
    {
        // reg_cco_large_iptat = 2'b01 --> 12.5%
        ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // reg_cco_large_iptat = 2'b00 --> 0%
        ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT1 | _BIT0), 0x00);
    }

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) == _DP_LINK_UHBR20)
    {
        // Enable VCO High Power Mode
        ScalerSetBit_EXINT(PE8_5D_LOW_POWER_MODE_1, ~_BIT2, _BIT2);

        // Enable Large Icp
        ScalerSetBit_EXINT(PE8_20_KVCO_1, ~_BIT3, _BIT3);
    }
    else
    {
        // Disable VCO High Power Mode
        ScalerSetBit_EXINT(PE8_5D_LOW_POWER_MODE_1, ~_BIT2, 0x00);

        // Disable Large Icp
        ScalerSetBit_EXINT(PE8_20_KVCO_1, ~_BIT3, 0x00);
    }
    /*
    if(g_enumDpPhyRx2LinkRate == _DP_LINK_HBR2)
    {
        // reg_sel_leqgain_rs = 2'b11 --> High Gain Low Boost
        ScalerSetBit_EXINT(PE8_37_REG_RESERVED_3, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
    else
    {
        // reg_sel_leqgain_rs = 2'b00 --> Low Gain High Boost
        ScalerSetBit_EXINT(PE8_37_REG_RESERVED_3, ~(_BIT1 | _BIT0), 0x00);
    }

    // KP+KI = MAX in FLD Auto Mode
    ScalerSetByte_EXINT(PE7_C6_U3_FLD_22, 0xFF);
    ScalerSetBit_EXINT(PE7_C7_U3_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetByte_EXINT(PE7_AA_FLD_KICO_B02, 0x00);
    ScalerSetByte_EXINT(PE7_AC_FLD_KICO_B04, 0x00);
    ScalerSetByte_EXINT(PE7_CD_FLD_KICO_B09, 0x00);
    ScalerSetByte_EXINT(PE7_CF_FLD_KICO_B11, 0x00);
    */

    // Enable Direct Modulation Mode
    ScalerSetBit_EXINT(PE8_25_KP_PATH_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // manual mode icp_band
    ScalerSetBit_EXINT(PE7_CE_FLD_KICO_B14, ~_BIT0, _BIT0);

    // Max Icp
    ScalerSetBit_EXINT(PE7_87_DP_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetByte_EXINT(PE7_86_DP_FLD_22, 0xFF);

    switch(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort))
    {
        case _DP_LINK_UHBR20:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit_EXINT(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0x110 (10G in 5~10G)
            ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            ScalerSetByte_EXINT(PE7_95_DP_FLD_36, 0x10);
            ScalerSetByte_EXINT(PE7_96_DP_FLD_37, 0x10);
            ScalerSetByte_EXINT(PE7_97_DP_FLD_38, 0x10);
            ScalerSetByte_EXINT(PE7_98_DP_FLD_39, 0x10);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 1250    = 2 *    27     *  10000/16  /  27

            // divid num = 27 = 0x1B
            ScalerSetByte_EXINT(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit_EXINT(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));

            // ref_cnt = 1250 = 0x4E2
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte_EXINT(PE7_7B_DP_FLD_11, 0xE2);
            ScalerSetByte_EXINT(PE7_7D_DP_FLD_13, 0xE2);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 10000 = 14.318  * 2 * (345 + 4) --> N = 0x159
            ScalerSetBit_EXINT(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetByte_EXINT(PE8_57_PLL_3, 0x59);
            ScalerSetByte_EXINT(PE8_58_PLL_4, 0x59);
            ScalerSetByte_EXINT(PE8_59_PLL_5, 0x59);
            ScalerSetByte_EXINT(PE8_5A_PLL_6, 0x59);

            // ideal 20G
            g_pusDpPhyRx2ClockTarget[0] = 0x90AD;

            // peak @10G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xF0);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x00);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x10);

            // reg_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), 0x00);

            // reg_cdr_cp
            ScalerSetByte_EXINT(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_UHBR20());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_UHBR20());
            ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_UHBR20());
            /*
            ScalerSetByte_EXINT(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte_EXINT(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            */
            // reg_slope_band = KVCO
            ScalerSetBit_EXINT(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR20() >> 1);
            ScalerSetBit_EXINT(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR20() >> 1);
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR20());
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR20());

            break;

        case _DP_LINK_UHBR13_5:

            // Sel_DIV = 3'b000 (10-20G)
            ScalerSetBit_EXINT(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0x100 (6.75G in 5~10G)
            ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            ScalerSetByte_EXINT(PE7_95_DP_FLD_36, 0x00);
            ScalerSetByte_EXINT(PE7_96_DP_FLD_37, 0x00);
            ScalerSetByte_EXINT(PE7_97_DP_FLD_38, 0x00);
            ScalerSetByte_EXINT(PE7_98_DP_FLD_39, 0x00);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 500     = 2 *    16     *   6750/16  /  27

            // divid num = 16 = 0x10
            ScalerSetByte_EXINT(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit_EXINT(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // ref_cnt = 500 = 0x1F4
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(PE7_7B_DP_FLD_11, 0xF4);
            ScalerSetByte_EXINT(PE7_7D_DP_FLD_13, 0xF4);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 6750 =  14.318  * 2 * (232 + 4) --> N = 0x0E8
            ScalerSetBit_EXINT(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PE8_57_PLL_3, 0xE8);
            ScalerSetByte_EXINT(PE8_58_PLL_4, 0xE8);
            ScalerSetByte_EXINT(PE8_59_PLL_5, 0xE8);
            ScalerSetByte_EXINT(PE8_5A_PLL_6, 0xE8);

            // ideal 13.5G
            g_pusDpPhyRx2ClockTarget[0] = 0x61A8;

            // peak @6.75G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT1 | _BIT0));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xE1);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x01);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x11);

            // reg_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), 0x00);

            // reg_cdr_cp
            ScalerSetByte_EXINT(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_UHBR13P5());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_UHBR13P5());
            ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_UHBR13P5());
            /*
            ScalerSetByte_EXINT(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte_EXINT(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            */
            // reg_slope_band = KVCO
            ScalerSetBit_EXINT(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR13P5() >> 1);
            ScalerSetBit_EXINT(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR13P5() >> 1);
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR13P5());
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR13P5());

            break;

        case _DP_LINK_UHBR10:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit_EXINT(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0x120 (10G in 5~10G)
            ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(PE7_95_DP_FLD_36, 0x90);
            ScalerSetByte_EXINT(PE7_96_DP_FLD_37, 0x90);
            ScalerSetByte_EXINT(PE7_97_DP_FLD_38, 0x90);
            ScalerSetByte_EXINT(PE7_98_DP_FLD_39, 0x90);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 625    = 2 *    27     *  5000/16  /  27

            // divid num = 27 = 0x1B
            ScalerSetByte_EXINT(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit_EXINT(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));

            // ref_cnt = 625 = 0x271
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetByte_EXINT(PE7_7B_DP_FLD_11, 0x71);
            ScalerSetByte_EXINT(PE7_7D_DP_FLD_13, 0x71);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 5000 = 14.318  * 2 * (171 + 4) --> N = 0xAB
            ScalerSetBit_EXINT(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PE8_57_PLL_3, 0xAB);
            ScalerSetByte_EXINT(PE8_58_PLL_4, 0xAB);
            ScalerSetByte_EXINT(PE8_59_PLL_5, 0xAB);
            ScalerSetByte_EXINT(PE8_5A_PLL_6, 0xAB);

            // ideal 10G
            g_pusDpPhyRx2ClockTarget[0] = 0x4857;

            // peak @5G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1 | _BIT0));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xA2);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x1B);

            // reg_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), _BIT4);

            // reg_cdr_cp
            ScalerSetByte_EXINT(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_UHBR10());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_UHBR10());
            ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_UHBR10());
            /*
            ScalerSetByte_EXINT(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte_EXINT(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            */
            // reg_slope_band = KVCO
            ScalerSetBit_EXINT(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR10() >> 1);
            ScalerSetBit_EXINT(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR10() >> 1);
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR10());
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR10());

            break;

        case _DP_LINK_HBR3_9G:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit_EXINT(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0xD0 (4.5G in 2.5~5G)
            ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(PE7_95_DP_FLD_36, 0xD0);
            ScalerSetByte_EXINT(PE7_96_DP_FLD_37, 0xD0);
            ScalerSetByte_EXINT(PE7_97_DP_FLD_38, 0xD0);
            ScalerSetByte_EXINT(PE7_98_DP_FLD_39, 0xD0);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 500     = 2 *    24     *   4500/16  /  27

            // divid num = 24 = 0x18
            ScalerSetByte_EXINT(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit_EXINT(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // ref_cnt = 500 = 0x1F4
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(PE7_7B_DP_FLD_11, 0xF4);
            ScalerSetByte_EXINT(PE7_7D_DP_FLD_13, 0xF4);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 4500 = 14.318  * 2 * (153 + 4) --> N = 0x099
            ScalerSetBit_EXINT(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PE8_57_PLL_3, 0x99);
            ScalerSetByte_EXINT(PE8_58_PLL_4, 0x99);
            ScalerSetByte_EXINT(PE8_59_PLL_5, 0x99);
            ScalerSetByte_EXINT(PE8_5A_PLL_6, 0x99);

            // ideal 9G
            g_pusDpPhyRx2ClockTarget[0] = 0x411B;

            // peak @5G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xE2);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x13);

            // reg_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), _BIT4);

            // reg_cdr_cp
            ScalerSetByte_EXINT(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_HBR3());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_HBR3());
            ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_HBR3());
            /*
            ScalerSetByte_EXINT(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            */
            // reg_slope_band = KVCO
            ScalerSetBit_EXINT(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR3() >> 1);
            ScalerSetBit_EXINT(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR3() >> 1);
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR3());
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR3());

            break;

        case _DP_LINK_HBR3:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit_EXINT(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0xD0 (4.05G in 2.5~5G)
            ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(PE7_95_DP_FLD_36, 0xD0);
            ScalerSetByte_EXINT(PE7_96_DP_FLD_37, 0xD0);
            ScalerSetByte_EXINT(PE7_97_DP_FLD_38, 0xD0);
            ScalerSetByte_EXINT(PE7_98_DP_FLD_39, 0xD0);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 300     = 2 *    16     *   4050/16  /  27

            // divid num = 16 = 0x10
            ScalerSetByte_EXINT(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit_EXINT(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // ref_cnt = 300 = 0x12C
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(PE7_7B_DP_FLD_11, 0x2C);
            ScalerSetByte_EXINT(PE7_7D_DP_FLD_13, 0x2C);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 4050 = 14.318  * 2 * (137 + 4) --> N = 0x089
            ScalerSetBit_EXINT(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PE8_57_PLL_3, 0x89);
            ScalerSetByte_EXINT(PE8_58_PLL_4, 0x89);
            ScalerSetByte_EXINT(PE8_59_PLL_5, 0x89);
            ScalerSetByte_EXINT(PE8_5A_PLL_6, 0x89);

            // ideal 8.1G
            g_pusDpPhyRx2ClockTarget[0] = 0x3A98;

            // peak @5G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xE2);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x1B);

            // reg_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), _BIT4);

            // reg_cdr_cp
            ScalerSetByte_EXINT(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_HBR3());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_HBR3());
            ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_HBR3());
            /*
            ScalerSetByte_EXINT(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte_EXINT(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            */
            // reg_slope_band = KVCO
            ScalerSetBit_EXINT(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR3() >> 1);
            ScalerSetBit_EXINT(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR3() >> 1);
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR3());
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR3());

            break;

        case _DP_LINK_HBR2:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit_EXINT(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0x70 (2.7G in 2.5~5G)
            ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(PE7_95_DP_FLD_36, 0x70);
            ScalerSetByte_EXINT(PE7_96_DP_FLD_37, 0x70);
            ScalerSetByte_EXINT(PE7_97_DP_FLD_38, 0x70);
            ScalerSetByte_EXINT(PE7_98_DP_FLD_39, 0x70);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 300     = 2 *    24     *   2700/16  /  27

            // divid num = 24 = 0x18
            ScalerSetByte_EXINT(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit_EXINT(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // ref_cnt = 300 = 0x12C
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(PE7_7B_DP_FLD_11, 0x2C);
            ScalerSetByte_EXINT(PE7_7D_DP_FLD_13, 0x2C);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
            ScalerSetBit_EXINT(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PE8_57_PLL_3, 0x5A);
            ScalerSetByte_EXINT(PE8_58_PLL_4, 0x5A);
            ScalerSetByte_EXINT(PE8_59_PLL_5, 0x5A);
            ScalerSetByte_EXINT(PE8_5A_PLL_6, 0x5A);

            // ideal 5.4G
            g_pusDpPhyRx2ClockTarget[0] = 0x2710;

            // peak @2.7G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xC4);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x07);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x0F);

            // reg_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // reg_cdr_cp
            ScalerSetByte_EXINT(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_HBR2());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_HBR2());
            ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_HBR2());
            /*
            ScalerSetByte_EXINT(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte_EXINT(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            */
            // reg_slope_band = KVCO
            ScalerSetBit_EXINT(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR2() >> 1);
            ScalerSetBit_EXINT(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR2() >> 1);
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR2());
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR2());

            break;

        case _DP_LINK_HBR:

            // Sel_DIV = 3'b001 (2.5-5G)
            ScalerSetBit_EXINT(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            // FLD Initial Band = 0x70 (2.7G in 2.5~5G)
            ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(PE7_95_DP_FLD_36, 0x70);
            ScalerSetByte_EXINT(PE7_96_DP_FLD_37, 0x70);
            ScalerSetByte_EXINT(PE7_97_DP_FLD_38, 0x70);
            ScalerSetByte_EXINT(PE7_98_DP_FLD_39, 0x70);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 300     = 2 *    24     *   2700/16  /  27

            // divid num = 24 = 0x18
            ScalerSetByte_EXINT(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit_EXINT(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // ref_cnt = 300 = 0x12C
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(PE7_7B_DP_FLD_11, 0x2C);
            ScalerSetByte_EXINT(PE7_7D_DP_FLD_13, 0x2C);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
            ScalerSetBit_EXINT(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PE8_57_PLL_3, 0x5A);
            ScalerSetByte_EXINT(PE8_58_PLL_4, 0x5A);
            ScalerSetByte_EXINT(PE8_59_PLL_5, 0x5A);
            ScalerSetByte_EXINT(PE8_5A_PLL_6, 0x5A);

            // ideal 2.7G
            g_pusDpPhyRx2ClockTarget[0] = 0x1388;

            // peak @1.35G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0x86);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x0F);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x0F);

            // reg_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // reg_cdr_cp
            ScalerSetByte_EXINT(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_HBR());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_HBR());
            ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_HBR());
            /*
            ScalerSetByte_EXINT(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte_EXINT(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            */
            // reg_slope_band = KVCO
            ScalerSetBit_EXINT(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR() >> 1);
            ScalerSetBit_EXINT(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR() >> 1);
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR());
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR());

            break;

        case _DP_LINK_RBR:
        default:

            // Sel_DIV = 3'b010 (1.25-2.5G)
            ScalerSetBit_EXINT(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // FLD Initial Band = 0x90 (3.24G in 2.5~5G)
            ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(PE7_95_DP_FLD_36, 0x90);
            ScalerSetByte_EXINT(PE7_96_DP_FLD_37, 0x90);
            ScalerSetByte_EXINT(PE7_97_DP_FLD_38, 0x90);
            ScalerSetByte_EXINT(PE7_98_DP_FLD_39, 0x90);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 405     = 2 *    27     *   3240/16  /  27

            // divid num = 27 = 0x1B
            ScalerSetByte_EXINT(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit_EXINT(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));

            // ref_cnt = 405 = 0x195
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(PE7_7B_DP_FLD_11, 0x95);
            ScalerSetByte_EXINT(PE7_7D_DP_FLD_13, 0x95);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 3240 =  14.318  * 2 * (109 + 4) --> N = 0x06D
            ScalerSetBit_EXINT(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PE8_57_PLL_3, 0x6D);
            ScalerSetByte_EXINT(PE8_58_PLL_4, 0x6D);
            ScalerSetByte_EXINT(PE8_59_PLL_5, 0x6D);
            ScalerSetByte_EXINT(PE8_5A_PLL_6, 0x6D);

            // ideal 1.62G
            g_pusDpPhyRx2ClockTarget[0] = 0xBB8;

            // peak @1.35G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0x86);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x0F);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x0F);

            // reg_cco_neq_iptat = 2'b10 --> -25%
            ScalerSetBit_EXINT(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), _BIT5);

            // reg_cdr_cp
            ScalerSetByte_EXINT(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_RBR());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_RBR());
            ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_RBR());
            /*
            ScalerSetByte_EXINT(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte_EXINT(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            */

            // reg_slope_band = KVCO
            ScalerSetBit_EXINT(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_RBR() >> 1);
            ScalerSetBit_EXINT(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_RBR() >> 1);
            ScalerSetBit_EXINT(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_RBR());
            ScalerSetBit_EXINT(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_RBR());
            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);

    enumDpNFCodeRef = enumDpNFCodeRef;

    ScalerDpMacDphyRxLaneSwapSelect_EXINT0(enumInputPort, ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));

    ScalerDpMacDphyRxLaneCountSet_EXINT0(enumInputPort, (BYTE)ScalerDpAuxRxGetLaneCount_EXINT0(enumInputPort));

    ScalerDpMacDphyRxReset_EXINT0(enumInputPort);

    ScalerDpPhyRx2Tp1Measure_EXINT0();
}

//--------------------------------------------------
// Description : Initial Signal check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2Tp1Measure_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);
    BYTE pucOobsOffset[4];

    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
#endif
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)) || (_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON))
        ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE0);
        ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE1);
        ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE2);
        ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE3);
#endif
        switch(ScalerDpAuxRxGetLaneCount_EXINT0(enumInputPort) & 0x1F)
        {
            case _DP_ONE_LANE:

                ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, GET_DP_PHY_RX2_PCB_LANE0_MAPPING());

                break;

            case _DP_TWO_LANE:

                ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, GET_DP_PHY_RX2_PCB_LANE0_MAPPING());
                ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, GET_DP_PHY_RX2_PCB_LANE1_MAPPING());

                break;

            default:
            case _DP_FOUR_LANE:

                ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, GET_DP_PHY_RX2_PCB_LANE0_MAPPING());
                ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, GET_DP_PHY_RX2_PCB_LANE1_MAPPING());
                ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, GET_DP_PHY_RX2_PCB_LANE2_MAPPING());
                ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, GET_DP_PHY_RX2_PCB_LANE3_MAPPING());

                break;
        }
    }


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    ScalerDpPhyRx2SetDFEInitial_EXINT0();


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort))
    {
        case _DP_LINK_UHBR13_5:

            // peak @6.75G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT1 | _BIT0));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xE1);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x01);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x11);

            break;

        case _DP_LINK_UHBR10:

            // peak @5G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1 | _BIT0));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xA2);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x1B);

            break;

        case _DP_LINK_HBR3:

            // peak @5G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xE2);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x1B);

            break;

        case _DP_LINK_HBR2:

            // peak @2.7G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1));
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0xC4);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x07);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x0F);

            break;

        case _DP_LINK_HBR:

            // peak @1.35G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0x86);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x0F);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x0F);

            break;

        case _DP_LINK_RBR:
        default:

            // peak @1.35G
            ScalerSetBit_EXINT(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte_EXINT(PE8_35_LE_MODE_1, 0x86);
            ScalerSetByte_EXINT(PE8_36_LE_MODE_2, 0x0F);
            ScalerSetByte_EXINT(PE8_37_LE_MODE_3, 0x0F);

            break;
    }


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // OOBS Offset Auto Mode
    ScalerSetBit_EXINT(PE3_00_RX_K_OOBS_L0_00, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PE3_08_RX_K_OOBS_L1_00, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PE3_10_RX_K_OOBS_L2_00, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PE3_18_RX_K_OOBS_L3_00, ~_BIT2, 0x00);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0x0F);

    // Double Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ScalerGetByte_EXINT(PE7_86_DP_FLD_22));
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, 0xFF);

    // Reset OOBS Offset Calibration
    ScalerSetBit_EXINT(PE3_00_RX_K_OOBS_L0_00, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PE3_08_RX_K_OOBS_L1_00, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PE3_10_RX_K_OOBS_L2_00, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PE3_18_RX_K_OOBS_L3_00, ~_BIT7, 0x00);

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            break;
        }
    }

    // OOBS Swap Vthpn = 0
    ScalerSetBit_EXINT(PE8_62_LFPS_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Enable OOBS Offset Calibration
    ScalerSetBit_EXINT(PE3_00_RX_K_OOBS_L0_00, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PE3_08_RX_K_OOBS_L1_00, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PE3_10_RX_K_OOBS_L2_00, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PE3_18_RX_K_OOBS_L3_00, ~_BIT7, _BIT7);

    DELAY_XUS_EXINT(50);

    // Read OOBS Offset+
    pucOobsOffset[0] = ScalerGetByte_EXINT(PE3_06_RX_K_OOBS_L0_06);
    pucOobsOffset[1] = ScalerGetByte_EXINT(PE3_0E_RX_K_OOBS_L1_06);
    pucOobsOffset[2] = ScalerGetByte_EXINT(PE3_16_RX_K_OOBS_L2_06);
    pucOobsOffset[3] = ScalerGetByte_EXINT(PE3_1E_RX_K_OOBS_L3_06);

    // OOBS Swap Vthpn = 1
    ScalerSetBit_EXINT(PE8_62_LFPS_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Reset OOBS Offset Calibration
    ScalerSetBit_EXINT(PE3_00_RX_K_OOBS_L0_00, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PE3_08_RX_K_OOBS_L1_00, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PE3_10_RX_K_OOBS_L2_00, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PE3_18_RX_K_OOBS_L3_00, ~_BIT7, 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(PE3_00_RX_K_OOBS_L0_00, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PE3_08_RX_K_OOBS_L1_00, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PE3_10_RX_K_OOBS_L2_00, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PE3_18_RX_K_OOBS_L3_00, ~_BIT7, _BIT7);

    DELAY_XUS_EXINT(50);

    // Reload OOBS Offset = (Offset+)/2 + (Offset-)/2
    ScalerSetByte_EXINT(PE3_03_RX_K_OOBS_L0_03, (pucOobsOffset[0] >> 1) + (ScalerGetByte_EXINT(PE3_06_RX_K_OOBS_L0_06) >> 1));
    ScalerSetByte_EXINT(PE3_0B_RX_K_OOBS_L1_03, (pucOobsOffset[1] >> 1) + (ScalerGetByte_EXINT(PE3_0E_RX_K_OOBS_L1_06) >> 1));
    ScalerSetByte_EXINT(PE3_13_RX_K_OOBS_L2_03, (pucOobsOffset[2] >> 1) + (ScalerGetByte_EXINT(PE3_16_RX_K_OOBS_L2_06) >> 1));
    ScalerSetByte_EXINT(PE3_1B_RX_K_OOBS_L3_03, (pucOobsOffset[3] >> 1) + (ScalerGetByte_EXINT(PE3_1E_RX_K_OOBS_L3_06) >> 1));

    // OOBS Offset Manual Mode
    ScalerSetBit_EXINT(PE3_00_RX_K_OOBS_L0_00, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PE3_08_RX_K_OOBS_L1_00, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PE3_10_RX_K_OOBS_L2_00, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PE3_18_RX_K_OOBS_L3_00, ~_BIT2, _BIT2);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) < _DP_LINK_UHBR10)
    {
        switch(ScalerDpAuxRxGetLaneCount_EXINT0(enumInputPort))
        {
            case _DP_ONE_LANE:

                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX2_D2_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);

                // Measure Count x 4 for Default ref. Counter = 1000
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] = (g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] << 3);

                break;

            case _DP_TWO_LANE:

                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX2_D2_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE1] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX2_D2_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);

                // Measure Count x 4 for Default ref. Counter = 1000
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] = (g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] << 3);
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE1] = (g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE1] << 3);

                break;

            case _DP_FOUR_LANE:
            default:

                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX2_D2_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE1] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX2_D2_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE2] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX2_D2_LANE2, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE3] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX2_D2_LANE3, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);

                // Measure Count x 4 for Default ref. Counter = 1000
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] = (g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] << 3);
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE1] = (g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE1] << 3);
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE2] = (g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE2] << 3);
                g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE3] = (g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE3] << 3);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2Tp1SetPhy4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    /////////////////////////////
    // Frequency & DFE Setting //
    /////////////////////////////

    ScalerDpPhyRx2CDRFLDSetting4Lane_EXINT0(enumDpNFCodeRef);


    ///////////////////////////////
    // Enable FLD and Close loop //
    ///////////////////////////////

    // [7:4] reg_fld_auto_mode = 4'b1111 --> FLD Auto Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0xFF);

    // Disable cp2adp_en
    ScalerSetBit_EXINT(PE7_83_DP_FLD_19, ~_BIT6, 0x00);

    // Reset FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    DELAY_5US_EXINT();

    // Start FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [0,1250] Waiting for FLD
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 250; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PE7_8B_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PE7_8C_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PE7_8D_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PE7_8E_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))))
        {
            break;
        }
    }

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PE7_94_DP_FLD_35) >> 4);
    ScalerSetByte_EXINT(PE7_95_DP_FLD_36, ScalerGetByte_EXINT(PE7_90_DP_FLD_31));
    ScalerSetByte_EXINT(PE7_96_DP_FLD_37, ScalerGetByte_EXINT(PE7_91_DP_FLD_32));
    ScalerSetByte_EXINT(PE7_97_DP_FLD_38, ScalerGetByte_EXINT(PE7_92_DP_FLD_33));
    ScalerSetByte_EXINT(PE7_98_DP_FLD_39, ScalerGetByte_EXINT(PE7_93_DP_FLD_34));

    // Reset FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    DELAY_10US_EXINT();

    // Start FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [0,1250] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PE7_8B_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PE7_8C_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PE7_8D_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PE7_8E_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(100);


    ////////////////
    // Manual FLD //
    ////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PE7_94_DP_FLD_35) >> 4);
    ScalerSetByte_EXINT(PE7_95_DP_FLD_36, ScalerGetByte_EXINT(PE7_90_DP_FLD_31));
    ScalerSetByte_EXINT(PE7_96_DP_FLD_37, ScalerGetByte_EXINT(PE7_91_DP_FLD_32));
    ScalerSetByte_EXINT(PE7_97_DP_FLD_38, ScalerGetByte_EXINT(PE7_92_DP_FLD_33));
    ScalerSetByte_EXINT(PE7_98_DP_FLD_39, ScalerGetByte_EXINT(PE7_93_DP_FLD_34));
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyCtsTp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);
    BYTE ucIcp = 0;
    BYTE ucIcpKp = 0;


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    ScalerDpMacDphyRxLaneSwapSelect_EXINT0(enumInputPort, (g_ucDpPhyRx2CtsCtrl & 0x30) << 2);

    ScalerDpMacDphyRxLaneCountSet_EXINT0(enumInputPort, _DP_FOUR_LANE);

    // CDR_EN,RX_EN Reset
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE0);
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE1);
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE2);
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE3);

    switch(g_ucDpPhyRx2CtsCtrl & 0x30)
    {
        case 0x10:

            // Lane1 Test, Enable RX_EN/CDR_EN for Lane1
            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE1);

            break;

        case 0x20:

            // Lane2 Test, Enable RX_EN/CDR_EN for Lane2
            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE2);

            break;

        case 0x30:

            // Lane3 Test, Enable RX_EN/CDR_EN for Lane3
            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE3);

            break;

        default:
        case 0x00:

            // Lane0 Test, Enable RX_EN/CDR_EN for Lane0
            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE0);

            break;
    }


    /////////////////////////////
    // Frequency & DFE Setting //
    /////////////////////////////

    ScalerDpPhyRx2CDRFLDSetting4Lane_EXINT0(enumDpNFCodeRef);
    ucIcp = ScalerGetByte_EXINT(PE7_85_DP_FLD_21);
    ucIcpKp = ScalerGetByte_EXINT(PE7_C5_FLD_KICO_B05);


    //////////////
    // EQ + DFE //
    //////////////

    ScalerDpPhyRx2SetDFEInitial_EXINT0();

    // [4] tap0_notrans = 1'b0 --> Tap0 is dependent on Every Bits
    ScalerSetBit_EXINT(PE8_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Auto Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0xFF);

    // Reset FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            break;
        }
    }


    ///////////////////////////////
    // Enable FLD and Close loop //
    ///////////////////////////////

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0xC3);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0xC3);
    }

    // Start FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [0,1250] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 250; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PE7_8B_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PE7_8C_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PE7_8D_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PE7_8E_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Disable LE/Vth/Tap0~2 Adaptation
    ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0x00);


    ////////////////
    // Manual FLD //
    ////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PE7_94_DP_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte_EXINT(PE7_94_DP_FLD_35) >> 4);
    ScalerSetByte_EXINT(PE7_95_DP_FLD_36, ScalerGetByte_EXINT(PE7_90_DP_FLD_31));
    ScalerSetByte_EXINT(PE7_96_DP_FLD_37, ScalerGetByte_EXINT(PE7_91_DP_FLD_32));
    ScalerSetByte_EXINT(PE7_97_DP_FLD_38, ScalerGetByte_EXINT(PE7_92_DP_FLD_33));
    ScalerSetByte_EXINT(PE7_98_DP_FLD_39, ScalerGetByte_EXINT(PE7_93_DP_FLD_34));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // Double Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ScalerGetByte_EXINT(PE7_86_DP_FLD_22));
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, 0xFF);

    // Disable cp2adp_en
    ScalerSetBit_EXINT(PE7_83_DP_FLD_19, ~_BIT6, 0x00);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b0000 --> Disable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0x0F);

    // Waiting for CDR lock
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 1; ucLoopIndex++)
    {
        DELAY_5US_EXINT();
    }

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    // Waiting for CDR lock
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 1; ucLoopIndex++)
    {
        DELAY_5US_EXINT();
    }

    // Restore Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ucIcp);
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, ucIcpKp);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, ucIcpKp);

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2Tp2SetPhy_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);
    BYTE ucIcp = 0;
    BYTE ucIcpKp = 0;
    WORD usTargetClock = 0;

#if(_DP_RX_FEC_SUPPORT == _ON)
    BYTE pucTap0[4];
#endif

    ScalerDpPhyRx2Tp1SetPhy4Lane_EXINT0(_DP_NF_REF_XTAL);

    ScalerDpMacDphyRxSetCommaDetect_EXINT0(enumInputPort, _ON);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx2SetDFEInitial_EXINT0();

    // Backup Icp
    ucIcp = ScalerGetByte_EXINT(PE7_85_DP_FLD_21);
    ucIcpKp = ScalerGetByte_EXINT(PE7_C5_FLD_KICO_B05);

    // Double Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ScalerGetByte_EXINT(PE7_86_DP_FLD_22));
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, 0xFF);


    ///////////////////////////////
    // Manual FLD DFE Adaptation //
    ///////////////////////////////

    // [7:4] reg_fld_auto_mode = 4'b1111 --> FLD Auto Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0xFF);

    // Reset FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    DELAY_5US_EXINT();

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0xC3);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(PE8_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Start FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PE7_8B_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PE7_8C_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PE7_8D_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PE7_8E_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(PE8_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Start to Record Max/Min
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Stop To Record Max/Min
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~_BIT0, 0x00);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0x00);

    // Read Back LE Max
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Select to Lane0
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    g_pucDpPhyRx2LE[0] = (ScalerGetByte_EXINT(PE8_F3_COEF_4) & 0x1F);

    // Select to Lane1
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    g_pucDpPhyRx2LE[1] = (ScalerGetByte_EXINT(PE8_F3_COEF_4) & 0x1F);

    // Select to Lane2
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    g_pucDpPhyRx2LE[2] = (ScalerGetByte_EXINT(PE8_F3_COEF_4) & 0x1F);

    // Select to Lane3
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    g_pucDpPhyRx2LE[3] = (ScalerGetByte_EXINT(PE8_F3_COEF_4) & 0x1F);

#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
    {
        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
        {
            // Read Back Tap0
            ScalerSetByte_EXINT(PE8_F0_COEF_1, 0x01);

            // Select to Lane0
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            pucTap0[0] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            // Select to Lane1
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            pucTap0[1] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            // Select to Lane2
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            pucTap0[2] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            // Select to Lane3
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            pucTap0[3] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            if(pucTap0[0] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PE8_A4_L0_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PE8_A4_L0_INIT_2, (pucTap0[0] + 6));
                ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[1] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PE8_B4_L1_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PE8_B4_L1_INIT_2, (pucTap0[1] + 6));
                ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[2] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PE8_C4_L2_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PE8_C4_L2_INIT_2, (pucTap0[2] + 6));
                ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[3] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PE8_D4_L3_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PE8_D4_L3_INIT_2, (pucTap0[3] + 6));
                ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
        }


        /////////////////////
        // Second K Offset //
        /////////////////////

        // Read Back K offset Lane0
        if((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PE8_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PE8_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane1
        if((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PE8_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PE8_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane2
        if((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PE8_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PE8_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane3
        if((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PE8_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PE8_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Reload Servo
        ScalerSetByte_EXINT(PE8_AA_L0_INIT_8, 0x20);
        ScalerSetByte_EXINT(PE8_BA_L1_INIT_8, 0x20);
        ScalerSetByte_EXINT(PE8_CA_L2_INIT_8, 0x20);
        ScalerSetByte_EXINT(PE8_DA_L3_INIT_8, 0x20);

        ScalerSetByte_EXINT(PE8_AA_L0_INIT_8, 0x00);
        ScalerSetByte_EXINT(PE8_BA_L1_INIT_8, 0x00);
        ScalerSetByte_EXINT(PE8_CA_L2_INIT_8, 0x00);
        ScalerSetByte_EXINT(PE8_DA_L3_INIT_8, 0x00);
    }
#endif

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            break;
        }
    }

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0x0F);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // Restore Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ucIcp);
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, ucIcpKp);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, ucIcpKp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);

    usTargetClock = g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0];
    g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE0] = (((usTargetClock >> 2) * 5) >> 1);

    usTargetClock = g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE1];
    g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE1] = (((usTargetClock >> 2) * 5) >> 1);

    usTargetClock = g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE2];
    g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE2] = (((usTargetClock >> 2) * 5) >> 1);

    usTargetClock = g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE3];
    g_pusDpPhyRx2ClockTarget[_DP_PHY_RX2_D2_LANE3] = (((usTargetClock >> 2) * 5) >> 1);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2Tp3SetPhy_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);
    BYTE ucIcp = 0;
    BYTE ucIcpKp = 0;


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // Backup Icp
    ucIcp = ScalerGetByte_EXINT(PE7_85_DP_FLD_21);
    ucIcpKp = ScalerGetByte_EXINT(PE7_C5_FLD_KICO_B05);

    // Double Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ScalerGetByte_EXINT(PE7_86_DP_FLD_22));
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, 0xFF);

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // Restore Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ucIcp);
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, ucIcpKp);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, ucIcpKp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyCtsTp2SetPhy_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);
    BYTE ucIcp = 0;
    BYTE pucTap0[4];

    ScalerDpMacDphyRxSetCommaDetect_EXINT0(enumInputPort, _ON);


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // [4] tap0_notrans = 1'b1 --> Tap0 is dependent on run length
    ScalerSetBit_EXINT(PE8_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    ScalerDpPhyRx2SetDFEInitial_EXINT0();

    // Backup Icp
    ucIcp = ScalerGetByte_EXINT(PE7_85_DP_FLD_21);


    ///////////////////////////////
    // Manual FLD DFE Adaptation //
    ///////////////////////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // Double Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ScalerGetByte_EXINT(PE7_86_DP_FLD_22));

    // Enable cp2adp_en
    ScalerSetBit_EXINT(PE7_83_DP_FLD_19, ~_BIT6, _BIT6);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0x0F);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0xC3);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0xC3);
    }

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    // Delay Time us [0,500] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PE7_8B_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PE7_8C_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PE7_8D_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PE7_8E_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Start to Record Max/Min
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Stop To Record Max/Min
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~_BIT0, 0x00);

    // Read Back LE Max
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Select to Lane0
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    g_pucDpPhyRx2LE[0] = (ScalerGetByte_EXINT(PE8_F3_COEF_4) & 0x1F);

    // Select to Lane1
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    g_pucDpPhyRx2LE[1] = (ScalerGetByte_EXINT(PE8_F3_COEF_4) & 0x1F);

    // Select to Lane2
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    g_pucDpPhyRx2LE[2] = (ScalerGetByte_EXINT(PE8_F3_COEF_4) & 0x1F);

    // Select to Lane3
    ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    g_pucDpPhyRx2LE[3] = (ScalerGetByte_EXINT(PE8_F3_COEF_4) & 0x1F);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0x00);

    // Disable cp2adp_en
    ScalerSetBit_EXINT(PE7_83_DP_FLD_19, ~_BIT6, 0x00);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(PE8_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(PE8_A4_L0_INIT_2, 0x1B);
            ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(PE8_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(PE8_B4_L1_INIT_2, 0x1B);
            ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(PE8_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(PE8_C4_L2_INIT_2, 0x1B);
            ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(PE8_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(PE8_D4_L3_INIT_2, 0x1B);
            ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(PE8_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(PE8_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(PE8_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(PE8_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(PE8_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(PE8_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(PE8_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(PE8_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(PE8_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte_EXINT(PE8_AA_L0_INIT_8, 0x20);
    ScalerSetByte_EXINT(PE8_BA_L1_INIT_8, 0x20);
    ScalerSetByte_EXINT(PE8_CA_L2_INIT_8, 0x20);
    ScalerSetByte_EXINT(PE8_DA_L3_INIT_8, 0x20);

    ScalerSetByte_EXINT(PE8_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_DA_L3_INIT_8, 0x00);

    // Foreground offset calibration reset (low active)
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            break;
        }
    }

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b0000 --> Disable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0x0F);

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 1; ucLoopIndex++)
    {
        DELAY_5US_EXINT();
    }

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 1; ucLoopIndex++)
    {
        DELAY_5US_EXINT();
    }

    // Restore Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ucIcp);

    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 1; ucLoopIndex++)
    {
        DELAY_5US_EXINT();
    }

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Phy Reset in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2ResetCDR_EXINT0(BYTE ucTp2Result)
{
    ucTp2Result = ucTp2Result;

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // DP MAC FIFO Reset
    ScalerDpMacDphyRxChannelFifoReset_EXINT0(ScalerDpPhyRxRxDxMapping_EXINT0(_RX2));

    // Delay Time us [25,x] Waiting for FIFO Reset
    DELAY_25US_EXINT();
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2SetDFEInitial_EXINT0(void)
{
#if(_DP_PHY_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(PE8_ED_LOOP_DIV_2, 0xCA);
    }
    else if(ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TPS3@8B/10B
        ScalerSetByte_EXINT(PE8_ED_LOOP_DIV_2, 0xE2);
    }
    else
#endif
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(PE8_ED_LOOP_DIV_2, 0xCA);
    }

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0x00);


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte_EXINT(PE8_A2_L0_LIMIT_INIT, 0xF8);
    ScalerSetByte_EXINT(PE8_B2_L1_LIMIT_INIT, 0xF8);
    ScalerSetByte_EXINT(PE8_C2_L2_LIMIT_INIT, 0xF8);
    ScalerSetByte_EXINT(PE8_D2_L3_LIMIT_INIT, 0xF8);

    ScalerSetByte_EXINT(PE8_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(PE8_B3_L1_INIT_1, 0xD0);
    ScalerSetByte_EXINT(PE8_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(PE8_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte_EXINT(PE8_A4_L0_INIT_2, 0x14);
    ScalerSetByte_EXINT(PE8_B4_L1_INIT_2, 0x14);
    ScalerSetByte_EXINT(PE8_C4_L2_INIT_2, 0x14);
    ScalerSetByte_EXINT(PE8_D4_L3_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte_EXINT(PE8_A5_L0_INIT_3, 0x03);
    ScalerSetByte_EXINT(PE8_B5_L1_INIT_3, 0x03);
    ScalerSetByte_EXINT(PE8_C5_L2_INIT_3, 0x03);
    ScalerSetByte_EXINT(PE8_D5_L3_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(PE8_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(PE8_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(PE8_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(PE8_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetBit_EXINT(PE8_A9_L0_INIT_7, ~0x7F, 0x1C);
    ScalerSetBit_EXINT(PE8_B9_L1_INIT_7, ~0x7F, 0x1C);
    ScalerSetBit_EXINT(PE8_C9_L2_INIT_7, ~0x7F, 0x1C);
    ScalerSetBit_EXINT(PE8_D9_L3_INIT_7, ~0x7F, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(PE8_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(PE8_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(PE8_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(PE8_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(PE8_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(PE8_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PE8_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}

//--------------------------------------------------
// Description : check DFE Coef in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpPhyRx2DFECheck_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);
    BYTE ucVth = 0;
    BYTE ucTap0 = 0;

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpAuxRxGetLaneCount_EXINT0(enumInputPort))
    {
        case _DP_FOUR_LANE:

            // Read Lane3 DFE
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            // Read Lane2 DFE
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
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

//--------------------------------------------------
// Description : Enable Signal Detection
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2SignalDetection_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // [3:0] Enable Signal Detection
        ScalerSetBit_EXINT(PE8_02_SIGNAL_DETECTION_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        if(ScalerDpAuxRxGetLinkRate_EXINT0(ScalerDpPhyRxRxDxMapping_EXINT0(_RX2)) >= _DP_LINK_HBR2)
        {
            // [4] reg_sel_ls_path_sigdtc = 0 --> Disable Low Speed Path for Signal Detection
            ScalerSetBit_EXINT(PE8_02_SIGNAL_DETECTION_1, ~_BIT4, 0x00);
        }
        else
        {
            // [4] reg_sel_ls_path_sigdtc = 1 --> Enable Low Speed Path for Signal Detection
            ScalerSetBit_EXINT(PE8_02_SIGNAL_DETECTION_1, ~_BIT4, _BIT4);
        }
    }
    else
    {
        // [3:0] Disable Signal Detection
        ScalerSetBit_EXINT(PE8_02_SIGNAL_DETECTION_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}

#endif // End of #if(_D2_DP_SUPPORT == _ON)

