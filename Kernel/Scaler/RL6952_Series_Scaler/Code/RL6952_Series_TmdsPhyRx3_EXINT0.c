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
// ID Code      : RL6952_Series_TmdsPhyRx3_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_TMDSPHYRX3_EXINT0__

#include "ScalerFunctionInclude.h"
#include "TmdsPhyRx3/ScalerTmdsPhyRx3.h"



#if(_TMDS_PHY_RX3_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucTmdsPhyRx3Tap0Init;
WORD g_usTmdsPhyRx3ExDataRate = 0;
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : TMDS Set Z0 Status (EXINT0 Only)
// Input Value  : ENABLE / DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3SetZ0Status_EXINT0(bit bEnable)
{
    // reg_p_channel_en = 0x00
    // reg_n_channel_en = 0x00
    ScalerSetByte_EXINT(P7C_2B_CHANNEL_EN_00, 0x00);

    // reg_psm = 0x00
    ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT0), 0x00);

    if(bEnable == _ENABLE)
    {
        ScalerSetByte_EXINT(P7C_01_GDI_TERM_1, 0xFF);
        DELAY_5US_EXINT();
    }
    else
    {
        ScalerSetByte_EXINT(P7C_01_GDI_TERM_1, 0x00);
    }

    // reg_p_channel_en = 0x01
    // reg_n_channel_en = 0x01
    ScalerSetByte_EXINT(P7C_2B_CHANNEL_EN_00, 0xFF);

    // reg_psm = 0x01
    ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT0), (_BIT0));
}
//--------------------------------------------------
// Description  : TMDS Set Rx_EN Status (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3SetRxEn_EXINT0(BYTE ucRxENStatus)
{
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~_BIT7, (ucRxENStatus << 7));
}
//--------------------------------------------------
// Description  : TMDS DFE Initial Setting (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3SetDFEInitial_EXINT0(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsPhyRxRxDxMapping_EXINT0(_RX3);
    WORD usInputPixel = ScalerTmdsMacRxGetInputPixel_EXINT0(enumMappingPort);

    if(usInputPixel == 0)
    {
        return;
    }

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_D1_L3_DFE_EN_2, 0x00);

    if((usInputPixel > 1000))
    {
        ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        ScalerSetBit_EXINT(P7C_AF_L0_GDI_DE, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
        ScalerSetBit_EXINT(P7C_BF_L1_GDI_DE, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
        ScalerSetBit_EXINT(P7C_CF_L2_GDI_DE, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
        ScalerSetBit_EXINT(P7C_DF_L3_GDI_DE, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }
    else
    {
        ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT1 | _BIT0), _BIT1);

        ScalerSetBit_EXINT(P7C_AF_L0_GDI_DE, ~(_BIT3 | _BIT2), (_BIT3));
        ScalerSetBit_EXINT(P7C_BF_L1_GDI_DE, ~(_BIT3 | _BIT2), (_BIT3));
        ScalerSetBit_EXINT(P7C_CF_L2_GDI_DE, ~(_BIT3 | _BIT2), (_BIT3));
        ScalerSetBit_EXINT(P7C_DF_L3_GDI_DE, ~(_BIT3 | _BIT2), (_BIT3));
    }

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    // Default gray_en[7:0] =0xA1 ,set [7]=0 --> Disable LE Gray Code
    ScalerSetByte_EXINT(P7C_EE_GRAY_DEC_1, (_BIT5 | _BIT0));

    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetBit_EXINT(P7C_E0_MODE_TIMER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1));

    // Set DFE Delay Time
    ScalerSetByte_EXINT(P7C_E1_TIMER, 0x01);

    // Tap0_Gain = 1/256, Tap1_Gain = 1/512
    ScalerSetBit_EXINT(P7C_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT2));

    // Tap2_Gain = 1/512; Tap3_Gain = 1/512
    ScalerSetBit_EXINT(P7C_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4_Gain = 1/512; Servo_Gain = 1/256
    ScalerSetBit_EXINT(P7C_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE_Gain1 = 1/256, LE_Gain2 = 0
    ScalerSetBit_EXINT(P7C_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit_EXINT(P7C_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0_adjust=01
    ScalerSetBit_EXINT(P7C_F6_ERRCNT2, ~(_BIT1 | _BIT0), _BIT0);

    // Vth_Threshold[5:3][2:0] = 010010
    ScalerSetBit_EXINT(P7C_F4_ERRCNT0, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit_EXINT(P7C_E6_LIMIT_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // Tap0_Max[5][4:0] = 0 11111 = 0x1F
    ScalerSetBit_EXINT(P7C_E0_MODE_TIMER, ~(_BIT6), 0x00);
    ScalerSetBit_EXINT(P7C_E6_LIMIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    if(ScalerGetBit_EXINT(P7C_0F_GDI_DCDR_04, _BIT0) == _BIT0) // DCDR
    {
        // LE = 0~24
        if(usInputPixel <= 1000)
        {
            // Tap1 = 0~31 in Mode2
            ScalerSetBit_EXINT(P7C_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            // Tap1 = 0~55 in Mode3
            ScalerSetBit_EXINT(P7C_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
        }
    }
    else   // ACDR LE = 0~21
    {
        // Tap1 = 0~52 in Mode3,
        ScalerSetBit_EXINT(P7C_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
    }

    // Tap2 Max is 10, Min is -6
    ScalerSetBit_EXINT(P7C_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT4));
    ScalerSetBit_EXINT(P7C_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P7C_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 0, Min is -3
    ScalerSetBit_EXINT(P7C_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 0, Min is -3
    ScalerSetBit_EXINT(P7C_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_EB_LIMIT_6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P7C_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0_Threshold[4][3:0] = 0 1111
    ScalerSetBit_EXINT(P7C_E0_MODE_TIMER, ~(_BIT7), 0x00);
    ScalerSetBit_EXINT(P7C_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Vth_max = 111111
    // Vth_min = 010000
    ScalerSetBit_EXINT(P7C_F4_ERRCNT0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit_EXINT(P7C_F6_ERRCNT2, ~(_BIT3 | _BIT2), _BIT2);
    ScalerSetByte_EXINT(P7C_F9_LIMIT_10, 0xF0);

    // Set Vth/Tap Divider
    // Servo_Divider = 40
    // Vth_Divider = 15
    // Tap_Divider = 10
    ScalerSetByte_EXINT(P7C_EC_LOOP_DIV_1, 0xA3);
    ScalerSetByte_EXINT(P7C_ED_LOOP_DIV_2, 0xCA);

    // [5] servo_notrans = 1'b1 --> Transition Bits are not Effective in Servo
    // [4] tap0_notrans = 1'b1 --> Transition Bits are not Effective in Tap0
    ScalerSetBit_EXINT(P7C_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [0] tap0_trans = 1'b0 --> Nontransition Bits are Effective in Tap0
    ScalerSetBit_EXINT(P7C_E3_GAIN_2, ~_BIT0, 0x00);

    // trans_rlength[2] = 1'b0 = Default
    ScalerSetBit_EXINT(P7C_E5_GAIN_4, ~_BIT0, 0x00);

    // over 3.4Gbps, data has scramble, use Run length = 4
    if(usInputPixel >= 3400)
    {
        // [1:0] trans_rlength[1:0] = 2'b10 --> Tap0 Run Length = 4
        ScalerSetBit_EXINT(P7C_E4_GAIN_3, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // [1:0] trans_rlength[1:0] = 2'b00 --> Tap0 Run Length = 2
        ScalerSetBit_EXINT(P7C_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);
    }

    // [1] tap1_trans = 1'b1 --> Nontransition Bits are not Effective in LE/Tap1
    ScalerSetBit_EXINT(P7C_E3_GAIN_2, ~_BIT1, _BIT1);

    // [1] De_inverse = 1'b0 --> Adapation Only for Blanking Area (Transition Maximum)
    // [0] De_brank_en = 1'b0 --> Disable Blank Function of gdi_de
    ScalerSetBit_EXINT(P7C_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_DF_L3_GDI_DE, ~(_BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    if(ScalerGetBit_EXINT(P7C_0F_GDI_DCDR_04, (_BIT0)) == (_BIT0)) // DCDR
    {
        // LE Max[4] = 1, Initial[4] = 0
        ScalerSetByte_EXINT(P7C_A3_L0_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7C_B3_L1_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7C_C3_L2_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7C_D3_L3_INIT_1, 0x90);

        if(usInputPixel <= 375)
        {
            // LE Max = 24, Initial = 4
            ScalerSetByte_EXINT(P7C_A2_L0_LIMIT_INIT, 0x84);
            ScalerSetByte_EXINT(P7C_B2_L1_LIMIT_INIT, 0x84);
            ScalerSetByte_EXINT(P7C_C2_L2_LIMIT_INIT, 0x84);

            // Tap1 Initial Value = 0
            ScalerSetByte_EXINT(P7C_A5_L0_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7C_B5_L1_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7C_C5_L2_INIT_3, 0x00);
        }
        else if(usInputPixel <= 700)
        {
            // LE Max = 24, Initial = 6
            ScalerSetByte_EXINT(P7C_A2_L0_LIMIT_INIT, 0x86);
            ScalerSetByte_EXINT(P7C_B2_L1_LIMIT_INIT, 0x86);
            ScalerSetByte_EXINT(P7C_C2_L2_LIMIT_INIT, 0x86);

            // Tap1 Initial Value = 0
            ScalerSetByte_EXINT(P7C_A5_L0_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7C_B5_L1_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7C_C5_L2_INIT_3, 0x00);
        }
        else if(usInputPixel <= 1000)
        {
            // LE Max = 24, Initial = 4
            ScalerSetByte_EXINT(P7C_A2_L0_LIMIT_INIT, 0x84);
            ScalerSetByte_EXINT(P7C_B2_L1_LIMIT_INIT, 0x84);
            ScalerSetByte_EXINT(P7C_C2_L2_LIMIT_INIT, 0x84);

            // Tap1 Initial Value = 0
            ScalerSetByte_EXINT(P7C_A5_L0_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7C_B5_L1_INIT_3, 0x00);
            ScalerSetByte_EXINT(P7C_C5_L2_INIT_3, 0x00);
        }
        else
        {
            // LE Max = 24, Initial = 12
            ScalerSetByte_EXINT(P7C_A2_L0_LIMIT_INIT, 0x8C);
            ScalerSetByte_EXINT(P7C_B2_L1_LIMIT_INIT, 0x8C);
            ScalerSetByte_EXINT(P7C_C2_L2_LIMIT_INIT, 0x8C);

            // Tap1 Initial Value = 12
            ScalerSetByte_EXINT(P7C_A5_L0_INIT_3, 0x0C);
            ScalerSetByte_EXINT(P7C_B5_L1_INIT_3, 0x0C);
            ScalerSetByte_EXINT(P7C_C5_L2_INIT_3, 0x0C);
        }
    }
    else  // ACDR
    {
        // LE Max = 21, LE Initial = 15, Servo Initial = 16
        ScalerSetByte_EXINT(P7C_A2_L0_LIMIT_INIT, 0x5F);
        ScalerSetByte_EXINT(P7C_B2_L1_LIMIT_INIT, 0x5F);
        ScalerSetByte_EXINT(P7C_C2_L2_LIMIT_INIT, 0x5F);
        ScalerSetByte_EXINT(P7C_D2_L3_LIMIT_INIT, 0x5F);

        ScalerSetByte_EXINT(P7C_A3_L0_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7C_B3_L1_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7C_C3_L2_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7C_D3_L3_INIT_1, 0x90);

        // Tap1 Initial Value = 15
        ScalerSetByte_EXINT(P7C_A5_L0_INIT_3, 0x0F);
        ScalerSetByte_EXINT(P7C_B5_L1_INIT_3, 0x0F);
        ScalerSetByte_EXINT(P7C_C5_L2_INIT_3, 0x0F);
        ScalerSetByte_EXINT(P7C_D5_L3_INIT_3, 0x0F);
    }

    if(usInputPixel <= 375)
    {
        // Tap0[5][4:0]=0x14
        ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT3), 0x00);
        ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT3), 0x00);
        ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT3), 0x00);
        ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT3), 0x00);
        ScalerSetBit_EXINT(P7C_A4_L0_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x14);
        ScalerSetBit_EXINT(P7C_B4_L1_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x14);
        ScalerSetBit_EXINT(P7C_C4_L2_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x14);
        ScalerSetBit_EXINT(P7C_D4_L3_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x14);
    }
    else
    {
        // Tap0[5][4:0]=0x0F
        ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT3), 0x00);
        ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT3), 0x00);
        ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT3), 0x00);
        ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT3), 0x00);
        ScalerSetBit_EXINT(P7C_A4_L0_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit_EXINT(P7C_B4_L1_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit_EXINT(P7C_C4_L2_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit_EXINT(P7C_D4_L3_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
    }

    // Tap2
    ScalerSetByte_EXINT(P7C_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7C_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7C_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7C_D6_L3_INIT_4, 0x00);

    // Tap3 Initial -> Default
    ScalerSetByte_EXINT(P7C_A7_L0_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7C_B7_L1_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7C_C7_L2_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7C_D7_L3_INIT_5, 0x00);

    // Tap4 Initial -> Default
    ScalerSetByte_EXINT(P7C_A8_L0_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7C_B8_L1_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7C_C8_L2_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7C_D8_L3_INIT_6, 0x00);

    // Vth
    ScalerSetByte_EXINT(P7C_A9_L0_INIT_7, 0x1C);
    ScalerSetByte_EXINT(P7C_B9_L1_INIT_7, 0x1C);
    ScalerSetByte_EXINT(P7C_C9_L2_INIT_7, 0x1C);
    ScalerSetByte_EXINT(P7C_D9_L3_INIT_7, 0x1C);

    // DFE Loop Normal Reset, before load_in at Mode3 in S4
    ScalerSetBit_EXINT(P7C_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    DELAY_XUS_EXINT(150);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7C_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_DA_L3_INIT_8, 0x00);

    DELAY_XUS_EXINT(150);
}
//--------------------------------------------------
// Description  : TMDS Frl DFE Initial Setting (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3FrlSetDFEInitial_EXINT0(void)
{
    // Tap Divider = 10 for All Other Pattern
    ScalerSetByte_EXINT(P7C_ED_LOOP_DIV_2, 0xCA);

    // [6] Enable Timer Control DFE Loop
    ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT6), (_BIT6));
    ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT6), (_BIT6));
    ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT6), (_BIT6));
    ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT6), (_BIT6));

    // [5:4] Reduce Gain to 1/4
    ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT5 | _BIT4), (_BIT5));
    ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT5 | _BIT4), (_BIT5));
    ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT5 | _BIT4), (_BIT5));
    ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT5 | _BIT4), (_BIT5));

    // [1:0] Mode 2 DFE
    ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT1 | _BIT0), (_BIT1));
    ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT1 | _BIT0), (_BIT1));
    ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT1 | _BIT0), (_BIT1));
    ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT1 | _BIT0), (_BIT1));

    // adapt_mode_post_lane0~3[1:0] = 2'b10
    ScalerSetBit_EXINT(P7C_AF_L0_GDI_DE, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit_EXINT(P7C_BF_L1_GDI_DE, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit_EXINT(P7C_CF_L2_GDI_DE, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit_EXINT(P7C_DF_L3_GDI_DE, ~(_BIT3 | _BIT2), _BIT3);

    // [7] Tap0_Threshold[4] = 0
    // [6] Tap0_max[5] = 0
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte_EXINT(P7C_E0_MODE_TIMER, 0x32);

    // [1:0] trans_rlength = 3'b000 --> Tap0 Run Length = 2
    ScalerSetBit_EXINT(P7C_E5_GAIN_4, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7C_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);

    // Tap0 Loop Gain 1/512, Tap1 Loop Gain 1/128
    ScalerSetBit_EXINT(P7C_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit_EXINT(P7C_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit_EXINT(P7C_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0
    ScalerSetBit_EXINT(P7C_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));

    // LE Pre-Courser Gain 0
    ScalerSetBit_EXINT(P7C_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetBit_EXINT(P7C_F8_GRAY_DEC_2, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte_EXINT(P7C_EC_LOOP_DIV_1, 0xA3);

    // Default gray_en[7:0] =0xA1 ,set [7]=0 --> Disable LE Gray Code
    ScalerSetByte_EXINT(P7C_EE_GRAY_DEC_1, (_BIT5 | _BIT0));

    // Set Vth Max = 63, Min = 12
    ScalerSetBit_EXINT(P7C_F4_ERRCNT0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit_EXINT(P7C_F6_ERRCNT2, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetByte_EXINT(P7C_F9_LIMIT_10, 0xFC);

    // Tap0 Max is 31
    ScalerSetBit_EXINT(P7C_E6_LIMIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Tap1 Min is -15
    ScalerSetByte_EXINT(P7C_E7_LIMIT_2, 0x0F);

    // Tap2 Max is 6, Min is -6
    ScalerSetBit_EXINT(P7C_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7C_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P7C_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 3, Min is -3
    ScalerSetBit_EXINT(P7C_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit_EXINT(P7C_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 3, Min is -3
    ScalerSetBit_EXINT(P7C_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_EB_LIMIT_6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit_EXINT(P7C_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Vth Threshold = 18
    ScalerSetBit_EXINT(P7C_F4_ERRCNT0, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit_EXINT(P7C_E6_LIMIT_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // tap0_adjust[1:0] = 0x00
    ScalerSetBit_EXINT(P7C_F6_ERRCNT2, ~(_BIT1 | _BIT0), 0x00);

    // Tap0 Threshold = 10
    ScalerSetBit_EXINT(P7C_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // [1] tap1_trans = 1'b1 --> Tap1 is Effective on Transition bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every Bits
    ScalerSetBit_EXINT(P7C_E3_GAIN_2, ~(_BIT1 | _BIT0), _BIT1);

    // [4] tap0_notrans = 1
    ScalerSetBit_EXINT(P7C_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // [5] servo_notrans = 1'b0 --> Servo is Effective on Every Bits
    ScalerSetBit_EXINT(P7C_F8_GRAY_DEC_2, ~_BIT5, 0x00);

    // Disable All Adaptation Loop
    ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_D1_L3_DFE_EN_2, 0x00);


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // LE Max = 31, LE Initial = 16, Servo Initial = 16
    ScalerSetByte_EXINT(P7C_A2_L0_LIMIT_INIT, 0xF0);
    ScalerSetByte_EXINT(P7C_B2_L1_LIMIT_INIT, 0xF0);
    ScalerSetByte_EXINT(P7C_C2_L2_LIMIT_INIT, 0xF0);
    ScalerSetByte_EXINT(P7C_D2_L3_LIMIT_INIT, 0xF0);

    ScalerSetByte_EXINT(P7C_A3_L0_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P7C_B3_L1_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P7C_C3_L2_INIT_1, 0xD0);
    ScalerSetByte_EXINT(P7C_D3_L3_INIT_1, 0xD0);

    // Tap1 Initial Value = 3
    ScalerSetByte_EXINT(P7C_A5_L0_INIT_3, 0x03);
    ScalerSetByte_EXINT(P7C_B5_L1_INIT_3, 0x03);
    ScalerSetByte_EXINT(P7C_C5_L2_INIT_3, 0x03);
    ScalerSetByte_EXINT(P7C_D5_L3_INIT_3, 0x03);

    // Tap0[5][4:0] = 20
    ScalerSetBit_EXINT(P7C_A0_L0_DFE_EN_1, ~(_BIT3), 0x00);
    ScalerSetBit_EXINT(P7C_B0_L1_DFE_EN_1, ~(_BIT3), 0x00);
    ScalerSetBit_EXINT(P7C_C0_L2_DFE_EN_1, ~(_BIT3), 0x00);
    ScalerSetBit_EXINT(P7C_D0_L3_DFE_EN_1, ~(_BIT3), 0x00);
    ScalerSetBit_EXINT(P7C_A4_L0_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x14);
    ScalerSetBit_EXINT(P7C_B4_L1_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x14);
    ScalerSetBit_EXINT(P7C_C4_L2_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x14);
    ScalerSetBit_EXINT(P7C_D4_L3_INIT_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x14);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P7C_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7C_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7C_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7C_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 24
    ScalerSetBit_EXINT(P7C_A9_L0_INIT_7, ~0x7F, 0x18);
    ScalerSetBit_EXINT(P7C_B9_L1_INIT_7, ~0x7F, 0x18);
    ScalerSetBit_EXINT(P7C_C9_L2_INIT_7, ~0x7F, 0x18);
    ScalerSetBit_EXINT(P7C_D9_L3_INIT_7, ~0x7F, 0x18);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7C_DA_L3_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal Reset
    ScalerSetBit_EXINT(P7C_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    DELAY_XUS_EXINT(150);
}
//--------------------------------------------------
// Description  : TMDS CLK Measure Mux
// Input Value  : Lane0~3
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3CdrMeasureClkSelect_EXINT0(BYTE ucLane)
{
    // reg_sel_hdmi_measure_clk = ucLane
    ScalerSetBit_EXINT(P1D_FC_DATA_PATH_16, ~(_BIT7 | _BIT6), ucLane << 6);
}
//--------------------------------------------------
// Description  : TMDS CLK Measure Mux
// Input Value  : Lane0~3
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3Cdr2xClkEnable_EXINT0(bit bEnable)
{
    // reg_enable_clk_div5 can only be used in HDMI20 or HDMI14 , must be 0 at HDMI21
    if(bEnable == _TRUE)
    {
        if(ScalerGetBit_EXINT(P1D_1B_ANA_CDR_01, _BIT3) == _BIT3) // reg_hdmi20_en = 0x01
        {
            // reg_enable_clk_div5 = _TRUE
            ScalerSetBit_EXINT(P7C_0B_GDI_DIGI_13, ~(_BIT0), _TRUE);
        }
    }
    else
    {
        // reg_enable_clk_div5 = _FALSE
        ScalerSetBit_EXINT(P7C_0B_GDI_DIGI_13, ~(_BIT0), _FALSE);
    }
}
//--------------------------------------------------
// Description  : FRL Mac Transition detect data lane sel
// Input Value  : Lane0~3
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3TransitionDataLaneSelect_EXINT0(BYTE ucLane)
{
    // reg_sel_hdmi_trans_clk = ucLane
    ScalerSetBit_EXINT(P1D_FC_DATA_PATH_16, ~(_BIT1 | _BIT0), ucLane);
}

//--------------------------------------------------
// Description  : FRL Mac Transition detect data Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3TransitionDataEnable_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable reg_en_sigdect for L0~3
        ScalerSetBit_EXINT(P7C_09_GDI_DIGI_11, ~(_BIT0), (_BIT0));
    }
    else
    {
        // Enable reg_en_sigdect for L0~3
        ScalerSetBit_EXINT(P7C_09_GDI_DIGI_11, ~(_BIT0), 0x00);
    }
}
//--------------------------------------------------
// Description  : TMDS FIFO Auto Reset Enable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3FifoAutoResetEnable_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // [7:4]reg_fifo_auto_rst_l0~3 = 1
        ScalerSetByte_EXINT(P1D_E8_FLD_KICO_B15, 0xFF);
    }
    else
    {
        ScalerSetByte_EXINT(P1D_E8_FLD_KICO_B15, 0x0F);
    }
}
//--------------------------------------------------
// Description  : TMDS FIFO Auto Reset Flag Clear
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3FifoAutoClearFlag_EXINT0(void)
{
    // Need ScalerTmdsPhyRx3FifoAutoResetEnable(_Enable)
    // reg_fifo_unstable_clr_l0~3 = 1, write one clear
    ScalerSetBit_EXINT(P1D_E8_FLD_KICO_B15, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}
//--------------------------------------------------
// Description  : TMDS FIFO Auto Reset Done Check
// Input Value  : None
// Output Value : BYTE unstable_flag
//--------------------------------------------------
BYTE ScalerTmdsPhyRx3FifoAutoResetDone_EXINT0(void)
{
    // Return Value[0] = 1 -> L0 Done flag=1, [1] = L1, [2] = L2 , [3] = L3
    // Return Value = 0, flag=0
    // read fifo_unstable_flag_l0~3
    return (ScalerGetBit_EXINT(P1D_E9_REG_CLKWR_INV, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
}
//--------------------------------------------------
// Description  : TMDS FIFO Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3UnstableFifoReset_EXINT0(void)
{
    // Reset Lane 0
    ScalerSetBit_EXINT(P1D_F8_DATA_PATH_12, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(P1D_F8_DATA_PATH_12, ~_BIT2, _BIT2);

    // Reset Lane 1
    ScalerSetBit_EXINT(P1D_F9_DATA_PATH_13, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(P1D_F9_DATA_PATH_13, ~_BIT2, _BIT2);

    // Reset Lane 2
    ScalerSetBit_EXINT(P1D_FA_DATA_PATH_14, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(P1D_FA_DATA_PATH_14, ~_BIT2, _BIT2);

    // Reset Lane 3
    ScalerSetBit_EXINT(P1D_FB_DATA_PATH_15, ~_BIT2, 0x00);
    ScalerSetBit_EXINT(P1D_FB_DATA_PATH_15, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : ScalerTMDSFRLPathSel_EXINT0 (EXINT0 Only)
// Input Value  : FRL =1 => HDMI2.1 path or FRL = 0 TMDS mode
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3FRLPathSel_EXINT0(bit bFRL)
{
    // reg_sel_div10_div20_sigdetect = 0x01
    ScalerSetBit_EXINT(P7C_0B_GDI_DIGI_13, ~(_BIT1), (_BIT1));

    if(bFRL == 0)
    {
        // reg_en_div18_clk = 0x00
        ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT1), 0x00);

        // reg_xtal_sel = 0x00
        ScalerSetBit_EXINT(P1D_1E_ANA_CDR_04, ~(_BIT7), 0x00);

        // reg_hdmi_ck_sel = 0x01
        ScalerSetBit_EXINT(P1D_1F_ANA_CDR_05, ~(_BIT5), (_BIT5));

        // reg_hdmi21_en = 0x00
        ScalerSetBit_EXINT(P1D_1E_ANA_CDR_04, ~(_BIT6), 0x00);

        // reg_hdmi20_en = 0x01
        ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT3), (_BIT3));
    }
    else
    {
        // reg_en_div18_clk = 0x01
        ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT1), (_BIT1));

        // reg_xtal_sel = 0x01
        ScalerSetBit_EXINT(P1D_1E_ANA_CDR_04, ~(_BIT7), (_BIT7));

        // reg_hdmi_ck_sel = 0x00 ->clock from xtal
        ScalerSetBit_EXINT(P1D_1F_ANA_CDR_05, ~(_BIT5), (0x00));

        // reg_hdmi21_en = 0x01
        ScalerSetBit_EXINT(P1D_1E_ANA_CDR_04, ~(_BIT6), (_BIT6));

        // reg_hdmi20_en = 0x00
        ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT3), 0x00);
    }
}

//--------------------------------------------------
// Description  : TMDS Set PHY Function (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3SetPhy_EXINT0(void)
{
    EnumInputPort enumMappingPort = ScalerTmdsPhyRxRxDxMapping_EXINT0(_RX3);
    BYTE ucOffsetOK = 0;
    BYTE ucFldOK = 0;
    BYTE ucDivNum = 0;
    WORD usFLDBand = 0;
    WORD usHVDiff = 0;
    WORD usLVDiff = 0;
    WORD usVCOfreq = 0;
    DWORD ulSlopeHV = 0;
    DWORD ulSlopeLV = 0;

    WORD usInputPixel = ScalerTmdsMacRxGetInputPixel(enumMappingPort);

    if(usInputPixel == 0)
    {
        return;
    }

    // Reset channel fifo & DFE ready bit
    ScalerSetBit_EXINT(P1D_F8_DATA_PATH_12, ~(_BIT2 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P1D_F9_DATA_PATH_13, ~(_BIT2 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P1D_FA_DATA_PATH_14, ~(_BIT2 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P1D_FB_DATA_PATH_15, ~(_BIT2 | _BIT1), 0x00);

    // [7:4]reg_rx_en = 0x0F
    // [3:0]reg_cdr_en = 0x00
    // [4]reg_bg_en = 0x01
    ScalerSetByte_EXINT(P7C_10_GDI_POWR_00, 0xF0);
    ScalerSetBit_EXINT(P7C_02_GDI_TERM_2, ~(_BIT4), (_BIT4));

    // reg_vcckoffb_dv = 0x01
    // reg_en_sigdect = 0x00
    ScalerSetBit_EXINT(P7C_16_GDI_CTRL1, ~(_BIT0), (_BIT0));
    ScalerSetBit_EXINT(P7C_09_GDI_DIGI_11, ~(_BIT0), 0x00);

    // reg_rxvcom_sel = 0x01
    ScalerSetBit_EXINT(P7C_11_GDI_POWR_18, ~(_BIT5 | _BIT4), _BIT4);


    ///////////////////
    // Power Process //
    ///////////////////

    ScalerTmdsPhyRx3SetZ0Status_EXINT0(_ENABLE);

    // reg_p_channel_en = 0x01
    // reg_n_channel_en = 0x01
    ScalerSetByte_EXINT(P7C_2B_CHANNEL_EN_00, 0xFF);

    if(usInputPixel <= 2000) // DCDR
    {
        if(usInputPixel <= 375)
        {
            // kp = 3.5(U2.4)
            ScalerSetBit_EXINT(P1D_61_DCDR_17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x38);
            ScalerSetBit_EXINT(P1D_63_DCDR_19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x38);
            ScalerSetBit_EXINT(P1D_65_DCDR_21, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x38);
            ScalerSetBit_EXINT(P1D_67_DCDR_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x38);
        }
        else if(usInputPixel <= 1500)
        {
            // kp = 3.75(U2.4)
            ScalerSetBit_EXINT(P1D_61_DCDR_17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3C);
            ScalerSetBit_EXINT(P1D_63_DCDR_19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3C);
            ScalerSetBit_EXINT(P1D_65_DCDR_21, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3C);
            ScalerSetBit_EXINT(P1D_67_DCDR_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3C);
        }
        else if(usInputPixel <= 1750)
        {
            // kp = 2.5(U2.4)
            ScalerSetBit_EXINT(P1D_61_DCDR_17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x24);
            ScalerSetBit_EXINT(P1D_63_DCDR_19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x24);
            ScalerSetBit_EXINT(P1D_65_DCDR_21, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x24);
            ScalerSetBit_EXINT(P1D_67_DCDR_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x24);
        }
        else // 1750~2000
        {
            // kp = 2(U2.4)
            ScalerSetBit_EXINT(P1D_61_DCDR_17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);
            ScalerSetBit_EXINT(P1D_63_DCDR_19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);
            ScalerSetBit_EXINT(P1D_65_DCDR_21, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);
            ScalerSetBit_EXINT(P1D_67_DCDR_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);
        }

        if(usInputPixel <= 1500)
        {
            // KI = 0x01=1/512
            ScalerSetBit_EXINT(P1D_71_KI_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
            ScalerSetBit_EXINT(P1D_71_KI_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(P1D_72_KI_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
            ScalerSetBit_EXINT(P1D_72_KI_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
        }
        else
        {
            // KI = 0x02
            ScalerSetBit_EXINT(P1D_71_KI_00, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
            ScalerSetBit_EXINT(P1D_71_KI_00, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit_EXINT(P1D_72_KI_01, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
            ScalerSetBit_EXINT(P1D_72_KI_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
        }
    }
    else
    {
        // kp = 0x20 ->Default
        ScalerSetBit_EXINT(P1D_61_DCDR_17, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);
        ScalerSetBit_EXINT(P1D_63_DCDR_19, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);
        ScalerSetBit_EXINT(P1D_65_DCDR_21, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);
        ScalerSetBit_EXINT(P1D_67_DCDR_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x20);
    }

    // reg_en_back_offset = 0x01
    ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT3), _BIT3);

    // reg_en_fore_offset = 0x01
    ScalerSetBit_EXINT(P7C_0F_GDI_DCDR_04, ~(_BIT7), (_BIT7));

    // reg_en_lpf_vco = 0x01
    ScalerSetBit_EXINT(P7C_08_GDI_DIGI_05, ~(_BIT7), _BIT7);

    // reg_vco_lpf_force_en=0x01
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT0), _BIT0);


    ////////////
    // SETPHY //
    ////////////

    // reg_sel_clklane_div4 = 0x00 -->clk lane divider for cmu
    ScalerSetBit_EXINT(P7C_0C_GDI_DCDR_01, ~(_BIT4), 0x00);

    ScalerTmdsPhyRx3FRLPathSel_EXINT0(0);

    // reg_sel_cmu_ref = 0x11
    ScalerSetBit_EXINT(P7C_0C_GDI_DCDR_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // reg_en_large_icp = 0x00
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT2), 0x00);

    // reg_sel_large_icp_kp = 0x00->Default
    ScalerSetBit_EXINT(P7C_16_GDI_CTRL1, ~(_BIT3), 0x00);

    if(usInputPixel <= 2000)
    {
        // [0]reg_en_dcdr = 0x01
        // [4]reg_en_large_rs_for_cmu = 0x01
        // [7:4]reg_config_cmu = 0x07
        ScalerSetBit_EXINT(P7C_0F_GDI_DCDR_04, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
        ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

        // [2] reg_en_prclk_to_data=1
        ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT2), _BIT2);

        // 0x7C0D[7:6],reg_cmu_cp=0x03
        ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // reg_acdr_en = 0x00
        ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT0), 0x00);

        // [7:4]reg_wd_pll_en = 0x01
        ScalerSetBit_EXINT(P1D_A1_CMU_WATCHDOG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [7:4]reg_shift_inv_l0~3 = 0x00
        ScalerSetBit_EXINT(P1D_52_DCDR_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // [3:0]reg_st_mode_l0~3 = 0x01
        ScalerSetBit_EXINT(P1D_4F_DCDR_TEST_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // [4]reg_en_op_cp_kp_path = 0x00
        // [3]reg_en_cp_kp_path = 0x00
        ScalerSetBit_EXINT(P7C_14_GDI_FEEDBACK_RES, ~(_BIT4 | _BIT3), 0x00);

        // [5:4]reg_ic_sel_l0~3 = 2'b10
        ScalerSetBit_EXINT(P1D_20_FLD_KICO_L0_A00, ~(_BIT5 | _BIT4), (_BIT5));
        ScalerSetBit_EXINT(P1D_24_FLD_KICO_L1_A00, ~(_BIT5 | _BIT4), (_BIT5));
        ScalerSetBit_EXINT(P1D_28_FLD_KICO_L2_A00, ~(_BIT5 | _BIT4), (_BIT5));
        ScalerSetBit_EXINT(P1D_2C_FLD_KICO_L3_A00, ~(_BIT5 | _BIT4), (_BIT5));

        // [7:3],reg_slope_icp_offset_l0[24:20] = 0x00 -> default
        // [6:2],reg_slope_icp_offset_l1[24:20] = 0x00 -> default
        // [4:0],reg_slope_icp_offset_l2[24:20] = 0x00 -> default
        // [4:0],reg_slope_icp_offset_l3[24:20] = 0x00 -> default
        ScalerSetBit_EXINT(P1D_DD_U3_FLD_RES_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (0x00 << 3));
        ScalerSetBit_EXINT(P1D_E0_U3_FLD_40, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (0x00 << 2));
        ScalerSetBit_EXINT(P1D_E3_U3_FLD_RESV_00, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P1D_E4_U3_FLD_RESV_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // reg_slope_icp_offset_l0~3[19:16] = 0x00 -> default
        ScalerSetByte_EXINT(P1D_A8_FLD_KICO_B00, 0x00);
        ScalerSetByte_EXINT(P1D_CB_FLD_KICO_B07, 0x00);

        // reg_slope_icp_offset_l0~3[15:8] = 0x00 -> default
        ScalerSetByte_EXINT(P1D_A9_FLD_KICO_B01, 0x00);
        ScalerSetByte_EXINT(P1D_AB_FLD_KICO_B03, 0x00);
        ScalerSetByte_EXINT(P1D_CC_FLD_KICO_B08, 0x00);
        ScalerSetByte_EXINT(P1D_CE_FLD_KICO_B10, 0x00);

        // reg_slope_icp_offset_l0~3[7:0] = 0x00 -> default
        ScalerSetByte_EXINT(P1D_AA_FLD_KICO_B02, 0x00);
        ScalerSetByte_EXINT(P1D_AC_FLD_KICO_B04, 0x00);
        ScalerSetByte_EXINT(P1D_CD_FLD_KICO_B09, 0x00);
        ScalerSetByte_EXINT(P1D_CF_FLD_KICO_B11, 0x00);

        // reg_slope_band_l0~3[3:0] = 0x08 -> default
        ScalerSetByte_EXINT(P1D_E1_U3_FLD_41, 0x88);
        ScalerSetByte_EXINT(P1D_E2_U3_FLD_42, 0x88);

        // reg_enable_pr = 0x01
        ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT1), _BIT1);

        // reg_en_cpkp_mirror_path = 0x00
        ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT4), 0x00);

        // reg_cdr_direct_l0~3=0x00
        ScalerSetBit_EXINT(P7C_22_BACK_OFFCAL_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        if(usInputPixel <= 375)
        {
            // reg_cdr_r=0x37
            ScalerSetBit_EXINT(P1D_CA_U3_FLD_26, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x37);

            // reg_cdr_cp[19:16][15:8][7:0] = 0x07 77 75
            ScalerSetBit_EXINT(P1D_C7_U3_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
            ScalerSetByte_EXINT(P1D_C6_U3_FLD_22, 0x77);
            ScalerSetByte_EXINT(P1D_C5_U3_FLD_21, 0x75);

            // reg_bypass_div5_cdrdec[1:1] = 0x01
            ScalerSetBit_EXINT(P1D_50_DCDR_00, ~(_BIT3), _BIT3);

            // reg_bypass_div5_cdrdec[0:0] = 0x00->Default
            ScalerSetBit_EXINT(P1D_52_DCDR_02, ~(_BIT3), 0x00);

            // reg_bypass_cdr_dec = 2'b11
            ScalerSetBit_EXINT(P7C_0B_GDI_DIGI_13, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        }
        else if(usInputPixel <= 1500)
        {
            // reg_cdr_r=0x35
            ScalerSetBit_EXINT(P1D_CA_U3_FLD_26, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT0));

            // reg_cdr_cp[19:16][15:8][7:0] = 0x07 77 76
            ScalerSetBit_EXINT(P1D_C7_U3_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
            ScalerSetByte_EXINT(P1D_C6_U3_FLD_22, 0x77);
            ScalerSetByte_EXINT(P1D_C5_U3_FLD_21, 0x76);

            // reg_bypass_div5_cdrdec[1:1] = 0x01
            ScalerSetBit_EXINT(P1D_50_DCDR_00, ~(_BIT3), _BIT3);

            // reg_bypass_div5_cdrdec[0:0] = 0x00->Default
            ScalerSetBit_EXINT(P1D_52_DCDR_02, ~(_BIT3), 0x00);

            // reg_bypass_cdr_dec = 2'b11
            ScalerSetBit_EXINT(P7C_0B_GDI_DIGI_13, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        }
        else // 1500~2000
        {
            // reg_cdr_r=0x35
            ScalerSetBit_EXINT(P1D_CA_U3_FLD_26, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT0));

            // reg_cdr_cp[19:16][15:8][7:0] = 0x07 77 76
            ScalerSetBit_EXINT(P1D_C7_U3_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
            ScalerSetByte_EXINT(P1D_C6_U3_FLD_22, 0x77);
            ScalerSetByte_EXINT(P1D_C5_U3_FLD_21, 0x76);

            // reg_bypass_div5_cdrdec[1:1] = 0x00
            ScalerSetBit_EXINT(P1D_50_DCDR_00, ~(_BIT3), _BIT3);

            // reg_bypass_div5_cdrdec[0:0] = 0x01
            ScalerSetBit_EXINT(P1D_52_DCDR_02, ~(_BIT3), 0x00);

            // reg_bypass_cdr_dec = 2'b10
            ScalerSetBit_EXINT(P7C_0B_GDI_DIGI_13, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        }
    }
    else
    {
        // [0]reg_en_dcdr = 0x00
        // [4]reg_en_large_rs_for_cmu = 0x00
        // [7:4]reg_config_cmu = 0x00
        ScalerSetBit_EXINT(P7C_0F_GDI_DCDR_04, ~(_BIT4 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // [2] reg_en_prclk_to_data=0
        ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT2), 0x00);

        // 0x7C0D[7:6],reg_cmu_cp=0x00-->Default
        ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT7 | _BIT6), 0x00);

        // reg_acdr_en = 0x01
        ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT0), (_BIT0));

        // [7:4]reg_wd_pll_en = 0x00 -->Default
        ScalerSetBit_EXINT(P1D_A1_CMU_WATCHDOG_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // [7:4]reg_shift_inv_l0~3 = 0x01->Default
        ScalerSetBit_EXINT(P1D_52_DCDR_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [3:0]reg_st_mode_l0~3 = 0x00->Default
        ScalerSetBit_EXINT(P1D_4F_DCDR_TEST_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // [4]reg_en_op_cp_kp_path = 0x01
        // [3]reg_en_cp_kp_path = 0x01
        ScalerSetBit_EXINT(P7C_14_GDI_FEEDBACK_RES, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // [5:4]reg_ic_sel_l0~3 = 2'b01
        ScalerSetBit_EXINT(P1D_20_FLD_KICO_L0_A00, ~(_BIT5 | _BIT4), (_BIT4));
        ScalerSetBit_EXINT(P1D_24_FLD_KICO_L1_A00, ~(_BIT5 | _BIT4), (_BIT4));
        ScalerSetBit_EXINT(P1D_28_FLD_KICO_L2_A00, ~(_BIT5 | _BIT4), (_BIT4));
        ScalerSetBit_EXINT(P1D_2C_FLD_KICO_L3_A00, ~(_BIT5 | _BIT4), (_BIT4));

        // reg_cdr_r = 0x30
        ScalerSetBit_EXINT(P1D_CA_U3_FLD_26, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x30);

        // reg_cdr_cp[19:16][15:8][7:0] = 0x07 77 74/72
        ScalerSetBit_EXINT(P1D_C7_U3_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
        ScalerSetByte_EXINT(P1D_C6_U3_FLD_22, 0x77);

        if(usInputPixel <= 3000) // 2000~3000
        {
            ScalerSetByte_EXINT(P1D_C5_U3_FLD_21, 0x74);
        }
        else if(usInputPixel <= 3400)
        {
            ScalerSetByte_EXINT(P1D_C5_U3_FLD_21, 0x72);
        }
        else
        {
            ScalerSetByte_EXINT(P1D_C5_U3_FLD_21, 0x74);
        }

        // reg_slope_icp_offset_l0~3[24:20]=0x00 -> default
        ScalerSetBit_EXINT(P1D_DD_U3_FLD_RES_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
        ScalerSetBit_EXINT(P1D_E0_U3_FLD_40, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        ScalerSetBit_EXINT(P1D_E3_U3_FLD_RESV_00, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P1D_E4_U3_FLD_RESV_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // reg_slope_icp_offset_l0~3[19:16] = 0x02
        ScalerSetByte_EXINT(P1D_A8_FLD_KICO_B00, 0x22);
        ScalerSetByte_EXINT(P1D_CB_FLD_KICO_B07, 0x22);

        // reg_slope_icp_offset_l0~3[15:8] = 0x22
        ScalerSetByte_EXINT(P1D_A9_FLD_KICO_B01, 0x22);
        ScalerSetByte_EXINT(P1D_AB_FLD_KICO_B03, 0x22);
        ScalerSetByte_EXINT(P1D_CC_FLD_KICO_B08, 0x22);
        ScalerSetByte_EXINT(P1D_CE_FLD_KICO_B10, 0x22);

        // reg_slope_icp_offset_l0~3[7:0] = 0x20
        ScalerSetByte_EXINT(P1D_AA_FLD_KICO_B02, 0x20);
        ScalerSetByte_EXINT(P1D_AC_FLD_KICO_B04, 0x20);
        ScalerSetByte_EXINT(P1D_CD_FLD_KICO_B09, 0x20);
        ScalerSetByte_EXINT(P1D_CF_FLD_KICO_B11, 0x20);

        // reg_slope_band_l0~3[3:0] = 0x09
        ScalerSetByte_EXINT(P1D_E1_U3_FLD_41, 0x99);
        ScalerSetByte_EXINT(P1D_E2_U3_FLD_42, 0x99);

        // reg_enable_pr = 0x00 ->Default
        ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT1), 0x00);

        // reg_bypass_cdr_dec = 2'b01 ->Default
        ScalerSetBit_EXINT(P7C_0B_GDI_DIGI_13, ~(_BIT5 | _BIT4), (_BIT4));

        // reg_bypass_div5_cdrdec[1:1] = 0x00 ->Default
        ScalerSetBit_EXINT(P1D_50_DCDR_00, ~(_BIT3), 0x00);

        // reg_bypass_div5_cdrdec[0:0] = 0x00->Default
        ScalerSetBit_EXINT(P1D_52_DCDR_02, ~(_BIT3), 0x00);

        // reg_en_cpkp_mirror_path = 0x01
        ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT4), _BIT4);

        // reg_cdr_direct_l0~3=0x01 -->Default
        ScalerSetBit_EXINT(P7C_22_BACK_OFFCAL_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    }

    // reg_rstb_fsm[3][2:0] = 0x00
    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), 0x00);

    // reg_en_offpn_edge_demux = 0x01->Enable offpn mux, set 0 when DFE adapt,offsetK end
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT1), _BIT1);

    // reg_fld_reserved[18] = reg_aphy_adp_en_off = 0
    ScalerSetBit_EXINT(P1D_DD_U3_FLD_RES_00, ~(_BIT2), 0x00);

    // reg_en_fld_div = 0x01
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT3), _BIT3);

    // reg_pi_ibsel = 0x01
    ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT4));

    if(usInputPixel <= 375)
    {
        // reg_slope_icp_band_l0~3[3:0] = 0x00
        ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x00);
        ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x00);

        // reg_sel_div = 0x05
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
    }
    else if(usInputPixel <= 750)
    {
        // reg_slope_icp_band_l0~3[3:0] = 0x00
        ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x00);
        ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x00);

        // reg_sel_div = 0x04
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6));
    }
    else if(usInputPixel <= 1500)
    {
        // reg_slope_icp_band_l0~3[3:0] = 0x00
        ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x00);
        ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x00);

        // reg_sel_div = 0x03
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
    }
    else if(usInputPixel <= 3000)
    {
        if(usInputPixel <= 2000) // 1500~2000
        {
            // reg_slope_icp_band_l0~3[3:0] = 0x00
            ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x00);
            ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x00);
        }
        else // 2000~3000
        {
            // reg_slope_icp_band_l0~3[3:0] = 0x88
            ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x88);
            ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x88);
        }

        // reg_sel_div = 0x02
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5));
    }
    else  // 3000~6000
    {
        if(usInputPixel <= 3400)
        {
            // reg_slope_icp_band_l0~3[3:0] = 0x66
            ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x66);
            ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x66);
        }
        else
        {
            // reg_slope_icp_band_l0~3[3:0] = 0x02
            ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x22);
            ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x22);
        }

        // reg_sel_div = 0x01
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), (_BIT4));
    }

    // reg_vsel_kvco_l0~3=0x01-->Default
    ScalerSetBit_EXINT(P7C_27_BACK_OFFCAL_0A, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5],reg_en_chargeshare_op=0x01-->Default
    ScalerSetBit_EXINT(P7C_08_GDI_DIGI_05, ~(_BIT6), (_BIT6));

    // [5:4],reg_ldo_cp_vsel=0x02
    ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT5 | _BIT4), (_BIT5));

    // [3:0],reg_vsel_ldo=0x05-->Default
    ScalerSetBit_EXINT(P7C_11_GDI_POWR_18, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);

    // [7:6],reg_ldo_res_fb_sel=2'b11-->Default
    ScalerSetBit_EXINT(P7C_11_GDI_POWR_18, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // reg_en_iki_track_l0~3=0x01-->Default
    ScalerSetBit_EXINT(P7C_29_VVI_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [1:0]reg_band_default_l0~3=0x01
    ScalerSetByte_EXINT(P7C_21_BACK_OFFCAL_04, 0x55);

    // reg_enable_divmux = 1;
    ScalerSetBit_EXINT(P7C_23_BACK_OFFCAL_06, ~(_BIT7), _BIT7);

    ucDivNum = ScalerGetBit_EXINT(P7C_07_GDI_ACC_12, (_BIT6 | _BIT5 | _BIT4)) >> 4;
    usVCOfreq = usInputPixel << abs(ucDivNum - 1);

    if(usVCOfreq < 5000)
    {
        // reg_pi_csel = 0x02
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT3 | _BIT2), _BIT3);
    }
    else
    {
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT3 | _BIT2), _BIT2);
    }

    if(usVCOfreq < 5500)
    {
        // [3:2]reg_sel_cco_large_iptat=0x00
        ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT3 | _BIT2), 0x00);
    }
    else
    {
        // [3:2]reg_sel_cco_large_iptat=0x01
        ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT3 | _BIT2), (_BIT2));
    }

    if(usInputPixel <= 2000) // DCDR icp_track=0
    {
        // reg_en_icpkp_track_l0~3=0x00
        ScalerSetBit_EXINT(P7C_29_VVI_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
    else // ACDR
    {
        ScalerSetBit_EXINT(P7C_29_VVI_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    }

    if(usVCOfreq <= 4500)
    {
        // [5]reg_en_cco_lp_mode=1
        ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT5), _BIT5);

        // [1:0]reg_sel_cco_neg_iptat=0x01
        ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT1 | _BIT0), (_BIT0));

        // [7]~[4]reg_kvco_lp_mode_sel_l3~0=0x01
        ScalerSetBit_EXINT(P7C_27_BACK_OFFCAL_0A, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [1:0]reg_vtoi_isel_l0~3=0x00
        ScalerSetByte_EXINT(P7C_2A_VVI_01, 0x00);
    }
    else
    {
        // [5]reg_en_cco_lp_mode =00
        ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT5), 0x00);

        // [1:0]reg_sel_cco_neg_iptat=0x00
        ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT1 | _BIT0), 0x00);

        // [7]~[4]reg_kvco_lp_mode_sel_l3~0=0x00
        ScalerSetBit_EXINT(P7C_27_BACK_OFFCAL_0A, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // [1:0]reg_vtoi_isel_l0~3=0x02
        ScalerSetByte_EXINT(P7C_2A_VVI_01, 0xAA);
    }

    if(usInputPixel <= 2000)
    {
        // reg_sel_icp_kp_ratio_l0~3=0x02
        ScalerSetBit_EXINT(P7C_24_BACK_OFFCAL_07, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1));
        ScalerSetBit_EXINT(P7C_24_BACK_OFFCAL_07, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5));
        ScalerSetBit_EXINT(P7C_23_BACK_OFFCAL_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1));
        ScalerSetBit_EXINT(P7C_23_BACK_OFFCAL_06, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5));
    }
    else
    {
        // reg_sel_icp_kp_ratio_l0~3=0x06
        ScalerSetBit_EXINT(P7C_24_BACK_OFFCAL_07, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        ScalerSetBit_EXINT(P7C_24_BACK_OFFCAL_07, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
        ScalerSetBit_EXINT(P7C_23_BACK_OFFCAL_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        ScalerSetBit_EXINT(P7C_23_BACK_OFFCAL_06, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    }

    if(usInputPixel <= 2000)
    {
        // reg_le_isel = 0x31
        // reg_le_rlsel = 0x01
        // reg_le_rssel = 0x01
        // reg_le_mf_rssel = 0x01
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT4));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT4));
    }
    else if(usInputPixel <= 4000)
    {
        // reg_le_isel = 0x0D
        // reg_le_rlsel = 0x02
        // reg_le_rssel = 0x02
        // reg_le_mf_rssel = 0x02
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5));
    }
    else if(usInputPixel <= 5000)
    {
        // reg_le_isel = 0x07
        // reg_le_rlsel = 0x03
        // reg_le_rssel = 0x04
        // reg_le_mf_rssel = 0x03
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
    }
    else
    {
        // reg_le_isel = 0x04
        // reg_le_rlsel = 0x04
        // reg_le_rssel = 0x05
        // reg_le_mf_rssel = 0x04
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6));
    }

    if(usInputPixel <= 2000) // DCDR
    {
        if(usInputPixel <= 375)
        {
            // [3:2]reg_large_kvco = 0x01
            ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));
        }
        else
        {
            // [3:2]reg_large_kvco = 0x01
            ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));
        }

        if(usInputPixel <= 1000)
        {
            // [7:6]reg_bbpd_pulse_sel = 2'b01
            ScalerSetBit_EXINT(P7C_06_GDI_ACC_09, ~(_BIT7 | _BIT6), (_BIT6));
        }
        else  // 1000~2000
        {
            // [7:6]reg_bbpd_pulse_sel = 2'b01
            ScalerSetBit_EXINT(P7C_06_GDI_ACC_09, ~(_BIT7 | _BIT6), (_BIT6));
        }
    }
    else if(usInputPixel <= 3000) // 2000~3000
    {
        if(usInputPixel <= 2250)
        {
            // [3:2]reg_large_kvco = 0x01
            ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));
        }
        else // 2250~3000
        {
            // [3:2]reg_large_kvco = 0x01
            ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));
        }

        // [7:6]reg_bbpd_pulse_sel = 2'b11
        ScalerSetBit_EXINT(P7C_06_GDI_ACC_09, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else if(usInputPixel <= 3400) // 3000~3400
    {
        // [3:2]reg_large_kvco = 0x01
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));

        // [7:6]reg_bbpd_pulse_sel = 2'b11
        ScalerSetBit_EXINT(P7C_06_GDI_ACC_09, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else if(usInputPixel <= 4000)
    {
        // [3:2]reg_large_kvco = 0x01
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));

        // [7:6]reg_bbpd_pulse_sel = 2'b01
        ScalerSetBit_EXINT(P7C_06_GDI_ACC_09, ~(_BIT7 | _BIT6), (_BIT6));
    }
    else if(usInputPixel <= 4500)
    {
        // [3:2]reg_large_kvco = 0x01
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));

        // [7:6]reg_bbpd_pulse_sel = 2'b01
        ScalerSetBit_EXINT(P7C_06_GDI_ACC_09, ~(_BIT7 | _BIT6), _BIT6);
    }
    else  // 4500~6000
    {
        // [3:2]reg_large_kvco = 0x01
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));

        // [7:6]reg_bbpd_pulse_sel = 2'b01
        ScalerSetBit_EXINT(P7C_06_GDI_ACC_09, ~(_BIT7 | _BIT6), (_BIT6));
    }

    // reg_tap_en = 0x0F
    ScalerSetBit_EXINT(P7C_0A_GDI_DIGI_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_tap0_sumamp = 0x00
    ScalerSetBit_EXINT(P7C_16_GDI_CTRL1, ~(_BIT7 | _BIT6 | _BIT5), (0x00));

    // reg_vcm_tune = 0x02
    ScalerSetBit_EXINT(P7C_0A_GDI_DIGI_10, ~(_BIT5 | _BIT4), (_BIT5));

    // [7]reg_b_dig_rst_n = 0x01
    // [6]reg_g_dig_rst_n = 0x01
    // [5]reg_r_dig_rst_n = 0x01
    // [4]reg_ck_dig_rst_n = 0x01
    // [3:0]cde_rst_n = 0x0F
    ScalerSetByte_EXINT(P1D_10_GDI_TEMP_00, 0xFF);

    // [7:5]reg_inbuf_num_l0~3=010-->FIFO space number
    // [4:3]reg_format_sel_l0~3=00-->bits mode=10bit
    // [2]reg_fifo_en_l0~3=1-->Enable fifo
    // [1]reg_dfe_data_en_l0~3=1-->Data for DFE ready
    ScalerSetByte_EXINT(P1D_F8_DATA_PATH_12, 0x46);
    ScalerSetByte_EXINT(P1D_F9_DATA_PATH_13, 0x46);
    ScalerSetByte_EXINT(P1D_FA_DATA_PATH_14, 0x46);
    ScalerSetByte_EXINT(P1D_FB_DATA_PATH_15, 0x46);

    // [7]reg_cp_en_manual = 0x01 -> close loop
    ScalerSetBit_EXINT(P1D_1F_ANA_CDR_05, ~(_BIT7), (_BIT7));

    // reg_auto_mode = 0x0F -->Auto FLD KBand
    ScalerSetBit_EXINT(P1D_B0_DP_FLD_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // reg_enhance_alltap = 0x01
    ScalerSetBit_EXINT(P7C_17_GDI_CTRL2, ~(_BIT5 | _BIT4), _BIT4);

    if(ScalerGetBit_EXINT(P7C_0F_GDI_DCDR_04, (_BIT0)) == (_BIT0))    // DCDR
    {
        // reg_band_out_mode[1:0] = 0x02
        ScalerSetBit_EXINT(P1D_E0_U3_FLD_40, ~(_BIT1 | _BIT0), 0x02);
    }
    else
    {
        // reg_band_out_mode[1:0] = 0x00
        ScalerSetBit_EXINT(P1D_E0_U3_FLD_40, ~(_BIT1 | _BIT0), 0x00);
    }

    // reg_rx_en = 0x0F
    // reg_cdr_en = 0x01 --> 0x03  --> 0x07
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // N.F code
    if(ScalerGetBit_EXINT(P7C_0F_GDI_DCDR_04, (_BIT0)) == (_BIT0))    // DCDR
    {
        // reg_ssc_bypass_pi_l0~3=1
        ScalerSetBit_EXINT(P1D_80_CMU_SSC_0, ~(_BIT0), _BIT0);
        ScalerSetBit_EXINT(P1D_87_CMU_SSC_7, ~(_BIT0), _BIT0);
        ScalerSetBit_EXINT(P1D_90_CMU_SSC_14, ~(_BIT0), _BIT0);
        ScalerSetBit_EXINT(P1D_97_CMU_SSC_21, ~(_BIT0), _BIT0);

        // reg_fcode_l0~2=0([12:8]default=0)
        ScalerSetByte_EXINT(P1D_85_CMU_SSC_5, 0x00);
        ScalerSetByte_EXINT(P1D_8C_CMU_SSC_12, 0x00);
        ScalerSetByte_EXINT(P1D_95_CMU_SSC_19, 0x00);

        // n.f code setting
        // VCO_FREQ = 6000 = 27 * [2*(N+4)]=ref_clk*[loop_divn]
        if(usInputPixel <= 375)
        {
            // reg_cmu_selprediv=0x00 -->Default
            ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT5 | _BIT4), 0x00);

            // reg_ncode_l0~2[7:0] = 0x4C
            ScalerSetByte_EXINT(P1D_86_CMU_SSC_6, 0x4C);
            ScalerSetByte_EXINT(P1D_8D_CMU_SSC_13, 0x4C);
            ScalerSetByte_EXINT(P1D_96_CMU_SSC_20, 0x4C);
        }
        else if(usInputPixel <= 750)
        {
            // reg_cmu_selprediv=0x00 -->Default
            ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT5 | _BIT4), 0x00);

            // reg_ncode_l0~2[7:0] = 0x24
            ScalerSetByte_EXINT(P1D_86_CMU_SSC_6, 0x24);
            ScalerSetByte_EXINT(P1D_8D_CMU_SSC_13, 0x24);
            ScalerSetByte_EXINT(P1D_96_CMU_SSC_20, 0x24);
        }
        else if(usInputPixel <= 1500)
        {
            // reg_cmu_selprediv=0x00 -->Default
            ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT5 | _BIT4), 0x00);

            // reg_ncode_l0~2[7:0] = 0x10
            ScalerSetByte_EXINT(P1D_86_CMU_SSC_6, 0x10);
            ScalerSetByte_EXINT(P1D_8D_CMU_SSC_13, 0x10);
            ScalerSetByte_EXINT(P1D_96_CMU_SSC_20, 0x10);
        }
        else
        {
            // reg_cmu_selprediv=0x01
            ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT5 | _BIT4), (_BIT4));

            // reg_ncode_l0~2[7:0] = 0x10
            ScalerSetByte_EXINT(P1D_86_CMU_SSC_6, 0x10);
            ScalerSetByte_EXINT(P1D_8D_CMU_SSC_13, 0x10);
            ScalerSetByte_EXINT(P1D_96_CMU_SSC_20, 0x10);
        }

        // reg_cdr_rst_n = 0x0F --> 0x00 --> 0x0F
        ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        // reg_cdr_rst_n = 0x00
        ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }


    /////////////////
    // DFE Initial //
    /////////////////
    ScalerTmdsPhyRx3SetDFEInitial_EXINT0();

    // reg_sel_foreoff_autok = 0x7F
    ScalerSetBit_EXINT(P1D_12_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_offk_pc_l0~3 = 0x01
    ScalerSetBit_EXINT(P1D_13_ADJR_01, ~(_BIT7), (_BIT7));
    ScalerSetBit_EXINT(P1D_13_ADJR_01, ~(_BIT6), (_BIT6));
    ScalerSetBit_EXINT(P1D_14_ADJR_02, ~(_BIT7), (_BIT7));
    ScalerSetBit_EXINT(P1D_14_ADJR_02, ~(_BIT6), (_BIT6));

    // reg_rstb_fore_offset[3][2:0] = 1 --> 0 --> 1
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), (_BIT5));
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), 0x00);
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), (_BIT5));
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // reg_sel_fore_off = 0x06 --> Debug out leq code for K offset
    ScalerSetBit_EXINT(P1D_11_DPHY_DEBUG, ~(_BIT2 | _BIT1 | _BIT0), 0x06);

    // Delay Time Waiting for K Offset
    for(ucOffsetOK = 0; ucOffsetOK <= 50; ucOffsetOK++)
    {
        if((ScalerGetBit_EXINT(P1D_17_FORE_OFF_TST_L0, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_18_FORE_OFF_TST_L1, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_19_FORE_OFF_TST_L2, _BIT7) == _BIT7))
        {
            break;
        }
        DELAY_10US_EXINT();
    }

    DELAY_45US_EXINT();

    /////////////////////
    // FLD Ref Counter //
    /////////////////////

    // reg_init_time = 0x01
    ScalerSetBit_EXINT(P1D_C0_U3_FLD_16, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

    // reg_fld_mode_l0~3 = 0x00 ->Kband--> First K
    ScalerSetBit_EXINT(P1D_20_FLD_KICO_L0_A00, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_24_FLD_KICO_L1_A00, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_28_FLD_KICO_L2_A00, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_2C_FLD_KICO_L3_A00, ~(_BIT7 | _BIT6), 0x00);

    // FLD Band Estimate
    usFLDBand = abs(((WORD)(usInputPixel << ucDivNum) / 20) - 290);

    if(g_usTmdsPhyRx3ExDataRate != usInputPixel)
    {
        // FLD Band Estimate
        if(usVCOfreq < 4500)
        {// low power mode
            usFLDBand = abs((usVCOfreq / 11) - 112);
        }
        else
        {// normal mode
            usFLDBand = abs((usVCOfreq / 19) - 112);
        }

        // reg_coarse_fsm_lx[8][7:0] = usFLDBand
        if(usFLDBand >= 0x100)
        {
            ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        }
        else
        {
            ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
        ScalerSetByte_EXINT(P1D_D9_U3_FLD_36, (usFLDBand & 0x00FF));
        ScalerSetByte_EXINT(P1D_DA_U3_FLD_37, (usFLDBand & 0x00FF));
        ScalerSetByte_EXINT(P1D_DB_U3_FLD_38, (usFLDBand & 0x00FF));
        ScalerSetByte_EXINT(P1D_DC_U3_FLD_39, (usFLDBand & 0x00FF));

        g_usTmdsPhyRx3ExDataRate = usInputPixel;
    }

    // First K fld//
    // FLD_CLK=VCO_FREQ/16
    // VCO_FREQ only 3G~6G
    // Counter = div_num * 2 *FLD_CLK / ref_clk
    // VCO_FREQ=Counter/div_num/2*16*ref_clk
    // Counter/div_num=VCO_FREQ/16*2/ref_clk
    if(usInputPixel <= 375) // 1:10
    {
        // taget ref_clk 25Mhz-> VCO_Freq 6000MHz
        // reg_cdr_divide_num[11:8] = 0x00 , [7:0] = 0x10
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x10);

        // reg_cdr_lock_dn_limit[11:8] = 0x01 , reg_cdr_lock_dn_limit[7:0] = 0x40
        // reg_cdr_lock_up_limit[11:8] = 0x01  ,  reg_cdr_lock_up_limit[7:0] = 0x40
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT4));
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x40);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x40);
    }
    else if(usInputPixel <= 750) // 1:10
    {
        // reg_cdr_divide_num[11:8] = 0x00 , [7:0] = 0x10
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x10);

        // reg_cdr_lock_dn_limit[11:8] = 0x00 , reg_cdr_lock_dn_limit[7:0] = 0xA0
        // reg_cdr_lock_up_limit[11:8] = 0x00  ,  reg_cdr_lock_up_limit[7:0] = 0xA0
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0xA0);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0xA0);
    }
    else if(usInputPixel <= 1500) // 1:10
    {
        // reg_cdr_divide_num[11:8] = 0x00 , [7:0] = 0x20
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x20);

        // reg_cdr_lock_dn_limit[11:8] = 0x00 , reg_cdr_lock_dn_limit[7:0] = 0xA0
        // reg_cdr_lock_up_limit[11:8] = 0x00 , reg_cdr_lock_up_limit[7:0] = 0xA0
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0xA0);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0xA0);
    }
    else if(usInputPixel <= 3000) // 1:10
    {
        // reg_cdr_divide_num[11:8] = 0x00 , [7:0] = 0x28
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x28);

        // reg_cdr_lock_dn_limit[11:8] = 0x00 , reg_cdr_lock_dn_limit[7:0] = 0x64
        // reg_cdr_lock_up_limit[11:8] = 0x00  ,  reg_cdr_lock_up_limit[7:0] = 0x64
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x64);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x64);
    }
    else if(usInputPixel <= 3400) // 1:10
    {
        // reg_cdr_divide_num[11:8] = 0x00 , [7:0] = 0x50
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x50);

        // reg_cdr_lock_dn_limit[11:8] = 0x00 , reg_cdr_lock_dn_limit[7:0] = 0x64
        // reg_cdr_lock_up_limit[11:8] = 0x00  ,  reg_cdr_lock_up_limit[7:0] = 0x64
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x64);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x64);
    }
    else // 1:40
    {
#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX3_HIGH_SPEED_MODE() == _FALSE)
        {
            // reg_cdr_divide_num[11:8] = 0x00 , [7:0] = 0x50
            ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x50);

            // reg_cdr_lock_dn_limit[11:8] = 0x00 , reg_cdr_lock_dn_limit[7:0] = 0x64
            // reg_cdr_lock_up_limit[11:8] = 0x00  ,  reg_cdr_lock_up_limit[7:0] = 0x64
            ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x64);
            ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x64);
        }
        else
