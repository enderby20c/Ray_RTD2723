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
// ID Code      : RL6952_Series_DpPhyRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
// Description  : Rebuilding DP PHY
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1RebuildPhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);

    ScalerDpMacDphyRxSetCommaDetect(enumInputPort, _ON);

    ScalerDpMacDphyRxLaneSwapSelect(enumInputPort, _DP_PHY_RX1_D1_LANE0 << 6);

    ScalerDpMacDphyRxLaneCountSet(enumInputPort, (ucDpcdLane & 0x1F));

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    if(ScalerTypeCRxCheckTypeCSupportOn(enumInputPort) == _TRUE)
    {
        ScalerDpPhyRx1SetAltModeLaneMapping(ScalerTypeCRxGetPinAssignment(enumInputPort), ScalerTypeCRxGetOrientation(enumInputPort));
    }
#endif

    ScalerDpPhyRx1SignalDetection(_DISABLE);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3/2] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            ScalerDpPhyRx1RebuildUnFlip2LanePhy(enumDpLinkRate, ucDpcdLane);

            // [3/2] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), 0x00);
        }
        else
        {
            // [1/0] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            ScalerDpPhyRx1RebuildFlip2LanePhy(enumDpLinkRate, ucDpcdLane);

            // [1/0] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        }
    }
    else
#endif
    {
        // [3:0] reg_offpn_sync = 1 --> Enable Offpn
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ScalerDpPhyRx1Rebuild4LanePhy(enumDpLinkRate, ucDpcdLane);

        // [3:0] reg_offpn_sync = 0 --> Disable Offpn
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    // DP MAC FIFO Reset
    ScalerDpMacDphyRxChannelFifoReset(enumInputPort);
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SetDFEInitial(EnumDpLinkRate enumDpLinkRate)
{
    if((enumDpLinkRate == _DP_LINK_HBR2) && (ScalerDpPhyRx1GetPhyCtsFlag() == _TRUE) && ((g_ucDpPhyRx1CtsCtrl & 0x0F) == 0x02))
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte(PB2_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte(PB2_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte(PB2_A2_L0_LIMIT_INIT, 0xF8);
    ScalerSetByte(PB2_B2_L1_LIMIT_INIT, 0xF8);
    ScalerSetByte(PB2_C2_L2_LIMIT_INIT, 0xF8);
    ScalerSetByte(PB2_D2_L3_LIMIT_INIT, 0xF8);

    ScalerSetByte(PB2_A3_L0_INIT_1, 0xD0);
    ScalerSetByte(PB2_B3_L1_INIT_1, 0xD0);
    ScalerSetByte(PB2_C3_L2_INIT_1, 0xD0);
    ScalerSetByte(PB2_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte(PB2_A4_L0_INIT_2, 0x14);
    ScalerSetByte(PB2_B4_L1_INIT_2, 0x14);
    ScalerSetByte(PB2_C4_L2_INIT_2, 0x14);
    ScalerSetByte(PB2_D4_L3_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte(PB2_A5_L0_INIT_3, 0x03);
    ScalerSetByte(PB2_B5_L1_INIT_3, 0x03);
    ScalerSetByte(PB2_C5_L2_INIT_3, 0x03);
    ScalerSetByte(PB2_D5_L3_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte(PB2_A6_L0_INIT_4, 0x00);
    ScalerSetByte(PB2_B6_L1_INIT_4, 0x00);
    ScalerSetByte(PB2_C6_L2_INIT_4, 0x00);
    ScalerSetByte(PB2_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 28
    ScalerSetByte(PB2_A9_L0_INIT_7, 0x1C);
    ScalerSetByte(PB2_B9_L1_INIT_7, 0x1C);
    ScalerSetByte(PB2_C9_L2_INIT_7, 0x1C);
    ScalerSetByte(PB2_D9_L3_INIT_7, 0x1C);

    // Load Intial DFE Code
    ScalerSetByte(PB2_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0xFF);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0xFF);

    ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x00);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(PB2_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB2_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(EnumDpLinkRate enumDpLinkRate)
{
    if((enumDpLinkRate == _DP_LINK_HBR2) && (ScalerDpPhyRx1GetPhyCtsFlag() == _TRUE) && ((g_ucDpPhyRx1CtsCtrl & 0x0F) == 0x02))
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte(PB2_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte(PB2_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0x00);

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte(PB2_C2_L2_LIMIT_INIT, 0xF8);
    ScalerSetByte(PB2_D2_L3_LIMIT_INIT, 0xF8);

    ScalerSetByte(PB2_C3_L2_INIT_1, 0xD0);
    ScalerSetByte(PB2_D3_L3_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte(PB2_C4_L2_INIT_2, 0x14);
    ScalerSetByte(PB2_D4_L3_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte(PB2_C5_L2_INIT_3, 0x03);
    ScalerSetByte(PB2_D5_L3_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte(PB2_C6_L2_INIT_4, 0x00);
    ScalerSetByte(PB2_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 24
    ScalerSetByte(PB2_C9_L2_INIT_7, 0x18);
    ScalerSetByte(PB2_D9_L3_INIT_7, 0x18);

    // Load Intial DFE Code
    ScalerSetByte(PB2_CA_L2_INIT_8, 0xFF);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0xFF);

    ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(PB2_EF_RESET_1, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(PB2_EF_RESET_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SetDFEInitialFlip2Lane(EnumDpLinkRate enumDpLinkRate)
{
    if((enumDpLinkRate == _DP_LINK_HBR2) && (ScalerDpPhyRx1GetPhyCtsFlag() == _TRUE) && ((g_ucDpPhyRx1CtsCtrl & 0x0F) == 0x02))
    {
        // Tap Divider = 34 for TPS3
        ScalerSetByte(PB2_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for All Other Pattern
        ScalerSetByte(PB2_ED_LOOP_DIV_2, 0xCA);
    }


    ////////////////////
    // DFE Initialize //
    ////////////////////

    // Disable All Adaptation Loop
    ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0x00);

    // LE Max = 31, LE Initial = 24, Servo Initial = 16
    ScalerSetByte(PB2_A2_L0_LIMIT_INIT, 0xF8);
    ScalerSetByte(PB2_B2_L1_LIMIT_INIT, 0xF8);

    ScalerSetByte(PB2_A3_L0_INIT_1, 0xD0);
    ScalerSetByte(PB2_B3_L1_INIT_1, 0xD0);

    // Tap0 Initial Value = 20
    ScalerSetByte(PB2_A4_L0_INIT_2, 0x14);
    ScalerSetByte(PB2_B4_L1_INIT_2, 0x14);

    // Tap1 Initial Value = 3
    ScalerSetByte(PB2_A5_L0_INIT_3, 0x03);
    ScalerSetByte(PB2_B5_L1_INIT_3, 0x03);

    // Tap2 Initial Value = 0
    ScalerSetByte(PB2_A6_L0_INIT_4, 0x00);
    ScalerSetByte(PB2_B6_L1_INIT_4, 0x00);

    // Vth Initial Value = 24
    ScalerSetByte(PB2_A9_L0_INIT_7, 0x18);
    ScalerSetByte(PB2_B9_L1_INIT_7, 0x18);

    // Load Intial DFE Code
    ScalerSetByte(PB2_AA_L0_INIT_8, 0xFF);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0xFF);

    ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit(PB2_EF_RESET_1, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB2_EF_RESET_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}
#endif

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpPhyRx1DFECheck(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);

    if(ScalerDpAuxRxGetLinkRate(enumInputPort) >= _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)))
    {
        case _DP_FOUR_LANE:

            // Read Lane3 DFE
            ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx1("7. Lane3 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane2 DFE
            ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx1("7. Lane2 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx1("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx1("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_DP_PHY_RX1_D1_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x3F);

            // Read Back Tap0
            ScalerSetBit(PB2_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

            if((pData[1] == 0x1F) && (pData[0] == 0x0C))
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

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
// Description  : DP PHY CTS Auto Mode Rebuild PHY + Error Count IRQ Enable After Link Training
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsAutoMode(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);

    while(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x02, 0x70, _BIT7) == _BIT7)
    {
        ScalerDebug();

        DebugMessageRx1("DP Rx PHY CTS Auto Mode", 0x00);
    }
}

//--------------------------------------------------
// Description  : DP PHY CTS Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCts(void)
{
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX1_DP14_MAC, _POWER_CUT_OFF, _POWER_RESET_DISABLE);
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_RX1_DP20_MAC, _POWER_CUT_OFF, _POWER_RESET_DISABLE);

    while(ScalerDpPhyRx1GetPhyCtsFlag() == _TRUE)
    {
#if(_DP_PHY_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
        {
            ScalerDpPhyRx1PhyCtsManualMode_128b132b();
        }
        else
#endif
        {
            ScalerDpPhyRx1PhyCtsManualMode_8b10b();
        }
    }
}
//--------------------------------------------------
// Description  : DP PHY CTS Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsManualMode_8b10b(void)
{
    // g_ucDpPhyRx1CtsCtrl(APHY 0xA8[5]) = 1 --> PHY CTS Enable
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x01 --> Clock Recovery
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x02 --> EQ CRC
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x03 --> Error Counter Reset
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x04 --> Error Counter Read
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x05 --> PHY CTS Register Clear
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[3]) = 0 --> DP 1.4 Mode
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[3]) = 1 --> DP 2.0 Mode
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[5:4]) = 00 --> lane0
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[5:4]) = 01 --> lane1
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[5:4]) = 10 --> lane2
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[5:4]) = 11 --> lane3
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[7:6]) = 00 --> RBR/UHBR10
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[7:6]) = 01 --> HBR/UHBR10
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[7:6]) = 10 --> HBR2/UHBR13_5
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[7:6]) = 11 --> HBR3/UHBR20

    WORD usErrorCount = 0;
    BYTE ucErrorCountLaneSelect = 0;
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);

    usErrorCount = usErrorCount;

#if(_DP_PHY_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_8B10B);
    }
#endif

    while((ScalerDpPhyRx1GetPhyCtsFlag() == _TRUE) && (ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE))
    {
        ScalerDebug();

        if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
        {
            return;
        }

        DebugMessageRx1("7. PHY CTS Loop1", ScalerGetByte(P1F_B9_REG_DUMMY_1));

        switch(ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30)
        {
            default:
            case 0x00: // Source Lane0

                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_PHY_RX1_D1_LANE0 << 4);

                break;

            case 0x10: // Source Lane1

                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_PHY_RX1_D1_LANE1 << 4);

                break;

            case 0x20: // Source Lane2

                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_PHY_RX1_D1_LANE2 << 4);

                break;

            case 0x30: // Source Lane3

                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_PHY_RX1_D1_LANE3 << 4);

                break;
        }

        g_ucDpPhyRx1CtsCtrl = ScalerGetByte(P1F_B9_REG_DUMMY_1);

        DebugMessageRx1("7. PHY CTS Loop2", g_ucDpPhyRx1CtsCtrl);

        switch(g_ucDpPhyRx1CtsCtrl & 0x07)
        {
            case 0x01: // CDR Lock Check

                ScalerSetByte(P1F_B9_REG_DUMMY_1, (g_ucDpPhyRx1CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0))); // Clear DP PHY CTS Phase Info

                ScalerDpPhyRx1PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                if(ScalerDpMacDphyRxPhyCtsTp1Check(enumInputPort) == _TRUE)
                {
                    ScalerSetBit(P1F_BA_REG_DUMMY_2, ~_BIT0, _BIT0);
                }
                else
                {
                    ScalerSetBit(P1F_BA_REG_DUMMY_2, ~_BIT0, 0x00);
                }

                break;

            case 0x02: // Symbol Lock Check

                ScalerSetByte(P1F_B9_REG_DUMMY_1, (g_ucDpPhyRx1CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerDpPhyRx1PhyCtsTp2SetPhy();

                if(ScalerDpMacDphyRxPhyCtsTp2Check(enumInputPort) == _TRUE)
                {
                    ScalerSetBit(P1F_BA_REG_DUMMY_2, ~_BIT1, _BIT1);
                }
                else
                {
                    ScalerSetBit(P1F_BA_REG_DUMMY_2, ~_BIT1, 0x00);
                }

                break;

            case 0x03:

                ScalerSetByte(P1F_B9_REG_DUMMY_1, (g_ucDpPhyRx1CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerDpPhyRx1PhyCtsTp2SetPhy();

                ScalerTimerDelayXms(10);

                if((g_ucDpPhyRx1CtsCtrl & 0xC0) >= 0x80)
                {
                    // TPS Pattern Follow MAC Lane
                    if(ScalerDpMacDphyRxGetLaneMuxMapping(enumInputPort, _DP_LANE_0) == ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4))
                    {
                        // MAC Lane0 Test
                        ucErrorCountLaneSelect = (0x00 << 4);
                    }
                    else if(ScalerDpMacDphyRxGetLaneMuxMapping(enumInputPort, _DP_LANE_1) == ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4))
                    {
                        // MAC Lane1 Test
                        ucErrorCountLaneSelect = (0x01 << 4);
                    }
                    else if(ScalerDpMacDphyRxGetLaneMuxMapping(enumInputPort, _DP_LANE_2) == ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4))
                    {
                        // MAC Lane2 Test
                        ucErrorCountLaneSelect = (0x02 << 4);
                    }
                    else if(ScalerDpMacDphyRxGetLaneMuxMapping(enumInputPort, _DP_LANE_3) == ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4))
                    {
                        // MAC Lane3 Test
                        ucErrorCountLaneSelect = (0x03 << 4);
                    }
                }
                else
                {
                    // PRBS Pattern Follow PHY Lane
                    ucErrorCountLaneSelect = (g_ucDpPhyRx1CtsCtrl & (_BIT5 | _BIT4));
                }

                usErrorCount = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, (ucErrorCountLaneSelect >> 4));

                if((g_ucDpPhyRx1CtsCtrl & 0xC0) >= 0x80)
                {
                    // Enable Scramble
                    ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);

                    // HBR2/3 Compliance Eye Pattern
                    ScalerDpMacDphyRxDecodeErrorCountReset(enumInputPort, _DP_MAC_DECODE_METHOD_8B10B_DISPARITY);
                }
                else
                {
                    // PRBS7 Pattern for RBR/HBR
                    ScalerDpMacDphyRxDecodeErrorCountReset(enumInputPort, _DP_MAC_DECODE_METHOD_PRBS7);
                }

                // Reset Error Count = 0
                ScalerSetByte(P1F_8E_DUMMY, 0x00);

                break;

            case 0x04:

                ScalerSetByte(P1F_B9_REG_DUMMY_1, (g_ucDpPhyRx1CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerTimerDelayXms(10);

                if(((ScalerGetByte(PB0_09_BIST_PATTERN1) & 0x7F) | ScalerGetByte(PB0_0A_BIST_PATTERN2)) != 0x00)
                {
                    ScalerSetByte(P1F_8E_DUMMY, ScalerGetByte(PB0_0C_BIST_PATTERN4));
                }
                else
                {
                    ScalerSetByte(P1F_8E_DUMMY, 0xFF);
                }

                break;

            case 0x05:

                // Clear DP PHY CTS Control Register
                ScalerSetByte(P1F_B9_REG_DUMMY_1, 0x00);

                // Clear DP PHY CTS Result
                ScalerSetByte(P1F_BA_REG_DUMMY_2, 0x00);
                ScalerSetByte(P1F_8E_DUMMY, 0x00);

                // Disable PRBS7 Error Detection
                ScalerSetBit(PB0_08_BIST_PATTERN_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                ScalerSetBit(PB2_A8_L0_INIT_6, ~_BIT5, 0x00);

                break;

            default:

                // Clear DP PHY CTS Control Register
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

                break;
        }

        if((g_ucDpPhyRx1CtsCtrl & 0x07) != 0x05)
        {
            if(((ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 4) == _DP_PHY_RX1_D1_LANE0) // Source Lane0
            {
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_SCALER_LANE0 << 4);
            }
            else if(((ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 4) == _DP_PHY_RX1_D1_LANE1) // Source Lane1
            {
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_SCALER_LANE1 << 4);
            }
            else if(((ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 4) == _DP_PHY_RX1_D1_LANE2) // Source Lane2
            {
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_SCALER_LANE2 << 4);
            }
            else if(((ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 4) == _DP_PHY_RX1_D1_LANE3) // Source Lane3
            {
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_SCALER_LANE3 << 4);
            }

            DebugMessageRx1("7. PHY CTS Loop (Swap Back)", ScalerGetByte(P1F_B9_REG_DUMMY_1));
        }
        else
        {
            g_ucDpPhyRx1CtsCtrl = 0x00;
        }
    }
}

