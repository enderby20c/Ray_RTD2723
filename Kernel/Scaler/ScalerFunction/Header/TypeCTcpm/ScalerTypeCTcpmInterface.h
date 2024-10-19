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
// ID Code      : ScalerTypeCTcpmInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
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
// Main Loop
extern void ScalerTypeCTcpmInitial(void);
extern void ScalerTypeCTcpmInitialProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmHandler(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmSetDischargeCount(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucDischargeCount);
extern void ScalerTypeCTcpmSetOperationMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCOperationMode enumOperationMode);
extern void ScalerTypeCTcpmSetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower);
extern void ScalerTypeCTcpmSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucSPRPdoCnt, BYTE ucEPRPdoCnt);
extern void ScalerTypeCTcpmGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCnt, BYTE *pucEPRPdoCnt);
extern void ScalerTypeCTcpmSetFixPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumTypeCPDPeakCurType enumPeakCur);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern void ScalerTypeCTcpmSetPpsPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, BYTE ucMaxCur);
#endif
extern void ScalerTypeCTcpmSetAvsPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, EnumTypeCPDPeakCurType enumPeakCur);
extern StructTypeCUserPDO ScalerTypeCTcpmGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern BYTE ScalerTypeCTcpmGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO ScalerTypeCTcpmGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern StructTypeCStatusEvent ScalerTypeCTcpmGetPartnerStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCAlertEvent ScalerTypeCTcpmGetPartnerAlertInfo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent);
extern StructTypeCUserPDO ScalerTypeCTcpmGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmSetPdoByKernel(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeCTcpmSetSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo stTypeCSnkInfo);
extern void ScalerTypeCTcpmSetInitRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO stTypeCUserInitRdo);
extern void ScalerTypeCTcpmSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo);
extern void ScalerTypeCTcpmSetUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCUnconstrainPowerExist enumTypeCUnconstrainPowerExist);
extern void ScalerTypeCTcpmSetPdSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDSysEvent enumPdSysEvent);
extern EnumTypeCPDPortCtrlEvent ScalerTypeCTcpmGetPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmClrPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDPortCtrlEvent enumPdPortCtrlEvent);
extern void ScalerTypeCTcpmSetVbusProtectInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCVbusProtectInfo stTypeCVbusProtectInfo);
extern bit ScalerTypeCTcpmUpdateConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);
extern void ScalerTypeCTcpmWaitDpConfigUpdate(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmPowerSwitch(EnumTypeCPcbPort enumTypeCPcbPort, EnumPowerAction enumPowerAction);
extern void ScalerTypeCTcpmClockSetting(BYTE ucClockSel);
extern bit ScalerTypeCTcpmPowerControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerControlStatus enumPowerControlStatus);
extern bit ScalerTypeCTcpmReconnect(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmSetFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCFunctionSupport enumFunctionSupport);
extern StructTypeCDpStatusInfo ScalerTypeCTcpmGetDpStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCTcpmSetStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent stTypeCStatusEvent);
extern void ScalerTypeCTcpmSetAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent stTypeCAlertEvent);
extern EnumTypeCAttachStatus ScalerTypeCTcpmGetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCAltModeStatus ScalerTypeCTcpmGetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCOrientation ScalerTypeCTcpmGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCDataRole ScalerTypeCTcpmGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPowerRole ScalerTypeCTcpmGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit ScalerTypeCTcpmGetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit ScalerTypeCTcpmGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment);
extern bit ScalerTypeCTcpmGetMultiFunctionChangeDone(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCCablePdCapability ScalerTypeCTcpmGetCablePdCapability(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCUFPProductType ScalerTypeCTcpmGetUFPProductType(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCDFPProductType ScalerTypeCTcpmGetDFPProductType(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD ScalerTypeCTcpmGetCableMaxCurrent(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCCableInfoForDpcd ScalerTypeCTcpmGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort);

extern void ScalerTypeCTcpmCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction);

#if(_TYPE_C_PMIC_SUPPORT == _ON)
extern bit ScalerTypeCTcpmPmicIICRead(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
extern bit ScalerTypeCTcpmPmicIICWrite(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
#endif

// EXINT0
extern void ScalerTypeCTcpmIntHandler_EXINT0(void);

#if(_TYPE_C_PMIC_SUPPORT == _ON)
extern bit ScalerTypeCTcpmPmicIICRead_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
extern bit ScalerTypeCTcpmPmicIICWrite_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
#endif

// WDINT

#if(_TYPE_C_PMIC_SUPPORT == _ON)
extern bit ScalerTypeCTcpmPmicIICRead_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
extern bit ScalerTypeCTcpmPmicIICWrite_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
#endif

#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

