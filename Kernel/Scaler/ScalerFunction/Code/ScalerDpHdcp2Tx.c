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
// ID Code      : ScalerDpHdcp2Tx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp2Tx/ScalerDpHdcp2Tx.h"

#if((_DP_HDCP2_RX_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructHdcp2TxAuthInfo g_stDpHdcp2TxAuthInfo;
EnumHdcp2TxCpirqType g_enumDpHdcp2TxCpirqType = _HDCP_2_2_TX_CPIRQ_NONE;
DWORD g_ulDpHdcp2TxSeqNumM;
DWORD g_ulDpHdcp2TxSeqNumV;

BYTE g_pucDpHdcp2TxCaps[3];
BYTE g_pucDpHdcp2TxReceiverId[5];
BYTE g_pucDpHdcp2TxRxCaps[3];
BYTE g_pucDpHdcp2TxRrx[8];
BYTE g_pucDpHdcp2TxNpub[128];
BYTE g_pucDpHdcp2TxEpub[3];
BYTE g_pucDpHdcp2TxdKey0[16];
BYTE g_pucDpHdcp2TxdKey1[16];
BYTE g_pucDpHdcp2TxReceiverIdList[_DP_TX_HDCP2_DEVICE_COUNT_MAX * 5];
BYTE g_pucDpHdcp2TxM[32];
BYTE g_pucDpHdcp2TxPairingEkhkm[16];
BYTE g_pucDpHdcp2TxPairingM[16];
BYTE g_pucDpHdcp2TxPairingKm[16];
BYTE g_pucDpHdcp2TxPairingReceiverID[5];
BYTE g_pucDpHdcp2TxH[32];
BYTE g_pucDpHdcp2TxDownStreamV[20];
BYTE g_ucDpHdcp2TxLoadKey;

#if(_DP_MST_SUPPORT == _ON)
BYTE g_pucDpHdcp2TxMstTimeSlotBackup[6];
#endif

BYTE g_pucDpHdcp2TxRtx[8];
BYTE g_pucDpHdcp2TxKm[16];
BYTE g_pucDpHdcp2TxRn[8];
BYTE g_pucDpHdcp2TxRiv[8];
BYTE g_ucDpHdcp2TxECFChange;

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tLHash[32] =
{
    0xE3, 0xB0, 0xC4, 0x42, 0x98, 0xFC, 0x1C, 0x14,
    0x9A, 0xFB, 0xF4, 0xC8, 0x99, 0x6F, 0xB9, 0x24,
    0x27, 0xAE, 0x41, 0xE4, 0x64, 0x9B, 0x93, 0x4C,
    0xA4, 0x95, 0x99, 0x1B, 0x78, 0x52, 0xB8, 0x55,
};

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process for Dp Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxHandler(void)
{
    BYTE pucTemp1[16] = {0};

    CLR_DP_HDCP2_TX_DOWNSTREAM_EVENT();

    if(ScalerSyncDpHdcp2GetUpstreamEvent() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT)
    {
        CLR_DP_HDCP2_TX_AUTH_START();

        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcp2GetUpstreamEvent() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE)
    {
        SET_DP_HDCP2_TX_AUTH_START();

        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcp2GetUpstreamEvent() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION)
    {
        CLR_DP_HDCP2_TX_AUTH_START();

        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
    }
    else if(GET_DP_HDCP2_TX_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL) == _HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL)
    {
        CLR_DP_HDCP2_TX_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL);

        if(ScalerDpMacTxHdcpGetEncryptStatus() == _TRUE)
        {
            DebugMessageHDCP2("DPTX HDCP2 - CPIRQ LVP Fail", 0);

            ScalerDpHdcp2TxEncryptSignalProc(_DISABLE);

            SET_DP_HDCP2_TX_AUTH_START();

            ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
        }
    }
    else if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON)
    {
        if(GET_DP_HDCP2_TX_AUTH_STATE() != _HDCP_2_2_TX_STATE_IDLE)
        {
            ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
        }
    }
    else if(GET_DP_HDCP2_TX_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_V_READY) == _HDCP_2_2_TX_CPIRQ_V_READY)
    {
        CLR_DP_HDCP2_TX_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_V_READY);

        if(GET_DP_HDCP2_TX_AUTH_STATE() == _HDCP_2_2_TX_STATE_AUTHEN_DONE)
        {
            ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_V_PRIME);
        }
    }
    else if(GET_DP_HDCP2_TX_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_REAUTH_REQUEST) == _HDCP_2_2_TX_CPIRQ_REAUTH_REQUEST)
    {
        CLR_DP_HDCP2_TX_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_REAUTH_REQUEST);

        ScalerDpHdcp2TxCheckCapability();

        if(GET_DP_HDCP2_TX_AUTH_STATE() != _HDCP_2_2_TX_STATE_IDLE)
        {
            DebugMessageHDCP2("DPTX Reauth Bypass", 0);

            SET_DP_HDCP2_TX_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH);
        }
    }
    else if(ScalerSyncDpHdcp2GetUpstreamEvent() == _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_ECF_CHANGE)
    {
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
        {
            SET_DP_HDCP2_TX_ECF_CHANGE();
        }
    }

    switch(GET_DP_HDCP2_TX_AUTH_STATE())
    {
        case _HDCP_2_2_TX_STATE_IDLE:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Idle", 0);

                ScalerDpHdcp2TxResetAuthInfo();

                ScalerDpHdcp2TxEncryptSignalProc_8b10b(_DISABLE);
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                ScalerDpHdcp2TxEncryptSignalProc_128b132b(_DISABLE);
#endif
                ScalerDpHdcp2TxCheckCapability();
            }

            if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) &&
               (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE) &&
               (GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_ON) &&
               (GET_DP_HDCP2_TX_AUTH_START() == _TRUE))
            {
                CLR_DP_HDCP2_TX_AUTH_START();
                CLR_DP_HDCP2_TX_IRQ_TYPE();

                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_AKE_INIT);
            }

            break;

        case _HDCP_2_2_TX_STATE_AKE_INIT:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - AKE INIT", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();
            }

            if(ScalerDpHdcp2TxAkeInitial() == _TRUE)
            {
                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_SIGNATURE);
            }
            else
            {
                SET_DP_HDCP2_TX_AUTH_START();

                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_VERIFY_SIGNATURE:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Verify S", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();

                // Set up 100ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_CERTIFICATE);

                SET_DP_HDCP2_TX_AUTH_HOLD();
            }

            if(GET_DP_HDCP2_TX_LOAD_KEY_FINISH() == _TRUE)
            {
                CLR_DP_HDCP2_TX_AUTH_HOLD();

                CLR_DP_HDCP2_TX_LOAD_KEY_FINISH();

                if(ScalerDpHdcp2TxVerifySignature() == _TRUE)
                {
                    DebugMessageHDCP2("DPTX HDCP2 - S_Verify Pass", 0);

                    // Go to No stored km or Stored km
                    if(ScalerDpHdcp2TxCheckPairingInfo() == _TRUE)
                    {
                        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_STORED_KM);
                    }
                    else
                    {
                        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_NO_STORED_KM);
                    }
                }
                else
                {
                    DebugMessageHDCP2("DPTX HDCP2 - S_Verify Fail", 0);

                    // DP HDCP2.2 CTS 3A-03(Same as 1A-08)
                    SET_DP_HDCP2_TX_AUTH_START();

                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
            }

            break;

        case _HDCP_2_2_TX_STATE_NO_STORED_KM:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - No Stored Km", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();
            }

            if(ScalerDpHdcp2TxNoStoredKmProc() == _TRUE)
            {
                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_H_PRIME);

                // Set up 1s Timer Event
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_H_PRIME);
            }
            else
            {
                SET_DP_HDCP2_TX_AUTH_START();

                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_STORED_KM:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Stored Km", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();
            }

            if(ScalerDpHdcp2TxStoredKmProc() == _TRUE)
            {
                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_H_PRIME);

                // Set up 200ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_H_PRIME);
            }
            else
            {
                SET_DP_HDCP2_TX_AUTH_START();

                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_VERIFY_H_PRIME:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - H", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();

                if(GET_DP_HDCP2_TX_PAIRING_INFO_READY() == _TRUE)
                {
                    // Compute H for Stored Km Flow
                    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2TxPairingKm);
                    ScalerDpHdcp2TxComputeH(g_pucDpHdcp2TxRtx, g_pucDpHdcp2TxRrx, pucTemp1);
                }
                else
                {
                    // Compute H for No Stored Km Flow
                    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2TxKm);
                    ScalerDpHdcp2TxComputeH(g_pucDpHdcp2TxRtx, g_pucDpHdcp2TxRrx, pucTemp1);
                }
            }

            if((GET_DP_HDCP2_TX_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE) == _HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE) ||
               (GET_DP_HDCP2_TX_H_PRIME_TIMEOUT() == _TRUE))
            {
                CLR_DP_HDCP2_TX_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE);

                if(ScalerDpHdcp2TxVerifyHprime() == _TRUE)
                {
                    if(GET_DP_HDCP2_TX_PAIRING_INFO_READY() == _TRUE)
                    {
                        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_LOCALITY_CHECK);
                    }
                    else
                    {
                        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_PAIRING);

                        // Set up 200ms Timer Event
                        ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_PAIRING_INFO);
                    }
                }
                else
                {
                    // DP HDCP2.2 CTS 3A-04(Same as 1A-10)
                    SET_DP_HDCP2_TX_AUTH_START();

                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
            }

            break;

        case _HDCP_2_2_TX_STATE_PAIRING:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Pairing", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();
            }

            if(GET_DP_HDCP2_TX_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE) == _HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE)
            {
                CLR_DP_HDCP2_TX_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE);

                if(ScalerDpHdcp2TxStorePairingInfo() == _TRUE)
                {
                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_LOCALITY_CHECK);
                }
                else
                {
                    // DP HDCP2.2 CTS 3A-05(Same as 1A-11)
                    SET_DP_HDCP2_TX_AUTH_START();

                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
            }
            else if(GET_DP_HDCP2_TX_PAIRING_INFO_TIMEOUT() == _TRUE)
            {
                // DP HDCP2.2 CTS 3A-05(Same as 1A-11)
                SET_DP_HDCP2_TX_AUTH_START();

                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_LOCALITY_CHECK:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - LC", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();
            }

            if(GET_DP_HDCP2_TX_LC_RETRY_COUNTER() < _DP_HDCP2_TX_LC_RETRY_MAX_NUMBER)
            {
                if(ScalerDpHdcp2TxLocalityCheck() == _TRUE)
                {
                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_SKE);
                }
                else
                {
                    ADD_DP_HDCP2_TX_LC_RETRY_COUNTER();
                }
            }
            else
            {
                // DP HDCP2.2 CTS 3A-06(Same as 1A-12)
                SET_DP_HDCP2_TX_AUTH_START();

                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_SKE:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - SKE", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();
            }

            if(ScalerDpHdcp2TxSessionKeyExchangeProc() == _TRUE)
            {
                if(GET_DP_HDCP2_TX_REPEATER_SUPPORTED() == _TRUE)
                {
                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_VERIFY_V_PRIME);
                }
                else
                {
                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_AUTHEN_DONE);

                    SET_DP_HDCP2_TX_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS);
                }
            }
            else
            {
                SET_DP_HDCP2_TX_AUTH_START();

                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_VERIFY_V_PRIME:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - V", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();

                ScalerTimerActiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_FOR_V_READY);
                ScalerTimerActiveTimerEvent(SEC(0.25), _SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);
            }

            if(GET_DP_HDCP2_TX_POLLING_V_READY() == _TRUE)
            {
                CLR_DP_HDCP2_TX_POLLING_V_READY();
                CLR_DP_HDCP2_TX_V_READY_BIT();

                if(ScalerDpHdcp2TxPollingCpIrqType() == _HDCP_2_2_TX_CPIRQ_V_READY)
                {
                    SET_DP_HDCP2_TX_V_READY_BIT();
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);
                }
            }

            if((GET_DP_HDCP2_TX_IRQ_TYPE(_HDCP_2_2_TX_CPIRQ_V_READY) == _HDCP_2_2_TX_CPIRQ_V_READY) ||
               (GET_DP_HDCP2_TX_V_READY_BIT() == _TRUE))
            {
                CLR_DP_HDCP2_TX_IRQ_TARGET_TYPE(_HDCP_2_2_TX_CPIRQ_V_READY);
                CLR_DP_HDCP2_TX_V_READY_BIT();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_FOR_V_READY);

                if(ScalerDpHdcp2TxChecRxInfo() == _TRUE)
                {
                    if(ScalerDpHdcp2TxVerifyVprime() == _TRUE)
                    {
                        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_AUTHEN_DONE);

                        SET_DP_HDCP2_TX_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS);
                    }
                    else
                    {
                        // DP HDCP2.2 CTS 3B-03(Same as 1B-03)
                        SET_DP_HDCP2_TX_AUTH_START();

                        ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                    }
                }
                else
                {
                    // DP HDCP2.2 CTS 3B-04/05(Same as 1B-04/05)
                    SET_DP_HDCP2_TX_AUTH_START();

                    // DP HDCP2.2 CTS 3C-18
                    SET_DP_HDCP2_TX_DOWNSTREAM_EVENT(_DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED);

                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
            }

            if(GET_DP_HDCP2_TX_V_READY_TIMEOUT() == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);

                // DP HDCP2.2 CTS 3B-02(Same as 1B-02)
                SET_DP_HDCP2_TX_AUTH_START();

                ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
            }

            break;

        case _HDCP_2_2_TX_STATE_AUTHEN_DONE:

            if(GET_DP_HDCP2_TX_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPTX HDCP2 - Done", 0);

                CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();
            }

            break;

        default:

            break;
    }

    if((GET_DP_HDCP2_TX_AUTH_STATE() == _HDCP_2_2_TX_STATE_AUTHEN_DONE) ||
       (GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_AUTH_PASS))
    {
        ScalerDpHdcp2TxContentStreamManagementHandler();

#if(_DP_MST_SUPPORT == _ON)
        if(GET_DP_HDCP2_TX_ECF_CHANGE() == _TRUE)
        {
            CLR_DP_HDCP2_TX_ECF_CHANGE();

            if(ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE)
            {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
                {
                    ScalerDpHdcp2TxSetECFProc_128b132b();
                }
                else
#endif
                {
                    ScalerDpHdcp2TxSetECFProc_8b10b();
                }
                DebugMessageHDCP2("DPTX HDCP2 - Encrypt Change", 0);
            }
        }
#endif
    }

    if(ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE)
    {
        if((GET_DP_HDCP2_TX_AUTH_STATE() > _HDCP_2_2_TX_STATE_SKE) &&
           (GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE) &&
           (GET_DP_HDCP2_TX_ENCRYPT_DATA_TIMEOUT() == _TRUE))
        {
            if(ScalerDpMacTxHdcpGetEncryptStatus() == _FALSE)
            {
                ScalerDpHdcp2TxEncryptSignalProc(_ENABLE);

                DebugMessageHDCP2("DPTX HDCP2 - Encrypt", 0);
            }
        }
    }
    else
    {
        if(ScalerDpMacTxHdcpGetEncryptStatus() == _TRUE)
        {
            ScalerDpHdcp2TxEncryptSignalProc(_DISABLE);

            DebugMessageHDCP2("DPTX HDCP2 - Disable Encrypt", 0);
        }
    }
}