#if(_DP_PHY_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP PHY CTS Process for DP2.x Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsManualMode_128b132b(void)
{
    // g_ucDpPhyRx1CtsCtrl(APHY 0xA8[5]) = 1 --> PHY CTS Enable
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x01 --> Clock Recovery
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x02 --> EQ CRC
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x03 --> Error Counter Reset
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x04 --> Error Counter Read
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[2:0]) = 0x05 --> PHY CTS Register Clear
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[3]) = 0 --> DP 1.4 Mode
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[3]) = 1 --> DP 2.0 Mode
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[5:4]) = 00 --> lane0
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[5:4]) = 01 --> lane1
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[5:4]) = 10 --> lane2
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[5:4]) = 11 --> lane3
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[7:6]) = 00 --> RBR/UHBR10
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[7:6]) = 01 --> HBR/UHBR10
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[7:6]) = 10 --> HBR2/UHBR13_5
    // g_ucDpPhyRx1CtsCtrl(20MAC 0xB9[7:6]) = 11 --> HBR3/UHBR20

    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);

    if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        ScalerDpAuxRxSetCodingType(enumInputPort, _CODING_TYPE_128B132B);
    }

    while((ScalerDpPhyRx1GetPhyCtsFlag() == _TRUE) && (ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE))
    {
        ScalerDebug();

        if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() != _TRUE)   // switch to 8b10b
        {
            return;
        }

        DebugMessageRx1("7. PHY CTS Loop1", ScalerGetByte(P1F_B9_REG_DUMMY_1));

        // DP 20 MAC Select Lane
        ScalerSetBit(P1F_B3_ERROR_COUNT_CTRL_DP20, ~(_BIT5 | _BIT4), (ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30));
        ScalerSetBit(P1F_A8_BIST_PATTERN_SEL_DP20, ~(_BIT4 | _BIT3 | _BIT2), (ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 1);

        switch(ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30)
        {
            default:
            case 0x00: // Source Lane0

                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_PHY_RX1_D1_LANE0 << 4);

                break;

            case 0x10: // Source Lane1

                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_PHY_RX1_D1_LANE1 << 4);

                break;

            case 0x20: // Source Lane2

                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_PHY_RX1_D1_LANE2 << 4);

                break;

            case 0x30: // Source Lane3

                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_PHY_RX1_D1_LANE3 << 4);

                break;
        }

        g_ucDpPhyRx1CtsCtrl = ScalerGetByte(P1F_B9_REG_DUMMY_1);

        DebugMessageRx1("7. PHY CTS Loop2", g_ucDpPhyRx1CtsCtrl);

        switch(g_ucDpPhyRx1CtsCtrl & 0x07)
        {
            case 0x01: // CDR Lock Check

                ScalerSetByte(P1F_B9_REG_DUMMY_1, (g_ucDpPhyRx1CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0))); // Clear DP PHY CTS Phase Info

                ScalerDpPhyRx1PhyCtsTp1SetPhy(_DP_NF_REF_XTAL);

                if(ScalerDpMacDphyRxPhyCtsTp1Check(enumInputPort) == _TRUE)
                {
                    ScalerSetBit(P1F_BA_REG_DUMMY_2, ~_BIT0, _BIT0);
                }
                else
                {
                    ScalerSetBit(P1F_BA_REG_DUMMY_2, ~_BIT0, 0x00);
                }

                break;

            case 0x02: // Symbol Lock Check

                ScalerSetByte(P1F_B9_REG_DUMMY_1, (g_ucDpPhyRx1CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerDpPhyRx1PhyCtsTp2SetPhy();

                if(ScalerDpMacDphyRxPhyCtsTp2Check(enumInputPort) == _TRUE)
                {
                    ScalerSetBit(P1F_BA_REG_DUMMY_2, ~_BIT1, _BIT1);
                }
                else
                {
                    ScalerSetBit(P1F_BA_REG_DUMMY_2, ~_BIT1, 0x00);
                }

                break;

            case 0x03:

                ScalerSetByte(P1F_B9_REG_DUMMY_1, (g_ucDpPhyRx1CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerDpPhyRx1PhyCtsTp2SetPhy();

                ScalerTimerDelayXms(10);

                // PRBS Pattern Follow PHY Lane
                PDATA_WORD(0) = ScalerDpMacDphyRxGetDecodeErrorCount(enumInputPort, ((g_ucDpPhyRx1CtsCtrl & (_BIT5 | _BIT4)) >> 4));

                // PRBS31 Pattern for UHBR
                ScalerDpMacDphyRxDecodeErrorCountReset(enumInputPort, _DP_MAC_DECODE_METHOD_PRBS31);

                // Reset Error Count = 0
                ScalerSetByte(P1F_8E_DUMMY, 0x00);

                break;

            case 0x04:

                ScalerSetByte(P1F_B9_REG_DUMMY_1, (g_ucDpPhyRx1CtsCtrl & ~(_BIT2 | _BIT1 | _BIT0)));

                ScalerTimerDelayXms(10);

                if((ScalerGetByte(P1F_A9_BIST_PATTERN_DP_20_1) | ScalerGetByte(P1F_AA_BIST_PATTERN_DP_20_2)) != 0x00)
                {
                    ScalerSetByte(P1F_8E_DUMMY, ScalerGetByte(P1F_AC_BIST_PATTERN_DP_20_4));
                }
                else
                {
                    ScalerSetByte(P1F_8E_DUMMY, 0xFF);
                }

                break;

            case 0x05:

                // Clear DP PHY CTS Control Register
                ScalerSetByte(P1F_B9_REG_DUMMY_1, 0x00);

                // Clear DP PHY CTS Result
                ScalerSetByte(P1F_BA_REG_DUMMY_2, 0x00);
                ScalerSetByte(P1F_8E_DUMMY, 0x00);

                // Disable PRBS7 Error Detection
                ScalerSetBit(P1F_A7_SCRAMBLE_CTRL_DP20, ~_BIT4, 0x00);

                ScalerSetBit(PB2_A8_L0_INIT_6, ~_BIT5, 0x00);

                break;

            default:

                // Clear DP PHY CTS Control Register
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT7 | _BIT6 | _BIT2 | _BIT1 | _BIT0), 0x00);

                break;
        }

        if((g_ucDpPhyRx1CtsCtrl & 0x07) != 0x05)
        {
            if(((ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 4) == _DP_PHY_RX1_D1_LANE0) // Source Lane0
            {
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_SCALER_LANE0 << 4);
            }
            else if(((ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 4) == _DP_PHY_RX1_D1_LANE1) // Source Lane1
            {
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_SCALER_LANE1 << 4);
            }
            else if(((ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 4) == _DP_PHY_RX1_D1_LANE2) // Source Lane2
            {
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_SCALER_LANE2 << 4);
            }
            else if(((ScalerGetByte(P1F_B9_REG_DUMMY_1) & 0x30) >> 4) == _DP_PHY_RX1_D1_LANE3) // Source Lane3
            {
                ScalerSetBit(P1F_B9_REG_DUMMY_1, ~(_BIT5 | _BIT4), _DP_SCALER_LANE3 << 4);
            }

            DebugMessageRx1("7. PHY CTS Loop (Swap Back)", ScalerGetByte(P1F_B9_REG_DUMMY_1));
        }
        else
        {
            g_ucDpPhyRx1CtsCtrl = 0x00;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Set DP Phy CTS Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpPhyRx1GetPhyCtsFlag(void)
{
    return (ScalerGetBit(PB2_A8_L0_INIT_6, _BIT5) == _BIT5);
}

//--------------------------------------------------
// Description  : Get DP Phy CTS Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpPhyRx1GetPhyCtsForDP14Flag(void)
{
    return ((ScalerGetByte(P1F_B9_REG_DUMMY_1) & _BIT3) != _BIT3);
}

//--------------------------------------------------
// Description  : Get DP Phy CTS Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpPhyRx1GetPhyCtsForDP20Flag(void)
{
    return ((ScalerGetByte(P1F_B9_REG_DUMMY_1) & _BIT3) == _BIT3);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp1SetPhy(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);

    ScalerDpMacDphyRxLaneSwapSelect(enumInputPort, (g_ucDpPhyRx1CtsCtrl & 0x30) << 2);

    // [4:3] DP MAC Select Four Lane
    ScalerDpMacDphyRxLaneCountSet(enumInputPort, _DP_FOUR_LANE);

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    if(ScalerTypeCRxCheckTypeCSupportOn(enumInputPort) == _TRUE)
    {
        ScalerDpPhyRx1SetAltModeLaneMapping(ScalerTypeCRxGetPinAssignment(enumInputPort), ScalerTypeCRxGetOrientation(enumInputPort));
    }
#endif

    ScalerDpPhyRx1SignalDetection(_DISABLE);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3/2] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            ScalerDpPhyRx1PhyCtsTp1SetPhyUnFlip2Lane(enumDpNFCodeRef);

            // [3/2] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), 0x00);
        }
        else
        {
            // [1/0] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            ScalerDpPhyRx1PhyCtsTp1SetPhyFlip2Lane(enumDpNFCodeRef);

            // [1/0] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        }
    }
    else
#endif
    {
        // [3:0] reg_offpn_sync = 1 --> Enable Offpn
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ScalerDpPhyRx1PhyCtsTp1SetPhy4Lane(enumDpNFCodeRef);

        // [3:0] reg_offpn_sync = 0 --> Disable Offpn
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    // DP MAC FIFO Reset
    ScalerDpMacDphyRxChannelFifoReset(enumInputPort);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp2SetPhy(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);

    ScalerDpMacDphyRxSetCommaDetect(enumInputPort, _ON);

    // [2] Disable Enhancement Control Mode
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);

    ScalerDpPhyRx1SignalDetection(_DISABLE);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3/2] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            ScalerDpPhyRx1PhyCtsTp2SetPhyUnFlip2Lane();

            // [3/2] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2), 0x00);
        }
        else
        {
            // [1/0] reg_offpn_sync = 1 --> Enable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            ScalerDpPhyRx1PhyCtsTp2SetPhyFlip2Lane();

            // [1/0] reg_offpn_sync = 0 --> Disable Offpn
            ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        }
    }
    else
#endif
    {
        // [3:0] reg_offpn_sync = 1 --> Enable Offpn
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ScalerDpPhyRx1PhyCtsTp2SetPhy4Lane();

        // [3:0] reg_offpn_sync = 0 --> Disable Offpn
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    // DP MAC FIFO Reset
    ScalerDpMacDphyRxChannelFifoReset(enumInputPort);
}

//--------------------------------------------------
// Description : Check DP Eye Monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1EyeMonitor(void)
{
    /*
    // _ERROR_PRONE_CODE
    // (0x0E[7] = 1 --> Eye Monitor Enable
    // (0xC170[2:0]) = 0x01 --> Search Phase
    // (0xC170[2:0]) = 0x02 --> Vth Min
    // (0xC170[2:0]) = 0x03 --> Vth Max
    // (0xC170[2:0]) = 0x04 --> Start Phase
    // (0xC170[2:0]) = 0x05 --> End Phase
    // (0xC170[2:0]) = 0x06 --> Report Error Count for Single Point
    // (0xC170[5:4]) = 00 --> lane0
    // (0xC170[5:4]) = 01 --> lane1
    // (0xC170[5:4]) = 10 --> lane2
    // (0xC170[5:4]) = 11 --> lane3
    // (0xC170[6]) = 1 --> Enable Eye Monitor All Once
    // (0xC170[7]) = 1 --> Enable Allocation Once

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

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _DISABLE);

    DebugMessageRx1("Enable Eye Monitor", ScalerGetByte(PB2_0E_RX_EYE_00));

    while(ScalerDpPhyRx1GetEyeMonitorEnableFlag() == _TRUE)
    {
        // Enable Eye Monitor
        ScalerSetBit(PB2_0E_RX_EYE_00, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

        // Enable RP for EYE
        ScalerSetBit(PB2_0F_RX_EYE_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Vth Ctrl Manual Mode
        ScalerSetBit(PB2_EB_LIMIT_6, ~_BIT5, _BIT5);

        // PI Phase Manual Mode
        ScalerSetBit(PB2_F5_ERRCNT1, ~_BIT7, _BIT7);

        ScalerDebug();

        // Enable Allocation Once
        if(ScalerGetBit(PC1_70_DFP_RESERVED_DPHY_00, _BIT7) == _BIT7)
        {
            ///////////
            // Reset //
            ///////////

            ScalerSetBit(PC1_70_DFP_RESERVED_DPHY_00, ~_BIT7, 0x00);

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
                usErrorCount = ScalerDpPhyRx1EyeMonitorErrorCount(1, ucPhase);

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
                        if(ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucPhase) < ucPassCriteriaCount)
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
                            if(ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucPhase) < ucPassCriteriaCount)
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
                            if(ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucPhase) < ucPassCriteriaCount)
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
                            if(ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucPhase) < ucPassCriteriaCount)
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
                    if(ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucBestPhase) < ucPassCriteriaCount)
                    {
                        // Vth Max = The First Vth Level w/o Error
                        ucVthMax = ucVth;
                    }
                }
            }

            for(ucVth = 65; ucVth < 128; ucVth++) // #(65~127 = 63)
            {
                if(ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucBestPhase) < ucPassCriteriaCount)
                {
                    // Vth Min = The Last Vth Level w/o Error
                    ucVthMin = ucVth;
                }
            }

            DebugMessageRx1("Allocation Finish", ScalerGetByte(PC1_70_DFP_RESERVED_DPHY_00));
        }

        // Read Out
        switch(ScalerGetBit(PC1_70_DFP_RESERVED_DPHY_00, (_BIT2 | _BIT1 | _BIT0)))
        {
            case 0x01: // Search Phase

                ScalerSetBit(PC1_70_DFP_RESERVED_DPHY_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                ScalerSetByte(PC1_71_DFP_RESERVED_DPHY_01, ucBestPhase);

                break;

            case 0x02: // Vth Min

                ScalerSetBit(PC1_70_DFP_RESERVED_DPHY_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                ScalerSetByte(PC1_71_DFP_RESERVED_DPHY_01, ucVthMin);

                break;

            case 0x03: // Vth Max

                ScalerSetBit(PC1_70_DFP_RESERVED_DPHY_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                ScalerSetByte(PC1_71_DFP_RESERVED_DPHY_01, ucVthMax);

                break;

            case 0x04: // Start Phase

                ScalerSetBit(PC1_70_DFP_RESERVED_DPHY_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                ScalerSetByte(PC1_71_DFP_RESERVED_DPHY_01, ucStartPhase);

                break;

            case 0x05: // End Phase

                ScalerSetBit(PC1_70_DFP_RESERVED_DPHY_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                ScalerSetByte(PC1_71_DFP_RESERVED_DPHY_01, ucEndPhase);

                break;

            case 0x06: // Report Error Count for Single Point

                ScalerSetBit(PC1_70_DFP_RESERVED_DPHY_00, ~(_BIT2 | _BIT1 | _BIT0), 0x00); // Clear Step Info

                ucPhase = ScalerGetByte(PC1_72_DFP_RESERVED_DPHY_02) & 0x3F;

                ucVth = ScalerGetByte(PB2_A9_L0_INIT_7) & 0x7F;

                usErrorCount = ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucPhase);

                ScalerSetByte(PC1_71_DFP_RESERVED_DPHY_01, usErrorCount);

                break;

            default:

                break;
        }

#if(_DEBUG_MESSAGE_RX1 == _ON)
        // Enable Eye Monitor for Whole Plot
        if(ScalerGetBit(PC1_70_DFP_RESERVED_DPHY_00, _BIT6) == _BIT6)
        {
            ScalerSetBit(PC1_70_DFP_RESERVED_DPHY_00, ~_BIT6, 0x00);

            DebugMessageRx1("Eye Monitor All", 0x00);

            // For DebugMsg Not Missing First X Error Count
            ScalerTimerDelayXms(100);

            // All Phase
            for(ucPhase = 0; ucPhase < 64; ucPhase++)
            {
                // Positive Vth Up-Down (63 -> 1)
                for(ucVth = 63; ucVth > 0; ucVth--) // #(1~63 = 64)
                {
                    usErrorCount = ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucPhase);

                    DebugMessageRx1("====Error====", usErrorCount);
                }

                // Negative Vth Up-Down (0 -> -63)
                for(ucVth = 64; ucVth < 128; ucVth++) // #(64~127 = 63)
                {
                    usErrorCount = ScalerDpPhyRx1EyeMonitorErrorCount(ucVth, ucPhase);

                    DebugMessageRx1("====Error====", usErrorCount);
                }
            }
        }
#endif
    }

    // Disable PR
    ScalerSetBit(PB2_0F_RX_EYE_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable Eye Monitor
    ScalerSetBit(PB2_0E_RX_EYE_00, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Vth Ctrl Auto Mode
    ScalerSetBit(PB2_EB_LIMIT_6, ~_BIT5, 0x00);

    // PI Phase Auto Mode
    ScalerSetBit(PB2_F5_ERRCNT1, ~_BIT7, 0x00);
    */
}

