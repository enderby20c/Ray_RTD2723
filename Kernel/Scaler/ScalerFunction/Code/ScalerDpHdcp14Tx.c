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
// ID Code      : ScalerDpHdcp14Tx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp14Tx/ScalerDpHdcp14Tx.h"

#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDPTxHDCPAuthInfo g_stDpHdcp14TxAuthInfo;
BYTE g_ucDpHdcp14TxECFChange;
WORD g_usDpHdcp14TxR0RetryCounter;
BYTE g_ucDpHdcp14TxLoadKey;

BYTE g_pucDpHdcp14TxKsvBackup[5];


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Dp Tx HDCP Auth
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp14TxHandler(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_EVENT();

    if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT)
    {
        CLR_DP_TX_HDCP_AUTH_START();

        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS)
    {
        SET_DP_TX_HDCP_AUTH_START();

        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION)
    {
        CLR_DP_TX_HDCP_AUTH_START();

        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(GET_DP_TX_IRQ_HDCP_TYPE(_DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL) == _DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL)
    {
        CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL);

        if(ScalerDpMacTxHdcpGetEncryptStatus() == _TRUE)
        {
            ScalerDpHdcp14TxEncryptSignalProc(_DISABLE);

            SET_DP_TX_HDCP_AUTH_START();

            ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
        }
    }
    else if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON)
    {
        if(GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE)
        {
            ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
        }
    }
    else if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_ECF_CHANGE)
    {
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
        {
            SET_DP_TX_HDCP_ECF_CHANGE();
        }
    }

    if((GET_DP_TX_HDCP_AUTH_STATE() >= _DP_TX_HDCP_STATE_AUTH_2) && (GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE))
    {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
        if((ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE) &&
           (GET_DP_HDCP2_TX_STOP_CONTENT_STREAM() == _FALSE))
#else
        if(ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE)
#endif
        {
            if(ScalerDpMacTxHdcpGetEncryptStatus() == _FALSE)
            {
#if(_DP_MST_SUPPORT == _ON)
                ScalerDpHdcp14TxSetECFProc();
#endif
                ScalerDpHdcp14TxEncryptSignalProc(_ENABLE);
            }
        }
        else
        {
            if(ScalerDpMacTxHdcpGetEncryptStatus() == _TRUE)
            {
                ScalerDpHdcp14TxEncryptSignalProc(_DISABLE);
            }
        }
    }

    switch(GET_DP_TX_HDCP_AUTH_STATE())
    {
        case _DP_TX_HDCP_STATE_IDLE:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();
                CLR_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT();
                CLR_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();
                CLR_DP_TX_HDCP_AUTH_HOLD();
                CLR_DP_TX_HDCP_ECF_CHANGE();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_TO_READ_R0);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);

                ScalerDpHdcp14TxEncryptSignalProc(_DISABLE);

                ScalerDpHdcp14TxCheckDownstreamCapability();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                CLR_DP_HDCP2_TX_STOP_CONTENT_STREAM();
