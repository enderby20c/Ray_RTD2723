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
// ID Code      : ScalerTypeC1PdInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// Definitions of Alt Mode Support Count
#define _TYPE_C_1_PD_ALT_MODE_SUPPORT_CNT               ((_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) + (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))

// POWER ROLE SWAP OPTIONS (If DRP Must Support One Kind Of Swap)
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#define _TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK             _FALSE
#define _TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK            _FALSE
#define _TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC            _TRUE
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
#define _TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK             _TRUE
#define _TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK            _TRUE
#define _TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC            _TRUE
#endif

// DATA ROLE SWAP OPTIONS
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#define _TYPE_C_1_PD_DFP_SWAP_TO_UFP                    _TRUE
#define _TYPE_C_1_PD_UFP_SWAP_TO_DFP                    _FALSE
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
#define _TYPE_C_1_PD_DFP_SWAP_TO_UFP                    _FALSE
#define _TYPE_C_1_PD_UFP_SWAP_TO_DFP                    _TRUE
#endif

// Role Setting Macro
#define GET_TYPE_C_1_PD_POWER_ROLE()                    (BYTE)(g_stTypeC1PdStatus.b1PDPowerRole)
#define SET_TYPE_C_1_PD_POWER_ROLE(x)                   (g_stTypeC1PdStatus.b1PDPowerRole = (x))

