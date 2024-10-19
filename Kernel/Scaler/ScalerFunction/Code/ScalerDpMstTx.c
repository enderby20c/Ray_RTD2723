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
// ID Code      : ScalerDpMstTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPTXMST__

#include "ScalerFunctionInclude.h"
#include "DpMstTx/ScalerDpMstTx.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tDpMstTxRadBaseBitMap[13] =
{
    12, 8, 20, 16, 28, 24,
    4, 0, 12, 8, 20, 16, 28,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
volatile StructTxMsgFunctionInfo g_stDpMstTxMsgFunction;
volatile StructTxMsgInfo g_stDpMstTxMsgInfo;
volatile StructTxEventProcInfo g_stDpMstTxEventProcInfo;
BYTE g_ucDpMstTxDownReqBodyLength;
BYTE g_ucDpMstTxUpRepBodyLength;
volatile BYTE g_ucDpMstTxReceivedMsgCount;
EnumDpMstTxConnectStatus g_penumDpMstTxOutputPortStatusReported[1];
UnionMstTxEdidReadPos g_punDpMstTxPortEdidReadPosition[1];

// For SBMSG Interleave Case
StructTxDownReplyMsgInterleaveHeaderInfo g_stDpMstTxMsgBackupHeaderInfo0;
StructTxDownReplyMsgInterleaveHeaderInfo g_stDpMstTxMsgBackupHeaderInfo1;
StructTxDownReplyMsgInterleaveInfo g_stDpMstTxMsgInterleaveInfo;
StructTxUpRequestMsgHeaderInfo g_stDpMstTxUpReqMsgHeaderInfo;
BYTE g_pucDpMstTxDownReplyBuf0Data[259];
BYTE g_pucDpMstTxDownReplyBuf1Data[259];
StructDpMstTxCsnInfo g_pstDpMstTxBypassCsnQueue[_CSN_QUEUE_ENTRY_NUM];
StructDpMstTxSenInfo g_pstDpMstTxBypassSenQueue[_SEN_QUEUE_ENTRY_NUM];
EnumDpMSTSinkEventID g_penumDpMstTxSinkEventID[1];

// Output Px Port CSN Queue Array
StructTxMstPxPortCsnQueue g_pstDpMstTxCsnQueueInfo[1];

#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
bit g_bDpMstTxInterceptDdcciMsg;
bit g_bDpMstTxInterceptDdcciMsgAdjustLCR;
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
BYTE g_ucDpMstTx128b132bTo8b10bMsaConvertFlag;
StructDpMstTx128b132bTo8b10bMsaInfo g_pstDpMstTx128b132bTo8b10bMsaInfo[_HW_DP_MST_DAISY_ST_NUM_MAX];
#endif

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Tx Mst Msg Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxMsgHandler(void)
{
    ScalerDpMstTxDownRequestProc();

    ScalerDpMstTxDownReplyProc();

    ScalerDpMstTxUpRequestEventCheck();

    ScalerDpMstTxUpRequestProc();

    ScalerDpMstTxUpReplyProc();
}

//--------------------------------------------------
// Description  : DP Tx Mst Msg Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxDownRequestSelfGen(EnumMessageReuqestID enumMsgID)
{
    SET_DP_MST_RX_GEN_DOWN_REQUEST_MSG(enumMsgID);
}

//--------------------------------------------------
// Description  : DP Tx Processor for Down Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownRequestSend(void)
{
    if(GET_DP_MST_TX_DOWN_REQUEST_READY() == _TRUE)
    {
        CLR_DP_MST_TX_DOWN_REQUEST_READY();

        // Disable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

        // Reset FIFO
        SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_PTR(0x00);

        Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Disable Defer/TimeOut/Nack/Error Retry Machine
        Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

        // Move Array Data to Buffer
        for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_TX_REG_DOWNSTREAM_MSG_LENGTH(); ucIndex++)
        {
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_DATA(GET_DP_MST_RX_MSG_REQUEST_ARRAY(ucIndex));
        }

        // Make Sure Down Request has Been Propagated
        if(ScalerDpMstTxWriteMsgToDownstreamStatusCheck(_DP_DOWN_REQUEST_MSG) == _TRUE)
        {
            if(GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
            {
                SET_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
            }

            // Count DownRequest Msg
            if(GET_DP_MST_TX_RECEIVED_MSG_COUNT() < 255)
            {
                SET_DP_MST_TX_RECEIVED_MSG_COUNT(GET_DP_MST_TX_RECEIVED_MSG_COUNT() + 1);
            }

            ScalerDpMstRxReactiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT);
        }

        // Enable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

        SET_DP_MST_TX_DOWN_REQUEST_MSG_DONE();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Processor for Down Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownReplyReceive(void)
{
    BYTE ucRetry = 0;
    bit bDone = _TRUE;

    if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ) == _DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ)
    {
        SET_DP_MST_TX_DOWN_REPLY_READY();
    }

    // Down Reply Ready IRQ_HPD Received and Read Buffer is not used by Up Request
    if(GET_DP_MST_TX_DOWN_REPLY_READY() == _TRUE)
    {
        if((GET_DP_MST_TX_RD_BUFFER_STATUS() != _DP_TX_READ_BUF_UP_REQUEST_IN_USE) && (GET_DP_MST_TX_DOWN_REPLY_READ_DISABLE() == _FALSE))
        {
            CLR_DP_MST_TX_DOWN_REPLY_READY();

            ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

            if(GET_DP_MST_TX_RD_BUFFER_STATUS() == _DP_TX_READ_BUF_EMPTY)
            {
                // CLR MSG Finish Flag
                CLR_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH_FLAG();

                // CLR SBMSG Finish Flag
                CLR_DP_MST_TX_REG_UPSTREAM_SBMSG_FINISH_FLAG();

                // Buf_CLR=1 WR_PTR = 0x00
                CLR_DP_MST_TX_REG_UPSTREAM_MSG_BUF();

                ScalerDpMstTxClrDownReplyInterleaveFlag();
            }

            SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

            // Select to DownReply Address
            SET_DP_MST_TX_REG_UPSTREAM_MSG_T0_DOWN_REPLY_ADDRESS();

            // Disable Short HPD Int.
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

            // Disable AUX FW Handle Mode
            Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT5 | _BIT0), 0x00);

            for(ucRetry = 0; ucRetry < 20; ucRetry++)
            {
                // When the first time or "HW Retry Times" reaches RETRY_NUM, reactive HW to read MSG
                if((ucRetry == 0) || (Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT1) == _BIT1))
                {
                    // Clear AUX IRQ Flag
                    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                    // Disable Defer/TimeOut/Nack/Error Retry Machine
                    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // Enable Defer/TimeOut/Nack/Error Retry Machine
                    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

                    // Start RD MSG circuit
                    SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DISABLE();
                    SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_ENABLE();
                }

                if(ScalerTimerPollingFlagProc32Bit(5, PB18083_88_MSG_RD_FINISH, _BIT1, _TRUE) == _TRUE)
                {
                    // CLR SBMSG Finish Flag
                    CLR_DP_MST_TX_REG_UPSTREAM_SBMSG_FINISH_FLAG();

                    if(GET_DP_MST_TX_REG_UPSTREAM_MSG_BODY_LENGTH() != 0x00)
                    {
                        ScalerDpMstTxDownReplySideBandMsgProc();

                        SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_DOWN_REPLY_IN_USE);
                    }

                    break;
                }
            }

            // Disable Tx Read MSG
            SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DISABLE();

            // Disable Defer/TimeOut/Nack/Error Retry Machine
            Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Enable AUX FW Handle Mode
            Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT5 | _BIT0), _BIT5);

            // CLR DownStream DPCD DownReply Ready Bit
            BYTE ucData = _BIT4;
            ScalerDpAuxTxNativeWrite(0x00, 0x20, 0x03, 1, &ucData);

            // CLR DownReply Ready Flag
            CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ);

            // Enable Short HPD Int.
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);
        }
        else
        {
            bDone = _FALSE;
        }
    }

    if(GET_DP_MST_TX_RD_BUFFER_STATUS() == _DP_TX_READ_BUF_DOWN_REPLY_IN_USE)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

        if((GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE) || (GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH() == _TRUE))
        {
            if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) && (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
            {
                CLR_DP_MST_RX_REPLY_POOL_FREE();

                // Disable Reply Buffer Free
                CLR_DP_MST_RX_REPLY_BUF_FREE();

                // Move full MSG from RD Buffer to Array
                if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
                {
                    for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH(); ucIndex++)
                    {
                        SET_DP_MST_RX_MSG_REPLY_ARRAY(ucIndex, GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA(ucIndex));
                    }
                }
                else
                {
                    for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH(); ucIndex++)
                    {
                        SET_DP_MST_RX_MSG_REPLY_ARRAY(ucIndex, GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA(ucIndex));
                    }
                }

                if(GET_DP_MST_RX_MSG_REPLY_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
                {
                    CLR_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
                }

                SET_DP_MST_TX_DOWN_REPLY_ANAL();

                // Delete DownRequest Msg Count
                if(GET_DP_MST_TX_RECEIVED_MSG_COUNT() > 0)
                {
                    SET_DP_MST_TX_RECEIVED_MSG_COUNT(GET_DP_MST_TX_RECEIVED_MSG_COUNT() - 1);
                }

                if(GET_DP_MST_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE() == _TRUE)
                {
                    if((GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() == 0) || (GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH() == 0))
                    {
                        SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);
                    }
                }
                else
                {
                    SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);
                }
            }
            else
            {
                bDone = _FALSE;
            }
        }
    }

    return bDone;
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Down Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownRequestAnal(void)
{
    bit bDone = _TRUE;

    // Generate Clear ID Table to Downstream if Uptream is Disconnected
    if(GET_DP_MST_RX_GEN_DOWN_REQUEST_MSG() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
    {
        if(GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE)
        {
            ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

            // Set Gen Msg to None
            CLR_DP_MST_RX_GEN_DOWN_REQUEST_MSG();

            // Occupy Request Memory Pool
            CLR_DP_MST_RX_REQUEST_POOL_FREE();

            //=== Set Header Info.===
            // Set LCT
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LCT(1);

            // Set LCR
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LCR(6);

            // Set Broadcast Bit
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_BROADCAST(_TRUE);

            // Set Path Bit
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_PATH(_TRUE);

            // Set TX MSG Write Total Length
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LENGTH(1);

            // Set MSN Bit
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_MSN(0);

            //=== Set Body Info.===
            // Set Down Request ID
            SET_DP_MST_RX_DOWN_REQUEST_CLEAR_ID_TABLE_MSG_REQUEST_ID(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);

            // Set Dp Tx Down Request Analysis
            SET_DP_MST_TX_DOWN_REQUEST_ANAL();

            SET_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG();
        }
        else
        {
            bDone = _FALSE;
        }
    }

    if(GET_DP_MST_TX_DOWN_REQUEST_ANAL() == _TRUE)
    {
        // Tx Down Req MSG Anal
        if(ScalerDpMstTxDownRequestMsgAnal() == _TRUE)
        {
            // CLR Flag
            CLR_DP_MST_TX_DOWN_REQUEST_ANAL();
        }
        else
        {
            bDone = _FALSE;
        }
    }

    return bDone;
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Down Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownRequestAnalDone(void)
{
    // Tx Event processor finish, check result is sucessful or fail
    if(GET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH() == _TRUE)
    {
        // CLR Flag
        CLR_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

        if(GET_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE)
        {
            SET_DP_MST_TX_DOWN_REQUEST_READY();
        }
        else
        {
            BYTE ucLCR = 0;
            EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

            ScalerDpRxSetBaseInputPort(enumInputPort);

#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
            if(GET_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR() == _TRUE)
            {
                ucLCR = 0;
            }
            else
#endif
            {
                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_UNPLUG)
                {
                    ucLCR = 0;
                }
                else
                {
                    ucLCR = GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR();
                }
            }

            if((ucLCR > 0) && (GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT))
            {
                // Modify DP Tx WR MSG header based on DP Rx RD MSG header
                ScalerDpMstTxDownRequestHeaderModify();

                // Modify DP Tx WR MSG Body
                ScalerDpMstTxDownRequestBodyModfiy();

                if(GET_DP_MST_TX_DOWN_REQUEST_BROAD_MSG() == _FALSE)
                {
                    // Release Down Request Buffer
                    ScalerDpMstRxDownRequestBufferRelease(enumInputPort);
                }

                // Bypass Down Request MSG
                SET_DP_MST_TX_DOWN_REQUEST_READY();
            }
            else
            {
                if(GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS)
                {
                    if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT)
                    {
                        // Modify DP Tx WR MSG header based on DP Rx RD MSG header
                        ScalerDpMstTxDownRequestHeaderModify();

                        // Modify DP Tx WR MSG Body
                        ScalerDpMstTxDownRequestBodyModfiy();

                        // Release Down Request Buffer
                        ScalerDpMstRxDownRequestBufferRelease(enumInputPort);

                        // Bypass Down Request MSG
                        SET_DP_MST_TX_DOWN_REQUEST_READY();
                    }
                    else
                    {
                        SET_DP_MST_TX_DOWN_REPLY_DIRECTLY();
                    }
                }
                else
                {
                    SET_DP_MST_TX_DOWN_REPLY_DIRECTLY();
                }
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Down Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownRequestDone(void)
{
    if(GET_DP_MST_TX_DOWN_REQUEST_MSG_DONE() == _TRUE)
    {
        // CLR Flag
        CLR_DP_MST_TX_DOWN_REQUEST_MSG_DONE();

        if(GET_DP_MST_TX_DOWN_REQUEST_BROAD_MSG() == _TRUE)
        {
            // Clr flag
            CLR_DP_MST_TX_DOWN_REQUEST_BROAD_MSG();

            if(GET_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE)
            {
                // Clr flag
                CLR_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG();

                // Release Request Array Free
                SET_DP_MST_RX_REQUEST_POOL_FREE();
            }
            else
            {
                SET_DP_MST_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE();
            }
        }
        else
        {
            // Release Request Array Free
            SET_DP_MST_RX_REQUEST_POOL_FREE();
        }
    }

    if(GET_DP_MST_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE() == _TRUE)
    {
        if(GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE)
        {
            ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

            if(GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE)
            {
                // Occupy Reply Pool
                CLR_DP_MST_RX_REPLY_POOL_FREE();

                // Disable Reply Buffer Free
                CLR_DP_MST_RX_REPLY_BUF_FREE();

                CLR_DP_MST_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE();

                SET_DP_MST_TX_DOWN_REPLY_DIRECTLY();
            }
        }
        else
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Down Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownReplyAnal(void)
{
    if(GET_DP_MST_TX_DOWN_REPLY_ANAL() == _TRUE)
    {
        // CLR Flag
        CLR_DP_MST_TX_DOWN_REPLY_ANAL();

        ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

        // Check MSG CRC
        if(ScalerDpMstTxGetDownReplyCrcFailed() == _FALSE)
        {
            if(ScalerDpMstTxGetDownReplyBroadcastBit() == _FALSE)
            {
                // Set Down Reply Target Port
                SET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT(GET_DP_RX_MAIN_PORT());

                ScalerDpMstTxDownReplyBypass();

                // Modify Header Info.
                ScalerDpMstTxDownReplyBypassHeaderModify();

//================================================For Interleave case===================================
                if(GET_DP_MST_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE() == _TRUE)
                {
                    ScalerDpMstTxDownReplyInterleaveFinishCheck();
                }
                else
                {
                    // TX Read Enable
                    CLR_DP_MST_TX_DOWN_REPLY_READ_DISABLE();

                    CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH();
                }
//================================================For Interleave case===================================
            }
            else
            {
                SET_DP_MST_RX_REPLY_POOL_FREE();

                // Free Reply Buffer
                SET_DP_MST_RX_REPLY_BUF_FREE();

                // TX Read Enable
                CLR_DP_MST_TX_DOWN_REPLY_READ_DISABLE();
            }
        }
        else
        {
            SET_DP_MST_RX_REPLY_POOL_FREE();

            // Free Reply Buffer
            SET_DP_MST_RX_REPLY_BUF_FREE();

            // TX Read Enable
            CLR_DP_MST_TX_DOWN_REPLY_READ_DISABLE();
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Down Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownReplyAnalDone(void)
{
    if(GET_DP_MST_TX_DOWN_REPLY_DIRECTLY() == _TRUE)
    {
        EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

        // CLR Flag
        CLR_DP_MST_TX_DOWN_REPLY_DIRECTLY();

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if(GET_DP_MST_RX_REG_UPSTREAM_REPLY() == _FALSE)
        {
            // Set Down Reply Target Port
            SET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT(enumInputPort);

            // Message Reply
            ScalerDpMstTxDownReplyDirectlyMsg();

            // Release Down Request Buffer
            ScalerDpMstRxDownRequestBufferRelease(enumInputPort);

            // Free Request Array
            SET_DP_MST_RX_REQUEST_POOL_FREE();

            SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
        }
        else
        {
            // Nak Reeason: DEFER
            SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_DEFER);

            DebugMessageMst("[MST] Tx down reply proccess ERROR!!!", GET_DP_MST_RX_MSG_REQUEST_ID());
        }
    }

    if(GET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG() == _TRUE)
    {
        if(GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE)
        {
            EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

            ScalerDpRxSetBaseInputPort(enumInputPort);

            if(GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE)
            {
                // Occupy Reply Pool
                CLR_DP_MST_RX_REPLY_POOL_FREE();

                // Disable Reply Buffer Free
                CLR_DP_MST_RX_REPLY_BUF_FREE();

                // CLR Flag
                CLR_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();

                // Set Down Reply Target Port
                SET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT(enumInputPort);

                // Error Reply
                ScalerDpMstRxIllegalMsgReply();

                // Release Down Request Buffer
                ScalerDpMstRxDownRequestBufferRelease(enumInputPort);

                // Free Request Array
                SET_DP_MST_RX_REQUEST_POOL_FREE();

                if(GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT() == GET_DP_RX_MAIN_PORT())
                {
                    // Trigger Tx Cap Change When Initial State
                    if(GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_OFF)
                    {
                        SET_DP_MST_TX_MSG_DURING_HPD_LOW_DEBOUNCE();

                        DebugMessageDpTx("Tx MSG during HPD debounce!!", 0);
                    }
                }

                SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
            return _FALSE;
        }
    }

    if(GET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH() == _TRUE)
    {
        // CLR Flag
        CLR_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();

        SET_DP_MST_RX_DOWN_REPLY_BYPASS();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Processor for Up Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxUpRequestReceive(void)
{
    BYTE ucRetry = 0;
    bit bDone = _TRUE;

    if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ) == _DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ)
    {
        SET_DP_MST_TX_UP_REQUEST_READY();
    }

    // Up Request Ready IRQ_HPD Received and Read Buffer is not used by Down Reply
    if(GET_DP_MST_TX_UP_REQUEST_READY() == _TRUE)
    {
        if((GET_DP_MST_TX_RD_BUFFER_STATUS() != _DP_TX_READ_BUF_DOWN_REPLY_IN_USE) && (GET_DP_MST_TX_DOWN_REPLY_READ_DISABLE() == _FALSE))
        {
            CLR_DP_MST_TX_UP_REQUEST_READY();

            if(GET_DP_MST_TX_RD_BUFFER_STATUS() == _DP_TX_READ_BUF_EMPTY)
            {
                // CLR MSG Finish Flag
                CLR_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH_FLAG();

                // CLR SBMSG Finish Flag
                CLR_DP_MST_TX_REG_UPSTREAM_SBMSG_FINISH_FLAG();

                // Buf_CLR=1 WR_PTR=0x00
                CLR_DP_MST_TX_REG_UPSTREAM_MSG_BUF();

                SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_UP_REQUEST_IN_USE);
            }

            // Select to Up Request Address
            SET_DP_MST_TX_REG_UPSTREAM_MSG_TO_UP_REQUEST_ADDRESS();

            // Disable Short HPD Int.
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

            // Disable AUX FW Handle Mode
            Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT5 | _BIT0), 0x00);

            for(ucRetry = 0; ucRetry < 20; ucRetry++)
            {
                // When the first time or "HW Retry Times" reaches RETRY_NUM, reactive HW to read MSG
                if((ucRetry == 0) || (Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT1) == _BIT1))
                {
                    // Clear AUX IRQ Flag
                    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                    // Disable Defer/TimeOut/Nack/Error Retry Machine
                    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // Enable Defer/TimeOut/Nack/Error Retry Machine
                    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

                    // Start RD MSG circuit
                    SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DISABLE();
                    SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_ENABLE();
                }

                if(ScalerTimerPollingFlagProc32Bit(5, PB18083_88_MSG_RD_FINISH, _BIT1, _TRUE) == _TRUE)
                {
                    // CLR SBMSG Finish Flag
                    CLR_DP_MST_TX_REG_UPSTREAM_SBMSG_FINISH_FLAG();

                    // Disable Tx Read MSG
                    SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DISABLE();

                    // CLR DownStream DPCD Up Request Ready Bit
                    BYTE ucData = _BIT5;
                    ScalerDpAuxTxNativeWrite(0x00, 0x20, 0x03, 1, &ucData);

                    if(GET_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH() == _TRUE)
                    {
                        SET_DP_MST_TX_UP_REQUEST_MSG_LENGTH(GET_DP_MST_TX_REG_UPSTREAM_MSG_LENGTH());

                        SET_DP_MST_TX_UP_REQUEST_MSG_LCR(GET_DP_MST_TX_REG_UPSTREAM_MSG_LCR());

                        SET_DP_MST_TX_UP_REQUEST_MSG_LCT(GET_DP_MST_TX_REG_UPSTREAM_MSG_LCT());

                        SET_DP_MST_TX_UP_REQUEST_MSG_BROADCAST(GET_DP_MST_TX_REG_UPSTREAM_MSG_BROADCAST());

                        SET_DP_MST_TX_UP_REQUEST_MSG_PATH(GET_DP_MST_TX_REG_UPSTREAM_MSG_PATH());

                        SET_DP_MST_TX_UP_REQUEST_MSG_MSN(GET_DP_MST_TX_REG_UPSTREAM_MSG_MSN());

                        SET_DP_MST_TX_UP_REQUEST_MSG_READ_FINISH(GET_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH());

                        SET_DP_MST_TX_DOWN_REPLY_READ_DISABLE();
                    }

                    break;
                }
            }

            if(ucRetry == 20)
            {
                // Disable Tx Read MSG
                SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DISABLE();

                SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);
            }

            // Disable Defer/TimeOut/Nack/Error Retry Machine
            Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Enable AUX FW Handle Mode
            Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT5 | _BIT0), _BIT5);

            // CLR DownReply Ready Flag
            CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ);

            // Enable Short HPD Int.
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);
        }
        else
        {
            bDone = _FALSE;
        }
    }

    if(GET_DP_MST_TX_RD_BUFFER_STATUS() == _DP_TX_READ_BUF_UP_REQUEST_IN_USE)
    {
        if(GET_DP_MST_TX_UP_REQUEST_MSG_READ_FINISH() == _TRUE)
        {
            ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

            if((GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE) && (GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE))
            {
                // Occupy Request Pool
                CLR_DP_MST_RX_REQUEST_POOL_FREE();

                // Disable Reply Buffer Free
                CLR_DP_MST_RX_REPLY_BUF_FREE();

                // CLR Flag
                CLR_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH_FLAG();

                // BUF_READ_PTR = 0
                SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_PTR(0x00);

                // Get Up Request MSG and Using Requeset Pool to Analysis
                for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_TX_UP_REQUEST_MSG_LENGTH(); ucIndex++)
                {
                    SET_DP_MST_RX_MSG_REQUEST_ARRAY(ucIndex, GET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DATA());
                }

                SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

                //========== Set Next Action ==============

                // Dp Tx Self Analize Received Up_Request MSG
                SET_DP_MST_TX_UP_REQUEST_ANAL();
            }
            else
            {
                bDone = _FALSE;
            }
        }
    }

    return bDone;
}