//--------------------------------------------------
// Description  : Clear HDCP2 Auth Flag and Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxResetAuthInfo(void)
{
    CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE();
    CLR_DP_HDCP2_TX_H_PRIME_TIMEOUT();
    CLR_DP_HDCP2_TX_PAIRING_INFO_TIMEOUT();
    CLR_DP_HDCP2_TX_AUTH_HOLD();
    CLR_DP_HDCP2_TX_LC_RETRY_COUNTER();
    CLR_DP_HDCP2_TX_ENCRYPT_DATA_TIMEOUT();
    CLR_DP_HDCP2_TX_V_READY_TIMEOUT();
    CLR_DP_HDCP2_TX_POLLING_V_READY();
    CLR_DP_HDCP2_TX_V_READY_BIT();
    CLR_DP_HDCP2_TX_SEQUENCE_NUMBER_M();
    CLR_DP_HDCP2_TX_M_PRIME_TIMEOUT();
    CLR_DP_HDCP2_TX_STOP_CONTENT_STREAM();
    CLR_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT();
    CLR_DP_HDCP2_TX_SEQUENCE_NUMBER_V();
    CLR_DP_HDCP2_TX_ECF_CHANGE();

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_CERTIFICATE);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_H_PRIME);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_PAIRING_INFO);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_FOR_V_READY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_M_PRIME);
}

