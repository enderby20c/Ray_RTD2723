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
// ID Code      : ExternalDeviceTypeCPmicInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC DEBUG FUNCTION
//--------------------------------------------------
#define _EMB_TYPE_C_PMIC_DEBUG                      _OFF


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Type-C PMIC Contorl
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_CONTROL_FAIL = 0,
    _TYPE_C_PMIC_CONTROL_SUCCESS = 1,
} EnumTypeCPmicControlResult;

//--------------------------------------------------
// Enumerations of Type-C PMIC Direction
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_DIRECTION_SNK = 0,
    _TYPE_C_PMIC_DIRECTION_SRC = 1,
} EnumTypeCPmicDirection;

//--------------------------------------------------
// Enumerations of Type-C PMIC Discharge
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_DISCHARGE_DISABLE = 0,
    _TYPE_C_PMIC_DISCHARGE_ENABLE = 1,
} EnumTypeCPmicDischarge;

//--------------------------------------------------
// Enumerations of Type-C PMIC Discharge
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE = 0,
    _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE = 1,
} EnumTypeCPmicSwitchControl;

//--------------------------------------------------
// Enumerations of Type-C PMIC Operation Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_CV_MODE_OPERATION = 0x00,
    _TYPE_C_PMIC_CC_MODE_OPERATION = 0x01,
    _TYPE_C_PMIC_TRANSITION_MODE = 0x02,
    _TYPE_C_PMIC_NONE_MODE_OPERATION = 0xFF,
} EnumTypeCPmicOperationMode;

//--------------------------------------------------
// Enumerations of Type-C Vbus Check Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_VBUS_CHECK_NONE = 0x00,
    _TYPE_C_VBUS_CHECK_0V = 0x01,
    _TYPE_C_VBUS_CHECK_5V = 0x02,
}EnumTypeCVbusCheckType;

//--------------------------------------------------
// Enumerations of Type-C Power Role
//--------------------------------------------------
typedef enum
{
    _TYPE_C_POWER_ROLE_NONE = 0x00,
    _TYPE_C_POWER_SNK = 0x01,
    _TYPE_C_POWER_SRC = 0x02,
}EnumTypeCPowerRole;

//--------------------------------------------------
// Enumerations of Type-C PDO Types
//--------------------------------------------------
typedef enum
{
    _PD_FIX_SUPPLY_PDO = 0x00,      // Fix Supply PDO, [31:30] in PDO (2 Bits)
    _PD_RESERVED_BAT_PDO = 0x01,    // Battery Supply PDO, [31:30] in PDO (2 Bits)
    _PD_RESERVED_VAR_PDO = 0x02,    // Variable Supply PDO, [31:30] in PDO (2 Bits)
    _PD_3_PROGRAMMABLE_PDO = 0x0C,  // PPS APDO (Only for PD3.0), [31:28] in APDO (4 Bits)
    _PD_3_1_ADJUSTABLE_PDO = 0x0D,  // AVS APDO (Only for PD3.1), [31:28] in APDO (4 Bits)
    _PD_NONE_SETTING_PDO = 0xFF,    // None Setting PDO (For PMIC Initial State)
}EnumTypeCPDPdoType;

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
//--------------------------------------------------
// Enumerations of Type-C PMIC Force Off Types
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_FORCE_OFF_BY_GPIO = 0,
    _TYPE_C_PMIC_FORCE_OFF_BY_IIC = 1,
} EnumTypeCPmicForceOffType;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON)) && (_TYPE_C_PMIC_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicUnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicUnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
extern void ExternalDeviceInterfaceTypeCPmicUnattachReset_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

/////////////////////////////////////
// EIZO PMIC SIC437A CUSTOMIZED FW //
/////////////////////////////////////
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
extern BYTE ExternalDeviceInterfaceTypeCPmicAttachProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicUnattachProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicUnattachProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern BYTE ExternalDeviceInterfaceTypeCPmicTransitionStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, WORD usVoltage, WORD usCurrent, WORD *pusSrcAdjustPowerTime);
extern BYTE ExternalDeviceInterfaceTypeCPmicTransitionReadyProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicPRSwapStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern BYTE ExternalDeviceInterfaceTypeCPmicPRSwapToSrcProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicHardRstStartProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicHardRstStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicHardRstStartProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern BYTE ExternalDeviceInterfaceTypeCPmicHardRstVbusOffProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicOcpProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicOcpProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicOcpProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicOvpProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVbus5VReadyProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern BYTE ExternalDeviceInterfaceTypeCPmicVbus0VReadyProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
#endif // end of #if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))

