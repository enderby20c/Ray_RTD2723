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
// ID Code      : ScalerDDR3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDR3__

#include "ScalerFunctionInclude.h"
#include "DDR3/ScalerDDR3.h"


#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
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
// Description  : DC_phy initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3DCPHYInitial(void)
{
#if(_HW_MEMORY_DDR3_DPIDLL_GEN_TYPE == _MEMORY_DDR3_DPIDLL_GEN_1)
    ScalerDDR3DpiDllGen1();
#elif(_HW_MEMORY_DDR3_DPIDLL_GEN_TYPE == _MEMORY_DDR3_DPIDLL_GEN_2)
    ScalerDDR3DpiDllGen2();
#endif // End of #if(_HW_MEMORY_DDR3_DPIDLL_GEN_TYPE == _MEMORY_DDR3_DPIDLL_GEN_1)

#if(_HW_MEMORY_DDR3_GEN_TYPE == _MEMORY_DDR3_GEN_2)
    //==============================
    // DC PHY Setting
    //==============================
    //------------------------------
    // DDR timing setting
    //------------------------------
#if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M)
    Scaler32SetDWord(PB08200_00_TMCTRL0, 0x00100E08);
    Scaler32SetDWord(PB08200_04_TMCTRL1, 0x030C0A31);
    Scaler32SetDWord(PB08200_08_TMCTRL2, 0x02040C16);
    Scaler32SetDWord(PB08200_0C_TMCTRL3, 0x22104030);
    Scaler32SetDWord(PB08200_10_TMCTRL4, 0x01010400);
    Scaler32SetDWord(PB08200_14_TMCTRL5, 0x000AC159);
    Scaler32SetDWord(PB08200_18_TMCTRL6, 0x00200056);
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00040125);  // honda // MR1,MR0/OCD=40/ODT=60
    Scaler32SetDWord(PB08200_48_MOD23_REG, 0x00000028); // MR3,MR2
    Scaler32SetDWord(PB08200_2C_DC_MIS, 0x000A0001); // DDR3 Enable
    Scaler32SetDWord(PB08200_38_DC_MISC, 0x00000000); // Reserved
    Scaler32SetDWord(PB08202_90_WEIGHT_BANK, 0x00081938);

#elif(_MEMORY_DATA_RATE_SPEED <= _DDR3_DATA_RATE_1866M)
    Scaler32SetDWord(PB08200_00_TMCTRL0, 0x000F0D07); //
    Scaler32SetDWord(PB08200_04_TMCTRL1, 0x030E0A2A);
    Scaler32SetDWord(PB08200_08_TMCTRL2, 0x02040C13);
    Scaler32SetDWord(PB08200_0C_TMCTRL3, 0x1E0E602A);
    Scaler32SetDWord(PB08200_10_TMCTRL4, 0x00000300);
    Scaler32SetDWord(PB08200_14_TMCTRL5, 0x0009612C);
    Scaler32SetDWord(PB08200_18_TMCTRL6, 0x0020004C);
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00060115); // MR1,MR0/OCD=34/ODT=60
    Scaler32SetDWord(PB08200_48_MOD23_REG, 0x00000020); // MR3,MR2
    Scaler32SetDWord(PB08200_2C_DC_MIS, 0x000A0001); // DDR3 Enable
    Scaler32SetDWord(PB08200_38_DC_MISC, 0x00000000); // Reserved
    Scaler32SetDWord(PB08202_90_WEIGHT_BANK, 0x00081630);
#endif

    //------------------------------
    // Other DDR setting
    //------------------------------
    Scaler32SetDWord(PB08200_50_ERR_STATUS, 0x00000000); // Clear fifo Status
    Scaler32SetDWord(PB08200_4C_RFIFO_CTL, 0x00000030); // rfifo_thred=48
    Scaler32SetDWord(PB08201_40_DUMMY_REG, 0x80000048); // Dummy_Reg

    // cmdq-channel fifo Threshold
    Scaler32SetDWord(PB08205_00_FIFO_ARB_0, 0x00000040);
    Scaler32SetDWord(PB08205_F8_CS_CTRL, 0x00000000);

    // DQ Sel "1": dq from [15:0]
    Scaler32SetDWord(PB08201_54_CAL_MODE, 0x00000001);

    // Dc_sys2 write qfifo enable; dc_sys2 read/write separate enable
    Scaler32SetDWord(PB08203_98_DC_SYS2_CTRL, 0x00000005);

    // WEIGHT Setting
    Scaler32SetDWord(PB08202_80_WEIGHT_ENABLE, 0x0000001D);
    Scaler32SetDWord(PB08202_88_WEIGHT_DIERECTION, 0x00008200);

    if(ScalerDDR3DcPhyScrambleAvaiable() == _TRUE)
    {
        // DC_PHY Scrambling Enable
        Scaler32SetBit(PB08201_40_DUMMY_REG, ~(_BIT29), _BIT29);
        Scaler32SetDWord(PB08205_74_SCRAMBLE_CTRL, 0x00000003);
    }
    else
    {
#if(_HW_CPU32_ALLOCATE_DDR_SPACE == _OFF)
        // DC_PHY Scrambling Enable
        Scaler32SetBit(PB08201_40_DUMMY_REG, ~(_BIT29), _BIT29);
        Scaler32SetDWord(PB08205_74_SCRAMBLE_CTRL, 0x00000003);
#else
        DebugMessageCpu32("warning!!! NOTE: cpu allocate DDR space, DC_PHY Scramble Disable!!!", 0);
#endif
    }

    // DC1 init
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x30000000); // Dummy Setting
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x0A000000); // Clear Setting
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x0000C003); // Disable precharge all, Enable DDR3 int.
    ScalerTimerDelayXms(2);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x03000000); // end 200us
    ScalerTimerDelayXms(2);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x0C000000); // end 500us
    ScalerTimerDelayXms(5);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x00200000);

#if(_DDR3_KGD_DCC_SUPPORT == _OFF)
    // Config DDR3 KGD into DCCOFF test mode
    ScalerDDR3KGDDCCOff();
#endif

