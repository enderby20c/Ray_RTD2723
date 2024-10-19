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
// ID Code      : ScalerPLL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_PLL__

#include "ScalerFunctionInclude.h"
#include "PLL/ScalerPLL.h"

#if(_HW_EPLL_SUPPORT == _ON)
#if(_EMCUPLL_NF_N < 5)
#warning "_EMCUPLL_NF_N Should Be >= 5!!!"
#endif
#endif

#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#if(_M2PLL_NF_N < 5)
#warning "_M2PLL_NF_N Should Be >= 5!!!"
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
StructAdjustApllData g_stPLLApllData;
#endif



//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_EPLL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : EMCUPLL Off COntrol.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetEMCUPLLOffProc(void)
{
    // Power Off EMCUPLL
    ScalerSetBit(P23_08_EMCU_PLL_CONTROL, ~_BIT0, _BIT0);

    // Reserved for Set LDO Disable

    // rs=b'001=6.5k, cs=b'11=66pF, Ic =b'010=7.5uA
    ScalerSetByte(P23_06_EMCU_PLL_0, ((1 << 5) | (3 << 3) | (2 << 0)));

    // vco mode , ipi=2'b00=2.5uA, No LDO
    ScalerSetBit(P23_07_EMCU_PLL_1, ~(_BIT7 | _BIT1 | _BIT0), _BIT7);

    // Set preDiv byPass, Output Div1
    ScalerSetBit(P23_05_EMCU_PLL_DIVIDER1, ~(_BIT7 | _BIT1 | _BIT0), _BIT7);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(P23_08_EMCU_PLL_CONTROL, ~_BIT1, (_HW_DPLL_VCORSTB_NORMAL_VALUE << 1));

    // Set CP Enable, close loop. Set Vc, Set LPF Enable
    ScalerSetBit(P23_0A_EMCU_PLL_DUMMY, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT0));

    // Set PLL Double Buffer
    ScalerSetBit(P23_03_PLL_IN_CONTROL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : EMCUPLL On COntrol.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetEMCUPLLOnProc(void)
{
    // Set LDO Enable
//Need to be modified,    ScalerSetBit(P23_09_EMCU_PLL_LDO, ~_BIT7, _BIT7);

    // Power On EMCUPLL
    ScalerSetBit(P23_08_EMCU_PLL_CONTROL, ~_BIT0, 0x00);

    // Wait for LDO Stable (>40us)
    DELAY_XUS(150);

    // Set VCO/4 Enable
    ScalerSetBit(P23_08_EMCU_PLL_CONTROL, ~_BIT7, _BIT7);

    // Check if NCode >= 5
#if((_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_354M) ||\
    (_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_480M))
    // Set EMCUPLL N Code
    ScalerSetByte(P23_0D_N_F_CODE_1, (_EMCUPLL_NF_N - 2));

    // Set EMCUPLL F Code
    ScalerSetByte(P23_10_N_F_CODE_4, ((_EMCUPLL_NF_F & 0x000FF) >> 0));
    ScalerSetByte(P23_0F_N_F_CODE_3, ((_EMCUPLL_NF_F & 0x0FF00) >> 8));
    ScalerSetByte(P23_0E_N_F_CODE_2, ((_EMCUPLL_NF_F & 0xF0000) >> 16));
#endif
    // Set N.F Double Buffer
    ScalerSetBit(P23_0C_N_F_CODE_0, ~_BIT0, _BIT0);

    // Wait for EMCUPLL Stable (1ms)
    DELAY_XUS(1000);

    // Debug
#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_354M)
    DebugMessageDigital("6. EMCUPLL *** fvco=354M, N=0x18, F=0xB77CD ***", 0);
#endif
#if(_HW_CPU32_CLK_SRC_EMCU_PLL == _EMCU_PLL_SPEED_480M)
    DebugMessageDigital("6. EMCUPLL *** fvco=480M, N=0x21, F=0x86344 ***", 0);
#endif
    DebugMessageDigital("6. EMCUPLL     Ncode =", (ScalerGetByte(P23_0D_N_F_CODE_1) + 2));
    DebugMessageDigital("6. EMCUPLL Reg_Fcode[7:0] =", ScalerGetByte(P23_10_N_F_CODE_4));
    DebugMessageDigital("6. EMCUPLL Reg_Fcode[15:8] =", ScalerGetByte(P23_0F_N_F_CODE_3));
    DebugMessageDigital("6. EMCUPLL Reg_Fcode[19:16] =", (ScalerGetByte(P23_0E_N_F_CODE_2) & 0x0F));
    DebugMessageDigital("6. EMCUPLL ~Freq(Mhz) ~=Xtal*Ncode=", ((DWORD)14318 * (ScalerGetByte(P23_0D_N_F_CODE_1) + 2) / 1000));
    DebugMessageDigital("6. EMCUPLL **********************", 0);
}

//--------------------------------------------------
// Description  : EMCUPLL Power COntrol.
// Input Value  : ucOn    --> ON/OFF.
// Output Value : None
//--------------------------------------------------
void ScalerPLLEMCUPLLPower(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        ScalerPLLSetEMCUPLLOffProc();
        ScalerPLLSetEMCUPLLOnProc();
    }
    else
    {
        // Power Off EMCUPLL
        ScalerSetBit(P23_08_EMCU_PLL_CONTROL, ~_BIT0, _BIT0);
    }
}
#endif // #if(_EPLL_SUPPORT == _ON)


#if((_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
//--------------------------------------------------
// Description  : Calculate N.F Parameter
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
DWORD ScalerPLLCalNFCode(DWORD ulFreq, DWORD ulRefClk, BYTE ucPreDiv, BYTE ucPixelDiv2_DIV, EnumPLLSel enumPLLSel, EnumDclkChg enumDclkChg)
{
    BYTE ucPostDiv = 0;
    BYTE ucNcode = 0;
    BYTE ucFcode_MSB4b = 0;
    WORD usFcode_LSB16b = 0;
    DWORD ulvcoFreq = 0;
    BYTE ucHigh_Freq = 0;

    if((enumPLLSel == _DPLL_NF_PLL) && (enumDclkChg == _PLL_FREQ_CHG_UNDER_10PER))
    {
        // Get Postdiv,
        ucPostDiv = ((ScalerGetByte(P1_D0_DPLL_ANALOG_SETTING_0) & 0x60) >> 5);
        ulvcoFreq = ulFreq << ucPostDiv << (1 - ucPixelDiv2_DIV);
    }
    else
    {
        PDATA_DWORD(1) = ulFreq * 8;

        if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_0)
        {
            ucPostDiv = 3;
        }
        else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_1)
        {
            ucPostDiv = 2;
        }
        else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_2)
        {
            ucPostDiv = 1;
        }
        else if(PDATA_DWORD(1) <= _DPLL_BOUNDRY_3)
        {
            ucPostDiv = 0;
        }
        else
        {
            ucPostDiv = 0;
            ucHigh_Freq = 0;// Set High_Freq Enable for 55NFPLL
        }

        // Calculate N.F
        // Fvco = (RefClk / PreDiv) * N.F = (RefClk / PreDiv) * (N + F/2^20) = ulFreq * PostDiv
        // NFcode = ulFreq * Postdiv * ucPreDiv / RefClk
        ulvcoFreq = ulFreq << ucPostDiv << (1 - ucPixelDiv2_DIV);
    }


    if((enumPLLSel == _DPLL_NF_PLL) && (_PANEL_STYLE == _PANEL_VBO))
    {
        ucNcode = _PANEL_VBO_OUTPUT_PORT << ((ScalerGetBit(P1_BF_DPLL_CLK_CTRL_0, (_BIT3 | _BIT2)) >> 2) + 1) << ucPostDiv >> GET_D_DOMAIN_PATH();
        ucFcode_MSB4b = 0x00;
        usFcode_LSB16b = 0x00;
    }
    else
    {
        ucNcode = ulvcoFreq * ucPreDiv / ulRefClk;
        ucFcode_MSB4b = ((ulvcoFreq * ucPreDiv - ((DWORD)ulRefClk) * ucNcode) << 4) / ulRefClk;
        usFcode_LSB16b = ((((ulvcoFreq * ucPreDiv - ((DWORD)ulRefClk) * ucNcode) << 4) - ucFcode_MSB4b * ulRefClk) << 16) / ulRefClk;
    }

    // Debug
    DebugMessageDigital("6. *** CalNFcode ***", 0);
    DebugMessageDigital("6.  GET_D_DOMAIN_PATH() =", GET_D_DOMAIN_PATH());
    DebugMessageDigital("6.  RefClk =", ulRefClk);
    DebugMessageDigital("6.  Freq =", ulFreq);
    DebugMessageDigital("6.  ucPostDiv =", ucPostDiv);
    DebugMessageDigital("6.  ulvcoFreq =", ulvcoFreq);
    DebugMessageDigital("6.  ucNcode =", ucNcode);
    DebugMessageDigital("6.  ucFcode_MSB4b =", ucFcode_MSB4b);
    DebugMessageDigital("6.  usFcode_LSB16b =", usFcode_LSB16b);

    return ((((DWORD)(ucHigh_Freq & 0x01)) << 30) |
            (((DWORD)(ucPostDiv & 0x03)) << 28) |
            (((DWORD)(ucNcode)) << 20) |
            (((DWORD)(ucFcode_MSB4b & 0x0F)) << 16) |
            ((DWORD)(usFcode_LSB16b)));
}

//--------------------------------------------------
// Description  : Calculate PLL Parameter
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
DWORD ScalerPLLCalPLLParameter(DWORD ulFreq, DWORD ulRefClk, BYTE ucPreDiv, BYTE ucPixelDiv2_DIV, EnumPLLSel enumPLLSel, EnumDclkChg enumDclkChg)
{
    BYTE ucPostDiv = 0;
    BYTE ucNcode = 0;
    DWORD ulvcoFreq = 0;
    BYTE ucIcp = 0;
    BYTE ucIpi = 0;
    BYTE ucHigh_Freq = 0;

    PDATA_DWORD(0) = ScalerPLLCalNFCode(ulFreq, ulRefClk, ucPreDiv, ucPixelDiv2_DIV, enumPLLSel, enumDclkChg);

    ucHigh_Freq = (BYTE)((PDATA_DWORD(0) & 0x40000000) >> 30);
    ucPostDiv = (BYTE)((PDATA_DWORD(0) & 0x30000000) >> 28);
    ucNcode = (BYTE)((PDATA_DWORD(0) & 0x0FF00000) >> 20);

    ulvcoFreq = ulFreq << ucPostDiv << (1 - ucPixelDiv2_DIV);

#if(_HW_NF_PLL_STRUCT_TYPE == _NF_PLL_GEN_0)
    // Icp = (1400 * loopDiv * 2 * pi)/(Kvco * Rs)
    // Rs = 4.5k + 2*_NFPLL_RS_SEL
    // _NFPLL_KVCO_for_ALL = 4000
    // Icp = (2.5uA+2.5uA*bit[5]+5uA*bit[6]+10uA*bit[7])

    PDATA_DWORD(0) = (ucNcode * 1400UL * 628 * 20) / _NFPLL_KVCO / ((45 + _NFPLL_RS_SEL * 20) * 100 / 10);
#elif(_HW_NF_PLL_STRUCT_TYPE == _NF_PLL_GEN_1)
    // Icp = loopDiv/4
    // Rs = 1k + 2*_NFPLL_RS_SEL

    PDATA_DWORD(0) = (ucNcode * 20 / 4);
#endif
    ucIcp = (PDATA_DWORD(0) + 25) / 50;
    ucIcp -= (ucIcp == 0) ? 0 : 1;

    // Get Ipi from freq.
    if(ulvcoFreq < 400000)
    {
        ucIpi = 0;
    }
    else if(ulvcoFreq < 500000)
    {
        ucIpi = 1;
    }
    else if(ulvcoFreq < 600000)
    {
        ucIpi = 2;
    }
    else
    {
        ucIpi = 3;
    }

    return ((((DWORD)(ucIpi & 0x03)) << 16) |
            (((DWORD)(ucIcp & 0x07)) << 8) |
            (((DWORD)(ucHigh_Freq & 0x01)) << 4) |
            ((DWORD)(ucPostDiv & 0x03)));
}
#endif // End of #if((_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))

