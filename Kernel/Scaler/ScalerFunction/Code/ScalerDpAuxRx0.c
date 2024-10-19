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
// ID Code      : ScalerDpAuxRx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPAUXRX0__

#include "ScalerFunctionInclude.h"
#include "DpAuxRx0/ScalerDpAuxRx0.h"


#if(_DP_AUX_RX0_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile bit g_bDpAuxRx0CommandNoReply = _FALSE;
DWORD g_ulDpAuxRx0Backup_EXINT0;
DWORD g_ulDpAuxRx0Backup_WDINT;
volatile StructDpAuxRxDpcdUpdateProtect g_stDpAuxRx0DpcdUpdateProtect;
volatile StructDpAuxRxDpcdUpdateProtect g_stDpAuxRx0DpcdUpdateProtect_WDINT;
bit g_bDpAuxRx0SourceRDErrorCount = _FALSE;
volatile BYTE g_ucDpAuxRx0LTStatus = _DP_LINK_TRAINING_NONE;
bit g_bDpAuxRx0Info;
BYTE g_pucDpAuxRx0LinkStatusBackup_INT[3];
bit g_bDpAuxRx0Tp1Initial = _FALSE;
BYTE g_ucDpAuxRx0LinkStatus01;
BYTE g_ucDpAuxRx0LinkStatus23;
BYTE g_ucDpAuxRx0LinkRequest01;
BYTE g_ucDpAuxRx0LinkRequest23;
BYTE g_ucDpAuxRx0PreferPreset;
bit g_bDpAuxRx0FakeLT;

#if(_DP_LT_TP2_RETRY_FOR_S2P1_S3P0 == _ON)
BYTE g_pucDpAuxRx0MaxSwing[4];
#endif

volatile EnumDpLinkRate g_enumDpAuxRx0LinkRate;
volatile EnumDpLaneCount g_enumDpAuxRx0LaneCount;
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
volatile EnumDpLinkChannelCodingType g_enumDpAuxRx0CodingType;
#endif
BYTE g_ucDpAuxRx0TrainingPatternSet;

BYTE g_ucDpAuxRx0LTPatternSet;
bit g_bDpAuxRx0HpdLowResetFlag;
EnumDpVersionType g_enumDpAuxRx0CurrentVersion;
EnumDpAuxRxModeStatus g_enumDpAuxRx0ModeBackup_EXINT0 = _DP_RX_AUX_AUTO_MODE;
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
volatile bit g_bDpAuxRx0IntProtect = _FALSE;
#endif

volatile StructDpRxAuxPowerInfo g_stDpAuxRx0PowerInfo;

volatile bit g_bDpAuxRx0MSTBackupLinkStatusFlg_INT;

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
volatile bit g_bDpAuxRx0HpdIrqAssertT2Event;
EnumDpAuxRxModeStatus g_enumDpAuxRx0AutoModeBackup_T2INT;
#endif

#if((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_SPECIFIC_SOURCE_OUI == _ON) || ((_DP_LT_TP1_PERMIT_SWING_LEVEL_0_FOR_TBT == _ON) && (_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TBT)))
BYTE g_ucDpAuxRx0Tp1PermitSwingLevel0;
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
bit g_bDpAuxRx0PRModeCrcEnableFlag;
#endif

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
BYTE g_ucDpAuxRx0PVth;
BYTE g_ucDpAuxRx0NVth;
#endif

EnumDpAuxReceiveMode g_enumDpAuxRx0ReceiveMode = _AUX_DIFF_MODE;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
volatile StructDpAuxRxReceiveBackup g_stDpAuxRx0ReceiveBackup;
#if(_DP_HDCP_2_2_SUPPORT == _ON)
volatile WORD g_usDpAuxRx0StreamIdAddrEnd;
#endif
#if(_DP_RX_FEC_SUPPORT == _ON)
volatile bit g_bDpAuxRx0FecStatusW1cProtect = _DISABLE;
#endif
#endif

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
BYTE g_ucDpAuxRx0AccessBackup_EXINT0;
BYTE g_ucDpAuxRx0AccessBackup_WDINT;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Setting for DP AUX
// Input Value  : enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumDisplayMode, enumFreeSyncSupport
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0Initial(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Aux New Mac Enable
    Scaler32SetBit(PB18006_00_AUX_MAC_CTRL, ~_BIT0, _BIT0);
#endif

    // Clr Aux Dpcd Update Protect Flag
    CLR_DP_AUX_RX0_DPCD_UPDATE_PROTECT();
    CLR_DP_AUX_RX0_DPCD_UPDATE_PROTECT_WDINT();

    // Aux Power on Initial Setting
    ScalerDpAuxRx0PowerOnInitial();

    ScalerDpAuxRx0AuxSet();

    ScalerDpAuxRx0DpcdInitial();

    // Must be initialized "AFTER DPCD setting" to avoid entering interruption unexpectively
    ScalerDpAuxRx0AuxIntInitial();

    SET_DP_AUX_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    CLR_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE();
    CLR_DP_AUX_RX0_CHECK_CH_POWER_STATUS();
    CLR_DP_AUX_RX0_CH_POWER_ON_WAKE_UP();
    CLR_DP_AUX_RX0_SOURCE_FIRST_POWER_ON();
    CLR_DP_AUX_RX0_SOURCE_WRITE_POWER_UP();
}

//--------------------------------------------------
// Description  : Initial Setting for DP Digital Aux, Analog Aux, Aux INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0AuxIntInitial(void)
{
    // Aux IRQ Initial Setting
    ScalerDpAuxRx0DpcdAddrIrqInitial();

    // I2c slave addr 50 Interrupt
    Scaler32SetByte(_REG_DP_AUX_RX0_IIC_CTRL0, 0x01, 0xA1);

    // Enable INT0
    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _ENABLE);
}

//-------------------------------------------------------
// Description  : Aux Power on Initial Setting
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx0PowerOnInitial(void)
{
    BYTE ucConnectorType = ScalerDpRxGetConnectorType(ScalerDpAuxRxRxDxMapping(_RX0));

    if(ucConnectorType == _DP_CONNECTOR_EMBEDDED)
    {
        // Reset Aux Phy
        Scaler32SetBit(PB18000_14_AUX_5, ~_BIT7, 0x00);
    }

    // Aux_timeout setting
    Scaler32SetByte(_REG_DP_AUX_RX0_TX_TIMER, 0x01, _DP_AUX_REPLY_TIMEOUT_USER_SETTING);

    // Average 8 cycles as Start Postion, Aux Clk Select to 27MHz
    Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~(_BIT(15, 11)), (_BIT15 | _BIT14));

#if(_DP_AUX_REPLY_CLK_SEL_FROM == _DP_AUX_REPLY_SEL_IOSC)
    // Aux Clk Select Manual Mode, Aux New Mode
    Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~(_BIT23 | _BIT22), _BIT22);
#else
    // Aux Clk Select Source, Aux New Mode
    Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~(_BIT23 | _BIT22), (_BIT23 | _BIT22));
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    // HW Fake Link Training Disable.
    Scaler32SetBit(PB18002_28_FAKE_LT, ~_BIT4, 0x00);
#endif

    // Set Aux Precharge Number.
    Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~(_BIT28 | _BIT27 | _BIT26 | _BIT25 | _BIT24), (_BIT27 | _BIT24));

    // Aux Auto Mode, Using Default Average Number.
    Scaler32SetByte(PB18001_04_AUX_DIG_PHY, 0x00, 0x0D);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Enable Dpcd/Remap Sram.
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~(_BIT23 | _BIT22), (_BIT23 | _BIT22));
#else
    // Enable Hdcp 2.2/Remap Sram.
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT22, _BIT22);
#endif

    // Enable Aux Channel & Force Defer New Mode
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~(_BIT21 | _BIT19 | _BIT16), (_BIT21 | _BIT16));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    // Disable Auto LT Process
    Scaler32SetBit(PB18002_28_FAKE_LT, ~_BIT5, 0x00);
#endif

    // Fast IIC Clock.
    Scaler32SetBit(_REG_DP_AUX_RX0_IIC_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_AUX_IIC_SCL_CLK_SETTING << 4));

    // Set aux mac clk use xclk
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT3, _BIT3);

    // Not Reply when Aux Error.
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~(_BIT13 | _BIT12), _BIT12);

    // Sync Count Rounding
    Scaler32SetBit(PB18001_04_AUX_DIG_PHY, ~(_BIT15 | _BIT14), _BIT14);

    // Disable other DPCD, Aux Timeout, Receiving Aux INT.
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~(_BIT25 | _BIT24), 0x00);

    // Disable Aux Phy Int
    Scaler32SetBit(PB18001_08_AUX_IRQ_EN, ~_BIT7, 0x00);

    // Aux Ack Timer & Tx_Start_Miss_Protect
    Scaler32SetBit(_REG_DP_AUX_RX0_TX_TIMER, ~(_BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT0));

    // I2C timeout setting
    Scaler32SetByte(_REG_DP_AUX_RX0_TX_TIMER, 0x02, _DP_AUX_I2C_REPLY_TIMEOUT_SETTING);

    // Disable Reply IIC Defer Before Data Ready.
    Scaler32SetBit(_REG_DP_AUX_RX0_IIC_CTRL0, ~(_BIT22 | _BIT21), 0x00);

    // Enable Aux Error Handler.
    Scaler32SetBit(PB18001_04_AUX_DIG_PHY, ~(_BIT30 | _BIT29 | _BIT28), (_BIT29 | _BIT28));
    Scaler32SetBit(PB18001_08_AUX_IRQ_EN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if(ucConnectorType != _DP_CONNECTOR_EMBEDDED)
    {
        // Toggle Aux Auto K
        Scaler32SetBit(PB18000_14_AUX_5, ~_BIT7, 0x00);
        Scaler32SetBit(PB18000_14_AUX_5, ~_BIT7, _BIT7);
    }

    // Clear the Clock Divider for AUX MAC and PHY
    Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~(_BIT19 | _BIT18 | _BIT17 | _BIT16), 0x00);
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~(_BIT11 | _BIT10 | _BIT9 | _BIT8), 0x00);

    // Aux Source Clock Setting
    ScalerDpAuxRx0SourceClkSet();

    // Set the Clock Divider = 1 for AUX MAC and PHY
    Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~(_BIT19 | _BIT18 | _BIT17 | _BIT16), _BIT16);
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~(_BIT11 | _BIT10 | _BIT9 | _BIT8), _BIT8);

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
    ScalerDpAuxRx0AutoCalibration();
#endif

    // Set Aux Rx, Swing, Vth, z0
    ScalerDpAuxRx0AuxSet();

    // Enable Aux 50/50 Duty, Talk Mode High Period and Low Period Will Keep The Same of 1M Counter
    Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT10, _BIT10);

    // Set 1M Count = 28, 50/50 Duty Enable, The High Period and Low Period are The Same = 14 (28M / 28 = 1MHz)
    Scaler32SetByte(PB18001_00_AUX_DIG_PHY, 0x00, 0x1C);

    // Digital Aux Power On, DPCD REG Power On, MSG Power On.
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT1), 0x00);

    // Disable Dpcd Access Auto Inc
    ScalerDpAuxRx0DpcdAutoIncEnable(_DISABLE);

    // Set end to idle trigger Aux Int Flag
    Scaler32SetBit(PB18001_08_AUX_IRQ_EN, ~(_BIT11 | _BIT10 | _BIT9), (_BIT11 | _BIT9));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Disable HW Aux Mode Protect / Set Dpcd Db Mode
    Scaler32SetBit(PB18006_00_AUX_MAC_CTRL, ~(_BIT29 | _BIT28), 0x00);
#endif
}