//--------------------------------------------------
// Description  : DP Tx Processor for Up Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxUpReplySend(void)
{
    if(GET_DP_MST_TX_UP_REPLY_READY() == _TRUE)
    {
        CLR_DP_MST_TX_UP_REPLY_READY();

        // Disable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

        // Move MSG body from Array to DP Tx WR Buffer
        SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_PTR(0x00);

        // Move Array Data to Buffer
        for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_TX_REG_DOWNSTREAM_MSG_LENGTH(); ucIndex++)
        {
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_DATA(GET_DP_MST_RX_MSG_REPLY_ARRAY(ucIndex));
        }

        ScalerDpMstTxWriteMsgToDownstreamStatusCheck(_DP_UP_REPLY_MSG);

        // Enable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

        SET_DP_MST_TX_UP_REPLY_MSG_DONE();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Up Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxUpRequestAnal(void)
{
    BYTE ucDpMstDownstreamSinkCnt = 0;

    // Receive Up Request From Downstream
    if(GET_DP_MST_TX_UP_REQUEST_ANAL() == _TRUE)
    {
        // CLR Flag
        CLR_DP_MST_TX_UP_REQUEST_ANAL();

        ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

        if(GET_DP_MST_RX_HOT_PLUG_STATUS() == _TRUE)
        {
            // CRC OK
            if(GET_DP_MST_TX_REG_UPSTREM_MSG_CRC_STATUS() == _TRUE)
            {
                switch(GET_DP_MST_RX_MSG_REQUEST_ID())
                {
                    case _DP_MSG_CONNECTION_STATUS_NOTIFY:

                        // In MST mode, Bit2 : STREAM_STATUS_CHANGED is set to 1 if DPTX connect a new downstream device.
                        // Indicates the source must re-check the Stream Status with the QUERY_STREAM_ENCRYPTION_STATUS message.
                        SET_DP_MST_RX_REG_W1C_DPCD_INFO(0x00, 0x20, 0x05, (GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x20, 0x05) | _BIT2));

                        if((GET_DP_MST_TX_UP_REQUEST_MSG_LCR() > 0) && (GET_DP_MST_TX_UP_REQUEST_MSG_LCR() >= GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCR(_CSN_QUEUE_ENTRY_0)))
                        {
                            // Clear queue if CSN > backup CSN or unplug case
                            if((GET_DP_MST_TX_UP_REQUEST_MSG_LCR() > GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCR(_CSN_QUEUE_ENTRY_0)) ||
                               ((GET_DP_MST_TX_UP_REQUEST_MSG_LCR() == GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCR(_CSN_QUEUE_ENTRY_0)) &&
                                (GET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PLUG_STATUS() == _DP_UNPLUG)))
                            {
                                ScalerDpMstTxCsnEventClearQueue(_TX_UP_REQ_QUEUE_BYPASS);
                            }

                            // Read Downstream Device Sink Count
                            ScalerDpAuxTxNativeRead(0x00, 0x02, 0x00, 1, &ucDpMstDownstreamSinkCnt);
                            SET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT(ucDpMstDownstreamSinkCnt & 0xBF);

                            // Backup CSN to bypass queue
                            if(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCR(_CSN_QUEUE_ENTRY_0) == 0)
                            {
                                SET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_HEADER(_CSN_QUEUE_ENTRY_0, GET_DP_MST_TX_UP_REQUEST_MSG_HEADER());
                                SET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_BODY(_CSN_QUEUE_ENTRY_0, GET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_BODY());
                            }
                            else
                            {
                                SET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_HEADER(_CSN_QUEUE_ENTRY_1, GET_DP_MST_TX_UP_REQUEST_MSG_HEADER());
                                SET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_BODY(_CSN_QUEUE_ENTRY_1, GET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_BODY());
                            }
                        }

                        // Reply ACK to Downstream
                        SET_DP_MST_TX_UP_REPLY_DIRECTLY();

                        // Free Reply Buffer
                        SET_DP_MST_RX_REPLY_BUF_FREE();

                        break;

                    case _DP_MSG_SINK_EVENT_NOTIFY:

                        if(GET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_ID() != 0)
                        {
                            EnumDpMstTxSenQueueEntry enumSenQueueEntry = _SEN_QUEUE_ENTRY_0;

                            for(enumSenQueueEntry = _SEN_QUEUE_ENTRY_0; enumSenQueueEntry < _SEN_QUEUE_ENTRY_NUM; enumSenQueueEntry ++)
                            {
                                if(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_EVENT_ID(enumSenQueueEntry) == 0)
                                {
                                    SET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_HEADER(enumSenQueueEntry, GET_DP_MST_TX_UP_REQUEST_MSG_HEADER());
                                    SET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_BODY(enumSenQueueEntry, GET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_BODY());

                                    break;
                                }
                            }
                        }

                        // Reply ACK to Downstream
                        SET_DP_MST_TX_UP_REPLY_DIRECTLY();

                        // Free Reply Buffer
                        SET_DP_MST_RX_REPLY_BUF_FREE();

                        break;

                    default:

                        // ID Failure, Bad Param
                        SET_DP_MST_TX_ILLEGAL_UP_REQUEST_MSG();
                        SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);

                        // Free Reply Buffer
                        SET_DP_MST_RX_REPLY_BUF_FREE();

                        break;
                }
            }
            else
            {
                // CRC Failure
                SET_DP_MST_TX_ILLEGAL_UP_REQUEST_MSG();
                SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_CRC_FAILURE);

                // Free Reply Buffer
                SET_DP_MST_RX_REPLY_BUF_FREE();
            }
        }
        else
        {
            // Free Request Pool
            SET_DP_MST_RX_REQUEST_POOL_FREE();

            // Free Reply Buffer
            SET_DP_MST_RX_REPLY_BUF_FREE();
        }

        // TX Read Enable
        CLR_DP_MST_TX_DOWN_REPLY_READ_DISABLE();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Up Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxUpReplyAnal(void)
{
    if(GET_DP_MST_TX_UP_REPLY_BYPASS() == _TRUE)
    {
        // CLR Flag
        CLR_DP_MST_TX_UP_REPLY_BYPASS();

        //========== Set Next Action ==============

        // Dp Tx Bypass Rx Up_Reply MSG to Down Stream
        SET_DP_MST_TX_UP_REPLY_READY();
    }

    if(GET_DP_MST_TX_UP_REPLY_DIRECTLY() == _TRUE)
    {
        if(GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE)
        {
            ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

            // CLR Flag
            CLR_DP_MST_TX_UP_REPLY_DIRECTLY();

            // Occupy Reply Pool
            CLR_DP_MST_RX_REPLY_POOL_FREE();

            //========== Body Info ==============

            SET_DP_MST_RX_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            SET_DP_MST_RX_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REQUEST_ID(GET_DP_MST_RX_MSG_REQUEST_ID());

            //========== Header Info ==============
            // Set LCT
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LCT(GET_DP_MST_TX_UP_REQUEST_MSG_LCT());

            // Set LCR
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LCR(GET_DP_MST_TX_UP_REQUEST_MSG_LCT() - 1);

            // Set Broadcast Bit
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_BROADCAST(GET_DP_MST_TX_UP_REQUEST_MSG_BROADCAST());

            // Set Path Bit
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_PATH(GET_DP_MST_TX_UP_REQUEST_MSG_PATH());

            // Set TX MSG Write Total Length
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LENGTH(1);

            // Set MSN Bit
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_MSN(GET_DP_MST_TX_UP_REQUEST_MSG_MSN());

            //========== Release FW Memory ==============

            // Free Request Array
            SET_DP_MST_RX_REQUEST_POOL_FREE();

            //========== Set Next Action ==============

            // Dp Rx Directly Reply Up_Reply (Ack) MSG to Down Stream
            SET_DP_MST_TX_UP_REPLY_READY();
        }
        else
        {
            return _FALSE;
        }
    }

    if(GET_DP_MST_TX_ILLEGAL_UP_REQUEST_MSG() == _TRUE)
    {
        if(GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE)
        {
            ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

            // CLR Flag
            CLR_DP_MST_TX_ILLEGAL_UP_REQUEST_MSG();

            // Occupy Reply Pool
            CLR_DP_MST_RX_REPLY_POOL_FREE();

            // Set Reply Data
            ScalerDpMstTxIllegalMsgReply();

            //========== Release FW Memory ==============

            // Free Request Pool
            SET_DP_MST_RX_REQUEST_POOL_FREE();

            //========== Set Next Action ==============

            // Dp Tx Reply Illegal Up_Reply MSG to Down Stream
            SET_DP_MST_TX_UP_REPLY_READY();
        }
        else
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Up Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxUpReplyDone(void)
{
    if(GET_DP_MST_TX_UP_REPLY_MSG_DONE() == _TRUE)
    {
        CLR_DP_MST_TX_UP_REPLY_MSG_DONE();

        SET_DP_MST_RX_REPLY_POOL_FREE();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx Processor for Event
// Input Value  : ucEventType --> Event Type for Process
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownRequestEventProc(void)
{
    BYTE ucTemp = 0;

    if(GET_DP_MST_TX_DOWN_REQUEST_EVENT() != _DP_TX_NONE_EVENT)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());

        switch(GET_DP_MST_TX_DOWN_REQUEST_EVENT())
        {
            case _DP_TX_SYNC_PAYLOAD_TABLE:

                if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
                {
                    if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_MST)
                    {
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if(GET_DP_TX_STREAM_SOURCE_CHANGE() == _FALSE)
                        {
                            if(ScalerDpMacTxLinkStatusCheck() == _FAIL)
                            {
                                SET_DP_TX_FORCE_LINK_TRAINING();

                                return _FALSE;
                            }

                            WORD usPbn = GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN();

                            EnumDpStreamNum enumDpStreamNum = ScalerDpMstRxSearchMatchStream(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(), GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

                            if(enumDpStreamNum != _DP_ST_NONE)
                            {
                                WORD usPbnMax = ScalerDpMacDphyRxGetPBN(ScalerDpAuxRxGetLinkRate(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT()), ScalerDpAuxRxGetLaneCount(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT()), GET_DP_MAC_DPHY_RX_ST_TIMESLOT_LENGTH(enumDpStreamNum));

                                // Check Whether PBN in Msg is Out of Range
                                if((usPbnMax != 0) && (usPbn > usPbnMax))
                                {
                                    usPbn = usPbnMax;
                                }
                            }

#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_FEC_SUPPORT == _ON))
                            WORD usPbnModify = ScalerDpMstTxJudgePbnConversion(usPbn, _DP_MSG_ALLOCATE_PAYLOAD);

                            if(ScalerDpMacTxSyncPayloadIDTable(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(), usPbnModify) == _TRUE)
                            {
                                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                            }
#else
                            if(ScalerDpMacTxSyncPayloadIDTable(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(), usPbn) == _TRUE)
                            {
                                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                            }
#endif
                            else
                            {
                                // Table Sync Fail
                                // Linsp => Set Finish to Prevent Dead Lock
                                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                            }
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    if(ScalerDpMacTxSyncPayloadIDTable(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(), GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN()) == _TRUE)
                    {
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        // Table Sync Fail
                        // Linsp => Set Finish to Prevent Dead Lock
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                }

                break;

            case _DP_TX_CLEAR_ID_TABLE:

                if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT)
                {
                    // Clear All Daisy Stream Time Slot
                    ScalerDpMacTxResetDaisyStreamPositionReg();

                    ScalerDpMacTxSyncDownStreamTableSetting(0x00, 0x00, 0x3F);
                }

                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

                break;

            case _DP_TX_DPCD_READ:

                if(ScalerDpAuxTxNativeRead(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H(),
                                           GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M(),
                                           GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L(), GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ(), &SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(0)) == _TRUE)
                {
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    // Failed to Readed

                    // Linsp => Set Finish to Prevent Dead Lock
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }

                break;

            case _DP_TX_DPCD_WRITE:

                if(ScalerDpAuxTxNativeWrite(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_H(),
                                            GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M(),
                                            GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_L(),
                                            GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_NUM_OF_WRITE(), &(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_DATA(0))) == _TRUE)
                {
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
                    // Check MST2SST DFP Sink DSC Enable
                    if((GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_NO_SUPPORT) &&
                       (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H() == 0x00) &&
                       (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M() == 0x01) &&
                       (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L() == 0x60))
                    {
                        if((GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_DATA(0) & _BIT0) == _BIT0)
                        {
                            SET_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE();
                        }
                        else
                        {
                            CLR_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE();
                        }
                    }
#endif

                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    // Failed to Write

                    // Linsp => Set Finish to Prevent Dead Lock
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }

                break;

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)

            case _DP_TX_VIRTUAL_DPCD_READ:

                for(ucTemp = 0; ucTemp < GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ(); ucTemp++)
                {
                    SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(ucTemp) = ScalerDpMstRxGetVirtualDpcdInfo(GET_DP_RX_MAIN_PORT(),
                                                                                                                 GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(),
                                                                                                                 GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H(),
                                                                                                                 GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M(),
                                                                                                                 (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L() + ucTemp));
                }

                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

                break;

            case _DP_TX_VIRTUAL_DPCD_WRITE:

                for(ucTemp = 0; ucTemp < GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_NUM_OF_WRITE(); ucTemp++)
                {
                    ScalerDpMstRxSetVirtualDpcdInfoBySrc(GET_DP_RX_MAIN_PORT(),
                                                         GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(),
                                                         GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_H(),
                                                         GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M(),
                                                         (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_L() + ucTemp),
                                                         GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_DATA(ucTemp));
                }

                if((GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_H() == 0x00) &&
                   (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M() == 0x01) &&
                   (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_L() == 0x60))
                {
                    ScalerDpMstRxDscSupportSwitch(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());
                }

                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

                break;
#endif

            case _DP_TX_I2C_READ:

                if(ScalerDpMstTxI2CRead() == _TRUE)
                {
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _I2C_NAK Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REMOTE_I2C_READ_FAIL();
                    SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_REASON(_I2C_NAK);

                    SET_DP_MST_RX_REPLY_POOL_FREE();
                    SET_DP_MST_RX_REPLY_BUF_FREE();
                }

                break;

            case _DP_TX_I2C_WRITE:

                if(ScalerDpMstTxI2CWrite(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_WRITE_DEVICE_ID(),
                                         GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE(),
                                         &GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(0), 0) == _TRUE)
                {
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _I2C_NAK Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_I2C_NAK);

                    SET_DP_MST_RX_REPLY_POOL_FREE();
                    SET_DP_MST_RX_REPLY_BUF_FREE();
                }

                break;

            case _DP_TX_POWER_UP:

                ucTemp = 0x01;

                if(ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, &ucTemp) == _TRUE)
                {
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

                    if(ScalerDpMacTxLinkStatusCheck() == _FAIL)
                    {
                        // Force Link Training
                        SET_DP_TX_FORCE_LINK_TRAINING();
                    }
                }
                else
                {
                    // Failed to Power up

                    // Linsp => Set Finish to Prevent Dead Lock
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }

                break;

            case _DP_TX_POWER_DOWN:

                ucTemp = 0x02;

                if(ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, &ucTemp) == _TRUE)
                {
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    // Failed to Power down

                    // Linsp => Set Finish to Prevent Dead Lock
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }

                break;

            case _DP_TX_QUERY_STREAM_ENCRYPTION_STATUS:

                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

                break;

            default:
                break;
        }

        SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_NONE_EVENT);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Tx DownReply MSG Event Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownReplyEventProc(void)
{
    BYTE pucIndex[2];
    BYTE ucTemp = 0;

    if(GET_DP_MST_TX_DOWN_REPLY_EVENT() != _DP_TX_NONE_EVENT)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

        switch(GET_DP_MST_TX_DOWN_REPLY_EVENT())
        {
            case  _DP_TX_SYNC_PAYLOAD_TABLE:

                if(ScalerDpMacTxSyncPayloadIDTable(GET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(), GET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN()) == _TRUE)
                {
                    SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
                }
                else
                {
                    // Fail to Sync Table
                    SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
                }

                break;

            case _DP_TX_POWER_DOWN:

                ucTemp = 0x02;
                if(ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, &ucTemp) == _TRUE)
                {
                    SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
                }
                else
                {
                    // Failed to Power down
                    SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
                }

                break;

            case _DP_TX_QUERY_STREAM_ENCRYPTION_STATUS:

                if(GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED() == 1)
                {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    if(ScalerDpHdcp2TxGetHdcpMode() == _ENABLE)
                    {
                        DebugMessageHDCP2("[QSE] Tx-0 : Cal Signature L'", 0);

                        // Calculate Signature L for Downstream
                        ScalerDpMstTxQueryEncryptionWriteSha256Input(GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT());

                        // Caompare Signature L with L' from Downstream
                        SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(ScalerDpMstTxQueryEncryptionCompareSha256Result());
                    }
                    else
#endif
                    {
                        // Calculate Signature L for Downstream
                        ScalerDpMstTxQueryEncryptionWriteShaInput();

                        // Caompare Signature L with L' from Downstream
                        SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(ScalerDpMstTxQueryEncryptionCompareShaResult());
                    }
                }

                // Check Stream State
                ucTemp = (GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE());

                // Set Stream State
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE(ucTemp);

                // Check Stream Encryption
                ucTemp = (GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION() &&
                          GET_DP_MST_RX_HDCP_AUTH_ENCRYPTION() &&
                          ScalerDpMstTxGetHdcpEncryptEnable());

                // Set Stream Encryption
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION(ucTemp);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                pucIndex[0] = (GET_DP_MST_RX_HDCP2_MODE() == _HDCP_22) ? GET_DP_MST_RX_HDCP2_AUTH_PROC_DONE() : GET_DP_MST_RX_HDCP_AUTH_PROC_DONE();
                pucIndex[1] = (ScalerDpHdcp2TxGetHdcpMode() == _TRUE) ? GET_DP_MST_TX_HDCP2_AUTH_PROC_PASS() : GET_DP_MST_TX_HDCP_AUTH_PROC_PASS();
#else
                pucIndex[0] = GET_DP_MST_RX_HDCP_AUTH_PROC_DONE();
                pucIndex[1] = GET_DP_MST_TX_HDCP_AUTH_PROC_PASS();
#endif

                ucTemp = (GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN() &&
                          pucIndex[0] &&
                          pucIndex[1]);

                // Set Stream Authentication
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(ucTemp);

                // Check Stream Output Sink Type
                ucTemp = (GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE());

                // Set Stream Output Sink Type
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE(ucTemp);

                // Check Stream Output CP Type
                ucTemp = GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE();

                // Set Stream Output CP Type
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(ucTemp);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if(GET_DP_MST_RX_HDCP2_MODE() == _HDCP_22)
                {
                    // Set Message Body Length = 36
                    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(36);
                }
                else
#endif
                {
                    // Set Message Body Length = 24
                    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(24);
                }

                if(GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED() == 1)
                {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    if(GET_DP_MST_RX_HDCP2_MODE() == _HDCP_22)
                    {
                        DebugMessageHDCP2("[QSE] Tx-1 : Cal Signature L'", 0);

                        // Calculate Signature L'
                        ScalerDpMstRxQueryEncryptionWriteSha256Input(GET_DP_MST_RX_HDCP2_REPEATER_SUPPORTED());

                        // Set Stream State Signature L'
                        for(ucTemp = 0; ucTemp < 32; ucTemp++)
                        {
                            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(ucTemp, GET_DP_MST_RX_REG_HDCP_SHA256_RESULT(ucTemp));
                        }
                    }
                    else
#endif
                    {
                        // Calculate Signature L' for Upstream
                        ScalerDpMstRxQueryEncryptionWriteShaInput();

                        // Set Stream State Signature L'for Upstream
                        for(ucTemp = 0; ucTemp < 20; ucTemp++)
                        {
                            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(ucTemp, GET_DP_MST_RX_REG_HDCP_SHA_RESULT(ucTemp));
                        }
                    }
                }
                else
                {
                    // Reset Stream State Signature L'
                    for(ucTemp = 0; ucTemp < 32; ucTemp++)
                    {
                        SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(ucTemp, 0x00);
                    }
                }

                SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();

                break;

            default:

                break;
        }

        SET_DP_MST_TX_DOWN_REPLY_EVENT(_DP_TX_NONE_EVENT);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx Write MSG to Downstream Status Check
// Input Value  : MSG Type
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpMstTxWriteMsgToDownstreamStatusCheck(EnumDpMessageType enumMsgType)
{
    BYTE ucRetry = 0;

    if(enumMsgType == _DP_DOWN_REQUEST_MSG)
    {
        // Select Write Address
        SET_DP_MST_TX_REG_DOWNSTREAM_TO_DOWN_REQUEST_ADDRESS();
    }
    else if(enumMsgType == _DP_UP_REPLY_MSG)
    {
        // Select Write Address
        SET_DP_MST_TX_REG_DOWNSTREAM_TO_UP_REPLY_ADDRESS();
    }

    // Disable AUX FW Handle Mode
    Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT5 | _BIT0), 0x00);

    for(ucRetry = 0; ucRetry < 20; ucRetry++)
    {
        // When the first time or "HW Retry Times" reaches RETRY_NUM, reactive HW to write MSG
        if((ucRetry == 0) || (Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT1) == _BIT1))
        {
            // Clear AUX IRQ Flag
            Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

            // Disable Defer/TimeOut/Nack/Error Retry Machine
            Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Enable Defer/TimeOut/Nack/Error Retry Machine
            Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

            // Clear Read Pointer
            CLR_DP_MST_TX_REG_DOWNSTREAM_MSG_BUF();

            // Reset FIFO
            Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Reset TX Aux FSM to Aviod HW received 2 times Defer Bug
            ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT5, _BIT5);
            ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT5, 0x00);

            // Start WR MSG circuit
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_DISABLE();
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_ENABLE();
        }

        if(ScalerTimerPollingFlagProc32Bit(5, PB18083_04_MSG_WR_FINISH, _BIT0, _TRUE) == _TRUE)
        {
            // CLR SBMSG Finish Flag
            CLR_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_FINISH_FLAG();

            // Disable Tx Write MSG
            SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_DISABLE();

            break;
        }
    }

    // Disable Tx Write MSG
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_DISABLE();

    // Disable Defer/TimeOut/Nack/Error Retry Machine
    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Reset FIFO
    Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable AUX FW Handle Mode
    Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT5 | _BIT0), _BIT5);

    return (ucRetry < 20);
}