//--------------------------------------------------
// Description  : System Clock Select From M2PLL Divider Control.
// Input Value  : ucDiv    --> Divider.
// Output Value : None
//--------------------------------------------------
void ScalerM2PLLDiv(BYTE ucDiv)
{
    // Internal Xtal Freq. From M2PLL divider
    ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), ucDiv << 3);
}

#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
//--------------------------------------------------
// Description  : M2PLL Off COntrol.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetM2PLLOffProc(void)
{
#if(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
#if(_EXT_XTAL == _XTAL14318K)
    // Power Off M2PLL
    ScalerSetBit(P1_58_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // Reserved for Set LDO Disable

    // Set Rs, Cs none, Icp
    ScalerSetByte(P1_56_M2PLL_0, (((_NFPLL_RS_SEL & 0x07) << 5) | _M2PLL_ICP));

    // Set Vco Mode, Ipi
    ScalerSetBit(P1_57_M2PLL_1, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _M2PLL_IPI));

    // Set preDiv byPass, Output Div1
    ScalerSetBit(P1_55_M2PLL_DIVIDER1, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _M2PLL_POSTDIV));

    // Set Pixel Output Div2
    ScalerSetBit(P1_52_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), _M2PLL_PIXELDIV);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(P1_58_M2PLL_CONTROL, ~_BIT1, (_HW_DPLL_VCORSTB_NORMAL_VALUE << 1));

    // Set CP Enable, close loop. Set Vc, Set LPF Enable
    ScalerSetBit(P1_5A_M2PLL_DUMMY, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT0));

    // Set PLL Double Buffer
    ScalerSetBit(P1_53_PLL_IN_CONTROL, ~_BIT0, _BIT0);
#endif
#endif
}

//--------------------------------------------------
// Description  : M2PLL On COntrol.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetM2PLLOnProc(void)
{
#if(_FW_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
#if(_EXT_XTAL == _XTAL14318K)
    // Reserved for Set LDO Enable

    // Power On M2PLL
    ScalerSetBit(P1_58_M2PLL_CONTROL, ~_BIT0, 0x00);

    // Wait for LDO Stable (>40us)
    DELAY_XUS(150);

    // Set VCO/4 Enable
    ScalerSetBit(P1_58_M2PLL_CONTROL, ~_BIT7, _BIT7);

    // Check if NCode >= 5

    // Set M2PLL N Code
    ScalerSetByte(P1_5D_N_F_CODE_1, (_M2PLL_NF_N - 2));

    // Set M2PLL F Code
    ScalerSetByte(P1_60_N_F_CODE_4, ((_M2PLL_NF_F & 0x000FF) >> 0));
    ScalerSetByte(P1_5F_N_F_CODE_3, ((_M2PLL_NF_F & 0x0FF00) >> 8));
    ScalerSetByte(P1_5E_N_F_CODE_2, ((_M2PLL_NF_F & 0xF0000) >> 16));

    // Set N.F Double Buffer
    ScalerSetByte(P1_5C_N_F_CODE_0, _BIT0);

    // Wait for M2PLL Stable (1ms)
    DELAY_XUS(1000);

    // Debug
    DebugMessageDigital("6. M2PLL *** fvco=351M, N=0x16+2, F=0x83BCD ***", 0);
    DebugMessageDigital("6. M2PLL *** fvco=702M, N=0x2F+2, F=0x07794 ***", 0);
    DebugMessageDigital("6. M2PLL     Ncode =", (ScalerGetByte(P1_5D_N_F_CODE_1) + 2));
    DebugMessageDigital("6. M2PLL Reg_Fcode[7:0] =", ScalerGetByte(P1_60_N_F_CODE_4));
    DebugMessageDigital("6. M2PLL Reg_Fcode[15:8] =", ScalerGetByte(P1_5F_N_F_CODE_3));
    DebugMessageDigital("6. M2PLL Reg_Fcode[19:16] =", (ScalerGetByte(P1_5E_N_F_CODE_2) & 0x0F));
    DebugMessageDigital("6. M2PLL ~Freq(Mhz) ~=Xtal*Ncode=", ((DWORD)14318 * (ScalerGetByte(P1_5D_N_F_CODE_1) + 2) / 1000));
    DebugMessageDigital("6. M2PLL **********************", 0);
#endif
#endif
}
#endif // End of #if(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)

//--------------------------------------------------
// Description  : M2PLL Power COntrol.
// Input Value  : ucOn    --> ON/OFF.
// Output Value : None
//--------------------------------------------------
void ScalerPLLM2PLLPower(BYTE ucOn)
{
    if(ucOn == _ON)
    {
#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
        ScalerPLLSetM2PLLOffProc();
        ScalerPLLSetM2PLLOnProc();
#endif
    }
    else
    {
        // Power Off M2PLL
        ScalerSetBit(P1_58_M2PLL_CONTROL, ~_BIT0, _BIT0);
    }
}

#if(_HW_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)
//--------------------------------------------------
// Description  : MPLL Power COntrol.
// Input Value  : ucOn    --> ON/OFF.
// Output Value : None
//--------------------------------------------------
void ScalerPLLMPLLPower(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Set MPLL CLK
        ScalerPLLSetMPLLFreq((DWORD)_MEMORY_PLL_CLOCK * 1000);
    }
    else
    {
        // Power Down  MPLL
        ScalerSetBit(P1_32_MPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Set memory clock(Mclk) frequency in kHz
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetMPLLFreq(DWORD ulFreq)
{
    DWORD ulRefClk = _EXT_XTAL;

    ScalerPLLSetMPLLOffProc(ulFreq, ulRefClk);
    ScalerPLLSetMPLLOnProc(ulFreq, ulRefClk);
}

//--------------------------------------------------
// Description  : MPLL Off COntrol.
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetMPLLOffProc(DWORD ulFreq, DWORD ulRefClk)
{
    BYTE ucPostDiv = 0;
    BYTE ucIcp = 0;
    BYTE ucIpi = 0;

    // calculate postDiv, Icp, Ipi
    PDATA_DWORD(0) = ScalerPLLCalPLLParameter(ulFreq, ulRefClk, _MPLL_PREDIV_DIV, _MPLL_PIXELDIV2_DIV, _MPLL_NF_PLL, _PLL_FREQ_CHG_OVER_10PER);

    ucPostDiv = (BYTE)(PDATA_DWORD(0) & 0x00000003);
    ucIcp = (BYTE)((PDATA_DWORD(0) & 0x0000700) >> 8);
    ucIpi = (BYTE)((PDATA_DWORD(0) & 0x00030000) >> 16);

    // Debug
    DebugMessageDigital("6. MPLL *** fvco=466M, N=0x20, F=0x8BE3D ***", 0);
    DebugMessageDigital("6. MPLL ulFreq =", ulFreq);
    DebugMessageDigital("6. MPLL ucPostDiv =", ucPostDiv);
    DebugMessageDigital("6. MPLL ucIcp =", ucIcp);
    DebugMessageDigital("6. MPLL ucIpi =", ucIpi);

    // Power Down PLL
    ScalerSetBit(P1_32_MPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

    // Reserved for Disable LDO

#if(_MPLL_PREDIV_BYPASS == _ON)

    // Set Postdiv, Prediv bypass
    ScalerSetBit(P1_31_MPLL_ANALOG_SETTING_0, ~(_BIT6 | _BIT5 | _BIT4), ((ucPostDiv << 5) | _BIT4));

#else

    // Set Postdiv, Prediv bypass
    ScalerSetBit(P1_31_MPLL_ANALOG_SETTING_0, ~(_BIT6 | _BIT5 | _BIT4), (ucPostDiv << 5));

    // Set Prediv
    ScalerSetByte(P1_2A_MPLL_CLK_CTRL_1, (_MPLL_PREDIV_DIV - 2));
#endif

    // Set CMU Icp, Cs none, Rs
    ScalerSetByte(P1_34_MPLL_ANALOG_SETTING_3, ((ucIcp & 0x07) << 5) | (_NFPLL_RS_SEL & 0x07));

    // Set CMU Ipi
    ScalerSetBit(P1_33_MPLL_ANALOG_SETTING_2, ~(_BIT7 | _BIT6 | _BIT5), ((ucIpi & 0x03) << 5));

    // Set CP Enable, close loop. Set Vc, Set LPF Enable
    ScalerSetBit(P1_32_MPLL_ANALOG_SETTING_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT3));

    // Set VCO Mode
    ScalerSetBit(P1_40_MPLL_ANALOG_SETTING_4, ~_BIT7, _BIT7);

    // Set Double Buffer
    pData[0] = ScalerGetByte(P1_21_MPLL_N_F_CODE_1);
    ScalerSetByte(P1_21_MPLL_N_F_CODE_1, (_BIT7 | pData[0]));
}

//--------------------------------------------------
// Description  : MPLL On COntrol.
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetMPLLOnProc(DWORD ulFreq, DWORD ulRefClk)
{
    BYTE ucNcode = 0;
    BYTE ucFcode_MSB4b = 0;
    WORD usFcode_LSB16b = 0;

    // calculate NF code
    PDATA_DWORD(0) = ScalerPLLCalNFCode(ulFreq, ulRefClk, _MPLL_PREDIV_DIV, _MPLL_PIXELDIV2_DIV, _MPLL_NF_PLL, _PLL_FREQ_CHG_OVER_10PER);

    usFcode_LSB16b = (WORD)(PDATA_DWORD(0) & 0x0000FFFF);
    ucFcode_MSB4b = (BYTE)((PDATA_DWORD(0) & 0x000F0000) >> 16);
    ucNcode = (BYTE)((PDATA_DWORD(0) & 0x0FF00000) >> 20);

    // Debug
    DebugMessageDigital("6. MPLL *** fvco=533M, N=0x23+2, F=0x39D29 ***", 0);
    DebugMessageDigital("6. MPLL ucNcode =", ucNcode);
    DebugMessageDigital("6. MPLL usFcode[15:0] =", usFcode_LSB16b);
    DebugMessageDigital("6. MPLL usFcode[19:16] =", ucFcode_MSB4b);
    DebugMessageDigital("6. MPLL ~Freq(Mhz) ~=Xtal*Ncode=", ((DWORD)14318 * ucNcode / 1000));

    // Reserved for Enable LDO

    // Power Up PLL
    ScalerSetBit(P1_32_MPLL_ANALOG_SETTING_1, ~_BIT0, 0x00);

    // Wait for LDO Stable (>40us)
    DELAY_XUS(150);

    // Set VCO/4 Enable
    pData[0] = ScalerGetByte(P1_31_MPLL_ANALOG_SETTING_0);
    ScalerSetByte(P1_31_MPLL_ANALOG_SETTING_0, (_BIT7 | pData[0]));

    // Check if NCode >= 5
    if(ucNcode < 5)
    {
        ucNcode = 5;
        DebugMessageScaler("invalid MPLL N code", ucNcode);
    }

    // Set N.F Code
    ScalerSetByte(P1_24_MPLL_N_F_CODE_4, ((usFcode_LSB16b & 0x00FF) >> 0));
    ScalerSetByte(P1_23_MPLL_N_F_CODE_3, ((usFcode_LSB16b & 0xFF00) >> 8));
    ScalerSetByte(P1_22_MPLL_N_F_CODE_2, ((((ucNcode - 2) & 0x0F) << 4) | ucFcode_MSB4b));

    // Set N.F Double Buffer, can't use SetBit
    ScalerSetByte(P1_21_MPLL_N_F_CODE_1, (0xA0 | (((ucNcode - 2) & 0xF0) >> 4)));



    // Wait for Mpll stable (Must!)
    ScalerTimerDelayXms(2);

    // Debug
    DebugMessageDigital("6. MPLL *** fvco=533M, N=0x23+2, F=0x39D29 ***", 0);
    DebugMessageDigital("6. MPLL     Ncode =", ((((ScalerGetByte(P1_21_MPLL_N_F_CODE_1) & 0x0F) << 4) | ((ScalerGetByte(P1_22_MPLL_N_F_CODE_2) & 0xF0) >> 4)) + 2));
    DebugMessageDigital("6. MPLL Reg_Fcode[7:0] =", ScalerGetByte(P1_24_MPLL_N_F_CODE_4));
    DebugMessageDigital("6. MPLL Reg_Fcode[15:8] =", ScalerGetByte(P1_23_MPLL_N_F_CODE_3));
    DebugMessageDigital("6. MPLL Reg_Fcode[19:16] =", (ScalerGetByte(P1_22_MPLL_N_F_CODE_2) & 0x0F));
    DebugMessageDigital("6. MPLL ~Freq(Mhz) ~=Xtal*Ncode=", ((DWORD)14318 * ((((ScalerGetByte(P1_21_MPLL_N_F_CODE_1) & 0x0F) << 4) | ((ScalerGetByte(P1_22_MPLL_N_F_CODE_2) & 0xF0) >> 4)) + 2) / 1000));
    DebugMessageDigital("6. MPLL **********************", 0);
}
#endif // End of #if(_MPLL_STRUCT_TYPE == _MPLL_STRUCT_N_F)

//--------------------------------------------------
// Description  : Reset DPLL Setting, Enable DPLL Spread Spectrum Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLReset(void)
{
    // Switch Dclk Source from DPLL to Eclk
    ScalerSetBit(P80_DD_DCLK_SRC_CTRL, ~_BIT7, 0x00);

    // Power Down DPLL
    ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
    // Power Down DPTx PLL
    ScalerPLLDPTxPLLReset();
#endif

    // Reserved for Disable LDO

    // Power Down PLL
    ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

    // Disable SSCG
    ScalerSetBit(P1_CA_DPLL_SSCG_0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Get DPLL Ref Clk from DPTx PLL or Xtal
// Input Value  : Dclk
// Output Value : DPTx PLL clk or Xtal Clk
//--------------------------------------------------
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq)
{
#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
    DWORD ulMacClk = 0;
#if(_PANEL_STYLE == _PANEL_VBO)
    DWORD ulDPTxClkIn = 0;
#endif

    ulMacClk = ulMacClk;
#endif

    ulFreq = ulFreq;

#if(_PANEL_STYLE == _PANEL_VBO)

    ulMacClk = (ulFreq * _PANEL_VBO_BYTE_MODE) / _PANEL_VBO_OUTPUT_PORT;

#elif(_PANEL_STYLE == _PANEL_DPTX)

    if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_RBR)
    {
        ulMacClk = _DPTX_PHY_RATE_RBR / 10;
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR)
    {
        ulMacClk = _DPTX_PHY_RATE_HBR / 10;
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
    {
        ulMacClk = _DPTX_PHY_RATE_HBR2 / 10;
    }

#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)

#if((_PANEL_STYLE == _PANEL_LVDS) || (_PANEL_STYLE == _PANEL_DPTX))

    return (_EXT_XTAL);

#elif(_PANEL_STYLE == _PANEL_VBO)

    if(ulMacClk > (_DPTX_CLK_IN_BOUNDRY_2 * _PANEL_VBO_BYTE_MODE))
    {
        ulDPTxClkIn = ulMacClk / 16;
        ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }
    else if(ulMacClk > (_DPTX_CLK_IN_BOUNDRY_1 * _PANEL_VBO_BYTE_MODE))
    {
        ulDPTxClkIn = ulMacClk / 8;
        ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~(_BIT3 | _BIT2), (_BIT3));
    }
    else if(ulMacClk > (_DPTX_CLK_IN_BOUNDRY_0 * _PANEL_VBO_BYTE_MODE))
    {
        ulDPTxClkIn = ulMacClk / 4;
        ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~(_BIT3 | _BIT2), (_BIT2));
    }
    else
    {
        ulDPTxClkIn = ulMacClk / 2;
        ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~(_BIT3 | _BIT2), 0x00);
    }

    DebugMessageDigital("==== ulFreq", ulFreq);
    DebugMessageDigital("==== ulMacClk", ulMacClk);
    DebugMessageDigital("==== ulDPTxClkIn", ulDPTxClkIn);

    return (ulDPTxClkIn);

#endif // End of #if((_PANEL_STYLE == _PANEL_LVDS) || (_PANEL_STYLE == _PANEL_DPTX))

    return (_EXT_XTAL);
}