#endif // End of #if(_HW_MEMORY_DDR3_GEN_TYPE == _MEMORY_DDR3_GEN_2)
}
//--------------------------------------------------
// Description  : DC Sys initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3DCSysInitial(void)
{
#if(_HW_MEMORY_DDR3_GEN_TYPE == _MEMORY_DDR3_GEN_2)

    // ------- Set PA0_04_DC_SYS_MISC -----
    // (_BIT4 | _BIT3 | _BIT2 | _BIT1): Set 1'b1 when using 8G/4G/2G DRAM. DC_sys will use page[n] as bank[2].
    // _BIT0: Set 1'b1 for new pre-arbitration scheme or 1'b0 for the original one.
    // ------- Set PA0_05_DC_SYS_MISC -----
    // _BIT7: Set 1'b1 to enable the option of changing that the arbiter arbitrating request masking individual qack to all qacks
    // _BIT6: Set 1'b1 to enable address mapping of DDR3.
    // _BIT4: Set self_lookback_mode
    // _BIT3: Set DDR number : 0=One-DDR ; 1=Two-DDR.
    // (_BIT1 | _BIT0): Page size selection: 00=512bytes, 01=1024bytes, 10=2048bytes, 11=4096bytes
    if(GET_MEMORY_PIECE() == _MEMORY_1PC)
    {
        Scaler32SetDWord(PB08100_04_DC_SYS_MISC, 0x00420100);
        ScalerSetByte(P37_01_MCU_DC_LEN, 0x02);
    }
    else // _MEMORY_2PCS
    {
        Scaler32SetDWord(PB08100_04_DC_SYS_MISC, 0x024B0100);
        ScalerSetByte(P37_01_MCU_DC_LEN, 0x84);
    }

#endif // End of #if(_HW_MEMORY_DDR3_GEN_TYPE == _MEMORY_DDR3_GEN_2)
}

//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3PowerControl(bit bOn)
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
        ScalerDDR3DCSysSystemBridgeReset();

        //------------------------------
        // System Bridge Initial
        //------------------------------
        ScalerDDR3SystemBridgeInitial();

        //------------------------------
        // DC Sys Initial
        //------------------------------
        ScalerDDR3DCSysInitial();

        //------------------------------
        // DC PHY Initial
        //------------------------------
        ScalerDDR3DCPHYInitial();

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
        SET_MEMORY_PIECE(ScalerDDR3CheckMemoryCount());
        ScalerDDR3DCSysInitial();
        ScalerDDR3DCPHYInitial();
#endif

#if((_DDR3_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE))
        ScalerDDR3OfflinePhaseCalMCUMode();
#endif
    }
    else
    {
#if(_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_3)
        // Set ICG_clk_en Disable
        Scaler32SetBit(PB08000_04_PLL_CTL0, ~(_BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
#elif(_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_4)
        // Set ICG_clk_en Disable
        Scaler32SetBit(PB08000_04_PLL_CTL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);
#endif
        // Set clk_oe Disable
        Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT18 | _BIT17 | _BIT16), 0x00000000);

        // Reset DDR PLL
        Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000);

#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
        // Power Down  MPLL
        ScalerPLLMPLLPower(_OFF);
#endif
    }
}

