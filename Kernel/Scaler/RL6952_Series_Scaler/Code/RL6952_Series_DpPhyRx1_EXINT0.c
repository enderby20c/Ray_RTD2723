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
// ID Code      : RL6952_Series_DpPhyRx1_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPPHYRX1_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx1/ScalerDpPhyRx1.h"


#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX1_SUPPORT == _ON))
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
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SetDFEInitial_EXINT0(void)
{
#if(_DP_PHY_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xCA);
    }
    else if(ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TPS3@8B/10B
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xE2);
    }
    else
#endif
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte_EXINT(PB2_A2_L0_LIMIT_INIT, 0xF8);
    ScalerSetByte_EXINT(PB2_B2_L1_LIMIT_INIT, 0xF8);
    ScalerSetByte_EXINT(PB2_C2_L2_LIMIT_INIT, 0xF8);
    ScalerSetByte_EXINT(PB2_D2_L3_LIMIT_INIT, 0xF8);

    ScalerSetByte_EXINT(PB2_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(PB2_B3_L1_INIT_1, 0xD0);
    ScalerSetByte_EXINT(PB2_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(PB2_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, 0x14);
    ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, 0x14);
    ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, 0x14);
    ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte_EXINT(PB2_A5_L0_INIT_3, 0x03);
    ScalerSetByte_EXINT(PB2_B5_L1_INIT_3, 0x03);
    ScalerSetByte_EXINT(PB2_C5_L2_INIT_3, 0x03);
    ScalerSetByte_EXINT(PB2_D5_L3_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(PB2_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(PB2_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(PB2_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(PB2_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 24
    ScalerSetByte_EXINT(PB2_A9_L0_INIT_7, 0x18);
    ScalerSetByte_EXINT(PB2_B9_L1_INIT_7, 0x18);
    ScalerSetByte_EXINT(PB2_C9_L2_INIT_7, 0x18);
    ScalerSetByte_EXINT(PB2_D9_L3_INIT_7, 0x18);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(PB2_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB2_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SetDFEInitialUnFlip2Lane_EXINT0(void)
{
#if(_DP_PHY_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xCA);
    }
    else if(ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TPS3@8B/10B
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xE2);
    }
    else
#endif
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte_EXINT(PB2_C2_L2_LIMIT_INIT, 0xF8);
    ScalerSetByte_EXINT(PB2_D2_L3_LIMIT_INIT, 0xF8);

    ScalerSetByte_EXINT(PB2_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(PB2_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, 0x14);
    ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte_EXINT(PB2_C5_L2_INIT_3, 0x03);
    ScalerSetByte_EXINT(PB2_D5_L3_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(PB2_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(PB2_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 24
    ScalerSetByte_EXINT(PB2_C9_L2_INIT_7, 0x18);
    ScalerSetByte_EXINT(PB2_D9_L3_INIT_7, 0x18);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(PB2_EF_RESET_1, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(PB2_EF_RESET_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SetDFEInitialFlip2Lane_EXINT0(void)
{
#if(_DP_PHY_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    if(ScalerDpAuxRxGetCodingType_EXINT0(enumInputPort) == _CODING_TYPE_128B132B)
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xCA);
    }
    else if(ScalerDpAuxRxTrainingPatternSet_EXINT0(enumInputPort) == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TPS3@8B/10B
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xE2);
    }
    else
#endif
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte_EXINT(PB2_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0x00);

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte_EXINT(PB2_A2_L0_LIMIT_INIT, 0xF8);
    ScalerSetByte_EXINT(PB2_B2_L1_LIMIT_INIT, 0xF8);

    ScalerSetByte_EXINT(PB2_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(PB2_B3_L1_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, 0x14);
    ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte_EXINT(PB2_A5_L0_INIT_3, 0x03);
    ScalerSetByte_EXINT(PB2_B5_L1_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(PB2_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(PB2_B6_L1_INIT_4, 0x00);

    // Vth Initial Value = 24
    ScalerSetByte_EXINT(PB2_A9_L0_INIT_7, 0x18);
    ScalerSetByte_EXINT(PB2_B9_L1_INIT_7, 0x18);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0xFF);

    ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(PB2_EF_RESET_1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB2_EF_RESET_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}
#endif

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    ScalerDpMacDphyRxLaneSwapSelect_EXINT0(enumInputPort, ScalerDpPhyRxGetPCBLaneMapping_EXINT0(enumInputPort, _DP_LANE_0));

    ScalerDpMacDphyRxLaneCountSet_EXINT0(enumInputPort, (BYTE)ScalerDpAuxRxGetLaneCount_EXINT0(enumInputPort));

    ScalerDpMacDphyRxReset_EXINT0(enumInputPort);

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    if(ScalerTypeCRxCheckTypeCSupportOn_EXINT0(enumInputPort) == _TRUE)
    {
        ScalerDpPhyRx1SetAltModeLaneMapping_EXINT0(ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort), ScalerTypeCRxGetOrientation_EXINT0(enumInputPort));
    }
#endif

    ScalerDpPhyRx1Tp1Measure_EXINT0();

    enumDpNFCodeRef = enumDpNFCodeRef;
}

//--------------------------------------------------
// Description : Initial Signal check for TP1 D10.2 Measure
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp1Measure_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit_EXINT(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_offpn_sync = 1 --> Enable Offpn
    ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort))
    {
        case _DP_LINK_UHBR13_5:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x31);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE1);

            break;

        case _DP_LINK_UHBR10:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x33);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xA2);

            break;

        case _DP_LINK_HBR3:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            break;

        case _DP_LINK_HBR2:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x27);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xC4);

            break;

        case _DP_LINK_HBR:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0x86);

            break;

        case _DP_LINK_RBR:
        default:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0x86);

            break;
    }


    ///////////////////////////
    // DP Mode for Detection //
    ///////////////////////////

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE2);
            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE3);

            // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
            ScalerSetBit_EXINT(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_UHBR10)
            {
                // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
                ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            }
            else
            {
                // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
                ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6), 0x00);
            }

            if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_UHBR13_5)
            {
                // reg_lehv_isel = 0
                ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2), 0x00);
            }
            else
            {
                // reg_lehv_isel = 1
                ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            }

            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane_EXINT0();

            // [7] reg_cp_en_manual = 0 --> CDR Open Loop
            ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

            // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
            ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

            // Enable Foreground Calibration
            ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Delay Time us [0,500] Waiting for K Offset
            for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
            {
                DELAY_5US_EXINT();

                if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
                   ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
                {
                    break;
                }
            }
        }
        else
        {
            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE0);
            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE1);

            // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
            ScalerSetBit_EXINT(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_UHBR10)
            {
                // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
                ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
            }
            else
            {
                // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
                ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT5 | _BIT4), 0x00);
            }

            if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_UHBR13_5)
            {
                // reg_lehv_isel = 0
                ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT1 | _BIT0), 0x00);
            }
            else
            {
                // reg_lehv_isel = 1
                ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            }

            ScalerDpPhyRx1SetDFEInitialFlip2Lane_EXINT0();

            // [7] reg_cp_en_manual = 0 --> CDR Open Loop
            ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

            // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
            ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

            // Enable Foreground Calibration
            ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
            DELAY_5US_EXINT();
            ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Delay Time us [0,500] Waiting for K Offset
            for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
            {
                DELAY_5US_EXINT();

                if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
                   ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
                {
                    break;
                }
            }
        }
    }
    else
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    {
        ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE0);
        ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE1);
        ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE2);
        ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE3);

        // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
        ScalerSetBit_EXINT(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_UHBR10)
        {
            // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
            ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        }
        else
        {
            // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
            ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        }

        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_UHBR13_5)
        {
            // reg_lehv_isel = 0
            ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
        else
        {
            // reg_lehv_isel = 1
            ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }

        ScalerDpPhyRx1SetDFEInitial_EXINT0();

        // [7] reg_cp_en_manual = 0 --> CDR Open Loop
        ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

        // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
        ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

        // Enable Foreground Calibration
        ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        DELAY_5US_EXINT();
        ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [0,500] Waiting for K Offset
        for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
        {
            DELAY_5US_EXINT();

            if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
               ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
               ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
               ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
            {
                break;
            }
        }
    }

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _OFF)
    ScalerDpPhyRx1KOobs_EXINT0();
#endif

    switch(ScalerDpAuxRxGetLaneCount_EXINT0(enumInputPort))
    {
        case _DP_ONE_LANE:

            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX1_D1_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] = (g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] << 3);

            break;

        case _DP_TWO_LANE:

            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX1_D1_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX1_D1_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] = (g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] << 3);
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1] = (g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1] << 3);

            break;

        case _DP_FOUR_LANE:
        default:

            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX1_D1_LANE0, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX1_D1_LANE1, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE2] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX1_D1_LANE2, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE3] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, _DP_PHY_RX1_D1_LANE3, _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_125_CYCLE);

            // Measure Count x 4 for Default ref. Counter = 1000
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] = (g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] << 3);
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1] = (g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1] << 3);
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE2] = (g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE2] << 3);
            g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE3] = (g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE3] << 3);

            break;
    }
}

//--------------------------------------------------
// Description  : DP Phy CTS Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    ScalerDpMacDphyRxLaneSwapSelect_EXINT0(enumInputPort, (g_ucDpPhyRx1CtsCtrl & 0x30) << 2);

    ScalerDpPhyRx1SignalDetection_EXINT0(_DISABLE);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3/2] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            ScalerDpPhyRx1PhyCtsTp1SetPhyUnFlip2Lane_EXINT0(enumDpNFCodeRef);

            // [3/2] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), 0x00);
        }
        else
        {
            // [1/0] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            ScalerDpPhyRx1PhyCtsTp1SetPhyFlip2Lane_EXINT0(enumDpNFCodeRef);

            // [1/0] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        }
    }
    else