#if(_PANEL_STYLE != _PANEL_VBO)
#if((_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
//--------------------------------------------------
// Description  : Adjust DPLL N.F
// Input Value  : Target N.F Value
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLNFcode(DWORD ulNFcode)
{
    BYTE ucNCode = 0;
    DWORD ulFCode = 0;

    ucNCode = ((ulNFcode & 0xFF00000) >> 20);

    ulFCode = (ulNFcode & 0x00FFFFF);

    // Check if (ucNCode + 2) < 5
    ucNCode = (((ucNCode + 2) < 5) ? (5 - 2) : ucNCode);

    // Set N[3:0].F[19:16] Code and double buffer for N.f code, prediv, postdiv
    ScalerSetByte(P1_C1_DPLL_N_F_CODE_2, ((ucNCode & 0x0F) << 4) | ((ulFCode & 0xF0000) >> 16));

    // Set F[15:8] Code
    ScalerSetByte(P1_C2_DPLL_N_F_CODE_3, ((ulFCode & 0x0FF00) >> 8));

    // Set F[7:0] Code
    ScalerSetByte(P1_C3_DPLL_N_F_CODE_4, ((ulFCode & 0x000FF) >> 0));

    // Set Double Buffer and N[7:4] Code, can't use SetBit
    ScalerSetByte(P1_C0_DPLL_N_F_CODE_1, (0xA0 | ((ucNCode & 0xF0) >> 4)));
}
#endif
#endif

//--------------------------------------------------
// Description  : Adjust DPLL Spread Spectrum
// Input Value  : Spread Spectrum Range
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLSSC(BYTE ucDclkSpreadSpeed, BYTE ucSpreadRange)
{
#if(_PANEL_STYLE == _PANEL_VBO)

    // _SPEED_30K
    ScalerDisplayVboTxSetPllSsc(ucDclkSpreadSpeed, ucSpreadRange);

#if((_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))

    // Disable SSCG, Disable SSCG_TBASE_CAL_EN
    ScalerSetBit(P1_CA_DPLL_SSCG_0, ~(_BIT7 | _BIT2), 0x00);

    // Wait SSCG disalbe, SSCG disable at triangle center
    ScalerTimerPollingFlagProc(2, P1_CA_DPLL_SSCG_0, _BIT7, 0x00);
#endif

#else // Else of #if(_PANEL_STYLE == _PANEL_VBO)

#if((_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))

    DWORD ulSSCGStep = 0;
    WORD usTBase = 0;
    BYTE ucStepWeighting = 0;

    // Disable SSCG, Disable SSCG_TBASE_CAL_EN
    ScalerSetBit(P1_CA_DPLL_SSCG_0, ~(_BIT7 | _BIT2), 0x00);

    // Wait SSCG disalbe, SSCG disable at triangle center
    ScalerTimerPollingFlagProc(2, P1_CA_DPLL_SSCG_0, _BIT7, 0x00);

    if((ucSpreadRange != _OFF) &&
       ((ucDclkSpreadSpeed == _SPEED_33K) || (ucDclkSpreadSpeed == _SPEED_66K)))
    {
        // Set SSCG speed
        BYTE ucSpreadSpeed = (ucDclkSpreadSpeed == _SPEED_33K) ? 33 : 66;

        // calculate TBase with constant Fref
        usTBase = (ScalerGetBit(P1_D0_DPLL_ANALOG_SETTING_0, _BIT4) == _BIT4) ? _EXT_XTAL : (_EXT_XTAL / GET_N_F_PLL_PREDIVIDER());

        usTBase = usTBase / ucSpreadSpeed;

        // TBase must be a multiple of 4
        usTBase = ((usTBase + 2) >> 2) << 2;

        // SSCG_TBASE_CAL_EN set manual mode
        ScalerSetBit(P1_CA_DPLL_SSCG_0, ~_BIT2, 0x00);

        ///////////////////////////////////////////////////////////////////////////
        //
        // Calculate SSCG range step
        //
        // N.F * range = step * (TBASE / 2)
        // Step = SSCG_step * SSCG_weight, SSCG_step unit: 2^8, SSCG_weight min:1/8
        // Setp calculate use min unit: 2^8 / 8 = 2^5
        // range: 5 * ucSpreadRange / 1000.   ucSpreadRange = 15 --> range = 7.5%
        //
        ///////////////////////////////////////////////////////////////////////////
        ulSSCGStep = ((((DWORD)(ScalerGetDWord(P1_C0_DPLL_N_F_CODE_1) & 0x0FFFFFFF) >> 5) * 5 * ucSpreadRange * 2) / 1000 + (usTBase / 2)) / usTBase;

        if((ulSSCGStep >> 8) < 1)
        {
            ucStepWeighting = 0;
        }
        else if((ulSSCGStep >> 8) < 2)
        {
            ucStepWeighting = 1;
        }
        else if((ulSSCGStep >> 8) < 4)
        {
            ucStepWeighting = 2;
        }
        else if((ulSSCGStep >> 8) < 8)
        {
            ucStepWeighting = 3;
        }
        else if((ulSSCGStep >> 8) < 16)
        {
            ucStepWeighting = 4;
        }
        else if((ulSSCGStep >> 8) < 32)
        {
            ucStepWeighting = 5;
        }
        else
        {
            ucStepWeighting = 6;
        }

        DebugMessageDigital("6. DPLL SSCG Step", ulSSCGStep);
        DebugMessageDigital("6. DPLL SSCG Step Weighting", ucStepWeighting);
        DebugMessageDigital("6. DPLL TBASE", usTBase);

        ScalerSetByte(P1_CB_DPLL_SSCG_1, (ulSSCGStep >> ucStepWeighting));
        ScalerSetByte(P1_CC_DPLL_SSCG_2, (((ucStepWeighting & 0x07) << 5) | ((usTBase >> 8) & 0x0F)));
        ScalerSetByte(P1_CD_DPLL_SSCG_3, (usTBase & 0xFF));

        // Enable SSCG
        ScalerSetBit(P1_CA_DPLL_SSCG_0, ~_BIT7, _BIT7);
    }
#endif // End of #if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL)
#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)
}

