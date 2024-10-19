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
// ID Code      : RL6952_Series_DisplayVboTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DisplayVboTx/ScalerDisplayVboTx.h"

#if(_PANEL_STYLE == _PANEL_VBO)
//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tDISPLAY_VBO_DRV_TABLE[32] =
{
    // Pre-emphasis->         0              1                2              3
    // VoltageSwing
    /*    0    */        0x1A, 0x00,     0x14, 0x03,     0x0D, 0x07,     0x02, 0x0C,
    /*    1    */        0x14, 0x00,     0x0D, 0x03,     0x09, 0x05,     0x02, 0x09,
    /*    2    */        0x09, 0x00,     0x02, 0x02,     0x02, 0x04,     0x02, 0x06,
    /*    3    */        0x02, 0x00,     0x02, 0x03,     0x02, 0x05,     0x02, 0x07,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Settings for Vbyone Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxInitialTable(void)
{
    // Set Vby1 Display Conversion Control
    ScalerDisplayVboTxSetDspcControl();

    // Vcck off Analog/Digital 1.0 Power
    ScalerDisplayVboTxPhyPowerDomainEnable(_POWER_CUT_OFF);

    // KVCO1/ KVCO2
    Scaler32SetBit(PB58050_04_DP14_TX_CMU4, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28 | _BIT27 | _BIT26 | _BIT25 | _BIT24), (_BIT29 | _BIT28 | _BIT27 | _BIT26));

    // LPF_KVCO
    Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT20 | _BIT19 | _BIT13 | _BIT10 | _BIT9 | _BIT8), (_BIT20 | _BIT19));

    // Select the Source of VBY1 eDP Combo TX from VBY1
    Scaler32SetBit(PB58050_08_DP14_TX_CMU8, ~_BIT16, _BIT16);

#if(_PANEL_VBO_LANE_SKEW_RESET_TYPE == _VBO_LANE_SKEW_RESET_BY_CK_USABLE)
    // Set CMU ckusable mode = FW mode
    Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~_BIT7, _BIT7);
#endif

    ScalerDisplayVboTxXInitialTable(_VBO_TX_PORT_0);

    // LOCKN Pin Connect Detect
    g_stDisplayVboTxInfo.b1VboLocknPinDetect = _FALSE;

    // LOCKN Ripped off status initial: False
    g_stDisplayVboTxInfo.b1VboLocknRippedOff = _FALSE;

    // Set Panel Fast Off Disable
    g_stDisplayVboTxInfo.b1PanelFastOffStatus = _DISABLE;
}

//--------------------------------------------------
// Description  : Control Vby1 Phy
// Input Value  : bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxPhyControl(bit bEnable)
{
    // LOCKN Pin Connect Detect
    if(ScalerDisplayVboTxGetLocknVoltageLevel() == _HIGH)
    {
        g_stDisplayVboTxInfo.b1VboLocknPinDetect = _TRUE;
    }

    if(bEnable == _ENABLE)
    {
#if(_PANEL_VBO_LANE_SKEW_RESET_TYPE == _VBO_LANE_SKEW_RESET_BY_CMU_POWER)

        EnumGlobalLineBufferFifoWDIrqStatus enumWDIrqbackup = ScalerGlobalGetFrameSyncLinebufferFifoWatchDogStatus();

        if(enumWDIrqbackup != _FRAME_BUFFER_NO_NEED_TO_CHK)
        {
            ScalerGlobalSetFrameSyncLinebufferFifoWDIrq(enumWDIrqbackup, _DISABLE);
        }

        ScalerDisplayVboTxXAPhyControl(_VBO_TX_PORT_0, _ENABLE);

        // Power Down DPLL
        ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, _BIT0);

        // Power Down VBO Tx CMU
        Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT15 | _BIT13 | _BIT10 | _BIT9 | _BIT8), 0x00);

        ScalerDisplayVboTxXDPhyControl(_VBO_TX_PORT_0, _ENABLE);

        // Power On VBO Tx CMU
        Scaler32SetBit(PB58050_00_DP14_TX_CMU0, ~(_BIT15 | _BIT13 | _BIT10 | _BIT9 | _BIT8), _BIT15);

        // Power On DPLL
        ScalerSetBit(P1_D1_DPLL_ANALOG_SETTING_1, ~_BIT0, 0x00);

        if(enumWDIrqbackup != _FRAME_BUFFER_NO_NEED_TO_CHK)
        {
            ScalerGlobalSetFrameSyncLinebufferFifoWDIrq(enumWDIrqbackup, _ENABLE);
        }

        // Enable Vby1 sclk
        Scaler32SetBit(PB58030_00_VBY1_EDPTX_CLOCK_GEN, ~_BIT6, _BIT6);