//-------------------------------------------------------
// Description  : Set Aux Diff mode or Single-eneded mode
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx0AuxSet(void)
{
#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
    BYTE ucPVTH = 0;
    BYTE ucNVTH = 0;

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    if((Scaler32GetByte(PB18000_24_AUX_REV_0, 0x00) & _BIT0) == _BIT0)
    {
        ucPVTH = g_ucDpAuxRx0NVth;
        ucNVTH = g_ucDpAuxRx0PVth;
    }
    else
#endif
    {
        ucPVTH = g_ucDpAuxRx0PVth;
        ucNVTH = g_ucDpAuxRx0NVth;
    }
#else
#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    if((Scaler32GetByte(PB18000_24_AUX_REV_0, 0x00) & _BIT0) == _BIT0)
    {
        ucPVTH = 0;
        ucNVTH = _DP_AUX_AUTO_CALIBRATION_VTH;
    }
    else
#endif
    {
        ucPVTH = _DP_AUX_AUTO_CALIBRATION_VTH;
        ucNVTH = 0;
    }
#endif
#endif

    // Set Aux Tx LDO = _DP_RX_AUX_REPLY_SWING_LEVEL
    Scaler32SetBit(PB18000_14_AUX_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_RX_AUX_REPLY_SWING_LEVEL);

    // Rx Vcom = 0.5V
    Scaler32SetBit(PB18000_10_AUX_4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
    // Reserved For User Adjust
    if(GET_DP_AUX_DIFF_MODE() == _FALSE)
    {
        // Enable Single-Ended Mode
        Scaler32SetBit(PB18000_08_AUX_2, ~_BIT5, _BIT5);

        // Vth = 50mV
#if(_HW_DP_AUX_SINGLE_END_GEN == _DP_AUX_SINGLE_END_ONLY)
        Scaler32SetBit(PB18000_00_DIG_TX_04, ~(_BIT1 | _BIT0), _BIT0);
#elif(_HW_DP_AUX_SINGLE_END_GEN == _DP_AUX_SINGLE_END_COMBO_RX2)
        Scaler32SetBit(PB18000_00_DIG_TX_04, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
#endif

        // Open ADJR_P
        Scaler32SetBit(PB18000_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Open ADJR_N
        Scaler32SetBit(PB18000_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
#endif
    {
        switch(GET_DP_AUX_RX0_RECEIVE_MODE())
        {
            case _AUX_PN_SWAP_MODE:
                // Enable Aux DPHY Swap
                Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, _BIT8);

                // aux_inv = 0
                Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT21, 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
                // Disable Single-Ended Mode
                Scaler32SetBit(PB18000_08_AUX_2, ~_BIT5, 0x00);
#endif

#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_ONLY)
                // Vth = 75mV
                Scaler32SetDWord(PB18000_24_AUX_REV_0, (_BIT2 | _BIT1));
#elif(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
                // Set Vth = 75mV + Offset, |(Bit12:8 - Bit20:16)*5| = Vth
                Scaler32SetDWord(PB18001_38_AUXCH_DIG_TEST_SEL, TO_DWORD(0, ucNVTH, ucPVTH, 0));
#endif

                // Set Aux Listen Mode ADJR_P, default = 66Ohm
                Scaler32SetBit(PB18000_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

                // Set Aux Listen Mode ADJR_N, default = 66Ohm
                Scaler32SetBit(PB18000_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

                // Set Aux Talk Mode ADJR
                Scaler32SetByte(PB18000_3C_DIG_TX_03_2, 0x00, 0x17);
                Scaler32SetByte(PB18000_1C_DIG_TX_03_1, 0x00, 0x17);

                break;
            case _AUX_DIFF_MODE:
            default:
                // Disable Aux DPHY Swap
                Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

                // aux_inv = 0
                Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT21, 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
                // Disable Single-Ended Mode
                Scaler32SetBit(PB18000_08_AUX_2, ~_BIT5, 0x00);
#endif

#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_ONLY)
                // Vth = 75mV
                Scaler32SetDWord(PB18000_24_AUX_REV_0, (_BIT2 | _BIT1));
#elif(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
                // Set Vth = 75mV + Offset, |(Bit12:8 - Bit20:16)*5| = Vth
                Scaler32SetDWord(PB18001_38_AUXCH_DIG_TEST_SEL, TO_DWORD(0, ucNVTH, ucPVTH, 0));
#endif

                // Set Aux Listen Mode ADJR_P, default = 66Ohm
                Scaler32SetBit(PB18000_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

                // Set Aux Listen Mode ADJR_N, default = 66Ohm
                Scaler32SetBit(PB18000_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_AUX_ADJR_SETTING());

                // Set Aux Talk Mode ADJR
                Scaler32SetByte(PB18000_3C_DIG_TX_03_2, 0x00, 0x17);
                Scaler32SetByte(PB18000_1C_DIG_TX_03_1, 0x00, 0x17);

                break;
        }
    }
}

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
//-------------------------------------------------------
// Description  : Aux Rx Auto Calibration offset
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx0AutoCalibration(void)
{
    EnumDpAuxRxAutoKState enumDpAuxRxAutoKState = _AUTO_CALIBRATION_INIT;
    BYTE ucDpAuxRxPVthBackup = 0;
    BYTE ucDpAuxRxNVthBackup = 0;
    BYTE ucDpAuxRxPVthBackup2 = 0;
    BYTE ucDpAuxRxNVthBackup2 = 0;
    BYTE ucTimeout = 0;
    BYTE ucAutoCalibrationCount = 0;

    // variable values may vary for experimental purposes and should not be treated as constants.
    // coverity[assignment]
    BYTE ucDpAuxRxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;

    // coverity[assignment]
    BYTE ucDpAuxRxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;

    // debsp_time = Value/Dphy Clk ~ 100ns
    Scaler32SetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x03, 0x03);

#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    Scaler32SetBit(PB18000_18_AUX_6, ~_BIT6, _BIT6);
#endif

    // Set autok_toggle_num = 3(Bit31:29), autok_chk_num = Value*8/Dphy Clk(Bit28:24) ~ 1us, Detect Range N(Bit20:16)/P(Bit12:8), aux_d1_deb_en = 1(Bit2)
    Scaler32SetDWord(PB18001_38_AUXCH_DIG_TEST_SEL, TO_DWORD(0x64, ucDpAuxRxNVthStart, ucDpAuxRxPVthStart, (_BIT7 | _BIT6 | _BIT2)));

    while((enumDpAuxRxAutoKState == _AUTO_CALIBRATION_INIT) && (ucAutoCalibrationCount < 2))
    {
        // Enable auto calibration
        Scaler32SetBit(PB18001_38_AUXCH_DIG_TEST_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), _BIT3);

        // Wait FSM = SET_INIT
        if(Scaler32GetBit(PB18001_34_AUX_SRAM_MARGIN_CTRL, _BIT(31, 29)) != _BIT29)
        {
            DELAY_5US();
        }

        // aux_rx_vth_set_done = 1
        Scaler32SetBit(PB18001_38_AUXCH_DIG_TEST_SEL, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // Set Timeout
        ucTimeout = 2 * (ucDpAuxRxNVthStart + ucDpAuxRxPVthStart) / 5;

        // Polling auto_k_done = 1
        while((Scaler32GetBit(PB18001_38_AUXCH_DIG_TEST_SEL, _BIT6) != _BIT6) && (ucTimeout != 0))
        {
            DELAY_5US();

            ucTimeout--;
        }

        // Check fail flag
        if(Scaler32GetBit(PB18001_38_AUXCH_DIG_TEST_SEL, _BIT7) == _BIT7)
        {
            // Detect from n->p
            if(Scaler32GetBit(PB18001_38_AUXCH_DIG_TEST_SEL, _BIT4) == 0x00)
            {
                // Fail result in Aux Trigger at Start Point
                if(Scaler32GetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x02) == ucDpAuxRxNVthStart)
                {
                    if(ucDpAuxRxNVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDpAuxRxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Negative or Zero
                        ucDpAuxRxPVthStart = 5;
                        ucDpAuxRxNVthStart += 5;

                        // Avoid Vth over limit
                        if(ucDpAuxRxNVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDpAuxRxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
                // Fail result in Aux never Trigger
                else if(Scaler32GetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x01) == ucDpAuxRxPVthStart)
                {
                    if(ucDpAuxRxPVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDpAuxRxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Positive or Zero
                        ucDpAuxRxPVthStart += 5;
                        ucDpAuxRxNVthStart = 5;

                        // Avoid Vth over limit
                        if(ucDpAuxRxPVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDpAuxRxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
            }
            // Detect from p->n
            else
            {
                // Fail result in Aux Trigger at Start Point
                if(Scaler32GetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x01) == ucDpAuxRxPVthStart)
                {
                    if(ucDpAuxRxPVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDpAuxRxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Positive or Zero
                        ucDpAuxRxPVthStart += 5;
                        ucDpAuxRxNVthStart = 5;

                        // Avoid Vth over limit
                        if(ucDpAuxRxPVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDpAuxRxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
                // Fail result in Aux never Trigger
                else if(Scaler32GetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x02) == ucDpAuxRxNVthStart)
                {
                    if(ucDpAuxRxNVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDpAuxRxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Negative or Zero
                        ucDpAuxRxPVthStart = 5;
                        ucDpAuxRxNVthStart += 5;

                        // Avoid Vth over limit
                        if(ucDpAuxRxNVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDpAuxRxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
            }

            // Refresh Detect Range P/N, Disable auto calibration
            Scaler32SetDWord(PB18001_38_AUXCH_DIG_TEST_SEL, TO_DWORD(0x64, ucDpAuxRxNVthStart, ucDpAuxRxPVthStart, _BIT2));
        }
        else
        {
            // Detect from n->p, First Loop Finish
            if(Scaler32GetBit(PB18001_38_AUXCH_DIG_TEST_SEL, _BIT4) == 0x00)
            {
                // Backup First Loop Result
                ucDpAuxRxPVthBackup = Scaler32GetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x01);
                ucDpAuxRxNVthBackup = Scaler32GetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x02);

                if(ucDpAuxRxPVthBackup == 0x00)
                {
                    ucDpAuxRxNVthBackup++;
                }
                else
                {
                    ucDpAuxRxPVthBackup--;
                }

                // Change to Detect Fron p->n
                Scaler32SetBit(PB18001_38_AUXCH_DIG_TEST_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
            }
            else
            {
                // Backup Second Loop Result
                ucDpAuxRxPVthBackup2 = Scaler32GetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x01);
                ucDpAuxRxNVthBackup2 = Scaler32GetByte(PB18001_34_AUX_SRAM_MARGIN_CTRL, 0x02);

                // Finish
                enumDpAuxRxAutoKState = _AUTO_CALIBRATION_DONE;
            }
        }

        // Disable auto calibration
        Scaler32SetBit(PB18001_38_AUXCH_DIG_TEST_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), 0x00);

        // Clear auto_k_done & Fail
        Scaler32SetBit(PB18001_38_AUXCH_DIG_TEST_SEL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

        ucAutoCalibrationCount++;
    }

    if(enumDpAuxRxAutoKState == _AUTO_CALIBRATION_DONE)
    {
        g_ucDpAuxRx0PVth = (ucDpAuxRxPVthBackup + ucDpAuxRxPVthBackup2) / 2 + _DP_AUX_AUTO_CALIBRATION_VTH;
        g_ucDpAuxRx0NVth = (ucDpAuxRxNVthBackup + ucDpAuxRxNVthBackup2) / 2;
    }
    else
    {
        g_ucDpAuxRx0PVth = _DP_AUX_AUTO_CALIBRATION_VTH;
        g_ucDpAuxRx0NVth = 0;
    }

#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    Scaler32SetBit(PB18000_18_AUX_6, ~_BIT6, 0x00);
#endif
}
#endif

//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : enumPinAssignment --> Pin Assignment Type
//                enumOrientation   --> Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetLaneMapping(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    // Aux Pin-Share Setting
    ScalerPinshareRx0TypeCPinAssert(enumPinAssignment, enumOrientation);

    if(enumOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
#if(_D0_TYPE_C_EXT_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
            // Enable Aux PN Pull High Low Swap PCB Function
            PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_ON);

            // Enable Aux Digital Phy PN Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, _BIT8);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_PN_SWAP_MODE);
#else
            // Disable Aux PN Pull High Low Swap PCB Function
            PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);

            // Disable Aux Digital Phy PN Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_DIFF_MODE);
#endif
        }
        else // Normal Cable Mode
        {
            // Disable Aux PN Pull High Low Swap PCB Function
            PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);

            // Disable Aux Digital Phy PN Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_DIFF_MODE);
        }
    }
    else
    {
        if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // Disable Aux PN Pull High Low Swap PCB Function
            PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF);

            // Disable Aux Digital Phy PN Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_DIFF_MODE);
        }
        else // Normal Cable Mode
        {
            // Enable Aux PN Pull High Low Swap PCB Function
            PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(_AUX_PN_1M_PULL_HI_LOW_SWAP_ON);

            // Enable Aux Digital Phy PN Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, _BIT8);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_PN_SWAP_MODE);
        }
    }
}

//-------------------------------------------------------
// Description  : Initial DPCD Related Addr IRQ
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx0DpcdAddrIrqInitial(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0DpcdAddrIrqInitial_SramCtrl();
#else
    ScalerDpAuxRx0DpcdAddrIrqInitial_RegCtrl();
#endif
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//-------------------------------------------------------
// Description  : Separate Dpcd Addr Irq Initial For New Mac (Sram Control)
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx0DpcdAddrIrqInitial_SramCtrl(void)
{
    // Dpcd INT Flag Clear
    Scaler32SetDWord(PB18006_38_DPCD_IRQ_FLAG, 0xFFFFFFFF);

    // Tx request backup reset
    ScalerDpAuxRx0RequestReset();

    // Dpcd Write 1 Clear Initial
    ScalerDpAuxRx0DpcdWrite1ClearInitial();

    // Dpcd Read Clear Initial
    ScalerDpAuxRx0DpcdReadClearInitial();

    // WildCard Clear
    Scaler32SetDWord(_REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_EN, 0x00);
    Scaler32SetDWord(_REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_FLAG, 0xFFFFFFFF);

    // WildCard Initial
    ScalerDpAuxRx0DpcdWildCardInitial();

    // Remap Clear
    Scaler32SetDWord(PB18005_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, 0xFFFFFFFF);

    // Remap Initial
    ScalerDpAuxRx0DpcdRemapInitial();

    // Enable DPCD INT 100~108
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x01, 0x00, 9, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);

#if((_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
    // Enable DPCD INT 110
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x01, 0x10, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);
#endif

    // Enable DPCD INT 270
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x02, 0x70, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);

    // Enable DPCD INT 600
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x06, 0x00, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);

    // Enable DPCD INT 68006
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x80, 0x06, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);

    // Enable DPCD INT 68013
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x80, 0x13, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
    // Enable DPCD INT 68027
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x80, 0x27, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);
#endif

    // Enable DPCD INT 6802B
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x80, 0x2B, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Enable HDCP2.2 Paring_info INT & Clear 69493 bit2
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x92, 0xEF, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);

    // Enable HDCP2.2 RxInfo INT & Clear 69493 bit0
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x93, 0x31, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);

    // Enable HDCP2.2 k INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x93, 0xF4, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);

    ScalerDpAuxRx0Hdcp2HandshakeIRQ(_ENABLE);
#endif

#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDscDecoderGetSupport(ScalerDpAuxRxRxDxMapping(_RX0)) == _DSC_DECODER_SUPPORT_ON)
    {
        ScalerDpAuxRx0DscIrqCtrl(_ENABLE);
    }
#endif

    // Enable HDCP AKSV IRQ
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x80, 0x0B, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);

#if(_DP_RX_FEC_SUPPORT == _ON)
    // Enable FEC DPCD 00120h and 00281h/00282h INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x01, 0x20, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);
    ScalerDpAuxRx0DpcdWildCardIntClr(_AUX_RX_DPCD_WILDCARD_281);
    ScalerDpAuxRx0SetDpcdWildCardForceDeferEnable(_AUX_RX_DPCD_WILDCARD_281, _ENABLE);
    ScalerDpAuxRx0SetDpcdWildCardIntEnable(_AUX_RX_DPCD_WILDCARD_281, _ENABLE);
#endif

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT == _ON)
    // Setting Wildcard for DPCD 2003
    ScalerDpAuxRx0DpcdWildCardSetting(_AUX_RX_DPCD_WILDCARD_2003, 0x00, 0x20, 0x03, _AUX_RX_DPCD_WILDCARD_MASK_NONE);
#endif
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    // Enable Panel Replay DPCD 001B0h INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x01, 0xB0, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);
#endif

    ScalerDpAuxRx0SwitchDpcdAddrIrqSetting();

#if(_DP_AUX_RX_DPCD_300_SOURCE_OUI_INT_SUPPORT == _ON)
    // Enable Write DPCD 300~302h INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x03, 0x00, 3, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);
#endif
}
#else
//-------------------------------------------------------
// Description  : Separate Dpcd Addr Irq Initial For Old Mac (Reg Control)
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx0DpcdAddrIrqInitial_RegCtrl(void)
{
    // Enable 068xxx INT
    Scaler32SetBit(PB18001_88_AUX_HDCP_IRQ_EN, ~_BIT16, _BIT16);

    // Enable DPCD INT
    Scaler32SetByte(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, 0x03, 0xE5);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    ScalerDpAuxRx0Hdcp2HandshakeIRQ(_ENABLE);
#endif

#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDscDecoderGetSupport(ScalerDpAuxRxRxDxMapping(_RX0)) == _DSC_DECODER_SUPPORT_ON)
    {
        ScalerDpAuxRx0DscIrqCtrl(_ENABLE);
    }
#endif

    // Clear HDCP AKSV IRQ
    Scaler32SetDWord(PB18001_8C_AUX_HDCP_IRQ_FLAG, _BIT14);

    // Enable HDCP AKSV IRQ
    Scaler32SetBit(PB18001_88_AUX_HDCP_IRQ_EN, ~_BIT14, _BIT14);

    // Disable IRQ for Error Counter
    Scaler32SetBit(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT9, 0x00);

#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT == _ON)
    // DPCD 280h Wildcard IRQ
    ScalerDpAuxRx0DpcdWildCardSetting(_AUX_RX_FEC_DECODE_EN_DETECTED, 0x00, 0x02, 0x80, _AUX_RX_DPCD_WILDCARD_MASK_NONE);
#endif

    // Clear FEC DPCD 00120h and 00281h/00282h INT Flag
    Scaler32SetDWord(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, (_BIT15 | _BIT11));

    // Enable FEC DPCD 00120h and 00281h/00282h INT
    Scaler32SetBit(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, ~(_BIT15 | _BIT14 | _BIT13 | _BIT12 | _BIT11), (_BIT15 | _BIT11));
#endif

#if((_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON) && (_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON))
#if(_DP_AUX_RX_DPCD_WILDCARD_00110_SUPPORT == _ON)
    // Setting Wildcard & Enable Int for updating DPCD
    ScalerDpAuxRx0DpcdWildCardSetting(_AUX_RX_CABLE_ID_UPDATE, 0x00, 0x01, 0x10, _AUX_RX_DPCD_WILDCARD_MASK_NONE);
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
#if(_DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT == _ON)
    // Setting Wildcard for DPCD 2003
    ScalerDpAuxRx0DpcdWildCardSetting(_AUX_RX_DPCD_WILDCARD_2003, 0x00, 0x20, 0x03, _AUX_RX_DPCD_WILDCARD_MASK_NONE);
#endif
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    // Clear Panel Replay DPCD 001B0h INT Flag
    Scaler32SetDWord(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT10);

    // Enable Panel Replay DPCD 001B0h INT
    Scaler32SetBit(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT10, _BIT10);
#endif

    ScalerDpAuxRx0SwitchDpcdAddrIrqSetting();

#if(_DP_AUX_RX_DPCD_300_SOURCE_OUI_INT_SUPPORT == _ON)
    // Clr IRQ Flag
    Scaler32SetDWord(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT25);

    // Enable Write DPCD 300~302h INT
    Scaler32SetBit(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT25, _BIT25);
#endif
}
#endif

//-------------------------------------------------------
// Description  : Aux Souce Clock Setting
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxRx0SourceClkSet(void)
{
    // Select Aux Source clk to IOSC
    ScalerSetBit(P0_0B_POWER_CTRL, ~(_BIT5 | _BIT4), 0x00);
}

//--------------------------------------------------
// Description  : DPCD Table Initial
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdInitial(void)
{
    EnumDpLaneCount enumDpLaneCount = GET_DP_RX_D0_PORT_TARGET_LANE_COUNT();
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);

    enumInputPort = enumInputPort;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Wait Rom code Initial
    BYTE ucTimeout = 0;

    while((Scaler32GetBit(PB18006_10_AUX_STATUS, _BIT31) == _BIT31) && (ucTimeout < 200))
    {
        DELAY_XUS(2);
        ucTimeout++;
    }
#endif

    ScalerDpAuxRx0SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
    ScalerDpAuxRx0SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
    ScalerDpAuxRx0SinkStatusSet(_DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);

    // MST Capability Disable
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x21, 0x00);

    ScalerDpAuxRx0ChangeDpcdVersion();

    // Enhanced Framing Support(Bit7) and DP Lane Count(Bit[4:0])
    ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x02, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | enumDpLaneCount));

    // Down Spread 0.5%
    ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x03, ~_BIT0, _BIT0);

#if(_AUDIO_SUPPORT == _ON)
    if(ScalerAudioDpGetCapabilityState(enumInputPort) == _AUDIO_DP_DPCD_SUPPORT)
    {
        ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x00, 0x04, 0x01);
    }
    else
#endif
    {
        ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x00, 0x04, 0x00);
    }

    // Down Sream Port isn't Present
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x05, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x05, 0x00);

    ScalerDpAuxRx0ClrBranchDeviceSpecificField();

    ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT0, _BIT0);

    ScalerDpAuxRxDpcdSetting_00008h(enumInputPort);

    ScalerDpAuxRxDpcdSetting_00009h(enumInputPort);

#if(_AUDIO_SUPPORT == _ON)
    if(ScalerAudioDpGetCapabilityState(enumInputPort) == _AUDIO_DP_DPCD_SUPPORT)
    {
        ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x00, 0x0A, 0x06);
    }
    else
#endif
    {
        ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x00, 0x0A, 0x00);
    }

    ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x00, 0x0B, 0x00);

#if(_DP_AUX_RX0_ASSR_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x00, 0x0D, 0x01);

    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x0A, 0x00);
#endif

    // SINK_VIDEO_FALLBACK_FORMATS Enable
    ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x20, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // Reset PCON Audio Capability
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x50, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x51, 0x00);

    // Coding Type Reset 8B10B
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x08, _CODING_TYPE_8B10B);

    // DPCD Link Status Field Setting
    ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x00, 0x41);
    ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue(0x00, 0x02, 0x01, 0x00);
    ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x02, 0x08, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x02, 0x09, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x02, 0x0A, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x02, 0x0B, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x02, 0x46, 0x20);

    // DPCD Initial Power Normal
    ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // DPCD [0x03054 ~ 0x03059]
    ScalerDpAuxRxHblankingModifyDpcdTimingInfoReset(enumInputPort);
#endif

    // DPCD [0x68000 ~ 0x68004]
    ScalerDpAuxRx0SetDpcdValue(0x06, 0x80, 0x00, g_pucSyncHdcpBksvBackup[0]);
    ScalerDpAuxRx0SetDpcdValue(0x06, 0x80, 0x01, g_pucSyncHdcpBksvBackup[1]);
    ScalerDpAuxRx0SetDpcdValue(0x06, 0x80, 0x02, g_pucSyncHdcpBksvBackup[2]);
    ScalerDpAuxRx0SetDpcdValue(0x06, 0x80, 0x03, g_pucSyncHdcpBksvBackup[3]);
    ScalerDpAuxRx0SetDpcdValue(0x06, 0x80, 0x04, g_pucSyncHdcpBksvBackup[4]);

#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
    g_ucDpHdcp14Rx0Caps = 0x03;
#else
    g_ucDpHdcp14Rx0Caps = 0x01;
#endif
    // _BIT1: Repeater,  _BIT0: HDCP Capable
    ScalerDpAuxRx0SetDpcdValue(0x06, 0x80, 0x28, g_ucDpHdcp14Rx0Caps);

#if(_DP_TX_SUPPORT == _ON)
    // Dfp Cap Initial
    ScalerDpRxDfpDeviceDetailConfigReset(enumInputPort);
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    // Initialize HDCP2.2 DPCD (69XXXh) to 0s for avoiding SRAM initial state values remained
    ScalerDpAuxRx0DpcdGroupReset(0x06, 0x90, 0x00, 1216);
#endif

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpAuxRx0MstProtocolDpcdReset();
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    // Load Certrx to DPCD Table
    ScalerDpAuxRx0Hdcp2LoadCertRrxKey();

    // Set HDCP_Capable and Repeater Bit
    g_pucDpHdcp2Rx0Caps[0] = 0x02;
    g_pucDpHdcp2Rx0Caps[1] = 0x00;
#if(_DP_AUX_RX0_HDCP22_REPEATER_SUPPORT == _ON)
    g_pucDpHdcp2Rx0Caps[2] = (_BIT1 | _BIT0);
#else
    g_pucDpHdcp2Rx0Caps[2] = (_BIT1);
#endif

    // Load RxCaps to DPCD Table
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // DPCD [0x6921D ~ 0x6921F]
        ScalerDpAuxRx0SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDpHdcp2Rx0Caps[pData[0]]);
    }
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0InitialDpcdAttribute();
#else
    // DPCD Force NACK 0x2217/2218
    ScalerDpAuxRx0DpcdForceNack();
#endif

    // AAR Mode Reset 0
    ScalerDpAuxRx0SetDpcdWriteValue(0x0F, 0xFF, 0xFF, 0x00);
}

//--------------------------------------------------
// Description  : Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx0VersionChange(EnumDpVersionType enumDpVersion)
{
    if(GET_DP_AUX_RX0_CURRENT_VERSION() != enumDpVersion)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0ChangeDpcdVersion(void)
{
    EnumDpVersionType enumDpVersion = GET_DP_RX_D0_PORT_TARGET_VERSION();
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumDpLinkRate enumDpLinkRate = ScalerDpRxGetTargetMaxLinkRate(enumInputPort);

    if(enumDpVersion >= _DP_VERSION_2_0)
    {
        // DPCD Capability Field Initial
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x00, _DP_VERSION_1_4);

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x0E, ~_BIT7, _BIT7);

        // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x10, ~_BIT3, _BIT3);

#if(_DP_RX_SST_SPLIT_SDP_SUPPORT == _ON)
        // SST Split SDP support
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x10, ~_BIT1, _BIT1);
#endif
        // Set Dpcd Link Rate by Dp Version
        ScalerDpAuxRx0SetDpcdMaxLinkRateCapability(enumDpVersion, enumDpLinkRate);

        ScalerDpAuxRx0SetSinkDeviceSpecificField(enumDpVersion);

