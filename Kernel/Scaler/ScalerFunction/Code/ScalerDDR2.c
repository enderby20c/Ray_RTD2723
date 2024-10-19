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
// ID Code      : ScalerDDR2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDR2__

#include "ScalerFunctionInclude.h"
#include "DDR2/ScalerDDR2.h"


#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
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
// Description  : DC Phy initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2DCPHYInitial(void)
{
    Scaler32SetDWord(PB08002_40_DPI_CTRL_2, 0x901A3000); // [28]set_reg_valid_ mode= 0x1 : auto
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT1 | _BIT0), 0x00000002); // [1:0]fw_set_mode = 'b10 (immediately)
    //==============================
    // DLL Setting
    //==============================
    //---Begin IO OCD/ODT.----//
    Scaler32SetDWord(PB08001_30_PAD_CTRL_PROG, 0x08000000); // dzq_auto_up & dzq_ref_up = 1
    Scaler32SetDWord(PB08001_F8_PAD_BUS_1, 0x00009400); // PB08001_F8_PAD_BUS_1[6]: zq pad PD =1
    Scaler32SetDWord(PB08001_F4_PAD_BUS_0, 0x9BF80000);
    // [7]vref_range_0/1 = 'b1; [6:1]vref_s_0/1 = 0x0F (50%); [0]Vref_PD = 'b0 : internal
    Scaler32SetDWord(PB08001_FC_PAD_BUS_2, 0x9E9E9E9E);
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0xC0000003); // fw_set_wr_dly =1

    // OCD : SET0 65/47/47/40/18
    Scaler32SetDWord(PB08001_90_OCDP0_SET0, 0x15151B3B);
    Scaler32SetDWord(PB08001_94_OCDP1_SET0, 0x26262610);
    Scaler32SetDWord(PB08001_98_OCDN0_SET0, 0x14141D33);
    Scaler32SetDWord(PB08001_9C_OCDN1_SET0, 0x2626260E);
    Scaler32SetDWord(PB08001_B0_OCDP0_SET1, 0x15151B3B);
    Scaler32SetDWord(PB08001_B4_OCDP1_SET1, 0x26262610);
    Scaler32SetDWord(PB08001_B8_OCDN0_SET1, 0x14141D33);
    Scaler32SetDWord(PB08001_BC_OCDN1_SET1, 0x2626260E);

#ifdef _LQFP156_2D_DDRX1_LVDS_PIN_28
    Scaler32SetDWord(PB08001_94_OCDP1_SET0, 0x2626260E);
    Scaler32SetDWord(PB08001_9C_OCDN1_SET0, 0x2626260C);
    Scaler32SetDWord(PB08001_B4_OCDP1_SET1, 0x2626260E);
    Scaler32SetDWord(PB08001_BC_OCDN1_SET1, 0x2626260C);
