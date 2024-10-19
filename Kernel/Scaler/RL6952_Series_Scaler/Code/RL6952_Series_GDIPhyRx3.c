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
// ID Code      : RL6952_Series_GDIPhyRx3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_GDIPHYRX3__

#include "ScalerFunctionInclude.h"
#include "GDIPhyRx3/ScalerGDIPhyRx3.h"





//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx3Power(EnumPowerAction enumPowerAction)
{
    EnumInputPort enumMappingPort = ScalerTmdsPhyRxRxDxMapping(_RX3);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ///////////////////////////
            // Release GDI Power Cut //
            ///////////////////////////

            // [1] reg_power_cut_dv = 0 --> Disable Power Cut
            // [0] reg_vcckoffb_dv = 1 --> Enable VCCK Off
            ScalerSetBit(P7C_16_GDI_CTRL1, ~(_BIT1 | _BIT0), _BIT0);


            ////////////////////////
            // Clock Lane Enhance //
            ////////////////////////

            // CLK Lane Initial PSM State
            ScalerSetBit(P7C_07_GDI_ACC_12, ~_BIT0, _BIT0);

            // Hysteresis OP for CMU
            ScalerSetBit(P7C_07_GDI_ACC_12, ~_BIT1, _BIT1);

            // [0] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            ScalerSetBit(P7C_0F_GDI_DCDR_04, ~_BIT7, 0x00);

            // [6] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P1D_12_ADJR_00, ~_BIT6, 0x00);


            ///////////////
            // Z0 Manual //
            ///////////////

#if(_D3_TMDS_Z0_IMPEDANCE_OPTION == _90_OHM)
            // [3:0] Z0_ADJR = 8 --> Z0 Differential Impedance = level 8
            ScalerSetBit(P7C_02_GDI_TERM_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            // [1:0] reg_z0_sel = 2'b11 --> 90Ohm
            ScalerSetBit(P7C_00_GDI_TERM_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
#else
            // [3:0] Z0_ADJR = 8 --> Z0 Differential Impedance = level 8
            ScalerSetBit(P7C_02_GDI_TERM_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            // [1:0] reg_z0_sel = 2'b01 --> 100Ohm
            ScalerSetBit(P7C_00_GDI_TERM_0, ~(_BIT1 | _BIT0), _BIT0);
#endif
            // p_channel_en = 1 --> Switch p Channel 50ohm Z0
            // n_channel_en = 1 --> Switch n Channel 50ohm Z0
            ScalerSetByte(P7C_2B_CHANNEL_EN_00, 0xFF);


            ////////////////
            // Reset DPHY //
            ////////////////

            // [2:0] phy_si_reset_n = 4'b1111 --> Normal Digital PHY
            ScalerSetBit(P1D_10_GDI_TEMP_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));


            ////////////////////
            // HDMI Interface //
            ////////////////////

            // Digital PHY Lane Swap Setting
            ScalerSetByte(P1D_FD_DATA_PATH_17, 0xE4);

            // Digital PHY P/N Swap Setting
            ScalerSetBit(P1D_EC_DATA_PATH_00, ~_BIT0, 0x00);
            ScalerSetBit(P1D_ED_DATA_PATH_01, ~_BIT0, 0x00);
            ScalerSetBit(P1D_EE_DATA_PATH_02, ~_BIT0, 0x00);
            ScalerSetBit(P1D_EF_DATA_PATH_03, ~_BIT0, 0x00);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            // TMDS Power Saving Process
            ScalerTmdsMacRxPowerSavingProc(enumMappingPort);

            // CLK Lane Initial PSM State
            ScalerSetBit(P7C_07_GDI_ACC_12, ~_BIT0, _BIT0);

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT7, _BIT7);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT6, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT5, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT4, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT3, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT2, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT1, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT0, 0x00);

            // [0] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            ScalerSetBit(P7C_0F_GDI_DCDR_04, ~_BIT7, 0x00);

            // [6] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P1D_12_ADJR_00, ~_BIT6, 0x00);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

            // Disable RGB Z0
            ScalerTmdsPhyRx3RestoreZ0Status(0x88);

#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // TMDS Power Off Process
            ScalerTmdsMacRxPowerOffProc(enumMappingPort);

            // CLK Lane Initial PSM State
            ScalerSetBit(P7C_07_GDI_ACC_12, ~_BIT0, _BIT0);

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT7, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT6, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT5, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT4, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT3, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT2, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT1, 0x00);
            DELAY_5US();
            ScalerSetBit(P7C_10_GDI_POWR_00, ~_BIT0, 0x00);

            // [0] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            ScalerSetBit(P7C_0F_GDI_DCDR_04, ~_BIT7, 0x00);

            // [6] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P1D_12_ADJR_00, ~_BIT6, 0x00);

            // [1] reg_power_cut_dv = 1 --> Enable Power Cut
            // [0] reg_vcckoffb_dv = 0 --> Disable VCCK Off
            ScalerSetBit(P7C_16_GDI_CTRL1, ~(_BIT1 | _BIT0), _BIT1);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : GDI Rx3 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx3PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx3Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

