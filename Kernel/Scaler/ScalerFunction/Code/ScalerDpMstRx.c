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
// ID Code      : ScalerDpMstRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPRXMST__

#include "ScalerFunctionInclude.h"
#include "DpMstRx/ScalerDpMstRx.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
BYTE code tDpMstRxRadBaseBitMap[13] =
{
    12, 8, 20, 16, 28, 24,
    4, 0, 12, 8, 20, 16, 28,
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
volatile EnumDpMstModeStatus g_penumDpMstRxModeStatus[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];
volatile BYTE g_ucDpMstRxEvent = _DP_RX_NONE_EVENT;
//BYTE g_ucMsgErrorType = _NONE_MSG_ERROR;

UnionDpMacRxReqStrct g_unDpMstRxRequestPool;
UnionDpMacRxRepStrct g_unDpMstRxReplyPool;
volatile StructPoolUsageInfo g_stDpMstRxPoolUsage;
volatile StructRxMsgFunctionInfo g_stDpMstRxMsgFunction;
volatile StructRxMsgOtherInfo g_stDpMstRxMsgOtherInfo;
volatile StructRxMsgPortInfo g_pstDpMstRxMsgPortInfo[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];
EnumDpMstPort g_enumDpMstRxDownRequestPortNum = _DP_PORT0;
StructDpMstRxMsgPort g_stDpMstRxMsgPort;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
bit g_bDpMstRxPxpModeSupprot;
BYTE g_ucDpMstRxPxpModeType;
BYTE g_ucDpMstRxPxpInputPort;
EnumDpPxpPortNumSwapStatus g_enumDpMstRxPxpPortNumSwap;
#endif

#if(_DP_TX_SUPPORT == _ON)
volatile BYTE g_ucDpMstRxTotalReceivedMsgCount;
#endif

// INT Used Flags
volatile bit g_pbDpMstRxMacReplyBufFree[3];
BYTE g_pucDpMstRxMsgQueryEncryptClientId[7];
StructReqGetMsgCRC g_stDpMstRxReqGetMsgCRC;
volatile StructTimerEventTableType g_pstDpMstRxTimerEvent[_SCALER_DP_MST_EVENT_COUNT];

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
StructMstMutiFunction g_stDpMstRxMultiFunc;
#endif
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Rx Msg Initial
// Input Value  : EnumDpRxMstPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxInitial(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    ScalerDpMstRxReset(enumInputPort);

    if(ScalerDpRxGetMstCapability(enumInputPort) == _TRUE)
    {
        // Reset Rx MSG Block Before Enabling MSG Reception to Clear HW Flags
        SET_DP_MST_RX_REG_MSG_RESET();

        // Enable Down Requeset BUF0 / BUF1 MSG Receive
        SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_BUF1_MSG_RECEIVE_ENABLE();

        // Enable Up Reply BUF0 / BUF1 MSG Receive
        SET_DP_MST_RX_REG_UP_REPLY_BUF0_BUF1_MSG_RECEIVE_ENABLE();

        // Clear DPCD 111/ 1C2 IRQ Flag
        CLR_DP_AUX_RX_REG_111_IRQ_FLAG();
        CLR_DP_AUX_RX_REG_1C2_IRQ_FLAG();

        // Enable DPCD 111/1C2 IRQ
        SET_DP_AUX_RX_REG_111_IRQ_EN();
        SET_DP_AUX_RX_REG_1C2_IRQ_EN();

        // Clear Payload ID Table
        CLR_DP_AUX_RX_REG_CLEAR_PAYLOAD_ID_TABLE();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
        ScalerDpMstRxMultiFunctionInitial(enumInputPort);
#endif
    }
    else
    {
        // Disable Down Requeset BUF0 / BUF1 MSG Receive
        CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_BUF1_MSG_RECEIVE_ENABLE();

        // Disable Up Reply BUF0 / BUF1 MSG Receive
        CLR_DP_MST_RX_REG_UP_REPLY_BUF0_BUF1_MSG_RECEIVE_ENABLE();

        // Disable DPCD 111 IRQ
        CLR_DP_AUX_RX_REG_111_IRQ_EN();

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x06, _BIT1) == 0x00)
#endif
        {
            // Disable DPCD 1C2 IRQ When 128b132b Don't Support and MST off
            CLR_DP_AUX_RX_REG_1C2_IRQ_EN();
        }
    }
}

//--------------------------------------------------
// Description  : Mst Capable Port Switch
// Input Value  : EnumDpRxMstPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxCapablePortSwitch(EnumDPMSTPort enumMstCapablePort)
{
    DebugMessageMst("MST Capable Port Switch to", enumMstCapablePort);

    SET_DP_RX_TARGET_MST_PORT(enumMstCapablePort);
    SET_DP_RX_CAPABILITY_SWITCHED();
}

//--------------------------------------------------
// Description  : Dp Message Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxHandler(void)
{
    if(GET_DP_RX_TARGET_MST_PORT() == _DP_MST_NO_PORT)
    {
        return;
    }

    ScalerDpMstRxModeStatusCheck();

    ScalerDpMstRxMsgHandler();

    ScalerDpMstRxMsgErrorHandler();

    ScalerDpMstRxTimerEventActiveHandler();
}

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx Pxp Mode Switch
// Input Value  : bit bStatus
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxPxpModeSwitch(EnumDpMstPxpMode enumDpMstPxpMode)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    SET_DP_MST_RX_PXP_MODE(enumDpMstPxpMode);

    if(enumDpMstPxpMode != _DP_MST_PXP_OFF)
    {
        SET_DP_MST_RX_PXP_MODE_SUPPORT(_ON);
    }
    else
    {
        SET_DP_MST_RX_PXP_MODE_SUPPORT(_OFF);
    }

    // Pxp mode switch set long hpd notify Mst Source logical port9 status changed
    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
    {
        if(ScalerDpRxGetSrcMstUpRequestEnable(enumInputPort) == _ENABLE)
        {
            if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
            {
                ScalerDpRxSetHotPlugEvent(enumInputPort, _DP_MST_LONG_HPD_EVENT);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Dp Mst Rx Get Pxp Mode
// Input Value  : None
// Output Value : EnumDpMstPxpMode enumDpMstPxpMode
//--------------------------------------------------
EnumDpMstPxpMode ScalerDpMstRxGetPxpMode(void)
{
    return GET_DP_MST_RX_PXP_MODE();
}
#endif

//--------------------------------------------------
// Description  : Rx MST Mode Status Check for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxModeStatusCheck(void)
{
    for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
        {
            continue;
        }

        ScalerDpRxSetBaseInputPort(enumInputPort);

        switch(GET_DP_MST_RX_MODE_STATE())
        {
            case _DP_RX_MST_MODE_STATUS_NONE_MSG:

                break;

            case _DP_RX_MST_MODE_STATUS_BUILD_TOPOLOGY:

                if(ScalerDpMstRxCheckMsgBufferFree(enumInputPort) == _TRUE)
                {
                    SET_DP_MST_RX_MODE_STATE(_DP_RX_MST_MODE_STATUS_ALLOCATED_PBN);
                }

                break;

            case _DP_RX_MST_MODE_STATUS_ALLOCATED_PBN:

                break;

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : DP Rx Mst Msg Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxMsgHandler(void)
{
    ScalerDpMstRxDownRequestProc();

#if((_DP_TX_SUPPORT == _ON) || (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
    ScalerDpMstRxUpRequestEventCheckDone();
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(GET_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT()) == _TRUE)
    {
        // Recover Urgent Event Check
        CLR_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());
    }
    else
    {
        if(ScalerDpMstRxDownReqMsgCheckUrgent() == _FALSE)
        {
            // Skip Urgent Event Check
            SET_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());

            // Run Other Handlers Before MSG Reply
            return;
        }
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    ScalerDpMstTxMsgHandler();
#endif

    ScalerDpMstRxDownReplyProc();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
    ScalerDpMstRxVirtualDpUpRequestEventCheck();
#endif

    ScalerDpMstRxUpRequestProc();

    ScalerDpMstRxUpReplyProc();
}

//--------------------------------------------------
// Description  : Set DP Aux Msg Irq Enable
// Input Value  : EnumInputPort, Enable
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetMsgReadyIrqEnable(EnumInputPort enumInputPort, EnumDpMessageType enumDpMessageType, bit bEnable)
{
    enumInputPort = enumInputPort;
    enumDpMessageType = enumDpMessageType;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(bEnable == _ENABLE)
    {
        if(enumDpMessageType == _DP_DOWN_REPLY_MSG)
        {
            SET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ();
        }
        else if(enumDpMessageType == _DP_UP_REQUEST_MSG)
        {
            SET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ();
        }
    }
    else
    {
        if(enumDpMessageType == _DP_DOWN_REPLY_MSG)
        {
            CLR_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ();
        }
        else if(enumDpMessageType == _DP_UP_REQUEST_MSG)
        {
            CLR_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ();
        }
    }
}

//--------------------------------------------------
// Description  : Rx Down Request Burst Repeat Situation Proccess
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxDownRequestBurstRepeatHandle(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());

    // Add Request_ID we need in there
    if((GET_DP_MST_RX_MSG_REQUEST_ID() != _DP_MSG_REMOTE_I2C_READ) &&
       (GET_DP_MST_RX_MSG_REQUEST_ID() != _DP_MSG_REMOTE_DPCD_READ) &&
       (GET_DP_MST_RX_MSG_REQUEST_ID() != _DP_MSG_ENUM_PATH_RESOURCES))
    {
        return _TRUE;
    }

    if(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH() == _FALSE)
    {
        return _TRUE;
    }

    // Backup buffer0 Header CRC
    SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER_CRC_BACKUP(GET_DP_MST_RX_REG_DOWN_REQUEST_HEADER_CRC());

    // Backup buffer0 Body CRC
    SET_DP_MST_RX_REG_DOWN_REQUEST_BODY_CRC_BACKUP(GET_DP_MST_RX_REG_DOWN_REQUEST_BODY_CRC());

    // Change Buffer1 Pointer
    SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER1_INFO();

    // Detect Error Retry
    if((GET_DP_MST_RX_REG_DOWN_REQUEST_HEADER_CRC_BACKUP() != GET_DP_MST_RX_REG_DOWN_REQUEST_HEADER_CRC()) ||
       (GET_DP_MST_RX_REG_DOWN_REQUEST_BODY_CRC_BACKUP() != GET_DP_MST_RX_REG_DOWN_REQUEST_BODY_CRC()))
    {
        // Recovery Buff Pointer
        SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER0_INFO();

        return _TRUE;
    }

    // Recovery Buff Pointer
    SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER0_INFO();

    return _FALSE;
}

//--------------------------------------------------
// Description  : Rx Down Request Buffer Release Proccess
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxDownRequestBufferRelease(EnumInputPort enumInputPort)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

    ScalerDpRxSetBaseInputPort(enumInputPort);

    CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN();

    if(GET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_MST_RX_DOWN_REQUEST_BUF0)
    {
        // Clear Flag
        CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH();

        // Defer Any Other MSGs to Prevent Priority and Using Buf Conflict
        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_MST_RX_REG_AUX_TO_MANUAL_MODE();
        }

        if((GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) || (GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_WRITE_PTR() != 0x00))
        {
            CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN();

            if(ScalerDpMstRxDownRequestBurstRepeatHandle() == _TRUE)
            {
                SET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_MST_RX_DOWN_REQUEST_BUF1);
            }
            else
            {
                // Clear buff1 Finish Flag
                CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH();

                // Clear Buff1
                CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1();

                // Enable BUF1 to Receive MSG
                SET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE();
            }
        }
        else
        {
            SET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_MST_RX_DOWN_REQUEST_BUF0);
        }

        // Clear BUF0
        CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0();

        // Enable BUF0 to Receive MSG
        SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE();

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_MST_RX_REG_AUX_TO_AUTO_MODE();
        }
    }
    else
    {
        // Clear BUF1
        CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1();

        // Enable BUF1 to Receive MSG
        SET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE();

        SET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_MST_RX_DOWN_REQUEST_BUF0);
    }
}

//--------------------------------------------------
// Description  : Rx Down Request MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxDownRequestReceive(void)
{
    for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
        {
            continue;
        }

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if(GET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_MST_RX_DOWN_REQUEST_BUF0)
        {
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH() == _TRUE)
            {
                if(GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE)
                {
                    // Clear Request Array Free Flag
                    CLR_DP_MST_RX_REQUEST_POOL_FREE();

                    // Clear Flag
                    CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH();

                    // Set BUF0 Read PTR to 0
                    SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_READ_PTR(0);

                    // Move BUF0 Down Request MSG to Request Array
                    for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_LENGTH(); ucIndex++)
                    {
                        SET_DP_MST_RX_MSG_REQUEST_ARRAY(ucIndex, GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_DATA());
                    }

                    // Select To Header 0
                    SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER0_INFO();

                    SET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(enumInputPort);

                    // Analysis Down Request MSG
                    SET_DP_MST_RX_DOWN_REQUEST_ANAL();
                }
                else
                {
                    return _FALSE;
                }
            }
            // Handle Buf1 to prevent deadlock when Buf0 enable bit has been cleared unexpectedly
            else if(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH() == _TRUE)
            {
                if(GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE)
                {
                    SET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_MST_RX_DOWN_REQUEST_BUF1);

                    // Enable BUF0 to Receive MSG
                    SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE();
                }
            }
        }

        if(GET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_MST_RX_DOWN_REQUEST_BUF1)
        {
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH() == _TRUE)
            {
                if(GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE)
                {
                    // Clear Request Array Free Flag
                    CLR_DP_MST_RX_REQUEST_POOL_FREE();

                    // Clear Flag
                    CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH();

                    // Set BUF1 Read PTR to Zero
                    SET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_READ_PTR(0);

                    // Move BUF1 Down Request MSG to Request Array
                    for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_LENGTH(); ucIndex++)
                    {
                        SET_DP_MST_RX_MSG_REQUEST_ARRAY(ucIndex, GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_DATA());
                    }

                    // Select to Header 1
                    SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER1_INFO();

                    SET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(enumInputPort);

                    // Analysis Down Request MSG
                    SET_DP_MST_RX_DOWN_REQUEST_ANAL();
                }
                else
                {
                    return _FALSE;
                }
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Rx Mst Msg Error Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxMsgErrorHandler(void)
{
    for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
        {
            continue;
        }

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if((GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) &&
           ((GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE) && (GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE)))
        {
            // MSG was written in 1000h but not finish, and no data in pool -> check if LCT/LCR valid or not
            // Allow only LCT = 1 ~ 15; LCR = 0 ~ 14
            if((GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() == 0) || (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() == 15))
            {
                ScalerDpMstRxDownRequestBufferRelease(enumInputPort);
            }
        }

        EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

        // Prevent Down Request MSG BUF0 FSM Dead Lock
        if((GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_ERROR() != _NONE_MSG_ERROR) && (GET_DP_MST_RX_DOWN_REQUEST_ANAL() == _FALSE))
        {
            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_MST_RX_REG_AUX_TO_MANUAL_MODE();
            }

            CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_ERROR();

            CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0();

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_MST_RX_REG_AUX_TO_AUTO_MODE();
            }
        }

        // Prevent Down Request MSG BUF1 FSM Dead Lock
        if((GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_ERROR() != _NONE_MSG_ERROR) && (GET_DP_MST_RX_DOWN_REQUEST_ANAL() == _FALSE))
        {
            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_MST_RX_REG_AUX_TO_MANUAL_MODE();
            }

            CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_ERROR();

            CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1();

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_MST_RX_REG_AUX_TO_AUTO_MODE();
            }
        }

        // Prevent Up Reply MSG BUF0 FSM Dead Lock
        if((GET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_ERROR() != _NONE_MSG_ERROR) && (GET_DP_MST_RX_UP_REPLY_ANAL() == _FALSE))
        {
            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_MST_RX_REG_AUX_TO_MANUAL_MODE();
            }

            CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_ERROR();

            CLR_DP_MST_RX_REG_UP_REPLY_BUF0();

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_MST_RX_REG_AUX_TO_AUTO_MODE();
            }
        }

        // Prevent Up Reply MSG BUF1 FSM Dead Lock
        if((GET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_ERROR() != _NONE_MSG_ERROR) && (GET_DP_MST_RX_UP_REPLY_ANAL() == _FALSE))
        {
            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_MST_RX_REG_AUX_TO_MANUAL_MODE();
            }

            CLR_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_ERROR();

            CLR_DP_MST_RX_REG_UP_REPLY_BUF1();

            if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
            {
                SET_DP_MST_RX_REG_AUX_TO_AUTO_MODE();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Rx Down Reply MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxDownReplySend(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    if(GET_DP_MST_RX_DOWN_REPLY_READY() == _TRUE)
    {
        // CLR Down Reply Ready Flag
        CLR_DP_MST_RX_DOWN_REPLY_READY();

        enumInputPort = GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT();

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if(GET_DP_MST_RX_HOT_PLUG_STATUS() == _TRUE)
        {
            if(GET_DP_MST_RX_MSG_REPLY_ID() == _DP_MSG_LINK_ADDRESS)
            {
                if(GET_DP_MST_RX_MODE_STATE() != _DP_RX_MST_MODE_STATUS_BUILD_TOPOLOGY)
                {
                    SET_DP_MST_RX_MODE_STATE(_DP_RX_MST_MODE_STATUS_BUILD_TOPOLOGY);
                }

#if(_DP_TX_SUPPORT == _ON)
                if((GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT() != 1) && (GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR() == 0))
                {
                    CLR_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
                }
#endif
            }

            // CLR Read Pointer to 0
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY_BUF();

            // CLR Write Pointer to 0
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR();

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR_DONE();

            if(GET_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR_DONE() == _FALSE)
            {
                DELAY_5US();
            }
#endif

            for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(); ucIndex++)
            {
                // Fill Reply Msg into Buffer
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA(GET_DP_MST_RX_MSG_REPLY_ARRAY(ucIndex));

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA_DONE();

                if(GET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA_DONE() == _FALSE)
                {
                    DELAY_5US();
                }
#endif
            }

            // Free Reply Array
            SET_DP_MST_RX_REPLY_POOL_FREE();

            // Select to Down Reply BUF Address
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_DOWN_REPLY_ADDRESS();

#if(_DP_MST_RX_DOWN_REPLY_MANUAL_MODE_SUPPORT == _OFF)

            // Set Start and End Bit to HW Auto Mode
            SET_DP_MST_RX_REG_UPSTREAM_HW_AUTO_MODE();
#else

            // Body length max = total length max - header length - 1byte body CRC
            // Header length = 3 + ((LCT - 1) / 2)
            SET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX(_DP_MST_RX_DOWN_REPLY_MANUAL_MODE_MAX_LEN - (4 + ((GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT() - 1) / 2) + ((GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT() - 1) % 2)));

            SET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH(GET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH());

            SET_DP_MST_RX_DOWN_REPLY_MSG_COUNT((GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH() / GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX()) + (((GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH() % GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX()) > 0) ? 1 : 0));

            if(GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH() > GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX())
            {
                // Set Start and End Bit to Manual Mode
                SET_DP_MST_RX_REG_UPSTREAM_HW_MANUAL_MODE();

                // Set Start Bit
                SET_DP_MST_RX_REG_UPSTREAM_START_BIT();

                // Clear End Bit
                CLR_DP_MST_RX_REG_UPSTREAM_END_BIT();

                // Set Manual Mode Body Length
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX());

                SET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH(GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH() - GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX());
            }
            else
            {
                // Set Start and End Bit to HW Auto Mode
                SET_DP_MST_RX_REG_UPSTREAM_HW_AUTO_MODE();

                // Set Manual Mode Body Length
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH());

                SET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH(0);
            }

            SET_DP_MST_RX_DOWN_REPLY_MSG_COUNT(GET_DP_MST_RX_DOWN_REPLY_MSG_COUNT() - 1);

            // Clear Down Reply Is Read Flag
            CLR_DP_MST_RX_REG_DOWN_REPLY_MSG_IS_READ();
#endif

            CLR_DP_MST_RX_DOWN_REPLY_RETRY_NUM();

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT() == GET_DP_RX_MAIN_PORT())
            {
                // Delete DownRequest Msg Count
                if(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() > 0)
                {
                    SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() - 1);

                    if(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() == 0)
                    {
                        // Cancel Timer Event
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
                    }
                }
            }
