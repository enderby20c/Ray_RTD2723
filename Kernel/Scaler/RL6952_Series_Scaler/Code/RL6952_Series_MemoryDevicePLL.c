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
// ID Code      : RL6952_Series_MemoryDevicePLL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "MemoryDevicePLL/ScalerMemoryDevicePLL.h"

#if(_DDR3PLL_SSC_SUPPORT == _ON)
#warning "NOTE: DDR3PLL SSC support is ON, Memory BW may be affected. Please check with SD!!!"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructDDRPhaseInfo code tDdr3PllPi[] =
{
#if(_EMBEDDED_DDR3_PWR == _MEMORY_POWER_NORMAL)
// {PLL_PI0, PLL_PI1, PLL_PI2, AFIFO_STR_0, AFIFO_STR_1, AFIFO_STR_2}
// RL6952 1866MHz 1V5 New RDL
    {0x15150018, 0x00171D1A, 0x00000000, 0x00001111, 0x000C0012, 0x00001111},
// RL6952 2133MHz 1V5 New RDL
    {0x1717001B, 0x00191F1B, 0x00000000, 0x00001111, 0x000C0012, 0x00001111},
#elif(_EMBEDDED_DDR3_PWR == _MEMORY_POWER_LOW)
// RL6952 2133MHz & 1866MHz 1V35 Old RDL (Reserved parameters)
    {0x00000000, 0x00000808, 0x00000000, 0x11111111, 0x000C0011, 0x00001111}, // Default Phase
// RL6952 2133MHz & 1866MHz 1V5 New RDL (Reserved parameters)
    {0x00000000, 0x00000808, 0x00000000, 0x11111111, 0x000C0011, 0x00001111}, // Default Phase
#endif
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Memory Device PLL Enable Control
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerMemoryDevicePLLEnableControl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
        // Enable CLK output, Reset PLL, Enable PLL
        ScalerDDR3PowerControl(_ENABLE);
#endif
    }
    else
    {
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
        // Disable CLK output, Reset PLL, Disable PLL
        ScalerDDR3PowerControl(_DISABLE);
#endif
    }
}

//--------------------------------------------------
// Description  : Set Memory Device PLL Freq
// Input Value  : Target DDR Data Rate (KHz)
// Output Value : None
//--------------------------------------------------
void ScalerMemoryDevicePLLSetPLLFreq(DWORD ulFreq)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    // change DDR3 Data Rate to Clock Rate (Khz)
    ulFreq = ulFreq / 2;

    // release PLL LDO reset
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000009);

    // Clock Tree: dpi_pow_ldo_vco = 1b'1 (from LDO); VCO: dpi_pow_ldo_tree =  1b'1(from LDO)
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT27 | _BIT26 | _BIT25 | _BIT24), 0x06000000);

    // Clock tree power from DVDD
    Scaler32SetBit(PB08000_0C_PLL_CTL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0000000F);

    //===========================
    // PLL initial value setting
    //===========================

    // Set Icp = 0x07 , cco_kvco = 'b0 , reg_cco_band = 0x03 for CLK(HZ) at 1066MHz
    if(ulFreq >= 1100000)
    {
        pData[3] = 0x77;
    }
    else if((ulFreq < 1100000) && (ulFreq >= 750000))
    {
        pData[3] = 0x73;
    }
    else if((ulFreq < 750000) && (ulFreq >= 667000))
    {
        pData[3] = 0x76;
    }
    else if((ulFreq < 667000) && (ulFreq >= 500000))
    {
        pData[3] = 0x56;
    }
    else if((ulFreq < 500000) && (ulFreq >= 400000))
    {
        pData[3] = 0x54;
    }
    else
    {
        pData[3] = 0x50;
    }

    // Set LPF_SR '011, LPF_CP 'b1, loop_PI_Isel,
    if(ulFreq >= 1066000)
    {
        pData[2] = 0x56;
    }
    else if((ulFreq < 1066000) && (ulFreq >= 933000))
    {
        pData[2] = 0x55;
    }
    else if((ulFreq < 933000) && (ulFreq >= 667000))
    {
        pData[2] = 0x54;
    }
    else
    {
        pData[2] = 0x52;
    }

    // Set post_PI_bias[0], PLL_SEL_CPMODE,  PLL_LDO_Vsel 'b010, PreDiv 'b00
    if(ulFreq >= 667000)
    {
        pData[1] = 0xD8;
    }
    else
    {
        pData[1] = 0x58;
    }

    // Set V11_LDO_Vsel , CkRef_Sel = 1'b1=0(CKREF_PAD), post_PI_RS, post_PI_RL, post_PI_bias[1]
    if(ulFreq >= 10066000)
    {
        pData[0] = 0x64; // CLKREFPAD
    }
    else if((ulFreq < 1066000) && (ulFreq >= 933000))
    {
        pData[0] = 0x62;
    }
    else if((ulFreq < 933000) && (ulFreq >= 667000))
    {
        pData[0] = 0x60;
    }
    else
    {
        pData[0] = 0x64;
    }

    Scaler32SetDWord(PB08000_18_PLL_CTL3, (((DWORD)pData[0] << 24) | ((DWORD)pData[1] << 16) | ((DWORD)pData[2] << 8) | ((DWORD)pData[3])));

    // Set Ncode, Fcode
