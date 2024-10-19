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
// ID Code      : RL6952_Series_DpPhyRx2_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPPHYRX2_WDINT__

#include "ScalerFunctionInclude.h"
#include "DpPhyRx2/ScalerDpPhyRx2.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DP_SUPPORT == _ON) && (_DP_PHY_RX2_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Rebuilding DP PHY in WDINT
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2RebuildPhy_WDINT(EnumDpLinkRate enumDpLinkRate)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping_EXINT0(_RX2);
    BYTE ucIcp = 0;
    BYTE ucIcpKp = 0;
    BYTE pucTap0[4];


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx2SetDFEInitial_EXINT0();

    // Backup Icp
    ucIcp = ScalerGetByte_EXINT(PE7_85_DP_FLD_21);
    ucIcpKp = ScalerGetByte_EXINT(PE7_C5_FLD_KICO_B05);

    // Double Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ScalerGetByte_EXINT(PE7_86_DP_FLD_22));
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, 0xFF);


    ///////////////////////////////
    // Manual FLD DFE Adaptation //
    ///////////////////////////////

    // [7:4] reg_fld_auto_mode = 4'b1111 --> FLD Auto Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0xFF);

    // Reset FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    DELAY_5US_EXINT();

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0xC3);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit_EXINT(PE8_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Start FLD
    ScalerSetBit_EXINT(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 200; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || (ScalerGetBit_EXINT(PE7_8B_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || (ScalerGetBit_EXINT(PE7_8C_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || (ScalerGetBit_EXINT(PE7_8D_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || (ScalerGetBit_EXINT(PE7_8E_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))))
        {
            break;
        }
    }

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit_EXINT(PE8_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [25,x] Waiting for DFE Adaptation
    DELAY_25US_EXINT();

    // Disable DFE Adaptation
    ScalerSetByte_EXINT(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(PE8_D1_L3_DFE_EN_2, 0x00);

    if(ScalerDpAuxRxGetLinkRate_WDINT(enumInputPort) >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte_EXINT(PE8_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit_EXINT(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte_EXINT(PE8_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte_EXINT(PE8_A4_L0_INIT_2, 0x1F);
            ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(PE8_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte_EXINT(PE8_B4_L1_INIT_2, 0x1F);
            ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(PE8_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte_EXINT(PE8_C4_L2_INIT_2, 0x1F);
            ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(PE8_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte_EXINT(PE8_D4_L3_INIT_2, 0x1F);
            ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte_EXINT(PE8_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit_EXINT(PE8_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(PE8_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(PE8_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(PE8_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(PE8_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(PE8_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(PE8_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit_EXINT(PE8_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit_EXINT(PE8_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte_EXINT(PE8_AA_L0_INIT_8, 0x20);
    ScalerSetByte_EXINT(PE8_BA_L1_INIT_8, 0x20);
    ScalerSetByte_EXINT(PE8_CA_L2_INIT_8, 0x20);
    ScalerSetByte_EXINT(PE8_DA_L3_INIT_8, 0x20);

    ScalerSetByte_EXINT(PE8_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(PE8_DA_L3_INIT_8, 0x00);

    // Enable Foreground Calibration
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US_EXINT();
    ScalerSetBit_EXINT(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(BYTE ucLoopIndex = 0; ucLoopIndex <= 100; ucLoopIndex++)
    {
        DELAY_5US_EXINT();

        if(((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte_EXINT(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte_EXINT(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte_EXINT(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit_EXINT(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte_EXINT(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            break;
        }
    }

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte_EXINT(PE7_70_DP_FLD_0, 0x0F);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit_EXINT(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // Restore Icp
    ScalerSetByte_EXINT(PE7_85_DP_FLD_21, ucIcp);
    ScalerSetByte_EXINT(PE7_C5_FLD_KICO_B05, ucIcpKp);
    ScalerSetByte_EXINT(PE7_C6_FLD_KICO_B06, ucIcpKp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US_EXINT();

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect_EXINT0(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    ScalerDpMacDphyRxChannelFifoReset_EXINT0(enumInputPort);
}
#endif