//--------------------------------------------------
// Description  : Set DPLL Freq
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLFreq(DWORD ulFreq)
{
    ulFreq = ulFreq;

#if(_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
    ScalerPLLSetDPLLFreqNf(ulFreq);
#endif
}

#if(_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)
//--------------------------------------------------
// Description  : Set DPLL Power Down Parameter
// Input Value  : Target Freq, Reference CLk
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLOffProc(DWORD ulFreq, DWORD ulRefClk)
{
    BYTE ucIcp = 0;
    BYTE ucIpi = 0;
    BYTE ucHigh_Freq = 0;

    ucHigh_Freq = ucHigh_Freq;

    // calculate postDiv, Icp, Ipi
    PDATA_DWORD(0) = ScalerPLLCalPLLParameter(ulFreq, ulRefClk, _DPLL_PREDIV_DIV, _DPLL_PIXELDIV2_DIV, _DPLL_NF_PLL, _PLL_FREQ_CHG_OVER_10PER);

    ucHigh_Freq = (BYTE)((PDATA_DWORD(0) & 0x00000010) >> 4);
    ucIcp = (BYTE)((PDATA_DWORD(0) & 0x00000700) >> 8);
    ucIpi = (BYTE)((PDATA_DWORD(0) & 0x00030000) >> 16);

    // Debug
    DebugMessageDigital("6. DPLL Off Process ***", 0);
    DebugMessageDigital("6. DPLL ulFreq =", ulFreq);
    DebugMessageDigital("6. DPLL ucHigh_Freq =", ucHigh_Freq);
    DebugMessageDigital("6. DPLL ucIcp =", ucIcp);
    DebugMessageDigital("6. DPLL ucIpi =", ucIpi);

    // Wait DEN STOP
    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

    // Reserved for Disable LDO

    // Switch Dclk Source from DPLL to Eclk
    ScalerSetBit(P80_DD_DCLK_SRC_CTRL, ~_BIT7, 0x00);

    // Power Down PLL
    ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

    // Set PixelClkDiv Div1
    ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~(_BIT6 | _BIT5), 0x0);

    // Set fixed divide 2, circuit reserved


    // Set Rs, Cs none, Icp
    ScalerSetByte(P1_D3_DPLL_ANALOG_SETTING_3, ((ucIcp & 0x07) << 5) | (_NFPLL_RS_SEL & 0x07));

    // Set CMU PI normal, Ipi
    ScalerSetBit(P1_D2_DPLL_ANALOG_SETTING_2, ~(_BIT7 | _BIT6 | _BIT5), ((ucIpi & 0x03) << 5));

    // Set CP Enable, close loop. Set Vc, Set LPF Enable
    ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT3));

    // Set VCO Mode
    ScalerSetBit(P1_DF_DPLL_ANALOG_SETTING_4, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Set DPLL Power Up Parameter
// Input Value  : Target Freq, Reference CLk
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLOnProc(DWORD ulFreq, DWORD ulRefClk, EnumDclkChg enumDclkChg)
{
    BYTE ucPostDiv = 0;
    BYTE ucNcode = 0;
    BYTE ucFcode_MSB4b = 0;
    WORD usFcode_LSB16b = 0;
#if(_PANEL_STYLE == _PANEL_VBO)
    BYTE ucPreDiv = 0;
#endif

    ucFcode_MSB4b = ucFcode_MSB4b;
    usFcode_LSB16b = usFcode_LSB16b;

    // calculate NF code
    PDATA_DWORD(0) = ScalerPLLCalNFCode(ulFreq, ulRefClk, _DPLL_PREDIV_DIV, _DPLL_PIXELDIV2_DIV, _DPLL_NF_PLL, enumDclkChg);

    ucPostDiv = (BYTE)((PDATA_DWORD(0) & 0x30000000) >> 28);
    usFcode_LSB16b = (WORD)(PDATA_DWORD(0) & 0x0000FFFF);
    ucFcode_MSB4b = (BYTE)((PDATA_DWORD(0) & 0x000F0000) >> 16);
    ucNcode = (BYTE)((PDATA_DWORD(0) & 0x0FF00000) >> 20);

    // Debug
    DebugMessageDigital("6. DPLL On Process ***", 0);
    DebugMessageDigital("6. DPLL ucNcode =", ucNcode);
    DebugMessageDigital("6. DPLL usFcode[15:0] =", usFcode_LSB16b);
    DebugMessageDigital("6. DPLL usFcode[19:16] =", ucFcode_MSB4b);
    DebugMessageDigital("6. DPLL ~Freq(Mhz) ~=Xtal*Ncode=", ((DWORD)14318 * ucNcode / 1000));

    // Reserved for Enable LDO

#if(_PANEL_STYLE == _PANEL_VBO)

    ucPreDiv = (g_ulPLLFifoRateMode == _BIT16) ? (_PANEL_VBO_BYTE_MODE << 1) : _PANEL_VBO_BYTE_MODE;

    // Set Prediv
    ScalerSetByte(P1_C9_DPLL_CLK_CTRL_1, ((ucPreDiv < 2) ? 0 : (ucPreDiv - 2)));

#else

    // Set Prediv
    ScalerSetByte(P1_C9_DPLL_CLK_CTRL_1, 0x00);

#endif

    // Power Up PLL
    ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, 0x00);

    // Wait for LDO Stable (>40us)
    DELAY_XUS(150);


    pData[0] = ScalerGetBit(P1_D0_DPLL_ANALOG_SETTING_0, (_BIT3 | _BIT2 | _BIT1));

#if(_PANEL_STYLE == _PANEL_VBO)

    // Set Postdiv, Prediv enable
    pData[0] |= (ucPostDiv << 5);

#else
#if(_DPLL_PREDIV_BYPASS == _ON)

    // Set Postdiv, Prediv bypass
    pData[0] |= ((ucPostDiv << 5) | _BIT4);

#else

    // Set Postdiv, Prediv enable
    pData[0] |= (ucPostDiv << 5);

#endif
#endif

    // Set VCO/4 Enable
    ScalerSetByte(P1_D0_DPLL_ANALOG_SETTING_0, (_BIT7 | pData[0]));

#if(_PANEL_STYLE == _PANEL_VBO)

    // Set SDM Manual Mode
    ScalerSetBit(P1_C4_DPLL_SDM_0, ~_BIT5, _BIT5);

    // Set N Code
    ScalerSetByte(P1_C5_DPLL_SDM_1, (ucNcode - 2));

    // Set Double Buffer, can't use SetBit
    ScalerSetByte(P1_C0_DPLL_N_F_CODE_1, 0xA0);

    ScalerTimerDelayXms(2);

    // Set dpll_refck_sel From dptx_clkin
    ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~(_BIT1), _BIT1);
#else
    // Check if NCode >= 5
    if(ucNcode < 5)
    {
        ucNcode = 5;
        DebugMessageScaler("invalid DPLL N code", ucNcode);
    }

    // Set N.F Code
    ScalerSetByte(P1_C3_DPLL_N_F_CODE_4, ((usFcode_LSB16b & 0x00FF) >> 0));
    ScalerSetByte(P1_C2_DPLL_N_F_CODE_3, ((usFcode_LSB16b & 0xFF00) >> 8));
    ScalerSetByte(P1_C1_DPLL_N_F_CODE_2, ((((ucNcode - 2) & 0x0F) << 4) | ucFcode_MSB4b));

    // Set Double Buffer, can't use SetBit
    ScalerSetByte(P1_C0_DPLL_N_F_CODE_1, (0xA0 | (((ucNcode - 2) & 0xF0) >> 4)));

    ScalerTimerDelayXms(2);

    // Set dpll_refck_sel From xclk
    ScalerSetBit(P1_BF_DPLL_CLK_CTRL_0, ~(_BIT1), 0x00);
#endif

    // Wait for DPLL Stable (2ms)
    ScalerTimerDelayXms(2);

    // Switch Dclk Source from Eclk to DPLL
    ScalerSetBit(P80_DD_DCLK_SRC_CTRL, ~_BIT7, _BIT7);

    // Debug
    DebugMessageDigital("6. DPLL ***1080p fvco=580M/2/2, N=0x28, F=0x8229D ***", 0);
    DebugMessageDigital("6. DPLL     Ncode =", ((((ScalerGetByte(P1_C0_DPLL_N_F_CODE_1) & 0x0F) << 4) | ((ScalerGetByte(P1_C1_DPLL_N_F_CODE_2) & 0xF0) >> 4)) + 2));
    DebugMessageDigital("6. DPLL Reg_Fcode[7:0] =", ScalerGetByte(P1_C3_DPLL_N_F_CODE_4));
    DebugMessageDigital("6. DPLL Reg_Fcode[15:8] =", ScalerGetByte(P1_C2_DPLL_N_F_CODE_3));
    DebugMessageDigital("6. DPLL Reg_Fcode[19:16] =", (ScalerGetByte(P1_C1_DPLL_N_F_CODE_2) & 0x0F));
    DebugMessageDigital("6. DPLL ~Freq(Mhz) ~=Xtal*Ncode=", ((DWORD)14318 * ((((ScalerGetByte(P1_C1_DPLL_N_F_CODE_2) & 0x0F) << 4) | ((ScalerGetByte(P1_C1_DPLL_N_F_CODE_2) & 0xF0) >> 4)) + 2) / 1000));
    DebugMessageDigital("6. DPLL **********************", 0);
}

//--------------------------------------------------
// Description  : Set DPLL Freq
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLFreqNf(DWORD ulFreq)
{
    DWORD ulRefClk = 0;
    DWORD ulNFCodeOld = 0;
    DWORD ulCurrentDPLLVcoClk = 0;
    EnumDclkChg enumDclkChg = _PLL_FREQ_CHG_OVER_10PER;

#if((_PANEL_STYLE == _PANEL_DPTX) || (_PANEL_STYLE == _PANEL_VBO))
    ScalerPLLSetDPLLRefPLL(ulFreq);
#elif(_PANEL_STYLE == _PANEL_LVDS)
    ScalerPLLSetDisplayPLL(ulFreq);
#endif

    ulRefClk = ScalerPLLGetDPLLRefClk(ulFreq);

    ulFreq = (ulFreq >> GET_D_DOMAIN_PATH());

    if(ScalerDisplayGetPllPowerStatus() == _ON)
    {
        BYTE ucPreDiv = 1;

        DebugMessageDigital("9. DPLL bDISPPower=", _ON);

#if(_PANEL_STYLE == _PANEL_VBO)
        // Get current (N code + 2) * 2^20
        ulNFCodeOld = (((DWORD)ScalerGetByte(P1_C5_DPLL_SDM_1) << 20) + 0x200000);
#else
        // Get current (N code + 2) * 2^20 + F code
        ulNFCodeOld = ((ScalerGetDWord(P1_C0_DPLL_N_F_CODE_1) & 0x0FFFFFFF) + 0x200000);
#endif
        // vco Freq = ((N code + 2) * RefClk) + (F code * RefClk / 2^20)
        ulCurrentDPLLVcoClk = (((ulNFCodeOld & 0xFF00000) >> 20) * ulRefClk) + (GET_DWORD_MUL_DIV((ulNFCodeOld & 0xFFFFF), ulRefClk, 1048576));

        ucPreDiv = ((ScalerGetBit(P1_D0_DPLL_ANALOG_SETTING_0, _BIT4) == _BIT4) ? 1 : (ScalerGetByte(P1_C9_DPLL_CLK_CTRL_1) + 2));

        // PLL output clk = (vco Freq / Post_div / Pixel_ck_div)
        ulCurrentDPLLVcoClk = (((ulCurrentDPLLVcoClk / ucPreDiv) >> ((ScalerGetByte(P1_D0_DPLL_ANALOG_SETTING_0) & 0x60) >> 5)) >> ((ScalerGetByte(P1_BF_DPLL_CLK_CTRL_0) & 0x60) >> 5));

        if(ABSDWORD(ulFreq, ulCurrentDPLLVcoClk) <= (ulCurrentDPLLVcoClk / 10))
        {
            enumDclkChg = _PLL_FREQ_CHG_UNDER_10PER;
        }
    }

    // DPLL freq change under 10%, VCO band and div_o keep as before
    if(enumDclkChg == _PLL_FREQ_CHG_OVER_10PER)
    {
        ScalerPLLSetDPLLOffProc(ulFreq, ulRefClk);
    }

    ScalerPLLSetDPLLOnProc(ulFreq, ulRefClk, enumDclkChg);
}
#endif // End of #if(_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F)

