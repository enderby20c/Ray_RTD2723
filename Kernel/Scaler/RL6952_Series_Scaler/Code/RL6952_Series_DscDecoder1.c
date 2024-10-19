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
// ID Code      : RL6952_Series_DscDecoder1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DSCDECODER1__

#include "ScalerFunctionInclude.h"
#include "DscDecoder1/ScalerDscDecoder1.h"

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DSC1 Set ALPM T1 Vstart
// Input Value  : usAlpmT1Vstart
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder1SetAlpmT1Vstart(WORD usAlpmT1Vstart)
{
    // Set VStart
    ScalerSetByte(PF5_36_MN_DPF_ALPM_T1_VST_M, HIBYTE(usAlpmT1Vstart));
    ScalerSetByte(PF5_37_MN_DPF_ALPM_T1_VST_L, LOBYTE(usAlpmT1Vstart));
}
#endif
#endif

//--------------------------------------------------
// Description  : DSC Setting for PLL Power Off Process
// Input Value  : ulvcoFreq --> VCO Frequency(Hz)
//              : ucNcode --> PLL N Code
//              : ucpllo --> divider o code
//              : ucdivs --> divider s code
// Output Value : None
//--------------------------------------------------
void ScalerDscDecoder1SetPLLNfOffProc(DWORD ulvcoFreq, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs)
{
    // Power Off PLL
    ScalerSetBit(PF6_A8_DSCPLL_CONTROL, ~_BIT0, _BIT0);

    // Icp = LoopDivider* 0.25
    PDATA_DWORD(0) = ((DWORD)ucNcode * 20) / 4;

    pData[1] = (PDATA_DWORD(0) + 25) / 50;
    pData[1] -= (pData[1] == 0) ? 0 : 1;

    // Set Icp , RS:12.5K
    pData[2] = (_BIT7 | _BIT4 | _BIT3 | (pData[1] & 0x07));
    ScalerSetByte(PF6_A6_DSCPLL_0, pData[2]);

    // Set Vco Band11, Ipi
    if(ulvcoFreq < 400000000)
    {
        pData[1] = 0;
    }
    else if(ulvcoFreq < 500000000)
    {
        pData[1] = 1;
    }
    else if(ulvcoFreq < 600000000)
    {
        pData[1] = 2;
    }
    else
    {
        pData[1] = 3;
    }

    // Enable Charge Pump, Set Ipi, Disable PI bypass
    ScalerSetBit(PF6_A7_DSCPLL_1, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT4 | (pData[1] & 0x03)));

    // Set Output Div
    ScalerSetBit(PF6_A5_DSCPLL_DIVIDER1, ~(_BIT1 | _BIT0), ucpllo);
    ScalerSetBit(PF5_03_DSC_DIV_CTRL0, ~(_BIT7 | _BIT6), (ucdivs << 6));
}

//--------------------------------------------------
// Description  : DSC PLL Setting for PLL Power Off Process
// Input Value  : ucNcode --> PLL N Code
//              : ucFcode_MSB4b --> PLL F Code (MSB 4 bits)
//              : usFcode_LSB16b --> PLL F Code (LSB 16 bits)
// Output Value : None
//--------------------------------------------------
bit ScalerDscDecoder1SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b)
{
    // PI Control Enable
    ScalerSetBit(PF6_C5_TRACKING_5, ~(_BIT7 | _BIT6), _BIT7);

    // Power On DSC PLL
    ScalerSetBit(PF6_A8_DSCPLL_CONTROL, ~_BIT0, 0x00);

    // Delay 200us
    // Delay Time us [200,x]
    DELAY_XUS(200);

    // Enable VCO/4 & High VCO frequency
    ScalerSetBit(PF6_A8_DSCPLL_CONTROL, ~(_BIT7 | _BIT6), _BIT7);

    // Check N code must set to >= 5
    ucNcode = ucNcode - 2;

    if(ucNcode < 5)
    {
        DebugMessageDSC("pll N Code is out of Spec", ucNcode);

        ucNcode = 5;

        return _FALSE;
    }

    // Set N[7:0]
    ScalerSetByte(PF6_AD_N_F_CODE_1, ucNcode);

    // Set F[19:16] Code
    ScalerSetByte(PF6_AE_N_F_CODE_2, (ucFcode_MSB4b & 0x0F));

    // Set F[15:8] Code
    ScalerSetByte(PF6_AF_N_F_CODE_3, ((usFcode_LSB16b & 0xFF00) >> 8));

    // Set F[7:0] Code
    ScalerSetByte(PF6_B0_N_F_CODE_4, (usFcode_LSB16b & 0x00FF));

    // Load N.F
    ScalerSetBit(PF6_AC_N_F_CODE_0, ~_BIT0, _BIT0);

    return _TRUE;
}
#endif // End of #if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
