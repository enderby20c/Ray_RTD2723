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
// ID Code      : RL6952_Series_Usb3RetimerDfpPhy0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_USB3RETIMERDFPPHY0__

#include "ScalerFunctionInclude.h"
#include "Usb3RetimerDfpPhy0/ScalerUsb3RetimerDfpPhy0.h"

#if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_FOUR_LANE)
//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Reload Initial Value
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0By2KModeInitialSetting(void)
{
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Rx K OOBS
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0By2DfpRxKOobs(EnumUsbLinkRateKMode enumUsbLinkRateKMode)
{
    enumUsbLinkRateKMode = enumUsbLinkRateKMode;
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Rx K Offset
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0By2DfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode)
{
    enumUsbLinkRateKMode = enumUsbLinkRateKMode;
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0By2Initial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
}
#endif

#if(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_TWO_LANE)
//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Reload Initial Value
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0By1KModeInitialSetting(void)
{
    // [7] reg_pipe_manual_en = 0x01
    ScalerSetBit(PC8_69_SPPHY_21, ~_BIT7, _BIT7);

    // [0] reg_rx_mode_10g_en_l0_10g = 0x01
    ScalerSetBit(PC8_AA_APHY_RX_10G_00, ~_BIT0, _BIT0);

    // [5] reg_rx_sum_ok_sel_l0 = 1'b1 => K SA/SUM Together
    // [2] reg_rx_sum_en_manual_mode_l0 = 1'b1
    ScalerSetBit(PC1_2C_RX_DFE_05, ~_BIT5, _BIT5);
    ScalerSetBit(PC1_3D_RX_LEQ_04, ~_BIT2, _BIT2);

    // [6:5] reg_rx_oobs_deglitch_sel_l0
    ScalerSetBit(PC1_3F_RX_INVOOBS_01, ~(_BIT6 | _BIT5), 0x00);

    // [7] reg_txcmu_sel_ckrd_tx_rx  = 1'b1
    ScalerSetBit(PC1_57_TXCMU_0B, ~_BIT7, _BIT7);

    // [1:0] reg_tx_rxd_tsel_l0 = 2'b01
    ScalerSetBit(PC1_61_TX_LFPS_03, ~(_BIT1 | _BIT0), _BIT0);

    // [5:4] reg_tx_sel_vcm_l0 = 2'b11
    ScalerSetBit(PC1_75_TX_BOOST_01, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [3:0] reg_tx_lfps_l0 = 4'b0000
    ScalerSetBit(PC1_5F_TX_LFPS_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [5] reg_rx_cdr_dec_rst_sel2_l0 = 1'b1
    // [4] reg_rx_cdr_dec_rst_sel_l0 = 1'b0
    ScalerSetBit(PC1_0E_RXCDR_01, ~(_BIT5 | _BIT4), _BIT5);

    // [4] reg_rx_vgaleq_const_en_l0 = 1'b1
    // [2] reg_rx_sel_rxidle_l0 = 1'b0
    ScalerSetBit(PC1_26_RX_SA_EWEH_01, ~_BIT4, _BIT4);
    ScalerSetBit(PC1_26_RX_SA_EWEH_01, ~_BIT2, 0x00);

    // [2:0] reg_txcmu_istank = 3'b100
    // [7] reg_txcmu_pi_bypass = 1'b0
    ScalerSetBit(PC1_54_TXCMU_08, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
    ScalerSetBit(PC1_56_TXCMU_0A, ~_BIT7, 0x00);

    // [3] reg_cdr_reg_sel = 1'b0
    // [4] reg_cdr_en_l0 = 1'b1
    ScalerSetBit(PC8_02_DPHY_02, ~_BIT3, 0x00);
    ScalerSetBit(PC8_02_DPHY_02, ~_BIT4, _BIT4);

    // [7] reg_rx_dfe_sa_offset_edge_en_l0 = 1'b1
    ScalerSetBit(PC1_12_RXCDR_05, ~_BIT7, _BIT7);

    // [0] reg_tx_post_data_en_l0_10g=1'b1
    // [0] reg_tx_pre_data_en_l0_10g=1'b1
    ScalerSetBit(PC8_B2_APHY_TX_10G_06, ~_BIT0, _BIT0);
    ScalerSetBit(PC8_B6_APHY_TX_10G_10, ~_BIT0, _BIT0);

    // [0] reg_tx_main_data_en_l0_5g = 1'b1
    // [0] reg_tx_main_data_en_l0_10g = 1'b1
    ScalerSetBit(PC8_A0_APHY_TX_5G_02, ~_BIT0, _BIT0);
    ScalerSetBit(PC8_AE_APHY_TX_10G_02, ~_BIT0, _BIT0);

    // [0] reg_tx_main_bc_en_l0_5g = 1'b1
    // [0] reg_tx_main_bc_en_l0_10g = 1'b1
    ScalerSetBit(PC8_9C_APHY_TX_5G_00, ~_BIT0, _BIT0);
    ScalerSetBit(PC8_AC_APHY_TX_10G_00, ~_BIT0, _BIT0);

    // [6:1] reg_tx_post_drv_data_l0_10g=0x0E
    // [6:1] reg_tx_pre_drv_data_l0_10g=0x07
    ScalerSetBit(PC8_B2_APHY_TX_10G_06, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (0x0E << 1));
    ScalerSetBit(PC8_B6_APHY_TX_10G_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (0x07 << 1));

    // [6:1] reg_tx_main_drv_bc_l0_10g=0x34
    // [6:1] reg_tx_main_drv_bc_l0_5g=0x34
    ScalerSetBit(PC8_AC_APHY_TX_10G_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (0x34 << 1));
    ScalerSetBit(PC8_9C_APHY_TX_5G_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (0x34 << 1));

    // [6:1] reg_tx_main_drv_data_l0_10g=0x34
    // [6:1] reg_tx_main_drv_data_l0_5g=0x34
    ScalerSetBit(PC8_AE_APHY_TX_10G_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (0x34 << 1));
    ScalerSetBit(PC8_A0_APHY_TX_5G_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (0x34 << 1));

    // [0] reg_dphy_save_power_en = 0x01
    // (Bist mode)[0] reg_dphy_save_power_en = 0x00
    ScalerSetBit(PC8_55_SPPHY_01, ~_BIT0, _BIT0);

    // [3:0] reg_rx_spdsel_l0_5g = 0x02
    ScalerSetBit(PC8_9B_APHY_RX_5G_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    // [3:0] reg_rx_spdsel_l1_10g = 0x03
    ScalerSetBit(PC8_AB_APHY_RX_10G_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [6] reg_clk_inv = 0x01
    // [5] reg_shift_inv = 0x01
    ScalerSetBit(PC8_C7_JCDR_06, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // [7:5] reg_cdr_spdsel_5g = 0x06
    // [7:5] reg_cdr_spdsel_10g = 0x07
    ScalerSetBit(PC8_C1_JCDR_00, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));
    ScalerSetBit(PC8_C2_JCDR_01, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // [4] reg_powerdown_init = 0x00
    ScalerSetBit(PC8_80_SPPHY_44, ~_BIT4, 0x00);

    // [0] reg_deskew_en = 0x00
    ScalerSetBit(PC8_64_SPPHY_16, ~_BIT0, 0x00);

    // [2] reg_low_latency_gen1 = 0x00
    ScalerSetBit(PC8_01_DPHY_01, ~_BIT2, 0x00);

    // [7:6] reg_offset_stable_cnt = 0x00
    ScalerSetBit(PC2_3A_OFFSET_TOP_03, ~(_BIT7 | _BIT6), 0x00);

    // [5:0] reg_offset_timeout[5:0] = 0x3F
    // [3:0] reg_offset_timeout[9:6] = 0x0C
    ScalerSetBit(PC2_3A_OFFSET_TOP_03, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PC2_3B_OFFSET_TOP_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // [6] reg_offset_sa_pc_edge = 1
    ScalerSetBit(PC2_3B_OFFSET_TOP_04, ~_BIT6, _BIT6);

    // [1] reg_offset_sa_pc_data = 1
    ScalerSetBit(PC2_3D_OFFSET_TOP_06, ~_BIT1, _BIT1);

    // [2] reg_offset_sum_pc = 1
    ScalerSetBit(PC2_3C_OFFSET_TOP_05, ~_BIT2, _BIT2);

    // [2] reg_offset_z0_gray_en = 0x00
    ScalerSetBit(PC2_38_OFFSET_TOP_01, ~_BIT2, 0x00);

    // [0] reg_offset_oobs_gray_en = 0
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT0, 0x00);

    // [5] reg_offset_oobs2_gray_en = 0
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT5, 0x00);

    // [7:0] reg_rx_lfps_ext = 0x40
    ScalerSetByte(PC2_AD_SPPHY_56, 0x40);

    // [5] reg_ref_clk_sel_rx = 0x01 => ref Xtal
    ScalerSetBit(PC8_31_FLD_RX_19, ~_BIT5, _BIT5);

    // lock_up/dn_limit = 2* divide_num * (fld_clk/ref_clk) = 2*32*(156.25/14.31818)=698(174=0x2BA)
    // [5:0] reg_vco_coarse_rx = 0x20
    ScalerSetBit(PC8_20_FLD_RX_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);

    // [1:0] reg_fld_mode_rx = 0x00
    ScalerSetBit(PC8_1E_FLD_RX_0, ~(_BIT1 | _BIT0), 0x00);

    // [7:0] reg_divide_num_rx[7:0] = 0x20 (12'd32)
    // [3:0] reg_divide_num_rx[11:8] = 0x00
    ScalerSetByte(PC8_26_FLD_RX_8, 0x020);
    ScalerSetBit(PC8_27_FLD_RX_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7:0] reg_lock_up_limit_rx[7:0 = 0xBA
    // [3:0] reg_lock_up_limit_rx[11:8] = 0x02
    ScalerSetByte(PC8_22_FLD_RX_4, 0xBA);
    ScalerSetBit(PC8_23_FLD_RX_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);

    // [7:0] reg_lock_dn_limit_rx[7:0] = 0xBA
    // [3:0] reg_lock_dn_limit_rx[11:8] = 0x02
    ScalerSetByte(PC8_24_FLD_RX_6, 0xBA);
    ScalerSetBit(PC8_25_FLD_RX_7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);

    // [7] reg_fld_rst_n_rx = 1'b0 --> 1'b1
    ScalerSetBit(PC8_1E_FLD_RX_0, ~_BIT7, 0x00);
    ScalerSetBit(PC8_1E_FLD_RX_0, ~_BIT7, _BIT7);

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 150; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(PC8_36_FLD_RX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(PC8_36_FLD_RX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Reload FLD Auto Mode to Manual Mode
    ScalerSetBit(PC8_20_FLD_RX_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte(PC8_37_FLD_RX_25));
}
//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Rx K OOBS
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0By1DfpRxKOobs(EnumUsbLinkRateKMode enumUsbLinkRateKMode)
{
    BYTE ucOobsL0 = 0;
    BYTE ucOobs2L0 = 0;
    WORD usLoopIndex = 0;

    if(enumUsbLinkRateKMode == _USB_LINK_KMODE_10G)
    {
        // [5:4] reg_pipe_rate_m [1:0] = 2'b01 -> Switch to 10G Mode
        ScalerSetBit(PC8_69_SPPHY_21, ~(_BIT5 | _BIT4), _BIT4);

        // [7] reg_offset_oobs_manual_10g = 0x00
        // [6] reg_offset_oobs2_manual_10g = 0x00
        ScalerSetBit(PC2_49_OFFSETK_08, ~(_BIT7 | _BIT6), 0x00);
    }
    else
    {
        // [5:4] reg_pipe_rate_m [1:0] = 2'b00 -> Switch to 5G Mode
        ScalerSetBit(PC8_69_SPPHY_21, ~(_BIT5 | _BIT4), 0x00);

        // [7] reg_offset_oobs_manual_5g = 0x00
        // [6] reg_offset_oobs2_manual_5g = 0x00
        ScalerSetBit(PC2_48_OFFSETK_07, ~(_BIT7 | _BIT6), 0x00);
    }

    ////////////////
    // Reset oobs///
    ////////////////

    // [2] reg_offset_oobs_en = 0x00 --> 0x01
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT2, 0x00);
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT2, _BIT2);


    // [5:0] reg_debug_sel = 0x00 --> Check oobs ok
    ScalerSetBit(PC2_8C_DEBUG_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Delay Time us [0,200] Waiting for Calibration Done
    for(usLoopIndex = 0; usLoopIndex <= 200; usLoopIndex++)
    {
        // L0 check
        // [3] reg_cdr_reg_sel = 0x00 --> Switch to L0
        ScalerSetBit(PC8_02_DPHY_02, ~_BIT3, 0x00);

        DELAY_10US();

        // L0 oobs ok check
        if(ScalerGetBit(PC2_37_OFFSET_TOP_00, _BIT6) == _BIT6)
        {
            // Get L0 Cal Result out
            ucOobsL0 = ScalerGetBit(PC2_37_OFFSET_TOP_00, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;
        }
    }
    ////////////////
    // Reset oobs2//
    ////////////////

    // [4] reg_offset_oobs2_en = 0x00 --> 0x01
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT4, 0x00);
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT4, _BIT4);

    // [5:0] reg_debug_sel = 0x01 --> Check oobs2 ok
    ScalerSetBit(PC2_8C_DEBUG_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

    // Delay Time us [0,200] Waiting for Calibration Done
    for(usLoopIndex = 0; usLoopIndex <= 200; usLoopIndex++)
    {
        // L0 check
        // [3] reg_cdr_reg_sel = 0x00 --> Switch to L0
        ScalerSetBit(PC8_02_DPHY_02, ~_BIT3, 0x00);

        DELAY_10US();

        // L0 oobs2 ok check
        if(ScalerGetBit(PC2_37_OFFSET_TOP_00, _BIT6) == _BIT6)
        {
            // Get L0 Cal Result out
            ucOobs2L0 = ScalerGetBit(PC2_37_OFFSET_TOP_00, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;
        }
    }

    // [2] reg_offset_oobs_en = 0x00
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT2, 0x00);

    // [4] reg_offset_oobs2_en = 0x00
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT4, 0x00);

    // [0] reg_offset_oobs_ok = 0x01
    ScalerSetBit(PC2_3D_OFFSET_TOP_06, ~_BIT0, (_BIT0));

    // [6] reg_offset_oobs2_ok = 0x01
    ScalerSetBit(PC2_3E_OFFSET_TOP_07, ~_BIT6, (_BIT6));

    if(enumUsbLinkRateKMode == _USB_LINK_KMODE_10G)
    {
        // Reload Calibration Result to Ini
        // reg_offset_oobs_ini_10g_l0
        ScalerSetBit(PC2_4F_OFFSETK_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), ucOobsL0 << 3);

        // reg_offset_oobs2_ini_10g_l0
        ScalerSetBit(PC2_51_OFFSETK_16, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucOobs2L0);

        // [7] reg_offset_oobs_manual_10g = 0x01
        // [6] reg_offset_oobs2_manual_10g = 0x01
        ScalerSetBit(PC2_49_OFFSETK_08, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        // Reload Calibration Result to Ini
        // reg_offset_oobs_ini_5g
        ScalerSetBit(PC2_4E_OFFSETK_13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), ucOobsL0 << 3);

        // reg_offset_oobs2_ini_5g
        ScalerSetBit(PC2_50_OFFSETK_15, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucOobs2L0);

        // [7] reg_offset_oobs_manual_5g = 0x01
        // [6] reg_offset_oobs2_manual_5g = 0x01
        ScalerSetBit(PC2_48_OFFSETK_07, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
}
//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Rx K Offset
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0By1DfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode)
{
    BYTE ucDataL0 = 0;
    BYTE ucEdgeL0 = 0;
    // BYTE ucSumL0 = 0;
    BYTE ucOffsetZ0L0 = 0;
    WORD usLoopIndex = 0;

    // dh,dl not use,don't need auto K
    if(enumUsbLinkRateKMode == _USB_LINK_KMODE_10G)
    {
        // [5:4] reg_pipe_rate_m [1:0] = 2'b01 -> Switch to 10G Mode
        ScalerSetBit(PC8_69_SPPHY_21, ~(_BIT5 | _BIT4), (_BIT4));

        // Lane0
        // [7] reg_offset_sa_manual_edge_10g = 0x00
        ScalerSetBit(PC2_45_OFFSETK_04, ~_BIT7, 0x00);

        // [1] reg_offset_sa_manual_data_10g = 0x00
        ScalerSetBit(PC2_45_OFFSETK_04, ~_BIT1, 0x00);

        // [1] reg_offset_sum_manual_10g = 0x00
        ScalerSetBit(PC2_4F_OFFSETK_14, ~_BIT1, _BIT1);

        // [6] reg_offset_z0_manual_10g = 0x00
        ScalerSetBit(PC2_01_LFPS_01, ~_BIT6, 0x00);
    }
    else
    {
        // [5:4] reg_pipe_rate_m [1:0] = 2'b00 -> Switch to 5G Mode
        ScalerSetBit(PC8_69_SPPHY_21, ~(_BIT5 | _BIT4), 0x00);

        // Lane0
        // [7] reg_offset_sa_manual_edge_5g = 0x00
        ScalerSetBit(PC2_44_OFFSETK_03, ~_BIT7, 0x00);

        // [1] reg_offset_sa_manual_data_5g = 0x00
        ScalerSetBit(PC2_44_OFFSETK_03, ~_BIT1, 0x00);

        // [1] reg_offset_sum_manual_5g = 0x00
        ScalerSetBit(PC2_4E_OFFSETK_13, ~_BIT1, _BIT1);

        // [6] reg_offset_z0_manual_5g = 0x00
        ScalerSetBit(PC2_00_LFPS_00, ~_BIT6, 0x00);
    }


    //////////////////
    // Reset Sa Data//
    //////////////////

    // [6] reg_offset_sa_en_data = 0x00 --> 0x01
    ScalerSetBit(PC2_3D_OFFSET_TOP_06, ~_BIT6, 0x00);
    ScalerSetBit(PC2_3D_OFFSET_TOP_06, ~_BIT6, (_BIT6));

    // [5:0] reg_debug_sel = 0x04 --> Check sa data ok
    ScalerSetBit(PC2_8C_DEBUG_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);

    // Delay Time us [0,200] Waiting for Calibration Done
    for(usLoopIndex = 0; usLoopIndex <= 200; usLoopIndex++)
    {
        // L0 check
        // [3] reg_cdr_reg_sel = 0x00 --> Switch to L0
        ScalerSetBit(PC8_02_DPHY_02, ~_BIT3, 0x00);

        DELAY_10US();

        // L0 ok check
        if(ScalerGetBit(PC2_37_OFFSET_TOP_00, _BIT6) == _BIT6)
        {
            // Get L0 Cal Result out
            ucDataL0 = ScalerGetBit(PC2_37_OFFSET_TOP_00, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;
        }
    }

    //////////////////
    // Reset Sa Edge//
    //////////////////

    // [7] reg_offset_sa_en_edge = 0x00 --> 0x01
    ScalerSetBit(PC2_3B_OFFSET_TOP_04, ~_BIT7, 0x00);
    ScalerSetBit(PC2_3B_OFFSET_TOP_04, ~_BIT7, _BIT7);

    // [5:0] reg_debug_sel = 0x03 --> Check sa edge ok
    ScalerSetBit(PC2_8C_DEBUG_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x03);

    // Delay Time us [0,200] Waiting for Calibration Done
    for(usLoopIndex = 0; usLoopIndex <= 200; usLoopIndex++)
    {
        // L0 check
        // [3] reg_cdr_reg_sel = 0x00 --> Switch to L0
        ScalerSetBit(PC8_02_DPHY_02, ~_BIT3, 0x00);

        DELAY_10US();

        // L0 ok check
        if(ScalerGetBit(PC2_37_OFFSET_TOP_00, _BIT6) == _BIT6)
        {
            // Get L0 Cal Result out
            ucEdgeL0 = ScalerGetBit(PC2_37_OFFSET_TOP_00, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;
        }
    }


    //////////////////
    // Reset summer//
    //////////////////

    // [3] reg_offset_sum_en = 0x00
    ScalerSetBit(PC2_3C_OFFSET_TOP_05, ~_BIT3, 0x00);

    //////////////////
    // Reset OffsetZ0//
    //////////////////

    // [2] reg_offset_z0_en = 0x00 --> 0x01
    ScalerSetBit(PC2_04_LFPS_04, ~_BIT2, 0x00);
    ScalerSetBit(PC2_04_LFPS_04, ~_BIT2, _BIT2);

    // [5:0] reg_debug_sel = 0x08 --> Check offsetZ0 ok
    ScalerSetBit(PC2_8C_DEBUG_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x08);

    // Delay Time us [0,200] Waiting for Calibration Done
    for(usLoopIndex = 0; usLoopIndex <= 2000; usLoopIndex++)
    {
        // L0 check
        // [3] reg_cdr_reg_sel = 0x00 --> Switch to L0
        ScalerSetBit(PC8_02_DPHY_02, ~_BIT3, 0x00);

        DELAY_10US();

        // L0 ok check
        if(ScalerGetBit(PC2_37_OFFSET_TOP_00, _BIT3) == _BIT3)
        {
            // [5:0] reg_debug_sel = 0x07 --> Get Cal offsetZ0 value
            ScalerSetBit(PC2_8C_DEBUG_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

            // Get L0 Cal Result out
            ucOffsetZ0L0 = ScalerGetByte(PC2_37_OFFSET_TOP_00);

            break;
        }
    }

    // [6] reg_offset_sa_en_data = 0x00
    ScalerSetBit(PC2_3D_OFFSET_TOP_06, ~_BIT6, 0x00);

    // [7] reg_offset_sa_en_edge = 0x00
    ScalerSetBit(PC2_3B_OFFSET_TOP_04, ~_BIT7, 0x00);

    // [7] reg_offset_sa_en_dh = 0x00
    ScalerSetBit(PC2_3C_OFFSET_TOP_05, ~_BIT7, 0x00);

    // [5] reg_offset_sa_en_dl = 0x00
    ScalerSetBit(PC2_3D_OFFSET_TOP_06, ~_BIT5, 0x00);

    // [3] reg_offset_sum_en = 0x00
    ScalerSetBit(PC2_3C_OFFSET_TOP_05, ~_BIT3, 0x00);

    // [2] reg_offset_z0_en = 0x00
    ScalerSetBit(PC2_04_LFPS_04, ~_BIT2, 0x00);

    // [1] reg_offset_sa_ok_data = 0x01
    ScalerSetBit(PC2_3C_OFFSET_TOP_05, ~_BIT1, _BIT1);

    // [4] reg_offset_sa_ok_edge = 0x01
    ScalerSetBit(PC2_3B_OFFSET_TOP_04, ~_BIT4, _BIT4);

    // [7] reg_offset_sa_ok_dh = 0x01
    ScalerSetBit(PC2_3D_OFFSET_TOP_06, ~_BIT7, _BIT7);

    // [2] reg_offset_sa_ok_dl = 0x01
    ScalerSetBit(PC2_3D_OFFSET_TOP_06, ~_BIT2, _BIT2);

    // [4] reg_offset_sum_ok = 0x01
    ScalerSetBit(PC2_3C_OFFSET_TOP_05, ~_BIT4, _BIT4);

    // [0] reg_offset_z0_ok = 0x01
    ScalerSetBit(PC2_39_OFFSET_TOP_02, ~_BIT0, _BIT0);

    if(enumUsbLinkRateKMode == _USB_LINK_KMODE_10G)
    {
        // Reload Calibration Result to Ini
        // reg_offset_sa_ini_data_10g
        ScalerSetBit(PC2_49_OFFSETK_08, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucDataL0);

        // reg_offset_sa_ini_edge_10g
        ScalerSetBit(PC2_45_OFFSETK_04, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ucEdgeL0 << 2);

        // reg_offset_sum_data_ini_10g
        ScalerSetBit(PC2_53_OFFSETK_18, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // reg_offset_z0_ini_10g1
        ScalerSetByte(PC2_43_OFFSETK_02, ucOffsetZ0L0);

        // [1] reg_offset_sa_manual_data_10g = 0x01
        ScalerSetBit(PC2_45_OFFSETK_04, ~_BIT1, _BIT1);

        // [7] reg_offset_sa_manual_edge_10g = 0x01
        ScalerSetBit(PC2_45_OFFSETK_04, ~_BIT7, _BIT7);

        // [0] reg_offset_sa_manual_dh_10g = 0x01
        ScalerSetBit(PC2_45_OFFSETK_04, ~_BIT0, _BIT0);

        // [5] reg_offset_sa_manual_dl_10g = 0x01
        ScalerSetBit(PC2_49_OFFSETK_08, ~_BIT5, _BIT5);

        // [1] reg_offset_sum_manual_10g = 0x01
        ScalerSetBit(PC2_4F_OFFSETK_14, ~_BIT1, _BIT1);

        // [6] reg_offset_z0_manual_10g = 0x01
        ScalerSetBit(PC2_01_LFPS_01, ~_BIT6, _BIT6);
    }
    else
    {
        // Reload Calibration Result to Ini
        // reg_offset_sa_ini_data_5g
        ScalerSetBit(PC2_48_OFFSETK_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucDataL0);

        // reg_offset_sa_ini_edge_5g
        ScalerSetBit(PC2_44_OFFSETK_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ucEdgeL0 << 2);

        // reg_offset_sum_data_ini_5g
        ScalerSetBit(PC2_52_OFFSETK_17, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // reg_offset_z0_ini_5g
        ScalerSetByte(PC2_42_OFFSETK_01, ucOffsetZ0L0);

        // [1] reg_offset_sa_manual_data_5g = 0x01
        ScalerSetBit(PC2_44_OFFSETK_03, ~_BIT1, _BIT1);

        // [7] reg_offset_sa_manual_edge_5g = 0x01
        ScalerSetBit(PC2_44_OFFSETK_03, ~_BIT7, _BIT7);

        // [0] reg_offset_sa_manual_dh_5g = 0x01
        ScalerSetBit(PC2_44_OFFSETK_03, ~_BIT0, _BIT0);

        // [5] reg_offset_sa_manual_dl_5g = 0x01
        ScalerSetBit(PC2_48_OFFSETK_07, ~_BIT5, _BIT5);

        // [1] reg_offset_sum_manual_5g = 0x01
        ScalerSetBit(PC2_4E_OFFSETK_13, ~_BIT1, _BIT1);

        // [6] reg_offset_z0_manual_5g = 0x01
        ScalerSetBit(PC2_00_LFPS_00, ~_BIT6, _BIT6);
    }
}
//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0By1Initial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // [7] reg_rx_pow_ctle_sel_l0 = 1'b0
    ScalerSetBit(PC1_2C_RX_DFE_05, ~_BIT7, 0x00);

    // [2] reg_rx_en_self_l0 = 1'b0
    ScalerSetBit(PC1_14_RXCDR_07, ~_BIT2, 0x00);

    // [7] reg_rx_forcerun_l0 = 1'b1
    ScalerSetBit(PC1_15_RXEYE_00, ~_BIT7, _BIT7);

    // [1] reg_rxcmu_en_manual_en = 1'b0
    // [0] reg_rxcmu_en_manual = 1'b0
    ScalerSetBit(PC1_05_RXCMU_05, ~(_BIT1 | _BIT0), 0x00);

    // [5] reg_txcmu_en_manual_en = 1'b0
    // [4] reg_txcmu_en_manual = 1'b0
    ScalerSetBit(PC1_51_TXCMU_05, ~(_BIT5 | _BIT4), 0x00);

#if(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_UNFLIP)
    // choose JFM From wihich lane
    // [3] reg_cdr_reg_sel = 0x00
    ScalerSetBit(PC8_02_DPHY_02, ~_BIT3, 0x00);

    // [0] reg_lane_debug_sel = 1'b0 => Lane0/1
    ScalerSetBit(PC8_7B_SPPHY_39, ~_BIT0, 0x00);

    // [0] reg_lane_config_init = 1'b0 => Initial Lane config to Lane0
    ScalerSetBit(PC8_81_SPPHY_45, ~_BIT0, 0x00);

    // [0] rx_jfm_cclk_sel = 0x00
    ScalerSetBit(PC8_8A_APHY_SIG_02, ~_BIT0, 0x00);
#else
    // [3] reg_cdr_reg_sel = 0x01
    ScalerSetBit(PC8_02_DPHY_02, ~_BIT3, _BIT3);

    // [0] reg_lane_debug_sel = 1'b1 => Lane2/3
    ScalerSetBit(PC8_7B_SPPHY_39, ~_BIT0, _BIT0);

    // [0] reg_lane_config_init = 1'b1 => Initial Lane config to Lane2
    ScalerSetBit(PC8_81_SPPHY_45, ~_BIT0, _BIT0);

    // [0] rx_jfm_cclk_sel = 0x01
    ScalerSetBit(PC8_8A_APHY_SIG_02, ~_BIT0, _BIT0);
#endif

    // [3:0] reg_rx_oobs_z0_l0=0x09
    ScalerSetBit(PC1_1E_RX_PI_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x09);

    // [2:0] reg_rx_pi_trisel_l0[2:0] = 3'b111
    ScalerSetBit(PC1_42_RX_PI_JFM_02, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [3] reg_tx_sel_ckrd_duty_l0 = 1'b1
    ScalerSetBit(PC1_60_TX_LFPS_02, ~_BIT3, _BIT3);

    // [3:0] reg_tx_txterm_l0 = 0x00
    ScalerSetBit(PC1_63_TX_LFPS_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [0] reg_tx_reserved_l0<16> = 1'b1
    ScalerSetBit(PC1_71_TX_RESERVED_01, ~_BIT0, _BIT0);

    // [3] reg_jfm_en_mode = 0x01
    ScalerSetBit(PC8_C7_JCDR_06, ~_BIT1, _BIT1);

    // [5:0] reg_kp_5g = 0x04
    // [5:0] reg_kp_10g = 0x03
    ScalerSetBit(PC8_C8_JCDR_07, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
    ScalerSetBit(PC8_C9_JCDR_08, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x03);

    // [5:0] reg_ki_5g = 0x01
    // [5:0] reg_ki_10g = 0x01
    ScalerSetBit(PC8_CA_JCDR_09, ~(_BIT2 | _BIT1 | _BIT0), 0x01);
    ScalerSetBit(PC8_CB_JCDR_10, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

    // [4:0] reg_rxcmu_cp_i_sel = 0x05
    // [2:0] reg_rxcmu_istank = 0x04
    // [7:4] reg_rxcmu_lpf_rs = 0x02
    // [6:4] reg_rxcmu_fld_vref_sel = 0x04
    ScalerSetBit(PC1_04_RXCMU_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(PC1_08_RXCMU_08, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
    ScalerSetBit(PC1_08_RXCMU_08, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit(PC1_06_RXCMU_06, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // [4:0] reg_txcmu_cp_i_sel = 0x07
    // [2:0] reg_txcmu_istank = 0x04
    // [3:0] reg_txcmu_lpf_rs = 0x01
    // [2:0] reg_txcmu_fld_vref_sel = 0x04 ->5/9LV
    ScalerSetBit(PC1_50_TXCMU_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PC1_54_TXCMU_08, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
    ScalerSetBit(PC1_55_TXCMU_09, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PC1_76_TX_BOOST_02, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // [0] reg_dphy_save_power_en = 0x01
    // (Bist mode)[0] reg_dphy_save_power_en = 0x00
    ScalerSetBit(PC8_55_SPPHY_01, ~_BIT0, _BIT0);

    // If let Tx ref xtal=14.318 for Debug->reg_txcmu_ck_fref_in_txref_rxref_sel=0
    // [5] reg_txcmu_ck_fref_in_txref_rxref_sel=1
    ScalerSetBit(PC1_4E_TXCMU_02, ~_BIT5, _BIT5);

    // [TX] fld_clk_sel=2'b10->/16->fld_clk = 2.5GHz/16 = 156.25MHz
    // [RX] fld_clk_sel=2'b11->/32->fld_clk = 5GHz/32 =156.25MHz
    // [7:6] reg_txcmu_fld_clk_sel=10
    // [3:2] reg_rxcmu_fld_clk_sel=11
    ScalerSetBit(PC1_51_TXCMU_05, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(PC1_05_RXCMU_05, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [5] reg_ref_clk_sel_rx = 0x01 => ref Xtal
    // [5] reg_ref_clk_sel_tx = 0x00 => ref Xtal
    ScalerSetBit(PC8_31_FLD_RX_19, ~_BIT5, _BIT5);
    ScalerSetBit(PC8_4C_FLD_TX_19, ~_BIT5, 0x00);

    // lock_up/dn_limit = 2* divide_num * (fld_clk/ref_clk) = 2*32*(156.25/14.31818)=698(174=0x2BA)
    // [5:0] reg_vco_coarse_rx,0x20
    ScalerSetBit(PC8_20_FLD_RX_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);

    // [1:0] reg_fld_mode_rx,0x00
    ScalerSetBit(PC8_1E_FLD_RX_0, ~(_BIT1 | _BIT0), 0x00);

    // [7:0] reg_divide_num_rx[7:0],0x20 (12'd32)
    // [3:0] reg_divide_num_rx[11:8],0x00
    ScalerSetByte(PC8_26_FLD_RX_8, 0x020);
    ScalerSetBit(PC8_27_FLD_RX_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7:0] reg_lock_up_limit_rx[7:0],0xBA
    // [3:0] reg_lock_up_limit_rx[11:8],0x02
    ScalerSetByte(PC8_22_FLD_RX_4, 0xBA);
    ScalerSetBit(PC8_23_FLD_RX_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);

    // [7:0] reg_lock_dn_limit_rx[7:0],0xBA
    // [3:0] reg_lock_dn_limit_rx[11:8],0x02
    ScalerSetByte(PC8_24_FLD_RX_6, 0xBA);
    ScalerSetBit(PC8_25_FLD_RX_7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);

    // lock_up/dn_limit = 2* divide_num * (fld_clk/ref_clk) = 2*64*(156.25/27)=741(92=0x2E4)
    // [5:0] reg_vco_coarse_tx,0x20
    ScalerSetBit(PC8_3B_FLD_TX_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);

    // [1:0] reg_fld_mode_tx,0x00
    ScalerSetBit(PC8_39_FLD_TX_0, ~(_BIT1 | _BIT0), 0x00);

    // [7:0] reg_divide_num_tx[7:0] = 0x40 (12'd64)
    // [3:0] reg_divide_num_tx[11:8]=0x00
    ScalerSetByte(PC8_41_FLD_TX_8, 0x40);
    ScalerSetBit(PC8_42_FLD_TX_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7:0] reg_lock_up_limit_tx[7:0],0xE4
    // [3:0] reg_lock_up_limit_tx[11:8],0x02
    ScalerSetByte(PC8_3D_FLD_TX_4, 0xE4);
    ScalerSetBit(PC8_3E_FLD_TX_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);

    // [7:0] reg_lock_dn_limit_tx[7:0],0xE4
    // [3:0] reg_lock_dn_limit_tx[11:8],0x02
    ScalerSetByte(PC8_3F_FLD_TX_6, 0xE4);
    ScalerSetBit(PC8_40_FLD_TX_7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);


    // [7:0] reg_p2p0_delay_0,1[7:0] = 0xF4
    // [7:0] reg_p2p0_delay_0,1[15:8] = 0x01
    ScalerSetByte(PC8_5C_SPPHY_08, 0xF4);
    ScalerSetByte(PC8_5D_SPPHY_09, 0x01);
    ScalerSetByte(PC8_5E_SPPHY_10, 0xF4);
    ScalerSetByte(PC8_5F_SPPHY_11, 0x01);

    // AutoMode->reg_rx_leq_manual=1,reg_rx_leq_sel=1,reg_eq_selreg=0;
    // ManuMode->reg_rx_leq_manual=0,reg_rx_leq_sel=0,reg_eq_selreg=1;
    // [1]reg_rx_leq_manual = 1(Default=0)
    // [0]reg_rx_leq_sel = 1(Default=0)
    // ScalerSetBit(PC8_68_SPPHY_20, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [5] reg_eq_selreg_5g_l0,1 = 0x01
    // [6:0] reg_filter_out_5g_l0,1 = 0x00
    ScalerSetBit(PC2_07_EQ_02, ~_BIT5, _BIT5);
    ScalerSetBit(PC2_0B_EQ_06, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [5] reg_eq_selreg_10g_l0,1 = 0x01
    // [6:0] reg_filter_out_10g_l0,1 = 0x00
    ScalerSetBit(PC2_08_EQ_03, ~_BIT5, _BIT5);
    ScalerSetBit(PC2_0C_EQ_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [9:0] reg_lfps_lperiod_5g = 0x27 => 8ns / 0.2ns - 1 = 39 (0x27)
    ScalerSetBit(PC2_89_LFPS_PERIOD_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(PC2_02_LFPS_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

    // [9:0] reg_lfps_hperiod_5g = 0x153 => 68ns / 0.2ns - 1 = 339 (0x153)
    ScalerSetBit(PC2_89_LFPS_PERIOD_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(PC2_00_LFPS_00, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1 | _BIT0));

    // [9:0] reg_lfps_lperiod_10g = 0x4F => 8ns / 0.1ns - 1 = 79 (0x4F)
    ScalerSetBit(PC2_8A_LFPS_PERIOD_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    ScalerSetBit(PC2_03_LFPS_03, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [9:0] reg_lfps_hperiod_10g = 0x2A7 => 68ns / 0.1ns - 1 = 679 (0x2A7)
    ScalerSetBit(PC2_8A_LFPS_PERIOD_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(PC2_01_LFPS_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

    // [2] reg_low_latency_gen1 = 0x01
    ScalerSetBit(PC8_01_DPHY_01, ~_BIT2, _BIT2);

    // [3] reg_ssc_bypass_pi_rx = 0x00
    // [1] reg_ssc_en_rx = 0x00
    ScalerSetBit(PC8_06_SSC_RX_00, ~_BIT3, 0x00);
    ScalerSetBit(PC8_06_SSC_RX_00, ~_BIT1, 0x00);

    // [3] reg_ssc_bypass_pi_tx = 0x00
    // [2] Enable Center SSC = 0 ->DownSteam
    // [1] reg_ssc_en_tx = 0x00 => SSC OFF
    ScalerSetBit(PC8_10_SSC_TX_00, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

    // VCO Freq Fixed=10G
    // TX NFcode =  VCOFreq/4/ref_clk-2
    // ref_clk = 125MHz -> 10G/4/125-2=18=0x12,fcode=0
    // ref_clk = 14.318MHz -> 10G/4/14.318-2=172.6054,ncode=172=0xAC, fcode= 0.6054*2^13=4959=0x135F
    // [1]reg_ssc_n_code_ini_tx[8],0x00
    // [7:0]reg_ssc_n_code_ini_tx,0x12
    // [0]reg_ssc_n_code_tx[8],0x00
    // [7:0]reg_ssc_n_code_tx,0x12
    // [7:0]reg_ssc_f_code_tx[7:0],0x00
    // [4:0]reg_ssc_f_code_tx[12:8],0x00

    ScalerSetBit(PC8_13_SSC_TX_03, ~_BIT1, 0x00);
    ScalerSetByte(PC8_11_SSC_TX_01, 0x12);
    ScalerSetBit(PC8_13_SSC_TX_03, ~_BIT0, 0x00);
    ScalerSetByte(PC8_12_SSC_TX_02, 0x12);
    ScalerSetByte(PC8_14_SSC_TX_04, 0x00);
    ScalerSetBit(PC8_15_SSC_TX_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // RX NFcode =  VCOFreq/2/ref_clk-2
    // ref_clk = 14.318MHz -> 10G/2/14.318-2=347.20639,ncode=347=0x15B, fcode= 0.20639*2^13=1727=0x6BF
    // [0]reg_ssc_n_code_rx[8],0x01
    // [7:0]reg_ssc_n_code_rx,0x5B
    // [7:0]reg_ssc_f_code_rx[7:0],0xBF
    // [4:0]reg_ssc_f_code_rx[12:8],0x06
    ScalerSetBit(PC8_09_SSC_RX_03, ~_BIT0, _BIT0);
    ScalerSetByte(PC8_08_SSC_RX_02, 0x5B);
    ScalerSetByte(PC8_0A_SSC_RX_04, 0xBF);
    ScalerSetBit(PC8_0B_SSC_RX_05, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);


    // Set SSCFreq=31.5[KHz],RX Doesn't need SSC on
    // Set SSC(ppm)=4500
    // TBase=Ref_clk[MHz] *1000 / SSCFreq[KHz]
    // NFCode_SSC=(1-SSC[ppm]/10^6)*VCOFreq[MHz]/4/Ref_clk-2
    // reg_ssc_step_in_tx have 13bit -> F_code_bit_width=13
    // Step_IN=64*(NFcode-NFCode_SSC)*2^F_code_bit_width/(TBase/2)

    // [7:0] reg_ssc_tbase_in_tx[7:0]=0x80
    // [3:0] reg_ssc_tbase_in_tx[13:8]=0x0F
    ScalerSetByte(PC8_19_SSC_TX_09, 0x80);
    ScalerSetBit(PC8_18_SSC_TX_08, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:0] reg_ssc_step_in_tx[7:0]=0x18
    // [4:0] reg_ssc_step_in_tx[12:8]=0x00
    ScalerSetByte(PC8_17_SSC_TX_07, 0x18);
    ScalerSetBit(PC8_16_SSC_TX_06, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7] reg_tx_beacon_sync=1
    ScalerSetBit(PC1_59_TX_TERM_00, ~_BIT7, _BIT7);

    // [7] reg_fld_rst_n_rx=1
    ScalerSetBit(PC8_1E_FLD_RX_0, ~_BIT7, 0x00);
    ScalerSetBit(PC8_1E_FLD_RX_0, ~_BIT7, _BIT7);

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 40; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(PC8_36_FLD_RX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(PC8_36_FLD_RX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Reload FLD Auto Mode to Manual Mode
    ScalerSetByte(PC8_20_FLD_RX_2, ScalerGetByte(PC8_37_FLD_RX_25));

    // [7] reg_fld_rst_n_tx=1
    ScalerSetBit(PC8_39_FLD_TX_0, ~_BIT7, 0x00);
    ScalerSetBit(PC8_39_FLD_TX_0, ~_BIT7, _BIT7);

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 40; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(PC8_51_FLD_TX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(PC8_51_FLD_TX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Reload FLD Auto Mode to Manual Mode
    ScalerSetByte(PC8_3B_FLD_TX_2, ScalerGetByte(PC8_52_FLD_TX_25));

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    // BLR TxBist Releated FW Solution
    // Set DFP DFP Rx LFPS Extend For Reset to MAC 255us
    ScalerSetByte(PC2_AD_SPPHY_56, 0xFF);
#endif // End of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
}
#endif

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Reload Initial Value
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0KModeInitialSetting(void)
{
#if(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_FOUR_LANE)

    ScalerUsb3RetimerDfpPhy0By2KModeInitialSetting();

#elif(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_TWO_LANE)

    ScalerUsb3RetimerDfpPhy0By1KModeInitialSetting();

#endif
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer UFP PHY K mode End Setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0KModeEndSetting(void)
{
    // [7] reg_pipe_manual_en = 0x00
    ScalerSetBit(PC8_69_SPPHY_21, ~(_BIT7), 0x00);

#if(_U3_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON)
    ScalerUsb3RetimerDfpPhy0PhyDisable();
#endif
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer UFP PHY Rx K OOBS
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0DfpRxKOobs(EnumUsbLinkRateKMode enumUsbLinkRateKMode)
{
#if(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_FOUR_LANE)

    ScalerUsb3RetimerDfpPhy0By2DfpRxKOobs(enumUsbLinkRateKMode);

#elif(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_TWO_LANE)

    ScalerUsb3RetimerDfpPhy0By1DfpRxKOobs(enumUsbLinkRateKMode);

#endif
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer UFP PHY Rx K Offset
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0DfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode)
{
#if(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_FOUR_LANE)

    ScalerUsb3RetimerDfpPhy0By2DfpRxKOffset(enumUsbLinkRateKMode);

#elif(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_TWO_LANE)

    ScalerUsb3RetimerDfpPhy0By1DfpRxKOffset(enumUsbLinkRateKMode);

#endif
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0Initial(EnumTypeCPcbPort enumTypeCPcbPort)
{
#if(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_FOUR_LANE)

    ScalerUsb3RetimerDfpPhy0By2Initial(enumTypeCPcbPort);

#elif(_HW_USB3_REPEATER_DFP_PHY_LANE_NUM_SUPPORT == _DFP_TWO_LANE)

    ScalerUsb3RetimerDfpPhy0By1Initial(enumTypeCPcbPort);

#endif
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0Disable(void)
{
    ScalerUsb3RetimerDfpPhy0PhyDisable();
    ScalerUsb3RetimerDfpPhy0IrqDisable();
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0PhyDisable(void)
{
    // [7] reg_rx_pow_ctle_sel_l0 = 1'b1
    ScalerSetBit(PC1_2C_RX_DFE_05, ~_BIT7, _BIT7);

    // [2] reg_rx_en_self_l0 = 1'b1
    ScalerSetBit(PC1_14_RXCDR_07, ~_BIT2, _BIT2);

    // [7] reg_rx_forcerun_l0 = 1'b0
    ScalerSetBit(PC1_15_RXEYE_00, ~_BIT7, 0x00);

    // [1] reg_rxcmu_en_manual_en = 1'b1
    // [0] reg_rxcmu_en_manual = 1'b0
    ScalerSetBit(PC1_05_RXCMU_05, ~(_BIT1 | _BIT0), _BIT1);

    // [5] reg_txcmu_en_manual_en = 1'b1
    // [4] reg_txcmu_en_manual = 1'b0
    ScalerSetBit(PC1_51_TXCMU_05, ~(_BIT5 | _BIT4), _BIT5);
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerDfpPhy0IrqDisable(void)
{
}
#endif // End of #if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)