//--------------------------------------------------
// Description  : Modify for Down Request MSG Header
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxDownRequestHeaderModify(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());

    if(((bit)GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BROADCAST() == _FALSE) && (GET_DP_MST_RX_MSG_REQUEST_ID() != _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS))
    {
        // Modify RAD
        ScalerDpMstTxModifyRAD(_DP_DOWN_REQUEST_MSG);
    }

    // Set LCT
    Scaler32SetBit(PB18083_10_MSG_WR_SET0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() << 4));

    BYTE ucTemp = (GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS) ? GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() : (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() - 1);

    // Set LCR
    Scaler32SetBit(PB18083_10_MSG_WR_SET0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucTemp);

    // Set Broadcast Bit
    Scaler32SetBit(PB18083_18_MSG_WR_SET2, ~_BIT7, GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BROADCAST());

    // Set Path Bit
    Scaler32SetBit(PB18083_18_MSG_WR_SET2, ~_BIT6, GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_PATH());

    // Set TX MSG Write Total Length
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LENGTH(GET_DP_MST_TX_DOWN_REQUEST_BODY_LENGTH());

    // Set MSN Bit
    Scaler32SetBit(PB18083_18_MSG_WR_SET2, ~_BIT12, GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_MSN());
}

//--------------------------------------------------
// Description  : Modify for Down Request MSG Body
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxDownRequestBodyModfiy(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());

#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_FEC_SUPPORT == _ON))
    if(GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_ALLOCATE_PAYLOAD)
    {
        WORD usPbnModify = ScalerDpMstTxJudgePbnConversion(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN(), _DP_MSG_ALLOCATE_PAYLOAD);

        SET_DP_MST_TX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN(usPbnModify);
    }
#endif
}

//--------------------------------------------------
// Description  : Manage for Down Request MSG Body
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxDownRequestMsgAnal(void)
{
    BYTE ucLCR = 0;

    if(GET_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE)
    {
        if(GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
        {
            if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_CLEAR_ID_TABLE);

                // Set Broadcast Flag
                SET_DP_MST_TX_DOWN_REQUEST_BROAD_MSG();
            }
            else
            {
                CLR_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG();

                // Free DownReq Pool
                SET_DP_MST_RX_REQUEST_POOL_FREE();
            }
        }
        else
        {
            CLR_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG();

            // Free DownReq Pool
            SET_DP_MST_RX_REQUEST_POOL_FREE();
        }
    }
    else
    {
        EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

        ScalerDpRxSetBaseInputPort(enumInputPort);

        ucLCR = GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        if((ucLCR > 0) && (ScalerDpMstRxGetVirtualDpEnable(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _TRUE))
        {
            ucLCR = 0;
        }
#endif

#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
        // Ddcci Read Need Intercept
        if(GET_DP_MST_TX_INTERCEPT_DDCCI_MSG_STATUS() == _TRUE)
        {
            if((GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_REMOTE_I2C_WRITE) || (GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_REMOTE_I2C_READ))
            {
                if(g_unDpMstRxRequestPool.pucData[2] == _DP_MSG_IIC_DEVICE_DDCCI)
                {
                    ucLCR = 0;
                }
            }
        }
#endif

        if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_UNPLUG)
        {
            ucLCR = 0;
        }

        // Tx Bypass Case
        if(ucLCR > 0)
        {
            if(GET_DP_MST_TX_RECEIVED_MSG_COUNT() >= 2)
            {
                return _FALSE;
            }

            if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) &&
               (ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG) &&
               (GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT))
            {
                if(GET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_MST_RX_DOWN_REQUEST_BUF0)
                {
                    SET_DP_MST_TX_DOWN_REQUEST_BODY_LENGTH(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_LENGTH());
                }
                else
                {
                    SET_DP_MST_TX_DOWN_REQUEST_BODY_LENGTH(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_LENGTH());
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);

                return _TRUE;
            }
        }

        switch(GET_DP_MST_RX_MSG_REQUEST_ID())
        {
            case _DP_MSG_GET_MESSAGE_TRANSACTION_VERSION:

                // Tx Cable Plug
                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

                            // Analysis Finish
                            SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_LINK_ADDRESS:

                // Tx Cable Plug
                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        if((GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() - GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR()) == 1)
                        {
                            SET_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
                        }

                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

                            // Analysis Finish
                            SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_ENUM_PATH_RESOURCES:

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                        if((GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_READY) || (GET_DP_MST_TX_ENUM_MSG_REPLY_TIMEOUT() == _TRUE))
#else
                        if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
#endif
                        {
                            if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                               (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                            {
                                // Occupy Reply Pool
                                CLR_DP_MST_RX_REPLY_POOL_FREE();

                                // Disable Reply Buffer Free
                                CLR_DP_MST_RX_REPLY_BUF_FREE();

                                // Analysis Finish
                                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                            }
                            else
                            {
                                return _FALSE;
                            }
                        }
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                        else if(GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_WAIT)
                        {
                            if(ScalerTimerSearchActiveTimerEvent(_SCALER_TIMER_EVENT_DP_TX_ENUM_MSG_REPLY_PBN_WAIT_TIMEOUT) == _FALSE)
                            {
                                // Clear Timeout Flag
                                CLR_DP_MST_TX_ENUM_MSG_REPLY_TIMEOUT();

                                // Active
                                ScalerDpMstRxActiveTimerEvent(_DP_MST_ENUM_REPLY_PBN_WAIT_TIME, _SCALER_TIMER_EVENT_DP_TX_ENUM_MSG_REPLY_PBN_WAIT_TIMEOUT);
                            }

                            return _FALSE;
                        }
#endif
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                        else if(GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_FAIL)
#else
                        else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_FAIL)
#endif
                        {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                            // Clear Timeout Flag
                            CLR_DP_MST_TX_ENUM_MSG_REPLY_TIMEOUT();

                            // Cancel REPLY_PBN_WAIT timer
                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_ENUM_MSG_REPLY_PBN_WAIT_TIMEOUT);
#endif

                            // Report Link Failure
                            SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_LINK_FAILURE);
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_ALLOCATE_PAYLOAD:

                if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
                {
                    // Add 1% Margin for AMD Source
                    if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > (ScalerDpMstTxGetAvailablePBN() + (GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() * _DP_MST_RX_PBN_MARGIN_PERCENTAGE_FOR_ALLOCATE_PAYLOAD / 100UL)))
                    {
                        // Reply Error MSG , Nack Reason : _NO_RESOURCES
                        SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                        SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_NO_RESOURCES);

                        break;
                    }
                }

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if((GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_READY) || (GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_WAIT))
#else
                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
#endif
                    {
                        if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_NO_SUPPORT)
                        {
                            if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                               (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                            {
                                // Occupy Reply Pool
                                CLR_DP_MST_RX_REPLY_POOL_FREE();

                                // Disable Reply Buffer Free
                                CLR_DP_MST_RX_REPLY_BUF_FREE();

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                                if((ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B) &&
                                   (ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B))
                                {
                                    // Sync Downstream Payload ID Table
                                    SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_SYNC_PAYLOAD_TABLE);
                                }
                                else
#endif
                                {
                                    // Analysis Finish
                                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                                }
                            }
                            else
                            {
                                return _FALSE;
                            }
                        }
                        else
                        {
                            if(GET_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE() == _FALSE)
                            {
                                if(ucLCR > 0)
                                {
                                    if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() == 0)
                                    {
                                        // Analysis Finish
                                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                                    }
                                    else
                                    {
                                        if((bit)GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_PATH() == _TRUE)
                                        {
                                            // Sync Downstream Payload ID Table
                                            SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_SYNC_PAYLOAD_TABLE);
                                        }
                                        else
                                        {
                                            // Analysis Finish
                                            SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                                        }
                                    }
                                }
                                else
                                {
                                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                                    {
                                        // Occupy Reply Pool
                                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                                        // Disable Reply Buffer Free
                                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                                        // Sync Downstream Payload ID Table
                                        SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_SYNC_PAYLOAD_TABLE);
                                    }
                                    else
                                    {
                                        return _FALSE;
                                    }
                                }
                            }
                            else
                            {
                                return _FALSE;
                            }
                        }
                    }
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    else if(GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_FAIL)
#else
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_FAIL)
#endif
                    {
                        if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() == 0)
                        {
                            if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_NO_SUPPORT)
                            {
                                // Analysis Finish
                                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                            }
                            else
                            {
                                if(GET_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE() == _FALSE)
                                {
                                    if(ucLCR > 0)
                                    {
                                        // Analysis Finish
                                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                                    }
                                    else
                                    {
                                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                                        {
                                            // Occupy Reply Pool
                                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                                            // Disable Reply Buffer Free
                                            CLR_DP_MST_RX_REPLY_BUF_FREE();

                                            // Sync Downstream Payload ID Table
                                            SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_SYNC_PAYLOAD_TABLE);
                                        }
                                        else
                                        {
                                            return _FALSE;
                                        }
                                    }
                                }
                                else
                                {
                                    return _FALSE;
                                }
                            }
                        }
                        else
                        {
                            // Reply Error MSG , Nack Reason : Link Failure
                            SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_LINK_FAILURE);
                        }
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
                else
                {
                    if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
                    {
                        // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                        SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                        SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                    }
                    else
                    {
                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

                            // Analysis Finish
                            SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }

                break;

            case _DP_MSG_QUERY_PAYLOAD:

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if(ScalerDpMstRxCheckIDExisted(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID()) == _TRUE)
                        {
                            if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_NO_SUPPORT)
                            {
                                if(ScalerDpMacTxCheckIDExisted(GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID()) == _TRUE)
                                {
                                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                                    {
                                        // Clear Reply Array Free Flag
                                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                                        // Disable Reply Buffer Free
                                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                                        // Analysis Finish
                                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                                    }
                                    else
                                    {
                                        return _FALSE;
                                    }
                                }
                                else
                                {
                                    // Error Bad param
                                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                                }
                            }
                            else
                            {
                                if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                                   (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                                {
                                    // Occupy Reply Pool
                                    CLR_DP_MST_RX_REPLY_POOL_FREE();

                                    // Disable Reply Buffer Free
                                    CLR_DP_MST_RX_REPLY_BUF_FREE();

                                    // Analysis Finish
                                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                                }
                                else
                                {
                                    return _FALSE;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_CLEAR_PAYLOAD_ID_TABLE:

                if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
                {
                    if((bit)GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_PATH() == _TRUE)
                    {
                        SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_CLEAR_ID_TABLE);
                    }
                    else
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }

                    if((bit)GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BROADCAST() == _TRUE)
                    {
                        // Set Broadcast Flag
                        SET_DP_MST_TX_DOWN_REQUEST_BROAD_MSG();
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_POWER_UP_PHY:

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Path MSG
                        if((bit)GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_PATH() == _TRUE)
                        {
                            SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_POWER_UP);
                        }
                        else // Node MSG
                        {
                            // Analysis Finish
                            SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                        }
                    }
                    else
                    {
                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

                            SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_POWER_UP);
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_POWER_DOWN_PHY:

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

                            if(ScalerDpMstTxGetStreamAllocate() == _FALSE)
                            {
                                SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_POWER_DOWN);
                            }
                            else
                            {
                                // Analysis Finish
                                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                            }
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_REMOTE_DPCD_READ:

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_NO_RESULT)
                        {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                            if((GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS) || (GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() != _LINK_ESTABLISH_READY))
#else
                            if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS)
#endif
                            {
                                return _FALSE;
                            }
                        }

                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                            if((ScalerDpMstRxGetVirtualDpEnable(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _TRUE) &&
                               (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() == 0))
                            {
                                SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_VIRTUAL_DPCD_READ);
                            }
                            else
#endif
                            {
                                SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_DPCD_READ);
                            }
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_REMOTE_DPCD_WRITE:

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_NO_RESULT)
                        {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                            if((GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS) || (GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() != _LINK_ESTABLISH_READY))
#else
                            if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS)
#endif
                            {
                                return _FALSE;
                            }
                        }

                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                            if((ScalerDpMstRxGetVirtualDpEnable(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _TRUE) &&
                               (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() == 0))
                            {
                                SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_VIRTUAL_DPCD_WRITE);
                            }
                            else
#endif
                            {
                                SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_DPCD_WRITE);
                            }
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_REMOTE_I2C_READ:

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_NO_RESULT)
                        {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                            if((GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS) || (GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() != _LINK_ESTABLISH_READY))
#else
                            if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS)
#endif
                            {
                                return _FALSE;
                            }
                        }

                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

                            SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_I2C_READ);
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_REMOTE_I2C_WRITE:

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
                    if(ucLCR > 0)
                    {
                        // Analysis Finish
                        SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_NO_RESULT)
                        {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                            if((GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS) || (GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() != _LINK_ESTABLISH_READY))
#else
                            if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS)
#endif
                            {
                                return _FALSE;
                            }
                        }

                        if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                           (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_MST_RX_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_MST_RX_REPLY_BUF_FREE();

                            SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_I2C_WRITE);
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }

                break;

            case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

                if(GET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_MST_RX_DOWN_REQUEST_BUF0)
                {
                    SET_DP_MST_TX_DOWN_REQUEST_BODY_LENGTH(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_LENGTH());
                }
                else
                {
                    SET_DP_MST_TX_DOWN_REQUEST_BODY_LENGTH(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_LENGTH());
                }

                if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG)
                {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                    if(GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE)
                    {
                        if(GET_DP_MST_TX_HDCP2_AUTH_PROCCESSING() == _FALSE)
                        {
                            SET_DP_HDCP2_TX_AUTH_START();

                            SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_QUERY_STREAM_ENCRYPTION_STATUS);
                        }
                        else
                        {
                            // Analysis Finish
                            SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                        }
                    }
                    else
#endif
                    {
                        if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                        {
                            if(GET_DP_MST_TX_HDCP_AUTH_PROCCESSING() == _FALSE)
                            {
                                SET_DP_TX_HDCP_AUTH_START();

                                SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_QUERY_STREAM_ENCRYPTION_STATUS);
                            }
                            else
                            {
                                // Analysis Finish
                                SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                            }
                        }
                        else
                        {
                            // Analysis Finish
                            SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                        }
                    }
                }
                else
                {
                    // Analysis Finish
                    SET_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }

                break;

            default:
                break;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Port Px Mapping to Port Num
// Input Value  : Px
// Output Value : Physical Port
//--------------------------------------------------
EnumDpMstPort ScalerDpMstTxPxPortNumMapping(EnumOutputPort enumOutputPort)
{
    EnumDpMstPort enumDpMstPort = _DP_PORT1;

    switch(enumOutputPort)
    {
#if(_P0_OUTPUT_TYPE != _P0_NO_PORT)
        case _P0_OUTPUT_PORT:

            enumDpMstPort = _DP_PORT1;

            break;
#endif

#if(_P1_OUTPUT_TYPE != _P1_NO_PORT)
        case _P1_OUTPUT_PORT:

            enumDpMstPort = _DP_PORT2;

            break;
#endif

#if(_P2_OUTPUT_TYPE != _P2_NO_PORT)
        case _P2_OUTPUT_PORT:

            enumDpMstPort = _DP_PORT3;

            break;
#endif

#if(_P3_OUTPUT_TYPE != _P3_NO_PORT)
        case _P3_OUTPUT_PORT:

            enumDpMstPort = _DP_PORT4;

            break;
#endif

#if(_P4_OUTPUT_TYPE != _P4_NO_PORT)
        case _P4_OUTPUT_PORT:

            enumDpMstPort = _DP_PORT5;

            break;
#endif

        default:
            break;
    }

    return enumDpMstPort;
}

//--------------------------------------------------
// Description  : DP Port Port Num Mapping to Px
// Input Value  : Physical Port
// Output Value : Px
//--------------------------------------------------
EnumOutputPort ScalerDpMstTxPortNumPxMapping(EnumDpMstPort enumDpMstPort)
{
    EnumOutputPort enumOutputPort = _NO_OUTPUT_PORT;

    switch(enumDpMstPort)
    {
#if(_P0_OUTPUT_TYPE != _P0_NO_PORT)
        case _DP_PORT1:

            enumOutputPort = _P0_OUTPUT_PORT;

            break;
#endif

#if(_P1_OUTPUT_TYPE != _P1_NO_PORT)
        case _DP_PORT2:

            enumOutputPort = _P1_OUTPUT_PORT;

            break;
#endif

#if(_P2_OUTPUT_TYPE != _P2_NO_PORT)
        case _DP_PORT3:

            enumOutputPort = _P2_OUTPUT_PORT;

            break;
#endif

#if(_P3_OUTPUT_TYPE != _P3_NO_PORT)
        case _DP_PORT4:

            enumOutputPort = _P3_OUTPUT_PORT;

            break;
#endif

#if(_P4_OUTPUT_TYPE != _P4_NO_PORT)
        case _DP_PORT5:

            enumOutputPort = _P4_OUTPUT_PORT;

            break;
#endif

        default:
            break;
    }

    return enumOutputPort;
}

//--------------------------------------------------
// Description  : Rx MSG Reply for DP
// Input Value  : Reply Message Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxDownReplyDirectlyMsg(void)
{
    BYTE pucData[2] = {0};
    BYTE ucTimeslot = 0;
    BYTE ucDpStream = 0;
    WORD usPBN = 0;
    EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

    ScalerDpRxSetBaseInputPort(enumInputPort);

    switch(GET_DP_MST_RX_MSG_REQUEST_ID())
    {
        case _DP_MSG_GET_MESSAGE_TRANSACTION_VERSION:

            // Set Message Body Length = 2
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_REQUEST_ID(_DP_MSG_GET_MESSAGE_TRANSACTION_VERSION);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            if(ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _ENABLE)
            {
                SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_VERSION(0x02);
            }
            else
#endif
            {
                if((GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_3) &&
                   (GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() >= _DP_TX_MSG_SUPPORT))
                {
                    SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_VERSION(0x02);
                }
                else
                {
                    SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_VERSION(0x01);
                }
            }

            break;

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        case _DP_MSG_LINK_ADDRESS:

            // Set Message Body Length = _DP_MSG_LINK_ADDRESS_BODY_LENGTH
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(40);

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_REQUEST_ID(_DP_MSG_LINK_ADDRESS);

#if(_DP_SUPPORT == _ON)
            // Set GUID
            for(pucData[0] = 0; pucData[0] < 16; pucData[0]++)
            {
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_GUID(pucData[0], ScalerDpMstRxGetVirtualDpcdInfo(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x00, (0x30 + pucData[0])));
            }
#endif

            // Set Number of Ports
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_PORT(2);

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_ZEROS();

            // Setting Port0 Is Input Port
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_TYPE(_DP_MST_RX_INPUT_PORT);

            // Setting Port Number Of Port0
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_NUM(_DP_PORT0);

            // Set Peer Device Type
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PEER_DEVICE_TYPE(_DP_TX_MST_OR_SST_BRANCH_DOWNSTREAM);

            // Set Message Capability status
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_MSG_CAP(_DP_TX_MSG_SUPPORT);

            // Setting Port0 Dp Plug Status
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PLUG_STATUS(_DP_PLUG);

            // Setting Physical Port1 is Output Port
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_TYPE(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), _DP_MST_RX_OUTPUT_PORT);

            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), _DP_PORT1);

            // Set Physical Port1 Peer Device Type
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PEER_DEVICE_TYPE(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), GET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE());

            // Set Physical Port1 Message Capability
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_MSG_CAP(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), _DP_TX_MSG_NO_SUPPORT);

            // Set Physical Port1 Dp Plug Status
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PLUG_STATUS(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), _HIGH);

            // Set Physical Port1 Legacy Plug Status
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_LEGACY_PLUG_STATUS(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), GET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS());

            // Set Physical Port1 DPCD Revision
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_DPCD_REV(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV());

            // Set Physical Port1 Number Of Secondary Streams
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), GET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP());

            // Set Physical Port1 Number Of Secondary Stream Sinks
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP_SINK(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), GET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK());

            // Set Physical Port1 Number Of Zeros
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_ZEROS(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8));

            // Set Physical Port1 GUID
            for(pucData[0] = 0; pucData[0] < 16; pucData[0]++)
            {
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT_GUID(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT8), pucData[0], 0);
            }

            break;