#endif

    // CK OCD = 18
    Scaler32SetDWord(PB08001_F0_CK_OCD_SEL, 0x00000000);
    // 1T CA (CS/CKE)
    Scaler32SetDWord(PB08001_E8_CKE_OCD_SEL, 0x00001111); // CKE OCD = 40
    Scaler32SetDWord(PB08001_EC_ADR_OCD_SEL, 0x11001100); // CS OCD = 40
    // 2T CA OCD = 47
    Scaler32SetDWord(PB08002_04_OCD_SEL_0, 0x22222222); // A0,A1,A2,A3
    Scaler32SetDWord(PB08002_08_OCD_SEL_1, 0x22222222); // A4,A5,A6,A7
    Scaler32SetDWord(PB08002_0C_OCD_SEL_2, 0x22222222); // A8,A9,A10,A11
    Scaler32SetDWord(PB08002_10_OCD_SEL_3, 0x22222222); // A12,A13,A14,A15
    Scaler32SetDWord(PB08002_14_OCD_SEL_4, 0x22222222); // A16,BA0
    Scaler32SetDWord(PB08002_18_OCD_SEL_5, 0x22222222); // BA1,BA2,RASN,CASN
    Scaler32SetDWord(PB08002_1C_OCD_SEL_6, 0x22222222); // WEN,ODT,RSTN,PAR
    Scaler32SetDWord(PB08002_20_OCD_SEL_7, 0x22222222); // PAR_1, ACTN, BG0, TEN
    Scaler32SetDWord(PB08002_24_OCD_SEL_8, 0x22222222); // ALERT, ALERT_1,
    // DQS OCD = 47
    Scaler32SetDWord(PB08001_E0_DQS_OCD_SEL, 0x33333333);
    Scaler32SetDWord(PB08001_E4_DQS_OCD_SEL, 0x33333333);
    // DQ 216pin : OCD = 65 156pin : OCD = 75
    Scaler32SetDWord(PB08001_C8_DQ_OCD_SEL, 0x00004444);
    Scaler32SetDWord(PB08001_CC_DQ_OCD_SEL, 0x00004444);
    Scaler32SetDWord(PB08003_28_DQ_OCD_SEL_2, 0x44444444);
    Scaler32SetDWord(PB08003_2C_DQ_OCD_SEL_2, 0x44444444);

    // ODT :  SET0 300/150/120
    Scaler32SetDWord(PB08001_80_ODT_TTCP0_SET0, 0x00030709);
    Scaler32SetDWord(PB08001_88_ODT_TTCN0_SET0, 0x00030608);
    Scaler32SetDWord(PB08001_A0_ODT_TTCP0_SET1, 0x00030709);
    Scaler32SetDWord(PB08001_A8_ODT_TTCN0_SET1, 0x00030608);
    // DQS PUPD3
    Scaler32SetDWord(PB08001_D0_DQS_P_ODT_SEL, 0x00000011);
    Scaler32SetDWord(PB08001_D4_DQS_P_ODT_SEL, 0x00000011);
    Scaler32SetDWord(PB08001_D8_DQS_N_ODT_SEL, 0x00001100);
    Scaler32SetDWord(PB08001_DC_DQS_N_ODT_SEL, 0x00001100);
    // DQ
    Scaler32SetDWord(PB08001_C0_DQ_ODT_SEL, 0x00002222);
    Scaler32SetDWord(PB08001_C4_DQ_ODT_SEL, 0x00002222);
    //---end IO OCD/ODT.----

    // DQ 3-point Calibration
    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E0C26); // [5:4]cal_set_mode = 'b10;[1:0]fw_set_mode = 'b10 (both immediately)
    Scaler32SetDWord(PB08004_20_DEL_POS_SEL, 0x22222222); // Left sampling point of 3-point calibration
    Scaler32SetDWord(PB08004_24_DEL_POS_SEL, 0x22222222);
    Scaler32SetDWord(PB08004_30_DEL_NEG_SEL, 0x22222222); // Right sampling point of 3-point calibration
    Scaler32SetDWord(PB08004_34_DEL_NEG_SEL, 0x22222222);
    Scaler32SetDWord(PB08006_20_DEL_POS_SEL, 0x22222222); // Left sampling point of 3-point calibration
    Scaler32SetDWord(PB08006_24_DEL_POS_SEL, 0x22222222);
    Scaler32SetDWord(PB08006_30_DEL_NEG_SEL, 0x22222222); // Right sampling point of 3-point calibration
    Scaler32SetDWord(PB08006_34_DEL_NEG_SEL, 0x22222222);
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0xC0000030); // fw_set_cal_rang

    //------------------------------
    // Tx/Rx DQ delay tap
    //------------------------------
    // Tx delay
    Scaler32SetDWord(PB08001_00_ADR_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08001_04_ADR_DLY_1, 0x88888888);
    Scaler32SetDWord(PB08001_08_ADR_DLY_2, 0x88888888);
    Scaler32SetDWord(PB08001_0C_CMD_DLY_0, 0x20888888);
    Scaler32SetDWord(PB08001_10_CMD_DLY_1, 0x88888888);

    // odt_en dealy
    Scaler32SetDWord(PB08004_18_READ_CTRL_6_0, 0x00000018);
    Scaler32SetDWord(PB08004_1C_READ_CTRL_6_1, 0x0000003C);

    Scaler32SetDWord(PB08004_80_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08004_84_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08004_88_DQ_DLY_1, 0x00008888);
    Scaler32SetDWord(PB08004_8C_DQ_DLY_1, 0x00008888);

    // odt_en dealy
    Scaler32SetDWord(PB08006_18_READ_CTRL_6_0, 0x0000007E);
    Scaler32SetDWord(PB08006_1C_READ_CTRL_6_1, 0x000000FF);

    Scaler32SetDWord(PB08006_80_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08006_84_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08006_88_DQ_DLY_1, 0x00008888);
    Scaler32SetDWord(PB08006_8C_DQ_DLY_1, 0x00008888);

    // RTL: 0x08000000 // [27]: CS output delay enable
    Scaler32SetDWord(PB08001_54_CMD_ADR_PH, 0x00000000);
    // Read FIFO latency = 7T; rd_dly_follow_dq0 =0
    Scaler32SetDWord(PB08001_70_READ_CTRL_1, 0x00000004); // RTL: 0x00000004 // tm_rd_fifo

    // Read dqs_en latency = F : FRC Mode
    Scaler32SetDWord(PB08005_F8_READ_CTRL_0, 0x0C000003); // Default = 3
    Scaler32SetDWord(PB08005_FC_READ_CTRL_0, 0x0C000003); //
    Scaler32SetDWord(PB08007_F8_READ_CTRL_0, 0x0C000003); //
    Scaler32SetDWord(PB08007_FC_READ_CTRL_0, 0x0C000003); //

    // [21]= 0x1 : repeat the first data (WL + 2);[20]=0x0 initial level of write data
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT21 | _BIT20), 0x00200000);
    // [15:12] = 0x1 : DQ OE pre 0.5T open
    Scaler32SetBit(PB08005_18_DQ_IO_CTL_2, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12), 0x00001000);
    Scaler32SetBit(PB08007_18_DQ_IO_CTL_2, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12), 0x00001000);

