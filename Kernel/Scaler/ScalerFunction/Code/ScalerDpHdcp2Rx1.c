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
// ID Code      : ScalerDpHdcp2Rx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp2Rx1/ScalerDpHdcp2Rx1.h"


#if((_DP_HDCP2_RX1_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
//----------------------------------------------------------------------------
// Global Variables (XDATA) for Each Interface = 77 Bytes
//----------------------------------------------------------------------------
volatile BYTE g_ucDpHdcp2Rx1Ctrl0;
volatile BYTE g_ucDpHdcp2Rx1Ctrl1;
BYTE g_pucDpHdcp2Rx1dKey0[16];
BYTE g_pucDpHdcp2Rx1dKey1[16];
BYTE g_pucDpHdcp2Rx1Km[16];
BYTE g_pucDpHdcp2Rx1Rtx[8];
BYTE g_pucDpHdcp2Rx1TxCaps[3];
BYTE g_pucDpHdcp2Rx1Rn[8];
BYTE g_pucDpHdcp2Rx1Rrx[8];
BYTE g_pucDpHdcp2Rx1VPrime[20];
BYTE g_pucDpHdcp2Rx1Caps[3];

#if(_DP_TX_SUPPORT == _ON)
volatile StructDpHdcp2RxAuthInfo g_stDpHdcp2Rx1AuthInfo;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process for DP Rx1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1Handler(void)
{
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    BYTE pucTemp3[16] = {0};

    // Receiver Has Received AKE_INIT
    if(GET_DP_HDCP2_RX1_AKE_INIT_RECEIVED() == _TRUE)
    {
        CLR_DP_HDCP2_RX1_AKE_INIT_RECEIVED();

#if(_DP_TX_SUPPORT == _ON)
        if(GET_DP_HDCP2_RX1_REPEATER_SUPPORT() == _TRUE)
        {
            SET_DP_HDCP2_RX1_REPEATER_AUTH_1_START();
        }

        // Clear DPCD Repeater Info
        ScalerDpHdcp2Rx1ClearDpcdRepeaterInfo();
#endif

        DebugMessageHDCP2("[D1]AKE_INIT", 0);
    }

    // Receiver Has received AKE_NO_STORED_KM
    if(GET_DP_HDCP2_RX1_AKE_NO_STORED_KM_RECEIVED() == _TRUE)
    {
        if(ScalerDpHdcp2Rx1CaptureKpubKm() == _TRUE)
        {
            // Decrypt Km by FW to Get 128 bit Km
            if(ScalerHdcp2RxRsaOaepCalculate(pucTemp1) == _TRUE)
            {
                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_0, g_pucDpHdcp2Rx1Rtx, g_pucDpHdcp2Rx1Rrx, pucTemp1, g_pucDpHdcp2Rx1Rn);

                memcpy(pucTemp2, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_1, g_pucDpHdcp2Rx1Rtx, g_pucDpHdcp2Rx1Rrx, pucTemp1, g_pucDpHdcp2Rx1Rn);

                memcpy(pucTemp3, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                ScalerHdcp2Proc2(g_pucDpHdcp2Rx1Km, pucTemp1);
                ScalerHdcp2Proc2(g_pucDpHdcp2Rx1dKey0, pucTemp2);
                ScalerHdcp2Proc2(g_pucDpHdcp2Rx1dKey1, pucTemp3);

                if(ScalerHdcp2HPrimeCalculate(pucTemp2, pucTemp3, g_pucDpHdcp2Rx1Rtx, g_pucDpHdcp2Rx1TxCaps, g_pucDpHdcp2Rx1Caps) == _TRUE)
                {
                    ScalerDpHdcp2Rx1CalculateKmKh();
                }
            }
        }
    }

    if(GET_DP_HDCP2_RX1_AKE_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_DP_HDCP2_RX1_AKE_STORED_KM_RECEIVED();

        DebugMessageHDCP2("[D1]AKE_STORED_KM", 0);
    }

    if(GET_DP_HDCP2_RX1_LC_INIT_RECEIVED() == _TRUE)
    {
        CLR_DP_HDCP2_RX1_LC_INIT_RECEIVED();

        DebugMessageHDCP2("[D1]LC_INIT", 0);
    }

    if(GET_DP_HDCP2_RX1_SKE_SEND_EKS_RECEIVED() == _TRUE)
    {
        CLR_DP_HDCP2_RX1_SKE_SEND_EKS_RECEIVED();

#if(_DP_TX_SUPPORT == _ON)
        if(GET_DP_HDCP2_RX1_REPEATER_SUPPORT() == _TRUE)
        {
            SET_DP_HDCP2_RX1_REPEATER_AUTH_2_START();
        }
#endif

        DebugMessageHDCP2("[D1]SKE_SEND_EKS", 0);
    }

    if(GET_DP_HDCP2_RX1_STREAM_MANAGE_RECEIVED() == _TRUE)
    {
        CLR_DP_HDCP2_RX1_STREAM_MANAGE_RECEIVED();

#if(_DP_TX_SUPPORT == _ON)
        SET_DP_HDCP2_RX1_CONTENT_STREAM_MANAGEMENT();
#endif
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1ResetProc(void)
{
    if(GET_DP_HDCP2_RX1_AUTHENTICATION_DONE() == _TRUE)
    {
        EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);

        // Reset for Hdcp 2.2 Block of Mac
        ScalerDpMacDphyRxHdcp2ResetProc(enumInputPort);

        // Reset for Hdcp 2.2 Type Value
        ScalerDpAuxRxHdcp2TypeValueReset(enumInputPort);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
        // Reset for Hdcp 2.2 StreamID Type Value
        ScalerDpAuxRxHdcp2StreamIDTypeReset(enumInputPort);
#endif

        // Disable Read M Prime(69473h) Force Defer
        ScalerDpAuxRxSetMPrimeReadDefer(enumInputPort, _DISABLE);

        // Clear RxStatus REAUTH_REQ
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x94, 0x93) & 0xE0));

        ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_AKE_INIT);

        ScalerDpHdcp2Rx1ClearDpcdReadValue(_HDCP22_RX_H_PRIME, 32);
        ScalerDpHdcp2Rx1ClearDpcdReadValue(_HDCP22_RX_L_PRIME, 32);
        ScalerDpHdcp2Rx1ClearDpcdReadValue(_HDCP22_RX_M_PRIME, 32);
        ScalerDpHdcp2Rx1ClearDpcdReadValue(_HDCP22_RX_PAIRING_INFO, 16);

        CLR_DP_HDCP2_RX1_AKE_INIT_RECEIVED();
        CLR_DP_HDCP2_RX1_AKE_NO_STORED_KM_RECEIVED();
        CLR_DP_HDCP2_RX1_AKE_STORED_KM_RECEIVED();
        CLR_DP_HDCP2_RX1_LC_INIT_RECEIVED();
        CLR_DP_HDCP2_RX1_SKE_SEND_EKS_RECEIVED();
        CLR_DP_HDCP2_RX1_AUTHENTICATION_ACTIVE();

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
        CLR_DP_HDCP2_RX1_HANDSHAKE_START();
