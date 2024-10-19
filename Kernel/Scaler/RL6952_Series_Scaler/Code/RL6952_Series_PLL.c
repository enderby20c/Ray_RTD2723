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
// ID Code      : RL6952_Series_PLL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "PLL/ScalerPLL.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
DWORD g_ulPLLFifoRateMode;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PLL Control in Fake_PS Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLFakePowerSavingControl(void)
{
    // Disable All PLL

    // MPLL OFF
    ScalerSetBit(P1_32_MPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

    // Turn-OFF Memory PLL
    ScalerMemoryDevicePLLEnableControl(_DISABLE);

    // GDI M2PLL Can not be OFF!!!
    // ScalerSetBit(P1_58_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // Display PLL OFF
    ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

    // DSC0 DPLL OFF
    ScalerSetBit(P55_A8_DSCPLL_CONTROL, ~_BIT0, _BIT0);

    // DSC1 DPLL OFF
    ScalerSetBit(PF6_A8_DSCPLL_CONTROL, ~_BIT0, _BIT0);

    // D3 HDMI DPLL OFF
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // D4 HDMI DPLL OFF
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // D3 Audio N.F PLL OFF
    ScalerSetBit(P72_87_PORT_PAGE72_HDMI_DPLL_ANASET_1, ~_BIT0, _BIT0);

    // D4 Audio N.F PLL OFF
    ScalerSetBit(P73_87_PORT_PAGE73_HDMI_DPLL_ANASET_1, ~_BIT0, _BIT0);

    // D0 DP1.4 PLL OFF
    ScalerSetBit(PB5_A8_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // D0 DP Audio PLL OFF
    // Already Close in Audio Flow
    // ScalerSetBit(PB6_D8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);

    // D1 DP1.4 PLL OFF
    ScalerSetBit(PB8_A8_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // D1 DP Audio PLL OFF
    // Already Close in Audio Flow
    // ScalerSetBit(PB9_D8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);

    // D2 DP1.4 PLL OFF
    ScalerSetBit(PC6_A8_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // D2 DP Audio PLL OFF
    // Already Close in Audio Flow
    // ScalerSetBit(PC7_D8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);

    // Audio DAC PLL OFF
    // Already Close in Audio Flow
    // ScalerSetBit(PBF_A8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);
}

#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : Set Display Interface PLL: Frequency, VCO Band
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDisplayPLL(DWORD ulFreq)
{
    BYTE ucDispPhaseBand = 0x00;
    BYTE ucDispVcoBand = 0x00;

    PDATA_DWORD(0) = (ulFreq >> GET_D_DOMAIN_PATH());

    // LVDS data rate = ((Pixel Clk) / (LVDS Outport)) * 7
    PDATA_DWORD(1) = ((PDATA_DWORD(0) << GET_D_DOMAIN_PATH()) / (1 << _PANEL_LVDS_OUTPUT_PORT)) * 7;

    // ----------- Previous Select Band & Div Alg. -----------
    // LVDS PI Operation Frequency Seletcion
    if(PDATA_DWORD(1) < 250000)
    {
        ucDispPhaseBand = 0;
    }
    else if(PDATA_DWORD(1) < 400000)
    {
        ucDispPhaseBand = _BIT5;
    }
    else if(PDATA_DWORD(1) < 600000)
    {
        ucDispPhaseBand = _BIT6;
    }
    else
    {
        ucDispPhaseBand = (_BIT6 | _BIT5);
    }

    // LVDS_PLL_VCO Band Select
    if(PDATA_DWORD(1) < 105000)
    {
        ucDispVcoBand = (_BIT6 | _BIT5);
    }
    else if(PDATA_DWORD(1) < 210000)
    {
        ucDispVcoBand = _BIT6;
    }
    else if(PDATA_DWORD(1) < 420000)
    {
        ucDispVcoBand = _BIT5;
    }
    else
    {
        ucDispVcoBand = 0;
    }

    // ----------- Set Display VCO Band -----------
    // Manual set LVDS VCO band
    ScalerDisplayLvdsSetVcoBand(ucDispVcoBand);

    // Set LVDS PI Operation band
    ScalerDisplayLvdsSetPhaseBand(ucDispPhaseBand);
}
#endif

#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
//--------------------------------------------------
// Description  : Reset DPTX PLL Setting, Disable DPTX PLL Spread Spectrum Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLDPTxPLLReset(void)
{
    if(Scaler32GetBit(PB58050_10_DP1P3_TX_CMU11, _BIT13) != 0x00)
    {
        // Disable SSC
        // ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT5, 0x00);
        Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT13, 0x00);

        // SSC Off stable
        ScalerTimerDelayXms(2);
    }
    // Disable CMU Power
    // ScalerSetBit(P38_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);
    Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT15 | _BIT13 | _BIT10 | _BIT9 | _BIT8), 0x00);

    // Disabe DP TX Power
    // ScalerSetBit(P38_A0_DPTX_PHY_CTRL0, ~_BIT7, 0x00);
    Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~_BIT15, 0x00);
}

