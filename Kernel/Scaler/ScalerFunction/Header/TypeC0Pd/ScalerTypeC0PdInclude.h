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
// ID Code      : ScalerTypeC0PdInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// Definitions of Alt Mode Support Count
#define _TYPE_C_0_PD_ALT_MODE_SUPPORT_CNT               ((_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON) + (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

// POWER ROLE SWAP OPTIONS (If DRP Must Support One Kind Of Swap)
#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#define _TYPE_C_0_PD_SRC_ACCEPT_SWAP_TO_SNK             _FALSE
#define _TYPE_C_0_PD_SRC_REQUEST_SWAP_TO_SNK            _FALSE
#define _TYPE_C_0_PD_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _TYPE_C_0_PD_SNK_REQUEST_SWAP_TO_SRC            _TRUE
#elif(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
#define _TYPE_C_0_PD_SRC_ACCEPT_SWAP_TO_SNK             _TRUE
#define _TYPE_C_0_PD_SRC_REQUEST_SWAP_TO_SNK            _TRUE
#define _TYPE_C_0_PD_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _TYPE_C_0_PD_SNK_REQUEST_SWAP_TO_SRC            _TRUE
#endif

// DATA ROLE SWAP OPTIONS
#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#define _TYPE_C_0_PD_DFP_SWAP_TO_UFP                    _TRUE
#define _TYPE_C_0_PD_UFP_SWAP_TO_DFP                    _FALSE
#elif(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
#define _TYPE_C_0_PD_DFP_SWAP_TO_UFP                    _FALSE
#define _TYPE_C_0_PD_UFP_SWAP_TO_DFP                    _TRUE
#endif

// Role Setting Macro
#define GET_TYPE_C_0_PD_POWER_ROLE()                    (BYTE)(g_stTypeC0PdStatus.b1PDPowerRole)
#define SET_TYPE_C_0_PD_POWER_ROLE(x)                   (g_stTypeC0PdStatus.b1PDPowerRole = (x))

