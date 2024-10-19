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
// ID Code      : ScalerDDR1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDR1__

#include "ScalerFunctionInclude.h"
#include "DDR1/ScalerDDR1.h"


#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//! Default DDRPLL Phase
StructDDR1PLLPI g_pstDDR1PLLPHASE[] =
{
    // CLK,  CMD, DQS0, DQS1,  DQ0,  DQ1
    {0x39, 0x40, 0x38, 0x37, 0x48, 0x48},
};

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1PowerControl(bit bOn)
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
        // DC PHY Initial
        //------------------------------
        ScalerDDR1DCPHYInitial();
    }
    else
    {
        // Disable CLK output, Reset PLL, Disable PLL
        ScalerDDR1PLLOutputCtrl(_DISABLE);
        ScalerDDR1PLLCtrl(_DISABLE);

#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
        // Power Down MPLL
        ScalerPLLMPLLPower(_OFF);
#endif
    }
}

//--------------------------------------------------
// Description  : DC Phy initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1DCPHYInitial(void)
{
    ScalerSetByte(P33_A6_M_DOMAIN_DUMMY02, 0x20); // DDR1
    //==============================
    // DLL Setting
    //==============================
    // PHY & MAC Frequency Ratio 1:2
    ScalerSetDWord(P8F_D8_BIST_2TO1_0_D8, 0x00000000);

    // One cycele command output delay, RDQS gen mode: PUPD3, enable 3-point cal, fw_set_mode = 'b10.
    ScalerSetDWord(P8F_7C_DPI_CTRL_0_7C, 0x09770C56);

    // Enable CS Output One cycle Delay and Initial DQS/DQ Mux table
    ScalerSetDWord(P8E_28_WRLVL_CTRL_28, 0x20800FF0);
    ScalerSetDWord(P8E_28_WRLVL_CTRL_28, ((0x20800FF0 & 0xFFFCCCCF) | (~0xFFFCCCCF & ScalerDDR1CalcWrlvlConfig(&(g_pstDDR1PLLPHASE[0])))));

    // Vref PAD Mode
    // ScalerSetDWord(P8F_70_PAD_BUS_0_70, 0x00000002); // if DQS is single end, set DQS SE = 1 for RX ( PAD_BUS_0[1] )
    ScalerSetDWord(P8F_70_PAD_BUS_0_70, 0x00000012); // This Setting is for A version. Need to Change back for B version.

    //------------------------------
    // RDQS Enable
    //------------------------------
    // RDQS enable latency
    ScalerSetDWord(P8E_54_READ_CTRL_0_54, 0x0000000D);
    ScalerSetDWord(P8E_58_READ_CTRL_0_58, 0x0000000D);

    // Apply read delay setting
    ScalerSetDWord(P8F_80_DPI_CTRL_1_80, 0x0000000C);

    //------------------------------
    // Read DQ delay tap
    //------------------------------
    // RDQ delay tap - rising
    ScalerSetDWord(P8E_B8_DQS_IN_DLY_0_B8, 0x13131313); // slice_0: DQ_03~DQ_00
    ScalerSetDWord(P8E_BC_DQS_IN_DLY_0_BC, 0x13131313); // slice_1: DQ_11~DQ_08
    ScalerSetDWord(P8E_C8_DQS_IN_DLY_1_C8, 0x13131313); // slice_0: DQ_07~DQ_04
    ScalerSetDWord(P8E_CC_DQS_IN_DLY_1_CC, 0x13131313); // slice_1: DQ_15~DQ_12
    // RDQ delay tap - falling
    ScalerSetDWord(P8E_D8_DQS_IN_DLY_2_D8, 0x13131313); // slice_0: DQ_03~DQ_00
    ScalerSetDWord(P8E_DC_DQS_IN_DLY_2_DC, 0x13131313); // slice_1: DQ_11~DQ_08
    ScalerSetDWord(P8E_E8_DQS_IN_DLY_3_E8, 0x13131313); // slice_0: DQ_07~DQ_04
    ScalerSetDWord(P8E_EC_DQS_IN_DLY_3_EC, 0x13131313); // slice_1: DQ_15~DQ_12
    // Apply read delay setting
    ScalerSetDWord(P8F_80_DPI_CTRL_1_80, 0x0000000C);

    //------------------------------
    // Rx FIFO latency
    //------------------------------
    ScalerSetDWord(P8E_64_READ_CTRL_1_64, 0x0000040E); // Follow DQ0
    // Apply read delay setting
    ScalerSetDWord(P8F_80_DPI_CTRL_1_80, 0x0000000C);
    //------------------------------
    // Controller IO pad driving/ODT
    //------------------------------
    // Set IO Pad Driving
    ScalerSetDWord(P8F_14_ODT_TTCP0_SET0_14, 0x03030503); // P-ODT
    ScalerSetDWord(P8F_18_ODT_TTCP1_SET0_18, 0x03030303);
    ScalerSetDWord(P8F_1C_ODT_TTCN0_SET0_1C, 0x03030503); // N-ODT
    ScalerSetDWord(P8F_20_ODT_TTCN1_SET0_20, 0x03030303);

    ScalerSetDWord(P8F_24_OCDP0_SET0_24, 0x11111111); // P-OCD
    ScalerSetDWord(P8F_28_OCDP1_SET0_28, 0x11111111);
    ScalerSetDWord(P8F_2C_OCDN0_SET0_2C, 0x11111111); // N-OCD
    ScalerSetDWord(P8F_30_OCDN1_SET0_30, 0x11111111);

    ScalerMaskSetDWord(P8E_1C_PAD_CTRL_PROG_1C, 0xF7FFFFFF, 0x08000000); // dzq_auto_up (if dzq_ref_up set 0)

    //For PUPD3, the signals are divided into groups//
    // ODT
    ScalerSetDWord(P90_60_DQ_ODT_SEL_60, 0x00000000);
    ScalerSetDWord(P90_64_DQ_ODT_SEL_64, 0x00000000);
    // Set unbalanced DQS ODT for PUPD3
    ScalerSetDWord(P90_70_DQS_P_ODT_SEL_70, 0x00001100); // P-ODT/N-ODT coarse tune selection for DQS[0],DQS[1],DQS[2],DQS[3]
    ScalerSetDWord(P90_74_DQS_P_ODT_SEL_74, 0x00001100); // P-ODT/N-ODT coarse tune selection for DQS[0],DQS[1],DQS[2],DQS[3]
    ScalerSetDWord(P90_78_DQS_N_ODT_SEL_78, 0x00000011); // P-ODT/N-ODT coarse tune selection for DQS#[0],DQS#[1],DQS#[2],DQS#[3]
    ScalerSetDWord(P90_7C_DQS_N_ODT_SEL_7C, 0x00000011); // P-ODT/N-ODT coarse tune selection for DQS#[0],DQS#[1],DQS#[2],DQS#[3]

    // OCD
    ScalerSetDWord(P90_68_DQ_OCD_SEL_68, 0x00000000);
    ScalerSetDWord(P90_6C_DQ_OCD_SEL_6C, 0x00000000);
    ScalerSetDWord(P90_80_DQS_OCD_SEL_80, 0x00000000); // NOCD/POCD  for DQS[0] & DQS[1] & DQS#[0] & DQS#[1]
    ScalerSetDWord(P90_84_DQS_OCD_SEL_84, 0x00000000); // NOCD/POCD  for DQS[2] & DQS[3] & DQS#[2] & DQS#[3]
    ScalerSetDWord(P8F_64_CKE_OCD_SEL_64, 0x00000000); // CKE OCD
    ScalerSetDWord(P8F_68_ADR_OCD_SEL_68, 0x00000000); // CS OCD
    ScalerSetDWord(P8F_6C_CK_OCD_SEL_6C, 0x00000000); // DCK & DCK# OCD

    // Set ODT enable interval
    ScalerSetDWord(P8E_68_READ_CTRL_2_68, 0x000FFFFF);
    ScalerSetDWord(P8E_6C_READ_CTRL_2_6C, 0x000FFFFF);
    // Apply read delay setting
    ScalerSetDWord(P8F_80_DPI_CTRL_1_80, 0x0000000C);

    // Set fw_set_mode = 'b01
    ScalerSetDWord(P8F_7C_DPI_CTRL_0_7C, 0x09770C55);

    //==============================
    // DDR1 DCU Settig
    //==============================
    // FIFO Frequency
    ScalerSetByte(P33_03_M1_FIFO_CLOCK_SELECT, 0x00); // FIFO Frequency [00]: DDRPLL;[11]: M2PLL

    //------------------------------
    // DCU start
    //------------------------------
    ScalerSetByte(P4_FC_EXTENDED_MODE_REGISTER0, 0x20); // 0xFC Mode Register
                                                        // bit 7 emr_first           = 0 0: EMR / 1: MR
                                                        // bit 6    mcurd_crc_en     = 0
                                                        // bit 5:4  emr_addr         = 10
                                                        // bit 3:0  emr_config[11:8] = 0
    ScalerSetByte(P4_FD_EXTENDED_MODE_REGISTER1, 0x00); // 0xFD Extended Mode Register bit 7:0 emr_config[7:0]  = 00

    ScalerSetByte(P4_FE_RANDOM_GENERATOR, 0x00); // bit7 rst_random_sel ( 0: dvs 1: ivs )   = 0
                                                 // bit6   rst_crc_sel ( 0: dvs 1: ivs )    = 0
                                                 // bit5   random_en                        = 0
                                                 // bit4   crc_start ( 0: finish 1: start ) = 0
                                                 // bit[3:0] crc_adr_port                   = 0

    ScalerSetByte(P4_4F_DDR_DCU_WRITE_RECOVERY, 0x0D); // bit 7:4 reserved
                                                       // bit 3   new cke mode  = 1 0: disable / 1: enable  (20190625 jjtsai)   TBD
                                                       // bit 2:0 DDR write recovery cycle  = 101   000: 0 cycle / 001: 1 cycle / 010: 2 cycle / 011: 3 cycle TBD
                                                       // 100: 4 cycle / 101: 5 cycle / 110: 6 cycle / 111: 7 cycle

    ScalerSetByte(P4_A1_SDR_CTRL0, 0x1B); // bit 7   rst_dll        = 0
                                          // bit 5:3 sdr_rd_delay   = 011
                                          // bit 2:0 sdr_wr_delay   = 011

    ScalerSetByte(P4_A2_SDR_CTRL1, 0x66); // bit 7:5 sdr_cl                               = 011
                                          // bit 4   burst_type                           = 0
                                          // bit 3:1 burst length                         = 011 BL = 8
                                          // bit 0   mode register set ( 0: mrs 1: emrs ) = 0

    ScalerSetByte(P4_A3_SDR_AREF_TIME, 0x0E); // Auto Refresh Time  (20190625 jjtsai)

    ScalerSetByte(P4_A4_SDR_PRCG, 0x93); // bit 7   Precharge all bank by ( 0: A8 1: A10 ) = 1
                                         // bit 6   Force to precharge all bank            = 0
                                         // bit 5   Columns per bank ( 0: 256 1: 512 )     = 0  256 column
                                         // bit 4   SDR reset ( 0: normal 1: reset )       = 1
                                         // bit 3:0 precharge delay cycle                  = 03

    ScalerSetByte(P4_A5_SDR_MEM_TYPE, 0x47); // bit 7:6 sdr_mem_size ( 00: 1Mx16x1 01: 4Mx16x1 10: 4Mx16x2 ) = 01
                                             // bit 5   sdr_bank_sel ( 0: 4bank 1: 2bank )                   = 0    4 bank
                                             // bit 4   sdr_abr_status                                       = 0
                                             // bit 3   sdr_abr_rec_en                                       = 0
                                             // bit 2:0 sdr_cas_latn                                         = 111  (20190703 jjtsai)   TBD

    ScalerSetByte(P4_A6_SDR_SLEW_RATE, 0x04); // bit 7   is_sdram ( 0: DDR 1: SDR ) = 0
                                              // bit 6:3 reserved
                                              // bit 2   sdr_auto_gating            = 1
                                              // bit 1   sdr_cke_l                  = 0
                                              // bit 0   sdr_cke_h                  = 0

    ScalerSetByte(P4_A7_SDR_AREF_CNT, 0x04); // Periodic refresh command interval time  (for simulation)
                                             // 444MHz  13ns * 256 * 4.5ns = 14.976us < 15.6us (4K / 64ms)  ( STD FW must set 0xD )
                                             // 400MHz  12ns * 256 * 5ns   = 15.36us  < 15.6us (4K / 64ms)  ( STD FW must set 0xC )

    ScalerSetByte(P4_A8_SDR_CLK_ALIGN, 0x00); // bit 7   DDR / SDR Clock Align MPLL Reset ( 0: Normal 1: Reset )
                                              // bit 6:0 reserved

    ScalerSetByte(P4_AA_SDR_RSC_AREF, 0xFF); // sdr_rsc_aref        TBD
    ScalerSetByte(P4_AB_SDR_RSC_MCU, 0xFF); // sdr_rsc_mcu      TBD
    ScalerSetByte(P4_AC_SDR_RSC_CAP1, 0xFF); // CAP         TBD
    ScalerSetByte(P4_AE_SDR_RSC_MAIN, 0x44); // DISP            TBD
    ScalerSetByte(P4_B0_SDR_RSC_RTC_RD, 0x11); // OD R          TBD
    ScalerSetByte(P4_B1_SDR_RSC_RTC_WR, 0xAA); // OD W          TBD
    ScalerSetByte(P4_B7_SDR_POWER_CTRL0, 0x00); // bit 7   enter precharge power down mode
                                                // bit 6   power down ready
                                                // bit 5:4 sdr_powdn_cmd ( 00: precharge power down 01: reserved 10: deep power down 11: self refresh )
                                                // bit 3   Force CKE pin of SDRAM High
                                                // bit 2:0 reserved

    ScalerSetByte(P4_A4_SDR_PRCG, 0x93); // Controller reset
    ScalerSetByte(P4_A4_SDR_PRCG, 0x83);
    ScalerTimerDelayXms(2);
    //------------------------------
    // DCU End
    //------------------------------

}