#if(_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_4)
    // _DDR_PLL_CLOCK, 1066M, 933M, 800M, 667M, 533M.
    if((ulFreq == ((DWORD)_FW_DDR_PLL_CLOCK * 1000)) && (_DDR_PLL_N_CODE != 0))
    {
        Scaler32SetBit(PB08000_28_SSC3, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8), ((DWORD)_DDR_PLL_N_CODE << 8));
        Scaler32SetBit(PB08000_24_SSC2, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28 | _BIT27 | _BIT26 | _BIT25 | _BIT24 | _BIT23 | _BIT22 | _BIT21 | _BIT20 | _BIT19 | _BIT18 | _BIT17 | _BIT16), ((DWORD)_DDR_PLL_F_CODE << 16));
    }
    else
#endif
    {
        //=============================================
        // Calculate Freq. & Set N F code & Disable SSC
        //=============================================
        BYTE ucNCode = 0;
        DWORD ulNCodeFreq = 0;
        DWORD ulFCode = 0;

        ucNCode = ulFreq / (DWORD)_EXT_XTAL;

        // Calculate DDRPLL Output Freq. According to current Settings
        ulNCodeFreq = (DWORD)_EXT_XTAL * 1000 * ucNCode;

        // Offset resolution (Dclk / 2^11) in Hz
        ulFCode = ((DWORD)_EXT_XTAL * 1000 + (1 << 10)) >> 11;

        // Target frequency of DDR clk in Hz
        ulFCode = ((ulFreq * 1000) - ulNCodeFreq / ulFCode);
        ulFCode = ulFCode & 0x3ff;

        // Set DDR PLL N code / Offset / SSC Enable bit
        ucNCode = ucNCode - ((ucNCode >= 3) ? 3 : 0);

        // Set Ncode
        Scaler32SetBit(PB08000_28_SSC3, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8), ((DWORD)ucNCode << 8));

        // Set Fcode
        Scaler32SetBit(PB08000_24_SSC2, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28 | _BIT27 | _BIT26 | _BIT25 | _BIT24 | _BIT23 | _BIT22 | _BIT21 | _BIT20 | _BIT19 | _BIT18 | _BIT17 | _BIT16), (ulFCode << 16));
    }

    // _DDR3_PLL_INITIAL_PHASE_0 = {ck[0],ck[1],ck[2],ck[3]}
    // _DDR3_PLL_INITIAL_PHASE_0 = {ck, cmd, dqs_0, dqs_1}

    // _DDR3_PLL_INITIAL_PHASE_1 = {ck[4],ck[5],ck[6], int_ck}
    // _DDR3_PLL_INITIAL_PHASE_1 = {dq_0, dq_1, mck_cs, int_ck}

    StructDDRPhaseInfo *pstDdr3PllPi = &tDdr3PllPi[0];

