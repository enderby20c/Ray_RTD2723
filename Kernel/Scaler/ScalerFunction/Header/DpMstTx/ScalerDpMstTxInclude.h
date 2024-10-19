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
// ID Code      : ScalerDpMstTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of RD Buffer Status
//--------------------------------------------------
#define _DP_MST_TX_I2C_MAX_TRANSACTION_LENGTH                       16
#define _DP_MST_TX_AUX_WRITE_BURST_LENGTH                           0x0F
#define _DP_MST_TX_AUX_READ_BURST_LENGTH                            0x0F

//--------------------------------------------------
// Macro of Downstream MSG Block
//--------------------------------------------------
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_AUTO_MODE()                {Scaler32SetBit(PB18083_00_MSG_WR_CTRL, ~_BIT2, 0x00);}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_ENABLE()             {Scaler32SetBit(PB18083_00_MSG_WR_CTRL, ~_BIT0, _BIT0);}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_DISABLE()            {Scaler32SetBit(PB18083_00_MSG_WR_CTRL, ~_BIT0, 0x00);}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_DISABLE_EXINT()      {Scaler32SetBit_EXINT0(PB18083_00_MSG_WR_CTRL, ~_BIT0, 0x00);}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_BURST_LENGTH(x)            {Scaler32SetBit(PB18083_0C_MSG_WR_BUR_LENGTH, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((x) & 0x0F));}
#define SET_DP_MST_TX_REG_DOWNSTREAM_TO_DOWN_REQUEST_ADDRESS()      {Scaler32SetBit(PB18083_00_MSG_WR_CTRL, ~_BIT8, 0x00);}
#define SET_DP_MST_TX_REG_DOWNSTREAM_TO_UP_REPLY_ADDRESS()          {Scaler32SetBit(PB18083_00_MSG_WR_CTRL, ~_BIT8, _BIT8);}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LCT(x)                     {Scaler32SetBit(PB18083_10_MSG_WR_SET0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((x) << 4));}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LCR(x)                     {Scaler32SetBit(PB18083_10_MSG_WR_SET0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x));}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_BROADCAST(x)               {Scaler32SetBit(PB18083_18_MSG_WR_SET2, ~_BIT7, ((x) << 7));}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_PATH(x)                    {Scaler32SetBit(PB18083_18_MSG_WR_SET2, ~_BIT6, ((x) << 6));}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_MSN(x)                     {Scaler32SetBit(PB18083_18_MSG_WR_SET2, ~_BIT12, ((x) << 12));}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LENGTH(x)                  {Scaler32SetByte(PB18083_08_MSG_WR_LENGTH, _REG8TO32_BYTE_0, (x));}
#define GET_DP_MST_TX_REG_DOWNSTREAM_MSG_LENGTH()                   (Scaler32GetByte(PB18083_08_MSG_WR_LENGTH, _REG8TO32_BYTE_0))
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_PTR(x)               {Scaler32SetByte(PB18083_28_BUF_FW_WRPTR, _REG8TO32_BYTE_0, ((x) & 0x3F));}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_PTR_EXINT(x)         {Scaler32SetByte_EXINT0(PB18083_28_BUF_FW_WRPTR, _REG8TO32_BYTE_0, ((x) & 0x3F));}
#define SET_DP_MST_TX_REG_DOWNSTREAM_MSG_DATA(x)                    {Scaler32SetByte(PB18083_2C_BUF_FW_WR_DATA, _REG8TO32_BYTE_0, (x));}
#define CLR_DP_MST_TX_REG_DOWNSTREAM_MSG_BUF()                      {Scaler32SetBit(PB18083_24_BUF_CLR, ~_BIT0, _BIT0);}
#define CLR_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_FINISH_FLAG()        {Scaler32SetDWord(PB18083_04_MSG_WR_FINISH, _BIT0);}
//--------------------------------------------------
// Macro of Upstream MSG Block
//--------------------------------------------------
#define SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_ENABLE()                {Scaler32SetBit(PB18083_80_AUX_TX_MSG_RD_CTRL, ~_BIT0, _BIT0);}
#define SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DISABLE()               {Scaler32SetBit(PB18083_80_AUX_TX_MSG_RD_CTRL, ~_BIT0, 0x00);}
#define SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DISABLE_EXINT()         {Scaler32SetBit_EXINT0(PB18083_80_AUX_TX_MSG_RD_CTRL, ~_BIT0, 0x00);}
#define SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_BURST_LENGTH(x)         {Scaler32SetByte(PB18083_90_MSG_RD_BUR_LENGTH, _REG8TO32_BYTE_0, (_BIT4 | ((x) & 0x0F)));}
#define SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_PTR(x)                  {Scaler32SetByte(PB18083_A0_MSG_BUF_RDPTR, _REG8TO32_BYTE_0, ((x) & 0x3F));}
#define SET_DP_MST_TX_REG_UPSTREAM_MSG_T0_DOWN_REPLY_ADDRESS()      {Scaler32SetBit(PB18083_80_AUX_TX_MSG_RD_CTRL, ~_BIT8, 0x00);}
#define SET_DP_MST_TX_REG_UPSTREAM_MSG_TO_UP_REQUEST_ADDRESS()      {Scaler32SetBit(PB18083_80_AUX_TX_MSG_RD_CTRL, ~_BIT8, _BIT8);}
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_LCT()                        ((Scaler32GetBit(PB18083_94_MSG_RD_DATA0, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> 4)
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_LCR()                        (Scaler32GetBit(PB18083_94_MSG_RD_DATA0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_BROADCAST()                  ((Scaler32GetBit(PB18083_9C_MSG_RD_DATA2, _BIT7)) >> 7)
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_PATH()                       ((Scaler32GetBit(PB18083_9C_MSG_RD_DATA2, _BIT6)) >> 6)
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_BODY_LENGTH()                (Scaler32GetBit(PB18083_9C_MSG_RD_DATA2, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_MSN()                        ((Scaler32GetBit(PB18083_9C_MSG_RD_DATA2, _BIT12)) >> 12)
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_LENGTH()                     (Scaler32GetByte(PB18083_8C_MSG_RD_LENGTH, _REG8TO32_BYTE_0))
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DATA()                  (Scaler32GetByte(PB18083_A4_MSG_BUF_RD_DATA, _REG8TO32_BYTE_0))
#define GET_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH()                (Scaler32GetBit(PB18083_88_MSG_RD_FINISH, _BIT0))
#define CLR_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH_FLAG()           {Scaler32SetDWord(PB18083_88_MSG_RD_FINISH, _BIT0);}
#define CLR_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH_FLAG_EXINT()     {Scaler32SetDWord_EXINT0(PB18083_88_MSG_RD_FINISH, _BIT0);}
#define CLR_DP_MST_TX_REG_UPSTREAM_SBMSG_FINISH_FLAG()              {Scaler32SetDWord(PB18083_88_MSG_RD_FINISH, _BIT1);}
#define CLR_DP_MST_TX_REG_UPSTREAM_SBMSG_FINISH_FLAG_EXINT()        {Scaler32SetDWord_EXINT0(PB18083_88_MSG_RD_FINISH, _BIT1);}
#define GET_DP_MST_TX_REG_UPSTREM_MSG_CRC_STATUS()                  (Scaler32GetBit(PB18083_9C_MSG_RD_DATA2, (_BIT25 | _BIT24)) == (_BIT25 | _BIT24))
#define GET_DP_MST_TX_REG_UPSTREM_MSG_HEADER_CRC_STATUS()           ((bit)Scaler32GetBit(PB18083_9C_MSG_RD_DATA2, _BIT25))
#define GET_DP_MST_TX_REG_UPSTREAM_SBMSG_START_OF_BIT()             ((bit)Scaler32GetBit(PB18083_9C_MSG_RD_DATA2, _BIT15))
#define GET_DP_MST_TX_REG_UPSTREAM_SBMSG_END_OF_BIT()               ((bit)Scaler32GetBit(PB18083_9C_MSG_RD_DATA2, _BIT14))
#define CLR_DP_MST_TX_REG_UPSTREAM_MSG_BUF()                        {Scaler32SetBit(PB18083_A8_MSG_BUF_CLR, ~_BIT0, _BIT0);}
#define CLR_DP_MST_TX_REG_UPSTREAM_MSG_BUF_EXINT()                  {Scaler32SetBit_EXINT0(PB18083_A8_MSG_BUF_CLR, ~_BIT0, _BIT0);}

//--------------------------------------------------
// Macro of QUERY STREAM ENCRYPTION STATUS
//--------------------------------------------------
#define SET_DP_MST_TX_REG_SHA_ENABLE()                              {ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT1 | _BIT0), 0x00);}
#define CLR_DP_MST_TX_REG_SHA_ENABLE()                              {ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT1 | _BIT0), _BIT1);}
#define SET_DP_MST_TX_REG_SHA_INPUT_0(x)                            {ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, (x));}
#define SET_DP_MST_TX_REG_SHA_INPUT_1(x)                            {ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, (x));}
#define SET_DP_MST_TX_REG_SHA_INPUT_2(x)                            {ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, (x));}
#define SET_DP_MST_TX_REG_SHA_INPUT_3(x)                            {ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, (x));}
#define SET_DP_MST_TX_REG_SHA_INPUT_DB()                            {ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);}
#define GET_DP_MST_TX_REG_HDCP_AN(x)                                (ScalerGetByte(PBB_3B_AN_BYTE_0 - (x)))
#define GET_DP_MST_TX_REG_HDCP_BKSV(x)                              (ScalerGetByte(PBB_4F_BKSV_0 + (x)))

#define GET_DP_MST_TX_HDCP_M0_0()                                   (GET_DP_TX_HDCP14_M0_0())
#define GET_DP_MST_TX_HDCP_M0_1()                                   (GET_DP_TX_HDCP14_M0_1())
#define GET_DP_MST_TX_HDCP_M0_2()                                   (GET_DP_TX_HDCP14_M0_2())
#define GET_DP_MST_TX_HDCP_M0_3()                                   (GET_DP_TX_HDCP14_M0_3())
#define GET_DP_MST_TX_HDCP_M0_4()                                   (GET_DP_TX_HDCP14_M0_4())
#define GET_DP_MST_TX_HDCP_M0_5()                                   (GET_DP_TX_HDCP14_M0_5())
#define GET_DP_MST_TX_HDCP_M0_6()                                   (GET_DP_TX_HDCP14_M0_6())
#define GET_DP_MST_TX_HDCP_M0_7()                                   (GET_DP_TX_HDCP14_M0_7())

#define GET_DP_MST_TX_HDCP_AUTH_PROC_PASS()                         (GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_AUTH_PASS)
#define GET_DP_MST_TX_HDCP_AUTH_PROCCESSING()                       (GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE)

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#define GET_DP_MST_TX_HDCP2_AUTH_PROC_PASS()                        (GET_DP_HDCP2_TX_AUTH_STATE() == _HDCP_2_2_TX_STATE_AUTHEN_DONE)
#define GET_DP_MST_TX_HDCP2_AUTH_PROCCESSING()                      (GET_DP_HDCP2_TX_AUTH_STATE() != _HDCP_2_2_TX_STATE_IDLE)
#endif

//--------------------------------------------------
// Macro of Message Function Action info
//--------------------------------------------------
#define GET_DP_MST_TX_DOWN_REQUEST_READY()                          (g_stDpMstTxMsgFunction.b1DownRequestReady)
#define SET_DP_MST_TX_DOWN_REQUEST_READY()                          (g_stDpMstTxMsgFunction.b1DownRequestReady = _TRUE)
#define CLR_DP_MST_TX_DOWN_REQUEST_READY()                          (g_stDpMstTxMsgFunction.b1DownRequestReady = _FALSE)

#define GET_DP_MST_TX_DOWN_REQUEST_ANAL()                           (g_stDpMstTxMsgFunction.b1DownRequestAnal)
#define SET_DP_MST_TX_DOWN_REQUEST_ANAL()                           (g_stDpMstTxMsgFunction.b1DownRequestAnal = _TRUE)
#define CLR_DP_MST_TX_DOWN_REQUEST_ANAL()                           (g_stDpMstTxMsgFunction.b1DownRequestAnal = _FALSE)

#define GET_DP_MST_TX_DOWN_REPLY_READY()                            (g_stDpMstTxMsgFunction.b1DownReplyReady)
#define SET_DP_MST_TX_DOWN_REPLY_READY()                            (g_stDpMstTxMsgFunction.b1DownReplyReady = _TRUE)
#define CLR_DP_MST_TX_DOWN_REPLY_READY()                            (g_stDpMstTxMsgFunction.b1DownReplyReady = _FALSE)

#define GET_DP_MST_TX_DOWN_REPLY_ANAL()                             (g_stDpMstTxMsgFunction.b1DownReplyAnal)
#define SET_DP_MST_TX_DOWN_REPLY_ANAL()                             (g_stDpMstTxMsgFunction.b1DownReplyAnal = _TRUE)
#define CLR_DP_MST_TX_DOWN_REPLY_ANAL()                             (g_stDpMstTxMsgFunction.b1DownReplyAnal = _FALSE)

#define GET_DP_MST_TX_DOWN_REPLY_DIRECTLY()                         (g_stDpMstTxMsgFunction.b1DownReplyDirect)
#define SET_DP_MST_TX_DOWN_REPLY_DIRECTLY()                         (g_stDpMstTxMsgFunction.b1DownReplyDirect = _TRUE)
#define CLR_DP_MST_TX_DOWN_REPLY_DIRECTLY()                         (g_stDpMstTxMsgFunction.b1DownReplyDirect = _FALSE)

#define GET_DP_MST_TX_DOWN_REPLY_READ_DISABLE()                     (g_stDpMstTxMsgFunction.b1DownReplyReadDisable)
#define SET_DP_MST_TX_DOWN_REPLY_READ_DISABLE()                     (g_stDpMstTxMsgFunction.b1DownReplyReadDisable = _TRUE)
#define CLR_DP_MST_TX_DOWN_REPLY_READ_DISABLE()                     (g_stDpMstTxMsgFunction.b1DownReplyReadDisable = _FALSE)

#define GET_DP_MST_TX_UP_REQUEST_READY()                            (g_stDpMstTxMsgFunction.b1UpRequestReady)
#define SET_DP_MST_TX_UP_REQUEST_READY()                            (g_stDpMstTxMsgFunction.b1UpRequestReady = _TRUE)
#define CLR_DP_MST_TX_UP_REQUEST_READY()                            (g_stDpMstTxMsgFunction.b1UpRequestReady = _FALSE)

#define GET_DP_MST_TX_UP_REQUEST_ANAL()                             (g_stDpMstTxMsgFunction.b1UpRequestAnal)
#define SET_DP_MST_TX_UP_REQUEST_ANAL()                             (g_stDpMstTxMsgFunction.b1UpRequestAnal = _TRUE)
#define CLR_DP_MST_TX_UP_REQUEST_ANAL()                             (g_stDpMstTxMsgFunction.b1UpRequestAnal = _FALSE)

#define GET_DP_MST_TX_UP_REPLY_READY()                              (g_stDpMstTxMsgFunction.b1UpReplyReady)
#define SET_DP_MST_TX_UP_REPLY_READY()                              (g_stDpMstTxMsgFunction.b1UpReplyReady = _TRUE)
#define CLR_DP_MST_TX_UP_REPLY_READY()                              (g_stDpMstTxMsgFunction.b1UpReplyReady = _FALSE)

#define GET_DP_MST_TX_UP_REPLY_BYPASS()                             (g_stDpMstTxMsgFunction.b1UpReplyBypass)
#define SET_DP_MST_TX_UP_REPLY_BYPASS()                             (g_stDpMstTxMsgFunction.b1UpReplyBypass = _TRUE)
#define CLR_DP_MST_TX_UP_REPLY_BYPASS()                             (g_stDpMstTxMsgFunction.b1UpReplyBypass = _FALSE)

#define GET_DP_MST_TX_UP_REPLY_DIRECTLY()                           (g_stDpMstTxMsgFunction.b1UpReplyDirect)
#define SET_DP_MST_TX_UP_REPLY_DIRECTLY()                           (g_stDpMstTxMsgFunction.b1UpReplyDirect = _TRUE)
#define CLR_DP_MST_TX_UP_REPLY_DIRECTLY()                           (g_stDpMstTxMsgFunction.b1UpReplyDirect = _FALSE)

//--------------------------------------------------
// Macro of Message Block info
//--------------------------------------------------
#define GET_DP_MST_TX_RD_BUFFER_STATUS()                            (g_stDpMstTxMsgInfo.b2RdBufferStatus)
#define SET_DP_MST_TX_RD_BUFFER_STATUS(x)                           (g_stDpMstTxMsgInfo.b2RdBufferStatus = (x))

#define GET_DP_MST_TX_DOWN_REQUEST_BROAD_MSG()                      (g_stDpMstTxMsgInfo.b1DownRequestBroadcastProc)
#define SET_DP_MST_TX_DOWN_REQUEST_BROAD_MSG()                      (g_stDpMstTxMsgInfo.b1DownRequestBroadcastProc = _TRUE)
#define CLR_DP_MST_TX_DOWN_REQUEST_BROAD_MSG()                      (g_stDpMstTxMsgInfo.b1DownRequestBroadcastProc = _FALSE)

#define GET_DP_MST_TX_DOWN_REQUEST_MSG_DONE()                       (g_stDpMstTxMsgInfo.b1DownRequestMsgDone)
#define SET_DP_MST_TX_DOWN_REQUEST_MSG_DONE()                       (g_stDpMstTxMsgInfo.b1DownRequestMsgDone = _TRUE)
#define CLR_DP_MST_TX_DOWN_REQUEST_MSG_DONE()                       (g_stDpMstTxMsgInfo.b1DownRequestMsgDone = _FALSE)

#define GET_DP_MST_TX_UP_REPLY_MSG_DONE()                           (g_stDpMstTxMsgInfo.b1UpReplyMsgDone)
#define SET_DP_MST_TX_UP_REPLY_MSG_DONE()                           (g_stDpMstTxMsgInfo.b1UpReplyMsgDone = _TRUE)
#define CLR_DP_MST_TX_UP_REPLY_MSG_DONE()                           (g_stDpMstTxMsgInfo.b1UpReplyMsgDone = _FALSE)

#define GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE()                  (g_stDpMstTxMsgInfo.enumUpReqIntiatedQueue)
#define SET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE(x)                 (g_stDpMstTxMsgInfo.enumUpReqIntiatedQueue = (x))
#define CLR_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE()                  (g_stDpMstTxMsgInfo.enumUpReqIntiatedQueue = _TX_UP_REQ_QUEUE_NONE)

#define GET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG()                    (g_stDpMstTxMsgInfo.b1IllegalDownRequestMSG)
#define SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG()                    (g_stDpMstTxMsgInfo.b1IllegalDownRequestMSG = _TRUE)
#define CLR_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG()                    (g_stDpMstTxMsgInfo.b1IllegalDownRequestMSG = _FALSE)

#define GET_DP_MST_TX_ILLEGAL_UP_REQUEST_MSG()                      (g_stDpMstTxMsgInfo.b1IllegalUpRequestMSG)
#define SET_DP_MST_TX_ILLEGAL_UP_REQUEST_MSG()                      (g_stDpMstTxMsgInfo.b1IllegalUpRequestMSG = _TRUE)
#define CLR_DP_MST_TX_ILLEGAL_UP_REQUEST_MSG()                      (g_stDpMstTxMsgInfo.b1IllegalUpRequestMSG = _FALSE)

#define GET_DP_MST_TX_GEN_UP_REQUEST_MSG()                          (g_stDpMstTxMsgInfo.ucGenUpRequestMsg)
#define SET_DP_MST_TX_GEN_UP_REQUEST_MSG(x)                         (g_stDpMstTxMsgInfo.ucGenUpRequestMsg = (x))
#define CLR_DP_MST_TX_GEN_UP_REQUEST_MSG()                          (g_stDpMstTxMsgInfo.ucGenUpRequestMsg = _DP_MSG_NONE)

#define GET_DP_MST_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE()    (g_stDpMstTxMsgInfo.b1DownReplyBroadcastDirectlyReplyDone)
#define SET_DP_MST_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE()    (g_stDpMstTxMsgInfo.b1DownReplyBroadcastDirectlyReplyDone = _TRUE)
#define CLR_DP_MST_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE()    (g_stDpMstTxMsgInfo.b1DownReplyBroadcastDirectlyReplyDone = _FALSE)

#define GET_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE()      (g_stDpMstTxMsgInfo.b1WaitClearPayloadIdTableDownReplyMsg)
#define SET_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE()      (g_stDpMstTxMsgInfo.b1WaitClearPayloadIdTableDownReplyMsg = _TRUE)
#define CLR_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE()      (g_stDpMstTxMsgInfo.b1WaitClearPayloadIdTableDownReplyMsg = _FALSE)

#define GET_DP_MST_TX_WAIT_TOPOLOGY_REBUILD_MSG()                   (g_stDpMstTxMsgInfo.b1WaitTopologyRebuildProcess)
#define SET_DP_MST_TX_WAIT_TOPOLOGY_REBUILD_MSG()                   (g_stDpMstTxMsgInfo.b1WaitTopologyRebuildProcess = _TRUE)
#define CLR_DP_MST_TX_WAIT_TOPOLOGY_REBUILD_MSG()                   (g_stDpMstTxMsgInfo.b1WaitTopologyRebuildProcess = _FALSE)

#define GET_DP_MST_TX_MSG_DURING_HPD_LOW_DEBOUNCE()                 (g_stDpMstTxMsgInfo.b1MsgDuringHpdLowDebounce)
#define SET_DP_MST_TX_MSG_DURING_HPD_LOW_DEBOUNCE()                 (g_stDpMstTxMsgInfo.b1MsgDuringHpdLowDebounce = _TRUE)
#define CLR_DP_MST_TX_MSG_DURING_HPD_LOW_DEBOUNCE()                 (g_stDpMstTxMsgInfo.b1MsgDuringHpdLowDebounce = _FALSE)

#if(_DP_MST_TX_PLUG_CSN_DEBOUNCE_SUPPORT == _ON)
#define GET_DP_MST_TX_PLUG_CSN_DEBOUNCING()                         (g_stDpMstTxMsgInfo.b1PlugCsnDebouncing)
#define SET_DP_MST_TX_PLUG_CSN_DEBOUNCING()                         (g_stDpMstTxMsgInfo.b1PlugCsnDebouncing = _TRUE)
#define CLR_DP_MST_TX_PLUG_CSN_DEBOUNCING()                         (g_stDpMstTxMsgInfo.b1PlugCsnDebouncing = _FALSE)
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MST_TX_ENUM_MSG_REPLY_TIMEOUT()                      (g_stDpMstTxMsgInfo.b1EnumMsgReplyTimeOut)
#define SET_DP_MST_TX_ENUM_MSG_REPLY_TIMEOUT()                      (g_stDpMstTxMsgInfo.b1EnumMsgReplyTimeOut = _TRUE)
#define CLR_DP_MST_TX_ENUM_MSG_REPLY_TIMEOUT()                      (g_stDpMstTxMsgInfo.b1EnumMsgReplyTimeOut = _FALSE)
#endif

//--------------------------------------------------
// Macro of Event Processor info
//--------------------------------------------------

#define GET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH()                (g_stDpMstTxEventProcInfo.b1MsgDownReqAnalFinish)
#define SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH()                (g_stDpMstTxEventProcInfo.b1MsgDownReqAnalFinish = _TRUE)
#define CLR_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH()                (g_stDpMstTxEventProcInfo.b1MsgDownReqAnalFinish = _FALSE)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH()                  (g_stDpMstTxEventProcInfo.b1MsgDownRepAnalFinish)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH()                  (g_stDpMstTxEventProcInfo.b1MsgDownRepAnalFinish = _TRUE)
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH()                  (g_stDpMstTxEventProcInfo.b1MsgDownRepAnalFinish = _FALSE)

//--------------------------------------------------
//Others
//--------------------------------------------------

#define GET_DP_MST_TX_DOWN_REQUEST_EVENT()                          (g_stDpMstTxEventProcInfo.b4MsgDownReqEventType)
#define SET_DP_MST_TX_DOWN_REQUEST_EVENT(x)                         (g_stDpMstTxEventProcInfo.b4MsgDownReqEventType = (x))
#define GET_DP_MST_TX_DOWN_REPLY_EVENT()                            (g_stDpMstTxEventProcInfo.b4MsgDownRepEventType)
#define SET_DP_MST_TX_DOWN_REPLY_EVENT(x)                           (g_stDpMstTxEventProcInfo.b4MsgDownRepEventType = (x))


//--------------------------------------------------
//DownReply SBMSG Interleave Macro
//--------------------------------------------------
#define GET_DP_MST_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE()             (g_stDpMstTxMsgInterleaveInfo.b1SidebandMsgInterLeaveReply)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE()             (g_stDpMstTxMsgInterleaveInfo.b1SidebandMsgInterLeaveReply = _TRUE)
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE()             (g_stDpMstTxMsgInterleaveInfo.b1SidebandMsgInterLeaveReply = _FALSE)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE()             (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf0CrcFailure)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE()             (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf0CrcFailure = _TRUE)
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE()             (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf0CrcFailure = _FALSE)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE()             (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf1CrcFailure)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE()             (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf1CrcFailure = _TRUE)
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE()             (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf1CrcFailure = _FALSE)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH()              (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf0Finish)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH()              (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf0Finish = _TRUE)
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH()              (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf0Finish = _FALSE)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH()              (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf1Finish)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH()              (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf1Finish = _TRUE)
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH()              (g_stDpMstTxMsgInterleaveInfo.b1DownReplyBuf1Finish = _FALSE)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT()           (g_stDpMstTxMsgInterleaveInfo.ucDownReplyStartCount)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT(x)          (g_stDpMstTxMsgInterleaveInfo.ucDownReplyStartCount = (x))
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT()           (g_stDpMstTxMsgInterleaveInfo.ucDownReplyStartCount = 0)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT()             (g_stDpMstTxMsgInterleaveInfo.ucDownReplyEndCount)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT(x)            (g_stDpMstTxMsgInterleaveInfo.ucDownReplyEndCount = (x))
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT()             (g_stDpMstTxMsgInterleaveInfo.ucDownReplyEndCount = 0)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH()             (g_stDpMstTxMsgInterleaveInfo.ucDownReplyBuf0DataLength)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH(x)            (g_stDpMstTxMsgInterleaveInfo.ucDownReplyBuf0DataLength = (x))
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH()             (g_stDpMstTxMsgInterleaveInfo.ucDownReplyBuf0DataLength = 0)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH()             (g_stDpMstTxMsgInterleaveInfo.ucDownReplyBuf1DataLength)
#define SET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH(x)            (g_stDpMstTxMsgInterleaveInfo.ucDownReplyBuf1DataLength = (x))
#define CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH()             (g_stDpMstTxMsgInterleaveInfo.ucDownReplyBuf1DataLength = 0)

#define GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA(x)                   (g_pucDpMstTxDownReplyBuf0Data[x])
#define SET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA(x, y)                (g_pucDpMstTxDownReplyBuf0Data[x] = (y))

#define GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA(x)                   (g_pucDpMstTxDownReplyBuf1Data[x])
#define SET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA(x, y)                (g_pucDpMstTxDownReplyBuf1Data[x] = (y))


//--------------------------------------------------
// Definitions of Tx Receipt Msg Count Macro
//--------------------------------------------------
#define GET_DP_MST_TX_RECEIVED_MSG_COUNT()                          (g_ucDpMstTxReceivedMsgCount)
#define SET_DP_MST_TX_RECEIVED_MSG_COUNT(x)                         (g_ucDpMstTxReceivedMsgCount = (x))


#define GET_DP_MST_TX_DOWN_REQUEST_BODY_LENGTH()                    (g_ucDpMstTxDownReqBodyLength)
#define SET_DP_MST_TX_DOWN_REQUEST_BODY_LENGTH(x)                   (g_ucDpMstTxDownReqBodyLength = (x))

#define GET_DP_MST_TX_UP_REPLY_BODY_LENGTH()                        (g_ucDpMstTxUpRepBodyLength)
#define SET_DP_MST_TX_UP_REPLY_BODY_LENGTH(x)                       (g_ucDpMstTxUpRepBodyLength = (x))

//--------------------------------------------------
// Definitions of Up Request Msg Header Info
//--------------------------------------------------
#define CLR_DP_MST_TX_UP_REQUEST_MSG_HEADER()                       (memset(&g_stDpMstTxUpReqMsgHeaderInfo, 0, sizeof(g_stDpMstTxUpReqMsgHeaderInfo)))

#define GET_DP_MST_TX_UP_REQUEST_MSG_HEADER()                       (g_stDpMstTxUpReqMsgHeaderInfo)

#define GET_DP_MST_TX_UP_REQUEST_MSG_LENGTH()                       (g_stDpMstTxUpReqMsgHeaderInfo.ucUpReqMsgLength)
#define SET_DP_MST_TX_UP_REQUEST_MSG_LENGTH(x)                      (g_stDpMstTxUpReqMsgHeaderInfo.ucUpReqMsgLength = (x))

#define GET_DP_MST_TX_UP_REQUEST_MSG_LCR()                          (g_stDpMstTxUpReqMsgHeaderInfo.b4UpReqMsgLCR)
#define SET_DP_MST_TX_UP_REQUEST_MSG_LCR(x)                         (g_stDpMstTxUpReqMsgHeaderInfo.b4UpReqMsgLCR = (x))

#define GET_DP_MST_TX_UP_REQUEST_MSG_LCT()                          (g_stDpMstTxUpReqMsgHeaderInfo.b4UpReqMsgLCT)
#define SET_DP_MST_TX_UP_REQUEST_MSG_LCT(x)                         (g_stDpMstTxUpReqMsgHeaderInfo.b4UpReqMsgLCT = (x))

#define GET_DP_MST_TX_UP_REQUEST_MSG_BROADCAST()                    (g_stDpMstTxUpReqMsgHeaderInfo.b1UpReqMsgBroadcast)
#define SET_DP_MST_TX_UP_REQUEST_MSG_BROADCAST(x)                   (g_stDpMstTxUpReqMsgHeaderInfo.b1UpReqMsgBroadcast = (x))

#define GET_DP_MST_TX_UP_REQUEST_MSG_PATH()                         (g_stDpMstTxUpReqMsgHeaderInfo.b1UpReqMsgPath)
#define SET_DP_MST_TX_UP_REQUEST_MSG_PATH(x)                        (g_stDpMstTxUpReqMsgHeaderInfo.b1UpReqMsgPath = (x))

#define GET_DP_MST_TX_UP_REQUEST_MSG_MSN()                          (g_stDpMstTxUpReqMsgHeaderInfo.b1UpReqMsgMsn)
#define SET_DP_MST_TX_UP_REQUEST_MSG_MSN(x)                         (g_stDpMstTxUpReqMsgHeaderInfo.b1UpReqMsgMsn = (x))

#define GET_DP_MST_TX_UP_REQUEST_MSG_READ_FINISH()                  (g_stDpMstTxUpReqMsgHeaderInfo.b1UpReqMsgReadFinish)
#define SET_DP_MST_TX_UP_REQUEST_MSG_READ_FINISH(x)                 (g_stDpMstTxUpReqMsgHeaderInfo.b1UpReqMsgReadFinish = (x))

//Connection Status Notify MSG
#define GET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_BODY()          (g_unDpMstRxRequestPool.stConnectionStatusNotify)
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_BODY(x)         (memcpy(&g_unDpMstRxRequestPool.stConnectionStatusNotify, &(x), sizeof(g_unDpMstRxRequestPool.stConnectionStatusNotify)))
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PORT_NUM(x)     (g_unDpMstRxRequestPool.stConnectionStatusNotify.b4PortNum = (x))
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_GUID(x, y)      (g_unDpMstRxRequestPool.stConnectionStatusNotify.pucGUID[x] = (y))
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PEER_DEVICE_TYPE(x)\
                                                                    (g_unDpMstRxRequestPool.stConnectionStatusNotify.b3PeerDeviceType = (x))
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_INPUT_PORT(x)   (g_unDpMstRxRequestPool.stConnectionStatusNotify.b1InputPort = (x))
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_MSG_CAP(x)      (g_unDpMstRxRequestPool.stConnectionStatusNotify.b1MsgCabability = (x))
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PLUG_STATUS(x)  (g_unDpMstRxRequestPool.stConnectionStatusNotify.b1DpPlugStatus = (x))
#define GET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PLUG_STATUS()   (g_unDpMstRxRequestPool.stConnectionStatusNotify.b1DpPlugStatus)
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_LEGACY_PLUG_STATUS(x)\
                                                                    (g_unDpMstRxRequestPool.stConnectionStatusNotify.b1LegacyPlugStatus = (x))
#define SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_ZEROS()         {\
                                                                        g_unDpMstRxRequestPool.stConnectionStatusNotify.b1Zero = 0;\
                                                                        g_unDpMstRxRequestPool.stConnectionStatusNotify.b4Zero1 = 0;\
                                                                        g_unDpMstRxRequestPool.stConnectionStatusNotify.b1Zero2 = 0;\
                                                                    }

//Resource Status Notify MSG
#define SET_DP_MST_TX_REQUEST_MSG_RESOURCE_STATUS_PORT_NUM(x)       (g_unDpMstRxRequestPool.stStructReqResourceStatusNotify.b4PortNum = (x))
#define SET_DP_MST_TX_REQUEST_MSG_RESOURCE_STATUS_GUID(x, y)        (g_unDpMstRxRequestPool.stStructReqResourceStatusNotify.pucGUID[x] = (y))
#define SET_DP_MST_TX_REQUEST_MSG_RESOURCE_STATUS_AVAILABLE_PBN(x)  {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        g_unDpMstRxRequestPool.stStructReqResourceStatusNotify.pucAvailablePBN[0] = HIBYTE(usLocalValue);\
                                                                        g_unDpMstRxRequestPool.stStructReqResourceStatusNotify.pucAvailablePBN[1] = LOBYTE(usLocalValue);\
                                                                    }
#define SET_DP_MST_TX_REQUEST_MSG_RESORUCE_STATUS_ZEROS()           {\
                                                                        g_unDpMstRxRequestPool.stStructReqResourceStatusNotify.b1Zero = 0;\
                                                                        g_unDpMstRxRequestPool.stStructReqResourceStatusNotify.b4Zero1 = 0;\
                                                                    }

//Sink Event Notify MSG
#define GET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_BODY()                 (g_unDpMstRxRequestPool.stStructReqSinkEventNotify)
#define SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_PORT_NUM(x)            (g_unDpMstRxRequestPool.stStructReqSinkEventNotify.b4PortNum = (x))
#define SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_GUID(x, y)             (g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucGUID[x] = (y))
#define GET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_ID(x)                  (\
                                                                        TO_WORD(\
                                                                            g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucEventID[0],\
                                                                            g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucEventID[1])\
                                                                    )
#define SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_ID(x)                  {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucEventID[0] = HIBYTE(usLocalValue);\
                                                                        g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucEventID[1] = LOBYTE(usLocalValue);\
                                                                    }
#define SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_ZEROS()                {\
                                                                        g_unDpMstRxRequestPool.stStructReqSinkEventNotify.b1Zero = 0;\
                                                                        g_unDpMstRxRequestPool.stStructReqSinkEventNotify.b4Zero1 = 0;\
                                                                    }