#endif
    {
        // [3:0] reg_offpn_sync = 1 --> Enable Offpn
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ScalerDpPhyRx1PhyCtsTp1SetPhy4Lane_EXINT0(enumDpNFCodeRef);

        // [3:0] reg_offpn_sync = 0 --> Disable Offpn
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp2SetPhy_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    ScalerDpMacDphyRxSetCommaDetect_EXINT0(enumInputPort, _ON);

    ScalerDpPhyRx1SignalDetection_EXINT0(_DISABLE);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3/2] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            ScalerDpPhyRx1Tp1SetPhyUnFlip2Lane_EXINT0(_DP_NF_REF_XTAL);
            ScalerDpPhyRx1Tp2SetPhyUnFlip2Lane_EXINT0();

            // [3/2] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), 0x00);
        }
        else
        {
            // [1/0] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            ScalerDpPhyRx1Tp1SetPhyFlip2Lane_EXINT0(_DP_NF_REF_XTAL);
            ScalerDpPhyRx1Tp2SetPhyFlip2Lane_EXINT0();

            // [1/0] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        }
    }
    else
#endif
    {
        // [3:0] reg_offpn_sync = 1 --> Enable Offpn
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ScalerDpPhyRx1Tp1SetPhy4Lane_EXINT0(_DP_NF_REF_XTAL);
        ScalerDpPhyRx1Tp2SetPhy4Lane_EXINT0();

        // [3:0] reg_offpn_sync = 0 --> Disable Offpn
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp3SetPhy_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            ScalerDpPhyRx1Tp3SetPhyUnFlip2Lane_EXINT0();
        }
        else
        {
            ScalerDpPhyRx1Tp3SetPhyFlip2Lane_EXINT0();
        }
    }
    else
#endif
    {
        ScalerDpPhyRx1Tp3SetPhy4Lane_EXINT0();
    }

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp2SetPhy_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    ScalerDpMacDphyRxSetCommaDetect_EXINT0(enumInputPort, _ON);

    ScalerDpPhyRx1SignalDetection_EXINT0(_DISABLE);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3/2] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            ScalerDpPhyRx1PhyCtsTp2SetPhyUnFlip2Lane_EXINT0();

            // [3/2] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), 0x00);
        }
        else
        {
            // [1/0] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            ScalerDpPhyRx1PhyCtsTp2SetPhyFlip2Lane_EXINT0();

            // [1/0] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        }
    }
    else
#endif
    {
        // [3:0] reg_offpn_sync = 1 --> Enable Offpn
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ScalerDpPhyRx1PhyCtsTp2SetPhy4Lane_EXINT0();

        // [3:0] reg_offpn_sync = 0 --> Disable Offpn
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
}

//--------------------------------------------------
// Description : check DFE Coef in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpPhyRx1DFECheck_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE ucVth = 0;
    BYTE ucTap0 = 0;

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpAuxRxGetLaneCount_EXINT0(enumInputPort))
    {
        case _DP_FOUR_LANE:

            // Read Lane3 DFE
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            // Read Lane2 DFE
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ucVth = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit_EXINT(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ucTap0 = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if((ucTap0 == 0x1F) && (ucVth == 0x0C))
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp1SetPhy4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    ////////////////////
    // 4 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit_EXINT(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [3:0] Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_en_vco_lpf = 4'b1111 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_timer_en = 1 for CDR_RDY
    // [3:0] reg_acdr_en = 1
    ScalerSetByte_EXINT(P7A_96_DATA_TIMER_0, 0xFF);

    // reg_en_fld_clk = 4'b1111 --> Enable FLD Clock
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit_EXINT(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_6E_FLD_L1_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_EE_FLD_L3_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit_EXINT(PB1_2F_FLD_L0_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_6F_FLD_L1_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_AF_FLD_L2_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_EF_FLD_L3_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_clkout_manual = 1'b0
    // [3:0] reg_bypass_clk_rdy = 1'b0
    ScalerSetByte_EXINT(P7A_97_DATA_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P7A_99_DATA_TIMER_3, 0x0F);


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSetting4Lane_EXINT0(ScalerDpAuxRxGetLinkRate_EXINT0(ScalerDpPhyRxRxDxMapping_EXINT0(_RX1)), enumDpNFCodeRef);


    //////////////
    // FLD Band //
    //////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));
}

//--------------------------------------------------
// Description  : DP Phy Reset in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1ResetCDR_EXINT0(BYTE ucTp2Result)
{
    BYTE ucBackupCpEn = 0;

    // [3:0] = Lane3-0 CP_EN
    ucBackupCpEn = ((ScalerGetBit_EXINT(PB1_13_FLD_L0_19, _BIT7) >> 7) | (ScalerGetBit_EXINT(PB1_53_FLD_L1_19, _BIT7) >> 6) |
                    (ScalerGetBit_EXINT(PB1_93_FLD_L2_19, _BIT7) >> 5) | (ScalerGetBit_EXINT(PB1_D3_FLD_L3_19, _BIT7) >> 4));

    // MAC Lane0 Fail
    if((ucTp2Result & _BIT0) == 0x00)
    {
        // Fine out PHY Lane
        switch(GET_DP_PHY_RX1_PCB_LANE0_MAPPING())
        {
            case _DP_SCALER_LANE0:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE1:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE2:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE3:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

                break;

            default:
                break;
        }
    }

    // MAC Lane1 Fail
    if((ucTp2Result & _BIT1) == 0x00)
    {
        // Fine out PHY Lane
        switch(GET_DP_PHY_RX1_PCB_LANE1_MAPPING())
        {
            case _DP_SCALER_LANE0:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE1:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE2:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE3:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

                break;

            default:
                break;
        }
    }

    // MAC Lane2 Fail
    if((ucTp2Result & _BIT2) == 0x00)
    {
        // Fine out PHY Lane
        switch(GET_DP_PHY_RX1_PCB_LANE2_MAPPING())
        {
            case _DP_SCALER_LANE0:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE1:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE2:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE3:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

                break;

            default:
                break;
        }
    }

    // MAC Lane3 Fail
    if((ucTp2Result & _BIT3) == 0x00)
    {
        // Fine out PHY Lane
        switch(GET_DP_PHY_RX1_PCB_LANE3_MAPPING())
        {
            case _DP_SCALER_LANE0:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE1:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE2:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);

                break;

            case _DP_SCALER_LANE3:

                // [7] reg_cp_en_manual = 0 --> CDR Open Loop
                ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

                break;

            default:
                break;
        }
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    if((ucBackupCpEn & _BIT0) == _BIT0)
    {
        // [7] reg_cp_en_manual = 1 --> CDR Close Loop
        ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    }

    if((ucBackupCpEn & _BIT1) == _BIT1)
    {
        // [7] reg_cp_en_manual = 1 --> CDR Close Loop
        ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    }

    if((ucBackupCpEn & _BIT2) == _BIT2)
    {
        // [7] reg_cp_en_manual = 1 --> CDR Close Loop
        ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    }

    if((ucBackupCpEn & _BIT3) == _BIT3)
    {
        // [7] reg_cp_en_manual = 1 --> CDR Close Loop
        ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);
    }

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // DP MAC FIFO Reset
    ScalerDpMacDphyRxChannelFifoReset_EXINT0(ScalerDpPhyRxRxDxMapping_EXINT0(_RX1));

    // Delay Time us [25,x] Waiting for FIFO Reset
    DELAY_25US_EXINT();
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp1SetPhy4Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    enumDpNFCodeRef = enumDpNFCodeRef;
    BYTE pucIcp[3];


    ////////////////////
    // 4 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit_EXINT(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [3:0] Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_en_vco_lpf = 4'b1111 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_timer_en = 1 for CDR_RDY
    // [3:0] reg_acdr_en = 1
    ScalerSetByte_EXINT(P7A_96_DATA_TIMER_0, 0xFF);

    // reg_en_fld_clk = 4'b1111 --> Enable FLD Clock
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit_EXINT(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_6E_FLD_L1_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_EE_FLD_L3_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit_EXINT(PB1_2F_FLD_L0_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_6F_FLD_L1_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_AF_FLD_L2_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_EF_FLD_L3_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit_EXINT(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] LANE_EN = 4'b0000 --> Disable LANE_EN
    // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE0);
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE1);
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE2);
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE3);

    switch(g_ucDpPhyRx1CtsCtrl & 0x30)
    {
        case 0x10:

            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE1);

            break;

        case 0x20:

            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE2);

            break;

        case 0x30:

            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE3);

            break;

        default:
        case 0x00:

            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE0);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_clkout_manual = 1'b0
    // [3:0] reg_bypass_clk_rdy = 1'b0
    ScalerSetByte_EXINT(P7A_97_DATA_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P7A_99_DATA_TIMER_3, 0x0F);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitial_EXINT0();

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSetting4Lane_EXINT0(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort), enumDpNFCodeRef);

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _OFF)
    ScalerDpPhyRx1KOobs_EXINT0();