#endif
        {
            // reg_cdr_divide_num[11:8] = 0x00 , [7:0] = 0x20
            ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x20);

            // reg_cdr_lock_dn_limit[11:8] = 0x00, reg_cdr_lock_dn_limit[7:0] = 0xA0
            // reg_cdr_lock_up_limit[11:8] = 0x00, reg_cdr_lock_up_limit[7:0] = 0xA0
            ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0xA0);
            ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0xA0);

            // reg_sel_clklane_div4=0x01;
            ScalerSetBit_EXINT(P7C_0C_GDI_DCDR_01, ~_BIT4, _BIT4);
        }
    }

    // reg_rstb_fsm[3][2:0] = 0x00 --> 0x0F
    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), 0x00);

    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), (_BIT7));

    // Delay Time Waiting for FLD Kband
    for(ucFldOK = 0; ucFldOK <= 100; ucFldOK++)
    {
        if((ScalerGetBit_EXINT(P1D_D0_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
           (ScalerGetBit_EXINT(P1D_D1_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
           (ScalerGetBit_EXINT(P1D_D2_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
        {
            break;
        }
        DELAY_10US_EXINT();
    }

    ScalerSetByte_EXINT(P7C_18_OOBS_00, ucFldOK); // get fld waiting time

    // Record FLD Band to ManuMode
    // reg_vco_coarse_lx = reg_coarse_fsm_lx
    ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetBit_EXINT(P1D_D8_U3_FLD_35, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    ScalerSetByte_EXINT(P1D_D9_U3_FLD_36, ScalerGetByte_EXINT(P1D_D4_DP_FLD_31));
    ScalerSetByte_EXINT(P1D_DA_U3_FLD_37, ScalerGetByte_EXINT(P1D_D5_DP_FLD_32));
    ScalerSetByte_EXINT(P1D_DB_U3_FLD_38, ScalerGetByte_EXINT(P1D_D6_DP_FLD_33));
    ScalerSetByte_EXINT(P1D_DC_U3_FLD_39, ScalerGetByte_EXINT(P1D_D7_DP_FLD_34));

    // reg_fld_mode_l0~3 = 0x01 ->Kband+VCO
    ScalerSetBit_EXINT(P1D_20_FLD_KICO_L0_A00, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit_EXINT(P1D_24_FLD_KICO_L1_A00, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit_EXINT(P1D_28_FLD_KICO_L2_A00, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit_EXINT(P1D_2C_FLD_KICO_L3_A00, ~(_BIT7 | _BIT6), _BIT6);

    // ------Second K fld------//
    // FLD_CLK=VCO_FREQ/16
    // VCO_FREQ only 3G~6G
    // Counter = div_num * 2 *FLD_CLK / ref_clk
    // VCO_FREQ=Counter/div_num/2*16*ref_clk
    // Counter/div_num=VCO_FREQ/16*2/ref_clk
    if(usInputPixel <= 375) // 1:10
    {
        // taget ref_clk 25Mhz-> VCO_Freq 6000MHz
        // 3200 = 160 * 2 * (6000 / 16) / 37.5 = 0xC80
        // reg_cdr_divide_num[11:8] = 0x00 , [7:0] = 0xA0
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0xA0);

        // reg_cdr_lock_dn_limit[11:8] = 0x0C , reg_cdr_lock_dn_limit[7:0] = 0x80
        // reg_cdr_lock_up_limit[11:8] = 0x0C  ,  reg_cdr_lock_up_limit[7:0] = 0x80
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x80);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x80);
    }
    else if(usInputPixel <= 750) // 1:10
    {
        // 1600 = 160 * 2 * (6000 / 16) / 75 =0x640
        // reg_cdr_divide_num[11:8] = 0x01 , [7:0] = 0x40
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0xA0);

        // reg_cdr_lock_dn_limit[11:8] = 0x06 , reg_cdr_lock_dn_limit[7:0] = 0x40
        // reg_cdr_lock_up_limit[11:8] = 0x06  ,  reg_cdr_lock_up_limit[7:0] = 0x40
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x40);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x40);
    }
    else if(usInputPixel <= 1500) // 1:10
    {
        // 1600 = 320 * 2 * (6000 / 16) / 150 =0x640
        // reg_cdr_divide_num[11:8] = 0x01 , [7:0] = 0x40
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x40);

        // reg_cdr_lock_dn_limit[11:8] = 0x06 , reg_cdr_lock_dn_limit[7:0] = 0x40
        // reg_cdr_lock_up_limit[11:8] = 0x06  ,  reg_cdr_lock_up_limit[7:0] = 0x40
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x40);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x40);
    }
    else if(usInputPixel <= 3000) // 1:10
    {
        // 1000 = 400 * 2 * (6000 / 16) / 300 =0x3E8
        // reg_cdr_divide_num[11:8] = 0x01 , [7:0] = 0x90
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x90);

        // reg_cdr_lock_dn_limit[11:8] = 0x03 , reg_cdr_lock_dn_limit[7:0] = 0xE8
        // reg_cdr_lock_up_limit[11:8] = 0x03  ,  reg_cdr_lock_up_limit[7:0] = 0xE8
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0xE8);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0xE8);
    }
    else if(usInputPixel <= 3400) // 1:10
    {
        // 1000 = 800 * 2 * (3400 / 16) / 340 =0x3E8
        // reg_cdr_divide_num[11:8] = 0x03 , [7:0] = 0x20
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x03);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x20);

        // reg_cdr_lock_dn_limit[11:8] = 0x03 , reg_cdr_lock_dn_limit[7:0] = 0xE8
        // reg_cdr_lock_up_limit[11:8] = 0x03  ,  reg_cdr_lock_up_limit[7:0] = 0xE8
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0xE8);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0xE8);
    }
    else // 1:40
    {
        // reg_cdr_divide_num[11:8] = 0x01 , [7:0] = 0xE0 --> d'480
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);
        ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0xE0);

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
        if(GET_TMDS_MAC_RX3_HIGH_SPEED_MODE() == _FALSE)
        {
            // 600 = 480 * 2 * (6000 / 16) / 600 =0x258 1:10
            // reg_cdr_lock_dn_limit[11:8] = 0x02 , reg_cdr_lock_dn_limit[7:0] = 0x58
            // reg_cdr_lock_up_limit[11:8] = 0x02  ,  reg_cdr_lock_up_limit[7:0] = 0x60
            ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5));
            ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x58);
            ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x58);

            // reg_sel_clklane_div4=0x00;
            ScalerSetBit_EXINT(P7C_0C_GDI_DCDR_01, ~_BIT4, 0x00);
        }
        else
