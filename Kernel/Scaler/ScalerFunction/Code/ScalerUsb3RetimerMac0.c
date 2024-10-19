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
// ID Code      : ScalerUsb3RetimerMac0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Usb3RetimerMac0/ScalerUsb3RetimerMac0.h"

#if(_USB3_RETIMER_MAC0_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
bit g_bUsb3RetimerMac0U3stateEntry = _FALSE;
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
bit g_bUsb3RetimerMac0U2stateEntry = _FALSE;
bit g_bUsb3RetimerMac0U1stateEntry = _FALSE;
#endif
#endif
#if (_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
bit g_bUsb3RetimerMac0P3Entry = _FALSE;
bit g_bUsb3RetimerMac0P3NSQIntEntry = _FALSE;
BYTE g_ucUsb3RetimerMac0PhyRate = _USB_3_GEN1;
BYTE g_ucUsb3RetimerMac0LaneCount = _USB_3_LANE_X1;
EnumUsb3RetimerP3State g_enumUsb3RetimerMac0P3State = _USB3_RETIMER_NO_ACTION;
#endif
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
BYTE g_ucUsb3RetimerMac0CompliancePattern;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : USB3 Rx0 Retimer Initial
// Input Value  : EnumTypeCOrientation
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0Initial(EnumTypeCOrientation enumOrientation)
{
    // Retimer Mac0 UFP On Region Initial
    ScalerUsb3RetimerMac0UfpOnRegionInitial(enumOrientation);

    // Retimer Mac0 UFP Off Region Initial
    ScalerUsb3RetimerMac0UfpOffRegionInitial(enumOrientation);

    // Retimer Mac0 UFP Off Region U3_Exit Related Initial
    ScalerUsb3RetimerMac0UfpOffRegionU3ExitInitial();

    // Retimer Mac0 DFP On Region Initial
    ScalerUsb3RetimerMac0DfpOnRegionInitial();

    // Retimer Mac0 DFP Off Region Initial
    ScalerUsb3RetimerMac0DfpOffRegionInitial();

    // Retimer Mac0 DFP Off Region U3_Exit Related Initial
    ScalerUsb3RetimerMac0DfpOffRegionU3ExitInitial();

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
    // Clear P3 Status Marco
    SET_USB3_RETIMER_P3_STATUS(_USB3_RETIMER_NO_ACTION);
    g_bUsb3RetimerMac0P3Entry = _FALSE;
    g_bUsb3RetimerMac0P3NSQIntEntry = _FALSE;
#endif
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer UFP Mac Initial at On Region
// Input Value  : EnumTypeCOrientation
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0UfpOnRegionInitial(EnumTypeCOrientation enumOrientation)
{
    // Retimer UFP Setting TypeC Orienation
    if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        // RTSSM Lane Switch & write protect [7][3]
        ScalerSetBit(P3B_0A_RTSSM_FLAG_00, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT3));
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
        {
            // PIPE0 To Lane Switch - UnFlip
            ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~_BIT1, 0x00);
        }
        else
        {
            // PIPE1 To Lane Switch - UnFlip
            ScalerSetBit(P81_D6_PIPE_CONTROL_U_06, ~_BIT1, 0x00);
        }
#else
        // PIPE0 To Lane Switch - UnFlip
        ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~_BIT1, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
        DebugMessageTypeC("9. [USB] [Retimer] Set Retimer(RTSSM) by TypeC UFP UnFlip", enumOrientation);
    }
    else if(enumOrientation == _TYPE_C_ORIENTATION_FLIP)
    {
        // RTSSM Lane Switch & write protect [7][3]
        ScalerSetBit(P3B_0A_RTSSM_FLAG_00, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5 | _BIT4 | _BIT3));
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
        {
            // PIPE0 To Lane Switch - Flip
            ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~_BIT1, _BIT1);
        }
        else
        {
            // PIPE1 To Lane Switch - Flip
            ScalerSetBit(P81_D6_PIPE_CONTROL_U_06, ~_BIT1, _BIT1);
        }