//--------------------------------------------------
// Description  : Calculate write level config
// Input Value  : pstDDR1PLLPhase
// Output Value : DWORD (32bit) of register setting
//--------------------------------------------------
DWORD ScalerDDR1CalcWrlvlConfig(StructDDR1PLLPI *pstDDR1PLLPhase)
{
    StructDDR1PLLPI stTheoPI;
    DWORD ulWrlvlConfig = 0;

    stTheoPI.ucDQS0 = pstDDR1PLLPhase->ucDQS0 % _TOTAL_THEO_DPI_PI_NUM;
    stTheoPI.ucDQS1 = pstDDR1PLLPhase->ucDQS1 % _TOTAL_THEO_DPI_PI_NUM;
    stTheoPI.ucDQ0 = pstDDR1PLLPhase->ucDQ0 % _TOTAL_THEO_DPI_PI_NUM;
    stTheoPI.ucDQ1 = pstDDR1PLLPhase->ucDQ1 % _TOTAL_THEO_DPI_PI_NUM;

    // DQS0
    ulWrlvlConfig |= ((stTheoPI.ucDQS0 < (53 + 0)) ? 0x00000000 :
                      ((stTheoPI.ucDQS0 < (21 + 64)) ? 0x00000010 :
                       ((stTheoPI.ucDQS0 < (53 + 64)) ? 0x00001000 : 0x00001010)));
    // DQS1
    ulWrlvlConfig |= ((stTheoPI.ucDQS1 < (53 + 0)) ? 0x00000000 :
                      ((stTheoPI.ucDQS1 < (21 + 64)) ? 0x00000020 :
                       ((stTheoPI.ucDQS1 < (53 + 64)) ? 0x00002000 : 0x00002020)));
    // DQ0
    ulWrlvlConfig |= ((stTheoPI.ucDQ0 < (53 + 0)) ? 0x00000000 :
                      ((stTheoPI.ucDQ0 < (21 + 64)) ? 0x00000100 :
                       ((stTheoPI.ucDQ0 < (53 + 64)) ? 0x00010000 : 0x00010100)));
    // DQ1
    ulWrlvlConfig |= ((stTheoPI.ucDQ1 < (53 + 0)) ? 0x00000000 :
                      ((stTheoPI.ucDQ1 < (21 + 64)) ? 0x00000200 :
                       ((stTheoPI.ucDQ1 < (53 + 64)) ? 0x00020000 : 0x00020200)));

    return ulWrlvlConfig;
}

