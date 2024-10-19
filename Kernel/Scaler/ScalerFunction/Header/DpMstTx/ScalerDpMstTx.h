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
// ID Code      : ScalerDpMstTx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MST_TX_H__
#define __SCALER_DP_MST_TX_H__


#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
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

// DPTX MSG
extern bit ScalerDpMstTxDownRequestSend(void);
extern bit ScalerDpMstTxDownReplyReceive(void);
extern bit ScalerDpMstTxDownRequestAnal(void);
extern bit ScalerDpMstTxDownReplyAnal(void);
extern bit ScalerDpMstTxUpRequestReceive(void);
extern bit ScalerDpMstTxUpReplySend(void);
extern bit ScalerDpMstTxUpRequestAnal(void);
extern bit ScalerDpMstTxUpReplyAnal(void);
extern bit ScalerDpMstTxDownRequestEventProc(void);
extern bit ScalerDpMstTxDownReplyEventProc(void);
extern bit ScalerDpMstTxWriteMsgToDownstreamStatusCheck(EnumDpMessageType enumMsgType);
extern void ScalerDpMstTxDownRequestHeaderModify(void);
extern void ScalerDpMstTxDownRequestBodyModfiy(void);
extern bit ScalerDpMstTxDownRequestMsgAnal(void);
extern void ScalerDpMstTxDownReplyDirectlyMsg(void);
extern void ScalerDpMstTxSetDownReplyEnumPathPBN(void);
extern bit ScalerDpMstTxGetDownReplyCrcFailed(void);
extern BYTE ScalerDpMstTxGetDownReplyLct(void);
extern BYTE ScalerDpMstTxGetDownReplyLcr(void);
extern bit ScalerDpMstTxGetDownReplyBroadcastBit(void);
extern bit ScalerDpMstTxGetDownReplyPathBit(void);
extern bit ScalerDpMstTxGetDownReplyMsn(void);
extern BYTE ScalerDpMstTxGetDownReplyLength(void);
extern void ScalerDpMstTxDownReplyBypassHeaderModify(void);
extern void ScalerDpMstTxDownReplyBypass(void);
extern void ScalerDpMstTxDownReplyHeaderBackUp(StructTxDownReplyMsgInterleaveHeaderInfo *pstTxDownReplyMsgHeaderInfo);
extern bit ScalerDpMstTxDownReplySidebandMsgHeaderCheck(StructTxDownReplyMsgInterleaveHeaderInfo stTxDownReplyMsgHeaderInfo);
extern void ScalerDpMstTxDownReplySideBandMsgProc(void);
extern void ScalerDpMstTxDownReplyInterleaveFinishCheck(void);
extern void ScalerDpMstTxClrDownReplyInterleaveFlag(void);
extern void ScalerDpMstTxCsnEventClearQueue(EnumDpMstTxUpReqQueue enumCsnQueue);
extern EnumDpMstTxUpReqQueue ScalerDpMstTxCsnEventCheck(void);
extern void ScalerDpMstTxCsnEventSinkCountUpdate(EnumDpMstTxUpReqQueue enumCsnQueue);
extern void ScalerDpMstTxUpRequestEventCheck(void);
extern EnumDpMstTxUpReqQueue ScalerDpMstTxSenEventCheck(void);
extern void ScalerDpMstTxSenEventClearQueue(EnumDpMstTxUpReqQueue enumSenQueue);

extern BYTE ScalerDpMstTxGetRegUpstreamMsgRad(BYTE ucRadIndex);
extern void ScalerDpMstTxSetRegDownstreamMsgRad(BYTE ucRadIndex, BYTE ucValue);

//void ScalerDpMacTxMonitorDownstreamBW(void);
//void ScalerDpMacTxLocalRecoveryPayloadTable(BYTE ucCurrentPBNPerTimerslot);
extern void ScalerDpMstTxModifyRAD(EnumDpMessageType enumMsgType);
extern void ScalerDpMstTxIllegalMsgReply(void);
extern bit ScalerDpMstTxI2CRead(void);
extern bit ScalerDpMstTxI2CWrite(BYTE ucI2CDeviceID, BYTE ucWriteNum, BYTE *pucData, bit bNoStop);
extern void ScalerDpMstTxQueryEncryptionWriteShaInput(void);
extern BYTE ScalerDpMstTxQueryEncryptionGetShaResult(BYTE ucIndex);
extern bit ScalerDpMstTxQueryEncryptionCompareShaResult(void);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpMstTxQueryEncryptionWriteSha256Input(bit bRepeater);
extern bit ScalerDpMstTxQueryEncryptionCompareSha256Result(void);
#endif

#endif


#endif // End of #ifndef __SCALER_DP_MST_TX_H__
