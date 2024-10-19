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
// ID Code      : ScalerDpHdcp2Rx2_WDINT.c No.0000
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
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2SkeProc_WDINT(void)
{
    BYTE pucTemp1[16];
    BYTE pucTemp2[16];
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_WDINT(_RX2);

    if(GET_DP_HDCP2_RX2_AUTHENTICATION_DONE() == _TRUE)
    {
        // Disable HDCP2.2 Auth. Done
        ScalerDpMacDphyRxHdcp2EnableAuthDone_WDINT(_DISABLE, enumInputPort);

        CLR_DP_HDCP2_RX2_AUTHENTICATION_DONE();

        // Delay Time us [200, x]
        for(BYTE ucLoopIndex = 0; ucLoopIndex < 40; ucLoopIndex++)
        {
            DELAY_5US_EXINT();
        }
    }

    // Calculate Dkey 2
    ScalerHdcp2Proc2_WDINT(pucTemp1, g_pucDpHdcp2Rx2Km);

    ScalerDpHdcp2RxDkeyCalculate_WDINT(_HDCP_2_2_DKEY_2, g_pucDpHdcp2Rx2Rtx, g_pucDpHdcp2Rx2Rrx, pucTemp1, g_pucDpHdcp2Rx2Rn);

    // Save Edkey_ks to g_pucHdcp2EDkeyKs
    ScalerDpHdcp2Rx2LoadDpcdValue_WDINT(0x06, 0x93, 0x18, 16, g_pucHdcp2EDkeyKs);

    // Save Riv to g_pucHdcp2Riv
    ScalerDpHdcp2Rx2LoadDpcdValue_WDINT(0x06, 0x93, 0x28, 8, g_pucHdcp2Riv);

    // Decode Ks
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ++ucLoopIndex)
    {
        pucTemp2[ucLoopIndex] = g_pucHdcp2EDkeyKs[ucLoopIndex] ^ ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + ucLoopIndex));
    }

    for(BYTE ucLoopIndex = 8; ucLoopIndex < 16; ++ucLoopIndex)
    {
        pucTemp2[ucLoopIndex] = g_pucHdcp2EDkeyKs[ucLoopIndex] ^ (ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + ucLoopIndex)) ^ g_pucDpHdcp2Rx2Rrx[ucLoopIndex - 8]);
    }

    ScalerHdcp2Proc2_WDINT(g_pucHdcp2Ks, pucTemp2);

    // Enable DP Link Integrity Check
    ScalerDpMacDphyRxHdcp2EnableLinkIntegrityCheck_WDINT(_ENABLE, enumInputPort);

    // Enable Decryption
    ScalerDpMacDphyRxHdcp2EnableDecryption_WDINT(enumInputPort);

    // Solve Mute Issue For S8_TW Which Has Not Sent Type Value After SKE
    if(ScalerDpAuxRxGetDpcdBitInfo_WDINT(enumInputPort, 0x06, 0x92, 0x1F, (_BIT1 | _BIT0)) == _BIT1)
    {
        // Enable HDCP2.2 Auth. Done
        ScalerDpMacDphyRxHdcp2EnableAuthDone_WDINT(_ENABLE, enumInputPort);

        SET_DP_HDCP2_RX2_AUTHENTICATION_DONE();
    }

    SET_DP_HDCP2_RX2_SKE_SEND_EKS_RECEIVED();
}