#endif

        case _DP_MSG_ENUM_PATH_RESOURCES:

            // Set Message Body Length = 6
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(6);

            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_REQUEST_ID(_DP_MSG_ENUM_PATH_RESOURCES);

            // Set Port Num
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM());

            // Set PBN
            ScalerDpMstTxSetDownReplyEnumPathPBN();

            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            // Set Message Body Length = 5
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(5);

            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REQUEST_ID(_DP_MSG_ALLOCATE_PAYLOAD);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM());

            // Set Payload ID
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

            if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
            {
                // Get # of Allocate timeslot
                ucTimeslot = ScalerDpMacTxCalTimeslotNeed(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN());

                // Calculate Allocated PBN
                usPBN = ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucTimeslot);

                // Set Allocated PBN
                SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(usPBN);
            }
            else
            {
                // Set PBN
                SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN());
            }

            break;

        case _DP_MSG_QUERY_PAYLOAD:

            // Set Message Body Length = 4
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(4);

            SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_REQUEST_ID(_DP_MSG_QUERY_PAYLOAD);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM());

            ucDpStream = ScalerDpMacTxSearchMatchStream(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

            if(ucDpStream != _DP_ST_NONE)
            {
                if(GET_DP_MAC_TX_DAISY_ST_STATUS_REG(ucDpStream) == _ENABLE)
                {
                    // Calculate # of Allocated Timeslot
                    ucTimeslot = GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(ucDpStream);

                    // Calculate Allocated PBN
                    usPBN = ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucTimeslot);

                    // Set Allocated PBN
                    SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(usPBN);
                }
                else
                {
                    // Set Allocated PBN
                    SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(0);
                }
            }

            break;

        case _DP_MSG_CLEAR_PAYLOAD_ID_TABLE:

            // Set Message Body Length = 1
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(1);

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REQUEST_ID(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);

            break;

        case _DP_MSG_POWER_UP_PHY:

            // Set Message Body Length = 2
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_MST_RX_DOWN_REPLY_POWER_UP_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_POWER_UP_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_POWER_UP_MSG_REQUEST_ID(_DP_MSG_POWER_UP_PHY);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_POWER_UP_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_POWER_UP_MSG_PORT_NUM());

            break;

        case _DP_MSG_POWER_DOWN_PHY:

            // Set Message Body Length = 2
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_MST_RX_DOWN_REPLY_POWER_DOWN_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_POWER_DOWN_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_POWER_DOWN_MSG_REQ_ID(_DP_MSG_POWER_DOWN_PHY);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_POWER_DOWN_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_POWER_DOWN_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_DPCD_READ:

            // Set Message Body Length
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH((3 + GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ()));

            SET_DP_MST_RX_DOWN_REPLY_MSG_REMOTE_DPCD_READ_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REQUEST_ID(_DP_MSG_REMOTE_DPCD_READ);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_PORT_NUM());

            // Set Number Of Read Byte
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_NUM_OF_READ(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ());

            break;

        case _DP_MSG_REMOTE_DPCD_WRITE:

            // Set Message Body Length
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCE_WRITE_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REQUEST_ID(_DP_MSG_REMOTE_DPCD_WRITE);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_I2C_READ:

            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_REQUEST_ID(_DP_MSG_REMOTE_I2C_READ);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_I2C_WRITE:

            // Set Message Body Length
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REQUEST_ID(_DP_MSG_REMOTE_I2C_WRITE);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM());

            break;

        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REQUEST_ID(_DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS);

            // Get Downstream Port Power Status
            if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                ScalerDpAuxTxNativeRead(0x00, 0x06, 0x00, 1, pucData);

                pucData[1] = ((pucData[0] & 0x07) == _BIT0) ? _DP_STREAM_ACTIVE : _DP_STREAM_NOT_ACTIVE;
            }
            else
            {
                pucData[1] = _DP_STREAM_NOT_EXIST;
            }

            // Set Stream State
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE(pucData[1]);

            // Set Stream Encryption
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION(ScalerDpMstTxGetHdcpEncryptEnable());

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if(GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE)
            {
                // Set Stream Repeater Function Present
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(GET_DP_HDCP2_TX_REPEATER_SUPPORTED());

                if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
                {
                    pucData[0] = (GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) ? _DP_OUTPUT_SINK_TYPE_MSG_NO_SUPPORT : _DP_OUTPUT_SINK_TYPE_NON_AUTHENTICABLE;
                }
                else
                {
                    pucData[0] = 0x00;
                }
            }
            else
#endif
            {
                // Set Stream Repeater Function Present
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER());

                if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
                {
                    pucData[0] = (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE) ? _DP_OUTPUT_SINK_TYPE_MSG_NO_SUPPORT : _DP_OUTPUT_SINK_TYPE_NON_AUTHENTICABLE;
                }
                else
                {
                    pucData[0] = 0x00;
                }
            }

            // Set Stream Output Sink Type
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE(pucData[0]);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if(GET_DP_MST_RX_HDCP2_MODE() == _HDCP_22)
            {
                // Set Message Body Length = 36
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(36);
            }
            else
#endif
            {
                // Set Message Body Length = 24
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(24);
            }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if(GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE)
            {
                pucData[0] = _HDCP_FEATURE_2_2;
            }
            else
#endif
            {
                if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                {
                    pucData[0] = _HDCP_FEATURE_1_1;
                }
                else
                {
                    pucData[0] = 0x00;
                }
            }

            // Set Stream Output CP Type
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(pucData[0]);

            // Set Stream Authentication
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if(ScalerDpHdcp2TxGetHdcpMode() == _ENABLE)
            {
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_MST_TX_HDCP2_AUTH_PROC_PASS());
            }
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_MST_TX_HDCP_AUTH_PROC_PASS());
            }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if((GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) &&
               ((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)))
#else
            if((GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE))
#endif
            {
                // Set Signed
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(1);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if(GET_DP_MST_RX_HDCP2_MODE() == _HDCP_22)
                {
                    DebugMessageHDCP2("[QSE] Tx-2 : Cal Signature L'", 0);

                    // Calculate Signature L'
                    ScalerDpMstRxQueryEncryptionWriteSha256Input(GET_DP_MST_RX_HDCP2_REPEATER_SUPPORTED());

                    // Set Stream State Signature L'
                    for(pucData[0] = 0; pucData[0] < 32; pucData[0]++)
                    {
                        SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pucData[0], GET_DP_MST_RX_REG_HDCP_SHA256_RESULT(pucData[0]));
                    }
                }
                else
#endif
                {
                    // Calculate Signature L' for Upstream
                    ScalerDpMstRxQueryEncryptionWriteShaInput();

                    // Set Stream State Signature L'for Upstream
                    for(pucData[0] = 0; pucData[0] < 20; pucData[0]++)
                    {
                        SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pucData[0], GET_DP_MST_RX_REG_HDCP_SHA_RESULT(pucData[0]));
                    }
                }
            }
            else
            {
                // Set Signed
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(0);

                // Reset Stream State Signature L'
                for(pucData[0] = 0; pucData[0] < 20; pucData[0]++)
                {
                    SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pucData[0], 0x00);
                }
            }

            // Set Stream ID
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID(GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());

            break;

        default:

            break;
    }

    if((GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE) || (GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS))
    {
        // Set LCT
        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(1);

        // Set LCR
        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(0x00);
    }
    else
    {
        // Set LCT
        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT());

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        if((ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _ENABLE) && (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0))
        {
            BYTE ucRadIndex = 0;

            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() - 2);

            // Set RAD
            for(ucRadIndex = 0; ucRadIndex < GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(); ucRadIndex++)
            {
                BYTE ucRadValue = ScalerDpMstRxGetRegDownRequestRad(enumInputPort, ucRadIndex + GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR());
                ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, ucRadIndex, ucRadValue);
            }

            ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, ucRadIndex, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM());
        }
        else
#endif
        {
#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
            if(GET_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR() == _TRUE)
            {
                CLR_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR();

                // Set LCR
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() - GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() - 1);
            }
            else
#endif
            {
                if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_UNPLUG)
                {
                    // Set LCR
                    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() - GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() - 1);
                }
                else
                {
                    // Set LCR
                    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() - 1);
                }
            }

            // Set RAD
            for(BYTE ucRadIndex = 0; ucRadIndex < GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(); ucRadIndex++)
            {
                BYTE ucRadValue = ScalerDpMstRxGetRegDownRequestRad(enumInputPort, ucRadIndex);
                ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, ucRadIndex, ucRadValue);
            }
        }
    }

    // Set Broadcast and Path
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BROADCAST());
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_PATH());

    // Set MSN
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_MSN(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_MSN());
}

//--------------------------------------------------
// Description  : Set Tx Down Reply EnumPath PBN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSetDownReplyEnumPathPBN(void)
{
    DWORD ulFullPBN = 0;
    DWORD ulAvailablePBN = 0;
    EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();

    if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT)
    {
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x90, _BIT0) == _TRUE)
        {
#if((_DP_MST_MULTI_FUNCTION_SUPPORT == _ON) && (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON))
            if((ScalerDpMstRxGetVirtualDpEnable(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _TRUE) &&
               (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() == 0))
            {
                SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(_TRUE);
            }
            else
#endif
            {
#if(_DP_TX_FEC_SUPPORT == _ON)
                if(GET_DP_TX_DOWNSTREAM_FEC_SUPPORT() == _TRUE)
                {
                    // Set FEC Capability
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(_TRUE);
                }
                else
#endif
                {
                    // Set FEC Capability
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(_FALSE);
                }
            }
        }
        else
        {
            // Set FEC Capability
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(_FALSE);
        }

        ulFullPBN = ScalerDpMstTxGetFullPBN();

        ulAvailablePBN = ScalerDpMstTxGetAvailablePBN();

        // Set Full PBN
        SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN(ulFullPBN);

        SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(ulAvailablePBN);
    }
    else
    {
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x90, _BIT0) == _TRUE)
        {
#if((_DP_MST_MULTI_FUNCTION_SUPPORT == _ON) && (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON))
            if((ScalerDpMstRxGetVirtualDpEnable(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _TRUE) &&
               (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() == 0))
            {
                SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(_TRUE);
            }
            else
#endif
            {
#if(_DP_TX_FEC_SUPPORT == _ON)
                if(GET_DP_TX_DOWNSTREAM_FEC_SUPPORT() == _TRUE)
                {
                    // Set FEC Capability
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(_TRUE);
                }
                else
#endif
                {
                    // Set FEC Capability
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(_FALSE);
                }
            }
        }
        else
        {
            // Set FEC Capability
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(_FALSE);
        }

        ulFullPBN = ScalerDpMstTxGetFullPBN();

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
        {
            ulFullPBN = (ulFullPBN < _DP_MAC_DPHY_RX_MAX_PBN_128B132B) ? (ulFullPBN) : (_DP_MAC_DPHY_RX_MAX_PBN_128B132B);
        }
        else
#endif
        {
            ulFullPBN = (ulFullPBN < _DP_MAC_DPHY_RX_MAX_PBN_8B10B) ? (ulFullPBN) : (_DP_MAC_DPHY_RX_MAX_PBN_8B10B);
        }

        // Set Full PBN
        SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN(ulFullPBN);

        if(ScalerDpMacTxGetDaisySourceMuxBackup(_DP_ST_SOURCE1) == _DP_ST_NONE)
        {
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(GET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN());
        }
        else
        {
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(0);
        }
    }
}

//--------------------------------------------------
// Description  : Get Tx CRC Status of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxGetDownReplyCrcFailed(void)
{
    if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE();
    }
    else
    {
        return GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE();
    }
}

//--------------------------------------------------
// Description  : Get Tx LCT of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMstTxGetDownReplyLct(void)
{
    if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return ((BYTE)g_stDpMstTxMsgBackupHeaderInfo0.b4MsgLct);
    }
    else
    {
        return ((BYTE)g_stDpMstTxMsgBackupHeaderInfo1.b4MsgLct);
    }
}

//--------------------------------------------------
// Description  : Get Tx LCR of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMstTxGetDownReplyLcr(void)
{
    if(GET_DP_MST_RX_MSG_REPLY_ID() == _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS)
    {
        if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
        {
            return (((BYTE)g_stDpMstTxMsgBackupHeaderInfo0.b4MsgLcr) & 0x0f);
        }
        else
        {
            return (((BYTE)g_stDpMstTxMsgBackupHeaderInfo1.b4MsgLcr) & 0x0f);
        }
    }
    else
    {
        if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
        {
            return ((((BYTE)g_stDpMstTxMsgBackupHeaderInfo0.b4MsgLcr) & 0x0f) - 1);
        }
        else
        {
            return ((((BYTE)g_stDpMstTxMsgBackupHeaderInfo1.b4MsgLcr) & 0x0f) - 1);
        }
    }
}

//--------------------------------------------------
// Description  : Get Tx Broadcast Bit of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxGetDownReplyBroadcastBit(void)
{
    if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return g_stDpMstTxMsgBackupHeaderInfo0.b1MsgBroadcast;
    }
    else
    {
        return g_stDpMstTxMsgBackupHeaderInfo1.b1MsgBroadcast;
    }
}

//--------------------------------------------------
// Description  : Get Tx Path Bit of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxGetDownReplyPathBit(void)
{
    if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return g_stDpMstTxMsgBackupHeaderInfo0.b1MsgPath;
    }
    else
    {
        return g_stDpMstTxMsgBackupHeaderInfo1.b1MsgPath;
    }
}

//--------------------------------------------------
// Description  : Get Tx MSN of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxGetDownReplyMsn(void)
{
    if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return g_stDpMstTxMsgBackupHeaderInfo0.b1MsgMsn;
    }
    else
    {
        return g_stDpMstTxMsgBackupHeaderInfo1.b1MsgMsn;
    }
}

//--------------------------------------------------
// Description  : Get Tx Length of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMstTxGetDownReplyLength(void)
{
    if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH();
    }
    else
    {
        return GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH();
    }
}

//--------------------------------------------------
// Description  : Tx Bypass MSG Header Modify for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxDownReplyBypassHeaderModify(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

    // Set LCT
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(ScalerDpMstTxGetDownReplyLct());

    // Set LCR
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(ScalerDpMstTxGetDownReplyLcr());

    // Update RAD
    ScalerDpMstTxModifyRAD(_DP_DOWN_REPLY_MSG);

    // Set Broadcast
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(ScalerDpMstTxGetDownReplyBroadcastBit());

    // Set Path
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(ScalerDpMstTxGetDownReplyPathBit());

    // Set MSN
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_MSN(ScalerDpMstTxGetDownReplyMsn());

    // Set MSG Body Length
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(ScalerDpMstTxGetDownReplyLength());
}

//--------------------------------------------------
// Description  : Tx DownReply MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxDownReplyBypass(void)
{
    BYTE ucTimeslot = 0;
    EnumDpStreamNum enumDpStreamNum = _DP_ST_NONE;
    WORD usPBN = 0;

    switch(GET_DP_MST_RX_MSG_REPLY_ID())
    {
        case _DP_MSG_ENUM_PATH_RESOURCES:

            if(ScalerDpMstTxGetDownReplyPathBit() == _TRUE)
            {
                // Get DownStream Available PBN
                usPBN = ScalerDpMstTxGetAvailablePBN();

                if(usPBN < GET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN())
                {
                    // Set Available PBN
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(usPBN);
                }

                // Get DownStream Full PBN
                usPBN = ScalerDpMstTxGetFullPBN();

                if(usPBN < GET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN())
                {
                    // Set Available PBN
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN(usPBN);
                }
            }

            SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();

            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            if(GET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN() == 0)
            {
                if(ScalerDpMstTxGetDownReplyPathBit() == _TRUE)
                {
                    SET_DP_MST_TX_DOWN_REPLY_EVENT(_DP_TX_SYNC_PAYLOAD_TABLE);
                }
                else
                {
                    SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
                }
            }
            else
            {
                // Get Using STX for this ID
                enumDpStreamNum = ScalerDpMacTxSearchMatchStream(GET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

                ucTimeslot = GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(enumDpStreamNum);

                if(ucTimeslot != 0)
                {
                    usPBN = ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucTimeslot);

                    if(usPBN > GET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN())
                    {
                        SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(usPBN);
                    }
                }

                // For PBN > 0 Case
                SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }

            break;

        case _DP_MSG_POWER_DOWN_PHY:

            if((ScalerDpMstTxGetDownReplyPathBit() == _TRUE) &&
               (GET_DP_MST_RX_MSG_REPLY_TYPE() == _DP_MST_RX_MSG_ACK) &&
               (ScalerDpMstTxGetStreamAllocate() == _FALSE))
            {
                SET_DP_MST_TX_DOWN_REPLY_EVENT(_DP_TX_POWER_DOWN);
            }
            else
            {
                SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }

            break;

        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            SET_DP_MST_TX_DOWN_REPLY_EVENT(_DP_TX_QUERY_STREAM_ENCRYPTION_STATUS);

            break;

        default:

            SET_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();

            break;
    }
}



/*
//--------------------------------------------------
// Description  : Monitor Tx Down stream Bandwidth
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxMonitorDownstreamBW(void)
{
    BYTE ucCurrentPBNPerTimerslot = GET_DP_PBN_PER_TIME_SLOT(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM());

    if(GET_DP_TX_LINK_PBN_PER_TIMESOLT() == 0)
    {
        // Set PBN per Timeslot
        SET_DP_TX_LINK_PBN_PER_TIMESOLT(ucCurrentPBNPerTimerslot);
    }

    // Check Tx Downstream BW Whether Change or not
    if((GET_DP_TX_LINK_PBN_PER_TIMESOLT() != ucCurrentPBNPerTimerslot))
    {
        if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT)
        {
            if((GET_REG_DP_RX_DAIZY_ST3_START() != 0) || (GET_REG_DP_RX_DAIZY_ST4_START() != 0) || (GET_REG_DP_RX_DAIZY_ST5_START() != 0))
            {
                if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0xC0, 1, pData) == _TRUE)
                {
                    // VC Payload Table Exception Clear
                    if((pData[0] & _BIT2) != _BIT2)
                    {
                        // Timeslot Local Recovery
                        ScalerDpMacTxLocalRecoveryPayloadTable(ucCurrentPBNPerTimerslot);
                    }
                }
            }
        }
        else
        {
            // Get STx
            pData[0] = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2);

            // Get STx using Length : End Position - Start Position + 1
            pData[1] = GET_DP_RX_MST_STREAM_TIME_SLOT(pData[0] - 1);

            if(((WORD)ucCurrentPBNPerTimerslot << 6) < ((WORD)pData[1] * GET_DP_TX_LINK_PBN_PER_TIMESOLT()))
            {
                ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);

                SET_DP_RX_MST2SST_ENABLE(_DISABLE);
            }
        }

#if(_DP_SUPPORT == _ON)
        // if Up Request Support
        if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) == _BIT1)
        {
            // Issue Resource Status Notify
            SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_RESOURCE_STATUS_NOTIFY);
        }
#endif

        // Set PBN per Timeslot
        SET_DP_TX_LINK_PBN_PER_TIMESOLT(ucCurrentPBNPerTimerslot);
    }

    if(GET_DP_RX_SELF_GEN_UP_REQUEST_RETRY() == _DP_MSG_RESOURCE_STATUS_NOTIFY)
    {
        CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();

        SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_RESOURCE_STATUS_NOTIFY);
    }
}

//--------------------------------------------------
// Description  : Tx Payload Table Local Recovery as Link Loss
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacTxLocalRecoveryPayloadTable(BYTE ucCurrentPBNPerTimerslot)
{
    WORD usCurrentAvailablePBN = ucCurrentPBNPerTimerslot * 63;
    WORD usPastAllocatedPBN = 0;
    BYTE ucStreamOrder[3];

    // Initial Stream Order
    ucStreamOrder[0] = 0;
    ucStreamOrder[1] = 1;
    ucStreamOrder[2] = 2;

    // Sorting Bypass Stream based on Start Position
    pData[0] = GET_REG_DP_RX_DAIZY_ST3_START();
    pData[1] = GET_REG_DP_RX_DAIZY_ST4_START();
    pData[2] = GET_REG_DP_RX_DAIZY_ST5_START();

    if(pData[0] > pData[1])
    {
        ucStreamOrder[0] = 1;
        ucStreamOrder[1] = 0;
    }

    if(pData[2] < pData[ucStreamOrder[0]])
    {
        ucStreamOrder[2] = ucStreamOrder[1];
        ucStreamOrder[1] = ucStreamOrder[0];
        ucStreamOrder[0] = 2;
    }
    else if(pData[2] < pData[ucStreamOrder[1]])
    {
        ucStreamOrder[2] = ucStreamOrder[1];
        ucStreamOrder[1] = 2;
    }
    else
    {
        ucStreamOrder[2] = 2;
    }

    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        if(ScalerGetBit(GET_DP_TX_STX_START_ADDRESS(ucStreamOrder[pData[0]] + 2), 0x3F) != 0)
        {
            // Get Past Allocated PBN
            usPastAllocatedPBN = (ScalerGetBit(GET_DP_TX_STX_START_ADDRESS(ucStreamOrder[pData[0]] + 2), 0x3F) -
                                  ScalerGetBit(GET_DP_TX_STX_END_ADDRESS(ucStreamOrder[pData[0]] + 2), 0x3F) + 1) *
                                  GET_DP_TX_LINK_PBN_PER_TIMESOLT();

            // Get STx
            pData[1] = ScalerDpRxMstStreamMuxCheck(ucStreamOrder[pData[0]] + 2) - 1;

            if(usCurrentAvailablePBN >= usPastAllocatedPBN)
            {
                // Get Remain Available PBN
                usCurrentAvailablePBN = usCurrentAvailablePBN - usPastAllocatedPBN;

                // Modify Daisy Chain Timeslot Length
                ScalerDpMacTxMstSyncTableProcess(g_pucDpStreamToIdMapping[pData[1]], usPastAllocatedPBN);
            }
            else
            {
                // Delete Daisy Chain Timeslot
                ScalerDpMacTxMstSyncTableProcess(g_pucDpStreamToIdMapping[pData[1]], 0);
            }
        }
    }
}
*/


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpMstTxGetRegUpstreamMsgRad(BYTE ucRadIndex)
{
    if(ucRadIndex >= (sizeof(tDpMstTxRadBaseBitMap) / sizeof(tDpMstTxRadBaseBitMap[0])))
    {
        return 0;
    }

    BYTE ucBaseBit = tDpMstTxRadBaseBitMap[ucRadIndex];
    DWORD ulMask = (0x0FU) << ucBaseBit;
    DWORD ulAddress = ((ucRadIndex < 6) ? PB18083_94_MSG_RD_DATA0 : PB18083_98_MSG_RD_DATA1);

    DWORD ulValue = Scaler32GetBit(ulAddress, ulMask);

    return (ulValue >> ucBaseBit) % 0x0F;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMstTxSetRegDownstreamMsgRad(BYTE ucRadIndex, BYTE ucValue)
{
    if(ucRadIndex >= (sizeof(tDpMstTxRadBaseBitMap) / sizeof(tDpMstTxRadBaseBitMap[0])))
    {
        return;
    }

    BYTE ucBaseBit = tDpMstTxRadBaseBitMap[ucRadIndex];
    DWORD ulMask = (0x0FU) << ucBaseBit;
    DWORD ulAddress = ((ucRadIndex < 6) ? PB18083_10_MSG_WR_SET0 : PB18083_14_MSG_WR_SET1);

    DWORD ulValue = ((ucValue % 0x0F) << ucBaseBit);

    Scaler32SetBit(ulAddress, ~ulMask, ulValue);
}

//--------------------------------------------------
// Description  : Modify RAD
// Input Value  : Target Message Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxModifyRAD(EnumDpMessageType enumMsgType)
{
    BYTE ucLCR = 0;
    BYTE ucLCT = 0;

    if(GET_DP_MST_RX_MSG_REPLY_ID() != _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS)
    {
        if(enumMsgType == _DP_DOWN_REQUEST_MSG)
        {
            BYTE ucRadIndex = 0;
            EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

            ScalerDpRxSetBaseInputPort(enumInputPort);

            ucLCR = GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR();
            ucLCT = GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT();

            // Copy RAD
            for(ucRadIndex = 0; ucRadIndex < (ucLCT - 1); ucRadIndex++)
            {
                ScalerDpMstTxSetRegDownstreamMsgRad(ucRadIndex, ScalerDpMstRxGetRegDownRequestRad(enumInputPort, ucRadIndex));
            }

            // Update RAD
            for(ucRadIndex = 0; ucRadIndex < (ucLCR - 1); ucRadIndex++)
            {
                ScalerDpMstTxSetRegDownstreamMsgRad(ucRadIndex, ScalerDpMstRxGetRegDownRequestRad(enumInputPort, ucRadIndex + 1));
            }

            // Record Input Port
            ScalerDpMstTxSetRegDownstreamMsgRad(ucRadIndex, _DP_PORT0);
        }
        else if(enumMsgType == _DP_DOWN_REPLY_MSG)
        {
            StructTxDownReplyMsgInterleaveHeaderInfo *pstDpMstTxMsgDownReplyHeaderPtr = (GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE) ? &g_stDpMstTxMsgBackupHeaderInfo0 : &g_stDpMstTxMsgBackupHeaderInfo1;
            BYTE ucRadIndex = 0;
            EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();

            ScalerDpRxSetBaseInputPort(enumInputPort);

            ucLCR = pstDpMstTxMsgDownReplyHeaderPtr->b4MsgLcr;
            ucLCT = pstDpMstTxMsgDownReplyHeaderPtr->b4MsgLct;

            // Copy RAD
            for(ucRadIndex = 0; ucRadIndex < (ucLCT - 1); ucRadIndex++)
            {
                ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, ucRadIndex, (pstDpMstTxMsgDownReplyHeaderPtr->pucMsgRad[ucRadIndex]));
            }

            // Update RAD
            for(ucRadIndex = 0; ucRadIndex < (ucLCR - 1); ucRadIndex++)
            {
                ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, ucRadIndex, (pstDpMstTxMsgDownReplyHeaderPtr->pucMsgRad[ucRadIndex + 1]));
            }

            // Record Input Port
            ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, ucRadIndex, _DP_PORT1);
        }
    }
}