// Allocate Payload MSG
#define SET_DP_MST_TX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN(x)      {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        g_unDpMstRxRequestPool.stAllocatePayload.pucPBN[0] = HIBYTE(usLocalValue);\
                                                                        g_unDpMstRxRequestPool.stAllocatePayload.pucPBN[1] = LOBYTE(usLocalValue);\
                                                                    }

#define SET_DP_MST_TX_MSG_REQUEST_ID(x)                             (g_unDpMstRxRequestPool.pucData[0] = (x))

#define GET_DP_MST_TX_BYPASS_CSN_BACKUP(x)                          (g_pstDpMstTxBypassCsnQueue[x])
#define SET_DP_MST_TX_BYPASS_CSN_BACKUP(x, y)                       (memcpy(&g_pstDpMstTxBypassCsnQueue[x], &(y), sizeof(g_pstDpMstTxBypassCsnQueue[x])))
#define CLR_DP_MST_TX_BYPASS_CSN_BACKUP(x)                          (memset(&g_pstDpMstTxBypassCsnQueue[x], 0, sizeof(g_pstDpMstTxBypassCsnQueue[x])))

#define SET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_HEADER(x, y)            (memcpy(&g_pstDpMstTxBypassCsnQueue[x].stCsnHeader, &(y), sizeof(g_pstDpMstTxBypassCsnQueue[x].stCsnHeader)))
#define CLR_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_HEADER(x)               (memset(&g_pstDpMstTxBypassCsnQueue[x].stCsnHeader, 0, sizeof(g_pstDpMstTxBypassCsnQueue[x].stCsnHeader)))