//--------------------------------------------------
// Description  : As a part of Stored_km Proc, after Calculate Dkey
//                Split here to avoid taking too long time in EXINT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2HPrimeProc_WDINT(void)
{
    BYTE pucTemp1[16];
    BYTE pucTemp2[16];
    BYTE pucTemp3[16];
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_WDINT(_RX2);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus_WDINT(enumInputPort);

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode_WDINT(enumInputPort);
    }

    // Save m From Transmitter to FW
    ScalerDpHdcp2Rx2LoadDpcdValue_WDINT(0x06, 0x92, 0xB0, 16, g_pucHdcp2M);

    // Calculate Km use AES Cipher, Input Value = m, Input Cipher = Kh
    ScalerHdcp2Proc2_WDINT(pucTemp1, g_pucHdcp2Kh);

    ScalerHdcp2RxAesOfflineCtrl_WDINT(g_pucHdcp2M, pucTemp1);

    // Save Ekh[km] From Transmitter to FW
    ScalerDpHdcp2Rx2LoadDpcdValue_WDINT(0x06, 0x92, 0xA0, 16, pucTemp1);

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        pucTemp1[ucLoopIndex] = pucTemp1[ucLoopIndex] ^ ScalerGetByte_WDINT(P63_81_HDCP_AES_OUT_15 + ucLoopIndex);
    }

    // Calculate DKey0
    ScalerHdcp2DkeyCalculate_WDINT(_HDCP_2_2_DKEY_0, g_pucDpHdcp2Rx2Rtx, g_pucDpHdcp2Rx2Rrx, pucTemp1, g_pucDpHdcp2Rx2Rn);

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        pucTemp2[ucLoopIndex] = ScalerGetByte_WDINT(P63_81_HDCP_AES_OUT_15 + ucLoopIndex);
    }

    // Calculate Dkey1
    ScalerHdcp2DkeyCalculate_WDINT(_HDCP_2_2_DKEY_1, g_pucDpHdcp2Rx2Rtx, g_pucDpHdcp2Rx2Rrx, pucTemp1, g_pucDpHdcp2Rx2Rn);

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        pucTemp3[ucLoopIndex] = ScalerGetByte_WDINT(P63_81_HDCP_AES_OUT_15 + ucLoopIndex);
    }

    // Calculate H'
    if(ScalerHdcp2HPrimeCalculate_WDINT(pucTemp2, pucTemp3, g_pucDpHdcp2Rx2Rtx, g_pucDpHdcp2Rx2TxCaps, g_pucDpHdcp2Rx2Caps) == _TRUE)
    {
        for(BYTE ucLoopIndex = 0; ucLoopIndex < 32; ucLoopIndex++)
        {
            g_pucHdcp2Sha256[ucLoopIndex] = ScalerGetByte_WDINT(P63_35_HDCP_SHA_0 + ucLoopIndex);
        }

        // Load H prime to DPCD Table
        ScalerDpHdcp2Rx2SetDpcdReadValue_WDINT(_HDCP22_RX_H_PRIME, g_pucHdcp2Sha256, 32);
    }

    ScalerDpAuxRxCpIRQ_EXINT0(_DP_HDCP2_H_PRIME_AVAILABLE, enumInputPort);

    ScalerHdcp2Proc2_WDINT(g_pucDpHdcp2Rx2Km, pucTemp1);
    ScalerHdcp2Proc2_WDINT(g_pucDpHdcp2Rx2dKey0, pucTemp2);
    ScalerHdcp2Proc2_WDINT(g_pucDpHdcp2Rx2dKey1, pucTemp3);

    SET_DP_HDCP2_RX2_AKE_STORED_KM_RECEIVED();

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode_WDINT(enumInputPort);
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
void ScalerDpHdcp2Rx2LoadDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray)
{
    BYTE ucIndex = 0x00;
    WORD usDpcdAddress = 0;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_WDINT(_RX2);

    usDpcdAddress = (((WORD)ucDpcdAccessPortM << 8) | ((WORD)ucDpcdAccessPortL));

    // Load Value To FW
    for(ucIndex = 0; ucIndex < ucLength; ucIndex++)
    {
        pucReadArray[ucIndex] = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, ucDpcdAccessPortH, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress));

        usDpcdAddress = usDpcdAddress + 1;
    }
}

