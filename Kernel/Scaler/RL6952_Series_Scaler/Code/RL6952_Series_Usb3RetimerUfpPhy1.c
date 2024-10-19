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
// ID Code      : RL6952_Series_Usb3RetimerUfpPhy1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_USB3RETIMERUFPPHY1__

#include "ScalerFunctionInclude.h"
#include "Usb3RetimerUfpPhy1/ScalerUsb3RetimerUfpPhy1.h"

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bUsb3RetimerUfpPhy1KmodeFinish = _FALSE;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Reload Initial Value
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1KModeInitialSetting(void)
{
    // [2] reg_en_sigdect = 1'b1
    // [0] reg_en_sigdect = 1'b1
    ScalerSetBit(PB2_30_RX_CDR_16, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

    // [7] reg_pipe_manual_en = 1'b1
    ScalerSetBit(PC9_85_SPPHY_21, ~_BIT7, _BIT7);

    // [7:4] reg_lane_en = 4'b1111
    ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE0);
    ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE1);
    ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE2);
    ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE3);

    ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE0);
    ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE1);
    ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE2);
    ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE3);

    // [7:6] reg_term_sel_l0 = 2'b10 --> 95Ohm
    // [3:2] reg_term_sel_l2 = 2'b10 --> 95Ohm
    ScalerSetBit(PB2_3E_TERM_02, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(PB2_3E_TERM_02, ~(_BIT3 | _BIT2), _BIT3);

    // [7:6] reg_rx_en_self = 2'b11
    ScalerSetBit(PB2_03_RX_TOP_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [4] reg_en_rx_250m = 1'b1
    // [6] reg_en_rx_250m = 1'b1
    ScalerSetBit(PB2_0C_RX_TOP_12, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

    // [7:4] reg_en_weak_pull_g = 4'b1111
    ScalerSetBit(PB2_06_RX_TOP_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [3:0] reg_en_weak_pull_lv = 4'b0000
    ScalerSetBit(PB2_0C_RX_TOP_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7:4] reg_rx_pch_en = 4'b1111
    // [3:0] reg_rx_nch_en = 4'b1111
    ScalerSetByte(PB2_11_RX_TOP_17, 0xFF);

    // [7:4] reg_sel_div20_10_sigdtc = 4'b1111
    ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [7:6] reg_en_oobs = 2'b11
    // [5:4] reg_oobs_lfps_sel = 2'b00
    ScalerSetBit(PB2_1A_OOBS_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

    // [3:2] reg_freq_sel = 2'b00 => oobs frequency = 250M
    ScalerSetBit(PB2_1A_OOBS_00, ~(_BIT3 | _BIT2), 0x00);

    // [7:6] reg_lfps_freqsel = 2'b11 => LFPS tPeriod = 64ns
    ScalerSetBit(PB2_62_TX_LFPS_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [0] reg_en_offpn_sync = 1'b1
    // [2] reg_en_offpn_sync = 1'b1
    ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

    // [0] reg_en_cp_kp_path = 1'b1
    // [2] reg_en_cp_kp_path = 1'b1
    // [4] reg_en_fld_clk = 1'b1
    // [6] reg_en_fld_clk = 1'b1
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    // [4] reg_en_le_hv_bias = 1'b1 --> Enable LEQ HV Bias (Level Up Common Mode)
    // [6] reg_en_le_hv_bias = 1'b1 --> Enable LEQ HV Bias (Level Up Common Mode)
    ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

    // [7:6] reg_clk_stop_en = 2'b00
    ScalerSetBit(PB2_52_TX_TOP_02, ~(_BIT7 | _BIT6), 0x00);

    // [3:2] reg_pdown_dly_sel_l23 = 2'b10
    // [1:0] reg_pdown_dly_sel_l01 = 2'b10
    ScalerSetBit(PB2_54_TX_TOP_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // [7:6] reg_idle_dly_sel_l23 = 2'b10
    // [5:4] reg_idle_dly_sel_l01 = 2'b10
    ScalerSetBit(PB2_55_TX_TOP_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // [5:4] reg_en_short_elidleu0_u1 = 2'b11
    // [3] reg_sel_ckref_dfp_jfm = 1'b1 => Use APR
    ScalerSetBit(PB2_5D_TX_CMU_06, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // [7] reg_en_ufp_jfm_driver = 1'b0 => OFF When reg_sel_ckref_dfp_jfm use APR
    // [6] reg_en_dfp_jfm_driver = 1'b0 => OFF When reg_sel_ckref_dfp_jfm use APR
    ScalerSetBit(PB2_21_RX_CDR_01, ~(_BIT7 | _BIT6), 0x00);

    // [7:6] reg_rl_pdrv_bc_l01 = 2'b11
    // [7:6] reg_rl_pdrv_bc_l23 = 2'b11
    ScalerSetBit(PB2_64_TX_LFPS_04, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(PB2_66_TX_LFPS_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [6:4] reg_ib_pdrv_sel_bc_l01 = 3'b100
    // [2:0] reg_ib_pdrv_sel_bc_l23 = 3'b100
    ScalerSetBit(PB2_67_TX_LFPS_07, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);
    ScalerSetBit(PB2_67_TX_LFPS_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // [7:6] reg_vcm_sel_l23 = 2'b01 => 0.8*VDD
    // [5:4] reg_vcm_sel_l01 = 2'b01 => 0.8*VDD
    ScalerSetBit(PB2_6A_TX_RXD_02, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit(PB2_6A_TX_RXD_02, ~(_BIT5 | _BIT4), _BIT4);

    // [4] reg_spd_page_load = 1'b1
    ScalerSetBit(P7A_90_DPHY_00, ~_BIT4, _BIT4);

    // [7] reg_openloop_rx_clk_en = 1'b0
    ScalerSetBit(P7A_92_DPHY_02, ~_BIT7, 0x00);

    // [7:4] reg_rdy_timer_en = 4'b1111
    ScalerSetBit(P7A_96_DATA_TIMER_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [0] reg_acdr_en = 1'b1
    // [2] reg_acdr_en = 1'b1
    ScalerSetBit(P7A_96_DATA_TIMER_0, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

    // [7:4] reg_rx_gen2_align_cnt = 4'b0001 => Aling 1 symbol for Local loopback
    ScalerSetBit(PC9_7F_SPPHY_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

    // [0] reg_lpbk_align = 1'b0 => Tx data don't align for local loopback
    ScalerSetBit(PC9_A2_SPPHY_34, ~_BIT0, 0x00);

    // [6] reg_p1_oobs_en = 1'b1
    // [4] reg_v2a_delay_ana_en = 1'b0
    ScalerSetBit(PC9_72_SPPHY_02, ~(_BIT6 | _BIT4), _BIT6);

    // [1] reg_px_lfps_sel = 1'b1
    // [0] reg_p1_lfps_sel = 1'b1
    ScalerSetBit(PC9_73_SPPHY_03, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [7:0] reg_rx_lfps_ext = 0x40
    ScalerSetByte(PC9_B2_SPPHY_50, 0x40);

    // [5] reg_lfps_half_det = 1'b1
    ScalerSetBit(PC9_C6_LFPS_EQEN_0, ~_BIT5, _BIT5);

#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // [4:0] reg_oobs_vth_lx = 0x02
    ScalerSetBit(PB2_1D_OOBS_03, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _D1_USB_UFP_RX_OOBS_VTH);
    ScalerSetBit(PB2_1E_OOBS_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _D1_USB_UFP_RX_OOBS_VTH);

    // [4] reg_en_cco_lp_mode = 1'b0
    // [6] reg_en_cco_lp_mode = 1'b0
    ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT6 | _BIT4), 0x00);

    // [3:2] reg_rxd_tsel_l23 = 0x02
    // [1:0] reg_rxd_tsel_l01 = 0x02
    ScalerSetBit(PB2_68_TX_RXD_00, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit(PB2_68_TX_RXD_00, ~(_BIT1 | _BIT0), _BIT1);

    // normal power mode
    // [0] reg_sel_rx_250m = 1'b1 => VCO/20
    // [2] reg_sel_rx_250m = 1'b1 => VCO/20
    ScalerSetBit(PB2_0B_RX_TOP_11, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

    // [4] reg_lane_p0_tx_toggle = 1'b1 => usb3_reset_n & reg_lane_en
    ScalerSetBit(PC9_A1_SPPHY_33, ~_BIT4, _BIT4);

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // [4:0] reg_oobs_vth_lx = 5'b00100
    ScalerSetBit(PB2_1D_OOBS_03, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _D1_USB_UFP_RX_OOBS_VTH);
    ScalerSetBit(PB2_1E_OOBS_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _D1_USB_UFP_RX_OOBS_VTH);

    // [4] reg_en_cco_lp_mode = 1'b1
    // [6] reg_en_cco_lp_mode = 1'b1
    ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

    // [0] reg_en_div32_clk = 1'b1
    // [2] reg_en_div32_clk = 1'b1
    ScalerSetBit(PB2_27_RX_CDR_07, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

    // [3:2] reg_rxd_tsel_l23 = 2'b01 => 256*T
    // [1:0] reg_rxd_tsel_l01 = 2'b01 => 256*T
    ScalerSetBit(PB2_68_TX_RXD_00, ~(_BIT3 | _BIT2), _BIT2);
    ScalerSetBit(PB2_68_TX_RXD_00, ~(_BIT1 | _BIT0), _BIT0);

    if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT6 | _BIT4)) == (_BIT6 | _BIT4))
    {
        // low power mode
        // [0] reg_sel_rx_250m = 1'b0 => VCO/40
        // [2] reg_sel_rx_250m = 1'b0 => VCO/40
        ScalerSetBit(PB2_0B_RX_TOP_11, ~(_BIT2 | _BIT0), 0x00);

        // [4] reg_sel_rx_div32 = 1'b0 => VCO/32
        // [6] reg_sel_rx_div32 = 1'b0 => VCO/32
        ScalerSetBit(PB2_33_RX_CDR_19, ~(_BIT6 | _BIT4), 0x00);
    }
    else
    {
        // normal power mode
        // [0] reg_sel_rx_250m = 1'b1 => VCO/20
        // [2] reg_sel_rx_250m = 1'b1 => VCO/20
        ScalerSetBit(PB2_0B_RX_TOP_11, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        // [4] reg_sel_rx_div32 = 1'b1 => VCO/16
        // [6] reg_sel_rx_div32 = 1'b1 => VCO/16
        ScalerSetBit(PB2_33_RX_CDR_19, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
    }

#endif

    // [2] reg_auto_mode_lx = 1'b1 => Auto mode
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);

    // [7:0] reg_vco_coarse_lx[7:0] = 0x40
    // [0] reg_vco_coarse_lx[8] = 0x00
    ScalerSetByte(PB1_14_FLD_L0_20, 0x40);
    ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
    ScalerSetByte(PB1_94_FLD_L2_20, 0x40);
    ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);

    // FLD_cnt = (27 x 3) x 312.5M x 2 / 27M = 1875(0x753)
    // [7:0] reg_lock_up_limit_lx[7:0] = 0x53
    // [3:0] reg_lock_up_limit_lx[11:8] = 0x07
    ScalerSetByte(PB1_17_FLD_L0_23, 0x53);
    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
    ScalerSetByte(PB1_97_FLD_L2_23, 0x53);
    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

    // [7:0] reg_lock_dn_limit_lx[7:0] = 0x53
    // [3:0] reg_lock_dn_limit_lx[11:8] = 0x07
    ScalerSetByte(PB1_19_FLD_L0_25, 0x53);
    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
    ScalerSetByte(PB1_99_FLD_L2_25, 0x53);
    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

    // [7:0] reg_divide_num_lx[7:0] = 81 (0x51)
    // [3:0] reg_divide_num_lx[3:0] = 0x00
    ScalerSetByte(PB1_1B_FLD_L0_27, 0x51);
    ScalerSetByte(PB1_1C_FLD_L0_28, 0x00);
    ScalerSetByte(PB1_9B_FLD_L2_27, 0x51);
    ScalerSetByte(PB1_9C_FLD_L2_28, 0x00);

    ScalerUsb3RetimerUfpPhy1Gen1Setting();

    ScalerUsb3RetimerUfpPhy1Gen2Setting();

    ScalerUsb3RetimerUfpPhy1TxSscSetting();

    ScalerUsb3RetimerUfpPhy1OutputSwingSetting();

    ScalerUsb3RetimerUfpPhy1DFESetting();

    // [7] reg_fld_rst_n_lx = 1'b0 -> 1'b1 => Toggle Reset
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 150; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 150; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Reload FLD Auto Mode to Manual Mode
    ScalerSetByte(PB1_14_FLD_L0_20, ScalerGetByte(P28_32_FLD_L0_48));
    ScalerSetByte(PB1_15_FLD_L0_21, ScalerGetByte(P28_33_FLD_L0_49));
    ScalerSetByte(PB1_94_FLD_L2_20, ScalerGetByte(P28_B2_FLD_L2_48));
    ScalerSetByte(PB1_95_FLD_L2_21, ScalerGetByte(P28_B3_FLD_L2_49));

    // [2] reg_auto_mode_lx = 1'b0 => Manual mode
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, 0x00);

    // [7] reg_cp_en_manual_lx = 1'b0 => Openloop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY K mode End Setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1KModeEndSetting(void)
{
#if(_U3_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON)
    ScalerUsb3RetimerUfpPhy1PhyDisable(_FALSE, _TYPE_C_ORIENTATION_NONE, _TYPE_C_PIN_ASSIGNMENT_NONE);
#endif

    // [2] reg_en_sigdect = 1'b0
    // [0] reg_en_sigdect = 1'b0
    ScalerSetBit(PB2_30_RX_CDR_16, ~(_BIT2 | _BIT0), 0x00);

    // [2] reg_auto_mode_lx = 1'b1 => Auto mode
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);

    // [7] reg_cp_en_manual_lx = 1'b1 => Closeloop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);

    // [7] reg_pipe_manual_en = 1'b0
    ScalerSetBit(PC9_85_SPPHY_21, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Gen1 Setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1Gen1Setting(void)
{
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // [7:4] reg_le_mf_rssel_5g = 0x02
    ScalerSetBit(P7A_01_MODE_GAIN_5G_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

    // [3:0] reg_le_isel_5g = 0x07
    ScalerSetBit(P7A_01_MODE_GAIN_5G_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_le_rssel_5g = 0x0C
    ScalerSetBit(P7A_02_MODE_GAIN_5G_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

    // [3:0] reg_le_rlsel_5g = 0x04
    ScalerSetBit(P7A_02_MODE_GAIN_5G_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // [6:4] reg_sel_div_jfm_5g = 3'b001
    ScalerSetBit(P7A_03_MODE_OFFSET_K_5G_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

    // [1:0] reg_sel_leqgain_rs_5g = 0x00
    ScalerSetBit(P7A_10_FLD_5G_0, ~(_BIT1 | _BIT0), 0x00);

    // [7:3] reg_slope_icp_band_5g = 0x18
    ScalerSetBit(P7A_10_FLD_5G_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6));

    // [2] reg_cdr_cp[24:20] = 5'b00010
    // [7:4] reg_cdr_cp[24:20] = 5'b00010
    ScalerSetBit(P7A_10_FLD_5G_0, ~_BIT2, 0x00);
    ScalerSetBit(P7A_13_FLD_5G_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

    // [3:0] reg_cdr_cp[19:15] = 5'b00010
    // [7] reg_cdr_cp[19:15] = 5'b00010
    ScalerSetBit(P7A_13_FLD_5G_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P7A_12_FLD_5G_2, ~_BIT7, 0x00);

    // [6:2] reg_cdr_cp[14:10] = 5'b00010
    ScalerSetBit(P7A_12_FLD_5G_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);

    // [1:0] reg_cdr_cp[9:5] = 5'b00010
    // [7:5] reg_cdr_cp[9:5] = 5'b00010
    ScalerSetBit(P7A_12_FLD_5G_2, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_11_FLD_5G_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // [4:0] reg_cdr_cp[4:0] = 5'b00010
    ScalerSetBit(P7A_11_FLD_5G_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    // [7:5] reg_isel_v2i_5g = 3'b010
    ScalerSetBit(P7A_14_CDR_5G_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // [7:6] reg_dcc_en_txlane_5g = 2'b11
    ScalerSetBit(P7A_A1_TX_DDC_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // [7:4] reg_le_mf_rssel_5g = 4'b0010
    ScalerSetBit(P7A_01_MODE_GAIN_5G_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

    // [3:0] reg_le_isel_5g = 4'b0100
    ScalerSetBit(P7A_01_MODE_GAIN_5G_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    // [7:4] reg_le_rssel_5g = 4'b0110
    ScalerSetBit(P7A_02_MODE_GAIN_5G_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    // [3:0] reg_le_rlsel_5g = 4'b0011
    ScalerSetBit(P7A_02_MODE_GAIN_5G_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [6:4] reg_sel_div_jfm_5g = 3'b010
    ScalerSetBit(P7A_03_MODE_OFFSET_K_5G_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

    // [1:0] reg_sel_leqgain_rs_5g = 2'b01
    ScalerSetBit(P7A_10_FLD_5G_0, ~(_BIT1 | _BIT0), _BIT0);

    // [7:3] reg_slope_icp_band_5g = 5'b01110
    ScalerSetBit(P7A_10_FLD_5G_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));

    // [2] reg_cdr_cp[24:20] = 5'b01001 -> 9uA
    // [7:4] reg_cdr_cp[24:20] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_10_FLD_5G_0, ~_BIT2, 0x00);
    ScalerSetBit(P7A_13_FLD_5G_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

    // [3:0] reg_cdr_cp[19:15] = 5'b01001 -> 9uA
    // [7] reg_cdr_cp[19:15] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_13_FLD_5G_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
    ScalerSetBit(P7A_12_FLD_5G_2, ~_BIT7, _BIT7);

    // [6:2] reg_cdr_cp[14:10] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_12_FLD_5G_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // [1:0] reg_cdr_cp[9:5] = 5'b01001 -> 9uA
    // [7:5] reg_cdr_cp[9:5] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_12_FLD_5G_2, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P7A_11_FLD_5G_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // [4:0] reg_cdr_cp[4:0] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_11_FLD_5G_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

    // [7:6] reg_dcc_en_txlane_5g = 2'b00
    ScalerSetBit(P7A_A1_TX_DDC_00, ~(_BIT7 | _BIT6), 0x00);

#endif

    // [6:5] reg_div_updn_5g = 2'b00
    ScalerSetBit(P7A_00_MODE_CDR_5G, ~(_BIT6 | _BIT5), 0x00);

    // [4:2] reg_cdr_res_5g = 3'b000
    ScalerSetBit(P7A_00_MODE_CDR_5G, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

    // [1:0] reg_bbpd_pulse_sel_5g = 2'b01
    ScalerSetBit(P7A_00_MODE_CDR_5G, ~(_BIT1 | _BIT0), _BIT0);

    // [6:5] reg_txcmu_lcvco_div123_5g = 2'b00
    ScalerSetBit(P7A_04_MODE_OFFSET_K_5G_01, ~(_BIT6 | _BIT5), 0x00);

    // [4:3] reg_dr_div_tx_5g = 2'b00
    ScalerSetBit(P7A_04_MODE_OFFSET_K_5G_01, ~(_BIT4 | _BIT3), 0x00);

    // [2:0] reg_sel_div_5g = 3'b001
    ScalerSetBit(P7A_04_MODE_OFFSET_K_5G_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [9:0] reg_lfps_lperiod_5g = 0x27 => 8ns / 0.2ns - 1 = 39 (0x27)
    ScalerSetByte(PC9_C9_LFPS_EQEN_3, 0x27);
    ScalerSetBit(PC9_CD_LFPS_EQEN_7, ~(_BIT7 | _BIT6), 0x00);

    // [9:0] reg_lfps_hperiod_5g = 0x153 => 68ns / 0.2ns - 1 = 339 (0x153)
    ScalerSetByte(PC9_CB_LFPS_EQEN_5, 0x53);
    ScalerSetBit(PC9_CD_LFPS_EQEN_7, ~(_BIT3 | _BIT2), _BIT2);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Gen2 Setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1Gen2Setting(void)
{
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // [7:4] reg_le_mf_rssel_10g = 0x03
    ScalerSetBit(P7A_06_MODE_GAIN_10G_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [3:0] reg_le_isel_10g = 0x03
    ScalerSetBit(P7A_06_MODE_GAIN_10G_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [7:4] reg_le_rssel_10g = 0x0A
    ScalerSetBit(P7A_07_MODE_GAIN_10G_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // [3:0] reg_le_rlsel_10g = 0x02
    ScalerSetBit(P7A_07_MODE_GAIN_10G_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    // [6:4] reg_sel_div_jfm_10g = 3'b001
    ScalerSetBit(P7A_08_MODE_OFFSET_K_10G_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

    // [1:0] reg_sel_leqgain_rs_10g = 0x00
    ScalerSetBit(P7A_20_FLD_10G_0, ~(_BIT1 | _BIT0), 0x00);

    // [7:3] reg_slope_icp_band_10g = 0x06
    ScalerSetBit(P7A_20_FLD_10G_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));

    // [2] reg_cdr_cp[24:20] = 5'b00011
    // [7:4] reg_cdr_cp[24:20] = 5'b000011
    ScalerSetBit(P7A_20_FLD_10G_0, ~_BIT2, 0x00);
    ScalerSetBit(P7A_23_FLD_10G_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [3:0] reg_cdr_cp[19:15] = 5'b00011
    // [7] reg_cdr_cp[19:15] = 5'b00011
    ScalerSetBit(P7A_23_FLD_10G_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P7A_22_FLD_10G_2, ~_BIT7, _BIT7);

    // [6:2] reg_cdr_cp[14:10] = 5'b00011
    ScalerSetBit(P7A_22_FLD_10G_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [1:0] reg_cdr_cp[9:5] = 5'b00011
    // [7:5] reg_cdr_cp[9:5] = 5'b00011
    ScalerSetBit(P7A_22_FLD_10G_2, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_21_FLD_10G_1, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

    // [4:0] reg_cdr_cp[4:0] = 5'b00011
    ScalerSetBit(P7A_21_FLD_10G_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [7:5] reg_isel_v2i_10g = 3'b010
    ScalerSetBit(P7A_24_CDR_10G_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // [5:4] reg_dcc_en_txlane_10g = 2'b11
    ScalerSetBit(P7A_A1_TX_DDC_00, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // [7:4] reg_le_mf_rssel_10g = 4'b0011
    ScalerSetBit(P7A_06_MODE_GAIN_10G_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [3:0] reg_le_isel_10g = 4'b0011
    ScalerSetBit(P7A_06_MODE_GAIN_10G_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [7:4] reg_le_rssel_10g = 4'b1110
    ScalerSetBit(P7A_07_MODE_GAIN_10G_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5));

    // [3:0] reg_le_rlsel_10g = 4'b0001
    ScalerSetBit(P7A_07_MODE_GAIN_10G_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // [6:4] reg_sel_div_jfm_10g = 3'b010
    ScalerSetBit(P7A_08_MODE_OFFSET_K_10G_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

    // [1:0] reg_sel_leqgain_rs_10g = 2'b00
    ScalerSetBit(P7A_20_FLD_10G_0, ~(_BIT1 | _BIT0), 0x00);

    // [7:3] reg_slope_icp_band_10g = 5'b01110
    ScalerSetBit(P7A_20_FLD_10G_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));

    // [2] reg_cdr_cp[24:20] = 5'b01001 -> 9uA
    // [7:4] reg_cdr_cp[24:20] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_20_FLD_10G_0, ~_BIT2, 0x00);
    ScalerSetBit(P7A_23_FLD_10G_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

    // [3:0] reg_cdr_cp[19:15] = 5'b01001 -> 9uA
    // [7] reg_cdr_cp[19:15] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_23_FLD_10G_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
    ScalerSetBit(P7A_22_FLD_10G_2, ~_BIT7, _BIT7);

    // [6:2] reg_cdr_cp[14:10] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_22_FLD_10G_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // [1:0] reg_cdr_cp[9:5] = 5'b01001 -> 9uA
    // [7:5] reg_cdr_cp[9:5] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_22_FLD_10G_2, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P7A_21_FLD_10G_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // [4:0] reg_cdr_cp[4:0] = 5'b01001 -> 9uA
    ScalerSetBit(P7A_21_FLD_10G_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

    // [5:4] reg_dcc_en_txlane_10g = 2'b00
    ScalerSetBit(P7A_A1_TX_DDC_00, ~(_BIT5 | _BIT4), 0x00);

#endif

    // [6:5] reg_div_updn_10g = 2'b10
    ScalerSetBit(P7A_05_MODE_CDR_10G, ~(_BIT6 | _BIT5), _BIT6);

    // [4:2] reg_cdr_res_10g = 3'b000
    ScalerSetBit(P7A_05_MODE_CDR_10G, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

    // [1:0] reg_bbpd_pulse_sel_10g = 2'b01
    ScalerSetBit(P7A_05_MODE_CDR_10G, ~(_BIT1 | _BIT0), _BIT0);

    // [6:5] reg_txcmu_lcvco_div123_10g = 2'b00
    ScalerSetBit(P7A_09_MODE_OFFSET_K_10G_01, ~(_BIT6 | _BIT5), 0x00);

    // [4:3] reg_dr_div_tx_10g = 2'b00
    ScalerSetBit(P7A_09_MODE_OFFSET_K_10G_01, ~(_BIT4 | _BIT3), 0x00);

    // [2:0] reg_sel_div_10g = 3'b000
    ScalerSetBit(P7A_09_MODE_OFFSET_K_10G_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // [9:0] reg_lfps_lperiod_10g = 0x4F => 8ns / 0.1ns - 1 = 79 (0x4F)
    ScalerSetByte(PC9_CA_LFPS_EQEN_4, 0x4F);
    ScalerSetBit(PC9_CD_LFPS_EQEN_7, ~(_BIT5 | _BIT4), 0x00);

    // [9:0] reg_lfps_hperiod_10g = 0x2A7 => 68ns / 0.1ns - 1 = 679 (0x2A7)
    ScalerSetByte(PC9_CC_LFPS_EQEN_6, 0xA7);
    ScalerSetBit(PC9_CD_LFPS_EQEN_7, ~(_BIT1 | _BIT0), _BIT1);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY DFE Setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1DFESetting(void)
{
    // [6] timer_ctrl_en_lanex = 1'b1 => Enable Timer Control DFE Loop
    // [5:4] reduce_adapt_gain_lanex = 2'b10 => Reduce Gain to 1/4
    // [1:0] adapt_mode_lanex = 2'b10 => Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [5] edge_det_mode = 1'b1 => Edge Lag Data
    // [4] tap2_trans = 1'b1 => Only Transition Bit is Effective
    // [3] le_auto_reload = 1'b0 => Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay = 3'b010 => Tap1+LE Delay 2us after Tap0
    ScalerSetBit(PB2_E0_MODE_TIMER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1));

    // [7:5] tap0_gain = 3'b001 => Tap0 Loop Gain 1/512
    // [4:2] tap1_gain = 3'b011 => Tap1 Loop Gain 1/128
    ScalerSetBit(PB2_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3 | _BIT2));

    // [7:5] tap2_gain = 3'b001 => Tap2 Loop Gain 1/512
    // [4:2] tap3_gain = 3'b001 => Tap3 Loop Gain 1/512
    ScalerSetBit(PB2_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // [7:5] tap4_gain = 3'b001 => Tap4 Loop Gain 1/512
    // [4:2] servo_gain = 3'b001 => Servo Loop Gain 1/512
    ScalerSetBit(PB2_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // [7:5] le_gain1 = 3'b010 => LE Gain1 Loop Gain 1/256
    // [4:2] le_gain2 = 3'b110 => LE Gain2 Loop Gain 0
    // [1] le2_sign = 1'b0
    ScalerSetBit(PB2_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));

    // [3] le_prec_sign = 1'b0
    // [2:0] le_gain_prec = 3'b110 => LE Pre-Courser Gain 0
    ScalerSetBit(PB2_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // [7:0] gray_en = 0x21 => Disable LE Gray Code
    ScalerSetByte(PB2_EE_GRAY_DEC_1, 0x21);

    // [5:0] tap0_max = 6'b011111 => Tap0 Max is 31
    ScalerSetBit(PB2_E0_MODE_TIMER, ~_BIT6, 0x00);
    ScalerSetBit(PB2_E6_LIMIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5:0] tap1_min = 6'b001111 => Tap1 Min is -15
    ScalerSetBit(PB2_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4:0] tap2_max = 5'b00110 => Tap2 Max is 6
    // [4:0] tap2_min = 5'b00110 => Tap2 Min is -6
    ScalerSetBit(PB2_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit(PB2_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB2_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // [4:0] tap3_max = 5'b00011 => Tap3 Max is 3
    // [4:0] tap3_min = 5'b00011 => Tap3 Min is -3
    ScalerSetBit(PB2_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(PB2_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // [4:0] tap4_max = 5'b00011 => Tap4 Max is 3
    // [4:0] tap4_min = 5'b00011 => Tap4 Min is -3
    ScalerSetBit(PB2_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB2_EB_LIMIT_6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(PB2_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [5:0] vth_threshold = 6'b010010 => Vth Threshold = 18
    ScalerSetBit(PB2_F4_ERRCNT0, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit(PB2_E6_LIMIT_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // [7:4] tap0_threshold = 4'b1010 => Tap0 Threshold = 10
    ScalerSetBit(PB2_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // [7:2] servo_divisor = 6'b101000 => Set Vth/Servo-loop/Tap Divider
    // [5:0] vth_divisor = 6'b001101 => Set Vth/Servo-loop/Tap Divider
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte(PB2_EC_LOOP_DIV_1, 0xA3);

    // [1] tap1_trans = 1'b1 --> Tap1 is Effective on Transition bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every Bits
    ScalerSetBit(PB2_E3_GAIN_2, ~(_BIT1 | _BIT0), _BIT1);

    // [5] servo_notrans = 1'b0 --> Servo is Effective on Every Bits
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT5, 0x00);

    // [2:0] trans_rlength = 3'b000 --> Tap0 Run Length = 2
    ScalerSetBit(PB2_E5_GAIN_4, ~_BIT0, 0x00);
    ScalerSetBit(PB2_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);

    // [1:0] tap0_adjust = 2'b01
    ScalerSetBit(PB2_F6_ERRCNT2, ~(_BIT1 | _BIT0), _BIT0);

    // Set Vth Max = 63, Min = 12
    ScalerSetBit(PB2_F4_ERRCNT0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(PB2_F6_ERRCNT2, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetByte(PB2_F9_LIMIT_10, 0xFC);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Output Swing Setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1OutputSwingSetting(void)
{
    // [3:2] reg_main_dat_en = 2'b11
    ScalerSetBit(PB2_50_TX_TOP_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [7:6] reg_main_bc_en = 2'b11
    ScalerSetBit(PB2_63_TX_LFPS_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [5:0] reg_main_bc_in_lx = 6'b111111
    ScalerSetBit(PB2_63_TX_LFPS_03, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PB2_64_TX_LFPS_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:6] reg_rl_pdrv_l23 = 2'b11
    // [5:4] reg_rl_pdrv_l01 = 2'b11
    ScalerSetBit(PB2_54_TX_TOP_04, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [5:3] reg_ib_pdrv_sel_l23 = 3'b100
    // [2:0] reg_ib_pdrv_sel_l01 = 3'b100
    ScalerSetBit(PB2_51_TX_TOP_01, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
    ScalerSetBit(PB2_51_TX_TOP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // [7:6] reg_pre_dat_en = 2'b11
    ScalerSetBit(PB2_53_TX_TOP_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [3:2] reg_post_dat_en = 2'b11
    ScalerSetBit(PB2_53_TX_TOP_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // [1] reg_mac_deemph_en = 1'b0 => Disable Mac control Pre/Post Setting
    ScalerSetBit(PC9_71_SPPHY_01, ~_BIT1, 0x00);

    // [5:0] reg_pre_dat_in_lx = 0x1A => Valid When reg_mac_deemph_en = 1'b0
    ScalerSetByte(PC9_E5_TX_PRE_DAT_00, 0x1A);
    ScalerSetByte(PC9_E6_TX_PRE_DAT_01, 0x1A);

    // [5:0] reg_main_dat_in_lx = 0x34
    ScalerSetByte(PC9_E0_TX_MAIN_DAT_00, 0x34);
    ScalerSetByte(PC9_E1_TX_MAIN_DAT_01, 0x34);

    // [5:0] reg_post_dat_in_lx = 0x12 => Valid When reg_mac_deemph_en = 1'b0
    ScalerSetByte(PC9_E3_TX_POST_DAT_00, 0x12);
    ScalerSetByte(PC9_E4_TX_POST_DAT_01, 0x12);

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // [1] reg_mac_deemph_en = 1'b1 => Enable Mac control Pre/Post Setting
    ScalerSetBit(PC9_71_SPPHY_01, ~_BIT1, _BIT1);

    // [5:0] reg_pre_dat_in_lx = 0x22 => Valid When reg_mac_deemph_en = 1'b0
    ScalerSetByte(PC9_E5_TX_PRE_DAT_00, 0x22);
    ScalerSetByte(PC9_E6_TX_PRE_DAT_01, 0x22);

    // [5:0] reg_main_dat_in_lx = 0x3F
    ScalerSetByte(PC9_E0_TX_MAIN_DAT_00, 0x3F);
    ScalerSetByte(PC9_E1_TX_MAIN_DAT_01, 0x3F);

    // [5:0] reg_post_dat_in_lx = 0x16 => Valid When reg_mac_deemph_en = 1'b0
    ScalerSetByte(PC9_E3_TX_POST_DAT_00, 0x16);
    ScalerSetByte(PC9_E4_TX_POST_DAT_01, 0x16);

#endif

    // [5:0] reg_post_dat_nodeemph_lx => 0x00
    ScalerSetByte(PC9_E7_TX_POST_DAT_G1_00, 0x00);
    ScalerSetByte(PC9_EA_TX_POST_DAT_G1_03, 0x00);

    // [5:0] reg_post_dat_n3p5db_lx => 0x16
    ScalerSetByte(PC9_E8_TX_POST_DAT_G1_01, 0x16);
    ScalerSetByte(PC9_EB_TX_POST_DAT_G1_04, 0x16);

    // [5:0] reg_post_dat_n6db_lx => 0x16
    ScalerSetByte(PC9_E9_TX_POST_DAT_G1_02, 0x16);
    ScalerSetByte(PC9_EC_TX_POST_DAT_G1_05, 0x16);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Tx SSC Setting
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1TxSscSetting(void)
{
    // [0] reg_rdy_timer_en_tx = 1'b1
    ScalerSetBit(P7A_9D_DATA_TIMER_7, ~_BIT0, _BIT0);

    // [3:2] reg_band_out_mode_tx = 2'b01
    ScalerSetBit(P7A_D0_FLD_TX_0, ~(_BIT3 | _BIT2), _BIT2);

    // [11:0] reg_lock_up_limit_tx = 0x1F4 => FLD_cnt = (27) x 250M x 2 / 27M = 500 (0x1F4)
    ScalerSetByte(P7A_D4_FLD_TX_4, 0xF4);
    ScalerSetByte(P7A_D5_FLD_TX_5, 0x01);

    // [11:0] reg_lock_dn_limit_tx = 0x1F4 => FLD_cnt = (27) x 250M x 2 / 27M = 500 (0x1F4)
    ScalerSetByte(P7A_D6_FLD_TX_6, 0xF4);
    ScalerSetByte(P7A_D7_FLD_TX_7, 0x01);

    // [11:0] reg_divide_num_tx = 27 (0x1B)
    ScalerSetByte(P7A_D8_FLD_TX_8, 0x1B);
    ScalerSetByte(P7A_D9_FLD_TX_9, 0x00);

    // [7:3] reg_cp_time = 0.64us x ( 0x0E + 1) = 9.6us
    ScalerSetBit(P7A_DC_FLD_TX_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));

    // [4:0] reg_adp_time = 0.64us x ( 0x1E + 1) = 19.84us
    ScalerSetBit(P7A_D3_FLD_TX_3, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1));

    // [5:3] reg_calib_time = 0.64us x ( 0x07 + 1) = 5.12us
    ScalerSetBit(P7A_D1_FLD_TX_1, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // [5] reg_timer_5 = 1.28us x ( 0x01 + 1) = 2.56us
    // [4:0] reg_timer_4 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(P7A_DD_FLD_TX_13, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4:0] reg_timer_6 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(P7A_DE_FLD_TX_14, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_cdr_cp_tx[19:16] = 4'b1111 -> 22.5uA
    ScalerSetBit(P7A_E1_FLD_TX_17, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_cdr_cp_tx[15:12] = 4'b1110 -> 19.5uA
    // [3:0] reg_cdr_cp_tx[11:8] = 4'b1110 -> 19.5uA
    ScalerSetByte(P7A_E0_FLD_TX_16, 0xEE);

    // [7:4] reg_cdr_cp_tx[7:4] = 4'b1110 -> 19.5uA
    // [3:0] reg_cdr_cp_tx[3:0] = 4'b1110 -> 19.5uA
    ScalerSetByte(P7A_DF_FLD_TX_15, 0xEE);

    // [4] reg_ssc_order_tx = 1'b0 => 1 order SSC
    // [2] reg_ssc_en_enter_in_tx = 1'b0 => Disable
    ScalerSetBit(PC9_40_SSC_TX_00, ~(_BIT4 | _BIT2), 0x00);

    // [3] reg_ssc_bypass_pi_tx = 1'b0
    ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT3, 0x00);

    // [0] reg_txcmu_bypass_pi = 1'b0 => Fraction N
    // [1] reg_txcmu_bypass_r2 = 1'b0
    // [2] reg_en_diffck = 1'b1
    ScalerSetBit(PB2_58_TX_CMU_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // [6:4] reg_ck_xtal_sel_tx = 3'b011
    ScalerSetBit(PB2_5C_TX_CMU_05, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

    if(ScalerGetBit(PB2_5C_TX_CMU_05, (_BIT6 | _BIT5 | _BIT4)) == (_BIT6 | _BIT5 | _BIT4))
    {
        // ref. xtalk_L 14.318M => (VCO /2 /ref.clk) - 4 = 5G/2/14.31818M - 4 = 170.6031968
        // [8:0] reg_ssc_n_code_ini_tx = 0xAA
        ScalerSetByte(PC9_41_SSC_TX_01, 0xAA);
        ScalerSetBit(PC9_43_SSC_TX_03, ~_BIT1, 0x00);

        // [8:0] reg_ssc_n_code_tx = 0xAA
        ScalerSetByte(PC9_42_SSC_TX_02, 0xAA);
        ScalerSetBit(PC9_43_SSC_TX_03, ~_BIT0, 0x00);

        // .6031968 x 2^13 = 4941
        // [12:0] reg_ssc_f_code_tx = 0x134D
        ScalerSetByte(PC9_44_SSC_TX_04, 0x4D);
        ScalerSetByte(PC9_45_SSC_TX_05, 0x13);

        // SSC 31.5KHz down spread 5000 ppm
        // [12:0] reg_ssc_step_in_tx = 0x7DC
        ScalerSetByte(PC9_46_SSC_TX_06, 0x07);
        ScalerSetByte(PC9_47_SSC_TX_07, 0xDC);

        // [11:0] reg_ssc_tbase_in_tx = 0x1C7
        ScalerSetByte(PC9_48_SSC_TX_08, 0x01);
        ScalerSetByte(PC9_49_SSC_TX_09, 0xC7);

        // [6:0] reg_txcmu_cp_i = 0x13 => 50uA
        ScalerSetBit(PB2_59_TX_CMU_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x13);

        // [3:0] reg_txcmu_r1 = 4'b1000 => 18K
        ScalerSetBit(PB2_5C_TX_CMU_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        DebugMessageTypeC("UFP0Tx Ref. 14.318Mhz", 0);
    }
    else if(ScalerGetBit(PB2_5C_TX_CMU_05, (_BIT6 | _BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        // ref. DFPRx JFM 125M => (VCO /2 /ref.clk) - 4 = 5G/2/125M - 4 = 16
        // [8:0] reg_ssc_n_code_ini_tx = 0x10
        ScalerSetByte(PC9_41_SSC_TX_01, 0x10);
        ScalerSetBit(PC9_43_SSC_TX_03, ~_BIT1, 0x00);

        // [8:0] reg_ssc_n_code_tx = 0x10
        ScalerSetByte(PC9_42_SSC_TX_02, 0x10);
        ScalerSetBit(PC9_43_SSC_TX_03, ~_BIT0, 0x00);

        // [12:0] reg_ssc_f_code_tx = 0x00
        ScalerSetByte(PC9_44_SSC_TX_04, 0x00);
        ScalerSetByte(PC9_45_SSC_TX_05, 0x00);

        // SSC 31.5KHz down spread 5000 ppm
        // [12:0] reg_ssc_step_in_tx = 0x18
        ScalerSetByte(PC9_46_SSC_TX_06, 0x00);
        ScalerSetByte(PC9_47_SSC_TX_07, 0x18);

        // [13:0] reg_ssc_tbase_in_tx = 0xF80
        ScalerSetByte(PC9_48_SSC_TX_08, 0x0F);
        ScalerSetByte(PC9_49_SSC_TX_09, 0x80);

#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

        // [6:0] reg_txcmu_cp_i = 0x27
        ScalerSetBit(PB2_59_TX_CMU_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x27);

        // [3:0] reg_txcmu_r1 = 0x03
        ScalerSetBit(PB2_5C_TX_CMU_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x03);

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

        // [6:0] reg_txcmu_cp_i = 0x06 => 17.5uA
        ScalerSetBit(PB2_59_TX_CMU_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);

        // [3:0] reg_txcmu_r1 = 4'b1010 => 22K
        ScalerSetBit(PB2_5C_TX_CMU_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

#endif

        DebugMessageTypeC("UFP0Tx Ref. DFPRx 125Mhz", 0);
    }
    else
    {
        DebugMessageTypeC("UFP0Tx Ref. None", 0);
    }

    // [6] reg_ssc_set_valid_tx = 1'b0 -> 1'b1 -> 1'b0
    ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT6, 0x00);
    ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT6, _BIT6);
    ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Rx K OOBS
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1UfpRxKOobs(void)
{
    BYTE ucOobsSenVal = 0;
    BYTE ucOobsOffsetL0 = 0;
    BYTE ucOobsOffsetL2 = 0;
    BYTE ucTemp = 0;

    // [7:6] reg_oobs_offset_timeout [9:8] = 2'b11
    // [7:0] reg_oobs_offset_timeout [7:0] = 0xFF
    ScalerSetBit(PC9_D5_RX_K_OOBS_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte(PC9_D6_RX_K_OOBS_02, 0xFF);

    for(ucOobsSenVal = 0; ucOobsSenVal <= (_BIT1 | _BIT0); ucOobsSenVal++)
    {
        DebugMessageTypeC("phy1_ucOobsSenVal_L0", ucOobsSenVal);

        // reg_sen_val_range_l01
        ScalerSetBit(PB2_19_LDO_03, ~(_BIT3 | _BIT2), (ucOobsSenVal << 2));

        // [1:0] reg_oobs_offset_ini_l0 [9:8] = 2'b10
        // [7:0] reg_oobs_offset_ini_l0 [7:0] = 0x00
        ScalerSetBit(PC9_D9_RX_K_OOBS_05, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetByte(PC9_D8_RX_K_OOBS_04, 0x00);

        // [1] reg_oobs_offset_ok_l0 = 1'b0 -> Disable Manual Mode Calibration ok
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT1, 0x00);

        // [0] reg_oobs_offset_manual_l0 = 1'b0 -> Calibration Auto Mode
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT0, 0x00);

        // [4] reg_rstb_oobs_offset = 1'b0 >> 1'b1 -> reset
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT4, 0x00);
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT4, _BIT4);

        // [0] reg_oobs_offset_en_l0 = 1'b1 -> Set Calibration Mode Enable
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT0, _BIT0);

        // Delay Time us [0,500] Waiting for Calibration Done
        for(ucTemp = 0; ucTemp <= 50; ucTemp++)
        {
            DELAY_10US();

            if(ScalerGetBit(PC9_DC_RX_K_OOBS_08, _BIT0) == _BIT0)
            {
                break;
            }
        }

        ucOobsOffsetL0 = (((ScalerGetByte(PC9_D9_RX_K_OOBS_05) & 0xC0) >> 1) | ((ScalerGetByte(PC9_DD_RX_K_OOBS_09) & 0xF8) >> 3));

        DebugMessageTypeC("phy1_ucOobsOffsetL0", ucOobsOffsetL0);

        // [0] reg_oobs_offset_en_l0 = 1'b0 -> Disable calibration
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT0, 0x00);

        // [1] reg_oobs_offset_ok_l0 = 1'b1 -> Enable Manual Mode Calibration ok
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT1, _BIT1);

        // [0] reg_oobs_offset_manual_l0 = 1'b1 -> Calibration Manual Mode
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT0, _BIT0);

        if((ucOobsOffsetL0 != 0x7F) || (ucOobsSenVal == (_BIT1 | _BIT0)))
        {
            // Reload L0 Calibration Result
            ScalerSetBit(PC9_D9_RX_K_OOBS_05, ~(_BIT1 | _BIT0), (ScalerGetByte(PC9_D9_RX_K_OOBS_05) >> 6));
            ScalerSetByte(PC9_D8_RX_K_OOBS_04, ScalerGetByte(PC9_DD_RX_K_OOBS_09));

            break;
        }
    }

    for(ucOobsSenVal = 0; ucOobsSenVal <= (_BIT1 | _BIT0); ucOobsSenVal++)
    {
        DebugMessageTypeC("phy1_ucOobsSenVal_L2", ucOobsSenVal);

        // reg_sen_val_range_l23
        ScalerSetBit(PB2_19_LDO_03, ~(_BIT1 | _BIT0), ucOobsSenVal);

        // [1:0] reg_oobs_offset_ini_l1 [9:8] = 2'b10
        // [7:0] reg_oobs_offset_ini_l1 [7:0] = 0x00
        ScalerSetBit(PC9_DB_RX_K_OOBS_07, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetByte(PC9_DA_RX_K_OOBS_06, 0x00);

        // [5] reg_oobs_offset_ok_l1 = 1'b0 -> Disable Manual Mode Calibration ok
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT5, 0x00);

        // [4] reg_oobs_offset_manual_l1 = 1'b0 -> Calibration Auto Mode
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT4, 0x00);

        // [4] reg_rstb_oobs_offset = 1'b0 >> 1'b1 -> reset
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT4, 0x00);
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT4, _BIT4);

        // [1] reg_oobs_offset_en_l1 = 1'b1 -> Set Calibration Mode Enable
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT1, _BIT1);

        // Delay Time us [0,500] Waiting for Calibration Done
        for(ucTemp = 0; ucTemp <= 50; ucTemp++)
        {
            DELAY_10US();

            if(ScalerGetBit(PC9_DC_RX_K_OOBS_08, _BIT3) == _BIT3)
            {
                break;
            }
        }

        ucOobsOffsetL2 = (((ScalerGetByte(PC9_DB_RX_K_OOBS_07) & 0xC0) >> 1) | ((ScalerGetByte(PC9_DE_RX_K_OOBS_10) & 0xF8) >> 3));

        DebugMessageTypeC("phy1_ucOobsOffsetL2", ucOobsOffsetL2);

        // [1] reg_oobs_offset_en_l1 = 1'b0 -> Disable calibration
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT1, 0x00);

        // [5] reg_oobs_offset_ok_l1 = 1'b1 -> Enable Manual Mode Calibration ok
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT5, _BIT5);

        // [4] reg_oobs_offset_manual_l1 = 1'b1 -> Calibration Manual Mode
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT4, _BIT4);

        if((ucOobsOffsetL2 != 0x7F) || (ucOobsSenVal == (_BIT1 | _BIT0)))
        {
            // Reload L2 Calibration Result
            ScalerSetBit(PC9_DB_RX_K_OOBS_07, ~(_BIT1 | _BIT0), (ScalerGetByte(PC9_DB_RX_K_OOBS_07) >> 6));
            ScalerSetByte(PC9_DA_RX_K_OOBS_06, ScalerGetByte(PC9_DE_RX_K_OOBS_10));

            break;
        }
    }
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Rx K Offset
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1UfpRxKOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode)
{
    BYTE ucLeqLinkRateInfo = ((enumUsbLinkRateKMode == _USB_LINK_KMODE_10G) ? 0x0C : 0x00);

    if(enumUsbLinkRateKMode == _USB_LINK_KMODE_10G)
    {
        // [5:4] reg_pipe_rate_m [1:0] = 2'b01 -> Switch to 10G Mode
        ScalerSetBit(PC9_85_SPPHY_21, ~(_BIT5 | _BIT4), _BIT4);
    }
    else
    {
        // [5:4] reg_pipe_rate_m [1:0] = 2'b00 -> Switch to 5G Mode
        ScalerSetBit(PC9_85_SPPHY_21, ~(_BIT5 | _BIT4), 0x00);
    }

    // [3:2] reg_offk_delay = 2'b11 -> 8*Clock Period
    ScalerSetBit(P7A_A8_ADJR_05, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [1:0] reg_timeout_sel = 2'b11 -> Timeout After Offset K 127 Times
    ScalerSetBit(P7A_A8_ADJR_05, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [6:0] reg_sel_foreoff_autok_l0 = 7'b0111111
    // [6:0] reg_sel_foreoff_autok_l1 = 7'b0111111
    // [6:0] reg_sel_foreoff_autok_l2 = 7'b0111111
    // [6:0] reg_sel_foreoff_autok_l3 = 7'b0111111
    ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7] reg_rstb_fore_offset = 1'b1
    ScalerSetBit(P7A_A3_ADJR_00, ~_BIT7, _BIT7);

    // [3] reg_fore_offset_en_l3 = 1'b1 -> Enable Calibration
    // [2] reg_fore_offset_en_l2 = 1'b1 -> Enable Calibration
    // [1] reg_fore_offset_en_l1 = 1'b1 -> Enable Calibration
    // [0] reg_fore_offset_en_l0 = 1'b1 -> Enable Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    //////////////
    // Data_Odd //
    //////////////


    // [2:0] reg_sel_foreoff = 0x00 -> data_odd_code
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Delay Time us [0,500] Waiting for Calibration Done
    for(pData[0] = 0; pData[0] <= 50; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7) && (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7))
        {
            break;
        }
    }

    // [4:0] reg_man_data_odd_lx -> Reload Calibration Value
    ScalerSetBit((P7A_50_ADJR_DATA_ODD_L0_5G + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F));
    ScalerSetBit((P7A_51_ADJR_DATA_ODD_L2_5G + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F));


    ///////////////
    // Data_Even //
    ///////////////


    // [2:0] reg_sel_foreoff = 0x01 -> data_even_code
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // Delay Time us [0,500] Waiting for Calibration Done
    for(pData[0] = 0; pData[0] <= 50; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7) && (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7))
        {
            break;
        }
    }

    // [4:0] reg_man_data_even_lx -> Reload Calibration Value
    ScalerSetBit((P7A_52_ADJR_DATA_EVEN_L0_5G + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F));
    ScalerSetBit((P7A_53_ADJR_DATA_EVEN_L2_5G + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F));


    //////////////
    // Edge_Odd //
    //////////////


    // [2:0] reg_sel_foreoff = 0x02 -> edge_odd_code
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // Delay Time us [0,500] Waiting for Calibration Done
    for(pData[0] = 0; pData[0] <= 50; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7) && (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7))
        {
            break;
        }
    }

    // [4:0] reg_man_edge_odd_lx -> Reload Calibration Value
    ScalerSetBit((P7A_54_ADJR_EDGE_ODD_L0_5G + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F));
    ScalerSetBit((P7A_55_ADJR_EDGE_ODD_L2_5G + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F));

    ///////////////
    // Edge_Even //
    ///////////////


    // [2:0] reg_sel_foreoff = 0x03 -> edge_even_code
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for Calibration Done
    for(pData[0] = 0; pData[0] <= 50; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7) && (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7))
        {
            break;
        }
    }

    // [4:0] reg_man_edge_even_lx -> Reload Calibration Value
    ScalerSetBit((P7A_56_ADJR_EDGE_EVEN_L0_5G + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F));
    ScalerSetBit((P7A_57_ADJR_EDGE_EVEN_L2_5G + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F));

    /////////////
    // Off_Odd //
    /////////////


    // [2:0] reg_sel_foreoff = 0x04 -> off_odd_code
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Delay Time us [0,500] Waiting for Calibration Done
    for(pData[0] = 0; pData[0] <= 50; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7) && (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7))
        {
            break;
        }
    }

    // [4:0] reg_man_off_odd_lx -> Reload Calibration Value
    ScalerSetBit((P7A_58_ADJR_OFF_ODD_L0_5G + ucLeqLinkRateInfo), ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x7F));
    ScalerSetBit((P7A_59_ADJR_OFF_ODD_L2_5G + ucLeqLinkRateInfo), ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x7F));


    //////////////
    // Off_Even //
    //////////////


    // [2:0] reg_sel_foreoff = 0x05 -> off_even_code
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Delay Time us [0,500] Waiting for Calibration Done
    for(pData[0] = 0; pData[0] <= 50; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7) && (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7))
        {
            break;
        }
    }

    // [4:0] reg_man_off_even_lx -> Reload Calibration Value
    ScalerSetBit((P7A_5A_ADJR_OFF_EVEN_L0_5G + ucLeqLinkRateInfo), ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x7F));
    ScalerSetBit((P7A_5B_ADJR_OFF_EVEN_L2_5G + ucLeqLinkRateInfo), ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x7F));

    // [6:0] reg_sel_foreoff_autok_l0 = 7'b0000000
    // [6:0] reg_sel_foreoff_autok_l1 = 7'b0000000
    // [6:0] reg_sel_foreoff_autok_l2 = 7'b0000000
    // [6:0] reg_sel_foreoff_autok_l3 = 7'b0000000
    ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);


    //////////////
    // LEQ_Code //
    //////////////

    ScalerUsb3RetimerUfpPhy1UfpRxKLeqOffset(enumUsbLinkRateKMode);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Rx K LEQ
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1UfpRxKLeqOffset(EnumUsbLinkRateKMode enumUsbLinkRateKMode)
{
    BYTE ucLeqLevel = 0;
    BYTE ucLeqLinkRateInfo = ((enumUsbLinkRateKMode == _USB_LINK_KMODE_10G) ? 0x08 : 0x00);
    BYTE ucOffcalRange = 0;
    BYTE ucOffcalBoundaryHit = _FALSE;

    if(enumUsbLinkRateKMode == _USB_LINK_KMODE_10G)
    {
        // [5:4] reg_pipe_rate_m [1:0] = 2'b01 -> Switch to 10G Mode
        ScalerSetBit(PC9_85_SPPHY_21, ~(_BIT5 | _BIT4), _BIT4);
    }
    else
    {
        // [5:4] reg_pipe_rate_m [1:0] = 2'b00 -> Switch to 5G Mode
        ScalerSetBit(PC9_85_SPPHY_21, ~(_BIT5 | _BIT4), 0x00);
    }

    // [5:0] reg_tap0_level0 = 0x04 -> LV0 max.4
    // [5:0] reg_tap0_level1 = 0x08 -> LV1 max.8
    // [5:0] reg_tap0_level2 = 0x0C -> LV2 max.12
    // [5:0] reg_tap0_level3 = 0x10 -> LV3 max.16
    // [5:0] reg_tap0_level4 = 0x14 -> LV4 max.20
    // [5:0] reg_tap0_level5 = 0x18 -> LV5 max.24
    // [5:0] reg_tap0_level6 = 0x1C -> LV6 max.28
    ScalerSetBit(P7A_68_ADJR_U3_TAP0_LV0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
    ScalerSetBit(P7A_69_ADJR_U3_TAP0_LV1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit(P7A_6A_ADJR_U3_TAP0_LV2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
    ScalerSetBit(P7A_6B_ADJR_U3_TAP0_LV3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    ScalerSetBit(P7A_6C_ADJR_U3_TAP0_LV4, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
    ScalerSetBit(P7A_6D_ADJR_U3_TAP0_LV5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    ScalerSetBit(P7A_6E_ADJR_U3_TAP0_LV6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2));

    for(ucOffcalRange = 0; ucOffcalRange <= (_BIT1 | _BIT0); ucOffcalRange++)
    {
        ucOffcalBoundaryHit = _FALSE;

        if(enumUsbLinkRateKMode == _USB_LINK_KMODE_10G)
        {
            // [1:0] reg_offcal_range_10g
            ScalerSetBit(P7A_08_MODE_OFFSET_K_10G_00, ~(_BIT1 | _BIT0), ucOffcalRange);
        }
        else
        {
            // [1:0] reg_offcal_range_5g
            ScalerSetBit(P7A_03_MODE_OFFSET_K_5G_00, ~(_BIT1 | _BIT0), ucOffcalRange);
        }

        for(ucLeqLevel = 0; ucLeqLevel <= 7; ucLeqLevel++)
        {
            // tap0_init_lane0 [4:0] -> Set Tap0 Initial
            // tap0_init_lane1 [4:0] -> Set Tap0 Initial
            // tap0_init_lane2 [4:0] -> Set Tap0 Initial
            // tap0_init_lane3 [4:0] -> Set Tap0 Initial
            ScalerSetBit(PB2_A4_L0_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLeqLevel << 2) + 2));
            ScalerSetBit(PB2_B4_L1_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLeqLevel << 2) + 2));
            ScalerSetBit(PB2_C4_L2_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLeqLevel << 2) + 2));
            ScalerSetBit(PB2_D4_L3_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLeqLevel << 2) + 2));

            // load_in_init_lane0 [7:0] = 0x01 >> 0x00 -> Tap0 Reload
            // load_in_init_lane1 [7:0] = 0x01 >> 0x00 -> Tap0 Reload
            // load_in_init_lane2 [7:0] = 0x01 >> 0x00 -> Tap0 Reload
            // load_in_init_lane3 [7:0] = 0x01 >> 0x00 -> Tap0 Reload
            ScalerSetByte(PB2_AA_L0_INIT_8, 0x01);
            ScalerSetByte(PB2_BA_L1_INIT_8, 0x01);
            ScalerSetByte(PB2_CA_L2_INIT_8, 0x01);
            ScalerSetByte(PB2_DA_L3_INIT_8, 0x01);

            ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);
            ScalerSetByte(PB2_BA_L1_INIT_8, 0x00);
            ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);
            ScalerSetByte(PB2_DA_L3_INIT_8, 0x00);

            // [6:0] reg_sel_foreoff_autok_l0 = 7'b1000000
            // [6:0] reg_sel_foreoff_autok_l1 = 7'b1000000
            // [6:0] reg_sel_foreoff_autok_l2 = 7'b1000000
            // [6:0] reg_sel_foreoff_autok_l3 = 7'b1000000
            ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
            ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
            ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
            ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);

            // [2:0] reg_sel_foreoff = 0x06 -> leq_code
            ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // [7] reg_rstb_fore_offset = 1'b1
            ScalerSetBit(P7A_A3_ADJR_00, ~_BIT7, _BIT7);

            // [3] reg_fore_offset_en_l3 = 1'b1 -> Enable Calibration
            // [2] reg_fore_offset_en_l2 = 1'b1 -> Enable Calibration
            // [1] reg_fore_offset_en_l1 = 1'b1 -> Enable Calibration
            // [0] reg_fore_offset_en_l0 = 1'b1 -> Enable Calibration
            ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // Delay Time us [0,500] Waiting for Calibration Done
            for(pData[0] = 0; pData[0] <= 50; pData[0]++)
            {
                DELAY_10US();

                if((ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7) && (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7))
                {
                    break;
                }
            }

            if(((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) == 0x00) ||
               ((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) == 0x1F) ||
               ((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) == 0x00) ||
               ((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) == 0x1F))
            {
                ucOffcalBoundaryHit = _TRUE;

                if(ucOffcalRange != (_BIT1 | _BIT0))
                {
                    break;
                }
            }

            // [4:0] reg_leq_offset_level0_l0_5g -> Reload Calibration Value
            // [4:0] reg_leq_offset_level0_l1_5g -> Reload Calibration Value
            ScalerSetBit((P7A_70_ADJR_LEQ_LV0_L0_5G + ucLeqLevel + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F));
            ScalerSetBit((P7A_80_ADJR_LEQ_LV0_L2_5G + ucLeqLevel + ucLeqLinkRateInfo), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F));

            // [6:0] reg_sel_foreoff_autok_l0 = 7'b0000000
            // [6:0] reg_sel_foreoff_autok_l1 = 7'b0000000
            // [6:0] reg_sel_foreoff_autok_l2 = 7'b0000000
            // [6:0] reg_sel_foreoff_autok_l3 = 7'b0000000
            ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }

        if((ucOffcalBoundaryHit == _FALSE) || (ucOffcalRange == 0x03))
        {
            break;
        }
    }

    // tap0_init_lane0 [4:0] -> Set Tap0 Initial
    // tap0_init_lane1 [4:0] -> Set Tap0 Initial
    // tap0_init_lane2 [4:0] -> Set Tap0 Initial
    // tap0_init_lane3 [4:0] -> Set Tap0 Initial
    ScalerSetBit(PB2_A4_L0_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
    ScalerSetBit(PB2_B4_L1_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
    ScalerSetBit(PB2_C4_L2_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
    ScalerSetBit(PB2_D4_L3_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // load_in_init_lane0 [7:0] = 0x01 >> 0x00 -> Tap0 Reload
    // load_in_init_lane1 [7:0] = 0x01 >> 0x00 -> Tap0 Reload
    // load_in_init_lane2 [7:0] = 0x01 >> 0x00 -> Tap0 Reload
    // load_in_init_lane3 [7:0] = 0x01 >> 0x00 -> Tap0 Reload
    ScalerSetByte(PB2_AA_L0_INIT_8, 0x01);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x01);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x01);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x01);

    ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x00);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x00);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1Initial(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumOrientation)
{
    switch(enumTypeCPinCfgType)
    {
        case _TYPE_C_PIN_ASSIGNMENT_D:

            // Lane01
            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                DebugMessageTypeC("[Retimer] TypeC Pin_D UnFlip", enumOrientation);

                ScalerUsb3RetimerUfpPhy1UfpUnflipConfigInitial();

                ScalerUsb3RetimerUfpPhy1UfpUnflipInitial();
            }
            else // Lane23
            {
                DebugMessageTypeC("[Retimer] TypeC Pin_D Flip", enumOrientation);

                ScalerUsb3RetimerUfpPhy1UfpFlipConfigInitial();

                ScalerUsb3RetimerUfpPhy1UfpFlipInitial();
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            // Lane01
            if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                DebugMessageTypeC("[Retimer] TypeC Pin_None UnFlip", enumOrientation);

                ScalerUsb3RetimerUfpPhy1UfpUnflipConfigInitial();

                ScalerUsb3RetimerUfpPhy1UfpUnflipInitial();
                ScalerUsb3RetimerUfpPhy1UfpFlipInitial();
            }
            else // Lane23
            {
                DebugMessageTypeC("[Retimer] TypeC Pin_None Flip", enumOrientation);

                ScalerUsb3RetimerUfpPhy1UfpFlipConfigInitial();

                ScalerUsb3RetimerUfpPhy1UfpUnflipInitial();
                ScalerUsb3RetimerUfpPhy1UfpFlipInitial();
            }

            break;

        default:
            break;
    }

    // Enable JFM
    ScalerSetBit(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), _BIT6);
    ScalerSetBit(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // [1] reg_ssc_en_tx = 1'b0 => SSC OFF
    ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT1, 0x00);

    // [7] reg_txcmu_ldo_en = 1'b1
    ScalerSetBit(PB2_5C_TX_CMU_05, ~_BIT7, _BIT7);

    // [3:0] reg_txcmu_vc_sel = 4'b0110 => 0.8V
    ScalerSetBit(PB2_5A_TX_CMU_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // [2:0] reg_txcmu_lcvco_ib = 3'b100 => ib x 6
    ScalerSetBit(PB2_5B_TX_CMU_04, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // [3:2] reg_txcmu_lc_ls_mode = 2'b00
    ScalerSetBit(PB2_5E_TX_CMU_07, ~(_BIT3 | _BIT2), 0x00);

    // [7] reg_reserve7<7> = 1'b1
    // [1:0] reg_reserve7<1:0> = 1'b01
    ScalerSetBit(PB2_6F_TX_RESERVE_03, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT0));

    // [2:0] reg_txcmu_pi_i = 3'b101
    ScalerSetBit(PB2_5D_TX_CMU_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Delay 5ms for Waiting LDO Stable
    ScalerTimerDelayXms(5);

    // [7] reg_txcmu_en = 1'b1
    // [4] reg_ck_mntrack_en_tx = 1'b1
    ScalerSetBit(PB2_57_TX_CMU_00, ~_BIT7, 0x00);
    ScalerSetBit(PB2_57_TX_CMU_00, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

    // Delay Time us [100,x] Waiting for CMU Clk Stable
    DELAY_XUS(100);

    // [0] reg_ssc_rst_n_tx = 1'b0 -> 1'b1
    ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT0, 0x00);
    ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT0, _BIT0);

    // Disable LE Gray Code
    ScalerSetByte(PB2_EE_GRAY_DEC_1, 0x21);

    // [7:6] vth_divisor = 2'b11
    ScalerSetBit(PB2_ED_LOOP_DIV_2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // [7] reg_fld_rst_n = 1'b0 -> 1'b1 => Toggle fld_rst
    ScalerSetBit(P7A_D0_FLD_TX_0, ~_BIT7, 0x00);
    ScalerSetBit(P7A_D0_FLD_TX_0, ~_BIT7, _BIT7);

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 40; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(P7A_E8_FLD_TX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(P7A_E8_FLD_TX_24, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Reload FLD Auto Mode to Manual Mode
    ScalerSetByte(P7A_D2_FLD_TX_2, ScalerGetByte(P7A_E9_FLD_TX_25));
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Unflip Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1UfpUnflipInitial(void)
{
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // [7:3] reg_slope_vco_band_lx = 0x09
    ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT3));

    // normal power mode
    // [0]reg_sel_rx_250m = 1'b1 => VCO/20
    ScalerSetBit(PB2_0B_RX_TOP_11, ~_BIT0, _BIT0);

    // [0] reg_lehv_isel_msb = 1'b1
    ScalerSetBit(PB2_0D_RX_TOP_13, ~_BIT0, _BIT0);

    // [6:4] reg_sel_large_kvco_l0 = 3'b100
    ScalerSetBit(PB2_0F_RX_TOP_15, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // [4] reg_en_cco_lp_mode = 1'b0
    ScalerSetBit(PB2_22_RX_CDR_02, ~_BIT4, 0x00);

    // [0] reg_en_lpf_dual_loop = 1'b1
    ScalerSetBit(PB2_26_RX_CDR_06, ~_BIT0, _BIT0);

    // [0] reg_v2i_lpf_force_en = 1'b1
    ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT0, _BIT0);

    // [4] reg_kvco_lpmode_sel = 1'b0
    ScalerSetBit(PB2_2B_RX_CDR_11, ~_BIT4, 0x00);

    // [6:4] reg_large_kvco_lpf_sel_l0 = 3'b100
    ScalerSetBit(PB2_31_RX_CDR_17, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // [0] reg_en_icpkp_track = 1'b1
    ScalerSetBit(PB2_33_RX_CDR_19, ~_BIT0, _BIT0);

    // [1:0] reg_ldo_cp_vsel_l0 = 2'b10
    ScalerSetBit(PB2_35_RX_CDR_21, ~(_BIT1 | _BIT0), _BIT1);

    // [2:0] reg_sel_icp_kp_ratio_l0 = 3'b101
    ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // [4]reg_txterm_vcm_en_l01 = 1'b1
    ScalerSetBit(PB2_56_TX_TOP_06, ~_BIT4, _BIT4);

    // [5:0] tap_divisor_l01 = 10 for All Other Pattern
    ScalerSetBit(PB2_ED_LOOP_DIV_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0A);

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // [7:3] reg_slope_vco_band_lx = 5'b00111
    ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // [6:4] reg_sel_large_iptat_l0 = 3'b000
    ScalerSetBit(PB2_0D_RX_TOP_13, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // [6:4] reg_sel_large_kvco_l0 = 3'b101
    ScalerSetBit(PB2_0F_RX_TOP_15, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // [4] reg_en_cco_lp_mode = 1'b1
    ScalerSetBit(PB2_22_RX_CDR_02, ~_BIT4, _BIT4);

    // [0] reg_en_lpf_dual_loop = 1'b0
    ScalerSetBit(PB2_26_RX_CDR_06, ~_BIT0, 0x00);

    // [4] reg_kvco_lpmode_sel = 1'b1
    ScalerSetBit(PB2_2B_RX_CDR_11, ~_BIT4, _BIT4);

    // [4] reg_en_half_pd = 1'b1
    ScalerSetBit(PB2_30_RX_CDR_16, ~_BIT4, _BIT4);

    // [6:4] reg_large_kvco_lpf_sel_l0 = 3'b101
    ScalerSetBit(PB2_31_RX_CDR_17, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // [0] reg_en_icpkp_track = 1'b0
    ScalerSetBit(PB2_33_RX_CDR_19, ~_BIT0, 0x00);

    // [2:0] reg_isel_v2i_l0 = 3'b011
    ScalerSetBit(PB2_35_RX_CDR_21, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [5:0] tap_divisor = 10 for All Other Pattern
    ScalerSetBit(PB2_ED_LOOP_DIV_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0A);

    if(ScalerGetBit(PB2_22_RX_CDR_02, _BIT4) == _BIT4)
    {
        // low power mode
        // [0]reg_sel_rx_250m = 1'b0 => VCO/40
        ScalerSetBit(PB2_0B_RX_TOP_11, ~_BIT0, 0x00);

        // [4]reg_sel_rx_div32 = 1'b0 => VCO/32
        ScalerSetBit(PB2_33_RX_CDR_19, ~_BIT4, 0x00);
    }
    else
    {
        // normal power mode
        // [0]reg_sel_rx_250m = 1'b1 => VCO/20
        ScalerSetBit(PB2_0B_RX_TOP_11, ~_BIT0, _BIT0);

        // [4]reg_sel_rx_div32 = 1'b1 => VCO/16
        ScalerSetBit(PB2_33_RX_CDR_19, ~_BIT4, _BIT4);
    }

#endif

    // [5:4] reg_lane_en = 2'b11
    ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE0);
    ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE1);

    ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE0);
    ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE1);

    // [1:0] reg_vcm_tune_l0 = 2'b10
    ScalerSetBit(PB2_05_RX_TOP_05, ~(_BIT1 | _BIT0), _BIT1);

    // [3:0] reg_ldo_vsel_l0 = 4'b1010
    ScalerSetBit(PB2_17_LDO_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // [6] reg_en_oobs = 1'b1
    ScalerSetBit(PB2_1A_OOBS_00, ~_BIT6, _BIT6);

    // [0] reg_vco_lpf_force_en = 1'b1
    ScalerSetBit(PB2_20_RX_CDR_00, ~_BIT0, _BIT0);

    // [0] reg_en_offpn_sync = 1'b1
    ScalerSetBit(PB2_22_RX_CDR_02, ~_BIT0, _BIT0);

    // [4] reg_bbpd_vote_en = 1'b1
    ScalerSetBit(PB2_24_RX_CDR_04, ~_BIT4, _BIT4);

    // [0] reg_sel_large_icp_kp = 1'b0
    ScalerSetBit(PB2_25_RX_CDR_05, ~_BIT0, 0x00);

    // [0] reg_en_vco_lpf = 1'b1
    ScalerSetBit(PB2_2B_RX_CDR_11, ~_BIT0, _BIT0);

    // [0] reg_en_cp_kp_path = 1'b1
    // [4] reg_en_fld_clk = 1'b1
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

    // [4] reg_en_iki_track = 1'b1
    ScalerSetBit(PB2_34_RX_CDR_20, ~_BIT4, _BIT4);

    // [4] reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias (Level Up Common Mode)
    ScalerSetBit(PB2_37_RX_EQ_00, ~_BIT4, _BIT4);

    // [0] reg_sel_dfe_delay_tap1 = 1'b0
    ScalerSetBit(PB2_13_RX_TOP_19, ~_BIT0, 0x00);

    // Disable All Adaptation Loop
    ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0x00);

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte(PB2_A2_L0_LIMIT_INIT, 0xF8);
    ScalerSetByte(PB2_A3_L0_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte(PB2_A4_L0_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte(PB2_A5_L0_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte(PB2_A6_L0_INIT_4, 0x00);

    // Vth Initial Value = 24
    ScalerSetByte(PB2_A9_L0_INIT_7, 0x18);

    // Load Intial DFE Code
    ScalerSetByte(PB2_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(PB2_EF_RESET_1, ~_BIT0, 0x00);
    ScalerSetBit(PB2_EF_RESET_1, ~_BIT0, _BIT0);

    // Enable LE/Vth/Tap0~Tap4
    ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xDF);

    // [4] reg_rdy_timer_en = 1'b1
    // [0] reg_acdr_en = 1'b1
    ScalerSetBit(P7A_96_DATA_TIMER_0, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

    // [5:4] reg_en_data_manual = 2'b00
    // [1:0] reg_bypass_data_rdy = 2'b00
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [6:0] reg_sel_foreoff_autok_lx = 6'b000000
    ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [0] reg_fore_offset_en_lx = 1'b1
    ScalerSetBit(P7A_A7_ADJR_04, ~_BIT0, _BIT0);

    // [5] reg_slope_icp_manual_lx = 1'b1 => manual mode
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT5, _BIT5);

    // [4] reg_slope_vco_manual_lx = 1'b1 => manual mode
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT4, _BIT4);

    // [3:2] reg_band_out_mode_lx = 2'b00 => band normal
    ScalerSetBit(PB1_00_FLD_L0_0, ~(_BIT3 | _BIT2), 0x00);

    // [2] reg_auto_mode_lx = 1'b1 => Auto mode
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);

    // [7:0] reg_vco_coarse_lx[7:0] = 0x40
    // [0] reg_vco_coarse_lx[8] = 0x00
    ScalerSetByte(PB1_14_FLD_L0_20, 0x40);
    ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);

    // FLD_cnt = (27 x 3) x 312.5M x 2 / 27M = 1875(0x753)
    // [7:0] reg_lock_up_limit_lx[7:0] = 0x53
    // [3:0] reg_lock_up_limit_lx[11:8] = 0x07
    ScalerSetByte(PB1_17_FLD_L0_23, 0x53);
    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

    // [7:0] reg_lock_dn_limit_lx[7:0] = 0x53
    // [3:0] reg_lock_dn_limit_lx[11:8] = 0x07
    ScalerSetByte(PB1_19_FLD_L0_25, 0x53);
    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

    // [7:0] reg_divide_num_lx[7:0] = 81 (0x51)
    // [3:0] reg_divide_num_lx[3:0] = 0x00
    ScalerSetByte(PB1_1B_FLD_L0_27, 0x51);
    ScalerSetByte(PB1_1C_FLD_L0_28, 0x00);

    // [7:3] reg_cp_time = 0.64us x ( 0x0E + 1) = 9.6us
    ScalerSetBit(PB1_3D_FLD_L0_59, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));

    // [4:0] reg_adp_time = 0.64us x ( 0x1E + 1) = 19.84us
    ScalerSetBit(PB1_16_FLD_L0_22, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1));

    // [5:3] reg_calib_time = 0.64us x ( 0x07 + 1) = 5.12us
    ScalerSetBit(PB1_13_FLD_L0_19, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // [5] reg_timer_5 = 1.28us x ( 0x01 + 1) = 2.56us
    // [4:0] reg_timer_4 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(PB1_20_FLD_L0_30, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4:0] reg_timer_6 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(PB1_21_FLD_L0_31, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4:0] reg_slope_icp_offset_lx[4:0] = 5'b0000
    ScalerSetBit(PB1_25_FLD_L0_35, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [1:0] reg_slope_icp_offset_lx[9:5] = 5'b0001
    // [7:5] reg_slope_icp_offset_lx[9:5] = 5'b0001
    ScalerSetBit(PB1_26_FLD_L0_36, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB1_25_FLD_L0_35, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // [6:2] reg_slope_icp_offset_lx[14:10] = 5'b0001
    ScalerSetBit(PB1_26_FLD_L0_36, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);

    // [3:0] reg_slope_icp_offset_lx[19:15] = 5'b0010
    // [7] reg_slope_icp_offset_lx[19:15] = 5'b0010
    ScalerSetBit(PB1_27_FLD_L0_37, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_26_FLD_L0_36, ~_BIT7, 0x00);

    // [1] reg_slope_icp_offset_lx[24:20] = 5'b0010
    // [7:4] reg_slope_icp_offset_lx[24:20] = 5'b0010
    ScalerSetBit(PB1_29_FLD_L0_39, ~_BIT1, 0x00);
    ScalerSetBit(PB1_27_FLD_L0_37, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

    // [5:0] reg_cdr_r_lx = 6'b000000
    ScalerSetBit(PB1_2B_FLD_L0_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [1:0] reg_ic_sel_lx = 2'b01 --> Icp Select NV
    ScalerSetBit(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);

    // [5] reg_fld_ok_manual_lx = 1'b0
    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, 0x00);

    // [4] reg_en_clkout_manual = 1'b0
    // [0] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT4 | _BIT0), 0x00);

    // [7] reg_fld_rst_n_lx = 1'b0 -> 1'b1 => Toggle Reset
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 150; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Reload FLD Auto Mode to Manual Mode
    ScalerSetByte(PB1_14_FLD_L0_20, ScalerGetByte(PB1_32_FLD_L0_48));
    ScalerSetByte(PB1_15_FLD_L0_21, ScalerGetByte(PB1_33_FLD_L0_49));

#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)
    // [4] reg_en_clkout_manual = 1'b1
    // [0] reg_bypass_clk_rdy = 1'b1
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
#endif
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Unflip Config Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1UfpUnflipConfigInitial(void)
{
    // [6] reg_jfm_sel_lane = 1'b0 => Lane0
    ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT6, 0x00);

    // [4] reg_jfm_rxlane_sel = 1'b0 => Lane0
    ScalerSetBit(P7A_92_DPHY_02, ~_BIT4, 0x00);

    // [0] reg_lane_config_init = 1'b0 => Initial Lane config to Lane0
    ScalerSetBit(PC9_AD_SPPHY_45, ~_BIT0, 0x00);

    // [0] reg_lane_debug_sel = 1'b0 => Lane0/1
    ScalerSetBit(PC9_A7_SPPHY_39, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Flip Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1UfpFlipInitial(void)
{
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // [7:3] reg_slope_vco_band_lx = 0x09
    ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT3));

    // normal power mode
    // [2]reg_sel_rx_250m = 1'b1 => VCO/20
    ScalerSetBit(PB2_0B_RX_TOP_11, ~_BIT2, _BIT2);

    // [2] reg_lehv_isel_msb = 1'b1
    ScalerSetBit(PB2_0D_RX_TOP_13, ~_BIT2, _BIT2);

    // [6:4] reg_sel_large_kvco_l2 = 3'b100
    ScalerSetBit(PB2_10_RX_TOP_16, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // [6] reg_en_cco_lp_mode = 1'b0
    ScalerSetBit(PB2_22_RX_CDR_02, ~_BIT6, 0x00);

    // [2] reg_en_lpf_dual_loop = 1'b1
    ScalerSetBit(PB2_26_RX_CDR_06, ~_BIT2, _BIT2);

    // [2] reg_v2i_lpf_force_en = 1'b1
    ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT2, _BIT2);

    // [6] reg_kvco_lpmode_sel = 1'b0
    ScalerSetBit(PB2_2B_RX_CDR_11, ~_BIT6, 0x00);

    // [6:4] reg_large_kvco_lpf_sel_l2 = 3'b100
    ScalerSetBit(PB2_32_RX_CDR_18, ~(_BIT6 | _BIT5 | _BIT4), _BIT6);

    // [2] reg_en_icpkp_track = 1'b1
    ScalerSetBit(PB2_33_RX_CDR_19, ~_BIT2, _BIT2);

    // [1:0] reg_ldo_cp_vsel_l2 = 2'b10
    ScalerSetBit(PB2_35_RX_CDR_21, ~(_BIT5 | _BIT4), _BIT5);

    // [2:0] reg_sel_icp_kp_ratio_l2 = 3'b101
    ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // [5]reg_txterm_vcm_en_l23 = 1'b1
    ScalerSetBit(PB2_56_TX_TOP_06, ~_BIT5, _BIT5);

    // [5:0] tap_divisor_l23 = 10 for All Other Pattern
    ScalerSetBit(PB2_FB_DEBUG, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0A);

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // [7:3] reg_slope_vco_band_lx = 5'b00111
    ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // [6:4] reg_sel_large_iptat_l2 = 3'b000
    ScalerSetBit(PB2_0E_RX_TOP_14, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // [6:4] reg_sel_large_kvco_l2 = 3'b101
    ScalerSetBit(PB2_10_RX_TOP_16, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // [6] reg_en_cco_lp_mode = 1'b1
    ScalerSetBit(PB2_22_RX_CDR_02, ~_BIT6, _BIT6);

    // [2] reg_en_lpf_dual_loop = 1'b0
    ScalerSetBit(PB2_26_RX_CDR_06, ~_BIT2, 0x00);

    // [6] reg_kvco_lpmode_sel = 1'b1
    ScalerSetBit(PB2_2B_RX_CDR_11, ~_BIT6, _BIT6);

    // [6] reg_en_half_pd = 1'b1
    ScalerSetBit(PB2_30_RX_CDR_16, ~_BIT6, _BIT6);

    // [6:4] reg_large_kvco_lpf_sel_l2 = 3'b101
    ScalerSetBit(PB2_32_RX_CDR_18, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // [2] reg_en_icpkp_track = 1'b0
    ScalerSetBit(PB2_33_RX_CDR_19, ~_BIT2, 0x00);

    // [2:0] reg_isel_v2i_l2 = 3'b011
    ScalerSetBit(PB2_36_RX_CDR_22, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [5:0] tap_divisor = 10 for All Other Pattern
    ScalerSetBit(PB2_ED_LOOP_DIV_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0A);

    if(ScalerGetBit(PB2_22_RX_CDR_02, _BIT6) == _BIT6)
    {
        // low power mode
        // [2]reg_sel_rx_250m = 1'b0 => VCO/40
        ScalerSetBit(PB2_0B_RX_TOP_11, ~_BIT2, 0x00);

        // [6]reg_sel_rx_div32 = 1'b0 => VCO/32
        ScalerSetBit(PB2_33_RX_CDR_19, ~_BIT6, 0x00);
    }
    else
    {
        // normal power mode
        // [2] reg_sel_rx_250m = 1'b1 => VCO/20
        ScalerSetBit(PB2_0B_RX_TOP_11, ~_BIT2, _BIT2);

        // [6]reg_sel_rx_div32 = 1'b1 => VCO/16
        ScalerSetBit(PB2_33_RX_CDR_19, ~_BIT6, _BIT6);
    }

#endif

    // [7:6] reg_lane_en = 2'b11
    ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE2);
    ScalerGDIPhyRx1LanePower(_ENABLE, _GDI_PHY_LANE3);

    ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE2);
    ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE3);

    // [5:4] reg_vcm_tune_l2 = 2'b10
    ScalerSetBit(PB2_05_RX_TOP_05, ~(_BIT5 | _BIT4), _BIT5);

    // [3:0] reg_ldo_vsel_l2 = 4'b1010
    ScalerSetBit(PB2_18_LDO_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // [7] reg_en_oobs = 1'b1
    ScalerSetBit(PB2_1A_OOBS_00, ~_BIT7, _BIT7);

    // [2] reg_vco_lpf_force_en = 1'b1
    ScalerSetBit(PB2_20_RX_CDR_00, ~_BIT2, _BIT2);

    // [2] reg_en_offpn_sync = 1'b1
    ScalerSetBit(PB2_22_RX_CDR_02, ~_BIT2, _BIT2);

    // [6] reg_bbpd_vote_en = 1'b1
    ScalerSetBit(PB2_24_RX_CDR_04, ~_BIT6, _BIT6);

    // [2] reg_sel_large_icp_kp = 1'b0
    ScalerSetBit(PB2_25_RX_CDR_05, ~_BIT2, 0x00);

    // [2] reg_en_vco_lpf = 1'b1
    ScalerSetBit(PB2_2B_RX_CDR_11, ~_BIT2, _BIT2);

    // [2] reg_en_cp_kp_path = 1'b1
    // [6] reg_en_fld_clk = 1'b1
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

    // [6] reg_en_iki_track = 1'b1
    ScalerSetBit(PB2_34_RX_CDR_20, ~_BIT6, _BIT6);

    // [6] reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias (Level Up Common Mode)
    ScalerSetBit(PB2_37_RX_EQ_00, ~_BIT6, _BIT6);

    // [2] reg_sel_dfe_delay_tap1 = 1'b0
    ScalerSetBit(PB2_13_RX_TOP_19, ~_BIT2, 0x00);

    // Disable All Adaptation Loop
    ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0x00);

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte(PB2_C2_L2_LIMIT_INIT, 0xF8);
    ScalerSetByte(PB2_C3_L2_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte(PB2_C4_L2_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte(PB2_C5_L2_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte(PB2_C6_L2_INIT_4, 0x00);

    // Vth Initial Value = 24
    ScalerSetByte(PB2_C9_L2_INIT_7, 0x18);

    // Load Intial DFE Code
    ScalerSetByte(PB2_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(PB2_EF_RESET_1, ~_BIT2, 0x00);
    ScalerSetBit(PB2_EF_RESET_1, ~_BIT2, _BIT2);

    // Enable LE/Vth/Tap0~Tap4
    ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xDF);

    // [6] reg_rdy_timer_en = 1'b1
    // [2] reg_acdr_en = 1'b1
    ScalerSetBit(P7A_96_DATA_TIMER_0, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

    // [7:6] reg_en_data_manual = 2'b00
    // [3:2] reg_bypass_data_rdy = 2'b00
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [6:0] reg_sel_foreoff_autok_lx = 6'b000000
    ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [2] reg_fore_offset_en_lx = 1'b1
    ScalerSetBit(P7A_A7_ADJR_04, ~_BIT2, _BIT2);

    // [5] reg_slope_icp_manual_lx = 1'b1 => manual mode
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT5, _BIT5);

    // [4] reg_slope_vco_manual_lx = 1'b1 => manual mode
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT4, _BIT4);

    // [3:2] reg_band_out_mode_lx = 2'b00 => band normal
    ScalerSetBit(PB1_80_FLD_L2_0, ~(_BIT3 | _BIT2), 0x00);

    // [2] reg_auto_mode_lx = 1'b1 => Auto mode
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);

    // [7:0] reg_vco_coarse_lx[7:0] = 0x40
    // [0] reg_vco_coarse_lx[8] = 0x00
    ScalerSetByte(PB1_94_FLD_L2_20, 0x40);
    ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);

    // FLD_cnt = (27 x 3) x 312.5M x 2 / 27M = 1875(0x753)
    // [7:0] reg_lock_up_limit_lx[7:0] = 0x53
    // [3:0] reg_lock_up_limit_lx[11:8] = 0x07
    ScalerSetByte(PB1_97_FLD_L2_23, 0x53);
    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

    // [7:0] reg_lock_dn_limit_lx[7:0] = 0x53
    // [3:0] reg_lock_dn_limit_lx[11:8] = 0x07
    ScalerSetByte(PB1_99_FLD_L2_25, 0x53);
    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

    // [7:0] reg_divide_num_lx[7:0] = 81 (0x51)
    // [3:0] reg_divide_num_lx[3:0] = 0x00
    ScalerSetByte(PB1_9B_FLD_L2_27, 0x51);
    ScalerSetByte(PB1_9C_FLD_L2_28, 0x00);

    // [7:3] reg_cp_time = 0.64us x ( 0x0E + 1) = 9.6us
    ScalerSetBit(PB1_BD_FLD_L2_59, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));

    // [4:0] reg_adp_time = 0.64us x ( 0x1E + 1) = 19.84us
    ScalerSetBit(PB1_96_FLD_L2_22, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1));

    // [5:3] reg_calib_time = 0.64us x ( 0x07 + 1) = 5.12us
    ScalerSetBit(PB1_93_FLD_L2_19, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // [5] reg_timer_5 = 1.28us x ( 0x01 + 1) = 2.56us
    // [4:0] reg_timer_4 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(PB1_A0_FLD_L2_30, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4:0] reg_timer_6 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(PB1_A1_FLD_L2_31, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4:0] reg_slope_icp_offset_lx[4:0] = 5'b0000
    ScalerSetBit(PB1_A5_FLD_L2_35, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [1:0] reg_slope_icp_offset_lx[9:5] = 5'b0001
    // [7:5] reg_slope_icp_offset_lx[9:5] = 5'b0001
    ScalerSetBit(PB1_A6_FLD_L2_36, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB1_A5_FLD_L2_35, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // [6:2] reg_slope_icp_offset_lx[14:10] = 5'b0001
    ScalerSetBit(PB1_A6_FLD_L2_36, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT2);

    // [3:0] reg_slope_icp_offset_lx[19:15] = 5'b0010
    // [7] reg_slope_icp_offset_lx[19:15] = 5'b0010
    ScalerSetBit(PB1_A7_FLD_L2_37, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_A6_FLD_L2_36, ~_BIT7, 0x00);

    // [1] reg_slope_icp_offset_lx[24:20] = 5'b0010
    // [7:4] reg_slope_icp_offset_lx[24:20] = 5'b0010
    ScalerSetBit(PB1_A9_FLD_L2_39, ~_BIT1, 0x00);
    ScalerSetBit(PB1_A7_FLD_L2_37, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

    // [5:0] reg_cdr_r_lx = 6'b000000
    ScalerSetBit(PB1_AB_FLD_L2_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [1:0] reg_ic_sel_lx = 2'b01 --> Icp Select NV
    ScalerSetBit(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);

    // [5] reg_fld_ok_manual_lx = 1'b0
    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);

    // [6] reg_en_clkout_manual = 1'b0
    // [2] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT6 | _BIT2), 0x00);

    // [7] reg_fld_rst_n_lx = 1'b0 -> 1'b1 => Toggle Reset
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 150; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Reload FLD Auto Mode to Manual Mode
    ScalerSetByte(PB1_94_FLD_L2_20, ScalerGetByte(PB1_B2_FLD_L2_48));
    ScalerSetByte(PB1_95_FLD_L2_21, ScalerGetByte(PB1_B3_FLD_L2_49));

#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)
    // [6] reg_en_clkout_manual = 1'b1
    // [2] reg_bypass_clk_rdy = 1'b1
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
#endif
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Flip Config Initial
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1UfpFlipConfigInitial(void)
{
    // [6] reg_jfm_sel_lane = 1'b1 => Lane2
    ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT6, _BIT6);

    // [4] reg_jfm_rxlane_sel = 1'b1 => Lane2
    ScalerSetBit(P7A_92_DPHY_02, ~_BIT4, _BIT4);

    // [0] reg_lane_config_init = 1'b1 => Initial Lane config to Lane2
    ScalerSetBit(PC9_AD_SPPHY_45, ~_BIT0, _BIT0);

    // [0] reg_lane_debug_sel = 1'b1 => Lane2/3
    ScalerSetBit(PC9_A7_SPPHY_39, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : USB3 PHY Rate change Initial Setting
// Input Value  : PHY Rate
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1UfpPhyRateChangeSetting_EXINT3(EnumUsbLinkPhyRate enumUsbLinkPhyRate)
{
    if(enumUsbLinkPhyRate == _USB_LINK_PHY_RATE_10G)
    {
        if(ScalerGetBit_EXINT3(PB2_01_RX_TOP_01, _BIT1) == _BIT1)
        {
        }

        if(ScalerGetBit_EXINT3(PB2_01_RX_TOP_01, _BIT3) == _BIT3)
        {
        }
    }
    else if(enumUsbLinkPhyRate == _USB_LINK_PHY_RATE_5G)
    {
        if(ScalerGetBit_EXINT3(PB2_01_RX_TOP_01, _BIT1) == _BIT1)
        {
        }

        if(ScalerGetBit_EXINT3(PB2_01_RX_TOP_01, _BIT3) == _BIT3)
        {
        }
    }
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1Disable(bit bAttach, EnumTypeCOrientation enumTypeCOrientation, EnumTypeCPinCfgType enumTypeCPinCfgType)
{
    ScalerUsb3RetimerUfpPhy1PhyDisable(bAttach, enumTypeCOrientation, enumTypeCPinCfgType);
    ScalerUsb3RetimerUfpPhy1IrqDisable();
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1PhyDisable(bit bAttach, EnumTypeCOrientation enumTypeCOrientation, EnumTypeCPinCfgType enumTypeCPinCfgType)
{
    // [7] reg_en_jfm = 1'b0
    ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT7, 0x00);

    // [7] reg_txcmu_en = 1'b0
    ScalerSetBit(PB2_57_TX_CMU_00, ~_BIT7, 0x00);

    // [7] reg_txcmu_ldo_en = 1'b0
    ScalerSetBit(PB2_5C_TX_CMU_05, ~_BIT7, 0x00);

    if((bAttach == _FALSE) || ((bAttach == _TRUE) && (enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_NONE)))
    {
        // Disable UFP1 APHY
        // [7:4] reg_lane_en = 4'b0000
        // [3:0] reg_cdr_en = 4'b0000
        ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE0);
        ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE1);
        ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE2);
        ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE3);

        // [7:6] reg_en_oobs = 2'b00
        ScalerSetBit(PB2_1A_OOBS_00, ~(_BIT7 | _BIT6), 0x00);
    }
    else if((bAttach == _TRUE) && (enumTypeCPinCfgType == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Disable UFP1 APHY
            // [5:4] reg_lane_en = 4'bXX00
            // [1:0] reg_cdr_en = 4'bXX00
            ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE1);

            // [6] reg_en_oobs = 2'bX0
            ScalerSetBit(PB2_1A_OOBS_00, ~_BIT6, 0x00);
        }
        else if(enumTypeCOrientation == _TYPE_C_ORIENTATION_FLIP)
        {
            // Disable UFP1 APHY
            // [7:6] reg_lane_en = 4'b00XX
            // [3:2] reg_cdr_en = 4'b00XX
            ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx1LanePower(_DISABLE, _GDI_PHY_LANE3);

            // [7] reg_en_oobs = 2'b0X
            ScalerSetBit(PB2_1A_OOBS_00, ~_BIT7, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : USB3 Rx1 Retimer UFP PHY Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerUfpPhy1IrqDisable(void)
{
}

#endif // End of #if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