#if(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_1200M)
    // DDR data rate: 1333 MHz
    // RDQ delay tap - DQS_IN raising edge delay chain control
    Scaler32SetDWord(PB08004_40_DQS_IN_DLY_0, 0x11121111);
    Scaler32SetDWord(PB08004_48_DQS_IN_DLY_1, 0x11111111);
    Scaler32SetDWord(PB08004_44_DQS_IN_DLY_0, 0x11120F11);
    Scaler32SetDWord(PB08004_4C_DQS_IN_DLY_1, 0x10121112);
    Scaler32SetDWord(PB08006_40_DQS_IN_DLY_0, 0x10101010);
    Scaler32SetDWord(PB08006_48_DQS_IN_DLY_1, 0x10101010);
    Scaler32SetDWord(PB08006_44_DQS_IN_DLY_0, 0x0F120F10);
    Scaler32SetDWord(PB08006_4C_DQS_IN_DLY_1, 0x10101110);

    // RDQ delay tap - DQS_IN falling edge delay chain control
    Scaler32SetDWord(PB08004_58_DQS_IN_DLY_2, 0x12121212);
    Scaler32SetDWord(PB08004_60_DQS_IN_DLY_3, 0x11111211);
    Scaler32SetDWord(PB08004_5C_DQS_IN_DLY_2, 0x12121212);
    Scaler32SetDWord(PB08004_64_DQS_IN_DLY_3, 0x12121212);
    Scaler32SetDWord(PB08006_58_DQS_IN_DLY_2, 0x10101011);
    Scaler32SetDWord(PB08006_60_DQS_IN_DLY_3, 0x10101010);
    Scaler32SetDWord(PB08006_5C_DQS_IN_DLY_2, 0x11111111);
    Scaler32SetDWord(PB08006_64_DQS_IN_DLY_3, 0x11101110);

