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
// ID Code      : RL6952_Series_HdmiFrlMacRx4.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_HDMIFRLMACRX4__

#include "ScalerFunctionInclude.h"
#include "HdmiFrlMacRx4/ScalerHdmiFrlMacRx4.h"


#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
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
// Description  : Check DPF setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdmiFrlMacRx4DisplayFormatCheck(EnumInputPort enumInputPort)
{
    // RL6952 can't support 420 4-pixel mode
    if((GET_COLOR_SPACE(enumInputPort) == _COLOR_SPACE_YCBCR420) && (ScalerGetBit(P69_71_DPF_CTRL_1, (_BIT7 | _BIT6)) == 0x00))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : MAC RX4 PN Swap setting
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4PnSwapConfig(EnumInputPort enumInputPort)
{
    // RL6952's MAC-RX4 always connect to PHY-RX4
    ScalerSetByte(P1E_29_HDMI21_DPHY_1, ((_D4_TMDS_PCB_LANE3_MAPPING << 6) | (_D4_TMDS_PCB_LANE2_MAPPING << 4) |
                                         (_D4_TMDS_PCB_LANE1_MAPPING << 2) | _D4_TMDS_PCB_LANE0_MAPPING));

    if(ScalerTmdsMacRxCheckPNSwap(enumInputPort) == _TRUE)
    {
        ScalerSetBit(P1E_28_HDMI21_DPHY_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    }
    else
    {
        ScalerSetBit(P1E_28_HDMI21_DPHY_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
}

#if(_HDMI_FRL_REBUILD_PHY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Rebuild PHY flow
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerHdmiFrlMacRx4RebuildPhy(void)
{
    bit bResult = _FALSE;
    EnumInputPort enumMappingPort = ScalerTmdsMacRxRxDxMapping(_RX4);
    DWORD ulCrcResult1 = 0;
    DWORD ulCrcResult2 = 0;

    if((GET_HDMI_FRL_MAC_RX4_SIGNAL_DETECTING() == _FALSE) && (ScalerHdmiFrlMacRxGetDxFrlRate(enumMappingPort) != _HDMI_FRL_RATE_NONE))
    {
        ///////////////////////////
        // Turn on power
        ///////////////////////////

        // RX_LV Power on
        PCB_SET_RX_LV_POWER(_RX_LV_POWER_ON);

        // turn on VCCK_off power, due to Signal Detection need turn on APHY/DPHY power
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_TOPOFF, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);

        // Turn on RX4 APHY/DPHY
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX4_HDMI21_APHY, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX4_HDMI_DPHY, _POWER_CUT_OFF, _POWER_ON_DELAY_5_MS);


        ///////////////////////////
        // Turn on Xtal and M2PLL
        // Change MCU speed to 88MHz
        ///////////////////////////

        // Power on Xtal Clock.
        ScalerPowerXtalPower(_ON);

        // Power on M2PLL.
        ScalerPLLM2PLLPower(_ON);

        // Set Mcu/Flash Clock to M2PLL
        ScalerMcuFlashClockGroupSetting(_M2PLL_CLK);

        // GDI Clock Select to M2PLL & Set Divider
        ScalerTmdsPhyRxGdiClkSelect(_M2PLL_CLK);


        ///////////////////////////
        // PHY Initial
        ///////////////////////////

        // FRL PHY Initial before set PHY
        ScalerTmdsPhyRxFrlRebuildPhyInitial(enumMappingPort);


        /////////////////////////////////////////////
        // Use Signal Detection to check FRL Signal
        /////////////////////////////////////////////

        // Clear Signal Detect Done flag
        ScalerSetBit(P78_DA_HDMI21_FRL_DETECTION_0, ~(_BIT6 | _BIT1 | _BIT0), _BIT6);

        // Start Signal Detect
        ScalerSetBit(P78_DA_HDMI21_FRL_DETECTION_0, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), _BIT7);

        if(ScalerTimerPollingFlagProc(2, P78_DA_HDMI21_FRL_DETECTION_0, _BIT6, _TRUE) == _TRUE)
        {
            // Get CRC Result
            ulCrcResult1 = ((DWORD)ScalerGetBit(P78_DA_HDMI21_FRL_DETECTION_0, (_BIT1 | _BIT0)) << 16) | (ScalerGetByte(P78_DB_HDMI21_FRL_DETECTION_1) << 8) | ScalerGetByte(P78_E0_HDMI21_FRL_DETECTION_2);

            // Check again
            // Clear Signal Detect Done flag
            ScalerSetBit(P78_DA_HDMI21_FRL_DETECTION_0, ~(_BIT6 | _BIT1 | _BIT0), _BIT6);

            // Start Signal Detect
            ScalerSetBit(P78_DA_HDMI21_FRL_DETECTION_0, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), _BIT7);

            if(ScalerTimerPollingFlagProc(2, P78_DA_HDMI21_FRL_DETECTION_0, _BIT6, _TRUE) == _TRUE)
            {
                // Get CRC Result
                ulCrcResult2 = ((DWORD)ScalerGetBit(P78_DA_HDMI21_FRL_DETECTION_0, (_BIT1 | _BIT0)) << 16) | (ScalerGetByte(P78_DB_HDMI21_FRL_DETECTION_1) << 8) | ScalerGetByte(P78_E0_HDMI21_FRL_DETECTION_2);

                // if CRC1 != CRC2, it's not GAP
                if((ulCrcResult1 != ulCrcResult2) && (ulCrcResult1 != 0) && (ulCrcResult2 != 0))
                {
                    bResult = _TRUE;
                }
                else
                {
                    // Set Signal Detection flag
                    SET_HDMI_FRL_MAC_RX4_SIGNAL_DETECTING();

                    // Set Timer Event
                    ScalerTimerActiveTimerEvent(_HDMI_FRL_SIGNAL_DETECT_PERIOD, _SCALER_TIMER_EVENT_RX4_HDMI_FRL_SIGNAL_DETECT);
                }
            }
        }


        ///////////////////////////
        // turn off PHY
        ///////////////////////////

        // PHY off before turn off power
        ScalerTmdsPhyRxFrlRebuildPhyOff(enumMappingPort);

        // GDI Clock Select to Xtal
        ScalerTmdsPhyRxGdiClkSelect(_EXT_XTAL_CLK);

        // Set Mcu/Flash Clock to IOSC
        ScalerMcuFlashClockGroupSetting(_IOSC_CLK);

        // Power down M2PLL.
        ScalerPLLM2PLLPower(_OFF);

        // Power down Xtal.
        ScalerPowerXtalPower(_OFF);


        ///////////////////////////
        // turn off power
        ///////////////////////////

        // turn off PHY power
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX4_HDMI_DPHY, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_RX4_HDMI21_APHY, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);

        // turn off VCCK_off power
        ScalerPowerDomainEnableControl(_POWER_CUT_GROUP_TOPOFF, _POWER_CUT_ON, _POWER_ON_DELAY_NONE);

        // RX_LV Power off
        PCB_SET_RX_LV_POWER(_RX_LV_POWER_OFF);
    }

    return bResult;
}
#endif

