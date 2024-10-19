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
// ID Code      : TypeC_Pmic_SILERGY_SY8665.h
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC SY8665
//--------------------------------------------------
#define _TYPE_C_PMIC_SY8665_SUPPORT                 ((_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665))

//--------------------------------------------------
// Register Addresss
//--------------------------------------------------
#define _SY8665_SUBADDR_LENGTH                      0x01
#define _SY8665_FUNCTION_SETTING1                   0x00
#define _SY8665_FUNCTION_SETTING2                   0x01
#define _SY8665_FUNCTION_SETTING3                   0x02
#define _SY8665_PROTECT_SETTING1                    0x03
#define _SY8665_PROTECT_SETTING2                    0x04

#define _SY8665_STATE_REG                           0x05

//--------------------------------------------------
// Definitions of Voltage(10mV) and Current(10mA)
//--------------------------------------------------
#define _SY8665_VBUS_VOLTAGE_5V                     500
#define _SY8665_VBUS_VOLTAGE_7V                     700
#define _SY8665_VBUS_VOLTAGE_9V                     900
#define _SY8665_VBUS_VOLTAGE_12V                    1200
#define _SY8665_VBUS_VOLTAGE_15V                    1500
#define _SY8665_VBUS_VOLTAGE_20V                    2000

//--------------------------------------------------
// Definitions of Pmic SY8665 Control
//--------------------------------------------------
#define _SY8665_TUNE_RISE                           0
#define _SY8665_TUNE_FALL                           1
#define _SY8665_PMIC_SOURCE                         0
#define _SY8665_PMIC_SINK                           1

//--------------------------------------------------
// Macros of PMIC STATUS
//--------------------------------------------------


//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _DISCHARGE_REG_1_80_K                       0x00
#define _DISCHARGE_REG_1_44_K                       0x01
#define _DISCHARGE_REG_1_08_K                       0x02
#define _DISCHARGE_REG_0_72_K                       0x03

#define _TURN_OFF_DISCHANGE_AT_ALL                  0x00
#define _TURN_ON_DISCHANGE_AT_ALL                   0x01

#define _MODE_ALL_OFF1                              0x00
#define _MODE_SOURCE_MODE1                          0x01 // Buck switching, NFET turn on,  PFET turn off.
#define _MODE_SOURCE_MODE2                          0x02 // Buck standby,   NFET turn on,  PFET turn on.
#define _MODE_SOURCE_MODE3                          0x03 // Buck standby,   NFET turn off, PFET turn on
#define _MODE_ALL_OFF2                              0x04
#define _MODE_SINK_MODE1                            0x05 // Buck is disabled, NFET turn on,  PFET turn on.
#define _MODE_SINK_MODE2                            0x06 // Buck standby,     NFET turn off, PFET turn on.
#define _MODE_SINK_MODE3                            0x07 // Buck is disabled, NFET turn off, PFET turn on.

#define _OUTPUT_VOLTAGE_0V                          0x00
#define _OUTPUT_VOLTAGE_3V                          0x01
#define _OUTPUT_VOLTAGE_5V                          (_OUTPUT_VOLTAGE_3V + 10)
#define _OUTPUT_VOLTAGE_7V                          (_OUTPUT_VOLTAGE_3V + 20)
#define _OUTPUT_VOLTAGE_9V                          (_OUTPUT_VOLTAGE_3V + 30)
#define _OUTPUT_VOLTAGE_12V                         (_OUTPUT_VOLTAGE_3V + 45)
#define _OUTPUT_VOLTAGE_15V                         (_OUTPUT_VOLTAGE_3V + 60)
#define _OUTPUT_VOLTAGE_20V                         (_OUTPUT_VOLTAGE_3V + 85)

#define _LIGHT_LOAD_PULSE_SKIP                      0x00
#define _LIGHT_LOAD_BURST_MODE                      0x01