//--------------------------------------------------
// Description  : DDR Power On/Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3DCSysSystemBridgeReset(void)
{
#if(_HW_MEMORY_DDR3_GEN_TYPE == _MEMORY_DDR3_GEN_2)
    //-----------------------------
    // Reset both DCSys/Sys Bridge
    //-----------------------------
    ScalerSetBit(P33_A0_M_DOMAIN_SB_RESET_A, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    // Delay Time us [5,x] Waiting for DDR3 setting
    DELAY_5US();

    //-----------------------------
    // Release DCSys reset
    //-----------------------------
    ScalerSetBit(P33_A0_M_DOMAIN_SB_RESET_A, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    // Delay Time us [5,x] Waiting for DDR3 setting
    DELAY_5US();

    //-----------------------------
    // Release Sys Bridge reset
    //-----------------------------
    ScalerSetBit(P33_A0_M_DOMAIN_SB_RESET_A, ~(_BIT2 | _BIT1 | _BIT0), (0x00));
    // Delay Time us [5,x] Waiting for DDR3 setting
    DELAY_5US();
#endif // End of #if(_HW_MEMORY_DDR3_GEN_TYPE == _MEMORY_DDR3_GEN_2)
}

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DDR3 Count for QC
// Input Value  : None
// Output Value : _MEMORY_1PC or _MEMORY_2PCS
//--------------------------------------------------
DWORD ScalerDDR3CheckMemoryCount(void)
{
    // Write DRAM Addr
    ScalerSetDWord(P37_04_MCU_DC_ADDR_H, 0x01FFF000);

    // Write Data
    ScalerSetDWord(P37_16_MCU_DC_DATABUF_W_A_06, 0x12345678);
    ScalerSetDWord(P37_26_MCU_DC_DATABUF_W_B_06, 0x9ABCDEF0);

    // Set Write command
    ScalerSetBit(P37_00_MCU_DC_CMD, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    ScalerTimerDelayXms(2);

    // Set Read command
    ScalerSetBit(P37_00_MCU_DC_CMD, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    ScalerTimerDelayXms(2);

    if((ScalerGetDWord(P37_36_MCU_DC_DATABUF_R_A_06) == 0x12345678) &&
       (ScalerGetDWord(P37_46_MCU_DC_DATABUF_R_B_06) == 0x9ABCDEF0))
    {
        DebugMessageQC("Memory Count = 2PCS", _MEMORY_2PCS);
        return _MEMORY_2PCS;
    }
    else
    {
        DebugMessageQC("Memory Count = 1PC", _MEMORY_1PC);
        return _MEMORY_1PC;
    }
}
#endif // End of #if(_FACTORY_RTD_QC_SUPPORT == _ON)

#if(_HW_MEMORY_DDR3_DPIDLL_GEN_TYPE == _MEMORY_DDR3_DPIDLL_GEN_1)
//--------------------------------------------------
// Description  : DDR DPI_DLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3DpiDllGen1(void)
{
    Scaler32SetBit(PB08002_40_DPI_CTRL_2, ~_BIT28, 0x10000000); // [28]set_reg_valid_ mode= 0x1 : auto
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT1 | _BIT0), 0x00000002); // [1:0]fw_set_mode = 'b10 (immediately)
    //==============================
    // DLL Setting
    //==============================
    //==DDR3 OCD/ODT Calibration Flow ==//
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT26 | _BIT25), 0x04000000); // zclk/32
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT19), 0x00080000); // ext. cal resistor
    Scaler32SetBit(PB08001_F8_PAD_BUS_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000); // PB08001_F8_PAD_BUS_1[6]: zq pad PD =0
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT7), 0x00000080); // zq_cal_cmd=1 : DDR3 no use

    Scaler32SetBit(PB08001_F4_PAD_BUS_0, ~(_BIT29), 0x00000000); // en_dmyi =0
    Scaler32SetBit(PB08001_F4_PAD_BUS_0, ~(_BIT26 | _BIT25 | _BIT24 | _BIT23 | _BIT22 | _BIT21), 0x03E00000); // vref_s[5:0]
    Scaler32SetBit(PB08001_F4_PAD_BUS_0, ~(_BIT28), 0x10000000); // vref_sel =1 : no use

    // [7]vref_range_0/1 = 'b1; [6:1]vref_s_0/1 = 0x3F (50%); [0]Vref_PD = 'b1 : external
    Scaler32SetDWord(PB08001_FC_PAD_BUS_2, 0x00BFBFBF);
    Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT1 | _BIT0), 0x00000003); // fw_set_wr_dly =1

    // ZQ Calibration
    // K set0
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT30 | _BIT29 | _BIT28), 0x00000000); // dzq_up_sel, set0
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT27), 0x08000000); // dzq_auto_up (if dzq_ref_up set 0)
    Scaler32SetDWord(PB08002_E8_PAD_CTRL_ZPROG, 0x01080318); // Set0 NOCD=40/ NODT=120 RL6829 U28 table
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x01000000); // zctrl_start =1
    // Wait for Calibration Done
    ScalerTimerPollingFlagProc32Bit(5, PB08001_40_PAD_ZCTRL_STATUS, _BIT7, _TRUE);
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x00000000); // zctrl_start =0

    // K set1
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT30 | _BIT29 | _BIT28), 0x10000000); // dzq_up_sel, set1
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT27), 0x08000000); // dzq_auto_up (if dzq_ref_up set 0)
    Scaler32SetDWord(PB08002_EC_PAD_CTRL_ZPROG, 0x00260318); // Set1 NOCD=40/ NODT=151.8 RL6829 U28 table
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x01000000); // zctrl_start =1
    // Wait for Calibration Done
    ScalerTimerPollingFlagProc32Bit(5, PB08001_40_PAD_ZCTRL_STATUS, _BIT7, _TRUE);
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x00000000); // zctrl_start =0

    // K set2
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT30 | _BIT29 | _BIT28), 0x20000000); // dzq_up_sel, set2
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT27), 0x08000000);
    Scaler32SetDWord(PB08002_F0_PAD_CTRL_ZPROG, 0x01080218); // Set2 NOCD=55.38/ NODT=120 RL6829
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x01000000);
    // Wait for Calibration Done
    ScalerTimerPollingFlagProc32Bit(5, PB08001_40_PAD_ZCTRL_STATUS, _BIT7, _TRUE);
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x00000000);

    // K set3
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT30 | _BIT29 | _BIT28), 0x30000000); // dzq_up_sel, set3
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT27), 0x08000000);
    Scaler32SetDWord(PB08002_F4_PAD_CTRL_ZPROG, 0x01080332); // Set3 NOCD=33.88 /NODT=120 RL6829 U28 table
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x01000000);
    // Wait for Calibration Done
    ScalerTimerPollingFlagProc32Bit(5, PB08001_40_PAD_ZCTRL_STATUS, _BIT7, _TRUE);
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x00000000);

    // K set4
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT30 | _BIT29 | _BIT28), 0x40000000); // dzq_up_sel, set4
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT27), 0x08000000);
    Scaler32SetDWord(PB08002_F8_PAD_CTRL_ZPROG, 0x01080210); // Set4 NOCD=60 /NODT=120 RL6829 U28 table
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x01000000);
    // Wait for Calibration Done
    ScalerTimerPollingFlagProc32Bit(5, PB08001_40_PAD_ZCTRL_STATUS, _BIT7, _TRUE);
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x00000000);

    if((ScalerDDR3GetDDROldRDLStatus() != _TRUE) && (_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M))
    {
        Scaler32SetDWord(PB08001_E0_DQS_OCD_SEL, 0x33333333); // DQS OCD 33.88
        Scaler32SetDWord(PB08001_E4_DQS_OCD_SEL, 0x33333333); // DQS OCD 33.88
        Scaler32SetDWord(PB08003_30_DQS_OCD_SEL_2, 0x33333333);
        Scaler32SetDWord(PB08003_34_DQS_OCD_SEL_2, 0x33333333);
        Scaler32SetDWord(PB08001_D0_DQS_P_ODT_SEL, 0x00110011);
        Scaler32SetDWord(PB08001_D4_DQS_P_ODT_SEL, 0x00110011);
        Scaler32SetDWord(PB08001_D8_DQS_N_ODT_SEL, 0x11001100);
        Scaler32SetDWord(PB08001_DC_DQS_N_ODT_SEL, 0x11001100);
        // DQ Chnage to Set3 OCD = 33.88
        Scaler32SetDWord(PB08001_C8_DQ_OCD_SEL, 0x00003333); // DQ OCD 33.88
        Scaler32SetDWord(PB08001_CC_DQ_OCD_SEL, 0x00003333);
        Scaler32SetDWord(PB08003_28_DQ_OCD_SEL_2, 0x33333333);
        Scaler32SetDWord(PB08003_2C_DQ_OCD_SEL_2, 0x33333333);
        Scaler32SetDWord(PB08001_C0_DQ_ODT_SEL, 0x00000000);
        Scaler32SetDWord(PB08001_C4_DQ_ODT_SEL, 0x00000000);
        Scaler32SetDWord(PB08002_9C_CS_SEL_EMPH_CTL, 0x11111111);
        Scaler32SetDWord(PB08002_A0_DDR4_CS_EMPH_CTL, 0x11110077);
        Scaler32SetDWord(PB08002_A4_CK_EMPH_CTL, 0x10771077);
        Scaler32SetDWord(PB08002_A8_CK_SEL_EMPH_CTL, 0x11111111);
        Scaler32SetDWord(PB08002_AC_ADR_EMPH_CTL, 0x11111111);
        Scaler32SetDWord(PB08002_B0_ADR_EMPH_CTL, 0x11111111);
        Scaler32SetDWord(PB08001_F0_CK_OCD_SEL, 0x33333333); // DCK & DCK# OCD = 34
        // CA Change to Set 0 = OCD40
        Scaler32SetDWord(PB08001_E8_CKE_OCD_SEL, 0x00000000); // CKE OCD
        Scaler32SetDWord(PB08001_EC_ADR_OCD_SEL, 0x00000000); // CS OCD
        Scaler32SetDWord(PB08002_04_OCD_SEL_0, 0x00000000); // A0,A1,A2,A3
        Scaler32SetDWord(PB08002_08_OCD_SEL_1, 0x00000000); // A4,A5,A6,A7
        Scaler32SetDWord(PB08002_0C_OCD_SEL_2, 0x00000000); // A8,A9,A10,A11
        Scaler32SetDWord(PB08002_10_OCD_SEL_3, 0x00000000); // A12,A13,A14,A15
        Scaler32SetDWord(PB08002_14_OCD_SEL_4, 0x00000000); // A16,BA0
        Scaler32SetDWord(PB08002_18_OCD_SEL_5, 0x00000000); // BA1,BA2,RASN,CASN
        Scaler32SetDWord(PB08002_1C_OCD_SEL_6, 0x00000000); // WEN,ODT,RSTN,PAR
        Scaler32SetDWord(PB08002_20_OCD_SEL_7, 0x00000000); // PAR_1, ACTN, BG0, TEN
        Scaler32SetDWord(PB08002_24_OCD_SEL_8, 0x00000000); // ALERT, ALERT_1,
    }
    else
    {
        //For PUPD3, the signals are divided into groups//
        Scaler32SetDWord(PB08001_E0_DQS_OCD_SEL, 0x00000000); // DQS OCD 40
        Scaler32SetDWord(PB08001_E4_DQS_OCD_SEL, 0x00000000); // DQS OCD 40
        Scaler32SetDWord(PB08003_30_DQS_OCD_SEL_2, 0x00000000);
        Scaler32SetDWord(PB08003_34_DQS_OCD_SEL_2, 0x00000000);
        Scaler32SetDWord(PB08001_D0_DQS_P_ODT_SEL, 0x00110011);
        Scaler32SetDWord(PB08001_D4_DQS_P_ODT_SEL, 0x00110011);
        Scaler32SetDWord(PB08001_D8_DQS_N_ODT_SEL, 0x11001100);
        Scaler32SetDWord(PB08001_DC_DQS_N_ODT_SEL, 0x11001100);
        // DQ Chnage to Set2 OCD =50
        Scaler32SetDWord(PB08001_C8_DQ_OCD_SEL, 0x00002222);
        Scaler32SetDWord(PB08001_CC_DQ_OCD_SEL, 0x00002222);
        Scaler32SetDWord(PB08003_28_DQ_OCD_SEL_2, 0x22222222);
        Scaler32SetDWord(PB08003_2C_DQ_OCD_SEL_2, 0x22222222);
        Scaler32SetDWord(PB08001_C0_DQ_ODT_SEL, 0x00000000);
        Scaler32SetDWord(PB08001_C4_DQ_ODT_SEL, 0x00000000);
        Scaler32SetDWord(PB08002_9C_CS_SEL_EMPH_CTL, 0x11111111);
        Scaler32SetDWord(PB08002_A0_DDR4_CS_EMPH_CTL, 0x11110077);
        Scaler32SetDWord(PB08002_A4_CK_EMPH_CTL, 0x10771077);
        Scaler32SetDWord(PB08002_A8_CK_SEL_EMPH_CTL, 0x11111111);
        Scaler32SetDWord(PB08002_AC_ADR_EMPH_CTL, 0x11111111);
        Scaler32SetDWord(PB08002_B0_ADR_EMPH_CTL, 0x11111111);
        Scaler32SetDWord(PB08001_F0_CK_OCD_SEL, 0x00000000); // DCK & DCK# OCD = OCD40
        // CA Change to Set 3 & 4
        Scaler32SetDWord(PB08001_E8_CKE_OCD_SEL, 0x00004343); // CKE OCD
        Scaler32SetDWord(PB08001_EC_ADR_OCD_SEL, 0x43000300); // CS OCD
        Scaler32SetDWord(PB08002_04_OCD_SEL_0, 0x43434343); // A0,A1,A2,A3
        Scaler32SetDWord(PB08002_08_OCD_SEL_1, 0x43434343); // A4,A5,A6,A7
        Scaler32SetDWord(PB08002_0C_OCD_SEL_2, 0x43434343); // A8,A9,A10,A11
        Scaler32SetDWord(PB08002_10_OCD_SEL_3, 0x43434343); // A12,A13,A14,A15
        Scaler32SetDWord(PB08002_14_OCD_SEL_4, 0x43434343); // A16,BA0
        Scaler32SetDWord(PB08002_18_OCD_SEL_5, 0x43434343); // BA1,BA2,RASN,CASN
        Scaler32SetDWord(PB08002_1C_OCD_SEL_6, 0x43434343); // WEN,ODT,RSTN,PAR
        Scaler32SetDWord(PB08002_20_OCD_SEL_7, 0x43434343); // PAR_1, ACTN, BG0, TEN
        Scaler32SetDWord(PB08002_24_OCD_SEL_8, 0x43430000); // ALERT, ALERT_1,
    }
    Scaler32SetDWord(PB08002_2C_CKE_ODT_SEL, 0x77777777);
    Scaler32SetDWord(PB08002_34_CLK_ODT_SEL, 0x77777777);
    Scaler32SetDWord(PB08002_30_ADR_ODT_SEL, 0x77777777);
    //---end ZQ Cal.----

    // DQ 3-point Calibration
    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E2026); // [5:4]cal_set_mode = 'b10;[1:0]fw_set_mode = 'b10 (both immediately)
    Scaler32SetDWord(PB08004_F8_CAL_LS_SEL, 0x11111111); // Left sampling point of 3-point calibration
    Scaler32SetDWord(PB08004_FC_CAL_LS_SEL, 0x11111111);
    Scaler32SetDWord(PB08005_08_CAL_RS_SEL, 0x11111111); // Right sampling point of 3-point calibration
    Scaler32SetDWord(PB08005_0C_CAL_RS_SEL, 0x11111111);
    Scaler32SetDWord(PB08006_F8_CAL_LS_SEL, 0x11111111); // Left sampling point of 3-point calibration
    Scaler32SetDWord(PB08006_FC_CAL_LS_SEL, 0x11111111);
    Scaler32SetDWord(PB08007_08_CAL_RS_SEL, 0x11111111); // Right sampling point of 3-point calibration
    Scaler32SetDWord(PB08007_0C_CAL_RS_SEL, 0x11111111);
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x00000030); // fw_set_cal_rang

    //------------------------------
    // Tx/Rx DQ delay tap
    //------------------------------
    // Tx delay
    Scaler32SetDWord(PB08001_00_ADR_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08001_04_ADR_DLY_1, 0x88888888);
    Scaler32SetDWord(PB08001_08_ADR_DLY_2, 0x88888888);
    Scaler32SetDWord(PB08001_0C_CMD_DLY_0, 0x20888888);
    Scaler32SetDWord(PB08001_10_CMD_DLY_1, 0x88888888);
    Scaler32SetDWord(PB08004_60_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08004_64_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08004_68_DQ_DLY_1, 0x00008888);
    Scaler32SetDWord(PB08004_6C_DQ_DLY_1, 0x00008888);
    Scaler32SetDWord(PB08006_60_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08006_64_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08006_68_DQ_DLY_1, 0x00008888);
    Scaler32SetDWord(PB08006_6C_DQ_DLY_1, 0x00008888);

    // odt_en length = Request length + 0.5T (1T = DDRPLL)
    Scaler32SetDWord(PB08004_08_READ_CTRL_2, 0x00000000);
    Scaler32SetDWord(PB08004_0C_READ_CTRL_2, 0x00000000);
    Scaler32SetDWord(PB08006_08_READ_CTRL_2, 0x00000000);
    Scaler32SetDWord(PB08006_0C_READ_CTRL_2, 0x00000000);