#endif


    //////////////
    // FLD Band //
    //////////////

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0x00);


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    DELAY_5US_EXINT();

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    g_pusDpPhyRx1ClockTarget[0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_1000_CYCLE);

    if(g_pusDpPhyRx1ClockTarget[0] != 0)
    {
        g_pusDpPhyRx1ClockTarget[1] = g_pusDpPhyRx1ClockTarget[0];
        g_pusDpPhyRx1ClockTarget[2] = g_pusDpPhyRx1ClockTarget[0];
        g_pusDpPhyRx1ClockTarget[3] = g_pusDpPhyRx1ClockTarget[0];
    }
}

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Dp Rx1 K OOBS
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerDpPhyRx1KOobs_EXINT0(void)
{
    BYTE ucOobsSenVal = 0;
    BYTE ucOobsOffsetL0 = 0;
    BYTE ucOobsOffsetL2 = 0;
    BYTE ucTemp = 0;

    // [7:6] reg_en_oobs = 2'b11
    // [5:4] reg_oobs_lfps_sel = 2'b00
    ScalerSetBit_EXINT(PB2_1A_OOBS_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

    // [3:2] reg_freq_sel = 2'b00 => oobs frequency = 250M
    ScalerSetBit_EXINT(PB2_1A_OOBS_00, ~(_BIT3 | _BIT2), 0x00);

    // [4:0] reg_oobs_vth_lx = 5'b01000
    ScalerSetBit_EXINT(PB2_1D_OOBS_03, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit_EXINT(PB2_1E_OOBS_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // [7:6] reg_oobs_offset_timeout [9:8] = 2'b11
    // [7:0] reg_oobs_offset_timeout [7:0] = 0xFF
    ScalerSetBit_EXINT(PC9_D5_RX_K_OOBS_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte_EXINT(PC9_D6_RX_K_OOBS_02, 0xFF);

    for(ucOobsSenVal = 0; ucOobsSenVal <= (_BIT1 | _BIT0); ucOobsSenVal++)
    {
        // reg_sen_val_range_l01
        ScalerSetBit_EXINT(PB2_19_LDO_03, ~(_BIT3 | _BIT2), (ucOobsSenVal << 2));

        // [1:0] reg_oobs_offset_ini_l0 [9:8] = 2'b10
        // [7:0] reg_oobs_offset_ini_l0 [7:0] = 0x00
        ScalerSetBit_EXINT(PC9_D9_RX_K_OOBS_05, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetByte_EXINT(PC9_D8_RX_K_OOBS_04, 0x00);

        // [1] reg_oobs_offset_ok_l0 = 1'b0 -> Disable Manual Mode Calibration ok
        ScalerSetBit_EXINT(PC9_D7_RX_K_OOBS_03, ~_BIT1, 0x00);

        // [0] reg_oobs_offset_manual_l0 = 1'b0 -> Calibration Auto Mode
        ScalerSetBit_EXINT(PC9_D7_RX_K_OOBS_03, ~_BIT0, 0x00);

        // [4] reg_rstb_oobs_offset = 1'b0 >> 1'b1 -> reset
        ScalerSetBit_EXINT(PC9_D4_RX_K_OOBS_00, ~_BIT4, 0x00);
        ScalerSetBit_EXINT(PC9_D4_RX_K_OOBS_00, ~_BIT4, _BIT4);

        // [0] reg_oobs_offset_en_l0 = 1'b1 -> Set Calibration Mode Enable
        ScalerSetBit_EXINT(PC9_D4_RX_K_OOBS_00, ~_BIT0, _BIT0);

        // Delay Time us [0,500] Waiting for Calibration Done
        for(ucTemp = 0; ucTemp <= 50; ucTemp++)
        {
            DELAY_10US_EXINT();

            if(ScalerGetBit_EXINT(PC9_DC_RX_K_OOBS_08, _BIT0) == _BIT0)
            {
                break;
            }
        }

        ucOobsOffsetL0 = (((ScalerGetByte_EXINT(PC9_D9_RX_K_OOBS_05) & 0xC0) >> 1) | ((ScalerGetByte_EXINT(PC9_DD_RX_K_OOBS_09) & 0xF1) >> 3));

        // [0] reg_oobs_offset_en_l0 = 1'b0 -> Disable calibration
        ScalerSetBit_EXINT(PC9_D4_RX_K_OOBS_00, ~_BIT0, 0x00);

        // [1] reg_oobs_offset_ok_l0 = 1'b1 -> Enable Manual Mode Calibration ok
        ScalerSetBit_EXINT(PC9_D7_RX_K_OOBS_03, ~_BIT1, _BIT1);

        // [0] reg_oobs_offset_manual_l0 = 1'b1 -> Calibration Manual Mode
        ScalerSetBit_EXINT(PC9_D7_RX_K_OOBS_03, ~_BIT0, _BIT0);

        if((ucOobsOffsetL0 != 0x7F) || (ucOobsSenVal == (_BIT1 | _BIT0)))
        {
            // Reload L0 Calibration Result
            ScalerSetBit_EXINT(PC9_D9_RX_K_OOBS_05, ~(_BIT1 | _BIT0), (ScalerGetByte_EXINT(PC9_D9_RX_K_OOBS_05) >> 6));
            ScalerSetByte_EXINT(PC9_D8_RX_K_OOBS_04, ScalerGetByte_EXINT(PC9_DD_RX_K_OOBS_09));

            break;
        }
    }

    for(ucOobsSenVal = 0; ucOobsSenVal <= (_BIT1 | _BIT0); ucOobsSenVal++)
    {
        // reg_sen_val_range_l23
        ScalerSetBit_EXINT(PB2_19_LDO_03, ~(_BIT1 | _BIT0), ucOobsSenVal);

        // [1:0] reg_oobs_offset_ini_l1 [9:8] = 2'b10
        // [7:0] reg_oobs_offset_ini_l1 [7:0] = 0x00
        ScalerSetBit_EXINT(PC9_DB_RX_K_OOBS_07, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetByte_EXINT(PC9_DA_RX_K_OOBS_06, 0x00);

        // [5] reg_oobs_offset_ok_l1 = 1'b0 -> Disable Manual Mode Calibration ok
        ScalerSetBit_EXINT(PC9_D7_RX_K_OOBS_03, ~_BIT5, 0x00);

        // [4] reg_oobs_offset_manual_l1 = 1'b0 -> Calibration Auto Mode
        ScalerSetBit_EXINT(PC9_D7_RX_K_OOBS_03, ~_BIT4, 0x00);

        // [4] reg_rstb_oobs_offset = 1'b0 >> 1'b1 -> reset
        ScalerSetBit_EXINT(PC9_D4_RX_K_OOBS_00, ~_BIT4, 0x00);
        ScalerSetBit_EXINT(PC9_D4_RX_K_OOBS_00, ~_BIT4, _BIT4);

        // [1] reg_oobs_offset_en_l1 = 1'b1 -> Set Calibration Mode Enable
        ScalerSetBit_EXINT(PC9_D4_RX_K_OOBS_00, ~_BIT1, _BIT1);

        // Delay Time us [0,500] Waiting for Calibration Done
        for(ucTemp = 0; ucTemp <= 50; ucTemp++)
        {
            DELAY_10US_EXINT();

            if(ScalerGetBit_EXINT(PC9_DC_RX_K_OOBS_08, _BIT3) == _BIT3)
            {
                break;
            }
        }

        ucOobsOffsetL2 = (((ScalerGetByte_EXINT(PC9_DB_RX_K_OOBS_07) & 0xC0) >> 1) | ((ScalerGetByte_EXINT(PC9_DE_RX_K_OOBS_10) & 0xF1) >> 3));

        // [1] reg_oobs_offset_en_l1 = 1'b0 -> Disable calibration
        ScalerSetBit_EXINT(PC9_D4_RX_K_OOBS_00, ~_BIT1, 0x00);

        // [5] reg_oobs_offset_ok_l1 = 1'b1 -> Enable Manual Mode Calibration ok
        ScalerSetBit_EXINT(PC9_D7_RX_K_OOBS_03, ~_BIT5, _BIT5);

        // [4] reg_oobs_offset_manual_l1 = 1'b1 -> Calibration Manual Mode
        ScalerSetBit_EXINT(PC9_D7_RX_K_OOBS_03, ~_BIT4, _BIT4);

        if((ucOobsOffsetL2 != 0x7F) || (ucOobsSenVal == (_BIT1 | _BIT0)))
        {
            // Reload L2 Calibration Result
            ScalerSetBit_EXINT(PC9_DB_RX_K_OOBS_07, ~(_BIT1 | _BIT0), (ScalerGetByte_EXINT(PC9_DB_RX_K_OOBS_07) >> 6));
            ScalerSetByte_EXINT(PC9_DA_RX_K_OOBS_06, ScalerGetByte_EXINT(PC9_DE_RX_K_OOBS_10));

            break;
        }
    }
}
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp1SetPhyUnFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    ////////////////////
    // 2 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit_EXINT(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [3/2] Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3/2] reg_en_vco_lpf = 2'b11 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [7/6] reg_timer_en = 1 for CDR_RDY
    // [3/2] reg_acdr_en = 1
    ScalerSetBit_EXINT(P7A_96_DATA_TIMER_0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));

    // reg_en_fld_clk = 2'b11 --> Enable FLD Clock
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit_EXINT(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_EE_FLD_L3_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit_EXINT(PB1_AF_FLD_L2_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_EF_FLD_L3_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7/6] reg_en_clkout_manual = 1'b0
    // [3/2] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit_EXINT(P7A_97_DATA_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7/6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane_EXINT0(ScalerDpAuxRxGetLinkRate_EXINT0(ScalerDpPhyRxRxDxMapping_EXINT0(_RX1)), enumDpNFCodeRef);


    //////////////
    // FLD Band //
    //////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp1SetPhyFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    ////////////////////
    // 2 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit_EXINT(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [1/0] Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [5/4] reg_en_vco_lpf = 2'b11 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [5/4] reg_timer_en = 1 for CDR_RDY
    // [1/0] reg_acdr_en = 1
    ScalerSetBit_EXINT(P7A_96_DATA_TIMER_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));

    // reg_en_fld_clk = 2'b11 --> Enable FLD Clock
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit_EXINT(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_6E_FLD_L1_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit_EXINT(PB1_2F_FLD_L0_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_6F_FLD_L1_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5/4] reg_en_clkout_manual = 1'b0
    // [1/0] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit_EXINT(P7A_97_DATA_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSettingFlip2Lane_EXINT0(ScalerDpAuxRxGetLinkRate_EXINT0(ScalerDpPhyRxRxDxMapping_EXINT0(_RX1)), enumDpNFCodeRef);


    //////////////
    // FLD Band //
    //////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp1SetPhyUnFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    enumDpNFCodeRef = enumDpNFCodeRef;
    BYTE pucIcp[3];


    ////////////////////
    // 2 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit_EXINT(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [3/2] Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3/2] reg_en_vco_lpf = 2'b11 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [7/6] reg_timer_en = 1 for CDR_RDY
    // [3/2] reg_acdr_en = 1
    ScalerSetBit_EXINT(P7A_96_DATA_TIMER_0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));

    // reg_en_fld_clk = 2'b11 --> Enable FLD Clock
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit_EXINT(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_EE_FLD_L3_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit_EXINT(PB1_AF_FLD_L2_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_EF_FLD_L3_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit_EXINT(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7/6] LANE_EN = 2'b00 --> Disable LANE_EN
    // [3/2] CDR_EN = 2'b00 --> Disable CDR_EN
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE2);
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE3);

    switch(g_ucDpPhyRx1CtsCtrl & 0x30)
    {
        case 0x30:

            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE3);

            break;

        default:
        case 0x20:

            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE2);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7/6] reg_en_clkout_manual = 1'b0
    // [3/2] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit_EXINT(P7A_97_DATA_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7/6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitialUnFlip2Lane_EXINT0();

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane_EXINT0(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort), enumDpNFCodeRef);

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////
    // FLD Band //
    //////////////

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0x00);


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    DELAY_5US_EXINT();

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7/6] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    g_pusDpPhyRx1ClockTarget[0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_1000_CYCLE);

    if(g_pusDpPhyRx1ClockTarget[0] != 0)
    {
        g_pusDpPhyRx1ClockTarget[1] = g_pusDpPhyRx1ClockTarget[0];
        g_pusDpPhyRx1ClockTarget[2] = g_pusDpPhyRx1ClockTarget[0];
        g_pusDpPhyRx1ClockTarget[3] = g_pusDpPhyRx1ClockTarget[0];
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp1SetPhyFlip2Lane_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    enumDpNFCodeRef = enumDpNFCodeRef;
    BYTE pucIcp[3];


    ////////////////////
    // 2 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit_EXINT(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit_EXINT(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [1/0] Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [5/4] reg_en_vco_lpf = 2'b11 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [5/4] reg_timer_en = 1 for CDR_RDY
    // [1/0] reg_acdr_en = 1
    ScalerSetBit_EXINT(P7A_96_DATA_TIMER_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));

    // reg_en_fld_clk = 2'b11 --> Enable FLD Clock
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit_EXINT(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(PB1_6E_FLD_L1_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit_EXINT(PB1_2F_FLD_L0_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(PB1_6F_FLD_L1_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit_EXINT(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5/4] LANE_EN = 2'b00 --> Disable LANE_EN
    // [1/0] CDR_EN = 2'b00 --> Disable CDR_EN
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE0);
    ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _DISABLE, _DP_SCALER_LANE1);

    switch(g_ucDpPhyRx1CtsCtrl & 0x30)
    {
        case 0x10:

            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE1);

            break;

        default:
        case 0x00:

            ScalerGDIPhyRxLanePower_EXINT0(enumInputPort, _ENABLE, _DP_SCALER_LANE0);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5/4] reg_en_clkout_manual = 1'b0
    // [1/0] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit_EXINT(P7A_97_DATA_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitialFlip2Lane_EXINT0();

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSettingFlip2Lane_EXINT0(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort), enumDpNFCodeRef);

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////
    // FLD Band //
    //////////////

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xC7);
    }

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);

    // Delay Time us [0,500] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0x00);


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

    DELAY_5US_EXINT();

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);

    // Delay Time us [0,500] Waiting for FLD
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[0]);

    // [5/4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    g_pusDpPhyRx1ClockTarget[0] = ScalerDpMacDphyRxSignalDetectMeasureCount_EXINT0(enumInputPort, ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_1000_CYCLE);

    if(g_pusDpPhyRx1ClockTarget[0] != 0)
    {
        g_pusDpPhyRx1ClockTarget[1] = g_pusDpPhyRx1ClockTarget[0];
        g_pusDpPhyRx1ClockTarget[2] = g_pusDpPhyRx1ClockTarget[0];
        g_pusDpPhyRx1ClockTarget[3] = g_pusDpPhyRx1ClockTarget[0];
    }
}
#endif

