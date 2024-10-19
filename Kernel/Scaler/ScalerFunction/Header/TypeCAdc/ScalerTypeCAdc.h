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
// ID Code      : ScalerTypeCAdc.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TYPE_CADC_H__
#define __SCALER_TYPE_CADC_H__


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Type-C ADC Debug Setting
//--------------------------------------------------
#define _TYPE_C_ADC_DEBUG               _OFF

//--------------------------------------------------
// Type-C ADC Voltage Setting
//--------------------------------------------------
// Unit = 0.1V (Use Unsigned Long to prevent int overflow during calculation)
#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#define _TYPE_C_0_VSAFE5V_UP_BND        55UL
#define _TYPE_C_0_VSAFE5V_LOW_BND       46UL

#define _TYPE_C_0_UNATTACH5V_AVG        22UL // ((3.67V + 0.8V) / 2 = 2.24V)

#define _TYPE_C_0_VSAFE0V_UP_BND        8UL

#if(_USB3_REPEATER_SUPPORT == _ON)
#define _USB3_0_VBUS_ON_THR             46UL
#define _USB3_0_VBUS_OFF_THR            37UL
#endif
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#define _TYPE_C_1_VSAFE5V_UP_BND        55UL
#define _TYPE_C_1_VSAFE5V_LOW_BND       46UL

#define _TYPE_C_1_UNATTACH5V_AVG        22UL // ((3.67V + 0.8V) / 2 = 2.24V)

#define _TYPE_C_1_VSAFE0V_UP_BND        8UL

#if(_USB3_REPEATER_SUPPORT == _ON)
#define _USB3_1_VBUS_ON_THR             46UL
#define _USB3_1_VBUS_OFF_THR            37UL
#endif
#endif

//--------------------------------------------------
// Type-C ADC Macro
//--------------------------------------------------
#define GET_TYPE_C_LOC_PW_EXIST()       (g_stTypeCAdcLocalPowerInfo.enumTypeCLocalPowerExist)
#define SET_TYPE_C_LOC_PW_EXIST(x)      (g_stTypeCAdcLocalPowerInfo.enumTypeCLocalPowerExist = (x))

#define GET_TYPE_C_LOC_PW_ON_THR()      ((WORD)(g_stTypeCAdcLocalPowerInfo.b10LocPowOn))
#define SET_TYPE_C_LOC_PW_ON_THR(x)     (g_stTypeCAdcLocalPowerInfo.b10LocPowOn = ScalerTypeCAdcCorrectionToRawData(_TYPE_C_CHANNEL_2_LOC_PW_VMON, (x)))
#define GET_TYPE_C_LOC_PW_OFF_THR()     ((WORD)(g_stTypeCAdcLocalPowerInfo.b10LocPowOff))
#define SET_TYPE_C_LOC_PW_OFF_THR(x)    (g_stTypeCAdcLocalPowerInfo.b10LocPowOff = ScalerTypeCAdcCorrectionToRawData(_TYPE_C_CHANNEL_2_LOC_PW_VMON, (x)))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTypeCAdcLoadTrimming(void);
#if(_LOCAL_POWER_VBUS_ADC_CHANNEL != _TYPE_C_PMIC_ADC_MAPPING_NONE)
extern void ScalerTypeCAdcLocPowReset(void);
#endif

extern WORD ScalerTypeCAdcCorrectionToRawData_WDINT(EnumTypeCAdcChannel enumChannel, WORD usIdealVoltage);
//extern bit ScalerTypeCAdcCheckVbusReady(WORD usVoltage);

extern void ScalerTypeCAdcOnOffCompIntDebounce(EnumTypeCAdcChannel enumChannel, bit bType, BYTE ucDebCycle);

extern WORD ScalerTypeCAdc10BitAdcCorrectionToRawData(WORD usIdealVoltage);
extern WORD ScalerTypeCAdc10BitAdcCorrectionToRawData_EXINT0(WORD usIdealVoltage);
extern WORD ScalerTypeCAdc10BitAdcCorrectionToRawData_WDINT(WORD usIdealVoltage);

extern WORD ScalerTypeCAdc10BitAdcGetAdcOutput(Enum10BitAdcChannel enumChannel);
extern WORD ScalerTypeCAdc10BitAdcGetAdcOutput_EXINT0(Enum10BitAdcChannel enumChannel);
extern WORD ScalerTypeCAdc10BitAdcGetAdcOutput_WDINT(Enum10BitAdcChannel enumChannel);

