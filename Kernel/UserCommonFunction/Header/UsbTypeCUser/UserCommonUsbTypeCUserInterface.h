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
// ID Code      : UserCommonUsbTypeCUserInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))

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
#if(_PORT_CTRL_USER_DET_CC_ATTACH_BY_SMBUS == _ON)
extern EnumTypeCAttachStatus UserCommonUsbTypeCUserGetCcAttachByI2C(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_USER_DET_ALT_MODE_READY_BY_SMBUS == _ON)
extern EnumTypeCAltModeStatus UserCommonUsbTypeCUserGetAltModeReadyByI2C(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern bit UserCommonUsbTypeCUserReconnect(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
extern EnumTypeCOrientation UserCommonUsbTypeCUserGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern bit UserCommonUsbTypeCUserGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment);
extern EnumTypeCPowerRole UserCommonUsbTypeCUserGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCDataRole UserCommonUsbTypeCUserGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCUserSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
extern void UserCommonUsbTypeCUserSetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
extern void UserCommonUsbTypeCUserSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo);
extern void UserCommonUsbTypeCUserCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction);
extern EnumTypeCPdoNumber UserCommonUsbTypeCUserGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO UserCommonUsbTypeCUserGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern EnumTypeCPdoNumber UserCommonUsbTypeCUserGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO UserCommonUsbTypeCUserGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern void UserCommonUsbTypeCUserGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent);
extern StructTypeCUserPDO UserCommonUsbTypeCUserGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbTypeCUserGetFwVersion(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCPortCtrlFwVersion *pstTypeCFwVersion);
extern StructTypeCCableInfoForDpcd UserCommonUsbTypeCUserGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort);

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
extern EnumTypeCLenovoAltModeStatus UserCommonUsbTypeCUserGetLenovoAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCLenovoDeviceType UserCommonUsbTypeCUserGetLenovoDeviceType(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCUserSetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
extern StructTypeCLenovoSysEvent UserCommonUsbTypeCUserGetLenovoSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCLenovoCheckBusyResult UserCommonUsbTypeCUserCheckLenovoDockingEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))