#endif

            // Enable Upstream (HW starts to load data to buffer after 3T delay time)
            SET_DP_MST_RX_REG_UPSTREAM_REPLY();

            // Set MSG Timeout Timer Event Before 2003h IRQ Setting
            CLR_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT();
            ScalerDpMstRxReactiveTimerEvent(_DP_MST_RX_DOWN_REPLY_MSG_TIME_OUT, ScalerDpMstRxGetTimerEvent(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

            // CLR DOWN_REP_MSG_RDY IRQ Flag
            CLR_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ_FLAG();

            // Enable DOWN_REP_MSG_RDY IRQ
            ScalerDpMstRxSetMsgReadyIrqEnable(enumInputPort, _DP_DOWN_REPLY_MSG, _ENABLE);

            // Set Down Reply MSG Ready Bit of DPCD Table
            SET_DP_MST_RX_REG_W1C_DPCD_MIRROR_BIT(0x00, 0x20, 0x03, ~_BIT4, _BIT4);

            // Gen HPD With Duration 1 ms
            SET_DP_MST_RX_HPD_IRQ();
        }
        else
        {
            if(GET_DP_MST_RX_REPLY_POOL_FREE() == _FALSE)
            {
                // Free Reply Array
                SET_DP_MST_RX_REPLY_POOL_FREE();
            }

            if(GET_DP_MST_RX_REPLY_BUF_FREE() == _FALSE)
            {
                // Free Reply Buffer
                SET_DP_MST_RX_REPLY_BUF_FREE();
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx Down Request MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxDownRequestAnal(void)
{
    if(GET_DP_MST_RX_DOWN_REQUEST_ANAL() == _TRUE)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());

        if(ScalerDpMstRxCheckMsgCRC(_DP_DOWN_REQUEST_MSG) == _TRUE)
        {
            // Analyze Down Request MSG
            if(ScalerDpMstRxMsgAnalysis() == _TRUE)
            {
#if(_DP_TX_SUPPORT == _ON)
                if(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT())
                {
                    // Count DownRequest Msg
                    if(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() < 255)
                    {
                        SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() + 1);
                    }

                    ScalerDpMstRxReactiveTimerEvent(SEC(10), _SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
                }
#endif

                // CLR Flag
                CLR_DP_MST_RX_DOWN_REQUEST_ANAL();
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
            // CRC Error
            SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_CRC_FAILURE);

            // CLR Flag
            CLR_DP_MST_RX_DOWN_REQUEST_ANAL();
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx Down Reply MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxDownReplyAnal(void)
{
    if(GET_DP_MST_RX_DOWN_REPLY_DIRECTLY() == _TRUE)
    {
        EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

        // Clear Flag
        CLR_DP_MST_RX_DOWN_REPLY_DIRECTLY();

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if(GET_DP_MST_RX_REG_UPSTREAM_REPLY() == _FALSE)
        {
            // Set Down Reply Target Port
            SET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT(enumInputPort);

            // Message Reply
            ScalerDpMstRxDownReplyDirectlyMsg();

            // Release Down Request Buffer
            ScalerDpMstRxDownRequestBufferRelease(enumInputPort);

            //========== Release FW Memory ==============

            // Free Request Array
            SET_DP_MST_RX_REQUEST_POOL_FREE();

            //========== Set Next Action ==============

            // Set Reply MSG Ready
            SET_DP_MST_RX_DOWN_REPLY_READY();
        }
        else
        {
            // MSG error DEFER
            SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_DEFER);

            DebugMessageMst("[MST] Rx down reply proccess ERROR!!!", GET_DP_MST_RX_MSG_REQUEST_ID());
        }
    }

    if(GET_DP_MST_RX_DOWN_REPLY_BYPASS() == _TRUE)
    {
        // Clear Flag
        CLR_DP_MST_RX_DOWN_REPLY_BYPASS();

        //========== Set Next Action ==============

        // Set Reply MSG Ready
        SET_DP_MST_RX_DOWN_REPLY_READY();
    }

    if(GET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG() == _TRUE)
    {
        if(GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE)
        {
            EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

            ScalerDpRxSetBaseInputPort(enumInputPort);

            if(GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE)
            {
                // CLR Flag
                CLR_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();

                // Set Down Reply Target Port
                SET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT(enumInputPort);

                // Occupy Reply Pool
                CLR_DP_MST_RX_REPLY_POOL_FREE();

                // Disable Reply Buffer Free
                CLR_DP_MST_RX_REPLY_BUF_FREE();

                // Error Reply
                ScalerDpMstRxIllegalMsgReply();

                // Release Down Request Buffer
                ScalerDpMstRxDownRequestBufferRelease(enumInputPort);

                //========== Release FW Memory ==============

                // Free Request Array
                SET_DP_MST_RX_REQUEST_POOL_FREE();

                //========== Set Next Action ==============

                // Set Reply MSG Ready
                SET_DP_MST_RX_DOWN_REPLY_READY();
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

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx Up Request MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxUpRequestSend(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    if(GET_DP_MST_RX_UP_REQUEST_READY() == _TRUE)
    {
        // Clear Flag
        CLR_DP_MST_RX_UP_REQUEST_READY();

        enumInputPort = GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT();

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if(((GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN() == _FALSE) &&
            (GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH() == _FALSE) &&
            (GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH() == _FALSE) &&
            (GET_DP_MST_RX_MODE_STATE() == _DP_RX_MST_MODE_STATUS_ALLOCATED_PBN)))
        {
            if(GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_SINK_EVENT_NOTIFY)
            {
                SET_DP_MST_RX_UP_REQUEST_ISSUED_SINK_EVENT_ID(GET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_ID());
            }

            // CLR Read Pointer to 0
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY_BUF();

            // CLR Write Pointer to 0
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR();

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR_DONE();

            if(GET_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR_DONE() == _FALSE)
            {
                DELAY_5US();
            }
#endif

            for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(); ucIndex++)
            {
                // Fill Up Request MSG
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA(GET_DP_MST_RX_MSG_REQUEST_ARRAY(ucIndex));

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA_DONE();

                if(GET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA_DONE() == _FALSE)
                {
                    DELAY_5US();
                }
#endif
            }

            // Select To Up Request BUF Address
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_UP_REQUEST_ADDRESS();

            // Set Start and End Bit to HW Auto Mode
            SET_DP_MST_RX_REG_UPSTREAM_HW_AUTO_MODE();

            // Increasing Retry number
            INCREASE_DP_MST_RX_UP_REQUEST_RETRY_NUM();

            // Free Request Pool
            SET_DP_MST_RX_REQUEST_POOL_FREE();

            // Message Upstream Enable
            SET_DP_MST_RX_REG_UPSTREAM_REPLY();

            // Set MSG Timeout Timer Event Before 2003h IRQ Setting
            CLR_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT();
            ScalerDpMstRxReactiveTimerEvent(_DP_MST_RX_UP_REQUEST_MSG_TIME_OUT, ScalerDpMstRxGetTimerEvent(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

            // Set Timer Event
            SET_DP_MST_RX_UP_REQUEST_PROCESSING();
            ScalerDpMstRxReactiveTimerEvent(SEC(2), ScalerDpMstRxGetTimerEvent(enumInputPort, _SCALER_TIMER_EVENT_DP_UP_REQUEST_PROCESSING));

            // Clear UP_REQ_MSG_RDY Bit IRQ Flag
            CLR_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ_FLAG();

            // Enable UP_REQ_MSG_RDY Bit IRQ
            ScalerDpMstRxSetMsgReadyIrqEnable(enumInputPort, _DP_UP_REQUEST_MSG, _ENABLE);

            // Set Up Request MSG Ready Bit of DPCD Table
            SET_DP_MST_RX_REG_W1C_DPCD_MIRROR_BIT(0x00, 0x20, 0x03, ~_BIT5, _BIT5);

#if(_DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT == _ON)
            // Clear 2003h read/write flag
            ScalerDpAuxRxDpcdWildCardIntClr(enumInputPort, _AUX_RX_DPCD_WILDCARD_2003);

            // Enable 0x1000 Write INT (Down request MSG is written) to Cancel Up Request
            SET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE();
#endif

            // Gen HPD With Duration 1 ms
            SET_DP_MST_RX_HPD_IRQ();
        }
        else
        {
            // Free Request Array
            SET_DP_MST_RX_REQUEST_POOL_FREE();

            // Free Reply Buffer
            SET_DP_MST_RX_REPLY_BUF_FREE();
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx Up Reply MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxUpReplyBufferRelease(void)
{
    ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_UP_REPLY_MSG_INPUT_PORT());
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus(GET_DP_MST_RX_UP_REPLY_MSG_INPUT_PORT());

    CLR_DP_MST_RX_REG_UP_REPLY_ADDR_WRITTEN();

    // Buffer0 is processed
    if(GET_DP_MST_RX_UP_REPLY_BUF_PRIORITY() == _DP_MST_RX_UP_REPLY_BUF0)
    {
        // Clear Flag
        CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH();

        // Clear BUF0
        CLR_DP_MST_RX_REG_UP_REPLY_BUF0();

        // Defer Any Other MSGs to Prevent Priority and Using Buf Conflict
        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_MST_RX_REG_AUX_TO_MANUAL_MODE();
        }

        if((GET_DP_MST_RX_REG_UP_REPLY_ADDR_WRITTEN() == _TRUE) || (GET_DP_MST_RX_REG_UP_REPLY_BUF1_WRITE_PTR() != 0x00))
        {
            CLR_DP_MST_RX_REG_UP_REPLY_ADDR_WRITTEN();

            SET_DP_MST_RX_UP_REPLY_BUF_PRIORITY(_DP_MST_RX_UP_REPLY_BUF1);
        }
        else
        {
            SET_DP_MST_RX_UP_REPLY_BUF_PRIORITY(_DP_MST_RX_UP_REPLY_BUF0);
        }

        // Enable BUF0 to Receive MSG
        SET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE();

        if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
        {
            SET_DP_MST_RX_REG_AUX_TO_AUTO_MODE();
        }
    }
    else
    {
        // Clear BUF1
        CLR_DP_MST_RX_REG_UP_REPLY_BUF1();

        // Enable BUF1 to Receive MSG
        SET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE();

        SET_DP_MST_RX_UP_REPLY_BUF_PRIORITY(_DP_MST_RX_UP_REPLY_BUF0);
    }
}

//--------------------------------------------------
// Description  : Rx Up Reply MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxUpReplyReceive(void)
{
    for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
        {
            continue;
        }

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if(GET_DP_MST_RX_UP_REPLY_BUF_PRIORITY() == _DP_MST_RX_UP_REPLY_BUF0)
        {
            if(GET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH() == _TRUE)
            {
                if(GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE)
                {
                    // Occupy Reply Pool
                    CLR_DP_MST_RX_REPLY_POOL_FREE();

                    // CLR Flag
                    CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH();

                    // Set BUF0 Read PTR to 0
                    SET_DP_MST_RX_REG_UP_REPLY_BUF0_RDAD_PTR(0);

                    // Get Up Reply MSG and Using Reply Pool to Analysis
                    for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_LENGTH(); ucIndex++)
                    {
                        SET_DP_MST_RX_MSG_REPLY_ARRAY(ucIndex, GET_DP_MST_RX_REG_UP_REPLY_BUF0_DATA());
                    }

                    // Select to Header 0
                    SET_DP_MST_RX_REG_UP_REPLY_HEADER0_INFO();

                    SET_DP_MST_RX_UP_REPLY_MSG_INPUT_PORT(enumInputPort);

                    // Analysis Up Reply MSG
                    SET_DP_MST_RX_UP_REPLY_ANAL();
                }
                else
                {
                    return _FALSE;
                }
            }
        }
        else
        {
            if(GET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_FINISH() == _TRUE)
            {
                if(GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE)
                {
                    // Occupy Reply Pool
                    CLR_DP_MST_RX_REPLY_POOL_FREE();

                    // CLR Flag
                    CLR_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_FINISH();

                    // Set BUF1 Up Reply Read PTR to 0
                    SET_DP_MST_RX_REG_UP_REPLY_BUF1_RDAD_PTR(0);

                    // Get Up Reply MSG and Using Reply Pool to Analysis
                    for(BYTE ucIndex = 0; ucIndex < GET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_LENGTH(); ucIndex++)
                    {
                        SET_DP_MST_RX_MSG_REPLY_ARRAY(ucIndex, GET_DP_MST_RX_REG_UP_REPLY_BUF1_DATA());
                    }

                    // Select to Header 1
                    SET_DP_MST_RX_REG_UP_REPLY_HEADER1_INFO();

                    SET_DP_MST_RX_UP_REPLY_MSG_INPUT_PORT(enumInputPort);

                    // Analysis Up Reply MSG
                    SET_DP_MST_RX_UP_REPLY_ANAL();
                }
                else
                {
                    return _FALSE;
                }
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx Up Request MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxUpRequestAnal(void)
{
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
    if(GET_DP_MST_RX_GEN_UP_REQUEST_MSG() != _DP_MSG_NONE)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT());

        if(GET_DP_MST_RX_HOT_PLUG_STATUS() == _TRUE)
        {
            if((GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE) && (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
            {
                EnumDpMstPort enumPortNum = GET_DP_MST_RX_UP_REQUEST_QUEUE_PORT_NUM(GET_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE());

                switch(GET_DP_MST_RX_GEN_UP_REQUEST_MSG())
                {
                    case _DP_MSG_SINK_EVENT_NOTIFY:

                        SET_DP_MST_RX_UP_REQUEST_ISSUED_ID(_DP_MSG_SINK_EVENT_NOTIFY);

                        // Occupy Reply Pool
                        CLR_DP_MST_RX_REQUEST_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        CLR_DP_MST_RX_GEN_UP_REQUEST_MSG();

                        //========== Set MSG Header ==============

                        // Set LCT = 1
                        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(1);

                        // Set LCR = 6
                        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(0x06);

                        // Set Broadcast and Path Bit
                        SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(_ENABLE);
                        SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(_DISABLE);

                        // Set MSG Body Length
                        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(20);

                        //========== Set MSG Body ==============

                        SET_DP_MST_RX_MSG_REQUEST_ID(_DP_MSG_SINK_EVENT_NOTIFY);
                        SET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_PORT_NUM(enumPortNum);

#if(_DP_SUPPORT == _ON)
                        for(BYTE ucIndex = 0; ucIndex < 16; ucIndex++)
                        {
                            SET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_GUID(ucIndex, GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, (0x30 + ucIndex)));
                        }
#endif

                        SET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_ID(ScalerDpMstRxGetVirtualDpSinkEventNotify(GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(), enumPortNum));
                        SET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_ZEROS();

                        //========== Set Next Action ==============

                        // Call Dp Rx to Analize Received Up_Request MSG
                        SET_DP_MST_RX_UP_REQUEST_ANAL();

                        break;

                    default:
                        break;
                }
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
            CLR_DP_MST_RX_GEN_UP_REQUEST_MSG();
        }
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    if(GET_DP_MST_TX_GEN_UP_REQUEST_MSG() != _DP_MSG_NONE)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT());

        if(GET_DP_MST_RX_HOT_PLUG_STATUS() == _TRUE)
        {
            if((GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE) && (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
            {
                switch(GET_DP_MST_TX_GEN_UP_REQUEST_MSG())
                {
                    case _DP_MSG_CONNECTION_STATUS_NOTIFY:

                        SET_DP_MST_RX_UP_REQUEST_ISSUED_ID(_DP_MSG_CONNECTION_STATUS_NOTIFY);

                        // Occupy Reply Pool
                        CLR_DP_MST_RX_REQUEST_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        CLR_DP_MST_TX_GEN_UP_REQUEST_MSG();

                        // In MST mode, Bit2 : STREAM_STATUS_CHANGED is set to 1 if DPTX connect a new downstream device.
                        // Indicates the source must re-check the Stream Status with the QUERY_STREAM_ENCRYPTION_STATUS message.
                        SET_DP_MST_RX_REG_W1C_DPCD_INFO(0x00, 0x20, 0x05, (GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x20, 0x05) | _BIT2));

                        if(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE() == _TX_UP_REQ_QUEUE_BYPASS)
                        {
                            //========== Set MSG Header ==============

                            // Set LCT = 1
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCT(_CSN_QUEUE_ENTRY_0));

                            // Set LCR - 1
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LCR(_CSN_QUEUE_ENTRY_0) - 1);

                            // Set Broadcast and Path Bit
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_BROADCAST(_CSN_QUEUE_ENTRY_0));
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_PATH(_CSN_QUEUE_ENTRY_0));

                            // Set MSG Body Length
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_LENGTH(_CSN_QUEUE_ENTRY_0));

                            //========== Set MSG Body ==============
                            SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_BODY(GET_DP_MST_TX_BYPASS_CSN_BACKUP_MSG_BODY(_CSN_QUEUE_ENTRY_0));
                        }
                        else
                        {
                            //========== Set MSG Header ==============

                            // Set LCT = 1
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(1);

                            // Set LCR = 6
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(0x06);

                            // Set Broadcast and Path Bit
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(_ENABLE);
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(_DISABLE);

                            // Set MSG Body Length
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(19);

                            //========== Set MSG Body ==============

                            SET_DP_MST_TX_MSG_REQUEST_ID(_DP_MSG_CONNECTION_STATUS_NOTIFY);
                            SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PORT_NUM(_DP_PORT1);

#if(_DP_SUPPORT == _ON)
                            for(BYTE ucIndex = 0; ucIndex < 16; ucIndex++)
                            {
                                SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_GUID(ucIndex, GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, (0x30 + ucIndex)));
                            }
#endif
                            SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_INPUT_PORT(_DP_MST_RX_OUTPUT_PORT);
                            SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_ZEROS();

                            if((ScalerDpMstTxCsnEventGetStatus(_TX_UP_REQ_QUEUE_SELF_GEN) == _CONNECT_STATUS_PLUG))
                            {
                                SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PLUG_STATUS(_DP_PLUG);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                                if(ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(), _DP_PORT1) == _ENABLE)
                                {
                                    SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_LEGACY_PLUG_STATUS(_DP_UNPLUG);

                                    // Set Physical Portx Message Capability
                                    SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_MSG_CAP(_DP_TX_MSG_SUPPORT);

                                    // Set Physical Portx Peer Device Type
                                    SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PEER_DEVICE_TYPE(_DP_TX_MST_OR_SST_BRANCH_DOWNSTREAM);
                                }
                                else
#endif
                                {
                                    SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_LEGACY_PLUG_STATUS(GET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS());
                                    SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_MSG_CAP(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS());
                                    SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PEER_DEVICE_TYPE(GET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE());
                                }
                            }
                            else
                            {
                                SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PLUG_STATUS(_DP_UNPLUG);
                                SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_LEGACY_PLUG_STATUS(_DP_UNPLUG);
                                SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_MSG_CAP(_DP_TX_MSG_NO_SUPPORT);
                                SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_PEER_DEVICE_TYPE(_DP_TX_NO_DEVICE);
                            }

                            if(ScalerDpMstTxCsnEventGetStatus(_TX_UP_REQ_QUEUE_SELF_GEN) == _CONNECT_STATUS_PLUG)
                            {
                                // Set 8s Timer to Wait that Source Rebuild Topology
                                ScalerDpMstRxActiveTimerEvent(SEC(8), _SCALER_TIMER_EVENT_DP_TX_FORCE_REBUILD_TOPOLOGY_EVENT);
                            }
                            else
                            {
                                // Reset Tx Payloads to Avoid Conflict Caused by The Mismatch of CSN and HPD Status
                                if((GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT) &&
                                   (GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG))
                                {
                                    BYTE ucData = 0;

                                    // Clear Payload ID Only if Downstream PID Table is Not Empty
                                    if(ScalerDpAuxTxNativeRead(0x00, 0x02, 0xC1, 1, &ucData) == _TRUE)
                                    {
                                        if(ucData != 0x00)
                                        {
                                            // Set Flag to Gen Clear ID Table Msg
                                            ScalerDpMstTxDownRequestSelfGen(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);
                                        }
                                    }
                                }
                            }
                        }

                        //========== Set Next Action ==============

                        // Call Dp Rx to Analize Received Up_Request MSG
                        SET_DP_MST_RX_UP_REQUEST_ANAL();

                        break;

                    case _DP_MSG_SINK_EVENT_NOTIFY:

                        SET_DP_MST_RX_UP_REQUEST_ISSUED_ID(_DP_MSG_SINK_EVENT_NOTIFY);

                        // Occupy Reply Pool
                        CLR_DP_MST_RX_REQUEST_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        CLR_DP_MST_TX_GEN_UP_REQUEST_MSG();

                        if(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE() == _TX_UP_REQ_QUEUE_BYPASS)
                        {
                            //========== Set MSG Header ==============

                            // Set LCT = 1
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_LCT(_SEN_QUEUE_ENTRY_0));

                            // Set LCR - 1
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_LCR(_SEN_QUEUE_ENTRY_0) - 1);

                            // Set Broadcast and Path Bit
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_BROADCAST(_SEN_QUEUE_ENTRY_0));
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_PATH(_SEN_QUEUE_ENTRY_0));

                            // Set MSG Body Length
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_LENGTH(_SEN_QUEUE_ENTRY_0));

                            //========== Set MSG Body ==============
                            SET_DP_MST_TX_REQUEST_MSG_CONNECTION_STATUS_BODY(GET_DP_MST_TX_BYPASS_SEN_BACKUP_MSG_BODY(_SEN_QUEUE_ENTRY_0));
                        }
                        else
                        {
                            BYTE ucByte = 0;

                            //========== Set MSG Header ==============

                            // Set Broadcast and Path Bit
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(_ENABLE);
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(_DISABLE);

                            // Set MSG Body Length
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(20);

                            // Set LCT = 1
                            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(1);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                            if(ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(), _DP_PORT1) == _ENABLE)
                            {
                                // Set LCR = 5
                                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(0x05);
                            }
                            else
#endif
                            {
                                // Set LCR = 6
                                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(0x06);
                            }

                            //========== Set MSG Body ==============

                            SET_DP_MST_TX_MSG_REQUEST_ID(_DP_MSG_SINK_EVENT_NOTIFY);
                            SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_PORT_NUM(_DP_PORT1);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                            if(ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(), _DP_PORT1) == _ENABLE)
                            {
                                for(ucByte = 0; ucByte < 16; ucByte++)
                                {
                                    SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_GUID(ucByte, ScalerDpMstRxGetVirtualDpcdInfo(GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(), _DP_PORT1, 0x00, 0x00, (0x30 + ucByte)));
                                }
                            }
                            else
#endif
                            {
                                for(ucByte = 0; ucByte < 16; ucByte++)
                                {
                                    SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_GUID(ucByte, GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, (0x30 + ucByte)));
                                }
                            }

                            SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_ID(GET_DP_MST_TX_SINK_EVENT_ID());
                            SET_DP_MST_TX_REQUEST_MSG_SINK_EVENT_ZEROS();
                        }

                        //========== Set Next Action ==============

                        // Call Dp Rx to Analize Received Up_Request MSG
                        SET_DP_MST_RX_UP_REQUEST_ANAL();

                        break;

                    default:
                        break;
                }
            }
            else
            {
                return _FALSE;
            }
        }
        else
        {
            CLR_DP_MST_TX_GEN_UP_REQUEST_MSG();
        }
    }
#endif

    if(GET_DP_MST_RX_UP_REQUEST_ANAL() == _TRUE)
    {
        // Clear Flag
        CLR_DP_MST_RX_UP_REQUEST_ANAL();

        // Bypass Up Request MSG
        SET_DP_MST_RX_UP_REQUEST_READY();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx Up Reply MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxUpReplyAnal(void)
{
    if(GET_DP_MST_RX_UP_REPLY_ANAL() == _TRUE)
    {
        CLR_DP_MST_RX_UP_REPLY_ANAL();

        // Release Up Reply BUF
        ScalerDpMstRxUpReplyBufferRelease();

        // Free Reply Pool
        SET_DP_MST_RX_REPLY_POOL_FREE();
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Msg Transition
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMstRxCheckMsgTransition(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(ScalerDpRxGetMstCapability(enumInputPort) == _TRUE)
    {
        if(ScalerDpMstRxCheckMsgBufferFree(enumInputPort) == _FALSE)
        {
            return _TRUE;
        }

#if(_DP_TX_SUPPORT == _ON)
        if(enumInputPort == GET_DP_RX_MAIN_PORT())
        {
            if(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() != 0)
            {
                return _TRUE;
            }

            if(GET_DP_MST_TX_RECEIVED_MSG_COUNT() != 0)
            {
                return _TRUE;
            }

            if(GET_DP_TX_HDCP_AUTH_HOLD() == _TRUE)
            {
                return _TRUE;
            }
        }
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Tx Mst Msg Count Check Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxMsgCountResetEvent(void)
{
    EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

    ScalerDpRxSetBaseInputPort(enumInputPort);

    // Release Down Request Buffer
    ScalerDpMstRxDownRequestBufferRelease(enumInputPort);

    ScalerTimerCancelTimerEvent(ScalerDpMstRxGetTimerEvent(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

#if(_DP_TX_SUPPORT == _ON)
    if(enumInputPort == GET_DP_RX_MAIN_PORT())
    {
        SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(0);

        CLR_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
    }
#endif
}

//--------------------------------------------------
// Description  : Rx MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxMsgTimeoutEvent(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(GET_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT() == _TRUE)
    {
        CLR_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT();

        return;
    }

    // Down Reply Ready bit unclear
    if(GET_DP_MST_RX_REG_UPSTREAM_REPLY_DOWN_REPLY_ADDRESS() == _TRUE)
    {
        if(GET_DP_MST_RX_DOWN_REPLY_RETRY_NUM() >= _DP_MST_DOWN_REPLY_MSG_TIME_OUT_RETRY_MAX)
        {
            // Disable DOWN_REP_MSG_RDY Bit INT
            ScalerDpMstRxSetMsgReadyIrqEnable(enumInputPort, _DP_DOWN_REPLY_MSG, _DISABLE);

            // Clear DOWN_REP_MSG_RDY Bit of DPCD Table
            ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x03, ~_BIT4, 0x00);

            // Clear Buffer
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY_BUF();

            // Disable Message Upstream
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY();

            // Free Reply Buffer
            SET_DP_MST_RX_REPLY_BUF_FREE();
        }
        else
        {
            INCREASE_DP_MST_RX_DOWN_REPLY_RETRY_NUM();

            // Set Timer Event
            ScalerDpMstRxReactiveTimerEvent(_DP_MST_RX_DOWN_REPLY_MSG_TIME_OUT, ScalerDpMstRxGetTimerEvent(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

            // Gen HPD With Duration 1 ms
            SET_DP_MST_RX_HPD_IRQ();
        }
    }

    // Up Request Ready bit unclear
    if(GET_DP_MST_RX_REG_UPSTREAM_REPLY_UP_REQUEST_ADDRESS() == _TRUE)
    {
        // Disable UP_REQ_MSG_RDY INT
        ScalerDpMstRxSetMsgReadyIrqEnable(enumInputPort, _DP_UP_REQUEST_MSG, _DISABLE);

        // Clear UP_REQ_MSG_RDY Bit of DPCD Table
        ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(enumInputPort, 0x00, 0x20, 0x03, ~_BIT5, 0x00);

        // Clear Buffer
        CLR_DP_MST_RX_REG_UPSTREAM_REPLY_BUF();

        // Message Upstream Disable
        CLR_DP_MST_RX_REG_UPSTREAM_REPLY();

        // Disable 0x1000 Write INT
        CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE();

        // Free Reply Pool
        SET_DP_MST_RX_REPLY_BUF_FREE();
    }
}

//--------------------------------------------------
// Description  : Rx MSG Processes for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxDownRequestEventProc(void)
{
    bit bIllegal = _FALSE;
    static bit sbEdidSegIsWritten = _FALSE;
    BYTE ucTemp = 0;
    BYTE ucLength = 0;
    BYTE pucData[4] = {0};
    WORD usData = 0;
    EnumDpStreamNum enumDpStream = _DP_ST_NONE;
    EnumDpStreamSourceNum enumDpSourceTemp = _DP_NO_SOURCE;
    static WORD susEdidReadPosition = 0;

    enumDpStream = enumDpStream;
    enumDpSourceTemp = enumDpSourceTemp;

    if(GET_DP_MST_RX_EVENT() != _DP_RX_NONE_EVENT)
    {
        EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();

        ScalerDpRxSetBaseInputPort(enumInputPort);

        switch(GET_DP_MST_RX_EVENT())
        {
            case _DP_RX_DPCD_READ_REQUEST:

                for(ucTemp = 0; ucTemp < GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ(); ucTemp++)
                {
                    SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(ucTemp) = GET_DP_MST_RX_REG_DPCD_INFO(
                        GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H(),
                        GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M(),
                        GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L() + ucTemp);
                }

                // Set Native Reply Message
                SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                break;

            case _DP_RX_DPCD_WRITE_REQUEST:

                // Set Native Reply Message
                SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                break;

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            case _DP_RX_VIRTUAL_DPCD_READ_REQUEST:

                for(ucTemp = 0; ucTemp < GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ(); ucTemp++)
                {
                    SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(ucTemp) = ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort,
                                                                                                                 GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(),
                                                                                                                 GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H(),
                                                                                                                 GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M(),
                                                                                                                 GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L() + ucTemp);
                }

                // Set Native Reply Message
                SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                break;

            case _DP_RX_VIRTUAL_DPCD_WRITE_REQUEST:

                for(ucTemp = 0; ucTemp < GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_NUM_OF_WRITE(); ucTemp++)
                {
                    ScalerDpMstRxSetVirtualDpcdInfoBySrc(enumInputPort,
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
                    ScalerDpMstRxDscSupportSwitch(enumInputPort);
                }

                // Set Native Reply Message
                SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                break;
#endif

            case _DP_RX_NATIVE_PORT8_DISPLAY:

                ScalerDpMacDphyRxSetStreamAllocateInfo(enumInputPort, _DP_PORT8, ScalerDpMstRxSearchMatchStream(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()));

                if(ScalerDpRxGetMacSwitch(ScalerDpMstRxPortNumDxMapping(_DP_PORT8)) != _DP_MAC_NONE)
                {
                    enumDpSourceTemp = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(ScalerDpRxDxMacSourceMapping(ScalerDpMstRxPortNumDxMapping(_DP_PORT8)));
                    enumDpStream = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT8);

                    // Set Stream Mux Source
                    ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumDpSourceTemp, enumDpStream);
                }

                SET_DP_MST_RX_REG_WR_DPCD_INFO(0x00, 0x06, 0x00, 0x01);

                break;

            case _DP_RX_NATIVE_PORT8_DELETE:

                for(enumDpSourceTemp = _DP_ST_SOURCE1; enumDpSourceTemp <= _DP_ST_SOURCE_END; enumDpSourceTemp++)
                {
                    if(ScalerDpMstRxGetSourceMuxBackup(enumInputPort, enumDpSourceTemp) == ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT8))
                    {
                        ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumDpSourceTemp, _DP_ST_NONE);

                        break;
                    }
                }

                ScalerDpMacDphyRxSetStreamAllocateInfo(enumInputPort, _DP_PORT8, _DP_ST_NONE);

                break;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            case _DP_RX_NATIVE_PORT9_DISPLAY:

                ScalerDpMacDphyRxSetStreamAllocateInfo(enumInputPort, _DP_PORT9, ScalerDpMstRxSearchMatchStream(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()));

                if(ScalerDpRxGetMacSwitch(ScalerDpMstRxPortNumDxMapping(_DP_PORT9)) != _DP_MAC_NONE)
                {
                    enumDpSourceTemp = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(ScalerDpRxDxMacSourceMapping(ScalerDpMstRxPortNumDxMapping(_DP_PORT9)));
                    enumDpStream = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT9);

                    // Set Stream Mux Source
                    ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumDpSourceTemp, enumDpStream);
                }

                SET_DP_MST_RX_REG_WR_DPCD_INFO(0x00, 0x06, 0x00, 0x01);

                break;

            case _DP_RX_NATIVE_PORT9_DELETE:

                for(enumDpSourceTemp = _DP_ST_SOURCE1; enumDpSourceTemp <= _DP_ST_SOURCE_END; enumDpSourceTemp++)
                {
                    if(ScalerDpMstRxGetSourceMuxBackup(enumInputPort, enumDpSourceTemp) == ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT9))
                    {
                        ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumDpSourceTemp, _DP_ST_NONE);

                        break;
                    }
                }

                ScalerDpMacDphyRxSetStreamAllocateInfo(enumInputPort, _DP_PORT9, _DP_ST_NONE);

                break;
#endif
#if(_DP_TX_SUPPORT == _ON)

            case _DP_RX_REMOTE_DAISY_TRANSPORT:

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if((GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_READY) || (GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_WAIT))
#else
                if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
#endif
                {
                    enumDpStream = ScalerDpMstRxSearchMatchStream(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

                    for(enumDpSourceTemp = _DP_ST_SOURCE_DAISY_START; enumDpSourceTemp <= _DP_ST_SOURCE_DAISY_END; enumDpSourceTemp++)
                    {
                        if(ScalerDpMacTxGetDaisySourceMuxBackup(enumDpSourceTemp) == enumDpStream)
                        {
                            break;
                        }
                        else if(ScalerDpMacTxGetDaisySourceMuxBackup(enumDpSourceTemp) == _DP_ST_NONE)
                        {
                            // Set Stream Mux Source
                            ScalerDpMacTxSetDaisySourceMuxBackup(enumDpSourceTemp, enumDpStream);

                            break;
                        }
                    }

                    ScalerDpMstRxSetTxStreamSourceMux();

                    SET_DP_MST_RX_REG_WR_DPCD_INFO(0x00, 0x06, 0x00, 0x01);

                    // Set Tx Stream Source Type
                    if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_MST)
                    {
                        ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_MST);
                    }

                    if(GET_DP_MAC_MST2SST_ENABLE() == _ENABLE)
                    {
                        CLR_DP_MAC_MST2SST_ENABLE();
                    }

                    ScalerDpMstTxMst2SstInitialSetting();
                }
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                else if(GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() != _LINK_ESTABLISH_FAIL)
#else
                else if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_FAIL)
