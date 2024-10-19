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
// ID Code      : RL6952_Series_TmdsMacRx3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_TMDSMACRX3__

#include "ScalerFunctionInclude.h"
#include "TmdsMacRx3/ScalerTmdsMacRx3.h"

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
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
// Description  : Deep Color PLL Off COntrol.
// Input Value  : usVCOFreq, ucPreDiv, ucOutputDiv
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3DPLLOffProc(WORD usVCOFreq, BYTE ucPreDiv, BYTE ucOutputDiv, BYTE ucNcode)
{
    // Power Off DPLL
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // Set Rs[7:5] = 001 = 12.5k
    ScalerSetBit(P68_C5_M2PLL_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Set Icp
    if(ucNcode == 16)
    {
        // Icp[2:0] = 5
        ScalerSetBit(P68_C5_M2PLL_0, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // Icp[2:0] = 7.5
        ScalerSetBit(P68_C5_M2PLL_0, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
    }

    // Set IPI = 10uA
    if((6000 <= usVCOFreq) && (usVCOFreq < 7700))
    {
        ScalerSetBit(P68_C6_M2PLL_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
    // Set IPI = 5uA
    else if((5000 <= usVCOFreq) && (usVCOFreq < 6000))
    {
        ScalerSetBit(P68_C6_M2PLL_1, ~(_BIT1 | _BIT0), _BIT1);
    }
    // Set IPI = 3.3uA
    else if((4000 <= usVCOFreq) && (usVCOFreq < 5000))
    {
        ScalerSetBit(P68_C6_M2PLL_1, ~(_BIT1 | _BIT0), _BIT0);
    }
    // Set IPI = 2.5uA
    else
    {
        ScalerSetBit(P68_C6_M2PLL_1, ~(_BIT1 | _BIT0), 0x00);
    }

    // Enable Pre-Div
    if(ucPreDiv >= 2)
    {
        ScalerSetBit(P68_C4_M2PLL_DIVIDER1, ~_BIT7, 0x00);
        ScalerSetByte(P68_C3_M2PLL_DIVIDER0, (ucPreDiv - 2));
    }
    else // Disable Pre-Div
    {
        ScalerSetBit(P68_C4_M2PLL_DIVIDER1, ~_BIT7, _BIT7);
        ScalerSetByte(P68_C3_M2PLL_DIVIDER0, 0x00);
    }

    // Set Output-Div
    if(ucOutputDiv <= 8)
    {
        // analog div = 1
        ScalerSetBit(P68_C4_M2PLL_DIVIDER1, ~(_BIT1 | _BIT0), 0x00);

        // digital div = ucOutputDiv
        ScalerSetBit(P2E_B0_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), (ucOutputDiv - 1));
    }
    else if((ucOutputDiv / 2) <= 8)
    {
        // analog div = 2
        ScalerSetBit(P68_C4_M2PLL_DIVIDER1, ~(_BIT1 | _BIT0), _BIT0);

        // digital div = (ucOutputDiv / 2) - 1
        ScalerSetBit(P2E_B0_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), ((ucOutputDiv / 2) - 1));
    }
    else if((ucOutputDiv / 4) <= 8)
    {
        // analog div = 4
        ScalerSetBit(P68_C4_M2PLL_DIVIDER1, ~(_BIT1 | _BIT0), _BIT1);

        // digital div = (ucOutputDiv / 4) - 1
        ScalerSetBit(P2E_B0_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), ((ucOutputDiv / 4) - 1));
    }
    else
    {
        // analog div = 8
        ScalerSetBit(P68_C4_M2PLL_DIVIDER1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // digital div = (ucOutputDiv / 8) - 1
        ScalerSetBit(P2E_B0_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), ((ucOutputDiv / 8) - 1));
    }

    // Set CP Enable, close loop
    // Set Vc 0.5v
    // Set LPF Enable, VCO reset set to normal
    ScalerSetBit(P68_C9_M2PLL_DUMMY, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT0));

    // Set VCO Mode
    ScalerSetBit(P68_C6_M2PLL_1, ~_BIT7, _BIT7);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(P68_C7_M2PLL_CONTROL, ~_BIT1, 0x00);
}

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Rx3 HDMI Audio Off Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3SetAudioPLLOffProc(void)
{
    // DPLL power down
    ScalerSetBit(P72_87_PORT_PAGE72_HDMI_DPLL_ANASET_1, ~_BIT0, _BIT0);

    // Set Input Clk to GDI CLK
    ScalerSetBit(P72_81_PORT_PAGE72_HDMI_DPLL_CTRL0, ~(_BIT7 | _BIT6), 0x00);

    // Set O code 0x00          [6:5]
    // Bypass Predivider        [4]
    ScalerSetBit(P72_86_PORT_PAGE72_HDMI_DPLL_ANASET_0, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

    // Set pi Current to 3.3uA[6:5]
    ScalerSetBit(P72_88_PORT_PAGE72_HDMI_DPLL_ANASET_2, ~(_BIT6 | _BIT5), 0x00);

    // Set icp [7:5] = 001
    // Set rs = 12.5k
    ScalerSetBit(P72_89_PORT_PAGE72_HDMI_DPLL_ANASET_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

    // Set CP Enable, close loop
    // Set Vc 0.5v
    // Set LPF Enable, VCO reset set to normal
    ScalerSetBit(P72_87_PORT_PAGE72_HDMI_DPLL_ANASET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3));

    // Set VCO Mode
    ScalerSetBit(P72_8B_PORT_PAGE72_HDMI_DPLL_WD_1, ~(_BIT4 | _BIT3), _BIT3);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        // Set double buffer
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Enable SDM [1]
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_2D_PORT_PAGE77_HDMI_AAPNR, ~(_BIT3 | _BIT1), _BIT1);
    }
    else
#endif
    {
        // Set double buffer
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Enable SDM [1]
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_2D_PORT_PAGE72_HDMI_AAPNR, ~(_BIT3 | _BIT1), _BIT1);
    }
}

//--------------------------------------------------
// Description  : Set Rx3 HDMI Audio N Code
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3SetAudioNCode(BYTE ucNcode)
{
    ScalerSetBit(P72_8E_PORT_PAGE73_HDMI_NF_CODE_1, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucNcode & 0x1F));
}

//--------------------------------------------------
// Description  : Set Rx3 HDMI Audio F Code
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3SetAudioFCode(WORD usFcode)
{
    ScalerSetByte(P72_8F_PORT_PAGE72_HDMI_NF_CODE_2, HIBYTE(usFcode));
    ScalerSetByte(P72_90_PORT_PAGE72_HDMI_NF_CODE_3, LOBYTE(usFcode));
}

//--------------------------------------------------
// Description  : Set Rx3 HDMI Audio Clamp N Code
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerTmdsMacRx3SetAudioClampNCode(void)
{
    // Set Maximum N code for Tracking
    ScalerSetByte(P72_91_PORT_PAGE72_NF_CODE_MAX, (_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE + 1));

    // Set Minimum N code for Tracking
    ScalerSetByte(P72_92_PORT_PAGE72_NF_CODE_MIN, (_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE - 1));
}
#endif
#endif