#if(_MEMORY_DATA_RATE_SPEED > _DDR3_DATA_RATE_1866M)
    if(ScalerDDR3GetDDROldRDLStatus() != _TRUE)
    {
        pstDdr3PllPi = &tDdr3PllPi[1]; // new RDL
    }
#endif

    // Set phase control
    ScalerMemoryDevicePLLWritePhase(pstDdr3PllPi);

    // Set WD disable
    Scaler32SetBit(PB08000_2C_WDOG, ~(_BIT0), 0x00000000);

    // Set SSC disable
    Scaler32SetBit(PB08000_1C_SSC0, ~(_BIT1), 0x00000000);

// (a) DCC initial value setting

    // Set DQS1 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_34_DCC_DQS, 0x15053833);

    // Set DQS2 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_38_DCC_DQS, 0x15053833);

    // Set DQS3 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_3C_DCC_DQS, 0x15053833);

    // Set DQS4 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_40_DCC_DQS, 0x15053833);

    // Set DQ1 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_44_DCC_DQ, 0x15053833);

    // Set DQ2 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_48_DCC_DQ, 0x15053833);

    // Set DQ3 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_4C_DCC_DQ, 0x15053833);

    // Set DQ4 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_50_DCC_DQ, 0x15053833);

    // Set CK_1 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_54_DCC_CK, 0x15053833);

    // Set CMD close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_30_DCC_CMD, 0x15053833);

    // Set CS close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_A4_DCC_CS, 0x15053833);

    // Set CS1 close loop mode, presetB 3, presetA 3
    Scaler32SetDWord(PB08000_A8_DCC_CS1, 0x15053833);


#if((_DDR3PLL_SSC_SUPPORT == _ON) && (_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_1066MHZ))
    // "NOTE: DDR3PLL SSC support is ON, Memory BW may be affected. Please check with SD!!!"
#if(_DDR3PLL_SSC_AMPLITUDE == _1_PERCENT)
    // Set Ncode = 8'd70
    Scaler32SetBit(PB08000_28_SSC3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000046);
    // Set Fcode = 11'd1398
    Scaler32SetBit(PB08000_24_SSC2, ~(_BIT10 | _BIT9 | _BIT8 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000576);
    // Set gran = 19'd14845 & dot_gran=3'b100
    Scaler32SetDWord(PB08000_20_SSC1, 0x00C039FD);
#elif(_DDR3PLL_SSC_AMPLITUDE == _2_PERCENT)
    // Set Ncode = 8'd69
    Scaler32SetBit(PB08000_28_SSC3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000045);
    // Set Fcode = 11'd1872
    Scaler32SetBit(PB08000_24_SSC2, ~(_BIT10 | _BIT9 | _BIT8 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00000750);
    // Set gran = 19'd29700 & dot_gran=3'b100
    Scaler32SetDWord(PB08000_20_SSC1, 0x00C07404);
#endif

#elif((_DDR3PLL_SSC_SUPPORT == _ON) && (_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_933MHZ))
#if(_DDR3PLL_SSC_AMPLITUDE == _1_PERCENT)
    // Set Ncode = 8'd61
    Scaler32SetBit(PB08000_28_SSC3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0000003D);
    // Set Fcode = 11'd949
    Scaler32SetBit(PB08000_24_SSC2, ~(_BIT10 | _BIT9 | _BIT8 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x000003B5);
    // Set gran = 19'd13505 & dot_gran=3'b100, 33K
    Scaler32SetDWord(PB08000_20_SSC1, 0x00C034C1);
#elif(_DDR3PLL_SSC_AMPLITUDE == _2_PERCENT)
    // Set Ncode = 8'd60
    Scaler32SetBit(PB08000_28_SSC3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0000003C);
    // Set Fcode = 11'd1712
    Scaler32SetBit(PB08000_24_SSC2, ~(_BIT10 | _BIT9 | _BIT8 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x000006B0);
    // Set gran = 19'd25642 & dot_gran=3'b100, 33K
    Scaler32SetDWord(PB08000_20_SSC1, 0x00C0642A);
#endif

#else
    // Set SSC disable
    Scaler32SetBit(PB08000_1C_SSC0, ~(_BIT1), 0x00000000);
#endif

// ( b ) DPI initial value setting

    // Set mode & pin mux setting (choose one mode), zq_ddr3_mode, ca_ddr3_mode
    Scaler32SetDWord(PB08000_00_CRT_CTL, 0x0C081831);// RL6952 modify

    // Release SSC NFCODE sync_reset Set rst_n = 1, b1 & ptr_rst_n = 1'b1
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT1), 0x00000002);

    // Enable mck_mc Set mck_mc_en = 1
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT31), 0x80000000);

    // Set ptr_rst_n = 1'b0
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3), 0x00000000);

    // Set rst_n = 1'b1
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT2), 0x00000004);

    // Set ptr_rst_n = 1'b1
    Scaler32SetBit(PB08000_8C_CRT_RST_CTL, ~(_BIT3), 0x00000008);

    // Set OC_EN, ensure N_code, F_code load successfully
    Scaler32SetBit(PB08000_28_SSC3, ~(_BIT26), 0x04000000);// OC_EN 0->1
    Scaler32SetBit(PB08000_28_SSC3, ~(_BIT26), 0x00000000);// OC_EN 1->0
    // Set Flag_initial = 1
    Scaler32SetBit(PB08000_1C_SSC0, ~(_BIT3), 0x00000008);