#if(_TDMS_Z0_PS_CLOCK_LANE_200OHM_SUPPORT == _ON)
            // Z0 200 ohm disable
            ScalerSetBit(P7C_02_GDI_TERM_2, ~_BIT6, 0x00);
#endif

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            if(ScalerGetBit(P7C_01_GDI_TERM_1, _BIT7) == _BIT7)
            {
                // Enable RGB Z0
                ScalerTmdsPhyRx3SetZ0Status(_ENABLE);
            }

#if(_TDMS_Z0_PS_CLOCK_LANE_200OHM_SUPPORT == _ON)
            // Z0 200 ohm disable
            ScalerSetBit(P7C_02_GDI_TERM_2, ~_BIT6, 0x00);
#endif

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            ScalerGDIPhyRx3Z0Switch(_ON);

#if(_TDMS_Z0_PS_CLOCK_LANE_200OHM_SUPPORT == _ON)
            // Z0 200 ohm disable
            ScalerSetBit(P7C_02_GDI_TERM_2, ~_BIT6, 0x00);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_TDMS_Z0_PS_CLOCK_LANE_200OHM_SUPPORT == _ON)
            // Z0 200 ohm enable
            ScalerSetBit(P7C_02_GDI_TERM_2, ~_BIT6, _BIT6);
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            ScalerGDIPhyRx3Z0Switch(_OFF);

#if((_TMDS_MAC_RX3_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            CLR_TMDS_MAC_RX3_TOGGLE_Z0();
            CLR_TMDS_MAC_RX3_TOGGLE_Z0_EVENT();
#endif
            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D3/D3 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx3Z0Switch(bit bSelect)
{
    EnumInputPort enumMappingPort = ScalerTmdsPhyRxRxDxMapping(_RX3);

    if(bSelect == _ON)
    {
        ScalerTmdsMacRxSetDigitalPort(enumMappingPort, _HIGH);
    }
    else
    {
        ScalerTmdsMacRxSetDigitalPort(enumMappingPort, _LOW);
    }

    if(bSelect == _ON)
    {
        if(ScalerGetBit(P7C_01_GDI_TERM_1, _BIT7) == 0x00)
        {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)

            ScalerTmdsMacRxSetZ0Asserted(enumMappingPort);

            // Clear HDCP Flag
            ScalerTmdsMacRxHdcpFlagClear(enumMappingPort);

            // Initialize DDC Detection Process
            ScalerMcuDdcClrDdcDetectFlag(enumMappingPort);

            // Enable DDC Toggle IRQ
            ScalerMcuDdcSetSclToggleIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort), _ENABLE);

#endif // End of #if(_TMDS_PHY_RX3_SUPPORT == _ON)

            // Enable Z0
            ScalerTmdsPhyRx3SetZ0Status(_ENABLE);
        }
    }
    else
    {
#if(_TMDS_PHY_RX3_SUPPORT == _ON)
        // Disable DDC Toggle IRQ
        ScalerMcuDdcSetSclToggleIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort), _DISABLE);
        ScalerMcuDdcSetEdidReadIrqEnable(ScalerMcuGetDdcChannelFromInputPort(enumMappingPort), _DISABLE);

        // Disable Z0
        ScalerTmdsPhyRx3SetZ0Status(_DISABLE);
#endif

#if((_RX3_PHY_HDMI_PORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
        // Backup HDCP Type
        ScalerTmdsMacRxBackupHdcpType(enumMappingPort);

        // Reset Hdcp2 Proc
        ScalerTmdsMacRxHdcp2ResetProc(enumMappingPort);
#endif
    }
}

#endif


