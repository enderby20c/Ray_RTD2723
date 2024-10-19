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
// ID Code      : ScalerTypeCAdc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeCAdc/ScalerTypeCAdc.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if((_EMB_TYPE_C_0_PD3_1_EPR_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE == 2400) || (_EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO == 12)))
#warning "NOTE: '_EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE' and '_EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO' Should be modified based on PCB when Type-C 0 support EPR Mode!"
#endif // End of #if((_EMB_TYPE_C_0_PD3_1_EPR_SUPPORT) && ((_EMB_TYPE_C_0_PMIC_VBUS_MAX_VOLTAGE == 2400) || (_EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO == 12)))
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if((_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON) && ((_EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE == 2400) || (_EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO == 12)))
#warning "NOTE: '_EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE' and '_EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO' Should be modified based on PCB when Type-C 1 support EPR Mode!"
#endif // End of #if((_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT) && ((_EMB_TYPE_C_1_PMIC_VBUS_MAX_VOLTAGE == 2400) || (_EMB_TYPE_C_1_PMIC_VBUS_TO_ADC_INPUT_RATIO == 12)))
#endif

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
#warning "NOTE: Please modify 'UserInterfaceUsbTypeCGetLocalPow' to make sure Local Power Status is expected when '_LOCAL_POWER_VBUS_ADC_CHANNEL' == '_TYPE_C_PMIC_ADC_MAPPING_NONE'!"
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTypeCAdcTrimming g_stTypeCAdcTrimming;

StructTypeCAdcLocalPowerInfo g_stTypeCAdcLocalPowerInfo;

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
StructTypeCAdcInfo g_stTypeCAdc0PowerInfo;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
StructTypeCAdcInfo g_stTypeCAdc1PowerInfo;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Type C ADC Clk Setting (Always Use IOSC = 28MHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcClkSel(BYTE ucClockSel)
{
    if(ucClockSel == _IOSC_CLK)
    {
        // [0x7F03] [7:6] Clk Sel = IOSC (b'00) / [5:0] adc_clk_div = b'0004
        ScalerSetByte(P7F_03_10B_ADC_CLK_CLRT, 0x05);
    }
}

//--------------------------------------------------
// Description  : TypeC ADC Initail Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcInitial(void)
{
    BYTE ucAdcRegTemp = 0x00;

    ucAdcRegTemp = ucAdcRegTemp;

    // -------------------- ADC AIF Setting ------------------------

    ScalerTypeCAdcLoadTrimming();

#if (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
    // [0x7F55] LDO Setting : [7] pow_sar_vref = Disable
    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT7, 0x00);
#endif

    // [0x7F55] LDO Setting : [5] reg_sar_ckout_sel = Reserve ckout / [4] reg_ldo_trim = LDO Normal Mode
    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT5 | _BIT4), _BIT5);

    // [0x7F59] Low Pass Filter Setting
    ScalerSetBit(P7F_59_ADC_LPF, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

#if((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) && (_EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT == _ON))
    // [0x7F56] Fast Role Swap Comparator Setting ([7:6] Vth2 = 4.2, 7.2, 9.6 & 16.2V)
    ScalerSetBit(P7F_56_FRS_VBUS_COMP0, ~(_BIT7 | _BIT6), _BIT7);

    // [0x7F57] Fast Role Swap Comparator Setting 2
    // [6] Vbus Comp 2 Result = Vmon < Vth, [2] Vbus Comp 2 Vth Selection = 2-bit Vth
    ScalerSetBit(P7F_57_FRS_VBUS_COMP1, ~(_BIT6 | _BIT2), (_BIT2));
#endif

    // -------------------- ADC Output Setting ---------------------

    // [0x7F05] [2:0]ADC Number of Outputs Averaged (1/2/4/8/16/32) = 16
    ScalerSetBit(P7F_05_10B_ADC_AVE_CTRL, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // [0x7F07-08] ADC Switch Time (#ADC_CLK Cycles) = 8 * 12 clk cycles
    ScalerSetBit(P7F_07_10B_ADC_SW_TM0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P7F_08_10B_ADC_SW_TM1, 0x60);

    // [0x7F09-0A] ADC Idle Time (#ADC_CLK Cycles) = 0 clk cycle
    ScalerSetBit(P7F_09_10B_ADC_IDLE_TM0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P7F_0A_10B_ADC_IDLE_TM1, 0x00);

    // [0x7F01] ADC Output Channel Disable
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

#if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
    // [0x7F01] ADC Output Channel Enable
    // [7:6] Channel4/3 (DFP_VOMN/IMON) Enable
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6));

    // Debounce for Channel of DFP
    ScalerSetByte(P7F_0E_10B_ADC_A3_DEB_CLRT, 0x02);
    ScalerSetByte(P7F_0F_10B_ADC_A4_DEB_CLRT, 0x02);

    // Set Debounce For DFP Vbus On/Off Comparator Detection
    ScalerTypeCAdcOnOffCompIntDebounce(_TYPE_C_DFP_VMON, _ON, 0x02);
    ScalerTypeCAdcOnOffCompIntDebounce(_TYPE_C_DFP_VMON, _OFF, 0x02);
#endif

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)
#if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))
    // [0x7F01] ADC Output Channel Enable
    // Store register value
    ucAdcRegTemp = ScalerGetByte(P7F_01_10B_ADC_CH_EN);

    // Enable Channel of Local Power
    ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (ucAdcRegTemp | (_BIT3 << _LOCAL_POWER_VBUS_ADC_CHANNEL)));

    // Debounce for Channel of LOC_PW
    ScalerSetByte((P7F_0B_10B_ADC_A0_DEB_CLRT + _LOCAL_POWER_VBUS_ADC_CHANNEL), 0x02);