#else
        // PIPE0 To Lane Switch - Flip
        ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~_BIT1, _BIT1);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif
        DebugMessageTypeC("9. [USB] [Retimer] Set Retimer(RTSSM) by TypeC UFP Flip", enumOrientation);
    }

    // RTSSM Global Setting : Set U0toReco(BothSide) [3:2]
    ScalerSetBit(P3B_00_RTSSM_GLOBAL_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // RTSSM Global Setting : (Default) U/D eq_training_timing
    // [5]UFP : 1'b0 EQ_State (UFP NSQ Only Active At One Lane)
    // [2]DFP : 1'b0 EQ_State
    ScalerSetBit(P3B_05_RTSSM_GLOBAL_05, ~(_BIT5 | _BIT2), 0x00);

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
    // Enable LFPS Global Enable
    ScalerSetBit(P3B_07_RTSSM_GLOBAL_07, ~_BIT2, _BIT2);
#endif

#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
    // Disable cmd_rx_eq_training Reference LFPS-EI_Timeout at Polling.RxEQ State
    // To avoid the TSEQ LinkTraining Fail by eq_training_done  =1 after PollingRxEQ State received Warm Reset, Before ECO#1737
    ScalerSetBit(P3B_05_RTSSM_GLOBAL_05, ~(_BIT1 | _BIT0), 0x00);
#endif // End of (_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)

    // RTSSM Condition : Enable Compliance (Default)
    ScalerSetBit(P3B_0B_RTSSM_STATE_CONTROL_00, ~_BIT1, _BIT1);

    // RTSSM Condition : RxDetect to Speeddetect when Both Side Detect Polling.LFPS : 2'b00
    ScalerSetBit(P3B_0E_RTSSM_STATE_CONTROL_03, ~(_BIT7 | _BIT6), 0x00);

    // RTSSM Condition : Speeddetect to Polling.RxEQ When Any Side 60us_EI_Timeout : 2'b01
    ScalerSetBit(P3B_0E_RTSSM_STATE_CONTROL_03, ~(_BIT4 | _BIT3), _BIT3);

    // RTSSM Condition : Polling/Recovery.TSx to Idle / Idle to U0 State Condition by monitor Tx/Rx Handshake Condition
    ScalerSetByte(P3B_0F_RTSSM_STATE_CONTROL_04, 0x00);

    // Switch to Local Loopback and set early enter local loopback
    ScalerSetBit(P3B_10_RTSSM_STATE_CONTROL_05, ~_BIT0, _BIT0);

    // Set PM_ENTRY_TIMER to 10us (To avoid Timer Missmatch with Hub) 8us + 2us
    ScalerSetByte(P3B_AD_TIMER_CNT_LIST_13, 0x0A);

    //--------------------------------------------------
    // Gen1 Aphy Pre/Post Paramenter Setting
    //--------------------------------------------------

    // Pipe0
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // [7:6] u3_normal_deemp_tx0_u => Normal Data
    ScalerSetBit(P3B_CE_PIPE_TXDEEMP_TX0_G1, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit(P3B_CF_PIPE_TXDEEMP_TX1_G1, ~(_BIT7 | _BIT6), _BIT6);

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // [7:6] u3_normal_deemp_tx0_u => Normal Data
    ScalerSetBit(P3B_CE_PIPE_TXDEEMP_TX0_G1, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(P3B_CF_PIPE_TXDEEMP_TX1_G1, ~(_BIT7 | _BIT6), _BIT7);

#endif

    // [5:4] u3_en_deemp_tx0_u => CP5/7
    ScalerSetBit(P3B_CE_PIPE_TXDEEMP_TX0_G1, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit(P3B_CF_PIPE_TXDEEMP_TX1_G1, ~(_BIT5 | _BIT4), _BIT4);

    // [3:2] u3_dis_deemp_tx0_u => CP6/8
    ScalerSetBit(P3B_CE_PIPE_TXDEEMP_TX0_G1, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit(P3B_CF_PIPE_TXDEEMP_TX1_G1, ~(_BIT3 | _BIT2), _BIT3);

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // Pipe1
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // [7:6] u3_normal_deemp_tx0_u => Normal Data
    ScalerSetBit(P81_DE_PIPE_TXDEEMP_TX0_G1, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit(P81_DF_PIPE_TXDEEMP_TX1_G1, ~(_BIT7 | _BIT6), _BIT6);

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // [7:6] u3_normal_deemp_tx0_u => Normal Data
    ScalerSetBit(P81_DE_PIPE_TXDEEMP_TX0_G1, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetBit(P81_DF_PIPE_TXDEEMP_TX1_G1, ~(_BIT7 | _BIT6), _BIT7);

#endif

    // [5:4] u3_en_deemp_tx0_u => CP5/7
    ScalerSetBit(P81_DE_PIPE_TXDEEMP_TX0_G1, ~(_BIT5 | _BIT4), _BIT4);
    ScalerSetBit(P81_DF_PIPE_TXDEEMP_TX1_G1, ~(_BIT5 | _BIT4), _BIT4);

    // [3:2] u3_dis_deemp_tx0_u => CP6/8
    ScalerSetBit(P81_DE_PIPE_TXDEEMP_TX0_G1, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit(P81_DF_PIPE_TXDEEMP_TX1_G1, ~(_BIT3 | _BIT2), _BIT3);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

    //--------------------------------------------------
    // Gen2 Aphy Pre/Post Paramenter Setting
    //--------------------------------------------------

#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)

    // Pipe0
    // [5:0] deemp_norm_cn1_tx0_u => Normal Data => Pre = 0x22
    // [5:0] deemp_norm_c0_tx0_u => Normal Data => Main = 0x30
    // [5:0] deemp_norm_cp1_tx0_u => Normal Data => Post => 0x16
    ScalerSetByte(P3B_D0_PIPE_TXDEEMP_NORM_CN1_TX0_G2, 0x22);
    ScalerSetByte(P3B_D1_PIPE_TXDEEMP_NORM_C0_TX0_G2, 0x30);
    ScalerSetByte(P3B_D2_PIPE_TXDEEMP_NORM_CP1_TX0_G2, 0x16);
    ScalerSetByte(P3B_E0_PIPE_TXDEEMP_NORM_CN1_TX1_G2, 0x22);
    ScalerSetByte(P3B_E1_PIPE_TXDEEMP_NORM_C0_TX1_G2, 0x30);
    ScalerSetByte(P3B_E2_PIPE_TXDEEMP_NORM_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp13_cn1_tx0_u => CP13 => Pre = 0x22
    // [5:0] deemp_cp13_c0_tx0_u => CP13 => Main = 0x30
    // [5:0] deemp_cp13_cp1_tx0_u => CP13 => Post => 0x00
    ScalerSetByte(P3B_D4_PIPE_TXDEEMP_CP13_CN1_TX0_G2, 0x22);
    ScalerSetByte(P3B_D5_PIPE_TXDEEMP_CP13_C0_TX0_G2, 0x30);
    ScalerSetByte(P3B_D6_PIPE_TXDEEMP_CP13_CP1_TX0_G2, 0x00);
    ScalerSetByte(P3B_E4_PIPE_TXDEEMP_CP13_CN1_TX1_G2, 0x22);
    ScalerSetByte(P3B_E5_PIPE_TXDEEMP_CP13_C0_TX1_G2, 0x30);
    ScalerSetByte(P3B_E6_PIPE_TXDEEMP_CP13_CP1_TX1_G2, 0x00);

    // [5:0] deemp_cp14_cn1_tx0_u => CP14 => Pre = 0x00
    // [5:0] deemp_cp14_c0_tx0_u => CP14 => Main = 0x30
    // [5:0] deemp_cp14_cp1_tx0_u => CP14 => Post => 0x16
    ScalerSetByte(P3B_D7_PIPE_TXDEEMP_CP14_CN1_TX0_G2, 0x00);
    ScalerSetByte(P3B_D8_PIPE_TXDEEMP_CP14_C0_TX0_G2, 0x30);
    ScalerSetByte(P3B_D9_PIPE_TXDEEMP_CP14_CP1_TX0_G2, 0x16);
    ScalerSetByte(P3B_E7_PIPE_TXDEEMP_CP14_CN1_TX1_G2, 0x00);
    ScalerSetByte(P3B_E8_PIPE_TXDEEMP_CP14_C0_TX1_G2, 0x30);
    ScalerSetByte(P3B_E9_PIPE_TXDEEMP_CP14_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp15_cn1_tx0_u => CP15 => Pre = 0x22
    // [5:0] deemp_cp15_c0_tx0_u => CP15 => Main = 0x30
    // [5:0] deemp_cp15_cp1_tx0_u => CP15 => Post => 0x16
    ScalerSetByte(P3B_DA_PIPE_TXDEEMP_CP15_CN1_TX0_G2, 0x22);
    ScalerSetByte(P3B_DB_PIPE_TXDEEMP_CP15_C0_TX0_G2, 0x30);
    ScalerSetByte(P3B_DC_PIPE_TXDEEMP_CP15_CP1_TX0_G2, 0x16);
    ScalerSetByte(P3B_EA_PIPE_TXDEEMP_CP15_CN1_TX1_G2, 0x22);
    ScalerSetByte(P3B_EB_PIPE_TXDEEMP_CP15_C0_TX1_G2, 0x30);
    ScalerSetByte(P3B_EC_PIPE_TXDEEMP_CP15_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp16_cn1_tx0_u => CP116 => Pre = 0x00
    // [5:0] deemp_cp16_c0_tx0_u => CP16 => Main = 0x30
    // [5:0] deemp_cp16_cp1_tx0_u => CP16 => Post => 0x00
    ScalerSetByte(P3B_DD_PIPE_TXDEEMP_CP16_CN1_TX0_G2, 0x00);
    ScalerSetByte(P3B_DE_PIPE_TXDEEMP_CP16_C0_TX0_G2, 0x30);
    ScalerSetByte(P3B_DF_PIPE_TXDEEMP_CP16_CP1_TX0_G2, 0x00);
    ScalerSetByte(P3B_ED_PIPE_TXDEEMP_CP16_CN1_TX1_G2, 0x00);
    ScalerSetByte(P3B_EE_PIPE_TXDEEMP_CP16_C0_TX1_G2, 0x30);
    ScalerSetByte(P3B_EF_PIPE_TXDEEMP_CP16_CP1_TX1_G2, 0x00);

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // Pipe1
    // [5:0] deemp_norm_cn1_tx0_u => Normal Data => Pre = 0x22
    // [5:0] deemp_norm_c0_tx0_u => Normal Data => Main = 0x30
    // [5:0] deemp_norm_cp1_tx0_u => Normal Data => Post => 0x16
    ScalerSetByte(P81_E0_PIPE_TXDEEMP_NORM_CN1_TX0_G2, 0x22);
    ScalerSetByte(P81_E1_PIPE_TXDEEMP_NORM_C0_TX0_G2, 0x30);
    ScalerSetByte(P81_E2_PIPE_TXDEEMP_NORM_CP1_TX0_G2, 0x16);
    ScalerSetByte(P81_F0_PIPE_TXDEEMP_NORM_CN1_TX1_G2, 0x22);
    ScalerSetByte(P81_F1_PIPE_TXDEEMP_NORM_C0_TX1_G2, 0x30);
    ScalerSetByte(P81_F2_PIPE_TXDEEMP_NORM_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp13_cn1_tx0_u => CP13 => Pre = 0x22
    // [5:0] deemp_cp13_c0_tx0_u => CP13 => Main = 0x30
    // [5:0] deemp_cp13_cp1_tx0_u => CP13 => Post => 0x00
    ScalerSetByte(P81_E4_PIPE_TXDEEMP_CP13_CN1_TX0_G2, 0x22);
    ScalerSetByte(P81_E5_PIPE_TXDEEMP_CP13_C0_TX0_G2, 0x30);
    ScalerSetByte(P81_E6_PIPE_TXDEEMP_CP13_CP1_TX0_G2, 0x00);
    ScalerSetByte(P81_F4_PIPE_TXDEEMP_CP13_CN1_TX1_G2, 0x22);
    ScalerSetByte(P81_F5_PIPE_TXDEEMP_CP13_C0_TX1_G2, 0x30);
    ScalerSetByte(P81_F6_PIPE_TXDEEMP_CP13_CP1_TX1_G2, 0x00);

    // [5:0] deemp_cp14_cn1_tx0_u => CP14 => Pre = 0x00
    // [5:0] deemp_cp14_c0_tx0_u => CP14 => Main = 0x30
    // [5:0] deemp_cp14_cp1_tx0_u => CP14 => Post => 0x16
    ScalerSetByte(P81_E7_PIPE_TXDEEMP_CP14_CN1_TX0_G2, 0x00);
    ScalerSetByte(P81_E8_PIPE_TXDEEMP_CP14_C0_TX0_G2, 0x30);
    ScalerSetByte(P81_E9_PIPE_TXDEEMP_CP14_CP1_TX0_G2, 0x16);
    ScalerSetByte(P81_F7_PIPE_TXDEEMP_CP14_CN1_TX1_G2, 0x00);
    ScalerSetByte(P81_F8_PIPE_TXDEEMP_CP14_C0_TX1_G2, 0x30);
    ScalerSetByte(P81_F9_PIPE_TXDEEMP_CP14_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp15_cn1_tx0_u => CP15 => Pre = 0x22
    // [5:0] deemp_cp15_c0_tx0_u => CP15 => Main = 0x30
    // [5:0] deemp_cp15_cp1_tx0_u => CP15 => Post => 0x16
    ScalerSetByte(P81_EA_PIPE_TXDEEMP_CP15_CN1_TX0_G2, 0x22);
    ScalerSetByte(P81_EB_PIPE_TXDEEMP_CP15_C0_TX0_G2, 0x30);
    ScalerSetByte(P81_EC_PIPE_TXDEEMP_CP15_CP1_TX0_G2, 0x16);
    ScalerSetByte(P81_FA_PIPE_TXDEEMP_CP15_CN1_TX1_G2, 0x22);
    ScalerSetByte(P81_FB_PIPE_TXDEEMP_CP15_C0_TX1_G2, 0x30);
    ScalerSetByte(P81_FC_PIPE_TXDEEMP_CP15_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp16_cn1_tx0_u => CP116 => Pre = 0x00
    // [5:0] deemp_cp16_c0_tx0_u => CP16 => Main = 0x30
    // [5:0] deemp_cp16_cp1_tx0_u => CP16 => Post => 0x00
    ScalerSetByte(P81_ED_PIPE_TXDEEMP_CP16_CN1_TX0_G2, 0x00);
    ScalerSetByte(P81_EE_PIPE_TXDEEMP_CP16_C0_TX0_G2, 0x30);
    ScalerSetByte(P81_EF_PIPE_TXDEEMP_CP16_CP1_TX0_G2, 0x00);
    ScalerSetByte(P81_FD_PIPE_TXDEEMP_CP16_CN1_TX1_G2, 0x00);
    ScalerSetByte(P81_FE_PIPE_TXDEEMP_CP16_C0_TX1_G2, 0x30);
    ScalerSetByte(P81_FF_PIPE_TXDEEMP_CP16_CP1_TX1_G2, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)

    // Pipe0
    // [5:0] deemp_norm_cn1_tx0_u => Normal Data => Pre = 0x22
    // [5:0] deemp_norm_c0_tx0_u => Normal Data => Main = 0x3F
    // [5:0] deemp_norm_cp1_tx0_u => Normal Data => Post => 0x16
    ScalerSetByte(P3B_D0_PIPE_TXDEEMP_NORM_CN1_TX0_G2, 0x22);
    ScalerSetByte(P3B_D1_PIPE_TXDEEMP_NORM_C0_TX0_G2, 0x3F);
    ScalerSetByte(P3B_D2_PIPE_TXDEEMP_NORM_CP1_TX0_G2, 0x16);
    ScalerSetByte(P3B_E0_PIPE_TXDEEMP_NORM_CN1_TX1_G2, 0x22);
    ScalerSetByte(P3B_E1_PIPE_TXDEEMP_NORM_C0_TX1_G2, 0x3F);
    ScalerSetByte(P3B_E2_PIPE_TXDEEMP_NORM_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp13_cn1_tx0_u => CP13 => Pre = 0x22
    // [5:0] deemp_cp13_c0_tx0_u => CP13 => Main = 0x3F
    // [5:0] deemp_cp13_cp1_tx0_u => CP13 => Post => 0x00
    ScalerSetByte(P3B_D4_PIPE_TXDEEMP_CP13_CN1_TX0_G2, 0x22);
    ScalerSetByte(P3B_D5_PIPE_TXDEEMP_CP13_C0_TX0_G2, 0x3F);
    ScalerSetByte(P3B_D6_PIPE_TXDEEMP_CP13_CP1_TX0_G2, 0x00);
    ScalerSetByte(P3B_E4_PIPE_TXDEEMP_CP13_CN1_TX1_G2, 0x22);
    ScalerSetByte(P3B_E5_PIPE_TXDEEMP_CP13_C0_TX1_G2, 0x3F);
    ScalerSetByte(P3B_E6_PIPE_TXDEEMP_CP13_CP1_TX1_G2, 0x00);

    // [5:0] deemp_cp14_cn1_tx0_u => CP14 => Pre = 0x00
    // [5:0] deemp_cp14_c0_tx0_u => CP14 => Main = 0x3F
    // [5:0] deemp_cp14_cp1_tx0_u => CP14 => Post => 0x16
    ScalerSetByte(P3B_D7_PIPE_TXDEEMP_CP14_CN1_TX0_G2, 0x00);
    ScalerSetByte(P3B_D8_PIPE_TXDEEMP_CP14_C0_TX0_G2, 0x3F);
    ScalerSetByte(P3B_D9_PIPE_TXDEEMP_CP14_CP1_TX0_G2, 0x16);
    ScalerSetByte(P3B_E7_PIPE_TXDEEMP_CP14_CN1_TX1_G2, 0x00);
    ScalerSetByte(P3B_E8_PIPE_TXDEEMP_CP14_C0_TX1_G2, 0x3F);
    ScalerSetByte(P3B_E9_PIPE_TXDEEMP_CP14_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp15_cn1_tx0_u => CP15 => Pre = 0x22
    // [5:0] deemp_cp15_c0_tx0_u => CP15 => Main = 0x3F
    // [5:0] deemp_cp15_cp1_tx0_u => CP15 => Post => 0x16
    ScalerSetByte(P3B_DA_PIPE_TXDEEMP_CP15_CN1_TX0_G2, 0x22);
    ScalerSetByte(P3B_DB_PIPE_TXDEEMP_CP15_C0_TX0_G2, 0x3F);
    ScalerSetByte(P3B_DC_PIPE_TXDEEMP_CP15_CP1_TX0_G2, 0x16);
    ScalerSetByte(P3B_EA_PIPE_TXDEEMP_CP15_CN1_TX1_G2, 0x22);
    ScalerSetByte(P3B_EB_PIPE_TXDEEMP_CP15_C0_TX1_G2, 0x3F);
    ScalerSetByte(P3B_EC_PIPE_TXDEEMP_CP15_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp16_cn1_tx0_u => CP116 => Pre = 0x00
    // [5:0] deemp_cp16_c0_tx0_u => CP16 => Main = 0x3F
    // [5:0] deemp_cp16_cp1_tx0_u => CP16 => Post => 0x00
    ScalerSetByte(P3B_DD_PIPE_TXDEEMP_CP16_CN1_TX0_G2, 0x00);
    ScalerSetByte(P3B_DE_PIPE_TXDEEMP_CP16_C0_TX0_G2, 0x3F);
    ScalerSetByte(P3B_DF_PIPE_TXDEEMP_CP16_CP1_TX0_G2, 0x00);
    ScalerSetByte(P3B_ED_PIPE_TXDEEMP_CP16_CN1_TX1_G2, 0x00);
    ScalerSetByte(P3B_EE_PIPE_TXDEEMP_CP16_C0_TX1_G2, 0x3F);
    ScalerSetByte(P3B_EF_PIPE_TXDEEMP_CP16_CP1_TX1_G2, 0x00);

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // Pipe1
    // [5:0] deemp_norm_cn1_tx0_u => Normal Data => Pre = 0x22
    // [5:0] deemp_norm_c0_tx0_u => Normal Data => Main = 0x3F
    // [5:0] deemp_norm_cp1_tx0_u => Normal Data => Post => 0x16
    ScalerSetByte(P81_E0_PIPE_TXDEEMP_NORM_CN1_TX0_G2, 0x22);
    ScalerSetByte(P81_E1_PIPE_TXDEEMP_NORM_C0_TX0_G2, 0x3F);
    ScalerSetByte(P81_E2_PIPE_TXDEEMP_NORM_CP1_TX0_G2, 0x16);
    ScalerSetByte(P81_F0_PIPE_TXDEEMP_NORM_CN1_TX1_G2, 0x22);
    ScalerSetByte(P81_F1_PIPE_TXDEEMP_NORM_C0_TX1_G2, 0x3F);
    ScalerSetByte(P81_F2_PIPE_TXDEEMP_NORM_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp13_cn1_tx0_u => CP13 => Pre = 0x22
    // [5:0] deemp_cp13_c0_tx0_u => CP13 => Main = 0x3F
    // [5:0] deemp_cp13_cp1_tx0_u => CP13 => Post => 0x00
    ScalerSetByte(P81_E4_PIPE_TXDEEMP_CP13_CN1_TX0_G2, 0x22);
    ScalerSetByte(P81_E5_PIPE_TXDEEMP_CP13_C0_TX0_G2, 0x3F);
    ScalerSetByte(P81_E6_PIPE_TXDEEMP_CP13_CP1_TX0_G2, 0x00);
    ScalerSetByte(P81_F4_PIPE_TXDEEMP_CP13_CN1_TX1_G2, 0x22);
    ScalerSetByte(P81_F5_PIPE_TXDEEMP_CP13_C0_TX1_G2, 0x3F);
    ScalerSetByte(P81_F6_PIPE_TXDEEMP_CP13_CP1_TX1_G2, 0x00);

    // [5:0] deemp_cp14_cn1_tx0_u => CP14 => Pre = 0x00
    // [5:0] deemp_cp14_c0_tx0_u => CP14 => Main = 0x3F
    // [5:0] deemp_cp14_cp1_tx0_u => CP14 => Post => 0x16
    ScalerSetByte(P81_E7_PIPE_TXDEEMP_CP14_CN1_TX0_G2, 0x00);
    ScalerSetByte(P81_E8_PIPE_TXDEEMP_CP14_C0_TX0_G2, 0x3F);
    ScalerSetByte(P81_E9_PIPE_TXDEEMP_CP14_CP1_TX0_G2, 0x16);
    ScalerSetByte(P81_F7_PIPE_TXDEEMP_CP14_CN1_TX1_G2, 0x00);
    ScalerSetByte(P81_F8_PIPE_TXDEEMP_CP14_C0_TX1_G2, 0x3F);
    ScalerSetByte(P81_F9_PIPE_TXDEEMP_CP14_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp15_cn1_tx0_u => CP15 => Pre = 0x22
    // [5:0] deemp_cp15_c0_tx0_u => CP15 => Main = 0x3F
    // [5:0] deemp_cp15_cp1_tx0_u => CP15 => Post => 0x16
    ScalerSetByte(P81_EA_PIPE_TXDEEMP_CP15_CN1_TX0_G2, 0x22);
    ScalerSetByte(P81_EB_PIPE_TXDEEMP_CP15_C0_TX0_G2, 0x3F);
    ScalerSetByte(P81_EC_PIPE_TXDEEMP_CP15_CP1_TX0_G2, 0x16);
    ScalerSetByte(P81_FA_PIPE_TXDEEMP_CP15_CN1_TX1_G2, 0x22);
    ScalerSetByte(P81_FB_PIPE_TXDEEMP_CP15_C0_TX1_G2, 0x3F);
    ScalerSetByte(P81_FC_PIPE_TXDEEMP_CP15_CP1_TX1_G2, 0x16);

    // [5:0] deemp_cp16_cn1_tx0_u => CP116 => Pre = 0x00
    // [5:0] deemp_cp16_c0_tx0_u => CP16 => Main = 0x3F
    // [5:0] deemp_cp16_cp1_tx0_u => CP16 => Post => 0x00
    ScalerSetByte(P81_ED_PIPE_TXDEEMP_CP16_CN1_TX0_G2, 0x00);
    ScalerSetByte(P81_EE_PIPE_TXDEEMP_CP16_C0_TX0_G2, 0x3F);
    ScalerSetByte(P81_EF_PIPE_TXDEEMP_CP16_CP1_TX0_G2, 0x00);
    ScalerSetByte(P81_FD_PIPE_TXDEEMP_CP16_CN1_TX1_G2, 0x00);
    ScalerSetByte(P81_FE_PIPE_TXDEEMP_CP16_C0_TX1_G2, 0x3F);
    ScalerSetByte(P81_FF_PIPE_TXDEEMP_CP16_CP1_TX1_G2, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif

    // Disable U3S state
    ScalerSetBit(P3B_0C_RTSSM_STATE_CONTROL_01, ~_BIT6, 0x00);

    //--------------------------------------------------
    // Retimer MAC Set Gen 1x1 to 20bits Data Path - On-Region
    //--------------------------------------------------
    // Disable RTSSM : gen1x1_fast_mode_en
    ScalerSetBit(P3B_07_RTSSM_GLOBAL_07, ~_BIT6, 0x00);

    // Disable RTSSM : blr_mode_rxeq_2_tsx_cond_u
    ScalerSetBit(P3B_10_RTSSM_STATE_CONTROL_05, ~_BIT5, 0x00);

    // Disable PIPE0 : gen1_fast_mode_u
    ScalerSetBit(P3B_C4_PIPE_CONTROL_U_04, ~_BIT7, 0x00);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // Disable PIPE1 : gen1_fast_mode_u
    ScalerSetBit(P81_D4_PIPE_CONTROL_U_04, ~_BIT7, 0x00);
#endif
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
    {
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)
        // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
        ScalerSetBit(P96_40_SSC_TX_00, ~_BIT1, 0x00);
#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)
        // UFP0 - [1] reg_ssc_en_tx = 1'b1 => SSC ON
        ScalerSetBit(P96_40_SSC_TX_00, ~_BIT1, _BIT1);
#endif
    }
    else
    {
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)
        // UFP1 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
        ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT1, 0x00);
#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)
        // UFP1 - [1] reg_ssc_en_tx = 1'b1 => SSC ON
        ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT1, _BIT1);
#endif
    }
#else
    // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
    ScalerSetBit(P96_40_SSC_TX_00, ~_BIT1, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        //--------------------------------------------------
        // Retimer MAC Set Gen 1x1 BLR Path - On-Region
        //--------------------------------------------------
        // Enable RTSSM : gen1x1_fast_mode_en
        ScalerSetBit(P3B_07_RTSSM_GLOBAL_07, ~_BIT6, _BIT6);

#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
        // Disable RTSSM : blr_mode_rxeq_2_tsx_cond_u
        // To avoid Polling.RxEQ LinkTraining Fail after TSx.Timeout, Before ECO#1724
        ScalerSetBit(P3B_10_RTSSM_STATE_CONTROL_05, ~_BIT5, 0x00);
#else
        // Enable RTSSM : blr_mode_rxeq_2_tsx_cond_u
        ScalerSetBit(P3B_10_RTSSM_STATE_CONTROL_05, ~_BIT5, _BIT5);
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)

        // Enable PIPE0 : gen1_fast_mode_u
        ScalerSetBit(P3B_C4_PIPE_CONTROL_U_04, ~_BIT7, _BIT7);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        // Enable PIPE1 : gen1_fast_mode_u
        ScalerSetBit(P81_D4_PIPE_CONTROL_U_04, ~_BIT7, _BIT7);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
        {
            // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
            ScalerSetBit(P96_40_SSC_TX_00, ~_BIT1, 0x00);
        }
        else
        {
            // UFP1 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
            ScalerSetBit(PC9_40_SSC_TX_00, ~_BIT1, 0x00);
        }
#else
        // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
        ScalerSetBit(P96_40_SSC_TX_00, ~_BIT1, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    }
#endif // end of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
    //--------------------------------------------------
    // U3 State PowerDown = P3, Low Power Support
    //--------------------------------------------------
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
    {
        // Set UFP0 PIPE U3 PowerDown = P3
        ScalerSetBit(P3B_C4_PIPE_CONTROL_U_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Set UFP0 reg_pclk_sel = 1 : PCLK is aux_clk when P3
        ScalerSetBit(P96_AC_SPPHY_44, ~_BIT6, _BIT6);
    }
    else
    {
        // Set UFP1 reg_pclk_sel = 1 : PCLK is aux_clk when P3
        ScalerSetBit(PC9_AC_SPPHY_44, ~_BIT6, _BIT6);

        // Set UFP1 PIPE U3 PowerDown = P3
        ScalerSetBit(P81_D4_PIPE_CONTROL_U_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
#else
    // Set UFP0 PIPE U3 PowerDown = P3
    ScalerSetBit(P3B_C4_PIPE_CONTROL_U_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    // Set UFP0 reg_pclk_sel = 1 : PCLK is aux_clk when P3
    ScalerSetBit(P96_AC_SPPHY_44, ~_BIT6, _BIT6);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif
#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X1)
    // Set UFP0 Compliance Mode x1 Lane Mode
    ScalerSetBit(P3B_C8_PIPE_CONTROL_U_08, ~(_BIT7 | _BIT3), 0x00);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // Set UFP1 Compliance Mode x1 Lane Mode
    ScalerSetBit(P81_D8_PIPE_CONTROL_U_08, ~(_BIT7 | _BIT3), 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer UFP Mac Initial at Off Region
// Input Value  : EnumTypeCOrientation
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0UfpOffRegionInitial(EnumTypeCOrientation enumOrientation)
{
    // Retimer UFP Setting TypeC Orienation
    if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
        // LFPS Lane Switch
        ScalerSetBit(P3B_20_LANE_SWITCH_U_01, ~(_BIT6 | _BIT4), 0x00);
#endif
        DebugMessageTypeC("9. [USB] [Retimer] Set Retimer(LFPS) by TypeC UFP UnFlip", enumOrientation);
    }
    else if(enumOrientation == _TYPE_C_ORIENTATION_FLIP)
    {
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
        // LFPS Lane Switch
        ScalerSetBit(P3B_20_LANE_SWITCH_U_01, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
#endif
        DebugMessageTypeC("9. [USB] [Retimer] Set Retimer(LFPS) by TypeC UFP Flip", enumOrientation);
    }

    // Retimer UFP Setting Highest support Speed
    if(GET_USB_HUB_U3_SPEED_SUPPORT() == _USB_3_GEN2)
    {
        ScalerSetBit(P3B_76_LBPM_TRANSMIT_CTRL_U_01, ~_BIT2, _BIT2);

        DebugMessageTypeC("9. [USB] [Retimer] Support Speed Gen2", GET_USB_HUB_U3_SPEED_SUPPORT());
    }
    else
    {
        ScalerSetBit(P3B_76_LBPM_TRANSMIT_CTRL_U_01, ~_BIT2, 0x00);

        DebugMessageTypeC("9. [USB] [Retimer] Support Speed Gen1", GET_USB_HUB_U3_SPEED_SUPPORT());
    }

    // Retimer UFP Setting Highest support Lane Count
    if(GET_USB_HUB_U3_LANE_SUPPORT() == _USB_3_LANE_X2)
    {
        ScalerSetBit(P3B_76_LBPM_TRANSMIT_CTRL_U_01, ~_BIT1, _BIT1);

        DebugMessageTypeC("9. [USB] [Retimer] Support Lane Count x2", GET_USB_HUB_U3_LANE_SUPPORT());
    }
    else
    {
        ScalerSetBit(P3B_76_LBPM_TRANSMIT_CTRL_U_01, ~_BIT1, 0x00);

        DebugMessageTypeC("9. [USB] [Retimer] Support Lane Count x1", GET_USB_HUB_U3_LANE_SUPPORT());
    }
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
    // [BLR Path] Enable Forward SKP After Debounce Ready, This Behavior in RL6829 is opposite, Before ECO#1721
    ScalerSetBit(P3D_E3_TX_MUX_U_03, ~_BIT7, _BIT7);
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)

    // Dsiable LFPS Detect : pol_lfps_state_aware at Polling.EQ State to aviod Transmit Polling.LFPS Between TSEQ & Wite-Protect[1]
    ScalerSetBit(P3B_25_POLLING_LFPS_U_01, ~(_BIT3 | _BIT1), 0x00);

    // Set Phy Ready Handshake Condition to 3
    ScalerSetBit(P3B_3E_LBPM_DETECT_U_08, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Set LBPM Detection Number of EI to 11us : To make sure the number of phy.rdy is equal between the transmit and receive.
    ScalerSetByte(P3B_4A_LBPM_DETECT_U_DUMMY_02, 0x0B);

    // LFPS Wait Force P0 Ack : Disable RxDetect/U2/U3 wait Ack (For LVS TD.10.127)
    ScalerSetBit(P3B_5A_UX_EXIT_DETECT_U_DUMMY_01, ~_BIT6, 0x00);

    // Polling.LFPS Forward Condition : Disable Condition to Forward more Polling.LFPS
    ScalerSetBit(P3B_60_LFPS_TX_SETTING_U, ~_BIT1, 0x00);

    // Polling.LFPS Forward CTS Condition : (Default) Enable CTS Condition
    ScalerSetBit(P3B_68_LFPS_LOCAL_GEN_CTRL_U_07, ~_BIT0, _BIT0);

    // LFPS/LBPM Tx Mux Switch Condition : Set Disable to avoid forwarding LBPM treated as Polling.LFPS
    ScalerSetBit(P3B_6A_LFPS_TRANSMIT_CTRL_U_DUMMY_U_01, ~_BIT7, 0x00);

    // LBPM Retimer Presence : Increasing Only Phy Ready[7] Asserted. ([7]=1'b1)
    ScalerSetBit(P3B_76_LBPM_TRANSMIT_CTRL_U_01, ~(_BIT4 | _BIT3), _BIT4);

    // LBPM tPWM Max set to 2.496us : To Avoid Dphy Elecidle Debounce resulting in detection of wider Delimiter-0
    ScalerSetByte(P3B_3F_LBPM_DETECT_U_09, 0x92);

    // U1_Exit Tx Fixed Length
    // To avoid (Hub Rx Delay + U1_Exit sent by Hub) too long. Ex: 300ns(Hub Rx Delay) + 1.1us (Hub U1_Exit) = 1.4 us
    ScalerSetBit(P3B_85_UX_EXIT_TRANSMIT_CTRL_U_01, ~_BIT6, _BIT6);

    // [Ping.LFPS Detect Lower Bound] MAC Detect Ping set to min 22ns
    ScalerSetBit(P3B_4B_PING_LFPS_DETECT_U_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // [Ping.LFPS Detect Upper Bound]MAC Detect Ping set to MAC 280ns
    ScalerSetByte(P3B_4C_PING_LFPS_DETECT_U_02, 0x64);

    // [Ping.LFPS Tx] Set Ping.LFPS Width to 187ns & Wite-Protect[6]
    ScalerSetBit(P3B_80_PING_LFPS_TRANSMIT_CTRL_U, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Timer Enable Ping.LFPS Timer(Reference DFP Side)
    ScalerSetBit(P3B_93_TIMER_TOP, ~_BIT3, _BIT3);

    // Timer - Ping.LFPS Timer Reference Other Side (DFP Side) & write-protect[5]
    ScalerSetBit(P3B_9D_TIMER_CNT_LIST_CONTROL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Timer - Set Polling.LFPS timeout to 367ms to avoid Polling.LFPS mix high speed signal at compliance mode
    ScalerSetByte(P3B_A3_TIMER_CNT_LIST_3, 0x6F);

    // Gen1 LinLDetect Enable Reset PN Result at RxDetect
    ScalerSetBit(P3D_64_LINK_DET_DUMMY_02, ~_BIT0, _BIT0);

    // COMMA Detect Delay (Default) 100x10 us
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    ScalerSetByte(P3D_0A_COM_DETECT_U_03, 0x0A);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

    // [BLR Path] Tx switch to Forward condition : TSx State => For CTS[7.16][7.30]
    ScalerSetBit(P3D_E0_TX_MUX_U_00, ~_BIT5, _BIT5);

    // [BLR Path] Tx switch to Forward condition : wait Both side at Polling
    ScalerSetBit(P3D_E1_TX_MUX_U_01, ~_BIT6, _BIT6);

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
    // [BLR Path] Correct the RD error while switching to Forward by changing TS1 FunctionByte[6].
    ScalerSetBit(P3D_E3_TX_MUX_U_03, ~(_BIT5 | _BIT4), _BIT4);

    // [BLR Path] UFP0 CommaDetect Enable TS1A/B Detect To Notify RTSSM & write-protect[6][2]
    ScalerSetBit(P3D_ED_COM_DETECT_U_04, ~(_BIT6 | _BIT2 | _BIT1), (_BIT6 | _BIT2 | _BIT1));
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // [BLR Path] UFP1 CommaDetect Enable TS1A/B Detect To Notify RTSSM & write-protect[6][2]
    ScalerSetBit(P3D_FD_COM_DETECT_U_04, ~(_BIT6 | _BIT2 | _BIT1), (_BIT6 | _BIT2 | _BIT1));
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif

    // [BLR Path] Set FIFO Rx0 Forward WL = 7 & Wite-Protect[5:4]
    ScalerSetBit(P3D_C5_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
    ScalerSetBit(P3D_D5_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // RL6829: AsyFIFO is in front of Lane Mux
    // RL6952: AsyFIFO is behind Lane Mux
    // [BLR Path] Set FIFO Rx1 Forward WL = 7 & Wite-Protect[5:4]
    ScalerSetBit(P3D_C6_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P3D_D6_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

    // [BLR Path] Disable FIFO SKP Remove/Add Function for more compatibility
    ScalerSetBit(P3D_C4_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~_BIT3, 0x00);
#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
    ScalerSetBit(P3D_D4_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~_BIT3, 0x00);
#endif
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust EB WL for 1/4 EB
    ScalerSetByte(P3D_8C_EB_WL_0_G1X1, 0x0E);
    ScalerSetByte(P3D_90_EB_WL_2_G1X1, 0x1C);
    ScalerSetByte(P3D_92_EB_WL_3_G1X1, 0x28);
    ScalerSetByte(P3D_94_EB_WL_4_G1X1, 0x0E);
    ScalerSetByte(P3D_98_EB_WL_6_G1X1, 0x10);
#endif
#endif

    // Switch to Local Loopback and set early enter local loopback
    ScalerSetBit(P3D_63_LINK_DET_DUMMY_01, ~_BIT1, _BIT1);

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        // Switch back to Passthrough Loopback
        ScalerSetBit(P3D_63_LINK_DET_DUMMY_01, ~_BIT1, 0x00);
    }
#endif // end of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
    ScalerSetBit(P3C_61_LINK_DET_DUMMY_01, ~_BIT1, _BIT1);
#endif // end of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)

    //--------------------------------------------------
    // Retimer MAC Set Gen 1x1 to 20bits Data Path - Off-Region
    //--------------------------------------------------
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // Disable Gen1 LinkDetect : eb_glob_opt_x1_u
    ScalerSetBit(P3D_30_LINK_DET_GLOBAL_G1, ~_BIT1, 0x00);

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        // Enable Gen1 LinkDetect : eb_glob_opt_x1_u
        ScalerSetBit(P3D_30_LINK_DET_GLOBAL_G1, ~_BIT1, _BIT1);
    }
#endif // end of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
    // UFP Gen2 BlockAlign - Set Header Check Mode to 3 bit correct
    ScalerSetBit(P3C_09_BLOCK_ALIGN_01, ~_BIT3, _BIT3);

    // Gen2 Linkdetect - Set Link Command Need to Detect Reserved Bit
    ScalerSetBit(P3C_30_LINK_DET_GLOBAL_G2, ~_BIT0, _BIT0);

    // Gen2 FIFO2 Change Undefined Header to Data Header(VIP) & write-protect[2]
    ScalerSetBit(P3C_C8_FIFO2_GLOBAL_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT4 | _BIT2));

    // Gen2 EB - Set SKP Add Number to 2, [*] To Cover EB SKP Add Bug
    ScalerSetBit(P3C_71_EB_GLOBAL_G2_1, ~(_BIT4 | _BIT3), _BIT3);

    // Gen2 EB - TSx Remove WL - Adjust to 13
    ScalerSetByte(P3C_7A_EB_WL_G2_0, 0x0D);

    // Gen2 EB - SKP Remove WL - Adjust to 14
    ScalerSetByte(P3C_7B_EB_WL_G2_1, 0x0E);

    // Gen2 EB - SKP Add WL - Adjust to 8
    ScalerSetByte(P3C_7C_EB_WL_G2_2, 0x08);

    // Gen2 EB - EB Forward WL - Adjust to 20
    ScalerSetByte(P3C_7D_EB_WL_G2_3, 0x14);

    // Gen2 EB - TSx SKP Add WL - Adjust to 4
    ScalerSetByte(P3C_7E_EB_WL_G2_4, 0x04);
#endif // End of #if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer UFP Mac LFPS U3_Exit Relatd Initial at OFF Region
// Input Value  : EnumTypeCOrientation
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0UfpOffRegionU3ExitInitial(void)
{
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // U3_Exit : Set u3_stop_cnt_rst_enable = 1, RL6829 ver.A Shall set = 1
    ScalerSetBit(P3B_20_LANE_SWITCH_U_01, ~_BIT7, _BIT7);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust U3_Exit_Extend Unit from us to ms
    ScalerSetBit(P3B_58_UX_EXIT_DETECT_U_03, ~_BIT0, _BIT0);

    // Adjust U3_Exit_Extend to 4ms (Actually, Tx extend 2-3 ms U3 Exit)
    ScalerSetByte(P3B_8C_LFPS_TRANSMIT_U_DUMMY_02, 0x04);
#endif
#else
    // U3_Exit : Set u3_stop_cnt_rst_enable = 0, This behavior is completely opposite between RL6829 and RL6952
    ScalerSetBit(P3B_20_LANE_SWITCH_U_01, ~_BIT7, 0x00);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust U3_Exit_Extend Unit from us to ms
    ScalerSetBit(P3B_8D_LFPS_TRANSMIT_U_DUMMY_03, ~_BIT7, _BIT7);

    // Adjust U3_Exit_Extend to 4ms (Actually, Tx extend 2-3 ms U3 Exit)
    ScalerSetByte(P3B_8C_LFPS_TRANSMIT_U_DUMMY_02, 0x04);
#endif
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP Mac Initial at On Region
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0DfpOnRegionInitial(void)
{
    // Retimer DFP Setting Downstream Port Orienation
#if(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_UNFLIP)
    // RTSSM Lane Switch & write protect [7][3]
    ScalerSetBit(P3E_0A_RTSSM_FLAG_00, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT3));

    DebugMessageTypeC("9. [USB] [Retimer] Set Retimer(RTSSM) by TypeC DFP UnFlip ", _TYPE_C_ORIENTATION_UNFLIP);

#elif(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_FLIP)
    // RTSSM Lane Switch & write protect [7][3]
    ScalerSetBit(P3E_0A_RTSSM_FLAG_00, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5 | _BIT4 | _BIT3));

    DebugMessageTypeC("9. [USB] [Retimer] Set Retimer(RTSSM) by TypeC DFP Flip", _TYPE_C_ORIENTATION_FLIP);
#endif
    // RTSSM Condition : Enable Compliance (Default)
    ScalerSetBit(P3E_0B_RTSSM_STATE_CONTROL_00, ~_BIT1, _BIT1);

    // RTSSM Condition : RxDetect to Speeddetect when Both Side Detect Polling.LFPS
    ScalerSetBit(P3E_0E_RTSSM_STATE_CONTROL_03, ~(_BIT7 | _BIT6), 0x00);

    // RTSSM Condition : Speeddetect to Polling.RxEQ When Any Side 60us_EI_Timeout : 2'b01
    ScalerSetBit(P3E_0E_RTSSM_STATE_CONTROL_03, ~(_BIT4 | _BIT3), _BIT3);

    // RTSSM Condition : Polling/Recovery.TSx to Idle / Idle to U0 State Condition by monitor Tx/Rx Handshake Condition
    ScalerSetByte(P3E_0F_RTSSM_STATE_CONTROL_04, 0x00);

    // Set PM_ENTRY_TIMER to 10us (To avoid Timer Missmatch with Hub) 8us + 2us
    ScalerSetByte(P3E_AD_TIMER_CNT_LIST_13, 0x0A);

    //--------------------------------------------------
    // Retimer MAC Set Gen 1x1 to 20bits Data Path - On-Region
    //--------------------------------------------------
    // Disable RTSSM : blr_mode_rxeq_2_tsx_cond_d
    ScalerSetBit(P3E_10_RTSSM_STATE_CONTROL_05, ~_BIT5, 0x00);

    // Disable PIPE : gen1_fast_mode_d
    ScalerSetBit(P3E_C4_PIPE_CONTROL_D_04, ~_BIT7, 0x00);

    // [1] reg_ssc_en_tx = 1'b1 => SSC ON
    ScalerSetBit(PC8_10_SSC_TX_00, ~_BIT1, _BIT1);

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        //--------------------------------------------------
        // Retimer MAC Set Gen 1x1 BLR Path - On-Region
        //--------------------------------------------------
#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
        // Disable RTSSM : blr_mode_rxeq_2_tsx_cond_d
        // Before ECO#1724. To avoid Polling.RxEQ LinkTraining Fail after TSx.Timeout
        ScalerSetBit(P3E_10_RTSSM_STATE_CONTROL_05, ~_BIT5, 0x00);
#else
        // Enable RTSSM : blr_mode_rxeq_2_tsx_cond_d
        ScalerSetBit(P3E_10_RTSSM_STATE_CONTROL_05, ~_BIT5, _BIT5);
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)

        // Enable PIPE : gen1_fast_mode_d
        ScalerSetBit(P3E_C4_PIPE_CONTROL_D_04, ~_BIT7, _BIT7);

        // [1] reg_ssc_en_tx = 1'b0 => SSC OFF
        ScalerSetBit(PC8_10_SSC_TX_00, ~_BIT1, 0x00);
    }
#endif // end of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
    //--------------------------------------------------
    // U3 State PowerDown = P3, Low Power Support
    //--------------------------------------------------
    // Set DFP reg_pclk_sel = 1 : PCLK is aux_clk when P3
    ScalerSetBit(PC8_80_SPPHY_44, ~_BIT6, _BIT6);

    // Set clk_seq_delay = 3'b011, extend PowerCut execution time to aviod gating clock too early
    ScalerSetBit(P3E_05_RTSSM_POWER_CUT_CTL_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set DFP PIPE U3 PowerDown = P3
    ScalerSetBit(P3E_C4_PIPE_CONTROL_D_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
    // Set p3_rx_det_pc_ctl = 1 : Whole Domian Power on When Power Cut OFF By Rxdetect
    ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT7, _BIT7);
#endif

    if(GET_USB_REPEATER_POWER_CUT_MODE() == _USB_POWER_CUT_HW_MODE)
    {
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL == _USB3_PS_SUPPORT_LEVEL_1)
        ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_1)
        ScalerSetByte(P3E_04_RTSSM_POWER_CUT_CTL_00, 0x80);
        ScalerSetByte(P3E_04_RTSSM_POWER_CUT_CTL_00, 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_2)
        ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT6, 0x00);
#endif
    }
    else if(GET_USB_REPEATER_POWER_CUT_MODE() == _USB_POWER_CUT_FW_MODE)
    {
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL == _USB3_PS_SUPPORT_LEVEL_1)
        ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, _BIT7);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_1)
        // Set the Power Cut Control
        ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~(_BIT6 | _BIT4 | _BIT2), (_BIT6 | _BIT4 | _BIT2));
        ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, _BIT7);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_2)
        ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT6, _BIT6);
#endif
    }
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X1)
    // Set DFP Compliance Mode x1 Lane Mode
    ScalerSetBit(P3E_C8_PIPE_CONTROL_D_08, ~(_BIT7 | _BIT3), 0x00);
#endif
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP Mac Initial at Off Region
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0DfpOffRegionInitial(void)
{
    // Retimer DFP Setting Downstream Port Orienation
#if(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_UNFLIP)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // LFPS Lane Switch
    ScalerSetBit(P3E_20_LANE_SWITCH_D_01, ~(_BIT6 | _BIT4), 0x00);
#endif
    DebugMessageTypeC("9. [USB] [Retimer] Set Retimer(LFPS) by TypeC DFP UnFlip ", _TYPE_C_ORIENTATION_UNFLIP);

#elif(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_FLIP)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // LFPS Lane Switch
    ScalerSetBit(P3E_20_LANE_SWITCH_D_01, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));
#endif
    DebugMessageTypeC("9. [USB] [Retimer] Set Retimer(LFPS) by TypeC DFP Flip", _TYPE_C_ORIENTATION_FLIP);
#endif
    // Retimer DFP Setting Highest support Speed
    if(GET_USB_HUB_U3_SPEED_SUPPORT() == _USB_3_GEN2)
    {
        ScalerSetBit(P3E_76_LBPM_TRANSMIT_CTRL_D_01, ~_BIT2, _BIT2);
    }
    else
    {
        ScalerSetBit(P3E_76_LBPM_TRANSMIT_CTRL_D_01, ~_BIT2, 0x00);
    }

    // Retimer DFP Setting Highest support Lane Count
    if(GET_USB_HUB_U3_LANE_SUPPORT() == _USB_3_LANE_X2)
    {
        ScalerSetBit(P3E_76_LBPM_TRANSMIT_CTRL_D_01, ~_BIT1, _BIT1);
    }
    else
    {
        ScalerSetBit(P3E_76_LBPM_TRANSMIT_CTRL_D_01, ~_BIT1, 0x00);
    }

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
    // [BLR Path] Enable Forward SKP After Debounce Ready, This Behavior in RL6829 is opposite
    ScalerSetBit(P82_E3_TX_MUX_D_03, ~_BIT7, _BIT7);
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

    // Dsiable LFPS Detect : pol_lfps_state_aware at Polling.EQ State to aviod Transmit Polling.LFPS Between TSEQ Wite-Protect[1]
    ScalerSetBit(P3E_25_POLLING_LFPS_D_01, ~(_BIT3 | _BIT1), 0x00);

    // Set Phy Ready Handshake Condition to 3
    ScalerSetBit(P3E_3E_LBPM_DETECT_D_08, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Set LBPM Detection Number of EI to 11us : To make sure the number of phy.rdy is equal between the transmit and receive.
    ScalerSetByte(P3E_4A_LBPM_DETECT_D_DUMMY_02, 0x0B);

    // LFPS Wait Force P0 Ack : Disable RxDetect/U2/U3 wait Ack (For LVS TD.10.127)
    ScalerSetBit(P3E_5A_UX_EXIT_DETECT_D_DUMMY_01, ~_BIT6, 0x00);

    // Polling.LFPS Forward Condition : Disable Condition to Forward more Polling.LFPS
    ScalerSetBit(P3E_60_LFPS_TX_SETTING_D, ~_BIT1, 0x00);

    // Polling.LFPS Forward CTS Condition : (Default) Enable CTS Condition
    ScalerSetBit(P3E_68_LFPS_LOCAL_GEN_CTRL_D_07, ~_BIT0, _BIT0);

    // LFPS/LBPM Tx Mux Switch Condition : Set Disable to avoid forwarding LBPM treated as Polling.LFPS
    ScalerSetBit(P3E_6A_LFPS_TRANSMIT_CTRL_DUMMY_D_01, ~_BIT7, 0x00);

    // LBPM Retimer Presence : Increasing Only Phy Ready[7] Asserted. ([7]=1'b1)
    ScalerSetBit(P3E_76_LBPM_TRANSMIT_CTRL_D_01, ~(_BIT4 | _BIT3), _BIT4);

    // LBPM tPWM Max set to 2.496us : To Avoid Dphy Elecidle Debounce resulting in detection of wider Delimiter-0
    ScalerSetByte(P3E_3F_LBPM_DETECT_D_09, 0x92);

    // U1_Exit Tx Fixed Length
    // To avoid (Hub Rx Delay + U1_Exit sent by Hub) too long. Ex: 300ns(Hub Rx Delay) + 1.1us (Hub U1_Exit) = 1.4 us
    ScalerSetBit(P3E_85_UX_EXIT_TRANSMIT_CTRL_D_01, ~_BIT6, _BIT6);

    // U1_Exit Fast Forward Threshold to Max = 4'b1111, Releated to 0x3E89[1] u1_exit_forward_mode = 1
    // To avoid misidentified Ping.LFPS by DFP Aphy NSQ MAC Debounce 66ns
    ScalerSetBit(P3E_5B_LFPS_RECEIVE_D_DUMMY_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [Ping.LFPS Detect Lower Bound] MAC Detect Ping set to min 22ns
    ScalerSetBit(P3E_4B_PING_LFPS_DETECT_D_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // [Ping.LFPS Detect Upper Bound]MAC Detect Ping set to MAC 280ns
    ScalerSetByte(P3E_4C_PING_LFPS_DETECT_D_02, 0x64);

    // [Ping.LFPS Tx] Set Ping.LFPS Width to 187ns & Wite-Protect[6]
    ScalerSetBit(P3E_80_PING_LFPS_TRANSMIT_CTRL_D, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Timer Enable Ping.LFPS Timer(Reference DFP Side) & U2/U3 DFP Side RxDetection
    ScalerSetBit(P3E_93_TIMER_TOP, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2 | _BIT1));

    // Timer -Ping.LFPS Timer Reference Same Side (DFP Side) & write-protect[5]
    ScalerSetBit(P3E_9D_TIMER_CNT_LIST_CONTROL, ~(_BIT7 | _BIT5), _BIT5);

    // Timer - Set Polling.LFPS timeout to 367ms to avoid Polling.LFPS mix high speed signal at compliance mode
    ScalerSetByte(P3E_A3_TIMER_CNT_LIST_3, 0x6F);

    // Gen1 LinLDetect Enable Reset PN Result at RxDetect
    ScalerSetBit(P82_64_LINK_DET_DUMMY_02, ~_BIT0, _BIT0);

    // COMMA Detect Delay (Default) 100x10 us
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    ScalerSetByte(P82_0A_COM_DETECT_D_03, 0x0A);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

    // [BLR Path] Tx switch to Forward condition : TSx State => For CTS[7.16][7.30]
    ScalerSetBit(P82_E0_TX_MUX_D_00, ~_BIT5, _BIT5);

    // [BLR Path] Tx switch to Forward condition : wait Both side at Polling
    ScalerSetBit(P82_E1_TX_MUX_D_01, ~_BIT6, _BIT6);

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
    // [BLR Path] Correct the RD error while switching to Forward by changing TS1 FunctionByte[6].
    ScalerSetBit(P82_E3_TX_MUX_D_03, ~(_BIT5 | _BIT4), _BIT4);

    // [BLR Path] CommaDetect Enable TS1A/B Detect To Notify RTSSM & write-protect[6][2]
    ScalerSetBit(P82_ED_COM_DETECT_D_04, ~(_BIT6 | _BIT2 | _BIT1), (_BIT6 | _BIT2 | _BIT1));
#endif

    // [BLR Path] Set FIFO Forward WL = 5 & Wite-Protect[5:4]
    ScalerSetBit(P82_D5_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // RL6829: AsyFIFO is in front of Lane Mux
    // RL6952: AsyFIFO is behind Lane Mux
    // [BLR Path] Set FIFO Rx1 Forward WL = 7 & Wite-Protect[5:4]
    ScalerSetBit(P82_D6_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

    // [BLR Path] Disable FIFO SKP Remove/Add Function for more compatibility
    ScalerSetBit(P82_D4_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~_BIT3, 0x00);

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust EB WL for 1/4 EB
    ScalerSetByte(P82_8C_EB_WL_0_G1X1, 0x0E);
    ScalerSetByte(P82_90_EB_WL_2_G1X1, 0x1C);
    ScalerSetByte(P82_94_EB_WL_4_G1X1, 0x0E);
    ScalerSetByte(P82_98_EB_WL_6_G1X1, 0x10);
#endif
#endif

    // Disable U3S State
    ScalerSetBit(P3E_0C_RTSSM_STATE_CONTROL_01, ~_BIT6, 0x00);

    //--------------------------------------------------
    // Retimer MAC Set Gen 1x1 to 20bits Data Path
    //--------------------------------------------------
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // Disable Gen1 LinkDetect : eb_glob_opt_x1_d
    ScalerSetBit(P82_30_LINK_DET_GLOBAL_G1, ~_BIT1, 0x00);

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        // Enable Gen1 LinkDetect : eb_glob_opt_x1_d
        ScalerSetBit(P82_30_LINK_DET_GLOBAL_G1, ~_BIT1, _BIT1);
    }
#endif // end of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
    // DFP Gen2 BlockAlign - Set Header Check Mode to 3 bit correct
    ScalerSetBit(P81_09_BLOCK_ALIGN_01, ~_BIT3, _BIT3);

    // Gen2 Linkdetect - Set Link Command Need to Detect Reserved Bit
    ScalerSetBit(P81_30_LINK_DET_GLOBAL_G2, ~_BIT0, _BIT0);

    // Gen2 EB - Set SKP Add Number to 2, [*] To Cover EB SKP Add Bug
    ScalerSetBit(P81_71_EB_GLOBAL_G2_1, ~(_BIT4 | _BIT3), _BIT3);

    // Gen2 EB - TSx Remove WL - Adjust to 13
    ScalerSetByte(P81_7A_EB_WL_G2_0, 0x0D);

    // Gen2 EB - SKP Remove WL - Adjust to 14
    ScalerSetByte(P81_7B_EB_WL_G2_1, 0x0E);

    // Gen2 EB - SKP Add WL - Adjust to 8
    ScalerSetByte(P81_7C_EB_WL_G2_2, 0x08);

    // Gen2 EB - EB Forward WL - Adjust to 20
    ScalerSetByte(P81_7D_EB_WL_G2_3, 0x14);

    // Gen2 EB - TSx SKP Add WL - Adjust to 4
    ScalerSetByte(P81_7E_EB_WL_G2_4, 0x04);

    // Gen2 FIFO2 Change Undefined Header to Data Header(VIP) & write-protect[2]
    ScalerSetBit(P81_C8_FIFO2_GLOBAL_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT4 | _BIT2));
#endif // End of #if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer DFP Mac LFPS U3_Exit Relatd Initial at OFF Region
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0DfpOffRegionU3ExitInitial(void)
{
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // U3_Exit : Set u3_stop_cnt_rst_enable = 1, RL6829 ver.A Shall set = 1
    ScalerSetBit(P3E_20_LANE_SWITCH_D_01, ~_BIT7, _BIT7);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust U3_Exit_Extend to 4ms (Actually, Tx extend 2-3 ms U3 Exit)
    ScalerSetBit(P3E_58_UX_EXIT_DETECT_D_03, ~_BIT0, _BIT0);

    // Adjust U3_Exit_Extend to 4ms (Actually, Tx extend 2-3 ms U3 Exit)
    ScalerSetByte(P3E_8C_LFPS_TRANSMIT_D_DUMMY_02, 0x04);
#endif
#else
    // U3_Exit : Set u3_stop_cnt_rst_enable = 0, This behavior is completely opposite between RL6829 and RL6952
    ScalerSetBit(P3E_20_LANE_SWITCH_D_01, ~_BIT7, 0x00);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Adjust U3_Exit_Extend to 4ms (Actually, Tx extend 2-3 ms U3 Exit)
    ScalerSetBit(P3E_8D_LFPS_TRANSMIT_D_DUMMY_03, ~_BIT7, _BIT7);

    // Adjust U3_Exit_Extend to 4ms (Actually, Tx extend 2-3 ms U3 Exit)
    ScalerSetByte(P3E_8C_LFPS_TRANSMIT_D_DUMMY_02, 0x04);
#endif
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0Enable(bit bEnable)
{
    ScalerUsb3RetimerMac0IrqEnable(bEnable);

    // Retimer Mac0 Off Region Enable
    ScalerUsb3RetimerMac0OffRegionEnable(bEnable);

    // Retimer Mac0 On Region Enable
    ScalerUsb3RetimerMac0OnRegionEnable(bEnable);
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer On-Region Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0OnRegionEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        //========================
        // (For UFP State Machine)Enable U0 State IRQ For TD.7.17
        //========================
        // Turn on 8b10b / 128/132 decode error reset
        ScalerSetBit(P3B_0C_RTSSM_STATE_CONTROL_01, ~_BIT0, _BIT0);

        //=======================================================
        // Release RTSSM Reset & Soft Reset & write-protect[4][3]
        //=======================================================
        ScalerSetBit(P3B_06_RTSSM_GLOBAL_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
    else
    {
        //=======================================================
        // Set RTSSM Reset & Soft Reset & write-protect[4][3]
        //=======================================================
        ScalerSetBit(P3B_06_RTSSM_GLOBAL_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));


        //========================
        // (For UFP State Machine)Disable U0 State IRQ For TD.7.17
        //========================
        // Turn off 8b10b / 128/132 decode error reset
        ScalerSetBit(P3B_0C_RTSSM_STATE_CONTROL_01, ~_BIT0, 0x00);

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
        //========================
        // Set DFP reg_powerdown_init = 0 : Initial PowerDown = P2
        //========================
        ScalerSetBit(PC8_80_SPPHY_44, ~_BIT4, 0x00);

        //==================================================================================
        // Reset the MAC Power Cut and Iso Control when Power Cut FSM from PWR_OFF to PWR_ON
        //==================================================================================
        // Application context : UFP Port unplugs and Retimer is in U3-P3 Status.
        if(g_bUsb3RetimerMac0P3Entry == _TRUE)
        {
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL == _USB3_PS_SUPPORT_LEVEL_1)
            // Reset Mac Low Power
            ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT3, _BIT3);
            ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT3, 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_1)
            // Reset MAC Power Cut and ISO Control
            ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT1, _BIT1);
            ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT1, 0x00);

            // Reset DFP PHY Power Cut and ISO Control
            ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT3, _BIT3);
            ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT3, 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_2)
            // Reset JFM Power Cut and ISO Control
            ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT5, _BIT5);
            ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT5, 0x00);
#endif
            // Reset P3Entry and Retimer P3 status flag
            g_bUsb3RetimerMac0P3Entry = _FALSE;
            SET_USB3_RETIMER_P3_STATUS(_USB3_RETIMER_NO_ACTION);
        }

        //===================================================================
        // Release Force PIPE Power/Signal Setting For P3 related application
        //===================================================================
        // Unplugging the Dx port shall release the PIPE control set in Power_Cut_ON_INT.
        // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = Back to HW Mode
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // For UFP0 PIPE
        {
            // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = Back to HW Mode
            ScalerSetBit(P3B_C0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = Back to HW Mode
            ScalerSetBit(P3B_C2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Force PIPE Tx PowerDown Back to HW Mode
            ScalerSetBit(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }
        else // For UFP1 PIPE
        {
            // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = Back to HW Mode
            ScalerSetBit(P81_D0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = Back to HW Mode
            ScalerSetBit(P81_D2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Force PIPE Tx PowerDown Back to HW Mode
            ScalerSetBit(P81_D5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }
#else
        // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = Back to HW Mode
        ScalerSetBit(P3B_C0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = Back to HW Mode
        ScalerSetBit(P3B_C2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Force PIPE Tx PowerDown Back to HW Mode
        ScalerSetBit(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
#endif
        // Force DFP PIPE Tx PowerDown Back to HW Mode
        ScalerSetBit(P3E_C5_PIPE_CONTROL_D_05, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // UFP0
        {
            // Release UFP PIPE0 PhyRate/LaneCount to HW Mode
            ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
        }
        else
        {
            // Release UFP PIPE1 PhyRate/LaneCount to HW Mode
            ScalerSetBit(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
        }
#else
        // Release UFP PIPE0 PhyRate/LaneCount to HW Mode
        ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
#endif
        // Release DFP PIPE PhyRate/LaneCount to HW Mode
        ScalerSetBit(P3E_C6_PIPE_CONTROL_D_06, ~(_BIT5 | _BIT3), 0x00);

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
        // Reset Gen1 CommaDetect rxeq_valid_delay_cnt to 0x0A(1ms)
        ScalerSetByte(P3D_0A_COM_DETECT_U_03, 0x0A);
        ScalerSetByte(P82_0A_COM_DETECT_D_03, 0x0A);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

        if(ScalerUsb3RepeaterMacCheckP3PowerCutOFF_EXINT3() == _FALSE)
        {
            // When Detecting NSQ but not Power on, use FW Mode to Force Power on
            ScalerUsb3RetimerMac0PowerCutOffAwake();
        }

        // Enable Force P0 wait Rxdetect done
        ScalerSetBit(P3B_5A_UX_EXIT_DETECT_U_DUMMY_01, ~_BIT4, _BIT4);
        ScalerSetBit(P3E_5A_UX_EXIT_DETECT_D_DUMMY_01, ~_BIT4, _BIT4);

        // Enable LFPS Global
        ScalerSetBit(P3B_07_RTSSM_GLOBAL_07, ~_BIT2, _BIT2);

        // Release PIPE CMD_RxDetect to HW Mode
        ScalerSetBit(P3E_C0_PIPE_CONTROL_D_00, ~_BIT7, 0x00);

        // Enable Force P0 wait Rxdetect done
        ScalerSetBit(P3B_5A_UX_EXIT_DETECT_U_DUMMY_01, ~_BIT4, _BIT4);
        ScalerSetBit(P3E_5A_UX_EXIT_DETECT_D_DUMMY_01, ~_BIT4, _BIT4);
#endif
    }
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer Off-Region Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0OffRegionEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
        //========================
        // Enable BlockAlign, Deskew Module
        //========================
        // UFP Gen2 BlockAlign Enable
        ScalerSetBit(P3C_09_BLOCK_ALIGN_01, ~_BIT7, _BIT7);

        // DFP Gen2 BlockAlign Enable
        ScalerSetBit(P81_09_BLOCK_ALIGN_01, ~_BIT7, _BIT7);
#endif

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
        // UFP Gen1 Deskew Module Enable & write-protect[2][0]
        ScalerSetBit(P3D_10_DE_SKEW_GEN1_GLOBAL, ~(_BIT7 | _BIT2 | _BIT0), _BIT7);

        // DFP Gen1 Deskew Module Enable & write-protect[2][0]
        ScalerSetBit(P82_10_DE_SKEW_GEN1_GLOBAL, ~(_BIT7 | _BIT2 | _BIT0), _BIT7);

        // UFP Gen2 Deskew Module Enable & write-protect[2][0]
        ScalerSetBit(P3C_10_DE_SKEW_GEN2_GLOBAL, ~(_BIT7 | _BIT2 | _BIT0), _BIT7);

        // DFP Gen2 Deskew Module Enable & write-protect[2][0]
        ScalerSetBit(P81_10_DE_SKEW_GEN2_GLOBAL, ~(_BIT7 | _BIT2 | _BIT0), _BIT7);
#endif // End of (_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

        //========================
        // Enable PassModeRx CommaDetect
        //========================
        // UFP0 PassModeRx CommaDetect
        ScalerSetBit(P3D_C0_COM_DETECT_U_00, ~_BIT7, _BIT7);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        // UFP1 PassModeRx CommaDetect
        ScalerSetBit(P3D_D0_COM_DETECT_U_00, ~_BIT7, _BIT7);
#endif
        // DFP PassModeRx CommaDetect
        ScalerSetBit(P82_D0_COM_DETECT_D_00, ~_BIT7, _BIT7);
    }
    else
    {
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
        //========================
        // Disable BlockAlign, Deskew Module
        //========================
        // UFP Gen2 BlockAlign Disable
        ScalerSetBit(P3C_09_BLOCK_ALIGN_01, ~_BIT7, 0x00);

        // DFP Gen2 BlockAlign Disable
        ScalerSetBit(P81_09_BLOCK_ALIGN_01, ~_BIT7, 0x00);
#endif

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
        // UFP Gen1 Deskew Module Disable & write-protect[2][0]
        ScalerSetBit(P3D_10_DE_SKEW_GEN1_GLOBAL, ~(_BIT7 | _BIT2 | _BIT0), 0x00);

        // DFP Gen1 Deskew Module Disable & write-protect[2][0]
        ScalerSetBit(P82_10_DE_SKEW_GEN1_GLOBAL, ~(_BIT7 | _BIT2 | _BIT0), 0x00);

        // UFP Gen2 Deskew Module Disable & write-protect[2][0]
        ScalerSetBit(P3C_10_DE_SKEW_GEN2_GLOBAL, ~(_BIT7 | _BIT2 | _BIT0), 0x00);

        // DFP Gen2 Deskew Module Disable & write-protect[2][0]
        ScalerSetBit(P81_10_DE_SKEW_GEN2_GLOBAL, ~(_BIT7 | _BIT2 | _BIT0), 0x00);
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

        //========================
        // Disable PassModeRx CommaDetect
        //========================
        // UFP0 PassModeRx CommaDetect Disable
        ScalerSetBit(P3D_C0_COM_DETECT_U_00, ~_BIT7, 0x00);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        // UFP1 PassModeRx CommaDetect Disable
        ScalerSetBit(P3D_D0_COM_DETECT_U_00, ~_BIT7, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        // DFP PassModeRx CommaDetect Disable
        ScalerSetBit(P82_D0_COM_DETECT_D_00, ~_BIT7, 0x00);

        //==============================
        // UFP/DFP PortConfig Register Reset
        //==============================
        // Reset to Gen1 Related
        // Reset EQ Training Time to Gen1 4ms
        ScalerSetByte(P3B_A7_TIMER_CNT_LIST_7, 0x28);
        ScalerSetByte(P3E_A7_TIMER_CNT_LIST_7, 0x28);

        // Reset to x1 Lane Related
        // Reset Polling.Active_Timeout to 12ms
        ScalerSetByte(P3B_A9_TIMER_CNT_LIST_9, 0x78);
        ScalerSetByte(P3E_A9_TIMER_CNT_LIST_9, 0x78);

        // Reset Polling.Configuration_Timeout to 12ms
        ScalerSetByte(P3B_AA_TIMER_CNT_LIST_10, 0x78);
        ScalerSetByte(P3E_AA_TIMER_CNT_LIST_10, 0x78);

        // Reset PM_ENTRY_TIMER to 10us (To avoid Timer Missmatch with Hub) 8us + 2us
        ScalerSetByte(P3B_AD_TIMER_CNT_LIST_13, 0x0A);
        ScalerSetByte(P3E_AD_TIMER_CNT_LIST_13, 0x0A);

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
        // Reset AsyFIFO WL for x1 Lane Mode
        ScalerUsb3RetimerMac0UfpAsyFifoResetProc();
        ScalerUsb3RetimerMac0DfpAsyFifoResetProc();
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
        // Reset Phy rate control to HW mode
        ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), 0x00);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        ScalerSetBit(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), 0x00);
#endif
        // Reset Tx Bist to EB
        ScalerSetBit(P3D_B0_TXBIST_PAT_SEL_G1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
        ScalerSetBit(P3C_A0_TXBIST_PAT_SEL_G2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif
#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
        // Force LBPM Phy Rate to HW Mode, Before ECO#1511
        ScalerSetBit_EXINT3(P3B_49_LBPM_DETECT_U_DUMMY_01, ~(_BIT7 | _BIT6), _BIT7);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#endif
    }
}

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer Enable/Disable
// Input Value  : bEnable
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0IrqEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        //========================
        // UFP IRQ Enable
        //========================

        // Enable UFP State INT : RxDetect[7],Speeddetect[5], PortConfig[3], RxEQ[1]
        ScalerSetByte(P3B_11_RTSSM_IRQ_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
        //========================
        // P3 PowerSaving IRQ Enable
        //========================
        // Enable UFP State INT : U0[5]
        ScalerSetBit(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0));
#endif
        // Enable UFP State INT : Compliance Mode[1]
        ScalerSetBit(P3B_14_RTSSM_IRQ_03, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

        // Enable UFP Compliance Mode Rcv Polling/LBPM INT : Rcv Polling/LBPM[3]
        ScalerSetBit(P3B_15_RTSSM_IRQ_04, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0));

        //========================
        // DFP IRQ Enable
        //========================

        // Enable DFP State INT : PortConfig[3]
        ScalerSetBit(P3E_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0));

        // Enable DFP State INT : RxEQ[1] For Rx_Clk_Ctl Solution & Release AsyFIFO
        ScalerSetBit(P3E_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

        // U0 State IRQ For TD.7.17
        // Enable DFP State INT : U0[5]
        ScalerSetBit(P3E_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0));

        // Enable DFP Compliance Mode Rcv Polling/LBPM INT : Rcv Polling/LBPM[3]
        ScalerSetBit(P3E_15_RTSSM_IRQ_04, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0));

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
        //========================
        // P3 PowerSaving IRQ Enable
        //========================

        // Enable PowerCut INT : PowerCut_On[1]
        ScalerSetBit(P3E_07_RTSSM_POWER_CUT_CTL_03, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0));


        // Enable PowerCut INT : PowerCut_Off_by_nsq[7] : Enable for extremely fast exit from U3.
        ScalerSetBit(P3E_07_RTSSM_POWER_CUT_CTL_03, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0));
#endif
    }
    else
    {
        //========================
        // UFP IRQ Disable
        //========================

        // Disable UFP State INT : RxDetect[7],Speeddetect[5], PortConfig[3], RxEQ[1]
        ScalerSetByte(P3B_11_RTSSM_IRQ_00, (_BIT6 | _BIT4 | _BIT2 | _BIT0));

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
        //========================
        // P3 PowerSaving IRQ Disable
        //========================
        // Disable UFP State INT : U0[5]
        ScalerSetBit(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
#endif
        // Disable UFP State INT : Compliance Mode[1]
        ScalerSetBit(P3B_14_RTSSM_IRQ_03, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

        // Disable UFP Compliance Mode Rcv Polling/LBPM INT : Rcv Polling/LBPM[3]
        ScalerSetBit(P3B_15_RTSSM_IRQ_04, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
        if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
        {
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
            // Disable UFP State INT : Polling.Idle[5]
            ScalerSetBit(P3B_12_RTSSM_IRQ_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // Disable UFP State INT : U1[3]
            ScalerSetBit(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // Disable UFP State INT : U2[1]
            ScalerSetBit(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
#endif // End of #if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
            // Disable UFP State INT : U3[7], Recovery.TSx[5]
            ScalerSetBit(P3B_14_RTSSM_IRQ_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
        }
#endif
        //========================
        // DFP IRQ Disable
        //========================

        // Disable DFP State INT : PortConfig[3]
        ScalerSetBit(P3E_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

        // Disable DFP State INT : RxEQ[1] For Rx_Clk_Ctl Solution & Release AsyFIFO
        ScalerSetBit(P3E_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

        // U0 State IRQ For TD.7.17
        // Disable DFP State INT : U0[5]
        ScalerSetBit(P3E_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

        // Disable DFP Compliance Mode Rcv Polling/LBPM INT : Rcv Polling/LBPM[3]
        ScalerSetBit(P3E_15_RTSSM_IRQ_04, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
        //========================
        // P3 PowerSaving IRQ Disable
        //========================

        // Disable PowerCut INT : PowerCut_On[1]
        ScalerSetBit(P3E_07_RTSSM_POWER_CUT_CTL_03, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

        // Disable PowerCut INT : PowerCut_Off_by_nsq[7] : Enable for extremely fast exit from U3.
        ScalerSetBit(P3E_07_RTSSM_POWER_CUT_CTL_03, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
#endif
    }
}

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer MAC AsyFIFO x1 Lane Reset Proc
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0UfpAsyFifoResetProc(void)
{
    //==========================
    // UFP0 Gen1/Gen2 AsyFifo
    //==========================
    // Gen1, fifo_rx1_delay_g1_u
    // Set Gen1 AsyFIFO_1_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P3D_02_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen1, fifo_rx0_delay_g1_u
    // Set Gen1 AsyFIFO_0_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P3D_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen2, fifo_rx1_delay_g2_u
    // Set Gen2 AsyFIFO_1_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P3C_02_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen2, fifo_rx0_delay_g2_u
    // Set Gen2 AsyFIFO_0_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P3C_01_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    //==========================
    // UFP1 Gen1/Gen2 AsyFifo
    //==========================

    // Gen1, fifo_rx1_delay_g1_u
    // Set Gen1 AsyFIFO_1_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P3D_F2_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen1, fifo_rx0_delay_g1_u
    // Set Gen1 AsyFIFO_0_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P3D_F1_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen2, fifo_rx1_delay_g2_u
    // Set Gen2 AsyFIFO_1_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P3C_D2_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen2, fifo_rx0_delay_g2_u
    // Set Gen2 AsyFIFO_0_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P3C_D1_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    //==========================
    // UFP0 Reset Gen1/Gen2 AsyFifo
    //==========================
    ScalerSetBit(P3D_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P3C_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    //==========================
    // UFP1 Reset Gen1/Gen2 AsyFifo
    //==========================
    ScalerSetBit(P3D_F0_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P3C_D0_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer MAC AsyFIFO x1 Lane Reset Proc
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0DfpAsyFifoResetProc(void)
{
    //==========================
    // DFP Gen1/Gen2 AsyFifo
    //==========================
    // Gen1, fifo_rx1_delay_g1_u
    // Set Gen1 AsyFIFO_1_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P82_02_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen1, fifo_rx0_delay_g1_u
    // Set Gen1 AsyFIFO_0_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P82_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen2, fifo_rx1_delay_g2_u
    // Set Gen2 AsyFIFO_1_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P81_02_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    // Gen2, fifo_rx0_delay_g2_u
    // Set Gen2 AsyFIFO_0_Rx1 WL to 1 & write-protect[5][4]
    ScalerSetBit(P82_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));

    //==========================
    // DFP Reset Gen1/Gen2 AsyFifo
    //==========================
    ScalerSetBit(P82_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P81_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
}
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Description  : Clear USB3 Retimer P3 Status
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0ClearLowPowerStateStatus(void)
{
    SET_USB3_RETIMER_P3_STATUS(_USB3_RETIMER_NO_ACTION);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer P3 Status
// Input Value  : None
// Output Value : GET_USB3_RETIMER_P3_STATUS
//----------------------------------------------------------------------------------------------------
EnumUsb3RetimerP3State ScalerUsb3RetimerMac0GetLowPowerStateStatus(void)
{
    return GET_USB3_RETIMER_P3_STATUS();
}

//----------------------------------------------------------------------------------------------------
// Description  : Set USB3 Retimer P3 Status to At_P3_Power_Saving
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0SetAtLowPowerStateStatus(void)
{
    SET_USB3_RETIMER_P3_STATUS(_USB3_RETIMER_AT_P3_PS);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Detect NSQ at P3 state
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
bit ScalerUsb3RetimerMac0GetDetectNSQFlag(void)
{
    return ScalerGetBit(P3B_1E_SS_DATA_RCV_U_04, _BIT3);
}

//------------------------------------------------------------------------------
// Description  : USB3 Repeater Disable U3 IRQ Enable to avoid unexpected power off
// Input Value  : void
// Output Value : void
//------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0DisableU3IRQ(void)
{
    // Clean & Disable U3 state INT Flag
    ScalerSetBit_EXINT3(P3E_14_RTSSM_IRQ_03, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT6);
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Power Cut ON FW Mode to HW Mode Sleep Flow
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0PowerCutOnSleep(void)
{
    // If RTSSM State is in U3 State, set the low power control to HW Mode.
    if(ScalerGetByte(P3E_08_RTSSM_TOP_CONTROL_00) == 0x07)
    {
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL == _USB3_PS_SUPPORT_LEVEL_1)
        ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_1)
        ScalerSetByte(P3E_04_RTSSM_POWER_CUT_CTL_00, 0x80);
        ScalerSetByte(P3E_04_RTSSM_POWER_CUT_CTL_00, 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_2)
        ScalerSetBit(P3E_5F_RTSSM_DUMMY_05, ~_BIT6, 0x00);
#endif
    }
    else
    {
        // Some Hosts may enter the U3 State later after PN->Fake Saving flow
        SET_USB_REPEATER_PIND_FAKE_SAVING_U3_LATE();

        // Enable UFP U3 INT
        ScalerSetBit(P3E_14_RTSSM_IRQ_03, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT7);
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer Power Cut OFF FW Mode Awake Flow
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0PowerCutOffAwake(void)
{
    // Set Power Cut to FW Mode and Enable the Mac/DFP PHY Reset
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL == _USB3_PS_SUPPORT_LEVEL_1)
    ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_1)
    ScalerSetByte(P3E_04_RTSSM_POWER_CUT_CTL_00, 0xFE);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_2)
    ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
#endif
    // Set the Power Cut Register to OFF Status
    ScalerUsb3RepeaterMacPowerCutOffProcess_EXINT3();

    // Release the Reset Signal
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL == _USB3_PS_SUPPORT_LEVEL_1)
    ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~(_BIT7 | _BIT3), 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_1)
    ScalerSetByte(P3E_04_RTSSM_POWER_CUT_CTL_00, 0xD4);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_2)
    ScalerSetBit(P3E_04_RTSSM_POWER_CUT_CTL_00, ~(_BIT6 | _BIT5), _BIT6);
#endif
}

//----------------------------------------------------------------------------------------------------
// Description  : Clear USB3 Retimer P3 Status
// Input Value  : EnumTypeCPcbPort
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0PowerCutOffInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // Disable LFPS Global : OFF-Region LFPS Global Enable, Default : Enable, Only For RL6829
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    ScalerSetBit(P3B_24_LFPS_GLOBAL_SETTING_U, ~_BIT7, 0x00);
#endif

    // Retimer Mac0 UFP Off Region Initial
    ScalerUsb3RetimerMac0UfpOffRegionInitial(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort));

    // Re-Initial PortConfig Setting
    ScalerUsb3RetimerMac0UfpPortConfigSetting_EXINT3();

    // Retimer Mac0 DFP Off Region Initial
    ScalerUsb3RetimerMac0DfpOffRegionInitial();

    // Re-Initial PortConfig Setting
    ScalerUsb3RetimerMac0DfpPortConfigSetting_EXINT3();

#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
    // Set DFP BLR Tx Comma Debounce to 0
    ScalerSetBit(P82_E0_TX_MUX_D_00, ~(_BIT1 | _BIT0), 0x00);
#endif

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // ByPass Gen1 CommaDetect rxeq_valid_delay_cnt
    ScalerSetByte(P3D_0A_COM_DETECT_U_03, 0x00);
    ScalerSetByte(P82_0A_COM_DETECT_D_03, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // UFP0
    {
        // Release UFP PIPE0 PhyRate/LaneCount to HW Mode
        ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
    }
    else
    {
        // Release UFP PIPE1 PhyRate/LaneCount to HW Mode
        ScalerSetBit(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
    }
#else
    // Release UFP PIPE0 PhyRate/LaneCount to HW Mode
    ScalerSetBit(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

    // Release DFP PIPE PhyRate/LaneCount to HW Mode
    ScalerSetBit(P3E_C6_PIPE_CONTROL_D_06, ~(_BIT5 | _BIT3), 0x00);

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
    // Release AsyFIFO
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // UFP0
    {
        //==========================
        // Set UFP0 Reset Gen1/Gen2 AsyFifo
        //==========================
        ScalerSetBit(P3D_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P3C_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
    }
    else
    {
        //==========================
        // Set UFP1 Reset Gen1/Gen2 AsyFifo
        //==========================
        ScalerSetBit(P3D_F0_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P3C_D0_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
    }
#else
    //==========================
    // Set UFP0 Reset Gen1/Gen2 AsyFifo
    //==========================
    ScalerSetBit(P3D_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P3C_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
#endif

    //==========================
    // Set DFP Reset Gen1/Gen2 AsyFifo
    //==========================
    ScalerSetBit(P82_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit(P81_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

    // Retimer Mac0 Off Region Enable
    ScalerUsb3RetimerMac0OffRegionEnable(_ENABLE);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Set LBPM Phy Rate / Lane Count Back to HW Mode
    ScalerSetBit(P3B_49_LBPM_DETECT_U_DUMMY_01, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
    ScalerSetBit(P3E_49_LBPM_DETECT_D_DUMMY_01, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
#endif

    // Enable U0 IRQ
    // When Retimer had entered P3, it will get into U0 INT to clear P3Entry Flag.
    ScalerSetBit(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0));

    // Release PIPE CMD_RxDetect to HW Mode
    ScalerSetBit(P3E_C0_PIPE_CONTROL_D_00, ~_BIT7, 0x00);

    // Enable Force P0 wait Rxdetect done
    ScalerSetBit(P3B_5A_UX_EXIT_DETECT_U_DUMMY_01, ~_BIT4, _BIT4);
    ScalerSetBit(P3E_5A_UX_EXIT_DETECT_D_DUMMY_01, ~_BIT4, _BIT4);

    // Disable Timer Event Timeout of Group 1
    ScalerSetBit_EXINT3(P3E_94_TIMER_GRP1_0, ~(_BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT2));
}

//----------------------------------------------------------------------------------------------------
// Description  : Clear USB3 Retimer LFPS Initial Setting
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0PowerCutOffLFPSInitialSetting(EnumTypeCPcbPort enumTypeCPcbPort)
{
    //========================
    // Set PortConfig PhyRate/LaneCount MAC Setting
    //========================
    if(g_ucUsb3RetimerMac0PhyRate == _USB_3_GEN2)
    {
        // Force LBPM Phy Rate FW Mode to Gen2
        ScalerSetBit(P3B_49_LBPM_DETECT_U_DUMMY_01, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit(P3E_49_LBPM_DETECT_D_DUMMY_01, ~(_BIT7 | _BIT6), _BIT6);
    }

    // UFP Mac LFPS U3_Exit Relatd Initial at OFF Region
    ScalerUsb3RetimerMac0UfpOffRegionU3ExitInitial();

    // DFP Mac LFPS U3_Exit Relatd Initial at OFF Region
    ScalerUsb3RetimerMac0DfpOffRegionU3ExitInitial();

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
    // Toggle UFP Aphy Tx Lane Reset to generate LFPS, Beforce ECO#1520
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // UFP0
    {
        if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Toggle Aphy Lane [1] for TypeC Orientation UNFLIP
            ScalerGDIPhyRxLanePower(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
            ScalerGDIPhyRxLanePower(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
        }
        else
        {
            // Toggle Aphy Lane [3] for TypeC Orientation FLIP
            ScalerGDIPhyRxLanePower(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
            ScalerGDIPhyRxLanePower(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
        }
    }
    else // UFP1
    {
        if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Toggle Aphy Lane [1] for TypeC Orientation UNFLIP
            ScalerGDIPhyRxLanePower(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
            ScalerGDIPhyRxLanePower(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
        }
        else
        {
            // Toggle Aphy Lane [3] for TypeC Orientation FLIP
            ScalerGDIPhyRxLanePower(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
            ScalerGDIPhyRxLanePower(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
        }
    }
#else
    if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
    {
        // Toggle Aphy Lane [1] for TypeC Orientation UNFLIP
        ScalerGDIPhyRxLanePower(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
        ScalerGDIPhyRxLanePower(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
    }
    else
    {
        // Toggle Aphy Lane [3] for TypeC Orientation FLIP
        ScalerGDIPhyRxLanePower(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
        ScalerGDIPhyRxLanePower(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
    }
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif

    // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = Back to HW Mode
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    if(ScalerGetBit(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // For UFP0 PIPE
    {
        // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = Back to HW Mode
        ScalerSetBit(P3B_C0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = Back to HW Mode
        ScalerSetBit(P3B_C2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Force PIPE Tx PowerDown Back to HW Mode
        ScalerSetBit(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
    }
    else // For UFP1 PIPE
    {
        // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = Back to HW Mode
        ScalerSetBit(P81_D0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = Back to HW Mode
        ScalerSetBit(P81_D2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Force PIPE Tx PowerDown Back to HW Mode
        ScalerSetBit(P81_D5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
    }
#else
    // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = Back to HW Mode
    ScalerSetBit(P3B_C0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = Back to HW Mode
    ScalerSetBit(P3B_C2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Force PIPE Tx PowerDown Back to HW Mode
    ScalerSetBit(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

    // Force DFP PIPE Tx PowerDown Back to HW Mode
    ScalerSetBit(P3E_C5_PIPE_CONTROL_D_05, ~_BIT7, 0x00);

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // Enable LFPS Global
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    ScalerSetBit(P3B_24_LFPS_GLOBAL_SETTING_U, ~_BIT7, _BIT7);
#else
    ScalerSetBit(P3B_07_RTSSM_GLOBAL_07, ~_BIT2, _BIT2);
#endif
#endif
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP Do RxDetect in U3 state
// Input Value  : void
// Output Value : void
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0U3DFPRxDetectTimeOut_WDINT(void)
{
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(_RX0);
#endif

    // w1c rx_detect_done_tx0_d
    ScalerSetBit_EXINT3(P3E_C9_PIPECTRL_DUMMY_01, ~(_BIT3 | _BIT2), _BIT2);

    // Control PIPE to Do CMD_Rxdetect
    ScalerSetBit_EXINT3(P3E_C0_PIPE_CONTROL_D_00, ~_BIT6, _BIT6);

    DELAY_30US_EXINT();

    ScalerSetBit_EXINT3(P3E_C0_PIPE_CONTROL_D_00, ~_BIT6, 0x00);

    // Check if Rx_detect done & detect fail
    if(ScalerGetBit_EXINT3(P3E_C9_PIPECTRL_DUMMY_01, _BIT2) == _BIT2)
    {
        // RxDetection Fail
        if(ScalerGetBit_EXINT3(P3E_C9_PIPECTRL_DUMMY_01, _BIT0) == 0x00)
        {
            // PowerCutOffInitial_Step(1) : Power Cut OFF Register FW Mode Setting Process
            ScalerUsb3RepeaterMacPowerCutOffProcess_EXINT3();

            // PowerCutOffInitial_Step(2) : Re-Initial LFPS Module
            ScalerUsb3RetimerMac0PowerCutOffLFPSInitialSetting(enumTypeCPcbPort);

            // PowerCutOffInitial_Step(3) : Clear USB3 Retimer P3 Status, Re-Initial Off Region
            ScalerUsb3RetimerMac0PowerCutOffInitialSetting(enumTypeCPcbPort);
        }
    }
}
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : USB3 Retimer MAC0 DFP Rx_Clk_Ctl Enable after U1/U2/U3 for Gen1x1 BLR mode
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0DfpU1U2U3JfmEnableTimeOut_WDINT(void)
{
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        // set rx_clk_ctl to Back HW Mode
        ScalerSetBit_EXINT3(P3E_17_RTSSM_DUMMY_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
        ScalerSetBit_EXINT3(P3E_17_RTSSM_DUMMY_00, ~(_BIT3 | _BIT2), _BIT2);
    }
}
#endif // End of #if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
#endif // End of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)

//--------------------------------------------------
// Description  : USB3 Rx0 Retimer INT Handler
// Input Value  : EnumPowerStatus
// Output Value : void
//--------------------------------------------------
void ScalerUsb3RetimerMac0IntHandler_EXINT3(EnumPowerStatus enumPowerStatus)
{
    //========================
    // DFP U0 state INT
    //========================
    // (1) TD.7.17 FW Solution
    if(ScalerGetBit_EXINT3(P3E_13_RTSSM_IRQ_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        // Delay tPortConfiguration(20~30us)
        DELAY_15US_EXINT();

        // Turn off 8b10b / 128/132 decode error reset
        ScalerSetBit_EXINT3(P3B_0C_RTSSM_STATE_CONTROL_01, ~_BIT0, 0x00);

        // Clean & Disable U0 state INT Flag
        ScalerSetBit_EXINT3(P3E_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), _BIT4);
    }

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)

    //========================
    // P3 Power Cut ON INT
    //========================
    if(ScalerGetBit_EXINT3(P3E_07_RTSSM_POWER_CUT_CTL_03, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable LFPS Global : ON-Region LFPS Global Enable
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
        ScalerSetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, ~_BIT2, 0x00);
#endif
        // Set Power Cut Register to ON Status
        ScalerUsb3RepeaterMacPowerCutOnProcess_EXINT3();

        // Set the PIPE CMD_Rxdetect to FW Mode
        ScalerSetBit_EXINT3(P3E_C0_PIPE_CONTROL_D_00, ~_BIT7, _BIT7);

        // Clean NSQ From Low to High INT Flag
        ScalerSetBit_EXINT3(P3B_1E_SS_DATA_RCV_U_04, ~(_BIT5 | _BIT3 | _BIT1), _BIT3);

        //========================
        // Set DFP reg_powerdown_init = 1 : Initial PowerDown = P3
        //========================
        ScalerSetBit_EXINT3(PC8_80_SPPHY_44, ~_BIT4, _BIT4);

        //========================
        // Force PIPE PhyRate/LaneCount Setting
        //========================
        if(g_ucUsb3RetimerMac0PhyRate == _USB_3_GEN2)
        {
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // UFP0
            {
                // Force UFP PIPE0 PhyRate to Gen2
                ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
            }
            else
            {
                // Force UFP PIPE1 PhyRate to Gen2
                ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
            }
#else
            // Force UFP PIPE0 PhyRate to Gen2
            ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
#endif

            // Force DFP PIPE PhyRate to Gen2
            ScalerSetBit_EXINT3(P3E_C6_PIPE_CONTROL_D_06, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        }

        // Force UFP PIPE
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // For UFP0 PIPE
        {
            // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = FW Mode
            ScalerSetBit_EXINT3(P3B_C0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = FW Mode
            ScalerSetBit_EXINT3(P3B_C2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            // Force PIPE Tx PowerDown to P3
            ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
        }
        else // For UFP1 PIPE
        {
            // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = FW Mode
            ScalerSetBit_EXINT3(P81_D0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = FW Mode
            ScalerSetBit_EXINT3(P81_D2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            // Force PIPE Tx PowerDown to P3
            ScalerSetBit_EXINT3(P81_D5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
        }
#else
        // Force PIPE Tx0 [txdetect_loopback , tx_elecidle] = FW Mode
        ScalerSetBit_EXINT3(P3B_C0_PIPE_CONTROL_U_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

        // Force PIPE Tx1 [txdetect_loopback , tx_elecidle] = FW Mode
        ScalerSetBit_EXINT3(P3B_C2_PIPE_CONTROL_U_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

        // Force PIPE Tx PowerDown to P3
        ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
#endif

        // Force DFP PIPE Tx PowerDown to P3
        ScalerSetBit_EXINT3(P3E_C5_PIPE_CONTROL_D_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

        // Set P3 PS Marco
        SET_USB3_RETIMER_P3_STATUS(_USB3_RETIMER_ENTER_P3_PS);
        g_bUsb3RetimerMac0P3Entry = _TRUE;

        // When there are no NSQ events detected on both UFP and DFP,
        // the NSQ IRQ will be enabled and the PowerCut_off_by_NSQ IRQ will be disabled
        if((ScalerGetBit_EXINT3(P3B_1E_SS_DATA_RCV_U_04, _BIT6) == 0x00) && (ScalerGetBit_EXINT3(P3E_1E_SS_DATA_RCV_04, _BIT6) == 0x00))
        {
            // Enable Detect NSQ Rising at U3 state IRQ
            ScalerSetBit_EXINT3(P3E_06_RTSSM_POWER_CUT_CTL_02, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0));

            // Disable Power Cut off Done by NSQ
            ScalerSetBit_EXINT3(P3E_07_RTSSM_POWER_CUT_CTL_03, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT7 | _BIT6));
        }

        // Enable Timer Event Timeout of Group 1 for Rxdetection
        ScalerSetBit_EXINT3(P3E_94_TIMER_GRP1_0, ~(_BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5 | _BIT2));

        // Clean P3 Power Cut ON INT Flag
        ScalerSetBit_EXINT3(P3E_07_RTSSM_POWER_CUT_CTL_03, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT0);
    }

#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(_RX0);
#endif

    //=============================================================================================
    // UFP NSQ Rising at U3 state || DFP NSQ Rising at U3 state INT || PowerCut_Off_Done_By_NSQ INT
    //=============================================================================================
    if((ScalerGetBit_EXINT3(P3E_06_RTSSM_POWER_CUT_CTL_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)) ||
       (ScalerGetBit_EXINT3(P3E_06_RTSSM_POWER_CUT_CTL_02, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2)) ||
       (ScalerGetBit_EXINT3(P3E_07_RTSSM_POWER_CUT_CTL_03, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)))
    {
        if(g_bUsb3RetimerMac0P3NSQIntEntry == _FALSE)
        {
#if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
            // First Step for [_P3_POWER_SOLUTION_HIGH_PIRORITY]
            // P3 Power Interfere FW Solution : For Power-On with Stable Delay or MCU/Flash Speed-Up
            if((enumPowerStatus == _POWER_STATUS_SAVING) || (enumPowerStatus == _POWER_STATUS_OFF))
            {
                ScalerUsb3RepeaterMacP3PowerInterfereSolution_EXINT3(enumTypeCPcbPort, _P3_POWER_SOLUTION_HIGH_PIRORITY);
            }
#endif
            // PowerCutOffInitial_Step(1) : Power Cut OFF Register FW Mode Setting Process
            ScalerUsb3RepeaterMacPowerCutOffProcess_EXINT3();

#if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
            // Second Step for [_P3_POWER_SOLUTION_MEDIUM_PIRORITY]
            // P3 Power Interfere FW Solution : Activate the adjacent Dx Port Phy in advance to avoid power interference and prevent BitError.
            if((enumPowerStatus == _POWER_STATUS_SAVING) || (enumPowerStatus == _POWER_STATUS_OFF))
            {
                ScalerUsb3RepeaterMacP3PowerInterfereSolution_EXINT3(enumTypeCPcbPort, _P3_POWER_SOLUTION_MEDIUM_PIRORITY);
            }
#endif
            // Check the Power Cut Status
            if(ScalerUsb3RepeaterMacCheckP3PowerCutOFF_EXINT3() == _FALSE)
            {
                // When Detecting NSQ but not Power on, use FW Mode to Force Power on
                ScalerUsb3RetimerMac0PowerCutOffAwake();
            }

            // Disable Force P0 shall Wait Rxdetect Done
            ScalerSetBit_EXINT3(P3B_5A_UX_EXIT_DETECT_U_DUMMY_01, ~_BIT4, 0x00);
            ScalerSetBit_EXINT3(P3E_5A_UX_EXIT_DETECT_D_DUMMY_01, ~_BIT4, 0x00);

            // PowerCutOffInitial_Step(2) : Re-Initial LFPS Module
            ScalerUsb3RetimerMac0PowerCutOffLFPSInitialSetting(enumTypeCPcbPort);

#if(_USB32_GEN2_P3_CV_FW_SOLUTION_SUPPORT == _ON)
            // FW Solution For Gen2x1 CV
            // Enable U3_Exit Handshake Fail INT
            if((g_ucUsb3RetimerMac0PhyRate == _USB_3_GEN2) && (g_ucUsb3RetimerMac0LaneCount == _USB_3_LANE_X1))
            {
                // Enable UFP U3_Exit Handshake Fail INT
                ScalerSetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, ~(_BIT7 | _BIT6 | _BIT3), (_BIT7 | _BIT6));
            }
#endif

            // PowerCutOffInitial_Step(3) : Clear USB3 Retimer P3 Status, Re-Initial Off Region
            ScalerUsb3RetimerMac0PowerCutOffInitialSetting(enumTypeCPcbPort);

#if(_USB32_P3_POWER_INTERFERE_SOLUTION_SUPPORT == _ON)
            // Third Step for [_P3_POWER_SOLUTION_LOW_PIRORITY]
            // P3 Power Interfere FW Solution : Activate the adjacent Module Which Need To Be Set At Final Setp
            if((enumPowerStatus == _POWER_STATUS_SAVING) || (enumPowerStatus == _POWER_STATUS_OFF))
            {
                ScalerUsb3RepeaterMacP3PowerInterfereSolution_EXINT3(enumTypeCPcbPort, _P3_POWER_SOLUTION_LOW_PIRORITY);
            }
#endif

#if(_TYPE_C_EMB_CTS_FLOW == _OFF)
            // Enable LFPS Global
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
            ScalerSetBit_EXINT3(P3B_24_LFPS_GLOBAL_SETTING_U, ~_BIT7, _BIT7);
#else
            ScalerSetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, ~_BIT2, _BIT2);
#endif
            // Set LBPM Phy Rate / Lane Count Back to HW Mode
            ScalerSetBit_EXINT3(P3B_49_LBPM_DETECT_U_DUMMY_01, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
            ScalerSetBit_EXINT3(P3E_49_LBPM_DETECT_D_DUMMY_01, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));
#endif

            // Set P3 PS Marco
            SET_USB3_RETIMER_P3_STATUS(_USB3_RETIMER_EXIT_P3_PS);
        }

        g_bUsb3RetimerMac0P3NSQIntEntry = _TRUE;

        // Clean P3 NSQ INT Flag
        ScalerSetBit_EXINT3(P3E_06_RTSSM_POWER_CUT_CTL_02, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT2));

        // Enable PowerCut INT : PowerCut_Off_by_nsq[7] : Enable for extremely fast exit from U3.
        ScalerSetBit_EXINT3(P3E_07_RTSSM_POWER_CUT_CTL_03, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0));
    }


#if(_USB32_GEN2_P3_CV_FW_SOLUTION_SUPPORT == _ON)
    //========================
    // UFP U3_Exit Handshake Fail INT
    //========================
    if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // Disable UFP Block Align : To Eliminate This FW Solution At Recovery State
        ScalerSetBit_EXINT3(P3C_09_BLOCK_ALIGN_01, ~_BIT7, 0x00);

        // Force UFP PIPE Power State to P0 : To Prevent Unexpected Power State P3<->P0 Loop
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
        {
            // Check if the UFP0 USB3 Lane Mux is Unflip.
            if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, _BIT5) == 0x00)
            {
                ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);
            }
            else
            {
                ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT4);
            }
        }
        else
        {
            // Check if the UFP1 USB3 Lane Mux is Unflip.
            if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, _BIT5) == 0x00)
            {
                ScalerSetBit_EXINT3(P81_D5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);
            }
            else
            {
                ScalerSetBit_EXINT3(P81_D5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT4);
            }
        }
#else
        // Check if the UFP0 USB3 Lane Mux is Unflip.
        if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, _BIT5) == 0x00)
        {
            ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);
        }
        else
        {
            ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT4);
        }
#endif

        // Enable DFP Recovery.TSx INT
        ScalerSetBit_EXINT3(P3E_14_RTSSM_IRQ_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT5 | _BIT4));

        // Clear and Disable UFP U3_Exit Handshake Fail IRQ
        ScalerSetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, ~(_BIT7 | _BIT6 | _BIT3), _BIT7);
    }

    //========================
    // DFP Recovery.TSx state INT
    //========================
    if(ScalerGetBit_EXINT3(P3E_14_RTSSM_IRQ_03, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
        {
            // Set UFP0 PIPE Power Control back to HW Mode
            ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }
        else
        {
            // Set UFP1 PIPE Power Control back to HW Mode
            ScalerSetBit_EXINT3(P81_D5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }
#else
        // Set UFP0 PIPE Power Control back to HW Mode
        ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
#endif

        // Enable UFP Block Align
        ScalerSetBit_EXINT3(P3C_09_BLOCK_ALIGN_01, ~_BIT7, _BIT7);

        // Clear and Disable DFP Recovery.TSx IRQ
        ScalerSetBit_EXINT3(P3E_14_RTSSM_IRQ_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), _BIT4);
    }
#endif

    //=================================
    // tU3_RxDetectDelay Timeout INT
    //=================================
    if(ScalerGetBit_EXINT3(P3E_94_TIMER_GRP1_0, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        // Enable 10 ms Timer Event For Enable DFP Rx_Clk_Ctl FW Control TimerEvent
        ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_USB_U3_DFP_RXDETECT);

        // Clean tU3_RxDetectDelay Timeout INT Flag
        ScalerSetBit_EXINT3(P3E_94_TIMER_GRP1_0, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
    }


    //========================
    // UFP U0 state INT
    //========================
    // (1) TD.7.17 FW Solution(UFP)
    if(ScalerGetBit_EXINT3(P3B_13_RTSSM_IRQ_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        g_bUsb3RetimerMac0P3Entry = _FALSE;
        g_bUsb3RetimerMac0P3NSQIntEntry = _FALSE;

        // Enable Force P0 wait Rxdetect done
        ScalerSetBit_EXINT3(P3B_5A_UX_EXIT_DETECT_U_DUMMY_01, ~_BIT4, _BIT4);
        ScalerSetBit_EXINT3(P3E_5A_UX_EXIT_DETECT_D_DUMMY_01, ~_BIT4, _BIT4);

        // Disable Detect NSQ Rising at U3 state IRQ
        ScalerSetBit_EXINT3(P3E_06_RTSSM_POWER_CUT_CTL_02, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

        if(GET_TYPE_C_PIN_ASSIGNMENT_EXINT3(enumTypeCPcbPort) != _TYPE_C_PIN_ASSIGNMENT_NONE)
        {
            // Set the Power Cut Control to FW Mode
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL == _USB3_PS_SUPPORT_LEVEL_1)
            ScalerSetBit_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, _BIT7);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_1)
            ScalerSetBit_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, ~(_BIT6 | _BIT4 | _BIT2), (_BIT6 | _BIT4 | _BIT2));
            ScalerSetBit_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, _BIT7);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_2)
            ScalerSetBit_EXINT3(P3E_5F_RTSSM_DUMMY_05, ~_BIT6, _BIT6);
#endif
        }
        else
        {
#if(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL == _USB3_PS_SUPPORT_LEVEL_1)
            ScalerSetBit_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_1)
            ScalerSetByte_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, 0x80);
            ScalerSetByte_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, 0x00);
#elif(_HW_USB3_REPEATER_MAC_POWER_SAVING_SUPPORT_LEVEL > _USB3_PS_SUPPORT_LEVEL_2)
            ScalerSetBit_EXINT3(P3E_5F_RTSSM_DUMMY_05, ~_BIT6, 0x00);
#endif
        }

#if(_USB32_GEN2_P3_CV_FW_SOLUTION_SUPPORT == _ON)
        // Clear and Disable UFP U3_Exit Handshake Fail IRQ
        ScalerSetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, ~(_BIT7 | _BIT6 | _BIT3), _BIT7);
#endif
        // Clean & Disable U0 state INT Flag
        ScalerSetBit_EXINT3(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), _BIT4);
    }


    //========================
    // DFP U3 state INT
    //========================
    if(ScalerGetBit_EXINT3(P3E_14_RTSSM_IRQ_03, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
        ScalerSetBit_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, ~_BIT7, 0x00);
#else
        ScalerSetByte_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, 0x80);
        ScalerSetByte_EXINT3(P3E_04_RTSSM_POWER_CUT_CTL_00, 0x00);
#endif
        // Clean & Disable U3 state INT Flag
        ScalerSetBit_EXINT3(P3E_14_RTSSM_IRQ_03, ~(_BIT7 | _BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT6);
    }
#endif // End of #if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)


    //========================
    // UFP U1 state INT
    //========================
#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
        if(ScalerGetBit_EXINT3(P3B_13_RTSSM_IRQ_02, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // set rx_clk_ctl to FW Mode
            ScalerSetBit_EXINT3(P3E_17_RTSSM_DUMMY_00, ~(_BIT3 | _BIT2), _BIT3);

            // Set Enter U1 State
            g_bUsb3RetimerMac0U1stateEntry = _TRUE;

            // Clear IRQ
            ScalerSetBit_EXINT3(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT2);
        }
#endif // End of #if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
    }
#endif // End of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)

    //========================
    // UFP RxDetect state INT
    //========================
    // (1) UFP Phy Keep ST1/ST2 (Once entered U3) (2) Disable JFM
    if(ScalerGetBit_EXINT3(P3B_11_RTSSM_IRQ_00, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        //========================
        // DFP RxDetect state INT
        //========================
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
        // Reset Phy rate control to HW mode
        ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), 0x00);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), 0x00);
#endif
        // Reset Tx Bist to EB
        ScalerSetBit_EXINT3(P3D_B0_TXBIST_PAT_SEL_G1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
        ScalerSetBit_EXINT3(P3C_A0_TXBIST_PAT_SEL_G2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif
        // Disable Ping.LFPS IRQ
        ScalerSetBit_EXINT3(P3B_4D_PING_LFPS_DETECT_U_03, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);

#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
        // Reset LBPM Phy Rate to HW Mode, Before ECO#1511
        ScalerSetBit_EXINT3(P3B_49_LBPM_DETECT_U_DUMMY_01, ~(_BIT7 | _BIT6), _BIT7);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)

#endif
        if(ScalerUsb3RetimerPhyGetCtsCtrl() == _ON)
        {
            // Disable UFP Phy Lane Enable Solution,cP7.8 FW Solution
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
                // Disable Tx_ones_zero For FW Solution At CP7,8
                ScalerSetByte_EXINT3(P96_A2_SPPHY_34, 0x02);
#endif
#if(_D0_USB_LANE == _USB_3_LANE_X2)
                if(GET_USB_HUB_U3_LANE_SUPPORT() == _USB_3_LANE_X2)
                {
                    // Enable lane
                    if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == 0x00)
                    {
                        ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                        ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
                    }
                    else if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                    {
                        ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                        ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                    }
                }
#endif // End of #if(_D0_USB_LANE == _USB_3_LANE_X2)
#endif // End of #if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
            }
            else
            {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
                // Disable Tx_ones_zero For FW Solution At CP7,8
                ScalerSetByte_EXINT3(PC9_A2_SPPHY_34, 0x02);
#endif
#if(_D1_USB_LANE == _USB_3_LANE_X2)
                if(GET_USB_HUB_U3_LANE_SUPPORT() == _USB_3_LANE_X2)
                {
                    // Enable lane
                    if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == 0x00)
                    {
                        ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                        ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
                    }
                    else if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                    {
                        ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                        ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                    }
                }
#endif // End of #if(_D1_USB_LANE == _USB_3_LANE_X2)
#endif // End of #if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
            }
#else
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
            // Disable Tx_ones_zero For FW Solution At CP7,8
            ScalerSetByte_EXINT3(P96_A2_SPPHY_34, 0x02);
#endif
#endif // End of #if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        }

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
        if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
        {
            // UFP Phy U3-> RxDetect Setting (Shall keep st1/st2)
            if(g_bUsb3RetimerMac0U3stateEntry == _TRUE)
            {
                // [4] reg_rst_mode = 1'b0 => keep ST1/ST2
                ScalerSetBit_EXINT3(PEC_10_JCDR_00, ~_BIT4, 0x00);
            }

            // Clear U1/U2/U3 Entry Flag by  U1/2/3 -> RxDetect
            g_bUsb3RetimerMac0U3stateEntry = _FALSE;
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
            g_bUsb3RetimerMac0U2stateEntry = _FALSE;
            g_bUsb3RetimerMac0U1stateEntry = _FALSE;

            // set rx_clk_ctl to HW Mode
            ScalerSetBit_EXINT3(P3E_17_RTSSM_DUMMY_00, ~(_BIT3 | _BIT2), 0x00);
#endif // End of #if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
        }
#endif // End of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // UFP0
        {
            // Release UFP PIPE0 PhyRate/LaneCount to HW Mode
            ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
        }
        else
        {
            // Release UFP PIPE1 PhyRate/LaneCount to HW Mode
            ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
        }
#else
        // Release UFP PIPE0 PhyRate/LaneCount to HW Mode
        ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT3), 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

        // Release DFP PIPE PhyRate/LaneCount to HW Mode
        ScalerSetBit_EXINT3(P3E_C6_PIPE_CONTROL_D_06, ~(_BIT5 | _BIT3), 0x00);

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
        // Reset Gen1 CommaDetect rxeq_valid_delay_cnt to 0x0A(1ms)
        ScalerSetByte_EXINT3(P3D_0A_COM_DETECT_U_03, 0x0A);
        ScalerSetByte_EXINT3(P82_0A_COM_DETECT_D_03, 0x0A);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

        if(g_bUsb3RetimerMac0P3Entry == _TRUE)
        {
            // Set P3 Status marco to Exit P3
            SET_USB3_RETIMER_P3_STATUS(_USB3_RETIMER_EXIT_P3_PS);
            g_bUsb3RetimerMac0P3Entry = _FALSE;
        }
        else
        {
            // Clear P3 Status Marco
            SET_USB3_RETIMER_P3_STATUS(_USB3_RETIMER_NO_ACTION);
        }
#endif

        // Clean RxDetect state INT Flag
        ScalerSetBit_EXINT3(P3B_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT6);
    }

    //========================
    // UFP Speeddetect state INT
    //========================
    if(ScalerGetBit_EXINT3(P3B_11_RTSSM_IRQ_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
        if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
        {
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
            // Set DFP BLR Tx Comma Debounce to 0x02
            ScalerSetBit_EXINT3(P82_E0_TX_MUX_D_00, ~(_BIT1 | _BIT0), _BIT1);

            // Enable UFP State INT : Polling.Idle[5]
            ScalerSetBit_EXINT3(P3B_12_RTSSM_IRQ_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0));

            // Enable UFP State INT : U1[3]
            ScalerSetBit_EXINT3(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0));

            // Enable UFP State INT : U2[1]
            ScalerSetBit_EXINT3(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
#endif
            // Enable UFP State INT : U3[7], Recovery.TSx[5]
            ScalerSetBit_EXINT3(P3B_14_RTSSM_IRQ_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0));


            //========================
            // Disable UFP Tx SSC When FallBack or level Compliance Mode
            //========================
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
            ScalerSetBit_EXINT3(P96_40_SSC_TX_00, ~_BIT1, 0x00);

            // UFP1 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
            ScalerSetBit_EXINT3(PC9_40_SSC_TX_00, ~_BIT1, 0x00);
#else
            // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
            ScalerSetBit_EXINT3(P96_40_SSC_TX_00, ~_BIT1, 0x00);
#endif
            //========================
            // Disable DFP Tx SSC When FallBack or level Compliance Mode
            //========================
            // [1] reg_ssc_en_tx = 1'b0 => SSC OFF
            ScalerSetBit_EXINT3(PC8_10_SSC_TX_00, ~_BIT1, 0x00);
        }
#endif

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00) // UFP0
        {
            //==========================
            // Set UFP0 Reset Gen1/Gen2 AsyFifo
            //==========================
            ScalerSetBit_EXINT3(P3D_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetBit_EXINT3(P3C_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
        else
        {
            //==========================
            // Set UFP1 Reset Gen1/Gen2 AsyFifo
            //==========================
            ScalerSetBit_EXINT3(P3D_F0_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetBit_EXINT3(P3C_D0_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
#else
        //==========================
        // Set UFP0 Reset Gen1/Gen2 AsyFifo
        //==========================
        ScalerSetBit_EXINT3(P3D_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit_EXINT3(P3C_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

        //==========================
        // Set DFP Reset Gen1/Gen2 AsyFifo
        //==========================
        ScalerSetBit_EXINT3(P82_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit_EXINT3(P81_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
        // Record USB3 Phy Rate For PowerSaving
        g_ucUsb3RetimerMac0PhyRate = _USB_3_GEN1;
#endif
        // Clean Speeddetect state INT Flag
        ScalerSetBit_EXINT3(P3B_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT4);
    }

    //========================
    // UFP PortConfig state INT
    //========================
    // (1) PortConfig Change Gen2/x2 Lane Register
    if(ScalerGetBit_EXINT3(P3B_11_RTSSM_IRQ_00, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        //=====================
        // Gen2 / Gen1 Mode Setting
        //=====================
        if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == _BIT7)
        {
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
                ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_10G);
#endif
            }
            else
            {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
                ScalerUsb3RetimerUfpPhy1UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_10G);
#endif
            }
#else
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
            ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_10G);
#endif
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
            // Record USB3 Phy Rate For PowerSaving
            g_ucUsb3RetimerMac0PhyRate = _USB_3_GEN2;
#endif
        }
        else
        {
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
                ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_5G);
#endif
            }
            else
            {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
                ScalerUsb3RetimerUfpPhy1UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_5G);
#endif
            }
#else
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
            ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_5G);
#endif
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
            // Record USB3 Phy Rate For PowerSaving
            g_ucUsb3RetimerMac0PhyRate = _USB_3_GEN1;
#endif
        }

        // USB3 Retimer UFP MAC PortConfig State Config
        ScalerUsb3RetimerMac0UfpPortConfigSetting_EXINT3();

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
        if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
        {
            // Disable U1/U2/U3/RecoveryTSx INT When not in Gen1x1_BLR
            if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, (_BIT7 | _BIT6)) != 0x00)
            {
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
                // Disable UFP State INT : Polling.Idle[5]
                ScalerSetBit_EXINT3(P3B_12_RTSSM_IRQ_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

                // Disable UFP State INT : U1[3]
                ScalerSetBit_EXINT3(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

                // Disable UFP State INT : U2[1]
                ScalerSetBit_EXINT3(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
#endif
                // Disable UFP State INT : U3[7], Recovery.TSx[5]
                ScalerSetBit_EXINT3(P3B_14_RTSSM_IRQ_03, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
            }
        }
#endif

#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
        //=====================
        // x2 / x1 Lane Mode Setting
        //=====================
        if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT6) == _BIT6)
        {
            // Record USB3 Phy Rate For PowerSaving
            g_ucUsb3RetimerMac0LaneCount = _USB_3_LANE_X2;
        }
        // x1 Lane Mode Reset
        else
        {
            // Record USB3 Phy Rate For PowerSaving
            g_ucUsb3RetimerMac0LaneCount = _USB_3_LANE_X1;
        }
#endif

        // Clean PortConfig state INT Flag
        ScalerSetBit_EXINT3(P3B_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT2);
    }

    //========================
    // DFP PortConfig state INT
    //========================
    if(ScalerGetBit_EXINT3(P3E_11_RTSSM_IRQ_00, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        // USB3 Retimer DFP MAC PortConfig State Config
        ScalerUsb3RetimerMac0DfpPortConfigSetting_EXINT3();

        // Clean PortConfig state INT Flag
        ScalerSetBit_EXINT3(P3E_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT2);
    }

    //========================
    // UFP Polling.RxEQ state INT
    //========================
    if(ScalerGetBit_EXINT3(P3B_11_RTSSM_IRQ_00, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Delay for Waiting TSEQ
        DELAY_XUS_EXINT(100);

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
        {
            //==========================
            // Release UFP0 Gen1/Gen2 AsyFifo
            //==========================
            ScalerSetBit_EXINT3(P3D_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit_EXINT3(P3C_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
        }
        else
        {
            //==========================
            // Release UFP1 Gen1/Gen2 AsyFifo
            //==========================
            ScalerSetBit_EXINT3(P3D_F0_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit_EXINT3(P3C_D0_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
        }
#else
        //==========================
        // Release UFP0 Gen1/Gen2 AsyFifo
        //==========================
        ScalerSetBit_EXINT3(P3D_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit_EXINT3(P3C_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
        if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
        {
            if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == 0x00)
            {
                // Disable Early Local Loopback For Gen1 BLR Enter Passthrough Loopback
                ScalerSetBit_EXINT3(P3B_10_RTSSM_STATE_CONTROL_05, ~_BIT0, 0x00);
            }
        }
#endif // End of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)

        // Clean Polling.RxEQ state INT Flag
        ScalerSetBit_EXINT3(P3B_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT0);
    }


    //========================
    // DFP Polling.RxEQ state INT
    //========================
    if(ScalerGetBit_EXINT3(P3E_11_RTSSM_IRQ_00, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Delay for Waiting 2 Lane Data Valid both asserted
        DELAY_XUS_EXINT(20);

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
        //==========================
        // Release DFP Reset Gen1/Gen2 AsyFifo
        //==========================
        ScalerSetBit_EXINT3(P82_00_GEN1_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit_EXINT3(P81_00_GEN2_ASYNCHRONOUS_FIFO_CTRL_00, ~(_BIT7 | _BIT6), 0x00);
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

        // Clean Polling.RxEQ state INT Flag
        ScalerSetBit_EXINT3(P3E_11_RTSSM_IRQ_00, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT0);
    }


#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        // BLR Solution : Polling.Idle, Recovery.TSx, U1, U2, U3
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
        //========================
        // UFP Polling.Idle state INT
        //========================
        if(ScalerGetBit_EXINT3(P3B_12_RTSSM_IRQ_01, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
        {
            // Set DFP BLR Tx Comma Debounce to 0
            ScalerSetBit_EXINT3(P82_E0_TX_MUX_D_00, ~(_BIT1 | _BIT0), 0x00);

            // Clean Polling.Idle state INT Flag
            ScalerSetBit_EXINT3(P3B_12_RTSSM_IRQ_01, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT4);
        }
#endif
        //========================
        // UFP Recovery.TSx state INT
        //========================
        if(ScalerGetBit_EXINT3(P3B_14_RTSSM_IRQ_03, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
        {
            // UFP Phy Keep ST1/ST2 (Once entered U3)
            // Identify U3 --> Recovery Case
            if(g_bUsb3RetimerMac0U3stateEntry == _TRUE)
            {
                // [4] reg_rst_mode = 1'b0 => keep ST1/ST2
                ScalerSetBit_EXINT3(PEC_10_JCDR_00, ~_BIT4, 0x00);
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
                // Enable 4ms Timer Event For Enable DFP Rx_Clk_Ctl FW Control TimerEvent
                ScalerTimerWDActivateTimerEvent_EXINT0(4, _SCALER_WD_TIMER_EVENT_USB_HUB_U1U2U3_DFP_JFM_ENABLE_TIMEOUT);
#endif
                g_bUsb3RetimerMac0U3stateEntry = _FALSE;
            }
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
            if(g_bUsb3RetimerMac0U2stateEntry == _TRUE)
            {
                // Enable 2ms Timer Event For Enable DFP Rx_Clk_Ctl FW Control TimerEvent
                ScalerTimerWDActivateTimerEvent_EXINT0(2, _SCALER_WD_TIMER_EVENT_USB_HUB_U1U2U3_DFP_JFM_ENABLE_TIMEOUT);

                g_bUsb3RetimerMac0U2stateEntry = _FALSE;
            }

            if(g_bUsb3RetimerMac0U1stateEntry == _TRUE)
            {
                // Enable 2ms Timer Event For Enable DFP Rx_Clk_Ctl FW Control TimerEvent
                ScalerTimerWDActivateTimerEvent_EXINT0(2, _SCALER_WD_TIMER_EVENT_USB_HUB_U1U2U3_DFP_JFM_ENABLE_TIMEOUT);

                g_bUsb3RetimerMac0U1stateEntry = _FALSE;
            }
#endif
            // Clean Recovery state INT Flag
            ScalerSetBit_EXINT3(P3B_14_RTSSM_IRQ_03, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT4);
        }

#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
        //========================
        // UFP U2 state INT
        //========================
        if(ScalerGetBit_EXINT3(P3B_13_RTSSM_IRQ_02, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // set rx_clk_ctl to FW Mode
            ScalerSetBit_EXINT3(P3E_17_RTSSM_DUMMY_00, ~(_BIT3 | _BIT2), _BIT3);

            // Set Enter U2 State
            g_bUsb3RetimerMac0U2stateEntry = _TRUE;

            // Clear IRQ
            ScalerSetBit_EXINT3(P3B_13_RTSSM_IRQ_02, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT0);
        }
#endif // End of #if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)

        //========================
        // UFP U3 State INT
        //========================
        // UFP U3 State
        if(ScalerGetBit_EXINT3(P3B_14_RTSSM_IRQ_03, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
#if(_USB32_GEN1_BLR_FW_SOLUTION_SUPPORT == _ON)
            // set rx_clk_ctl to FW Mode
            ScalerSetBit_EXINT3(P3E_17_RTSSM_DUMMY_00, ~(_BIT3 | _BIT2), _BIT3);
#endif
            // [4] reg_rst_mode = 1'b1 => reset ST1/ST2
            ScalerSetBit_EXINT3(PEC_10_JCDR_00, ~_BIT4, _BIT4);

            // Identify U3 --> Recovery/Rxdetect Case
            g_bUsb3RetimerMac0U3stateEntry = _TRUE;

            // Clear IRQ
            ScalerSetBit_EXINT3(P3B_14_RTSSM_IRQ_03, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), _BIT6);
        }
    }
#endif // End of #if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)


    //========================
    // UFP Compliance Rcv Polling/LBPM INT
    //========================
    if(ScalerGetBit_EXINT3(P3B_15_RTSSM_IRQ_04, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        // Set Unexpected Used Lane to P3 Mode
        ScalerUsb3RetimerMac0UfpExitCPbyPollingSolution_EXINT3();

        // Disable UFP Compliance Mode FW Solution Setting
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
        // Reset Phy rate control to HW mode
        ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), 0x00);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), 0x00);
#endif
        // Reset Tx Bist to EB
        ScalerSetBit_EXINT3(P3D_B0_TXBIST_PAT_SEL_G1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
        ScalerSetBit_EXINT3(P3C_A0_TXBIST_PAT_SEL_G2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif
        // Disable Ping.LFPS IRQ
        ScalerSetBit_EXINT3(P3B_4D_PING_LFPS_DETECT_U_03, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT5);
#endif
        if(ScalerUsb3RetimerPhyGetCtsCtrl() == _ON)
        {
            // Disable UFP Phy Lane Enable Solution,cP7.8 FW Solution
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
                // Disable Tx_ones_zero For FW Solution At CP7,8
                ScalerSetByte_EXINT3(P96_A2_SPPHY_34, 0x02);
#endif
#if(_D0_USB_LANE == _USB_3_LANE_X2)
                if(GET_USB_HUB_U3_LANE_SUPPORT() == _USB_3_LANE_X2)
                {
                    // Enable lane
                    if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == 0x00)
                    {
                        ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                        ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
                    }
                    else if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                    {
                        ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                        ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                    }
                }
#endif // End of #if(_D0_USB_LANE == _USB_3_LANE_X2)
#endif // End of #if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
            }
            else
            {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
                // Disable Tx_ones_zero For FW Solution At CP7,8
                ScalerSetByte_EXINT3(PC9_A2_SPPHY_34, 0x02);
#endif
#if(_D1_USB_LANE == _USB_3_LANE_X2)
                if(GET_USB_HUB_U3_LANE_SUPPORT() == _USB_3_LANE_X2)
                {
                    // Enable lane
                    if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == 0x00)
                    {
                        ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                        ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
                    }
                    else if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                    {
                        ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                        ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                    }
                }
#endif // End of #if(_D1_USB_LANE == _USB_3_LANE_X2)
#endif // End of #if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
            }
#else // (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
            // Disable Tx_ones_zero For FW Solution At CP7,8
            ScalerSetByte_EXINT3(P96_A2_SPPHY_34, 0x02);
#endif
#endif // End of #if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        }

        // Clean & Disable UFP Compliance Rcv Polling/LBPM INT
        ScalerSetBit_EXINT3(P3B_15_RTSSM_IRQ_04, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), _BIT2);
    }

    //========================
    // DFP Compliance Rcv Polling/LBPM INT
    //========================
    if(ScalerGetBit_EXINT3(P3E_15_RTSSM_IRQ_04, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        // Set Unexpected Used Lane to P3 Mode
        ScalerUsb3RetimerMac0DfpExitCPbyPollingSolution_EXINT3();

        // Clean & Disable UFP Compliance Rcv Polling/LBPM INT
        ScalerSetBit_EXINT3(P3E_15_RTSSM_IRQ_04, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT0), _BIT2);
    }

    //========================
    // UFP Compliance state INT
    //========================
    if(ScalerGetBit_EXINT3(P3B_14_RTSSM_IRQ_03, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
        if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
        {
            // Enable UFP Tx SSC
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
                // UFP0 - [1] reg_ssc_en_tx = 1'b1 => SSC ON
                ScalerSetBit_EXINT3(P96_40_SSC_TX_00, ~_BIT1, _BIT1);
            }
            else
            {
                // UFP1 - [1] reg_ssc_en_tx = 1'b1 => SSC ON
                ScalerSetBit_EXINT3(PC9_40_SSC_TX_00, ~_BIT1, _BIT1);
            }
#else
            // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
            ScalerSetBit_EXINT3(P96_40_SSC_TX_00, ~_BIT1, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

            // Enable DFP Tx SSC
            // [1] reg_ssc_en_tx = 1'b1 => SSC ON
            ScalerSetBit_EXINT3(PC8_10_SSC_TX_00, ~_BIT1, _BIT1);
        }
#endif

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
        {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
            if(ScalerUsb3RetimerPhyGetCtsCtrl() == _ON)
            {
                ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_5G);

                if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == 0x00)
                {
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE2);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
                }
                else if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE0);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
                }

#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
                // Enable Tx_ones_zero For FW Solution At CP7,8
                ScalerSetByte_EXINT3(P96_A2_SPPHY_34, 0x22);
#endif
                // Toggle lane/cdr enable
                ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);

                DELAY_XUS_EXINT(200);

                // Toggle lane/cdr enable
                if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == 0x00)
                {
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE2);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
                }
                else if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE0);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                    ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
                }
            }
#endif

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
            if(ScalerUsb3RetimerPhyGetCtsCtrl() == _ON)
            {
                ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE0);
                ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
                ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE2);
                ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
            }
#endif

#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
            // Control Phy rate by FW mode
            ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), _BIT5);
#endif
        }
        else
        {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
            if(ScalerUsb3RetimerPhyGetCtsCtrl() == _ON)
            {
                ScalerUsb3RetimerUfpPhy1UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_5G);

                if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == 0x00)
                {
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE2);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
                }
                else if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE0);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
                }

#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
                // Enable Tx_ones_zero For FW Solution At CP7,8
                ScalerSetByte_EXINT3(PC9_A2_SPPHY_34, 0x22);
#endif

                // Toggle lane/cdr enable
                ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);

                DELAY_XUS_EXINT(200);

                // Toggle lane/cdr enable
                if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == 0x00)
                {
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE0);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE1);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE2);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
                }
                else if(ScalerGetBit_EXINT3(P3B_0A_RTSSM_FLAG_00, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE0);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE2);
                    ScalerGDIPhyRxLanePower_EXINT0(_D1_INPUT_PORT, _ENABLE, _GDI_PHY_LANE3);
                }
            }
#endif

#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
            if(ScalerUsb3RetimerPhyGetCtsCtrl() == _ON)
            {
                ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE0);
                ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE1);
                ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE2);
                ScalerGDIPhyRxLanePower_EXINT0(_D0_INPUT_PORT, _DISABLE, _GDI_PHY_LANE3);
            }
#endif

#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
            // Control Phy rate by FW mode
            ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), _BIT5);
#endif
        }
#else // (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
        // Control Phy rate by FW mode
        ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), _BIT5);
#endif
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
        // Enable Rx ping.lfps irq
        ScalerSetBit_EXINT3(P3B_4D_PING_LFPS_DETECT_U_03, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

        // Switch Tx Bist Local-gen compliance pattern
        ScalerSetBit_EXINT3(P3D_B0_TXBIST_PAT_SEL_G1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), _BIT5);
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
        ScalerSetBit_EXINT3(P3C_A0_TXBIST_PAT_SEL_G2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);
#endif
#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
        // Force LBPM Phy Rate to FW Mode, Before ECO#1511
        ScalerSetBit_EXINT3(P3B_49_LBPM_DETECT_U_DUMMY_01, ~(_BIT7 | _BIT6), 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)

        // Reset Compliance pattern counter
        g_ucUsb3RetimerMac0CompliancePattern = 0;
#endif

        // Clean Compliance state INT Flag
        ScalerSetBit_EXINT3(P3B_14_RTSSM_IRQ_03, ~(_BIT6 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }

#if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)
    // Compliance mode receive ping.LFPS INT
    if(ScalerGetBit_EXINT3(P3B_4D_PING_LFPS_DETECT_U_03, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        // Clear IRQ
        ScalerSetBit_EXINT3(P3B_4D_PING_LFPS_DETECT_U_03, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1), (_BIT5 | _BIT4));

        g_ucUsb3RetimerMac0CompliancePattern = g_ucUsb3RetimerMac0CompliancePattern + 1;

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _OFF)
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_5G)
        // Compliance mode pattern counter reset for RL6978 (Support Gen1 Only)
        if(g_ucUsb3RetimerMac0CompliancePattern == 9)
        {
            g_ucUsb3RetimerMac0CompliancePattern = 0;
        }
#endif
#endif
#endif
        // Compliance mode pattern counter reset
        if(g_ucUsb3RetimerMac0CompliancePattern == 17)
        {
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
                ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_5G);

                // Reset PIPE Phy rate
                ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), _BIT5);
#endif
            }
            else
            {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
                ScalerUsb3RetimerUfpPhy1UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_5G);

                // Reset PIPE Phy rate
                ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), _BIT5);
#endif
            }
#else
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
            ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_5G);

            // Reset PIPE Phy rate
            ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT5 | _BIT4), _BIT5);
#endif
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
            // Force LBPM Phy Rate FW Mode to Gen1 When CP0, Before ECO#1511
            ScalerSetBit_EXINT3(P3B_49_LBPM_DETECT_U_DUMMY_01, ~(_BIT7 | _BIT6), 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)

            ScalerSetBit_EXINT3(P3D_B0_TXBIST_PAT_SEL_G1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), _BIT5); // CP0
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
            ScalerSetBit_EXINT3(P3C_A0_TXBIST_PAT_SEL_G2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5); // CP9
#endif
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            // Remove Pre/Post Tap from Main Tap for TX CTS
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, 0x00);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, 0x00);
            }
            else
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT7, 0x00);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT6, 0x00);
            }