extern void ScalerTypeCAdc10BitAdcOnOffCompIntDebounce(Enum10BitAdcChannel enumChannel, bit bType, BYTE ucDebCycle);
extern void ScalerTypeCAdc10BitAdcOnOffCompIntControl(Enum10BitAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdc10BitAdcOnOffCompIntControl_EXINT0(Enum10BitAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdc10BitAdcOnOffCompIntControl_WDINT(Enum10BitAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdc10BitAdcOnOffCompIntSetting(Enum10BitAdcChannel enumChannel, bit bType, WORD usThreshold);
extern void ScalerTypeCAdc10BitAdcOnOffCompIntSetting_EXINT0(Enum10BitAdcChannel enumChannel, bit bType, WORD usThreshold);
extern void ScalerTypeCAdc10BitAdcOnOffCompIntSetting_WDINT(Enum10BitAdcChannel enumChannel, bit bType, WORD usThreshold);
extern void ScalerTypeCAdc10BitAdcInOutCompIntControl(Enum10BitAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdc10BitAdcInOutCompIntSetting(Enum10BitAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern void ScalerTypeCAdc10BitAdcInOutCompIntClearFlag(Enum10BitAdcChannel enumChannel);

#if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    ((_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
extern void ScalerTypeCAdc10BitAdcInOutCompIntControl_EXINT0(Enum10BitAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdc10BitAdcInOutCompIntControl_WDINT(Enum10BitAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdc10BitAdcInOutCompIntSetting_EXINT0(Enum10BitAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern void ScalerTypeCAdc10BitAdcInOutCompIntSetting_WDINT(Enum10BitAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern void ScalerTypeCAdc10BitAdcInOutCompIntClearFlag_EXINT0(Enum10BitAdcChannel enumChannel);
extern void ScalerTypeCAdc10BitAdcInOutCompIntClearFlag_WDINT(Enum10BitAdcChannel enumChannel);
extern BYTE ScalerTypeCAdc10BitAdcInOutCompIntCheck_EXINT0(Enum10BitAdcChannel enumChannel);
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_FW_OVP_UVP_SUPPORT == _ON) || (_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC)) ||

extern WORD ScalerTypeCAdcLsAdcGetAdcOutput(EnumLsAdcChannel enumChannel);
extern WORD ScalerTypeCAdcLsAdcGetAdcOutput_EXINT0(EnumLsAdcChannel enumChannel);
extern WORD ScalerTypeCAdcLsAdcGetAdcOutput_WDINT(EnumLsAdcChannel enumChannel);
extern WORD ScalerTypeCAdcLsAdcCorrectionToRawData(WORD usIdealVoltage);
extern WORD ScalerTypeCAdcLsAdcCorrectionToRawData_EXINT0(WORD usIdealVoltage);
extern WORD ScalerTypeCAdcLsAdcCorrectionToRawData_WDINT(WORD usIdealVoltage);

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)
#if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)))
extern void ScalerTypeCAdcLsAdcOnOffCompIntDebounce(EnumLsAdcChannel enumChannel, bit bType, BYTE ucDebCycle);
extern void ScalerTypeCAdcLsAdcOnOffCompIntControl(EnumLsAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdcLsAdcOnOffCompIntControl_EXINT0(EnumLsAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdcLsAdcOnOffCompIntControl_WDINT(EnumLsAdcChannel enumChannel, bit bType, bit bAction);
extern void ScalerTypeCAdcLsAdcOnOffCompIntSetting(EnumLsAdcChannel enumChannel, bit bType, WORD usThreshold);
extern void ScalerTypeCAdcLsAdcOnOffCompIntSetting_EXINT0(EnumLsAdcChannel enumChannel, bit bType, WORD usThreshold);
extern void ScalerTypeCAdcLsAdcOnOffCompIntSetting_WDINT(EnumLsAdcChannel enumChannel, bit bType, WORD usThreshold);
#endif // End of #if(((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0_3)) ||
#endif // End of #if((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1)

#if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||\
    ((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)) ||\
    ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_1_3)) ||\
    (_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON))
extern void ScalerTypeCAdcLsAdcInOutCompIntControl(EnumLsAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdcLsAdcInOutCompIntControl_EXINT0(EnumLsAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdcLsAdcInOutCompIntControl_WDINT(EnumLsAdcChannel enumChannel, bit bAction);
extern void ScalerTypeCAdcLsAdcInOutCompIntSetting(EnumLsAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern void ScalerTypeCAdcLsAdcInOutCompIntSetting_EXINT0(EnumLsAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern void ScalerTypeCAdcLsAdcInOutCompIntSetting_WDINT(EnumLsAdcChannel enumChannel, WORD usHigh, WORD usLow, bit bRange);
extern void ScalerTypeCAdcLsAdcInOutCompIntClearFlag(EnumLsAdcChannel enumChannel);
extern void ScalerTypeCAdcLsAdcInOutCompIntClearFlag_EXINT0(EnumLsAdcChannel enumChannel);
extern void ScalerTypeCAdcLsAdcInOutCompIntClearFlag_WDINT(EnumLsAdcChannel enumChannel);
extern BYTE ScalerTypeCAdcLsAdcInOutCompIntCheck_EXINT0(EnumLsAdcChannel enumChannel);
#endif // End of #if((_EMB_TYPE_C_0_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) ||

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON))


#endif // End of #ifndef __SCALER_TYPE_CADC_H__