#define SET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_BODY(x, y)              (memcpy(&g_pstDpMstTxBypassCsnQueue[x].stCsnBody, &(y), sizeof(g_pstDpMstTxBypassCsnQueue[x].stCsnBody)))
#define CLR_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_BODY(x)                 (memset(&g_pstDpMstTxBypassCsnQueue[x].stCsnBody, 0, sizeof(g_pstDpMstTxBypassCsnQueue[x].stCsnBody)))

#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_HEADER(x)               (g_pstDpMstTxBypassCsnQueue[x].stCsnHeader)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LENGTH(x)               (g_pstDpMstTxBypassCsnQueue[x].stCsnHeader.ucUpReqMsgLength)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCR(x)                  (g_pstDpMstTxBypassCsnQueue[x].stCsnHeader.b4UpReqMsgLCR)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCT(x)                  (g_pstDpMstTxBypassCsnQueue[x].stCsnHeader.b4UpReqMsgLCT)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_BROADCAST(x)            (g_pstDpMstTxBypassCsnQueue[x].stCsnHeader.b1UpReqMsgBroadcast)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_PATH(x)                 (g_pstDpMstTxBypassCsnQueue[x].stCsnHeader.b1UpReqMsgPath)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_MSN(x)                  (g_pstDpMstTxBypassCsnQueue[x].stCsnHeader.b1UpReqMsgMsn)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_READ_FINISH(x)          (g_pstDpMstTxBypassCsnQueue[x].stCsnHeader.b1UpReqMsgReadFinish)