#endif

#if(_DP_TX_SUPPORT == _ON)
        CLR_DP_HDCP2_RX1_REPEATER_AUTH_1_START();
        CLR_DP_HDCP2_RX1_REPEATER_AUTH_2_START();

        ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_IDLE);

        ScalerDpHdcp2Rx1ClearDpcdReadValue(_HDCP22_RX_V_PRIME, 190);
#endif
    }
}

//--------------------------------------------------
// Description  : Capture Kpub/Km
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2Rx1CaptureKpubKm(void)
{
    BYTE ucIndex = 0x00;
    BYTE pucKpubKm[128] = {0};
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);

    CLR_DP_HDCP2_RX1_AKE_NO_STORED_KM_RECEIVED();
    CLR_DP_HDCP2_RX1_AUTHENTICATION_ACTIVE();

    DebugMessageHDCP2("[D1]AKE_NO_STORED_KM", 0);

    // Save Transmitter Ekpub[km] to FW
    for(ucIndex = 0; ucIndex < 128; ucIndex++)
    {
        pucKpubKm[ucIndex] = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x92, (0x20 + ucIndex));
    }

    // Decrypt Ekpub[km]
    return (ScalerHdcp2RxRsaCalculate(pucKpubKm) == _TRUE);
}

//--------------------------------------------------
// Description  : Calculate Km/Kh
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1CalculateKmKh(void)
{
    BYTE ucIndex = 0x00;
    BYTE pucSHA256[32] = {0};
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE();

    // Load H prime to pucSHA256
    memcpy(pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    // Load H prime to DPCD Table
    for(ucIndex = 0; ucIndex < 32; ucIndex++)
    {
        // DPCD [0x692C0 ~ 0x692DF]
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x92, (0xC0 + ucIndex), pucSHA256[ucIndex]);
    }

    // Initialize Waiting To Assert H Prime_CPIRQ To Check if H' Is Read By Source Before CPIRQ With H Pirme Available Is Asserted
    SET_DP_HDCP2_RX1_WAITING_H_PRIME_CPIRQ_ASSERTED();

    // Initialize Pairing Available CPIRQ Flag To Record Pairing Available CPIRQ Asserted Status
    CLR_DP_HDCP2_RX1_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();

    SET_DP_HDCP2_RX1_AKE_NO_STORED_KM_DONE();

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }

    // Set H Prime Available Flag
    ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP2_H_PRIME_AVAILABLE);

    // Clear H Prime Available CPIRQ Status
    CLR_DP_HDCP2_RX1_WAITING_H_PRIME_CPIRQ_ASSERTED();

    // Assert Pairing Available CPIRQ If No Asserting in Pairing Info INT State
    if(GET_DP_HDCP2_RX1_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED() == _TRUE)
    {
        // Clear Pairing Available CPIRQ Status
        CLR_DP_HDCP2_RX1_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();

        // Set Pairing Available Flag
        ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP2_PARING_AVAILABLE);
    }
}