//--------------------------------------------------
// Description  : Change HDCP2 Auth State
// Input Value  : Target HDCP2 Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxChangeAuthState(EnumHdcp2TxAuthState enumHdcp2AuthState)
{
    SET_DP_HDCP2_TX_AUTH_STATE(enumHdcp2AuthState);
    SET_DP_HDCP2_TX_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Polling IRQ status of Downstream
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumHdcp2TxCpirqType ScalerDpHdcp2TxPollingCpIrqType(void)
{
    if(ScalerDpAuxTxNativeRead(0x06, 0x94, 0x93, 1, pData) == _FALSE)
    {
        return _HDCP_2_2_TX_CPIRQ_NONE;
    }

    if((pData[0] & _BIT4) == _BIT4)
    {
        return _HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL;
    }
    else if((pData[0] & _BIT3) == _BIT3)
    {
        return _HDCP_2_2_TX_CPIRQ_REAUTH_REQUEST;
    }
    else if((pData[0] & _BIT2) == _BIT2)
    {
        return _HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE;
    }
    else if((pData[0] & _BIT1) == _BIT1)
    {
        return _HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE;
    }
    else if((pData[0] & _BIT0) == _BIT0)
    {
        return _HDCP_2_2_TX_CPIRQ_V_READY;
    }

    return _HDCP_2_2_TX_CPIRQ_NONE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxInitial(void)
{
    // The HDCP Tx must set VERSION(0x6900A) to 0x02
    g_pucDpHdcp2TxCaps[0] = 0x02;
    g_pucDpHdcp2TxCaps[1] = 0x00;
    g_pucDpHdcp2TxCaps[2] = 0x00;
}

//--------------------------------------------------
// Description  : Authentication Key Exchange Initial(AKE_init)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxCheckCapability(void)
{
    CLR_DP_HDCP2_TX_CAPABLE_SUPPORTED();
    CLR_DP_HDCP2_TX_REPEATER_SUPPORTED();
    CLR_DP_HDCP2_TX_VERSION_SUPPORTED();
    CLR_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM();

    if(GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_UNPLUG)
    {
        // Disable HDCP 2.2 function
        ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT0, 0x00);

        return;
    }

    // Check if Receiver support HDCP capable and version
    if(ScalerDpAuxTxNativeRead(0x06, 0x92, 0x1D, 3, pData) == _TRUE)
    {
        // Check HDCP Version
        if(((pData[0] == 0x02) || (pData[0] == 0x03) || (pData[0] == 0x04)) &&
           (pData[1] == 0x00) &&
           ((pData[2] & ~(_BIT1 | _BIT0)) == 0x00))
        {
            SET_DP_HDCP2_TX_VERSION_SUPPORTED();
        }

        // Check HDCP Capable
        if((pData[2] & _BIT1) == _BIT1)
        {
            SET_DP_HDCP2_TX_CAPABLE_SUPPORTED();
        }

        // Check HDCP Repeater
        if((pData[2] & _BIT0) == _BIT0)
        {
            SET_DP_HDCP2_TX_REPEATER_SUPPORTED();

            // Check  HDCP2.0 Repeater Downstream in the topology
            if(pData[0] < 0x02)
            {
                SET_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Authentication Key Exchange Initial(AKE_init)
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxAkeInitial(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        // Enable DP TX HDCP function
        ScalerSetBit(P2B_48_DPTX_HDCP_CTRL1, ~_BIT0, _BIT0);

        // Disable AES-Ctrl Cipher
        ScalerSetBit(P2B_69_HDCP22_CTRL1, ~_BIT2, 0x00);
    }
    else
#endif
    {
        // Switch HDCP Cipher Module to HDCP 2.2
        ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT0, _BIT0);

        // Enable DP TX HDCP function
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT0, _BIT0);

        // Disable AES-Ctrl Cipher
        ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, 0x00);
    }

    // Generate Rtx
    if(ScalerDpHdcp2TxRandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load Rtx
    for(pData[0] = 0; pData[0] < 8; pData[0]++)
    {
        g_pucDpHdcp2TxRtx[pData[0]] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - pData[0]);
        PDATA_WORD(1) += g_pucDpHdcp2TxRtx[pData[0]];
    }

    // Disable AES Random Gen
    SET_HDCP22_RANDOM_GENERATOR_DISABLE();

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }

    // Write Rtx to the DPCD Table of Downstream Device
    if(ScalerDpAuxTxNativeWrite(0x06, 0x90, 0x00, 8, g_pucDpHdcp2TxRtx) == _FALSE)
    {
        return _FALSE;
    }

    // Write TxCaps to the DPCD Table of Downstream Device
    if(ScalerDpAuxTxNativeWrite(0x06, 0x90, 0x08, 3, g_pucDpHdcp2TxCaps) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : AES Random Pattern Generator
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxRandomGenerate(void)
{
    // Enable AES Random Gen
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), (_BIT5));

    // AES Trigger
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    for(pData[0] = 0; pData[0] < (GET_MCU_TIMER_RANDOM_BYTE() >> 2); pData[0]++)
    {
        DELAY_5US();
    }

    // Wait Finish for AES Random Gen
    pData[1] = 0x0A;

    do
    {
        DELAY_5US();
    }
    while((ScalerGetBit(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && ((--pData[1]) != 0));

    if(ScalerGetBit(P63_60_HDCP_AES_CTRL, _BIT5) == 0x00)
    {
        SET_HDCP22_RANDOM_GENERATOR_DISABLE();

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Read Certificate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxTimeoutToReadCertificateEvent(void)
{
    SET_DP_HDCP2_TX_LOAD_KEY_EN();
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Circuit Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxDcpLlcRsaInit(void)
{
    // Enable HDCP 2.2 RSA Module
    SET_HDCP22_RSA_WRITE_KEY_MODE();

    // RSA Clock Select
    SET_HDCP22_RSA_CLK();

    // Reset HDCP 2.2 RSA module
    SET_HDCP22_SOFTWARE_RESET();
    CLR_HDCP22_SOFTWARE_RESET();

    // Select RSA Key Download Data Length
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), 0x00);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Load Key Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxLoadKeyProc(BYTE ucLoadKeyType, BYTE *pucDpTxHdcp2Key)
{
    switch(ucLoadKeyType)
    {
        case _DP_TX_HDCP2_KEY_SIGNATURE:

            for(pData[0] = 0; pData[0] < 48; pData[0]++)
            {
                // Enable write cipher text to RSA Module
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (47 - pData[0]));

                memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Key[pData[0] << 3], 8);

                // Rsa Data Write-in
                ScalerHdcp2RxRsaWriteData();

                /*
                for(pData[1] = 0; pData[1] < 8; pData[1]++)
                {
                    DebugMessageHDCP2("S'", pucSignature[(pData[0] << 3) + pData[1]]);
                }
                */
            }

            break;

        case _DP_TX_HDCP2_KEY_RRMODN:

            for(pData[0] = 0; pData[0] < 48; pData[0]++)
            {
                // Load RRmodN
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (47 - pData[0])));

                memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Key[pData[0] << 3], 8);

                // Rsa Data Write-in
                ScalerHdcp2RxRsaWriteData();
            }

            break;

        case _DP_TX_HDCP2_KEY_DCP_LLC_N:

            for(pData[0] = 0; pData[0] < 48; pData[0]++)
            {
                // Load DCP LLC Public N Key
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (47 - pData[0])));

                memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Key[pData[0] << 3], 8);

                // Rsa Data Write-in
                ScalerHdcp2RxRsaWriteData();
            }

            break;

        case _DP_TX_HDCP2_KEY_EKEY1:

            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                // Load e Key(0x00)
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (47 - pData[0])));

                for(pData[1] = 0; pData[1] < 8; pData[1]++)
                {
                    ScalerSetByte((P63_17_HDCP_RSA_DATA_IN_DATA7 + pData[1]), 0x00);
                }

                // Rsa Data Write-in
                ScalerHdcp2RxRsaWriteData();
            }

            break;

        case _DP_TX_HDCP2_KEY_EKEY2:

            for(pData[0] = 32; pData[0] < 48; pData[0]++)
            {
                // Load e Key
                ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (47 - pData[0])));
                memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Key[(pData[0] - 32) << 3], 8);

                // Rsa Data Write-in
                ScalerHdcp2RxRsaWriteData();
            }

            break;

        case _DP_TX_HDCP2_KEY_NPINV:

            memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, pucDpTxHdcp2Key, 4);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Start RSA Calculate
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxDcpLlcRsaCalculate(void)
{
    // Set RSA Write key done
    SET_HDCP22_RSA_WRITE_KEY_DONE();

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT0), 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        CLR_HDCP22_RSA_MODULE_ENABLE();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signature Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxVerifySignature(void)
{
    BYTE ucI = 0;
    WORD usDpcdAddress = 0;
    BYTE pucSha256Input[64] = {0};
    BYTE pucDpTxHdcp2CertificatePart1[138] = {0};
    BYTE pucDpTxHdcp2Signature[384] = {0};
    BYTE pucDigestInfo[20] =
    {
        0x00, 0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48,
        0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20
    };

    // Read Certificate Part I: Receiver ID(5 bytes) + Public Key(131 bytes) + Reserved(2 bytes)
    // Read Receiver ID(5 Bytes)
    if(ScalerDpAuxTxNativeRead(0x06, 0x90, 0x0B, 5, pData) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(pucDpTxHdcp2CertificatePart1, pData, 5);
    memcpy(g_pucDpHdcp2TxReceiverId, pData, 5);

    // Read Public n(128 Bytes)
    for(ucI = 0; ucI < 8; ucI++)
    {
        if(ScalerDpAuxTxNativeRead(0x06, 0x90, (0x10 + ucI * 16), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        memcpy(&pucDpTxHdcp2CertificatePart1[5 + ucI * 16], pData, 16);
    }

    memcpy(g_pucDpHdcp2TxNpub, &pucDpTxHdcp2CertificatePart1[5], 128);

    // Read Public e(3 Bytes) and Reserved(2 Bytes)
    if(ScalerDpAuxTxNativeRead(0x06, 0x90, 0x90, 5, pData) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(&pucDpTxHdcp2CertificatePart1[133], pData, 5);
    memcpy(g_pucDpHdcp2TxEpub, &pucDpTxHdcp2CertificatePart1[133], 3);

    // Read Certificate Part II: Signature
    // Initial DPCD Address of Signature
    usDpcdAddress = 0x9095;

    for(ucI = 0; ucI < 24; ucI++)
    {
        if(ScalerDpAuxTxNativeRead(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        memcpy(&pucDpTxHdcp2Signature[ucI * 16], pData, 16);

        usDpcdAddress += 16;
    }

    for(ucI = 0; ucI < 48; ucI++)
    {
        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (47 - ucI));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucDpTxHdcp2Signature[ucI << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();

        /*
        for(pData[1] = 0; pData[1] < 8; pData[1]++)
        {
            DebugMessageHDCP2("S'", pucSignature[(pData[0] << 3) + pData[1]]);
        }
        */
    }

    // Read Rrx
    if(ScalerDpAuxTxNativeRead(0x06, 0x92, 0x15, 8, pData) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(g_pucDpHdcp2TxRrx, pData, 8);

    // Read RxCaps
    if(ScalerDpAuxTxNativeRead(0x06, 0x92, 0x1D, 3, pData) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(g_pucDpHdcp2TxRxCaps, pData, 3);

    CLR_DP_HDCP2_TX_CAPABLE_SUPPORTED();
    CLR_DP_HDCP2_TX_REPEATER_SUPPORTED();
    CLR_DP_HDCP2_TX_VERSION_SUPPORTED();
    CLR_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM();

    // Check HDCP Version
    if(((pData[0] == 0x02) || (pData[0] == 0x03) || (pData[0] == 0x04)) &&
       (pData[1] == 0x00) &&
       ((pData[2] & ~(_BIT1 | _BIT0)) == 0x00))
    {
        SET_DP_HDCP2_TX_VERSION_SUPPORTED();
    }

    // Check HDCP Capable
    if((pData[2] & _BIT1) == _BIT1)
    {
        SET_DP_HDCP2_TX_CAPABLE_SUPPORTED();
    }

    // Check HDCP Repeater
    if((pData[2] & _BIT0) == _BIT0)
    {
        SET_DP_HDCP2_TX_REPEATER_SUPPORTED();

        // Check  HDCP2.0 Repeater Downstream in the topology
        if(pData[0] < 0x02)
        {
            SET_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM();
        }
    }

    // Compute Encode Message(EM)
    for(ucI = 0; ucI < 2; ucI++)
    {
        memcpy(pucSha256Input, &pucDpTxHdcp2CertificatePart1[ucI * 64], 64);

        if(ScalerHdcp2RxSha256Calculate(pucSha256Input, ucI) == _FALSE)
        {
            return _FALSE;
        }
    }

    memcpy(pucSha256Input, &pucDpTxHdcp2CertificatePart1[128], 10);
    memset(&pucSha256Input[10], 0, 54);
    pucSha256Input[10] = 0x80;
    pucSha256Input[62] = 0x04;
    pucSha256Input[63] = 0x50;

    if(ScalerHdcp2RxSha256Calculate(pucSha256Input, 2) == _FALSE)
    {
        return _FALSE;
    }

    // Get SHA-256(M) of EM
    memcpy(pucSha256Input, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    /*
    for(pData[0] = 0; pData[0] < 32; pData[0]++)
    {
        DebugMessageHDCP2("EM", ScalerGetByte(P63_35_HDCP_SHA_0 + pData[0]));
    }
    */

    // Compute Encode Message Prime(EM')
    ScalerDpHdcp2TxDcpLlcRsaCalculate();

    // Get EM'
    SET_HDCP22_RSA_READ_OUT_MODE();

    // Read Message From One of 2 Address
    if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(pData[0] = 0; pData[0] < 48; pData[0]++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (47 - pData[0]));

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucDpTxHdcp2Signature[pData[0] << 3], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(pData[0] = 0; pData[0] < 48; pData[0]++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 + (47 - pData[0])));

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucDpTxHdcp2Signature[pData[0] << 3], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }

    // Compare EM with EM'
    // EM[3071:0] = 0x00 || 0x01 || PS || 0x00 || T(SHA256) || SHA-256(M), length = 3072 bits

    // Check 0x00 || 0x01
    if((pucDpTxHdcp2Signature[0] != 0x00) && (pucDpTxHdcp2Signature[1] != 0x01))
    {
        DebugMessageHDCP2("S - Fail 0", 0);

        return _FALSE;
    }

    // Check PS(330 bytes)
    for(PDATA_WORD(0) = 2; PDATA_WORD(0) < 332; PDATA_WORD(0)++)
    {
        if(pucDpTxHdcp2Signature[PDATA_WORD(0)] != 0xFF)
        {
            DebugMessageHDCP2("S - Fail 1", PDATA_WORD(0));

            return _FALSE;
        }
    }

    // Check T(SHA256)
    for(PDATA_WORD(0) = 332; PDATA_WORD(0) < 352; PDATA_WORD(0)++)
    {
        if(pucDpTxHdcp2Signature[PDATA_WORD(0)] != pucDigestInfo[PDATA_WORD(0) - 332])
        {
            DebugMessageHDCP2("S - Fail 2", PDATA_WORD(0));

            return _FALSE;
        }
    }

    // Check SHA-256(M)
    for(PDATA_WORD(0) = 352; PDATA_WORD(0) < 384; PDATA_WORD(0)++)
    {
        if(pucDpTxHdcp2Signature[PDATA_WORD(0)] != pucSha256Input[PDATA_WORD(0) - 352])
        {
            DebugMessageHDCP2("S - Fail 3", PDATA_WORD(0));

            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2TxRsaCalculate(BYTE *pucEmKmArray, BYTE *pucRrmodn)
{
    BYTE pucEpubXorCode[128] = {0};

    ScalerHdcp2Proc3(pucEpubXorCode);

    // Enable HDCP 2.2 RSA Module
    SET_HDCP22_RSA_WRITE_KEY_MODE();

    // RSA Clock Select
    SET_HDCP22_RSA_CLK();

    // Reset HDCP 2.2 RSA module
    SET_HDCP22_SOFTWARE_RESET();
    CLR_HDCP22_SOFTWARE_RESET();

    // Select RSA Key Download Data Length
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

    // Load EM_km to RSA Module as Plain text
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(15 - pData[0]));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEmKmArray[pData[0] << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load RRmodN
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucRrmodn[pData[0] << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_pucDpHdcp2TxNpub[pData[0] << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    // Encrypted Epub Key
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        pucEpubXorCode[125 + pData[0]] = pucEpubXorCode[125 + pData[0]] ^ g_pucDpHdcp2TxEpub[pData[0]];
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load e Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEpubXorCode[pData[0] << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT0), 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        CLR_HDCP22_RSA_MODULE_ENABLE();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : No Stored Km Procss
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxNoStoredKmProc(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    BYTE pucEkpubKm[128] = {0};
    BYTE pucDB[95] = {0};
    BYTE pucTemp[16] = {0};
    BYTE pucSeed[32] = {0};

    // Encrypt Km
    // Step1: Hash stream  L = 32byte 0x00 stream, lHash = SHA256(L) = 0x e3 b0 04 42 == > hLen = 32byte
    // Step2: PS stream = 0x00 stream == > PS Length = length(n) - length(km)-2xhLen-2 = 128 - 16 - 2x32 -2 = 46bytes
    // Step3: M = km stream == > km length = 16bytes

    // Generate Km
    if(ScalerDpHdcp2TxRandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load Km
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        pucTemp[pData[0]] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - pData[0]);
        PDATA_WORD(1) += pucTemp[pData[0]];
    }

    // Disable AES Random Gen
    SET_HDCP22_RANDOM_GENERATOR_DISABLE();

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }

    // Step4: DB = lHash || PS || 0x01 || M == > DB Length = 95bytes
    memcpy(pucDB, tLHash, 32);
    memset(&pucDB[32], 0, 46);
    pucDB[78] = 0x01;
    memcpy(&pucDB[79], pucTemp, 16);

    ScalerHdcp2Proc2(g_pucDpHdcp2TxKm, pucTemp);

    // Step5: Generate random stream seed == > Seed Length = hLen = 32bytes

    // Generate 16 bytes for Msb part of Random Stream Seed
    if(ScalerDpHdcp2TxRandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        pucSeed[pData[0]] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - pData[0]);
        PDATA_WORD(1) += pucSeed[pData[0]];
    }

    // Disable AES Random Gen
    SET_HDCP22_RANDOM_GENERATOR_DISABLE();

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }

    // Generate 16 bytes for Lsb part of Random Stream Seed
    if(ScalerDpHdcp2TxRandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        pucSeed[pData[0] + 16] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - pData[0]);
        PDATA_WORD(1) += pucSeed[pData[0] + 16];
    }

    // Disable AES Random Gen
    SET_HDCP22_RANDOM_GENERATOR_DISABLE();

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }

    // Step6: dbMask = MGF (seed, k-hLen-1) == > dbMask Length = 95bytes
    {
        BYTE pucSHA256Input[64] = {0};

        memcpy(pucSHA256Input, pucSeed, 32);
        memset(&pucSHA256Input[32], 0, 32);
        pucSHA256Input[36] = 0x80;
        pucSHA256Input[62] = 0x01;
        pucSHA256Input[63] = 0x20;

        for(ucI = 0; ucI < 3; ucI++)
        {
            pucSHA256Input[35] = ucI;

            if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0) == _FALSE)
            {
                return _FALSE;
            }

            for(ucJ = 0; ucJ < 32; ucJ++)
            {
                pucEkpubKm[(ucI * 32) + ucJ] = ScalerGetByte((P63_35_HDCP_SHA_0 + ucJ));
            }
        }

        // Step7: maskedDB = DB XOR dbMask; == > maskedDB = 95 bytes
        for(ucI = 0; ucI < 95; ucI++)
        {
            pucDB[ucI] = pucDB[ucI] ^ pucEkpubKm[ucI];
        }

        // Step8: seedMask = MGF(maskedDB, hLen) == > seedMask Length = 32bytes
        memcpy(pucSHA256Input, pucDB, 64);

        if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0) == _FALSE)
        {
            return _FALSE;
        }

        memcpy(pucSHA256Input, &pucDB[64], 31);
        memset(&pucSHA256Input[31], 0, 33);
        pucSHA256Input[35] = 0x80;
        pucSHA256Input[62] = 0x03;
        pucSHA256Input[63] = 0x18;

        if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 1) == _FALSE)
        {
            return _FALSE;
        }
    }

    // Step9: maskedSeed = seed XOR seedMask == > maskedSeed Length = 32bytes
    for(ucI = 0; ucI < 32; ucI++)
    {
        pucEkpubKm[1 + ucI] = pucSeed[ucI] ^ ScalerGetByte((P63_35_HDCP_SHA_0 + ucI));
    }

    // Step10: EM = 0x00 || maskedSeed || maskedDB ==> EM Length = 1+ 32 + 95 = 128bytes
    pucEkpubKm[0] = 0x00;
    memcpy(&pucEkpubKm[33], pucDB, 95);

    ScalerDpHdcp2TxRrmodnCalculate(g_pucDpHdcp2TxNpub);

    // Read Out RSA Message
    SET_HDCP22_RSA_READ_OUT_MODE();

    // Read RRmodN
    {
        BYTE pucRrmodn[128] = {0};

        for(ucI = 0; ucI < 16; ucI++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 + (15 - ucI)));

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucRrmodn[ucI * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }

        // Generate Ekpub[km]
        ScalerDpHdcp2TxRsaCalculate(pucEkpubKm, pucRrmodn);
    }

    // Read Out RSA Message
    SET_HDCP22_RSA_READ_OUT_MODE();

    // Read Message From One of 2 Address
    if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(ucI = 0; ucI < 16; ucI++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (15 - ucI));

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucEkpubKm[ucI * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(ucI = 0; ucI < 16; ucI++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 + (15 - ucI)));

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucEkpubKm[ucI * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }

    // Write Ekpub[km]
    for(ucI = 0; ucI < 8; ucI++)
    {
        if(ScalerDpAuxTxNativeWrite(0x06, 0x92, (0x20 + ucI * 16), 16, &pucEkpubKm[ucI * 16]) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Stored Km Procss
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxRrmodnCalculate(BYTE *pucPubN)
{
    BYTE pucEpubXorCode[128] = {0};

    ScalerHdcp2Proc3(pucEpubXorCode);

    // Enable HDCP 2.2 RSA Module
    SET_HDCP22_RSA_WRITE_KEY_MODE();

    // RSA Clock Select
    SET_HDCP22_RSA_CLK();

    // Reset HDCP 2.2 RSA module
    SET_HDCP22_SOFTWARE_RESET();
    CLR_HDCP22_SOFTWARE_RESET();

    // Select RSA Key Download Data Length and RRMODN mode
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - pData[0])));

        memset((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, 0, 8);

        if((0x30 + (15 - pData[0])) == 0x3F)
        {
            ScalerSetByte(P63_17_HDCP_RSA_DATA_IN_DATA7, 0x80);
        }

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucPubN[pData[0] << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    // 1024 bits + 66 bits
    PDATA_WORD(0) = 1088;

    pucEpubXorCode[126] = HIBYTE(PDATA_WORD(0)) ^ pucEpubXorCode[126];
    pucEpubXorCode[127] = LOBYTE(PDATA_WORD(0)) ^ pucEpubXorCode[127];

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        // Load e Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEpubXorCode[pData[0] << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    // Get Npub Mod 2^32
    PDATA_DWORD(0) = TO_DWORD(g_pucDpHdcp2TxNpub[124],
                              g_pucDpHdcp2TxNpub[125],
                              g_pucDpHdcp2TxNpub[126],
                              g_pucDpHdcp2TxNpub[127]);

    // Get Npinv
    PDATA_DWORD(0) = ScalerDpHdcp2TxNpinvCalculate(PDATA_DWORD(0));

    // Load Npinv to RSA Module
    ScalerSetByte(P63_12_HDCP_RSA_NP_INV_3, (BYTE)(PDATA_DWORD(0) >> 24));
    ScalerSetByte(P63_13_HDCP_RSA_NP_INV_2, (BYTE)(PDATA_DWORD(0) >> 16));
    ScalerSetByte(P63_14_HDCP_RSA_NP_INV_1, (BYTE)(PDATA_DWORD(0) >> 8));
    ScalerSetByte(P63_15_HDCP_RSA_NP_INV_0, (BYTE)(PDATA_DWORD(0) >> 0));

    // Set RSA Write key done
    SET_HDCP22_RSA_WRITE_KEY_DONE();

    // Get Mod N Shift Counter
    PDATA_WORD(0) = ScalerDpHdcp2TxGetNShiftCounter(pucPubN);

    // Set Mod N Shift Counter
    ScalerSetByte(P63_28_HDCP_RSA_TX_FUNTION1, (BYTE)(PDATA_WORD(0) >> 4));
    ScalerSetBit(P63_29_HDCP_RSA_TX_FUNTION0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (BYTE)(PDATA_WORD(0) << 4));

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT0), 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        CLR_HDCP22_RSA_MODULE_ENABLE();

        // Disable RRMODN mode
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~_BIT5, 0x00);

        return _TRUE;
    }

    // Disable RRMODN mode
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~_BIT5, 0x00);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Calculate Mod N Shift Counter
// Input Value  : None
// Output Value : 66 ~ 1089 => (1023 - (MSB No. of Kpubdcp-key) + 66)
//--------------------------------------------------
WORD ScalerDpHdcp2TxGetNShiftCounter(BYTE *pucPubN)
{
    for(pData[0] = 0; pData[0] < 128; pData[0]++)
    {
        for(pData[1] = 0; pData[1] < 8; pData[1]++)
        {
            if((bit)(pucPubN[pData[0]] & (_BIT7 >> pData[1])) == 1)
            {
                return ((WORD)(pData[0] * 8) + pData[1] + 66);
            }
        }
    }

    return 0x0441;
}

