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
// ID Code      : ScalerDpMstRx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MST_RX_H__
#define __SCALER_DP_MST_RX_H__

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DP MSG Timeout
//--------------------------------------------------
#define _DP_MST_RX_DOWN_REPLY_MSG_TIME_OUT  SEC(0.5)
#define _DP_MST_RX_UP_REQUEST_MSG_TIME_OUT  SEC(0.5)

//--------------------------------------------------
// DP Message Error Type
//--------------------------------------------------
// #define GET_DP_RX_MSG_ERROR_TYPE()          (g_ucMsgErrorType)
// #define SET_DP_RX_MSG_ERROR_TYPE(x)         (g_ucMsgErrorType = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// DPRX MSG
extern void ScalerDpMstRxModeStatusCheck(void);
extern void ScalerDpMstRxMsgErrorHandler(void);
extern void ScalerDpMstRxMsgHandler(void);
extern bit ScalerDpMstRxDownRequestReceive(void);
extern bit ScalerDpMstRxDownRequestBurstRepeatHandle(void);
extern bit ScalerDpMstRxDownReplySend(void);
extern bit ScalerDpMstRxDownRequestAnal(void);
extern bit ScalerDpMstRxDownReplyAnal(void);
extern bit ScalerDpMstRxUpRequestSend(void);
extern bit ScalerDpMstRxUpReplyReceive(void);
extern bit ScalerDpMstRxUpRequestAnal(void);
extern bit ScalerDpMstRxUpReplyAnal(void);
extern bit ScalerDpMstRxDownRequestEventProc(void);
extern bit ScalerDpMstRxMsgAnalysis(void);
extern void ScalerDpMstRxDownReplyDirectlyMsg(void);
extern bit ScalerDpMstRxCheckMsgCRC(BYTE ucMSGDirection);
extern BYTE *ScalerDpMstRxGetEdidRamAddress(EnumInputPort enumInputPort);
extern WORD ScalerDpMstRxGetEdidRamSize(EnumInputPort enumInputPort);
extern bit ScalerDpMstRxDownRequestProc(void);
extern bit ScalerDpMstRxUpRequestProc(void);
extern bit ScalerDpMstRxUpReplyProc(void);
extern void ScalerDpMstRxTimerEventActiveHandler(void);

#if(_URGENT_EVENT_CHECK_MODE == _ON)
extern bit ScalerDpMstRxDownReqMsgCheckUrgent(void);
#endif

#if((_DP_TX_SUPPORT == _ON) || (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
extern void ScalerDpMstRxUpRequestEventCheckDone(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpMstRxQueryEncryptionBackupClientId(void);
#endif

// DPRX MST STREAM
extern void ScalerDpMstRxResetBackupInfo(EnumInputPort enumInputPort);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
extern EnumVirtualDpcdEntry ScalerDpMstRxGetVirtualDpcdEntry(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL);
extern EnumDpMSTSinkEventID ScalerDpMstRxGetVirtualDpSinkEventNotify(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort);
extern void ScalerDpMstRxClrVirtualDpSinkEventNotify(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, EnumDpMSTSinkEventID enumSinkEventID);
extern void ScalerDpMstRxVirtualDpUpRequestEventCheck(void);
extern void ScalerDpMstRxVirtualDpSenEventDelete(EnumDpMstRxUpReqQueue enumSenQueue);
extern EnumDpMstRxUpReqQueue ScalerDpMstRxVirtualDpSenEventCheck(void);

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void ScalerDpMstRxAdaptivesyncVirtualDpcdSetting(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern void ScalerDpMstRxFreesyncVirtualDpcdSetting(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort);
#endif
#endif
#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

#if((_DP_SUPPORT == _ON) && ((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)))
extern void ScalerDpMstRxResetStreamPositionReg(EnumInputPort enumInputPort);
#endif

#endif // End of #ifndef __SCALER_DP_MST_RX_H__