#else
            // [7] reg_sel_tx_post_to_main_10g = 1'b0
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, 0x00);
            // [6] reg_sel_tx_pre_to_main_10g = 1'b0
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif

            g_ucUsb3RetimerMac0CompliancePattern = 0;
        }

        // 5G Compliance pattern
        if(g_ucUsb3RetimerMac0CompliancePattern <= 8)
        {
            ScalerSetBit_EXINT3(P3D_B0_TXBIST_PAT_SEL_G1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), ((g_ucUsb3RetimerMac0CompliancePattern + 2) << 4));
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _OFF)
            if(g_ucUsb3RetimerMac0CompliancePattern == 0)
            {
                // [6] reg_mode_da_bc_sel_da_en_post_l0 = 1'b1
                ScalerSetBit_EXINT3(P1C_51_DA_MODE_2, ~_BIT6, _BIT6);
                // [6] reg_mode_da_bc_sel_da_en_post_l3 = 1'b1
                ScalerSetBit_EXINT3(P1C_53_DA_MODE_4, ~_BIT6, _BIT6);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 6)
            {
                // [6] reg_mode_da_bc_sel_da_en_post_l0 = 1'b0
                ScalerSetBit_EXINT3(P1C_51_DA_MODE_2, ~_BIT6, 0x00);
                // [6] reg_mode_da_bc_sel_da_en_post_l3 = 1'b0
                ScalerSetBit_EXINT3(P1C_53_DA_MODE_4, ~_BIT6, 0x00);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 7)
            {
                // [6] reg_mode_da_bc_sel_da_en_post_l0 = 1'b1
                ScalerSetBit_EXINT3(P1C_51_DA_MODE_2, ~_BIT6, _BIT6);
                // [6] reg_mode_da_bc_sel_da_en_post_l3 = 1'b1
                ScalerSetBit_EXINT3(P1C_53_DA_MODE_4, ~_BIT6, _BIT6);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 8)
            {
                // [6] reg_mode_da_bc_sel_da_en_post_l0 = 1'b0
                ScalerSetBit_EXINT3(P1C_51_DA_MODE_2, ~_BIT6, 0x00);
                // [6] reg_mode_da_bc_sel_da_en_post_l3 = 1'b0
                ScalerSetBit_EXINT3(P1C_53_DA_MODE_4, ~_BIT6, 0x00);
            }
