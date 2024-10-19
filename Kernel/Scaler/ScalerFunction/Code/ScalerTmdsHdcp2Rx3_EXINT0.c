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
// ID Code      : ScalerTmdsHdcp2Rx3_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TmdsHdcp2Rx3/ScalerTmdsHdcp2Rx3.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)

//--------------------------------------------------
// Description  : HDCP 2.2 On-Line AES Ctrl in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3AesOnlineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    // Set AES Cipher Key
    SET_HDCP22_RX3_ONLINE_AES(pucCipherArray, pucInputArray);

    // Set HW to Authenticated State
    ScalerSetByte_EXINT(P2E_28_HDCP_I2C_CTRL_2, 0x10);
    ScalerSetBit_EXINT(P2E_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Value in INT
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ScalerSetByte_EXINT(P2E_21_HDCP_MSGWAP, ucSubAddr);

    // Load Value To FW
    for(BYTE ucLoopIndex = ucSubAddr; ucLoopIndex < (ucSubAddr + ucLength); ucLoopIndex++)
    {
        pucReadArray[ucLoopIndex - ucSubAddr] = ScalerGetByte_EXINT(P2E_22_HDCP_MSGWDP);
    }
}

//--------------------------------------------------
// Description  : HDCP 1.4 Switch to HDCP 2.2 (Can't change the enable/disable procedure)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3Enable_EXINT0(void)
{
    ScalerTmdsMacRxWaitSclStatusIntoIdle_EXINT0(ScalerTmdsMacRxRxDxMapping_EXINT0(_RX3));

    // Detectd DDC non-Toggle or Timeout to Enable HDCP 2.2 Function
    // Enable HDCP 2.2 Module
    ScalerSetBit_EXINT(P2E_26_HDCP_I2C_CTRL_0, ~_BIT7, _BIT7);

    // Disable HDCP 1.4 Module
    ScalerSetBit_EXINT(P72_C0_HDCP_CR, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Int Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3IntHandler_EXINT0(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    BYTE pucBackUp[4];
#else
    BYTE pucBackUp[2];
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P72_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P72_C8_HDMI_APC) & 0x01);
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    pucBackUp[2] = ScalerGetByte_EXINT(P77_C9_HDMI_AP);
    pucBackUp[3] = (ScalerGetByte_EXINT(P77_C8_HDMI_APC) & 0x01);
#endif

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, 0x00);
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    ScalerSetBit_EXINT(P77_C8_HDMI_APC, ~_BIT0, 0x00);
#endif

    BYTE pucTemp1[16] = {0};
    BYTE pucTemp2[16] = {0};
    BYTE pucTemp3[16] = {0};

    // Backup W/R Sram & HDCP Port Addr.
    g_pucHdcp2BackUp[0] = ScalerGetByte_EXINT(P2E_21_HDCP_MSGWAP);
    g_pucHdcp2BackUp[1] = ScalerGetByte_EXINT(P2E_23_HDCP_MSGRAP_H);
    g_pucHdcp2BackUp[2] = ScalerGetByte_EXINT(P2E_24_HDCP_MSGRAP_L);
    g_pucHdcp2BackUp[3] = ScalerGetByte_EXINT(P72_C3_HDCP_AP);

    // Detect HDCP 2.2 Write Message Done IRQ
    if((ScalerGetBit_EXINT(P2E_35_HDCP_I2C_CTRL_7, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P2E_36_HDCP_I2C_CTRL_8, _BIT0) == _BIT0))
    {
        // Clear HDCP 2.2 Write Message Done Flag
        ScalerSetBit_EXINT(P2E_36_HDCP_I2C_CTRL_8, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        // Judge HDCP Switch to 2.2 Mode or not
        if((ScalerGetBit_EXINT(P2E_26_HDCP_I2C_CTRL_0, _BIT7) == 0x00) && (ScalerGetBit_EXINT(P72_C0_HDCP_CR, _BIT0) == _BIT0))
        {
            ScalerTmdsHdcp2Rx3Enable_EXINT0();
        }

        ScalerSetByte_EXINT(P2E_21_HDCP_MSGWAP, 0x00);

        // Detect HDCP 2.2 Transmitter Write AKE_Init Message, Message ID = 2
        switch(ScalerGetByte_EXINT(P2E_22_HDCP_MSGWDP))
        {
            case _HDCP22_AKE_INIT:

                // HDCP2 Reset Proc
                ScalerTmdsHdcp2Rx3ResetProc_EXINT0();

                // Save Transmitter Rtx to FW
                ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(0x01, 8, g_pucTmdsHdcp2Rx3Rtx);

                // Save TxCaps to FW
                ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(0x09, 3, g_pucTmdsHdcp2Rx3TxCaps);

                // Generate the psudo-random key of Rrx
                ScalerHdcp2RxGenRrx_EXINT0(g_pucTmdsHdcp2Rx3Rrx);

                // Load Certrx to Read SRAM
                ScalerTmdsHdcp2Rx3SetRdMsgValue_EXINT0(0x01, g_stHdcp2RxDownLoadKeyType.pucHdcp2Certrx, 522);

                // Load Rrx to Read SRAM
                ScalerTmdsHdcp2Rx3SetRdMsgValue_EXINT0(0x020B, g_pucTmdsHdcp2Rx3Rrx, 8);

                // Load RxCaps HDCP 2.2 Support to Read SRAM
                ScalerTmdsHdcp2Rx3SetRdMsgValue_EXINT0(0x0213, g_pucTmdsMacRx3Caps, 3);

                // Load Message ID = 3
                ScalerTmdsHdcp2Rx3SetRdMsgIDCode_EXINT0(_HDCP22_AKE_SEND_CERT);

                // Set AKE_SEND_CERT Message Size = 534
                ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x70);
                ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x16);
                ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x71);
                ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x02);
                ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

                SET_TMDS_HDCP2_RX3_AKE_INIT_RECEIVED();
                SET_TMDS_MAC_RX3_BACKUP_HDCP_TYPE(_HDCP_22);

                break;

            case _HDCP22_AKE_NO_STORED_KM:

                SET_TMDS_HDCP2_RX3_AKE_NO_STORED_KM_RECEIVED();
                SET_TMDS_HDCP2_RX3_AUTHENTICATION_ACTIVE();

                if(ScalerHdcp2RsaAvailable_EXINT0() == _TRUE)
                {
                    if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT7) == _BIT7) // RSA power on
                    {
                        // delay to start RSA Cal
                        ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_RSA_CAL_START);
                    }
                    else
                    {
                        ScalerTmdsHdcp2Rx3RxRsaCalculate_EXINT0();
                    }
                }
                break;

            case _HDCP22_AKE_STORED_KM:

                // Save m From Transmitter to FW
                ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(0x11, 16, g_pucHdcp2M);

                // Calculate Km use AES Cipher, Input Value = m, Input Cipher = Kh
                ScalerHdcp2Proc2_EXINT0(pucTemp1, g_pucHdcp2Kh);

                ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, pucTemp1);

                // Save Ekh[km] From Transmitter to FW
                ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(0x01, 16, pucTemp1);

                for(BYTE ucLoopIndex = 0; ucLoopIndex < 0x10; ++ucLoopIndex)
                {
                    pucTemp1[ucLoopIndex] = pucTemp1[ucLoopIndex] ^ ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + ucLoopIndex);
                }

                // Calculate DKey0
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_0, g_pucTmdsHdcp2Rx3Rtx, g_pucTmdsHdcp2Rx3Rrx, pucTemp1, g_pucTmdsHdcp2Rx3Rn);

                for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
                {
                    pucTemp2[ucLoopIndex] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + ucLoopIndex);
                }

                // Calculate Dkey1
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_1, g_pucTmdsHdcp2Rx3Rtx, g_pucTmdsHdcp2Rx3Rrx, pucTemp1, g_pucTmdsHdcp2Rx3Rn);

                for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
                {
                    pucTemp3[ucLoopIndex] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + ucLoopIndex);
                }

                // Calculate H'
                if(ScalerHdcp2HPrimeCalculate_EXINT0(pucTemp2, pucTemp3, g_pucTmdsHdcp2Rx3Rtx, g_pucTmdsHdcp2Rx3TxCaps, g_pucTmdsMacRx3Caps) == _TRUE)
                {
                    // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 0x07
                    ScalerTmdsHdcp2Rx3SetRdMsgIDCode_EXINT0(_HDCP22_AKE_SEND_H_PRIME);

                    for(BYTE ucLoopIndex = 0; ucLoopIndex < 32; ucLoopIndex++)
                    {
                        g_pucHdcp2Sha256[ucLoopIndex] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + ucLoopIndex);
                    }

                    ScalerTmdsHdcp2Rx3SetRdMsgValue_EXINT0(0x01, g_pucHdcp2Sha256, 32);

                    // Set Message Size = 0x21
                    ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                    ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x70);
                    ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x21);
                    ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x71);
                    ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x00);
                    ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, 0x00);
                }

                ScalerHdcp2Proc2_EXINT0(g_pucTmdsHdcp2Rx3Km, pucTemp1);
                ScalerHdcp2Proc2_EXINT0(g_pucTmdsHdcp2Rx3dKey0, pucTemp2);
                ScalerHdcp2Proc2_EXINT0(g_pucTmdsHdcp2Rx3dKey1, pucTemp3);

                SET_TMDS_HDCP2_RX3_AKE_STORED_KM_RECEIVED();

                // Set HDCP 2.2 State to Compute Km
                SET_TMDS_HDCP2_RX3_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_KM);

                break;

            case _HDCP22_LC_INIT:

                // Save Transmitter Rn to FW
                ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(0x01, 8, g_pucTmdsHdcp2Rx3Rn);

                ScalerHdcp2Proc2_EXINT0(pucTemp2, g_pucTmdsHdcp2Rx3dKey0);
                ScalerHdcp2Proc2_EXINT0(pucTemp3, g_pucTmdsHdcp2Rx3dKey1);

                if(ScalerHdcp2LPrimeCalculate_EXINT0(pucTemp2, pucTemp3, g_pucTmdsHdcp2Rx3Rrx, g_pucTmdsHdcp2Rx3Rn) == _TRUE)
                {
                    // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 10
                    ScalerTmdsHdcp2Rx3SetRdMsgIDCode_EXINT0(_HDCP22_LC_SEND_L_PRIME);

                    for(BYTE ucLoopIndex = 0; ucLoopIndex < 32; ucLoopIndex++)
                    {
                        g_pucHdcp2Sha256[ucLoopIndex] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + ucLoopIndex);
                    }

                    ScalerTmdsHdcp2Rx3SetRdMsgValue_EXINT0(0x01, g_pucHdcp2Sha256, 32);

                    // Set Message Size = 0x21
                    ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                    ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x70);
                    ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x21);
                    ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x71);
                    ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x00);
                    ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, 0x00);
                }

                SET_TMDS_HDCP2_RX3_LC_INIT_RECEIVED();

                // Set HDCP 2.2 State to Compute L'
                SET_TMDS_HDCP2_RX3_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_L_PRIME);

                break;

            case _HDCP22_SKE_SEND_EKS:

                // HW Encryption Mode for Input Cipher
                if(ScalerGetBit_EXINT(P67_00_HDMI_TOP_0, _BIT6) == 0x00)
                {
                    ScalerSetBit_EXINT(P2E_10_AES_DUMMY_0, ~_BIT6, _BIT6);
                }
                else
                {
                    ScalerSetBit_EXINT(P2E_60_AES_DUMMY_1_0, ~_BIT6, _BIT6);
                }

                // Calculate Dkey 2
                ScalerHdcp2Proc2_EXINT0(pucTemp1, g_pucTmdsHdcp2Rx3Km);

                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_2, g_pucTmdsHdcp2Rx3Rtx, g_pucTmdsHdcp2Rx3Rrx, pucTemp1, g_pucTmdsHdcp2Rx3Rn);

                // Save EDkeyKs from Write SRAM to FW
                ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(0x01, 16, g_pucHdcp2EDkeyKs);

                // Save Riv from Write SRAM to FW
                ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(0x11, 8, g_pucHdcp2Riv);

                // Decode Ks
                for(BYTE ucLoopIndex = 0; ucLoopIndex < 8; ++ucLoopIndex)
                {
                    pucTemp2[ucLoopIndex] = g_pucHdcp2EDkeyKs[ucLoopIndex] ^ ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + ucLoopIndex));
                }

                for(BYTE ucLoopIndex = 8; ucLoopIndex < 16; ++ucLoopIndex)
                {
                    pucTemp2[ucLoopIndex] = g_pucHdcp2EDkeyKs[ucLoopIndex] ^ (ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + ucLoopIndex)) ^ g_pucTmdsHdcp2Rx3Rrx[ucLoopIndex - 8]);
                }

                SET_TMDS_HDCP2_RX3_AUTHENTICATION_DONE();

                // Enable HDMI Link Integrity Check & Clear BCH Error Flag
                ScalerTmdsHdcp2Rx3LinkIntegrityCheckEnable_EXINT0();

                SET_TMDS_HDCP2_RX3_AUTH_STATE(_HDCP_2_2_STATE_AUTHENTICATED);

                // Enable Decryption
                ScalerHdcp2Proc1_EXINT0(pucTemp1, g_stHdcp2RxDownLoadKeyType.pucHdcp2Lc);

                for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ++ucLoopIndex)
                {
                    g_pucHdcp2InputCipher[ucLoopIndex] = pucTemp2[ucLoopIndex] ^ pucTemp1[ucLoopIndex];
                }

                ScalerHdcp2Proc2_EXINT0(g_pucHdcp2Ks, pucTemp2);

                ScalerHdcp2Proc4_EXINT0(g_pucHdcp2InputCipher);

                // Enable AES Decryption Cipher
                ScalerTmdsHdcp2Rx3AesOnlineCtrl_EXINT0(g_pucHdcp2Riv, g_pucHdcp2InputCipher);

                SET_TMDS_HDCP2_RX3_SKE_SEND_EKS_RECEIVED();

                break;

            default:
                break;
        }
    }

    // Source Has Read Msg Done IRQ
    if((ScalerGetBit_EXINT(P2E_35_HDCP_I2C_CTRL_7, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P2E_36_HDCP_I2C_CTRL_8, _BIT1) == _BIT1))
    {
        // Clear Read Msg Done Flag
        ScalerSetBit_EXINT(P2E_36_HDCP_I2C_CTRL_8, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

        // Disable Read Msg Done IRQ
        ScalerSetBit_EXINT(P2E_35_HDCP_I2C_CTRL_7, ~_BIT1, 0x00);

        // Start Pairing AES Calculate
        for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ++ucLoopIndex)
        {
            if(ucLoopIndex < 8)
            {
                g_pucHdcp2M[ucLoopIndex] = g_pucTmdsHdcp2Rx3Rtx[ucLoopIndex];
            }
            else
            {
                g_pucHdcp2M[ucLoopIndex] = g_pucTmdsHdcp2Rx3Rrx[ucLoopIndex - 8];
            }
        }

        // AES Cipher Calculate Ekh[km]
        ScalerHdcp2Proc2_EXINT0(pucTemp1, g_pucHdcp2Kh);

        ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, pucTemp1);

        // Calculate Ekh[km] = kh AES m XOR Km
        ScalerHdcp2Proc2_EXINT0(pucTemp1, g_pucTmdsHdcp2Rx3Km);

        for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ++ucLoopIndex)
        {
            g_pucHdcp2EkhKm[ucLoopIndex] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + ucLoopIndex) ^ pucTemp1[ucLoopIndex];
        }

        ScalerTmdsHdcp2Rx3SetRdMsgValue_EXINT0(0x01, g_pucHdcp2EkhKm, 16);

        // Load AKE Send Pairing Info
        ScalerTmdsHdcp2Rx3SetRdMsgIDCode_EXINT0(_HDCP22_AKE_SEND_PAIRING_INFO);

        // Set Message Size = 0x11
        ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
        ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x70);
        ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x11);
        ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x71);
        ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x00);
        ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, 0x00);
    }

    // Recover Backup for  W/R Sram & HDCP Port Addr.
    ScalerSetByte_EXINT(P2E_21_HDCP_MSGWAP, g_pucHdcp2BackUp[0]);
    ScalerSetByte_EXINT(P2E_23_HDCP_MSGRAP_H, g_pucHdcp2BackUp[1]);
    ScalerSetByte_EXINT(P2E_24_HDCP_MSGRAP_L, g_pucHdcp2BackUp[2]);
    ScalerSetByte_EXINT(P72_C3_HDCP_AP, g_pucHdcp2BackUp[3]);

    ScalerSetBit_EXINT(P72_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, pucBackUp[0]);
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    ScalerSetBit_EXINT(P77_C8_HDMI_APC, ~_BIT0, pucBackUp[3]);
    ScalerSetByte_EXINT(P77_C9_HDMI_AP, pucBackUp[2]);
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 Enable the Link Integrity Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3LinkIntegrityCheckEnable_EXINT0(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
    {
        ScalerSetByte_EXINT(P77_C9_HDMI_AP, _P77_CA_PT_63_PORT_PAGE77_HDMI_PEAC1);
        BYTE ucData = ((ScalerGetByte_EXINT(P77_CA_HDMI_DP) & (~_BIT7)) | _BIT7 | _BIT6);

        ScalerSetByte_EXINT(P77_C9_HDMI_AP, _P77_CA_PT_63_PORT_PAGE77_HDMI_PEAC1);
        ScalerSetByte_EXINT(P77_CA_HDMI_DP, ucData);
    }
    else
#endif
    {
        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_63_PORT_PAGE72_HDMI_PEAC1);
        BYTE ucData = ((ScalerGetByte_EXINT(P72_CA_HDMI_DP) & (~_BIT7)) | _BIT7 | _BIT6);

        ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_63_PORT_PAGE72_HDMI_PEAC1);
        ScalerSetByte_EXINT(P72_CA_HDMI_DP, ucData);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3ResetProc_EXINT0(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    BYTE pucBackUp[2];

    pucBackUp[0] = ScalerGetByte_EXINT(P77_C9_HDMI_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P77_C8_HDMI_APC) & 0x01);

    // Set CA Port non-auto increase
    ScalerSetBit_EXINT(P77_C8_HDMI_APC, ~_BIT0, 0x00);