#if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M)
    // odt_en dealy
    Scaler32SetDWord(PB08004_18_READ_CTRL_6, 0x000001E0);
    Scaler32SetDWord(PB08004_1C_READ_CTRL_6, 0x000003F0);
    Scaler32SetDWord(PB08006_18_READ_CTRL_6, 0x000007F8);
    Scaler32SetDWord(PB08006_1C_READ_CTRL_6, 0x00000FFC);

    // Read dqs_en latency = F : FRC Mode
    Scaler32SetDWord(PB08005_F8_READ_CTRL_0, 0x0000000E); // FRC Mode
    Scaler32SetDWord(PB08005_FC_READ_CTRL_0, 0x0000000E);
    Scaler32SetDWord(PB08007_F8_READ_CTRL_0, 0x0000000E);
    Scaler32SetDWord(PB08007_FC_READ_CTRL_0, 0x0000000E);
    // Read FIFO latency = 7T; rd_dly_follow_dq0 =0
    Scaler32SetDWord(PB08001_70_READ_CTRL_1, 0x00000007); // Old&New RDL

#elif(_MEMORY_DATA_RATE_SPEED <= _DDR3_DATA_RATE_1866M)
    // odt_en dealy
    Scaler32SetDWord(PB08004_18_READ_CTRL_6, 0x000001FF);
    Scaler32SetDWord(PB08004_1C_READ_CTRL_6, 0x000003FF);
    Scaler32SetDWord(PB08006_18_READ_CTRL_6, 0x000007FF);
    Scaler32SetDWord(PB08006_1C_READ_CTRL_6, 0x00000FFF);

    // Read dqs_en latency = F : FRC Mode
    Scaler32SetDWord(PB08005_F8_READ_CTRL_0, 0x0000000B); // FRC Mode
    Scaler32SetDWord(PB08005_FC_READ_CTRL_0, 0x0000000B);
    Scaler32SetDWord(PB08007_F8_READ_CTRL_0, 0x0000000B);
    Scaler32SetDWord(PB08007_FC_READ_CTRL_0, 0x0000000B);
    // Read FIFO latency = 6T; rd_dly_follow_dq0 =0
    Scaler32SetDWord(PB08001_70_READ_CTRL_1, 0x00000006);
