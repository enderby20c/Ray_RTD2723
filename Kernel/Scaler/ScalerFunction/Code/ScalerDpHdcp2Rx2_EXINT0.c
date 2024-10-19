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
// ID Code      : ScalerDpHdcp2Rx2_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp2Rx2/ScalerDpHdcp2Rx2.h"




#if((_DP_HDCP2_RX2_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 2.2 Int Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2Handler_EXINT0(void)
{
    BYTE ucMessageId = 0;
    BYTE ucIndex = 0;
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    BYTE pucTemp3[16] = {0};
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_EXINT0(_RX2);

    // DP Global IRQ Flag
    if(ScalerDpAuxRxGetGlobalIrq_EXINT0(enumInputPort) == _TRUE)
    {
        // Get HDCP2.2 Message ID
        ucMessageId = ScalerDpAuxRxHdcp2GetMessageID_EXINT0(enumInputPort);

        if(ucMessageId == _HDCP22_NONE)
        {
            return;
        }
        else
        {
            // Switch HDCP to 2.2 Module from 1.4 Module
            if(GET_DP_HDCP_RX2_HDCP_MODE() != _HDCP_22)
            {
                // Enable HDCP 2.2 Module
                ScalerDpHdcpRxSetHdcpMode_EXINT0(enumInputPort, _HDCP_22);
            }
        }

        switch(ucMessageId)
        {
            case _HDCP22_AKE_INIT:

                // HDCP2 Reset Proc
                ScalerDpHdcp2Rx2ResetProc_EXINT0();

                // Save Transmitter Rtx to FW (MSB located at index 0)
                ScalerDpHdcp2Rx2LoadDpcdValue_EXINT0(0x06, 0x90, 0x00, 8, g_pucDpHdcp2Rx2Rtx);

                // Save TxCaps to FW (MSB located at index 0)
                ScalerDpHdcp2Rx2LoadDpcdValue_EXINT0(0x06, 0x90, 0x08, 3, g_pucDpHdcp2Rx2TxCaps);

                // Generate the psudo-random key of Rrx
                ScalerHdcp2RxGenRrx_EXINT0(g_pucDpHdcp2Rx2Rrx);

                // Load Rrx to DPCD Table (MSB located at index 0)
                ScalerDpHdcp2Rx2SetDpcdReadValue_EXINT0(_HDCP22_RRX, g_pucDpHdcp2Rx2Rrx, 8);

                ScalerDpHdcp2Rx2CancelTimerEvent_EXINT0();

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT);

                // Execute AKE_INIT Procedure after 3msec
                ScalerTimerWDActivateTimerEvent_EXINT0(3, _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT);

                SET_DP_HDCP2_RX2_AKE_INIT_RECEIVED();

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
                SET_DP_HDCP2_RX2_HANDSHAKE_START();
#endif

                break;

            case _HDCP22_AKE_NO_STORED_KM:

                SET_DP_HDCP2_RX2_AKE_NO_STORED_KM_RECEIVED();
                SET_DP_HDCP2_RX2_AUTHENTICATION_ACTIVE();

                // If not clear (H' & Pairing Info) in WDINT in time, cancel the WD and clear it here;
                if(GET_DP_HDCP2_RX2_CLEAR_DPCD_READ_VALUE_DONE() == _FALSE)
                {
                    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT);

                    ScalerDpHdcp2Rx2ClearDpcdReadValue_EXINT0(_HDCP22_RX_H_PRIME, 32);
                    ScalerDpHdcp2Rx2ClearDpcdReadValue_EXINT0(_HDCP22_RX_PAIRING_INFO, 16);
                }

                break;

            case _HDCP22_AKE_SEND_PAIRING_INFO:

                // Start Pairing AES Calculate
                for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
                {
                    if(ucLoopIndex < 8)
                    {
                        g_pucHdcp2M[ucLoopIndex] = g_pucDpHdcp2Rx2Rtx[ucLoopIndex];
                    }
                    else
                    {
                        g_pucHdcp2M[ucLoopIndex] = g_pucDpHdcp2Rx2Rrx[ucLoopIndex - 8];
                    }
                }

                // AES Cipher Calculate Ekh[km]
                ScalerHdcp2Proc2_EXINT0(pucTemp1, g_pucHdcp2Kh);

                ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, pucTemp1);

                // Calculate Ekh[km] = kh AES m XOR Km
                ScalerHdcp2Proc2_EXINT0(pucTemp1, g_pucDpHdcp2Rx2Km);

                for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
                {
                    g_pucHdcp2EkhKm[ucLoopIndex] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + ucLoopIndex) ^ pucTemp1[ucLoopIndex];
                }

                // Load Ekh_km prime to DPCD Table
                for(ucIndex = 0; ucIndex < 16; ucIndex++)
                {
                    // DPCD [0x692E0 ~ 0x692EF]
                    ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x06, 0x92, (0xE0 + ucIndex), g_pucHdcp2EkhKm[ucIndex]);
                }

                // Doesn't Assert Pairing Available CPIRQ Before H Prime CPIRQ
                if(GET_DP_HDCP2_RX2_WAITING_H_PRIME_CPIRQ_ASSERTED() == _FALSE)
                {
                    // Set Pairing Available Flag
                    ScalerDpAuxRxCpIRQ_EXINT0(_DP_HDCP2_PARING_AVAILABLE, enumInputPort);
                }
                else
                {
                    // Recoed Pairing Available CPIRQ Asserted Sataus
                    SET_DP_HDCP2_RX2_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED();
                }

                break;

            case _HDCP22_AKE_STORED_KM:

                // If not clear H' in WDINT in time, cancel the WD and clear it here;
                if(GET_DP_HDCP2_RX2_CLEAR_DPCD_READ_VALUE_DONE() == _FALSE)
                {
                    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT);

                    ScalerDpHdcp2Rx2ClearDpcdReadValue_EXINT0(_HDCP22_RX_H_PRIME, 32);
                }

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_H_PRIME);

                // Execute H' Procedure after 4msec
                ScalerTimerWDActivateTimerEvent_EXINT0(4, _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_H_PRIME);

                break;

            case _HDCP22_LC_INIT:

                // Save Transmitter Rn to FW
                ScalerDpHdcp2Rx2LoadDpcdValue_EXINT0(0x06, 0x92, 0xF0, 8, g_pucDpHdcp2Rx2Rn);

                ScalerHdcp2Proc2_EXINT0(pucTemp2, g_pucDpHdcp2Rx2dKey0);
                ScalerHdcp2Proc2_EXINT0(pucTemp3, g_pucDpHdcp2Rx2dKey1);

                // If not clear L' in WDINT in time, cancel the WD and clear it here;
                if(GET_DP_HDCP2_RX2_CLEAR_DPCD_READ_VALUE_DONE() == _FALSE)
                {
                    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT);

                    ScalerDpHdcp2Rx2ClearDpcdReadValue_EXINT0(_HDCP22_RX_L_PRIME, 32);
                }

                if(ScalerHdcp2LPrimeCalculate_EXINT0(pucTemp2, pucTemp3, g_pucDpHdcp2Rx2Rrx, g_pucDpHdcp2Rx2Rn) == _TRUE)
                {
                    // Load L prime to g_pucHdcp2Sha256
                    for(BYTE ucLoopIndex = 0; ucLoopIndex < 32; ucLoopIndex++)
                    {
                        g_pucHdcp2Sha256[ucLoopIndex] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + ucLoopIndex);
                    }

                    // Load L prime to DPCD Table
                    ScalerDpHdcp2Rx2SetDpcdReadValue_EXINT0(_HDCP22_RX_L_PRIME, g_pucHdcp2Sha256, 32);
                }

                SET_DP_HDCP2_RX2_LC_INIT_RECEIVED();

                break;

            case _HDCP22_SKE_SEND_EKS:

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_SKE);

                // Execute Ske_Send_Eks Procedure after 4msec
                ScalerTimerWDActivateTimerEvent_EXINT0(4, _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_SKE);

                break;

            case _HDCP22_SKE_TYPE_VALUE:

                // Set AES Type
                ScalerDpMacDphyRxHdcp2SetAESType_EXINT0(enumInputPort);

                break;

            case _HDCP22_REPEATERAUTH_STREAM_MANAGE:

#if(_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON)
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_M_PRIME);

                // Enable Read M Prime(69473h) Force Defer
                ScalerDpAuxRxSetMPrimeReadDefer_EXINT0(enumInputPort, _ENABLE);

                // Calculate M' Value after 4msec
                ScalerTimerWDActivateTimerEvent_EXINT0(4, _SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_M_PRIME);

                // If not clear M' in WDINT in time, cancel the WD and clear it here;
                if(GET_DP_HDCP2_RX2_CLEAR_DPCD_READ_VALUE_DONE() == _FALSE)
                {
                    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT);

                    ScalerDpHdcp2Rx2ClearDpcdReadValue_EXINT0(_HDCP22_RX_M_PRIME, 32);
                }
#endif

                break;

            default:
                break;
        }
    }
}
//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Value in INT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                usLength == > Length,
//                pReadArray == > Key Array
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2LoadDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray)
{
    BYTE ucIndex = 0x00;
    WORD usDpcdAddress = 0;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_EXINT0(_RX2);

    usDpcdAddress = (((WORD)ucDpcdAccessPortM << 8) | ((WORD)ucDpcdAccessPortL));

    // Load Value To FW
    for(ucIndex = 0; ucIndex < ucLength; ucIndex++)
    {
        pucReadArray[ucIndex] = ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, ucDpcdAccessPortH, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress));

        usDpcdAddress = usDpcdAddress + 1;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2ResetProc_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_EXINT0(_RX2);

    // Reset for Hdcp 2.2 Block of Mac
    ScalerDpMacDphyRxHdcp2ResetProc_EXINT0(enumInputPort);

    // Reset for Hdcp 2.2 Type Value
    ScalerDpAuxRxHdcp2TypeValueReset_EXINT0(enumInputPort);