//--------------------------------------------------
// Description  : Npinv Calculate by Euclidean Algorithm
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
DWORD ScalerDpHdcp2TxNpinvCalculate(DWORD ulA)
{
    DWORD ulM = 0xFFFFFFFF; // 2^32 - 1
    DWORD ulE = ulM - ulA + 1;
    DWORD ulX = 0;
    DWORD ulY = 1;
    DWORD ulx = 1;
    DWORD uly = 1;

    while(ulE != 0)
    {
        PDATA_DWORD(0) = ulM / ulE;
        PDATA_DWORD(1) = ulM % ulE;

        if(ulM == 0xFFFFFFFF)
        {
            PDATA_DWORD(1)++;
        }

        ulM = ulE;
        ulE = PDATA_DWORD(1);

        PDATA_DWORD(1) = ulY;

        ulY *= PDATA_DWORD(0);

        if(ulx == uly)
        {
            if(ulX >= ulY)
            {
                ulY = ulX - ulY;
            }
            else
            {
                ulY -= ulX;
                uly = 0;
            }
        }
        else
        {
            ulY += ulX;
            ulx = 1 - ulx;
            uly = 1 - uly;
        }

        ulX = PDATA_DWORD(1);
    }

    if(ulx == 0)
    {
        ulX = 0xFFFFFFFF - ulX + 1;
    }

    return ulX;
}

