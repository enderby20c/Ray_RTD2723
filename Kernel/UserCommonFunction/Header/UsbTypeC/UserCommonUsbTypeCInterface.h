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
// ID Code      : UserCommonUsbTypeCInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))
extern EnumTypeCAttachStatus UserCommonUsbTypeCGetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCAltModeStatus UserCommonUsbTypeCGetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbTypeCUpdateConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);
extern EnumTypeCPortCtrlReconnectStatus UserCommonUsbTypeCGetPowerOnReconnectStatus(EnumTypeCPcbPort enumTypeCPcbPort, EnumPowerAction enumSwitch);
#endif  // End of #if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
extern EnumTypeCPinAssignmentESupportStatus UserCommonUsbTypeCGetOsdPinAssignmentESupportSelection(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern EnumTypeCPinCfgCapType UserCommonUsbTypeCGetPinAssignmentConfig(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCMultiFuncStatus UserCommonUsbTypeCGetMultiFuncConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgCapType enumPinAssignmentCap);
extern EnumTypeCPinMismatchAction UserCommonUsbTypeCGetPinAssignmentMismatchAction(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCUpdateDisplayConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment);
extern EnumTypeCAltModeWaitStatus UserCommonUsbTypeCGetDpAltModeWaitStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCFunctionSupport UserCommonUsbTypeCGetFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCOperationMode UserCommonUsbTypeCGetOperationMode(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCGetStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent *pstStatusEvent);
extern void UserCommonUsbTypeCGetAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent *pstAlertEvent);
extern EnumTypeCPdoReference UserCommonUsbTypeCPdoReference(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCRdoReference UserCommonUsbTypeCRdoReference(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD UserCommonUsbTypeCGetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCGetSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo *pstTypeCSnkInfo);
extern void UserCommonUsbTypeCGetPdoCount(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCount, BYTE *pucEPRPdoCount);
extern void UserCommonUsbTypeCGetPdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserPdo);
extern void UserCommonUsbTypeCGetInitRdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO *pstTypeCUserInitRdo);
extern void UserCommonUsbTypeCGetRdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO *pstTypeCUserRdo);
extern EnumTypeCUnconstrainPowerExist UserCommonUsbTypeCGetUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort);

#if(_TYPE_C_EIZO_CUSTOMIZED_DP_LANE_CNT_SUPPORT == _ON)
extern EnumDpLaneCount UserCommonUsbTypeCGetAltModeLaneCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment);
#endif

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern EnumTypeCLenovoCheckDeviceTypeResult UserCommonUsbTypeCCheckLenovoDeviceTypeValid(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCLenovoDeviceType enumLenovoDeviceType);
extern void UserCommonUsbTypeCLenovoAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoSysEvent stLenovoSysEvent);
extern void UserCommonUsbTypeCGetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent *pstLenovoDockEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern void UserCommonUsbTypeCAcerAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerSysEvent stAcerSysEvent);
extern void UserCommonUsbTypeCGetAcerUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerUserEvent *pstAcerUserEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern void UserCommonUsbTypeCHpAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpSysEvent stHpSysEvent);
extern void UserCommonUsbTypeCGetHpUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpUserEvent *pstHpUserEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern EnumTypeCDellInitCompleteStatus UserCommonUsbTypeCGetDellAltModeInitComplete(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCDellAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellSysEvent stDellSysEvent);
extern void UserCommonUsbTypeCGetDellUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellUserEvent *pstDellUserEvent);
#endif
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#endif  // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))))
#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
extern EnumTypeCLocalPowerExist UserCommonUsbTypeCGetLocalPow(void);
#endif
#endif