#endif
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
            {
                // Prevent TX HDCP1.4 Key Corrupting, reloading key finished
                if(GET_DP_TX_HDCP_RELOAD_KEY_EN() == _FALSE)
                {
                    if((GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_ON) && (GET_DP_TX_HDCP_AUTH_START() == _TRUE))
                    {
                        CLR_DP_TX_HDCP_AUTH_START();
                        CLR_DP_TX_IRQ_HDCP_TYPE();

                        ScalerDpHdcp14TxResetInfo();

                        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_AUTH_1);
                    }
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_1:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                if(ScalerDpHdcp14TxAuth1Proc() == _SUCCESS)
                {
                    ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0);
                }
                else
                {
                    ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                // Wait 100ms to read R0'
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_TO_READ_R0);

                SET_DP_TX_HDCP_AUTH_HOLD();
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_HOLD();
                CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_R0_AVAILABLE);

                if(ScalerDpHdcp14TxAuth1CompareR0() == _SUCCESS)
                {
                    CLR_DP_TX_HDCP_R0_RETRY_COUNTER();

                    if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
                    {
                        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_AUTH_2);
                    }
                    else
                    {
                        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_AUTH_PASS);

                        SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS);
                    }
                }
                else
                {
                    // Retry R0 10 times failed, reloading TX HDCP1.4 key
                    if(GET_DP_TX_HDCP_R0_RETRY_COUNTER() > 10)
                    {
                        CLR_DP_TX_HDCP_R0_RETRY_COUNTER();
                        SET_DP_TX_HDCP_RELOAD_KEY_EN();
                    }
                    else
                    {
                        ADD_DP_TX_HDCP_R0_RETRY_COUNTER();
                    }

                    SET_DP_TX_HDCP_AUTH_START();

                    ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_2:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);
                ScalerTimerActiveTimerEvent(SEC(0.25), _SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY() == _TRUE)
            {
                CLR_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();

                if(ScalerDpHdcp14TxPollingCpIrqType() == _DP_TX_IRQ_HDCP_V_READY)
                {
                    SET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
                }
            }

            if((GET_DP_TX_IRQ_HDCP_TYPE(_DP_TX_IRQ_HDCP_V_READY) == _DP_TX_IRQ_HDCP_V_READY) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT() == _TRUE))
            {
                CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_V_READY);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);

                if(ScalerDpHdcp14TxCheckBinfo() == _TRUE)
                {
                    if(ScalerDpHdcp14TxAuth2Proc() == _SUCCESS)
                    {
                        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_AUTH_PASS);

                        SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS);
                    }
                    else
                    {
                        ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                    }
                }
                else
                {
                    ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);

                    SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX);
                }
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT() == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);

                SET_DP_TX_HDCP_AUTH_START();

                ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_PASS:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();
            }

#if(_DP_MST_SUPPORT == _ON)
            if(GET_DP_TX_HDCP_ECF_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_ECF_CHANGE();

                if(ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE)
                {
                    ScalerDpHdcp14TxSetECFProc();
                }
            }