//--------------------------------------------------
// Description : Check DP Eye Monitor
// Input Value  : Vth Selection, Phase Selection
// Output Value : # of Error Count
//--------------------------------------------------
WORD ScalerDpPhyRx1EyeMonitorErrorCount(BYTE ucVth, BYTE ucPhase)
{
    ucVth = ucVth;
    ucPhase = ucPhase;
    WORD usErrorCount = 0;

    /*
    // Disable Eye Scan
    ScalerSetBit(PB2_F4_ERRCNT0, ~_BIT1, 0x00);

    // Set PI Phase
    ScalerSetBit(PB2_FC_PR_CTRL0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), g_pucDpRxEN[ucPhase / 16]);
    ScalerSetByte(PB2_FE_EM_CTRL0, g_pusDpRxST[ucPhase] >> 8);
    ScalerSetByte(PB2_FD_PR_CTRL1, g_pusDpRxST[ucPhase]);

    // Set Vth
    ScalerSetByte(PB2_A9_L0_INIT_7, ucVth);
    ScalerSetByte(PB2_B9_L1_INIT_7, ucVth);
    ScalerSetByte(PB2_C9_L2_INIT_7, ucVth);
    ScalerSetByte(PB2_D9_L3_INIT_7, ucVth);

    // Enable Eye Scan
    ScalerSetBit(PB2_F4_ERRCNT0, ~_BIT1, _BIT1);

    switch(ScalerGetBit(PC1_70_DFP_RESERVED_DPHY_00, (_BIT5 | _BIT4)))
    {
        default:
        case (0x00):

            ScalerSetByte(PB2_FB_DEBUG, 0x04);

            break;

        case (_BIT4):

            ScalerSetByte(PB2_FB_DEBUG, 0x05);

            break;

        case (_BIT5):

            ScalerSetByte(PB2_FB_DEBUG, 0x06);

            break;

        case (_BIT5 | _BIT4):

            ScalerSetByte(PB2_FB_DEBUG, 0x07);
    }

    pData[0] = 0;
    while(ScalerGetBit(PB2_F4_ERRCNT0, _BIT7) == 0)        // wait valid bit assert
    {
        DELAY_5US();
        if(pData[0]++ > 100)
        {
            break;
        }
    }
    // DELAY_XUS(500);  // 500us For Error

    switch(ScalerGetBit(PC1_70_DFP_RESERVED_DPHY_00, (_BIT5 | _BIT4)))
    {
        default:
        case (0x00):

            ScalerSetByte(PB2_FB_DEBUG, 0x04);

            usErrorCount = (WORD)ScalerGetByte(PB2_FF_EM_CTRL1) << 4; // [11:4]

            ScalerSetByte(PB2_FB_DEBUG, 0x08);

            usErrorCount = usErrorCount + (ScalerGetByte(PB2_FF_EM_CTRL1) >> 4);  // [3:0]

            break;

        case (_BIT4):

            ScalerSetByte(PB2_FB_DEBUG, 0x05);

            usErrorCount = (WORD)ScalerGetByte(PB2_FF_EM_CTRL1) << 4;

            ScalerSetByte(PB2_FB_DEBUG, 0x08);

            usErrorCount = usErrorCount + (ScalerGetByte(PB2_FF_EM_CTRL1) & 0x0F);

            break;

        case (_BIT5):

            ScalerSetByte(PB2_FB_DEBUG, 0x06);

            usErrorCount = (WORD)ScalerGetByte(PB2_FF_EM_CTRL1) << 4;

            ScalerSetByte(PB2_FB_DEBUG, 0x09);

            usErrorCount = usErrorCount + (ScalerGetByte(PB2_FF_EM_CTRL1) >> 4);

            break;

        case (_BIT5 | _BIT4):

            ScalerSetByte(PB2_FB_DEBUG, 0x07);

            usErrorCount = (WORD)ScalerGetByte(PB2_FF_EM_CTRL1) << 4;

            ScalerSetByte(PB2_FB_DEBUG, 0x09);

            usErrorCount = usErrorCount + (ScalerGetByte(PB2_FF_EM_CTRL1) & 0x0F);
    }

    */
    return usErrorCount;
}

//--------------------------------------------------
// Description : Get Eye Monitor ENable Flag
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpPhyRx1GetEyeMonitorEnableFlag(void)
{
    return _FALSE;
    // return (ScalerGetBit(PB2_0E_RX_EYE_00, _BIT7) == _BIT7);
}

//--------------------------------------------------
// Description  : DP Phy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyInitial(void)
{
    //////////////
    // Rx Power //
    //////////////

#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
#if((_DUAL_DP_SUPPORT == _OFF) && (_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF))
    ScalerGDIPhyRxDisableOtherPort(ScalerDpPhyRxRxDxMapping(_RX1));
#endif
#endif

    // [3:0] reg_en_weak_pull_lv = 4'b0000
    ScalerSetBit(PB2_0C_RX_TOP_12, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [7:4] reg_en_weak_pull_g = 4'b1111
    ScalerSetBit(PB2_06_RX_TOP_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


    /////////////////
    // DFE Initial //
    /////////////////

    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetBit(PB2_E0_MODE_TIMER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1));

    // Tap0 Loop Gain 1/512, Tap1 Loop Gain 1/128
    ScalerSetBit(PB2_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit(PB2_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit(PB2_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit(PB2_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit(PB2_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Disable LE Gray Code
    ScalerSetByte(PB2_EE_GRAY_DEC_1, 0x21);

    // Tap0 Max is 31
    ScalerSetBit(PB2_E0_MODE_TIMER, ~_BIT6, 0x00);
    ScalerSetBit(PB2_E6_LIMIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Tap1 Min is -15
    ScalerSetBit(PB2_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Tap2 Max is 6, Min is -6
    ScalerSetBit(PB2_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit(PB2_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB2_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 3, Min is -3
    ScalerSetBit(PB2_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetBit(PB2_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 3, Min is -3
    ScalerSetBit(PB2_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB2_EB_LIMIT_6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(PB2_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Vth Threshold = 18
    ScalerSetBit(PB2_F4_ERRCNT0, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit(PB2_E6_LIMIT_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // Tap0 Threshold = 10
    ScalerSetBit(PB2_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte(PB2_EC_LOOP_DIV_1, 0xA3);

    // [1] tap1_trans = 1'b1 --> Tap1 is Effective on Transition bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every Bits
    ScalerSetBit(PB2_E3_GAIN_2, ~(_BIT1 | _BIT0), _BIT1);

    // [5] servo_notrans = 1'b0 --> Servo is Effective on Every Bits
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT5, 0x00);

    // [1:0] trans_rlength = 3'b000 --> Tap0 Run Length = 2
    ScalerSetBit(PB2_E5_GAIN_4, ~_BIT0, 0x00);
    ScalerSetBit(PB2_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);

    // [1:0] tap0_adjust = 2'b01
    ScalerSetBit(PB2_F6_ERRCNT2, ~(_BIT1 | _BIT0), _BIT0);

    // Set Vth Max = 63, Min = 12
    ScalerSetBit(PB2_F4_ERRCNT0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(PB2_F6_ERRCNT2, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetByte(PB2_F9_LIMIT_10, 0xFC);


    /////////////////
    // CDR Setting //
    /////////////////

    // [7:3] reg_cp_time = 0.64us x ( 0x0E + 1) = 9.6us
    ScalerSetBit(PB1_3D_FLD_L0_59, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(PB1_7D_FLD_L1_59, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(PB1_BD_FLD_L2_59, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));
    ScalerSetBit(PB1_FD_FLD_L3_59, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4));

    // [4:0] reg_adp_time = 0.64us x ( 0x1E + 1) = 19.84us
    ScalerSetBit(PB1_16_FLD_L0_22, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1));
    ScalerSetBit(PB1_56_FLD_L1_22, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1));
    ScalerSetBit(PB1_96_FLD_L2_22, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1));
    ScalerSetBit(PB1_D6_FLD_L3_22, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1));

    // [5:3] reg_calib_time = 0.64us x ( 0x07 + 1) = 5.12us
    ScalerSetBit(PB1_13_FLD_L0_19, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(PB1_53_FLD_L1_19, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(PB1_93_FLD_L2_19, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));
    ScalerSetBit(PB1_D3_FLD_L3_19, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // [5] reg_timer_5 = 1.28us x ( 0x01 + 1) = 2.56us
    // [4:0] reg_timer_4 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(PB1_20_FLD_L0_30, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PB1_60_FLD_L1_30, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PB1_A0_FLD_L2_30, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PB1_E0_FLD_L3_30, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [4:0] reg_timer_6 = 1.28us x ( 0x1F + 1) = 40.96us
    ScalerSetBit(PB1_21_FLD_L0_31, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PB1_61_FLD_L1_31, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PB1_A1_FLD_L2_31, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PB1_E1_FLD_L3_31, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    SET_DP_PHY_RX1_ICP_KP_RBR(_BIT6);
    SET_DP_PHY_RX1_ICP_KP_HBR(_BIT6);
    SET_DP_PHY_RX1_ICP_KP_HBR2(_BIT5);
    SET_DP_PHY_RX1_ICP_KP_HBR3(_BIT5);
    SET_DP_PHY_RX1_ICP_KP_UHBR10(_BIT6 | _BIT4);
    SET_DP_PHY_RX1_ICP_KP_UHBR13P5(_BIT6);
    SET_DP_PHY_RX1_ICP_KP_UHBR20(_BIT6);

    SET_DP_PHY_RX1_ICP_RBR(_BIT0);
    SET_DP_PHY_RX1_ICP_HBR(_BIT0);
    SET_DP_PHY_RX1_ICP_HBR2(_BIT1);
    SET_DP_PHY_RX1_ICP_HBR3(_BIT2);
    SET_DP_PHY_RX1_ICP_UHBR10(_BIT1 | _BIT0);
    SET_DP_PHY_RX1_ICP_UHBR13P5(_BIT2 | _BIT1);
    SET_DP_PHY_RX1_ICP_UHBR20(_BIT2 | _BIT1);

    SET_DP_PHY_RX1_KVCO_RBR(_BIT6 | _BIT4);
    SET_DP_PHY_RX1_KVCO_HBR(_BIT6 | _BIT4);
    SET_DP_PHY_RX1_KVCO_HBR2(_BIT6 | _BIT4);
    SET_DP_PHY_RX1_KVCO_HBR3(_BIT6 | _BIT4);
    SET_DP_PHY_RX1_KVCO_UHBR10(_BIT6 | _BIT3);
    SET_DP_PHY_RX1_KVCO_UHBR13P5(_BIT6 | _BIT4 | _BIT3);
    SET_DP_PHY_RX1_KVCO_UHBR20(_BIT6 | _BIT4 | _BIT3);


    //////////////////
    // MISC Setting //
    //////////////////

    // [7:4] reg_sel_div20_10_sigdtc = 4'b1111 --> Signal Detector = Data Rate / 10
    ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [3:0] reg_en_div32_clk = 4'b1111
    ScalerSetBit(PB2_03_RX_TOP_03, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_timer_en = 1 for CDR_RDY
    ScalerSetBit(P7A_9D_DATA_TIMER_7, ~_BIT0, _BIT0);

    // reg_offcal_range_dp = 2'b10
    ScalerSetBit(P7A_0D_MODE_OFFSET_K_DP_00, ~(_BIT1 | _BIT0), _BIT1);

    // [3:2] reg_offk_delay = 8*Clock Period for Accuracy
    // [1:0] reg_timeout_sel = 2'b11 -> Timeout After Offset K 127 Times
    ScalerSetBit(P7A_A8_ADJR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // DP ALPM Clock Gating
    ScalerSetByte(PC9_66_ALPM_22, 0x0F);
    ScalerSetByte(PC9_67_ALPM_23, 0xF0);
    ScalerSetByte(PC9_68_ALPM_24, 0x0F);
    ScalerSetByte(PC9_69_ALPM_25, 0x00);

    // DP Global Parameter MeasureCount Initial
    ScalerDpRxMeasureCountInitial();


    //////////////////
    // ALPM Initial //
    //////////////////

    // [7:6] reg_en_oobs = 2'b11 => Enable OOBS
    ScalerSetBit(PB2_1A_OOBS_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [7:4] reg_cmu_config_alpm = 4'b1111 => Enable ACDR CMU mode When ALPM
    ScalerSetBit(PB2_41_RX_ALPM_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [7:4] reg_rx_pch_en_alpm = 4'b1111
    // [3:0] reg_rx_nch_en_alpm = 4'b1111
    ScalerSetByte(PB2_42_RX_APLM_02, 0xFF);

    // [9:0] reg_lfps_lperiod_dp = 0x05
    ScalerSetBit(PC9_D2_LFPS_EQEN_12, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetByte(PC9_CE_LFPS_EQEN_8, 0x05);

    // [9:0] reg_lfps_hperiod_dp = 0x1C
    ScalerSetBit(PC9_D2_LFPS_EQEN_12, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetByte(PC9_CF_LFPS_EQEN_9, 0x1C);

    // [7:0] reg_lfps_count = 0x06 => LFPS debouce times, neet 1T LFPS for Detect
    ScalerSetByte(PC9_D0_LFPS_EQEN_10, 0x06);
}

//--------------------------------------------------
// Description  : Lane Swap
// Input Value  : TypeC Pin Assigment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SetAltModeLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation)
{
    ///////////////////////
    // AUX Pin-Share/PHY //
    ///////////////////////

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
    // Aux Pin-Share and Aux PN Pull High/Low Setting
    ScalerPinshareRx1TypeCPinAssert(enumPinAssignment, enumTypeCOrientation);

    // Aux APHY Swap Setting
    ScalerDpAuxRxTypeCPinAssert(ScalerDpPhyRxRxDxMapping(_RX1), enumPinAssignment, enumTypeCOrientation);

#if((_D1_USB_HUB_TYPE != _USB_NONE) && (_D1_USB_U3_HUB_TRACE_TYPE == _USB_U3_TRACE_GO_THROUGH_SCALER))
    switch(enumPinAssignment)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:
        case _TYPE_C_PIN_ASSIGNMENT_E:

            ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);

            // [7:4] reg_cmu_config_pllmode = 4'b1111
            ScalerSetBit(PB2_45_RX_PLL_MODE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Disable JFM
            ScalerSetBit(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), 0x00);

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
            {
                ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE0);
                ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE1);
                ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
                ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);

                // [7:4] reg_cmu_config_pllmode = 4'b1100
                ScalerSetBit(PB2_45_RX_PLL_MODE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));
            }
            else
            {
                ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
                ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
                ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE2);
                ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE3);

                // [7:4] reg_cmu_config_pllmode = 4'b0011
                ScalerSetBit(PB2_45_RX_PLL_MODE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
            }

            break;

        default:
        case _TYPE_C_PIN_ASSIGNMENT_NONE:

            ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE3);

            // [7:4] reg_cmu_config_pllmode = 4'b0000
            ScalerSetBit(PB2_45_RX_PLL_MODE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

            break;
    }
#else
    ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
    ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
    ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
    ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);

    // [7:4] reg_cmu_config_pllmode = 4'b1111
    ScalerSetBit(PB2_45_RX_PLL_MODE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Disable JFM
    ScalerSetBit(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), 0x00);
#endif

#else
    enumPinAssignment = enumPinAssignment;
    enumTypeCOrientation = enumTypeCOrientation;

    ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
    ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
    ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
    ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);

    // [7:4] reg_cmu_config_pllmode = 4'b1111
    ScalerSetBit(PB2_45_RX_PLL_MODE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Disable JFM
    ScalerSetBit(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Rebuilding DP PHY
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1Rebuild4LanePhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];
    BYTE pucTap0[4];
    WORD usTargetClock = 0;


    ////////////////////
    // 4 Lane Initial //
    ////////////////////

    DebugMessageRx1("RebuildPhy", (WORD)(enumDpLinkRate << 8) + ucDpcdLane);

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [3:0] Enable Foreground Offset Calibration
    ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_en_vco_lpf = 4'b1111 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_timer_en = 1 for CDR_RDY
    // [3:0] reg_acdr_en = 1
    ScalerSetByte(P7A_96_DATA_TIMER_0, 0xFF);

    // reg_en_fld_clk = 4'b1111 --> Enable FLD Clock
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit(PB1_00_FLD_L0_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_40_FLD_L1_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_80_FLD_L2_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_C0_FLD_L3_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_6E_FLD_L1_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_EE_FLD_L3_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit(PB1_2F_FLD_L0_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_6F_FLD_L1_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_AF_FLD_L2_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_EF_FLD_L3_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
#endif
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)) || (_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON))
        ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE0);
        ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE1);
        ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE2);
        ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE3);
#endif
        switch(ucDpcdLane & 0x1F)
        {
            case _DP_ONE_LANE:

                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());

                break;

            case _DP_TWO_LANE:

                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());
                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE1_MAPPING());

                break;

            default:
            case _DP_FOUR_LANE:

                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());
                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE1_MAPPING());
                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE2_MAPPING());
                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE3_MAPPING());

                break;
        }
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_clkout_manual = 1'b0
    // [3:0] reg_bypass_clk_rdy = 1'b0
    ScalerSetByte(P7A_97_DATA_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte(P7A_99_DATA_TIMER_3, 0x0F);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitial(enumDpLinkRate);

    if(enumDpLinkRate >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSetting4Lane(enumDpLinkRate, _DP_NF_REF_XTAL);

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_25_FLD_L0_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_70_FLD_L1_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[2]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            DebugMessageRx1("1st Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _OFF)
    ScalerDpPhyRx1KOobs();
#endif


    //////////////
    // FLD Band //
    //////////////

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            DebugMessageRx1("1st FLD Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte(PB1_14_FLD_L0_20, ScalerGetByte(PB1_32_FLD_L0_48));
    ScalerSetByte(PB1_54_FLD_L1_20, ScalerGetByte(PB1_72_FLD_L1_48));
    ScalerSetByte(PB1_94_FLD_L2_20, ScalerGetByte(PB1_B2_FLD_L2_48));
    ScalerSetByte(PB1_D4_FLD_L3_20, ScalerGetByte(PB1_F2_FLD_L3_48));

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    DELAY_10US();

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            DebugMessageRx1("2nd FLD Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(100);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(100);

    // Disable DFE Adaptation
    ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0x00);

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte(PB2_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_A4_L0_INIT_2, 0x1F);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_B4_L1_INIT_2, 0x1F);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_C4_L2_INIT_2, 0x1F);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_D4_L3_INIT_2, 0x1F);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte(P7A_AB_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AB_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte(P7A_AD_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AD_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte(PB2_AA_L0_INIT_8, 0x20);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x20);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x20);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x20);

    ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x00);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x00);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            DebugMessageRx1("2nd Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte(PB1_14_FLD_L0_20, ScalerGetByte(PB1_32_FLD_L0_48));
    ScalerSetByte(PB1_54_FLD_L1_20, ScalerGetByte(PB1_72_FLD_L1_48));
    ScalerSetByte(PB1_94_FLD_L2_20, ScalerGetByte(PB1_B2_FLD_L2_48));
    ScalerSetByte(PB1_D4_FLD_L3_20, ScalerGetByte(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[1]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[0]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    usTargetClock = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, _DP_PHY_RX1_D1_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_125_CYCLE) << 3;

    if(usTargetClock != 0)
    {
        g_pusDpPhyRx1ClockTarget[0] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[1] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[2] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[3] = usTargetClock;
    }
}

#if(_USB3_RETIMER_UFP_PHY1_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Dp Rx1 K OOBS
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerDpPhyRx1KOobs(void)
{
    BYTE ucOobsSenVal = 0;
    BYTE ucOobsOffsetL0 = 0;
    BYTE ucOobsOffsetL2 = 0;
    BYTE ucTemp = 0;

    // [7:6] reg_en_oobs = 2'b11
    // [5:4] reg_oobs_lfps_sel = 2'b00
    ScalerSetBit(PB2_1A_OOBS_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6));

    // [3:2] reg_freq_sel = 2'b00 => oobs frequency = 250M
    ScalerSetBit(PB2_1A_OOBS_00, ~(_BIT3 | _BIT2), 0x00);

    // [4:0] reg_oobs_vth_lx = 5'b01000
    ScalerSetBit(PB2_1D_OOBS_03, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit(PB2_1E_OOBS_04, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // [7:6] reg_oobs_offset_timeout [9:8] = 2'b11
    // [7:0] reg_oobs_offset_timeout [7:0] = 0xFF
    ScalerSetBit(PC9_D5_RX_K_OOBS_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte(PC9_D6_RX_K_OOBS_02, 0xFF);

    for(ucOobsSenVal = 0; ucOobsSenVal <= (_BIT1 | _BIT0); ucOobsSenVal++)
    {
        DebugMessageRx1("Dp_Rx1_ucOobsSenVal_L0", ucOobsSenVal);

        // reg_sen_val_range_l01
        ScalerSetBit(PB2_19_LDO_03, ~(_BIT3 | _BIT2), (ucOobsSenVal << 2));

        // [1:0] reg_oobs_offset_ini_l0 [9:8] = 2'b10
        // [7:0] reg_oobs_offset_ini_l0 [7:0] = 0x00
        ScalerSetBit(PC9_D9_RX_K_OOBS_05, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetByte(PC9_D8_RX_K_OOBS_04, 0x00);

        // [1] reg_oobs_offset_ok_l0 = 1'b0 -> Disable Manual Mode Calibration ok
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT1, 0x00);

        // [0] reg_oobs_offset_manual_l0 = 1'b0 -> Calibration Auto Mode
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT0, 0x00);

        // [4] reg_rstb_oobs_offset = 1'b0 >> 1'b1 -> reset
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT4, 0x00);
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT4, _BIT4);

        // [0] reg_oobs_offset_en_l0 = 1'b1 -> Set Calibration Mode Enable
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT0, _BIT0);

        // Delay Time us [0,500] Waiting for Calibration Done
        for(ucTemp = 0; ucTemp <= 50; ucTemp++)
        {
            DELAY_10US();

            if(ScalerGetBit(PC9_DC_RX_K_OOBS_08, _BIT0) == _BIT0)
            {
                break;
            }
        }

        ucOobsOffsetL0 = (((ScalerGetByte(PC9_D9_RX_K_OOBS_05) & 0xC0) >> 1) | ((ScalerGetByte(PC9_DD_RX_K_OOBS_09) & 0xF1) >> 3));

        DebugMessageRx1("Dp_Rx1_ucOobsOffsetL0", ucOobsOffsetL0);

        // [0] reg_oobs_offset_en_l0 = 1'b0 -> Disable calibration
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT0, 0x00);

        // [1] reg_oobs_offset_ok_l0 = 1'b1 -> Enable Manual Mode Calibration ok
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT1, _BIT1);

        // [0] reg_oobs_offset_manual_l0 = 1'b1 -> Calibration Manual Mode
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT0, _BIT0);

        if((ucOobsOffsetL0 != 0x7F) || (ucOobsSenVal == (_BIT1 | _BIT0)))
        {
            // Reload L0 Calibration Result
            ScalerSetBit(PC9_D9_RX_K_OOBS_05, ~(_BIT1 | _BIT0), (ScalerGetByte(PC9_D9_RX_K_OOBS_05) >> 6));
            ScalerSetByte(PC9_D8_RX_K_OOBS_04, ScalerGetByte(PC9_DD_RX_K_OOBS_09));

            break;
        }
    }

    for(ucOobsSenVal = 0; ucOobsSenVal <= (_BIT1 | _BIT0); ucOobsSenVal++)
    {
        DebugMessageRx1("Dp_Rx1_ucOobsSenVal_L2", ucOobsSenVal);

        // reg_sen_val_range_l23
        ScalerSetBit(PB2_19_LDO_03, ~(_BIT1 | _BIT0), ucOobsSenVal);

        // [1:0] reg_oobs_offset_ini_l1 [9:8] = 2'b10
        // [7:0] reg_oobs_offset_ini_l1 [7:0] = 0x00
        ScalerSetBit(PC9_DB_RX_K_OOBS_07, ~(_BIT1 | _BIT0), _BIT1);
        ScalerSetByte(PC9_DA_RX_K_OOBS_06, 0x00);

        // [5] reg_oobs_offset_ok_l1 = 1'b0 -> Disable Manual Mode Calibration ok
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT5, 0x00);

        // [4] reg_oobs_offset_manual_l1 = 1'b0 -> Calibration Auto Mode
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT4, 0x00);

        // [4] reg_rstb_oobs_offset = 1'b0 >> 1'b1 -> reset
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT4, 0x00);
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT4, _BIT4);

        // [1] reg_oobs_offset_en_l1 = 1'b1 -> Set Calibration Mode Enable
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT1, _BIT1);

        // Delay Time us [0,500] Waiting for Calibration Done
        for(ucTemp = 0; ucTemp <= 50; ucTemp++)
        {
            DELAY_10US();

            if(ScalerGetBit(PC9_DC_RX_K_OOBS_08, _BIT3) == _BIT3)
            {
                break;
            }
        }

        ucOobsOffsetL2 = (((ScalerGetByte(PC9_DB_RX_K_OOBS_07) & 0xC0) >> 1) | ((ScalerGetByte(PC9_DE_RX_K_OOBS_10) & 0xF1) >> 3));

        DebugMessageRx1("Dp_Rx1_ucOobsOffsetL2", ucOobsOffsetL2);

        // [1] reg_oobs_offset_en_l1 = 1'b0 -> Disable calibration
        ScalerSetBit(PC9_D4_RX_K_OOBS_00, ~_BIT1, 0x00);

        // [5] reg_oobs_offset_ok_l1 = 1'b1 -> Enable Manual Mode Calibration ok
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT5, _BIT5);

        // [4] reg_oobs_offset_manual_l1 = 1'b1 -> Calibration Manual Mode
        ScalerSetBit(PC9_D7_RX_K_OOBS_03, ~_BIT4, _BIT4);

        if((ucOobsOffsetL2 != 0x7F) || (ucOobsSenVal == (_BIT1 | _BIT0)))
        {
            // Reload L2 Calibration Result
            ScalerSetBit(PC9_DB_RX_K_OOBS_07, ~(_BIT1 | _BIT0), (ScalerGetByte(PC9_DB_RX_K_OOBS_07) >> 6));
            ScalerSetByte(PC9_DA_RX_K_OOBS_06, ScalerGetByte(PC9_DE_RX_K_OOBS_10));

            break;
        }
    }
}
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Rebuilding DP PHY (Lane1/3)
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1RebuildUnFlip2LanePhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];
    BYTE pucTap0[2];
    WORD usTargetClock = 0;


    ////////////////////
    // 2 Lane Initial //
    ////////////////////

    DebugMessageRx1("RebuildPhy UnFlip 2 Lane", (WORD)(enumDpLinkRate << 8) + ucDpcdLane);

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [3/2] Enable Foreground Offset Calibration
    ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3/2] reg_en_vco_lpf = 2'b11 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [7/6] reg_timer_en = 1 for CDR_RDY
    // [3/2] reg_acdr_en = 1
    ScalerSetBit(P7A_96_DATA_TIMER_0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));

    // reg_en_fld_clk = 2'b11 --> Enable FLD Clock
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit(PB1_80_FLD_L2_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_C0_FLD_L3_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_EE_FLD_L3_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit(PB1_AF_FLD_L2_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_EF_FLD_L3_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
#endif
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)) || (_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON))
        ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE2);
        ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE3);