#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_BODY(x)                 (g_pstDpMstTxBypassCsnQueue[x].stCsnBody)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_ID(x)                   (g_pstDpMstTxBypassCsnQueue[x].stCsnBody.b7ReqID)
#define GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_DP_PLUG_STATUS(x)       (g_pstDpMstTxBypassCsnQueue[x].stCsnBody.b1DpPlugStatus)

//--------------------------------------------------
// Define Output Port Queue Info Macro
//--------------------------------------------------
#define GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(x)                 (g_pstDpMstTxCsnQueueInfo[0].pstTxMstCsnEvent[x].enumTxMstPxPortConnectStatus)
#define SET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(x, y)              (g_pstDpMstTxCsnQueueInfo[0].pstTxMstCsnEvent[x].enumTxMstPxPortConnectStatus = (y))
#define CLR_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(x)                 {\
                                                                        g_pstDpMstTxCsnQueueInfo[0].pstTxMstCsnEvent[x].enumTxMstPxPortConnectStatus = _CONNECT_STATUS_NONE;\
                                                                        g_pstDpMstTxCsnQueueInfo[0].pstTxMstCsnEvent[x].enumTargetInputPort = _NO_INPUT_PORT;\
                                                                    }
#define GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(x)            (g_pstDpMstTxCsnQueueInfo[0].pstTxMstCsnEvent[x].enumTargetInputPort)
#define SET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(x, y)         (g_pstDpMstTxCsnQueueInfo[0].pstTxMstCsnEvent[x].enumTargetInputPort = (y))