#endif
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
            if(g_ucUsb3RetimerMac0CompliancePattern == 7)
            {
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
                if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
                {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
                    // Enable Dphy PIPE Manual Mode
                    ScalerSetByte_EXINT3(P96_85_SPPHY_21, 0x80);
#endif
                }
                else
                {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
                    // Enable Dphy PIPE Manual Mode
                    ScalerSetByte_EXINT3(PC9_85_SPPHY_21, 0x80);
#endif
                }
#else
                // Enable Dphy PIPE Manual Mode
                ScalerSetByte_EXINT3(P96_85_SPPHY_21, 0x80);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            }
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
        }

        // Switch to 10G & 10G Compliance pattern
        if(g_ucUsb3RetimerMac0CompliancePattern == 9)
        {
            // Set Gen1 TxBist  Back to CP0
            ScalerSetBit_EXINT3(P3D_B0_TXBIST_PAT_SEL_G1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), _BIT5); // CP0

#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
                // Disable Dphy PIPE Manual Mode
                ScalerSetByte_EXINT3(P96_85_SPPHY_21, 0x00);
#endif
            }
            else
            {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
                // Disable Dphy PIPE Manual Mode
                ScalerSetByte_EXINT3(PC9_85_SPPHY_21, 0x00);
#endif
            }