#define GET_TYPE_C_1_PD_FUNCTION_EN()                   (g_stTypeC1PdStatus.b1PDFunctionEnable)
#define SET_TYPE_C_1_PD_FUNCTION_EN()                   (g_stTypeC1PdStatus.b1PDFunctionEnable = _TRUE)
#define CLR_TYPE_C_1_PD_FUNCTION_EN()                   (g_stTypeC1PdStatus.b1PDFunctionEnable = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructTypeCPDStatus g_stTypeC1PdStatus;
extern volatile StructTypeCCableStatus g_stTypeC1PdCableInfo;
extern volatile StructTypeCCableInfoForDpcd g_stTypeC1PdCableInfoForDpcd;
extern volatile StructTypeCMsgInfo g_stTypeC1PdMsgInfo;
extern volatile StructTypeCPdPartnerInfo g_stTypeC1PdPartnerInfo;
extern volatile StructTypeCEPRModeInfo g_stTypeC1PdEPRMode;
extern volatile StructTypeCAltModeInfo g_stTypeC1PdAltModeInfo;
extern volatile StructTypeCDpStatusInfo g_stTypeC1PdDpStatusInfo;
extern StructTypeCExtMsgInfo g_stTypeC1PdExtMsgInfo;
extern StructTypeCPDO g_pstTypeC1PdSrcPDO[_MAX_DATA_OBJ_CNT];
extern StructTypeCPDO g_pstTypeC1PdPartnerSrcCap[_MAX_DATA_OBJ_CNT];
extern volatile StructTypeCPDO g_pstTypeC1PdSnkCap[_MAX_DATA_OBJ_CNT];
extern StructTypeCPDO g_pstTypeC1PdPartnerSnkCap[_MAX_DATA_OBJ_CNT];
extern volatile StructTypeCSnkInfo g_stTypeC1PdSnkInfo;
extern volatile StructTypeCUserRDO g_stTypeC1PdSnkRDO;
extern volatile StructTypeCSnkRDO g_stTypeC1PdPartnerRDO;
extern volatile StructTypeCHpdQueue g_stTypeC1PdHpdQueue;
extern volatile StructTypeCPdTimerEvent g_stTypeC1PdTimerEvent;
extern volatile StructTypeCPdEvent g_stTypeC1PdEvent;
extern BYTE g_pucTypeC1PdDataObject[_MAX_DATA_OBJ_CNT * 4];
extern volatile StructTypeCPdoStatus g_stTypeC1PdPDOStatus;
extern volatile StructTypeCStatusEvent g_stTypeC1PdStatusEvent;
extern volatile StructTypeCAlertEvent g_stTypeC1PdAlertEvent;
extern volatile StructTypeCStatusEvent g_stTypeC1PdPartnerStatusEvent;
extern volatile StructTypeCAlertEvent g_stTypeC1PdPartnerAlertEvent;
extern BYTE g_pucTypeC1PdDataObject_EXINT[_MAX_DATA_OBJ_CNT * 4];
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern volatile StructTypeCAcerAltModeInfo g_stTypeC1PdAcerAltModeInfo;
extern volatile StructTypeCAcerSysEvent g_stTypeC1PdAcerSysEvent;
extern volatile StructTypeCAcerUserEvent g_stTypeC1PdAcerUserEvent;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern volatile StructTypeCHpAltModeInfo g_stTypeC1PdHpAltModeInfo;
extern volatile StructTypeCHpUserEvent g_stTypeC1PdHpUserEvent;
extern volatile StructTypeCHpSysEventQueue g_stTypeC1PdHpSysEventQueue;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern volatile StructTypeCDellAltModeInfo g_stTypeC1PdDellAltModeInfo;
extern volatile StructTypeCDellSysEvent g_stTypeC1PdDellSysEvent;
extern volatile StructTypeCDellUserEvent g_stTypeC1PdDellUserEvent;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// Main Loop
extern void ScalerTypeC1PdClkSel(BYTE ucClockSel);
extern void ScalerTypeC1PdInitial(void);
extern void ScalerTypeC1PdReset(void);
extern void ScalerTypeC1PdHandler(void);
extern void ScalerTypeC1PdPowerSwitch(EnumPowerAction enumPowerAction);
// PD FW Timer Event Flow
extern void ScalerTypeC1PdTimerEventProc(EnumScalerTimerEventID enumEventID);
// PD Send Msg. Functions
extern void ScalerTypeC1PdSendHardRst(void);
// PD FW Supplementary Functions
extern void ScalerTypeC1PdSetUnconstrainedPow(EnumTypeCUnconstrainPowerExist enumTypeCUnconstrainPowerExist);
extern void ScalerTypeC1PdSetPdoByKernel(EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeC1PdSetMaxPower(WORD usMaxPower);
extern void ScalerTypeC1PdSetSnkInfo(StructTypeCSnkInfo stTypeCSnkInfo);
extern void ScalerTypeC1PdSetStatusEvent(StructTypeCStatusEvent stTypeCStatusEvent);
extern void ScalerTypeC1PdSetAlertEvent(StructTypeCAlertEvent stTypeCAlertEvent);
extern void ScalerTypeC1PdSetSPRPdoCnt(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
extern BYTE ScalerTypeC1PdGetSPRPdoCnt(EnumTypeCPowerRole enumPowerRole);
#if(_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON)
extern void ScalerTypeC1PdSetEPRPdoCnt(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
extern BYTE ScalerTypeC1PdGetEPRPdoCnt(EnumTypeCPowerRole enumPowerRole);
#endif
extern StructTypeCUserPDO ScalerTypeC1PdGetPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern BYTE ScalerTypeC1PdGetPartnerPdoCnt(EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO ScalerTypeC1PdGetPartnerPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern StructTypeCStatusEvent ScalerTypeC1PdGetPartnerStatusInfo(void);
extern StructTypeCAlertEvent ScalerTypeC1PdGetPartnerAlertInfo(void);
extern void ScalerTypeC1PdGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent);
extern StructTypeCUserPDO ScalerTypeC1PdGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeC1PdSetFixPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumTypeCPDPeakCurType enumPeakCur);
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
extern void ScalerTypeC1PdSetArgumentedPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, BYTE ucMaxCur);
#endif
extern void ScalerTypeC1PdSetAdjustablePdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, EnumTypeCPDPeakCurType enumPeakCur);
extern void ScalerTypeC1PdSetInitRdo(StructTypeCUserInitRDO stTypeCUserInitRdo);
extern void ScalerTypeC1PdSetRdo(StructTypeCUserRDO stTypeCUserRdo);
extern bit ScalerTypeC1PdGetAltModeReady(void);
extern void ScalerTypeC1PdPushHpd(EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);
extern EnumTypeCPDHpdType ScalerTypeC1PdRxGetHPDQueue(BYTE ucIndex);
extern BYTE ScalerTypeC1PdRxGetHPDQueReadPointer(void);
extern bit ScalerTypeC1PdRxGetHPDStatus(void);
extern StructTypeCTxHpdQueue ScalerTypeC1PdTxGetHPDQueue(void);
extern EnumTypeCPinCfgType ScalerTypeC1PdGetPinAssignment(void);
extern void ScalerTypeC1PdSetPinAssignmentCapability(EnumTypeCPinCfgCapType enumPinAssignmentCap);
extern void ScalerTypeC1PdSetMultiFunctionBit(EnumTypeCMultiFuncStatus enumMultiFunc);
extern bit ScalerTypeC1PdGetMultiFunctionChangeDone(void);
extern void ScalerTypeC1PdWaitDpConfig(void);
extern void ScalerTypeC1PdSetSystemEvent(EnumTypeCPDSysEvent enumPdSysEvent);
extern EnumTypeCPDPortCtrlEvent ScalerTypeC1PdGetPortCtrlEvent(void);
extern void ScalerTypeC1PdClrPortCtrlEvent(EnumTypeCPDPortCtrlEvent enumPdPortCtrlEvent);
extern EnumTypeCDataRole ScalerTypeC1PdGetDataRole(void);
extern EnumTypeCPowerRole ScalerTypeC1PdGetPowerRole(void);
extern bit ScalerTypeC1PdGetExplicitContract(void);
extern bit ScalerTypeC1PdGetPRSwapProcesing(void);
extern void ScalerTypeC1PdSetVbusProtectInfo(BYTE ucPdoIndex, StructTypeCVbusProtectInfo stTypeCVbusProtectInfo);
extern void ScalerTypeC1PdClrInteropS8Flag(void);
extern EnumTypeCCablePdCapability ScalerTypeC1PdGetCablePdCapability(void);
extern EnumTypeCUFPProductType ScalerTypeC1PdGetUFPProductType(void);
extern EnumTypeCDFPProductType ScalerTypeC1PdGetDFPProductType(void);
extern WORD ScalerTypeC1PdGetCableMaxCurrent(void);
extern StructTypeCCableInfoForDpcd ScalerTypeC1PdGetCableInfoForDpcd(void);
extern void ScalerTypeC1PdSetFunctionSupport(EnumTypeCFunctionSupport enumFunctionSupport);
extern StructTypeCDpStatusInfo ScalerTypeC1PdGetDpStatusInfo(void);
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
extern void ScalerTypeC1PdDpCTSForceHpdIrq(void);
#endif
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern bit ScalerTypeC1PdGetLenovoAltModeReady(void);
extern EnumTypeCLenovoDeviceType ScalerTypeC1PdGetLenovoDeviceType(void);
extern StructTypeCLenovoSysEvent ScalerTypeC1PdGetLenovoSystemEvent(void);
extern void ScalerTypeC1PdSetLenovoDockingEvent(StructTypeCLenovoDockEvent stLenovoDockEvent);
extern EnumTypeCLenovoCheckBusyResult ScalerTypeC1PdCheckLenovoDockingEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern bit ScalerTypeC1PdGetAcerAltModeReady(void);
extern StructTypeCAcerSysEvent ScalerTypeC1PdGetAcerSystemEvent(void);
extern void ScalerTypeC1PdSetAcerUserEvent(StructTypeCAcerUserEvent stAcerUserEvent);
extern EnumTypeCAcerBusyStatus ScalerTypeC1PdCheckAcerUserEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern bit ScalerTypeC1PdGetHpAltModeReady(void);
extern StructTypeCHpSysEvent ScalerTypeC1PdGetHpSystemEvent(void);
extern void ScalerTypeC1PdSetHpUserEvent(StructTypeCHpUserEvent stHpUserEvent);
extern EnumTypeCHpBusyStatus ScalerTypeC1PdCheckHpUserEventBusy(void);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern bit ScalerTypeC1PdGetDellAltModeReady(void);
extern StructTypeCDellSysEvent ScalerTypeC1PdGetDellSystemEvent(void);
extern void ScalerTypeC1PdSetDellUserEvent(StructTypeCDellUserEvent stDellUserEvent);
extern void ScalerTypeC1PdSetDellAltModeInitComplete(EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus);
extern EnumTypeCDellBusyStatus ScalerTypeC1PdCheckDellUserEventBusy(void);
extern EnumTypeCEnterDellAltModeTimeOut ScalerTypeC1PdGetEnterDellAltModeTimeOut(void);
#endif
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_BILLBOARD_SUPPORT == _ON)
extern void ScalerTypeC1PdGetAltModeBillboardInfo(BYTE *pucBillboardAltModeInfo);
#endif

