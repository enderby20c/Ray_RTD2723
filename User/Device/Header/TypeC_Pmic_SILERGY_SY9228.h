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
// ID Code      : TypeC_Pmic_SILERGY_SY9228.h
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC SY9228
//--------------------------------------------------
#define _TYPE_C_PMIC_SY9228_SUPPORT                 ((_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228))

//--------------------------------------------------
// Register Addresss
//--------------------------------------------------
#define _SY9228_SUBADDR_LENGTH                      0x01
#define _SY9228_FUNCTION_SETTING1                   0x00
#define _SY9228_FUNCTION_SETTING2                   0x01
#define _SY9228_VOUT_SETTING                        0x02
#define _SY9228_PROTECT_REG1                        0x03
#define _SY9228_PROTECT_REG2                        0x04
#define _SY9228_STATE_REG                           0x05
#define _SY9228_INT_REG                             0x06
#define _SY9228_VIN_VALUE_REG                       0x07
#define _SY9228_VOUT_VALUE_REG                      0x08
#define _SY9228_CURRENT_VALUE_REG                   0x09
#define _SY9228_VENDER_ID                           0x0A

//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _SY9228_ADDR_00_REGULATOR_ENABLE            0x00 // Disable
#define _SY9228_ADDR_00_SWITCH_FREQ                 0x00 // 250kHz
#define _SY9228_ADDR_00_ADC_ACTIVE                  0x01 // Active
#define _SY9228_ADDR_00_ADC_MODE                    0x01 // Auto Detect Mode
#define _SY9228_ADDR_00_VBUS_DISCHARGE              0x01 // Inactive Discharge
#define _SY9228_ADDR_00_GATE_ENABLE                 0x00 // Disable
#define _SY9228_ADDR_01_CABLE_COMPENSATION          0x02 // 100m Ohm
#define _SY9228_ADDR_02_VOUT_SETTING                0x32 // 5V
#define _SY9228_ADDR_03_VOUT_OCP_SETTING            0x06 // 50mV
#define _SY9228_ADDR_03_VOUT_OVP_SETTING            0x02 // 120%
#define _SY9228_ADDR_03_SLEW_RATE                   0x03 // 4mV/uS
#define _SY9228_ADDR_04_LOCP_SETTING                0x00 // 6A
#define _SY9228_ADDR_04_VOUT_UVP_SETTING            0x02 // 70%
#define _SY9228_ADDR_04_LOCP_MODE                   0x00 // Latch off
#define _SY9228_ADDR_04_VOUT_UVP_MODE               0x00 // Latch off
#define _SY9228_ADDR_04_OTP_MODE                    0x01 // Auto recover
#define _SY9228_ADDR_04_VOUT_OVP_MODE               0x01 // Auto recover

//--------------------------------------------------
// Definitions of Pmic SY9228 Control
//--------------------------------------------------
#define _SY9228_PMIC_SOURCE                         1
#define _SY9228_PMIC_SINK                           0


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1FS1Reserved : 1;
    BYTE b1GateEnable : 1;
    BYTE b1VOUTDischarge : 1;
    BYTE b1ADCMode : 1;
    BYTE b1ADCEnable : 1;
    BYTE b2SwitchFreq : 2;
    BYTE b1PMICEnable : 1;

    BYTE b5FS2Reserved : 5;
    BYTE b3CableCompensation : 3;

    BYTE ucOutputVoltageSetting;

    BYTE b1PS1Reserved : 1;
    BYTE b2SlewRate : 2;
    BYTE b2OVPSetting : 2;
    BYTE b3VOCPSetting : 3;

    BYTE b1OVPMode : 1;
    BYTE b1OTPMode : 1;
    BYTE b1UVPMode : 1;
    BYTE b1LOCPMode : 1;
    BYTE b2UVPSetting : 2;
    BYTE b2LOCPSetting : 2;

    BYTE b6SRReserved : 6;
    BYTE b1VinVoutRelation : 1;
    BYTE b1PowerGoodState : 1;

    BYTE b2IRReserved : 2;
    BYTE b1OVPFlag : 1;
    BYTE b1OTPFlag : 1;
    BYTE b1UVPFlag : 1;
    BYTE b1LOCPFlag : 1;
    BYTE b1VOCPFlag : 1;
    BYTE b1ADCReady : 1;

    BYTE ucInputVoltageValue;
    BYTE ucOutputVoltageValue;
    BYTE ucOutputCurrentValue;

    BYTE b4VenderID : 4;
    BYTE b4Product : 4;
} StructSY9228RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))) && (_TYPE_C_PMIC_SY9228_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
extern void ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON))
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))) && (_TYPE_C_PMIC_SY9228_SUPPORT == _ON))