#if(_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2MPrimeProc_WDINT(void)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_WDINT(_RX2);

    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = ScalerDpAuxRxGetAuxModeStatus_WDINT(enumInputPort);

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode_WDINT(enumInputPort);
    }

    // Get M Prime
    if(ScalerDpHdcp2Rx2MPrimeCalculate_WDINT(enumInputPort) == _TRUE)
    {
        for(BYTE ucLoopIndex = 0; ucLoopIndex < 32; ucLoopIndex++)
        {
            g_pucHdcp2Sha256[ucLoopIndex] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + ucLoopIndex);
        }

        // Load M prime to DPCD Table
        ScalerDpHdcp2Rx2SetDpcdReadValue_WDINT(_HDCP22_RX_M_PRIME, g_pucHdcp2Sha256, 32);

        // Disable Read M Prime(69473h) Force Defer
        ScalerDpAuxRxSetMPrimeReadDefer_EXINT0(enumInputPort, _DISABLE);

        // Set AES Type
        ScalerDpMacDphyRxHdcp2SetRepeaterAESType_WDINT(enumInputPort);

        // Enable HDCP2.2 Auth. Done
        ScalerDpMacDphyRxHdcp2EnableAuthDone_WDINT(_ENABLE, enumInputPort);

        SET_DP_HDCP2_RX2_AUTHENTICATION_DONE();

        SET_DP_HDCP2_RX2_STREAM_MANAGE_RECEIVED();
    }

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode_WDINT(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Get M Prime
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpHdcp2Rx2MPrimeCalculate_WDINT(EnumInputPort enumInputPort)
{
    BYTE ucIndex = 0x00;
    BYTE ucStreamIdLength = 0x00;
    BYTE pucSHA256Input[64] = {0};
    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};

    // Get kd
    ScalerHdcp2Proc2_WDINT(pucTemp1, g_pucDpHdcp2Rx2dKey0);
    ScalerHdcp2Proc2_WDINT(pucTemp2, g_pucDpHdcp2Rx2dKey1);

    for(ucIndex = 0; ucIndex < 64; ucIndex++)
    {
        if(ucIndex < 16)
        {
            pucSHA256Input[ucIndex] = pucTemp1[ucIndex];
        }
        else if(ucIndex < 32)
        {
            pucSHA256Input[ucIndex] = pucTemp2[ucIndex - 16];
        }
        else
        {
            pucSHA256Input[ucIndex] = 0;
        }
    }

    pucSHA256Input[32] = 0x80;
    pucSHA256Input[62] = 0x01;

    // Get SHA256(kd)
    if(ScalerHdcp2RxSha256Calculate_WDINT(pucSHA256Input, 0) == _TRUE)
    {
        for(ucIndex = 0; ucIndex < 64; ucIndex++)
        {
            if(ucIndex < 32)
            {
                g_pucHdcp2HmacSha256CipherInput[ucIndex] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + ucIndex);
            }
            else
            {
                g_pucHdcp2HmacSha256CipherInput[ucIndex] = 0;
            }
        }
    }

    // Get # of StreamID_Type Length, StreamID_Type = stream_ID1 || Type || stream_ID2 || Type || .....
    ucStreamIdLength = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, 0xF4) * 2;

    // Stuff streamID_Type
    for(ucIndex = 0; ucIndex < ucStreamIdLength; ucIndex++)
    {
        g_pucHdcp2HmacSha256Input[ucIndex] = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, (0xF5 + ucIndex));
    }

    // Stuff seq_num_M
    for(ucIndex = 0; ucIndex < 3; ucIndex++)
    {
        g_pucHdcp2HmacSha256Input[ucStreamIdLength + ucIndex] = ScalerDpAuxRxGetDpcdInfo_WDINT(enumInputPort, 0x06, 0x93, (0xF0 + ucIndex));
    }

    g_pucHdcp2HmacSha256Input[ucStreamIdLength + 3] = 0x80;

    for(ucIndex = ucStreamIdLength + 4; ucIndex < 64; ucIndex++)
    {
        g_pucHdcp2HmacSha256Input[ucIndex] = 0;
    }

    // 8 * (StreamID_Type + seq_num_M + SHA256(kd))
    WORD usData = 8 * (ucStreamIdLength + 3 + 64);

    g_pucHdcp2HmacSha256Input[62] = HIBYTE(usData);
    g_pucHdcp2HmacSha256Input[63] = LOBYTE(usData);

    if(ScalerHdcp2RxHmacSha256Calculate_WDINT(g_pucHdcp2HmacSha256Input, g_pucHdcp2HmacSha256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif // End of #if(_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Download HDCP Receiver Public Key Certificate
// Input Value  : Public Key / Write Length
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2Rx2SetDpcdReadValue_WDINT(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength)
{
    BYTE ucIndex = 0x00;
    WORD usDpcdAddress = 0;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping_WDINT(_RX2);

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
        ScalerDpAuxRxSetDpcdValue_WDINT(enumInputPort, 0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), pucReadArray[ucIndex]);
        usDpcdAddress = usDpcdAddress + 1;
    }
}
#endif // End of #if((_DP_HDCP2_RX2_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
