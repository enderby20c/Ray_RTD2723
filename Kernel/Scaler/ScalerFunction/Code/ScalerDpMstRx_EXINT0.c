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
// ID Code      : ScalerDpMstRx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPRXMST_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpMstRx/ScalerDpMstRx.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Rx Mst reset stream
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxResetStream_EXINT0(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    // Reset Stream ID Mapping Table
    ScalerDpMacDphyRxResetStreamToIDMapping_EXINT0(enumInputPort);

    // Reset Stream Allocate Info
    ScalerDpMacDphyRxResetStreamAllocateInfo_EXINT0(enumInputPort);

    // Clear Payload ID Table
    CLR_DP_AUX_RX_REG_CLEAR_PAYLOAD_ID_TABLE_EXINT();

    // Reset Source Mux Backup
    ScalerDpMacDphyRxResetSourceMuxBackup_EXINT0(enumInputPort);

    // Reset Source Mux Reg
    ScalerDpMacDphyRxResetSourceMuxReg_EXINT0(enumInputPort);

    // Reset Stream Start End Position, Stream Enable Backup
    ScalerDpMacDphyRxResetStreamStatusBackup_EXINT0(enumInputPort);
    ScalerDpMacDphyRxResetStreamStartBackup_EXINT0(enumInputPort);
    ScalerDpMacDphyRxResetStreamEndBackup_EXINT0(enumInputPort);

    // Reset Stream Start End Position, Stream Enable
    ScalerDpMacDphyRxResetStreamPositionReg_EXINT0(enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
    if(enumInputPort == GET_DP_RX_MAIN_PORT())
    {
        // Reset Stream ID Mapping Table
        ScalerDpMacTxResetStreamToIdMapping_EXINT0();

        // Reset All Daisy Chain Start End Position, Stream Enable
        ScalerDpMstTxResetDaisyStreamPositionReg_EXINT0();

        // Reset All Daisy Chain Stream Source Mux Backup
        ScalerDpMstTxResetDaisySourceMuxBackup_EXINT0();

        // Reset All Daisy Chain Stream Source Mux Reg
        ScalerDpMstTxResetDaisySourceMuxReg_EXINT0();

        ScalerDpMacTxSetStreamSource_EXINT0(_DP_TX_SOURCE_NONE);

        CLR_DP_MAC_MST2SST_ENABLE();
    }
#endif
}

//--------------------------------------------------
// Description  : Rx MSG INT Handle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxIntHandle_EXINT0(EnumInputPort enumInputPort)
{
    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

    // Write 002003h Bit4 into INT0 (Down Reply Ready Bit)
    if((GET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ() == _ENABLE) &&
       (GET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ_FLAG() == _TRUE))
    {
        // Disable Down Reply Ready Bit IRQ
        ScalerDpMstRxSetMsgReadyIrqEnable_EXINT0(enumInputPort, _DP_DOWN_REPLY_MSG, _DISABLE);

        // Clear Flag
        CLR_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ_FLAG();

        // Set MSG Timer Flag
        SET_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT();
        ScalerTimerCancelTimerEvent_EXINT0(ScalerDpMstRxGetTimerEvent_EXINT0(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

        // Last Sideband MSG Have Been Read
#if(_DP_MST_RX_DOWN_REPLY_MANUAL_MODE_SUPPORT == _OFF)
        if(GET_DP_MST_RX_REG_UPSTREAM_LAST_SIDEBAND_IS_READ() == _TRUE)
        {
            // Message Upstream Disable
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY_EXINT();

            // Free Reply Buffer
            SET_DP_MST_RX_REPLY_BUF_FREE();
        }
        else
        {
            // HPD Event
            SET_DP_MST_RX_DOWN_REPLY_SET_HPD();
        }
#else
        // Check Down Reply MSG Fragment Has Been Read
        if(GET_DP_MST_RX_REG_DOWN_REPLY_MSG_IS_READ_EXINT() == _TRUE)
        {
            CLR_DP_MST_RX_REG_DOWN_REPLY_MSG_IS_READ_EXINT();

            if(GET_DP_MST_RX_DOWN_REPLY_MSG_COUNT() == 0)
            {
                // Message Upstream Disable
                CLR_DP_MST_RX_REG_UPSTREAM_REPLY_EXINT();

                // Free Reply Buffer
                SET_DP_MST_RX_REPLY_BUF_FREE();
            }
            else
            {
                // Disable Upstream
                CLR_DP_MST_RX_REG_UPSTREAM_REPLY_EXINT();

                if(GET_DP_MST_RX_DOWN_REPLY_MSG_COUNT() == 1)
                {
                    // Set Manual Mode Body Length
                    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH());

                    SET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH(0);

                    // Clear Start Bit
                    CLR_DP_MST_RX_REG_UPSTREAM_START_BIT();

                    // Set End Bit
                    SET_DP_MST_RX_REG_UPSTREAM_END_BIT();
                }
                else if(GET_DP_MST_RX_DOWN_REPLY_MSG_COUNT() > 1)
                {
                    // Set Manual Mode Body Length
                    SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX());

                    SET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH(GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH() - GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX());

                    // Clear Start Bit
                    CLR_DP_MST_RX_REG_UPSTREAM_START_BIT();

                    // Clear End Bit
                    CLR_DP_MST_RX_REG_UPSTREAM_END_BIT();
                }

                SET_DP_MST_RX_DOWN_REPLY_MSG_COUNT(GET_DP_MST_RX_DOWN_REPLY_MSG_COUNT() - 1);

                // HPD Event
                SET_DP_MST_RX_DOWN_REPLY_SET_HPD();
            }
        }
        else
        {
            // Enable Upstream
            SET_DP_MST_RX_REG_UPSTREAM_REPLY();

            // HPD Event
            SET_DP_MST_RX_DOWN_REPLY_SET_HPD();
        }
#endif

        if(GET_DP_MST_RX_DOWN_REPLY_SET_HPD() == _TRUE)
        {
            CLR_DP_MST_RX_DOWN_REPLY_SET_HPD();

            CLR_DP_MST_RX_DOWN_REPLY_RETRY_NUM();

            // Enable Upstream (HW starts to load data to buffer after 3T delay time)
            SET_DP_MST_RX_REG_UPSTREAM_REPLY();

            // Set MSG Timeout Timer Event Before 2003h IRQ Setting
            CLR_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT();
            ScalerDpMstRxReactiveTimerEvent(_DP_MST_RX_DOWN_REPLY_MSG_TIME_OUT, ScalerDpMstRxGetTimerEvent_EXINT0(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

            // Enable DOWN_REP_MSG_RDY IRQ
            ScalerDpMstRxSetMsgReadyIrqEnable_EXINT0(enumInputPort, _DP_DOWN_REPLY_MSG, _ENABLE);

            // Set Down Reply Message Ready Bit of DPCD Table
            ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue_EXINT0(enumInputPort, 0x00, 0x20, 0x03, ~_BIT4, _BIT4);

            // Gen HPD With Duration 1 ms
            ScalerDpAuxRxHpdIrqAssert_EXINT0(enumInputPort);
        }
    }

    // Write 002003h Bit5 into INT0 (Up Request Ready Bit)
    if((GET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ() == _ENABLE) &&
       (GET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ_FLAG() == _TRUE))
    {
        // Disable UP_REQ_MSG_RDY Bit INT
        ScalerDpMstRxSetMsgReadyIrqEnable_EXINT0(enumInputPort, _DP_UP_REQUEST_MSG, _DISABLE);

        // Clear Flag
        CLR_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ_FLAG();

        // Set MSG Timer Flag
        SET_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT();
        ScalerTimerCancelTimerEvent_EXINT0(ScalerDpMstRxGetTimerEvent_EXINT0(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

        // Message Upstream Disable
        CLR_DP_MST_RX_REG_UPSTREAM_REPLY_EXINT();

        // Free Reply Buffer
        SET_DP_MST_RX_REPLY_BUF_FREE();

        if((GET_DP_MST_RX_REG_UPSTREAM_LAST_SIDEBAND_IS_READ() == _TRUE) && (GET_DP_MST_RX_UP_REQUEST_PROCESSING() == _TRUE))
        {
            // Set Up Request Bypass Done Flag
            SET_DP_MST_RX_UP_REQUEST_BYPASS_DONE();
        }

        // Disable 0x1000 Write INT
        CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE();
    }

    // Write 0x1000 into INT0 (Down request MSG is written)
    if((GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE() == _ENABLE) &&
       (GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE))
    {
        // Disable 0x1000 Write INT
        CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE();

#if(_DP_AUX_RX_DPCD_WILDCARD_02003_SUPPORT == _ON)
        // Check up request is ready and 2003h hasn't been read, then cancel the up request for now (It'll be retried after 2s)
        if((GET_DP_MST_RX_REG_UPSTREAM_REPLY_UP_REQUEST_ADDRESS_EXINT() == _TRUE) &&
           (ScalerDpAuxRxDpcdWildCardIntCheck_EXINT0(enumInputPort, _AUX_RX_DPCD_WILDCARD_2003) == _FALSE))
        {
            // Set MSG Timer Flag
            SET_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT();
            ScalerTimerCancelTimerEvent_EXINT0(ScalerDpMstRxGetTimerEvent_EXINT0(enumInputPort, _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT));

            // Disable UP_REQ_MSG_RDY INT
            ScalerDpMstRxSetMsgReadyIrqEnable_EXINT0(enumInputPort, _DP_UP_REQUEST_MSG, _DISABLE);

            // Clear UP_REQ_MSG_RDY Bit of DPCD Table
            ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue_EXINT0(enumInputPort, 0x00, 0x20, 0x03, ~_BIT5, 0x00);

            // Clear Buffer
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY_BUF();

            // Message Upstream Disable
            CLR_DP_MST_RX_REG_UPSTREAM_REPLY_EXINT();

            // Free Reply Pool
            SET_DP_MST_RX_REPLY_BUF_FREE();
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Get MST timerevent
// Input Value  : enumInputPort, enumEventType
// Output Value : None
//--------------------------------------------------
EnumScalerTimerEventID ScalerDpMstRxGetTimerEvent_EXINT0(EnumInputPort enumInputPort, EnumDpMstRxTimerEventType enumEventType)
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
// Description  : Set DP Aux Msg Irq Enable
// Input Value  : EnumInputPort, Enable
// Output Value : None
//--------------------------------------------------
void ScalerDpMstRxSetMsgReadyIrqEnable_EXINT0(EnumInputPort enumInputPort, EnumDpMessageType enumDpMessageType, bit bEnable)
{
    enumInputPort = enumInputPort;
    enumDpMessageType = enumDpMessageType;

    ScalerDpRxSetBaseInputPort_EXINT0(enumInputPort);

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
#endif // End for #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