#endif
            if(GET_DP_TX_HDCP_AUTH_START() == _TRUE)
            {
                ScalerDpHdcp14TxChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Downstream HDCP Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp14TxCheckDownstreamCapability(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
    CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();

    if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG)
    {
        // Read HDCP capability from DPCD table of DownStream
        if(ScalerDpAuxTxNativeRead(0x06, 0x80, 0x28, 1, pData) == _TRUE)
        {
            // Check if Rx HDCP is capable
            if((pData[0] & _BIT0) == _BIT0)
            {
                SET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
            }

            // Check if Rx is repeater
            if((pData[0] & _BIT1) == _BIT1)
            {
                SET_DP_TX_HDCP_DOWNSTREAM_REPEATER();

                ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, _BIT4);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpHdcp14TxAuth1Proc(void)
{
    // Switch HDCP Cipher Module to HDCP 1.4
    ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT0, 0x00);

    // Enable DP Tx HDCP Tx function .
    ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT0, _BIT0);

    // Step1: Read Bcap from DPCD
    ScalerDpAuxTxNativeRead(0x06, 0x80, 0x28, 1, pData);

    // Check if Downstream's HDCP is capable
    if((pData[0] & _BIT0) == _BIT0)
    {
        SET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
    }
    else
    {
        CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();

        return _FAIL;
    }

    // Check if Downstream is HDCP repeater
    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_TX_HDCP_DOWNSTREAM_REPEATER();

        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, _BIT4);
    }
    else
    {
        CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();

        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, 0x00);
    }

    // Step2: Check Bksv
    if(ScalerDpHdcp14TxAuth1CheckBksv() == _FAIL)
    {
        SET_DP_TX_HDCP_AUTH_START();

        return _FAIL;
    }

    // Step3: Generate An
    ScalerDpHdcp14TxAuth1GenAn();

    // For HDCP14 CTS Unigraf DPR-100
    ScalerTimerDelayXms(5);

    // Step4: Write Akey and write Aksv
    ScalerDpHdcp14TxAuth1WriteAnAkey();

    // Step5: Geneate Km,Ks,M0 and R0
    if(ScalerDpHdcp14TxAuth1GenKm() == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 -Check Bksv
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpHdcp14TxAuth1CheckBksv(void)
{
    bit bResult = _FAIL;

    // Read Bksv
    ScalerDpAuxTxNativeRead(0x06, 0x80, 0x00, 5, pData);

    ScalerWrite(PBB_4F_BKSV_0, 5, pData, _AUTOINC);

    // Turn on circuit that check BKSV
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT2, _BIT2);

    if(ScalerTimerPollingFlagProc(5, PBB_56_DP_HDCP_TX, _BIT1, 1) == _SUCCESS)
    {
        bResult = (ScalerGetBit(PBB_56_DP_HDCP_TX, _BIT0) == 0x00) ? _SUCCESS : _FAIL;
    }
    else
    {
        bResult = _FAIL;
    }

    // Turn Off circuit that check BKSV
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT2, 0x00);

    return bResult;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1- Gen An
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp14TxAuth1GenAn(void)
{
    // Write an_gen_start = 1 , and An gen start to run
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT3, _BIT3);

    // Write reg_freerun_init an initial value
    ScalerSetByte(PBB_58_DP_HDCP_AN_SEED, GET_MCU_TIMER_RANDOM_BYTE());

    // Write reg_freerun_init_en 0 to 1 to load init value
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Write an_gen_start = 0 , An gen stop
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT3, 0x00);

    // Disable load init value
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT3, 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1- Gen Aksv
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp14TxAuth1WriteAnAkey(void)
{
    BYTE ucI = 0;
    BYTE pucData[8] = {0};

    for(ucI = 0; ucI < 8; ucI++)
    {
        pucData[ucI] = ScalerGetByte(PBB_3B_AN_BYTE_0 - ucI);
    }

    // Write An to Downstream DPCD
    ScalerDpAuxTxNativeWrite(0x06, 0x80, 0x0C, 8, pucData);

    // Write Aksv to Downstream DPCD
    ScalerDpAuxTxNativeWrite(0x06, 0x80, 0x07, 5, g_pucSyncHdcpAksvBackup);
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 -Gen Km
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpHdcp14TxAuth1GenKm(void)
{
    bit bResult = _FAIL;

    // Turn on computation
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT1, _BIT1);

    // Km = Akey over Bksv
    // (Ks,M0,R0) = Km,Repeater||An

    if(ScalerTimerPollingFlagProc(5, PBB_31_DPTX_HDCP_CTRL2, _BIT0, 1) == _SUCCESS)
    {
        bResult = _SUCCESS;
    }

    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT1, 0x00);

    return bResult;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 Compare R0 and R0'
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpHdcp14TxAuth1CompareR0(void)
{
    BYTE ucCompareCounter = 0;

    do
    {
        // Read R0'
        ScalerDpAuxTxNativeRead(0x06, 0x80, 0x05, 2, pData);

        // Compare R0 and R0'
        if((ScalerGetByte(PBB_4C_R0_BYTE_LSB) == pData[0]) &&
           (ScalerGetByte(PBB_4B_R0_BYTE_MSB) == pData[1]))
        {
            return _SUCCESS;
        }

        ScalerTimerDelayXms(2);

        ucCompareCounter++;
    }
    while(ucCompareCounter < 3);

    return _FAIL;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpHdcp14TxAuth2Proc(void)
{
    BYTE ucCompareCounter = 0;

    do
    {
        // Load SHA-1 Input Data
        ScalerDpHdcp14TxAuth2WriteShaInput();

        // Compare V and V'
        if(ScalerDpHdcp14TxAuth2CompareV() == _SUCCESS)
        {
            return _SUCCESS;
        }

        ucCompareCounter++;
    }
    while(ucCompareCounter < 3);

    SET_DP_TX_HDCP_AUTH_START();

    return _FAIL;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2-Wrtie Data to SHA input
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp14TxAuth2WriteShaInput(void)
{
    WORD usKsvFifoLength = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() * 5;
    WORD usShaInputBitNumbers = 0;
    WORD usKsvLengthTemp = 0;
    WORD usKsvLengthRemain = 0;
    BYTE ucKsvLengthReadOnce = 0;
    BYTE pucKsvData[16];

    usKsvLengthRemain = usKsvFifoLength;

    // Read KSV FIFO List from Downstream Device
    do
    {
        ucKsvLengthReadOnce = ((usKsvLengthRemain > 15) ? 15 : usKsvLengthRemain);

        ScalerDpAuxTxNativeRead(0x06, 0x80, 0x2C, ucKsvLengthReadOnce, pucKsvData);

        if(GET_DP_TX_HDCP_KSV_FIFO_MAX() > usShaInputBitNumbers)
        {
            memcpy(&g_pucDpMacTxHdcpKsvFifo[usShaInputBitNumbers], pucKsvData, ucKsvLengthReadOnce);
        }
        else
        {
            DebugMessageDpTx("Dp Tx HDCP14 DFP Device is Exceed!!!", 0);
        }

        usShaInputBitNumbers += ucKsvLengthReadOnce;

        usKsvLengthRemain = usKsvLengthRemain - ucKsvLengthReadOnce;
    }
    while(usKsvLengthRemain > 0);

    // Total bit numbers of SHA-1 input = the length of KSV FIFO + the length of B_info + the length of M0'
    usShaInputBitNumbers = (usKsvFifoLength + 2 + 8) * 8;

    // Reset SHA Block counter
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT1 | _BIT0), _BIT1);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT1 | _BIT0), 0x00);

    // Initialize The Index of KSV FIFO List
    usKsvLengthTemp = 0;

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 2]);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 3]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        ScalerMcuDelayXus(1);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }
    while((usKsvFifoLength - usKsvLengthTemp) >= 4);

    // Write the remaining KSV, B info and M0' into SHA-1 Transform Input
    switch(usKsvFifoLength - usKsvLengthTemp)
    {
        case 1:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP14_M0_0());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP14_M0_1());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP14_M0_2());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP14_M0_3());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP14_M0_4());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP14_M0_5());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP14_M0_6());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP14_M0_7());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x80);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 2:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP14_M0_0());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP14_M0_1());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP14_M0_2());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP14_M0_3());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP14_M0_4());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP14_M0_5());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP14_M0_6());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP14_M0_7());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x80);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 3:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, g_pucDpMacTxHdcpKsvFifo[usKsvLengthTemp + 2]);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP14_M0_0());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP14_M0_1());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP14_M0_2());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP14_M0_3());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP14_M0_4());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP14_M0_5());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP14_M0_6());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP14_M0_7());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x80);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        default:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP14_M0_0());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP14_M0_1());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP14_M0_2());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP14_M0_3());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP14_M0_4());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP14_M0_5());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP14_M0_6());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP14_M0_7());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x80);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;
    }

    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 60)
    {
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        ScalerMcuDelayXus(1);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }

    // Write 0x00 into the remaining SHA-1 Transform Input space
    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) <= 56)
    {
        while((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) < 56)
        {
            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            ScalerMcuDelayXus(1);

            usKsvLengthTemp += 4;
        }

        // The input length is equal to 2^64
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        ScalerMcuDelayXus(1);

        // Write the valid bit numbers into SHA-1 Transform Input
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, HIBYTE(usShaInputBitNumbers));
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, LOBYTE(usShaInputBitNumbers));

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 8;

        ScalerDpHdcp14TxAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
    }
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2 -SHA circuit Run
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp14TxAuth2ShaRun(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT3 | _BIT0), ((bIsFirst == _TRUE) ? _BIT3 : 0x00));

    // Run SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT2 | _BIT0), _BIT2);

    ScalerTimerPollingFlagProc(5, PBB_5B_DP_HDCP_TX_SHA_CTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT3 | _BIT2 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Check Binfo of Downstream port
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpHdcp14TxCheckBinfo(void)
{
    // Read Binfo(Device Count and Depth)
    ScalerDpAuxTxNativeRead(0x06, 0x80, 0x2A, 2, pData);

    // Record Binfo of Downstream
    SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE(pData[0]);
    SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH(pData[1]);

    // Check if MAX_DEVS_EXCEEDED or MAX_CASCADE_EXCEEDED is 1 and then abort authentication
    if(((pData[0] & _BIT7) == _BIT7) || ((pData[1] & _BIT3) == _BIT3))
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2 -Compare V and V'
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpHdcp14TxAuth2CompareV(void)
{
    BYTE ucSha1VHx = 0;
    BYTE ucIndex = 4;
    bit bCompareResult = _SUCCESS;

    for(ucSha1VHx = 0; ucSha1VHx < 5; ucSha1VHx++)
    {
        ScalerDpAuxTxNativeRead(0x06, 0x80, (0x14 + (ucSha1VHx * 4)), 4, pData);

        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT0), ((ucIndex - ucSha1VHx) << 5));

        // Compare V with V'
        if((ScalerGetByte(PBB_63_DP_HDCP_TX_SHA_OUT_0) != pData[0]) ||
           (ScalerGetByte(PBB_62_DP_HDCP_TX_SHA_OUT_1) != pData[1]) ||
           (ScalerGetByte(PBB_61_DP_HDCP_TX_SHA_OUT_2) != pData[2]) ||
           (ScalerGetByte(PBB_60_DP_HDCP_TX_SHA_OUT_3) != pData[3]))
        {
            bCompareResult = _FAIL;
        }

        g_pucDpMacTxHdcpDownStreamV[(ucSha1VHx * 4)] = pData[0];
        g_pucDpMacTxHdcpDownStreamV[(ucSha1VHx * 4) + 1] = pData[1];
        g_pucDpMacTxHdcpDownStreamV[(ucSha1VHx * 4) + 2] = pData[2];
        g_pucDpMacTxHdcpDownStreamV[(ucSha1VHx * 4) + 3] = pData[3];
    }

    if(bCompareResult == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Change HDCP Auth State
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14TxChangeAuthState(EnumDPTxHDCPAuthState enumHDCPAuthState)
{
    SET_DP_TX_HDCP_AUTH_STATE(enumHDCPAuthState);
    SET_DP_TX_HDCP_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Change HDCP Auth State to Compare R0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14TxTimeoutToReadR0Event(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT();
}

//--------------------------------------------------
// Description  : Waiting for V ready of downstream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14TxTimeoutForVReadyEvent(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT();
}

//--------------------------------------------------
// Description  : Polling V ready of downstream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14TxPollingVReadyEvent(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
}

//--------------------------------------------------
// Description  : Polling IRQ status of Downstream
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxTRQEventHDCPType ScalerDpHdcp14TxPollingCpIrqType(void)
{
    ScalerDpAuxTxNativeRead(0x06, 0x80, 0x29, 1, pData);

    if((pData[0] & _BIT3) == _BIT3)
    {
        return _DP_TX_IRQ_HDCP_REAUTH_REQUEST;
    }
    else if((pData[0] & _BIT2) == _BIT2)
    {
        return _DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL;
    }
    else if((pData[0] & _BIT1) == _BIT1)
    {
        return _DP_TX_IRQ_HDCP_R0_AVAILABLE;
    }
    else if((pData[0] & _BIT0) == _BIT0)
    {
        return _DP_TX_IRQ_HDCP_V_READY;
    }

    return _DP_TX_IRQ_HDCP_NONE;
}

//--------------------------------------------------
// Description  : Enable HDCP TX Encryption
// Input Value  : _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp14TxEncryptSignalProc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // HDCP encryption enable.
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable HDCP function, Encryption and Reset Repeater Flag
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, 0x00);