#else // Else of #if(_PANEL_VBO_LANE_SKEW_RESET_TYPE == _VBO_LANE_SKEW_RESET_BY_CMU_POWER)

        ScalerDisplayVboTxXAPhyControl(_VBO_TX_PORT_0, _ENABLE);

        ScalerDisplayVboTxXDPhyControl(_VBO_TX_PORT_0, _ENABLE);

        // Enable Vby1 sclk
        Scaler32SetBit(PB58030_00_VBY1_EDPTX_CLOCK_GEN, ~_BIT6, _BIT6);

        // Set CMU ckusable mode = HW mode
        Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~_BIT7, 0x00);

#endif
    }
    else
    {
#if(_PANEL_VBO_LANE_SKEW_RESET_TYPE == _VBO_LANE_SKEW_RESET_BY_CK_USABLE)
        // Set CMU ckusable mode = FW mode
        Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~_BIT7, _BIT7);
#endif

        // Disable Vby1 sclk
        Scaler32SetBit(PB58030_00_VBY1_EDPTX_CLOCK_GEN, ~_BIT6, 0x00);

        ScalerDisplayVboTxXDPhyControl(_VBO_TX_PORT_0, _DISABLE);

        ScalerDisplayVboTxXAPhyControl(_VBO_TX_PORT_0, _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Adjust Vbo Ref DPLL Spread Spectrum
// Input Value  : bDclkSpreadSpeed, ucSpreadRange
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxSetPllSsc(bit bDclkSpreadSpeed, BYTE ucSpreadRange)
{
    WORD usNcode = 0;
    DWORD ulFcode = 0;
    WORD usSscgFreq = 0;
    WORD usSscgRange = 0;

    bDclkSpreadSpeed = bDclkSpreadSpeed;

    if(ucSpreadRange != 0x00)
    {
        usNcode = (WORD)ScalerDisplayVboTxGetNFCode(_DISPLAY_VBO_CMU_N_CODE);
        ulFcode = ScalerDisplayVboTxGetNFCode(_DISPLAY_VBO_CMU_F_CODE);

#if(_PANEL_VBO_SPREAD_SPEED == _SPEED_27K)
        {
            // Calculate Spread Spectrum FMDIV: 27kHz
            usSscgFreq = (((_EXT_XTAL / 28) + 2) & 0xFFFC);
        }
#else
        {
            // Calculate Spread Spectrum FMDIV: 30kHz
            usSscgFreq = (((_EXT_XTAL / 31) + 2) & 0xFFFC);
        }
#endif
        // Calculate SSC
        usSscgRange = ((((DWORD)usNcode + 4) * 4096 + ulFcode)) * 16 / 100 / usSscgFreq / 15 * ucSpreadRange;

        // Set Spread Spectrum FMDIV: 30kHz
        Scaler32SetByte(PB58050_1C_DP1P3_TX_CMU23, 0x02, HIBYTE(usSscgFreq));
        Scaler32SetByte(PB58050_1C_DP1P3_TX_CMU23, 0x03, LOBYTE(usSscgFreq));

        // Set Spread Spectrum Range
        Scaler32SetByte(PB58050_20_DP1P3_TX_CMU27, 0x00, HIBYTE(usSscgRange));
        Scaler32SetByte(PB58050_20_DP1P3_TX_CMU27, 0x01, LOBYTE(usSscgRange));

        // [5] 1: Enable SSC, 0: disable
        // [4] 0: 1st Order SDM, 1:2nd Order SDM
        // [3] 0: Triangular wave, 1: Square wave
        Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT13, _BIT13);
    }
    else
    {
        // Disable SSC
        Scaler32SetBit(PB58050_10_DP1P3_TX_CMU11, ~_BIT13, 0x00);
    }
}