#elif(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_1066M)
    // DDR data rate: 1200 MHz
    // RDQ delay tap - DQS_IN raising edge delay chain control
    Scaler32SetDWord(PB08004_40_DQS_IN_DLY_0, 0x11111011);
    Scaler32SetDWord(PB08004_48_DQS_IN_DLY_1, 0x11101111);
    Scaler32SetDWord(PB08004_44_DQS_IN_DLY_0, 0x12121112);
    Scaler32SetDWord(PB08004_4C_DQS_IN_DLY_1, 0x12121212);
    Scaler32SetDWord(PB08006_40_DQS_IN_DLY_0, 0x0F0F0F10);
    Scaler32SetDWord(PB08006_48_DQS_IN_DLY_1, 0x100F100F);
    Scaler32SetDWord(PB08006_44_DQS_IN_DLY_0, 0x10110F11);
    Scaler32SetDWord(PB08006_4C_DQS_IN_DLY_1, 0x11101010);

    // RDQ delay tap - DQS_IN falling edge delay chain control
    Scaler32SetDWord(PB08004_58_DQS_IN_DLY_2, 0x11111011);
    Scaler32SetDWord(PB08004_60_DQS_IN_DLY_3, 0x10101111);
    Scaler32SetDWord(PB08004_5C_DQS_IN_DLY_2, 0x12121111);
    Scaler32SetDWord(PB08004_64_DQS_IN_DLY_3, 0x12121212);
    Scaler32SetDWord(PB08006_58_DQS_IN_DLY_2, 0x0F100F10);
    Scaler32SetDWord(PB08006_60_DQS_IN_DLY_3, 0x100F100F);
    Scaler32SetDWord(PB08006_5C_DQS_IN_DLY_2, 0x10101010);
    Scaler32SetDWord(PB08006_64_DQS_IN_DLY_3, 0x1110100F);

#elif(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_800M)
    // DDR data rate: 1066 MHz
    // RDQ delay tap - DQS_IN raising edge delay chain control
    Scaler32SetDWord(PB08004_40_DQS_IN_DLY_0, 0x11111011);
    Scaler32SetDWord(PB08004_48_DQS_IN_DLY_1, 0x11101111);
    Scaler32SetDWord(PB08004_44_DQS_IN_DLY_0, 0x12121112);
    Scaler32SetDWord(PB08004_4C_DQS_IN_DLY_1, 0x12121212);
    Scaler32SetDWord(PB08006_40_DQS_IN_DLY_0, 0x0F0F0F10);
    Scaler32SetDWord(PB08006_48_DQS_IN_DLY_1, 0x100F100F);
    Scaler32SetDWord(PB08006_44_DQS_IN_DLY_0, 0x10110F11);
    Scaler32SetDWord(PB08006_4C_DQS_IN_DLY_1, 0x11101010);

    // RDQ delay tap - DQS_IN falling edge delay chain control
    Scaler32SetDWord(PB08004_58_DQS_IN_DLY_2, 0x11111011);
    Scaler32SetDWord(PB08004_60_DQS_IN_DLY_3, 0x10101111);
    Scaler32SetDWord(PB08004_5C_DQS_IN_DLY_2, 0x12121111);
    Scaler32SetDWord(PB08004_64_DQS_IN_DLY_3, 0x12121212);
    Scaler32SetDWord(PB08006_58_DQS_IN_DLY_2, 0x0F100F10);
    Scaler32SetDWord(PB08006_60_DQS_IN_DLY_3, 0x100F100F);
    Scaler32SetDWord(PB08006_5C_DQS_IN_DLY_2, 0x10101010);
    Scaler32SetDWord(PB08006_64_DQS_IN_DLY_3, 0x1110100F);
#endif // End of #if(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_1200M)

    // Triger all DLL setting
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0xC000000C); // fw_set_rd_dly
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0xC0000030); // fw_set_cal_rang
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0xC0000003); // fw_set_wr_fly
    Scaler32SetBit(PB08002_40_DPI_CTRL_2, ~_BIT28, 0x10000000);
    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E0C04); // [1:0]fw_set_mode = 'b00 (during no read)

#if(_HW_MEMORY_DDR2_GEN_TYPE == _MEMORY_DDR2_GEN_0)
    //==============================
    // DC PHY Setting
    //==============================
    //------------------------------
    // DDR timing setting
    //------------------------------