#define GET_TYPE_C_0_PD_FUNCTION_EN()                   (g_stTypeC0PdStatus.b1PDFunctionEnable)
#define SET_TYPE_C_0_PD_FUNCTION_EN()                   (g_stTypeC0PdStatus.b1PDFunctionEnable = _TRUE)
#define CLR_TYPE_C_0_PD_FUNCTION_EN()                   (g_stTypeC0PdStatus.b1PDFunctionEnable = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructTypeCPDStatus g_stTypeC0PdStatus;
extern volatile StructTypeCCableStatus g_stTypeC0PdCableInfo;
extern volatile StructTypeCCableInfoForDpcd g_stTypeC0PdCableInfoForDpcd;
extern volatile StructTypeCMsgInfo g_stTypeC0PdMsgInfo;
extern volatile StructTypeCPdPartnerInfo g_stTypeC0PdPartnerInfo;
extern volatile StructTypeCEPRModeInfo g_stTypeC0PdEPRMode;
extern volatile StructTypeCAltModeInfo g_stTypeC0PdAltModeInfo;
extern volatile StructTypeCDpStatusInfo g_stTypeC0PdDpStatusInfo;
extern StructTypeCExtMsgInfo g_stTypeC0PdExtMsgInfo;
extern StructTypeCPDO g_pstTypeC0PdSrcPDO[_MAX_DATA_OBJ_CNT];
extern StructTypeCPDO g_pstTypeC0PdPartnerSrcCap[_MAX_DATA_OBJ_CNT];
extern volatile StructTypeCPDO g_pstTypeC0PdSnkCap[_MAX_DATA_OBJ_CNT];
extern StructTypeCPDO g_pstTypeC0PdPartnerSnkCap[_MAX_DATA_OBJ_CNT];
extern volatile StructTypeCSnkInfo g_stTypeC0PdSnkInfo;
extern volatile StructTypeCUserRDO g_stTypeC0PdSnkRDO;
extern volatile StructTypeCSnkRDO g_stTypeC0PdPartnerRDO;
extern volatile StructTypeCHpdQueue g_stTypeC0PdHpdQueue;
extern volatile StructTypeCPdTimerEvent g_stTypeC0PdTimerEvent;
extern volatile StructTypeCPdEvent g_stTypeC0PdEvent;
extern BYTE g_pucTypeC0PdDataObject[_MAX_DATA_OBJ_CNT * 4];
extern volatile StructTypeCPdoStatus g_stTypeC0PdPDOStatus;
extern volatile StructTypeCStatusEvent g_stTypeC0PdStatusEvent;
extern volatile StructTypeCAlertEvent g_stTypeC0PdAlertEvent;
extern volatile StructTypeCStatusEvent g_stTypeC0PdPartnerStatusEvent;
extern volatile StructTypeCAlertEvent g_stTypeC0PdPartnerAlertEvent;
extern BYTE g_pucTypeC0PdDataObject_EXINT[_MAX_DATA_OBJ_CNT * 4];
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern volatile StructTypeCAcerAltModeInfo g_stTypeC0PdAcerAltModeInfo;
extern volatile StructTypeCAcerSysEvent g_stTypeC0PdAcerSysEvent;
extern volatile StructTypeCAcerUserEvent g_stTypeC0PdAcerUserEvent;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern volatile StructTypeCHpAltModeInfo g_stTypeC0PdHpAltModeInfo;
extern volatile StructTypeCHpUserEvent g_stTypeC0PdHpUserEvent;
extern volatile StructTypeCHpSysEventQueue g_stTypeC0PdHpSysEventQueue;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern volatile StructTypeCDellAltModeInfo g_stTypeC0PdDellAltModeInfo;
extern volatile StructTypeCDellSysEvent g_stTypeC0PdDellSysEvent;
extern volatile StructTypeCDellUserEvent g_stTypeC0PdDellUserEvent;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// Main Loop
extern void ScalerTypeC0PdClkSel(BYTE ucClockSel);
extern void ScalerTypeC0PdInitial(void);
extern void ScalerTypeC0PdReset(void);
extern void ScalerTypeC0PdHandler(void);
extern void ScalerTypeC0PdPowerSwitch(EnumPowerAction enumPowerAction);
// PD FW Timer Event Flow
extern void ScalerTypeC0PdTimerEventProc(EnumScalerTimerEventID enumEventID);
// PD Send Msg. Functions
extern void ScalerTypeC0PdSendHardRst(void);
// PD FW Supplementary Functions
extern void ScalerTypeC0PdSetUnconstrainedPow(EnumTypeCUnconstrainPowerExist enumTypeCUnconstrainPowerExist);
extern void ScalerTypeC0PdSetPdoByKernel(EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeC0PdSetMaxPower(WORD usMaxPower);
extern void ScalerTypeC0PdSetSnkInfo(StructTypeCSnkInfo stTypeCSnkInfo);
extern void ScalerTypeC0PdSetStatusEvent(StructTypeCStatusEvent stTypeCStatusEvent);
extern void ScalerTypeC0PdSetAlertEvent(StructTypeCAlertEvent stTypeCAlertEvent);
extern void ScalerTypeC0PdSetSPRPdoCnt(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
extern BYTE ScalerTypeC0PdGetSPRPdoCnt(EnumTypeCPowerRole enumPowerRole);
#if(_EMB_TYPE_C_0_PD3_1_EPR_SUPPORT == _ON)
extern void ScalerTypeC0PdSetEPRPdoCnt(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
extern BYTE ScalerTypeC0PdGetEPRPdoCnt(EnumTypeCPowerRole enumPowerRole);
#endif
extern StructTypeCUserPDO ScalerTypeC0PdGetPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern BYTE ScalerTypeC0PdGetPartnerPdoCnt(EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO ScalerTypeC0PdGetPartnerPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern StructTypeCStatusEvent ScalerTypeC0PdGetPartnerStatusInfo(void);
extern StructTypeCAlertEvent ScalerTypeC0PdGetPartnerAlertInfo(void);
extern void ScalerTypeC0PdGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent);
extern StructTypeCUserPDO ScalerTypeC0PdGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeC0PdSetFixPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumTypeCPDPeakCurType enumPeakCur);
#if(_EMB_TYPE_C_0_PD3_PPS_SUPPORT == _ON)
extern void ScalerTypeC0PdSetArgumentedPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, BYTE ucMaxCur);
#endif
extern void ScalerTypeC0PdSetAdjustablePdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, EnumTypeCPDPeakCurType enumPeakCur);
extern void ScalerTypeC0PdSetInitRdo(StructTypeCUserInitRDO stTypeCUserInitRdo);
extern void ScalerTypeC0PdSetRdo(StructTypeCUserRDO stTypeCUserRdo);
extern bit ScalerTypeC0PdGetAltModeReady(void);
extern void ScalerTypeC0PdPushHpd(EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);
extern EnumTypeCPDHpdType ScalerTypeC0PdRxGetHPDQueue(BYTE ucIndex);
extern BYTE ScalerTypeC0PdRxGetHPDQueReadPointer(void);
extern bit ScalerTypeC0PdRxGetHPDStatus(void);
extern StructTypeCTxHpdQueue ScalerTypeC0PdTxGetHPDQueue(void);
extern EnumTypeCPinCfgType ScalerTypeC0PdGetPinAssignment(void);
extern void ScalerTypeC0PdSetPinAssignmentCapability(EnumTypeCPinCfgCapType enumPinAssignmentCap);
extern void ScalerTypeC0PdSetMultiFunctionBit(EnumTypeCMultiFuncStatus enumMultiFunc);
extern bit ScalerTypeC0PdGetMultiFunctionChangeDone(void);
extern void ScalerTypeC0PdWaitDpConfig(void);
extern void ScalerTypeC0PdSetSystemEvent(EnumTypeCPDSysEvent enumPdSysEvent);
extern EnumTypeCPDPortCtrlEvent ScalerTypeC0PdGetPortCtrlEvent(void);
extern void ScalerTypeC0PdClrPortCtrlEvent(EnumTypeCPDPortCtrlEvent enumPdPortCtrlEvent);
extern EnumTypeCDataRole ScalerTypeC0PdGetDataRole(void);
extern EnumTypeCPowerRole ScalerTypeC0PdGetPowerRole(void);
extern bit ScalerTypeC0PdGetExplicitContract(void);
extern bit ScalerTypeC0PdGetPRSwapProcesing(void);
extern void ScalerTypeC0PdSetVbusProtectInfo(BYTE ucPdoIndex, StructTypeCVbusProtectInfo stTypeCVbusProtectInfo);
extern void ScalerTypeC0PdClrInteropS8Flag(void);
extern EnumTypeCCablePdCapability ScalerTypeC0PdGetCablePdCapability(void);
extern EnumTypeCUFPProductType ScalerTypeC0PdGetUFPProductType(void);
extern EnumTypeCDFPProductType ScalerTypeC0PdGetDFPProductType(void);
extern WORD ScalerTypeC0PdGetCableMaxCurrent(void);
extern StructTypeCCableInfoForDpcd ScalerTypeC0PdGetCableInfoForDpcd(void);
extern void ScalerTypeC0PdSetFunctionSupport(EnumTypeCFunctionSupport enumFunctionSupport);
extern StructTypeCDpStatusInfo ScalerTypeC0PdGetDpStatusInfo(void);
#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
extern void ScalerTypeC0PdDpCTSForceHpdIrq(void);
#endif
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern bit ScalerTypeC0PdGetLenovoAltModeReady(void);
extern EnumTypeCLenovoDeviceType ScalerTypeC0PdGetLenovoDeviceType(void);
extern StructTypeCLenovoSysEvent ScalerTypeC0PdGetLenovoSystemEvent(void);
extern void ScalerTypeC0PdSetLenovoDockingEvent(StructTypeCLenovoDockEvent stLenovoDockEvent);
extern EnumTypeCLenovoCheckBusyResult ScalerTypeC0PdCheckLenovoDockingEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern bit ScalerTypeC0PdGetAcerAltModeReady(void);
extern StructTypeCAcerSysEvent ScalerTypeC0PdGetAcerSystemEvent(void);
extern void ScalerTypeC0PdSetAcerUserEvent(StructTypeCAcerUserEvent stAcerUserEvent);
extern EnumTypeCAcerBusyStatus ScalerTypeC0PdCheckAcerUserEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern bit ScalerTypeC0PdGetHpAltModeReady(void);
extern StructTypeCHpSysEvent ScalerTypeC0PdGetHpSystemEvent(void);
extern void ScalerTypeC0PdSetHpUserEvent(StructTypeCHpUserEvent stHpUserEvent);
extern EnumTypeCHpBusyStatus ScalerTypeC0PdCheckHpUserEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern bit ScalerTypeC0PdGetDellAltModeReady(void);
extern StructTypeCDellSysEvent ScalerTypeC0PdGetDellSystemEvent(void);
extern void ScalerTypeC0PdSetDellUserEvent(StructTypeCDellUserEvent stDellUserEvent);
extern void ScalerTypeC0PdSetDellAltModeInitComplete(EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus);
extern EnumTypeCDellBusyStatus ScalerTypeC0PdCheckDellUserEventBusy(void);
extern EnumTypeCEnterDellAltModeTimeOut ScalerTypeC0PdGetEnterDellAltModeTimeOut(void);
#endif
#endif  // Emd of #if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_BILLBOARD_SUPPORT == _ON)
extern void ScalerTypeC0PdGetAltModeBillboardInfo(BYTE *pucBillboardAltModeInfo);
#endif