#else
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
            // Disable Dphy PIPE Manual Mode
            ScalerSetByte_EXINT3(P96_85_SPPHY_21, 0x00);
#endif
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
                ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_10G);

                // Switch Phy rate to 10G
                ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~_BIT4, _BIT4);
#endif
            }
            else
            {
#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _ON)
                ScalerUsb3RetimerUfpPhy1UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_10G);

                // Reset PIPE Phy rate to 10G
                ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~_BIT4, _BIT4);
#endif
            }
#else // (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#if(_USB3_RETIMER_UFP_PHY0_SUPPORT == _ON)
#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
            ScalerUsb3RetimerUfpPhy0UfpPhyRateChangeSetting_EXINT3(_USB_LINK_PHY_RATE_10G);

            // Switch Phy rate to 10G
            ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~_BIT4, _BIT4);
#endif
#endif
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)

#if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
            // Force LBPM Phy Rate FW Mode to Gen2 When CP9, Before ECO#1511
            ScalerSetBit_EXINT3(P3B_49_LBPM_DETECT_U_DUMMY_01, ~(_BIT7 | _BIT6), _BIT6);
#endif // End of #if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _OFF)
#endif // End of #if(_USB32_RL6952_FW_SOLUTION_SUPPORT == _ON)
        }

#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
        {
            // Add Pre/Post Tap to Main Tap for TX CTS
            if(g_ucUsb3RetimerMac0CompliancePattern == 13)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b1
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, _BIT7);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, 0x00);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 14)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, 0x00);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b1
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, _BIT6);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 15)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, 0x00);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, 0x00);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 16)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b1
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, _BIT7);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b1
                ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, _BIT6);
            }
        }
        else
        {
            // Add Pre/Post Tap to Main Tap for TX CTS
            if(g_ucUsb3RetimerMac0CompliancePattern == 13)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b1
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT7, _BIT7);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT6, 0x00);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 14)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT7, 0x00);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b1
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT6, _BIT6);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 15)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT7, 0x00);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b0
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT6, 0x00);
            }

            if(g_ucUsb3RetimerMac0CompliancePattern == 16)
            {
                // [7] reg_sel_tx_post_to_main_10g = 1'b1
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT7, _BIT7);
                // [6] reg_sel_tx_pre_to_main_10g = 1'b1
                ScalerSetBit_EXINT3(P7A_28_TX_OUT_10G_1, ~_BIT6, _BIT6);
            }
        }