#endif
        switch(ucDpcdLane & 0x1F)
        {
            case _DP_ONE_LANE:

                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());

                break;

            default:
            case _DP_TWO_LANE:

                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());
                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE1_MAPPING());

                break;
        }
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7/6] reg_en_clkout_manual = 1'b0
    // [3/2] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7/6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(enumDpLinkRate);

    if(enumDpLinkRate >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(enumDpLinkRate, _DP_NF_REF_XTAL);

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_A5_FLD_L2_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_A5_FLD_L2_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_A5_FLD_L2_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            DebugMessageRx1("1st Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }


    //////////////
    // FLD Band //
    //////////////

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            DebugMessageRx1("1st FLD Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte(PB1_94_FLD_L2_20, ScalerGetByte(PB1_B2_FLD_L2_48));
    ScalerSetByte(PB1_D4_FLD_L3_20, ScalerGetByte(PB1_F2_FLD_L3_48));

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    DELAY_10US();

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            DebugMessageRx1("2nd FLD Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(100);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(100);

    // Disable DFE Adaptation
    ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0x00);

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte(PB2_F0_COEF_1, 0x01);

        // Select to Lane2
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_C4_L2_INIT_2, 0x1F);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_C4_L2_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_D4_L3_INIT_2, 0x1F);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_D4_L3_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane2
    if((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte(P7A_AD_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AD_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x20);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x20);

    ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x00);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            DebugMessageRx1("2nd Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte(PB1_94_FLD_L2_20, ScalerGetByte(PB1_B2_FLD_L2_48));
    ScalerSetByte(PB1_D4_FLD_L3_20, ScalerGetByte(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7/6] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    usTargetClock = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, _DP_PHY_RX1_D1_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_125_CYCLE) << 3;

    if(usTargetClock != 0)
    {
        g_pusDpPhyRx1ClockTarget[0] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[1] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[2] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[3] = usTargetClock;
    }
}


//--------------------------------------------------
// Description  : Rebuilding DP PHY (Lane0/2)
// Input Value  : DPCD Bit Rate and Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1RebuildFlip2LanePhy(EnumDpLinkRate enumDpLinkRate, BYTE ucDpcdLane)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];
    BYTE pucTap0[2];
    WORD usTargetClock = 0;


    ////////////////////
    // 2 Lane Initial //
    ////////////////////

    DebugMessageRx1("RebuildPhy Flip 2 Lane", (WORD)(enumDpLinkRate << 8) + ucDpcdLane);

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [1/0] Enable Foreground Offset Calibration
    ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1/0] reg_en_vco_lpf = 2'b11 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [5/4] reg_timer_en = 1 for CDR_RDY
    // [1/0] reg_acdr_en = 1
    ScalerSetBit(P7A_96_DATA_TIMER_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));

    // reg_en_fld_clk = 2'b11 --> Enable FLD Clock
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit(PB1_00_FLD_L0_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_40_FLD_L1_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_6E_FLD_L1_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit(PB1_2F_FLD_L0_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_6F_FLD_L1_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _OFF)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
#endif
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_SOURCE_BACKGROUND_DETECT_SUPPORT == _OFF)) || (_DP_DYNAMIC_POWER_MANAGEMENT_SUPPORT == _ON))
        ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE0);
        ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE1);
#endif
        switch(ucDpcdLane & 0x1F)
        {
            case _DP_ONE_LANE:

                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());

                break;

            default:
            case _DP_TWO_LANE:

                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());
                ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE1_MAPPING());

                break;
        }
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5/4] reg_en_clkout_manual = 1'b0
    // [1/0] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    ScalerDpPhyRx1SetDFEInitialFlip2Lane(enumDpLinkRate);

    if(enumDpLinkRate >= _DP_LINK_HBR3)
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    ScalerDpPhyRx1APhyFLDSettingFlip2Lane(enumDpLinkRate, _DP_NF_REF_XTAL);

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_25_FLD_L0_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);

    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_70_FLD_L1_46, ~_BIT5, 0x00);

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
        {
            DebugMessageRx1("1st Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }


    //////////////
    // FLD Band //
    //////////////

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            DebugMessageRx1("1st FLD Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetByte(PB1_14_FLD_L0_20, ScalerGetByte(PB1_32_FLD_L0_48));
    ScalerSetByte(PB1_54_FLD_L1_20, ScalerGetByte(PB1_72_FLD_L1_48));

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

    DELAY_10US();

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // [7] reg_fld_rst_n = 1 --> Enable FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            DebugMessageRx1("2nd FLD Time = pData[0]*5us", pData[0]);
            break;
        }
    }

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(100);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(100);

    // Disable DFE Adaptation
    ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0x00);

    if(enumDpLinkRate >= _DP_LINK_HBR2)
    {
        // Read Back Tap0
        ScalerSetByte(PB2_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_A4_L0_INIT_2, 0x1F);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_B4_L1_INIT_2, 0x1F);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte(P7A_AB_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AB_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte(PB2_AA_L0_INIT_8, 0x20);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x20);

    ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x00);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
        {
            DebugMessageRx1("2nd Foreground Offset Time = pData[0]*5us", pData[0]);
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetByte(PB1_14_FLD_L0_20, ScalerGetByte(PB1_32_FLD_L0_48));
    ScalerSetByte(PB1_54_FLD_L1_20, ScalerGetByte(PB1_72_FLD_L1_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT2, 0x00);

    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[0]);

    // [5/4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ///////////////////////
    // CDR Clock Measure //
    ///////////////////////

    usTargetClock = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, _DP_PHY_RX1_D1_LANE0, _DP_MEASURE_TARGET_CDR_CLOCK, _DP_MEASURE_PERIOD_125_CYCLE) << 3;

    if(usTargetClock != 0)
    {
        g_pusDpPhyRx1ClockTarget[0] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[1] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[2] = usTargetClock;
        g_pusDpPhyRx1ClockTarget[3] = usTargetClock;
    }
}
#endif