#endif
        {
            // 2400 = 480 * 2 * (6000 / 16) / 150 =0x960 1:40
            // reg_cdr_lock_dn_limit[11:8] = 0x09 , reg_cdr_lock_dn_limit[7:0] = 0x60
            // reg_cdr_lock_up_limit[11:8] = 0x09  ,  reg_cdr_lock_up_limit[7:0] = 0x60
            ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));
            ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x60);
            ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));
            ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x60);

            // reg_sel_clklane_div4=0x01;
            ScalerSetBit_EXINT(P7C_0C_GDI_DCDR_01, ~_BIT4, _BIT4);
        }
    }

    ////////////////
    // KVCO CALI. //
    ////////////////

    // KVCO_Target = 1000=220/0.2
    // FLD_CLK=VCO_FREQ/FLD_Freq_div
    // FLD_Freq_div = 16
    // VCO_FREQ only 3000~6000MHz
    // HV/LV Voltage Difference = 0.1V
    // HV_Freq_Diff = FLD_CLK + KVCO_Target*HV_Voltagediff/Fld_freq_div
    // LV_Freq_Diff = FLD_CLK - KVCO_Target*HV_Voltagediff/Fld_freq_div
    // *16 at freq_diff caculate and then /16 at slope_hv
    // slope_hv = cdr_div_num*2*HV_Freq_Diff/ref_clk
    // slope_lv = cdr_div_num*2*LV_Freq_Diff/ref_clk
    // cdr_div_num = (ScalerGetByte_EXINT(P1D_BE_U3_FLD_14)&0x0F)<<8 | ScalerGetByte_EXINT(P1D_BF_U3_FLD_15);
    // ucDivNum in hdmi20 ~6G must >=1
    ucDivNum = abs(ucDivNum - 1);
    usHVDiff = ((WORD)(usInputPixel << ucDivNum) + 1000 / 10);
    usLVDiff = ((WORD)(usInputPixel << ucDivNum) - 1000 / 10);