//--------------------------------------------------
// Description  : Tx Error MSG Reply for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxIllegalMsgReply(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

    SET_DP_MST_TX_UP_REPLY_BODY_LENGTH(19);

    //================ Body Info ==============

    // Set Reply Type
    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_REPLY_TYPE(_DP_MST_RX_MSG_NACK);

    // Set Request ID
    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_REQUESET_ID(GET_DP_MST_RX_MSG_REQUEST_ID());

#if(_DP_SUPPORT == _ON)
    // Set GUID
    for(BYTE ucIndex = 0; ucIndex < 16; ucIndex++)
    {
        SET_DP_MST_RX_REPLY_ILLEGAL_MSG_GUID(ucIndex, GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, (0x30 + ucIndex)));
    }
#endif

    // Set NACK Reason at MSG analysis

    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_DATA(0);

    //================ Header Info ==============
    // Set LCT
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LCT(GET_DP_MST_TX_REG_UPSTREAM_MSG_LCT());

    // Set LCR
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LCR(GET_DP_MST_TX_REG_UPSTREAM_MSG_LCT() - 1);

    // Set Broadcast Bit
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_BROADCAST(GET_DP_MST_TX_REG_UPSTREAM_MSG_BROADCAST());

    // Set Path Bit
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_PATH(GET_DP_MST_TX_REG_UPSTREAM_MSG_PATH());

    // Set TX MSG Write Total Length
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_LENGTH(GET_DP_MST_TX_UP_REPLY_BODY_LENGTH());

    // Set MSG Bit
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_MSN(GET_DP_MST_TX_REG_UPSTREAM_MSG_MSN());

    /*
    if(GET_DP_RX_MSG_ERROR_TYPE() != _NONE_MSG_ERROR)
    {
        switch(GET_DP_RX_MSG_ERROR_TYPE())
        {
            case _WRITE_FAILURE:

                break;

            case _INVALID_RAD:

                break;

            case _CRC_FAILURE:

                break;

            case _BAD_PARAM:

                break;

            case _DEFER:

                break;

            case _LINK_FAILURE:

                break;

            case _NO_RESOURCES:

                break;

            case _DPCD_FAIL:

                break;

            case _I2C_NAK:

                break;

            case _ALLOCATE_FAIL:

                break;

            default:

                break;
        }

        //SET_DP_RX_EVENT(_NONE_MSG_ERROR);
    }
    */
}

//--------------------------------------------------
// Description  : Tx I2C Over Aux Read Down Stream
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMstTxI2CRead(void)
{
    BYTE ucArrayIndex = 2;
    BYTE ucLength = _DP_MST_TX_I2C_MAX_TRANSACTION_LENGTH;
    BYTE ucReadIndex = 0;
    BYTE pucData[3] = {0};
    BYTE ucCnt = 0;
    bit bMot = 1;

    ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());

#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
    // Ddcci Read Write Intercept & Set Adjust LCR When Reply
    if(GET_DP_MST_TX_INTERCEPT_DDCCI_MSG_STATUS() == _TRUE)
    {
        if(g_unDpMstRxRequestPool.pucData[ucArrayIndex] == _DP_MSG_IIC_DEVICE_DDCCI)
        {
            // Reply Null Msg
            g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[0] = 0x6E;
            g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[1] = 0x80;
            g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[2] = (0x50 ^ 0x6E ^ 0x80);

            // Set Number Of Byte Read
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(3);

            // Set Message Body Length
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(6);

            SET_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR();

            return _TRUE;
        }
    }
#endif

    if(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE() > 0)
    {
        CLR_DP_MST_TX_EDID_READ_POSITION();

        for(ucCnt = 0; ucCnt < GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE(); ucCnt++)
        {
            // Get write Length Offset
            pucData[0] = ucArrayIndex + 1;

            // Get write Data Offset
            pucData[1] = pucData[0] + 1;

            // Get MOT and Transaction Delay Offset
            pucData[2] = pucData[1] + g_unDpMstRxRequestPool.pucData[pucData[0]];

            // Set I2C Write Command
            if(ScalerDpMstTxI2CWrite(g_unDpMstRxRequestPool.pucData[ucArrayIndex], g_unDpMstRxRequestPool.pucData[pucData[0]],
                                     &g_unDpMstRxRequestPool.pucData[pucData[1]], (bit)(g_unDpMstRxRequestPool.pucData[pucData[2]] & _BIT4)) == _TRUE)
            {
                // Set I2C Transaction Delay
                ScalerTimerDelayXms((g_unDpMstRxRequestPool.pucData[pucData[2]] & 0x0F) * 10);
            }
            else
            {
                SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_TRANSACTION(ucCnt + 1);

                // I2C Write Fail
                return _FALSE;
            }

            // Set Offset to Indicate Write_I2C_Device ID for Next Write Transcation
            ucArrayIndex = pucData[2] + 1;
        }
    }

    // Not EDID Read
    if(g_unDpMstRxRequestPool.pucData[ucArrayIndex] != _DP_MSG_IIC_DEVICE_EDID)
    {
        do
        {
            if((g_unDpMstRxRequestPool.pucData[ucArrayIndex + 1] - ucReadIndex) <= _DP_MST_TX_I2C_MAX_TRANSACTION_LENGTH)
            {
                ucLength = (g_unDpMstRxRequestPool.pucData[ucArrayIndex + 1] - ucReadIndex);

                bMot = 0;
            }

            if(ScalerDpAuxTxI2CoverRead(g_unDpMstRxRequestPool.pucData[ucArrayIndex], ucLength, &(g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[ucReadIndex]), bMot) == _TRUE)
            {
                ucReadIndex += ucLength;
            }
            else
            {
                // Read I2C Data Fail
                break;
            }
        }
        while(g_unDpMstRxRequestPool.pucData[ucArrayIndex + 1] > ucReadIndex);
    }
    else
    {
        ucLength = g_unDpMstRxRequestPool.pucData[ucArrayIndex + 1];

#if(_MST_DFP_SINK_EDID_REPORT_SOURCE_METHOD == _BYPASS_RAW_DATA)
        if(ScalerDpMacTxReadDfpDeviceEdid(GET_DP_MST_TX_EDID_READ_POSITION(), ucLength, g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead) == _TRUE)
#else
        if((GET_DP_MST_TX_EDID_READ_POSITION() + ucLength) > _DP_TX_EDID_SIZE_MAX)
        {
            ucLength = _DP_TX_EDID_SIZE_MAX - GET_DP_MST_TX_EDID_READ_POSITION();
        }

        if(ScalerDpMacTxGetDfpDeviceStoredEdid(GET_DP_MST_TX_EDID_READ_POSITION(), ucLength, g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead) == _TRUE)
#endif
        {
            INC_DP_MST_TX_EDID_READ_POSITION(g_unDpMstRxRequestPool.pucData[ucArrayIndex + 1]);

            if(GET_DP_MST_TX_EDID_READ_POSITION() >= _DP_TX_EDID_SIZE_MAX)
            {
                CLR_DP_MST_TX_EDID_READ_POSITION();
            }

            ucReadIndex += ucLength;
        }
    }

    // Set Number Of Byte Read
    SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(ucReadIndex);

    // Set Message Body Length
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(3 + ucReadIndex);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Tx I2C Over Aux Write Down Stream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxI2CWrite(BYTE ucI2CDeviceID, BYTE ucWriteNum, BYTE *pucData, bit bNoStop)
{
    BYTE ucLength = _DP_MST_TX_I2C_MAX_TRANSACTION_LENGTH;
    BYTE ucWriteIndex = 0;
    bit bMot = 1;

#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
    // Ddcci Read Write Intercept & Set Adjust LCR When Reply
    if(GET_DP_MST_TX_INTERCEPT_DDCCI_MSG_STATUS() == _TRUE)
    {
        if(ucI2CDeviceID == _DP_MSG_IIC_DEVICE_DDCCI)
        {
            SET_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR();
            return _TRUE;
        }
    }
#endif

    switch(ucI2CDeviceID)
    {
        // Set EDID Segment
        case _DP_MSG_IIC_DEVICE_EDID_SEGMENT:

            CLR_DP_MST_TX_EDID_READ_POSITION();

            if(ucWriteNum > 0)
            {
                SET_DP_MST_TX_EDID_READ_SEGMENT(pucData[ucWriteNum - 1]);

#if(_MST_DFP_SINK_EDID_REPORT_SOURCE_METHOD == _BACKUP_DDCRAM_DATA)
                if(GET_DP_MST_TX_EDID_READ_POSITION() >= _DP_TX_EDID_SIZE_MAX)
                {
                    CLR_DP_MST_TX_EDID_READ_POSITION();
                }
#endif
            }

            break;

        // Set EDID Offset
        case _DP_MSG_IIC_DEVICE_EDID:

            if(ucWriteNum > 0)
            {
                SET_DP_MST_TX_EDID_READ_OFFSET(pucData[ucWriteNum - 1]);

#if(_MST_DFP_SINK_EDID_REPORT_SOURCE_METHOD == _BACKUP_DDCRAM_DATA)
                if(GET_DP_MST_TX_EDID_READ_POSITION() >= _DP_TX_EDID_SIZE_MAX)
                {
                    CLR_DP_MST_TX_EDID_READ_POSITION();
                }
#endif
            }

            break;

        default:

            do
            {
                if((ucWriteNum - ucWriteIndex) <= _DP_MST_TX_I2C_MAX_TRANSACTION_LENGTH)
                {
                    ucLength = (ucWriteNum - ucWriteIndex);

                    bMot = bNoStop;
                }

                if(ScalerDpAuxTxI2CoverWrite(ucI2CDeviceID, ucLength, &pucData[ucWriteIndex], bMot) == _TRUE)
                {
                    ucWriteIndex += ucLength;
                }
                else
                {
                    // Write I2C Data Fail
                    return _FALSE;
                }
            }
            while(ucWriteNum > ucWriteIndex);

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Tx Mst Msg Count Check Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxMsgCountResetEvent(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

    if(GET_DP_MST_TX_RECEIVED_MSG_COUNT() != 0)
    {
        // Update Total Received Count
        if(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() >= GET_DP_MST_TX_RECEIVED_MSG_COUNT())
        {
            SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() - GET_DP_MST_TX_RECEIVED_MSG_COUNT());
        }
        else
        {
            SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(0);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
        }

        // Reset Tx Received Count
        SET_DP_MST_TX_RECEIVED_MSG_COUNT(0);
    }

    CLR_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
}




//--------------------------------------------------
// Description  : L = SHA-1(Stream-Status | Q_id | S_id | An | Bksv | V | M0)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxQueryEncryptionWriteShaInput(void)
{
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT3 | _BIT0), _BIT3);

    // Reset SHA Block counter
    CLR_DP_MST_TX_REG_SHA_ENABLE();

    // Start to Write SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_ENABLE();

    // 1. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(g_unDpMstRxReplyPool.pucData[1]);
    SET_DP_MST_TX_REG_SHA_INPUT_1(g_unDpMstRxReplyPool.pucData[2]);
    SET_DP_MST_TX_REG_SHA_INPUT_2(g_pucDpMstRxMsgQueryEncryptClientId[0]);
    SET_DP_MST_TX_REG_SHA_INPUT_3(g_pucDpMstRxMsgQueryEncryptClientId[1]);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    // 2. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(g_pucDpMstRxMsgQueryEncryptClientId[2]);
    SET_DP_MST_TX_REG_SHA_INPUT_1(g_pucDpMstRxMsgQueryEncryptClientId[3]);
    SET_DP_MST_TX_REG_SHA_INPUT_2(g_pucDpMstRxMsgQueryEncryptClientId[4]);
    SET_DP_MST_TX_REG_SHA_INPUT_3(g_pucDpMstRxMsgQueryEncryptClientId[5]);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    // 3. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(g_pucDpMstRxMsgQueryEncryptClientId[6]);
    SET_DP_MST_TX_REG_SHA_INPUT_1(GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());
    SET_DP_MST_TX_REG_SHA_INPUT_2(GET_DP_MST_TX_REG_HDCP_AN(0));
    SET_DP_MST_TX_REG_SHA_INPUT_3(GET_DP_MST_TX_REG_HDCP_AN(1));

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    // 4. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(GET_DP_MST_TX_REG_HDCP_AN(2));
    SET_DP_MST_TX_REG_SHA_INPUT_1(GET_DP_MST_TX_REG_HDCP_AN(3));
    SET_DP_MST_TX_REG_SHA_INPUT_2(GET_DP_MST_TX_REG_HDCP_AN(4));
    SET_DP_MST_TX_REG_SHA_INPUT_3(GET_DP_MST_TX_REG_HDCP_AN(5));

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    // 5. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(GET_DP_MST_TX_REG_HDCP_AN(6));
    SET_DP_MST_TX_REG_SHA_INPUT_1(GET_DP_MST_TX_REG_HDCP_AN(7));
    SET_DP_MST_TX_REG_SHA_INPUT_2(GET_DP_MST_TX_REG_HDCP_BKSV(0));
    SET_DP_MST_TX_REG_SHA_INPUT_3(GET_DP_MST_TX_REG_HDCP_BKSV(1));

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    // 6. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(GET_DP_MST_TX_REG_HDCP_BKSV(2));
    SET_DP_MST_TX_REG_SHA_INPUT_1(GET_DP_MST_TX_REG_HDCP_BKSV(3));
    SET_DP_MST_TX_REG_SHA_INPUT_2(GET_DP_MST_TX_REG_HDCP_BKSV(4));
    SET_DP_MST_TX_REG_SHA_INPUT_3(g_pucDpMacTxHdcpDownStreamV[0]);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    BYTE ucIndex = 1;

    do
    {
        // 7~10. Write Data into SHA-1 Transform Input
        SET_DP_MST_TX_REG_SHA_INPUT_0(g_pucDpMacTxHdcpDownStreamV[ucIndex]);
        SET_DP_MST_TX_REG_SHA_INPUT_1(g_pucDpMacTxHdcpDownStreamV[ucIndex + 1]);
        SET_DP_MST_TX_REG_SHA_INPUT_2(g_pucDpMacTxHdcpDownStreamV[ucIndex + 2]);
        SET_DP_MST_TX_REG_SHA_INPUT_3(g_pucDpMacTxHdcpDownStreamV[ucIndex + 3]);

        // Enable write 32-bit data to SHA-1 block
        SET_DP_MST_TX_REG_SHA_INPUT_DB();

        ucIndex += 4;
    }
    while(ucIndex < 17);

    // 11. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(g_pucDpMacTxHdcpDownStreamV[17]);
    SET_DP_MST_TX_REG_SHA_INPUT_1(g_pucDpMacTxHdcpDownStreamV[18]);
    SET_DP_MST_TX_REG_SHA_INPUT_2(g_pucDpMacTxHdcpDownStreamV[19]);
    SET_DP_MST_TX_REG_SHA_INPUT_3(GET_DP_MST_TX_HDCP_M0_0());

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    // 12. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(GET_DP_MST_TX_HDCP_M0_1());
    SET_DP_MST_TX_REG_SHA_INPUT_1(GET_DP_MST_TX_HDCP_M0_2());
    SET_DP_MST_TX_REG_SHA_INPUT_2(GET_DP_MST_TX_HDCP_M0_3());
    SET_DP_MST_TX_REG_SHA_INPUT_3(GET_DP_MST_TX_HDCP_M0_4());

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    // 13. Write Data into SHA-1 Transform Input
    SET_DP_MST_TX_REG_SHA_INPUT_0(GET_DP_MST_TX_HDCP_M0_5());
    SET_DP_MST_TX_REG_SHA_INPUT_1(GET_DP_MST_TX_HDCP_M0_6());
    SET_DP_MST_TX_REG_SHA_INPUT_2(GET_DP_MST_TX_HDCP_M0_7());
    SET_DP_MST_TX_REG_SHA_INPUT_3(0x80);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    for(ucIndex = 14; ucIndex < 16; ucIndex++)
    {
        // 14~15. Write 0x00 into the remaining SHA-1 Transform Input space
        SET_DP_MST_TX_REG_SHA_INPUT_0(0x00);
        SET_DP_MST_TX_REG_SHA_INPUT_1(0x00);
        SET_DP_MST_TX_REG_SHA_INPUT_2(0x00);
        SET_DP_MST_TX_REG_SHA_INPUT_3(0x00);

        // Enable write 32-bit data to SHA-1 block
        SET_DP_MST_TX_REG_SHA_INPUT_DB();
    }

    // 16. Write 0x00 into the remaining SHA-1 Transform Input space
    SET_DP_MST_TX_REG_SHA_INPUT_0(0x00);
    SET_DP_MST_TX_REG_SHA_INPUT_1(0x00);
    SET_DP_MST_TX_REG_SHA_INPUT_2(0x01);
    SET_DP_MST_TX_REG_SHA_INPUT_3(0x98);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_TX_REG_SHA_INPUT_DB();

    ScalerDpHdcp14TxAuth2ShaRun(_TRUE);
}

//--------------------------------------------------
// Description  : Get DP TX SHA-1 Input Result
// Input Value  : Index
// Output Value : V
//--------------------------------------------------
BYTE ScalerDpMstTxQueryEncryptionGetShaResult(BYTE ucIndex)
{
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), ((4 - (ucIndex / 4)) << 5));

    return ScalerGetByte(PBB_60_DP_HDCP_TX_SHA_OUT_3 + (ucIndex % 4));
}