//--------------------------------------------------
// Description  : Calulate New PLL Parameter
// Input Value  : ulCountNew, ulCountOld, ulValueOld, bPropitional
// Output Value : New Parameter
//--------------------------------------------------
DWORD ScalerPLLGetNewCount(DWORD ulCountNew, DWORD ulCountOld, DWORD ulValueOld, bit bProportion)
{
    if(bProportion == _TRUE)
    {
        return GET_DWORD_MUL_DIV(ulCountNew, ulValueOld, ulCountOld);
    }
    else
    {
        return GET_DWORD_MUL_DIV(ulCountOld, ulValueOld, ulCountNew);
    }
}

//--------------------------------------------------
// Description  : Set FrameSync offset to match I/D active time & last-line target
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDPLLFineTuneFrameSyncLineBuffer(void)
{
    DWORD ulNFCodeOld = 0;
    DWORD ulNFCodeNew = 0;
    DWORD ulDisplayActiveRegion = 0;
    DWORD ulDclk = GET_D_CLK_FREQ();
    bit bProportion = _TRUE;
    BYTE ucDebounceCnt = 5;
    DWORD ulPanelClockMaxSpread = MAXOF(GET_PANEL_PIXEL_CLOCK_MAX_SPREAD(), GET_PANEL_PIXEL_CLOCK_TYPICAL());
    DWORD ulPanelClockMinSpread = MINOF(GET_PANEL_PIXEL_CLOCK_MIN_SPREAD(), GET_PANEL_PIXEL_CLOCK_TYPICAL());
    StructDHtotalFTStatus stDHtotalFTStatus;
    BYTE ucIRQPageOffset = ScalerIDomainGetIRQPageOffset(GET_MDOMAIN_INPUT_DATA_PATH());

    // Dclk_max_spread < Dclk_min_spread, not make sense!
    if(GET_PANEL_PIXEL_CLOCK_MAX_SPREAD() < GET_PANEL_PIXEL_CLOCK_MIN_SPREAD())
    {
        return;
    }

    // Temporary Enable Frame Sync Fine Tune for Interlace Mode in order to Get Equal Frame Period
    if(GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE)
    {
        if(ScalerGetBit(ScalerDDomainGetScalingUpPageAddr(GET_MDOMAIN_OUTPUT_RGN()), _BIT6) == _BIT6)
        {
            // Video Compensation on Even Field; Enable Last Line Measure on Odd Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT7 | _BIT6), _BIT7);
        }
        else
        {
            // Video Compensation on Odd Field; Enable Last Line Measure on Even Field
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
    }
    else
    {
        // Disable Last Line Measure by Field
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT7 | _BIT6), 0x00);
    }

    // Get NF code
#if(_PANEL_STYLE == _PANEL_VBO)
    // Get current NF CodeF
    ulNFCodeOld = ScalerDisplayVboTxGetNFCode(_DISPLAY_VBO_CMU_NF_CODE);
#else
    // Get current (N code + 2) * 2^20 + F code
    ulNFCodeOld = ((ScalerGetDWord(P1_C0_DPLL_N_F_CODE_1) & 0x0FFFFFFF) + 0x200000);
#endif

    while(ucDebounceCnt > 0)
    {
        // Clear status (status register will be cleared after write)
        ScalerSetByte(P0_A2_M1_EVENT_FLAG + ucIRQPageOffset, _EVENT_IVS);

        // Measure DVtotal in frame sync mode
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

        //=====================================
        // Measure input/ display active region
        //=====================================
        ulDisplayActiveRegion = ScalerMDomainGetDisplayActiveRegion();
        DebugMessageFS("DisplayRegionCount", ulDisplayActiveRegion);

        // don't do fine tune when no IVS
        if((ScalerGetByte(P0_A2_M1_EVENT_FLAG + ucIRQPageOffset) & _EVENT_IVS) == 0x00)
        {
            return;
        }

        // Check DV_BG_End <= DVtotal to avoid measure display active count abnormal and calculate dclk = 0
        if((GET_MDOMAIN_OUTPUT_VBSTART() + GET_MDOMAIN_OUTPUT_VBHEIGHT()) > ScalerMDomainGetDVtotalLastline())
        {
            return;
        }

        /////////////////////////////////////////////////////////////////////////
        ///
        /// N.F PLL: active_count and NF code relation are in inverse proportion when frame sync fine tune
        ///
        /// (disp_act_region * N.F_old) = (input_act_region * N.F_new)
        /// N.F_new = disp_act_region * N.F_old / input_act_region
        ///
        /////////////////////////////////////////////////////////////////////////

        // Calculate NF code
        ulNFCodeNew = ScalerPLLGetNewCount(ScalerMeasureGetAdjustedActiveRegionCount(GET_MDOMAIN_INPUT_DATA_PATH(), GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_INPUT_VHEIGHT()), ulDisplayActiveRegion, ulNFCodeOld, !bProportion);

        // Calculate Dclk
        ulDclk = (ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, GET_D_CLK_FREQ(), bProportion));

        stDHtotalFTStatus = ScalerMDomainDHtotalFinetune(ulDclk, ulPanelClockMaxSpread, ulPanelClockMinSpread);

        if(stDHtotalFTStatus.usDHtotal != GET_MDOMAIN_OUTPUT_HTOTAL())
        {
            SET_MDOMAIN_OUTPUT_HTOTAL(stDHtotalFTStatus.usDHtotal);

            // Set DHtotal and Last line
            ScalerMDomainSetDisplayTimingGenDHTotalLastline(GET_MDOMAIN_OUTPUT_HTOTAL());

            ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_INDEX_0, _DB_APPLY_POLLING);

            if(stDHtotalFTStatus.b1DHtotalFineTuneStatus == _FALSE)
            {
                break;
            }
        }
        else
        {
            break;
        }

        ucDebounceCnt --;
    }

#if((_DT_RANGE_TEST_SUPPORT == _OFF) || ((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON)))
#if(_PANEL_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) == _DRR_NONE_TYPE)
#endif
    {
        /////////////////////////////////////////////////////////////////////////
        ///
        /// N.F PLL: active_count and NF code relation are in direct proportion when last line fine tune
        ///
        /// Fine Tune Last Line to Panel Target
        /// Dtotal_old = DHtotal * DV count + Last-line
        ///
        /// Dtotal' = Dtotal_old * N.F_New / N.F_Old
        ///
        /////////////////////////////////////////////////////////////////////////

        WORD usDVtotal = 0;
        WORD usLastLine = 0;
        DWORD ulDtotal = 0;
        DWORD ulDtotalNew = 0;
        DWORD ulDtotalTemp = 0;

        // Measure DVtotal in frame sync mode
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        usDVtotal = ScalerMDomainGetDVtotalLastline();

        // Pop out Last line
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);
        usLastLine = ScalerMDomainGetDVtotalLastline();
        usLastLine = (usLastLine << GET_D_DOMAIN_PATH());

        // Calculate Frame Sync fine tuneDtotal
        ulDtotal = (DWORD)usDVtotal * GET_MDOMAIN_OUTPUT_HTOTAL() + usLastLine;

        ulDtotal = ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, ulDtotal, bProportion);

        // Calculate new last-line
        usLastLine = ulDtotal % GET_MDOMAIN_OUTPUT_HTOTAL();

        DebugMessageFS("Estimated last-line", usLastLine);

        // Calculate modified Dtotal
        ulDtotalNew = ulDtotal - usLastLine + _PANEL_LAST_LINE_TARGET;

        if(abs(usLastLine - _PANEL_LAST_LINE_TARGET) > (GET_MDOMAIN_OUTPUT_HTOTAL() >> 1))
        {
            if(usLastLine > _PANEL_LAST_LINE_TARGET)
            {
                ulDtotalNew += (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL();  // +
            }
            else
            {
                ulDtotalNew -= (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL();  // -
            }
        }

        ulNFCodeNew = ScalerPLLGetNewCount(ulDtotalNew, ulDtotal, ulNFCodeNew, bProportion);
        ulDclk = (ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, GET_D_CLK_FREQ(), bProportion));

        ulDtotalTemp = ScalerMDomainDtotalLastLineFinetune(ulDclk, ulPanelClockMaxSpread, ulPanelClockMinSpread, ulDtotalNew);

        if(ulDtotalTemp != ulDtotalNew)
        {
            ulNFCodeNew = ScalerPLLGetNewCount(ulDtotalTemp, ulDtotalNew, ulNFCodeNew, bProportion);
            ulDclk = (ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, GET_D_CLK_FREQ(), bProportion));

            ulDtotalNew = ulDtotalTemp;
            DebugMessageFS("_Last_line_modify_Dclk", ulDclk);
        }

        // Modify Dt by new Dtotal & old Dtotal
        ScalerMemoryCompensateDtForLastLine(ulDtotalNew, ulDtotal);
    }
#endif
#endif

    SET_D_CLK_FREQ(ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, GET_D_CLK_FREQ(), bProportion));

    DebugMessageScaler("Dclk fine tune", GET_D_CLK_FREQ());

#if(_PANEL_STYLE == _PANEL_VBO)
    ScalerPLLSetDPLLRefPLL(GET_D_CLK_FREQ());
#else
#if((_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
    // Apply N.F for last-line
    ScalerPLLSetDPLLNFcode(ulNFCodeNew - 0x200000);
#endif
#endif

    // Disable Last Line Measure by Field
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~(_BIT7 | _BIT6), 0x00);
}

#if(_FRC_SUPPORT == _ON)
#if(_PANEL_LAST_LINE_FINETUNE_ENABLE == _ENABLE)
//--------------------------------------------------
// Description  : Set FrameSync offset to match I/D active time & last-line target
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDPLLFineTuneFrameSyncFrameBuffer(void)
{
    WORD usDVtotal = 0;
    WORD usLastLine = 0;
    WORD usDVtotalNext = 0;
    WORD usLastLineNext = 0;
    DWORD ulNFCodeOld = 0;
    DWORD ulNFCodeNew = 0;
    DWORD ulDclk = GET_D_CLK_FREQ();
    DWORD ulDtotal = 0;
    DWORD ulDtotalNew = 0;
    DWORD ulDtotalTemp = 0;
    DWORD ulPanelClockMaxSpread = MAXOF(GET_PANEL_PIXEL_CLOCK_MAX_SPREAD(), GET_PANEL_PIXEL_CLOCK_TYPICAL());
    DWORD ulPanelClockMinSpread = MINOF(GET_PANEL_PIXEL_CLOCK_MIN_SPREAD(), GET_PANEL_PIXEL_CLOCK_TYPICAL());
    bit bProportion = _TRUE;
    bit bInterlaced = (GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE);

#if(_DRR_SUPPORT == _ON)
    if(ScalerDrrGetType(GET_MDOMAIN_INPUT_PORT()) != _DRR_NONE_TYPE)
    {
        return;
    }
#endif

    // Dclk_max_spread < Dclk_min_spread, not make sense!
    if(GET_PANEL_PIXEL_CLOCK_MAX_SPREAD() < GET_PANEL_PIXEL_CLOCK_MIN_SPREAD())
    {
        return;
    }

    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

    // Measure DVtotal in frame sync mode
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
    usDVtotal = ScalerMDomainGetDVtotalLastline();

    // Pop out Last line
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);
    usLastLine = ScalerMDomainGetDVtotalLastline();
    usLastLine = (usLastLine << GET_D_DOMAIN_PATH());

    if(bInterlaced == _TRUE)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

        // Pop out DVtotal
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        usDVtotalNext = ScalerMDomainGetDVtotalLastline();

        // Pop out Last line
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);
        usLastLineNext = ScalerMDomainGetDVtotalLastline();
        usLastLineNext = (usLastLineNext << GET_D_DOMAIN_PATH());
    }