//--------------------------------------------------
// Define Portx Edid Read Position Macro
//--------------------------------------------------
#define GET_DP_MST_TX_EDID_READ_SEGMENT()                           (g_punDpMstTxPortEdidReadPosition[0].pucData[0])
#define SET_DP_MST_TX_EDID_READ_SEGMENT(x)                          (g_punDpMstTxPortEdidReadPosition[0].pucData[0] = (x))

#define GET_DP_MST_TX_EDID_READ_OFFSET()                            (g_punDpMstTxPortEdidReadPosition[0].pucData[1])
#define SET_DP_MST_TX_EDID_READ_OFFSET(x)                           (g_punDpMstTxPortEdidReadPosition[0].pucData[1] = (x))

#define GET_DP_MST_TX_EDID_READ_POSITION()                          (\
                                                                        TO_WORD(\
                                                                            g_punDpMstTxPortEdidReadPosition[0].pucData[0],\
                                                                            g_punDpMstTxPortEdidReadPosition[0].pucData[1])\
                                                                    )
#define SET_DP_MST_TX_EDID_READ_POSITION(x)                         {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        g_punDpMstTxPortEdidReadPosition[0].pucData[0] = HIBYTE(usLocalValue);\
                                                                        g_punDpMstTxPortEdidReadPosition[0].pucData[1] = LOBYTE(usLocalValue);\
                                                                    }