#endif

    // [21]= 0x1 : repeat the first data (WL + 2);[20]=0x0 initial level of write data
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT21 | _BIT20), 0x00200000);
    // [15:12] = 0x1 : DQ OE pre 0.5T open
    Scaler32SetBit(PB08005_18_DQ_IO_CTL_2, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12), 0x00001000);
    Scaler32SetBit(PB08007_18_DQ_IO_CTL_2, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12), 0x00001000);

#if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M)
    if(ScalerDDR3GetDDROldRDLStatus() != _TRUE)
    {
        // RDQ delay tap - DQS_IN raising edge delay chain control
        Scaler32SetDWord(PB08004_20_DQS_IN_DLY_0, 0x13141413); // FRC Mode
        Scaler32SetDWord(PB08004_28_DQS_IN_DLY_1, 0x13131412);
        Scaler32SetDWord(PB08004_24_DQS_IN_DLY_0, 0x14141113);
        Scaler32SetDWord(PB08004_2C_DQS_IN_DLY_1, 0x14141414);
        Scaler32SetDWord(PB08006_20_DQS_IN_DLY_0, 0x11121213);
        Scaler32SetDWord(PB08006_28_DQS_IN_DLY_1, 0x13131412);
        Scaler32SetDWord(PB08006_24_DQS_IN_DLY_0, 0x14141213);
        Scaler32SetDWord(PB08006_2C_DQS_IN_DLY_1, 0x14141414);

        // RDQ delay tap - DQS_IN falling edge delay chain control
        Scaler32SetDWord(PB08004_38_DQS_IN_DLY_2, 0x12141313); // FRC Mode
        Scaler32SetDWord(PB08004_40_DQS_IN_DLY_3, 0x13131312);
        Scaler32SetDWord(PB08004_3C_DQS_IN_DLY_2, 0x14151315);
        Scaler32SetDWord(PB08004_44_DQS_IN_DLY_3, 0x15151415);
        Scaler32SetDWord(PB08006_38_DQS_IN_DLY_2, 0x12131313);
        Scaler32SetDWord(PB08006_40_DQS_IN_DLY_3, 0x14121412);
        Scaler32SetDWord(PB08006_3C_DQS_IN_DLY_2, 0x13131112);
        Scaler32SetDWord(PB08006_44_DQS_IN_DLY_3, 0x12121212);
    }
    else
    {
        // RDQ delay tap - DQS_IN raising edge delay chain control
        Scaler32SetDWord(PB08004_20_DQS_IN_DLY_0, 0x15151514); // FRC Mode
        Scaler32SetDWord(PB08004_28_DQS_IN_DLY_1, 0x15141515);
        Scaler32SetDWord(PB08004_24_DQS_IN_DLY_0, 0x16161316);
        Scaler32SetDWord(PB08004_2C_DQS_IN_DLY_1, 0x14141214);
        Scaler32SetDWord(PB08006_20_DQS_IN_DLY_0, 0x14161213);
        Scaler32SetDWord(PB08006_28_DQS_IN_DLY_1, 0x14151513);
        Scaler32SetDWord(PB08006_24_DQS_IN_DLY_0, 0x15141215);
        Scaler32SetDWord(PB08006_2C_DQS_IN_DLY_1, 0x14141313);

        // RDQ delay tap - DQS_IN falling edge delay chain control
        Scaler32SetDWord(PB08004_38_DQS_IN_DLY_2, 0x15141513); // FRC Mode
        Scaler32SetDWord(PB08004_40_DQS_IN_DLY_3, 0x15141414);
        Scaler32SetDWord(PB08004_3C_DQS_IN_DLY_2, 0x15151216);
        Scaler32SetDWord(PB08004_44_DQS_IN_DLY_3, 0x15141514);
        Scaler32SetDWord(PB08006_38_DQS_IN_DLY_2, 0x14141414);
        Scaler32SetDWord(PB08006_40_DQS_IN_DLY_3, 0x15161615);
        Scaler32SetDWord(PB08006_3C_DQS_IN_DLY_2, 0x14151316);
        Scaler32SetDWord(PB08006_44_DQS_IN_DLY_3, 0x14151414);
    }