#if(_DP_MST_SUPPORT == _ON)
        // Disable MST ST3/ST4/ST5 Stream Encryption
        ScalerSetBit(PBB_6C_DP_STREAM_1_PBN, ~_BIT6, 0x00);
        ScalerSetBit(PBB_6D_DP_STREAM_2_PBN, ~_BIT6, 0x00);
        ScalerSetBit(PBB_6E_DP_STREAM_3_PBN, ~_BIT6, 0x00);

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_4_STREAM)
        // Disable MST ST6 Stream Encryption
        ScalerSetBit(PBB_6F_DP_STREAM_4_PBN, ~_BIT6, 0x00);

#elif(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
        // Disable MST ST6/ST7/ST8 Stream Encryption
        ScalerSetBit(PBB_6F_DP_STREAM_4_PBN, ~_BIT6, 0x00);
        ScalerSetBit(PBB_96_DP_STREAM_5_PBN, ~_BIT6, 0x00);
        ScalerSetBit(PBB_97_DP_STREAM_6_PBN, ~_BIT6, 0x00);
#endif

        // Output MST type
        if(GET_DP_MST_TX_ENABLE() == _TRUE)
        {
            // Set ECF by FW
            ScalerSetByte(PBB_64_HDCP_ECF_BYTE0, 0x00);
            ScalerSetByte(PBB_65_HDCP_ECF_BYTE1, 0x00);
            ScalerSetByte(PBB_66_HDCP_ECF_BYTE2, 0x00);
            ScalerSetByte(PBB_67_HDCP_ECF_BYTE3, 0x00);
            ScalerSetByte(PBB_68_HDCP_ECF_BYTE4, 0x00);
            ScalerSetByte(PBB_69_HDCP_ECF_BYTE5, 0x00);
            ScalerSetByte(PBB_6A_HDCP_ECF_BYTE6, 0x00);
            ScalerSetByte(PBB_6B_HDCP_ECF_BYTE7, 0x00);

            // Double Buffer by ACT
            SET_DP_MAC_TX_REG_SEND_ACT_ENABLE();
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Reset HDCP TX Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14TxResetInfo(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE();
    CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH();

    memset(g_pucDpMacTxHdcpKsvFifo, 0, sizeof(g_pucDpMacTxHdcpKsvFifo));
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDCP1.4 TX ECF Encryption
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14TxSetECFProc(void)
{
    // Output MST type
    if(GET_DP_MST_TX_ENABLE() == _TRUE)
    {
        BYTE ucDaisyStreamCnt = 0;
        BYTE ucLoopIndex = 0;
        EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort = GET_DP_RX_HDCP_UPSTREAM_PORT();

        // Set ECF by HW
        ScalerSetBit(PBB_64_HDCP_ECF_BYTE0, ~_BIT7, _BIT7);

        for(ucDaisyStreamCnt = _DP_ST_SOURCE_DAISY_START; ucDaisyStreamCnt <= _DP_ST_SOURCE_DAISY_END; ucDaisyStreamCnt++)
        {
            BYTE ucShiftCnt = 0;
            BYTE ucPresentRxStartPosition = (ScalerGetByte(ScalerDpMacDphyRxStreamStartAddress(enumDpHdcpUpstreamPort, ScalerDpMacTxGetDaisySourceMuxBackup(ucDaisyStreamCnt))) & 0x3F);
            BYTE ucPresentTxStartPosition = GET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(ucDaisyStreamCnt);

            // Set Length of STx Stream to Be Ready For Encryption Except ST None
            if(ucPresentTxStartPosition != 0x00)
            {
                // Mapping STx Stream to ECF Stream
                for(ucLoopIndex = _DP_ST_SOURCE_DAISY_START; ucLoopIndex <= _DP_ST_SOURCE_DAISY_END; ucLoopIndex++)
                {
                    BYTE ucScanStartPosition = GET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(ucLoopIndex);

                    if((ucPresentTxStartPosition > ucScanStartPosition) &&
                       (ScalerDpMacTxGetDaisySourceMuxBackup(ucLoopIndex) != _DP_ST_NONE))
                    {
                        ucShiftCnt ++;
                    }
                }

                ScalerSetBit(PBB_6C_DP_STREAM_1_PBN + ucShiftCnt, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(ucDaisyStreamCnt));
            }

            if(ScalerDpMacDphyRxHdcpTimeSlotEncStatus(enumDpHdcpUpstreamPort, ucPresentRxStartPosition) == _TRUE)
            {
                // Enable MST STX Stream Encryption
                if(ScalerGetBit((PBB_6C_DP_STREAM_1_PBN + ucShiftCnt), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00)
                {
                    ScalerSetBit((PBB_6C_DP_STREAM_1_PBN + ucShiftCnt), ~_BIT6, _BIT6);
                }
            }
        }

        // Double Buffer by ACT
        SET_DP_MAC_TX_REG_SEND_ACT_ENABLE();

        // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
        ScalerTimerDelayXms(2);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14TxPowerOnInitial(void)
{
    CLR_DP_TX_HDCP_RELOAD_KEY_EN();
    CLR_DP_TX_HDCP_R0_RETRY_COUNTER();
}

//--------------------------------------------------
// Description  : Reset HDCP TX KSV Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14TxResetKsvBackup(void)
{
    memset(g_pucDpHdcp14TxKsvBackup, 0, sizeof(g_pucDpHdcp14TxKsvBackup));
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Check DownStream Device is Same or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp14TxDownstreamBksvChange(void)
{
    // Read Bksv
    ScalerDpAuxTxNativeRead(0x06, 0x80, 0x00, 5, pData);

    // Compare Bksv
    if((g_pucDpHdcp14TxKsvBackup[0] != pData[0]) ||
       (g_pucDpHdcp14TxKsvBackup[1] != pData[1]) ||
       (g_pucDpHdcp14TxKsvBackup[2] != pData[2]) ||
       (g_pucDpHdcp14TxKsvBackup[3] != pData[3]) ||
       (g_pucDpHdcp14TxKsvBackup[4] != pData[4]))
    {
        return _TRUE;
    }

    return _FALSE;
}

#endif // End of #if(_DP_TX_SUPPORT == _ON)