//--------------------------------------------------
// Description  : DP APhy Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1APhyFLDSetting4Lane(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef)
{
    // reg_sel_large_kvco = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit(PB2_0F_RX_TOP_15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));
    ScalerSetBit(PB2_10_RX_TOP_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_large_kvco_lpf_sel = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit(PB2_31_RX_CDR_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));
    ScalerSetBit(PB2_32_RX_CDR_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_vco_lpf_force_en = 4'b1111 --> Enable Force VCO LPF by Register
    ScalerSetBit(PB2_20_RX_CDR_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_v2i_lpf_force_en = 4'b1111 --> Enable V2I Dual Loop LPF
    ScalerSetBit(PB2_27_RX_CDR_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_en_lpf_dual_loop = 4'b1111 --> Enable LPF in Dual Loop
    ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_ldo_cp_vsel = 2'b10 --> 1.05V
    ScalerSetByte(PB2_35_RX_CDR_21, 0xAA);

    // reg_en_cp_kp_path = 1 --> Enable Direct Modulation Mode
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // reg_cdr_r = 2K
    ScalerSetBit(PB1_2B_FLD_L0_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB1_6B_FLD_L1_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB1_AB_FLD_L2_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB1_EB_FLD_L3_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // reg_slope_icp_offset = 2 -> 1 -> 0 --> 0 00100001 00000100 00100000 = 0x0210420
    ScalerSetBit(PB1_29_FLD_L0_39, ~_BIT1, 0x00);
    ScalerSetByte(PB1_27_FLD_L0_37, 0x21);
    ScalerSetByte(PB1_26_FLD_L0_36, 0x04);
    ScalerSetByte(PB1_25_FLD_L0_35, 0x20);

    ScalerSetBit(PB1_69_FLD_L1_39, ~_BIT1, 0x00);
    ScalerSetByte(PB1_67_FLD_L1_37, 0x21);
    ScalerSetByte(PB1_66_FLD_L1_36, 0x04);
    ScalerSetByte(PB1_65_FLD_L1_35, 0x20);

    ScalerSetBit(PB1_A9_FLD_L2_39, ~_BIT1, 0x00);
    ScalerSetByte(PB1_A7_FLD_L2_37, 0x21);
    ScalerSetByte(PB1_A6_FLD_L2_36, 0x04);
    ScalerSetByte(PB1_A5_FLD_L2_35, 0x20);

    ScalerSetBit(PB1_E9_FLD_L3_39, ~_BIT1, 0x00);
    ScalerSetByte(PB1_E7_FLD_L3_37, 0x21);
    ScalerSetByte(PB1_E6_FLD_L3_36, 0x04);
    ScalerSetByte(PB1_E5_FLD_L3_35, 0x20);

    if(enumDpNFCodeRef == _DP_NF_REF_D10_2)
    {
        // reg_ref_clk_sel = 1 --> Ref. D10.2/20 Clock
        ScalerSetBit(PB1_2A_FLD_L0_40, ~_BIT5, _BIT5);
        ScalerSetBit(PB1_6A_FLD_L1_40, ~_BIT5, _BIT5);
        ScalerSetBit(PB1_AA_FLD_L2_40, ~_BIT5, _BIT5);
        ScalerSetBit(PB1_EA_FLD_L3_40, ~_BIT5, _BIT5);

        // divide num = 100
        ScalerSetByte(PB1_1B_FLD_L0_27, 0x64);
        ScalerSetByte(PB1_5B_FLD_L1_27, 0x64);
        ScalerSetByte(PB1_9B_FLD_L2_27, 0x64);
        ScalerSetByte(PB1_DB_FLD_L3_27, 0x64);

        // ref_cnt = divid_num * 2 * target_freq/ref_clock
        // 400   =     100     * 2 * (data_rate/20) / (data_rate/2/20)
        ScalerSetByte(PB1_17_FLD_L0_23, 0x90);
        ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte(PB1_19_FLD_L0_25, 0x90);
        ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte(PB1_57_FLD_L1_23, 0x90);
        ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte(PB1_59_FLD_L1_25, 0x90);
        ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte(PB1_97_FLD_L2_23, 0x90);
        ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte(PB1_99_FLD_L2_25, 0x90);
        ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte(PB1_D7_FLD_L3_23, 0x90);
        ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte(PB1_D9_FLD_L3_25, 0x90);
        ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // reg_ref_clk_sel = 0 --> Ref. XTAL Clock 27MHz
        ScalerSetBit(PB1_2A_FLD_L0_40, ~_BIT5, 0x00);
        ScalerSetBit(PB1_6A_FLD_L1_40, ~_BIT5, 0x00);
        ScalerSetBit(PB1_AA_FLD_L2_40, ~_BIT5, 0x00);
        ScalerSetBit(PB1_EA_FLD_L3_40, ~_BIT5, 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR10)
    {
        // Disable VCO Low Power Mode
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
        ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // V2I Isel = 3'010 --> X3
        ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    }
    else
    {
        // Enable VCO Low Power Mode
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
        ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // V2I Isel = 3'000 --> X1
        ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR13_5)
    {
        // reg_sel_large_iptat = 3'b001 --> 12.5%
        ScalerSetBit(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // reg_lehv_isel = 0
        ScalerSetBit(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_large_iptat = 3'b000 --> 0%
        ScalerSetBit(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // reg_lehv_isel = 1
        ScalerSetBit(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

    switch(enumDpLinkRate)
    {
        case _DP_LINK_UHBR13_5: // UHBR135

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_sel_div = 3'b000
            ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x31);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE1);

            // FLD Initial Band = 0x100
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, _BIT0);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, _BIT0);
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, _BIT0);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, _BIT0);
            ScalerSetByte(PB1_14_FLD_L0_20, 0x00);
            ScalerSetByte(PB1_54_FLD_L1_20, 0x00);
            ScalerSetByte(PB1_94_FLD_L2_20, 0x00);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 6750 =  14.318  * 2 * (232 + 4) --> N = 0x0E8
            ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte(PB2_2D_RX_CDR_13, 0xE8);
            ScalerSetByte(PB2_2E_RX_CDR_14, 0xE8);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // divide num = 20
                ScalerSetByte(PB1_1B_FLD_L0_27, 0x14);
                ScalerSetByte(PB1_5B_FLD_L1_27, 0x14);
                ScalerSetByte(PB1_9B_FLD_L2_27, 0x14);
                ScalerSetByte(PB1_DB_FLD_L3_27, 0x14);

                // Divide Num x 2 x (6750/16) / 27MHz = FLD Counter
                // 20         x 2 x  421.875  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte(PB1_17_FLD_L0_23, 0x71);
                ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_19_FLD_L0_25, 0x71);
                ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_57_FLD_L1_23, 0x71);
                ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_59_FLD_L1_25, 0x71);
                ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_97_FLD_L2_23, 0x71);
                ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_99_FLD_L2_25, 0x71);
                ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_D7_FLD_L3_23, 0x71);
                ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_D9_FLD_L3_25, 0x71);
                ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), 0x00);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR13P5() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR13P5());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR13P5());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());

            g_pusDpPhyRx1ClockTarget[0] = 0x61A8; // ideal 13.5G

            break;

        case _DP_LINK_UHBR10:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x33);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xA2);

            // reg_sel_div = 3'b000
            ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 5000 = 14.318  * 2 * (170 + 4) --> N = 0x0AA
            ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte(PB2_2D_RX_CDR_13, 0xAA);
            ScalerSetByte(PB2_2E_RX_CDR_14, 0xAA);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // FLD Initial Band = 0xA0
                ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
                ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
                ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
                ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
                ScalerSetByte(PB1_14_FLD_L0_20, 0xA0);
                ScalerSetByte(PB1_54_FLD_L1_20, 0xA0);
                ScalerSetByte(PB1_94_FLD_L2_20, 0xA0);
                ScalerSetByte(PB1_D4_FLD_L3_20, 0xA0);

                // divide num = 27
                ScalerSetByte(PB1_1B_FLD_L0_27, 0x1B);
                ScalerSetByte(PB1_5B_FLD_L1_27, 0x1B);
                ScalerSetByte(PB1_9B_FLD_L2_27, 0x1B);
                ScalerSetByte(PB1_DB_FLD_L3_27, 0x1B);

                // Divide Num x 2 x (5000/16) / 27MHz = FLD Counter
                // 27         x 2 x   312. 5  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte(PB1_17_FLD_L0_23, 0x71);
                ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_19_FLD_L0_25, 0x71);
                ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_57_FLD_L1_23, 0x71);
                ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_59_FLD_L1_25, 0x71);
                ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_97_FLD_L2_23, 0x71);
                ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_99_FLD_L2_25, 0x71);
                ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_D7_FLD_L3_23, 0x71);
                ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_D9_FLD_L3_25, 0x71);
                ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR10() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR10() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR10() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR10() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR10());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR10());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());

            g_pusDpPhyRx1ClockTarget[0] = 0x4857; // ideal 10G

            break;

        case _DP_LINK_HBR3_9G:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xE0
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0xE0);
            ScalerSetByte(PB1_54_FLD_L1_20, 0xE0);
            ScalerSetByte(PB1_94_FLD_L2_20, 0xE0);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0xE0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4500 =  14.318  * 2 * (153 + 4) --> N = 0x099
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x99);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x99);

                    // divide num = 24
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x18);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (4500/16) / 27MHz = FLD Counter
                    // 24         x 2 x   281.25  / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 9000 =  14.318  * 2 * (310 + 4) --> N = 0x136
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x36);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x36);

                    // divide num = 18
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x12);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x12);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x12);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x12);

                    // Divide Num x 2 x (9000/16) / 27MHz = FLD Counter
                    // 18         x 2 x    562.5  / 27MHz = 750 = 0x2EE  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xEE);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xEE);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xEE);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xEE);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0xEE);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xEE);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xEE);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xEE);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x411B; // ideal 9G

            break;

        case _DP_LINK_HBR3:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xC0
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0xC0);
            ScalerSetByte(PB1_54_FLD_L1_20, 0xC0);
            ScalerSetByte(PB1_94_FLD_L2_20, 0xC0);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0xC0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4050 =  14.318  * 2 * (137 + 4) --> N = 0x089
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x89);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x89);

                    // divide num = 36
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x24);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x24);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x24);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x24);

                    // Divide Num x 2 x (4050/16) / 27MHz = FLD Counter
                    // 36         x 2 x  253.125  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xA3);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xA3);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xA3);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xA3);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0xA3);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xA3);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xA3);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xA3);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 8100 =  14.318  * 2 * (279 + 4) --> N = 0x117
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x17);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x17);

                    // divide num = 18
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x12);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x12);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x12);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x12);

                    // Divide Num x 2 x (8100/16) / 27MHz = FLD Counter
                    // 18         x 2 x   506.25  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xA3);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xA3);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xA3);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xA3);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0xA3);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xA3);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xA3);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xA3);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x3A98; // ideal 8.1G

            break;

        case _DP_LINK_HBR2:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x27);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xC4);

            // FLD Initial Band = 0x068
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0x68);
            ScalerSetByte(PB1_54_FLD_L1_20, 0x68);
            ScalerSetByte(PB1_94_FLD_L2_20, 0x68);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x5A);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x5A);

                    // divide num = 24
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x18);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0x2C);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0x2C);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0x2C);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0x2C);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0x2C);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0x2C);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0x2C);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0x2C);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0xB8);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0xB8);

                    // divide num = 20
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x14);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR2() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR2() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR2() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR2() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR2());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR2());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());

            g_pusDpPhyRx1ClockTarget[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x068
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0x68);
            ScalerSetByte(PB1_54_FLD_L1_20, 0x68);
            ScalerSetByte(PB1_94_FLD_L2_20, 0x68);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x5A);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x5A);

                    // divide num = 24
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x18);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0x2C);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0x2C);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0x2C);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0x2C);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0x2C);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0x2C);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0x2C);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0x2C);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0xB8);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0xB8);

                    // divide num = 20
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x14);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());

            g_pusDpPhyRx1ClockTarget[0] = 0x1388; // ideal 2.7G

            break;

        case _DP_LINK_RBR:
        default:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x0A0
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0xA0);
            ScalerSetByte(PB1_54_FLD_L1_20, 0xA0);
            ScalerSetByte(PB1_94_FLD_L2_20, 0xA0);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0xA0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 3240 =  14.318  * 2 * (109 + 4) --> N = 0x06D
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x6D);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x6D);

                    // divide num = 32
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x20);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x20);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x20);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x20);

                    // Divide Num x 2 x (3240/15) / 27MHz = FLD Counter
                    // 32         x 2     202.5   / 27MHz = 480 = 0x1E0  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xE0);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xE0);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xE0);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xE0);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0xE0);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xE0);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xE0);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xE0);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b011
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 6480 =  14.318  * 2 * (222 + 4) --> N = 0x0DE
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0xDE);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0xDE);

                    // divide num = 20
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x14);
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (6480/16) / 27MHz = FLD Counter
                    // 20         x 2 x     405   / 27MHz = 600 = 0x258  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0x58);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0x58);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0x58);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0x58);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_97_FLD_L2_23, 0x58);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0x58);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0x58);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0x58);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b10 --> -25%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT3);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_RBR() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_RBR() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_RBR() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_RBR() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_RBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_RBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());

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
void ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef)
{
    // reg_sel_large_kvco = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit(PB2_10_RX_TOP_16, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_large_kvco_lpf_sel = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit(PB2_32_RX_CDR_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_vco_lpf_force_en = 2'b11 --> Enable Force VCO LPF by Register
    ScalerSetBit(PB2_20_RX_CDR_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // reg_v2i_lpf_force_en = 2'b11 --> Enable V2I Dual Loop LPF
    ScalerSetBit(PB2_27_RX_CDR_07, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // reg_en_lpf_dual_loop = 2'b11 --> Enable LPF in Dual Loop
    ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // reg_ldo_cp_vsel = 2'b10 --> 1.05V
    ScalerSetBit(PB2_35_RX_CDR_21, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // reg_en_cp_kp_path = 1 --> Enable Direct Modulation Mode
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // reg_cdr_r = 2K
    ScalerSetBit(PB1_AB_FLD_L2_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit(PB1_EB_FLD_L3_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // reg_slope_icp_offset = 2 -> 1 -> 0 --> 0 00100001 00000100 00100000 = 0x0210420
    ScalerSetBit(PB1_A9_FLD_L2_39, ~_BIT1, 0x00);
    ScalerSetByte(PB1_A7_FLD_L2_37, 0x21);
    ScalerSetByte(PB1_A6_FLD_L2_36, 0x04);
    ScalerSetByte(PB1_A5_FLD_L2_35, 0x20);

    ScalerSetBit(PB1_E9_FLD_L3_39, ~_BIT1, 0x00);
    ScalerSetByte(PB1_E7_FLD_L3_37, 0x21);
    ScalerSetByte(PB1_E6_FLD_L3_36, 0x04);
    ScalerSetByte(PB1_E5_FLD_L3_35, 0x20);

    if(enumDpNFCodeRef == _DP_NF_REF_D10_2)
    {
        // reg_ref_clk_sel = 1 --> Ref. D10.2/20 Clock
        ScalerSetBit(PB1_AA_FLD_L2_40, ~_BIT5, _BIT5);
        ScalerSetBit(PB1_EA_FLD_L3_40, ~_BIT5, _BIT5);

        // divide num = 100
        ScalerSetByte(PB1_9B_FLD_L2_27, 0x64);
        ScalerSetByte(PB1_DB_FLD_L3_27, 0x64);

        // ref_cnt = divid_num * 2 * target_freq/ref_clock
        // 400   =     100     * 2 * (data_rate/20) / (data_rate/2/20)
        ScalerSetByte(PB1_97_FLD_L2_23, 0x90);
        ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte(PB1_99_FLD_L2_25, 0x90);
        ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte(PB1_D7_FLD_L3_23, 0x90);
        ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte(PB1_D9_FLD_L3_25, 0x90);
        ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // reg_ref_clk_sel = 0 --> Ref. XTAL Clock 27MHz
        ScalerSetBit(PB1_AA_FLD_L2_40, ~_BIT5, 0x00);
        ScalerSetBit(PB1_EA_FLD_L3_40, ~_BIT5, 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR10)
    {
        // Disable VCO Low Power Mode
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT7 | _BIT6), 0x00);

        // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
        ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // V2I Isel = 3'010 --> X3
        ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    }
    else
    {
        // Enable VCO Low Power Mode
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
        ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT7 | _BIT6), 0x00);

        // V2I Isel = 3'000 --> X1
        ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR13_5)
    {
        // reg_sel_large_iptat = 3'b001 --> 12.5%
        ScalerSetBit(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // reg_lehv_isel = 0
        ScalerSetBit(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2), 0x00);
    }
    else
    {
        // reg_sel_large_iptat = 3'b000 --> 0%
        ScalerSetBit(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // reg_lehv_isel = 1
        ScalerSetBit(PB2_0D_RX_TOP_13, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }

    switch(enumDpLinkRate)
    {
        case _DP_LINK_UHBR13_5: // UHBR135

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_sel_div = 3'b000
            ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x31);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE1);

            // FLD Initial Band = 0x100
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, _BIT0);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, _BIT0);
            ScalerSetByte(PB1_94_FLD_L2_20, 0x00);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 6750 =  14.318  * 2 * (232 + 4) --> N = 0x0E8
            ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
            ScalerSetByte(PB2_2E_RX_CDR_14, 0xE8);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // divide num = 20
                ScalerSetByte(PB1_9B_FLD_L2_27, 0x14);
                ScalerSetByte(PB1_DB_FLD_L3_27, 0x14);

                // Divide Num x 2 x (6750/16) / 27MHz = FLD Counter
                // 20         x 2 x  421.875  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte(PB1_97_FLD_L2_23, 0x71);
                ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_99_FLD_L2_25, 0x71);
                ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_D7_FLD_L3_23, 0x71);
                ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_D9_FLD_L3_25, 0x71);
                ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), 0x00);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR13P5() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR13P5());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR13P5());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());

            g_pusDpPhyRx1ClockTarget[0] = 0x61A8; // ideal 13.5G

            break;

        case _DP_LINK_UHBR10:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x33);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xA2);

            // reg_sel_div = 3'b000
            ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 5000 = 14.318  * 2 * (170 + 4) --> N = 0x0AA
            ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte(PB2_2D_RX_CDR_13, 0xAA);
            ScalerSetByte(PB2_2E_RX_CDR_14, 0xAA);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // FLD Initial Band = 0xA0
                ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
                ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
                ScalerSetByte(PB1_94_FLD_L2_20, 0xA0);
                ScalerSetByte(PB1_D4_FLD_L3_20, 0xA0);

                // divide num = 27
                ScalerSetByte(PB1_9B_FLD_L2_27, 0x1B);
                ScalerSetByte(PB1_DB_FLD_L3_27, 0x1B);

                // Divide Num x 2 x (5000/16) / 27MHz = FLD Counter
                // 27         x 2 x   312. 5  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte(PB1_97_FLD_L2_23, 0x71);
                ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_99_FLD_L2_25, 0x71);
                ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_D7_FLD_L3_23, 0x71);
                ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_D9_FLD_L3_25, 0x71);
                ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR10() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR10() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR10() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR10() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR10());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR10());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());

            g_pusDpPhyRx1ClockTarget[0] = 0x4857; // ideal 10G

            break;

        case _DP_LINK_HBR3_9G:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xE0
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_94_FLD_L2_20, 0xE0);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0xE0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4500 =  14.318  * 2 * (153 + 4) --> N = 0x099
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x99);

                    // divide num = 24
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (4500/16) / 27MHz = FLD Counter
                    // 24         x 2 x   281.25  / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 9000 =  14.318  * 2 * (310 + 4) --> N = 0x136
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, _BIT0);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x36);

                    // divide num = 18
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x12);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x12);

                    // Divide Num x 2 x (9000/16) / 27MHz = FLD Counter
                    // 18         x 2 x    562.5  / 27MHz = 750 = 0x2EE  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0xEE);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xEE);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xEE);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xEE);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x411B; // ideal 9G

            break;

        case _DP_LINK_HBR3:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xC0
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_94_FLD_L2_20, 0xC0);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0xC0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4050 =  14.318  * 2 * (137 + 4) --> N = 0x089
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x89);

                    // divide num = 36
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x24);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x24);

                    // Divide Num x 2 x (4050/16) / 27MHz = FLD Counter
                    // 36         x 2 x  253.125  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0xA3);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xA3);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xA3);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xA3);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 8100 =  14.318  * 2 * (279 + 4) --> N = 0x117
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, _BIT0);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x17);

                    // divide num = 18
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x12);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x12);

                    // Divide Num x 2 x (8100/16) / 27MHz = FLD Counter
                    // 18         x 2 x   506.25  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0xA3);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xA3);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xA3);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xA3);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x3A98; // ideal 8.1G

            break;

        case _DP_LINK_HBR2:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x27);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xC4);

            // FLD Initial Band = 0x068
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_94_FLD_L2_20, 0x68);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x5A);

                    // divide num = 24
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0x2C);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0x2C);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0x2C);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0x2C);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0xB8);

                    // divide num = 20
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR2() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR2() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR2() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR2() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR2());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR2());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());

            g_pusDpPhyRx1ClockTarget[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x068
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_94_FLD_L2_20, 0x68);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x5A);

                    // divide num = 24
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x18);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0x2C);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0x2C);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0x2C);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0x2C);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0xB8);

                    // divide num = 20
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0xF4);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xF4);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xF4);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xF4);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());

            g_pusDpPhyRx1ClockTarget[0] = 0x1388; // ideal 2.7G

            break;

        case _DP_LINK_RBR:
        default:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x0A0
            ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_94_FLD_L2_20, 0xA0);
            ScalerSetByte(PB1_D4_FLD_L3_20, 0xA0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 3240 =  14.318  * 2 * (109 + 4) --> N = 0x06D
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0x6D);

                    // divide num = 32
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x20);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x20);

                    // Divide Num x 2 x (3240/15) / 27MHz = FLD Counter
                    // 32         x 2     202.5   / 27MHz = 480 = 0x1E0  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0xE0);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0xE0);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0xE0);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0xE0);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b011
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 6480 =  14.318  * 2 * (222 + 4) --> N = 0x0DE
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT0, 0x00);
                    ScalerSetByte(PB2_2E_RX_CDR_14, 0xDE);

                    // divide num = 20
                    ScalerSetByte(PB1_9B_FLD_L2_27, 0x14);
                    ScalerSetByte(PB1_DB_FLD_L3_27, 0x14);

                    // Divide Num x 2 x (6480/16) / 27MHz = FLD Counter
                    // 20         x 2 x     405   / 27MHz = 600 = 0x258  //final ck_sys = 625M
                    ScalerSetByte(PB1_97_FLD_L2_23, 0x58);
                    ScalerSetBit(PB1_98_FLD_L2_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_99_FLD_L2_25, 0x58);
                    ScalerSetBit(PB1_9A_FLD_L2_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_D7_FLD_L3_23, 0x58);
                    ScalerSetBit(PB1_D8_FLD_L3_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_D9_FLD_L3_25, 0x58);
                    ScalerSetBit(PB1_DA_FLD_L3_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b10 --> -25%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT3);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_RBR() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_RBR() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_RBR() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_RBR() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_RBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_RBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT3 | _BIT2), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_49_RX_ICP_KP_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_89_FLD_L2_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit(PB1_C9_FLD_L3_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());

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
void ScalerDpPhyRx1APhyFLDSettingFlip2Lane(EnumDpLinkRate enumDpLinkRate, EnumDpNFCodeRef enumDpNFCodeRef)
{
    // reg_sel_large_kvco = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit(PB2_0F_RX_TOP_15, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_large_kvco_lpf_sel = 3'b100 --> 1xKVCO + 4xKVCO(Dual Loop)
    ScalerSetBit(PB2_31_RX_CDR_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

    // reg_vco_lpf_force_en = 2'b11 --> Enable Force VCO LPF by Register
    ScalerSetBit(PB2_20_RX_CDR_00, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // reg_v2i_lpf_force_en = 2'b11 --> Enable V2I Dual Loop LPF
    ScalerSetBit(PB2_27_RX_CDR_07, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // reg_en_lpf_dual_loop = 2'b11 --> Enable LPF in Dual Loop
    ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // reg_ldo_cp_vsel = 2'b10 --> 1.05V
    ScalerSetBit(PB2_35_RX_CDR_21, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // reg_en_cp_kp_path = 1 --> Enable Direct Modulation Mode
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // reg_cdr_r = 2K
    ScalerSetBit(PB1_2B_FLD_L0_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    ScalerSetBit(PB1_6B_FLD_L1_41, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // reg_slope_icp_offset = 2 -> 1 -> 0 --> 0 00100001 00000100 00100000 = 0x0210420
    ScalerSetBit(PB1_29_FLD_L0_39, ~_BIT1, 0x00);
    ScalerSetByte(PB1_27_FLD_L0_37, 0x21);
    ScalerSetByte(PB1_26_FLD_L0_36, 0x04);
    ScalerSetByte(PB1_25_FLD_L0_35, 0x20);

    ScalerSetBit(PB1_69_FLD_L1_39, ~_BIT1, 0x00);
    ScalerSetByte(PB1_67_FLD_L1_37, 0x21);
    ScalerSetByte(PB1_66_FLD_L1_36, 0x04);
    ScalerSetByte(PB1_65_FLD_L1_35, 0x20);

    if(enumDpNFCodeRef == _DP_NF_REF_D10_2)
    {
        // reg_ref_clk_sel = 1 --> Ref. D10.2/20 Clock
        ScalerSetBit(PB1_2A_FLD_L0_40, ~_BIT5, _BIT5);
        ScalerSetBit(PB1_6A_FLD_L1_40, ~_BIT5, _BIT5);

        // divide num = 100
        ScalerSetByte(PB1_1B_FLD_L0_27, 0x64);
        ScalerSetByte(PB1_5B_FLD_L1_27, 0x64);

        // ref_cnt = divid_num * 2 * target_freq/ref_clock
        // 400   =     100     * 2 * (data_rate/20) / (data_rate/2/20)
        ScalerSetByte(PB1_17_FLD_L0_23, 0x90);
        ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte(PB1_19_FLD_L0_25, 0x90);
        ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        ScalerSetByte(PB1_57_FLD_L1_23, 0x90);
        ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetByte(PB1_59_FLD_L1_25, 0x90);
        ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // reg_ref_clk_sel = 0 --> Ref. XTAL Clock 27MHz
        ScalerSetBit(PB1_2A_FLD_L0_40, ~_BIT5, 0x00);
        ScalerSetBit(PB1_6A_FLD_L1_40, ~_BIT5, 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR10)
    {
        // Disable VCO Low Power Mode
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT5 | _BIT4), 0x00);
        ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT5 | _BIT4), 0x00);

        // reg_en_le_hv_bias = 1 --> Enable LEQ HV Bias
        ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // V2I Isel = 3'010 --> X3
        ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    }
    else
    {
        // Enable VCO Low Power Mode
        ScalerSetBit(PB2_22_RX_CDR_02, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // reg_en_le_hv_bias = 0 --> Disable LEQ HV Bias
        ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT5 | _BIT4), 0x00);

        // V2I Isel = 3'000 --> X1
        ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }

    if(enumDpLinkRate >= _DP_LINK_UHBR13_5)
    {
        // reg_sel_large_iptat = 3'b001 --> 12.5%
        ScalerSetBit(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // reg_lehv_isel = 0
        ScalerSetBit(PB2_0D_RX_TOP_13, ~(_BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_large_iptat = 3'b000 --> 0%
        ScalerSetBit(P7A_35_CDR_DP_1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // reg_lehv_isel = 1
        ScalerSetBit(PB2_0D_RX_TOP_13, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }

    switch(enumDpLinkRate)
    {
        case _DP_LINK_UHBR13_5: // UHBR135

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_sel_div = 3'b000
            ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x31);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE1);

            // FLD Initial Band = 0x100
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, _BIT0);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, _BIT0);
            ScalerSetByte(PB1_14_FLD_L0_20, 0x00);
            ScalerSetByte(PB1_54_FLD_L1_20, 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 6750 =  14.318  * 2 * (232 + 4) --> N = 0x0E8
            ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
            ScalerSetByte(PB2_2D_RX_CDR_13, 0xE8);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // divide num = 20
                ScalerSetByte(PB1_1B_FLD_L0_27, 0x14);
                ScalerSetByte(PB1_5B_FLD_L1_27, 0x14);

                // Divide Num x 2 x (6750/16) / 27MHz = FLD Counter
                // 20         x 2 x  421.875  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte(PB1_17_FLD_L0_23, 0x71);
                ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_19_FLD_L0_25, 0x71);
                ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_57_FLD_L1_23, 0x71);
                ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_59_FLD_L1_25, 0x71);
                ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b00 --> 0%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), 0x00);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR13P5() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR13P5() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR13P5());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR13P5());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR13P5());

            g_pusDpPhyRx1ClockTarget[0] = 0x61A8; // ideal 13.5G

            break;

        case _DP_LINK_UHBR10:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x33);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xA2);

            // reg_sel_div = 3'b000
            ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // FVCO = CKREF_IN * 2 * (N + 4)
            // 5000 = 14.318  * 2 * (170 + 4) --> N = 0x0AA
            ScalerSetBit(PB2_2C_RX_CDR_12, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetByte(PB2_2D_RX_CDR_13, 0xAA);
            ScalerSetByte(PB2_2E_RX_CDR_14, 0xAA);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                // FLD Initial Band = 0xA0
                ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
                ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
                ScalerSetByte(PB1_14_FLD_L0_20, 0xA0);
                ScalerSetByte(PB1_54_FLD_L1_20, 0xA0);

                // divide num = 27
                ScalerSetByte(PB1_1B_FLD_L0_27, 0x1B);
                ScalerSetByte(PB1_5B_FLD_L1_27, 0x1B);

                // Divide Num x 2 x (5000/16) / 27MHz = FLD Counter
                // 27         x 2 x   312. 5  / 27MHz = 625 = 0x271  //final ck_sys = 625M
                ScalerSetByte(PB1_17_FLD_L0_23, 0x71);
                ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_19_FLD_L0_25, 0x71);
                ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                ScalerSetByte(PB1_57_FLD_L1_23, 0x71);
                ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                ScalerSetByte(PB1_59_FLD_L1_25, 0x71);
                ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_UHBR10() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_UHBR10() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_UHBR10() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_UHBR10() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_UHBR10());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_UHBR10());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_UHBR10());

            g_pusDpPhyRx1ClockTarget[0] = 0x4857; // ideal 10G

            break;

        case _DP_LINK_HBR3_9G:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xE0
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0xE0);
            ScalerSetByte(PB1_54_FLD_L1_20, 0xE0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4500 =  14.318  * 2 * (153 + 4) --> N = 0x099
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x99);

                    // divide num = 24
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x18);

                    // Divide Num x 2 x (4500/16) / 27MHz = FLD Counter
                    // 24         x 2 x   281.25  / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 9000 =  14.318  * 2 * (310 + 4) --> N = 0x136
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, _BIT1);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x36);

                    // divide num = 18
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x12);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x12);

                    // Divide Num x 2 x (9000/16) / 27MHz = FLD Counter
                    // 18         x 2 x    562.5  / 27MHz = 750 = 0x2EE  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xEE);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xEE);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xEE);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xEE);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x411B; // ideal 9G

            break;

        case _DP_LINK_HBR3:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            // FLD Initial Band = 0xC0
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0xC0);
            ScalerSetByte(PB1_54_FLD_L1_20, 0xC0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 4050 =  14.318  * 2 * (137 + 4) --> N = 0x089
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x89);

                    // divide num = 36
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x24);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x24);

                    // Divide Num x 2 x (4050/16) / 27MHz = FLD Counter
                    // 36         x 2 x  253.125  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xA3);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xA3);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xA3);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xA3);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 8100 =  14.318  * 2 * (279 + 4) --> N = 0x117
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, _BIT1);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x17);

                    // divide num = 18
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x12);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x12);

                    // Divide Num x 2 x (8100/16) / 27MHz = FLD Counter
                    // 18         x 2 x   506.25  / 27MHz = 675 = 0x2A3  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xA3);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xA3);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xA3);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xA3);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b01 --> -12.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT2);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR3() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR3() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR3() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR3() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR3());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR3());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR3());

            g_pusDpPhyRx1ClockTarget[0] = 0x3A98; // ideal 8.1G

            break;

        case _DP_LINK_HBR2:

            // bbpd_pulse_sel = 01 --> Half Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), _BIT0);

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x27);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xC4);

            // FLD Initial Band = 0x068
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0x68);
            ScalerSetByte(PB1_54_FLD_L1_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b000
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x5A);

                    // divide num = 24
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0x2C);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0x2C);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0x2C);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0x2C);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0xB8);

                    // divide num = 20
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR2() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR2() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR2() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR2() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR2());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR2());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR2());

            g_pusDpPhyRx1ClockTarget[0] = 0x2710; // ideal 5.4G

            break;

        case _DP_LINK_HBR:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x068
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0x68);
            ScalerSetByte(PB1_54_FLD_L1_20, 0x68);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b001
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 2700 =  14.318  * 2 * (90 + 4) --> N = 0x05A
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x5A);

                    // divide num = 24
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x18);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x18);

                    // Divide Num x 2 x (2700/16) / 27MHz = FLD Counter
                    // 24         x 2    168.75   / 27MHz = 300 = 0x12C  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0x2C);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0x2C);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0x2C);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0x2C);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 5400 =  14.318  * 2 * (184 + 4) --> N = 0x0B8
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0xB8);

                    // divide num = 20
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x14);

                    // Divide Num x 2 x (5400/16) / 27MHz = FLD Counter
                    // 20         x 2     337.5   / 27MHz = 500 = 0x1F4  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xF4);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xF4);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xF4);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xF4);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b11 --> -37.5%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_HBR() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_HBR() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_HBR() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_HBR() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_HBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_HBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_HBR());

            g_pusDpPhyRx1ClockTarget[0] = 0x1388; // ideal 2.7G

            break;

        case _DP_LINK_RBR:
        default:

            // bbpd_pulse_sel = 11 --> Full Rate /3
            ScalerSetBit(P7A_0A_MODE_CDR_DP, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x86);

            // FLD Initial Band = 0x0A0
            ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, 0x00);
            ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, 0x00);
            ScalerSetByte(PB1_14_FLD_L0_20, 0xA0);
            ScalerSetByte(PB1_54_FLD_L1_20, 0xA0);

            if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
            {
                if(ScalerGetBit(PB2_22_RX_CDR_02, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
                {
                    // reg_sel_div = 3'b010
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 3240 =  14.318  * 2 * (109 + 4) --> N = 0x06D
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0x6D);

                    // divide num = 32
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x20);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x20);

                    // Divide Num x 2 x (3240/15) / 27MHz = FLD Counter
                    // 32         x 2     202.5   / 27MHz = 480 = 0x1E0  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0xE0);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0xE0);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0xE0);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0xE0);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
                }
                else
                {
                    // reg_sel_div = 3'b011
                    ScalerSetBit(P7A_0E_MODE_OFFSET_K_DP_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // FVCO = CKREF_IN * 2 * (N + 4)
                    // 6480 =  14.318  * 2 * (222 + 4) --> N = 0x0DE
                    ScalerSetBit(PB2_2C_RX_CDR_12, ~_BIT1, 0x00);
                    ScalerSetByte(PB2_2D_RX_CDR_13, 0xDE);

                    // divide num = 20
                    ScalerSetByte(PB1_1B_FLD_L0_27, 0x14);
                    ScalerSetByte(PB1_5B_FLD_L1_27, 0x14);

                    // Divide Num x 2 x (6480/16) / 27MHz = FLD Counter
                    // 20         x 2 x     405   / 27MHz = 600 = 0x258  //final ck_sys = 625M
                    ScalerSetByte(PB1_17_FLD_L0_23, 0x58);
                    ScalerSetBit(PB1_18_FLD_L0_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_19_FLD_L0_25, 0x58);
                    ScalerSetBit(PB1_1A_FLD_L0_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

                    ScalerSetByte(PB1_57_FLD_L1_23, 0x58);
                    ScalerSetBit(PB1_58_FLD_L1_24, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                    ScalerSetByte(PB1_59_FLD_L1_25, 0x58);
                    ScalerSetBit(PB1_5A_FLD_L1_26, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
                }
            }

            // reg_sel_cco_neq_iptat = 2'b10 --> -25%
            ScalerSetBit(P7A_34_CDR_DP_0, ~(_BIT3 | _BIT2), _BIT3);

            // reg_cdr_cp
            ScalerSetBit(P7A_30_FLD_DP_0, ~_BIT2, 0x00);
            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_PHY_RX1_ICP_RBR() << 4) & 0xF0);

            ScalerSetBit(P7A_33_FLD_DP_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_DP_PHY_RX1_ICP_RBR() >> 1) & 0x0F);
            ScalerSetBit(P7A_32_FLD_DP_2, ~_BIT7, 0x00);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (GET_DP_PHY_RX1_ICP_RBR() << 2) & 0x7C);

            ScalerSetBit(P7A_32_FLD_DP_2, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT7 | _BIT6 | _BIT5), (GET_DP_PHY_RX1_ICP_RBR() << 5) & 0xE0);

            ScalerSetBit(P7A_31_FLD_DP_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_PHY_RX1_ICP_RBR());

            // reg_slope_icp_band --> Manual KICP
            ScalerSetBit(P7A_30_FLD_DP_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_ICP_KP_RBR());

            // reg_sel_large_Icp_Kp = 0 --> Disable Icp_Kp*3
            ScalerSetBit(PB2_25_RX_CDR_05, ~(_BIT1 | _BIT0), 0x00);

            // reg_sel_icp_kp_ratio
            ScalerSetBit(PB2_48_RX_ICP_KP_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            // reg_slope_vco_band --> Manual KVCO
            ScalerSetBit(PB1_09_FLD_L0_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());
            ScalerSetBit(PB1_49_FLD_L1_9, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), GET_DP_PHY_RX1_KVCO_RBR());

            g_pusDpPhyRx1ClockTarget[0] = 0xBB8; // ideal 1.62G

            break;
    }

    g_pusDpPhyRx1ClockTarget[1] = g_pusDpPhyRx1ClockTarget[0];
    g_pusDpPhyRx1ClockTarget[2] = g_pusDpPhyRx1ClockTarget[0];
    g_pusDpPhyRx1ClockTarget[3] = g_pusDpPhyRx1ClockTarget[0];
}
#endif