#endif

    // Set Debounce For Local Power On/Off Comparator Detection
    ScalerTypeCAdcOnOffCompIntDebounce(_TYPE_C_CHANNEL_2_LOC_PW_VMON, _ON, 0x02);
    ScalerTypeCAdcOnOffCompIntDebounce(_TYPE_C_CHANNEL_2_LOC_PW_VMON, _OFF, 0x02);

#if((_EMB_TYPE_C_0_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT) && (_EMB_TYPE_C_1_MAPPING != _VALUE_ADAPTOR_TYPE_C_PORT))
    // Set ON/OFF Range
    SET_TYPE_C_LOC_PW_ON_THR(_TYPE_C_ADAPTOR_VOLTAGE * 9 / 10);
    SET_TYPE_C_LOC_PW_OFF_THR(_TYPE_C_ADAPTOR_VOLTAGE * 8 / 10);
#elif(_EMB_TYPE_C_0_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
    // Set ON/OFF Range
    SET_TYPE_C_LOC_PW_ON_THR(_TYPE_C_0_VSAFE5V_LOW_BND);
    SET_TYPE_C_LOC_PW_OFF_THR(_TYPE_C_0_UNATTACH5V_AVG);
#elif(_EMB_TYPE_C_1_MAPPING == _VALUE_ADAPTOR_TYPE_C_PORT)
    // Set ON/OFF Range
    SET_TYPE_C_LOC_PW_ON_THR(_TYPE_C_1_VSAFE5V_LOW_BND);
    SET_TYPE_C_LOC_PW_OFF_THR(_TYPE_C_1_UNATTACH5V_AVG);
#endif

    // Reset ADC Channel of Local Power
    ScalerTypeCAdcLocPowReset();
#endif

    // Enable SARADC LDO
    ScalerSetBit(P7F_00_10B_ADC_CTL, ~_BIT4, _BIT4);

#if (_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
    // Enable SARADC VREF Enable
    ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerTimerDelayXms(2);

    // [0x7F00] ADC Mode Setting : [7] Normal Mode / [6] Auto Mode = Enable / [5] ADC En = Enable
    ScalerSetBit(P7F_00_10B_ADC_CTL, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));
}

//--------------------------------------------------
// Description  : TypeC ADC Initail Setting
// Input Value  : enumTypeCIndex : Embedded Type-C Port
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcPortInitial(EnumTypeCEmbeddedList enumTypeCIndex)
{
    BYTE ucAdcRegTemp = 0x00;

    // -------------------- ADC Output Setting ---------------------
    if(enumTypeCIndex == _EMB_TYPE_C_0)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if(_EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT == _ON)
        // [0x7F57] Fast Role Swap Comparator Setting
        // [4] Vbus Comp 0 Result = Vmon < Vth, [0] Vbus Comp 0 Vth Selection = 6-bit Vth
        ScalerSetBit(P7F_57_FRS_VBUS_COMP1, ~((_BIT4 | _BIT0) << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL), 0x00);
#endif

        // [0x7F01] ADC Output Channel Enable
        // Store register value
        ucAdcRegTemp = ScalerGetByte(P7F_01_10B_ADC_CH_EN);
#if((_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) ||\
    (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1) ||\
    (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2) ||\
    (_EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))
        // Channel of Type-C 0 VOMN & IOUT Enable
        ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (ucAdcRegTemp | (_BIT3 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL) | (_BIT3 << _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL)));
#else
        // Channel of Type-C 0 VOMN Enable
        ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (ucAdcRegTemp | (_BIT3 << _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL)));
#endif

        // Debounce for Channel of Type-C 0 VOMN
        ScalerSetByte((P7F_0B_10B_ADC_A0_DEB_CLRT + _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL), 0x02);

        // Debounce Time Setting
        // Set Debounce For Type-C 0 Vbus On/Off Comparator Detection
        ScalerTypeCAdcOnOffCompIntDebounce(_TYPE_C_CHANNEL_0_VMON, _ON, 0x02);
        ScalerTypeCAdcOnOffCompIntDebounce(_TYPE_C_CHANNEL_0_VMON, _OFF, 0x02);

        // Fast Role Swap Setting
        // [0x7F75] ADC Switch Setting : [3:2] CC HW Det = V0 Vbus
        ScalerSetBit(P7F_75_FRS_SIG_CTRL_TC0, ~(_BIT3 | _BIT2), (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL << 2));

        // [0x7F75] ADC Switch Setting : [5:4] FR_SWAP Comp = V0 Vbus
        ScalerSetBit(P7F_75_FRS_SIG_CTRL_TC0, ~(_BIT5 | _BIT4), (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL << 4));

        // Initiate Avaliable Power = PMIC Max Power
        // Reset ADC Related Flags
        SET_TYPE_C_0_VBUS_STATUS(_OFF);
        SET_TYPE_C_0_REQ_PWR(0);
        SET_TYPE_C_0_5V_UP_BND(_TYPE_C_0_VSAFE5V_UP_BND);
        SET_TYPE_C_0_5V_LOW_BND(_TYPE_C_0_VSAFE5V_LOW_BND);
        SET_TYPE_C_0_0V_UP_BND(_TYPE_C_0_VSAFE0V_UP_BND);
#endif
    }
    else if(enumTypeCIndex == _EMB_TYPE_C_1)
    {
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
        // [0x7F57] Fast Role Swap Comparator Setting
        // [5] Vbus Comp 1 Result = Vmon < Vth, [1] Vbus Comp 1 Vth Selection = 6-bit Vth
        ScalerSetBit(P7F_57_FRS_VBUS_COMP1, ~((_BIT4 | _BIT0) << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL), 0x00);
#endif

        // [0x7F01] ADC Output Channel Enable
        // Store register value
        ucAdcRegTemp = ScalerGetByte(P7F_01_10B_ADC_CH_EN);
#if((_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) ||\
    (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1) ||\
    (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2) ||\
    (_EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))
        // Channel of Type-C 1 VOMN Enable
        ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (ucAdcRegTemp | (_BIT3 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL) | (_BIT3 << _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL)));