//--------------------------------------------------
// Description  : DDR1PLL Function Control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR1PLLCtrl(bit bEnable)
{
#if(_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_2)
    if(bEnable == _ENABLE)
    {
        // Enable DDR1PLL LDO
        ScalerSetDWord(P88_34_CRT_RST_CTL_34, 0x00000001);

        DELAY_XUS(150);

        // De-assert both PLL reset and PLL ptr reset
        ScalerSetDWord(P88_34_CRT_RST_CTL_34, 0x0000000D);

        DELAY_XUS(85);
    }
    else // Disable
    {
        // Assert both PLL reset and PLL ptr reset
        ScalerMaskSetDWord(P88_34_CRT_RST_CTL_34, 0xFFFFFFF3, 0x00000000);

        DELAY_XUS(85);

        // Disable DDR1PLL LDO
        ScalerMaskSetDWord(P88_34_CRT_RST_CTL_34, 0xFFFFFFFE, 0x00000000);

        DELAY_XUS(150);
    }
#endif
}

//--------------------------------------------------
// Description  : DDR1PLL Output Control
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerDDR1PLLOutputCtrl(bit bEnable)
{
#if(_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_2)
    if(bEnable == _ENABLE)
    {
        // Enable DDR1PLL CLK
        ScalerSetDWord(P88_04_PLL_CTL0_04, 0x803F007F);

        DELAY_XUS(85);

        // Enable DDR1PLL CLK output, and wait until PLL is stable
        ScalerSetDWord(P88_08_PLL_CTL1_08, (0x003F0000 | ((~0xFFFFFFC0 & GET_OESYNC_SETTING(g_pstDDR1PLLPHASE[0])))));
        ScalerTimerPollingFlagProc(40, P90_13_INT_STATUS_2_13, _BIT0, _TRUE);
    }
    else // Disable
    {
        // Disable DDR1PLL CLK
        ScalerSetDWord(P88_04_PLL_CTL0_04, 0x00000057);

        DELAY_XUS(85);

        // Disable DDR1PLL A CLK output
        ScalerSetDWord(P88_08_PLL_CTL1_08, (0x00000000 | ((~0xFFFFFFC0 & GET_OESYNC_SETTING(g_pstDDR1PLLPHASE[0])))));

        DELAY_XUS(85);
    }
#endif
}

