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
// ID Code      : ScalerHdcp2_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDCP2_EXINT0__

#include "ScalerFunctionInclude.h"
#include "Hdcp2/ScalerHdcp2.h"




#if(_HDCP_2_2_SUPPORT == _ON)
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
// Description  : HDCP 2.2 Dkey Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2DkeyCalculate_EXINT0(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn)
{
    switch(ucDkeyCount)
    {
        case _HDCP_2_2_DKEY_0:

            // Initial AES Input Value
            for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ucLoopIndex++)
            {
                g_pucHdcp2AesInput[ucLoopIndex] = pucHdcp2Rtx[ucLoopIndex];
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ucLoopIndex++)
            {
                g_pucHdcp2AesInput[8 + ucLoopIndex] = pucHdcp2Rrx[ucLoopIndex];
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
            {
                g_pucHdcp2AesCipherInput[ucLoopIndex] = pucHdcp2Km[ucLoopIndex];
            }

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

            break;

        case _HDCP_2_2_DKEY_1:

            // Initial AES Input Value
            for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ucLoopIndex++)
            {
                g_pucHdcp2AesInput[ucLoopIndex] = pucHdcp2Rtx[ucLoopIndex];
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < 7; ucLoopIndex++)
            {
                g_pucHdcp2AesInput[8 + ucLoopIndex] = pucHdcp2Rrx[ucLoopIndex];
            }

            g_pucHdcp2AesInput[15] = pucHdcp2Rrx[7] ^ 0x01;

            for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
            {
                g_pucHdcp2AesCipherInput[ucLoopIndex] = pucHdcp2Km[ucLoopIndex];
            }

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

            break;

        case _HDCP_2_2_DKEY_2:

            // Initial AES Input Value
            for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ucLoopIndex++)
            {
                g_pucHdcp2AesInput[ucLoopIndex] = pucHdcp2Rtx[ucLoopIndex];
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < 7; ucLoopIndex++)
            {
                g_pucHdcp2AesInput[8 + ucLoopIndex] = pucHdcp2Rrx[ucLoopIndex];
            }

            g_pucHdcp2AesInput[15] = pucHdcp2Rrx[7] ^ 0x02;

            for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ucLoopIndex++)
            {
                g_pucHdcp2AesCipherInput[ucLoopIndex] = pucHdcp2Km[ucLoopIndex];
            }

            for(BYTE ucLoopIndex = 8; ucLoopIndex < 16; ucLoopIndex++)
            {
                g_pucHdcp2AesCipherInput[ucLoopIndex] = pucHdcp2Km[ucLoopIndex] ^ pucHdcp2Rn[ucLoopIndex - 8];
            }

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Hprime Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2HPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps)
{
    // H = HMAC-SHA256(rtx || RxCaps || TxCaps, kd)
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        g_pucHdcp2HmacSha256CipherInput[ucLoopIndex] = pucHdcp2dKey0[ucLoopIndex];
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        g_pucHdcp2HmacSha256CipherInput[16 + ucLoopIndex] = pucHdcp2dKey1[ucLoopIndex];
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ucLoopIndex++)
    {
        g_pucHdcp2HmacSha256Input[ucLoopIndex] = pucHdcp2Rtx[ucLoopIndex];
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 3; ucLoopIndex++)
    {
        g_pucHdcp2HmacSha256Input[8 + ucLoopIndex] = pucHdcp2RxCaps[ucLoopIndex];
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 3; ucLoopIndex++)
    {
        g_pucHdcp2HmacSha256Input[11 + ucLoopIndex] = pucHdcp2TxCaps[ucLoopIndex];
    }

    g_pucHdcp2HmacSha256Input[14] = 0x80;

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 47; ucLoopIndex++)
    {
        g_pucHdcp2HmacSha256Input[15 + ucLoopIndex] = 0;
    }

    g_pucHdcp2HmacSha256Input[62] = 0x02;
    g_pucHdcp2HmacSha256Input[63] = 0x70;

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 32; ucLoopIndex++)
    {
        g_pucHdcp2HmacSha256CipherInput[32 + ucLoopIndex] = 0;
    }

    if(ScalerHdcp2RxHmacSha256Calculate_EXINT0(g_pucHdcp2HmacSha256Input, g_pucHdcp2HmacSha256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2IntHandler_EXINT0(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D0_DP_SUPPORT == _ON)
    ScalerDpHdcp2Rx0Handler_EXINT0();
#endif

#if(_D1_DP_SUPPORT == _ON)
    ScalerDpHdcp2Rx1Handler_EXINT0();
#endif

#if(_D2_DP_SUPPORT == _ON)
    ScalerDpHdcp2Rx2Handler_EXINT0();
#endif
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)

#if(_TMDS_MAC_RX3_SUPPORT == _ON)
    ScalerTmdsHdcp2Rx3IntHandler_EXINT0();
#endif

#if(_TMDS_MAC_RX4_SUPPORT == _ON)
    ScalerTmdsHdcp2Rx4IntHandler_EXINT0();
#endif

#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 Lprime Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2LPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn)
{
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 64; ucLoopIndex++)
    {
        if(ucLoopIndex < 8)
        {
            g_pucHdcp2HmacSha256Input[ucLoopIndex] = pucHdcp2Rn[ucLoopIndex];
        }
        else
        {
            g_pucHdcp2HmacSha256Input[ucLoopIndex] = 0;
        }
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 64; ucLoopIndex++)
    {
        if(ucLoopIndex < 16)
        {
            g_pucHdcp2HmacSha256CipherInput[ucLoopIndex] = pucHdcp2dKey0[ucLoopIndex];
        }
        else if(ucLoopIndex < 32)
        {
            g_pucHdcp2HmacSha256CipherInput[ucLoopIndex] = pucHdcp2dKey1[ucLoopIndex - 16];

            if(ucLoopIndex > 23)
            {
                g_pucHdcp2HmacSha256CipherInput[ucLoopIndex] = g_pucHdcp2HmacSha256CipherInput[ucLoopIndex] ^ pucHdcp2Rrx[ucLoopIndex - 24];
            }
        }
        else
        {
            g_pucHdcp2HmacSha256CipherInput[ucLoopIndex] = 0;
        }
    }


    g_pucHdcp2HmacSha256Input[8] = 0x80;
    g_pucHdcp2HmacSha256Input[62] = 0x02;
    g_pucHdcp2HmacSha256Input[63] = 0x40;

    if((bit)ScalerHdcp2RxHmacSha256Calculate_EXINT0(g_pucHdcp2HmacSha256Input, g_pucHdcp2HmacSha256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check RSA Available or Not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE ScalerHdcp2RsaAvailable_EXINT0(void)
{
    // (M2PLL Power ON) && (GDI Clock is M2PLL)
    if((ScalerGetBit_EXINT(P1_58_M2PLL_CONTROL, _BIT0) == 0x00) && (ScalerGetBit_EXINT(P80_06_GDI_CLK_DIVIDER, _BIT4) == _BIT4))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Off-Line AES Ctrl in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxAesOfflineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    // AES Random Disable
    ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    // HDCP 2.2 Reset
    SET_HDCP22_SOFTWARE_RESET();
    CLR_HDCP22_SOFTWARE_RESET();

    // Load Input Value
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        ScalerSetByte_EXINT((P63_61_HDCP_AES_DATA_IN_15 + ucLoopIndex), pucInputArray[ucLoopIndex]);

        ScalerSetByte_EXINT((P63_71_HDCP_AES_CIPHER_KEY_15 + ucLoopIndex), pucCipherArray[ucLoopIndex]);
    }

    // Start AES Calculation
    ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    // Wait Finish for AES
    BYTE ucCounter = 0xFF;
    while((ScalerGetBit_EXINT(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && (--ucCounter != 0))
    {
        DELAY_5US_EXINT();
    }

    memset((volatile BYTE xdata *)P63_61_HDCP_AES_DATA_IN_15, 0, 16);
    memset((volatile BYTE xdata *)P63_71_HDCP_AES_CIPHER_KEY_15, 0, 16);
}

//--------------------------------------------------
// Description  : Get psudo-random Rrx Key for HDCP 2.2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxGenRrx_EXINT0(BYTE *pucInputArray)
{
    BYTE ucDelayXus_Cnt = 0x00;
    BYTE ucLoop = 0x00;
    BYTE ucDelay = 0x00;

    do
    {
        // Rrx Gen
        // Enable AES Random Gen
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), (_BIT5));

        // AES Trigger
        ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

        // Delay [1, x]ms Randon Time
        ucDelayXus_Cnt = ((5 * (GET_MCU_TIMER_RANDOM_BYTE() >> 2)) % 1000) >> 2;
        do
        {
            DELAY_5US_EXINT();
        }
        while(ucDelayXus_Cnt--);

        // Wait Finish for AES Random Gen
        ucDelay = 0x0A;

        while((ScalerGetBit_EXINT(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && ((--ucDelay) != 0))
        {
            DELAY_5US_EXINT();
        }

        // Get Rrx from HW (MSB located at index 0)
        ScalerHdcp2RxGetRrx_EXINT0(pucInputArray);

        // Disable AES Random Gen
        SET_HDCP22_RANDOM_GENERATOR_DISABLE_EXINT();

        if((__real_memcmp(pucInputArray, g_pucHdcp2DpRrxErrta0, 8) != 0x00) &&
           (__real_memcmp(pucInputArray, g_pucHdcp2DpRrxErrta1, 8) != 0x00))
        {
            break;
        }
        else
        {
            ucLoop++;
        }
    }
    while(ucLoop < 3);

    if(ucLoop == 0x03)
    {
        // Force Assign a default Rrx Key
        pucInputArray[0] = 0x11;
        pucInputArray[1] = 0x22;
        pucInputArray[2] = 0x33;
        pucInputArray[3] = 0x44;
        pucInputArray[4] = 0x55;
        pucInputArray[5] = 0x66;
        pucInputArray[6] = 0x77;
        pucInputArray[7] = 0x88;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Rrx Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxGetRrx_EXINT0(BYTE *pucHdcp2Rrx)
{
    // Load Rrx to Read SRAM
    pucHdcp2Rrx[0] = ScalerGetByte_EXINT(P63_89_HDCP_AES_OUT_7);
    pucHdcp2Rrx[1] = ScalerGetByte_EXINT(P63_8A_HDCP_AES_OUT_6);
    pucHdcp2Rrx[2] = ScalerGetByte_EXINT(P63_8B_HDCP_AES_OUT_5);
    pucHdcp2Rrx[3] = ScalerGetByte_EXINT(P63_8C_HDCP_AES_OUT_4);
    pucHdcp2Rrx[4] = ScalerGetByte_EXINT(P63_8D_HDCP_AES_OUT_3);
    pucHdcp2Rrx[5] = ScalerGetByte_EXINT(P63_8E_HDCP_AES_OUT_2);
    pucHdcp2Rrx[6] = ScalerGetByte_EXINT(P63_8F_HDCP_AES_OUT_1);
    pucHdcp2Rrx[7] = ScalerGetByte_EXINT(P63_90_HDCP_AES_OUT_0);
}

//--------------------------------------------------
// Description  : HDCP 2.2 HMACSHA 256 Calculate IN INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RxHmacSha256Calculate_EXINT0(BYTE *pucInputArray1, BYTE *pucInputArray2)
{
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 64; ucLoopIndex++)
    {
        // K0 XOR ipad = 512 bit
        pucInputArray2[ucLoopIndex] = pucInputArray2[ucLoopIndex] ^ 0x36;
    }

    // Calculate SHA256((K0 XOR ipad) || text)
    if(ScalerHdcp2RxSha256Calculate_EXINT0(pucInputArray2, 0) == _TRUE)
    {
        if(ScalerHdcp2RxSha256Calculate_EXINT0(pucInputArray1, 1) == _TRUE)
        {
            // KO XOR opad
            for(BYTE ucLoopIndex = 0; ucLoopIndex < 64; ucLoopIndex++)
            {
                pucInputArray2[ucLoopIndex] = (pucInputArray2[ucLoopIndex] ^ 0x36) ^ 0x5C;
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < 64; ucLoopIndex++)
            {
                if(ucLoopIndex < 32)
                {
                    pucInputArray1[ucLoopIndex] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + ucLoopIndex);
                }
                else
                {
                    pucInputArray1[ucLoopIndex] = 0;
                }
            }

            pucInputArray1[32] = 0x80;
            pucInputArray1[62] = 0x03;

            // SHA256((KO XOR opad) || SHA256(KO XOR ipad) || text)
            if(ScalerHdcp2RxSha256Calculate_EXINT0(pucInputArray2, 0) == _TRUE)
            {
                if(ScalerHdcp2RxSha256Calculate_EXINT0(pucInputArray1, 1) == _TRUE)
                {
                    return _TRUE;
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 SHA 256 Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RxSha256Calculate_EXINT0(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Set 1, Then Set 0 for Reset SHA256 Module
    SET_HDCP22_SHA_MODULE_RESET();
    CLR_HDCP22_SHA_MODULE_RESET();

    // Write SHA256 Input Data, Total 512 bits
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        ScalerSetByte_EXINT(P63_31_HDCP_SHA_DATA1, pucInputArray[ucLoopIndex * 4]);
        ScalerSetByte_EXINT(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + ucLoopIndex * 4]);
        ScalerSetByte_EXINT(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + ucLoopIndex * 4]);
        ScalerSetByte_EXINT(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + ucLoopIndex * 4]);

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
    if(ScalerTimerPollingFlagProc_EXINT0(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        memset((volatile BYTE xdata *)P63_31_HDCP_SHA_DATA1, 0, 4);

        return _TRUE;
    }

    memset((volatile BYTE xdata *)P63_31_HDCP_SHA_DATA1, 0, 4);

    return _FALSE;
}

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxRsaCal_EXINT0(BYTE *pucEkpubKmArray)
{
    BYTE ucLoop = 0;
    BYTE pucTemp[128] = {0};

    for(ucLoop = 0; ucLoop < 8; ucLoop++)
    {
        ScalerHdcp2Proc1_EXINT0(&pucTemp[ucLoop * 16], &g_stHdcp2RxDownLoadKeyType.pucHdcp2DKey[ucLoop * 16]);
    }

    // Enable HDCP 2.2 RSA Module
    SET_HDCP22_RSA_WRITE_KEY_MODE();

    // RSA Clock Select
    SET_HDCP22_RSA_CLK();

    // Select RSA Key Download Data Length
    ScalerSetBit_EXINT(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

    // Load Ekpub[km] to RSA Module as cipher text
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        // Enable write cipher text to RSA Module
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (15 - ucLoopIndex));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEkpubKmArray[ucLoopIndex << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        // Load RRmodN
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - ucLoopIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stHdcp2RxDownLoadKeyType.pucHdcp2Rrmodn[ucLoopIndex << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        // Load N Key
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (15 - ucLoopIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stHdcp2RxDownLoadKeyType.pucHdcp2Certrx[(ucLoopIndex << 3) + 5], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        // Load D Key
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (15 - ucLoopIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucTemp[ucLoopIndex << 3], 8);

        // Rsa Data Write-in
        ScalerHdcp2RxRsaWriteData();
    }

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, &g_stHdcp2RxDownLoadKeyType.pucHdcp2Npinv, 4);

    // Set RSA Write key done
    SET_HDCP22_RSA_WRITE_KEY_DONE();

    // Enable RSA Calculate
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Oaep Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RxRsaOaepCalculate_EXINT0(BYTE *pucKmArray)
{
    BYTE pucHdcp2RsaOaepInput[128];

    // Read Out RSA Message
    SET_HDCP22_RSA_READ_OUT_MODE();

    // Read Message From One of 2 Address
    if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
        {
            ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, ucLoopIndex);

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucHdcp2RsaOaepInput[(15 - ucLoopIndex) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
        {
            ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (0x30 | ucLoopIndex));

            // RSA Read Out Data
            ScalerHdcp2RxRsaReadData();

            memcpy(&pucHdcp2RsaOaepInput[(15 - ucLoopIndex) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }

    // Calculate First Block 512 Bit SHA256 Calculate, Calculate MGF(maskDB, 32)
    if(ScalerHdcp2RxSha256Calculate_EXINT0(&pucHdcp2RsaOaepInput[33], 0) == _TRUE)
    {
        // Load Second Block 512 Bit Data
        __real_memcpy(g_pucHdcp2SHA256Input, &pucHdcp2RsaOaepInput[97], 31);
        __real_memset(&g_pucHdcp2SHA256Input[31], 0, 33);
        g_pucHdcp2SHA256Input[35] = 0x80;
        g_pucHdcp2SHA256Input[62] = 0x03;
        g_pucHdcp2SHA256Input[63] = 0x18;

        // Calculate Second Block 512 Bit Data
        if(ScalerHdcp2RxSha256Calculate_EXINT0(g_pucHdcp2SHA256Input, 1) == _TRUE)
        {
            for(BYTE ucLoopIndex = 0; ucLoopIndex < 32; ucLoopIndex++)
            {
                g_pucHdcp2SHA256Input[ucLoopIndex] = pucHdcp2RsaOaepInput[1 + ucLoopIndex] ^ ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + ucLoopIndex));
            }

            __real_memset(&g_pucHdcp2SHA256Input[32], 0, 32);
            g_pucHdcp2SHA256Input[36] = 0x80;
            g_pucHdcp2SHA256Input[62] = 0x01;
            g_pucHdcp2SHA256Input[63] = 0x20;

            // Calculte MGF(Seed, 95), Seed = 32 byte SHA256 output + C 0x0000000x + 0x80 + Stream Length
            g_pucHdcp2SHA256Input[35] = 0;
            if(ScalerHdcp2RxSha256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0) == _FALSE)
            {
                return _FALSE;
            }

            g_pucHdcp2SHA256Input[35] = 1;
            if(ScalerHdcp2RxSha256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0) == _FALSE)
            {
                return _FALSE;
            }

            g_pucHdcp2SHA256Input[35] = 2;
            if(ScalerHdcp2RxSha256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0) == _FALSE)
            {
                return _FALSE;
            }

            // DB maskDB XOR DBmask
            for(BYTE ucLoopIndex = 0; ucLoopIndex < 31; ucLoopIndex++)
            {
                g_pucHdcp2SHA256Input[ucLoopIndex] = pucHdcp2RsaOaepInput[33 + ucLoopIndex + 64] ^ ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + ucLoopIndex));
            }

            g_pucHdcp2SHA256Input[31] = ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + 31));

            if(g_pucHdcp2SHA256Input[14] == 0x01)
            {
                __real_memcpy(pucKmArray, &g_pucHdcp2SHA256Input[15], 16);

                return _TRUE;
            }
        }
    }

    return _FALSE;
}

#endif
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