//--------------------------------------------------
// Description  : Stored Km Procss
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxStoredKmProc(void)
{
    // Send Ekh[km]
    if(ScalerDpAuxTxNativeWrite(0x06, 0x92, 0xA0, 16, g_pucDpHdcp2TxPairingEkhkm) == _FALSE)
    {
        return _FALSE;
    }

    // Send m
    if(ScalerDpAuxTxNativeWrite(0x06, 0x92, 0xB0, 16, g_pucDpHdcp2TxPairingM) == _FALSE)
    {
        return _FALSE;
    }

    // Delay 10ms for DFP replying MSG Flow after reading 692B0 to prevent DFP entering Interrupt force defer
    ScalerTimerDelayXms(10);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Read H'
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxTimeoutToReadHPrimeEvent(void)
{
    SET_DP_HDCP2_TX_H_PRIME_TIMEOUT();
}

//--------------------------------------------------
// Description  : H Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxComputeH(BYTE *pucDpTxHdcp2Rtx, BYTE *pucDpTxHdcp2Rrx, BYTE *pucDpTxHdcp2Km)
{
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    BYTE pucTemp3[32] = {0};
    BYTE ucLoop = 0;

    // Get Kd = dkey0 || dkey1
    ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_0, pucDpTxHdcp2Rtx, pucDpTxHdcp2Rrx, pucDpTxHdcp2Km, g_pucDpHdcp2TxRn);

    memcpy(pucTemp1, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

    ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_1, pucDpTxHdcp2Rtx, pucDpTxHdcp2Rrx, pucDpTxHdcp2Km, g_pucDpHdcp2TxRn);

    memcpy(pucTemp2, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

    // Compute H
    if(ScalerHdcp2HPrimeCalculate(pucTemp1, pucTemp2, pucDpTxHdcp2Rtx, g_pucDpHdcp2TxCaps, g_pucDpHdcp2TxRxCaps) == _FALSE)
    {
        return _FALSE;
    }

    // Get H
    memcpy(pucTemp3, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    ScalerHdcp2Proc2(g_pucDpHdcp2TxdKey0, pucTemp1);
    ScalerHdcp2Proc2(g_pucDpHdcp2TxdKey1, pucTemp2);

    for(ucLoop = 0; ucLoop < 2; ucLoop++)
    {
        ScalerHdcp2Proc2(&g_pucDpHdcp2TxH[ucLoop * 16], &pucTemp3[ucLoop * 16]);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : H Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxVerifyHprime(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    BYTE pucTemp[32] = {0};
    BYTE ucLoop = 0;

    for(ucLoop = 0; ucLoop < 2; ucLoop++)
    {
        ScalerHdcp2Proc2(&pucTemp[ucLoop * 16], &g_pucDpHdcp2TxH[ucLoop * 16]);
    }

    // Read H' and Compare H' with H
    for(ucI = 0; ucI < 2; ucI++)
    {
        if(ScalerDpAuxTxNativeRead(0x06, 0x92, (0xC0 + ucI * 16), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        for(ucJ = 0; ucJ < 16; ucJ++)
        {
            if(pucTemp[16 * ucI + ucJ] != pData[ucJ])
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Pairing Info
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxStorePairingInfo(void)
{
    // Store Ekn[km]
    if(ScalerDpAuxTxNativeRead(0x06, 0x92, 0xE0, 16, g_pucDpHdcp2TxPairingEkhkm) == _FALSE)
    {
        return _FALSE;
    }

    // Store Km. m, Receiver ID
    memcpy(g_pucDpHdcp2TxPairingKm, g_pucDpHdcp2TxKm, 16);
    memcpy(g_pucDpHdcp2TxPairingM, g_pucDpHdcp2TxRtx, 8);
    memcpy(&g_pucDpHdcp2TxPairingM[8], g_pucDpHdcp2TxRrx, 8);
    memcpy(g_pucDpHdcp2TxPairingReceiverID, g_pucDpHdcp2TxReceiverId, 5);

    SET_DP_HDCP2_TX_PAIRING_INFO_READY();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Clear Pairing Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxClearPairingInfo(void)
{
    // Clear Km. m, Receiver ID
    memset(g_pucDpHdcp2TxPairingKm, 0, sizeof(g_pucDpHdcp2TxPairingKm));
    memset(g_pucDpHdcp2TxPairingM, 0, sizeof(g_pucDpHdcp2TxPairingM));
    memset(g_pucDpHdcp2TxPairingReceiverID, 0, sizeof(g_pucDpHdcp2TxPairingReceiverID));

    CLR_DP_HDCP2_TX_PAIRING_INFO_READY();
}

//--------------------------------------------------
// Description  : Check Pairing Info
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxCheckPairingInfo(void)
{
    BYTE ucI = 0;

    if(GET_DP_HDCP2_TX_PAIRING_INFO_READY() == _FALSE)
    {
        return _FALSE;
    }

    for(ucI = 0; ucI < 5; ucI++)
    {
        if(g_pucDpHdcp2TxPairingReceiverID[ucI] != g_pucDpHdcp2TxReceiverId[ucI])
        {
            ScalerDpHdcp2TxClearPairingInfo();

            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Read pairing Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxTimeoutToReadPairingInfoEvent(void)
{
    SET_DP_HDCP2_TX_PAIRING_INFO_TIMEOUT();
}

//--------------------------------------------------
// Description  : Locality Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxLocalityCheck(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    WORD usDpcdAddress = 0;
    BYTE pucL[32] = {0};
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};

    // Generate Rn
    if(ScalerDpHdcp2TxRandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load Rn
    for(ucI = 0; ucI < 8; ucI++)
    {
        g_pucDpHdcp2TxRn[ucI] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - ucI);
        PDATA_WORD(1) += g_pucDpHdcp2TxRn[ucI];
    }

    // Disable AES Random Gen
    SET_HDCP22_RANDOM_GENERATOR_DISABLE();

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }

    // Write Rn
    if(ScalerDpAuxTxNativeWrite(0x06, 0x92, 0xF0, 8, g_pucDpHdcp2TxRn) == _FALSE)
    {
        return _FALSE;
    }

    ScalerTimerDelayXms(20);

    // Compute L
    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2TxdKey0);
    ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2TxdKey1);

    if(ScalerHdcp2LPrimeCalculate(pucTemp1, pucTemp2, g_pucDpHdcp2TxRrx, g_pucDpHdcp2TxRn) == _FALSE)
    {
        return _FALSE;
    }

    // Get L
    memcpy(pucL, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    // Initial DPCD Address of L'
    usDpcdAddress = 0x92F8;

    // Read L' and Compare L' with L
    for(ucI = 0; ucI < 2; ucI++)
    {
        if(ScalerDpAuxTxNativeRead(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        for(ucJ = 0; ucJ < 16; ucJ++)
        {
            if(pucL[16 * ucI + ucJ] != pData[ucJ])
            {
                return _FALSE;
            }
        }

        usDpcdAddress += 16;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Session Key Exchange Proc
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxSessionKeyExchangeProc(void)
{
    BYTE ucI = 0;
    BYTE pucdKey2[16] = {0};

    BYTE pucKs[16] = {0};
    BYTE pucdRiv[8] = {0};
    BYTE pucTemp[16] = {0};

    ScalerHdcp2Proc1(pucTemp, g_stHdcp2RxDownLoadKeyType.pucHdcp2Lc);

    // Generate Ks(128 bits)
    if(ScalerDpHdcp2TxRandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load Ks
    for(ucI = 0; ucI < 16; ucI++)
    {
        pucKs[ucI] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - ucI);
        PDATA_WORD(1) += pucKs[ucI];

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
        {
            // Set Ks to Cipher
            ScalerSetByte((P2B_55_HDCP_AES_CIPHER_KEY_15 + ucI), (pucKs[ucI] ^ pucTemp[ucI]));
        }
        else
#endif
        {
            // Set Ks to Cipher
            ScalerSetByte((PBB_80_HDCP_AES_CIPHER_KEY_15 + ucI), (pucKs[ucI] ^ pucTemp[ucI]));
        }
    }

    // Disable AES Random Gen
    SET_HDCP22_RANDOM_GENERATOR_DISABLE();

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }

    // Generate dkey2
    ScalerHdcp2Proc2(pucTemp, g_pucDpHdcp2TxKm);

    ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_2, g_pucDpHdcp2TxRtx, g_pucDpHdcp2TxRrx, pucTemp, g_pucDpHdcp2TxRn);

    memcpy(pucdKey2, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

    // Compute Edkey(ks)
    // LSB 64bits of dkey2 ^ Rrx
    for(ucI = 0; ucI < 8; ucI++)
    {
        pucdKey2[ucI + 8] = g_pucDpHdcp2TxRrx[ucI] ^ pucdKey2[ucI + 8];
    }

    // Edkey(ks) = ks ^ (dkey2 ^ Rrx)
    for(ucI = 0; ucI < 16; ucI++)
    {
        pucKs[ucI] = pucKs[ucI] ^ pucdKey2[ucI];
    }

    // Write Edkey(ks)
    if(ScalerDpAuxTxNativeWrite(0x06, 0x93, 0x18, 16, pucKs) == _FALSE)
    {
        return _FALSE;
    }

    // Generate riv(64 bits)
    if(ScalerDpHdcp2TxRandomGenerate() == _FALSE)
    {
        return _FALSE;
    }

    PDATA_WORD(1) = 0x0000;

    // Load riv
    for(ucI = 0; ucI < 8; ucI++)
    {
        pucdRiv[ucI] = ScalerGetByte(P63_90_HDCP_AES_OUT_0 - ucI);
        PDATA_WORD(1) += pucdRiv[ucI];

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
        {
            // Set Riv to Cipher
            ScalerSetByte((P2B_40_RIV0 + ucI), pucdRiv[ucI]);
        }
        else
#endif
        {
            // Set Riv to Cipher
            ScalerSetByte((PBB_11_RIV0 + ucI), pucdRiv[ucI]);
        }
    }

    // Disable AES Random Gen
    SET_HDCP22_RANDOM_GENERATOR_DISABLE();

    if(PDATA_WORD(1) == 0x0000)
    {
        return _FALSE;
    }

    // Write riv
    if(ScalerDpAuxTxNativeWrite(0x06, 0x93, 0x28, 8, pucdRiv) == _FALSE)
    {
        return _FALSE;
    }

    memcpy(g_pucDpHdcp2TxRiv, pucdRiv, sizeof(g_pucDpHdcp2TxRiv));

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Encrypt Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxTimeoutToEncyptDataEvent(void)
{
    SET_DP_HDCP2_TX_ENCRYPT_DATA_TIMEOUT();
}

//--------------------------------------------------
// Description  : Waiting for V ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxTimeoutForVReadyEvent(void)
{
    SET_DP_HDCP2_TX_V_READY_TIMEOUT();
}

//--------------------------------------------------
// Description  : Polling V Ready bit
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxPollingVReadyEvent(void)
{
    SET_DP_HDCP2_TX_POLLING_V_READY();
}

//--------------------------------------------------
// Description  : Check Rx Info
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxChecRxInfo(void)
{
    // Read Rxinfo(Device Count and Depth)
    ScalerDpAuxTxNativeRead(0x06, 0x93, 0x30, 2, pData);

    // Check if MAX_DEVS_EXCEEDED or MAX_CASCADE_EXCEEDED is 1 and then abort authentication
    if((pData[1] & _BIT3) == _BIT3)
    {
        SET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED();
    }
    else
    {
        CLR_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED();
    }

    if((pData[1] & _BIT2) == _BIT2)
    {
        SET_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED();
    }
    else
    {
        CLR_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED();
    }

    // Set Rx Info
    SET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT(((pData[0] & _BIT0) << 4) | (pData[1] & 0xF0) >> 4);
    SET_DP_HDCP2_TX_RXINFO_DEPTH((pData[0] & 0x0E) >> 1);

    if((GET_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM() == _FALSE) && ((pData[1] & _BIT1) == _BIT1))
    {
        SET_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM();
    }

    if((pData[1] & _BIT0) == _BIT0)
    {
        SET_DP_HDCP2_TX_RXINFO_HDCP1_DOWNSTREAM();
    }
    else
    {
        CLR_DP_HDCP2_TX_RXINFO_HDCP1_DOWNSTREAM();
    }

    if((GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED() == _TRUE) ||
       (GET_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED() == _TRUE))
    {
        return _FALSE;
    }

    DebugMessageHDCP2("Get Downstream Device", GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT());
    DebugMessageHDCP2("Get Downstream Depth", GET_DP_HDCP2_TX_RXINFO_DEPTH());

    return _TRUE;
}

//--------------------------------------------------
// Description  : V Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxVerifyVprime(void)
{
    BYTE pucRxInfo[2] = {0};
    BYTE pucSeqNumV[3] = {0};
    WORD usDpcdAddress = 0;
    BYTE pucV[32] = {0};
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};

    memset(g_pucDpHdcp2TxReceiverIdList, 0, sizeof(g_pucDpHdcp2TxReceiverIdList));


    // Read Rxinfo
    pucRxInfo[0] = ((GET_DP_HDCP2_TX_RXINFO_DEPTH() << 1) | (GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT() >> 4));
    pucRxInfo[1] = ((GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT() << 4) |
                    ((BYTE)GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED() << 3) |
                    ((BYTE)GET_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED() << 2) |
                    ((BYTE)GET_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM() << 1) |
                    (GET_DP_HDCP2_TX_RXINFO_HDCP1_DOWNSTREAM()));

    // Read seq_bum_V
    ScalerDpAuxTxNativeRead(0x06, 0x93, 0x32, 3, pucSeqNumV);

    PDATA_DWORD(0) = ((DWORD)pucSeqNumV[0] << 16) | ((DWORD)pucSeqNumV[1] << 8) | (DWORD)pucSeqNumV[2];

    if((GET_DP_HDCP2_TX_SEQUENCE_NUMBER_V() == 0x00FFFFFF) && (PDATA_DWORD(0) == 0x00))
    {
        return _FALSE;
    }

    SET_DP_HDCP2_TX_SEQUENCE_NUMBER_V(PDATA_DWORD(0));

    pucV[0] = GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT() * 5;

    // Initial DPCD Address of Receicer ID List
    usDpcdAddress = 0x9345;

    // Read KSV FIFO List from Downstream Device
    do
    {
        ScalerDpAuxTxNativeRead(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), ((pucV[0] > 15) ? 15 : pucV[0]), pData);

        memcpy(&g_pucDpHdcp2TxReceiverIdList[pucV[1]], pData, ((pucV[0] > 15) ? 15 : pucV[0]));

        usDpcdAddress += 15;
        pucV[1] += 15;

        pucV[0] = (pucV[0] > 15) ? (pucV[0] - 15) : 0x00;
    }
    while(pucV[0] != 0x00);

    // Compute V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2TxdKey0);
    ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2TxdKey1);

    if(ScalerHdcp2VprimeCalculate(pucTemp1, pucTemp2, g_pucDpHdcp2TxReceiverIdList, pucRxInfo, pucSeqNumV) == _FALSE)
    {
        return _FALSE;
    }

    // Get V
    memcpy(pucV, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
    memcpy(g_pucDpHdcp2TxDownStreamV, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 20);

    // Read MSB of V'
    if(ScalerDpAuxTxNativeRead(0x06, 0x93, 0x35, 16, pData) == _FALSE)
    {
        return _FALSE;
    }

    for(usDpcdAddress = 0; usDpcdAddress < 16; usDpcdAddress++)
    {
        if(pucV[usDpcdAddress] != pData[usDpcdAddress])
        {
            return _FALSE;
        }
    }

    // Write LSB of V
    if(ScalerDpAuxTxNativeWrite(0x06, 0x93, 0xE0, 16, &pucV[16]) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Content Stream Management
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2TxContentStreamManagement(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        return ScalerDpHdcp2TxContentStreamManagement_128b132b();
    }
    else
#endif
    {
        return ScalerDpHdcp2TxContentStreamManagement_8b10b();
    }
}

//--------------------------------------------------
// Description  : Content Stream Management
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2TxContentStreamManagement_8b10b(void)
{
    WORD usK = 0;
    BYTE pucStreamIDType[126] = {0};
    BYTE ucI = 0;
    WORD usDpcdAddress = 0;
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};

#if(_DP_MST_SUPPORT == _ON)
    EnumDpStreamSourceNum enumDpSourceTemp = _DP_NO_SOURCE;
    BYTE ucStreamId = 0;
#endif

    // Reset type value of Tx_STx(x = 1~4)
    ScalerSetBit(PBB_90_HDCP22_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
    // Reset type value of Tx_STx(x = 5~6)
    ScalerSetBit(PBB_95_HDCP22_ST_TYPE_CTRL, ~(_BIT1 | _BIT0), 0x00);
#endif

    // Clear Length of Daisy STx Encrypted Stream
    ScalerSetBit(PBB_6C_DP_STREAM_1_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PBB_6D_DP_STREAM_2_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PBB_6E_DP_STREAM_3_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_4_STREAM)
    ScalerSetBit(PBB_6F_DP_STREAM_4_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#elif(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
    ScalerSetBit(PBB_6F_DP_STREAM_4_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PBB_96_DP_STREAM_5_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PBB_97_DP_STREAM_6_PBN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if(_DP_MST_SUPPORT == _ON)
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
    {
        if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);
        }

        DebugMessageHDCP2("CSM - MST2MST", 0);

        for(enumDpSourceTemp = _DP_ST_SOURCE_DAISY_START; enumDpSourceTemp <= _DP_ST_SOURCE_DAISY_END; enumDpSourceTemp++)
        {
            if(ScalerDpMacTxGetDaisySourceMuxBackup(enumDpSourceTemp) != _DP_ST_NONE)
            {
                // Get Stream Source X Status
                ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(enumDpSourceTemp);

                // Get Stream IDx in STx
                pucStreamIDType[usK * 2] = GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(GET_DP_RX_MAIN_PORT(), ucStreamId);

                if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
                {
                    // Get Type of Stream IDx
                    pucStreamIDType[(usK * 2) + 1] = ScalerDpHdcp2RxGetStxType(ucStreamId);
                }
                else
                {
                    // Get Type of Stream IDx
                    pucStreamIDType[(usK * 2) + 1] = 0;
                }

                // Set Type of Tx_ST1
                ScalerSetBit(PBB_90_HDCP22_CTRL, ~(_BIT7 >> usK), (pucStreamIDType[(usK * 2) + 1] << (7 - usK)));

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
                if(usK > 3)
                {
                    // Set Type of Tx_ST5 ~ 6
                    ScalerSetBit(PBB_95_HDCP22_ST_TYPE_CTRL, ~(_BIT1 >> (usK - 4)), (pucStreamIDType[(usK * 2) + 1] << (5 - usK)));

                    // Set Length of ST5 ~ 6 Stream to Be Ready For Encryption
                    ScalerSetBit((PBB_96_DP_STREAM_5_PBN + usK - 4), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(ucStreamId));
                }
#endif

                DebugMessageHDCP2("CSM - STx Source", ucStreamId);
                DebugMessageHDCP2("CSM - STx Stream ID", pucStreamIDType[usK * 2]);
                DebugMessageHDCP2("CSM - TimeSlot Length", GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(ucStreamId));

                usK++;
            }
        }

        DebugMessageHDCP2("CSM - MST2SST Type", ScalerGetBit(PBB_90_HDCP22_CTRL, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3)));
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        usK = 1;

        // Get Stream IDx
        pucStreamIDType[0] = 0x00;

        if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

            // Get Stream Source X Status
            ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(_DP_ST_SOURCE1);

            // Get Type Value
            pucStreamIDType[1] = ScalerDpHdcp2RxGetStxType(ucStreamId);
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);

            // Set Type Value = 0 for HDCP1.3
            pucStreamIDType[1] = 0x00;
        }

        DebugMessageHDCP2("CSM - MST2SST", 0);

        if(pucStreamIDType[1] == 0x00)
        {
            // Set Type Value of Tx_ST1 as 0
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, 0x00);
        }
        else
        {
            // Set Type Value of Tx_ST1 as 1
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, _BIT7);
        }

        DebugMessageHDCP2("CSM - MST2SST Type", pucStreamIDType[1]);
    }
    else
#endif
    {
        usK = 1;

        // Get Stream IDx
        pucStreamIDType[0] = 0x00;

        if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

            // Get Type of Rx_ST1
            pucStreamIDType[1] = ScalerDpHdcp2TxGetUpstreamDpcdInfo(0x06, 0x93, 0xF6);
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);

            // Set Type = 00
            pucStreamIDType[1] = 0x00;
        }

        if(pucStreamIDType[1] == 0x00)
        {
            // Set Type Value of Tx_ST1 as 0
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, 0x00);
        }
        else
        {
            // Set Type Value of Tx_ST1 as 1
            ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, _BIT7);
        }

        DebugMessageHDCP2("CSM - SST2SST Type", pucStreamIDType[1]);
    }

    // Enable AES-Ctrl Cipher
    ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, _BIT1);

    // Write seq_num_M[23 : 0]
    pData[0] = LOBYTE(HIWORD(GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M()));
    pData[1] = HIBYTE(LOWORD(GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M()));
    pData[2] = LOBYTE(LOWORD(GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M()));
    ScalerDpAuxTxNativeWrite(0x06, 0x93, 0xF0, 3, pData);

    // Write k
    pData[0] = HIBYTE(usK);
    pData[1] = LOBYTE(usK);
    ScalerDpAuxTxNativeWrite(0x06, 0x93, 0xF3, 2, pData);

    // Initial DPCD Address of Stream ID Type
    usDpcdAddress = 0x93F5;

    // Initial Length of Stream ID Type
    ucI = 126;

    do
    {
        // Write StreamID_Type
        ScalerDpAuxTxNativeWrite(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), 16, &pucStreamIDType[abs(usDpcdAddress - 0x93F5)]);

        usDpcdAddress += 16;
        ucI -= 16;

        if(ucI <= 16)
        {
            // Write StreamID_Type
            ScalerDpAuxTxNativeWrite(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), ucI, &pucStreamIDType[abs(usDpcdAddress - 0x93F5)]);
        }
    }
    while(ucI > 16);

    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2TxdKey0);
    ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2TxdKey1);

    if(ScalerHdcp2MprimeCalculate(pucTemp1, pucTemp2, pucStreamIDType, GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M(), usK) == _FALSE)
    {
        return _FALSE;
    }

    // Get M
    memcpy(g_pucDpHdcp2TxM, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Timeout to Read M'
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxTimeoutToReadMPrimeEvent(void)
{
    SET_DP_HDCP2_TX_M_PRIME_TIMEOUT();
}

//--------------------------------------------------
// Description  : M Verification
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2TxVerifyMprime(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;

    // Read M' and Compare M' with M
    for(ucI = 0; ucI < 2; ucI++)
    {
        if(ScalerDpAuxTxNativeRead(0x06, 0x94, (0x73 + ucI * 16), 16, pData) == _FALSE)
        {
            return _FALSE;
        }

        for(ucJ = 0; ucJ < 16; ucJ++)
        {
            if(g_pucDpHdcp2TxM[16 * ucI + ucJ] != pData[ucJ])
            {
                DebugMessageHDCP2("CSM - M != M'", 16 * ucI + ucJ);

                return _FALSE;
            }
        }
    }

    DebugMessageHDCP2("CSM - M Pass", 0);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Content Stream Management Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxContentStreamManagementHandler(void)
{
    BYTE ucTypeValue = 0;
    WORD usKValue = 0;

#if(_DP_MST_SUPPORT == _ON)
    EnumDpStreamSourceNum enumStSourceTemp = _DP_NO_SOURCE;
    BYTE ucStreamId = 0;
#endif

    usKValue = usKValue;

    if((ScalerSyncDpHdcp2GetContentStreamManagementStatus() == _TRUE) && (GET_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT() == _FALSE))
    {
        CLR_DP_HDCP2_TX_STOP_CONTENT_STREAM();

        if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) &&
           (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE) &&
           (GET_DP_HDCP2_TX_AUTH_STATE() > _HDCP_2_2_TX_STATE_SKE))
        {
            DebugMessageHDCP2("CSM - DPTX HDCP22", 0);

            ScalerDpHdcp2TxEncryptSignalProc(_DISABLE);

            if(GET_DP_HDCP2_TX_REPEATER_SUPPORTED() == _TRUE)
            {
                DebugMessageHDCP2("CSM - DPTX RP ON", 0);

                if(ScalerDpHdcp2TxContentStreamManagement() == _TRUE)
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_M_PRIME);
                }
                else
                {
                    DebugMessageHDCP2("CSM - DPTX M Preset fail", 0);
                }
            }
            else
            {
                DebugMessageHDCP2("CSM - DPTX RP OFF", 0);

                if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
                {
                    DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

#if(_DP_MST_SUPPORT == _ON)
                    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
                    {
                        for(enumStSourceTemp = _DP_ST_SOURCE_DAISY_START; enumStSourceTemp <= _DP_ST_SOURCE_DAISY_END; enumStSourceTemp++)
                        {
                            if(ScalerDpMacTxGetDaisySourceMuxBackup(enumStSourceTemp) != _DP_ST_NONE)
                            {
                                // Get Stream Source X Status
                                ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(enumStSourceTemp);

                                // RX in MST Mode
                                ucTypeValue = ScalerDpHdcp2RxGetStxType(ucStreamId);

                                DebugMessageHDCP2("CSM - STx Source", ucStreamId);
                                DebugMessageHDCP2("CSM - MST2MST type", ucTypeValue);

                                break;
                            }
                        }
                    }
                    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
                    {
                        // Get Stream Source X Status
                        ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(_DP_ST_SOURCE1);

                        // RX in MST Mode
                        ucTypeValue = ScalerDpHdcp2RxGetStxType(ucStreamId);

                        DebugMessageHDCP2("CSM - MST2SST type", ucTypeValue);
                    }
                    else
#endif
                    {
                        // RX in SST Mode
                        ucTypeValue = (bit)ScalerDpHdcp2TxGetUpstreamDpcdInfo(0x06, 0x93, 0xF6);

                        DebugMessageHDCP2("CSM - SST2SST type", ucTypeValue);
                    }
                }
                else
                {
                    // Set Type Value = 0 when RX is HDCP1.3
                    ucTypeValue = 0x00;

                    DebugMessageHDCP2("CSM - HDCP13 to 22", 0x00);
                    DebugMessageHDCP2("CSM - type", ucTypeValue);
                }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
                {
                    // Ser Type of Tx_ST1
                    ScalerSetBit(P2B_68_HDCP22_CTRL0, ~(_BIT1 | _BIT0), ucTypeValue);

                    // Enable AES-Ctrl Cipher
                    ScalerSetBit(P2B_69_HDCP22_CTRL1, ~_BIT2, _BIT2);
                }
                else
#endif
                {
                    // Ser Type of Tx_ST1
                    ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT7, (ucTypeValue << 7));

                    // Enable AES-Ctrl Cipher
                    ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, _BIT1);
                }

                // Write Type Value to SST Sink
                ScalerDpAuxTxNativeWrite(0x06, 0x94, 0x94, 1, &ucTypeValue);

                // Set up 200ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA);
            }

            SET_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT();
        }
        else if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) &&
                (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _FALSE) &&
                (GET_DP_HDCP2_TX_AUTH_STATE() > _HDCP_2_2_TX_STATE_SKE))
        {
            DebugMessageHDCP2("CSM - DPTX HDCP20", 0);

            // HDCP 2.0-compliant can't support content stream management
            ScalerDpHdcp2TxEncryptSignalProc(_DISABLE);


#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
            if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
            {
                // Reset type value of Tx_STx(x = 1~4)
                ScalerSetByte(P2B_68_HDCP22_CTRL0, 0x00);

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
                // Reset type value of Tx_STx(x = 5~6)
                ScalerSetBit(P2B_6B_HDCP22_CTRL3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
            }
            else
#endif
            {
                // Reset type value of Tx_STx(x = 1~4)
                ScalerSetBit(PBB_90_HDCP22_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
                // Reset type value of Tx_STx(x = 5~6)
                ScalerSetBit(PBB_95_HDCP22_ST_TYPE_CTRL, ~(_BIT1 | _BIT0), 0x00);
#endif
            }

            if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
            {
#if(_DP_MST_SUPPORT == _ON)
                if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
                {
                    usKValue = 0;
                    ucTypeValue = 0;

                    for(enumStSourceTemp = _DP_ST_SOURCE_DAISY_START; enumStSourceTemp <= _DP_ST_SOURCE_DAISY_END; enumStSourceTemp++)
                    {
                        if(ScalerDpMacTxGetDaisySourceMuxBackup(enumStSourceTemp) != _DP_ST_NONE)
                        {
                            // Get Stream Source X Status
                            ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(enumStSourceTemp);

                            // Check Type of Stream IDx
                            ucTypeValue = ucTypeValue + (BYTE)ScalerDpHdcp2RxGetStxType(ucStreamId);

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                            if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_8B10B)
#endif
                            {
#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
                                if(usKValue > 3)
                                {
                                    // Set Length of ST5 ~ 6 Stream to Be Ready For Encryption
                                    ScalerSetBit((PBB_96_DP_STREAM_5_PBN + usKValue - 4), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(ucStreamId));
                                }
#endif
                            }

                            usKValue++;
                        }
                    }

                    DebugMessageHDCP2("CSM - MST2MST type", ucTypeValue);
                }
                else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
                {
                    // Get Stream Source X Status
                    ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(_DP_ST_SOURCE1);

                    // RX in MST Mode
                    ucTypeValue = ScalerDpHdcp2RxGetStxType(ucStreamId);
                }
                else
#endif
                {
                    // RX in SST Mode
                    ucTypeValue = ScalerDpHdcp2TxGetUpstreamDpcdInfo(0x06, 0x93, 0xF6);
                }
            }
            else
            {
                // Set Type Value = 0 when RX is HDCP1.3
                ucTypeValue = 0x00;
            }

            if(ucTypeValue == 0x00)
            {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
                {
                    // Enable AES-Ctrl Cipher
                    ScalerSetBit(P2B_69_HDCP22_CTRL1, ~_BIT2, _BIT2);
                }
                else
#endif
                {
                    // Enable AES-Ctrl Cipher
                    ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, _BIT1);
                }

                // Set up 200ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA);
            }
            else
            {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
                {
                    // Disable AES-Ctrl Cipher
                    ScalerSetBit(P2B_69_HDCP22_CTRL1, ~_BIT2, 0x00);
                }
                else
#endif
                {
                    // Disable AES-Ctrl Cipher
                    ScalerSetBit(PBB_90_HDCP22_CTRL, ~_BIT1, 0x00);
                }

                DebugMessageHDCP2("HDCP 2.0 must not be received stream with Type = 1", 0);

                SET_DP_HDCP2_TX_STOP_CONTENT_STREAM();
            }

            SET_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT();
        }
        else if((ScalerSyncDpGetHdcpModeStatus() == _HDCP_22) &&
                (GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _FALSE) &&
                (GET_DP_TX_HDCP_AUTH_STATE() >= _DP_TX_HDCP_STATE_AUTH_2))
        {
            DebugMessageHDCP2("CSM - DPTX HDCP 1x", 0);

#if(_DP_MST_SUPPORT == _ON)
            // HDCP 1.x-compliant can't support content stream management
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
            {
                usKValue = 0;
                ucTypeValue = 0;

                for(enumStSourceTemp = _DP_ST_SOURCE_DAISY_START; enumStSourceTemp <= _DP_ST_SOURCE_DAISY_END; enumStSourceTemp++)
                {
                    if(ScalerDpMacTxGetDaisySourceMuxBackup(enumStSourceTemp) != _DP_ST_NONE)
                    {
                        // Get Stream Source X Status
                        ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(enumStSourceTemp);

                        // Check Type of Stream IDx
                        ucTypeValue = ucTypeValue + (BYTE)ScalerDpHdcp2RxGetStxType(ucStreamId);

                        usKValue++;

                        // Max. Number of MST Stream can be transmitted by DPTX is 3
                        if(usKValue == 3)
                        {
                            break;
                        }
                    }
                }

                DebugMessageHDCP2("CSM - MST2MST type", ucTypeValue);
            }
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
            {
                // Get Stream Source X Status
                ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(_DP_ST_SOURCE1);

                // RX in MST Mode
                ucTypeValue = ScalerDpHdcp2RxGetStxType(ucStreamId);

                DebugMessageHDCP2("CSM - MST2SST type", ucTypeValue);
            }
            else
#endif
            {
                // RX in SST Mode
                ucTypeValue = ScalerDpHdcp2TxGetUpstreamDpcdInfo(0x06, 0x93, 0xF6);

                DebugMessageHDCP2("CSM - SST2SST type", ucTypeValue);
            }

            if(ucTypeValue != 0x00)
            {
                DebugMessageHDCP2("HDCP 1.x must not be received stream with Type = 1", 0);

                SET_DP_HDCP2_TX_STOP_CONTENT_STREAM();
            }

            SET_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT();
        }
    }

    if(GET_DP_HDCP2_TX_M_PRIME_TIMEOUT() == _TRUE)
    {
        CLR_DP_HDCP2_TX_M_PRIME_TIMEOUT();

        if(GET_DP_HDCP2_TX_AUTH_STATE() > _HDCP_2_2_TX_STATE_SKE)
        {
            if(ScalerDpHdcp2TxVerifyMprime() == _TRUE)
            {
                // Set up 200ms Timer Event
                ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA);
            }
            else
            {
                DebugMessageHDCP2("CSM - DPTX M Verify fail", 0);

                // seq_num_M roll-over detected
                if(GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M() >= 0x00FFFFFF)
                {
                    ScalerDpHdcp2TxChangeAuthState(_HDCP_2_2_TX_STATE_IDLE);
                }
                else
                {
                    ADD_DP_HDCP2_TX_SEQUENCE_NUMBER_M();

                    CLR_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT();
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Content Stream Management Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxOutputContentStreamHandler(void)
{
    if((ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE) &&
       (GET_DP_HDCP2_TX_STOP_CONTENT_STREAM() == _TRUE))
    {
        if(GET_DP_HDCP2_TX_BACKUP_CONTENT_STREAM() == _FALSE)
        {
            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
            {
                // Main Link switch to IDLE Pattern
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_IDLE_PATTERN);

                SET_DP_HDCP2_TX_BACKUP_CONTENT_STREAM();

                DebugMessageHDCP2("CSM - Back up Clone", 0);
            }
#if(_DP_MST_SUPPORT == _ON)
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
            {
                // Main Link switch to IDLE Pattern
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_IDLE_PATTERN);

                SET_DP_HDCP2_TX_BACKUP_CONTENT_STREAM();

                DebugMessageHDCP2("CSM - Back up MST2SST", 0);
            }
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
            {
                // Backup TimeSlot Info of Daisy Chain
                memcpy(g_pucDpHdcp2TxMstTimeSlotBackup, (volatile BYTE xdata *)PA_06_DAISY_CTRL_1, 6);

                // Clear TimeSlot Info of Daisy Chain
                memset((volatile BYTE xdata *)PA_06_DAISY_CTRL_1, 0, 6);

                // Double Buffer by ACT
                SET_DP_MAC_TX_REG_SEND_ACT_ENABLE();

                // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
                ScalerTimerDelayXms(2);

                SET_DP_HDCP2_TX_BACKUP_CONTENT_STREAM();

                DebugMessageHDCP2("CSM - Back up MST", 0);
            }
#endif
        }
    }
    else
    {
        if(GET_DP_HDCP2_TX_BACKUP_CONTENT_STREAM() == _TRUE)
        {
            DebugMessageHDCP2("CSM - Restore Stream", 0);

            if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
            {
                // Main Link switch to VIDEO pattern
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_VIDEO_PATTERN);


                DebugMessageHDCP2("CSM - Restore Clone", 0);
            }
#if(_DP_MST_SUPPORT == _ON)
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
            {
                // Main Link switch to VIDEO pattern
                ScalerDpMacTxMainLinkPatternSetting(_DP_TX_OUTPUT_VIDEO_PATTERN);

                DebugMessageHDCP2("CSM - Restore MST2SST", 0);
            }
            else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
            {
                // Restore TimeSlot Info of Daisy Chain
                memcpy((volatile BYTE xdata *)PA_06_DAISY_CTRL_1, g_pucDpHdcp2TxMstTimeSlotBackup, 6);

                // Clear Temp Timeslot Info
                memset(g_pucDpHdcp2TxMstTimeSlotBackup, 0, 6);

                // Double Buffer by ACT
                SET_DP_MAC_TX_REG_SEND_ACT_ENABLE();

                // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
                ScalerTimerDelayXms(2);

                DebugMessageHDCP2("CSM - Restore MST Timeslot", 0);
            }
#endif
            CLR_DP_HDCP2_TX_BACKUP_CONTENT_STREAM();
        }
    }
}