//--------------------------------------------------
// Description  : Cancel Timer Event for HDCP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1CancelTimerEvent(void)
{
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_H_PRIME);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_SKE);

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_HDCP2_RX1_REAUTH_LONG_HPD();

    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_M_PRIME);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX1_AKE_INIT);
#endif
}

//--------------------------------------------------
// Description  : Clear HDCP Receiver Public Key Certificate
// Input Value  : Public Key / Write Length
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1ClearDpcdReadValue(BYTE ucRSAType, WORD usLength)
{
    WORD usDpcdAddress = 0;

    switch(ucRSAType)
    {
        case _HDCP22_RRX:
            usDpcdAddress = 0x9215;
            break;

        case _HDCP22_RX_H_PRIME:
            usDpcdAddress = 0x92C0;
            break;

        case _HDCP22_RX_PAIRING_INFO:
            usDpcdAddress = 0x92E0;
            break;

        case _HDCP22_RX_L_PRIME:
            usDpcdAddress = 0x92F8;
            break;

        case _HDCP22_RX_M_PRIME:
            usDpcdAddress = 0x9473;
            break;

        case _HDCP22_RX_V_PRIME:
            usDpcdAddress = 0x9332;
            break;

        default:

            return;
    }

    ScalerDpAuxRx1DpcdGroupReset(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), usLength);
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1RepeaterHandler(void)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);

    if(ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_22)
    {
        if(GET_DP_HDCP2_RX1_CAPABLE_SUPPORT() == _TRUE)
        {
            if(GET_DP_HDCP2_RX1_REPEATER_SUPPORT() == _TRUE)
            {
                if(GET_DP_HDCP2_RX1_REPEATER_AUTH_1_START() == _TRUE)
                {
                    DebugMessageHDCP2("DPRX1 HDCP2 - Get AKE INIT", 0);

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP2_CPIRQ_EVENT);

                    CLR_DP_HDCP2_RX1_AUTH_CPIRQ_TIMRE();

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
                    ScalerDpHdcp14Rx1ChangeAuthState(_DP_RX_HDCP_STATE_IDLE);
#endif

                    ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_IDLE);
                }

                if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
                {
                    // For MST mode
                    if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
                    {
                        if((ScalerDpMacDphyRxHdcpCheckValid(enumInputPort) == _TRUE) && (GET_DP_HDCP2_RX1_AUTH_CPIRQ_TIMRE() == _FALSE))
                        {
                            if(ScalerDpMacDphyRxHdcpCheckLvp(enumInputPort) == _FALSE)
                            {
                                SET_DP_HDCP2_RX1_AUTH_CPIRQ_TIMRE();

                                ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

                                ScalerTimerActiveTimerEvent(SEC(0.02), _SCALER_TIMER_EVENT_DP_RX1_HDCP2_CPIRQ_EVENT);
                            }
                        }
                    }

                    if((ScalerDpHdcp2Rx1ReauthEventCheck() == _TRUE) && (GET_DP_HDCP2_RX1_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE))
                    {
                        if(GET_DP_HDCP2_RX1_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE)
                        {
                            ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_1);

                            SET_DP_HDCP2_RX1_REPEATER_DFP_REAUTH();
                        }
                        else
                        {
                            CLR_DP_HDCP2_RX1_REPEATER_DFP_REAUTH();

                            ScalerDpHdcp2Rx1ReAuthProcess(enumInputPort);
                        }
                    }
                }

                if((GET_DP_HDCP2_RX1_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE) && (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE))
                {
                    ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_IDLE);
                }
            }
        }
    }

    switch(GET_DP_HDCP2_RX1_AUTH_STATE())
    {
        case _DP_RX_HDCP2_REPEATER_STATE_IDLE:

            if(GET_DP_HDCP2_RX1_AUTH_STATE_CHANGE() == _TRUE)
            {
                // Clear Backup Table of ECF
                memset(g_pucDpHdcpRx1ECFBackup, 0, sizeof(g_pucDpHdcpRx1ECFBackup));

                CLR_DP_HDCP2_RX1_AUTH_STATE_CHANGE();
                CLR_DP_HDCP2_RX1_AUTH_REPEATER_PROC_TIMEOUT();
                CLR_DP_HDCP2_RX1_AUTH_CPIRQ_TIMRE();
                CLR_DP_HDCP2_RX1_CONTENT_STREAM_MANAGEMENT();
                CLR_DP_HDCP2_RX1_REPEATER_DFP_REAUTH();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT);

                SET_DP_HDCP2_RX1_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION);
            }

            if((ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_22) && (GET_DP_HDCP2_RX1_REPEATER_SUPPORT() == _TRUE))
            {
                if(GET_DP_HDCP2_RX1_REPEATER_AUTH_1_START() == _TRUE)
                {
                    CLR_DP_HDCP2_RX1_REPEATER_AUTH_1_START();

                    ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_1);
                }
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_1:

            if(GET_DP_HDCP2_RX1_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Auth 1", 0);

                CLR_DP_HDCP2_RX1_AUTH_STATE_CHANGE();

                if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
                {
                    // Check if downstream device support HDCP2 capability.
                    if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE))
                    {
                        DebugMessageHDCP2("DPRX1 HDCP2 - To DPTX HDCP2", 0);

                        // Issue event to make DPTX start HDCP2 handshake.
                        SET_DP_HDCP2_RX1_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_START_HANDSHAKE);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT);
                    }
                    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                    {
                        DebugMessageHDCP2("DPRX1 HDCP2 - To DPTX HDCP1", 0);

                        // Issue event to make DPTX start HDCP handshake.
                        SET_DP_HDCP14_RX1_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT);
                    }
                    else
                    {
                        CLR_DP_HDCP2_RX1_REPEATER_DFP_REAUTH();

                        ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_2);
                    }
                }
                else
                {
                    CLR_DP_HDCP2_RX1_REPEATER_DFP_REAUTH();

                    ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_FAKE);
                }
            }

            // Wait for downstream pass event or device/depth max event
            if((GET_DP_HDCP2_TX_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_HDCP2_TX_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX))
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - TX PASS", 0);

                CLR_DP_HDCP2_RX1_REPEATER_DFP_REAUTH();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT);

                ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_2);
            }
            else if(GET_DP_HDCP2_RX1_AUTH_REPEATER_PROC_TIMEOUT() == _TRUE)
            {
                CLR_DP_HDCP2_RX1_AUTH_REPEATER_PROC_TIMEOUT();

                if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE))
                {
                    SET_DP_HDCP2_RX1_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }
                else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                {
                    SET_DP_HDCP14_RX1_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }

                if(GET_DP_HDCP2_RX1_REPEATER_DFP_REAUTH() == _TRUE)
                {
                    CLR_DP_HDCP2_RX1_REPEATER_DFP_REAUTH();

                    ScalerDpHdcp2Rx1ReAuthProcess(enumInputPort);
                }

                ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_2:

            if(GET_DP_HDCP2_RX1_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Auth 2", 0);

                CLR_DP_HDCP2_RX1_AUTH_STATE_CHANGE();
            }

            if(GET_DP_HDCP2_RX1_REPEATER_AUTH_2_START() == _TRUE)
            {
                CLR_DP_HDCP2_RX1_REPEATER_AUTH_2_START();

                if(ScalerDpHdcp2Rx1CheckRxInfo() == _TRUE)
                {
                    ScalerDpHdcp2Rx1LoadReceiverIdList();

                    ScalerDpHdcp2Rx1VComputeProc();
                }

                DebugMessageHDCP2("DPRX1 HDCP2 - V Ready", 0);

                // Set V' Ready Bit and Issue CP_IRQ
                ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP2_V_READY);

                ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_FAKE:

            if(GET_DP_HDCP2_RX1_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Fake", 0);

                CLR_DP_HDCP2_RX1_AUTH_STATE_CHANGE();
            }

            if(GET_DP_HDCP2_RX1_REPEATER_AUTH_2_START() == _TRUE)
            {
                CLR_DP_HDCP2_RX1_REPEATER_AUTH_2_START();

                // Fake Authentication
                ScalerDpHdcp2Rx1FakeAuthenProc();

                // Set V' Ready Bit and Issue CP_IRQ
                ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP2_V_READY);

                ScalerDpHdcp2Rx1ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE:

            if(GET_DP_HDCP2_RX1_AUTH_STATE_CHANGE() == _TRUE)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Done", 0);

                CLR_DP_HDCP2_RX1_AUTH_STATE_CHANGE();
            }

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpHdcp2Rx1ChangeECFCheck();
#endif
            break;

        default:

            break;
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check HDCP ECF Change
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1ChangeECFCheck(void)
{
    bit bECFChanged = _FALSE;
    BYTE ucDaisyStreamCnt = 0;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);
    EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort = GET_DP_RX_HDCP2_UPSTREAM_PORT();

    if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT) && (GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT))
    {
        for(ucDaisyStreamCnt = 0; ucDaisyStreamCnt < _HW_DP_MST_DAISY_ST_NUM_MAX; ucDaisyStreamCnt++)
        {
            BYTE ucHdcpTimeSlotEncValue = ScalerDpMacDphyRxHdcpTimeSlotEncValue(enumInputPort, (ScalerGetByte(ScalerDpMacDphyRxStreamStartAddress(enumDpHdcpUpstreamPort, ucDaisyStreamCnt)) & 0x3F));

            if(ucHdcpTimeSlotEncValue != g_pucDpHdcpRx1ECFBackup[ucDaisyStreamCnt])
            {
                g_pucDpHdcpRx1ECFBackup[ucDaisyStreamCnt] = ucHdcpTimeSlotEncValue;

                bECFChanged = _TRUE;
            }
        }
    }

    if(bECFChanged == _TRUE)
    {
        if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE) && (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST))
        {
            // Issue event to inform DPTX HDCP ECF Changed.
            SET_DP_HDCP2_RX1_UPSTREAM_EVENT(_DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_ECF_CHANGE);
        }
        else
        {
            if((GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE) && (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST))
            {
                // Issue event to inform DPTX HDCP ECF Changed.
                SET_DP_HDCP14_RX1_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_ECF_CHANGE);
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Change HDCP2 Auth State
// Input Value  : Target HDCP2 Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1ChangeAuthState(EnumDpHdcp2RxRepeaterAuthState enumHdcp2AuthState)
{
    SET_DP_HDCP2_RX1_AUTH_STATE(enumHdcp2AuthState);
    SET_DP_HDCP2_RX1_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Set HDCP2 Repeater Proc Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1SetRepeaterProcTimeout(void)
{
    SET_DP_HDCP2_RX1_AUTH_REPEATER_PROC_TIMEOUT();
}

//--------------------------------------------------
// Description  : Check B info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2Rx1CheckRxInfo(void)
{
    BYTE pucRxInfo[2] = {0};
    BYTE ucRxInfoDevice = 0;
    BYTE ucRxInfoDepth = 0;
    bit bRxInfoDeviceExceed = _FALSE;
    bit bRxInfoDepthExceed = _FALSE;
    bit bRxInfoHdcp1Dowstream = _FALSE;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);

    if(GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE)
    {
        if(GET_DP_HDCP2_TX_REPEATER_SUPPORTED() == _TRUE)
        {
            if((GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED() == _TRUE) ||
               (GET_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED() == _TRUE))
            {
                bRxInfoDeviceExceed = (GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED() == _TRUE) ? _TRUE : _FALSE;
                bRxInfoDepthExceed = (GET_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED() == _TRUE) ? _TRUE : _FALSE;
            }
            else
            {
                ucRxInfoDevice = GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT();
                ucRxInfoDepth = GET_DP_HDCP2_TX_RXINFO_DEPTH();

                if(ucRxInfoDevice > 30)
                {
                    ucRxInfoDevice = 0x00;
                    bRxInfoDeviceExceed = _TRUE;
                }

                if(ucRxInfoDepth > 3)
                {
                    ucRxInfoDepth = 0x00;
                    bRxInfoDepthExceed = _TRUE;
                }
            }
        }

        if(bRxInfoDeviceExceed == _FALSE)
        {
            ucRxInfoDevice++;
        }

        bRxInfoHdcp1Dowstream = GET_DP_HDCP2_TX_RXINFO_HDCP1_DOWNSTREAM();
    }
    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            if((GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() > 30))
            {
                bRxInfoDeviceExceed = _TRUE;
            }
            else
            {
                ucRxInfoDevice = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT();
            }

            if((GET_DP_TX_HDCP_DOWNSTREAM_DEPTH_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEPTH() > 3))
            {
                bRxInfoDepthExceed = _TRUE;
            }
            else
            {
                ucRxInfoDepth = GET_DP_TX_HDCP_DOWNSTREAM_DEPTH();
            }
        }

        if(bRxInfoDeviceExceed == _FALSE)
        {
            ucRxInfoDevice++;
        }

        bRxInfoHdcp1Dowstream = _TRUE;
    }

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_INPUT_PORT() == enumInputPort))
    {
        if(bRxInfoDeviceExceed == _FALSE)
        {
            ucRxInfoDevice++;
        }
    }
