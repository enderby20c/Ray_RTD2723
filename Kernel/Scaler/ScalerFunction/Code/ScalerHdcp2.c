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
// ID Code      : ScalerHdcp2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDCP2__

#include "ScalerFunctionInclude.h"
#include "Hdcp2/ScalerHdcp2.h"


#if(_HDCP_2_2_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
//----------------------------------------------------------------------------
// Rx Key = 1118 Bytes
//----------------------------------------------------------------------------
StructHdcp2DownLoadKeyType g_stHdcp2RxDownLoadKeyType;

//----------------------------------------------------------------------------
// Global Variables (XDATA) for All Interface Shared
//----------------------------------------------------------------------------
volatile BYTE g_ucHdcp2AuthActive;

BYTE g_pucHdcp2SHA256Input[64];
BYTE g_pucHdcp2HmacSha256Input[64];
BYTE g_pucHdcp2HmacSha256CipherInput[64];
BYTE g_pucHdcp2Sha256[32];

BYTE g_pucHdcp2BackUp[4];

BYTE g_pucHdcp2M[16];
BYTE g_pucHdcp2Kh[16];
BYTE g_pucHdcp2EkhKm[16];
BYTE g_pucHdcp2Ks[16];
BYTE g_pucHdcp2EDkeyKs[16];
BYTE g_pucHdcp2Riv[8];

BYTE g_pucHdcp2InputCipher[16];
BYTE g_pucHdcp2AesInput[16];
BYTE g_pucHdcp2AesCipherInput[16];

BYTE g_pucHdcp2DpRrxErrta0[8] = {0x3B, 0xA0, 0xBE, 0xDE, 0x0C, 0x46, 0xA9, 0x91};
BYTE g_pucHdcp2DpRrxErrta1[8] = {0xE1, 0x7A, 0xB0, 0xFD, 0x0F, 0x54, 0x40, 0x52};


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------------------------------------------------------------------------------
// Description  : HDCP 2.2 Down Load RSA Key
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array, ucRSAType == > Key Type
// Output Value : None
//--------------------------------------------------------------------------------------------------------------------------
void ScalerHdcp2DownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType)
{
    ScalerHdcp2RxDownLoadCalculateKey(usSubAddr, usLength, pucReadArray, ucRSAType);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2Handler(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D0_DP_SUPPORT == _ON)
    ScalerDpHdcp2Rx0Handler();
#endif

#if(_D1_DP_SUPPORT == _ON)
    ScalerDpHdcp2Rx1Handler();
#endif

#if(_D2_DP_SUPPORT == _ON)
    ScalerDpHdcp2Rx2Handler();
#endif
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    ScalerTmdsHdcp2Rx3Handler();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    ScalerTmdsHdcp2Rx4Handler();
#endif

#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 Initial Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2Initial(void)
{
    // Disable HDCP 2.2 Software Reset
    CLR_HDCP22_SOFTWARE_RESET();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D0_DP_SUPPORT == _ON)
    ///ScalerDPRx0Hdcp2Initial();
#endif

#if(_D1_DP_SUPPORT == _ON)
    ///ScalerDPRx1Hdcp2Initial();
#endif
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    ScalerTmdsHdcp2Rx3Initial();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    ScalerTmdsHdcp2Rx4Initial();
#endif

#endif

#if((_DP_TX_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
    ScalerDpHdcp2TxInitial();
#endif
}