//--------------------------------------------------
// Description  : Set DPLL Referenced DPTX PLL: Frequency, VCO Band
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLRefPLL(DWORD ulFreq)
{
    WORD usNCode = 0;
    DWORD ulFCode = 0;
    DWORD ulCMUFreq = 0;

    g_ulPLLFifoRateMode = 0x00;

#if(_PANEL_STYLE == _PANEL_VBO)

    ulCMUFreq = (ulFreq * _PANEL_VBO_BYTE_MODE * 10) / _PANEL_VBO_OUTPUT_PORT;

    Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT14, _BIT14);

    if(Scaler32GetBit(PB58050_00_DP14_TX_CMU0, _BIT15) == 0x00)
    {
        // Disable SSC Function
        Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT13, 0x00);
    }

#elif(_PANEL_STYLE == _PANEL_DPTX)

    if(Scaler32GetBit(PB58050_00_DP14_TX_CMU0, _BIT15) == _BIT15)
    {
        return;
    }

    ulFreq = ulFreq;

    // HBR2 = 5.4GHz, HBR = 2.7GHz, RBR = 1.62GHz
    if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_RBR)
    {
        ulCMUFreq = _DPTX_PHY_RATE_RBR;
        DebugMessageCheck("ulCMUFreq---_DPTX_PHY_RATE_RBR--FRED", ulCMUFreq);
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR)
    {
        ulCMUFreq = _DPTX_PHY_RATE_HBR;
        DebugMessageCheck("ulCMUFreq---_DPTX_PHY_RATE_HBR--FRED", ulCMUFreq);
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
    {
        ulCMUFreq = _DPTX_PHY_RATE_HBR2;
        DebugMessageCheck("ulCMUFreq---_DPTX_PHY_RATE_HBR2--FRED", ulCMUFreq);
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR3)
    {
        ulCMUFreq = _DPTX_PHY_RATE_HBR3;
        DebugMessageCheck("ulCMUFreq---_DPTX_PHY_RATE_HBR3--FRED", ulCMUFreq);
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR3_9G)
    {
        ulCMUFreq = _DPTX_PHY_RATE_HBR3_9G;
        DebugMessageCheck("ulCMUFreq---_DPTX_PHY_RATE_HBR3_9G--FRED", ulCMUFreq);
    }

    // Set Down SSC
    Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT14, 0x00);

    // Disable SSC Function
    Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT13, 0x00);

