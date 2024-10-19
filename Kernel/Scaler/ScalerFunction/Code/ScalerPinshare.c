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
// ID Code      : ScalerPinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_PINSHARE__

#include "ScalerFunctionInclude.h"
#include "Pinshare/ScalerPinshare.h"





//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)
WORD g_usPinshareSlop;
BYTE g_ucPinshareOffset;
bit g_bPinshareSign;
#endif // #if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Low Leakage or Normal Pin Config.
// Input Value  : ON --> Low Leakage Config. ; OFF --> Normal Operation
// Output Value : None
//--------------------------------------------------
void ScalerPinshareConfig(BYTE ucPorStatus)
{
    // GPIO Config
    if(ucPorStatus == _POWER_STATUS_NORMAL)
    {
        PCB_GPIO_SETTING_POWER_NORMAL();
    }
    else if(ucPorStatus == _POWER_STATUS_SAVING)
    {
        PCB_GPIO_SETTING_POWER_SAVING();
    }
    else if(ucPorStatus == _POWER_STATUS_AC_ON)
    {
        ScalerPinshareAdjustFlashDrive();
        ScalerPinshareAdjustFlashSlewRate();
    }
    else // Power Down
    {
        PCB_GPIO_SETTING_POWER_DOWN();
    }
}

//--------------------------------------------------
// Description  : Get DP / Type-C Source Power
// Input Value  : Input Port
// Output Value : Source Power Status
//--------------------------------------------------
bit ScalerPinshareGetDPSourcePower(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            return ScalerPinshareGetTypeCDPSourcePower(_D0_INPUT_PORT);
#else
            if(PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP() == _AUX_PN_1M_PULL_HI_LOW_SWAP_ON)
            {
                return GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP();
            }
            else
            {
                return GET_PCB_D0_DP_SOURCE_POWER();
            }
#endif

        case _D1_INPUT_PORT:

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            return ScalerPinshareGetTypeCDPSourcePower(_D1_INPUT_PORT);
#else
            if(PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP() == _AUX_PN_1M_PULL_HI_LOW_SWAP_ON)
            {
                return GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP();
            }
            else
            {
                return GET_PCB_D1_DP_SOURCE_POWER();
            }
#endif

        case _D2_INPUT_PORT:

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_EMBEDDED)
            return ScalerPinshareGetTypeCDPSourcePower(_D2_INPUT_PORT);
#else
            if(PCB_GET_D2_AUX_PN_1M_PULL_H_L_SWAP() == _AUX_PN_1M_PULL_HI_LOW_SWAP_ON)
            {
                return GET_PCB_D2_DP_SOURCE_POWER_PN_SWAP();
            }
            else
            {
                return GET_PCB_D2_DP_SOURCE_POWER();
            }
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : SPI Funtion Pinshare Config check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareSPIPinGPIOCheck(void)
{
#if(_SPI0_SUPPORT == _ON)
    static_assert((
                      !(((_PIN_SPI_CLK_SELECTED_0 == _TRUE) || (_PIN_SPI_SI_SELECTED_0 == _TRUE) || (_PIN_SPI_SO_SELECTED_0 == _TRUE) || (_PIN_SPI_CEB0_SELECTED_0 == _TRUE) || (_PIN_SPI_CEB1_SELECTED_0 == _TRUE)) &&
                        ((_PIN_SPI_CLK_SELECTED_0 != _TRUE) || (_PIN_SPI_SI_SELECTED_0 != _TRUE) || (_PIN_SPI_SO_SELECTED_0 != _TRUE) || ((_PIN_SPI_CEB0_SELECTED_0 != _TRUE) && (_PIN_SPI_CEB1_SELECTED_0 != _TRUE))))),
                  "SPI-0-related pinshare configurations should be consistent. Either all four pins are configured to be SPI, or none should be.");
#endif

#if(_SPI1_SUPPORT == _ON)
    static_assert((
                      !(((_PIN_SPI_CLK_SELECTED_1 == _TRUE) || (_PIN_SPI_SI_SELECTED_1 == _TRUE) || (_PIN_SPI_SO_SELECTED_1 == _TRUE) || (_PIN_SPI_CEB0_SELECTED_1 == _TRUE) || (_PIN_SPI_CEB1_SELECTED_1 == _TRUE)) &&
                        ((_PIN_SPI_CLK_SELECTED_1 != _TRUE) || (_PIN_SPI_SI_SELECTED_1 != _TRUE) || (_PIN_SPI_SO_SELECTED_1 != _TRUE) || ((_PIN_SPI_CEB0_SELECTED_1 != _TRUE) && (_PIN_SPI_CEB1_SELECTED_1 != _TRUE))))),
                  "SPI-1-related pinshare configurations should be consistent. Either all four pins are configured to be SPI, or none should be.");
#endif

#if(_SPI2_SUPPORT == _ON)
    static_assert((
                      !(((_PIN_SPI_CLK_SELECTED_2 == _TRUE) || (_PIN_SPI_SI_SELECTED_2 == _TRUE) || (_PIN_SPI_SO_SELECTED_2 == _TRUE) || (_PIN_SPI_CEB0_SELECTED_2 == _TRUE) || (_PIN_SPI_CEB1_SELECTED_2 == _TRUE)) &&
                        ((_PIN_SPI_CLK_SELECTED_2 != _TRUE) || (_PIN_SPI_SI_SELECTED_2 != _TRUE) || (_PIN_SPI_SO_SELECTED_2 != _TRUE) || ((_PIN_SPI_CEB0_SELECTED_2 != _TRUE) && (_PIN_SPI_CEB1_SELECTED_2 != _TRUE))))),
                  "SPI-2-related pinshare configurations should be consistent. Either all four pins are configured to be SPI, or none should be.");
#endif
}