#if(_DDR3PLL_SSC_SUPPORT == _ON)
    // Set Flag_initial = 1 & en_ssc =1
    Scaler32SetBit(PB08000_1C_SSC0, ~(_BIT3 | _BIT1), 0x0000000A);
#endif

    // (d) Turn on clock flow
    // Set ICG_clk_en
    Scaler32SetBit(PB08000_04_PLL_CTL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0000007F);
    // Set clk_oe Enable
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT18 | _BIT17 | _BIT16), 0x00070000);

    ScalerTimerDelayXms(2);
    Scaler32SetDWord(PB08000_00_CRT_CTL, 0x04081031);// REL1108 Modify

    // Wait for DDR3PLL Stable (2ms)
    ScalerTimerDelayXms(2);

    // Debug
    DebugMessageDigital("6. DDR3PLL *** fvco=1066M, N=0x47, F=0x3E4 ***", 0);
    DebugMessageDigital("6. DDR3DPLL Ncode =", ((Scaler32GetDWord(PB08000_28_SSC3) & 0x0000FF00) >> 8));
    DebugMessageDigital("6. DDR3DPLL Fcode[10:0] =", ((Scaler32GetDWord(PB08000_24_SSC2) & 0xFFFF0000) >> 16));
    DebugMessageDigital("6. DDR3DPLL ~Freq(Mhz) ~=Xtal*Ncode=", (14318 * ((((Scaler32GetDWord(PB08000_28_SSC3)) & 0x0000FF00) >> 8) + 3 + ((Scaler32GetDWord(PB08000_24_SSC2) & 0xFFFF0000) >> 16) / 2048) / 1000));
    DebugMessageDigital("6. DDR3DPLL **********************", 0);
#endif
}