//--------------------------------------------------
// Description  : PLL Off COntrol.
// Input Value  : usVCOFreq, ucPreDiv, ucOutputDiv
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4DPLLOffProc(WORD usVCOFreq, WORD usPLLinClkFreq, BYTE ucOutputDiv)
{
    BYTE ucNcode = 0;
    DWORD ulIcp = 0;

    // Power Off DPLL
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT0, _BIT0);

    // Set Rs[7:5] = 100 = 12.5k
    ScalerSetBit(P69_C5_M2PLL_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Set Icp
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Icp set 2.5uA, 3.3uA, 5uA, 10uA......                                                        //
    // Icp = N * 0.25                                                                               //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ucNcode = (BYTE)(usVCOFreq / usPLLinClkFreq);
    ulIcp = (ucNcode * 20) * 25 / (100);
    ulIcp = (ulIcp + 25) / 50;
    ulIcp -= (ulIcp == 0) ? 0 : 1;

    // Icp[2:0]
    ScalerSetBit(P69_C5_M2PLL_0, ~(_BIT2 | _BIT1 | _BIT0), (ulIcp & 0x07));

    // Set Cp[6] = 0 = 5pF, VCO Band[5:4] = 10, PI[2] = normal
    ScalerSetBit(P69_C6_M2PLL_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2), _BIT5);

    // Set IPI = 10uA
    if((6000 <= usVCOFreq) && (usVCOFreq < 7700))
    {
        ScalerSetBit(P69_C6_M2PLL_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
    // Set IPI = 5uA
    else if((5000 <= usVCOFreq) && (usVCOFreq < 6000))
    {
        ScalerSetBit(P69_C6_M2PLL_1, ~(_BIT1 | _BIT0), _BIT1);
    }
    // Set IPI = 3.33uA
    else if((4000 <= usVCOFreq) && (usVCOFreq < 5000))
    {
        ScalerSetBit(P69_C6_M2PLL_1, ~(_BIT1 | _BIT0), _BIT0);
    }
    // Set IPI = 2.5uA
    else
    {
        ScalerSetBit(P69_C6_M2PLL_1, ~(_BIT1 | _BIT0), 0x00);
    }

    // Disable Pre-Div
    ScalerSetBit(P69_C4_M2PLL_DIVIDER1, ~_BIT7, _BIT7);
    ScalerSetByte(P69_C3_M2PLL_DIVIDER0, 0x00);

    // Set Output-Div
    if(ucOutputDiv <= 8)
    {
        // analog div = 1
        ScalerSetBit(P69_C4_M2PLL_DIVIDER1, ~(_BIT1 | _BIT0), 0x00);

        // digital div = ucOutputDiv
        ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), (ucOutputDiv - 1));
    }
    else if((ucOutputDiv / 2) <= 8)
    {
        // analog div = 2
        ScalerSetBit(P69_C4_M2PLL_DIVIDER1, ~(_BIT1 | _BIT0), _BIT0);

        // digital div = (ucOutputDiv / 2) - 1
        ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), ((ucOutputDiv / 2) - 1));
    }
    else if((ucOutputDiv / 4) <= 8)
    {
        // analog div = 4
        ScalerSetBit(P69_C4_M2PLL_DIVIDER1, ~(_BIT1 | _BIT0), _BIT1);

        // digital div = (ucOutputDiv / 4) - 1
        ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), ((ucOutputDiv / 4) - 1));
    }
    else
    {
        // analog div = 8
        ScalerSetBit(P69_C4_M2PLL_DIVIDER1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // digital div = (ucOutputDiv / 8) - 1
        ScalerSetBit(P69_D0_PLL_OUT_CONTROL, ~(_BIT2 | _BIT1 | _BIT0), ((ucOutputDiv / 8) - 1));
    }

    // Set CP Enable, close loop
    // Set Vc 0.5v
    // Set LPF Enable, VCO reset set to normal
    ScalerSetBit(P69_C9_M2PLL_DUMMY, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT0));

    // Set VCO Mode
    ScalerSetBit(P69_C6_M2PLL_1, ~_BIT7, _BIT7);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(P69_C7_M2PLL_CONTROL, ~_BIT1, 0x00);
}

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Rx4 FRL Audio N Code
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetAudioNCode(BYTE ucNcode)
{
    ScalerSetBit(P73_93_PORT_PAGE73_HDMI_NF_CODE_HD21_1, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucNcode & 0x1F));
}

//--------------------------------------------------
// Description  : Set Rx4 FRL Audio F Code
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetAudioFCode(WORD usFcode)
{
    ScalerSetByte(P73_94_PORT_PAGE73_HDMI_NF_CODE_HD21_2, HIBYTE(usFcode));
    ScalerSetByte(P73_95_PORT_PAGE73_HDMI_NF_CODE_HD21_3, LOBYTE(usFcode));
}

//--------------------------------------------------
// Description  : Set Rx4 FRL Audio Clamp N Code
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerHdmiFrlMacRx4SetAudioClampNCode(void)
{
    // Set Maximum N code for Tracking
    ScalerSetByte(P73_96_PORT_PAGE73_NF_CODE_HD21_MAX, (_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE + 1));

    // Set Minimum N code for Tracking
    ScalerSetByte(P73_97_PORT_PAGE73_NF_CODE_HD21_MIN, (_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE - 1));
}
#endif
#endif // End for #if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