#endif
#endif

    if(bRxInfoDepthExceed == _FALSE)
    {
        ucRxInfoDepth++;
    }

    pucRxInfo[0] = (ucRxInfoDepth << 1) | (ucRxInfoDevice >> 4);
    pucRxInfo[1] = (ucRxInfoDevice << 4) |
                   ((BYTE)bRxInfoDeviceExceed << 3) |
                   ((BYTE)bRxInfoDepthExceed << 2) |
                   ((BYTE)GET_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM() << 1) |
                   (bRxInfoHdcp1Dowstream);

    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, 0x30, pucRxInfo[0]);
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, 0x31, pucRxInfo[1]);

    if((bRxInfoDeviceExceed == _TRUE) || (bRxInfoDepthExceed == _TRUE))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Load Receiver ID List
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1LoadReceiverIdList(void)
{
    BYTE ucIndex = 0x00;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE();

    pData[0] = 0;

    if(GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE)
    {
        if(GET_DP_HDCP2_TX_REPEATER_SUPPORTED() == _TRUE)
        {
            pData[0] = GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT() * 5;
        }
        else
        {
            memset(g_pucDpHdcp2TxReceiverIdList, 0, sizeof(g_pucDpHdcp2TxReceiverIdList));
        }

        memcpy(&g_pucDpHdcp2TxReceiverIdList[pData[0]], g_pucDpHdcp2TxReceiverId, 5);
    }
    else if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            pData[0] = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() * 5;

            memcpy(g_pucDpHdcp2TxReceiverIdList, g_pucDpMacTxHdcpKsvFifo, pData[0]);
        }
        else
        {
            memset(g_pucDpHdcp2TxReceiverIdList, 0, sizeof(g_pucDpHdcp2TxReceiverIdList));
        }

        memcpy(&g_pucDpHdcp2TxReceiverIdList[pData[0]], (volatile BYTE xdata *)PBB_4F_BKSV_0, 5);
    }
    else
    {
        memset(g_pucDpHdcp2TxReceiverIdList, 0, sizeof(g_pucDpHdcp2TxReceiverIdList));
    }

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_INPUT_PORT() == enumInputPort))
    {
        if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE))
        {
            memcpy(&g_pucDpHdcp2TxReceiverIdList[(pData[0] + 1) * 5], g_stHdcp2RxDownLoadKeyType.pucHdcp2Certrx, 5);
        }
        else
        {
            memcpy(&g_pucDpHdcp2TxReceiverIdList, g_stHdcp2RxDownLoadKeyType.pucHdcp2Certrx, 5);
        }
    }