#endif
                {
                    return _FALSE;
                }

                break;

            case _DP_RX_REMOTE_DAISY_DELETE:

                enumDpStream = ScalerDpMstRxSearchMatchStream(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

                for(enumDpSourceTemp = _DP_ST_SOURCE_DAISY_START; enumDpSourceTemp <= _DP_ST_SOURCE_DAISY_END; enumDpSourceTemp++)
                {
                    if(ScalerDpMacTxGetDaisySourceMuxBackup(enumDpSourceTemp) == enumDpStream)
                    {
                        // Set Stream Mux Source
                        ScalerDpMacTxSetDaisySourceMuxBackup(enumDpSourceTemp, _DP_ST_NONE);

                        break;
                    }
                }

                break;

            case _DP_RX_REMOTE_MST2SST_TRANSPORT:

                if(ScalerDpMacTxLinkStatusCheck() == _FAIL)
                {
                    SET_DP_TX_FORCE_LINK_TRAINING();
                }

                ScalerDpMacDphyRxSetStreamAllocateInfo(enumInputPort, _DP_PORT1, ScalerDpMstRxSearchMatchStream(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()));

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
                if(ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST) != _DP_MAC_NONE)
                {
                    enumDpSourceTemp = ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(_STREAM_SOURCE_MST2SST);
                    enumDpStream = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT1);

                    // Set Stream Mux Source
                    ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumDpSourceTemp, enumDpStream);
                }
#endif
                // Set Stream Mux Source for Video
                ScalerDpMacTxSetDaisySourceMuxBackup(_DP_ST_SOURCE1, ScalerDpMstRxSearchMatchStream(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()));

                ScalerDpMstRxSetTxStreamSourceMux();

                ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);

                SET_DP_MAC_MST2SST_ENABLE();

                ScalerDpMstTxMst2SstInitialSetting();

                break;

            case _DP_RX_REMOTE_MST2SST_DELETE:

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
                // Set Stream Mux Source
                for(enumDpSourceTemp = _DP_ST_SOURCE1; enumDpSourceTemp <= _DP_ST_SOURCE_END; enumDpSourceTemp++)
                {
                    if(ScalerDpMstRxGetSourceMuxBackup(enumInputPort, enumDpSourceTemp) == ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT1))
                    {
                        ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumDpSourceTemp, _DP_ST_NONE);

                        break;
                    }
                }
#endif
                ScalerDpMacDphyRxSetStreamAllocateInfo(enumInputPort, _DP_PORT1, _DP_ST_NONE);

                // Set Stream Mux Source
                ScalerDpMacTxSetDaisySourceMuxBackup(_DP_ST_SOURCE1, _DP_ST_NONE);

                ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);

                CLR_DP_MAC_MST2SST_ENABLE();

                break;

#endif // End of #if(_DP_TX_SUPPORT == _ON)

            case _DP_RX_I2C_READ:

                // Clear the flag of EDID segmet been written
                sbEdidSegIsWritten = _FALSE;

                // The first position of I2C_Device_Identifier
                pucData[0] = 2;

                if(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE() > 0)
                {
                    susEdidReadPosition = 0;

                    // Handling Wtire Command
                    for(pucData[1] = 1; pucData[1] <= GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE(); pucData[1]++)
                    {
                        // Get Write I2C Device ID
                        switch(g_unDpMstRxRequestPool.pucData[pucData[0]])
                        {
                            case _DP_MSG_IIC_DEVICE_EDID_SEGMENT:
                            case _DP_MSG_IIC_DEVICE_EDID:
                            case _DP_MSG_IIC_DEVICE_DDCCI:

                                break;

                            default:

                                bIllegal = _TRUE;

                                break;
                        }

                        // Get Number_Of_Bytes_To_Write
                        if((ucLength = g_unDpMstRxRequestPool.pucData[pucData[0] + 1]) > 0)
                        {
                            // Get data (which is illegal if > 255)
                            for(pucData[2] = 1; pucData[2] < ucLength; pucData[2]++)
                            {
                                if(g_unDpMstRxRequestPool.pucData[pucData[0] + 1 + pucData[2]] != 0)
                                {
                                    bIllegal = _TRUE;
                                    break;
                                }
                            }

                            ucTemp = g_unDpMstRxRequestPool.pucData[pucData[0] + 1 + ucLength];

                            // Get Write I2C Device ID
                            switch(g_unDpMstRxRequestPool.pucData[pucData[0]])
                            {
                                case _DP_MSG_IIC_DEVICE_EDID_SEGMENT:

                                    if(ucTemp <= 1)
                                    {
                                        susEdidReadPosition = ucTemp * 256;
                                    }
                                    else
                                    {
                                        bIllegal = _TRUE;
                                    }

                                    break;

                                // Set Offset
                                case _DP_MSG_IIC_DEVICE_EDID:

                                    if((susEdidReadPosition + ucTemp) < ScalerDpMstRxGetEdidRamSize(ScalerDpMstRxPortNumDxMapping(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM())))
                                    {
                                        susEdidReadPosition += ucTemp;
                                    }
                                    else
                                    {
                                        bIllegal = _TRUE;
                                    }

                                    break;

                                case _DP_MSG_IIC_DEVICE_DDCCI:

                                    break;

                                default:

                                    bIllegal = _TRUE;

                                    break;
                            }
                        }

                        if(bIllegal == _TRUE)
                        {
                            SET_DP_MST_RX_REMOTE_I2C_READ_FAIL();
                            SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                            SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_REASON(_I2C_NAK);
                            SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_TRANSACTION(pucData[1]);

                            SET_DP_MST_RX_REPLY_POOL_FREE();
                            SET_DP_MST_RX_REPLY_BUF_FREE();
                            SET_DP_MST_RX_EVENT(_DP_RX_NONE_EVENT);

                            return _TRUE;
                        }

                        // Point to next I2C_Device_Identifier
                        pucData[0] += (3 + g_unDpMstRxRequestPool.pucData[pucData[0] + 1]);
                    }
                }

                // Number of Bytes To Read
                ucLength = (g_unDpMstRxRequestPool.pucData[pucData[0] + 1]);

                // Handling Read Command
                switch(g_unDpMstRxRequestPool.pucData[pucData[0]])
                {
                    case _DP_MSG_IIC_DEVICE_EDID:

                        memcpy(g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead, (ScalerDpMstRxGetEdidRamAddress(ScalerDpMstRxPortNumDxMapping(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM())) + susEdidReadPosition), ucLength);

                        susEdidReadPosition += ucLength;

                        if(susEdidReadPosition >= ScalerDpMstRxGetEdidRamSize(ScalerDpMstRxPortNumDxMapping(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM())))
                        {
                            // Initialize the ReadPosition while EOF
                            susEdidReadPosition = 0;
                        }

                        // Set Number Of Byte Read
                        SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(ucLength);

                        // Set Message Body Length
                        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(3 + ucLength);

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                        break;

                    case _DP_MSG_IIC_DEVICE_DDCCI:

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_DP_MST_RX_INTERCEPT_PORT9_DDCCI_MSG_SUPPORT == _ON)
                        // Reply ACK NULL MSG for Port 9
                        if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9)
                        {
                            ucLength = 3;

                            // Reply Null Msg
                            g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[0] = 0x6E;
                            g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[1] = 0x80;
                            g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[2] = (0x50 ^ 0x6E ^ 0x80);
                        }
                        else
#endif
#endif
                        {
                            for(ucTemp = 0; ucTemp < ucLength; ucTemp++)
                            {
                                if(ucTemp < _DDCCI_TXBUF_LENGTH)
                                {
                                    g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[ucTemp] = g_pucMcuDdcciTxBuf[ucTemp];
                                }
                                else
                                {
                                    g_unDpMstRxReplyPool.stRemoteI2CRead.pucI2CRead[ucTemp] = 0;
                                }
                            }
                        }

                        // Set Number Of Byte Read
                        SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(ucLength);

                        // Set Message Body Length
                        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(3 + ucLength);

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                        break;

                    default:

                        // Release Down Request Buffer
                        ScalerDpMstRxDownRequestBufferRelease(enumInputPort);

                        // Free Request Array
                        SET_DP_MST_RX_REQUEST_POOL_FREE();

                        // Set Reply Pool Free
                        SET_DP_MST_RX_REPLY_POOL_FREE();

                        // Set Reply Buffer Free
                        SET_DP_MST_RX_REPLY_BUF_FREE();

#if(_DP_TX_SUPPORT == _ON)
                        if(enumInputPort == GET_DP_RX_MAIN_PORT())
                        {
                            SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() - 1);

                            if(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() == 0)
                            {
                                // Cancel Timer Event
                                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
                            }
                        }
#endif
                        break;
                }

                break;

            case _DP_RX_I2C_WRITE:

                switch(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_WRITE_DEVICE_ID())
                {
                    case _DP_MSG_IIC_DEVICE_EDID_SEGMENT:

                        if(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() > 0)
                        {
                            usData = GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() - 1) * 256;

                            if(usData < ScalerDpMstRxGetEdidRamSize(ScalerDpMstRxPortNumDxMapping(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM())))
                            {
                                susEdidReadPosition = usData;

                                sbEdidSegIsWritten = _TRUE;
                            }
                            else
                            {
                                susEdidReadPosition = 0;
                            }
                        }
                        else
                        {
                            susEdidReadPosition = 0;
                        }

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                        break;

                    case _DP_MSG_IIC_DEVICE_EDID:

                        if(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() > 0)
                        {
                            if(sbEdidSegIsWritten == _TRUE)
                            {
                                susEdidReadPosition += GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() - 1);
                            }
                            else
                            {
                                susEdidReadPosition = GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() - 1);
                            }

                            if(susEdidReadPosition >= ScalerDpMstRxGetEdidRamSize(ScalerDpMstRxPortNumDxMapping(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM())))
                            {
                                susEdidReadPosition = 0;
                            }
                        }
                        else
                        {
                            if(sbEdidSegIsWritten == _FALSE)
                            {
                                susEdidReadPosition = 0;
                            }
                        }

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                        break;

                    case _DP_MSG_IIC_DEVICE_DDCCI:

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_DP_MST_RX_INTERCEPT_PORT9_DDCCI_MSG_SUPPORT == _ON)
                        // Reply ACK without Writing Anything for Port 9
                        if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() != _DP_PORT9)
#endif
#endif
                        {
                            BYTE ucWriteNum = GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE();

                            if(ucWriteNum <= _DDCCI_RXBUF_LENGTH)
                            {
#if((_OGC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_OCC_FUNCTION == _ON))
                                if(ScalerMcuDdcciColorCalibrationCheckDisplayMode() == _TRUE)
                                {
                                    for(BYTE ucIndex = 0; ucIndex < ucWriteNum; ucIndex++)
                                    {
                                        g_pucMcuDdcciRxBuf[ucIndex] = GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(ucIndex);
                                    }
                                }
                                else
#endif
                                {
                                    for(BYTE ucIndex = 0; ucIndex < ucWriteNum; ucIndex++)
                                    {
                                        g_ppucMcuDdcciGroupRxBuf[0][ucIndex] = GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(ucIndex);
                                    }
                                }

                                SET_RUN_DDCCI0_COMMAND(_SUCCESS);
                                SET_RUN_DDCCI_COMMAND_SRC(_DDCCI0, _DDCCI_CMD_SRC_MST);
                            }
                        }

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                        break;

                    default:

                        // Release Down Request Buffer
                        ScalerDpMstRxDownRequestBufferRelease(enumInputPort);

                        // Free Request Array
                        SET_DP_MST_RX_REQUEST_POOL_FREE();

                        // Set Reply Pool Free
                        SET_DP_MST_RX_REPLY_POOL_FREE();

                        // Set Reply Buffer Free
                        SET_DP_MST_RX_REPLY_BUF_FREE();

#if(_DP_TX_SUPPORT == _ON)
                        if(enumInputPort == GET_DP_RX_MAIN_PORT())
                        {
                            SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() - 1);

                            if(GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT() == 0)
                            {
                                // Cancel Timer Event
                                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
                            }
                        }
#endif
                        break;
                }
                break;

            case _DP_RX_QUERY_STREAM_ECRYPTION_STATUS:

                // Set Native Reply Message
                SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();

                break;

            default:
                break;
        }

        SET_DP_MST_RX_EVENT(_DP_RX_NONE_EVENT);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx MSG Analysis for DP
// Input Value  : Request Message Type
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxMsgAnalysis(void)
{
    EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();
    EnumDpStreamNum enumDpStreamNum = _DP_ST_NONE;

    enumDpStreamNum = enumDpStreamNum;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
    {
        if((GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BROADCAST() == _FALSE) &&
           ((GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() != _DP_PORT1) ||
            (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() != GET_DP_RX_MAIN_PORT())))
        {
            // Error Bad Param
            SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);

            return _TRUE;
        }

        SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BYPASS_PORT_NUM());
    }
    else
    {
        SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(_DP_PORT0);
    }

    switch(GET_DP_MST_RX_MSG_REQUEST_ID())
    {
        case _DP_MSG_GET_MESSAGE_TRANSACTION_VERSION:

            if(ScalerDpMstRxGetDpVersion(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT()) < _DP_VERSION_1_3)
            {
                // Error Bad Param
                SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);

                break;
            }

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_GET_MSG_VERSION_MSG_PORT_NUM());

                if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT0) || (GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8))
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_LINK_ADDRESS:

            if((GET_DP_MST_RX_VBIOS_BACKUP_INFO() == _TRUE) && (GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() == 1))
            {
                CLR_DP_MST_RX_VBIOS_BACKUP_INFO();

                ScalerDpMstRxResetBackupInfo(enumInputPort);
            }

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
#if(_DP_TX_SUPPORT == _ON)
                if(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT())
                {
                    // Update Sink Count
                    ScalerDpAuxRxSinkCountUpdate(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(), (GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT() + 1), _FALSE);

                    ScalerDpMstTxCsnEventReset();
                }
#endif

                if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                   (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                {
                    // CLR Flag
                    CLR_DP_MST_RX_REPLY_POOL_FREE();

                    // Disable Reply Buffer Free
                    CLR_DP_MST_RX_REPLY_BUF_FREE();

                    // Set Native Reply Message
                    SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                }
                else
                {
                    return _FALSE;
                }
            }

            break;

        case _DP_MSG_ENUM_PATH_RESOURCES:

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM());

                if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
                else if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9)
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#endif
#if(_DP_TX_SUPPORT == _ON)
                else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            // Add 1% Margin for AMD Source
            if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > (ScalerDpMstRxGetAvailablePBN(enumInputPort) + (GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() * _DP_MST_RX_PBN_MARGIN_PERCENTAGE_FOR_ALLOCATE_PAYLOAD / 100UL)))
            {
                // Error No Resource
                SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_NO_RESOURCES);

                break;
            }

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Downstream is MST with branching unit
                if((GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BYPASS_PORT_NUM() == _DP_PORT1) && (GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();

                    if(enumInputPort == GET_DP_RX_MAIN_PORT())
                    {
                        if((GET_DP_MAC_MST2SST_ENABLE() == _TRUE) && (GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() == 0))
                        {
                            ScalerDpMstRxMsgJudgeAllocatePayloadTxEvent(_DP_RX_MSG_ALLOCATE_PAYLOAD_MST2SST_PATH);
                        }
                        else
                        {
                            ScalerDpMstRxMsgJudgeAllocatePayloadTxEvent(_DP_RX_MSG_ALLOCATE_PAYLOAD_DAISY_PATH);
                        }
                    }
                }
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                // Downstream is SST sink or SST branch
                else if(ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _ENABLE)
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();

                    if(enumInputPort == GET_DP_RX_MAIN_PORT())
                    {
                        // Set Rx Event to Handle Tx Mux According to Data Path
                        ScalerDpMstRxMsgJudgeAllocatePayloadTxEvent(ScalerDpMstRxMsgJudgeTxDataPath());
                    }
                }
#endif
                else if((ScalerDpMstTxGetIncomingHPDStatus() == _DP_UNPLUG) && (GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() == 0))
                {
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();

                    if(enumInputPort == GET_DP_RX_MAIN_PORT())
                    {
                        if(GET_DP_MAC_MST2SST_ENABLE() == _TRUE)
                        {
                            ScalerDpMstRxMsgJudgeAllocatePayloadTxEvent(_DP_RX_MSG_ALLOCATE_PAYLOAD_MST2SST_PATH);
                        }
                    }
                }
                else
                {
                    // Error Bad Param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }
            // LCR = 0, Rx is Last MST with branching unit
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM());

                if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8)
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }

                    // Set Rx Event to Handle Rx Mux According to MSG Port Num
                    ScalerDpMstRxMsgJudgeAllocatePayloadRxEvent(_DP_RX_MSG_ALLOCATE_PAYLOAD_PORT8_PATH);
                }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
                else if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9)
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }

                    // Set Rx Event to Handle Rx Mux According to MSG Port Num
                    ScalerDpMstRxMsgJudgeAllocatePayloadRxEvent(_DP_RX_MSG_ALLOCATE_PAYLOAD_PORT9_PATH);
                }
#endif
#if(_DP_TX_SUPPORT == _ON)
                // Downstream is SST sink or SST branch
                else if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1)
                {
                    if(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT())
                    {
                        // Set TX DownReq Analysis
                        SET_DP_MST_TX_DOWN_REQUEST_ANAL();

                        // Set Rx Event to Handle Tx Mux According to Data Path
                        ScalerDpMstRxMsgJudgeAllocatePayloadTxEvent(ScalerDpMstRxMsgJudgeTxDataPath());
                    }
                    else
                    {
                        if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() == 0)
                        {
                            if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                               (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                            {
                                // Clear Reply Array Free Flag
                                CLR_DP_MST_RX_REPLY_POOL_FREE();

                                // Disable Reply Buffer Free
                                CLR_DP_MST_RX_REPLY_BUF_FREE();

                                // Set Native Reply Message
                                SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                            }
                            else
                            {
                                return _FALSE;
                            }
                        }
                        else
                        {
                            // Error Bad Param
                            SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                        }
                    }
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            // Clear Allocated Flag Manual Mode
            CLR_DP_MAC_DPHY_RX_MANUAL_FORCE_SET_ACT();

            // Disable Read 2C0 INT
            CLR_DP_AUX_RX_REG_2C0_IRQ_EN();

            break;

        case _DP_MSG_QUERY_PAYLOAD:

#if(_DP_TX_SUPPORT == _ON)
            // LCR > 0
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM());

                if(ScalerDpMstRxCheckIDExisted(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID()) == _TRUE)
                {
                    if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8)
                    {
                        enumDpStreamNum = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT8);

                        if((enumDpStreamNum < _HW_DP_MST_ST_SOURCE_COUNT) &&
                           (GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum) == GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID()))
                        {
                            if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                               (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                            {
                                // Clear Reply Array Free Flag
                                CLR_DP_MST_RX_REPLY_POOL_FREE();

                                // Disable Reply Buffer Free
                                CLR_DP_MST_RX_REPLY_BUF_FREE();

                                // Set Native Reply Message
                                SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                            }
                            else
                            {
                                return _FALSE;
                            }
                        }
                        else
                        {
                            // Error Bad param
                            SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                        }
                    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
                    else if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9)
                    {
                        enumDpStreamNum = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT9);

                        if((enumDpStreamNum < _HW_DP_MST_ST_SOURCE_COUNT) &&
                           (GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum) == GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID()))
                        {
                            if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                               (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                            {
                                // Clear Reply Array Free Flag
                                CLR_DP_MST_RX_REPLY_POOL_FREE();

                                // Disable Reply Buffer Free
                                CLR_DP_MST_RX_REPLY_BUF_FREE();

                                // Set Native Reply Message
                                SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                            }
                            else
                            {
                                return _FALSE;
                            }
                        }
                        else
                        {
                            // Error Bad param
                            SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                        }
                    }
#endif
#if(_DP_TX_SUPPORT == _ON)
                    else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                    {
                        // Set TX Down Request Analysis
                        SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                    }
#endif
                    else
                    {
                        // Error Bad param
                        SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                        SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                    }
                }
                else
                {
                    // Error Bad param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_CLEAR_PAYLOAD_ID_TABLE:

            // Clear Payload ID Table
            CLR_DP_AUX_RX_REG_CLEAR_PAYLOAD_ID_TABLE();

            // Reset ST1_Source ~ ST6_Source
            ScalerDpMstRxResetSourceMuxBackup(enumInputPort);

            // Reset Stream To Id Mapping
            ScalerDpMstRxResetStreamToIdMapping(enumInputPort);

            // Reset Allocate Stream Info
            ScalerDpMacDphyRxResetStreamAllocateInfo(enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT())
            {
                // Delete Tx Stream Position, Source Mux ,Stream ID mapping table, 128b132b MSA convert
                ScalerDpMacTxResetDaisyStreamPositionReg();
                ScalerDpMacTxResetDaisySourceMuxReg();
                ScalerDpMacTxResetDaisySourceMuxBackup();
                ScalerDpMacTxResetStreamToIdMapping();
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
                ScalerDpMstTxReset128b132bTo8b10bMsaConvert();
#endif
            }

            if((GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0) && (ScalerDpMstTxGetIncomingHPDStatus() == _DP_PLUG) &&
               (GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(_DP_PORT1);

                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
                if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                   (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                {
                    // Clear Reply Array Free Flag
                    CLR_DP_MST_RX_REPLY_POOL_FREE();

                    // Disable Reply Buffer Free
                    CLR_DP_MST_RX_REPLY_BUF_FREE();

                    // Set Native Reply Message
                    SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                }
                else
                {
                    return _FALSE;
                }
            }

            // Clear Allocated Flag Manual Mode
            CLR_DP_MAC_DPHY_RX_MANUAL_FORCE_SET_ACT();

            // Disable Read 2C0 INT
            CLR_DP_AUX_RX_REG_2C0_IRQ_EN();

            break;

        case _DP_MSG_POWER_UP_PHY:

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else // LCR = 0
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_POWER_UP_MSG_PORT_NUM());

                if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8) || (GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9))
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_POWER_DOWN_PHY:

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_POWER_DOWN_MSG_PORT_NUM());

                if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8) || (GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9))
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Native Reply Message
                        SET_DP_MST_RX_DOWN_REPLY_DIRECTLY();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_REMOTE_DPCD_READ:

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_PORT_NUM());

                if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8) || (GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9))
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Rep Memory Pool Free
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                        if(ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _TRUE)
                        {
                            SET_DP_MST_RX_EVENT(_DP_RX_VIRTUAL_DPCD_READ_REQUEST);
                        }
                        else