#else
        // Add Pre/Post Tap to Main Tap for TX CTS
        if(g_ucUsb3RetimerMac0CompliancePattern == 13)
        {
            // [7] reg_sel_tx_post_to_main_10g = 1'b1
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, _BIT7);
            // [6] reg_sel_tx_pre_to_main_10g = 1'b0
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, 0x00);
        }

        if(g_ucUsb3RetimerMac0CompliancePattern == 14)
        {
            // [7] reg_sel_tx_post_to_main_10g = 1'b0
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, 0x00);
            // [6] reg_sel_tx_pre_to_main_10g = 1'b1
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, _BIT6);
        }

        if(g_ucUsb3RetimerMac0CompliancePattern == 15)
        {
            // [7] reg_sel_tx_post_to_main_10g = 1'b0
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, 0x00);
            // [6] reg_sel_tx_pre_to_main_10g = 1'b0
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, 0x00);
        }

        if(g_ucUsb3RetimerMac0CompliancePattern == 16)
        {
            // [7] reg_sel_tx_post_to_main_10g = 1'b1
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT7, _BIT7);
            // [6] reg_sel_tx_pre_to_main_10g = 1'b1
            ScalerSetBit_EXINT3(P1C_28_TX_OUT_10G_1, ~_BIT6, _BIT6);
        }
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#endif