// EXINT0
// PD FW Flow
extern void ScalerTypeC0PdReset_EXINT0(void);
extern void ScalerTypeC0PdAttachedSetting_EXINT0(EnumTypeCPDState enumPdFwState);
extern void ScalerTypeC0PdIntHandler_EXINT0(void);
// PD Send Msg. Functions
extern void ScalerTypeC0PdSendHardRst_EXINT0(void);
// PD FW Supplementary Functions
#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
extern void ScalerTypeC0PdDpCTSForceHpdIrq_EXINT0(void);
#endif
#endif
#endif
extern EnumTypeCPDSrcCapValid ScalerTypeC0PdCheckSrcCapValid_EXINT0(void);
extern void ScalerTypeC0PdPushHpd_EXINT0(EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);
extern EnumTypeCPowerRole ScalerTypeC0PdGetPowerRole_EXINT0(void);
extern bit ScalerTypeC0PdGetHardRstPowerOff_EXINT0(void);
extern void ScalerTypeC0PdClrInteropS8Flag_EXINT0(void);
extern void ScalerTypeC0PdSetSystemEvent_EXINT0(EnumTypeCPDSysEvent enumPdSysEvent);

// WDINT
// PD FW Timer Event Flow
extern void ScalerTypeC0PdWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
// PD Send Msg. Functions
extern void ScalerTypeC0PdSendHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
// PD FW Supplementary Functions
#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
extern void ScalerTypeC0PdDpCTSForceHpdIrq_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
#endif
#endif
#endif
extern EnumTypeCPinCfgType ScalerTypeC0PdGetPinAssignment_WDINT(void);
extern void ScalerTypeC0PdSetSystemEvent_WDINT(EnumTypeCPDSysEvent enumPdSysEvent);

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))

