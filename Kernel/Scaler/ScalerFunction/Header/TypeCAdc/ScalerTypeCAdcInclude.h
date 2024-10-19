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
// ID Code      : ScalerTypeCAdcInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON)) || (_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON))
//--------------------------------------------------
// Type-C ADC Definition
//--------------------------------------------------
#define _ADC_OUTPUT_MAX_TIME            2
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))

// Temporary Definittions
#define _TYPE_C_EMB_DFP_PORT_SUPPORT    _OFF

#define _TYPE_C_ADC_WITHIN_RANGE        0x00
#define _TYPE_C_ADC_WITHOUT_RANGE       0x01

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#define GET_TYPE_C_0_5V_UP_BND()        ((WORD)(g_stTypeCAdc0PowerInfo.b10Vbus5VUpBound))
#define SET_TYPE_C_0_5V_UP_BND(x)       (g_stTypeCAdc0PowerInfo.b10Vbus5VUpBound = ScalerTypeCAdcCorrectionToRawData(_TYPE_C_CHANNEL_0_VMON, (x)))

#define GET_TYPE_C_0_5V_LOW_BND()       ((WORD)(g_stTypeCAdc0PowerInfo.b10Vbus5VLowBound))
#define SET_TYPE_C_0_5V_LOW_BND(x)      (g_stTypeCAdc0PowerInfo.b10Vbus5VLowBound = ScalerTypeCAdcCorrectionToRawData(_TYPE_C_CHANNEL_0_VMON, (x)))

#define GET_TYPE_C_0_0V_UP_BND()        ((WORD)(g_stTypeCAdc0PowerInfo.b10Vbus0VUpBound))
#define SET_TYPE_C_0_0V_UP_BND(x)       (g_stTypeCAdc0PowerInfo.b10Vbus0VUpBound = ScalerTypeCAdcCorrectionToRawData(_TYPE_C_CHANNEL_0_VMON, (x)))
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#define GET_TYPE_C_1_5V_UP_BND()        ((WORD)(g_stTypeCAdc1PowerInfo.b10Vbus5VUpBound))
#define SET_TYPE_C_1_5V_UP_BND(x)       (g_stTypeCAdc1PowerInfo.b10Vbus5VUpBound = ScalerTypeCAdcCorrectionToRawData(_TYPE_C_CHANNEL_1_VMON, (x)))

#define GET_TYPE_C_1_5V_LOW_BND()       ((WORD)(g_stTypeCAdc1PowerInfo.b10Vbus5VLowBound))
#define SET_TYPE_C_1_5V_LOW_BND(x)      (g_stTypeCAdc1PowerInfo.b10Vbus5VLowBound = ScalerTypeCAdcCorrectionToRawData(_TYPE_C_CHANNEL_1_VMON, (x)))

#define GET_TYPE_C_1_0V_UP_BND()        ((WORD)(g_stTypeCAdc1PowerInfo.b10Vbus0VUpBound))
#define SET_TYPE_C_1_0V_UP_BND(x)       (g_stTypeCAdc1PowerInfo.b10Vbus0VUpBound = ScalerTypeCAdcCorrectionToRawData(_TYPE_C_CHANNEL_1_VMON, (x)))
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
// Type-C ADC Trimming Struct
typedef struct
{
    WORD usSlop;
    BYTE ucOffset;
    BYTE b1Sign : 1;
}StructTypeCAdcTrimming;

// Type-C Local Power Information Struct
typedef struct
{
    EnumTypeCLocalPowerExist enumTypeCLocalPowerExist;
    WORD b10LocPowOn : 10;
    WORD b10LocPowOff : 10;
}StructTypeCAdcLocalPowerInfo;

// Type-C Power Related Information Struct
typedef struct
{
    WORD b10Vbus5VUpBound : 10;
    WORD b10Vbus5VLowBound : 10;
    WORD b10Vbus0VUpBound : 10;
}StructTypeCAdcInfo;

#if(_USB3_REPEATER_SUPPORT == _ON)
// Retimer ADC Channels
typedef struct
{
    WORD b10Usb3VbusOnThr : 10;
    WORD b10Usb3VbusOffThr : 10;
}StructUsb3VbusOnOffThr;
#endif

// Type-C ADC Digital Comparator Channels
typedef enum
{
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _TYPE_C_CHANNEL_0_VBUS = _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL,
#endif // End Of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _TYPE_C_CHANNEL_1_VBUS = _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL,
#endif // End Of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _TYPE_C_CHANNEL_2_LOC_PW = _LOCAL_POWER_VBUS_ADC_CHANNEL,
#if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
    _TYPE_C_CHANNEL_3_DFP_VBUS = _TYPE_C_PMIC_ADC_MAPPING_NONE,
    _TYPE_C_CHANNEL_4_DFP_VBUS = _TYPE_C_PMIC_ADC_MAPPING_NONE,
#endif // End of #if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    _TYPE_C_0_IOUT = _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL,
#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    _TYPE_C_1_IOUT = _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL,
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
}EnumAdcVbusCompChannel;