#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
        WORD usMaxPixelRate = _HW_DP_MAC_MAX_PIXEL_MODE_128B132B * _HW_DP_MAX_PIXEL_CLOCK;

        // Max Uncompress Pixel Rate
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x22, 0x1C, LOBYTE(usMaxPixelRate));
        ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x22, 0x1D, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usMaxPixelRate));

        // Set Max Uncompress Pixel Rate Valid
        ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x22, 0x1D, ~_BIT7, _BIT7);

        ScalerDpAuxRx0DscDpcdSetting();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        ScalerDpMstRxDscVirtualDpcdSetting(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort));
#endif

#endif
    }
    else if(enumDpVersion == _DP_VERSION_1_4)
    {
        // DPCD Capability Field Initial
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x00, enumDpVersion);

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x0E, ~_BIT7, _BIT7);

        // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x10, ~_BIT3, _BIT3);

#if(_DP_RX_SST_SPLIT_SDP_SUPPORT == _ON)
        // SST Split SDP support
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x10, ~_BIT1, _BIT1);
#endif
        // Set Dpcd Link Rate by Dp Version
        ScalerDpAuxRx0SetDpcdMaxLinkRateCapability(enumDpVersion, enumDpLinkRate);

        ScalerDpAuxRx0SetSinkDeviceSpecificField(enumDpVersion);

#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
        WORD usMaxPixelRate = _HW_DP_MAC_MAX_PIXEL_MODE_8B10B * _HW_DP_MAX_PIXEL_CLOCK;

        // Max Uncompress Pixel Rate
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x22, 0x1C, LOBYTE(usMaxPixelRate));
        ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x22, 0x1D, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usMaxPixelRate));

        // Set Max Uncompress Pixel Rate Valid
        ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x22, 0x1D, ~_BIT7, _BIT7);

        ScalerDpAuxRx0DscDpcdSetting();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        ScalerDpMstRxDscVirtualDpcdSetting(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort));
#endif

#endif
    }
    else if(enumDpVersion == _DP_VERSION_1_2)
    {
        // DPCD Capability Field Initial
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_2);

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

        // Set Dpcd Link Rate by Dp Version
        ScalerDpAuxRx0SetDpcdMaxLinkRateCapability(enumDpVersion, enumDpLinkRate);

        ScalerDpAuxRx0SetSinkDeviceSpecificField(enumDpVersion);

#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
        // Clear Max Uncompress Pixel Rate
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x22, 0x1C, 0x00);

        // Clear Max Uncompress Pixel Rate and Valid bit
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x22, 0x1D, 0x00);

        ScalerDpAuxRx0DscDpcdSetting();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        ScalerDpMstRxDscVirtualDpcdSetting(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort));
#endif

#endif
    }
    else
    {
        // DPCD Capability Field Initial
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x00, _DP_VERSION_1_1);

        // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x0E, ~_BIT7, 0x00);

        // Set Dpcd Link Rate by Dp Version
        ScalerDpAuxRx0SetDpcdMaxLinkRateCapability(enumDpVersion, enumDpLinkRate);

        ScalerDpAuxRx0SetSinkDeviceSpecificField(enumDpVersion);

#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
        // Clear Max Uncompress Pixel Rate
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x22, 0x1C, 0x00);

        // Clear Max Uncompress Pixel Rate and Valid bit
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x22, 0x1D, 0x00);

        ScalerDpAuxRx0DscDpcdSetting();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        ScalerDpMstRxDscVirtualDpcdSetting(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort));
#endif

#endif
    }

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpAuxRx0SetCodingType(_CODING_TYPE_8B10B);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    ScalerDpAuxRx0PRModeDpcdSetting();
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    ScalerDpAuxRx0AuxlessAlpmDpcdSetting();
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
    ScalerDpAuxRx0FecDpcdSetting();
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerDpAuxRx0FreesyncDpcdSetting();

    // Initialize Reserved to 0
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x12, 0x00);
#else
    // Initialize Reserved to 0
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x10, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x12, 0x00);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    ScalerDpAuxRx0AdaptiveSyncDpcdSetting();
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
    ScalerDpAuxRx0HdrDpcdSetting();
#endif
#endif

    if(((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x22, 0x01) >= _DP_LINK_HBR3)))
    {
        // TPS3 Support
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x02, ~_BIT6, _BIT6);

        // TPS4 Support
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x03, ~_BIT7, _BIT7);

        // Set TRAINING_AUX_RD_INTERVAL = 8ms for EQ phase
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x0E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_LT_AUX_RD_INTVL_EQ_8MS);
    }
    else if(((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x01) == _DP_LINK_HBR2)) ||
            ((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x22, 0x01) == _DP_LINK_HBR2)))
    {
        // TPS3 Support
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x02, ~_BIT6, _BIT6);

        // TPS4 NonSupport
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x03, ~_BIT7, 0x00);

        // Set TRAINING_AUX_RD_INTERVAL Manual, Default = 400us for EQ phase
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x0E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _D0_DP_HBR2_TRAINING_AUX_RD_INTERVAL_EQ);
    }
    else
    {
        // TPS3 NonSupport
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x02, ~_BIT6, 0x00);

        // TPS4 NonSupport
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x03, ~_BIT7, 0x00);

        // Set TRAINING_AUX_RD_INTERVAL = 400us for EQ phase
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x0E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_LT_AUX_RD_INTVL_EQ_400US);
    }

    SET_DP_AUX_RX0_CURRENT_VERSION(enumDpVersion);
}

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Link Training Coding Type
// Input Value  : EnumDpLinkChannelCodingType
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetCodingType(EnumDpLinkChannelCodingType enumCodingType)
{
    g_enumDpAuxRx0CodingType = enumCodingType;
}
#endif

//--------------------------------------------------
// Description  : Dp Set IEEE OUI Support and Dp Set Sink Device Specific Field 00400h - 004FFh
// Input Value  : enumDpVersionType
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetSinkDeviceSpecificField(EnumDpVersionType enumDpVersion)
{
    switch(enumDpVersion)
    {
        case _DP_VERSION_2_0:

            // _BIT7 = 1: Always IEEE OUI Support When DPCD ver >= 1.2
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

            // Sink IEEE OUI For DP2.0
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_2_0_SINK_RTK_IEEE_OUI_L);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_2_0_SINK_RTK_IEEE_OUI_M);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_2_0_SINK_RTK_IEEE_OUI_H);

            // Sink IEEE OUI LSB For DP2.0
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_2_0_SINK_RTK_ID_STRING_0);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_2_0_SINK_RTK_ID_STRING_1);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_2_0_SINK_RTK_ID_STRING_2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_2_0_SINK_RTK_ID_STRING_3);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_2_0_SINK_RTK_ID_STRING_4);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_2_0_SINK_RTK_ID_STRING_5);

            // Sink HW/FW Version For DP2.0
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_2_0_SINK_RTK_HW_VERSION);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_2_0_SINK_RTK_FW_VERSION_H);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_2_0_SINK_RTK_FW_VERSION_L);

            break;

        case _DP_VERSION_1_4:

            // _BIT7 = 1: Always IEEE OUI Support When DPCD ver >= 1.2
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

            // Sink IEEE OUI For DP1.4
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_1_4_SINK_RTK_IEEE_OUI_L);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_1_4_SINK_RTK_IEEE_OUI_M);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_1_4_SINK_RTK_IEEE_OUI_H);

            // Sink IEEE OUI LSB For DP1.4
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_1_4_SINK_RTK_ID_STRING_0);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_1_4_SINK_RTK_ID_STRING_1);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_1_4_SINK_RTK_ID_STRING_2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_1_4_SINK_RTK_ID_STRING_3);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_1_4_SINK_RTK_ID_STRING_4);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_1_4_SINK_RTK_ID_STRING_5);

            // Sink HW/FW Version For DP1.4
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_1_4_SINK_RTK_HW_VERSION);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_4_SINK_RTK_FW_VERSION_H);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_4_SINK_RTK_FW_VERSION_L);

            break;

        case _DP_VERSION_1_2:

            // _BIT7 = 1: Always IEEE OUI Support When DPCD ver >= 1.2
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

            // Sink IEEE OUI for DP1.2
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_1_2_SINK_RTK_IEEE_OUI_L);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_1_2_SINK_RTK_IEEE_OUI_M);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_1_2_SINK_RTK_IEEE_OUI_H);

            // Sink IEEE OUI LSB For DP1.2
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_1_2_SINK_RTK_ID_STRING_0);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_1_2_SINK_RTK_ID_STRING_1);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_1_2_SINK_RTK_ID_STRING_2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_1_2_SINK_RTK_ID_STRING_3);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_1_2_SINK_RTK_ID_STRING_4);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_1_2_SINK_RTK_ID_STRING_5);

            // Sink HW/FW Version For DP1.2
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_1_2_SINK_RTK_HW_VERSION);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_2_SINK_RTK_FW_VERSION_H);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_2_SINK_RTK_FW_VERSION_L);

            break;

        default:
#if(_DP_SINK_VER11_OUI_SUPPORT == _ON)
            // _BIT7 = 1: IEEE OUI Support
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT7, _BIT7);

            // Sink IEEE OUI For DP1.1
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x00, _DP_1_1_SINK_RTK_IEEE_OUI_L);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x01, _DP_1_1_SINK_RTK_IEEE_OUI_M);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x02, _DP_1_1_SINK_RTK_IEEE_OUI_H);
#else
            // _BIT7 = 0: IEEE OUI Not Support
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT7, 0x00);

            // Sink IEEE OUI Not Support
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x00, 0x00);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x01, 0x00);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x02, 0x00);
#endif
            // Sink IEEE OUI LSB For DP1.1
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x03, _DP_1_1_SINK_RTK_ID_STRING_0);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x04, _DP_1_1_SINK_RTK_ID_STRING_1);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x05, _DP_1_1_SINK_RTK_ID_STRING_2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x06, _DP_1_1_SINK_RTK_ID_STRING_3);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x07, _DP_1_1_SINK_RTK_ID_STRING_4);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x08, _DP_1_1_SINK_RTK_ID_STRING_5);

            // Sink HW/FW Version For DP1.1
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x09, _DP_1_1_SINK_RTK_HW_VERSION);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x0A, _DP_1_1_SINK_RTK_FW_VERSION_H);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x0B, _DP_1_1_SINK_RTK_FW_VERSION_L);

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Set Branch Device Specific Field 00500h - 005FFh
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2 or _DP_VERSION_1_4
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetBranchDeviceSpecificField(EnumDpVersionType enumDpVersion)
{
    switch(enumDpVersion)
    {
        case _DP_VERSION_2_0:

            // Branch IEEE OUI For DP2.0
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x00, _DP_2_0_BRANCH_RTK_IEEE_OUI_L);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x01, _DP_2_0_BRANCH_RTK_IEEE_OUI_M);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x02, _DP_2_0_BRANCH_RTK_IEEE_OUI_H);

            // Branch IEEE OUI LSB For DP2.0
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x03, _DP_2_0_BRANCH_RTK_ID_STRING_0);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x04, _DP_2_0_BRANCH_RTK_ID_STRING_1);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x05, _DP_2_0_BRANCH_RTK_ID_STRING_2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x06, _DP_2_0_BRANCH_RTK_ID_STRING_3);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x07, _DP_2_0_BRANCH_RTK_ID_STRING_4);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x08, _DP_2_0_BRANCH_RTK_ID_STRING_5);

            // Branch HW/FW Version For DP2.0
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x09, _DP_2_0_BRANCH_RTK_HW_VERSION);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0A, _DP_2_0_BRANCH_RTK_FW_VERSION_H);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0B, _DP_2_0_BRANCH_RTK_FW_VERSION_L);

            break;

        case _DP_VERSION_1_4:

            // Branch IEEE OUI For DP1.4
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x00, _DP_1_4_BRANCH_RTK_IEEE_OUI_L);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x01, _DP_1_4_BRANCH_RTK_IEEE_OUI_M);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x02, _DP_1_4_BRANCH_RTK_IEEE_OUI_H);

            // Branch IEEE OUI LSB For DP1.4
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x03, _DP_1_4_BRANCH_RTK_ID_STRING_0);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x04, _DP_1_4_BRANCH_RTK_ID_STRING_1);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x05, _DP_1_4_BRANCH_RTK_ID_STRING_2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x06, _DP_1_4_BRANCH_RTK_ID_STRING_3);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x07, _DP_1_4_BRANCH_RTK_ID_STRING_4);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x08, _DP_1_4_BRANCH_RTK_ID_STRING_5);

            // Branch HW/FW Version For DP1.4
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x09, _DP_1_4_BRANCH_RTK_HW_VERSION);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0A, _DP_1_4_BRANCH_RTK_FW_VERSION_H);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0B, _DP_1_4_BRANCH_RTK_FW_VERSION_L);

            break;

        case _DP_VERSION_1_2:

            // Branch IEEE OUI For DP1.2
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x00, _DP_1_2_BRANCH_RTK_IEEE_OUI_L);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x01, _DP_1_2_BRANCH_RTK_IEEE_OUI_M);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x02, _DP_1_2_BRANCH_RTK_IEEE_OUI_H);

            // Branch IEEE OUI LSB For DP1.2
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x03, _DP_1_2_BRANCH_RTK_ID_STRING_0);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x04, _DP_1_2_BRANCH_RTK_ID_STRING_1);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x05, _DP_1_2_BRANCH_RTK_ID_STRING_2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x06, _DP_1_2_BRANCH_RTK_ID_STRING_3);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x07, _DP_1_2_BRANCH_RTK_ID_STRING_4);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x08, _DP_1_2_BRANCH_RTK_ID_STRING_5);

            // Branch HW/FW Version For DP1.2
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x09, _DP_1_2_BRANCH_RTK_HW_VERSION);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0A, _DP_1_2_BRANCH_RTK_FW_VERSION_H);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0B, _DP_1_2_BRANCH_RTK_FW_VERSION_L);

            break;

        default:

#if(_DP_SINK_VER11_OUI_SUPPORT == _ON)
            // Branch IEEE OUI For DP1.1
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x00, _DP_1_1_BRANCH_RTK_IEEE_OUI_L);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x01, _DP_1_1_BRANCH_RTK_IEEE_OUI_M);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x02, _DP_1_1_BRANCH_RTK_IEEE_OUI_H);
#else
            // Branch IEEE OUI Not Support
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x00, 0x00);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x01, 0x00);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x02, 0x00);
#endif
            // Branch IEEE OUI LSB For DP1.1
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x03, _DP_1_1_BRANCH_RTK_ID_STRING_0);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x04, _DP_1_1_BRANCH_RTK_ID_STRING_1);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x05, _DP_1_1_BRANCH_RTK_ID_STRING_2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x06, _DP_1_1_BRANCH_RTK_ID_STRING_3);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x07, _DP_1_1_BRANCH_RTK_ID_STRING_4);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x08, _DP_1_1_BRANCH_RTK_ID_STRING_5);

            // Branch HW/FW Version For DP1.1
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x09, _DP_1_1_BRANCH_RTK_HW_VERSION);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0A, _DP_1_1_BRANCH_RTK_FW_VERSION_H);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0B, _DP_1_1_BRANCH_RTK_FW_VERSION_L);

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Clear Branch Device Specific Field 00500h - 005FFh
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0ClrBranchDeviceSpecificField(void)
{
    // Clear Branch IEEE OUI
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x00, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x01, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x02, 0x00);

    // Clear Branch IEEE OUI LSB
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x03, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x04, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x05, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x06, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x07, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x08, 0x00);

    // Clear Branch HW/FW Version
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x09, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0A, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x05, 0x0B, 0x00);
}

//--------------------------------------------------
// Description  : Switch Irq Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SwitchDpcdAddrIrqSetting(void)
{
#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpAuxRx0SwitchMstProtocolIrq();
#endif
}

#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Switch 1C2 IRQ
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SwitchMstProtocolIrq(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Disable DPCD 1C2 / 2C0 IRQ
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x01, 0xC2, 1, _DP_AUX_RX_DPCD_INT_WRITE, _DISABLE);
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x02, 0xC0, 1, _DP_AUX_RX_DPCD_INT_READ, _DISABLE);

    if((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x06, _BIT1) == _BIT1) ||
       (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0))
    {
        // Enable DPCD 1C2 IRQ
        ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x01, 0xC2, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);
    }
#else
    // Disable DPCD 1C2 / 2C0 IRQ
    Scaler32SetBit(PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~(_BIT4 | _BIT3), 0x00);

    // Clear DPCD 1C2 / 2C0 IRQ Flag
    Scaler32SetDWord(PB18001_C8_AUX_PAYLOAD_IRQ_FLAG, (_BIT4 | _BIT3));

    if((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x06, _BIT1) == _BIT1) ||
       (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0))
    {
        // Enable DPCD 1C2 IRQ
        Scaler32SetBit(PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT4, _BIT4);
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    enumInputPort = enumInputPort;

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    if(enumDpResetStatus == _DP_DPCD_LINK_STATUS_INITIAL)
    {
        // Set DPCD 00600h to 0x01
        ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x02, 0x00);
    ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x03, 0x00);
    ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x04, 0x80);
    ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x20, 0x05, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x20, 0x05) | _BIT1));
    ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x02, 0x06, 0x00);
    ScalerDpAuxRx0SetDpcdValue(0x00, 0x02, 0x07, 0x00);

    SET_DP_AUX_RX0_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    CLR_DP_AUX_RX0_BACKUP_PD_LINK_STATUS_FLG();

#if(_DP_RX_FEC_SUPPORT == _ON)
    ScalerDpMacDphyRxFecDecode(enumInputPort, _DISABLE);

    // Clear FEC en/dis seq
    ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(0x00, 0x02, 0x80, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    if((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
    {
        // Reset FEC Ready
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x20, 0x00);
        ScalerDpMacDphyRxFecInitial(enumInputPort);
    }
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, 0x16, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT1 | _BIT0))
    {
        ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(0x00, 0x20, 0x0B, ~_BIT2, _BIT2);
    }

    ScalerDpMacDphyRxAuxlessAlpmEnable(enumInputPort, _DISABLE);
#endif

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }

#if(_DP_MST_SUPPORT == _ON)

    if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x02, 0xC0, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x02, 0xC0) & ~_BIT1));
    }

#endif
}