#if(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_1200M)
    // DDR data rate: 1333 MHz
    Scaler32SetDWord(PB08200_00_TMCTRL0, 0x000D0906);
    Scaler32SetDWord(PB08200_04_TMCTRL1, 0x03080627);
    Scaler32SetDWord(PB08200_0C_TMCTRL3, 0x160A2013);
    Scaler32SetDWord(PB08200_10_TMCTRL4, 0x00000001);
    Scaler32SetDWord(PB08200_14_TMCTRL5, 0x00200400);
    Scaler32SetDWord(PB08200_18_TMCTRL6, 0x00240080);
    if(GET_MEMORY_PIECE() == _MEMORY_2PCS)
    {
        Scaler32SetDWord(PB08200_08_TMCTRL2, 0x0002040A);
        Scaler32SetDWord(PB08200_44_MOD_REG, 0x00420002);  // RL6978 2pcs BL4 BC4
    }
    else
    {
        Scaler32SetDWord(PB08200_08_TMCTRL2, 0x0004060C);
        Scaler32SetDWord(PB08200_44_MOD_REG, 0x00420003);  // RL6978 1pc BL8
    }
    Scaler32SetDWord(PB08200_48_MOD23_REG, 0x00000080); // [7]: High Temperature Self Refresh rate, 0: Disable, 1: Enable.
    Scaler32SetDWord(PB08200_2C_DC_MIS, 0x0006000E); // DDR2 Enable
    Scaler32SetDWord(PB08200_38_DC_MISC, 0x00000000); // Reserved
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x000C0000);
    Scaler32SetDWord(PB08202_90_WEIGHT_BANK, 0x00081428);

#elif(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_1066M)
    // DDR data rate: 1200 MHz
    Scaler32SetDWord(PB08200_00_TMCTRL0, 0x000C0906);
    Scaler32SetDWord(PB08200_04_TMCTRL1, 0x02080620);
    Scaler32SetDWord(PB08200_0C_TMCTRL3, 0x16092010);
    Scaler32SetDWord(PB08200_10_TMCTRL4, 0x00000001);
    Scaler32SetDWord(PB08200_14_TMCTRL5, 0x00200400);
    Scaler32SetDWord(PB08200_18_TMCTRL6, 0x00240080);
    if(GET_MEMORY_PIECE() == _MEMORY_2PCS)
    {
        Scaler32SetDWord(PB08200_08_TMCTRL2, 0x0002040A);
        Scaler32SetDWord(PB08200_44_MOD_REG, 0x00420002);  // RL6978 2pcs BL4 BC4
    }
    else
    {
        Scaler32SetDWord(PB08200_08_TMCTRL2, 0x0004060C);
        Scaler32SetDWord(PB08200_44_MOD_REG, 0x00420003);  // RL6978 1pc BL8
    }
    Scaler32SetDWord(PB08200_48_MOD23_REG, 0x00000080); // MR3,MR2
    Scaler32SetDWord(PB08200_2C_DC_MIS, 0x0006000E); // DDR2 Enable
    Scaler32SetDWord(PB08200_38_DC_MISC, 0x00000000); // Reserved
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x000C0000);
    Scaler32SetDWord(PB08202_90_WEIGHT_BANK, 0x00081228);

#elif(_MEMORY_DATA_RATE_SPEED > _DDR2_DATA_RATE_800M)
    // DDR data rate: 1066 MHz
    Scaler32SetDWord(PB08200_00_TMCTRL0, 0x000C0906);
    Scaler32SetDWord(PB08200_04_TMCTRL1, 0x02080620);
    Scaler32SetDWord(PB08200_0C_TMCTRL3, 0x16092010);
    Scaler32SetDWord(PB08200_10_TMCTRL4, 0x00000001);
    Scaler32SetDWord(PB08200_14_TMCTRL5, 0x00200400);
    Scaler32SetDWord(PB08200_18_TMCTRL6, 0x00240080);
    if(GET_MEMORY_PIECE() == _MEMORY_2PCS)
    {
        Scaler32SetDWord(PB08200_08_TMCTRL2, 0x0002040A);
        Scaler32SetDWord(PB08200_44_MOD_REG, 0x00420002);  // RL6978 2pcs BL4 BC4
    }
    else
    {
        Scaler32SetDWord(PB08200_08_TMCTRL2, 0x0004060C);
        Scaler32SetDWord(PB08200_44_MOD_REG, 0x00420003);  // RL6978 1pc BL8
    }
    Scaler32SetDWord(PB08200_48_MOD23_REG, 0x00000080); // MR3,MR2
    Scaler32SetDWord(PB08200_2C_DC_MIS, 0x0006000E); // DDR2 Enable
    Scaler32SetDWord(PB08200_38_DC_MISC, 0x00000000); // Reserved
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x000C0000);
    Scaler32SetDWord(PB08202_90_WEIGHT_BANK, 0x00081228);