//--------------------------------------------------
// Description  : DP APhy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1APhyFLDSetting4Lane_EXINT0(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef)
{
    // reg_sel_large_kvco = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit_EXINT(PB2_0F_RX_TOP_15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));
    ScalerSetBit_EXINT(PB2_10_RX_TOP_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_large_kvco_lpf_sel = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit_EXINT(PB2_31_RX_CDR_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));
    ScalerSetBit_EXINT(PB2_32_RX_CDR_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_vco_lpf_force_en = 4'b1111 --> Enable Force VCO LPF by Register
    ScalerSetBit_EXINT(PB2_20_RX_CDR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_v2i_lpf_force_en = 4'b1111 --> Enable V2I Dual Loop LPF
    ScalerSetBit_EXINT(PB2_27_RX_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_en_lpf_dual_loop = 4'b1111 --> Enable LPF in Dual Loop
    ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_ldo_cp_vsel = 2'b10 --> 1.05V
    ScalerSetByte_EXINT(PB2_35_RX_CDR_21, 0xAA);

    // reg_en_cp_kp_path = 1 --> Enable Direct Modulation Mode
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_cdr_r = 2K
    ScalerSetBit_EXINT(PB1_2B_FLD_L0_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB1_6B_FLD_L1_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB1_AB_FLD_L2_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(PB1_EB_FLD_L3_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // reg_slope_icp_offset = 2 -> 1 -> 0 --> 0 00100001 00000100 00100000 = 0x0210420
    ScalerSetBit_EXINT(PB1_29_FLD_L0_39, ~_BIT1, 0x00);
    ScalerSetByte_EXINT(PB1_27_FLD_L0_37, 0x21);
    ScalerSetByte_EXINT(PB1_26_FLD_L0_36, 0x04);
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, 0x20);

    ScalerSetBit_EXINT(PB1_69_FLD_L1_39, ~_BIT1, 0x00);
    ScalerSetByte_EXINT(PB1_67_FLD_L1_37, 0x21);
    ScalerSetByte_EXINT(PB1_66_FLD_L1_36, 0x04);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, 0x20);

    ScalerSetBit_EXINT(PB1_A9_FLD_L2_39, ~_BIT1, 0x00);
    ScalerSetByte_EXINT(PB1_A7_FLD_L2_37, 0x21);
    ScalerSetByte_EXINT(PB1_A6_FLD_L2_36, 0x04);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, 0x20);

    ScalerSetBit_EXINT(PB1_E9_FLD_L3_39, ~_BIT1, 0x00);
    ScalerSetByte_EXINT(PB1_E7_FLD_L3_37, 0x21);
    ScalerSetByte_EXINT(PB1_E6_FLD_L3_36, 0x04);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, 0x20);

    if(enumDpNFCodeRef == _DP_NF_REF_D10_2)
    {
        // reg_ref_clk_sel = 1 --> Ref. D10.2/20 Clock
        ScalerSetBit_EXINT(PB1_2A_FLD_L0_40, ~_BIT5, _BIT5);
        ScalerSetBit_EXINT(PB1_6A_FLD_L1_40, ~_BIT5, _BIT5);
        ScalerSetBit_EXINT(PB1_AA_FLD_L2_40, ~_BIT5, _BIT5);
        ScalerSetBit_EXINT(PB1_EA_FLD_L3_40, ~_BIT5, _BIT5);

        // divide num = 100
        ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x64);
        ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x64);
        ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x64);
        ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x64);

        // ref_cnt = divid_num * 2 * target_freq/ref_clock
        // 400   =     100     * 2 * (data_rate/20) / (data_rate/2/20)
        ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x90);
        ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x90);
        ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x90);
        ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x90);
        ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x90);
        ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x90);
        ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x90);
        ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x90);
        ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // reg_ref_clk_sel = 0 --> Ref. XTAL Clock 27MHz
        ScalerSetBit_EXINT(PB1_2A_FLD_L0_40, ~_BIT5, 0x00);
        ScalerSetBit_EXINT(PB1_6A_FLD_L1_40, ~_BIT5, 0x00);
        ScalerSetBit_EXINT(PB1_AA_FLD_L2_40, ~_BIT5, 0x00);
        ScalerSetBit_EXINT(PB1_EA_FLD_L3_40, ~_BIT5, 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR10)
    {
        // Disable VCO Low Power Mode
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
        ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // V2I Isel = 3'010 --> X3
        ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    }
    else
    {
        // Enable VCO Low Power Mode
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
        ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // V2I Isel = 3'000 --> X1
        ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR13_5)
    {
        // reg_sel_large_iptat = 3'b001 --> 12.5%
        ScalerSetBit_EXINT(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // reg_lehv_isel = 0
        ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_large_iptat = 3'b000 --> 0%
        ScalerSetBit_EXINT(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // reg_lehv_isel = 1
        ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

    switch(enumDpLinkRate)
    {
        case _DP_LINK_UHBR13_5: // UHBR135

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_sel_div = 3'b000
            ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x31);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE1);

            // FLD Initial Band = 0x100
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, _BIT0);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0x00);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0x00);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0x00);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 6750 =  14.318  * 2 * (232 + 4) --> N = 0x0E8
            ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xE8);
            ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xE8);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // divide num = 20
                ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x14);
                ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x14);
                ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x14);
                ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x14);

                // Divide Num x 2 x (6750/16) / 27MHz = FLD Counter
                // 20         x 2 x  421.875  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x71);
                ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x71);
                ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x71);
                ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x71);
                ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x71);
                ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x71);
                ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x71);
                ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x71);
                ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), 0x00);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR13P5() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR13P5());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR13P5());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());

            g_pusDpPhyRx1ClockTarget[0] = 0x61A8; // ideal 13.5G

            break;

        case _DP_LINK_UHBR10:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x33);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xA2);

            // reg_sel_div = 3'b000
            ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 5000 = 14.318  * 2 * (170 + 4) --> N = 0x0AA
            ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xAA);
            ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xAA);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // FLD Initial Band = 0xA0
                ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
                ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
                ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
                ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
                ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0xA0);
                ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0xA0);
                ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0xA0);
                ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0xA0);

                // divide num = 27
                ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x1B);
                ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x1B);
                ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x1B);
                ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x1B);

                // Divide Num x 2 x (5000/16) / 27MHz = FLD Counter
                // 27         x 2 x   312. 5  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x71);
                ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x71);
                ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x71);
                ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x71);
                ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x71);
                ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x71);
                ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x71);
                ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x71);
                ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR10() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR10() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR10() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR10() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR10());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR10());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());

            g_pusDpPhyRx1ClockTarget[0] = 0x4857; // ideal 10G

            break;

        case _DP_LINK_HBR3_9G:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xE0
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0xE0);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0xE0);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0xE0);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0xE0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4500 =  14.318  * 2 * (153 + 4) --> N = 0x099
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x99);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x99);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x18);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (4500/16) / 27MHz = FLD Counter
                    // 24         x 2 x   281.25  / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 9000 =  14.318  * 2 * (310 + 4) --> N = 0x136
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x36);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x36);

                    // divide num = 18
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x12);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x12);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x12);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x12);

                    // Divide Num x 2 x (9000/16) / 27MHz = FLD Counter
                    // 18         x 2 x    562.5  / 27MHz = 750 = 0x2EE  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xEE);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xEE);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xEE);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xEE);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xEE);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xEE);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xEE);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xEE);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x411B; // ideal 9G

            break;

        case _DP_LINK_HBR3:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xC0
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0xC0);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0xC0);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0xC0);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0xC0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4050 =  14.318  * 2 * (137 + 4) --> N = 0x089
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x89);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x89);

                    // divide num = 36
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x24);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x24);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x24);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x24);

                    // Divide Num x 2 x (4050/16) / 27MHz = FLD Counter
                    // 36         x 2 x  253.125  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 8100 =  14.318  * 2 * (279 + 4) --> N = 0x117
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x17);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x17);

                    // divide num = 18
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x12);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x12);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x12);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x12);

                    // Divide Num x 2 x (8100/16) / 27MHz = FLD Counter
                    // 18         x 2 x   506.25  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x3A98; // ideal 8.1G

            break;

        case _DP_LINK_HBR2:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x27);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xC4);

            // FLD Initial Band = 0x068
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0x68);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0x68);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0x68);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x5A);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x5A);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x18);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xB8);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xB8);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x14);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR2() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR2() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR2() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR2() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR2());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR2());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());

            g_pusDpPhyRx1ClockTarget[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x068
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0x68);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0x68);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0x68);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x5A);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x5A);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x18);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xB8);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xB8);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x14);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());

            g_pusDpPhyRx1ClockTarget[0] = 0x1388; // ideal 2.7G

            break;

        case _DP_LINK_RBR:
        default:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x0A0
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0xA0);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0xA0);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0xA0);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0xA0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 3240 =  14.318  * 2 * (109 + 4) --> N = 0x06D
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x6D);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x6D);

                    // divide num = 32
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x20);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x20);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x20);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x20);

                    // Divide Num x 2 x (3240/15) / 27MHz = FLD Counter
                    // 32         x 2     202.5   / 27MHz = 480 = 0x1E0  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xE0);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xE0);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xE0);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xE0);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xE0);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xE0);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xE0);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xE0);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b011
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 6480 =  14.318  * 2 * (222 + 4) --> N = 0x0DE
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xDE);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xDE);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x14);
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (6480/16) / 27MHz = FLD Counter
                    // 20         x 2 x     405   / 27MHz = 600 = 0x258  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x58);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x58);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x58);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x58);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x58);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x58);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x58);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x58);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b10 --> -25%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT3);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_RBR() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_RBR() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_RBR() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_RBR() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_RBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_RBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());

            g_pusDpPhyRx1ClockTarget[0] = 0xBB8; // ideal 1.62G

            break;
    }

    g_pusDpPhyRx1ClockTarget[1] = g_pusDpPhyRx1ClockTarget[0];
    g_pusDpPhyRx1ClockTarget[2] = g_pusDpPhyRx1ClockTarget[0];
    g_pusDpPhyRx1ClockTarget[3] = g_pusDpPhyRx1ClockTarget[0];
}

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP APhy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane_EXINT0(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef)
{
    // reg_sel_large_kvco = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit_EXINT(PB2_10_RX_TOP_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_large_kvco_lpf_sel = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit_EXINT(PB2_32_RX_CDR_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_vco_lpf_force_en = 2'b11 --> Enable Force VCO LPF by Register
    ScalerSetBit_EXINT(PB2_20_RX_CDR_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // reg_v2i_lpf_force_en = 2'b11 --> Enable V2I Dual Loop LPF
    ScalerSetBit_EXINT(PB2_27_RX_CDR_07, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // reg_en_lpf_dual_loop = 2'b11 --> Enable LPF in Dual Loop
    ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // reg_ldo_cp_vsel = 2'b10 --> 1.05V
    ScalerSetBit_EXINT(PB2_35_RX_CDR_21, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // reg_en_cp_kp_path = 1 --> Enable Direct Modulation Mode
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // reg_cdr_r = 2K
    ScalerSetBit_EXINT(PB1_AB_FLD_L2_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit_EXINT(PB1_EB_FLD_L3_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // reg_slope_icp_offset = 2 -> 1 -> 0 --> 0 00100001 00000100 00100000 = 0x0210420
    ScalerSetBit_EXINT(PB1_A9_FLD_L2_39, ~_BIT1, 0x00);
    ScalerSetByte_EXINT(PB1_A7_FLD_L2_37, 0x21);
    ScalerSetByte_EXINT(PB1_A6_FLD_L2_36, 0x04);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, 0x20);

    ScalerSetBit_EXINT(PB1_E9_FLD_L3_39, ~_BIT1, 0x00);
    ScalerSetByte_EXINT(PB1_E7_FLD_L3_37, 0x21);
    ScalerSetByte_EXINT(PB1_E6_FLD_L3_36, 0x04);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, 0x20);

    if(enumDpNFCodeRef == _DP_NF_REF_D10_2)
    {
        // reg_ref_clk_sel = 1 --> Ref. D10.2/20 Clock
        ScalerSetBit_EXINT(PB1_AA_FLD_L2_40, ~_BIT5, _BIT5);
        ScalerSetBit_EXINT(PB1_EA_FLD_L3_40, ~_BIT5, _BIT5);

        // divide num = 100
        ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x64);
        ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x64);

        // ref_cnt = divid_num * 2 * target_freq/ref_clock
        // 400   =     100     * 2 * (data_rate/20) / (data_rate/2/20)
        ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x90);
        ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x90);
        ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x90);
        ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x90);
        ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // reg_ref_clk_sel = 0 --> Ref. XTAL Clock 27MHz
        ScalerSetBit_EXINT(PB1_AA_FLD_L2_40, ~_BIT5, 0x00);
        ScalerSetBit_EXINT(PB1_EA_FLD_L3_40, ~_BIT5, 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR10)
    {
        // Disable VCO Low Power Mode
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT7 | _BIT6), 0x00);

        // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
        ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // V2I Isel = 3'010 --> X3
        ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    }
    else
    {
        // Enable VCO Low Power Mode
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
        ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6), 0x00);

        // V2I Isel = 3'000 --> X1
        ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR13_5)
    {
        // reg_sel_large_iptat = 3'b001 --> 12.5%
        ScalerSetBit_EXINT(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // reg_lehv_isel = 0
        ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2), 0x00);
    }
    else
    {
        // reg_sel_large_iptat = 3'b000 --> 0%
        ScalerSetBit_EXINT(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // reg_lehv_isel = 1
        ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }

    switch(enumDpLinkRate)
    {
        case _DP_LINK_UHBR13_5: // UHBR135

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_sel_div = 3'b000
            ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x31);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE1);

            // FLD Initial Band = 0x100
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, _BIT0);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0x00);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 6750 =  14.318  * 2 * (232 + 4) --> N = 0x0E8
            ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xE8);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // divide num = 20
                ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x14);
                ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x14);

                // Divide Num x 2 x (6750/16) / 27MHz = FLD Counter
                // 20         x 2 x  421.875  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x71);
                ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x71);
                ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x71);
                ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x71);
                ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), 0x00);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR13P5() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR13P5());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR13P5());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());

            g_pusDpPhyRx1ClockTarget[0] = 0x61A8; // ideal 13.5G

            break;

        case _DP_LINK_UHBR10:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x33);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xA2);

            // reg_sel_div = 3'b000
            ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 5000 = 14.318  * 2 * (170 + 4) --> N = 0x0AA
            ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xAA);
            ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xAA);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // FLD Initial Band = 0xA0
                ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
                ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
                ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0xA0);
                ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0xA0);

                // divide num = 27
                ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x1B);
                ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x1B);

                // Divide Num x 2 x (5000/16) / 27MHz = FLD Counter
                // 27         x 2 x   312. 5  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x71);
                ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x71);
                ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x71);
                ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x71);
                ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR10() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR10() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR10() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR10() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR10());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR10());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());

            g_pusDpPhyRx1ClockTarget[0] = 0x4857; // ideal 10G

            break;

        case _DP_LINK_HBR3_9G:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xE0
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0xE0);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0xE0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4500 =  14.318  * 2 * (153 + 4) --> N = 0x099
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x99);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (4500/16) / 27MHz = FLD Counter
                    // 24         x 2 x   281.25  / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 9000 =  14.318  * 2 * (310 + 4) --> N = 0x136
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, _BIT0);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x36);

                    // divide num = 18
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x12);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x12);

                    // Divide Num x 2 x (9000/16) / 27MHz = FLD Counter
                    // 18         x 2 x    562.5  / 27MHz = 750 = 0x2EE  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xEE);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xEE);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xEE);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xEE);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x411B; // ideal 9G

            break;

        case _DP_LINK_HBR3:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xC0
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0xC0);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0xC0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4050 =  14.318  * 2 * (137 + 4) --> N = 0x089
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x89);

                    // divide num = 36
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x24);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x24);

                    // Divide Num x 2 x (4050/16) / 27MHz = FLD Counter
                    // 36         x 2 x  253.125  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 8100 =  14.318  * 2 * (279 + 4) --> N = 0x117
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, _BIT0);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x17);

                    // divide num = 18
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x12);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x12);

                    // Divide Num x 2 x (8100/16) / 27MHz = FLD Counter
                    // 18         x 2 x   506.25  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x3A98; // ideal 8.1G

            break;

        case _DP_LINK_HBR2:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x27);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xC4);

            // FLD Initial Band = 0x068
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0x68);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x5A);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xB8);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR2() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR2() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR2() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR2() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR2());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR2());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());

            g_pusDpPhyRx1ClockTarget[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x068
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0x68);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x5A);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xB8);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());

            g_pusDpPhyRx1ClockTarget[0] = 0x1388; // ideal 2.7G

            break;

        case _DP_LINK_RBR:
        default:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x0A0
            ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_94_FLD_L2_20, 0xA0);
            ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, 0xA0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 3240 =  14.318  * 2 * (109 + 4) --> N = 0x06D
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0x6D);

                    // divide num = 32
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x20);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x20);

                    // Divide Num x 2 x (3240/15) / 27MHz = FLD Counter
                    // 32         x 2     202.5   / 27MHz = 480 = 0x1E0  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0xE0);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0xE0);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0xE0);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0xE0);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b011
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 6480 =  14.318  * 2 * (222 + 4) --> N = 0x0DE
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xDE);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte_EXINT(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (6480/16) / 27MHz = FLD Counter
                    // 20         x 2 x     405   / 27MHz = 600 = 0x258  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_97_FLD_L2_23, 0x58);
                    ScalerSetBit_EXINT(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_99_FLD_L2_25, 0x58);
                    ScalerSetBit_EXINT(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_D7_FLD_L3_23, 0x58);
                    ScalerSetBit_EXINT(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_D9_FLD_L3_25, 0x58);
                    ScalerSetBit_EXINT(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b10 --> -25%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT3);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_RBR() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_RBR() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_RBR() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_RBR() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_RBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_RBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit_EXINT(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());

            g_pusDpPhyRx1ClockTarget[0] = 0xBB8; // ideal 1.62G

            break;
    }

    g_pusDpPhyRx1ClockTarget[1] = g_pusDpPhyRx1ClockTarget[0];
    g_pusDpPhyRx1ClockTarget[2] = g_pusDpPhyRx1ClockTarget[0];
    g_pusDpPhyRx1ClockTarget[3] = g_pusDpPhyRx1ClockTarget[0];
}