//--------------------------------------------------
// Description  : Dp Before Hpd Toggle Process
// Input Value  : EnumDpRxHotPlugAssertType
// Output Value : None
//--------------------------------------------------
EnumDpHotPlugTime ScalerDpAuxRx0BeforeHpdToggleProc(EnumDpHotPlugAssertType enumHpdType)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);

    if(enumHpdType == _DP_HPD_NONE)
    {
        return _DP_HPD_TIME_NONE;
    }

    if(enumHpdType == _DP_HPD_ASSERTED)
    {
        if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
        {
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_DX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
            if(ScalerTypeCPcbxTypeCxMapping(ScalerTypeCDxConvertToPcbPort(enumInputPort)) != _EMB_TYPE_C_NOT_EXIST)
            {
                return _DP_HPD_TIME_NONE;
            }
            else
#endif
            {
                if(ScalerDpRxGetHotPlugPinDetect(enumInputPort) == _HIGH)
                {
                    return _DP_HPD_TIME_NONE;
                }
            }
        }
    }

    // Reset Aux Toggle Flag
    CLR_DP_AUX_RX0_TOGGLE();

    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX0_DP_HPD_IRQ_ASSERT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);

    ScalerDpHdcpRxClrHdcpCpirqFlag(enumInputPort);
#if(_DP_HDCP2_RX_SUPPORT == _ON)
    ScalerDpHdcp2RxCancelTimerEvent(enumInputPort);
#endif

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);

#if(_DP_TX_SUPPORT == _ON)
    ScalerDpHdcp14RxCancelHdcpCpIRQ(enumInputPort);
    ScalerDpHdcp14RxCancelHdcpRepeaterProcTimeout(enumInputPort);
    ScalerDpHdcp14RxCancelHdcpReadIRQTimeout(enumInputPort);
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    ScalerDpRxDscCancelPpsTimerEvent(enumInputPort);
#endif

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
    if(enumHpdType != _DP_MARGIN_LINK_HPD_EVENT)
    {
        ScalerSyncDpCalculateLinkRate(enumInputPort);
    }
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
    ScalerDpAuxRx0SetFecStatusW1cProtectEnable(_DISABLE);
#endif

    if(enumHpdType != _DP_HPD_ASSERTED)
    {
#if(_DP_MARGIN_LINK_SUPPORT == _ON)
        if((enumHpdType != _DP_HDCP_LONG_HPD_EVENT) && (enumHpdType != _DP_MARGIN_LINK_HPD_EVENT))
        {
            ScalerDpAuxRx0MarginLinkCapabilitySwitchProc(ScalerDpRxGetTargetMaxLinkRate(enumInputPort));
        }
#endif

        ScalerDpMacStreamRxAVMute(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
        if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
        {
            ScalerDpMacDphyRxMstInfoBackup(enumInputPort, _DP_MST_BACKUP_INFO);
        }
#endif

        ScalerDpAuxRx0DisconnectReset();

        ScalerDpAuxRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

#if(_DP_TX_SUPPORT == _ON)
        ScalerDpRxDfpDeviceDetailConfigReset(enumInputPort);

        if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
        {
            ScalerDpMacTxForceIdlePatternSetting();
        }
#endif

#if(_DP_HPD_LOW_AUX_NOT_REPLY_SUPPORT == _ON)
        SET_DP_RX_AUX_RX0_HPD_LOW_RESET_FLAG();
#endif
    }

    if(enumHpdType == _DP_HPD_LOW)
    {
        ScalerDpRxSetHotPlug(enumInputPort, _LOW, 0);

        return _DP_HPD_TIME_NONE;
    }
    else if(enumHpdType == _DP_HPD_LOW_RESET_AUX)
    {
        SET_DP_RX_AUX_RX0_HPD_LOW_RESET_FLAG();

        ScalerDpRxSetHotPlug(enumInputPort, _LOW, 0);

        return _DP_HPD_TIME_NONE;
    }

    // Reset DDC0
    ScalerMcuDdcReset(enumInputPort);

    if(enumHpdType == _DP_LONG_HPD_EVENT)
    {
        return _DP_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_HDCP_LONG_HPD_EVENT)
    {
        return _DP_HDCP_LONG_HPD_TIME;
    }
    else if(enumHpdType == _DP_MST_LONG_HPD_EVENT)
    {
        SET_DP_RX_AUX_RX0_HPD_LOW_RESET_FLAG();

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
        // No Receiving Topology Rebuild MSG within 4s
        if(GET_DP_MST_TX_WAIT_TOPOLOGY_REBUILD_MSG() == _TRUE)
        {
            CLR_DP_MST_TX_WAIT_TOPOLOGY_REBUILD_MSG();

            return _DP_MST_FORCE_LONG_HPD_TIME;
        }
        else
#endif
        {
            return _DP_MST_LONG_HPD_TIME;
        }
    }
#if(_DP_MARGIN_LINK_SUPPORT == _ON)
    else if(enumHpdType == _DP_MARGIN_LINK_HPD_EVENT)
    {
        return _DP_MARGIN_LINK_HPD_TIME;
    }
#endif
    else if(enumHpdType == _DP_HPD_ASSERTED)
    {
        return _DP_HPD_ASSERTED_TIME;
    }

    return _DP_HPD_TIME_NONE;
}

//--------------------------------------------------
// Description  : Disconnect Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DisconnectReset(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);

    // GUID Reset 00030-0003F
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x00, 0x30, 16);

    // Link Configuration Reset 100~106
    ScalerDpAuxRx0DpcdLinkConfigReset();

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_ADAPTIVESYNC_SUPPORT == _ON))
    // Ignor MSA Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x07, 0x00);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    ScalerDrrFreeSyncDpSetEnable(enumInputPort, _DISABLE);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    ScalerDrrDpAdaptiveSyncSetEnable(enumInputPort, _DISABLE);
#endif

#if(_DP_AUX_RX0_ASSR_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x0A, 0x00);
#endif

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Cable ID Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x10, 0x00);
#endif

    // Audio Delay Reset 00112-00114
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x01, 0x12, 3);

    // eDP Link Rate / TX GTC Cap Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x15, 0x00);

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
    // Reset Auxless ALPM Enable
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x16, 0x00);
    ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x20, 0x0B, 0x00);
    ScalerDpMacDphyRxAuxlessAlpmEnable(enumInputPort, _DISABLE);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
    // FEC Status Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x20, 0x00);
    ScalerDpMacDphyRxFecInitial(enumInputPort);
#endif

#if((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
    ScalerDpAuxRxDscUnplugReset(enumInputPort);
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpAuxRx0MstProtocolDpcdReset();

    ScalerDpMstRxReset(enumInputPort);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
    // PR Status Reset
    ScalerDpAuxRx0PRModeDpcdSetting();
#endif

    // DP_PWR_NOT_NEEDED_BY_UPSTREAM_DEVICE Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x18, 0x00);

    // DPRX_SLEEP_WAKE_TIMEOUT_PERIOD_GRANTED Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x19, 0x00);

    // TX/RX GTC Value Reset 00154-0015B
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x01, 0x54, 8);

    // Adapter Ctrl Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0xA0, 0x00);

    // Hot Plug/Hot Unplug Event Notification Type Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0xA1, 0x00);

    // Continuous 80Bit Pattern From DpRx Aux Ch Enable Reset
    ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x02, 0x5B, ~_BIT0, 0x00);

    // Source OUI Reset
    ScalerDpAuxRx0DpcdSourceOUIReset();

    // Continuous 264Bit Pattern From DpRx Aux Ch Enable Reset
    ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x22, 0x52, ~_BIT0, 0x00);

    // Protocol Converter Extension Reset
    ScalerDpAuxRx0DpcdProtocolConverterReset();

    ScalerDpMacDphyRxHDCPUnplugReset(enumInputPort);

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // DPCD [0x03054 ~ 0x03059]
    ScalerDpAuxRxHblankingModifyDpcdTimingInfoReset(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : Dp After Hpd Toggle Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0AfterHpdToggleProc(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    if((GET_DP_AUX_RX0_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS) && (GET_DP_AUX_RX0_LINK_TRAINING_STATUS() != _DP_FAKE_LINK_TRAINING_PASS))
    {
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x00, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x01, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x01, 0x01) & 0xE0));
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x08, _CODING_TYPE_8B10B);

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerDpAuxRx0SetCodingType(_CODING_TYPE_8B10B);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
        // FEC Status Reset
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x20, 0x00);
        ScalerDpMacDphyRxFecInitial(enumInputPort);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
        // Reset Auxless ALPM Enable
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x16, 0x00);
        ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x20, 0x0B, 0x00);
        ScalerDpMacDphyRxAuxlessAlpmEnable(enumInputPort, _DISABLE);
#endif
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }

    // Rx Mac SST Mode Config for 0x111 Reset
    ScalerDpMacDphyRxConfigMstOrSstMode(enumInputPort);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(enumInputPort == GET_DP_RX_MAIN_PORT())
    {
        CLR_DP_MAC_TX_LINK_ESTABLISH_STATUS();
    }
#endif

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Cable ID Proc to Update DPCD
    ScalerDpRxCableIdProc(enumInputPort);
#endif

    if(ScalerDpRxCableStatus(enumInputPort) == _TRUE)
    {
        ScalerDpAuxRxClrValidVideoCheck(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
        ScalerTimerActiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
#else
        ScalerTimerActiveTimerEvent(SEC(1.2), _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_DP_DPCD_DFP_PRESENT_REF_TO == _DP_MST_CAPABILITY)
        if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
        {
            ScalerDpAuxRxSinkCountUpdate(enumInputPort, 1, _FALSE);
        }
        else
#endif
        {
            if(enumInputPort == GET_DP_RX_MAIN_PORT())
            {
                ScalerDpAuxRxSinkCountUpdate(enumInputPort, (GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT() + 1), _FALSE);
            }
            else
            {
                ScalerDpAuxRxSinkCountUpdate(enumInputPort, 1, _FALSE);
            }
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Dp Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0LinkStatusIRQ(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    if((GET_DP_AUX_RX0_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_FAIL) || (GET_DP_AUX_RX0_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
    {
        ScalerDpAuxRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_IRQ);

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_AUX_RX0_AUTO_MODE();
        }

#if(_DP_HDCP14_RX_SUPPORT == _ON)
        ScalerDpHdcp14RxResetProc(enumInputPort);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        ScalerDpHdcp2RxResetProc(enumInputPort);
#endif

        if((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
           (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);

            ScalerDpHdcpRxClrHdcpCpirqFlag(enumInputPort);

#if(_DP_HDCP2_RX_SUPPORT == _ON)
            ScalerDpHdcp2RxCancelTimerEvent(enumInputPort);
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            ScalerDpRxDscCancelPpsTimerEvent(enumInputPort);
#endif

            ScalerDpAuxRx0HpdIrqAssert();
        }
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
}

//--------------------------------------------------
// Description  : Dp Aux Power On
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0PowerOn(void)
{
    // Disable Aux Power Saving Mode
    Scaler32SetBit(PB18000_08_AUX_2, ~_BIT1, 0x00);

    // Disable Aux INT
    Scaler32SetBit(PB18001_08_AUX_IRQ_EN, ~_BIT12, 0x00);
}

//--------------------------------------------------
// Description  : Dp IRQ Assert Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0HpdIrqAssert(void)
{
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON)))

    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCDxConvertToPcbPort(enumInputPort);

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
    if(ScalerTypeCPcbxTypeCxMapping(enumTypeCPcbPort) != _EMB_TYPE_C_NOT_EXIST)
    {
        if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
        {
            ScalerTypeCPdPushHpd(enumInputPort, _PD_HPD_IRQ, 2);
        }
    }
    else
#elif(_PORT_CTRL_TCPM_SUPPORT == _ON)
    if(ScalerTypeCRxGetPortCtrlType(enumInputPort) == _TYPE_C_PORT_CTRL_TCPM)
    {
        if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
        {
            ScalerTypeCTcpmPdPushHpd(enumTypeCPcbPort, _PD_HPD_IRQ, 2);
        }
    }
    else
#endif
#endif
    {
        if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
        {
#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
            SET_DP_AUX_RX0_HPD_IRQ_ASSERT_T2_EVENT();
#else
            EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

#if(_DP_TX_SUPPORT == _ON)
            // Disable IRQs that take too long
            BYTE ucBackUp2 = ScalerGetBit(PBB_72_HPD_IRQ_EN, _BIT6);
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);
#endif

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_AUX_RX0_MANUAL_MODE();
            }

            PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);

            // Default = 750us
            switch(GET_DP_IRQ_TIME_10US())
            {
                case 55:
                    DELAY_XUS(500);
                    break;

                case 60:
                    DELAY_XUS(546);
                    break;

                case 65:
                    DELAY_XUS(588);
                    break;

                case 70:
                    DELAY_XUS(634);
                    break;

                case 75:
                default:
                    DELAY_XUS(682);
                    break;

                case 80:
                    DELAY_XUS(728);
                    break;

                case 85:
                    DELAY_XUS(768);
                    break;

                case 90:
                    DELAY_XUS(816);
                    break;

                case 95:
                    DELAY_XUS(862);
                    break;
            }

            PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_AUX_RX0_AUTO_MODE();
            }

#if(_DP_TX_SUPPORT == _ON)
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, ucBackUp2);
#endif
#endif

            // For Meeting Spec of HPD_IRQ Minimum Spacing >= 2 ms
            ScalerTimerDelayXms(3);
        }
    }
}

//--------------------------------------------------
// Description  : DP Rx0 Interface Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0FakeLTProtect(void)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY);

    SET_DP_AUX_RX0_FAKE_LINK_TRAINING();

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    if((GET_DP_AUX_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_AUX_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
    {
        SET_DP_AUX_RX0_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);

#if(_DP_RX_FEC_SUPPORT == _ON)
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if((ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, 0x20, _BIT0) == _BIT0) &&
           (g_enumDpAuxRx0CodingType == _CODING_TYPE_8B10B))
#else
        if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, 0x20, _BIT0) == _BIT0)
#endif
        {
            ScalerDpAuxRx0SetFecStatusW1cProtectEnable(_ENABLE);
        }
#endif
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
}

//--------------------------------------------------
// Description  : DP Sink Status Setting
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync)
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x05, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x05, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x02, 0x05) | _BIT1));
        }
        else if(enumReceiverPort == _DP_STREAM_REGENERATION_STATUS)
        {
            // Set Stream is Being Regenerated
            ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x05, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x02, 0x05) | _BIT2));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x05, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x05, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT1));
        }
        else if(enumReceiverPort == _DP_STREAM_REGENERATION_STATUS)
        {
            // Set Stream is Not Being Regenerated
            ScalerDpAuxRx0SetDpcdMirrorValue(0x00, 0x02, 0x05, (ScalerDpAuxRx0GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT2));
        }
    }
}

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetManualMode(void)
{
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(CPU32_IS_INSIDE_INTERRUPT() == _FALSE)
    {
        WORD usManualModeDelay = 0;

        while((g_enumDpAuxRx0CodingType == _CODING_TYPE_128B132B) && (g_ucDpAuxRx0TrainingPatternSet == _DP_TRAINING_PATTERN_2) && (usManualModeDelay < 12000))
        {
            DELAY_5US();

            usManualModeDelay++;
        }
    }
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    BYTE ucLoopIndexInAuxMacro = 0;

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _DISABLE);

    if(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) > _BIT9)
    {
        do
        {
            DELAY_5US();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 45)
            {
                break;
            }
        }while(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) > _BIT9);
    }

    // If aux state is xmit_st, wait 5us to handle request data
    if(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) == _BIT9)
    {
        DELAY_5US();
    }

    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT17, 0x00);

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _ENABLE);
#else
    BYTE ucLoopIndexInAuxMacro = 0;

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    if(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) != _BIT8)
    {
        do
        {
            DELAY_5US();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 100)
            {
                break;
            }
        }while(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) != _BIT8);
    }

    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT17, 0x00);

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);
#endif
}

//--------------------------------------------------
// Description  : DP Aux Set Manual Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetAutoMode(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    BYTE ucLoopIndexInAuxMacro = 0;

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _DISABLE);

    if(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) > _BIT9)
    {
        do
        {
            DELAY_5US();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 45)
            {
                break;
            }
        }while(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) > _BIT9);

        DELAY_5US();
    }

    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT17, _BIT17);

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _ENABLE);
#else
    BYTE ucLoopIndexInAuxMacro = 0;

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    if(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) != _BIT8)
    {
        do
        {
            DELAY_5US();

            ucLoopIndexInAuxMacro++;

            if(ucLoopIndexInAuxMacro > 100)
            {
                break;
            }
        }while(Scaler32GetBit(_REG_DP_AUX_RX0_STATUS, _BIT(10, 8)) != _BIT8);
    }

    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT17, _BIT17);

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);
#endif
}

//--------------------------------------------------
// Description  : Input Dpcd Access Addr
// Input Value  : ulDpcdAddr
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdAccessAddr(DWORD ulDpcdAddr)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

    // Set Dpcd Addr
    Scaler32SetDWord(_REG_DP_AUX_RX0_DPCD_ADDR_INPUT_PORT, ulDpcdAddr);

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT2);

    while((Scaler32GetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, _BIT2) == _BIT2) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Addr
    Scaler32SetDWord(_REG_DP_AUX_RX0_DPCD_ADDR_INPUT_PORT, ulDpcdAddr);
#endif
}

//--------------------------------------------------
// Description  : Input Dpcd Access Data
// Input Value  : usDpcdData
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdAccessByteData(BYTE ucDpcdData)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    // Backup For Avoid Interrupt Conflict
    g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxNotDpcdBit = 0xFF00;
    g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdBit = ucDpcdData;

    // Set Flag Avoid Interrupt
    SET_DP_AUX_RX0_DPCD_UPDATE_PROTECT();
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Data Value = Original Data and Set _BITX
    g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdData = ((ScalerDpAuxRx0GetDpcdAccessData() & 0xFF00) | ucDpcdData);
#else
    // Set Dpcd Data Value
    g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdData = ucDpcdData;
#endif

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess = Scaler32GetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, _DP_AUX_RX_DPCD_ACCESS_ALL);

    // Avoid Hw Bug
    ScalerDpAuxRx0AccessSelect(_DP_AUX_RX_DPCD_ACCESS_ALL);
#endif

    // Set Dpcd Data
    Scaler32SetDWord(_REG_DP_AUX_RX0_DPCD_DATA_INPUT_PORT, g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdData);

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT0);

    // Reset Backup
    CLR_DP_AUX_RX0_DPCD_UPDATE_PROTECT();

    while((Scaler32GetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, _BIT0) == _BIT0) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore Original Setting
    ScalerDpAuxRx0AccessSelect(enumDpAuxRxDpcdAccess);
#endif
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Data
    Scaler32SetDWord(_REG_DP_AUX_RX0_DPCD_DATA_INPUT_PORT, g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdData);
#endif
}

//--------------------------------------------------
// Description  : Input Dpcd Access Data
// Input Value  : usDpcdData
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdAccessBitData(WORD usNotDpcdBit, WORD usDpcdBit)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    bit bAutoIncBackUp = (Scaler32GetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, _BIT3) == _BIT3);
#else
    bit bAutoIncBackUp = (Scaler32GetBit(_REG_DP_AUX_RX0_DPCD_ADDR_INPUT_PORT, _BIT20) == _BIT20);