//--------------------------------------------------
// Description  : Compare SHA-1 Input Result L with L'
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
bit ScalerDpMstTxQueryEncryptionCompareShaResult(void)
{
    BYTE ucCnt = 0;

    for(ucCnt = 0; ucCnt < 20; ucCnt++)
    {
        // MSB first
        if(ScalerDpMstTxQueryEncryptionGetShaResult(ucCnt) != GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(ucCnt))
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get HDCP TX Encrypt Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxGetHdcpEncryptEnable(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        return (ScalerGetBit(P2B_48_DPTX_HDCP_CTRL1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0));
    }
    else
#endif
    {
        return (ScalerGetBit(PBB_30_DPTX_HDCP_CTRL1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0));
    }
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : L' = SHA-256(Stream-Status | Q_id | S_id | Riv | Receiver_ID | V' | (Qid | Qid | Qid))
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxQueryEncryptionWriteSha256Input(bit bRepeater)
{
    BYTE pucHmacSha256Input[64] = {0};
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    BYTE ucIndex = 0;

    // Load Stream-Status (16-Bits)
    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        pucHmacSha256Input[ucIndex] = g_unDpMstRxReplyPool.pucData[ucIndex + 1];
    }

    // Load Q_id (56-bits)
    for(ucIndex = 0; ucIndex < 7; ucIndex++)
    {
        pucHmacSha256Input[ucIndex + 2] = g_pucDpMstRxMsgQueryEncryptClientId[ucIndex];
    }

    // Load S_id (8-bits)
    pucHmacSha256Input[9] = GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID();

    // Load Riv (64-bits)
    memcpy(&pucHmacSha256Input[10], g_pucDpHdcp2TxRiv, sizeof(g_pucDpHdcp2TxRiv));

    // Load Receiver ID of DSP (40-bits)
    for(ucIndex = 0; ucIndex < 5; ucIndex++)
    {
        pucHmacSha256Input[ucIndex + 18] = g_pucDpHdcp2TxReceiverId[ucIndex];
    }

    if(bRepeater == _TRUE)
    {
        // Load Link_S (160-bits) = V'
        for(ucIndex = 0; ucIndex < 20; ucIndex++)
        {
            pucHmacSha256Input[ucIndex + 23] = g_pucDpHdcp2TxDownStreamV[ucIndex];
        }
    }
    else
    {
        // Load Link_S (160-bits) = (Qid | Qid | Qid[47:0])
        for(ucIndex = 0; ucIndex < 3; ucIndex++)
        {
            if(ucIndex == 2)
            {
                for(BYTE ucIndex2 = 0; ucIndex2 < 6; ucIndex2++)
                {
                    pucHmacSha256Input[((ucIndex * 7) + ucIndex2) + 23] = g_pucDpMstRxMsgQueryEncryptClientId[ucIndex2];
                }
            }
            else
            {
                for(BYTE ucIndex2 = 0; ucIndex2 < 7; ucIndex2++)
                {
                    pucHmacSha256Input[((ucIndex * 7) + ucIndex2) + 23] = g_pucDpMstRxMsgQueryEncryptClientId[ucIndex2];
                }
            }
        }
    }

    // Load (Q_id | Q_id | Q_id) (168-bits)
    for(ucIndex = 0; ucIndex < 3; ucIndex++)
    {
        for(BYTE ucIndex2 = 0; ucIndex2 < 7; ucIndex2++)
        {
            pucHmacSha256Input[((ucIndex * 7) + ucIndex2) + 43] = g_pucDpMstRxMsgQueryEncryptClientId[ucIndex2];
        }
    }

    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2TxdKey0);
    ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2TxdKey1);

    ScalerHdcp2RepeaterLPrimeCalculate(pucTemp1, pucTemp2, pucHmacSha256Input);
}

//--------------------------------------------------
// Description  : Compare SHA-256 Input Result L with L'
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
bit ScalerDpMstTxQueryEncryptionCompareSha256Result(void)
{
    BYTE ucCnt = 0;

    for(ucCnt = 0; ucCnt < 32; ucCnt++)
    {
        // MSB first
        if(GET_DP_MST_RX_REG_HDCP_SHA256_RESULT(ucCnt) != GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(ucCnt))
        {
            return _FALSE;
        }
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Header Info. BackUp
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpMstTxDownReplyHeaderBackUp(StructTxDownReplyMsgInterleaveHeaderInfo *pstTxDownReplyMsgHeaderInfo)
{
    pstTxDownReplyMsgHeaderInfo->b4MsgLct = GET_DP_MST_TX_REG_UPSTREAM_MSG_LCT();
    pstTxDownReplyMsgHeaderInfo->b4MsgLcr = GET_DP_MST_TX_REG_UPSTREAM_MSG_LCR();

    for(BYTE ucRadIndex = 0; ucRadIndex < (pstTxDownReplyMsgHeaderInfo->b4MsgLct - 1); ucRadIndex++)
    {
        pstTxDownReplyMsgHeaderInfo->pucMsgRad[ucRadIndex] = ScalerDpMstTxGetRegUpstreamMsgRad(ucRadIndex);
    }

    pstTxDownReplyMsgHeaderInfo->b1MsgBroadcast = GET_DP_MST_TX_REG_UPSTREAM_MSG_BROADCAST();
    pstTxDownReplyMsgHeaderInfo->b1MsgPath = GET_DP_MST_TX_REG_UPSTREAM_MSG_PATH();
    pstTxDownReplyMsgHeaderInfo->b1MsgMsn = GET_DP_MST_TX_REG_UPSTREAM_MSG_MSN();
}

//--------------------------------------------------
// Description  : Check SBMSG Header Info. Consistent
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
bit ScalerDpMstTxDownReplySidebandMsgHeaderCheck(StructTxDownReplyMsgInterleaveHeaderInfo stTxDownReplyMsgHeaderInfo)
{
    if(stTxDownReplyMsgHeaderInfo.b4MsgLct != GET_DP_MST_TX_REG_UPSTREAM_MSG_LCT())
    {
        return _FALSE;
    }

    if(stTxDownReplyMsgHeaderInfo.b4MsgLcr != GET_DP_MST_TX_REG_UPSTREAM_MSG_LCR())
    {
        return _FALSE;
    }

    if(stTxDownReplyMsgHeaderInfo.b1MsgBroadcast != GET_DP_MST_TX_REG_UPSTREAM_MSG_BROADCAST())
    {
        return _FALSE;
    }

    if(stTxDownReplyMsgHeaderInfo.b1MsgPath != GET_DP_MST_TX_REG_UPSTREAM_MSG_PATH())
    {
        return _FALSE;
    }

    if(stTxDownReplyMsgHeaderInfo.b1MsgMsn != GET_DP_MST_TX_REG_UPSTREAM_MSG_MSN())
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Down Reply SBMSG Interleave Proc
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpMstTxDownReplySideBandMsgProc(void)
{
    BYTE ucIndex = 0;

    if((GET_DP_MST_TX_REG_UPSTREAM_SBMSG_START_OF_BIT() == _TRUE) && (GET_DP_MST_TX_REG_UPSTREM_MSG_HEADER_CRC_STATUS() == _TRUE))
    {
        if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() == 0)
        {
            // BacKup Interleave0 Header
            ScalerDpMstTxDownReplyHeaderBackUp(&g_stDpMstTxMsgBackupHeaderInfo0);
        }
        else if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH() == 0)
        {
            // BacKup Interleave1 Header
            ScalerDpMstTxDownReplyHeaderBackUp(&g_stDpMstTxMsgBackupHeaderInfo1);

            // Set SBMSG Interleave Flag
            SET_DP_MST_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE();
        }

        SET_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT(GET_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT() + 1);
    }

    if(ScalerDpMstTxDownReplySidebandMsgHeaderCheck(g_stDpMstTxMsgBackupHeaderInfo0) == _TRUE)
    {
        // Get Interleave0 Data
        SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_PTR(0x00);

        for(ucIndex = 0; ucIndex < Scaler32GetByte(PB18083_AC_BUF_FW_WRPTR, _REG8TO32_BYTE_0); ucIndex++)
        {
            SET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH(), GET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DATA());

            SET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() + 1);
        }

        if(GET_DP_MST_TX_REG_UPSTREAM_SBMSG_END_OF_BIT() == _TRUE)
        {
            SET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH();

            SET_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT(GET_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT() + 1);
        }

        if(GET_DP_MST_TX_REG_UPSTREM_MSG_CRC_STATUS() == _FALSE)
        {
            SET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE();
        }

        // Buf_CLR=1 WR_PTR = 0x00
        CLR_DP_MST_TX_REG_UPSTREAM_MSG_BUF();
    }
    else if(ScalerDpMstTxDownReplySidebandMsgHeaderCheck(g_stDpMstTxMsgBackupHeaderInfo1) == _TRUE)
    {
        SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_PTR(0x00);

        for(ucIndex = 0; ucIndex < Scaler32GetByte(PB18083_AC_BUF_FW_WRPTR, _REG8TO32_BYTE_0); ucIndex++)
        {
            SET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH(), GET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DATA());

            SET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH() + 1);
        }

        if(GET_DP_MST_TX_REG_UPSTREAM_SBMSG_END_OF_BIT() == _TRUE)
        {
            SET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH();

            SET_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT(GET_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT() + 1);
        }

        if(GET_DP_MST_TX_REG_UPSTREM_MSG_CRC_STATUS() == _FALSE)
        {
            SET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE();
        }

        // Buf_CLR=1 WR_PTR = 0x00
        CLR_DP_MST_TX_REG_UPSTREAM_MSG_BUF();
    }

    if(((GET_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT() == 1) && (GET_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT() == 1)) ||
       ((GET_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT() == 2) && (GET_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT() == 2)))
    {
        // CLR Start/End Of Bit Count
        CLR_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT();
        CLR_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT();

        // Disable Tx DownReply Read
        SET_DP_MST_TX_DOWN_REPLY_READ_DISABLE();
    }
}

//--------------------------------------------------
// Description  : Down Reply Interleave Finish Check
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpMstTxDownReplyInterleaveFinishCheck(void)
{
    if(GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH();

        CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH();
    }
    else
    {
        CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH();

        CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH();
    }

    if((GET_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() == 0) && (GET_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH() == 0))
    {
        // CLR SBMSG Interleave Flag
        CLR_DP_MST_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE();

        // TX Read Enable
        CLR_DP_MST_TX_DOWN_REPLY_READ_DISABLE();
    }
}

//--------------------------------------------------
// Description  : Clear Down Reply Interleave Flag
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpMstTxClrDownReplyInterleaveFlag(void)
{
    CLR_DP_MST_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE();
    g_stDpMstTxMsgBackupHeaderInfo0.b4MsgLct = 0;
    g_stDpMstTxMsgBackupHeaderInfo1.b4MsgLct = 0;
}

//--------------------------------------------------
// Description  : DP MST Link Clock Enable or Disable
// Input Value  : bEn  --> _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxLinkClockEn(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable DP Tx Link Clock
        ScalerSetBit(PA_03_MST2SST_CLK_GATE, ~_BIT6, _BIT6);
    }
    else
    {
        // Disable DP Tx Link Clock for Power Saving Mode
        ScalerSetBit(PA_03_MST2SST_CLK_GATE, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get DP MST Tx Port Plug Status Reported
// Input Value  : EnumOutputPort enumOutputPort
// Output Value : _DP_PLUG / _DP_UNPLUG
//--------------------------------------------------
EnumDpMstTxConnectStatus ScalerDpMstTxGetOutputPortStatusReported(void)
{
    return g_penumDpMstTxOutputPortStatusReported[0];
}

//--------------------------------------------------
// Description  : Set DP MST Tx Port Plug Status Reported
// Input Value  : EnumDpMstTxPxPortConnectStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSetOutputPortStatusReported(EnumDpMstTxConnectStatus enumPlugStatus)
{
    DebugMessageMst("Report Tx port is plug/unplug", (enumPlugStatus == _CONNECT_STATUS_PLUG));

    if(enumPlugStatus == _CONNECT_STATUS_UNPLUG)
    {
        CLR_DP_MST_TX_MSG_DURING_HPD_LOW_DEBOUNCE();
    }

    g_penumDpMstTxOutputPortStatusReported[0] = enumPlugStatus;
}

//--------------------------------------------------
// Description  : DP Tx Get CSN event status
// Input Value  : EnumDpMstTxUpReqQueue
// Output Value : _DP_UNPLUG / _DP_PLUG
//--------------------------------------------------
EnumDpMstTxConnectStatus ScalerDpMstTxCsnEventGetStatus(EnumDpMstTxUpReqQueue enumCsnQueue)
{
    if(enumCsnQueue == _TX_UP_REQ_QUEUE_NONE)
    {
        return _CONNECT_STATUS_NONE;
    }

    if(enumCsnQueue == _TX_UP_REQ_QUEUE_BYPASS)
    {
        if(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCR(_CSN_QUEUE_ENTRY_0) > 0)
        {
            if(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_DP_PLUG_STATUS(_CSN_QUEUE_ENTRY_0) == _DP_PLUG)
            {
                return _CONNECT_STATUS_PLUG;
            }
            else
            {
                return _CONNECT_STATUS_UNPLUG;
            }
        }
    }
    else
    {
        return GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_0);
    }

    return _CONNECT_STATUS_NONE;
}

//--------------------------------------------------
// Description  : DP Tx Delete CSN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxCsnEventDelete(EnumDpMstTxUpReqQueue enumCsnQueue)
{
    if(enumCsnQueue == _TX_UP_REQ_QUEUE_NONE)
    {
        return;
    }

    if(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE() == enumCsnQueue)
    {
        if(enumCsnQueue == _TX_UP_REQ_QUEUE_BYPASS)
        {
            ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());
        }
        else
        {
            ScalerDpRxSetBaseInputPort(GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_0));
        }

        if(GET_DP_MST_RX_UP_REQUEST_ISSUED_ID() == _DP_MSG_CONNECTION_STATUS_NOTIFY)
        {
            CLR_DP_MST_RX_UP_REQUEST_PROCESSING();

            if((GET_DP_MST_RX_UP_REQUEST_ANAL() == _TRUE) || (GET_DP_MST_RX_UP_REQUEST_READY() == _TRUE))
            {
                SET_DP_MST_RX_REQUEST_POOL_FREE();

                SET_DP_MST_RX_REPLY_BUF_FREE();
            }

            CLR_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE();

            CLR_DP_MST_RX_UP_REQUEST_ISSUED_ID();

            CLR_DP_MST_TX_GEN_UP_REQUEST_MSG();

            CLR_DP_MST_RX_UP_REQUEST_BYPASS_DONE();

            CLR_DP_MST_RX_UP_REQUEST_RETRY_NUM();

            CLR_DP_MST_RX_UP_REQUEST_ANAL();

            CLR_DP_MST_RX_UP_REQUEST_READY();

            // Cancel TimerEvent as CSN Has Been Delete
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_FORCE_REBUILD_TOPOLOGY_EVENT);
        }
    }

    // Delete & Shift Item
    if(enumCsnQueue == _TX_UP_REQ_QUEUE_BYPASS)
    {
        if(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCR(_CSN_QUEUE_ENTRY_1) == 0x00)
        {
            CLR_DP_MST_TX_BYPASS_CSN_BACKUP(_CSN_QUEUE_ENTRY_0);
        }
        else
        {
            SET_DP_MST_TX_BYPASS_CSN_BACKUP(_CSN_QUEUE_ENTRY_0, GET_DP_MST_TX_BYPASS_CSN_BACKUP(_CSN_QUEUE_ENTRY_1));

            CLR_DP_MST_TX_BYPASS_CSN_BACKUP(_CSN_QUEUE_ENTRY_1);
        }
    }
    else
    {
        if(GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_1) == _CONNECT_STATUS_NONE)
        {
            CLR_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_0);
        }
        else
        {
            SET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_0, GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_1));
            SET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_0, GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_1));

            CLR_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_1);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Delete CSN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxCsnEventClearQueue(EnumDpMstTxUpReqQueue enumCsnQueue)
{
    EnumDpMstTxCsnQueueEntry enumEntry = _CSN_QUEUE_ENTRY_0;

    for(enumEntry = _CSN_QUEUE_ENTRY_0; enumEntry < _CSN_QUEUE_ENTRY_NUM; enumEntry++)
    {
        ScalerDpMstTxCsnEventDelete(enumCsnQueue);
    }
}

//--------------------------------------------------
// Description  : DP Tx CSN event reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxCsnEventReset(void)
{
    EnumDpMstTxUpReqQueue enumCsnQueue = _TX_UP_REQ_QUEUE_SELF_GEN;

    for(enumCsnQueue = _TX_UP_REQ_QUEUE_SELF_GEN; enumCsnQueue < _TX_UP_REQ_QUEUE_NONE; enumCsnQueue++)
    {
        ScalerDpMstTxCsnEventClearQueue(enumCsnQueue);
    }
}

//--------------------------------------------------
// Description  : DP Tx Check CSN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumDpMstTxUpReqQueue ScalerDpMstTxCsnEventCheck(void)
{
    // Check Tx Queue
    if(ScalerDpMstTxCsnEventGetStatus(_TX_UP_REQ_QUEUE_SELF_GEN) != _CONNECT_STATUS_NONE)
    {
        EnumInputPort enumInputPort = GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_0);

        if((ScalerDpRxGetSrcMstUpRequestEnable(enumInputPort) == _TRUE) &&
           (ScalerDpMstTxCsnEventGetStatus(_TX_UP_REQ_QUEUE_SELF_GEN) != ScalerDpMstTxGetOutputPortStatusReported()))
        {
            if(ScalerDpMstRxUpRequestAllowedCheck(enumInputPort) == _TRUE)
            {
                return _TX_UP_REQ_QUEUE_SELF_GEN;
            }
        }
        else
        {
            ScalerDpMstTxCsnEventDelete(_TX_UP_REQ_QUEUE_SELF_GEN);
        }
    }

    // Check Bypass Queue
    if(ScalerDpMstTxCsnEventGetStatus(_TX_UP_REQ_QUEUE_BYPASS) != _CONNECT_STATUS_NONE)
    {
        if(ScalerDpRxGetSrcMstUpRequestEnable(GET_DP_RX_MAIN_PORT()) == _TRUE)
        {
            if(ScalerDpMstRxUpRequestAllowedCheck(GET_DP_RX_MAIN_PORT()) == _TRUE)
            {
                return _TX_UP_REQ_QUEUE_BYPASS;
            }
        }
        else
        {
            ScalerDpMstTxCsnEventDelete(_TX_UP_REQ_QUEUE_BYPASS);
        }
    }

    return _TX_UP_REQ_QUEUE_NONE;
}

//--------------------------------------------------
// Description  : DP Tx Sink Count Update by CSN Event
// Input Value  : EnumDpMstTxUpReqQueue
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxCsnEventSinkCountUpdate(EnumDpMstTxUpReqQueue enumCsnQueue)
{
    BYTE ucSinkCount = (GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT() + 1);
    EnumInputPort enumInputport = _NO_INPUT_PORT;

    if(enumCsnQueue == _TX_UP_REQ_QUEUE_NONE)
    {
        return;
    }

    // Sink Count Change Proccess
    if(enumCsnQueue == _TX_UP_REQ_QUEUE_BYPASS)
    {
        enumInputport = GET_DP_RX_MAIN_PORT();

        SET_DP_MAC_TX_DOWNSTREAM_PRE_SINK_COUNT(GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT());
    }
    else
    {
        enumInputport = GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_0);

        if(ScalerDpMstTxCsnEventGetStatus(enumCsnQueue) == _CONNECT_STATUS_UNPLUG)
        {
            ucSinkCount = 1;
        }
    }

    DebugMessageMst("sink count change to", ucSinkCount);

    // Update Sink Count
    ScalerDpAuxRxSinkCountUpdate(enumInputport, ucSinkCount, _FALSE);
}

//--------------------------------------------------
// Description  : DP Tx Check CSN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstTxCsnTransmitDoneCheck(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

    if(GET_DP_MST_RX_UP_REQUEST_PROCESSING() == _FALSE)
    {
        return _TRUE;
    }

    if(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE() == _TX_UP_REQ_QUEUE_BYPASS)
    {
        return _TRUE;
    }

    if(ScalerDpMstTxCsnEventGetStatus(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE()) == _CONNECT_STATUS_PLUG)
    {
        return _TRUE;
    }

    if(GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_0) != GET_DP_RX_MAIN_PORT())
    {
        return _TRUE;
    }

    // Px unplug case should wait for Allocate MSG which PBN = 0 or 2s timeout
    // Mark For INTEL UHD 630 fail to handle intensive and multiple port CSN MSGs. Wait 2s after unplug CSN solves this issue.
    // if(ScalerDpMstTxGetStreamAllocate() == _FALSE)
    // {
    // return _TRUE;
    // }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Up Request Event Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxUpRequestEventCheck(void)
{
    EnumDpMstTxUpReqQueue enumDpMstTxUpReqQueueTemp = _TX_UP_REQ_QUEUE_NONE;

    // Check if there is CSN to be sent
    if((enumDpMstTxUpReqQueueTemp = ScalerDpMstTxCsnEventCheck()) != _TX_UP_REQ_QUEUE_NONE)
    {
        SET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE(enumDpMstTxUpReqQueueTemp);

        // Update sink count then clear the value of the csn event
        ScalerDpMstTxCsnEventSinkCountUpdate(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE());

        // Initiate Connection Status Notify
        SET_DP_MST_TX_GEN_UP_REQUEST_MSG(_DP_MSG_CONNECTION_STATUS_NOTIFY);

        if(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE() == _TX_UP_REQ_QUEUE_SELF_GEN)
        {
            ScalerDpMstTxCsnEventClearQueue(_TX_UP_REQ_QUEUE_BYPASS);
            ScalerDpMstTxSenEventClearQueue(_TX_UP_REQ_QUEUE_SELF_GEN);
            ScalerDpMstTxSenEventClearQueue(_TX_UP_REQ_QUEUE_BYPASS);

            SET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_0));
        }
        else
        {
            SET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(GET_DP_RX_MAIN_PORT());
        }
    }

    // Check if there is SEN to be sent
    if((enumDpMstTxUpReqQueueTemp = ScalerDpMstTxSenEventCheck()) != _TX_UP_REQ_QUEUE_NONE)
    {
        DebugMessageMst("Tx SEN Gen!!!", enumDpMstTxUpReqQueueTemp);

        SET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE(enumDpMstTxUpReqQueueTemp);

        // Initiate Sink Event Notify
        SET_DP_MST_TX_GEN_UP_REQUEST_MSG(_DP_MSG_SINK_EVENT_NOTIFY);

        SET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(GET_DP_RX_MAIN_PORT());
    }
}