//--------------------------------------------------
// Description  : Vbo TX Power Domain Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxPhyPowerDomainEnable(EnumPowerCut enumPowerCut)
{
    // Vcck off isolation
    ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_VBO_EDP_8_LANE, enumPowerCut, _POWER_ON_DELAY_5_MS);
}

//--------------------------------------------------
// Description  : Set Vby1 DisplayConversion Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxSetDspcControl(void)
{
    BYTE ucPortRegNum = 0;
    BYTE ucSectionRegNum = 0;
    BYTE ucPixelModeRegNum = 0;

    switch(_PANEL_VBO_OUTPUT_PORT)
    {
        case _VBO_1_DATA_LANE:
            ucPortRegNum = 1;
            ucPixelModeRegNum = 0; // 1 pixel mode
            break;

        case _VBO_2_DATA_LANE:
            ucPortRegNum = 2;
            ucPixelModeRegNum = 0; // 1 pixel mode
            break;

        case _VBO_4_DATA_LANE:
            ucPortRegNum = 3;
            ucPixelModeRegNum = 1; // 2 pixel mode
            break;

        case _VBO_8_DATA_LANE:
            ucPortRegNum = 4;
            ucPixelModeRegNum = 1; // 2 pixel mode
            break;

        default:
            break;
    }

    switch(_PANEL_VBO_PANEL_SECTION)
    {
        case _VBO_PANEL_1_SECTION:
            ucSectionRegNum = 1;
            break;

        case _VBO_PANEL_2_SECTION:
            ucSectionRegNum = 2;
            break;

        case _VBO_PANEL_4_SECTION:
            ucSectionRegNum = 3;
            break;

        case _VBO_PANEL_8_SECTION:
            ucSectionRegNum = 4;
            break;

        default:
            break;
    }

    // Set Display Type
    ScalerSetBit(P39_00_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Set Line Buffer Access
    ScalerSetBit(P39_27_PANEL_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5), (ucPortRegNum << 5));

    // Set Section
    ScalerSetBit(P39_27_PANEL_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1), (ucSectionRegNum << 1));

    // Set Pixel Mode
    ScalerSetBit(P39_28_PANEL_CTRL_2, ~(_BIT7 | _BIT6 | _BIT5), (ucPixelModeRegNum << 5));

    // Set Fold Disable
    ScalerSetBit(P39_28_PANEL_CTRL_2, ~_BIT4, 0x00);

    // Set Datamux From Front Length
    ScalerSetBit(P39_29_DATAMUX_CONTROL1, ~(_BIT7 | _BIT6 | _BIT5), (ucPortRegNum << 5));
}