#if(_PANEL_STYLE == _PANEL_VBO)
    // Get current NF CodeF
    ulNFCodeOld = ScalerDisplayVboTxGetNFCode(_DISPLAY_VBO_CMU_NF_CODE);
#else
    // Get current (N code + 2) * 2^20 + F code
    ulNFCodeOld = ((ScalerGetDWord(P1_C0_DPLL_N_F_CODE_1) & 0xFFFFFFF) + 0x200000);
#endif

    ulNFCodeNew = ulNFCodeOld;
    // Calculate Dtotal
    ulDtotal = (DWORD)usDVtotal * GET_MDOMAIN_OUTPUT_HTOTAL() + usLastLine;

    /////////////////////////////////////////////////////////////////////////
    ///
    /// N.F PLL: active_count and NF code relation are in direct proportion when last line fine tune
    ///
    /// Fine Tune Last Line to Panel Target
    /// Dtotal_old = DHtotal * DV count + Last-line
    ///
    /// Dtotal' = Dtotal_old * N.F_New / N.F_Old
    ///
    /////////////////////////////////////////////////////////////////////////

    // Calculate modified Dtotal
    ulDtotalNew = ulDtotal - usLastLine + _PANEL_LAST_LINE_TARGET;

#if(_LOCAL_CONTRAST_FUNCTION == _ON)

    // Local contrast prefer larger DVtotal
    ulDtotalNew += (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL();

#else

    if(abs(usLastLine - _PANEL_LAST_LINE_TARGET) > (GET_MDOMAIN_OUTPUT_HTOTAL() >> 1))
    {
        if(usLastLine > _PANEL_LAST_LINE_TARGET)
        {
            ulDtotalNew += (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL();  // +
        }
        else
        {
            ulDtotalNew -= (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL();  // -
        }
    }

#endif

    ulNFCodeNew = ScalerPLLGetNewCount(ulDtotalNew, ulDtotal, ulNFCodeNew, bProportion);

    ulDclk = (ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, GET_D_CLK_FREQ(), bProportion));

    ulDtotalTemp = ScalerMDomainDtotalLastLineFinetune(ulDclk, ulPanelClockMaxSpread, ulPanelClockMinSpread, ulDtotalNew);

    if(ulDtotalTemp != ulDtotalNew)
    {
        ulNFCodeNew = ScalerPLLGetNewCount(ulDtotalTemp, ulDtotalNew, ulNFCodeNew, bProportion);
        ulDclk = (ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, GET_D_CLK_FREQ(), bProportion));

        ulDtotalNew = ulDtotalTemp;
        DebugMessageFS("_Last_line_modify_Dclk", ulDclk);
    }

    if(bInterlaced == _TRUE)
    {
        // Calculate next frame Dtotal
        ulDtotal = ((DWORD)usDVtotalNext * GET_MDOMAIN_OUTPUT_HTOTAL() + usLastLineNext);

        // Using new Dclk offset, calculate next frame new last line
        PDATA_DWORD(1) = ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, ulDtotal, bProportion);
        PDATA_DWORD(1) = PDATA_DWORD(1) % GET_MDOMAIN_OUTPUT_HTOTAL();

        // (0 < (next frame new last line) <= 0.05 line) or (0.95 line <= (next frame new last line) <= 1 line), modify Dclk offset
        if((PDATA_DWORD(1) <= ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 5 / 100)) || (PDATA_DWORD(1) >= ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 95 / 100)))
        {
            // Calculate 0.2 line for Dclk offset
            pData[15] = (((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 20 / 100) * ulNFCodeNew / ulDtotal);

            if(_PANEL_LAST_LINE_TARGET <= (GET_MDOMAIN_OUTPUT_HTOTAL() / 2))
            {
                ulNFCodeNew += pData[15];
            }
            else
            {
                ulNFCodeNew -= pData[15];
            }
        }
    }

    SET_D_CLK_FREQ(ScalerPLLGetNewCount(ulNFCodeNew, ulNFCodeOld, GET_D_CLK_FREQ(), bProportion));

#if(_PANEL_STYLE == _PANEL_VBO)
    ScalerPLLSetDPLLRefPLL(GET_D_CLK_FREQ());
#else
#if((_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F_COMBO_LVDSPLL) || (_HW_DPLL_STRUCT_TYPE == _DPLL_STRUCT_N_F))
    // Apply N.F for last-line
    ScalerPLLSetDPLLNFcode(ulNFCodeNew - 0x200000);