#endif

    if(bAutoIncBackUp == _TRUE)
    {
        // Disable Dpcd Auto Inc
        ScalerDpAuxRx0DpcdAutoIncEnable(_DISABLE);
    }

    // Backup For Avoid Interrupt Conflict
    g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxNotDpcdBit = usNotDpcdBit;
    g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdBit = usDpcdBit;

    // Set Flag Avoid Interrupt
    SET_DP_AUX_RX0_DPCD_UPDATE_PROTECT();

    // Set Dpcd Data Value = Original Data and Set _BITX
    g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdData = ((ScalerDpAuxRx0GetDpcdAccessData() & g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxNotDpcdBit) | g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdBit);

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    WORD usTimeout = 1000;

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess = Scaler32GetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, _DP_AUX_RX_DPCD_ACCESS_ALL);

    // Avoid Hw Bug
    ScalerDpAuxRx0AccessSelect(_DP_AUX_RX_DPCD_ACCESS_ALL);
#endif

    // Set Dpcd Data
    Scaler32SetDWord(_REG_DP_AUX_RX0_DPCD_DATA_INPUT_PORT, g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdData);

    // Set Aux Rx Mac Access Busy to toggle Hw
    Scaler32SetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, ~(_BIT(2, 0)), _BIT0);

    // Reset Backup
    CLR_DP_AUX_RX0_DPCD_UPDATE_PROTECT();

    while((Scaler32GetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, _BIT0) == _BIT0) && (--usTimeout))
    {
        ScalerMcuDelayDot2usPN();
    }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore Original Setting
    ScalerDpAuxRx0AccessSelect(enumDpAuxRxDpcdAccess);
#endif
#else
    ScalerMcuDelayDot2usPN();

    // Set Dpcd Data
    Scaler32SetDWord(_REG_DP_AUX_RX0_DPCD_DATA_INPUT_PORT, g_stDpAuxRx0DpcdUpdateProtect.usDpAuxRxDpcdData);

    // Reset Backup
    CLR_DP_AUX_RX0_DPCD_UPDATE_PROTECT();
#endif

    if(bAutoIncBackUp == _TRUE)
    {
        // Enable Dpcd Auto Inc
        ScalerDpAuxRx0DpcdAutoIncEnable(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : Get Dpcd Access Data
// Input Value  : none
// Output Value : usDpcdData
//--------------------------------------------------
WORD ScalerDpAuxRx0GetDpcdAccessData(void)
{
    ScalerMcuDelayDot2usPN();

    // Get Dpcd Data
    return Scaler32GetWord(_REG_DP_AUX_RX0_DPCD_DATA_OUTPUT_PORT, 0x00);
}

//--------------------------------------------------
// Description  : DP Aux Auto Inc Enable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdAutoIncEnable(bit bEnable)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    Scaler32SetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, ~_BIT3, (bEnable << 3));
#else
    Scaler32SetBit(_REG_DP_AUX_RX0_DPCD_ADDR_INPUT_PORT, ~_BIT20, (bEnable << 20));
#endif
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRx0GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
#endif

    return (BYTE)(ScalerDpAuxRx0GetDpcdAccessData() & _BIT(7, 0));
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpAuxRx0GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
#endif

    return (BYTE)(ScalerDpAuxRx0GetDpcdAccessData() & ucDpcdBit);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Access Data
    ScalerDpAuxRx0AccessSelect(_DP_AUX_RX_DPCD_ACCESS_DATA);
#endif

    // Set Dpcd Data
    ScalerDpAuxRx0SetDpcdAccessByteData(ucDpcdValue);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Set Manual Mode For R/W Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data
    ScalerDpAuxRx0SetDpcdAccessByteData(ucDpcdValue);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Set Auto Mode For W1C Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data
    ScalerDpAuxRx0SetDpcdAccessByteData(ucDpcdValue);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }
#endif

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Access Data
    ScalerDpAuxRx0AccessSelect(_DP_AUX_RX_DPCD_ACCESS_DATA);
#endif

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx0SetDpcdAccessBitData((WORD)ulNotDpcdBit, ucDpcdBit);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdBitWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Set Manual Mode For R/W Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx0SetDpcdAccessBitData((WORD)ulNotDpcdBit, ucDpcdBit);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Set Auto Mode For W1C Dpcd
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Set Dpcd Data Value = Original Data and Set _BITX
    ScalerDpAuxRx0SetDpcdAccessBitData((WORD)ulNotDpcdBit, ucDpcdBit);

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_MANUAL_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdMirrorValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    DWORD ulDpcdAddrMirror = ScalerDpAuxRxDpcdGetMirrorAddr((ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    BYTE ucDpcdAddrMirrorH = (ulDpcdAddrMirror >> 16) & 0x0F;
    BYTE ucDpcdAddrMirrorM = (ulDpcdAddrMirror >> 8) & 0xFF;
    BYTE ucDpcdAddrMirrorL = ulDpcdAddrMirror & 0xFF;
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Set Manual Mode to Protect Mirror Addr Mismatch
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    // Set Target Dpcd Addr
    ScalerDpAuxRx0SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);

    if(ulDpcdAddrMirror != 0xFFFFFFFF)
    {
        // Set Mirror Dpcd Addr
        ScalerDpAuxRx0SetDpcdValue(ucDpcdAddrMirrorH, ucDpcdAddrMirrorM, ucDpcdAddrMirrorL, ucDpcdValue);
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
#else
    ScalerDpAuxRx0SetDpcdValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdMirrorWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    ScalerDpAuxRx0SetDpcdWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdMirrorWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdMirrorValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#else
    ScalerDpAuxRx0SetDpcdWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdValue);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdMirrorBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    DWORD ulDpcdAddrMirror = ScalerDpAuxRxDpcdGetMirrorAddr((ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    BYTE ucDpcdAddrMirrorH = (ulDpcdAddrMirror >> 16) & 0x0F;
    BYTE ucDpcdAddrMirrorM = (ulDpcdAddrMirror >> 8) & 0xFF;
    BYTE ucDpcdAddrMirrorL = ulDpcdAddrMirror & 0xFF;
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Set Manual Mode to Protect Mirror Addr Mismatch
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    // Set Target Dpcd Addr
    ScalerDpAuxRx0SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);

    if(ulDpcdAddrMirror != 0xFFFFFFFF)
    {
        // Set Mirror Dpcd Addr
        ScalerDpAuxRx0SetDpcdBitValue(ucDpcdAddrMirrorH, ucDpcdAddrMirrorM, ucDpcdAddrMirrorL, ulNotDpcdBit, ucDpcdBit);
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
#else
    ScalerDpAuxRx0SetDpcdBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdMirrorBitWriteValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    ScalerDpAuxRx0SetDpcdBitWriteValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Information, Use For Dpcd Need Manual Mapping
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdMirrorBitValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#else
    ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ulNotDpcdBit, ucDpcdBit);
#endif
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Mac Access Select For New Mac
// Input Value  : enumInputPort, enumDpAuxRxDpcdAccess
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0AccessSelect(EnumDpAuxRxDpcdAccess enumDpAuxRxDpcdAccess)
{
#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    Scaler32SetBit(PB18006_68_AUX_DPCD_ACCESS_CONTROL, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), enumDpAuxRxDpcdAccess);
#else
    Scaler32SetBit(_REG_DP_AUX_RX0_DPCD_ADDR_INPUT_PORT, ~(_BIT(23, 22)), enumDpAuxRxDpcdAccess);
#endif
}

//--------------------------------------------------
// Description  : Set DPCD Table Config
// Input Value  : ucDpcdAccessPortH   --> High Byte of DPCD Address
//                ucDpcdAccessPortM   --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL   --> Low Bye of DPCD Adress
//                enumDpAuxRxDpcdConfig --> Attr : R / RW / Write Block
//                ucDpcdLen           --> Setting N = Len + 1 Dpcd Addr Attr
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdAttribute(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    DWORD ulDpcdAddr = TO_DWORD(0x00, (ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    while(ucDpcdLen > 0)
    {
        // Set Dpcd Addr
        ScalerDpAuxRx0SetDpcdAccessAddr(ulDpcdAddr);

        // Set Dpcd Access Config
        ScalerDpAuxRx0AccessSelect(_DP_AUX_RX_DPCD_ACCESS_CONFIG);

        // Set Dpcd Attr
        ScalerDpAuxRx0SetDpcdAccessBitData(~(WORD)_BIT8, enumDpAuxRxDpcdAttr);

        ulDpcdAddr++;

        ucDpcdLen--;
    }

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
}

//--------------------------------------------------
// Description  : Set DPCD Table Config
// Input Value  : ucDpcdAccessPortH        --> High Byte of DPCD Address
//                ucDpcdAccessPortM        --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL        --> Low Bye of DPCD Adress
//                enumDpAuxRxDpcdConfig --> DPCD W / R / WR INT Enable
//                ucDpcdLen                --> Setting N = Len + 1 Dpcd Addr Int Enable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdIntEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt, bit bEnable)
{
    DWORD ulDpcdAddr = TO_DWORD(0x00, (ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    while(ucDpcdLen > 0)
    {
        // Set Dpcd Addr
        ScalerDpAuxRx0SetDpcdAccessAddr(ulDpcdAddr);

        // Set Dpcd Access Config
        ScalerDpAuxRx0AccessSelect(_DP_AUX_RX_DPCD_ACCESS_CONFIG);

        // Set Dpcd Int
        if(bEnable == _ENABLE)
        {
            ScalerDpAuxRx0SetDpcdAccessBitData(~enumDpAuxRxDpcdInt, enumDpAuxRxDpcdInt);
        }
        else
        {
            ScalerDpAuxRx0SetDpcdAccessBitData(~enumDpAuxRxDpcdInt, 0x00);
        }

        ulDpcdAddr++;

        ucDpcdLen--;
    }

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
}

//--------------------------------------------------
// Description  : Get DPCD Table Config
// Input Value  : ucDpcdAccessPortH        --> High Byte of DPCD Address
//                ucDpcdAccessPortM        --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL        --> Low Bye of DPCD Adress
//                enumDpAuxRxDpcdConfig -->DPCD W / R / WR INT Enable
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpAuxRx0GetDpcdIntEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdInt enumDpAuxRxDpcdInt)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }

    return ((ScalerDpAuxRx0GetDpcdAccessData() & enumDpAuxRxDpcdInt) == enumDpAuxRxDpcdInt);
}

//--------------------------------------------------
// Description  : Set DPCD Table Config
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                bEnable           --> Force Defer Enable
//                ucDpcdLen         --> Setting N = Len Dpcd Addr Force Defer Enable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdForceDeferEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdLen, bit bEnable)
{
    DWORD ulDpcdAddr = TO_DWORD(0x00, (ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    while(ucDpcdLen > 0)
    {
        // Set Dpcd Addr
        ScalerDpAuxRx0SetDpcdAccessAddr(ulDpcdAddr);

        // Set Dpcd Access Config
        ScalerDpAuxRx0AccessSelect(_DP_AUX_RX_DPCD_ACCESS_CONFIG);

        // Set Dpcd Defer
        if(bEnable == _ENABLE)
        {
            ScalerDpAuxRx0SetDpcdAccessBitData(~(WORD)_BIT12, _BIT12);
        }
        else
        {
            ScalerDpAuxRx0SetDpcdAccessBitData(~(WORD)_BIT12, 0x00);
        }

        ulDpcdAddr++;

        ucDpcdLen--;
    }

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
}

//--------------------------------------------------
// Description  : Get DPCD Table Config
// Input Value  : ucDpcdAccessPortH   --> High Byte of DPCD Address
//                ucDpcdAccessPortM   --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL   --> Low Bye of DPCD Adress
// Output Value : Force Defer Enable
//--------------------------------------------------
bit ScalerDpAuxRx0GetDpcdForceDeferEnable(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    // Avoid Tx & FW conflict
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));

    // Restore to Original Mode
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }

    return ((ScalerDpAuxRx0GetDpcdAccessData() & _BIT12) == _BIT12);
}

//--------------------------------------------------
// Description  : Source command backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0RequestReset(void)
{
    g_stDpAuxRx0ReceiveBackup.enumDpcdGroupIrq = _DP_AUX_RX_DPCD_NONE;
    g_stDpAuxRx0ReceiveBackup.ulDpcdWildCardIrq = 0x00;
    g_stDpAuxRx0ReceiveBackup.ulDpcdRemapIrq = 0x00;
    g_stDpAuxRx0ReceiveBackup.ulReqAddrStart = 0x00;
    g_stDpAuxRx0ReceiveBackup.ucReqLen = 0x00;
    g_stDpAuxRx0ReceiveBackup.enumReqType = _DP_AUX_RX_REQ_NONE;
    g_stDpAuxRx0ReceiveBackup.ulReqAddrEnd = 0x00;
    g_stDpAuxRx0ReceiveBackup.enumIntCase = _DP_AUX_RX_INT_NONE;
    memset(g_stDpAuxRx0ReceiveBackup.pucFifoBackup, 0, sizeof(g_stDpAuxRx0ReceiveBackup.pucFifoBackup));
}

//--------------------------------------------------
// Description  : DPCD write 1 clear value initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdWrite1ClearInitial(void)
{
    // 00201 bit6:0 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x02, 0x01, 1, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 0020F bit2:0 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x02, 0x0F, 1, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 00280 bit1:0 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x02, 0x80, 1, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 002C0 bit0 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x02, 0xC0, 1, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 02003 bit6:0 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x20, 0x03, 1, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 02004 bit4:0 & 02005 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x20, 0x04, 2, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 0200B w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x20, 0x0B, 1, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 02011 bit2:0 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x20, 0x11, 1, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 02020 bit2:0 & 02021 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x20, 0x20, 2, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);

    // 03004 w1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x30, 0x04, 1, _DP_AUX_RX_DPCD_INT_WRITE_1_CLEAR, _ENABLE);
}

//--------------------------------------------------
// Description  : DPCD read 1 clear value initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdReadClearInitial(void)
{
    // 00204 bit7 r1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x02, 0x04, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);

    // 0200E bit7 r1c
    ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x20, 0x0E, 1, _DP_AUX_RX_DPCD_INT_READ, _ENABLE);
}

//--------------------------------------------------
// Description  : DP Aux DPCD Fix Attribute
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx0InitialDpcdAttribute(void)
{
    // Dpcd Config RW for 0x00110
    ScalerDpAuxRx0SetDpcdAttribute(0x00, 0x01, 0x10, 1, _AUX_RX_DPCD_ATTR_RW);

    // DPCD Config RO for 0x0300E/0x0300F
    ScalerDpAuxRx0SetDpcdAttribute(0x00, 0x30, 0x0E, 2, _AUX_RX_DPCD_ATTR_R);

    // DPCD Config RO for 0x02217/0x02218
    ScalerDpAuxRx0SetDpcdAttribute(0x00, 0x22, 0x17, 2, _AUX_RX_DPCD_ATTR_R);
}
#else
//--------------------------------------------------
// Description  : DP Aux DPCD Force NACK
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx0DpcdForceNack(void)
{
    Scaler32SetDWord(PB18002_70_AUX_AUTO_NACK1, 0x00802217);

    Scaler32SetDWord(PB18002_74_AUX_AUTO_NACK2, 0x00802218);
}
#endif

//--------------------------------------------------
// Description  : Set DPCD Group Reset
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucLen             --> Group Len
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdGroupReset(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, WORD usLen)
{
    DWORD ulDpcdAddr = TO_DWORD(0x00, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_MANUAL_MODE();
    }

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
    bit bAutoIncBackUp = (Scaler32GetBit(_REG_DP_AUX_RX0_DPCD_ACCESS_CONTROL, _BIT3) == _BIT3);

    // Set Dpcd Addr
    ScalerDpAuxRx0SetDpcdAccessAddr(ulDpcdAddr);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Set Dpcd Access Data
    ScalerDpAuxRx0AccessSelect(_DP_AUX_RX_DPCD_ACCESS_DATA);
#endif

    if(bAutoIncBackUp == _FALSE)
    {
        // Enable Dpcd Auto Inc
        ScalerDpAuxRx0DpcdAutoIncEnable(_ENABLE);
    }

    while(usLen > 0)
    {
        // Reset Dpcd
        ScalerDpAuxRx0SetDpcdAccessByteData(0x00);

        usLen--;
    }

    if(bAutoIncBackUp == _FALSE)
    {
        // Disable Dpcd Auto Inc
        ScalerDpAuxRx0DpcdAutoIncEnable(_DISABLE);
    }
#else
    while(usLen > 0)
    {
        // Set Dpcd Addr
        ScalerDpAuxRx0SetDpcdAccessAddr(ulDpcdAddr);

        // Reset Dpcd
        ScalerDpAuxRx0SetDpcdAccessByteData(0x00);

        usLen--;
        ulDpcdAddr++;
    }
#endif

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        SET_DP_AUX_RX0_AUTO_MODE();
    }
}

//--------------------------------------------------
// Description  : Dpcd LinkConfig Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdLinkConfigReset(void)
{
    // Link Configuration Reset 100~106
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x01, 0x00, 7);

    // Coding Type Reset
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x08, _CODING_TYPE_8B10B);

#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpAuxRx0SetCodingType(_CODING_TYPE_8B10B);
#endif

    // Link Quality Reset 10B~10E
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x01, 0x0B, 4);
}

//--------------------------------------------------
// Description  : Dpcd Source OUI Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdSourceOUIReset(void)
{
    // Source OUI Reset
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x03, 0x00, 12);
}

//--------------------------------------------------
// Description  : Dpcd Protocol Converter Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdProtocolConverterReset(void)
{
    // Protocol Converter Extension Reset
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x30, 0x01, 4);
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x30, 0x0E, 2);
    ScalerDpAuxRx0DpcdGroupReset(0x00, 0x30, 0x51, 9);
}

//--------------------------------------------------
// Description  : Aux PHY Swap Setting
// Input Value  : TypeC PinAssignment, TypeC Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0TypeCPinAssert(EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumTypeCOrientation)
{
    if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        // Disable Aux DPHY Swap
        Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

        SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_DIFF_MODE);
    }
    else if(enumPinAssignment == _TYPE_C_PIN_ASSIGNMENT_E)
    {
        if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Enable Aux DPHY Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, _BIT8);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_PN_SWAP_MODE);
        }
        else
        {
            // Disable Aux DPHY Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_DIFF_MODE);
        }
    }
    else
    {
        if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Disable Aux DPHY Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, 0x00);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_DIFF_MODE);
        }
        else
        {
            // Enable Aux DPHY Swap
            Scaler32SetBit(PB18001_00_AUX_DIG_PHY, ~_BIT8, _BIT8);

            SET_DP_AUX_RX0_RECEIVE_MODE(_AUX_PN_SWAP_MODE);
        }
    }
}

//--------------------------------------------------
// Description  : DP HPD Toggle AUX Reset Process
// Input Value  : HPD _HIGH/_LOW
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0HpdTogglePhyResetProc(bit bHpdHighLow)
{
    if(bHpdHighLow == _LOW)
    {
        if(GET_DP_RX_AUX_RX0_HPD_LOW_RESET_FLAG() == _TRUE)
        {
            CLR_DP_RX_AUX_RX0_HPD_LOW_RESET_FLAG();

            // Aux Phy Reset
            Scaler32SetBit(PB18000_14_AUX_5, ~_BIT7, 0x00);
        }
    }
    else
    {
        // Release Aux Phy Reset
        Scaler32SetBit(PB18000_14_AUX_5, ~_BIT7, _BIT7);
    }
}

