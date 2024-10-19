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
// ID Code      : ScalerHdmiArcTxPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMIARCTXPHY__

#include "ScalerFunctionInclude.h"
#include "HdmiArcTxPhy/ScalerHdmiArcTxPhy.h"

#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
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
// Description  : Scaler HDMI ARC Tx Phy Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyInitial(void)
{
    // reg_earc_data_sel = eARC mode
    // enable earc power(reg_pow_earc_mbias = 1)
    ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // enable ldo
    ScalerSetBit(PE6_01_EARC_ARC_TX_APHY_CTRL_1, ~_BIT7, _BIT7);

    // reg_arc_res_sel = 0x7
    ScalerSetBit(PE6_0D_EARC_ARC_TX_IMPEDANCE_2, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Phy Set ARC Mode
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhySetArcMode(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // set Tx phy to ARC Mode(Enable ARC output)
        ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT7, 0x00);
    }
    else
    {
        // set Tx phy to eARC Mode(Disable ARC output)
        ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Phy Power Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyPowerOff(void)
{
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxPhyEarcDiffDrivingPower(_OFF);
    ScalerHdmiArcTxPhyEarcCmDrivingPower(_OFF);
#endif

    ScalerHdmiArcTxPhyPllPowerOff();

    // Disable ARC output
    ScalerHdmiArcTxPhySetArcMode(_DISABLE);

    // disable mbias
    ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT6, 0x00);

    // disable ldo
    ScalerSetBit(PE6_01_EARC_ARC_TX_APHY_CTRL_1, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Phy PLL Power Off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyPllPowerOff(void)
{
    // disable pll_oeb
    ScalerSetBit(PE6_12_EARC_ARC_TX_NF_PLL_CTRL_2, ~_BIT7, _BIT7);

    // reset pll
    ScalerSetBit(PE6_10_EARC_ARC_TX_NF_PLL_CTRL_0, ~(_BIT6 | _BIT5), 0x00);

    // disable pll power
    ScalerSetBit(PE6_10_EARC_ARC_TX_NF_PLL_CTRL_0, ~(_BIT7), 0x00);
}

//--------------------------------------------------
// Description  : Scaler HDMI ARC Tx Phy Set PLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhySetPll(void)
{
    DebugMessageArcTx("[ARC Tx] audio output sampling freq", GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ());

    //====== Initial eARC Tx NF PLL =====//
    // NF pll pow disable
    ScalerSetBit(PE6_10_EARC_ARC_TX_NF_PLL_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // disable pll output clk
    ScalerSetBit(PE6_12_EARC_ARC_TX_NF_PLL_CTRL_2, ~_BIT7, _BIT7);

    // reg_earctx_xtal_in_sel = 3.3V xtal
    ScalerSetBit(PE6_11_EARC_ARC_TX_NF_PLL_CTRL_1, ~_BIT7, 0x00);

    // xtal_in_src_sel = gdi_clk(27M)
    ScalerSetBit(PE6_11_EARC_ARC_TX_NF_PLL_CTRL_1, ~(_BIT6 | _BIT5), 0x00);

    // pre_div = 1
    ScalerSetBit(PE6_11_EARC_ARC_TX_NF_PLL_CTRL_1, ~(_BIT1 | _BIT0), 0x00);

    // Set NF Code
    switch(GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ())
    {
        case _AUDIO_FREQ_PACKET_32K:
        case _AUDIO_FREQ_PACKET_48K:
        case _AUDIO_FREQ_PACKET_64K:
        case _AUDIO_FREQ_PACKET_96K:
        case _AUDIO_FREQ_PACKET_128K:
        case _AUDIO_FREQ_PACKET_192K:
        case _AUDIO_FREQ_PACKET_256K:
        case _AUDIO_FREQ_PACKET_384K:
        case _AUDIO_FREQ_PACKET_768K:

            // N = 31 = 0x1F
            ScalerSetByte(PE5_A1_NF_CODE_CTRL_1, 0x1F);

            // F = 344789 = 0x542D5
            ScalerSetByte(PE5_A2_NF_CODE_CTRL_2, 0x05);
            ScalerSetByte(PE5_A3_NF_CODE_CTRL_3, 0x42);
            ScalerSetByte(PE5_A4_NF_CODE_CTRL_4, 0xD5);

            // max N = 32 = 0x20
            ScalerSetByte(PE5_A5_NF_CODE_MAX, 0x20);

            // min N = 30 = 0x1F
            ScalerSetByte(PE5_A6_NF_CODE_MIN, 0x1E);

            // load N.F code
            ScalerSetBit(PE5_A0_NF_CODE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), _BIT7);

            break;

        case _AUDIO_FREQ_PACKET_44_1K:
        case _AUDIO_FREQ_PACKET_88_2K:
        case _AUDIO_FREQ_PACKET_176_4K:
        case _AUDIO_FREQ_PACKET_352_8K:
        case _AUDIO_FREQ_PACKET_705_6K:

            // N = 28 = 0x1C
            ScalerSetByte(PE5_A1_NF_CODE_CTRL_1, 0x1C);

            // F = 565812 = 0x8A234
            ScalerSetByte(PE5_A2_NF_CODE_CTRL_2, 0x08);
            ScalerSetByte(PE5_A3_NF_CODE_CTRL_3, 0xA2);
            ScalerSetByte(PE5_A4_NF_CODE_CTRL_4, 0x34);

            // max N = 29 = 0x1D
            ScalerSetByte(PE5_A5_NF_CODE_MAX, 0x1D);

            // min N = 27 = 0x1B
            ScalerSetByte(PE5_A6_NF_CODE_MIN, 0x1B);

            // load N.F code
            ScalerSetBit(PE5_A0_NF_CODE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), _BIT7);

            break;

        case _AUDIO_FREQ_PACKET_512K:

            // N = 42 = 0x2A
            ScalerSetByte(PE5_A1_NF_CODE_CTRL_1, 0x2A);

            // F = 809245 = 0xC591D
            ScalerSetByte(PE5_A2_NF_CODE_CTRL_2, 0x0C);
            ScalerSetByte(PE5_A3_NF_CODE_CTRL_3, 0x59);
            ScalerSetByte(PE5_A4_NF_CODE_CTRL_4, 0x1D);

            // max N = 43 = 0x2B
            ScalerSetByte(PE5_A5_NF_CODE_MAX, 0x2B);

            // min N = 41 = 0x29
            ScalerSetByte(PE5_A6_NF_CODE_MIN, 0x29);

            // load N.F code
            ScalerSetBit(PE5_A0_NF_CODE_CTRL_0, ~(_BIT7 | _BIT6 | _BIT4), _BIT7);

            break;

        default:
            break;
    }

    // reg_earc_pll_k
    if((GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_32K) ||
       (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_64K) ||
       (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_128K))
    {
        // reg_earc_pll_k = 6
        ScalerSetBit(PE6_14_EARC_ARC_TX_NF_PLL_CTRL_4, ~(_BIT7 | _BIT6 | _BIT5), _BIT7)
    }
    else if((GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_44_1K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_48K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_88_2K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_96K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_176_4K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_192K))
    {
        // reg_earc_pll_k = 4
        ScalerSetBit(PE6_14_EARC_ARC_TX_NF_PLL_CTRL_4, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5))
    }
    else if((GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_352_8K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_384K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_512K))
    {
        // reg_earc_pll_k = 2
        ScalerSetBit(PE6_14_EARC_ARC_TX_NF_PLL_CTRL_4, ~(_BIT7 | _BIT6 | _BIT5), _BIT5)
    }
    else
    {
        // reg_earc_pll_k = 1
        ScalerSetBit(PE6_14_EARC_ARC_TX_NF_PLL_CTRL_4, ~(_BIT7 | _BIT6 | _BIT5), 0x00)
    }

    // reg_tx_div
    if((GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_32K) ||
       (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_44_1K) ||
       (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_48K))
    {
        // reg_tx_div = 4
        ScalerSetBit(PE6_14_EARC_ARC_TX_NF_PLL_CTRL_4, ~(_BIT1 | _BIT0), _BIT1)
    }
    else if((GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_64K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_88_2K) ||
            (GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() == _AUDIO_FREQ_PACKET_96K))
    {
        // reg_tx_div = 2
        ScalerSetBit(PE6_14_EARC_ARC_TX_NF_PLL_CTRL_4, ~(_BIT1 | _BIT0), _BIT0)
    }
    else
    {
        // reg_tx_div = 1
        ScalerSetBit(PE6_14_EARC_ARC_TX_NF_PLL_CTRL_4, ~(_BIT1 | _BIT0), 0x00)
    }

    // NF pll pow enable
    ScalerSetBit(PE6_10_EARC_ARC_TX_NF_PLL_CTRL_0, ~_BIT7, _BIT7);

    // pll_rstb = enable
    ScalerSetBit(PE6_10_EARC_ARC_TX_NF_PLL_CTRL_0, ~_BIT6, _BIT6);

    // pll_vco = enable
    ScalerSetBit(PE6_10_EARC_ARC_TX_NF_PLL_CTRL_0, ~_BIT5, _BIT5);

    // enable pll output clk
    ScalerSetBit(PE6_12_EARC_ARC_TX_NF_PLL_CTRL_2, ~_BIT7, 0x00);

    DELAY_XUS(1000);
}

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Phy Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyEarcInitial(void)
{
    // reg_earc_data_sel = eARC mode
    // enable earc power(reg_pow_earc_mbias = 1)
    ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // df_ib_sel = 0x5
    ScalerSetBit(PE6_08_EARC_ARC_TX_DM_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // cm_ib_sel = 0x2
    ScalerSetBit(PE6_05_EARC_ARC_TX_CM_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

    // reg_cm_trf_sel = 0x2
    ScalerSetBit(PE6_05_EARC_ARC_TX_CM_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // reg_vol_level_extra = 1.5mA
    ScalerSetBit(PE6_03_EARC_ARC_TX_VOL_CTRL, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // enable ldo
    ScalerSetBit(PE6_01_EARC_ARC_TX_APHY_CTRL_1, ~_BIT7, _BIT7);

    // reg_r60_sel = 0x9
    ScalerSetBit(PE6_0C_EARC_ARC_TX_IMPEDANCE_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

    // reg_r300_sel = 0x5
    ScalerSetBit(PE6_0C_EARC_ARC_TX_IMPEDANCE_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // enable R60&R300([0]: R60P [1]: R06N [2]: R300P [3]: R300N)
    ScalerSetBit(PE6_0B_EARC_ARC_TX_IMPEDANCE_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Phy Set Duty
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyEarcSetDuty(void)
{
    // set duty
    if(GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ() > _AUDIO_FREQ_PACKET_192K)
    {
        // duty = 37.5/60
        ScalerSetBit(PE6_07_EARC_ARC_TX_DM_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(PE6_07_EARC_ARC_TX_DM_CTRL_0, ~_BIT5, _BIT5);
        ScalerSetBit(PE6_07_EARC_ARC_TX_DM_CTRL_0, ~(_BIT7 | _BIT6), 0x00);
    }
    else
    {
        // duty = 40/60
        ScalerSetBit(PE6_07_EARC_ARC_TX_DM_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(PE6_07_EARC_ARC_TX_DM_CTRL_0, ~_BIT5, 0x00);
        ScalerSetBit(PE6_07_EARC_ARC_TX_DM_CTRL_0, ~(_BIT7 | _BIT6), 0x00);
    }
}

//--------------------------------------------------
// Description  : bOnOff HDMI eARC Tx Phy Differential Mode Driving Power
// Input Value  : bOnOff
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyEarcDiffDrivingPower(bit bOnOff)
{
    if(bOnOff == _ON)
    {
        // enable df driver
        ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT4, _BIT4);
    }
    else
    {
        // set Tx phy to eARC Mode(Disable ARC output)
        ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT7, _BIT7);

        // disable df driver
        ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Scaler HDMI eARC Tx Phy Common Mode Driving Power
// Input Value  : bOnOff
// Output Value : None
//--------------------------------------------------
void ScalerHdmiArcTxPhyEarcCmDrivingPower(bit bOnOff)
{
    if(bOnOff == _ON)
    {
        // enable cm driver
        ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT5, _BIT5);
    }
    else
    {
        // disable cm driver
        ScalerSetBit(PE6_00_EARC_ARC_TX_APHY_CTRL_0, ~_BIT5, 0x00);
    }
}

#endif // End for #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
#endif // End for #if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