#endif
                        {
                            SET_DP_MST_RX_EVENT(_DP_RX_DPCD_READ_REQUEST);
                        }
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_REMOTE_DPCD_WRITE:

            // LCR > 0
#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else // LCR = 0
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM());

                if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8) || (GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9))
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Rep Memory Pool Free
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                        if(ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _TRUE)
                        {
                            SET_DP_MST_RX_EVENT(_DP_RX_VIRTUAL_DPCD_WRITE_REQUEST);
                        }
                        else
#endif
                        {
                            SET_DP_MST_RX_EVENT(_DP_RX_DPCD_WRITE_REQUEST);
                        }
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Bad Param
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_REMOTE_I2C_READ:

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM());

                if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8) || (GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9))
                {
#if(_DP_TX_SUPPORT == _ON)
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY() == _FALSE))
#else
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
#endif
                    {
                        // Clear Reply Pool Free
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Rx Event
                        SET_DP_MST_RX_EVENT(_DP_RX_I2C_READ);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Handler
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_REMOTE_I2C_WRITE:

#if(_DP_TX_SUPPORT == _ON)
            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Set TX DownReq Analysis
                SET_DP_MST_TX_DOWN_REQUEST_ANAL();
            }
            else
#endif
            {
                SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM());

                if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT8) || (GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT9))
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Pool Free
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Rx Event
                        SET_DP_MST_RX_EVENT(_DP_RX_I2C_WRITE);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
#if(_DP_TX_SUPPORT == _ON)
                else if((GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1) && (GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == GET_DP_RX_MAIN_PORT()))
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
#endif
                else
                {
                    // Error Handler
                    SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                    SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
                }
            }

            break;

        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            if(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() > 0)
            {
                // Error Handler
                SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
                SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
            }
            else
            {
#if(_DP_TX_SUPPORT == _ON)
                // Check Stream ID attached to which ST MUX
                enumDpStreamNum = ScalerDpMstRxSearchMatchStream(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());

                // Back-up Q_ID
                ScalerDpMstRxQueryEncryptionBackupClientId();

#if(_DP_MST_PXP_MODE_SUPPORT == _OFF)
                // Check if Stream ID of Down Request MSG is equal to Stream ID in the ST Source 1 and Stream ID is valid
                if((ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT8) != enumDpStreamNum) && (enumDpStreamNum != _DP_ST_NONE))
#else
                if((ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT8) != enumDpStreamNum) &&
                   (ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT9) != enumDpStreamNum) && (enumDpStreamNum != _DP_ST_NONE))
#endif
                {
                    // Set TX DownReq Analysis
                    SET_DP_MST_TX_DOWN_REQUEST_ANAL();
                }
                else
#endif
                {
                    if((GET_DP_MST_RX_REPLY_POOL_FREE() == _TRUE) &&
                       (GET_DP_MST_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Clear Reply Array Free Flag
                        CLR_DP_MST_RX_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_MST_RX_REPLY_BUF_FREE();

                        // Set Rx Event
                        SET_DP_MST_RX_EVENT(_DP_RX_QUERY_STREAM_ECRYPTION_STATUS);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            break;

        default:

            // Error Handler
            SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();
            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(_BAD_PARAM);
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Rx Port Link Address Info Setting
// Input Value  : Logical Port 8 or Logical Port 9
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpMstRxGetLogicalPortPlugStatus(EnumDpMstPort enumMstPortNum)
{
    enumMstPortNum = enumMstPortNum;
    return _DP_PLUG;
}

//--------------------------------------------------
// Description  : Rx Logical Port Judge
// Input Value  : Logical Port 8 or Logical Port 9 or Physical Port 1
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpMstRxValidLogicalPortJudge(EnumDpMstPort enumMstPort)
{
    if(enumMstPort == _DP_PORT8)
    {
        return _TRUE;
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(enumMstPort == _DP_PORT9)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Rx Port Number Mapping Index
// Input Value  : Logical Port 8 or Logical Port 9 or Physical Port 1
// Output Value : Byte Index
//--------------------------------------------------
BYTE ScalerDpMstRxPortNumMappingIndex(EnumInputPort enumInputPort, EnumDpMstPort enumMstPortNum)
{
    BYTE ucIndex = 0x00;
    enumInputPort = enumInputPort;

    if(enumMstPortNum >= _DP_PORT8)
    {
        ucIndex = enumMstPortNum - _DP_PORT8;
    }
    else
    {
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
        {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
            if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
            {
                // Tx Loop Back Port Can't Support Multi Logical Port So Far
                ucIndex = enumMstPortNum;
            }
            else
#endif
            {
                ucIndex = enumMstPortNum + (_DP_MST_RX_LOGICAL_PORT_NUM - 1);
            }
        }
        else
        {
            ucIndex = enumMstPortNum + (_DP_MST_RX_LOGICAL_PORT_NUM - 2);
        }
#else
        ucIndex = enumMstPortNum + (_DP_MST_RX_LOGICAL_PORT_NUM - 1);
#endif
    }

    if(ucIndex >= (_DP_MST_RX_LOGICAL_PORT_NUM + _DP_MST_RX_NUM_OF_OUTPUT_PORTS))
    {
        ucIndex = 0;
    }

    return ucIndex;
}

//--------------------------------------------------
// Description  : Rx Port Link Address Info Setting
// Input Value  : Logical Port 8 or Logical Port 9
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxPortLinkAddressInfoSetting(EnumDpMstPort enumMstPortNum)
{
    EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();
    BYTE ucIndex = ScalerDpMstRxPortNumMappingIndex(enumInputPort, enumMstPortNum);
    BYTE ucTemp = 0;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    // Set Reserve Bit to 0
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_ZEROS(ucIndex);

    // Setting Port is Output Port
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_TYPE(ucIndex, _DP_MST_RX_OUTPUT_PORT);

    // Set Logical Port Peer Device Type
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PEER_DEVICE_TYPE(ucIndex, 3);

    // Set Logical Port Number
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM(ucIndex, enumMstPortNum);

    // Set Logical Port Message Capability
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_MSG_CAP(ucIndex, 0);

    // Set Logical Port Dp Plug Status
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PLUG_STATUS(ucIndex, ScalerDpMstRxGetLogicalPortPlugStatus(enumMstPortNum));

    // Set Logical Port Legacy Plug Status
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_LEGACY_PLUG_STATUS(ucIndex, _DP_UNPLUG);

    // Set Logical Port DPCD Revision
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_DPCD_REV(ucIndex, ScalerDpMstRxGetDpVersion(GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT()));

    // Set Logical Port GUID
    for(ucTemp = 0; ucTemp < 16; ucTemp++)
    {
        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT_GUID(ucIndex, ucTemp, GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, (0x30 + ucTemp)));
    }

    // Set Logical Port Number Of Secondary Streams
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP(ucIndex, _DP_MST_RX_NUM_OF_SDP_STREAMS);

    // Set Logical Port Number Of Secondary Stream Sinks
    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP_SINK(ucIndex, _DP_MST_RX_NUM_OF_SDP_SINKS);
}


//--------------------------------------------------
// Description  : Rx MSG Reply for DP
// Input Value  : Reply Message Type
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxDownReplyDirectlyMsg(void)
{
    EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT();
    EnumDpStreamNum enumDpStreamNum = _DP_ST_NONE;
    WORD usPBN = 0;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    switch(GET_DP_MST_RX_MSG_REQUEST_ID())
    {
        case _DP_MSG_GET_MESSAGE_TRANSACTION_VERSION:

            // Set Message Body Length = 2
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_REQUEST_ID(_DP_MSG_GET_MESSAGE_TRANSACTION_VERSION);

            SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_VERSION(0x02);

            break;

        case _DP_MSG_LINK_ADDRESS:

            // Set Message Body Length = (Logical Port + Physic Port)  * 20
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _OFF)
            {
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH((_DP_MST_RX_NUM_OF_PORTS - 1) * 20);
            }
            else
#endif
            {
#if((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON))
                if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
                {
                    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH((_DP_MST_RX_NUM_OF_PORTS - 1) * 20);
                }
                else
#endif
                {
                    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH((_DP_MST_RX_NUM_OF_PORTS * 20));
                }
            }

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_REQUEST_ID(_DP_MSG_LINK_ADDRESS);

#if(_DP_SUPPORT == _ON)
            // Set GUID
            for(BYTE ucIndex = 0; ucIndex < 16; ucIndex++)
            {
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_GUID(ucIndex, GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, (0x30 + ucIndex)));
            }
#endif

            // Set Number of Ports
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _OFF)
            {
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_PORT(_DP_MST_RX_NUM_OF_PORTS - 1);
            }
            else
#endif
            {
#if((_DP_MST_PXP_MODE_SUPPORT == _ON) && (_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON))
                if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
                {
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_PORT(_DP_MST_RX_NUM_OF_PORTS - 1);
                }
                else
#endif
                {
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_PORT(_DP_MST_RX_NUM_OF_PORTS);
                }
            }

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_ZEROS();

            // Setting Port0 Is Input Port
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_TYPE(_DP_MST_RX_INPUT_PORT);

            // Setting Port Number Of Port0
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_NUM(_DP_PORT0);

            // Check Up Stream Is Source
            if((GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x01, 0x11) & _BIT2) == _BIT2)
            {
                // Set Peer Device Type
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PEER_DEVICE_TYPE(1);
            }
            else
            {
                // Set Peer Device Type
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PEER_DEVICE_TYPE(2);
            }

            // Set Message Capability status
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_MSG_CAP(1);

            // Setting Port0 Dp Plug Status
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PLUG_STATUS(_DP_PLUG);

            //===== Set Logical Port Info. ======
            ScalerDpMstRxPortLinkAddressInfoSetting(_DP_PORT8);

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
            {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
                if(enumInputPort != _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
#endif
                {
                    ScalerDpMstRxPortLinkAddressInfoSetting(_DP_PORT9);
                }
            }
#endif

            //===== Set Physical Port Info. ======
#if(_DP_TX_SUPPORT == _ON)
            if(enumInputPort == GET_DP_RX_MAIN_PORT())
            {
                BYTE ucIndex = ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT1);

                // Setting Physical Port1 is Output Port
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_TYPE(ucIndex, _DP_MST_RX_OUTPUT_PORT);

                ScalerDpMstTxSetOutputPortStatusReported((EnumDpMstTxConnectStatus)GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS());

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                if((GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (ScalerDpMstRxGetVirtualDpEnable(GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT(), _DP_PORT1) == _ENABLE))
                {
                    // Set Reserve Bit to 0
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_ZEROS(ucIndex);

                    // Set Physical Port1 Peer Device Type
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PEER_DEVICE_TYPE(ucIndex, _DP_TX_MST_OR_SST_BRANCH_DOWNSTREAM);

                    // Set Physical Port1 Message Capability
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_MSG_CAP(ucIndex, _DP_TX_MSG_SUPPORT);

                    // Set Physical Port1 Dp Plug Status
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PLUG_STATUS(ucIndex, _DP_PLUG);

                    // Set Physical Port1 Legacy Plug Status
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_LEGACY_PLUG_STATUS(ucIndex, _DP_UNPLUG);

                    // Set Physical Port1 DPCD Revision
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_DPCD_REV(ucIndex, ScalerDpMstRxGetDpVersion(GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT()));

                    // Set Physical Port1 Number Of Secondary Streams
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP(ucIndex, 0);

                    // Set Physical Port1 Number Of Secondary Stream Sinks
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP_SINK(ucIndex, 0);
                }
                else
#endif
                {
                    // Set Reserve Bit to 0
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_ZEROS(ucIndex);

                    // Set Physical Port1 Dp Plug Status
                    SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PLUG_STATUS(ucIndex, GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS());

                    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
                    {
                        // Set Physical Port1 Peer Device Type
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PEER_DEVICE_TYPE(ucIndex, GET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE());

                        // Set Physical Port1 Message Capability
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_MSG_CAP(ucIndex, GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS());

                        // Set Physical Port1 Legacy Plug Status
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_LEGACY_PLUG_STATUS(ucIndex, GET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS());

                        // Set Physical Port1 DPCD Revision
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_DPCD_REV(ucIndex, GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV());

                        if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_NO_SUPPORT)
                        {
                            // Set Physical Port1 Number Of Secondary Streams
                            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP(ucIndex, GET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP());

                            // Set Physical Port1 Number Of Secondary Stream Sinks
                            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP_SINK(ucIndex, GET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK());
                        }
                        else
                        {
                            // Set Physical Port1 Number Of Secondary Streams
                            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP(ucIndex, 0);

                            // Set Physical Port1 Number Of Secondary Stream Sinks
                            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP_SINK(ucIndex, 0);
                        }
                    }
                    else
                    {
                        // Set Physical Port1 Peer Device Type
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PEER_DEVICE_TYPE(ucIndex, 0);

                        // Set Physical Port1 Message Capability
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_MSG_CAP(ucIndex, _DP_TX_MSG_NO_SUPPORT);

                        // Set Physical Port1 Legacy Plug Status
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_LEGACY_PLUG_STATUS(ucIndex, 0);

                        // Set Physical Port1 DPCD Revision
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_DPCD_REV(ucIndex, 0);

                        // Set Physical Port1 Number Of Secondary Streams
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP(ucIndex, 0);

                        // Set Physical Port1 Number Of Secondary Stream Sinks
                        SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP_SINK(ucIndex, 0);
                    }
                }
            }
            else
            {
                BYTE ucIndex = ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT1);

                // Set Reserve Bit to 0
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_ZEROS(ucIndex);

                // Setting Physical Port1 is Output Port
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_TYPE(ucIndex, _DP_MST_RX_OUTPUT_PORT);

                // Set Physical Port1 Peer Device Type
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PEER_DEVICE_TYPE(ucIndex, 0);

                // Set Physical Port1 Message Capability
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_MSG_CAP(ucIndex, 0);

                // Set Physical Port1 Dp Plug Status
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PLUG_STATUS(ucIndex, 0);

                // Set Physical Port1 Legacy Plug Status
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_LEGACY_PLUG_STATUS(ucIndex, 0);

                // Set Physical Port1 DPCD Revision
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_DPCD_REV(ucIndex, 0);

                // Set Physical Port1 Number Of Secondary Streams
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP(ucIndex, 0);

                // Set Physical Port1 Number Of Secondary Stream Sinks
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP_SINK(ucIndex, 0);
            }

            // Set Physical Port Number
            SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT1), _DP_PORT1);

            // Set Physical Port1 GUID
            for(BYTE ucTemp = 0; ucTemp < 16; ucTemp++)
            {
                SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT_GUID(ScalerDpMstRxPortNumMappingIndex(enumInputPort, _DP_PORT1), ucTemp, 0);
            }

#endif // End of #if(_DP_TX_SUPPORT == _ON)

            break;

        case _DP_MSG_ENUM_PATH_RESOURCES:

            // Set Message Body Length = 6
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(6);

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_REQUEST_ID(_DP_MSG_ENUM_PATH_RESOURCES);

            // Set Port Num
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM());

            // Set FEC Capability
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, 0x90) & _BIT0);

            // Set Full PBN
            SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN(ScalerDpMstRxGetMaxPBN(enumInputPort));

            if(GET_DP_MST_RX_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM() == _DP_PORT8)
            {
                if(ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT8) == _DP_ST_NONE)
                {
                    // Set Available PBN
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(ScalerDpMstRxGetMaxPBN(enumInputPort));
                }
                else
                {
                    // Set Available PBN
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(0);
                }
            }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            else if(GET_DP_MST_RX_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM() == _DP_PORT9)
            {
                if(ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT9) == _DP_ST_NONE)
                {
                    // Set Available PBN
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(ScalerDpMstRxGetMaxPBN(enumInputPort));
                }
                else
                {
                    // Set Available PBN
                    SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(0);
                }
            }
#endif
            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            // Set Message Body Length = 5
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(5);

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REQUEST_ID(_DP_MSG_ALLOCATE_PAYLOAD);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM());

            // Set Payload ID
            SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

            if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM() == _DP_PORT8)
            {
                if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() <= ScalerDpMstRxGetMaxPBN(enumInputPort))
                {
                    SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN());
                }
                else
                {
                    // Allocate Failed
                }
            }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            else if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM() == _DP_PORT9)
            {
                if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() <= ScalerDpMstRxGetMaxPBN(enumInputPort))
                {
                    SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN());
                }
                else
                {
                    // Allocate Failed
                }
            }
#endif
#if(_DP_TX_SUPPORT == _ON)
            else if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM() == _DP_PORT1)
            {
                SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN());
            }
#endif

            break;

        case _DP_MSG_QUERY_PAYLOAD:

            // Set Message Body Length = 4
            SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(4);

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_REQUEST_ID(_DP_MSG_QUERY_PAYLOAD);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM());

            // For Initial Stream Mux Source
            enumDpStreamNum = _DP_ST_NONE;

            if(GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM() == _DP_PORT8)
            {
                enumDpStreamNum = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT8);
            }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            else if(GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM() == _DP_PORT9)
            {
                enumDpStreamNum = ScalerDpMacDphyRxGetStreamAllocateInfo(enumInputPort, _DP_PORT9);
            }
#endif
#if(_DP_TX_SUPPORT == _ON)
            else if(GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM() == _DP_PORT1)
            {
                enumDpStreamNum = ScalerDpMacTxGetDaisySourceMuxBackup(_DP_ST_SOURCE1);
            }
#endif
            if((enumDpStreamNum != _DP_ST_NONE) &&
               (GET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(enumDpStreamNum) != 0))
            {
                // Calculate Allocated PBN
                usPBN = ScalerDpMacDphyRxGetPBN(ScalerDpAuxRxGetLinkRate(enumInputPort), ScalerDpAuxRxGetLaneCount(enumInputPort), GET_DP_MAC_DPHY_RX_ST_TIMESLOT_LENGTH(enumDpStreamNum));

                // Set Allocated PBN
                SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(usPBN);
            }
            else
            {
                // Set Allocated PBN
                SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(0);
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

            // Set Reserve Bit to 0
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

            // Set Reserve Bit to 0
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

            // Set Reserve Bit to 0
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

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCE_WRITE_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REQUEST_ID(_DP_MSG_REMOTE_DPCD_WRITE);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_I2C_READ:

            // Set Reserve Bit to 0
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

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REQUEST_ID(_DP_MSG_REMOTE_I2C_WRITE);

            // Set Port Number
            SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_PORT_NUM(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM());

            break;

#if(_DP_TX_SUPPORT == _ON)
        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            // Set Reserve Bit to 0
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_ZEROS();

            // Set Reply Type
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REPLY_TYPE(_DP_MST_RX_MSG_ACK);

            // Set Request ID
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REQUEST_ID(_DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS);

            EnumDpStreamNum enumStreamNum = ScalerDpMstRxSearchMatchStream(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());
            EnumDpQueryEncryptStreamState enumEncryptState = _DP_STREAM_NOT_EXIST;

            // Check if Stream ID of Down Request MSG is equal to Stream ID in the ST Source 1 and Stream ID is valid
            if(enumStreamNum != _DP_ST_NONE)
            {
                enumEncryptState = (GET_DP_MST_RX_HDCP_POWER_STATUS_NORMAL() == _TRUE) ? _DP_STREAM_ACTIVE : _DP_STREAM_NOT_ACTIVE;
            }

            // Set Stream State
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE(enumEncryptState);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if(GET_DP_MST_RX_HDCP2_MODE() == _HDCP_22)
            {
                // Set Message Body Length = 36
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(36);

                // Set Stream Repeater Function Present
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(GET_DP_MST_RX_HDCP2_REPEATER_SUPPORTED());

                // Set Stream Authentication
                if(GET_DP_MST_RX_HDCP2_REPEATER_SUPPORTED() == _TRUE)
                {
                    SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_MST_RX_HDCP2_AUTH_PROC_DONE());
                }
                else
                {
                    SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_MST_RX_HDCP_AUTH_ENCRYPTION());
                }

                // Set Stream Output CP Type => HDCP 2.x
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(_HDCP_FEATURE_2_2);
            }
            else
#endif
            {
                // Set Message Body Length = 24
                SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(24);

                // Set Stream Repeater Function Present
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(GET_DP_MST_RX_HDCP_REPEATER_SUPPORTED());

                // Set Stream Authentication
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_MST_RX_HDCP_AUTH_PROC_DONE());

                // Set Stream Output CP Type => HDCP 1.x
                SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(_HDCP_FEATURE_1_1);
            }

            // Set Stream Encryption
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION(GET_DP_MST_RX_HDCP_AUTH_ENCRYPTION());

            // Set Stream Output Sink Type
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE(_DP_OUTPUT_SINK_TYPE_MSG_NO_SUPPORT);

            // Set Signed
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(_TRUE);

            // Set Stream ID
            SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID(GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if(GET_DP_MST_RX_HDCP2_MODE() == _HDCP_22)
            {
                DebugMessageHDCP2("[QSE] Rx : Cal Signature L'", 0);

                // Calculate Signature L'
                ScalerDpMstRxQueryEncryptionWriteSha256Input(GET_DP_MST_RX_HDCP2_REPEATER_SUPPORTED());

                // Set Stream State Signature L'
                for(BYTE ucIndex = 0; ucIndex < 32; ucIndex++)
                {
                    SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(ucIndex, GET_DP_MST_RX_REG_HDCP_SHA256_RESULT(ucIndex));
                }
            }
            else
#endif
            {
                // Calculate Signature L'
                ScalerDpMstRxQueryEncryptionWriteShaInput();

                // Set Stream State Signature L'
                for(BYTE ucIndex = 0; ucIndex < 20; ucIndex++)
                {
                    SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(ucIndex, GET_DP_MST_RX_REG_HDCP_SHA_RESULT(ucIndex));
                }
            }

            break;
#endif // End of #if(_DP_TX_SUPPORT == _ON)

        default:

            break;
    }

    if(GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
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

        // Set LCR
        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() - 1);

        // Set RAD
        for(BYTE ucRadIndex = 0; ucRadIndex < GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(); ucRadIndex++)
        {
            BYTE ucRadValue = ScalerDpMstRxGetRegDownRequestRad(enumInputPort, ucRadIndex);
            ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, ucRadIndex, ucRadValue);
        }
    }

    // Set Broadcast and Path
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BROADCAST());
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_PATH());

    // Set MSN
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_MSN(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_MSN());
}

//--------------------------------------------------
// Description  : Rx Error MSG Reply for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxIllegalMsgReply(void)
{
    EnumInputPort enumInputPort = GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT();
    BYTE ucIndex = 0;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    if((GET_DP_MST_RX_MSG_REQUEST_ID() == _DP_MSG_REMOTE_I2C_READ) &&
       (GET_DP_MST_RX_REMOTE_I2C_READ_FAIL() == _TRUE))
    {
        CLR_DP_MST_RX_REMOTE_I2C_READ_FAIL();
        // Set Message Body Length
        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(20);

        SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_ZEROS();

        SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_REP_TYPE(_DP_MST_RX_MSG_NACK);

        SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_REQUESET_ID(_DP_MSG_REMOTE_I2C_READ);

#if(_DP_SUPPORT == _ON)
        // Set GUID
        for(ucIndex = 0; ucIndex < 16; ucIndex++)
        {
            SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_GUID(ucIndex, GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, (0x30 + ucIndex)));
        }
#endif

        SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_PORT(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM());
    }
    else
    {
        // Set Message Body Length
        SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(19);

        // Set Reply Type
        SET_DP_MST_RX_REPLY_ILLEGAL_MSG_REPLY_TYPE(_DP_MST_RX_MSG_NACK);

        // Set Request ID
        SET_DP_MST_RX_REPLY_ILLEGAL_MSG_REQUESET_ID(GET_DP_MST_RX_MSG_REQUEST_ID());

#if(_DP_SUPPORT == _ON)
        // Set GUID
        for(ucIndex = 0; ucIndex < 16; ucIndex++)
        {
            SET_DP_MST_RX_REPLY_ILLEGAL_MSG_GUID(ucIndex, GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x00, (0x30 + ucIndex)));
        }