//--------------------------------------------------
// Description  : DP APhy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1APhyFLDSettingFlip2Lane_EXINT0(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef)
{
    // reg_sel_large_kvco = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit_EXINT(PB2_0F_RX_TOP_15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_large_kvco_lpf_sel = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit_EXINT(PB2_31_RX_CDR_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_vco_lpf_force_en = 2'b11 --> Enable Force VCO LPF by Register
    ScalerSetBit_EXINT(PB2_20_RX_CDR_00, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // reg_v2i_lpf_force_en = 2'b11 --> Enable V2I Dual Loop LPF
    ScalerSetBit_EXINT(PB2_27_RX_CDR_07, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // reg_en_lpf_dual_loop = 2'b11 --> Enable LPF in Dual Loop
    ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // reg_ldo_cp_vsel = 2'b10 --> 1.05V
    ScalerSetBit_EXINT(PB2_35_RX_CDR_21, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // reg_en_cp_kp_path = 1 --> Enable Direct Modulation Mode
    ScalerSetBit_EXINT(PB2_2F_RX_CDR_15, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // reg_cdr_r = 2K
    ScalerSetBit_EXINT(PB1_2B_FLD_L0_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit_EXINT(PB1_6B_FLD_L1_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // reg_slope_icp_offset = 2 -> 1 -> 0 --> 0 00100001 00000100 00100000 = 0x0210420
    ScalerSetBit_EXINT(PB1_29_FLD_L0_39, ~_BIT1, 0x00);
    ScalerSetByte_EXINT(PB1_27_FLD_L0_37, 0x21);
    ScalerSetByte_EXINT(PB1_26_FLD_L0_36, 0x04);
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, 0x20);

    ScalerSetBit_EXINT(PB1_69_FLD_L1_39, ~_BIT1, 0x00);
    ScalerSetByte_EXINT(PB1_67_FLD_L1_37, 0x21);
    ScalerSetByte_EXINT(PB1_66_FLD_L1_36, 0x04);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, 0x20);

    if(enumDpNFCodeRef == _DP_NF_REF_D10_2)
    {
        // reg_ref_clk_sel = 1 --> Ref. D10.2/20 Clock
        ScalerSetBit_EXINT(PB1_2A_FLD_L0_40, ~_BIT5, _BIT5);
        ScalerSetBit_EXINT(PB1_6A_FLD_L1_40, ~_BIT5, _BIT5);

        // divide num = 100
        ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x64);
        ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x64);

        // ref_cnt = divid_num * 2 * target_freq/ref_clock
        // 400   =     100     * 2 * (data_rate/20) / (data_rate/2/20)
        ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x90);
        ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x90);
        ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x90);
        ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x90);
        ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // reg_ref_clk_sel = 0 --> Ref. XTAL Clock 27MHz
        ScalerSetBit_EXINT(PB1_2A_FLD_L0_40, ~_BIT5, 0x00);
        ScalerSetBit_EXINT(PB1_6A_FLD_L1_40, ~_BIT5, 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR10)
    {
        // Disable VCO Low Power Mode
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT5 | _BIT4), 0x00);

        // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
        ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // V2I Isel = 3'010 --> X3
        ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    }
    else
    {
        // Enable VCO Low Power Mode
        ScalerSetBit_EXINT(PB2_22_RX_CDR_02, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        ScalerSetBit_EXINT(PB2_2B_RX_CDR_11, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
        ScalerSetBit_EXINT(PB2_37_RX_EQ_00, ~(_BIT5 | _BIT4), 0x00);

        // V2I Isel = 3'000 --> X1
        ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR13_5)
    {
        // reg_sel_large_iptat = 3'b001 --> 12.5%
        ScalerSetBit_EXINT(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // reg_lehv_isel = 0
        ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_large_iptat = 3'b000 --> 0%
        ScalerSetBit_EXINT(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // reg_lehv_isel = 1
        ScalerSetBit_EXINT(PB2_0D_RX_TOP_13, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }

    switch(enumDpLinkRate)
    {
        case _DP_LINK_UHBR13_5: // UHBR135

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_sel_div = 3'b000
            ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x31);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE1);

            // FLD Initial Band = 0x100
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, _BIT0);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0x00);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 6750 =  14.318  * 2 * (232 + 4) --> N = 0x0E8
            ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
            ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xE8);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // divide num = 20
                ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x14);
                ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x14);

                // Divide Num x 2 x (6750/16) / 27MHz = FLD Counter
                // 20         x 2 x  421.875  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x71);
                ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x71);
                ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x71);
                ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x71);
                ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), 0x00);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR13P5() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR13P5());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR13P5());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());

            g_pusDpPhyRx1ClockTarget[0] = 0x61A8; // ideal 13.5G

            break;

        case _DP_LINK_UHBR10:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x33);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xA2);

            // reg_sel_div = 3'b000
            ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 5000 = 14.318  * 2 * (170 + 4) --> N = 0x0AA
            ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xAA);
            ScalerSetByte_EXINT(PB2_2E_RX_CDR_14, 0xAA);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // FLD Initial Band = 0xA0
                ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
                ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
                ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0xA0);
                ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0xA0);

                // divide num = 27
                ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x1B);
                ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x1B);

                // Divide Num x 2 x (5000/16) / 27MHz = FLD Counter
                // 27         x 2 x   312. 5  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x71);
                ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x71);
                ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x71);
                ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x71);
                ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR10() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR10() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR10() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR10() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR10());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR10());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());

            g_pusDpPhyRx1ClockTarget[0] = 0x4857; // ideal 10G

            break;

        case _DP_LINK_HBR3_9G:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xE0
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0xE0);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0xE0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4500 =  14.318  * 2 * (153 + 4) --> N = 0x099
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x99);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x18);

                    // Divide Num x 2 x (4500/16) / 27MHz = FLD Counter
                    // 24         x 2 x   281.25  / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 9000 =  14.318  * 2 * (310 + 4) --> N = 0x136
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, _BIT1);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x36);

                    // divide num = 18
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x12);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x12);

                    // Divide Num x 2 x (9000/16) / 27MHz = FLD Counter
                    // 18         x 2 x    562.5  / 27MHz = 750 = 0x2EE  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xEE);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xEE);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xEE);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xEE);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x411B; // ideal 9G

            break;

        case _DP_LINK_HBR3:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xC0
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0xC0);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0xC0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4050 =  14.318  * 2 * (137 + 4) --> N = 0x089
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x89);

                    // divide num = 36
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x24);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x24);

                    // Divide Num x 2 x (4050/16) / 27MHz = FLD Counter
                    // 36         x 2 x  253.125  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 8100 =  14.318  * 2 * (279 + 4) --> N = 0x117
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, _BIT1);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x17);

                    // divide num = 18
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x12);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x12);

                    // Divide Num x 2 x (8100/16) / 27MHz = FLD Counter
                    // 18         x 2 x   506.25  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xA3);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xA3);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x3A98; // ideal 8.1G

            break;

        case _DP_LINK_HBR2:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x27);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0xC4);

            // FLD Initial Band = 0x068
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0x68);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x5A);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xB8);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR2() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR2() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR2() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR2() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR2());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR2());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());

            g_pusDpPhyRx1ClockTarget[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x068
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0x68);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x5A);

                    // divide num = 24
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x2C);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x2C);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xB8);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());

            g_pusDpPhyRx1ClockTarget[0] = 0x1388; // ideal 2.7G

            break;

        case _DP_LINK_RBR:
        default:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit_EXINT(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte_EXINT(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte_EXINT(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x0A0
            ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte_EXINT(PB1_14_FLD_L0_20, 0xA0);
            ScalerSetByte_EXINT(PB1_54_FLD_L1_20, 0xA0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit_EXINT(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 3240 =  14.318  * 2 * (109 + 4) --> N = 0x06D
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0x6D);

                    // divide num = 32
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x20);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x20);

                    // Divide Num x 2 x (3240/15) / 27MHz = FLD Counter
                    // 32         x 2     202.5   / 27MHz = 480 = 0x1E0  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0xE0);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0xE0);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0xE0);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0xE0);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b011
                    ScalerSetBit_EXINT(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 6480 =  14.318  * 2 * (222 + 4) --> N = 0x0DE
                    ScalerSetBit_EXINT(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte_EXINT(PB2_2D_RX_CDR_13, 0xDE);

                    // divide num = 20
                    ScalerSetByte_EXINT(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte_EXINT(PB1_5B_FLD_L1_27, 0x14);

                    // Divide Num x 2 x (6480/16) / 27MHz = FLD Counter
                    // 20         x 2 x     405   / 27MHz = 600 = 0x258  //final ck_sys = 625M
                    ScalerSetByte_EXINT(PB1_17_FLD_L0_23, 0x58);
                    ScalerSetBit_EXINT(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_19_FLD_L0_25, 0x58);
                    ScalerSetBit_EXINT(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte_EXINT(PB1_57_FLD_L1_23, 0x58);
                    ScalerSetBit_EXINT(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte_EXINT(PB1_59_FLD_L1_25, 0x58);
                    ScalerSetBit_EXINT(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b10 --> -25%
            ScalerSetBit_EXINT(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT3);

            // reg_cdr_cp
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_RBR() << 4) & 0xF0);

            ScalerSetBit_EXINT(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_RBR() >> 1) & 0x0F);
            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_RBR() << 2) & 0x7C);

            ScalerSetBit_EXINT(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_RBR() << 5) & 0xE0);

            ScalerSetBit_EXINT(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_RBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit_EXINT(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_RBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit_EXINT(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit_EXINT(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit_EXINT(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit_EXINT(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());

            g_pusDpPhyRx1ClockTarget[0] = 0xBB8; // ideal 1.62G

            break;
    }

    g_pusDpPhyRx1ClockTarget[1] = g_pusDpPhyRx1ClockTarget[0];
    g_pusDpPhyRx1ClockTarget[2] = g_pusDpPhyRx1ClockTarget[0];
    g_pusDpPhyRx1ClockTarget[3] = g_pusDpPhyRx1ClockTarget[0];
}
#endif

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp2SetPhy4Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];
    WORD usTargetClock = 0;

#if(_DP_RX_FEC_SUPPORT == _ON)
    BYTE pucTap0[4];
#endif

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_clkout_manual = 1'b0
    // [3:0] reg_bypass_clk_rdy = 1'b0
    ScalerSetByte_EXINT(P7A_97_DATA_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P7A_99_DATA_TIMER_3, 0x0F);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitial_EXINT0();

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[2]);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Start to Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Stop To Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, 0x00);

    // Read Back LE Max
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Select to Lane0
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    g_pucDpPhyRx1LE[0] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane1
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    g_pucDpPhyRx1LE[1] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane2
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    g_pucDpPhyRx1LE[2] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane3
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    g_pucDpPhyRx1LE[3] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0x00);

#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
    {
        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
        {
            // Read Back Tap0
            ScalerSetByte_EXINT(PB2_F0_COEF_1, 0x01);

            // Select to Lane0
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            pucTap0[0] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane1
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            pucTap0[1] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane2
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            pucTap0[2] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane3
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            pucTap0[3] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if(pucTap0[0] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, (pucTap0[0] + 6));
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[1] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, (pucTap0[1] + 6));
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[2] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, (pucTap0[2] + 6));
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[3] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, (pucTap0[3] + 6));
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
        }


        /////////////////////
        // Second K Offset //
        /////////////////////

        // Read Back K offset Lane0
        if((ScalerGetByte_EXINT(P7A_AA_FORE_OFF_TST_L0) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AA_FORE_OFF_TST_L0) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane1
        if((ScalerGetByte_EXINT(P7A_AB_FORE_OFF_TST_L1) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AB_FORE_OFF_TST_L1) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane2
        if((ScalerGetByte_EXINT(P7A_AC_FORE_OFF_TST_L2) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AC_FORE_OFF_TST_L2) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane3
        if((ScalerGetByte_EXINT(P7A_AD_FORE_OFF_TST_L3) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AD_FORE_OFF_TST_L3) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Reload Servo
        ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x00);
    }
#endif

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    usTargetClock = g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0];
    g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] = (((usTargetClock >> 2) * 5) >> 1);

    usTargetClock = g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1];
    g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1] = (((usTargetClock >> 2) * 5) >> 1);

    usTargetClock = g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE2];
    g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE2] = (((usTargetClock >> 2) * 5) >> 1);

    usTargetClock = g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE3];
    g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE3] = (((usTargetClock >> 2) * 5) >> 1);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp3SetPhy4Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P7A_99_DATA_TIMER_3, 0x0F);

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[2]);


    ///////////////
    // VCO Reset //
    ///////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}