#if(_HW_USB_MAX_LINK_RATE_SUPPORT == _USB_SPEED_10G)
        // 10G Compliance pattern
        if(g_ucUsb3RetimerMac0CompliancePattern >= 10)
        {
            ScalerSetBit_EXINT3(P3C_A0_TXBIST_PAT_SEL_G2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((g_ucUsb3RetimerMac0CompliancePattern - 7) << 4));
        }
#endif
    }
#endif // end of #if(_USB32_TX_COMPLIANCE_MODE_FW_MODE == _ON)

    enumPowerStatus = enumPowerStatus;
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP MAC PortConfig State Config in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0UfpPortConfigSetting_EXINT3(void)
{
    //=====================
    // Gen2 / Gen1 Mode Setting
    //=====================
    if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == _BIT7)
    {
        // Set EQ Training Time to Gen2 7ms
        ScalerSetByte_EXINT3(P3B_A7_TIMER_CNT_LIST_7, 0x46);
    }
    else
    {
        // Set EQ Training Time to Gen1 4ms
        ScalerSetByte_EXINT3(P3B_A7_TIMER_CNT_LIST_7, 0x28);
    }

    //=====================
    // x2 / x1 Lane Mode Setting
    //=====================
    if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT6) == _BIT6)
    {
#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
        // Change AsyFIFO WL for x2 Lane Mode
        ScalerUsb3RetimerMac0UfpAsyFifox2Proc_EXINT3();
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

        // Change Polling.Active_Timeout to 24ms
        ScalerSetByte_EXINT3(P3B_A9_TIMER_CNT_LIST_9, 0xF0);

        // Change Polling.Configuration_Timeout to 24ms
        ScalerSetByte_EXINT3(P3B_AA_TIMER_CNT_LIST_10, 0xF0);

        // Change PM_ENTRY_TIMER to 18us (To avoid Timer Missmatch with Hub) 16us + 2us
        ScalerSetByte_EXINT3(P3B_AD_TIMER_CNT_LIST_13, 0x12);
    }
    // x1 Lane Mode Reset
    else
    {
#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
        // Reset AsyFIFO WL for x1 Lane Mode
        ScalerUsb3RetimerMac0UfpAsyFifox1Proc_EXINT3();
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

        // Reset Polling.Active_Timeout to 12ms
        ScalerSetByte_EXINT3(P3B_A9_TIMER_CNT_LIST_9, 0x78);

        // Reset Polling.Configuration_Timeout to 12ms
        ScalerSetByte_EXINT3(P3B_AA_TIMER_CNT_LIST_10, 0x78);

        // Reset PM_ENTRY_TIMER to 10us (To avoid Timer Missmatch with Hub) 8us + 2us
        ScalerSetByte_EXINT3(P3B_AD_TIMER_CNT_LIST_13, 0x0A);
    }

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        // Enable Tx SSC When BLR Support == _ON & Retimer Capability is not Gen1x1
        if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, (_BIT7 | _BIT6)) != 0x00)
        {
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
            if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
            {
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)
                // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
                ScalerSetBit_EXINT3(P96_40_SSC_TX_00, ~_BIT1, 0x00);
#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)
                // UFP0 - [1] reg_ssc_en_tx = 1'b1 => SSC ON
                ScalerSetBit_EXINT3(P96_40_SSC_TX_00, ~_BIT1, _BIT1);
#endif
            }
            else
            {
#if(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_32_BIT)
                // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
                ScalerSetBit_EXINT3(PC9_40_SSC_TX_00, ~_BIT1, 0x00);
#elif(_HW_USB3_REPEATER_UFP_AD_INTERFACE_BIT_WIDTH == _UFP_16_BIT)
                // UFP1 - [1] reg_ssc_en_tx = 1'b1 => SSC ON
                ScalerSetBit_EXINT3(PC9_40_SSC_TX_00, ~_BIT1, _BIT1);
#endif
            }
