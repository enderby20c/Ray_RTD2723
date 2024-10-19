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
// ID Code      : ScalerDpHdcp2Rx_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp2Rx/ScalerDpHdcp2Rx.h"



#if(_DP_HDCP2_RX_SUPPORT == _ON)
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
// Description  : As a part of AKE_INIT Proc, after Gen & Load Rrx
//                Split here to avoid taking too long time in EXINT
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxAkeInitProc_WDINT(EnumInputPort enumInputPort)
{
    ScalerDpHdcp2RxClearDpcdReadValue_WDINT(enumInputPort, _HDCP22_RX_H_PRIME, 32);
    ScalerDpHdcp2RxClearDpcdReadValue_WDINT(enumInputPort, _HDCP22_RX_L_PRIME, 32);
    ScalerDpHdcp2RxClearDpcdReadValue_WDINT(enumInputPort, _HDCP22_RX_M_PRIME, 32);
    ScalerDpHdcp2RxClearDpcdReadValue_WDINT(enumInputPort, _HDCP22_RX_PAIRING_INFO, 16);

    switch(ScalerDpHdcpRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)
        case _RX0:

            SET_DP_HDCP2_RX0_CLEAR_DPCD_READ_VALUE_DONE();

            break;
#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)
        case _RX1:

            SET_DP_HDCP2_RX1_CLEAR_DPCD_READ_VALUE_DONE();

            break;
#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)
        case _RX2:

            SET_DP_HDCP2_RX2_CLEAR_DPCD_READ_VALUE_DONE();

            break;
#endif

        default:

            return;
    }
}

//--------------------------------------------------
// Description  : Clear HDCP Receiver Public Key Certificate
// Input Value  : Public Key / Write Length
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxClearDpcdReadValue_WDINT(EnumInputPort enumInputPort, BYTE ucRSAType, WORD usLength)
{
    BYTE ucIndex = 0x00;
    WORD usDpcdAddress = 0;
    BYTE ucDpcdAddrMid = 0x00;
    BYTE ucDpcdAddrLow = 0x00;

    switch(ucRSAType)
    {
        case _HDCP22_RRX:

            ucDpcdAddrMid = 0x92;
            ucDpcdAddrLow = 0x15;

            break;

        case _HDCP22_RX_H_PRIME:

            ucDpcdAddrMid = 0x92;
            ucDpcdAddrLow = 0xC0;

            break;

        case _HDCP22_RX_PAIRING_INFO:

            ucDpcdAddrMid = 0x92;
            ucDpcdAddrLow = 0xE0;

            break;

        case _HDCP22_RX_L_PRIME:

            ucDpcdAddrMid = 0x92;
            ucDpcdAddrLow = 0xF8;

            break;

        case _HDCP22_RX_M_PRIME:

            ucDpcdAddrMid = 0x94;
            ucDpcdAddrLow = 0x73;

            break;

        case _HDCP22_RX_V_PRIME:

            ucDpcdAddrMid = 0x93;
            ucDpcdAddrLow = 0x32;

            break;

        default:

            return;
    }

    usDpcdAddress = (((WORD)ucDpcdAddrMid << 8) | ((WORD)ucDpcdAddrLow));

    for(ucIndex = 0; ucIndex < usLength; ucIndex++)
    {
        // DPCD [IGNORE]
        ScalerDpAuxRxSetDpcdValue_WDINT(enumInputPort, 0x06, HIBYTE(usDpcdAddress), LOBYTE(usDpcdAddress), 0x00);
        usDpcdAddress = usDpcdAddress + 1;
    }
}

//--------------------------------------------------
// Description  : Execute Ske_Send_Eks Procedure
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxSkeProc_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping_WDINT(enumInputPort))
    {
#if((_DP_HDCP2_RX0_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _RX0:
            ScalerDpHdcp2Rx0SkeProc_WDINT();
            break;
#endif

#if((_DP_HDCP2_RX1_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _RX1:
            ScalerDpHdcp2Rx1SkeProc_WDINT();
            break;
#endif

#if((_DP_HDCP2_RX2_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _RX2:
            ScalerDpHdcp2Rx2SkeProc_WDINT();
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Execute Calculate H' Procedure
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxHPrimeProc_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping_WDINT(enumInputPort))
    {
#if((_DP_HDCP2_RX0_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _RX0:
            ScalerDpHdcp2Rx0HPrimeProc_WDINT();
            break;
#endif

#if((_DP_HDCP2_RX1_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _RX1:
            ScalerDpHdcp2Rx1HPrimeProc_WDINT();
            break;
#endif

#if((_DP_HDCP2_RX2_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
        case _RX2:
            ScalerDpHdcp2Rx2HPrimeProc_WDINT();
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Dkey Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxDkeyCalculate_WDINT(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn)
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
            ScalerDpHdcp2RxAesOfflineCtrl_WDINT(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

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
            ScalerDpHdcp2RxAesOfflineCtrl_WDINT(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

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
            ScalerDpHdcp2RxAesOfflineCtrl_WDINT(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Off-Line AES Ctrl in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxAesOfflineCtrl_WDINT(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    BYTE ucData = 0;

    // HDCP 2.2 Reset
    SET_HDCP22_SOFTWARE_RESET();
    CLR_HDCP22_SOFTWARE_RESET();

    // AES Random Disable
    ScalerSetBit_WDINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    // Load Input Value
    for(ucData = 0; ucData < 16; ucData++)
    {
        ScalerSetByte_WDINT((P63_61_HDCP_AES_DATA_IN_15 + ucData), pucInputArray[ucData]);

        ScalerSetByte_WDINT((P63_71_HDCP_AES_CIPHER_KEY_15 + ucData), pucCipherArray[ucData]);
    }

    // Start AES Calculation
    ScalerSetBit_WDINT(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    // Wait Finish for AES
    ucData = 0xFF;
    while((ScalerGetBit_WDINT(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && (--ucData != 0))
    {
        DELAY_5US_EXINT();
    }

    memset((volatile BYTE xdata *)P63_61_HDCP_AES_DATA_IN_15, 0, 16);
    memset((volatile BYTE xdata *)P63_71_HDCP_AES_CIPHER_KEY_15, 0, 16);
}

#if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxMPrimeProc_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping_WDINT(enumInputPort))
    {
#if(_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:
            ScalerDpHdcp2Rx0MPrimeProc_WDINT();
            break;
#endif

#if(_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:
            ScalerDpHdcp2Rx1MPrimeProc_WDINT();
            break;
#endif

#if(_DP_HDCP2_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:
            ScalerDpHdcp2Rx2MPrimeProc_WDINT();
            break;
#endif
        default:

            break;
    }
}
#endif // End of #if(_DP_HDCP2_RX_REPEATER_SUPPORT == _ON)
#endif // End of #if(_DP_HDCP2_RX_SUPPORT == _ON)