#else
        // Channel of Type-C 1 VOMN Enable
        ScalerSetBit(P7F_01_10B_ADC_CH_EN, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (ucAdcRegTemp | (_BIT3 << _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL)));
#endif

        // Debounce for Channel of Type-C 1 VOMN
        ScalerSetByte((P7F_0B_10B_ADC_A0_DEB_CLRT + _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL), 0x02);

        // Debounce Time Setting
        // Set Debounce For Type-C 1 Vbus On/Off Comparator Detection
        ScalerTypeCAdcOnOffCompIntDebounce(_TYPE_C_CHANNEL_1_VMON, _ON, 0x02);
        ScalerTypeCAdcOnOffCompIntDebounce(_TYPE_C_CHANNEL_1_VMON, _OFF, 0x02);

        // Fast Role Swap Setting
        // [0x7F76] ADC Switch Setting : [3:2] CC HW Det = V1 Vbus
        ScalerSetBit(P7F_76_FRS_SIG_CTRL_TC1, ~(_BIT3 | _BIT2), (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL << 2));

        // [0x7F76] ADC Switch Setting : [5:4] FR_SWAP Comp = V1 Vbus
        ScalerSetBit(P7F_76_FRS_SIG_CTRL_TC1, ~(_BIT5 | _BIT4), (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL << 4));

        // Initiate Avaliable Power = PMIC Max Power
        // Reset ADC Related Flags
        SET_TYPE_C_1_VBUS_STATUS(_OFF);
        SET_TYPE_C_1_REQ_PWR(0);
        SET_TYPE_C_1_5V_UP_BND(_TYPE_C_1_VSAFE5V_UP_BND);
        SET_TYPE_C_1_5V_LOW_BND(_TYPE_C_1_VSAFE5V_LOW_BND);
        SET_TYPE_C_1_0V_UP_BND(_TYPE_C_1_VSAFE0V_UP_BND);
#endif
    }
}

//--------------------------------------------------
// Description  : Load Trimming Value From E-Fuse
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLoadTrimming(void)
{
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
        g_stTypeCAdcTrimming.usSlop = (((WORD)pucEfuseArray[1] * 256) + pucEfuseArray[2]);

        // Offset
        g_stTypeCAdcTrimming.ucOffset = (pucEfuseArray[3] & 0x7F);
        g_stTypeCAdcTrimming.b1Sign = ((pucEfuseArray[3] & 0x80) >> 7);

        // Avoid Unreasonable Gain/Offset
        if((g_stTypeCAdcTrimming.usSlop > 3000) || (g_stTypeCAdcTrimming.usSlop < 1000) || (g_stTypeCAdcTrimming.ucOffset > 200))
        {
            // Ideal slop*1000 = (2000 / 1024) * 1000 = 1953.125
            g_stTypeCAdcTrimming.usSlop = 1953;

            // Ideal Offset
            g_stTypeCAdcTrimming.ucOffset = 0;
        }

#if((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) && (_EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT == _ON))
        // Vbus 6-bit Comparator
        // [0x7F56] Fast Role Swap Comparator Setting ([5:0] Vth = 250 ~ 565 mV, Delta = 5mV)
        ScalerSetBit(P7F_56_FRS_VBUS_COMP0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucEfuseArray[4 + (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0)] & 0x3F));
#endif
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
        g_stTypeCAdcTrimming.usSlop = 1953;

        // Ideal Offset
        g_stTypeCAdcTrimming.ucOffset = 0;

        // Ideal Sign
        g_stTypeCAdcTrimming.b1Sign = 0;

#if((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) && (_EMB_TYPE_C_0_PD3_FRSWAP_SUPPORT == _ON))
        // Vbus 6-bit Comparator Vth: 0.360V
        // [0x7F56] Fast Role Swap Comparator Setting ([5:0] Vth = 250 ~ 565 mV, Delta = 5mV)
        ScalerSetBit(P7F_56_FRS_VBUS_COMP0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x16);
#endif
    }
}

//--------------------------------------------------
// Description  : Get Local Power (Adaptor or Power Board) Status
// Input Value  : None
// Output Value : EnumTypeCLocalPowerExist (_TYPE_C_LOCAL_POWER_NOT_EXIST / _TYPE_C_LOCAL_POWER_EXIST)
//--------------------------------------------------
EnumTypeCLocalPowerExist ScalerTypeCAdcGetLocPowExist(void)
{
    return GET_TYPE_C_LOC_PW_EXIST();
}

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)
//--------------------------------------------------
// Description  : Reset ADC Local Power Channel Threshold to Default Value and Disable IRQs
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLocPowReset(void)
{
    // 1. Disable Local Power Range Detection IRQ
    ScalerTypeCAdcInOutCompIntControl(_TYPE_C_CHANNEL_2_LOC_PW_VMON, _DISABLE);

    // 2. Disable Local Power Digital Comparator On/Off Detection IRQs
    ScalerTypeCAdcOnOffCompIntControl(_TYPE_C_CHANNEL_2_LOC_PW_VMON, _ON, _DISABLE);
    ScalerTypeCAdcOnOffCompIntControl(_TYPE_C_CHANNEL_2_LOC_PW_VMON, _OFF, _DISABLE);

    // 3. Reset Local Power Didital Comparator On/Off Detection Threshold
    ScalerTypeCAdcOnOffCompIntSetting(_TYPE_C_CHANNEL_2_LOC_PW_VMON, _ON, GET_TYPE_C_LOC_PW_ON_THR());
    ScalerTypeCAdcOnOffCompIntSetting(_TYPE_C_CHANNEL_2_LOC_PW_VMON, _OFF, GET_TYPE_C_LOC_PW_OFF_THR());
}