//--------------------------------------------------
// Description : Initial Signal check
// Input Value  : DP Link Rate
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SignalDetectInitial(BYTE ucDpLinkRate, BYTE ucDpLEQScanValue)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    ucDpLEQScanValue = ucDpLEQScanValue;


    /////////////////////////////
    // MAC Lane Swap Selection //
    /////////////////////////////

    ScalerDpMacDphyRxLaneSwapSelect(enumInputPort, _DP_PHY_RX1_D1_LANE0 << 6);

    // [4:3] DP MAC Select Four Lane
    ScalerDpMacDphyRxLaneCountSet(enumInputPort, _DP_FOUR_LANE);

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // SEL_Rate Initial
    ScalerSetBit(P7A_0D_MODE_OFFSET_K_DP_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);


    /////////////////////////////////
    // Frequency Parameter Setting //
    /////////////////////////////////

    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR3:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x13);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0xE2);

            break;

        case _DP_LINK_HBR2:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x24);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x63);

            break;

        case _DP_LINK_HBR:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x86);

            break;

        case _DP_LINK_RBR:
        default:

            // reg_le_rlsel/reg_le_sel_high_bw/reg_le_rssel/reg_le_isel
            ScalerSetByte(P7A_0B_MODE_GAIN_DP_00, 0x4F);
            ScalerSetByte(P7A_0C_MODE_GAIN_DP_01, 0x86);

            break;
    }


    ///////////////////////////
    // DP Mode for Detection //
    ///////////////////////////

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);

            ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());

            // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
            ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(ucDpLinkRate);

            // Enable Foreground Calibration
            ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
            DELAY_5US();
            ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

            // Delay Time us [0,500] Waiting for K Offset
            for(pData[0] = 0; pData[0] <= 100; pData[0]++)
            {
                DELAY_5US();

                if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
                   ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
                {
                    break;
                }
            }
        }
        else
        {
            ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
            ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
            ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE2);
            ScalerGDIPhyRx1LaneMode(_LANE_USB3_MODE, _GDI_PHY_LANE3);

            ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());

            // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
            ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            ScalerDpPhyRx1SetDFEInitialFlip2Lane(ucDpLinkRate);

            // Enable Foreground Calibration
            ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
            DELAY_5US();
            ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Delay Time us [0,500] Waiting for K Offset
            for(pData[0] = 0; pData[0] <= 100; pData[0]++)
            {
                DELAY_5US();

                if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
                   ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
                {
                    break;
                }
            }
        }
    }
    else
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    {
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE0);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE1);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE2);
        ScalerGDIPhyRx1LaneMode(_LANE_DP_MODE, _GDI_PHY_LANE3);

        // Disable JFM
        ScalerSetBit(P7A_92_DPHY_02, ~(_BIT6 | _BIT5), 0x00);

        ScalerGDIPhyRx1LanePower(_ENABLE, GET_DP_PHY_RX1_PCB_LANE0_MAPPING());

        // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
        ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        ScalerDpPhyRx1SetDFEInitial(ucDpLinkRate);

        // Enable Foreground Calibration
        ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        DELAY_5US();
        ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Delay Time us [0,500] Waiting for K Offset
        for(pData[0] = 0; pData[0] <= 100; pData[0]++)
        {
            DELAY_5US();

            if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
               ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
               ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
               ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
            {
                break;
            }
        }
    }
}