#endif

    //------------------------------
    // Other DDR setting
    //------------------------------
    Scaler32SetDWord(PB08200_50_ERR_STATUS, 0x00000000); // Clear fifo Status
    Scaler32SetDWord(PB08200_4C_RFIFO_CTL, 0x00000030); // rfifo_thred=48
    if(GET_MEMORY_PIECE() == _MEMORY_2PCS)
    {
        Scaler32SetDWord(PB08201_40_DUMMY_REG, 0xB8000048); // RL6978 2pcs BL4 BC4 // [31] reg_pin_mux_ddr2_stack_en [28] reg_bl4
    }
    else
    {
        Scaler32SetDWord(PB08201_40_DUMMY_REG, 0xA8000048); // RL6978 2pcs BL4 BC4 // [31] reg_pin_mux_ddr2_stack_en [28] reg_bl4
    }

    // cmdq-channel fifo Threshold
    Scaler32SetDWord(PB08205_00_FIFO_ARB_0, 0x00000040);
    Scaler32SetDWord(PB08205_74_SCRAMBLE_CTRL, 0x00000002); // [1] seq_mode_sc_sel, Sequencial mode scramble select 0: only block mode data, 1: block, seq data all. (default 1). [0] scramble_en. RL6978 New
    Scaler32SetDWord(PB08205_F8_CS_CTRL, 0x00000000);

    // DQ Sel "1": dq from [15:0]
    Scaler32SetDWord(PB08201_54_CAL_MODE, 0x00000001);

    // Dc_sys2 write qfifo enable; dc_sys2 read/write separate enable
    Scaler32SetDWord(PB08203_98_DC_SYS2_CTRL, 0x00000005);

    // WEIGHT Setting
    Scaler32SetDWord(PB08202_80_WEIGHT_ENABLE, 0x0000001D);
    Scaler32SetDWord(PB08202_88_WEIGHT_DIERECTION, 0x00008200);

    // DC1 init
    Scaler32SetDWord(PB08200_28_DC_MIS2, 0x00000010);  // [4] init (only for DDR2) RL6978.

#endif // End of #if(_HW_MEMORY_DDR2_GEN_TYPE == _MEMORY_DDR2_GEN_0)

}
//--------------------------------------------------
// Description  : DC Sys initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2DCSysInitial(void)
{
#if(_HW_MEMORY_DDR2_GEN_TYPE == _MEMORY_DDR2_GEN_0)

    if(GET_MEMORY_PIECE() == _MEMORY_1PC)
    {
        // 1pc  DDR2. [19] mem_num_0: One-DDR, 1: Two-DDR. [17:16] page_size 00: 512bytes, 01: 1024bytes, 10: 2048bytes, 11: 4096bytes, [8] en_max_bl_max. RL6978
        Scaler32SetDWord(PB08100_04_DC_SYS_MISC, 0x00010000);
        ScalerSetByte(P37_01_MCU_DC_LEN, 0x02);
    }
    else // _MEMORY_2PCS
    {
        // 2pcs DDR2. [19] mem_num_0: One-DDR, 1: Two-DDR. [17:16] page_size 00: 512bytes, 01: 1024bytes, 10: 2048bytes, 11: 4096bytes, [8] en_max_bl_max. RL6978
        Scaler32SetDWord(PB08100_04_DC_SYS_MISC, 0x000A0000);
        ScalerSetByte(P37_01_MCU_DC_LEN, 0x84);
    }

#endif // End of #if(_HW_MEMORY_DDR2_GEN_TYPE == _MEMORY_DDR2_GEN_0)

}