//--------------------------------------------------
// Description  : Set Tx CSN Event
// Input Value  : None
// Output Value : EnumDpMstTxConnectStatus
//--------------------------------------------------
void ScalerDpMstTxSetCsnEvent(EnumInputPort enumTargetInputPort, EnumDpMstTxConnectStatus enumCsnEvent)
{
    if(enumTargetInputPort == _NO_INPUT_PORT)
    {
        return;
    }

    if(enumCsnEvent == _CONNECT_STATUS_UNPLUG)
    {
        ScalerDpMstTxCsnEventClearQueue(_TX_UP_REQ_QUEUE_SELF_GEN);
    }

    if(GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_0) == _CONNECT_STATUS_NONE)
    {
        SET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_0, enumCsnEvent);
        SET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_0, enumTargetInputPort);
    }
    else
    {
        SET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_1, enumCsnEvent);
        SET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_1, enumTargetInputPort);
    }
}

//--------------------------------------------------
// Description  : Get If Tx Port Stream Is Allocated
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpMstTxGetStreamAllocate(void)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_NO_SOURCE;

    // MST to SST case
    if(ScalerDpMacTxGetDaisySourceMuxBackup(_DP_ST_SOURCE1) != _DP_ST_NONE)
    {
        return _TRUE;
    }

    // MST to MST case
    for(enumSourceNum = _DP_ST_SOURCE_DAISY_START; enumSourceNum <= _DP_ST_SOURCE_DAISY_END; enumSourceNum++)
    {
        if(ScalerDpMacTxGetDaisySourceMuxBackup(enumSourceNum) != _DP_ST_NONE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Tx MST2SST Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxMst2SstInitialSetting(void)
{
    // Reset MST Enable
    ScalerSetBit(PA_02_MST2SST_CONFIG, ~_BIT7, _BIT7);

    // Swtich MST2SST Lane Num
    ScalerDpMstTxSetMst2SstLaneNum();
}

//--------------------------------------------------
// Description  : Switch Tx MST2SST Stream Source Lane Num
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSetMst2SstLaneNum(void)
{
    if(GET_DP_RX_MAIN_PORT() != _NO_INPUT_PORT)
    {
        // Swtich MST2SST Lane Num
        switch(ScalerDpAuxRxGetDpcdBitInfo(GET_DP_RX_MAIN_PORT(), 0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)))
        {
            case _DP_ONE_LANE:

                ScalerSetBit(PA_02_MST2SST_CONFIG, ~(_BIT4 | _BIT3), _BIT3);

                break;

            case _DP_TWO_LANE:

                ScalerSetBit(PA_02_MST2SST_CONFIG, ~(_BIT4 | _BIT3), _BIT4);

                break;

            default:
            case _DP_FOUR_LANE:

                ScalerSetBit(PA_02_MST2SST_CONFIG, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

                break;
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Delete SEN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSenEventDelete(EnumDpMstTxUpReqQueue enumSenQueue)
{
    if(enumSenQueue == _TX_UP_REQ_QUEUE_NONE)
    {
        return;
    }

    if(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE() == enumSenQueue)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

        if(GET_DP_MST_RX_UP_REQUEST_ISSUED_ID() == _DP_MSG_SINK_EVENT_NOTIFY)
        {
            CLR_DP_MST_RX_UP_REQUEST_PROCESSING();

            if(enumSenQueue == _TX_UP_REQ_QUEUE_SELF_GEN)
            {
                CLR_DP_MST_TX_SINK_EVENT_ID(GET_DP_MST_RX_UP_REQUEST_ISSUED_SINK_EVENT_ID());
            }

            if((GET_DP_MST_RX_UP_REQUEST_ANAL() == _TRUE) || (GET_DP_MST_RX_UP_REQUEST_READY() == _TRUE))
            {
                SET_DP_MST_RX_REQUEST_POOL_FREE();

                SET_DP_MST_RX_REPLY_BUF_FREE();
            }

            CLR_DP_MST_RX_UP_REQUEST_ISSUED_SINK_EVENT_ID();

            CLR_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE();

            CLR_DP_MST_RX_UP_REQUEST_ISSUED_ID();

            CLR_DP_MST_TX_GEN_UP_REQUEST_MSG();

            CLR_DP_MST_RX_UP_REQUEST_BYPASS_DONE();

            CLR_DP_MST_RX_UP_REQUEST_RETRY_NUM();

            CLR_DP_MST_RX_UP_REQUEST_ANAL();

            CLR_DP_MST_RX_UP_REQUEST_READY();
        }
    }
    else
    {
        // For reset case
        if(enumSenQueue == _TX_UP_REQ_QUEUE_SELF_GEN)
        {
            CLR_DP_MST_TX_SINK_EVENT_ID(_SINK_EVENT_ALL);
        }
    }

    // Delete & Shift Item
    if(enumSenQueue == _TX_UP_REQ_QUEUE_BYPASS)
    {
        EnumDpMstTxSenQueueEntry enumEntry = _SEN_QUEUE_ENTRY_0;

        for(enumEntry = _SEN_QUEUE_ENTRY_0; enumEntry < (_SEN_QUEUE_ENTRY_NUM - 1); enumEntry ++)
        {
            if(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_EVENT_ID(enumEntry) == 0x00)
            {
                break;
            }

            SET_DP_MST_TX_BYPASS_SEN_BACKUP(enumEntry, GET_DP_MST_TX_BYPASS_SEN_BACKUP(enumEntry + 1));

            CLR_DP_MST_TX_BYPASS_SEN_BACKUP(enumEntry + 1);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Check SEN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumDpMstTxUpReqQueue ScalerDpMstTxSenEventCheck(void)
{
    // Check Tx Queue
    if(GET_DP_MST_TX_SINK_EVENT_ID() != _SINK_EVENT_NONE)
    {
        if(ScalerDpRxGetSrcMstUpRequestEnable(GET_DP_RX_MAIN_PORT()) == _TRUE)
        {
            if(ScalerDpMstRxUpRequestAllowedCheck(GET_DP_RX_MAIN_PORT()) == _TRUE)
            {
                return _TX_UP_REQ_QUEUE_SELF_GEN;
            }
        }
        else
        {
            CLR_DP_MST_TX_SINK_EVENT_ID(_SINK_EVENT_ALL);
        }
    }

    // Check Bypass Queue
    if(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_EVENT_ID(_SEN_QUEUE_ENTRY_0) != _SINK_EVENT_NONE)
    {
        if(ScalerDpRxGetSrcMstUpRequestEnable(GET_DP_RX_MAIN_PORT()) == _TRUE)
        {
            if(ScalerDpMstRxUpRequestAllowedCheck(GET_DP_RX_MAIN_PORT()) == _TRUE)
            {
                return _TX_UP_REQ_QUEUE_BYPASS;
            }
        }
        else
        {
            CLR_DP_MST_TX_BYPASS_SEN_BACKUP(_SEN_QUEUE_ENTRY_0);
        }
    }

    return _TX_UP_REQ_QUEUE_NONE;
}

//--------------------------------------------------
// Description  : DP Tx Delete SEN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSenEventClearQueue(EnumDpMstTxUpReqQueue enumSenQueue)
{
    EnumDpMstTxSenQueueEntry enumEntry = _SEN_QUEUE_ENTRY_0;

    if(enumSenQueue == _TX_UP_REQ_QUEUE_BYPASS)
    {
        for(enumEntry = _SEN_QUEUE_ENTRY_0; enumEntry < _SEN_QUEUE_ENTRY_NUM; enumEntry++)
        {
            ScalerDpMstTxSenEventDelete(enumSenQueue);
        }
    }
    else
    {
        ScalerDpMstTxSenEventDelete(enumSenQueue);
    }
}

//--------------------------------------------------
// Description  : DP Tx CSN event reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSenEventReset(void)
{
    EnumDpMstTxUpReqQueue enumSenQueue = _TX_UP_REQ_QUEUE_SELF_GEN;

    for(enumSenQueue = _TX_UP_REQ_QUEUE_SELF_GEN; enumSenQueue < _TX_UP_REQ_QUEUE_NONE; enumSenQueue++)
    {
        ScalerDpMstTxSenEventClearQueue(enumSenQueue);
    }
}

//--------------------------------------------------
// Description  : ScalerDpMstTxDownRequestProc
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMstTxDownRequestProc(void)
{
    bit bDone = _TRUE;

    bDone &= ScalerDpMstTxDownRequestAnal();

    bDone &= ScalerDpMstTxDownRequestEventProc();

    bDone &= ScalerDpMstTxDownRequestAnalDone();

    bDone &= ScalerDpMstTxDownRequestSend();

    bDone &= ScalerDpMstTxDownRequestDone();

    return bDone;
}

//--------------------------------------------------
// Description  : ScalerDpMstTxDownReplyProc
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMstTxDownReplyProc(void)
{
    bit bDone = _TRUE;

    bDone &= ScalerDpMstTxDownReplyReceive();

    bDone &= ScalerDpMstTxDownReplyAnal();

    bDone &= ScalerDpMstTxDownReplyEventProc();

    bDone &= ScalerDpMstTxDownReplyAnalDone();

    return bDone;
}

//--------------------------------------------------
// Description  : ScalerDpMstTxUpRequestProc
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMstTxUpRequestProc(void)
{
    bit bDone = _TRUE;

    bDone &= ScalerDpMstTxUpRequestReceive();

    bDone &= ScalerDpMstTxUpRequestAnal();

    return bDone;
}

//--------------------------------------------------
// Description  : ScalerDpMstTxUpReplyProc
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMstTxUpReplyProc(void)
{
    bit bDone = _TRUE;

    bDone &= ScalerDpMstTxUpReplyAnal();

    bDone &= ScalerDpMstTxUpReplySend();

    bDone &= ScalerDpMstTxUpReplyDone();

    return bDone;
}

//--------------------------------------------------
// Description  : Set Tx Daisy from D0 = 00, D1 = 01, D2 = 10 or 11
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSetDaisyInputPortMux(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            ScalerSetBit(P6F_04_MUX_DPRX_OUT, ~(_BIT5 | _BIT4), 0x00 << 4);
            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerSetBit(P6F_04_MUX_DPRX_OUT, ~(_BIT5 | _BIT4), 0x01 << 4);
            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            ScalerSetBit(P6F_04_MUX_DPRX_OUT, ~(_BIT5 | _BIT4), 0x02 << 4);
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Calculate Tx Full PBN
// Input Value  : None
// Output Value : Full PBN
//--------------------------------------------------
WORD ScalerDpMstTxGetFullPBN(void)
{
    WORD usTxFullPbn = 0;
    BYTE ucTimeSlot = 0;

#if(_DP_MST_ENUM_PATH_RESOURCE_REPLY_IGNORE_RX_BW == _OFF)
    WORD usRxFullPbn = 0;
    EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();

    ScalerDpRxSetBaseInputPort(enumInputPort);

    // Rx - Set RxPBN to max PBN if LT is not ready
    if(GET_DP_MST_RX_LT_STATUS_CHCEK() == _FALSE)
    {
        usRxFullPbn = ScalerDpMstRxGetMaxPBN(enumInputPort);
    }
    else
    {
        // Rx - Compute full pbn
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
        {
            ucTimeSlot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM;
        }
        else
#endif
        {
            ucTimeSlot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM - 1;
        }

        usRxFullPbn = ScalerDpMacDphyRxGetPBN(ScalerDpAuxRxGetLinkRate(enumInputPort), ScalerDpAuxRxGetLaneCount(enumInputPort), ucTimeSlot);
    }
#endif

    // Tx - Compute full pbn
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        ucTimeSlot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM;
    }
    else
#endif
    {
        ucTimeSlot = (_DP_MST_RX_TOTAL_TIME_SLOT_NUM - ((GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT) ? 1 : 0));
    }

    usTxFullPbn = ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucTimeSlot);

    // Return PBN Value
    if(usTxFullPbn != 0)
    {
#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_FEC_SUPPORT == _ON))
        usTxFullPbn = ScalerDpMstTxJudgePbnConversion(usTxFullPbn, _DP_MSG_ENUM_PATH_RESOURCES);
#endif

#if(_DP_MST_ENUM_PATH_RESOURCE_REPLY_IGNORE_RX_BW == _OFF)
        return ((usRxFullPbn < usTxFullPbn) ? usRxFullPbn : usTxFullPbn);
#else
        return usTxFullPbn;
#endif
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Calculate Current Tx Available PBN
// Input Value  : None
// Output Value : Available PBN
//--------------------------------------------------
WORD ScalerDpMstTxGetAvailablePBN(void)
{
    BYTE ucAvailableTimeSlot = 0;
    WORD usTxAvlPBN = 0;
    EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();

    ScalerDpRxSetBaseInputPort(enumInputPort);

#if(_DP_MST_ENUM_PATH_RESOURCE_REPLY_IGNORE_RX_BW == _OFF)
    WORD usRxAvlPBN = 0;
    // RX - Get Remain PBN
    // Rx - Set to max PBN if LT is not ready
    if(GET_DP_MST_RX_LT_STATUS_CHCEK() == _FALSE)
    {
        usRxAvlPBN = ScalerDpMstRxGetMaxPBN(enumInputPort);
    }
    else
    {
        ucAvailableTimeSlot = ScalerDpMstRxGetAvailableTimeslot(enumInputPort);
        usRxAvlPBN = ScalerDpMacDphyRxGetPBN(ScalerDpAuxRxGetLinkRate(enumInputPort), ScalerDpAuxRxGetLaneCount(enumInputPort), ucAvailableTimeSlot);
    }
#endif

    // Tx - Calculate Remain PBN
    ucAvailableTimeSlot = ScalerDpMstTxGetAvailableTimeslot();
    usTxAvlPBN = ScalerDpMacDphyRxGetPBN(GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(), GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(), ucAvailableTimeSlot);

    if(usTxAvlPBN != 0)
    {
#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_FEC_SUPPORT == _ON))
        usTxAvlPBN = ScalerDpMstTxJudgePbnConversion(usTxAvlPBN, _DP_MSG_ENUM_PATH_RESOURCES);
#endif

#if(_DP_MST_ENUM_PATH_RESOURCE_REPLY_IGNORE_RX_BW == _OFF)
        return ((usRxAvlPBN < usTxAvlPBN) ? usRxAvlPBN : usTxAvlPBN);
#else
        return usTxAvlPBN;
#endif
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Calculate Available Timeslot
// Input Value  : None
// Output Value : ucTimeslot
//--------------------------------------------------
BYTE ScalerDpMstTxGetAvailableTimeslot(void)
{
    BYTE ucLastTimeslot = 0;
    BYTE ucAvaTimeslot = 0;
    EnumDpStreamNum enumDpStreamNum = _DP_ST_DAISY_START;
    bit bStreamStatus = _DISABLE;

    for(enumDpStreamNum = _DP_ST_DAISY_START; enumDpStreamNum <= _DP_ST_DAISY_END; enumDpStreamNum++)
    {
        // Find The Last Timeslot
        if(GET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(enumDpStreamNum) > ucLastTimeslot)
        {
            ucLastTimeslot = GET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(enumDpStreamNum);
        }

        // Determine if any stream is in use
        if(GET_DP_MAC_TX_DAISY_ST_STATUS_REG(enumDpStreamNum) == _ENABLE)
        {
            bStreamStatus = _ENABLE;
        }
    }

    // Error Handler
    if(ucLastTimeslot > 63)
    {
        ucLastTimeslot = 63;
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Max AvaTimeslot: 128b132b = 64, 8b10b = 63
    // LastTimeslot: 128b132b = 0~63, 8b10b = 1~63
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        // 64 timeslot
        if(bStreamStatus == _DISABLE)
        {
            ucAvaTimeslot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM;
        }
        // 64 timeslot - (end - start + 1)
        else
        {
            ucAvaTimeslot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM - (ucLastTimeslot - 0 + 1);
        }
    }
    else
#endif
    {
        // MST:63 timeslot, SST: 64 timeslot
        if(bStreamStatus == _DISABLE)
        {
            ucAvaTimeslot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM - ((GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT) ? 1 : 0);
        }
        // 63 timeslot - (end - start +1)
        else
        {
            ucAvaTimeslot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM - 1 - (ucLastTimeslot - 1 + 1);
        }
    }

    return ucAvaTimeslot;
}

#if((_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) && (_DP_TX_FEC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Judge PBN Conversion
// Input Value  : WORD PBN, EnumMessageRequestID
// Output Value : WORD PBN
//--------------------------------------------------
WORD ScalerDpMstTxJudgePbnConversion(WORD usInputPbn, EnumMessageReuqestID enumMsgRequestId)
{
    DWORD ulOutputPbn = usInputPbn;
    EnumInputPort enumInputPort = GET_DP_RX_MAIN_PORT();

    if(usInputPbn == 0)
    {
        return 0;
    }

    // A. Rx 128b132b to Tx 8b10b with FEC
    // 1. EnumPathResource: - 2.4% PBN of Tx
    // 2. AllocatePayload:  + 2.4% PBN to Tx
    //
    // B. Rx 8b10b with FEC to Tx 128b132b
    // 1. EnumPathResource: + 2.4% PBN of Tx
    // 2. AllocatePayload:  - 2.4% PBN to Tx
    //
    // Others. No Modification

    // Case A
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
    {
        if((ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_8B10B) &&
           (GET_DP_TX_FEC_READY_8B10B() == _TRUE))
        {
            DebugMessageMst("MST TX PBN Rx20 to Tx14 + FEC Before", usInputPbn);

            if(enumMsgRequestId == _DP_MSG_ENUM_PATH_RESOURCES)
            {
                ulOutputPbn = LOWORD(ScalerGlobalComputeDwordMulDiv((DWORD)usInputPbn, 976, 1000));

                DebugMessageMst("MST TX PBN Conversion EnumPathResource", 0);
            }
            else if(enumMsgRequestId == _DP_MSG_ALLOCATE_PAYLOAD)
            {
                ulOutputPbn = LOWORD(ScalerGlobalComputeDwordMulDiv((DWORD)usInputPbn, 1000, 976));

                DebugMessageMst("MST TX PBN Conversion AllocatePayload", 0);
            }

            DebugMessageMst("MST TX PBN Rx20 to Tx14 + FEC After", ulOutputPbn);
        }
    }
    // Case B
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    else if((ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_8B10B) &&
            (ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x20, _BIT0) == _TRUE))
    {
        if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
        {
            DebugMessageMst("MST TX PBN Rx14 + FEC to Tx20 Before", usInputPbn);

            if(enumMsgRequestId == _DP_MSG_ENUM_PATH_RESOURCES)
            {
                ulOutputPbn = LOWORD(ScalerGlobalComputeDwordMulDiv((DWORD)usInputPbn, 1000, 976));

                DebugMessageMst("MST TX PBN Conversion EnumPathResource", 0);
            }
            else if(enumMsgRequestId == _DP_MSG_ALLOCATE_PAYLOAD)
            {
                ulOutputPbn = LOWORD(ScalerGlobalComputeDwordMulDiv((DWORD)usInputPbn, 976, 1000));

                DebugMessageMst("MST TX PBN Conversion AllocatePayload", 0);
            }

            DebugMessageMst("MST TX PBN Rx14 + FEC to Tx20 After", ulOutputPbn);
        }
    }
#endif

    return (WORD)ulOutputPbn;
}
#endif

//--------------------------------------------------
// Description  : Get Tx HPD Status
// Input Value  : None
// Output Value : _DP_PLUG / _DP_UNPLUG
//--------------------------------------------------
bit ScalerDpMstTxGetIncomingHPDStatus(void)
{
    if((GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_TARGET_PORT(_CSN_QUEUE_ENTRY_0) == GET_DP_RX_MAIN_PORT()) &&
       (GET_TX_MST_OUTPUT_PORT_PLUG_QUEUE_STATUS(_CSN_QUEUE_ENTRY_0) == _CONNECT_STATUS_UNPLUG))
    {
        return _DP_UNPLUG;
    }

    return GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS();
}

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP128b132b to 8b10b MST to MST Intial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTx128b132bTo8b10bInitial(void)
{
    // Enable SF to 4 SF, BS delay 3 cycle
    // Enable Stream 1,
    ScalerSetBit(P2F_10_CTRL_ST1_10, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);

    // Enable Stream 2
    ScalerSetBit(P2F_50_CTRL_ST2_10, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);

    // Enable Stream 3
    ScalerSetBit(P2F_90_CTRL_ST3_10, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);

    // Enable Stream 4
    ScalerSetBit(P2F_D0_CTRL_ST4_10, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);

    // Enable Stream 5
    ScalerSetBit(P2D_10_CTRL_ST5_10, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);

    // Enable Stream 6
    ScalerSetBit(P2D_50_CTRL_ST6_10, ~(_BIT3 | _BIT2), _BIT3 | _BIT2);

    // Enable Hblank No Sf New Mode
    if(ScalerDpMstTx128b132bTo8b10bHblankNoSfModeSupport() == _TRUE)
    {
        SET_DP_MST_128B132B_TO_8B10B_NO_SF_NEW_MODE();
    }
}

//--------------------------------------------------
// Description  : DP128b132b to 8b10b MST to MST Stream Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTx128b132bTo8b10bStreamHandler(void)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_NONE;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE)
    {
        return;
    }

    if(GET_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_GLOBAL_ENABLE() == _ENABLE)
    {
        for(enumDpStreamNum = _DP_ST_DAISY_START; enumDpStreamNum <= _DP_ST_DAISY_END; enumDpStreamNum++)
        {
            if(GET_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(enumDpStreamNum) == _ENABLE)
            {
                ScalerDpMstTx128b132bTo8b10bMsaStableCheck(enumDpStreamNum);

                ScalerDpMstTx128b132bTo8b10bMiscStableCheck(enumDpStreamNum);
            }
        }
    }
}
//--------------------------------------------------
// Description  : DP128b132b to 8b10b MST Page Address Mapping Function
// Input Value  : EnumDpStreamNum, St1 Page Address
// Output Value : Stx Page Address
//--------------------------------------------------
WORD ScalerDpMstTxGet128b132bTo8b10bPageAddress(EnumDpStreamNum enumDpStreamNum, WORD usSt1Address)
{
    BYTE ucRegOffset = (BYTE)(usSt1Address - 0x2F00);

    switch(enumDpStreamNum)
    {
        case _DP_ST_1:
            return 0x2F00 + ucRegOffset;

        case _DP_ST_2:
            return 0x2F40 + ucRegOffset;

        case _DP_ST_3:
            return 0x2F80 + ucRegOffset;

        case _DP_ST_4:
            return 0x2FC0 + ucRegOffset;

        case _DP_ST_5:
            return 0x2D00 + ucRegOffset;

        case _DP_ST_6:
            return 0x2D40 + ucRegOffset;

        default:
            return usSt1Address;
    }
}

//--------------------------------------------------
// Description  : Convert DP128b132b MSA to DP8b10b MSA
// Input Value  : EnumDpStreamNum enumDpStreamNum, bit bEn
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSet128b132bTo8b10bMsaConvert(EnumDpStreamNum enumDpStreamNum, bit bEn)
{
    StructDpMstTx128b132bTo8b10bMsaInfo stDpMstTxMsaInfoUpdate = {0};

    if(bEn == _DISABLE)
    {
        // Disable MSA 128b132b to 8b10b clk HW auto transport
        ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_00_CTRL_ST1_00), ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        CLR_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(enumDpStreamNum);
        CLR_DP_MST_TX_128B132B_MSA_VIDEO_FREQ(enumDpStreamNum);
        CLR_DP_MST_TX_128B132B_MSA_AUDIO_FREQ(enumDpStreamNum);
        CLR_DP_MST_TX_128B132B_MSA_COLOR_DEPTH(enumDpStreamNum);
        CLR_DP_MST_TX_128B132B_MSA_COLOR_SPACE(enumDpStreamNum);

        return;
    }

    // enable MSA 128b132b to 8b10b clk HW auto transport
    ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_00_CTRL_ST1_00), ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
    ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~_BIT7, 0x00);

    // Pop up DP128b132b MSA
    ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_00_CTRL_ST1_00), ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

    // Delay one frame
    ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

    // 1. Set Mvid Maud Nvid Naud
    stDpMstTxMsaInfoUpdate.ul128b132bMsaVfreq = TO_DWORD(ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_14_CTRL_ST1_14)),
                                                         ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_13_CTRL_ST1_13)),
                                                         ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_12_CTRL_ST1_12)),
                                                         ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_11_CTRL_ST1_11)));

    stDpMstTxMsaInfoUpdate.ul128b132bMsaAfreq = TO_DWORD(ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_1A_CTRL_ST1_1A)),
                                                         ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_19_CTRL_ST1_19)),
                                                         ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_18_CTRL_ST1_18)),
                                                         ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_17_CTRL_ST1_17)));

    ScalerDpMstTxSet128b132bTo8b10bMsaValue(enumDpStreamNum, stDpMstTxMsaInfoUpdate.ul128b132bMsaVfreq, stDpMstTxMsaInfoUpdate.ul128b132bMsaAfreq);

    // 2. Set Color Depth & Color Space
    ScalerDpMstTx128b132bTo8b10bColorInfoUpdate(enumDpStreamNum, &stDpMstTxMsaInfoUpdate);

    ScalerDpMstTxSet128b132bTo8b10bMiscValue(enumDpStreamNum, stDpMstTxMsaInfoUpdate.b2ColorDepth, stDpMstTxMsaInfoUpdate.b3ColorSpace);

    SET_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(enumDpStreamNum);
}