#endif

        // Set NACK Reason at MSG analysis

        // Set NACK Data
        SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_DATA(0);
    }

    // Set LCT
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT());

    // Set LCR
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT() - GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() - 1);

    // Modify RAD
    for(BYTE ucRadIndex = 0; ucRadIndex < GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR(); ucRadIndex++)
    {
        BYTE ucRadValue = ScalerDpMstRxGetRegDownRequestRad(enumInputPort, ucRadIndex);
        ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, (GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR() + ucRadIndex), ucRadValue);
    }

    for(BYTE ucRadIndex = 0; ucRadIndex < GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(); ucRadIndex++)
    {
        BYTE ucRadValue = ScalerDpMstRxGetRegDownRequestRad(enumInputPort, GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR() + ucRadIndex);
        ScalerDpMstRxSetRegUpstreamReplyRad(enumInputPort, ucRadIndex, ucRadValue);
    }

    // Set Broadcast and Path
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BROADCAST());
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_PATH());

    // Set MSN
    SET_DP_MST_RX_REG_UPSTREAM_REPLY_MSN(GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_MSN());

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
// Description  : Check MSG CRC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxCheckMsgCRC(BYTE ucMSGDirection)
{
    if(ucMSGDirection == _DP_DOWN_REQUEST_MSG)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT());

        if(GET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY() == _DP_MST_RX_DOWN_REQUEST_BUF0)
        {
            // Check BUF0 Down Request CRC
            if((GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_ERROR() & (_BIT1 | _BIT0)) == 0x00)
            {
                return _TRUE;
            }
            else
            {
                // CLR Flag
                CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_ERROR();

                return _FALSE;
            }
        }
        else
        {
            // Check BUF1 Down Request CRC
            if((GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_ERROR() & (_BIT5 | _BIT4)) == 0x00)
            {
                return _TRUE;
            }
            else
            {
                // CLR Flag
                CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_ERROR();

                return _FALSE;
            }
        }
    }
    else if(ucMSGDirection == _DP_UP_REPLY_MSG)
    {
        ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_UP_REPLY_MSG_INPUT_PORT());

        if(GET_DP_MST_RX_UP_REPLY_BUF_PRIORITY() == _DP_MST_RX_DOWN_REQUEST_BUF0)
        {
            // Check BUF0 Up Reply CRC
            if((GET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_ERROR() & (_BIT1 | _BIT0)) == 0x00)
            {
                return _TRUE;
            }
            else
            {
                // CLR Flag
                CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_ERROR();

                return _FALSE;
            }
        }
        else
        {
            // Check BUF1 Up Reply CRC
            if((GET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_ERROR() & (_BIT5 | _BIT4)) == 0x00)
            {
                return _TRUE;
            }
            else
            {
                // CLR Flag
                CLR_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_ERROR();

                return _FALSE;
            }
        }
    }

    return _FALSE;
}


//--------------------------------------------------
// Description  : Check Msg Buffer Free
// Input Value  : None
// Output Value : True / False
//--------------------------------------------------
bit ScalerDpMstRxCheckMsgBufferFree(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE)
    {
        return _FALSE;
    }

    if(GET_DP_MST_RX_REQUEST_MSG_PORT() == enumInputPort)
    {
        return _FALSE;
    }

    if(GET_DP_MST_RX_REPLY_MSG_PORT() == enumInputPort)
    {
        return _FALSE;
    }

    if(GET_DP_MST_RX_REPLY_BUF_FREE() == _FALSE)
    {
        return _FALSE;
    }

    if(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH() == _TRUE)
    {
        return _FALSE;
    }

    if(GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH() == _TRUE)
    {
        return _FALSE;
    }

#if(_DP_TX_SUPPORT == _ON)
    if(enumInputPort == GET_DP_RX_MAIN_PORT())
    {
        if(GET_DP_MST_TX_RD_BUFFER_STATUS() != _DP_TX_READ_BUF_EMPTY)
        {
            return _FALSE;
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Add Payload ID Whether Existed Or Not
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpMstRxCheckIDExisted(EnumInputPort enumInputPort, BYTE ucPayloadID)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        // ID Exist in STx to ID Table
        if(ucPayloadID == GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Stream Source Status
// Input Value  : Source Number
// Output Value : Stream Number
//--------------------------------------------------
EnumDpStreamNum ScalerDpMstRxGetSourceMuxBackup(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumDpStreamSourceNum)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    return GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumDpStreamSourceNum);
}

//--------------------------------------------------
// Description  : Search ST1 ~ ST6 to Match Input Paramater
// Input Value  : Target ID
// Output Value : Match ST Number Index
//--------------------------------------------------
EnumDpStreamNum ScalerDpMstRxSearchMatchStream(EnumInputPort enumInputPort, BYTE ucTargetID)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        // Setting STx to ID Table
        if(GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum) == ucTargetID)
        {
            return enumDpStreamNum;
        }
    }

    return _DP_ST_NONE;
}

//--------------------------------------------------
// Description  : Set Flag to Generate Clear Payload ID Table MSG
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxCableUnplugReset(EnumInputPort enumInputPort)
{
    if(ScalerDpRxGetMstCapability(enumInputPort) == _TRUE)
    {
        ScalerDpRxSetBaseInputPort(enumInputPort);

        DebugMessageMst("[MST] Cable Unplug Reset!!", 0);

        // Clear Aux ch Power On Wake Up Flag
        ScalerDpAuxRxClrAuxChPowerOnWakeUp(enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
        if(enumInputPort == GET_DP_RX_MAIN_PORT())
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_FORCE_REBUILD_TOPOLOGY_EVENT);

            CLR_DP_MST_TX_WAIT_TOPOLOGY_REBUILD_MSG();

            // Set DPTx Force To Idle Pattern
            ScalerDpMacTxForceIdlePatternSetting();
        }
#endif
    }

    ScalerDpAuxRxClrSourceWritePowerUp(enumInputPort);
}

//--------------------------------------------------
// Description  : Reset Backup Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxResetBackupInfo(EnumInputPort enumInputPort)
{
    // Reset STx
    ScalerDpMstRxResetStreamStatusBackup(enumInputPort);
    ScalerDpMstRxResetStreamStartBackup(enumInputPort);
    ScalerDpMstRxResetStreamEndBackup(enumInputPort);

    // Reset STx_Source
    ScalerDpMacDphyRxResetSourceMuxReg(enumInputPort);
}

//--------------------------------------------------
// Description  : Get DP Version
// Input Value  : None
// Output Value : DP Version
//--------------------------------------------------
EnumDpVersionType ScalerDpMstRxGetDpVersion(EnumInputPort enumInputPort)
{
    // Get Logical Port 8 DPCD Revision
    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x0E, _BIT7) == _BIT7)
    {
        return ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x22, 0x00);
    }
    else
    {
        return _DP_VERSION_1_2;
    }
}

//--------------------------------------------------
// Description  : Get DP Mst Input Port
// Input Value  : None
// Output Value : EnumSourceSearchPort
//--------------------------------------------------
EnumInputPort ScalerDpMstRxGetInputPort(EnumDPMSTPort enumMstPort)
{
    switch(enumMstPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _DP_MST_RX0_PORT:
            return _D0_INPUT_PORT;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _DP_MST_RX1_PORT:
            return _D1_INPUT_PORT;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _DP_MST_RX2_PORT:
            return _D2_INPUT_PORT;
#endif

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Get Input Port of Current Downrequest Msg
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort ScalerDpMstRxGetRxDownRequestMstInputPort(void)
{
    if(GET_DP_MST_RX_REQUEST_POOL_FREE() == _TRUE)
    {
        return _NO_INPUT_PORT;
    }
    else
    {
        return GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();
    }
}

//--------------------------------------------------
// Description  : Get DP EDID DDC Ram Address
// Input Value  : enumInputPort --> target input port
// Output Value : DDCRAM pointer
//--------------------------------------------------
BYTE *ScalerDpMstRxGetEdidRamAddress(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
        case _D0_INPUT_PORT:

            return MCU_DDCRAM_D0;
#endif
#endif

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
        case _D1_INPUT_PORT:
            return MCU_DDCRAM_D1;
#endif
#endif

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D2_DDC_CHANNEL_SEL == _DDC2)
        case _D2_INPUT_PORT:
            return MCU_DDCRAM_D2;
#endif
#endif

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
#if(_D9_EMBEDDED_XRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D9_INPUT_PORT:

#if(_DP_MST_PXP_LOAD_D9_EDID_BY_INPUT_PORT == _ON)
            switch(GET_DP_MST_RX_PXP_INPUT_PORT())
            {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                case _D0_INPUT_PORT:
                    return g_pucDpRx0PxpEdid;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                case _D1_INPUT_PORT:
                    return g_pucDpRx1PxpEdid;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
                case _D2_INPUT_PORT:
                    return g_pucDpRx2PxpEdid;
#endif

                default:
                    return _NULL_POINTER;
            }
#else
            return g_pucDpRxPxpEdid;
#endif
#endif
#endif

        default:
            break;
    }

    return _NULL_POINTER;
}

//--------------------------------------------------
// Description  : Get DP EDID DDC Ram Size
// Input Value  : enumInputPort --> target input port, EnumDpMstPort
// Output Value : BYTE
//--------------------------------------------------
WORD ScalerDpMstRxGetEdidRamSize(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
        case _D0_INPUT_PORT:

            return _D0_EMBEDDED_DDCRAM_MAX_SIZE;
#endif
#endif

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
        case _D1_INPUT_PORT:
            return _D1_EMBEDDED_DDCRAM_MAX_SIZE;
#endif
#endif

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D2_DDC_CHANNEL_SEL == _DDC2)
        case _D2_INPUT_PORT:
            return _D2_EMBEDDED_DDCRAM_MAX_SIZE;
#endif
#endif

#if(_D9_EMBEDDED_XRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D9_INPUT_PORT:
            return _D9_EMBEDDED_XRAM_MAX_SIZE;
#endif

        default:
            break;
    }

    return _EDID_SIZE_NONE;
}

//--------------------------------------------------
// Description  : Dp Mst Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxCapabilitySwitchProc(void)
{
    bit bEnable = _DISABLE;

    for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort ++)
    {
        switch(enumInputPort)
        {
#if(_D0_DP_SUPPORT == _ON)
            case _D0_INPUT_PORT:

#if(_D0_DP_MST_PORT_SUPPORT == _ON)
                bEnable = (((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) || (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_AUTO_PORT)) && (GET_DP_RX_D0_PORT_TARGET_VERSION() >= _DP_VERSION_1_2));
#else
                bEnable = _DISABLE;
#endif

                break;
#endif

#if(_D1_DP_SUPPORT == _ON)
            case _D1_INPUT_PORT:

#if(_D1_DP_MST_PORT_SUPPORT == _ON)
                bEnable = (((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT) || (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_AUTO_PORT)) && (GET_DP_RX_D1_PORT_TARGET_VERSION() >= _DP_VERSION_1_2));
#else
                bEnable = _DISABLE;
#endif

                break;
#endif

#if(_D2_DP_SUPPORT == _ON)
            case _D2_INPUT_PORT:

#if(_D2_DP_MST_PORT_SUPPORT == _ON)
                bEnable = (((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX2_PORT) || (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_AUTO_PORT)) && (GET_DP_RX_D2_PORT_TARGET_VERSION() >= _DP_VERSION_1_2));
#else
                bEnable = _DISABLE;
#endif

                break;
#endif

            default:

                continue;
        }

        if(ScalerDpAuxRxMstCapabilitySwitch(enumInputPort, bEnable) == _TRUE)
        {
            ScalerDpMstRxInitial(enumInputPort);

            ScalerDpAuxRxClrCheckChNoPowerDebounce(enumInputPort);
            ScalerDpAuxRxClrCheckChPowerStatus(enumInputPort);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            ScalerDpAuxRxDscDpcdExtendedCapSetting(enumInputPort);
#endif

#if(_DP_RX_FEC_SUPPORT == _ON)
            ScalerDpAuxRxFecDpcdSetting(enumInputPort);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
            ScalerDpAuxRxFreesyncDpcdSetting(enumInputPort);
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
            ScalerDpAuxRxAdaptiveSyncDpcdSetting(enumInputPort);
#endif

#if(_DP_TX_SUPPORT == _ON)
            if(enumInputPort == GET_DP_RX_MAIN_PORT())
            {
                if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
                {
                    ScalerDpMacTxForceIdlePatternSetting();
                }
                else
                {
                    ScalerDpMacTxSetStreamSource(_DP_TX_SOURCE_NONE);
                }

                if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
                {
#if(_DP_FREESYNC_SUPPORT == _ON)
                    BYTE ucData = 0;

                    // Clear freesync enable bit
                    ScalerDpAuxTxNativeRead(0x00, 0x01, 0x07, 1, &ucData);

                    if((ucData & _BIT7) == _BIT7)
                    {
                        ucData &= ~_BIT7;
                        ScalerDpAuxTxNativeWrite(0x00, 0x01, 0x07, 1, &ucData);
                    }
#endif
                }
            }
#endif
            DebugMessageMst("Dx MST Switch", (((enumInputPort - _D0_INPUT_PORT) << 4) | bEnable));

            if(ScalerDpRxGetHotPlugStatus(enumInputPort) == _HIGH)
            {
                ScalerDpRxSetHotPlugEvent(enumInputPort, _DP_MST_LONG_HPD_EVENT);
            }
        }
    }
}

//--------------------------------------------------
// Description  : MST Power Switch Proc
// Input Value  : enumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_D0_DP_SUPPORT == _ON)
            ScalerDpAuxRxClearCommandNoReply(_D0_INPUT_PORT);
#endif // End of #if(_D0_DP_SUPPORT == _ON)

#if(_D1_DP_SUPPORT == _ON)
            ScalerDpAuxRxClearCommandNoReply(_D1_INPUT_PORT);
#endif // End of #if(_D1_DP_SUPPORT == _ON)

#if(_D2_DP_SUPPORT == _ON)
            ScalerDpAuxRxClearCommandNoReply(_D2_INPUT_PORT);
#endif // End of #if(_D2_DP_SUPPORT == _ON)

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_D0_DP_SUPPORT == _ON)
            ScalerDpAuxRxClearCommandNoReply(_D0_INPUT_PORT);

            if(ScalerDpRxGetMstCapability(_D0_INPUT_PORT) == _TRUE)
            {
                ScalerDpMstRxReset(_D0_INPUT_PORT);
            }
#endif // End of #if(_D0_DP_SUPPORT == _ON)

#if(_D1_DP_SUPPORT == _ON)
            ScalerDpAuxRxClearCommandNoReply(_D1_INPUT_PORT);

            if(ScalerDpRxGetMstCapability(_D1_INPUT_PORT) == _TRUE)
            {
                ScalerDpMstRxReset(_D1_INPUT_PORT);
            }
#endif // End of #if(_D1_DP_SUPPORT == _ON)

#if(_D2_DP_SUPPORT == _ON)
            ScalerDpAuxRxClearCommandNoReply(_D2_INPUT_PORT);

            if(ScalerDpRxGetMstCapability(_D2_INPUT_PORT) == _TRUE)
            {
                ScalerDpMstRxReset(_D2_INPUT_PORT);
            }
#endif // End of #if(_D2_DP_SUPPORT == _ON)

            break;

        default:
            break;
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Judge Tx Data Path when receive Rx MSG DownRequest Allocate Payload
// Input Value  : None
// Output Value : EnumDpRxMsgAllocatePayloadTxDataPath
//--------------------------------------------------
EnumDpRxMsgAllocatePayloadTxDataPath ScalerDpMstRxMsgJudgeTxDataPath(void)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B)
    {
        if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
        {
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            if(GET_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE() == _TRUE)
            {
                // Rx = 128b132b, Tx = 128b132b, Source Enable Branch DSC Decode, MST to SST path
                return _DP_RX_MSG_ALLOCATE_PAYLOAD_MST2SST_PATH;
            }
            else
#endif
            {
                // Rx = 128b132b, Tx = 128b132b, Daisy path
                return _DP_RX_MSG_ALLOCATE_PAYLOAD_DAISY_PATH;
            }
        }
        else
        {
            // Rx = 128b132b, Tx = 8b10b, MST to SST path
            return _DP_RX_MSG_ALLOCATE_PAYLOAD_MST2SST_PATH;
        }
    }
    else
#endif
    {
        // Rx = 8b10b, Tx = 8b10b, MST to SST path
        return _DP_RX_MSG_ALLOCATE_PAYLOAD_MST2SST_PATH;
    }
}

//--------------------------------------------------
// Description  : Judge Tx Event when receive Rx MSG DownRequest Allocate Payload
// Input Value  : EnumDpMstRxAllocatePayloadTxDataPath
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxMsgJudgeAllocatePayloadTxEvent(EnumDpRxMsgAllocatePayloadTxDataPath enumTxDataPath)
{
    // PBN > 0
    if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
    {
        if(ScalerDpMstTxGetIncomingHPDStatus() == _DP_UNPLUG)
        {
            return;
        }

        if(enumTxDataPath == _DP_RX_MSG_ALLOCATE_PAYLOAD_DAISY_PATH)
        {
            SET_DP_MST_RX_EVENT(_DP_RX_REMOTE_DAISY_TRANSPORT);
        }
        else
        {
            SET_DP_MST_RX_EVENT(_DP_RX_REMOTE_MST2SST_TRANSPORT);
        }
    }
    // PBN = 0
    else
    {
        if(enumTxDataPath == _DP_RX_MSG_ALLOCATE_PAYLOAD_DAISY_PATH)
        {
            SET_DP_MST_RX_EVENT(_DP_RX_REMOTE_DAISY_DELETE);
        }
        else
        {
            SET_DP_MST_RX_EVENT(_DP_RX_REMOTE_MST2SST_DELETE);
        }
    }
}

//--------------------------------------------------
// Description  : Check DP Add Reactive Time for Main Port Switch
// Input Value  : enumInputPort
// Output Value : _TRUE to add reactive time
//--------------------------------------------------
bit ScalerDpMstRxReactiveSearchTimeCheck(EnumInputPort enumInputPort)
{
    if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRxGetSrcMstUpRequestEnable(enumInputPort) == _FALSE)
    {
        return _FALSE;
    }

    if(GET_DP_RX_MAIN_PORT() == enumInputPort)
    {
        return _FALSE;
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_UNPLUG)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Judge Rx Event when receive Rx MSG DownRequest Allocate Payload
// Input Value  : EnumDpMstRxAllocatePayloadTxDataPath
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxMsgJudgeAllocatePayloadRxEvent(EnumDpRxMsgAllocatePayloadRxDataPath enumRxDataPath)
{
    // PBN > 0
    if(GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
    {
        if(enumRxDataPath == _DP_RX_MSG_ALLOCATE_PAYLOAD_PORT8_PATH)
        {
            SET_DP_MST_RX_EVENT(_DP_RX_NATIVE_PORT8_DISPLAY);
        }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        else
        {
            SET_DP_MST_RX_EVENT(_DP_RX_NATIVE_PORT9_DISPLAY);
        }
#endif
    }
    // PBN = 0
    else
    {
        if(enumRxDataPath == _DP_RX_MSG_ALLOCATE_PAYLOAD_PORT8_PATH)
        {
            SET_DP_MST_RX_EVENT(_DP_RX_NATIVE_PORT8_DELETE);
        }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        else
        {
            SET_DP_MST_RX_EVENT(_DP_RX_NATIVE_PORT9_DELETE);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxMainPortSwitchProc(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DP_TX_SUPPORT == _ON)
    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        if(GET_DP_RX_MAIN_PORT() != _NO_INPUT_PORT)
        {
            // Disable MST to SST
            CLR_DP_MAC_MST2SST_ENABLE();

            // Set DPTx Force To Idle Pattern
            ScalerDpMacTxForceIdlePatternSetting();

            ScalerDpMstTxReset();

            if(ScalerDpRxGetSrcMstUpRequestEnable(GET_DP_RX_MAIN_PORT()) == _TRUE)
            {
                ScalerDpMstTxSetCsnEvent(GET_DP_RX_MAIN_PORT(), _CONNECT_STATUS_UNPLUG);
            }
        }

        if((ScalerDpRxGetMstCapability(enumInputPort) == _TRUE) && (ScalerDpRxGetSrcMstUpRequestEnable(enumInputPort) == _TRUE))
        {
            ScalerDpMstTxSetCsnEvent(enumInputPort, _CONNECT_STATUS_PLUG);

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
            ScalerDpMstRxVirtualDpInitial(enumInputPort, ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT));
#endif
        }
    }

    // Set Daisy InputPort Mux
    ScalerDpMstTxSetDaisyInputPortMux(enumInputPort);
#endif
}

//--------------------------------------------------
// Description  : Get Rx Max PBN -> MIN(LinkBW, HW MAC BW)
// Input Value  : void
// Output Value : PBN
//--------------------------------------------------
WORD ScalerDpMstRxGetMaxPBN(EnumInputPort enumInputPort)
{
    WORD usMacMaxPBN = 0;
    WORD usLinkMaxPBN = 0;
    BYTE ucMaxTimeSlot = 0;
    EnumDpLinkRate enumDpLinkRate = ScalerDpAuxRxGetLinkRate(enumInputPort);
    EnumDpLaneCount enumDpLaneCount = ScalerDpAuxRxGetLaneCount(enumInputPort);
    EnumDpAuxRxModeStatus enumBackUpAuxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

    if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    // Some Source: No Link Training -> EnumPathResource , Use Project BW and set the limit to HBR3
    if((enumDpLinkRate == _DP_LINK_NONE) || (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE))
    {
        enumDpLinkRate = ScalerDpAuxRxGetDpcdMaxLinkRateCapability(enumInputPort);
        enumDpLaneCount = ScalerDpAuxRxGetDpcdMaxLaneCountCapability(enumInputPort);
    }

    if(enumBackUpAuxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }

    // Source: Link Training -> EnumPathResource
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(enumDpLinkRate >= _DP_LINK_UHBR10)
    {
        usMacMaxPBN = _DP_MAC_DPHY_RX_MAX_PBN_128B132B;
        ucMaxTimeSlot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM;
    }
    else
#endif
    {
        usMacMaxPBN = _DP_MAC_DPHY_RX_MAX_PBN_8B10B;
        ucMaxTimeSlot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM - 1;
    }

    usLinkMaxPBN = ScalerDpMacDphyRxGetPBN(enumDpLinkRate, enumDpLaneCount, ucMaxTimeSlot);

    return ((usLinkMaxPBN < usMacMaxPBN) ? (usLinkMaxPBN) : (usMacMaxPBN));
}

//--------------------------------------------------
// Description  : Calculate Current Rx Available PBN
// Input Value  : None
// Output Value : Available PBN
//--------------------------------------------------
WORD ScalerDpMstRxGetAvailablePBN(EnumInputPort enumInputPort)
{
    BYTE ucAvailableTimeSlot = ScalerDpMstRxGetAvailableTimeslot(enumInputPort);

    return ScalerDpMacDphyRxGetPBN(ScalerDpAuxRxGetLinkRate(enumInputPort), ScalerDpAuxRxGetLaneCount(enumInputPort), ucAvailableTimeSlot);
}

//--------------------------------------------------
// Description  : Calculate Available Timeslot
// Input Value  : EnumInputPort
// Output Value : ucTimeslot
//--------------------------------------------------
BYTE ScalerDpMstRxGetAvailableTimeslot(EnumInputPort enumInputPort)
{
    BYTE ucLastTimeslot = 0;
    BYTE ucAvaTimeslot = 0;
    EnumDpStreamSourceNum enumDpSourceNum = _DP_ST_SOURCE1;
    EnumDpStreamNum enumDpStreamNum = _DP_ST_NONE;
    bit bStreamStatus = _DISABLE;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    for(enumDpSourceNum = _DP_ST_SOURCE1; enumDpSourceNum <= _DP_ST_SOURCE_END; enumDpSourceNum++)
    {
        enumDpStreamNum = GET_DP_MAC_DPHY_RX_ST_SOURCE_BACKUP(enumDpSourceNum);

        if(enumDpStreamNum != _DP_ST_NONE)
        {
            // Determine if any stream is in use
            if(GET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(enumDpStreamNum) == _ENABLE)
            {
                bStreamStatus = _ENABLE;

                // Find The Last Timeslot
                if(GET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(enumDpStreamNum) > ucLastTimeslot)
                {
                    ucLastTimeslot = GET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(enumDpStreamNum);
                }
            }
        }
    }

    // Error Handler
    if(ucLastTimeslot > 63)
    {
        ucLastTimeslot = 63;
    }

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Max AvaTimeslot: 128b132b = 64, 8b10b = 63
    // LastTimeslot: 128b132b = 0~63, 8b10b = 1~63
    if(ScalerDpAuxRxGetCodingType(enumInputPort) == _CODING_TYPE_128B132B)
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
        // 63 timeslot
        if(bStreamStatus == _DISABLE)
        {
            ucAvaTimeslot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM - 1;
        }
        // 63 timeslot - (end - start + 1)
        else
        {
            ucAvaTimeslot = _DP_MST_RX_TOTAL_TIME_SLOT_NUM - 1 - (ucLastTimeslot - 1 + 1);
        }
    }

    return ucAvaTimeslot;
}