//--------------------------------------------------
// Description  : Enable HDCP2.2 TX Encryption
// Input Value  : _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp2TxEncryptSignalProc(bit bEnable)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        ScalerDpHdcp2TxEncryptSignalProc_128b132b(bEnable);
    }
    else
#endif
    {
        ScalerDpHdcp2TxEncryptSignalProc_8b10b(bEnable);
    }
}

//--------------------------------------------------
// Description  : Enable HDCP2.2 TX Encryption
// Input Value  : _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp2TxEncryptSignalProc_8b10b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_MST_SUPPORT == _ON)
        ScalerDpHdcp2TxSetECFProc_8b10b();
#endif

        // Enable HDCP Encryption
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable HDCP Encryption
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
            // Double Buffer by ACT
            SET_DP_MAC_TX_REG_SEND_ACT_ENABLE();

            // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
            ScalerTimerDelayXms(2);
        }

        // Set ECF by FW
        ScalerSetBit(PBB_64_HDCP_ECF_BYTE0, ~_BIT7, 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : Get TX HDCP2.2 Function Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2TxGetHdcpMode(void)
{
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        return (ScalerGetBit(P2B_48_DPTX_HDCP_CTRL1, _BIT0) == _BIT0);
    }
    else
#endif
    {
        return (ScalerGetBit(PBB_90_HDCP22_CTRL, _BIT0) == _BIT0);
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDCP2.2 TX ECF Encryption
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxSetECFProc_8b10b(void)
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
// Description  : Get HDCP2 DPCD Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpHdcp2TxGetUpstreamDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    switch(GET_DP_RX_HDCP2_UPSTREAM_PORT())
    {
        case _HDCP_D0_PORT:

            return ScalerDpAuxRxGetDpcdInfo(_D0_INPUT_PORT, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);

        case _HDCP_D1_PORT:

            return ScalerDpAuxRxGetDpcdInfo(_D1_INPUT_PORT, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);

        case _HDCP_D2_PORT:

            return ScalerDpAuxRxGetDpcdInfo(_D2_INPUT_PORT, ucDpcdAccessPortH, ucDpcdAccessPortM, ucDpcdAccessPortL);

        default:

            break;
    }

    return _FALSE;
}

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Content Stream Management
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2TxContentStreamManagement_128b132b(void)
{
    WORD usK = 0;
    BYTE pucStreamIDType[126] = {0};
    BYTE ucI = 0;
    BYTE ucStreamId = 0;
    WORD usDpcdAddress = 0;
    BYTE ucStSourceTemp = 0;
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};

    ucStSourceTemp = ucStSourceTemp;
    ucStreamId = ucStreamId;

    // Reset type value of Tx_STx(x = 1~4)
    ScalerSetByte(P2B_68_HDCP22_CTRL0, 0x00);

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
    // Reset type value of Tx_STx(x = 5~6)
    ScalerSetBit(P2B_6B_HDCP22_CTRL3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

#if(_DP_MST_SUPPORT == _ON)
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST)
    {
        if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);
        }

        DebugMessageHDCP2("CSM - MST2MST", 0);

        for(ucStSourceTemp = _DP_ST_SOURCE_DAISY_START; ucStSourceTemp <= _DP_ST_SOURCE_DAISY_END; ucStSourceTemp++)
        {
            if(ScalerDpMacTxGetDaisySourceMuxBackup(ucStSourceTemp) != _DP_ST_NONE)
            {
                // Get Stream Source X Status
                ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(ucStSourceTemp);

                // Get Stream IDx in STx
                pucStreamIDType[usK * 2] = GET_DP_MAC_DPHY_RX_STREAM_TO_ID_MAPPING(GET_DP_RX_MAIN_PORT(), ucStreamId);

                if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
                {
                    // Get Type of Stream IDx
                    pucStreamIDType[(usK * 2) + 1] = ScalerDpHdcp2RxGetStxType(ucStreamId);
                }
                else
                {
                    // Get Type of Stream IDx
                    pucStreamIDType[(usK * 2) + 1] = 0;
                }

                // Set AES Type of Tx_ST1 ~ 4
                ScalerSetBit(P2B_68_HDCP22_CTRL0, ~(_BIT0 << (usK * 2)), (pucStreamIDType[(usK * 2) + 1] << (usK * 2)));

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
                if(usK > 3)
                {
                    // Set AES Type of Tx_ST5 ~ 6
                    ScalerSetBit(P2B_6B_HDCP22_CTRL3, ~(_BIT0 << ((usK - 4) * 2)), (pucStreamIDType[(usK * 2) + 1] << ((usK - 4) * 2)));
                }
#endif

                DebugMessageHDCP2("CSM - STx Source", ucStreamId);
                DebugMessageHDCP2("CSM - STx Stream ID", pucStreamIDType[usK * 2]);
                DebugMessageHDCP2("CSM - STx Type of Stream ID", pucStreamIDType[(usK * 2) + 1]);
                DebugMessageHDCP2("CSM - TimeSlot Length", GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(ucStreamId));

                usK++;
            }
        }
    }
    else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        usK = 1;

        // Get Stream IDx
        pucStreamIDType[0] = 0x00;

        if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

            // Get Stream Source X Status
            ucStreamId = ScalerDpMacTxGetDaisySourceMuxBackup(_DP_ST_SOURCE1);

            // Get Type Value
            pucStreamIDType[1] = ScalerDpHdcp2RxGetStxType(ucStreamId);
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);

            // Set Type Value = 0 for HDCP1.3
            pucStreamIDType[1] = 0x00;
        }

        DebugMessageHDCP2("CSM - MST2SST", 0);

        if(pucStreamIDType[1] == 0x00)
        {
            // Set Type Value of Tx_ST1 as 0
            ScalerSetBit(P2B_68_HDCP22_CTRL0, ~(_BIT1 | _BIT0), 0x00);
        }
        else
        {
            // Set Type Value of Tx_ST1 as 1
            ScalerSetBit(P2B_68_HDCP22_CTRL0, ~(_BIT1 | _BIT0), _BIT0);
        }

        DebugMessageHDCP2("CSM - MST2SST Type", pucStreamIDType[1]);
    }
    else