#if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx0 DSC DPCD Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DscDpcdSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumDscDecoderSupport enumDscDecoderSupport = ScalerDscDecoderGetSupport(enumInputPort);

    if((enumDscDecoderSupport == _DSC_DECODER_SUPPORT_ON) && (GET_DP_RX_D0_PORT_TARGET_VERSION() >= _DP_VERSION_1_4))
    {
        // Set DSC Support And Dynamic PPS Compressed-to-Compressed Support
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x60, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        // Set DSC Algorithm Revision V1.2
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x61, 0x21);

        // Set DSC RC Buffer Block Size = 1KB
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x62, 0x00);

        // Set DSC Buffer Size = 5KB
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x63, 0x04);

        // Set DSC Slice Capabilities 1: 1/ 2/ 4/ 8
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x64, _HW_DP_AUX_DPCD_DSC_SLICE_CAPABILITY);

        // Set DSC Line Buffer Bit Depth = 13bits
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x65, 0x04);

        // Set DSC Block Prediction Support, Simple422 CRC Support: 444 TEST_CRC for YCbCr Simple 422 Support
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x66, 0x09);

#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
        // Set DSC Decoder Color Format Capabilities: Simple444, Simple422, Native422, Native420
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x69, 0x1F);
#else
        // Set DSC Decoder Color Format Capabilities: Simple444, Simple422, Native422
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x69, 0x0F);
#endif

        // Set DSC Decoder Color Depth Capabilities
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6A, 0x0E);

        // Set Peak DSC Throughput, Throughout Mode 0 = 340MP/s, Throughout Mode 1 = 340MP/s
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6B, 0x11);

        // Set Maximum Slice Width = 2560pixels
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6C, 0x08);

        // Set DSC Slice Capabilities 2: 1/ 2/ 4/ 8
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6D, 0x00);

        // Set MAX_BPP_DELTA_AVAILABILITY Avaliable at DPCD 0006Eh[7:0] and 0006Fh[6:3]
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x68, 0x80);

        // Set Maximum bits_per_pixel Supporte: YCbCr444 and Simple YCbCr422 with 16bpp, Natvie YCbCr420 with 12bpp
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6E, 0x21);

        // Set Maximum bits_per_pixel Supporte: Natvie YCbCr422 with 16bpp, Set bits_per_pixel Increment = 1/16bpp
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6F, 0x08);
    }
    else
    {
        // Reset DSC Support And Dynamic PPS Compressed-to-Compressed Support
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x60, ~(_BIT2 | _BIT0), 0x00);

        // Reset DSC Algorithm Revision
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x61, 0x00);

        // Reset DSC RC Buffer Block Size
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x62, 0x00);

        // Reset DSC Buffer Size
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x63, 0x00);

        // Reset DSC Slice Capabilities 1
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x64, 0x00);

        // Reset DSC Line Buffer Bit Depth
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x65, 0x00);

        // Reset DSC Block Prediction Support
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x66, 0x00);

        // Reset DSC Decoder Color Format Capabilities
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x69, 0x00);

        // Reset DSC Decoder Color Depth Capabilities
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6A, 0x00);

        // Reset Peak DSC Throughput
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6B, 0x00);

        // Reset Maximum Slice Width
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6C, 0x00);

        // Reset DSC Slice Capabilities 2
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6D, 0x00);

        // Reset MAX_BPP_DELTA_AVAILABILITY
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x68, 0x00);

        // Reset Maximum bits_per_pixel
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6E, 0x00);

        // Reset Maximum bits_per_pixel and Reset bits_per_pixel Increment
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x6F, 0x00);

        // Reset DSC Slice Line Buffer Width
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0xA2, 0x00);
    }

    ScalerDpAuxRx0DscDpcdExtendedCapSetting();

    // Reset DSC Decompression Enable
    ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x01, 0x60, ~_BIT0, 0x00);

    // Reset DSC Status
    ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue(0x00, 0x02, 0x0F, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : DP Aux Rx0 DSC DPCD Extended Cap Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DscDpcdExtendedCapSetting(void)
{
    if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        // Set DSC Support: Mirror From 00060h[2:0]
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x60, ~(_BIT2 | _BIT1 | _BIT0), ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x60, (_BIT2 | _BIT1 | _BIT0)));

        // Set DSC Algorithm Revision: Mirror From 00061h
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x61, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x61));

        // Set DSC RC Buffer Block Size: Mirror From 00062h
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x62, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x62));

        // Set DSC Buffer Size: Mirror From 00063h
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x63, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x63));

        // Set DSC Slice Capabilities 1: Mirror From 00064h
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x64, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x64));

        // Set DSC Line Buffer Bit Depth: Mirror From 00065h
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x65, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x65));

        // Set DSC Block Prediction Support, RGB Color Conversion Bypass: Mirror From 00066h
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x66, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x66));

        // Set MAX_BPP_DELTA_AVAILABILITY Avaliable: Mirror From 00068h
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x68, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x68));

        // Set DSC Decoder Color Format Capabilities: Mirror From 00069h
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x69, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x69));

        // Set DSC Decoder Color Depth Capabilities: Mirror From 0006Ah
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6A, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x6A));

        // Set Peak DSC Throughput: Mirror From 0006Bh
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6B, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x6B));

        // Set Maximum Slice Width: Mirror From 0006Ch
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6C, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x6C));

        // Set DSC Slice Capabilities 2: Mirror From 0006Dh
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6D, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x6D));

        // Set Maximum bits_per_pixel Supporte: Mirror From 0006Eh
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6E, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x6E));

        // Set Maximum bits_per_pixel Supporte: Mirror From 0006Fh
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6F, ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x6F));
    }
    else
    {
        // Set DSC Support: 0x00
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x60, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Set DSC Algorithm Revision: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x61, 0x00);

        // Set DSC RC Buffer Block Size: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x62, 0x00);

        // Set DSC Buffer Size: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x63, 0x00);

        // Set DSC Slice Capabilities 1: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x64, 0x00);

        // Set DSC Line Buffer Bit Depth: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x65, 0x00);

        // Set DSC Block Prediction Support, RGB Color Conversion Bypass: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x66, 0x00);

        // Set MAX_BPP_DELTA_AVAILABILITY Avaliable: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x68, 0x00);

        // Set DSC Decoder Color Format Capabilities: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x69, 0x00);

        // Set DSC Decoder Color Depth Capabilities: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6A, 0x00);

        // Set Peak DSC Throughput: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6B, 0x00);

        // Set Maximum Slice Width: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6C, 0x00);

        // Set DSC Slice Capabilities 2: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6D, 0x00);

        // Set Maximum bits_per_pixel Supporte: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6E, 0x00);

        // Set Maximum bits_per_pixel Supporte: 0x00
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x6F, 0x00);
    }
}

//--------------------------------------------------
// Description  : DP Aux Rx0 DSC Irq Control
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DscIrqCtrl(bit bEnable)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    if(bEnable == _ENABLE)
    {
        // Enable DSC Handshaked Related IRQ
        ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x01, 0x60, 1, _DP_AUX_RX_DPCD_INT_WRITE, _ENABLE);
    }
    else
    {
        // Disable DSC Handshaked Related IRQ
        ScalerDpAuxRx0SetDpcdIntEnable(0x00, 0x01, 0x60, 1, _DP_AUX_RX_DPCD_INT_WRITE, _DISABLE);
    }
#else
    if(bEnable == _ENABLE)
    {
        // Clear DSC Handshaked Related IRQ
        Scaler32SetDWord(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT8);

        // Enable DSC Handshaked Related IRQ
        Scaler32SetBit(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT8, _BIT8);
    }
    else
    {
        // Disable DSC Handshaked Related IRQ
        Scaler32SetBit(PB18002_50_AUX_DPCD_MISC0_IRQ_EN, ~_BIT8, 0x00);

        // Clear DSC Handshaked Related IRQ
        Scaler32SetDWord(PB18002_54_AUX_DPCD_MISC0_IRQ_FLAG, _BIT8);
    }
#endif
}

#endif // End of #if(_DP_AUX_RX0_DSC_DECODER_SUPPORT == _ON)

#if(_DP_RX_FEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx0 FEC Support Check
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpAuxRx0FecGetSupport(void)
{
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Dp20 Support
    if(GET_DP_RX_D0_PORT_TARGET_VERSION() >= _DP_VERSION_2_0)
    {
        return _TRUE;
    }
#endif

    if(GET_DP_RX_D0_PORT_TARGET_VERSION() >= _DP_VERSION_1_4)
    {
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x60, _BIT0) != 0x00)
        {
            return _TRUE;
        }
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
        if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
        {
            return _TRUE;
        }
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
        if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0xB0, _BIT0) != 0x00)
        {
            return _TRUE;
        }
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Aux Rx0 FEC DPCD Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0FecDpcdSetting(void)
{
    if(ScalerDpAuxRx0FecGetSupport() == _TRUE)
    {
        // Add Fec Running Indicator Support: Bit6
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x90, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Add Aggregated Error Counter Support
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x91, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x90, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x91, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Fec Status W1C Protect
// Input Value  : _ENABLE/_DISABLE
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx0SetFecStatusW1cProtectEnable(bit bEnable)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    g_bDpAuxRx0FecStatusW1cProtect = bEnable;
#elif(_DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT == _ON)
    ScalerDpAuxRx0SetDpcdWildCardIntEnable(_AUX_RX_FEC_DECODE_EN_DETECTED, bEnable);
#endif
}

//--------------------------------------------------
// Description  : Get Fec Status W1C Protect
// Input Value  : none
// Output Value : _ENABLE/_DISABLE
//--------------------------------------------------
bit ScalerDpAuxRx0GetFecStatusW1cProtectEnable(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    return g_bDpAuxRx0FecStatusW1cProtect;
#elif(_DP_AUX_RX_DPCD_WILDCARD_00280_SUPPORT == _ON)
    return ScalerDpAuxRx0GetDpcdWildCardIntEnable(_AUX_RX_FEC_DECODE_EN_DETECTED);
#else
    return _DISABLE;
#endif
}
#endif

//--------------------------------------------------
// Description  : Dp Rx Aux Ch Source Power Check
// Input Value  : None
// Output Value : _ON / _OFF
//--------------------------------------------------
bit ScalerDpAuxRx0ChSourcePowerCheck(void)
{
    return ScalerPinshareGetDPSourcePower(ScalerDpAuxRxRxDxMapping(_RX0));
}

//--------------------------------------------------
// Description  : Dp Rx Aux Ch Power Status Check
// Input Value  : bCableStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0AuxChPowerStatusCheck(bit bCableStatus)
{
    BYTE ucDebounceCnt = 0;

    if(bCableStatus == _TRUE)
    {
        if(ScalerDpRxGetHotPlugStatus(ScalerDpAuxRxRxDxMapping(_RX0)) == _HIGH)
        {
            // First time check power on with debounce to avoid AUX N always low case
            if((GET_DP_AUX_RX0_CHECK_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_NONE) && (ScalerDpAuxRx0ChSourcePowerCheck() == _ON))
            {
                // Debounce for 10ms
                for(ucDebounceCnt = 0; ucDebounceCnt < 5; ucDebounceCnt++)
                {
                    ScalerTimerDelayXms(2);

                    if(ScalerDpAuxRx0ChSourcePowerCheck() == _OFF)
                    {
                        break;
                    }
                }

                if(ucDebounceCnt == 5)
                {
                    SET_DP_AUX_RX0_CHECK_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_ON);
                }
            }

            // Whether to Start Debounce
            if((ScalerDpAuxRx0ChSourcePowerCheck() == _OFF) &&
               (GET_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE() == _FALSE) &&
               (GET_DP_AUX_RX0_CHECK_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_ON))
            {
                SET_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE();

                ScalerTimerActiveTimerEvent(200, _SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
            }

            // Debouncing
            if(GET_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE() == _TRUE)
            {
                if(ScalerDpAuxRx0ChSourcePowerCheck() == _ON)
                {
                    CLR_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE();
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                }
            }

            // 1.5s HotPlug has been removed because NVIDIA GTX-1080 failed while HPD togglled at the moment of PC waked up from sleep.
            if((GET_DP_AUX_RX0_CHECK_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_OFF) && (ScalerDpAuxRx0ChSourcePowerCheck() == _ON))
            {
                SET_DP_AUX_RX0_CHECK_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_ON);

#if(_DP_MST_SUPPORT == _ON)
                SET_DP_AUX_RX0_CH_POWER_ON_WAKE_UP();

                SET_DP_AUX_RX0_SOURCE_FIRST_POWER_ON();
#endif
            }
        }
    }
    else
    {
        CLR_DP_AUX_RX0_CHECK_CH_NO_POWER_DEBOUNCE();
        CLR_DP_AUX_RX0_CHECK_CH_POWER_STATUS();

        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : MST Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0MstReset(void)
{
    BYTE ucTemp = 0;
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    BYTE ucBackup111Irq = Scaler32GetBit(PB18001_C4_AUX_PAYLOAD_IRQ_EN, _BIT7);
#endif

    ScalerDpRxSetBaseInputPort(enumInputPort);

    // Reset GUID
    for(ucTemp = 0; ucTemp < 16; ucTemp++)
    {
        // DPCD [0x00030 ~ 0x0003F]
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x00, (0x30 + ucTemp), 0x00);
    }

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Clear 0x111
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x11, 0x00);
#else
    // Disable 0x111 IRQ
    Scaler32SetBit(PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT7, 0x00);

    // Clear 0x111
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0x11, 0x00);

    // Clear Source Write Mst Enable Backup
    SET_DP_AUX_RX_DPCD111_MST_ENABLE_BACKUP(_DISABLE);

    // Clear DPCD 111 Flag
    Scaler32SetDWord(PB18001_C8_AUX_PAYLOAD_IRQ_FLAG, _BIT7);

    // Backup DPCD 111 IRQ
    Scaler32SetBit(PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT7, ucBackup111Irq);
#endif

    ScalerDpAuxRx0MstProtocolDpcdReset();

    if((GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH() == 0x01) || (GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH() == 0x01))
    {
        SET_DP_AUX_RX0_COMMAND_NO_REPLY();
    }

    // Reset Rx MSG Block
    SET_DP_MST_RX_REG_MSG_RESET();

    // Disable Rx Igrone Error
    Scaler32SetBit(_REG_DP_AUX_RX0_MAC_CTRL, ~_BIT14, 0x00);

    // Clr Buf0/Buf1 MSG Finish Flag
    CLR_DP_MST_RX_REG_DOWN_REQUEST_MSG_FINISH();
    CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH();
    CLR_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_FINISH();

    // Clr Buf0 / Buf1
    CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_BUF1();
    CLR_DP_MST_RX_REG_UP_REPLY_BUF0();
    CLR_DP_MST_RX_REG_UP_REPLY_BUF1();

    // Clr Buf0/Buf1 MSG Error Flag
    CLR_DP_MST_RX_REG_DOWN_REQUEST_MSG_ERROR();

    // Clr 1000h Has Been Write
    CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN();

    // Clr 1200h Has Been Write
    CLR_DP_MST_RX_REG_UP_REPLY_ADDR_WRITTEN();

    // Message Upstream Disable
    CLR_DP_MST_RX_REG_UPSTREAM_REPLY();

    if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        // Enable Down Requeset BUF0 / BUF1 MSG Receive
        SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_BUF1_MSG_RECEIVE_ENABLE();

        // Enable Up Reply BUF0 / BUF1 MSG Receive
        SET_DP_MST_RX_REG_UP_REPLY_BUF0_BUF1_MSG_RECEIVE_ENABLE();
    }

    // Disable DOWN_REP_MSG_RDY Bit INT
    ScalerDpMstRxSetMsgReadyIrqEnable(enumInputPort, _DP_DOWN_REPLY_MSG, _DISABLE);

    // Disable UP_REQ_MSG_RDY INT
    ScalerDpMstRxSetMsgReadyIrqEnable(enumInputPort, _DP_UP_REQUEST_MSG, _DISABLE);

    // Clear Buffer
    CLR_DP_MST_RX_REG_UPSTREAM_REPLY_BUF();

    // Clear DOWN_REP_MSG_RDY & UP_REQ_MSG_RDY Bit of DPCD Table
    ScalerDpAuxRx0SetDpcdMirrorBitWrite1ClearValue(0x00, 0x20, 0x03, ~(_BIT5 | _BIT4), 0x00);
}
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#if(_DP_MARGIN_LINK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Margin Link Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0MarginLinkCapabilitySwitchProc(BYTE ucDPPhyLinkRate)
{
    if((ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) ||
       (ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7))
    {
        if(ScalerDpAuxRx0GetDpcdMaxLinkRateCapability() < ucDPPhyLinkRate)
        {
            ScalerDpAuxRx0SetDpcdMaxLinkRateCapability(_DP_VERSION_1_4, ucDPPhyLinkRate);

            DebugMessageRx0("DP14_MarginLink_Recovery_D0", ucDPPhyLinkRate);
        }
    }
}
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Load Certificate Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0Hdcp2LoadCertRrxKey(void)
{
    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < 522; PDATA_WORD(0)++)
    {
        PDATA_WORD(1) = 0x900B + PDATA_WORD(0);

        // DPCD [0x6900B ~ 0x69214]
        ScalerDpAuxRx0SetDpcdValue(0x06, HIBYTE(PDATA_WORD(1)), LOBYTE(PDATA_WORD(1)), g_stHdcp2RxDownLoadKeyType.pucHdcp2Certrx[PDATA_WORD(0)]);
    }
}

//--------------------------------------------------
// Description  : DP HDCP2.2 M' Read Defer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetMPrimeReadDefer(bit bEnable)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    if(bEnable == _ENABLE)
    {
        // Enable 69473h Force Defer
        ScalerDpAuxRx0SetDpcdForceDeferEnable(0x06, 0x94, 0x73, 1, _ENABLE);
    }
    else
    {
        // Disable 69473h Force Defer
        ScalerDpAuxRx0SetDpcdForceDeferEnable(0x06, 0x94, 0x73, 1, _DISABLE);
    }
#else
    if(bEnable == _ENABLE)
    {
        // Enable 69473h Force Defer
        Scaler32SetBit(PB18002_40_DPCD_MISC_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // Disable 69473h Force Defer
        Scaler32SetBit(PB18002_40_DPCD_MISC_CTRL, ~_BIT5, 0x00);
    }
#endif
}
#endif

#if(_DP_HDCP2_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2 Type Value Reset
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0Hdcp2TypeValueReset(void)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Reset 69494h Type Value
    ScalerDpAuxRx0SetDpcdWriteValue(0x06, 0x94, 0x94, 0x00);
#else
    // Disable Type INT
    Scaler32SetBit(PB18001_88_AUX_HDCP_IRQ_EN, ~_BIT13, 0x00);

    // Reset 69494h Type Value. Be Careful. If Clear this Address which is Writed by Source, Must Disable INT Function First.
    ScalerDpAuxRx0SetDpcdWriteValue(0x06, 0x94, 0x94, 0x00);

    // Clear Type INT Flag
    Scaler32SetDWord(PB18001_8C_AUX_HDCP_IRQ_FLAG, _BIT13);

    // Enable Type INT
    Scaler32SetBit(PB18001_88_AUX_HDCP_IRQ_EN, ~_BIT13, _BIT13);