#define _CABLE_IMPEDANCE_RCMP_0                     0x01
#define _CABLE_IMPEDANCE_RCMP_20                    0x01
#define _CABLE_IMPEDANCE_RCMP_40                    0x02
#define _CABLE_IMPEDANCE_RCMP_60                    0x03
#define _CABLE_IMPEDANCE_RCMP_70                    0x04
#define _CABLE_IMPEDANCE_RCMP_100                   0x05
#define _CABLE_IMPEDANCE_RCMP_120                   0x06
#define _CABLE_IMPEDANCE_RCMP_140                   0x07

#define _SY8665_INT_ENABLE                          0x00
#define _SY8665_INT_DISABLE                         0x01

#define _GO_BIT_INTERNAL_MODE                       0x00
#define _GO_BIT_EXTERNAL_MODE                       0x01

#define _BUCK_SWITCHING_250KHZ                      0x00
#define _BUCK_SWITCHING_500KHZ                      0x01
#define _BUCK_SWITCHING_750KHZ                      0x02
#define _BUCK_SWITCHING_1MHZ                        0x03

#define _LATCH_OFF_MODE                             0x00
#define _AUTO_RECOVER_MODE                          0x01

#define _OUTPUT_CURRENT_LIMIT_10MV                  0x00
#define _OUTPUT_CURRENT_LIMIT_15MV                  0x01
#define _OUTPUT_CURRENT_LIMIT_20MV                  0x02
#define _OUTPUT_CURRENT_LIMIT_25MV                  0x03
#define _OUTPUT_CURRENT_LIMIT_30MV                  0x04
#define _OUTPUT_CURRENT_LIMIT_40MV                  0x05
#define _OUTPUT_CURRENT_LIMIT_50MV                  0x06
#define _OUTPUT_CURRENT_LIMIT_60MV                  0x07

#define _V_VBUS_OVP_THRESHOLD_125P                  0x00
#define _V_VBUS_OVP_THRESHOLD_120P                  0x01
#define _V_VBUS_OVP_THRESHOLD_115P                  0x02
#define _V_VBUS_OVP_THRESHOLD_110P                  0x03

#define _V_SWO_UVP_THRESHOLD_50P                    0x00
#define _V_SWO_UVP_THRESHOLD_60P                    0x01
#define _V_SWO_UVP_THRESHOLD_70P                    0x02
#define _V_SWO_UVP_THRESHOLD_80P                    0x03

#define INDUCTOR_PEAK_CURRENT_LIMIT_5A              0x00
#define INDUCTOR_PEAK_CURRENT_LIMIT_7A              0x01


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b3Mode : 3;
    BYTE b1DischargeEnableAllOff : 1;
    BYTE b1Fs1Reserved : 1;
    BYTE b2DischargeResistorSetting : 2;
    BYTE b1I2cReset : 1;

    BYTE b7OutputVoltageSetting : 7;
    BYTE b1Fs2Reserved : 1;

    BYTE b2Fs3Reserved : 2;
    BYTE b1InterruptEnable : 1;
    BYTE b1GoBit : 1;
    BYTE b3CableImpedanceCompensation : 3;
    BYTE b1LightLoadOperation : 1;

    BYTE b2Ps1Reserved : 2;
    BYTE b2BuckSwitchingFrequence : 2;
    BYTE b1Uvp : 1;
    BYTE b1Ovp : 1;
    BYTE b1Otp : 1;
    BYTE b1ReverseCurrentProtectionMode : 1;

    BYTE b1InductorPeakCurrentLimit : 1;
    BYTE b2VswoUvpThreshold : 2;
    BYTE b2VvbusOvpThreshod : 2;
    BYTE b3OutputCurrentLimit : 3;

    BYTE b1IntFlagUvp : 1;
    BYTE b1IntFlagOcp : 1;
    BYTE b1IntFlagOvp : 1;
    BYTE b1IntFlagOverTemperatureProtection : 1;
    BYTE b1IntFlagVoltageReversed : 1;
    BYTE b1IntFlagVbusAbsoluteMaximumOvp : 1;
    BYTE b1IntFlagReserved : 1;
    BYTE b1PowerGood : 1;

} StructSY8665RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_SY8665_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_SY8665_SUPPORT == _ON))