// EXINT0
// PD FW Flow
extern void ScalerTypeC1PdReset_EXINT0(void);
extern void ScalerTypeC1PdAttachedSetting_EXINT0(EnumTypeCPDState enumPdFwState);
extern void ScalerTypeC1PdIntHandler_EXINT0(void);
// PD Send Msg. Functions
extern void ScalerTypeC1PdSendHardRst_EXINT0(void);
// PD FW Supplementary Functions
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
extern void ScalerTypeC1PdDpCTSForceHpdIrq_EXINT0(void);
#endif
#endif
#endif
extern EnumTypeCPDSrcCapValid ScalerTypeC1PdCheckSrcCapValid_EXINT0(void);
extern void ScalerTypeC1PdPushHpd_EXINT0(EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);
extern EnumTypeCPowerRole ScalerTypeC1PdGetPowerRole_EXINT0(void);
extern bit ScalerTypeC1PdGetHardRstPowerOff_EXINT0(void);
extern void ScalerTypeC1PdClrInteropS8Flag_EXINT0(void);
extern void ScalerTypeC1PdSetSystemEvent_EXINT0(EnumTypeCPDSysEvent enumPdSysEvent);

// WDINT
// PD FW Timer Event Flow
extern void ScalerTypeC1PdWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
// PD Send Msg. Functions
extern void ScalerTypeC1PdSendHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
// PD FW Supplementary Functions
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
extern void ScalerTypeC1PdDpCTSForceHpdIrq_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
#endif
#endif
#endif
extern EnumTypeCPinCfgType ScalerTypeC1PdGetPinAssignment_WDINT(void);
extern void ScalerTypeC1PdSetSystemEvent_WDINT(EnumTypeCPDSysEvent enumPdSysEvent);

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))