//--------------------------------------------------
// Description  : Get MST timerevent
// Input Value  : enumInputPort, enumEventType
// Output Value : None
//--------------------------------------------------
EnumScalerTimerEventID ScalerDpMstRxGetTimerEvent(EnumInputPort enumInputPort, EnumDpMstRxTimerEventType enumEventType)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            switch(enumEventType)
            {
                case _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT:

                    return _SCALER_TIMER_EVENT_DP_RX0_MSG_TIMEOUT_EVENT;

                case _SCALER_TIMER_EVENT_DP_UP_REQUEST_PROCESSING:

                    return _SCALER_TIMER_EVENT_DP_RX0_UP_REQUEST_PROCESSING;

                default:

                    break;
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            switch(enumEventType)
            {
                case _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT:

                    return _SCALER_TIMER_EVENT_DP_RX1_MSG_TIMEOUT_EVENT;

                case _SCALER_TIMER_EVENT_DP_UP_REQUEST_PROCESSING:

                    return _SCALER_TIMER_EVENT_DP_RX1_UP_REQUEST_PROCESSING;

                default:

                    break;
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            switch(enumEventType)
            {
                case _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT:

                    return _SCALER_TIMER_EVENT_DP_RX2_MSG_TIMEOUT_EVENT;

                case _SCALER_TIMER_EVENT_DP_UP_REQUEST_PROCESSING:

                    return _SCALER_TIMER_EVENT_DP_RX2_UP_REQUEST_PROCESSING;

                default:

                    break;
            }

            break;
#endif

        default:

            break;
    }

    return _SCALER_TIMER_EVENT_INVALID;
}

//--------------------------------------------------
// Description  : Dp Rx Fake Power Saving Check
// Input Value  : None
// Output Value : True  --> Fake Power Saving
//                False --> Power Saving
//--------------------------------------------------
bit ScalerDpMstRxFakePowerSavingCheck(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
    {
        return _FALSE;
    }

    if(GET_DP_MST_RX_SOURCE_FIRST_POWER_ON() == _TRUE)
    {
        return _TRUE;
    }

    // Source writes 00600h = 0x01, go to fake power saving for 3s.
    if(GET_DP_RX_MST_SOURCE_WRITE_POWER_UP() != _DP_SOURCE_WRITE_POWER_UP_NONE)
    {
        return _TRUE;
    }

    if(GET_DP_MST_RX_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_OFF)
    {
        return _FALSE;
    }

    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
    {
        return _TRUE;
    }

    if(GET_DP_MST_RX_MODE_STATE() != _DP_RX_MST_MODE_STATUS_NONE_MSG)
    {
        return _TRUE;
    }

    // Check if MSG Processing or Stream Propagating
    if((ScalerDpMstRxCheckMsgTransition(enumInputPort) == _TRUE) || (GET_DP_MST_RX_REG_DPCD_INFO(0x00, 0x02, 0xC1) != 0))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : ScalerDpMstRxDownRequestProc
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMstRxDownRequestProc(void)
{
    bit bDone = _TRUE;

    bDone &= ScalerDpMstRxDownRequestReceive();

    bDone &= ScalerDpMstRxDownRequestAnal();

    bDone &= ScalerDpMstRxDownRequestEventProc();

    return bDone;
}

//--------------------------------------------------
// Description  : ScalerDpMstRxDownReplytProc
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMstRxDownReplyProc(void)
{
    bit bDone = _TRUE;

    bDone &= ScalerDpMstRxDownReplyAnal();

    bDone &= ScalerDpMstRxDownReplySend();

    return bDone;
}

//--------------------------------------------------
// Description  : ScalerDpMstRxDownRequestProc
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMstRxUpRequestProc(void)
{
    bit bDone = _TRUE;

    bDone &= ScalerDpMstRxUpRequestAnal();

    bDone &= ScalerDpMstRxUpRequestSend();

    return bDone;
}

//--------------------------------------------------
// Description  : ScalerDpMstRxUpReplyProc
// Input Value  : None
// Output Value : bit
//--------------------------------------------------
bit ScalerDpMstRxUpReplyProc(void)
{
    bit bDone = _TRUE;

    bDone &= ScalerDpMstRxUpReplyReceive();

    bDone &= ScalerDpMstRxUpReplyAnal();

    return bDone;
}

//--------------------------------------------------
// Description  : MST Timer Event Active Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxTimerEventActiveHandler(void)
{
    BYTE ucEventIndex = 0;

    // Search for Valid MST Timer Event
    for(ucEventIndex = 0; ucEventIndex < _SCALER_DP_MST_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_MST_TIMER_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _DISABLE);

            ScalerTimerReactiveTimerEvent(GET_MST_TIMER_EVENT_TIME(ucEventIndex), GET_MST_TIMER_EVENT_ID(ucEventIndex));

            CLR_MST_TIMER_EVENT_VALID(ucEventIndex);

            SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _ENABLE);
        }
    }
}

//--------------------------------------------------
// Description  : Active Timer Event
// Input Value  : usTime --> Time to active Timer Event
//                ucEventID --> Event to be actived
// Output Value : _TRUE if actived successfully
//--------------------------------------------------
bit ScalerDpMstRxActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search for Existing Event with the same Event ID and Do Nothing
    if(ScalerTimerSearchActiveTimerEvent(enumEventID) == _TRUE)
    {
        return _TRUE;
    }

    // Search for Existing MST Event with the same Event ID and Do Nothing
    for(ucEventIndex = 0; ucEventIndex < _SCALER_DP_MST_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_MST_TIMER_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_MST_TIMER_EVENT_ID(ucEventIndex) == enumEventID)
            {
                return _TRUE;
            }
        }
    }

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _DISABLE);

    // Choose any Vacant Storage for Event
    for(ucEventIndex = 0; ucEventIndex < _SCALER_DP_MST_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_MST_TIMER_EVENT_VALID(ucEventIndex) == _FALSE)
        {
            SET_MST_TIMER_EVENT_ID(ucEventIndex, enumEventID);

            SET_MST_TIMER_EVENT_TIME(ucEventIndex, usTime);

            SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _ENABLE);

            return _TRUE;
        }
    }

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _ENABLE);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reactive a timer for an event. If the event is exist,
//                this function will reset the executing time and restart.
// Input Value  : usTime    --> Unit in 1ms, range in 0.01 ~ 61 sec
//                Event     --> Execute Event while timeup
// Output Value : _TRUE if actived successfully
//--------------------------------------------------
bit ScalerDpMstRxReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search for Existing Event with the same Event ID
    for(ucEventIndex = 0; ucEventIndex < _SCALER_DP_MST_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_MST_TIMER_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_MST_TIMER_EVENT_ID(ucEventIndex) == enumEventID)
            {
                SET_MST_TIMER_EVENT_TIME(ucEventIndex, usTime);

                return _TRUE;
            }
        }
    }

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _DISABLE);

    // Choose any Vacant Storage for Event
    for(ucEventIndex = 0; ucEventIndex < _SCALER_DP_MST_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_MST_TIMER_EVENT_VALID(ucEventIndex) == _FALSE)
        {
            SET_MST_TIMER_EVENT_ID(ucEventIndex, enumEventID);

            SET_MST_TIMER_EVENT_TIME(ucEventIndex, usTime);

            SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _ENABLE);

            return _TRUE;
        }
    }

    SET_INTERRUPT_ENABLE_STATUS(_INT_DP, _ENABLE);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Cancel an event
// Input Value  : Event     --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxCancelTimerEvent(EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search for Existing Event with the same Event ID
    for(ucEventIndex = 0; ucEventIndex < _SCALER_DP_MST_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_MST_TIMER_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_MST_TIMER_EVENT_ID(ucEventIndex) == enumEventID)
            {
                CLR_MST_TIMER_EVENT_VALID(ucEventIndex);

                return;
            }
        }
    }
}

#if(_URGENT_EVENT_CHECK_MODE == _ON)
//--------------------------------------------------
// Description  : Check If The Down Request Is Urgent or Not
// Input Value  : None
// Output Value : _TRUE: Urgent; _FALSE: Not Urgent
//--------------------------------------------------
bit ScalerDpMstRxDownReqMsgCheckUrgent(void)
{
    if(GET_DP_MST_RX_REQUEST_POOL_FREE() == _FALSE)
    {
        switch(GET_DP_MST_RX_MSG_REQUEST_ID())
        {
            case _DP_MSG_REMOTE_I2C_WRITE:

                if(GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_WRITE_DEVICE_ID() == _DP_MSG_IIC_DEVICE_DDCCI)
                {
                    return _FALSE;
                }

                break;

            case _DP_MSG_REMOTE_DPCD_READ:

                if((GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H() == 0x00) &&
                   ((GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M() == 0x04) ||
                    (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M() == 0x05)) &&
                   (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L() >= 0x0C))
                {
                    return _FALSE;
                }

                break;

            case _DP_MSG_REMOTE_DPCD_WRITE:

                if((GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_H() == 0x00) &&
                   ((GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M() == 0x04) ||
                    (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M() == 0x05)) &&
                   (GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_L() >= 0x0C))
                {
                    return _FALSE;
                }

                break;

            default:
                break;
        }
    }

    return _TRUE;
}
#endif // End of #if(_URGENT_EVENT_CHECK_MODE == _ON)

#if((_DP_TX_SUPPORT == _ON) || (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Tx Up Request Event Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxUpRequestEventCheckDone(void)
{
    // Check if a Up Request is transmitted done
    for(EnumInputPort enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
        {
            continue;
        }

        ScalerDpRxSetBaseInputPort(enumInputPort);

        if((GET_DP_MST_RX_UP_REQUEST_BYPASS_DONE() == _TRUE) || (GET_DP_MST_RX_UP_REQUEST_RETRY_NUM() >= 5))
        {
            if(GET_DP_MST_RX_UP_REQUEST_ISSUED_ID() == _DP_MSG_SINK_EVENT_NOTIFY)
            {
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
                // Check if a Rx Sink Event Notify is transmitted done
                if(GET_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE() != _RX_UP_REQ_QUEUE_NONE)
                {
                    // Delete Event
                    ScalerDpMstRxVirtualDpSenEventDelete(GET_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE());
                }
#endif

#if(_DP_TX_SUPPORT == _ON)
                // Check if a Tx Sink Event Notify is transmitted done
                if(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE() != _TX_UP_REQ_QUEUE_NONE)
                {
                    // Delete Event
                    ScalerDpMstTxSenEventDelete(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE());
                }
#endif
            }
#if(_DP_TX_SUPPORT == _ON)
            else if(GET_DP_MST_RX_UP_REQUEST_ISSUED_ID() == _DP_MSG_CONNECTION_STATUS_NOTIFY)
            {
                // Check if a Tx Connection Status Notify is transmitted done
                if(ScalerDpMstTxCsnTransmitDoneCheck() == _TRUE)
                {
                    // Update Status Reported
                    if(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE() != _TX_UP_REQ_QUEUE_BYPASS)
                    {
                        ScalerDpMstTxSetOutputPortStatusReported(ScalerDpMstTxCsnEventGetStatus(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE()));
                    }

                    // Delete Event
                    ScalerDpMstTxCsnEventDelete(GET_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE());
                }
            }
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Up Request Allowed Check
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
bit ScalerDpMstRxUpRequestAllowedCheck(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(GET_DP_MST_RX_GEN_UP_REQUEST_MSG() != _DP_MSG_NONE)
    {
        return _FALSE;
    }

#if(_DP_TX_SUPPORT == _ON)
    if(GET_DP_MST_TX_GEN_UP_REQUEST_MSG() != _DP_MSG_NONE)
    {
        return _FALSE;
    }
#endif

    if(GET_DP_MST_RX_MODE_STATE() == _DP_RX_MST_MODE_STATUS_NONE_MSG)
    {
        return _FALSE;
    }

    if(GET_DP_MST_RX_UP_REQUEST_PROCESSING() == _TRUE)
    {
        return _FALSE;
    }

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_TX_PLUG_CSN_DEBOUNCE_SUPPORT == _ON))
    if((enumInputPort == GET_DP_RX_MAIN_PORT()) && (GET_DP_MST_TX_PLUG_CSN_DEBOUNCING() == _TRUE))
    {
        return _FALSE;
    }
#endif

    if(ScalerDpMstRxCheckMsgTransition(enumInputPort) == _TRUE)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : L' = SHA-1(Stream-Status | Q_id | S_id | An | Bksv | V | M0)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxQueryEncryptionWriteShaInput(void)
{
    BYTE ucIndex = 0;

    // Reset SHA Block counter
    CLR_DP_MST_RX_REG_SHA_ENABLE();

    // Start to Write SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_ENABLE();

    // 1. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(g_unDpMstRxReplyPool.pucData[1]);
    SET_DP_MST_RX_REG_SHA_INPUT_1(g_unDpMstRxReplyPool.pucData[2]);
    SET_DP_MST_RX_REG_SHA_INPUT_2(g_pucDpMstRxMsgQueryEncryptClientId[0]);
    SET_DP_MST_RX_REG_SHA_INPUT_3(g_pucDpMstRxMsgQueryEncryptClientId[1]);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    // 2. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(g_pucDpMstRxMsgQueryEncryptClientId[2]);
    SET_DP_MST_RX_REG_SHA_INPUT_1(g_pucDpMstRxMsgQueryEncryptClientId[3]);
    SET_DP_MST_RX_REG_SHA_INPUT_2(g_pucDpMstRxMsgQueryEncryptClientId[4]);
    SET_DP_MST_RX_REG_SHA_INPUT_3(g_pucDpMstRxMsgQueryEncryptClientId[5]);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    // 3. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(g_pucDpMstRxMsgQueryEncryptClientId[6]);
    SET_DP_MST_RX_REG_SHA_INPUT_1(GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());
    SET_DP_MST_RX_REG_SHA_INPUT_2(GET_DP_MST_RX_HDCP_AN(0));
    SET_DP_MST_RX_REG_SHA_INPUT_3(GET_DP_MST_RX_HDCP_AN(1));

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    // 4. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(GET_DP_MST_RX_HDCP_AN(2));
    SET_DP_MST_RX_REG_SHA_INPUT_1(GET_DP_MST_RX_HDCP_AN(3));
    SET_DP_MST_RX_REG_SHA_INPUT_2(GET_DP_MST_RX_HDCP_AN(4));
    SET_DP_MST_RX_REG_SHA_INPUT_3(GET_DP_MST_RX_HDCP_AN(5));

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    // 5. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(GET_DP_MST_RX_HDCP_AN(6));
    SET_DP_MST_RX_REG_SHA_INPUT_1(GET_DP_MST_RX_HDCP_AN(7));
    SET_DP_MST_RX_REG_SHA_INPUT_2(g_pucSyncHdcpBksvBackup[0]);
    SET_DP_MST_RX_REG_SHA_INPUT_3(g_pucSyncHdcpBksvBackup[1]);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    // 6. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(g_pucSyncHdcpBksvBackup[2]);
    SET_DP_MST_RX_REG_SHA_INPUT_1(g_pucSyncHdcpBksvBackup[3]);
    SET_DP_MST_RX_REG_SHA_INPUT_2(g_pucSyncHdcpBksvBackup[4]);
    SET_DP_MST_RX_REG_SHA_INPUT_3(GET_DP_MST_RX_HDCP_V(0));

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    ucIndex = 1;

    do
    {
        // 7~10. Write Data into SHA-1 Transform Input
        SET_DP_MST_RX_REG_SHA_INPUT_0(GET_DP_MST_RX_HDCP_V(ucIndex));
        SET_DP_MST_RX_REG_SHA_INPUT_1(GET_DP_MST_RX_HDCP_V(ucIndex + 1));
        SET_DP_MST_RX_REG_SHA_INPUT_2(GET_DP_MST_RX_HDCP_V(ucIndex + 2));
        SET_DP_MST_RX_REG_SHA_INPUT_3(GET_DP_MST_RX_HDCP_V(ucIndex + 3));

        // Enable write 32-bit data to SHA-1 block
        SET_DP_MST_RX_REG_SHA_INPUT_DB();

        ucIndex += 4;
    }
    while(ucIndex < 17);

    // 11. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(GET_DP_MST_RX_HDCP_V(17));
    SET_DP_MST_RX_REG_SHA_INPUT_1(GET_DP_MST_RX_HDCP_V(18));
    SET_DP_MST_RX_REG_SHA_INPUT_2(GET_DP_MST_RX_HDCP_V(19));
    SET_DP_MST_RX_REG_SHA_INPUT_3(GET_DP_MST_RX_REG_HDCP_M0_0());

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    // 12. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(GET_DP_MST_RX_REG_HDCP_M0_1());
    SET_DP_MST_RX_REG_SHA_INPUT_1(GET_DP_MST_RX_REG_HDCP_M0_2());
    SET_DP_MST_RX_REG_SHA_INPUT_2(GET_DP_MST_RX_REG_HDCP_M0_3());
    SET_DP_MST_RX_REG_SHA_INPUT_3(GET_DP_MST_RX_REG_HDCP_M0_4());

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    // 13. Write Data into SHA-1 Transform Input
    SET_DP_MST_RX_REG_SHA_INPUT_0(GET_DP_MST_RX_REG_HDCP_M0_5());
    SET_DP_MST_RX_REG_SHA_INPUT_1(GET_DP_MST_RX_REG_HDCP_M0_6());
    SET_DP_MST_RX_REG_SHA_INPUT_2(GET_DP_MST_RX_REG_HDCP_M0_7());
    SET_DP_MST_RX_REG_SHA_INPUT_3(0x80);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    for(ucIndex = 14; ucIndex < 16; ucIndex++)
    {
        // 14~15. Write 0x00 into the remaining SHA-1 Transform Input space
        SET_DP_MST_RX_REG_SHA_INPUT_0(0x00);
        SET_DP_MST_RX_REG_SHA_INPUT_1(0x00);
        SET_DP_MST_RX_REG_SHA_INPUT_2(0x00);
        SET_DP_MST_RX_REG_SHA_INPUT_3(0x00);

        // Enable write 32-bit data to SHA-1 block
        SET_DP_MST_RX_REG_SHA_INPUT_DB();
    }

    // 16. Write 0x00 into the remaining SHA-1 Transform Input space
    SET_DP_MST_RX_REG_SHA_INPUT_0(0x00);
    SET_DP_MST_RX_REG_SHA_INPUT_1(0x00);
    SET_DP_MST_RX_REG_SHA_INPUT_2(0x01);
    SET_DP_MST_RX_REG_SHA_INPUT_3(0x98);

    // Enable write 32-bit data to SHA-1 block
    SET_DP_MST_RX_REG_SHA_INPUT_DB();

    // Run SHA-1 Process
    SET_DP_MST_RX_HDCP_SHA_INPUT_RUN(_TRUE);
}

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : L' = SHA-256(Stream-Status | Q_id | S_id | Riv | Receiver_ID | V' | (Qid | Qid | Qid))
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxQueryEncryptionWriteSha256Input(bit bRepeater)
{
    BYTE pucHmacSha256Input[64] = {0};
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

    // Load Link-id (64-bits) = riv
    for(ucIndex = 0; ucIndex < 8; ucIndex++)
    {
        pucHmacSha256Input[ucIndex + 10] = ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_MAIN_PORT(), 0x06, 0x93, (0x28 + ucIndex));
    }

    // Load Link_Pk (40-bits) = Receiver ID
    for(ucIndex = 0; ucIndex < 5; ucIndex++)
    {
        pucHmacSha256Input[ucIndex + 18] = g_stHdcp2RxDownLoadKeyType.pucHdcp2Certrx[ucIndex];
    }

    if(bRepeater == _TRUE)
    {
        // Load Link_S (160-bits) = V'
        for(ucIndex = 0; ucIndex < 20; ucIndex++)
        {
            pucHmacSha256Input[ucIndex + 23] = GET_DP_MST_RX_HDCP2_V(ucIndex);
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

    // Load SALT (168-bits) = Q_id | Q_id | Q_id
    for(ucIndex = 0; ucIndex < 3; ucIndex++)
    {
        for(BYTE ucIndex2 = 0; ucIndex2 < 7; ucIndex2++)
        {
            pucHmacSha256Input[((ucIndex * 7) + ucIndex2) + 43] = g_pucDpMstRxMsgQueryEncryptClientId[ucIndex2];
        }
    }

    SET_DP_MST_RX_HDCP2_LPRIME_CAL(pucHmacSha256Input);
}
#endif // End for #if(_DP_HDCP_2_2_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Backup Client ID of MSG "QUERY_STREAM_ENCRYPTION_STATUS"
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxQueryEncryptionBackupClientId(void)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < 7; ucIndex++)
    {
        g_pucDpMstRxMsgQueryEncryptClientId[ucIndex] = GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_CLIENT_ID(ucIndex);
    }
}
#endif // End for #if(_DP_TX_SUPPORT == _ON)

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Multi-function Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxMultiFunctionInitial(EnumInputPort enumInputPort)
{
    ScalerDpMstRxVirtualDpInitial(enumInputPort, ScalerDpMstRxDxPortNumMapping(enumInputPort));

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
    {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
        if(enumInputPort != _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
#endif
        {
            ScalerDpMstRxVirtualDpInitial(enumInputPort, ScalerDpMstRxDxPortNumMapping(_D9_INPUT_PORT));
        }
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    if(enumInputPort == GET_DP_RX_MAIN_PORT())
    {
        ScalerDpMstRxVirtualDpInitial(enumInputPort, ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT));
    }
#endif
}

//--------------------------------------------------
// Description  : Virtual DP Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxVirtualDpInitial(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort)
{
    bit bMultiFuncEn = ScalerDpMstRxGetMultiFuncEnableStatus(enumInputPort, enumMstPort);

    ScalerDpMstRxSetVirtualDpEnable(enumInputPort, enumMstPort, bMultiFuncEn);
    ScalerDpMstRxVirtualDpcdInitial(enumInputPort, enumMstPort);
    ScalerDpMstRxClrVirtualDpSinkEventNotify(enumInputPort, enumMstPort, _SINK_EVENT_ALL);
}

//--------------------------------------------------
// Description  : Virtual DP Initial
// Input Value  : enumMstPort
// Output Value : _TRUE if multi-function should be enabled
//--------------------------------------------------
bit ScalerDpMstRxGetMultiFuncEnableStatus(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort)
{
    enumMstPort = enumMstPort;

    if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
    {
        return _FALSE;
    }

    if(enumMstPort == _DP_PORT8)
    {
        return _TRUE;
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
        {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
            if(enumInputPort != _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
#endif
            {
                return _TRUE;
            }
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort <= _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
    {
        if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_UNPLUG)
        {
            return _FALSE;
        }

        if(GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_TX_MSG_SUPPORT)
        {
            return _FALSE;
        }

#if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) ||\
    (_DP_HBLANKING_MODIFY_SUPPORT == _ON))

        return _TRUE;

#else

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(ScalerDrrFreeSyncDpGetSupport(enumInputPort) == _FREESYNC_SUPPORT_ON)
        {
            return _TRUE;
        }
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
        if(ScalerDrrDpAdaptiveSyncGetSupport(enumInputPort) == _DP_ADAPTIVESYNC_SUPPORT_ON)
        {
            return _TRUE;
        }
#endif

        return _FALSE;

#endif // End of #if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) || (_DP_HBLANKING_MODIFY_SUPPORT == _ON))
    }
#endif

    return _FALSE;
}
//--------------------------------------------------
// Description  : Get Virtual DP Status
// Input Value  : enumOutputPort
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
void ScalerDpMstRxVirtualDpcdInitial(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort)
{
    BYTE ucTemp = 0;

    // Set DFP_PRESENT
    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x05, ~_BIT0, _BIT0);

    // Set DFP_COUNT
    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    // Set MSA_TIMING_PAR_IGNORED & AS SDP support bit
    ScalerDpMstRxAdaptivesyncVirtualDpcdSetting(enumInputPort, enumMstPort);

    // Reset ADAPTIVE_SYNC_SDP_EN & MSA_TIMING_PAR_IGNORE_EN
    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x01, 0x07, (_BIT7 | _BIT6), 0x00);
#elif(_DP_FREESYNC_SUPPORT == _ON)
    // Set MSA_TIMING_PAR_IGNORED support bit
    ScalerDpMstRxFreesyncVirtualDpcdSetting(enumInputPort, enumMstPort);

    // Reset MSA_TIMING_PAR_IGNORE_EN
    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x01, 0x07, _BIT7, 0x00);
#endif

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
    // Initialize HBE HBR Config
    // Set Buffer Size unit
    ucTemp = (_BIT5 | _BIT4 | _BIT1);

    // Set HBE HBR Cap
#if(_DP_HBE_SUPPORT == _ON)
    ucTemp = (ucTemp | _BIT3);
#endif

#if(_DP_HBLANKING_REDUCTION_SUPPORT == _ON)
    ucTemp = (ucTemp | _BIT6);
#endif

    ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x08, ucTemp);
    ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x09, _FW_DP_RX_HBLANKING_MODIFY_BUFFER_SIZE);

    // Reset HBE HBR Status
    for(ucTemp = 0; ucTemp <= 5; ucTemp ++)
    {
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x30, (0x54 + ucTemp), 0x00);
    }
#endif

    // Set MSTM_CAP
    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x21, ~_BIT0, _BIT0);

    // Reset GUID
    for(ucTemp = 0; ucTemp < 16; ucTemp++)
    {
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, (0x30 + ucTemp), 0x00);
    }

    if(ScalerDpMstRxValidLogicalPortJudge(enumMstPort) == _TRUE)
    {
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
        ScalerDpMstRxDscVirtualDpcdSetting(enumInputPort, enumMstPort);
#endif
    }
    else if(enumMstPort == _DP_PORT1)
    {
#if((_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON) || (_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON))
        ScalerDpMstRxDscVirtualDpcdSetting(enumInputPort, enumMstPort);
#endif
    }

    // Set Detail Cap Info
    ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x80, _BIT3);
    ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x81, 0x00);
    ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x82, 0x00);
    ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x83, 0x00);

    // Set SINK_COUNT
    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x02, 0x00, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

    // Reset Protocal Converter Status
    for(ucTemp = 0; ucTemp <= 3; ucTemp ++)
    {
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x30, (0x50 + ucTemp), 0x00);
    }
}