#endif
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2 Stream ID Type Value Reset
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0Hdcp2StreamIDTypeReset(void)
{
    // Reset Stream ID Type IRQ
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, HIBYTE(g_usDpAuxRx0StreamIdAddrEnd), LOBYTE(g_usDpAuxRx0StreamIdAddrEnd), 1, _DP_AUX_RX_DPCD_INT_WRITE, _DISABLE);

    g_usDpAuxRx0StreamIdAddrEnd = 0x0000;
}
#endif

//--------------------------------------------------
// Description  : HDCP2.2 Handshaked Related IRQ
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0Hdcp2HandshakeIRQ(bit bEnable)
{
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Enable HDCP2.2 Ekh_km for AKE_Stored_km INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x90, 0x0A, 1, _DP_AUX_RX_DPCD_INT_WRITE, bEnable);

    // Enable HDCP2.2 Ekpub_km for AKE_no_Stored_km INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x92, 0x9F, 1, _DP_AUX_RX_DPCD_INT_WRITE, bEnable);

    // Enable HDCP2.2 m for AKE_Stored_km INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x92, 0xBF, 1, _DP_AUX_RX_DPCD_INT_WRITE, bEnable);

    // Enable HDCP2.2 Rn INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x92, 0xF7, 1, _DP_AUX_RX_DPCD_INT_WRITE, bEnable);

    // Enable HDCP2.2 Riv INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x93, 0x2F, 1, _DP_AUX_RX_DPCD_INT_WRITE, bEnable);

    // Enable Cipher Type INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x94, 0x94, 1, _DP_AUX_RX_DPCD_INT_WRITE, bEnable);

    // Enable Read DPCD 692DFh(HPrime) INT
    ScalerDpAuxRx0SetDpcdIntEnable(0x06, 0x92, 0xDF, 1, _DP_AUX_RX_DPCD_INT_READ, bEnable);
#else
    if(bEnable == _ENABLE)
    {
        // Clear HDCP2.2 Handshaked Related IRQ
        Scaler32SetDWord(PB18001_8C_AUX_HDCP_IRQ_FLAG, (_BIT13 | _BIT12 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1));

        // Enable HDCP2.2 Handshaked Related IRQ
        Scaler32SetBit(PB18001_88_AUX_HDCP_IRQ_EN, ~(_BIT13 | _BIT12 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), (_BIT13 | _BIT12 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1));
    }
    else
    {
        // Disable HDCP2.2 Handshaked Related IRQ
        Scaler32SetBit(PB18001_88_AUX_HDCP_IRQ_EN, ~(_BIT13 | _BIT12 | _BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), 0x00);
    }
#endif
}
#endif

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DPCD Wildcard function Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdWildCardInitial(void)
{
    ScalerDpAuxRx0DpcdWildCardSetting(_AUX_RX_DPCD_WILDCARD_210, 0x00, 0x02, 0x10, _AUX_RX_DPCD_WILDCARD_MASK_BIT3_0);
#if(_DP_RX_FEC_SUPPORT == _ON)
    ScalerDpAuxRx0DpcdWildCardSetting(_AUX_RX_DPCD_WILDCARD_281, 0x00, 0x02, 0x81, _AUX_RX_DPCD_WILDCARD_MASK_BIT3_0);
#endif
}

//--------------------------------------------------
// Description  : DPCD Remap function Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemapInitial(void)
{
/*
    Example
    ScalerDpAuxRx0DpcdRemapSetting(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen);
*/
}
#endif

//--------------------------------------------------
// Description  : DPCD Wildcard function setting
// Input Value  : WildcardId, DPCD address range, address mask or len
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdWildCardSetting(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdWildCardBitMask enumDpAuxRxDpcdWildCardBitMask)
{
    DWORD ulDpcdWildCard_Addr = 0;

    // Calculate WildCard_Addr
    ulDpcdWildCard_Addr = _REG_DP_AUX_RX0_WILDCARD_ADDR + (BYTE) enumDpAuxRxDpcdWildCardId * 4;

    // Setting len and Dpcd Addr
    Scaler32SetBit(ulDpcdWildCard_Addr, ~(_BIT(31, 24) | _BIT(19, 0)), TO_DWORD(enumDpAuxRxDpcdWildCardBitMask, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL));
}

//--------------------------------------------------
// Description  : DPCD Wildcard function Set Force Defer Enable
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdWildCardForceDeferEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable)
{
    DWORD ulDpcdWildCard_Addr = 0;

    // Calculate WildCard_Addr
    ulDpcdWildCard_Addr = _REG_DP_AUX_RX0_WILDCARD_ADDR + (BYTE) enumDpAuxRxDpcdWildCardId * 4;

    // Setting Force Defer Enable
    Scaler32SetBit(ulDpcdWildCard_Addr, ~_BIT23, ((bEnable) ? _BIT23 : 0x00));
}

//--------------------------------------------------
// Description  : DPCD Wildcard function Get Force Defer Enable
// Input Value  : wildcardId
// Output Value : Force Defer Enable
//--------------------------------------------------
bit ScalerDpAuxRx0GetDpcdWildCardForceDeferEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    DWORD ulDpcdWildCard_Addr = 0;

    // Calculate WildCard_Addr
    ulDpcdWildCard_Addr = _REG_DP_AUX_RX0_WILDCARD_ADDR + (BYTE) enumDpAuxRxDpcdWildCardId * 4;

    // Return Force Defer
    return (Scaler32GetBit(ulDpcdWildCard_Addr, _BIT23) == _BIT23);
}

//--------------------------------------------------
// Description  : DPCD Wildcard int enable
// Input Value  : WildcardId, enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdWildCardIntEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId, bit bEnable)
{
    WORD usDpcdWildCardFlag = 0;

    // Calculate WildCard_Flag
    usDpcdWildCardFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdWildCardId);

    // Clear Wildcard DPCD INT Flag
    Scaler32SetDWord(_REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_FLAG, usDpcdWildCardFlag);

    // Enable/Disable Wildcard DPCD INT
    if(bEnable == _ENABLE)
    {
        Scaler32SetBit(_REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_EN, ~usDpcdWildCardFlag, usDpcdWildCardFlag);
    }
    else
    {
        Scaler32SetBit(_REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_EN, ~usDpcdWildCardFlag, 0x00);
    }
}

//--------------------------------------------------
// Description  : DPCD Wildcard int enable
// Input Value  : WildcardId, enable/disable
// Output Value : WildCard Int Enable
//--------------------------------------------------
bit ScalerDpAuxRx0GetDpcdWildCardIntEnable(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    WORD usDpcdWildCardFlag = 0;

    // Calculate WildCard_Flag
    usDpcdWildCardFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdWildCardId);

    return (Scaler32GetBit(_REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_EN, usDpcdWildCardFlag) == usDpcdWildCardFlag);
}

//--------------------------------------------------
// Description  : DPCD Wildcard int check
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
bit ScalerDpAuxRx0DpcdWildCardIntCheck(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    WORD usDpcdWildCardFlag = 0;

    // Calculate WildCard_Flag
    usDpcdWildCardFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdWildCardId);

    return (Scaler32GetBit(_REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_FLAG, usDpcdWildCardFlag) == usDpcdWildCardFlag);
}

//--------------------------------------------------
// Description  : DPCD Wildcard int clear
// Input Value  : WildcardId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdWildCardIntClr(EnumDpAuxRxDpcdWildCardId enumDpAuxRxDpcdWildCardId)
{
    WORD usDpcdWildCardFlag = 0;

    // Calculate WildCard_Flag
    usDpcdWildCardFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdWildCardId);

    // Clear Wildcard DPCD INT Flag
    Scaler32SetDWord(_REG_DP_AUX_RX0_WILDCARD_ADDR_IRQ_FLAG, usDpcdWildCardFlag);
}

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DPCD Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemapSetting(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdRemapLen)
{
    DWORD ulDpcdRemap_Addr = 0;

    // Calculate Remap_Addr
    ulDpcdRemap_Addr = PB18005_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemapId * 4;

    // Setting len and Dpcd Addr
    Scaler32SetBit(ulDpcdRemap_Addr, ~(_BIT(31, 23) | _BIT(19, 0)), (_BIT23 | TO_DWORD(ucDpcdRemapLen, (ucDpcdAccessPortH & 0x0F), ucDpcdAccessPortM, ucDpcdAccessPortL)));

    // Reset Remap Dpcd Value
    ScalerDpAuxRx0DpcdGroupReset(ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL, ucDpcdRemapLen);
}

//--------------------------------------------------
// Description  : Get DPCD Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRx0GetDpcdRemapEnable(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId)
{
    DWORD ulDpcdRemap_Addr = 0;

    // Calculate Remap_Addr
    ulDpcdRemap_Addr = PB18005_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemapId * 4;

    return (Scaler32GetBit(ulDpcdRemap_Addr, _BIT23) == _BIT23);
}

//--------------------------------------------------
// Description  : Clear DPCD Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemapReset(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId)
{
    DWORD ulDpcdRemapBackup = 0x00;
    BYTE ucDpcdAddrH = 0x00;
    BYTE ucDpcdAddrM = 0x00;
    BYTE ucDpcdAddrL = 0x00;
    BYTE ucDpcdLen = 0x00;
    DWORD ulDpcdRemap_Addr = 0;

    // Calculate Remap_Addr
    ulDpcdRemap_Addr = PB18005_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemapId * 4;

    // Backup Dpcd Remap Dpcd Addr
    ulDpcdRemapBackup = Scaler32GetDWord(ulDpcdRemap_Addr);
    ucDpcdAddrH = (BYTE)((ulDpcdRemapBackup >> 16) & 0x0F);
    ucDpcdAddrM = (BYTE)((ulDpcdRemapBackup >> 8) & 0xFF);
    ucDpcdAddrL = (BYTE)(ulDpcdRemapBackup & 0xFF);
    ucDpcdLen = (BYTE)(ulDpcdRemapBackup >> 24);

    // Reset Remap Dpcd Value
    ScalerDpAuxRx0DpcdGroupReset(ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL, ucDpcdLen);

    Scaler32SetBit(ulDpcdRemap_Addr, ~(_BIT(31, 23) | _BIT(19, 0)), 0x00);
}

//--------------------------------------------------
// Description  : DPCD Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRx0DpcdRemapIntCheck(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId)
{
    WORD usDpcdRemapFlag = 0;

    // Calculate Remap_Addr
    usDpcdRemapFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdRemapId);

    return (Scaler32GetBit(PB18005_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, usDpcdRemapFlag) == usDpcdRemapFlag);
}

//--------------------------------------------------
// Description  : DPCD Remapping int clr
// Input Value  : remapId
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemapIntClr(EnumDpAuxRxDpcdRemapId enumDpAuxRxDpcdRemapId)
{
    WORD usDpcdRemapFlag = 0;

    // Calculate Remap_Addr
    usDpcdRemapFlag = ((WORD)(_BIT0) << (BYTE) enumDpAuxRxDpcdRemapId);

    // Clear Remap DPCD INT Flag
    Scaler32SetDWord(PB18005_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, usDpcdRemapFlag);
}
#else
//--------------------------------------------------
// Description  : DPCD 32B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap32BSetting(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    DWORD ulDpcd_Addr = (((DWORD)ucDpcdAccessPortH << 16) | (ucDpcdAccessPortM << 8) | (ucDpcdAccessPortL));
    DWORD ulDpcdRemapOffset_Addr = 0;

    DWORD ulDcpd_Offset = 0;
    DWORD ulDpcdRemapStart_Addr = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB18001_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemap32BId * 4;

        // Shift Dpcd Addr to your input
        ulDpcdRemapStart_Addr = 0x03100 + (BYTE) enumDpAuxRxDpcdRemap32BId * 32;

        // Calculate Offset
        if(ulDpcd_Addr < ulDpcdRemapStart_Addr)
        {
            ulDcpd_Offset = 0xFFFFF - ulDpcdRemapStart_Addr + ulDpcd_Addr + 1;
        }
        else
        {
            ulDcpd_Offset = ulDpcd_Addr - ulDpcdRemapStart_Addr;
        }

        // Enable Remap & Input Offset & RW Enable
        if(enumDpAuxRxDpcdAttr == _AUX_RX_DPCD_ATTR_RW)
        {
            Scaler32SetBit(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | _BIT22 | ulDcpd_Offset));
        }
        else
        {
            Scaler32SetBit(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | ulDcpd_Offset));
        }
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap16BSetting(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    DWORD ulDpcd_Addr = (((DWORD)ucDpcdAccessPortH << 16) | (ucDpcdAccessPortM << 8) | (ucDpcdAccessPortL));
    DWORD ulDpcdRemapOffset_Addr = PB18001_50_DP_MANUAL_DPCD_REMAP_ADDR4;

    DWORD ulDcpd_Offset = 0;
    DWORD ulDpcdRemapStart_Addr = 0x694A0;

    if(enumDpAuxRxDpcdRemap16BId < 2)
    {
        // Calculate Offset
        if(ulDpcd_Addr < ulDpcdRemapStart_Addr)
        {
            ulDcpd_Offset = 0xFFFFF - ulDpcdRemapStart_Addr + ulDpcd_Addr + 1;
        }
        else
        {
            ulDcpd_Offset = ulDpcd_Addr - ulDpcdRemapStart_Addr;
        }

        // Enable Remap & Input Offset & RW Enable
        if(enumDpAuxRxDpcdAttr == _AUX_RX_DPCD_ATTR_RW)
        {
            Scaler32SetBit(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | _BIT22 | ulDcpd_Offset));
        }
        else
        {
            Scaler32SetBit(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | ulDcpd_Offset));
        }
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping function for Setting
// Input Value  : RemapId, DPCD address
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap8BSetting(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, EnumDpAuxRxDpcdAttr enumDpAuxRxDpcdAttr)
{
    DWORD ulDpcd_Addr = (((DWORD)ucDpcdAccessPortH << 16) | (ucDpcdAccessPortM << 8) | (ucDpcdAccessPortL));
    DWORD ulDpcdRemapOffset_Addr = 0;

    DWORD ulDcpd_Offset = 0;
    DWORD ulDpcdRemapStart_Addr = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        if(enumDpAuxRxDpcdRemap8BId < 2)
        {
            // Calculate Remap_Addr
            ulDpcdRemapOffset_Addr = PB18001_54_DP_MANUAL_DPCD_REMAP_ADDR5 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

            // Shift Dpcd Addr to your input
            ulDpcdRemapStart_Addr = 0x694B0 + (BYTE) enumDpAuxRxDpcdRemap8BId * 8;
        }
        else
        {
            // Calculate Remap_Addr
            ulDpcdRemapOffset_Addr = PB18001_5C_DP_MANUAL_DPCD_REMAP_ADDR7 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

            // Shift Dpcd Addr to your input
            ulDpcdRemapStart_Addr = 0x00320 + (BYTE) enumDpAuxRxDpcdRemap8BId * 8;
        }

        // Calculate Offset
        if(ulDpcd_Addr < ulDpcdRemapStart_Addr)
        {
            ulDcpd_Offset = 0xFFFFF - ulDpcdRemapStart_Addr + ulDpcd_Addr + 1;
        }
        else
        {
            ulDcpd_Offset = ulDpcd_Addr - ulDpcdRemapStart_Addr;
        }

        // Enable Remap & Input Offset & RW Enable
        if(enumDpAuxRxDpcdAttr == _AUX_RX_DPCD_ATTR_RW)
        {
            Scaler32SetBit(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | _BIT22 | ulDcpd_Offset));
        }
        else
        {
            Scaler32SetBit(ulDpcdRemapOffset_Addr, ~(_BIT23 | _BIT22 | _BIT(19, 0)), (_BIT23 | ulDcpd_Offset));
        }
    }
}

