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
// ID Code      : RL6952_Series_DpPhyRx2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
// Description  : Rebuilding DP PHY
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2RebuildPhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);
    BYTE ucIcp = 0;
    BYTE ucIcpKp = 0;
    BYTE pucTap0[4];
    WORD usTargetClock = 0;
    BYTE pucOobsOffset[4];


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    ScalerDpMacDphyRxSetCommaDetect(enumInputPort, _ON);

    ScalerDpMacDphyRxLaneSwapSelect(enumInputPort, ScalerDpPhyRxGetLaneMapping(enumInputPort, _DP_LANE_0) << 6);

    ScalerDpMacDphyRxLaneCountSet(enumInputPort, (ucDpcdLane & 0x1F));

    DebugMessageRx2("RebuildPhy", (WORD)((BYTE)enumDpLinkRate << 8) + ucDpcdLane);

#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
#endif
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)) || (_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON))
        ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE0);
        ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE1);
        ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE2);
        ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE3);
#endif
        switch(ucDpcdLane & 0x1F)
        {
            case _DP_ONE_LANE:

                ScalerGDIPhyRx2LanePower(_ENABLE, GET_DP_PHY_RX2_PCB_LANE0_MAPPING());

                break;

            case _DP_TWO_LANE:

                ScalerGDIPhyRx2LanePower(_ENABLE, GET_DP_PHY_RX2_PCB_LANE0_MAPPING());
                ScalerGDIPhyRx2LanePower(_ENABLE, GET_DP_PHY_RX2_PCB_LANE1_MAPPING());

                break;

            default:
            case _DP_FOUR_LANE:

                ScalerGDIPhyRx2LanePower(_ENABLE, GET_DP_PHY_RX2_PCB_LANE0_MAPPING());
                ScalerGDIPhyRx2LanePower(_ENABLE, GET_DP_PHY_RX2_PCB_LANE1_MAPPING());
                ScalerGDIPhyRx2LanePower(_ENABLE, GET_DP_PHY_RX2_PCB_LANE2_MAPPING());
                ScalerGDIPhyRx2LanePower(_ENABLE, GET_DP_PHY_RX2_PCB_LANE3_MAPPING());

                break;
        }
    }


    /////////////////////////////
    // Frequency & DFE Setting //
    /////////////////////////////

    ScalerDpPhyRx2CDRFLDSetting4Lane(enumDpLinkRate, _DP_NF_REF_XTAL);

    ucIcp = ScalerGetByte(PE7_85_DP_FLD_21);
    ucIcpKp = ScalerGetByte(PE7_C5_FLD_KICO_B05);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // OOBS Offset Auto Mode
    ScalerSetBit(PE3_00_RX_K_OOBS_L0_00, ~_BIT2, 0x00);
    ScalerSetBit(PE3_08_RX_K_OOBS_L1_00, ~_BIT2, 0x00);
    ScalerSetBit(PE3_10_RX_K_OOBS_L2_00, ~_BIT2, 0x00);
    ScalerSetBit(PE3_18_RX_K_OOBS_L3_00, ~_BIT2, 0x00);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte(PE7_70_DP_FLD_0, 0x0F);

    // Double Icp_kp/ki
    ScalerSetByte(PE7_85_DP_FLD_21, ScalerGetByte(PE7_86_DP_FLD_22));
    ScalerSetByte(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte(PE7_C6_FLD_KICO_B06, 0xFF);

    // Reset OOBS Offset Calibration
    ScalerSetBit(PE3_00_RX_K_OOBS_L0_00, ~_BIT7, 0x00);
    ScalerSetBit(PE3_08_RX_K_OOBS_L1_00, ~_BIT7, 0x00);
    ScalerSetBit(PE3_10_RX_K_OOBS_L2_00, ~_BIT7, 0x00);
    ScalerSetBit(PE3_18_RX_K_OOBS_L3_00, ~_BIT7, 0x00);

    // Enable Foreground Calibration
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US();
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            DebugMessageRx2("1st Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // OOBS Swap Vthpn = 0
    ScalerSetBit(PE8_62_LFPS_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Enable OOBS Offset Calibration
    ScalerSetBit(PE3_00_RX_K_OOBS_L0_00, ~_BIT7, _BIT7);
    ScalerSetBit(PE3_08_RX_K_OOBS_L1_00, ~_BIT7, _BIT7);
    ScalerSetBit(PE3_10_RX_K_OOBS_L2_00, ~_BIT7, _BIT7);
    ScalerSetBit(PE3_18_RX_K_OOBS_L3_00, ~_BIT7, _BIT7);

    DELAY_XUS(50);

    // Read OOBS Offset+
    pucOobsOffset[0] = ScalerGetByte(PE3_06_RX_K_OOBS_L0_06);
    pucOobsOffset[1] = ScalerGetByte(PE3_0E_RX_K_OOBS_L1_06);
    pucOobsOffset[2] = ScalerGetByte(PE3_16_RX_K_OOBS_L2_06);
    pucOobsOffset[3] = ScalerGetByte(PE3_1E_RX_K_OOBS_L3_06);

    // OOBS Swap Vthpn = 1
    ScalerSetBit(PE8_62_LFPS_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Reset OOBS Offset Calibration
    ScalerSetBit(PE3_00_RX_K_OOBS_L0_00, ~_BIT7, 0x00);
    ScalerSetBit(PE3_08_RX_K_OOBS_L1_00, ~_BIT7, 0x00);
    ScalerSetBit(PE3_10_RX_K_OOBS_L2_00, ~_BIT7, 0x00);
    ScalerSetBit(PE3_18_RX_K_OOBS_L3_00, ~_BIT7, 0x00);
    DELAY_5US();
    ScalerSetBit(PE3_00_RX_K_OOBS_L0_00, ~_BIT7, _BIT7);
    ScalerSetBit(PE3_08_RX_K_OOBS_L1_00, ~_BIT7, _BIT7);
    ScalerSetBit(PE3_10_RX_K_OOBS_L2_00, ~_BIT7, _BIT7);
    ScalerSetBit(PE3_18_RX_K_OOBS_L3_00, ~_BIT7, _BIT7);

    DELAY_XUS(50);

    // Reload OOBS Offset = (Offset+)/2 + (Offset-)/2
    ScalerSetByte(PE3_03_RX_K_OOBS_L0_03, (pucOobsOffset[0] >> 1) + (ScalerGetByte(PE3_06_RX_K_OOBS_L0_06) >> 1));
    ScalerSetByte(PE3_0B_RX_K_OOBS_L1_03, (pucOobsOffset[1] >> 1) + (ScalerGetByte(PE3_0E_RX_K_OOBS_L1_06) >> 1));
    ScalerSetByte(PE3_13_RX_K_OOBS_L2_03, (pucOobsOffset[2] >> 1) + (ScalerGetByte(PE3_16_RX_K_OOBS_L2_06) >> 1));
    ScalerSetByte(PE3_1B_RX_K_OOBS_L3_03, (pucOobsOffset[3] >> 1) + (ScalerGetByte(PE3_1E_RX_K_OOBS_L3_06) >> 1));

    // OOBS Offset Manual Mode
    ScalerSetBit(PE3_00_RX_K_OOBS_L0_00, ~_BIT2, _BIT2);
    ScalerSetBit(PE3_08_RX_K_OOBS_L1_00, ~_BIT2, _BIT2);
    ScalerSetBit(PE3_10_RX_K_OOBS_L2_00, ~_BIT2, _BIT2);
    ScalerSetBit(PE3_18_RX_K_OOBS_L3_00, ~_BIT2, _BIT2);

    DebugMessageRx2("OOBS Offset Lane0 =", ScalerGetByte(PE3_03_RX_K_OOBS_L0_03));
    DebugMessageRx2("OOBS Offset Lane1 =", ScalerGetByte(PE3_0B_RX_K_OOBS_L1_03));
    DebugMessageRx2("OOBS Offset Lane2 =", ScalerGetByte(PE3_13_RX_K_OOBS_L2_03));
    DebugMessageRx2("OOBS Offset Lane3 =", ScalerGetByte(PE3_1B_RX_K_OOBS_L3_03));


    ///////////////////////////////
    // Enable FLD and Close loop //
    ///////////////////////////////

    // [7:4] reg_fld_auto_mode = 4'b1111 --> FLD Auto Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte(PE7_70_DP_FLD_0, 0xFF);

    // Disable cp2adp_en
    ScalerSetBit(PE7_83_DP_FLD_19, ~_BIT6, 0x00);

    // Reset FLD
    ScalerSetBit(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    DELAY_5US();

    // Start FLD
    ScalerSetBit(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [0,1250] Waiting for FLD
    for(pData[0] = 0; pData[0] <= 250; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || (ScalerGetBit(PE7_8B_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || (ScalerGetBit(PE7_8C_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || (ScalerGetBit(PE7_8D_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || (ScalerGetBit(PE7_8E_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))))
        {
            DebugMessageRx2("1st FLD Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte(PE7_94_DP_FLD_35) >> 4);
    ScalerSetByte(PE7_95_DP_FLD_36, ScalerGetByte(PE7_90_DP_FLD_31));
    ScalerSetByte(PE7_96_DP_FLD_37, ScalerGetByte(PE7_91_DP_FLD_32));
    ScalerSetByte(PE7_97_DP_FLD_38, ScalerGetByte(PE7_92_DP_FLD_33));
    ScalerSetByte(PE7_98_DP_FLD_39, ScalerGetByte(PE7_93_DP_FLD_34));

    // Reset FLD
    ScalerSetBit(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    DELAY_10US();

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0xC3);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(PE8_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // Start FLD
    ScalerSetBit(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || (ScalerGetBit(PE7_8B_DP_FLD_27, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || (ScalerGetBit(PE7_8C_DP_FLD_28, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || (ScalerGetBit(PE7_8D_DP_FLD_29, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || (ScalerGetBit(PE7_8E_DP_FLD_30, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))))
        {
            DebugMessageRx2("2nd FLD Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Delay Time us [100,x] Waiting for DFE Adaptation
    DELAY_XUS(100);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(PE8_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [100,x] Waiting for DFE Adaptation
    DELAY_XUS(100);

    // Disable LE/Vth/Tap0~2 Adaptation
    ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0x00);

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte(PE8_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PE8_A4_L0_INIT_2, 0x1F);
            ScalerSetBit(PE8_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PE8_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PE8_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(PE8_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PE8_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PE8_B4_L1_INIT_2, 0x1F);
            ScalerSetBit(PE8_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PE8_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PE8_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(PE8_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PE8_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PE8_C4_L2_INIT_2, 0x1F);
            ScalerSetBit(PE8_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PE8_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PE8_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit(PE8_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PE8_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PE8_D4_L3_INIT_2, 0x1F);
            ScalerSetBit(PE8_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PE8_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PE8_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit(PE8_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PE8_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte(PE7_40_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PE8_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(PE7_40_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PE8_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte(PE7_41_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PE8_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(PE7_41_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PE8_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte(PE7_42_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PE8_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(PE7_42_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PE8_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte(PE7_43_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PE8_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(PE7_43_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PE8_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte(PE8_AA_L0_INIT_8, 0x20);
    ScalerSetByte(PE8_BA_L1_INIT_8, 0x20);
    ScalerSetByte(PE8_CA_L2_INIT_8, 0x20);
    ScalerSetByte(PE8_DA_L3_INIT_8, 0x20);

    ScalerSetByte(PE8_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PE8_BA_L1_INIT_8, 0x00);
    ScalerSetByte(PE8_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PE8_DA_L3_INIT_8, 0x00);

    // Enable Foreground Calibration
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US();
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            DebugMessageRx2("2nd Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }


    ////////////////
    // Manual FLD //
    ////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte(PE7_94_DP_FLD_35) >> 4);
    ScalerSetByte(PE7_95_DP_FLD_36, ScalerGetByte(PE7_90_DP_FLD_31));
    ScalerSetByte(PE7_96_DP_FLD_37, ScalerGetByte(PE7_91_DP_FLD_32));
    ScalerSetByte(PE7_97_DP_FLD_38, ScalerGetByte(PE7_92_DP_FLD_33));
    ScalerSetByte(PE7_98_DP_FLD_39, ScalerGetByte(PE7_93_DP_FLD_34));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte(PE7_70_DP_FLD_0, 0x0F);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // Restore Icp
    ScalerSetByte(PE7_85_DP_FLD_21, ucIcp);
    ScalerSetByte(PE7_C5_FLD_KICO_B05, ucIcpKp);
    ScalerSetByte(PE7_C6_FLD_KICO_B06, ucIcpKp);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    // DP MAC FIFO Reset
    ScalerDpMacDphyRxChannelFifoReset(enumInputPort);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    usTargetClock = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, _DP_PHY_RX2_D2_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_125_CYCLE) << 3;

    if(usTargetClock != 0)
    {
        g_pusDpPhyRx2ClockTarget[0] = usTargetClock;
        g_pusDpPhyRx2ClockTarget[1] = usTargetClock;
        g_pusDpPhyRx2ClockTarget[2] = usTargetClock;
        g_pusDpPhyRx2ClockTarget[3] = usTargetClock;
    }
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2SetDFEInitial(EnumDpLinkRate enumDpLinkRate)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);

    if(((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x02) & (_BIT2 | _BIT1 | _BIT0)) == 0x03) ||
       ((enumDpLinkRate == _DP_LINK_HBR2) && (ScalerDpPhyRx2GetPhyCtsFlag() == _TRUE) && ((g_ucDpPhyRx2CtsCtrl & 0x0F) == 0x02)))
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte(PE8_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte(PE8_ED_LOOP_DIV_2, 0xCA);
    }

    // Disable All Adaptation Loop
    ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0x00);


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte(PE8_A2_L0_LIMIT_INIT, 0xF8);
    ScalerSetByte(PE8_B2_L1_LIMIT_INIT, 0xF8);
    ScalerSetByte(PE8_C2_L2_LIMIT_INIT, 0xF8);
    ScalerSetByte(PE8_D2_L3_LIMIT_INIT, 0xF8);

    ScalerSetByte(PE8_A3_L0_INIT_1, 0xD0);
    ScalerSetByte(PE8_B3_L1_INIT_1, 0xD0);
    ScalerSetByte(PE8_C3_L2_INIT_1, 0xD0);
    ScalerSetByte(PE8_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte(PE8_A4_L0_INIT_2, 0x14);
    ScalerSetByte(PE8_B4_L1_INIT_2, 0x14);
    ScalerSetByte(PE8_C4_L2_INIT_2, 0x14);
    ScalerSetByte(PE8_D4_L3_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte(PE8_A5_L0_INIT_3, 0x03);
    ScalerSetByte(PE8_B5_L1_INIT_3, 0x03);
    ScalerSetByte(PE8_C5_L2_INIT_3, 0x03);
    ScalerSetByte(PE8_D5_L3_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte(PE8_A6_L0_INIT_4, 0x00);
    ScalerSetByte(PE8_B6_L1_INIT_4, 0x00);
    ScalerSetByte(PE8_C6_L2_INIT_4, 0x00);
    ScalerSetByte(PE8_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetBit(PE8_A9_L0_INIT_7, ~0x7F, 0x1C);
    ScalerSetBit(PE8_B9_L1_INIT_7, ~0x7F, 0x1C);
    ScalerSetBit(PE8_C9_L2_INIT_7, ~0x7F, 0x1C);
    ScalerSetBit(PE8_D9_L3_INIT_7, ~0x7F, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte(PE8_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(PE8_BA_L1_INIT_8, 0xFF);
    ScalerSetByte(PE8_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(PE8_DA_L3_INIT_8, 0xFF);

    ScalerSetByte(PE8_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PE8_BA_L1_INIT_8, 0x00);
    ScalerSetByte(PE8_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PE8_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(PE8_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PE8_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}


//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpPhyRx2DFECheck(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);

    if(ScalerDpAuxRxGetLinkRate(enumInputPort) >= _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)))
    {
        case _DP_FOUR_LANE:

            // Read Lane3 DFE
            ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx2("7. Lane3 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane2 DFE
            ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx2("7. Lane2 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx2("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx2("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx2("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx2("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit(PE8_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX2_D2_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PE8_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PE8_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PE8_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx2("7. Lane0 DFE Fail", 0);

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
// Description : Initial Signal check
// Input Value  : DP Link Rate
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2SignalDetectInitial(EnumDpLinkRate enumDpLinkRate, BYTE ucDpLEQScanValue)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);

    ucDpLEQScanValue = ucDpLEQScanValue;


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    ScalerDpMacDphyRxLaneSwapSelect(enumInputPort, _DP_PHY_RX2_D2_LANE0 << 6);


    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [7:4] LANE_EN = 4'b0000 --> Disable LANE_EN
    // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE0);
    ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE1);
    ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE2);
    ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE3);

    ScalerGDIPhyRx2LanePower(_ENABLE, _DP_SCALER_LANE0);
    ScalerGDIPhyRx2LanePower(_ENABLE, _DP_SCALER_LANE1);
    ScalerGDIPhyRx2LanePower(_ENABLE, _DP_SCALER_LANE2);
    ScalerGDIPhyRx2LanePower(_ENABLE, _DP_SCALER_LANE3);

    // [4:3] DP MAC Select Four Lane
    ScalerDpMacDphyRxLaneCountSet(enumInputPort, _DP_FOUR_LANE);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    ScalerDpPhyRx2SetDFEInitial(enumDpLinkRate);


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(enumDpLinkRate)
    {
        case _DP_LINK_UHBR20:

            // peak @10G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xF0);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x00);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x10);

            break;

        case _DP_LINK_UHBR13_5:

            // peak @6.75G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT1 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xE1);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x01);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x11);

            break;

        case _DP_LINK_UHBR10:

            // peak @5G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xA2);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x1B);

            break;

        case _DP_LINK_HBR3_9G:

            // peak @5G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xE2);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x13);

            break;

        case _DP_LINK_HBR3:

            // peak @5G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xE2);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x1B);

            break;

        case _DP_LINK_HBR2:

            // peak @2.7G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xC4);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x07);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x0F);

            break;

        case _DP_LINK_HBR:

            // peak @1.35G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte(PE8_35_LE_MODE_1, 0x86);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x0F);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x0F);

            break;

        case _DP_LINK_RBR:
        default:

            // peak @1.35G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte(PE8_35_LE_MODE_1, 0x86);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x0F);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x0F);

            break;
    }

    // Enable Foreground Calibration
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US();
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            DebugMessageRx2("1st Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }
}

//--------------------------------------------------
// Description : Enable Signal Detection
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2SignalDetection(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // [3:0] Enable Signal Detection
        ScalerSetBit(PE8_02_SIGNAL_DETECTION_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        if(ScalerDpAuxRxGetLinkRate(ScalerDpPhyRxRxDxMapping(_RX2)) >= _DP_LINK_HBR2)
        {
            // [4] reg_sel_ls_path_sigdtc = 0 --> Disable Low Speed Path for Signal Detection
            ScalerSetBit(PE8_02_SIGNAL_DETECTION_1, ~_BIT4, 0x00);
        }
        else
        {
            // [4] reg_sel_ls_path_sigdtc = 1 --> Enable Low Speed Path for Signal Detection
            ScalerSetBit(PE8_02_SIGNAL_DETECTION_1, ~_BIT4, _BIT4);
        }
    }
    else
    {
        // [3:0] Disable Signal Detection
        ScalerSetBit(PE8_02_SIGNAL_DETECTION_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Set DP Phy CTS Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpPhyRx2GetPhyCtsFlag(void)
{
    return ScalerGetBit(PE8_0E_FW_RESERVE_1, _BIT2);
}

//--------------------------------------------------
// Description  : Set DP Phy CTS Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpPhyRx2GetPhyCtsForDP14Flag(void)
{
    return (ScalerGetBit(PE8_0F_FW_RESERVE_2, _BIT3) != _BIT3);
}

//--------------------------------------------------
// Description  : Set DP Phy CTS Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpPhyRx2GetPhyCtsForDP20Flag(void)
{
    return (ScalerGetBit(PE8_0F_FW_RESERVE_2, _BIT3) >> 3);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);
    BYTE ucIcpKp = 0;
    BYTE ucIcp = 0;

    ScalerDpMacDphyRxLaneSwapSelect(enumInputPort, (g_ucDpPhyRx2CtsCtrl & 0x30) << 2);


    ///////////////////
    // Clock / Power //
    ///////////////////

    // CDR_EN,RX_EN Reset
    ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE0);
    ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE1);
    ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE2);
    ScalerGDIPhyRx2LanePower(_DISABLE, _DP_SCALER_LANE3);

    switch(g_ucDpPhyRx2CtsCtrl & 0x30)
    {
        case 0x00: // Lane0 Test

            ScalerGDIPhyRx2LanePower(_ENABLE, _DP_SCALER_LANE0);

            break;

        case 0x20: // Lane2 Test

            ScalerGDIPhyRx2LanePower(_ENABLE, _DP_SCALER_LANE2);

            break;

        case 0x30: // Lane3 Test

            ScalerGDIPhyRx2LanePower(_ENABLE, _DP_SCALER_LANE3);

            break;

        default:
        case 0x10: // Lane1 Test

            ScalerGDIPhyRx2LanePower(_ENABLE, _DP_SCALER_LANE1);

            break;
    }

    // [4:3] DP MAC Select Four Lane
    ScalerDpMacDphyRxLaneCountSet(enumInputPort, _DP_FOUR_LANE);


    //////////////
    // EQ + DFE //
    //////////////

    if(ScalerDpPhyRx2GetPhyCtsForDP14Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx2CtsCtrl & 0xC0)
        {
            case 0xC0: // HBR3

                ScalerDpPhyRx2CDRFLDSetting4Lane(_DP_LINK_HBR3, enumDpNFCodeRef);
                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_HBR3);

                break;

            case 0x80: // HBR2

                ScalerDpPhyRx2CDRFLDSetting4Lane(_DP_LINK_HBR2, enumDpNFCodeRef);
                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_HBR2);

                break;

            case 0x40: // HBR

                ScalerDpPhyRx2CDRFLDSetting4Lane(_DP_LINK_HBR, enumDpNFCodeRef);
                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_HBR);

                break;

            case 0x00: // RBR
            default:

                ScalerDpPhyRx2CDRFLDSetting4Lane(_DP_LINK_RBR, enumDpNFCodeRef);
                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_RBR);

                break;
        }
    }
    else if(ScalerDpPhyRx2GetPhyCtsForDP20Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx2CtsCtrl & 0xC0)
        {
            case 0xC0: // UHBR20
                DebugMessageRx2("UHBR20 TP1", g_ucDpPhyRx2CtsCtrl);
                ScalerDpPhyRx2CDRFLDSetting4Lane(_DP_LINK_UHBR20, enumDpNFCodeRef);
                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_UHBR20);

                break;

            case 0x80: // UHBR135
                DebugMessageRx2("UHBR13_5 TP1", g_ucDpPhyRx2CtsCtrl);
                ScalerDpPhyRx2CDRFLDSetting4Lane(_DP_LINK_UHBR13_5, enumDpNFCodeRef);
                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_UHBR13_5);

                break;

            default:
            case 0x40: // UHBR10
                DebugMessageRx2("UHBR10 TP1", g_ucDpPhyRx2CtsCtrl);
                ScalerDpPhyRx2CDRFLDSetting4Lane(_DP_LINK_UHBR10, enumDpNFCodeRef);
                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_UHBR10);

                break;
        }
    }

    ucIcp = ScalerGetByte(PE7_85_DP_FLD_21);
    ucIcpKp = ScalerGetByte(PE7_C5_FLD_KICO_B05);

    // [4] tap0_notrans = 1'b0 --> Tap0 is dependent on Every Bits
    ScalerSetBit(PE8_F8_GRAY_DEC_2, ~_BIT4, 0x00);


    /////////////
    // Koffset //
    /////////////

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Auto Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte(PE7_70_DP_FLD_0, 0xFF);

    // Reset FLD
    ScalerSetBit(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Foreground offset calibration reset (low active)
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US();
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            DebugMessageRx2("1st Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }


    ///////////////////////////////
    // Enable FLD and Close loop //
    ///////////////////////////////

    // Enable LE/Vth/Tap0~1 Adaptation
    ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0xC1);
    ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0xC1);
    ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0xC1);
    ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0xC1);

    // Keep LE for DFE bug
    ScalerSetBit(PE8_AA_L0_INIT_8, ~_BIT7, _BIT7);
    ScalerSetBit(PE8_BA_L1_INIT_8, ~_BIT7, _BIT7);
    ScalerSetBit(PE8_CA_L2_INIT_8, ~_BIT7, _BIT7);
    ScalerSetBit(PE8_DA_L3_INIT_8, ~_BIT7, _BIT7);

    // Start FLD
    ScalerSetBit(PE7_19_ANA_CDR_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    if(ScalerDpPhyRx2GetPhyCtsForDP14Flag() == _TRUE)
    {
        for(pData[0] = 0; pData[0] <= 200; pData[0]++)
        {
            DELAY_5US();
        }
    }
    else if(ScalerDpPhyRx2GetPhyCtsForDP20Flag() == _TRUE)
    {
        for(pData[0] = 0; pData[0] <= 200; pData[0]++)
        {
            DELAY_15US();
        }
    }

    // Disable LE/Vth/Tap0~2 Adaptation
    ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0x00);

    // Disable Keep LE for DFE bug
    ScalerSetBit(PE8_AA_L0_INIT_8, ~_BIT7, 0x00);
    ScalerSetBit(PE8_BA_L1_INIT_8, ~_BIT7, 0x00);
    ScalerSetBit(PE8_CA_L2_INIT_8, ~_BIT7, 0x00);
    ScalerSetBit(PE8_DA_L3_INIT_8, ~_BIT7, 0x00);


    ////////////////
    // Manual FLD //
    ////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerGetByte(PE7_94_DP_FLD_35) >> 4);
    ScalerSetByte(PE7_95_DP_FLD_36, ScalerGetByte(PE7_90_DP_FLD_31));
    ScalerSetByte(PE7_96_DP_FLD_37, ScalerGetByte(PE7_91_DP_FLD_32));
    ScalerSetByte(PE7_97_DP_FLD_38, ScalerGetByte(PE7_92_DP_FLD_33));
    ScalerSetByte(PE7_98_DP_FLD_39, ScalerGetByte(PE7_93_DP_FLD_34));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // Double Icp_kp/ki
    ScalerSetByte(PE7_85_DP_FLD_21, ScalerGetByte(PE7_86_DP_FLD_22));
    ScalerSetByte(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte(PE7_C6_FLD_KICO_B06, 0xFF);

    // Disable cp2adp_en
    ScalerSetBit(PE7_83_DP_FLD_19, ~_BIT6, 0x00);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b0000 --> Disable CDR Clock
    ScalerSetByte(PE7_70_DP_FLD_0, 0x0F);

    // Waiting for CDR lock
    for(pData[0] = 0; pData[0] <= 1; pData[0]++)
    {
        DELAY_5US();
    }

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    // Waiting for CDR lock
    for(pData[0] = 0; pData[0] <= 1; pData[0]++)
    {
        DELAY_5US();
    }

    // Restore Icp
    ScalerSetByte(PE7_85_DP_FLD_21, ucIcp);
    ScalerSetByte(PE7_C5_FLD_KICO_B05, ucIcpKp);
    ScalerSetByte(PE7_C6_FLD_KICO_B06, ucIcpKp);

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    // DP MAC FIFO Reset
    ScalerDpMacDphyRxChannelFifoReset(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyCtsTp2SetPhy(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);
    BYTE ucIcpKp = 0;
    BYTE ucIcp = 0;


    ScalerDpMacDphyRxSetCommaDetect(enumInputPort, _ON);

    // [2] Disable Enhancement Control Mode
    ScalerSetBit(PC5_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);


    /////////////////////////////
    // DFE CDR Initial Setting //
    /////////////////////////////

    // [4] tap0_notrans = 1'b1 --> Tap0 is dependent on run length
    ScalerSetBit(PE8_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    if(ScalerDpPhyRx2GetPhyCtsForDP14Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx2CtsCtrl & 0xC0)
        {
            case 0xC0: // HBR3

                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_HBR3);

                break;

            case 0x80: // HBR2

                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_HBR2);

                break;

            case 0x40: // HBR

                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_HBR);

                break;

            case 0x00: // RBR
            default:

                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_RBR);

                break;
        }
    }
    else if(ScalerDpPhyRx2GetPhyCtsForDP20Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx2CtsCtrl & 0xC0)
        {
            case 0xC0:

                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_UHBR20);

                break;

            case 0x80:

                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_UHBR13_5);

                break;

            default:
            case 0x40:

                ScalerDpPhyRx2SetDFEInitial(_DP_LINK_UHBR10);

                break;
        }
    }

    // Backup Icp
    ucIcp = ScalerGetByte(PE7_85_DP_FLD_21);
    ucIcpKp = ScalerGetByte(PE7_C5_FLD_KICO_B05);


    ///////////////////////////////
    // Manual FLD DFE Adaptation //
    ///////////////////////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    // Double Icp_kp/ki
    ScalerSetByte(PE7_85_DP_FLD_21, ScalerGetByte(PE7_86_DP_FLD_22));
    ScalerSetByte(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte(PE7_C6_FLD_KICO_B06, 0xFF);

    // Enable cp2adp_en
    ScalerSetBit(PE7_83_DP_FLD_19, ~_BIT6, _BIT6);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b1111 --> Enable CDR Clock
    ScalerSetByte(PE7_70_DP_FLD_0, 0x0F);

    if(((g_ucDpPhyRx2CtsCtrl & 0x80) == 0x80) || (ScalerDpPhyRx2GetPhyCtsForDP20Flag() == _TRUE))
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0xC3);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0xC3);
        ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0xC3);
    }

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    for(pData[0] = 0; pData[0] <= 1; pData[0]++)
    {
        DELAY_5US();
    }

    // Restore Icp
    ScalerSetByte(PE7_85_DP_FLD_21, ucIcp);
    ScalerSetByte(PE7_C5_FLD_KICO_B05, ucIcpKp);
    ScalerSetByte(PE7_C6_FLD_KICO_B06, ucIcpKp);

    // Delay for CDR lock / DFE Adaption
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();
    }

    // Disable DFE Adaptation
    ScalerSetByte(PE8_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PE8_D1_L3_DFE_EN_2, 0x00);

    // Disable cp2adp_en
    ScalerSetBit(PE7_83_DP_FLD_19, ~_BIT6, 0x00);

    // [7:4] reg_fld_auto_mode = 4'b0000 --> FLD Manual Mode
    // [3:0] reg_fld_adp_en_manual = 4'b0000 --> Disable CDR Clock
    ScalerSetByte(PE7_70_DP_FLD_0, 0x0F);

    // Foreground offset calibration reset (low active)
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, 0x00);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    DELAY_5US();
    ScalerSetBit(PE7_26_ADJR_03, ~_BIT5, _BIT5);
    ScalerSetBit(PE7_27_ADJR_04, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT0) == 0x00) || ((ScalerGetByte(PE7_40_FORE_OFF_TST_L0) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT1) == 0x00) || ((ScalerGetByte(PE7_41_FORE_OFF_TST_L1) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT2) == 0x00) || ((ScalerGetByte(PE7_42_FORE_OFF_TST_L2) & _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PE8_0B_RX_ENABLE, _BIT3) == 0x00) || ((ScalerGetByte(PE7_43_FORE_OFF_TST_L3) & _BIT7) == _BIT7)))
        {
            DebugMessageRx2("2nd Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Double Icp_kp/ki
    ScalerSetByte(PE7_85_DP_FLD_21, ScalerGetByte(PE7_86_DP_FLD_22));
    ScalerSetByte(PE7_C5_FLD_KICO_B05, 0xFF);
    ScalerSetByte(PE7_C6_FLD_KICO_B06, 0xFF);

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PE7_1E_ANA_CDR_05, ~_BIT7, 0x00);

    for(pData[0] = 0; pData[0] <= 1; pData[0]++)
    {
        DELAY_5US();
    }

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PE7_1E_ANA_CDR_05, ~_BIT7, _BIT7);

    for(pData[0] = 0; pData[0] <= 1; pData[0]++)
    {
        DELAY_5US();
    }

    // Restore Icp
    ScalerSetByte(PE7_85_DP_FLD_21, ucIcp);
    ScalerSetByte(PE7_C5_FLD_KICO_B05, ucIcpKp);
    ScalerSetByte(PE7_C6_FLD_KICO_B06, ucIcpKp);

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);

    // DP MAC FIFO Reset
    ScalerDpMacDphyRxChannelFifoReset(enumInputPort);
}

//--------------------------------------------------
// Description  : DP PHY CTS Process for DP1.x Auto Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyCtsAutoMode(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);

    while(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x70, _BIT7) == _BIT7)
    {
        ScalerDebug();

        DebugMessageRx2("DP Rx PHY CTS Auto Mode", 0x00);
    }
}

//--------------------------------------------------
// Description  : DP PHY CTS Process for DP1.x Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyCtsManualMode_8b10b(void)
{
    WORD usErrorCount = 0;
    BYTE ucErrorCountLaneSelect = 0;
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);

    usErrorCount = usErrorCount;

#if(_DP_PHY_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpPhyRx2GetPhyCtsForDP14Flag() == _TRUE)
    {
        ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_8B10B);
    }
#endif

    while((ScalerDpPhyRx2GetPhyCtsFlag() == _TRUE) && (ScalerDpPhyRx2GetPhyCtsForDP14Flag() == _TRUE))
    {
        ScalerDebug();

        if(ScalerDpPhyRx2GetPhyCtsForDP20Flag() == _TRUE)
        {
            return;
        }

        DebugMessageRx2("7. PHY CTS Loop1", ScalerGetByte(PE8_0F_FW_RESERVE_2));

        switch(ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30)
        {
            default:
            case 0x00: // Source Lane0

                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_PHY_RX2_D2_LANE0 << 4);

                break;

            case 0x10: // Source Lane1

                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_PHY_RX2_D2_LANE1 << 4);

                break;

            case 0x20: // Source Lane2

                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_PHY_RX2_D2_LANE2 << 4);

                break;

            case 0x30: // Source Lane3

                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_PHY_RX2_D2_LANE3 << 4);

                break;
        }

        g_ucDpPhyRx2CtsCtrl = ScalerGetByte(PE8_0F_FW_RESERVE_2);

        DebugMessageRx2("7. PHY CTS Loop2", g_ucDpPhyRx2CtsCtrl);

        switch(g_ucDpPhyRx2CtsCtrl & 0x07)
        {
            case 0x01: // CDR Lock Check

                ScalerSetByte(PE8_0F_FW_RESERVE_2, (g_ucDpPhyRx2CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0))); // Clear DP PHY CTS Phase Info

                ScalerDpPhyRx2PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                if(ScalerDpMacDphyRxPhyCtsTp1Check(enumInputPort) == _TRUE)
                {
                    ScalerSetBit(PE8_0E_FW_RESERVE_1, ~_BIT0, _BIT0);
                }
                else
                {
                    ScalerSetBit(PE8_0E_FW_RESERVE_1, ~_BIT0, 0x00);
                }

                break;

            case 0x02: // Symbol Lock Check

                ScalerSetByte(PE8_0F_FW_RESERVE_2, (g_ucDpPhyRx2CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerDpPhyRx2PhyCtsTp2SetPhy();

                if(ScalerDpMacDphyRxPhyCtsTp2Check(enumInputPort) == _TRUE)
                {
                    ScalerSetBit(PE8_0E_FW_RESERVE_1, ~_BIT1, _BIT1);
                }
                else
                {
                    ScalerSetBit(PE8_0E_FW_RESERVE_1, ~_BIT1, 0x00);
                }

                break;

            case 0x03:

                ScalerSetByte(PE8_0F_FW_RESERVE_2, (g_ucDpPhyRx2CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerDpPhyRx2PhyCtsTp2SetPhy();

                ScalerTimerDelayXms(10);

                if((g_ucDpPhyRx2CtsCtrl & 0xC0) >= 0x80)
                {
                    // TPS Pattern Follow MAC Lane
                    if(ScalerDpMacDphyRxGetLaneMuxMapping(enumInputPort, _DP_LANE_0) == ((g_ucDpPhyRx2CtsCtrl & 0x30) >> 4))
                    {
                        // MAC Lane0 Test
                        ucErrorCountLaneSelect = (0x00 << 4);
                    }
                    else if(ScalerDpMacDphyRxGetLaneMuxMapping(enumInputPort, _DP_LANE_1) == ((g_ucDpPhyRx2CtsCtrl & 0x30) >> 4))
                    {
                        // MAC Lane1 Test
                        ucErrorCountLaneSelect = (0x01 << 4);
                    }
                    else if(ScalerDpMacDphyRxGetLaneMuxMapping(enumInputPort, _DP_LANE_2) == ((g_ucDpPhyRx2CtsCtrl & 0x30) >> 4))
                    {
                        // MAC Lane2 Test
                        ucErrorCountLaneSelect = (0x02 << 4);
                    }
                    else if(ScalerDpMacDphyRxGetLaneMuxMapping(enumInputPort, _DP_LANE_3) == ((g_ucDpPhyRx2CtsCtrl & 0x30) >> 4))
                    {
                        // MAC Lane3 Test
                        ucErrorCountLaneSelect = (0x03 << 4);
                    }
                }
                else
                {
                    // PRBS Pattern Follow PHY Lane
                    ucErrorCountLaneSelect = (g_ucDpPhyRx2CtsCtrl & (_BIT5 | _BIT4));
                }

                usErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, (ucErrorCountLaneSelect >> 4));

                if((g_ucDpPhyRx2CtsCtrl & 0xC0) >= 0x80)
                {
                    // Enable Scramble
                    ScalerSetBit(PC5_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);

                    // HBR2/3 Compliance Eye Pattern
                    ScalerDpMacDphyRxDecodeErrorCountReset(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B_DISPARITY);
                }
                else
                {
                    // PRBS7 Pattern for RBR/HBR
                    ScalerDpMacDphyRxDecodeErrorCountReset(enumInputPort, _DP_MAC_DECODE_METHOD_PRBS7);
                }

                // Reset Error Count = 0
                ScalerSetByte(PE8_66_FW_RESERVE_3, 0x00);
                ScalerSetByte(PE8_67_FW_RESERVE_4, 0x00);

                break;

            case 0x04:

                ScalerSetByte(PE8_0F_FW_RESERVE_2, (g_ucDpPhyRx2CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerTimerDelayXms(10);

                if(((ScalerGetByte(PC5_09_BIST_PATTERN1) & 0x7F) | ScalerGetByte(PC5_0A_BIST_PATTERN2)) != 0x00)
                {
                    ScalerSetByte(PE8_66_FW_RESERVE_3, ScalerGetByte(PC5_0B_BIST_PATTERN3) & 0x7F);
                    ScalerSetByte(PE8_67_FW_RESERVE_4, ScalerGetByte(PC5_0C_BIST_PATTERN4));
                }
                else
                {
                    ScalerSetByte(PE8_66_FW_RESERVE_3, 0x7F);
                    ScalerSetByte(PE8_67_FW_RESERVE_4, 0xFF);
                }

                break;

            case 0x05:

                // Clear DP PHY CTS Control Register
                ScalerSetByte(PE8_0F_FW_RESERVE_2, 0x00);

                // Clear DP PHY CTS Result
                ScalerSetByte(PE8_0E_FW_RESERVE_1, 0x00);
                ScalerSetByte(PE8_66_FW_RESERVE_3, 0x00);
                ScalerSetByte(PE8_67_FW_RESERVE_4, 0x00);

                // Disable PRBS7 Error Detection
                ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                break;

            default:

                // Clear DP PHY CTS Control Register
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

                break;
        }

        if((g_ucDpPhyRx2CtsCtrl & 0x07) != 0x05)
        {
            if(((ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 4) == _DP_PHY_RX2_D2_LANE0) // Source Lane0
            {
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_SCALER_LANE0 << 4);
            }
            else if(((ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 4) == _DP_PHY_RX2_D2_LANE1) // Source Lane1
            {
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_SCALER_LANE1 << 4);
            }
            else if(((ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 4) == _DP_PHY_RX2_D2_LANE2) // Source Lane2
            {
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_SCALER_LANE2 << 4);
            }
            else if(((ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 4) == _DP_PHY_RX2_D2_LANE3) // Source Lane3
            {
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_SCALER_LANE3 << 4);
            }

            DebugMessageRx2("7. PHY CTS Loop (Swap Back)", ScalerGetByte(PE8_0F_FW_RESERVE_2));
        }
        else
        {
            g_ucDpPhyRx2CtsCtrl = 0x00;
        }
    }
}

#if(_DP_PHY_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP PHY CTS Process for DP2.x Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyCtsManualMode_128b132b(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX2);

    if(ScalerDpPhyRx2GetPhyCtsForDP20Flag() == _TRUE)
    {
        ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_128B132B);
    }

    while((ScalerDpPhyRx2GetPhyCtsFlag() == _TRUE) && (ScalerDpPhyRx2GetPhyCtsForDP20Flag() == _TRUE))
    {
        ScalerDebug();

        if(ScalerDpPhyRx2GetPhyCtsForDP20Flag() != _TRUE)   // switch to 8b10b
        {
            return;
        }

        DebugMessageRx2("7. PHY CTS Loop1", ScalerGetByte(PE8_0F_FW_RESERVE_2));

        // DP 20 MAC Select Lane
        ScalerSetBit(PD2_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), (ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30));
        ScalerSetBit(PD2_A8_BIST_PATTERN_SEL_DP20, ~(_BIT4 | _BIT3 | _BIT2), (ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 1);

        switch(ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30)
        {
            default:
            case 0x00: // Source Lane0

                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_PHY_RX2_D2_LANE0 << 4);

                break;

            case 0x10: // Source Lane1

                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_PHY_RX2_D2_LANE1 << 4);

                break;

            case 0x20: // Source Lane2

                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_PHY_RX2_D2_LANE2 << 4);

                break;

            case 0x30: // Source Lane3

                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_PHY_RX2_D2_LANE3 << 4);

                break;
        }

        g_ucDpPhyRx2CtsCtrl = ScalerGetByte(PE8_0F_FW_RESERVE_2);

        DebugMessageRx2("7. PHY CTS Loop DP20", g_ucDpPhyRx2CtsCtrl);

        switch(g_ucDpPhyRx2CtsCtrl & 0x07)
        {
            case 0x01: // CDR Lock Check

                ScalerSetByte(PE8_0F_FW_RESERVE_2, (g_ucDpPhyRx2CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0))); // Clear DP PHY CTS Phase Info

                ScalerDpPhyRx2PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                if(ScalerDpMacDphyRxPhyCtsTp1Check(enumInputPort) == _TRUE)
                {
                    ScalerSetBit(PE8_0E_FW_RESERVE_1, ~_BIT0, _BIT0);
                }
                else
                {
                    ScalerSetBit(PE8_0E_FW_RESERVE_1, ~_BIT0, 0x00);
                }

                break;

            case 0x02: // Symbol Lock Check

                ScalerSetByte(PE8_0F_FW_RESERVE_2, (g_ucDpPhyRx2CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerDpPhyRx2PhyCtsTp2SetPhy();

                if(ScalerDpMacDphyRxPhyCtsTp2Check(enumInputPort) == _TRUE)
                {
                    ScalerSetBit(PE8_0E_FW_RESERVE_1, ~_BIT1, _BIT1);
                }
                else
                {
                    ScalerSetBit(PE8_0E_FW_RESERVE_1, ~_BIT1, 0x00);
                }

                break;

            case 0x03:

                ScalerSetByte(PE8_0F_FW_RESERVE_2, (g_ucDpPhyRx2CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerDpPhyRx2PhyCtsTp2SetPhy();

                ScalerTimerDelayXms(2);

                // Reset PRBS Error Check
                ScalerSetBit(PD2_A7_SCRAMBLE_CTRL_DP20, ~_BIT4, 0x00);

                ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT1, _BIT1);
                ScalerSetBit(PD2_A1_PHY_DIG_RESET_CTRL_DP20, ~_BIT1, 0x00);

                // Reset Error Count = 0
                ScalerSetByte(PE8_66_FW_RESERVE_3, 0x00);
                ScalerSetByte(PE8_67_FW_RESERVE_4, 0x00);

                // Select PRBS31
                ScalerSetBit(PD2_A8_BIST_PATTERN_SEL_DP20, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT7 | _BIT5));

                // Disable PRBS New Mode, de-scramble
                ScalerSetBit(PD2_A7_SCRAMBLE_CTRL_DP20, ~(_BIT7 | _BIT5), _BIT5);

                // Wait for 2ms
                ScalerTimerDelayXms(2);

                // Start Record PRBS7 Error Count Value
                ScalerSetBit(PD2_A7_SCRAMBLE_CTRL_DP20, ~_BIT4, _BIT4);

                break;

            case 0x04:

                ScalerSetByte(PE8_0F_FW_RESERVE_2, (g_ucDpPhyRx2CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerTimerDelayXms(2);

                if((ScalerGetByte(PD2_A9_BIST_PATTERN_DP_20_1) | ScalerGetByte(PD2_AA_BIST_PATTERN_DP_20_2)) != 0x00)
                {
                    ScalerSetByte(PE8_66_FW_RESERVE_3, ScalerGetByte(PD2_AB_BIST_PATTERN_DP_20_3) & 0x7F);
                    ScalerSetByte(PE8_67_FW_RESERVE_4, ScalerGetByte(PD2_AC_BIST_PATTERN_DP_20_4));
                }
                else
                {
                    ScalerSetByte(PE8_66_FW_RESERVE_3, 0x7F);
                    ScalerSetByte(PE8_67_FW_RESERVE_4, 0xFF);
                }

                break;

            case 0x05:

                // Clear DP PHY CTS Control Register
                ScalerSetByte(PE8_0F_FW_RESERVE_2, 0x00);

                // Clear DP PHY CTS Result
                ScalerSetByte(PE8_0E_FW_RESERVE_1, 0x00);
                ScalerSetByte(PE8_66_FW_RESERVE_3, 0x00);
                ScalerSetByte(PE8_67_FW_RESERVE_4, 0x00);

                // Disable PRBS7 Error Detection
                ScalerSetBit(PC5_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                break;

            default:

                // Clear DP PHY CTS Control Register
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

                break;
        }

        if((g_ucDpPhyRx2CtsCtrl & 0x07) != 0x05)
        {
            if(((ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 4) == _DP_PHY_RX2_D2_LANE0) // Source Lane0
            {
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_SCALER_LANE0 << 4);
            }
            else if(((ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 4) == _DP_PHY_RX2_D2_LANE1) // Source Lane1
            {
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_SCALER_LANE1 << 4);
            }
            else if(((ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 4) == _DP_PHY_RX2_D2_LANE2) // Source Lane2
            {
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_SCALER_LANE2 << 4);
            }
            else if(((ScalerGetByte(PE8_0F_FW_RESERVE_2) & 0x30) >> 4) == _DP_PHY_RX2_D2_LANE3) // Source Lane3
            {
                ScalerSetBit(PE8_0F_FW_RESERVE_2, ~(_BIT5 | _BIT4), _DP_SCALER_LANE3 << 4);
            }

            DebugMessageRx2("7. PHY CTS Loop (Swap Back)", ScalerGetByte(PE8_0F_FW_RESERVE_2));
        }
        else
        {
            g_ucDpPhyRx2CtsCtrl = 0x00;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : DP PHY CTS Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyCts(void)
{
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX2_DP14_MAC, _POWER_CUT_OFF, _POWER_RESET_DISABLE);
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX2_DP20_MAC, _POWER_CUT_OFF, _POWER_RESET_DISABLE);

    while(ScalerDpPhyRx2GetPhyCtsFlag() == _TRUE)
    {
#if(_DP_PHY_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpPhyRx2GetPhyCtsForDP20Flag() == _TRUE)
        {
            ScalerDpPhyRx2PhyCtsManualMode_128b132b();
        }
        else
#endif
        {
            ScalerDpPhyRx2PhyCtsManualMode_8b10b();
        }
    }
}

//--------------------------------------------------
// Description : Check DP Eye Monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2EyeMonitor(void)
{
    /*
    // _ERROR_PRONE_CODE
    // (0x1D3A[1] = 1 --> Eye Monitor Enable
    // (0x1D39[2:0]) = 0x01 --> Search Phase
    // (0x1D39[2:0]) = 0x02 --> Vth Min
    // (0x1D39[2:0]) = 0x03 --> Vth Max
    // (0x1D39[2:0]) = 0x04 --> Start Phase
    // (0x1D39[2:0]) = 0x05 --> End Phase
    // (0x1D39[2:0]) = 0x06 --> Report Error Count for Single Point
    // (0x1D39[5:4]) = 00 --> lane0
    // (0x1D39[5:4]) = 01 --> lane1
    // (0x1D39[5:4]) = 10 --> lane2
    // (0x1D39[5:4]) = 11 --> lane3
    // (0x1D39[6]) = 1 --> Enable Eye Monitor All Once
    // (0x1D39[7]) = 1 --> Enable Allocation Once

    // PE7_EB_RESV_02 Phase
    // PE7_EC_RESV_03 Vth

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxx   xxxxxxxxxxxxxx  <- Vth Max
    // xxxxxxxxxxxx       xxxxxxxxxxxx
    // xxxxxxxxxx           xxxxxxxxxx
    // xxxxxxxx               xxxxxxxx
    // xxxxxxxxxx           xxxxxxxxxx
    // xxxxxxxxxxxx       xxxxxxxxxxxx
    // xxxxxxxxxxxxxx   xxxxxxxxxxxxxx  <- Vth Min
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // (       ^      ^      ^       )
    // (     Start   Best   End Phase)

    BYTE ucBestPhase = 0xFF;
    BYTE ucVthMin = 0;
    BYTE ucVthMax = 0;
    BYTE ucStartPhase = 0xFF;
    BYTE ucEndPhase = 0xFF;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // x   xxxxxxxxxxxxxxx   xxxxxxxxxxxxxxx  x
    // x     xxxxxxxxxxx       xxxxxxxxxxx    x
    // x       xxxxxxx           xxxxxxx      x
    // x         xxx               xxx        x
    // x       xxxxxxx           xxxxxxx      x
    // x     xxxxxxxxxxx       xxxxxxxxxxx    x
    // x   xxxxxxxxxxxxxxx   xxxxxxxxxxxxxxx  x
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // (^       ^   ^             ^   ^      ^)
    // Start  End Start         End Start  End
    // <--Left->    <-----Mid----->   <-Right->

    BYTE ucStartPhaseCountLeft = 0xFF;
    BYTE ucEndPhaseCountLeft = 0xFF;
    BYTE ucStartPhaseCountMid = 0xFF;
    BYTE ucEndPhaseCountMid = 0xFF;
    BYTE ucStartPhaseCountRight = 0xFF;
    BYTE ucEndPhaseCountRight = 0xFF;
    BYTE ucPhaseFirstEye = 0;
    BYTE ucPhaseSecondEye = 0;

    BYTE ucPassCriteriaCount = 1;
    BYTE ucBestVthCount = 0;
    BYTE ucCurrentVthCount = 0;
    WORD usErrorCount = 0;
    BYTE ucPhase = 0;
    BYTE ucVth = 0;

    // SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _DISABLE);

    DebugMessageRx2("Enable Eye Monitor", ScalerGetByte(PE8_39_REG_DUMMY_2));

    while(ScalerDpPhyRx2GetEyeMonitorEnableFlag() == _TRUE)
    {
        // Enable Eye Monitor
        ScalerSetBit(PE8_0D_EYE_MONITOR, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // reg_sel_pi_phase = 0
        ScalerSetBit(PE8_22_PI_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Vth Ctrl Manual Mode
        ScalerSetBit(PE8_EB_LIMIT_6, ~_BIT5, _BIT5);

        // PI Phase Manual Mode
        // ScalerSetBit(PE8_F5_ERRCNT1, ~_BIT7, _BIT7);

        // PI Phase Manual Mode
        ScalerSetBit(PE7_4E_DCDR_TEST_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


        while(ScalerDpPhyRx2GetEyeMonitorEnableFlag() == _TRUE)
        {
            ScalerDebug();

            // Enable Allocation Once
            if(ScalerGetBit(PE8_39_REG_DUMMY_2, _BIT7) == _BIT7)
            {
                ///////////
                // Reset //
                ///////////

                ScalerSetBit(PE8_39_REG_DUMMY_2, ~_BIT7, 0x00);

                // Reset Allocation Result
                ucBestPhase = 0xFF;
                ucStartPhaseCountLeft = 0xFF;
                ucEndPhaseCountLeft = 0xFF;
                ucStartPhaseCountMid = 0xFF;
                ucEndPhaseCountMid = 0xFF;
                ucStartPhaseCountRight = 0xFF;
                ucEndPhaseCountRight = 0xFF;

                ucBestVthCount = 0;
                ucVthMin = 0;
                ucVthMax = 0;


                ////////////////////////////
                // Locate 3 Phase Segment //
                ////////////////////////////

                for(ucPhase = 0; ucPhase < 64; ucPhase++)
                {
                    // Fix Vth = 1, Phase = 0~63
                    usErrorCount = ScalerDpPhyRx2EyeMonitorErrorCount(1, ucPhase);

                    // Allocate Left(Start, End) -> Mid(Start, End) -> Right(Start, End) In Order
                    if(ucStartPhaseCountLeft == 0xFF)
                    {
                        if(usErrorCount < ucPassCriteriaCount)
                        {
                            // Left(Start) = The First Phase w/o Error
                            ucStartPhaseCountLeft = ucPhase;
                        }
                    }
                    else if(ucEndPhaseCountLeft == 0xFF)
                    {
                        if(usErrorCount >= ucPassCriteriaCount)
                        {
                            // Left(End) = The First Phase w Error After Left(Start)
                            ucEndPhaseCountLeft = ucPhase - 1;
                        }
                    }
                    else if(ucStartPhaseCountMid == 0xFF)
                    {
                        if(usErrorCount < ucPassCriteriaCount)
                        {
                            // Mid(Start) = The First Phase w/o Error After Left(End)
                            ucStartPhaseCountMid = ucPhase;
                        }
                    }
                    else if(ucEndPhaseCountMid == 0xFF)
                    {
                        if(usErrorCount >= ucPassCriteriaCount)
                        {
                            // Mid(End) = The First Phase w Error After Mid(Start)
                            ucEndPhaseCountMid = ucPhase - 1;
                        }
                    }
                    else if(ucStartPhaseCountRight == 0xFF)
                    {
                        if(usErrorCount < ucPassCriteriaCount)
                        {
                            // Right(Start) = The First Phase w/o Error After Mid(End)
                            ucStartPhaseCountRight = ucPhase;
                        }
                    }
                    else if(ucEndPhaseCountRight == 0xFF)
                    {
                        if(usErrorCount >= ucPassCriteriaCount)
                        {
                            // Right(End) = The First Phase w Error After Right(Start)
                            ucEndPhaseCountRight = ucPhase - 1;
                        }
                        else if(ucPhase == 63)
                        {
                            ucEndPhaseCountRight = 63;
                        }
                    }
                }


                ///////////////////////
                // Search Best Phase //
                ///////////////////////

                if(ucStartPhaseCountRight == 0xFF)
                {
                    ucPhaseFirstEye = (ucEndPhaseCountLeft - ucStartPhaseCountLeft + 1);
                }
                else
                {
                    ucPhaseFirstEye = ((ucEndPhaseCountLeft - ucStartPhaseCountLeft + 1) + (ucEndPhaseCountRight - ucStartPhaseCountRight + 1));
                }

                ucPhaseSecondEye = (ucEndPhaseCountMid - ucStartPhaseCountMid + 1);

                // The Complete Eye is Locate At Middle
                if(ucPhaseFirstEye <= ucPhaseSecondEye)
                {
                    // Set (Start, End) to Search Best Phase
                    ucStartPhase = ucStartPhaseCountMid;
                    ucEndPhase = ucEndPhaseCountMid;

                    // Search Best Phase by the #(Vth w/o Error)
                    for(ucPhase = ucStartPhase; ucPhase <= ucEndPhase; ucPhase++)
                    {
                        ucCurrentVthCount = 0;

                        for(ucVth = 0; ucVth < 128; ucVth++) // #(0~127 = 128)
                        {
                            if(ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucPhase) < ucPassCriteriaCount)
                            {
                                ucCurrentVthCount++;
                            }
                        }

                        if(ucCurrentVthCount >= ucBestVthCount)
                        {
                            // Replace Best Phase if Current Phase has More Vth w/o Error
                            ucBestVthCount = ucCurrentVthCount;
                            ucBestPhase = ucPhase;
                        }
                    }
                }
                // The Complete Eye is Locate At (Right, Left)
                else
                {
                    if(ucStartPhaseCountRight == 0xFF)
                    {
                        // Two Complete Eye
                        ucStartPhase = ucStartPhaseCountLeft;
                        ucEndPhase = ucEndPhaseCountLeft;

                        // Search Best Phase by the #(Vth w/o Error)
                        for(ucPhase = ucStartPhase; ucPhase <= ucEndPhase; ucPhase++)
                        {
                            ucCurrentVthCount = 0;

                            for(ucVth = 0; ucVth < 128; ucVth++) // #(0~127 = 128)
                            {
                                if(ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucPhase) < ucPassCriteriaCount)
                                {
                                    ucCurrentVthCount++;
                                }
                            }

                            if(ucCurrentVthCount >= ucBestVthCount)
                            {
                                // Replace Best Phase if Current Phase has More Vth w/o Error
                                ucBestVthCount = ucCurrentVthCount;
                                ucBestPhase = ucPhase;
                            }
                        }
                    }
                    else
                    {
                        // One Complete Eye with Two Half Eye
                        ucStartPhase = ucStartPhaseCountRight;
                        ucEndPhase = ucEndPhaseCountLeft;

                        // Search Best Phase by the #(Vth w/o Error)
                        for(ucPhase = ucStartPhase; ucPhase <= 63; ucPhase++)
                        {
                            ucCurrentVthCount = 0;

                            for(ucVth = 0; ucVth < 128; ucVth++) // #(0~127 = 128)
                            {
                                if(ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucPhase) < ucPassCriteriaCount)
                                {
                                    ucCurrentVthCount++;
                                }
                            }

                            if(ucCurrentVthCount >= ucBestVthCount)
                            {
                                // Replace Best Phase if Current Phase has More Vth w/o Error
                                ucBestVthCount = ucCurrentVthCount;
                                ucBestPhase = ucPhase;
                            }
                        }

                        // Search Best Phase by the #(Vth w/o Error)
                        for(ucPhase = 0; ucPhase <= ucEndPhase; ucPhase++)
                        {
                            ucCurrentVthCount = 0;

                            for(ucVth = 0; ucVth < 128; ucVth++) // #(0~127 = 128)
                            {
                                if(ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucPhase) < ucPassCriteriaCount)
                                {
                                    ucCurrentVthCount++;
                                }
                            }

                            if(ucCurrentVthCount >= ucBestVthCount)
                            {
                                // Replace Best Phase if Current Phase has More Vth w/o Error
                                ucBestVthCount = ucCurrentVthCount;
                                ucBestPhase = ucPhase;
                            }
                        }
                    }
                }


                ////////////////////////
                // Search Vth Max/Min //
                ////////////////////////

                for(ucVth = 63; ucVth > 0; ucVth--) // #(1~63 = 63)
                {
                    if(ucVthMax == 0)
                    {
                        if(ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucBestPhase) < ucPassCriteriaCount)
                        {
                            // Vth Max = The First Vth Level w/o Error
                            ucVthMax = ucVth;
                        }
                    }
                }

                for(ucVth = 65; ucVth < 128; ucVth++) // #(65~127 = 63)
                {
                    if(ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucBestPhase) < ucPassCriteriaCount)
                    {
                        // Vth Min = The Last Vth Level w/o Error
                        ucVthMin = ucVth;
                    }
                }

                DebugMessageRx2("Allocation Finish", ScalerGetByte(PE8_39_REG_DUMMY_2));
            }

            // Read Out
            switch(ScalerGetBit(PE8_39_REG_DUMMY_2, (_BIT2 | _BIT1 | _BIT0)))
            {
                case 0x01: // Search Phase

                    ScalerSetBit(PE8_39_REG_DUMMY_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                    ScalerSetByte(PE8_0F_FW_RESERVE_2, ucBestPhase);

                    break;

                case 0x02: // Vth Min

                    ScalerSetBit(PE8_39_REG_DUMMY_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                    ScalerSetByte(PE8_0F_FW_RESERVE_2, ucVthMin);

                    break;

                case 0x03: // Vth Max

                    ScalerSetBit(PE8_39_REG_DUMMY_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                    ScalerSetByte(PE8_0F_FW_RESERVE_2, ucVthMax);

                    break;

                case 0x04: // Start Phase

                    ScalerSetBit(PE8_39_REG_DUMMY_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                    ScalerSetByte(PE8_0F_FW_RESERVE_2, ucStartPhase);

                    break;

                case 0x05: // End Phase

                    ScalerSetBit(PE8_39_REG_DUMMY_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                    ScalerSetByte(PE8_0F_FW_RESERVE_2, ucEndPhase);

                    break;

                case 0x06: // Report Error Count for Single Point

                    ScalerSetBit(PE8_39_REG_DUMMY_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                    // ucPhase = ScalerGetByte(PE7_EB_RESV_02) & 0x3F;

                    // ucVth = ScalerGetByte(PE7_EC_RESV_03) & 0x7F;

                    usErrorCount = ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucPhase);

                    ScalerSetByte(PE8_0F_FW_RESERVE_2, usErrorCount);

                    break;

                default:

                    break;
            }

#if(_DEBUG_MESSAGE_RX2 == _ON)
            // Enable Eye Monitor for Whole Plot
            if(ScalerGetBit(PE8_39_REG_DUMMY_2, _BIT6) == _BIT6)
            {
                ScalerSetBit(PE8_39_REG_DUMMY_2, ~_BIT6, 0x00);

                DebugMessageRx2("Eye Monitor All", 0x00);

                // For debugmsg not miss first X error cnt
                ScalerTimerDelayXms(100);

                // All Phase
                for(ucPhase = 0; ucPhase < 64; ucPhase++)
                {
                    // Positive Vth Up-Down (63 -> 1)
                    for(ucVth = 63; ucVth > 0; ucVth--) // #(1~63 = 64)
                    {
                        usErrorCount = ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucPhase);

                        DebugMessageRx2("====Error====", usErrorCount);
                    }

                    // Negative Vth Up-Down (0 -> -63)
                    for(ucVth = 64; ucVth < 128; ucVth++) // #(64~127 = 63)
                    {
                        usErrorCount = ScalerDpPhyRx2EyeMonitorErrorCount(ucVth, ucPhase);

                        DebugMessageRx2("====Error====", usErrorCount);
                    }
                }
            }
#endif
        }
    }
    // reg_sel_pi_phase = 0
    ScalerSetBit(PE8_22_PI_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Disable Eye Monitor
    ScalerSetBit(PE8_0D_EYE_MONITOR, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Vth Ctrl Auto Mode
    ScalerSetBit(PE8_EB_LIMIT_6, ~_BIT5, 0x00);

    // PI Phase Auto Mode
    // ScalerSetBit(PE8_F5_ERRCNT1, ~_BIT7, 0x00);

    // PI Phase Auto Mode
    ScalerSetBit(PE7_4E_DCDR_TEST_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    */
}
/*
//--------------------------------------------------
// Description : Check DP Eye Monitor
// Input Value  : Vth Selection, Phase Selection
// Output Value : # of Error Count
//--------------------------------------------------
WORD ScalerDpPhyRx2EyeMonitorErrorCount(BYTE ucVth, BYTE ucPhase)
{
    WORD usErrorCount = 0;

    // Disable Eye Scan
    ScalerSetBit(PE8_F4_ERRCNT0, ~_BIT1, 0x00);

    // Set PI Phase
    // ScalerSetBit(PE8_FC_PR_CTRL0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), g_pucDpRxEN[ucPhase / 16]);
    // ScalerSetByte(PE8_FE_EM_CTRL0, g_pusDpRxST[ucPhase] >> 8);
    // ScalerSetByte(PE8_FD_PR_CTRL1, g_pusDpRxST[ucPhase]);

    // Set PI Phase for NO EN ST
    switch(ScalerGetBit(PE8_39_REG_DUMMY_2, (_BIT5 | _BIT4)))
    {
        default:
        case (0x00):

            ScalerSetBit(PE7_69_CDR_25, ~0x3F, ucPhase);

            break;

        case (_BIT4):

            ScalerSetBit(PE7_6B_CDR_27, ~0x3F, ucPhase);

            break;

        case (_BIT5):

            ScalerSetBit(PE7_6D_CDR_29, ~0x3F, ucPhase);

            break;

        case (_BIT5 | _BIT4):

            ScalerSetBit(PE7_6F_CDR_31, ~0x3F, ucPhase);
    }

    // Set Vth
    ScalerSetBit(PE8_A9_L0_INIT_7, ~0x7F, ucVth);
    ScalerSetBit(PE8_B9_L1_INIT_7, ~0x7F, ucVth);
    ScalerSetBit(PE8_C9_L2_INIT_7, ~0x7F, ucVth);
    ScalerSetBit(PE8_D9_L3_INIT_7, ~0x7F, ucVth);

    // Enable Eye Scan
    ScalerSetBit(PE8_F4_ERRCNT0, ~_BIT1, _BIT1);

    switch(ScalerGetBit(PE8_39_REG_DUMMY_2, (_BIT5 | _BIT4)))
    {
        default:
        case (0x00):

            ScalerSetByte(PE8_FB_DEBUG, 0x04);

            break;

        case (_BIT4):

            ScalerSetByte(PE8_FB_DEBUG, 0x05);

            break;

        case (_BIT5):

            ScalerSetByte(PE8_FB_DEBUG, 0x06);

            break;

        case (_BIT5 | _BIT4):

            ScalerSetByte(PE8_FB_DEBUG, 0x07);
    }

    pData[0] = 0;
    while(ScalerGetBit(PE8_F4_ERRCNT0, _BIT7) == 0)        // wait valid bit assert
    {
        DELAY_5US();
        if(pData[0]++ > 100)
        {
            DebugMessageRx2("!!!!eye timeout!!!!", 0);
            break;
        }
    }
    // DELAY_XUS(500);  // 500us For Error

    switch(ScalerGetBit(PE8_39_REG_DUMMY_2, (_BIT5 | _BIT4)))
    {
        default:
        case (0x00):

            ScalerSetByte(PE8_FB_DEBUG, 0x04);

            usErrorCount = (WORD)ScalerGetByte(PE8_FF_EM_CTRL1) << 4; // [11:4]

            ScalerSetByte(PE8_FB_DEBUG, 0x08);

            usErrorCount = usErrorCount + (ScalerGetByte(PE8_FF_EM_CTRL1) >> 4);  // [3:0]

            break;

        case (_BIT4):

            ScalerSetByte(PE8_FB_DEBUG, 0x05);

            usErrorCount = (WORD)ScalerGetByte(PE8_FF_EM_CTRL1) << 4;

            ScalerSetByte(PE8_FB_DEBUG, 0x08);

            usErrorCount = usErrorCount + (ScalerGetByte(PE8_FF_EM_CTRL1) & 0x0F);

            break;

        case (_BIT5):

            ScalerSetByte(PE8_FB_DEBUG, 0x06);

            usErrorCount = (WORD)ScalerGetByte(PE8_FF_EM_CTRL1) << 4;

            ScalerSetByte(PE8_FB_DEBUG, 0x09);

            usErrorCount = usErrorCount + (ScalerGetByte(PE8_FF_EM_CTRL1) >> 4);

            break;

        case (_BIT5 | _BIT4):

            ScalerSetByte(PE8_FB_DEBUG, 0x07);

            usErrorCount = (WORD)ScalerGetByte(PE8_FF_EM_CTRL1) << 4;

            ScalerSetByte(PE8_FB_DEBUG, 0x09);

            usErrorCount = usErrorCount + (ScalerGetByte(PE8_FF_EM_CTRL1) & 0x0F);
    }

    return usErrorCount;
}
*/

//--------------------------------------------------
// Description : Get Eye Monitor ENable Flag
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpPhyRx2GetEyeMonitorEnableFlag(void)
{
    return ((ScalerGetByte(PE8_0E_FW_RESERVE_1) & _BIT3) == _BIT3);
}

//--------------------------------------------------
// Description  : DP Phy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2PhyInitial(void)
{
    //////////////
    // Rx Power //
    //////////////

#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
#if((_DUAL_DP_SUPPORT == _OFF) && (_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF))
    ScalerGDIPhyRxDisableOtherPort(ScalerDpPhyRxRxDxMapping(_RX2));
#endif
#endif

    //////////////////
    // Misc Setting //
    //////////////////

    // Enable Div20 Clock for DP 4 Lane
    ScalerSetBit(PE8_15_CLOCK_DIV_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Data/10
    ScalerSetBit(PE8_02_SIGNAL_DETECTION_1, ~_BIT5, _BIT5);

    // DP Global Parameter MeasureCount Initial
    ScalerDpRxMeasureCountInitial();


    /////////////////
    // DFE Initial //
    /////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit(PE8_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PE8_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PE8_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PE8_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetBit(PE8_E0_MODE_TIMER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1));

    // Tap0 Loop Gain 1/512, Tap1 Loop Gain 1/128
    ScalerSetBit(PE8_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit(PE8_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit(PE8_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit(PE8_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit(PE8_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Disable LE Gray Code
    ScalerSetByte(PE8_EE_GRAY_DEC_1, 0x21);

    // Tap0 Max is 31
    ScalerSetBit(PE8_E6_LIMIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Tap1 Min is -15
    ScalerSetBit(PE8_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Tap2 Max is 6, Min is -6
    ScalerSetBit(PE8_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit(PE8_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PE8_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 3, Min is -3
    ScalerSetBit(PE8_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(PE8_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 3, Min is -3
    ScalerSetBit(PE8_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PE8_EB_LIMIT_6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(PE8_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Vth Threshold = 18
    ScalerSetBit(PE8_F4_ERRCNT0, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit(PE8_E6_LIMIT_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // Tap0 Threshold = 10
    ScalerSetBit(PE8_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetBit(PE8_F8_GRAY_DEC_2, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte(PE8_EC_LOOP_DIV_1, 0xA3);

    // [1] tap1_trans = 1'b1 --> Tap1 is Effective on Transition bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every Bits
    ScalerSetBit(PE8_E3_GAIN_2, ~(_BIT1 | _BIT0), _BIT1);

    // [5] servo_notrans = 1'b0 --> Servo is Effective on Every Bits
    ScalerSetBit(PE8_F8_GRAY_DEC_2, ~_BIT5, 0x00);

    // [1:0] trans_rlength = 3'b000 --> Tap0 Run Length = 2
    ScalerSetBit(PE8_E5_GAIN_4, ~_BIT0, 0x00);
    ScalerSetBit(PE8_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);

    // [1:0] tap0_adjust = 2'b01
    ScalerSetBit(PE8_F6_ERRCNT2, ~(_BIT1 | _BIT0), _BIT0);

    // Set Vth Max = 63, Min = 12
    ScalerSetBit(PE8_F4_ERRCNT0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(PE8_F6_ERRCNT2, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetByte(PE8_F9_LIMIT_10, 0xFC);


    ////////////////
    // EQ Setting //
    ////////////////

    // DFE Enable
    ScalerSetBit(PE7_F8_DATA_PATH_12, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    ScalerSetBit(PE7_F9_DATA_PATH_13, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    ScalerSetBit(PE7_FA_DATA_PATH_14, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
    ScalerSetBit(PE7_FB_DATA_PATH_15, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

    // reg_tap_en : DFE TAP Enable
    ScalerSetByte(PE8_46_DFE_ENABLE_1, 0xFF);
    ScalerSetByte(PE8_47_DFE_ENABLE_2, 0xFF);


    /////////////////
    // CDR Setting //
    /////////////////

    // Enable Analog CDR
    ScalerSetBit(PE7_1A_ANA_CDR_01, ~_BIT0, _BIT0);
    ScalerSetByte(PE8_1A_BBPD_SEL_2, 0xFF);
    ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Enable Clkout for Open Loop Measure
    ScalerSetBit(PE7_1A_ANA_CDR_01, ~_BIT1, _BIT1);
    ScalerSetBit(PE7_1B_ANA_CDR_02, ~_BIT1, _BIT1);

    // Release CDR Reset
    ScalerSetBit(PE7_10_DPHY_SETUP, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(PE7_11_DPHY_DEBUG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // FLD k band only
    ScalerSetByte(PE7_A0_FLD_KICO_L0_A00, 0x12);
    ScalerSetByte(PE7_A8_FLD_KICO_L1_A00, 0x12);
    ScalerSetByte(PE7_B0_FLD_KICO_L2_A00, 0x12);
    ScalerSetByte(PE7_B8_FLD_KICO_L3_A00, 0x12);

    // FLD Bandout Mode = 2'b01 --> >= Target
    ScalerSetBit(PE7_99_DP_FLD_40, ~(_BIT1 | _BIT0), _BIT0);

    // Manual KVCO
    ScalerSetBit(PE7_71_DP_FLD_1, ~_BIT1, _BIT1);

    // [7] reg_en_icpkp_track = 1 --> Enable Icp_Kp Tracking
    // [6] reg_en_iki_track = 1 --> Enable Icp_Ki Tracking
    // [3] reg_v2i_lpf_force_en = 1 --> Enable V2I in Dual Loop
    ScalerSetBit(PE8_2E_DUAL_LOOP_1, ~(_BIT7 | _BIT6 | _BIT3), (_BIT7 | _BIT6 | _BIT3));

    // reg_cdr_res_direct = 1 --> Enable Min CDR Rs ~ 100Ohm
    ScalerSetBit(PE8_15_CLOCK_DIV_1, ~_BIT4, _BIT4);

    // reg_cdr_r = 2K
    ScalerSetBit(PE7_8A_DP_FLD_26, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // reg_slope_icp_band[4] = 0
    ScalerSetBit(PE7_CF_FLD_KICO_B15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [1] reg_vco_lpf_force_en = 1 --> Enable Force VCO LPF by Register
    ScalerSetBit(PE8_1D_VCO_LPF_1, ~_BIT1, _BIT1);

    // reg_large_kvco_sel = 3'b100 --> 1xKVCO + 4xKVCO
    ScalerSetBit(PE8_20_KVCO_1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // reg_large_kvco_lpf_sel = 3'b100 --> 4xKVCO after LPF
    ScalerSetBit(PE8_2E_DUAL_LOOP_1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    SET_DP_PHY_RX2_ICP_KP_RBR(0x88);
    SET_DP_PHY_RX2_ICP_KP_HBR(0x66);
    SET_DP_PHY_RX2_ICP_KP_HBR2(0x33);
    SET_DP_PHY_RX2_ICP_KP_HBR3(0x22);
    SET_DP_PHY_RX2_ICP_KP_UHBR10(0x33);
    SET_DP_PHY_RX2_ICP_KP_UHBR13P5(0x22);
    SET_DP_PHY_RX2_ICP_KP_UHBR20(0x33);

    SET_DP_PHY_RX2_ICP_RBR(0x11);
    SET_DP_PHY_RX2_ICP_HBR(0x44);
    SET_DP_PHY_RX2_ICP_HBR2(0x11);
    SET_DP_PHY_RX2_ICP_HBR3(0x66);
    SET_DP_PHY_RX2_ICP_UHBR10(0x33);
    SET_DP_PHY_RX2_ICP_UHBR13P5(0x33);
    SET_DP_PHY_RX2_ICP_UHBR20(0x11);

    SET_DP_PHY_RX2_KVCO_RBR(_BIT7 | _BIT4);
    SET_DP_PHY_RX2_KVCO_HBR(_BIT7 | _BIT4);
    SET_DP_PHY_RX2_KVCO_HBR2(_BIT7 | _BIT4);
    SET_DP_PHY_RX2_KVCO_HBR3(_BIT7 | _BIT5);
    SET_DP_PHY_RX2_KVCO_UHBR10(_BIT6 | _BIT5 | _BIT4);
    SET_DP_PHY_RX2_KVCO_UHBR13P5(_BIT7 | _BIT4);
    SET_DP_PHY_RX2_KVCO_UHBR20(_BIT7 | _BIT4);


    ////////////////////
    // Offset Setting //
    ////////////////////

    // reg_offk_delay = 6*Clock Period for Accuracy
    ScalerSetBit(PE7_26_ADJR_03, ~(_BIT7 | _BIT6), _BIT7);

    // reg_sel_forek = LEQ for Detecting Calibration Done
    ScalerSetBit(PE7_11_DPHY_DEBUG, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(PE7_23_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // oobs_offset_timeout = 0x40
    ScalerSetByte(PE3_01_RX_K_OOBS_L0_01, 0x40);
    ScalerSetByte(PE3_09_RX_K_OOBS_L1_01, 0x40);
    ScalerSetByte(PE3_11_RX_K_OOBS_L2_01, 0x40);
    ScalerSetByte(PE3_19_RX_K_OOBS_L3_01, 0x40);

    // Enable OOBS Offset
    ScalerSetBit(PE3_00_RX_K_OOBS_L0_00, ~_BIT4, _BIT4);
    ScalerSetBit(PE3_08_RX_K_OOBS_L1_00, ~_BIT4, _BIT4);
    ScalerSetBit(PE3_10_RX_K_OOBS_L2_00, ~_BIT4, _BIT4);
    ScalerSetBit(PE3_18_RX_K_OOBS_L3_00, ~_BIT4, _BIT4);


    //////////
    // ALPM //
    //////////

    // [3] reg_rx_en_alpm = 1 --> Enable Rx Bias @ ALPM Mode
    // [2] reg_lfps_inputs = 1 --> Enable APHY LFPS Input Switch
    ScalerSetBit(PE8_50_ALPM_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [7:6] reg_z0_pn_en_alpm --> Enable Rx Termination @ ALPM Mode
    ScalerSetBit(PE8_53_ALPM_4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Enable APHY LFPS Detect
    ScalerSetByte(PE8_60_LFPS_1, 0xFF);
    ScalerSetBit(PE8_61_LFPS_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(PE8_64_LFPS_5, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
    ScalerSetBit(PE8_65_LFPS_6, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));

    // Enable CMU Large Rs for PLL Mode
    ScalerSetBit(PE8_23_CMU_2, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // APHY LFPS Threshold = 0x00 (Coarse) + 0x02 (Fine)
    // ScalerSetByte(PE8_63_LFPS_4, 0x00);
    // ScalerSetBit(PE8_64_LFPS_5, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));
    // ScalerSetBit(PE8_65_LFPS_6, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

    // Enable DPHY LFPS Detect
    ScalerSetBit(PE3_40_LFPS_DETECT_20, ~_BIT7, _BIT7);

    // LFPS Period Setting
    ScalerSetByte(PE3_41_LFPS_DETECT_21, 0x05);
    ScalerSetByte(PE3_42_LFPS_DETECT_22, 0x1C);

    // [7:0] reg_lfps_count = 0x06 => LFPS debouce times, neet 1T LFPS for Detect
    ScalerSetByte(PE3_45_LFPS_DETECT_25, 0x06);

    // Disable Gating Clock @ ALPM Mode
    ScalerSetByte(PE3_72_ALPM_35, 0x00);
    ScalerSetByte(PE3_73_ALPM_36, 0x00);
    ScalerSetByte(PE3_74_ALPM_37, 0x00);
    ScalerSetByte(PE3_75_ALPM_38, 0x00);
    ScalerSetByte(PE3_76_ALPM_39, 0x00);
}
//--------------------------------------------------
// Description  : DP APhy CDR & FLD Initial Setting
// Input Value  : Link Ratw & Ref Method
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx2CDRFLDSetting4Lane(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef)
{
    enumDpNFCodeRef = enumDpNFCodeRef;

    // using xtal
    ScalerSetBit(PE7_1D_ANA_CDR_04, ~_BIT7, 0x00);

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // bbpd_pulse_sel = 01 --> Half Rate /3
        ScalerSetBit(PE8_19_BBPD_SEL_1, ~(_BIT1 | _BIT0), _BIT0);

        // reg_sel_icp_kp_ratio = 3'b010 --> 8/10
        ScalerSetBit(PE8_26_KP_PATH_2, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // bbpd_pulse_sel = 11 --> Full Rate /3
        ScalerSetBit(PE8_19_BBPD_SEL_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // reg_sel_icp_kp_ratio = 3'b001 --> 8/8 (Default)
        ScalerSetBit(PE8_26_KP_PATH_2, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    if(enumDpLinkRate >= _DP_LINK_HBR3)
    {
        // Disable DFE Delay Increase
        ScalerSetBit(PE8_34_LE_PEAKING, ~_BIT3, 0x00);
    }
    else
    {
        // Enable DFE Delay Increase
        ScalerSetBit(PE8_34_LE_PEAKING, ~_BIT3, _BIT3);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR10)
    {
        // Disable VCO Low Power Mode
        ScalerSetBit(PE8_5D_LOW_POWER_MODE_1, ~(_BIT1 | _BIT0), 0x00);

        // reg_v2i_isel = 2'b10
        ScalerSetBit(PE8_2F_DUAL_LOOP_2, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Enable VCO Low Power Mode
        ScalerSetBit(PE8_5D_LOW_POWER_MODE_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // reg_v2i_isel = 2'b00
        ScalerSetBit(PE8_2F_DUAL_LOOP_2, ~(_BIT1 | _BIT0), 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR13_5)
    {
        // reg_cco_large_iptat = 2'b01 --> 12.5%
        ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // reg_cco_large_iptat = 2'b00 --> 0%
        ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT1 | _BIT0), 0x00);
    }

    if(enumDpLinkRate == _DP_LINK_UHBR20)
    {
        // Enable VCO High Power Mode
        ScalerSetBit(PE8_5D_LOW_POWER_MODE_1, ~_BIT2, _BIT2);

        // Enable Large Icp
        ScalerSetBit(PE8_20_KVCO_1, ~_BIT3, _BIT3);
    }
    else
    {
        // Disable VCO High Power Mode
        ScalerSetBit(PE8_5D_LOW_POWER_MODE_1, ~_BIT2, 0x00);

        // Disable Large Icp
        ScalerSetBit(PE8_20_KVCO_1, ~_BIT3, 0x00);
    }
    /*
    if(enumDpLinkRate == _DP_LINK_HBR2)
    {
        // reg_sel_leqgain_rs = 2'b11 --> High Gain Low Boost
        ScalerSetBit(PE8_37_REG_RESERVED_3, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
    else
    {
        // reg_sel_leqgain_rs = 2'b00 --> Low Gain High Boost
        ScalerSetBit(PE8_37_REG_RESERVED_3, ~(_BIT1 | _BIT0), 0x00);
    }

    // KP+KI = MAX in FLD Auto Mode
    ScalerSetByte(PE7_C6_U3_FLD_22, 0xFF);
    ScalerSetBit(PE7_C7_U3_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(PE7_AA_FLD_KICO_B02, 0x00);
    ScalerSetByte(PE7_AC_FLD_KICO_B04, 0x00);
    ScalerSetByte(PE7_CD_FLD_KICO_B09, 0x00);
    ScalerSetByte(PE7_CF_FLD_KICO_B11, 0x00);
    */

    // Enable Direct Modulation Mode
    ScalerSetBit(PE8_25_KP_PATH_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // manual mode icp_band
    ScalerSetBit(PE7_CE_FLD_KICO_B14, ~_BIT0, _BIT0);

    // Max Icp
    ScalerSetBit(PE7_87_DP_FLD_23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(PE7_86_DP_FLD_22, 0xFF);

    ScalerDpPhyRx2SetDFEInitial(enumDpLinkRate);

    switch(enumDpLinkRate)
    {
        case _DP_LINK_UHBR20:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0x110 (10G in 5~10G)
            ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            ScalerSetByte(PE7_95_DP_FLD_36, 0x10);
            ScalerSetByte(PE7_96_DP_FLD_37, 0x10);
            ScalerSetByte(PE7_97_DP_FLD_38, 0x10);
            ScalerSetByte(PE7_98_DP_FLD_39, 0x10);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 1250    = 2 *    27     *  10000/16  /  27

            // divid num = 27 = 0x1B
            ScalerSetByte(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));

            // ref_cnt = 1250 = 0x4E2
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte(PE7_7B_DP_FLD_11, 0xE2);
            ScalerSetByte(PE7_7D_DP_FLD_13, 0xE2);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 10000 = 14.318  * 2 * (345 + 4) --> N = 0x159
            ScalerSetBit(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetByte(PE8_57_PLL_3, 0x59);
            ScalerSetByte(PE8_58_PLL_4, 0x59);
            ScalerSetByte(PE8_59_PLL_5, 0x59);
            ScalerSetByte(PE8_5A_PLL_6, 0x59);

            // ideal 20G
            g_pusDpPhyRx2ClockTarget[0] = 0x90AD;

            // peak @10G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xF0);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x00);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x10);

            // reg_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), 0x00);

            // reg_cdr_cp
            ScalerSetByte(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_UHBR20());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_UHBR20());
            ScalerSetByte(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_UHBR20());
            /*
            ScalerSetByte(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            ScalerSetByte(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR20));
            */
            // reg_slope_band = KVCO
            ScalerSetBit(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR20() >> 1);
            ScalerSetBit(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR20() >> 1);
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR20());
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR20());

            break;

        case _DP_LINK_UHBR13_5:

            // Sel_DIV = 3'b000 (10-20G)
            ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0x100 (6.75G in 5~10G)
            ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            ScalerSetByte(PE7_95_DP_FLD_36, 0x00);
            ScalerSetByte(PE7_96_DP_FLD_37, 0x00);
            ScalerSetByte(PE7_97_DP_FLD_38, 0x00);
            ScalerSetByte(PE7_98_DP_FLD_39, 0x00);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 500     = 2 *    16     *   6750/16  /  27

            // divid num = 16 = 0x10
            ScalerSetByte(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // ref_cnt = 500 = 0x1F4
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte(PE7_7B_DP_FLD_11, 0xF4);
            ScalerSetByte(PE7_7D_DP_FLD_13, 0xF4);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 6750 =  14.318  * 2 * (232 + 4) --> N = 0x0E8
            ScalerSetBit(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(PE8_57_PLL_3, 0xE8);
            ScalerSetByte(PE8_58_PLL_4, 0xE8);
            ScalerSetByte(PE8_59_PLL_5, 0xE8);
            ScalerSetByte(PE8_5A_PLL_6, 0xE8);

            // ideal 13.5G
            g_pusDpPhyRx2ClockTarget[0] = 0x61A8;

            // peak @6.75G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT1 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xE1);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x01);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x11);

            // reg_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), 0x00);

            // reg_cdr_cp
            ScalerSetByte(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_UHBR13P5());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_UHBR13P5());
            ScalerSetByte(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_UHBR13P5());
            /*
            ScalerSetByte(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            ScalerSetByte(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR13_5));
            */
            // reg_slope_band = KVCO
            ScalerSetBit(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR13P5() >> 1);
            ScalerSetBit(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR13P5() >> 1);
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR13P5());
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR13P5());

            break;

        case _DP_LINK_UHBR10:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0x120 (10G in 5~10G)
            ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte(PE7_95_DP_FLD_36, 0x90);
            ScalerSetByte(PE7_96_DP_FLD_37, 0x90);
            ScalerSetByte(PE7_97_DP_FLD_38, 0x90);
            ScalerSetByte(PE7_98_DP_FLD_39, 0x90);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 625    = 2 *    27     *  5000/16  /  27

            // divid num = 27 = 0x1B
            ScalerSetByte(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));

            // ref_cnt = 625 = 0x271
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetByte(PE7_7B_DP_FLD_11, 0x71);
            ScalerSetByte(PE7_7D_DP_FLD_13, 0x71);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 5000 = 14.318  * 2 * (171 + 4) --> N = 0xAB
            ScalerSetBit(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(PE8_57_PLL_3, 0xAB);
            ScalerSetByte(PE8_58_PLL_4, 0xAB);
            ScalerSetByte(PE8_59_PLL_5, 0xAB);
            ScalerSetByte(PE8_5A_PLL_6, 0xAB);

            // ideal 10G
            g_pusDpPhyRx2ClockTarget[0] = 0x4857;

            // peak @5G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xA2);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x1B);

            // reg_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), _BIT4);

            // reg_cdr_cp
            ScalerSetByte(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_UHBR10());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_UHBR10());
            ScalerSetByte(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_UHBR10());
            /*
            ScalerSetByte(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            ScalerSetByte(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_UHBR10));
            */
            // reg_slope_band = KVCO
            ScalerSetBit(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR10() >> 1);
            ScalerSetBit(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_UHBR10() >> 1);
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR10());
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_UHBR10());

            break;

        case _DP_LINK_HBR3_9G:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0xD0 (4.5G in 2.5~5G)
            ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte(PE7_95_DP_FLD_36, 0xD0);
            ScalerSetByte(PE7_96_DP_FLD_37, 0xD0);
            ScalerSetByte(PE7_97_DP_FLD_38, 0xD0);
            ScalerSetByte(PE7_98_DP_FLD_39, 0xD0);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 500     = 2 *    24     *   4500/16  /  27

            // divid num = 24 = 0x18
            ScalerSetByte(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // ref_cnt = 500 = 0x1F4
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte(PE7_7B_DP_FLD_11, 0xF4);
            ScalerSetByte(PE7_7D_DP_FLD_13, 0xF4);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 4500 = 14.318  * 2 * (153 + 4) --> N = 0x099
            ScalerSetBit(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(PE8_57_PLL_3, 0x99);
            ScalerSetByte(PE8_58_PLL_4, 0x99);
            ScalerSetByte(PE8_59_PLL_5, 0x99);
            ScalerSetByte(PE8_5A_PLL_6, 0x99);

            // ideal 9G
            g_pusDpPhyRx2ClockTarget[0] = 0x411B;

            // peak @5G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xE2);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x13);

            // reg_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), _BIT4);

            // reg_cdr_cp
            ScalerSetByte(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_HBR3());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_HBR3());
            ScalerSetByte(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_HBR3());
            /*
            ScalerSetByte(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            */
            // reg_slope_band = KVCO
            ScalerSetBit(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR3() >> 1);
            ScalerSetBit(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR3() >> 1);
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR3());
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR3());

            break;

        case _DP_LINK_HBR3:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0xD0 (4.05G in 2.5~5G)
            ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte(PE7_95_DP_FLD_36, 0xD0);
            ScalerSetByte(PE7_96_DP_FLD_37, 0xD0);
            ScalerSetByte(PE7_97_DP_FLD_38, 0xD0);
            ScalerSetByte(PE7_98_DP_FLD_39, 0xD0);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 300     = 2 *    16     *   4050/16  /  27

            // divid num = 16 = 0x10
            ScalerSetByte(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            // ref_cnt = 300 = 0x12C
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte(PE7_7B_DP_FLD_11, 0x2C);
            ScalerSetByte(PE7_7D_DP_FLD_13, 0x2C);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 4050 = 14.318  * 2 * (137 + 4) --> N = 0x089
            ScalerSetBit(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(PE8_57_PLL_3, 0x89);
            ScalerSetByte(PE8_58_PLL_4, 0x89);
            ScalerSetByte(PE8_59_PLL_5, 0x89);
            ScalerSetByte(PE8_5A_PLL_6, 0x89);

            // ideal 8.1G
            g_pusDpPhyRx2ClockTarget[0] = 0x3A98;

            // peak @5G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xE2);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x03);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x1B);

            // reg_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), _BIT4);

            // reg_cdr_cp
            ScalerSetByte(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_HBR3());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_HBR3());
            ScalerSetByte(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_HBR3());
            /*
            ScalerSetByte(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            ScalerSetByte(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_HBR3));
            */
            // reg_slope_band = KVCO
            ScalerSetBit(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR3() >> 1);
            ScalerSetBit(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR3() >> 1);
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR3());
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR3());

            break;

        case _DP_LINK_HBR2:

            // Sel_DIV = 3'b000 (5-10G)
            ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FLD Initial Band = 0x70 (2.7G in 2.5~5G)
            ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte(PE7_95_DP_FLD_36, 0x70);
            ScalerSetByte(PE7_96_DP_FLD_37, 0x70);
            ScalerSetByte(PE7_97_DP_FLD_38, 0x70);
            ScalerSetByte(PE7_98_DP_FLD_39, 0x70);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 300     = 2 *    24     *   2700/16  /  27

            // divid num = 24 = 0x18
            ScalerSetByte(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // ref_cnt = 300 = 0x12C
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte(PE7_7B_DP_FLD_11, 0x2C);
            ScalerSetByte(PE7_7D_DP_FLD_13, 0x2C);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
            ScalerSetBit(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(PE8_57_PLL_3, 0x5A);
            ScalerSetByte(PE8_58_PLL_4, 0x5A);
            ScalerSetByte(PE8_59_PLL_5, 0x5A);
            ScalerSetByte(PE8_5A_PLL_6, 0x5A);

            // ideal 5.4G
            g_pusDpPhyRx2ClockTarget[0] = 0x2710;

            // peak @2.7G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT1));
            ScalerSetByte(PE8_35_LE_MODE_1, 0xC4);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x07);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x0F);

            // reg_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // reg_cdr_cp
            ScalerSetByte(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_HBR2());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_HBR2());
            ScalerSetByte(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_HBR2());
            /*
            ScalerSetByte(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            ScalerSetByte(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_HBR2));
            */
            // reg_slope_band = KVCO
            ScalerSetBit(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR2() >> 1);
            ScalerSetBit(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR2() >> 1);
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR2());
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR2());

            break;

        case _DP_LINK_HBR:

            // Sel_DIV = 3'b001 (2.5-5G)
            ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

            // FLD Initial Band = 0x70 (2.7G in 2.5~5G)
            ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte(PE7_95_DP_FLD_36, 0x70);
            ScalerSetByte(PE7_96_DP_FLD_37, 0x70);
            ScalerSetByte(PE7_97_DP_FLD_38, 0x70);
            ScalerSetByte(PE7_98_DP_FLD_39, 0x70);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 300     = 2 *    24     *   2700/16  /  27

            // divid num = 24 = 0x18
            ScalerSetByte(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);

            // ref_cnt = 300 = 0x12C
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte(PE7_7B_DP_FLD_11, 0x2C);
            ScalerSetByte(PE7_7D_DP_FLD_13, 0x2C);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
            ScalerSetBit(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(PE8_57_PLL_3, 0x5A);
            ScalerSetByte(PE8_58_PLL_4, 0x5A);
            ScalerSetByte(PE8_59_PLL_5, 0x5A);
            ScalerSetByte(PE8_5A_PLL_6, 0x5A);

            // ideal 2.7G
            g_pusDpPhyRx2ClockTarget[0] = 0x1388;

            // peak @1.35G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte(PE8_35_LE_MODE_1, 0x86);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x0F);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x0F);

            // reg_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // reg_cdr_cp
            ScalerSetByte(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_HBR());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_HBR());
            ScalerSetByte(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_HBR());
            /*
            ScalerSetByte(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            ScalerSetByte(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_HBR));
            */
            // reg_slope_band = KVCO
            ScalerSetBit(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR() >> 1);
            ScalerSetBit(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_HBR() >> 1);
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR());
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_HBR());

            break;

        case _DP_LINK_RBR:
        default:

            // Sel_DIV = 3'b010 (1.25-2.5G)
            ScalerSetBit(PE8_16_CLOCK_DIV_2, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

            // FLD Initial Band = 0x90 (3.24G in 2.5~5G)
            ScalerSetBit(PE7_94_DP_FLD_35, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte(PE7_95_DP_FLD_36, 0x90);
            ScalerSetByte(PE7_96_DP_FLD_37, 0x90);
            ScalerSetByte(PE7_97_DP_FLD_38, 0x90);
            ScalerSetByte(PE7_98_DP_FLD_39, 0x90);

            // ref_cnt = 2 * divid_num * target_freq/ref_clock
            // 405     = 2 *    27     *   3240/16  /  27

            // divid num = 27 = 0x1B
            ScalerSetByte(PE7_81_DP_FLD_17, 0x01);
            ScalerSetBit(PE7_82_DP_FLD_18, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));

            // ref_cnt = 405 = 0x195
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetByte(PE7_7B_DP_FLD_11, 0x95);
            ScalerSetByte(PE7_7D_DP_FLD_13, 0x95);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 3240 =  14.318  * 2 * (109 + 4) --> N = 0x06D
            ScalerSetBit(PE8_56_PLL_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(PE8_57_PLL_3, 0x6D);
            ScalerSetByte(PE8_58_PLL_4, 0x6D);
            ScalerSetByte(PE8_59_PLL_5, 0x6D);
            ScalerSetByte(PE8_5A_PLL_6, 0x6D);

            // ideal 1.62G
            g_pusDpPhyRx2ClockTarget[0] = 0xBB8;

            // peak @1.35G
            ScalerSetBit(PE8_34_LE_PEAKING, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerSetByte(PE8_35_LE_MODE_1, 0x86);
            ScalerSetByte(PE8_36_LE_MODE_2, 0x0F);
            ScalerSetByte(PE8_37_LE_MODE_3, 0x0F);

            // reg_cco_neq_iptat = 2'b10 --> -25%
            ScalerSetBit(PE8_29_IPTAT_1, ~(_BIT5 | _BIT4), _BIT5);

            // reg_cdr_cp
            ScalerSetByte(PE7_85_DP_FLD_21, GET_DP_PHY_RX2_ICP_RBR());

            // reg_slope_icp_band = Icp_kp
            ScalerSetByte(PE7_C5_FLD_KICO_B05, GET_DP_PHY_RX2_ICP_KP_RBR());
            ScalerSetByte(PE7_C6_FLD_KICO_B06, GET_DP_PHY_RX2_ICP_KP_RBR());
            /*
            ScalerSetByte(PE7_C0_FLD_KICO_B00, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_C1_FLD_KICO_B01, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_C2_FLD_KICO_B02, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_C3_FLD_KICO_B03, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_C4_FLD_KICO_B04, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_C7_FLD_KICO_B07, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_C8_FLD_KICO_B08, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_C9_FLD_KICO_B09, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_CA_FLD_KICO_B10, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            ScalerSetByte(PE7_CB_FLD_KICO_B11, (0xFF - _DP_PHY_RX2_ICP_KP_RBR));
            */

            // reg_slope_band = KVCO
            ScalerSetBit(PE7_71_DP_FLD_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_RBR() >> 1);
            ScalerSetBit(PE7_7A_DP_FLD_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX2_KVCO_RBR() >> 1);
            ScalerSetBit(PE7_7C_DP_FLD_12, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_RBR());
            ScalerSetBit(PE7_7E_DP_FLD_14, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), GET_DP_PHY_RX2_KVCO_RBR());
            break;
    }
}
#endif // End of #if(_D2_DP_SUPPORT == _ON)