//--------------------------------------------------
// Description  : Set DDR1PLL Freq
// Input Value  : Target DDR Data Rate (KHz)
// Output Value : None
//--------------------------------------------------
void ScalerDDR1SetPLLFreq(DWORD ulFreq)
{
    ulFreq = ulFreq;
}

//--------------------------------------------------
// Description  : Set DDR1PLL Write Phase
// Input Value  : pstDDR2PLLPhase, bDDRSel
// Output Value : None
//--------------------------------------------------
void ScalerDDR1SetPLLWritePhase(StructDDR1PLLPI *pstDDR1PLLPhase)
{
    pstDDR1PLLPhase = pstDDR1PLLPhase;
}

//--------------------------------------------------
// Description  : DDR1 Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR1ControlReset(void)
{
    ScalerSetBit(P4_A4_SDR_PRCG, ~_BIT4, _BIT4);
    ScalerSetBit(P4_A4_SDR_PRCG, ~_BIT4, 0x00);

    // Delay Time us [300,x] Waiting for DDR1 Control Reset
    DELAY_XUS(300);

    // Set Mclk Gen Reset Align MPLL
    // Set Mclk Gen Local Reset
    ScalerSetBit(P4_A8_SDR_CLK_ALIGN, ~_BIT7, _BIT7);

    // Delay Time us [300,x] Waiting for DDR1 Mclk Reset
    DELAY_XUS(300);

    // Set Mclk Gen Local Reset
    ScalerSetBit(P4_A8_SDR_CLK_ALIGN, ~_BIT7, 0x00);
}
#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