//--------------------------------------------------
// Description  : DP Phy CTS Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp2SetPhy4Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];

#if(_DP_RX_FEC_SUPPORT == _ON)
    BYTE pucTap0[4];
#endif

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_clkout_manual = 1'b0
    // [3:0] reg_bypass_clk_rdy = 1'b0
    ScalerSetByte_EXINT(P7A_97_DATA_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P7A_99_DATA_TIMER_3, 0x0F);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitial_EXINT0();

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35);

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[2]);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Start to Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Stop To Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, 0x00);

    // Read Back LE Max
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Select to Lane0
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    g_pucDpPhyRx1LE[0] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane1
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    g_pucDpPhyRx1LE[1] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane2
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    g_pucDpPhyRx1LE[2] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane3
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    g_pucDpPhyRx1LE[3] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0x00);

#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
    {
        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
        {
            // Read Back Tap0
            ScalerSetByte_EXINT(PB2_F0_COEF_1, 0x01);

            // Select to Lane0
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            pucTap0[0] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane1
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            pucTap0[1] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane2
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            pucTap0[2] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane3
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            pucTap0[3] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if(pucTap0[0] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, (pucTap0[0] + 6));
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[1] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, (pucTap0[1] + 6));
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[2] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, (pucTap0[2] + 6));
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[3] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, (pucTap0[3] + 6));
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
        }


        /////////////////////
        // Second K Offset //
        /////////////////////

        // Read Back K offset Lane0
        if((ScalerGetByte_EXINT(P7A_AA_FORE_OFF_TST_L0) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AA_FORE_OFF_TST_L0) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane1
        if((ScalerGetByte_EXINT(P7A_AB_FORE_OFF_TST_L1) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AB_FORE_OFF_TST_L1) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane2
        if((ScalerGetByte_EXINT(P7A_AC_FORE_OFF_TST_L2) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AC_FORE_OFF_TST_L2) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane3
        if((ScalerGetByte_EXINT(P7A_AD_FORE_OFF_TST_L3) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AD_FORE_OFF_TST_L3) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Reload Servo
        ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x00);
    }
#endif

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp2SetPhyUnFlip2Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];
    WORD usTargetClock = 0;

#if(_DP_RX_FEC_SUPPORT == _ON)
    BYTE pucTap0[2];
#endif

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7/6] reg_en_clkout_manual = 1'b0
    // [3/2] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit_EXINT(P7A_97_DATA_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7/6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitialUnFlip2Lane_EXINT0();

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[2]);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Start to Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Stop To Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, 0x00);

    // Read Back LE Max
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Select to Lane2
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    g_pucDpPhyRx1LE[2] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane3
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    g_pucDpPhyRx1LE[3] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0x00);

