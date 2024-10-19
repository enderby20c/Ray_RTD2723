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
// ID Code      : RL6952_Series_DisplayDpTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DisplayDpTx/ScalerDisplayDpTx.h"

#if(_DISPLAY_DP_TX_SUPPORT == _ON)
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
// Description  : DP Tx Power Domain Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxPhyPowerDomainEnable(EnumPowerCut enumPowerCut)
{
    // Vcck off isolation
    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_VBO_EDP_8_LANE, enumPowerCut, _POWER_ON_DELAY_5_MS);
}

//--------------------------------------------------
// Description  : DPTx Display Conversion Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxSetDspcControl(void)
{
    BYTE ucLaneRegNum = 2;

    switch(_PANEL_DPTX_LANE_NUMBER)
    {
        // 1 Port Edptx, 2 Lane
        case _PANEL_DPTX_LANE_NUMBER_1:
        case _PANEL_DPTX_LANE_NUMBER_2:
        case _PANEL_DPTX_LANE_NUMBER_4:
        default:
            ucLaneRegNum = 2;
            break;

        // 2 Port Edptx, 4/8 Lane
        case _PANEL_DPTX_LANE_NUMBER_8:
            if(_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_2_SECTION)
            {
                // 4 Lane
                ucLaneRegNum = 3;
            }
            else // MSO
            {
                // 8 Lane
                ucLaneRegNum = 4;
            }
            break;
    }

    // Set DISP mode is Dp Tx
    ScalerSetBit(P39_00_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Set Line Buffer Access
    ScalerSetBit(P39_27_PANEL_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5), (ucLaneRegNum << 5));

    // Set Panel Section
    ScalerSetBit(P39_27_PANEL_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1), ((_PANEL_DPTX_PANEL_SECTION + 1) << 1));

    // Set Fold Mode & Pixel Mode & Datamux From Front Length
    if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)
    {
        if(_PANEL_DPTX_PANEL_SECTION == _DPTX_PANEL_4_SECTION)
        {
            // 2 port 4 section edptx, MSO
            // 4 Pixel Mode
            ScalerSetBit(P39_28_PANEL_CTRL_2, ~(_BIT7 | _BIT6 | _BIT5), ((ucLaneRegNum - 2) << 5));
            // Fold Enable
            ScalerSetBit(P39_28_PANEL_CTRL_2, ~_BIT4, _BIT4);
            // Set Datamux From Front Length = 4
            ScalerSetBit(P39_29_DATAMUX_CONTROL1, ~(_BIT7 | _BIT6 | _BIT5), ((ucLaneRegNum - 1) << 5));
        }
        else
        {
            // 2 port 2 section edptx
            // 4 Pixel Mode
            ScalerSetBit(P39_28_PANEL_CTRL_2, ~(_BIT7 | _BIT6 | _BIT5), ((ucLaneRegNum - 1) << 5));
            // Fold Disable
            ScalerSetBit(P39_28_PANEL_CTRL_2, ~_BIT4, 0x00);
            // Set Datamux From Front Length
            ScalerSetBit(P39_29_DATAMUX_CONTROL1, ~(_BIT7 | _BIT6 | _BIT5), (ucLaneRegNum << 5));
        }
    }
    else
    {
        // Normal type edptx
        // Set Pixel Mode
        ScalerSetBit(P39_28_PANEL_CTRL_2, ~(_BIT7 | _BIT6 | _BIT5), ((ucLaneRegNum - 1) << 5));
        // Fold Disable
        ScalerSetBit(P39_28_PANEL_CTRL_2, ~_BIT4, 0x00);
        // Set Datamux From Front Length
        ScalerSetBit(P39_29_DATAMUX_CONTROL1, ~(_BIT7 | _BIT6 | _BIT5), (ucLaneRegNum << 5));
    }
}