//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2PowerControl(bit bOn)
{
    if(bOn == _ON)
    {
#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
        // Set MPLL CLK
        ScalerPLLSetMPLLFreq((DWORD)_MEMORY_PLL_CLOCK * 1000);
#endif

        // Set Memory Device PLL CLK
        ScalerMemoryDevicePLLSetPLLFreq((DWORD)_MEMORY_DATA_RATE_SPEED * 1000);

        //------------------------------
        // DC Sys & Sys Bridge Reset
        //------------------------------
        ScalerDDR2DCSysSystemBridgeReset();

        //------------------------------
        // System Bridge Initial
        //------------------------------
        ScalerDDR2SystemBridgeInitial();

        //------------------------------
        // DC Sys Initial
        //------------------------------
        ScalerDDR2DCSysInitial();

        //------------------------------
        // DC PHY Initial
        //------------------------------
        ScalerDDR2DCPHYInitial();

#if((_DDR2_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE))
        ScalerDDR2OfflinePhaseCalMCUMode();
#endif
    }
    else
    {
        // Set ICG_clk_en Disable
        Scaler32SetBit(PB08000_04_PLL_CTL0, ~(_BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);

        // Set clk_oe Disable
        Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT18 | _BIT17 | _BIT16), 0x00000000);

        // Reset DDR PLL
        Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);

#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
        // Power Down MPLL
        ScalerPLLMPLLPower(_OFF);
#endif
    }
}

//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2DCSysSystemBridgeReset(void)
{
#if(_HW_MEMORY_DDR2_GEN_TYPE == _MEMORY_DDR2_GEN_0)
    //-----------------------------
    // Reset both DCSys/Sys Bridge
    //-----------------------------
    ScalerSetBit(P33_A0_M_DOMAIN_SB_RESET_A, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    // Delay Time us [5,x] Waiting for DDR3 setting
    DELAY_5US();

    //-----------------------------
    // Release DCSys reset
    //-----------------------------
    ScalerSetBit(P33_A0_M_DOMAIN_SB_RESET_A, ~(_BIT1 | _BIT0), (_BIT0));
    // Delay Time us [5,x] Waiting for DDR3 setting
    DELAY_5US();

    //-----------------------------
    // Release Sys Bridge reset
    //-----------------------------
    ScalerSetBit(P33_A0_M_DOMAIN_SB_RESET_A, ~(_BIT1 | _BIT0), (0x00));
    // Delay Time us [5,x] Waiting for DDR3 setting
    DELAY_5US();
#endif // End of #if(_HW_MEMORY_DDR2_GEN_TYPE == _MEMORY_DDR2_GEN_0)
}

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_MEMORY_DDR2_2PC_SEPARATE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch display client mux for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR2RotationSetClientMux(void)
{
    if(GET_MEMORY_PIECE() == _MEMORY_2PCS)
    {
        switch(GET_ROT_TYPE())
        {
            case _ROT_CW180:
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
            case _ROT_VER_MIRROR:
#endif
                // _ROT_CW180, _ROT_VER_MIRROR: set disp client mux different from cap client
                // M1
                ScalerSetBit(P33_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ~_BIT4, ((ScalerGetBit(P33_B0_M_DOMAIN_CLIENT_MUX_CTRL0, _BIT0) == _BIT0) ? 0x00 : _BIT4));
                // M2
                ScalerSetBit(P33_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ~_BIT5, ((ScalerGetBit(P33_B0_M_DOMAIN_CLIENT_MUX_CTRL0, _BIT1) == _BIT1) ? 0x00 : _BIT5));
                break;

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
            case _ROT_HOR_MIRROR:
#endif
            default:
                // Other cases: set disp client mux as cap client
                // M1
                ScalerSetBit(P33_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ~_BIT4, ((ScalerGetBit(P33_B0_M_DOMAIN_CLIENT_MUX_CTRL0, _BIT0) == _BIT0) ? _BIT4 : 0x00));
                // M2
                ScalerSetBit(P33_B0_M_DOMAIN_CLIENT_MUX_CTRL0, ~_BIT5, ((ScalerGetBit(P33_B0_M_DOMAIN_CLIENT_MUX_CTRL0, _BIT1) == _BIT1) ? _BIT5 : 0x00));
                break;
        }
    }
}
#endif
#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)