#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
    {
        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
        {
            // Read Back Tap0
            ScalerSetByte_EXINT(PB2_F0_COEF_1, 0x01);

            // Select to Lane2
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            pucTap0[0] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane3
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            pucTap0[1] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if(pucTap0[0] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, (pucTap0[0] + 6));
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[1] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, (pucTap0[1] + 6));
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
        }


        /////////////////////
        // Second K Offset //
        /////////////////////

        // Read Back K offset Lane2
        if((ScalerGetByte_EXINT(P7A_AC_FORE_OFF_TST_L2) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AC_FORE_OFF_TST_L2) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane3
        if((ScalerGetByte_EXINT(P7A_AD_FORE_OFF_TST_L3) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AD_FORE_OFF_TST_L3) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Reload Servo
        ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x00);
    }
#endif

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    usTargetClock = g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0];
    g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE0] = (((usTargetClock >> 2) * 5) >> 1);

    usTargetClock = g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1];
    g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE1] = (((usTargetClock >> 2) * 5) >> 1);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp2SetPhyFlip2Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];
    WORD usTargetClock = 0;

#if(_DP_RX_FEC_SUPPORT == _ON)
    BYTE pucTap0[2];
#endif

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5/4] reg_en_clkout_manual = 1'b0
    // [1/0] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit_EXINT(P7A_97_DATA_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitialFlip2Lane_EXINT0();

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit_EXINT(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[2]);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xC7);
    }

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Start to Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Stop To Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, 0x00);

    // Read Back LE Max
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Select to Lane0
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    g_pucDpPhyRx1LE[0] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane1
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    g_pucDpPhyRx1LE[1] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0x00);

#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
    {
        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
        {
            // Read Back Tap0
            ScalerSetByte_EXINT(PB2_F0_COEF_1, 0x01);

            // Select to Lane0
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            pucTap0[0] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane1
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            pucTap0[1] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if(pucTap0[0] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, (pucTap0[0] + 6));
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[1] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, (pucTap0[1] + 6));
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
            }
        }


        /////////////////////
        // Second K Offset //
        /////////////////////

        // Read Back K offset Lane0
        if((ScalerGetByte_EXINT(P7A_AA_FORE_OFF_TST_L0) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AA_FORE_OFF_TST_L0) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane1
        if((ScalerGetByte_EXINT(P7A_AB_FORE_OFF_TST_L1) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AB_FORE_OFF_TST_L1) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Reload Servo
        ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x00);
    }
#endif

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    usTargetClock = g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE2];
    g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE2] = (((usTargetClock >> 2) * 5) >> 1);

    usTargetClock = g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE3];
    g_pusDpPhyRx1ClockTarget[_DP_PHY_RX1_D1_LANE3] = (((usTargetClock >> 2) * 5) >> 1);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP3
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp3SetPhyUnFlip2Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7/6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[2]);


    ///////////////
    // VCO Reset //
    ///////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP3
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Tp3SetPhyFlip2Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[2]);


    ///////////////
    // VCO Reset //
    ///////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_5US_EXINT();

    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp2SetPhyUnFlip2Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];