#else
            // UFP0 - [1] reg_ssc_en_tx = 1'b0 => SSC OFF
            ScalerSetBit_EXINT3(P96_40_SSC_TX_00, ~_BIT1, 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
        }
    }
#endif
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP MAC PortConfig State Config in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0DfpPortConfigSetting_EXINT3(void)
{
    //=====================
    // Gen2 Mode Setting
    //=====================
    if(ScalerGetBit_EXINT3(P3E_39_LBPM_DETECT_D_03, _BIT7) == _BIT7)
    {
        // Set EQ Training Time to Gen2 7ms
        ScalerSetByte_EXINT3(P3E_A7_TIMER_CNT_LIST_7, 0x46);
    }
    else
    {
        // Set EQ Training Time to Gen1 4ms
        ScalerSetByte_EXINT3(P3E_A7_TIMER_CNT_LIST_7, 0x28);
    }

    //=====================
    // x2 Lane Mode Setting
    //=====================
    if(ScalerGetBit_EXINT3(P3E_39_LBPM_DETECT_D_03, _BIT6) == _BIT6)
    {
#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
        // Change AsyFIFO WL for x2 Lane Mode
        ScalerUsb3RetimerMac0DfpAsyFifox2Proc_EXINT3();
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

        // Change Polling.Active_Timeout to 24ms
        ScalerSetByte_EXINT3(P3E_A9_TIMER_CNT_LIST_9, 0xF0);

        // Change Polling.Configuration_Timeout to 24ms
        ScalerSetByte_EXINT3(P3E_AA_TIMER_CNT_LIST_10, 0xF0);

        // Change PM_ENTRY_TIMER to 16us (To avoid Timer Missmatch with Hub) 16us + 2us
        ScalerSetByte_EXINT3(P3E_AD_TIMER_CNT_LIST_13, 0x12);
    }
    // x1 Lane Mode Reset
    else
    {
#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
        // Reset AsyFIFO WL for x1 Lane Mode
        ScalerUsb3RetimerMac0DfpAsyFifox1Proc_EXINT3();
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)

        // Reset Polling.Active_Timeout to 12ms
        ScalerSetByte_EXINT3(P3E_A9_TIMER_CNT_LIST_9, 0x78);

        // Reset Polling.Configuration_Timeout to 12ms
        ScalerSetByte_EXINT3(P3E_AA_TIMER_CNT_LIST_10, 0x78);

        // Reset PM_ENTRY_TIMER to 10us (To avoid Timer Missmatch with Hub) 8us + 2us
        ScalerSetByte_EXINT3(P3E_AD_TIMER_CNT_LIST_13, 0x0A);
    }

#if(_USB32_GEN1_BLR_PATH_SUPPORT == _ON)
    if(ScalerUsb3RepeaterMacBlrPathSupport() == _ON)
    {
        // Enable Tx SSC When BLR Support == _ON & Retimer Capability is not Gen1x1
        if(ScalerGetBit_EXINT3(P3E_39_LBPM_DETECT_D_03, (_BIT7 | _BIT6)) != 0x00)
        {
            // [1] reg_ssc_en_tx = 1'b1 => SSC ON
            ScalerSetBit_EXINT3(PC8_10_SSC_TX_00, ~_BIT1, _BIT1);
        }
    }
#endif
}

#if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP MAC AsyFIFO x2 Lane Proc in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0UfpAsyFifox2Proc_EXINT3(void)
{
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(_RX0);
#endif

    //================================================
    // AsyFIFO Setting By Dx Port & Gen1/Gen2 & CC_Orientation
    //================================================
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // Check Dx Mux Setting
    if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
    {
        if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == 0x00)
        {
            if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Gen1, fifo_rx1_delay_g1_u
                // Set Gen1 AsyFIFO_1_Rx1 WL to 6
                ScalerSetBit_EXINT3(P3D_02_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }
            else
            {
                // Gen1, fifo_rx0_delay_g1_u
                // Set Gen1 AsyFIFO_0_Rx1 WL to 6
                ScalerSetBit_EXINT3(P3D_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }
        }
        else
        {
            if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Gen2, fifo_rx1_delay_g2_u
                // Set Gen2 AsyFIFO_1_Rx1 WL to 6
                ScalerSetBit_EXINT3(P3C_02_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }
            else
            {
                // Gen2, fifo_rx0_delay_g2_u
                // Set Gen2 AsyFIFO_0_Rx1 WL to 6
                ScalerSetBit_EXINT3(P3C_01_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }
        }
    }
    else
    {
        if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == 0x00)
        {
            if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Gen1, fifo_rx1_delay_g1_u
                // Set Gen1 AsyFIFO_1_Rx1 WL to 6
                ScalerSetBit_EXINT3(P3D_F2_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }
            else
            {
                // Gen1, fifo_rx0_delay_g1_u
                // Set Gen1 AsyFIFO_0_Rx1 WL to 6
                ScalerSetBit_EXINT3(P3D_F1_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }
        }
        else
        {
            if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
            {
                // Gen2, fifo_rx1_delay_g2_u
                // Set Gen2 AsyFIFO_1_Rx1 WL to 6
                ScalerSetBit_EXINT3(P3C_D2_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }
            else
            {
                // Gen2, fifo_rx0_delay_g2_u
                // Set Gen2 AsyFIFO_0_Rx1 WL to 6
                ScalerSetBit_EXINT3(P3C_D1_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            }
        }
    }
#else
    if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == 0x00)
    {
        if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Gen1, fifo_rx1_delay_g1_u
            // Set Gen1 AsyFIFO_1_Rx1 WL to 6
            ScalerSetBit_EXINT3(P3D_02_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        }
        else
        {
            // Gen1, fifo_rx0_delay_g1_u
            // Set Gen1 AsyFIFO_0_Rx1 WL to 6
            ScalerSetBit_EXINT3(P3D_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        }
    }
    else
    {
        if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Gen2, fifo_rx1_delay_g2_u
            // Set Gen2 AsyFIFO_1_Rx1 WL to 6
            ScalerSetBit_EXINT3(P3C_02_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        }
        else
        {
            // Gen2, fifo_rx0_delay_g2_u
            // Set Gen2 AsyFIFO_0_Rx1 WL to 6
            ScalerSetBit_EXINT3(P3C_01_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
        }
    }
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP MAC AsyFIFO x2 Lane Proc in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0DfpAsyFifox2Proc_EXINT3(void)
{
    //================================================
    // AsyFIFO Setting By Gen1/Gen2 & DFP_CC_Orientation_Define
    //================================================
    if(ScalerGetBit_EXINT3(P3E_39_LBPM_DETECT_D_03, _BIT7) == 0x00)
    {
#if(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_UNFLIP)
        // Gen1, fifo_rx1_delay_g1_d
        // Set Gen1 AsyFIFO_1_Rx1 WL to 6
        ScalerSetBit_EXINT3(P82_02_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#elif(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_FLIP)
        // Gen1, fifo_rx0_delay_g1_d
        // Set Gen1 AsyFIFO_0_Rx1 WL to 6
        ScalerSetBit_EXINT3(P82_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif
    }
    else
    {
#if(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_UNFLIP)
        // Gen2, fifo_rx1_delay_g2_d
        // Set Gen2 AsyFIFO_1_Rx1 WL to 6
        ScalerSetBit_EXINT3(P81_02_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#elif(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_FLIP)
        // Gen2, fifo_rx0_delay_g2_d
        // Set Gen2 AsyFIFO_0_Rx1 WL to 6
        ScalerSetBit_EXINT3(P81_01_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#endif
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP MAC AsyFIFO x1 Lane Proc in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0UfpAsyFifox1Proc_EXINT3(void)
{
    //================================================
    // AsyFIFO Setting By Dx Port & Gen1/Gen2
    //================================================
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // Check Dx Mux Setting
    if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
    {
        if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == 0x00)
        {
            // Gen1, fifo_rx0_delay_g1_u
            // Set Gen1 AsyFIFO_0_Rx1 WL to 1
            ScalerSetBit_EXINT3(P3D_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // Gen1, fifo_rx1_delay_g1_u
            // Set Gen1 AsyFIFO_1_Rx1 WL to 1
            ScalerSetBit_EXINT3(P3D_02_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        }
        else
        {
            // Gen2, fifo_rx0_delay_g2_u
            // Set Gen2 AsyFIFO_0_Rx1 WL to 1
            ScalerSetBit_EXINT3(P3C_01_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // Gen2, fifo_rx1_delay_g2_u
            // Set Gen2 AsyFIFO_1_Rx1 WL to 1
            ScalerSetBit_EXINT3(P3C_02_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        }
    }
    else
    {
        if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == 0x00)
        {
            // Gen1, fifo_rx1_delay_g1_u
            // Set Gen1 AsyFIFO_1_Rx1 WL to 1
            ScalerSetBit_EXINT3(P3D_F2_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // Gen1, fifo_rx0_delay_g1_u
            // Set Gen1 AsyFIFO_0_Rx1 WL to 1
            ScalerSetBit_EXINT3(P3D_F1_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        }
        else
        {
            // Gen2, fifo_rx0_delay_g2_u
            // Set Gen2 AsyFIFO_0_Rx1 WL to 1
            ScalerSetBit_EXINT3(P3C_D1_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            // Gen2, fifo_rx1_delay_g2_u
            // Set Gen2 AsyFIFO_1_Rx1 WL to 1
            ScalerSetBit_EXINT3(P3C_D2_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        }
    }
#else
    if(ScalerGetBit_EXINT3(P3B_39_LBPM_DETECT_U_03, _BIT7) == 0x00)
    {
        // Gen1, fifo_rx0_delay_g1_u
        // Set Gen1 AsyFIFO_0_Rx1 WL to 1
        ScalerSetBit_EXINT3(P3D_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        // Gen1, fifo_rx1_delay_g1_u
        // Set Gen1 AsyFIFO_1_Rx1 WL to 1
        ScalerSetBit_EXINT3(P3D_02_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // Gen2, fifo_rx0_delay_g2_u
        // Set Gen2 AsyFIFO_0_Rx1 WL to 1
        ScalerSetBit_EXINT3(P3C_01_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        // Gen2, fifo_rx1_delay_g2_u
        // Set Gen2 AsyFIFO_1_Rx1 WL to 1
        ScalerSetBit_EXINT3(P3C_02_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP MAC AsyFIFO x1 Lane Proc in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0DfpAsyFifox1Proc_EXINT3(void)
{
    //================================================
    // AsyFIFO Setting By Gen1/Ge2
    //================================================
    if(ScalerGetBit_EXINT3(P3E_39_LBPM_DETECT_D_03, _BIT7) == 0x00)
    {
#if(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_UNFLIP)
        // Gen1, fifo_rx1_delay_g1_d
        // Set Gen1 AsyFIFO_1_Rx1 WL to 1
        ScalerSetBit_EXINT3(P82_02_GEN1_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
#elif(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_FLIP)
        // Gen1, fifo_rx0_delay_g1_d
        // Set Gen1 AsyFIFO_0_Rx1 WL to 1
        ScalerSetBit_EXINT3(P82_01_GEN1_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
#endif
    }
    else
    {
#if(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_UNFLIP)
        // Gen2, fifo_rx1_delay_g2_d
        // Set Gen2 AsyFIFO_1_Rx1 WL to 1
        ScalerSetBit_EXINT3(P81_02_GEN2_ASYNCHRONOUS_FIFO_CTRL_02, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
#elif(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_FLIP)
        // Gen2, fifo_rx0_delay_g2_d
        // Set Gen2 AsyFIFO_0_Rx1 WL to 1
        ScalerSetBit_EXINT3(P81_01_GEN2_ASYNCHRONOUS_FIFO_CTRL_01, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
#endif
    }
}
#endif // End of #if(_HW_USB_MAX_LINK_LANE_SUPPORT == _USB_LANE_X2)
//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer UFP MAC Exit ComplianceMode by Polling/LBPM in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0UfpExitCPbyPollingSolution_EXINT3(void)
{
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerUsb3RepeaterMacMacx2DxMapping_EXINT3(_RX0);
#endif

#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
    // Check Dx Mux Setting
    if(ScalerGetBit_EXINT3(P3B_07_RTSSM_GLOBAL_07, _BIT7) == 0x00)
    {
        if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Set UFP0 Tx1 Power FW to P3
            ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));
            // Set UFP0 Tx1 Power Back to HW Mode
            ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~_BIT4, 0x00);
        }
        else
        {
            // Set UFP0 Tx0 Power FW to P3
            ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
            // Set UFP0 Tx0 Power Back to HW Mode
            ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~_BIT7, 0x00);
        }

        // Set UFP0 PIPE Lane count to 1lane
        ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT3 | _BIT2), _BIT3);
        ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT3 | _BIT2), 0x00);
    }
    else
    {
        if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Set UFP1 Tx1 Power FW to P3
            ScalerSetBit_EXINT3(P81_D5_PIPE_CONTROL_U_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));
            // Set UFP1 Tx1 Power Back to HW Mode
            ScalerSetBit_EXINT3(P81_D5_PIPE_CONTROL_U_05, ~_BIT4, 0x00);
        }
        else
        {
            // Set UFP1 Tx0 Power FW to P3
            ScalerSetBit_EXINT3(P81_D5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
            // Set UFP1 Tx0 Power Back to HW Mode
            ScalerSetBit_EXINT3(P81_D5_PIPE_CONTROL_U_05, ~_BIT7, 0x00);
        }

        // Set UFP1 PIPE Lane count to 1lane
        ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~(_BIT3 | _BIT2), _BIT3);
        ScalerSetBit_EXINT3(P81_D6_PIPE_CONTROL_U_06, ~(_BIT3 | _BIT2), 0x00);
    }
#else
    if(GET_TYPE_C_ORIENTATION_EXINT3(enumTypeCPcbPort) == _TYPE_C_ORIENTATION_UNFLIP)
    {
        // Set UFP0 Tx1 Power FW to P3
        ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));
        // Set UFP0 Tx1 Power Back to HW Mode
        ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~_BIT4, 0x00);
    }
    else
    {
        // Set UFP0 Tx0 Power FW to P3
        ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        // Set UFP0 Tx0 Power Back to HW Mode
        ScalerSetBit_EXINT3(P3B_C5_PIPE_CONTROL_U_05, ~_BIT7, 0x00);
    }

    // Set UFP0 PIPE Lane count to 1lane
    ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit_EXINT3(P3B_C6_PIPE_CONTROL_U_06, ~(_BIT3 | _BIT2), 0x00);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
}

//----------------------------------------------------------------------------------------------------
// Description  : USB3 Retimer DFP MAC Exit ComplianceMode by Polling/LBPM in INT
// Input Value  : None
// Output Value : None
//----------------------------------------------------------------------------------------------------
void ScalerUsb3RetimerMac0DfpExitCPbyPollingSolution_EXINT3(void)
{
#if(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_UNFLIP)
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // Set DFP Tx1 Power FW to P3
    ScalerSetBit_EXINT3(P3E_C5_PIPE_CONTROL_D_05, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));
    // Set DFP Tx1 Power Back to HW Mode
    ScalerSetBit_EXINT3(P3E_C5_PIPE_CONTROL_D_05, ~_BIT4, 0x00);
#endif
#elif(_RETIMER_DFP_ORIENTATION == _TYPE_C_DFP_ORIENTATION_FLIP)
    // Set DFP Tx0 Power FW to P3
    ScalerSetBit_EXINT3(P3E_C5_PIPE_CONTROL_D_05, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    // Set DFP Tx0 Power Back to HW Mode
    ScalerSetBit_EXINT3(P3E_C5_PIPE_CONTROL_D_05, ~_BIT7, 0x00);
#endif
#if(_HW_USB3_REPEATER_MAC_GEN1_PARALLEL_PATH_SUPPORT == _ON)
    // Set DFP PIPE Lane count to 1lane
    ScalerSetBit_EXINT3(P3E_C6_PIPE_CONTROL_D_06, ~(_BIT3 | _BIT2), _BIT3);
    ScalerSetBit_EXINT3(P3E_C6_PIPE_CONTROL_D_06, ~(_BIT3 | _BIT2), 0x00);
#endif
}
#endif // End of #if(_USB3_RETIMER_MAC0_SUPPORT == _ON)