#define INC_DP_MST_TX_EDID_READ_POSITION(x)                         {\
                                                                        WORD usLocalDpMstTxEdidPosition = GET_DP_MST_TX_EDID_READ_POSITION() + (x);\
                                                                        SET_DP_MST_TX_EDID_READ_POSITION(usLocalDpMstTxEdidPosition);\
                                                                    }

#define CLR_DP_MST_TX_EDID_READ_POSITION()                          {SET_DP_MST_TX_EDID_READ_POSITION(0);}

//--------------------------------------------------
// Define of Sink Event Macro
//--------------------------------------------------
#define GET_DP_MST_TX_SINK_EVENT_ID()                               (g_penumDpMstTxSinkEventID[0])
#define SET_DP_MST_TX_SINK_EVENT_ID(x)                              (g_penumDpMstTxSinkEventID[0] |= (x))
#define CLR_DP_MST_TX_SINK_EVENT_ID(x)                              (g_penumDpMstTxSinkEventID[0] &= (EnumDpMSTSinkEventID)~(x))

#define GET_DP_MST_TX_BYPASS_SEN_BACKUP(x)                          (g_pstDpMstTxBypassSenQueue[x])
#define SET_DP_MST_TX_BYPASS_SEN_BACKUP(x, y)                       (memcpy(&g_pstDpMstTxBypassSenQueue[x], &(y), sizeof(g_pstDpMstTxBypassSenQueue[x])))
#define CLR_DP_MST_TX_BYPASS_SEN_BACKUP(x)                          (memset(&g_pstDpMstTxBypassSenQueue[x], 0, sizeof(g_pstDpMstTxBypassSenQueue[x])))

#define GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_EVENT_ID(x)             (\
                                                                        TO_WORD(g_pstDpMstTxBypassSenQueue[x].stSenBody.pucEventID[0],\
                                                                                g_pstDpMstTxBypassSenQueue[x].stSenBody.pucEventID[1])\
                                                                    )

#define SET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_HEADER(x, y)            (memcpy(&g_pstDpMstTxBypassSenQueue[x].stSenHeader, &(y), sizeof(g_pstDpMstTxBypassSenQueue[x].stSenHeader)))
#define CLR_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_HEADER(x)               (memset(&g_pstDpMstTxBypassSenQueue[x].stSenBody, 0, sizeof(g_pstDpMstTxBypassSenQueue[x].stSenBody)))

#define GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_LENGTH(x)               (g_pstDpMstTxBypassSenQueue[x].stSenHeader.ucUpReqMsgLength)
#define GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_LCR(x)                  (g_pstDpMstTxBypassSenQueue[x].stSenHeader.b4UpReqMsgLCR)
#define GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_LCT(x)                  (g_pstDpMstTxBypassSenQueue[x].stSenHeader.b4UpReqMsgLCT)
#define GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_BROADCAST(x)            (g_pstDpMstTxBypassSenQueue[x].stSenHeader.b1UpReqMsgBroadcast)
#define GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_PATH(x)                 (g_pstDpMstTxBypassSenQueue[x].stSenHeader.b1UpReqMsgPath)

#define GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_BODY(x)                 (g_pstDpMstTxBypassSenQueue[x].stSenBody)
#define SET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_BODY(x, y)              (memcpy(&g_pstDpMstTxBypassSenQueue[x].stSenBody, &(y), sizeof(g_pstDpMstTxBypassSenQueue[x].stSenBody)))
#define CLR_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_BODY(x)                 (memset(&g_pstDpMstTxBypassSenQueue[x].stSenBody, 0, sizeof(g_pstDpMstTxBypassSenQueue[x].stSenBody)))

#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
#define GET_DP_MST_TX_INTERCEPT_DDCCI_MSG_STATUS()                  (g_bDpMstTxInterceptDdcciMsg)
#define SET_DP_MST_TX_INTERCEPT_DDCCI_MSG_STATUS(x)                 (g_bDpMstTxInterceptDdcciMsg = (x))

#define GET_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR()              (g_bDpMstTxInterceptDdcciMsgAdjustLCR)
#define SET_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR()              (g_bDpMstTxInterceptDdcciMsgAdjustLCR = _TRUE)
#define CLR_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR()              (g_bDpMstTxInterceptDdcciMsgAdjustLCR = _FALSE)
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_GLOBAL_ENABLE() (g_ucDpMstTx128b132bTo8b10bMsaConvertFlag != 0x00)
#define SET_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(x)       (g_ucDpMstTx128b132bTo8b10bMsaConvertFlag |= (_BIT0 << (x)))
#define GET_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(x)       (g_ucDpMstTx128b132bTo8b10bMsaConvertFlag >> (x) & _BIT0)
#define CLR_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(x)       (g_ucDpMstTx128b132bTo8b10bMsaConvertFlag &= ~(_BIT0 << (x)))

#define SET_DP_MST_TX_128B132B_MSA_VIDEO_FREQ(x, y)                 (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].ul128b132bMsaVfreq = (y))
#define GET_DP_MST_TX_128B132B_MSA_VIDEO_FREQ(x)                    (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].ul128b132bMsaVfreq)
#define CLR_DP_MST_TX_128B132B_MSA_VIDEO_FREQ(x)                    (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].ul128b132bMsaVfreq = 0)

#define SET_DP_MST_TX_128B132B_MSA_AUDIO_FREQ(x, y)                 (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].ul128b132bMsaAfreq = (y))
#define GET_DP_MST_TX_128B132B_MSA_AUDIO_FREQ(x)                    (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].ul128b132bMsaAfreq)
#define CLR_DP_MST_TX_128B132B_MSA_AUDIO_FREQ(x)                    (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].ul128b132bMsaAfreq = 0)

#define SET_DP_MST_TX_128B132B_MSA_COLOR_DEPTH(x, y)                (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].b2ColorDepth = (y))
#define GET_DP_MST_TX_128B132B_MSA_COLOR_DEPTH(x)                   (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].b2ColorDepth)
#define CLR_DP_MST_TX_128B132B_MSA_COLOR_DEPTH(x)                   (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].b2ColorDepth = 0)