#endif
    {
        usK = 1;

        // Get Stream IDx
        pucStreamIDType[0] = 0x00;

        if(ScalerSyncDpGetHdcpModeStatus() == _HDCP_22)
        {
            DebugMessageHDCP2("CSM - HDCP22 to 22", 0);

            // Get Type of Rx_ST1
            pucStreamIDType[1] = ScalerDpHdcp2TxGetUpstreamDpcdInfo(0x06, 0x93, 0xF6);
        }
        else
        {
            DebugMessageHDCP2("CSM - HDCP13 to 22", 0);

            // Set Type = 00
            pucStreamIDType[1] = 0x00;
        }

        if(pucStreamIDType[1] == 0x00)
        {
            // Set Type Value of Tx_ST1 as 0
            ScalerSetBit(P2B_68_HDCP22_CTRL0, ~(_BIT1 | _BIT0), 0x00);
        }
        else
        {
            // Set Type Value of Tx_ST1 as 1
            ScalerSetBit(P2B_68_HDCP22_CTRL0, ~(_BIT1 | _BIT0), _BIT0);
        }

        DebugMessageHDCP2("CSM - SST2SST Type", pucStreamIDType[1]);
    }

    // Enable AES-Ctrl Cipher
    ScalerSetBit(P2B_69_HDCP22_CTRL1, ~_BIT2, _BIT2);

    // Write seq_num_M[23 : 0]
    pData[0] = LOBYTE(HIWORD(GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M()));
    pData[1] = HIBYTE(LOWORD(GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M()));
    pData[2] = LOBYTE(LOWORD(GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M()));
    ScalerDpAuxTxNativeWrite(0x06, 0x93, 0xF0, 3, pData);

    // Write k
    pData[0] = HIBYTE(usK);
    pData[1] = LOBYTE(usK);
    ScalerDpAuxTxNativeWrite(0x06, 0x93, 0xF3, 2, pData);

    // Initial DPCD Address of Stream ID Type
    usDpcdAddress = 0x93F5;

    // Initial Length of Stream ID Type
    ucI = 126;

    do
    {
        // Write StreamID_Type
        ScalerDpAuxTxNativeWrite(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), 16, &pucStreamIDType[abs(usDpcdAddress - 0x93F5)]);

        usDpcdAddress += 16;
        ucI -= 16;

        if(ucI <= 16)
        {
            // Write StreamID_Type
            ScalerDpAuxTxNativeWrite(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), ucI, &pucStreamIDType[abs(usDpcdAddress - 0x93F5)]);
        }
    }
    while(ucI > 16);

    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2TxdKey0);
    ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2TxdKey1);

    if(ScalerHdcp2MprimeCalculate(pucTemp1, pucTemp2, pucStreamIDType, GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M(), usK) == _FALSE)
    {
        return _FALSE;
    }

    // Get M
    memcpy(g_pucDpHdcp2TxM, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Enable HDCP2.2 TX Encryption
// Input Value  : _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerDpHdcp2TxEncryptSignalProc_128b132b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_DP_MST_SUPPORT == _ON)
        ScalerDpHdcp2TxSetECFProc_128b132b();
#endif

        // Enable HDCP Encryption
        ScalerSetBit(P2B_48_DPTX_HDCP_CTRL1, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable HDCP Encryption
        ScalerSetBit(P2B_48_DPTX_HDCP_CTRL1, ~_BIT1, 0x00);

#if(_DP_MST_SUPPORT == _ON)
        // Disable MST ST3/ST4/ST5 Stream Encryption
        ScalerSetBit(P2B_54_DP_STREAM_ENC_CTL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_4_STREAM)
        // Disable MST ST6 Stream Encryption
        ScalerSetBit(P2B_54_DP_STREAM_ENC_CTL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#elif(_HW_DP_MST_DAISY_ST_NUM_MAX == _DP_MST_6_STREAM)
        // Disable MST ST6/ST7/ST8 Stream Encryption
        ScalerSetBit(P2B_54_DP_STREAM_ENC_CTL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

        // Output MST type
        if(GET_DP_MST_TX_ENABLE() == _TRUE)
        {
            // Double Buffer by ACT
            SET_DP_MAC_TX_REG_SEND_ACT_ENABLE();

            // more than (1024 MTP + 5 MTP) x 64 timeslot, unit: link clock
            ScalerTimerDelayXms(2);
        }

        // Set ECF by FW
        ScalerSetBit(P2B_4B_HDCP_ECF_CTL, ~_BIT0, 0x00);
#endif
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDCP2.2 TX ECF Encryption
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2TxSetECFProc_128b132b(void)
{
    // Output MST type
    if(GET_DP_MST_TX_ENABLE() == _TRUE)
    {
        BYTE ucDaisyStreamCnt = 0;
        BYTE ucLoopIndex = 0;
        EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort = GET_DP_RX_HDCP_UPSTREAM_PORT();

        // Set ECF by HW and ECF ACT Mode
        ScalerSetBit(P2B_4B_HDCP_ECF_CTL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

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
            }

            // Check Rx Stream Status
            if(ScalerDpMacDphyRxHdcpStreamStatus(enumDpHdcpUpstreamPort, ScalerDpMacTxGetDaisySourceMuxBackup(ucDaisyStreamCnt)) == _TRUE)
            {
                if(ScalerDpMacDphyRxHdcpTimeSlotEncStatus(enumDpHdcpUpstreamPort, ucPresentRxStartPosition) == _TRUE)
                {
                    // Check Tx Stream Status
                    if(GET_DP_MAC_TX_DAISY_ST_STATUS_REG(ucDaisyStreamCnt) == _TRUE)
                    {
                        // Enable MST STX Stream Encryption
                        ScalerSetBit(P2B_54_DP_STREAM_ENC_CTL, ~(_BIT0 << ucShiftCnt), (_BIT0 << ucShiftCnt));

                        // Double Buffer ECF Value
                        ScalerSetBit(P2B_4B_HDCP_ECF_CTL, ~_BIT2, _BIT2);
                    }
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
#endif
#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
