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
// ID Code      : ScalerTmdsHdcp2Rx3_WDINT.c No.0000
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
// Description  : HDCP 2.2 RSA Calculate in INT
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3RxRsaCalculate_WDINT(void)
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
    ScalerHdcp2RxRsaCal_WDINT(pucHdcp2KpubKm);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message ID Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3SetRdMsgIDCode_WDINT(BYTE ucValue)
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
void ScalerTmdsHdcp2Rx3SetRdMsgValue_WDINT(WORD usAddress, BYTE *pucReadArray, WORD usLength)
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

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message Value in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTmdsHdcp2Rx3HPrime_WDINT(BYTE *pucTemp1)
{
    BYTE pucTemp2[16] = {0};
    BYTE pucTemp3[16] = {0};
    BYTE pucBackUp[2] = {0};
    pucBackUp[0] = ScalerGetByte_EXINT(P72_C3_HDCP_AP);
    pucBackUp[1] = (ScalerGetByte_EXINT(P72_C2_HDCP_PCR) & 0x01);

    // Set C4 Port non-auto increase
    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), _BIT0);

    ScalerHdcp2DkeyCalculate_WDINT(_HDCP_2_2_DKEY_0, g_pucTmdsHdcp2Rx3Rtx, g_pucTmdsHdcp2Rx3Rrx, pucTemp1, g_pucTmdsHdcp2Rx3Rn);

    memcpy(pucTemp2, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

    ScalerHdcp2DkeyCalculate_WDINT(_HDCP_2_2_DKEY_1, g_pucTmdsHdcp2Rx3Rtx, g_pucTmdsHdcp2Rx3Rrx, pucTemp1, g_pucTmdsHdcp2Rx3Rn);

    memcpy(pucTemp3, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

    if(ScalerHdcp2HPrimeCalculate_WDINT(pucTemp2, pucTemp3, g_pucTmdsHdcp2Rx3Rtx, g_pucTmdsHdcp2Rx3TxCaps, g_pucTmdsMacRx3Caps) == _TRUE)
    {
        __real_memset(g_pucHdcp2Sha256, 0, sizeof(g_pucHdcp2Sha256));

        // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 0x07
        ScalerTmdsHdcp2Rx3SetRdMsgIDCode_WDINT(_HDCP22_AKE_SEND_H_PRIME);

        memcpy(g_pucHdcp2Sha256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

        // Load Km to Read SRAM
        ScalerTmdsHdcp2Rx3SetRdMsgValue_WDINT(0x01, g_pucHdcp2Sha256, 32);

        // Set Message Size = 0x21
        ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
        ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x70);
        ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x21);
        ScalerSetByte_EXINT(P72_C3_HDCP_AP, 0x71);
        ScalerSetByte_EXINT(P72_C4_HDCP_DP, 0x00);
        ScalerSetBit_EXINT(P2E_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

        // Enable HDCP2 Source Read Done IRQ
        ScalerSetBit_EXINT(P2E_36_HDCP_I2C_CTRL_8, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
        ScalerSetBit_EXINT(P2E_35_HDCP_I2C_CTRL_7, ~_BIT1, _BIT1);
    }

    ScalerHdcp2Proc2_WDINT(g_pucTmdsHdcp2Rx3Km, pucTemp1);
    ScalerHdcp2Proc2_WDINT(g_pucTmdsHdcp2Rx3dKey0, pucTemp2);
    ScalerHdcp2Proc2_WDINT(g_pucTmdsHdcp2Rx3dKey1, pucTemp3);

    // Set HDCP 2.2 State to Compute Km
    SET_TMDS_HDCP2_RX3_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_KM);

    ScalerSetBit_EXINT(P72_C2_HDCP_PCR, ~(_BIT4 | _BIT0), pucBackUp[1]);
    ScalerSetByte_EXINT(P72_C3_HDCP_AP, pucBackUp[0]);
}
#endif
#endif