#elif(_MEMORY_DATA_RATE_SPEED <= _DDR3_DATA_RATE_1866M)
    // RDQ delay tap - DQS_IN raising edge delay chain control
    Scaler32SetDWord(PB08004_20_DQS_IN_DLY_0, 0x18181817); // FRC Mode
    Scaler32SetDWord(PB08004_28_DQS_IN_DLY_1, 0x17171716);
    Scaler32SetDWord(PB08004_24_DQS_IN_DLY_0, 0x18181718);
    Scaler32SetDWord(PB08004_2C_DQS_IN_DLY_1, 0x16171717);
    Scaler32SetDWord(PB08006_20_DQS_IN_DLY_0, 0x17171717);
    Scaler32SetDWord(PB08006_28_DQS_IN_DLY_1, 0x18181817);
    Scaler32SetDWord(PB08006_24_DQS_IN_DLY_0, 0x18181718);
    Scaler32SetDWord(PB08006_2C_DQS_IN_DLY_1, 0x17181717);

    // RDQ delay tap - DQS_IN falling edge delay chain control
    Scaler32SetDWord(PB08004_38_DQS_IN_DLY_2, 0x16161716); // FRC Mode
    Scaler32SetDWord(PB08004_40_DQS_IN_DLY_3, 0x16161615);
    Scaler32SetDWord(PB08004_3C_DQS_IN_DLY_2, 0x18181718);
    Scaler32SetDWord(PB08004_44_DQS_IN_DLY_3, 0x16171817);
    Scaler32SetDWord(PB08006_38_DQS_IN_DLY_2, 0x16161717);
    Scaler32SetDWord(PB08006_40_DQS_IN_DLY_3, 0x16171716);
    Scaler32SetDWord(PB08006_3C_DQS_IN_DLY_2, 0x17161517);
    Scaler32SetDWord(PB08006_44_DQS_IN_DLY_3, 0x15161615);