#if(_HDMI20_MAC_RX3_SUPPORT == _ON)
    if(GET_TMDS_MAC_RX3_HIGH_SPEED_MODE() == _FALSE)
    {
        // usRefClk = usInputPixel/10;
        ulSlopeHV = (DWORD)((ScalerGetByte_EXINT(P1D_BE_U3_FLD_14) & 0x0F) << 8 | ScalerGetByte_EXINT(P1D_BF_U3_FLD_15)) * 2 * usHVDiff / 16;
        ulSlopeLV = (DWORD)((ScalerGetByte_EXINT(P1D_BE_U3_FLD_14) & 0x0F) << 8 | ScalerGetByte_EXINT(P1D_BF_U3_FLD_15)) * 2 * usLVDiff / 16;
        ulSlopeHV = ulSlopeHV * 10 / usInputPixel;
        ulSlopeLV = ulSlopeLV * 10 / usInputPixel;
    }
    else
#endif
    {
        // usRefClk = usInputPixel/40;
        ulSlopeHV = (DWORD)((ScalerGetByte_EXINT(P1D_BE_U3_FLD_14) & 0x0F) << 8 | ScalerGetByte_EXINT(P1D_BF_U3_FLD_15)) * 2 * usHVDiff / 16;
        ulSlopeLV = (DWORD)((ScalerGetByte_EXINT(P1D_BE_U3_FLD_14) & 0x0F) << 8 | ScalerGetByte_EXINT(P1D_BF_U3_FLD_15)) * 2 * usLVDiff / 16;
        ulSlopeHV = ulSlopeHV * 40 / usInputPixel;
        ulSlopeLV = ulSlopeLV * 40 / usInputPixel;
    }

    // reg_slope_hv_up = reg_slope_hv_dn = ulSlopeHV
    ScalerSetBit_EXINT(P1D_B7_U3_FLD_7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F & HIBYTE(LOWORD(ulSlopeHV)));
    ScalerSetBit_EXINT(P1D_B9_U3_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F & HIBYTE(LOWORD(ulSlopeHV)));
    ScalerSetByte_EXINT(P1D_B6_U3_FLD_6, LOBYTE(LOWORD(ulSlopeHV)));
    ScalerSetByte_EXINT(P1D_B8_U3_FLD_8, LOBYTE(LOWORD(ulSlopeHV)));

    // reg_slope_lv_up = reg_slope_lv_dn = ulSlopeHV
    ScalerSetBit_EXINT(P1D_B3_U3_FLD_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F & HIBYTE(LOWORD(ulSlopeLV)));
    ScalerSetBit_EXINT(P1D_B5_U3_FLD_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F & HIBYTE(LOWORD(ulSlopeLV)));
    ScalerSetByte_EXINT(P1D_B2_U3_FLD_2, LOBYTE(LOWORD(ulSlopeLV)));
    ScalerSetByte_EXINT(P1D_B4_U3_FLD_4, LOBYTE(LOWORD(ulSlopeLV)));


    ///////////////
    // FLD Reset //
    ///////////////

    // reg_rstb_fsm[3][2:0] = 0x00 --> 0x0F
    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), 0x00);

    if(usInputPixel <= 375) // TMDS Clock < 375
    {
        // Disable Adaptation Loop  0x000
        ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0x00);
    }
    else if(usInputPixel <= 1000)// 375~1000
    {
        // Enable the Vth, Tap0~1 Adaptation Loop 0x043
        ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0x43);
        ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0x43);
        ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0x43);
    }
    else if(usInputPixel <= 2000)
    {
        // Enable the LE, Vth, Tap0~1 Adaptation Loop 0x0C3
        ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0xC3);
    }
    else
    {
        // Enable LE, Vth, Tap0~4 Adaptation
        ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0xDF);
    }

    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), (_BIT7));

    // Delay Time Waiting for FLD Kband
    for(ucFldOK = 0; ucFldOK <= 200; ucFldOK++)
    {
        if((ScalerGetBit_EXINT(P1D_D0_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
           (ScalerGetBit_EXINT(P1D_D1_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
           (ScalerGetBit_EXINT(P1D_D2_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
        {
            break;
        }
        DELAY_10US_EXINT();
    }

    ScalerSetByte_EXINT(P7C_19_OOBS_01, ucFldOK); // get fld waiting time

    // Waiting for DFE Adaptation
    DELAY_XUS_EXINT(250);

    ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_D1_L3_DFE_EN_2, 0x00);

    // Record kvcoslope to ManuMode
    // reg_slope_band_lx = reg_coarse_fsm_lx
    ScalerSetBit_EXINT(P1D_E1_U3_FLD_41, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ScalerGetBit_EXINT(P1D_B3_U3_FLD_3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)));
    ScalerSetBit_EXINT(P1D_E1_U3_FLD_41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetBit_EXINT(P1D_B5_U3_FLD_5, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    ScalerSetBit_EXINT(P1D_E2_U3_FLD_42, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ScalerGetBit_EXINT(P1D_B7_U3_FLD_7, (_BIT7 | _BIT6 | _BIT5 | _BIT4)));
    ScalerSetBit_EXINT(P1D_E2_U3_FLD_42, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetBit_EXINT(P1D_B9_U3_FLD_9, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

    // Record FLD Band to ManuMode
    // reg_vco_coarse_lx = reg_coarse_fsm_lx
    ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetBit_EXINT(P1D_D8_U3_FLD_35, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    ScalerSetByte_EXINT(P1D_D9_U3_FLD_36, ScalerGetByte_EXINT(P1D_D4_DP_FLD_31));
    ScalerSetByte_EXINT(P1D_DA_U3_FLD_37, ScalerGetByte_EXINT(P1D_D5_DP_FLD_32));
    ScalerSetByte_EXINT(P1D_DB_U3_FLD_38, ScalerGetByte_EXINT(P1D_D6_DP_FLD_33));
    ScalerSetByte_EXINT(P1D_DC_U3_FLD_39, ScalerGetByte_EXINT(P1D_D7_DP_FLD_34));


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte_EXINT(P1D_17_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P7C_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1D_17_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P7C_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte_EXINT(P1D_18_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P7C_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1D_18_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P7C_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte_EXINT(P1D_19_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P7C_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1D_19_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P7C_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0x20);
    ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0x20);
    ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0x20);
    ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0x00);

    // reg_auto_mode = 0x00 -->Manu FLD KBand
    ScalerSetBit_EXINT(P1D_B0_DP_FLD_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [7]reg_cp_en_manual = 0x00 -> open loop
    ScalerSetBit_EXINT(P1D_1F_ANA_CDR_05, ~(_BIT7), 0x00);

    // reg_rstb_fore_offset[3][2:0] = 0 --> 1
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), 0x00);
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), (_BIT5));
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time Waiting for K Offset
    for(ucOffsetOK = 0; ucOffsetOK <= 50; ucOffsetOK++)
    {
        if((ScalerGetBit_EXINT(P1D_17_FORE_OFF_TST_L0, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_18_FORE_OFF_TST_L1, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_19_FORE_OFF_TST_L2, _BIT7) == _BIT7))
        {
            break;
        }
        DELAY_10US_EXINT();
    }
    DELAY_45US_EXINT();

    // [7]reg_cp_en_manual = 0x01 -> close loop
    ScalerSetBit_EXINT(P1D_1F_ANA_CDR_05, ~(_BIT7), _BIT7);
    DELAY_XUS_EXINT(150);

    // reg_en_offpn_edge_demux = 0x00->Disable offpn mux, set 0 when DFE adapt,offsetK end
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT1), 0x00);

    // reg_fld_reserved[18] = reg_aphy_adp_en_off = 1
    ScalerSetBit_EXINT(P1D_DD_U3_FLD_RES_00, ~(_BIT2), _BIT2);

    // reg_en_fld_div = 0x00 -->FLD K disable
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT3), 0x00);

    // Fifo Reset
    // [7]reg_b_dig_rst_n = 0 -> 1
    // [6]reg_g_dig_rst_n = 0 -> 1
    // [5]reg_r_dig_rst_n = 0 -> 1
    // [4]reg_ck_dig_rst_n = 0 -> 1
    ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
}

#if(_HDMI21_PHY_RX3_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FRL Set PHY Function (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsPhyRx3FrlSetPhy_EXINT0(BYTE ucLane, BYTE ucFRLrate)
{
    BYTE ucOffsetOK = 0;
    BYTE ucFldOK = 0;
    BYTE pucTap0[4];

    // Reset channel fifo & DFE ready bit
    ScalerSetBit_EXINT(P1D_F8_DATA_PATH_12, ~(_BIT2 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P1D_F9_DATA_PATH_13, ~(_BIT2 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P1D_FA_DATA_PATH_14, ~(_BIT2 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P1D_FB_DATA_PATH_15, ~(_BIT2 | _BIT1), 0x00);

    ScalerTmdsPhyRx3Cdr2xClkEnable_EXINT0(_FALSE);

    // reg_init_time = 0x01
    ScalerSetBit_EXINT(P1D_C0_U3_FLD_16, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // [0]reg_en_dcdr = 0x00
    // [4]reg_en_large_rs_for_cmu = 0x00
    // [7:4]reg_config_cmu = 0x00
    // [3:0]reg_cdr_rst_n = 0x00 -->DCDR rst=0
    ScalerSetBit_EXINT(P7C_0F_GDI_DCDR_04, ~(_BIT4 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7:6],reg_cmu_cp=0x00-->Default
    ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT7 | _BIT6), 0x00);

    // [2] reg_en_prclk_to_data=0
    ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT2), 0x00);

    // [7:4]reg_rx_en = 0x0F
    // [3:0]reg_cdr_en = 0x00
    // [4]reg_bg_en = 0x01
    ScalerSetByte_EXINT(P7C_10_GDI_POWR_00, 0xF0);
    ScalerSetBit_EXINT(P7C_02_GDI_TERM_2, ~(_BIT4), (_BIT4));

    // reg_vcckoffb_dv = 0x01
    // reg_en_sigdect = 0x00
    ScalerSetBit_EXINT(P7C_16_GDI_CTRL1, ~(_BIT0), (_BIT0));
    ScalerSetBit_EXINT(P7C_09_GDI_DIGI_11, ~(_BIT0), 0x00);

    // reg_rxvcom_sel = 0x01
    ScalerSetBit_EXINT(P7C_11_GDI_POWR_18, ~(_BIT5 | _BIT4), _BIT4);


    ////////////////////
    // Power Process //
    ////////////////////

    ScalerTmdsPhyRx3SetZ0Status_EXINT0(_ENABLE);

    // [3]reg_p_channel_en = 0x01
    // [2]reg_n_channel_en = 0x01
    ScalerSetByte_EXINT(P7C_2B_CHANNEL_EN_00, 0xFF);

    // reg_en_back_offset = 0x01
    ScalerSetBit_EXINT(P7C_0E_GDI_DCDR_03, ~(_BIT3), _BIT3);

    // reg_en_fore_offset = 0x01
    ScalerSetBit_EXINT(P7C_0F_GDI_DCDR_04, ~(_BIT7), (_BIT7));

    // reg_en_lpf_vco = 0x01
    ScalerSetBit_EXINT(P7C_08_GDI_DIGI_05, ~(_BIT7), _BIT7);

    // reg_vco_lpf_force_en=0x01
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT0), _BIT0);

    // reg_cdr_cp[19:16][15:8][7:0] = 0x07 77 72/4
    ScalerSetBit_EXINT(P1D_C7_U3_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetByte_EXINT(P1D_C6_U3_FLD_22, 0x77);

    if(ucFRLrate == 3)
    {
        ScalerSetByte_EXINT(P1D_C5_U3_FLD_21, 0x72);
    }
    else
    {
        ScalerSetByte_EXINT(P1D_C5_U3_FLD_21, 0x74);
    }

    // reg_cdr_r = 0x30
    ScalerSetBit_EXINT(P1D_CA_U3_FLD_26, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x30);

    // [5:4]reg_ic_sel_l0~3 = 0x01
    ScalerSetBit_EXINT(P1D_20_FLD_KICO_L0_A00, ~(_BIT5 | _BIT4), (_BIT4));
    ScalerSetBit_EXINT(P1D_24_FLD_KICO_L1_A00, ~(_BIT5 | _BIT4), (_BIT4));
    ScalerSetBit_EXINT(P1D_28_FLD_KICO_L2_A00, ~(_BIT5 | _BIT4), (_BIT4));
    ScalerSetBit_EXINT(P1D_2C_FLD_KICO_L3_A00, ~(_BIT5 | _BIT4), (_BIT4));

    // reg_slope_icp_offset_l0~3[24:20]=0x00 -> default
    ScalerSetBit_EXINT(P1D_DD_U3_FLD_RES_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    ScalerSetBit_EXINT(P1D_E0_U3_FLD_40, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
    ScalerSetBit_EXINT(P1D_E3_U3_FLD_RESV_00, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_E4_U3_FLD_RESV_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // reg_slope_icp_offset_l0~3[19:16] = 0x02
    ScalerSetByte_EXINT(P1D_A8_FLD_KICO_B00, 0x22);
    ScalerSetByte_EXINT(P1D_CB_FLD_KICO_B07, 0x22);

    // reg_slope_icp_offset_l0~3[15:8] = 0x22
    ScalerSetByte_EXINT(P1D_A9_FLD_KICO_B01, 0x22);
    ScalerSetByte_EXINT(P1D_AB_FLD_KICO_B03, 0x22);
    ScalerSetByte_EXINT(P1D_CC_FLD_KICO_B08, 0x22);
    ScalerSetByte_EXINT(P1D_CE_FLD_KICO_B10, 0x22);

    // reg_slope_icp_offset_l0~3[7:0] = 0x20
    ScalerSetByte_EXINT(P1D_AA_FLD_KICO_B02, 0x20);
    ScalerSetByte_EXINT(P1D_AC_FLD_KICO_B04, 0x20);
    ScalerSetByte_EXINT(P1D_CD_FLD_KICO_B09, 0x20);
    ScalerSetByte_EXINT(P1D_CF_FLD_KICO_B11, 0x20);

    if((ucFRLrate == 3) || (ucFRLrate == 8))
    {
        // reg_slope_icp_band_l0~3[3:0] = 0x02
        ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x22);
        ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x22);
    }
    else
    {
        // reg_slope_icp_band_l0~3[3:0] = 0x04
        ScalerSetByte_EXINT(P1D_AD_FLD_KICO_B05, 0x44);
        ScalerSetByte_EXINT(P1D_AE_FLD_KICO_B06, 0x44);
    }

    // reg_slope_band_l0~3[3:0] = 0x09
    ScalerSetByte_EXINT(P1D_E1_U3_FLD_41, 0x99);
    ScalerSetByte_EXINT(P1D_E2_U3_FLD_42, 0x99);

    // reg_sel_large_icp_kp = 0x00-->Default
    ScalerSetBit_EXINT(P7C_16_GDI_CTRL1, ~(_BIT3), 0x00);

    // reg_vsel_kvco_l0~3=0x01-->Default
    ScalerSetBit_EXINT(P7C_27_BACK_OFFCAL_0A, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5],reg_en_chargeshare_op=0x01-->Default
    ScalerSetBit_EXINT(P7C_08_GDI_DIGI_05, ~(_BIT6), (_BIT6));

    // [5:4],reg_ldo_cp_vsel=0x02
    ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT5 | _BIT4), (_BIT5));

    // [3:0],reg_vsel_ldo=0x05-->Default
    ScalerSetBit_EXINT(P7C_11_GDI_POWR_18, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);

    // [7:6],reg_ldo_res_fb_sel=2'b11-->Default
    ScalerSetBit_EXINT(P7C_11_GDI_POWR_18, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // reg_en_iki_track_l0~3=0x01-->Default
    ScalerSetBit_EXINT(P7C_29_VVI_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [1:0]reg_band_default_l0~3=0x01
    ScalerSetByte_EXINT(P7C_21_BACK_OFFCAL_04, 0x55);


    ////////////
    // SETPHY //
    ////////////

    // reg_sel_clklane_div4 = 0x01
    ScalerSetBit_EXINT(P7C_0C_GDI_DCDR_01, ~(_BIT4), (_BIT4));

    ScalerTmdsPhyRx3FRLPathSel_EXINT0(1);

    // reg_acdr_en = 0x01
    // reg_rstb_fsm[3][2:0] = 0x00
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT0), (_BIT0));
    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), 0x00);

    // [4]reg_en_op_cp_kp_path = 0x01
    // [3]reg_en_cp_kp_path = 0x01
    ScalerSetBit_EXINT(P7C_14_GDI_FEEDBACK_RES, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

    // [4]reg_en_cpkp_mirror_path = 0x01
    // [2]reg_en_large_icp = 0x00 ->Default
    // [1]reg_en_offpn_edge_demux = 0x01->Enable offpn mux, set 0 when DFE adapt,offsetK end
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT4 | _BIT2 | _BIT1), (_BIT4 | _BIT1));

    // reg_cdr_direct_l0~3=0x01 -->Default
    ScalerSetBit_EXINT(P7C_22_BACK_OFFCAL_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // reg_fld_reserved[18] = reg_aphy_adp_en_off = 0
    ScalerSetBit_EXINT(P1D_DD_U3_FLD_RES_00, ~(_BIT2), 0x00);

    // reg_en_fld_div = 0x01
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT3), _BIT3);

    // reg_pi_ibsel = 0x01
    ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

    // reg_enable_pr = 0x00 ->Default
    ScalerSetBit_EXINT(P7C_0D_GDI_DCDR_02, ~(_BIT1), 0x00);

    // reg_bypass_cdr_dec = 2'b01 ->Default
    ScalerSetBit_EXINT(P7C_0B_GDI_DIGI_13, ~(_BIT5 | _BIT4), (_BIT4));

    // reg_bypass_div5_cdrdec[1:1] = 0x00 ->Default
    ScalerSetBit_EXINT(P1D_50_DCDR_00, ~(_BIT3), 0x00);

    // reg_bypass_div5_cdrdec[0:0] = 0x00->Default
    ScalerSetBit_EXINT(P1D_52_DCDR_02, ~(_BIT3), 0x00);

    // reg_enable_divmux = 1;
    ScalerSetBit_EXINT(P7C_23_BACK_OFFCAL_06, ~(_BIT7), _BIT7);

    // reg_en_icpkp_track_l0~3=0x01 -->Default
    ScalerSetBit_EXINT(P7C_29_VVI_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // reg_sel_icp_kp_ratio_l0~3=0x06
    ScalerSetBit_EXINT(P7C_24_BACK_OFFCAL_07, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(P7C_24_BACK_OFFCAL_07, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7C_23_BACK_OFFCAL_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit_EXINT(P7C_23_BACK_OFFCAL_06, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    // [3:2]reg_large_kvco = 0x01
    ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT3 | _BIT2), (_BIT2));

    if(ucFRLrate == 8)
    {
        // [5]reg_en_cco_lp_mode=1
        ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT5), _BIT5);

        // [1:0]reg_sel_cco_neg_iptat=0x01
        ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT1 | _BIT0), (_BIT0));

        // [7]~[4]reg_kvco_lp_mode_sel_l3~0=0x01
        ScalerSetBit_EXINT(P7C_27_BACK_OFFCAL_0A, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [1:0]reg_vtoi_isel_l0~3=0x00
        ScalerSetByte_EXINT(P7C_2A_VVI_01, 0x00);
    }
    else
    {
        // [5]reg_en_cco_lp_mode=0
        ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT5), 0x00);

        // [1:0]reg_sel_cco_neg_iptat=0x00
        ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT1 | _BIT0), 0x00);

        // [7]~[4]reg_kvco_lp_mode_sel_l3~0=0x00
        ScalerSetBit_EXINT(P7C_27_BACK_OFFCAL_0A, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // [1:0]reg_vtoi_isel_l0~3=0x02
        ScalerSetByte_EXINT(P7C_2A_VVI_01, 0xAA);
    }

    if((ucFRLrate == 8) || (ucFRLrate == 10))
    {
        // [3:2]reg_sel_cco_large_iptat=0x00
        ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT3 | _BIT2), 0x00);
    }
    else
    {
        // [3:2]reg_sel_cco_large_iptat=0x01
        ScalerSetBit_EXINT(P7C_26_BACK_OFFCAL_09, ~(_BIT3 | _BIT2), (_BIT2));
    }

    if(ucFRLrate == 3)
    {
        // reg_sel_div = 0x02
        // reg_pi_csel = 0x01
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5));
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT3 | _BIT2), (_BIT2));

        // reg_le_isel = 0x0D
        // reg_le_rlsel = 0x02
        // reg_le_rssel = 0x02
        // reg_le_mf_rssel = 0x02
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5));
    }
    else if(ucFRLrate == 6)
    {
        // reg_sel_div = 0x01
        // reg_pi_csel = 0x01
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), (_BIT4));
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT3 | _BIT2), _BIT2);

        // reg_le_isel = 0x04
        // reg_le_rlsel = 0x04
        // reg_le_rssel = 0x05
        // reg_le_mf_rssel = 0x04
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6));
    }
    else if(ucFRLrate == 8)
    {
        // reg_sel_div = 0x00
        // reg_pi_csel = 0x02
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT3 | _BIT2), _BIT3);

        // reg_le_isel = 0x02
        // reg_le_rlsel = 0x05
        // reg_le_rssel = 0x07
        // reg_le_mf_rssel = 0x05
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x02);
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
    }
    else if(ucFRLrate == 10)
    {
        // reg_sel_div = 0x00
        // reg_pi_csel = 0x02
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT3 | _BIT2), _BIT3);

        // reg_le_isel = 0x01
        // reg_le_rlsel = 0x06
        // reg_le_rssel = 0x08
        // reg_le_mf_rssel = 0x06
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x08);
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));
    }
    else // 12G
    {
        // reg_sel_div = 0x00
        // reg_pi_csel = 0x01
        ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT3 | _BIT2), _BIT2);

        // reg_le_isel = 0x00
        // reg_le_rlsel = 0x07
        // reg_le_rssel = 0x0A
        // reg_le_mf_rssel = 0x07
        ScalerSetBit_EXINT(P7C_04_GDI_ACC_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7C_05_GDI_ACC_08, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
        ScalerSetBit_EXINT(P7C_15_GDI_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0A);
        ScalerSetBit_EXINT(P7C_1F_BACK_OFFCAL_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
    }

    // reg_tap_en = 0x0F
    ScalerSetBit_EXINT(P7C_0A_GDI_DIGI_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_tap0_sumamp = 0x00
    ScalerSetBit_EXINT(P7C_16_GDI_CTRL1, ~(_BIT7 | _BIT6 | _BIT5), (0x00));

    // reg_vcm_tune = 0x02
    ScalerSetBit_EXINT(P7C_0A_GDI_DIGI_10, ~(_BIT5 | _BIT4), _BIT5);

    // reg_b_dig_rst_n = 0x01
    // reg_g_dig_rst_n = 0x01
    // reg_r_dig_rst_n = 0x01
    // reg_ck_dig_rst_n = 0x01
    ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [7:5]reg_inbuf_num_l0~3=010-->FIFO space number
    // [4:3]reg_format_sel_l0~3=01-->bits mode=18bit
    // [2]reg_fifo_en_l0~3=1-->Enable fifo
    // [1]reg_dfe_data_en_l0~3=1-->Data for DFE ready
    ScalerSetByte_EXINT(P1D_F8_DATA_PATH_12, 0x4E);
    ScalerSetByte_EXINT(P1D_F9_DATA_PATH_13, 0x4E);
    ScalerSetByte_EXINT(P1D_FA_DATA_PATH_14, 0x4E);
    ScalerSetByte_EXINT(P1D_FB_DATA_PATH_15, 0x4E);

    // [7]reg_cp_en_manual = 0x01 -> close loop
    ScalerSetBit_EXINT(P1D_1F_ANA_CDR_05, ~(_BIT7), (_BIT7));

    // reg_auto_mode = 0x0F -->Auto FLD KBand
    ScalerSetBit_EXINT(P1D_B0_DP_FLD_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // reg_band_out_mode[1:0] = 0x00 -> finetune FLD band
    ScalerSetBit_EXINT(P1D_E0_U3_FLD_40, ~(_BIT1 | _BIT0), 0x00);

    // reg_bbpd_pulse_sel = 0x01
    ScalerSetBit_EXINT(P7C_06_GDI_ACC_09, ~(_BIT7 | _BIT6), (_BIT6));

    // reg_rx_en = 0x0F
    // reg_cdr_en = 0x01 --> 0x03  --> 0x07 --> 0x0F
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    if(ucLane == 4)
    {
        ScalerSetBit_EXINT(P7C_10_GDI_POWR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }


    /////////////
    // DFE Initial //
    /////////////
    ScalerTmdsPhyRx3FrlSetDFEInitial_EXINT0();

    // reg_sel_foreoff_autok = 0x7F
    ScalerSetBit_EXINT(P1D_12_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x7F);

    // reg_offk_pc_l0~3 = 0x01
    ScalerSetBit_EXINT(P1D_13_ADJR_01, ~(_BIT7), (_BIT7));
    ScalerSetBit_EXINT(P1D_13_ADJR_01, ~(_BIT6), (_BIT6));
    ScalerSetBit_EXINT(P1D_14_ADJR_02, ~(_BIT7), (_BIT7));
    ScalerSetBit_EXINT(P1D_14_ADJR_02, ~(_BIT6), (_BIT6));

    // reg_psm = 0x00 --> OFF psm when Offset K to prevent abnormal offset value
    ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT0), 0x00);

    // reg_rstb_fore_offset[3][2:0] = 1 --> 0 --> 1
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), (_BIT5));
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), 0x00);
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), (_BIT5));
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // reg_sel_fore_off = 0x06 --> Debug out leq code for K offset
    ScalerSetBit_EXINT(P1D_11_DPHY_DEBUG, ~(_BIT2 | _BIT1 | _BIT0), 0x06);

    // Delay Time Waiting for K Offset
    for(ucOffsetOK = 0; ucOffsetOK <= 50; ucOffsetOK++)
    {
        if((ScalerGetBit_EXINT(P1D_17_FORE_OFF_TST_L0, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_18_FORE_OFF_TST_L1, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_19_FORE_OFF_TST_L2, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_1A_FORE_OFF_TST_L3, _BIT7) == _BIT7))
        {
            break;
        }
        DELAY_10US_EXINT();
    }

    // reg_psm = 0x01 --> Return to Clk Detect
    ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT0), (_BIT0));
    DELAY_45US_EXINT();


    /////////////////////
    // FLD Ref Counter //
    /////////////////////

    // reg_fld_mode_l0~3 = 0x00 ->Kband
    ScalerSetBit_EXINT(P1D_20_FLD_KICO_L0_A00, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_24_FLD_KICO_L1_A00, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_28_FLD_KICO_L2_A00, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P1D_2C_FLD_KICO_L3_A00, ~(_BIT7 | _BIT6), 0x00);

    if(g_usTmdsPhyRx3ExDataRate != ucFRLrate)
    {
        if((ucFRLrate == 3) || (ucFRLrate == 6) || (ucFRLrate == 12))
        {
            // reg_vco_coarse_lx[8][7:0] = 0x0C9
            ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(P1D_D9_U3_FLD_36, 0xC9);
            ScalerSetByte_EXINT(P1D_DA_U3_FLD_37, 0xC9);
            ScalerSetByte_EXINT(P1D_DB_U3_FLD_38, 0xC9);
            ScalerSetByte_EXINT(P1D_DC_U3_FLD_39, 0xC9);
        }
        else if(ucFRLrate == 8)
        {
            // reg_vco_coarse_lx[8][7:0] = 0x0F7
            ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(P1D_D9_U3_FLD_36, 0xF7);
            ScalerSetByte_EXINT(P1D_DA_U3_FLD_37, 0xF7);
            ScalerSetByte_EXINT(P1D_DB_U3_FLD_38, 0xF7);
            ScalerSetByte_EXINT(P1D_DC_U3_FLD_39, 0xF7);
        }
        else if(ucFRLrate == 10)
        {
            // reg_vco_coarse_lx[8][7:0] = 0x094
            ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte_EXINT(P1D_D9_U3_FLD_36, 0x94);
            ScalerSetByte_EXINT(P1D_DA_U3_FLD_37, 0x94);
            ScalerSetByte_EXINT(P1D_DB_U3_FLD_38, 0x94);
            ScalerSetByte_EXINT(P1D_DC_U3_FLD_39, 0x94);
        }
        g_usTmdsPhyRx3ExDataRate = ucFRLrate;
    }

    // First K fld//
    // FLD_clk=VCO_Freq/16
    // reg_cdr_divide_num[11:8] = 0x00 , reg_cdr_divide_num[7:0] = 0x0D
    ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x0D);

    if(ucFRLrate == 3)
    {
        // reg_cdr_lock_dn_limit[11:8] = 0x01 , reg_cdr_lock_dn_limit[7:0] = 0x69
        // reg_cdr_lock_up_limit[11:8] = 0x01  ,  reg_cdr_lock_up_limit[7:0] = 0x69
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x69);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x69);
    }
    else if(ucFRLrate == 6)
    {
        // reg_cdr_lock_dn_limit[11:8] = 0x01 , reg_cdr_lock_dn_limit[7:0] = 0x69
        // reg_cdr_lock_up_limit[11:8] = 0x01 , reg_cdr_lock_up_limit[7:0] = 0x69
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x69);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x69);
    }
    else if(ucFRLrate == 8)
    {
        // reg_cdr_lock_dn_limit[11:8] = 0x00 , reg_cdr_lock_dn_limit[7:0] = 0xF0
        // reg_cdr_lock_up_limit[11:8] = 0x00  ,  reg_cdr_lock_up_limit[7:0] = 0xF0
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0xF0);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0xF0);
    }
    else if(ucFRLrate == 10)
    {
        // reg_cdr_lock_dn_limit[11:8] = 0x01 , reg_cdr_lock_dn_limit[7:0] = 0x2C
        // reg_cdr_lock_up_limit[11:8] = 0x01 , reg_cdr_lock_up_limit[7:0] = 0x2C
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x2C);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x2C);
    }
    else if(ucFRLrate == 12)
    {
        // reg_cdr_lock_dn_limit[11:8] = 0x01 , reg_cdr_lock_dn_limit[7:0] = 0x69
        // reg_cdr_lock_up_limit[11:8] = 0x01  ,  reg_cdr_lock_up_limit[7:0] = 0x69
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x69);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x69);
    }


    ///////////////
    // FLD Reset //
    ///////////////

    // reg_rstb_fsm[3][2:0] = 0x00 --> 0x0F
    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), 0x00);

    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), (_BIT7));

    // Waiting for VCO Stable & DFE Adaptation
    // Delay Time Waiting for FLD Kband
    for(ucFldOK = 0; ucFldOK <= 100; ucFldOK++)
    {
        if(ucLane == 3)
        {
            if((ScalerGetBit_EXINT(P1D_D0_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D1_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D2_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
            {
                break;
            }
        }
        else
        {
            if((ScalerGetBit_EXINT(P1D_D0_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D1_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D2_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D3_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
            {
                break;
            }
        }
        DELAY_10US_EXINT();
    }

    ScalerSetByte_EXINT(P7C_18_OOBS_00, ucFldOK); // get fld waiting time

    // Record FLD Band to ManuMode
    // reg_vco_coarse_lx = reg_coarse_fsm_lx
    ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetBit_EXINT(P1D_D8_U3_FLD_35, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    ScalerSetByte_EXINT(P1D_D9_U3_FLD_36, ScalerGetByte_EXINT(P1D_D4_DP_FLD_31));
    ScalerSetByte_EXINT(P1D_DA_U3_FLD_37, ScalerGetByte_EXINT(P1D_D5_DP_FLD_32));
    ScalerSetByte_EXINT(P1D_DB_U3_FLD_38, ScalerGetByte_EXINT(P1D_D6_DP_FLD_33));
    ScalerSetByte_EXINT(P1D_DC_U3_FLD_39, ScalerGetByte_EXINT(P1D_D7_DP_FLD_34));

    // reg_fld_mode_l0~3 = 0x01 ->Kband+VCO
    ScalerSetBit_EXINT(P1D_20_FLD_KICO_L0_A00, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit_EXINT(P1D_24_FLD_KICO_L1_A00, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit_EXINT(P1D_28_FLD_KICO_L2_A00, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit_EXINT(P1D_2C_FLD_KICO_L3_A00, ~(_BIT7 | _BIT6), _BIT6);

    // Second K fld//
    // FLD_clk=VCO_Freq/16
    // reg_cdr_divide_num[11:8] = 0x00 , reg_cdr_divide_num[7:0] = 0x27
    ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte_EXINT(P1D_BF_U3_FLD_15, 0x41);


    if((ucFRLrate == 3) || (ucFRLrate == 6) || (ucFRLrate == 12))
    {
        // 1805  = 65  *  2  * 375M  / 27M = 0x70D
        // reg_cdr_lock_dn_limit[11:8] = 0x07 , reg_cdr_lock_dn_limit[7:0] = 0x0D
        // reg_cdr_lock_up_limit[11:8] = 0x07  ,  reg_cdr_lock_up_limit[7:0] = 0x0D
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0x0D);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0x0D);

        // reg_slope_hv_up = reg_slope_hv_dn = ulSlopeHV
        ScalerSetBit_EXINT(P1D_B7_U3_FLD_7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
        ScalerSetBit_EXINT(P1D_B9_U3_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
        ScalerSetByte_EXINT(P1D_B6_U3_FLD_6, 0x2B);
        ScalerSetByte_EXINT(P1D_B8_U3_FLD_8, 0x2B);

        // reg_slope_lv_up = reg_slope_lv_dn = ulSlopeHV
        ScalerSetBit_EXINT(P1D_B3_U3_FLD_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
        ScalerSetBit_EXINT(P1D_B5_U3_FLD_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
        ScalerSetByte_EXINT(P1D_B2_U3_FLD_2, 0xEF);
        ScalerSetByte_EXINT(P1D_B4_U3_FLD_4, 0xEF);
    }
    else if(ucFRLrate == 8)
    {
        // ref_cnt = div_num * fld_ck /ref_clk
        // 240  = 65  *  2  * 250M  / 27M = 0x4B0
        // reg_cdr_lock_dn_limit[11:8] = 0x04 , reg_cdr_lock_dn_limit[7:0] = 0xB0
        // reg_cdr_lock_up_limit[11:8] = 0x04  ,  reg_cdr_lock_up_limit[7:0] = 0xB0
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0xB0);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0xB0);

        // reg_slope_hv_up = reg_slope_hv_dn = ulSlopeHV
        ScalerSetBit_EXINT(P1D_B7_U3_FLD_7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
        ScalerSetBit_EXINT(P1D_B9_U3_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
        ScalerSetByte_EXINT(P1D_B6_U3_FLD_6, 0xD1);
        ScalerSetByte_EXINT(P1D_B8_U3_FLD_8, 0xD1);

        // reg_slope_lv_up = reg_slope_lv_dn = ulSlopeHV
        ScalerSetBit_EXINT(P1D_B3_U3_FLD_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
        ScalerSetBit_EXINT(P1D_B5_U3_FLD_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
        ScalerSetByte_EXINT(P1D_B2_U3_FLD_2, 0x95);
        ScalerSetByte_EXINT(P1D_B4_U3_FLD_4, 0x95);
    }
    else if(ucFRLrate == 10)
    {
        // 300  = 65  *  2  * 312.5M  / 27M = 0x5DC
        // reg_cdr_lock_dn_limit[11:8] = 0x05 , reg_cdr_lock_dn_limit[7:0] = 0xDC
        // reg_cdr_lock_up_limit[11:8] = 0x05  ,  reg_cdr_lock_up_limit[7:0] = 0xDC
        ScalerSetBit_EXINT(P1D_BE_U3_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
        ScalerSetByte_EXINT(P1D_BD_U3_FLD_13, 0xDC);
        ScalerSetBit_EXINT(P1D_BC_U3_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        ScalerSetByte_EXINT(P1D_BB_U3_FLD_11, 0xDC);

        // reg_slope_hv_up = reg_slope_hv_dn = ulSlopeHV
        ScalerSetBit_EXINT(P1D_B7_U3_FLD_7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);
        ScalerSetBit_EXINT(P1D_B9_U3_FLD_9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);
        ScalerSetByte_EXINT(P1D_B6_U3_FLD_6, 0xFE);
        ScalerSetByte_EXINT(P1D_B8_U3_FLD_8, 0xFE);

        // reg_slope_lv_up = reg_slope_lv_dn = ulSlopeHV
        ScalerSetBit_EXINT(P1D_B3_U3_FLD_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);
        ScalerSetBit_EXINT(P1D_B5_U3_FLD_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);
        ScalerSetByte_EXINT(P1D_B2_U3_FLD_2, 0xC2);
        ScalerSetByte_EXINT(P1D_B4_U3_FLD_4, 0xC2);
    }


    ///////////////
    // FLD Reset //
    ///////////////

    // reg_rstb_fsm[3][2:0] = 0x00 --> 0x0F
    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), 0x00);

    // Enable LE, Vth, Tap0~4 Adaptation
    ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0xDF);
    ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0xDF);
    ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0xDF);
    ScalerSetByte_EXINT(P7C_D1_L3_DFE_EN_2, 0xDF);

    ScalerSetBit_EXINT(P1D_1B_ANA_CDR_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P1D_1C_ANA_CDR_02, ~(_BIT7), (_BIT7));

    // Waiting for VCO Stable & DFE Adaptation
    // Delay Time Waiting for FLD Kband
    for(ucFldOK = 0; ucFldOK <= 200; ucFldOK++)
    {
        if(ucLane == 3)
        {
            if((ScalerGetBit_EXINT(P1D_D0_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D1_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D2_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
            {
                break;
            }
        }
        else
        {
            if((ScalerGetBit_EXINT(P1D_D0_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D1_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D2_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)) &&
               (ScalerGetBit_EXINT(P1D_D3_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
            {
                break;
            }
        }
        DELAY_10US_EXINT();
    }
    DELAY_XUS_EXINT(250);

    ScalerSetByte_EXINT(P7C_19_OOBS_01, ucFldOK); // get fld waiting time

    // Disable DFE Adaption
    ScalerSetByte_EXINT(P7C_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7C_D1_L3_DFE_EN_2, 0x00);

    // Record kvcoslope to ManuMode
    // reg_slope_band_lx = reg_coarse_fsm_lx
    ScalerSetBit_EXINT(P1D_E1_U3_FLD_41, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ScalerGetBit_EXINT(P1D_B3_U3_FLD_3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)));
    ScalerSetBit_EXINT(P1D_E1_U3_FLD_41, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetBit_EXINT(P1D_B5_U3_FLD_5, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    ScalerSetBit_EXINT(P1D_E2_U3_FLD_42, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ScalerGetBit_EXINT(P1D_B7_U3_FLD_7, (_BIT7 | _BIT6 | _BIT5 | _BIT4)));
    ScalerSetBit_EXINT(P1D_E2_U3_FLD_42, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetBit_EXINT(P1D_B9_U3_FLD_9, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

    // Record FLD Band to ManuMode
    // reg_vco_coarse_lx = reg_coarse_fsm_lx
    ScalerSetBit_EXINT(P1D_D8_U3_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetBit_EXINT(P1D_D8_U3_FLD_35, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    ScalerSetByte_EXINT(P1D_D9_U3_FLD_36, ScalerGetByte_EXINT(P1D_D4_DP_FLD_31));
    ScalerSetByte_EXINT(P1D_DA_U3_FLD_37, ScalerGetByte_EXINT(P1D_D5_DP_FLD_32));
    ScalerSetByte_EXINT(P1D_DB_U3_FLD_38, ScalerGetByte_EXINT(P1D_D6_DP_FLD_33));
    ScalerSetByte_EXINT(P1D_DC_U3_FLD_39, ScalerGetByte_EXINT(P1D_D7_DP_FLD_34));


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte_EXINT(P1D_17_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P7C_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1D_17_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P7C_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte_EXINT(P1D_18_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P7C_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1D_18_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P7C_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte_EXINT(P1D_19_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P7C_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1D_19_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P7C_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte_EXINT(P1D_1A_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(P7C_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(P1D_1A_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(P7C_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0x20);
    ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0x20);
    ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0x20);
    ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0x00);

    // reg_auto_mode = 0x00 -->Manu FLD KBand
    ScalerSetBit_EXINT(P1D_B0_DP_FLD_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [7]reg_cp_en_manual = 0x00 -> open loop
    ScalerSetBit_EXINT(P1D_1F_ANA_CDR_05, ~(_BIT7), 0x00);

    // reg_psm = 0x00 --> OFF psm when Offset K to prevent abnormal offset value
    ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT0), 0x00);

    // reg_rstb_fore_offset[3][2:0] = 1 --> 0 --> 1
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), 0x00);
    ScalerSetBit_EXINT(P1D_15_ADJR_03, ~(_BIT5), (_BIT5));
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetBit_EXINT(P1D_16_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time Waiting for K Offset
    for(ucOffsetOK = 0; ucOffsetOK <= 50; ucOffsetOK++)
    {
        if((ScalerGetBit_EXINT(P1D_17_FORE_OFF_TST_L0, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_18_FORE_OFF_TST_L1, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_19_FORE_OFF_TST_L2, _BIT7) == _BIT7) &&
           (ScalerGetBit_EXINT(P1D_1A_FORE_OFF_TST_L3, _BIT7) == _BIT7))
        {
            break;
        }
        DELAY_10US_EXINT();
    }

    // reg_psm = 0x01 --> Return to Clk Detect
    ScalerSetBit_EXINT(P7C_07_GDI_ACC_12, ~(_BIT0), (_BIT0));
    DELAY_45US_EXINT();


    /////////////////////
    //           Tap0+3         //
    /////////////////////

    if(ucFRLrate == 12)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(P7C_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(P7C_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte_EXINT(P7C_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte_EXINT(P7C_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte_EXINT(P7C_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 27)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte_EXINT(P7C_A4_L0_INIT_2, 0x1F);
        }
        else
        {
            // Reload Tap0 to Adapt + 3 (Max)
            ScalerSetByte_EXINT(P7C_A4_L0_INIT_2, (pucTap0[0] + 3));
        }
        ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0x01);
        ScalerSetByte_EXINT(P7C_AA_L0_INIT_8, 0x00);

        if(pucTap0[1] > 27)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte_EXINT(P7C_B4_L1_INIT_2, 0x1F);
        }
        else
        {
            // Reload Tap0 to Adapt + 3 (Max)
            ScalerSetByte_EXINT(P7C_B4_L1_INIT_2, (pucTap0[1] + 3));
        }
        ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0x01);
        ScalerSetByte_EXINT(P7C_BA_L1_INIT_8, 0x00);

        if(pucTap0[2] > 27)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte_EXINT(P7C_C4_L2_INIT_2, 0x1F);
        }
        else
        {
            // Reload Tap0 to Adapt + 3 (Max)
            ScalerSetByte_EXINT(P7C_C4_L2_INIT_2, (pucTap0[2] + 3));
        }
        ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0x01);
        ScalerSetByte_EXINT(P7C_CA_L2_INIT_8, 0x00);

        if(pucTap0[3] > 27)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte_EXINT(P7C_D4_L3_INIT_2, 0x1F);
        }
        else
        {
            // Reload Tap0 to Adapt + 3 (Max)
            ScalerSetByte_EXINT(P7C_D4_L3_INIT_2, (pucTap0[3] + 3));
        }
        ScalerSetByte_EXINT(P7C_DA_L3_INIT_8, 0x01);
        ScalerSetByte_EXINT(P7C_DA_L3_INIT_8, 0x00);
    }

    // [7]reg_cp_en_manual = 0x01 -> close loop
    ScalerSetBit_EXINT(P1D_1F_ANA_CDR_05, ~(_BIT7), _BIT7);
    DELAY_XUS_EXINT(150);

    // reg_en_offpn_edge_demux = 0x00->Disable offpn mux, set 0 when DFE adapt,offsetK end
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT1), 0x00);

    // reg_fld_reserved[18] = reg_aphy_adp_en_off = 1
    ScalerSetBit_EXINT(P1D_DD_U3_FLD_RES_00, ~(_BIT2), _BIT2);

    // reg_en_fld_div = 0x00 -->FLD K disable
    ScalerSetBit_EXINT(P7C_1E_BACK_OFFCAL_00, ~(_BIT3), 0x00);

    // Fifo Reset
    // [7]reg_b_dig_rst_n = 0 -> 1
    // [6]reg_g_dig_rst_n = 0 -> 1
    // [5]reg_r_dig_rst_n = 0 -> 1
    // [4]reg_ck_dig_rst_n = 0 -> 1
    ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(P1D_10_GDI_TEMP_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
}
#endif
#endif

