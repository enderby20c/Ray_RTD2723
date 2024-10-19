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
// ID Code      : TypeC_Pmic_Sys_Solution.h
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC System Solution
//--------------------------------------------------
#define _TYPE_C_PMIC_SYS_SOLUTION_SUPPORT           ((_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))) && (_TYPE_C_PMIC_SYS_SOLUTION_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
extern void ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON))
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))) && (_TYPE_C_PMIC_SYS_SOLUTION_SUPPORT == _ON))