#endif // End of #if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M)

    // Triger all DLL setting
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x0000000C); // fw_set_rd_dly
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x00000030); // fw_set_cal_rang
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x00000003); // fw_set_wr_fly
    Scaler32SetBit(PB08002_40_DPI_CTRL_2, ~_BIT28, 0x10000000);
    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E2004); // [1:0]fw_set_mode = 'b00 (during no read)
}
#elif(_HW_MEMORY_DDR3_DPIDLL_GEN_TYPE == _MEMORY_DDR3_DPIDLL_GEN_2)
//--------------------------------------------------
// Description  : DDR DPI_DLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3DpiDllGen2(void)
{
    Scaler32SetBit(PB08002_40_DPI_CTRL_2, ~_BIT28, 0x10000000); // [28]set_reg_valid_ mode= 0x1 : auto
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT1 | _BIT0), 0x00000002); // [1:0]fw_set_mode = 'b10 (immediately)
    //==============================
    // DLL Setting
    //==============================
    //==DDR3 OCD/ODT Calibration Flow ==//
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT26 | _BIT25), 0x04000000); // zclk/32
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT19), 0x00080000); // ext. cal resistor
    Scaler32SetBit(PB08001_F8_PAD_BUS_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000000); // PB08001_F8_PAD_BUS_1[6]: zq pad PD =0
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT7), 0x00000000); // zq_cal_cmd=0 : RL6952

    Scaler32SetBit(PB08001_F4_PAD_BUS_0, ~(_BIT29), 0x00000000); // en_dmyi =0
    Scaler32SetBit(PB08001_F4_PAD_BUS_0, ~(_BIT26 | _BIT25 | _BIT24 | _BIT23 | _BIT22 | _BIT21), 0x03E00000); // vref_s[5:0]
    Scaler32SetBit(PB08001_F4_PAD_BUS_0, ~(_BIT28), 0x10000000); // vref_sel =1 : no use

    // [7]vref_range_0/1 = 'b1; [6:1]vref_s_0/1 = 0x3F (50%); [0]Vref_PD = 'b1 : external
    Scaler32SetDWord(PB08001_FC_PAD_BUS_2, 0x00BFBFBF);
    Scaler32SetBit(PB08002_3C_DPI_CTRL_1, ~(_BIT1 | _BIT0), 0x00000003); // fw_set_wr_dly =1

    ScalerTimerDelayXms(50); // Wait internal Vref stable

    // ZQ Calibration
    // K set0
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT30 | _BIT29 | _BIT28), 0x00000000); // dzq_up_sel, set0
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT27), 0x08000000); // dzq_auto_up (if dzq_ref_up set 0)
    Scaler32SetDWord(PB08002_E8_PAD_CTRL_ZPROG, 0x00300331); // Set0 NOCD=34/ NODT=120 RL6952 T22 table

    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x01000000); // zctrl_start =1
    // Wait for Calibration Done
    ScalerTimerPollingFlagProc32Bit(5, PB08001_40_PAD_ZCTRL_STATUS, _BIT7, _TRUE);
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x00000000); // zctrl_start =0

    // K set1
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT30 | _BIT29 | _BIT28), 0x10000000); // dzq_up_sel, set1
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT27), 0x08000000); // dzq_auto_up (if dzq_ref_up set 0)
    Scaler32SetDWord(PB08002_EC_PAD_CTRL_ZPROG, 0x0026023F); // Set1 NOCD=40/ NODT=150 RL6952 T22 table

    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x01000000); // zctrl_start =1
    // Wait for Calibration Done
    ScalerTimerPollingFlagProc32Bit(5, PB08001_40_PAD_ZCTRL_STATUS, _BIT7, _TRUE);
    Scaler32SetBit(PB08001_30_PAD_CTRL_PROG, ~(_BIT24), 0x00000000); // zctrl_start =0


    //For PUPD3, the signals are divided into groups//
    Scaler32SetDWord(PB08001_E0_DQS_OCD_SEL, 0x00000000); // DQS OCD 34
    Scaler32SetDWord(PB08001_E4_DQS_OCD_SEL, 0x00000000); // DQS OCD 34
    Scaler32SetDWord(PB08001_E8_CKE_OCD_SEL, 0x00001111); // CKE OCD
    Scaler32SetDWord(PB08001_EC_ADR_OCD_SEL, 0x11111111); // CS OCD
    Scaler32SetDWord(PB08001_F0_CK_OCD_SEL, 0x00000000); // DCK & DCK# OCD

    Scaler32SetDWord(PB08003_30_DQS_OCD_SEL_2, 0x00000000);
    Scaler32SetDWord(PB08003_34_DQS_OCD_SEL_2, 0x00000000);

    Scaler32SetDWord(PB08001_C8_DQ_OCD_SEL, 0x00000000);
    Scaler32SetDWord(PB08001_CC_DQ_OCD_SEL, 0x00000000);
    Scaler32SetDWord(PB08003_28_DQ_OCD_SEL_2, 0x00000000);
    Scaler32SetDWord(PB08003_2C_DQ_OCD_SEL_2, 0x00000000);

    Scaler32SetDWord(PB08002_04_OCD_SEL_0, 0x11111111); // A0,A1,A2,A3
    Scaler32SetDWord(PB08002_08_OCD_SEL_1, 0x11111111); // A4,A5,A6,A7
    Scaler32SetDWord(PB08002_0C_OCD_SEL_2, 0x11111111); // A8,A9,A10,A11
    Scaler32SetDWord(PB08002_10_OCD_SEL_3, 0x11111111); // A12,A13,A14,A15
    Scaler32SetDWord(PB08002_14_OCD_SEL_4, 0x11111111); // A16,BA0
    Scaler32SetDWord(PB08002_18_OCD_SEL_5, 0x11111111); // BA1,BA2,RASN,CASN
    Scaler32SetDWord(PB08002_1C_OCD_SEL_6, 0x11111111); // WEN,ODT,RSTN,PAR
    Scaler32SetDWord(PB08002_20_OCD_SEL_7, 0x11111111); // PAR_1, ACTN, BG0, TEN
    Scaler32SetDWord(PB08002_24_OCD_SEL_8, 0x11110000); // ALERT, ALERT_1,

    Scaler32SetDWord(PB08001_D0_DQS_P_ODT_SEL, 0x00110011);
    Scaler32SetDWord(PB08001_D4_DQS_P_ODT_SEL, 0x00110011);
    Scaler32SetDWord(PB08001_D8_DQS_N_ODT_SEL, 0x11001100);
    Scaler32SetDWord(PB08001_DC_DQS_N_ODT_SEL, 0x11001100);

    Scaler32SetDWord(PB08001_C0_DQ_ODT_SEL, 0x00000000);
    Scaler32SetDWord(PB08001_C4_DQ_ODT_SEL, 0x00000000);

    Scaler32SetDWord(PB08002_2C_CKE_ODT_SEL, 0x77777777);
    Scaler32SetDWord(PB08002_34_CLK_ODT_SEL, 0x77777777);
    Scaler32SetDWord(PB08002_30_ADR_ODT_SEL, 0x77777777);

    Scaler32SetDWord(PB08002_9C_CS_SEL_EMPH_CTL, 0x11111111);
    Scaler32SetDWord(PB08002_A0_DDR4_CS_EMPH_CTL, 0x11110077);
    Scaler32SetDWord(PB08002_A4_CK_EMPH_CTL, 0x10771077);
    Scaler32SetDWord(PB08002_A8_CK_SEL_EMPH_CTL, 0x11111111);
    Scaler32SetDWord(PB08002_AC_ADR_EMPH_CTL, 0x11111111);
    Scaler32SetDWord(PB08002_B0_ADR_EMPH_CTL, 0x11111111);

    //---end ZQ Cal.----

    // DQ 3-point Calibration
    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E2026); // [5:4]cal_set_mode = 'b10;[1:0]fw_set_mode = 'b10 (both immediately)
    Scaler32SetDWord(PB08004_20_DEL_POS_SEL, 0x11111111); // Left/Right sampling point of 3-point calibration
    Scaler32SetDWord(PB08004_24_DEL_POS_SEL, 0x11111111);
    Scaler32SetDWord(PB08004_30_DEL_NEG_SEL, 0x11111111); // Left/Right sampling point of 3-point calibration
    Scaler32SetDWord(PB08004_34_DEL_NEG_SEL, 0x11111111);

    //------------------------------
    // Tx/Rx DQ delay tap
    //------------------------------
    // Tx delay
    Scaler32SetDWord(PB08001_00_ADR_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08001_04_ADR_DLY_1, 0x88888888);
    Scaler32SetDWord(PB08001_08_ADR_DLY_2, 0x88888888);
    Scaler32SetDWord(PB08001_0C_CMD_DLY_0, 0x20888888);
    Scaler32SetDWord(PB08001_10_CMD_DLY_1, 0x88888888);
    Scaler32SetDWord(PB08004_80_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08004_84_DQ_DLY_0, 0x88888888);
    Scaler32SetDWord(PB08004_88_DQ_DLY_1, 0x00008888);
    Scaler32SetDWord(PB08004_8C_DQ_DLY_1, 0x00008888);

    // odt_en length = Request length + 0.5T (1T = DDRPLL)
    Scaler32SetDWord(PB08004_08_READ_CTRL_2, 0x00000000);
    Scaler32SetDWord(PB08004_0C_READ_CTRL_2, 0x00000000);