#define SET_DP_MST_TX_128B132B_MSA_COLOR_SPACE(x, y)                (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].b3ColorSpace = (y))
#define GET_DP_MST_TX_128B132B_MSA_COLOR_SPACE(x)                   (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].b3ColorSpace)
#define CLR_DP_MST_TX_128B132B_MSA_COLOR_SPACE(x)                   (g_pstDpMstTx128b132bTo8b10bMsaInfo[x].b3ColorSpace = 0)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DP Tx Event Which Result From Message
//--------------------------------------------------
typedef enum
{
    _DP_TX_NONE_EVENT,
    _DP_TX_SYNC_PAYLOAD_TABLE,
    _DP_TX_CLEAR_ID_TABLE,
    _DP_TX_POWER_UP,
    _DP_TX_POWER_DOWN,
    _DP_TX_DPCD_READ,
    _DP_TX_DPCD_WRITE,
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
    _DP_TX_VIRTUAL_DPCD_READ,
    _DP_TX_VIRTUAL_DPCD_WRITE,
#endif
    _DP_TX_I2C_READ,
    _DP_TX_I2C_WRITE,
    _DP_TX_ENUM_PATH,
    _DP_TX_QUERY_STREAM_ENCRYPTION_STATUS,
} EnumTxEventType;

typedef enum
{
    _DP_TX_READ_BUF_EMPTY,
    _DP_TX_READ_BUF_DOWN_REPLY_IN_USE,
    _DP_TX_READ_BUF_UP_REQUEST_IN_USE,
} EnumTxReadBufferStatus;

typedef enum
{
    // MSG Header
    _UP_REQ_BACK_UP_LCT,
    _UP_REQ_BACK_UP_LCR,
    _UP_REQ_BACK_UP_BROADCAST,
    _UP_REQ_BACK_UP_PATH,
    _UP_REQ_BACK_UP_MSG_LENGTH,
    _UP_REQ_BACK_UP_MSG_MSN,

    // MSG Body (General)
    _UP_REQ_BACK_UP_MSG_ID,
    _UP_REQ_BACK_UP_PORT_NUM,
    _UP_REQ_BACK_UP_GUID_1,
    _UP_REQ_BACK_UP_GUID_2,
    _UP_REQ_BACK_UP_GUID_3,
    _UP_REQ_BACK_UP_GUID_4,
    _UP_REQ_BACK_UP_GUID_5,
    _UP_REQ_BACK_UP_GUID_6,
    _UP_REQ_BACK_UP_GUID_7,
    _UP_REQ_BACK_UP_GUID_8,
    _UP_REQ_BACK_UP_GUID_9,
    _UP_REQ_BACK_UP_GUID_10,
    _UP_REQ_BACK_UP_GUID_11,
    _UP_REQ_BACK_UP_GUID_12,
    _UP_REQ_BACK_UP_GUID_13,
    _UP_REQ_BACK_UP_GUID_14,
    _UP_REQ_BACK_UP_GUID_15,
    _UP_REQ_BACK_UP_GUID_16,

    // MSG Body (Connection Status Notify)
    _UP_REQ_BACK_UP_LEGACY_STATUS,
    _UP_REQ_BACK_UP_DP_STATUS,
    _UP_REQ_BACK_UP_MSG_CAP_STATUS,
    _UP_REQ_BACK_UP_INPUT_PORT,
    _UP_REQ_BACK_UP_PEER_DEV_TYPE,
/*
    // MSG Body (Resource Status Notify)
    _UP_REQ_BACK_UP_AVAILABLE_PBN_H,
    _UP_REQ_BACK_UP_AVAILABLE_PBN_L,
*/
    _UP_REQ_BACK_UP_DPCD_200_STATUS,
} EnumUpRequestBackUp;

//--------------------------------------------------
// Enumerations of Connect Status List
//--------------------------------------------------
typedef enum
{
    _CONNECT_STATUS_UNPLUG = 0x00,
    _CONNECT_STATUS_PLUG,
    _CONNECT_STATUS_NONE,
} EnumDpMstTxConnectStatus;

//--------------------------------------------------
// Enumerations of DP Tx CSN Queue
//--------------------------------------------------
typedef enum
{
    _TX_UP_REQ_QUEUE_SELF_GEN,
    _TX_UP_REQ_QUEUE_BYPASS,
    _TX_UP_REQ_QUEUE_NONE,
} EnumDpMstTxUpReqQueue;

//--------------------------------------------------
// Enumerations of DP Tx CSN Queue Entry
//--------------------------------------------------
typedef enum
{
    _CSN_QUEUE_ENTRY_0,
    _CSN_QUEUE_ENTRY_1,
    _CSN_QUEUE_ENTRY_NUM,
} EnumDpMstTxCsnQueueEntry;

//--------------------------------------------------
// Enumerations of DP Tx SEN Queue Entry
//--------------------------------------------------
typedef enum
{
    _SEN_QUEUE_ENTRY_0,
    _SEN_QUEUE_ENTRY_1,
    _SEN_QUEUE_ENTRY_NUM,
} EnumDpMstTxSenQueueEntry;

//--------------------------------------------------
// Struct for Message Function Action Info
//--------------------------------------------------
typedef struct
{
    BYTE b1DownRequestAnal : 1;
    BYTE b1DownReplyDirect : 1;
    BYTE b1DownReplyAnal : 1;
    BYTE b1UpRequestAnal : 1;
    BYTE b1UpReplyBypass : 1;
    BYTE b1UpReplyDirect : 1;
    BYTE b1DownRequestReady : 1;
    BYTE b1DownReplyReady : 1;
    BYTE b1DownReplyReadDisable : 1;
    BYTE b1UpRequestReady : 1;
    BYTE b1UpReplyReady : 1;
}StructTxMsgFunctionInfo;

//--------------------------------------------------
// Struct for Message Info
//--------------------------------------------------
typedef struct
{
    EnumDpMstTxUpReqQueue enumUpReqIntiatedQueue;
    BYTE b1DownRequestMsgDone : 1;
    BYTE b1UpReplyMsgDone : 1;
    EnumTxReadBufferStatus b2RdBufferStatus : 2;
    BYTE b1DownRequestBroadcastProc : 1;
    BYTE b1IllegalDownRequestMSG : 1;
    BYTE b1IllegalUpRequestMSG : 1;
    BYTE ucGenUpRequestMsg;
    BYTE b1DownReplyBroadcastDirectlyReplyDone : 1;
    BYTE b1WaitClearPayloadIdTableDownReplyMsg : 1;
    BYTE b1WaitTopologyRebuildProcess : 1;
    BYTE b1MsgDuringHpdLowDebounce : 1;
    BYTE b1PlugCsnDebouncing : 1;
    BYTE b1EnumMsgReplyTimeOut : 1;
} StructTxMsgInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//--------------------------------------------------
// Struct for Event Processor Info
//--------------------------------------------------
typedef struct
{
    EnumTxEventType b4MsgDownReqEventType : 4;
    EnumTxEventType b4MsgDownRepEventType : 4;
    BYTE b1MsgDownRepAnalFinish : 1;
    BYTE b1MsgDownReqAnalFinish : 1;
}StructTxEventProcInfo;

//--------------------------------------------------
// Struct for Tx Up Request MSG
//--------------------------------------------------
typedef struct
{
    BYTE ucUpReqMsgLength;
    BYTE b4UpReqMsgLCR : 4;
    BYTE b4UpReqMsgLCT : 4;
    BYTE b1UpReqMsgBroadcast : 1;
    BYTE b1UpReqMsgPath : 1;
    BYTE b1UpReqMsgMsn : 1;
    BYTE b1UpReqMsgReadFinish : 1;
} StructTxUpRequestMsgHeaderInfo;

//--------------------------------------------------
// Struct for Tx Header Backup
//--------------------------------------------------
typedef struct
{
    BYTE b4MsgLct : 4;
    BYTE b4MsgLcr : 4;
    BYTE pucMsgRad[14];
    BYTE b1MsgBroadcast : 1;
    BYTE b1MsgPath : 1;
    BYTE b1MsgMsn : 1;
    BYTE ucWritePtr;
}StructTxDownReplyMsgInterleaveHeaderInfo;

