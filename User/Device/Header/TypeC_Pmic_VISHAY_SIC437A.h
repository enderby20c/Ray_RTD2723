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
// ID Code      : TypeC_Pmic_VISHAY_SIC437A.h
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC VISHAY SiC437A
//--------------------------------------------------
#define _TYPE_C_PMIC_VISHAY_SIC437A_SUPPORT         ((_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A))

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
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_VISHAY_SIC437A_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

/////////////////////////////////////
// EIZO PMIC SIC437A CUSTOMIZED FW //
/////////////////////////////////////
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, WORD usVoltage, WORD usCurrent, WORD *pusSrcAdjustPowerTime);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
#endif // End of #if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_VISHAY_SIC437A_SUPPORT == _ON))