#if(_DP_RX_FEC_SUPPORT == _ON)
    BYTE pucTap0[2];
#endif

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7/6] reg_en_clkout_manual = 1'b0
    // [3/2] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit_EXINT(P7A_97_DATA_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7/6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitialUnFlip2Lane_EXINT0();

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_A5_FLD_L2_35);

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[2]);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Start to Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Stop To Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, 0x00);

    // Read Back LE Max
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Select to Lane2
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    g_pucDpPhyRx1LE[2] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane3
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    g_pucDpPhyRx1LE[3] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_D1_L3_DFE_EN_2, 0x00);

#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
    {
        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
        {
            // Read Back Tap0
            ScalerSetByte_EXINT(PB2_F0_COEF_1, 0x01);

            // Select to Lane2
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            pucTap0[0] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane3
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            pucTap0[1] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if(pucTap0[0] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_C4_L2_INIT_2, (pucTap0[0] + 6));
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[1] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_D4_L3_INIT_2, (pucTap0[1] + 6));
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
            }
        }


        /////////////////////
        // Second K Offset //
        /////////////////////

        // Read Back K offset Lane2
        if((ScalerGetByte_EXINT(P7A_AC_FORE_OFF_TST_L2) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AC_FORE_OFF_TST_L2) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane3
        if((ScalerGetByte_EXINT(P7A_AD_FORE_OFF_TST_L3) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AD_FORE_OFF_TST_L3) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Reload Servo
        ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_CA_L2_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_DA_L3_INIT_8, 0x00);
    }
#endif

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit_EXINT(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit_EXINT(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit_EXINT(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte_EXINT(PB1_94_FLD_L2_20, ScalerGetByte_EXINT(PB1_B2_FLD_L2_48));
    ScalerSetByte_EXINT(PB1_D4_FLD_L3_20, ScalerGetByte_EXINT(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp2SetPhyFlip2Lane_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);
    BYTE pucIcp[3];

#if(_DP_RX_FEC_SUPPORT == _ON)
    BYTE pucTap0[2];
#endif

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5/4] reg_en_clkout_manual = 1'b0
    // [1/0] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit_EXINT(P7A_97_DATA_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitialFlip2Lane_EXINT0();

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte_EXINT(PB1_25_FLD_L0_35);

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, 0x00);

    // [7] reg_fld_rst_n = 0 --> Reset FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[2]);

    if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0xC7);
    }

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit_EXINT(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Start to Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, _BIT0);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Stop To Record Max/Min
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~_BIT0, 0x00);

    // Read Back LE Max
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // Select to Lane0
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    g_pucDpPhyRx1LE[0] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Select to Lane1
    ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    g_pucDpPhyRx1LE[1] = (ScalerGetByte_EXINT(PB2_F3_COEF_4) & 0x1F);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PB2_B1_L1_DFE_EN_2, 0x00);

#if(_DP_RX_FEC_SUPPORT == _ON)
    if(ScalerDpAuxRxGetDpcdBitInfo_EXINT0(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _BIT0)
    {
        if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
        {
            // Read Back Tap0
            ScalerSetByte_EXINT(PB2_F0_COEF_1, 0x01);

            // Select to Lane0
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            pucTap0[0] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            // Select to Lane1
            ScalerSetBit_EXINT(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            pucTap0[1] = (ScalerGetByte_EXINT(PB2_F1_COEF_2) & 0x1F);

            if(pucTap0[0] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_A4_L0_INIT_2, (pucTap0[0] + 6));
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
            }

            if(pucTap0[1] > 25)
            {
                // Reload Tap0 to 31 (Max)
                ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, 0x1F);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
            }
            else
            {
                // Reload Tap0 to Adapt + 6 (Max)
                ScalerSetByte_EXINT(PB2_B4_L1_INIT_2, (pucTap0[1] + 6));
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
                ScalerSetBit_EXINT(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
            }
        }


        /////////////////////
        // Second K Offset //
        /////////////////////

        // Read Back K offset Lane0
        if((ScalerGetByte_EXINT(P7A_AA_FORE_OFF_TST_L0) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AA_FORE_OFF_TST_L0) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Read Back K offset Lane1
        if((ScalerGetByte_EXINT(P7A_AB_FORE_OFF_TST_L1) & 0x1F) > 24)
        {
            // Set Servo = 24
            ScalerSetBit_EXINT(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        }
        else if((ScalerGetByte_EXINT(P7A_AB_FORE_OFF_TST_L1) & 0x1F) < 8)
        {
            // Set Servo = 8
            ScalerSetBit_EXINT(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
        }

        // Reload Servo
        ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x20);
        ScalerSetByte_EXINT(PB2_AA_L0_INIT_8, 0x00);
        ScalerSetByte_EXINT(PB2_BA_L1_INIT_8, 0x00);
    }
#endif

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit_EXINT(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit_EXINT(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit_EXINT(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit_EXINT(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetByte_EXINT(PB1_14_FLD_L0_20, ScalerGetByte_EXINT(PB1_32_FLD_L0_48));
    ScalerSetByte_EXINT(PB1_54_FLD_L1_20, ScalerGetByte_EXINT(PB1_72_FLD_L1_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT2, 0x00);

    ScalerSetBit_EXINT(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    ScalerSetByte_EXINT(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte_EXINT(PB1_65_FLD_L1_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}
#endif

//--------------------------------------------------
// Description : Enable Signal Detection
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SignalDetection_EXINT0(bit bEnable)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType_EXINT0(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment_EXINT0(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation_EXINT0(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            if(bEnable == _ENABLE)
            {
                // [3:0] Enable Signal Detection
                ScalerSetBit_EXINT(PB2_30_RX_CDR_16, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
                {
                    // [7:4] reg_sel_ls_path_sigdtc = 4'b0000 --> Disable Low Speed Path for Signal Detection
                    ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT7 | _BIT6), 0x00);
                }
                else
                {
                    // [7:4] reg_sel_ls_path_sigdtc = 4'b1111 --> Enable Low Speed Path for Signal Detection
                    ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                }
            }
            else
            {
                // [3:0] Disable Signal Detection
                ScalerSetBit_EXINT(PB2_30_RX_CDR_16, ~(_BIT3 | _BIT2), 0x00);
            }
        }
        else
        {
            if(bEnable == _ENABLE)
            {
                // [3:0] Enable Signal Detection
                ScalerSetBit_EXINT(PB2_30_RX_CDR_16, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
                {
                    // [7:4] reg_sel_ls_path_sigdtc = 4'b0000 --> Disable Low Speed Path for Signal Detection
                    ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT5 | _BIT4), 0x00);
                }
                else
                {
                    // [7:4] reg_sel_ls_path_sigdtc = 4'b1111 --> Enable Low Speed Path for Signal Detection
                    ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
                }
            }
            else
            {
                // [3:0] Disable Signal Detection
                ScalerSetBit_EXINT(PB2_30_RX_CDR_16, ~(_BIT1 | _BIT0), 0x00);
            }
        }
    }
    else
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    {
        if(bEnable == _ENABLE)
        {
            // [3:0] Enable Signal Detection
            ScalerSetBit_EXINT(PB2_30_RX_CDR_16, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            if(ScalerDpAuxRxGetLinkRate_EXINT0(enumInputPort) >= _DP_LINK_HBR2)
            {
                // [7:4] reg_sel_ls_path_sigdtc = 4'b0000 --> Disable Low Speed Path for Signal Detection
                ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            }
            else
            {
                // [7:4] reg_sel_ls_path_sigdtc = 4'b1111 --> Enable Low Speed Path for Signal Detection
                ScalerSetBit_EXINT(PB2_26_RX_CDR_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            }
        }
        else
        {
            // [3:0] Disable Signal Detection
            ScalerSetBit_EXINT(PB2_30_RX_CDR_16, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Lane Swap
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SetAltModeLaneMapping_EXINT0(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX1);

    ///////////////////////
    // AUX Pin-Share/PHY //
    ///////////////////////

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    // Aux Pin-Share and Aux PN Pull High/Low Setting
    ScalerPinshareRx1TypeCPinAssert_EXINT0(enumPinAssignment, enumTypeCOrientation);

    // Aux APHY Swap Setting
    ScalerDpAuxRxTypeCPinAssert_EXINT0(enumInputPort, enumPinAssignment, enumTypeCOrientation);

#if((_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))
    switch(enumPinAssignment)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:
        case _TYPE_C_PIN_ASSIGNMENT_E:

            ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE0);
            ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE1);
            ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE2);
            ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE3);

            // Disable JFM
            ScalerSetBit_EXINT(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), 0x00);

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_USB3_MODE, _GDI_PHY_LANE0);
                ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_USB3_MODE, _GDI_PHY_LANE1);
                ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE2);
                ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE3);
            }
            else
            {
                ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE0);
                ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE1);
                ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_USB3_MODE, _GDI_PHY_LANE2);
                ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_USB3_MODE, _GDI_PHY_LANE3);
            }

            break;

        default:
        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_USB3_MODE, _GDI_PHY_LANE0);
            ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_USB3_MODE, _GDI_PHY_LANE1);
            ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_USB3_MODE, _GDI_PHY_LANE2);
            ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_USB3_MODE, _GDI_PHY_LANE3);

            break;
    }
#else
    ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE0);
    ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE1);
    ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE2);
    ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE3);

    // Disable JFM
    ScalerSetBit_EXINT(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), 0x00);
#endif

#else
    enumPinAssignment = enumPinAssignment;
    enumTypeCOrientation = enumTypeCOrientation;

    ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE0);
    ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE1);
    ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE2);
    ScalerGDIPhyRxLaneMode_EXINT0(enumInputPort, _LANE_DP_MODE, _GDI_PHY_LANE3);

    // Disable JFM
    ScalerSetBit_EXINT(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), 0x00);
#endif
}
#endif