#if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TypeC ADC Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareTypeCAdcInitial(void)
{
    // -------------------- ADC Power On ---------------------

#if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
    // Enable SARADC Power (Power Cut OFF)
    ScalerPowerGroupPowerCut(_POWER_CUT_GROUP_10_BIT_SARADC, _POWER_CUT_OFF, _POWER_RESET_ENABLE);
#endif

    // -------------------- ADC Load Trimming ---------------------

#if(_FACTORY_RTD_QC_SUPPORT == _OFF)
#if(_HW_FUSE_TYPE != _TYPE_NONE)
    BYTE pucEfuseArray[_HW_OTPFUSE_TYPE_C_SARADC_TRIMDATA_LEN] = {0};

    // Read Check Bit
    if(ScalerOTPMemoryCheckDoneBit() == _TRUE)
    {
        // Read all TypeC0 PD/CC related Efuse address
        ScalerOTPMemoryReadData(_OTPMEMORY_TYPE_C_SARADC_TRIMDATA, &pucEfuseArray[0]);

        // Set SARADC LDO
#if (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)
        ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT3 | _BIT2 | _BIT1), ((pucEfuseArray[0] & 0xE0) >> 4));
#elif (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
        ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pucEfuseArray[0] & 0x0F));
#endif

        // Set ADC Slop and Offset
        // Slop*1000
        g_usPinshareSlop = (((WORD)pucEfuseArray[1] * 256) + pucEfuseArray[2]);

        // Offset
        g_ucPinshareOffset = (pucEfuseArray[3] & 0x7F);
        g_bPinshareSign = ((pucEfuseArray[3] & 0x80) >> 7);

        // Avoid Unreasonable Gain/Offset
        if((g_usPinshareSlop > 3000) || (g_usPinshareSlop < 1000) || (g_ucPinshareOffset > 200))
        {
            // Ideal slop*1000 = (2000 / 1024) * 1000 = 1953.125
            g_usPinshareSlop = 1953;

            // Ideal Offset
            g_ucPinshareOffset = 0;
        }
    }
    else
#endif
#endif
    {
        // Set SARADC LDO to 2V when no trimming
        if(ScalerTypeCAdcGetLdoBandgapCoverSupport() == _TRUE)
        {
#if (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)
            ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
#elif (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
            ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
        }
        else
        {
#if (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)
            ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));
