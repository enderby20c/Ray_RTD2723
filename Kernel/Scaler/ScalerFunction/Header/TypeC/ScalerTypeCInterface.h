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
// ID Code      : ScalerTypeCInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Type C PD VDM Related Definition
//--------------------------------------------------
// PD SVDM Version Option
#define _SVDM_VERSION_2_0_EARLIER                       0x00
#define _SVDM_VERSION_2_1                               0x01

#define _TYPE_C_SVDM_VERSION                            _SVDM_VERSION_2_1

//--------------------------------------------------
// Type C DP Related Definition
//--------------------------------------------------
// Dp Alt Mode Version Option
#define _DPAM_VERSION_NULL                              0x00
#define _DPAM_VERSION_1_0                               0x01
#define _DPAM_VERSION_2_0                               0x02
#define _DPAM_VERSION_2_1                               0x03

// Type C Dp Alt Mode Version Select
#define _TYPE_C_DPAM_VERSION                            _DPAM_VERSION_2_1

//--------------------------------------------------
// Type C Lenovo Alt Mode Related Macro
//--------------------------------------------------
#if(_PORT_CTRL_RTS_SUPPORT == _ON)
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#define GET_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT()   (g_bTypeCRtsLenovoAltModeUrgentEvent)
#define SET_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT()   (g_bTypeCRtsLenovoAltModeUrgentEvent = _TRUE)
#define CLR_TYPE_C_RTS_LENOVO_ALT_MODE_URGENT_EVENT()   (g_bTypeCRtsLenovoAltModeUrgentEvent = _FALSE)
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumeration Of USB-C Port Controller Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PORT_CTRL_NONE = 0x00,
    _TYPE_C_PORT_CTRL_RTS = 0x01,
    _TYPE_C_PORT_CTRL_EMBEDDED = 0x02,
    _TYPE_C_PORT_CTRL_USER = 0x03,
    _TYPE_C_PORT_CTRL_RTD = 0x04,
    _TYPE_C_PORT_CTRL_TCPM = 0x05,
}EnumTypeCPortCtrlType;

// Enumeration of DP Connect Status
typedef enum
{
    _PD_DP_CONNECT_NONE = 0x00,
    _PD_DP_TX_CONNECTED = 0x01,
    _PD_DP_RX_CONNECTED = 0x02,
    _PD_DP_TX_RX_BOTH_CONNECTED = 0x03,
}EnumTypeCDpConnectStatus;

// Enumeration of PD HPD State
typedef enum
{
    _PD_HPD_NONE = 0x00,
    _PD_HPD_IRQ = 0x01,
    _PD_HPD_LOW = 0x02,
    _PD_HPD_HIGH = 0x03,
}EnumTypeCPDHpdType;

// PD DP_Status Info
typedef struct
{
    EnumTypeCDpConnectStatus enumPartnerDpConnectStatus;
    // -----------------------------
    BYTE b1PartnerDpPowerLow : 1;
    BYTE b1PartnerDpFunctionEnabled : 1;
    BYTE b1PartnerMultiFunctionBit : 1;
    BYTE b1PartnerUsbConfigRequest : 1;
    BYTE b1PartnerDpAltModeExit : 1;
    // -----------------------------
    EnumTypeCPDHpdType enumPartnerHpdType;
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    BYTE b1PartnerNoDpAltSuspend : 1;
#endif
}StructTypeCDpStatusInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
extern EnumTypeCPcbPort g_penumTypeCEmbeddedPort[_EMB_TYPE_C_PORT_VALID];
#endif

#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
extern EnumTypeCPcbPort g_penumTypeCTcpmPort[_TCPM_PORT_VALID];
#endif

