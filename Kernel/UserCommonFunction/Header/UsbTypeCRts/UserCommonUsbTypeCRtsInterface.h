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
// ID Code      : UserCommonUsbTypeCRtsInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))

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
extern void UserCommonUsbTypeCRtsSetI2CEnabledFlag(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtsClrI2CEnabledFlag(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbTypeCRtsInitializeI2CCommunication(EnumTypeCPcbPort enumTypeCPcbPort);

#if(_PORT_CTRL_RTS_DET_CC_ATTACH_BY_SMBUS == _ON)
extern void UserCommonUsbTypeCRtsI2CDetCCAttachCtrl(EnumTypeCPcbPort enumTypeCPcbPort, bit bAction);
#endif
#if(_PORT_CTRL_RTS_DET_ALT_MODE_READY_BY_SMBUS == _ON)
extern void UserCommonUsbTypeCRtsI2CDetAltModeReadyCtrl(EnumTypeCPcbPort enumTypeCPcbPort, bit bAction);
#endif
extern void UserCommonUsbTypeCRtsReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtsSetStatusDetection(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtsUpdateStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCDataRole UserCommonUsbTypeCRtsGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPowerRole UserCommonUsbTypeCRtsGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE UserCommonUsbTypeCRtsGetPortPartnerFlag(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
extern bit UserCommonUsbTypeCRtsGetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD UserCommonUsbTypeCRtsGetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtsGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCnt, BYTE *pucEPRPdoCnt);
extern StructTypeCUserPDO UserCommonUsbTypeCRtsGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern void UserCommonUsbTypeCRtsGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCnt, BYTE *pucEPRPdoCnt);
extern StructTypeCUserPDO UserCommonUsbTypeCRtsGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern void UserCommonUsbTypeCRtsGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent);
extern StructTypeCUserPDO UserCommonUsbTypeCRtsGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE UserCommonUsbTypeCRtsGetPortOperationMode(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtsSetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower);
extern void UserCommonUsbTypeCRtsSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucSPRPdoCnt, BYTE ucEPRPdoCnt);
extern void UserCommonUsbTypeCRtsSetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
extern void UserCommonUsbTypeCRtsSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo);
#endif

#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
extern EnumTypeCOrientation UserCommonUsbTypeCRtsGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern bit UserCommonUsbTypeCRtsGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment);
extern StructTypeCCableInfoForDpcd UserCommonUsbTypeCRtsGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbTypeCRtsGetFwVersion(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCPortCtrlFwVersion *pstTypeCFwVersion);
extern void UserCommonUsbTypeCRtsCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction);
extern void UserCommonUsbTypeCRtsSetTargetPowerMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern bit UserCommonUsbTypeCRtsReconnect(EnumTypeCPcbPort enumTypeCPcbPort);

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
extern void UserCommonUsbTypeCRtsSetLenovoAltModeDetection(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtsSetLenovoDeviceTypeDetection(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCLenovoAltModeStatus UserCommonUsbTypeCRtsGetLenovoAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCLenovoDeviceType UserCommonUsbTypeCRtsGetLenovoDeviceType(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCLenovoSysEvent UserCommonUsbTypeCRtsGetLenovoSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtsSetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
extern EnumTypeCLenovoCheckBusyResult UserCommonUsbTypeCRtsCheckLenovoDockingEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))