#endif
#endif

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    for(ucIndex = 0; ucIndex < 155; ucIndex++)
    {
        if(GET_DP_HDCP2_TX_RECEIVER_ID_LIST_MAX() > ucIndex)
        {
            // DPCD [0x69345 ~ 0x693DF]
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, (0x45 + ucIndex), g_pucDpHdcp2TxReceiverIdList[ucIndex]);
        }
        else
        {
            // DPCD [0x69345 ~ 0x693DF]
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, (0x45 + ucIndex), 0x00);
        }
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2Rx1VComputeProc(void)
{
    BYTE ucIndex = 0x00;
    BYTE pucRxInfo[2] = {0};
    BYTE pucSeqNumV[3] = {0};
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE();

    pucRxInfo[0] = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x30);
    pucRxInfo[1] = ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x93, 0x31);

    // Compute V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2Rx1dKey0);
    ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2Rx1dKey1);

    if(ScalerHdcp2VprimeCalculate(pucTemp1, pucTemp2, g_pucDpHdcp2TxReceiverIdList, pucRxInfo, pucSeqNumV) == _FALSE)
    {
        return _FALSE;
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    // Load MSB of V' into DPCD table
    for(ucIndex = 0; ucIndex < 3; ucIndex++)
    {
        // DPCD [0x69332 ~ 0x69334]
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, (0x32 + ucIndex), pucSeqNumV[ucIndex]);
    }

    // Load MSB of V' into DPCD table
    for(ucIndex = 0; ucIndex < 16; ucIndex++)
    {
        g_pucDpHdcp2Rx1VPrime[ucIndex] = ScalerGetByte(P63_35_HDCP_SHA_0 + ucIndex);

        // DPCD [0x69335 ~ 0x69344]
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, (0x35 + ucIndex), g_pucDpHdcp2Rx1VPrime[ucIndex]);
    }

    for(ucIndex = 16; ucIndex < 20; ucIndex++)
    {
        g_pucDpHdcp2Rx1VPrime[ucIndex] = ScalerGetByte(P63_35_HDCP_SHA_0 + ucIndex);
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Fake HDCP Authentication
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2Rx1FakeAuthenProc(void)
{
    BYTE ucIndex = 0x00;
    BYTE pucRxInfo[2] = {0};
    BYTE pucSeqNumV[3] = {0};
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX1_MODE();

    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, 0x30, pucRxInfo[0]);
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, 0x31, pucRxInfo[1]);

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    for(ucIndex = 0; ucIndex < 5; ucIndex++)
    {
        // DPCD [0x69345 ~ 0x69349]
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, (0x45 + ucIndex), g_pucSyncHdcpAksvBackup[ucIndex]);
    }

    // DPCD [0x6934A ~ 0x693DF]
    ScalerDpAuxRx1DpcdGroupReset(0x06, 0x93, 0x4A, 150);

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }

    // Compute V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    ScalerHdcp2Proc2(pucTemp1, g_pucDpHdcp2Rx1dKey0);
    ScalerHdcp2Proc2(pucTemp2, g_pucDpHdcp2Rx1dKey1);

    if(ScalerHdcp2VprimeCalculate(pucTemp1, pucTemp2, g_pucSyncHdcpAksvBackup, pucRxInfo, pucSeqNumV) == _FALSE)
    {
        return _FALSE;
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    // Load MSB of V' into DPCD table
    for(ucIndex = 0; ucIndex < 16; ucIndex++)
    {
        // DPCD [0x69335 ~ 0x69344]
        ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x93, (0x35 + ucIndex), ScalerGetByte(P63_35_HDCP_SHA_0 + ucIndex));
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Change DP HDCP2.2 Repeater Capable for Rx1 Base On DPTX Clone Status
// Input Value  : InputPort, PortType, Clone Mode or not
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1RepeaterSupportProc(void)
{
    bit bDPRx1Hdcp2SetRepeater = _OFF;
    EnumInputPort enumHdcpInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);

    if(GET_DP_HDCP2_RX1_CAPABLE_SUPPORT() == _FALSE)
    {
        return;
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() != _DP_UNPLUG)
    {
        if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
        {
            bDPRx1Hdcp2SetRepeater = _ON;
        }
    }

    if(bDPRx1Hdcp2SetRepeater != GET_DP_HDCP2_RX1_REPEATER_SUPPORT())
    {
        if(bDPRx1Hdcp2SetRepeater == _ON)
        {
            SET_DP_HDCP2_RX1_REPEATER_SUPPORT();
        }
        else
        {
            CLR_DP_HDCP2_RX1_REPEATER_SUPPORT();
        }

        switch(GET_DP_RX1_HOTPLUG_ASSERT_TYPE())
        {
            case _DP_HPD_NONE:

                if(!((ScalerDpHdcpRxGetHdcpMode(enumHdcpInputPort) == _HDCP_14) && (ScalerDpMacDphyRxHdcpDetectLvp(enumHdcpInputPort) == _TRUE)))
                {
#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
                    if(GET_DP_HDCP14_RX1_AUTH_STATE() == _DP_RX_HDCP_STATE_IDLE)
#endif
                    {
                        if(ScalerDpRxGetHotPlugStatus(enumHdcpInputPort) == _HIGH)
                        {
                            ScalerDpMacDphyRxCpIRQ(enumHdcpInputPort, _DP_HDCP2_RXSTATUS_REAUTH_REQ);
                        }
                    }
                }

                break;

            case _DP_HPD_ASSERTED:

                if(!((ScalerDpHdcpRxGetHdcpMode(enumHdcpInputPort) == _HDCP_14) && (ScalerDpMacDphyRxHdcpDetectLvp(enumHdcpInputPort) == _TRUE)))
                {
#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
                    if(GET_DP_HDCP14_RX1_AUTH_STATE() == _DP_RX_HDCP_STATE_IDLE)
#endif
                    {
                        if(ScalerDpRxGetHotPlugStatus(enumHdcpInputPort) == _HIGH)
                        {
                            ScalerDpMacDphyRxCpIRQ(enumHdcpInputPort, _DP_HDCP2_RXSTATUS_REAUTH_REQ);
                        }
                    }
                }

                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : HDCP2 Reauth Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp2Rx1ReauthEventCheck(void)
{
    BYTE ucReauth = 0;

    if((GET_DP_HDCP2_TX_CAPABLE_SUPPORTED() == _TRUE) && (GET_DP_HDCP2_TX_VERSION_SUPPORTED() == _TRUE))
    {
        if(GET_DP_HDCP2_TX_DOWNSTREAM_EVENT() == _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH)
        {
            DebugMessageHDCP2("DPRX1 HDCP2 - Get DPTX HDCP2 ReAuth Event", 0);

            ucReauth |= _BIT0;
        }
    }
    else
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
        {
            if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH)
            {
                DebugMessageHDCP2("DPRX1 HDCP2 - Get DPTX HDCP14 ReAuth Event", 0);

                ucReauth |= _BIT0;
            }
        }
    }

    if(ucReauth != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check DP Hdcp2 ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpHdcp2Rx1ReAuthStatusCheck(void)
{
    if(GET_DP_HDCP2_RX1_REAUTH_LONG_HPD() == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : HDCP ReAuth Process
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1ReAuthProcess(EnumInputPort enumInputPort)
{
    ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP2_RXSTATUS_REAUTH_REQ);

    // In SST mode, issue Long HPD Event caused by Reauth Event issued after 1 sec.
    // In MST mode, notify source by CPIRQ only. Don't issue long HPD.
    if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, (_BIT1 | _BIT0)) == 0x00) &&
       (GET_DP_HDCP2_RX1_AUTH_STATE() != _DP_RX_HDCP2_REPEATER_STATE_IDLE) &&
       (ScalerDpMacDphyRxHdcpCheckValid(enumInputPort) == _TRUE))
    {
        SET_DP_HDCP2_RX1_REAUTH_LONG_HPD();

        ScalerTimerReactiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_DP_RX1_HDCP2_LONG_HOTPLUG_EVENT);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx1ClearDpcdRepeaterInfo(void)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX1);

    // Clear HDCP2: seq_num_V, V', Receiver ID List
    ScalerDpHdcp2Rx1ClearDpcdReadValue(_HDCP22_RX_V_PRIME, 190);

    // Clear HDCP14: Bstatus, Binfo, V', KSV FIFO
    if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A) != 0x00) || (ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B) != 0x00))
    {
        // DPCD [0x68014 ~ 0x68027]
        ScalerDpAuxRx1DpcdGroupReset(0x06, 0x80, 0x14, 20);

        // DPCD [0x68029 ~ 0x6803A]
        ScalerDpAuxRx1DpcdGroupReset(0x06, 0x80, 0x29, 18);
    }
}

#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if((_DP_HDCP2_RX1_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
