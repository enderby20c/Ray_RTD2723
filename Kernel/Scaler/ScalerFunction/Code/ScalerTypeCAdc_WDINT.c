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
// ID Code      : ScalerTypeCAdc_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeCAdc/ScalerTypeCAdc.h"




#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
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
// Description  : Correction Raw Data to Ideal Data
// Input Value  : ADC_Code (0 ~ 1024)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcCorrectionToIdealData_WDINT(EnumTypeCAdcChannel enumChannel, WORD usRawData)
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
WORD ScalerTypeCAdcCorrectionToRawData_WDINT(EnumTypeCAdcChannel enumChannel, WORD usIdealVoltage)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            return ScalerTypeCAdc10BitAdcCorrectionToRawData_WDINT(usIdealVoltage);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return ScalerTypeCAdcLsAdcCorrectionToRawData_WDINT(usIdealVoltage);

            break;
#endif

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            return ScalerTypeCAdcLsAdcCorrectionToRawData_WDINT(usIdealVoltage);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Check if Vbus Voltage is Ready
// Input Value  : enumTypeCIndex : TypeC Index (_TYPE_C_EMB_0 / _TYPE_C_EMB_1...)
//                usVoltage : Unit = 10mV
// Output Value : _TRUE / _FLASE
//--------------------------------------------------
bit ScalerTypeCAdcCheckVbusReady_WDINT(EnumTypeCEmbeddedList enumTypeCIndex, WORD usVoltage)
{
    if(usVoltage == 500)
    {
        // Check Vbus = vSafe5V
        if(enumTypeCIndex == _EMB_TYPE_C_0)
        {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if((ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_0_VMON) >= GET_TYPE_C_0_5V_LOW_BND()) && (ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_0_VMON) <= GET_TYPE_C_0_5V_UP_BND()))
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
            if((ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_1_VMON) >= GET_TYPE_C_1_5V_LOW_BND()) && (ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_1_VMON) <= GET_TYPE_C_1_5V_UP_BND()))
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
    {
        // Check Vbus = vSafe0V
        if(enumTypeCIndex == _EMB_TYPE_C_0)
        {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if(ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_0_VMON) <= GET_TYPE_C_0_0V_UP_BND())
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
            if(ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_1_VMON) <= GET_TYPE_C_1_0V_UP_BND())
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
    {
        // Check Other Voltage Reange (0.95 ~ 1.05 vSrcNew) : 0.43 = [usVoltage * 10mV * 1024(10-bit)] / [24(Max Vol) * 1000]
        if(enumTypeCIndex == _EMB_TYPE_C_0)
        {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
            if((ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_0_VMON) >= ScalerTypeCAdcCorrectionToRawData_WDINT(_TYPE_C_CHANNEL_0_VMON, (WORD)((DWORD)usVoltage * 95 / 100 / 10))) &&
               (ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_0_VMON) <= ScalerTypeCAdcCorrectionToRawData_WDINT(_TYPE_C_CHANNEL_0_VMON, (WORD)((DWORD)usVoltage * 105 / 100 / 10))))
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
            if((ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_1_VMON) >= ScalerTypeCAdcCorrectionToRawData_WDINT(_TYPE_C_CHANNEL_1_VMON, (WORD)((DWORD)usVoltage * 95 / 100 / 10))) &&
               (ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_1_VMON) <= ScalerTypeCAdcCorrectionToRawData_WDINT(_TYPE_C_CHANNEL_1_VMON, (WORD)((DWORD)usVoltage * 105 / 100 / 10))))
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

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if UFP Vbus Voltage is vSafe0V
// Input Value  : None
// Output Value : 0 : Not vSafe0V / 1 : Vbus is vSafe0V
//--------------------------------------------------
bit ScalerTypeCAdcCheckVbusSafe0V_WDINT(EnumTypeCEmbeddedList enumTypeCIndex)
{
    if(enumTypeCIndex == _EMB_TYPE_C_0)
    {
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        if(ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_0_VMON) <= GET_TYPE_C_0_0V_UP_BND())
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
        if(ScalerTypeCAdcGetAdcOutput_WDINT(_TYPE_C_CHANNEL_1_VMON) <= GET_TYPE_C_1_0V_UP_BND())
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
// Description  : Get ADC Channel Output Value
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcGetAdcOutput_WDINT(EnumTypeCAdcChannel enumChannel)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            return ScalerTypeCAdc10BitAdcGetAdcOutput_WDINT((Enum10BitAdcChannel)enumChannel);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            return ScalerTypeCAdcLsAdcGetAdcOutput_WDINT((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0));

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

            return ScalerTypeCAdcLsAdcGetAdcOutput_WDINT((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0));

            break;
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get ADC Channel Output Value
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdc10BitAdcGetAdcOutput_WDINT(Enum10BitAdcChannel enumChannel)
{
    DWORD ulResult = 0;

    // [0x7F02] [4:0] Write Valid Output Bit to Get New Value From ADC
    ScalerSetBit_EXINT(P7F_02_10B_ADC_OUTPUT, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));

    // Polling Valid Output Bit (will be 1 when the New Output is Put into Register [0x7F10-19])
    if(ScalerTimerPollingFlagProc_WDINT(_ADC_OUTPUT_MAX_TIME, P7F_02_10B_ADC_OUTPUT, (_BIT0 << enumChannel), (_BIT0 << enumChannel)) == _TRUE)
    {
        BYTE ucResult_h = (ScalerGetByte_EXINT(P7F_10_10B_ADC_A0_RSLT_H + (enumChannel * 2)));
        BYTE ucResult_l = (ScalerGetByte_EXINT(P7F_11_10B_ADC_A0_RSLT_L + (enumChannel * 2))) & (_BIT1 | _BIT0);

        // usResult [9:0] = {RSLT_H[7:0] | RSLT[1:0]}
        ulResult = ((ucResult_h << 2) | (ucResult_l));
    }
    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcOnOffCompIntControl_WDINT(EnumTypeCAdcChannel enumChannel, bit bType, bit bAction)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcOnOffCompIntControl_WDINT((Enum10BitAdcChannel)enumChannel, bType, bAction);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            ScalerTypeCAdcLsAdcOnOffCompIntControl_WDINT((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bType, bAction);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcOnOffCompIntSetting_WDINT(EnumTypeCAdcChannel enumChannel, bit bType, WORD usThreshold)
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

            ScalerTypeCAdc10BitAdcOnOffCompIntSetting_WDINT((Enum10BitAdcChannel)enumChannel, bType, usThreshold);

            break;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3:

            ScalerTypeCAdcLsAdcOnOffCompIntSetting_WDINT((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bType, usThreshold);

            break;
#endif
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

        default:
            break;
    }
}

#if(((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcInOutCompIntControl_WDINT(EnumTypeCAdcChannel enumChannel, bit bAction)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
#if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcInOutCompIntControl_WDINT((Enum10BitAdcChannel)enumChannel, bAction);

            break;

#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            ScalerTypeCAdcLsAdcInOutCompIntControl_WDINT((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0), bAction);

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

            ScalerTypeCAdcLsAdcInOutCompIntControl_WDINT((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), bAction);

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
void ScalerTypeCAdcInOutCompIntSetting_WDINT(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    BYTE ucAdcMapping = enumChannel;

    switch(ucAdcMapping)
    {
#if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_10_BIT_ADC_3:

            ScalerTypeCAdc10BitAdcInOutCompIntSetting_WDINT((Enum10BitAdcChannel)enumChannel, usHigh, usLow, bRange);

            break;

#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_2:
        case _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3:

            ScalerTypeCAdcLsAdcInOutCompIntSetting_WDINT((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0), usHigh, usLow, bRange);

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

            ScalerTypeCAdcLsAdcInOutCompIntSetting_WDINT((EnumLsAdcChannel)(enumChannel - _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0), usHigh, usLow, bRange);

            break;
#endif

#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))

        default:
            break;
    }
}
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data for 10B SAR_ADC
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdc10BitAdcCorrectionToRawData_WDINT(WORD usIdealVoltage)
{
    DWORD ulCorrectionCompThr = (DWORD)usIdealVoltage;

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
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control for 10B SAR_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcOnOffCompIntControl_WDINT(Enum10BitAdcChannel enumChannel, bit bType, bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(bType == _ON)
        {
            ScalerSetByte_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
        }
        else
        {
            ScalerSetByte_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
        }
    }
    else
    {
        if(bType == _ON)
        {
            ScalerSetByte_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), 0x00);
        }
        else
        {
            ScalerSetByte_EXINT(P7F_3A_10B_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_3B_10B_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting for 10B SAR_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcOnOffCompIntSetting_WDINT(Enum10BitAdcChannel enumChannel, bit bType, WORD usThreshold)
{
    if(bType == _ON)
    {
        // [0x7F40-41 + ucChannel*2] A0/A1/A2 Vbus On Comparator Threshold
        // [0x7F40] = adc_a0_vbus_on_thr[9:2] = usThreshold[9:2]
        // [0x7F41] = adc_a0_vbus_on_thr[1:0] = usThreshold[1:0]
        ScalerSetByte_EXINT(P7F_40_10B_ADC_A0_VBUS_ON_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit_EXINT(P7F_41_10B_ADC_A0_VBUS_ON_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
    else
    {
        // [0x7F48-49 + ucChannel*2] A0/A2/A4 Vbus Off Comparator Threshold
        // [0x7F48] = adc_a0_vbus_off_thr[9:2] = ucValue[9:2]
        // [0x7F49] = adc_a0_vbus_off_thr[1:0] = ucValue[1:0]
        ScalerSetByte_EXINT(P7F_48_10B_ADC_A0_VBUS_OFF_THR1 + (enumChannel * 2), (BYTE)(usThreshold >> 2));
        ScalerSetBit_EXINT(P7F_49_10B_ADC_A0_VBUS_OFF_THR2 + (enumChannel * 2), ~(_BIT1 | _BIT0), (BYTE)(usThreshold & (_BIT1 | _BIT0)));
    }
}

#if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntControl_WDINT(Enum10BitAdcChannel enumChannel, bit bAction)
{
    // Clear IRQ Flag
    ScalerTypeCAdc10BitAdcInOutCompIntClearFlag_WDINT(enumChannel);

    // Control Judgment
    if(bAction == _ENABLE)
    {
        // [0x7F1B] Enable Channel INT
        ScalerSetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }
    else
    {
        // [0x7F1B] Disable Channel INT
        ScalerSetBit_EXINT(P7F_1B_10B_ADC_COMP_INT_EN, ~(_BIT0 << enumChannel), 0x00);
    }
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntSetting_WDINT(Enum10BitAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
{
    // [0x7F1C] Set INT Triggered Condition (INT Triggered when IN/OUT of Range)
    if(bRange == _TYPE_C_ADC_WITHIN_RANGE)
    {
        ScalerSetBit_EXINT(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P7F_1C_10B_ADC_COMP_THR_CTRL, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
    }

    // Clip High/Low Threshold to Valid Range
    usHigh = ((usHigh >= 0x03FF) ? 0x03FF : (usHigh & 0x03FF));
    usLow = ((usLow >= 0x03FC) ? 0x03FC : (usLow & 0x03FF));

    // [0x7F20-29] Set High Threshold
    // [0x7F20] adc_a0_hi_thr[9:2] = ucHigh[9:2]
    // [0x7F21] adc_a0_hi_thr[1:0] = ucHigh[1:0]
    ScalerSetByte_EXINT((P7F_20_10B_ADC_A0_HIGH_THR1 + (enumChannel * 2)), (BYTE)(usHigh >> 2));
    ScalerSetBit_EXINT((P7F_21_10B_ADC_A0_HIGH_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usHigh & (_BIT1 | _BIT0)));

    // [0x7F30-39] Set Low Threshold
    // [0x7F30] adc_a0_low_thr[9:2] = ucLow[9:2]
    // [0x7F31] adc_a0_low_thr[1:0] = ucLow[1:0]
    ScalerSetByte_EXINT((P7F_30_10B_ADC_A0_LOW_THR1 + (enumChannel * 2)), (BYTE)(usLow >> 2));
    ScalerSetBit_EXINT((P7F_31_10B_ADC_A0_LOW_THR2 + (enumChannel * 2)), ~(_BIT1 | _BIT0), (BYTE)(usLow & (_BIT1 | _BIT0)));
}

//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdc10BitAdcInOutCompIntClearFlag_WDINT(Enum10BitAdcChannel enumChannel)
{
    // [0x7F1A] Clear Channel Range Detection IRQ Flag
    ScalerSetBit_EXINT(P7F_1A_10B_ADC_COMP_INT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0 << enumChannel));
}
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||

//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcLsAdcGetAdcOutput_WDINT(EnumLsAdcChannel enumChannel)
{
    DWORD ulResult = 0;

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    // Transfer 5-bit ADC to 10-bit result
    ulResult = (WORD)(ScalerGetBit_EXINT(PFF_09_ADC_A0_CONVERT_RESULT + enumChannel, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3))) << 2;

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    // Transfer 8-bit ADC to 10-bit result
    if(enumChannel <= _LS_ADC_0_3)
    {
        ulResult = (WORD)(ScalerGetByte_EXINT(PFD_3B_ADC_A0_CONVERT_RESULT + enumChannel)) << 2;
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ulResult = (WORD)(ScalerGetByte_EXINT(PFF_09_ADC_A0_CONVERT_RESULT + (enumChannel - _LS_ADC_1_0))) << 2;
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    return (WORD)ulResult;
}

//--------------------------------------------------
// Description  : Correction Ideal Voltage to Raw Data for LS_ADC
// Input Value  : Voltage (Unit:0.1V)
// Output Value : ADC_Code (0 ~ 1024)
//--------------------------------------------------
WORD ScalerTypeCAdcLsAdcCorrectionToRawData_WDINT(WORD usIdealVoltage)
{
    // ADC_Code = (usIdealVoltage / 10)(Unit:V) * (256 Code / Max Voltage)
    DWORD ulCorrectionCompThr = (DWORD)(usIdealVoltage * 256 / _LOCAL_POWER_VBUS_MAX_VOLTAGE / 10) << 2;

    return (WORD)ulCorrectionCompThr;
}

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))
//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator On/Off IRQ Control for LS_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW) / 3 (_TYPE_C_CHANNEL_4_DFP_VBUS)
//                bType : _ON (Vbus On Detection) / _OFF (Vbus Off Detection)
//                bAction : IRQ _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcOnOffCompIntControl_WDINT(EnumLsAdcChannel enumChannel, bit bType, bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(bType == _ON)
        {
            ScalerSetByte_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), (_BIT0 << enumChannel));
        }
        else
        {
            ScalerSetByte_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
        }
    }
    else
    {
        if(bType == _ON)
        {
            ScalerSetByte_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT0 << enumChannel));
            ScalerSetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT0 << enumChannel), 0x00);
        }
        else
        {
            ScalerSetByte_EXINT(P7F_CC_ADC_VBUS_INT, (_BIT4 << enumChannel));
            ScalerSetBit_EXINT(P7F_CD_ADC_VBUS_INT_EN, ~(_BIT4 << enumChannel), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : ADC Vbus(Voltage) Comparator Thresholed Setting for LS_ADC
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VBUS) / 1 (_TYPE_C_CHANNEL_1_VBUS) / 2 (_TYPE_C_CHANNEL_2_LOC_PW)
//                bType : _ON (Vbus On Comparator) / _OFF (Vbus Off Comparator)
//                usDebCycle : Number of ADC CLK Cycle to be Debounced
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcOnOffCompIntSetting_WDINT(EnumLsAdcChannel enumChannel, bit bType, WORD usThreshold)
{
    if(bType == _ON)
    {
        // [0x7FC4] adc_a0/a1/a2/a3_vbus_on_thr = usThreshold[9:2]
        ScalerSetByte_EXINT(P7F_C4_ADC_A0_VBUS_ON_THR + (enumChannel * 2), (BYTE)(usThreshold >> 2));
    }
    else
    {
        // [0x7FC5] adc_a0/a1/a2/a3_vbus_off_thr = usThreshold[9:2]
        ScalerSetByte_EXINT(P7F_C5_ADC_A0_VBUS_OFF_THR + (enumChannel * 2), (BYTE)(usThreshold >> 2));
    }
}
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||\
    ((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Control
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                bRange : IRQ Triggered When Within / Without Range
//                bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntControl_WDINT(EnumLsAdcChannel enumChannel, bit bAction)
{
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    if(bAction == _ENABLE)
    {
        // [0xFF0E] ADC0: Clear Flag & Enable INT
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), ((_BIT4 | _BIT0) << enumChannel));
    }
    else
    {
        // [0xFF0E] ADC0: Reset Threshold
        ScalerTypeCAdcLsAdcInOutCompIntSetting_WDINT(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

        // [0xFF0E] ADC0: Disable INT, but don't clear flag
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), 0x00);
    }

    // Clear INT Flag
    ScalerTypeCAdcLsAdcInOutCompIntClearFlag_WDINT(enumChannel);

    // ADC Start Scan
    ScalerSetBit_EXINT(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    if(enumChannel <= _LS_ADC_0_3)
    {
        if(bAction == _ENABLE)
        {
            // [0xFD40] ADC0: Clear Flag & Enable INT
            ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), ((_BIT4 | _BIT0) << enumChannel));
        }
        else
        {
            // [0xFD40] ADC0: Reset Threshold
            ScalerTypeCAdcLsAdcInOutCompIntSetting_WDINT(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

            // [0xFD40] ADC0: Disable INT, but don't clear flag
            ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << enumChannel)), 0x00);
        }
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        if(bAction == _ENABLE)
        {
            // [0xFF0E] ADC0: Clear Flag & Enable INT
            ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (enumChannel - _LS_ADC_1_0))), ((_BIT4 | _BIT0) << (enumChannel - _LS_ADC_1_0)));
        }
        else
        {
            // [0xFF0E] ADC0: Reset Threshold
            ScalerTypeCAdcLsAdcInOutCompIntSetting_WDINT(enumChannel, 0x0000, 0x03FF, _TYPE_C_ADC_WITHIN_RANGE);

            // [0xFF0E] ADC0: Disable INT, but don't clear flag
            ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (enumChannel - _LS_ADC_1_0))), 0x00);
        }
    }

    // Clear INT Flag
    ScalerTypeCAdcLsAdcInOutCompIntClearFlag_WDINT(enumChannel);

    // ADC Start Scan
    ScalerSetBit_EXINT(PFD_3A_ADC_ACONTROL, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
//                usHigh / usLow : High/Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntSetting_WDINT(EnumLsAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange)
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
    ScalerSetByte_EXINT((PFF_0F_ADC0_THRESHOLD_H + (enumChannel * 2)), (BYTE)(usHigh << 3));
    ScalerSetByte_EXINT((PFF_10_ADC0_THRESHOLD_L + (enumChannel * 2)), (BYTE)(usLow << 3));

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 2;
    usHigh = ((usHigh >= 0x00FF) ? 0x00FF : (usHigh & 0x00FF));

    usLow = usLow >> 2;
    usLow = ((usLow >= 0x00FE) ? 0x00FE : (usLow & 0x00FF));

    // Set High/Low Threshold for 8-Bit LS_ADC
    if(enumChannel <= _LS_ADC_0_3)
    {
        ScalerSetByte_EXINT((PFD_F7_ADC0_THRESHOLD_H + (enumChannel * 2)), (BYTE)(usHigh));
        ScalerSetByte_EXINT((PFD_F8_ADC0_THRESHOLD_L + (enumChannel * 2)), (BYTE)(usLow));
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ScalerSetByte_EXINT((PFF_0F_ADC0_THRESHOLD_H + ((enumChannel - _LS_ADC_1_0) * 2)), (BYTE)(usHigh));
        ScalerSetByte_EXINT((PFF_10_ADC0_THRESHOLD_L + ((enumChannel - _LS_ADC_1_0) * 2)), (BYTE)(usLow));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : enumChannel : 0 (_TYPE_C_CHANNEL_0_VMON) / 1 (_TYPE_C_CHANNEL_1_VMON) / 2 (_TYPE_C_CHANNEL_2_LOC_PW_VMON) / 3/4 (_TYPE_C_DFP_VMON/IMON)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCAdcLsAdcInOutCompIntClearFlag_WDINT(EnumLsAdcChannel enumChannel)
{
    // Clear Flag
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));

#elif(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
    if(enumChannel <= _LS_ADC_0_3)
    {
        ScalerSetBit_EXINT(PFD_40_AUTO_MODE_CTRL01, ~(_BIT4 << enumChannel), (_BIT4 << enumChannel));
    }
    else if((enumChannel >= _LS_ADC_1_0) && (enumChannel <= _LS_ADC_1_3))
    {
        ScalerSetBit_EXINT(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << (enumChannel - _LS_ADC_1_0)), (_BIT4 << (enumChannel - _LS_ADC_1_0)));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}
#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))