//--------------------------------------------------
// Description  : Set DDRPLL Write Phase
// Input Value  : _DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1
// Output Value : None
//--------------------------------------------------
void ScalerMemoryDevicePLLWritePhase(StructDDRPhaseInfo *pstDdrPhaseData)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    BYTE ucSyncSel = 0x00;
    BYTE pucPhaseOfClk[7];
    BYTE ucCmdRdStrNumSel = 0x00;

    // pstDdrPhaseData->ulDdrPllInitialPhase2 = pstDdrPhaseData->ulDdrPllInitialPhase2;
    // _DDR3_PLL_INITIAL_PHASE_0 = {ck[3],ck[2],ck[1],ck[0]}
    // _DDR3_PLL_INITIAL_PHASE_0 = {dqs_1, dqs_0, cmd, ck}
    Scaler32SetDWord(PB08000_10_PLL_PI0, pstDdrPhaseData->ulDdrPllInitialPhase0);

    // _DDR3_PLL_INITIAL_PHASE_1 = {int_ck, ck[6],ck[5],ck[4]}
    // _DDR3_PLL_INITIAL_PHASE_1 = {int_ck, mck_cs, dq_1, dq_0}
    Scaler32SetDWord(PB08000_14_PLL_PI1, pstDdrPhaseData->ulDdrPllInitialPhase1);

    // valid phase range: 0~31
    pucPhaseOfClk[0] = (BYTE)(pstDdrPhaseData->ulDdrPllInitialPhase0 >> 0) & 0x1F; // CK
    pucPhaseOfClk[1] = (BYTE)(pstDdrPhaseData->ulDdrPllInitialPhase0 >> 8) & 0x1F; // CMD
    pucPhaseOfClk[2] = (BYTE)(pstDdrPhaseData->ulDdrPllInitialPhase0 >> 16) & 0x1F; // dqs_0
    pucPhaseOfClk[3] = (BYTE)(pstDdrPhaseData->ulDdrPllInitialPhase0 >> 24) & 0x1F; // dqs_1

    pucPhaseOfClk[4] = (BYTE)(pstDdrPhaseData->ulDdrPllInitialPhase1 >> 0) & 0x1F; // dq_0
    pucPhaseOfClk[5] = (BYTE)(pstDdrPhaseData->ulDdrPllInitialPhase1 >> 8) & 0x1F; // dq_1
    pucPhaseOfClk[6] = (BYTE)(pstDdrPhaseData->ulDdrPllInitialPhase1 >> 16) & 0x1F; // mck_cs

    // DDR PLL sync select setting
    // Fast version of "if((16 <= phase <= 31) OR (48 <= phase <= 63)), then corresponding SyncSel bit is set to 1"
    ucSyncSel |= (((pucPhaseOfClk[0] & _BIT4) == _BIT4) ? _BIT0 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[1] & _BIT4) == _BIT4) ? _BIT1 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[2] & _BIT4) == _BIT4) ? _BIT2 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[3] & _BIT4) == _BIT4) ? _BIT3 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[4] & _BIT4) == _BIT4) ? _BIT4 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[5] & _BIT4) == _BIT4) ? _BIT5 : 0x00);
    ucSyncSel |= (((pucPhaseOfClk[6] & _BIT4) == _BIT4) ? _BIT6 : 0x00);

    // Set oesync_op_sel
    Scaler32SetBit(PB08000_08_PLL_CTL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucSyncSel);

    // DDR FIFO Threshold
    Scaler32SetDWord(PB08000_80_AFIFO_STR_0, pstDdrPhaseData->ulDdrTxFifoStr0); // DQS,DQ TX FIFO threshold setting
    Scaler32SetBit(PB08000_84_AFIFO_STR_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), pstDdrPhaseData->ulDdrTxFifoStr1); // CMD TX FIFO threshold setting
    Scaler32SetDWord(PB08000_88_AFIFO_STR_2, pstDdrPhaseData->ulDdrRxFifoStr2); // RX FIFO threshold setting

    if((pstDdrPhaseData->ulDdrTxFifoStr1 & 0x000000FF) == 0x00000012)
    {
        ucCmdRdStrNumSel = 0x03;
    }
    else
    {
        ucCmdRdStrNumSel = 0x00;
    }
    Scaler32SetDWord(PB08000_94_AFIFO_STR_SEL, ((DWORD)(ucCmdRdStrNumSel << 28))); // [28:29]CS : cmd_ex_rd_str_num : cs and cmd same threshold

#endif
}

