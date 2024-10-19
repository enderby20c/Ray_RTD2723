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
// ID Code      : TypeC_Pmic_SILERGY_SY9329.h
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC SY9329
//--------------------------------------------------
#define _TYPE_C_PMIC_SY9329_SUPPORT                 ((_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329))

//--------------------------------------------------
// Register Addresss
//--------------------------------------------------
#define _SY9329_SUBADDR_LENGTH                      0x01
#define _SY9329_CTRL_REG1                           0x00
#define _SY9329_CTRL_REG2                           0x01
#define _SY9329_PROTECT_REG1                        0x02
#define _SY9329_PROTECT_REG2                        0x03
#define _SY9329_STATE_REG                           0x04
#define _SY9329_INT_REG                             0x05
#define _SY9329_BAT_VALUE_REG                       0x06
#define _SY9329_VBUS_VALUE_REG                      0x07
#define _SY9329_CURRENT_VALUE_REG                   0x08

//--------------------------------------------------
// Definitions of Voltage(10mV) and Current(10mA)
//--------------------------------------------------
#define _SY9329_VBUS_VOLTAGE_5V                     500
#define _SY9329_VBUS_VOLTAGE_7V                     700
#define _SY9329_VBUS_VOLTAGE_9V                     900
#define _SY9329_VBUS_VOLTAGE_12V                    1200
#define _SY9329_VBUS_VOLTAGE_15V                    1500
#define _SY9329_VBUS_VOLTAGE_20V                    2000

//--------------------------------------------------
// Definitions of Pmic SY9329 Control
//--------------------------------------------------
#define _SY9329_TUNE_RISE                           0
#define _SY9329_TUNE_FALL                           1
#define _SY9329_PMIC_SOURCE                         0
#define _SY9329_PMIC_SINK                           1

//--------------------------------------------------
// Macros of PMIC STATUS
//--------------------------------------------------


//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _SY9329_ADDR_00_REGULATOR_ENABLE            0x00 // Disable
#define _SY9329_ADDR_00_LOWBATTERY_VOLTAGE          0x00 // 10.2V
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
#define _SY9329_ADDR_00_ADC_ACTIVE                  0x01 // Active
#define _SY9329_ADDR_00_ADC_MODE                    0x01 // Auto Detect Mode
#else
#define _SY9329_ADDR_00_ADC_ACTIVE                  0x00 // Inactive
#define _SY9329_ADDR_00_ADC_MODE                    0x00 // Single Detect Mode
#endif
#define _SY9329_ADDR_00_VBUS_DISCHARGE              0x01 // Inactive Discharge

#define _SY9329_ADDR_01_SWITCH_FREQ                 0x01 // 500kHz
#define _SY9329_ADDR_01_VOLTAGE_SETTING             0x00 // 5V
#define _SY9329_ADDR_01_VOLTAGE_ADJUST              0x02 // +-0%

#define _SY9329_ADDR_02_CURRENT_LIMIT               0x03 // 33mV
#define _SY9329_ADDR_02_VBUS_OVP_SETTING            0x02 // 120%
#define _SY9329_ADDR_02_VBUS_UVP_SETTING            0x02 // 70%

#define _SY9329_ADDR_03_LOCP_SETTING                0x00 // 6A
#define _SY9329_ADDR_03_LOCP_MODE                   0x00 // Latch-off
#define _SY9329_ADDR_03_VBUS_UVP_MODE               0x00 // Latch-off
#define _SY9329_ADDR_03_OTP_MODE                    0x00 // Latch-off
#define _SY9329_ADDR_03_BIDIRECTIONAL_MODE          0x00 // Source Mode


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1CR1Reserved : 1;
    BYTE b1VBUSDischarge : 1;
    BYTE b1ADCMode : 1;
    BYTE b1ADCEnable : 1;
    BYTE b3LowBATVoltageSetting : 3;
    BYTE b1PMICEnable : 1;

    BYTE b3VBUSAdjust : 3;
    BYTE b3VBUSSetting : 3;
    BYTE b2SwitchFreq : 2;

    BYTE b1PS1Reserved : 1;
    BYTE b2UVPSetting : 2;
    BYTE b2OVPSetting : 2;
    BYTE b3VOCPSetting : 3;

    BYTE b2PS2Reserved : 2;
    BYTE b1BiDirSetting : 1;
    BYTE b1OTPMode : 1;
    BYTE b1UVPMode : 1;
    BYTE b1LOCPMode : 1;
    BYTE b2LOCPSetting : 2;

    BYTE b5SRReserved : 5;
    BYTE b1BATStatus : 1;
    BYTE b1BATVBUSRelation : 1;
    BYTE b1PowerGoodState : 1;

    BYTE b3IRReserved : 3;
    BYTE b1OTPFlag : 1;
    BYTE b1UVPFlag : 1;
    BYTE b1LOCPFlag : 1;
    BYTE b1VOCPFlag : 1;
    BYTE b1ADCReady : 1;

    BYTE ucBATValue;
    BYTE ucVBUSValue;
    BYTE ucVBUSCurrentValue;
} StructSY9329RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_SY9329_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_SY9329_SUPPORT == _ON))