//--------------------------------------------------------------------------------------------------------------------------
// Description  : HDCP 2.2 Down Load RSA Key for Rx Key
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array, ucRSAType == > Key Type
// Output Value : None
//--------------------------------------------------------------------------------------------------------------------------
void ScalerHdcp2RxDownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType)
{
    switch(ucRSAType)
    {
        case _HDCP22_RSA_D_KEY:

            memcpy(&g_stHdcp2RxDownLoadKeyType.pucHdcp2DKey[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP22_RSA_RRMODN_KEY:

            memcpy(&g_stHdcp2RxDownLoadKeyType.pucHdcp2Rrmodn[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP22_RSA_N_PINV:

            memcpy(&g_stHdcp2RxDownLoadKeyType.pucHdcp2Npinv[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP22_CERT_RX:

            memcpy(&g_stHdcp2RxDownLoadKeyType.pucHdcp2Certrx[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP22_LC:

            memcpy(&g_stHdcp2RxDownLoadKeyType.pucHdcp2Lc[usSubAddr], pucReadArray, usLength);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Pairing Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxPairingCalculate(BYTE *pucHdcp2KPriv, BYTE ucIndex)
{
    BYTE ucLoop = 0;
    BYTE pucTemp1[64] = {0};
    BYTE pucTemp2[16] = {0};

    // Disable HDCP 2.2 Software Reset
    CLR_HDCP22_SOFTWARE_RESET();

    for(ucLoop = 0; ucLoop < 4; ucLoop++)
    {
        ScalerHdcp2Proc1(&pucTemp1[ucLoop * 16], &pucHdcp2KPriv[ucLoop * 16]);
    }

    // Calculate Kh = SHA256(Kprivrx), Need 3 SHA256 Block
    if(ucIndex < 5)
    {
        return ScalerHdcp2RxSha256Calculate(pucTemp1, ucIndex);
    }
    else
    {
        pucTemp1[0] = 0x80;
        memset(&pucTemp1[1], 0, 63);
        pucTemp1[62] = 0x0A;

        if(ScalerHdcp2RxSha256Calculate(pucTemp1, ucIndex) == _TRUE)
        {
            memcpy(pucTemp2, (volatile BYTE xdata *)(P63_35_HDCP_SHA_0 + 16), 16);

            memset((volatile BYTE xdata *)P63_35_HDCP_SHA_0, 0, 32);

            ScalerHdcp2Proc2(g_pucHdcp2Kh, pucTemp2);

            return _TRUE;
        }
        else
        {
            memset((volatile BYTE xdata *)P63_35_HDCP_SHA_0, 0, 32);

            DebugMessageHDCP2("HDCP2 Pairing Fail", 0x00);
            return _FALSE;
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 SHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxSha256Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Set 1, Then Set 0 for Reset SHA256 Module
    SET_HDCP22_SHA_MODULE_RESET();
    CLR_HDCP22_SHA_MODULE_RESET();

    // Write SHA256 Input Data, Total 512 bits
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        ScalerSetByte(P63_31_HDCP_SHA_DATA1, pucInputArray[ucLoopIndex * 4]);
        ScalerSetByte(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + ucLoopIndex * 4]);
        ScalerSetByte(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + ucLoopIndex * 4]);
        ScalerSetByte(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + ucLoopIndex * 4]);

        // Inform HW SHA data Has been set first 32 bit
        ScalerHdcp2RxShaWriteData();
    }

    if(ucCalCount == 0)
    {
        // Set First Calculate
        SET_HDCP22_SHA_FIRST_CALCULATE();

        // Enable SHA256 Calculate
        SET_HDCP22_SHA_CALCULATE_ENABLE();
    }
    else
    {
        // Disable First Calculate
        CLR_HDCP22_SHA_FIRST_CALCULATE();

        // Enable SHA256 Calculate
        SET_HDCP22_SHA_CALCULATE_ENABLE();
    }

    // Polling 10ms for HDCP Sha Done
    if(ScalerTimerPollingFlagProc(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        memset((volatile BYTE xdata *)P63_31_HDCP_SHA_DATA1, 0, 4);

        return _TRUE;
    }

    memset((volatile BYTE xdata *)P63_31_HDCP_SHA_DATA1, 0, 4);

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Write Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxRsaWriteData(void)
{
#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT0), _BIT0);

    // Polling 1ms for Rsa Data Write Done
    if(ScalerTimerPollingFlagProc(1, P63_93_HDCP_DUMMY1, _BIT5, _TRUE) == _TRUE)
    {
        ScalerSetBit(P63_93_HDCP_DUMMY1, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
    }
#else
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Read Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxShaWriteData(void)
{
#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
    // Inform HW SHA data Has been set first 32 bit
    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT0), _BIT0);

    // Polling 1ms for HDCP Sha Data Write Done
    if(ScalerTimerPollingFlagProc(1, P63_30_HDCP_SHA_CONTRL, _BIT6, _TRUE) == _TRUE)
    {
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT0), _BIT6);
    }
#else
    // Inform HW SHA data Has been set first 32 bit
    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT0, _BIT0);

    ScalerMcuDelayXus(1);
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Read Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxRsaReadData(void)
{
    // RSA Module Pop-Out Enable
    SET_HDCP22_RSA_READ_POP_OUT_ENABLE();

#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
    // Polling 1ms for Rsa Data Read Pop-Out Done
    if(ScalerTimerPollingFlagProc(1, P63_93_HDCP_DUMMY1, _BIT4, _TRUE) == _TRUE)
    {
        ScalerSetBit(P63_93_HDCP_DUMMY1, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
#endif
}

#if(_HW_HDCP_SHA384_AES192_AES256_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 SHA 384 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxSha384Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Set 1, Then Set 0 for Reset SHA384 Module
    SET_HDCP22_SHA_MODULE_RESET();
    CLR_HDCP22_SHA_MODULE_RESET();

    // Set SHA2-384 Mode
    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT5 | _BIT0), _BIT5);

    // Write SHA384 Input Data, Total 1024 bits
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        ScalerSetByte(P63_31_HDCP_SHA_DATA1, pucInputArray[ucLoopIndex * 8]);
        ScalerSetByte(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + ucLoopIndex * 8]);
        ScalerSetByte(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + ucLoopIndex * 8]);
        ScalerSetByte(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + ucLoopIndex * 8]);
        ScalerSetByte(P63_55_HDCP_SHA_DATA5, pucInputArray[4 + ucLoopIndex * 8]);
        ScalerSetByte(P63_56_HDCP_SHA_DATA6, pucInputArray[5 + ucLoopIndex * 8]);
        ScalerSetByte(P63_57_HDCP_SHA_DATA7, pucInputArray[6 + ucLoopIndex * 8]);
        ScalerSetByte(P63_58_HDCP_SHA_DATA8, pucInputArray[7 + ucLoopIndex * 8]);

        // Inform HW SHA data Has been set first 32 bit
        ScalerHdcp2RxShaWriteData();
    }

    if(ucCalCount == 0)
    {
        // Set First Calculate
        SET_HDCP22_SHA_FIRST_CALCULATE();

        // Enable SHA384 Calculate
        SET_HDCP22_SHA_CALCULATE_ENABLE();
    }
    else
    {
        // Disable First Calculate
        CLR_HDCP22_SHA_FIRST_CALCULATE();

        // Enable SHA384 Calculate
        SET_HDCP22_SHA_CALCULATE_ENABLE();
    }

    // Polling 10ms for HDCP Sha Done
    if(ScalerTimerPollingFlagProc(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        memset((volatile BYTE xdata *)P63_31_HDCP_SHA_DATA1, 0, 4);
        memset((volatile BYTE xdata *)P63_55_HDCP_SHA_DATA5, 0, 4);

        return _TRUE;
    }

    memset((volatile BYTE xdata *)P63_31_HDCP_SHA_DATA1, 0, 4);
    memset((volatile BYTE xdata *)P63_55_HDCP_SHA_DATA5, 0, 4);

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Off-Line AES192 Ctrl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxAes192OfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    BYTE ucDelayTemp = 0xFF;

    // AES Random Disable
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    // HDCP 2.2 Reset
    SET_HDCP22_SOFTWARE_RESET();
    CLR_HDCP22_SOFTWARE_RESET();

    // Set AES-192 key size
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT1 | _BIT0), _BIT0);

    // Load Input Value
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetByte((P63_61_HDCP_AES_DATA_IN_15 + pData[0]), pucInputArray[pData[0]]);
    }

    // Load Input Cipher Key
    for(pData[0] = 0; pData[0] < 24; pData[0]++)
    {
        if(pData[0] < 16)
        {
            ScalerSetByte((P63_71_HDCP_AES_CIPHER_KEY_15 + pData[0]), pucCipherArray[pData[0]]);
        }
        else
        {
            ScalerSetByte((P63_E8_HDCP_AES_CIPHER_KEY_23 + pData[0] - 16), pucCipherArray[pData[0]]);
        }
    }

    // Start AES Calculation
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    // Wait Finish for AES
    while((ScalerGetBit(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && (--ucDelayTemp != 0))
    {
        DELAY_5US();
    }

    memset((volatile BYTE xdata *)P63_61_HDCP_AES_DATA_IN_15, 0, 16);
    memset((volatile BYTE xdata *)P63_71_HDCP_AES_CIPHER_KEY_15, 0, 16);
    memset((volatile BYTE xdata *)P63_E8_HDCP_AES_CIPHER_KEY_23, 0, 8);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Off-Line AES256 Ctrl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxAes256OfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    BYTE ucDelayTemp = 0xFF;

    // AES Random Disable
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    // HDCP 2.2 Reset
    SET_HDCP22_SOFTWARE_RESET();
    CLR_HDCP22_SOFTWARE_RESET();

    // Set AES-256 key size
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT1 | _BIT0), _BIT1);

    // Load Input Value
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetByte((P63_61_HDCP_AES_DATA_IN_15 + pData[0]), pucInputArray[pData[0]]);
    }

    // Load Input Cipher Key
    for(pData[0] = 0; pData[0] < 32; pData[0]++)
    {
        if(pData[0] < 16)
        {
            ScalerSetByte((P63_71_HDCP_AES_CIPHER_KEY_15 + pData[0]), pucCipherArray[pData[0]]);
        }
        else
        {
            ScalerSetByte((P63_E0_HDCP_AES_CIPHER_KEY_31 + pData[0] - 16), pucCipherArray[pData[0]]);
        }
    }

    // Start AES Calculation
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    // Wait Finish for AES
    while((ScalerGetBit(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && (--ucDelayTemp != 0))
    {
        DELAY_5US();
    }

    memset((volatile BYTE xdata *)P63_61_HDCP_AES_DATA_IN_15, 0, 16);
    memset((volatile BYTE xdata *)P63_71_HDCP_AES_CIPHER_KEY_15, 0, 16);
    memset((volatile BYTE xdata *)P63_E0_HDCP_AES_CIPHER_KEY_31, 0, 16);
}
#endif

//--------------------------------------------------
// Description  : HDCP 2.2 Off-Line AES Ctrl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxAesOfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    BYTE ucDelayTemp = 0xFF;

    // AES Random Disable
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    // HDCP 2.2 Reset
    SET_HDCP22_SOFTWARE_RESET();
    CLR_HDCP22_SOFTWARE_RESET();

    // Load Input Value
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetByte((P63_61_HDCP_AES_DATA_IN_15 + pData[0]), pucInputArray[pData[0]]);

        ScalerSetByte((P63_71_HDCP_AES_CIPHER_KEY_15 + pData[0]), pucCipherArray[pData[0]]);
    }

    // Start AES Calculation
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    // Wait Finish for AES
    while((ScalerGetBit(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && (--ucDelayTemp != 0))
    {
        DELAY_5US();
    }

    memset((volatile BYTE xdata *)P63_61_HDCP_AES_DATA_IN_15, 0, 16);
    memset((volatile BYTE xdata *)P63_71_HDCP_AES_CIPHER_KEY_15, 0, 16);
}

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : HDCP 2.2 Mprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2MprimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucStreamIdType, DWORD ulSeqNumM, WORD usK)
{
    BYTE pucHMACSHA256Input[192] = {0};
    BYTE pucHMACSHA256CipherInput[64] = {0};

    // M = HMAC-SHA256(StreamID_Type || seq_num_M, SHA256(kd))
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)

    memcpy(pucHMACSHA256CipherInput, pucHdcp2dKey0, 16);
    memcpy(&pucHMACSHA256CipherInput[16], pucHdcp2dKey1, 16);
    memset(&pucHMACSHA256CipherInput[32], 0, 32);
    pucHMACSHA256CipherInput[32] = 0x80;
    pucHMACSHA256CipherInput[62] = 0x01;
    pucHMACSHA256CipherInput[63] = 0x00;

    if(ScalerHdcp2RxSha256Calculate(pucHMACSHA256CipherInput, 0) == _FALSE)
    {
        return _FALSE;
    }

    // Get SHA256(kd)
    memcpy(pucHMACSHA256CipherInput, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
    memset(&pucHMACSHA256CipherInput[32], 0, 32);

    // Number of StreamID_Type
    pData[0] = usK * 2;

    // Number of (StreamID_Type + seq_num_M + 0x80 + Bit Length of SHA256)
    pData[1] = pData[0] + 3 + 9;

    // Amount of SHA256 block
    pData[1] = ((pData[1] <= 64) ? 1 : ((pData[1] <= 128) ? 2 : 3));

    // Bit length of SHA256
    PDATA_WORD(1) = (64 + pData[0] + 3) * 8;

    memcpy(pucHMACSHA256Input, pucStreamIdType, pData[0]);

    pucHMACSHA256Input[pData[0]] = (BYTE)(ulSeqNumM >> 16);
    pucHMACSHA256Input[pData[0] + 1] = (BYTE)(ulSeqNumM >> 8);
    pucHMACSHA256Input[pData[0] + 2] = (BYTE)(ulSeqNumM >> 0);
    pucHMACSHA256Input[pData[0] + 3] = 0x80;
    pucHMACSHA256Input[(pData[1] * 64) - 2] = HIBYTE(PDATA_WORD(1));
    pucHMACSHA256Input[(pData[1] * 64) - 1] = LOBYTE(PDATA_WORD(1));

    if(ScalerHdcp2RepeaterHmacSha256Calculate(pucHMACSHA256Input, pucHMACSHA256CipherInput, pData[1]) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 HMACSHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RepeaterHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2, BYTE ucInputArray1BlockNumber)
{
    BYTE ucTemp = 0;
    BYTE pucSHA256Input[64] = {0};

    for(pData[0] = 0; pData[0] < 64; pData[0]++)
    {
        // K0 XOR ipad = 512 bit
        pucInputArray2[pData[0]] = pucInputArray2[pData[0]] ^ 0x36;
    }

    // Calculate SHA256((K0 XOR ipad) || text)
    if(ScalerHdcp2RxSha256Calculate(pucInputArray2, 0) == _FALSE)
    {
        return _FALSE;
    }

    ucTemp = 0;

    do
    {
        memcpy(pucSHA256Input, (pucInputArray1 + (64 * ucTemp)), 64);

        if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, (ucTemp + 1)) == _FALSE)
        {
            return _FALSE;
        }

        ucTemp++;
    }
    while(ucTemp < ucInputArray1BlockNumber);

    // KO XOR opad
    for(pData[0] = 0; pData[0] < 64; pData[0]++)
    {
        pucInputArray2[pData[0]] = (pucInputArray2[pData[0]] ^ 0x36) ^ 0x5C;
    }

    memcpy(pucInputArray1, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
    memset(pucInputArray1 + 32, 0, 32);
    pucInputArray1[32] = 0x80;
    pucInputArray1[62] = 0x03;

    // SHA256((KO XOR opad) || SHA256(KO XOR ipad) || text)
    if(ScalerHdcp2RxSha256Calculate(pucInputArray2, 0) == _TRUE)
    {
        if(ScalerHdcp2RxSha256Calculate(pucInputArray1, 1) == _TRUE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Vprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2VprimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucReceiverIdList, BYTE *pucRxinfo, BYTE *pucSeqNumV)
{
    BYTE pucHMACSHA256Input[192] = {0};
    BYTE pucHMACSHA256CipherInput[64] = {0};

    // V = HMAC-SHA256(Receiver ID List || RxInfo || seq_num_V, kd)
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)

    memcpy(pucHMACSHA256CipherInput, pucHdcp2dKey0, 16);
    memcpy(&pucHMACSHA256CipherInput[16], pucHdcp2dKey1, 16);
    memset(&pucHMACSHA256CipherInput[32], 0, 32);

    pData[0] = ((pucRxinfo[0] & _BIT0) << 4 | (pucRxinfo[1] >> 4)) * 5;
    pData[1] = pData[0] + 5 + 9;
    pData[1] = ((pData[1] <= 64) ? 1 : ((pData[1] <= 128) ? 2 : 3));
    PDATA_WORD(1) = (64 + pData[0] + 5) * 8;

    memcpy(pucHMACSHA256Input, pucReceiverIdList, pData[0]);
    memcpy(&pucHMACSHA256Input[pData[0]], pucRxinfo, 2);
    memcpy(&pucHMACSHA256Input[pData[0] + 2], pucSeqNumV, 3);
    pucHMACSHA256Input[pData[0] + 5] = 0x80;
    pucHMACSHA256Input[(pData[1] * 64) - 2] = HIBYTE(PDATA_WORD(1));
    pucHMACSHA256Input[(pData[1] * 64) - 1] = LOBYTE(PDATA_WORD(1));

    if(ScalerHdcp2RepeaterHmacSha256Calculate(pucHMACSHA256Input, pucHMACSHA256CipherInput, pData[1]) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Dkey Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2DkeyCalculate(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn)
{
    BYTE pucAESInput[16] = {0};
    BYTE pucAESCipherInput[16] = {0};

    switch(ucDkeyCount)
    {
        case _HDCP_2_2_DKEY_0:

            // Initial AES Input Value
            memcpy(pucAESInput, pucHdcp2Rtx, 8);
            memcpy(&pucAESInput[8], pucHdcp2Rrx, 8);
            memcpy(pucAESCipherInput, pucHdcp2Km, 16);

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl(pucAESInput, pucAESCipherInput);

            break;

        case _HDCP_2_2_DKEY_1:

            // Initial AES Input Value
            memcpy(pucAESInput, pucHdcp2Rtx, 8);
            memcpy(&pucAESInput[8], pucHdcp2Rrx, 7);
            pucAESInput[15] = pucHdcp2Rrx[7] ^ 0x01;
            memcpy(pucAESCipherInput, pucHdcp2Km, 16);

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl(pucAESInput, pucAESCipherInput);

            break;

        case _HDCP_2_2_DKEY_2:

            // Initial AES Input Value
            memcpy(pucAESInput, pucHdcp2Rtx, 8);
            memcpy(&pucAESInput[8], pucHdcp2Rrx, 7);
            pucAESInput[15] = pucHdcp2Rrx[7] ^ 0x02;

            memcpy(pucAESCipherInput, pucHdcp2Km, 8);

            for(pData[0] = 8; pData[0] < 16; pData[0]++)
            {
                pucAESCipherInput[pData[0]] = pucHdcp2Km[pData[0]] ^ pucHdcp2Rn[pData[0] - 8];
            }

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl(pucAESInput, pucAESCipherInput);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Hprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2HPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps)
{
    BYTE pucHMACSHA256Input[64] = {0};
    BYTE pucHMACSHA256CipherInput[64] = {0};

    // H = HMAC-SHA256(rtx || RxCaps || TxCaps, kd)
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)

    memcpy(pucHMACSHA256CipherInput, pucHdcp2dKey0, 16);
    memcpy(&pucHMACSHA256CipherInput[16], pucHdcp2dKey1, 16);
    memcpy(pucHMACSHA256Input, pucHdcp2Rtx, 8);
    memcpy(&pucHMACSHA256Input[8], pucHdcp2RxCaps, 3);
    memcpy(&pucHMACSHA256Input[11], pucHdcp2TxCaps, 3);
    pucHMACSHA256Input[14] = 0x80;
    memset(&pucHMACSHA256Input[15], 0, 47);
    pucHMACSHA256Input[62] = 0x02;
    pucHMACSHA256Input[63] = 0x70;

    memset(&pucHMACSHA256CipherInput[32], 0, 32);

    if(ScalerHdcp2RxHmacSha256Calculate(pucHMACSHA256Input, pucHMACSHA256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 HMACSHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2)
{
    for(pData[0] = 0; pData[0] < 64; pData[0]++)
    {
        // K0 XOR ipad = 512 bit
        pucInputArray2[pData[0]] = pucInputArray2[pData[0]] ^ 0x36;
    }

    // Calculate SHA256((K0 XOR ipad) || text)
    if(ScalerHdcp2RxSha256Calculate(pucInputArray2, 0) == _TRUE)
    {
        if(ScalerHdcp2RxSha256Calculate(pucInputArray1, 1) == _TRUE)
        {
            // KO XOR opad
            for(pData[0] = 0; pData[0] < 64; pData[0]++)
            {
                pucInputArray2[pData[0]] = (pucInputArray2[pData[0]] ^ 0x36) ^ 0x5C;
            }

            memcpy(pucInputArray1, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
            memset(pucInputArray1 + 32, 0, 32);
            pucInputArray1[32] = 0x80;
            pucInputArray1[62] = 0x03;

            // SHA256((KO XOR opad) || SHA256(KO XOR ipad) || text)
            if(ScalerHdcp2RxSha256Calculate(pucInputArray2, 0) == _TRUE)
            {
                if(ScalerHdcp2RxSha256Calculate(pucInputArray1, 1) == _TRUE)
                {
                    return _TRUE;
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxRsaCalculate(BYTE *pucEkpubKmArray)
{
    BYTE ucLoop = 0;
    BYTE pucTemp[128] = {0};
    BYTE ucLoopIndex = 0x00;

    for(ucLoop = 0; ucLoop < 8; ucLoop++)
    {
        ScalerHdcp2Proc1(&pucTemp[ucLoop * 16], &g_stHdcp2RxDownLoadKeyType.pucHdcp2DKey[ucLoop * 16]);
    }

    // Enable HDCP 2.2 RSA Module
    SET_HDCP22_RSA_WRITE_KEY_MODE();

    // RSA Clock Select
    SET_HDCP22_RSA_CLK();

    // Select RSA Key Download Data Length
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

    // Load Ekpub[km] to RSA Module as cipher text
    for(ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (15 - ucLoopIndex));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEkpubKmArray[ucLoopIndex << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        // Load RRmodN
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - ucLoopIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stHdcp2RxDownLoadKeyType.pucHdcp2Rrmodn[ucLoopIndex << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (15 - ucLoopIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stHdcp2RxDownLoadKeyType.pucHdcp2Certrx[(ucLoopIndex << 3) + 5], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        // Load D Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (15 - ucLoopIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucTemp[ucLoopIndex << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, &g_stHdcp2RxDownLoadKeyType.pucHdcp2Npinv, 4);

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

        // Clear RSA Module Data Input
        memset((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, 0, 8);

        return _TRUE;
    }

    // Clear RSA Module Data Input
    memset((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, 0, 8);

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Oaep Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxRsaOaepCalculate(BYTE *pucKmArray)
{
    BYTE pucSHA256Input[64];
    BYTE pucRsaOaepInput[128];
    BYTE ucLoopIndex = 0x00;

    // Read Out RSA Message
    SET_HDCP22_RSA_READ_OUT_MODE();

    // Read Message From One of 2 Address
    if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, ucLoopIndex);

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucRsaOaepInput[(15 - ucLoopIndex) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 | ucLoopIndex));

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucRsaOaepInput[(15 - ucLoopIndex) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }

    // Calculate First Block 512 Bit SHA256 Calculate, Calculate MGF(maskDB, 32)
    if(ScalerHdcp2RxSha256Calculate(&pucRsaOaepInput[33], 0) == _TRUE)
    {
        // Load Second Block 512 Bit Data
        memcpy(pucSHA256Input, &pucRsaOaepInput[97], 31);
        memset(&pucSHA256Input[31], 0, 33);
        pucSHA256Input[35] = 0x80;
        pucSHA256Input[62] = 0x03;
        pucSHA256Input[63] = 0x18;

        // Calculate Second Block 512 Bit Data
        if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 1) == _TRUE)
        {
            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                pucSHA256Input[pData[0]] = pucRsaOaepInput[1 + pData[0]] ^ ScalerGetByte((P63_35_HDCP_SHA_0 + pData[0]));
            }

            memset(&pucSHA256Input[32], 0, 32);
            pucSHA256Input[36] = 0x80;
            pucSHA256Input[62] = 0x01;
            pucSHA256Input[63] = 0x20;

            // Calculte MGF(Seed, 95), Seed = 32 byte SHA256 output + C 0x0000000x + 0x80 + Stream Length
            pucSHA256Input[35] = 0;
            if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0) == _FALSE)
            {
                return _FALSE;
            }

            pucSHA256Input[35] = 1;
            if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0) == _FALSE)
            {
                return _FALSE;
            }

            pucSHA256Input[35] = 2;
            if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0) == _FALSE)
            {
                return _FALSE;
            }

            // DB maskDB XOR DBmask
            for(pData[0] = 0; pData[0] < 31; pData[0]++)
            {
                pucSHA256Input[pData[0]] = pucRsaOaepInput[33 + pData[0] + 64] ^ ScalerGetByte((P63_35_HDCP_SHA_0 + pData[0]));
            }

            pucSHA256Input[31] = ScalerGetByte((P63_35_HDCP_SHA_0 + 31));

            if(pucSHA256Input[14] == 0x01)
            {
                memcpy(pucKmArray, &pucSHA256Input[15], 16);

                return _TRUE;
            }
        }
    }

    return _FALSE;
}

#if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : HDCP 2.2 Repeater Lprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RepeaterLPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucInputArray)
{
    BYTE pucLPrimeInput1[64] = {0};
    BYTE pucLPrimeInput2[64] = {0};
    BYTE pucHMACSHA256CipherInput[64] = {0};

    // L = HMAC-SHA256(Stream-Status || Q_id || S_id || Link_id || Link_Pk || Link_S || SALT, kd)
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)
    memcpy(pucLPrimeInput1, pucInputArray, 64);

    // Total Length of (KO XOR ipad) || text) = 496 + 512 (bits) = 1008 (bits)
    pucLPrimeInput2[0] = 0x80;
    memset(&pucLPrimeInput2[1], 0, 61);
    pucLPrimeInput2[62] = 0x04;
    pucLPrimeInput2[63] = 0x00;

    memcpy(pucHMACSHA256CipherInput, pucHdcp2dKey0, 16);
    memcpy(&pucHMACSHA256CipherInput[16], pucHdcp2dKey1, 16);
    memset(&pucHMACSHA256CipherInput[32], 0, 32);

    if(ScalerHdcp2RepeaterLPrimeHmacSha256Calculate(pucLPrimeInput1, pucLPrimeInput2, pucHMACSHA256CipherInput) == _TRUE)
    {
        DebugMessageHDCP2("[QSE] LPrime Pass", 0);
        return _TRUE;
    }

    DebugMessageHDCP2("[QSE] LPrime Fail", 0);
    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 HMACSHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RepeaterLPrimeHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2, BYTE *pucInputArray3)
{
    for(pData[0] = 0; pData[0] < 64; pData[0]++)
    {
        // K0 XOR ipad = 512 bit
        // pInputArray2[pData[0]] = pInputArray2[pData[0]] ^ 0x36;
        pucInputArray3[pData[0]] = pucInputArray3[pData[0]] ^ 0x36;
    }

    // Calculate SHA256((K0 XOR ipad) || text)
    if(ScalerHdcp2RxSha256Calculate(pucInputArray3, 0) == _TRUE)
    {
        if(ScalerHdcp2RxSha256Calculate(pucInputArray1, 1) == _TRUE)
        {
            if(ScalerHdcp2RxSha256Calculate(pucInputArray2, 1) == _TRUE)
            {
                // KO XOR opad
                for(pData[0] = 0; pData[0] < 64; pData[0]++)
                {
                    // pInputArray2[pData[0]] = (pInputArray2[pData[0]] ^ 0x36) ^ 0x5C;
                    pucInputArray3[pData[0]] = (pucInputArray3[pData[0]] ^ 0x36) ^ 0x5C;
                }

                memcpy(pucInputArray1, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
                memset(pucInputArray1 + 32, 0, 32);
                pucInputArray1[32] = 0x80;
                pucInputArray1[62] = 0x03;

                // SHA256((KO XOR opad) || SHA256(KO XOR ipad) || text)
                if(ScalerHdcp2RxSha256Calculate(pucInputArray3, 0) == _TRUE)
                {
                    if(ScalerHdcp2RxSha256Calculate(pucInputArray1, 1) == _TRUE)
                    {
                        return _TRUE;
                    }
                }
            }
        }
    }

    return _FALSE;
}

#endif

#endif

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : HDCP 2.2 Lprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2LPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn)
{
    BYTE pucHMACSHA256Input[64] = {0};
    BYTE pucHMACSHA256CipherInput[64] = {0};

    memcpy(pucHMACSHA256CipherInput, pucHdcp2dKey0, 16);

    for(pData[0] = 16; pData[0] < 32; pData[0]++)
    {
        pucHMACSHA256CipherInput[pData[0]] = pucHdcp2dKey1[pData[0] - 16];

        if(pData[0] > 23)
        {
            pucHMACSHA256CipherInput[pData[0]] = pucHMACSHA256CipherInput[pData[0]] ^ pucHdcp2Rrx[pData[0] - 24];
        }
    }

    memset(&pucHMACSHA256CipherInput[32], 0, 32);
    memcpy(pucHMACSHA256Input, pucHdcp2Rn, 8);
    pucHMACSHA256Input[8] = 0x80;
    memset(&pucHMACSHA256Input[9], 0, 53);
    pucHMACSHA256Input[62] = 0x02;
    pucHMACSHA256Input[63] = 0x40;

    if(ScalerHdcp2RxHmacSha256Calculate(pucHMACSHA256Input, pucHMACSHA256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_IROM)
//--------------------------------------------------
// Description  : Get HDCP2 DcpLIcN From IROM
// Input Value  : StartAddress, Length, *pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2GetTxHdcp2DcpLlcNFromIrom(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    ScalerMcuIromAccess((_HW_TX_HDCP_2_2_KEY_START_ADDRESS_IROM + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP2 EKey From IROM
// Input Value  : StartAddress, Length, *pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2GetTxHdcp2EKeyFromIrom(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    ScalerMcuIromAccess((_HW_TX_HDCP_2_2_KEY_START_ADDRESS_IROM + 384 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP2 RRMODN From IROM
// Input Value  : StartAddress, Length, *pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2GetTxHdcp2RRMODNFromIrom(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    ScalerMcuIromAccess((_HW_TX_HDCP_2_2_KEY_START_ADDRESS_IROM + 512 + (usSubAddr)), usLength, pucReadArray);
}

//--------------------------------------------------
// Description  : Get HDCP2 NPinv From IROM
// Input Value  : StartAddress, Length, *pucReadArray
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2GetTxHdcp2NPinvFromIrom(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    ScalerMcuIromAccess((_HW_TX_HDCP_2_2_KEY_START_ADDRESS_IROM + 896 + (usSubAddr)), usLength, pucReadArray);
}
#endif
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2.2 Re-Auth Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH:

            ScalerTmdsHdcp2Rx3ReAuthEvent();

            break;
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_HDCP2_REAUTH:

            ScalerTmdsHdcp2Rx4ReAuthEvent();

            break;
#endif

        default:

            break;
    }
}
#endif
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