//--------------------------------------------------
// Description : Enable Signal Detection
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1SignalDetection(bit bEnable)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    if((ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_EMBEDDED) && (ScalerTypeCRxGetPinAssignment(enumInputPort) == _TYPE_C_PIN_ASSIGNMENT_D))
    {
        if(ScalerTypeCRxGetOrientation(enumInputPort) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            if(bEnable == _ENABLE)
            {
                // [3:0] Enable Signal Detection
                ScalerSetBit(PB2_30_RX_CDR_16, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                if(ScalerDpAuxRxGetLinkRate(enumInputPort) >= _DP_LINK_HBR2)
                {
                    // [7:4] reg_sel_ls_path_sigdtc = 4'b0000 --> Disable Low Speed Path for Signal Detection
                    ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT7 | _BIT6), 0x00);
                }
                else
                {
                    // [7:4] reg_sel_ls_path_sigdtc = 4'b1111 --> Enable Low Speed Path for Signal Detection
                    ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                }
            }
            else
            {
                // [3:0] Disable Signal Detection
                ScalerSetBit(PB2_30_RX_CDR_16, ~(_BIT3 | _BIT2), 0x00);
            }
        }
        else
        {
            if(bEnable == _ENABLE)
            {
                // [3:0] Enable Signal Detection
                ScalerSetBit(PB2_30_RX_CDR_16, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                if(ScalerDpAuxRxGetLinkRate(enumInputPort) >= _DP_LINK_HBR2)
                {
                    // [7:4] reg_sel_ls_path_sigdtc = 4'b0000 --> Disable Low Speed Path for Signal Detection
                    ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT5 | _BIT4), 0x00);
                }
                else
                {
                    // [7:4] reg_sel_ls_path_sigdtc = 4'b1111 --> Enable Low Speed Path for Signal Detection
                    ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
                }
            }
            else
            {
                // [3:0] Disable Signal Detection
                ScalerSetBit(PB2_30_RX_CDR_16, ~(_BIT1 | _BIT0), 0x00);
            }
        }
    }
    else
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
    {
        if(bEnable == _ENABLE)
        {
            // [3:0] Enable Signal Detection
            ScalerSetBit(PB2_30_RX_CDR_16, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            if(ScalerDpAuxRxGetLinkRate(enumInputPort) >= _DP_LINK_HBR2)
            {
                // [7:4] reg_sel_ls_path_sigdtc = 4'b0000 --> Disable Low Speed Path for Signal Detection
                ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            }
            else
            {
                // [7:4] reg_sel_ls_path_sigdtc = 4'b1111 --> Enable Low Speed Path for Signal Detection
                ScalerSetBit(PB2_26_RX_CDR_06, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            }
        }
        else
        {
            // [3:0] Disable Signal Detection
            ScalerSetBit(PB2_30_RX_CDR_16, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp1SetPhy4Lane(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];


    ////////////////////
    // 4 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [3:0] Enable Foreground Offset Calibration
    ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [3:0] reg_en_vco_lpf = 4'b1111 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] reg_timer_en = 1 for CDR_RDY
    // [3:0] reg_acdr_en = 1
    ScalerSetByte(P7A_96_DATA_TIMER_0, 0xFF);

    // reg_en_fld_clk = 4'b1111 --> Enable FLD Clock
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit(PB1_00_FLD_L0_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_40_FLD_L1_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_80_FLD_L2_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_C0_FLD_L3_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_6E_FLD_L1_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_EE_FLD_L3_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit(PB1_2F_FLD_L0_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_6F_FLD_L1_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_AF_FLD_L2_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_EF_FLD_L3_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7:4] LANE_EN = 4'b0000 --> Disable LANE_EN
    // [3:0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE0);
    ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE1);
    ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE2);
    ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE3);

    switch(g_ucDpPhyRx1CtsCtrl & 0x30)
    {
        case 0x30:

            // Lane3 Test, Enable LANE_EN/CDR_EN for Lane3
            ScalerGDIPhyRx1LanePower(_ENABLE, _DP_SCALER_LANE3);

            break;

        case 0x20:

            // Lane2 Test, Enable LANE_EN/CDR_EN for Lane2
            ScalerGDIPhyRx1LanePower(_ENABLE, _DP_SCALER_LANE2);

            break;

        case 0x10:

            // Lane1 Test, Enable LANE_EN/CDR_EN for Lane1
            ScalerGDIPhyRx1LanePower(_ENABLE, _DP_SCALER_LANE1);

            break;

        default:
        case 0x00:

            // Lane0 Test, Enable LANE_EN/CDR_EN for Lane0
            ScalerGDIPhyRx1LanePower(_ENABLE, _DP_SCALER_LANE0);

            break;
    }

    DebugMessageRx1("PHY Test Lane", ScalerGetByte(PB2_00_RX_TOP_00));

    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_clkout_manual = 1'b0
    // [3:0] reg_bypass_clk_rdy = 1'b0
    ScalerSetByte(P7A_97_DATA_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte(P7A_99_DATA_TIMER_3, 0x0F);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_HBR3);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_HBR2);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x40)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_HBR);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_RBR);
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_UHBR20);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_UHBR13_5);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_UHBR10);
        }
    }

    if(((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0) || (ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE))
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx1CtsCtrl & 0xC0)
        {
            case 0xC0:

                ScalerDpPhyRx1APhyFLDSetting4Lane(_DP_LINK_HBR3, enumDpNFCodeRef);

                break;

            case 0x80:

                ScalerDpPhyRx1APhyFLDSetting4Lane(_DP_LINK_HBR2, enumDpNFCodeRef);

                break;

            case 0x40:

                ScalerDpPhyRx1APhyFLDSetting4Lane(_DP_LINK_HBR, enumDpNFCodeRef);

                break;

            default:
            case 0x00:

                ScalerDpPhyRx1APhyFLDSetting4Lane(_DP_LINK_RBR, enumDpNFCodeRef);

                break;
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx1CtsCtrl & 0xC0)
        {
            case 0xC0:

                ScalerDpPhyRx1APhyFLDSetting4Lane(_DP_LINK_UHBR20, enumDpNFCodeRef);

                break;

            case 0x80:

                ScalerDpPhyRx1APhyFLDSetting4Lane(_DP_LINK_UHBR13_5, enumDpNFCodeRef);

                break;

            default:
            case 0x40:

                ScalerDpPhyRx1APhyFLDSetting4Lane(_DP_LINK_UHBR10, enumDpNFCodeRef);

                break;
        }
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_25_FLD_L0_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_70_FLD_L1_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[2]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////
    // FLD Band //
    //////////////

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    DebugMessageRx1("CTS TP1 L0 Band", ((((WORD)ScalerGetBit(PB1_33_FLD_L0_49, _BIT0)) << 8) | ScalerGetByte(PB1_32_FLD_L0_48)));
    DebugMessageRx1("CTS TP1 L1 Band", ((((WORD)ScalerGetBit(PB1_73_FLD_L1_49, _BIT0)) << 8) | ScalerGetByte(PB1_72_FLD_L1_48)));
    DebugMessageRx1("CTS TP1 L2 Band", ((((WORD)ScalerGetBit(PB1_B3_FLD_L2_49, _BIT0)) << 8) | ScalerGetByte(PB1_B2_FLD_L2_48)));
    DebugMessageRx1("CTS TP1 L3 Band", ((((WORD)ScalerGetBit(PB1_F3_FLD_L3_49, _BIT0)) << 8) | ScalerGetByte(PB1_F2_FLD_L3_48)));

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte(PB1_14_FLD_L0_20, ScalerGetByte(PB1_32_FLD_L0_48));
    ScalerSetByte(PB1_54_FLD_L1_20, ScalerGetByte(PB1_72_FLD_L1_48));
    ScalerSetByte(PB1_94_FLD_L2_20, ScalerGetByte(PB1_B2_FLD_L2_48));
    ScalerSetByte(PB1_D4_FLD_L3_20, ScalerGetByte(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[1]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[0]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    g_pusDpPhyRx1ClockTarget[(g_ucDpPhyRx1CtsCtrl & 0x30) >> 4] = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_1000_CYCLE);
}

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp1SetPhyUnFlip2Lane(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];


    ////////////////////
    // 2 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit(PB2_C0_L2_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_D0_L3_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [3/2] Enable Foreground Offset Calibration
    ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [3/2] reg_en_vco_lpf = 4'b1111 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [7/6] reg_timer_en = 1 for CDR_RDY
    // [3/2] reg_acdr_en = 1
    ScalerSetBit(P7A_96_DATA_TIMER_0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));

    // reg_en_fld_clk = 2'b11 --> Enable FLD Clock
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit(PB1_80_FLD_L2_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_C0_FLD_L3_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit(PB1_AE_FLD_L2_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_EE_FLD_L3_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit(PB1_AF_FLD_L2_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_EF_FLD_L3_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P7A_A5_ADJR_02, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A6_ADJR_03, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7/6] LANE_EN = 4'b0000 --> Disable LANE_EN
    // [3/2] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE2);
    ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE3);

    switch(g_ucDpPhyRx1CtsCtrl & 0x30)
    {
        case 0x30:

            // Lane3 Test, Enable LANE_EN/CDR_EN for Lane3
            ScalerGDIPhyRx1LanePower(_ENABLE, _DP_SCALER_LANE3);

            break;

        default:
        case 0x20:

            // Lane2 Test, Enable LANE_EN/CDR_EN for Lane2
            ScalerGDIPhyRx1LanePower(_ENABLE, _DP_SCALER_LANE2);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7/6] reg_en_clkout_manual = 1'b0
    // [3/2] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7/6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_HBR3);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_HBR2);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x40)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_HBR);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_RBR);
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_UHBR20);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_UHBR13_5);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_UHBR10);
        }
    }

    if(((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0) || (ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE))
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx1CtsCtrl & 0xC0)
        {
            case 0xC0:

                ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(_DP_LINK_HBR3, enumDpNFCodeRef);

                break;

            case 0x80:

                ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(_DP_LINK_HBR2, enumDpNFCodeRef);

                break;

            case 0x40:

                ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(_DP_LINK_HBR, enumDpNFCodeRef);

                break;

            default:
            case 0x00:

                ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(_DP_LINK_RBR, enumDpNFCodeRef);

                break;
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx1CtsCtrl & 0xC0)
        {
            case 0xC0:

                ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(_DP_LINK_UHBR20, enumDpNFCodeRef);

                break;

            case 0x80:

                ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(_DP_LINK_UHBR13_5, enumDpNFCodeRef);

                break;

            default:
            case 0x40:

                ScalerDpPhyRx1APhyFLDSettingUnFlip2Lane(_DP_LINK_UHBR10, enumDpNFCodeRef);

                break;
        }
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_A5_FLD_L2_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_A5_FLD_L2_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_A5_FLD_L2_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT2, _BIT2);

    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_F0_FLD_L3_46, ~_BIT5, 0x00);

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////
    // FLD Band //
    //////////////

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit(PB1_80_FLD_L2_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_C0_FLD_L3_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    DebugMessageRx1("CTS TP1 L2 Band", ((((WORD)ScalerGetBit(PB1_B3_FLD_L2_49, _BIT0)) << 8) | ScalerGetByte(PB1_B2_FLD_L2_48)));
    DebugMessageRx1("CTS TP1 L3 Band", ((((WORD)ScalerGetBit(PB1_F3_FLD_L3_49, _BIT0)) << 8) | ScalerGetByte(PB1_F2_FLD_L3_48)));

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_95_FLD_L2_21, ~_BIT0, ScalerGetBit(PB1_B3_FLD_L2_49, _BIT0));
    ScalerSetBit(PB1_D5_FLD_L3_21, ~_BIT0, ScalerGetBit(PB1_F3_FLD_L3_49, _BIT0));
    ScalerSetByte(PB1_94_FLD_L2_20, ScalerGetByte(PB1_B2_FLD_L2_48));
    ScalerSetByte(PB1_D4_FLD_L3_20, ScalerGetByte(PB1_F2_FLD_L3_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT2, 0x00);

    ScalerSetBit(PB1_B0_FLD_L2_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_F0_FLD_L3_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7/6] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    g_pusDpPhyRx1ClockTarget[(g_ucDpPhyRx1CtsCtrl & 0x30) >> 4] = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_1000_CYCLE);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1 for PHY CTS
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp1SetPhyFlip2Lane(EnumDpNFCodeRef enumDpNFCodeRef)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];


    ////////////////////
    // 2 Lane Initial //
    ////////////////////

    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [1:0] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    ScalerSetBit(PB2_A0_L0_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));
    ScalerSetBit(PB2_B0_L1_DFE_EN_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT1));

    // [1/0] Enable Foreground Offset Calibration
    ScalerSetBit(PB2_37_RX_EQ_00, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [1/0] reg_en_vco_lpf = 2'b11 --> Analog CDR Multi Band VCO's LPF Always On
    ScalerSetBit(PB2_2B_RX_CDR_11, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [5/4] reg_timer_en = 1 for CDR_RDY
    // [1/0] reg_acdr_en = 1
    ScalerSetBit(P7A_96_DATA_TIMER_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));

    // reg_en_fld_clk = 2'b11 --> Enable FLD Clock
    ScalerSetBit(PB2_2F_RX_CDR_15, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [5] reg_slope_icp_manual = 1 --> Manual Icp
    // [4] reg_slope_vco_manual = 1 --> Manual KVCO
    // [1:0] reg_fld_mode = 2'b00 -> K Band Only
    ScalerSetBit(PB1_00_FLD_L0_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));
    ScalerSetBit(PB1_40_FLD_L1_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    // [6] reg_adp_en_manual = 1 --> Enable CDR Clock
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT6, _BIT6);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT6, _BIT6);

    // [1:0] reg_ic_sel = 2'b01 --> Icp Select NV
    ScalerSetBit(PB1_2E_FLD_L0_44, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PB1_6E_FLD_L1_44, ~(_BIT1 | _BIT0), _BIT0);

    // [3:0] reg_cp2adp_time = 4'b0110 --> Assert adp_en after cp_en+2.4*6us
    ScalerSetBit(PB1_2F_FLD_L0_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(PB1_6F_FLD_L1_45, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // reg_sel_foreoff = LEQ for Detecting Calibration Done
    ScalerSetBit(P7A_A9_ADJR_06, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // [6:0] sel_foreoff_autok = 7'b1111111 --> Auto Offset Calibration
    ScalerSetBit(P7A_A3_ADJR_00, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P7A_A4_ADJR_01, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [5/4] LANE_EN = 4'b0000 --> Disable LANE_EN
    // [1/0] CDR_EN = 4'b0000 --> Disable CDR_EN
    ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE0);
    ScalerGDIPhyRx1LanePower(_DISABLE, _DP_SCALER_LANE1);

    switch(g_ucDpPhyRx1CtsCtrl & 0x30)
    {
        case 0x10:

            // Lane1 Test, Enable LANE_EN/CDR_EN for Lane1
            ScalerGDIPhyRx1LanePower(_ENABLE, _DP_SCALER_LANE1);

            break;

        default:
        case 0x00:

            // Lane0 Test, Enable LANE_EN/CDR_EN for Lane0
            ScalerGDIPhyRx1LanePower(_ENABLE, _DP_SCALER_LANE0);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5/4] reg_en_clkout_manual = 1'b0
    // [1/0] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_HBR3);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_HBR2);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x40)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_HBR);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_RBR);
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_UHBR20);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_UHBR13_5);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_UHBR10);
        }
    }

    if(((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0) || (ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE))
    {
        // reg_sel_dfe_delay_tap1 = 0 --> Disable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT1 | _BIT0), 0x00);
    }
    else
    {
        // reg_sel_dfe_delay_tap1 = 1 --> Enable DFE Delay Increase
        ScalerSetBit(PB2_13_RX_TOP_19, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }


    ///////////////////////////////
    // CDR/FLD Parameter Setting //
    ///////////////////////////////

    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx1CtsCtrl & 0xC0)
        {
            case 0xC0:

                ScalerDpPhyRx1APhyFLDSettingFlip2Lane(_DP_LINK_HBR3, enumDpNFCodeRef);

                break;

            case 0x80:

                ScalerDpPhyRx1APhyFLDSettingFlip2Lane(_DP_LINK_HBR2, enumDpNFCodeRef);

                break;

            case 0x40:

                ScalerDpPhyRx1APhyFLDSettingFlip2Lane(_DP_LINK_HBR, enumDpNFCodeRef);

                break;

            default:
            case 0x00:

                ScalerDpPhyRx1APhyFLDSettingFlip2Lane(_DP_LINK_RBR, enumDpNFCodeRef);

                break;
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        switch(g_ucDpPhyRx1CtsCtrl & 0xC0)
        {
            case 0xC0:

                ScalerDpPhyRx1APhyFLDSettingFlip2Lane(_DP_LINK_UHBR20, enumDpNFCodeRef);

                break;

            case 0x80:

                ScalerDpPhyRx1APhyFLDSettingFlip2Lane(_DP_LINK_UHBR13_5, enumDpNFCodeRef);

                break;

            default:
            case 0x40:

                ScalerDpPhyRx1APhyFLDSettingFlip2Lane(_DP_LINK_UHBR10, enumDpNFCodeRef);

                break;
        }
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_25_FLD_L0_35);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Auto FLD
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, _BIT2);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT2, _BIT2);

    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, 0x00);
    ScalerSetBit(PB1_70_FLD_L1_46, ~_BIT5, 0x00);

    // [7:4] reg_fld_rst_n = 4'b0000 --> Reset FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, 0x00);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[2]);

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    //////////////
    // FLD Band //
    //////////////

    // [7:4] reg_fld_rst_n = 4'b0000 --> Enable FLD
    ScalerSetBit(PB1_00_FLD_L0_0, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_40_FLD_L1_0, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }


    //////////////////////
    // FLD Band Restore //
    //////////////////////

    DebugMessageRx1("CTS TP1 L0 Band", ((((WORD)ScalerGetBit(PB1_33_FLD_L0_49, _BIT0)) << 8) | ScalerGetByte(PB1_32_FLD_L0_48)));
    DebugMessageRx1("CTS TP1 L1 Band", ((((WORD)ScalerGetBit(PB1_73_FLD_L1_49, _BIT0)) << 8) | ScalerGetByte(PB1_72_FLD_L1_48)));

    // Write Auto FLD to Manaul FLD
    ScalerSetBit(PB1_15_FLD_L0_21, ~_BIT0, ScalerGetBit(PB1_33_FLD_L0_49, _BIT0));
    ScalerSetBit(PB1_55_FLD_L1_21, ~_BIT0, ScalerGetBit(PB1_73_FLD_L1_49, _BIT0));
    ScalerSetByte(PB1_14_FLD_L0_20, ScalerGetByte(PB1_32_FLD_L0_48));
    ScalerSetByte(PB1_54_FLD_L1_20, ScalerGetByte(PB1_72_FLD_L1_48));

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

    // Disable FLD Auto Mode
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT2, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT2, 0x00);

    ScalerSetBit(PB1_30_FLD_L0_46, ~_BIT5, _BIT5);
    ScalerSetBit(PB1_70_FLD_L1_46, ~_BIT5, _BIT5);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[0]);

    // [5/4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);


    ////////////////////////
    // FLD Target Measure //
    ////////////////////////

    g_pusDpPhyRx1ClockTarget[(g_ucDpPhyRx1CtsCtrl & 0x30) >> 4] = ScalerDpMacDphyRxSignalDetectMeasureCount(enumInputPort, ((g_ucDpPhyRx1CtsCtrl & 0x30) >> 4), _DP_MEASURE_TARGET_RAW_DATA, _DP_MEASURE_PERIOD_1000_CYCLE);
}
#endif