//--------------------------------------------------
// Description  : Get Virtual DP Status
// Input Value  : enumMstPort
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
bit ScalerDpMstRxGetVirtualDpEnable(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort)
{
    BYTE ucIndex = 0;

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            return g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].b1VirtualDpEnable;
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            return g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].b1VirtualDpEnable;
        }
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            return g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].b1VirtualDpEnable;
        }
    }
#endif

    return _DISABLE;
}

//--------------------------------------------------
// Description  : Set Virtual DP Status
// Input Value  : enumMstPort, _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetVirtualDpEnable(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, bit bEn)
{
    BYTE ucIndex = 0;

    bEn &= (ScalerDpMstRxGetDpVersion(enumInputPort) >= _DP_VERSION_1_4);

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].b1VirtualDpEnable = bEn;
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].b1VirtualDpEnable = bEn;
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].b1VirtualDpEnable = bEn;
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Virtual DPCD Table Information
// Input Value  : enumMstPort, DPCD Address
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpMstRxGetVirtualDpcdInfo(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL)
{
    BYTE ucIndex = 0;
    BYTE ucValue = ScalerDpAuxRxGetDpcdInfo(enumInputPort, ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL);
    BYTE ucField = 0xFF;
    EnumVirtualDpcdEntry enumEntry = ScalerDpMstRxGetVirtualDpcdEntry(enumInputPort, enumMstPort, ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL);

    // Special case for GUID_2 (0004Xh), return a common non-zero value which is generated by UUID v4 (random generater)
    if(enumEntry == _VIRTUAL_DPCD_0004XH_GUID_2)
    {
        BYTE pucVirtualGuid2[16] = {0xfc, 0xa7, 0x8a, 0xcf, 0xad, 0xd5, 0x44, 0xcc, 0x9d, 0xbe, 0x63, 0x8c, 0xed, 0x02, 0x40, 0x8d};

        return pucVirtualGuid2[(ucDpcdAddrL & 0x0F)];
    }

    // For the remaining DPCD registers, reply with the DPCD register values of its MST BU's DPRX
    if(enumEntry >= _VIRTUAL_DPCD_ENTRY_NONE)
    {
        return ucValue;
    }

    // Get Valid Bit Field
    switch(enumEntry)
    {
        case _VIRTUAL_DPCD_00005H:
            ucField = _BIT0;
            break;

        case _VIRTUAL_DPCD_00007H:
            ucField = (_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
            break;

        case _VIRTUAL_DPCD_00107H:
            ucField = _BIT7;
            break;

        default:
            break;
    }

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            return ((ucValue & ~ucField) | (g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].pucVirtualDpcd[enumEntry] & ucField));
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            return ((ucValue & ~ucField) | (g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].pucVirtualDpcd[enumEntry] & ucField));
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            return ((ucValue & ~ucField) | (g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].pucVirtualDpcd[enumEntry] & ucField));
        }
    }
#endif

    return 0;
}

//--------------------------------------------------
// Description  : Get Virtual DPCD Table Bit Information
// Input Value  : enumMstPort, DPCD Address, BitField
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpMstRxGetVirtualDpcdBitInfo(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL, BYTE ucDpcdBit)
{
    return (ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, enumMstPort, ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL) & ucDpcdBit);
}

//--------------------------------------------------
// Description  : Set Virtual DPCD Table Information
// Input Value  : enumMstPort, DPCD Address, DPCD Information
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetVirtualDpcdInfo(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL, BYTE ucValue)
{
    BYTE ucIndex = 0;
    EnumVirtualDpcdEntry enumEntry = ScalerDpMstRxGetVirtualDpcdEntry(enumInputPort, enumMstPort, ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL);

    if(enumEntry >= _VIRTUAL_DPCD_ENTRY_NONE)
    {
        return;
    }

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].pucVirtualDpcd[enumEntry] = ucValue;
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].pucVirtualDpcd[enumEntry] = ucValue;
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].pucVirtualDpcd[enumEntry] = ucValue;
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Set Virtual DPCD Table Information
// Input Value  : enumMstPort, DPCD Address, DPCD Information
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetVirtualDpcdBitInfo(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL, DWORD ulNotDpcdBit, BYTE ucDpcdBit)
{
    BYTE ucIndex = 0;
    BYTE ucTemp = ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, enumMstPort, ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL);
    EnumVirtualDpcdEntry enumEntry = ScalerDpMstRxGetVirtualDpcdEntry(enumInputPort, enumMstPort, ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL);

    if(enumEntry >= _VIRTUAL_DPCD_ENTRY_NONE)
    {
        return;
    }

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].pucVirtualDpcd[enumEntry] = (ucTemp & (BYTE)ulNotDpcdBit) | ucDpcdBit;
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].pucVirtualDpcd[enumEntry] = (ucTemp & (BYTE)ulNotDpcdBit) | ucDpcdBit;
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].pucVirtualDpcd[enumEntry] = (ucTemp & (BYTE)ulNotDpcdBit) | ucDpcdBit;
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Set Virtual DPCD Table Information
// Input Value  : enumMstPort, DPCD Address, DPCD Information
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetVirtualDpcdInfoBySrc(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL, BYTE ucValue)
{
    BYTE ucIndex = 0;
    EnumVirtualDpcdEntry enumEntry = _VIRTUAL_DPCD_ENTRY_NONE;
    bit bWriteClear = _FALSE;

    switch(TO_DWORD(0x00, ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL))
    {
        case 0x00107:
            enumEntry = _VIRTUAL_DPCD_00107H;
            break;

        case 0x00160:
        case 0x00161:
            enumEntry = (_VIRTUAL_DPCD_00160H + (ucDpcdAddrL & 0x0F));
            break;

        case 0x00030:
        case 0x00031:
        case 0x00032:
        case 0x00033:
        case 0x00034:
        case 0x00035:
        case 0x00036:
        case 0x00037:
        case 0x00038:
        case 0x00039:
        case 0x0003A:
        case 0x0003B:
        case 0x0003C:
        case 0x0003D:
        case 0x0003E:
        case 0x0003F:
            enumEntry = (_VIRTUAL_DPCD_00030H + (ucDpcdAddrL & 0x0F));
            break;

        case 0x0020F:
        case 0x02011:
            enumEntry = _VIRTUAL_DPCD_0020FH;
            bWriteClear = _TRUE;
            break;

        case 0x03050:
        case 0x03051:
        case 0x03052:
        case 0x03053:
        case 0x03054:
        case 0x03055:
        case 0x03056:
        case 0x03057:
        case 0x03058:
        case 0x03059:
            enumEntry = (_VIRTUAL_DPCD_03050H + (ucDpcdAddrL & 0x0F));
            break;

        default:
            break;
    }

    if(enumEntry == _VIRTUAL_DPCD_ENTRY_NONE)
    {
        return;
    }

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            if(bWriteClear == _TRUE)
            {
                g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].pucVirtualDpcd[enumEntry] &= ~ucValue;
            }
            else
            {
                g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].pucVirtualDpcd[enumEntry] = ucValue;
            }
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            if(bWriteClear == _TRUE)
            {
                g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].pucVirtualDpcd[enumEntry] &= ~ucValue;
            }
            else
            {
                g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].pucVirtualDpcd[enumEntry] = ucValue;
            }
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            if(bWriteClear == _TRUE)
            {
                g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].pucVirtualDpcd[enumEntry] &= ~ucValue;
            }
            else
            {
                g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].pucVirtualDpcd[enumEntry] = ucValue;
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Virtual DP Status
// Input Value  : enumOutputPort
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
EnumVirtualDpcdEntry ScalerDpMstRxGetVirtualDpcdEntry(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL)
{
    if(ScalerDpMstRxGetVirtualDpEnable(enumInputPort, enumMstPort) == _DISABLE)
    {
        return _VIRTUAL_DPCD_ENTRY_NONE;
    }

    switch(TO_DWORD(0x00, ucDpcdAddrH, ucDpcdAddrM, ucDpcdAddrL))
    {
        case 0x00005:
        case 0x02205:
            return _VIRTUAL_DPCD_00005H;

        case 0x00007:
        case 0x02207:
            return _VIRTUAL_DPCD_00007H;

        case 0x00008:
        case 0x02208:
            return _VIRTUAL_DPCD_00008H;

        case 0x00009:
        case 0x02209:
            return _VIRTUAL_DPCD_00009H;

        case 0x00021:
            return _VIRTUAL_DPCD_00021H;

        case 0x00030:
        case 0x00031:
        case 0x00032:
        case 0x00033:
        case 0x00034:
        case 0x00035:
        case 0x00036:
        case 0x00037:
        case 0x00038:
        case 0x00039:
        case 0x0003A:
        case 0x0003B:
        case 0x0003C:
        case 0x0003D:
        case 0x0003E:
        case 0x0003F:
            return (_VIRTUAL_DPCD_00030H + (ucDpcdAddrL & 0x0F));

        case 0x00040:
        case 0x00041:
        case 0x00042:
        case 0x00043:
        case 0x00044:
        case 0x00045:
        case 0x00046:
        case 0x00047:
        case 0x00048:
        case 0x00049:
        case 0x0004A:
        case 0x0004B:
        case 0x0004C:
        case 0x0004D:
        case 0x0004E:
        case 0x0004F:
            return _VIRTUAL_DPCD_0004XH_GUID_2;

        case 0x00060:
        case 0x00061:
        case 0x00062:
        case 0x00063:
        case 0x00064:
        case 0x00065:
        case 0x00066:
        case 0x00067:
        case 0x00068:
        case 0x00069:
        case 0x0006A:
        case 0x0006B:
        case 0x0006C:
        case 0x0006D:
        case 0x0006E:
        case 0x0006F:
            return (_VIRTUAL_DPCD_00060H + (ucDpcdAddrL & 0x0F));

        case 0x00080:
        case 0x00081:
        case 0x00082:
        case 0x00083:
            return (_VIRTUAL_DPCD_00080H + (ucDpcdAddrL & 0x0F));

        case 0x000A0:
        case 0x000A1:
        case 0x000A2:
            return (_VIRTUAL_DPCD_000A0H + (ucDpcdAddrL & 0x0F));

        case 0x00107:
            return _VIRTUAL_DPCD_00107H;

        case 0x00160:
        case 0x00161:
            return (_VIRTUAL_DPCD_00160H + (ucDpcdAddrL & 0x0F));

        case 0x00200:
        case 0x02002:
            return _VIRTUAL_DPCD_00200H;

        case 0x0020F:
        case 0x02011:
            return _VIRTUAL_DPCD_0020FH;

        case 0x00240:
        case 0x00241:
        case 0x00242:
        case 0x00243:
        case 0x00244:
        case 0x00245:
            return (_VIRTUAL_DPCD_00240H + (ucDpcdAddrL & 0x0F));

        case 0x03050:
        case 0x03051:
        case 0x03052:
        case 0x03053:
        case 0x03054:
        case 0x03055:
        case 0x03056:
        case 0x03057:
        case 0x03058:
        case 0x03059:
            return (_VIRTUAL_DPCD_03050H + (ucDpcdAddrL & 0x0F));

        default:
            break;
    }

    return _VIRTUAL_DPCD_ENTRY_NONE;
}

//--------------------------------------------------
// Description  : Get Virtual Dp Sink Event Notify
// Input Value  : enumMstPort
// Output Value : EnumDpMSTSinkEventID
//--------------------------------------------------
EnumDpMSTSinkEventID ScalerDpMstRxGetVirtualDpSinkEventNotify(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort)
{
    BYTE ucIndex = 0;

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            return g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].enumSinkEventID;
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            return g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].enumSinkEventID;
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            return g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].enumSinkEventID;
        }
    }
#endif

    return _SINK_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Set Virtual Dp Sink Event Notify
// Input Value  : enumMstPort, enumSinkEventID
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetVirtualDpSinkEventNotify(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, EnumDpMSTSinkEventID enumSinkEventID)
{
    BYTE ucIndex = 0;

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].enumSinkEventID |= enumSinkEventID;
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].enumSinkEventID |= enumSinkEventID;
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].enumSinkEventID |= enumSinkEventID;
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Clear Virtual Dp Sink Event Notify
// Input Value  : enumMstPort, enumSinkEventID
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxClrVirtualDpSinkEventNotify(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, EnumDpMSTSinkEventID enumSinkEventID)
{
    BYTE ucIndex = 0;

    if(enumMstPort == _DP_PORT8)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort8[ucIndex].enumSinkEventID &= ~enumSinkEventID;
        }
    }
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    else if(enumMstPort == _DP_PORT9)
    {
        ucIndex = enumInputPort - _D0_INPUT_PORT;

        if(ucIndex < _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstLogicPort9[ucIndex].enumSinkEventID &= ~enumSinkEventID;
        }
    }
#endif
#if(_DP_TX_SUPPORT == _ON)
    else if(enumMstPort < _DP_PORT8)
    {
        ucIndex = enumMstPort - _DP_PORT1;

        if(ucIndex < _DP_MST_RX_NUM_OF_OUTPUT_PORTS)
        {
            g_stDpMstRxMultiFunc.pstPhyPort[ucIndex].enumSinkEventID &= ~enumSinkEventID;
        }
    }
#endif
}

//--------------------------------------------------
// Description  : DP Tx Up Request Event Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxVirtualDpUpRequestEventCheck(void)
{
    EnumDpMstRxUpReqQueue enumDpMstRxUpReqQueueTemp = _RX_UP_REQ_QUEUE_NONE;

    // Check if there is SEN to be sent
    if((enumDpMstRxUpReqQueueTemp = ScalerDpMstRxVirtualDpSenEventCheck()) != _RX_UP_REQ_QUEUE_NONE)
    {
        DebugMessageMst("Rx SEN Gen!!!", enumDpMstRxUpReqQueueTemp);

        ScalerDpRxSetBaseInputPort(GET_DP_MST_RX_UP_REQUEST_QUEUE_INPUT_PORT(enumDpMstRxUpReqQueueTemp));

        SET_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE(enumDpMstRxUpReqQueueTemp);

        // Initiate Sink Event Notify
        SET_DP_MST_RX_GEN_UP_REQUEST_MSG(_DP_MSG_SINK_EVENT_NOTIFY);

        SET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(GET_DP_MST_RX_UP_REQUEST_QUEUE_INPUT_PORT(enumDpMstRxUpReqQueueTemp));
    }
}

//--------------------------------------------------
// Description  : DP Tx Delete SEN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxVirtualDpSenEventDelete(EnumDpMstRxUpReqQueue enumSenQueue)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    if(enumSenQueue == _RX_UP_REQ_QUEUE_NONE)
    {
        return;
    }

#if(_DP_TX_SUPPORT == _ON)
    if(enumSenQueue == _RX_UP_REQ_QUEUE_PORT1)
    {
        enumInputPort = GET_DP_RX_MAIN_PORT();
    }
    else
#endif
    {
        enumInputPort = GET_DP_MST_RX_UP_REQUEST_QUEUE_INPUT_PORT(enumSenQueue);
    }

    ScalerDpRxSetBaseInputPort(enumInputPort);

    if((GET_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE() == enumSenQueue) &&
       (GET_DP_MST_RX_UP_REQUEST_ISSUED_ID() == _DP_MSG_SINK_EVENT_NOTIFY))
    {
        CLR_DP_MST_RX_UP_REQUEST_PROCESSING();

        if((GET_DP_MST_RX_UP_REQUEST_ANAL() == _TRUE) || (GET_DP_MST_RX_UP_REQUEST_READY() == _TRUE))
        {
            SET_DP_MST_RX_REQUEST_POOL_FREE();

            SET_DP_MST_RX_REPLY_BUF_FREE();
        }

        // Delete item
        ScalerDpMstRxClrVirtualDpSinkEventNotify(enumInputPort, GET_DP_MST_RX_UP_REQUEST_QUEUE_PORT_NUM(enumSenQueue), GET_DP_MST_RX_UP_REQUEST_ISSUED_SINK_EVENT_ID());

        CLR_DP_MST_RX_UP_REQUEST_ISSUED_SINK_EVENT_ID();

        CLR_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE();

        CLR_DP_MST_RX_UP_REQUEST_ISSUED_ID();

        CLR_DP_MST_RX_GEN_UP_REQUEST_MSG();

        CLR_DP_MST_RX_UP_REQUEST_BYPASS_DONE();

        CLR_DP_MST_RX_UP_REQUEST_RETRY_NUM();

        CLR_DP_MST_RX_UP_REQUEST_ANAL();

        CLR_DP_MST_RX_UP_REQUEST_READY();
    }
    else
    {
        // For reset case
        ScalerDpMstRxClrVirtualDpSinkEventNotify(enumInputPort, GET_DP_MST_RX_UP_REQUEST_QUEUE_PORT_NUM(enumSenQueue), _SINK_EVENT_ALL);
    }
}

//--------------------------------------------------
// Description  : DP Tx Check SEN event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumDpMstRxUpReqQueue ScalerDpMstRxVirtualDpSenEventCheck(void)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;
    EnumDpMstPort enumDpMstPort = ScalerDpMstRxDxPortNumMapping(GET_DP_RX_MAIN_PORT());

    // Check Main Port SEN
    if(ScalerDpMstRxGetVirtualDpSinkEventNotify(GET_DP_RX_MAIN_PORT(), enumDpMstPort) != _SINK_EVENT_NONE)
    {
        if(ScalerDpRxGetSrcMstUpRequestEnable(GET_DP_RX_MAIN_PORT()) == _TRUE)
        {
            if(ScalerDpMstRxUpRequestAllowedCheck(GET_DP_RX_MAIN_PORT()) == _TRUE)
            {
                return GET_DP_MST_RX_UP_REQUEST_QUEUE(GET_DP_RX_MAIN_PORT(), enumDpMstPort);
            }
        }
        else
        {
            ScalerDpMstRxClrVirtualDpSinkEventNotify(GET_DP_RX_MAIN_PORT(), enumDpMstPort, _SINK_EVENT_ALL);
        }
    }

    // Check Other Port SEN
    for(enumInputPort = _D0_INPUT_PORT; enumInputPort <= _D2_INPUT_PORT; enumInputPort++)
    {
        enumDpMstPort = ScalerDpMstRxDxPortNumMapping(enumInputPort);

        if(ScalerDpRxGetMstCapability(enumInputPort) == _FALSE)
        {
            continue;
        }

        if(enumInputPort == GET_DP_RX_MAIN_PORT())
        {
            continue;
        }

        if(ScalerDpMstRxGetVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort) != _SINK_EVENT_NONE)
        {
            if(ScalerDpRxGetSrcMstUpRequestEnable(enumInputPort) == _TRUE)
            {
                if(ScalerDpMstRxUpRequestAllowedCheck(enumInputPort) == _TRUE)
                {
                    return GET_DP_MST_RX_UP_REQUEST_QUEUE(enumInputPort, enumDpMstPort);
                }
            }
            else
            {
                ScalerDpMstRxClrVirtualDpSinkEventNotify(enumInputPort, enumDpMstPort, _SINK_EVENT_ALL);
            }
        }
    }

#if(_DP_TX_SUPPORT == _ON)
    enumDpMstPort = ScalerDpMstTxPxPortNumMapping(_P0_OUTPUT_PORT);

    // Check Tx Port SEN
    if(ScalerDpMstRxGetVirtualDpSinkEventNotify(GET_DP_RX_MAIN_PORT(), enumDpMstPort) != _SINK_EVENT_NONE)
    {
        if(ScalerDpRxGetSrcMstUpRequestEnable(GET_DP_RX_MAIN_PORT()) == _TRUE)
        {
            if(ScalerDpMstRxUpRequestAllowedCheck(GET_DP_RX_MAIN_PORT()) == _TRUE)
            {
                return _RX_UP_REQ_QUEUE_PORT1;
            }
        }
        else
        {
            ScalerDpMstRxClrVirtualDpSinkEventNotify(GET_DP_RX_MAIN_PORT(), enumDpMstPort, _SINK_EVENT_ALL);
        }
    }
#endif

    return _RX_UP_REQ_QUEUE_NONE;
}

//--------------------------------------------------
// Description  : DSC Virtual DPCD Setting
// Input Value  : enumMstPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxDscVirtualDpcdSetting(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort)
{
    EnumDscDecoderSupport enumDscDecoderSupport = _DSC_DECODER_SUPPORT_OFF;

    if(ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x00, 0x21, _BIT0) == _BIT0)
    {
        if(ScalerDpMstRxValidLogicalPortJudge(enumMstPort) == _TRUE)
        {
#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderSupport = ScalerDscDecoderGetSupport(ScalerDpMstRxInputPortJudge(enumInputPort, enumMstPort));
#endif
        }
        else if(enumMstPort == _DP_PORT1)
        {
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            enumDscDecoderSupport = ScalerDscDecoderDpMstToSstGetSupport();
#endif
        }
    }

    if(enumDscDecoderSupport == _DSC_DECODER_SUPPORT_ON)
    {
        // Set DSC Support, Dynamic PPS Compressed-to-Compressed Support
        ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x60, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        // Set DSC Algorithm Revision V1.2
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x61, 0x21);

        // Set DSC RC Buffer Block Size = 1KB
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x62, 0x00);

        // Set DSC Buffer Size = 5KB
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x63, 0x04);

        // Set DSC Slice Capabilities 1: 1/ 2/ 4/ 8
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x64, _HW_DP_AUX_DPCD_DSC_SLICE_CAPABILITY);

        // Set DSC Line Buffer Bit Depth = 13bits
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x65, 0x04);

        // Set DSC Block Prediction Support, Simple422 CRC Support: 444 TEST_CRC for YCbCr Simple 422 Support
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x66, 0x09);

#if(_DP_RX_COLOR_FORMAT_420_SUPPORT == _ON)
        // Set DSC Decoder Color Format Capabilities: Simple444, Simple422, Native422, Native420
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x69, 0x1F);
#else
        // Set DSC Decoder Color Format Capabilities: Simple444, Simple422, Native422
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x69, 0x0F);
#endif

        // Set DSC Decoder Color Depth Capabilities
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6A, 0x0E);

        // Set Peak DSC Throughput, Throughout Mode 0 = 340MP/s, Throughout Mode 1 = 340MP/s
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6B, 0x11);

        // Set Maximum Slice Width = 2560pixels
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6C, 0x08);

        // Set DSC Slice Capabilities 2: 1/ 2/ 4/ 8
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6D, 0x00);

        // Set MAX_BPP_DELTA_AVAILABILITY Avaliable at DPCD 0006Eh[7:0] and 0006Fh[6:3]
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x68, 0x80);

        // Set Maximum bits_per_pixel Supporte: YCbCr444 and Simple YCbCr422 with 16bpp, Natvie YCbCr420 with 12bpp
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6E, 0x21);

        // Set Maximum bits_per_pixel Supporte: Natvie YCbCr422 with 16bpp, Set bits_per_pixel Increment = 1/16bpp
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6F, 0x08);

        // Reset DSC Decompression & Pass-through Enable
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x01, 0x60, 0x00);

        // Reset DSC Configuration
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x01, 0x61, 0x00);

        // Reset DSC Status
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x02, 0x0F, 0x00);
    }
    else
    {
        // Reset DSC Support
        ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x60, ~(_BIT2 | _BIT0), 0x00);

        // Reset DSC Algorithm Revision
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x61, 0x00);

        // Reset DSC RC Buffer Block Size
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x62, 0x00);

        // Reset DSC Buffer Size
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x63, 0x00);

        // Reset DSC Slice Capabilities 1
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x64, 0x00);

        // Reset DSC Line Buffer Bit Depth
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x65, 0x00);

        // Reset DSC Block Prediction Support
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x66, 0x00);

        // Reset Maximum bits_per_pixel
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x67, 0x00);
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x68, 0x00);

        // Reset DSC Decoder Color Format Capabilities
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x69, 0x00);

        // Reset DSC Decoder Color Depth Capabilities
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6A, 0x00);

        // Reset Peak DSC Throughput
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6B, 0x00);

        // Reset Maximum Slice Width
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6C, 0x00);

        // Reset DSC Slice Capabilities 2
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6D, 0x00);

        // Reset Maximum bits_per_pixel
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6E, 0x00);

        // Reset bits_per_pixel Increment
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x6F, 0x00);

        // Reset DSC Decompression & Pass-through Enable
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x01, 0x60, 0x00);

        // Reset DSC Configuration
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x01, 0x61, 0x00);

        // Reset DSC Status
        ScalerDpMstRxSetVirtualDpcdInfo(enumInputPort, enumMstPort, 0x00, 0x02, 0x0F, 0x00);
    }

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    if(enumMstPort == _DP_PORT1)
    {
        ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x60, ~_BIT1, _BIT1);
    }
#endif
}