#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
    // Reset for Hdcp 2.2 StreamID Type Value
    ScalerDpAuxRxHdcp2StreamIDTypeReset_EXINT0(enumInputPort);
#endif

    // Clear HDCP2 Backup Info
    ScalerDpMacDphyRxClrHdcp2CipherBackupInfo(enumInputPort);

    // Disable Read M Prime(69473h) Force Defer
    ScalerDpAuxRxSetMPrimeReadDefer_EXINT0(enumInputPort, _DISABLE);

    // Clear RxStatus REAUTH_REQ and Link Intergrity Failure for HDCP 2.2
    ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x06, 0x94, 0x93, (ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x06, 0x94, 0x93) & 0xE0));

    // Clear Bstatus REAUTH_REQ and Link Intergrity Failure for HDCP 1.4
    ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x06, 0x80, 0x29, (ScalerDpAuxRxGetDpcdInfo_EXINT0(enumInputPort, 0x06, 0x80, 0x29) & 0xF0));

    CLR_DP_HDCP2_RX2_AUTHENTICATION_DONE();
    CLR_DP_HDCP2_RX2_AKE_INIT_RECEIVED();
    CLR_DP_HDCP2_RX2_AKE_NO_STORED_KM_RECEIVED();
    CLR_DP_HDCP2_RX2_AKE_NO_STORED_KM_DONE();
    CLR_DP_HDCP2_RX2_AKE_STORED_KM_RECEIVED();
    CLR_DP_HDCP2_RX2_LC_INIT_RECEIVED();
    CLR_DP_HDCP2_RX2_SKE_SEND_EKS_RECEIVED();
    CLR_DP_HDCP2_RX2_AUTHENTICATION_ACTIVE();
    CLR_DP_HDCP2_RX2_CLEAR_DPCD_READ_VALUE_DONE();

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_HDCP2_RX2_REPEATER_AUTH_1_START();
    CLR_DP_HDCP2_RX2_REPEATER_AUTH_2_START();
#endif
}

//--------------------------------------------------
// Description  : Download HDCP Receiver Public Key Certificate
// Input Value  : Public Key / Write Length
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2SetDpcdReadValue_EXINT0(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength)
{
    BYTE ucIndex = 0x00;
    WORD usDpcdAddress = 0;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_EXINT0(_RX2);

    switch(ucRSAType)
    {
        case _HDCP22_RRX:
            usDpcdAddress = 0x9215;
            break;

        case _HDCP22_RX_H_PRIME:
            usDpcdAddress = 0x92C0;
            break;

        case _HDCP22_RX_L_PRIME:
            usDpcdAddress = 0x92F8;
            break;

        case _HDCP22_RX_M_PRIME:
            usDpcdAddress = 0x9473;
            break;

        default:

            return;
    }

    for(ucIndex = 0; ucIndex < usLength; ucIndex++)
    {
        // DPCD [IGNORE]
        ScalerDpAuxRxSetDpcdValue_EXINT0(enumInputPort, 0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), pucReadArray[ucIndex]);
        usDpcdAddress = usDpcdAddress + 1;
    }
}

//--------------------------------------------------
// Description  : Clear HDCP Receiver Public Key Certificate
// Input Value  : Public Key / Write Length
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2ClearDpcdReadValue_EXINT0(BYTE ucRSAType, WORD usLength)
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

    ScalerDpAuxRx2DpcdGroupReset_EXINT0(0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), usLength);
}

//--------------------------------------------------
// Description  : Cancel Timer Event for HDCP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2CancelTimerEvent_EXINT0(void)
{
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_H_PRIME);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_SKE);

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_HDCP2_RX2_REAUTH_LONG_HPD_EXINT();

    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_M_PRIME);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_DP_HDCP2_RX2_AKE_INIT);
#endif
}
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