//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp2SetPhy4Lane(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];
    BYTE pucTap0[4];


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7:4] reg_en_clkout_manual = 1'b0
    // [3:0] reg_bypass_clk_rdy = 1'b0
    ScalerSetByte(P7A_97_DATA_TIMER_1, 0x00);

    // [7:4] reg_en_data_manual = 0 --> Disable Data Ready
    // [3:0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetByte(P7A_99_DATA_TIMER_3, 0x0F);


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_HBR3);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_HBR2);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x40)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_HBR);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_RBR);
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_UHBR20);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_UHBR13_5);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitial(_DP_LINK_UHBR10);
        }
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_25_FLD_L0_35);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // [4] reg_cp2adp_en = 1 --> Assert adp_en after cp_en is asserted automatically
    ScalerSetBit(PB1_2F_FLD_L0_45, ~_BIT4, _BIT4);
    ScalerSetBit(PB1_6F_FLD_L1_45, ~_BIT4, _BIT4);
    ScalerSetBit(PB1_AF_FLD_L2_45, ~_BIT4, _BIT4);
    ScalerSetBit(PB1_EF_FLD_L3_45, ~_BIT4, _BIT4);

    if(((g_ucDpPhyRx1CtsCtrl & 0x80) == 0x80) || (ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE))
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[2]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[2]);

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(250);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(250);

    // Disable DFE Adaptation
    ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0x00);

    if(((g_ucDpPhyRx1CtsCtrl & 0xC0) >= 0x80) && (ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE))
    {
        // Read Back Tap0
        ScalerSetByte(PB2_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane2
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[2] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[3] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_A4_L0_INIT_2, 0x1F);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_B4_L1_INIT_2, 0x1F);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[2] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_C4_L2_INIT_2, 0x1F);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_C4_L2_INIT_2, (pucTap0[2] + 6));
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[3] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_D4_L3_INIT_2, 0x1F);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_D4_L3_INIT_2, (pucTap0[3] + 6));
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte(P7A_AB_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AB_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane2
    if((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte(P7A_AD_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AD_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte(PB2_AA_L0_INIT_8, 0x20);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x20);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x20);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x20);

    ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x00);
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x00);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    ///////////////
    // VCO Reset //
    ///////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[1]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[0]);
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7:4] reg_en_data_manual = 4'b1111 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp2SetPhyUnFlip2Lane(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];
    BYTE pucTap0[2];


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [7/6] reg_en_clkout_manual = 1'b0
    // [3/2] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

    // [7/6] reg_en_data_manual = 0 --> Disable Data Ready
    // [3/2] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_HBR3);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_HBR2);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x40)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_HBR);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_RBR);
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_UHBR20);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_UHBR13_5);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitialUnFlip2Lane(_DP_LINK_UHBR10);
        }
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_A5_FLD_L2_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_A5_FLD_L2_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_A5_FLD_L2_35);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // [4] reg_cp2adp_en = 1 --> Assert adp_en after cp_en is asserted automatically
    ScalerSetBit(PB1_AF_FLD_L2_45, ~_BIT4, _BIT4);
    ScalerSetBit(PB1_EF_FLD_L3_45, ~_BIT4, _BIT4);

    if(((g_ucDpPhyRx1CtsCtrl & 0x80) == 0x80) || (ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE))
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[2]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[2]);

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(PB1_B1_FLD_L2_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(PB1_F1_FLD_L3_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(250);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(250);

    // Disable DFE Adaptation
    ScalerSetByte(PB2_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_D1_L3_DFE_EN_2, 0x00);

    if(((g_ucDpPhyRx1CtsCtrl & 0xC0) >= 0x80) && (ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE))
    {
        // Read Back Tap0
        ScalerSetByte(PB2_F0_COEF_1, 0x01);

        // Select to Lane2
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        pucTap0[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane3
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        pucTap0[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_C4_L2_INIT_2, 0x1F);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_C4_L2_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_CA_L2_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_D4_L3_INIT_2, 0x1F);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_D4_L3_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_DA_L3_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane2
    if((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AC_FORE_OFF_TST_L2) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_C3_L2_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane3
    if((ScalerGetByte(P7A_AD_FORE_OFF_TST_L3) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AD_FORE_OFF_TST_L3) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_D3_L3_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte(PB2_CA_L2_INIT_8, 0x20);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x20);

    ScalerSetByte(PB2_CA_L2_INIT_8, 0x00);
    ScalerSetByte(PB2_DA_L3_INIT_8, 0x00);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT2) == 0x00) || (ScalerGetBit(P7A_AC_FORE_OFF_TST_L2, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT3) == 0x00) || (ScalerGetBit(P7A_AD_FORE_OFF_TST_L3, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    ///////////////
    // VCO Reset //
    ///////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_93_FLD_L2_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_D3_FLD_L3_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[1]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_A5_FLD_L2_35, pucIcp[0]);
    ScalerSetByte(PB1_E5_FLD_L3_35, pucIcp[0]);

    // [7/6] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2 for PHY CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPhyRx1PhyCtsTp2SetPhyFlip2Lane(void)
{
    EnumInputPort enumInputPort = ScalerDpPhyRxRxDxMapping(_RX1);
    BYTE pucIcp[3];
    BYTE pucTap0[2];


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [5/4] reg_en_clkout_manual = 1'b0
    // [1/0] reg_bypass_clk_rdy = 1'b0
    ScalerSetBit(P7A_97_DATA_TIMER_1, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

    // [5/4] reg_en_data_manual = 0 --> Disable Data Ready
    // [1/0] reg_bypass_data_rdy = 1 --> Data Ready Manual Mode
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT1 | _BIT0));


    /////////////////////////
    // DFE Initial Setting //
    /////////////////////////

    // DFE Parameter -> Set DFE Initial
    if(ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_HBR3);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_HBR2);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x40)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_HBR);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_RBR);
        }
    }
    else if(ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE)
    {
        if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0xC0)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_UHBR20);
        }
        else if((g_ucDpPhyRx1CtsCtrl & 0xC0) == 0x80)
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_UHBR13_5);
        }
        else
        {
            ScalerDpPhyRx1SetDFEInitialFlip2Lane(_DP_LINK_UHBR10);
        }
    }

    // Backup Icp for CDR lock (2 -> 1 -> 0)
    pucIcp[2] = ScalerGetByte(PB1_25_FLD_L0_35) + 2;
    pucIcp[1] = ScalerGetByte(PB1_25_FLD_L0_35) + 1;
    pucIcp[0] = ScalerGetByte(PB1_25_FLD_L0_35);


    /////////////////////////////////
    // FLD Band and DFE Adaptation //
    /////////////////////////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

    // [4] reg_cp2adp_en = 1 --> Assert adp_en after cp_en is asserted automatically
    ScalerSetBit(PB1_2F_FLD_L0_45, ~_BIT4, _BIT4);
    ScalerSetBit(PB1_6F_FLD_L1_45, ~_BIT4, _BIT4);

    if(((g_ucDpPhyRx1CtsCtrl & 0x80) == 0x80) || (ScalerDpPhyRx1GetPhyCtsForDP20Flag() == _TRUE))
    {
        // Enable LE/Vth/Tap0~Tap4
        ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0xDF);
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0xC7);
    }

    // [4] tap0_notrans = 1'b0 --> Tap0 Effective on Every Bits
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, 0x00);

    // reg_fld_cdr_cp Icp = Max Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[2]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[2]);

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);

    // Delay Time us [0,1000] Waiting for FLD + DFE Adaptation
    for(pData[0] = 0; pData[0] <= 200; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(PB1_31_FLD_L0_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(PB1_71_FLD_L1_47, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT3))))
        {
            break;
        }
    }

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(250);

    // [4] tap0_notrans = 1'b1 --> Tap0 Depends on Run Length
    ScalerSetBit(PB2_F8_GRAY_DEC_2, ~_BIT4, _BIT4);

    // Delay Time us [250,x] Waiting for DFE Adaptation
    DELAY_XUS(250);

    // Disable DFE Adaptation
    ScalerSetByte(PB2_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte(PB2_B1_L1_DFE_EN_2, 0x00);

    if(((g_ucDpPhyRx1CtsCtrl & 0xC0) >= 0x80) && (ScalerDpPhyRx1GetPhyCtsForDP14Flag() == _TRUE))
    {
        // Read Back Tap0
        ScalerSetByte(PB2_F0_COEF_1, 0x01);

        // Select to Lane0
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        pucTap0[0] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        // Select to Lane1
        ScalerSetBit(PB2_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        pucTap0[1] = (ScalerGetByte(PB2_F1_COEF_2) & 0x1F);

        if(pucTap0[0] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_A4_L0_INIT_2, 0x1F);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_A4_L0_INIT_2, (pucTap0[0] + 6));
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_AA_L0_INIT_8, ~_BIT0, 0x00);
        }

        if(pucTap0[1] > 25)
        {
            // Reload Tap0 to 31 (Max)
            ScalerSetByte(PB2_B4_L1_INIT_2, 0x1F);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
        else
        {
            // Reload Tap0 to Adapt + 6 (Max)
            ScalerSetByte(PB2_B4_L1_INIT_2, (pucTap0[1] + 6));
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, _BIT0);
            ScalerSetBit(PB2_BA_L1_INIT_8, ~_BIT0, 0x00);
        }
    }


    /////////////////////
    // Second K Offset //
    /////////////////////

    // Read Back K offset Lane0
    if((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AA_FORE_OFF_TST_L0) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_A3_L0_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Read Back K offset Lane1
    if((ScalerGetByte(P7A_AB_FORE_OFF_TST_L1) & 0x1F) > 24)
    {
        // Set Servo = 24
        ScalerSetBit(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
    }
    else if((ScalerGetByte(P7A_AB_FORE_OFF_TST_L1) & 0x1F) < 8)
    {
        // Set Servo = 8
        ScalerSetBit(PB2_B3_L1_INIT_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }

    // Reload Servo
    ScalerSetByte(PB2_AA_L0_INIT_8, 0x20);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x20);

    ScalerSetByte(PB2_AA_L0_INIT_8, 0x00);
    ScalerSetByte(PB2_BA_L1_INIT_8, 0x00);


    /////////////////////////////
    // DCVS Offset Calibration //
    /////////////////////////////

    // Enable Foreground Calibration
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), 0x00);
    DELAY_5US();
    ScalerSetBit(P7A_A7_ADJR_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [0,500] Waiting for K Offset
    for(pData[0] = 0; pData[0] <= 100; pData[0]++)
    {
        DELAY_5US();

        if(((ScalerGetBit(PB2_00_RX_TOP_00, _BIT0) == 0x00) || (ScalerGetBit(P7A_AA_FORE_OFF_TST_L0, _BIT7) == _BIT7)) &&
           ((ScalerGetBit(PB2_00_RX_TOP_00, _BIT1) == 0x00) || (ScalerGetBit(P7A_AB_FORE_OFF_TST_L1, _BIT7) == _BIT7)))
        {
            break;
        }
    }


    ///////////////
    // VCO Reset //
    ///////////////

    // [7] reg_cp_en_manual = 0 --> CDR Open Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, 0x00);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, 0x00);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // [7] reg_cp_en_manual = 1 --> CDR Close Loop
    ScalerSetBit(PB1_13_FLD_L0_19, ~_BIT7, _BIT7);
    ScalerSetBit(PB1_53_FLD_L1_19, ~_BIT7, _BIT7);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    // reg_fld_cdr_cp Icp = Median Setting for Locking Range
    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[1]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[1]);

    // Delay Time us [25,x] Waiting for VCO Stable
    DELAY_25US();

    ScalerSetByte(PB1_25_FLD_L0_35, pucIcp[0]);
    ScalerSetByte(PB1_65_FLD_L1_35, pucIcp[0]);

    // [5/4] reg_en_data_manual = 2'b11 --> Data from PHY to MAC
    ScalerSetBit(P7A_99_DATA_TIMER_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // DP Mac Clock Select to Link Clock
    ScalerDpMacDphyRxClkSelect(enumInputPort, _DP_MAC_CLOCK_SELECT_LINK_CLOCK);
}
#endif

#endif // End of #if(_DP_PHY_RX1_SUPPORT == _ON)