#endif
#endif
}
#endif
#endif // End of #if(_FRC_SUPPORT == _ON)

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : ADC Clock adjust.
// Input Value  : usCurrHTotal    --> IHTotal.
// Output Value : Return _TRUE if adjust successful.
//--------------------------------------------------
bit ScalerAPLLAdjust(WORD usCurrHTotal, WORD usCurrHFreq)
{
    BYTE pucData[5] = {0};
    BYTE ucMcode = 0;
    BYTE ucNcode = 0;
    SBYTE chKcode = 0;
    WORD usIcode = 0;
    WORD usPcode = 0;
    DWORD ulOldPllDivider = 0;

    DebugMessageAnalog("APLL Clock", usCurrHTotal);

    // Disable new mode
    ScalerSetByte(P1_BB_DDS_MIX_4, 0x1b);

    // Disable Fast PLL Mechanism
    ScalerSetByte(P1_AA_FAST_PLL_CTRL, 0x00);

    // Power down APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, _BIT0);

    // APLL Inital Setting
    ScalerSetByte(P1_A0_PLL_DIV_CTRL, 0x08);

    // Set DDS Mix
    ScalerSetByte(P1_B9_DDS_MIX_2, 0xFF);
    ScalerSetByte(P1_BA_DDS_MIX_3, 0xFF);

    // Set APLL lock threshold by H-Sync Freq
    ScalerAPLLLockThdSet(usCurrHFreq);

    // Set the divide number
    ScalerSetBit(P1_B1_PLLDIV_H, ~0x0F, (BYTE)(((usCurrHTotal - 1) >> 8) & 0x0f));
    ScalerSetByte(P1_B2_PLLDIV_L, (BYTE)((usCurrHTotal - 1) & 0x00ff));

    // Get ADC Sampling clock freq.
    ulOldPllDivider = (DWORD)usCurrHFreq * usCurrHTotal / 10; // ADC sampling clock, UNIT in KHz

    // Record Current Pixel Clock
    SET_A0_INPUT_PIXEL_CLK(ulOldPllDivider / 100); // Unit: 0.1M Hz

    pucData[0] = (ulOldPllDivider < _APLL_VCO_DEVIDER_4_2_THERSHOLD) ? 4 : 2; // Vco_divider

    // Decide N Code value by Vco clock Freq
    if(ulOldPllDivider * pucData[0] >= 120000)
    {
        ucNcode = 1;
    }
    else
    {
        ucNcode = 2;
    }

    // VCO divider select
    pData[0] = ScalerGetBit(P1_B1_PLLDIV_H, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    if(pucData[0] == 2)
    {
        ScalerSetBit(P1_B1_PLLDIV_H, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | pData[0]));
    }
    else
    {
        ScalerSetBit(P1_B1_PLLDIV_H, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | pData[0]));
    }

    // Calculate (M + K/16) = IHF * usCurrHTotal * N1 * vco_divider / Fxtal
    ulOldPllDivider = ((ulOldPllDivider * ucNcode * pucData[0]) << 10) / _EXT_XTAL;

    // Get M, K code, M + K/16 = pllclock / 1024
    ucMcode = ulOldPllDivider >> 10; // M code is the integer part.

    // K is the fraction part quantized by 16
    chKcode = ((DWORD)ulOldPllDivider - ((DWORD)ucMcode << 10)) >> 6;

    // Set K code within -8 to 7 due to 3 bits.
    if(chKcode > 7)
    {
        ucMcode += 1;
        chKcode -= 16;
    }
    else if(chKcode < -8)
    {
        ucMcode -= 1;
        chKcode += 16;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Precise formula of Chrage Pump Current depends on VCO Freq  or M Code                        //
    // M Code can't be less than 5                                                                  //
    // Fvco >= 360M, N =1                                                                           //
    // Loop filter resister = 3b'000 (R1 = 4K), 4.4K Consider 0.4K parasitic resistance             //
    //                                                                                              //
    //         1MHz * 2 * pi * M                                                                    //
    //  Icp = ---------------------- = (3140 * ucMcode) / 1100   (icp unit uA)                      //
    //         500MHz/V * 4.4K                                                                      //
    //                                                                                              //
    // Fvco >= 120M, N =1                                                                           //
    // Loop filter resister = 3b'001 (R1 = 8K), 8.4K Consider 0.4K parasitic resistance             //
    //                                                                                              //
    //         1MHz * 2 * pi * M                                                                    //
    //  Icp = ---------------------- = (3140 * ucMcode) / 2100   (icp unit uA)                      //
    //         500MHz/V * 8.4K                                                                      //
    //                                                                                              //
    // Fvco < 120M, N = 2                                                                           //
    // Loop filter resister = 3b'101 (R1 = 16K),16.4K Consider 0.4K parasitic resistance            //
    //                                                                                              //
    //         0.5MHz * 2 * pi * M                                                                  //
    //  Icp = ---------------------- = (3140 * ucMcode) / 8200    (icp unit uA)                     //
    //         500MHz/V * 16.4K                                                                     //
    // Let pi = 3.14                                                                                //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    if(((DWORD)GET_A0_INPUT_PIXEL_CLK() * pucData[0]) >= 3600)
    {
        PDATA_WORD(0) = (WORD)((DWORD)3140 * ucMcode * 10 / 1100); // x 10 in order to 0.1, Unit 0.1uA

        // Resiter = 3b'000 --> 4K
        pData[14] = 0x00;
    }
    else if(((DWORD)GET_A0_INPUT_PIXEL_CLK() * pucData[0]) >= 1200)
    {
        PDATA_WORD(0) = (WORD)((DWORD)3140 * ucMcode * 10 / 2100); // x 10 in order to 0.1, Unit 0.1uA

        // Resiter = 3b'010 --> 8K
        pData[14] = _BIT6;
    }
    else
    {
        PDATA_WORD(0) = (WORD)((DWORD)3140 * ucMcode * 10 / 8200); // x 10 in order to 0.1, Unit 0.1uA

        // Resiter = 3b'110 --> 16K
        pData[14] = (_BIT7 | _BIT6);
    }

    // Get icp step, truncate lsb bit
    pData[15] = (PDATA_WORD(0)) / 25;
    pData[15] -= (pData[15] == 0) ? 0 : 1;

    // Icp only 5bit (bit4 = doubled), Min current = 2.5uA, Max current = 80mA
    pData[15] = (pData[15] > 0x0F) ? ((pData[15] / 2) | _BIT4) : pData[15];
    pData[15] = (pData[15] > 0x1F) ? 0x1F : pData[15];

    // Reg = Resistor & Icp, Resistor: MSB 3bit, Icp: LSB 5bit (When bit4 = 1, current * 2)
    ScalerSetByte(P1_AE_PLL_CRNT, (pData[14] | pData[15]));

    // Set N code & K code
    pData[0] = ((chKcode & 0x0f) << 4);
    if(ucNcode == 1)
    {
        pData[0] |= _BIT3;
    }
    else
    {
        pData[0] |= (((ucNcode - 2) & 0x07));
    }
    ScalerSetByte(P1_AD_PLL_N, pData[0]);

    // Set M code
    ScalerSetByte(P1_AC_PLL_M, (ucMcode - 3));

    // Enable PFD Calibration
    ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, 0x00);
    ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, _BIT7);

    // Get PFD Calibration result
    if(ScalerTimerPollingFlagProc(100, P1_A4_PFD_CALIBRATED_RESULTS_H, _BIT7, 0) == _TRUE)
    {
        ScalerRead(P1_A4_PFD_CALIBRATED_RESULTS_H, 2, pucData, _AUTOINC);
        g_stPLLApllData.usPEValue = ((WORD)(pucData[0] & 0x0F) << 8) | pucData[1];

        g_stPLLApllData.usPEValue = (WORD)((DWORD)1000000 / ((DWORD)g_stPLLApllData.usPEValue * _SYS_CLK_KHZ / 1000)); // Unit : ps

        DebugMessageAnalog("5. usPEValue", g_stPLLApllData.usPEValue);
    }
    else
    {
        ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, 0x00);

        return _FALSE;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Formula :                                                                 //
    //                                                                           //
    //  I_gain       Ths                    PE(UNIT)                   1         //
    // --------- x  ------- = ------------------------------------ x  -----      //
    //   2^22        Tbck        Txclk x 16N / (16M +- K) x 1/16       8         //
    //                                                                           //
    //  I_gain         Ths                      PE(UNIT)                   1     //
    // --------- x  ----------- = ------------------------------------ x  -----  //
    //   2^22       Tclk x N         Txclk x N / (M +- K/16) x 1/16        8     //
    //                                                                           //
    //                                                                           //
    //           2^22 x PE_U x (M +- K/16) x 2^4        1                        //
    // I_gain = ----------------------------------- x ------                     //
    //                        Ths                      2^3                       //
    //                                                                           //
    //           2^23 x PE_U x (M +- K/16)                                       //
    //       = -----------------------------                                     //
    //                      Ths                                                  //
    //                                                                           //
    //                                                                           //
    //       = IHF x 2^23 x PE_U x (M +- K/16)                                   //
    //                                                                           //
    //                                                                           //
    // I_gain = IHF x 2^23 x PE_U x (M +- K/16)                                  //
    // IHFreq/10 UNIT is KHz, so result has to multiply 10^2          //
    // (PE Value UNIT is ps, so result has to multiply 10^-12)                   //
    //                                                                           //
    // I_gain = 10^2 x 2^23 x 10^-12 x 2^-10 => 10^10 / 2^13 = 1220703           //
    //                                                                           //
    ///////////////////////////////////////////////////////////////////////////////

    // Calculate I code
    usIcode = (WORD)(((DWORD)usCurrHFreq * g_stPLLApllData.usPEValue * (ulOldPllDivider >> 10)) / 1192);

    // Total gain = 3 / 8
    usIcode = (usIcode / 64) & 0x00007fff; // n = 64 x 8 = 512

    // The minimum value of I code is 1.
    if(usIcode < 1)
    {
        usIcode = 1;
    }

    // Set I code
    ScalerSetByte(P1_A1_I_CODE_M, (BYTE)(usIcode >> 8));
    ScalerSetByte(P1_A2_I_CODE_L, (BYTE)usIcode);

    // Calculate P code
    usPcode = (WORD)(((DWORD)191 * usIcode * _EXT_XTAL / ((ucNcode * usCurrHFreq + 5) / 10)) >> 7); // Total Gain = 192/512

    // Get G value (ucData[0])
    pucData[0] = ScalerAPLLGetAPLLGValue(&usPcode);

    // Set G value
    ScalerSetByte(P1_B6_P_CODE_MAPPING_METHOD, (pucData[0] << 2));

    // Set P code
    ScalerSetByte(P1_A3_P_CODE, (BYTE)usPcode);

    // Intial Phase
    ScalerSetByte(P1_B4_PLLPHASE_CTRL1, 0x00);

    // Apply phase write port for phase DB
    ScalerSetByte(P1_B3_PLLPHASE_CTRL0, ScalerGetByte(P1_B3_PLLPHASE_CTRL0));

    // Release top misc power down control
    ScalerSetBit(P1_F2_APLL_MISC, ~_BIT7, 0x00);

    // Power up APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, 0x00);

    // Check PLL lock already
    if(ScalerTimerPollingFlagProc(150, P1_B8_DDS_MIX_1, _BIT0, _TRUE) == _FALSE)
    {
        DebugMessageAnalog("5. APLL Unlock", 0);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : APLL Lock Threshold Setting
// Input Value  : usHFreq --> H-Sync Freq
// Output Value : None
//--------------------------------------------------
void ScalerAPLLLockThdSet(WORD usHFreq)
{
    if(usHFreq <= 250) // 25K
    {
        ScalerSetBit(P1_B8_DDS_MIX_1, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));   // PE thd= 46
    }
    else if(usHFreq <= 500) // 50K
    {
        ScalerSetBit(P1_B8_DDS_MIX_1, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);   // PE thd= 23
    }
    else if(usHFreq <= 750) // 75K
    {
        ScalerSetBit(P1_B8_DDS_MIX_1, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));   // PE thd= 11
    }
    else // Uper 75K
    {
        ScalerSetBit(P1_B8_DDS_MIX_1, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);   // PE thd= 9
    }
}

//--------------------------------------------------
// Description  : Get APLL G value
// Input Value  : The P code of APLL
// Output Value : G value
//--------------------------------------------------
BYTE ScalerAPLLGetAPLLGValue(WORD *pusDelta)
{
    if(*pusDelta == 0)
    {
        *pusDelta = 0x01;
    }

    if(*pusDelta > 255)
    {
        for(pData[0] = 9; pData[0] < 15; pData[0]++)
        {
            if((*pusDelta >> pData[0]) == 0)
            {
                break;
            }
        }

        switch(pData[0] - 9)
        {
            case 0:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_0 / 2)) / _G_VALUE_DIVIDER_0;
                break;

            case 1:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_1 / 2)) / _G_VALUE_DIVIDER_1;
                break;

            case 2:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_2 / 2)) / _G_VALUE_DIVIDER_2;
                break;

            case 3:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_3 / 2)) / _G_VALUE_DIVIDER_3;
                break;

            case 4:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_4 / 2)) / _G_VALUE_DIVIDER_4;
                break;

            case 5:
                *pusDelta = (*pusDelta + (_G_VALUE_DIVIDER_5 / 2)) / _G_VALUE_DIVIDER_5;
                break;

            default:
                break;
        }

        return (pData[0] - 7);
    }

    return 1;
}

//--------------------------------------------------
// Description  : ADC Clock Fast Lock adjust.
// Input Value  : usCurrHTotal    --> IHTotal.
// Output Value : Return _TRUE if adjust successful.
//--------------------------------------------------
bit ScalerAPLLFastLockAdjust(WORD usCurrHTotal)
{
    BYTE ucMcode = 0;
    BYTE ucNcode = 0;
    SBYTE chKcode = 0;
    WORD usIcode = 0;
    WORD usPcode = 0;
    DWORD ulClockRatio = 0;

    // Get New PLL Divider
    if(ScalerAPLLGetSumI(&g_stPLLApllData.ulDivider) == _FALSE)
    {
        DebugMessageAnalog("5. Measure Sum I Fail", 0);

        // Set usCurrHTotal, M ocde, K code
        ScalerSetBit(P1_B1_PLLDIV_H, ~0x0F, (BYTE)(((usCurrHTotal - 1) >> 8) & 0x000f));
        ScalerSetByte(P1_B2_PLLDIV_L, (BYTE)((usCurrHTotal - 1) & 0x00ff));

        // Set the fast PLL setting by double buffer method
        ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

        if(ScalerTimerPollingFlagProc(100, P1_AA_FAST_PLL_CTRL, _BIT6, 0) == _FALSE)
        {
            return _FALSE;
        }
        else
        {
            return _TRUE;
        }
    }

    // Enable Fast PLL Mechanism
    ScalerSetByte(P1_AA_FAST_PLL_CTRL, 0x20);

    // Calculate Clock Ratio = usCurrHTotal / Old IH-Total
    ulClockRatio = (((DWORD)0x01 << 30) / ScalerAPLLGetIHTotal()) * usCurrHTotal;

    // Calculate New PLL Divider = Old PLL Divider x (New Clock / Old IH-Total) = Old PLL Divider x Clock Ratio
    PDATA_DWORD(0) = ((g_stPLLApllData.ulDivider & 0xffff0000) >> 16) * ((ulClockRatio & 0xffff0000) >> 16);
    PDATA_DWORD(1) = ((g_stPLLApllData.ulDivider & 0xffff0000) >> 16) * ((ulClockRatio & 0x0000ffff) >> 0);
    PDATA_DWORD(1) += ((g_stPLLApllData.ulDivider & 0x0000ffff) >> 0) * ((ulClockRatio & 0xffff0000) >> 16);
    PDATA_DWORD(2) = ((g_stPLLApllData.ulDivider & 0x0000ffff) >> 0) * ((ulClockRatio & 0x0000ffff) >> 0);
    PDATA_DWORD(3) = (PDATA_DWORD(0) << (16 - 14)) + (PDATA_DWORD(1) >> 14) + (PDATA_DWORD(2) >> (16 + 14));

    // Get M code, K code
    ucMcode = (BYTE)(PDATA_DWORD(3) >> 24);
    chKcode = (((BYTE)(PDATA_DWORD(3) >> 16) & 0xf0) >> 4) & 0x0f;

    if(chKcode > 7)
    {
        ucMcode += 1;
        chKcode -= 16;
    }

    // Set usCurrHTotal, M ocde, K code
    ScalerSetBit(P1_B1_PLLDIV_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usCurrHTotal - 1) & 0x0F));
    ScalerSetByte(P1_B2_PLLDIV_L, LOBYTE(usCurrHTotal - 1));
    ScalerSetByte(P1_AC_PLL_M, (ucMcode - 3));
    pData[0] = ScalerGetBit(P1_AD_PLL_N, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(P1_AD_PLL_N, ((chKcode & 0x0f) << 4) | pData[0]);

    // Calculate Sum_I (22 bits)
    PDATA_DWORD(0) = (PDATA_DWORD(3) & 0x000FFFFF) << 2;

    // Set Sum_I (22 bits)
    ScalerSetBit(P1_F7_FAST_PLL_SUM_I_26_24, ~(_BIT2 | _BIT1 | _BIT0), ((BYTE)(PDATA_DWORD(0) >> 24) & 0x07));
    ScalerSetByte(P1_F8_FAST_PLL_SUM_I_23_16, (BYTE)(PDATA_DWORD(0) >> 16));
    ScalerSetByte(P1_F9_FAST_PLL_SUM_I_15_8, (BYTE)(PDATA_DWORD(0) >> 8));
    ScalerSetByte(P1_FA_FAST_PLL_SUM_I_7_0, (BYTE)(PDATA_DWORD(0) >> 0));

    // Read PFD Calibrated result
    ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, _BIT7); // Enable PFD Calibration
    if(ScalerTimerPollingFlagProc(100, P1_A4_PFD_CALIBRATED_RESULTS_H, _BIT7, 0) == _TRUE)
    {
        g_stPLLApllData.usPEValue = (ScalerGetWord(P1_A4_PFD_CALIBRATED_RESULTS_H) & 0xFFF);
        g_stPLLApllData.usPEValue = (WORD)((DWORD)1000000 / ((DWORD)g_stPLLApllData.usPEValue * _SYS_CLK_KHZ / 1000)); // Unit : ps
    }
    else
    {
        ScalerSetBit(P1_A4_PFD_CALIBRATED_RESULTS_H, ~_BIT7, 0x00);
        return _FALSE;
    }

    // Calculate I code
    usIcode = (WORD)(((((DWORD)GET_INPUT_TIMING_HFREQ() + 5) / 10) * g_stPLLApllData.usPEValue * (PDATA_DWORD(3) / 100000)) / 20000);
    usIcode = (usIcode / 64) & 0x00007fff; // n = 64 x 8 = 512

    // The minimum value of I code is 1.
    if(usIcode < 1)
    {
        usIcode = 1;
    }

    // Set I code
    ScalerSetByte(P1_A1_I_CODE_M, (BYTE)(usIcode >> 8));
    ScalerSetByte(P1_A2_I_CODE_L, (BYTE)usIcode);

    // Get N Code
    ucNcode = ScalerGetByte(P1_AD_PLL_N);
    ucNcode = (ucNcode & _BIT3) ? 1 : ((ucNcode & 0x07) + 2);
    DebugMessageAnalog("Fast Pll N Code =", ucNcode);

    // Calculate P code
    usPcode = (WORD)(((DWORD)191 * usIcode * _EXT_XTAL / ((ucNcode * GET_INPUT_TIMING_HFREQ() + 5) / 10)) >> 7); // Total Gain = 192/512

    // Get G value (ucData[15])
    pData[15] = ScalerAPLLGetAPLLGValue(&usPcode);

    // Set G value
    ScalerSetByte(P1_B6_P_CODE_MAPPING_METHOD, (pData[15] << 2));

    // Set P code
    ScalerSetByte(P1_A3_P_CODE, (BYTE)usPcode);

    // Set the P code Maximum
    ScalerSetByte(P1_B9_DDS_MIX_2, 0xFF);
    ScalerSetByte(P1_BA_DDS_MIX_3, 0xFF);

    // Coast Sent into APLL condition : Capture unlock && Coast Signal Enable
    if(((ScalerGetBit(P0_4E_HSYNC_TYPE_DETECTION_FLAG, _BIT0)) == _BIT0) && ((ScalerGetBit(P0_48_SYNC_INVERT, _BIT6)) == _BIT6))
    {
        // APLL Setting Apply at the End of Coast Window
        ScalerSetBit(P1_A0_PLL_DIV_CTRL, ~_BIT0, _BIT0);
    }
    else
    {
        // APLL Setting Apply at the End of DEN
        ScalerSetBit(P1_A0_PLL_DIV_CTRL, ~_BIT0, 0x00);
    }

    // Set the fast PLL setting by double buffer method
    ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    if(ScalerTimerPollingFlagProc(100, P1_AA_FAST_PLL_CTRL, _BIT6, 0) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}