//--------------------------------------------------
// Description  : Get DPCD 32B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRx0GetDpcdRemap32BEnable(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    DWORD ulDpcdRemapOffset_Addr = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB18001_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemap32BId * 4;

        return (Scaler32GetBit(ulDpcdRemapOffset_Addr, _BIT23) == _BIT23);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Get DPCD 16B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRx0GetDpcdRemap16BEnable(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    if(enumDpAuxRxDpcdRemap16BId < 1)
    {
        return (Scaler32GetBit(PB18001_50_DP_MANUAL_DPCD_REMAP_ADDR4, _BIT23) == _BIT23);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Get DPCD 8B Remapping function Enable
// Input Value  : RemapId
// Output Value : Enable / Disable
//--------------------------------------------------
bit ScalerDpAuxRx0GetDpcdRemap8BEnable(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    DWORD ulDpcdRemapOffset_Addr = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB18001_54_DP_MANUAL_DPCD_REMAP_ADDR5 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

        return (Scaler32GetBit(ulDpcdRemapOffset_Addr, _BIT23) == _BIT23);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 32B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap32BReset(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    DWORD ulDpcdRemapOffset_Addr = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB18001_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemap32BId * 4;

        // Reset Remap HW(offset/wr/En/irq_en/irq_offset)
        Scaler32SetBit(ulDpcdRemapOffset_Addr, ~(_BIT31 | _BIT(28, 22) | _BIT(19, 0)), 0x00);
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 16B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap16BReset(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    if(enumDpAuxRxDpcdRemap16BId < 1)
    {
        // Reset Remap HW(offset/wr/En/irq_en/irq_offset)
        Scaler32SetBit(PB18001_50_DP_MANUAL_DPCD_REMAP_ADDR4, ~(_BIT31 | _BIT(28, 22) | _BIT(19, 0)), 0x00);
    }
}

//--------------------------------------------------
// Description  : Clear DPCD 8B Remapping function
// Input Value  : RemapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap8BReset(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    DWORD ulDpcdRemapOffset_Addr = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapOffset_Addr = PB18001_54_DP_MANUAL_DPCD_REMAP_ADDR5 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

        // Reset Remap HW(offset/wr/En/irq_en/irq_offset)
        Scaler32SetBit(ulDpcdRemapOffset_Addr, ~(_BIT31 | _BIT(28, 22) | _BIT(19, 0)), 0x00);
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap32BIntEnable(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    BYTE ucDpcdRemapFlag = 0;
    DWORD ulDpcdRemapIrqEn_Addr = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapIrqEn_Addr = PB18001_40_DP_MANUAL_DPCD_REMAP_ADDR0 + (BYTE) enumDpAuxRxDpcdRemap32BId * 4;

        // Calculate DpcdRemapFlag
        ucDpcdRemapFlag = ((BYTE)(_BIT0) << enumDpAuxRxDpcdRemap32BId);

        // Clear dpcd_remap_irq
        Scaler32SetDWord(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ucDpcdRemapFlag);

        // Enable/Disable dpcd_remap_irq and Set dpcd_remap_irq Bit Offset
        Scaler32SetBit(ulDpcdRemapIrqEn_Addr, ~(_BIT31 | _BIT(28, 24)), TO_DWORD((((BYTE) (bEnable) << 7)) | ucDpcdRemapIrqBitOffset, 0x00, 0x00, 0x00));
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap16BIntEnable(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    if(enumDpAuxRxDpcdRemap16BId < 1)
    {
        // Clear dpcd_remap_irq
        Scaler32SetDWord(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, _BIT4);

        // Enable/Disable dpcd_remap_irq and Set dpcd_remap_irq Bit Offset
        Scaler32SetBit(PB18001_50_DP_MANUAL_DPCD_REMAP_ADDR4, ~(_BIT31 | _BIT(28, 24)), TO_DWORD((((BYTE) (bEnable) << 7)) | ucDpcdRemapIrqBitOffset, 0x00, 0x00, 0x00));
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int enable
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap8BIntEnable(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId, BYTE ucDpcdRemapIrqBitOffset, bit bEnable)
{
    BYTE ucDpcdRemapFlag = 0;
    DWORD ulDpcdRemapIrqEn_Addr = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate Remap_Addr
        ulDpcdRemapIrqEn_Addr = PB18001_54_DP_MANUAL_DPCD_REMAP_ADDR5 + (BYTE) enumDpAuxRxDpcdRemap8BId * 4;

        // Calculate DpcdRemapFlag
        ucDpcdRemapFlag = ((BYTE)(_BIT5) << enumDpAuxRxDpcdRemap8BId);

        // Clear dpcd_remap_irq
        Scaler32SetDWord(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ucDpcdRemapFlag);

        // Enable/Disable dpcd_remap_irq and Set dpcd_remap_irq Bit Offset
        Scaler32SetBit(ulDpcdRemapIrqEn_Addr, ~(_BIT31 | _BIT(28, 24)), TO_DWORD((((BYTE) (bEnable) << 7)) | ucDpcdRemapIrqBitOffset, 0x00, 0x00, 0x00));
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRx0DpcdRemap32BIntCheck(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    DWORD ulDpcdRemapFlag = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate DpcdRemapFlag
        ulDpcdRemapFlag = ((DWORD)(_BIT0) << enumDpAuxRxDpcdRemap32BId);

        return (Scaler32GetBit(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ulDpcdRemapFlag) == ulDpcdRemapFlag);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRx0DpcdRemap16BIntCheck(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    if(enumDpAuxRxDpcdRemap16BId < 1)
    {
        return (Scaler32GetBit(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, _BIT4) == _BIT4);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int check
// Input Value  : remapId
// Output Value : Int flag:1/0
//--------------------------------------------------
bit ScalerDpAuxRx0DpcdRemap8BIntCheck(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    DWORD ulDpcdRemapFlag = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate DpcdRemapFlag
        ulDpcdRemapFlag = ((DWORD)(_BIT5) << enumDpAuxRxDpcdRemap8BId);

        return (Scaler32GetBit(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ulDpcdRemapFlag) == ulDpcdRemapFlag);
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : DPCD 32B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap32BIntClr(EnumDpAuxRxDpcdRemap32BId enumDpAuxRxDpcdRemap32BId)
{
    DWORD ulDpcdRemapFlag = 0;

    if(enumDpAuxRxDpcdRemap32BId < 4)
    {
        // Calculate DpcdRemapFlag
        ulDpcdRemapFlag = ((DWORD)(_BIT0) << enumDpAuxRxDpcdRemap32BId);

        // Clear dpcd_remap_irq
        Scaler32SetDWord(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ulDpcdRemapFlag);
    }
}

//--------------------------------------------------
// Description  : DPCD 16B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap16BIntClr(EnumDpAuxRxDpcdRemap16BId enumDpAuxRxDpcdRemap16BId)
{
    if(enumDpAuxRxDpcdRemap16BId < 4)
    {
        // Clear dpcd_remap_irq
        Scaler32SetDWord(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, _BIT4);
    }
}

//--------------------------------------------------
// Description  : DPCD 8B Remapping int clear
// Input Value  : remapId
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdRemap8BIntClr(EnumDpAuxRxDpcdRemap8BId enumDpAuxRxDpcdRemap8BId)
{
    DWORD ulDpcdRemapFlag = 0;

    if(enumDpAuxRxDpcdRemap8BId < 4)
    {
        // Calculate DpcdRemapFlag
        ulDpcdRemapFlag = ((DWORD)(_BIT5) << enumDpAuxRxDpcdRemap8BId);

        // Clear dpcd_remap_irq
        Scaler32SetDWord(PB18001_3C_DP_MANUAL_DPCD_REMAP_IRQ_FLAG, ulDpcdRemapFlag);
    }
}
#endif

//--------------------------------------------------
// Description  : DPCD Link Rate Setting with different dp version
// Input Value  : DpVersion, Link Rate
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0SetDpcdMaxLinkRateCapability(EnumDpVersionType enumDpVersionType, EnumDpLinkRate enumDpLinkRate)
{
    if(enumDpVersionType >= _DP_VERSION_2_0)
    {
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        // UHBR Enable
        if(enumDpLinkRate >= _DP_ULTRA_SPEED_2000MHZ)
        {
            // 128B132B Support
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT1, _BIT1);

            ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x15, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        }
        else if(enumDpLinkRate == _DP_ULTRA_SPEED_1350MHZ)
        {
            // 128B132B Support
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT1, _BIT1);

            ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x15, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
        }
        else if(enumDpLinkRate == _DP_ULTRA_SPEED_1000MHZ)
        {
            // 128B132B Support
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT1, _BIT1);

            ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x15, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
        }
        else
        {
            // 128B132B Unsupport
            ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT1, 0x00);

            // UHBR Disable
            ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x15, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
        }
#else
        // 128B132B Unsupport
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT1, 0x00);

        // UHBR Disable
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x15, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

        if(enumDpLinkRate >= _DP_HIGH_SPEED3_810MHZ)
        {
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);

            if(enumDpLinkRate < _DP_ULTRA_SPEED_1000MHZ)
            {
                ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, enumDpLinkRate);
            }
            else
            {
                ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, _DP_LINK_HBR3);
            }
        }
        else
        {
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x01, enumDpLinkRate);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, enumDpLinkRate);
        }
    }
    else if(enumDpVersionType == _DP_VERSION_1_4)
    {
        // 128B132B Unsupport
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT1, 0x00);

        // UHBR Disable
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x15, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        if(enumDpLinkRate >= _DP_HIGH_SPEED3_810MHZ)
        {
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);

            if(enumDpLinkRate < _DP_ULTRA_SPEED_1000MHZ)
            {
                ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, enumDpLinkRate);
            }
            else
            {
                ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, _DP_LINK_HBR3);
            }
        }
        else
        {
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x01, enumDpLinkRate);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, enumDpLinkRate);
        }
    }
    else if(enumDpVersionType == _DP_VERSION_1_2)
    {
        // 128B132B Unsupport
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT1, 0x00);

        // UHBR Disable
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x15, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        if(enumDpLinkRate >= _DP_HIGH_SPEED2_540MHZ)
        {
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, _DP_LINK_HBR2);
        }
        else
        {
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x01, enumDpLinkRate);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, enumDpLinkRate);
        }
    }
    else
    {
        // 128B132B Unsupport
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x06, ~_BIT1, 0x00);

        // UHBR Disable
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x15, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        if(enumDpLinkRate >= _DP_HIGH_SPEED_270MHZ)
        {
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, _DP_LINK_HBR);
        }
        else
        {
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x00, 0x01, enumDpLinkRate);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x22, 0x01, enumDpLinkRate);
        }
    }
}

//--------------------------------------------------
// Description  : DPCD Link Rate Getting with different dp version
// Input Value  : None
// Output Value : LinkRate
//--------------------------------------------------
EnumDpLinkRate ScalerDpAuxRx0GetDpcdMaxLinkRateCapability(void)
{
#if(_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x22, 0x15, _BIT1) == _BIT1)
    {
        return _DP_LINK_UHBR20;
    }
    else if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x22, 0x15, _BIT2) == _BIT2)
    {
        return _DP_LINK_UHBR13_5;
    }
    else if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x22, 0x15, _BIT0) == _BIT0)
    {
        return _DP_LINK_UHBR10;
    }
    else if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
    {
        return (EnumDpLinkRate) ScalerDpAuxRx0GetDpcdInfo(0x00, 0x22, 0x01);
    }
    else
    {
        return (EnumDpLinkRate) ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x01);
    }
#else
    if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
    {
        return (EnumDpLinkRate) ScalerDpAuxRx0GetDpcdInfo(0x00, 0x22, 0x01);
    }
    else
    {
        return (EnumDpLinkRate) ScalerDpAuxRx0GetDpcdInfo(0x00, 0x00, 0x01);
    }
#endif
}

#if(_DP_PR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx0 PR Mode DPCD Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0PRModeDpcdSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumDpPRModeSupport enumDpPRModeSupport = ScalerDpRxPRModeGetSupport(enumInputPort);

    if((enumDpPRModeSupport == _DP_PR_MODE_SUPPORT_ON) && (GET_DP_RX_D0_PORT_TARGET_VERSION() >= _DP_VERSION_1_4))
    {
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0xB0, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0xB0, ~_BIT0, 0x00);
    }

    CLR_DP_AUX_RX0_PR_MODE_DPCD_CRC_ENABLE();

    // Reset PR Mode Enable
    ScalerDpAuxRx0SetDpcdBitWriteValue(0x00, 0x01, 0xB0, ~_BIT0, 0x00);

    // Reset PR Mode Error Status
    ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x20, 0x20, 0x00);

    // Reset PR Mode Status Inactive
    ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x20, 0x22, ~(_BIT2 | _BIT1 | _BIT0), _DP_PR_MODE_INACTIVE);

    // Reset PR Mode _DP_STREAM_REGENERATION_STATUS
    ScalerDpAuxRx0SinkStatusSet(_DP_STREAM_REGENERATION_STATUS, _DP_SINK_OUT_OF_SYNC);
}

//--------------------------------------------------
// Description  : Get DP PR Enable
// Input Value  : enumInputPort
// Output Value : PR Enable/Disable
//--------------------------------------------------
bit ScalerDpAuxRx0PRModeFlagStatus(void)
{
    return ((((ScalerDpAuxRx0GetDpcdInfo(0x00, 0x01, 0xB0) & _BIT0) == _BIT0) ? _TRUE : _FALSE));
}

//--------------------------------------------------
// Description  : Update PR Mode Error Statu DPCD 02020h
// Input Value  : EnumPRModeErrorStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdPRModeErrorStateUpdate(EnumPRModeErrorStatus enumPRModeErrorStatus)
{
    switch(enumPRModeErrorStatus)
    {
        case _DP_PR_MODE_CRC_ERROR:

            ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x20, 0x20, _DP_PR_MODE_CRC_ERROR);

            // Set Panel Replay Error Status
            ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(0x00, 0x20, 0x04, ~_BIT3, _BIT3);

            if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, 0xB0, _BIT5) == _BIT5)
            {
                ScalerDpAuxRx0HpdIrqAssert();
            }

            break;

        case _DP_PR_MODE_RFB_STORAGE_ERROR:

            ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x20, 0x20, _DP_PR_MODE_RFB_STORAGE_ERROR);

            // Set Panel Replay Error Status
            ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(0x00, 0x20, 0x04, ~_BIT3, _BIT3);

            if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, 0xB0, _BIT4) == _BIT4)
            {
                ScalerDpAuxRx0HpdIrqAssert();
            }

            break;

        case _DP_PR_MODE_SDP_UNCORRECTABLE_ERROR:

            ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x20, 0x20, _DP_PR_MODE_SDP_UNCORRECTABLE_ERROR);

            // Set Panel Replay Error Status
            ScalerDpAuxRx0SetDpcdBitWrite1ClearValue(0x00, 0x20, 0x04, ~_BIT3, _BIT3);

            if(ScalerDpAuxRx0GetDpcdBitInfo(0x00, 0x01, 0xB0, _BIT3) == _BIT3)
            {
                ScalerDpAuxRx0HpdIrqAssert();
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Update PR Mode Status DPCD 02022h
// Input Value  : EnumPRModeStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0DpcdPRModeStatusUpdate(EnumPRModeStatus enumPRModeStatus)
{
    switch(enumPRModeStatus)
    {
        case _DP_PR_MODE_INACTIVE:

            ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x20, 0x22, ~(_BIT2 | _BIT1 | _BIT0), _DP_PR_MODE_INACTIVE);

            break;

        case _DP_PR_MODE_ENTRY:

            ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x20, 0x22, ~(_BIT2 | _BIT1 | _BIT0), _DP_PR_MODE_ENTRY);

            break;

        case _DP_PR_MODE_ACTIVE:

            ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x20, 0x22, ~(_BIT2 | _BIT1 | _BIT0), _DP_PR_MODE_ACTIVE);

            break;

        case _DP_PR_MODE_INTERNAL_ERROR:

            ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x20, 0x22, ~(_BIT2 | _BIT1 | _BIT0), _DP_PR_MODE_INTERNAL_ERROR);

            // Set Hpd Irq for Pr Sink Status Internal Error
            ScalerDpAuxRx0HpdIrqAssert();

            break;

        default:
            break;
    }
}
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Aux Rx0 Auxless Alpm DPCD Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0AuxlessAlpmDpcdSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumDpAuxlessAlpmSupport enumDpAuxlessAlpmSupport = ScalerDpRxAuxlessAlpmGetSupport(enumInputPort);

    if((enumDpAuxlessAlpmSupport == _DP_AUXLESS_ALPM_SUPPORT_ON) && (GET_DP_RX_D0_PORT_TARGET_VERSION() >= _DP_VERSION_2_0))
    {
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x2E, ~_BIT2, _BIT2);
    }
    else
    {
        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x00, 0x2E, ~_BIT2, 0x00);
    }
}
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
//--------------------------------------------------
// Description  : DP Aux Rx0 Hdr DPCD Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0HdrDpcdSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);
    EnumDpHdrSupport enumDpHdrSupport = ScalerDpRxHdrGetSupport(enumInputPort);

    if((enumDpHdrSupport == _DP_HDR_SUPPORT_ON) && (GET_DP_RX_D0_PORT_TARGET_VERSION() >= _DP_VERSION_1_4))
    {
#if(_DP_HDR_VENDOR_SUPPORT == _DP_HDR_VENDOR_SUPPORT_INTEL)
        // Initial Intel EDP HDR CAPS
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x03, 0x40, 0x01);
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x03, 0x41, 0x53);
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x03, 0x42, 0x00);
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x03, 0x43, 0x00);

        // Reset Intel EDP HDR GETSET CTRL PARAMS
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x44, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x45, 0x00);

        // Reset Intel EDP HDR CONTENT LUMINANCE
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x46, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x47, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x48, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x49, 0x00);

        // Reset Intel EDP HDR PANEL LUMINANCE OVERRIDE
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4A, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4B, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4C, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4D, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4E, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4F, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x50, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x51, 0x00);

        // Reset Intel EDP SDR LUMINANCE LEVEL
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x52, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x53, 0x00);

        // Reset Intel EDP BRIGHTNESS_NITS
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x54, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x55, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x56, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x57, 0x00);

        // Reset Intel EDP BRIGHTNESS_OPTIMIZATION
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x58, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x59, 0x00);
#endif
    }
    else
    {
#if(_DP_HDR_VENDOR_SUPPORT == _DP_HDR_VENDOR_SUPPORT_INTEL)
        // Reset Intel EDP HDR CAPS
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x03, 0x40, 0x00);
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x03, 0x41, 0x00);
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x03, 0x42, 0x00);
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x03, 0x43, 0x00);

        // Reset Intel EDP HDR GETSET CTRL PARAMS
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x44, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x45, 0x00);

        // Reset Intel EDP HDR CONTENT LUMINANCE
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x46, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x47, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x48, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x49, 0x00);

        // Reset Intel EDP HDR PANEL LUMINANCE OVERRIDE
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4A, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4B, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4C, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4D, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4E, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x4F, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x50, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x51, 0x00);

        // Reset Intel EDP SDR LUMINANCE LEVEL
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x52, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x53, 0x00);

        // Reset Intel EDP BRIGHTNESS_NITS
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x54, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x55, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x56, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x57, 0x00);

        // Reset Intel EDP BRIGHTNESS_OPTIMIZATION
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x58, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x03, 0x59, 0x00);
#endif
    }
}
#endif
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Freesync Aux Rx0 DPCD Setting
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0FreesyncDpcdSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);

    if(ScalerDrrFreeSyncDpGetSupport(enumInputPort) == _FREESYNC_SUPPORT_ON)
    {
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);

        if(GET_FREESYNC_DP_AUPI_INFO() == _TRUE)
        {
            // Set AMD AUPI Info
            ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x0C, g_stDrrDpAmdAupiInfo.ucPanelManufactureIdL);
            ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x0D, g_stDrrDpAmdAupiInfo.ucPanelManufactureIdM);
            ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x0E, g_stDrrDpAmdAupiInfo.ucPanelIdL);
            ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x0F, g_stDrrDpAmdAupiInfo.ucPanelIdM);
            ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x10, g_stDrrDpAmdAupiInfo.ucFwCheckSumL);
            ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x11, g_stDrrDpAmdAupiInfo.ucFwCheckSumM);
        }
    }
    else
    {
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);

        // Clr AMD AUPI Info
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x0C, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x0D, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x0E, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x0F, 0x00);
        ScalerDpAuxRx0SetDpcdValue(0x00, 0x04, 0x10, 0x00);
        ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x04, 0x11, 0x00);
    }
}
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP AdaptiveSync Aux Rx0 DPCD Setting
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxRx0AdaptiveSyncDpcdSetting(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);

    if(ScalerDrrDpAdaptiveSyncGetSupport(enumInputPort) == _DP_ADAPTIVESYNC_SUPPORT_ON)
    {
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);

        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x14, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerDpAuxRx0SetDpcdMirrorBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);

        ScalerDpAuxRx0SetDpcdBitValue(0x00, 0x22, 0x14, ~_BIT0, 0x00);
    }
}
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_AUX_RX0_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Mst Protocol Reset Dpcd
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerDpAuxRx0MstProtocolDpcdReset(void)
{
    EnumInputPort enumInputPort = ScalerDpAuxRxRxDxMapping(_RX0);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    BYTE ucBackup1C2Irq = Scaler32GetBit(PB18001_C4_AUX_PAYLOAD_IRQ_EN, _BIT4);

    // Disable DPCD 1C2 IRQ To Avoid Trigger INT
    Scaler32SetBit(PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT4, 0x00);
#endif

    // Clear 0x1C0 ~ 0x1C2
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0xC0, 0x00);
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0xC1, 0x00);
    ScalerDpAuxRx0SetDpcdWriteValue(0x00, 0x01, 0xC2, 0x00);

    // Clear 0x2C0
    ScalerDpAuxRx0SetDpcdWrite1ClearValue(0x00, 0x02, 0xC0, 0x00);

    // Clear Payload ID Table (0x2C0 ~ 0x2FF)
    ScalerDpAuxRxClearPayload(enumInputPort);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _OFF)
    // Clear DPCD 1C2 Flag
    Scaler32SetDWord(PB18001_C8_AUX_PAYLOAD_IRQ_FLAG, _BIT4);

    // Backup DPCD 1C2 IRQ
    Scaler32SetBit(PB18001_C4_AUX_PAYLOAD_IRQ_EN, ~_BIT4, ucBackup1C2Irq);
#endif
}
#endif

#endif // End of #if(_DP_AUX_RX0_SUPPORT == _ON)