#elif (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
            ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
        }

        // Ideal slop*1000 = (2000 / 1024) * 1000 = 1953.125
        g_usPinshareSlop = 1953;

        // Ideal Offset
        g_ucPinshareOffset = 0;

        // Ideal Sign
        g_bPinshareSign = 0;
    }

    // -------------------- ADC AIF Setting ------------------------

#if (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
    // [0x7F55] LDO Setting : [7] pow_sar_vref = Disable
    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT7, 0x00);
#endif

    // [0x7F55] LDO Setting : [5] reg_sar_ckout_sel = Reserve ckout / [4] reg_ldo_trim = LDO Normal Mode
    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT5 | _BIT4), _BIT5);

    // [0x7F59] Low Pass Filter Setting
    ScalerSetBit(P7F_59_ADC_LPF, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // -------------------- ADC Output Setting ---------------------

    // [0x7F01] ADC Output Channel Disable
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // [0x7F05] [2:0]ADC Number of Outputs Averaged (1/2/4/8/16/32) = 16
    ScalerSetBit(P7F_05_10B_ADC_AVE_CTRL, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // [0x7F07-08] ADC Switch Time (#ADC_CLK Cycles) = 8 * 12 clk cycles
    ScalerSetBit(P7F_07_10B_ADC_SW_TM0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P7F_08_10B_ADC_SW_TM1, 0x60);

    // [0x7F09-0A] ADC Idle Time (#ADC_CLK Cycles) = 0 clk cycle
    ScalerSetBit(P7F_09_10B_ADC_IDLE_TM0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P7F_0A_10B_ADC_IDLE_TM1, 0x00);

    // Enable SARADC LDO
    ScalerSetBit(P7F_00_10B_ADC_CTL, ~_BIT4, _BIT4);

#if (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
    // Enable SARADC VREF Enable
    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerTimerDelayXms(2);

    // [0x7F00] ADC Mode Setting : [7] Normal Mode / [6] Auto Mode = Enable / [5] ADC En = Enable
    ScalerSetBit(P7F_00_10B_ADC_CTL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

    // [0x7F01] ADC Output Channel 2/1/0 Enable
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));
}

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_0_VMON) / 1 (_TYPE_C_1_VMON) / 2 (_TYPE_C_LOC_PW)
// Output Value : None
//--------------------------------------------------
WORD ScalerPinshareTypeCAdcGetAdcIdealData(EnumTypeC10BitAdcChannel enumChannel)
{
    DWORD ulResult = 0;
    DWORD ulAx = 0;
    DWORD ulB = 0;

    // =================
    // Get ADC Output
    // =================

    // [0x7F02] [4:0] Write Valid Output Bit to Get New Value From ADC
    ScalerSetBit(P7F_02_10B_ADC_OUTPUT, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));

    // Polling Valid Output Bit (will be 1 when the New Output is Put into Register [0x7F10-19])
    if(ScalerTimerPollingFlagProc(_ADC_OUTPUT_MAX_TIME, P7F_02_10B_ADC_OUTPUT, (_BIT0 << enumChannel), (_BIT0 << enumChannel)) == _TRUE)
    {
        BYTE ucResult_h = (ScalerGetByte(P7F_10_10B_ADC_A0_RSLT_H + (enumChannel * 2)));
        BYTE ucResult_l = (ScalerGetByte(P7F_11_10B_ADC_A0_RSLT_L + (enumChannel * 2))) & (_BIT1 | _BIT0);

        // usResult [9:0] = {RSLT_H[7:0] | RSLT[1:0]}
        ulResult = ((ucResult_h << 2) | (ucResult_l));
    }

    // =================
    // Start Correction
    // =================

    ulAx = (DWORD)(g_usPinshareSlop) * ulResult / 1000;
    ulB = g_ucPinshareOffset;

    // check offset is positive or negative
    if(g_bPinshareSign == 0x01)
    {
        if(ulAx > ulB)
        {
            ulResult = ((ulAx - ulB) * 512 / 1000);
        }
        else
        {
            ulResult = 0;
        }
    }
    else
    {
        ulResult = ((ulAx + ulB) * 512 / 1000);
    }

    // =================
    // Overflow Check
    // =================
    if(ulResult > 1023)
    {
        return 1023;
    }

    return (WORD)ulResult;
}
#endif