#if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M)
    // odt_en dealy
    Scaler32SetDWord(PB08004_18_READ_CTRL_6, 0x000001E0);
    Scaler32SetDWord(PB08004_1C_READ_CTRL_6, 0x000003F0);
    // Read dqs_en latency = F : FRC Mode
    Scaler32SetDWord(PB08005_F8_READ_CTRL_0, 0x0000000F); // FRC Mode
    Scaler32SetDWord(PB08005_FC_READ_CTRL_0, 0x0000000F);
    // Read FIFO latency = 6T; rd_dly_follow_dq0 =0
    Scaler32SetDWord(PB08001_70_READ_CTRL_1, 0x00000006); // FRC Mode

#elif(_MEMORY_DATA_RATE_SPEED <= _DDR3_DATA_RATE_1866M)
    // odt_en dealy
    Scaler32SetDWord(PB08004_18_READ_CTRL_6, 0x000001FF);
    Scaler32SetDWord(PB08004_1C_READ_CTRL_6, 0x000003FF);
    // Read dqs_en latency = F : FRC Mode
    Scaler32SetDWord(PB08005_F8_READ_CTRL_0, 0x0000000C); // FRC Mode
    Scaler32SetDWord(PB08005_FC_READ_CTRL_0, 0x0000000C);
    // Read FIFO latency = 6T; rd_dly_follow_dq0 =0
    Scaler32SetDWord(PB08001_70_READ_CTRL_1, 0x00000006);
#endif

    // [21]= 0x1 : repeat the first data (WL + 2);[20]=0x0 initial level of write data
    Scaler32SetBit(PB08002_38_DPI_CTRL_0, ~(_BIT21 | _BIT20), 0x00200000);
    // [15:12] = 0x1 : DQ OE pre 0.5T open
    Scaler32SetBit(PB08005_18_DQ_IO_CTL_2, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12), 0x00001000);

#if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M)
    // RDQ delay tap - DQS_IN raising edge delay chain control
    Scaler32SetDWord(PB08004_40_DQS_IN_DLY_0, 0x0D0C0C0D); // FRC Mode
    Scaler32SetDWord(PB08004_48_DQS_IN_DLY_1, 0x0E0E0D0D);
    Scaler32SetDWord(PB08004_44_DQS_IN_DLY_0, 0x0E0F0F10);
    Scaler32SetDWord(PB08004_4C_DQS_IN_DLY_1, 0x0E100F0F);
    // RDQ delay tap - DQS_IN falling edge delay chain control
    Scaler32SetDWord(PB08004_58_DQS_IN_DLY_2, 0x0E0E0D0E); // FRC Mode
    Scaler32SetDWord(PB08004_60_DQS_IN_DLY_3, 0x0E0E0E0D);
    Scaler32SetDWord(PB08004_5C_DQS_IN_DLY_2, 0x0F0F0F0F);
    Scaler32SetDWord(PB08004_64_DQS_IN_DLY_3, 0x0F100F10);

#elif(_MEMORY_DATA_RATE_SPEED <= _DDR3_DATA_RATE_1866M)
    // RDQ delay tap - DQS_IN raising edge delay chain control
    Scaler32SetDWord(PB08004_40_DQS_IN_DLY_0, 0x0E0E0E0F); // FRC Mode
    Scaler32SetDWord(PB08004_48_DQS_IN_DLY_1, 0x0F0F0F0E);
    Scaler32SetDWord(PB08004_44_DQS_IN_DLY_0, 0x11121011);
    Scaler32SetDWord(PB08004_4C_DQS_IN_DLY_1, 0x11121111);
    // RDQ delay tap - DQS_IN falling edge delay chain control
    Scaler32SetDWord(PB08004_58_DQS_IN_DLY_2, 0x0F0F0E0F); // FRC Mode
    Scaler32SetDWord(PB08004_60_DQS_IN_DLY_3, 0x10100F0F);
    Scaler32SetDWord(PB08004_5C_DQS_IN_DLY_2, 0x10111011);
    Scaler32SetDWord(PB08004_64_DQS_IN_DLY_3, 0x10111011);


#endif // End of #if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M)

    // Triger all DLL setting
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x0000000C); // fw_set_rd_dly
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x00000030); // fw_set_cal_rang
    Scaler32SetDWord(PB08002_3C_DPI_CTRL_1, 0x00000003); // fw_set_wr_dly
    Scaler32SetBit(PB08002_40_DPI_CTRL_2, ~_BIT28, 0x10000000);
    Scaler32SetDWord(PB08002_38_DPI_CTRL_0, 0x002E2004); // [1:0]fw_set_mode = 'b00 (during no read)
}
#endif // End of #if(_HW_MEMORY_DDR3_DPIDLL_GEN_TYPE == _MEMORY_DDR3_DPIDLL_GEN_1)

#if(_DDR3_KGD_DCC_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Config DDR3 KFG into DCC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3KGDDCCOff(void)
{
    WORD usNOPNum = 0;

    // DDR3 WINBOND KGD Test Mode : DCC OFF
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x000604CA);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 3; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00060CA3);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 3; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x000608DC);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 3; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x000604CA);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 3; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00060180);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 3; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00060380);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E83);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E8D);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E8F);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061AAF);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E8F);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00060F8F);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E8F);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E8F);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E8F);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E8F);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
    Scaler32SetDWord(PB08200_44_MOD_REG, 0x00061E80);
    Scaler32SetDWord(PB08200_40_DC_DDR3_CTL, 0x1000400C); // MR0 CMD
    for(usNOPNum = 0; usNOPNum < 63; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }

    for(usNOPNum = 0; usNOPNum < 1000; usNOPNum++)
    {
        ScalerSetByte(P37_00_MCU_DC_CMD, 0x00); // NOP CMD
    }
}
#endif // End of #if(_DDR3_KGD_DCCOFF_SUPPORT == _ON)

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