//--------------------------------------------------
// Description  : Check if Local Power (Adaptor or Power Board) Exists
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcCheckLocPowExist(void)
{
#if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))
    DWORD ulResult = ScalerTypeCAdcGetAdcOutput((EnumTypeCAdcChannel)_LOCAL_POWER_VBUS_ADC_CHANNEL);

    if(ulResult >= GET_TYPE_C_LOC_PW_ON_THR())
    {
        SET_TYPE_C_LOC_PW_EXIST(_TYPE_C_LOCAL_POWER_EXIST);
    }
    else if(ulResult < GET_TYPE_C_LOC_PW_OFF_THR())
    {
        SET_TYPE_C_LOC_PW_EXIST(_TYPE_C_LOCAL_POWER_NOT_EXIST);
    }

    // Clear Local Power On/Off IRQ Flag For Update Next Time
    ScalerSetByte(P7F_3A_10B_ADC_VBUS_INT, ((_BIT4 | _BIT0) << _LOCAL_POWER_VBUS_ADC_CHANNEL));

#else
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3))
    // Check Local Power On IRQ Flag
    if(ScalerGetBit(P7F_CC_ADC_VBUS_INT, (_BIT0 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))) == (_BIT0 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0)))
    {
        SET_TYPE_C_LOC_PW_EXIST(_TYPE_C_LOCAL_POWER_EXIST);
    }

    // Check Local Power Off IRQ Flag
    if(ScalerGetBit(P7F_CC_ADC_VBUS_INT, (_BIT4 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0))) == (_BIT4 << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0)))
    {
        SET_TYPE_C_LOC_PW_EXIST(_TYPE_C_LOCAL_POWER_NOT_EXIST);
    }

    // Clear Local Power On/Off IRQ Flag For Update Next Time
    ScalerSetByte(P7F_CC_ADC_VBUS_INT, ((_BIT4 | _BIT0) << (_LOCAL_POWER_VBUS_ADC_CHANNEL - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0)));

#endif // End of #if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3))
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#endif // End of #if((_LOCAL_POWER_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0) && (_LOCAL_POWER_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3))
}
#else
//--------------------------------------------------
// Description  : Set Local Power (Adaptor or Power Board) Status
// Input Value  : EnumTypeCLocalPowerExist (_TYPE_C_LOCAL_POWER_NOT_EXIST / _TYPE_C_LOCAL_POWER_EXIST)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcSetLocPowExist(EnumTypeCLocalPowerExist enumLocPowExist)
{
    SET_TYPE_C_LOC_PW_EXIST(enumLocPowExist);
}
#endif // End of #if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)

//--------------------------------------------------
// Description  : Correction Raw Data to Ideal Data
// Input Value  : ADC_Code (0 ~ 1024)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcCorrectionToIdealData(EnumTypeCAdcChannel enumChannel, WORD usRawData)
{
    DWORD ulResult = (DWORD)(usRawData);
    DWORD ulAx = 0;
    DWORD ulB = 0;
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:

            ulAx = (DWORD)(g_stTypeCAdcTrimming.usSlop) * ulResult / 1000;
            ulB = g_stTypeCAdcTrimming.ucOffset;

            // check offset is positive or negative
            if(g_stTypeCAdcTrimming.b1Sign == 0x01)
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

            return (WORD)ulResult;

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return (WORD)ulResult;

            break;
#endif

        default:
            break;
    }

    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcCorrectionToRawData(EnumTypeCAdcChannel enumChannel, WORD usIdealVoltage)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            return ScalerTypeCAdc10BitAdcCorrectionToRawData(usIdealVoltage);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return ScalerTypeCAdcLsAdcCorrectionToRawData(usIdealVoltage);

            break;
#endif

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            return ScalerTypeCAdcLsAdcCorrectionToRawData(usIdealVoltage);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Reset ADC UFP Vbus Channel (ch1/2) Threshold to Default Value and Disable IRQs
// Input Value  : enumTypeCIndex: _EMB_TYPE_C_0 / _EMB_TYPE_C_1
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcUnattachReset(EnumTypeCEmbeddedList enumTypeCIndex)
{
    if(enumTypeCIndex == _EMB_TYPE_C_0)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // Reset Local Power Digital Comparator On/Off Detection Threshold to 4.6V
        ScalerTypeCAdcOnOffCompIntSetting(_TYPE_C_CHANNEL_0_VMON, _ON, GET_TYPE_C_0_5V_LOW_BND());

        // [WS116] Lecroy TD.4.7.2 Try.SNK DRP Connect DRP Test, We shall not Check vSafe0V(0.8V) from Unattached.SRC to AttachWait.SRC
        // HW Solution, Directly Use Optional Bit [0x6637[1]/0x6C37[1]] to Disable Checking vSafe0V(0.8V)
        ScalerTypeCAdcOnOffCompIntSetting(_TYPE_C_CHANNEL_0_VMON, _OFF, GET_TYPE_C_0_0V_UP_BND());
#endif
    }
    else if(enumTypeCIndex == _EMB_TYPE_C_1)
    {
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // Reset Local Power Digital Comparator On/Off Detection Threshold to 4.6V
        ScalerTypeCAdcOnOffCompIntSetting(_TYPE_C_CHANNEL_1_VMON, _ON, GET_TYPE_C_1_5V_LOW_BND());

        // [WS116] Lecroy TD.4.7.2 Try.SNK DRP Connect DRP Test, We shall not Check vSafe0V(0.8V) from Unattached.SRC to AttachWait.SRC
        // HW Solution, Directly Use Optional Bit [0x6637[1]/0x6C37[1]] to Disable Checking vSafe0V(0.8V)
        ScalerTypeCAdcOnOffCompIntSetting(_TYPE_C_CHANNEL_1_VMON, _OFF, GET_TYPE_C_1_0V_UP_BND());
#endif
    }
}