#endif

    // Enable power ibias
    Scaler32SetBit(PB58060_08_DP14_TX_IBHN_TRIM, ~_BIT23, _BIT23);

    // Enable Power of DPTX, CMU LDO Enable
    Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~_BIT15, _BIT15);

    // Wait for CMU LDO Stable
    ScalerTimerDelayXms(2);

    // Divider for Postdivider of CMU and Pre-divder of CMU
    Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT13 | _BIT10 | _BIT9 | _BIT8), 0x00);

    // [23] Duty cycle correction circuit enable
    // [22:21] 00:small kvco, 01:big kvco
    // [6] 0:with PI, 1:bypass PI
    // [5:3] PI Current setting
    // [1:0] Duty cycle correction circuit current selection
    Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT23 | _BIT22 | _BIT21 | _BIT13 | _BIT10 | _BIT9 | _BIT8 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

    if(ulCMUFreq > _DPTX_PLL_BOUNDRY_4)
    {
        // Phy range = 6~9 GHz
        ulCMUFreq = ulCMUFreq / 4;

        // VCO = 1.5~3 GHz, spdsel = div1
        // ScalerSetBit(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ~(_BIT1 | _BIT0), 0x00);
        // Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17), 0x00);
        Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17 | _BIT13 | _BIT10 | _BIT9 | _BIT8), 0x00);

        // [18:16] CMU'S LPF Rs
        // [7:2] CMU'S CP Current
        // Rs=10k, Icp=100uA
        Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~(_BIT18 | _BIT17 | _BIT16 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT18 | _BIT16 | _BIT6 | _BIT4 | _BIT3 | _BIT2));
        DebugMessageCheck("ulCMUFreq---_DPTX_PLL_BOUNDRY_4--FRED", ulCMUFreq);
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_3)
    {
        // Phy range = 3~6 GHz
        ulCMUFreq = ulCMUFreq / 2;

        // VCO = 1.5~3 GHz, spdsel = div1
        // ScalerSetBit(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ~(_BIT1 | _BIT0), 0x00);
        // Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17), 0x00);
        Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17 | _BIT13 | _BIT10 | _BIT9 | _BIT8), 0x00);

        // [18:16] CMU'S LPF Rs
        // [7:2] CMU'S CP Current
        // Rs=10k, Icp=100uA
        Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~(_BIT18 | _BIT17 | _BIT16 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT18 | _BIT16 | _BIT6 | _BIT4 | _BIT3 | _BIT2));
        DebugMessageCheck("ulCMUFreq---_DPTX_PLL_BOUNDRY_3--FRED", ulCMUFreq);
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_2)
    {
        // Phy range = 1.5 ~ 3 GHz
        ulCMUFreq = ulCMUFreq * 1;

        // VCO = 1.5~3 GHz, spdsel = div2
        // ScalerSetBit(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ~(_BIT1 | _BIT0), _BIT0);
        // Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17), _BIT17);
        Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17 | _BIT13 | _BIT10 | _BIT9 | _BIT8), _BIT17);

        // [18:16] CMU'S LPF Rs
        // [7:2] CMU'S CP Current
        // Rs=10k, Icp=100uA
        Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~(_BIT18 | _BIT17 | _BIT16 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT18 | _BIT16 | _BIT6 | _BIT4 | _BIT3 | _BIT2));
        DebugMessageCheck("ulCMUFreq---_DPTX_PLL_BOUNDRY_2--FRED", ulCMUFreq);
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_1)
    {
        // Phy range = 1.5 ~ 3 GHz
        ulCMUFreq = ulCMUFreq * 1;

        // VCO = 3~6 GHz, spdsel = div2
        Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17 | _BIT13 | _BIT10 | _BIT9 | _BIT8), _BIT17);

        // [18:16] CMU'S LPF Rs
        // [7:2] CMU'S CP Current
        // Rs=10k, Icp=100uA
        Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~(_BIT18 | _BIT17 | _BIT16 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT18 | _BIT16 | _BIT6 | _BIT4 | _BIT3 | _BIT2));
        DebugMessageCheck("ulCMUFreq---_DPTX_PLL_BOUNDRY_1--FRED", ulCMUFreq);
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_0)
    {
        // Phy range = 0.75 ~ 1.5 GHz
        ulCMUFreq = ulCMUFreq * 2;

        // VCO = 3~6 GHz, spdsel = div4
        Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17 | _BIT13 | _BIT10 | _BIT9 | _BIT8), _BIT18);

        // [18:16] CMU'S LPF Rs
        // [7:2] CMU'S CP Current
        // Rs=10k, Icp=100uA
        Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~(_BIT18 | _BIT17 | _BIT16 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT18 | _BIT16 | _BIT6 | _BIT4 | _BIT3 | _BIT2));
        DebugMessageCheck("ulCMUFreq---_DPTX_PLL_BOUNDRY_0--FRED", ulCMUFreq);
    }
    else
    {
        // VCO = 375 ~ 750 MHz
        ulCMUFreq = ulCMUFreq * 4;

        // VCO = 1.5~3 GHz, spdsel = div8
        Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT18 | _BIT17 | _BIT13 | _BIT10 | _BIT9 | _BIT8), (_BIT18 | _BIT17));

        // [18:16] CMU'S LPF Rs
        // [7:2] CMU'S CP Current
        // Rs=10k, Icp=100uA
        Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~(_BIT18 | _BIT17 | _BIT16 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT18 | _BIT16 | _BIT6 | _BIT4 | _BIT3 | _BIT2));
        DebugMessageCheck("ulCMUFreq---ELSE--FRED", ulCMUFreq);
    }

    DebugMessageCheck("ulCMUFreq-----FRED", ulCMUFreq);

    // Count N.F Code
    usNCode = ulCMUFreq / (_EXT_XTAL * 2) - 4;
    ulFCode = ulCMUFreq % (_EXT_XTAL * 2);

    DebugMessageCheck("usNCode-----FRED", usNCode);
    DebugMessageCheck("ulFCode-----FRED", ulFCode);

    if(ulFCode != 0)
    {
        // ulCMUFreq = ((DWORD) ulFCode << 20);
        ulCMUFreq = ((DWORD) ulFCode << 14);

        DebugMessageCheck("ulCMUFreq---XX--FRED", ulCMUFreq);

        // ulFCode = ulCMUFreq / (_EXT_XTAL * 2);
        ulFCode = ulCMUFreq / (_EXT_XTAL * 2);
        ulFCode = ulFCode << 6;
        DebugMessageCheck("ulFCode---XX--FRED", ulFCode);
    }

    // N Code = 9 bit
    // F Code = 20 bit
    usNCode &= 0x1FF;
    ulFCode &= 0xFFFFF;

    DebugMessageCheck("usNCode--2---FRED", usNCode);
    DebugMessageCheck("usFCode---2--FRED", ulFCode);

    Scaler32SetByte(PB58050_1C_DP1P3_TX_CMU23, 0x00, (BYTE)ulFCode);
    Scaler32SetDWord(PB58050_18_DP1P3_TX_CMU19, (((DWORD)((ulFCode >> 8) & 0xFF) << 24) | ((DWORD)(((usNCode << 4) & 0xFF) | ((ulFCode >> 16) & 0xFF)) << 16) | (WORD)((((_BIT7) | (usNCode >> 4)) & 0xFF) << 8)));

    // [15] cmu enable
    // [1:0] duty cycle correction circuit current selection
    Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT15 | _BIT14 | _BIT13 | _BIT10 | _BIT9 | _BIT8 | _BIT1 | _BIT0), (_BIT15 | _BIT14 | _BIT1));

    // Enable D2A Link Clock
    Scaler32SetBit(PB58030_00_VBY1_EDPTX_CLOCK_GEN, ~_BIT5, _BIT5);

    // Wait for CMU Stable
    ScalerTimerDelayXms(2);

    // Enable Watch Dog
    Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT15, _BIT15);

    // Wait Watch Dog to check PLL is stable or not
    ScalerTimerPollingFlagProc32Bit(2, PB58050_10_DP1P3_TX_CMU11, _BIT7, _TRUE);

    // Disable WD
    Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT15, 0X00);
}

#endif