//--------------------------------------------------
// Struct for Tx Header Backup
//--------------------------------------------------
typedef struct
{
    BYTE b1SidebandMsgInterLeaveReply : 1;
    BYTE b1DownReplyBuf0CrcFailure : 1;
    BYTE b1DownReplyBuf1CrcFailure : 1;
    BYTE b1DownReplyBuf0Finish : 1;
    BYTE b1DownReplyBuf1Finish : 1;
    BYTE ucDownReplyStartCount;
    BYTE ucDownReplyEndCount;
    BYTE ucDownReplyBuf0DataLength;
    BYTE ucDownReplyBuf1DataLength;
}StructTxDownReplyMsgInterleaveInfo;

//--------------------------------------------------
// Struct for Tx CSN Info
//--------------------------------------------------
typedef struct
{
    StructTxUpRequestMsgHeaderInfo stCsnHeader;
    StructReqConnectionStatusNotify stCsnBody;
} StructDpMstTxCsnInfo;

//--------------------------------------------------
// Struct for Tx SEN Info
//--------------------------------------------------
typedef struct
{
    StructTxUpRequestMsgHeaderInfo stSenHeader;
    StructReqSinkEventNotify stSenBody;
} StructDpMstTxSenInfo;

//--------------------------------------------------
// Define CSN Info Structure
//--------------------------------------------------
typedef struct
{
    EnumDpMstTxConnectStatus enumTxMstPxPortConnectStatus;
    EnumInputPort enumTargetInputPort;
} StructTxMstCsnInfo;

//--------------------------------------------------
// Define Px Port CSN Queue Structure
//--------------------------------------------------
typedef struct
{
    StructTxMstCsnInfo pstTxMstCsnEvent[_CSN_QUEUE_ENTRY_NUM];
} StructTxMstPxPortCsnQueue;

//--------------------------------------------------
// Define Mst Tx 128b132b To 8b10b Msa Convert
//--------------------------------------------------
typedef struct
{
    DWORD ul128b132bMsaVfreq;
    DWORD ul128b132bMsaAfreq;
    BYTE b2ColorDepth : 2;
    BYTE b3ColorSpace : 3;
} StructDpMstTx128b132bTo8b10bMsaInfo;

//--------------------------------------------------
// Union for Tx EDID Read Position
//--------------------------------------------------
typedef union
{
    BYTE pucData[2];
} UnionMstTxEdidReadPos;

extern volatile StructTxMsgFunctionInfo g_stDpMstTxMsgFunction;
extern volatile StructTxMsgInfo g_stDpMstTxMsgInfo;
extern volatile StructTxEventProcInfo g_stDpMstTxEventProcInfo;
extern BYTE g_ucDpMstTxDownReqBodyLength;
extern BYTE g_ucDpMstTxUpRepBodyLength;
extern volatile BYTE g_ucDpMstTxReceivedMsgCount;
extern BYTE g_pucDpMstTxUpRequestBackUp[30];
extern StructTxUpRequestMsgHeaderInfo g_stDpMstTxUpReqMsgHeaderInfo;
extern StructDpMstTxCsnInfo g_pstDpMstTxBypassCsnQueue[];
extern StructDpMstTxSenInfo g_pstDpMstTxBypassSenQueue[];
extern EnumDpMSTSinkEventID g_penumDpMstTxSinkEventID[];
extern bit g_bDpMstTxInterceptDdcciMsgAdjustLCT;

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE g_ucDpMstTx128b132bTo8b10bMsaConvertFlag;
extern StructDpMstTx128b132bTo8b10bMsaInfo g_pstDpMstTx128b132bTo8b10bMsaInfo[_HW_DP_MST_DAISY_ST_NUM_MAX];
extern DWORD g_ulDpMstTxMsgPbnConversion;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//extern void ScalerDpMacTxMonitorDownstreamBW(void);
extern void ScalerDpMstTxMsgHandler(void);
extern void ScalerDpMstTxDownRequestSelfGen(EnumMessageReuqestID enumMsgID);
extern void ScalerDpMstTxLinkClockEn(bit bEn);
extern void ScalerDpMstTxToSstFCMuxSetting(void);
extern EnumDpMstPort ScalerDpMstTxPxPortNumMapping(EnumOutputPort enumOutputPort);
extern EnumOutputPort ScalerDpMstTxPortNumPxMapping(EnumDpMstPort enumDpMstPort);

// DPTX MSG
extern void ScalerDpMstTxMsgCountResetEvent(void);
extern EnumDpMstTxConnectStatus ScalerDpMstTxGetOutputPortStatusReported(void);
extern void ScalerDpMstTxSetOutputPortStatusReported(EnumDpMstTxConnectStatus enumPlugStatus);
extern void ScalerDpMstTxCsnEventReset(void);
extern void ScalerDpMstTxSetCsnEvent(EnumInputPort enumTargetInputPort, EnumDpMstTxConnectStatus enumCsnEvent);
extern EnumDpMstTxConnectStatus ScalerDpMstTxCsnEventGetStatus(EnumDpMstTxUpReqQueue enumCsnQueue);
extern void ScalerDpMstTxCsnEventDelete(EnumDpMstTxUpReqQueue enumCsnQueue);
extern bit ScalerDpMstTxCsnTransmitDoneCheck(void);
extern void ScalerDpMstTxSenEventDelete(EnumDpMstTxUpReqQueue enumSenQueue);
extern void ScalerDpMstTxSenEventReset(void);
extern bit ScalerDpMstTxDownRequestProc(void);
extern bit ScalerDpMstTxDownReplyProc(void);
extern bit ScalerDpMstTxUpRequestProc(void);
extern bit ScalerDpMstTxUpReplyProc(void);

// DPTX MST STREAM
extern WORD ScalerDpMstTxGetAvailablePBN(void);
extern BYTE ScalerDpMstTxGetAvailableTimeslot(void);
extern WORD ScalerDpMstTxGetFullPBN(void);
extern bit ScalerDpMstTxGetStreamAllocate(void);
extern void ScalerDpMstTxMst2SstInitialSetting(void);
extern void ScalerDpMstTxSetMst2SstLaneNum(void);
extern void ScalerDpMstTxSetDaisyInputPortMux(EnumInputPort enumInputPort);
extern void ScalerDpMstTxResetDaisySourceMuxReg_EXINT0(void);
extern void ScalerDpMstTxResetDaisySourceMuxBackup_EXINT0(void);
extern void ScalerDpMstTxResetDaisyStreamPositionReg_EXINT0(void);

extern bit ScalerDpMstTxGetIncomingHPDStatus(void);
extern bit ScalerDpMstTxGetHdcpEncryptEnable(void);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern WORD ScalerDpMstTxGet128b132bTo8b10bPageAddress(EnumDpStreamNum enumDpStreamNum, WORD usSt1Address);
extern void ScalerDpMstTxReset128b132bTo8b10bMsaConvert(void);
extern void ScalerDpMstTxSet128b132bTo8b10bMsaConvert(EnumDpStreamNum enumDpStreamNum, bit bEn);
extern void ScalerDpMstTx128b132bTo8b10bColorInfoUpdate(EnumDpStreamNum enumDpStreamNum, StructDpMstTx128b132bTo8b10bMsaInfo *pstDpMstTxMsaInfoUpdate);
extern void ScalerDpMstTxSet128b132bTo8b10bMsaValue(EnumDpStreamNum enumDpStreamNum, DWORD ulVideoFreq, DWORD ulAudioFreq);
extern void ScalerDpMstTxSet128b132bTo8b10bMiscValue(EnumDpStreamNum enumDpStreamNum, BYTE ucColorDepthValue, BYTE ucColorSpaceValue);
extern void ScalerDpMstTx128b132bTo8b10bMsaStableCheck(EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMstTx128b132bTo8b10bMiscStableCheck(EnumDpStreamNum enumDpStreamNum);
extern bit ScalerDpMstTx128b132bTo8b10bHblankNoSfModeSupport(void);
#endif

#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_FEC_SUPPORT == _ON))
extern WORD ScalerDpMstTxJudgePbnConversion(WORD usInputPbn, EnumMessageReuqestID enumMsgRequestId);
#endif


#endif // End of #if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

#if((_DP_TX_SUPPORT == _ON) && ((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)))
extern void ScalerDpMstTxReset(void);
#endif