//--------------------------------------------------
// Description  : Set Display Dp Tx Mac Mapping PHY Mux
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxSetMacToPhyMux(void)
{
    BYTE ucDpTxMacToPhyMux = 0;

    if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)
    {
        if(GET_PANEL_DPTX_PORT_MIRROR() == _ENABLE)
        {
            ucDpTxMacToPhyMux = 0x01;
        }
        else
        {
            ucDpTxMacToPhyMux = 0x04;
        }
    }
    else
    {
        ucDpTxMacToPhyMux = 0x00;
    }

    Scaler32SetByte(PB58050_28_EDP1P4_TX_PORT_SWAP, 0x00, ucDpTxMacToPhyMux);
}

#if(_PANEL_EXIST_MULTIPANEL == _ON)
//--------------------------------------------------
// Description  : Set Display Interface Lane Power
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxPowerSwitch(void)
{
    // Set Dptx Analog PHY Power
    ScalerDisplayDpTxAnalogPhyConrol(_ENABLE);
}
#endif

//--------------------------------------------------
// Description  : Control Vby1 Phy
// Input Value  : bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxAnalogPhyConrol(bit bOn)
{
    // Initial Vby1 Analog PHY for DPTx
    ScalerDisplayDpTxPower(bOn);

    // Initial Vby1 PLL for DPTx
    ScalerDisplayDpTxPLL(bOn);

    // Initial Vby1 Digital PHY for DPTx
    ScalerDisplayDpTxPhy(bOn);

    if(bOn == _ON)
    {
        // Set CMU ckusable mode = HW mode
        Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~_BIT7, 0x00);
    }
    else
    {
        // Set CMU ckusable mode = FW mode
        Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxPhyInitial(void)
{
    // Set DISP mode is Dp Tx
    ScalerDisplayDpTxSetDspcControl();

    // Set Link Clk Source
    Scaler32SetBit(PB58070_54_MAC0_VBY1_LCLK_SOURCE_CTRL_0, ~_BIT0, _BIT0);

    // Set Dptx Digital Phy Initial
    Scaler32SetBit(PB58080_14_PHY0_TXBIST_CTRL0, ~_BIT0, _BIT0);

    // Vcck off isolation
    ScalerDisplayDpTxPhyPowerDomainEnable(_POWER_CUT_OFF);

    // KVCO1
    // KVCO2
    Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28 | _BIT27 | _BIT26 | _BIT25 | _BIT24), (_BIT29 | _BIT28 | _BIT27 | _BIT26));

    // LPF_KVCO
    Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT20 | _BIT19 | _BIT13 | _BIT10 | _BIT9 | _BIT8), (_BIT20 | _BIT19));

    // Set CMU ckusable mode = FW mode
    Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~_BIT7, _BIT7);

    // Initial Z0 for DPTx
    ScalerDisplayDpTxSetZ0();

    // Waiting for PHY initial
    ScalerTimerDelayXms(10);
}