#endif

    // Disable Read Msg Done IRQ
    ScalerSetBit_EXINT(P2E_35_HDCP_I2C_CTRL_7, ~_BIT1, 0x00);

    // Clear Reading Msg Size & RxStatus REAUTH_REQ
    ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
    ScalerSetByte_EXINT(P72_C3_HDCP_AP, _P72_C4_PT_70_PORT_PAGE72_HDCP2_STATUS1);
    ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x00);
    ScalerSetByte_EXINT(P72_C3_HDCP_AP, _P72_C4_PT_71_PORT_PAGE72_HDCP2_STATUS2);
    ScalerSetBit_EXINT(P72_C4_HDCP_DP, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

    // Disable Link Interity Check
    ScalerSetByte_EXINT(P72_C9_HDMI_AP, _P72_CA_PT_63_PORT_PAGE72_HDMI_PEAC1);
    ScalerSetBit_EXINT(P72_CA_HDMI_DP, ~(_BIT7 | _BIT6), 0x00);

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    ScalerSetByte_EXINT(P77_C9_HDMI_AP, _P77_CA_PT_63_PORT_PAGE77_HDMI_PEAC1);
    ScalerSetBit_EXINT(P77_CA_HDMI_DP, ~(_BIT7 | _BIT6), 0x00);
#endif

    // Reset Authenticated FSM
    ScalerSetByte_EXINT(P2E_28_HDCP_I2C_CTRL_2, 0x01);
    ScalerSetBit_EXINT(P2E_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

    // Cancel HDCP 2.2 Re-Auth Timer Event
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH);

    // Cancel HDCP 2.2 RSA Cal Timer Event
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_RSA_CAL_START);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX3_HDCP2_SET_REAUTH);

    CLR_TMDS_HDCP2_RX3_AUTHENTICATION_DONE();
    CLR_TMDS_HDCP2_RX3_AKE_INIT_RECEIVED();
    CLR_TMDS_HDCP2_RX3_AKE_NO_STORED_KM_RECEIVED();
    CLR_TMDS_HDCP2_RX3_AKE_STORED_KM_RECEIVED();
    CLR_TMDS_HDCP2_RX3_LC_INIT_RECEIVED();
    CLR_TMDS_HDCP2_RX3_SKE_SEND_EKS_RECEIVED();
    CLR_TMDS_HDCP2_RX3_AUTHENTICATION_ACTIVE();

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    ScalerSetBit_EXINT(P77_C8_HDMI_APC, ~_BIT0, pucBackUp[1]);
    ScalerSetByte_EXINT(P77_C9_HDMI_AP, pucBackUp[0]);
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate in INT
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3RxRsaCalculate_EXINT0(void)
{
    BYTE pucHdcp2KpubKm[128];
    BYTE ucIndex = 0;

    // Save Transmitter Ekpub[km] to FW
    ScalerSetByte_EXINT(P2E_21_HDCP_MSGWAP, 0x01);

    for(ucIndex = 0; ucIndex < 128; ++ucIndex)
    {
        pucHdcp2KpubKm[ucIndex] = ScalerGetByte_EXINT(P2E_22_HDCP_MSGWDP);
    }

    // RSA Calculate
    ScalerHdcp2RxRsaCal_EXINT0(pucHdcp2KpubKm);

    // delay to check RSA
    ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_TMDS_RX3_HDCP2_CHECK_RSA_CAL_DONE);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message ID Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3SetRdMsgIDCode_EXINT0(BYTE ucValue)
{
    ScalerSetBit_EXINT(P2E_23_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte_EXINT(P2E_24_HDCP_MSGRAP_L, 0x00);
    ScalerSetByte_EXINT(P2E_25_HDCP_MSGRDP, ucValue);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message Value in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3SetRdMsgValue_EXINT0(WORD usAddress, BYTE *pucReadArray, WORD usLength)
{
    WORD usTemp = 0;

    ScalerSetBit_EXINT(P2E_23_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), usAddress >> 8);
    ScalerSetByte_EXINT(P2E_24_HDCP_MSGRAP_L, usAddress);

    // Set HDCP 2 Read SRAM Message Value, Disable HDCP 2 Read SRAM auto Increase
    for(usTemp = usAddress; usTemp < (usAddress + usLength); usTemp++)
    {
        ScalerSetByte_EXINT(P2E_25_HDCP_MSGRDP, pucReadArray[usTemp - usAddress]);
    }
}
#endif

#endif