// Type-C ADC Channels
typedef enum
{
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _TYPE_C_CHANNEL_0_VMON = _EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL,
#endif // End Of #if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _TYPE_C_CHANNEL_1_VMON = _EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL,
#endif // End Of #if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
    _TYPE_C_CHANNEL_2_LOC_PW_VMON = _LOCAL_POWER_VBUS_ADC_CHANNEL,
#if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
    _TYPE_C_DFP_VMON = _TYPE_C_PMIC_ADC_MAPPING_NONE,
    _TYPE_C_DFP_IMON = _TYPE_C_PMIC_ADC_MAPPING_NONE,
#endif // End of #if(_TYPE_C_EMB_DFP_PORT_SUPPORT == _ON)
#if((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) || ((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
    _TYPE_C_0_IMON = _EMB_TYPE_C_0_PMIC_IOUT_ADC_CHANNEL,
#endif // End of #if((_EMB_TYPE_C_0_PMIC_VOLTAGE_COMPENSATION == _ON) || ((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
#if((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) || ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
    _TYPE_C_1_IMON = _EMB_TYPE_C_1_PMIC_IOUT_ADC_CHANNEL,
#endif // End of #if((_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON) || ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)))
}EnumTypeCAdcChannel;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTypeCAdcTrimming g_stTypeCAdcTrimming;

extern StructTypeCAdcLocalPowerInfo g_stTypeCAdcLocalPowerInfo;

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
extern StructTypeCAdcInfo g_stTypeCAdc0PowerInfo;
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
extern StructTypeCAdcInfo g_stTypeCAdc1PowerInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTypeCAdcPortInitial(EnumTypeCEmbeddedList enumTypeCIndex);
extern void ScalerTypeCAdcIntHandler_EXINT0(void);
extern EnumTypeCLocalPowerExist ScalerTypeCAdcGetLocPowExist_EXINT0(void);
#if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)
extern void ScalerTypeCAdcLocalPowerIntHandler_EXINT0(void);
#endif // End of #if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)

extern WORD ScalerTypeCAdcCorrectionToIdealData(EnumTypeCAdcChannel enumChannel, WORD usRawData);
extern WORD ScalerTypeCAdcCorrectionToIdealData_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usRawData);
extern WORD ScalerTypeCAdcCorrectionToIdealData_WDINT(EnumTypeCAdcChannel enumChannel, WORD usRawData);
extern WORD ScalerTypeCAdcCorrectionToRawData(EnumTypeCAdcChannel enumChannel, WORD usIdealVoltage);
extern WORD ScalerTypeCAdcCorrectionToRawData_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usIdealVoltage);

extern void ScalerTypeCAdcUnattachReset(EnumTypeCEmbeddedList enumTypeCIndex);
extern void ScalerTypeCAdcUnattachVthAdjust(EnumTypeCAdcChannel enumChannel, WORD usVoltage);
extern bit ScalerTypeCAdcCheckVbusSafe0V(EnumTypeCEmbeddedList enumTypeCIndex);
extern bit ScalerTypeCAdcCheckVbusSafe5V(EnumTypeCEmbeddedList enumTypeCIndex);
extern void ScalerTypeCAdcUnattachReset_EXINT0(EnumTypeCEmbeddedList enumTypeCIndex);
extern void ScalerTypeCAdcUnattachVthAdjust_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usVoltage);
extern bit ScalerTypeCAdcCheckVbusReady_WDINT(EnumTypeCEmbeddedList enumTypeCIndex, WORD usVoltage);

extern WORD ScalerTypeCAdcGetAdcOutput(EnumTypeCAdcChannel enumChannel);
extern WORD ScalerTypeCAdcGetAdcOutput_EXINT0(EnumTypeCAdcChannel enumChannel);
extern bit ScalerTypeCAdcCheckVbusSafe0V_WDINT(EnumTypeCEmbeddedList enumTypeCIndex);
extern WORD ScalerTypeCAdcGetAdcOutput_WDINT(EnumTypeCAdcChannel enumChannel);

extern void ScalerTypeCAdcOnOffCompIntControl(EnumTypeCAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdcOnOffCompIntSetting(EnumTypeCAdcChannel enumChannel, bit bType, WORD usThreshold);
extern void ScalerTypeCAdcOnOffCompIntControl_EXINT0(EnumTypeCAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdcOnOffCompIntSetting_EXINT0(EnumTypeCAdcChannel enumChannel, bit bType, WORD usThreshold);
extern void ScalerTypeCAdcOnOffCompIntControl_WDINT(EnumTypeCAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdcOnOffCompIntSetting_WDINT(EnumTypeCAdcChannel enumChannel, bit bType, WORD usThreshold);

extern void ScalerTypeCAdcInOutCompIntControl(EnumTypeCAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdcInOutCompIntSetting(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);

#if(((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
extern void ScalerTypeCAdcInOutCompIntControl_EXINT0(EnumTypeCAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdcInOutCompIntControl_WDINT(EnumTypeCAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdcInOutCompIntSetting_EXINT0(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern void ScalerTypeCAdcInOutCompIntSetting_WDINT(EnumTypeCAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern BYTE ScalerTypeCAdcInOutCompIntCheck_EXINT0(EnumTypeCAdcChannel enumChannel);
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC) || (_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON)) ||

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))

#if(((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON)) || (_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON))
extern bit ScalerTypeCAdcGetLdoBandgapCoverSupport(void);
#endif // End of #if(((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON)) || (_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON))