//--------------------------------------------------
// Description  : Set Vbus Threshold When Attached
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3 (_TYPE_C_DFP_VMON)
//                usVoltage : Negotiated Voltage in 10mV
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcUnattachVthAdjust(EnumTypeCAdcChannel enumChannel, WORD usVoltage)
{
    // Sink Unattach Voltage "Refer to CC Spec Table 4-3" (Unit:10mV)
    if(usVoltage == 500)
    {
        // When PD Contract = 5V or No PD : Use 3.67V (367 * 10mV)
        // Adjust Sink Unattach Vth (usVoltage * 10 / 100 = usVoltage / 10)
        usVoltage = ScalerTypeCAdcCorrectionToRawData(enumChannel, 367 / 10);
    }
    else
    {
        // When PD Contract Above 5V : [(Vnew * 0.95) - 1250mV] * 0.9
        // Adjust Sink Unattach Vth (usVoltage * 10 / 100 = usVoltage / 10)
        usVoltage = ScalerTypeCAdcCorrectionToRawData(enumChannel, (((usVoltage * 19 / 20) - 125) * 9 / 10) / 10);
    }

    // Adjust Sink Unattach Vth
    ScalerTypeCAdcOnOffCompIntSetting(enumChannel, _ON, usVoltage);

    // Only Need to Adjust Vbus_On_Thr(Vbus Detect) for SNK CC HW FSM When [0x6634[2]/0x6C34[2]]=1(Vbus Detect has 2 Threshold)
    // ScalerTypeCAdcOnOffCompIntSetting(enumChannel, _OFF, usVoltage);
}

//--------------------------------------------------
// Description  : Check if UFP Vbus Voltage is vSafe0V
// Input Value  : None
// Output Value : 0 : Not vSafe0V / 1 : Vbus is vSafe0V
//--------------------------------------------------
bit ScalerTypeCAdcCheckVbusSafe0V(EnumTypeCEmbeddedList enumTypeCIndex)
{
    if(enumTypeCIndex == _EMB_TYPE_C_0)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_ADC_DEBUG == _ON))
        DebugMessageTypeC("    [PWR CHK] Vbus Vol : ", ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON));
        DebugMessageTypeC("    [PWR CHK] vSafe0v Vol Max: ", GET_TYPE_C_0_0V_UP_BND());
#endif

        if(ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) <= GET_TYPE_C_0_0V_UP_BND())
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
#endif
    }
    else if(enumTypeCIndex == _EMB_TYPE_C_1)
    {
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_ADC_DEBUG == _ON))
        DebugMessageTypeC("    [PWR CHK] Vbus Vol : ", ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON));
        DebugMessageTypeC("    [PWR CHK] vSafe0v Vol Max: ", GET_TYPE_C_1_0V_UP_BND());
#endif

        if(ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) <= GET_TYPE_C_1_0V_UP_BND())
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if UFP Vbus Voltage is vSafe5V
// Input Value  : enumTypeCIndex : _EMB_TYPE_C_0 / _EMB_TYPE_C_1
// Output Value : 0 : Not vSafe5V / 1 : Vbus is vSafe5V
//--------------------------------------------------
bit ScalerTypeCAdcCheckVbusSafe5V(EnumTypeCEmbeddedList enumTypeCIndex)
{
    if(enumTypeCIndex == _EMB_TYPE_C_0)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_ADC_DEBUG == _ON))
        DebugMessageTypeC("    [PWR CHK] Vbus Vol : ", ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON));
        DebugMessageTypeC("    [PWR CHK] vSafe5v Vol Min : ", GET_TYPE_C_0_5V_LOW_BND());
#endif

        if((ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) >= GET_TYPE_C_0_5V_LOW_BND()) && (ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) <= GET_TYPE_C_0_5V_UP_BND()))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
#endif
    }
    else if(enumTypeCIndex == _EMB_TYPE_C_1)
    {
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_ADC_DEBUG == _ON))
        DebugMessageTypeC("    [PWR CHK] Vbus Vol : ", ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON));
        DebugMessageTypeC("    [PWR CHK] vSafe5v Vol Min : ", GET_TYPE_C_1_5V_LOW_BND());
#endif

        if((ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) >= GET_TYPE_C_1_5V_LOW_BND()) && (ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) <= GET_TYPE_C_1_5V_UP_BND()))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
#endif
    }

    return _FALSE;
}

