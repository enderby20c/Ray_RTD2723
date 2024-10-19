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
// ID Code      : RL6952_Series_Usb3RetimerPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_USB3RETIMERPHY__

#include "ScalerFunctionInclude.h"
#include "Usb3RetimerPhy/ScalerUsb3RetimerPhy.h"

#if(_USB3_RETIMER_PHY_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bUsb3RetimerPhyCtsSetPhy = _OFF;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : USB3 Power Switch Initial
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyPowerSwitchInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    ScalerUsb3RetimerPhyKModeInitialSetting(enumTypeCPcbPort);

    // UFPRX_K_OFFSET
    ScalerUsb3RetimerPhyUfpRxKOffset(enumTypeCPcbPort);

    // UFPRX_K_OOBS
    ScalerUsb3RetimerPhyUfpRxKOobs(enumTypeCPcbPort);

    // DFPRX_K_OFFSET
    ScalerUsb3RetimerPhyDfpRxKOffset(enumTypeCPcbPort);

    // DFPRX_K_OOBS
    ScalerUsb3RetimerPhyDfpRxKOobs(enumTypeCPcbPort);

    ScalerUsb3RetimerPhyKModeEndSetting(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : USB3 Set KMode Finish
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhySetKModeFinish(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            SET_USB3_RETIMER_UFP_PHY0_KMODE_FINISH();

#endif
            break;

        case _RX1:

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            SET_USB3_RETIMER_UFP_PHY1_KMODE_FINISH();

#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Get KMode Finish
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
bit ScalerUsb3RetimerPhyGetKModeFinish(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            return GET_USB3_RETIMER_UFP_PHY0_KMODE_FINISH();

#endif
            break;

        case _RX1:

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            return GET_USB3_RETIMER_UFP_PHY1_KMODE_FINISH();

#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : USB3 Clear KMode Finish
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyClearKModeFinish(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            CLR_USB3_RETIMER_UFP_PHY0_KMODE_FINISH();

#endif
            break;

        case _RX1:

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            CLR_USB3_RETIMER_UFP_PHY1_KMODE_FINISH();

#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 KMode Initial Setting
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyKModeInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy0KModeInitialSetting();

#endif
            break;

        case _RX1:

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy1KModeInitialSetting();

#endif
            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }

    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerDfpPhy0KModeInitialSetting();

#endif
            break;

        case _RX1:

            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 KMode End Setting
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyKModeEndSetting(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy0KModeEndSetting();

#endif
            break;

        case _RX1:

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy1KModeEndSetting();

#endif
            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }

    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerDfpPhy0KModeEndSetting();

#endif
            break;

        case _RX1:

            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 UfpRx KOobs
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyUfpRxKOobs(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy0UfpRxKOobs();

#endif
            break;

        case _RX1:

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy1UfpRxKOobs();

#endif
            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 UfpRx KOffset
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyUfpRxKOffset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy0UfpRxKOffset(_USB_LINK_KMODE_5G);
            ScalerUsb3RetimerUfpPhy0UfpRxKOffset(_USB_LINK_KMODE_10G);

#endif
            break;

        case _RX1:

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            ScalerUsb3RetimerUfpPhy1UfpRxKOffset(_USB_LINK_KMODE_5G);
            ScalerUsb3RetimerUfpPhy1UfpRxKOffset(_USB_LINK_KMODE_10G);

#endif
            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Retimer Ufp Phy Jfm Initial Setting
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyUfpJfmInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort)
{
    ScalerUsb3RetimerPhyUfpJfmMuxSel(enumTypeCPcbPort);

    // [5] reg_shift_inv = 1'b1
    ScalerSetBit(PEC_10_JCDR_00, ~_BIT5, _BIT5);

    // [4] reg_rst_mode = 1'b0 => keep ST1/ST2
    ScalerSetBit(PEC_10_JCDR_00, ~_BIT4, 0x00);

    // [6:5] reg_kc_switch_diff = 2'b01 => 1/256
    ScalerSetBit(PEC_11_JCDR_01, ~(_BIT6 | _BIT5), _BIT5);

    // [5:0] reg_bbw_kp = 0x08
    ScalerSetBit(PEC_13_JCDR_03, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // [7:6] reg_kp2 = 2'b00
    ScalerSetBit(PEC_14_JCDR_04, ~(_BIT7 | _BIT6), 0x00);

    // [5:0] reg_kp = 0x6
    ScalerSetBit(PEC_14_JCDR_04, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // [7:6] reg_bbw_kp2 = 2'b00
    ScalerSetBit(PEC_15_JCDR_05, ~(_BIT7 | _BIT6), 0x00);

    // [5:3] reg_bbw_ki = 3'b010 => 1/256
    ScalerSetBit(PEC_15_JCDR_05, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);

    // [2:0] reg_ki = 3'b010 => 1/256
    ScalerSetBit(PEC_15_JCDR_05, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // [5:3] reg_kc_init = 3'b001 => 1/16384
    ScalerSetBit(PEC_18_JCDR_08, ~(_BIT5 | _BIT4 | _BIT3), _BIT3);

    // [2:0] reg_kc = 3'b101 => 1/1024
    ScalerSetBit(PEC_18_JCDR_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // [6] reg_acc3_init_sel = 1'b1 => ACC3 slow to initial
    // [4] reg_acc2_init_sel = 1'b0 => ACC2 reset
    ScalerSetBit(PEC_1F_JCDR_15, ~(_BIT6 | _BIT4), _BIT6);

    // [7:0] reg_ssc_period_timer = 0x94 => (256 x (1 / 1.25G) x 148) = 30.3K SSC Period
    ScalerSetByte(PEC_2A_JCDR_26, 0x94);

#if(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _DFP_RX_CMU)

    // [2] reg_jfm_ufp_data_div_en = 1'b1
    // [6] reg_pow_jgm = 1'b1
    ScalerSetBit(PEC_00_RX_JFM_00, ~_BIT6, _BIT6);
    ScalerSetBit(PEC_00_RX_JFM_00, ~_BIT2, _BIT2);

    // Delay Time us [100,x] Waiting for Clk Stable
    DELAY_XUS(100);

    // [4] reg_rxcmu_clock_stable = 1'b1
    ScalerSetBit(PEC_00_RX_JFM_00, ~_BIT4, _BIT4);

    // Delay Time us [10,x] Waiting for Clk Stable
    DELAY_10US();

    // [7] reg_en_jfm = 1'b1
    ScalerSetBit(PEC_00_RX_JFM_00, ~_BIT7, _BIT7);

    // [7] reg_cmu_control_auto = 1'b1 => HW Mode
    ScalerSetBit(PEC_1A_JCDR_10, ~_BIT7, _BIT7);

#elif(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _UFP_JFM_CMU)

    // [7] reg_cmu_en_rxcmu = 1'b1
    // [6] reg_cmu_ldo_en_rxcmu = 1'b1
    // [5] reg_pow_jgm = 1'b1
    ScalerSetBit(PEC_00_RX_JFM_00, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [100,x] Waiting for Clk Stable
    DELAY_XUS(100);

    // [2] reg_rxcmu_clock_stable = 1'b1
    ScalerSetBit(PEC_00_RX_JFM_00, ~_BIT2, _BIT2);

    // Delay Time us [10,x] Waiting for Clk Stable
    DELAY_10US();

    // [3] reg_en_jfm = 1'b1
    // [1] reg_ck_sys_en_rxcmu = 1'b1
    ScalerSetBit(PEC_00_RX_JFM_00, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));

    // [4] reg_localbias_en_rxcmu = 1'b1
    // [2] reg_ck_250m_en_rxcmu = 1'b1
    ScalerSetBit(PEC_01_RX_JFM_01, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

    // [2:0] reg_lcvco_ib_rxcmu = 3'b001 => ib x 9
    ScalerSetBit(PEC_02_RX_JFM_02, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [6:0] reg_cmu_cp_i_rxcmu = 7'b0101111
    ScalerSetBit(PEC_05_RX_JFM_05, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_vc_sel_rxcmu = 4'b0101 => 0.7V
    ScalerSetBit(PEC_07_RX_JFM_07, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // [3:0] reg_cmu_r1_rxcmu = 4'b0111
    ScalerSetBit(PEC_08_RX_JFM_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [3:2] reg_band_out_mode = 2'b01
    ScalerSetBit(PEC_40_FLD_00, ~(_BIT3 | _BIT2), _BIT2);

    // [2] reg_auto_mode = 1'b1 => Auto Mode
    ScalerSetBit(PEC_53_FLD_19, ~_BIT2, _BIT2);

    // [11:0] reg_lock_up_limit = 0x075D => FLD_cnt = (27) x 500M x 2 / 14.318M = 1885 = 0x75D
    ScalerSetByte(PEC_57_FLD_23, 0x5D);
    ScalerSetByte(PEC_58_FLD_24, 0x07);

    // [11:0] reg_lock_dn_limit = 0x075D => FLD_cnt = (27) x 500M x 2 / 14.318M = 1885 = 0x75D
    ScalerSetByte(PEC_59_FLD_25, 0x5D);
    ScalerSetByte(PEC_5A_FLD_26, 0x07);

    // [11:0] reg_divide_num [11:0] = 0x01B => divide_num = 27
    ScalerSetByte(PEC_5B_FLD_27, 0x1B);
    ScalerSetByte(PEC_5C_FLD_28, 0x00);

    // [7:3] reg_cp_time = 0.64us x ( 0x0E + 1) = 9.6us
    ScalerSetBit(PEC_7B_FLD_59, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));

    // [4:0] reg_adp_time = 0.64us x ( 0x1E + 1) = 19.84us
    ScalerSetBit(PEC_56_FLD_22, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1));

    // [5:3] reg_calib_time = 0.64us x ( 0x07 + 1) = 5.12us
    ScalerSetBit(PEC_53_FLD_19, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // [5] reg_timer_5 = 1.28us x ( 0x01 + 1) = 2.56us
    // [4:0] reg_timer_4 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(PEC_5E_FLD_30, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4:0] reg_timer_6 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(PEC_5F_FLD_31, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_cdr_cp[19:16] = 4'b1111 -> 22.5uA
    ScalerSetBit(PEC_62_FLD_34, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_cdr_cp[15:12] = 4'b1110 -> 19.5uA
    // [3:0] reg_cdr_cp[11:8] = 4'b1110 -> 19.5uA
    ScalerSetByte(PEC_61_FLD_33, 0xEE);

    // [7:4] reg_cdr_cp[7:4] = 4'b1110 -> 19.5uA
    // [3:0] reg_cdr_cp[3:0] = 4'b1110 -> 19.5uA
    ScalerSetByte(PEC_60_FLD_32, 0xEE);

    // [1] reg_ssc_en = 1'b0 => JFM SSC Off
    ScalerSetBit(PEC_80_SSC_00, ~_BIT1, 0x00);

    // [8:0] reg_ssc_n_code = 0x159 => (10G/2/14.31818M) - 4 = 345.2063936
    ScalerSetByte(PEC_83_SSC_03, 0x01);
    ScalerSetByte(PEC_82_SSC_02, 0x59);

    // [12:0] reg_ssc_f_code = 0x69A => 2^13 x 0.20639355 = 1690.xxxxx => 1690 = 0x69A
    ScalerSetByte(PEC_85_SSC_05, 0x06);
    ScalerSetByte(PEC_84_SSC_04, 0x9A);

    // [7] reg_fld_rst_n = 1'b0 -> 1'b1 => Toggle fld_rst
    ScalerSetBit(PEC_40_FLD_00, ~_BIT7, 0x00);
    ScalerSetBit(PEC_40_FLD_00, ~_BIT7, _BIT7);

    // Delay Time us [0,400] Waiting for Polling FLD FSM
    for(pData[0] = 0; pData[0] <= 40; pData[0]++)
    {
        DELAY_10US();

        if((ScalerGetBit(PEC_6F_FLD_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3)) ||
           (ScalerGetBit(PEC_6F_FLD_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4)))
        {
            break;
        }
    }

    // Reload FLD Auto Mode to Manual Mode
    ScalerSetByte(PEC_54_FLD_20, ScalerGetByte(PEC_70_FLD_48));
    ScalerSetByte(PEC_55_FLD_21, ScalerGetByte(PEC_71_FLD_49));

#endif
}

//--------------------------------------------------
// Description  : USB3 Retimer Ufp Phy Jfm Mux Sel
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyUfpJfmMuxSel(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2UfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            // [7] reg_en_jfm = 1'b1
            ScalerSetBit(P29_27_RX_CDR_07, ~_BIT7, _BIT7);

            // [6] reg_jfm_sel_ctrl_ufp0_ufp1 = 1'b0 => Ufp0
            ScalerSetBit(PEC_13_JCDR_03, ~_BIT6, 0x00);

#if(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _DFP_RX_CMU)

            // [5] reg_en_jfm_up = 1'b0 => Dn Side For D0/D1 Port
            ScalerSetBit(P29_27_RX_CDR_07, ~_BIT5, 0x00);

            // [1] reg_jfm_ufp0_ufp1_data_sel = 1'b0 => Select Ufp0
            ScalerSetBit(PEC_00_RX_JFM_00, ~_BIT1, 0x00);

#elif(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _UFP_JFM_CMU)

            // [5] reg_en_jfm_up = 1'b1 => Up Side For D0 Port
            ScalerSetBit(P29_27_RX_CDR_07, ~_BIT5, _BIT5);

            // [7] reg_jfm_sel_data_ufp0_ufp1 = 1'b0 => Select Ufp0
            ScalerSetBit(PEC_01_RX_JFM_01, ~_BIT7, 0x00);

#endif
#endif

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            // [7] reg_en_jfm = 1'b0
            ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT7, 0x00);

#if(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _DFP_RX_CMU)

            // [5] reg_en_jfm_up = 1'b1 => Up Side For D0/D1 Port
            ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT5, _BIT5);

#elif(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _UFP_JFM_CMU)

            // [5] reg_en_jfm_up = 1'b1 => Up Side For D0 Port
            ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT5, _BIT5);

#endif
#endif

            break;

        case _RX1:

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)

            // [7] reg_en_jfm = 1'b0
            ScalerSetBit(P29_27_RX_CDR_07, ~_BIT7, 0x00);

            // [6] reg_jfm_sel_ctrl_ufp0_ufp1 = 1'b1 => Ufp1
            ScalerSetBit(PEC_13_JCDR_03, ~_BIT6, _BIT6);

#if(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _DFP_RX_CMU)

            // [5] reg_en_jfm_up = 1'b1 => Up Side For D1 Port
            ScalerSetBit(P29_27_RX_CDR_07, ~_BIT5, _BIT5);

            // [1] reg_jfm_ufp0_ufp1_data_sel = 1'b1 => Select Ufp1
            ScalerSetBit(PEC_00_RX_JFM_00, ~_BIT1, _BIT1);

#elif(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _UFP_JFM_CMU)

            // [5] reg_en_jfm_up = 1'b0 => Down Side For D1 Port
            ScalerSetBit(P29_27_RX_CDR_07, ~_BIT5, 0x00);

            // [7] reg_jfm_sel_data_ufp0_ufp1 = 1'b1 => Select Ufp1
            ScalerSetBit(PEC_01_RX_JFM_01, ~_BIT7, _BIT7);

#endif
#endif

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)

            // [7] reg_en_jfm = 1'b1
            ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT7, _BIT7);

#if(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _DFP_RX_CMU)

            // [5] reg_en_jfm_up = 1'b0 => Down Side For D1 Port
            ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT5, 0x00);

#elif(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _UFP_JFM_CMU)

            // [5] reg_en_jfm_up = 1'b0 => Down Side For D1 Port
            ScalerSetBit(PB2_27_RX_CDR_07, ~_BIT5, 0x00);

#endif
#endif

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Retimer Ufp Phy Jfm Enable/Disable
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyUfpJfmDisable(void)
{
#if(_HW_USB3_REPEATER_UFP_JFM_CLK_SEL == _DFP_RX_CMU)
    // [7] reg_en_jfm = 1'b1
    // [6] reg_pow_jgm = 1'b1
    // [4] reg_rxcmu_clock_stable = 1'b1
    ScalerSetBit(PEC_00_RX_JFM_00, ~(_BIT7 | _BIT6 | _BIT4), 0x00);
#endif
}

//--------------------------------------------------
// Description  : USB3 DfpRx KOobs
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyDfpRxKOobs(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerDfpPhy0DfpRxKOobs(_USB_LINK_KMODE_5G);
            ScalerUsb3RetimerDfpPhy0DfpRxKOobs(_USB_LINK_KMODE_10G);

#endif
            break;

        case _RX1:

            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 DfpRx KOffset
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhyDfpRxKOffset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(ScalerUsb3RepeaterPhyDx2DfpPhyxMapping(enumTypeCPcbPort))
    {
        case _RX0:

#if(_USB3_RETIMER_DFP_PHY0_SUPPORT == _ON)

            ScalerUsb3RetimerDfpPhy0DfpRxKOffset(_USB_LINK_KMODE_5G);
            ScalerUsb3RetimerDfpPhy0DfpRxKOffset(_USB_LINK_KMODE_10G);

#endif
            break;

        case _RX1:

            break;

        case _RX_MAP_NONE:

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : USB3 Set CTS Ctrl
// Input Value  : _ON or _OFF
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerPhySetCtsCtrl(bit bOn)
{
    SET_USB3_CTS_SET_PHY(bOn);
}

//--------------------------------------------------
// Description  : USB3 Get CTS Ctrl
// Input Value  : void
// Output Value : _ON or _OFF
//--------------------------------------------------
bit ScalerUsb3RetimerPhyGetCtsCtrl(void)
{
    return GET_USB3_CTS_SET_PHY();
}

#endif

