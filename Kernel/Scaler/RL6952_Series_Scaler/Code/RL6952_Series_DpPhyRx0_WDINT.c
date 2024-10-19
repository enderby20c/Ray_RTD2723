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
// ID Code      : RL6952_Series_DpPhyRx0_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPPHYRX0_WDINT__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx0/ScalerDpPhyRx0.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX0_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx0RebuildPhy_WDINT(EnumDpLinkRate enumDpLinkRate)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_WDINT(_RX0);

    ScalerDpMacDphyRxSetCommaDetect_WDINT(enumInputPort, _ON);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType_WDINT(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment_WDINT(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation_WDINT(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            ScalerDpPhyRx0RebuildPhyUnFlip2Lane_WDINT(enumDpLinkRate);
        }
        else
        {
            ScalerDpPhyRx0RebuildPhyFlip2Lane_WDINT(enumDpLinkRate);
        }
    }
    else
#endif
    {
        ScalerDpPhyRx0RebuildPhy4Lane_WDINT(enumDpLinkRate);
    }
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx0RebuildPhy4Lane_WDINT(EnumDpLinkRate enumDpLinkRate)
{
    enumDpLinkRate = enumDpLinkRate;
    /*
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_WDINT(_RX0);
    BYTE ucIcp = 0;
    BYTE pucTap0[4];


    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte_EXINT(P1C_14_DATA_TIMER_1, 0x0F);

    ucIcp = ScalerGetBit_EXINT(P1C_27_FLD_05, (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    ///////////////
    // DFE Reset //
    ///////////////

    // Tap Divider = 10 for All Other Pattern
    ScalerSetByte_EXINT(P29_ED_LOOP_DIV_2, 0xCA);

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P29_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_D1_L3_DFE_EN_2, 0x00);

    if(ucDpLinkRate == _DP_LINK_HBR3)
    {
        // LE Max = 24, LE Initial = 20, Servo Initial = 16
        ScalerSetByte_EXINT(P29_A2_L0_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P29_B2_L1_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P29_C2_L2_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P29_D2_L3_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P29_A3_L0_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_B3_L1_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_C3_L2_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_D3_L3_INIT_1, 0xD0);
    }
    else
    {
        // LE Max = 24, LE Initial = 16, Servo Initial = 16
        ScalerSetByte_EXINT(P29_A2_L0_LIMIT_INIT, 0x80);
        ScalerSetByte_EXINT(P29_B2_L1_LIMIT_INIT, 0x80);
        ScalerSetByte_EXINT(P29_C2_L2_LIMIT_INIT, 0x80);
        ScalerSetByte_EXINT(P29_D2_L3_LIMIT_INIT, 0x80);
        ScalerSetByte_EXINT(P29_A3_L0_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_B3_L1_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_C3_L2_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_D3_L3_INIT_1, 0xD0);
    }

    // Tap0 Initial Value = 20
    ScalerSetByte_EXINT(P29_A4_L0_INIT_2, 0x14);
    ScalerSetByte_EXINT(P29_B4_L1_INIT_2, 0x14);
    ScalerSetByte_EXINT(P29_C4_L2_INIT_2, 0x14);
    ScalerSetByte_EXINT(P29_D4_L3_INIT_2, 0x14);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P29_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P29_B5_L1_INIT_3, 0x00);
    ScalerSetByte_EXINT(P29_C5_L2_INIT_3, 0x00);
    ScalerSetByte_EXINT(P29_D5_L3_INIT_3, 0x00);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P29_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P29_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P29_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P29_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P29_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P29_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P29_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P29_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P29_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P29_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    ///////////////////////////
    // Foregound Calibration //
    ///////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_17_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_18_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_19_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_1A_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
    ScalerSetBit_EXINT(P29_31_RX_GAIN_L0_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_41_RX_GAIN_L1_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_51_RX_GAIN_L2_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_61_RX_GAIN_L3_01, ~_BIT3, _BIT3);

    // Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Polling for K Offset
    for(pData_EXINT[0] = 0; pData_EXINT[0] <= 10; pData_EXINT[0]++)
    {
        if(((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_1E_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_1F_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_20_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_21_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    if(ucDpLinkRate > _DP_LINK_RBR)
    {
        // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
        ScalerSetBit_EXINT(P29_31_RX_GAIN_L0_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_41_RX_GAIN_L1_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_51_RX_GAIN_L2_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_61_RX_GAIN_L3_01, ~_BIT3, 0x00);
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(P1C_22_FLD_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Reset FLD Band
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset FLD -> Low Active Reset
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P29_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P29_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P29_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P29_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P29_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P29_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P29_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P29_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P29_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Enable FLD and DFE Adaptation
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P29_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P29_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_D1_L3_DFE_EN_2, 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(P29_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(P29_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(P29_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(P29_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte_EXINT(P29_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(P29_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte_EXINT(P29_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P29_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte_EXINT(P29_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P29_A4_L0_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P29_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P29_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(P29_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P29_B4_L1_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P29_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P29_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(P29_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P29_C4_L2_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P29_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P29_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit_EXINT(P29_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P29_D4_L3_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P29_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P29_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit_EXINT(P29_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte_EXINT(P1C_1E_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P29_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1C_1E_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P29_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte_EXINT(P1C_1F_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P29_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1C_1F_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P29_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte_EXINT(P1C_20_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P29_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1C_20_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P29_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte_EXINT(P1C_21_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P29_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1C_21_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P29_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte_EXINT(P29_AA_L0_INIT_8, 0x20);
    ScalerSetByte_EXINT(P29_BA_L1_INIT_8, 0x20);
    ScalerSetByte_EXINT(P29_CA_L2_INIT_8, 0x20);
    ScalerSetByte_EXINT(P29_DA_L3_INIT_8, 0x20);

    ScalerSetByte_EXINT(P29_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P29_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P29_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P29_DA_L3_INIT_8, 0x00);

    // [3] sel_dyn_std = 1 --> Standard DFF for K Offset
    ScalerSetBit_EXINT(P29_31_RX_GAIN_L0_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_41_RX_GAIN_L1_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_51_RX_GAIN_L2_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_61_RX_GAIN_L3_01, ~_BIT3, _BIT3);

    // Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,50] Polling for K Offset
    for(pData_EXINT[0] = 0; pData_EXINT[0] <= 10; pData_EXINT[0]++)
    {
        if(((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_1E_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_1F_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_20_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_21_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    if(ucDpLinkRate > _DP_LINK_RBR)
    {
        // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
        ScalerSetBit_EXINT(P29_31_RX_GAIN_L0_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_41_RX_GAIN_L1_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_51_RX_GAIN_L2_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_61_RX_GAIN_L3_01, ~_BIT3, 0x00);
    }

    // [7:4] reg_fld_cp_en_manual = 4'b0000 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_23_FLD_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_22_FLD_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetBit_EXINT(P1C_27_FLD_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_fld_cp_en_manual = 4'b1111 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_23_FLD_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetBit_EXINT(P1C_27_FLD_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_14_DATA_TIMER_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_WDINT(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
    */
}

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx0RebuildPhyUnFlip2Lane_WDINT(EnumDpLinkRate enumDpLinkRate)
{
    enumDpLinkRate = enumDpLinkRate;
    /*
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_WDINT(_RX0);
    BYTE ucIcp = 0;
    BYTE pucTap0[4];


    // [7/5] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/1] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P1C_14_DATA_TIMER_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT3 | _BIT1));

    ucIcp = ScalerGetBit_EXINT(P1C_27_FLD_05, (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    ///////////////
    // DFE Reset //
    ///////////////

    // Tap Divider = 10 for All Other Pattern
    ScalerSetByte_EXINT(P29_ED_LOOP_DIV_2, 0xCA);

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P29_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_D1_L3_DFE_EN_2, 0x00);

    if(ucDpLinkRate == _DP_LINK_HBR3)
    {
        // LE Max = 24, LE Initial = 20, Servo Initial = 16
        ScalerSetByte_EXINT(P29_B2_L1_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P29_D2_L3_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P29_B3_L1_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_D3_L3_INIT_1, 0xD0);
    }
    else
    {
        // LE Max = 24, LE Initial = 16, Servo Initial = 16
        ScalerSetByte_EXINT(P29_B2_L1_LIMIT_INIT, 0x80);
        ScalerSetByte_EXINT(P29_D2_L3_LIMIT_INIT, 0x80);
        ScalerSetByte_EXINT(P29_B3_L1_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_D3_L3_INIT_1, 0xD0);
    }

    // Tap0 Initial Value = 20
    ScalerSetByte_EXINT(P29_B4_L1_INIT_2, 0x14);
    ScalerSetByte_EXINT(P29_D4_L3_INIT_2, 0x14);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P29_B5_L1_INIT_3, 0x00);
    ScalerSetByte_EXINT(P29_D5_L3_INIT_3, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P29_EF_RESET_1, ~(_BIT3 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P29_EF_RESET_1, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));



    ///////////////////////////
    // Foregound Calibration //
    ///////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_18_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_1A_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
    ScalerSetBit_EXINT(P29_41_RX_GAIN_L1_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_61_RX_GAIN_L3_01, ~_BIT3, _BIT3);

    // Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT3 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));

    // Delay Time us [0,50] Polling for K Offset
    for(pData_EXINT[0] = 0; pData_EXINT[0] <= 10; pData_EXINT[0]++)
    {
        if(((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_1F_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_21_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    if(ucDpLinkRate > _DP_LINK_RBR)
    {
        // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
        ScalerSetBit_EXINT(P29_41_RX_GAIN_L1_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_61_RX_GAIN_L3_01, ~_BIT3, 0x00);
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(P1C_22_FLD_00, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Reset FLD Band
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT3 | _BIT1), 0x00);

    // Reset FLD -> Low Active Reset
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT7 | _BIT5), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P29_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P29_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P29_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P29_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P29_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Enable FLD and DFE Adaptation
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P29_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P29_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_D1_L3_DFE_EN_2, 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(P29_F0_COEF_1, 0x01);

        // Select to Lane1
        ScalerSetBit_EXINT(P29_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[0] = (ScalerGetByte_EXINT(P29_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P29_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[1] = (ScalerGetByte_EXINT(P29_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P29_B4_L1_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P29_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P29_B4_L1_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(P29_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P29_D4_L3_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P29_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P29_D4_L3_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(P29_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane1
    if((ScalerGetByte_EXINT(P1C_1F_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P29_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1C_1F_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P29_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte_EXINT(P1C_21_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P29_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1C_21_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P29_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte_EXINT(P29_BA_L1_INIT_8, 0x20);
    ScalerSetByte_EXINT(P29_DA_L3_INIT_8, 0x20);

    ScalerSetByte_EXINT(P29_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P29_DA_L3_INIT_8, 0x00);

    // [3] sel_dyn_std = 1 --> Standard DFF for K Offset
    ScalerSetBit_EXINT(P29_41_RX_GAIN_L1_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_61_RX_GAIN_L3_01, ~_BIT3, _BIT3);

    // Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT3 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));

    // Delay Time us [0,50] Polling for K Offset
    for(pData_EXINT[0] = 0; pData_EXINT[0] <= 10; pData_EXINT[0]++)
    {
        if(((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit_EXINT(P1C_1F_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit_EXINT(P1C_21_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    if(ucDpLinkRate > _DP_LINK_RBR)
    {
        // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
        ScalerSetBit_EXINT(P29_41_RX_GAIN_L1_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_61_RX_GAIN_L3_01, ~_BIT3, 0x00);
    }

    // [7/5] reg_fld_cp_en_manual = 2'b00 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_23_FLD_01, ~(_BIT7 | _BIT5), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_22_FLD_00, ~(_BIT7 | _BIT5), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetBit_EXINT(P1C_27_FLD_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7/5] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_23_FLD_01, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetBit_EXINT(P1C_27_FLD_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7/5] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_14_DATA_TIMER_1, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // [6] DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_WDINT(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
    */
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx0RebuildPhyFlip2Lane_WDINT(EnumDpLinkRate enumDpLinkRate)
{
    enumDpLinkRate = enumDpLinkRate;
    /*
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_WDINT(_RX0);
    BYTE ucIcp = 0;
    BYTE pucTap0[4];


    // [6/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [2/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit_EXINT(P1C_14_DATA_TIMER_1, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT2 | _BIT0));

    ucIcp = ScalerGetBit_EXINT(P1C_27_FLD_05, (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    ///////////////
    // DFE Reset //
    ///////////////

    // Tap Divider = 10 for All Other Pattern
    ScalerSetByte_EXINT(P29_ED_LOOP_DIV_2, 0xCA);

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P29_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_C1_L2_DFE_EN_2, 0x00);

    if(ucDpLinkRate == _DP_LINK_HBR3)
    {
        // LE Max = 24, LE Initial = 20, Servo Initial = 16
        ScalerSetByte_EXINT(P29_A2_L0_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P29_C2_L2_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P29_A3_L0_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_C3_L2_INIT_1, 0xD0);
    }
    else
    {
        // LE Max = 24, LE Initial = 16, Servo Initial = 16
        ScalerSetByte_EXINT(P29_A2_L0_LIMIT_INIT, 0x80);
        ScalerSetByte_EXINT(P29_C2_L2_LIMIT_INIT, 0x80);
        ScalerSetByte_EXINT(P29_A3_L0_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P29_C3_L2_INIT_1, 0xD0);
    }

    // Tap0 Initial Value = 20
    ScalerSetByte_EXINT(P29_A4_L0_INIT_2, 0x14);
    ScalerSetByte_EXINT(P29_C4_L2_INIT_2, 0x14);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P29_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P29_C5_L2_INIT_3, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P29_EF_RESET_1, ~(_BIT2 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P29_EF_RESET_1, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));


    ///////////////////////////
    // Foregound Calibration //
    ///////////////////////////

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit_EXINT(P1C_17_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1C_19_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
    ScalerSetBit_EXINT(P29_31_RX_GAIN_L0_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_51_RX_GAIN_L2_01, ~_BIT3, _BIT3);

    // Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT2 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

    // Delay Time us [0,50] Polling for K Offset
    for(pData_EXINT[0] = 0; pData_EXINT[0] <= 10; pData_EXINT[0]++)
    {
        if(((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_1E_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_20_FORE_OFF_TST_L2, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    if(ucDpLinkRate > _DP_LINK_RBR)
    {
        // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
        ScalerSetBit_EXINT(P29_31_RX_GAIN_L0_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_51_RX_GAIN_L2_01, ~_BIT3, 0x00);
    }


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // Enable Auto FLD
    ScalerSetBit_EXINT(P1C_22_FLD_00, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

    // Reset FLD Band
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT2 | _BIT0), 0x00);

    // Reset FLD -> Low Active Reset
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT6 | _BIT4), 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(P29_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P29_C1_L2_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P29_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P29_C1_L2_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(P29_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Enable FLD and DFE Adaptation
    ScalerSetBit_EXINT(P1C_25_FLD_03, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

    // Delay Time us [85,x] Waiting for FLD and DFE Adaptation
    DELAY_XUS_EXINT(85);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(P29_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [85,x] Waiting for DFE Adaptation
    DELAY_XUS_EXINT(85);

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(P29_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P29_C1_L2_DFE_EN_2, 0x00);

    if(ucDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(P29_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(P29_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(P29_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(P29_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[1] = (ScalerGetByte_EXINT(P29_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P29_A4_L0_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P29_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P29_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(P29_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 21)
        {
            // Reload Tap0 to 27 (Max)
            ScalerSetByte_EXINT(P29_C4_L2_INIT_2, 0x1B);
            ScalerSetBit_EXINT(P29_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(P29_C4_L2_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(P29_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(P29_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte_EXINT(P1C_1E_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P29_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1C_1E_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P29_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte_EXINT(P1C_20_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P29_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1C_20_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P29_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte_EXINT(P29_AA_L0_INIT_8, 0x20);
    ScalerSetByte_EXINT(P29_CA_L2_INIT_8, 0x20);

    ScalerSetByte_EXINT(P29_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P29_CA_L2_INIT_8, 0x00);

    // [3] sel_dyn_std = 1 --> Standard DFF for K Offset
    ScalerSetBit_EXINT(P29_31_RX_GAIN_L0_01, ~_BIT3, _BIT3);
    ScalerSetBit_EXINT(P29_51_RX_GAIN_L2_01, ~_BIT3, _BIT3);

    // Enable Foreground Offset Calibration
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT2 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1C_1B_ADJR_04, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

    // Delay Time us [0,50] Polling for K Offset
    for(pData_EXINT[0] = 0; pData_EXINT[0] <= 10; pData_EXINT[0]++)
    {
        if(((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit_EXINT(P1C_1E_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(P29_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit_EXINT(P1C_20_FORE_OFF_TST_L2, _BIT7) == _BIT7)))
        {
            break;
        }

        DELAY_5US_EXINT();
    }

    if(ucDpLinkRate > _DP_LINK_RBR)
    {
        // [3] sel_dyn_std = 0 --> Dynamic DFF for HBR/HBR2/HBR3 after K Offset
        ScalerSetBit_EXINT(P29_31_RX_GAIN_L0_01, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P29_51_RX_GAIN_L2_01, ~_BIT3, 0x00);
    }

    // [6/4] reg_fld_cp_en_manual = 2'b00 --> CDR Open Loop
    ScalerSetBit_EXINT(P1C_23_FLD_01, ~(_BIT6 | _BIT4), 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit_EXINT(P1C_22_FLD_00, ~(_BIT6 | _BIT4), 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp Icp = MAX for Locking Range
    ScalerSetBit_EXINT(P1C_27_FLD_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [6/4] reg_fld_cp_en_manual = 2'b11 --> CDR Close Loop
    ScalerSetBit_EXINT(P1C_23_FLD_01, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // reg_fld_cdr_cp = Reload Icp
    ScalerSetBit_EXINT(P1C_27_FLD_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [6/4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P1C_14_DATA_TIMER_1, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

    // [6] DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_WDINT(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
    */
}
#endif
#endif
