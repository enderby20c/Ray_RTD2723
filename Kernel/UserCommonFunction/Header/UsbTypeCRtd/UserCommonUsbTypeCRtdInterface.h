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
// ID Code      : UserCommonUsbTypeCRtdInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTD_SUPPORT == _ON))

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
extern void UserCommonUsbTypeCRtdInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtdUpdateStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCOrientation UserCommonUsbTypeCRtdGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbTypeCRtdGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment);
extern EnumTypeCDataRole UserCommonUsbTypeCRtdGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPowerRole UserCommonUsbTypeCRtdGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE UserCommonUsbTypeCRtdGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO UserCommonUsbTypeCRtdGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern BYTE UserCommonUsbTypeCRtdGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO UserCommonUsbTypeCRtdGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern void UserCommonUsbTypeCRtdGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent);
extern StructTypeCUserPDO UserCommonUsbTypeCRtdGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCCableInfoForDpcd UserCommonUsbTypeCRtdGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtdSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
extern void UserCommonUsbTypeCRtdSetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
extern void UserCommonUsbTypeCRtdSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo);
extern void UserCommonUsbTypeCRtdCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction);
extern void UserCommonUsbTypeCRtdSetTargetPowerMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern bit UserCommonUsbTypeCRtdReconnect(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtdStatusDetCtrl(EnumTypeCPcbPort enumTypeCPcbPort, bit bAction);
#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))