//--------------------------------------------------
// Description  : Setting for Vbyone driving control
// Input Value  : Driving current and Pre-emphasis for Vby1 Data Lane
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXDrivingControl(BYTE ucDrvLane, BYTE ucEmpLane)
{
    ucDrvLane = ucDrvLane;
    ucEmpLane = ucEmpLane;

    BYTE ucIndex = 0x00;
    BYTE *pucTable = 0x00;

    ucIndex = (ucDrvLane * 4 + ucEmpLane) * 2;

    pucTable = tDISPLAY_VBO_DRV_TABLE;

    // enable main
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_00_DP14_TX_IB_DRV_EN0, 0x00, 0xFF);

    // enable post
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_04_DP14_TX_EM_EN0, 0x00, 0xFF);

    // main swing
    // lane0~lane3
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_10_DP14_TX_IB_DRV_CH0, 0x00, (pucTable[ucIndex + 0]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_10_DP14_TX_IB_DRV_CH0, 0x01, (pucTable[ucIndex + 0]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_10_DP14_TX_IB_DRV_CH0, 0x02, (pucTable[ucIndex + 0]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_10_DP14_TX_IB_DRV_CH0, 0x03, (pucTable[ucIndex + 0]));

    // lane4~lane7
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_14_DP14_TX_IB_DRV_CH4, 0x00, (pucTable[ucIndex + 0]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_14_DP14_TX_IB_DRV_CH4, 0x01, (pucTable[ucIndex + 0]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_14_DP14_TX_IB_DRV_CH4, 0x02, (pucTable[ucIndex + 0]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_14_DP14_TX_IB_DRV_CH4, 0x03, (pucTable[ucIndex + 0]));

    // post preemphasis
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_20_DP14_TX_EM_DRV_CH0, 0x00, (pucTable[ucIndex + 1]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_20_DP14_TX_EM_DRV_CH0, 0x01, (pucTable[ucIndex + 1]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_20_DP14_TX_EM_DRV_CH0, 0x02, (pucTable[ucIndex + 1]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_20_DP14_TX_EM_DRV_CH0, 0x03, (pucTable[ucIndex + 1]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_24_DP14_TX_EM_DRV_CH4, 0x00, (pucTable[ucIndex + 1]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_24_DP14_TX_EM_DRV_CH4, 0x01, (pucTable[ucIndex + 1]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_24_DP14_TX_EM_DRV_CH4, 0x02, (pucTable[ucIndex + 1]));
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_24_DP14_TX_EM_DRV_CH4, 0x03, (pucTable[ucIndex + 1]));
}

//--------------------------------------------------
// Description  : Vbyone Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXPower(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up Vby1 Digital Block: reg_en
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT31, _BIT31);

        // Power Up Vby1 Analog Block
        if(_PANEL_VBO_OUTPUT_PORT == _VBO_1_DATA_LANE)
        {
            // Lane0: LDO Power, Clock Buffer Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_0C_DP14_TX_POW_CKBUF0, 0x00800001);

            // Lane0: Serializer Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x00000001);

            // Lane0: Driver Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x00010001);
        }
        else if(_PANEL_VBO_OUTPUT_PORT == _VBO_2_DATA_LANE)
        {
            // Lane0~1: LDO Power, Clock Buffer Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_0C_DP14_TX_POW_CKBUF0, 0x00800003);

            // Lane0~1: Serializer Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x00000003);

            // Lane0~1: Driver Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x00030003);
        }
        else if(_PANEL_VBO_OUTPUT_PORT == _VBO_4_DATA_LANE)
        {
            // Lane0~3: LDO Power, Clock Buffer Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_0C_DP14_TX_POW_CKBUF0, 0x0080000F);

            // Lane0~3: Serializer Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x0000000F);

            // Lane0~3: Driver Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x000F000F);
        }
        else if(_PANEL_VBO_OUTPUT_PORT == _VBO_8_DATA_LANE)
        {
            // Lane0~7: LDO Power, Clock Buffer Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_0C_DP14_TX_POW_CKBUF0, 0x008000FF);

            // Lane0~7: Serializer Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x000000FF);

            // Lane0~7: Driver Power on
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x00FF00FF);
        }
    }
    else
    {
        // Power Down Vby1 Analog Block

        // Disable LDO Power, Clock Buffer Power
        SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_0C_DP14_TX_POW_CKBUF0, 0x00000000);

        // Disable Serializer Power, Driver Power
        SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x00000000);

        // Lane0~7: power off
        SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_70_DP14_TX_POW_SER0, 0x00, 0x00);

        // Power Down Vby1 Digital Block
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT31, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get Vbo N.F Code
// Input Value  : enumDisplayVboTxCmuInfo
// Output Value : N.F Code
//--------------------------------------------------
DWORD ScalerDisplayVboTxGetNFCode(EnumDisplayVboTxCmuInfo enumDisplayVboTxCmuInfo)
{
    WORD usNcode = 0;
    DWORD ulFcode = 0;
    DWORD ulNFcode = 0;
    usNcode = (WORD)((Scaler32GetByte(PB58050_18_DP1P3_TX_CMU19, 0x01) << 4) | (Scaler32GetByte(PB58050_18_DP1P3_TX_CMU19, 0x02) >> 4));
    ulFcode = (DWORD)(((Scaler32GetByte(PB58050_18_DP1P3_TX_CMU19, 0x02) & 0x0F) << 16) | (Scaler32GetByte(PB58050_18_DP1P3_TX_CMU19, 0x03) << 8) | (Scaler32GetByte(PB58050_1C_DP1P3_TX_CMU23, 0x00))); // F CODE

    // Get current (N code + 4) * 2^20 + F code
    ulNFcode = (((DWORD)usNcode + 4) * 1048576) + ulFcode;

    if(enumDisplayVboTxCmuInfo == _DISPLAY_VBO_CMU_N_CODE)
    {
        return usNcode;
    }
    else if(enumDisplayVboTxCmuInfo == _DISPLAY_VBO_CMU_F_CODE)
    {
        return ulFcode;
    }
    else
    {
        return ulNFcode;
    }
}
#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)