//--------------------------------------------------
// Description  : Disable Tx128b132b to 8b10b MSA convert
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxReset128b132bTo8b10bMsaConvert(void)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_NONE;

    for(enumDpStreamNum = _DP_ST_DAISY_START; enumDpStreamNum <= _DP_ST_DAISY_END; enumDpStreamNum++)
    {
        CLR_DP_MST_TX_128B132B_TO_8B10B_MSA_CONVERT_ENABLE(enumDpStreamNum);
        CLR_DP_MST_TX_128B132B_MSA_VIDEO_FREQ(enumDpStreamNum);
        CLR_DP_MST_TX_128B132B_MSA_AUDIO_FREQ(enumDpStreamNum);
        CLR_DP_MST_TX_128B132B_MSA_COLOR_DEPTH(enumDpStreamNum);
        CLR_DP_MST_TX_128B132B_MSA_COLOR_SPACE(enumDpStreamNum);

        // Reset MSA 128b132b to 8b10b enable
        ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_00_CTRL_ST1_00), ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Update 128b132b to 8b10b Color Depth & Color Space Value
// Input Value  : enumDpStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTx128b132bTo8b10bColorInfoUpdate(EnumDpStreamNum enumDpStreamNum, StructDpMstTx128b132bTo8b10bMsaInfo *pstDpMstTxMsaInfoUpdate)
{
    BYTE ucMisc0 = 0;
    BYTE ucMisc1 = 0;
    BYTE ucColorSpaceValue = 0;

    ScalerSetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_28_CTRL_ST1_28), 0x16);

    ucMisc0 = ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_29_CTRL_ST1_29));

    ScalerSetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_28_CTRL_ST1_28), 0x17);

    ucMisc1 = ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_29_CTRL_ST1_29));

    // Check MISC1[6]
    if((ucMisc1 & _BIT6) == _BIT6)
    {
        pstDpMstTxMsaInfoUpdate->b2ColorDepth = ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_2D_CTRL_ST1_2D)) & (_BIT1 | _BIT0);

        ucColorSpaceValue = ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_2C_CTRL_ST1_2C)) & (_BIT7 | _BIT6 | _BIT5 | _BIT4);

        // Get Color Space
        switch(ucColorSpaceValue)
        {
            // RGB
            case _VSC_COLOR_SPACE_0:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_RGB;
                break;

            // YCBCR444
            case _VSC_COLOR_SPACE_1:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_YCBCR444;
                break;

            // YCBCR422
            case _VSC_COLOR_SPACE_2:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_YCBCR422;
                break;

            // YCBCR420
            case _VSC_COLOR_SPACE_3:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_YCBCR420;
                break;

            // Y-ONLY
            case _VSC_COLOR_SPACE_4:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_Y_ONLY;
                break;

            // RAW
            case _VSC_COLOR_SPACE_5:
            default:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_RGB;
                break;
        }
    }
    else
    {
        pstDpMstTxMsaInfoUpdate->b2ColorDepth = (ucMisc0 & (_BIT6 | _BIT5)) >> 5;

        ucColorSpaceValue = (ucMisc1 & _BIT7) | (ucMisc0 & (_BIT2 | _BIT1));

        // Get Color Space
        switch(ucColorSpaceValue)
        {
            // YCBCR422
            case _BIT1:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_YCBCR422;
                break;

            // YCBCR444
            case _BIT2:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_YCBCR444;
                break;

            // Y-ONLY
            case _BIT7:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_Y_ONLY;
                break;

            // RAW
            case (_BIT7 | _BIT1):
            // RGB
            case 0x00:
            default:
                pstDpMstTxMsaInfoUpdate->b3ColorSpace = _COLOR_SPACE_RGB;
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Set 128b132b to 8b10b MSA Mvid Maud Nvid Naud Value
// Input Value  : enumDpStreamNum, ulVideoFreq, ulAudioFreq
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSet128b132bTo8b10bMsaValue(EnumDpStreamNum enumDpStreamNum, DWORD ulVideoFreq, DWORD ulAudioFreq)
{
    WORD usTempAddr = 0;
    WORD usTempData = 0;
    DWORD ulNvid = 0;
    DWORD ulMvid = 0;
    DWORD ulNaud = 0;
    DWORD ulMaud = 0;

    // Record Video and Audio Freq
    SET_DP_MST_TX_128B132B_MSA_VIDEO_FREQ(enumDpStreamNum, ulVideoFreq);
    SET_DP_MST_TX_128B132B_MSA_AUDIO_FREQ(enumDpStreamNum, ulAudioFreq);

    // Nvid
    ulNvid = 0x8000;

    // calculate Mvid
    // Mvid = vfreq * Nvid / Link clock
    // = vfreq_reg * Nvid / 10^6 * Link clcok
    ulMvid = GET_DWORD_MUL_DIV(ulVideoFreq, ulNvid, ((DWORD)27 * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() * (1000000)));

    // Naud
    ulNaud = 0x8000;

    // calculate Maud
    // Maud = afreq * Naud / Link clock
    // = afreq_reg * Naud / 10^6 * Link clcok
    ulMaud = GET_DWORD_MUL_DIV(ulAudioFreq, ulNaud, ((DWORD)27 * GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() * (1000000)));

    if(GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _TRUE)
    {
        ulMvid = GET_DWORD_MUL_DIV(ulMvid, 9975, 10000);
        ulMaud = GET_DWORD_MUL_DIV(ulMaud, 9975, 10000);
    }

    // Set Mvid, Nvid
#if(_DP_HW_TX_128B132B_TO_8B10B_ADDR_PORT_AUTO_INC_SUPPORT == _OFF)
    BYTE ucCount = 0;

    for(ucCount = 0; ucCount <= 32; ucCount++)
    {
        usTempAddr = ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_26_CTRL_ST1_26);

        if(ScalerGetByte(usTempAddr) == 0x00)
        {
            usTempData = ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_27_CTRL_ST1_27);

            ScalerSetByte(usTempData, DWORD_TO_BYTE(ulMvid, 0));
            ScalerGetByte(usTempAddr);
            ScalerSetByte(usTempData, DWORD_TO_BYTE(ulMvid, 1));
            ScalerGetByte(usTempAddr);
            ScalerSetByte(usTempData, DWORD_TO_BYTE(ulMvid, 2));
            ScalerGetByte(usTempAddr);
            ScalerSetByte(usTempData, DWORD_TO_BYTE(ulNvid, 0));
            ScalerGetByte(usTempAddr);
            ScalerSetByte(usTempData, DWORD_TO_BYTE(ulNvid, 1));
            ScalerGetByte(usTempAddr);
            ScalerSetByte(usTempData, DWORD_TO_BYTE(ulNvid, 2));
            break;
        }
    }
#else
    usTempAddr = ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_26_CTRL_ST1_26);
    usTempData = ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_27_CTRL_ST1_27);

    ScalerSetByte(usTempAddr, 0x00);

    ScalerSetByte(usTempData, DWORD_TO_BYTE(ulMvid, 0));
    ScalerSetByte(usTempData, DWORD_TO_BYTE(ulMvid, 1));
    ScalerSetByte(usTempData, DWORD_TO_BYTE(ulMvid, 2));
    ScalerSetByte(usTempData, DWORD_TO_BYTE(ulNvid, 0));
    ScalerSetByte(usTempData, DWORD_TO_BYTE(ulNvid, 1));
    ScalerSetByte(usTempData, DWORD_TO_BYTE(ulNvid, 2));
#endif
    // Set Maud, Naud
    usTempAddr = ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_0A_CTRL_ST1_0A);

    ScalerSetByte(usTempAddr++, DWORD_TO_BYTE(ulMaud, 0));
    ScalerSetByte(usTempAddr++, DWORD_TO_BYTE(ulMaud, 1));
    ScalerSetByte(usTempAddr++, DWORD_TO_BYTE(ulMaud, 2));
    ScalerSetByte(usTempAddr++, DWORD_TO_BYTE(ulNaud, 0));
    ScalerSetByte(usTempAddr++, DWORD_TO_BYTE(ulNaud, 1));
    ScalerSetByte(usTempAddr++, DWORD_TO_BYTE(ulNaud, 2));
}

//--------------------------------------------------
// Description  : Set 128b132b to 8b10b Color Depth & Color Space Value
// Input Value  : enumDpStreamNum, ucColorDepthValue, ucColorSpaceValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxSet128b132bTo8b10bMiscValue(EnumDpStreamNum enumDpStreamNum, BYTE ucColorDepthValue, BYTE ucColorSpaceValue)
{
    // Record Color Depth & Color Space
    SET_DP_MST_TX_128B132B_MSA_COLOR_DEPTH(enumDpStreamNum, ucColorDepthValue);
    SET_DP_MST_TX_128B132B_MSA_COLOR_SPACE(enumDpStreamNum, ucColorSpaceValue);

    // Set Color Depth
    ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~(_BIT5 | _BIT4), ((ucColorDepthValue & (_BIT1 | _BIT0)) << 4));

    // Set Color Space
    switch(ucColorSpaceValue)
    {
        case _COLOR_SPACE_RGB:
            ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~(_BIT2 | _BIT1 | _BIT0), 0x00);
            break;

        case _COLOR_SPACE_YCBCR444:
            ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
            break;

        case _COLOR_SPACE_YCBCR422:
            ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
            break;

        case _COLOR_SPACE_YCBCR420:
            ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
            break;

        case _COLOR_SPACE_Y_ONLY:
            ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        default:
            ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_01_CTRL_ST1_01), ~(_BIT2 | _BIT1 | _BIT0), 0x00);
            break;
    }
}

//--------------------------------------------------
// Description  : Stable Check for 128b132b to 8b10b MSA Mvid Maud Nvid Naud Value
// Input Value  : enumDpStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTx128b132bTo8b10bMsaStableCheck(EnumDpStreamNum enumDpStreamNum)
{
    DWORD ulVideoFreq = 0;
    DWORD ulAudioFreq = 0;

    // Get Current Vfreq
    ulVideoFreq = TO_DWORD(ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_14_CTRL_ST1_14)),
                           ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_13_CTRL_ST1_13)),
                           ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_12_CTRL_ST1_12)),
                           ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_11_CTRL_ST1_11)));

    // Get Current Afreq
    ulAudioFreq = TO_DWORD(ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_1A_CTRL_ST1_1A)),
                           ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_19_CTRL_ST1_19)),
                           ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_18_CTRL_ST1_18)),
                           ScalerGetByte(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_17_CTRL_ST1_17)));

    // Setting New MSA Mvid or Maud Value if vfreq changes
    if((ulVideoFreq != GET_DP_MST_TX_128B132B_MSA_VIDEO_FREQ(enumDpStreamNum)) ||
       (ulAudioFreq != GET_DP_MST_TX_128B132B_MSA_AUDIO_FREQ(enumDpStreamNum)))
    {
        DebugMessageDpTx("DP20to14 MST2MST Freq Changes! enumDpStreamNum", enumDpStreamNum);
        DebugMessageDpTx("New Video Freq", ulVideoFreq);
        DebugMessageDpTx("Old Video Freq", GET_DP_MST_TX_128B132B_MSA_VIDEO_FREQ(enumDpStreamNum));
        DebugMessageDpTx("New Audio Freq", ulAudioFreq);
        DebugMessageDpTx("Old Audio Freq", GET_DP_MST_TX_128B132B_MSA_AUDIO_FREQ(enumDpStreamNum));

        ScalerDpMstTxSet128b132bTo8b10bMsaValue(enumDpStreamNum, ulVideoFreq, ulAudioFreq);
    }
}

//--------------------------------------------------
// Description  : Stable Check for 128b132b to 8b10b Color Depth & Color Space Value
// Input Value  : enumDpStreamNum
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTx128b132bTo8b10bMiscStableCheck(EnumDpStreamNum enumDpStreamNum)
{
    StructDpMstTx128b132bTo8b10bMsaInfo stDpMstTxMsaInfoUpdate = {0};

    // Pop up DP128b132b MSA
    ScalerSetBit(ScalerDpMstTxGet128b132bTo8b10bPageAddress(enumDpStreamNum, P2F_00_CTRL_ST1_00), ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

    // Get Current Color Depth & Color Space
    ScalerDpMstTx128b132bTo8b10bColorInfoUpdate(enumDpStreamNum, &stDpMstTxMsaInfoUpdate);

    // Setting New Color Depth & Color Space Value if changed
    if((stDpMstTxMsaInfoUpdate.b2ColorDepth != GET_DP_MST_TX_128B132B_MSA_COLOR_DEPTH(enumDpStreamNum)) ||
       (stDpMstTxMsaInfoUpdate.b3ColorSpace != GET_DP_MST_TX_128B132B_MSA_COLOR_SPACE(enumDpStreamNum)))
    {
        DebugMessageDpTx("DP20to14 MST2MST Misc Changes! enumDpStreamNum", enumDpStreamNum);
        DebugMessageDpTx("New Color Depth", stDpMstTxMsaInfoUpdate.b2ColorDepth);
        DebugMessageDpTx("Old Color Depth", GET_DP_MST_TX_128B132B_MSA_COLOR_DEPTH(enumDpStreamNum));
        DebugMessageDpTx("New Color Space", stDpMstTxMsaInfoUpdate.b3ColorSpace);
        DebugMessageDpTx("Old Color Space", GET_DP_MST_TX_128B132B_MSA_COLOR_SPACE(enumDpStreamNum));

        ScalerDpMstTxSet128b132bTo8b10bMiscValue(enumDpStreamNum, stDpMstTxMsaInfoUpdate.b2ColorDepth, stDpMstTxMsaInfoUpdate.b3ColorSpace);
    }
}
#endif

#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx CSN event reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxInterceptDdcciMsgSetting(bit bStatus)
{
    SET_DP_MST_TX_INTERCEPT_DDCCI_MSG_STATUS(bStatus);
}
#endif
#endif // End for #if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

#if((_DP_TX_SUPPORT == _ON) && ((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : DP Tx Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstTxReset(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_RX_MAIN_PORT());

// HW Reset-----------------------------------

    // Reset All Daisy Chain Start End Position
    ScalerDpMacTxResetDaisyStreamPositionReg();

    // Reset All Daisy Chain Source Mux
    ScalerDpMacTxResetDaisySourceMuxReg();

    // Reset MSA 128b132b to 8b10b convert
#if((_DP_MST_SUPPORT == _ON) && (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpMstTxReset128b132bTo8b10bMsaConvert();
#endif

#if(_DP_MST_SUPPORT == _ON)
    if((ScalerDpAuxRxGetDpcdBitInfo(GET_DP_RX_MAIN_PORT(), 0x00, 0x00, 0x21, _BIT0) == _BIT0) &&
       (GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT))
    {
        BYTE ucData = 0;

        // Clear Payload ID Only if Downstream PID Table is Not Empty
        if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0xC1, 1, &ucData) == _TRUE)
        {
            if(ucData != 0x00)
            {
                // Set Flag to Gen Clear ID Table Msg
                SET_DP_MST_RX_GEN_DOWN_REQUEST_MSG(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);
            }
        }
        else
        {
            // Set Flag to Gen Clear ID Table Msg
            SET_DP_MST_RX_GEN_DOWN_REQUEST_MSG(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);
        }
    }

    // AUX fifo reset
    Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Reset Tx MSG FIFO
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_PTR(0x00);

    // Reset Tx Write MSG FSM
    SET_DP_MST_TX_REG_DOWNSTREAM_MSG_WRITE_DISABLE();

    // Reset Tx Read MSG FSM
    SET_DP_MST_TX_REG_UPSTREAM_MSG_READ_DISABLE();

    // CLR MSG Finish Flag
    CLR_DP_MST_TX_REG_UPSTREAM_MSG_READ_FINISH_FLAG();

    // CLR SBMSG Finish Flag
    CLR_DP_MST_TX_REG_UPSTREAM_SBMSG_FINISH_FLAG();

    // Buf_CLR=1 WR_PTR = 0x00
    CLR_DP_MST_TX_REG_UPSTREAM_MSG_BUF();

// FW Reset-----------------------------------

    // Clear Flags of Tx MSG Proc Status
    SET_DP_MST_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);
    SET_DP_MST_TX_RECEIVED_MSG_COUNT(0);
    CLR_DP_MST_TX_MSG_DURING_HPD_LOW_DEBOUNCE();

    // Clear Down Request MSG Proc Flags
    SET_DP_MST_TX_DOWN_REQUEST_EVENT(_DP_TX_NONE_EVENT);
    CLR_DP_MST_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
    CLR_DP_MST_TX_DOWN_REQUEST_MSG_DONE();
    CLR_DP_MST_TX_DOWN_REQUEST_BROAD_MSG();
    CLR_DP_MST_TX_DOWN_REQUEST_ANAL();
    CLR_DP_MST_TX_DOWN_REQUEST_READY();
    CLR_DP_MST_TX_ILLEGAL_DOWN_REQUEST_MSG();
    SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(0);
    CLR_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG();

    // Clear Down Reply MSG Proc Flags
    SET_DP_MST_TX_DOWN_REPLY_EVENT(_DP_TX_NONE_EVENT);
    CLR_DP_MST_TX_DOWN_REPLY_READ_DISABLE();
    CLR_DP_MST_TX_DOWN_REPLY_DIRECTLY();
    CLR_DP_MST_TX_DOWN_REPLY_ANAL();
    CLR_DP_MST_TX_MSG_DOWN_REPLY_ANAL_FINISH();
    CLR_DP_MST_TX_DOWN_REPLY_READY();
    CLR_DP_MST_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
    CLR_DP_MST_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE();
    CLR_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();

    // Clear Up Request MSG Proc Flags
    CLR_DP_MST_TX_GEN_UP_REQUEST_MSG();
    CLR_DP_MST_TX_UP_REQUEST_MSG_HEADER();
    CLR_DP_MST_TX_UP_REQUEST_READY();
    CLR_DP_MST_TX_UP_REQUEST_ANAL();
    CLR_DP_MST_TX_ILLEGAL_UP_REQUEST_MSG();

    // Clear Up Reply MSG Proc Flags
    CLR_DP_MST_TX_UP_REPLY_BYPASS();
    CLR_DP_MST_TX_UP_REPLY_DIRECTLY();
    CLR_DP_MST_TX_UP_REPLY_MSG_DONE();
    CLR_DP_MST_TX_UP_REPLY_READY();
#endif

    // Reset Stream ID Mapping Table
    ScalerDpMacTxResetStreamToIdMapping();

    // Reset Source Mux Backup
    ScalerDpMacTxResetDaisySourceMuxBackup();

#if(_DP_MST_SUPPORT == _ON)
    // CSN Event Reset
    ScalerDpMstTxCsnEventReset();

    // SEN Event Reset
    ScalerDpMstTxSenEventReset();

    // Cancel Timers
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT);

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    // Reset DSC Pass-Through Setting
    ScalerDpMacTxDscPassThroughReset();

    CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    CLR_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE();
#endif

#if(_DP_MST_TX_INTERCEPT_DDCCI_MSG_SUPPORT == _ON)
    // Reset Tx DDCCI Intercept flag
    CLR_DP_MST_TX_INTERCEPT_DDCCI_MSG_ADJUST_LCR();
#endif
#endif
}
#endif