//--------------------------------------------------
// Description  : Get Sum I value
// Input Value  : pusDiv -- > Sum I change to divider par
// Output Value : Divider Pointor
//--------------------------------------------------
bit ScalerAPLLGetSumI(DWORD *pulDiv)
{
    BYTE pucData[5] = {0};
    BYTE ucMcode = 0;
    SBYTE chKcode = 0;
    SBYTE chKValue = 0;
    SDWORD lSumI = 0;
    SDWORD lTemp = 0;

    // Disable Sum_i Measure
    ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~(_BIT7 | _BIT2), 0x00);

    // Get Sum_I (27 bits)
    for(pucData[4] = 0; pucData[4] < _APLL_SUM_I_READ_COUNT; pucData[4]++)
    {
        // Enable Sum_i Measure
        ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~(_BIT7 | _BIT2), _BIT2);

        if(ScalerTimerPollingFlagProc(100, P1_AA_FAST_PLL_CTRL, _BIT2, 0) == _TRUE) // Check Measure Sum_I
        {
            // Disable Sum_i Measure
            ScalerSetBit(P1_AA_FAST_PLL_CTRL, ~(_BIT7 | _BIT2), 0x00);
            ScalerRead(P1_FB_FAST_PLL_SUM_I_MEASURE_26_24, 4, pucData, _AUTOINC);

            lTemp = ((((DWORD)pucData[0] & 0x07) << 24) | ((DWORD)pucData[1] << 16) | ((DWORD)pucData[2] << 8) | ((DWORD)pucData[3]));

            // To check the signed bit (Bit_26) of SUM_I
            if((pucData[0] & _BIT2) != 0x00)
            {
                lTemp |= 0xF8000000;
            }

            lSumI += lTemp;
            lTemp = 0;
        }
        else
        {
            ScalerSetByte(P1_AA_FAST_PLL_CTRL, 0x00);

            return _FALSE;
        }
    }

    lSumI = lSumI / _APLL_SUM_I_READ_COUNT;

    // Get K code
    pData[0] = ScalerGetBit(P1_AD_PLL_N, 0xF0);

    if((pData[0] & _BIT7) != 0x00) // Register chKcode is negative value
    {
        chKcode = (SBYTE)(0xF8 | (pData[0] >> 4));
    }
    else
    {
        chKcode = (pData[0] >> 4);
    }

    // Get K Value (4 bits for bit25 ~ bit22) and Set Sum I
    if(lSumI < 0)
    {
        DWORD ulSumI = 0 - lSumI;
        chKValue = 0 - (BYTE)((ulSumI >> 22) & 0x000000FF);
        lSumI = 0x400000 - (ulSumI & 0x003fffff); // 0x400000 = 2^22
        chKcode -= 1;
    }
    else
    {
        chKValue = (BYTE)((lSumI >> 22) & 0x000000FF);
    }

    // Compensate K Value
    chKcode = chKcode + chKValue;

    // Get M code
    ucMcode = ScalerGetByte(P1_AC_PLL_M) + 3;

    // Set K code >= 0
    if(chKcode < 0)
    {
        ucMcode -= 1;
        chKcode += 16;
    }

    *pulDiv = ((DWORD)ucMcode << (26 - 2)) + (((DWORD)chKcode & 0x0000000f) << (22 - 2)) + (((DWORD)lSumI & 0x003fffff) >> 2);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Apll H-Total Divider.
// Input Value  : None
// Output Value : None.
//--------------------------------------------------
WORD ScalerAPLLGetIHTotal(void)
{
    return ((((WORD)(ScalerGetByte(P1_B1_PLLDIV_H)) & 0x000F) << 8) | ScalerGetByte(P1_B2_PLLDIV_L)) + 1;
}

//--------------------------------------------------
// Description  : Apply Phase setting.
// Input Value  : ucPhase    --> For Apply  Phase step.
// Output Value : None.
//--------------------------------------------------
void ScalerPLLSetPhase(BYTE ucPhase, WORD usVfreq)
{
    BYTE ucEdgePhase = 0;
    BYTE ucEdgePhaseTemp = 0;
    BYTE ucLeftBound = 0;
    BYTE ucRightBound = 0;
    DWORD ulDotClock = 0;

    ucPhase = ucPhase & 0x3f;

    ///////////////////////////////////////////////////////////////////////////////////////
    // Code below is to select stable HSYNC latch edge.                                  //
    // Calculating delay between input clock into ADC and output from ADC.               //
    // Original Formula :                                                                //
    // select = 64 * 6.95  * ulRate / 1000000;                                           //
    ///////////////////////////////////////////////////////////////////////////////////////

    // Get the current IHTotal of ADC
    ulDotClock = (DWORD)(ScalerAPLLGetIHTotal()) * ScalerVgaSyncProcMeasureIHFreqByStableMeasure();
    PDATA_DWORD(0) = ((DWORD)ScalerAPLLGetIHTotal() * GET_INPUT_TIMING_VTOTAL() * usVfreq) / 1000;

    // Get phase delay count
    ucEdgePhase = (ulDotClock * g_usVgaTopPhaseDelayTime / 10000000) + _PHASE_DELAY_HALF_PERIOD_SHIFT;

    // Get phase delay count reference mode table
    ucEdgePhaseTemp = (PDATA_DWORD(0) * g_usVgaTopPhaseDelayTime / 10000000) + _PHASE_DELAY_HALF_PERIOD_SHIFT;

#if(_HW_VGA_PHASE_DELAY_TIME < 0)

    // Negate Hs delay meta-stable phase
    ucEdgePhase = (~ucEdgePhase & 0x3F);
    ucEdgePhaseTemp = (~ucEdgePhaseTemp & 0x3F);

#endif

    DebugMessageAnalog("Measure edge phase", ucEdgePhase);
    DebugMessageAnalog("Mode table edge phase", ucEdgePhaseTemp);

    // Eliminate measurement error if difference of edge phase is small
    if(ABSDWORD(ucEdgePhase, ucEdgePhaseTemp) <= _PHASE_DELAY_EDGEPHASE_THRESHOLD)
    {
        ucEdgePhase = ucEdgePhaseTemp;
    }

    ucLeftBound = ((ucEdgePhase + 64 - 12) % 64);
    ucRightBound = ((ucEdgePhase + 12) % 64);

    if(ucLeftBound < ucRightBound) // case1
    {
        if(ucPhase <= ucLeftBound)
        {
            ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3), 0x00);
        }
        else if((ucPhase > ucLeftBound) && (ucPhase <= ucRightBound))
        {
            ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        }
        else if(ucPhase > ucRightBound)
        {
            ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3), _BIT4);
        }
    }
    else // case 2
    {
        if(ucPhase < ucRightBound)
        {
            ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3), _BIT3);
        }
        else if((ucPhase >= ucRightBound) && (ucPhase < ucLeftBound))
        {
            ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3), 0x00);
        }
        else if(ucPhase >= ucLeftBound)
        {
            ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        }
    }

    // Phase Select Method for Look Up Table (default)
    pData[0] = (ScalerGetByte(P1_B1_PLLDIV_H) | _BIT6);
    ScalerSetByte(P1_B1_PLLDIV_H, pData[0]);

    // Set phase
    if(ScalerGetBit(P1_B1_PLLDIV_H, _BIT4) == _BIT4)
    {
        ScalerSetBit(P1_B4_PLLPHASE_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucPhase << 1) & (~_BIT7)));
    }
    else
    {
        ScalerSetBit(P1_B4_PLLPHASE_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucPhase & (~_BIT7)));
    }

    // Apply the above setting by setting Double Buffer Ready in VGIP
    ScalerVgaTopDoubleBufferApply();

    // Apply phase write port
    ScalerSetByte(P1_B3_PLLPHASE_CTRL0, ScalerGetByte(P1_B3_PLLPHASE_CTRL0));
}

#endif // End of #if(_VGA_SUPPORT == _ON)