/*
//--------------------------------------------------
// Description  : Check if UFP Vbus Voltage is in the Requested Range
// Input Value  : usVoltage : Unit = 50mV
// Output Value : _TRUE / _FLASE
//--------------------------------------------------
bit ScalerTypeCAdcCheckVbusReady(WORD usVoltage)
{
    if(usVoltage == 100)
    {   // Check Vbus = vSafe5V (4.5 ~ 5.5 V)
        if(enumTypeCIndex == _EMB_TYPE_C_0)
        {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if((ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) >= (WORD)((DWORD)usVoltage * 213 / 100 * 9 / 10)) &&
               (ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) <= (WORD)((DWORD)usVoltage * 213 / 100 * 11 / 10)))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif
        }
        else if(enumTypeCIndex == _EMB_TYPE_C_1)
        {
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if((ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) >= (WORD)((DWORD)usVoltage * 213 / 100 * 9 / 10)) &&
               (ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) <= (WORD)((DWORD)usVoltage * 213 / 100 * 11 / 10)))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif
        }
    }
    else if(usVoltage == 0)
    {   // Check Vbus = vSafe0V
        if(enumTypeCIndex == _EMB_TYPE_C_0)
        {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if(ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) <= GET_TYPE_C_0_0V_UP_BND())
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif
        }
        else if(enumTypeCIndex == _EMB_TYPE_C_1)
        {
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if(ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) <= GET_TYPE_C_1_0V_UP_BND())
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif
        }
    }
    else
    {   // Check Other Voltage Reange (0.95 ~ 1.05 vSrcNew) : 2.13 = [usVoltage * 50mV * 1024(10-bit)] / [24(Max Vol) * 1000]
        if(enumTypeCIndex == _EMB_TYPE_C_0)
        {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if((ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) >= (WORD)((DWORD)usVoltage * 213 / 100 * 95 / 100)) &&
               (ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_0_VMON) <= (WORD)((DWORD)usVoltage * 213 / 100 * 105 / 100)))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif
        }
        else if(enumTypeCIndex == _EMB_TYPE_C_1)
        {
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if((ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) >= (WORD)((DWORD)usVoltage * 213 / 100 * 95 / 100)) &&
               (ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) <= (WORD)((DWORD)usVoltage * 213 / 100 * 105 / 100)))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif
        }
    }
}
*/

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcGetAdcOutput(EnumTypeCAdcChannel enumChannel)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            return ScalerTypeCAdc10BitAdcGetAdcOutput((Enum10BitAdcChannel)enumChannel);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return ScalerTypeCAdcLsAdcGetAdcOutput((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0));

            break;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3:

            return ScalerTypeCAdcLsAdcGetAdcOutput((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0));

            break;
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdc10BitAdcGetAdcOutput(Enum10BitAdcChannel enumChannel)
{
    DWORD ulResult = 0;

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
    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcLsAdcGetAdcOutput(EnumLsAdcChannel enumChannel)
{
    DWORD ulResult = 0;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    // Transfer 5-bit ADC to 10-bit result
    ulResult = (WORD)(ScalerGetBit(PFF_09_ADC_A0_CONVERT_RESULT + enumChannel, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3))) << 2;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    // Transfer 8-bit ADC to 10-bit result
    if(enumChannel <= _LS_ADC_0_3)
    {
        ulResult = (WORD)(ScalerGetByte(PFD_3B_ADC_A0_CONVERT_RESULT + enumChannel)) << 2;
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ulResult = (WORD)(ScalerGetByte(PFF_09_ADC_A0_CONVERT_RESULT + (enumChannel - _LS_ADC_1_0))) << 2;
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Debounce Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus_On_Debounce) / _OFF (Vbus_Off_Debounce)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcOnOffCompIntDebounce(EnumTypeCAdcChannel enumChannel, bit bType, BYTE ucDebCycle)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcOnOffCompIntDebounce((Enum10BitAdcChannel)enumChannel, bType, ucDebCycle);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            ScalerTypeCAdcLsAdcOnOffCompIntDebounce((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bType, ucDebCycle);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcOnOffCompIntControl(EnumTypeCAdcChannel enumChannel, bit bType, bit bAction)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcOnOffCompIntControl((Enum10BitAdcChannel)enumChannel, bType, bAction);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            ScalerTypeCAdcLsAdcOnOffCompIntControl((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bType, bAction);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 2 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcOnOffCompIntSetting(EnumTypeCAdcChannel enumChannel, bit bType, WORD usThreshold)
{
    BYTE ucAdcMapping = enumChannel;

    // Clip Threshold to Valid Value (Not More than 10-bit)
    usThreshold = usThreshold & (0x03FF);

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcOnOffCompIntSetting((Enum10BitAdcChannel)enumChannel, bType, usThreshold);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            ScalerTypeCAdcLsAdcOnOffCompIntSetting((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bType, usThreshold);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcInOutCompIntControl(EnumTypeCAdcChannel enumChannel, bit bAction)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcInOutCompIntControl((Enum10BitAdcChannel)enumChannel, bAction);

            break;

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            ScalerTypeCAdcLsAdcInOutCompIntControl((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0), bAction);

            break;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3:

            ScalerTypeCAdcLsAdcInOutCompIntControl((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bAction);

            break;
#endif

#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcInOutCompIntSetting(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcInOutCompIntSetting((Enum10BitAdcChannel)enumChannel, usHigh, usLow, bRange);

            break;

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            ScalerTypeCAdcLsAdcInOutCompIntSetting((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0), usHigh, usLow, bRange);

            break;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3:

            ScalerTypeCAdcLsAdcInOutCompIntSetting((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), usHigh, usLow, bRange);

            break;
#endif

#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data for 10B SAR_ADC
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdc10BitAdcCorrectionToRawData(WORD usIdealVoltage)
{
    DWORD ulCorrectionCompThr = (DWORD)(usIdealVoltage);

    // Transition V to mV (*100)
    // Transition Voltage to ADC input domain
    ulCorrectionCompThr = ulCorrectionCompThr * 100 / _EMB_TYPE_C_0_PMIC_VBUS_TO_ADC_INPUT_RATIO;

    // Ident offset is positive or negative
    if(g_stTypeCAdcTrimming.b1Sign == 0x01)
    {
        ulCorrectionCompThr = (ulCorrectionCompThr + g_stTypeCAdcTrimming.ucOffset) * 1000 / g_stTypeCAdcTrimming.usSlop;
    }
    else
    {
        if(ulCorrectionCompThr > g_stTypeCAdcTrimming.ucOffset)
        {
            ulCorrectionCompThr = (ulCorrectionCompThr - g_stTypeCAdcTrimming.ucOffset) * 1000 / g_stTypeCAdcTrimming.usSlop;
        }
        else
        {
            ulCorrectionCompThr = (ulCorrectionCompThr - 0) * 1000 / 1953;
        }
    }

    return (WORD)ulCorrectionCompThr;
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Debounce Setting for 10B SAR_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus_On_Debounce) / _OFF (Vbus_Off_Debounce)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcOnOffCompIntDebounce(Enum10BitAdcChannel enumChannel, bit bType, BYTE ucDebCycle)
{
    // Clip Threshold to Valid Value (Not More than 4-bit)
    ucDebCycle = (ucDebCycle > 0x0F ? 0x0F : ucDebCycle);

    if(bType == _ON)
    {
        // [0x7F3C + ucChannel] adc_a0/a1/a2_vbus_on_off_deb = ucDebCycle
        ScalerSetBit((P7F_3C_10B_ADC_A0_VBUS_OFF_ON_DEB + enumChannel), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucDebCycle));
    }
    else
    {
        // [0x7F3C + ucChannel] adc_a0/a1/a2_vbus_on_off_deb = ucDebCycle << 4
        ScalerSetBit((P7F_3C_10B_ADC_A0_VBUS_OFF_ON_DEB + enumChannel), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ucDebCycle << 4));
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control for 10B SAR_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcOnOffCompIntControl(Enum10BitAdcChannel enumChannel, bit bType, bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(bType == _ON)
        {
            ScalerSetByte(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
        }
        else
        {
            ScalerSetByte(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
        }
    }
    else
    {
        if(bType == _ON)
        {
            ScalerSetByte(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), 0x00);
        }
        else
        {
            ScalerSetByte(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting for 10B SAR_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 2 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcOnOffCompIntSetting(Enum10BitAdcChannel enumChannel, bit bType, WORD usThreshold)
{
    if(bType == _ON)
    {
        // [0x7F40-41 + ucChannel*2] A0/A1/A2 Vbus On Comparator Threshold
        // [0x7F40] = adc_a0_vbus_on_thr[9:2] = usThreshold[9:2]
        // [0x7F41] = adc_a0_vbus_on_thr[1:0] = usThreshold[1:0]
        ScalerSetByte(P7F_40_10B_ADC_A0_VBUS_ON_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit(P7F_41_10B_ADC_A0_VBUS_ON_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
    else
    {
        // [0x7F48-49 + ucChannel*2] A0/A2/A4 Vbus Off Comparator Threshold
        // [0x7F48] = adc_a0_vbus_off_thr[9:2] = ucValue[9:2]
        // [0x7F49] = adc_a0_vbus_off_thr[1:0] = ucValue[1:0]
        ScalerSetByte(P7F_48_10B_ADC_A0_VBUS_OFF_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit(P7F_49_10B_ADC_A0_VBUS_OFF_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
}

//--------------------------------------------------
// Description  : 10-Bit ADC Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntControl(Enum10BitAdcChannel enumChannel, bit bAction)
{
    // Clear IRQ Flag
    ScalerTypeCAdc10BitAdcInOutCompIntClearFlag(enumChannel);

    // Control Judgment
    if(bAction == _ENABLE)
    {
        // [0x7F1B] Enable Channel INT
        ScalerSetBit(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }
    else
    {
        // [0x7F1B] Disable Channel INT
        ScalerSetBit(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), 0x00);
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0/1 (_TYPE_C_CHANNEL_0_VMON/IMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntSetting(Enum10BitAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    // [0x7F1C] Set INT Triggered Condition (INT Triggered when IN/OUT of Range)
    if(bRange == _TYPE_C_ADC_WITHIN_RANGE)
    {
        ScalerSetBit(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), 0x00);
    }
    else
    {
        ScalerSetBit(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }

    // Clip High/Low Threshold to Valid Range
    usHigh = ((usHigh >= 0x03FF) ? 0x03FF : (usHigh & 0x03FF));
    usLow = ((usLow >= 0x03FC) ? 0x03FC : (usLow & 0x03FF));

    // [0x7F20-29] Set High Threshold
    // [0x7F20] adc_a0_hi_thr[9:2] = ucHigh[9:2]
    // [0x7F21] adc_a0_hi_thr[1:0] = ucHigh[1:0]
    ScalerSetByte((P7F_20_10B_ADC_A0_HIGH_THR1 + (enumChannel * 2)), (BYTE)(usHigh >> 2));
    ScalerSetBit((P7F_21_10B_ADC_A0_HIGH_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usHigh & (_BIT1 | _BIT0)));

    // [0x7F30-39] Set Low Threshold
    // [0x7F30] adc_a0_low_thr[9:2] = ucLow[9:2]
    // [0x7F31] adc_a0_low_thr[1:0] = ucLow[1:0]
    ScalerSetByte((P7F_30_10B_ADC_A0_LOW_THR1 + (enumChannel * 2)), (BYTE)(usLow >> 2));
    ScalerSetBit((P7F_31_10B_ADC_A0_LOW_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usLow & (_BIT1 | _BIT0)));
}

//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntClearFlag(Enum10BitAdcChannel enumChannel)
{
    // [0x7F1A] Clear Channel Range Detection IRQ Flag
    ScalerSetBit(P7F_1A_10B_ADC_COMP_INT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));
}

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data for LS_ADC
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcLsAdcCorrectionToRawData(WORD usIdealVoltage)
{
    // ADC_Code = (usIdealVoltage / 10)(Unit:V) * (256 Code / Max Voltage)
    DWORD ulCorrectionCompThr = (DWORD)(usIdealVoltage * 256 / _LOCAL_POWER_VBUS_MAX_VOLTAGE / 10) << 2;

    return (WORD)ulCorrectionCompThr;
}

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))
//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Debounce Setting for LS_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus_On_Debounce) / _OFF (Vbus_Off_Debounce)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcOnOffCompIntDebounce(EnumLsAdcChannel enumChannel, bit bType, BYTE ucDebCycle)
{
    // Clip Threshold to Valid Value (Not More than 4-bit)
    ucDebCycle = (ucDebCycle > 0x0F ? 0x0F : ucDebCycle);

    if(bType == _ON)
    {
        // [0x7FC0 + enumChannel] adc_a0/a1/a2/a3_vbus_on_deb_5b = ucDebCycle
        ScalerSetBit((P7F_C0_ADC_A0_VBUS_OFF_ON_DEB + enumChannel), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucDebCycle));
    }
    else
    {
        // [0x7FC0 + enumChannel] adc_a0/a1/a2/a3_vbus_off_deb_5b = ucDebCycle << 4
        ScalerSetBit((P7F_C0_ADC_A0_VBUS_OFF_ON_DEB + enumChannel), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ucDebCycle << 4));
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control for LS_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcOnOffCompIntControl(EnumLsAdcChannel enumChannel, bit bType, bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(bType == _ON)
        {
            ScalerSetByte(P7F_CC_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
        }
        else
        {
            ScalerSetByte(P7F_CC_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
        }
    }
    else
    {
        if(bType == _ON)
        {
            ScalerSetByte(P7F_CC_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), 0x00);
        }
        else
        {
            ScalerSetByte(P7F_CC_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting for LS_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 2 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcOnOffCompIntSetting(EnumLsAdcChannel enumChannel, bit bType, WORD usThreshold)
{
    if(bType == _ON)
    {
        // [0x7FC4] adc_a0/a1/a2/a3_vbus_on_thr = usThreshold[9:2]
        ScalerSetByte(P7F_C4_ADC_A0_VBUS_ON_THR + (enumChannel * 2), (BYTE)(usThreshold >> 2));
    }
    else
    {
        // [0x7FC5] adc_a0/a1/a2/a3_vbus_off_thr = usThreshold[9:2]
        ScalerSetByte(P7F_C5_ADC_A0_VBUS_OFF_THR + (enumChannel * 2), (BYTE)(usThreshold >> 2));
    }
}
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||\
    ((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
//--------------------------------------------------
// Description  : LS ADC Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntControl(EnumLsAdcChannel enumChannel, bit bAction)
{
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    if(bAction == _ENABLE)
    {
        // [0xFF0E] ADC0: Clear Flag & Enable INT
        ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), ((_BIT4 | _BIT0) << enumChannel));
    }
    else
    {
        // [0xFF0E] ADC0: Reset Threshold
        ScalerTypeCAdcLsAdcInOutCompIntSetting(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

        // [0xFF0E] ADC0: Disable INT, but don't clear flag
        ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), 0x00);
    }

    // Clear INT Flag
    ScalerTypeCAdcLsAdcInOutCompIntClearFlag(enumChannel);

    // ADC Start Scan
    ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    if(enumChannel <= _LS_ADC_0_3)
    {
        if(bAction == _ENABLE)
        {
            // [0xFD40] ADC0: Clear Flag & Enable INT
            ScalerSetBit(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), ((_BIT4 | _BIT0) << enumChannel));
        }
        else
        {
            // [0xFD40] ADC0: Reset Threshold
            ScalerTypeCAdcLsAdcInOutCompIntSetting(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

            // [0xFD40] ADC0: Disable INT, but don't clear flag
            ScalerSetBit(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), 0x00);
        }
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        if(bAction == _ENABLE)
        {
            // [0xFF0E] ADC0: Clear Flag & Enable INT
            ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (enumChannel - _LS_ADC_1_0))), ((_BIT4 | _BIT0) << (enumChannel - _LS_ADC_1_0)));
        }
        else
        {
            // [0xFF0E] ADC0: Reset Threshold
            ScalerTypeCAdcLsAdcInOutCompIntSetting(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

            // [0xFF0E] ADC0: Disable INT, but don't clear flag
            ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (enumChannel - _LS_ADC_1_0))), 0x00);
        }
    }

    // Clear INT Flag
    ScalerTypeCAdcLsAdcInOutCompIntClearFlag(enumChannel);

    // ADC Start Scan
    ScalerSetBit(PFD_3A_ADC_ACONTROL, ~_BIT7, _BIT7);
    ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0/1 (_TYPE_C_CHANNEL_0_VMON/IMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntSetting(EnumLsAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    // Must be In-Range
    bRange = bRange;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 5;
    usHigh = ((usHigh >= 0x001F) ? 0x001F : (usHigh & 0x001F));

    usLow = usLow >> 5;
    usLow = ((usLow >= 0x001E) ? 0x001E : (usLow & 0x001F));

    // Set High/Low Threshold for 5-Bit LS_ADC
    ScalerSetByte((PFF_0F_ADC0_THRESHOLD_H + (enumChannel * 2)), (BYTE)(usHigh << 3));
    ScalerSetByte((PFF_10_ADC0_THRESHOLD_L + (enumChannel * 2)), (BYTE)(usLow << 3));

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 2;
    usHigh = ((usHigh >= 0x00FF) ? 0x00FF : (usHigh & 0x00FF));

    usLow = usLow >> 2;
    usLow = ((usLow >= 0x00FE) ? 0x00FE : (usLow & 0x00FF));

    // Set High/Low Threshold for 8-Bit LS_ADC
    if(enumChannel <= _LS_ADC_0_3)
    {
        ScalerSetByte((PFD_F7_ADC0_THRESHOLD_H + (enumChannel * 2)), (BYTE)(usHigh));
        ScalerSetByte((PFD_F8_ADC0_THRESHOLD_L + (enumChannel * 2)), (BYTE)(usLow));
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ScalerSetByte((PFF_0F_ADC0_THRESHOLD_H + ((enumChannel - _LS_ADC_1_0) * 2)), (BYTE)(usHigh));
        ScalerSetByte((PFF_10_ADC0_THRESHOLD_L + ((enumChannel - _LS_ADC_1_0) * 2)), (BYTE)(usLow));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntClearFlag(EnumLsAdcChannel enumChannel)
{
    // Clear Flag
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    if(enumChannel <= _LS_ADC_0_3)
    {
        ScalerSetBit(PFD_40_AUTO_MODE_CTRL01, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << (enumChannel - _LS_ADC_1_0)), (_BIT4 << (enumChannel - _LS_ADC_1_0)));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}
#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))