#if(_PORT_CTRL_RTS_SUPPORT == _ON)
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
extern bit g_bTypeCRtsLenovoAltModeUrgentEvent;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumTypeCPcbPort ScalerTypeCDxConvertToPcbPort(EnumInputPort enumInputPort);
extern EnumTypeCPcbPort ScalerTypeCPxConvertToPcbPort(EnumOutputPort enumOutputPort);
extern EnumTypeCPcbPort ScalerTypeCDxConvertToPcbPort_EXINT0(EnumInputPort enumInputPort);
extern EnumTypeCPcbPort ScalerTypeCPxConvertToPcbPort_EXINT0(EnumOutputPort enumOutputPort);
extern EnumTypeCPcbPort ScalerTypeCDxConvertToPcbPort_WDINT(EnumInputPort enumInputPort);
extern EnumTypeCPcbPort ScalerTypeCPxConvertToPcbPort_WDINT(EnumOutputPort enumOutputPort);
extern EnumInputPort ScalerTypeCPcbPortConvertToDx(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumOutputPort ScalerTypeCPcbPortConvertToPx(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumInputPort ScalerTypeCPcbPortConvertToDx_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumOutputPort ScalerTypeCPcbPortConvertToPx_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumInputPort ScalerTypeCPcbPortConvertToDx_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumOutputPort ScalerTypeCPcbPortConvertToPx_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCSetSysModeStatus(EnumSysModeStatusForUsb enumSysModeStatus);
extern void ScalerTypeCSetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCAttachStatus enumAttachStatus);
extern void ScalerTypeCSetOrientation(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCOrientation enumOrientation);
extern void ScalerTypeCSetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment);
extern void ScalerTypeCSetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCAltModeStatus enumAltModeStatus);
extern void ScalerTypeCSetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort, bit bGetExplicitContract);
extern void ScalerTypeCSetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd);
extern bit ScalerTypeCRxCheckTypeCSupportOn(EnumInputPort enumInputPort);
extern EnumTypeCPortCtrlType ScalerTypeCGetPortCtrlType(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPortCtrlType ScalerTypeCRxGetPortCtrlType(EnumInputPort enumInputPort);
extern EnumTypeCPortCtrlType ScalerTypeCTxGetPortCtrlType(EnumOutputPort enumOutputPort);
extern EnumTypeCPortCtrlType ScalerTypeCGetPortCtrlType_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPortCtrlType ScalerTypeCRxGetPortCtrlType_EXINT0(EnumInputPort enumInputPort);
extern EnumTypeCPortCtrlType ScalerTypeCTxGetPortCtrlType_EXINT0(EnumOutputPort enumOutputPort);
extern EnumTypeCPortCtrlType ScalerTypeCGetPortCtrlType_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPortCtrlType ScalerTypeCRxGetPortCtrlType_WDINT(EnumInputPort enumInputPort);
extern EnumTypeCPortCtrlType ScalerTypeCTxGetPortCtrlType_WDINT(EnumOutputPort enumOutputPort);
#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
extern void ScalerTypeCVbusPoweredSnkInitial(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern EnumTypeCEmbeddedList ScalerTypeCPcbxTypeCxMapping(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCEmbeddedList ScalerTypeCPcbxTypeCxMapping_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCEmbeddedList ScalerTypeCPcbxTypeCxMapping_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCHandler(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCClockSetting(BYTE ucClockSel);
extern EnumTypeCAttachStatus ScalerTypeCGetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCAltModeStatus ScalerTypeCGetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCOrientation ScalerTypeCGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit ScalerTypeCGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment);
extern bit ScalerTypeCGetMultiFunctionChangeDone(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCCableInfoForDpcd ScalerTypeCGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCSetDischargeCount(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucDischargeCount);
extern void ScalerTypeCSetPdSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDSysEvent enumPdSysEvent);
extern EnumTypeCPDPortCtrlEvent ScalerTypeCGetPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCClrPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDPortCtrlEvent enumPdPortCtrlEvent);
extern bit ScalerTypeCPowerControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerControlStatus enumPowerControlStatus);
extern void ScalerTypeCCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction);
extern void ScalerTypeCSetFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCFunctionSupport enumFunctionSupport);
extern void ScalerTypeCSetOperationMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCOperationMode enumOperationMode);
extern bit ScalerTypeCReconnect(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCWaitDpConfigUpdate(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit ScalerTypeCUpdateConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignmentCap);
extern void ScalerTypeCSetPdoByKernel(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeCSetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower);
extern void ScalerTypeCSetSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo stTypeCSnkInfo);
extern void ScalerTypeCSetStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent stTypeCStatusEvent);
extern void ScalerTypeCSetAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent stTypeCAlertEvent);
extern void ScalerTypeCSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucSPRPdoCnt, BYTE ucEPRPdoCnt);
extern void ScalerTypeCGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE *pucSPRPdoCnt, BYTE *pucEPRPdoCnt);
extern StructTypeCUserPDO ScalerTypeCGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern BYTE ScalerTypeCGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO ScalerTypeCGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern StructTypeCStatusEvent ScalerTypeCGetPartnerStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCAlertEvent ScalerTypeCGetPartnerAlertInfo(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCDataRole ScalerTypeCGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPowerRole ScalerTypeCGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit ScalerTypeCGetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent);
extern StructTypeCUserPDO ScalerTypeCGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCSetFixPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumTypeCPDPeakCurType enumPeakCur);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern void ScalerTypeCSetPpsPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, BYTE ucMaxCur);
#endif
extern void ScalerTypeCSetAvsPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, EnumTypeCPDPeakCurType enumPeakCur);
extern void ScalerTypeCSetInitRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO stTypeCUserInitRdo);
extern void ScalerTypeCSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo);
extern void ScalerTypeCSetUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCUnconstrainPowerExist enumTypeCUnconstrainPowerExist);
extern void ScalerTypeCSetVbusProtectInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCVbusProtectInfo stTypeCVbusProtectInfo);
extern EnumTypeCCablePdCapability ScalerTypeCGetCablePdCapability(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCUFPProductType ScalerTypeCGetUFPProductType(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCDFPProductType ScalerTypeCGetDFPProductType(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD ScalerTypeCGetCableMaxCurrent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCIntHandler_EXINT0(void);
extern void ScalerTypeCPowerSwitch(EnumPowerAction enumPowerAction);
extern bit ScalerTypeCRxGetHPDStatus(EnumInputPort enumInputPort);
extern StructTypeCDpStatusInfo ScalerTypeCGetDpStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern EnumTypeCLenovoAltModeStatus ScalerTypeCGetLenovoAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCLenovoDeviceType ScalerTypeCGetLenovoDeviceType(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCLenovoSysEvent ScalerTypeCGetLenovoSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCSetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
extern EnumTypeCLenovoCheckBusyResult ScalerTypeCCheckLenovoDockingEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern EnumTypeCAcerAltModeStatus ScalerTypeCGetAcerAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCAcerSysEvent ScalerTypeCGetAcerSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCSetAcerUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerUserEvent stAcerUserEvent);
extern EnumTypeCAcerBusyStatus ScalerTypeCCheckAcerUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern EnumTypeCHpAltModeStatus ScalerTypeCGetHpAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCHpSysEvent ScalerTypeCGetHpSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCSetHpUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpUserEvent stHpUserEvent);
extern EnumTypeCHpBusyStatus ScalerTypeCCheckHpUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern EnumTypeCDellAltModeStatus ScalerTypeCGetDellAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCDellSysEvent ScalerTypeCGetDellSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeCSetDellUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellUserEvent stDellUserEvent);
extern void ScalerTypeCSetDellAltModeInitComplete(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus);
extern EnumTypeCDellBusyStatus ScalerTypeCCheckDellUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCEnterDellAltModeTimeOut ScalerTypeCGetEnterDellAltModeTimeOut(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

#if(_USB_HUB_SUPPORT == _ON)
extern bit ScalerTypeCGetPdPRSwapProcessing(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit ScalerTypeCGetVbusStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif // End of #if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
extern void ScalerTypeCGpioModeInitialSetting(void);
extern EnumTypeCCcDetectStatus ScalerTypeCGetCcPinStatus(EnumTypeCEmbeddedList enumEmbTypeCIndex, EnumTypeCChannel enumTypeCChannel);
#endif  // End of #if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)