//--------------------------------------------------
// Description  : Dp Tx SSC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxSSCSet(bit bSscEn)
{
    if(bSscEn == _ENABLE)
    {
        WORD usNcode = 0;
        DWORD ulFcode = 0;
        WORD usSSCFreq = 0;
        DWORD ulSSCDownspread = 0;

        usNcode = (WORD)((Scaler32GetByte(PB58050_18_DP1P3_TX_CMU19, 0x01) << 4) | (Scaler32GetByte(PB58050_18_DP1P3_TX_CMU19, 0x02) >> 4));  // N CODE
        ulFcode = (DWORD)(((Scaler32GetByte(PB58050_18_DP1P3_TX_CMU19, 0x02) & 0x0F) << 16) | (Scaler32GetByte(PB58050_18_DP1P3_TX_CMU19, 0x03) << 8) | (Scaler32GetByte(PB58050_1C_DP1P3_TX_CMU23, 0x00))); // F CODE

        // Calculate SSC Frequency = 30~33k
        usSSCFreq = (((_EXT_XTAL / _DISPLAY_DP_TX_SSC_FREQ) + 2) & 0xFFFC);

        // Calculate SSC downspread
        ulSSCDownspread = ((DWORD)(((usNcode + 4) << 20) + ulFcode)) * 16 / 2000 / usSSCFreq / 15 * GET_PANEL_DPTX_SPREAD_RANGE();

        // Set SSC Frequency = 30~33k
        Scaler32SetByte(PB58050_1C_DP1P3_TX_CMU23, 0x02, (BYTE)(usSSCFreq >> 8));
        Scaler32SetByte(PB58050_1C_DP1P3_TX_CMU23, 0x03, (BYTE)(usSSCFreq));

        // Set SSC downspread
        Scaler32SetByte(PB58050_20_DP1P3_TX_CMU27, 0x00, (BYTE)(ulSSCDownspread >> 8));
        Scaler32SetByte(PB58050_20_DP1P3_TX_CMU27, 0x01, (BYTE)(ulSSCDownspread));

        Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT13, _BIT13);
    }
    else
    {
        // Disable SSC
        Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT13, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Digital Phy
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxPhy(bit bOn)
{
    if(bOn == _ON)
    {
        // Set Dp Tx Digital Phy
        Scaler32SetBit(PB58070_00_MAC0_VIDEO_FORMAT_0, ~_BIT4, _BIT4);

        // Enable Digital Phy output
        Scaler32SetDWord(PB58080_1C_PHY0_LANE_ENABLE0, 0x0000FFFF);
    }
    else
    {
        // Disable Digital Phy output
        Scaler32SetDWord(PB58080_1C_PHY0_LANE_ENABLE0, 0x00000000);

        // Reset Dp Tx Digital Phy
        Scaler32SetBit(PB58070_00_MAC0_VIDEO_FORMAT_0, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Z0 Tunning
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxSetZ0(void)
{
    // Set eDPTx Z0 Tx2-Tx3
    Scaler32SetDWord(PB58060_40_DP14_TX_TXTERM_RES_0, 0x02020202);
    Scaler32SetDWord(PB58060_44_DP14_TX_TXTERM_RES_4, 0x02020202);
}

//--------------------------------------------------
// Description  : Dp Tx Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxPower(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up Dptx Digital Block: reg_en
        Scaler32SetBit(PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT31, _BIT31);

        // Power Up Dptx Analog Block
        ScalerDisplayDpTxPhyControl();
    }
    else
    {
        // Power Down Dptx Analog Block
        Scaler32SetDWord(PB58060_70_DP14_TX_POW_SER0, 0x00000000);

        // Power Down Vby1 Digital Block
        Scaler32SetBit(PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT31, 0x00);
    }
}


//--------------------------------------------------
// Description  : Dp Tx Phy Drive Power
// Input Value  : EnumDisplayDpTxOutputPort
// Output Value :
//--------------------------------------------------
void ScalerDisplayDpTxPhyDrivePower(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    // enable Tx main current
    // Power_ckbuf
    if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
    {
        // Port 1
        Scaler32SetBit(PB58060_00_DP14_TX_IB_DRV_EN0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        Scaler32SetBit(PB58060_0C_DP14_TX_POW_CKBUF0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
    {
        // Port 2
        Scaler32SetBit(PB58060_00_DP14_TX_IB_DRV_EN0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        Scaler32SetBit(PB58060_0C_DP14_TX_POW_CKBUF0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    }

    // DPTX power on TX driver
    switch(GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort))
    {
        case _DP_ONE_LANE: // VTX Lane0

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                // Power Serializer power control
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                // Power Serializer power control
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
            }

            break;

        case _DP_TWO_LANE: // VTX Lane0~1

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                // Power Serializer power control
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                // Power Serializer power control
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
            }
            break;

        case _DP_FOUR_LANE: // VTX Lane0~3

            if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_1)
            {
                // Power Serializer power control
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            }
            else if(enumDisplayDpTxOutputPort == _DISPLAY_DP_TX_PORT_2)
            {
                // Power Serializer power control
                Scaler32SetBit(PB58060_70_DP14_TX_POW_SER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            }
            break;

        default:
            break;
    }
}
#endif // End of #if(_DISPLAY_DP_TX_SUPPORT == _ON)