//--------------------------------------------------
// Description  : Switch DP DSC Support
// Input Value  : Hotplug Type and DSC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxDscSupportSwitch(EnumInputPort enumInputPort)
{
    DebugMessageMst("DP MST Down Request Port", GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM());
    DebugMessageMst("V-DPCD 00060h =", ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x00, 0x60));
    DebugMessageMst("V-DPCD 00160h =", ScalerDpMstRxGetVirtualDpcdInfo(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x01, 0x60));

    if(ScalerDpMstRxValidLogicalPortJudge(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()) == _TRUE)
    {
        EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch(enumInputPort);
        enumDpMacSel = enumDpMacSel;

        enumDpMacSel = enumDpMacSel;

        switch(enumInputPort)
        {
#if(_D0_DP_SUPPORT == _ON)
            case _D0_INPUT_PORT:

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                if(ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x00, 0x60, _BIT0) == _BIT0)
                {
                    if(ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x01, 0x60, _BIT0) == _BIT0)
                    {
                        if((ScalerDpMacStreamRxGetFifoWDStatus(_D0_INPUT_PORT) == _ENABLE) && (ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel) == _DSC_MAC_NONE))
                        {
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D0_INPUT_PORT, _ENABLE);
                        }
                    }
                    else
                    {
                        if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel) != _DSC_MAC_NONE)
                        {
                            ScalerDpMacDscRxDscStreamSetChange(enumDpMacSel, _ENABLE);
                        }
                        else
                        {
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D0_INPUT_PORT, _DISABLE);
                        }
                    }
                }
#endif
                break;
#endif

#if(_D1_DP_SUPPORT == _ON)
            case _D1_INPUT_PORT:

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                if(ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x00, 0x60, _BIT0) == _BIT0)
                {
                    if(ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x01, 0x60, _BIT0) == _BIT0)
                    {
                        if((ScalerDpMacStreamRxGetFifoWDStatus(_D1_INPUT_PORT) == _ENABLE) && (ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel) == _DSC_MAC_NONE))
                        {
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D1_INPUT_PORT, _ENABLE);
                        }
                    }
                    else
                    {
                        if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel) != _DSC_MAC_NONE)
                        {
                            ScalerDpMacDscRxDscStreamSetChange(enumDpMacSel, _ENABLE);
                        }
                        else
                        {
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D1_INPUT_PORT, _DISABLE);
                        }
                    }
                }
#endif
                break;
#endif

#if(_D2_DP_SUPPORT == _ON)
            case _D2_INPUT_PORT:

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
                if(ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x00, 0x60, _BIT0) == _BIT0)
                {
                    if(ScalerDpMstRxGetVirtualDpcdBitInfo(enumInputPort, GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x01, 0x60, _BIT0) == _BIT0)
                    {
                        if((ScalerDpMacStreamRxGetFifoWDStatus(_D2_INPUT_PORT) == _ENABLE) && (ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel) == _DSC_MAC_NONE))
                        {
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D2_INPUT_PORT, _ENABLE);
                        }
                    }
                    else
                    {
                        if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel) != _DSC_MAC_NONE)
                        {
                            ScalerDpMacDscRxDscStreamSetChange(enumDpMacSel, _ENABLE);
                        }
                        else
                        {
                            ScalerDpMacStreamRxDscSetStreamIRQAndWD(_D2_INPUT_PORT, _DISABLE);
                        }
                    }
                }
#endif
                break;
#endif

            default:
                break;
        }
    }
    else if(GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM() == _DP_PORT1)
    {
#if((_DP_TX_SUPPORT == _ON) && (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
        if(ScalerDpMstRxGetVirtualDpcdBitInfo(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x00, 0x60, _BIT1) == _BIT1)
        {
            if(ScalerDpMstRxGetVirtualDpcdBitInfo(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x01, 0x60, _BIT1) == _BIT1)
            {
                SET_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH();
            }
            else
            {
                CLR_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH();
            }
        }
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
        if(ScalerDpMstRxGetVirtualDpcdBitInfo(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x00, 0x60, _BIT0) == _BIT0)
        {
            EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitchMappingSourceType(_STREAM_SOURCE_MST2SST);

            if(ScalerDpMstRxGetVirtualDpcdBitInfo(GET_DP_RX_MAIN_PORT(), GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(), 0x00, 0x01, 0x60, _BIT0) == _BIT0)
            {
                SET_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE();
            }
            else
            {
                // If Dsc Decoder Enable for MST2SST, Source Clr 00160h, Set Change Flag for Stable Detect
                if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumDpMacSel) != _DSC_MAC_NONE)
                {
                    ScalerDpMacDscRxDscStreamSetChange(enumDpMacSel, _ENABLE);
                }

                CLR_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE();
            }
        }
#endif
    }
}

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Freesync Virtual DPCD Setting
// Input Value  : enumMstPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxFreesyncVirtualDpcdSetting(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort)
{
    bit bEnable = (ScalerDrrFreeSyncDpGetSupport(enumInputPort) == _FREESYNC_SUPPORT_ON);

    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x07, ~_BIT6, ((BYTE)bEnable << 6));
}
#endif // End of #if(_DP_FREESYNC_SUPPORT == _ON)

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Adaptivesync Virtual DPCD Setting
// Input Value  : enumMstPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxAdaptivesyncVirtualDpcdSetting(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort)
{
    bit bEnable = (ScalerDrrDpAdaptiveSyncGetSupport(enumInputPort) == _DP_ADAPTIVESYNC_SUPPORT_ON);

    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x00, 0x07, ~_BIT6, ((BYTE)bEnable << 6));

    ScalerDpMstRxSetVirtualDpcdBitInfo(enumInputPort, enumMstPort, 0x00, 0x22, 0x14, ~_BIT0, bEnable);
}
#endif // End of #if(_DP_ADAPTIVESYNC_SUPPORT == _ON)

#endif // End of #if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpMstRxGetRegDownRequestRad(EnumInputPort enumInputPort, BYTE ucRadIndex)
{
    if(ucRadIndex >= (sizeof(tDpMstRxRadBaseBitMap) / sizeof(tDpMstRxRadBaseBitMap[0])))
    {
        return 0;
    }

    ScalerDpRxSetBaseInputPort(enumInputPort);

    BYTE ucBaseBit = tDpMstRxRadBaseBitMap[ucRadIndex];
    DWORD ulMask = (0x0FU) << ucBaseBit;
    DWORD ulAddress = ((ucRadIndex < 6) ? PB18003_14_MSG_RX_DATA0 : PB18003_18_MSG_RX_DATA1);

    DWORD ulValue = SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, ulAddress, ulMask);

    return (ulValue >> ucBaseBit) % 0x0F;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpMstRxSetRegUpstreamReplyRad(EnumInputPort enumInputPort, BYTE ucRadIndex, BYTE ucValue)
{
    if(ucRadIndex >= (sizeof(tDpMstRxRadBaseBitMap) / sizeof(tDpMstRxRadBaseBitMap[0])))
    {
        return;
    }

    ScalerDpRxSetBaseInputPort(enumInputPort);

    BYTE ucBaseBit = tDpMstRxRadBaseBitMap[ucRadIndex];
    DWORD ulMask = (0x0FU) << ucBaseBit;
    DWORD ulAddress = ((ucRadIndex < 6) ? PB18003_AC_MSG_TX_SET0 : PB18003_B0_MSG_TX_SET1);

    DWORD ulValue = ((ucValue % 0x0F) << ucBaseBit);

    SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, ulAddress, ~ulMask, ulValue);
}

#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

#if((_DP_SUPPORT == _ON) && ((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : DP MST Power-On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxPowerOnInitial(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
    SET_DP_MST_RX_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);

    SET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_MST_RX_DOWN_REQUEST_BUF0);

    // Free Request Array
    SET_DP_MST_RX_REQUEST_POOL_FREE();

    // Free Reply Array
    SET_DP_MST_RX_REPLY_POOL_FREE();

    // Free Reply Buffer
    SET_DP_MST_RX_REPLY_BUF_FREE();

    CLR_DP_MST_RX_GEN_UP_REQUEST_MSG();

    CLR_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE();

    SET_DP_MST_RX_GEN_DOWN_REQUEST_MSG(_DP_MSG_NONE);
#endif

    ScalerDpMstRxResetStreamToIdMapping(enumInputPort);

    ScalerDpMstRxResetSourceMuxBackup(enumInputPort);

    ScalerDpMacDphyRxResetSourceMuxReg(enumInputPort);

    ScalerDpMstRxResetStreamStatusBackup(enumInputPort);

    ScalerDpMstRxResetStreamStartBackup(enumInputPort);

    ScalerDpMstRxResetStreamEndBackup(enumInputPort);

    ScalerDpMstRxResetStreamPositionReg(enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
    ScalerDpMacTxResetStreamToIdMapping();

    ScalerDpMacTxResetDaisySourceMuxBackup();

    ScalerDpMacTxResetDaisySourceMuxReg();

    ScalerDpMacTxResetDaisyStreamPositionReg();

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpMstTxCsnEventReset();

    ScalerDpMstTxSenEventReset();

    CLR_DP_MST_TX_GEN_UP_REQUEST_MSG();

    CLR_DP_MST_TX_UP_REQUEST_INITIATED_QUEUE();
#endif
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
    // Enable MSG Force Ack Address Unexpect
    SET_DP_MST_RX_REG_DOWN_REQUEST_FORCE_ACK_ADDRESS_UNEXPECT();
    SET_DP_MST_RX_REG_UP_REPLY_FORCE_ACK_ADDRESS_UNEXPECT();

    // Enable BUF0 / BUF1 MSG Receive Double Buffer
    SET_DP_MST_RX_REG_DOWN_REQUEST_MSG_DOUBLE_BUFFER_ENABLE();

    // Rx0 Down Requeset BUF0 / BUF1 MSG Receive and Header/ Body Crc Ignore Enable
    SET_DP_MST_RX_REG_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE();

    // Rx0 Up Reply BUF0 / BUF1 MSG Receive and Header/ Body Crc Ignore Enable
    SET_DP_MST_RX_REG_UP_REPLY_MSG_RECEIVE_CRC_IGNORE_ENABLE();

    // Reset MSG FSM as 0x01000 Written
    SET_DP_MST_RX_REG_DOWN_REQUEST_WRITE_1000_RST_FSM();
    SET_DP_MST_RX_REG_UP_REPLY_WRITE_1000_RST_FSM();

    // Reset MSG Flags as 0x01000 Written
    SET_DP_MST_RX_REG_DOWN_REQUEST_WRITE_1000_RST_FLAG();
    SET_DP_MST_RX_REG_UP_REPLY_WRITE_1000_RST_FLAG();

    // Reset Data Buffer as 0x01000 Written
    SET_DP_MST_RX_REG_DOWN_REQUEST_WRITE_1000_RST_BUF();
    SET_DP_MST_RX_REG_UP_REPLY_WRITE_1000_RST_BUF();
#endif
}

//--------------------------------------------------
// Description  : DP Mst Reset
// Input Value  : EnumDpRxMstPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxReset(EnumInputPort enumInputPort)
{
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus(enumInputPort);

    if(enumInputPort == _NO_INPUT_PORT)
    {
        return;
    }

    ScalerDpRxSetBaseInputPort(enumInputPort);

// HW Reset-----------------------------------

    DebugMessageMst("[MST] Dx MST Reset!!", (enumInputPort - _D0_INPUT_PORT));

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        // AUX manual mode
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

#if(_DP_MST_SUPPORT == _ON)
    // MST Aux Reset
    ScalerDpAuxRxMstReset(enumInputPort);
#endif

    // MST Mac Reset
    ScalerDpMacDphyRxMstReset(enumInputPort);

    // Reset Rx Source Mux Reg
    ScalerDpMacDphyRxResetSourceMuxReg(enumInputPort);

    // Reset ACT signal coding type
    ScalerDpMstRxResetActSignalCodingType(enumInputPort);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _OFF)
    {
        // Reset PXP Mac Input Port Mux
        ScalerDpRxResetPxpInputPortMux(enumInputPort);
    }
#endif

#if(_DP_TX_SUPPORT == _ON)
    // Reset MST Tx Source Mux
    ScalerDpMstRxResetTxStreamSourceMux(enumInputPort);
#endif

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        // AUX Auto mode
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }

// FW Reset-----------------------------------

#if(_DP_MST_SUPPORT == _ON)
    // MSG Status Reset
    SET_DP_MST_RX_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);

    // Free Reply Buffer
    SET_DP_MST_RX_REPLY_BUF_FREE();

    CLR_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT();

    if(enumInputPort == GET_DP_MST_RX_REQUEST_MSG_PORT())
    {
        // MSG Status Reset
        SET_DP_MST_RX_EVENT(_DP_RX_NONE_EVENT);

        // Free Request Pool Array
        SET_DP_MST_RX_REQUEST_POOL_FREE();

        // Clear Down Request MSG Proc Flags
        CLR_DP_MST_RX_DOWN_REQUEST_ANAL();
        CLR_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG();

        // Clear Self Gen Down Request MSG Proc Flags
        CLR_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG();
        CLR_DP_MST_RX_GEN_DOWN_REQUEST_MSG();

        // Clear Up Request MSG Proc Flags
        CLR_DP_MST_RX_UP_REQUEST_READY();
        CLR_DP_MST_RX_UP_REQUEST_ANAL();
        CLR_DP_MST_RX_ILLEGAL_UP_REQUEST_MSG();
    }

    if(enumInputPort == GET_DP_MST_RX_REPLY_MSG_PORT())
    {
        // Free Reply Pool Array
        SET_DP_MST_RX_REPLY_POOL_FREE();

        // Clear Down Reply MSG Proc Flags
        CLR_DP_MST_RX_DOWN_REPLY_READY();
        CLR_DP_MST_RX_DOWN_REPLY_BYPASS();
        CLR_DP_MST_RX_DOWN_REPLY_DIRECTLY();

        // Clear Up Reply MSG Proc Flags
        CLR_DP_MST_RX_UP_REPLY_ANAL();
    }
#endif

    // Clear Allocated Flag Manual Mode
    CLR_DP_MAC_DPHY_RX_MANUAL_FORCE_SET_ACT();

    // Reset Stream Allocate info
    ScalerDpMacDphyRxResetStreamAllocateInfo(enumInputPort);

    // Reset Stream ID Mapping Table
    ScalerDpMstRxResetStreamToIdMapping(enumInputPort);

    // Reset Rx Source Mux Backup
    ScalerDpMstRxResetSourceMuxBackup(enumInputPort);

    // Reset Rx Position Backup
    ScalerDpMstRxResetStreamStatusBackup(enumInputPort);
    ScalerDpMstRxResetStreamStartBackup(enumInputPort);
    ScalerDpMstRxResetStreamEndBackup(enumInputPort);

#if(_DP_MST_SUPPORT == _ON)
    // Clear Down Request MSG Proc Flags
    SET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_MST_RX_DOWN_REQUEST_BUF0);

    // Clear Down Reply MSG Proc Flags
    CLR_DP_MST_RX_DOWN_REPLY_SET_HPD();
    CLR_DP_MST_RX_REG_DOWN_REPLY_MSG_IS_READ();

#if(_DP_MST_RX_DOWN_REPLY_MANUAL_MODE_SUPPORT == _ON)
    // Clear the Rx Down Reply MSG Segment Count No.
    CLR_DP_MST_RX_DOWN_REPLY_MSG_COUNT();
#endif

    // Clear Up Request MSG Proc Flags
    CLR_DP_MST_RX_UP_REQUEST_BYPASS_DONE();
    CLR_DP_MST_RX_UP_REQUEST_RETRY_NUM();

    // Clear Up Reply MSG Proc Flags
    SET_DP_MST_RX_UP_REPLY_BUF_PRIORITY(_DP_MST_RX_UP_REPLY_BUF0);

    ScalerTimerCancelTimerEvent(ScalerDpMstRxGetTimerEvent(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
    ScalerDpMstRxMultiFunctionInitial(enumInputPort);
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    CLR_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(enumInputPort);
#endif
#endif

// Tx Reset-----------------------------------

#if(_DP_TX_SUPPORT == _ON)
#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
    if(enumInputPort == GET_DP_RX_MAIN_PORT())
    {
#if(_DP_MST_SUPPORT == _ON)
        // Disable MST to SST
        CLR_DP_MAC_MST2SST_ENABLE();

        ScalerDpMstTxSetOutputPortStatusReported(_CONNECT_STATUS_NONE);
#endif

        ScalerDpMstTxReset();

#if((_DP_MST_SUPPORT == _ON) && (_DP_MAC_TX_SUPPORT == _ON) && (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
        ScalerDpMacTxDscPassThroughReset();
#endif
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : Reset MST Rx stream to ID array
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxResetStreamToIdMapping(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    // Reset Stream ID Mapping Table
    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        SET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(enumInputPort, enumDpStreamNum, 0);
    }
}

//--------------------------------------------------
// Description  : Reset DP Mst Rx ACT Signal coding type
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerDpMstRxResetActSignalCodingType(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18001_C0_AUX_PAYLOAD_CTRL, ~_BIT5, 0x00);
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6 Source Mux Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxResetSourceMuxBackup(EnumInputPort enumInputPort)
{
    EnumDpStreamSourceNum enumSourceNum = _DP_ST_SOURCE1;

    for(enumSourceNum = _DP_ST_SOURCE1; enumSourceNum <= _DP_ST_SOURCE_END; enumSourceNum++)
    {
        ScalerDpMacDphyRxSetSourceMuxBackup(enumInputPort, enumSourceNum, _DP_ST_NONE);
    }
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6 Start Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxResetStreamStartBackup(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        ScalerDpMstRxSetStreamStartBackup(enumInputPort, enumDpStreamNum, 0x00);
    }
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6 End Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxResetStreamEndBackup(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        ScalerDpMstRxSetStreamEndBackup(enumInputPort, enumDpStreamNum, 0x00);
    }
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6 Status Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxResetStreamStatusBackup(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
        ScalerDpMstRxSetStreamStatusBackup(enumInputPort, enumDpStreamNum, _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Set ST1 ~ ST6 Start Backup
// Input Value  : EnumDpStreamNum, BYTE ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetStreamStartBackup(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, BYTE ucValue)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(GET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(enumDpStreamNum) != ucValue)
    {
        SET_DP_MAC_DPHY_RX_ST_START_POSITION_BACKUP(enumDpStreamNum, ucValue);

        if(ScalerDpMacRxGetPowerCutFlagStatus(enumInputPort) == _FALSE)
        {
            SET_DP_MAC_DPHY_RX_REG_ST_START_POSITION(enumDpStreamNum, ucValue);
        }
        else
        {
            SET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE();
        }
    }
}

//--------------------------------------------------
// Description  : Set ST1 ~ ST6 End Backup
// Input Value  : EnumDpStreamNum, BYTE ucValue
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetStreamEndBackup(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, BYTE ucValue)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(GET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(enumDpStreamNum) != ucValue)
    {
        SET_DP_MAC_DPHY_RX_ST_END_POSITION_BACKUP(enumDpStreamNum, ucValue);

        if(ScalerDpMacRxGetPowerCutFlagStatus(enumInputPort) == _FALSE)
        {
            SET_DP_MAC_DPHY_RX_REG_ST_END_POSITION(enumDpStreamNum, ucValue);
        }
        else
        {
            SET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE();
        }
    }
}

//--------------------------------------------------
// Description  : Set ST1 ~ ST6 Status Backup
// Input Value  : EnumDpStreamNum, bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetStreamStatusBackup(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, bit bEnable)
{
    ScalerDpRxSetBaseInputPort(enumInputPort);

    if(GET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(enumDpStreamNum) != bEnable)
    {
        SET_DP_MAC_DPHY_RX_ST_STATUS_BACKUP(enumDpStreamNum, bEnable);

        if(ScalerDpMacRxGetPowerCutFlagStatus(enumInputPort) == _FALSE)
        {
            SET_DP_MAC_DPHY_RX_REG_ST_STATUS(enumDpStreamNum, bEnable);
        }
        else
        {
            SET_DP_MAC_DPHY_RX_ST_POSITION_CHANGE();
        }
    }
}

//--------------------------------------------------
// Description  : Reset ST1 ~ ST6
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxResetStreamPositionReg(EnumInputPort enumInputPort)
{
    EnumDpStreamNum enumDpStreamNum = _DP_ST_1;

    ScalerDpRxSetBaseInputPort(enumInputPort);

    for(enumDpStreamNum = _DP_ST_1; enumDpStreamNum <= _DP_ST_END; enumDpStreamNum++)
    {
#if(_DP_MST_SUPPORT == _ON)

        // Reset Start Position
        ScalerSetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_8B10B() + ((enumDpStreamNum) << 1)), ~0x3F, (0x00));

        // Reset End Position
        ScalerSetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_8B10B() + ((enumDpStreamNum) << 1) + 1), ~0x3F, (0x00));
#endif

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)

        // Reset Stream Enable
        ScalerSetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_128B132B() + ((enumDpStreamNum) << 1)), ~_BIT7, (0x00));

        // Reset Start Position
        ScalerSetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_128B132B() + ((enumDpStreamNum) << 1)), ~0x3F, (0x00));

        // Reset End Position
        ScalerSetBit((GET_DP_MAC_DPHY_RX_REG_ST_START_ADDR_128B132B() + ((enumDpStreamNum) << 1) + 1), ~0x3F, (0x00));
#endif
    }
}

//--------------------------------------------------
// Description  : DP Port Dx Mapping to Port Num
// Input Value  : Dx
// Output Value : Logical Port 8 or Logical Port 9
//--------------------------------------------------
EnumDpMstPort ScalerDpMstRxDxPortNumMapping(EnumInputPort enumInputPort)
{
    EnumDpMstPort enumDpMstPort = _DP_PORT8;

    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:
#endif

        default:

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
            if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_PORT_NUM_SWAP() == _TRUE))
            {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
                if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
                {
                    enumDpMstPort = _DP_PORT8;
                }
                else
#endif
                {
                    enumDpMstPort = _DP_PORT9;
                }
            }
            else
#endif
            {
                enumDpMstPort = _DP_PORT8;
            }
            break;

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
        case _D9_INPUT_PORT:

            if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_PORT_NUM_SWAP() == _TRUE))
            {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
                if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
                {
                    enumDpMstPort = _DP_PORT9;
                }
                else
#endif
                {
                    enumDpMstPort = _DP_PORT8;
                }
            }
            else
            {
                enumDpMstPort = _DP_PORT9;
            }
            break;
#endif
    }

    return enumDpMstPort;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP Mst2SST mux from 8b10b or 128b132b daisy
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void ScalerDpMstRxSetTxStreamSourceMux(void)
{
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT()) == _CODING_TYPE_128B132B)
    {
        ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT7, _BIT7);
    }
    else
#endif
    {
        ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Reset DP Mst2SST from 8b10b daisy
// Input Value  : enumInputPort
// Output Value : void
//--------------------------------------------------
void ScalerDpMstRxResetTxStreamSourceMux(EnumInputPort enumInputPort)
{
    if(enumInputPort == GET_DP_RX_MAIN_PORT())
    {
        ScalerSetBit(PA_00_MST2SST_RESET, ~_BIT7, 0x00);
    }
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Port Port Num Mapping to Dx
// Input Value  : Logical Port 8 or Logical Port 9
// Output Value : Dx
//--------------------------------------------------
EnumInputPort ScalerDpMstRxPortNumDxMapping(EnumDpMstPort enumDpMstPort)
{
    EnumInputPort enumInputPort = _NO_INPUT_PORT;

    switch(enumDpMstPort)
    {
        case _DP_PORT8:

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_PORT_NUM_SWAP() == _TRUE))
            {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
                if(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
                {
                    enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();
                }
                else
#endif
                {
                    enumInputPort = _D9_INPUT_PORT;
                }
            }
            else
#endif
            {
                enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();
            }
            break;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _DP_PORT9:

            if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_PORT_NUM_SWAP() == _TRUE))
            {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
                if(GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT() == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
                {
                    enumInputPort = _D9_INPUT_PORT;
                }
                else
#endif
                {
                    enumInputPort = GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT();
                }
            }
            else
            {
                enumInputPort = _D9_INPUT_PORT;
            }
            break;
#endif

        default:
            break;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : DP Input Port Judge
// Input Value  : Logical Port 8 or Logical Port 9 ; D0/D1/D2
// Output Value : D0/D1/D2/D9
//--------------------------------------------------
EnumInputPort ScalerDpMstRxInputPortJudge(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort)
{
    EnumInputPort enumInputPortTemp = _NO_INPUT_PORT;

    switch(enumDpMstPort)
    {
        case _DP_PORT8:

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_PORT_NUM_SWAP() == _TRUE))
            {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
                if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
                {
                    enumInputPortTemp = enumInputPort;
                }
                else
#endif
                {
                    enumInputPortTemp = _D9_INPUT_PORT;
                }
            }
            else
#endif
            {
                enumInputPortTemp = enumInputPort;
            }
            break;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _DP_PORT9:

            if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_PORT_NUM_SWAP() == _TRUE))
            {
#if(_DP_TX_LOOP_BACK_DPRX_SUPPORT == _ON)
                if(enumInputPort == _DP_TX_LOOP_BACK_DPRX_INPUT_PORT)
                {
                    enumInputPortTemp = _D9_INPUT_PORT;
                }
                else
#endif
                {
                    enumInputPortTemp = enumInputPort;
                }
            }
            else
            {
                enumInputPortTemp = _D9_INPUT_PORT;
            }
            break;
#endif

        default:
            break;
    }

    return enumInputPortTemp;
}
#endif // End of #if(_DP_MST_SUPPORT == _ON)
#endif // End of #if((_DP_SUPPORT == _ON) && ((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)))

